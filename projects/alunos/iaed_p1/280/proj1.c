#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* maximum size for a product description */
#define LIM_DESC 63
/* maximum number of products */
#define LIM_PRODS 10000
/* maximum input size */
#define LIM_INPUT 300
/* maximum number of orders */
#define LIM_ENCOMENDAS 500

/* variable that tracks the number of product id's */
int id_prod = 0;
/* variable that tracks the number of orders id's */
int id_encomenda = 0;
/* variable that tracks the number of orders */
int n_de_encomendas = 0;
/* variable that takes in user input in order to make commands */
char comando[LIM_INPUT];

typedef struct produto{
	char descricao [LIM_DESC];
	int preco;
	int peso;
	int stock;
	int idp;
}Produto;

typedef struct encomenda{
	Produto prods[LIM_PRODS];
	int ide;
	int n_de_produtos;
}Encomenda;

/* variable to store the products */
Produto produtos [LIM_PRODS];
/* variable to store the orders */
Encomenda encomendas [LIM_ENCOMENDAS];

/* auxiliar function that calculates an order's weight */
int peso_da_encomenda(int id_enc, int num_de_prods){
	int peso_encomenda = 0, b;

	for (b=0; b < num_de_prods; b++){
		peso_encomenda += encomendas[id_enc].prods[b].peso * encomendas[id_enc].prods[b].stock;
	}

	return peso_encomenda;
}

/* function that creates new products and stores them */
int a(){
	Produto a;
	int i=2, k=0, n=0, p=0, j=0;
    char preco_prod[LIM_INPUT], peso_prod[LIM_INPUT], stock_prod[LIM_INPUT];

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
 		a.descricao[k] = comando[i];
 		k += 1;
 	}
 	i+=1;
 	a.descricao[k] = '\0';
 	

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
 		preco_prod[n] = comando[i];
 		n += 1;
 	}
 	i+=1;
 	preco_prod[n] = '\0';
	a.preco = atoi(preco_prod);

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
 		peso_prod[p] = comando[i];
 		p += 1;
 	}
 	i+=1;
 	peso_prod[p] = '\0';
	a.peso = atoi(peso_prod);

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
 		stock_prod[j] = comando[i];
 		j += 1;
 	}
 	stock_prod[j] = '\0';
	a.stock = atoi(stock_prod);

	a.idp = id_prod;
	produtos[id_prod] = a;
    printf("Novo produto %d.\n", a.idp);
    id_prod += 1;

	return 0;
	}
 
 /* function that adds stock to a certain product */
 int q(){
 	int i=2, k=0, n=0, iden, st;
    char id[LIM_INPUT], stk[LIM_INPUT];
 	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
 		id[k] = comando[i];
 		k += 1;
 	}
 	i+=1;
 	id[k] = '\0';
 	iden = atoi(id);

 	if (iden > id_prod-1){
 		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", iden);
 		return 0;
 	}
 	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
 		stk[n] = comando[i];
 		n += 1;
 	}
 	stk[n] = '\0';
 	st = atoi(stk);

 	produtos[iden].stock += st;

 	return 0;
 }

/* function that creates new orders and stores them */
int N(){
	Encomenda a;
	a.ide = id_encomenda;
    encomendas[id_encomenda] = a;
    a.n_de_produtos = 0;
    printf("Nova encomenda %d.\n", a.ide);
    id_encomenda += 1;
    n_de_encomendas+=1;

	return 0;
}

/* function that adds products to an order if there is enough stock */
int A(){
	int i=2, k=0, n=0, p=0, a=0, id_enc, id_pr, qtd, peso_encomenda = 0;
	char encom[LIM_INPUT], prod[LIM_INPUT], quantidade[LIM_INPUT];

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		encom[k]= comando[i];
		k+=1;
	}
	i+=1;
	encom[k]= '\0';
	id_enc = atoi(encom);
	
	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		prod[n]= comando[i];
		n+=1;
	}
	i+=1;
	prod[n] = '\0';
	id_pr= atoi(prod);

	if (id_enc >= n_de_encomendas){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_pr, id_enc);
		return 0; 
	}
	if (id_pr >= id_prod){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_pr, id_enc);
		return 0;
	}
	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		quantidade[p]= comando[i];
		p+=1;
	}
	quantidade[p] = '\0';
	qtd= atoi(quantidade);

	if (qtd > produtos[id_pr].stock){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_pr, id_enc);
		return 0; 
	}

	peso_encomenda = peso_da_encomenda(id_enc, encomendas[id_enc].n_de_produtos);
	peso_encomenda += produtos[id_pr].peso * qtd;
    
	if ( peso_encomenda > 200){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_pr, id_enc);
		return 0;
	}

    for (; a < encomendas[id_enc].n_de_produtos ; a++){
    	if (encomendas[id_enc].prods[a].idp == id_pr){
    		encomendas[id_enc].prods[a].stock += qtd;
    		produtos[id_pr].stock = produtos[id_pr].stock - qtd;
    		return 0;
    	}
    }

    encomendas[id_enc].prods[encomendas[id_enc].n_de_produtos]= produtos[id_pr];
    encomendas[id_enc].prods[encomendas[id_enc].n_de_produtos].stock = qtd;
    produtos[id_pr].stock = produtos[id_pr].stock - qtd;
    encomendas[id_enc].n_de_produtos+= 1;

	return 0;
}

/* function that removes stock from a products */
int r(){
	int novo_stock, id_produto, i=2, a=0, b=0;
	char com_stock[LIM_INPUT], com_prod[LIM_INPUT];

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		com_prod[a]= comando[i];
		a+=1;
	}
	i+=1;
	com_prod[a] = '\0';
	id_produto= atoi(com_prod);

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		com_stock[b]= comando[i];
		b+=1;
	}
	com_stock[b]= '\0';
	novo_stock = atoi(com_stock);

	if (id_produto >= id_prod ){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_produto);
		return 0;
	}

	if (produtos[id_produto].stock - novo_stock < 0){
		printf("Impossivel remover %d do produto %d do stock. Quantidade insuficiente.\n", novo_stock, id_produto);
		return 0;
	}
	else{
		produtos[id_produto].stock = produtos[id_produto].stock - novo_stock;
	}

	return 0;
}

/* function that removes products from orders */
int R(){
	int enc_id, prod_id, i=2, a=0, b=0, c=0;
	Produto produto_a_remover;
	Produto ultimo_produto;
	char com_ide[LIM_INPUT], com_prod[LIM_INPUT];

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		com_ide[a]= comando[i];
		a+=1;
	}
	i+=1;
	com_ide[a] = '\0';
	enc_id = atoi(com_ide);

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		com_prod[b]= comando[i];
		b+=1;
	}
	com_prod [b] = '\0';
	prod_id = atoi(com_prod);

	if (enc_id >= id_encomenda){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod_id, enc_id);
		return 0; 
	} 
	if (prod_id >= id_prod){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod_id, enc_id);
		return 0; 
	}
    
    produto_a_remover = produtos[prod_id];
    ultimo_produto = encomendas[enc_id].prods[encomendas[enc_id].n_de_produtos - 1];
    
    for (; c < encomendas[enc_id].n_de_produtos; c++){
    	if (encomendas[enc_id].prods[c].idp == prod_id){
    		produtos[prod_id].stock += encomendas[enc_id].prods[c].stock;
            encomendas[enc_id].prods[c] = ultimo_produto;
            encomendas[enc_id].prods[encomendas[enc_id].n_de_produtos - 1] = produto_a_remover;
            encomendas[enc_id].n_de_produtos = encomendas[enc_id].n_de_produtos -1;

    	}
    }

    return 0;
}

/* function that calculates an order's total monetary cost */
int C(){
	int i=2, a=0, b=0, id_encom, total=0;
	char controlo_encom[LIM_INPUT];

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		controlo_encom[b]= comando[i];
		b+=1;
	}
	controlo_encom[b]= '\0';
	id_encom = atoi(controlo_encom);

	if(id_encom >= id_encomenda){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_encom);
		return 0;
	}

	for (; a < encomendas[id_encom].n_de_produtos; a++){
		total+= encomendas[id_encom].prods[a].stock * encomendas[id_encom].prods[a].preco;
	}
	printf("Custo da encomenda %d %d.\n", id_encom, total);

	return 0;
}

/* function that alters a product's price */
int p(){
	int produto_id, novo_preco, a=0, b=0, i=2, c, d;
	char com_idp[LIM_INPUT], com_npreco[LIM_INPUT];

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		com_idp[a]= comando[i];
		a+=1;
	}
	i+=1;
	com_idp[a] = '\0';
	produto_id = atoi(com_idp);

	if (produto_id > id_prod-1){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", produto_id);
		return 0;
	}

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		com_npreco[b] = comando[i];
		b+=1;
	}
	com_npreco[b] = '\0';
	novo_preco = atoi(com_npreco);
	produtos[produto_id].preco = novo_preco;

	for (c=0; c < id_encomenda; c++){
		for (d=0; d < id_prod; d++){
			if (encomendas[c].prods[d].idp == produto_id){
				encomendas[c].prods[d].preco = novo_preco;
			} 
		}
	}

	return 0;
}

/* function that returns a product's description and quantity in a given order */
int E(){
	int idenc, idprod, a=0, b=0, c=0, i=2;
	char idencomenda[LIM_INPUT], idproduto[LIM_INPUT];

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		idencomenda[a]= comando[i];
		a+=1;
	}
	i+=1;
	idencomenda[a] = '\0';
	idenc = atoi(idencomenda);

	if (idenc >= id_encomenda){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idenc);
		return 0;
	}

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		idproduto[b] = comando[i];
		b+=1;
	}
	idproduto[b] = '\0';
	idprod = atoi(idproduto);

	if (idprod >= id_prod){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idprod);
		return 0;
	}

	while (c < encomendas[idenc].n_de_produtos){
		if (encomendas[idenc].prods[c].idp == idprod){
			printf("%s %d.\n", encomendas[idenc].prods[c].descricao, encomendas[idenc].prods[c].stock);
			return 0;
		}
		c+=1;
	}

	printf("%s %d.\n", produtos[idprod].descricao, 0);

	return 0;
}

/* function that returns the order id in which the given products occurs more times */
int m(){
	int prod_id, i=2, a=0, k=0, p;
	/* variable that will be used to store the order id in which the product occurs more */
	int enc_prod= -1;
	/* variable that will be used to compare the product quantity in different orders */
	int qtd=0;
	char comando_idp[LIM_INPUT];

	if (n_de_encomendas == 0){
		return 0;
	}

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		comando_idp[a]= comando[i];
		a+=1;
	}
	comando_idp[a] = '\0';
	prod_id = atoi(comando_idp);

/* cycle that checks in which orders the product exists and checks in which it occurs more */
	for (; k < n_de_encomendas; k++){
		for (p=0; p < encomendas[k].n_de_produtos; p++){
			if (encomendas[k].prods[p].idp == prod_id){
				if (encomendas[k].prods[p].stock > qtd){
					enc_prod = k;
					qtd = encomendas[k].prods[p].stock;
				if (encomendas[k].prods[p].stock == qtd){
					if (k < enc_prod){
						enc_prod = k;
						qtd = encomendas[k].prods[p].stock;
					}
				}
				}

			}        
		}
	}
    if (enc_prod == -1){
    	return 0;
    }
    printf("Maximo produto %d %d %d.\n", prod_id, enc_prod, qtd);
	return 0;
}

/* function that returns all the products within the system by ordered by price from lower to higher */
int l(){
	return 0;
}

/* function that returns all the products from an order id ordered alphabetically */
int L(){
	return 0;
}

/* extra function that returns an order's weight */
int K(){
	int id_enc, peso_encomenda = 0, i=2, a=0, b;
	char com_encomenda[LIM_INPUT];

	for (; comando[i] != ':' && comando[i] != EOF && comando[i] != '\n'; i++){
		com_encomenda[a] = comando[i];
		a+=1;
	}
	com_encomenda[a] = '\0';
	id_enc = atoi(com_encomenda);

	for (b=0; b < encomendas[id_enc].n_de_produtos; b++){
		peso_encomenda += encomendas[id_enc].prods[b].peso * encomendas[id_enc].prods[b].stock;
	}
	printf("Peso da encomenda %d e igual a %d.\n", id_enc, peso_encomenda);

	return 0;
}

/* extra function that return a product's id description, price, weight and stock */
int P(){
	int i=2, a=0;
	char product_id [LIM_INPUT];
	int product;
	for (; comando[i]!= ':' && comando[i]!= EOF && comando[i]!= '\n'; i++){
		product_id[a] = comando[i];
		a+=1;
	}
	product = atoi(product_id);

	printf("%s %d %d %d\n", produtos[product].descricao, produtos[product].preco, produtos[product].peso, produtos[product].stock);

	return 0;
}

int main ()
{
while ( comando[0] != 'x'){
fgets(comando, LIM_INPUT, stdin);
if (comando[0] == 'a'){
	a();
}
if (comando [0] == 'q'){
	q();
}
if (comando [0] == 'A'){
	A();
}
if (comando [0] == 'N'){
	N();
}
if (comando [0] == 'r'){
	r();
}
if (comando [0] == 'R'){
	R();
}
if (comando [0] == 'C'){
	C();
}
if (comando [0] == 'E'){
	E();
}
if (comando [0] == 'p'){
	p();
}
if (comando [0] == 'm'){
	m();
}
if (comando [0] == 'l'){
	l();
}
if (comando [0] == 'L'){
	L();
}
if (comando [0] == 'K'){
	K();
}
if (comando[0] == 'P'){
	P();
}
}
return 0;
}

