#include <stdio.h>
#include <string.h>
#define MAX_PRODS 9999                                                    /* maximum number of products stored */
#define MAX_INPUT 100                                                     /* maximum length for an instruction */
#define MAX_DESCR 63                                                      /* maximum length for product description */
#define MAX_ORDERS 500                                                    /* maximum number of orders */
#define MAX_WEIGHT 200                                                    /* maximum weight per order */
#define MAX_INT 2147483647                                                /* maximum value for type int */
#define LAST_DESCR "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"   /* last description possible */


/* new type: Product, with the essential elements to define it */
typedef struct{
	char description[MAX_DESCR];
	int price_or_id;                                                      /* price_or_id stores the price when a product is added, 
																	      but when used inside orders stores the product id */  
	int weight;
	int stock;
} Product;

/* new type: Order, with the essential elements to define it */
typedef struct{
	Product products[MAX_WEIGHT];                                         /* minimum weight per product == 1, maximum weight per 
																	      order == 200 -> maximum # products per order == 200 */
	int total_weight;                                                     /* total weight in an order */
	int counter;                                                          /* number of different products in an order */
} Order;

/* new type: Instruction, evaluates the next value in an instruction and stores its length */
typedef struct{
	int temp_int;
	int temp_counter;
} Instruction;


Instruction instruction_reader(char input[MAX_INPUT], int i);

Product new_product(char input[MAX_INPUT]);

void list_simple(Product products[MAX_PRODS], int id);

void restock(char input[MAX_INPUT], Product products[MAX_PRODS], int id); 

void order_update(char input[MAX_INPUT], Order orders[MAX_ORDERS], Product products[MAX_PRODS], int order_id, int id);             

void list_order_simple(char input[MAX_INPUT], Order orders[MAX_ORDERS], Product products[MAX_PRODS], int order_id);

void remove_stock(char input[MAX_INPUT], Product products[MAX_PRODS], int id);

void remove_product_order(char input[MAX_INPUT], Product products[MAX_PRODS], Order orders[MAX_ORDERS], int order_id, int id);

void cost_of_order(char input[MAX_INPUT], Product products[MAX_PRODS], Order orders[MAX_ORDERS], int order_id);

void change_price(char input[MAX_INPUT], Product products[MAX_PRODS], int id);

void what_product(char input[MAX_INPUT], Product products[MAX_PRODS], Order orders[MAX_ORDERS], int order_id, int id);

void which_order(char input[MAX_INPUT], Order orders[MAX_ORDERS], int order_id, int id);

void list_by_price(Product products[MAX_PRODS], int id);

void list_by_name(char input[MAX_INPUT], Order orders[MAX_ORDERS], Product products[MAX_PRODS], int order_id);

int is_product_in_order(int temp_order_id, int temp_product_id, Order orders[MAX_ORDERS]);

void mergesort(Product products[MAX_PRODS], int left, int right);

void merge(Product products[MAX_PRODS], int left, int m, int right);


/* main: reads instructions from the standard input and calls the appropriate auxiliary function to execute what's asked */
int main(){
	char input[MAX_INPUT];                                                /* array for the instructions read */
	Product products[MAX_PRODS];                                          /* array for storage of products in the system */
	Order orders[MAX_ORDERS];                                             /* array for storage of active orders */
	int id = 0;                                                           /* id for the next product to be added */
	int order_id = 0;                                                     /* id for the next order */
	
	do{                                                                   /* cycle that awaits a new instruction */                                                                   
		fgets(input, MAX_INPUT, stdin);
		switch(input[0]){                                                 /* evaluates the first char of the instruction */
			case('a'):                                                    /* adds a new product to the system */
				products[id] = new_product(input);
				printf("Novo produto %d.\n", id);                         /* instruction successfully executed */
				id++;
				break;
			
			case('k'):                                                    /* lists the products in the system by order of insertion */
				list_simple(products, id);
				break;
				
			case('q'):                                                    /* adds stock to a product in the system */
				restock(input, products, id);
				break;
				
			case('N'):                                                    /* creates a new order */
				printf("Nova encomenda %d.\n", order_id);                 /* instruction successfully executed */
				orders[order_id].counter = 0;                             /* initializes the counter for the new order */
				order_id++;
				break;
				
			case('A'):                                                    /* adds a product to an order */
				order_update(input, orders, products, order_id, id);
				break;
				
			case('K'):                                                    /* lists the products in a given order */
				list_order_simple(input, orders, products, order_id);
				break;
				
			case('r'):                                                    /* removes stock from a product */
				remove_stock(input, products, id);
				break;
				
			case('R'):                                                    /* removes a product from an order */
				remove_product_order(input, products, orders, order_id, id);
				break;
				
			case('C'):                                                    /* calculates the final cost of an order */
				cost_of_order(input, products, orders, order_id);
				break;
				
			case('p'):                                                    /* changes the price of a product */
				change_price(input, products, id);
				break;
				
			case('E'):                                                    /* description and stock of a product in a given order */
				what_product(input, products, orders, order_id, id);
				break;
				
			case('m'):                                                    /* order in which a product has more stock */
				which_order(input, orders, order_id, id);
				break;

			case('l'):                                                    /* list the products by price */
				list_by_price(products, id);
				break;

			case('L'):                                                    /* lists the products in a given order by description */
				 list_by_name(input, orders, products, order_id);
				break;
				
		}
	} while (input[0] != 'x');                                            /* terminates the program */
	
	return 0;
}


/* instruction_reader: returns the next value in an instruction */
Instruction instruction_reader(char input[MAX_INPUT], int i){
	Instruction reader;
	reader.temp_int = 0;
	while(input[i] != ':' && input[i] != '\n'){
		reader.temp_int = reader.temp_int*10 + input[i] - '0';
		i++;
	}
	reader.temp_counter = i;
	return reader;
}

/* new_product: adds a new product to the system and inserts it into the vector products */
Product new_product(char input[MAX_INPUT]){
	Instruction reader;                                                   /* to temporary store values from the instruction */
	Product temp;
	int i = 2;                                                            /* rest of the instruction starts after initial char
																		  and empty space */
	int j = 0;

	while(input[i] != ':'){                                               /* description of the new product */
		temp.description[j] = input[i];
		i++;
		j++;
	}
	temp.description[j] = '\0';                                           /* adds the end of string character */
	
	i ++;
	reader = instruction_reader(input, i);                                /* price of the new product */
	temp.price_or_id = reader.temp_int;
	i = reader.temp_counter + 1;

	reader = instruction_reader(input, i);                                /* weight of the new product */
	temp.weight = reader.temp_int;
	i = reader.temp_counter + 1;
	
	reader = instruction_reader(input, i);                                /* stock of the new product */
	temp.stock = reader.temp_int;
	
	return temp;
	
}


/* list_simple: lists the products in the system by order of insertion */
void list_simple(Product products[MAX_PRODS], int id){
	int i = 0;
	printf("Produtos\n");
	while(i < id){
		printf("* %s %d %d\n", products[i].description, products[i].price_or_id, products[i].stock);
		i++;
	}
	
}


/* restock: adds stock to a product in the system */
void restock(char input[MAX_INPUT], Product products[MAX_PRODS], int id){
	Instruction reader;
	int temp_product_id = 0;
	int temp_amount = 0;
	int i = 2;
	
	reader = instruction_reader(input, i);                                /* which product */
	temp_product_id = reader.temp_int;
	
	if(temp_product_id < id){
		i = reader.temp_counter + 1;
		reader = instruction_reader(input, i);                            /* how much */
		temp_amount = reader.temp_int;
		products[temp_product_id].stock += temp_amount;
	}
	
	else{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", temp_product_id);
	}
}


/* order_update: adds a product to an order */
void order_update(char input[MAX_INPUT], Order orders[MAX_ORDERS], Product products[MAX_PRODS], int order_id, int id){
	Instruction reader;
	int temp_order_id = 0;
	int temp_product_id = 0;
	int temp_amount = 0;
	int already_in_order = -1;                                            /* if -1, product not in order; otherwise, index in order */
	int i = 2;

	reader = instruction_reader(input, i);                                /* which order */
	temp_order_id = reader.temp_int;
	i = reader.temp_counter + 1;

	reader = instruction_reader(input, i);                                /* which product */
	temp_product_id = reader.temp_int;
	i = reader.temp_counter + 1;

	reader = instruction_reader(input, i);                                /* how much */
	temp_amount = reader.temp_int;

	if (temp_order_id >= order_id){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", temp_product_id, temp_order_id);
	}

	else if (temp_product_id >= id){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", temp_product_id, temp_order_id);
	}
	
	else if (temp_amount > products[temp_product_id].stock){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", temp_product_id, 
			temp_order_id);
	}
	
	else if ((products[temp_product_id].weight * temp_amount + orders[temp_order_id].total_weight) > MAX_WEIGHT){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", temp_product_id, 
			temp_order_id);
	}
	
	else{
		already_in_order = is_product_in_order(temp_order_id, temp_product_id, orders);
		if(already_in_order != -1){
			orders[temp_order_id].products[already_in_order].stock += temp_amount;
			products[temp_product_id].stock -= temp_amount;
			orders[temp_order_id].total_weight += products[temp_product_id].weight * temp_amount;
		}

		else{
			strcpy(orders[temp_order_id].products[orders[temp_order_id].counter].description, products[temp_product_id].description);
			orders[temp_order_id].products[orders[temp_order_id].counter].price_or_id = temp_product_id;
			orders[temp_order_id].products[orders[temp_order_id].counter].stock = temp_amount;
			products[temp_product_id].stock -= temp_amount;
			orders[temp_order_id].total_weight += products[temp_product_id].weight * temp_amount;
			orders[temp_order_id].counter++;  
		}
	}
}


/* list_order_simple: lists the products in a given order */
void list_order_simple(char input[MAX_INPUT], Order orders[MAX_ORDERS], Product products[MAX_PRODS], int order_id){
	Instruction reader;
	int temp_order_id = 0;
	int i = 2;

	reader = instruction_reader(input, i);                                /* which product */
	temp_order_id = reader.temp_int;
	
	if(temp_order_id >= order_id){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", temp_order_id);
	}
	
	else{
		i = 0;
		printf("Encomenda %d\n", temp_order_id);
		while(i < orders[temp_order_id].counter){
			printf("* %s %d %d\n", orders[temp_order_id].products[i].description, 
				products[orders[temp_order_id].products[i].price_or_id].price_or_id, orders[temp_order_id].products[i].stock);
			i++;
		}
	}
}


/* remove_stock: removes stock from a product */
void remove_stock(char input[MAX_INPUT], Product products[MAX_PRODS], int id){
	Instruction reader;
	int temp_product_id = 0;
	int temp_amount = 0;
	int i = 2;

	reader = instruction_reader(input, i);                                /* which product */
	temp_product_id = reader.temp_int;
	i = reader.temp_counter + 1;

	reader = instruction_reader(input, i);                                /* how much */
	temp_amount = reader.temp_int;

	if (temp_product_id >= id){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", temp_product_id);
	}
	
	else if (temp_amount > products[temp_product_id].stock){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", temp_amount, temp_product_id);
	}
	
	else{
		products[temp_product_id].stock -= temp_amount;  
	}
}


/* remove_product_order: removes a product from an order */
void remove_product_order(char input[MAX_INPUT], Product products[MAX_PRODS], Order orders[MAX_ORDERS], int order_id, int id){
	Instruction reader;
	int temp_order_id = 0;
	int temp_product_id = 0;
	int product_in_order = -1;                                            /* index of the product in the order */
	int i = 2;
	
	reader = instruction_reader(input, i);                                /* which order */
	temp_order_id = reader.temp_int;
	i = reader.temp_counter + 1;

	reader = instruction_reader(input, i);                                /* which product */
	temp_product_id = reader.temp_int;
	
	if (temp_order_id >= order_id){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", temp_product_id, temp_order_id);
	}
	
	else if (temp_product_id >= id){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", temp_product_id, temp_order_id);
	}
	
	else{
		product_in_order = is_product_in_order(temp_order_id, temp_product_id, orders);
		
		if(product_in_order >= 0){                                        /* overwrites the product */
			products[temp_product_id].stock += orders[temp_order_id].products[product_in_order].stock;
			orders[temp_order_id].total_weight -= products[temp_product_id].weight * 
				orders[temp_order_id].products[product_in_order].stock;
			if(orders[temp_order_id].total_weight < 0) orders[temp_order_id].total_weight = 0;
			orders[temp_order_id].products[product_in_order].stock = 0;
			strcpy(orders[temp_order_id].products[product_in_order].description, 
				orders[temp_order_id].products[orders[temp_order_id].counter-1].description);
			orders[temp_order_id].products[product_in_order].price_or_id = 
				orders[temp_order_id].products[orders[temp_order_id].counter-1].price_or_id;
			orders[temp_order_id].products[product_in_order].stock = 
				orders[temp_order_id].products[orders[temp_order_id].counter-1].stock;
			orders[temp_order_id].counter--;
		}
	}	
}


/* cost_of_order: calculates the final cost of an order */
void cost_of_order(char input[MAX_INPUT], Product products[MAX_PRODS], Order orders[MAX_ORDERS], int order_id){
	Instruction reader;
	int temp_order_id = 0;
	int temp_cost = 0;
	int i = 2;

	reader = instruction_reader(input, i);                                /* which order */
	temp_order_id = reader.temp_int;

	if (temp_order_id >= order_id){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", temp_order_id);
	}
		
	else{
		i = 0;
		while(i < orders[temp_order_id].counter){
			temp_cost += products[orders[temp_order_id].products[i].price_or_id].price_or_id * 
			orders[temp_order_id].products[i].stock;
			i++;
		}
		printf("Custo da encomenda %d %d.\n", temp_order_id, temp_cost);
	}
}


/* change_price: changes the price of a product */
void change_price(char input[MAX_INPUT], Product products[MAX_PRODS], int id){
	Instruction reader;
	int temp_product_id = 0;
	int temp_price = 0;
	int i = 2;
	
	reader = instruction_reader(input, i);                                /* which product */
	temp_product_id = reader.temp_int;
	i = reader.temp_counter + 1;

	reader = instruction_reader(input, i);                                /* new price */
	temp_price  = reader.temp_int;

	if(temp_product_id >= id){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", temp_product_id);
	}

	else{
		products[temp_product_id].price_or_id = temp_price;
	}
}


/* what_product: description and stock of a product in a given order */
void what_product(char input[MAX_INPUT], Product products[MAX_PRODS], Order orders[MAX_ORDERS], int order_id, int id){
	Instruction reader;
	int temp_product_id = 0;
	int temp_order_id = 0;
	int product_in_order = -1;                                            /* index of the product in the order */
	int i = 2;
	
	reader = instruction_reader(input, i);                                /* which product */
	temp_order_id = reader.temp_int;
	i = reader.temp_counter + 1;

	reader = instruction_reader(input, i);                                /* new price */
	temp_product_id = reader.temp_int;
		
	if(temp_order_id >= order_id){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", temp_order_id);
	}
		
	else if(temp_product_id >= id){
		printf("Impossivel listar produto %d. Produto inexistente.\n", temp_product_id);
	}
		
	else{
		product_in_order = is_product_in_order(temp_order_id, temp_product_id, orders);
		
		if(product_in_order >= 0) printf("%s %d.\n", products[temp_product_id].description, 
			orders[temp_order_id].products[product_in_order].stock);

		else printf("%s 0.\n", products[temp_product_id].description);
	}
}


/* which_order: order in which a product has more stock */
void which_order(char input[MAX_INPUT], Order orders[MAX_ORDERS], int order_id, int id){
	Instruction reader;
	int temp_product_id = 0;
	int temp_order_id = 0;
	int temp_stock = 0;
	int j, i = 2;
	
	reader = instruction_reader(input, i);                                /* which product */
	temp_product_id = reader.temp_int;
	
	if(temp_product_id >= id){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", temp_product_id);
	}
	
	else{
		i = 0;
		while(i < order_id){
			j = 0;
			while(j < orders[i].counter){
				if(orders[i].products[j].price_or_id == temp_product_id){ /* if the product is in the order ... */
					if(orders[i].products[j].stock > temp_stock){
						temp_stock = orders[i].products[j].stock;         /* ... whats the stock */
						temp_order_id = i;
					}
				}
				j++;
			}
		i++;
		}
		if(temp_stock > 0){
			printf("Maximo produto %d %d %d.\n", temp_product_id, temp_order_id, temp_stock);
		}
	}
}


/* list_by_price: lists the products in the system by price */
void list_by_price(Product products[MAX_PRODS], int id){
	Product temp_products[MAX_PRODS];                                     /* array for temporary storage of products */
	int i;

	for(i = 0; i < id; i++){
		temp_products[i] = products[i];
	}

	mergesort(temp_products, 0, id-1);                                    /* sorts the products in the temporary array by price */
	printf("Produtos\n");
	for(i = 0; i < id; i++){
        printf("* %s %d %d\n", temp_products[i].description, temp_products[i].price_or_id, temp_products[i].stock);
    }
}


/* list_by_name: lists the products in a given order by description */
void list_by_name(char input[MAX_INPUT], Order orders[MAX_ORDERS], Product products[MAX_PRODS], int order_id){
	Instruction reader;
	int temp_order_id = 0;
	char min_description_this_cycle[MAX_DESCR];                           /* value for comparation */
	int min_position;                                                     /* index of the product to be printed in the order */
	int already_printed[MAX_WEIGHT] = {0};                                /* False || True */
	int j, k, i = 2;                                                      /* j for products, k for letters */
	Product min_name_prod;                                                /* product to be printed */

	reader = instruction_reader(input, i);                                /* which order */
	temp_order_id = reader.temp_int;
	
	if(temp_order_id >= order_id){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", temp_order_id);
	}
	
	else{
		printf("Encomenda %d\n", temp_order_id);
		for(i = 0; i < orders[temp_order_id].counter; i++){
			strcpy(min_description_this_cycle, LAST_DESCR);
		 	for(j = 0; j < orders[temp_order_id].counter; j++){
		 		if(!already_printed[j]){
		 			for(k = 0; k < MAX_DESCR; k++){
		 				if(orders[temp_order_id].products[j].description[k] < min_description_this_cycle[k]){
		 					strcpy(min_description_this_cycle, orders[temp_order_id].products[j].description);
		 					min_name_prod = orders[temp_order_id].products[j];
		 					min_position = j;
		 				}
		 				else if(orders[temp_order_id].products[j].description[k] > min_description_this_cycle[k]){
		 					break;
		 				}
		 			}
		 		}
			}
		already_printed[min_position] = 1;
		printf("* %s %d %d\n", min_name_prod.description, products[min_name_prod.price_or_id].price_or_id, min_name_prod.stock);
		}
	}
}


/* is_product_in_order: checks if a product is in a given order */
int is_product_in_order(int temp_order_id, int temp_product_id, Order orders[MAX_ORDERS]){
int i = 0;
		while(i < orders[temp_order_id].counter){
			if(orders[temp_order_id].products[i].price_or_id == temp_product_id){
				return i;                                                 /* index of the product in the order */
			}
			else i++;
		}
		return -1;                                                        /* product not in the order */
}


/* mergesort: divides the array into single-element arrays and sorts the products by price */
void mergesort(Product products[MAX_PRODS], int left, int right){
	int m = (right + left)/2;
	if(right <= left) return;
	mergesort(products, left, m);
	mergesort(products, m+1, right);
	merge(products, left, m, right);
}


/* merge: organizes the sub-arrays by price and merges them back together */
void merge(Product products[MAX_PRODS], int left, int m, int right){
	Product aux[MAX_PRODS];
	int i, j, k;
	for (i = m+1; i > left; i--)
		aux[i-1] = products[i-1];
	for (j = m; j < right; j++)
		aux[right+m-j] = products[j+1];
	for (k = left; k <= right; k++)
		if ((aux[j].price_or_id < aux[i].price_or_id) || i > m)
			products[k] = aux[j--];
		else
			products[k] = aux[i++];
}