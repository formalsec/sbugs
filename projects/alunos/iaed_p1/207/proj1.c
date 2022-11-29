#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>

/*
* Constants setting the maximum value limitig some properties.
*/
#define MAX_PRODUCTS 10000
#define MAX_ORDERS 500
#define MAX_ORDER_WEIGHT 200
#define MAX_STRING 63

/*
* Structure defining the type Product.
*/
typedef struct product {
    int id;
    int price;
    int weight;
    int quantity;
    char description[MAX_STRING];
} Product;

/*
* Structure defining the type Order.
*/
typedef struct order {
    int id;
    int weight;
    int size;
    int price;
    Product items[MAX_ORDER_WEIGHT];
} Order;

/*
* Global variables.
*/
Product productList[MAX_PRODUCTS];
Order orderList[MAX_ORDERS];
int NextProductID;
int NextOrderID;

/*
* Make a copy of a string.
*/
void copyString(char str[], char newStr[], int size) {

    int i;

    for(i = 0; i < size; ++i) {
        newStr[i] = str[i];
    }
}

/*
* Compares two strings.
* @returns -1 if str1<str2, 1 if str2<str1, 0 if str1==str2.
*/
int compareString(char str1[], char str2[]) {

    int i;

    i = 0;
    while(str1[i] != '\0' || str2[i] != '\0') {
        if(str1[i] < str2[i]) {
            return -1;
        }
        else if(str1[i] > str2[i]) {
            return 1;
        }
        ++i;
    }

    return 0;
}

/*
* Finds the position of a product in the product list.
* @returns -1 if the product is not on the list.
*/
int linearProductSearch(Product productList[], int idp, int size) {

    int i;

    for(i = 0; i < size; ++i) {
        if(productList[i].id == idp) {
            return i;
        }   
    }

    return -1;
}

/*
* Creates a new product.
*/
Product createProduct(int id, char description[], int price, int weight, int quantity) {

    Product p;

    p.id = id;
    p.price = price;
    p.weight = weight;
    p.quantity = quantity;
    copyString(description, p.description, MAX_STRING);

    return p;
}

/*
* Command 'a'.
* Adds a new product to the product list.
*/
void newProduct(char description[], int price, int weight, int quantity) {

    productList[NextProductID] = createProduct(NextProductID, description, price, weight, quantity);
    printf("Novo produto %d.\n", NextProductID);
    ++NextProductID;
}

/*
* Command 'q'
* Adds stock to an existing product.
*/
void addStock(int idp, int quantity) {

    if(idp >= NextProductID) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return;
    }

    productList[idp].quantity += quantity;
}

/*
* Create a new order.
*/
Order createOrder(int id) {

    Order e;

    e.id = id;
    e.weight = 0;
    e.size = 0;
    e.price = 0;

    return e;
}

/*
* Command 'N'
* Adds a new order to the order list.
*/
void addOrder() {

    orderList[NextOrderID] = createOrder(NextOrderID);
    printf("Nova encomenda %d.\n", NextOrderID);
    ++NextOrderID;
}

/*
* Command 'r'
* Removes a given amount of the product from stock.
*/
void removeStock(int idp, int quantity) {

    if(idp >= NextProductID) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
    else if(productList[idp].quantity < quantity) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, idp);
        return;
    }

    productList[idp].quantity -= quantity;
}

/*
* Command 'A'
* Adds a product to an existing order.
*/
void addProduct(int idp, int ide, int quantity) {

    int pos;
    
    if(ide >= NextOrderID) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if(idp >= NextProductID) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    else if(productList[idp].quantity < quantity) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }
    else if((orderList[ide].weight + (productList[idp].weight * quantity)) > MAX_ORDER_WEIGHT) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }

    pos = linearProductSearch(orderList[ide].items, idp, orderList[ide].size);
    if(pos != -1) {
        /* Increase the quantity if the product is already on the order */
        orderList[ide].items[pos].quantity += quantity;
    }
    else if(orderList[ide].size < MAX_ORDER_WEIGHT - 1) {
        /* Add product to end of order if it is not full yet */
        orderList[ide].items[orderList[ide].size] = productList[idp];
        orderList[ide].items[orderList[ide].size].quantity = quantity;
        ++orderList[ide].size;
    }
    else {
        /* Search and replace products with quantity=0 (removed products) */
        for(pos = 0; pos < orderList[ide].size; ++pos) {
            if(orderList[ide].items[pos].quantity == 0) {
                orderList[ide].items[pos] = productList[idp];
                orderList[ide].items[pos].quantity = quantity;
                break;
            }
        }
    }

    /* Adjusts the weight and price of the order according to quantity */
    orderList[ide].weight += productList[idp].weight * quantity;
    orderList[ide].price += productList[idp].price * quantity;
    removeStock(idp, quantity);
}

/*
* Command 'R'
* Removes a given product from a given order.
* Removed products are marked with quantity = 0 on the order list.
*/
void removeProduct(int ide, int idp) {

    int pos;

    if(ide >= NextOrderID) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if(idp >= NextProductID) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    /* Search position in order, mark as removed and adjust values */
    pos = linearProductSearch(productList, idp, MAX_PRODUCTS);
    orderList[ide].weight -= productList[idp].weight * orderList[ide].items[pos].quantity;
    orderList[ide].price -= productList[idp].price * orderList[ide].items[pos].quantity;
    addStock(idp, orderList[ide].items[pos].quantity);
    orderList[ide].items[pos].quantity = 0;
}

/*
* Command 'C'
* Displays the given order cost.
*/
void getOrderCost(int ide) {

    if(ide >= NextOrderID) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    printf("Custo da encomenda %d %d.\n", ide, orderList[ide].price);
}

/*
* Command 'p'
* Changes the price of a given product.
*/
void changePrice(int idp, int price) {

    int pos, i, delta;

    if(idp >= NextProductID) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }

    delta = price - productList[idp].price;
    productList[idp].price = price;

    /* Sync the change to orders */
    for(i = 0; i < NextOrderID; ++i) {
        pos = linearProductSearch(orderList[i].items, idp, orderList[i].size);
        if(pos != -1 && orderList[i].items[pos].quantity != 0) {
            orderList[i].items[pos].price = price;
        }
        orderList[i].price += delta; 
    }
}

/*
* Command 'E'
* List the product details in a given order.
*/
void listProduct(int ide, int idp) {

    int pos;

    if(ide >= NextOrderID) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    else if((pos = linearProductSearch(orderList[ide].items, idp, orderList[ide].size)) == -1) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }

    printf("%s %d.\n", orderList[ide].items[pos].description, orderList[ide].items[pos].quantity);
}

/*
* Command 'm'
* Lists the order in which the given product has the biggest quantity.
*/
void listOccurrences(int idp) {

    int count, most, i, j;
    
    if(idp >= NextProductID) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }

    count = 0;
    most = -1;
    for(i = 0; i < NextOrderID; ++i) {
        for(j = 0; j < orderList[i].size; ++j) {
            if((orderList[i].items[j].id == idp) && (orderList[i].items[j].quantity > count)) {
                count = orderList[i].items[j].quantity;
                most = i;
                break;
            }
        }
    }

    if(most != -1) {
        printf("Maximo produto %d %d %d.\n", idp, most, count);
    }
}

/*
* Merge function for listAllProducts().
*/
void mergeProducts(Product list[], Product temp[], int left, int middle, int right) {

    int i, j, k;

    for (i = middle + 1; i > left; --i) { 
        temp[i-1] = list[i-1];
    }

    for (j = middle; j < right; ++j) {
        temp[right+middle-j] = list[j+1];
    }
        
    for (k = left; k <= right; ++k) {
        if ((temp[j].price < temp[i].price) || i > middle) {
            list[k] = temp[j--];
        }
        else {
            list[k] = temp[i++];
        }
    }
}

/*
* Merge function for listOrder().
*/
void mergeOrder(Product list[], Product temp[], int left, int middle, int right) {
    int i, j, k;

    for (i = middle + 1; i > left; --i) { 
        temp[i-1] = list[i-1];
    }

    for (j = middle; j < right; ++j) {
        temp[right+middle-j] = list[j+1];
    }
        
    for (k = left; k <= right; ++k) {
        if (compareString(temp[j].description, temp[i].description) <= 0 || i > middle) {
            list[k] = temp[j--];
        }
        else {
            list[k] = temp[i++];
        }
    }
}

/*
* Function selector.
*/
void merge(Product list[], Product temp[], int left, int middle, int right, char option) {
    if(option == 'p') {
        mergeProducts(list, temp, left, middle, right);
    }
    else if(option == 'e') {
        mergeOrder(list, temp, left, middle, right);
    }
}

/*
* Sorts an array.
*/
void mergeSort(Product list[], Product temp[], int left, int right, char option) {
    
    int middle = (left + right) / 2;

    if(left >= right) {
        return;
    }

    mergeSort(list, temp, left, middle, option);
    mergeSort(list, temp, middle + 1, right, option);
    merge(list, temp, left, middle, right, option);
}

/*
* Command 'l'
* Lists all the products by ascending order of its price.
*/
void listAllProducts() {

    Product list[MAX_PRODUCTS];
    Product temp[MAX_PRODUCTS];
    int i;

    for(i = 0; i < NextProductID; ++i) {
        list[i] = productList[i];
    }

    mergeSort(list, temp, 0, NextProductID - 1, 'p');

    printf("Produtos\n");
    for(i = 0; i < NextProductID; ++i) {
        printf("* %s %d %d\n", list[i].description, list[i].price, list[i].quantity);
    }
}

/*
* Command 'L'
* Lists all the product in a given order by alphabetical order of its description.
*/
void listOrder(int ide) {

    Product list[MAX_ORDER_WEIGHT];
    Product temp[MAX_ORDER_WEIGHT];
    int i;

    if(ide >= NextOrderID) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    for(i = 0; i < orderList[ide].size; ++i) {
        list[i] = orderList[ide].items[i];
    }

    mergeSort(list, temp, 0, orderList[ide].size - 1, 'e');

    printf("Encomenda %d\n", ide);
    for(i = 0; i < orderList[ide].size; ++i) {
        if(list[i].quantity != 0) {
            printf("* %s %d %d\n", list[i].description, list[i].price, list[i].quantity);
        }
    }
}

/*
* Main function.
*/
int main() {

    char description[MAX_STRING];
    int idp, ide, price, weight, quantity, i;
    char command, c;

    NextProductID = 0;
    NextOrderID = 0;
    i = 0;

    /* Read command and choose option */
    command = getchar();

    while(command != 'x'){
        switch (command) {
        case 'a':
            getchar();
            while((c = getchar()) != ':' && c != EOF && i < MAX_STRING) {
                description[i] = c;
                ++i;
            }
            description[i] = '\0';

            scanf("%d:%d:%d", &price, &weight, &quantity);
            newProduct(description, price, weight, quantity);
            break;
        case 'q':
            scanf("%d:%d", &idp, &quantity);
            addStock(idp, quantity);
            break;
        case 'N':
            addOrder();
            break;
        case 'A':
            scanf("%d:%d:%d", &ide, &idp, &quantity);
            addProduct(idp, ide, quantity);
            break;
        case 'r':
            scanf("%d:%d", &idp, &quantity);
            removeStock(idp, quantity);
            break;
        case 'R':
            scanf("%d:%d", &ide, &idp);
            removeProduct(ide, idp);
            break;
        case 'C':
            scanf("%d", &ide);
            getOrderCost(ide);
            break;
        case 'p':
            scanf("%d:%d", &idp, &price);
            changePrice(idp, price);
            break;
        case 'E':
            scanf("%d:%d", &ide, &idp);
            listProduct(ide, idp);
            break;
        case 'm':
            scanf("%d", &idp);
            listOccurrences(idp);
            break;
        case 'l':
            listAllProducts();
            break;
        case 'L':
            scanf("%d", &ide);
            listOrder(ide);
            break;
        default:
            break;
        }
        command = getchar();
        i = 0;
    }
    
    return 0;
}