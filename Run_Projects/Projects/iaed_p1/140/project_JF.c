#include <stdio.h>
#include <strings.h>

/*#################################################################################################
  #################################################################################################
  ###                                                                                           ###
  ###                                 MAX VALUES && DIMENTIONS                                  ###
  ###                                                                                           ###
  #################################################################################################
  ################################################################################################# */
  

#define MAX_DESCRIPTION 63
#define MAX_N_PRODUCTS 10000
#define MAX_ORDER_WEIGHT 200
#define MAX_N_ORDERS 500

/*#################################################################################################
  #################################################################################################
  ###                                                                                           ###
  ###                                        STRUCTURES                                         ###
  ###                                                                                           ###
  #################################################################################################
  #################################################################################################*/


typedef struct product{
    char description[MAX_DESCRIPTION + 1]; /*extra slot for \0*/
    int price;
    int weight;
    int stock;

}product;

typedef struct order{
    int products[2][MAX_ORDER_WEIGHT]; /*array of product ids and amounts*/
    int next_index; /*stores the next free slot for a product */
    int weight;

}order;

/*#################################################################################################
  #################################################################################################
  ###                                                                                           ###
  ###                                     GLOBAL VARIABLES                                      ###
  ###                                                                                           ###
  #################################################################################################
  #################################################################################################*/


product warehouse[MAX_N_PRODUCTS];
int next_p_id; /*id for the next product created*/

int print_warehouse[MAX_N_PRODUCTS]; /* products id in print order, after sort_warehouse call */

order order_list[MAX_N_ORDERS];
int next_o_id; /*id for the next order created*/

/*#################################################################################################
  #################################################################################################
  ###                                                                                           ###
  ###                                     SORTING FUNCTIONS                                     ###
  ###                                                                                           ###
  #################################################################################################
  #################################################################################################*/


/*
* int compare_price(int pos_a, pos_b)
*   
*   Compararer for partion_warehouse, compares price
*   
*   Input: int pos_a -> position in print_warehouse that contains the id of the first product 
*          int pos_b -> position in print_warehouse that contains the id of the second product 
*
*   Output: 1 -> should be first
*           0 -> should be after
*
*   Observations: Ties are setled with id, lesser comes first; is called by partion_wearehouse
*/
int compare_price(int pos_a, int pos_b){
    int id_a = print_warehouse[pos_a];
    int id_b = print_warehouse[pos_b];

    if (warehouse[id_a].price < warehouse[id_b].price){
        return 1;

    }else if (warehouse[id_a].price == warehouse[id_b].price){
        if (id_a < id_b){
            return 1;

        }else{
            return 0;

        }

    }else{
        return 0;

    }
}


/*
* int partition_warehouse(int left, right)
*   
*   Partioner for quicksort_warehouse, splits the array, the parts, if not unitary will be threated
*   as a new array to sort
*   
*   Input: int left -> left limit of the print_warehouse array 
*          int right ->  right limit of the print_warehouse array 
*
*   Output: int position where the array will split
*
*   Observations: print_warehouse is altered; calls compare_price; is called by quicksort_warehouse 
*/
int partition_warehouse(int left, int right){
    int l = left - 1;
    int r = right;
    int pivot = right;
    int tmp;

    /*Goes through the print array until the place for the pivot is found*/
    while (l < r){
        while(compare_price(++l, pivot)); /*approaches from the left*/
        while(compare_price(pivot, --r)){ /*approcheas from the right*/
            if (r == left){ /* in case pivot is the lesser element */
                break;

            }
        }

        if (l < r){
            /* lements on the left of the pivot that are greater than it swap with elements on the
             right that are smaller */
            tmp = print_warehouse[l];
            print_warehouse[l] = print_warehouse[r];
            print_warehouse[r] = tmp;

        }
    }

    /*pivot is swaped into palce */
    tmp = print_warehouse[l];
    print_warehouse[l] = print_warehouse[right];
    print_warehouse[right] = tmp;

    return l;
    
}


/*
* void quicksort_warehouse(int left, int right)
*   
*   Sorts the print_wearehouse (array containing the product ids), sorts by price low to high.
*               
*   Input:  int left -> left limit of the print_warehouse array 
*           int right ->  right limit of the print_warehouse array
*
*   Observations: print_warehouse is altered; calls partion_warehouse and itself (operates 
*           recursively)
*/
void quicksort_warehouse(int left, int right){
    int i;

    if (right <= left){ /* checks for unitarium vectors or non vectores*/
        return;

    }

    i = partition_warehouse(left, right); /*position where the array is split*/
    quicksort_warehouse(left, i - 1); /*recursive call for left part of the array*/
    quicksort_warehouse(i+1, right); /*recursive call for righ part of the array*/

}


/*
* int compare_description(int pos_a, int pos_b, int order_id)
*   
*   Compararer for partion_order, compares descriptions
*   
*   Input: int pos_a -> position in order's product array that contains the id of the first product 
*          int pos_b -> position in order's product array that contains the id of the second product
*          int order_id -> id for the order in question 
*
*   Output: 1 -> should be first
*           0 -> should be after
*
*   Observations: Ties are ignored; called by partition_order
*/
int compare_description(int pos_a, int pos_b, int order_id){
    int product_id_a = order_list[order_id].products[0][pos_a];
    int product_id_b = order_list[order_id].products[0][pos_b];

    /*strcasecmp returns int < 0 if string is first in alphabethical order*/
    if (strcasecmp(warehouse[product_id_a].description, warehouse[product_id_b].description) < 0){
        return 1;

    }else{
        return 0;

    }
}


/*
* int partition_order(int left, int right, int order_id)
*   
*   Partioner for quicksort_warehouse, splits the array, the parts, if not unitary will be threated
*   as a new array to sort
*   
*   Input: int left -> left limit of the print_warehouse array 
*          int right ->  right limit of the print_warehouse array 
*          int order_id -> id for the order in question 
*
*   Output: int postion where the array will split
*
*   Observations: Ties are ignored; called by partition_order
*/
int partition_order(int left, int right, int order_id){
    int l = left - 1;
    int r = right;
    int pivot = right;
    int tmp_id, tmp_amount;

    /*Goes through the order until the place for the pivot is found*/
    while (l < r){
        while(compare_description(++l, pivot, order_id)); /*approaches from the left*/
        while(compare_description(pivot, --r, order_id)){ /*approcheas from the right*/
            if (r==left){ /* in case pivot is the lesser element */
                break;

            }
        }

        if (l < r){
            /* lements on the left of the pivot that are greater than it swap with elements on the
             right that are smaller (swaps ids [0] and amounts [1])*/
            tmp_id = order_list[order_id].products[0][l];
            order_list[order_id].products[0][l] = order_list[order_id].products[0][r];
            order_list[order_id].products[0][r] = tmp_id;

            tmp_id = order_list[order_id].products[1][l];
            order_list[order_id].products[1][l] = order_list[order_id].products[1][r];
            order_list[order_id].products[1][r] = tmp_id;

        }
    }
    
        /*pivot is swaped into palce*/
        tmp_id = order_list[order_id].products[0][l];
        order_list[order_id].products[0][l] = order_list[order_id].products[0][right];
        order_list[order_id].products[0][right] = tmp_id;

        tmp_amount = order_list[order_id].products[1][l];
        order_list[order_id].products[1][l] = order_list[order_id].products[1][right];
        order_list[order_id].products[1][right] = tmp_amount;

        return l;
    
}


/*
* void quicksort_order(int left, int right, int order_id)
*   
*   Sorts the order(array containing the product ids), sorts by price low to high.
*   
*   Input:  int left -> left limit of the order's product array 
*           int right ->  right limit of the order's pruduct array
*           int order_id -> id for the order in question
*
*   Observations: order is altered; calls partion_order and itself (operates recursively)
*/
void quicksort_order(int left, int right, int order_id){
    int i;

    if (right <= left){ /* checks for unitarium vectors or non vectores */
        return;

    }

    i = partition_order(left, right, order_id); /*position where the array is split*/
    quicksort_order(left, i - 1, order_id); /*recursive call for left part of the array*/
    quicksort_order(i+1, right, order_id); /*recursive call for righ part of the array*/
}

/*#################################################################################################
  #################################################################################################
  ###                                                                                           ###
  ###                                      MAIN FUNCTIONS                                       ###
  ###                                                                                           ###
  #################################################################################################
  #################################################################################################*/


/*
* void a(char description[], int price, int weight, int amount)
*   
*   Adds a new product to the warehouse
*   
*   Input: char description -> new product's description  
*          int price -> new product's price
*          int weight -> new product's weight
*          int amount -> new product's amount in the warehouse
*
*   Prints: "Novo Produto <product_id>"
*
*   Observations: warehouse is altered
*/
void a(char description[], int price, int weight, int amount){
    int i;

    /*fills the new product's atribuits with the input*/
    for(i = 0; description[i] != '\0' && i < MAX_DESCRIPTION; i++){
        warehouse[next_p_id].description[i] = description[i];

    }

    warehouse[next_p_id].price = price;
    warehouse[next_p_id].weight = weight;
    warehouse[next_p_id].stock = amount;

    printf("Novo produto %d.\n", next_p_id++); /*next product id is updated */

}


/*
* void q(int id, int amount)
*   
*   Adds stock to an existing product
*   
*   Input: int product_id -> product's id
*          int amount -> amount to add to the warehouse
*
*   Prints: Error or nothing
*
*   Observations: warehouse is altered
*/
void q(int product_id, int amount){
    /*product exists?*/
    if (product_id >= next_p_id){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", product_id);

    }else{
        warehouse[product_id].stock += amount;

    }
}


/*
* void N()
*   
*   Creates a new order
*
*   Prints: "Nova encomenda <order_id>"
*   
*   Observations: order_list is altered
*/
void N(){
    order_list[next_o_id].weight = 0;
    order_list[next_o_id].next_index = 0;
    printf("Nova encomenda %d.\n", next_o_id++); /*next order id is updated */
}


/*
* void q(int id, int amount)
*   
*   Adds a product to an order or updates the curent amount
*   
*   Input: int order_id -> order's id
*          int product_id -> product's id
*          int amount -> amount to add to the order
*
*   Prints: Error or nothing
*
*   Observations: warehouse and order_list are altered
*/
void A(int order_id, int product_id, int amount){
    int next_product_id, i;

    /*order exists?*/
    if(order_id >= next_o_id){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", 
        product_id, order_id);

    /*product exists?*/
    }else if(product_id >= next_p_id){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", 
        product_id, order_id);

    /*enough stock?*/
    }else if(warehouse[product_id].stock < amount){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",
        product_id, order_id);

    /*enough free weight?*/
    }else if(MAX_ORDER_WEIGHT - order_list[order_id].weight < amount * warehouse[product_id].weight){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",
        product_id, order_id);
    
    }else{

        next_product_id = order_list[order_id].next_index;

        /* checks if the producty already exists in the order*/
        for (i = 0; i < next_product_id; i++){

            if (order_list[order_id].products[0][i] == product_id){
                /*if the product is found updates amount and stops cicle*/
                order_list[order_id].products[1][i] += amount;
                break; 

            }
        }

        /*if the product wasnt in the order cicle runs till the end*/
        if (i == next_product_id){

            order_list[order_id].products[0][next_product_id] = product_id;
            order_list[order_id].products[1][next_product_id] = amount; 
            order_list[order_id].next_index++;

        }
        
        /*updates order weight and warehouse stock*/
        order_list[order_id].weight += amount * warehouse[product_id].weight;
        warehouse[product_id].stock -= amount;

    }

}


/*
* void r(int product_id, int amount)
*   
*   Removes stock to an existing product
*   
*   Input: int product_id -> product's id
*          int amount -> amount to add to the order
*
*   Prints: Error or nothing
*
*   Observations: warehouse is altered
*/
void r(int product_id, int amount){
    /*product exists?*/
    if(product_id >= next_p_id){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", product_id);

    /*enough stock?*/
    }else if(warehouse[product_id].stock < amount){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", 
        amount, product_id);

    }else{
        warehouse[product_id].stock -= amount;

    }  
}


/*
* void R(int order_id, int product_id)
*   
*   Removes a product from an order
*   
*   Input: int order_id -> order's id
*          int product_id -> product's id
*
*   Prints: Error or nothing
*
*   Observations: warehouse and order_list are altered
*/
void R(int order_id, int product_id){
    int i, last_p, amount;

    /*order exist?*/
    if(order_id >= next_o_id){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", product_id, 
        order_id);

    /*product exists?*/
    }else if(product_id >= next_p_id){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", product_id, 
        order_id);

    }else{
        /* looks for the product */
        for (i = 0; i < order_list[order_id].next_index; i++){
            if (order_list[order_id].products[0][i] == product_id){/*if the product is found */
                amount = order_list[order_id].products[1][i];

                /*product amount in the order is placed back in stock*/
                warehouse[product_id].stock += amount;
                /*order weight is updated*/
                order_list[order_id].weight -= amount * warehouse[product_id].weight;

                last_p = order_list[order_id].next_index-- - 1;  /*next_id is decreased*/

                 /*if the producuct isnt in the last slot, its replaced by the last product*/
                if(i != last_p){
                    order_list[order_id].products[0][i] = order_list[order_id].products[0][last_p];
                    order_list[order_id].products[1][i] = order_list[order_id].products[1][last_p];
                }

                break; 

            }
        }
    }
}


/*
* void C(int order_id)
*   
*   Calculates the price of an order
*   
*   Input: int order_id -> order's id
*
*   Prints: Error or "Custo da encomenda <total>"
*/
void C(int order_id){
    int total = 0, price, amount, i;

    /*order exists?*/
    if(order_id >= next_o_id){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", order_id);
    
    }else{

        for (i = 0; i < order_list[order_id].next_index; i++){
            /*adds the amount of each product multipled by its price found in the warehouse*/
            
            amount = order_list[order_id].products[1][i];
            price = warehouse[order_list[order_id].products[0][i]].price;

            total += amount * price;  

        }

        printf("Custo da encomenda %d %d.\n", order_id, total);

    }
}


/*
* void p(int product_id, int price)
*   
*   Changes a product's price
*   
*   Input: int product_id -> product's id
*          int price -> new price for the product
*
*   Prints: Error or nothing
*
*   Observations: warehouse is altered
*/
void p(int product_id, int price){
    /*product exists?*/
    if(product_id >= next_p_id){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", product_id);

    }else{
        warehouse[product_id].price = price;

    }
}


/*
*void E(int order_id, int product_id)
*   
*   Lists the description and amount of a product in an order
*   
*   Input: int order_id -> order's id
*          int product_id -> product's id
*
*   Prints: Error or nothing
*/
void E(int order_id, int product_id){
    int c, i;
    /*order exist?*/
    if(order_id >= next_o_id){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order_id);

    /*product exists?*/
    }else if(product_id >= next_p_id){
        printf("Impossivel listar produto %d. Produto inexistente.\n", product_id);
    
    }else{
        for(i = 0; (c = warehouse[product_id].description[i]) != '\0' && i < MAX_DESCRIPTION; i++){
            putchar(c);

        }

        /* checks if the producty is in the order*/
        for (i = 0; i < order_list[order_id].next_index; i++){
            if (order_list[order_id].products[0][i] == product_id){
                /*if the product is found prints amount and stops cicle*/
                printf(" %d.\n", order_list[order_id].products[1][i]);
                break;

            }
        }

        /*if the product wasnt in the order cicle runs till the end*/
        if (i == order_list[order_id].next_index){
            printf(" 0.\n");    
        
        }
    }
}


/*
* void m(int product_id)
*   
*   Lists de order which a product ocures most
*   
*   Input: int product_id -> product's id
*
*   Prints: Error or "Maximo produto <product_id> <order_id> <max>." or nothing
*/
void m(int product_id){
    int max = 0, last_o_id = 0, i ,j;

    /*product exists?*/
    if (product_id >= next_p_id){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", product_id);

    }else{
        for(i = 0; i < next_o_id; i++){ /*goes through order list*/
            for(j = 0; j < order_list[i].next_index; j++){ /*goes trough order*/
                /*if the order contains the product in a larger amount*/
                if (order_list[i].products[0][j] == product_id && order_list[i].products[1][j] > max){
                    max = order_list[i].products[1][j]; /*new max is saved*/
                    last_o_id = i; /*new order_id is saver*/
                    break;

                }
            }
        }

        /*if the product exists in an order*/
        if (max != 0){
            printf("Maximo produto %d %d %d.\n", product_id, last_o_id, max);

        } 
    }
}


/*
* void l()
*   
*   List all the products in stock sorted by price low to high
*
*   Prints: "Produtos
*            * <description> <price> <stock>
*            ..."
*   
*   Observations: quicsort_warehouse is called; print_wearehouse is altered
*/
void l(){
    int product_id, i;

    /* print_warehouse is populated with de ids, if the previous sort was used quicksort would be
    less eficient*/
    for(i=0; i< next_p_id; i++){
        print_warehouse[i] = i;

    }

    /*sorts the ids in the print_warehouse without altering the warehouse */
    quicksort_warehouse(0, next_p_id - 1);

    printf("Produtos\n");

    for(i = 0; i < next_p_id; i++){
        product_id = print_warehouse[i]; /*fetches the product ids in priting order*/

        /* print * <description> <price> <stock> */
        printf("* %s %d %d\n", warehouse[product_id].description, warehouse[product_id].price, 
        warehouse[product_id].stock);
      
    }

}


/*
* void L(int order_id)
*   
*   List all the products in stock sorted by price low to high
*
*   Prints: "Encomenda <order_id>
*            * <description> <price> <amount>
*            ..."
*   
*   Observations: quicsort_order is called; order_list is altered
*/
void L(int order_id){
    int N_products = order_list[order_id].next_index - 1 , product_id, i;
    
    /*order exists?*/
    if(order_id >= next_o_id){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order_id);

    }else{

        /*sorts products in the order and their respective amounts by price */
        quicksort_order(0, N_products, order_id); 

        printf("Encomenda %d\n", order_id);

        /* goes trought the order and prints the products info in order*/
        for(i = 0; i <= N_products; i++){
            product_id = order_list[order_id].products[0][i];

            /* print * <description> <price> <amount> */
            printf("* %s %d %d\n",warehouse[product_id].description, warehouse[product_id].price, 
            order_list[order_id].products[1][i]);

        }
    }
}


/*
* void parser()
*   
*   Primary function, reads inputs, selects and calls adquate functions
*   
*   Observations: operates recurservelly until x is feed as input by user
*/
void parser(){
    int opt, i, c, in1, in2, in3;
    char description[MAX_DESCRIPTION+1];

    opt = getchar();

    switch (opt){
        case 'a':
            getchar();
            /* reads description -> description*/
            for (i = 0; (c = getchar()) != ':' && i <= MAX_DESCRIPTION; i++){
                description[i] = c;

            }
            description[i] = '\0';

            /*read price -> in1 | weight -> in2 | amount*/
            scanf("%d:%d:%d", &in1, &in2, &in3);

            a(description, in1, in2, in3);

            break;
        
        case 'q':
            /*read product id -> in1 | amount -> in2 */
            scanf(" %d:%d", &in1, &in2);

            q(in1, in2);

            break;

        case 'N':

            N();

            break;

        case 'A':
            /*read order id -> in1 | product id -> in2 | amount -> in3*/
            scanf(" %d:%d:%d", &in1, &in2, &in3);

            A(in1, in2, in3);

            break;

        case 'r':
            /*read product id -> in1 | amount -> in2 */
            scanf(" %d:%d", &in1, &in2);

            r(in1, in2);

            break;

        case 'R':
            /*read order id -> in1 | product id -> in2 */
            scanf(" %d:%d", &in1, &in2);

            R(in1, in2);

            break;

        case 'C':
            /*read order id -> in1*/
            scanf(" %d", &in1);

            C(in1);

            break;
            
        case 'p':
            /*read product id -> in1 | price -> in2 */
            scanf(" %d:%d", &in1, &in2);

            p(in1, in2);

            break;            
        
        case 'E':
            /*read order id -> in1 | product id -> in2 */
            scanf(" %d:%d", &in1, &in2);

            E(in1, in2);

            break;

        case 'm':
            /*read product id -> in1*/
            scanf(" %d", &in1);

            m(in1);

        break;

        case 'l':
            l();

            break;

        case 'L':
            /*read order id -> in1*/
            scanf(" %d", &in1);

            L(in1);

            break;

        case 'x':
            return;

            break;

    }

    getchar(); /*disregards the new line (\n)*/
    parser(); /*recursive call*/

}


int main(){
    /*initial declarations*/
    next_p_id = 0;
    next_o_id = 0;

    /*calls parser initiating recursive calling*/
    parser();

    return 0;
}