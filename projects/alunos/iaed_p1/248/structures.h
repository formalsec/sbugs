#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_DESCRICAO 63

/*#####################################################################*/
/*	ESTRUTURAS														   */
/*#####################################################################*/

typedef struct produto{
	int idp;
	char descricao[MAX_DESCRICAO];
	int preco;
	int peso;
	int quantidade;
	int pCriado;
}Produto;

typedef struct encomenda{
	int ide;
	int pesoEnc;
	int numberOfProds;
	int prodsEnc[MAX_PRODUTOS];
	int eCriado;
}Encomenda;

/*#####################################################################*/
/*	PROTOTIPOS														   */
/*#####################################################################*/

int __a__();
int __q__();
int __N__();
int __A__();
int __r__();
int __R__();
int __C__();
int __p__();
int __E__();
int __m__();
int __l__();
int __L__();
int __k__();
int __K__();
void mergesort1(int a[], int l, int r);
void merge1(int a[], int l, int m, int r);
void mergesort2(int a[], int  b[], int l, int  r);
void merge2(int a[], int b[], int l, int m, int r);

/*#####################################################################*/

#endif /* STRUCTURES_H */
