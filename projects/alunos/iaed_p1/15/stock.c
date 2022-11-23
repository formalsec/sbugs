#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myLib.h"
#include "stock.h"

/* Criamos o stock */
Stock * stock_init() {

    
    Stock * stock = (Stock *) can_fail_malloc(sizeof(Stock));
    EXIT_IF_ERROR("stock_init: criar_stock");

    /* Valores iniciais */
    stock->count        = 0;
	stock->products     = NULL;
	stock->last_product = NULL;

	return stock;
}

/* Liberta a memoria da estrutura do produto presente no Stock*/
void stock_product_free(Stock_Product *sp) {

	ERROR_IF_NULL(sp, "stock_product_free", exit(EXIT_FAILURE));

	/* Free a estrutura Product */
	product_free( (Product*) sp->product);

	/* Free a estrutura Stock_Product */
	free(sp);
}

/* Liberta a memoria do Stock */
void stock_free(Stock *s) {
	Stock_Product * sp;
	ERROR_IF_NULL(s, "stock_free", exit(EXIT_FAILURE));
    
    /* Free das estruturas Stock_Product*/
	sp = s->products;
	while ( sp!=NULL ) {
		Stock_Product * next = sp->next;
		stock_product_free(sp);
		sp = next;
	}

    /* Free da estrutura Stock */
    free(s);
}

/*  */
int stock_count(const Stock * s) {
	ERROR_IF_NULL(s, "stock_count", exit(EXIT_FAILURE));
    return s->count;
}

/* Obtem o Stock existente de um produto */
Stock_Product * stock_get_product(const Stock * s, int pid) {
	Stock_Product * sp;
	ERROR_IF_NULL(s, "stock_get_product", exit(EXIT_FAILURE));
    
	sp = s->products;
	while ( sp!=NULL ) {
		if (sp->product->id == pid)
			return sp;
		sp = sp->next;
	}
	
	return NULL;
}

/* Adiciona produto a um Stock */
Stock_Product * stock_add_product(Stock * s, const Product *p, int qtd) {
    Stock_Product * sp;
	ERROR_IF_NULL(s, "stock_add_product: Stock", exit(EXIT_FAILURE));
	ERROR_IF_NULL(p, "stock_add_product: Product", exit(EXIT_FAILURE));

	/* Verifica se existe espaco */
	if (s->count==STOCK_MAX_PRODUCT)
		return NULL;

	/* Cria um Stock_Product */
	sp = (Stock_Product*) can_fail_malloc(sizeof(Stock_Product));
	EXIT_IF_ERROR("stock_add_product: criar_stock_product");

	/* Inicia o Stock_Product */
	sp->product      = p;
	sp->qtd          = qtd;
	sp->qtd_reserved = 0;
	sp->next         = NULL;
	sp->previous      = s->last_product;

	/* Adciona a linkedlist */
	s->count++;

	/* Caso ja exista producto atuliza last_product e last_product->next */
	if (s->last_product!=NULL)
		s->last_product->next = sp; /* op->previous->next = op */
	
	s->last_product = sp; /* last_product e agora este novo */

	/* Verifica se tambem e o primeiro */
	if (s->products==NULL) {
		s->products = sp;
	}

	return sp;
}

/* Obtem o produto do Stock */
Product * stock_product_get_product(const Stock_Product * sp) {
	ERROR_IF_NULL(sp, "stock_product_get_product", exit(EXIT_FAILURE));
	return (Product*) sp->product;
}

/* Obtem a quantidade de produto no Stock */
int stock_product_get_quantity(const Stock_Product * sp) {
	ERROR_IF_NULL(sp, "stock_product_get_quantity", exit(EXIT_FAILURE));
	return sp->qtd;
}

/* Obtem o produto reservado no Stock */
int stock_product_get_reserved(const Stock_Product * sp) {
	ERROR_IF_NULL(sp, "stock_product_get_reserved", exit(EXIT_FAILURE));
	return sp->qtd_reserved;
}

/* Obtem o produto disponivel no Stock */
int stock_product_get_available(const Stock_Product * sp) {
	ERROR_IF_NULL(sp, "stock_product_get_available", exit(EXIT_FAILURE));
    return (sp->qtd)-(sp->qtd_reserved);
}

/* Actualiza a quantidade de produto existente num Stock */
int stock_product_update_quantity(Stock_Product * sp, int qtd) {

	ERROR_IF_NULL(sp, "stock_product_update_quantity", exit(EXIT_FAILURE));

    if (stock_product_get_available(sp)+qtd<0) {
        return -1;
	}
	sp->qtd+=qtd;

	return 0;
}

/* Verifica a quantidade de produto reservado no Stock */
int stock_product_reserve_quantity(Stock_Product * sp, int qtd) {

	ERROR_IF_NULL(sp, "stock_product_reserve_quantity", exit(EXIT_FAILURE));

	/* Verifica que so ? reservada uma quantidade >= que a quantidade existente */
	if (stock_product_get_available(sp)<qtd)
		return -1;

    sp->qtd_reserved+=qtd;

	return 0;
}

/* Atribuicao string a todos os argumentos que constituem um Stock*/
char * stock_to_string(const Stock * s, char *buf, int buf_size) {
	//extern int snprintf (char *__restrict __s, size_t __maxlen,__const char *__restrict __format, ...)__THROW __attribute__ ((__format__ (__printf__, 3, 4)));
	ERROR_IF_NULL(s, "stock_to_string", exit(EXIT_FAILURE));
	snprintf(buf, buf_size, "Stock: C=%d", stock_count(s));
	return buf;
}

/* Imprime a string de um produto existente na stock*/
void stock_product_print(const Stock_Product * sp) {

	ERROR_IF_NULL(sp, "stock_product_print", exit(EXIT_FAILURE));
	
	printf("Stock_Product: ID=%d Q=%d R=%d A=%d\n",	product_get_id( stock_product_get_product(sp) ),
													stock_product_get_quantity(sp),
													stock_product_get_reserved(sp),
													stock_product_get_available(sp));
}

/* Imprime uma lista com todos os produtos disponiveis em Stock*/
void stock_list_products(const Stock *s) {
	Stock_Product *sp;
	const Product *p;
	ERROR_IF_NULL(s, "stock_list_products", exit(EXIT_FAILURE));

    sp = s->products;

    puts("Produtos");
    while (sp!=NULL) {
        p = sp->product;
        printf("* %s %d %d\n", p->descricao, p->preco, stock_product_get_available(sp));
		sp = sp->next;
    }
}

/* Imprime uma lista dos precos de todos os produtos disponiveis em Stock*/
void stock_list_products_by_price(const Stock *s) {

	ERROR_IF_NULL(s, "stock_list_products_by_price", exit(EXIT_FAILURE));
	/* TODO */
	stock_list_products(s);
}

/* Imprime o Stock*/
void stock_print(const Stock * s) {
	char buf[100];
	ERROR_IF_NULL(s, "stock_print", exit(EXIT_FAILURE));
	printf("%s\n", stock_to_string(s, buf, 100));
}


