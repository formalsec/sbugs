#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "stdio.h"
#include "string.h"

/* Atribuicao de constantes */

#define MAX_PRODUTOS 10000
#define MAX_DESCRICAO 63
#define MAX_ENCOMENDAS 500
#define MAX_PESO 200
#define NATURAIS 0 /* correspondera a funcao que ordena os produtos por preco */
#define STRINGS 1  /* correspondera a funcao que ordena os produtos numa encomenda por ordem alfabetica da descricao */

/* Criacao da estrutura produto, caraterizada por um identificador, uma descricao, preco, peso e quantidade. */

typedef struct produto {
    int identificador;
    char descricao[MAX_DESCRICAO];
    int preco;
    int peso;
    int quantidade;
}produto;

/* Criacao da estrutura prods_enc, que servira para guardar informacoes sobre o identificador, a quantidade na encomenda em questao
   e o peso de cada produto presente numa encomenda. */

typedef struct prods_enc { 
    int identificador;
    int quantidade;
    int peso; /* permite distinguir dos slots inalterados pois o peso nao pode ser nulo */
}prods_enc;

/* Declaracao de vetores e variaveis globais, todos inicializados a 0 */

produto produtos[MAX_PRODUTOS] = {0}; /* vetor de produtos */

prods_enc encomendas[MAX_ENCOMENDAS][MAX_PESO] = {0}; /*tabela de encomendas, linhas - encomendas, colunas - prods_enc */

int prods_dif_encomendas[MAX_ENCOMENDAS] = {0}; /* vetor com numero de produtos diferentes em cada encomenda */

int qtd_prods_enc[MAX_ENCOMENDAS][MAX_PRODUTOS] = {0}; /* tabela com quantidade de cada produto do sistema em cada encomenda */

int total_prod = 0, total_enc = 0; /* variaveis que indicam o numero total de produtos e encomendas, respetivamente, no sistema */




/* Funcao que calcula o peso total de uma encomenda(ide). */

/* Percorre cada produto de uma encomenda multiplicando a sua qtd pelo seu peso, acumulando os valores na variavel peso_total */

int peso_enc(int ide) { 
    int i, idp, peso_total = 0;
    for (i = 0; i < prods_dif_encomendas[ide]; i++) { 
        idp = encomendas[ide][i].identificador;
        peso_total += encomendas[ide][i].quantidade * produtos[idp].peso;
    }
    return peso_total;
}

/* Esta funcao adiciona um novo produto ao sistema. */

void a() {
    static int num_prod = 0; /* declaracao de variavel estatica que indica o idp do produto a ser criado. */
    int preco, peso, quantidade;
    getchar(); /* devido ao espaco entre o 'a' e o resto, repetido em todas as funcoes com argumentos */

    /* Obtencao dos valores tendo em conta o formato de input */

    scanf("%[^:]:%d:%d:%d", produtos[num_prod].descricao, &preco, &peso, &quantidade); 

    /* Registo no vetor global produtos as carateristicas do produto criado */

    produtos[num_prod].identificador = num_prod;
    produtos[num_prod].preco = preco;
    produtos[num_prod].peso = peso;
    produtos[num_prod].quantidade = quantidade;

    printf ("Novo produto %d.\n", num_prod);
    num_prod++; /* incremento da variavel estatica num_prod, permitindo que o proximo produto criado tenha idp = idp + 1 */
    total_prod++; 
    return; 
}


/* Esta funcao adiciona stock a um produto existente no sistema. */

void q() {
    int idp, qtd;
    getchar();
    scanf("%d:%d", &idp, &qtd);
    if (idp < total_prod) 
        produtos[idp].quantidade += qtd;
    else /* se o idp for maior ou igual que o total de produtos, entao o produto nao existe no sistema */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    return;
}

/* Esta funcao cria uma nova encomenda. */

void N() {
    static int num_enc = 0; /* declaracao da variavel estatica num_enc que indica o ide da encomenda a ser criada */
    printf ("Nova encomenda %d.\n", num_enc);
    num_enc++; /* incremento da variavel estatica num_enc, permitindo que a proxima encomenda criada tenha ide = ide + 1 */
    total_enc++;
    return;

}

/* Esta funcao adiciona um produto a uma encomenda. Caso o produto ja exista na encomenda, adiciona a nova quantidade ah
   quantidade existente. */

void A() {
    int ide, idp, qtd, i, coluna;
    getchar();
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    if (ide >= total_enc) {
        printf ("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if (idp >= total_prod) {
        printf ("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    
    /* produtos[idp].quantidade guarda o stock do produto, pelo que o seu valor tem de ser maior ou igual ah quantidade a adicionar */

    else if (qtd > produtos[idp].quantidade) { 
        printf ("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }

    /* O peso dos produtos ja existentes na encomenda mais o peso do produto a ser acrescentado nao pode exceder 200 */

    else if (peso_enc(ide) + qtd * produtos[idp].peso > MAX_PESO) {
        printf ("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }
    else {
        qtd_prods_enc[ide][idp] += qtd; /* atualizacao desta tabela global */
        for (i = 0; i < MAX_PESO; i++) {   /* se o produto ja estiver na encomenda, acrescenta-se a quantidade */
            if ((encomendas[ide][i].identificador == idp) && (encomendas[ide][i].peso == produtos[idp].peso)) {
                encomendas[ide][i].quantidade += qtd;
                produtos[idp].quantidade -= qtd; /* subtracao da quantidade a adicionar ao stock do produto no sistema */
                return;
            }
        }
        /* Se a funcao chega aqui, eh porque o produto nao existia na encomenda */
        /* A coluna na qual se introduz o produto eh igual ao numero de produtos diferentes - 1(apenas ? incrementada no fim da funcao */
        coluna = prods_dif_encomendas[ide]; 
        encomendas[ide][coluna].identificador = idp;
        encomendas[ide][coluna].quantidade = qtd;
        encomendas[ide][coluna].peso = produtos[idp].peso;
        prods_dif_encomendas[ide]++; /* Ha mais um produto diferente na encomenda */
        produtos[idp].quantidade -= qtd;
        return;
    }
}

/* Esta funcao remove stock a um produto existente. */

void r() {
    int idp, qtd;
    getchar();
    scanf("%d:%d", &idp, &qtd);
    if (idp >= total_prod) {
        printf ("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
    
    /* A quantidade a remover tem de ser maior ou igual que o stock */

    else if (produtos[idp].quantidade - qtd < 0) {
        printf ("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
    }
    else {
        produtos[idp].quantidade -= qtd;
        return;
    }
}

/* Esta funcao remove um produto de uma encomenda. */

void R() {
    int ide, idp, i, ind_maximo;
    getchar();
    scanf("%d:%d", &ide, &idp);
    if (ide >= total_enc) {
        printf ("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if (idp >= total_prod) {
        printf ("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    else {

        /* Metodo - colocar o ultimo produto registado no local do removido, colocando o spot do ultimo a zeros */

        qtd_prods_enc[ide][idp] = 0; /* atualizacao desta tabela global */
        ind_maximo = prods_dif_encomendas[ide] - 1; /* o indice do ultimo eh igual ao numero de prods dif numa enc - 1 */
        for (i = 0; i < prods_dif_encomendas[ide]; i++) {   
            if ((encomendas[ide][i].identificador == idp) && (encomendas[ide][i].peso == produtos[idp].peso)) {
                produtos[idp].quantidade += encomendas[ide][i].quantidade; /*repor o stock */

                encomendas[ide][i].identificador = encomendas[ide][ind_maximo].identificador;
                encomendas[ide][i].quantidade = encomendas[ide][ind_maximo].quantidade; /* o ultimo passa a estar no spot do removido */
                encomendas[ide][i].peso = encomendas[ide][ind_maximo].peso;

                encomendas[ide][ind_maximo].identificador = 0;
                encomendas[ide][ind_maximo].quantidade = 0;   /* o ultimo indice passou a nao ter produto */
                encomendas[ide][ind_maximo].peso = 0;

                prods_dif_encomendas[ide]--;         /* existe menos um produto na encomenda */ 
                return;
            }
        }
        
        return;
    }
}

/* Esta funcao calcula o custo de uma encomenda. */

void C() {
    int ide, custo = 0, i, idp;
    getchar();
    scanf("%d", &ide);
    if (ide >= total_enc) {
        printf ("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    else {

        /* Basta ir somando a quantidade de cada produto na encomenda * o seu preco */

        for (i = 0; i < MAX_PESO; i++) {
            idp = encomendas[ide][i].identificador;
            custo += encomendas[ide][i].quantidade * produtos[idp].preco;
        }
        printf ("Custo da encomenda %d %d.\n", ide, custo);
        return;
        
    }
}

/* Esta funcao altera o preco de um produto existente no sistema. */

void p() {
    int idp, preco;
    getchar();
    scanf("%d:%d", &idp, &preco);
    if (idp >= total_prod) {
        printf ("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }
    else {
        produtos[idp].preco = preco; /* o preco do produto passa a ser o preco indicado */
        return;
    }
}

/* Esta funcao lista a descricao e a quantidade de um produto numa encomenda. */

void E() {
    int ide, idp;
    getchar();
    scanf("%d:%d", &ide, &idp);
    if (ide >= total_enc) {
        printf ("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    else if (idp >= total_prod) {
        printf ("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    else {
        printf ("%s %d.\n", produtos[idp].descricao, qtd_prods_enc[ide][idp]); 
        return;
        
    }
}

/* Esta funcao lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas 
   nessa situacao, imprime a encomenda de menor id. */

void m() {
    int idp, i, ide, qtd_max = 0;
    getchar();
    scanf("%d",&idp);
    if (idp >= total_prod) {
        printf ("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    else {
        for (i = 0; i < total_enc; i++) {

            /* Se a qtd do produto numa encomenda eh maior do que qtd_max ate ai, passa a ser a qtd_max e eh guardado o ide correspondente */

            if (qtd_prods_enc[i][idp] > qtd_max) { 
                qtd_max = qtd_prods_enc[i][idp];
                ide = i;
            }
        }
        if (qtd_max > 0) 
            printf ("Maximo produto %d %d %d.\n", idp, ide, qtd_max);
        return;
    }
}

/* Funcao auxiliar do mergesort que retorna 1 se o elemento a for "menor" do que o b, e 0, caso contrario. */


int less(int a, int b, int tipo) {
    if (tipo == NATURAIS) { /* caso correspondente ah funcao que ordena os produtos por pre?o */
        if (produtos[a].preco < produtos[b].preco) 
            return 1;
        else if (produtos[a].preco == produtos[b].preco) { /* o criterio de desempate eh o idp */
            if (produtos[a].identificador < produtos[b].identificador)
                return 1;
            else 
                return 0;
        }
        else
            return 0;
    }
    else { /* caso correspondente ah funcao que ordena os produtos de uma encomenda por ordem alfabetica */
        if (strcmp(produtos[a].descricao, produtos[b].descricao) < 0)
            return 1;
        else
            return 0;
    }
}

/* Funcao auxiliar do mergesort */


void merge(int a[], int left, int m, int right, int tipo) {
    int i, j, k;
    int aux[MAX_PRODUTOS] = {0};
    for (i = m + 1; i > left; i--)
        aux[i - 1] = a[i -1 ];
    for (j = m; j < right; j++) 
        aux[right + m - j] = a[j + 1];
    for (k = left; k <= right; k++) {
        if (less(aux[j], aux[i], tipo))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}

/* Funcao principal do algoritmo de ordenacao mergesort */

void mergesort(int a[], int left, int right, int tipo) { 
    int m = (right + left) / 2;
    if (right <= left)
        return;
    mergesort(a, left, m, tipo);
    mergesort(a, m+1, right, tipo);
    merge(a, left, m, right, tipo);
}

/* Esta funcao lista todos os produtos existentes no sistema por ordem crescente de preco. Se houver 2 ou mais produtos com o 
   mesmo preco, imprime esses por ordem crescente de id de produto. */

void l() {
    int i;
    int vetor[MAX_PRODUTOS] = {0}; /* criacao de vetor auxiliar que tera os idps a serem ordenados */
    for (i = 0; i < total_prod; i++) /* os produtos sao identificados pelo idp, indo de 0 ate ao numero total de produtos - 1 */
        vetor[i] = i;
    mergesort(vetor, 0, total_prod - 1, NATURAIS); /* ordenacao dos idps por preco */
    i = 0;
    printf ("Produtos\n");
    while (i < total_prod) { 
        printf ("* %s %d %d\n", produtos[vetor[i]].descricao, produtos[vetor[i]].preco, produtos[vetor[i]].quantidade);
        i++;
    }
    return;
} 

/* Esta funcao lista todos os produtos de uma encomenda por ordem alfabetica da descricao. */

void L() {
    int i, ide;
    int array[MAX_PESO] = {0}; /* criacao de vetor auxiliar que tera os idps dos produtos na encomenda a serem ordenados */
    getchar();
    scanf ("%d", &ide);
    if (ide >= total_enc) {
        printf ("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    for (i = 0; i < prods_dif_encomendas[ide]; i++) 
        array[i] = encomendas[ide][i].identificador; /* cada slot tem um idp de um produto na encomenda */
    mergesort(array, 0, prods_dif_encomendas[ide] - 1, STRINGS); /* ordenacao dos idps por ordem alfabetica */
    i = 0;
    printf ("Encomenda %d\n", ide);
    while (i < prods_dif_encomendas[ide]) {
        printf ("* %s %d %d\n", produtos[array[i]].descricao, produtos[array[i]].preco, qtd_prods_enc[ide][array[i]]);
        i++;
    }
    return;
}



int main() {
    char c;
    while ((c = getchar()) != 'x') { /* enquanto a letra for diferente de x, o programa nao termina */
        switch (c){ /* corre a funcao correspondente ah letra lida no input e volta a ler uma nova letra */
            case 'a' :
                a();
                break;
            
            case 'q' :
                q();
                break;
            
            case 'N' :
                N();
                break;
            
            case 'A' :
                A();
                break;
            
            case 'r' :
                r();
                break;
            
            case 'R' :
                R();
                break;
            
            case 'C' :
                C();
                break;
            
            case 'p' :
                p();
                break;
          
            case 'E' :
                E();
                break;
            
            case 'm' :
                m();
                break;
            
            
            case 'l' :
                l();
                break;
            
            case 'L' :
                L();
                break; 
        }
    }
    return 0;
}





