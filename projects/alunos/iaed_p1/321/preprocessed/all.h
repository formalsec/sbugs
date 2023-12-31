/*File generated by PreProcessor.py*/

#ifndef ALL_H
#define ALL_H

#include "constants.h"


typedef struct Produto
{
  long int price;
  long int weight;
  long int qt;
  char desc[64];
} prod;
typedef struct Encomenda
{
  int weight;
  int len;
  int prod_list[10000];
} ord;
int get_error(int ide2, int idp2, long int qt);
long int get_prod_qt(int idp2, ord *order);
long int calc_cost(ord *order);
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
#endif