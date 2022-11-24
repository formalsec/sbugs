#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include "ls.h" /* Logistics System Library */

/* 
 *	Command __a__
 *	- Adds a new product to the system.
 */
void cmd_a() {
	char description[MAXSTRINGSIZE];
	int price, weight, quantity;
	scanf(" %[^:]:%d:%d:%d", description, &price, &weight, &quantity);
	getchar();
	add_product(description, price, weight, quantity);
}

/* 
 *	Command q
 *	- Adds stock to an existing product in the system.
 */
void cmd_q() {
	int product_id, quantity;
	scanf("%d:%d", &product_id, &quantity);
	getchar();
	add_stock(product_id, quantity);
}

/* 
 *	Command N
 *	- Creates a new order.
 */
void cmd_N() {
	getchar();
	create_order();
}

/* 
 *	Command A
 *	- Adds a product to an order.
 */
void cmd_A() {
	int order_id, product_id, quantity;
	scanf("%d:%d:%d", &order_id, &product_id, &quantity);
	getchar();
	add_product_to_order(order_id, product_id, quantity);
}

/* 
 *	Command r 
 *  - Removes stock from an existing product.
 */
void cmd_r() {
	int product_id, quantity;
	scanf("%d:%d", &product_id, &quantity);
	getchar();
	remove_stock_from_product(product_id, quantity);
}

/* 
 * 	Command R
 *	- Removes a product from an order.
 */
void cmd_R() {
	int order_id, product_id;
	scanf("%d:%d", &order_id, &product_id);
	getchar();
	remove_product_from_order(order_id, product_id);
}

/* 
 *	Command C
 *	- Calculates an order's cost.
 */
void cmd_C() {
	int order_id;
	scanf("%d", &order_id);
	getchar();
	get_order_cost(order_id);
}

/* 
 * 	Command p
 *	- Changes the price of an existing product in the system.
 */
void cmd_p() {
	int product_id, price;
	scanf("%d:%d", &product_id, &price);
	getchar();
	change_product_price(product_id, price);
}

/* 
 * 	Command E
 *	- Lists the description and quantity of a product in an order.
 */
void cmd_E() {
	int order_id, product_id;
	scanf("%d:%d", &order_id, &product_id);
	getchar();
	list_product_from_order(order_id, product_id);
}

/* 
 *	Command m
 *	- Lists the order identifier in which the given product occurs most often.
 *    If there are 2 or more orders in this situation, the lowest order `id` 
 * 	  will be printed.
 */
void cmd_m() {
	int product_id;
	scanf("%d", &product_id);
	getchar();
	list_order_with_highest_qty_of_product(product_id);
}


/* 
 *	Command l
 *	- Lists all products in the system in ascending price order.
 * 	  If there are 2 or more products with the same price, these will
 * 	  be printed in ascending order of product id.
 */
void cmd_l() {
	getchar();
	list_all_products_by_price_asc();
}

/* 
 * 	Command L
 *	- List all products in an order in alphabetical order from the description.
 */
void cmd_L() {
	int order_id;
	scanf("%d", &order_id);
	getchar();
	list_products_by_description(order_id);
}

int main() {
	/* Command character */
	char cmd;

	/* Flag that signals if the program terminated */
	int terminated = 0;

	while (terminated != 1) {
		cmd = getchar();
		switch (cmd) {
			case 'a':
				cmd_a();
				break;
			case 'q':
				cmd_q();
				break;
			case 'N':
				cmd_N();
				break;
			case 'A':
				cmd_A();
				break;
			case 'r':
				cmd_r();
				break;
			case 'R':
				cmd_R();
				break;
			case 'C':
				cmd_C();
				break;
			case 'p':
				cmd_p();
				break;
			case 'E':
				cmd_E();
				break;
			case 'm':
				cmd_m();
				break;
			case 'l':
				cmd_l();
				break;
			case 'L':
				cmd_L();
				break;
			case 'x':
				terminated = 1;
				break;
		}
	}
	return 0;
}
