#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_PESO_ENCOMENDA 200
#define MAX_PROD_ENCOMENDA 200


/* definicao de estruturas */

typedef struct produto { /* definicao da estrutura produto */
    char desc[64];
    int idp;
    int preco;
    int peso;
    int qtd;
} Produto;

typedef struct encomendas {
    Produto produtos[MAX_PROD_ENCOMENDA]; /* o maximo sao 200 porque cada produto tem no minimo 1 peso e a encomenda tem maximo de 200 peso */
    int ide;
} Encomendas;


/* declaracao e definicao de variaveis */

Produto prod[MAX_PRODUTOS]; /* conjunto dos produtos todos */
Encomendas encom[MAX_ENCOMENDAS]; /* conjunto das encomendas todas */ 
int n_atual_prod = 0; /* n_atual_prod corresponde ao numero do produto a ser adicionado (como sao adicionados por ordem sequencial) */
int n_atual_encom = 0; /* n_atual_encom corresponde ao numero da encomenda a ser adicionada (como sao adicionadas por ordem sequencial) */


/* funcoes iniciais e auxiliares */ 


void reset_encomendas() { /* esta funcao da numero de ide a 500 a todas as encomendas e quantidade dos produtos de todas as encomendas a 0,
                        de modo a criar uma forma facil de perceber se uma encomenda existe e se um produto esta numa encomenda */
    int i;
    for(i = 0; i < MAX_ENCOMENDAS; i++) {
        encom[i].ide = 500;
    }
}

int peso_encomenda(int ide) { /* funcao auxiliar para calcular o peso total de uma encomenda */
    int i, peso_total = 0;
    for(i = 0; i < MAX_PROD_ENCOMENDA; i++) {
        if(encom[ide].produtos[i].qtd > 0) {
            peso_total += (encom[ide].produtos[i].qtd * encom[ide].produtos[i].peso);
        }
    }
    return peso_total;
}

int num_produto(int ide, int n_produto) { /* funcao auxiliar que determina se um produto esta numa encomenda, 
                                            e caso esteja, retorna o seu endereco na estrutura da encomenda. caso nao esteja
                                            ele determina o endereco menor da encomenda que esteja livre (quantidade = 0) */
    int i, n_produto_temp = MAX_PROD_ENCOMENDA;
    for(i = 0; i < MAX_PROD_ENCOMENDA; i++) {
                if(encom[ide].produtos[i].idp == n_produto) {
                        n_produto_temp = i;
                        return n_produto_temp;
                        break;
                }
    }
    if(n_produto_temp == MAX_PROD_ENCOMENDA) {
        for(i = 0; i < MAX_PROD_ENCOMENDA; i++) {
            if(encom[ide].produtos[i].qtd == 0) {
                n_produto_temp = i;
                return n_produto_temp;
                break;
            }
        }
    }
    return n_produto_temp;
}

int qtd_encomenda(int ide, int idp) { /* funcao auxiliar que calcula a quantidade de um produto numa encomenda */
    int n_produto = num_produto(ide, idp);
    return encom[ide].produtos[n_produto].qtd;
}

int qtd_sistema(int idp) { /* funcao auxiliar que calcula a quantidade de um produto no sistema */
    int i;
    long quantidade = prod[idp].qtd;
    for(i = 0; i < MAX_ENCOMENDAS; i++) {
        quantidade += qtd_encomenda(i, idp);
    }
    return quantidade;
}

/* funcoes principais do programa, correspondem as operacoes efetuadas pelo programa */

void adiciona_produto() {
    char descricao_p[64];
    int preco_p, peso_p, qtd_p;

    scanf("  %[^:]:%d:%d:%d", descricao_p, &preco_p, &peso_p, &qtd_p);
    
    if(n_atual_prod < MAX_PRODUTOS) {
        strcpy(prod[n_atual_prod].desc, descricao_p);
        prod[n_atual_prod].idp = n_atual_prod;
        prod[n_atual_prod].preco = preco_p;
        prod[n_atual_prod].peso = peso_p;
        prod[n_atual_prod].qtd = qtd_p;
    
    printf("Novo produto %d.\n", n_atual_prod);

    n_atual_prod++; /* aumenta o numero atual do proximo produto a ser adicionado */
    }
}
 
void adiciona_stock() {
    int n_produto, add;

    scanf("  %d:%d", &n_produto, &add);
    
    if(prod[n_produto].preco == 0) { /* se o preco for 0, o produto nao existe (ver funcao auxiliar preco_zero) */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", n_produto);
    }
    else {
        prod[n_produto].qtd += add;
    }
}

void adiciona_encomenda() {
    if(n_atual_encom < MAX_ENCOMENDAS) {
        encom[n_atual_encom].ide = n_atual_encom;

        printf("Nova encomenda %d.\n", n_atual_encom);

        n_atual_encom++; /* aumenta o numero atual da proxima encomenda a ser adicionada */
    }
} 

void adiciona_produto_encomenda() {
    int n_produto, n_encomenda, quantidade, n_produto_mod; /* n_produto_mod corresponde ao endereco da encomenda que se modifica */
    int peso_produto;

    scanf("  %d:%d:%d", &n_encomenda, &n_produto, &quantidade);

    n_produto_mod = num_produto(n_encomenda, n_produto);

    if(encom[n_encomenda].ide == 500) { /* se a encomenda tiver ide 500, nao existe, como o n maximo e 499, criei uma funcao auxiliar para meter todas a 500 */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", n_produto, n_encomenda);
    }
    else if(prod[n_produto].preco == 0) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", n_produto, n_encomenda);
    }
    else if(prod[n_produto].qtd < quantidade) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", n_produto, n_encomenda);
    }
    else { /* a funcao percorre a encomenda para perceber se o produto ja esta na encomenda, se nao estiver, cria um produto \
            no slot menor que esteja livre, se estiver, apenas adiciona stock ao produto na encomenda */
        peso_produto = quantidade * prod[n_produto].peso;
        if((peso_encomenda(n_encomenda) + peso_produto) > MAX_PESO_ENCOMENDA) {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", n_produto, n_encomenda);
        }
        else { /* usa a funcao auxiliar num_produto para determinar se o produto existe ou nao e em que endereco da encomenda o coloca */
            if(encom[n_encomenda].produtos[n_produto_mod].qtd == 0) {
                strcpy(encom[n_encomenda].produtos[n_produto_mod].desc, prod[n_produto].desc);
                encom[n_encomenda].produtos[n_produto_mod].idp = prod[n_produto].idp;
                encom[n_encomenda].produtos[n_produto_mod].peso = prod[n_produto].peso;
                encom[n_encomenda].produtos[n_produto_mod].preco = prod[n_produto].preco;
                encom[n_encomenda].produtos[n_produto_mod].qtd += quantidade;
                prod[n_produto].qtd -= quantidade;
            }
            else {
                encom[n_encomenda].produtos[n_produto_mod].qtd += quantidade;
                prod[n_produto].qtd -= quantidade;
            }
        }
    }
}

void remove_stock() {
    int n_produto, remove;

    scanf("  %d:%d", &n_produto, &remove);

    if(prod[n_produto].preco == 0) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", n_produto);
    }
    else if(prod[n_produto].qtd < remove) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", remove, n_produto);
    }
    else {
        prod[n_produto].qtd -= remove;
    }
}

void remove_produto_encomenda() {
    int n_encomenda, n_produto;
    int n_produto_mod; /* endereco da encomenda em que esta o produto que se vai remover */

    scanf("  %d:%d", &n_encomenda, &n_produto);

    n_produto_mod = num_produto(n_encomenda, n_produto); /* endereco da encomenda em que esta o produto que se vai remover */

    if(encom[n_encomenda].ide == 500) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", n_produto, n_encomenda);
    }
    else if(prod[n_produto].preco == 0) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", n_produto, n_encomenda);
    }
    else {
        if(n_produto_mod < 200){
        prod[n_produto].qtd += encom[n_encomenda].produtos[n_produto_mod].qtd;
        encom[n_encomenda].produtos[n_produto_mod].qtd = 0;
        }
    }
}

void custo_encomenda() {
    int n_encomenda, i;
    long custo = 0;

    scanf("  %d", &n_encomenda);

    if(encom[n_encomenda].ide == 500) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", n_encomenda);
    }
    else {
        for(i = 0; i < MAX_PROD_ENCOMENDA; i++) {
            if(encom[n_encomenda].produtos[i].qtd > 0) {
                custo += encom[n_encomenda].produtos[i].qtd * encom[n_encomenda].produtos[i].preco;
            }
        }
        printf("Custo da encomenda %d %ld.\n", n_encomenda, custo);
    }
}

void altera_preco() {
    int n_produto, novo_preco, i, j;

    scanf("  %d:%d", &n_produto, &novo_preco);

    if(prod[n_produto].preco == 0) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", n_produto);
    }
    else {
        prod[n_produto].preco = novo_preco;
        for(i = 0; i < MAX_ENCOMENDAS; i++) { /* percorre as encomendas existentes e os produtos a ver se tem o idp do produto cujo preco se quer alterar */
            for(j = 0; j < MAX_PROD_ENCOMENDA; j++) {
                if(encom[i].ide != 500) {
                    if((encom[i].produtos[j].qtd > 0) && (encom[i].produtos[j].idp == n_produto)) {
                        encom[i].produtos[j].preco = novo_preco;
                    }
                }
            }
        }
    }
}

void desc_qtd_encom() {
    int n_encomenda, n_produto, n_produto_mod;

    scanf("  %d:%d", &n_encomenda, &n_produto);

    n_produto_mod = num_produto(n_encomenda, n_produto);

    if(encom[n_encomenda].ide == 500) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", n_encomenda);
    }
    else if(prod[n_produto].preco == 0) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", n_produto);
    }
    else{
        printf("%s %d.\n", prod[n_produto].desc, encom[n_encomenda].produtos[n_produto_mod].qtd);
    }
}

void mais_vezes() {
    int n_produto, i, j, max = 0, encom_max = 500;

    scanf("  %d", &n_produto);


    if(prod[n_produto].preco == 0) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", n_produto);
    }
    else{
        for(i = 0; i < MAX_ENCOMENDAS; i++) {
            for(j = 0; j < MAX_PROD_ENCOMENDA; j++) {
                if(encom[i].produtos[j].idp == n_produto) {
                    if(encom[i].produtos[j].qtd > max) {
                        max = encom[i].produtos[j].qtd;
                        encom_max = encom[i].ide;
                        }
                    }
                }
        }
        if(encom_max != 500) { /* se a encomenda_max for 500 quer dizer que o produto nao esta em nenhuma encomenda, 
                                entao so imprime se houver pelo menos uma encomenda com o produto */
            printf("Maximo produto %d %d %d.\n", n_produto, encom_max, encom[encom_max].produtos[num_produto(encom_max, n_produto)].qtd);
        }
     
    }
}

void preco_crescente() {
    int i, key, j; /* variaveis utilizadas no algoritmo de insertion sort */
    int vet_precos[MAX_PRODUTOS]; /* vetor que armazenar os precos por ordem crescente */
    int vet_qtd[MAX_PRODUTOS]; /* vetor que serve para repor a quantidade dos produtos no fim da funcao */

    for(i = 0; i < n_atual_prod; i++) { /* copia os precos para o vetor para serem organizados */
        vet_precos[i] = prod[i].preco;
        vet_qtd[i] = prod[i].qtd;
    }

    for (i = 1; i < n_atual_prod; i++) { /* insertion sort para ordenar os precos no vetor */
        key = vet_precos[i]; 
        j = i - 1; 

        while (j >= 0 && vet_precos[j] > key) { 
            vet_precos[j + 1] = vet_precos[j];
            j = j - 1; 
        } 
        vet_precos[j + 1] = key;
    }
    printf("Produtos\n");
    for(i = 0; i < n_atual_prod; i++) { /* imprime os produtos por ordem crescente de idp que correspondem aos precos do vetor
                                        que, por sua vez, tambem esta ordenado por ordem crescente de preco */
        for(j = 0; j <n_atual_prod; j++) {
            if((prod[j].preco == vet_precos[i]) && (prod[j].qtd != 0)) {
                printf("* %s %d %d.\n", prod[j].desc, prod[j].preco, prod[j].qtd);
                prod[j].qtd = 0; /* maneira de evitar que o mesmo produto seja imprimido duas vezes */
            }
        }
    }
     for(i = 0; i < n_atual_prod; i++) { /* repoe o peso dos produtos */
        prod[i].qtd = vet_qtd[i];
    }
}

void ordem_alfabetica() {
    int n_encomenda, n_atual_vec = 0; 
    int i, j; /* variaveis utilizadas no algoritmo de bubble sort */
    char temp[64];
    char strings[MAX_PROD_ENCOMENDA][64]; /* strings dos produtos */
    int vet_pesos[MAX_PROD_ENCOMENDA]; /* vetor que serve para repor o peso dos produtos no fim da funcao */

    scanf("  %d", &n_encomenda);

    if(encom[n_encomenda].ide == 500) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", n_encomenda);
    }
    else {
        for(i = 0; i < MAX_PROD_ENCOMENDA; i++) { /* copia os idp para o vetor para serem organizados */
            if(encom[n_encomenda].produtos[i].qtd != 0) {
                strcpy(strings[n_atual_vec], encom[n_encomenda].produtos[i].desc);
                vet_pesos[n_atual_vec] = encom[n_encomenda].produtos[i].peso;
                n_atual_vec++; /* para os elementos estarem todos de seguida nos vetores, adiciona-se em sequencia */
            }
        }
        for (i = 0; i < n_atual_vec-1; i++) {
            for(j = 0; j < n_atual_vec-1; j++) {
                if(strcmp(strings[j], strings[j+1]) > 0) {
                    strcpy(temp, strings[j]);
                    strcpy(strings[j], strings[j + 1]);
                    strcpy(strings[j + 1], temp);
                }
            }
        }
        printf("Encomenda %d\n", n_encomenda);
        if(vet_pesos[0] != 0) {
            for(i = 0; i < n_atual_vec; i++) {
                for(j = 0; j < n_atual_prod; j++) {
                    if((strcmp(prod[j].desc, strings[i]) == 0) && prod[j].peso != 0) {
                        printf("* %s %d %d\n", prod[j].desc, prod[j].preco, qtd_encomenda(n_encomenda, prod[j].idp));
                        vet_pesos[j] = prod[j].peso; /* dar "backup" ao peso para o report depois */
                        prod[j].peso = 0; /* maneira de evitar que o mesmo produto seja imprimido duas vezes */
                    }
                }
            }
            for(j = 0; j < n_atual_prod; j++) { /* ciclo para repor peso */
                prod[j].peso = vet_pesos[j];
            }
        }
    }
}



/* funcao main do programa */

int main() { /* corpo do programa, le a primeira letra do input e decide que operacao executar */
    char c; /* carater correspondente a operacao */
    reset_encomendas();
    while((c = getchar()) != 'x') {
        switch(c) {
            case 'a':
                adiciona_produto();
                break;
            case 'q':
                adiciona_stock();
                break;
            case 'N':
                adiciona_encomenda();
                break;
            case 'A':
                adiciona_produto_encomenda();
                break;
            case 'r':
                remove_stock();
                break;
            case 'R':
                remove_produto_encomenda();
                break;
            case 'C':
                custo_encomenda();
                break;
            case 'p':
                altera_preco();
                break;
            case 'E':
                desc_qtd_encom();
                break;
            case 'm':
                mais_vezes();
                break;
            case 'l':
                preco_crescente();
                break;
            case 'L':
                ordem_alfabetica();
                break;
        }
    }
    return 0;
}