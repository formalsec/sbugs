#ifndef PRODUCTS_H_
#define PRODUCTS_H_

#define PRODUCT_DESC_SIZE 64
#define MAX_STOCK_SIZE 10000


typedef struct
{
    int id;
    char description[PRODUCT_DESC_SIZE];
    int price;
    int weight;
    int quantity;

} Product;         

Product stock[MAX_STOCK_SIZE];

void new_product();
void add_stock();
int prod_exists(int id);
void remove_stock();
void change_price();
void sort_orders();
void sort_products();

#endif
