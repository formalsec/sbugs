#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>

#define STR 64				/* tamanho maximo da string */
#define ENCOMENDA 500		/* nr max de encomendas */
#define PRODUTO 10000		/* nr max de produtos */
#define PROD_NA_ENCO 200	/* nr max de produtos numa encomenda */



/* tipo produto */
typedef struct {

	int id, preco, peso, qtd;	/* id, preco, peso e quantidade em stock */
	char desc[STR];				/* descri??o do produto */
} TProduto;


/* tipo produto na lista de encomendas (s? usado na encomenda) */
struct ProdEnco {

	int id, qtd;	/* id do produto e quantidade na encomenda*/
};	


/* tipo encomenda */
typedef struct {		

	int N;									/* nr produtos */
	struct ProdEnco prod[PROD_NA_ENCO];		/* lista de produtos */
} TEncomenda;


typedef int Item;


/* variaveis globais */
int N = 0, M = 0;			/* N - nr de produtos, M - nr de encomendas */
Item aux[PRODUTO];			/* vetor auxiliar para o merge sort */
TProduto prod[PRODUTO];		/* lista de produtos (vetor de TProduto) */
TEncomenda enco[ENCOMENDA];	/* lista de encomendas (vetor de TEncomenda) */


/* macros para sorts */
#define key1(A) prod[A].preco
#define key3(A)	prod[enco[key].prod[A].id].desc
#define lessEq1(A, B) key1(A) <= key1(B)
#define lessEq3(A, B) strcmp(key3(A), key3(B)) <= 0
#define POR_PRECO -1
#define lessEq(A, B) ((key == POR_PRECO && lessEq1(A, B)) || \
					  (key >= 0 && lessEq3(A, B)))
					  
/* merge (auxiliar do mergeSort) */
void merge(Item a[], int lo, int mid, int hi, int key) {

	int i = lo, j = mid+1, k;
	
	for(k = lo; k <= hi; k++)	/* copia parte relevante de a[] para aux[] */
		aux[k] = a[k];	
		
	for(k = lo; k <= hi; k++)
		if(i <= mid && (j > hi || lessEq(aux[i], aux[j])))
			a[k] = aux[i++];
		else
			a[k] = aux[j++];
}


/* merge sort */
void mergeSort(Item a[], int lo, int hi, int key) { /* key negativa (por preco) ou natural (por descricao com key = ide) */

	if(hi > lo) {

		int mid = (lo + hi)/2;

		mergeSort(a, lo, mid, key);
		mergeSort(a, mid+1, hi, key);
		merge(a, lo, mid, hi, key);
	}
}


/* indice de um produto na lista de uma encomenda (devolve -1 caso nao exista) */
int indiceProdEnco(int idp, int ide) {
	
	int i;
	
	for(i = 0; i < enco[ide].N; i++)	
		if(enco[ide].prod[i].id == idp)			
			return i;

	return -1;
}


/* adiciona produto ? encomenda */
void adicionaProdEnco(int ide, int idp, int qtd) {
	
	int i = indiceProdEnco(idp, ide);

	if (i >= 0) {
		
		enco[ide].prod[i].qtd += qtd;     /* adiciona ? quantidade existente */
	} else {
		
		i = enco[ide].N;			/* adiciona produto ? lista*/
		enco[ide].prod[i].id = idp;
		enco[ide].prod[i].qtd = qtd;
		enco[ide].N++;
	}
	prod[idp].qtd -= qtd;
}


/* peso de uma encomenda */
int pesoEnco(int ide) {
	
	int i, r = 0;
	
	for(i = 0; i < enco[ide].N; i++)
		r += enco[ide].prod[i].qtd*prod[enco[ide].prod[i].id].peso;	

	return r;
}


/* quantidade de um produto numa encomenda */
int quantProdEnco(int idp, int ide) {

	int i = indiceProdEnco(idp, ide);
	
	if(i >= 0)
		return enco[ide].prod[i].qtd;
	else
		return 0;
}


/* custo de uma encomenda */
int custoEnco(int ide) {

	int i, v = 0;

	for(i = 0; i < enco[ide].N; i++)
		v += enco[ide].prod[i].qtd * prod[enco[ide].prod[i].id].preco;
	
	return v;
}


/* remove produto de uma encomenda */
void removeProdEnco(int ide, int idp) {
					
	int i = indiceProdEnco(idp, ide);
	
	if(i >= 0) {					/* se existir produto na encomenda, remove-o */
						
		prod[idp].qtd += enco[ide].prod[i].qtd;	/* repoe em stock o produto */
		enco[ide].N--;
		for( ; i < enco[ide].N; i++) {
			
			enco[ide].prod[i].id = enco[ide].prod[i+1].id;
			enco[ide].prod[i].qtd = enco[ide].prod[i+1].qtd;
		}				
	}
}


/* encomenda com maior qtd de um produto */
int encomendaMaiorQuantProd(int idp) {
	
	int i, ide = -1, qtd, max = 0;	/* aux variables */
	
	for(i = 0; i < M; i++) {
		
		if((qtd = quantProdEnco(idp, i)) > max) {
							
			ide = i;
			max = qtd;
		}
	}
	return ide;
}


/* adiciona um produto a uma encomenda */
void case_A() {
	
	char str[STR];	/* string auxiliar */
	int idp, ide, qtd;	/* aux variables */
	
	scanf(" %d:%d:%d", &ide, &idp, &qtd);
	sprintf(str, "Impossivel adicionar produto %d a encomenda %d.", idp, ide); 
	if(ide >= M)
					
		printf("%s Encomenda inexistente.\n", str);
	else if(idp >= N)
					
		printf("%s Produto inexistente.\n", str);
	else if(qtd > prod[idp].qtd)
					
		printf("%s Quantidade em stock insuficiente.\n", str);
	else if(pesoEnco(ide) + qtd * prod[idp].peso > 200)
					
		printf("%s Peso da encomenda excede o maximo de 200.\n", str);
	else 
					
		adicionaProdEnco(ide, idp, qtd);
}


/* lista a descri??o e a quantidade de um produto numa encomenda */
void case_E() {

	int idp, ide;	/* aux variables */
	
	scanf(" %d:%d", &ide, &idp);
	if(ide >= M)
					
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if(idp >= N)
					
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	else
					
		printf("%s %d.\n", prod[idp].desc, quantProdEnco(idp, ide));
}


/* adiciona stock a um produto existente no sistema */
void case_q() {
	
	int idp, qtd;	/* aux variables */
	
	scanf(" %d:%d", &idp, &qtd);
	if(idp >= N)
					
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	else
					
		prod[idp].qtd += qtd;
}


/* remove stock a um produto existente */
void case_r() {
	
	int idp, qtd;	/* aux variables */
	
	scanf(" %d:%d", &idp, &qtd);
	if(idp >= N)
					
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	else if(qtd > prod[idp].qtd)
					
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	else
					
		prod[idp].qtd -= qtd;
}


/* remove um produto de uma encomenda */
void case_R() {

	int idp, ide;	/* aux variables */

	scanf(" %d:%d", &ide, &idp);
	if(ide >= M)
					
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if(idp >= N)
					
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else

		removeProdEnco(ide, idp);
}


/* calcula o custo de uma encomenda */
void case_C() {

	int ide;	/* aux variables */
	
	scanf(" %d", &ide);
	if(ide >= M)
					
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	else
					
		printf("Custo da encomenda %d %d.\n",
				ide, custoEnco(ide));
}


/* altera o pre?o de um produto existente no sistema */
void case_p() {

	int idp, preco;	/* aux variables */
	
	scanf(" %d:%d", &idp, &preco);
	if(idp >= N)
					
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	else
					
		prod[idp].preco = preco;
}


/* lista o ide em que o produto dado ocorre mais vezes */
void case_m() {

	int idp;	/* aux variables */
	
	scanf(" %d", &idp);
	if(idp >= N)
					
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	else {
					
		int ide = encomendaMaiorQuantProd(idp);	/* aux variables */
		if(ide >= 0)						/* se existir mostra qual */
			printf("Maximo produto %d %d %d.\n",
					idp, ide, quantProdEnco(idp, ide));
	}		
}


/* imprime lista de produtos */
void imprimeProd(Item ord[]) {	/* ord[] - ordem dos id's */

	int i;
	
	printf("Produtos\n");
	for(i = 0; i < N; i++)  {
					
		printf("* %s %d %d\n", prod[ord[i]].desc,
							   prod[ord[i]].preco,
							   prod[ord[i]].qtd);
	}
}


/* imprime produtos na encomenda */
void imprimeEnco(int ide, Item ord[]) {	/* ord[] - ordem dos indices */

	int i;
	
	printf("Encomenda %d\n", ide);
	for(i = 0; i < enco[ide].N; i++)
		printf("* %s %d %d\n", prod[enco[ide].prod[ord[i]].id].desc,
							   prod[enco[ide].prod[ord[i]].id].preco,
							   enco[ide].prod[ord[i]].qtd);	
}


/* preenche naturais num vetor de dimensao n */
void naturais(Item a[], int n) {

	while(--n >= 0)
		a[n] = n;	
}


/* lista todos os produtos por ordem crescente de pre?o */
void case_l() {
	
	Item ord[PRODUTO];	/* ord - vetor com a ordem dos id's */

	naturais(ord, N);			/* ord[] tem a ordem inicial (id's crescentes) */
	mergeSort(ord, 0, N-1, POR_PRECO);	/* a lista ja esta ordenada por id. Ordena por preco */
	imprimeProd(ord);	/* imprime pela ordem dos id's do ord (por preco)*/
}


/* lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void case_L() {
				
	int ide;
	Item ord[PROD_NA_ENCO];	/* ord - vetor com a ordem dos indices */

	scanf(" %d", &ide);
	if(ide >= M)
					
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else {
					
		naturais(ord, enco[ide].N);			/* ord[] tem a ordem inicial (indices crescentes) */
		mergeSort(ord, 0, enco[ide].N-1, ide);	/* a lista ja esta ordenada por indices. Ordena por desc */
		imprimeEnco(ide, ord);
	}
}


/* lista produtos na ordem atual */
void case_k() {

	Item ord[PRODUTO];
	
	naturais(ord, N);
	imprimeProd(ord);
}


/* lista produtos na encomenda na ordem atual */
void case_K() {

	int ide;
	Item ord[PROD_NA_ENCO];
	
	scanf(" %d", &ide);
	naturais(ord, enco[ide].N);
	imprimeEnco(ide, ord);
}


/* main: le e executa comandos de gestao de stock */
int main() {

	char c;	/* c - caracter de commando lido */

	while((c = getchar()) != 'x') {	/* cicla enquanto nao for o comando x */
	
		switch(c) {
			
			case 'a':	/* adiciona um novo produto ao sistema */
			
				scanf(" %[^:]:%d:%d:%d", prod[N].desc,	/* le e acrescenta no final da lista */
					  &prod[N].preco, &prod[N].peso, &prod[N].qtd);
				prod[N].id = N;
				printf("Novo produto %d.\n", N);
				N++;
				break;
				
			case 'N':	/* cria uma nova encomenda */
			
				printf("Nova encomenda %d.\n", M);	/* acrescenta no final da lista */
				enco[M].N = 0;	/* inicialmente nao tem produtos */
				M++;
				break;
				
			case 'A':	/* adiciona um produto a uma encomenda */
			
				case_A();
				break;

			case 'E':	/* lista a descri??o e a quantidade de um produto numa encomenda */
			
				case_E();
				break;

			case 'q':	/* adiciona stock a um produto existente no sistema */
				
				case_q();
				break;
			
			case 'r':	/* remove stock a um produto existente */
				
				case_r();
				break;
			
			case 'R':	/* remove um produto de uma encomenda */
				
				case_R();
				break;
			
			case 'C':	/* calcula o custo de uma encomenda */
				
				case_C();
				break;
			
			case 'p':	/* altera o pre?o de um produto existente no sistema */
				
				case_p();
				break;
			
			case 'm':	/* lista o ide em que o produto dado ocorre mais vezes */
				
				case_m();
				break;
			
			case 'l':	/* lista todos os produtos por ordem crescente de pre?o */
				
				case_l();
				break;
			
			case 'L':	/* lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
				
				case_L();
				break;

			case 'k':	/* lista produtos na ordem atual */
				
				case_k();
				break;
			
			case 'K':	/* lista produtos na encomenda na ordem atual */
				
				case_K();
				break;
			
			default:
			
				printf("KO\n");	/* temporario para debug */
		}
		scanf("\n");
		
	}
	return 0;
}