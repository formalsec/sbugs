#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Constant Definition */
#define DESCRIPTION 64
#define PRODUCTS 10001
#define ORDERS 501
#define INPUT 200

/* Data Structures */
typedef struct {
	int id;
    char description[DESCRIPTION];
 	int price; 
    int weight; 
    int amount;
    int state;          /* Lets me check if the product already exists. If the state is 0 it doesn't, if the state is 1 it does */
} Product;

typedef struct {
    Product products[PRODUCTS];
    int price;
    int weight;
    int state;
    int id;
} Order;

/*----------
 Prototypes
-----------*/

/* Functions */
int getId();
int getOrderId();
int calcOrderId(int id, int x);
int getHighest(int id);
int getSortedN();
void clear();
void copyList(int id);
void updatePrice(int id, int price);
void sort();
void mergeAlpha(int left, int right);
void mergeAux(int left, int m, int right);
void mergeSort(int left, int right);
void merge(int left,int m, int right);
void addProduct();
void addStock();
void addOrder();
void addToOrder();
void removeAmount();
void removeFromOrder();
void orderPrice();
void changePrice();
void listProduct();
void listHighest();
void listStock();
void listAlpha();

/* Global Variables */
Product stock[PRODUCTS];            /* List that contains all Products and their information */
Product sortedList[PRODUCTS];       /* List that's going to be sorted by price or alphabetically */
Order orders[ORDERS];               /* List that contains all Orders and their information */
char* token;
char input[INPUT];

/* Code */
int main() {
    char command;

    do {
        command = getchar();        
        if (command == 'a')
            addProduct();
        else if (command == 'q')
            addStock();
        else if (command == 'N') 
            addOrder();
        else if (command == 'A') 
            addToOrder();
        else if (command == 'r')
            removeAmount();
        else if (command == 'R') 
            removeFromOrder();
        else if (command == 'C')
            orderPrice();
        else if (command == 'p') 
            changePrice();
        else if (command == 'E')
            listProduct();
        else if (command == 'm')
            listHighest();
        else if (command == 'l')
            listStock();
        else if (command == 'L')
            listAlpha();
    } while (command != 'x');

    return 0;
}

/*---------------------------------------
addProduct(): Adds a product to the stock
---------------------------------------*/
void addProduct() {
    int id; 

    getchar();
    fgets(input, sizeof(input), stdin);

    id = getId();
    
    if (id != -1) {
        sscanf(input, "%[^:]:%d:%d:%d", stock[id].description, &stock[id].price, &stock[id].weight, &stock[id].amount);
        stock[id].id = id;
        stock[id].state = 1;
        printf("Novo produto %d.\n", id);
    }
}

/*--------------------------------
getId(): Gets the next product id
--------------------------------*/
int getId() {
    int i;
    for (i = 0; i < PRODUCTS; i++) {
        if (stock[i].state == 0) 
            return i;
    }
    return -1;
}

/*---------------------------------------------
addStock(): Adds a certain amount of a product
---------------------------------------------*/
void addStock() {
    int id, amount;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d:%d", &id, &amount);

    if (stock[id].state == 0) 
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
    else 
        stock[id].amount += amount;
}

/*-----------------------
addOrder(): Adds an order
-----------------------*/
void addOrder() {
    int id = getOrderId();

    if (id != -1) {
        orders[id].state = 1;
        printf("Nova encomenda %d.\n", id);
    }
}

/*----------------------------------
getOrderId(): Gets the next order id
----------------------------------*/
int getOrderId() {
    int i;
    for (i = 0; i < ORDERS; i++) {
        if (orders[i].state == 0) 
            return i;
    }
    return -1;
}

/*--------------------------------------
addToOrder(): Adds a product to an order
--------------------------------------*/
void addToOrder() {
    int idOrder, idProduct, amount;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d:%d:%d", &idOrder, &idProduct, &amount);

    if(orders[idOrder].state == 0) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idProduct, idOrder);
        return;
    }
    else if(stock[idProduct].state == 0) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idProduct, idOrder);
        return;
    }
    else if(stock[idProduct].amount < amount) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idProduct, idOrder);
        return;
    }
    else if((orders[idOrder].weight + stock[idProduct].weight * amount) > 200) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idProduct, idOrder);
        return;
    }
    
    if (orders[idOrder].products[idProduct].state == 0) {
        orders[idOrder].products[idProduct] = stock[idProduct];
        orders[idOrder].products[idProduct].amount = amount;
        orders[idOrder].price += stock[idProduct].price * amount;
        orders[idOrder].weight += stock[idProduct].weight * amount;
        stock[idProduct].amount -= amount;
        return;
    }
    orders[idOrder].products[idProduct].amount += amount;
    orders[idOrder].price += stock[idProduct].price * amount;
    orders[idOrder].weight += stock[idProduct].weight * amount;
    stock[idProduct].amount -= amount;
}

/*---------------------------------------------------
removeAmount(): Removes a certain amount of a product
---------------------------------------------------*/
void removeAmount() {
    int id, amount;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d:%d", &id, &amount);

    if(stock[id].state == 0) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
        return;
    }
    else if(stock[id].amount < amount) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", amount, id);
        return;
    }
    stock[id].amount -= amount;
}

/*------------------------------------------------
removeFromOrder(): Removes a product from an order
------------------------------------------------*/
void removeFromOrder() {
    int idOrder, idProduct;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d:%d", &idOrder, &idProduct);

    if(orders[idOrder].state == 0) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idProduct, idOrder);
        return;
    }
    else if(stock[idProduct].state == 0) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idProduct, idOrder);
        return;
    }
    if (orders[idOrder].products[idProduct].state == 1) {
        orders[idOrder].weight -= orders[idOrder].products[idProduct].weight * orders[idOrder].products[idProduct].amount;
        orders[idOrder].price -= orders[idOrder].products[idProduct].price * orders[idOrder].products[idProduct].amount;
        stock[idProduct].amount += orders[idOrder].products[idProduct].amount;
        orders[idOrder].products[idProduct].amount = 0;
        orders[idOrder].products[idProduct].state = 0;
    }
}

/*------------------------------------------------
orderPrice(): Displays the total price of an order
------------------------------------------------*/
void orderPrice() {
    int id;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &id);

    if(orders[id].state == 0) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id);
        return;
    }
    printf("Custo da encomenda %d %d.\n", id, orders[id].price);
}

/*-------------------------------------------
changePrice(): Changes the price of a product
-------------------------------------------*/
void changePrice() {
    int id, price;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d:%d", &id, &price);

    if(stock[id].state == 0) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
        return;
    }
    updatePrice(id, price);
    stock[id].price = price;
}

/*-----------------------------------------------
updatePrice(int id, int price): Updates the price 
of a product on each order and its total price
-----------------------------------------------*/
void updatePrice(int id, int price) {
    int i;
    for(i = 0; i < ORDERS; i++) {
        if(orders[i].products[id].state == 1) {
            orders[i].price -= stock[id].price * orders[i].products[id].amount; 
            orders[i].products[id].price = price;
            orders[i].price += price * orders[i].products[id].amount;
        }
    }
}

/*-----------------------------------------
listProduct(): Displays the description and 
the amount of a product of a certain order
-----------------------------------------*/
void listProduct() {
    int idOrder, idProduct;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d:%d", &idOrder, &idProduct);

    if(orders[idOrder].state == 0) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idOrder);
        return;
    }
    else if(stock[idProduct].state == 0) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idProduct);
        return;
    }
    printf("%s %d.\n", stock[idProduct].description, orders[idOrder].products[idProduct].amount);
}

/*-------------------------------------------------
listHighest(): Displays the order id which has the 
highest amount of a certain product and that amount
-------------------------------------------------*/
void listHighest() {
    int idProduct, highest, idOrder;
    
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &idProduct);

    if (stock[idProduct].state == 0) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idProduct);
        return;
    }

    highest = getHighest(idProduct);
    idOrder = calcOrderId(idProduct, highest);

    if (idOrder != -1 && highest != 0)
        printf("Maximo produto %d %d %d.\n", idProduct, idOrder, highest);
}

/*--------------------------------------
getHighest(): Gets the highest amount of
a certain product out of every order
--------------------------------------*/
int getHighest(int id) {
    int highest = 0;
    int i;

    for(i = 0; i < ORDERS; i++) {
        if(orders[i].state == 1) {
            if(orders[i].products[id].state == 1) {
                if(orders[i].products[id].amount > highest)
                    highest = orders[i].products[id].amount;
            }
        }
    }
    return highest;
}

/*------------------------------------------
calcOrderId(int id, int x): Calculates the 
lowest order id which has the highest amount
------------------------------------------*/
int calcOrderId(int id, int x) {
    int i;

    for (i = 0; i < ORDERS; i++) {
        if (orders[i].products[id].amount == x)
            return i;
    }
    return -1;
}

/*-----------------------------------------
listStock(): Displays all products on stock
-----------------------------------------*/
void listStock(){
    int right, i;
    
    sort();
    right = getId() - 1;
    mergeSort(0, right);

    printf("Produtos\n");
    for (i = 0; i < right + 1; i++)
        printf("* %s %d %d\n", sortedList[i].description, sortedList[i].price, sortedList[i].amount);
    clear();
}

/*----------------------------------
sort(): Copies all products on stock
----------------------------------*/
void sort() {
    int i;

    for (i = 0; i < PRODUCTS; i++) 
        sortedList[i] = stock[i];
}

/*--------------------------------------------
clear(): Clears all products on the SortedList
--------------------------------------------*/
void clear() {
    int i;

    for(i = 0; i < PRODUCTS; i++)
        sortedList[i].state = 0;
}

/* Sorting Algorithm */
void mergeSort(int left, int right) {
    int m = (right+left)/2;

    if (right <= left)
        return;

    mergeSort(left, m);
    mergeSort(m + 1, right);
    merge(left, m, right);
}

/*-----------------------------------------------
merge(int left, int m, int right): Sorts by price
-----------------------------------------------*/
void merge(int left, int m, int right) {
    int i, j, k;
    Product aux[PRODUCTS];

    for (i = m + 1; i > left; i--)
        aux[i - 1] = sortedList[i - 1];
    for (j = m; j < right; j++)
        aux[right + m - j] = sortedList[j + 1];
    for (k = left; k <= right; k++)
        if (aux[j].price < aux[i].price || i > m)
            sortedList[k] = aux[j--];
        else if ((aux[j].price == aux[i].price && aux[j].id < aux[i].id) || i > m)   
            sortedList[k] = aux[j--];
        else
            sortedList[k] = aux[i++];
}

/*----------------------------------
listAlpha(): Displays alphabetically 
all products of a certain order
----------------------------------*/
void listAlpha() {
    int id, i, right;

    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &id);

    if(orders[id].state == 0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id);
        return;
    }

    copyList(id);
    right = getSortedN() - 1;
    mergeAlpha(0, right);

    printf("Encomenda %d\n", id);
    if (right != -2) {
        for (i = 0; i < right + 1; i++) 
            printf("* %s %d %d\n", sortedList[i].description, sortedList[i].price, sortedList[i].amount);
    }
    clear();
}

/*---------------------------
copyList(int id): Copies all 
products of a certain order
--------------------------*/
void copyList(int id) {
    int i;
    int k = 0;

    for (i = 0; i < PRODUCTS; i++) {
        if(orders[id].products[i].state == 1) {
            sortedList[k] = orders[id].products[i];
            k++;
        }
    }
}

/*---------------------------
getSortedN(): Gets the number 
of products on the sortedlist
---------------------------*/
int getSortedN() {
    int i;

    for(i = 0; i < PRODUCTS; i++) {
        if (sortedList[i].state == 0)
            return i;
    }
    return -1;
}

/* Sorting Algorithm */
void mergeAlpha(int left, int right) {
    int m = (right+left)/2;

    if (right <= left)
        return;

    mergeAlpha(left, m);
    mergeAlpha(m + 1, right);
    mergeAux(left, m, right);
}

/*--------------------------------------------------------
mergeAux(int left, int m, int right): Sorts alphabetically 
--------------------------------------------------------*/
void mergeAux(int left, int m, int right) {
    int i, j, k;
    Product aux[PRODUCTS];

    for (i = m+1; i > left; i--)
        aux[i-1] = sortedList[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = sortedList[j+1];
    for (k = left; k <= right; k++)
        if (aux[j].description[0] < aux[i].description[0] || i > m)
            sortedList[k] = aux[j--];
        else if ((aux[j].description[0] == aux[i].description[0] && aux[j].description[1] < aux[i].description[1]) || i > m)   
            sortedList[k] = aux[j--];
        else if (((aux[j].description[0] == aux[i].description[0] && aux[j].description[1] == aux[i].description[1])
        && (aux[j].description[2] < aux[i].description[2])) || i > m)
            sortedList[k] = aux[j--];
        else if (((aux[j].description[0] == aux[i].description[0] && aux[j].description[1] == aux[i].description[1])
        && (aux[j].description[2] == aux[i].description[2] && aux[j].description[3] < aux[i].description[3])) || i > m)
            sortedList[k] = aux[j--];
        else
            sortedList[k] = aux[i++];
}