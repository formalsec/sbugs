#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Products limit*/
#define MAXPRODUCTS 10000
/*Weight limit*/
#define MAXWEIGHT 200
/*Order limit*/
#define MAXORDERS 500
/*Description limit + 1 for '\0'*/
#define MAXDESCRIPTION 64
/*Command limit - I assumed as 100*/
#define MAXCOMMAND 100
/*Variable to create bidimensional arrays and check the length of the command*/
#define TWO 2


/*Variable where I will save the input line*/
char command[MAXCOMMAND];
/*Variables where I will save the different parts of input*/
int price = 0, weight = 0, quantity = 0, idp = 0, ido = 0;
/*Variables that save the first empty_spot in products_table and orders_table*/
int empty_spot_products_table = 0, empty_spot_orders_table = 0;
int i = 0,j = 0;
/*Variable to show if the product was found or not*/
int product_found = -1;

/*Structure to represent the product*/
struct product {
  int idp;
  char description[MAXDESCRIPTION];
  int price;
  int weight;
  int quantity;
};
typedef struct product product;

/*Structure to represent the order*/
struct order {
  /*Order id*/
  int ido;
  /*Saves the first empty spot in products_in_order*/
  int empty_spot_products_on_orders_table;
  /*Keeps the total weight of the order*/
  int total_weight;
  /*Keeps the total price of the order*/
  int total_price;
  /*Array of products in the order*/
  product products_in_order[MAXWEIGHT];
};
typedef struct order order;

/*Array of products*/
product products_table[MAXPRODUCTS];
/*Array of orders*/
order orders_table[MAXORDERS];

/*Changes all the pharameters of the product in the empty_spot_products_table to the values of input*/
void a () {
  products_table[empty_spot_products_table].idp = empty_spot_products_table;
  strcpy(products_table[empty_spot_products_table].description,strtok(NULL, ":"));
  products_table[empty_spot_products_table].price = atoi(strtok(NULL, ":"));
  products_table[empty_spot_products_table].weight = atoi(strtok(NULL, ":"));
  products_table[empty_spot_products_table].quantity = atoi(strtok(NULL, ":"));
  printf("Novo produto %d.\n",products_table[empty_spot_products_table].idp);
  empty_spot_products_table++;
}

/*Increases the pharameter quantity by quantity units of the product idp in products_table*/
void q () {
  idp = atoi(strtok(NULL, ":"));
  quantity = atoi(strtok(NULL, ":"));
  if (products_table[idp].price == 0) { /*price 0 -> product does not exist*/
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
  }
  products_table[idp].quantity += quantity;
}

/*Puts the idp of the first product in the order to -1 and increases the empty_spot_orders_table*/
void N () {
  printf("Nova encomenda %d.\n", empty_spot_orders_table);
  orders_table[empty_spot_orders_table].products_in_order[0].idp = -1;
  empty_spot_orders_table++;
}

/* Function to search for a product in an order; it returns the value of the product_in_order indice if the product has been found; -1 otherwise*/
int search_product (int product, int order) {
  for (i = 0; i < orders_table[order].empty_spot_products_on_orders_table && i < MAXWEIGHT; i++) {
    if (orders_table[order].products_in_order[i].idp == product && orders_table[order].products_in_order[i].price != 0) {
      return i;
    }
  }
  return -1;
}

/*Add a product in the empty_spot_products_on_orders_table if the product is not in the order or increases the quantity if the product is already in the order*/
void A () {
  /*Variable to check if the limit of weight is exceeded*/
  int possible_weight;
  /*Order id*/
  ido = atoi(strtok(NULL, ":"));
  /*Product id*/
  idp = atoi(strtok(NULL, ":"));
  /*Quantity of product given by the input command*/
  quantity = atoi(strtok(NULL, ":"));
  if (ido < empty_spot_orders_table) { /* ido < empty_spot -> the order already exist*/
    if (idp < empty_spot_products_table) { /* idp < empty_spot -> the product already exist*/
      if (quantity <= products_table[idp].quantity) { /*Quantity is enough*/
        possible_weight = orders_table[ido].total_weight;
        possible_weight += (quantity * products_table[idp].weight);
        if (possible_weight <= MAXWEIGHT) { /*the weight limit is not exceeded*/
          product_found = search_product(idp,ido);
          if (product_found != -1) {
            orders_table[ido].products_in_order[product_found].quantity += quantity;
            products_table[idp].quantity -= quantity;
            orders_table[ido].total_weight += (quantity * orders_table[ido].products_in_order[product_found].weight);
            orders_table[ido].total_price += (quantity * orders_table[ido].products_in_order[product_found].price);
          }
          else { /*Product does not exist in the order*/
            orders_table[ido].products_in_order[orders_table[ido].empty_spot_products_on_orders_table] = products_table[idp];
            orders_table[ido].products_in_order[orders_table[ido].empty_spot_products_on_orders_table].quantity = quantity;
            products_table[idp].quantity -= quantity;
            orders_table[ido].total_weight += (quantity * products_table[idp].weight);
            orders_table[ido].total_price += (quantity * products_table[idp].price);
            orders_table[ido].empty_spot_products_on_orders_table ++;
          }
        }
        else {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ido);
        }
      }
      else {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ido);
      }
    }
    else {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ido);
    }
  }
  else {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ido);
  }
}

/*Reduces the quantity of the product in products_table*/
void r () {
  idp = atoi(strtok(NULL, ":"));
  quantity = atoi(strtok(NULL, ":"));
  if (idp < empty_spot_products_table) {
    if ( (products_table[idp].quantity - quantity) < 0) {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quantity,idp);
    }
    else {
      products_table[idp].quantity -= quantity;
    }
  }
  else {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
  }
}

/*Eliminates the "blank line" created by "pulling" the next lines a number back, when a product is removed from an order*/
void clean_blank_line (int line) {
  for (; line < orders_table[ido].empty_spot_products_on_orders_table-1 && line < MAXWEIGHT-1; line++) {
    orders_table[ido].products_in_order[line] = orders_table[ido].products_in_order[line+1];
  }
  orders_table[ido].empty_spot_products_on_orders_table --;
  strcpy(orders_table[ido].products_in_order[line].description,"");
  orders_table[ido].products_in_order[line].idp = -1;
  orders_table[ido].products_in_order[line].price = 0;
  orders_table[ido].products_in_order[line].weight = 0;
  orders_table[ido].products_in_order[line].quantity = 0;
}

/*Removes a product form the order*/
void R () {
  ido = atoi(strtok(NULL, ":"));
  idp = atoi(strtok(NULL, ":"));
  if (ido < empty_spot_orders_table) { /* < -> order exists*/
    if (idp < empty_spot_products_table) {
      product_found = search_product(idp,ido);
      if (product_found != -1) {
        products_table[idp].quantity += orders_table[ido].products_in_order[i].quantity;
        orders_table[ido].total_weight -= (orders_table[ido].products_in_order[i].quantity * orders_table[ido].products_in_order[product_found].weight);
        orders_table[ido].total_price -= (orders_table[ido].products_in_order[i].quantity * orders_table[ido].products_in_order[product_found].price);
        clean_blank_line(product_found);
      }
    }
    else {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ido);
    }
  }
  else {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ido);
  }
}

/*Prints the pharameter tota_weight of the order*/
void C () {
  ido = atoi(strtok(NULL, ":"));
  if (ido < empty_spot_orders_table) {
    printf("Custo da encomenda %d %d.\n",ido,orders_table[ido].total_price);
  }
  else {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ido);
  }
}

/*Changes the price of the product in the products_table and in all the orders the product is in*/
void p () {
  int order;
  idp = atoi(strtok(NULL, ":"));
  price = atoi(strtok(NULL, ":"));
  if (idp < empty_spot_products_table) {
    products_table[idp].price = price;
    for (order = 0; order < empty_spot_orders_table && order < MAXORDERS; order++) {
      product_found = search_product(idp,order);
      if (product_found != -1) {
        orders_table[order].total_price = orders_table[order].total_price - (orders_table[order].products_in_order[product_found].price * orders_table[order].products_in_order[product_found].quantity);
        orders_table[order].products_in_order[product_found].price = price;
        orders_table[order].total_price += (orders_table[order].products_in_order[product_found].price * orders_table[order].products_in_order[product_found].quantity);
      }
    }
  }
  else {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
  }
}

/*Prints the description and the quantity of the product in the order or prints the description and 0 if the product is not in the order*/
void E () {
  ido = atoi(strtok(NULL, ":"));
  idp = atoi(strtok(NULL, ":"));
  if (idp < empty_spot_products_table) {
    if (ido < empty_spot_orders_table) {
      product_found = search_product(idp,ido);
      if (product_found != -1) {
        printf("%s %d.\n", orders_table[ido].products_in_order[product_found].description, orders_table[ido].products_in_order[product_found].quantity);
      }
      else {
        printf("%s 0.\n",products_table[idp].description);
      }
    }
    else {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ido);
    }
  }
  else {
    printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
  }
}

/*Search in every products_in_order array in every order in the orders_table to see the highest quantity*/
void m () {
  /*Variables to save the highest quantity and the order with the highest quantity*/
  int max_ido = -1, max_quantity = -1;
  int order = 0;
  idp = atoi(strtok(NULL, ":"));
  if (idp < empty_spot_products_table) {
    for (order = 0; order < empty_spot_orders_table && order < MAXORDERS; order++) {
      product_found = search_product(idp,order);
      if (product_found != -1 && orders_table[order].products_in_order[product_found].quantity > max_quantity) {
        max_quantity = orders_table[order].products_in_order[product_found].quantity;
        max_ido = order;
      }
    }
    if (max_ido != -1) {
      printf("Maximo produto %d %d %d.\n",idp,max_ido,max_quantity);
    }
  }
  else {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
  }
}

/*Fills the auxiliar array with all the idps and prices of the products*/
void read_idp_and_price (int array[MAXPRODUCTS][TWO]) {
  for (i = 0; i < empty_spot_products_table && i < MAXPRODUCTS; i++) {
    array[i][0] = products_table[i].idp;
    array[i][1] = products_table[i].price;
  }
}

/*Orders by price the auxiliar array*/
void price_sort (int array[MAXPRODUCTS][TWO]) {
  int price_aux,idp_aux;
  for (i = 0; i < empty_spot_products_table-1 && i < MAXPRODUCTS-1; i++) {
    for (j = i+1; j < empty_spot_products_table && j < MAXPRODUCTS; j++) {
      if (array[i][1] > array[j][1] || (array[i][1] == array[j][1] && array[i][0] > array[j][0])) {
        idp_aux = array[i][0];
        price_aux = array[i][1];
        array[i][0] = array[j][0];
        array[i][1] = array[j][1];
        array[j][0] = idp_aux;
        array[j][1] = price_aux;
      }
    }
  }
}

/*Prints all the idps and prices in the auxilar array*/
void print_sort_by_price (int array[MAXPRODUCTS][TWO]) {
  printf("Produtos\n");
  for (i = 0; i < empty_spot_products_table && i < MAXPRODUCTS; i++) {
    printf("* %s %d %d\n",products_table[array[i][0]].description,products_table[array[i][0]].price,products_table[array[i][0]].quantity);
  }
}

/*Creates an auxiliar array to sort by price and calls the functions read_idp_and_price, price_sort and print_sort_by_price*/
void l() {
  int sort_by_price[MAXPRODUCTS][TWO];
  read_idp_and_price(sort_by_price);
  price_sort(sort_by_price);
  print_sort_by_price(sort_by_price);
}

/*Creates auxiliar strucutures and arrays and dorts by description the products in the order*/
void L () { /*The idp used in this functions is the indice of the product in the order, not the idp of the system*/
  /*Structure to save the description and the idp_in_order of the product at the same time*/
  struct idp_and_description {
    /*Variable that represents the indice of the product in the product_in_order array*/
    int idp_in_order;
    char description[MAXDESCRIPTION];
  };
  typedef struct idp_and_description idp_and_description;
  /*Array of structures to sort by description*/
  idp_and_description alphabetical_order[MAXWEIGHT];
  /*Auxiliar description used to change to elements of the array above*/
  char aux_description[MAXDESCRIPTION];
  /*Auxiliar identificador used to change to elements of the array above*/
  int aux_idp;

  ido = atoi(strtok(NULL, ":"));

  if (ido < empty_spot_orders_table) {
    /*Cycle to fill the auxiliar array of structures*/
    for (i=0; i < orders_table[ido].empty_spot_products_on_orders_table && i < MAXWEIGHT; i++) {
      alphabetical_order[i].idp_in_order = i;
      strcpy(alphabetical_order[i].description, orders_table[ido].products_in_order[i].description);
    }

    /*Cycle to sort the auxiliar array*/
    for (i = 0; i < orders_table[ido].empty_spot_products_on_orders_table-1 && i < MAXWEIGHT-1; i++) {
      for (j = i+1; j < orders_table[ido].empty_spot_products_on_orders_table-1 && j < MAXWEIGHT-1; j++) {
        if (strcmp(alphabetical_order[i].description,alphabetical_order[j].description) > 0) {
          strcpy(aux_description,alphabetical_order[i].description);
          aux_idp = alphabetical_order[i].idp_in_order;
          strcpy(alphabetical_order[i].description,alphabetical_order[j].description);
          alphabetical_order[i].idp_in_order = alphabetical_order[j].idp_in_order;
          strcpy(alphabetical_order[j].description,aux_description);
          alphabetical_order[j].idp_in_order = aux_idp;
        }
      }
    }

    /*Things to print the sorted array*/
    printf("Encomenda %d\n",ido);
    for (i=0; i < orders_table[ido].empty_spot_products_on_orders_table && i < MAXWEIGHT; i++) {
      printf("* %s %d %d\n",alphabetical_order[i].description, orders_table[ido].products_in_order[alphabetical_order[i].idp_in_order].price, orders_table[ido].products_in_order[alphabetical_order[i].idp_in_order].quantity);
    }
  }
  else {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ido);
  }
}

/*Reads MAXCOMMAND values from stdin and inserts them into the vector command*/
char* read_command () {
  char *first_character;
  fgets(command,MAXCOMMAND,stdin);
  if (strlen(command) == TWO) { first_character = strtok(command,"\n"); }
  else { first_character = strtok(command," "); }
  return first_character;
}

/*Calls a function according to the first_character of the command*/
int main () {
  char* letter;
  for (;;) {
    letter = read_command();
    if (strcmp(letter,"x") == 0) { break; }
    else if (strcmp(letter,"a") == 0) { a(); }
    else if (strcmp(letter,"q") == 0) { q(); }
    else if (strcmp(letter,"N") == 0) { N(); }
    else if (strcmp(letter,"A") == 0) { A(); }
    else if (strcmp(letter,"r") == 0) { r(); }
    else if (strcmp(letter,"R") == 0) { R(); }
    else if (strcmp(letter,"C") == 0) { C(); }
    else if (strcmp(letter,"p") == 0) { p(); }
    else if (strcmp(letter,"E") == 0) { E(); }
    else if (strcmp(letter,"m") == 0) { m(); }
    else if (strcmp(letter,"l") == 0) { l(); }
    else if (strcmp(letter,"L") == 0) { L(); }
  }
  return 0;
}
