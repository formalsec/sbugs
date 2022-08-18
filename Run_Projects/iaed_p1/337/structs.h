#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_PROD 10000
#define MAX_ORDER 500
#define MAX_WEIGHT 200
#define DESC_SIZE 64


typedef struct product {
	char desc[DESC_SIZE];
	int price, wgt, qtt;
} product;


typedef struct order {
	int wgt, num;
	/* array 'prods' stores the quantity of each product in the order, 
	 * and 'ids' stores their IDs contiguously */ 
	int prods[MAX_PROD], ids[MAX_PROD];
} order;


/* Array with every product created (system) */
product sys[MAX_PROD];
int totalp=0; /* Number of products created */


/* Array with every order created */
order ords[MAX_ORDER];
int totalo=0; /* Number of orders created */


#endif /* STRUCTS_H */

