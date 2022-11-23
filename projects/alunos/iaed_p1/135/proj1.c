#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define DIM_ENCOM 500    /*limite de encomendas*/
#define DIM_PROD 10000   /*limite de produtos*/
#define DIM_DESC 64    /*limite de caracteres na descricao*/
#define LIM_PESO 200    /*peso max numa encomenda*/


typedef struct produto {
    int preco, peso, quant;
    char descr[DIM_DESC];   /*descricao do produto*/
} produto;

typedef struct encomenda {
    int peso;
    int lstPrdts[DIM_PROD];    /*contem a quantidade do produto id = indice na encom*/
} encomenda;

void adicionaProduto();     /*Adiciona novo produto*/
void adicionaStock();       /*Adiciona stock de um produto*/
void criaEncomenda();       /*Cria uma nova encomenda*/
void encomendaProduto();    /*Adiciona um produto a uma encomenda*/
void removeStock();         /*Remove stock de um produto no sistema*/
void removeProduto();       /*Retira um produto de uma encomenda*/
void custoEncomenda();      /*Devolve o custo total de uma encomenda*/
void alteraCusto();         /*Altera preco de um produto no sistema*/
void prodEncom();           /*Devolve descricao e quantidade de um produto numa encomenda*/
void identEncom();          /*Identifica a encomenda onde um certo produto ocorre mais vezes*/
void listaProd();           /*Lista os produtos no sistema por ordem crescente de preco*/
void listaEncom();          /*Lista os produtos de uma encomenda por ordem alfab?tica*/

void mergesort(int (*condicao)(int, int), int a[], int esq, int dir);   /*Funcao de ordenacao*/
void merge(int (*condicao)(int, int), int a[], int esq, int m, int dir);
int produto404(int idp);     /*O produto nao existe*/
int encomenda404(int ide);   /*A encomenda nao existe*/
int quantidadeInsuf(int idp, int qnt);    /*Quantidade do produto menor que quantidade fornecida*/
int menorPreco(int a, int b);       /*Verifica se o produto 'a' tem menor preco que o produto 'b'*/
int ordemAlf(int a, int b);         /*Verifica se a descricao dos produtos 'a' e 'b' estao por ordem alf*/ 

encomenda sistema[DIM_ENCOM];    /*Lista de encomandas criadas*/
produto produtos[DIM_PROD];      /*Lista dos produtos adicionados*/
int indexProd[DIM_PROD];     /*Vector com idp's para executar merge sort*/
int idpsEncom[DIM_PROD];     /*Vector com indices dos produtos numa encomenda para merge sort*/
int aux[DIM_PROD];     /*Vector aux para merge sort*/
int id_prod = 0;    /*ID do proximo produto adicionado*/
int id_encom = 0;   /*ID da proxima encomenda criada*/


int main() {
    char comm;
    /* Analisa input */
    while (comm != 'x') {           /* 'x' termina o programa */
        switch (comm = getchar()) {
            case 'a':
                adicionaProduto();
                break;
            case 'q':
                adicionaStock();
                break;
            case 'N':
                criaEncomenda();
                break;
            case 'A':
                encomendaProduto();
                break;
            case 'r':
                removeStock();
                break;
            case 'R':
                removeProduto();
                break;
            case 'C':
                custoEncomenda();
                break;
            case 'p':
                alteraCusto();
                break;
            case 'E':
                prodEncom();
                break;
            case 'm':
                identEncom();
                break;
            case 'l':
                listaProd();
                break;
            case 'L':
                listaEncom();
                break;
        }
    }
    return 0; 
}


int produto404(int idp) {
    return (idp >= id_prod);
}


int encomenda404(int ide) {
    return (ide >= id_encom);
}


int quantidadeInsuf(int idp, int qnt) {
    return (produtos[idp].quant < qnt);
}


void adicionaProduto() {
    scanf(" %[^:]:%d:%d:%d", produtos[id_prod].descr, &produtos[id_prod].preco, &produtos[id_prod].peso, &produtos[id_prod].quant);
    /*ID do produto igual ao indice no vetor*/
    indexProd[id_prod] = id_prod;
    printf("Novo produto %d.\n", id_prod);
    id_prod++;
}


void adicionaStock() {
    int idp, qnt;
    scanf(" %d:%d", &idp, &qnt);

    if (produto404(idp)) 
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    
    else
        produtos[idp].quant += qnt;    /*Aumenta a quantidade do produto*/

}


void criaEncomenda() {
    sistema[id_encom].peso = 0;
    printf("Nova encomenda %d.\n", id_encom);
    id_encom++;
}


void encomendaProduto() {
    int ide, idp, qnt;
    scanf(" %d:%d:%d", &ide, &idp, &qnt);
    
    if (encomenda404(ide))
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

    else if (produto404(idp))
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    
    else if (quantidadeInsuf(idp, qnt))
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    
    else if (sistema[ide].peso + qnt*produtos[idp].peso > LIM_PESO)     /*excede o peso m?ximo*/
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    
    else {
        sistema[ide].lstPrdts[idp] += qnt;          /*adiciona quantidade do produto idp*/
        sistema[ide].peso += qnt * produtos[idp].peso;   /*atualiza peso da encom*/
        produtos[idp].quant -= qnt;         /*subtrai a quantidade adicionada 'a quant em stock*/
    }
}


void removeStock() {
    int idp, qnt;
    scanf(" %d:%d", &idp, &qnt);

    if (produto404(idp))
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    
    else if (quantidadeInsuf(idp, qnt))
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qnt,idp);
    
    else
        produtos[idp].quant -= qnt;     
}


void removeProduto() {
    int ide, idp;
    scanf(" %d:%d", &ide, &idp);

    if (encomenda404(ide))
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

    else if (produto404(idp))
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

    else {
        produtos[idp].quant += sistema[ide].lstPrdts[idp];   /*repoe quantidade em stock*/
        sistema[ide].peso -= sistema[ide].lstPrdts[idp] * produtos[idp].peso;   /*atualiza peso da encom*/
        sistema[ide].lstPrdts[idp] = 0;   /*A quantidade do produto <idp> na encomenda <ide> passa a ser 0*/
    }
}


void custoEncomenda() {
    int i, custo = 0;
    int ide;
    scanf(" %d", &ide);

    if (encomenda404(ide))
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);

    else {
        for (i = 0; i < id_prod; i++) {
            if (sistema[ide].lstPrdts[i] != 0)    /*quantidade do produto <i> na encomenda <ide> != 0 */
                custo += sistema[ide].lstPrdts[i] * produtos[i].preco;            
        }
        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}


void alteraCusto() {
    int idp, preco;
    scanf(" %d:%d", &idp, &preco);

    if (produto404(idp))
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    
    else produtos[idp].preco = preco;
}


void prodEncom() {
    int ide, idp;
    scanf(" %d:%d", &ide, &idp);

    if (encomenda404(ide))
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    
    else if (produto404(idp))
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);

    else
        printf("%s %d.\n", produtos[idp].descr, sistema[ide].lstPrdts[idp]);
}


void identEncom() {
    int idp, encom = 0, i;
    scanf(" %d", &idp);

    if (produto404(idp))
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        
    else if (id_encom > 0) {
        for (i = 0; i < id_encom; i++) {
            /*se encom i tem mais quant de prod idp, passa a ser a encom a devolver*/
            if (sistema[i].lstPrdts[idp] > sistema[encom].lstPrdts[idp])
                encom = i;
        }
        if (sistema[encom].lstPrdts[idp] > 0)
            printf("Maximo produto %d %d %d.\n", idp, encom, sistema[encom].lstPrdts[idp]);
    }
}


int menorPreco(int a, int b) {
    return (produtos[a].preco < produtos[b].preco || (produtos[a].preco == produtos[b].preco && a < b));
}


int ordemAlf(int a, int b) {
    if (strcmp(produtos[a].descr, produtos[b].descr) < 0)
        return 1;
    return 0;
}


void listaProd() {    
    int i;

    mergesort(menorPreco, indexProd, 0, id_prod-1);

    printf("Produtos\n");
    for (i = 0; i < id_prod; i++) 
        printf("* %s %d %d\n", produtos[indexProd[i]].descr, produtos[indexProd[i]].preco, produtos[indexProd[i]].quant);
}


void listaEncom() {
    int ide, i, j = 0;
    scanf(" %d", &ide);
    
    if (encomenda404(ide)) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    for (i = 0; i < id_prod; i++) 
        if (sistema[ide].lstPrdts[i] > 0)
            idpsEncom[j++] = i; 
    
    mergesort(ordemAlf, idpsEncom, 0, j-1);

    printf("Encomenda %d\n", ide);
    for (i = 0; i < j; i++) 
        printf("* %s %d %d\n", produtos[idpsEncom[i]].descr, produtos[idpsEncom[i]].preco, sistema[ide].lstPrdts[idpsEncom[i]]);
}

/*mergesort recebe a condicao de ordenacao como argumento*/
/*divide o vector a ordenar, recursivamente*/
void mergesort(int (*condicao)(int, int), int a[], int esq, int dir) {
    int m = (esq + dir)/2;
    
    if (dir <= esq) return;

    mergesort(condicao, a, esq, m);
    mergesort(condicao, a, m+1, dir);
    merge(condicao, a, esq, m, dir);
}

/*ordena o vector*/
void merge(int (*condicao)(int, int), int a[], int esq, int m, int dir) {
    int i, j, k;

    for (i = m+1; i > esq; i--)
        aux[i-1] = a[i-1];
    for (j = m; j < dir; j++)
        aux[dir+m-j] = a[j+1];
    for (k = esq; k <= dir; k++) {
        if (condicao(aux[j], aux[i]))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}