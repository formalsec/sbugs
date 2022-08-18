#define MAX_TMNH_INPUT 100

/* Numero maximo de produtos dentro do sistema. */
#define MAX_PROD 10000

/* Numero maximo de encomendas dentro do sistema. */
#define MAX_ENC 500

/* Numero maximo de peso dentro de uma encomenda. */
#define MAX_PESO 200

/* Flag que indica que uma posicao contem informacao. */
#define CHEIO 1

/* Flag que indica que uma posicao nao contem informacao ou seja esta vazia. */
#define VAZIO 0

/* Numero maximo de caracteres da descricao. */
#define MAX_DESC 64

/* Numero maximo de produtos dentro de uma encomenda. */
#define MAX_PRD_ENC 200

/* Estrutura de um produto. */
typedef struct produto{
	int id;
	char descricao[MAX_DESC];
	int preco;
	int peso;
	int stock;
	int posfull;
}produto;

/* Estrutura de uma encomenda. */
typedef struct encomenda{
	int id;
	int totalprdcts;
	produto prdcts[MAX_PRD_ENC];
	int pesototal;
	int precototal;
	int posfull;
	
}encomenda;