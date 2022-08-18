#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Inicializacao de constantes */
#define MAXP 10000 /* Numero maximo de produtos que pode existir */
#define MAXCHAR 64 /* Numero maximo de caracteres para a descricao de cada produto */
#define MAXE 500 /* Numero maximo de encomendas que pode existir */
#define MAXW 200 /* Peso maximo que uma encomenda pode ter */
#define RECMAX 100 /* Numero maximo de caracteres que podemos receber em cada funcao e de produtos da encomenda */
#define INPUT 10 /* Numero maximo de valores e caracteres que o vetor de separacao da string pode suportar */

/* Estrutura criada para os produtos */
struct Product {
	int productIdentifier;
	char productDescription[MAXCHAR];
	int productPrice;
	int productWeight;
	int productStock;
} product;

/* Estrutura criada para as encomendas */
struct Order {
	struct Product prodt[RECMAX];
	int orderWeight;
} order;


/***********Funcoes Auxiliares************/


/* Funcao auxiliar que permite retirar o caracter ':' em qualquer que seja a string recebida */
char* Separate(char received[RECMAX], char new[INPUT][MAXCHAR]){
	char *thing;
	int i = 0;
	
	thing = strtok(received, ":");

	while (thing != NULL) {
  		strcpy(new[i], thing);
  		thing = strtok(NULL, ":"); 		
  		i++;
	}
	return (char*)new;
}

/* Funcao auxiliar que permite calcular o peso de uma encomenda */
int WeightOrder(struct Order warehouse[MAXE], char received[RECMAX]) {
	int i, Weight, totalWeight = 0;
	int orID;
	char new[INPUT][MAXCHAR];

	Separate(received, new); /* Retira o caracter ':' da string recebida */
	orID = atoi(new[0]);

	for (i = 0; i < RECMAX; i++) {
		Weight = warehouse[orID].prodt[i].productWeight * warehouse[orID].prodt[i].productStock;
		totalWeight += Weight;
	}
	return totalWeight;
}

/* Funcao auxiliar que permite fazer a troca de posicoes dentro do algoritmo de ordenacao quicksort */
int Switch(struct Product p1, struct Product p2) {
	struct Product t = p1;

	p1 = p2;
	p2 = t;
	return 0;
}

/* Funcao auxiliar que permite verificar qual o preco menor */
int Smaller(struct Product p1, struct Product p2) {
	if (p1.productPrice == p2.productPrice) {
		return (p1.productIdentifier < p2.productIdentifier);
	}
	else {
		return (p1.productPrice < p2.productPrice);
	}	
	return 0;
}

/* Funcao auxiliar que permite evidentemente realizar o algoritmo de ordenacao quicksort */
int PriceSort(struct Product new[MAXP], int l, int r){
	struct Product x = new[r]; /* Pivot */
	int i = l - 1; 
	int j = r;
		
	while (i < j) { /* Verifica se o numero da direita e maior que o da esquerda */ 
		while (Smaller(new[++i], x));
		while (Smaller(x, new[--j])) {
			if (l == j) {
				break;
			}
		}
		if (i < j) {
			Switch(new[i], new[r]);
		}	
	}
	Switch(new[i], new[r]);		
	return i;
}

/* Funcao auxiliar que permite realizar recursivamente o algoritmo de ordenacao quicksort */
void Sort(struct Product new[MAXP], int l, int r) {
	int i = 0;
	if (r <= l) return;
	i = PriceSort(new,l,r);
	PriceSort(new,l,i-1);
	PriceSort(new,i+1,r);
}


/***********Funcoes Principais************/


/* Esta funcao recebe um conjunto de caracteres com as informacoes referentes a um novo produto e 
permite adiciona-lo ao sistema */
int AddProduct(struct Product shelf[MAXP], int pidentifier, char received[RECMAX]){ 
	char new[INPUT][MAXCHAR];

	Separate(received, new); /* Retira o caracter ':' da string recebida */

	shelf[pidentifier].productIdentifier = pidentifier;
	strcpy(shelf[pidentifier].productDescription, new[0]);
	shelf[pidentifier].productPrice = atoi(new[1]);
	shelf[pidentifier].productWeight = atoi(new[2]);
	shelf[pidentifier].productStock = atoi(new[3]);
	
	printf("Novo produto %d.\n", pidentifier);
	return ++pidentifier; /* Realiza a iteracao de um novo produto no sistema */
}

/* Esta funcao recebe o identificador de um produto e uma determinada quantidade de stock, que adicionara 
ao respetivo produto. Caso nao exista, retorna um erro */ 
void AddStock(struct Product shelf[MAXP], int pidentifier, char received[RECMAX]){
	char new[INPUT][MAXCHAR];
	int pID, sAUX;
	
	Separate(received, new); /* Retira o caracter ':' da string recebida */
	pID = atoi(new[0]);
	sAUX = atoi(new[1]);
	
	if (pID >= pidentifier) {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", pID);			
	} 
	
	shelf[pID].productStock += sAUX;			
}

int NewOrder(int oridentifier) {
	printf("Nova encomenda %d.\n", oridentifier);
	return ++oridentifier; /* Realiza a iteracao de uma nova encomenda no sistema */
}

/* Esta funcao recebe o identificador de uma encomenda e o identificador de um produto, de modo a adicionar
esse produto a encomenda desejada. Caso ambos nao existam, nao haja stock suficiente desse produto ou a
ecomenda contenha excesso de peso, retorna, respetivamente, um erro  */
void OrderAddProd(struct Product shelf[MAXP], struct Order warehouse[MAXE], char received[RECMAX], int pidentifier, int oridentifier) {
	int totalWeight;
	int orID, pID, sAUX;
	char new[INPUT][MAXCHAR];

	Separate(received, new); /* Retira o caracter ':' da string recebida */
	orID = atoi(new[0]);
	pID = atoi(new[1]);
	sAUX = atoi(new[2]);
	
	if (orID >= oridentifier) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", pID, orID);
		return;
	} 
	if (pID >= pidentifier) {
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", pID, orID);
		return;
	}
	if (sAUX > shelf[pID].productStock) {
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", pID, orID);
		return;
	}
	
	warehouse[orID].orderWeight = WeightOrder(warehouse, received); /* Atualiza o preco da encomenda sem o novo produto a adicionar */
	totalWeight = warehouse[orID].orderWeight + (shelf[pID].productWeight * sAUX); /* Calcula o preco com o novo produto */
	
	if (totalWeight > 200) {
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", pID, orID);
		return;
	}
	if (warehouse[orID].prodt[pID].productStock != 0) { /* Verifica se o produto ja existe na encomenda */
		warehouse[orID].prodt[pID].productStock += sAUX;
		warehouse[orID].orderWeight = totalWeight; /* Atualiza o peso da encomenda com o novo proudto adicionado */
		shelf[pID].productStock -= sAUX; /* Remove a quantidade introduzida na encomenda, do sistema de produtos */
		return;
	}
	else {
		warehouse[orID].prodt[pID].productIdentifier = pID;
		strcpy(warehouse[orID].prodt[pID].productDescription, shelf[pID].productDescription);
		warehouse[orID].prodt[pID].productPrice = shelf[pID].productPrice;
		warehouse[orID].prodt[pID].productWeight = shelf[pID].productWeight;
		warehouse[orID].prodt[pID].productStock = sAUX;
		warehouse[orID].orderWeight = totalWeight; /* Atualiza o preco da encomenda com o novo produto adicionado */
	
		shelf[pID].productStock -= sAUX; /* Remove a quantidade do produto introduzida na encomenda, do sistema de produtos */
	}	
}

/* Esta funcao recebe o identificador de um produto e a quantidade de stock que a mesma ira remover desse
produto. Caso o produto nao exista ou nao haja quantidade suficiente, retorna, respetivamente, um erro */
void RemoveStock(struct Product shelf[MAXP], int pidentifier, char received[RECMAX]) {
	char new[INPUT][MAXCHAR];
	int pID, sAUX;

	Separate(received, new); /* Retira o caracter ':' da string recebida */
	pID = atoi(new[0]);
	sAUX = atoi(new[1]);

	if (pID >= pidentifier) {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", pID);
		return;
	}
	if (shelf[pID].productStock - sAUX < 0) {		
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", sAUX, pID);
		return;
	}
	shelf[pID].productStock -= sAUX; /* Remove do sistema de produtos a quantidade introduzida pelo utilizador */
}

/* Esta funcao recebe o identificador de uma encomenda e do produto que pretende remover dessa mesma encomenda.
Caso algum destes nao exista, retorna, respetivamente, um erro */
void RemoveProduct(struct Order warehouse[MAXE], struct Product shelf[MAXP], int oridentifier, int pidentifier, char received[RECMAX]) {
	char new[INPUT][MAXCHAR];
	int pID, orID;

	Separate(received, new); /* Retira o caracter ':' da string recebida */
	orID = atoi(new[0]);
	pID = atoi(new[1]);

	if (orID >= oridentifier) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", pID, orID);
		return;
	}
	if (pID >= pidentifier) {
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", pID, orID);
		return;
	}
	
	warehouse[orID].orderWeight -= warehouse[orID].prodt[pID].productStock * warehouse[orID].prodt[pID].productWeight; /* Atualiza o peso
	da encomenda, sem o produto */

	shelf[pID].productStock += warehouse[orID].prodt[pID].productStock; /* Adiciona a quantidade do produto no sistema do mesmo */
	
	warehouse[orID].prodt[pID].productStock = 0; /* Remove a quantidade do produto (introduzida pelo utilizador) da encomenda */

}

/* Esta funcao recebe o identificador de uma encomenda, da qual pretende calcular o preco. Caso a encomenda nao
exista, retorna um erro */
void OrderPrice(struct Order warehouse[MAXE], int oridentifier, char received[RECMAX]) {
	int orID, e = 0, totalPrice = 0;

	orID = atoi(received);

	if (orID >= oridentifier) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", orID);
		return;
	}
	while (e < RECMAX) { /* Enquanto e nao for maior que a quantidade de produtos existentes na encomenda */
		totalPrice += warehouse[orID].prodt[e].productStock * warehouse[orID].prodt[e].productPrice; /* Calcula o preco */
		e++;
	}

	printf("Custo da encomenda %d %d.\n", orID, totalPrice);
}

/* Esta funcao recebe o identificador de um produto e um novo preco, o qual pretendemos alterar no produto. Caso o
produto nao exista, retorna um erro */
void ChangePrice(struct Product shelf[MAXP], struct Order warehouse[MAXE],int oridentifier, int pidentifier, char received[RECMAX]) {
	char new[INPUT][MAXCHAR];
	int pID, prAUX, i = 0;

	Separate(received, new); /* Retira o caracter ':' da string recebida */
	pID = atoi(new[0]);
	prAUX = atoi(new[1]);

	if (pID >= pidentifier) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", pID);
		return;
	}
	while (i < oridentifier) { /* Permite atualizar o preco do produto dentro das encomendas onde o mesmo existe */
		if (strcmp(warehouse[i].prodt[pID].productDescription,shelf[pID].productDescription) == 0) {
			warehouse[i].prodt[pID].productPrice = prAUX;
		}
		i++;
	}
	
	shelf[pID].productPrice = prAUX; /* Atualiza o preco do produto no sistema */	
}

/* Esta funcao recebe o identificador de uma encomenda e de um produto, e retorna a descricao e a quantidade desse
produto. Caso a encomenda ou o produto nao existam, retorna, respetivamente, um erro */
void ListDescStock(struct Order warehouse[MAXE], struct Product shelf[MAXP], int oridentifier, int pidentifier, char received[RECMAX]) {
	char new[INPUT][MAXCHAR];
	int i, orID, pID, stock = 0;

	Separate(received, new); /* Retira o caracter ':' da string recebida */
	orID = atoi(new[0]);
	pID = atoi(new[1]);

	if (orID >= oridentifier) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", orID);
		return;
	}
	if (pID >= pidentifier) {
		printf("Impossivel listar produto %d. Produto inexistente.\n", pID);
		return;
	}
	for (i = 0; i < RECMAX; i++) { /* Percorre todos os produtos existentes na encomenda */
		if (warehouse[orID].prodt[i].productIdentifier == pID) { /* se idp do produto na encomenda = ao idp recebido do utilizador */
			stock = warehouse[orID].prodt[i].productStock;
			break;
		}
	}	
	printf("%s %d.\n", shelf[pID].productDescription, stock);	
}

/* Esta funcao recebe o identificador de um produto e verifica em que encomenda o produto ocorre mais vezes. Caso
o produto nao exista, retorna um erro */
void ListBiggest(struct Order warehouse[MAXE], int oridentifier, int pidentifier, char received[RECMAX]) {
	int pID, orID = 0, i, e, stock = 0, biggest = 0;

	pID = atoi(received);

	if (pID >= pidentifier) {
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", pID);
		return;
	}
	else {
		for (i = 0; i < oridentifier; i++) { 
			for (e = 0; e < RECMAX; e++) {
				if (warehouse[i].prodt[e].productIdentifier == pID) {
					stock = warehouse[i].prodt[e].productStock;
					if (stock == biggest) { /* Se quantidade do produto iterado for a maior quantidade */
						if (orID > i) { /* Se o ide da encomenda do atual produto com maior quantidade for maior que a iterada */	
							orID = i; /* O ide da encomenda do produto para a ser i */
						}
					} 
					if (stock > biggest) { /* Se quantidade do produto iterado maior que a maior quantidade */
						biggest = warehouse[i].prodt[e].productStock;
						orID = i;
					}
				}
			}				
		}
		
		if (biggest != 0) { /* Se existir produtos na encomenda, ou seja, se a quantidade maior nao for 0 */
			printf("Maximo produto %d %d %d.\n", pID, orID, biggest);
			return;
		}
	}	
}

/* Esta funcao permite ordenar os produtos existentes por ordem crescente de preco. Devolve uma lista de produtos
ordenada de tal forma */
void PriceList(struct Product shelf[MAXP], int pidentifier){
	int i;
	struct Product new[MAXP]; /* Inicializacao do novo vetor de produtos */
	
	printf("Produtos\n");
	
	for (i = 0; i <= pidentifier + 1; i++) { /* Copia todos os produtos do sistema para um novo vetor */
		strcpy(new[i].productDescription, shelf[i].productDescription);
		new[i].productPrice = shelf[i].productPrice;
		new[i].productWeight = shelf[i].productWeight;
		new[i].productStock = shelf[i].productStock;
	}

	PriceSort(new, 0, MAXP + 1); /* Realiza o algoritmo quicksort no vetor criado */

	for (i = 0; i < pidentifier; i++) { /* Imprime todos os produtos do sistema ja organizados por ordem crecente de preco */
		printf("* %s %d %d\n", new[i].productDescription, new[i].productPrice, new[i].productStock);
	}
	return;
}

/* A funcao main, inicializa as estruturas das encomendas e dos produtos. Permite ao utilizador selecionar a 
operacao que permite efetuar no sistema logistico de gestao de stock */
int main(){
	struct Product shelf[MAXP];
	struct Order warehouse[MAXE];
	int run = 1, pidentifier, oridentifier;
	char c, received[RECMAX];

	while (run == 1){ /*Permite que a funcao main e a selecao da operacao estejam sempre ativas, sempre a correr no compilador */
		switch (c = getchar()) { /* Aguarda que o utilizador selecione a operacao */
			case 'a':
				scanf("%s",received);
				pidentifier = AddProduct(shelf, pidentifier, received);
				break;
			case 'q':
				scanf("%s",received);
				AddStock(shelf, pidentifier, received);
				break;
			case 'N':
				oridentifier = NewOrder(oridentifier);
				break;
			case 'A':
				scanf("%s",received);
				OrderAddProd(shelf, warehouse, received, pidentifier, oridentifier);
				break;
			case 'r':
				scanf("%s",received);
				RemoveStock(shelf, pidentifier, received);
				break;
			case 'R':
				scanf("%s",received);
				RemoveProduct(warehouse, shelf, oridentifier, pidentifier, received);
				break;
			case 'C':
				scanf("%s",received);
				OrderPrice(warehouse, oridentifier, received);
				break;
			case 'p':
				scanf("%s",received);
				ChangePrice(shelf, warehouse, oridentifier, pidentifier, received);
				break;
			case 'E':
				scanf("%s",received);
				ListDescStock(warehouse, shelf, oridentifier, pidentifier, received);
				break;
			case 'm':
				scanf("%s",received);
				ListBiggest(warehouse, oridentifier, pidentifier, received);
				break;
			case 'l':
				PriceList(shelf, pidentifier);
				break;
			case 'L':
				exit(1); /* Funcao que nao foi realizada, garante que a mesma termina */
				break;
			case 'x':
				return 0;
				break;
		}
	}
	return 0;
}
