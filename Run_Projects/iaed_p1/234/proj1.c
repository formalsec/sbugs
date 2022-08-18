#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define P_MAX 10000
#define O_MAX 500
#define MAX_DESC_SIZE 62
#define	MAX_WEIGHT_ORDER 200

typedef struct {
	int idp;
	char description[MAX_DESC_SIZE];
	unsigned long price, weight, quantity;
}product;


typedef struct {
	int ide;
	product p[P_MAX];
}order;


static product x[P_MAX];
static order y[O_MAX];
static int n;
static int m[O_MAX];
static int l;
char buf[100];

void cmds();
char* process_input();
void add_product();
void add_stock();
void new_order();
void add_to_order();
void rem_stock();
void rem_from_order();
void order_cost();
void change_price();
void product_from_order();
void order_id_product();
void sort_products();
void sort_orders_products();


int main() {
	cmds();
	return 0;
}


void cmds() {
	while(fgets(buf,sizeof(buf),stdin) != NULL) {	
		switch(buf[0]) {
			case 'a':
				add_product();
				break;
			case 'q':
				add_stock();
				break;
			case 'N':
				new_order();
				break;
			case 'A':
				add_to_order();
				break;
			case 'r':
				rem_stock();
				break;
			case 'R':
				rem_from_order();
				break;
			case 'C':
				order_cost();
				break;
			case 'p':
				change_price();
				break;
	/*		case 'E':
				product_from_order();
				break;
			case 'm':
				order_id_product();
				break;
			case 'l':
				sort_products();
				break;
			case 'L':
				sort_orders_products();
				break;
	*/		case 'x':
				return;
		}
	}
}


char* process_input() {
	int buf_lenght = strlen(buf);
	char *input = malloc(buf_lenght + 2);
	char delim = ' ';
												
	char *token = strtok(buf+2, ":");
	while(token != NULL) {
		strncat(input, token, sizeof(strlen(token-2)));
		token = strtok(NULL, ":"); 
		strncat(input, &delim, 1);
	}
	input[strlen(input)-2] = 0;
	return input;
}


void add_product() {
	if (n<P_MAX) {
		sscanf(process_input(),"%s %lu %lu %lu", x[n].description, &x[n].price, &x[n].weight, &x[n].quantity);	
		x[n].idp = n;
		printf("Novo produto %d.\n", n);
		n++;
	}
}


void add_stock() {
	int idp;
	unsigned long quantity;
	sscanf(process_input(), "%d %lu", &idp, &quantity);
	
	if (idp>=n)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	else
		x[idp].quantity += quantity;
}


void new_order() {
	if (l < O_MAX) {
		y[l].ide = l;
		printf("Nova encomenda %d.\n", l);
		l++;
	}
}


void add_to_order() {
	int ide, idp, total_weight=0, i, existing=0;
	unsigned long quantity;
	sscanf(process_input(), "%d %d %lu", &ide, &idp, &quantity);

	if (ide>=l)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (idp>=n)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else if (x[idp].quantity < quantity)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	
	else {
		for (i=0; i < m[ide]; i++) {
			total_weight += ((y[ide].p[i].weight)*(y[ide].p[i].quantity));

			if (y[ide].p[i].idp == idp)
				existing = i;
		}
		total_weight += ((x[idp].weight)*(quantity));

		if (total_weight <= MAX_WEIGHT_ORDER) {
			if (existing != 0) {
				y[ide].p[existing].quantity += quantity;
				x[idp].quantity -= quantity;
			}
			else {
				y[ide].p[m[ide]].price = x[idp].price;
				y[ide].p[m[ide]].weight = x[idp].weight;
				y[ide].p[m[ide]].quantity = quantity;
				x[idp].quantity -= quantity;	     
				y[ide].p[m[ide]].idp = idp;
				m[ide]++;
			}
		}
		else
			printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	}
}


void rem_stock() {
	int idp;
	unsigned long quantity;
	sscanf(process_input(), "%d %lu", &idp, &quantity);

	if (idp>=n)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	else if (x[idp].quantity < quantity)
		printf("Impossivel remover %lu unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, idp);
	else
		x[idp].quantity -= quantity;
}


void rem_from_order() {
	int ide, idp, i, temp=-1;
	sscanf(process_input(), "%d %d", &ide, &idp);
	
	if (ide>=l)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if (idp>=n)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else {
		for(i=0; i < m[ide]; i++) {
			if(y[ide].p[i].idp == idp) {
				temp = i;
				
			}
		}
		if (temp != -1) {
			x[idp].quantity += y[ide].p[temp].quantity;
			y[ide].p[temp].quantity = 0;
			memmove(m+temp, m+temp+1, sizeof(*m) * (m[ide]-temp-1));
		}
	}
}



void order_cost() {
	int ide, i;
	unsigned long total_cost=0;
	sscanf(process_input(), "%d", &ide);

	if (ide>=l)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	else {
		for(i=0; i < m[ide]; i++) {
			total_cost += (y[ide].p[i].price * y[ide].p[i].quantity);
		}
		printf("Custo da encomenda %d %lu.\n", ide, total_cost);
	}
}


void change_price() {
	int idp;
	unsigned long price;
	sscanf(process_input(), "%d %lu", &idp, &price);

	if(idp >= n) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
	}
	else {
		x[idp].price = price;
	}
}


void product_from_order() {
	int ide, idp, i;
	sscanf(process_input(), "%d %d", &ide, &idp);

	if(ide >= l)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if (idp >= n)
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	else {
		for(i=0; i<m[ide]; i++) {
			if(y[ide].p[i].idp == idp)
				printf("%s %lu", x[idp].description, y[ide].p[i].quantity);
		}
	}
}

/*
void order_id_product() {
}


void sort_products() {
}


void sort_orders_products() {
}
*/