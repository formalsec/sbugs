#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "produtos.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
The function initialise a Produto structure with the differents variables and return the
initialised structure
*/
Produto createProd(int id,char* name, int price, int weight, int stock){
  Produto new;
  new.name = can_fail_malloc(MAX_DESCRIPTION_SIZE*sizeof(char));
  if(!new.name){
    perror("failed to allocate name of Produto");
    exit(EXIT_FAILURE);
  }
  strcpy(new.name, name);
  new.name = can_fail_realloc(new.name, strlen(name)*sizeof(char));
  new.id = id;
  new.price = price;
  new.weight = weight;
  new.stock = stock;
  return new;
}

/*
Receive a Produto and a stock, add the stock to the Produto and returns the
modified Produto
*/

Produto addStock(Produto p, int num){
  p.stock += num;
  return p;
}

/*
Receive a Produto and a stock, remove the stock from the Produto and returns the
modified Produto
*/

Produto removeStock(Produto p, int num){
  p.stock -= num;
  return p;
}

/*
Receive a Produto and a price, change the produto price to the one received and
returns the modified Produto
*/

Produto changePrice(Produto p, int nPrice){
  p.price = nPrice;
  return p;
}

/*
Receive a Produto and return the price of the Produto
*/

int getProdPrice(Produto p){
  return p.price;
}

/*
Receive a Produto and return the stock of the Produto
*/

int getProdStock(Produto p){
  return p.stock;
}

/*
Receive a Produto and return the id of the Produto
*/

int getProdID(Produto p){
  return p.id;
}

/*
Receive a Produto and return the weight of the Produto
*/

int getProdWeight(Produto p){
  return p.weight;
}

/*
Receive a Produto and return the description/name of the Produto
*/

char *getProdName(Produto p){
  return p.name;
}

/*
Receive a Produto and print to the outputFile in the format:
  name price weight
*/

void printProd(Produto p){
  fprintf(outputFile, "%s %d %d\n", p.name, p.price, p.stock);
}

/*
Receive a Produto free the memory used
*/

void free_prod(Produto p){
  if(!p.name){
    return;
  }
  free(p.name);
}
