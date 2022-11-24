#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proj1.h"

/*  
    uppercase letters for Constants.
    camelCase letters for Functions and Variables in a Global Scope.
    lowercase letters for normal Variables and Parameters.
*/

/* GLOBAL VARIABLES AND ARRAYS */
struct Product productList[PRODUCT_LIM] = {0};
int idCount = 0;

struct Order orderList[ORDER_LIM] = {0};
int orderCount = 0;

/* FUNCTIONS */
int main(void){
    while(inputHandler()){} /* Infinite loop until the command 'x' is detected. */
    return 0;
}

int inputHandler(void){
    char inputstring[INPUT_LIM];
    char command[1];
    char temp[INPUT_NUM_LIM][STRING_LIM] = {0}; /* An array to temporarily hold the parsed input. */
    int i = 0;
    char *token;

    /* Basic variables */
    char description[STRING_LIM];
    int price, weight, stock, idp, ide;

    /* Gathering the input. */
    fgets(inputstring, INPUT_LIM, stdin);
    inputstring[strcspn(inputstring, "\n")] = 0; /* If it exists, removes \n from the string. */
    strcpy(command, strtok(inputstring, " ")); /* Separates the command from the rest of the input. */

    token = strtok(NULL, ":");
    while(token != NULL && i < INPUT_NUM_LIM){
        strcpy(temp[i], token);
        i++;
        token = strtok(NULL, ":");
    }

    strcat(inputstring, ":");
    
    /* Only assigns the needed Parameters. Also calls the Function corresponding to each command. */
    switch (command[0]){
        case 'a': /* Adds a Product. */
            strcpy(description, temp[0]);
            price = strtol(temp[1], NULL, 10);
            weight = strtol(temp[2], NULL, 10);
            stock = strtol(temp[3], NULL, 10);

            commandAddProduct(description, price, weight, stock);
            return 1;
        case 'q': /* Adds stock to an existing Product. */
            idp = strtol(temp[0], NULL, 10);
            stock = strtol(temp[1], NULL, 10);

            commandAddStock(idp, stock);
            return 1;
        case 'N': /* Adds a new Order. */
            commandAddOrder();
            return 1;
        case 'A': /* Adds a Product, or stock, to an existing Order. */
            ide = strtol(temp[0], NULL, 10);
            idp = strtol(temp[1], NULL, 10);
            stock = strtol(temp[2], NULL, 10);

            commandAddProdOrder(ide, idp, stock);
            return 1;
        case 'r': /* Removes stock from an existing Product. */
            idp = strtol(temp[0], NULL, 10);
            stock = strtol(temp[1], NULL, 10);
            
            commandRemoveStock(idp, stock);
            return 1;
        case 'R': /* Removes Product from an existing Order. */
            ide = strtol(temp[0], NULL, 10);
            idp = strtol(temp[1], NULL, 10);

            commandRemoveProdOrder(ide, idp);
            return 1;
        case 'C': /* Calculates the Order's price. */
            ide = strtol(temp[0], NULL, 10);

            commandOrderPrice(ide);
            return 1;
        case 'p': /* Changes the price of a Product. */
            idp = strtol(temp[0], NULL, 10);
            price = strtol(temp[1], NULL, 10);

            commandChangePrice(idp, price);
            return 1;
        case 'E': /* Lists the description and stock of a Product in an Order. */
            ide = strtol(temp[0], NULL, 10);
            idp = strtol(temp[1], NULL, 10);

            commandProdOrder(ide, idp);
            return 1;
        case 'm': /* Lists the id of the Order with the most occurrence of a Product, */
                  /* or, if multiple Orders exist, the one with the smaller id. */
            idp = strtol(temp[0], NULL, 10);

            commandMostProdOrder(idp);
            return 1;
        case 'l': /* Lists all Products, in ascending prices, */
                  /* or, if multiple Products with the same price exist, in ascending id. */
            commandListProd();
            return 1;
        case 'L': /* Lists all Products in alphabetical order, regarding their descriptions. */
            ide = strtol(temp[0], NULL, 10);
            
            commandListProdOrder(ide);
            return 1;
        case 'x': /* Breaks the potentially infinite loop in main(). */
            return 0;
        default: /* If the Command is anything other than the ones stated above, it ignores it. */
            return 1;
    }
}

/* COMMAND FUNCTIONS */

void commandAddProduct(char description[STRING_LIM], int price, int weight, int stock){
    int idp = idCount;

    strcpy(productList[idp].description ,description);
    productList[idp].price = price;
    productList[idp].weight = weight;
    productList[idp].stock = stock;

    idCount++;
    printf("Novo produto %d.\n", idp);
    return;
}

void commandAddStock(int idp, int stock){
    /* Error Handling */
    if(idp >= idCount){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return;
    }
    /* End of Error Handling */

    productList[idp].stock += stock;
    return;
}

void commandAddOrder(){
    int ide = orderCount;
    orderCount++;

    printf("Nova encomenda %d.\n", ide);
    return;
}

void commandAddProdOrder(int ide, int idp, int stock){
    int i = 0;
    
    /* Error Handling */
    if(ide >= orderCount){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }else if(idp >= idCount){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }else if(stock > findIdpStock(idp)){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }else if((findOrderWeight(ide) + (stock * findIdpWeight(idp))) > ORDER_WEIGHT_LIM){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }
    /* End of Error Handling */

    productList[idp].stock -= stock;

    while(i < orderList[ide].prodcount){
        if(orderList[ide].products[i][0] == idp){
            orderList[ide].products[i][1] += stock;
            return;
        }
        i++;
    }

    orderList[ide].products[orderList[ide].prodcount][0] = idp;
    orderList[ide].products[orderList[ide].prodcount][1] = stock;
    orderList[ide].prodcount++;

    return;
}

void commandRemoveStock(int idp, int stock){
    /* Error Handling */
    if(idp >= idCount){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }else if(stock > findIdpStock(idp)){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock, idp);
        return;
    }
    /* End of Error Handling */

    productList[idp].stock -= stock;
    return;
}

void commandRemoveProdOrder(int ide, int idp){
    int index = findIdpInOrder(ide, idp);
    
    /* Error Handling */
    if(ide >= orderCount){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }else if(idp >= idCount){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    /* End of Error Handling */

    if(index >= 0){ /* If the Product isn't in the Order, nothing happens. */
        commandAddStock(idp, orderList[ide].products[index][1]); /* Restocks the system. */
        while(index < orderList[ide].prodcount - 1){ /*  Shifts every Product after the removed one, but doesn't erase the last element. */
            orderList[ide].products[index][0] = orderList[ide].products[index + 1][0];
            orderList[ide].products[index][1] = orderList[ide].products[index + 1][1];
            index++;
        }
        orderList[ide].prodcount--;
        /* Erasing the last element manually because the loop wouldn't work if the Orders had reached the limit. */
        orderList[ide].products[index][0] = 0;
        orderList[ide].products[index][1] = 0;
    }

    return;
}

void commandOrderPrice(int ide){
    int i = 0;
    unsigned long int price = 0; /* uli to prevent integer overflow. */
    int idp;

    /* Error Handling */
    if(ide >= orderCount){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    /* End of Error Handling */

    /* Iterates through every Product present in the Order and adds up the price. */
    while(i < orderList[ide].prodcount){
        idp = orderList[ide].products[i][0];
        price += orderList[ide].products[i][1] * findIdpPrice(idp);
        i++;
    }
    printf("Custo da encomenda %d %lu.\n", ide, price);
    return;
}

void commandChangePrice(int idp, int price){
    /* Error Handling */
    if(idp >= idCount){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }
    /* End of Error Handling */

    productList[idp].price = price;
    return;
}

void commandProdOrder(int ide, int idp){
    char description[STRING_LIM];
    int stock = 0;
    int idporder = findIdpInOrder(ide, idp);
    strcpy(description, productList[idp].description);

    /* Error Handling */
    if(ide >= orderCount){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }else if(idp >= idCount){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    /* End of Error Handling */

    if(idporder > -1){ /* If the Product is in the Order, displays the stock value in the Order. */
        stock = orderList[ide].products[idporder][1];
    }

    printf("%s %d.\n", description, stock); /* If it isn't, the default value 0 will be displayed. */
    return;
}

void commandMostProdOrder(int idp){
    int i = 0;
    int idporder;
    int maxstock = 0;
    int tempstock = 0;
    int ide = 0;

    /* Error Handling */
    if(idp >= idCount){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    /* End of Error Handling */

    if(orderCount == 0){
        return;
    }

    while(i < orderCount){
        idporder = findIdpInOrder(i, idp);
        if(idporder > -1){ /* Ignores Orders that don't have the Product. */
            tempstock = orderList[i].products[idporder][1];
            if(maxstock < tempstock){ /* if the new Order has higher stock, updates maxstock and the Order's ide. */
                maxstock = tempstock;
                ide = i;
            }
        }
        i++;
    }

    if(maxstock != 0){ /* Only displays if the Product is in an Order. */
        printf("Maximo produto %d %d %d.\n", idp, ide, maxstock);
    }
    return;
}

void commandListProd(void){
    int i = 0;
    int array[PRODUCT_LIM] = {0}; /* Temporary array that will be sorted and displayed. */

    while(i < idCount){ /* Initializes the array from 0 to idCount - 1 with the value of its index */
        array[i] = i;   /* (which is the same as idp in productList), */
        i++;            /* because only the idp needs to be sorted. */
    }
    printf("Produtos\n");
    mergeSort(array, 0, idCount - 1, -1); /* Sorting the idp array according to the Products' prices. */
    printSortedArray(array, idCount, -1); /* Displaying the sorted array. */
    return;
}

void commandListProdOrder(int ide){
    int i = 0;
    int array[ORDER_WEIGHT_LIM] = {0}; /* Temporary array that will be sorted and displayed. */ /* LIM CHANGE LIM CHANGE LIM CHANGE LIM CHANGE LIM CHANGE */
    int prodcount = orderList[ide].prodcount;
    
    /* Error Handling */
    if(ide >= orderCount){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    /* End of Error Handling */

    while(i < prodcount){                           /* Initializing the array from 0 to prodcount - 1 */
        array[i] = orderList[ide].products[i][0];   /* with the idp in the Order's Products. */
        i++;
    }
    printf("Encomenda %d\n", ide);
    mergeSort(array, 0, prodcount - 1, ide); /* Sorting the idp array according to the Products' descriptions. */
    printSortedArray(array, prodcount, ide); /* Displaying the sorted array. */
    return;
}


/* AUXILIARY FUNCTIONS */

int findOrderWeight(int ide){
    int weight = 0;
    int i = 0;

    while(i <= orderList[ide].prodcount){ /* weight += ProdStock * ProdWeight */
        weight += orderList[ide].products[i][1] * productList[orderList[ide].products[i][0]].weight;
        i++;
    }

    return weight;
}

int findIdpInOrder(int ide,int idp){ /* Searches for the Product in the Order */
    int i = 0;

    while(i < orderList[ide].prodcount){
        if(idp == orderList[ide].products[i][0]){
            return i;
        }
        i++;
    }

    return -1; /* Product not in Order. */
}

/* O sorted array contem apenas os idp dos produtos */
void printSortedArray(int array[], int n, int m){ /* m specifies the type of array being displayed. */
    int i = 0;

    if(m == -1){ /* productList array */
        while(i < n){
            printf("* %s %d %d\n", productList[array[i]].description, findIdpPrice(array[i]), findIdpStock(array[i]));
            i++;
        }
    }else{ /* Products in Order array */
        while(i < n){ /* m is also the ide of the Order. */
            printf("* %s %d %d\n", productList[array[i]].description, findIdpPrice(array[i]), findStockInOrder(m, array[i]));
            i++;
        }
    }

    return;
}

void mergeSort(int array[], int l, int r, int n){
    int m = (l + r) / 2;
    
    if(r <= l){ /* Break condition. */
        return;
    }

    mergeSort(array, l, m, n);
    mergeSort(array, m + 1, r, n);
    merge(array, l, m, r, n);

    return;
}

void merge(int array[], int l, int m, int r, int n){ /* n specifies the type of array being sorted. */
    int i, j, k, aux[PRODUCT_LIM];

    for(i = m + 1; i > l; i--){
        aux[i - 1] = array[i - 1];
    }for(j = m; j < r; j++){
        aux[r + m - j] = array[j + 1];
    }

    if(n == -1){ /* productList array. Sorted by price. */
        for(k = l; k <= r; k++){
            if(productList[aux[j]].price < productList[aux[i]].price || i > m){
                array[k] = aux[j--];
            }else{
                array[k] = aux[i++];
            }
        }
    }else{ /* Products in Order array. Sorted by description. */
        for(k = l; k <= r; k++){
            if(strcmp(productList[aux[j]].description, productList[aux[i]].description) < 0 || i > m){
                array[k] = aux[j--];
            }else{
                array[k] = aux[i++];
            }
        }
    }

    return;
}

/* Abstraction Functions */
int findIdpPrice(int idp){
    return productList[idp].price;
}

int findIdpWeight(int idp){
    return productList[idp].weight;
}

int findIdpStock(int idp){
    return productList[idp].stock;
}

int findStockInOrder(int ide, int idp){
    return orderList[ide].products[findIdpInOrder(ide, idp)][1];
}