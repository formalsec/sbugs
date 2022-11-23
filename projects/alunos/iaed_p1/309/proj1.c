#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_DESC 64
#define MAX_PESO_ENCOM 200	/* se cada produto pesa no min 1, entao o num
			 				max de produtos numa encomenda e
			 				 200 produtos tambem */

# define less_preco(A, B) A.preco < B.preco
# define exch(A, B) { produto t = A; A = B; B = t; }


typedef struct produto {
	int idp;	/* identificador unico no intrevalo [0, 9999] */
	char desc[MAX_DESC];
	int preco;
	int peso;
	int quantidade;
} produto;

/* registo do inventario/sistema */
produto stock[MAX_PRODUTOS];

/* registo do proximo idp a ser criado */
int prox_idp;


/* definicao do tipo de produto usado para registar quais estao nas encomendas */
typedef struct produto_na_encomenda {
	int idp;		     /* o peso e o preco nao sao necessarios guardar */
	char desc[MAX_DESC]; /* na encomenda, pois os seus valores estao     */
	int quantidade;		 /* atualizados no stock, acessiveis pelo idp    */
} produto_na_encomenda;  


typedef struct encomenda {
	produto_na_encomenda registo_prod[MAX_PESO_ENCOM]; 
	int peso;
} encomenda;

/* registo das encomendas */
encomenda registo_encom[MAX_ENCOMENDAS];

/* registo do proximo ide a ser criado */
int prox_ide;


/*		PROTOTIPOS		*/
void adiciona_produto();
void adiciona_stock();
void cria_nova_encomenda();
void adiciona_produto_a_encomenda();
void remove_stock();
void remove_produto_encomenda();
void calcula_custo();
void altera_preco_produto();
void lista_descr_qtd_prod();
void lista_encomenda_maior_qtd_prod();
void lista_produtos_stock();
void lista_produtos_encomenda();

/*		FUNCOES AUXILIARES		*/
void mergesort(produto aux[], produto a[], int left, int right);
void merge(produto aux[], produto a[], int left, int m, int right);
void quicksort(produto a[], int left, int right);
int partition(produto a[], int left, int right);
int less_desc (produto a, produto b);


/*		FUNCAO INICIAL		*/
int main() {
	while (1) {
		char cmd;
		cmd = getchar();
		switch(cmd) {
			case 'a':
				adiciona_produto();
				break;
			case 'q':
				adiciona_stock();
				break;
			case 'N':
				cria_nova_encomenda();
				break;
			case 'A':
				adiciona_produto_a_encomenda();
				break;
			case 'r':
				remove_stock();
				break;
			case 'R':
				remove_produto_encomenda();
				break;
			case 'C':
				calcula_custo();
				break;
			case 'p':
				altera_preco_produto();
				break;
			case 'E':
				lista_descr_qtd_prod();
				break;
			case 'm':
				lista_encomenda_maior_qtd_prod();
				break;
			case 'l':
				lista_produtos_stock();
				break;
			case 'L':
				lista_produtos_encomenda();
				break;
			case 'x':
				return 0;	/* Termina o programa (sem erros) */	
			default:
				printf("Comando desconhecido\n");
		}
		getchar();	/* Retira o '\n' do stdin */
	}
	return -1;	/* Se chegou ate aqui, algo correu mal */
}


/*		FUNCOES PRINCIPAIS		*/

/* adiciona um novo produto ao sistema */
/*input: descricao:preco:peso:quantidade */
/*outup: Novo produto <idp>. */
void adiciona_produto() {
	stock[prox_idp].idp = prox_idp;
	scanf(" %63[^:]:%d:%d:%d", stock[prox_idp].desc, &stock[prox_idp].preco, 
						&stock[prox_idp].peso, &stock[prox_idp].quantidade);
	printf("Novo produto %d.\n", prox_idp);
	prox_idp++;
}


/* adiciona stock a um produto existente no sistema */
/* input: idp:quantidade */
/* erros: 1: se o produto inserido nao existir no sistema */
void adiciona_stock() {
	int idp, qtd;
	scanf(" %d:%d", &idp, &qtd);
	if (idp >= prox_idp) {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	}
	else {
		stock[idp].quantidade += qtd;
	}
}


/* cria uma nova encomenda */
/* output: Nova encomenda <ide>. */
void cria_nova_encomenda() {
	printf("Nova encomenda %d.\n", prox_ide);
	prox_ide++;
}


/* adiciona um produto a uma encomenda (se ja nao existir), 
caso contrario atualiza a sua quantidade (na encomenda) */
/* input: ide:idp:quantidade */
/* erros: 1: se a encomenda inserida nao existir;
		  2: se o produto inserido nao existir no sistema;
		  3: se nao existir stock suficiente desse produto para satisfazer a encomenda;
		  4: se a adicao do produto resulta numa encomenda com peso superior ao maximo permitido */
void adiciona_produto_a_encomenda() {
	int ide, idp, qtd, pos_prod = 0;
	scanf(" %d:%d:%d", &ide, &idp, &qtd);
	if (ide >= prox_ide) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	else if (idp >= prox_idp) {
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else if (stock[idp].quantidade < qtd) {
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	}
	else if ((registo_encom[ide].peso + (qtd * stock[idp].peso)) > MAX_PESO_ENCOM) {
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	}
	else {
		while (pos_prod < MAX_PESO_ENCOM && registo_encom[ide].registo_prod[pos_prod].desc[0] != '\0' 
				/*uma descricao vazia indica um espaco livre para um produto */
				&& registo_encom[ide].registo_prod[pos_prod].idp != idp) {
			pos_prod++;	
			/* Procura "espaco vazio" na encomenda para adicionar produto, caso nao o "encontre" primeiro */
		}	
		if (registo_encom[ide].registo_prod[pos_prod].idp != idp 
				|| registo_encom[ide].registo_prod[pos_prod].desc[0] == '\0') {	
				/* o produto nao esta na encomenda, e nao entra em conflito se o idp0 nao estiver na encomenda */
			registo_encom[ide].registo_prod[pos_prod].idp = idp;
			strcpy(registo_encom[ide].registo_prod[pos_prod].desc, stock[idp].desc);
		}
		stock[idp].quantidade -= qtd;
		registo_encom[ide].registo_prod[pos_prod].quantidade += qtd;
		registo_encom[ide].peso += qtd * stock[idp].peso; 
	}
}


/* remove stock a um produto existente no sistema */
/* input: idp:qtd */
/* erros: 1: se o produto inserido nao existir no sistema;
		  2:se a remocao do produto resulta numa quantidade em stock negativa */
void remove_stock() {
	int idp, qtd;
	scanf(" %d:%d", &idp, &qtd);
	if (idp >= prox_idp) {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	}
	else if (stock[idp].quantidade < qtd) {
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	}
	else {
		stock[idp].quantidade -= qtd;
	}
}


/* remove um produto de uma encomenda; se o produto nao existir 
na encomenda, nao ha alteracoes no sistema */
/* input: idp:quantidade */
/* erros: 1: se a encomenda inserida nao existir;
		  2: se o produto inserido nao existir no sistema */
void remove_produto_encomenda() {
	int ide, idp, pos_prod = 0;
	scanf(" %d:%d", &ide, &idp);
	if (ide >= prox_ide) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	else if (idp >= prox_idp) {
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else {
		while (pos_prod < MAX_PESO_ENCOM && registo_encom[ide].registo_prod[pos_prod].idp != idp) {
				pos_prod++;	/* procura a posicao do produto idp na encomenda*/
		}
		if (pos_prod == MAX_PESO_ENCOM) {
			return;	/* se isto se verificar, chegou ao final do regi_prod sem ter encontrado o produto, 
					   ou seja, nao esta na encomenda e nao ha alteracoes no sistema */
		}
		stock[idp].quantidade += registo_encom[ide].registo_prod[pos_prod].quantidade;
		registo_encom[ide].peso -= stock[idp].peso * registo_encom[ide].registo_prod[pos_prod].quantidade;
		while (pos_prod < MAX_PESO_ENCOM-1 /* o "limite-1" impede stack overflow */
				&& registo_encom[ide].registo_prod[pos_prod].desc[0] != '\0') { 
				/* descricao vazia significa que nao ha mais produtos na encomenda */
			registo_encom[ide].registo_prod[pos_prod] = registo_encom[ide].registo_prod[pos_prod+1]; 
			/* permite o funcionamento do comando "A", pois impede que detete idp0, quando este nao esta na encomenda */
			pos_prod++;
		}
		registo_encom[ide].registo_prod[pos_prod].idp = 0;
		registo_encom[ide].registo_prod[pos_prod].desc[0] = '\0';
		registo_encom[ide].registo_prod[pos_prod].quantidade = 0;
	}
}


/* calcula o custo de uma encomenda */
/* input: ide */
/* output: Custo da encomenda <ide> <total>. */
/* erros: 1: se a encomenda inserida nao existir */
void calcula_custo() {
	int ide;
	scanf(" %d", &ide);
	if (ide >= prox_ide) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	}
	else {
		int pos_prod, custo = 0;
		for (pos_prod = 0; 
				pos_prod < MAX_PESO_ENCOM && registo_encom[ide].registo_prod[pos_prod].desc[0] != '\0'; 
				pos_prod++) { /* se encontrar uma descricao vazia, nao ha mais produtos para contabilizar (otimizacao do ciclo) */
			
			custo += (stock[registo_encom[ide].registo_prod[pos_prod].idp].preco 
					   * registo_encom[ide].registo_prod[pos_prod].quantidade);
		}
		printf("Custo da encomenda %d %d.\n", ide, custo);
	}
}


/* altera o preco de um produto existente no sistema */
/* input: idp:preco */
/* erros: 1: se o produto inserido nao existir no sistema */
void altera_preco_produto() {
	int idp, preco;
	scanf(" %d:%d", &idp, &preco);
	if (idp >= prox_idp) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	}
	else {
		stock[idp].preco = preco;
	}
}


/* lista a descricao e a quantidade de um produto numa encomenda */
/* input: ide:idp */
/* output: <desc> <qtd na encomenda>. */
/* erros: 1: se a encomenda inserida nao existir;
		  2: se o produto inserido nao existir no sistema */
void lista_descr_qtd_prod() {
	int ide, idp, pos_prod = 0, qtd;
	scanf(" %d:%d", &ide, &idp);
	if (ide >= prox_ide) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else if (idp >= prox_idp){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	else {
		while (pos_prod < MAX_PESO_ENCOM && registo_encom[ide].registo_prod[pos_prod].desc[0] != '\0' 
				&& registo_encom[ide].registo_prod[pos_prod].idp != idp) {
			pos_prod++;	/* '\0': o produto nao esta na encomenda e qtd = 0 (otimiza); "!= idp": encontrou a posicao do produto na encomenda */
		}
		qtd = (pos_prod == MAX_PESO_ENCOM	/* acerto no caso de encomenda cheia, pois o produto nao vai estar la */
				|| registo_encom[ide].registo_prod[pos_prod].idp != idp) ? /* deteta o caso de quebra do ciclo while, */
					0 : registo_encom[ide].registo_prod[pos_prod].quantidade; /* e atribui valor correspondente */
		printf("%s %d.\n", stock[idp].desc, qtd);
	}
}


/* lista o ide em que o produto dado ocorre mais vezes;
se houver 2 ou mais encomendas nessa situacao, imprime 
a encomenda de menor id; nao lista nada se o produto 
nao ocorre em nenhuma encomenda, ou caso nao haja encomendas */
/* input: idp */
/* output: Maximo produto <idp> <ide> <qtd de idp em ide>. */
/* erros: 1: se o produto inserido nao existir no sistema */
void lista_encomenda_maior_qtd_prod() {
	int idp, contador_prod = 0, pos_encom, pos_prod, ide, max_na_encom = 0;
	scanf(" %d", &idp);
	if (idp >= prox_idp){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	}
	else if (prox_ide == 0) {	
		return;
	}
	else {
		for (pos_encom = 0; pos_encom < prox_ide; pos_encom++) {
			for (pos_prod = 0; pos_prod < MAX_PESO_ENCOM 
					&& registo_encom[pos_encom].registo_prod[pos_prod].desc[0] != '\0'; pos_prod++) {
					/* '\0': nao ha mais produtos na encomenda (otimiza e previne de contar varias vezes o idp0, caso esteja na encomenda) */
				if (registo_encom[pos_encom].registo_prod[pos_prod].idp == idp) {
					contador_prod = registo_encom[pos_encom].registo_prod[pos_prod].quantidade;
				}
			}
			if (contador_prod > max_na_encom) {
				ide = pos_encom;
				max_na_encom = contador_prod;
			}
			contador_prod = 0;
		}
		if (max_na_encom == 0) {
			return;
		}
		else {
			printf("Maximo produto %d %d %d.\n", idp, ide, max_na_encom);
		}
	}
}


/* lista todos os produtos existentes no sistema por ordem crescente de preco;
se houver 2 ou mais produtos com o mesmo preco, imprime estes por ordem crescente de idp  */
/* output: produtos listados por ordem crescente de preco:
"* <desc> <preco> <quantidade em stock>" */
void lista_produtos_stock() {
	int i;
	produto temp[MAX_PRODUTOS];	/* vetor a ser ordenado, impede que altere a ordenacao pelos idp's 
								   do stock, da qual dependem outros comandos (exemplo:"A") */
	produto aux[MAX_PRODUTOS];
	for (i = 0; i < prox_idp; i++) { 
		temp[i].idp = stock[i].idp;
		temp[i].preco = stock[i].preco;
	}
	mergesort(aux, temp, 0, prox_idp-1);	/* nao existe no sistema o produto com idp = prox_idp */
	printf("Produtos\n");
	for (i = 0; i < prox_idp; i++) {
		printf("* %s %d %d\n", stock[temp[i].idp].desc, temp[i].preco, stock[temp[i].idp].quantidade);
	}
}

/* ordena um vetor usando o merge sort; parte o vetor
dado ate se obter vetores de apenas um elemento */
void mergesort(produto aux[], produto a[], int left, int right) {
	int m = (right+left)/2;
	if (right <= left) {
		return;
	}
	mergesort(aux, a, left, m);
	mergesort(aux, a, m+1, right);
	merge(aux, a, left, m, right);
}

/* procedimento de merge, gera um vetor ordenado 
a partir de dois vetores ordenados */
void merge(produto aux[], produto a[], int left, int m, int right) {
	int i, j, k;
	for (i = m+1; i > left; i--) {
		aux[i-1] = a[i-1];
	}
	for (j = m; j < right; j++) {
		aux[right+m-j] = a[j+1];
	}
	for (k = left; k <= right; k++) {
		if (less_preco(aux[j], aux[i]) || i > m) {
			a[k] = aux[j--];
		}
		else {
			a[k] = aux[i++];
		}
	}
}


/* lista todos os produtos de uma encomenda 
por ordem alfabetica da descricao */
/* input: ide */
/* output: produtos listados por ordem alfabetica de descricao:
"* <desc> <preco> <quantidade na ide>" */
/* erros: 1: se a encomenda inserida nao existir */
void lista_produtos_encomenda() {
	int ide;
	produto temp[MAX_PESO_ENCOM];
	scanf(" %d", &ide);
	if (ide >= prox_ide) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else {
		int i, num_prod_encom = 0;
		for (i = 0; registo_encom[ide].registo_prod[i].desc[0] != '\0'; i++) {
			temp[i].idp = registo_encom[ide].registo_prod[i].idp;
			strcpy(temp[i].desc, registo_encom[ide].registo_prod[i].desc);
			temp[i].quantidade = registo_encom[ide].registo_prod[i].quantidade;
			num_prod_encom++;
		}	/* se existem n produtos na encomeda, entao o indice/posicao desse produto e n-1, prq os ids comecam no zero */
		quicksort(temp, 0, num_prod_encom-1);
		printf("Encomenda %d\n", ide);
		for (i = 0; registo_encom[ide].registo_prod[i].desc[0] != '\0'; i++) {
			printf("* %s %d %d\n", temp[i].desc, stock[temp[i].idp].preco, temp[i].quantidade);
		}
	}
}

/* ordena um vetor usando o quick sort */
void quicksort(produto a[], int left, int right) {
	int i;
	if (right <= left) {
		return;
	}

	i = partition(a, left, right);
	quicksort(a, left, i-1);
	quicksort(a, i+1, right);
}

/* parte o vetor dado em duas partes: um contendo os 
valores menores que o pivot, e outro os maiores;
devolve o indice do proximo pivot*/
int partition(produto a[], int left, int right) {
	int i = left-1;
	int j = right;
	produto pivot = a[right];
	while(i < j) {
		while (less_desc(a[++i], pivot));
		while (less_desc(pivot, a[--j])) {
			if (j == left) {
				break;
			}
		}
		if (i < j) {
			exch(a[i], a[j]);
		}
	}
	exch(a[i], a[right]);
	return i;
}

/* funcao auxiliar; devolve 1 se a decricao do 1o produto 
e "alfabeticamente menor" que a do 2o produto, senao devolve 0 */
int less_desc (produto a, produto b) {
	return (strcmp(a.desc, b.desc) < 0) ? 1 : 0;
}
