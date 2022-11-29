#include "estruturas.h"
#include <stdio.h>
#include <strings.h>

/*VARIAVEIS GLOBAIS*/

/*Vetor auxiliar usada pelaa funcao merge*/
int aux[MAX_PROD];

/*DECLARACAO DE FUNCOES*/

int get_string(char*);
int ret_preco(int, Produto*);
int cmp_str(int, int, Produto*);
void ordena_counting(Produto*, int, int*, int (*)(int, Produto*));
void merge(int*, int, int, int, Produto*, int (*)(int, int, Produto*));
void ordena_merge(int*, int, int, Produto*, int (*)(int, int, Produto*));
void imprime_ordenado(int*, int, Produto*, int*);

/*DEFENICAO DE FUNCOES*/

/*
  get_string: (char*) -> (int)
  Le uma string da stdin ate encontrar o carater ':' ou exceder o 
  limite de carateres lidos STR_MAX; Retorna o numero de carateres lidos 
*/
int get_string(char* arg){
    char c;
    int i = 0;
  
    c = getchar();
    while(c != ':' && i < STR_MAX - 1){
        arg[i] = c;
        i++;
        c = getchar();
    }

    /*Limpa a stdin ate encontrar ':'*/
    while(c != ':')
        c = getchar();

    /*Termina a string com null byte*/
    arg[i] = '\0';

    return i;
}

/*
  ret_preco: (int, Produto*) -> (int)
  Retorna o preco do produto com id correspondente a id. 
*/
int ret_preco(int id, Produto* p){
    return p[id].preco;
}

/*
  cmp_str: (int, int, Produto*) -> (int)
  Retorna um inteiro > 0 se a descricao do produto com id j e maior que a descricao
  do produto i, inteiro < 0 caso contrario ou 0 se forem iguais.
*/
int cmp_str(int i, int j, Produto* p){
    return strcasecmp(p[j].desc, p[i].desc);
}

/*
  ordena_counting: (Produto*, int, int*, Funcao*) -> ()
  Retorna um vetor output contendo os ids dos produtos ordenados tendo em conta o valor
  retornado pela funcao auxiliar ret_aux. Ordena o vetor segundo o algoritmo counting.
  Nao modifica destrutivamente o vetor de produtos p.
*/
void ordena_counting(Produto* p, int size, int* output, int (*ret_aux)(int id, Produto* p)){
    /*O numero maximo de preco e o maior inteiro possivel logo o range para o vetor conta
      e o maior inteiro possivel*/
    int conta[MAX_INT] = {0}, i;
    
    /*Constroi o vetor que guarda o numero de vezes que cada valor 
      retornado por ret_aux e repetido no produto*/
    for(i=0; i<size; i++)
        ++conta[ret_aux(i, p)];

    /*Transforma o numero de repeticoes em indices de ordenacao*/
    for(i=1; i < MAX_INT; i++)
        conta[i] += conta[i-1];

    /*Atribui cada id ao output tendo em conta os valores de conta*/
    for (i = size-1; i>=0; --i) { 
        output[conta[ret_aux(i, p)]-1] = p[i].id; 
        --conta[ret_aux(i, p)]; 
    }
}

/*
  merge: (int*, int, int, int, Produto*, Funcao*) -> ()
  Funcao auxiliar do algoritmo merge sort. Ordena o subvetor id[baixo:cima] segundo o comparador cmp.
*/
void merge(int* id, int baixo, int m, int cima, Produto* p, int (*cmp)(int i, int j, Produto* p)){
    int i,j,k;

    /*Constroi o vetor auxiliar*/
    for(i=m+1; i>baixo; i--)
        aux[i-1] = id[i-1];

    for(j=m; j<cima; j++)
        aux[cima+m-j] = id[j+1];

    /*Escolhe os elemntos das pontas para ordenar o vetor copia*/
    for(k=baixo; k<=cima; k++){
        if(cmp(aux[i], aux[j], p) < 0)
            id[k] = aux[j--];

        else
            id[k] = aux[i++];
    }
}

/*
  ordena_merge: (int*, int, int, Produto*, Funcao*) -> ()
  Ordena o subvertor de id's id[baixo:cima] segundo o criterio do comparador cmp segundo 
  o algoritmo merge.
*/
void ordena_merge(int* id, int baixo, int cima, Produto*p, int (*cmp)(int i, int j, Produto* p)){
    int m = (baixo+cima) / 2;

    if(cima <= baixo)
        return;

    /*Parte o vetor id a meio recursivamente*/
    ordena_merge(id, baixo, m, p, cmp);
    ordena_merge(id, m+1, cima, p, cmp);

    /*Ordena o subvetor id[baixo:cima]*/
    merge(id, baixo, m, cima, p, cmp);
}

/*
  imprime_vetor: (int*, int, Produto*, int*) -> ()
  Imprime a descricao, o preco e a quantidade de produtos referenciados por um vetor de id's, em
  que a quantidade de cada produto esta guardada no vetor stock.
*/
void imprime_ordenado(int* id, int size, Produto* produto, int* stock){
    int i;

    for(i=0; i<size; i++){
        printf("* %s %d %d\n",produto[id[i]].desc,produto[id[i]].preco,stock[id[i]]);
    }
}
