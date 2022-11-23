#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/

#define MAX_CHAR_DESCRICAO 63                                       /*numero maximo de caracteres para a descricao de um produto*/
#define MAX_PRODUTOS_STOCK 10000                                    /*numero maximo de produtos*/
#define MAX_PESO_ENCOMENDA 200                                      /*peso maximo de uma encomenda*/
#define MAX_PRODUTOS_ENCOMENDA MAX_PESO_ENCOMENDA                   /*maximo numero de produtos numa encomenda*/
#define MAX_ENCOMENDAS 500                                          /*numero maximo de encomendas*/

#define exch(A, B) { int t = A[0]; A[0] = B[0]; B[0] = t; t = A[1]; A[1] = B[1]; B[1] = t; } /*troca dois elementos de um vetor[][2]*/

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/

typedef struct {
    char descricao[MAX_CHAR_DESCRICAO + 1];
    int preco, peso;

} Produto;

typedef struct {
    int numeroProdutosEncomenda, pesoTotal;
    int produtos[MAX_PRODUTOS_ENCOMENDA][2]; /*[idProduto, quantidade]*/

} Encomenda;

typedef struct {
    int numeroProdutos, numeroEncomendas;
    int stock[MAX_PRODUTOS_STOCK];/*[quantidade], tem o idProduto como indice*/
    Produto produtos[MAX_PRODUTOS_STOCK];
    Encomenda encomendas[MAX_ENCOMENDAS];

} Sistema;

/*------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------*/

Sistema sistema;/*variavel global que guarda toda a informacao do sistema de logistica*/

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/

void adicionaProdutoSistema();          /*comando - a*/
void adicionaStockProduto();            /*comando - q*/
void criaEncomenda();                   /*comando - N*/
void adicionaProdutoEncomenda();        /*comando - A*/
void removeStockProduto();              /*comando - r*/
void removeProdutoEncomenda();          /*comando - R*/
void calculaCusto();                    /*comando - C*/
void alteraPreco();                     /*comando - p*/
void printProdutoEncomenda();           /*comando - E*/
void produtoMaiorOcorrencia();          /*comando - m*/
void printProdutos();                   /*comando - l*/
void printEncomenda();                  /*comando - L*/

void adicionaProdutoEncomend_aux(int, int, int);
void atualizaStock(int, int);

void quicksort(int lista[][2], int, int, int());
int partition(int lista[][2],int, int, int());

int cmp_preco(int a[2], int b[2]);
int cmp_desc(int a[2], int b[2]);

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/

int main() {
    char comando;                                             /*variavel que le e gaurda o comando de cada linha*/

    sistema.numeroProdutos = 0;                               /*comeca com 0 produtos*/
    sistema.numeroEncomendas = 0;                             /*comeca com 0 encomendas*/

    while (scanf("%c", &comando)) {
        switch (comando) {
            case 'a': adicionaProdutoSistema(); break;

            case 'q': adicionaStockProduto(); break;

            case 'N': criaEncomenda(); break;

            case 'A': adicionaProdutoEncomenda(); break;

            case 'r': removeStockProduto(); break;

            case 'R': removeProdutoEncomenda(); break;

            case 'C': calculaCusto(); break;

            case 'p': alteraPreco(); break;

            case 'E': printProdutoEncomenda(); break;

            case 'm': produtoMaiorOcorrencia(); break;

            case 'l': printProdutos(); break;

            case 'L': printEncomenda(); break;

            case 'x': return 0;/*x - termina o programa*/
        }
    }
    return -1;
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*a - adiciona um novo produto ao sistema.*/
void adicionaProdutoSistema() {
    Produto produto;

    scanf(" %[^:]:%d:%d:%d", produto.descricao, &produto.preco, &produto.peso, &sistema.stock[sistema.numeroProdutos]);
    printf("Novo produto %d.\n", sistema.numeroProdutos);
    sistema.produtos[sistema.numeroProdutos++] = produto;
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*q - adiciona stock a um produto existente no sistema.*/
void adicionaStockProduto() {
    int idProduto, quantidade;

    scanf("%d:%d", &idProduto, &quantidade);
    if (idProduto >= sistema.numeroProdutos) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idProduto);

    } else {
        atualizaStock(idProduto, quantidade);
    }
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*N - cria uma nova encomenda.*/
void criaEncomenda() {
    printf("Nova encomenda %d.\n", sistema.numeroEncomendas);

    sistema.encomendas[sistema.numeroEncomendas].numeroProdutosEncomenda = 0;
    sistema.encomendas[sistema.numeroEncomendas++].pesoTotal = 0;
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*A - adiciona um produto a uma encomenda.
Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente.*/
void adicionaProdutoEncomenda() {
    int idEncomenda, idProduto, quantidade;

    scanf("%d:%d:%d\n", &idEncomenda, &idProduto, &quantidade);

    if (idEncomenda >= sistema.numeroEncomendas) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idProduto, idEncomenda);

    } else if (idProduto >= sistema.numeroProdutos) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idProduto, idEncomenda);

    } else if (quantidade > sistema.stock[idProduto]) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idProduto, idEncomenda);

    } else if (sistema.encomendas[idEncomenda].pesoTotal + sistema.produtos[idProduto].peso*quantidade > MAX_PESO_ENCOMENDA) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idProduto, idEncomenda);

    } else {
        adicionaProdutoEncomend_aux(idEncomenda, idProduto, quantidade);
    }
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*Adiciona um produto a um encomenda.(aux)*/
void adicionaProdutoEncomend_aux(int idEncomenda, int idProduto, int quantidade) {
    Encomenda encomenda;
    int novoProduto = 1, i;

    encomenda = sistema.encomendas[idEncomenda];
    /*verifica se ja existe esse produto, se ja existir aumenta a quantidade*/
    for (i = 0; i < encomenda.numeroProdutosEncomenda; i++) {
        if (encomenda.produtos[i][0] == idProduto) {
            encomenda.produtos[i][1] += quantidade;
            novoProduto = 0;
            break;
        }
    }
    /*se nao existir insere [idProduto, quantidade]*/
    if (novoProduto) {
        /*insere [idProduto, quantidade]*/
        encomenda.produtos[i][0] = idProduto;
        encomenda.produtos[i][1] = quantidade;
        encomenda.numeroProdutosEncomenda++;
    }
    atualizaStock(idProduto, -quantidade);
    encomenda.pesoTotal += sistema.produtos[idProduto].peso*quantidade;

    sistema.encomendas[idEncomenda] = encomenda;
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*r - remove stock a um produto existente.*/
void removeStockProduto() {
    int idProduto, quantidade;

    scanf("%d:%d\n", &idProduto, &quantidade);

    if (idProduto >= sistema.numeroProdutos) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idProduto);

    } else if (quantidade > sistema.stock[idProduto]) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idProduto);

    } else {
        atualizaStock(idProduto, -quantidade);
    }
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*R - remove um produto de uma encomenda.*/
void removeProdutoEncomenda() {
    Encomenda encomenda;
    int idEncomenda, idProduto, quantidade = 0, i;

    scanf("%d:%d\n", &idEncomenda, &idProduto);

    if (idEncomenda >= sistema.numeroEncomendas) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idProduto, idEncomenda);

    } else if (idProduto >= sistema.numeroProdutos) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idProduto, idEncomenda);

    } else {
        encomenda = sistema.encomendas[idEncomenda];
        /*da shift a esquerda ao vetor das encomendas apartir do produto a remover*/
        for (i = 0; i < encomenda.numeroProdutosEncomenda; i++) {
            if (encomenda.produtos[i][0] == idProduto) {
                encomenda.numeroProdutosEncomenda--;
                quantidade = encomenda.produtos[i][1];
            }
            if (quantidade) {
                encomenda.produtos[i][0] = encomenda.produtos[i + 1][0];
                encomenda.produtos[i][1] = encomenda.produtos[i + 1][1];
            }
        }
        atualizaStock(idProduto, quantidade);
        encomenda.pesoTotal -= sistema.produtos[idProduto].peso*quantidade;

        sistema.encomendas[idEncomenda] = encomenda;
    }
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*C - calcula o custo de uma encomenda.*/
void calculaCusto() {
    Encomenda encomenda;
    Produto produto;
    int idEncomenda, quantidade, custo = 0, i;

    scanf("%d\n", &idEncomenda);

    if (idEncomenda >= sistema.numeroEncomendas) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idEncomenda);

    } else {
        encomenda = sistema.encomendas[idEncomenda];
        for (i = 0; i < encomenda.numeroProdutosEncomenda; i++) {
            produto = sistema.produtos[encomenda.produtos[i][0]];
            quantidade = encomenda.produtos[i][1];
            custo += produto.preco*quantidade;
        }
        printf("Custo da encomenda %d %d.\n", idEncomenda, custo);
    }
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*p - altera o preco de um produto existente no sistema.*/
void alteraPreco() {
    int idProduto, preco;

    scanf("%d:%d\n", &idProduto, &preco);

    if (idProduto >= sistema.numeroProdutos) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idProduto);

    } else {
        sistema.produtos[idProduto].preco = preco;
    }
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*E - lista a descricao e a quantidade de um produto numa encomenda.*/
void printProdutoEncomenda() {
    Encomenda encomenda;
    int idEncomenda, idProduto, quantidade = 0, i;

    scanf("%d:%d\n", &idEncomenda, &idProduto);

    if (idEncomenda >= sistema.numeroEncomendas) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idEncomenda);

    } else if (idProduto >= sistema.numeroProdutos) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idProduto);

    } else {
        encomenda = sistema.encomendas[idEncomenda];
        for (i = 0; i < encomenda.numeroProdutosEncomenda; i++) {
            if (encomenda.produtos[i][0] == idProduto) {
                quantidade = encomenda.produtos[i][1];
                break;
            }
        }
        printf("%s %d.\n", sistema.produtos[idProduto].descricao, quantidade);
    }
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*m - lista o identificador da encomenda em que o produto dado ocorre mais vezes.
Se houver 2 ou mais encomendas nessa situacao, devera imprimir a encomenda de menor id.*/
void produtoMaiorOcorrencia() {
    Encomenda encomenda;
    int idProduto, idEncomenda, max = 0, i, j;

    scanf("%d\n", &idProduto);

    if (idProduto >= sistema.numeroProdutos) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idProduto);

    } else {
        for (i = 0; i < sistema.numeroEncomendas; i++) {
            encomenda = sistema.encomendas[i];
            for (j = 0; j < encomenda.numeroProdutosEncomenda; j++) {
                if (encomenda.produtos[j][0] == idProduto && encomenda.produtos[j][1] > max) {
                    max = encomenda.produtos[j][1];
                    idEncomenda = i;/*vai ser sempre o menor pois as encomendas estao ordenadas por ordem crescente*/
                }
            }
        }
        if (max) {
            printf("Maximo produto %d %d %d.\n", idProduto, idEncomenda, max);
        }
    }
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*l - lista todos os produtos existentes no sistema por ordem crescente de preco.
Se houver 2 ou mais produtos com o mesmo preco, devera imprimir esses por ordem crescente de id de produto.*/
void printProdutos() {
    Produto produto;
    int lista[MAX_PRODUTOS_STOCK][2];/*[preco, idProduto]*/
    int i;

    printf("Produtos\n");

    for (i = 0; i < sistema.numeroProdutos; i++) {
        lista[i][0] = sistema.produtos[i].preco;
        lista[i][1] = i;
    }
    /*Ordena a lista por ordem crescente de preco, por ordem crescente de id.*/
    quicksort(lista, 0, sistema.numeroProdutos - 1, cmp_preco);

    for (i = 0; i < sistema.numeroProdutos; i++) {
        produto = sistema.produtos[lista[i][1]];
        printf("* %s %d %d\n", produto.descricao, produto.preco, sistema.stock[lista[i][1]]);
    }
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*L - lista todos os produtos de uma encomenda por ordem alfabetica da descricao.*/
void printEncomenda() {
    Encomenda encomenda;
    Produto produto;
    int lista[MAX_PRODUTOS_ENCOMENDA][2];/*[idProduto, quantidade]*/
    int idEncomenda, i;

    scanf("%d\n", &idEncomenda);

    if (idEncomenda >= sistema.numeroEncomendas) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idEncomenda);

    } else {
        encomenda = sistema.encomendas[idEncomenda];
        printf("Encomenda %d\n", idEncomenda);

        for (i = 0; i < encomenda.numeroProdutosEncomenda; i++) {
            lista[i][0] = encomenda.produtos[i][0];/*identificador do produto*/
            lista[i][1] = encomenda.produtos[i][1];/*quantidade*/
        }

        /*Ordena a lista por ordem alfabetica.*/
        quicksort(lista, 0, encomenda.numeroProdutosEncomenda - 1, cmp_desc);

        for (i = 0; i < encomenda.numeroProdutosEncomenda; i++) {
            produto = sistema.produtos[lista[i][0]];
            printf("* %s %d %d\n", produto.descricao, produto.preco, lista[i][1]);
        }
    }
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*Adiciona ou retira produto do stock.*/
void atualizaStock(int idProduto, int quantidade) {
    sistema.stock[idProduto] += quantidade;
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*Ordena o vetor "lista" apartir de l e ate r, usando a funcao comparacao para comparar os elementos da lista.*/
void quicksort(int lista[][2], int l, int r, int comparacao()) {
    int i;
    if (r <= l) {
        return;
    }

    i = partition(lista, l, r, comparacao);
    quicksort(lista, l, i - 1, comparacao);
    quicksort(lista, i + 1, r, comparacao);
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*coloca todos os elementos menores que o ultimo(pivot) a esquerda e os maiores a direita, retorna a posicao do pivot no final.
Usa a funcao comparacao para comparar os elementos da lista.*/
int partition(int lista[][2], int l, int r, int comparacao()) {
    int pivot[2];
    int i = l - 1;
    int j = r;

    pivot[0] = lista[r][0];
    pivot[1] = lista[r][1];

    while (i < j) {
        while (comparacao(lista[++i], pivot));
        while (comparacao(pivot, lista[--j]))
            if (j == l)
                break;

        if (i < j)
            exch(lista[i], lista[j]);
    }
    exch(lista[i], lista[r]);
    return i;
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*Compara pelo preco, se forem iguais compara pelo id.*/
int cmp_preco(int a[2], int b[2]) {
    return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
}

/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/*Compara pela descricao.*/
int cmp_desc(int a[2], int b[2]) {
    return strcmp(sistema.produtos[a[0]].descricao, sistema.produtos[b[0]].descricao) < 0;
}

/*------------------------------------------------------------------------------------------------------------------------------*/
