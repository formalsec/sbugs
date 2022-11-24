#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Constants */
#define MAX_INFO 4
#define MAX 64
#define MAX_ORDERS_PRODUCTS 10000
#define MAX_ORDERS 500
#define MAX_ORDER_WEIGHT 200

/* Structs for products and orders  */
typedef struct products {
  char description[MAX];
  int price, weight, quantity, id, orderQuantity;
} Product;

typedef struct orderInfo {
  int index, quantity;
} orderInfo;

typedef struct orders {
  int ide, weight, index, quantity;
  orderInfo products[MAX_ORDERS_PRODUCTS];
} Order;


/* Global */
Product products[MAX_ORDERS_PRODUCTS];
Order orders[MAX_ORDERS];
char arg1[MAX];
int arg2, arg3, arg4;
int productCount = 0;
int orderCount = 0;


/* Initialize products list and orders list at -1 or 0 and an empty string for products list */
void init() {
  int i, j;

  for (i = 0; i < MAX_ORDERS_PRODUCTS; i++) {
    products[i].price = products[i].weight = products[i].quantity = 0;
    products[i].id = -1;
  }

  for (i = 0; i < MAX_ORDERS; i++) {
    orders[i].ide = -1;
    orders[i].weight = orders[i].index = orders[i].quantity = 0;
    for (j = 0; j < MAX_ORDERS_PRODUCTS; j++) {
      orders[i].products[j].index = -1;
      orders[i].products[j].quantity = 0;
    }
  }
}


/* Takes an id and search if a product with this id exists, returning the product index
   if found or returns -1 in case the product with this id doesn't exists*/
int searchProduct(int id) {
  int i;

  for (i = 0; i < MAX_ORDERS_PRODUCTS; i++) {
    if (products[i].id == id)
      return i;
  }
  return -1;
}

/* Takes and id and search if an order with this id exists, returning the order index
   if found or return -1 in case the order with this id doesn't exists*/
int searchOrder(int id) {
  int i;

  for (i = 0; i < MAX_ORDERS; i++) {
    if (orders[i].ide == id)
      return i;
  }
  return -1;
}


/* Adds a product to the produts list, being:
arg1 = description
arg2 = price
arg3 = weight
arg4 = quantity
taken from the user input */
void addProduct() {
  if (productCount < MAX_ORDERS_PRODUCTS) { /* checks if the product count is lesser than the available */
    strcpy(products[productCount].description, arg1);
    products[productCount].price = arg2;
    products[productCount].weight = arg3;
    products[productCount].quantity = arg4;
    products[productCount].id = productCount;

    printf("Novo produto %d.\n", productCount);
    productCount++;
  }
  else
    return;
}


/* checks if a product exists in the stock and adds more units to this product stock
   in case the product doesn't exists it generates an error */
void addStock() {
  int iProduct;
  iProduct = searchProduct(arg2); /* function used to search a product and returns -1 if it doesn't exists */

  if (iProduct != -1)
    products[iProduct].quantity += arg3;
  else
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", arg2);
}


/* receives and order id and a product id and search if the product is in this specific order */
int searchProductInOrder(int iOrder, int idp) {
  int i = 0;

  while (orders[iOrder].products[i].index != -1) {
    if (products[orders[iOrder].products[i].index].id == idp)
      return i;
    i++;
  }
  return -1;
}


/* This function checks if the received order and product id exists (generates an error if any of those does not exists),
   then checks if the quantity available at the stock is enough to add to the order (generates an error if the quantity is not available),
   then checks if it is lower than the allowed max weight in an order */
void addProductToOrder() {
  int iProduct, iOrder, weight, aux,  idp = arg3, ide = arg2, qtd = arg4;

  iProduct = searchProduct(idp);
  iOrder = searchOrder(ide);

  if (iProduct != -1) { /* checks if product exists */
    if (iOrder != -1) { /* checks if order exists */
      if (products[iProduct].quantity >= qtd) { /* checks if the quantity available is enough */
        weight = qtd * products[idp].weight; /* calculates the weight only after checking the previous requirement */
        if ((orders[ide].weight + weight) <= MAX_ORDER_WEIGHT) { /* checks if the actual order weight plus the weight being added is lower than the max weight */
          aux = searchProductInOrder(iOrder, idp);  /* finds if the product is already in the order */
          if (aux != -1) {
            orders[iOrder].products[aux].quantity += qtd; /* adds in the same product quantity if it was already in the order before */
          }
          else {
            orders[iOrder].quantity++;
            orders[iOrder].products[orders[iOrder].index].index = iProduct; /* if the product wasn't in the order, creates the product in this order */
            orders[iOrder].products[orders[iOrder].index++].quantity += qtd; /* adds the product quantity in the order */
          }
          orders[iOrder].weight += weight; /* adds the weight to the order */
          products[iProduct].quantity -= qtd; /* remove the quantity added to the order from the stock */
        }
        else  /* ERRORS BELOW */
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
      }
      else
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
}


/* checks if the order and the product exists, then checks if the product is in the order and remove the product from the order */
void removeProductFromOrder() {
  int ide = arg2, idp = arg3;
  int iProduct = searchProduct(idp), iOrder = searchOrder(ide), aux = 0;

  if (iOrder != -1) { /* checks if the order exists */
      if (iProduct != -1) { /* checks if the product exists */
        aux = searchProductInOrder(iOrder, idp); /* checks if the product is in the order */
        if (aux != -1) {
          orders[iOrder].weight = orders[iOrder].weight - (orders[iOrder].products[aux].quantity * products[iProduct].weight); /* removes weight from the order */
          products[iProduct].quantity += orders[iOrder].products[aux].quantity; /* removes the product quantity from the order */
          orders[iOrder].products[aux].quantity= 0; /* set the product quantity in the order to 0 */
        }
      }
      else /* ERRORS BELOW */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  }
  else
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}


/* calculates a specific order price */
void orderPrice() {
  int iOrder, total, ide = arg2, i = total = 0;
  iOrder = searchOrder(ide);

  if (iOrder != -1) { /* checks if the order exists */
    while (orders[iOrder].products[i].index != -1) { /* search all products in the order */
      total += (products[orders[iOrder].products[i].index].price * orders[iOrder].products[i].quantity); /* add to the total variable the price * quantity of each product*/
      i++;
    } /* then prints the order price */
    printf("Custo da encomenda %d %d.\n", iOrder, total);
  }
  else /* ERROR BELOW */
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}


/* lists the info of a specific product in an order if both exists */
void returnInfo() {
  int iOrder, iProduct, ide = arg2, idp = arg3;
  iOrder = searchOrder(ide);
  iProduct = searchProduct(idp);

  if (iOrder != -1) { /* checks if the order exists */
    if (iProduct != -1) { /* checks if the product exists */
      iProduct = searchProductInOrder(iOrder, idp); /* search if the product is in the order */
      if (iProduct != -1) /* if the product is in the order ir returns the product description and the quantity in this order */
        printf("%s %d.\n", products[orders[iOrder].products[iProduct].index].description, orders[iOrder].products[iProduct].quantity);
      else /* if the product is not in the order, it returns the product description and a 0 because the product wasn't in this order */
        printf("%s %d.\n", products[idp].description, 0);
    }
    else /* ERRORS ABOVE */
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  }
  else
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}


/* creates a new order and increases the orderCount global variable */
void createOrder() {
  if (orderCount < MAX_ORDERS) { /* checks if the orderCount is less than the max orders  */
    orders[orderCount].ide = orderCount; /* then creates the new order */

    printf("Nova encomenda %d.\n", orderCount);
    orderCount++;
  }
}


/* checks in which order an specific products is with larger quantity, if it has the same quantity in more than one order, it
   returns the one with the lowest id */
void mostFrequentProduct() {
  int i = 0, freq, ide, iProduct, j = 0, idp = arg2;
  iProduct = searchProduct(idp);
  freq = 0; /* variable to count the frequency */

  if (iProduct != -1) { /* checks if the product exists */
    while (orders[i].ide != -1 && i < MAX_ORDERS) { /* runs throught all the orders */
      j = 0;
      while (orders[i].products[j].index != -1 && j < MAX_ORDERS_PRODUCTS) { /* checks all the products in the order */
        if (products[orders[i].products[j].index].id == idp) { /* if the product is in the order the cycle is through */
          if (freq < orders[i].products[j].quantity) { /* checks if it has a quantity higher than the previous one */
            freq = orders[i].products[j].quantity; /* if so, changes tthe frequency variable and set the ide variable to the order the product is */
            ide = i;
          }
          break;
        }
        j++;
      }
      i++;
    }

    if (freq != 0) /* if the products has greater than or equal to one quantity in the order */
      printf("Maximo produto %d %d %d.\n", idp, ide, freq);
  }
  else /* ERROR BELOW */
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}


/* removes a specific amount of quantity of an specific product if the quantity is less or equal than the available in stock */
void removeStock() {
  int iProduct, id = arg2, qtd = arg3;
  iProduct = searchProduct(id);

  if (iProduct == -1) /* checks if the product does not exists */
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
  else { /* if the product exists */
    if (products[iProduct].quantity < qtd) /* checks if the quantity given is higher than the quantity available in stock */
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id); /* ERROR */
    else { /* removes the quantity from the stock */
      products[iProduct].quantity -= qtd;
    }
  }
}


/* changes the price of an specific product */
void changePrice() {
  int i = 0, id = arg2, price = arg3;

  while (products[i].id != id) { /* checks if the product exists */
    if (i < MAX_ORDERS_PRODUCTS)
      i++;
    else { /* ERROR */
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
      return;
    }
  }
  products[i].price = price; /* changes the product price */
}


/* function used in sort command 'l' to print the sorted list */
void printArray(int arr[], int n) {
    int i;
    printf("Produtos\n");
    for (i = 0; i < n; i++) {
      if (arr[i] != -1)
        printf("* %s %d %d\n", products[arr[i]].description, products[arr[i]].price, products[arr[i]].quantity);
    }
}

/* insertion sort to sort products by price */
void insertionSortPrice(int arr[], int n) {
    int i, key, j;

    for (i = 1; i < n; i++) {
      if (arr[i] != -1) {
        key = arr[i];
        j = i - 1;
        /* move elements of arr[0, i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && products[arr[j]].price > products[key].price) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
      }
    }
}

/* function of the insertion sort to list products by price */
void listProducts() {
  int arr[MAX_ORDERS_PRODUCTS], i = 0;
  int n = sizeof(arr) / sizeof(arr[0]);

  for (i = 0; i < n; i++)
    arr[i] = products[i].id; /* adds the ids to the array that will be sorted */

  insertionSortPrice(arr, n);
  printArray(arr, n);
}


/*  */
int searchPrice(char descr[], int iOrder) {
  int i, price;

  for (i = 0; i < MAX_ORDERS_PRODUCTS; i++) {
    if (!strcmp(descr, products[orders[iOrder].products[i].index].description)) {
      price = products[orders[iOrder].products[i].index].price;
      return price;
    }
  }
  return -1;
}

int searchQuantity(char descr[], int iOrder) {
  int i, quantity;

  for (i = 0; i <MAX_ORDERS_PRODUCTS; i++) {
    if (!strcmp(descr, products[orders[iOrder].products[i].index].description)) {
      quantity = orders[iOrder].products[i].quantity;
      return quantity;
    }
  }
  return -1;
}


void listProductsFromOrder() {
  int ii=0, j=0, ide = arg2, iOrder, idp;
  Product ev[MAX_ORDERS_PRODUCTS], eve_aux;
  iOrder = searchOrder(ide);

  if (iOrder == -1)
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  else {
    for (ii = 0; ii < orders[iOrder].quantity ; ii++) {
      ev[ii] = products[orders[iOrder].products[ii].index];
      /*printf("%d\n", orders[iOrder].quantity);*/
    }

    for (ii = 1; ii < orders[iOrder].quantity; ii++) {
      eve_aux = ev[ii], j = ii - 1;

      while (j >= 0 && (strcmp(ev[j].description, eve_aux.description) > 0)) {
          ev[j+1] = ev[j];
          j--;
      }
      ev[j+1] = eve_aux;
    }

    printf("Encomenda %d\n", iOrder);
    for (ii = 0; ii < orders[iOrder].quantity; ii++) {
      idp = searchProductInOrder(iOrder, ev[ii].id);
      if (idp != -1 && orders[iOrder].products[idp].quantity > 0) {
        printf("* %s %d %d\n", ev[ii].description, ev[ii].price, orders[iOrder].products[idp].quantity);
      }
    }
  }
}


/* main function that init all the arrays and get the user choice */
int main() {
  char choice;
  init();

  while ((choice = getchar()) != 'x' && choice != EOF) { /* runs the program until the given command is x */
    switch(choice) {
      case'a':
        scanf(" %[^:]:%d:%d:%d", arg1, &arg2, &arg3, &arg4);
        addProduct();
        break;
      case'q':
        scanf("%d:%d", &arg2, &arg3);
        addStock();
        break;
      case'N':
        createOrder();
        break;
      case'A':
        scanf("%d:%d:%d", &arg2, &arg3, &arg4);
        addProductToOrder();
        break;
      case'r':
        scanf("%d:%d", &arg2, &arg3);
        removeStock();
        break;
      case'R':
        scanf("%d:%d", &arg2, &arg3);
        removeProductFromOrder();
        break;
      case'C':
        scanf("%d", &arg2);
        orderPrice();
        break;
      case'p':
        scanf("%d:%d", &arg2, &arg3);
        changePrice();
        break;
      case'E':
        scanf("%d:%d", &arg2, &arg3);
        returnInfo();
        break;
      case'm':
        scanf("%d", &arg2);
        mostFrequentProduct();
        break;
      case'l':
        listProducts();
        break;
      case'L':
        scanf("%d", &arg2);
        listProductsFromOrder();
        break;
    }
  }
  return 0;
}
