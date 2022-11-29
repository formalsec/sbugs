#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "products.h"
#include <stdio.h>
#include "misc.h"
#include "orders.h"
#include <string.h>

/*Function to show stock unordered*/
void show_stock()
{
    int i;

    printf("Produtos\n");

    /*For all the values o f i from 0 to 199, if product exists print description, price and quantity*/
    for (i = 0; i < MAX_STOCK_SIZE; i++)
    {
        if (prod_exists(i))
        {
            printf("* %s %d %d\n", stock[i].description, stock[i].price, stock[i].quantity);
        }
    }
}

/*Function to show orders unordered*/
void show_orders()
{
    int i;
    int ide;

    scanf(" %d", &ide);

    printf("Encomenda %d\n", ide);

    /*For all the values of i from 0 to 199, if the product is in the order, return the description, price and quantity*/
    for (i = 0; i < MAX_WEIGHT; i++)
    {
        if (strlen(order[ide][i].description) != 0)
        {
            printf("* %s %d %d\n", order[ide][i].description, order[ide][i].price, order[ide][i].quantity);
        }
    }
}

/*function to divide the string as per the quick sort algorithm*/
int partition(Product arr[], int low, int high)
{
    Product pivot = arr[high];
    Product temp_prod;
    int i = (low - 1);
    int j;

    for (j = low; j <= high - 1; j++)
    {
        if (pivot.price > arr[j].price || (pivot.price == arr[j].price && pivot.id > arr[j].id))
        {
            i++;

            if (i != j)
            {
                temp_prod = arr[i];
                arr[i] = arr[j];
                arr[j] = temp_prod;
            }
        }
    }

    temp_prod = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp_prod;

    return (i + 1);
}
/*Function to quick sort all products by price*/
void price_sort(Product arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        price_sort(arr, low, pi - 1);
        price_sort(arr, pi + 1, high);
    }
}

/*function to divide the string as per the quick sort algorithm*/
int alphabet_partition(Product arr[], int low, int high)
{
    Product pivot = arr[high];
    Product temp_prod;
    int i = (low - 1);
    int j;

    for (j = low; j <= high - 1; j++)
    {
        if (strcmp(arr[j].description, pivot.description) < 0)
        {
            i++;

            if (i != j)
            {
                temp_prod = arr[i];
                arr[i] = arr[j];
                arr[j] = temp_prod;
            }
        }
    }

    temp_prod = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp_prod;

    return (i + 1);
}

/*Function to quick sort all orders alphabetically*/
void alphabet_sort(Product arr[], int low, int high)
{
    if (low < high)
    {
        int pi = alphabet_partition(arr, low, high);

        alphabet_sort(arr, low, pi - 1);
        alphabet_sort(arr, pi + 1, high);
    }
}