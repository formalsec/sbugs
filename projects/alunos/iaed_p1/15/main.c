#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>

#include "myLib.h"
#include "product.h"
#include "stock.h"
#include "order.h"
#include "orders.h"

#define BUFFER_SIZE 100

/*Inicializacao estruturas globais*/
Stock * stock;
Orders * orders;

void read_line(char* buf) {
	int i;
	fgets(buf, BUFFER_SIZE, stdin);
	for(i=0; i<BUFFER_SIZE && buf[i]!=0; i++) {
		if (buf[i]==':') buf[i]=' ';
	}
}

/* Adiciona um novo produto ao sistema */
void command_a() {

	char buf[BUFFER_SIZE];
	char desc[PRODUCT_MAX_DESC];
	int  preco, peso, qtd;
	Product *p;


	/* Read line: a descricao:preco:peso:qtd */
	read_line(buf);
	
	/* Parse parameters: desc, preco, peso, qtd */
	sscanf(buf, "%s %d %d %d", desc, &preco, &peso, &qtd);

	p = product_new(desc, preco, peso);
	stock_add_product(stock, p, qtd);
	printf("Novo produto %d.\n", product_get_id(p));
}

/* Adiciona stock a um produto existente no sistema */
void command_q() {

	char buf[BUFFER_SIZE];
	int  pid, qtd;
	Stock_Product *sp;

	/* Read line: q idp:qtd */
	read_line(buf);
	
	/* Parse parameters pid, qtd */
	sscanf(buf, "%d %d", &pid, &qtd);

	/*Verifica-se Error: no caso de n?o existir nenhum produto criado com esse id*/
	sp = stock_get_product(stock, pid);
	if (sp==NULL) {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", pid);
		return;
	}

	stock_product_update_quantity(sp, qtd);
}

/* Remove stock a um produto existente no sistema */
void command_r() {

	char buf[BUFFER_SIZE];
	int  pid, qtd, error;
	Stock_Product *sp;

	/* Read line: r idp:qtd */
	read_line(buf);
	
	/* Parse parameters pid, qtd */
	sscanf(buf, "%d %d", &pid, &qtd);

	/*Verifica-se Error: caso nao exista nenhum produto criado com esse id*/
	sp = stock_get_product(stock, pid);
	if (sp==NULL) {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", pid);
		return;
	}

	/*Verifica-se Error:  caso de a quantidade de stock restante apos a remo??o ser negativa */
	error = stock_product_update_quantity(sp, -qtd);
	if (error) {
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, pid);
		return;
	}
}

/* Altera o pre?o de um produto existente no sistema */
void command_p() {

	char buf[BUFFER_SIZE];
	int  pid, price;
	Stock_Product *sp;

	/* Read line: p idp:price */
	read_line(buf);
	
	/* Parse parameters pid, price */
	sscanf(buf, "%d %d", &pid, &price);

	/*Verifica-se Error: caso nao exista nenhum produto criado com esse id*/
	sp = stock_get_product(stock, pid);
	if (sp==NULL) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", pid);
		return;
	}

	product_set_price(stock_product_get_product(sp), price);
}

/* Cria uma nova ecomenda */
void command_N() {

	Order * o = order_new();
	orders_add_order(orders, o);
	printf("Nova encomenda %d.\n", order_get_id(o));
}

/* Adiciona um produto a uma encomenda. 
Se o produto j? existir na encomenda, adiciona a nova quantidade ? quantidade existente */
void command_A() {

	char buf[BUFFER_SIZE];
	int  oid, pid, qtd;
	int  error;
	Order * o;
	Stock_Product * sp;


	/* Read line: A ide:idp:qtd */
	read_line(buf);
	
	/* Parse parameters oid, pid, qtd*/
	sscanf(buf, "%d %d %d", &oid, &pid, &qtd);

	/*Verifica-se Error: caso nao exista nenhuma order(encomenda) criada com esse id*/
	o = orders_get_order(orders, oid);
	if (o==NULL) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", pid, oid);
		return;
	}

	/*verifica-se Error: caso nao exista nenhum produto criado com esse id*/
	sp = stock_get_product(stock, pid);
	if (sp==NULL) {
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", pid, oid);
		return;
	}
	
	/* Verificamos se existe disponibilidade */
	/*Error: no caso de a adicao desse produto exceder o peso maximo permitido por order(encomenda)*/
	if (order_add_product(o, sp->product, qtd)==NULL) {
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", pid, oid);
		return;
	}

	/*Error: caso de nao existir stock suficiente desse produto para satisfazer a order(encomenda)*/
	error = stock_product_reserve_quantity(sp, qtd); 
	if (error) {
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", pid, oid);
		return;
	}

}

/* Remove um produto de uma encomenda */
void command_R() {

	char buf[BUFFER_SIZE];
	int  oid, pid;
	int error;
	Order * o;
	Stock_Product * sp;

	/* Read line: R oid:idp */
	read_line(buf);
	
	/* Parse parameters oid, pid */
	sscanf(buf, "%d %d", &oid, &pid);
	

	/*Verifica-se Error: caso nao exista nenhuma order(encomenda) criada com esse id*/
	o = orders_get_order(orders, oid);
	if (o==NULL) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", pid, oid);
		return;
	}

	/*Verifica-se Error: caso nao exista nenhuma order(encomenda) criada com esse id*/
	sp = stock_get_product(stock, pid);
	if (sp==NULL) {
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", pid, oid);
		return;
	}

	error = order_remove_product(o, pid);
	if(error) {
		return;
	}
}

/* Calcula o custo de uma encomenda */
void command_C() {

	char buf[BUFFER_SIZE];
	int  oid;
	Order * o;
	int custo;

	/* Read line: C ide */
	read_line(buf);
	
	/* Parse parameters oid */
	sscanf(buf, "%d", &oid);

	/*Verifica-se Error: nao existir nenhuma encomenda criada com esse id*/
	o = orders_get_order(orders, oid);
	if (o==NULL) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", oid);
		return;
	}

	custo = order_get_cost(o);
	printf("Custo da encomenda %d %d.\n", oid, custo);
}

/* Lista a descri??o e a quantidade de um produto numa encomenda */
void command_E() {

	char buf[BUFFER_SIZE];
	int  oid, pid;
	Order * o;
	Stock_Product * sp;
	Order_Product * op;

	/* Read line: E ide:idp */
	read_line(buf);
	
	/* Parse parameters oid, pid */
	sscanf(buf, "%d %d", &oid, &pid);


	/*Verifica-se Error: caso de nao existir nenhuma encomenda criada com esse id*/
	o = orders_get_order(orders, oid);
	if (o==NULL) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", oid);
		return;
	}

	/*Verifica-se Error: caso de nao existir nenhum produto com esse id*/
	sp = stock_get_product(stock, pid);
	if (sp==NULL) {
		printf("Impossivel listar produto %d. Produto inexistente.\n", pid);
		return;
	}

	op = order_get_product(o, pid);
	printf("%s %d.\n", product_get_desc(sp->product), order_product_get_quantity(op));
}

/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes */
void command_m() {
	char buf[BUFFER_SIZE];
	int  pid;
	Stock_Product * sp;


	/* Read line: m idp */
	read_line(buf);
	
	/* Parse parameters pid */
	sscanf(buf, "%d", &pid);


	/*Verifica-se Error: caso de nao existir nenhum produto com esse id*/
	sp = stock_get_product(stock, pid);
	if (sp==NULL) {
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", pid);
		return;
	}
}

/* Lista todos os produtos existentes no sistema por ordem crescente de pre?o */
void command_l(char command) {
	if (command=='l')
		stock_list_products_by_price(stock);
	else {
		stock_print(stock);
		stock_list_products(stock);
	}
}

/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void command_L(char command) {
	char buf[BUFFER_SIZE];
	int  oid;
	Order * o;

	/* Read line: L ide */
	read_line(buf);
	
	/* Parse parameters oid */
	sscanf(buf, "%d", &oid);

	/*Verifica-se Error: caso de nao existir nenhuma order(encomenda) com esse id*/
	o = orders_get_order(orders, oid);
	if (o==NULL) {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", oid);
		return;
	}
	
	if (command=='L')
		order_list_products_by_desc(o);
	else {
		order_print(o);
		order_list_products(o);
	}
}

int main() {
	char command;
	stock  = stock_init();
	orders = orders_init();

	do {
		command=getchar();
		switch(command)
		{
			case 'a': /* A diciona um novo produto ao sistema */
				command_a();
				break;
            
			case 'q': /* Adiciona stock a um produto existente no sistema */
				command_q();
                break;
            
			case 'N': /* Cria uma nova ecomenda */
				command_N();
                break;
            
			case 'A': /* Adiciona um produto a uma encomenda. */
				command_A();
                break;

            case 'r': /* Remove stock de um produto existente */
				command_r();
                break;
            
			case 'R': /* Remove um produto de uma encomenda */
				command_R();
                break;
			
			case 'p': /* Altera o pre?o de um produto existente no sistema */
				command_p();
				break;
			
			case 'E': /* lista a descri??o e a quantidade de um produto numa encomenda */
				command_E();
				break;

			case 'm': /* lista o identificador da encomenda em que o produto dado ocorre mais vezes */
				command_m();
				break;

			case 'l': /* lista todos os produtos existentes no sistema por ordem crescente de pre?o */
			case 'k':
				command_l(command);
				break;

			case 'L': /* lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
			case 'K':
				command_L(command);
				break;

			case 'C': /* Calcula o custo de uma encomenda */
				command_C();
				break;

			case 'x': break;
		}

	} while(command!='x');


	return EXIT_SUCCESS;
}
