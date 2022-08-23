#include <stdio.h>
#include <string.h>

/*
 * Constantes:
*/

/* O numero maximo de caracteres da descricao de um produto (mais caracter '/0'). */
#define MAX_DESC 64
/* O numero maximo de produtos diferentes. */
#define MAX_PRODUTOS 10000
/* O numero maximo de encomendas existentes. */
#define MAX_ENCOMENDAS 500
/* O peso maximo que uma encomenda pode ter. */
#define MAX_PESO 200
/* Estado que indica a ausencia de um produto numa encomenda. */
#define OUT -1
/* Estado que indica se estamos a ordenar os produtos duma encomenda. */
#define ENCOMENDA 0
/* Estado que indica se estamos a ordenar os produtos do sistema. */
#define PRODUTOS 1

/*
 * Abstracoes:
*/

/* Abstracoes utilizadas no algoritmo de ordenacao. */
typedef int Item;
#define keyP(A) (sistema_produtos[A].preco)
#define keyE(A) (sistema_produtos[sistema_encomendas[encomenda].produtos[A].idp].desc)
#define less(A, B, C) (C == ENCOMENDA ? strcmp(keyE(A), keyE(B)) < 0 : lessAux(A,B))
#define lessAux(A, B) (keyP(A) == keyP(B) ? A < B : keyP(A) < keyP(B))
#define exch(A, B) { Item t = A; A = B; B = t; }

/*
 * Estruturas:
*/

/* Estrutura que define o tipo produto e as suas caracteristicas. */
typedef struct {
    char desc[MAX_DESC];
    int preco, peso, qtd;
} Produto;
/* Estrutura que representa um produto numa encomenda. */
typedef struct {
    int idp, qtd;
} ProdutoEncomenda;
/* Estrutura que define o tipo encomenda e as suas caracteristicas. */
typedef struct {
    ProdutoEncomenda produtos[MAX_PESO];
    int peso, qtd_produtos;
} Encomenda;

/*
 * Variaveis Globais:
*/

/* Variavel global que representa os produtos existentes na memoria do sistema. */
Produto sistema_produtos[MAX_PRODUTOS] = {{"", 0, 0, 0}};
/* Variavel global que representa o numero de produtos no sistema. */
int produtos_existentes = 0;
/* Variavel global que representa as encomendas existentes na memoria do sistema. */
Encomenda sistema_encomendas[MAX_ENCOMENDAS] = {0};
/* Variavel global que representa o numero de encomendas no sistema. */
int encomendas_existentes = 0;
/* Variavel global que representa a encomenda que esta a ser analisada (util para a ordenacao). */
int encomenda = 0;

/*
 * Funcoes:
*/

/* Funcao que verifca e devolve a posicao de um produto numa encomenda. 
id_encomenda: parametro que representa o identificador da encomenda.
id_produto: parametro que representa o identificador do produto. */
int encontra_produto(int id_encomenda, int id_produto) {
    int contador;
    /* Variavel local onde e armazenada a posicao de um produto numa encomenda. */
    int pos = OUT;

    for (contador = 0; contador < sistema_encomendas[id_encomenda].qtd_produtos; contador++) {
        if (id_produto == sistema_encomendas[id_encomenda].produtos[contador].idp){
            pos = contador;
            break;
        }
    }
    return pos;
}

/* Funcao que adiciona stock a um produto existente.
id_produto: parametro que representa o identificador do produto.
qtd_produto: parametro que representa a quantidade do produto. */
void adiciona_stock(int id_produto, int qtd_produto) {
    if (id_produto >= produtos_existentes) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_produto);
    }
    else {
        sistema_produtos[id_produto].qtd += qtd_produto;
    }
}

/* Funcao que remove stock a um produto existente.
id_produto: parametro que representa o identificador do produto.
qtd_produto: parametro que representa a quantidade do produto. */
void remove_stock(int id_produto, int qtd_produto) {
    if (id_produto >= produtos_existentes) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_produto);
    }
    else if (sistema_produtos[id_produto].qtd - qtd_produto < 0) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_produto, id_produto);
    }
    else {
        sistema_produtos[id_produto].qtd -= qtd_produto;
    }
}

/* Funcao que adiciona uma certa quantidade de um produto a uma encomenda.
id_encomenda: parametro que representa o identificador da encomenda.
id_produto: parametro que representa o identificador do produto.
qtd_produto: parametro que representa a quantidade do produto. */
void adiciona_produto(int id_encomenda, int id_produto, int qtd_produto) {
    /* Variavel local onde e armazenada a posicao de um produto numa encomenda. */
    int pos;
    /* Variavel local onde e armazenado o numero de produtos numa encomenda. */
    int encomenda_produtos;

    if (id_encomenda >= encomendas_existentes) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);
    }
    else if (id_produto >= produtos_existentes) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
    }
    else if (qtd_produto > sistema_produtos[id_produto].qtd) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_produto, id_encomenda);
    }
    else if (qtd_produto * sistema_produtos[id_produto].peso + sistema_encomendas[id_encomenda].peso > 200) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_produto, id_encomenda);
    }
    else {
        pos = encontra_produto(id_encomenda, id_produto);
        if (pos != OUT) {
            /* Se o produto ja exitir na encomenda, apenas adiciona a nova quantidade ao espaco/posicao ja reservado para o produto. */
            sistema_encomendas[id_encomenda].produtos[pos].qtd += qtd_produto;
        }
        else {
            /* Caso contrario, cria um novo espaco/posicao para o produto a adicionar. */
            encomenda_produtos = sistema_encomendas[id_encomenda].qtd_produtos;
            sistema_encomendas[id_encomenda].produtos[encomenda_produtos].idp = id_produto;
            sistema_encomendas[id_encomenda].produtos[encomenda_produtos].qtd = qtd_produto;
            sistema_encomendas[id_encomenda].qtd_produtos += 1;
        }
        sistema_encomendas[id_encomenda].peso += sistema_produtos[id_produto].peso * qtd_produto;
        remove_stock(id_produto, qtd_produto);
    }
}

/* Funcao que remove um produto de uma encomenda.
id_encomenda: parametro que representa o identificador da encomenda.
id_produto: parametro que representa o identificador do produto. */
void remove_produto(int id_encomenda, int id_produto) {
    /* Variavel local onde e armazenada a posicao de um produto numa encomenda. */
    int pos;
    /* Variavel local onde e armazenado o numero de produtos numa encomenda. */
    int encomenda_produtos;

    if (id_encomenda >= encomendas_existentes) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);
    }
    else if (id_produto >= produtos_existentes) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
    }
    else {
        pos = encontra_produto(id_encomenda, id_produto);
        if (pos != OUT) {
            sistema_encomendas[id_encomenda].qtd_produtos -= 1;
            sistema_encomendas[id_encomenda].peso -= sistema_encomendas[id_encomenda].produtos[pos].qtd * sistema_produtos[id_produto].peso;
            adiciona_stock(id_produto, sistema_encomendas[id_encomenda].produtos[pos].qtd);
            /* Mete o produto que estava na ultima posicao, na posicao do produto que esta a ser removido, e anula a ultima posicao. */
            sistema_encomendas[id_encomenda].produtos[pos].idp = sistema_encomendas[id_encomenda].produtos[(encomenda_produtos = sistema_encomendas[id_encomenda].qtd_produtos)].idp;
            sistema_encomendas[id_encomenda].produtos[pos].qtd = sistema_encomendas[id_encomenda].produtos[encomenda_produtos].qtd;
            sistema_encomendas[id_encomenda].produtos[encomenda_produtos].idp = 0;
            sistema_encomendas[id_encomenda].produtos[encomenda_produtos].qtd = 0;
        }
    }
}

/* Funcao que calcula o custo de uma encomenda.
id_encomenda: parametro que representa o identificador da encomenda. */
void calcula_custo(int id_encomenda) {
    int contador;
    /* Variavel local onde e armazenado o custo de uma encomenda. */
    int custo = 0;
    /* Variavel local onde e armazenado o identificador de um produto. */
    int produto_id;
    /* Variavel local onde e armazenado a quantidade de um produto. */
    int produto_qtd;

    if (id_encomenda >= encomendas_existentes) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_encomenda);
    }
    else {
        for (contador = 0; contador < sistema_encomendas[id_encomenda].qtd_produtos; contador++){
            produto_id = sistema_encomendas[id_encomenda].produtos[contador].idp;
            produto_qtd = sistema_encomendas[id_encomenda].produtos[contador].qtd;
            custo += sistema_produtos[produto_id].preco * produto_qtd;
        }
        printf("Custo da encomenda %d %d.\n", id_encomenda, custo);
    }
}

/* Funcao que altera o pre?o de um produto existente.
id_produto: parametro que representa o identificador do produto.
preco: parametro que representa o novo preco do produto. */
void altera_preco(int id_produto, int preco) {
    if (id_produto >= produtos_existentes) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_produto);
    }
    else {
        sistema_produtos[id_produto].preco = preco;
    }
}

/* Funcao que lista a descri??o e a quantidade de um produto numa encomenda.
id_encomenda: parametro que representa o identificador da encomenda.
id_produto: parametro que representa o identificador do produto. */
void lista_produto(int id_encomenda, int id_produto) {
    /* Variavel local onde e armazenada a posicao de um produto numa encomenda. */
    int pos;
    /* Variavel local onde e armazenado a quantidade de um produto. */
    int produto_qtd;
    
    if (id_encomenda >= encomendas_existentes) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_encomenda);
    }
    else if (id_produto >= produtos_existentes) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", id_produto);
    }
    else {
        printf("%s ", sistema_produtos[id_produto].desc);
        pos = encontra_produto(id_encomenda, id_produto);
        if (pos != OUT) {
            produto_qtd = sistema_encomendas[id_encomenda].produtos[pos].qtd;
        }
        else {
            /* Se o produto nao existir na encomenda, significa que ha zero do mesmo. */
            produto_qtd = 0;
        }
        printf("%d.\n", produto_qtd);
    }
}

/* Funcao que lista o identificador da encomenda em que o produto dado ocorre mais vezes.
id_produto: parametro que representa o identificador do produto. */
void lista_ocorrencia(int id_produto) {
    int contador;
    /* Variavel local onde e armazenada a posicao de um produto numa encomenda. */
    int pos;
    /* Variavel local onde e armazenado a quantidade de um produto. */
    int produto_qtd;
    /* Variavel local onde e armazenado o identificador de uma encomenda e a quantidade de um produto nessa encomenda. */
    int encomenda_pqtd[2] = {0};

    if (id_produto >= produtos_existentes) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_produto);
    }
    else {
        for (contador = 0; contador < encomendas_existentes; contador++) {
            pos = encontra_produto(contador, id_produto);
            if (pos != OUT && (produto_qtd = sistema_encomendas[contador].produtos[pos].qtd) > encomenda_pqtd[1]){
                encomenda_pqtd[0] = contador;
                encomenda_pqtd[1] = produto_qtd;
            }
        }
        if (encomenda_pqtd[1] > 0) {
            printf("Maximo produto %d %d %d.\n", id_produto, encomenda_pqtd[0], encomenda_pqtd[1]);
        }
    }
}

/* Prototipo da funcao quick_sort, definida mais abaixo. */
void quick_sort(Item tabela[], int l, int r, int flag);

/* Funcao auxiliar da funcao que implementa o algoritmo de ordenacao quick sort.
tabela: parametro que representa a tabela de elementos a ordenar, que pode conter, ou identificadores de produtos, ou posicoes de produtos numa encomenda. 
l: parametro que representa a posicao do inicio da ordenacao.
r: parametro que representa a posicao do fim da ordenacao.
flag: parametro que indica se se esta a ordenar identificadores de produtos, ou posicoes de produtos numa encomenda. */
void partition(Item tabela[], int l, int r, int flag) {
    int i = l;
    int j = r;
    Item pivot = tabela[(l + r) / 2];

    while (i <= j) {
        while (less(tabela[i], pivot, flag)) {
            i++;
        }
        while (less(pivot, tabela[j], flag)) {
            j--;
        }
        if (i <= j) {
            exch(tabela[i], tabela[j]);
            i++;
            j--;
        }
    }
    quick_sort(tabela, l, j, flag);
    quick_sort(tabela, i, r, flag);
}

/* Funcao que implementa o algoritmo de ordenacao quick sort.
tabela: parametro que representa a tabela de elementos a ordenar, que pode conter, ou identificadores de produtos, ou posicoes de produtos numa encomenda. 
l: parametro que representa a posicao do inicio da ordenacao.
r: parametro que representa a posicao do fim da ordenacao.
flag: parametro que indica se se esta a ordenar identificadores de produtos, ou posicoes de produtos numa encomenda. */
void quick_sort(Item tabela[], int l, int r, int flag) {
    if (r <= l) {
        return;
    }
    partition(tabela, l, r, flag);
}

/* Funcao que lista todos os produtos existentes no sistema por ordem crescente de pre?o. */
void lista_sistema(void) {
    int contador;
    /* Variavel local onde sao armazenados os identficadores dos produtos existentes. */
    int produtos_ids[MAX_PRODUTOS] = {0};

    for (contador = 0; contador < produtos_existentes; contador++) {
        produtos_ids[contador] = contador;
    }
    if (produtos_existentes > 1) {
        quick_sort(produtos_ids, 0, produtos_existentes - 1, PRODUTOS);
    }
    printf("Produtos\n");
    for (contador = 0; contador < produtos_existentes; contador++) {
        printf("* %s %d %d\n", sistema_produtos[produtos_ids[contador]].desc, sistema_produtos[produtos_ids[contador]].preco, sistema_produtos[produtos_ids[contador]].qtd);
    }
}

/* Funcao que lista todos os produtos de uma encomenda por ordem alfabetica da descricao.
id_encomenda: parametro que representa o identificador da encomenda. */
void lista_encomenda(int id_encomenda) {
    int contador;
    /* Variavel local onde e armazenado o numero de produtos numa encomenda. */
    int encomenda_produtos;
    /* Variavel local onde sao armazenados os identficadores dos produtos existentes. */
    int posicoes[MAX_PESO] = {0};

    if (id_encomenda >= encomendas_existentes) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_encomenda);
    }
    else {
        /* Atribbuicao do identificador da encomenda a variavel global, usada nas macros. */
        encomenda = id_encomenda;
        for (contador = 0; contador < (encomenda_produtos = sistema_encomendas[id_encomenda].qtd_produtos); contador++) {
            posicoes[contador] = contador;
        }
        if (encomenda_produtos > 1) {
            quick_sort(posicoes, 0, encomenda_produtos - 1, ENCOMENDA);
        }
        printf("Encomenda %d\n", id_encomenda);
        for (contador = 0; contador < encomenda_produtos; contador++) {
            printf("* %s %d %d\n", sistema_produtos[sistema_encomendas[id_encomenda].produtos[posicoes[contador]].idp].desc, sistema_produtos[sistema_encomendas[id_encomenda].produtos[posicoes[contador]].idp].preco, sistema_encomendas[id_encomenda].produtos[posicoes[contador]].qtd);
        }
    }
}

/*
 * Funcao Main:
*/

int main() {
    /* Variavel local que armazena o caracter (de um comando) do standard input, e determina a acao a realizar. */
    char caracter;
    /* Variaveis locais onde sao armazenados os dados de entrada dos comandos. */
    int arg_1, arg_2, arg_3;

    while ((caracter = getchar()) != 'x' && caracter != EOF) {
        switch (caracter) {
            case 'a':
                scanf(" %[^:]:%d:%d:%d", sistema_produtos[produtos_existentes].desc, &sistema_produtos[produtos_existentes].preco, &sistema_produtos[produtos_existentes].peso, &sistema_produtos[produtos_existentes].qtd);
                printf("Novo produto %d.\n", produtos_existentes);
                produtos_existentes += 1;
                break;
            case 'q':
                scanf(" %d:%d", &arg_1, &arg_2);
                adiciona_stock(arg_1, arg_2);
                break;
            case 'N':
                printf("Nova encomenda %d.\n", encomendas_existentes);
                encomendas_existentes += 1;
                break;
            case 'A':
                scanf(" %d:%d:%d", &arg_1, &arg_2, &arg_3);
                adiciona_produto(arg_1, arg_2, arg_3);
                break;
            case 'r':
                scanf(" %d:%d", &arg_1, &arg_2);
                remove_stock(arg_1, arg_2);
                break;
            case 'R':
                scanf(" %d:%d", &arg_1, &arg_2);
                remove_produto(arg_1, arg_2);
                break;
            case 'C':
                scanf(" %d", &arg_1);
                calcula_custo(arg_1);
                break;
            case 'p':
                scanf(" %d:%d", &arg_1, &arg_2);
                altera_preco(arg_1, arg_2);
                break;
            case 'E':
                scanf(" %d:%d", &arg_1, &arg_2);
                lista_produto(arg_1, arg_2);
                break;
            case 'm':
                scanf(" %d", &arg_1);
                lista_ocorrencia(arg_1);
                break;
            case 'l':
                lista_sistema();
                break;
            case 'L':
                scanf(" %d", &arg_1);
                lista_encomenda(arg_1);
                break;
        }
    }
    return 0;
}
