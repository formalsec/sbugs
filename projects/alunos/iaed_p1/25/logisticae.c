#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "constants.h"
#include "logisticae.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Receives a Logistics and an int between 0 and 1
  0 represents the product id
  1 represents the order id
  retorn the iNumber in the system and add one at this iNumber
*/

int obtainIdNumber(Logistics *l, int i){
  int Inumber;
  if(i == 0){
    Inumber = (l->nextIdp)++;
  }
  else if(i == 1){
    Inumber = (l->nextIde)++;
  }
  else{
    fprintf(outputFile,"Wrong Initialisation of newInumber\n");
  }
  return Inumber;
}

/*
  Receive a Logistics and a product id, if the product exists in te logistics,
  returns the position in the list, otherwise returns -1
*/

int getProdPos(Logistics *l, int id){
  int i;
  if(id >= l->nextIdp){
    return -1;
  }
  for(i = 0; i < MAX_PRODUTOS; i++){
    if(getProdID(l->prods[i]) == id){
      return i;
    }
  }
  return -1;
}

/*
Separa uma string constituida entre 1 e 3 inteiros separados por ':'
return a list of num size with the int from the string
*/
void separate(char *string, int num, int *tab){
  char *first, *second, *third;
  int i = 0, firstLen = 0, secondLen = 0, thirdLen = 0, spacing = 0;
  while((string[i] == ':' || (string[i] >= '0' && string[i] <= '9')) && string[i] != '\0'){
    if(string[i] == ':'){
      spacing++;
    }
    else if(spacing == 0){
      firstLen++;
    }
    else if(spacing == 1){
      secondLen++;
    }
    else{
      thirdLen++;
    }
    i++;
  }
  first = can_fail_malloc((firstLen+1)*sizeof(char));
  second = can_fail_malloc((secondLen+1)*sizeof(char));
  third = can_fail_malloc((thirdLen+1)*sizeof(char));
  if(!first || !second || !third){
    perror("allocation failed in separate");
    exit(EXIT_FAILURE);
  }
  strncpy(first, string, firstLen);
  first[firstLen] = '\0';
  tab[0] = atoi(first);
  if(secondLen != 0 && num > 1){
    strncpy(second, string + firstLen + 1, secondLen);
    second[secondLen] = '\0';
    tab[1] = atoi(second);
  }
  if(thirdLen != 0 && num == 3){
    strncpy(third, string + firstLen + secondLen + 2, thirdLen);
    third[thirdLen] = '\0';
    tab[2] = atoi(third);
  }
  free(first);
  free(second);
  free(third);
}


void mergeProds(Logistics *l, int left, int middle, int right){
  int i, j, k, price1, price2;
  Logistics *aux = createLog();
  for(i = middle+1; i > left; i--){
    aux->prods[i-1] = l->prods[i-1];
  }
  for(j = middle; j < right; j++){
    aux->prods[right+middle-j] = l->prods[j+1];
  }
  for(k = left; k <=right; k++){
    price1 = getProdPrice(aux->prods[j]);
    price2 = getProdPrice(aux->prods[i]);
    if((price1 < price2) || (price1 == price2 && getProdID(aux->prods[j]) < getProdID(aux->prods[i]))){
      l->prods[k] = aux->prods[j--];
    }
    else{
      l->prods[k] = aux->prods[i++];
    }
  }
  freeLogistics(aux);
}

/*
Receives la Logistics, and sorts the products list by price and id
*/

void mergeSortProds(Logistics *l, int left , int right){
  int middle = (left + right)/2;
  if(right <= left){
    return;
  }
  mergeSortProds(l, left, middle);
  mergeSortProds(l, middle+1, right);
  mergeProds(l, left, middle, right);
}

/*
Initialises a Logistics structure
*/
Logistics *createLog(){
  Logistics *new = can_fail_malloc(sizeof(Logistics));
  new->prods = can_fail_malloc(MAX_PRODUTOS*sizeof(Produto));
  new->enco = can_fail_malloc(MAX_ENCOMENDAS*sizeof(Encomenda));
  if(!new->prods || !new->enco){
    perror("Error Initialising logistics");
    exit(EXIT_FAILURE);
  }
  new->nextIde = 0;
  new->nextIdp = 0;
  return new;
}

/*
  Receive a string and a Logistics, separate the string in a string and 3 int,
  then initialises a products and add him in the Logistics
*/
void addProd(Logistics *l, char *string){
  char *name, *rest;
  int nameLen = 0, tab[3], id, restLen=0;
  id = obtainIdNumber(l, 0);
  if(id < MAX_PRODUTOS){
    while (string[nameLen] != ':') {
      nameLen++;
    }
    restLen = strlen(string) - nameLen;
    name = can_fail_malloc((nameLen + 1)*sizeof(char));
    rest = can_fail_malloc((restLen + 1)* sizeof(char));
    if(!name || !rest || nameLen > MAX_DESCRIPTION_SIZE){
      perror("can_fail_malloc didnt work addProd");
      exit(EXIT_FAILURE);
    }
    name = strncpy(name, string, nameLen);
    rest = strncpy(rest, string + nameLen + 1, restLen);
    name[nameLen] = '\0';
    rest[restLen] = '\0';
    separate(rest, 3 ,tab);
    l->prods[id] = createProd(id , name, tab[0], tab[1], tab[2]);
    free(name);
    free(rest);
    fprintf(outputFile,"Novo produto %d.\n", id);
  }
}

/*
  Receive a Logistics and a string, separate the string in 2 int being the
  id of a prod and a stock, if the product exists in the Logistics, add the stock to it
*/
void addProdStock(Logistics *l, char* string){
  int tab[2], pos;
  separate(string, 2, tab);
  pos = getProdPos(l, tab[0]);
  if(pos == -1){
    fprintf(outputFile,"Impossivel adicionar produto %d ao stock. Produto inexistente.\n", tab[0]);
  }
  else{
    l->prods[pos] = addStock(l->prods[pos], tab[1]);
  }
}

/*
  Receive a Logistics and a string, separate the string in 2 int being the
  id of a prod and a stock, if the product exists in the Logistics and the product has enought stock,
  remove the stock from it
*/

void removeProdStock(Logistics *l, char *string){
  int tab[2], pos;
  separate(string, 2, tab);
  pos = getProdPos(l, tab[0]);
  if(pos == -1){
    fprintf(outputFile,"Impossivel remover stock do produto %d. Produto inexistente.\n", tab[0]);
  }
  else if(getProdStock(l->prods[pos]) < tab[1]){
    fprintf(outputFile,"Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", tab[1], tab[0]);
  }
  else{
    l->prods[pos] = removeStock(l->prods[pos], tab[1]);
  }
}

/*
  Receive a Logistics and add a new order to it
*/

void addEncomenda(Logistics *l){
  int id;
  id = obtainIdNumber(l, 1);
  if(id < MAX_ENCOMENDAS){
    l->enco[id] = createEncomenda(id);
    fprintf(outputFile,"Nova encomenda %d.\n", id);
  }
}

/*
  Receive a Logistics and a string, separate the string into a order id, a product id and a stock
  if the product and the order exists, the product has enought and the maximum weight of the order
  isn't exeded, add the product with the stock into the order while removing the stock from the Logistics
*/

void addProdInEnc(Logistics *l, char *string){
  int tab[3], pos;
  Produto newP, oldP;
  separate(string, 3 ,tab);
  pos = getProdPos(l, tab[1]);
  if(tab[0] >= l->nextIde){
    fprintf(outputFile,"Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", tab[1], tab[0]);
  }
  else if(pos == -1){
    fprintf(outputFile,"Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", tab[1], tab[0]);
  }
  else if(getProdStock(l->prods[pos]) < tab[2]){
    fprintf(outputFile,"Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", tab[1], tab[0]);
  }
  else if(getEncWeight(l->enco[tab[0]]) + getProdWeight(l->prods[pos])*tab[2] > MAX_PESO_ENCOMENDA){
    fprintf(outputFile,"Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", tab[1], tab[0], MAX_PESO_ENCOMENDA);
  }
  else{
    oldP = l->prods[pos];
    newP = createProd(getProdID(oldP), oldP.name, getProdPrice(oldP) ,getProdWeight(oldP), tab[2]);
    l->enco[tab[0]] = addEncProd(l->enco[tab[0]], newP);
    l->prods[pos] = removeStock(oldP, tab[2]);
  }
}

/*
  Receive a Logistics and a string, separate the string into a product id and a price
  If the product exists, change the price of the product inside the Logistics and the orders
*/

void changeProdPrice(Logistics *l, char *string){
  int tab[2], pos;
  int i;
  separate(string, 2, tab);
  pos = getProdPos(l, tab[0]);
  if(pos == -1){
    fprintf(outputFile,"Impossivel alterar preco do produto %d. Produto inexistente.\n", tab[0]);
  }
  else{
    l->prods[pos] = changePrice(l->prods[pos], tab[1]);
    for(i = 0; i < l->nextIde; i++){
      l->enco[i] = changeProdPriceInEnc(l->enco[i], tab[0], tab[1]);
    }
  }
}

/*
  Receive a Logistics and a string, separate the string into a product id and a order id
  If the order exists and the product exists, remove the product from the order and
  add the stock to the product in the Logistics
*/

void removeProdInEnc(Logistics *l, char* string){
  int tab[2], pos, stock;
  separate(string, 2, tab);
  pos = getProdPos(l, tab[1]);
  if(tab[0] >= l->nextIde){
    fprintf(outputFile, "Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", tab[1], tab[0]);
  }
  else if(pos == -1){
    fprintf(outputFile, "Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", tab[1], tab[0]);
  }
  else{
    stock = getProdStockInEnc(l->enco[tab[0]], getProdID(l->prods[pos]));
    l->prods[pos] = addStock(l->prods[pos], stock);
    l->enco[tab[0]] = removeEncProd(l->enco[tab[0]], getProdID(l->prods[pos]));
  }
}

/*
  Receive a Logistics and a string, get the id of the order from the string
  if the order exists, calculate the total price of the order and print in the outputFile
*/

void getPriceForEnc(Logistics *l, char *string){
  int tab[1], price;
  separate(string, 1, tab);
  if(tab[0] >= l->nextIde){
    fprintf(outputFile, "Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", tab[0]);
  }
  else{
    price = getEncPrice(l->enco[tab[0]]);
    fprintf(outputFile, "Custo da encomenda %d %d.\n", tab[0], price);
  }
}

/*
  Receive a Logistics and a string, get a product id from the string
  If the product exists, look at all the orders and print into the outputFile
  witch order hase the more of this product
*/

void mostFrequentProd(Logistics *l,char* string){
  int tab[1], pos, mPos = 0, i;
  separate(string, 1, tab);
  pos = getProdPos(l, tab[0]);
  if(pos == -1){
    fprintf(outputFile,"Impossivel listar maximo do produto %d. Produto inexistente.\n", tab[0]);
  }
  else{
    for(i = 0; i < l->nextIde; i++){
      if(getProdStockInEnc(l->enco[i], tab[0]) > getProdStockInEnc(l->enco[mPos], tab[0])){
        mPos = i;
      }
    }
    if(l->nextIde > 0 && getProdStockInEnc(l->enco[mPos], tab[0]) > 0){
      fprintf(outputFile,"Maximo produto %d %d %d.\n", tab[0], mPos, getProdStockInEnc(l->enco[mPos], tab[0]));
    }
  }
}

/*
  Receive a Logistics and a string, separate the string into a order id and a product id
  If the product and the order exists, print in the outputFile the name of the product and the
  stock in the order
*/

void printProdInEnc(Logistics *l,char* string){
  int tab[2], pos;
  separate(string, 2, tab);
  pos = getProdPos(l, tab[1]);
  if(tab[0] >= l->nextIde){
    fprintf(outputFile,"Impossivel listar encomenda %d. Encomenda inexistente.\n", tab[0]);
  }
  else if(pos == -1){
    fprintf(outputFile,"Impossivel listar produto %d. Produto inexistente.\n", tab[1]);
  }
  else{
    fprintf(outputFile,"%s %d.\n", getProdName(l->prods[pos]) ,getProdStockInEnc(l->enco[tab[0]], tab[1]));
  }
}

/*
  Receive a Logistics, sort the product list by price then print the list in the outputFile
*/

void printOrdProd(Logistics *l){
  int i;
  fprintf(outputFile,"Produtos\n");
  mergeSortProds(l, 0, l->nextIdp-1);
  for(i = 0; i < l->nextIdp; i++){
    fprintf(outputFile,"* ");
    printProd(l->prods[i]);
  }
}

/*
  Receive a Logistics and a string, get a order id from the string
  If the order exists, print the products from the order in the outputFile
*/

void printEncProds(Logistics *l, char *string){
  int tab[1];
  separate(string, 1,tab);
  if(tab[0] >= l->nextIde){
    fprintf(outputFile,"Impossivel listar encomenda %d. Encomenda inexistente.\n", tab[0]);
  }
  else{
    fprintf(outputFile,"Encomenda %d\n", tab[0]);
    listProd(l->enco[tab[0]]);
  }
}

/*
  Receive a logistics, free the memory used by all his products, and then free the Logistics
*/

void freeLogistics(Logistics *l){
  int i;
  for(i = 0; i < l->nextIdp; i++){
    free_prod(l->prods[i]);
  }
  for(i = 0; i < l->nextIde;i++){
    free_enco(l->enco[i]);
  }
  free(l->prods);
  free(l->enco);
  free(l);
}
