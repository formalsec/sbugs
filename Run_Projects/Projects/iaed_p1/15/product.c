#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "myLib.h"
#include "product.h"

/* Cria um novo produto */
Product * product_new(const char * desc, int preco, int peso) {
	Product *p;
	extern char* strdup(const char*);
	static int next_id = 0;

	p = (Product*) malloc(sizeof(Product));
	EXIT_IF_ERROR("product_new: malloc");

	p->id        = next_id++;
	p->preco     = preco;
	p->peso      = peso;
	p->descricao = strdup(desc); 

	return p;
}

/* liberta o espaco de memoria */
void product_free(Product *p) {
	ERROR_IF_NULL(p, "product_free", exit(EXIT_FAILURE));
	free(p->descricao);
	free(p);
}

/* Obtem ido do produto */
int product_get_id(const Product *p) {
	ERROR_IF_NULL(p, "product_get_id", exit(EXIT_FAILURE));
	return p->id;
}

/* Obtem preco do produto */
int product_get_price(const Product *p) {
	ERROR_IF_NULL(p, "product_get_price", exit(EXIT_FAILURE));
	return p->preco;
}

/* Obtem peso do produto */
int product_get_weight(const Product *p) {
	ERROR_IF_NULL(p, "product_get_weight", exit(EXIT_FAILURE));
	return p->peso;
}

/* Obtem descricao do produto */
char * product_get_desc(const Product *p) {
	ERROR_IF_NULL(p, "product_get_desc", exit(EXIT_FAILURE));
	return p->descricao;
}

/* Atribui novo preco ao produto */
int product_set_price(Product *p, int new_price) {
	
	ERROR_IF_NULL(p, "product_set_price", exit(EXIT_FAILURE));

	/*new_price validacao */
	p->preco = new_price;

	return 0;
}

/* Atribuicao string a todos os argumentos que constituem um produto */
char * product_to_string(const Product *p, char * buf, int buf_size) {
	//extern int snprintf (char *__restrict __s, size_t __maxlen,__const char *__restrict __format, ...)__THROW __attribute__ ((__format__ (__printf__, 3, 4)));
	ERROR_IF_NULL(p, "product_to_string", exit(EXIT_FAILURE));
	snprintf(buf, buf_size, "Product: ID=%d P=%d W=%d %s", product_get_id(p), product_get_price(p), product_get_weight(p), product_get_desc(p));
	return buf;
}

/* Imprime uma string com a estrutura interna de produto*/
void product_print(const Product *p) {
	char buf[100];
	ERROR_IF_NULL(p, "product_print", exit(EXIT_FAILURE));
	printf("%s\n", product_to_string(p, buf, 100));
}
