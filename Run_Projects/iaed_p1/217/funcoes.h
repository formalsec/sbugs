#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_DESC 64 
#define MAX_PRODUTOS 10000 
#define MAX_ENCOMENDAS 500
#define MAX_PRODENCOMENDAS 200

/*Estrutura de um produto*/
typedef struct {
	char desc[MAX_DESC];
	int preco;
	int peso;
	int stock;
} Produto;

/*Estrutura de um produto adicionado a uma encomenda*/
typedef struct {
	int id;
	int qtd;
} prodEncomenda;


/*Estrutura de uma encomenda*/
typedef struct {
	prodEncomenda produtos[MAX_PRODENCOMENDAS];
	int numProd;
	int peso;
} Encomenda;

/*Vetor de produtos inseridos no sistema*/
Produto vetorProdutos[MAX_PRODUTOS];

/*Vetor de Encomendas criadas no sistema*/
Encomenda vetorEncomendas[MAX_ENCOMENDAS];

/*Inteiro que guarda o valor total dos produtos*/
int numeroProdutos;

/*Inteiro que guarda o valor total das encomendas*/
int numEncomendas;


void a(char* desc, int preco, int peso, int qtd);
void q(int idp, int qtd);
void N();
void A(int ide, int idp, int qtd);
void r(int idp, int qtd);
void R(int ide, int idp);
void C(int ide);
void p(int idp, int preco);
void E(int ide, int idp);
void m(int idp);
void l();
void L(int ide);
int O(char *a, char *b);

#endif
