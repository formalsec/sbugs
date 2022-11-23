#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "IAED.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function that enters the product into the system and fills its details according to the input given */

void a_parsing(char input[MAX_INPUT], int productid){
    int i = 1;
    char *token = NULL;
    PRODUCT *product = (PRODUCT*)can_fail_calloc(1, sizeof(PRODUCT));
    product->id = productid;
    token = strtok(input, ":");
    while(token != NULL){
        switch(i){
            case 1: {
                strcpy(product->desc, token);
                break;
            }
            case 2: {
                product->price = atoi(token);
                break;
            }
            case 3: {
                product->weight = atoi(token);
                break;
            }
            case 4: {
                product->stock = atoi(token);
            }
            default: break;
        }
        i++;
        token = strtok(NULL, ":");
    }
    lstproducts[productid] = product;
}

/* Function that adds stock to a product in the system */

void add_stock(char input[MAX_INPUT]){
    int i = 0, qtd = 0;
    char *token = NULL;
    token = strtok(input, ":");
    i = atoi(token);
    if (lstproducts[i] == NULL){      /* Gives an error if the product doesn't exist in the system */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", i);
    }
    else {
        token = strtok(NULL, "\0");
        qtd = atoi(token);
        lstproducts[i]->stock += qtd;
    }
}

/* Function that removes stock from a product in the system */

void remove_stock(char input[MAX_INPUT]){
    int i = 0, qtd = 0;
    char *token = NULL;
    token = strtok(input, ":");
    i = atoi(token);
    if (lstproducts[i] == NULL){     /* Same as above and recurrent along the program */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", i);
    }
    else {
        token = strtok(NULL, "\0");
        qtd = atoi(token);
        if(lstproducts[i]->stock >= qtd){
            lstproducts[i]->stock -= qtd;
        }
        else{    /* Gives an error if it's impossible to remove stock from the product due to its quantity being lower than the qtd we want to remove */
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, i);
        }
    }
}

/* Function that adds an order to the system */

void create_order(int orderid){
    ORDER *order = (ORDER*)can_fail_calloc(1, sizeof(ORDER));
    order->orderid = orderid;
    order->orderweight = 0;
    order->sizelstproducts = 0;
    lstorders[orderid] = order;
}

/* Function that adds a product to an order, if the product was already in the order, it stacks its stock in the order */

void add_product_to_order(char input[MAX_INPUT]){
    int ide = 0, qtd = 0, idp = 0, i = 0, flag = 0, c = 0;
    char *token = NULL;
    token = strtok(input, ":");
    ide = atoi(token);
    token = strtok(NULL, ":");
    idp = atoi(token);
    token = strtok(NULL, "\0");
    qtd = atoi(token);
    if (lstorders[ide] == NULL){   /* Gives an error if the order doesn't exist in the system */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if(lstproducts[idp] == NULL){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else if(qtd > lstproducts[idp]->stock){  /* Gives an error if the quantity the order wants from the product surprasses its quantity in stock in the system */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else{
        if(lstorders[ide]->orderweight + lstproducts[idp]->weight * qtd <= 200) {
            for(i = 0; i < lstorders[ide]->sizelstproducts; i++) {
                if(strcmp(lstproducts[idp]->desc, lstorders[ide]->orderlstproducts[i].desc) == 0) {
                    flag++;
                    c = i;
                }
            }
            if(flag == 0){
                lstorders[ide]->orderlstproducts[lstorders[ide]->sizelstproducts] = *lstproducts[idp];
                lstorders[ide]->orderlstproducts[lstorders[ide]->sizelstproducts].stock = qtd;
                lstorders[ide]->sizelstproducts++;
                lstorders[ide]->orderweight += lstproducts[idp]->weight * qtd;
                lstproducts[idp]->stock -= qtd;
                lstproducts[idp]->times_in_order++;
            }
            else{
                lstorders[ide]->orderlstproducts[c].stock += qtd;
                lstproducts[idp]->stock -= qtd;
                lstorders[ide]->orderweight += lstproducts[idp]->weight * qtd;
            }
        }
        else{    /* Gives an error if the order's weight surprasses 200 when adding the product */
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
    }
}

/* Function that removes a product from an order */

void remove_product_from_order(char input[MAX_INPUT]){
    int ide = 0, idp = 0, i = 0, flag = 0, c = 0;
    char *token = NULL;
    token = strtok(input, ":");
    ide = atoi(token);
    token = strtok(NULL, "\0");
    idp = atoi(token);
    if (lstorders[ide] == NULL){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if(lstproducts[idp] == NULL) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else{
        for(i = 0; i < lstorders[ide]->sizelstproducts; i++) {
            if(strcmp(lstorders[ide]->orderlstproducts[i].desc, lstproducts[idp]->desc) == 0) {
                flag = i;
                lstproducts[idp]->stock += lstorders[ide]->orderlstproducts[flag].stock;
                lstorders[ide]->orderweight -= lstorders[ide]->orderlstproducts[flag].weight * lstorders[ide]->orderlstproducts[flag].stock;
                if(flag == lstorders[ide]->sizelstproducts - 1){
                    lstorders[ide]->orderlstproducts[flag].id = 0;
                    strcpy(lstorders[ide]->orderlstproducts[flag].desc, "\0");
                    lstorders[ide]->orderlstproducts[flag].price = 0;
                    lstorders[ide]->orderlstproducts[flag].weight = 0;
                    lstorders[ide]->orderlstproducts[flag].stock = 0;
                }
                for(c = flag; c < lstorders[ide]->sizelstproducts - 1; c++){
                    lstorders[ide]->orderlstproducts[c] = lstorders[ide]->orderlstproducts[c+1];
                }
                lstorders[ide]->sizelstproducts--;
                lstproducts[idp]->times_in_order--;
            }
        }
    }
}

/* Function that calculates the total cost of an order */

void calc_order_cost(char input[MAX_INPUT]){
    int ide = 0, total = 0, i = 0;
    ide = atoi(input);
    if (lstorders[ide] == NULL){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        for(i = 0; i < lstorders[ide]->sizelstproducts; i++){
            total += lstproducts[lstorders[ide]->orderlstproducts[i].id]->price * lstorders[ide]->orderlstproducts[i].stock;
        }
        printf("Custo da encomenda %d %d.\n", ide, total);
    }

}

/* Function that changes the price of a product within the system */

void change_product_price(char input[MAX_INPUT]){
    int idp = 0, new_price = 0;
    char *token = NULL;
    token = strtok(input, ":");
    idp = atoi(token);
    token = strtok(NULL, "\0");
    new_price = atoi(token);
    if (lstproducts[idp] == NULL){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        lstproducts[idp]->price = new_price;
    }
}

/* Function that shows the description and stock of a product in an order */

void list_product_in_order(char input[MAX_INPUT]){
    int idp = 0, ide = 0, i = 0, flag = 0;
    char *token = NULL;
    token = strtok(input, ":");
    ide = atoi(token);
    token = strtok(NULL, "\0");
    idp = atoi(token);
    if (lstorders[ide] == NULL){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if(lstproducts[idp] == NULL) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else{
        for(i = 0; i < lstorders[ide]->sizelstproducts; i++) {
            if (strcmp(lstproducts[idp]->desc, lstorders[ide]->orderlstproducts[i].desc) == 0) {
                flag++;
                printf("%s %d.\n", lstorders[ide]->orderlstproducts[i].desc, lstorders[ide]->orderlstproducts[i].stock);
            }
        }
        if(flag == 0){  /* If the product isn't in the order, its quantity is zero */
            printf("%s 0.\n", lstproducts[idp]->desc);
        }
    }
}

/* Function that shows the order where a certain product is the most amount of times  */

void show_order_of_max_times_product(char input[MAX_INPUT], int max){
    int idp = 0, ide = 0, i = 0, final_ide = 0, qtd = 0;
    idp = atoi(input);
    if(lstproducts[idp] == NULL){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else if(lstproducts[idp]->times_in_order != 0){
        for(ide = 0; ide < max; ide++){
            for(i = 0; i < lstorders[ide]->sizelstproducts; i++) {
                if(strcmp(lstorders[ide]->orderlstproducts[i].desc, lstproducts[idp]->desc) == 0 && lstorders[ide]->orderlstproducts[i].stock > qtd){
                    final_ide = ide;
                    qtd = lstorders[final_ide]->orderlstproducts[i].stock;
                }
            }
        }
        printf("Maximo produto %d %d %d.\n", idp, final_ide, qtd);
    }
}

/* Auxiliar function for mergesort */

void merge(PRODUCT a[], int left, int m, int right){
    int i = 0, j = 0, k = 0;
    for (i = m+1; i > left; i--)
        aux[i-1] = a[i-1];
    for(j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    for(k = left; k <= right; k++){
        if(aux[j].price < aux[i].price || i > m){
            a[k] = aux[j--];
        }
        else if(aux[j].id == aux[i].id){
            if (aux[j].id < aux[i].id){
                a[k] = aux[j--];
            }
            else{
                a[k] = aux[i++];
            }
        }
        else {
            a[k] = aux[i++];
        }
    }
}

/* Function that sorts the products in the system by their price (ascending order) */

void mergesort(PRODUCT a[], int l, int r){
    int m = (r+l)/2;
    if (r <= l)
        return;
    mergesort(a, l, m);
    mergesort(a, m+1, r);
    merge(a, l, m, r);
}

/* Auxiliar function for mergesort_alphabet */

void merge_alphabet(PRODUCT a[], int left, int m, int right){
    int i = 0, j = 0, k = 0;
    for (i = m+1; i > left; i--)
        aux[i-1] = a[i-1];
    for(j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    for(k = left; k <= right; k++){
        if(strcmp(aux[j].desc, aux[i].desc) < 0 || i > m){
            a[k] = aux[j--];
        }
        else {
            a[k] = aux[i++];
        }
    }
}

/* Function that sorts the products in a certain order by alphabetical order */

void mergesort_alphabet(PRODUCT a[], int l, int r){
    int m = (r+l)/2;
    if (r <= l)
        return;
    mergesort_alphabet(a, l, m);
    mergesort_alphabet(a, m+1, r);
    merge_alphabet(a, l, m, r);
}

/* Function that prints a list of all the products in the system by ascending order of price */

void print_lst_products(int max){
    int i = 0;
    PRODUCT *lstproducts_aux = (PRODUCT*) can_fail_calloc(10000, sizeof(PRODUCT));
    for(i = 0; i < max; i++){
        lstproducts_aux[i] = *lstproducts[i];
    }
    mergesort(lstproducts_aux, 0, max-1);
    printf("Produtos\n");
    for(i = 0; i < max; i++){
        printf("* %s %d %d\n",lstproducts_aux[i].desc, lstproducts_aux[i].price, lstproducts_aux[i].stock);
    }
    free(lstproducts_aux);
}

/* Function that prints all the products within an order alphabetically */

void print_lst_products_in_order(char input[MAX_INPUT]){
    int i = 0, ide = 0;
    ORDER *order_aux = (ORDER*) can_fail_calloc(1, sizeof(ORDER));
    ide = atoi(input);
    if(lstorders[ide] == NULL){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else {
        order_aux->sizelstproducts = lstorders[ide]->sizelstproducts;
        for (i = 0; i < lstorders[ide]->sizelstproducts; i++) {
            order_aux->orderlstproducts[i] = lstorders[ide]->orderlstproducts[i];
        }
        mergesort_alphabet(order_aux->orderlstproducts, 0, order_aux->sizelstproducts - 1);
        printf("Encomenda %d\n", ide);
        for (i = 0; i < order_aux->sizelstproducts; i++) {
            printf("* %s %d %d\n", order_aux->orderlstproducts[i].desc, lstproducts[order_aux->orderlstproducts[i].id]->price,
                   order_aux->orderlstproducts[i].stock);
        }
    }
    free(order_aux);
}

/* Main function that simulates the functionality of a logistics system */

int main(){
    int i = 0, j = 0, c = 0, k = 0;
    while(1) {
        char command = '\0';
        char input[MAX_INPUT] = "\0";
        scanf("%c", &command);   /* Scan of the stdin for the command to be used */
        switch (command) {              /* Choice of the command */
            case 'a': {
                scanf("%s", input);
                a_parsing(input, i);
                printf("Novo produto %d.\n", i);
                i++;
                break;
            }
            case 'q': {
                scanf("%s", input);
                add_stock(input);
                break;
            }
            case 'r':{
                scanf("%s", input);
                remove_stock(input);
                break;
            }
            case 'R':{
                scanf("%s", input);
                remove_product_from_order(input);
                break;
            }
            case 'C':{
                scanf("%s", input);
                calc_order_cost(input);
                break;
            }
            case 'p':{
                scanf("%s", input);
                change_product_price(input);
                break;
            }
            case 'E':{
                scanf("%s", input);
                list_product_in_order(input);
                break;
            }
            case 'N':{
                create_order(j);
                printf("Nova encomenda %d.\n", j);
                j++;
                break;
            }
            case 'm':{
                scanf("%s", input);
                show_order_of_max_times_product(input, j);
                break;
            }
            case 'A':{
                scanf("%s", input);
                add_product_to_order(input);
                break;
            }
            case 'l':{
                print_lst_products(i);
                break;
            }
            case 'L':{
                scanf("%15000s", input);
                print_lst_products_in_order(input);
                break;
            }
            case 'x': {                 /* Closes the system and deallocates the memory used */
                for(c = 0; c < i; c++){
                    free(lstproducts[c]);
                }
                for(k = 0; k < j; k++){
                    free(lstorders[k]);
                }
                return 0;
            }
            default:
                break;
        }
    }
}
