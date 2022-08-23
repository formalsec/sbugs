#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT 100
#define MAX_N_OF_INPUTS 4
#define MAX_DESC 63
#define MAX_INT_CHARACTERS 30
#define MAX_WEIGHT 200
/*structure used to stock products*/
typedef struct prd{
  int id;                                          /*product identification*/
  char desc[MAX_DESC];                             /*product description*/
  int price;                                       /*product price*/
  int w;                                           /*product weight*/
  int qtd;                                         /*quantity of product(in stock)*/
} prd;
/*string with the various stocked products*/
prd stock[10000];                                  /*stocks all products*/
/*structure used to store orders*/
typedef struct order{
  int n_diff_prod;                                 /*number of different ordered products*/
  int prod_ord[MAX_WEIGHT];                        /*what products are ordered*/
  int qtd_ord[MAX_WEIGHT];                         /*quantity of each ordered product*/
} order;
/*string with the various stored orders*/
order orders[500];                                 /*regiters all orders made*/

int main(){
/*----------------------------------------------------------------------------*/
/*---------------------inicializations of used variables----------------------*/
/*----------------------------------------------------------------------------*/
  int i, j, k, l;                                  /*vairables used for loops/operations*/
  char m[MAX_DESC];
  char input[MAX_INPUT];                           /*used to store all user input*/
  char i0[MAX_DESC];                               /*stores the 1st piece of input recieved*/
  char i1[MAX_INT_CHARACTERS];                     /*stores the 2nd piece of input recieved*/
  char i2[MAX_INT_CHARACTERS];                     /*stores the 3rd piece of input recieved*/
  char i3[MAX_INT_CHARACTERS];                     /*stores the 4th piece of input recieved*/
  char command;                                    /*stores the required command*/
  char *token;                                     /*used to separate input*/
  int n_input;                                     /*number of pieces of input recieved*/
  int id_occupied=0;                               /*current number of different products*/
  int n_orders=0;                                  /*current number of orders*/
/*----------------------------------------------------------------------------*/
/*--------------------------intake user information---------------------------*/
/*----------------------------------------------------------------------------*/
  while ((command = getchar()) != 'x') {
    if (command!='N') {
      if (command!='l') {
        getchar();                                 /*removes the extra space on user input*/
      }
    }
    fgets(input, MAX_INPUT, stdin);                 /*saves all user input*/
    n_input = 0;                                   /*resets number of inputs recieved*/
    token = strtok(input, ":");                    /*separates input by the : character*/
    while(token != NULL) {
      switch (n_input){
        case 0:                                    /*1st piece of input?*/
          strcpy(i0, token);
          break;
        case 1:                                    /*2nd piece of input?*/
          strcpy(i1, token);
          break;
        case 2:                                    /*3rd piece of input?*/
          strcpy(i2, token);
          break;
        case 3:                                    /*4th piece of input?*/
          strcpy(i3, token);
          break;
      }
      n_input = n_input + 1;                       /*next piece of input?*/
      token = strtok(NULL, ":");                   /*updates piece of input not stored yet*/
    }
/*----------------------------------------------------------------------------*/
/*-------------------------------input commands-------------------------------*/
/*----------------------------------------------------------------------------*/
    switch (command) {
/*------------------------add new product to the stock------------------------*/
      case 'a':
      stock[id_occupied].id = id_occupied;         /*attributes id number the product*/
      strcpy(stock[id_occupied].desc, i0);         /*attributes description to product*/
      stock[id_occupied].price = atoi(i1);         /*attributes price to product*/
      stock[id_occupied].w = atoi(i2);             /*attributes weight to product*/
      stock[id_occupied].qtd = atoi(i3);           /*attributes quantity to product*/
      printf("Novo produto %d.\n", id_occupied);
      id_occupied = id_occupied + 1;               /*next product id number*/
      break;
/*-----------add more quantity to an existing product on the stock------------*/
      case 'q':
      if (id_occupied<=atoi(i0)) {                 /*product doesn't exist*/
        printf("Impossivel adicionar produto %s ao stock. Produto inexistente.\n", i0);
        break;
      }
      stock[atoi(i0)].qtd = stock[atoi(i0)].qtd + atoi(i1);
      break;                                       /*adds the quantity desired to stock*/
/*-------------------------------add new order--------------------------------*/
      case 'N':
      orders[n_orders].n_diff_prod = 0;            /*order has no products at start*/
      printf("Nova encomenda %d.\n", n_orders);
      n_orders = n_orders + 1;                     /*adds to the number of total orders*/
      break;
/*---------------------------add product to order-----------------------------*/
      case 'A':
      if (n_orders<=atoi(i0)) {                    /*order exists?*/
        printf("Impossivel adicionar produto %s a encomenda %s. Encomenda inexistente.\n", i1, i0);
        break;
      }
      if (id_occupied<=atoi(i1)) {                 /*product exists?*/
        printf("Impossivel adicionar produto %s a encomenda %s. Produto inexistente.\n", i1, i0);
        break;
      }
      if (stock[atoi(i1)].qtd<atoi(i2)) {  /*is there enough product to add?*/
        printf("Impossivel adicionar produto %s a encomenda %s. Quantidade em stock insuficiente.\n", i1, i0);
        break;
      }
      i=0;                                         /*counts different products*/
      j=atoi(i2)*stock[atoi(i1)].w;                /*weight of order*/
      while (i!=orders[atoi(i0)].n_diff_prod) {
        j = j + (stock[orders[atoi(i0)].prod_ord[i]].w) * (orders[atoi(i0)].qtd_ord[i]);
        i=i+1;
      }
      if (j>MAX_WEIGHT) {
        printf("Impossivel adicionar produto %s a encomenda %s. Peso da encomenda excede o maximo de 200.\n", i1, i0);
        break;
      }
      i = 0;                                       /*counts different products*/
      j = 0;                                       /*becomes 1 if product already exists in order*/
      while (i != orders[atoi(i0)].n_diff_prod) {
        if (orders[atoi(i0)].prod_ord[i] == atoi(i1)) {
          orders[atoi(i0)].qtd_ord[i] = orders[atoi(i0)].qtd_ord[i] + atoi(i2);
          j = 1;                                   /*product already exists in order*/
        }
        i = i+1;                                   /*next product in order*/
      }
      if (j == 0) {                                /*product is new in order*/
        orders[atoi(i0)].prod_ord[orders[atoi(i0)].n_diff_prod] = atoi(i1);
                                                   /*adds new product*/
        orders[atoi(i0)].qtd_ord[orders[atoi(i0)].n_diff_prod] = atoi(i2);
                                                   /*quantity of new product*/
        orders[atoi(i0)].n_diff_prod = orders[atoi(i0)].n_diff_prod + 1;
      }                                            /*adds to the number of products*/
      stock[atoi(i1)].qtd = stock[atoi(i1)].qtd - atoi(i2);
      break;
/*------------------remove stock from an existing product---------------------*/
      case 'r':
      if (id_occupied<=atoi(i0)) {                 /*product doesn't exist*/
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", atoi(i0));
        break;
      }
      if (stock[atoi(i0)].qtd < atoi(i1)) {        /*not enough quantity in stock*/
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", atoi(i1), atoi(i0));
        break;
      }
      stock[atoi(i0)].qtd = stock[atoi(i0)].qtd - atoi(i1);
      break;                                       /*removes desired quantity from stock*/
/*------------------------remove product from an order------------------------*/
      case 'R':
      if (n_orders<=atoi(i0)) {                    /*order exists?*/
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", atoi(i1), atoi(i0));
        break;
      }
      if (id_occupied<=atoi(i1)) {                 /*product exists?*/
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", atoi(i1), atoi(i0));
        break;
      }
      i=0;                                         /*counts different products*/
      while (i != orders[atoi(i0)].n_diff_prod) {
        if (orders[atoi(i0)].prod_ord[i]==atoi(i1)) {
          stock[atoi(i1)].qtd = stock[atoi(i1)].qtd + orders[atoi(i0)].qtd_ord[i];
          orders[atoi(i0)].qtd_ord[i] = 0;         /*resets quantity of product*/
        }
        i = i+1;                                   /*next product in order*/
      }
      break;
/*-------------------------determine an order's cost--------------------------*/
      case 'C':
      if (n_orders<=atoi(i0)) {                    /*order exists?*/
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", atoi(i0));
        break;
      }
      i = 0;                                       /*counts different products*/
      j = 0;                                       /*counts order's price*/
      while (i != orders[atoi(i0)].n_diff_prod) {
        j = j + (stock[orders[atoi(i0)].prod_ord[i]].price * orders[atoi(i0)].qtd_ord[i]);
        i = i+1;                                   /*next product in order*/
      }
      printf("Custo da encomenda %d %d.\n", atoi(i0), j);
      break;
/*-------------------alter the price of an existing product-------------------*/
      case 'p':
      if (id_occupied<=atoi(i0)) {                 /*product doesn't exist*/
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", atoi(i0));
        break;
      }
      stock[atoi(i0)].price = atoi(i1);            /*change product price*/
      break;
/*-------------description and quantity of a product in an order--------------*/
      case 'E':
      if (n_orders<=atoi(i0)) {                    /*order exists?*/
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(i0));
        break;
      }
      if (id_occupied<=atoi(i1)) {                 /*product doesn't exist*/
        printf("Impossivel listar produto %d. Produto inexistente.\n", atoi(i1));
        break;
      }
      i = 0;                                       /*counts different products*/
      while (i != orders[atoi(i0)].n_diff_prod) {
        if (orders[atoi(i0)].prod_ord[i]==atoi(i1)) {
          printf("%s %d.\n", stock[atoi(i1)].desc, orders[atoi(i0)].qtd_ord[i]);
        }
        i = i+1;                                   /*next product in order*/
      }
      break;
/*---------------order with most quantity of a single product-----------------*/
      case 'm':
      if (id_occupied<=atoi(i0)) {                 /*product doesn't exist*/
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", atoi(i0));
        break;
      }
      i=n_orders;                                  /*counts different orders*/
      k=0;                                         /*counts most number of products registered*/
      while (i!=0) {
        j=0;                                       /*counts different products in order*/
        while (j!=orders[i].n_diff_prod) {
          if (orders[i].prod_ord[j]==atoi(i0)) {
            if (k<=orders[i].qtd_ord[j]) {
              l = i;                               /*order with most instances of product*/
            }
          }
          j = j+1;                                 /*next product*/
        }
        i = i-1;                                   /*previous order*/
      }
      if (k==0) {                                  /*breaks if there aren't*/
        break;                                     /*any instances of product*/
      }
      printf("Maximo produto %d %d %d.\n", atoi(i0), l, k);
      break;
/*----------all products organized by price least to most expensive-----------*/
      case 'l':
      /*orders the products from lest to most expensive to print them out*/
      i=0;                                         /*counts products in stock*/
      while (i!=id_occupied) {
        j=i+1;                                     /*next product in stock*/
        while (j!=id_occupied) {
          if (stock[i].price > stock[j].price) {   /*is it's price highest?*/
            k=stock[i].price;                      /*saves 1st price*/
            stock[i].price = stock[j].price;       /*stores price in right order*/
            stock[j].price = k;                    /*stores price in right order*/
            k=stock[i].qtd;                        /*saves 1st quantity*/
            stock[i].qtd = stock[j].qtd;           /*stores quantity in right order*/
            stock[j].qtd = k;                      /*stores quantity in right order*/
            strcpy(m, stock[i].desc);              /*stores 1st description*/
            strcpy(stock[i].desc, stock[j].desc);  /*stores description in right order*/
            strcpy(stock[j].desc, m);              /*stores description in right order*/

          }
          j=j+1;                                   /*next product in stock*/
        }
        i = i+1;                                   /*next product in stock*/
      }
      i=0;
      printf("Produtos\n");                        /*prints products ordered by price*/
      while (i!=id_occupied) {
        printf("* %s %d %d\n", stock[i].desc, stock[i].price, stock[i].qtd);
        i = i+1;
      }
      /*this part does the exact same thing as the previous one but*/
      /*instead of ordering the products by price it rearranges them*/
      /*by their id again*/
      i=0;
      while (i!=id_occupied) {
        j=i+1;
        while (j!=id_occupied) {
          if (stock[i].id > stock[j].id) {
            k=stock[i].price;
            stock[i].price = stock[j].price;
            stock[j].price = k;
            k=stock[i].qtd;
            stock[i].qtd = stock[j].qtd;
            stock[j].qtd = k;
            strcpy(m, stock[i].desc);              /*stores 1st description*/
            strcpy(stock[i].desc, stock[j].desc);  /*stores description in right order*/
            strcpy(stock[j].desc, m);              /*stores description in right order*/
          }
          j=j+1;
        }
        i = i+1;
      }
      break;
/*------all products in one order ordered by description alphabetically-------*/
      case 'L':
      if (n_orders<=atoi(i0)) {                    /*order exists?*/
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(i0));
        break;
      }
      i = 0;
      while (i!=orders[atoi(i0)].n_diff_prod) {
        j=i+1;
        while (j!=orders[atoi(i0)].n_diff_prod) {
          if (strcmp(stock[i].desc, stock[j].desc)>0) {
            k = orders[atoi(i0)].prod_ord[i];
            orders[atoi(i0)].prod_ord[i] = orders[atoi(i0)].prod_ord[j];
            orders[atoi(i0)].prod_ord[j] = k;
            k = orders[atoi(i0)].qtd_ord[i];
            orders[atoi(i0)].qtd_ord[i] = orders[atoi(i0)].qtd_ord[j];
            orders[atoi(i0)].qtd_ord[j] = k;
          }
          j=j+1;
        }
        i = i+1;
      }
      i=0;
      printf("Encomenda %d\n", atoi(i0));                        /*prints products ordered by description*/
      while (i!=orders[atoi(i0)].n_diff_prod) {
        if (orders[atoi(i0)].qtd_ord[i]!=0) {
          printf("* %s %d %d\n", stock[orders[atoi(i0)].prod_ord[i]].desc,
              stock[orders[atoi(i0)].prod_ord[i]].price, orders[atoi(i0)].qtd_ord[i]);
        }
        i = i+1;
      }
      break;
    }
  }
  return 0;
}
