#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>


#define EMPTY_STRING ""
#define NULL_QUANTITY 0
#define MAX_INT 32768 /*Max int with 16 bits to sets a range for counting sort*/
#define DESC_SIZE 63 /*Max characters a product's description can have*/
#define MAX_PRODS_WH 9999 /*Max amount of products in the warehouse*/
#define MAX_PRODS_ORDER 9999 /*Max number of products in an order*/
#define MAX_WEIGHT_ORDER 200 /*Max weight of an order*/
#define MAX_ORDERS 999 /*Max number of order*/

/* Struct product
 * 
 * Struct that defines a product with the following
 * parameters: identification number(id), description of
 * the product as a string, price, weight and quantity
 * avalaible(amount).
 */
typedef struct{
    int id; 
    char description[DESC_SIZE+1];
    int price;
    int weight;
    int amount;
} product;

/* Struct product
 * 
 * Struct that defines an order. Able to hold a given
 * amount of products(items parameter), with a parameter
 * for the total weight, a state set to 1 if available and
 * to 0 otherwise and a counter for the amount of unique
 * items within(n_products)
 */
typedef struct{
    product items[MAX_PRODS_ORDER];
    int weight;
    int state;
    int n_products;
} order;

/*funtion prototypes*/

void function_a();
void function_q();
void function_N();
void function_A();
void function_r();
void function_R();
void function_C();
void function_p();
void function_E();
void function_m();
void function_l();
void function_L();
void countingsort(int left, int right);
void mergesort(int o_id, int left, int right);
void merge(int o_id, int left, int m, int right);

 /*Array storing the systems products*/
product warehouse[MAX_PRODS_WH];
 /*Array storing the order*/
order shipping[MAX_ORDERS];
 /* Counter for the amount of products in the warehouse array*/
int warehouse_size;
 /*auxiliary array to store the ordered array from countingsort*/
product aux_wh[MAX_PRODS_WH];
 /*auxiliary order used in mergesort*/
order aux_order;

/*Parses the commands from stdin and calls the function to exectue the command*/
int main(){
    char command;/*Variable that holds the command's character*/
    
    while (command!='x') {
        command = getchar(); /*Reads the command to execute*/
        switch(command){
            case 'a':
                function_a();
                break;
            
            case 'q':
                function_q();
                break;

            case 'N':
                function_N();
                break;

            case 'A':
                function_A();
                break;

            case 'r':
                function_r();
                break;

            case 'R':
                function_R();
                break;

            case 'C':
                function_C();
                break;

            case 'p':
                function_p();
                break;

            case 'E':
                function_E();
                break;

            case 'm':
                function_m();
                break;

            case 'l':
                function_l();
                break;

            case 'L':
                function_L();
                break;
        }
        getchar(); /*Reads '\n' character at the end of the command*/
    }
    return 0;
}

/* Function: function_a ()->()
 * 
 * Reads from stdin in the format (description:price:weight:amount) and
 * attributes the values to a new product in the warehouse along with the
 * product id.
 */
void function_a(){
    int new_product_id, str_read, c;

    new_product_id = warehouse_size;

    warehouse[new_product_id].id = new_product_id; /*Attribute the identification number to the product*/
    c=getchar(); /*Remove space(' ') character from command line*/
    c=getchar();
    for (str_read=0; str_read<DESC_SIZE && c!=':'; str_read++){
        warehouse[new_product_id].description[str_read] = c;
        c=getchar();
    }
    warehouse[new_product_id].description[str_read] = '\0';
    scanf("%d:%d:%d",  &warehouse[new_product_id].price, &warehouse[new_product_id].weight, &warehouse[new_product_id].amount);
    
    /*Increase the counter of products in the the warehouse*/
    warehouse_size++;
    
    printf("Novo produto %d.\n", warehouse[new_product_id].id);
}

/* Function: function_q ()->()
 * 
 * Reads from stdin in the format (product_id:amount) and adds to the product
 * with product_id the amount read.
 */
void function_q(){
    int p_id, add_amount;

    scanf("%d:%d", &p_id, &add_amount);

    if (strcmp(warehouse[p_id].description, EMPTY_STRING) == 0){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p_id);
        return;
    }

    warehouse[p_id].amount += add_amount;
}    

/* Function: function_N ()->()
 * 
 * Creates a new order.
 */
void function_N(){
    int o_id;
    
    /*Find not active order in shipping array*/
    for (o_id=0; o_id<MAX_ORDERS && shipping[o_id].state==1; o_id++){;}

    /*Changes order's state to 1(active)*/
    shipping[o_id].state=1;

    printf("Nova encomenda %d.\n", o_id);
}

/* Function: function_A ()->()
 * 
 * Reads from stdin in the format (order_id:product_id:N) and moves N amount of
 * product with product_id to the order with order_id.
 */
void function_A(){
    int o_id, p_id, qtt, check, search_order;

    scanf("%d:%d:%d", &o_id, &p_id, &qtt);

    if (shipping[o_id].state==0){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p_id, o_id);
        return;
    } 
    else if (strcmp(warehouse[p_id].description, EMPTY_STRING) == 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", p_id, o_id);
        return;
    }
    else if (warehouse[p_id].amount<qtt){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p_id, o_id);
        return;
    } 
    else if (shipping[o_id].weight + warehouse[p_id].weight * qtt > MAX_WEIGHT_ORDER){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", p_id , o_id);
        return;
    } 

    /*Finds product in an order*/
    check = 0;
    for (search_order=0; search_order<shipping[o_id].n_products; search_order++){
        if (shipping[o_id].items[search_order].id == p_id){
            check=1;
            break;
        }
    }
    
    /*Moves the given amount to the order*/
    if (check==0){ /*If product not in order -> add it*/
        search_order = shipping[o_id].n_products;
        shipping[o_id].items[search_order] = warehouse[p_id];
        shipping[o_id].n_products++;
        shipping[o_id].items[search_order].amount = qtt;
        warehouse[p_id].amount -= qtt;
        shipping[o_id].weight += qtt * shipping[o_id].items[search_order].weight;
    } else if (check==1){ /*If product in order -> add the amount*/
        warehouse[p_id].amount -= qtt;
        shipping[o_id].items[search_order].amount += qtt;
        shipping[o_id].weight += qtt * shipping[o_id].items[search_order].weight;
    }
}

/* Function: function_r ()->()
 * 
 * Reads from stdin in the format (product_id:N) and removes N amount of
 * product with the product_id from the warehouse.
 */
void function_r(){
    int p_id, qtd;
    
    scanf("%d:%d", &p_id, &qtd);

    if (strcmp(warehouse[p_id].description, EMPTY_STRING) == 0){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p_id);
        return;
    } else if (warehouse[p_id].amount < qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, p_id);
        return;
    }
    
    warehouse[p_id].amount -= qtd;
}

/* Function: function_R ()->()
 * 
 * Reads from stdin in the format (order_id:product_id) and removes the product
 * with product_id from the order with order_id.
 */
void function_R(){
    int o_id, p_id, search_order, delete;

    scanf("%d:%d", &o_id, &p_id);

    if (shipping[o_id].state==0){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", p_id, o_id);
        return;
    }
    else if (strcmp(warehouse[p_id].description, EMPTY_STRING) == 0){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", p_id, o_id);
        return;
    }

    /*Finds product in order*/
    for (search_order=0; search_order<shipping[o_id].n_products; search_order++){
        if (shipping[o_id].items[search_order].id == p_id){
            /*Add back the amount of product in order to the warehouse*/
            warehouse[p_id].amount  += shipping[o_id].items[search_order].amount;
            /*Take weight from product moved*/
            shipping[o_id].weight -= shipping[o_id].items[search_order].amount * shipping[o_id].items[search_order].weight;
            /*Set every product from the point of the deleted to overwrite and delete*/
            for (delete=search_order; delete<shipping[o_id].n_products; delete++){
                shipping[o_id].items[delete] = shipping[o_id].items[delete+1]; 
            }
            /*Update counter of products in order o_id*/
            --shipping[o_id].n_products;

            break;
        }
    }
}

/* Function: function_C ()->()
 * 
 * Reads from stdin in the format (order) and calculates the total cost.
 */
void function_C(){
    int o_id, cicle, cost=0;

    scanf("%d", &o_id);

    if (shipping[o_id].state==0){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", o_id);
        return;
    }

    for (cicle=0; cicle<shipping[o_id].n_products; cicle++){
        cost += shipping[o_id].items[cicle].price * shipping[o_id].items[cicle].amount;
    }

    printf("Custo da encomenda %d %d.\n", o_id, cost);
}

/* Function: function_p ()->()
 * 
 * Reads from stdin in the format (product_id:price) and modifies the price of
 * the product with product_id to new_price.
 */
void function_p(){
    int p_id, new_price, search_order, search_items; 

    scanf("%d:%d", &p_id, &new_price);

    if (strcmp(warehouse[p_id].description, EMPTY_STRING) == 0){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", p_id);
        return;
    }

    warehouse[p_id].price = new_price;

    /*loop to run through all active orders*/
    for (search_order=0; search_order<MAX_ORDERS && shipping[search_order].state==1; search_order++){
        for (search_items=0; search_items<shipping[search_order].n_products; search_items++){
            if (shipping[search_order].items[search_items].id == p_id){
                shipping[search_order].items[search_items].price = new_price; /*new price attribution*/
            }
        }
    }
}

/* Function: function_E ()->()
 * 
 * Reads from stdin in the format (order_id:product_id) and lists the product's
 * description along with its amount in the order with order_id.
 */
void function_E(){
    int o_id, p_id, search_order;

    scanf("%d:%d", &o_id, &p_id);

    if (shipping[o_id].state == 0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
        return;
    }
    else if (strcmp(warehouse[p_id].description, EMPTY_STRING) == 0){
        printf("Impossivel listar produto %d. Produto inexistente.\n", p_id);
        return;
    }
    
    /*Finds product in the order and prints its amount*/
    for (search_order=0; search_order<warehouse_size; search_order++){
        if (shipping[o_id].items[search_order].id == p_id && shipping[o_id].items[search_order].amount != 0){
            printf("%s %d.\n", shipping[o_id].items[search_order].description, shipping[o_id].items[search_order].amount); 
            return;     
        }
    }
    /*In case product was not found print with 0 quantity*/
    printf("%s %d.\n", warehouse[p_id].description, NULL_QUANTITY);
}

/* Function: function_m ()->()
 * 
 * Reads from stdin in the format (product_id) and lists the product id, the id
 * of the order on which it appears in the most quantity along with the max
 * quantity.
 */
void function_m(){
    int p_id, search_order, search_items, order_max=0, qtt_max=0;

    scanf("%d", &p_id);

    if (strcmp(warehouse[p_id].description, EMPTY_STRING) == 0){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p_id);
        return;
    }

    /*Finds product in all orders and stores order in which it has the most amount as well as the amount*/
    for (search_order=0; search_order<MAX_ORDERS && shipping[search_order].state==1; search_order++){
        for (search_items=0; search_items<shipping[search_order].n_products; search_items++){
            if (shipping[search_order].items[search_items].id==p_id && shipping[search_order].items[search_items].amount > qtt_max){
                order_max = search_order;
                qtt_max = shipping[search_order].items[search_items].amount;
            }
        } 
    }

    if (qtt_max!=0){
        printf("Maximo produto %d %d %d.\n", p_id, order_max, qtt_max);
    }
}

/* Function: function_l ()->()
 * 
 * Lists the warehouse's products from lowest to highest price.
 */
void function_l(){
    int print;
    /*Call for the sorting function*/
    countingsort(0, warehouse_size);
    /*Prints all the elements after sorting*/
    puts("Produtos");
    for (print=0; print<warehouse_size ; print++){ /*Print all the elements after sorting*/
        printf("* %s %d %d\n", aux_wh[print].description, aux_wh[print].price, aux_wh[print].amount);
    }
}

/* Function: function_m ()->()
 * 
 * Reads from stdin in the format (order_id) and lists the products alphabetically
 * from a to z from the order with order_id.
 */
void function_L(){
    int o_id, print;

    scanf("%d", &o_id);

    if (shipping[o_id].state==0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
        return;
    }
    /*Call for the sorting function*/
    mergesort(o_id , 0, shipping[o_id].n_products-1);
    /*Prints all the elements from the auxiliary sorted array*/
    printf("Encomenda %d\n", o_id);
    for (print=0; print<shipping[o_id].n_products; print++){
        printf("* %s %d %d\n", shipping[o_id].items[print].description, shipping[o_id].items[print].price, shipping[o_id].items[print].amount);
    }
}

/* Function: counting_sort (left, right)->()
 *
 * left: left limiting index from array
 * right: right limiting index from array
 *
 * Sorts the array's (warehouse) products by ascending price from index left
 * to the index right calling for the counting method into the auxiliary array
 * of products aux_wh.
 */
void countingsort(int left, int right){
    int index;
    int counter_array[MAX_INT+1]={0}; /*array with the size of the max number of an int (16 bit int)*/

    /*Stores in the counting array the amount of times each price appears*/
    for (index = 0; index<right; index++){
        ++counter_array[warehouse[index].price];
    }

    counter_array[0] = left; /*Adds to the first index the left limit for the next conversion*/

    /*Adds all values to previous index's value to turn them into index to the final array*/
    for (index=1; index<=MAX_INT; index++){
        counter_array[index] += counter_array[index-1];
    }

    /*Fits the product into the auxiliary warehouse array in the correct position*/
    for (index=right-1; index>=0; index--){ /*Run the arrays backwards to make algorythm stable*/
        aux_wh[counter_array[warehouse[index].price]-1] = warehouse[index];
        --counter_array[warehouse[index].price];
    }
}

/* Function: mergesort_alpha (o_id, left, right)->()
 * 
 * o_id: id from the order to sort
 * left: left limiting index from array
 * right: right limiting index from array
 * 
 * Sorts the array's (warehouse) products in alphabetical order [a-z] from
 * index left to the index right calling for the mergesort method.
 */
void mergesort(int o_id, int left, int right) {
    int m = (right+left)/2;
    if (right <= left)
        return;

    mergesort(o_id, left, m);
    mergesort(o_id, m+1, right);
    merge(o_id, left, m, right);
}

/* Function: mergesort (left, right)->()
 * 
 * Description: Auxiliary funtion for the function mergesort
 */
void merge(int o_id, int left, int m, int right){
    int i, j, k;
    
    /*Fills in the auxiliary array*/
    for (i = m+1; i > left; i--)
        aux_order.items[i-1] = shipping[o_id].items[i-1];
    for (j = m; j < right && strcmp(aux_order.items[j].description, EMPTY_STRING) != 0; j++)
        aux_order.items[right+m-j] = shipping[o_id].items[j+1];
    /*Choses from the auxiliary array the elements to order them into the order array*/
    for (k = left; k <= right; k++)
        if (strcmp(aux_order.items[j].description, aux_order.items[i].description) < 0 || i > m)
            shipping[o_id].items[k] = aux_order.items[j--];
        else
            shipping[o_id].items[k] = aux_order.items[i++];
}