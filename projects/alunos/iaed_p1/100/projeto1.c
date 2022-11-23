#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_PRODUCT_QTY 10000
#define MAX_ORDER_QTY 500
#define MAX_ORDER_WGT 200
#define MAX_ITEM_QTY 200
#define MAX_NAME_LEN 64

/* Data structure that contains all the information about the products.      */
typedef struct {
	int p_id;
	char name[MAX_NAME_LEN];
	int price;
	int weight;
	int qty_available;
} product;

/* Data structure that represents an item in an order.                       */
typedef struct {
	int p_id;
	int qty;
} order_item;

/* Data structure that contains the necessary information about an order.    */
typedef struct {
	order_item item_list[MAX_ITEM_QTY];
	int item_list_end;
	int current_weight;
} order;


void command_a(); /* adds a new product to catalog                           */
void command_q(); /* adds stock to an existing product on catalog            */
void command_N(); /* creates a new order                                     */
void command_A(); /* adds a product to an order                              */
void command_r(); /* removes stock from an existing product                  */
void command_R(); /* removes a product from an order                         */
void command_C(); /* calculates the cost of an order                         */
void command_p(); /* changes the price of a product already on catalog       */
void command_E(); /* returns the name and qty of a product in a given order  */
void command_m(); /* returns the id of the order with the most qty of a given product */
void command_l(); /* lists all products in catalog by ascending price        */
void command_L(); /* lists all products alphabetically                       */
void add_product_catalog(product p);
void add_item_order(order_item new_item, int order_id);
void remove_product_order(int order_id, int product_id);
int order_cost(int order_id);
void update_price(int product_id, int new_price);
void print_item(int order_id, int product_id);
void print_most_item(int product_id);
int item_qty_order(int order_id, int product_id);
int index_from_pid(int p_id);
void clear_input_buffer();


/* Array of the products in the system                                       */
product catalog[MAX_PRODUCT_QTY];

/* Index of the first unused entry in catalog (which matches numbers of products) */
int catalog_end;

/* Array of the registered orders (index matches order id)                   */
order order_list[MAX_ORDER_QTY];

/* Index of the first unused entry in order_list_end (which matches numbers of orders) */
int order_list_end;


/* Receives user input and calls appropriate function.                       */
int main(){
	char command;

	do {
		command = getchar();

		switch (command) {
			case 'a': command_a(); break;
			case 'q': command_q(); break;
			case 'N': command_N(); break;
			case 'A': command_A(); break;
			case 'r': command_r(); break;
			case 'R': command_R(); break;
			case 'C': command_C(); break;
			case 'p': command_p(); break;
			case 'E': command_E(); break;
			case 'm': command_m(); break;
			case 'l': command_l(); break;
			case 'L': command_L(); break;
		}

	} while (command != 'x');

	return 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                             COMMAND FUNCTIONS                             */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* Reads input and adds a new product to the catalog                         */
/* Input format 'a name:price:weight:stock'                                  */
void command_a(){
	product p;

	scanf(" %[^:]:%d:%d:%d", p.name, &p.price, &p.weight, &p.qty_available);
	clear_input_buffer();
	p.p_id = catalog_end;

    add_product_catalog(p);
	printf("Novo produto %d.\n", p.p_id);
	return;
}


/* Reads input and adds stock to an existing product on catalog              */
/* Input format 'q idp:qtd'                                                  */
void command_q(){
	int p_id, qty;

	scanf("%d:%d", &p_id, &qty);
	clear_input_buffer();

	if (p_id >= catalog_end){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p_id);
		return;
	}
	catalog[index_from_pid(p_id)].qty_available += qty;
	return;
}


/* Creates a new order                                                       */
void command_N(){
	order o;
	o.item_list_end = o.current_weight = 0;
	clear_input_buffer();

	order_list[order_list_end] = o;
	printf("Nova encomenda %d.\n", order_list_end++);
	return;
}


/* Adds an item to an order                                                  */
/* Input format 'A ide:idp:qtd'                                              */
void command_A(){
	int order_id, product_index;
	order_item item;

	scanf("%d:%d:%d", &order_id, &item.p_id, &item.qty);
	clear_input_buffer();
	product_index = index_from_pid(item.p_id);

	if (order_id >= order_list_end){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", item.p_id, order_id);
		return;
	}
	else if (item.p_id >= catalog_end){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", item.p_id, order_id);
		return;
	}
	else if (item.qty > catalog[product_index].qty_available){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", item.p_id, order_id);
		return;
	}
	else if (order_list[order_id].current_weight + item.qty * catalog[product_index].weight > MAX_ORDER_WGT){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", item.p_id, order_id);
		return;
	}

	add_item_order(item, order_id);
	catalog[product_index].qty_available -= item.qty;
	return;
}


/* Removes stock from an existing product                                    */
/* Input format 'r idp:qtd'                                                  */
void command_r(){
	int p_id, stock_diff;
	int product_index;

	scanf("%d:%d", &p_id, &stock_diff);
	clear_input_buffer();
	product_index = index_from_pid(p_id);

	if (p_id >= catalog_end){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p_id);
		return;
	}
	else if (stock_diff > catalog[product_index].qty_available){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock_diff, p_id);
		return;
	}

	catalog[product_index].qty_available -= stock_diff;
	return;
}


/* Removes a product from an order                                           */
/* Input format 'R ide:idp'                                                  */
void command_R(){
	int order_id, product_id;

	scanf("%d:%d", &order_id, &product_id);
	clear_input_buffer();

	if (order_id >= order_list_end){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", product_id, order_id);
		return;
	}
	else if (product_id >= catalog_end){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", product_id, order_id);
		return;
	}
    remove_product_order(order_id, product_id);
	return;
}


/* Calculates the cost of an order                                           */
/* Input format 'C ide'                                                      */
void command_C() {
    int order_id;

    scanf("%d", &order_id);
    clear_input_buffer();

    if (order_id >= order_list_end) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", order_id);
        return;
    }
    printf("Custo da encomenda %d %d.\n", order_id, order_cost(order_id));
    return;
}


/* Changes the price of a product already on catalog                         */
/* Input format 'p idp:price'                                                */
void command_p(){
	int product_id, new_price;

	scanf("%d:%d", &product_id, &new_price);
	clear_input_buffer();

	if (product_id >= catalog_end){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", product_id);
		return;
	}
	update_price(product_id, new_price);
	return;
}


/* Returns the name and qty of a product in a given order                    */
/* Input format 'E ide:idp'                                                  */
void command_E(){
	int order_id, product_id;

	scanf("%d:%d", &order_id, &product_id);
	clear_input_buffer();

	if (order_id >= order_list_end){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order_id);
		return;
	}
	else if (product_id >= catalog_end){
		printf("Impossivel listar produto %d. Produto inexistente.\n", product_id);
		return;
	}
	print_item(order_id, product_id);
	return;
}


/* Returns the id of the order with the most qty of a given product          */
/* Input format 'm idp'                                                      */
void command_m(){
	int product_id;

	scanf("%d", &product_id);
	clear_input_buffer();

	if (product_id >= catalog_end){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", product_id);
		return;
	}
	else if (order_list_end == 0){
		return;
	}

	print_most_item(product_id);
	return;
}



/* Lists all products in catalog by ascending price                          */
void command_l(){
	int k;

	clear_input_buffer();
	puts("Produtos");

	for (k = 0; k < catalog_end; k++){
		printf("* %s %d %d\n", catalog[k].name, catalog[k].price, catalog[k].qty_available);
	}
	return;
}


/* Lists all products in a given order alphabetically                        */
/* Input format 'N ide'                                                      */
void command_L(){
    product current_product;
	order_item current_item;
    int order_id, k, max;

    scanf("%d", &order_id);
    clear_input_buffer();

    if (order_id >= order_list_end) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order_id);
        return;
	}

	printf("Encomenda %d\n", order_id);
	max = order_list[order_id].item_list_end;
	for (k = 0; k < max; k++){
		current_item = order_list[order_id].item_list[k];
		current_product = catalog[index_from_pid(current_item.p_id)];

		printf("* %s %d %d\n", current_product.name, current_product.price, current_item.qty);
    }
	return;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            AUXILIAR FUNCTIONS                             */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* Inserts new product in catalog respecting the ascending price order       */
void add_product_catalog(product p){
	int k;
	product temp;

	for (k = 0; k < catalog_end; k++){
		if (p.price < catalog[k].price){
			temp = catalog[k];
			catalog[k] = p;
			p = temp;
			break;
		}
	}
	/* moves rest of the array                                               */
	for (k++; k < catalog_end; k++){
		temp = catalog[k];
		catalog[k] = p;
		p = temp;
	}

	/* puts last element in the new last position                            */
	catalog[catalog_end++] = p;
	return;
}


/* Inserts item in a given order. If item already exists increases its quantity. */
void add_item_order(order_item new_item, int order_id){
    int k, current_item_pid;
	int max = order_list[order_id].item_list_end;
    order_item temp;

	order_list[order_id].current_weight += new_item.qty * catalog[index_from_pid(new_item.p_id)].weight;

	for (k = 0; k < max; k++){
		if (order_list[order_id].item_list[k].p_id == new_item.p_id){
			order_list[order_id].item_list[k].qty += new_item.qty;
			return;
		}
	}

    for (k = 0; k < max; k++){
        current_item_pid = order_list[order_id].item_list[k].p_id;

        if (strcmp(catalog[index_from_pid(new_item.p_id)].name, catalog[index_from_pid(current_item_pid)].name) < 0) {
            temp = order_list[order_id].item_list[k];
            order_list[order_id].item_list[k] = new_item;
            new_item = temp;
        }
    }
	/* puts last item in last position of the order                          */
	order_list[order_id].item_list[order_list[order_id].item_list_end++] = new_item;
	return;
}


/* Removes product from a given order                                        */
void remove_product_order(int order_id, int product_id){
    int k, qty, wgt, index_in_catalog;
	int max = order_list[order_id].item_list_end;

    for (k = 0; k < max; k++){
		if (order_list[order_id].item_list[k].p_id == product_id){
			break;
		}
	}
	/* k now holds the index of the item to be removed, or max if item not found */

	if (k == max){
		return;
	}
	
	index_in_catalog = index_from_pid(product_id);

	/* return stock to catalog                                               */
	qty = order_list[order_id].item_list[k].qty;
    catalog[index_in_catalog].qty_available += qty;

    wgt = qty * catalog[index_in_catalog].weight;
	order_list[order_id].current_weight -= wgt;

	for (; k < max - 1; k++){
		order_list[order_id].item_list[k] = order_list[order_id].item_list[k + 1];
	}
	order_list[order_id].item_list_end--;
	return;
}


/* Calculates the total cost of a given order                                */
int order_cost(int order_id){
	int k, item_price, item_qty, total = 0;
	int max = order_list[order_id].item_list_end;

	for (k = 0; k < max; k++){
		item_price = catalog[index_from_pid(order_list[order_id].item_list[k].p_id)].price;
		item_qty = order_list[order_id].item_list[k].qty;
		total += item_price * item_qty;
	}
	return total;
}


/* Changes the price of given product and reorders catalog accordingly       */
void update_price(int product_id, int new_price){
	int k, i, old_product_index = index_from_pid(product_id);
	product new, temp;

	new = catalog[old_product_index];
	new.price = new_price;

	for (k = 0; k < catalog_end; k++){
		if (new_price < catalog[k].price || (new_price == catalog[k].price && product_id < catalog[k].p_id)){
			break;
		}
	}
	/* k now holds new product index if k < old_index or (new index + 1) if k > old_index */

	if (k < old_product_index){
		for (i = k; i <= old_product_index; i++){
			temp = catalog[i];
			catalog[i] = new;
			new = temp;
		}
	}
	else if (k > old_product_index){
		for (i = k - 1; i >= old_product_index; i--){
			temp = catalog[i];
			catalog[i] = new;
			new = temp;
		}
	}
	else {
		catalog[old_product_index].price = new_price;
	}
	return;
}



/* Searches for item in given order and prints its description and quantity  */
void print_item(int order_id, int product_id){
	int k, qty, max = order_list[order_id].item_list_end;

	for (k = 0; k < max; k++){
		if (order_list[order_id].item_list[k].p_id == product_id){
			qty = order_list[order_id].item_list[k].qty;
			printf("%s %d.\n", catalog[index_from_pid(product_id)].name, qty);
			return;
		}
	}
	/* in case there is no such item in the order prints 0                   */
	printf("%s 0.\n", catalog[index_from_pid(product_id)].name);
	return;
}


/* Prints the order with the greatest qty of a given item                    */
void print_most_item(int product_id){
	int k, most_order_id, most_quantity;

	most_order_id = -1;
	most_quantity = 0;

	for (k = 0; k < order_list_end; k++){
		if (item_qty_order(k, product_id) > most_quantity){
			most_order_id = k;
			most_quantity = item_qty_order(k, product_id);
		}
	}
	/* in case no order has such product                                     */
	if (most_order_id == -1){
		return;
	}

	printf("Maximo produto %d %d %d.\n", product_id, most_order_id, most_quantity);
	return;
}


/* Returns The quantity of an item in a given order                          */
int item_qty_order(int order_id, int product_id){
	int k, max = order_list[order_id].item_list_end;

	for (k = 0; k < max; k++){
		if (order_list[order_id].item_list[k].p_id == product_id){
			return order_list[order_id].item_list[k].qty;
		}
	}
	return 0;
}


/* Searches for product in catalog and returns its index in the array        */
int index_from_pid(int p_id){
	int k;

	for (k = 0; k < catalog_end; k++){
		if (catalog[k].p_id == p_id){
			return k;
		}
	}
	return -1;
}


/* clears stdin buffer until finds \n or EOF character, removing it          */
void clear_input_buffer(){
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
	return;
}
