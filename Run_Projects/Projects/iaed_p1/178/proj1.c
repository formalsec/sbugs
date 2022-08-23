#include <stdio.h>
#include <string.h>

/* ============================================================== */
/* max number of products */
#define MAXPROD 10000

/* max length of the description of a product */
#define MAXDESC 63

/* max number of orders */
#define MAXORD 500 

/* max number of different products in an order */
#define MAXDIF 200

/* number of members in order array */
#define ARYORD 2

/* max weight of an order */
#define MAXWGH 200

/* constants to identify in the array of products of an order its idp and quantity, respectively */
#define IDP 0
#define QUANTITY 1

/* boolean values */
#define TRUE 1
#define FALSE 0

/* ============================================================== */
/* STRUCTURES */
/* ============================================================== */

/* structure for a product */ 
typedef struct /* product structures are given an idp, price, weight, stock and description */
{
    int idp, price, weight, stock;
    char description[MAXDESC];
} product;

/* structure for an order */
typedef struct /* order structures are given an ide, weight, product counter ( the number of different products in it) and a product array */
{
    int ide, weight, counter, products[MAXDIF][ARYORD]; /* the product array has arrays (becoming a matrix) */
} order;                                                /* the first element has the idp of a product and the second its quantity (within the order) */

typedef product Item;
    #define less(A, B) (A.price < B.price)
    #define exch(A, B) { Item t = A; A = B; B = t; }

/* ============================================================== */
/* GLOBAL VARIABLES AND ARRAYS */
/* ============================================================== */

/* global array with all different products */
product ProductList[MAXPROD] = {0};

/* global array with all different orders */
order OrderList[MAXORD] = {0};

/* IDP Counter that increases everytime a new product is added */
int IdpCounter = 0;

/* IDE Counter that increases everytime a new order is added */
int IdeCounter = 0;

/* ============================================================== */
/* MAIN FUNCTIONS */
/* ============================================================== */
void CreatesProduct();
void AddStock();
void CreatesOrder();
void AddProduct();
void RemoveStock();
void RemoveProduct();
void CalculateOrderCost();
void ChangePrice();
void OrderAmount();
void MostRecurringProduct();
void LeastToMostExpensive();
void ListProductsByName();
/* ============================================================== */
/* AUXILIAR FUNCTIONS */
/* ============================================================== */
product FindsProduct(int idp);                      /* function that finds an existing product, returning the structure of the respective product */
int ChecksProductInOrder(int idp, order object);    /* function that checks if a certain product exists within an order */
void InitializeMatrix(int list[][ARYORD]);          /* function that initializes all values of a matrix to a constant */
int ChecksProductInCatalog(int idp);                /* function that checks if a possible product exists in the system catalog */
int CalculateTotalProductQty(int idp);              /* function that calculates all around quantity of an existing product */
int Partition(Item a[], int l, int r);              /* partition function for the first Quicksort (integers) */
void Quicksort(Item a[], int l, int r);             /* Quicksort function (integers) */
int Partition_words(product a[], int l, int r);     /* partition function for the second Quicksort (strings) */
void Quicksort_words(product a[], int l, int r);    /* Quicksort function (strings) */
int FindsProductQuantityInOrder(int ide, int idp);  /* function that returns an existing product's quantity in a specific order */
order FindsOrder(int ide);                          /* function that finds an existing order, returning the structure of the respective order */
int ChecksOrder(int ide);                           /* function that checks if a certain order exists in the system */
/* ============================================================== */

/* Reads the first letter in the command to indicate which path (function) to follow */
int main()
{
    char command;
    int output = FALSE;

    do
    {
        scanf("%c", &command);
        
            switch (command)
        {
            case 'a':
            CreatesProduct();
            break;
            
            case 'q':
            AddStock();
            break;
            
            case 'N':
            CreatesOrder();
            break;
            
            case 'A':
            AddProduct();
            break;
            
            case 'r':
            RemoveStock();
            break;
            
            case 'R':
            RemoveProduct();
            break;
            
            case 'C':
            CalculateOrderCost();
            break;
            
            case 'p':
            ChangePrice();
            break;
            
            case 'E':
            OrderAmount();
            break;
            
            case 'm':
            MostRecurringProduct();
            break;
            
            case 'l':
            LeastToMostExpensive();
            break;
            
            case 'L':
            ListProductsByName();
            break;
            
            case 'x':
            output = TRUE;
            break;
            
            default:
            break;
        }
    } while (output != TRUE);
    return 0;
}

/* ============================================================== */
/* Command Functions */

/* creates a new product */
void CreatesProduct()
{
    product object;
    
    scanf(" %[^:]:%d:%d:%d", object.description, &object.price, &object.weight, &object.stock);
    
    object.idp = IdpCounter;    
    ProductList[IdpCounter] = object; /* adds the new product in the product array */
    IdpCounter++;
    
    printf("Novo produto %d.\n", object.idp);   
}

/* adds stock to an existing product */
void AddStock()
{
    int idp, quantity;

    scanf("%d:%d", &idp, &quantity);
    
    if (ChecksProductInCatalog(idp) == FALSE)
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return;
    }
    else /* if the product exists, proceeds to add stock */
    {
        ProductList[idp].stock += quantity;
        return;
    }              
}

/* creates a new order */
void CreatesOrder()
{
    order object;

    object.ide = IdeCounter;
    object.weight = 0;
    object.counter = 0;
    InitializeMatrix(object.products); /* initializes the matrix of products, so that the previous values don't influence other functions and operations */
    OrderList[IdeCounter] = object; /* adds the new order in the order array */
    IdeCounter++;

    printf("Nova encomenda %d.\n", object.ide);
}

/* either adds more quantity to an already existing product in the order, or initializes it in that order */
void AddProduct()
{
    int i = 0;
    int ide, idp, qty;

    scanf("%d:%d:%d", &ide, &idp, &qty);

    if (ChecksOrder(ide) == FALSE)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if (ChecksProductInCatalog(idp) == FALSE)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    else if (FindsProduct(idp).stock < qty)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }
    else if ((FindsOrder(ide).weight + (FindsProduct(idp).weight * qty)) > MAXWGH)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }
    else /* only adds the product if all the inputs are acceptable and respect the limitations of an order */
    {            
        if (ChecksProductInOrder(idp, OrderList[ide]) == TRUE) /* checks if the product is already in the order */
        {
            while (OrderList[ide].products[i][IDP] != idp) /* searches for the product in the array of products */
            { i++; }
            OrderList[ide].weight += ProductList[idp].weight * qty;
            OrderList[ide].products[i][QUANTITY] += qty;
            ProductList[idp].stock -= qty;
            return;
        }
        else /* in case it isn't, adds and initializes its parameters */
        {
            ProductList[idp].stock -= qty;                                   /* each order has an array of arrays; the second one is composed of two elements */
            OrderList[ide].products[OrderList[ide].counter][IDP] = idp;      /* the first element is the idp of the new product */
            OrderList[ide].products[OrderList[ide].counter][QUANTITY] = qty; /* the second element is the quantity present in the order */
            OrderList[ide].weight += ProductList[idp].weight * qty;
            OrderList[ide].counter++;
            return;
        }
    }
}

/* removes stock from an existing product */
void RemoveStock()
{
    int idp, quantity;

    scanf("%d:%d", &idp, &quantity);
    
    if (ChecksProductInCatalog(idp) == FALSE)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
    else if (FindsProduct(idp).stock < quantity)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, idp);
    }
    else /* only removes if the inputs are acceptable and respect the minimum amount of stock */
    {
        ProductList[idp].stock -= quantity;
        return;
    }
}

/* removes an existing product from an order */
void RemoveProduct()
{
    int i = 0, ide, idp;
    
    scanf("%d:%d", &ide, &idp);

    if (ChecksOrder(ide) == FALSE)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (ChecksProductInCatalog(idp) == FALSE)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else /* only proceeds to the next step if the inputs are seen as acceptable */
    {
        if (ChecksProductInOrder(idp, OrderList[ide]) == TRUE) /* checks if the product is in the order */
        {    
            while (OrderList[ide].products[i][IDP] != idp) /* searches for the product in the array of products */
            { i++; }
            ProductList[idp].stock += OrderList[ide].products[i][QUANTITY];
            OrderList[ide].weight -= (ProductList[idp].weight * OrderList[ide].products[i][QUANTITY]);
            OrderList[ide].products[i][QUANTITY] = 0;
            return;
        }
        return;
    }    
}

/* calculates the cost of a specific order */
void CalculateOrderCost()
{
    int i, ide, total_cost = 0;

    scanf("%d", &ide);

    if (ChecksOrder(ide) == FALSE)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else /* only starts to calculate the value if the order exists */
    {
        for (i = 0; i < OrderList[ide].counter; i++) /* goes through all products in the order */
        {
            total_cost += (FindsProduct(OrderList[ide].products[i][IDP]).price * OrderList[ide].products[i][QUANTITY]);
        }
        printf("Custo da encomenda %d %d.\n", ide, total_cost);
        return;
    }  
}

/* changes the price of an existing product */
void ChangePrice()
{
    int idp, new_price;

    scanf("%d:%d", &idp, &new_price);

    if (ChecksProductInCatalog(idp) == FALSE)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }
    else /* only changes the price of the product if it already exists */
    {
        ProductList[idp].price = new_price;
        return;
    }
}

/* returns the current quantity of a certain product present in a given order */
void OrderAmount()
{
    int i = 0, ide, idp;

    scanf("%d:%d", &ide, &idp);

    if (ChecksOrder(ide) == FALSE)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    else if (ChecksProductInCatalog(idp) == FALSE)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    else if (ChecksProductInOrder(idp, OrderList[ide]) == FALSE) /* if the product isn't in the order but exists, returns 0 */
    {
        printf("%s 0.\n", ProductList[idp].description);
        return;
    }
    else /* if all inputs are deemed acceptable, continues */
    {
        while (OrderList[ide].products[i][IDP] != idp) /* searches for the product in the order */
        { i++; }
        printf("%s %d.\n", ProductList[idp].description, OrderList[ide].products[i][QUANTITY]);
        return;
    }
}

/* searches for the order that has the most amount of a specific product */
void MostRecurringProduct()
{
    int i, idp, ide, most_quantity = 0;

    scanf("%d", &idp);

    if (ChecksProductInCatalog(idp) == FALSE)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    else if (IdeCounter == 0) /* if there are no orders, ends function */
    {
        return;
    }
    else /* due to both product and order being existent, proceeds */
    {
        for (i = 0; i < IdeCounter; i++)
        {
            if (ChecksProductInOrder(idp, OrderList[i]) == TRUE) /* checks if the product is in the order */
            {
                if (FindsProductQuantityInOrder(OrderList[i].ide, idp) > most_quantity)
                /* if it is, only accepts if its quantity is bigger than the current one */          
                {
                    most_quantity = FindsProductQuantityInOrder(OrderList[i].ide, idp);
                    ide = OrderList[i].ide;
                }
            }
        }
        if (most_quantity > 0) /* only prints the value if the initial one has changed */
        {
            printf("Maximo produto %d %d %d.\n", idp, ide, most_quantity);
            return;
        }        
    }
}

/* lists all existing products in the system by their price, frowm lowest to highest */
void LeastToMostExpensive()
{
    int i;
    product array[MAXPROD]; /* array that stores the products present in the system; later, it will be organized */

    for (i = 0; i < IdpCounter; i++) /* adds all existing products in the system to the array */
    {
        array[i] = ProductList[i];
    }

    Quicksort(array, 0, IdpCounter-1);

    printf("Produtos\n");
    for (i = 0; i < IdpCounter; i++)
    {
        printf("* %s %d %d\n", array[i].description, array[i].price, array[i].stock);
    }    
    return;
}

/* lists all existing products in a certain order regarding their description, alphabetically */
void ListProductsByName()
{
    int i, ide;
    product array[MAXDIF]; /* array that stores the products present the order; later, it will be organized */

    scanf("%d", &ide);

    if (ChecksOrder(ide) == FALSE)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    else /* only proceeds to the function if the inputs are acceptable */
    {
        for (i = 0; i < OrderList[ide].counter; i++)
        {
            array[i] = FindsProduct(OrderList[ide].products[i][IDP]); /* adds all products within a certain order to the array */
        }

        Quicksort_words(array, 0, OrderList[ide].counter - 1);
        
        printf("Encomenda %d\n", ide);
        
        for (i = 0; i < OrderList[ide].counter; i++)
        {
            if (ChecksProductInOrder(array[i].idp, OrderList[ide]) == TRUE)
            {
                if (FindsProductQuantityInOrder(ide, array[i].idp) > 0) /* only prints the product if it exists (quantity different from zero) */
                {
                    printf("* %s %d %d\n", array[i].description, array[i].price, FindsProductQuantityInOrder(ide, array[i].idp));
                }
            }
        }
        return;
    }
}

/* ============================================================== */
/* Auxiliar Functions */

int Partition(Item a[], int l, int r)
{
    int i = l - 1;
    int j = r;
    Item v = a[r];

    while (i < j)
    {
        while ((a[++i].price < v.price) || ((a[i].price == v.price) && (a[i].idp < v.idp)))
        { ; }
        while ((v.price < a[--j].price) || ((a[j].price == v.price) && (v.idp < a[j].idp)))
        {
            if (j == l)
            { break; }
        }
        if (i < j)
        {
            exch(a[i], a[j]);
        }        
    }
    exch(a[i], a[r]);
    return i;
}

void Quicksort(Item a[], int l, int r)
{
    int i;
    if (r <= l)
    { return; }
    i = Partition(a, l, r);
    Quicksort(a, l, i - 1);
    Quicksort(a, i + 1, r);
}

int Partition_words(product a[], int l, int r)
{
    int i = l - 1;
    int j = r;
    product v = a[r], t;

    while (i < j)
    {
        while (strcmp(a[++i].description, v.description) < 0)
        { ; }
        while (strcmp(v.description, a[--j].description) < 0)
        {
            if (j == l)
            { break; }
        }
        if (i < j)
        {
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    t = a[i];
    a[i] = a[r];
    a[r] = t;
    
    return i;
}

void Quicksort_words(product a[], int l, int r)
{
    int i;
    if (r <= l)
    { return; }
    i = Partition_words(a, l, r);
    Quicksort_words(a, l, i - 1);
    Quicksort_words(a, i + 1, r);
}

product FindsProduct(int idp)
{
    int i = 0;
    while (ProductList[i].idp != idp)
    { i++; }
    return ProductList[i];
}

int ChecksOrder(int ide)
{
    int i, OrderTracker = FALSE;
    for (i = 0; i < IdeCounter; i++)
    {
        if (OrderList[i].ide == ide)
        {
            OrderTracker = TRUE;
            break;
        }
    }
    return OrderTracker;
}

order FindsOrder(int ide)
{
    int i = 0;
    while (OrderList[i].ide != ide)
    { i++; }
    return OrderList[i];
}

int ChecksProductInOrder(int idp, order object)
{
    int i, ProductTracker = FALSE;
    for (i = 0; i < object.counter; i++)
    {
        if (object.products[i][0] == idp)
        {
            ProductTracker = TRUE;
        }
    }
    return ProductTracker;
}

void InitializeMatrix(int list[][ARYORD])
{
    int i, j;
    for (i = 0; i < MAXDIF; i++)
    {
        for (j = 0; j < ARYORD; j++)
        {
            list[i][j] = 0;
        }
    }
}

int ChecksProductInCatalog(int idp)
{
    int i, result = FALSE;
    for (i = 0; i < IdpCounter; i++)
    {
        if (ProductList[i].idp == idp)
        {
            result = TRUE;
        }
    }
    return result;
}

int FindsProductQuantityInOrder(int ide, int idp)
{
    int i = 0;
    while (OrderList[ide].products[i][IDP] != idp)
    { i++; }
    return (OrderList[ide].products[i][QUANTITY]);
}