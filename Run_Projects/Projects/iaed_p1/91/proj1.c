#include <stdio.h>
#include <string.h>


/* Max size of product description */
#define PROD_DESC_DIM 63


/* Max amount of products */
#define PROD_AMOUNT 10000


/* Max amount of orders */
#define ORDERS_AMOUNT 500


/* Max amount of products in an order (since weight has to be < 200) */
#define PROD_AMOUNT_IN_ORDER 200


/* Max order weight */
#define MAX_WEIGHT 200


/* Controllers for MergeSort  */
#define DESCRIPTION 0
#define PRICE 1


/******************************************************************************/
/*********************** STRUCTS & GLOBAL VARIABLES ***************************/
/******************************************************************************/


/* Product definition */
typedef struct {

    int identifier;
    char description[PROD_DESC_DIM];
    int price;
    int weight;
    int quantity;

} product;


/* Orders definition */
typedef struct {

    /* Contains all products added to order */
    product ordered_products[PROD_AMOUNT_IN_ORDER];

    int size;  /* Amount of products added to order */
    int weight;

} order;


/* Array containing all created products */
product stock[PROD_AMOUNT];


/* Array containing all created orders */
order requested_orders[ORDERS_AMOUNT];


/* Controls the identification of products globally
 * (amount of products added in the system) */
int product_identification = 0;


/* Controls the identification of orders globally
 * (amount of orders added in the system) */
int order_identification = 0;


/******************************************************************************/
/**************************** AUXILIARY FUNCTIONS *****************************/
/******************************************************************************/


/* Verifies if product has been created */
int product_exits(int prd_id) {
    return (prd_id < product_identification) ? 1 : 0;
}


/* Verifies if order has been created */
int order_exits(int ord_id) {
    return (ord_id < order_identification) ? 1 : 0;
}


/* Verifies if product is in input order */
int prod_is_inside_order(int prd_id, int ord_id) {

    /* Gets the number of different products inside order */
    int amount_of_orders = requested_orders[ord_id].size;

    int i;

    /* Cycles through all products inside order trying to find the
     * one corresponding to input */
    for (i = 0; i < amount_of_orders; i++) {

        if (requested_orders[ord_id].ordered_products[i].identifier == prd_id) {
            return 1;
        }

    }

    return 0;

}


/******************************************************************************/
/*************************** SORTING FUNCTIONS ********************************/
/******************************************************************************/


/* Auxiliary array for MergeSort */
product aux[PROD_AMOUNT];


/* Merges two sub-arrays either by comparing prices or descriptions */
void merge(product *array_to_sort, int left, int middle, int right,
           int method){

    int i, j, k;

    /* Copies data to auxiliary array */
    for (i = middle + 1; i > left; i--) {
        aux[i-1] = array_to_sort[i - 1];
    }
    for (j = middle; j < right; j++) {
        aux[right + middle - j] = array_to_sort[j + 1];
    }

    /* Controls what is it being sorted by (price or description) */
    if (method == PRICE) {

        /* Sorting by price */
        for (k = left; k <= right; k++) {

            /* Decides which element should come first */
            if ((aux[j].price < aux[i].price) ||
                (aux[j].price == aux[i].price &&
                 aux[j].identifier < aux[i].identifier)) {

                array_to_sort[k] = aux[j--];

            } else {

                array_to_sort[k] = aux[i++];
            }

        }


    } else if (method == DESCRIPTION) {

        /* Sorting by description */
        for (k = left; k <= right; k++) {

            /* Decides which element should come first */
            if (strcmp(aux[j].description, aux[i].description) < 0 ||
                (strcmp(aux[j].description, aux[i].description) == 0 &&
                 aux[j].identifier < aux[i].identifier)) {

                array_to_sort[k] = aux[j--];

            } else {

                array_to_sort[k] = aux[i++];

            }

        }

    }

}


/* Sorts array based on MergeSort's method */
void mergesort(product *array_to_sort, int left, int right, int method) {

    /* Gets middle position */
    int m = (right + left) / 2;

    /* Checks if it has finished sorting */
    if (right <= left)
        return;

    /* Recursive calls itself, dividing array */
    mergesort(array_to_sort, left, m, method);
    mergesort(array_to_sort, m + 1, right, method);
    merge(array_to_sort, left, m, right, method);

}


/******************************************************************************/
/***************************** COMMAND FUNCTIONS ******************************/
/******************************************************************************/


/* Command: 'a' */
/* Creates a new product */
void creates_product() {

    /* User description input */
    char char_input;

    product new_prod;

    int i = 0;

    /* Removes first whitespace */
    char_input = getchar();

    /* Gets description */
    while (i < PROD_DESC_DIM - 1 && (char_input = getchar()) != ':') {
        new_prod.description[i++] = char_input;
    }
    new_prod.description[i] = '\0';

    /* Gets price, weight and quantity from user */
    scanf("%d:%d:%d", &new_prod.price,
          &new_prod.weight, &new_prod.quantity);

    /* Although product's id is equal to it's position in stock, this variable,
     * is used for reference inside orders */
    new_prod.identifier = product_identification;

    /* Adds product to stock (arrays of products) */
    stock[product_identification] = new_prod;

    printf("Novo produto %d.\n", product_identification);

    /* Updates product id (so that, when a new product is created,
     * it will have a new id) */
    product_identification++;

}


/* Command: 'q' */
/* Increases product's quantity in stock */
void adds_stock() {

    /* User input */
    int prd_id, quantity;

    scanf(" %d:%d", &prd_id, &quantity);

    /* Verifies if input is valid */
    if (!product_exits(prd_id)) {
        printf("Impossivel adicionar produto %d ao stock. "
               "Produto inexistente.\n", prd_id);

    } else {

        stock[prd_id].quantity += quantity;

    }

}


/* Command: 'N' */
/* Creates a new order */
void creates_order() {

    order new_order;

    new_order.weight = 0;
    new_order.size = 0;

    /* Adds order to requested order's array */
    requested_orders[order_identification] = new_order;

    printf("Nova encomenda %d.\n", order_identification);

    /* Updates order id (so that, when a new order is created,
     * it will have a new id) */
    order_identification++;

}


/* Command: 'A' */
/* Adds product to order */
void adds_prod_to_order() {

    /* User input */
    int ord_id, prd_id, quantity;

    /* Gets the number of different products inside order */
    int amount_of_products;

    /* First available (empty) index of list of products inside order */
    int index;

    int i;

    scanf(" %d:%d:%d", &ord_id, &prd_id, &quantity);

    /* Verifies if input is valid */
    if (!order_exits(ord_id)) {
        printf("Impossivel adicionar produto %d a encomenda %d. "
               "Encomenda inexistente.\n", prd_id, ord_id);
    } else if (!product_exits(prd_id)) {
        printf("Impossivel adicionar produto %d a encomenda %d."
               " Produto inexistente.\n", prd_id, ord_id);
    } else if (quantity > stock[prd_id].quantity) {
        printf("Impossivel adicionar produto %d a encomenda %d. "
               "Quantidade em stock insuficiente.\n", prd_id, ord_id);
    } else if ((requested_orders[ord_id].weight +
                quantity * stock[prd_id].weight) > MAX_WEIGHT) {
        printf("Impossivel adicionar produto %d a encomenda %d. "
               "Peso da encomenda excede o maximo de 200.\n", prd_id, ord_id);

    } else {

        /* If it's not in the order, it's added.
         * Else, it's quantity is increased */
        if (!prod_is_inside_order(prd_id, ord_id)) {

            index = requested_orders[ord_id].size;

            /* Copies product into order's last index */
            requested_orders[ord_id].ordered_products[index] = stock[prd_id];

            /* Updates quantity */
            requested_orders[ord_id].
                    ordered_products[index].quantity = quantity;

            requested_orders[ord_id].size++;

        } else {

            amount_of_products = requested_orders[ord_id].size;

            /* Increases quantity of product inside order */
            for (i = 0; i < amount_of_products; i++) {

                if (requested_orders[ord_id].
                        ordered_products[i].identifier == prd_id) {

                    requested_orders[ord_id].
                            ordered_products[i].quantity += quantity;

                    break;
                }

            }

        }

        /* Removes from stock the same quantity that was put in the order */
        stock[prd_id].quantity -= quantity;

        /* Updates order's weight */
        requested_orders[ord_id].weight += stock[prd_id].weight * quantity;

    }

}


/* Command: 'r' */
/* Removes a certain amount of a product in stock */
void removes_quantity_from_stock() {

    /* User input */
    int prd_id, quantity;

    scanf(" %d:%d", &prd_id, &quantity);

    /* Verifies if input is valid */
    if (!product_exits(prd_id)) {
        printf("Impossivel remover stock do produto %d. "
               "Produto inexistente.\n", prd_id);
    } else if (stock[prd_id].quantity - quantity < 0) {
        printf("Impossivel remover %d unidades do produto %d do stock. "
               "Quantidade insuficiente.\n", quantity, prd_id);

    } else {

        stock[prd_id].quantity -= quantity;

    }

}


/* Command: 'R' */
/* Removes product from order */
void removes_product_from_order() {

    /* User input */
    int ord_id, prd_id;

    /* Gets the number of different products inside order */
    int amount_of_products;

    /* Holds product during iterations */
    product prod;

    int i;

    scanf(" %d:%d", &ord_id, &prd_id);

    /* Verifies if input is valid */
    if (!order_exits(ord_id)) {
        printf("Impossivel remover produto %d a encomenda %d. "
               "Encomenda inexistente.\n", prd_id, ord_id);
    } else if (!product_exits(prd_id)) {
        printf("Impossivel remover produto %d a encomenda %d. "
               "Produto inexistente.\n", prd_id, ord_id);

    } else {

        amount_of_products = requested_orders[ord_id].size;

        /* Cycles through all products until it finds the correct one */
        for (i = 0; i < amount_of_products; i++) {

            prod = requested_orders[ord_id].ordered_products[i];

            if (prod.identifier == prd_id) {

                /* Updates quantity in stock */
                stock[prd_id].quantity += prod.quantity;

                /* Updates order's weight */
                requested_orders[ord_id].weight -= prod.quantity *
                                                   stock[prd_id].weight;

                /* Resets quantity inside order */
                requested_orders[ord_id].ordered_products[i].quantity = 0;

                break;
            }

        }

    }

}


/* Command: 'C' */
/* Returns order's price */
void orders_price() {

    /* User input */
    int ord_id;

    /* Saves accumulated price */
    int total_price = 0;

    /* Gets the number of different products inside order */
    int amount_of_products;

    /* Holds product during iterations */
    product prod;

    int i;

    scanf(" %d", &ord_id);

    amount_of_products = requested_orders[ord_id].size;

    /* Verifies if input is valid */
    if (!order_exits(ord_id)) {
        printf("Impossivel calcular custo da encomenda %d. "
               "Encomenda inexistente.\n", ord_id);

    } else {

        /* Calculates order's price */
        for (i = 0; i < amount_of_products; i++) {

            prod = requested_orders[ord_id].ordered_products[i];

            total_price += stock[prod.identifier].price * prod.quantity;

        }

        printf("Custo da encomenda %d %d.\n", ord_id, total_price);

    }

}


/* Command: 'p' */
/* Changes product's price */
void changes_prod_price() {

    /* User input */
    int prd_id, new_price;

    scanf(" %d:%d", &prd_id, &new_price);

    /* Verifies if input is valid */
    if (!product_exits(prd_id)) {
        printf("Impossivel alterar preco do produto %d. "
               "Produto inexistente.\n", prd_id);

    } else {

        stock[prd_id].price = new_price;

    }

}


/* Command: 'E' */
/* Returns product description and quantity in an order */
void product_desc_and_qt_inside_order() {

    /* User input */
    int ord_id, prd_id;

    /* Gets the number of different products inside order */
    int amount_of_products;

    /* Holds product during iterations */
    product prod;

    int i;

    scanf(" %d:%d", &ord_id, &prd_id);

    amount_of_products = requested_orders[ord_id].size;

    /* Verifies if input is valid */
    if (!order_exits(ord_id)) {
        printf("Impossivel listar encomenda %d. "
               "Encomenda inexistente.\n", ord_id);
    } else if (!product_exits(prd_id)) {
        printf("Impossivel listar produto %d. "
               "Produto inexistente.\n", prd_id);

    } else {

        /* Prints description and quantity of product
         * if it is inside the order */
        for (i = 0; i < amount_of_products; i++) {

            prod = requested_orders[ord_id].ordered_products[i];

            if (prod.identifier == prd_id) {

                printf("%s %d.\n",stock[prd_id].description,
                       prod.quantity);

                return ;
            }

        }

        /* Prints description and quantity of product if it is not inside the
         * order */
        printf("%s %d.\n", stock[prd_id].description, 0);

    }

}


/* Command: 'm' */
/* Returns the id of the order in which said product occurs the most */
void most_occurring_prod_in_order() {

    /* User input */
    int prd_id;

    /* Saves order's id and product's quantity, respectively */
    int max[2] = {-1, -1};

    /* Used for comparision at the end. Used as a control group (same as max) */
    int control[2] = {-1, -1};

    /* Saves amount of products in each order during iterations */
    int total_amount;

    /* Holds product during iterations */
    product prod;

    int ord_id, i;

    scanf(" %d", &prd_id);

    /* Verifies if input is valid */
    if (!product_exits(prd_id)) {
        printf("Impossivel listar maximo do produto %d. "
               "Produto inexistente.\n", prd_id);

    } else {

        /* Cycles trough all orders */
        for (ord_id = 0; ord_id < order_identification; ord_id++) {

            total_amount = requested_orders[ord_id].size;

            /* Cycles trough all products in an order */
            for (i = 0; i < total_amount; i++) {

                prod = requested_orders[ord_id].ordered_products[i];

                /* If id is found and has a higher quantity,
                 * updates max's status */
                if (prod.identifier == prd_id && prod.quantity > max[1]) {

                    max[0] = ord_id;
                    max[1] = prod.quantity;

                }

            }

        }

        /* If a product was found and his quantity is different than zero,
         * print message */
        if (memcmp(max, control, 2) != 0 && max[1] != 0) {
            printf("Maximo produto %d %d %d.\n", prd_id, max[0], max[1]);
        }

    }

}


/* Command: 'l' */
/* Lists all products in stock by price */
void lists_products_by_price() {

    /* Created a different array so that I don't mess stock's indexation */
    product array_to_sort[PROD_AMOUNT] ={ 0 };

    int i;

    /* Copies content from stock */
    memcpy(array_to_sort, stock, sizeof(stock));

    /* Sorts array */
    mergesort(array_to_sort,
              0, product_identification - 1, PRICE);

    /* Prints result */
    printf("Produtos\n");
    for (i = 0; i < product_identification; i++) {
        printf("* %s %d %d\n", array_to_sort[i].description,
               array_to_sort[i].price, array_to_sort[i].quantity);
    }

}


/* Command: 'L' */
/* Lists all products, in an order, by it's description */
void list_products_in_order_by_desc() {

    /* User input */
    int ord_id;

    /* Gets the number of different products inside order */
    int amount_of_products;

    /* Used to link products inside the order with the ones from stock */
    int prod_id;

    /* Created a different array so that I don't mess order's indexation */
    product array_to_sort[PROD_AMOUNT_IN_ORDER];

    int i;

    scanf(" %d", &ord_id);

    /* Verifies if input if valid */
    if (!order_exits(ord_id)) {
        printf("Impossivel listar encomenda %d. "
               "Encomenda inexistente.\n", ord_id);

    } else {

        /* Copies content from order */
        memcpy(array_to_sort, requested_orders[ord_id].ordered_products,
               sizeof(requested_orders[ord_id].ordered_products));

        amount_of_products = requested_orders[ord_id].size;

        /* Sorts order */
        mergesort(array_to_sort, 0,amount_of_products - 1, DESCRIPTION);

        /* Prints result */
        printf("Encomenda %d\n", ord_id);
        for (i = 0; i < amount_of_products; i++) {

            prod_id = array_to_sort[i].identifier;

            /* Filters products that were removed from order */
            if (array_to_sort[i].quantity != 0) {
                printf("* %s %d %d\n", stock[prod_id].description,
                       stock[prod_id].price, array_to_sort[i].quantity);
            }

        }

    }

}


/******************************************************************************/
/******************************* MAIN FUNCTION ********************************/
/******************************************************************************/


int main() {

    /* User's input command */
    int command;

    /* Controls which command is going to be executed */
    while ((command = getchar()) != 'x') {

        switch (command) {

            case 'a':
                creates_product();
                break;

            case 'q':
                adds_stock();
                break;

            case 'N':
                creates_order();
                break;

            case 'A':
                adds_prod_to_order();
                break;

            case 'r':
                removes_quantity_from_stock();
                break;

            case 'R':
                removes_product_from_order();
                break;

            case 'C':
                orders_price();
                break;

            case 'p':
                changes_prod_price();
                break;

            case 'E':;
                product_desc_and_qt_inside_order();
                break;

            case 'm':
                most_occurring_prod_in_order();
                break;

            case 'l':
                lists_products_by_price();
                break;

            case 'L':
                list_products_in_order_by_desc();
                break;

            default:
                continue;

        }

    }

    return 0;
}
