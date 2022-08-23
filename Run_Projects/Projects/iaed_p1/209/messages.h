#ifndef MESSAGES
#define MESSAGES

#define INVALID_PRODUCT_ERROR "Impossivel adicionar produto %d ao stock. Produto inexistente.\n"
#define INVALID_STOCK_AMOUNT_ERROR "Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n"

#define INVALID_ADD_PRODUCT "Impossivel adicionar produto %d a encomenda %d."
#define INVALID_ADD_PRODUCT_PACKAGE INVALID_ADD_PRODUCT " Encomenda inexistente.\n"
#define INVALID_PACKAGE_ADD_ERROR INVALID_ADD_PRODUCT " Encomenda inexistente.\n"
#define INVALID_ADD_PRODUCT_PRODUCT INVALID_ADD_PRODUCT " Produto inexistente.\n"
#define INVALID_ADD_PRODUCT_STOCK INVALID_ADD_PRODUCT " Quantidade em stock insuficiente.\n"
#define INVALID_ADD_PRODUCT_OVERWEIGHT INVALID_ADD_PRODUCT " Peso da encomenda excede o maximo de 200.\n"

#define INVALID_RESTOCK_PRODUCT "Impossivel adicionar produto %d ao stock. Produto inexistente.\n"

#define INVALID_REMOVE_STOCK_PRODUCT "Impossivel remover stock do produto %d. Produto inexistente.\n"
#define INVALID_REMOVE_STOCK_AMOUNT "Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n"

#define INVALID_REMOVE_PRODUCT "Impossivel remover produto %d a encomenda %d."
#define INVALID_REMOVE_PRODUCT_PACKAGE INVALID_REMOVE_PRODUCT " Encomenda inexistente.\n"
#define INVALID_REMOVE_PRODUCT_PRODUCT INVALID_REMOVE_PRODUCT " Produto inexistente.\n"

#define INVALID_PACKAGE_PRICE_PACKAGE "Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n" 
#define INVALID_SET_PRODUCT_PRICE_PRODUCT "Impossivel alterar preco do produto %d. Produto inexistente.\n"

#define INVALID_PRODUCT_INFO_PACKAGE "Impossivel listar encomenda %d. Encomenda inexistente.\n"
#define INVALID_PRODUCT_INFO_PRODUCT "Impossivel listar produto %d. Produto inexistente.\n"

#define INVALID_MOST_VALUABLE_PACKAGE_PRODUCT "Impossivel listar maximo do produto %d. Produto inexistente.\n"

#define INVALID_LIST_PRODUCTS_BY_DESC "Impossivel listar encomenda %d. Encomenda inexistente.\n"

#define NEW_PRODUCT_MESSAGE "Novo produto %d.\n"
#define NEW_PACKAGE_MESSAGE "Nova encomenda %d.\n"
#define PACKAGE_PRICE "Custo da encomenda %d %d.\n"
#define PRODUCT_INFO "%s %d.\n"
#define MVP "Maximo produto %d %d %d.\n"
#define LIST_PRODUCTS_BY_PRICE_HEADER "Produtos\n"
#define LIST_PRODUCTS_BY_DESC_HEADER "Encomenda %d\n"
#define LIST_PRODUCTS_PRODUCT "* %s %d %d\n"

#endif
