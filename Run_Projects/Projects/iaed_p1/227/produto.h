#include <stdio.h>
#include <string.h>

typedef struct produto{
    int produto_id;
    char descricao[63];
    int preco;
    int peso;
    int stock;
}Produto;

typedef struct encomenda{
    int encomenda_id;
    int encomenda_peso;
    Produto encomenda_produto[300];
}Encomenda;