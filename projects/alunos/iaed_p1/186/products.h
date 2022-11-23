#ifndef PRODUCTS_H_
#define PRODUCTS_H_

/* Constante que define o numero maximo de produtos que podem ser inseridos no
   sistema. */
#define MAX_PRODUCTS 10000

/* Constante que define o tamanho maximo da descricao de um produto, incluindo
   o caracter '\0'. */
#define PROD_DESC_SIZE 64

/* Estrutura de um produto.

   Atributos:
      id: Identificador do produto.
      alive: 0 se o produto eh invalido, 1 quando o produto eh valido.
      description: Descricao do produto.
      price: Preco do produto.
      weight: Peso do produto.
      quantity: Quantidade de produto.
*/
typedef struct {
    int id, alive, price, weight, quantity;
    char description[PROD_DESC_SIZE];
} Product;

/* Variavel global que armazena todos os produtos do sistema. */
Product products[MAX_PRODUCTS];

/* Variavel global correspodente ao numero total de produtos existentes no
   sistema. */
int productCount;

/* Funcoes auxiliares */
int productExists(int idp);

/* Funcoes responsaveis pela logica de comandos */
void addProductCmd();
void addStockCmd();
void removeStockCmd();
void changePriceCmd();
void biggestOccurrenceCmd();
void listAllProductsCmd();
void listAllProductsIDCmd();

#endif
