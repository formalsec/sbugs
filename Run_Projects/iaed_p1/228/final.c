#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ID_SZ 10000
#define DESCRIPTION_SZ 64
#define ORDER_SZ 500
#define MAX_WEIGHT 200
#define MAX 10000000
#define MAX_CMD_SZ 200


typedef struct item {
	int idp, price, weight, stock;
	char description[DESCRIPTION_SZ];
} Item;


typedef struct order {
	int ide, weight, next_pos;
	Item item_list[ID_SZ];
} Order;

/* List of all the items added to the system */
Item items_array[ID_SZ];
/* List of all the orders added to the system */
Order orders_array[ORDER_SZ];
/* Auxiliary array to implement merge sort */
Item aux_item_array[ID_SZ-1];
/* Saves the position of the last item(ID) added to items_array */
int item_pos=0;		
/* Saves the postion of the last order added to orders_array */
int orders_pos=0;
/* saves the arguments from user input command */
char args[MAX_CMD_SZ-2];
/* saves item_id and order_id to avoid code repetition in is_overweight */
int item_id_pos=0, order_id_pos=0;

int exe_command(char action);
int getItemId();
int getOrderId();
int getPrice();
int getItemWeight();
int getOrderWeight();
int getStock();
void add_item();
int add_stock();
void list_items();
void sort();
void merging();
void quicksort();
void add_order();
int item_to_order();
int is_order();
int is_item();
int is_overweight();
void item_to_order_aux();
int remove_stock();
int no_stock();
int remove_item_from_order();
int order_cost();
int list_items_in_order();
int change_price();
int list_items_desc_amount_in_order();
int most_item_occ_order();
int list_orders();



/* Reads the command from user input and interprets the command */
int get_command() {
	char command[MAX_CMD_SZ];
	int i;
	fgets(command, sizeof command, stdin);
	fflush(stdin);

	/* Given the command in the format: <action> <arguments>*, splits and saves <arguments> in an array */
	for (i = 0; i < MAX_CMD_SZ-1 && command[i] != EOF; i++) {
		if (i >= 2) {
			args[i-2] = command[i];
		}
	}
	command[i] = '\0';
	return exe_command(command[0]);
}

/* Executes the command */
int exe_command(char action) {
	char description[DESCRIPTION_SZ];
	int price, weight, amount, ide, idp;
	/* Executes an action according to the command given */
	switch(action) {
		/* Adds an item to items_array */
		case 'a':
			sscanf(args, "%[^:]:%d:%d:%d", description, &price, & weight, &amount);
			add_item(description, price, weight, amount);
			return 1;
		/* Adds stock to an existing item */
		case 'q':
			sscanf(args, "%d:%d",&idp, &amount);
			add_stock(idp, amount);
			return 1;
		/* Lists all the products in items_array sorted by increasing price order */
		case 'l':
			list_items();
			return 1;
		/* Sorts the items of a specific order in alphabetical order */
		case 'L':
			sscanf(args, "%d", &ide);
			list_items_in_order(ide);
			return 1;
		/* Adds order to orders_array */
		case 'N':
			add_order();
			return 1;
		/* Adds item to existing order */
		case 'A':
			sscanf(args, "%d:%d:%d", &ide, &idp, &amount);
			item_to_order(ide, idp, amount);
			return 1;
		/* Removes stock from item */
		case 'r':
			sscanf(args, "%d:%d", &idp, &amount);
			remove_stock(idp, amount);
			return 1;
		/* Removes item from order */
		case 'R':
			sscanf(args, "%d:%d", &ide, &idp);
			remove_item_from_order(ide, idp);
			return 1;
		/* Calculates total cost of order */
		case 'C':
			sscanf(args, "%d", &ide);
			order_cost(ide);
			return 1;
		/* Changes price of item */
		case 'p':
			sscanf(args, "%d:%d", &idp, &price);
			change_price(idp, price);
			return 1;
		/* Prints the description and amount of a product inside an order */
		case 'E':
			sscanf(args, "%d:%d", &ide, &idp);
			list_items_desc_amount_in_order(ide, idp);
			return 1;
		/* Indicates the order ID in which the requested item has the larger stock */
		case 'm':
			sscanf(args, "%d", &idp);
			most_item_occ_order(idp);
			return 1;
		/* Terminates the program */
		case 'x':
			return 0;
		default:
			fflush(stdin);
			return 1;	
	}
}


int getItemId(Item item) {
	return item.idp;
}

int getOrderId(Order order) {
	return order.ide;
}

int getPrice(Item item) {
	return item.price;
}

int getItemWeight(Item item) {
	return item.weight;
}

int getOrderWeight(Order order) {
	return order.weight;
}

int getStock(Item item) {
	return item.stock;
}

/* Adds an item to items_array */ 
void add_item(char description[DESCRIPTION_SZ], int price, int weight, int amount) {
	Item item;
	strcpy(item.description, description);
	item.idp = item_pos;
	item.price = price;
	item.weight = weight;
	item.stock = amount;
	items_array[item_pos] = item;
	printf("Novo produto %d.\n", item_pos);
	item_pos++;
}


/* Adds stock to an existing item */
int add_stock(int idp, int amount) {
	if (is_item(idp) == 0) {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
		return 1;
	}

	else {
		items_array[item_id_pos].stock += amount;
		return 0;
	}
}



/* Prints items in items_array sorted by incresing price order */
void list_items() {
	int i;
	sort(0, item_pos - 1, items_array, aux_item_array);
	printf("Produtos\n");
	for (i = 0; i < item_pos; i++) {
		printf("* %s %d %d\n", items_array[i].description, getPrice(items_array[i]), getStock(items_array[i]));
	}
}


void merging(int low, int mid, int high, Item array1[ID_SZ], Item array_aux[ID_SZ]) {
    int l1, l2, i, j;
	
	for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
		
		for (j = 0; j < item_pos; j++) {
		}

    	if (getPrice(array1[l1]) < getPrice(array1[l2])) {
        	array_aux[i] = array1[l1++];
        }
        /* If price of both elements is equal it sorts by increasing ID number */
    	else if (getPrice(array1[l1]) == getPrice(array1[l2])) {
    		if (getItemId(array1[l1]) < getItemId(array1[l2]))
				array_aux[i] = array1[l1++];
			else 
				array_aux[i] = array1[l2++];
		}
   	
      	else
        	array_aux[i] = array1[l2++];
   }
   /* Copy the remaining elements of array1, if there 
       are any */
   while(l1 <= mid)
      array_aux[i++] = array1[l1++];

   while(l2 <= high)
      array_aux[i++] = array1[l2++];

   for(i = low; i <= high; i++)
      array1[i] = array_aux[i];
}

/* Implements merge sorting */
void sort(int low, int high, Item array1[ID_SZ], Item array_aux[ID_SZ]) {
	int mid;

	if (low < high) {
   		/* Find the middle point to divide the array into two halves */
		mid = (low + high) / 2;
		/* Call merge sort for first half */
		sort(low, mid, array1, array_aux);
		/* Call merge sort for second half */
		sort(mid + 1, high, array1, array_aux);
		/* Merge the two halves sorted before */
		merging(low, mid, high, items_array, aux_item_array);
    } 
    else 
    	return;
}


/* Adds order to orders_array */
void add_order() {
	Order order;
	order.ide = orders_pos;
	order.weight = 0;
	order.next_pos = 0;
	orders_array[orders_pos] = order;
	printf("Nova encomenda %d.\n", orders_pos);
	orders_pos++;
}

/* Adds item to order at orders_array if possible */
int item_to_order(int ide, int idp, int amount) {
	/* Checks if order exists in orders_array */
	if (is_order(ide) == 0) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide); 
		return 1;
	}
	/* Checks if item exists in items_array */
	if (is_item(idp) == 0) {
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return 1;
	}
	/* Checks if given amount surpasses items stock */
	if (no_stock(idp, amount) == 1) {
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		return 1;
	}
	/* Checks if order is overweight after adding an item */
	if (is_overweight(amount) == 1) {
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
		return 1;
	}
	else {
		item_to_order_aux(idp, amount);
		return 0;
	}
}

/* Checks if order exists in orders_array and prints an error message*/
int is_order(int ide) {
	/* Iterates over all the orders in orders_array */
	int i;
	for (i = 0; i < orders_pos; i++) {
		if (ide == getOrderId(orders_array[i])) {
			order_id_pos = i;
			return 1;
		}
	}
	return 0;
}

/* Checks if item exists in array */
int is_item(int idp) {
	int i;
	/* Iterates over all the items in items_array */
	for (i = 0; i < item_pos; i++) {
		if (idp == getItemId(items_array[i])) {
			item_id_pos = i;
			return 1;
		}
	}
	return 0;
}

/* Checks if theres enough stock of a product */
int no_stock(int idp, int amount) {
	if (is_item(idp) == 1) {
		if (amount > items_array[item_id_pos].stock) {
			return 1;
		}
	}
	return 0;
}

/* Checks if order is overweight after adding an item */
int is_overweight(int amount) {
	if (getItemWeight(items_array[item_id_pos]) * amount + getOrderWeight(orders_array[order_id_pos]) > 200) {
		return 1;
	}
	return 0;	
}

/* Adds item to order at orders_array  */
void item_to_order_aux(int idp, int amount) {
	/* Saves item position in case it already exists in the order */
	int temp_item_pos=0;
	int i, is_in_order=0;
	Item temp_item;
	/* Saves orders next position to be used */
	int next_pos = orders_array[order_id_pos].next_pos;
	/* Takes amount from stock in items_array */
	items_array[item_id_pos].stock -= amount;
	/* Checks if item is already in order */
	for (i = 0; i < orders_array[order_id_pos].next_pos; i++) {
		if (idp == getItemId(orders_array[order_id_pos].item_list[i])) {
			temp_item = orders_array[order_id_pos].item_list[i];
			is_in_order = 1;
			temp_item_pos = i;
		}
	}
	/* Adds a new item to order */
	if (is_in_order == 0) {
		temp_item = items_array[item_id_pos];
		temp_item.stock = amount;
		orders_array[order_id_pos].item_list[next_pos] = temp_item;
		orders_array[order_id_pos].weight += getItemWeight(temp_item) * amount;
		orders_array[order_id_pos].next_pos++;
	}
	/* Adds amount to existing item */
	else {
		orders_array[order_id_pos].item_list[temp_item_pos].stock += amount;
		orders_array[order_id_pos].weight += getItemWeight(orders_array[order_id_pos].item_list[temp_item_pos]) * amount;
	}
}

/* Removes stock fom existing item */
int remove_stock(int idp, int amount) {
	if (is_item(idp) == 0) {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
		return 1;
	}
	if (no_stock(idp, amount) == 1) {
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", amount, idp);
		return 1;
	}
	items_array[item_id_pos].stock -= amount;
	return 0;
}


/* Removes item from order */
int remove_item_from_order(int ide, int idp) {
	int i, id, len, amount, aux_id;
	/* Checks if order id is valid */
	if (is_order(ide) == 0) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return 1;
	}
	/* Checks if item id is valid */
	if (is_item(idp) == 0) {
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return 1;
	}

	len = orders_array[order_id_pos].next_pos;
	/* Restocks items in items_array with the removed item stocks from the removed order */
	for (i = 0; i < len; i++) {
		id = getItemId(orders_array[order_id_pos].item_list[i]);
		if (id == idp) {
			aux_id = i;
			amount = orders_array[order_id_pos].item_list[i].stock;
			items_array[item_id_pos].stock += amount;
			break;
		}
	}
	
	/*Eliminates the gap in order_array[order_id_pos].item_list left by the removed order pulling the remaining orders one position behind */
	for (i = aux_id; i < orders_array[order_id_pos].next_pos - 1; i++) {
		orders_array[order_id_pos].item_list[i] = orders_array[order_id_pos].item_list[i+1];
		orders_array[order_id_pos].next_pos--;
	}
	return 0;
}


/* Calculates the cost of an order */
int order_cost(int ide) {
	int total_cost=0, amount, price, len, i;
	

	if (is_order(ide) == 0) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
		return 1;
	}

	else {
		/* Iterates over the items inside the given order */
		len = orders_array[order_id_pos].next_pos;
		for (i = 0; i < len; i++) {
			amount = getStock(orders_array[order_id_pos].item_list[i]);
			price = getPrice(orders_array[order_id_pos].item_list[i]);
			total_cost += price * amount;
		}
		printf("Custo da encomenda %d %d.\n", ide, total_cost);
		return 0;
	}
}


/* Changes an items price */
int change_price(int idp, int price) {
	int i, j, len;
	if (is_item(idp) == 0) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
		return 1;
	}

	else {
		/* If item exists change its price in items_array*/
		items_array[item_id_pos].price = price;

		/* Changes prices of items that are already in orders */
		/* Iterates over the orders */ 
		for (i = 0; i < orders_pos; i++) {
			len = orders_array[i].next_pos;
			/* Iterates over the items inside the orders */ 
			for (j = 0; j < len; j++) {
				if (idp == getItemId(orders_array[i].item_list[j])) {
					orders_array[i].item_list[j].price = price;
				}	
			}
		}
		return 0;
	}
}



/* Prints the description and amount of a product inside an order */
int list_items_desc_amount_in_order(int ide, int idp) {
	int amount, temp_item_pos, len, i;
	if (is_order(ide) == 0) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return 1;
	}

	if (is_item(idp) == 0) {
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		return 1;
	}

	/* Checks if item is already in order */
	len = orders_array[order_id_pos].next_pos;
	for (i = 0; i < len; i++) {
		if (idp == getItemId(orders_array[order_id_pos].item_list[i])) {
			temp_item_pos = i;
		}
	}

	amount = orders_array[order_id_pos].item_list[temp_item_pos].stock;
	printf("%s %d.\n", orders_array[order_id_pos].item_list[temp_item_pos].description, amount);
	return 0;
}

/* Indicates the order ID in which the requested item has the larger stock */
int most_item_occ_order(int idp) {
	int i, j, len, is_in_order=0, max_stock=0;
	/* Auxiliar array to count the stocks of the product in each order.
	Each index in the array corresponds to the order ID in orders_array*/
	int item_occ_in_order[ORDER_SZ] = {0};
	int aux_order_id;
	if (is_item(idp) == 0) {
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
		return 1;
	}
	/* Iterates over the orders */ 
	for (i = 0; i < orders_pos; i++) {
		len = orders_array[i].next_pos;
		/* Iterates over the items inside the orders */ 
		for (j = 0; j < len; j++) {
			if (idp == getItemId(orders_array[i].item_list[j])) {
				item_occ_in_order[i] += getStock(orders_array[i].item_list[j]);
				is_in_order = 1;
			}	
		}
	}
	/* Does not list any product if it doesnt exist in any order */
	if (is_in_order == 0) {
		return 1;
	}
	else {
		/* Iterates over the auxiliar array to search for the order with the most amount of the product */
		for (i = 0; i < orders_pos; i++) {
			if (max_stock < item_occ_in_order[i]) {
				max_stock = item_occ_in_order[i];
				aux_order_id = i;

			}
			/* If two orders have the same amount of the product then the one with the smallest id number will be chosen */
			else if (max_stock == item_occ_in_order[i]) {
				if (i < aux_order_id) {
					max_stock = item_occ_in_order[i];
					aux_order_id = i;
				}
			}
		}

		printf("Maximo produto %d %d %d.\n", idp, aux_order_id, max_stock);
		return 0;
	}
}


/* Sorts the items of a specific order in alphabetical order */
int list_items_in_order(int ide) {
	int amount, price, len, i;
	if (is_order(ide) == 0) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return 1;
	}

	else {
		len = orders_array[order_id_pos].next_pos;
		printf("Encomenda %d\n", ide);
		for (i = 0; i < len; i++) {
			amount = getStock(orders_array[order_id_pos].item_list[i]);
			price = getPrice(orders_array[order_id_pos].item_list[i]);
			printf("* %s %d %d\n", 
					orders_array[order_id_pos].item_list[i].description, price, amount);
		}
		return 0;
	}
}


int main() {
	int exe=get_command();
	while (exe == 1) {
		exe = get_command();
	}

	return 0;
}

