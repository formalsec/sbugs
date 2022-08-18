#include <stdio.h>
#include <string.h>

/* Constants declaration */

#define MAX_PROD_NAME 63
#define MAX_NUMBER_PROD 10000
#define MAX_NUMBER_ORDERS 500
#define MAX_PER_ORDER 200

/* Structures declaration */

typedef struct 
{
    char name[MAX_PROD_NAME]; /* Array to store the products name */
    int price, weight, amount, identifier;

}Product;

typedef struct 
{
    int identifier, weight, number_diff_products;
    Product shoplist[MAX_PER_ORDER]; /* Array to store the different products added to an order */

}Order;

/* Function prototypes */

/* Functions for each specified command */
void command_a(char name[MAX_PROD_NAME], int price, int weight, int amount, int number_diff_products);

void command_q(int indentifier_product, int amount, int number_diff_products);

void command_N(int number_orders);

void command_A(int identifier_order, int identifier_product, int amount, int number_orders, int number_products);

void command_r(int identifier_product, int amount, int number_diff_products);

void command_R(int identifier_order, int identifier_product, int number_orders, int number_diff_products);

void command_C(int identifier_order, int number_orders);

void command_p(int identifier_product, int price, int number_orders, int number_diff_products);

void command_E(int identifier_order, int identifier_product, int number_orders, int number_diff_products);

void command_m(int identifier_product, int number_orders, int number_diff_products);

void command_l(int number_diff_products);

void command_L(int identifier_order, int number_orders);

void command_k(int number_diff_products);

void command_K(int identifier_order);

/* Auxiliary functions for sorting the store products array */
void quicksort_products(int array[MAX_NUMBER_PROD], int inf, int sup);

int partition_products(int array[MAX_NUMBER_PROD], int inf, int sup);

int less_products(int a, int b);

void exchange_products(int array[MAX_NUMBER_PROD], int a, int b);

/* Auxiliary functions for sorting the order products array */
void quicksort_orders(int array[MAX_NUMBER_ORDERS], int inf, int sup, int identifier_order);

int partition_orders(int array[MAX_NUMBER_ORDERS], int inf, int sup, int identifier_order);

int less_orders(int a, int b, int identifier_order);

void exchange_orders(int array[MAX_NUMBER_PROD], int a, int b);


/* Code */

Order orders_list[MAX_NUMBER_ORDERS]; /* A global array to store all the specified orders and their properties */
Product store_stock[MAX_NUMBER_PROD]; /* A global array to store all the specified products and their properties */

int main() 
{
    /* Variables to store the different kinds of input given */
    char command_type, name[MAX_PROD_NAME];
    int price, weight, amount, identifier_product, identifier_order;

    /* Variables to control the total numbers of products/orders in the system, for better control of loops */
    int number_diff_products=0, number_orders=0;

    scanf("%c", &command_type); /* Reads the desired command */

    while (command_type != 'x') /* While the program hasnt been told to close */
    {
        /* Chooses from the given command the right input format and the function supposed to be called */
        switch (command_type)
        {
        case 'a':   
            scanf(" %[^:]:%d:%d:%d", name, &price, &weight, &amount);
            command_a(name, price, weight, amount, number_diff_products);
            number_diff_products++;
            break;
        
        case 'q':
            scanf("%d:%d", &identifier_product, &amount);
            command_q(identifier_product, amount, number_diff_products);
            break;

        case 'N':
            command_N(number_orders);
            number_orders++;
            break;

        case 'A':
            scanf("%d:%d:%d", &identifier_order, &identifier_product, &amount);
            command_A(identifier_order, identifier_product, amount, number_orders, number_diff_products);
            break;

        case 'r':
            scanf("%d:%d", &identifier_product, &amount); 
            command_r(identifier_product, amount, number_diff_products); 
            break;
        
        case 'R':
            scanf("%d:%d", &identifier_order, &identifier_product); 
            command_R(identifier_order, identifier_product, number_orders, number_diff_products); 
            break;

        case 'C':
            scanf("%d", &identifier_order); 
            command_C(identifier_order, number_orders); 
            break;

        case 'p':
            scanf("%d:%d", &identifier_product, &price); 
            command_p(identifier_product, price, number_orders, number_diff_products);
            break;

        case 'E':
            scanf("%d:%d", &identifier_order, &identifier_product); 
            command_E(identifier_order, identifier_product, number_orders, number_diff_products); 
            break;

        case 'm':
            scanf("%d", &identifier_product); 
            command_m(identifier_product, number_orders, number_diff_products); 
            break;

        case 'l':
            command_l(number_diff_products); 
            break;
        
        case 'L':
            scanf("%d", &identifier_order);
            command_L(identifier_order, number_orders); 
            break;

        /* Auxiliary functions */
        case 'k':
            command_k(number_diff_products);
            break;

        case 'K':
            scanf("%d", &identifier_order);
            command_K(identifier_order);
            break;

        default:
            break;
        }

        scanf("%c", &command_type); /* Reads the next command, in order to reinitialize the loop */
    }
    
    return 0;
}

void command_a(char name[MAX_PROD_NAME], int price, int weight, int amount, int number_diff_products)
{
    int i;

    /* Adds the product with the specified characteristics in the last position of the products array */
    store_stock[number_diff_products].price = price;
    store_stock[number_diff_products].amount = amount;
    store_stock[number_diff_products].weight = weight;
    store_stock[number_diff_products].identifier = number_diff_products;

    for(i = 0; name[i] != '\0'; i++)
    {
        store_stock[number_diff_products].name[i] = name[i];
    }
    store_stock[number_diff_products].name[i] = '\0';

    printf("Novo produto %d.\n", number_diff_products);
} 

void command_q(int indentifier_product, int amount, int number_diff_products)
{
    /* If the product is already added to the store stock, adds the desired amount to stock */
    if (indentifier_product < number_diff_products)
        store_stock[indentifier_product].amount += amount;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", indentifier_product);
}

void command_N(int number_orders)
{
    /* Creates a new order, and initializes its variables, needed for the control of loops and stats */
    orders_list[number_orders].identifier = number_orders;
    orders_list[number_orders].weight = 0;
    orders_list[number_orders].number_diff_products = 0;

    printf("Nova encomenda %d.\n", number_orders);
}

void command_A(int identifier_order, int identifier_product, int amount, int number_orders, int number_products)
{
    Product newProduct;

    if(!(identifier_order < number_orders)) /* Verify if the order does not exist */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", identifier_product, identifier_order);

    else if(!(identifier_product < number_products)) /* Verify if the product does not exist */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", identifier_product, identifier_order);
    
    else if(amount > store_stock[identifier_product].amount) /* Verify if there is enough of the product at stock */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", identifier_product, identifier_order);
    
    else if((orders_list[identifier_order].weight + amount * store_stock[identifier_product].weight) > MAX_PER_ORDER) /* Verify if the order would exceed the max weight */
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", identifier_product, identifier_order);
    
    else
    {
        int position = orders_list[identifier_order].number_diff_products, i;

        /* Verify if the product already exists in the order */

        for (i = 0; i < orders_list[identifier_order].number_diff_products; i++)
        {
            if (orders_list[identifier_order].shoplist[i].identifier == identifier_product) /* It does */
            {
                orders_list[identifier_order].shoplist[i].amount += amount;
                orders_list[identifier_order].weight += orders_list[identifier_order].shoplist[i].weight * amount;

                /* Subtracts that amount from the store stock */
                store_stock[identifier_product].amount -= amount;
                return;
            }
        }

        /* If it does not */
        /* Copies the product values to add them to a new item */

        newProduct.identifier = identifier_product;
        newProduct.amount = amount;
        newProduct.price = store_stock[identifier_product].price;
        newProduct.weight = store_stock[identifier_product].weight;
        strcpy(newProduct.name, store_stock[identifier_product].name);

        orders_list[identifier_order].shoplist[position] = newProduct;
        orders_list[identifier_order].weight += amount * store_stock[identifier_product].weight;
        orders_list[identifier_order].number_diff_products += 1; /* Updates the number of products */

        /* Subtracts that amount from the store stock */
        store_stock[identifier_product].amount -= amount;
    }
}

void command_r(int identifier_product, int amount, int number_diff_products)
{
    if(!(identifier_product < number_diff_products)) /* Verify if the product does not exist */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", identifier_product);
    
    else if (amount > store_stock[identifier_product].amount) /* Verify if there is enough of the product at stock */
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", amount, identifier_product);

    else
        store_stock[identifier_product].amount -= amount; /* Subtracts the desired amount of stock from that product */
}

void command_R(int identifier_order, int identifier_product, int number_orders, int number_diff_products)
{
    if(!(identifier_order < number_orders)) /* Verify if the order does not exist */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", identifier_product, identifier_order);

    else if(!(identifier_product < number_diff_products)) /* Verify if the product does not exist */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", identifier_product, identifier_order);

    else
    {
        int i, returnAmount;

        for(i = 0; i < orders_list[identifier_order].number_diff_products; i++) /* Cicle to find the right product */
        {
            if(orders_list[identifier_order].shoplist[i].identifier == identifier_product)
            {
                /* Removes the amount of that product in that order, and returns that amount to the store stock */
                returnAmount = orders_list[identifier_order].shoplist[i].amount;
                orders_list[identifier_order].shoplist[i].amount = 0;
                store_stock[identifier_product].amount += returnAmount;

                /* Subtrats the extra weight from this orders total */
                orders_list[identifier_order].weight -= returnAmount * orders_list[identifier_order].shoplist[i].weight;
                return;
            }
        }
    }
}

void command_C(int identifier_order, int number_orders)
{
    if(!(identifier_order < number_orders)) /* Verify if the order does not exist */
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", identifier_order);

    else
    {
        int i, cost=0;

        /* Calculates the cost of the specified order, by checking every product and adding its cost */
        for (i = 0; i < orders_list[identifier_order].number_diff_products; i++)
        {
            cost += (orders_list[identifier_order].shoplist[i].amount * orders_list[identifier_order].shoplist[i].price);
        }

        printf("Custo da encomenda %d %d.\n", identifier_order, cost);
    }
    
}

void command_p(int identifier_product, int price, int number_orders, int number_diff_products)
{
    if(!(identifier_product < number_diff_products)) /* Verify if the product does not exist */
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", identifier_product);

    else
    {
        int i, j;

        store_stock[identifier_product].price = price; /* Resets the desired products price */

        /* Cycle to reset this product price in every existing order that contains it */
        for(i = 0; i < number_orders; i++)
        {
            for(j = 0; j < orders_list[i].number_diff_products; j++)
            {
                /* Finding the desired product, resets its price and proceeds to the next order */
                if(orders_list[i].shoplist[j].identifier == identifier_product)
                {
                    orders_list[i].shoplist[j].price = price;
                    break;
                }   
            }
        }
    }
}

void command_E(int identifier_order, int identifier_product, int number_orders, int number_diff_products)
{
    if(!(identifier_order < number_orders)) /* Verify if the order does not exist */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", identifier_order);

    else if(!(identifier_product < number_diff_products)) /* Verify if the product does not exist */
        printf("Impossivel listar produto %d. Produto inexistente.\n", identifier_product);

    else
    {
        int i;

        /* Verify if the order contains that product */
        for(i = 0; i < orders_list[identifier_order].number_diff_products; i++)
        {
            if(identifier_product == orders_list[identifier_order].shoplist[i].identifier)
            {
                /* If it does */
                printf("%s %d.\n", store_stock[identifier_product].name, orders_list[identifier_order].shoplist[i].amount);
                return;
            }
        }

        /* If it doesnt */
        printf("%s 0.\n", store_stock[identifier_product].name);
    }
}

void command_m(int identifier_product, int number_orders, int number_diff_products)
{
    if(!(identifier_product < number_diff_products)) /* Verify if the product does not exist */
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", identifier_product);

    else
    {
        #define YES 1 /* Constants to control if there is at least one order with the pretended product */
        #define NO 0
        int i, j, max_index=0, max_amount=0, state = NO;

        /* Cycle to check every order */
        for (i = 0; i < number_orders; i++)
        {
            /* Cycle to check every product in each order */
            for (j = 0; j < orders_list[i].number_diff_products; j++)
            {
                if(identifier_product == orders_list[i].shoplist[j].identifier && max_amount < orders_list[i].shoplist[j].amount)
                {
                    /* Case that an order with greater amount of that product is found */
                    max_amount = orders_list[i].shoplist[j].amount;
                    max_index = i;
                    state = YES; /* We are now sure that there is at least one order with the desired product */
                }
            }
        }

        if(state)
            printf("Maximo produto %d %d %d.\n", identifier_product, max_index, max_amount);
    }
}

void command_l(int number_diff_products)
{
    printf("Produtos\n");

    if (number_diff_products > 0)
    {
        int i , ordered_products[MAX_NUMBER_PROD]; /* Auxiliary array to store the products ids from the store */

        /* Puts in the array the ids from all the products in the store */
        for(i = 0; i < number_diff_products; i++) 
            ordered_products[i] = i;

        /* Calls the quicksort function to order the array */
        quicksort_products(ordered_products, 0, number_diff_products - 1); 

        for(i = 0; i < number_diff_products; i++)
            /* Prints the stores products, ordered by price */
            printf("* %s %d %d\n", store_stock[ordered_products[i]].name, store_stock[ordered_products[i]].price, store_stock[ordered_products[i]].amount);
    }
}


void command_L(int identifier_order, int number_orders)
{
    if(!(identifier_order < number_orders)) /* Verify if the order does not exist */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", identifier_order);
    else
    {
        int i;
        int ordered_products[MAX_PER_ORDER]; /* Auxiliary array to store the orders shoplist indexs */

        printf("Encomenda %d\n", identifier_order);

        /* Places in the array the indexs from the order shoplist */
        for(i = 0; i < orders_list[identifier_order].number_diff_products; i++)
            ordered_products[i] = i;

        /* Calls the quicksort function to order the array */
        quicksort_orders(ordered_products, 0, orders_list[identifier_order].number_diff_products - 1, identifier_order);

        for(i = 0; i < orders_list[identifier_order].number_diff_products; i++)

            /* If each product has stock in that order, it is printed, sorted by their names, alphabetically */ 
            if(orders_list[identifier_order].shoplist[ordered_products[i]].amount > 0)
                printf("* %s %d %d\n", orders_list[identifier_order].shoplist[ordered_products[i]].name, orders_list[identifier_order].shoplist[ordered_products[i]].price, orders_list[identifier_order].shoplist[ordered_products[i]].amount);
    }
}

void command_k(int number_diff_products)
{
    int i;

    printf("Produtos\n");

    for(i = 0; i < number_diff_products; i++)
    {
        printf("* %s %d %d\n", store_stock[i].name, store_stock[i].price, store_stock[i].amount);
    }
}

void command_K(int identifier_order)
{ 
    int i;

    printf("Encomenda %d\n", identifier_order);

    for(i = 0; i < orders_list[identifier_order].number_diff_products; i++)
    {
        printf("* %s %d %d\n", orders_list[identifier_order].shoplist[i].name, orders_list[identifier_order].shoplist[i].price, orders_list[identifier_order].shoplist[i].amount);
    }
}

void quicksort_products(int array[MAX_NUMBER_PROD], int inf, int sup)
{
    int middle;

    if(sup <= inf)
        return;
    
    middle = partition_products(array, inf, sup); /* Stores the item that is already sorted */

    quicksort_products(array, inf, middle - 1); /* Proceeds to sort the remaining two sectors of the array */
    quicksort_products(array, middle + 1, sup);
}

int partition_products(int array[MAX_NUMBER_PROD], int inf, int sup)
{
    int i = inf -1, j = sup;

    while (i < j)
    {
        while (less_products(array[++i], array[sup])); /* Proceeds with the cycle if the first argument is inferior to the second */
        while (less_products(array[sup], array[--j]))
        {
            if(j == inf)
                break;
        }

            if (i < j)
                exchange_products(array, i, j); /* Puts the items in the correct sector of the array, to be ordered */
    }   
        exchange_products(array, i, sup); /* Puts the pivot on its right position */

        return i; /* Returns the position of the pivot, in order for it not to be accounted in the next quicksort, since its in its right position */
}

int less_products(int a, int b)
{
    /* If the first element has smaller price then the second, continues the cycle */
    if (store_stock[a].price < store_stock[b].price)
        return 1;
    /* If they both have the same price, decides with the product ids */
    else if (store_stock[a].price == store_stock[b].price && a < b)
        return 1;
    else
    /* If none of these cases is veryfied, it breaks the cycle */
        return 0;
}

void exchange_products(int array[MAX_NUMBER_PROD], int a, int b)
{
    int aux;

    /* It switches the two given elements */
    aux = array[a];
    array[a] = array[b];
    array[b] = aux;
}


void quicksort_orders(int array[MAX_NUMBER_ORDERS], int inf, int sup, int identifier_order)
{
    int middle;

    if(sup <= inf)
        return;
    
    middle = partition_orders(array, inf, sup, identifier_order); /* Stores the item that is already sorted */

    quicksort_orders(array, inf, middle - 1, identifier_order); /* Proceeds to sort the remaining two sectors of the array */
    quicksort_orders(array, middle + 1, sup, identifier_order);
}


int partition_orders(int array[MAX_NUMBER_ORDERS], int inf, int sup, int identifier_order)
{
    int i = inf -1, j = sup;

    while (i < j)
    {
        while (less_orders(array[++i], array[sup], identifier_order)); /* Proceeds with the cycle if the first argument is inferior to the second */
        while (less_orders(array[sup], array[--j], identifier_order))
        {
            if(j == inf)
                break;
        }

            if (i < j)
                exchange_orders(array, i, j); /* Puts the items in the correct sector of the array, to be ordered */
    }   
        exchange_orders(array, i, sup); /* Puts the pivot on its right position */

        return i; /* Returns the position of the pivot, in order for it not to be accounted in the next quicksort, since its in its right position */
}

int less_orders(int a, int b, int identifier_order)
{
    /* If the string related to the first argument is "smaller" then the second, then it contiues the loop */
    if(strcmp(orders_list[identifier_order].shoplist[a].name, orders_list[identifier_order].shoplist[b].name) < 0)
        return 1;
    else
        return 0;
}

void exchange_orders(int array[MAX_NUMBER_PROD], int a, int b)
{
    int aux;

    /* It switches the two given elements */
    aux = array[a];
    array[a] = array[b];
    array[b] = aux;
}
