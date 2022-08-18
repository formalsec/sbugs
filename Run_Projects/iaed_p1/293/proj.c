#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define IDPMAX 10000
#define IDEMAX 500
#define PESOMAX 200
#define NOMEMAX 64

/*----------STRUCTS----------------*/

typedef struct Produto{
	char nome[NOMEMAX];
	int idp, preco, peso, qtd;
} produto;

typedef struct Encomenda{
	/* a encomenda possui o peso, ide e uma tabela bidimensional em que na 
	primeira 'dimensao' e o produto e na segunda e o idp do produto no indice 0
	 e a qtd no indice 1*/
	int ide, peso, prdEnc[PESOMAX][2];
} encomenda;

produto stock_produto[IDPMAX];
encomenda stock_encomenda[IDEMAX];
/*o n_pro conta o numero de produtos existentes no stock principal como nao ha 
remocao de produtos do stock principal o n_pro vai ser o proximo indice do
 produto novo e todos os produtos existentes teram indice menor que o n_pro.
 igualmente para as encomendas e para o n_enc*/
int n_pro = 0,n_enc = 0;
 
/*--------funcoes auxiliares---------*/

int leInput(char str[]){
	/* vai colocar na string o input dado no formato 'sa:20:10' dependendo do 
	comando*/ 
	char c;
	int i = 0;
	while((c = getchar()) != '\n'){
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return 0;
}

int separaStrings(char str[], char strAlvo[][NOMEMAX], int max){
	/*vai por na tabela de string as substrings de str dividindo pelos ':'*/
	int i = 0, j = 0, k = 0;
	/*poe os indices da tabela vazios*/
	for(i = 0; i < max; i++){
		strncpy(strAlvo[i], "", NOMEMAX);
	}
	i = 0;
	/*coloca as substings na string*/
	while(str[i] != '\0'){
		if(str[i] == ':'){
			/*muda de substring*/
			strAlvo[j][k] = '\0';
			k = 0;
			j++;
		}else{
			strAlvo[j][k] = str[i];
			k++;
		}
		i++;
	}
	return j;
}

void mergeL(int tabela_final[], int limite_inferior, int limite_superior, int meio, int enc){
	int k, i, j,  tab_aux[IDPMAX];
	/* guarda a metade da esquerda na tab_aux na esquerda */
	for(i = meio + 1; i > limite_inferior; i--){
		tab_aux[i - 1] = tabela_final[i - 1];
	}
	/* guarda a metade da direita na tab_aux na direita ao contrario */
	for(j = meio; j < limite_superior; j++){
		tab_aux[limite_superior + meio - j] = tabela_final[j + 1];
	}
	/* ordena escolhendo o primeiro ou o ultimo */
	for (k = limite_inferior; k <= limite_superior; k++)
	{
		if(strcmp(stock_produto[stock_encomenda[enc].prdEnc[tab_aux[j]][0]].nome,
		 stock_produto[stock_encomenda[enc].prdEnc[tab_aux[i]][0]].nome) < 0){
			tabela_final[k] = tab_aux[j--];
		}else{
			tabela_final[k] = tab_aux[i++];
		}	
	}
}


void mergel(int tabela_final[], int limite_inferior, int limite_superior, int meio){
	int k, i, j,  tab_aux[IDPMAX];
	for(i = meio + 1; i > limite_inferior; i--){
		tab_aux[i - 1] = tabela_final[i - 1];
	}
	for(j = meio; j < limite_superior; j++){
		tab_aux[limite_superior + meio - j] = tabela_final[j + 1];
	}
	for (k = limite_inferior; k <= limite_superior; k++)
	{
		if(stock_produto[tab_aux[j]].preco < stock_produto[tab_aux[i]].preco){
			tabela_final[k] = tab_aux[j--];
		}else if(stock_produto[tab_aux[j]].preco == stock_produto[tab_aux[i]].preco  && stock_produto[tab_aux[j]].idp < stock_produto[tab_aux[i]].idp){
			tabela_final[k] = tab_aux[j--];
		}else{
			tabela_final[k] = tab_aux[i++];
		}	
	}
}

void mergesort(int limite_inferior, int limite_superior, int tabela_final[], int eh_string, int enc){
	int meio = (limite_superior + limite_inferior) / 2;
	if(limite_superior <= limite_inferior)
		return;
	mergesort(limite_inferior, meio, tabela_final, eh_string, enc);
	mergesort(meio + 1, limite_superior, tabela_final, eh_string, enc);
	/* se for o cmd_L vai para o mergeL se for para o cmd_l vai para o mergel*/
	if(eh_string)
		mergeL(tabela_final, limite_inferior, limite_superior, meio, enc);
	else
		mergel(tabela_final, limite_inferior, limite_superior, meio);
}

/*------------funcoes principais--------------*/

int cmd_a(){
	/*divide o input em 4*/
	char s[80], sAux[4][NOMEMAX];
	getchar();
	leInput(s);
	separaStrings(s, sAux, 4);

	/*altera as carateristicas do novo produto*/
	stock_produto[n_pro].idp = n_pro;
	printf("Novo produto %d.\n", n_pro);
	strcpy(stock_produto[n_pro].nome, sAux[0]);
	stock_produto[n_pro].preco = atoi(sAux[1]);
	stock_produto[n_pro].peso = atoi(sAux[2]);
	stock_produto[n_pro].qtd = atoi(sAux[3]);
	/*aumenta o numero de produtos*/
	n_pro++;
	return 0;
}

int cmd_q(){
	int idp;
	char s[NOMEMAX], sAux[2][NOMEMAX];
	getchar();
	leInput(s);
	separaStrings(s, sAux, 2);
	idp = atoi(sAux[0]);
	if(idp < n_pro){
		stock_produto[idp].qtd += atoi(sAux[1]);
	}
	else{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", 
		idp);
	}
	return 0;
}

int cmd_N(){
	stock_encomenda[n_enc].ide = n_enc;
	stock_encomenda[n_enc].peso = 0;
	printf("Nova encomenda %d.\n", n_enc);
	/*aumenta o numero de encomendas*/
	n_enc++;
	return 0;
}

int cmd_A(){
	int i, produto, encomenda, qtd;
	char s[NOMEMAX], sAux[3][NOMEMAX];
	getchar();
	leInput(s);
	separaStrings(s, sAux, 3);
	encomenda = atoi(sAux[0]);
	produto = atoi(sAux[1]);
	qtd = atoi(sAux[2]);
	if(encomenda >= n_enc){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", produto, encomenda);
		return 0;
	}
	if(produto >= n_pro){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", produto, encomenda);
		return 0;	
	}
	if(stock_produto[produto].qtd < qtd){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", produto, encomenda);
		return 0;
	}
	if((stock_encomenda[encomenda].peso + (qtd * stock_produto[produto].peso)) > PESOMAX){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", produto, encomenda);
		return 0;
	}
	/*todos os produtos das encomendas comecam com o idp igual a -1.
	aqui ve quando o idp de um produto esta a -1 ainda nao esta um produto a usar
	este indice, mas primeiro ve se ja existe na encomenda*/
	for(i = 0; i < PESOMAX; i++){
		if(stock_encomenda[encomenda].prdEnc[i][0] == produto){
			break;
		}
	}
	if(i >= PESOMAX){
		for (i = 0; i < PESOMAX; i++){
			if(stock_encomenda[encomenda].prdEnc[i][0] == -1){
			break;
		}
		}
	}
	if(stock_encomenda[encomenda].prdEnc[i][0] == -1){
		stock_encomenda[encomenda].prdEnc[i][0] = produto;
		stock_encomenda[encomenda].prdEnc[i][1] = qtd;
	}else{
		stock_encomenda[encomenda].prdEnc[i][1] += qtd;
	}
	stock_produto[produto].qtd -= qtd;
	stock_encomenda[encomenda].peso += stock_produto[produto].peso * qtd;
	return 0;
}

int cmd_r(){
	int idproduto, qtd;
	char s[NOMEMAX], sAux[2][NOMEMAX];
	getchar();
	leInput(s);
	separaStrings(s, sAux, 2);
	idproduto = atoi(sAux[0]);
	qtd = atoi(sAux[1]);
	if(idproduto >= n_pro){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idproduto);
		return 0;
	}
	if(stock_produto[idproduto].qtd < qtd){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idproduto);
		return 0;
	}
	stock_produto[idproduto].qtd -= qtd ;
	return 0;
}

int cmd_R(){
	int i, idencomenda, idproduto;
	char s[8], sAux[2][NOMEMAX];
	getchar();
	leInput(s);
	separaStrings(s, sAux, 2);
	idencomenda = atoi(sAux[0]);
	idproduto = atoi(sAux[1]);
	if(idencomenda >= n_enc){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idproduto, idencomenda);
		return 0;
	}
	if(idproduto >= n_pro){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idproduto, idencomenda);
		return 0;
	}
	for(i = 0; i < PESOMAX; i++){
		if(stock_encomenda[idencomenda].prdEnc[i][0] == idproduto){
			/*para eliminar basta por o idp a -1*/
			stock_produto[idproduto].qtd += stock_encomenda[idencomenda].prdEnc[i][1];
			stock_encomenda[idencomenda].peso -= stock_encomenda[idencomenda].prdEnc[i][1]
			* stock_produto[idproduto].peso; 
			stock_encomenda[idencomenda].prdEnc[i][0] = 0;
			stock_encomenda[idencomenda].prdEnc[i][0] = -1;
			break;
		}
	}
	return 0;
}

int cmd_C(){
	int i, soma = 0, enc;
	char s[5];
	leInput(s);
	enc = atoi(s);
	if(enc >= n_enc){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
		return 0;
	}
	for(i = 0; i < PESOMAX; i++){
		if(stock_encomenda[enc].prdEnc[i][0] != -1){
			/*o preco total de um prd e a sua qtd que esta guardada na enc e o
			preco que esta no stock_produto*/
			soma += stock_encomenda[enc].prdEnc[i][1] *
			stock_produto[stock_encomenda[enc].prdEnc[i][0]].preco;
		}
	}
	printf("Custo da encomenda %d %d.\n", enc, soma);	
	return 0;
}

int cmd_p(){
	int idproduto, pre;
	char s[NOMEMAX], sAux[2][NOMEMAX];
	leInput(s);
	separaStrings(s, sAux, 2);
	idproduto = atoi(sAux[0]);
	pre = atoi(sAux[1]);
	if(idproduto >= n_pro){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idproduto );
		return 0;
	}
	/*como a encomenda nao guarda o preco dos prd basta alterar no stock*/
	stock_produto[idproduto ].preco = pre;	
	return 0;
}

int cmd_E(){
	int i, qtd_produto = 0, idencomenda, idproduto;
	char s[NOMEMAX], sAux[2][NOMEMAX];
	leInput(s);
	separaStrings(s, sAux, 2);
	idencomenda = atoi(sAux[0]);
	idproduto = atoi(sAux[1]);
	if(idencomenda >= n_enc){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idencomenda);
		return 0;
	}
	if(atoi(sAux[1]) >= n_pro){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idproduto);
		return 0;
	}
	for(i = 0; i < PESOMAX; i++){
		if(stock_encomenda[idencomenda].prdEnc[i][0] == idproduto){
			qtd_produto = stock_encomenda[idencomenda].prdEnc[i][1];
		}
	}
	printf("%s %d.\n", stock_produto[idproduto].nome, qtd_produto);	
	return 0;
}

int cmd_m(){
	int i, j, ide_max, qtd_produto = -1, prod;
	char s[7];
	leInput(s);
	prod = atoi(s);
	if(prod >= n_pro){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod);
		return 0;
	}
	for(i = 0; i < n_enc; i++){
		for(j = 0; j < PESOMAX; j++){
			if(stock_encomenda[i].prdEnc[j][0] == prod &&
			   stock_encomenda[i].prdEnc[j][1] > qtd_produto){
				qtd_produto = stock_encomenda[i].prdEnc[j][1];
				ide_max = i;
			}
		}
	}
	if(qtd_produto != -1){
		printf("Maximo produto %d %d %d.\n", prod, ide_max, qtd_produto);	
	}
	return 0;
}

int cmd_l(){
	int j, tabela_final[IDPMAX], limite_superior = n_pro , limite_inferior = 0;
	/* guarda o idp e depois ordena indo buscar o preco pelo idp*/
	for(j = 0; j < n_pro; j++)
		tabela_final[j] = stock_produto[j].idp;
	/* os dois ultimos parametros estao a zero pois nao interessam para o merge deste cmd */
	mergesort(limite_inferior, limite_superior - 1, tabela_final, 0, 0);
	printf("Produtos\n");
	for(j = 0; j < n_pro; j++){
		printf("* %s %d %d\n", stock_produto[tabela_final[j]].nome,
		 stock_produto[tabela_final[j]].preco, stock_produto[tabela_final[j]].qtd);
	}
	return 0;
}

int cmd_L(){
	int i, enc, tabela_final[PESOMAX], limite_superior = 0, limite_inferior = 0;
	char s[7];
	leInput(s);
	enc = atoi(s);
	/* guarda o indice do produto na enc e depois vai ordenar indo buscar o idp no indice do prd na enc 
	e com o indice consegue ir buscar todos os atributos do produto*/
	if(enc >= n_enc){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
		return 0;
	}
	for(i = 0; i < PESOMAX; i++)
		if(stock_encomenda[enc].prdEnc[i][0] != -1){
			tabela_final[limite_superior] = i;
			limite_superior++;
		}
	mergesort(limite_inferior, limite_superior - 1, tabela_final, 1, enc);
	printf("Encomenda %d\n", enc);
	for(i = 0; i < limite_superior; i++){
		printf("* %s %d %d\n", stock_produto[stock_encomenda[enc].prdEnc[tabela_final[i]][0]].nome,
		 stock_produto[stock_encomenda[enc].prdEnc[tabela_final[i]][0]].preco, stock_encomenda[enc].prdEnc[tabela_final[i]][1]);
	}
	return 0;
}

int main(){
	char c;
	int i, j, run = 1;
	/* inicializa os idp dos produtos das encomendas a -1*/
	for(i = 0; i < IDEMAX; i++){
		for(j = 0; j < PESOMAX; j++){
			stock_encomenda[i].prdEnc[j][0] = -1;
		}
	}
	while(run){
		switch(c = getchar()){
			case 'a':
				cmd_a();
				break;
			case 'q':
				cmd_q();
				break;
			case 'N':
				cmd_N();
				break;
			case 'A':
				cmd_A();
				break;
			case 'r':
				cmd_r();
				break;
			case 'R':
				cmd_R();
				break;
			case 'C':
				cmd_C();
				break;
			case 'p':
				cmd_p();
				break;
			case 'E':
				cmd_E();
				break;
			case 'm':
				cmd_m();
				break;
			case 'l':
				cmd_l();
				break;
			case 'L':
				cmd_L();
				break;
			case 'x':
				run = 0;
				break;
		}
	}
	return 0;
}