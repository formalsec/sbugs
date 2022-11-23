#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>


/**************** CONSTANT DEFINITION ****************/

/* The maximum number of identifiers */
#define MAXIDENT 10000

/* The maximum number of characters in a description */
#define DIM 63

/* The maximum number of product weight */
#define WEIGHT 200

/* The maximum number of orders */
#define MAXORDER 500

/* Returned if a product is not in the order */
#define NOT_IN 250

/* Value that determins if its integer or string sorting  */
#define STRING 0
#define INTEGER 1


/***** STRUCTURES *****/

typedef struct product {
    int stock;
    int ident;
    int price;
    int weight;
    char description[DIM];
    
} product;

typedef struct order {
    int ident;
    int weight;
    int totalProd;
    int cost;
    product products[MAXIDENT];

} order;


/*************** GLOBAL VARIABLES **************/

/* Array with products and their specifications */
product system[MAXIDENT];

/* Number of products in system */
int numProducts;

/* Array with all orders */
order orders[MAXORDER];

/* Total number of orders */
int numOrders;

/* Product that helps merging two arrays */
product aux[MAXIDENT];


/************************** FUNCTIONS DECLARATION ************************/

void new_product(char description[DIM], int price, int weight, int quant);
void add_stock(int identProd, int quant);
void new_order();
void add_product_order(int identOrder, int identProd, int quant);
void remove_stock(int identProd, int quant);
void remove_product(int identOrder, int identProd);
void order_cost(int identOrder);
void alter_price(int identProd, int price);
void list_desc_quant(int identOrder, int identProd);
void more_prod(int identProd);
void list_products_price();
void list_products_order(int identOrder);
int search(int ido, int idp);
void merge_sort(product array[], int left, int right, int mode);
void merge(product array[], int left, int mid, int right, int mode);


/******************************** MAIN FUNCTIONS *******************************/

/* Reads the first char(command) of each input and manage the stock and products 
in the system depending on the command. */
int main() {

    char command, description[DIM];
    int price, weight, quant, identProd, identOrder;

    /* Do the instructions depending on the first character of each line of the input.
    The cicle ends when the first character of the line is 'x'. */
    while ((command = getchar()) != 'x') {
        switch (command) {
            case 'a':
                scanf(" %[^:]:%d:%d:%d", description, &price, &weight, &quant);
                new_product(description, price, weight, quant);
                break;

            case 'q':
                scanf("%d:%d", &identProd, &quant);
                add_stock(identProd, quant);
                break;

            case 'N':
                new_order();
                break;

            case 'A':
                scanf("%d:%d:%d", &identOrder, &identProd, &quant);
                add_product_order(identOrder, identProd, quant);
                break;

            case 'r':
                scanf("%d:%d", &identProd, &quant);
                remove_stock(identProd, quant);
                break;

            case 'R':
                scanf("%d:%d", &identOrder, &identProd);
                remove_product(identOrder, identProd);
                break;
            
            case 'C':
                scanf("%d", &identOrder);
                order_cost(identOrder);
                break;
            
            case 'p':
                scanf("%d:%d", &identProd, &price);
                alter_price(identProd, price);
                break;

            case 'E':
                scanf("%d:%d", &identOrder, &identProd);
                list_desc_quant(identOrder, identProd);
                break;

            case 'm':
                scanf("%d", &identProd);
                more_prod(identProd);
                break;
            
            case 'l':
                list_products_price();
                break;

            case 'L':
                scanf("%d", &identOrder);
                list_products_order(identOrder);
                break;          
        }
    }
    return 0;
}

/* Adds new product with the given values to system, prints the product identifier. */
void new_product(char description[DIM], int price, int weight, int quant) {

    static int cont = 0; /* product identifier number */
    product new;

    /* creates new product with the given characteristics */
    new.stock = quant;
    new.ident = cont;
    new.price = price;
    new.weight = weight;
    strcpy(new.description, description);

    system[cont] = new;
    printf("Novo produto %d.\n", new.ident);
    numProducts = cont + 1;
    cont++;
}

/* Adds a given value to a product stock.
In case product doesnt exist prints an error. */
void add_stock(int identProd, int quant) {

    if (numProducts <= identProd) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", identProd);
    }
    else {
        /* adds to the product stock the value of quant */
        system[identProd].stock = system[identProd].stock + quant;
    }
}

/* Creates a new order and prints the identifier number. */
void new_order() {

    static int cont = 0; /* order identifier number */

    orders[cont].ident = cont;
    printf("Nova encomenda %d.\n", orders[cont].ident);
    numOrders = ++cont;
}

/* Adds to the given order the given product in the amount of the third given value. 
In case product or order dont exist, product stock isnt enough or order weight gets over 200, prints an error.*/ 
void add_product_order(int identOrder, int identProd, int quant) {

    int cont = orders[identOrder].totalProd; 
    int j = search(identOrder, identProd);
    product product_ = system[identProd], new_product_order;

    if (numOrders <= identOrder) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", identProd, identOrder);
    }
    else if (numProducts <= identProd) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", identProd, identOrder);
    }
    else if (product_.stock < quant) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", identProd, identOrder);
    }
    else if ((quant * product_.weight + orders[identOrder].weight ) > WEIGHT) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", identProd, identOrder);
    }
    else {
        /* if the product already exists in the order, the value of quant is added to the product stock in the order */
        if (j != NOT_IN) {
            orders[identOrder].products[j].stock += quant;
        }  
        /* if not, the product is added to the order */    
        else {
            new_product_order = system[identProd];
            new_product_order.stock = quant;
            orders[identOrder].products[cont] = new_product_order;
            orders[identOrder].totalProd++;
        }        
        remove_stock(identProd, quant);
        orders[identOrder].cost += product_.price * quant;
        orders[identOrder].weight += quant * product_.weight;
    }
}

/* Removes a given value from a product stock.
In case products doesnt exists or product stock isnt enough prints an error. */
void remove_stock(int identProd, int quant) {
    
    if (identProd >= numProducts) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", identProd);
    }
    else if (system[identProd].stock < quant) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, identProd);
    }
    else {
        system[identProd].stock -= quant; 
    }
}

/* Removes the product with the second id given from the order with the first id given.
In case order or product dont exist prints an error. */
void remove_product(int identOrder, int identProd) {

    int j = search(identOrder, identProd); 

    if (identOrder >= numOrders) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", identProd, identOrder);
    }
    else if (identProd >= numProducts) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", identProd, identOrder);
    }
    /* if the product is in the order */
    else if (j != NOT_IN) {
        system[identProd].stock += orders[identOrder].products[j].stock;
        orders[identOrder].weight -= orders[identOrder].products[j].stock * system[identProd].weight;
        orders[identOrder].cost -= orders[identOrder].products[j].stock * system[identProd].price;
        
        /* removes the product by resetting the product to 0 */
        orders[identOrder].products[j].stock = 0; 
        orders[identOrder].products[j].ident = 0;
        orders[identOrder].products[j].price = 0;
        orders[identOrder].products[j].weight = 0;
        memset(orders[identOrder].products[j].description, 0, DIM);
    }
}

/* Calculates the cost of the order with the given id. 
In case the order doesnt exists prints an error. */
void order_cost(int identOrder) {

    if (identOrder >= numOrders) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", identOrder);
    }
    else {
        printf("Custo da encomenda %d %d.\n", identOrder, orders[identOrder].cost);
    }
}

/* Changes the price of a product for the given value.
In case product doesnt exists prints an error. */
void alter_price(int identProd, int price) {

    int i, j; 

    if (identProd >= numProducts) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", identProd);
    }
    else {
        system[identProd].price = price;
        /* searches in all orders the product and if it exists changes the product price */
        for (i = 0; i < numOrders; i++) {
            j = search(orders[i].ident, identProd);
            if (j != NOT_IN) {
                /* subtracts (product quantity * old price) and adds (product quantity * new price) to the order cost */
                orders[i].cost = orders[i].cost - orders[i].products[j].stock * orders[i].products[j].price + orders[i].products[j].stock * price;
                orders[i].products[j].price = price;
            }
        }
    }
}

/* Prints the description and the quantity of the product with the given id in the order with the given id.
In case order or product dont exist prints an error. */
void list_desc_quant(int identOrder, int identProd) {

    int j = search(identOrder, identProd);
    
    if (identOrder >= numOrders) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", identOrder);
    }
    else if (identProd >= numProducts) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", identProd);
    }
    else if (j != NOT_IN) {
        printf("%s %d.\n", orders[identOrder].products[j].description, orders[identOrder].products[j].stock);
    }  
    else {
        printf("%s 0.\n", system[identProd].description);
    } 
}

/* Searches and prints the order id of the order with more quantity of the product with the given id. 
In case product doesnt exists prints an error. */
void more_prod(int identProd) {

    int i, j;
    int maxProd = 0; /* greater value of product stock found in orders */
    int maxOrder = -1;  /* id of the order that contains maxProd. */
    int stock, ido;

    if (identProd >= numProducts) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", identProd);
        return;
    }    
    else {
        
        /* searches in all orders if the product exists */
        for (i = 0; i < numOrders; i++) {
            ido = orders[i].ident;
            j = search(ido, identProd);
            /* if the product exists compares the stock in the order with maxProd */
            if (j != NOT_IN && orders[i].products[j].stock >= maxProd) {
                stock = orders[i].products[j].stock;
                /* if products stock is greater then the maxProd, maxProd becomes the product 
                stock and maxOrder the id of the order */
                if (maxProd < stock) {
                    maxProd = stock;
                    maxOrder = ido;
                }
                else if (maxOrder > ido) {
                    maxOrder = ido;
                }
            }
        }
        if (maxOrder >= 0) {
            printf("Maximo produto %d %d %d.\n", identProd, maxOrder, maxProd);
        }
    }
}

/* Lists all the products in the system by growing price order using merge_sort. */
void list_products_price() {

    int i;
    product organized[MAXIDENT];

    /* copies the array with all the products to the array organized */
    for (i = 0; i < numProducts; i++) {
        organized[i].stock = system[i].stock;
        organized[i].price = system[i].price;
        organized[i].ident = system[i].ident;
        organized[i].weight = system[i].weight;
        strcpy(organized[i].description, system[i].description);            
    }
    /* organizes the array */
    merge_sort(organized, 0, i - 1, INTEGER); 

    /* prints array by growing price order */
    printf("Produtos\n");
    for (i = 0; i < numProducts; i++) {
        printf("* %s %d %d\n", organized[i].description, organized[i].price, organized[i].stock);
    }
}

/* Lists all products in an order by alphabetically order of products descriptions.
In case the order doesnt exists prints an error. */
void list_products_order(int identOrder) {

    int i, cont = 0;
    product organized[MAXIDENT];

    if (identOrder >= numOrders) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", identOrder);
        return;
    }
    /* copies all the products to the array organized without any "null" products */
    for (i = 0; i < orders[identOrder].totalProd; i++) {
        if (orders[identOrder].products[i].price != 0) {
            organized[cont].stock = orders[identOrder].products[i].stock;
            organized[cont].price = orders[identOrder].products[i].price;
            organized[cont].ident = orders[identOrder].products[i].ident;
            organized[cont].weight = orders[identOrder].products[i].weight;
            strcpy(organized[cont].description, orders[identOrder].products[i].description);
            cont++;
        }
    }
    /* organizes the array */
    merge_sort(organized, 0, --cont, STRING);  

    /* prints the array by alphabetically order of product descriptions */
    printf("Encomenda %d\n", identOrder);
    for (i = 0; i <= cont; i++) {
        printf("* %s %d %d\n", organized[i].description, organized[i].price, organized[i].stock);
    }
}


/************************************* AUXILIAR FUNCTIONS ***************************************/

/* Searches in the order with the given id the product with the given id, if its there returns the 
product position in the order, if not returns NOT_IN. */
int search(int ido, int idp) {
    
    int i, total = orders[ido].totalProd;

    for (i = 0; i < total; i++) {
        if (orders[ido].products[i].ident == idp && orders[ido].products[i].price != 0) {
            return i;
        }
    }
    return NOT_IN;    
}

/* Organizes a given array by growing order of the products price in case mode is INTEGER.
In case mode is STRING than its organized by alphabetically order of products description. */
void merge_sort(product array[], int left, int right, int mode) {

    int mid = (left + right) / 2;

    if (left < right) {
        merge_sort(array, left, mid, mode); /* left recursion */
        merge_sort(array, mid + 1, right, mode); /* right recursion */
        merge(array, left, mid, right, mode); /* merging of two sorted sub-arrays */
    }
    
}

/* Receives an array and splits it in two, go through them comparing one elementent of the first array with 
another of the other array, sorting all elements in both arrays and putting them in the given array. */
void merge(product array[], int left, int mid, int right, int mode) {

    int i, j, k;

    /* copies to aux the first half of the array */
    for (i = mid + 1; i > left; i--) {
        aux[i - 1] = array[i - 1];
    }
    /* copies to aux the second half of the array */
    for (j = mid; j < right; j++) {
        aux[right + mid - j] = array[j + 1];
    }
    /* organizes by growing price order */
    if (mode == INTEGER) {
        for (k = left; k <= right; k++) {
            if (aux[j].price < aux[i].price || (aux[j].price == aux[i].price && aux[j].ident < aux[i].ident)) {
                array[k] = aux[j--];
            }
            else {
                array[k] = aux[i++];
            }
        }
    }
    /* organizes by alphabetically order of products descriptions */
    else {
        for (k = left; k <= right; k++) {
            if (strcmp(aux[j].description, aux[i].description) < 0) {
                array[k] = aux[j--];
            }
            else {
                array[k] = aux[i++];
            }
        }
    }  
}


