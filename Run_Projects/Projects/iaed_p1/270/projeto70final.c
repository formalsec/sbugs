#include <stdio.h>
#include <string.h>

#define PRODMAX 10000 		/* Apenas podem haver ate 10000 produtos (Vao de 0 a 9999) */
#define ENCOMAX 10000   	/* Espaco maximo que uma encomenda pode ocupar */
#define DESCMAX 64    		/* A descricao de um produto e uma string com 63 caracteres e um \0 */
#define SISTENCMAX 500		/* Maximo de encomendas possiveis */


/* Estruturas */

typedef struct{
	int identificador;
	char descricao[DESCMAX];
	int preco;
	int peso;
	int quantidade;
} PRODUTO;



typedef struct{
	int identificador;
	int produtos[PRODMAX];
	int peso;				/* Peso total da encomenda */
	int preco;				/* Preco total da encomenda */
} ENCOMENDA;



/* Variaveis globais */

PRODUTO sistema[PRODMAX];		/* Vetor que guarda os produtos */
int idp = -1;		/* idp     identificador do ultimo produto do sistema (inicializado a -1
						   	   pois nao existe nenhum produto no sistema) */

ENCOMENDA sistema_encomendas[SISTENCMAX];		/* Vetor que guarda as encomendas */
int ide = -1;		/* ide     identificador da ultima encomenda do sistema das encomendas
							   (inicializado a -1 pela mesma razao que o idp) */



/* Funcoes */

void cria_produto(char descricao[DESCMAX],int preco, int peso, int quantidade);	/* a */
void adiciona_stock(int i_prod, int quantidade);								/* q */
void cria_encomenda();															/* N */
void adiciona_a_encomenda(int i_encomenda, int i_prod, int quantidade);			/* A */
void remove_stock(int i_prod, int quantidade);									/* r */
void remove_produto(int i_encomenda, int i_prod);								/* R */
void calcula_custo(int i_encomenda);											/* C */
void altera_preco(int i_prod, int preco);										/* p */
void lista_produto(int i_encomenda, int i_prod);								/* E */
void produto_mais_pedido(int i_prod);											/* m */

void ordena_sistema();															/* l */
void mergesort(PRODUTO a[], int l, int r);										/* Ordenacao */
void merge(PRODUTO a[], int l, int m, int r);									/* Auiliar a ordenacao */

void ordena_encomenda(int i_encomenda);											/* L */
void mergesort2(PRODUTO a[], int l, int r);										/* Ordenacao II */
void merge2(PRODUTO a[], int l, int m, int r);									/* Auxiliar a ordenacao II */



/**********************/
/*                    */
/* inicio do programa */
/*                    */
/**********************/


int main(){
	char c, descricao[DESCMAX];
	int preco, peso, quantidade, i_prod, i_encomenda;

	while (1){
		switch (c = getchar()){
			case 'a':	/* Adiciona um produto a uma encomenda */
				scanf(" %[^:]:%d:%d:%d", descricao, &preco, &peso, &quantidade);
				cria_produto(descricao, preco, peso, quantidade);
				break;
			case 'q':	/* Adiciona stock de um produto ao sistema */
				scanf(" %d:%d", &i_prod, &quantidade);
				adiciona_stock(i_prod, quantidade);
				break;
			case 'N':	/* Cria uma encomenda no sistema das encomendas */
				cria_encomenda();
				break;
			case 'A':	/* Adiciona um produto a uma encomenda */
				scanf(" %d:%d:%d", &i_encomenda, &i_prod, &quantidade);
				adiciona_a_encomenda(i_encomenda, i_prod, quantidade);
				break;
			case 'r':	/* Remove stock de um produto numa encomenda */
				scanf(" %d:%d", &i_prod, &quantidade);
				remove_stock(i_prod, quantidade);
				break;
			case 'R':	/* Remove um produto de uma encomenda */
				scanf(" %d:%d", &i_encomenda, &i_prod);
				remove_produto(i_encomenda, i_prod);
				break;
			case 'C':	/* Calcula o custo de uma encomenda */
				scanf(" %d", &i_encomenda);
				calcula_custo(i_encomenda);
				break;
			case 'p':	/* Altera o preco de um produto */
				scanf(" %d:%d", &i_prod, &preco);
				altera_preco(i_prod, preco);
				break;
			case 'E':	/* Retorna a quantidade e a descricao de um produto na encomenda */
				scanf(" %d:%d", &i_encomenda, &i_prod);
				lista_produto(i_encomenda, i_prod);
				break;
			case 'm':	/* Retorna o identificador da encomenda em que o produto aparece mais vezes */
				scanf(" %d", &i_prod);
				produto_mais_pedido(i_prod);
				break;
			case 'l':	/* Ordena os produtos do sistema por ordem crescente de preco */
				ordena_sistema();
				break;
			case 'L':	/* Ordena alfabeticamente os produtos de uma encomenda */
				scanf(" %d", &i_encomenda);
				ordena_encomenda(i_encomenda);
				break;
			case 'x':	/* Termina o programa */
				return 0;
				break;
		}
	}
	return 0;
}




/* Cria produto --> a. Recebe as caracteristicas de um produto e coloca-o no sistema
					   O identificador do produto no sistema e o seu indice no vetor. */

void cria_produto(char descricao[DESCMAX],int preco, int peso, int quantidade){
	PRODUTO prod;
	idp++;

	strcpy(prod.descricao, descricao);
	prod.preco = preco;
	prod.peso = peso;
	prod.quantidade = quantidade;
	prod.identificador = idp;
	sistema[idp] = prod;

	printf("Novo produto %d.\n", idp);
}




/* Adiciona stock --> q. Recebe o identificador do produto e quantidade desse produto e, como o nome indica
						 adiciona essa quantidade ao stock. */

void adiciona_stock(int i_prod, int quantidade){
	if(i_prod > idp)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", i_prod);

	sistema[i_prod].quantidade += quantidade;
}




/* Cria Encomenda --> N. Cria uma encomenda */

void cria_encomenda(){
	ENCOMENDA enc;
	int i;
	ide++;

	for (i = 0; i < PRODMAX; i++)
	{
		enc.produtos[i] = 0;
	}

	enc.peso = 0;
	enc.preco = 0;
	sistema_encomendas[ide] = enc;

	printf("Nova encomenda %d.\n", ide);
}




/* Adiciona a encomenda --> A. Adiciona o produto a uma encomenda */

void adiciona_a_encomenda(int i_encomenda, int i_prod, int quantidade){

	if (i_encomenda > ide){		/* Caso a encomenda nao exista da um erro */
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", i_prod, i_encomenda);
		return;
	}
	if (i_prod > idp){			/* Caso o produto nao exista da um erro */
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", i_prod, i_encomenda);
		return;
	}
	if (quantidade > sistema[i_prod].quantidade){		/* Caso a quantidade pedida seja superior a quantidade em stock da um erro */
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", i_prod, i_encomenda);
		return;
	}
	if (sistema_encomendas[i_encomenda].peso + (quantidade * sistema[i_prod].peso) > 200){		/* caso o peso total da encomenda somado com o do produto ultrapasse os 200 da erro */
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", i_prod, i_encomenda);
		return;
	}

	
	sistema_encomendas[i_encomenda].peso += quantidade * sistema[i_prod].peso;		/* Altera o peso total da encomenda */
	sistema_encomendas[i_encomenda].preco += quantidade * sistema[i_prod].preco;	/* Altera o preco total da encomenda */

	sistema_encomendas[i_encomenda].produtos[i_prod] += quantidade;
	remove_stock(i_prod, quantidade);
}




/* Remove stock --> r. Retira quantidade ao sistema */

void remove_stock(int i_prod, int quantidade){

	if (i_prod > idp){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", i_prod);
		return;
	}

	if (sistema[i_prod].quantidade < quantidade){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, i_prod);
		return;
	}
	sistema[i_prod].quantidade -= quantidade;
}




/* Remove produto --> R. Remove um produto de uma encomenda*/

void remove_produto(int i_encomenda, int i_prod){
	if (i_encomenda > ide){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", i_prod, i_encomenda);
		return;
	}
	if (i_prod > idp){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", i_prod, i_encomenda);
		return;
	}
	if (sistema_encomendas[i_encomenda].produtos[i_prod] == 0){
		return;
	}

	sistema_encomendas[i_encomenda].preco -= sistema[i_prod].preco * sistema_encomendas[i_encomenda].produtos[i_prod];
	sistema[i_prod].quantidade += sistema_encomendas[i_encomenda].produtos[i_prod];
	sistema_encomendas[i_encomenda].peso -= sistema[i_prod].peso * sistema_encomendas[i_encomenda].produtos[i_prod];
	sistema_encomendas[i_encomenda].produtos[i_prod] = 0;

}
	





/* Calcula o custo --> C. */

void calcula_custo(int i_encomenda){
	if (i_encomenda > ide){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", i_encomenda);
		return;
	}

	printf("Custo da encomenda %d %d.\n", i_encomenda, sistema_encomendas[i_encomenda].preco);
}




/* Altera o preco --> p. */

void altera_preco(int i_prod, int preco){
	int i;

	if (i_prod > idp){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", i_prod);
		return;
	}


	for (i = 0; i <= ide; i++)
		if (sistema_encomendas[i].produtos[i_prod] != 0){
			sistema_encomendas[i].preco += sistema_encomendas[i].produtos[i_prod] * (preco - sistema[i_prod].preco);
			/* altera o preco total da encomenda para o preco que deveria ter com produto alterado */
		}

	sistema[i_prod].preco = preco;
}




/* lista o produto --> E. Devolve a quantidade e a descricao de dum produto numa encomenda*/

void lista_produto(int i_encomenda, int i_prod){

	if (ide < i_encomenda){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", i_encomenda);
		return;
	}
	if (idp < i_prod){
		printf("Impossivel listar produto %d. Produto inexistente.\n", i_prod);
		return;
	}

	printf("%s %d.\n", sistema[i_prod].descricao, sistema_encomendas[i_encomenda].produtos[i_prod]);
}



/* Produto mais pedido --> m. Devolve a encomenda em que o produto dado existe em maior quantidade */

void produto_mais_pedido(int i_prod){
	int i_encomenda, quantidade_max = 0, i;

	if (i_prod > idp){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", i_prod);
		return;
	}
	if (ide == -1)	/* caso nao haja encomendas */
		return;


	for (i = 0; i <= ide; i++)
	{
		if (sistema_encomendas[i].produtos[i_prod] > quantidade_max){
			quantidade_max = sistema_encomendas[i].produtos[i_prod];
			i_encomenda = i;
		}
	}

	if (quantidade_max == 0)
		return;

	printf("Maximo produto %d %d %d.\n", i_prod, i_encomenda, quantidade_max);
}




/* Ordena o sistema --> l. Devolve o sistema ordenado por ordem crescente do peso */

void ordena_sistema(){
	PRODUTO sist_cpy[PRODMAX];
	int i;

	for (i = 0; i <= idp; i++)
		sist_cpy[i] = sistema[i];

	mergesort(sist_cpy, 0, idp);

	
	printf("Produtos\n");
	for (i = 0; i <= idp; i++)
	{
		printf("* %s %d %d\n", sist_cpy[i].descricao, sist_cpy[i].preco, sist_cpy[i].quantidade);
	}
}




/* mergesort --> auxiliar a funcao l. */

void merge(PRODUTO a[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;

	PRODUTO L[PRODMAX], R[PRODMAX];

	for (i = 0; i < n1; i++)
    	L[i] = a[l + i];

	for (j = 0; j < n2; j++)
		R[j] = a[m + 1 + j];


	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].preco <= R[j].preco)
		{
			a[k] = L[i++];
		}
		else
		{
			a[k] = R[j++];
		}
		k++;
	}

	while (i < n1)
	{
		a[k] = L[i++];
		k++;
	}
	while (j < n2)
	{
		a[k] = R[j++];
		k++;
	}
}



void mergesort(PRODUTO arr[], int l, int r){
	if (l < r)
	{
		int m = l+(r-l)/2;
		mergesort(arr, l, m);
		mergesort(arr, m+1, r);

		merge(arr, l, m, r);
	}
}




/* Ordena a encomenda --> L. Imprime os produtos da encomenda ordenados alfabeticamente*/

void ordena_encomenda(int i_encomenda){
	PRODUTO enc_cpy[PRODMAX];
	int i, counter = 0;

	if(i_encomenda > ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", i_encomenda);
		return;
	}

	printf("Encomenda %d\n", i_encomenda);

	for (i = 0; i <= idp; i++)
	{
		if (sistema_encomendas[i_encomenda].produtos[i] != 0){
			enc_cpy[counter] = sistema[i];
			enc_cpy[counter].quantidade = sistema_encomendas[i_encomenda].produtos[i];
			counter += 1;		/* indice da posicao do ultimo elemento */
		}
	}


	mergesort2(enc_cpy, 0, counter-1);


	for (i = 0; i < counter; i++)
	{
		printf("* %s %d %d\n", enc_cpy[i].descricao, enc_cpy[i].preco, enc_cpy[i].quantidade);
	}

}




/* mergesort2 --> auxiliar da funcao L. */

void merge2(PRODUTO a[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;

	PRODUTO L[PRODMAX], R[PRODMAX];

	for (i = 0; i < n1; i++)
    	L[i] = a[l + i];

	for (j = 0; j < n2; j++)
		R[j] = a[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (strcmp(L[i].descricao, R[j].descricao) <= 0)	
		/* strcmp compara as duas strings retorna 0 se forem iguais*/
		
			a[k] = L[i++];
		else
			a[k] = R[j++];

		k++;
	}

	while (i < n1)
	{
		a[k] = L[i++];
		k++;
	}
	while (j < n2)
	{
		a[k] = R[j++];
		k++;
	}
}


void mergesort2(PRODUTO arr[], int l, int r){
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergesort2(arr, l, m);
		mergesort2(arr, m + 1, r);

		merge2(arr, l, m, r);
	}
}


/* Fim do projeto. */
