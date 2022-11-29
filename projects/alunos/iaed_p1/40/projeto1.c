#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* The maximum number of identifiers. */
#define MAXIDEN 10000

/* The maximum number of caracters plus \0 of description. */
#define MAXCAR 64

/* The maximum number of orders. */
#define MAXENC 500

/* The maximum number of weights units. */
#define MAXWEIGHT 200

/* Structure of a system. */
typedef struct{
    char desc[MAXCAR]; /* Descripition of product. */  
    int price;
    int weight;
    int qtd;
    int enc[MAXENC]; /* Qtd presents in each order. */
} System;

/* Array of Systems. */
System sys[MAXIDEN];

/* Structure of a list. */
typedef struct{
    int idp;
    char desc[MAXCAR]; /* Descripition of product. */  
    int price;
    int qtd;
} Listpr;

/* Array of listprs. */
Listpr lp[MAXIDEN], aux[MAXIDEN];

/* Number of the new products. */
int npr = 0;

/* Number of new orders. */
int nenc = 0;


/* Auxiliar functions.*/

/* Mergesort by price. */
void mergepriceSort(int left, int m, int right, Listpr a[]){

    int i, j, k;

    for (i = m+1; i > left; i--){
        aux[i-1] = a[i-1];
    }

    for (j = m; j < right; j++){
        aux[right+m-j] = a[j+1];
    }

    for (k = left; k <= right; k++){
        if (aux[j].price < aux[i].price)
            a[k] = aux[j--];
        else if(aux[j].price == aux[i].price && aux[j].idp < aux[i].idp)
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}

void mergeprice(int left, int right, Listpr a[]){
    int m = (right + left)/2;
    
    if (right <= left)
        return;
    
    mergeprice(left, m, a);
    mergeprice(m+1, right, a);
    mergepriceSort(left, m, right, a);
}


/* Mergesort by description. */
void mergedescSort(int left, int m, int right, Listpr a[]){

    int i, j, k;

    for (i = m+1; i > left; i--){
        aux[i-1] = a[i-1];
    }

    for (j = m; j < right; j++){
        aux[right+m-j] = a[j+1];
    }

    for (k = left; k <= right; k++){
        if (strcmp(aux[j].desc, aux[i].desc)<0)
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}


void mergedesc(int left, int right,Listpr a[]){
    int m = (right + left)/2;
    
    if (right <= left)
        return;
    
    mergedesc(left, m,a);
    mergedesc(m+1, right,a);
    mergedescSort(left, m, right,a);
}


/* Main functions. */

/* Adds new product to system. */
void __a__(){

    /* Remove the space between command and description. */
    getchar();
    
    scanf("%[^:]:%d:%d:%d", sys[npr].desc, &sys[npr].price, &sys[npr].weight, &sys[npr].qtd);
    
    if(npr >= MAXIDEN){
        memset(&sys[npr], 0, sizeof(System));
    }
    else{        
        printf("Novo produto %d.\n", npr++);
    } 
}


/* Adds stock to an existing product in the system. */
void __q__(){
    
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);

    if(idp < npr){
        sys[idp].qtd += qtd;
    }
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}


/* Creates a new order. */
void __N__(){
    if(nenc < MAXENC){
        printf("Nova encomenda %d.\n", nenc++);
    }
}


/*Adds a product in the order.*/
void __A__(){
    
    int ide, idp, qtd, weighttotal=0, i;

    scanf("%d:%d:%d", &ide, &idp, &qtd);

    if(ide >= nenc){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    if(idp >= npr){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    if(sys[idp].qtd < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }

    for(i=0; i < npr; i++){
        weighttotal += sys[i].enc[ide] * sys[i].weight; 
    }
    
    if((weighttotal + sys[idp].weight * qtd) > MAXWEIGHT){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }

    sys[idp].qtd -= qtd;
    sys[idp].enc[ide] += qtd;
}


/* Removes stock of an existing product. */
void __r__(){
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);

    if(idp >= npr){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
    else if(sys[idp].qtd < qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else{
        sys[idp].qtd -= qtd;
    }
}


/* Removes a product of an order. */
void __R__(){
    int ide, idp;
    scanf("%d:%d", &ide, &idp);

    if(ide >= nenc){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    if(idp >= npr){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    
    sys[idp].qtd += sys[idp].enc[ide];
    sys[idp].enc[ide] = 0;
}


/* Calculates the price of order. */
void __C__(){
    int ide, pricetotal=0, i;

    scanf("%d", &ide);

    if(ide >= nenc){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    for(i = 0; i < npr; i++){
        pricetotal += sys[i].price * sys[i].enc[ide];
    }
    printf("Custo da encomenda %d %d.\n", ide, pricetotal);
}


/* Change the price of an existing product in the system. */
void __p__(){
    int idp, price;
    scanf("%d:%d", &idp, &price);

    if(idp >= npr){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        sys[idp].price = price;
    }
}


/* Shows the products descripion and stock in an order. */
void __E__(){
    int ide, idp;
    scanf("%d:%d", &ide, &idp);

    if(npr <= idp){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    
    if(nenc <= ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    printf("%s %d.\n", sys[idp].desc, sys[idp].enc[ide]);
}


/* Lists the orders identifier in which the given product occurs most often. */
void __m__(){
    int i, idp, qtdmax=0, encmax=0, flag=0;
    
    scanf("%d", &idp);

    if(npr <= idp){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }

    for (i=0; i < nenc; i++){
        if(sys[idp].enc[i] > qtdmax){
            qtdmax = sys[idp].enc[i];
            encmax = i;
            flag=1;
        }  
    }

    if(flag){
        printf("Maximo produto %d %d %d.\n", idp, encmax, qtdmax);
    }
}


/* Lists all products in the system by ascending price order. */
void __l__(){
    int left = 0, right = npr-1, m, l;
    
    memset(lp, 0, sizeof(Listpr)*npr);

    printf("Produtos\n");

    for(l = 0; l < npr; l++){
        lp[l].idp = l;
        strcpy(lp[l].desc, sys[l].desc);
        lp[l].price = sys[l].price;
        lp[l].qtd = sys[l].qtd;
    }

    mergeprice(left, right, lp);

    for(m = 0; m < npr; m++){
        printf("* %s %d %d\n", lp[m].desc, lp[m].price, lp[m].qtd);
    }
   
}


/* Lists all products in an order in alphabetical order from the description. */
void __L__(){
    int ide, l, right, left=0, m, num=0;

    scanf("%d",&ide);
    
    if(nenc <= ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    memset(lp, 0, sizeof(Listpr)*npr);

    printf("Encomenda %d\n", ide);

    for(l = 0; l < npr; l++){
        if(sys[l].enc[ide] != 0){
            strcpy(lp[num].desc, sys[l].desc);
            lp[num].price = sys[l].price;
            lp[num++].qtd = sys[l].enc[ide];
        }
    }
    
    right = num-1;

    mergedesc(left, right, lp);

    for(m = 0; m < num; m++){
        printf("* %s %d %d\n", lp[m].desc, lp[m].price, lp[m].qtd);
    }   
}


/* Reads the commands and executes it and terminates when appears the command x. */
int main(){

    char command;

    while((command = getchar()) != 'x'){
        switch(command){
            case 'a':
                __a__();
                break;

            case 'q':
                __q__();
                break;

            case 'N':
                __N__();
                break;

            case 'A':
                __A__();
                break;
    
            case 'r':
                __r__();
                break;
            
            case 'R':
                __R__();
                break;
            
            case 'C':
                __C__();
                break;
            
            case 'p':
                __p__();

                break;
            
            case 'E':
                __E__();

                break;

             case 'm':
                __m__();
                break;
            
            case 'l':
                __l__();
                break;
            
            case 'L':
                __L__();
                break;
        }

        /* catch \n */
        getchar();
    }

    return 0;
}