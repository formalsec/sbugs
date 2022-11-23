#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utilities.h"


void create_prod();
void add_stock();
void create_order();
void prod_to_order();
void rm_stock();
void rm_prod();
void calc_cost();
void change_price();
void list_prod();
void most_occ();
void list_all();
void list_order();


/* Reads a character from stdin and performs an associated action
 * Entering 'x' exits the program */
int main() {
	char command;

	while ((command = getchar()) != 'x' ) {

		switch(command) {

			case 'a':
				create_prod();
				break;

			case 'q':
				add_stock();
				break;

			case 'N':
				create_order();
				break;

			case 'A':
				prod_to_order();
				break;

			case 'r':
				rm_stock();
				break;

			case 'R':
				rm_prod();
				break;

			case 'C':
				calc_cost();
				break;

			case 'p':
				change_price();
				break;

			case 'E':
				list_prod();
				break;

			case 'm':
				most_occ();
				break;

			case 'l':
				list_all();
				break;

			case 'L':
				list_order();
				break;
		}
	}

	return 0;
}


/* Inserts a new product into the system */
void create_prod() {

	scanf(" %[^:]:%d:%d:%d", sys[totalp].desc, &sys[totalp].price, 
							 &sys[totalp].wgt, &sys[totalp].qtt);
	printf("Novo produto %d.\n", totalp++);
}


/* Adds stocks to a product in the system */
void add_stock() {
	int p_id, qtt;

	scanf(" %d:%d", &p_id, &qtt);

	/* Product IDs above ( (# of products)-1) are invalid */
	if (p_id >= totalp) {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p_id);
		return;
	}

	sys[p_id].qtt += qtt;
}


/* Creates a new order, with no products */
void create_order() {

	printf("Nova encomenda %d.\n", totalo++);
}


 
/* Adds the ID (and quantity) of a product to an order if it is not yet included.
 * Else, only adds its quantity */
void prod_to_order() {
	int o_id, p_id, qtt;

	scanf(" %d:%d:%d", &o_id, &p_id, &qtt);

	/* Order IDs above ( (# of orders)-1) are invalid */
	if (o_id >= totalo) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda"
			   " inexistente.\n", p_id, o_id);
		return;
	}

	if (p_id >= totalp) {
		printf("Impossivel adicionar produto %d a encomenda %d. Produto"
			   " inexistente.\n", p_id, o_id);
		return;
	}

	/* Abort if the there is not enough stock to satisfy the order */
	if (sys[p_id].qtt < qtt) {
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade"
			   " em stock insuficiente.\n", p_id, o_id);
		return;
	}

	/* Abort if the total weight of the order would surpass the maximum
	 * after transference */
	if (sys[p_id].wgt*qtt + ords[o_id].wgt > MAX_WEIGHT) {
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda"
			   " excede o maximo de 200.\n", p_id, o_id);
		return;
	}

	/* Put a product in the order, if it is not already there */
	if ( !prod_in(p_id, &ords[o_id]) ) { 
		int num = ords[o_id].num++;

		ords[o_id].ids[num] = p_id;
	}

	/* Transfer the stock from the system into the order */
	sys[p_id].qtt			-= qtt;
	ords[o_id].prods[p_id]	+= qtt;
	ords[o_id].wgt 			+= sys[p_id].wgt * qtt;
}


/* Removes stock from existing product */
void rm_stock() {
	int p_id, qtt;

	scanf(" %d:%d", &p_id, &qtt);

	if (p_id >= totalp) {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p_id);
		return;
	}

	/* Abort if there is not enough stock to remove from */
	if (sys[p_id].qtt < qtt) {
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade"
			   " insuficiente.\n", qtt, p_id);
		return;
	}

	sys[p_id].qtt -= qtt;
}


/* Turns a product's quantity in an order into 0, effectively removing it */
void rm_prod() {
	int o_id, p_id;
	int *prod_qtt;

	scanf(" %d:%d", &o_id, &p_id);

	if (o_id >= totalo) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda"
			   " inexistente.\n", p_id, o_id);
		return;
	}

	if (p_id >= totalp) {
		printf("Impossivel remover produto %d a encomenda %d. Produto"
				" inexistente.\n", p_id, o_id);
		return;
	}

	prod_qtt		 = &ords[o_id].prods[p_id];
	sys[p_id].qtt	+= (*prod_qtt);
	ords[o_id].wgt	-= sys[p_id].wgt * (*prod_qtt);
	(*prod_qtt) = 0;
}


/* Calculates the total cost of an order */
void calc_cost() {
	int i, o_id, cost=0;

	scanf(" %d", &o_id);

	if (o_id >= totalo) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda"
			   " inexistente.\n", o_id);
		return;
	}


	/* Add the price of the bulk of each 
	 * product in the order to (total) 'cost' */
	for (i=0; i<ords[o_id].num; i++) {
		int id	= ords[o_id].ids[i], 
			qtt	= ords[o_id].prods[id];

		cost += sys[id].price * qtt;
	}

	printf("Custo da encomenda %d %d.\n", o_id, cost);
}


/* Changes the price of a product */
void change_price() {
	int p_id, new_p;

	scanf(" %d:%d", &p_id, &new_p);

	if (p_id >= totalp) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", p_id);
		return;
	}

	sys[p_id].price = new_p;
}


/* Lists the description and quantity of a product in an order */
void list_prod() {
	int o_id, p_id, qtt;

	scanf(" %d:%d", &o_id, &p_id);

	if (o_id >= totalo) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
		return;
	}

	if (p_id >= totalp) {
		printf("Impossivel listar produto %d. Produto inexistente.\n", p_id);
		return;
	}

	qtt = ords[o_id].prods[p_id];
	printf("%s %d.\n", sys[p_id].desc, qtt);
}



/* Lists the ID of the order in which given product is 
 * found in greatest quantity, and the quantity itself */
void most_occ() {
	int i, p_id, max = 0, max_o;

	scanf(" %d", &p_id);

	if (p_id >= totalp) {
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p_id);
		return;
	}

	/* Find the order with the greatest quantity of the product */
	for (i=0; i<totalo; i++) { 
		int qtt = ords[i].prods[p_id];

		if (qtt > max) {
			max = qtt;
			max_o = i;
		}
	}

	/* Do not print if no order has the product */
	if (max > 0)
		printf("Maximo produto %d %d %d.\n", p_id, max_o, max);
}



/* Lists the descriptions, prices and quantities of every
 * product in the system, sorted by price (ascending) */
void list_all() {	
	int i;  
	int *ids = can_fail_malloc(totalp*sizeof(int));

	/* Copy the IDs of every product in the system into array 'ids' */
	for (i=0; i<totalp; i++)
		ids[i] = i;

	/* Sort 'ids' by product price before printing */
	merge_sort(ids, 0, totalp-1, price_ordered);
	puts("Produtos");

	for (i=0; i<totalp; i++)
		printf("* %s %d %d\n", sys[ids[i]].desc, sys[ids[i]].price, sys[ids[i]].qtt);

	free(ids);
}



/* Lists the descriptions, prices, and quantities of every 
 * product in an order, sorted alphabetically (ascending) */
void list_order() {
	int i, o_id, num;
	int *ids;

	scanf(" %d", &o_id);

	if (o_id >= totalo) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
		return;
	}

	num = ords[o_id].num;
	ids = ords[o_id].ids; /* A copy of this array is unnecessary as it can be, or not, sorted */

	/* Sort 'ids' by product description before printing */
	merge_sort(ids, 0, num-1, ab_ordered); 
	printf("Encomenda %d\n", o_id);

	for (i=0; i<num; i++) {
		int qtt = ords[o_id].prods[ids[i]];

		/* Do not print if the product is not currently in the order (qtt = 0) */
		if (qtt > 0)
			printf("* %s %d %d\n", sys[ids[i]].desc, sys[ids[i]].price, qtt);
	}
}

