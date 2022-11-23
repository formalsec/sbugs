#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* O numero maximo de caracteres na descricao de um produto. */
#define MAX_PRO_CHAR 63
/* O numero maximo de produtos. */
#define PRODUTOS 10000
/* O numero maximo de encomendas. */
#define ENCOMENDAS 500
/* Termina o programa com sucesso (STDLIB). */
#define EXIT_SUCCESS 0
/* Se chegou aqui algo correu mal (STDLIB). */
#define EXIT_FAILURE -1
/* O numero maximo de unidades de peso. */
#define MAX_ENC_PESO 200

/* Estrutura define um produto. */
typedef struct {
	char descricao[MAX_PRO_CHAR]; /* Descricao do produto. */
	int preco; /* Preco do produto. */
	int peso; /* Peso do produto. */
	int quantidade; /* Quantidade em stock do produto. */
} Produto;

/* Prototipos das Funcoes. */
void novo_produto(int idp);
void adiciona_stock_produto(int numero_de_produtos);
void nova_encomenda(int ide);
int encomenda_peso(int ide, int numero_de_produtos);
void adiciona_produto_a_encomenda(int numero_de_encomendas, int numero_de_produtos);
void remove_stock_produto(int numero_de_produtos);
void remove_produto_encomenda(int numero_de_encomendas, int numero_de_produtos);
void custo_encomenda(int numero_de_encomendas, int numero_de_produtos);
void altera_preco(int numero_de_produtos);
void lista_produto_numa_encomenda(int numero_de_encomendas, int numero_de_produtos);
void maximo_produto_numa_encomenda(int numero_de_encomendas, int numero_de_produtos);

void merge_por_preco(Produto produtos[], int l, int m, int r);
void mergesort_por_preco(Produto produtos[], int l, int r);
void lista_por_preco(int numero_de_produtos);

void exch(Produto produtos[], int i, int j); 
int partition_por_alf(Produto produtos[], int left, int right);
void quicksort_por_alf(Produto produtos[], int left, int right);
void lista_por_alf(int numero_de_encomendas, int numero_de_produtos);

/* Vetor de produtos. */
Produto produtos[PRODUTOS];
/* Matriz de encomendas, linhas sao as encomendas e as colunas sao os produtos. */
int encomendas[ENCOMENDAS][PRODUTOS] = {{0}}; /* Cada entrada representa a quantidade de um produto j na encomenda i. */

/* Le os comandos do utlizador e chama as funcoes responsaveis pelas suas execucoes. */
int main(){

	/* O numero de produtos guardados. */
	int idp = 0;
	/* O numero de encomendas guardadas. */
	int ide = 0;
	
	char comando;

	while(1){

		comando = getchar(); /* Le o comando. */

		switch(comando){
			case 'a':
				novo_produto(idp);
				idp += 1; /* Atualiza o numero de produtos guardados. */
				break;
			case 'q':
				adiciona_stock_produto(idp);
				break;
			case 'N':
				nova_encomenda(ide);
				ide += 1;/* Atualiza o numero de encomendas guardadas. */
				break;
			case 'A':
				adiciona_produto_a_encomenda(ide, idp);
				break;
			case 'r':
				remove_stock_produto(idp);
				break;
			case 'R':
				remove_produto_encomenda(ide, idp);
				break;
			case 'C':
				custo_encomenda(ide, idp);
				break;
			case 'p':
				altera_preco(idp);
				break;
			case 'E':
				lista_produto_numa_encomenda(ide, idp);
				break;
			case 'm':
				maximo_produto_numa_encomenda(ide, idp);
				break;
			case 'l':
				lista_por_preco(idp);
				break;
			case 'L':
				lista_por_alf(ide, idp);
				break;
			case 'x':
				return EXIT_SUCCESS ;
		}

	}

	return EXIT_FAILURE;
}

/* Adiciona um dado produto ao vetor global de produtos. */
void novo_produto(int idp){

	int i;

	scanf("%[^:]:%d:%d:%d", produtos[idp].descricao, &produtos[idp].preco, &produtos[idp].peso, &produtos[idp].quantidade);/******duvida******/

	/* Ajusta a string da descricao do produto por questoes de estetica. */
	for(i = 0; produtos[idp].descricao[i] != '\0'; i++)
		produtos[idp].descricao[i] = produtos[idp].descricao[i + 1];

	printf("Novo produto %d.\n", idp);
}

/* Adiciona uma dada quantidade a um dado produto do vetor global de produtos. */
void adiciona_stock_produto(int numero_de_produtos){

	int idp, quantidade;
	char S;
	scanf("%d%c%d", &idp, &S, &quantidade);

	if (idp >= numero_de_produtos)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	else 
		produtos[idp].quantidade += quantidade;
}

/* Cria uma nova encomenda. */
void nova_encomenda(int ide){

	printf("Nova encomenda %d.\n", ide);
}

/* Calcula peso de uma encomenda da matriz global de encomendas. */
int encomenda_peso(int ide, int numero_de_produtos){

	int idp, peso = 0;
	
	for (idp = 0; idp < numero_de_produtos; idp++)
		peso += encomendas[ide][idp]*produtos[idp].peso;

	return peso;
} 

/* Adiciona uma dada quantidade de um dado produto do vetor de produtos a uma dada encomenda da matriz global de encomendas. */
void adiciona_produto_a_encomenda(int numero_de_encomendas, int numero_de_produtos){

	int ide, idp, quantidade;
	char S;
	scanf("%d%c%d%c%d", &ide, &S, &idp, &S, &quantidade);

	if (ide >= numero_de_encomendas){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	} 

	if (idp >= numero_de_produtos){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	} 

	if (quantidade > produtos[idp].quantidade){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		return;
	} 

	if ((encomenda_peso(ide, numero_de_produtos) + quantidade*produtos[idp].peso) > MAX_ENC_PESO){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
		return;
	} 
	
	encomendas[ide][idp] += quantidade;
	produtos[idp].quantidade -= quantidade;
}

/* Retira uma dada quantidade a um dado produto do vetor global de produtos. */
void remove_stock_produto(int numero_de_produtos){

	int idp, quantidade;
	char S;
	scanf("%d%c%d", &idp, &S, &quantidade);

	if (idp >= numero_de_produtos){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
		return;
	}
	
	if (quantidade > produtos[idp].quantidade){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade ,idp);
		return;
	}
	
	produtos[idp].quantidade -= quantidade;
}

/* Remove toda a quantidade de um dado produto do vetor global de produtos a uma a uma dada encomenda da matriz global de encomendas. */
void remove_produto_encomenda(int numero_de_encomendas, int numero_de_produtos){

	int idp, ide;
	char S;
	scanf("%d%c%d", &ide, &S, &idp);

	if (ide >= numero_de_encomendas){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}
	
	if (idp >= numero_de_produtos){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}

	produtos[idp].quantidade += encomendas[ide][idp];
	encomendas[ide][idp] = 0;
}

/* Calcula o custo de uma dada encomenda da matriz global de encomendas. */
void custo_encomenda(int numero_de_encomendas, int numero_de_produtos){

	int idp, ide, total = 0;
	scanf("%d", &ide);

	if (ide >= numero_de_encomendas){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}

	for (idp = 0; idp < numero_de_produtos; idp++)
		total += encomendas[ide][idp]*produtos[idp].preco;
	
	printf("Custo da encomenda %d %d.\n", ide, total);
}

/* Altera custo de um dado produto do vetor global de produtos. */
void altera_preco(int numero_de_produtos){

	int idp, preco;
	char S;
	scanf("%d%c%d", &idp, &S, &preco);

	if (idp >= numero_de_produtos)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	else
		produtos[idp].preco = preco;
}

/* Lista a decricao e a quantidade de um dado produto do vetor global de produtos numa dada encomenda da matriz global de encomendas. */
void lista_produto_numa_encomenda(int numero_de_encomendas, int numero_de_produtos){

	int idp, ide;
	char S;
	scanf("%d%c%d", &ide, &S, &idp);

	if (ide >= numero_de_encomendas){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}

	if (idp >= numero_de_produtos){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		return;
	}

	printf("%s %d.\n", produtos[idp].descricao, encomendas[ide][idp]);
}

/* Calcula o identificador da encomenda da matriz global de encomendas em que um dado produto do vetor global de produtos ocorre mais vezes. */
void maximo_produto_numa_encomenda(int numero_de_encomendas, int numero_de_produtos){

	int idp;
	scanf("%d", &idp);

	if (idp >= numero_de_produtos){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
		return;
	}
	
	if(numero_de_encomendas > 0){

		int ide, max_ide = 0;

		for (ide = 1; ide < numero_de_encomendas; ide++)
			if (encomendas[ide][idp] > encomendas[max_ide][idp])
				max_ide = ide;

		if (encomendas[max_ide][idp] > 0)
			printf("Maximo produto %d %d %d.\n", idp, max_ide, encomendas[max_ide][idp]);
	}
}

/* "Merge" dois vetores ordenados, L[l...m] e R[m+1...r], de um vetor recebido por ordem crescente de preco. */
void merge_por_preco(Produto produtos[], int l, int m, int r){ 
    
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    Produto L[PRODUTOS], R[PRODUTOS]; 
  
    /* Copia dados para os vetores auxiliares L[] e R[]. */
    for (i = 0; i < n1; i++) 
        L[i] = produtos[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = produtos[m + 1+ j]; 
  
    /* "Merge" os vetores auxiliares de volta para o vetor original. */
    i = 0;
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {

        if (L[i].preco <= R[j].preco){ 
            produtos[k] = L[i]; 
            i++; 
        } else { 
            produtos[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copia os restantes elementos de L[], se houver algum. */
    while (i < n1){ 
        produtos[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copia os restantes elementos de R[], se houver algum. */
    while (j < n2){ 
        produtos[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

/* Ordena o vetor de produtos recebido, do indice l ao indice r, por ordem crescento de preco */
void mergesort_por_preco(Produto produtos[], int l, int r){ 
    
    if (l < r){ 

        int m = l+(r-l)/2; 
  
        mergesort_por_preco(produtos, l, m); 
        mergesort_por_preco(produtos, m+1, r); 
  
        merge_por_preco(produtos, l, m, r); 
    } 
} 

/* lista todos os produtos existentes no vetor global de produtos por ordem crescente de preco. */
void lista_por_preco(int numero_de_produtos){

	Produto produtos_aux[PRODUTOS];
	int i;

	for (i = 0; i < numero_de_produtos; i++)
		produtos_aux[i] = produtos[i];

	mergesort_por_preco(produtos_aux, 0, numero_de_produtos - 1);

	printf("Produtos\n");

	for (i = 0; i < numero_de_produtos; i++)
		printf("* %s %d %d\n", produtos_aux[i].descricao, produtos_aux[i].preco, produtos_aux[i].quantidade);	
}

/* Troca dois dados produtos de indice i e j de um vetor de produtos recebido. */
void exch(Produto produtos[], int i, int j){ 

   	Produto aux = produtos[i]; 
   	produtos[i] = produtos[j]; 
   	produtos[j] = aux; 
} 

/* Particiona o vetor de produtos recebido por ordem alfabetica. */
int partition_por_alf(Produto produtos[], int left, int right){
	
	int i = left - 1, j = right;
	char v[MAX_PRO_CHAR]; /* Pivot. */
	strcpy(v, produtos[right].descricao); 

	while (i < j){

		while (strcmp(produtos[++i].descricao, v) < 0);

		while (strcmp(v, produtos[--j].descricao) < 0)
			if (j == left)
				break;

		if (i < j)
			exch(produtos, i, j);
	}

	exch(produtos, i, right);
	return i;
}

/* Ordena o vetor de produtos recebido, do indice left ao indice right, por ordem alfabetica */
void quicksort_por_alf(Produto produtos[], int left, int right){

	int i;
	
	if (right <= left)
		return;

	i = partition_por_alf(produtos, left, right);
	quicksort_por_alf(produtos, left, i-1);
	quicksort_por_alf(produtos, i+1, right);
}

/* lista todos os produtos do vetor global de produtos de uma dada encomenda da matriz global de encomendas por ordem alfabetica da descricao. */
void lista_por_alf(int numero_de_encomendas, int numero_de_produtos){

	Produto produtos_aux[PRODUTOS]; 
	int ide, i, numero_de_produtos_aux = 0;
	scanf("%d", &ide);

	if (ide >= numero_de_encomendas){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	} 

	for (i = 0; i < numero_de_produtos; i++){

		if (encomendas[ide][i] > 0){
			strcpy(produtos_aux[numero_de_produtos_aux].descricao, produtos[i].descricao);
			produtos_aux[numero_de_produtos_aux].preco = produtos[i].preco;  
			produtos_aux[numero_de_produtos_aux].quantidade =  encomendas[ide][i];
			numero_de_produtos_aux++;
		}	
	}

	quicksort_por_alf(produtos_aux, 0, numero_de_produtos_aux - 1);

	printf("Encomenda %d\n", ide);

	for (i = 0; i < numero_de_produtos_aux; i++)
		printf("* %s %d %d\n", produtos_aux[i].descricao, produtos_aux[i].preco, produtos_aux[i].quantidade);
}

















