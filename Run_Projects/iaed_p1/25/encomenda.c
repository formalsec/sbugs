#include "encomenda.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
  Receive 2 strings, return -1 if the first is 'lower', 1 if the second is 'lower'
  and 0 if they are equal
*/

int nameComp(char *c1, char *c2){
  int lenght, i;
  if(strcmp(c1, c2) < 0){
    lenght = strlen(c1);
  }
  else{
    lenght = strlen(c2);
  }
  for(i = 0; i < lenght; i++){
    if(c1[i] < c2[i]){
      return -1;
    }
    else if(c1[i] > c2[i]){
      return 1;
    }
  }
  return 0;
}

/*
  Receive a Encomenda, and sort the products by name
*/

void selectionSortProd(Encomenda e){
  int i, j ,temp;
  Produto p;
  for(i = 0; i < e.nProds - 1; i++){
    temp = i;
    for(j = i + 1; j <= e.nProds -1; j++){
      if(nameComp(getProdName(e.prods[j]), getProdName(e.prods[temp])) == -1){
        temp = j;
      }
    }
    p = e.prods[i];
    e.prods[i] = e.prods[temp];
    e.prods[temp] = p;
  }
}

/*
  Receive a Encomenda and a product id, if the product is in the order,
  return the position, else return -1
*/

int prodInEnc(Encomenda e,int idp){
  int i;
  for(i = 0; i < e.nProds; i++){
    if(getProdID(e.prods[i]) == idp){
      return i;
    }
  }
  return -1;
}

/*
  Receive an order id and return a new Encomenda
*/

Encomenda createEncomenda(int id){
  Encomenda new;
  new.prods = malloc(MAX_PRODUTOS*sizeof(Produto));
  if(!new.prods){
    perror("Error of allocation in createEncomenda");
    exit(EXIT_FAILURE);
  }
  new.weight = 0;
  new.nProds = 0;
  new.id = id;
  return new;
}

/*
  Receive a Encomenda, a product ip and a price, changes the price of the product in
  the order and return the Encomenda
*/

Encomenda changeProdPriceInEnc(Encomenda e, int idp, int newPrice){
  int pos = prodInEnc(e, idp);
  if(pos != -1){
    e.prods[pos] = changePrice(e.prods[pos], newPrice);
  }
  return e;
}

/*
  Receive a Encomenda and a Produto, if the product already exists in the order,
  add the stock, else add a new product in the order
  return the Encomenda
*/

Encomenda addEncProd(Encomenda e, Produto p){
  int pos = prodInEnc(e, getProdID(p));
  if(pos == -1){
    e.prods[e.nProds] = p;
    e.nProds ++;
  }
  else{
    e.prods[pos] = addStock(e.prods[pos], getProdStock(p));
  }
  e.weight += getProdWeight(p)*getProdStock(p);
  return e;
}

/*
  Receive a Encomenda and return its weight
*/

int getEncWeight(Encomenda e){
  return e.weight;
}

/*
  Receive a Encomenda and free the memory usedS
*/

void free_enco(Encomenda e){
  if(!e.prods){
    return;
  }
  free(e.prods);
}

/*
  Receive a Encomenda and a Produto, remove the stock from the product in the order
  return the Encomenda
*/

Encomenda removeEncProd(Encomenda e, int idp){
  int pos = prodInEnc(e, idp);
  if(pos != -1){
    e.weight -= getProdStock(e.prods[pos]) * getProdWeight(e.prods[pos]);
    e.prods[pos] = removeStock(e.prods[pos], getProdStock(e.prods[pos]));
  }
  return e;
}

/*
  Receive a Encomenda and a product id, and returns the stock of the product in the order
*/

int getProdStockInEnc(Encomenda e, int idp){
  int pos = prodInEnc(e, idp);
  if(pos != -1){
    return getProdStock(e.prods[pos]);
  }
  return 0;
}

/*
  Receive a Encomenda and a product id, and returns the name of the product in the order
*/

char* getProdNameInEnc(Encomenda e, int idp){
  int pos = prodInEnc(e, idp);
  return getProdName(e.prods[pos]);
}

/*
  Receive a Encomenda, and returns the price of the order
*/

int getEncPrice(Encomenda e){
  int i, total = 0;
  for(i = 0; i < e.nProds; i++){
    if(getProdStock(e.prods[i]) != 0){
      total += getProdPrice(e.prods[i]) * getProdStock(e.prods[i]);
    }
  }
  return total;
}

/*
  Receive a Encomenda, sort the list of products and print in the outputFile the products
*/

void listProd(Encomenda e){
  int i;
  selectionSortProd(e);
  for(i = 0; i < e.nProds; i++){
    if(getProdStock(e.prods[i]) > 0){
      fprintf(outputFile,"* ");
      printProd(e.prods[i]);
    }
  }
}
