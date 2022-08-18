#ifndef ORDER_H_
#define ORDER_H_

#include "product.h"

/* Peso maximo das encomendas */
#define ORDER_MAX_WEIGHT 200

/* Estrutura que representa conjunto de Produtos*/
typedef struct s_order_product {
    int             qtd;
    const Product * product;
	struct s_order_product * previous;
	struct s_order_product * next;
} Order_Product;

typedef struct s_order {
    int id;
    int count;
	int weight;
    Order_Product * products;
	Order_Product * last_product;
} Order;

Order * order_new();
void    order_free                  (      Order *o);
void    order_print                 (const Order *o);

int order_get_id                    (const Order *o);
int order_get_count                 (const Order *o);

int order_get_cost                  (const Order *o);
int order_get_weight                (const Order *o);

Order_Product * order_get_product   (const Order *o, int pid);
Order_Product * order_add_product   (      Order *o, const Product *p, int qtd);
int             order_remove_product(      Order *o, int pid);

void order_list_products            (const Order *o);
void order_list_products_by_desc    (const Order *o);

const Product * order_product_get_product (const Order_Product *op);
int             order_product_get_quantity(const Order_Product *op);
void            order_product_print       (const Order_Product *op);

#endif
