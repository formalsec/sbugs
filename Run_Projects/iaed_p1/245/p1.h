#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDES 64            
#define MAXPROD 10000
#define MAXENC 500
#define MAXARG 100 
/**
 * Cria uma estrutura Produto
 */
typedef struct produto{   
	char descricao[MAXDES];              /* descricao do produto */
	int preco;                           /* preco do produto */
	int peso;                            /* peso do produto */
	int stock;                           /* stock do produto */
    int flag;                            /* flag p ver se o produto existe */
}Produto;
/**
 * Cria uma estrutura Encomenda
 */
typedef struct encomenda{
	int peso;                            /* peso total da encomenda */
	int contaProdEnc;                    /* contador de produtos na encomenda */
	int quantidade[MAXPROD];             /* vetor que guarda a quantidade dos produtos na encomenda */
	int flag;                            /* flag p ver se a encomenda existe */
	Produto produtosEncomendas[MAXPROD]; /* vetor de produtos na encomenda */
}Encomenda;

Produto produtos[MAXPROD];               /* vetor com todos os produtos no sistema */
Encomenda encomendas[MAXENC];            /* vetor com todas as encomendas no sistema */

int contaProdutos = 0;                   /* contador de produtos no sistema */
int contaEncomendas = 0;                 /* contador de encomendas no sistema */

/* Funcoes */
/**
 * Adiciona um novo produto no sistema
 * @param char arg[] - especifica??es do produto que queremos adicionar.
 */
void comando_a(char arg[]); 

/**
 * Adiciona stock a um produto existente no sistema
 * @param char arg[] - id do produto e quantidade a adicionar.
 */
int comando_q(char arg[]);

/**
 * Adiciona uma encomenda ao sistema.
 */
void comando_N();

/**
 * Adiciona um produto a uma encomenda
 * @param char arg[] - id da encomenda, id do produto e quantidade a adicionar.
 */
int comando_A(char arg[]);

/**
 * Remove stock a um produto existente
 * @param char arg[] - id do produto e quantidade a remover.
 */
int comando_r(char arg[]); 

/**
 * Remove um produto de uma encomenda
 * @param char arg[] - id da encomenda e id do produto a remover.
 */
int comando_R(char arg[]); 

/**
 * Calcula o custo de uma encomenda
 * @param char arg[] - id da encomenda.
 */
int comando_C(char arg[]); 

/**
 * Altera o pre?o de um produto existente no sistema
 * @param char arg[] - id do produto e preco novo.
 */
int comando_p(char arg[]);

/**
 * Lista a descri??o e a quantidade de um produto numa encomenda
 * @param char arg[] - id da encomenda e id do produto.
 */
int comando_E(char arg[]);

/**
 * Lista o identificador da encomenda em que o produto dado ocorre mais vezes
 * @param char arg[] - id do produto.
 */
int comando_m(char arg[]);

/**
 * Lista todos os produtos existentes no sistema por ordem crescente de pre?o
 */
void comando_l(); 

/**
 * Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o
 * @param char arg[] - id da encomenda.
 */
int comando_L(char arg[]);

/**
 * Funcao auxiliar, juntamente com a funcao mergeSort, para a ordenacao da funcao l e L
 * @param Produto a[] - lista de produtos a ordenar.
 * @param int i1
 * @param int j1
 * @param int i2
 * @param int j2
 * @param int f - identificador da funcao l (f=1) ou da funcao L (f=2)
 */
void merge(Produto a[],int i1,int j1,int i2,int j2, int f);

/**
 * Funcao auxiliar, juntamente com a funcao merge, para a ordenacao da funcao l e L
 * @param Produto a[] - lista de produtos a ordenar.
 * @param int i
 * @param int j 
 * @param int f - identificador da funcao l (f=1) ou da funcao L (f=2).
 */
void mergeSort(Produto a[],int i,int j, int f);

/**
 * Funcao auxiliar que separa o input 
 * @param char arg[MAXARG] - input a separar
 * @param char res[][MAXARG]
 */
void separaInput(char arg[MAXARG], char res[][MAXARG]);

/**
 * Funcao auxiliar que remove o espaco no inicio da string 
 * @param char str 
 */
void removeEspaco(char *str);
