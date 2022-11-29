#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAX_DESC 63
#define MAX_PRODUTOS 10000
#define MAX_ENCOM 500
#define MAX_PESO 200
#define DIM 100


typedef struct produto{
    int preco;
    int peso;
    int qtd;
    int idp;
    char descricao[MAX_DESC];
}Produto;

/*Produto na encomenda simplificado*/
typedef struct simpProdEnc{
    int idp;
    int qtd;
}SimpProd;


typedef struct encomenda{
    SimpProd lstSimpProd[MAX_PESO];
    int pesoTotalEnc;
    int qtdprodutos;
}Encomenda;

/*VARIAVEIS GLOBAIS*/
signed int contadorProdutos = 0, contadorEncomendas = 0;
char str[DIM];
Produto lstProdutos[MAX_PRODUTOS];
Encomenda lstEncomendas[MAX_ENCOM];


/*Prototipagem de funcoes*/
void a();
void l();
void N();
int A();
int L();
int C();
int p();
int r();
int R();
int m();
int q();
int E();

/* Vai regista a string e entra na funcao escolhida */
int main(){

    while (1) {
        int c, i2;
        for (i2 = 0; i2 < DIM - 1 && (c = getchar()) != EOF && c != '\n'; i2++) {
            str[i2] = c;
        }
        str[i2] = '\0';
        switch (str[0]) {
            case 'a':
                a();
                break;
            case 'l':
                l();
                break;
            case 'N':
                N();
                break;
            case 'L':
                L();
                break;
            case 'C':
                C();
                break;
            case 'A':
                A();
                break;
            case 'p':
                p();
                break;
            case 'r':
                r();
                break;
            case 'R':
                R();
                break;
            case 'm':
                m();
                break;
            case 'q':
                q();
                break;
            case 'E':
                E();
                break;
            case 'x':
                return 0;

        }
    }

}

/* -----------------------FUNCOES AUX--------------------- */

void ordenarString(int qtd,SimpProd lstOrd[],SimpProd enc[]){ /*ordena string alfabeticamente com recurso
 * ao insertion sort*/

    int i1, i2, i3, i4;
    char alist[MAX_PESO][MAX_DESC] = {0};
    char key[MAX_DESC] = {0};
    int keyQt = 0;
    int keyID = 0;
    for (i3 = 0; i3 < qtd; ++i3) {
        lstOrd[i3].idp = enc[i3].idp;
        lstOrd[i3].qtd = enc[i3].qtd;
    }
    for (i4 = 0; i4 < qtd; ++i4) {
        strcpy(alist[i4],lstProdutos[enc[i4].idp].descricao);
    }
    for (i1 = 1; i1 < qtd; i1++) {
        keyID = lstOrd[i1].idp;
        keyQt = lstOrd[i1].qtd;
        strcpy(key,alist[i1]);
        i2 = i1 - 1;

        while (i2 >= 0 && strcmp(alist[i2],key) > 0) {
            lstOrd[i2 + 1].idp = lstOrd[i2].idp;
            lstOrd[i2 + 1].qtd = lstOrd[i2].qtd;
            strcpy(alist[i2 + 1],alist[i2]);
            i2 = i2 - 1;
        }
        strcpy(alist[i2 + 1],key);
        lstOrd[i2+1].idp = keyID;
        lstOrd[i2+1].qtd = keyQt;
    }
}


void copiarLstProdutos(Produto source[], Produto dest[]){/*copia lista de produtos*/

    int i;
    for(i=0; i < contadorProdutos; i++) {
        dest[i].preco = source[i].preco;
        dest[i].qtd = source[i].qtd;
        dest[i].peso = source[i].peso;
        dest[i].idp = source[i].idp;
        strcpy(dest[i].descricao, source[i].descricao);    }
}
void merge(Produto arr[], int l, int m, int r){

    int i1, i2, i3;
    int n1 = m - l + 1;
    int n2 = r - m;

    Produto L[MAX_PRODUTOS / 2], R[MAX_PRODUTOS / 2];

    for (i1 = 0; i1 < n1; i1++)
        L[i1] = arr[l + i1];
    for (i2 = 0; i2 < n2; i2++)
        R[i2] = arr[m + 1 + i2];

    i1 = 0;
    i2 = 0;
    i3 = l;
    while (i1 < n1 && i2 < n2){
        if (L[i1].preco <= R[i2].preco){
            arr[i3] = L[i1];
            i1++;
        }
        else{
            arr[i3] = R[i2];
            i2++;
        }
        i3++;
    }

    while (i1 < n1){
        arr[i3] = L[i1];
        i1++;
        i3++;
    }

    while (i2 < n2){
        arr[i3] = R[i2];
        i2++;
        i3++;
    }
}
void mergeSort(Produto arr[], int l, int r){

    if (l < r){
        int m = l+(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

int encontrarPosicao(int idpPedido,int idePedido){ /*encontra o indice da lista de produtos,
 * atraves do idpPedido*/

    int pos = 0,i;
    for (i = 0; i < lstEncomendas[idePedido].qtdprodutos; ++i) {
        if (lstEncomendas[idePedido].lstSimpProd[i].idp == idpPedido) {
            pos = i;
            return pos;
        }
    }
    return -1;
}

/*--------------------------------------FUNCOES PEDIDAS--------------------------------*/

void a() {/*adiciona um novo produto ao sistema*/

    sscanf(str, "%*s %[^:]:%d:%d:%d", lstProdutos[contadorProdutos].descricao,
           &lstProdutos[contadorProdutos].preco, &lstProdutos[contadorProdutos].peso,
           &lstProdutos[contadorProdutos].qtd);
    lstProdutos[contadorProdutos].idp = contadorProdutos;
    printf("%s %d%s\n", "Novo produto", contadorProdutos, ".");
    contadorProdutos = contadorProdutos + 1;
}

void l() {/*lista todos os produtos existentes no sistema por ordem crescente de preco*/

    int i;
    Produto novoV[MAX_PRODUTOS];
    copiarLstProdutos(lstProdutos, novoV);
    mergeSort(novoV,0, contadorProdutos - 1);
    printf("%s\n","Produtos");
    for (i = 0; i < contadorProdutos ; ++i) {
        printf("%c %s %d %d\n",'*',novoV[i].descricao,
               novoV[i].preco, novoV[i].qtd);
    }

}

void N(){/*cria uma nova encomenda*/

    printf("%s %d%s\n","Nova encomenda",contadorEncomendas,".");
    contadorEncomendas++;

}

int A() { /*adiciona um produto a uma encomenda*/

    int idePedido = 0, idpPedido = 0, qtdPedida = 0,i1 = 0;
    sscanf(str, "%*s %d:%d:%d", &idePedido, &idpPedido, &qtdPedida);

    if (idePedido > contadorEncomendas - 1){
        printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idpPedido,
               "a encomenda", idePedido, ". Encomenda inexistente.");
        return 0;
    }
    if (idpPedido > contadorProdutos - 1){
        printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idpPedido,
               "a encomenda", idePedido, ". Produto inexistente.");
        return 0;
    }
    if (qtdPedida > lstProdutos[idpPedido].qtd){
        printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idpPedido,
               "a encomenda", idePedido,
               ". Quantidade em stock insuficiente.");
        return 0;
    }
    if ((lstEncomendas[idePedido].pesoTotalEnc + (qtdPedida * lstProdutos[idpPedido].peso)) > 200){
        printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idpPedido,
               "a encomenda", idePedido,
               ". Peso da encomenda excede o maximo de "
               "200.");
        return 0;
    }

    for (i1 = 0; i1 < lstEncomendas[idePedido].qtdprodutos ; ++i1) {
        if (lstEncomendas[idePedido].lstSimpProd[i1].idp == idpPedido){ /* caso ja exista o produto pedido*/
            lstEncomendas[idePedido].lstSimpProd[i1].qtd += qtdPedida;
            lstProdutos[idpPedido].qtd -= qtdPedida;
            lstEncomendas[idePedido].pesoTotalEnc += (lstProdutos[idpPedido].peso * qtdPedida);
            return 0;
        }
    }
    lstEncomendas[idePedido].lstSimpProd[lstEncomendas[idePedido].qtdprodutos].idp = idpPedido;
    lstProdutos[idpPedido].qtd -= qtdPedida;
    lstEncomendas[idePedido].lstSimpProd[lstEncomendas[idePedido].qtdprodutos].qtd = qtdPedida;
    lstEncomendas[idePedido].pesoTotalEnc+= lstProdutos[idpPedido].peso * qtdPedida;
    lstEncomendas[idePedido].qtdprodutos++;

    return 0;
}


int L(){/* lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/

    int idePedido = 0;
    int i;
    SimpProd lstSProdOrd[200] = {0};
    sscanf(str, "%*s %d", &idePedido);
    if (idePedido > contadorEncomendas - 1){
        printf("%s %d%s\n", "Impossivel listar encomenda", idePedido,". Encomenda inexistente.");
        return 0;
    }
    ordenarString(lstEncomendas[idePedido].qtdprodutos,lstSProdOrd,lstEncomendas[idePedido].lstSimpProd);

    printf("%s %d\n","Encomenda",idePedido);
    for (i = 0; i < lstEncomendas[idePedido].qtdprodutos ; ++i) {
        printf("%c %s %d %d\n", '*', lstProdutos[lstSProdOrd[i].idp].descricao,
               lstProdutos[lstSProdOrd[i].idp].preco, lstSProdOrd[i].qtd);

    }

    return 0;
}
int C() { /* calcula o custo de uma encomenda*/

    int idePedido = 0;
    int total = 0,i;
    sscanf(str, "%*s %d", &idePedido);
    if (idePedido > contadorEncomendas - 1) {
        printf("%s%d%s\n", "Impossivel calcular custo da encomenda ", idePedido,
               ". Encomenda inexistente.");
        return 0;
    }
    for (i = 0; i < lstEncomendas[idePedido].qtdprodutos; ++i) {
        total += lstProdutos[lstEncomendas[idePedido].lstSimpProd[i].idp].preco * lstEncomendas[idePedido].lstSimpProd[i].qtd;
    }
    printf("%s %d %d%c\n","Custo da encomenda",idePedido,total,'.');
    return 0;
}

int p(){ /* altera o preco de um produto existente no sistema*/

    int idpPedido,preco;
    sscanf(str, "%*s %d:%d", &idpPedido, &preco);
    if (idpPedido > contadorProdutos - 1){
        printf("%s%d%s\n", "Impossivel alterar preco do produto ", idpPedido,
               ". Produto inexistente.");
        return 0;
    }

    lstProdutos[idpPedido].preco = preco;

    return 0;
}

int r(){ /* remove stock a um produto existente*/

    int idpPedido,qtd;
    sscanf(str, "%*s %d:%d", &idpPedido, &qtd);
    if (idpPedido > contadorProdutos - 1) {
        printf("%s %d%s\n", "Impossivel remover stock do produto", idpPedido,
               ". Produto inexistente.");
        return 0;
    }
    if (qtd > lstProdutos[idpPedido].qtd) {
        printf("%s %d %s %d %s\n", "Impossivel remover", qtd, "unidades do produto",
               idpPedido,"do stock. Quantidade insuficiente.");
        return 0;
    }
    lstProdutos[idpPedido].qtd -= qtd;
    return 0;
}

int R(){/* remove um produto de uma encomenda */

    int idpPedido,idePedido, pos = 0, i2;
    sscanf(str, "%*s %d:%d", &idePedido, &idpPedido);
    if (idePedido > contadorEncomendas - 1){
        printf("%s %d %s %d%s\n", "Impossivel remover produto", idpPedido,
               "a encomenda",idePedido,". Encomenda inexistente.");
        return 0;
    }
    if (idpPedido > contadorProdutos - 1) {
        printf("%s %d %s %d%s\n", "Impossivel remover produto", idpPedido,
               "a encomenda", idePedido, ". Produto inexistente.");
        return 0;
    }
    pos = encontrarPosicao(idpPedido,idePedido);
    if (pos != -1) { /*apenas corre se o produto pedido estiver na encomenda*/
        lstEncomendas[idePedido].pesoTotalEnc -= (lstProdutos[idpPedido].peso * lstEncomendas[idePedido].lstSimpProd[pos].qtd);

        lstProdutos[idpPedido].qtd += lstEncomendas[idePedido].lstSimpProd[pos].qtd;
        for (i2 = pos; i2 < lstEncomendas[idePedido].qtdprodutos; ++i2) {
            lstEncomendas[idePedido].lstSimpProd[i2] = lstEncomendas[idePedido].lstSimpProd[i2 + 1];
            lstEncomendas[idePedido].lstSimpProd[i2 + 1].idp = 0;
            lstEncomendas[idePedido].lstSimpProd[i2 + 1].qtd = 0;
        }
        lstEncomendas[idePedido].qtdprodutos -= 1;

        return 0;
    }
    return 0;
}
int m() {/* retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/

    int idpPedido, ideKey = -1, qtdKey = 0, pos = 0, i1;
    sscanf(str, "%*s %d", &idpPedido);
    if (contadorEncomendas == 0)
        return 0;
    if (idpPedido > contadorProdutos - 1) {
        printf("%s %d%s\n","Impossivel listar maximo do produto",
               idpPedido,". Produto inexistente.");
        return 0;
    }
    for (i1 = 0; i1 < contadorEncomendas; ++i1) {
        pos = encontrarPosicao(idpPedido,i1);
        if (pos > -1 && lstEncomendas[i1].lstSimpProd[pos].qtd > qtdKey) {
            qtdKey = lstEncomendas[i1].lstSimpProd[pos].qtd;
            ideKey = i1;
        }
    }
    if (ideKey == -1)
        return 0;
    else {
        printf("%s %d %d %d%c\n", "Maximo produto", idpPedido, ideKey, qtdKey, '.');
        return 0;
    }
}
int q(){/* adiciona stock a um produto existente no sistema */

    int idpPedido,qtdAd;
    sscanf(str, "%*s %d:%d", &idpPedido, &qtdAd);
    if (idpPedido > contadorProdutos - 1) {
        printf("%s %d %s\n","Impossivel adicionar produto",idpPedido,
               "ao stock. Produto inexistente.");
        return 0;
    }
    lstProdutos[idpPedido].qtd += qtdAd;
    return 0;
}

int E(){/* retorna a descricao e a quantidade de um produto numa dada encomenda*/

    int idePedido, idpPedido, pos = 0;
    sscanf(str, "%*s %d:%d", &idePedido, &idpPedido);
    if (idePedido > contadorEncomendas - 1){
        printf("%s %d%s\n","Impossivel listar encomenda",idePedido,
               ". Encomenda inexistente.");
        return 0;
    }
    if (idpPedido > contadorProdutos - 1){
        printf("%s %d%s\n","Impossivel listar produto",idpPedido,
               ". Produto inexistente.");
        return 0;
    }
    pos = encontrarPosicao(idpPedido,idePedido);
    if (pos != -1){
        printf("%s %d%c\n",lstProdutos[idpPedido].descricao,
               lstEncomendas[idePedido].lstSimpProd[pos].qtd,'.');
        return 0;
    }
    else{
        printf("%s %d%c\n",lstProdutos[idpPedido].descricao,0,'.');
        return 0;
    }
}


