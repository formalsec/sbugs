#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 63
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_PESO 200


typedef struct produto {
	int id;
	char descricao[MAX_STRING];
	int preco;
	int peso;
	int qtd;
} Produto;

typedef struct encomenda {
	Produto lista[MAX_PRODUTOS];	/* Produtos na encomenda */
	int nProds;						/* Numero de produtos na encomenda */
	int id;
	int peso;
} Encomenda;

/*
	Global variables
*/

Produto produtos[MAX_PRODUTOS]; /* Lista de produtos no sistema */

Encomenda encomendas[MAX_ENCOMENDAS]; /* Lista de encomendas no sistema */

int idAtualProd = 0; /* id do proximo produto a colocar */

int idAtualEnc = 0; /* id da proxima encomenda a colocar */

/*
					   ********************
					   *Funcoes auxiliares*
					   ********************
*/

/*	verificaSeExiste
	@return int
	Verifica se um produto esta numa ecomenda e se sim retorna a sua posicao na lista
*/
int verificaSeExiste(int idp, int nProds, Produto lista[MAX_PRODUTOS]) {
	int i;

	for (i = 0; i < nProds; i++) {
		if (idp == lista[i].id) {
			return i;
		}
	}
	return -1;
}

/*	merge
	@return void
	Junta dois sub-arrays de arr[].
	Primeiro sub-array e arr[l..m] e segundo sub-array e arr[m+1..r].
*/
void merge(Produto arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* Cria arrays temporarios */
	Produto L[MAX_PRODUTOS/2], R[MAX_PRODUTOS/2];

	/* Copia dados para arrays temporarios L[] e R[] */
	for (i = 0; i < n1; i++) {
		L[i] = arr[l + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
	}

	i = 0; /* Index inicial do primeiro sub-array */
	j = 0; /* Index inicial do segundo sub-array */
	k = l; /* Index inicial do sub-array formado pela juncao dos dois sub-arrays */

	/* Junta os dois arrays temporarios de volta em arr[l..r] */
	while (i < n1 && j < n2) {
		if (L[i].preco < R[j].preco) {
			arr[k] = L[i];
			i++;
			k++;
			continue;
		}
		else if (L[i].preco > R[j].preco) {
			arr[k] = R[j];
			j++;
			k++;
			continue;
		}
		else {
			if (L[i].id < R[j].id) {
				arr[k] = L[i];
				i++;
			} else {
				arr[k] = R[j];
				j++;
			}
			k++;
		}
	}

	/* Copia os restantes elementos de L[], se sobrarem alguns */
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copia os restantes elementos de R[], se sobrarem alguns */
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

/*	mergeSort
	@return void
	Algoritmo estavel que organiza os produtos com pouco consumo de tempo
*/
void mergeSort(Produto arr[], int l, int r) {
	int m;

	if (l < r) {
		m = l+(r-l)/2;

		/* Organiza primeira e segunda metades */
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);

		merge(arr, l, m, r);
	}
}

/*	executa_a
	@return void
	Adiciona um novo produto ao sistema
*/
void executa_a() {

	produtos[idAtualProd].id = idAtualProd;
	scanf(" %[^:]:%d:%d:%d", produtos[idAtualProd].descricao, &produtos[idAtualProd].preco, &produtos[idAtualProd].peso, &produtos[idAtualProd].qtd);

	printf("Novo produto %d.\n", idAtualProd);

	idAtualProd++;
}

/*	executa_q
	@return void
	Adiciona stock a um produto existente no sistema
*/
void executa_q() {
	int idp, qtd;

	scanf(" %d:%d", &idp, &qtd);

	if (idp >= idAtualProd) {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	} else {
		produtos[idp].qtd += qtd;
	}
}

/*	executa_N()
	@return void
	Cria uma nova encomenda
*/
void executa_N() {

	encomendas[idAtualEnc].id = idAtualEnc;
	encomendas[idAtualEnc].nProds = 0;
	encomendas[idAtualEnc].peso = 0;

	printf("Nova encomenda %d.\n", idAtualEnc);

	idAtualEnc++;
}

/*	executa_A()
	@return void
	Adiciona um produto a uma encomenda. Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente
*/
void executa_A() {
	int ide, idp, qtd, idAux, n;

	scanf(" %d:%d:%d", &ide, &idp, &qtd);

	n = encomendas[ide].nProds;
	idAux = verificaSeExiste(idp, n, encomendas[ide].lista);

	if (ide >= idAtualEnc) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	} else {
		if (idp >= idAtualProd) {
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		} else {
			if ((idAux < 0 && qtd > produtos[idp].qtd) || (idAux >= 0 && qtd > produtos[idp].qtd)) {
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
			} else {
				if ((encomendas[ide].peso + (qtd * produtos[idp].peso)) > MAX_PESO) {
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
				} else {
					if (idAux >= 0) {
						encomendas[ide].lista[idAux].qtd += qtd;
						encomendas[ide].peso += (qtd * produtos[idp].peso);
						produtos[idp].qtd -= qtd;
					} else {
						encomendas[ide].lista[n] = produtos[idp];
						encomendas[ide].lista[n].qtd = qtd;
						encomendas[ide].nProds++;
						encomendas[ide].peso += (qtd * produtos[idp].peso);
						produtos[idp].qtd -= qtd;
					}
				}
			}
		}
	}
}

/*	executa_r
	@return void
	Remove stock a um produto existente no sistema
*/
void executa_r() {
	int idp, qtd;

	scanf(" %d:%d", &idp, &qtd);

	if (idp >= idAtualProd) {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	} else {
		if (qtd > produtos[idp].qtd) {
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
		} else {
			produtos[idp].qtd -= qtd;
		}
	}
}

/*	executa_R
	@return void
	Remove um produto de uma encomenda
*/
void executa_R() {
	int ide, idp, n, idAux, i;

	scanf(" %d:%d", &ide, &idp);

	if (ide >= idAtualEnc) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	} else {
		if (idp >= idAtualProd) {
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		} else {
			n = encomendas[ide].nProds;
			idAux = verificaSeExiste(idp, n, encomendas[ide].lista);
			if (idAux >= 0) {
				encomendas[ide].peso -= (encomendas[ide].lista[idAux].qtd * produtos[idp].peso);
				produtos[idp].qtd += encomendas[ide].lista[idAux].qtd;
				for(i = idAux; i < n; i++) {
					encomendas[ide].lista[i] = encomendas[ide].lista[i+1];
				}
				encomendas[ide].nProds--;
			}
		}
	}
}

/*	executa_C
	@return void
	Calcula o custo de uma encomenda
*/
void executa_C() {
	int ide, n, i, precoProd, total = 0;

	scanf(" %d", &ide);

	if (ide >= idAtualEnc) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	} else {
		n = encomendas[ide].nProds;
		for (i = 0; i < n; i++) {
			precoProd = encomendas[ide].lista[i].preco * encomendas[ide].lista[i].qtd;
			total += precoProd;
		}
		printf("Custo da encomenda %d %d.\n", ide, total);
	}
}

/*	executa_q
	@return void
	Altera o preco de um produto existente no sistema
*/
void executa_p() {
	int idp, preco, i, idAux;

	scanf(" %d:%d", &idp, &preco);

	if (idp >= idAtualProd) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	} else {
		produtos[idp].preco = preco;

		for (i = 0; i < idAtualEnc; i++) {
			idAux = verificaSeExiste(idp, encomendas[i].nProds, encomendas[i].lista);
			if (idAux >= 0) {
				encomendas[i].lista[idAux].preco = preco;
			}
		}
	}
}

/*	executa_E
	@return void
	Lista a descricao e a quantidade de um produto numa encomenda
*/
void executa_E() {
	int ide, idp, n, idAux;

	scanf(" %d:%d", &ide, &idp);

	if (ide >= idAtualEnc) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	} else {
		if (idp >= idAtualProd) {
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		} else {
			n = encomendas[ide].nProds;
			idAux = verificaSeExiste(idp, n, encomendas[ide].lista);
			if (idAux >= 0) {
				printf("%s %d.\n", encomendas[ide].lista[idAux].descricao, encomendas[ide].lista[idAux].qtd);
			} else {
				printf("%s 0.\n", produtos[idp].descricao);
			}
		}
	}
}

/*	executa_m
	@return void
	Lista o identificador da encomenda em que o produto dado ocorre mais vezes
*/
void executa_m() {
	int idp, enc, i, idAux, n, counter = 0, max = 0;

	scanf(" %d", &idp);

	if (idp >= idAtualProd) {
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	} else {
		for (i = 0; i < idAtualEnc; i++) {
			n = encomendas[i].nProds;
			idAux = verificaSeExiste(idp, n, encomendas[i].lista);
			if (idAux >= 0) {
				if (encomendas[i].lista[idAux].qtd > max) {
					max = encomendas[i].lista[idAux].qtd;
					enc = i;
					counter++;
				}
			}
		}
		if (counter > 0) {
			printf("Maximo produto %d %d %d.\n", idp, enc, max);
		}
	}
}

/*	executa_l
	@return void
	Lista todos os produtos existentes no sistema por ordem crescente de preco, usando um algoritmo mergesort
*/
void executa_l() {
	int i;
	Produto produtosOrd[MAX_PRODUTOS];	/* Lista de produtos ordenada*/

	for (i = 0; i < idAtualProd; i++) {
		produtosOrd[i] = produtos[i]; 
	}

	mergeSort(produtosOrd, 0, idAtualProd - 1);

	printf("Produtos\n");
	for (i = 0; i < idAtualProd; i++) {
		printf("* %s %d %d\n", produtosOrd[i].descricao, produtosOrd[i].preco, produtosOrd[i].qtd);
	}
}

/*	executa_L
	@return void
	Lista todos os produtos de uma encomenda por ordem alfabetica da descricao
*/
void executa_L() {
	int ide, n, i, j;
	Produto tmp;
	Produto produtosOrd[MAX_PRODUTOS];

	scanf(" %d", &ide);

	if (ide >= idAtualEnc) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	} else {
		n = encomendas[ide].nProds;

		for (i = 0; i < n; i++) {
			produtosOrd[i] = encomendas[ide].lista[i];
		}

		for (i = 0; i < n; i++) {
			for (j = i+1; j < n; j++) {
				if (strcmp(produtosOrd[i].descricao, produtosOrd[j].descricao) > 0) {
					tmp = produtosOrd[i];
					produtosOrd[i] = produtosOrd[j];
					produtosOrd[j] = tmp;
				}
			}
		}

		printf("Encomenda %d\n", ide);
		for (i = 0; i < n; i++) {
			printf("* %s %d %d\n", produtosOrd[i].descricao, produtosOrd[i].preco, produtosOrd[i].qtd);
		}
	}
}


int main() {
	char c;

	while(1) {
		switch(c = getchar()) {
			case 'a':
				executa_a();	/* Chama a funcao responsavel pela execucao do comando a */
				break;
			case 'q':
				executa_q();	/* Chama a funcao responsavel pela execucao do comando q */
				break;
			case 'N':
				executa_N();	/* Chama a funcao responsavel pela execucao do comando N */
				break;
			case 'A':
				executa_A();	/* Chama a funcao responsavel pela execucao do comando A */
				break;
			case 'r':
				executa_r();	/* Chama a funcao responsavel pela execucao do comando r */
				break;
			case 'R':
				executa_R();	/* Chama a funcao responsavel pela execucao do comando R */
				break;
			case 'C':
				executa_C();	/* Chama a funcao responsavel pela execucao do comando C */
				break;
			case 'p':
				executa_p();	/* Chama a funcao responsavel pela execucao do comando p */
				break;
			case 'E':
				executa_E();	/* Chama a funcao responsavel pela execucao do comando E */
				break;
			case 'm':
				executa_m();	/* Chama a funcao responsavel pela execucao do comando m */
				break;
			case 'l':
				executa_l();	/* Chama a funcao responsavel pela execucao do comando l */
				break;
			case 'L':
				executa_L();	/* Chama a funcao responsavel pela execucao do comando L */
				break;
			case 'x':
				return EXIT_SUCCESS;	/* Termina o programa com sucesso */
			default:
				printf("Erro: Comando desconhecido\n");			
		}
		getchar(); /* le o '\n' introduzido pelo utilizador */
	}
	return EXIT_FAILURE;	/* Termina o programa sem sucesso */
}