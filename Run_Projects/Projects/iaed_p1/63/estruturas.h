#include <stdio.h>
#include <string.h>
#define STRSIZE 63 /*tamanho usado em todas strings do programa*/
#define MAX_PROD 10000 /*maximo de produtos que podem existir no sistema*/
#define MAX_ENCO 500 /* maximo de encomendas que podem existir no sistema*/
#define ENCO_MAX_PROD 200 /*maximo de produtos que podem existir numa encomenda*/
char input[STRSIZE];  /*string usada como input*/
int cont_enco=0;  /*contador das encomendas*/
int cont_prod=0;  /*contador dos produtos*/
int first=0,second=0,third=0;  /*explicacao na funcao auxStr()*/

typedef struct produto
{
    int idp;
    int peso;
    int preco;
    int qtd;
    char nome[STRSIZE];
}produto;

typedef struct encomenda{
    int ide;
    int index_prod; /*variavel usada para controlar o numero de produtos na encomenda*/
    produto vetProd[ENCO_MAX_PROD];
}encomenda;

encomenda encomendas[MAX_ENCO];/* vetor de encomendas*/
produto produtos[MAX_PROD]; /* vetor de produtos*/


int put_n(char c){/*funcao que converte um numero de char para int*/
    char vet[]={'0','1','2','3','4','5','6','7','8','9'};
    int i=0;
    for(i=0;i<10;i++){
        if(c==vet[i]){
            return i;
        }
    }
    return -1;
}


void auxStr(){
    /*
    esta funcao ajuda no tratamento do input que contem no maximo 3 elementos(exclusivo a inteiros)
    separando-os nas variaveis globais first,second e third.
    */
    int i,estado=0;
    int size_input;
    first=0;
    second=0;
    third=0; 
    size_input=strlen(input);
    

        
         for( i=0;i<size_input;i++){
               if(i>1 && (input[i]>='0' && input[i]<='9') && estado==0)
                    first=first*10+put_n(input[i]);
                else if(estado==1 &&(input[i]>='0' && input[i]<='9'))
                        second=second*10+put_n(input[i]);
                else if(estado==2 &&(input[i]>='0' && input[i]<='9'))
                        third=third*10+put_n(input[i]);
                
                if(input[i]==':')
                 estado++;

            }
    
}



int pesoEnco(int ide){/*funcao que calcula o peso de uma encomenda*/
    encomenda enco=encomendas[ide];
    int i=0,soma=0;
    for( i=0;i<enco.index_prod;i++)
       soma+= (enco.vetProd[i].peso)*(enco.vetProd[i].qtd);
    
    return soma;
}


