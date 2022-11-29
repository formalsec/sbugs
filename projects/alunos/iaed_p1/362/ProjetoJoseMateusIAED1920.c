#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESC 63             /* Maximum amount of characters for the description of a product */
#define MAX_PROD 10000          /* Maximum amount of products in the database */
#define MAX_WEIGHT 200          /* Maximum weight for each order */

/*Auxiliary Functions */
int parse_instructions();       /* Function used to parse command and call respective command function */


/*Stuctures*/
typedef struct product{                     /* Product structure - desc = product description */
    char desc[MAX_DESC];                    /* idp = product id unique number used to identify each product */
    int price, weight, quant, idp;
} Product;

typedef struct prod_ord{                   /* Product structure for orders, simplified version of Product structure, just contanining the  */
    int idp;                               /* necessary information  for an order */
    int quant;
} Prod_order;

typedef struct encomenda{                  /* Order structure, contains order id (ide), weight of the order, how many products (counter) */
    int ide;                               /* and a list of simplified products */
    int weight;
    int counter;
    Prod_order prod_list[200];
} Encomenda;

/*Database */
Product lista_produtos[MAX_PROD];          /* List of Product where all the produtcs are saved */
Encomenda lista_encomendas[500];           /* List of Encomenda where all the orders are saved */
int Product_Counter = 0;                    
int Encomenda_Counter = 0;

/*Declare command functions*/
int comando_a();    /*Create new product - desc:price:weight:quant*/
int comando_q();     /*Adds stock to an existing product - idp:quant*/
int comando_h();      /*List all available products */
int comando_N();       /*Creates a new order*/
int comando_A();        /*Adds a product to order - ide:idp:quant*/
int comando_r();         /*Removes stock from an existing product - idp:quant*/
int comando_R();         /*Removes a product from a order - ide:idp*/
int comando_C();         /*Calculate the cost of the order - ide*/
int comando_p();        /*Change the price of an existing product - idp:preco*/
int comando_E();       /*Print desc and quant of a product from an order - ide:idp*/
int comando_m();      /*Lists the ide in which the given product has the biggest quantity idp*/
int comando_l();     /*Lists all existing products by crescent price order*/
int comando_L();    /*Lists all of the products inside a encomenda by alphabethical order*/



/*Declare sorting functions*/
void merge(Product list_to_order[], int left, int middle, int right, int type_flag); 
void mergeSort(Product list_to_order[], int left, int right, int type_flag); 
Product Laux[10000];            /* Aux array for sorting */
Product Raux[10000];            /* Aux array for sorting */
Product ordered_prod[10000];    /* Array which contains all the products to be ordered  */


/*Declaring user input*/
char comando;                   /* Where user command is stored */
char junk;                      /* Used to store junk input */

int main(){
    /*Read commands from the user*/
    while(1){
        /* printf("waiting for next command\n"); */
        comando = getchar();
        parse_instructions();
    }
    return 0;
}

int parse_instructions(){
    int junk_flag = 0;   /* Set to one when function receives arguments (extra enter when command requires extra arguments) */
    /*Function used to parse command and call respective command function*/
    getchar(); /* Junk */
    switch (comando){
    case 65:
        /* printf("Running command A\n") */
        junk_flag = comando_A();
        break;
    case 67:
        /* printf("Running command C\n") */
        junk_flag = comando_C();
        break;
    case 69:
        /* printf("Running command E\n") */
        junk_flag = comando_E();
        break;
    case 76:
        /* printf("Running command L\n") */
        junk_flag = comando_L();
        break;
    case 78:
        /* printf("Running command N\n"); */
        junk_flag = comando_N();
        break;
    case 82:
        /* printf("Running command R\n"); */
        junk_flag = comando_R();
        break;
    case 97:
        /* printf("Running command a\n"); */
        junk_flag = comando_a();
        break;
    case 104:
        /* printf("Running command h\n"); */
        junk_flag = comando_h();
        break;
    case 108:
        /* printf("Running command l\n"); */
        junk_flag = comando_l();
        break;
    case 109:
        /* printf("Running command m\n"); */
        junk_flag = comando_m();
        break;
    case 112:
        /* printf("Running command p\n"); */
        junk_flag = comando_p();
        break;
    case 113:
        /* printf("Running command q\n"); */
        junk_flag = comando_q();
        break;
    case 114:
        /* printf("Running command r\n"); */
        junk_flag = comando_r();
        break;
    case 120:
        /* printf("Command x, quitting"); */
        exit(0);
    default:
        break;
    }
    if (junk_flag){
        junk = getchar();
    }
    return 0;
}



/*Command functions*/
int comando_a(){
    /*Create new product - desc:price:weight:quant*/
    Product new_product;
    scanf("%[^:]:%d:%d:%d",new_product.desc,&new_product.price,&new_product.weight,&new_product.quant);
    new_product.idp = Product_Counter;
    lista_produtos[Product_Counter] = new_product;
    Product_Counter ++;
    printf("Novo produto %d.\n", new_product.idp);
    return 1;
}

int comando_h (){
    /*List all available products */
    int counter;
    Product prod;
    printf("PRODUTOS\n");
    for (counter = 0; counter < Product_Counter; counter++){  /* Loop over all the products */
        prod = lista_produtos[counter];
        printf("  Price: %d\n", prod.price);
        printf("  Weight: %d\n", prod.weight);
        printf("  Quant: %d\n", prod.quant);
        printf("  ID: %d\n", prod.idp);
        printf("  Desc: %s\n", prod.desc);
        putchar('\n');
    }
    
    return 0;
}

int comando_q(){
    /*Adds stock to an existing product - idp:quant*/
    int idp, quant;
    scanf("%d:%d", &idp, &quant);
    if (idp >= Product_Counter){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return 1;
    }
    lista_produtos[idp].quant += quant;         /* Update quant */
    return 1;
}

int comando_N(){
    /*Creates a new order*/
    Encomenda new_encomenda;
    new_encomenda.ide = Encomenda_Counter;
    new_encomenda.counter = 0;
    new_encomenda.weight = 0;
    lista_encomendas[Encomenda_Counter] = new_encomenda;
    printf("Nova encomenda %d.\n", Encomenda_Counter++);
    return 0;
}

int comando_A(){
    /*Adds a product to order - ide:idp:quant*/
    int counter, ide, idp, quant;
    Encomenda enco;
    Product prod;
    Prod_order prod_order;
    scanf("%d:%d:%d", &ide,&idp, &quant);

    if(ide >= Encomenda_Counter){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return 1;
    }
    if(idp >= Product_Counter){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp, ide);
        return 1;
    }
    prod = lista_produtos[idp];
    enco = lista_encomendas[ide];

    if(prod.quant < quant){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
        return 1;
    }
    if(enco.weight+(prod.weight * quant) > MAX_WEIGHT){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp, ide);
        return 1;
    }

    /* Check to see if product is not already in the list */
    for (counter = 0; counter < enco.counter; counter++){   /* Loop over all the products inside the order */
        prod_order = enco.prod_list[counter];
        if (prod_order.idp == idp){
            prod_order.quant += quant;              /* Increase the quantity */
            enco.weight += prod.weight * quant;   /* Increase the weight */
            enco.prod_list[counter] = prod_order; /* Add the product */
            lista_produtos[idp].quant -= quant;   /* Remove quant from stock */
            lista_encomendas[ide] = enco;     /* Append encomenda */

            return 1;
        } 
    }
    /* If not on the list */
    prod_order.idp = idp;
    prod_order.quant = quant;
    enco.weight += prod.weight * quant;  /* Update the encomenda weight */
    enco.prod_list[enco.counter] = prod_order; /* Add the product */
    enco.counter ++;                   /* Increase amout of products */
    lista_produtos[idp].quant -= quant;   /* Remove quant from stock */
    lista_encomendas[ide] = enco;     /* Append encomenda */

    return 1;
}

int comando_r(){
    /*Removes stock from an existing product - idp:quant*/
    int idp, quant;
    scanf("%d:%d", &idp, &quant);
    if(idp >= Product_Counter){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
        return 1;
    }
    if (quant > lista_produtos[idp].quant){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, idp);
        return 1;
    }
    lista_produtos[idp].quant -= quant;
    return 1;
}

int comando_R(){
    /*Removes a product from a order - ide:idp*/
    int ide, idp, counter;
    Encomenda enco;
    Prod_order prod_order;
    scanf("%d:%d", &ide, &idp);
    if (ide >= Encomenda_Counter){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp, ide);
        return 1;
    }
    if(idp >= Product_Counter){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return 1;
    }
    enco = lista_encomendas[ide];
    for(counter = 0; counter < enco.counter; counter++){    /* Loop over all products in an order */
        prod_order = enco.prod_list[counter];
        if (prod_order.idp == idp){
            enco.weight -= prod_order.quant * lista_produtos[idp].weight; /* Remove weight from encomenda */
            lista_produtos[idp].quant += prod_order.quant;                /* Update the store stock */
            prod_order.quant = 0;                                         /* Remove all the stock from order */
            enco.prod_list[counter] = prod_order;                         /* Append (update) prod_order */
            lista_encomendas[ide] = enco;                                 /* Append (update) encomenda */
            return 1; 
        }
    }    
    return 1;
}

int comando_C(){
    /*Calculate the cost of the order - ide*/
    int ide, total;
    int counter;
    Encomenda enco;
    Product prod;
    scanf("%d", &ide);
    
    if (ide >= Encomenda_Counter){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return 1;
    }

    enco = lista_encomendas[ide];
    total = 0;
    for (counter = 0; counter < enco.counter; counter++){  /* Loop over all products in a order */
        prod = lista_produtos[enco.prod_list[counter].idp];
        total += prod.price * enco.prod_list[counter].quant;
    }
    printf("Custo da encomenda %d %d.\n", ide, total);
    
    return 1;
}

int comando_p(){
    /*Change the price of an existing product - idp:preco*/
    int idp, preco;
    scanf("%d:%d", &idp, &preco);
    if (idp >= Product_Counter){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return 1;
    }
    lista_produtos[idp].price = preco;
    return 1;
}

int comando_E(){
    /*Print desc and quant of a product from an order - ide:idp*/
    int ide, idp, counter, quant = 0;
    Encomenda enco;
    Prod_order prod_order;
    scanf("%d:%d", &ide, &idp);

    if (ide >= Encomenda_Counter){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return 1;
    }
    if (idp >= Product_Counter){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return 1;
    }

    enco = lista_encomendas[ide];
    for(counter = 0; counter < enco.counter; counter++){ /* Loop over all the prodcuts in the order */
        prod_order = enco.prod_list[counter];
        if (prod_order.idp == idp){
             quant = prod_order.quant;
        }
    }
    printf("%s %d.\n", lista_produtos[idp].desc, quant);
    return 1;
}

int comando_m(){
    /*Lists the ide in which the given product has the biggest quantity idp*/
    int idp, ide, counter, aux_counter;
    int quant, max_quant;
    scanf("%d", &idp);

    if(idp >= Product_Counter){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return 1;
    }

    max_quant = 0;
    for(counter = 0; counter < Encomenda_Counter; counter++){ /* Loop over all orders */
        for(aux_counter = 0; aux_counter < lista_encomendas[counter].counter; aux_counter++){ /* Loop over all products in the order */
            if(idp == lista_encomendas[counter].prod_list[aux_counter].idp){
                quant = lista_encomendas[counter].prod_list[aux_counter].quant;
                if(quant > max_quant){
                    max_quant = quant;
                    ide = counter;
                }
            }
        }
    }
    if(max_quant){
        printf("Maximo produto %d %d %d.\n", idp, ide, max_quant);
    }

    return 1;
}

int comando_l(){
    /*Lists all existing products by crescent price order*/
    int counter;

    for(counter = 0; counter < Product_Counter; counter++){ /* Create array to sort */
        ordered_prod[counter] = lista_produtos[counter];
    }

    mergeSort(ordered_prod, 0, Product_Counter-1, 1); /* Merge sort using first comparison method (by price) */

    /* Print ordered list */
    printf("Produtos\n");
    for(counter = 0; counter < Product_Counter; counter++){
        printf("* %s %d %d\n", ordered_prod[counter].desc, ordered_prod[counter].price, ordered_prod[counter].quant);
    }
    return 0;
}

int comando_L(){
    /*Lists all of the products inside a encomenda by alphabethical order*/
    int ide, counter, idp, quant;
    int aux_counter;
    Encomenda enco;
    scanf("%d", &ide);

    if(ide >= Encomenda_Counter){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return 1;
    }

    enco = lista_encomendas[ide];               /* I am talking about this encomenda */
    /* Setting the array with all the products I want to order */
    for(counter = 0; counter < enco.counter; counter++){    /* Loop over all the products in the order */
        idp = enco.prod_list[counter].idp;
        ordered_prod[counter] = lista_produtos[idp];        /* Create the arrey to sort */
    }

    mergeSort(ordered_prod, 0, enco.counter-1, 0); /* MergeSort using second comparison method (by description) */
    
    /* Print ordered list */    
    printf("Encomenda %d\n", ide);
    for(counter = 0; counter <  enco.counter; counter++){ /* Loop over all the ordered array to mach the unsorted parameters */
        idp = ordered_prod[counter].idp; /* What I am searching for */
        for(aux_counter = 0; aux_counter < enco.counter; aux_counter++){ /* Look in the order for the sorted product */
            if(idp == enco.prod_list[aux_counter].idp){
                quant = enco.prod_list[aux_counter].quant;
            }
        }
        if (quant)printf("* %s %d %d\n",ordered_prod[counter].desc, ordered_prod[counter].price, quant);   
    }
    return 1;
}



/*SORTING FUNCTIONS*/
void mergeSort(Product list_to_order[], int left, int right, int type_flag){
    /*Dividing the array - recursive - initial left = 0; initial right = max index*/
    /*type_flag = 1, means I am sorting prices, type_flag = 0 means I am sorting descriptions*/
    int middle = left + (right - left) / 2; 
    if (left < right){  

        mergeSort(list_to_order, left, middle, type_flag);
        mergeSort(list_to_order, middle+1, right, type_flag); 

        merge(list_to_order, left, middle, right, type_flag); 
    } 
} 

void merge(Product list_to_order[], int left, int middle, int right, int type_flag){
    /*Merge the arrays - Auxiliary function called by mergeSort*/
    /*type_flag = 1, means I am sorting prices, type_flag = 0 means I am sorting descriptions*/
    int i, j, k; 
    int n1 = middle - left + 1; 
    int n2 =  right - middle; 

    /*Save data to temp arrays*/
    /*On both cases I will save the products*/
    for (i = 0; i < n1; i++){ 
        Laux[i] = list_to_order[left + i];
    }
    for (j = 0; j < n2; j++){ 
        Raux[j] = list_to_order[middle + 1+ j]; 
    }

    /*Join arrays*/
    i = 0;  
    k = left;  
    j = 0;  
    while (i < n1 && j < n2){                   /* When joining need to use two different comparison methods */
        if(type_flag){                           /* Comparison method one (used to sort prices) */
            if (Laux[i].price <= Raux[j].price){ 
                list_to_order[k] = Laux[i++];  
            } 
            else{                              
                list_to_order[k] = Raux[j++];  
            } 
            k++;
        }
        else{                                   /* Second comparion method, by description (using strcmp from string.h) */
            if(strcmp(Laux[i].desc, Raux[j].desc) <= 0){
                list_to_order[k] = Laux[i++];
            }
            else{
                list_to_order[k] = Raux[j++];
            }
            k++;
        } 
    } 

    /*Copy any leftover elements*/
    while (i < n1){ 
        list_to_order[k++] = Laux[i++]; 
    } 
    while (j < n2){ 
        list_to_order[k++] = Raux[j++]; 
    } 
}

