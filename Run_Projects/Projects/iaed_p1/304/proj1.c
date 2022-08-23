#include <stdio.h>
#include <string.h>

#define MAX_CAR 63
#define MAX_PROD 10000
#define MAX_ENC 500
#define MAX_PESO_ENC 200

/* Estrutura para os produtos */
typedef struct {
	int identificador;
	char descricao[MAX_CAR];
	int preco;
	int peso;
	int stock;
} produto;


/* Estrutura para as encomendas */
typedef struct {
	/* Indice 0 guarda o id da encomenda; indice 1 guarda a quantidade; indice 2 guarda 1 se existir */
	int prod_in_encomenda[MAX_PESO_ENC][3]; 
	int id_encomenda;
	int var_existente;
} encomenda;



/*##################### VARIAVEIS GLOBAIS #####################*/

/* Lista que contem todos os produtos existentes */
produto lista_produtos[MAX_PROD];
/* O idp e a variavel que corresponde ao maior indice dos produtos que existem*/
int idp;
/* Lista com todas as encomendas */
encomenda lista_encomendas[MAX_ENC];
/* O idp_enc e a variavel que corresponde ao maior indice das encomendas existentes */
int idp_enc;
/*#############################################################*/


/* Esta funcao adiciona um novo produto ao conjunto de produtos existentes */
void cria_produto () {
	
	scanf(" %[^:]:%d:%d:%d", lista_produtos[idp].descricao, &lista_produtos[idp].preco, 
		&lista_produtos[idp].peso, &lista_produtos[idp].stock);
	
	lista_produtos[idp].identificador = idp;
	
	printf("Novo produto %d.\n", lista_produtos[idp].identificador);
	idp += 1;
}


/* Esta funcao adiciona stock a um produto ja existente */
void aumenta_stock() {
	int i, a, qtd;
	scanf("%d:%d",&i, &qtd);
	for (a = 0; lista_produtos[a].identificador != i && a < idp; a++)
		a = a;
	if (lista_produtos[a].preco != 0){
		/* Se o produto existe, tem preco >0 */
		lista_produtos[a].stock += qtd;
	}
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", i);
}


/* Esta funcao cria uma nova encomenda */
void cria_encomenda() {
	lista_encomendas[idp_enc].id_encomenda = idp_enc;
	/* Todas as encomendas criadas tem uma variavel que vale 1 */
	lista_encomendas[idp_enc].var_existente = 1;
	printf("Nova encomenda %d.\n", lista_encomendas[idp_enc].id_encomenda);
	idp_enc += 1;
}


/* Esta funcao adiciona um produto a uma encomenda */
void adiciona_prod_a_encomenda() {
	int i, n, q, a, b, c, d, soma = 0, num_prod, e;
	scanf("%d:%d:%d", &i, &n, &q);
	/* Determinar os identificadores do produto e da encomenda, respetivamente */
	for (a = 0; lista_produtos[a].identificador != n && a < idp; a++)
		a = a;
	for (b = 0;lista_encomendas[b].id_encomenda != i && b < idp_enc; b++)
		b = b;
	/* Se o produto nao existe */
	if (lista_produtos[a].preco == 0)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", n, i);
	/* Se nao existe stock suficiente desse produto */
	else if (q > lista_produtos[a].stock)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", n, i);
		/* Se nao existir nenhuma encomenda com esse identificador */
	else if (lista_encomendas[b].var_existente != 1)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", n, i);

	else {
		
		for (c = 0; lista_encomendas[b].prod_in_encomenda[c][0] != lista_produtos[a].identificador && lista_encomendas[b].prod_in_encomenda[c][2] == 1; c++)
			c = c;
		/* O produto ja existe na encomenda */
		if (lista_encomendas[b].prod_in_encomenda[c][0] == lista_produtos[a].identificador && lista_encomendas[b].prod_in_encomenda[c][2] == 1){
			lista_encomendas[b].prod_in_encomenda[c][1] += q;
			for (d = 0; d <= MAX_PESO_ENC; d++) {
				num_prod = lista_encomendas[b].prod_in_encomenda[d][0];
				for (e = 0; e < idp; e++) {
					if (lista_produtos[e].identificador == num_prod)
						soma += lista_encomendas[b].prod_in_encomenda[d][1] * lista_produtos[e].peso;
				}
			}
			if (soma > MAX_PESO_ENC){
				lista_encomendas[b].prod_in_encomenda[c][1] -= q;
				printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", n, i);	
			}
			else
				/* Reduz o stock do produto no sistema */
				lista_produtos[a].stock -= q;
		}
		/* O produto ainda nao existe na encomenda */
		else {
			lista_encomendas[b].prod_in_encomenda[c][0] = lista_produtos[a].identificador;
			lista_encomendas[b].prod_in_encomenda[c][1] = q;
			for (d = 0; d <= MAX_PESO_ENC; d++){
				num_prod = lista_encomendas[b].prod_in_encomenda[d][0];
				for (e = 0; e < idp; e++) {
					if (lista_produtos[e].identificador == num_prod)
						soma += lista_encomendas[b].prod_in_encomenda[d][1] * lista_produtos[e].peso;
				}
			}
			if (soma <= MAX_PESO_ENC) {
				lista_encomendas[b].prod_in_encomenda[c][2] = 1;
				/* Reduz o stock do produto no sistema */
				lista_produtos[a].stock -= q;
			}
			else {
				lista_encomendas[b].prod_in_encomenda[c][0] = 0;
				lista_encomendas[b].prod_in_encomenda[c][1] = 0;
				printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", n, i);
			}
		}	
	}
}


/* Esta funcao remove unidades de stock a um produto */
void remove_stock_produto() {
	int i, a, q, e, b, soma_stock = 0; 
	scanf("%d:%d", &i, &q);
	for (a = 0; lista_produtos[a].identificador != i && a < idp; a++){
		a = a;
	}
	/* Caso haja encomendas com o produto i */
	for (e = 0; e < MAX_ENC; e++){
		for (b = 0; b <MAX_PESO_ENC; b++){
			if (lista_encomendas[e].prod_in_encomenda[b][0] == a){
				soma_stock += lista_encomendas[e].prod_in_encomenda[b][1];
			}
		}
	}
	/* Se o prduto nao existir */
	if (lista_produtos[a].preco == 0)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", i);
	/* Se o stock restante do produto ficar negativo ou se depois da remocao nao der para satisfazer as encomendas atuais */
	else if (lista_produtos[a].stock - q < 0)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", q, i);
	else {
		lista_produtos[a].stock -= q;
	}
}


/* Esta funcao altera o preco de um produto no sistema */
void altera_preco_produto() {
	int i, a, p;
	scanf("%d:%d", &i, &p);
	for (a = 0; lista_produtos[a].identificador != i && a < idp; a++){
		a = a;
	}	
	if (lista_produtos[a].preco == 0)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", i);
	else
		lista_produtos[a].preco = p;
}


/* Esta funcao devolve o preco de uma encomenda */
void custo_encomenda() {
	int i, m, c, l, a, id_preco, soma = 0, valor_id[MAX_PESO_ENC];
	scanf("%d", &i);
	for (c = 0; lista_encomendas[c].id_encomenda != i && c < idp_enc; c++)
		c = c;
	
	if (lista_encomendas[c].var_existente != 1)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", i);

	else {
		for (m = 0; m < MAX_PESO_ENC && lista_encomendas[c].prod_in_encomenda[m][2] == 1; m++)
			valor_id[m] = lista_encomendas[c].prod_in_encomenda[m][0];

		for (l = 0; l < MAX_PESO_ENC; l++) {
			id_preco = valor_id[l];
			for (a = 0; a < idp; a++) {
				if (lista_produtos[a].identificador == id_preco) 
					soma += lista_produtos[a].preco * lista_encomendas[c].prod_in_encomenda[l][1];
			}
		}
		printf("Custo da encomenda %d %d.\n", lista_encomendas[c].id_encomenda, soma);
	}
}


/* Esta funcao retorna a descricao e a quantidade de certo produto numa certa encomenda */
void desc_stock_prod_in_encomenda() {
	int i, n, c, a, d;
	scanf("%d:%d", &i, &n);
	for (c = 0; lista_encomendas[c].id_encomenda != i && c < idp_enc; c++)
		c = c;
	for (a = 0; lista_produtos[a].identificador != n && a < idp; a++)
		a = a;
	for (d = 0; lista_encomendas[c].prod_in_encomenda[d][0] != n && d < MAX_PESO_ENC; d++)
		d = d;
	if (lista_encomendas[c].var_existente != 1)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", i);
	else if (lista_produtos[a].identificador != n)
		printf("Impossivel listar produto %d. Produto inexistente.\n", n);
	else 
		printf("%s %d.\n", lista_produtos[a].descricao, lista_encomendas[c].prod_in_encomenda[d][1]);
} 


/* Esta funcao remove um produto de uma encomenda */
void remove_produto_encomenda() {
	int i, n, a, c, quant, b, e;
	scanf("%d:%d", &i, &n);
	for (c = 0; lista_encomendas[c].id_encomenda != i && c < idp_enc; c++)
		c = c;
	for (a = 0; lista_produtos[a].identificador != n && a < idp; a++)
		a = a;
	/* Se nao existir nenhuma encomenda com esse identificador */
	if (lista_encomendas[c].var_existente != 1)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", n, i);
	/* Se o produto nao existe */
	else if (lista_produtos[a].preco == 0)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", n, i);
	else{
		for (b = 0; lista_encomendas[c].prod_in_encomenda[b][0] != n; b++)
			b = b;
		quant = lista_encomendas[c].prod_in_encomenda[b][1];
		lista_encomendas[c].prod_in_encomenda[b][1] = 0;
		lista_encomendas[c].prod_in_encomenda[b][0] = 0;
		/* Este produto deixa de existir na encomenda */
		lista_encomendas[c].prod_in_encomenda[b][2] = 0;
		/* O stock desse produto ? reposto no sistema */
		lista_produtos[a].stock += quant;

		/* Reduz se o indice em que cada produto aparece numa encomenda */
		for (e = b; e < MAX_ENC; e++){
			lista_encomendas[c].prod_in_encomenda[e][0] = lista_encomendas[c].prod_in_encomenda[e+1][0];
			lista_encomendas[c].prod_in_encomenda[e][1] = lista_encomendas[c].prod_in_encomenda[e+1][1];
			lista_encomendas[c].prod_in_encomenda[e][2] = lista_encomendas[c].prod_in_encomenda[e+1][2];	
		}
	}
	lista_encomendas[c].var_existente = 1;
}


/* Esta funcao indica a encomenda em que um produto ocorre em maior quantidade */
void identificador_prod_ocorre_mais() {
	int n, a, e, i, max = 0, v;
	/*int v_aux[MAX_ENC][3];*/
	scanf("%d", &n);
	for (a = 0; lista_produtos[a].identificador != n && a < idp; a++)
		a = a;
	
	/* Se o produto nao existe no sistema */
	if (lista_produtos[a].preco == 0)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", n);
	else {
		/* Verificar que a encomenda existe */
		for (e = 0; lista_encomendas[e].var_existente == 1; e++) {
			for (i = 0; lista_encomendas[e].prod_in_encomenda[i][0] != lista_produtos[a].identificador; i++) 
				i = i;
			/* Verifica se a encomenda contem o produto dado */
			if (lista_encomendas[e].prod_in_encomenda[i][0] == lista_produtos[a].identificador && lista_encomendas[e].prod_in_encomenda[i][2] == 1) {
				/* Se a quantidade for a maior, deve imprimir este indicador de encomenda */
				if (lista_encomendas[e].prod_in_encomenda[i][1] > max) {
					v = lista_encomendas[e].id_encomenda;
					max = lista_encomendas[e].prod_in_encomenda[i][1];
				}
				/* Se houver duas encomendas com a mesma quantidade maxima do produto, imprime a de identificador menor */
				else if (lista_encomendas[e].prod_in_encomenda[i][1] == max) {
					if (lista_encomendas[e].id_encomenda < v) {
						v = lista_encomendas[e].id_encomenda;
						max = lista_encomendas[e].prod_in_encomenda[i][1];
					}
				}
			}
		}
		if (v < idp_enc && max > 0)
			printf("Maximo produto %d %d %d.\n", n, v, max);
	}
}




/* Esta funcao lista os produtos de uma dada encomenda por ordem alfabetica */
void prod_ord_alfabetica() {
	int i, c, d, a, m, j;
	char str[MAX_PESO_ENC][MAX_CAR], temp[MAX_CAR];
	int v_final[MAX_PESO_ENC][2], vector[2];

	scanf("%d", &i);
	/* Guarda o indice em que a encomenda se encontra na lista das encomendas */
	for (c = 0; lista_encomendas[c].id_encomenda != i && c < idp_enc; c++)
		c = c;
	if (lista_encomendas[c].var_existente != 1)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", i);

	else {
		for (d = 0; lista_encomendas[c].prod_in_encomenda[d][2] == 1; d++) {
			/* Guarda as descricoes num vetor e o preco e quantidade na encomenda noutro vetor */
			for (a = 0; lista_produtos[a].identificador != lista_encomendas[c].prod_in_encomenda[d][0]; a++)
				a = a;
			strcpy(str[d], lista_produtos[a].descricao);
			/* v_final guarda os valores do preco e quantidade, para se aplicar tambem, a seguir o algoritmo de ordenacao */
			v_final[d][0] = lista_produtos[a].preco;
			v_final[d][1] = lista_encomendas[c].prod_in_encomenda[d][1];
		}
		
		/* Algoritmo que ordena alfabeticamente as descricoes dos produtos na encomenda */
		for(m=1; m<MAX_PESO_ENC; m++){
         	for(j=1; j<MAX_PESO_ENC; j++){
            	if(strcmp(str[j-1], str[j])>0){
                	strcpy(temp, str[j-1]);
                	vector[0] = v_final[j-1][0];
                	vector[1] = v_final[j-1][1];
                	strcpy(str[j-1], str[j]);
                	v_final[j-1][0] = v_final[j][0];
                	v_final[j-1][1] = v_final[j][1];
                	strcpy(str[j], temp);
                	v_final[j][0] = vector[0];
                	v_final[j][1] = vector[1];
            	}
        	}
    	}
    	/* Ter quantidade positiva e condicao necessaria para imprimir resultados */
    	printf("Encomenda %d\n", i);
		for (m = 0; m < MAX_PESO_ENC; m++) {
			if (v_final[m][0] != 0)
				printf("* %s %d %d\n", str[m], v_final[m][0], v_final[m][1]);	  	
		}
		for (m = 0; m < MAX_PESO_ENC; m++)
			v_final[m][0] = 0;
	}
}



/* Esta funcao devolve os produtos do sistema ordenados pelo preco ascendente */
void prod_ord_preco() {
	int a, i, j, v, x;
	int precos[MAX_PROD], ident[MAX_PROD];
	/* Guarda-se os valores dos precos e respetivos identificadores em vetores diferentes, para serem ordenados */
	for (a = 0; a < idp; a++) {
		precos[a] = lista_produtos[a].preco;
		ident[a] = lista_produtos[a].identificador;
	}
	/* Algoritmo de ordenacao dos produtos */
	for (i = 0; i < idp; ++i) {
        for (j = i + 1; j < idp; ++j) {
			if (precos[i] > precos[j]) {
                v =  precos[i];
                x = ident[i];
                precos[i] = precos[j];
                ident[i] = ident[j];
                precos[j] = v;
                ident[j] = x;
            }
        }     
    }
    printf("Produtos\n");
    for (i = 0; i < idp; i++) {
    	for (a = 0; lista_produtos[a].identificador != ident[i]; a++)
    		a = a;
    	printf("* %s %d %d\n", lista_produtos[a].descricao, precos[i], lista_produtos[a].stock);
	}
}



/* A funcao principal recebe um comando, e decide qual a operacao/funcao a executar */
int main(){
	char comando;
	while ((comando = getchar()) != 'x'){
		/* O comando 'x' termina o programa */
		switch(comando){
			case 'a':
				/* Adiciona um novo produto*/
				cria_produto();
				break;
			case 'q':
				/* Adiciona stock a um produto existente*/
				aumenta_stock();
				break;
			case 'N':
				/* Cria nova encomenda */
				cria_encomenda();
				break;
			case 'A':
				/* Adiciona um produto a uma encomenda */
				adiciona_prod_a_encomenda();
				break;
			case 'r':
				/* Remove stock a um produto */
				remove_stock_produto();
				break;
			case 'R':
				/* Remove um produto de uma encomenda */
				remove_produto_encomenda();
				break;
			case 'C':
				/* Calcula o custo de uma encomenda */
				custo_encomenda();
				break;
			case 'p':
				/* Altera o preco de um produto */
				altera_preco_produto();
				break;
			case 'E':
				/* Retorna a descricao e quantidade de um produto numa dada encomenda */
				desc_stock_prod_in_encomenda();
				break;
			case 'm':
				/* Retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
				identificador_prod_ocorre_mais();
				break;
			case 'l':
				/* Lista de todos os produtos por ordem crescente de preco */
				prod_ord_preco();
				break;
			case 'L':
				/* Lista de todos os produtos de uma encomenda por ordem alfabetica de descricao */
				prod_ord_alfabetica();
				break;
		}
	}
	return 0;
}