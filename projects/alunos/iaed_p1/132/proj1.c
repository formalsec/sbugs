#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Maximum number of values stored */
#define MAX_PRODUCTS 10000
#define MAX_ORDERS 500
#define MAX_WEIGHT 200
#define MAX_DESCRIPTION 63

/* Struct to save a product's data */
typedef struct a{
  int id, price, weight, stock;
  char description[MAX_DESCRIPTION];
} Product;

/* Struct to save a products data inside an order */
typedef struct b{
  int id, quantity;
} ProductInOrder;

/* Struct to save an order's content */
typedef struct c{
  int id, weight, price, num_of_prods;
  ProductInOrder orderProducts[MAX_WEIGHT];
} Order;

/* Array of products */
Product allProducts[MAX_PRODUCTS] = {0};

/* Array of orders */
Order allOrders[MAX_ORDERS] = {0};

/* Number of products stored and orders placed */
int countProd = 0, countOrd = 0;

/* Function that initializes all order id's as -1 */
void initOrder(){
  int i;
  for (i=0; i < MAX_ORDERS; i++){
    allOrders[i].id = -1;
  }
}

/* Function that returns the number of products inside a given order */
int getNumOfProds(int orderId){
  return allOrders[orderId].num_of_prods;
}

/* Function that deletes a struct from an array of structs */
void deleteStruct(int orderId ,int index){
  int i;
  for (i=index; i < MAX_WEIGHT-1; i++){
    allOrders[orderId].orderProducts[i].id = allOrders[orderId].orderProducts[i+1].id;
    allOrders[orderId].orderProducts[i].quantity = allOrders[orderId].orderProducts[i+1].quantity;
  }
}

/* Funtction that copies a struct's data onto another (structs of the type Product) */
void copyStructsProducts(Product dest[], int destIndex, Product src[], int srcIndex){
  /* Copy data from source product to the destination product */
  memmove(dest[destIndex].description, src[srcIndex].description, strlen(src[srcIndex].description) +1);
  dest[destIndex].price = src[srcIndex].price;
  dest[destIndex].id = src[srcIndex].id;
  dest[destIndex].weight = src[srcIndex].weight;
  dest[destIndex].stock = src[srcIndex].stock;
}

/* Funtction that copies a struct's data onto another (structs of the type ProductInOrder) */
void copyStructsOrders(ProductInOrder dest[], int destIndex, ProductInOrder src[], int srcIndex){
  /* Copy data from source product to the destination product */
  dest[destIndex].id = src[srcIndex].id;
  dest[destIndex].quantity = src[srcIndex].quantity;
}

/* Funtction that swaps two structs of the type Product */
void swapStructs(Product v[], int a, int b){
  Product temporary[1] = {0};
  /* Temporary = b */
  copyStructsProducts(temporary,0,v,b);
  /* b = a */
  copyStructsProducts(v,b,v,a);
  /* a = temporary */
  copyStructsProducts(v,a,temporary,0);
}

void swapStructsDescription(ProductInOrder v[], int a, int b){
  ProductInOrder temporary;

  /* Temporary = b */
  temporary.id = v[b].id;
  temporary.quantity = v[b].quantity;
  /* b = a */
  v[b].id = v[a].id;
  v[b].quantity = v[a].quantity;
  /* a = temporary */
  v[a].id = temporary.id;
  v[a].quantity = temporary.quantity;

}

/* Function that adds a new product to the system */
void addProduct(){

  /*Collect all the products data and store it inside the struct*/
  allProducts[countProd].id = countProd;
  scanf(" %[^:]:%d:%d:%d", allProducts[countProd].description,
                  &allProducts[countProd].price, &allProducts[countProd].weight,
                  &allProducts[countProd].stock);
  printf("Novo produto %d.\n", countProd);
  /* Uptade product counter */
  countProd++;
}

/* Funtction that adds stock to an already existing product */
void addStock(){
  int addId, addQuantity, i;
  scanf("%d:%d", &addId, &addQuantity);
  /* Check if the product is registered in the system */
  if (allProducts[addId].price == 0){
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",
                                                      addId);
  }
  /* Product is registered, proceed to add stock. */
  else{
    /* Cycle through all products until we get to the wanted product id */
    for (i=0; i < countProd; i++){
      if (allProducts[i].id == addId){
        allProducts[i].stock += addQuantity;
        break;
      }
    }
  }
}

/* Function that places a new order */
void createOrder(){
  /* New order placed */
  allOrders[countOrd].id = countOrd;
  allOrders[countOrd].weight = 0;
  printf("Nova encomenda %d.\n", allOrders[countOrd].id);
  countOrd++;
}

/* Funtction that calculates the weight of a given amount of product */
int calcWeight(int idp, int qtt){
  int individualWeight,i;
  /* Cycle through all products until we get to the wanted product id */
  for (i=0; i < countProd; i++){
    if (allProducts[i].id == idp){
      /* Get a product's weight */
      individualWeight = allProducts[i].weight;
      break;
    }
  }
  /* Return the weight of a certain amount of product */
  return qtt*individualWeight;
}

/* Function that returns the stock of a given product */
int getStock(int idp){
  int i;
  /* Cycle through all products until we get to the wanted product id */
  for (i=0; i < countProd; i++){
    if (allProducts[i].id == idp){
      return allProducts[i].stock;
    }
  }
  return 0;
}

/* Function that reduces the stock of a given product (for abstraction purposes) */
void reduceStock(int idp, int removeQuantity){
  int i;
  for (i=0; i < countProd; i++){
    if (allProducts[i].id == idp){
      allProducts[i].stock -= removeQuantity;
      break;
    }
  }
}

/* Function that returns the price of a certain amount of product */
int getPrice(int idp, int qtt){
  int individualPrice,i;
  /* Get a product's price */
  for (i=0; i < countProd; i++){
    if (allProducts[i].id == idp){
      individualPrice = allProducts[i].price;
    }
  }
  return individualPrice*qtt;
}

/* Function that adds a product to an already existing order */
void addProduct_2_Order(int orderId, int productId, int productQuantity){
  int i, checker=0, id2Add;
  /*Check if the the chosen order exists */
  if (allOrders[orderId].id == -1){
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",
            productId, orderId);
  }

  /* Check if the chosen product exists */
  else if (allProducts[productId].price == 0){
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",
            productId, orderId);
  }

  /* Check if there is stock available for the chosen product */
  else if (productQuantity > getStock(productId)){
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",
            productId, orderId);
  }

  /* Check if the orders weight exceeds the limit */
  else if (allOrders[orderId].weight + calcWeight(productId, productQuantity) > MAX_WEIGHT){
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",
            productId, orderId);
  }
  else{
    for (i=0; i < getNumOfProds(orderId); i++){
      if (allOrders[orderId].orderProducts[i].id == productId){
        checker = 1;
        id2Add = i;
        break;
      }
    }
    if (checker == 0){
      allOrders[orderId].num_of_prods += 1;
      /* Changes the order's overall cost */
      allOrders[orderId].price += getPrice(productId, productQuantity);
      /* Add the products weight to the order */
      allOrders[orderId].weight += calcWeight(productId, productQuantity);
      /* Remove the orders quantity from the products stock */
      reduceStock(productId, productQuantity);
      /* Store the product in the order */
      allOrders[orderId].orderProducts[getNumOfProds(orderId)-1].id = productId;
      allOrders[orderId].orderProducts[getNumOfProds(orderId)-1].quantity = productQuantity;
    }
    else{
      /* Changes the order's overall cost */
      allOrders[orderId].price += getPrice(productId, productQuantity);
      /* Add the products weight to the order */
      allOrders[orderId].weight += calcWeight(productId, productQuantity);
      /* Remove the orders quantity from the products stock */
      reduceStock(productId, productQuantity);
      /* Store the product in the order */
      allOrders[orderId].orderProducts[id2Add].quantity += productQuantity;
    }
  }
}

/* Function that removes stock from an already existing product */
void removeStock(){
  int removeId, removeQuantity;
  scanf("%d:%d", &removeId, &removeQuantity);

  if (allProducts[removeId].price == 0){
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n",
            removeId);
  }

  else if (getStock(removeId)-removeQuantity < 0){
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",
            removeQuantity, removeId);
  }
  else{
    reduceStock(removeId,removeQuantity);
  }
}

/* Function that removes a product from an order */
void removeProduct(int orderId, int productId){
  int removeQuantity, i, j;

  if (allOrders[orderId].id == -1){
    /* Order doesn't exist */
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",
            productId, orderId);
  }
  else if (allProducts[productId].price == 0){
    /* Product doesn't exist in the system */
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",
            productId, orderId);
  }
  else{
    /* Cycle through the products in the order */
    for (i=0; i < MAX_WEIGHT; i++){
      if (allOrders[orderId].orderProducts[i].id == productId && allOrders[orderId].orderProducts[i].quantity != 0){
        allOrders[orderId].num_of_prods -= 1;
        /* Registers ao much quantity the product had in the order */
        removeQuantity = allOrders[orderId].orderProducts[i].quantity;
        /* Reduces the order's weight according to the removed products */
        allOrders[orderId].weight -= calcWeight(productId, removeQuantity);
        /* Return products quantity to general stock */
        for (j=0; j < countProd; j++){
          if (allProducts[j].id == productId){
            allProducts[j].stock += removeQuantity;
          }
        }
        /* Adjusts order's overall cost according to the removed products */
        allOrders[orderId].price -= getPrice(productId, removeQuantity);
        /* Remove product from the order */
        deleteStruct(orderId,i);
        break;
      }
    }
  }
}

/* Function that returns an order's total cost */
void getOrderCost(){
  int orderId;
  scanf("%d", &orderId);
  if (allOrders[orderId].id == -1){
    /* Order doesn't exist */
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",
            orderId);
  }
  else{
    printf("Custo da encomenda %d %d.\n", orderId, allOrders[orderId].price);
  }
}

/* Function that changes the price of an already existing product */
void changePrice(){
  int productId, newPrice, quantity,i,j, inicialPrice, totalDifference;
  /* Get the products information */
  scanf("%d:%d", &productId, &newPrice);
  /* Check if the product exists */
  if (allProducts[productId].price == 0){
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",
            productId);
  }
  /* At this point we're dealing with an existing product */
  else{

    for (i=0; i < countProd; i++){
      if (allProducts[i].id == productId){
        /* Get the product's inicial price */
        inicialPrice = allProducts[i].price;
        /* Changes the internal product price */
        allProducts[i].price = newPrice;
      }
    }
    /* Update all the order's price according to the new product price */
    for (i=0; i < countOrd; i++){
      for (j=0; j < MAX_WEIGHT; j++){
        if ((allOrders[i].orderProducts[j].id) == productId){
          /* Get the quantity of the wanted product in the given order */
          quantity = allOrders[i].orderProducts[j].quantity;
          /* Calculate total difference in price */
          totalDifference = (newPrice - inicialPrice)*quantity;
          /* Change order's total price */
          allOrders[i].price += totalDifference;
          break;
        }
      }
    }
  }
}

/* Funtction that prints a product's description as well as it's quantity in a given order */
void giveDescription(){
  int orderId, productId,i, productQuantity=0;
  char productDescription[MAX_DESCRIPTION];
  /* Get information of the product we want the description */
  scanf("%d:%d", &orderId, &productId);
  /* Copy product's description into a variable */
  if (allOrders[orderId].id == -1){
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",
            orderId);
  }
  /* Product doesn't exist */
  else if (allProducts[productId].price == 0){
    printf("Impossivel listar produto %d. Produto inexistente.\n",
            productId);
  }
  /* At this point we're dealing with an existing order and product */
  else{
    for (i=0;i <= getNumOfProds(orderId);i++){
      /* Check if the product is in the order */
      if ((allOrders[orderId].orderProducts[i].id) == productId){
        productQuantity = allOrders[orderId].orderProducts[i].quantity;
        break;
      }
    }
    for (i=0; i < countProd; i++){
      if (allProducts[i].id == productId){
        memmove(productDescription,allProducts[i].description,strlen(allProducts[i].description)+1);
      }
    }
    /* If the given product isn't in the order, print product quantity = 0 */
    printf("%s %d.\n",productDescription, productQuantity);
  }
}

/* Function that returns the order where a given product exists in the biggest quantity */
void maxOccurrence(){
  int productId, biggestOrder, biggestQuantity=0, i, j;
  /* Get product id from the product we want to check */
  scanf("%d", &productId);
  /* Check if the product exists */
  if (allProducts[productId].price == 0){
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",
            productId);
  }
  /* At this point we know the product exists */
  else{
    /* Loop through orders */
    for (i=0; i < countOrd; i++){
      /* Loop through products inside orders */
      for (j=0; j <= getNumOfProds(i); j++){
        /* Check if an order contains the product we want */
        if ((allOrders[i].orderProducts[j].id) == productId){
          /* Wanted product is in order, check if it has the biggest quantity */
          if ((allOrders[i].orderProducts[j].quantity) > biggestQuantity){
            /* The current order contains the biggest quantity, swap variable values */
            biggestQuantity = allOrders[i].orderProducts[j].quantity;
            biggestOrder = i;
            break;
          }
        }
      }
    }
    /* If the product does not occur in any order don't print anything */
    if (biggestQuantity > 0){
      printf("Maximo produto %d %d %d.\n",productId,biggestOrder,biggestQuantity);
    }
  }
}

/* Insertion sort algorithm that sorts products by their prices (lowest to highest) */
void insertionSortPrice(Product a[], int left, int right){
  int i,j;
  /* Auxiliar product (array so that we can use the function copyStructsProducts) */
  Product aux[1] = {0};
  for (i=left+1; i<=right; i++){
    copyStructsProducts(aux,0,a,i);
    j = i-1;
    /* If both prices are equal, the algorithm chooses the one with the lowest product id */
    while ((j >= left && (aux[0].price < a[j].price)) || (j >= left && aux[0].price == a[j].price && aux[0].id < a[j].id))
    {
      copyStructsProducts(a,j+1,a,j);
      j--;
    }
    copyStructsProducts(a,j+1,aux,0);
  }
}

/* Function that sorts all the products on the system from the lowest to the highest price */
void sortByPrice(){
  int i;
  /* Sort products in the system */
  insertionSortPrice(allProducts,0,countProd-1);
  /* Cycle through the sorted products and print them */
  printf("Produtos\n");
  for(i=0; i < countProd; i++){
      printf("* %s %d %d\n", allProducts[i].description, allProducts[i].price, allProducts[i].stock);
  }
}

/* Insertion sort algorithm that sorts the products in an order by their descriptions (lowest to highest) */
void insertionSortDescription(ProductInOrder a[], int left, int right){
  int i,j;
  /* Auxiliar product in order struct (array so that we can use the function copyStructsOrders) */
  ProductInOrder aux[1] = {0};
  for (i=left+1; i<=right; i++){
    copyStructsOrders(aux,0,a,i);
    j = i-1;
    /* Use strcmp() to sort the descriptions by alphabetical order */
    while (j >= left && (strcmp(allProducts[aux[0].id].description, allProducts[a[j].id].description)) < 0){
      copyStructsOrders(a,j+1,a,j);
      j--;
    }
    copyStructsOrders(a,j+1,aux,0);
  }
}

/* Function that sorts the product in an order by their description */
void sortByDescription(){
  int orderId, i;
  scanf("%d", &orderId);
  /* Check if the order exists */
  if (allOrders[orderId].id == -1){
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",
            orderId);
  }
  else{
    /* Sort products in a given order */
    insertionSortDescription(allOrders[orderId].orderProducts, 0, getNumOfProds(orderId)-1);
    printf("Encomenda %d\n", orderId);
    /* Cycle through the sorted products */
    for(i=0; i < getNumOfProds(orderId); i++){
      printf("* %s %d %d\n", allProducts[allOrders[orderId].orderProducts[i].id].description,
              allProducts[allOrders[orderId].orderProducts[i].id].price, allOrders[orderId].orderProducts[i].quantity);
    }
  }
}

int main(){
  int productQuantity, orderId, productId;
  char c;
  initOrder();
  do{
    switch (c = getchar()){
        /* Add a product to the system */
        case 'a':
          addProduct();
          break;
        /* Add stock to a product already in the system */
        case 'q':
          addStock();
          break;
        /* Creates a new order */
        case 'N':
          createOrder();
          break;
        /* Add a product to an already existing order */
        case 'A':
          /* Collect order and products information */
          scanf("%d:%d:%d", &orderId, &productId, &productQuantity);
          addProduct_2_Order(orderId, productId, productQuantity);
          break;
        /* Removes stock from an already existing product */
        case 'r':
          removeStock();
          break;
        /* Removes a product from an already existing order */
        case 'R':
          /* Collect order and products information */
          scanf("%d:%d", &orderId, &productId);
          removeProduct(orderId, productId);
          break;
        /* Returns an order's overall cost */
        case 'C':
          getOrderCost();
          break;
        /* Changes price of a given product */
        case 'p':
          changePrice();
          break;
        /* Prints the amount of a given product in a given order */
        case 'E':
          giveDescription();
          break;
        /* Prints the highest occurrence of a given product in all orders */
        case 'm':
          maxOccurrence();
          break;
        /* Sorts all products in system from the lowest to the highest price */
        case 'l':
          sortByPrice();
          break;
        /* Sorts all products in an order by description */
        case 'L':
          sortByDescription();
          break;
        default:
          break;
    }
  /* Loop while the command isn't 'x' */
  } while (c != 'x');
  return 0;
}
