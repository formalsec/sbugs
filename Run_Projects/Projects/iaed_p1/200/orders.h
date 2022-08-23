#ifndef ORDERS_H_
#define ORDERS_H_

#include "products.h"

#define MAX_WEIGHT 200
#define MAX_ORDERS 500

Product order[MAX_ORDERS][MAX_WEIGHT];

void new_order();
void add_to_order();
void order_price();
void order_desc_quantity();
void compare_orders();
void sort_orders();
void remove_from_order();
void return_order_id();

#endif
