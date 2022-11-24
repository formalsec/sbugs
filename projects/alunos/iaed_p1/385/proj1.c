#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Numero maximo deprodutos. */
#define PLEN 10000
/* Numero maximo de encomendas. */
#define ELEN 500


typedef struct ProdutoE{
	/* Estrutura dos produtos que estao dentro da encomenda.
	   (z e z1 nao fazem nada, tentei elimina-los mas o 
	   programa nao corria bem os testes, por isso tive de os deixar
	   na estrutura mesmo nao sendo  usados para nada.) */
	int id, quantidade, peso, z,z1;
}ProdutoE;

typedef struct Produto{
	/* Estrutura dos produtos. */
	char descricao[64];
	int preco, peso, quantidade;
}Produto;

typedef struct Encomenda{
	/* Estrutura das encomendas. */
	int peso, quantidade;
	ProdutoE produtos[200];
}Encomenda;



void funcao_a(Produto produtos[], int id){

	/*---------------------------------
	ADICIONA UM NOVO PRODUTO AO SISTEMA
	---------------------------------*/

	scanf(" %[^:]:%d:%d:%d", produtos[id].descricao, &produtos[id].preco, &produtos[id].peso, &produtos[id].quantidade);
	printf("Novo produto %d.\n", id);
}



void funcao_q(Produto produtos[], int id){

	/*----------------------------------------------
	ADICIONA STOCK A UM PRODUTO EXISTENTE NO SISTEMA
	----------------------------------------------*/

	int quantidade = 0, ip = 0;
    scanf(" %d:%d", &ip, &quantidade);

	if (ip >= id)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", ip);
	else
		produtos[ip].quantidade += quantidade;
}

int funcao_A(Produto produtos[], Encomenda encomendas[], int ide, int id){

	/*---------------------------------
	ADICIONA UM PRODUTO A UMA ENCOMENDA
	---------------------------------*/

	int ideP=0, idP=0, quantidade=0, q = 0, i;
	scanf(" %d:%d:%d", &ideP , &idP, &quantidade);
	
	/* Caso a encomenda nao exista. */
	if (ideP >= ide){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idP, ideP);
		return 1;
	}
	/* Caso o produto nao exista. */
	else if (idP >= id){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idP, ideP);
		return 1;
	}
	/* Caso nao haja stock suficiente. */
	else if (quantidade  > produtos[idP].quantidade){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idP, ideP);
		return 1;
	}
	/* Altera peso da encomenda. */
	encomendas[ideP].peso += quantidade * produtos[idP].peso; 
	/* Se peso excede 200 mostra mensagem de erro. */
	if (encomendas[ideP].peso > 200){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idP, ideP);
		encomendas[ideP].peso -= quantidade * produtos[idP].peso;
		return 1;
	}
	else{
		/* q = quantidade de produtos na encomenda. */
		q = encomendas[ideP].quantidade;
		for (i = 0 ; i <= q ; i++){
			/* Se o produto ja existir na encomenda, adiciona ao stock na encomenda
			  e retira ao stock do produto. */
			if ((encomendas[ideP].produtos[i].peso > 0) && (encomendas[ideP].produtos[i].id == idP)){
				encomendas[ideP].produtos[i].quantidade += quantidade;
				produtos[idP].quantidade -= quantidade;
				return 1;
			}
		}
		/* Caso o produto nao exista na encomenda, cria o produto na encomenda. */
		encomendas[ideP].produtos[q].quantidade += quantidade;
		produtos[idP].quantidade -= quantidade;
		encomendas[ideP].produtos[q].id = idP;
		encomendas[ideP].produtos[q].peso = produtos[idP].peso;
		encomendas[ideP].quantidade += 1;
		return 1;
	}
}




int funcao_E(Encomenda encomendas[], Produto produtos[], int ide, int id){

	/*---------------------------------------------------------
	LISTA A DESCRICAO E QUANTIDADE DE UM PRODUTO NUMA ENCOMENDA
	---------------------------------------------------------*/

	int ideP = 0, idP = 0, q = 0, i, ind = 0;	
	scanf(" %d:%d",&ideP , &idP);

	/* Caso a encomenda nao exista.*/
	if (ideP >= ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ideP);
		return 1;
	}
	/* Caso o produto nao exista. */
	else if (idP >= id){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idP);
		return 1;
	}
	else{
		/* Guarda a quantidade de produtos diferentes em q */
		q = encomendas[ideP].quantidade;
		for (i = 0 ; i < q ; i++ ){
			/* Percorre encomendas, se o id da encomenda coincidir com o id desejado faz print. */
			if ((ind = encomendas[ideP].produtos[i].id) == idP){
				printf("%s %d.\n", produtos[ind].descricao, encomendas[ideP].produtos[i].quantidade);
				return 1;
				}		
		}
	/* Faz print de 0 caso o id desejado nao estej na encomenda. */
	printf("%s 0.\n", produtos[idP].descricao);
	return 1;
	}
}



void funcao_r(Produto produtos[],int id){

	/*---------------------------------
	REMOVE STOCK A UM PRODUTO EXISTENTE
	---------------------------------*/

	int idP, quantidade;
	scanf(" %d:%d",&idP , &quantidade);

	/* Caso o produto nao exista. */
	if (idP >= id)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idP);
	/* Caso a quantidade seja superior a quantidade em stock. */
	else if (quantidade > produtos[idP].quantidade)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idP);
	else{
		/* Remove quantidade ao stock. */
		produtos[idP].quantidade -= quantidade;
	}
}



void funcao_R(Encomenda encomendas[], int id,int ide, Produto produtos[]){

	/*--------------------------------
	REMOVE UM PRODUTO DE UMA ENCOMENDA
	--------------------------------*/

	int ideP, idP, i, q = 0;
	scanf(" %d:%d", &ideP, &idP);

	/* Caso a encomenda nao exista. */
	if (ideP >= ide)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idP, ideP);
	/* Caso o produto nao exista. */
	else if (idP >= id)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idP, ideP);
	else{
		/* Guarda quantidade de produtos diferentes em q. */
		q = encomendas[ideP].quantidade;
		for (i = 0 ; i < q ; i++){
			/* Por cada produto na encomenda, se o id coincidir com o id desejado. */
			if (encomendas[ideP].produtos[i].id == idP){
				/* Volta a por a quantidade em stock. */
				produtos[idP].quantidade += encomendas[ideP].produtos[i].quantidade;
				/* Retira o peso da encomenda. */
				encomendas[ideP].peso -= (encomendas[ideP].produtos[i].quantidade * produtos[idP].peso);
				/* Poe a quantidade desse produto na encomenda a 0.*/
				encomendas[ideP].produtos[i].quantidade = 0;
			}
		}
	}
}



void quicksort(int number[],int first,int last){

	/*------------------------------
	ALGORITMO DE ORDENACAO QUICKSORT
	------------------------------*/

	int i, j, pivot, temp;
	if(first<last){
		pivot=first;
		i=first;
		j=last;
		while(i<j){
			while(number[i]<=number[pivot]&&i<last)
				i++;
			while(number[j]>number[pivot])
				j--;
			if(i<j){
				temp=number[i];
				number[i]=number[j];
				number[j]=temp;
			}
		}
		temp=number[pivot];
		number[pivot]=number[j];
		number[j]=temp;
		quicksort(number,first,j-1);
		quicksort(number,j+1,last);
	}
}



int removeDuplicates(int arr[], int n){

	/*-----------------------------------
	REMOVE NUMEROS DUPLICADOS DE UM VETOR
	-----------------------------------*/

	int* temp;
    int j = 0, i;
    temp = (int*)can_fail_malloc(n*sizeof(int));
    /* Se o vetor for vazio ou so com 1 elemento. */
    if (n==0 || n==1) 
        return n; 

    for (i=0; i<n-1; i++){
    	/* Se um elemento for diferente que o proximo, adiciona a temp[]. */
        if (arr[i] != arr[i+1]) 
            temp[j++] = arr[i]; 
  	}
    temp[j++] = arr[n-1]; 
    /* Copia os elementos de volta para a arr[]. */
    for (i=0; i<j; i++){
        arr[i] = temp[i];
    }
    /* Devolve o numero de elementos da lista ja sem repeticoes. */
    return j; 
} 



void funcao_l(Produto produtos[], int id){

	/*------------------------------------------------------------------------
	LISTA TODOS OS PRODUTOS EXISTENTES NO SISTEMA POR ORDEM CRESCENTE DE PRECO
	------------------------------------------------------------------------*/

	int i, i2, s = 0; 
	int* prod; 
	prod = (int*)can_fail_malloc(id * sizeof(int));
	/* Copia o preco de cada produto paa o vetor prod[]. */
	for (i = 0 ; i < id ; i++){
		prod[i] = produtos[i].preco;
	}
	/* Aplica algoritmo quicksort. */ 
	quicksort(prod, 0, id-1);
	/* Remove elementos duplicados de prod[] e guarda em "s" o numero de elementos ja sem duplicados. */
	s = removeDuplicates(prod, id);
	printf("Produtos\n");
	/* Por cada elemento do vetor prod[]. */
	for (i = 0 ; i < s ; i++){
		/* Por cada produto. */
		for (i2 = 0 ; i2 < id ; i2++ ){
			/* Se o preco do produto coincidir com o preco do elemento i do vetor prod[]. */
			if (produtos[i2].preco == prod[i]){
				printf("* %s %d %d\n", produtos[i2].descricao, produtos[i2].preco, produtos[i2].quantidade);
			}
		}
	}
	
}



void swap(char arr[200][64], int i, int l){

	/*-----------------------------------
	FUNCAO AUXILAR - TROCA DOIS ELEMENTOS
	-----------------------------------*/

	char aux[64];
	strcpy(aux, arr[i]), strcpy(arr[i],arr[l]), strcpy(arr[l],aux);
}



void heapify(char arr[200][64], int n, int i) 
{ 
	/*------------------------
	FUNCAO SECUNDARIA HEAPSORT
	------------------------*/

    int largest = i; /* Inicializa largest como raiz. */
    int l = 2*i + 1;
    int r = 2*i + 2;
  
    /* Se a crianca esquerda > raiz. */
    if (l < n && strcmp(arr[l], arr[largest]) > 0) 
        largest = l; 
  
    /* Se a crianca direita > raiz */
    if (r < n && strcmp(arr[r], arr[largest]) > 0) 
        largest = r; 
  
    /* Se largest nao e raiz*/
    if (largest != i) 
    { 
        swap(arr, i, largest); 
  
        /* Recursivamente "heapifica" a sub-arvore. */ 
        heapify(arr, n, largest); 
    } 
} 
  

void heapSort(char arr[200][64], int n){

	/*-----------------------
	FUNCAO PRINCIPAL HEAPSORT
	-----------------------*/

	int i; 
    /* Constroi heap */
    for (i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    /* Extrai um elemnto de cada vez */
    for (i=n-1; i>0; i--) 
    { 
        /* Move raiz para o fim */
        swap(arr, 0, i); 
  
        /* chama heapify no heap ja reduzido */
        heapify(arr, i, 0); 
    } 
} 




int funcao_L(Encomenda encomendas[], int ide, Produto produtos[]){

	/*------------------------------------------------------------------------
	LISTA TODOS OS PRODUTOS DE UMA ENCOMENDA POR ORDEM ALFABETICA DA DESCRICAO
	------------------------------------------------------------------------*/

	int ideP, i, i2, r= 0, c = 0, ind = 0;
	char desc[200][64];
	scanf(" %d", &ideP);	
	/* CAso a encomenda nao exista. */
	if (ideP >= ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ideP);
		return 0;
	}
	/* Guarda a quantidade de produtos diferentes na encomenda em "r". */
	r = encomendas[ideP].quantidade;
	printf("Encomenda %d\n", ideP);
	/* Por cada produto diferente na encomenda. */
	for (i = 0 ; i < r  ; i++){
		/* Caso a quantidade seja > 0. */
		if (encomendas[ideP].produtos[i].quantidade > 0){
			ind = encomendas[ideP].produtos[i].id;
			/* Copia a descricao do produto "ind" para o vetor auxiliar "desc[]". */
			strcpy(desc[c], produtos[ind].descricao);
			c += 1;
		}
	}
	/* Aplica algoritmo heapSort no vetor auxiliar desc[] com "c" elementos. */
	heapSort(desc, c);
	/* Por cada elemento do vetor ordenado des[]. */
	for (i = 0; i < c ; i++){
		/* Por cada produto na encomenda. */
		for (i2 = 0; i2 < r; i2++){
			ind = encomendas[ideP].produtos[i2].id;
			/* Caso a descricao coincida. */
			if (strcmp(produtos[ind].descricao, desc[i]) == 0)
				printf("* %s %d %d\n", desc[i], produtos[ind].preco, encomendas[ideP].produtos[i2].quantidade);
		}
	}
	return 0;
}



void funcao_C(Encomenda encomendas[], int ide, Produto produtos[]){

	/*------------------------------
	CALCULA O CUSTO DE UMA ENCOMENDA
	------------------------------*/

	int ideP, custo = 0, i, n = 0, ind;
	scanf(" %d",&ideP);

	/* Caso a encomenda nao exista. */
	if (ideP >= ide)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ideP);
	else{
		/* Guarda a quantidade de produtos diferentes na encomenda em "n". */
		n = encomendas[ideP].quantidade;
		/* Por cada produto na encomenda. */
		for (i = 0 ; i < n ; i++){
			ind = encomendas[ideP].produtos[i].id;
			/* Adiciona ao custo total da encomenda. */
			custo += (encomendas[ideP].produtos[i].quantidade * produtos[ind].preco);
		}
		printf("Custo da encomenda %d %d.\n", ideP, custo);
	}
}



void funcao_p(Produto produtos[], int id){

	/*-----------------------------------------------
	ALTERA O PRECO DE UM PRODUTO EXISTENTE NO SISTEMA
	-----------------------------------------------*/

	int idP, preco;
	scanf(" %d:%d", &idP, &preco);

	/* Caso o produto nao exista. */
	if (idP >= id)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idP);
	else
		/* Altera o preco do produto. */
		produtos[idP].preco = preco;
}



void funcao_m(Encomenda encomendas[], int id, int ide){

	/*------------------------------------------------------------------------
	LISTA O IDENTIFICADOR DA ENCOMENDA EM QUE O PRODUTO DADO OCORRE MAIS VEZES
	------------------------------------------------------------------------*/

	int i, idP, max = 0, ind, i2,n;
	scanf(" %d", &idP);

	/* Caso o produto nao exista. */
	if (idP >= id)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idP);
	else{
		/* Por cada encomenda */
		for (i = 0 ; i < ide ; i++){
			/* Guarda em "n" a quantidade de produtos diferentes na encomenda de indice "i". */
			n = encomendas[i].quantidade;
			/* Por cada produto na encomenda "i". */
			for (i2 = 0 ; i2 < n ; i2++){
				/* Caso o id seja o pretendido, e quantidade seja maior que max. */
				if (encomendas[i].produtos[i2].id == idP && encomendas[i].produtos[i2].quantidade > max){
					/* Guarda a quantidade maxima. */
					max = encomendas[i].produtos[i2].quantidade;
					/* Guarda o indice da encomenda. */
					ind = i;
				}
			}
		}
		if (max > 0){
			printf("Maximo produto %d %d %d.\n", idP, ind, max);
		}
	}
}



int main(){

	/*------------------------------------------
	RECORRE A TODAS AS OUTRAS FUNCOES AUXILIARES
	E FICA A CORRER ATE SER RPEMIDA A TECLA "X"
	------------------------------------------*/

	char c;
	int id = 0, ide = 0;
	Produto produtos[PLEN];
	Encomenda encomendas[ELEN];

	while (1){
		/* Le tecla premida. */
		scanf(" %c", &c);
		if (c ==  'a'){
			funcao_a(produtos, id);
			/* Aumenta indice do produto. */
			id += 1;
		}

		else if (c ==  'q')
			funcao_q(produtos, id);
		
		else if (c ==  'N'){
			/* Aumenta indice da encomenda. */
			ide++;
			printf("Nova encomenda %d.\n", ide-1);
			/* Inicia as variaveis peso e quantidade a 0. */
			encomendas[ide-1].peso = 0;
			encomendas[ide-1].quantidade = 0;
		}

		else if (c ==  'A')
			funcao_A(produtos, encomendas, ide, id);
		
		else if (c ==  'r')
			funcao_r(produtos, id);
		
		else if (c ==  'R')
			funcao_R(encomendas, id, ide, produtos);

		else if (c ==  'C')
			funcao_C(encomendas, ide, produtos);

		else if (c ==  'p')
			funcao_p(produtos,id);

		else if (c ==  'E')
			funcao_E(encomendas,produtos, ide, id);
			
		else if (c ==  'm')
			funcao_m(encomendas, id, ide);
	
		else if (c ==  'l')
			funcao_l(produtos, id);

		else if (c ==  'L')
			funcao_L(encomendas, ide, produtos);
	
		else if (c ==  'x')
			break;

	}
	return 0;
}