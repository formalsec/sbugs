#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 64
#define LINEMAX 100
#define PRODUCTS 10000
#define ORDERS 500
#define MAXORDER 1000
#define INPUT 5

/*Macro definida para trocar os conteudos de um produto para outro*/
#define exchg(X,Y) {struct Product tmp; tmp = X; X = Y; Y = tmp;}

/*Definicao das structs usadas no projeto, sendo a primeira usada para os produtos e as seguintes para as encomendas*/
struct Product{
	char desc[MAX];
	int price, weight, qtd, idp;
} product;

struct Encomenda{
	int prodIdp[MAXORDER];
	int prodQtd[MAXORDER];
	int prodTotal;
} encomenda;

struct EncomendaUnica{
	struct Product prods[MAXORDER];
	int prodTotal;
} encomendaUnica;

/*Declaracao de todas as funcoes utilizadas*/
void strtoken(char line[INPUT][LINEMAX], int input);
int a(struct Product prodList[PRODUCTS], char line[INPUT][LINEMAX], int idp);
void q(struct Product prodList[PRODUCTS], char line[INPUT][LINEMAX], int idp);
void A(struct Product prodList[PRODUCTS], char line[INPUT][LINEMAX], int idp, int ide, struct Encomenda encomendas[ORDERS]);
int pesoEncomenda(struct Product prodList[PRODUCTS], struct Encomenda order);
void r(struct Product prodList[PRODUCTS], char line[INPUT][LINEMAX], int idp);
void R(char line[INPUT][LINEMAX], int idp, int ide, struct Encomenda encomendas[ORDERS], struct Product prodList[PRODUCTS]);
void C(int ide, struct Encomenda encomendas[ORDERS], char line[INPUT][LINEMAX], struct Product prodList[PRODUCTS]);
void p(struct Product prodList[PRODUCTS], char line[INPUT][LINEMAX], int idp);
void E(int ide, struct Encomenda encomendas[ORDERS], char line[INPUT][LINEMAX], struct Product prodList[PRODUCTS], int idp);
void m(int ide, struct Encomenda encomendas[ORDERS], char line[INPUT][LINEMAX], int idp);
void quicksort1(struct Product prodListSorted[PRODUCTS], int l, int r);
int partition(struct Product prodListSorted[PRODUCTS], int l, int r);
void l(struct Product prodList[PRODUCTS], int idp);
void quicksort2(struct Product produ[MAXORDER], int l, int r);
int partition1(struct Product produ[MAXORDER], int l, int r);
void L(int ide, struct Encomenda encomendas[ORDERS], char line[INPUT][LINEMAX], struct Product prodList[PRODUCTS]);

#endif
