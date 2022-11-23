#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "products.h"
#include "misc.h"
#include "orders.h"
#include <string.h>

/*Define an order as a string with max size of 500 and max weight of 200*/
Product order[MAX_ORDERS][MAX_WEIGHT] = {0};

int order_counter = 0; /*order counter is outside function because it is a global variable*/

/*Function to create a new order*/
void new_order()
{
    printf("Nova encomenda %d.\n", order_counter);

    order_counter++;
}

/*Function to determine if an order exists and is valid*/
int ord_exists(int ide)
{
    /*If the order ID is greater than or equal 0 and the order ID is less than the order_counter, return true. Else, return false*/
    if (ide >= 0 && ide < order_counter)
    {
        return 1;
    }

    return 0;
}

/*Function to ensure the weight of the order does not exceed max weight*/
int order_weight(int ide)
{
    int i;
    int weight_counter = 0;

    /*For all values of i from 0 to 199 (max weight - 1)*/
    for (i = 0; i < MAX_WEIGHT; i++)
    {
        /*If the product exists and is valid, add to the weight counter the product of the weight and the quantity of that product in that order*/
        if (strlen(order[ide][i].description) != 0)
        {
            weight_counter += order[ide][i].weight * order[ide][i].quantity;
        }
    }

    return weight_counter;
}

/*Function to add a product/s to an order*/
void add_to_order()
{
    int ide;
    int idp;
    int quantity;
    int j = 0;
    int i = 0;

    scanf("%d:%d:%d", &ide, &idp, &quantity);

    /*If the order does notexists and is not valid, return error */
    if (!ord_exists(ide))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }

    /*If the product does note xists and is not valid, return error */
    else if (!prod_exists(idp))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

    /*If there isnt sufficient quantity in stock to add to the order, return error */
    else if (stock[idp].quantity < quantity)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }

    /*If the order weight with the added stock exceeds the max weight, return error*/
    else if (order_weight(ide) + (stock[idp].weight * quantity) > MAX_WEIGHT)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }

    else
    {
        stock[idp].quantity -= quantity;

        /*For the value of i from 0 to 199; if a product with that ID exists in the order, add the quantity to order and leave loop*/
        for (i = 0; i < MAX_WEIGHT; i++)
        {
            if (strlen(order[ide][i].description) != 0 && order[ide][i].id == idp)
            {
                order[ide][i].quantity += quantity;
                j++;
                break;
            }
        }
        if (j == 0)
        {
            /*For the value of i from 1 to 199, If the */
            for (i = 0; i < MAX_WEIGHT; i++)
            {
                /*If a product with that ID does not exist in the order, add the product to the first available spot*/
                if (strlen(order[ide][i].description) == 0)
                {
                    order[ide][i] = stock[idp];
                    order[ide][i].quantity = quantity;
                    break;
                }
            }
        }
    }
}

/*Function that returns the total price of a function*/
void order_price()
{
    int ide;
    int i = 0;
    int total_price = 0;

    scanf(" %d", &ide);

    /*If the order is not valid, return error*/
    if (!ord_exists(ide))
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }

    else
    {   
        /*For all the values of i from 0 to 199, if the product is in the order add to the total price the total of the products in the order*/
        for (i = 0; i < MAX_WEIGHT; i++)
        {
            if (strlen(order[ide][i].description) != 0)
            {
                total_price += stock[order[ide][i].id].price * order[ide][i].quantity;
            }
        }

        printf("Custo da encomenda %d %d.\n", ide, total_price);
    }
}

/*Function that returns the quantity and description of a product in an order*/
void order_desc_quantity()
{
    int ide;
    int idp;
    int i = 0;
    int quantity = 0;

    scanf(" %d:%d", &ide, &idp);

    /*If the order does not exist, return error*/
    if (!ord_exists(ide))
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }

    /*If the product does not exist, return error*/
    else if (!prod_exists(idp))
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }

    else
    {
        /*For all the values of i from 0 to 199, if the product is in the order and the product ID matches the ID given, add to the quantity the products quantity*/
        for (i = 0; i < MAX_WEIGHT; i++)
        {
            if (strlen(order[ide][i].description) != 0 && order[ide][i].id == idp)
            {
                quantity = order[ide][i].quantity;
                break;
            }
        }
        printf("%s %d.\n", stock[idp].description, quantity);
    }
}

/*Function to return the order at which a product occures most*/
void compare_orders()
{
    int idp;
    int highest_ide;
    int highest_ide_quantity = 0;
    int i;
    int j;

    scanf(" %d", &idp);

    /*If the product does not exist, return error*/
    if (!prod_exists(idp))
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }

    else
    {
        /*For all the values of i from 0 to the total number of orders*/
        for (i = 0; i < order_counter; i++)
        {
            /*For all the values of j from 0 to 199*/
            for (j = 0; j < MAX_WEIGHT; j++)
            {   
                /*If the order is valid and the product ID matches the ID given and the quantity of that product is higher than the highest previous quantity, set the product quantity to the highest product quantity*/
                if (strlen(order[i][j].description) != 0 && order[i][j].id == idp && order[i][j].quantity > highest_ide_quantity)
                {
                    highest_ide_quantity = order[i][j].quantity;
                    highest_ide = i;
                }
            }
        }
        /*If the highest quantity is not 0, return the product ID, The highest ID and the highest quantity*/
        if (highest_ide_quantity != 0)
        {
            printf("Maximo produto %d %d %d.\n", idp, highest_ide, highest_ide_quantity);
        }
    }
}

/*Function to sort orders by alphabetically by description*/
void sort_orders()
{
    int ide;
    int i;
    int j;

    scanf(" %d", &ide);

    /*If the order does not exist, return error*/
    if (!ord_exists(ide))
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }

    else
    {
        /*For all values of j from 0 to 199, if there is no more products left in the order, break loop*/
        for (j = 0; j < MAX_WEIGHT; j++)
        {
            if (strlen(order[ide][j].description) == 0)
            {
                break;
            }
        }
        /*Use alphabet_sort funtion to sort the orders from product 0 to the last product*/
        alphabet_sort(order[ide], 0, j - 1);

        printf("Encomenda %d\n", ide);

        for (i = 0; i < j; i++)
        {
            printf("* %s %d %d\n", order[ide][i].description, stock[order[ide][i].id].price, order[ide][i].quantity);
        }
    }
}

void remove_from_order()
{
    int ide;
    int idp;
    int j = -1;
    int i = 0;

    scanf(" %d:%d", &ide, &idp);

    /*If order does not exist, return error*/
    if (!ord_exists(ide))
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }

    /*If product does not exist, return error*/
    else if (!prod_exists(idp))
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
        /*fRr all the values of i from 0 to 199 (all the orders)*/
        for (i = 0; i < MAX_WEIGHT; i++)
        {
            /*If a product is in the order*/
            if (strlen(order[ide][i].description) != 0)
            {
                /*If the product ID matches the give ID, */
                if (order[ide][i].id == idp)
                {

                    stock[order[ide][i].id].quantity += order[ide][i].quantity;
                    j = i;
                }
            }
            else
            {
                break;
            }
        }

        /*If i(the last order) is Greater than 0 and j(the last product in the order) is greather than or equal to 0, delete the order*/
        if (i > 0 && j >= 0)
        {
            order[ide][j] = order[ide][i - 1];
            order[ide][i - 1].id = 0;
            order[ide][i - 1].description[0] = '\0';
            
        }
    }
}