#define STR_MAX 64
#define MAX_PROD 10000
#define MAX_ENC 500
#define MAX_PESO 200
#define MAX_INT 32768

/*ESTRUTURAS*/

/*
  Produto: int, char*, int, int, int
  Representa um produto constituida por id, descricao, preco, peso e quantidade.
*/
typedef struct {
    int id;
    char desc[STR_MAX];
    int preco;
    int peso;
    int qtd;
} Produto;

/*
  Pinfo: int, int
  Representa a informacao de um produto numa encomenda constituida por uma quantidade
  e um numero set que indica se o produto existe na encomenda ou nao.
*/
typedef struct {
    int qtd;
    int set;
} Pinfo;

/*
  Encomenda: int, int, Pinfo*
  Representa uma encomenda constituida por peso, quantidade de produtos na encomenda e um
  vetor de informacoes de produtos.
*/
typedef struct {
    int peso;
    int size;
    Pinfo pinfo[MAX_PROD];
} Encomenda;
