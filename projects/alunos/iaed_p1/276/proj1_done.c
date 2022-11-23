#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Max value for the idp */ 
#define MAX 10000

/* Max value of an INT */
#define MAX_INT 32767

/* Max orders */
#define MAX_ORDER 500

/* Max legnth for the description */ 
#define MAX_STR 64

/* Max weight of the order */
#define MAX_WEIGHT 200


/* Variables for order ide and stock , idp of a product given on the input  */
int quantity, compare, id;

int counter_prod = 0, counter_order = 0;

void create_product();
void add_stock();
void create_order();
void product_to_order();
void remove_stock();
void remove_from_order();
void total_price();
void price_change();
void quantity_of_product();
void product_occurs_more();
void display_low_to_high();
void display_alphabetic_order();

void price_low_to_high();
void sort_by_name();



/* Creates a sturcture for the product*/
struct Products{

	char name[MAX_STR];
	int price;
	int weight;
	int qtd;
	int idp;
};

/* Creates a sturcture for the order*/
struct Orders{

	int ide;
	int list[MAX];
};

struct Products produto[MAX];
struct Products copy_products[MAX];

struct Orders order[MAX_ORDER];



int main(){


    /* Which command we are going to execute */
	char command;

	int i, j;

	command = getchar();

	/* Inicializes the quantity of every product in an order with value 0*/
	for (i = 0; i< MAX_ORDER; i++){

		for (j = 0; j< MAX; j++){

			order[i].list[j] = 0;

		}	
	}
	
	while (command != 'x'){

		switch (command){

		case 'a':

			create_product();

			break;

		case 'q':

			add_stock();
			
			break;

		case 'N':

			create_order();

			break;

		case 'A':

			product_to_order();

			break;

		case 'r':

			remove_stock();

			break;

		case 'R':

			remove_from_order();

			break;

		case 'C':

			total_price();

			break;

		case 'p':

			price_change();

			break;

		case 'E':

			quantity_of_product();
			
			break;

		case 'm':

			product_occurs_more();
			
			break;

		case 'l':

			display_low_to_high();

			break;

		case 'L':

			display_alphabetic_order();

			break;
			
		}
	
	command = getchar();
	
	}

	return 0;

} 

 
/* Adds a product to the system and then shows it in the output */
void create_product(){

	scanf(" %[^:]:%d:%d:%d", produto[counter_prod].name, &produto[counter_prod].price, &produto[counter_prod].weight, &produto[counter_prod].qtd);

	/* Assigns the value for each product idp which is the same as its position in the vector*/
	produto[counter_prod].idp = counter_prod;

	printf("Novo produto %d.\n", produto[counter_prod].idp);

	counter_prod+= 1;
}

/* Adds stock to a product in the system */
void add_stock(){

	scanf(" %d:%d", &compare, &quantity);

	if (compare > (counter_prod - 1)){

		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", compare);
	} 
	else{

		/* Adds a given value to a products stock in the system */
		produto[compare].qtd += quantity;
	}
}

/* Creates a new order */
void create_order(){

	printf("Nova encomenda %d.\n", counter_order);

	/* Assigns the value for each order ide which is the same as its position in the struct*/
	order[counter_order].ide = counter_order;

	counter_order+= 1;
}

/* Adds a new product to the order */ 
void product_to_order(){

	int i, sum;

	scanf(" %d:%d:%d", &compare, &id, &quantity);

	sum = 0;

		/* Calculates the weight of a given order */
		for (i = 0; i < counter_prod; i++){

			sum += produto[i].weight * order[compare].list[i];
		}


	if (compare > (counter_order - 1)){

		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id, compare);
	}
	else if (id > (counter_prod - 1)){

		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id, compare);
	}
	else if (quantity > produto[id].qtd){

		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id, compare);
	}
	else if ((sum + produto[id].weight * quantity) > MAX_WEIGHT){

			printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id, compare);
		}
	
	else{

		/* Updates the ammount of the product in ther order and the stock in the system */
		order[compare].list[id] += quantity;
		produto[id].qtd -= quantity;
	}
}

/* Removes stock from a product */
void remove_stock(){

	scanf(" %d:%d", &id, &quantity);

	if (id > (counter_prod -1)){

		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
	}
	else if ( quantity > produto[id].qtd){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, id);
	}
	else{
		/* Reduces the stock of the prodcut by a given quantity */
		produto[id].qtd -= quantity;
	}
}

/* Removes a product from an order */
void remove_from_order(){

	scanf(" %d:%d", &compare, &id);

	if ( compare > (counter_order-1)){

		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id, compare);
	}
	else if ( id > (counter_prod -1)){

		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id, compare);
	}
	else{

		/* Adds to stock the quantity of the product that was in the order */
		produto[id].qtd += order[compare].list[id];

		/* The quantity of the product in the order is updated do 0 */
		order[compare].list[id] = 0;				

	}

}

/* shows total price of an order */
void total_price(){

	int i, total;

	scanf(" %d", &compare);

	if ( compare > (counter_order - 1) ){

		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", compare);
	}
	else{

		total = 0;

		/* calculates total price of a given order */
		for (i = 0; i < counter_prod; i++){

			total+= order[compare].list[i] * produto[i].price;
		} 

		printf("Custo da encomenda %d %d.\n", compare, total);
	}

}

/*Changes the price of a product */
void price_change(){

	int change_price;

	scanf(" %d:%d", &id, &change_price);

	if (id > (counter_prod - 1)){

		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
	}
	else{

		/* The given value is now the new price of the also given product */
		produto[id].price = change_price;
	}

}

/* Shows the description and the quantity of a product*/
void quantity_of_product(){

	scanf(" %d:%d", &compare, &id);

	if ( compare > (counter_order-1)){

		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", compare);
	}
	else if ( id > (counter_prod -1)){

		printf("Impossivel listar produto %d. Produto inexistente.\n", id);
	}

	else{

		printf("%s %d.\n", produto[id].name, order[compare].list[id]);
				
	}

}

/* Lists the order ide in which the product occurs more*/
void product_occurs_more(){

	int i , max_number;

	/* Variable that saves the ide of the order in which the product occurs more */
	int max_prod;

	scanf(" %d", &id);

	if (id > (counter_prod - 1)){

		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id);

	}

	else if (counter_order != 0){

		max_number = 0;

		/* Checks if the given product is in any order */
		for ( i = 0; i < counter_order; i++ ){

			max_number += order[i].list[id];
		}

		/* If it exists in at least one order */
		if ( max_number != 0 ){

			/* then we fix the quantity of the product in the first order */
			max_number = order[0].list[id];

			max_prod = 0;

			for (i = 0; i < counter_order; i++){

				/* if the quantity of the product in the next order is higher then max_number is uptdated to that value */
				if ( order[i].list[id] > max_number ){

					max_number = order[i].list[id];

					max_prod = i;

				}
			}

			printf("Maximo produto %d %d %d.\n", id, max_prod, max_number);
		}
	}

}

/* Shows all products from the lowest to the highest price*/
void display_low_to_high(){

	int i, m;

	/* Creates a copy of all the products that exist in the system */
	memcpy(copy_products, produto, sizeof(struct Products)*MAX);

	 m = 0;

	 /* Gives the highest price of all products */
	 for (i = 0; i < MAX; i++){

	 	if (produto[i].price > m){

	 		m = produto[i].price;
	 	}
	 }

	price_low_to_high( copy_products, 0, counter_prod-1, m);

	printf("Produtos\n");

	for (i = 0; i < counter_prod; i++){

		printf("* %s %d %d\n", copy_products[i].name, copy_products[i].price, copy_products[i].qtd );
	}

}

/* Shows all products of an order in alphabetic order*/
void display_alphabetic_order(){

	int i,j;

	scanf(" %d", &compare);

	if ( compare > (counter_order-1)){

		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", compare);

	} 

	else{

		j = 0;

		/* creates a vector with only the products that exist in a given order */
		for (i = 0; i < counter_prod; i++){

			if (order[compare].list[i] != 0){

				copy_products[j] = produto[i];
				j++;
			}
		}

		sort_by_name(copy_products, 0, j-1);

		printf("Encomenda %d\n", compare);

		for (i = 0; i < j; i++){

			printf("* %s %d %d\n", copy_products[i].name, copy_products[i].price, order[compare].list[copy_products[i].idp]);
		}

	}

}

/* Sorts all products by their price from low to high */
void price_low_to_high(struct Products a[], int l, int r, int m){

	int i, j, count[MAX_INT];

	struct Products aux[MAX + 1];

	/* Inicializes every position of the counter with 0 */
	for (j = 0; j <= m; j++){

		count[j] = 0;
	}

	/* Keeps the count of the price in the index that has the value price+1 */
	for ( i = l ; i <= r; i++){

		count[a[i].price +1]++;
	}

	/* Accumulates in each element of count the previous element */
	for (j = 1; j <= m; j++){

		count[j] += count[j-1];
	}

	/* Saves the sorted values of a in the aux vector */
	for ( i = l; i <= r ; i++){

		aux[count[a[i].price]++] = a[i];
	}

	/* copies vector aux to vector a */
	for ( i = l; i <= r; i++){

		a[i] = aux[i-l];
	}

}

/* Merges two subarrays */
void merge(struct Products a[], int l, int m, int r){ 

    int i, j, k; 

    struct Products aux[MAX];
    
    /* creates the auxiliar vector */
    for ( i = m+1; i > l; i-- ){

    	aux[i-1] = a[i-1];
    }

    for ( j = m; j < r; j++ ){

    	aux[r+m-j] = a[j+1];
    }

    for ( k = l; k <= r; k++ ){

    	/* chooses which side (left or right) of the aux vector its going to pick the word from */ 
    	/* and places the word in the sorted vector a[] */
    	if (strcmp(aux[j].name, aux[i].name) < 0){

    		a[k] = aux[j--];
    	}
    	else{

    		a[k] = aux[i++];
    	}
    }

} 

/* Returns a sorted array alphabetically*/
void sort_by_name(struct Products a[], int l, int r){

	/* Find the middle to divide a[] in two halves */
	 int m = (r + l)/2;

	 if (r <= l)
	 	return;

	 /* Calls mergeSort for the fist half */
	 sort_by_name(a, l, m);

	 /* Calls mergeSort for the second half */
	 sort_by_name(a, m +1, r);

	 /* Merges the previous two halfes */
	 merge(a, l, m, r);

}