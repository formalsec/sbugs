#ifndef ENCOMENDA_H
#define ENCOMENDA_H

#include "produtos.h"
/*
 A structure that contains a list of Produto, a weight, the number of Produto added
 and a id
*/

typedef struct encomenda{
  Produto *prods;
  int weight;
  int nProds;
  int id;
}Encomenda;

Encomenda createEncomenda();
Encomenda addEncProd(Encomenda e, Produto p);
Encomenda removeEncProd(Encomenda e, int idp);
Encomenda changeProdPriceInEnc(Encomenda e, int idp, int newPrice);
char* getProdNameInEnc(Encomenda e, int idp);
int getProdStockInEnc(Encomenda e, int idp);
int getEncPrice(Encomenda e);
int getEncWeight(Encomenda e);
void listProd(Encomenda e);
void free_enco(Encomenda e);

#endif