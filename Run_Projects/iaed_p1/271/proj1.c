#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> /*PODE USAR-SE? ATOI DEPENDE DISTO*/

/*limite maximo de produtos criados no sistema*/
#define LIM_PRODUTOS 10000
/*tamanho maximo da descricao de cada produto*/
#define LEN_DESCRICAO_PRODUTO 63
/*limite de encomendas criadas no sistema*/
#define LIM_ENCOMENDAS 500
/*peso maximo de cada encomenda*/
#define LIM_PESO_ENCOMENDAS 200

/*guarda o ultimo argumento lido*/
char argument[64];
/*obtem um argumento apartir do user input e guarda-o em 'argument', retorna
 * um ponteiro para argument*/ 
char *get_arg(){
	char input_char;
	int i = 0;	
	while(true){
		input_char = getchar();
		if (input_char == '\n'){
			argument[i] = '\0'; /*'fecha' a string */
			return argument;
		}
		if (input_char == ':'){
			argument[i] = '\0'; /*'fecha' a string */
			return argument;
		}
		argument[i] = input_char;
		i++;
	} 
}

/*idp do proximo produto a ser criado*/
int id_prox_produto = 0; 
/*ide da proxima encomenda a ser criada*/
int id_prox_encomenda = 0; 
/*vetor auxiliar para o merge sort*/
int aux[LIM_PRODUTOS];
/*vetor resultado alfa_srt*/
int idps_ordenados[LIM_PRODUTOS];

/*estrutura que guarda todos os produtos*/
struct produto{
	char descricao[LEN_DESCRICAO_PRODUTO + 1];
	/*encomendas contem os ids das encomendas em que o produto esta listado*/
	int peso, preco, qtd;
	
} produtos[LIM_PRODUTOS];


/*verifica se existe um produto*/
int existe_produto(int id_produto){
	return id_produto < id_prox_produto;
}

/*representacao de um produto na encomenda*/
struct produto_na_encomenda{ 
	int qtd;
};

/*estrutura que guarda todas as encomendas*/
struct encomenda{
	struct produto_na_encomenda produtos[LIM_PRODUTOS];/*indice de 'produtos' = idp*/
	int pso;

} encomendas[LIM_ENCOMENDAS];


/*verifica se existe uma encomenda, retorna 1 se existir e 0 c.c.*/
int existe_encomenda(int id_encomenda){
	return id_encomenda < id_prox_encomenda;
}


/*adiciona uma produto ao sistema*/
void handler_a(){
	int preco, peso, qtd;
	strcpy(produtos[id_prox_produto].descricao, get_arg());
	preco = atoi(get_arg()), peso = atoi(get_arg()), qtd = atoi(get_arg());
	produtos[id_prox_produto].preco = preco;
	produtos[id_prox_produto].peso = peso;
	produtos[id_prox_produto].qtd = qtd;
	printf("Novo produto %d.\n",id_prox_produto);	
	++id_prox_produto;
}


/*adiciona produtos ao stock*/
void handler_q(){
	int idp = atoi(get_arg()), qtd = atoi(get_arg());
	if(!existe_produto(idp)){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
		return;
	}
	produtos[idp].qtd += qtd;	
}


/*inicializa uma nova encomenda*/
void handler_N(){
	printf("Nova encomenda %d.\n", id_prox_encomenda);
	id_prox_encomenda++ ;
}


/*adiciona produtos de um tipo a uma encomenda*/
void handler_A(){
	int ide = atoi(get_arg()), idp = atoi(get_arg()), qtd = atoi(get_arg());
	int peso_final = encomendas[ide].pso + produtos[idp].peso * qtd;
	char msg_err[64]; 
	sprintf(msg_err, "Impossivel adicionar produto %d a encomenda %d.", idp, ide);
	if (!existe_encomenda(ide)){
		printf("%s Encomenda inexistente.\n", msg_err);
		return;
	}
	if (!existe_produto(idp)){
		printf("%s Produto inexistente.\n", msg_err);
		return;
	}
	if (qtd > produtos[idp].qtd){
	       printf("%s Quantidade em stock insuficiente.\n", msg_err);
		return;
		}
	
	if(peso_final > LIM_PESO_ENCOMENDAS){
		printf("%s Peso da encomenda excede o maximo de %d.\n", msg_err, LIM_PESO_ENCOMENDAS);
		return;
	}
	else
		encomendas[ide].pso = peso_final;
	/*atualiza a quantidade do produto em questao*/
	encomendas[ide].produtos[idp].qtd += qtd;	
	/*adiciona se necessario a presenca do produto na encomenda atual*/
	produtos[idp].qtd -= qtd;/*atualiza stock*/
}

/*remove stock a um produto*/
void handler_r(){
	int idp	= atoi(get_arg()), qtd = atoi(get_arg());
	char msg_err[64]; 
	sprintf(msg_err, "Impossivel remover stock do produto %d. ", idp);
	if(!existe_produto(idp)){
		printf("%sProduto inexistente.\n", msg_err);
		return;
	}
	if( produtos[idp].qtd - qtd < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. "
			       "Quantidade insuficiente.\n",qtd, idp);
		return;
	}
	produtos[idp].qtd -= qtd; /*atualiza stock*/

}

/*remove produto de uma encomenda.*/
void handler_R(){
	int ide = atoi(get_arg()), idp = atoi(get_arg());
	char msg_err[64]; 
	sprintf(msg_err, "Impossivel remover produto %d a encomenda %d. ", idp, ide);
	if (!existe_encomenda(ide)){
		printf("%sEncomenda inexistente.\n", msg_err);
		return;
	}
	if (!existe_produto(idp)){
		printf("%sProduto inexistente.\n", msg_err);
		return;
	}
	produtos[idp].qtd += encomendas[ide].produtos[idp].qtd; /*atualiza stock*/
	encomendas[ide].pso -= encomendas[ide].produtos[idp].qtd * produtos[idp].peso;
	encomendas[ide].produtos[idp].qtd = 0;
}


/*calcula o custo de uma encomenda*/
void handler_C(){ 
	int ide = atoi(get_arg()), custo = 0, i;
	if(!existe_encomenda(ide)){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
		return;	
	}
	for(i = 0; i < LIM_PRODUTOS; i++)
		custo += produtos[i].preco * encomendas[ide].produtos[i].qtd;
	printf("Custo da encomenda %d %d.\n", ide, custo);
}


/*altera o preco de um produto*/
void handler_p(){
	int idp = atoi(get_arg()), preco = atoi(get_arg());
	if(!existe_produto(idp)){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
		return;
	}
	produtos[idp].preco = preco;
}


/*lista a descricao e quantidade de um produto na encomenda*/
void handler_E(){
	int ide = atoi(get_arg()), idp = atoi(get_arg());
	if(!existe_encomenda(ide)){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}
	if(!existe_produto(idp)){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		return;
		}
	printf("%s %d.\n", produtos[idp].descricao, encomendas[ide].produtos[idp].qtd);
}


/*lista o id da encomenda em que o produto ocorre mais vezes*/
void handler_m(){
	int idp = atoi(get_arg());
	int i, ide_res = -1, qtd = 0;
	if(!existe_produto(idp)){
		printf("Impossivel listar maximo do produto %d. "
				"Produto inexistente.\n", idp);
		return;
	}
	for(i = 0; i < LIM_ENCOMENDAS; i++){
		if(i >= id_prox_encomenda)
			break;
		if(encomendas[i].produtos[idp].qtd > qtd){
			ide_res = i;
			qtd = encomendas[i].produtos[idp].qtd;
		}
	}
	if(ide_res == -1)/*se nao tiver encontrado nenhum produto*/
		return;
	printf("Maximo produto %d %d %d.\n", idp, ide_res, qtd);
}

int less(int a, int b){
	/*assegurar estabilidade do algoritmo*/
	if(produtos[a].preco == produtos[b].preco)
		return a < b;/*(retorna sempre 0)*/
	return produtos[a].preco < produtos[b].preco;
}
void merge(int a[], int l, int m, int r){
	int i,j,k;
	for(i = m+1; i>l; i--) 
		aux[i-1] = a[i-1];
	for(j = m; j < r; j++)
		aux[r+m-j] = a[j+1];
	for(k = l; k<= r; k++)
		if(less(aux[j],aux[i]))
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
}
void mrge_srt(int p[], int l, int r){
	int m = (r+l)/2;
	if (r <=l)
		return;
	mrge_srt(p ,l ,m);
	mrge_srt(p, m+1, r);
	merge(p, l, m, r);
}

/*lista todos os produtos existentes por ordem crescente de preco*/
void handler_l(){
	int p, idps[LIM_PRODUTOS];
	printf("Produtos\n");
	if(id_prox_produto == 0)
		return;	
        for(p = 0; p < id_prox_produto; p++)	
		idps[p] = p;
	mrge_srt(idps, 0, id_prox_produto-1);
	for(p = 0; p < id_prox_produto; p++)
		printf("* %s %d %d\n", produtos[idps[p]].descricao, 
			produtos[idps[p]].preco, produtos[idps[p]].qtd);
}


/*converte chars para numeros entre 0 e 25*/
int ch_to_s_nr(char char_atual){
		char_atual = (int)char_atual;
		/*tornar a ordenacao case insensitive*/
		if(char_atual >= 97)
			char_atual -=  32; 
		/*fazer 'a' valer 1, 'b' valer 2...*/
		return char_atual - 65;
}


/*organiza('radix sort') a lista de produtos de uma encomenda por ordem alfabetica*/
int alfa_srt(int *ls_idps,int index_range[2], int c, int recursive){
	int ch_atual, p, n, e, index = 0;
	int iter_nr[26] = {0}, ch_slot[26] = {0}, scope_low[26] = {0}, indx_rge[2] = {0};
	/*ver quantas palavras teem o 'c' elemento com a mesma letra*/
	for(p = index_range[0]; p <= index_range[1]; p++ ){
		ch_atual = ch_to_s_nr(produtos[ls_idps[p]].descricao[c]);
		ch_slot[ch_atual]++; 	
	}
	/*calcular o primeiro indice absoluto de cada grupo de palavras*/
	for(e = 0; e < 26; e++){
		for(n = 0; n < e; n++)
			index += ch_slot[n];
		scope_low[e] = index;
		index = 0;
	}
	/*verifica se as strins sao validadas*/
	for(p = index_range[0]; p <= index_range[1]; p++ ){
		/*verifica se a letra nr 'c' existe*/
		if((signed int)strlen(produtos[ls_idps[p]].descricao) <= c + 1)
			return -1;
		ch_atual = ch_to_s_nr(produtos[ls_idps[p]].descricao[c]);
		if(ch_atual < 0)
			return -1;
	}
	/*obtem idps organizados alfabeticamente em ordem ha letra nr 'c'*/
	for(p = index_range[0]; p <= index_range[1]; p++ ){
		ch_atual = ch_to_s_nr(produtos[ls_idps[p]].descricao[c]);
		index = scope_low[ch_atual] + iter_nr[ch_atual] + index_range[0];
		idps_ordenados[index] = ls_idps[p];	
		iter_nr[ch_atual]++;
	}
	if(recursive == 0)
		return 0;
	/*analisa a proxima letra das descricoes*/
	/*for(; c < 1; c++){*/
		indx_rge[0] = 0;
		for(e = 1; e < 26; e++){
			if( scope_low[e] != 0)
				indx_rge[0] += scope_low[e] + 1;
			else
				indx_rge[0] += scope_low[e];
			indx_rge[1] = ch_slot[e] + scope_low[e] -1;
			alfa_srt(idps_ordenados, indx_rge, 1, 0);
			indx_rge[0] = 0;
			indx_rge[1] = 0;
		}
	/*}*/
	return 0;
	}

/*lista todos os produtos de uma encomenda por ordem alfabetica*/
void handler_L(){
	int ide = atoi(get_arg());
	int i, p, nr_ids; /*variaveis de iteracao*/
	int ls_idps[LIM_PRODUTOS];/*lista dos produtos da encomenda*/
	int index_range[2] = {0};
	struct produto pdt;
	if(!existe_encomenda(ide)){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
		return;
	}
	printf("Encomenda %d\n", ide);
	/*identifica todos os produtos que fazem parte da encomenda*/
	for(i = 0, nr_ids = -1; i < LIM_PRODUTOS; i++){
		if(encomendas[ide].produtos[i].qtd > 0){
			nr_ids++;	
			ls_idps[nr_ids] = i;
		}
	}
	index_range[1] = nr_ids;
	if(nr_ids == -1)
		return;
	if(index_range[1] == 0){ 
		pdt = produtos[ls_idps[0]];
		printf("* %s %d %d\n", pdt.descricao, pdt.preco, encomendas[ide].produtos[ls_idps[0]].qtd);
		return;
	}

	alfa_srt(ls_idps, index_range ,0,1);
	
	for(p = 0; p <= nr_ids; p++){
		pdt = produtos[idps_ordenados[p]];
		printf("* %s %d %d\n", pdt.descricao, pdt.preco, encomendas[ide].produtos[idps_ordenados[p]].qtd);
	}
}








int main(){
	char command;
while(true){
	command = getchar();
	if (command == 'x'){
		break;          
	}
	getchar(); /*catches the space*/
	switch (command){
		case 'a':
			handler_a();
			break;
		case 'q':
			handler_q();
			break;
		case 'N':
			handler_N();
			break;
		case 'A':
			handler_A();
			break;
		case 'r':
			handler_r();
			break;
		case 'R':
			handler_R();
			break;
		case 'C':
			handler_C();
			break;
		case 'p':
			handler_p();
			break;
		case 'E':
			handler_E();
			break;
		case 'm':
			handler_m();
			break;
		case 'l':
			handler_l();
			break;
		case 'L':
			handler_L();
			break;
	}
}	
return 0;
}






