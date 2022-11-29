#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAXID 10000     /* max product id number */
#define DSIZE 64        /* max description string length */
#define MAXORDERS 500   /* max number of orders */
#define MAXWEIGHT 200   /* max weight an order can support */

#define QTD 1           /* index of quantity in the products vector */
#define ID 0            /* index of id in the products vector */


/* declared structures */

/* product struct represents any product in the system's stock */
typedef struct product {
    int id;                         /* identifier of the product */
    char description[DSIZE];        /* string with the description of the product */
    int price;                      /* price of the product */
    int weight;                     /* weight of the product */
    int qtd;                        /* qtdity of the product in stock */
}Product;

/* order struct represent any order in the system */
typedef struct order {
    int id;                         /* identifier of the order */
    int weight;                     /* current weight of the order */
    int number;                     /* current number of products in the order */
    int products[MAXWEIGHT][2];     /* products in the order */
}Order;


/* Function prototypes */
void init();
void a();
void q();
void N();
void A();
void r();
void R();
void C();
void p();
void E();
void m();
void l();
void L();
void k();
void K();
void quickSort_l(int v[], int left, int right);
void quickSort_L(int v[], int left, int right);
void swap(int v[], int i, int j);
int find_idp(int ide,int idp);
int cmp_description(int x, int y);
int cmp_price(int x, int y);


/* global variables */
int productId;                    /* number of products created */
int orderId;                      /* number of orders created */
Product stock[MAXID];             /* array with all products created */
Order orders[MAXORDERS];          /* array with all orders created */


/* ******* MAIN ******* */
int main()
{
    int c;

    init();
    
    /* ask for command */
    while ((c = getchar()) != EOF && c != 'x') {
        
        getchar();  /* ignore blank space */

        switch (c) {
            
            case 'a':
                a();
                break;
            case 'q':
                q();
                break;
            case 'N':
                N();
                break;
            case 'A':
                A();
                break;
            case 'r':
                r();
                break;
            case 'R':
                R();
                break;
            case 'C':
                C();
                break;
            case 'p':
                p();
                break;                                          
            case 'E':
                E();
                break;
            case 'm':
                m();
                break;
            case 'l':
                l();
                break;
            case 'L':
                L();
                break;
        }
    }
    
    return 0;
}


/* ******** Funtions ******** */

/* init: initialize products vector of each order */
void init()
{
    int i, j;

    /* initialize all orders ids with an invalid id (-1) */
    for (i = 0; i < MAXORDERS; i++)
        for (j = 0; j < MAXWEIGHT; j++)
            orders[i].products[j][ID] = -1;
}


/* a: adds a product to the system */
void a()
{
    scanf("%[^:]:%d:%d:%d\n", stock[productId].description, 
            &stock[productId].price, 
            &stock[productId].weight, 
            &stock[productId].qtd);

    stock[productId].id = productId;        /* set product id */

    printf("Novo produto %d.\n", productId);

    productId++;        /* increment productId for the next creation */
}


/* q: adds stock to an existing product */
void q()
{
    int idp, qtd;

    scanf("%d:%d\n", &idp, &qtd);

    if (idp >= productId) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return;
    }

    stock[idp].qtd += qtd;      /* add quantity */
}


/* N: creates a new order */
void N()
{
    orders[orderId].id = orderId;
    
    printf("Nova encomenda %d.\n", orderId);
    
    orderId++;      /* increment orderId for the next creation */
}


/* A: adds a product to the order */
void A()
{
    int i;
    int idp, ide, qtd;

    scanf("%d:%d:%d\n", &ide, &idp, &qtd);

    if (ide >= orderId) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    if (idp >= productId) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    if (stock[idp].qtd < qtd) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide); 
        return;
    }

    if ((orders[ide].weight + stock[idp].weight * qtd) > MAXWEIGHT) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }

    if (qtd <= 0) return;

    if ((i = find_idp(ide, idp)) < 0) {                             /* if product is not in the order yet */
        orders[ide].products[orders[ide].number][ID] = idp;         /* save idp of the product */
        orders[ide].products[orders[ide].number][QTD] += qtd;       /* add the quantity of the product */
        orders[ide].number++;                                       /* increment number of products */
    }
    else
        orders[ide].products[i][QTD] += qtd;    /* add the quantity to the product found */
    
    orders[ide].weight += stock[idp].weight * qtd;    /* add weight to the order */
    stock[idp].qtd -= qtd;                            /* remove the quantity asked from the stock */
}


/* r: remove some stock from an existing product */
void r()
{
    int idp, qtd;
    
    scanf("%d:%d\n", &idp, &qtd);

    if (idp >= productId) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }

    if (stock[idp].qtd < qtd) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
    }

    stock[idp].qtd -= qtd;      /* add quantity */
}


/* R: remove a product from an order */
void R()
{
    int i;
    int ide, idp;

    scanf("%d:%d\n", &ide, &idp);

    if (ide >= orderId) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    if (idp >= productId) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    if ((i = find_idp(ide, idp)) < 0) return;       /* products was not found in the order */

    /* remove weight of the product from the order */
    orders[ide].weight -= stock[idp].weight * orders[ide].products[i][QTD];
    /* restore the quantity of products to the stock */
    stock[idp].qtd += orders[ide].products[i][QTD];

    /* shift all products 1 product to the left */
    while (i < orders[ide].number-1) {
        orders[ide].products[i][ID] = orders[ide].products[i+1][ID];
        orders[ide].products[i][QTD] = orders[ide].products[i+1][QTD];
        i++;
    }

    /* set the prev space of the last order free */
    orders[ide].products[i][ID] = -1;
    orders[ide].products[i][QTD] = 0;

    orders[ide].number--;       /* decrement the number of products int the order */
}


/* C: calculate the total price of an order */
void C()
{
    int i;
    int ide, total;

    total = 0;
    scanf("%d\n", &ide);

    if (ide >= orderId) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    for (i = 0; i < MAXWEIGHT; i++) {
        total += stock[orders[ide].products[i][ID]].price * orders[ide].products[i][QTD];   /* add price * qtd */
    }

    printf("Custo da encomenda %d %d.\n", ide, total);
}


/* p: change the price of a product in the system */
void p()
{
    int idp, price;

    scanf("%d:%d\n", &idp, &price);

    if (idp >= productId) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }

    stock[idp].price = price;   /* change price */
}


/* E: print the information of a product in an order (description and quantity) */
void E()
{
    int i;
    int qtd;
    int ide, idp;

    scanf("%d:%d\n", &ide, &idp);

    if (ide >= orderId) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    if (idp >= productId) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }

    if ((i = find_idp(ide, idp)) >= 0)
        qtd = orders[ide].products[i][QTD];
    else
        qtd = 0;        /* product not found in the order */

    printf("%s %d.\n", stock[idp].description, qtd);
}


/* m: print the id of the order with the most quantity of a product */
void m()
{
    int i, j;
    int idp;
    int higherQtd, higherId;        /* current higher quantity */

    higherId = higherQtd = 0;

    scanf("%d\n", &idp);

    if (idp >= productId) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }

    /* iterate through each order and compare the quantity */ 
    for (i = 0; i < orderId; i++) {
        if ((j = find_idp(i, idp)) >= 0)
            if (orders[i].products[j][QTD] > higherQtd) {     /* choose the one with higher quantity */
                higherId = i;
                higherQtd = orders[i].products[j][QTD];
            }
    }

    if (higherQtd > 0)      /* make sure qtd is positive */
        printf("Maximo produto %d %d %d.\n", idp, higherId, higherQtd);

}


/* l: prints a list of all existing products by ascending order of prices */
void l()
{   
    int i;
    int stockCopy[MAXID] = {0};

    /* copy all products ids created to the array */
    for (i = 0; i < productId; i++)
        stockCopy[i] = i;

    quickSort_l(stockCopy, 0, productId-1);

    printf("Produtos\n");
    for (i = 0; i < productId; i++)
        printf("* %s %d %d\n", stock[stockCopy[i]].description, 
                stock[stockCopy[i]].price, 
                stock[stockCopy[i]].qtd);
}


/* L: prints a list of all products in an order by alphabetic order */
void L()
{
    int i, j;
    int ide;
    /* local array that will contain the current products in the order */
    int orderCopy[MAXWEIGHT] = {0};

    scanf("%d\n", &ide);

    if (ide >= orderId) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    /* copy all product ids created from the order to the array */
    for (i = 0, j = 0; i < orders[ide].number; i++)
        orderCopy[j++] = orders[ide].products[i][ID];

    quickSort_L(orderCopy, 0, orders[ide].number-1);

    printf("Encomenda %d\n", ide);
    for (i = 0; i < orders[ide].number; i++)
        printf("* %s %d %d\n", stock[orderCopy[i]].description, 
                stock[orderCopy[i]].price, 
                orders[ide].products[find_idp(ide, orderCopy[i])][QTD]);
}


/* quickSort_l: sort a array of ids by ascending order of price */
void quickSort_l(int v[], int left, int right)
{
    int i, last;

    if (left >= right)      /* array contains fewer than two elements */
        return;

    swap(v, left, (left + right)/2);    /* choose the pivot */
    last = left;

    for (i = left+1; i <= right; i++)
        if (cmp_price(v[i], v[left]))   
            swap(v, ++last, i);

    swap(v, left, last);                /* restore pivot position */
    quickSort_l(v, left, last-1);       /* recursion */
    quickSort_l(v, last+1, right);
}

/* quickSort_L: sort an array of ids by alphabetic order */
void quickSort_L(int v[], int left, int right)
{
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right)/2);
    last = left;

    for (i = left+1; i <= right; i++)
        if (cmp_description(v[i], v[left]))
            swap(v, ++last, i);

    swap(v, left, last);
    quickSort_L(v, left, last-1);
    quickSort_L(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
    int tmp;

    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}


/* find_idp: search for a specific idp in the order 
 * return its index in the array; if the idp was not
 * found return -1 */
int find_idp(int ide, int idp)
{
    int i;

    for (i = 0; i < MAXWEIGHT; i++)
        if (orders[ide].products[i][ID] == idp) 
            return i;
    return -1;
}

/* cmp_description: returns 1 if description of x is alphabetically lower 
 * than the description of y and 0 otherwise */
int cmp_description(int x, int y)
{
    return (strcmp(stock[x].description, stock[y].description) < 0);
}

/* cmp_price: returns 1 if price of x in lower than price of y and 0 otherwise;
 * in case of equal prices compare by ids */
int cmp_price(int x, int y)
{
    return (stock[x].price < stock[y].price || (x < y && stock[x].price == stock[y].price));
}
