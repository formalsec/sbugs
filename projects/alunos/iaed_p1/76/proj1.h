#include <stdio.h>
#include <string.h>

/*Nos ciclos for que percorrem os produtos das encomendas, para quando atingir MAX_PRODUTOS porque nao ha produtos para
alem desse ponto, pois foram inicializados a 10000*/
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define PRODUTOS_EM_ENC 200
#define MAX_PESO 200
#define TAMANHO_DES 64

/*Um produto contem uma string com maximo de 63 caracteres que corresponde a descricao do produtos e 4 inteiros,
um "preco" que contem o preco do produto, um "peso" que contem o peso do produto, um "qtd" que contem a quantidade
existente desse produto em stock e um "state que contem a existencia do produto(0=nao existe; 1=existe)*/
typedef struct produto {
    int preco, peso, qtd, state;
    char des[TAMANHO_DES];
}produto;

/*Uma encomenda tem um vetor de produtos de tamanho 10000 com a quantidade de produto com o idp = indice em cada indice,
um vetor de tamanho 200 com os produtos que contem ordenados e 3 inteiros, um "state" que contem a existencia da encomenda
(0=nao existe; 1=existe), um "peso" que contem o peso atual da encomenda e um "n_prod" que guarda o numero de produtos
atualmente na encomenda*/
typedef struct encomenda {
    char state;
    int peso, n_prod;
    int produtos[MAX_PRODUTOS];
    int prod_ord[PRODUTOS_EM_ENC];
}encomenda;

int qtd_na_encomenda(int ide, int idp);
int produto_existe(int idp);
int encomenda_existe(int ide);
int qtd_prod(int idp);
int peso_prod(int idp);
int preco_prod(int idp);
void altera_quantidade(int idp, int qtd);
void remove_prod_ord(int ide, int idp);
void cria_produto();
void adiciona_stock();
void cria_encomenda();
void adiciona_produto();
void remove_stock();
void remove_produto();
void calcula_custo();
void altera_preco();
void descricao_produto();
void encomenda_maior();
void lista_produtos();
void lista_produtos_encomenda();
void insertion_sort(int arr[], int n);
void mergesort(int arr[], int esq, int drt);
void merge(int arr[], int esq, int m, int drt);