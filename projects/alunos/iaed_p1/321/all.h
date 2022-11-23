#ifndef ALL_H
#define ALL_H

#include "constants.h"

/* estrutura do produto */
typedef struct Produto {
	long int price;				/* preco do produto */
	long int weight;			/* peso do produto */
	long int qt;				/* quantidade em stock */
	char desc[MAX_DESC];		/* descricao do produto */
} prod;

/* estrutura da encomenda */
typedef struct Encomenda { 
	int weight;					/* peso da encomenda */
	int len;					/* numero de produtos */
	int prod_list[MAX_PROD];	/* lista dos produtos da encomenda */
} ord;

/*--------------------*\
 * Funcoes auxiliares *
\*--------------------*/

int get_error(int ide2, int idp2, long int qt);
long int get_prod_qt(int idp2, ord* order);
long int calc_cost(ord* order);

/*--------------------*\
 * Funcoes principais *
\*--------------------*/

void add_prod_sys();
void add_stock();
void add_order();
void add_prod_ord();
void remove_stock();
void remove_prod();
void order_cost();
void change_price();
void show_prod();
void most_wanted();
void list_prod_sys();
void list_prod_ord();

#endif /* ALL_H */
