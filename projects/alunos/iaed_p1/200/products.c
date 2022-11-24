#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include "products.h"
#include "misc.h"
#include <string.h>

/*Define stock as a strng of products with the max size of 10000.*/
Product stock[MAX_STOCK_SIZE] = {0};

/*Function to verify the descriptions validity*/
void get_desc(char string[]) 
{
    int position = 0; /*Set position to 0*/
    int character = getchar(); 

    /*While the description is valid and less than 64 characters, stores the character in the string.*/
    while (character != ':' && position < PRODUCT_DESC_SIZE - 1) 
    {
        string[position] = character;
        position++;

        character = getchar();
    }
    string[position] = '\0';
}

/*Function to create a new product*/
void new_product () 
{
    static int id = 0;
    char description[PRODUCT_DESC_SIZE];
    int price; /*Price of the product*/
    int weight; /*Weight of the product*/
    int quantity; /*Quantity of the product*/
    Product prod;

    getchar(); /*remove whitespace*/
    get_desc (description);

    scanf ("%d:%d:%d", &price, &weight, &quantity);
    
    /*Copies the products dexcription to the string*/
    strcpy(prod.description, description); 

    /*Copies price, weight, quantity and id to the string*/
    prod.price = price;
    prod.weight = weight;
    prod.quantity = quantity;
    prod.id = id;
    stock[id] = prod;

    printf("Novo produto %d.\n", id);

    id++;
}

/*Function to test if a product exists and is valid*/
int prod_exists(int id)
{   
    /* If the product id is between 0 and 10000 and the descriprion does not equal 0, return true. Else, return false*/
    if (id >= 0 && id < MAX_STOCK_SIZE && strlen(stock[id].description)!= 0) 
    {
        return 1;
    }
    return 0;
}

/*Function to add the quantity of a product in stock*/
void add_stock()
{
    int idp; /*Product ID*/
    int qtd; /*Desired quantity to add*/

    scanf(" %d:%d", &idp, &qtd);
    
    /*If the product exists, add the desired quantity to the stock. Else, return error.*/
    if (prod_exists(idp))
    {
        stock[idp].quantity += qtd;   
    }

    else
    {
        printf ("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}

/*Function to remove the quantity of a product in stock*/
void remove_stock()
{
    int idp;
    int qtd;

    scanf(" %d:%d", &idp, &qtd);
    
    /*If the product exists and is valid. Else, return error*/
    if (prod_exists(idp))
    {
        /*If the quantity in stock is less than the quantity to remove, raise error. Else, remove quantity from stock*/
        if (stock[idp].quantity < qtd)
        {
            printf ("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        }
        
        else
        {
            
            stock[idp].quantity -= qtd;
        }
    }
    else
    {
        printf ("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
}

/*Function to change the price of a product in stock.*/
void change_price()
{
    int idp;
    int price;

    scanf(" %d:%d", &idp, &price);

    /*If the product existsand is valid, set the stock price to the desired price. Else, return error.*/
    if (prod_exists(idp))
    {
        stock[idp].price = price;
    }

    else
    {
        printf ("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
}

/*Function to sort products by ID number*/
void sort_products()
{
    int i;
    int j;
    Product stock_copy[MAX_STOCK_SIZE]; 

    memcpy(stock_copy, stock, sizeof(stock)); /*Make a copy of the stock as to not alter the stock*/

    /*For all values of j from 0 to 10000*/
    for (j = 0; j < MAX_STOCK_SIZE; j++)
    {
        /*If the product does not exist and is not valid, leave loop.*/
        if (!prod_exists(j))
        {
            break;
        }
    }

    /*Sort the copy of the stock by ID number using the price_sort function*/
    price_sort(stock_copy, 0, j - 1);

    printf ("Produtos\n");

    /*For all values of i from until j, j being the number of products in stock, print description, price and quantity.*/
    for (i = 0; i < j; i++)
    {
        printf("* %s %d %d\n", stock_copy[i].description, stock_copy[i].price, stock_copy[i].quantity);
    }
}