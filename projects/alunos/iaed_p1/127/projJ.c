#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAXDES 63              /* numero maximo de carateres numa descricao */    
#define MAXPROD 10000          /* quantidade maxima de produtos armazenados num sistema */
#define MAXENCOM 500           /* quantidade maxima de encomendas existentes num instante */
#define MAXPESO 200            /* peso maximo que uma encomenda pode ter */


/*************** Definicao dos tipos: produto e encomenda *****************************/
typedef struct produto{
    int idp;            /* ID do produto */
    char des[MAXDES];   /* descricao do produto */
    int preco;          /* preco do produto */
    int peso;           /* peso do produto */
    int qtd;            /* quantidade em stock do produto */
}Produto;

typedef struct encomenda{
    int ide;                      /* ID da encomenda */
    int pesoTotal;                /* Peso total da encomenda */

    /* Estrutura de apresentacao das encomendas*/
    /* a cada indice i do array itens,corresponde o indice i do array quantidades*/
    
    int itens[MAXPROD];           /* array com os ID's dos itens na encomenda */
    int quantidades[MAXPROD];     /* array com as quantidades dos itens na encomenda */
    int contagem;                 /* contagem de itens na encomenda(sem considerar quantidades) */  
}Encomenda;
/***************************************************************************************/

/********************************* variaveis globais ***********************************/
int indice_p = 0;
Produto lista_p[MAXPROD];
int indice_e = 0;
Encomenda lista_e[MAXENCOM];
/***************************************************************************************/

/********************************* funcoes auxiliares************************************/


/* Esta funcao encontra o index em que se encontra um produto especifico numa encomenda */
int acharProdE(int idp, int ide){ 
    int i; 
    for (i = 0; i < lista_e[ide].contagem ; i++){
        if (idp == lista_e[ide].itens[i]) {
            return i;
        }
    }
    return -1;   
}

/* Esta funcao representa de forma legivel os produtos registados no sistema */
void mostra_itens(){
    int y;
    for (y = 0; y < indice_p; y++){
        printf("[%d] %s / %d / %d / %d \n",y,lista_p[y].des,lista_p[y].preco,lista_p[y].peso,lista_p[y].qtd);
    }
}

/* Esta funcao representa de forma legivel os produtos presentes numa encomenda especifica */
void mostra_encomendas(){
    int ide;
    int i;
    scanf(" %d", &ide);
    printf("[%d]",ide);
    for (i = 0; i < lista_e[ide].contagem; i++){
        printf(" %d:%d /",lista_e[ide].itens[i],lista_e[ide].quantidades[i]);
    }
    printf("    peso total: %d\n",lista_e[ide].pesoTotal);
}
/********************************************************************************************/

/******************************** comandos principais ***************************************/

/* 
 * Esta funcao adiciona um produto ao sistema,recebendo a sua descricao, preco, peso e quantidade em stock.
 * A funcao gera um ID para o produto.
 */
void addProd(){
    Produto item;
    int preco,peso,qtd;
    scanf(" %[^:]:%d:%d:%d", item.des, &preco, &peso, &qtd);
    item.preco = preco;
    item.peso = peso;
    item.qtd = qtd;
    item.idp = indice_p;
    lista_p[indice_p] = item;
    printf("Novo produto %d.\n",indice_p);
    indice_p++;
}

/* Esta funcao acrescenta uma certa quantidade de produto ao seu stock */
void addStock(){
    int idp;          
    int qtd_add;        /*quantidade a adicionar*/
    scanf(" %d:%d", &idp, &qtd_add);
    if (idp >= indice_p){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
    }
    else {
        lista_p[idp].qtd += qtd_add;
    }
}

/* 
 * Esta funcao gera uma encomenda nova.
 * Tambem define o ID da encomenda.
 * Coloca o peso total e a contagem de itens a 0.
 */
void novaE(){
    Encomenda E;
    E.ide = indice_e;
    E.pesoTotal = 0;
    E.contagem = 0;
    lista_e[indice_e] = E;
    printf("Nova encomenda %d.\n",indice_e);
    indice_e++;
}

/* Esta funcao adiciona uma quantidade 'x' de um produto a uma determinada encomenda */
void addProdE(){
    int contador;                 
    int ide;
    int idp;
    int qtd;
    scanf(" %d:%d:%d", &ide, &idp, &qtd);
    if (indice_e <= ide) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (indice_p <= idp) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    if (qtd > lista_p[idp].qtd) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }
    if ((qtd*lista_p[idp].peso) + lista_e[ide].pesoTotal > MAXPESO) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }

    contador = acharProdE(idp,ide);

    if (contador != -1) {
        lista_e[ide].quantidades[contador] += qtd;
        lista_p[idp].qtd -= qtd;
        lista_e[ide].pesoTotal += qtd*lista_p[idp].peso;
    }
    
    else {
        lista_e[ide].itens[lista_e[ide].contagem] = idp;
        lista_e[ide].quantidades[lista_e[ide].contagem] = qtd;
        lista_p[idp].qtd -= qtd;
        lista_e[ide].pesoTotal += qtd*lista_p[idp].peso;
        lista_e[ide].contagem++;
            
    }      
}

/* Esta funcao retira uma certa quantidade de um produto ao seu stock */
void remStock(){
    int idp;
    int qtd;
    scanf(" %d:%d", &idp, &qtd);
    if (idp >= indice_p){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
    if (lista_p[idp].qtd-qtd<0){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
    }
    lista_p[idp].qtd -= qtd;

}

/* Esta funcao remove um produto de uma encomenda, ajustando a sua contagem de itens e o seu peso total */
void remProdE(){
    int ide;
    int idp;
    int i;
    int posicao;        /* variavel usada para registar a posicao dum produto numa encomenda */
    scanf(" %d:%d", &ide, &idp);
    if (indice_e <= ide) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (indice_p <= idp) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    

    posicao = acharProdE(idp,ide);
    
    if ( posicao == -1){
        return;              /* caso particular em que o produto nao esta na encomenda */
    }
    
    lista_p[idp].qtd += lista_e[ide].quantidades[posicao];

    lista_e[ide].pesoTotal -= lista_e[ide].quantidades[posicao]*lista_p[idp].peso;

    for (i = posicao; i < lista_e[ide].contagem - 1; i++){
        lista_e[ide].itens[i] = lista_e[ide].itens[i+1];
        lista_e[ide].quantidades[i] = lista_e[ide].quantidades[i+1];
    }

    lista_e[ide].contagem -= 1;
}

/* Esta funcao calcula o preco total de uma encomenda no instante em que e executada */
void calculaPreco(){
    int total = 0;          /* registo do valor total do custo da encomenda */
    int ide;
    int i;
    scanf(" %d", &ide);
    if (ide >= indice_e) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;  
    }
    
    for (i = 0; i < lista_e[ide].contagem; i++){
        total += lista_e[ide].quantidades[i]*lista_p[lista_e[ide].itens[i]].preco;
    }
    printf("Custo da encomenda %d %d.\n", ide, total);
}

/* Esta funcao altera o preco de um determinado produto */
void alteraPreco(){
    int idp;
    int novoPreco;              /* novo preco a registar no produto*/
    scanf(" %d:%d", &idp, &novoPreco);
    if (indice_p <= idp) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }
    lista_p[idp].preco = novoPreco;
}

/* 
 * Esta funcao devolve a informacao relativa a um produto numa encomenda especifica.
 * A informacao devolvida inclui a descricao do produto e a quantidade dele naquela encomenda.
 */
void infoProdE(){
    int ide;
    int idp;
    scanf(" %d:%d", &ide, &idp);
    if (indice_e <= ide) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    if (indice_p <= idp) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    if (acharProdE(idp,ide) == -1){
        printf("%s %d.\n", lista_p[idp].des, 0);
        return;
    }
    
    printf("%s %d.\n", lista_p[idp].des, lista_e[ide].quantidades[acharProdE(idp,ide)]);
}

/* Esta funcao recebe um ID dum produto e encontra a encomenda em que ele existe em maior quantidade */
void EncomProdQtd(){
    int idp;
    int maiorQtd = 0;       /* variavel usada para registar a maior quantidade de produto encontrada numa encomenda ate entao */
    int ideCorrespondente = -1;     /* ide da encomenda correspondente ao registo da maiorQtd */
    int i;
    int e;
    scanf(" %d", &idp);
    if (idp >= indice_p) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    if (indice_e == 0) {
        return;
    }
    for (i = 0; i < indice_e; i++){
        e = acharProdE(idp,i);
        if (e > -1 && lista_e[i].quantidades[e] > maiorQtd) {
            maiorQtd = lista_e[i].quantidades[e];
            ideCorrespondente = lista_e[i].ide;
        }
    }
    if (maiorQtd > 0) {
        printf("Maximo produto %d %d %d.\n", idp, ideCorrespondente, maiorQtd);
    }
    
}
    

/* Esta funcao devolve uma lista de todos os produtos, organizados por preco de forma crescente */
void organizaPrecos(){

    Produto ordenar[MAXPROD];   /* array de produtos, usado para fazer uma copia modificavel da lista de produtos */
    int i;
    int e;
    
    int id_menor;           /* variavel que auxilia no algoritmo de ordenacao implementado */
    Produto copia;          /* variavel que auxilia no algoritmo de ordenacao implementado */

    printf("Produtos\n");
    

    for (i = 0; i < indice_p; i++){
        ordenar[i] = lista_p[i];
    }

    for (i = 0; i < indice_p; i++){
        id_menor = i;
        for (e = i+1; e < indice_p; e++){
            if (ordenar[id_menor].preco > ordenar[e].preco) {
                id_menor = e;
            }  
            if (ordenar[id_menor].preco == ordenar[e].preco && ordenar[id_menor].idp > ordenar[e].idp) {
                id_menor = e;
            }
        }
        copia = ordenar[id_menor];
        ordenar[id_menor] = ordenar[i];
        ordenar[i] = copia;
    }
    
    for (i = 0; i < indice_p; i++){
        printf("* %s %d %d\n", ordenar[i].des, ordenar[i].preco, ordenar[i].qtd);  
    }
    
}


/* Esta funcao devolve uma lista dos produtos numa encomenda, organizados alfabeticamente */
void organizaDesE(){
    
    int ide;
    int ordenar[MAXPROD];          /* array de ID's de produtos, usado para fazer uma copia modificavel do registo dos ID's dos itens da encomenda */
    int i;
    int e;
    int reg;                       /* variavel que auxilia no algoritmo de ordenacao implementado */
    scanf(" %d", &ide);
    
    if (indice_e > ide) {
        printf("Encomenda %d\n",ide);
    }
    else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    
    
    for (i = 0; i < lista_e[ide].contagem; i++){
        ordenar[i] = lista_e[ide].itens[i];
    }
    

    for (i = 0; i < lista_e[ide].contagem -1; i++){
        for (e = i+1; e < lista_e[ide].contagem; e++){
            if (0 < strcmp(lista_p[ordenar[i]].des,lista_p[ordenar[e]].des)) {
                reg = ordenar[e];
                ordenar[e] = ordenar[i];
                ordenar[i] = reg;
            }
        }
    }
    
    for (i = 0; i < lista_e[ide].contagem; i++){
        e = acharProdE(ordenar[i],ide);
        printf("* %s %d %d\n", lista_p[ordenar[i]].des, lista_p[ordenar[i]].preco, lista_e[ide].quantidades[e]);
    }
}
    
/****************************** Funcao MAIN ***********************************/
int main(){
    char fun;
    while (1 > 0){
        scanf("%c", &fun);
        switch(fun){
            case 'a':
                addProd();
            break;
            case 'q':
                addStock();
            break;
            case 'N':
                novaE();
            break;
            case 'A':
                addProdE();
            break;
            case 'r':
                remStock();
            break;
            case 'R':
                remProdE();
            break;
            case 'C':
                calculaPreco();
            break;
            case 'p':
                alteraPreco();
            break;
            case 'E':
                infoProdE();
            break;
            case 'm':
                EncomProdQtd();
            break;
            case 'l':
                organizaPrecos();
            break;
            case 'L':
                organizaDesE();
            break;
            case 'k':
                mostra_itens();
            break;
            case 'K':
                mostra_encomendas();
            break;
            case 'x':
                return 0;

        }
    }
    
    return 0;
}
/******************************************************************************/