#ifndef STOCK_H_
#define STOCK_H_

#include "product.h"

#define STOCK_MAX_PRODUCT 10000

/* A estrutura utilizada para adicionar ao Product ao Stock */
typedef struct s_stock_product {
    int             qtd;
    int             qtd_reserved;
	const Product * product;
	struct s_stock_product * next;
	struct s_stock_product * previous;
} Stock_Product;

/* A estrutura que define um stock*/
typedef struct s_stock {
    int count;					/* Numero actual de produtos */
    Stock_Product * products;	/* Apontador para o primeiro produto */
	Stock_Product * last_product;
} Stock;

Stock * stock_init();
void    stock_free(Stock * s);

char * stock_to_string                  (const Stock * s, char *buf, int buf_size);
void   stock_print                      (const Stock * s);

int stock_count                         (const Stock * s);

void stock_list_products                (const Stock * s);
void stock_list_products_by_price       (const Stock * s);

Stock_Product * stock_get_product       (const Stock * s, int pid);
Stock_Product * stock_add_product       (      Stock * s, const Product *p, int qtd);
int             stock_remove_product    (      Stock * s, int pid, int qtd);

Product * stock_product_get_product     (const Stock_Product * sp);
int       stock_product_get_quantity    (const Stock_Product * sp);
int       stock_product_get_reserved    (const Stock_Product * sp);
int       stock_product_get_available   (const Stock_Product * sp);
int       stock_product_update_quantity (      Stock_Product * sp, int qtd);
int       stock_product_reserve_quantity(      Stock_Product * sp, int qtd);
void      stock_product_print           (const Stock_Product * sp);

#endif
