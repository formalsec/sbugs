#include <stdio.h>

#include <string.h>

#include "proj1.h"

Product products[MAX_PRODUCTS]; /*Array of all products declared*/
int price[MAX_PRODUCTS]; /*Array of prices indexed by the id of the product*/
int nr_products = 0; /*Number of products declared*/
int changed = 0; /*Flag represents wether the product array is already sorted*/

Product aux[MAX_PRODUCTS]; /*Mergesort auxiliary array*/

Order orders[MAX_ORDERS]; /*Array of all orders declared*/
int nr_orders = 0; /*Number of orders declared*/

/*Given an array "arr", of length "len", 
function returns the position of product with id "id" in said array
if product doesn't exist returns -1*/
int findProduct(Product * arr, int len, int id) {
    int i;

    for (i = 0; i < len; i++) {
        if (arr[i].id == id)
            return i;
    }

    return -1; /*Product doesn't exist in array*/
}

/*---------------------------------------------------------------------*/

/*Reads string including spaces*/
void readString(char * s) {
    int count = 0;
    int c;

    /*Remove first space before input*/
    c = getchar();

    while ((c = getchar()) != ':') {
        s[count] = c;
        count++;
    }

    s[count] = '\0';
}

/*---------------------------------------------------------------------*/

/*Prints given product*/
void printProduct(Product product) {
    printf("%s ", product.description);
    printf("%d ", price[product.id]);
    printf("%d\n", product.stock);
}

/*---------------------------------------------------------------------*/

/*Prints all products in array products*/
void printProducts() {
    int i;

    printf("Produtos\n");

    for (i = 0; i < nr_products; i++) {
        printf("* ");
        printProduct(products[i]);
    }
}

/*---------------------------------------------------------------------*/

/*Prints all products in a given order*/
void printOrder(int order) {
    int i;

    printf("Encomenda %d\n", order);

    for (i = 0; i < orders[order].nr_products; i++) {
        printf("* ");
        printProduct(orders[order].products[i]);
    }
}

/*---------------------------------------------------------------------*/

/*Removes a specific product from a given array*/
void removeFromArray(Product * arr, int len, int position) {
    int i;

    for (i = position + 1; i < len; i++) {
        arr[i - 1] = arr[i];
    }
}

/*---------------------------------------------------------------------*/

/*
Command a: Creates new product
*/
void createProduct(char * d, int prc, int wght, int amount) {
    strcpy(products[nr_products].description, d);

    products[nr_products].id = nr_products;
    products[nr_products].weight = wght;
    products[nr_products].stock = amount;

    price[nr_products] = prc;
    /*Array order is compromised*/
    changed = 1;

    printf("Novo produto %d.\n", nr_products);

    nr_products++;
}

/*---------------------------------------------------------------------*/

/* 
Command q: Increments the stock of a specified product
*/
void incrementStock(int id, int amount) {
    int position = findProduct(products, nr_products, id);

    /*Check if the product exists*/
    if (position == -1) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
        return;
    }

    products[position].stock += amount;
}

/*---------------------------------------------------------------------*/

/*
Command N: Creates a new order
*/
void createOrder() {
    orders[nr_orders].id = nr_orders;
    orders[nr_orders].nr_products = 0;
    orders[nr_orders].weight = 0;
    orders[nr_orders].ordered = 1;

    printf("Nova encomenda %d.\n", nr_orders);

    nr_orders++;
}

/*---------------------------------------------------------------------*/

/*
Command A: Add Product to Order
*/
void addToOrder(int order, int product, int amount) {
    int position, productPosition, weightAfter;

    if (order >= nr_orders) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", product, order);
        return;
    }

    position = findProduct(products, nr_products, product);

    if (position == -1) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", product, order);
        return;
    }

    if (products[position].stock < amount) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", product, order);
        return;
    }

    weightAfter = orders[order].weight + amount * (products[position].weight);
    if (weightAfter > 200) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", product, order);
        return;
    }

    productPosition = position;

    position = findProduct(orders[order].products, orders[order].nr_products, product);

    /*Check if the product doesn't exist in the order*/
    if (position == -1) {
        position = orders[order].nr_products++;

        orders[order].products[position].id = products[productPosition].id;
        orders[order].products[position].weight = products[productPosition].weight;
        orders[order].products[position].stock = 0;
        /*New product in order means it may be unsorted*/
        orders[order].ordered = 0;
        strcpy(orders[order].products[position].description, products[productPosition].description);
    }

    orders[order].products[position].stock += amount;

    orders[order].weight = weightAfter;

    /*Decrease the amount of available stock*/
    products[productPosition].stock -= amount;
}

/*---------------------------------------------------------------------*/

/*
Command r: Removes a given amount of stock from a specified product
*/
void removeStock(int product, int amount) {
    int position;

    position = findProduct(products, nr_products, product);

    /*Check if the product exists*/
    if (position != -1) {
        if (products[position].stock >= amount) {
            products[position].stock -= amount;
        } else {
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", amount, product);
        }
    } else {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", product);
    }
}

/*---------------------------------------------------------------------*/

/*
Command R: Removes a given product from a specified order
*/
void removeProductFromOrder(int order, int product) {
    int position;

    if (order < nr_orders) {
        position = findProduct(products, nr_products, product);
        if (position == -1) {
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", product, order);
        } else {
            position = findProduct(orders[order].products, orders[order].nr_products, product);
            /*Check if the product exists in the order*/
            if (position != -1) {
                /*Stock has to be replenished*/
                incrementStock(product, orders[order].products[position].stock);
                orders[order].weight -= (orders[order].products[position].stock) * (orders[order].products[position].weight);
                removeFromArray(orders[order].products, orders[order].nr_products, position);
                orders[order].nr_products--;
            }
        }
    } else {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", product, order);
    }

}

/*---------------------------------------------------------------------*/

/*
Command C: Prints the value of a specified order
*/
void calcOrderCost(int order) {
    int i, sum = 0;

    if (order < nr_orders) {
        for (i = 0; i < orders[order].nr_products; i++) {
            sum += orders[order].products[i].stock * price[orders[order].products[i].id];
        }
        printf("Custo da encomenda %d %d.\n", order, sum);
    } else {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", order);
    }
}

/*---------------------------------------------------------------------*/

/*
Command p: Changes the price of a product globally
*/
void changeProductPrice(int product, int newPrice) {
    if (product < nr_products) {
        price[product] = newPrice;
        /*Change of price compromises array order*/
        changed = 1;
    } else {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", product);
    }
}

/*---------------------------------------------------------------------*/

/*
Command E: Lists description and quantity of a given product in specific order
*/
void infoProductInOrder(int order, int product) {
    int position;

    if (order < nr_orders) {
        position = findProduct(products, nr_products, product);
        if (position != -1) {
            printf("%s ", products[position].description);

            position = findProduct(orders[order].products, orders[order].nr_products, product);
            /*Check if the product exists in order*/
            if (position != -1) {
                printf("%d.\n", orders[order].products[position].stock);
            } else {
                printf("0.\n");
            }
        } else {
            printf("Impossivel listar produto %d. Produto inexistente.\n", product);
        }
    } else {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order);
    }
}

/*---------------------------------------------------------------------*/

/*
Command m: Returns the id of the order with the most instances of a product
*/
void mostCommissioningOrder(int product) {
    int i;
    int position;
    int max; /*Id of the order that has ordered the largest amount of the product*/
    int commissioned = -1; /*Largest amount of ordered product*/

    position = findProduct(products, nr_products, product);
    /*Check if the product exists*/
    if (position == -1) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", product);
        return;
    }

    for (i = 0; i < nr_orders; i++) {
        position = findProduct(orders[i].products, orders[i].nr_products, product);

        /*Check if the product exists in order*/
        if (position != -1) {
            if (orders[i].products[position].stock > commissioned) {
                commissioned = orders[i].products[position].stock;
                max = i;
            }
        }
    }

    /*Check if any order has ordered said product*/
    if (commissioned >= 0) {
        printf("Maximo produto %d %d %d.\n", product, max, commissioned);
    }

}

/*---------------------------------------------------------------------*/

/*
Returns 0 if product b is more expensive than a, returns "true" otherwise.
Or if their prices are the same returns 0 if b's id is larger than a's and "true" otherwise
*/
int lowerPrice(const Product a,
    const Product b) {
    if (price[a.id] == price[b.id])
        return a.id < b.id;
    return price[a.id] < price[b.id];
}

/*---------------------------------------------------------------------*/

/*
Returns 0 if product a preceeds product b alphabetically and "true" otherwise
*/
int lowerName(const Product a, const Product b) {
    int i = 0, j = 0;
    while (a.description[i] != '0' && b.description[j] != '0') {
        /*Ignore spaces in product description*/
        if (a.description[i] == ' ') {
            i++;
        }
        if (b.description[j] == ' ') {
            j++;
        }

        if (a.description[i] == b.description[j]) {
            i++;
            j++;
        } else {
            return a.description[i] < b.description[j];
        }
    }
    return 0;
}

/*---------------------------------------------------------------------*/

/*
Merges two subarrays of arr[]. 
First subarray is arr[left..m] 
Second subarray is arr[m+1..right] 
*/
void merge(Product arr[], int left, int m, int right, int( * less)(const Product a, const Product b)) {
    int i, j, k;
    /*Copy values in arr to auxiliary array*/
    for (i = m + 1; i > left; i--)
        aux[i - 1] = arr[i - 1];

    for (j = m; j < right; j++)
        aux[right + m - j] = arr[j + 1];

    /*Place values back in array arr from "smallest" to "largest"*/
    for (k = left; k <= right; k++) {
        if (less(aux[j], aux[i]) || i > m)
            arr[k] = aux[j--];
        else
            arr[k] = aux[i++];
    }
}

/*---------------------------------------------------------------------*/

/*
Sorts array arr based on comparing function less
*/
void mergeSort(Product arr[], int l, int r, int( * less)(const Product a, const Product b)) {
    int m;

    if (l < r) {
        m = l + (r - l) / 2;

        /*Divide and conquer approach*/
        mergeSort(arr, l, m, less);
        mergeSort(arr, m + 1, r, less);

        merge(arr, l, m, r, less);
    }
}

/*---------------------------------------------------------------------*/

/*
Command l: Lists all products sorted by price
*/
void listProductsByPrice() {

    /*Only sorts products if their order has been compromised by another command*/
    if (changed) {
        mergeSort(products, 0, nr_products - 1, lowerPrice);
        changed = 0;
    }
    printProducts();
}

/*---------------------------------------------------------------------*/

/*
Command L: Lists all products in specific order alphabetically
*/
void listOrderedProductsByName(int order) {
    if (order >= nr_orders) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order);
        return;
    }

    /*Only sorts products if their order has been compromised by another command*/
    if (!orders[order].ordered) {
        mergeSort(orders[order].products, 0, orders[order].nr_products - 1, lowerName);
        orders[order].ordered = 1;
    }
    printOrder(order);
}

/*---------------------------------------------------------------------*/

/*
 *  Main function
 */
int main() {
    int c;
    int id_prod, id_ord, prc, wght, qty;
    char s[MAX_DESCRIP];

    while (1) {
        c = getchar();

        switch (c) {
        case 'a':
            readString(s);
            scanf("%d:%d:%d", & prc, & wght, & qty);
            createProduct(s, prc, wght, qty);
            break;
        case 'q':
            scanf("%d:%d", & id_prod, & qty);
            incrementStock(id_prod, qty);
            break;
        case 'N':
            createOrder();
            break;
        case 'A':
            scanf("%d:%d:%d", & id_ord, & id_prod, & qty);
            addToOrder(id_ord, id_prod, qty);
            break;
        case 'r':
            scanf("%d:%d", & id_prod, & qty);
            removeStock(id_prod, qty);
            break;
        case 'R':
            scanf("%d:%d", & id_ord, & id_prod);
            removeProductFromOrder(id_ord, id_prod);
            break;
        case 'C':
            scanf("%d", & id_ord);
            calcOrderCost(id_ord);
            break;
        case 'p':
            scanf("%d:%d", & id_prod, & prc);
            changeProductPrice(id_prod, prc);
            break;
        case 'E':
            scanf("%d:%d", & id_ord, & id_prod);
            infoProductInOrder(id_ord, id_prod);
            break;
        case 'm':
            scanf("%d", & id_prod);
            mostCommissioningOrder(id_prod);
            break;
        case 'l':
            listProductsByPrice();
            break;
        case 'L':
            scanf("%d", & id_ord);
            listOrderedProductsByName(id_ord);
            break;
        case 'x':
            return 0;
        }
    }
}

/* =============================================================================
 *
 * End of proj1.c
 *
 * =============================================================================
 */