/*File generated by PreProcessor.py*/

#ifndef PRODUCTS_H_
#define PRODUCTS_H_



typedef struct 
{
  int id;
  char description[64];
  int price;
  int weight;
  int quantity;
} Product;
Product stock[10000];
void new_product();
void add_stock();
int prod_exists(int id);
void remove_stock();
void change_price();
void sort_orders();
void sort_products();
#endif