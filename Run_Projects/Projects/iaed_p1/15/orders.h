#ifndef ORDERS_H_
#define ORDERS_H_

#include "order.h"

/* Numero maximo de encomendas */
#define ORDERS_MAX_ORDERS 500

typedef struct orders {
    int count;
    Order ** orders;
} Orders;

Orders * orders_init();
void     orders_free(Orders * oo);

void orders_print(const Orders * oo);
void orders_list (const Orders * oo);

Order * orders_get_order(const Orders * oo, int oid);
int     orders_add_order(      Orders * oo, Order * o);

int orders_get_count      (const Orders * oo);

#endif
