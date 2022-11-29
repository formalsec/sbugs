#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Numero maximo de produtos */
#define MAX_PROD 10000

/* Numero maximo de encomendas */
#define MAX_ENC 500

/* Peso maximo de uma encomenda / Numero maximo de produtos numa encomenda */
#define MAX_PESO 200

/* Comprimento maximo da descricao de um produto */
#define MAX_DESC 64

/* Valores Logicos */

#define FALSE 0
#define TRUE 1

/* Abstracoes */

#define desc(prod) reg_prods[prod].desc
#define preco_prod(prod) reg_prods[prod].preco
#define peso_prod(prod) reg_prods[prod].peso
#define stock(prod) reg_prods[prod].stock
#define idp_prod_enc(enc, prod) reg_encs[enc].idp[prod]
#define idps_enc(enc) reg_encs[enc].idp
#define qtd_prod_enc(enc, prod) reg_encs[enc].qtd[prod]
#define qtds_enc(enc) reg_encs[enc].qtd
#define peso_enc(enc) reg_encs[enc].peso
#define preco_enc(enc) reg_encs[enc].preco
#define num_prods(enc) reg_encs[enc].num_prods

/* Definicao das Estruturas */

typedef struct {
    char desc[MAX_DESC];
    int idp;
    int preco;
    int peso;
    int stock;
} produto;

typedef struct {
    int idp[MAX_PESO];
    int qtd[MAX_PESO];
    int peso;
    int preco;
    int num_prods;
} encomenda;

/* Prototipos das Funcoes */

void novo_prod();
void mais_stock();
void nova_enc();
void novo_prod_enc();
void menos_stock();
void remover_prod_enc();
void custo_enc();
void alt_preco();
void quant_prod_enc();
void enc_maior_qtd_prod();
void listar_prods();
void listar_prods_enc();
void inicializar_vetor(int [], int , int );
void remover_elemento(int , int [], int , int );
void mergesort(produto [], int , int , int );
void merge_preco(produto [], int , int , int );
void merge_desc(produto [], int , int , int );

/* Declaracao de Variaveis Globais */

/* Vetor com todos os produtos registados no sistema */
produto reg_prods[MAX_PROD];

/* Vetor com todas as encomendas criadas */
encomenda reg_encs[MAX_ENC];

/* Vetor auxiliar para o merge sort */
produto aux[MAX_PROD];

/* Variavel global estatica que contem o id do proximo produto */
static int idp;

/* Variavel global estatica que contem o id da proxima encomenda */
static int ide;

/* Implementacao das Funcoes */

/* Le o primeiro caracter de cada linha e chama a funcao correspondente ao comando a executar */
int main() {
    char c;

    /* Quando c == 'x' o programa termina */
    while ((c = getchar()) != 'x')
        switch (c) {
            case 'a':
                novo_prod();
                break;
            case 'q':
                mais_stock();
                break;
            case 'N':
                nova_enc();
                break;
            case 'A':
                novo_prod_enc();
                break;
            case 'r':
                menos_stock();
                break;
            case 'R':
                remover_prod_enc();
                break;
            case 'C':
                custo_enc();
                break;
            case 'p':
                alt_preco();
                break;
            case 'E':
                quant_prod_enc();
                break;
            case 'm':
                enc_maior_qtd_prod();
                break;
            case 'l':
                listar_prods();
                break;
            case 'L':
                listar_prods_enc();
        }

    return 0;
}

/* Adiciona um novo produto ao sistema */
void novo_prod() {
    produto prod;

    scanf(" %[^:]:%d:%d:%d", prod.desc, &prod.preco, &prod.peso, &prod.stock);
    prod.idp = idp;
    reg_prods[idp] = prod;
    printf("Novo produto %d.\n", idp);
    idp++;
}

/* Adiciona stock a um produto existente no sistema */
void mais_stock() {
    int prod, qtd;

    scanf(" %d:%d", &prod, &qtd);

    if (prod >= idp)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prod);
    else
        stock(prod) += qtd;
}

/* Cria uma nova encomenda */
void nova_enc() {
    encomenda enc = {{0}, {0}, 0, 0, 0};
    /* Inicializa o vetor dos ids dos produtos da encomenda com o valor -1, 
       representando que todas as posicoes se encontram vazias, ou seja, sem produtos */
    inicializar_vetor(enc.idp, MAX_PESO, -1);
    reg_encs[ide] = enc;
    printf("Nova encomenda %d.\n", ide);
    ide++;
}

/* Adiciona um produto a uma encomenda */
void novo_prod_enc() {
    int i, id, enc, prod, qtd, existe = FALSE;

    scanf(" %d:%d:%d", &enc, &prod, &qtd);

    if (enc >= ide)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
    else if (prod >= idp)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
    else if ((stock(prod) - qtd) < 0)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod, enc);
    else if((peso_prod(prod) * qtd + peso_enc(enc)) > MAX_PESO)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod, enc);
    else {
        /* Percorre o vetor dos ids dos produtos da encomenda para verificar se o produto ja se encontra na mesma */
        for (i = 0; i < num_prods(enc); i++)
            if (idp_prod_enc(enc, i) == prod) {
                existe = TRUE;
                id = i;
                break;
            }

        /* Se ja estiver na encomenda, adiciona a nova quantidade 'a quantidade ja existente */
        if (existe)
            qtd_prod_enc(enc, id) += qtd;
        /* Caso contrario, adiciona o produto 'a encomenda */
        else {
            id = num_prods(enc);
            idp_prod_enc(enc, id) = prod;
            qtd_prod_enc(enc, id) = qtd;
            num_prods(enc)++;
        }
        /* No final, atualiza o peso e o preco da encomenda, bem como o stock do produto */
        peso_enc(enc) += (peso_prod(prod) * qtd);
        preco_enc(enc) += (preco_prod(prod) * qtd);
        stock(prod) -= qtd;
    }
}

/* Remove stock a um produto existente */
void menos_stock() {
    int prod, qtd;

    scanf(" %d:%d", &prod, &qtd);

    if (prod >= idp)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod);
    else if ((stock(prod) - qtd) < 0)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, prod);
    else
        stock(prod) -= qtd;
}

/* Remove um produto de uma encomenda */
void remover_prod_enc() {
    int enc, prod, id = -1, i;

    scanf(" %d:%d", &enc, &prod);

    if (enc >= ide)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
    else if (prod >= idp)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
    else {
        /* Percorre o vetor dos ids dos produtos da encomenda para verificar se o produto se encontra na mesma */
        for (i = 0; i < num_prods(enc); i++)
            if (idp_prod_enc(enc, i) == prod) {
                id = i;
                break;
            }
        /* Se o idp for maior ou igual a zero quer dizer que o produto se encontra 
           na encomenda e este e' removido da mesma, caso contrario nada acontece */
        if (id >= 0) {
            peso_enc(enc) -= (peso_prod(prod) * qtd_prod_enc(enc, id));
            preco_enc(enc) -= (preco_prod(prod) * qtd_prod_enc(enc, id));
            stock(prod) += qtd_prod_enc(enc, id);
            remover_elemento(id, idps_enc(enc), -1, MAX_PESO);
            remover_elemento(id, qtds_enc(enc), 0, MAX_PESO);
            num_prods(enc)--;
        }
    }
}

/* Calcula o custo de uma encomenda */
void custo_enc() {
    int enc;

    scanf(" %d", &enc);

    if (enc >= ide)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
    else
        printf("Custo da encomenda %d %d.\n", enc, preco_enc(enc));
}

/* Altera o preco de um produto existente no sistema */
void alt_preco() {
    int prod, preco, id, i, j, existe = FALSE;

    scanf(" %d:%d", &prod, &preco);

    if (prod >= idp)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prod);
    else {
        /* Percorre o vetor dos ids dos produtos de cada encomenda para verificar se o produto se encontra na mesma */
        for (i = 0; i < ide; i++) {
            for (j = 0; j < num_prods(i); j++) {
                if (idp_prod_enc(i, j) == prod) {
                    existe = TRUE;
                    id = j;
                    break;
                }
            }
            /* Se o produto se encontrar na encomenda, atualiza o seu preco */
            if (existe) {
                preco_enc(i) += (qtd_prod_enc(i, id) * (preco - preco_prod(prod)));
                existe = FALSE;
            }
        }
        /* No final, atualiza o preco do produto no sistema */
        preco_prod(prod) = preco;
    }
}

/* Retorna a descricao e a quantidade de um produto numa dada encomenda */
void quant_prod_enc() {
    int enc, prod, i, id, existe = FALSE, qtd = 0;

    scanf(" %d:%d", &enc, &prod);

    if (enc >= ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
    else if (prod >= idp)
        printf("Impossivel listar produto %d. Produto inexistente.\n", prod);
    else {
        /* Percorre o vetor dos ids dos produtos da encomenda para verificar se o produto se encontra na mesma */
        for (i = 0; i < num_prods(enc); i++)
            if (idp_prod_enc(enc, i) == prod) {
                id = i;
                existe = TRUE;
                break;
            }
        /* Se o produto se encontrar na encomenda, guarda a sua quantidade */
        if (existe)
            qtd = qtd_prod_enc(enc, id);

        printf("%s %d.\n", desc(prod), qtd);
    }
}

/* Retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
void enc_maior_qtd_prod() {
    int prod, qtd = 0, enc = -1, i, j, id, existe = FALSE;

    scanf(" %d", &prod);

    if (prod >= idp)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod);
    else if (ide > 0) {
        /* Percorre o vetor dos ids dos produtos de cada encomenda para verificar se o produto se encontra na mesma */
        for (i = 0; i < ide; i++) {
            for (j = 0; j < num_prods(i); j++)
                if (idp_prod_enc(i, j) == prod) {
                    existe = TRUE;
                    id = j;
                    break;
                }
            /* Se o produto existir na encomenda, compara a sua quantidade com a quantidade maxima ate agora e,
               se for superior, guarda o id da encomenda e a quantidade do produto na mesma. Nao e' necessario
               comparar o id das encomendas uma vez que estas sao percorridas por ordem crescente do ide */
            if (existe && qtd < qtd_prod_enc(i, id)) {
                qtd = qtd_prod_enc(i, id);
                enc = i;
            }
            existe = FALSE;
        }
        if (qtd > 0)
            printf("Maximo produto %d %d %d.\n", prod, enc, qtd);
    }
}

/* Lista todos os produtos existentes no sistema por ordem crescente de preco */
void listar_prods() {
    int i;
    produto prods[MAX_PROD];

    /* Copia todos os produtos do sistema para um novo vetor que sera ordenado */
    for (i = 0; i < idp; i++)
        prods[i] = reg_prods[i];

    mergesort(prods, 0, idp - 1, TRUE);

    printf("Produtos\n");

    for (i = 0; i < idp; i++)
        printf("* %s %d %d\n", prods[i].desc, prods[i].preco, prods[i].stock);
}

/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
void listar_prods_enc() {
    int enc, i, j, id;
    produto prods[MAX_PESO];

    scanf(" %d", &enc);

    if (enc >= ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
    else {
        /* Copia todos os produtos da encomenda para um novo vetor que sera ordenado */
        for (i = 0; i < num_prods(enc); i++) {
            id = idp_prod_enc(enc, i);
            prods[i] = reg_prods[id];
        }

        mergesort(prods, 0, num_prods(enc) - 1, FALSE);

        printf("Encomenda %d\n", enc);

        for (i = 0; i < num_prods(enc); i++) {
            /* Guarda o id do produto dentro da encomenda para se aceder depois 'a sua quantidade na mesma */
            for (j = 0; j < num_prods(enc); j++)
                if (prods[i].idp == idp_prod_enc(enc, j)) {
                    id = j;
                    break;
                }
            printf("* %s %d %d\n", prods[i].desc, prods[i].preco, qtd_prod_enc(enc, id));
        }
    }
}

/* Funcoes Auxiliares */

/* Inicializa um dado vetor com um dado valor */
void inicializar_vetor(int v[], int dim, int valor) {
    int i;

    for (i = 0; i < dim; i++)
        v[i] = valor;
}

/* Remove o elemento que se encontra numa dada posicao de um dado vetor */
void remover_elemento(int id, int v[], int valor, int dim) {
    int i;

    /* Recua todos os elementos do vetor uma posicao, ate ao penultimo */
    for (i = id; i < dim - 1; i++)
        v[i] = v[i + 1];
    
    /* A ultima posicao do vetor fica com o valor dado */
    v[dim - 1] = valor;
}

/* Ordena os produtos do vetor segundo um dado criterio (preco ou descricao) */
void mergesort(produto v[], int esq, int dir, int preco) {
    int meio = (dir + esq) / 2;

    if (dir <= esq)
        return;

    mergesort(v, esq, meio, preco);
    mergesort(v, meio + 1, dir, preco);

    /* Se preco == TRUE, entao ordena segundo os precos */
    if (preco)
        merge_preco(v, esq, meio, dir);
    /* Caso contrario, ordena segunda as descricoes */
    else
        merge_desc(v, esq, meio, dir);
}

/* Funcao auxiliar para ordenar os produtos por ordem crescente de preco */
void merge_preco(produto v[], int esq, int meio, int dir) {
    int i, j, k;

    for (i = meio + 1; i > esq; i--)
        aux[i - 1] = v[i - 1];

    for (j = meio; j < dir; j++)
        aux[dir + meio - j] = v[j + 1];

    for (k = esq; k <= dir; k++)
        if (aux[j].preco < aux[i].preco || i > meio)
            v[k] = aux[j--];
        else
            v[k] = aux[i++];
}

/* Funcao auxiliar para ordenar os produtos por ordem alfabetica da descricao */
void merge_desc(produto v[], int esq, int meio, int dir) {
    int i, j, k;

    for (i = meio + 1; i > esq; i--)
        aux[i - 1] = v[i - 1];

    for (j = meio; j < dir; j++)
        aux[dir + meio - j] = v[j + 1];

    for (k = esq; k <= dir; k++)
        /* Compara as descricoes do i e do j e, caso o resultado seja negativo,
           quer dizer que a do j e' alfabeticamente menor */
        if (strcmp(aux[j].desc, aux[i].desc) < 0)
            v[k] = aux[j--];
        else
            v[k] = aux[i++];
}