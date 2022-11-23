#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_MAX 90
#define STRING_MAX 64
#define PRODUCTS_MAX 10000
#define ORDERS_MAX 500
#define WEIGHT_MAX 200

typedef struct{
    int id, price, weight, stock;
    char description[STRING_MAX];
}product;

/* pid_in_order has the product id's in insertion order
 * product_quantities has the product quantities' in products id order */
typedef struct{
    int product_quantities[PRODUCTS_MAX], pid_in_order[PRODUCTS_MAX];
    int weight, products_in;
}order;

/* system products' array*/
product products[PRODUCTS_MAX];
int products_counter = 0;

/* system orders' array */
order orders[ORDERS_MAX];
int orders_counter = 0;

void new_product(){
    /* adds a new product to the system */
    product p;

    scanf(" %[^:]:%d:%d:%d", p.description, &p.price, &p.weight, &p.stock);
    p.id = products_counter;

    products[products_counter] = p;
    products_counter++;

    printf("Novo produto %d.\n",products_counter-1);
}

void increase_stock(){
    /* increases a given amount of stock in a specific product */
    int pid, qty;

    scanf(" %d:%d", &pid, &qty);

    if(pid >= products_counter)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",pid);
    else
        products[pid].stock += qty;
}

void new_order(){
    /* adds a new order to the system */

    orders[orders_counter].weight = 0;
    orders[orders_counter].products_in = 0;
    orders_counter++;

    printf("Nova encomenda %d.\n",orders_counter-1);
}

void add_product_to_order(){
    /* adds a specific product to a specific order */
    int pid, oid, qty;

    scanf(" %d:%d:%d", &oid, &pid, &qty);
    /* increases product quantity in the order and decreases product's stock in the system */

    if(oid >= orders_counter)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", pid, oid);
    else if(pid >= products_counter)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",pid, oid);
    else if(products[pid].stock < qty)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",pid, oid);
    else if((orders[oid].weight + (products[pid].weight * qty)) > WEIGHT_MAX)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",pid, oid);
    else{
        /* if product is already ordered */
        if (orders[oid].product_quantities[pid]){
            orders[oid].product_quantities[pid] += qty;
            products[pid].stock -= qty;
        }
        else {
            orders[oid].product_quantities[pid] = qty;
            /* adds the product id in the end of pid_in_order array */
            orders[oid].pid_in_order[orders[oid].products_in] = pid;
            orders[oid].products_in++;
            products[pid].stock -= qty;
        }
        orders[oid].weight += products[pid].weight * qty;
    }
}

void decrease_stock(){
    /* decreases a given amount of stock in a specific product */
    int pid, qty;

    scanf(" %d:%d", &pid, &qty);

    if(pid >= products_counter)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",pid);
    else if((products[pid].stock - qty) < 0)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qty, pid);
    else
        products[pid].stock -= qty;
}

void remove_product_from_order(){
    /* removes a specific product in a specific order */

    int pid, oid, i, found = 0;

    scanf(" %d:%d", &oid, &pid);

    if(oid >= orders_counter)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", pid, oid);
    else if(pid >= products_counter)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",pid, oid);
    else{
        /* tries to find the product in the order */
        for(i = 0; i < orders[oid].products_in; i++){
            if(orders[oid].pid_in_order[i] == pid){
                orders[oid].pid_in_order[i] = orders[oid].pid_in_order[orders[oid].products_in-1];
                found = 1;
            }
        }
        if(found){
            orders[oid].weight -= products[pid].weight * orders[oid].product_quantities[pid];
            products[pid].stock += orders[oid].product_quantities[pid];
            orders[oid].product_quantities[pid] = 0;
            orders[oid].products_in--;
        }
    }
}

void calculate_cost(){
    /* calculates the cost of a given order - each of its products price times their quantity */
    int oid, pid, qty, cost = 0, i;

    scanf(" %d", &oid);

    if(oid >= orders_counter)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", oid);
    else{
        for (i = 0; i < orders[oid].products_in; i++) {
            pid = orders[oid].pid_in_order[i];
            qty = orders[oid].product_quantities[pid];
            cost += qty * products[pid].price;
        }

        printf("Custo da encomenda %d %d.\n", oid, cost);
    }
}

void change_price(){
    /* changes the price of a specific product to a given new price */
    int pid, new_price;

    scanf(" %d:%d", &pid, &new_price);

    if(pid >= products_counter)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",pid);
    else
        products[pid].price = new_price;
}

void order_product_details(){
    /* lists a specific product's description and quantity in a given order */
    int oid, pid;

    scanf(" %d:%d", &oid, &pid);

    if(oid >= orders_counter)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",oid);
    else if(pid >= products_counter)
        printf("Impossivel listar produto %d. Produto inexistente.\n",pid);
    else
        printf("%s %d.\n", products[pid].description, orders[oid].product_quantities[pid]);
}

void order_product_ocurrence(){
    /* lists an order with the highest quantity of a given product and its quantity */
    int pid, k, max = 0, order = -1;

    scanf(" %d", &pid);

    if(pid >= products_counter)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",pid);
    else{
        /* searches all the order for the product pid and stores its highest quantity in max and its order*/
        for (k = 0; k < orders_counter; k++)
            if (orders[k].product_quantities[pid] > max) {
                max = orders[k].product_quantities[pid];
                order = k;
            }

        /* if no order has the designated product */
        if(order != -1 && max)
            printf("Maximo produto %d %d %d.\n", pid, order, max);
    }
}

int compare_price(product a, product b){
    /* comparator function for price quicksort */
    int price = a.price - b.price;
    if(price != 0)
        return price;
    return a.id - b.id;
}

int compare_descriptions(product a, product b){
    /* comparator function for alphabetical quicksort */
    int description = strcmp(a.description,b.description);
    if (description != 0)
        return description;
    return b.id - a.id;
}

void swap_products(product *a, product *b){
    /* swap function for quicksort */
    product temp = *a;
    *a = *b;
    *b = temp;
}

int divide_by_price(product prod[], int low, int high, int split){
    /* partition function for price quicksort */
    product price;
    int i = (low - 1), j;

    /* changes pivot from the end of the array to its middle*/
    swap_products(&prod[split],&prod[high]);
    price = prod[high];


    for(j = low; j <= high - 1; j++){
        if (compare_price(prod[j],price) < 0){
            i++;
            swap_products(&prod[i],&prod[j]);
        }
    }
    swap_products(&prod[i + 1],&prod[high]);
    return (i + 1);
}

int divide_by_description(product prod[], int low, int high, int split){
    /* partition function for alphabetical quicksort */
    product description;
    int i = (low - 1), j;

    /* changes pivot from the end of the array to its middle*/
    swap_products(&prod[split],&prod[high]);
    description = prod[high];


    for (j = low; j <= high - 1; j++) {
        if (compare_descriptions(prod[j],description) < 0) {
            i++;
            swap_products(&prod[i], &prod[j]);
        }
    }
    swap_products(&prod[i + 1], &prod[high]);
    return (i + 1);
}

void quicksort(product prod[], int low, int high, char type[]){
    /* quicksort by products' price (type = "price") or by products' description (type = "description") */
    int d;

    if (low < high){
        if(!strcmp(type,"price"))
            d = divide_by_price(prod, low, high, (low + high)/2);
        if(!strcmp(type,"description"))
            d = divide_by_description(prod, low, high, (low + high)/2);
        quicksort(prod, low, d - 1, type);
        quicksort(prod, d + 1, high, type);
    }
}

void crescent_price_sort(){
    /* sorts products by their price */
    int i;
    product prod[PRODUCTS_MAX];

    /* creates a copy of products[] */
    for (i = 0; i < products_counter; i++)
        prod[i] = products[i];

    quicksort(prod, 0, products_counter - 1, "price");

    printf("Produtos\n");
    for(i = 0; i < products_counter; i++)
        printf("* %s %d %d\n", prod[i].description, prod[i].price, prod[i].stock);
}

void alphabetical_sort(){
    /* sorts products alphabetically */

    product prod[WEIGHT_MAX];
    int oid, i;

    scanf(" %d", &oid);

    if(oid >= orders_counter)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", oid);
    else{
        /* creates an array of products in a specific order */
        for (i = 0; i < orders[oid].products_in; i++) {
            prod[i] = products[orders[oid].pid_in_order[i]];
            prod[i].stock = orders[oid].product_quantities[orders[oid].pid_in_order[i]];
        }

        quicksort(prod, 0, orders[oid].products_in - 1, "description");

        printf("Encomenda %d\n", oid);
        for (i = 0; i < orders[oid].products_in; i++)
            printf("* %s %d %d\n", prod[i].description, prod[i].price, prod[i].stock);
    }
}

int main(){
    char c;

    while(1){
        /* gets command */
        c = getchar();

        if(c == 'x') break;

        switch(c){
            case 'a':
                new_product();
                break;
            case 'q':
                increase_stock();
                break;
            case 'N':
                new_order();
                break;
            case 'A':
                add_product_to_order();
                break;
            case 'r':
                decrease_stock();
                break;
            case 'R':
                remove_product_from_order();
                break;
            case 'C':
                calculate_cost();
                break;
            case 'p':
                change_price();
                break;
            case 'E':
                order_product_details();
                break;
            case 'm':
                order_product_ocurrence();
                break;
            case 'l':
                crescent_price_sort();
                break;
            case 'L':
                alphabetical_sort();
                break;
            default:
                break;
        }
    }
    return 0;
}
