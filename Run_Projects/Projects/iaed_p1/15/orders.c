#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "myLib.h"
#include "product.h"
#include "order.h"
#include "orders.h"

/* Cria um conjunto de orders (encomendas)*/
Orders * orders_init() {

	Orders * oo = (Orders *) malloc(sizeof(Orders));
	EXIT_IF_ERROR("orders_init: malloc Order");

	oo->orders = (Order **) malloc(sizeof(Order*)*ORDERS_MAX_ORDERS);
	EXIT_IF_ERROR("orders_init: malloc Orders");

	oo->count  = 0;

	return oo;
}

/* Liberta espaco de memoria das orders(encomendas) */
void orders_free(Orders * oo) {
	int oid;
	ERROR_IF_NULL(oo, "orders_free", exit(EXIT_FAILURE));

	for (oid=0; oid<oo->count; oid++)
		order_free(orders_get_order(oo, oid));

	free(oo->orders);

	free(oo);
}

/* Imprime Orders(encomendas)*/
void orders_print(const Orders * oo) {
	ERROR_IF_NULL(oo, "orders_print", exit(EXIT_FAILURE));
	printf("Orders: C=%d\n", orders_get_count(oo));
}

/* Imprime lista de Orders(encomendas)*/
void orders_list(const Orders * oo) {
	int oid;
	ERROR_IF_NULL(oo, "orders_list", exit(EXIT_FAILURE));

	puts("ORDERS");
	for (oid=0; oid<oo->count; oid++) {
		order_print(orders_get_order(oo, oid));
	}
}

/* Obtem Order(encomenda) numa lista de Orders(encomendas) */
Order * orders_get_order(const Orders * oo, int oid) {

	ERROR_IF_NULL(oo, "orders_get_order", exit(EXIT_FAILURE));
	return oo->orders[oid];
}

/* Adiciona Order(encomenda) a lista de Orders(encomendas)*/
int orders_add_order(Orders * oo, Order * o) {

	ERROR_IF_NULL(oo, "orders_add_order: Orders", exit(EXIT_FAILURE));
	ERROR_IF_NULL( o, "orders_add_order: Order",  exit(EXIT_FAILURE));

	if (oo->count==ORDERS_MAX_ORDERS)
		return -1;

	oo->orders[oo->count++] = o;

	return 0;
}

/* Obtem numero de Orders(encomendas) existentes no sistema */
int orders_get_count(const Orders * oo) {
	ERROR_IF_NULL(oo, "orders_get_count", exit(EXIT_FAILURE));
	return oo->count;
}
