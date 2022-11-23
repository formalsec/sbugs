#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*maximum length of the product array*/
#define MAX_ID 10000
/*maximum weight*/
#define MAX_WEIGHT 200
/*maximum length of the order array*/
#define ORDERS 500
/*maximum length of product's description*/
#define LEN 63
/*maximum length of input*/
#define MAX_INPUT 80
/*product structure
each product has: id, description(desc), price, weight, quantity(qtd)
*/
typedef struct product
{
	int id;
	char desc[LEN];
	int *price;
	int weight;
	int qtd;
} product;
/*order structure
each product has: id, length of the products array(iter), array of products(products)
*/
typedef struct order{
	int id;
	int iter;
	product products[MAX_WEIGHT];
} order;
/*checks whether a particular product is in products
input: array of products, product id, size of the array
output: index of the given product in the array if found, else -1
*/
int in_order(product products[], int idp, int iter){
	int i;
	for (i = 0; i < iter; ++i){
		if(products[i].id==idp){
			if (idp==0 && products[i].weight==0){
				return -1;
			}
			return i;
		}
	}
	return -1;
}
/*helper function for merge_sort*/
void merge(product arr[], int l, int m, int r){ 
    int i, j, k; 
    /*temporary arrays creation*/
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    product *L = (product*)(can_fail_malloc(n1*sizeof(product)));
    product *R = (product*)(can_fail_malloc(n2*sizeof(product))); 
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1+ j]; 
    i = 0;
    j = 0;
    k = l;
    /*merging*/
    while (i < n1 && j < n2){ 
        if (*L[i].price < *R[j].price) { 
            arr[k] = L[i]; 
            i++; 
		} 
		else if(*L[i].price == *R[j].price && L[i].id < R[j].id){ /*if price is equal*/
            arr[k] = L[i]; 
            i++; 
		}
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    }
    /*copying remaining elements*/
    while (i < n1){ 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2){ 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
    /*freeing memory*/
    free(L);
    free(R);
} 
/*merge sort*/
void merge_sort(product arr[], int l, int r) { 
    if (l < r){ 
        int m = l+(r-l)/2; 
        /*sort halves*/
        merge_sort(arr, l, m); 
        merge_sort(arr, m+1, r); 
        /*calling helper function*/
        merge(arr, l, m, r); 
    } 
}
/*displays sorted elements(is used in case l)*/
void system_sort(product system[], int size){
	int i;
	/*creating a copy of the given array*/
	product *copy = (product*) can_fail_malloc(size * sizeof(product));
	for (i = 0; i < size; ++i){
		copy[i] = system[i];
	}
	/*sorting*/
	merge_sort(copy, 0, size-1);
	/*displaying*/
	printf("Produtos\n");
	for (i = 0; i < size; ++i){
		printf("* %s %d %d\n", copy[i].desc, *copy[i].price, copy[i].qtd);
	}
	/*freeing memory*/
	free(copy);
}
/*swaps two products*/
void swap(product *p1, product *p2){
	product aux = *p1;
	*p1 = *p2;
	*p2 = aux;
	return;
}
/*displays elements sorted alphabetically(is used in case L)*/
void alphabetic_sort(product products[], int size, int ide){
	int i, j;
	/*creating a copy of the given array*/
	product *copy = (product*) can_fail_malloc(size * sizeof(product));
	for (i = 0; i < size; ++i){
		copy[i] = products[i];
	}
	/*sorting*/
	for (i = 0; i < size - 1 ; i++){
		for (j = i + 1; j < size; j++){
			if (strcmp(copy[i].desc, copy[j].desc) > 0){
				swap(&copy[i], &copy[j]);
			}
		}
	}
	/*displaying*/
	printf("Encomenda %d\n", ide);
	for (i = 0; i < size; ++i){
		if(copy[i].qtd!=0) printf("* %s %d %d\n", copy[i].desc, *copy[i].price, copy[i].qtd);
	}
	/*freeing memory*/
	free(copy);
}
/*main function*/
int main(){
	/*declaring useful variables*/
	char input[MAX_INPUT]; /*input*/
	product p;
	product *system = (product*)can_fail_malloc(MAX_ID*sizeof(product)); /*products array*/
	order o;
	order *orders = (order*)can_fail_malloc(ORDERS*sizeof(order)); /*orders array*/
	int product_counter, order_counter, ide, idp, qtd, price, weight, i, product_index;
	product_counter = 0; /*current product id*/
	order_counter = 0; /*current order id*/
	/*loop to get input and execute commands, terminates when x is pressed*/
	while(1){
		fgets(input, MAX_INPUT, stdin); /*gets input*/
		/*switch checks the first letter of the input, 
		regarding to the first letter a particular case is executed.
		For parsing the remain part of the input sscanf is used*/
		switch(input[0]){
			case 'a':; /*if the first letter is 'a'*/
				/*adds new product to the system using already declared p variable
				input: <a> <description>:<price>:<weight>:<quantity>
				output: Novo produto <id>.*/
				printf("Novo produto %d.\n", product_counter); /*output*/
				p.price = (int*)can_fail_malloc(sizeof(int)); /*allocating memory*/
				/*parsing*/
				input[0] = ' ';
				for (i = 0; i < MAX_INPUT; ++i) if(input[i] == ':') input[i] = ' ';
				sscanf(input, "  %s %d %d %d", p.desc, p.price, &p.weight, &p.qtd);
				/*adding to the system, incrementing the product counter*/
				p.id = product_counter;
				system[product_counter] = p;
				product_counter++;
				break;
			case 'q':;/*if the first letter is 'q'*/
				/*adds some qtd to stock
				input: <q> <idp>:<quantity>
				output: none || error*/
				input[0] = ' ';
				sscanf(input, "  %d:%d", &idp, &qtd); /*parsing*/
				/*displaying an error if necessary*/
				if (product_counter-idp<=0) printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
				else system[idp].qtd = system[idp].qtd + qtd; /*adding the given qtd*/
				break;
			case 'r':;/*if the first letter is 'r'*/
				/*removes some qtd from stock
				input: <q> <idp>:<quantity>
				output: none || error*/
				input[0] = ' ';
				sscanf(input, "  %d:%d", &idp, &qtd); /*parsing*/
				/*displaying an error if necessary*/
				if (product_counter-idp<=0) printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
				else if(system[idp].qtd-qtd<0) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
				else system[idp].qtd = system[idp].qtd - qtd; /*removing the given qtd*/
				break;
			case 'p':;/*if the first letter is 'p'*/
				/*changes the price of a product
				input: <q> <idp>:<price>
				output: none || error*/
				input[0] = ' ';
				sscanf(input, "  %d:%d", &idp, &price); /*parsing*/
				/*displaying an error if necessary*/
				if(product_counter-idp<=0) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
				else *system[idp].price = price; /*changing the price*/
				break;
			case 'l':;/*if the first letter is 'l'*/
				/*displays sorted list of added products to the system
				input: <l>
				output: Sorted products list*/
				system_sort(system, product_counter); /*displaying the products*/
				break;
			case 'm':;/*if the first letter is 'm'*/
				/*displays which order has the most of the given product
				input: <m> <idp>
				output: Maximo produto <idp> <ide> <qtd>. || none || error*/
				input[0] = ' ';
				sscanf(input, "%d", &idp); /*parsing*/
				/*displaying an error if necessary*/
				if(product_counter - idp <= 0) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
				else{
					int orid, prid;
					qtd = -1;
					/*searching for an order*/
					for (orid = 0; orid < order_counter; ++orid){	
						o = orders[orid];
						for (prid = 0; prid < o.iter; ++prid){
							if(o.products[prid].id == idp && o.products[prid].qtd > qtd){
								qtd = o.products[prid].qtd;
								ide = o.id;
							}
						}
					}
					/*if there is an order with the product is going to be displayed, otherwise nothing will be displayed*/
					if (qtd != -1){
						product_index = in_order(orders[ide].products, idp, orders[ide].iter);
						if(orders[ide].products[product_index].qtd!=0) printf("Maximo produto %d %d %d.\n", idp, ide, qtd); /*output*/
					}
				}
				break;
			case 'N':;/*if the first letter is 'N'*/
				/* initiazes a new order
				input: <N>
				output: Nova encomenda <id>.*/
				/*initialization*/
				o.iter = 0;
				o.id = order_counter;
				orders[order_counter] = o;
				printf("Nova encomenda %d.\n", order_counter); /*output*/
				order_counter++; /*incrementing the order counter*/
				break;
			case 'A':;/*if the first letter is 'A'*/
				/* adds given quantity of given product to given order
				input: <A> <ide>:<idp>:<qtd>
				output: none || error*/
				input[0] = ' ';
				sscanf(input, "  %d:%d:%d", &ide, &idp, &qtd); /*parsing*/
				/*displaying an error if necessary*/
				if(order_counter-ide<=0){
					printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
					break;
				}
				weight = 0;
				for(i = 0; i < orders[ide].iter; ++i){weight = orders[ide].products[i].weight * orders[ide].products[i].qtd + weight;}
				if(product_counter-idp<=0) printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
				else if(system[idp].qtd-qtd<0) printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
				else if(weight+(system[idp].weight*qtd)>200) printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
				else{
					product_index = in_order(orders[ide].products, idp, orders[ide].iter); /*get index*/
					/*append to alredy existing product in the order*/
					if (product_index!=-1) orders[ide].products[product_index].qtd = orders[ide].products[product_index].qtd + qtd;
					/*add product to the order*/
					else{
						p.id = idp;
						strcpy(p.desc, system[idp].desc);
						p.price = system[idp].price;
						p.weight = system[idp].weight;
						p.qtd = qtd;
						orders[ide].products[orders[ide].iter] =  p;
						orders[ide].iter++;
					}
					system[idp].qtd = system[idp].qtd - qtd;
				}
				break;
			case 'E':;/*if the first letter is 'E'*/
				/* displays information about the given product in the given order
				input: <E> <ide>:<idp>
				output: <description> <idp> || error*/
				input[0] = ' ';
				sscanf(input, "  %d:%d", &ide, &idp); /*parsing*/
				/*displaying an error if necessary*/
				if(order_counter-ide<=0) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
				else if(product_counter - idp <= 0) printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
				else{
					product_index = in_order(orders[ide].products, idp, orders[ide].iter); /*get index*/
					if(product_index==-1) printf("%s 0.\n", system[idp].desc); /*output if the product was never added to the order*/
					else printf("%s %d.\n", orders[ide].products[product_index].desc, orders[ide].products[product_index].qtd); /*displaying the product in the order if found*/
				}
				break;
			case 'R':;/*if the first letter is 'R'*/
				/* sets the quantity of the given product in the given order to zero
				input: <R> <ide>:<idp>
				output: none|| error*/
				input[0] = ' ';
				sscanf(input, "  %d:%d", &ide, &idp); /*parsing*/
				/*displaying an error if necessary*/
				if(order_counter-ide<=0) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
				else if(product_counter-idp<=0) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
				else{
					product_index = in_order(orders[ide].products, idp, orders[ide].iter); /*get index*/
					/*if exists in the order set quantity to zero*/
					if(product_index!=-1){
						system[idp].qtd = system[idp].qtd + orders[ide].products[product_index].qtd;
						orders[ide].products[product_index].qtd = 0;
					}
				}
				break;
			case 'C':;/*if the first letter is 'C'*/
				/* calculates price for the given order
				input: <C> <ide>
				output: Custo da encomenda <ide> <price>. || error*/
				input[0] = ' ';
				sscanf(input, "%d", &ide); /*parsing*/
				/*displaying an error if necessary*/
				if(order_counter-ide<=0) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
				/*calculating price*/
				else{
					price = 0;
					for(i = 0; i < orders[ide].iter; ++i) price = orders[ide].products[i].qtd * *orders[ide].products[i].price + price;
					printf("Custo da encomenda %d %d.\n", ide, price);
				}
				break;
			case 'L':;/*if the first letter is 'L'*/
				/* displays alphabeticalally sorted list of products of the given order 
				input: <L> <ide>
				output: Alphabetically sorted list of products || error*/
				input[0] = ' ';
				sscanf(input, "  %d", &ide); /*parsing*/
				/*displaying an error if necessary*/
				if (order_counter - ide <= 0) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
				else alphabetic_sort(orders[ide].products, orders[ide].iter, ide); /*displaying sorted list of products*/
				break;
			case 'x':;/*if the first letter is 'x'*/
				return 0; /*terminates the program*/
			default:;
				break;
		}
	}
}
