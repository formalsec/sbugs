/*File generated by PreProcessor.py*/

#ifndef STRUCTS_H
#define STRUCTS_H



typedef struct product
{
  char desc[64];
  int price;
  int wgt;
  int qtt;
} product;
typedef struct order
{
  int wgt;
  int num;
  int prods[10000];
  int ids[10000];
} order;
product sys[10000];
int totalp = 0;
order ords[500];
int totalo = 0;
#endif