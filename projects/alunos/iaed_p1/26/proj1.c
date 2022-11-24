#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Definicao de Constantes*/
#define P 10000
#define NOMEMAX 63
#define N_ENCOMENDAS 500

/*Definicao de Estruturas*/

typedef struct produtos{

    int idp;
    int preco, peso, qtd;
    char descricao[NOMEMAX];
   
}Produto;

Produto produto[P];                        /*vector onde sao guardados os elementos do tipo produto*/
int p_size[N_ENCOMENDAS];
int p_size_out = 0;                         /*numero de produtos guardados*/
                                

typedef struct encomendas{
    int ide;
    Produto produto[P];
    int peso_t;
}Encomenda;

Encomenda encomenda[N_ENCOMENDAS];          /*vector onde sao guardados os elementos do tipo encomenda*/
int e_size = 0;                                  /*numero de encomendas guardadas*/


/*codigo*/

/*adiciona um novo produto ao sistema*/

void adicionaProduto(){

    char descricao[NOMEMAX];
    int preco,peso,qtd;
    scanf("%[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
    strcpy(produto[p_size_out].descricao, descricao);
    produto[p_size_out].preco = preco;
    produto[p_size_out].peso = peso;
    produto[p_size_out].qtd = qtd;
    printf("Novo produto %d.\n", p_size_out);
    p_size_out++;
}

/*adiciona stock a um produto existente no sistema*/

void adicionaStock(){
    int idp, qtd;

    scanf("%d:%d",&idp,&qtd);
    if (idp < p_size_out){
        produto[idp].qtd = produto[idp].qtd + qtd;}
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);}
}

/*funcao auxiliar que faz a procura de um produto numa encomenda, se ele existir retorna o indice da posicao em que esta*/
int searchForProductInEcom(int ide, int idp){
    int i;
    for(i=0;i<p_size[ide];i++){
        if(encomenda[ide].produto[i].idp == idp)
            return i;
    }
    return -1;
}

void A(){
    int ide,i, idp, qtd, p, q, peso_max;
    int n = 200;
    scanf("%d:%d:%d", &ide,&idp,&qtd);

    q = produto[idp].qtd;
    p = produto[idp].peso;
    peso_max = (p * qtd ) + encomenda[ide].peso_t;

/*------------------------------ERROS-------------------------------------------------------------*/
    if(ide > e_size - 1){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;}

    else if(idp > p_size_out - 1){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;}

    else if(qtd > q){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;}
    
    else if(peso_max > n ){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;}


    /* ve se o produto esta dentro da encomenda */

    i = searchForProductInEcom(ide,idp);

    /* se estiver faz */
    if (i!=-1){
        encomenda[ide].produto[i].qtd = encomenda[ide].produto[i].qtd + qtd;
        produto[idp].qtd = produto[idp].qtd - qtd;
        encomenda[ide].peso_t = peso_max;
    }
    /* se NAO estiver faz*/
    else{
        encomenda[ide].produto[p_size[ide]].qtd = qtd;
        encomenda[ide].produto[p_size[ide]].peso = produto[idp].peso;
        encomenda[ide].produto[p_size[ide]].preco = produto[idp].preco;
        strcpy(encomenda[ide].produto[p_size[ide]].descricao, produto[idp].descricao);
        encomenda[ide].produto[p_size[ide]].idp = idp;
        p_size[ide]++;

        produto[idp].qtd = produto[idp].qtd - qtd;
        encomenda[ide].peso_t = peso_max;
    }
}

/*se a qtd do produto existente no sistema menos a qtd q deseja remover for negativa nao sera possivel fazer a remocao*/

void r(){
    int idp, qtd;
    
    scanf("%d:%d", &idp, &qtd);
    
    if (idp < p_size_out){
        if((produto[idp].qtd - qtd) < 0){           
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
        }
        else{
            produto[idp].qtd = produto[idp].qtd - qtd;}
    }
    else{
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);}
}

/*Faz remocao de um produto numa encomenda*/

void R(){
    int i,p,q, ide, idp;
    scanf("%d:%d", &ide, &idp);

/*------------------------------ERROS-------------------------------------------------------------*/

    if (ide > e_size - 1){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;}
    if(idp > p_size_out - 1){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;}
    
    /*procura o produto na encomenda*/
    for(i = 0; i < p_size[ide]; i++){
        if (encomenda[ide].produto[i].idp == idp ){
            
            p = encomenda[ide].produto[i].peso;
            q = encomenda[ide].produto[i].qtd;
            encomenda[ide].peso_t = encomenda[ide].peso_t - (p *q) ; 
            produto[idp].qtd = produto[idp].qtd + q;
            /* apaga produto da encomenda */
            strcpy(encomenda[ide].produto[i].descricao,"");
            encomenda[ide].produto[i].idp = -1;
            encomenda[ide].produto[i].peso = 0;
            encomenda[ide].produto[i].preco = 0;
            encomenda[ide].produto[i].qtd = 0;}

    }    
}

/*calcula o custo de uma encomenda, fazendo a multiplicacao do preco e a quantidade de cada produto mais a soma de todos os produtos ( p * q) existentes na encomenda*/
int C(){
    int ide, i;                 
    int soma = 0;
    scanf("%d", &ide);
    if(ide < e_size){
        for (i = 0; i <= p_size[ide]; i++){
            soma = soma + (encomenda[ide].produto[i].preco * encomenda[ide].produto[i].qtd);}
        printf("Custo da encomenda %d %d.\n", ide, soma);
                
    }else{
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);}
        
    return 0;
}

/* altera o preco de um produto no sistema */

void p(){
    int idp,i,j,preco;
    scanf("%d:%d", &idp, &preco);
    if(idp < p_size_out){
        for(i = 0; i < e_size; i++){
            for(j = 0; j < p_size[i]; j++){
                if(encomenda[i].produto[j].idp == idp){
                    encomenda[i].produto[j].preco = preco;
                    break;}
            }
        }
        produto[idp].preco = preco;
    }else{
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);}
}

/*lista a descri??o e a quantidade de um produto numa encomenda*/

int E(){
    int ide, idp,i;
    scanf("%d:%d", &ide, &idp);
    i = searchForProductInEcom(ide, idp); /*funcao auxiliar que faz a procura de um produto numa encomenda*/
    if(ide < e_size){
        if(idp < p_size_out){
            if (i != -1){
                printf("%s %d.\n", encomenda[ide].produto[i].descricao, encomenda[ide].produto[i].qtd);
            }else{
                printf("%s 0.\n", produto[idp].descricao);
            }
        }else{
            printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        }
    }else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    return 0;
}

/*lista o identificador da encomenda em que o produto dado ocorre mais vezes.*/

int m(){
    int idp, i, j, aux;
    int x = 0;
    
    scanf("%d", &idp);
    if (idp < p_size_out){
        for (i = 0; i < e_size; i++){
            for(j = 0; j < p_size[i]; j++){
                if (encomenda[i].produto[j].idp == idp){
                    if( x < encomenda[i].produto[j].qtd){
                        x = encomenda[i].produto[j].qtd;
                        aux = i;
                        break;}    
                }
            }            
        }if(x!=0){
            printf("Maximo produto %d %d %d.\n", idp, aux , x);
        }
        
    }else{
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);}
    return 0;

}



int main(){
    char comando;

    while((comando = getchar()) != 'x'){
        switch(comando){
            case 'a':
                    getchar();
                    adicionaProduto();
                    break;

            case 'q':
                    adicionaStock();
                    break;

            case 'N':
                    printf("Nova encomenda %d.\n", e_size);
                    e_size++;
                    break;

            case 'A':
                    getchar();
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
        }
    }
    return 0;
}
