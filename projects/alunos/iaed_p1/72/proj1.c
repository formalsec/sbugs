#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>

/**************  Global Constants  **************/

/* The maximum number of different products. */
#define MAX_PRODUCTS 10000

/* Maximum string length. */
#define MAX_DESCRIPTION 64

/* The maximum number of orders. */
#define MAX_ORDERS 500

/* The maximum weight that an order can have. */
#define MAX_WEIGHT 200

/**************  Data structures  **************/

/* Defining the product type. */
typedef struct
{

    int identifier;
    char description[MAX_DESCRIPTION];
    int price;
    int weight;
    int quantity;

} product;

/* Defining the product info used in an order. */
typedef struct
{
    /* The product's unique identifier, used to fetch info from the product list in the system. */
    int identifier;

    /* The quantity of said product in an order. */
    int quantity;

    /* Whether or not the product is active. 
       In case a product is active, active == 1.
       If a product is not active, active == 0.
       As an example, let's say someone adds a product to an order, then removes it.
       Active is initialized as 0 in the global variable "orders", so it firstle switches to 1.
       Once the product is removed, active switches back to 0, making it so the product space
       can be used for a new product. */
    int active;

} product_info;

/* Defining the order type. */
typedef struct
{
    /* Max weight is 200, minimum weight per product is 1, so maximum 200 different products. */
    product_info products_info[MAX_WEIGHT];

} order;

/**************  Global Variables  **************/

/* The current number of different products in the system. */
int num_products = 0;

/* The current number of different orders in the system. */
int num_orders = 0;

/* Initializes the array of products and orders, setting all values to zero. */
product products[MAX_PRODUCTS];

order orders[MAX_ORDERS];

/**************  Prototypes  **************/

void command_a();
void command_q();
void command_N();
void command_A();
void command_r();
void command_R();
void command_C();
void command_p();
void command_E();
void command_m();
void command_l();
void command_L();

/**************  Main function  **************/

int main()
{
    char command;

    while ((command = getchar()) != 'x')
    {
        switch (command)
        {
        case 'a':
            command_a();
            break;

        case 'q':
            command_q();
            break;

        case 'N':
            command_N();
            break;

        case 'A':
            command_A();
            break;

        case 'r':
            command_r();
            break;

        case 'R':
            command_R();
            break;

        case 'C':
            command_C();
            break;

        case 'p':
            command_p();
            break;

        case 'E':
            command_E();
            break;

        case 'm':
            command_m();
            break;

        case 'l':
            command_l();
            break;

        case 'L':
            command_L();
            break;

        default:
            continue;
        }
    }
    return 0;
}

/**************  Separate functions  **************/

/**** Auxiliary functions ****/

/* Returns the total weight of a given order. */
int calc_weight(order ord)
{
    int i;
    int weight_total = 0;

    /* For each index in the order's product info array. */
    for (i = 0; i < MAX_WEIGHT; i++)
    {
        /* Checks to see if said item is actually part of the order
           or if it's just empty space. */
        if (ord.products_info[i].active)
        {
            /* If the product is part of the order, go fetch its weight from the
               global products variable, multiply it by the quantity of said item
               in the order and add that to the total weight. */
            weight_total += (products[ord.products_info[i].identifier].weight * ord.products_info[i].quantity);
        }
    }

    return weight_total;
}

/* In case a product is part of an order, returns its index in the products_info array.
   Else, returns -1. */
int product_in_order(int product_id, order ord)
{
    int i;
    /* Starts in_order as -1, that is the default value
       which signifies that the product isn't in the order. */
    int in_order = -1;

    /* For each slot in the product_info array. */
    for (i = 0; i < MAX_WEIGHT; i++)
    {
        /* In case the product is active (remember that product_info.active is either 1 or 0, 
           marking said product as being in the order), checks to see if its identifier matches
           the identifier of the product received as input. */
        if (ord.products_info[i].active && ord.products_info[i].identifier == product_id)
        {
            /* If the identifiers match, return the product's index in the products_info array. */
            in_order = i;
            break;
        }
    }
    return in_order;
}

/* Returns the first available space in the product array of an order.
   We assume ord has a slot for a new product. */
int available_space(order ord)
{
    int i;
    int index = 0;

    for (i = 0; i < MAX_WEIGHT; i++)
    {
        if (ord.products_info[i].active == 0)
        {
            index = i;
            break;
        }
    }

    return index;
}

/* Returns the quantity of a product in an order. */
int product_quantity_order(int product_id, order ord)
{
    int quantity = 0, product_index;

    /* Checks if the product is part of the order (remember product_in_order returns
       -1 in case the product isn't part of the order). If it is, product_index is equal
       to its index in the products_info array of said order. */
    if ((product_index = product_in_order(product_id, ord)) != -1)
    {
        quantity = ord.products_info[product_index].quantity;
    }
    return quantity;
}

/********** Mergesort implementation. **********/

/****** Product Mergesort ******/

/* Global array responsible for helping in sorting
   all the products using mergesort. */
product prod_aux[MAX_PRODUCTS];

/* Returns 1 if the price of product a is lesser than the price of b OR
   if the prices are the same but a has a smaller identifier.
   Otherwise, returns 0. */
int prod_less(product a, product b)
{
    return (((a.price == b.price) && a.identifier < b.identifier) || a.price < b.price);
}

/* Mergesort implementation as taught in IAED, altered for the 
   product type and using the auxiliary array prod_aux. */
void prod_merge(product prods[], int left, int m, int right)
{
    int i, j, k;
    for (i = (m + 1); i > left; i--)
    {
        prod_aux[i - 1] = prods[i - 1];
    }

    for (j = m; j < right; j++)
    {
        prod_aux[right + m - j] = prods[j + 1];
    }

    for (k = left; k <= right; k++)
    {
        if (prod_less(prod_aux[j], prod_aux[i]) || i > m)
        {
            prods[k] = prod_aux[j--];
        }
        else
        {
            prods[k] = prod_aux[i++];
        }
    }
}

void prod_mergesort(product prods[], int left, int right)
{
    int m = (right + left) / 2;

    if (right <= left)
    {
        return;
    }

    prod_mergesort(prods, left, m);
    prod_mergesort(prods, (m + 1), right);
    prod_merge(prods, left, m, right);
}

/****** Order Mergesort ******/

/* Global array responsible for helping in sorting
   all the products using mergesort. An order has
   a maximum of 200 products. */
product_info order_aux[MAX_WEIGHT];

/* Returns 1 in case description a is first alphabetically than description b.
   Otherwise returns a. */
int order_less(product_info a, product_info b)
{
    int i;
    int char_a, char_b;

    /* Tests for 5 different cases for each pair of characters. */
    for (i = 0; i < MAX_DESCRIPTION; i++)
    {
        (char_b = products[b.identifier].description[i]);
        (char_a = products[a.identifier].description[i]);

        /* If description b ends, that means it was equal to desciption a
           before ending. If it was equal and is smaller, then it is first
           alphabetically. So, return 0. */
        if (char_b == '\0')
        {
            return 0;
        }

        /* If description a ends first, it was equal to description b, but is
           smaller. So, return 1. */
        else if (char_a == '\0')
        {
            return 1;
        }

        /* If the chars are the same, analyze the next pair of chars. */
        else if (char_a == char_b)
        {
            continue;
        }
        /* If the chars aren't the same, they are different.
           So, return 1 if char a < char b OR
           return 1 if char a < char b. */
        else
        {
            return (char_a < char_b);
        }
    }
    /* If the function reaches this point, there is a problem . */
    return 0;
}

/* Mergesort implementation as taught in IAED, altered for the 
   product_info type and using the auxiliary array order_aux. */
void order_merge(product_info prods[], int left, int m, int right)
{
    int i, j, k;
    for (i = (m + 1); i > left; i--)
    {
        order_aux[i - 1] = prods[i - 1];
    }

    for (j = m; j < right; j++)
    {
        order_aux[right + m - j] = prods[j + 1];
    }

    for (k = left; k <= right; k++)
    {
        if (order_less(order_aux[j], order_aux[i]) || i > m)
        {
            prods[k] = order_aux[j--];
        }
        else
        {
            prods[k] = order_aux[i++];
        }
    }
}

void order_mergesort(product_info prods[], int left, int right)
{
    int m = (right + left) / 2;

    if (right <= left)
    {
        return;
    }

    order_mergesort(prods, left, m);
    order_mergesort(prods, (m + 1), right);
    order_merge(prods, left, m, right);
}

/**** Project functions ****/

/* Adds a new product to the system */
void command_a()
{
    int identifier;

    /* Updates the number of different products currently in the system. */
    num_products++;

    /* The next available space in the product array will have index equal to the total
       number of products added so far minus one, therefore the product's identifier
       will too. */
    identifier = (num_products - 1);

    products[identifier].identifier = identifier;

    scanf(" %[^:]:%d:%d:%d\n", products[identifier].description, &products[identifier].price,
          &products[identifier].weight, &products[identifier].quantity);

    printf("Novo produto %d.\n", identifier);
}

/* Adds stock to an existing product in the system. */
void command_q()
{
    int product_id, quantity;

    scanf(" %d:%d\n", &product_id, &quantity);

    /* Checks if the product ID matches up with the number of products currently in the system.
       If it doesnt, the function returns an error. */
    if (product_id >= num_products)
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", product_id);
    }

    else
    {
        products[product_id].quantity += quantity;
    }
}

/* Adds a new order to the system. */
void command_N()
{
    int order_id;

    scanf("\n");

    num_orders++;

    order_id = (num_orders - 1);

    printf("Nova encomenda %d.\n", order_id);
}

/* Either adds a new product to an existing order or, in case said product is already part
   of the order, adds a certain quantity of that product to the order. */
void command_A()
{
    int order_id, product_id, quantity, product_index;

    scanf(" %d:%d:%d\n", &order_id, &product_id, &quantity);

    /* Sees if there is any possible error and, if so, prints it. */

    /* Order doesn't exist. */
    if (order_id >= num_orders)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", product_id, order_id);
    }
    /* Product doesn't exist. */
    else if (product_id >= num_products)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", product_id, order_id);
    }
    /* Not enough stock */
    else if (quantity > products[product_id].quantity)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", product_id, order_id);
    }
    /* Weight exceeded. */
    else if ((calc_weight(orders[order_id]) + (products[product_id].weight * quantity)) > MAX_WEIGHT)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", product_id, order_id);
    }

    else
    {
        /* Subtracts stock from the product. */
        products[product_id].quantity -= quantity;

        /* If the product is already in the order, adds stock. */
        if ((product_index = product_in_order(product_id, orders[order_id])) != -1)
        {
            orders[order_id].products_info[product_index].quantity += quantity;
        }

        /* In case the product isn't yet part of the order, adds it */
        else
        {
            /* Finds out the first available index in the product array. */
            product_index = available_space(orders[order_id]);

            /* Updates the available products array to show that there is a new active product in the order. */
            orders[order_id].products_info[product_index].active = 1;

            /* Updates the product array with the new product's identifier and 
               updates its quantity to match the quantity given in the input. */
            orders[order_id].products_info[product_index].identifier = products[product_id].identifier;
            orders[order_id].products_info[product_index].quantity = quantity;
        }
    }
}

/* Removes stock from an existing product. */

void command_r()
{
    int product_id, quantity;

    scanf(" %d:%d\n", &product_id, &quantity);

    /* Checks possible errors. */
    /* Product not in system. */
    if (product_id >= num_products)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", product_id);
    }
    /* Not enough stock in system. */
    else if (quantity > products[product_id].quantity)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, product_id);
    }

    else
    {
        products[product_id].quantity -= quantity;
    }
}

/* Removes a product from an order */
void command_R()
{
    int order_id, product_id, product_index;

    scanf(" %d:%d\n", &order_id, &product_id);

    /* Sees if there is any possible error and, if so, prints it. */

    /* Order doesn't exist. */
    if (order_id >= num_orders)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", product_id, order_id);
    }
    /* Product doesn't exist. */
    else if (product_id >= num_products)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", product_id, order_id);
    }

    /* Checks whether the product is part of the order. */
    else if ((product_index = product_in_order(product_id, orders[order_id])) != -1)
    {
        /* If it's part of the order, switches "active" to 0, marking the
           product as not part of the order. */
        orders[order_id].products_info[product_index].active = 0;

        /* Adds the quantity of the product present in the order back to stock. */
        products[product_id].quantity += orders[order_id].products_info[product_index].quantity;
    }

    /* If the product is not part of the order, this function doesn't change anything,
       nor does it detect an error. */
}

/* Calculates the price of an order. */
void command_C()
{
    int i;
    int price_total = 0, order_id;

    scanf(" %d\n", &order_id);

    /* Order doesn't exist. */
    if (order_id >= num_orders)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", order_id);
    }

    else
    {
        for (i = 0; i < MAX_WEIGHT; i++)
        {
            /* Checks whether the product is part of the order. */
            if (orders[order_id].products_info[i].active)
            {
                /* If the product is part of the order, get its price from the global variable products,
                then multiply it by its quantity in the order. Lastly, add that value to the total price. */
                price_total += (products[orders[order_id].products_info[i].identifier].price * orders[order_id].products_info[i].quantity);
            }
        }
        printf("Custo da encomenda %d %d.\n", order_id, price_total);
    }
}

/* Alters the price of a product already in the system. */
void command_p()
{
    int product_id, price;

    scanf(" %d:%d\n", &product_id, &price);

    if (product_id >= num_products)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", product_id);
    }
    else
    {
        products[product_id].price = price;
    }
}

/* Lists the description and quantity of a product in an order. */
void command_E()
{
    int order_id, product_id;

    scanf(" %d:%d\n", &order_id, &product_id);

    /* Sees if there is any possible error and, if so, prints it. */

    /* Order doesn't exist. */
    if (order_id >= num_orders)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order_id);
    }
    /* Product doesn't exist. */
    else if (product_id >= num_products)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", product_id);
    }

    else
    {
        printf("%s %d.\n", products[product_id].description, product_quantity_order(product_id, orders[order_id]));
    }
}

/* Lists the order ID of the order in which a given product occurs more often. */
void command_m()
{
    int i;
    int product_id, quantity_temp = 0;
    int order_id_max = 0, quantity_max = 0;

    scanf(" %d\n", &product_id);

    /* Nonexistent product throws an error. */
    if (product_id >= num_products)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", product_id);
    }
    /* If there aren't any orders, don't do anything. */
    else if (num_orders == 0)
    {
        return;
    }

    /* Else, search through all the orders and mark the one that has the
       highest quantity of the given product. */
    else
    {
        for (i = 0; i < num_orders; i++)
        {
            if ((quantity_temp = product_quantity_order(product_id, orders[i])) > quantity_max)
            {
                quantity_max = quantity_temp;
                order_id_max = i;
            }
        }

        /* If the product doesn't appear in any orders, don't go anything. */
        if (quantity_max == 0)
        {
            return;
        }
        /* Else, list said product, the order with the highest quantity of the product
           and the quantity. */
        else
        {
            printf("Maximo produto %d %d %d.\n", product_id, order_id_max, quantity_max);
        }
    }
}

/* Lists all the products currently in the system according to their price,
   from lowest to highest. */
void command_l()
{
    int i;

    /* Creates a copy, so ordering the products doesn't affect the system. */
    product products_copy[MAX_PRODUCTS];

    for (i = 0; i < num_products; i++)
    {
        products_copy[i] = products[i];
    }

    prod_mergesort(products_copy, 0, (num_products - 1));

    /* Displays the products according to price. */
    printf("Produtos\n");

    for (i = 0; i < num_products; i++)
    {
        printf("* %s %d %d\n", products_copy[i].description, products_copy[i].price, products_copy[i].quantity);
    }
}

/* Lists all the products currently in an order alphabetically. */
void command_L()
{
    int i;
    int order_id, max_index_copy = 0;

    product_info products_info_copy[MAX_WEIGHT];

    scanf(" %d\n", &order_id);

    /* Order doesn't exist. */
    if (order_id >= num_orders)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order_id);
    }

    else
    {
        /* Creates a copy of the order, using only the items that are active in the order. */
        for (i = 0; i < MAX_WEIGHT; i++)
        {
            /* Checks if a product is active and, if so, copies it. */
            if (orders[order_id].products_info[i].active)
            {
                /* Each time a copy occurs, adds +1 to max_index_copy, moving it
                   to the next index. */
                products_info_copy[max_index_copy++] = orders[order_id].products_info[i];
            }
        }

        /* Sorts the copy array up to the max used index (remember when we copied the
           last item we added +1 to max_index_copy, so we have to subtract 1). */
        order_mergesort(products_info_copy, 0, (max_index_copy - 1));

        /* Prints the sorted array, fetching relevant info from the products array. */
        printf("Encomenda %d\n", order_id);

        /* Max_index_copy is already the highest index + 1, so we don't have to add anything. */
        for (i = 0; i < (max_index_copy); i++)
        {
            if (products_info_copy[i].active)
            {
                printf("* %s %d %d\n", products[products_info_copy[i].identifier].description, products[products_info_copy[i].identifier].price, products_info_copy[i].quantity);
            }
        }
    }
}