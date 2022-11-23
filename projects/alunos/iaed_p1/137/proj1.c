#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_DESCRICAO 64 /* maximo de caracteres na descricao de um produto (incluindo o caracter final) */
#define MAX_PESO_ENCOM 200 /* peso maximo de uma encomenda, que e igual ao numero maximo de produtos numa encomenda */
#define MAX_PRODUTOS 10000 /* maximo de produtos no sistema */
#define MAX_ENCOMENDAS 500 /* maximo de encomendas no sistema */
#define NADA -1 /* identificador dos produtos de uma encomenda quando estes nao correspondem a nada (sao espacos vazios da tabela) */

/* Estrutura de um produto do sistema */
typedef struct {
    int identificador;
    char descricao[MAX_DESCRICAO];
    int preco;
    int peso;
    int quantidade;
} produto;

/* Estrutura de um produto pertencente a uma encomenda */
typedef struct {
    int identificador; /* identificador do produto */
    int quantidade;   /*quantidade do produto na encomenda*/
} produto_encomenda;

/* Estrutura de uma encomenda */
typedef struct {
    int identificador;
    produto_encomenda produtos[MAX_PESO_ENCOM]; /* tabela com os produtos da encomenda*/
    int peso; /* peso total da encomenda*/
} encomenda;

/* Funcoes dos comandos */
void comando_a(produto produtos[]);
void comando_q(produto produtos[]);
void comando_N(encomenda encomendas[]);
void comando_A(produto produtos[], encomenda encomendas[]);
void comando_r(produto produtos[]);
void comando_R(produto produtos[], encomenda encomendas[]);
void comando_C(produto produtos[], encomenda encomendas[]);
void comando_p(produto produtos[]);
void comando_E(produto produtos[], encomenda encomendas[]);
void comando_m(encomenda encomendas[]);
void comando_l(produto produtos[]);
void comando_L(produto produtos[], encomenda encomendas[]);

/* Funcoes auxiliares */
int produto_existe(int idp); /* Ve se o produto existe */
int encomenda_existe(int ide); /* Ve se a encomenda existe */
int indice_produto_encomenda(encomenda encomendas[], int ide, int idp); /* Devolve o indice de um produto na tabela de produtos de uma encomenda */
void mergesort_preco(produto produtos[], int left, int right); /* Ordena produtos por ordem crescente do preco */
void merge_preco(produto produtos[], int left, int m, int right); /* Funcao auxiliar da mergesort_preco */
void mergesort_descricao(produto produtos[], int left, int right); /* Ordena produtos por ordem alfabetica da descricao */
void merge_descricao(produto produtos[], int left, int m, int right); /* Funcao auxiliar da mergesort_descricao */

/* Variaveis globais */
int conta_produtos = 0; /* quantos produtos estao no sistema e qual o indice do proximo na tabela */
int conta_encomendas = 0; /* quantas encomendas estao no sistema e qual o indice da proxima na tabela */


/* Funcao main: Le os comandos introduzidos pelo utilizador e chama as funcoes correspondentes */
int main() {
    char comando;
    produto produtos_sistema[MAX_PRODUTOS]; /* todos os produtos no sistema*/
    encomenda encomendas_sistema[MAX_ENCOMENDAS]; /* todas as encomendas no sistema*/

    while (1) {
        comando = getchar();
        switch (comando) {
            case 'a': {
                comando_a(produtos_sistema);
                break;
            }
            case 'q': {
                comando_q(produtos_sistema);
                break;
            }
            case 'N': {
                comando_N(encomendas_sistema);
                break;
            }
            case 'A': {
                comando_A(produtos_sistema, encomendas_sistema);
                break;
            }
            case 'r': {
                comando_r(produtos_sistema);
                break;
            }
            case 'R': {
                comando_R(produtos_sistema, encomendas_sistema);
                break;
            }
            case 'C': {
                comando_C(produtos_sistema, encomendas_sistema);
                break;
            }
            case 'p': {
                comando_p(produtos_sistema);
                break;
            }
            case 'E': {
                comando_E(produtos_sistema, encomendas_sistema);
                break;
            }
            case 'm': {
                comando_m(encomendas_sistema);
                break;
            }
            case 'l': {
                comando_l(produtos_sistema);
                break;
            }
            case 'L': {
                comando_L(produtos_sistema, encomendas_sistema);
                break;
            }
            case 'x': {
                /* Programa termina */
                return 0; 
            }
        }
        getchar();
    }
    return 0;
}


/* Recebe o identificador de um produto e verifica se ele existe no sistema */
int produto_existe(int idp) {
    return (idp >= 0 && idp < conta_produtos);
}


/* Recebe o identificador de uma encomenda e verifica se ela existe no sistema */
int encomenda_existe(int ide) {
    return (ide >= 0 && ide < conta_encomendas);
}


/* Funcao auxiliar: devolve o indice da posicao que o produto com o identificador idp ocupa na tabela de produtos da encomenda ide */
int indice_produto_encomenda(encomenda encomendas[], int ide, int idp) {
    int i;
    for (i = 0; i < MAX_PESO_ENCOM; i++)
        if (encomendas[ide].produtos[i].identificador == idp)
            return i;
    return NADA;
}


/* Adiciona um novo produto ao sistema: Le " descricao:preco:peso:quantidade" e cria um novo produto com os valores lidos */
void comando_a(produto produtos[]) {
    if (conta_produtos < MAX_PRODUTOS) {
        scanf(" %[^:]:%d:%d:%d", produtos[conta_produtos].descricao, &produtos[conta_produtos].preco, &produtos[conta_produtos].peso, &produtos[conta_produtos].quantidade);
        produtos[conta_produtos].identificador = conta_produtos;
        printf("Novo produto %d.\n", conta_produtos);
        conta_produtos++;    
    }
}


/* Adiciona stock a um produto existente no sistema: Le " idp:qtd" e adiciona o valor qtd 'a quantidade em stock do produto idp */
void comando_q(produto produtos[]) {
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);

    if ( produto_existe(idp) )
        produtos[idp].quantidade += qtd;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}


/* Cria nova encomenda: Cria uma nova encomenda vazia */
void comando_N(encomenda encomendas[]) {
    int i;

    if (conta_encomendas < MAX_ENCOMENDAS) {
        encomendas[conta_encomendas].identificador = conta_encomendas;
        /* inicializa todos os produtos da encomenda com o identificador NADA, para mostrar que nao correspondem a nenhum produto */
        for (i=0; i<MAX_PESO_ENCOM; i++)
            encomendas[conta_encomendas].produtos[i].identificador = NADA;
        
        printf("Nova encomenda %d.\n", conta_encomendas);
        conta_encomendas++;
    }
}


/* Adiciona um produto a uma encomenda: Le " idp:ide:qtd", adiciona qtd unidades do produto idp 'a encomenda ide e subtrai qtd do stock do produto */
void comando_A(produto produtos[], encomenda encomendas[]) {
    int ide, idp, qtd, novo_peso, i;
    scanf(" %d:%d:%d", &ide, &idp, &qtd);

    if ( !encomenda_existe(ide) )
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if ( !produto_existe(idp) )
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (produtos[idp].quantidade < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if ( (novo_peso = encomendas[ide].peso + qtd*produtos[idp].peso) > MAX_PESO_ENCOM)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idp, ide, MAX_PESO_ENCOM);

    else {
        i = indice_produto_encomenda(encomendas, ide, idp);
        /* Se o produto ja existir na encomenda, apenas adiciona a quantidade */
        if (i != NADA)
            encomendas[ide].produtos[i].quantidade += qtd;
        /* Se o produto nao existir na encomenda, e' criado */    
        else {
            i = indice_produto_encomenda(encomendas, ide, NADA);
            encomendas[ide].produtos[i].identificador = idp;
            encomendas[ide].produtos[i].quantidade = qtd;
        }

        encomendas[ide].peso = novo_peso;
        produtos[idp].quantidade -= qtd;
    }
}


/* Remove stock a um produto existente: Le " idp:qtd" e subtrai qtd 'a quantidade em stock de idp */
void comando_r(produto produtos[]) {
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    
    if ( !produto_existe(idp) )
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if (produtos[idp].quantidade < qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else
        produtos[idp].quantidade -= qtd;
}


/* Remove um produto de uma encomenda: Le " ide:idp" e remove o produto com o identificador idp da encomenda ide, adicionando ao stock a quantidade que estava na encomenda*/
void comando_R(produto produtos[], encomenda encomendas[]) {
    int ide, idp, i;
    scanf(" %d:%d", &ide, &idp);

    if ( !encomenda_existe(ide) )
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if ( !produto_existe(idp) )
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

    else {
        i = indice_produto_encomenda(encomendas, ide, idp);
        if (i != NADA) {
            encomendas[ide].peso -= encomendas[ide].produtos[i].quantidade * produtos[idp].peso;
            produtos[idp].quantidade += encomendas[ide].produtos[i].quantidade;
            encomendas[ide].produtos[i].quantidade = 0;
            encomendas[ide].produtos[i].identificador = NADA;
        }
    }
}


/* Calcula o custo de uma encomenda: Le " ide" e escreve a soma dos precos de todos os produtos da encomenda multiplicados pelas respetivas quantidades */
void comando_C(produto produtos[], encomenda encomendas[]) {
    int ide, idp, i, total = 0;
    scanf(" %d", &ide);

    if ( !encomenda_existe(ide) )
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);

    else {
        for (i = 0; i < MAX_PESO_ENCOM; i++) {
            if ( (idp = encomendas[ide].produtos[i].identificador) != NADA)
                total += produtos[idp].preco * encomendas[ide].produtos[i].quantidade;
        }
        printf("Custo da encomenda %d %d.\n", ide, total);
    }
}


/* Altera o preco de um produto existente no sistema: Le " idp:preco" e atualiza o preco do produto idp para o valor lido */
void comando_p(produto produtos[]) {
    int idp, preco;
    scanf(" %d:%d", &idp, &preco);

    if ( !produto_existe(idp) )
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else
        produtos[idp].preco = preco;
}


/* Lista a descricao e a quantidade de um produto numa encomenda: Le " ide:idp" e escreve a descricao do produto idp e a sua quantidade na encomenda ide */
void comando_E(produto produtos[], encomenda encomendas[]) {
    int ide, idp, quantidade, i;
    scanf(" %d:%d", &ide, &idp);

    if ( !encomenda_existe(ide) )
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if ( !produto_existe(idp) )
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    
    else {
        i = indice_produto_encomenda(encomendas, ide, idp);
        if (i == NADA)
            quantidade = 0;
        else
            quantidade = encomendas[ide].produtos[i].quantidade;
        printf("%s %d.\n", produtos[idp].descricao, quantidade);
    }
}


/* Lista o identificador da encomenda em que o produto ocorre mais vezes: Le " idp" e escreve o identificador da encomenda que contem maior quantidade do produto idp */
void comando_m(encomenda encomendas[]) {
    int idp, ide, i, max_ide = NADA, max_qtd = 0;
    scanf(" %d", &idp);

    if ( !produto_existe(idp) )
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);

    else if (conta_encomendas > 0) {
        for (ide = 0; ide < conta_encomendas; ide++)
            if ( (i = indice_produto_encomenda(encomendas, ide, idp)) != NADA )
                if (encomendas[ide].produtos[i].quantidade > max_qtd) {
                    max_qtd = encomendas[ide].produtos[i].quantidade;
                    max_ide = ide;
                }
        if (max_qtd > 0)
            printf("Maximo produto %d %d %d.\n", idp, max_ide, max_qtd);
    }
} 


/* Lista todos os produtos existentes no sistema por ordem crescente do preco (escreve descricao, preco e quantidade em stock) */
void comando_l(produto produtos[]) {
    int i;
    produto copia[MAX_PRODUTOS];

    for (i = 0; i < conta_produtos; i++)
        copia[i] = produtos[i];
    /* Ordena os produtos na tabela copia por ordem crescente dos seus precos */
    mergesort_preco(copia, 0, conta_produtos-1);
    printf("Produtos\n");
    for (i = 0; i < conta_produtos; i++) {
        printf("* %s %d %d\n", copia[i].descricao, copia[i].preco, copia[i].quantidade);
    }
}


/* Recebe um vetor de produtos, o indice do primeiro e o indice do ultimo e reordena os produtos no vetor por ordem crescente dos seus precos */ 
void mergesort_preco(produto produtos[], int left, int right){
    int meio = (right + left) / 2;

    if(right <= left)
        return;
    mergesort_preco(produtos, left, meio);
    mergesort_preco(produtos, meio+1, right);
    merge_preco(produtos, left, meio, right);
}

/* Funcao auxiliar da mergesort_preco */
void merge_preco(produto produtos[], int left, int m, int right){
    int i, j, k;
    produto aux[MAX_PRODUTOS];

    for(i = m+1; i > left; i--)
        aux[i-1]= produtos[i-1];

    for(j = m; j < right; j++)
        aux[right+m-j] = produtos[j+1];

    for(k = left; k <= right; k++){
        if(aux[j].preco < aux[i].preco || i > m )
            produtos[k] = aux[j--];
        else
            produtos[k]=aux[i++];
    }
}


/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao: Le " ide" e escreve descricao, preco e quantidade na encomenda */
void comando_L(produto produtos[], encomenda encomendas[]) {
    int ide, i, j, conta_prods_encom, idp, qtd;
    produto prods_encom[MAX_PESO_ENCOM];
    scanf(" %d", &ide);

    if ( !encomenda_existe(ide) )
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

    else {
        conta_prods_encom = 0;
        /* Cria vetor prods_encom com todos os produtos que estao na encomenda */
        for (i = 0; i < MAX_PESO_ENCOM; i++) {
            if ( (idp = encomendas[ide].produtos[i].identificador) != NADA) {
                prods_encom[conta_prods_encom] = produtos[idp];
                conta_prods_encom++;
            }
        }
        /* Ordena os produtos no vetor copia por ordem alfabetica das suas descricoes */
        mergesort_descricao(prods_encom, 0, conta_prods_encom-1);

        printf("Encomenda %d\n", ide);
        for (i = 0; i < conta_prods_encom; i++) {
            idp = prods_encom[i].identificador;
            j = indice_produto_encomenda(encomendas, ide, idp);
            qtd = encomendas[ide].produtos[j].quantidade;
            printf("* %s %d %d\n", prods_encom[i].descricao, prods_encom[i].preco, qtd);
        }
    }
}


/* Recebe um vetor de produtos, o indice do primeiro e o indice do ultimo e reordena os produtos no vetor por ordem alfabetica das suas descricoes */
void mergesort_descricao(produto produtos[], int left, int right){
    int m = (right + left) / 2;

    if(right <= left)
        return;
    mergesort_descricao(produtos, left, m);
    mergesort_descricao(produtos, m+1, right);
    merge_descricao(produtos, left, m, right);
}

/* Funcao auxiliar da mergesort_descricao */
void merge_descricao(produto produtos[], int left, int m, int right){
    int i, j, k;
    produto aux[MAX_PESO_ENCOM];

    for(i = m+1; i > left; i--)
        aux[i-1]= produtos[i-1];

    for(j = m; j < right; j++)
        aux[right+m-j] = produtos[j+1];

    for(k = left; k <= right; k++){
        if(strcmp(aux[j].descricao, aux[i].descricao) < 0 || i > m)
            produtos[k] = aux[j--];
        else
            produtos[k]=aux[i++];
    }
}
