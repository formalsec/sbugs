#ifndef PRODUCT_H_
#define PRODUCT_H_

/* Tamanho maximo da descricao do produto */
#define PRODUCT_MAX_DESC 63

typedef struct s_product {
	int  id;            /* actualizado pelo stock */
    int  preco;
    int  peso;
	char *descricao;
} Product;


Product * product_new       (const char * desc, int preco, int peso);
void      product_free      (Product *p);

char * product_to_string    (const Product *p, char * buf, int buf_size);
void   product_print        (const Product *p);

int product_get_id          (const Product *p);
int product_get_price       (const Product *p);
int product_get_weight      (const Product *p);
char * product_get_desc     (const Product *p);

int product_set_price       (Product *p, int new_price);

#endif
