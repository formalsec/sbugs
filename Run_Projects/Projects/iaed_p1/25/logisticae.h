#ifndef LOGISTICAE_H
#define LOGISTICAE_H

#include "encomenda.h"
#include "produtos.h"
/*
  A structure that contains an array of products, an array of orders, 
  the id for the next product and the id for the next order
*/
typedef struct logistics{
  Produto *prods;
  Encomenda *enco;
  int nextIde;
  int nextIdp;
}Logistics;

Logistics *createLog();
void addProd(Logistics *l,char *string);
void addProdStock(Logistics *l, char* string);
void removeProdStock(Logistics *l, char *string);
void changeProdPrice(Logistics *l, char*string);
void addEncomenda(Logistics *l);
void addProdInEnc(Logistics *l, char *string);
void removeProdInEnc(Logistics *l, char* string);
void printProdInEnc(Logistics *l,char* string);
void mostFrequentProd(Logistics *l,char* string);
void printEncProds(Logistics *l, char *string);
void printOrdProd(Logistics *l);
void getPriceForEnc(Logistics *l, char *string);
void freeLogistics(Logistics *l);

#endif
