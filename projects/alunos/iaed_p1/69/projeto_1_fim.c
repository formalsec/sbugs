#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* defini??o de constantes*/
#define MAX_COMMAND 100
#define MAX_DESC 64
#define MAX_PRODUCTS 10000
#define MAX_ORDERS 500
#define MAX_ORDER_WEIGHT 200

/* associacao a uma letra*/
typedef enum {
	ADD_PRODUCT = 'a',
	ADD_STOCK = 'q',
	ADD_ORDER = 'N',
	ADD_PRODUCT_ORDER = 'A',
	SUB_STOCK_PRODUCT = 'r',
	SUB_PRODUCT_ORDER = 'R',
	CALC_ORDER = 'C',
	CHANGE_PRICE = 'p',
	RETURN_DESC_QNT = 'E',
	RETURN_ORDER = 'm',
	LIST_PRODUCT_SIST = 'l',
	LIST_PRODUCT_ORDER = 'L',
	END_PROG = 'x',
	UNKNOWN_COMMAND = '\0'

} Command;

/* Size: 80 bytes */
/* caracterizacao do produto*/
typedef struct {

	int id;
	char desc[MAX_DESC];
	int preco;
	int peso;
	int qtd;

} Product;

/* Size: 812 bytes */
/* caracterizacao da encomenda*/
typedef struct {

	int id;
	int product_count;
	int weight;
	Product* products[MAX_ORDER_WEIGHT];
	int qtds[MAX_ORDER_WEIGHT];

} Order;

char buffer[MAX_COMMAND];
Product products[MAX_PRODUCTS];
Order orders[MAX_ORDERS];
int product_count;
int order_count;
/* troca de produtos*/
void swap(Product **p1, Product **p2){
	Product *temp = *p1;
	*p1 = *p2;
	*p2 = temp;

}
/* troca de quantidades*/
void swapQtd(int *q1, int *q2){
	int temp = *q1;
	*q1 = *q2;
	*q2 = temp;

}
/* algoritmo de ordena??o para o preco*/
void sort_preco(Product* products[], int product_count){
	int i, j, min;
	for (i = 0; i < product_count - 1; i++){
		min = i;
		for (j = i + 1; j < product_count; j++)
		 	if (products[j]->preco < products[min]->preco ||
		 		(products[j]->preco == products[min]->preco && products[j]->id < products[min]->id) )
		 		min = j;
		swap(&products[min], &products[i]);
	}

}
/* algoritmo de ordena??o para a descricao*/
void sort_desc(Product* products[], int qtds[], int product_count){
	int i, j, min, cmp;
	for (i = 0; i < product_count - 1; i++){
		min = i;
		for (j = i + 1; j < product_count; j++) {
			cmp = strcmp(products[j]->desc, products[min]->desc);
		 	if (cmp < 0)
		 		min = j;
		}
		swap(&products[min], &products[i]);
		swapQtd(&qtds[min], &qtds[i]);
	}

}

int find_product(int ide, int idp) {

	int i;

	for (i = 0; i < orders[ide].product_count; i++)
		if (orders[ide].products[i]->id == idp)
			return i;

	return -1;

}
/* a: adiciona um novo produto ao sistema */
void add_product(char* desc, int preco, int peso, int qtd) {

	products[product_count].id = product_count;
	strcpy(products[product_count].desc, desc);
	products[product_count].preco = preco;
	products[product_count].peso = peso;
	products[product_count].qtd = qtd;
	printf("Novo produto %d.\n", products[product_count].id);
	product_count++;

}
/* q: adiciona stock a um produto existente no sistema*/
void add_stock(int idp, int qtd) {

	if (products[idp].id != idp){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
		return;
	}

	products[idp].qtd += qtd;

/* N: cria uma nova encomenda*/
}
void add_order() {

	orders[order_count].id = order_count;
	orders[order_count].product_count = 0;
	printf("Nova encomenda %d.\n", order_count++);

}
/* A: adiciona um produto a uma enconmenda*/
void add_product_order(int ide, int idp, int qtd) {

	int index;

	if (orders[ide].id != ide) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}

	if (products[idp].id != idp) {
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}

	if (products[idp].qtd < qtd) {
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		return;
	}

	if (orders[ide].weight + products[idp].peso * qtd > MAX_ORDER_WEIGHT) {
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
		return;
	}

	products[idp].qtd -= qtd;

	index = find_product(ide, idp);
	if (index != -1) {
		orders[ide].qtds[index] += qtd;
		orders[ide].weight += products[idp].peso * qtd;
		return;
	}

	orders[ide].products[orders[ide].product_count] = &products[idp];
	orders[ide].qtds[orders[ide].product_count] = qtd;
	orders[ide].weight += products[idp].peso * qtd;
	orders[ide].product_count++;

}
/* r: remove um produto a uma encomenda*/
void sub_stock_product(int idp, int qtd) {

	if (products[idp].id != idp){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
		return;
	}

	if (products[idp].qtd < qtd){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
		return;
	}

	products[idp].qtd -= qtd;


}
/* R: remove um produto de uma encomenda*/
void sub_product_order(int ide, int idp) {

	int index;

	if (orders[ide].id != ide) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return;
	}

	if (products[idp].id != idp){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return;
	}

	index = find_product(ide, idp);
	if (index == -1)
		return;

	products[idp].qtd += orders[ide].qtds[index];
	orders[ide].product_count--;
	orders[ide].weight -= orders[ide].products[index]->peso * orders[ide].qtds[index];
	orders[ide].products[index] = orders[ide].products[orders[ide].product_count];
	orders[ide].qtds[index] = orders[ide].qtds[orders[ide].product_count];

}
/* C: calcula o custo de uma encomenda*/
void calc_order(int ide) {

	int i;
	int total = 0;

	if (orders[ide].id != ide) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}

	for (i = 0; i < orders[ide].product_count; i++)
		total += orders[ide].products[i]->preco * orders[ide].qtds[i];

	printf("Custo da encomenda %d %d.\n", ide, total);
}
/* p: Altera o preco de um produto existente no sistema*/
void change_price(int idp, int preco) {

	if (products[idp].id != idp){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
		return;
	}
	products[idp].preco = preco;

}
/* E: retorna a descricao e a quantidade de um produto numa dada encomenda*/
void return_desc_qnt(int ide,int idp) {

	int index;

	if (orders[ide].id != ide) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}

	if (products[idp].id != idp){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		return;
	}

	index = find_product(ide, idp);
	if (index == -1)
		printf("%s 0.\n", products[idp].desc);
	else
		printf("%s %d.\n", products[idp].desc, orders[ide].qtds[index]);

}
/* m: retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/
void return_order(int idp) {

	int i, index;
	int max_ide, max_qtd = -1;

	if (products[idp].id != idp){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
		return;
	}

	for (i = 0; i < order_count; i++) {
		index = find_product(i, idp);
		if (index != -1 && orders[i].qtds[index] > max_qtd){
			max_ide = i;
			max_qtd = orders[i].qtds[index];
		}
	}

	if (max_qtd != -1)
		printf("Maximo produto %d %d %d.\n", idp, max_ide, max_qtd);

}
/* l: lista todos os produtos existentes no sistema*/
void list_product_sist() {

	int i;
	Product* sorted_products[MAX_PRODUCTS];
	for (i = 0; i < product_count; i++ )
		sorted_products[i] = &products[i];
	sort_preco(sorted_products, product_count);

	printf("Produtos\n");
	for (i = 0; i < product_count; i++)
		printf("* %s %d %d\n", sorted_products[i]->desc, sorted_products[i]->preco, sorted_products[i]->qtd);

}
/* L: lista todos os produtos de uma encomenda por ordem alfabetica da descri??o*/
void list_product_order(int ide) {

	int i;

	if (orders[ide].id != ide) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}

	sort_desc(orders[ide].products, orders[ide].qtds, orders[ide].product_count);

	printf("Encomenda %d\n", ide);
	for (i = 0; i < orders[ide].product_count; i++)
		printf("* %s %d %d\n", orders[ide].products[i]->desc, orders[ide].products[i]->preco, orders[ide].qtds[i]);

}
/* x: termina o programa*/
void end_prog() {

	exit(0);

}


void run_command(Command com, char* args) {

	char desc[64], *remaining_args;
	int preco, peso, qtd, idp, ide;

	/* Identifica o comando, faz parse dos argumentos e chama a funcao certa*/
	switch(com) {

		/* Entrada: a descricao:preco:peso:qtd*/
		case ADD_PRODUCT:
			remaining_args = strchr(args, ':');
			remaining_args[0] = '\0';
			remaining_args++;
			strcpy(desc, args);
			sscanf(remaining_args, "%d:%d:%d", &preco, &peso, &qtd);
			add_product(desc, preco, peso, qtd);
			break;

		/* Entrada: q idp:qtd*/
		case ADD_STOCK:
			sscanf(args, "%d:%d", &idp, &qtd);
			add_stock(idp, qtd);
			break;

		/* Entrada: N */
		case ADD_ORDER:
			add_order();
			break;

		/* Entrada: A ide:idp:qtd*/
		case ADD_PRODUCT_ORDER:
			sscanf(args, "%d:%d:%d", &ide, &idp, &qtd);
			add_product_order(ide, idp, qtd);
			break;

		case SUB_STOCK_PRODUCT:
			sscanf(args, "%d:%d", &idp, &qtd);
			sub_stock_product(idp, qtd);
			break;

		/* Entrada: a ide:idp*/
		case SUB_PRODUCT_ORDER:
			sscanf(args, "%d:%d", &ide, &idp);
			sub_product_order(ide, idp);
			break;

			/* Entrada:C ide*/
		case CALC_ORDER:
			sscanf(args, "%d", &ide);
			calc_order(ide);
			break;

				/* Entrada: idp:preco*/
		case CHANGE_PRICE:
			sscanf(args, "%d:%d", &idp, &preco);
			change_price(idp, preco);
			break;

				/* Entrada: ide: idp*/
		case RETURN_DESC_QNT:
			sscanf(args, "%d:%d", &ide, &idp);
			return_desc_qnt(ide, idp);
			break;

			/* Entrada: m idp*/
		case RETURN_ORDER:
			sscanf(args, "%d", &idp);
			return_order(idp);
			break;

			/* Entrada: l*/
		case LIST_PRODUCT_SIST:
			list_product_sist();
			break;

			/* Entrada: l ide*/
		case LIST_PRODUCT_ORDER:
			sscanf(args, "%d", &ide);
			list_product_order(ide);
			break;

			/* Entrada: x*/
		case END_PROG:
			end_prog();
			break;

		default:
			break;

	}

}

Command read_command(char** args) {

	if(!fgets(buffer, MAX_COMMAND, stdin))
		return UNKNOWN_COMMAND;

	*args = buffer + 2;

	return (Command)buffer[0];

}

void setup(){

	int i;

	product_count = 0;
	order_count = 0;

	for (i = 0; i < MAX_PRODUCTS; i++)
		products[i].id = -1;

	for (i = 0; i < MAX_ORDERS; i++)
		orders[i].id = -1;

}

int main () {

	char* args = NULL;

	setup();

	while (1) {

		Command com = read_command(&args);
		run_command(com, args);

	}

}
