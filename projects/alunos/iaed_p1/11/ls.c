#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "ls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Number of prouducts in the system. */
int product_count = 0;

/* Number of orders in the system. */
int order_count = 0;

/* Array containing all the products in the system. */
Product storage[MAXPRODUCTS];

/* Array containing all the product id's in the system. */
int storage_ids[MAXPRODUCTS];

/* Array containing all the orders in the system. */
Order orders[MAXORDERS];

void add_product(const char *description, const int price, const int weight,
					const int stock) {
	/* Access next free position in storage and add the inputed values */
	storage[product_count].id = product_count;
	strcpy(storage[product_count].description, description);
	storage[product_count].price = price;
	storage[product_count].weight = weight;
	storage[product_count].stock = stock;

	/* Add id so array of product ids */
	storage_ids[product_count] = product_count;

	/* Product count is incremented */
	printf("Novo produto %d.\n", product_count++);
}
 
void add_stock(const int product_id, const int quantity) {
	/* Exit if product is non exixtent. */
	if (product_id >= product_count) {
		printf("Impossivel adicionar produto %d ao stock. "
			   "Produto inexistente.\n", product_id);
		return;
	}
	storage[product_id].stock += quantity;
}

void create_order() {
	printf("Nova encomenda %d.\n", order_count++);
}

void add_product_to_order(const int order_id, const int product_id, 
						    const int quantity) {
	/* Weight of the order after the product quantity is added. */						
	int weight_after;

	/* Exit if order is non exixtent. */
	if(order_id >= order_count) {
		printf("Impossivel adicionar produto %d a encomenda %d. "
			   "Encomenda inexistente.\n", product_id, order_id);
		return;
	}

	/* Exit if product is non exixtent. */
	if(product_id >= product_count) {
		printf("Impossivel adicionar produto %d a encomenda %d. "
		       "Produto inexistente.\n", product_id, order_id);
		return;
	}

	/* Exit if quantity of product in storage is smaller than the one to add. */
	if(quantity > storage[product_id].stock) {
		printf("Impossivel adicionar produto %d a encomenda %d. "
			   "Quantidade em stock insuficiente.\n", product_id, order_id);
		return;
	}

	/* Determine the weight of the order after the product quantity is added. */
	weight_after = orders[order_id].weight + 
					storage[product_id].weight * quantity;

	/* Exit if weight after product add is greater than 200. */
	if(weight_after > MAXWEIGHT) {
		printf("Impossivel adicionar produto %d a encomenda %d. "
		       "Peso da encomenda excede o maximo de 200.\n",
			   product_id, order_id);
		return;
	}
	
	/* In case a product already exists in the order, quantity will be added */
	if(orders[order_id].product_qty[product_id] != 0) {
		storage[product_id].stock -= quantity;
		orders[order_id].product_qty[product_id] += quantity;
		orders[order_id].weight = weight_after;
		return;
	}

	/* Otherwise a new product will be added to the order */
	storage[product_id].stock -= quantity;
	orders[order_id].product_ids[orders[order_id].num_products] = product_id;
	orders[order_id].product_qty[product_id] = quantity;
	orders[order_id].weight = weight_after;
	orders[order_id].num_products++;
}

void remove_stock_from_product(const int product_id, const int quantity) {
	
	/* Exit if product is non exixtent. */
	if(product_id >= product_count) {
		printf("Impossivel remover stock do produto %d. "
			   "Produto inexistente.\n", product_id);
		return;
	}

	/* Exit if quantity to remove is greater than the existing one. */
	if(quantity > storage[product_id].stock) {
		printf("Impossivel remover %d unidades do produto %d do stock. "
			   "Quantidade insuficiente.\n", quantity, product_id);
		return;
	}

	storage[product_id].stock -= quantity;
}

void remove_product_from_order(const int order_id, const int product_id) {
	int i;
	/* Order being assessed. */
	Order order;

	/* Exit if order is non exixtent. */
	if(order_id >= order_count) {
		printf("Impossivel remover produto %d a encomenda %d. "
			   "Encomenda inexistente.\n", product_id, order_id);
		return;
	}

	/* Exit if product is non exixtent. */
	if(product_id >= product_count) {
		printf("Impossivel remover produto %d a encomenda %d. "
			   "Produto inexistente.\n", product_id, order_id);
		return;
	}
	
	order = orders[order_id];

	/* Search for product in the order. */
	for (i = 0; i < order.num_products; i++) {
		if(order.product_ids[i] == product_id) { /* If found, remove it. */
			storage[product_id].stock += order.product_qty[product_id]; 
			order.weight -= order.product_qty[product_id] 
							* storage[product_id].weight;
			order.product_qty[product_id] = 0;
			/* Move the last product to the position of the removed one. */
			order.product_ids[i] = order.product_ids[--order.num_products];
			/* Assign -1 to the old last position, to clean that position. */
			order.product_ids[order.num_products] = -1;
			orders[order_id] = order;
			return;
		}
	}
}

void get_order_cost(const int order_id) {
	int i;
	int num_products = orders[order_id].num_products;
	/* Id of the product being assessed. */
	int product_id;
	/* Total cost of the order. */
	int cost = 0;

	/* Exit if order is non exixtent. */
	if(order_id >= order_count) {
		printf("Impossivel calcular custo da encomenda %d. "
			   "Encomenda inexistente.\n", order_id);
		return;
	}

	/* Go through all products in order and sum the price (stored in storage) */
	for (i = 0; i < num_products ; i++) {
		product_id = orders[order_id].product_ids[i];
		cost += storage[product_id].price 
				* orders[order_id].product_qty[product_id];
	}

	printf("Custo da encomenda %d %d.\n", order_id, cost);
}

void change_product_price(const int product_id, const int price) {
	/* Exit if product is non exixtent. */
	if(product_id >= product_count) {
		printf("Impossivel alterar preco do produto %d. "
		       "Produto inexistente.\n", product_id);
		return;
	}

	storage[product_id].price = price;
}

void list_product_from_order(const int order_id, const int product_id){
	/* Exit if order is non exixtent. */
	if (order_id >= order_count) {
		printf("Impossivel listar encomenda %d. "
			   "Encomenda inexistente.\n", order_id);
		return;
	}

	/* Exit if product is non exixtent. */
	if (product_id >= product_count) {
		printf("Impossivel listar produto %d. "
			   "Produto inexistente.\n", product_id);
		return;
	}

	printf("%s %d.\n", storage[product_id].description, 
					   orders[order_id].product_qty[product_id]);
}

void list_order_with_highest_qty_of_product(const int product_id) {
	int i;
	/* Highest quantity of the product inside an order. */
	int highest_quantity = 0;
	/* Order with the highest quantity of the product. */
	int order_id = -1;

	/* Exit if product is non exixtent. */
	if (product_id >= product_count) {
		printf("Impossivel listar maximo do produto %d. "
		       "Produto inexistente.\n", product_id);
		return;
	}
	/* Search through all the orders for the highest quantity of the product */
	for (i = 0; i < order_count; i++) {
		if (orders[i].product_qty[product_id] > highest_quantity) {
				order_id = i;
				highest_quantity = orders[i].product_qty[product_id];
		}
	}
	
	/* Only print if an order with the product is found */
	if (order_id >= 0)
		printf("Maximo produto %d %d %d.\n", product_id, 
											 order_id,
											 highest_quantity);
}
 
void list_all_products_by_price_asc() {
	int size = product_count;

	/* Array of ids to pass to the sorting algorithm. */
	int ids_array[MAXPRODUCTS];

	/* Copy existing array of product ids in the system to the local array. */
	memcpy(ids_array, storage_ids, sizeof(int) * size);

	/* Sort the array */
	mergesort(ids_array, 0, size-1, compare_product_by_price_asc);

	print_products(ids_array, size);
}

void list_products_by_description(const int order_id) {
	int size = orders[order_id].num_products;

	/* Array of ids to pass to the sorting algorithm. */
	int ids_array[MAXWEIGHT];

	/* Exit if order is non exixtent. */
	if (order_id >= order_count) {
		printf("Impossivel listar encomenda %d. "
			   "Encomenda inexistente.\n", order_id);
		return;
	}

	/* Copy existing array o product ids in the order to the local array. */
	memcpy(ids_array, orders[order_id].product_ids, sizeof(int) * size);

	/* Sort the array */
	mergesort(ids_array, 0, size-1, compare_product_by_description);

	print_order_products(order_id, ids_array, size);
}

/*
 * Auxiliary Functions
 */

void print_products(int ids_array[], int size) {
	int i;
	printf("Produtos\n");
	/* Go through all sorted ids and get the info from storage */
	for (i = 0; i < size; i++) {
		printf("* %s %d %d\n", storage[ids_array[i]].description, 
							   storage[ids_array[i]].price, 
							   storage[ids_array[i]].stock);
	}
}

void print_order_products(int order_id, int ids_array[], int size) {
	int i;
	printf("Encomenda %d\n", order_id);
	/* Go through all sorted ids and get the info from storage and orders*/
	for (i = 0; i < size; i++) {
		printf("* %s %d %d\n", storage[ids_array[i]].description,
							   storage[ids_array[i]].price, 
							   orders[order_id].product_qty[ids_array[i]]);
	}
}

/* 
 * Comparators for the sorting algorithm
 */

int compare_product_by_description(const Item i1, const Item i2) {
	return (strcmp(storage[i1].description, storage[i2].description) < 0);

}

int compare_product_by_price_asc(const Item i1, const Item i2) {
	return (storage[i1].price == storage[i2].price)
				? (storage[i1].id < storage[i2].id)
				: (storage[i1].price < storage[i2].price);
}

/* 
 * Sorting Algorithm functions
 */

void merge(Item a[], int l, int m, int r, int (*comparator)(Item, Item)) { 
	int i, j, k;
	/* Auxiliary array for merging. */
	Item aux[maxN];

	/* Copy data to the auxiliary array. */
	for (i = m+1; i > l; i--) 
		aux[i-1] = a[i-1];
	for (j = m; j < r; j++)
		aux[r+m-j] = a[j+1];
	/* Sort the array */
	for (k = l; k <= r; k++)
		if (comparator(aux[j], aux[i]) || i > m)
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
}

void mergesort(Item a[], int l, int r, int (*comparator)(Item, Item)) {
	/* Medium index position. */
	int m = (r+l)/2;
	/* Check if we arrived to an array of only one element. */
	if (r <= l)
		return;
	/* Apply the algorithm to the 2 new arrays and merge them after. */
	mergesort(a, l, m, comparator);
	mergesort(a, m+1, r, comparator);
	merge(a, l, m, r, comparator);
}
