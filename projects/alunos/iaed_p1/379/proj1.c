#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Os numeros maximos de valores armazenados. */
#define PROD_MAX 10000
#define ENCOM_MAX 500
#define DESC_MAX 63
#define PESO_MAX 200

/* funcao auxiliar para trocar a posicao de dois produtos. */
#define exch(A, B) { Produto t = A; A = B; B = t; }

/* estrutura que contem as informacoes de um produto. */
typedef struct {
    int id;
    char nome[DESC_MAX];
    int preco;
    int peso;
    int qtd;
} Produto;

/* estrutura que contem as informacoes de uma encomenda. */
typedef struct {
    Produto produtos[PESO_MAX];
    int np; /* numero de produtos na encomenda */
} Encomenda;

/* lista de produtos existentes no sistema. */
Produto produtos[PROD_MAX];
/* lista de encomendas existentes no sistema. */
Encomenda encomendas[ENCOM_MAX];

/* numero de produtos e encomendas armazenados.  */
int prod_atual = 0;
int encom_atual = 0;

/* Adiciona um produto ao sistema. */
void a() {
    scanf(" %[^:]:%d:%d:%d", produtos[prod_atual].nome, &produtos[prod_atual].preco, &produtos[prod_atual].peso, &produtos[prod_atual].qtd);
    produtos[prod_atual].id = prod_atual;
    printf("Novo produto %d.\n", prod_atual++);
}

/* Adiciona stock a um produto existente no sistema. */
void q() {
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if (idp >= prod_atual)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        produtos[idp].qtd += qtd;
}

/* Cria uma nova encomenda. */
void N() {
    printf("Nova encomenda %d.\n", encom_atual++);
}

/* Adiciona um produto a uma encomenda. */
void A() {
    int ide, idp, qtd, i, peso, idpe = -1; /* idpe: id do produto na encomenda (-1 = inexistente) */
    scanf("%d:%d:%d", &ide, &idp, &qtd);

    peso = produtos[idp].peso * qtd; /* inicio do calculo do preco */
    /* itera entre os produtos da encomenda */
    for (i = 0; i < encomendas[ide].np; i++) {
        peso += encomendas[ide].produtos[i].peso * encomendas[ide].produtos[i].qtd; /* adiciona o peso atual da encomenda */
        if (encomendas[ide].produtos[i].id == idp) /* verifica se o produto esta na encomenda */
            idpe = i; /* se sim, guarda o seu id */
    }
    if (ide >= encom_atual)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp >= prod_atual)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (qtd > produtos[idp].qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if (peso > PESO_MAX)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else if (idpe != -1) { /* caso o produto ja exista na encomenda, */
        encomendas[ide].produtos[idpe].qtd += qtd; /* adiciona stock a encomenda */
        produtos[idp].qtd -= qtd; /* e remove stock do sistema */
    }
    else { /* caso o produto nao exista na encomenda */
        encomendas[ide].produtos[encomendas[ide].np] = produtos[idp]; /* adiciona-o a encomenda */
        encomendas[ide].produtos[encomendas[ide].np].qtd = qtd; /* coloca o stock */
        encomendas[ide].np++; /* atualiza o numero de produtos */
        produtos[idp].qtd -= qtd; /* e remove stock do sistema */
    }
}

/* Remove stock a um produto existente. */
void r() {
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if (idp >= prod_atual)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if (qtd > produtos[idp].qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else
        produtos[idp].qtd -= qtd;
}

/* Remove um produto de uma encomenda. */
void R() {
    int i, ide, idp, idpe = -1; /* idpe: id do produto na encomenda (-1 = inexistente) */
    scanf("%d:%d", &ide, &idp);
    if (ide >= encom_atual)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp >= prod_atual)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else {
        for (i = 0; i < encomendas[ide].np; i++) /*procura o idp na lista de produros da encomenda */
            if (encomendas[ide].produtos[i].id == idp)
                idpe = i;

        if (idpe != -1) { /* caso exista, */
            produtos[idp].qtd += encomendas[ide].produtos[idpe].qtd; /* devolve a sua quantidade ao sistema */
            encomendas[ide].produtos[idpe].qtd = 0; /* e retira-a da encomenda */
        }
    }
}

/* Calcula o custo de uma encomenda. */
void C() {
    int i, ide, custo = 0;
    scanf("%d", &ide);
    if (ide >= encom_atual)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else {
        for (i = 0; i < encomendas[ide].np; i++) /* itera os produtos da encomenda e calcula o seu custo */
            custo += encomendas[ide].produtos[i].qtd * encomendas[ide].produtos[i].preco;
        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}

/* 	Altera o preco de um produto existente no sistema. */
void p() {
    int  i, j, idp, preco;
    scanf("%d:%d", &idp, &preco);
    if (idp >= prod_atual)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else {
        produtos[idp].preco = preco; /* altera o preco no sistema */

        /* procura produtos com o mesmo id nas encomendas e muda o respetivo preco */
        for (i = 0; i < encom_atual; i++)
            for (j = 0; j < encomendas[i].np; j++)
                if (encomendas[i].produtos[j].id == idp)
                    encomendas[i].produtos[j].preco = preco;
    }
}

/* 	Retorna a descricao e a quantidade de um produto numa dada encomenda. */
void E() {
    int i, ide, idp, idpe = -1; /* idpe: id do produto na encomenda (-1 = inexistente) */
    scanf("%d:%d", &ide, &idp);
    if (ide >= encom_atual)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (idp >= prod_atual)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else {
        for (i = 0; i < encomendas[ide].np; i++) /* procura o idp na lista de produtos da encomenda */
            if (encomendas[ide].produtos[i].id == idp)
                idpe = i;
        if (idpe != -1) /* caso exista, printa a sua quantidade */
            printf("%s %d.\n", produtos[idp].nome, encomendas[ide].produtos[idpe].qtd);
        else /* senao, printa 0 na quantidade */
            printf("%s 0.\n", produtos[idp].nome);
    }
}

/* Retorna o identificador da encomenda em que um dado produto ocorre mais vezes. */
void m() {
    int i, j, idp, ide, qtd = 0;
    scanf("%d", &idp);
    if (idp >= prod_atual)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else {
        /* itera entre todos os produtos de todas as encomendas */
        for (i = 0; i < encom_atual; i++)
            for (j = 0; j < encomendas[i].np; j++)
                /* se o produto tiver o id fornecido e uma quantidade superior a atual */
                if (encomendas[i].produtos[j].id == idp && encomendas[i].produtos[j].qtd > qtd) {
                        qtd = encomendas[i].produtos[j].qtd; /* atualiza a quantidade */
                        ide = i; /* e guarda o seu id */
                    }
        if (qtd) { /* se a quantidade for maior que 0, printa-a com os respetivos id's */
            printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
        }
    }
}

/* compara os precos de dois produtos */
int cmppreco(Produto prod1, Produto prod2) {
    return (prod1.preco != prod2.preco) ? (prod1.preco < prod2.preco) : (prod1.id < prod2.id);
}

/* compara os nomes de dois produtos */
int cmpdesc(Produto prod1, Produto prod2) {
    return(strcmp(prod1.nome, prod2.nome) < 0);
}

/* ordena os produtos de uma lista */
void quicksort(Produto lista[], int l, int r, int (*cmp)()) { /* cmp: funcao comparativa a ser utilizada */
    int i = l - 1, j = r; /* iteradores da "esquerda" e da "direita" */
    Produto v = lista[r]; /* inicializa o pivot */

    if (r <= l) /* condicao terminal */
        return;

    /* enquanto o iterador da esquerda nao for maior do que o da direita */
    while (i < j) {
        while (cmp(lista[++i], v)); /* vai avancando o iterador da esquerda, ate igualar o pivot */
        while (cmp(v, lista[--j])){ /* vai diminuindo o iterador da direita, ate igualar o pivot */
            if (j == l)
                break;
        }
        if (i < j) /* se o interador da esquerda ainda for menor que o da direita */
            exch(lista[i], lista[j]); /* troca os elementos */
    }
    exch(lista[i], lista[r]); /* colocacao do pivot na sua respetiva posicao */

    quicksort(lista, l, i - 1, cmp); /* recursao do "lado esquerdo" */
    quicksort(lista, i + 1, r, cmp); /* recursao do "lado direito" */
}

/* Lista todos os produtos existentes no sistema por ordem crescente de preco. */
void l() {
    Produto lista[PROD_MAX]; /* lista de produtos auxiliar para ordenacao */
    int i;
    /* cria uma copia da lista de produtos */
    for (i = 0; i < prod_atual; i++)
        lista[i] = produtos[i];

    quicksort(lista, 0, prod_atual - 1, cmppreco); /* ordena a lista */

    /* printa o output */
    printf("Produtos\n");
    for (i = 0; i < prod_atual; i++)
        printf("* %s %d %d\n", lista[i].nome, lista[i].preco, lista[i].qtd);
}

/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao. */
void L() {
    int ide, i;

    scanf("%d", &ide);
    if (ide >= encom_atual)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else {
        quicksort(encomendas[ide].produtos, 0, encomendas[ide].np - 1, cmpdesc); /* ordena a lista */

        /* printa o output */
        printf("Encomenda %d\n", ide);
        for (i = 0; i < encomendas[ide].np; i++)
            if (encomendas[ide].produtos[i].qtd > 0)
                printf("* %s %d %d\n",  encomendas[ide].produtos[i].nome,
                                        encomendas[ide].produtos[i].preco,
                                        encomendas[ide].produtos[i].qtd);
    }
}

/* Le um comando e chama a funcao com base no comando lido. */
int main() {
    char cmdo; /* variavel para a leitura do comando a executar */

    while (1) {
        scanf("%c", &cmdo);
        switch (cmdo) {
        case 'a':
            a();
            break;

        case 'q':
            q();
            break;

        case 'N':
            N();
            break;

        case 'A':
            A();
            break;

        case 'r':
            r();
            break;

        case 'R':
            R();
            break;

        case 'C':
            C();
            break;

        case 'p':
            p();
            break;

        case 'E':
            E();
            break;

        case 'm':
            m();
            break;

        case 'l':
            l();
            break;

        case 'L':
            L();
            break;

        case 'x':       /* caso o comando seja 'x', o programa termina */
            goto sair;
            break;
        }
    }
    sair:
    return 0;
}
