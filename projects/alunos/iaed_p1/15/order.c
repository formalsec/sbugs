#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myLib.h"
#include "product.h"
#include "order.h"


/* Cria uma order (encomenda)*/
Order * order_new() {

	static int next_id = 0;

	Order * order = (Order *) can_fail_malloc(sizeof(Order));
	EXIT_IF_ERROR("order_new: criar_order");

	/* Incializacao de variaveis*/
	order->id     = next_id++;
	order->count  = 0;
	order->weight = 0;

	order->products     = NULL;
	order->last_product = NULL;

	return order;
}
  
/* Liberta espaco de memoria dos produtos que constituem uma order(encomenda) */
void order_product_free(Order_Product *op) {
	ERROR_IF_NULL(op, "order_product_free", exit(EXIT_FAILURE));
	free(op);
}

/* Liberta espaco de memoria da order(encomenda) */
void order_free(Order *o) {
	Order_Product * op;
	
	ERROR_IF_NULL(o, "order_free", exit(EXIT_FAILURE));

	/* free dos Order_Product da linkedlist */
	op = o->products;
	while( op!=NULL ) {
		Order_Product * next = op->next;
		order_product_free(op);
		op = next;
	}

	/* free do Order */
	free(o);
}

/* Obtem id da order(encomenda) */
int order_get_id(const Order *o) {
	ERROR_IF_NULL(o, "order_get_id", exit(EXIT_FAILURE));
	return o->id;
}

/* Obtem numero de orders(encomendas) */
int order_get_count(const Order *o) {
	ERROR_IF_NULL(o, "order_get_count", exit(EXIT_FAILURE));
	return o->count;
}

/* Obtem custo da order(encomenda) */
int order_get_cost(const Order *o) {
	Order_Product * op;
	int sum = 0;
	
	ERROR_IF_NULL(o, "order_get_cost", exit(EXIT_FAILURE));

	op = o->products;

	while (op!=NULL) {
		sum += (op->qtd) * (op->product->preco);
		op = op->next;
	}

	return sum;
}

/* Obtem peso da order(encomenda) */
int order_get_weight(const Order *o) {
	ERROR_IF_NULL(o, "order_get_weight", exit(EXIT_FAILURE));
	return o->weight;
}

/* Obtem produto presente na order(encomenda)*/
Order_Product * order_get_product(const Order *o, int pid) {
	Order_Product * op;
	ERROR_IF_NULL(o, "order_get_product", exit(EXIT_FAILURE));

	op = o->products;

	while (op!=NULL) {
		if (op->product->id == pid)
			return op;
		op = op->next;
	}

	return NULL;
}

/* Adiciona produto a order(encomenda) */
Order_Product * order_add_product(Order *o, const Product *p, int qtd) {
	Order_Product * op;
	int weight; 

	ERROR_IF_NULL(o, "order_add_product: Order",   exit(EXIT_FAILURE));
	ERROR_IF_NULL(p, "order_add_product: Product", exit(EXIT_FAILURE));

	/* Orders(encomendas)  nao podem pesar mais do que macro: ORDER_MAX WEIGHT */
	weight = qtd*p->peso;
	if (o->weight+weight > ORDER_MAX_WEIGHT)
		return NULL;

	/* Verifica se o produto ja existe na ordem */
	op = order_get_product(o, p->id);

	/* Se exister actualiza a quantidade */
	if (op!=NULL) {
		op->qtd+=qtd;
	}

	/* Adiciona o produto */
	else {

		/* Cria um Order_Product */
		op = (Order_Product*) can_fail_malloc(sizeof(Order_Product));
		EXIT_IF_ERROR("order_add_product: criar_order_product");

		/* Inicializa o Order_Product */
		op->product  = p;
		op->qtd      = qtd;
		op->next     = NULL;
		op->previous = o->last_product;

		/* Adciona a linkedlist */
		o->count++;

		/* Caso ja existam producto  atualiza last_product e last_product->next */
		if (o->last_product!=NULL)
			o->last_product->next = op; 
		
		o->last_product = op; /* last_product e agora este novo */

		/* Verifica se tambem e o primeiro */
		if (o->products==NULL) {
			o->products = op;
		}
	}

	/* Actualiza weight */
	o->weight += weight;

	return op;
}

/* Remove produto a order(encomenda) */
int order_remove_product(Order *o, int pid) {
	Order_Product *op;
	ERROR_IF_NULL(o, "order_remove_product", exit(EXIT_FAILURE));

	op = order_get_product(o, pid);
	if (op==NULL)
		return -1;
	
	o->count--;

	/* Actualiza weight */
	o->weight -= (op->qtd)*(op->product->peso);

	/* Se for o primerio */
	if (op->previous==NULL) {
		o->products = op->next;
	}

	/* Se for o ultimo */
	if (op->next==NULL) {
		o->last_product = op->previous;
	}

	/* Se n?o for o primeiro */
	if (op->previous!=NULL) {
		op->previous->next = op->next;
	}

	order_product_free(op);

	return 0;
}

/* Obtem a lista de produtos na order(encomenda) */
void order_list_products(const Order *o) {
	Order_Product * op ;
	const Product * p;

	ERROR_IF_NULL(o, "order_list_products", exit(EXIT_FAILURE));

	 op = o->products;

	printf("Encomenda %d\n", o->id);	
	while (op!=NULL) {
		p = op->product;
		printf("* %s %d %d\n", p->descricao, p->preco, op->qtd);
		op = op->next;
	}
}

/* Obtem lista de produtos por ordem crescente do produto que ocorre mais vezes */
void order_list_products_by_desc(const Order *o) {
	/* TODO */
	order_list_products(o);
}

/* Obtem o produto de uma order(encomenta) */
const Product * order_product_get_product(const Order_Product *op) {
	ERROR_IF_NULL(op, "order_product_get_product", exit(EXIT_FAILURE));
	return op->product;
}

/* Obtem a quantidade de um produto na encomenda */
int order_product_get_quantity(const Order_Product *op) {
	ERROR_IF_NULL(op, "order_product_get_quantity", exit(EXIT_FAILURE));
	return op->qtd;
}

/* Imprime uma string com a estrutura interna de uma Order(encomenda)*/
void order_print(const Order *o) {
	ERROR_IF_NULL(o, "order_print", exit(EXIT_FAILURE));
	printf("Order: ID=%d C=%d P=%d W=%d\n", order_get_id(o), order_get_count(o), order_get_cost(o), order_get_weight(o));
}

/* Impriem a esturtura dos produtos existentes na Order(encomenda)*/
void order_product_print(const Order_Product *op) {
	ERROR_IF_NULL(op, "order_product_print", exit(EXIT_FAILURE));
	printf("Order_Product: I=%d Q=%d\n", product_get_id(order_product_get_product(op)), order_product_get_quantity(op) );
}
