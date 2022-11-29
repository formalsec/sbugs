#define ENCOMENDAS_MAX 500
#define PRODUTOS_MAX 10000

typedef struct produto
{
	char descricao[63];
	int peso;
	int preco;
	int qtd;
	int idp;
} PRODUTO;

void print_produto(PRODUTO item);

PRODUTO add_produto(char descricao[63],int peso,int preco,int qtd, int idp);


PRODUTO add_stock(PRODUTO item, int stock);


typedef struct encomenda
{
	int qtd[200];
	int peso;
	int produto[200];
	int ide;
} ENCOMENDA;

void print_produto(PRODUTO item);

PRODUTO add_produto(char descricao[63],int peso,int preco,int qtd, int numero_produto);

PRODUTO add_stock(PRODUTO item, int stock);

void print_encomenda(ENCOMENDA item);

ENCOMENDA create_encomenda(int numero_encomenda);

ENCOMENDA add_encomenda(ENCOMENDA encomenda, int qtd, PRODUTO produto, int* flag, int *i);

ENCOMENDA retira_produto(ENCOMENDA encomenda, PRODUTO produto, int* flag, int *qtd);

PRODUTO remove_stock(PRODUTO item, int stock);

void calcula_custo(ENCOMENDA encomenda, PRODUTO produtos[PRODUTOS_MAX]);

PRODUTO altera_preco(PRODUTO item, int novo_preco);

void listar_encomenda(ENCOMENDA encomenda, int idp, PRODUTO produtos[PRODUTOS_MAX]);

void encomenda_maior_produto(ENCOMENDA encomendas[ENCOMENDAS_MAX], int idp);
