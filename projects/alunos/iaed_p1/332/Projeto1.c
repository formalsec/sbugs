#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAX 63                     /* Tamanho maximo da descricao de um produto */
#define STRING 100000              /* Permite que se recebam os varios comandos */
#define NUMEROPROD 10000           /* Limite de produtos existentes */
#define DUZENTOS 200               /* Limite de peso de uma encomenda e de produtos que podem constar numa encomenda */
#define QUINHENTOS 500             /* Limite de encomendas */

/* VARIAVEIS GLOBAIS */

/* Variavel relativa ao identificador do produto */
int ind_prod = 0;
/* Variavel relativa ao identificador das encomendas */
int encomenda = 0;
/* Array com 3 espacos onde vao ser guardados os valores numericos dos inputs para serem utilizados em cada comando */
int variaveis[3];
/* Array onde vai ser guardada a descricao dos produtos */
char d[MAX];

/* Estrutura do stock de produtos */
typedef struct stock{
    char descricao[MAX];
    int preco;
    int peso;
    int quantidade;
    int idp;
}Stock;

Stock produtos[NUMEROPROD];

/* Estrutura das encomendas */
typedef struct encomendas{
    int peso;
    int prod_enc[DUZENTOS];
    int qnt_prod_enc[DUZENTOS];
    char desc_prod_enc[DUZENTOS][MAX];
}Encomendas;

Encomendas enc[QUINHENTOS];

/* Funcao responsavel por guardar os elementos do input em variaveis para poderem ser usados nos diversos comandos */
void guarda_variaveis(char s[STRING]){
    int h = 0, g, e, f = 0, j;
    j = strlen(s);

    if (j > 1) {     /* Verifica se o comando introduzido no input possui variaveis para serem guardadas */
        if (s[0] == 'a') {

            /* Ciclo responsavel por guardar a descricao do produto */
            for (e = 2; e < j; e++) {
                if (s[e] != ':') {
                    d[f] = s[e];
                    d[f + 1] = '\0';
                    f++;
                }
                else {
                    g = e;           /* Valor do identificador onde termina a descricao */
                    break;
                }
            }
            /* Variaveis iniciadas a 0 onde vao ser guardados o preco, peso e quantidade do produto */
            variaveis[0] = 0;
            variaveis[1] = 0;
            variaveis[2] = 0;

            /* Ciclo responsavel por guardar os valores do preco, peso e quantidade do produto nas variaveis */
            for (e = (g + 1); e < j; e++) {
                if (s[e] == '\0') {
                    break;
                }
                else if (s[e] == ':') {
                    h += 1;
                }
                else {
                    variaveis[h] = variaveis[h] * 10 + s[e] - '0';
                }
            }

        } else { /* Casos de comandos onde se tem de guardar variaveis mas nao possuem descricao */
            variaveis[0] = 0;
            variaveis[1] = 0;
            variaveis[2] = 0;
            for (e = 2; e < j; e++) {
                if (s[e] == '\0') {
                    break;
                }
                else if (s[e] == ':') {
                    h += 1;
                }
                else {
                    variaveis[h] = variaveis[h] * 10 + s[e] - '0';
                }
            }
        }
    }
}

/* Funcao merge relativa ao comando l */
void merge_l(int a[],int l,int m,int r){
    int aux[NUMEROPROD];
    int i,j,k;
    for (i = m + 1; i > l; i--)
        aux[i - 1]=a[i - 1];
    for (j = m; j < r; j++)
        aux[r + m - j] = a[j + 1];
    for (k = l; k <= r; k++)

        /* Compara os precos e verifica os ids para no caso de precos iguais apareca primeiro o produto de menor id */
        if (produtos[aux[j]].preco < produtos[aux[i]].preco || \
        (produtos[aux[j]].preco == produtos[aux[i]].preco && aux[j] < aux[i]))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
}

/* Funcao mergesort relativa ao comando l */
void mergesort_l(int a[], int l, int r){
    int m = (r + l)/2;
    if (r <= l) return;
    mergesort_l(a, l, m);
    mergesort_l(a, (m + 1), r);
    merge_l(a, l, m, r);
}

/* Funcao auxiliar a funcao merge do comando L */
int aux_merge_L(char a[], char b[]) {
    int j;
    for (j = 0; j < MAX; j++) {
        if (a[j] > b[j])         /* Verifica se a primeira letra de a e maior que a de b e se for retorna 1 */
            return 1;
        else if (a[j] < b[j])    /* Se a primeira letra de a for menor que a de b retorna 0 */
            return 0;
    }
    return 0;
}

/* Funcao merge relativa ao comando L */
void merge_L(int a[], int l, int m, int r){
    int aux[DUZENTOS];
    int i, j ,k;
    for (i = m + 1; i > l; i--)
        aux[i - 1] = a[i - 1];
    for (j = m; j < r; j++)
        aux[r + m - j] = a[j + 1];
    for (k = l; k <= r; k++)

        /* No caso da funcao auxiliar retornar 1 , esta condicao e feita */
        if (aux_merge_L(produtos[aux[i]].descricao, produtos[aux[j]].descricao))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
}

/* Funcao mergesort relativa ao comando L */
void mergesort_L(int a[],int l,int r){
    int m = (r + l)/2;
    if (r <= l)
        return;
    mergesort_L(a, l, m);
    mergesort_L(a, m+1, r);
    merge_L(a, l, m, r);
}

/* Funcao responsavel por adicionar um novo produto ao sistema */
void comando_a(){
    int l, i;
    produtos[ind_prod].preco = variaveis[0];
    produtos[ind_prod].peso = variaveis[1];
    produtos[ind_prod].quantidade = variaveis[2];

    for (i=0; d[i] != '\0'; i++);             /* Vai buscar o comprimento da descricao */

    for (l = 0; l < i; l++){
        produtos[ind_prod].descricao[l] = d[l];
    }
    produtos[ind_prod].idp = ind_prod;
    printf("Novo produto %d.\n", ind_prod);
    ind_prod++;                               /* Vai ser o identificador do proximo produto a ser adicionado */
}

/* Funcao responsavel por adicionar stock a um produto existente no sistema */
void comando_q(){
    if (variaveis[0] >= ind_prod)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", variaveis[0]);
    else
        produtos[variaveis[0]].quantidade += variaveis[1]; /* Adiciona stock ao produto */
}

/* Funcao responsavel por criar uma nova encomenda */
void comando_N(){
    int w;
    enc[encomenda].peso = 0;

/* Preenche a array onde vao ser guardados os idps toda com um valor nao correspondente ao id de nenhum produto */
    for (w = 0; w < DUZENTOS; w++ ) {
        enc[encomenda].prod_enc[w] = 10000;
        enc[encomenda].qnt_prod_enc[w] = 0;   /* Inicia a quantidade de todos os produtos a zero */
    }
    printf("Nova encomenda %d.\n", encomenda);
    encomenda++;                              /* Vai ser o identificador da proxima encomenda */
}

/* Funcao responsavel por adicionar um produto a uma encomenda */
void comando_A(){
    int w, x;
    if (variaveis[0] >= encomenda)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", variaveis[1], \
                variaveis[0]);

    else if (variaveis[1] >= ind_prod)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", variaveis[1], \
                variaveis[0]);

    else if (variaveis[2] > produtos[variaveis[1]].quantidade)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", \
                variaveis[1], variaveis[0]);

    else if ((enc[variaveis[0]].peso + (produtos[variaveis[1]].peso * variaveis[2])) > 200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", \
                variaveis[1], variaveis[0]);

    else{
        produtos[variaveis[1]].quantidade -= variaveis[2];
        enc[variaveis[0]].peso += produtos[variaveis[1]].peso * variaveis[2];
        for (w = 0; w < ind_prod; w++){
            if (enc[variaveis[0]].prod_enc[w] == variaveis[1]) {  /* Verifica se o produto ja esta na encomenda */
                enc[variaveis[0]].qnt_prod_enc[w] += variaveis[2]; /* Se ja estiver adiciona a quantidade pedida */
                break;
            }

            /* Se ainda nao existir o produto na encomenda */
            else{
                /* Ate encontrar o identificador que nao pertenca a um produto para o trocar pelo id do produto */
                if (enc[variaveis[0]].prod_enc[w] == 10000){
                    enc[variaveis[0]].prod_enc[w] = produtos[variaveis[1]].idp; /* Guarda o identificador do produto */
                    enc[variaveis[0]].qnt_prod_enc[w] += variaveis[2];          /* Guarda a quantidade do produto */

                    /* Guarda a descricao do produto */
                    for (x = 0; x < MAX; x++){
                        enc[variaveis[0]].desc_prod_enc[w][x] = produtos[variaveis[1]].descricao[x];
                    }
                    break;
                }
            }
        }
    }
}

/* Funcao responsavel por remover stock a um produto existente */
void comando_r(){
    if (variaveis[0] >= ind_prod)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", variaveis[0]);

    else if (variaveis[1] > produtos[variaveis[0]].quantidade)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", \
                variaveis[1], variaveis[0]);

    else{
        produtos[variaveis[0]].quantidade -= variaveis[1];   /* Remove a quantidade pedida do stock do produto */
    }
}

/* Funcao responsavel por remover um produto de uma encomenda */
void comando_R(){
    int w;
    if (variaveis[0] >= encomenda)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", \
                variaveis[1], variaveis[0]);

    else if (variaveis[1] >= ind_prod)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", \
                variaveis[1], variaveis[0]);

    else{
        for (w = 0; w < DUZENTOS; w++){                 /* Procura o identificador do produto dado no input */
            if (enc[variaveis[0]].prod_enc[w] == variaveis[1]){

                /* Aumenta o stock do produto removido da encomenda */
                produtos[enc[variaveis[0]].prod_enc[w]].quantidade += enc[variaveis[0]].qnt_prod_enc[w];

                /* Retira o peso desse produto a encomenda */
                enc[variaveis[0]].peso -= (enc[variaveis[0]].qnt_prod_enc[w] * produtos[variaveis[1]].peso);

                /* Reduz a quantidade do produto na encomenda a zero */
                enc[variaveis[0]].qnt_prod_enc[w] = 0;
            }
        }
    }
}

/* Funcao responsavel por calcular o custo de uma encomenda */
void comando_C(){
    int w, custo = 0;
    if (variaveis[0] >= encomenda)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", variaveis[0]);
    else {
        for (w = 0; w < DUZENTOS; w++) {        /* Procura os identificadores dos produtos que existem na encomenda */
            if (enc[variaveis[0]].prod_enc[w] != 10000) {
                if (enc[variaveis[0]].qnt_prod_enc[w] > 0) {

                    custo += (produtos[enc[variaveis[0]].prod_enc[w]].preco * enc[variaveis[0]].qnt_prod_enc[w]);
                }
            }
        }
        printf("Custo da encomenda %d %d.\n", variaveis[0], custo);
    }
}

/* Funcao responsavel por alterar o preco de um produto existente no sistema */
void comando_p(){
    if (variaveis[0] >= ind_prod)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", variaveis[0]);
    produtos[variaveis[0]].preco = variaveis[1];  /* Altera o preco do produto */
}

/* Funcao responsavel por listar a descricao e a quantidade de um produto numa encomenda */
void comando_E(){
    int a, b, c, estado = 0;
    if (variaveis[0] >= encomenda)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", variaveis[0]);
    else if (variaveis[1] >= ind_prod)
        printf("Impossivel listar produto %d. Produto inexistente.\n", variaveis[1]);
    else {
        for (a = 0; a < DUZENTOS; a++){     /* Procura o id do produto que se pretende listar na encomenda */
            if (enc[variaveis[0]].prod_enc[a] == produtos[variaveis[1]].idp){

                /* O estado passa a um para diferenciar os produtos com qnt superior a 0 dos que a quantidade e nula */
                estado = 1;
                b = produtos[variaveis[1]].idp;
                printf("%s %d.\n", produtos[b].descricao, enc[variaveis[0]].qnt_prod_enc[a]);
            }
        }
        /* Quando o estado se encontra a 0 significa que o produto do input nao possui nenhuma unidade na encomenda */
        if (estado == 0){
            c = produtos[variaveis[1]].idp;
            printf("%s %d.\n", produtos[c].descricao, 0);
        }
    }
}

/* Funcao responsavel por listar o identificador da encomenda em que o produto se encontra em maior quantidade */
void comando_m(){
    int b, c, k = 0, i = 0;
    if (variaveis[0] >= ind_prod)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", variaveis[0]);

    /* Percorre cada uma das posiveis 500 encomendas */
    for (b = 0; b < QUINHENTOS; b++){
        /* Percorre cada um dos possiveis 200 produtos contidos numa encomenda */
        for (c = 0; c < DUZENTOS; c++){
            if (enc[b].prod_enc[c] == variaveis[0]){  /* Verifica se o produto dado no input esta na encomenda */

                /* Verifica se a quantidade e maior do que a da encomenda previa, nao se aplica a primeira encomenda */
                if (enc[b].qnt_prod_enc[c] > k){
                    k = enc[b].qnt_prod_enc[c];
                    i = b;
                }
            }
        }
    }
    if (k != 0)
        printf("Maximo produto %d %d %d.\n", variaveis[0], i, k);
}

/* Funcao responsavel por listar os produtos existentes no sistema por ordem crescente tendo por base o seu preco */
void comando_l(){
    int listaids[NUMEROPROD], f, l = 0, r = ind_prod, y;
    printf("Produtos\n");

    for (f = 0; f < ind_prod; f++){                /* Passa o preco de todos os produtos para uma array */
        listaids[f] = produtos[f].idp;
    }

    mergesort_l(listaids, l, (r - 1));

    for (y = 0; y < ind_prod; y++){
        printf("* %s %d %d\n", produtos[listaids[y]].descricao, produtos[listaids[y]].preco, \
                produtos[listaids[y]].quantidade);
    }
}

/* Funcao responsavel por listar todos os produtos de uma encomenda por ordem alfabetica */
void comando_L() {
    int a, b = 0, c, l = 0;
    int lidps[NUMEROPROD];
    if (variaveis[0] >= encomenda) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", variaveis[0]);
    } else {
        printf("Encomenda %d\n", variaveis[0]);

        /* Passa para uma array os identificadores dos produtos cuja quantidade na encomenda e maior que zero */
        for (a = 0; a < ind_prod; a++) {
            if (enc[variaveis[0]].qnt_prod_enc[a] > 0)
                lidps[b++] = enc[variaveis[0]].prod_enc[a];
        }
    }

    mergesort_L(lidps, l, (b - 1));

    for (a = 0; a < b; a++){
        for (c = 0; c < ind_prod; c++) {
            if (lidps[a] == enc[variaveis[0]].prod_enc[c]) {
                printf("* %s %d %d\n", produtos[lidps[a]].descricao, produtos[lidps[a]].preco, \
                       enc[variaveis[0]].qnt_prod_enc[c]);
                break;
            }
        }
    }
}

/* Funcao responsavel por verificar qual o comando dado no input e levar o codigo ate a funcao desse comando */
void direciona(char s[STRING]){
    char k;
    k = s[0];         /* Retira o primeiro carater do input que e o comando */
    switch(k){

        /* Verifica qual o comando pedido */
        case 'a':
            comando_a();
            break;

        case 'q':
            comando_q();
            break;

        case 'N':
            comando_N();
            break;

        case 'A':
            comando_A();
            break;

        case 'r':
            comando_r();
            break;

        case 'R':
            comando_R();
            break;

        case 'C':
            comando_C();
            break;

        case 'p':
            comando_p();
            break;

        case 'E':
            comando_E();
            break;

        case 'm':
            comando_m();
            break;

        case 'l':
            comando_l();
            break;

        case 'L':
            comando_L();
            break;
    }
}

/* Funcao principal */
int main () {
    int i = 0;
    char s[STRING], c;
    c = getchar();
    while (i < STRING) {
        if (c == 'x') {    /* Se o comando dado for o comando 'x' termina o programa */
            break;
        }
        while (c != '\n') { /* Ciclo onde vai ser guardado cada input */
            s[i] = c;
            s[i + 1] = '\0';
            c = getchar();
            i++;
        }
        i = 0;
        guarda_variaveis(s);
        direciona(s);
        c =  getchar();    /* Permite que apos a execucao de cada comando seja pedido outro */
    }
    return 0;
}