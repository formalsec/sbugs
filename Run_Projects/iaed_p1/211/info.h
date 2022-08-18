#ifndef INF0_H
#define INF0_H



#include <stdbool.h>

/****declaration of constants*****/
/*the maximum number of characters of a product description.*/
#define DESCRIPTION 64 
/*the maximum number of products. */
#define TOTAL_PROD 10000 
 /* the maximum number of orders.*/
#define TOTAL_ORDERS 500 
 /* the maximum weight of each order.*/
#define MAX_WEIGHT 200
/*False/ value of zero.*/
#define ZERO 0      
/*true / value of one.*/
#define ONE 1 
/* non existing index*/
#define NONEXISTING -1
/* auxiliary value */
#define DEZ 10



/******************* structures implementation *******************/

typedef struct /* implementation of product */
{
    /*what makes a product ?*/
    int idp;                      /* product ID*/
    char desc[DESCRIPTION]; /* description of a product*/
    int price ;                   /* price of a product */
    int weight;                  /*weight of a  product  */
    int stock;            /* the amount of product available in stock*/
    bool standingP;     /* a flag that verifies whether or not a product is in the system,
    when marked with true(the product is in the system) otherwise it is not*/
    
} product;

typedef struct     /* implementation of order */      
{
    /* what makes an order ?*/
    int ide; /*order ID*/
    int price;  /*price of an order*/
    int weightOrder; /* the weight of an order (has to be less or equal to 200) */
    product products[MAX_WEIGHT]; /*200 products of weight 1 each*/
    bool verifier[MAX_WEIGHT];/*if marked with true the product is in the order*/
    bool standingO ; /* a flag that verifies whether or not an order is in the system,
    when marked with true(the order is in the system) otherwise it is not*/
    
} order;


/******************* structures implementation *******************/



/********* declaration of functions *********/
product createProduct(char *desc, int price, int weight, int stock); /*function that creates a product*/
order createOrder(); /*function that creates and returns an order */


        /********* command functions *********/

void a(char[],int,int,int);    /*function that adds a product to the system ,a command */
void q(int idp,int amount);    /*function that adds stock to an existing product,q command */
void N();    /*function responsible for creating a new order, N command */
void A(int ide,int idp,int stock);    /*function responsible for adding a product to an order,A command */
void r(int idp,int stock);    /*function responsible for removing the stock of an existing product, r command */
void r( int ide,int idp);   /*function responsible for removing a product from an order, R command */
void C(int ide);    /*function responsible for computing the total price of an order,C command */
void p(int idp,int price); /*function that changes the price of an existing product,p command*/
void E(int ide,int idp); /*function that lists the description and stock of a product in an ordee*/
void m(int idp); /* function that lists the id of the order in which a given product has more stock*/
void l(product array[]);  /* function that list every product in the system by ascending order of price*/

/* sorting function */
void mergePrice(product a[],int left,int m,int right);
void mergesortPrice(product a[],int left,int right);
 

#endif /* ifndef INFO_H*/
