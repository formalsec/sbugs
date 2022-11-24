#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao que procura o indice da hashtable onde se encontra uma equipa com o nome dado como argumento. Caso nao haja uma equipa na
hashtable com o nome dado, retorna NAO_ENCONTRA. */
int procura_indice_equipas(Equipa* Hashtable, char* nome, int tamanho_Hashtable){
    int indice;
    indice = hash(nome, tamanho_Hashtable);
    while (Hashtable[indice] != NULL){
        if (strcmp(Hashtable[indice] -> Nome, nome) == 0){
            return indice;
        }
        else{
            indice = (indice + 1) % tamanho_Hashtable;
        }
    }
    return NAO_ENCONTRA;
}

/* Funcao que verifica que a quipa e realmente nova na hashtable, e nesse caso retorna 0, ou caso contrario, retorna 1 */ 
int equipa_nova(char *nome, Equipa* Hashtable, int tamanho_Hashtable){
    int Indice = hash(nome, tamanho_Hashtable);
    while (Hashtable[Indice] != NULL){
        if (strcmp(Hashtable[Indice] -> Nome, nome) == 0){            
            return 1;
        }
        Indice = (Indice + 1) % tamanho_Hashtable;
    }
    return 0;
}

/* Funcao que cria uma equipa alocando memoria para uma equipa e alocando apenas a memoria necessaria a string que representa
o nome da equipa */
Equipa nova_equipa(char *nome){
    Equipa nova = (Equipa) can_fail_malloc(sizeof(struct equipa));
    nova -> Nome = can_fail_malloc(sizeof(char)*(strlen(nome) + 1));
    strcpy(nova -> Nome, nome);
    nova -> Vitorias = 0;
    return nova;
}

/* Funcao que procura uma equipa da hashtable e escreve o seu nome e numero de vitorias antecedido pelo NL. */
int procura_equipa(Equipa* Hashtable, int tamanho_Hashtable, int NL){
    int indice;
    char nome[MAXIMO_CARACTERES];
    scanf(" %[^\n]" , nome);
    indice = procura_indice_equipas(Hashtable, nome, tamanho_Hashtable);
    if (indice != NAO_ENCONTRA){
        printf("%d %s %d\n", NL, Hashtable[indice] -> Nome, Hashtable[indice] -> Vitorias);
        return 0;
        }
    else{
        printf("%d Equipa inexistente.\n", NL);
        return 0;
        }
}

/* Funcao que verifica a existencia de ambas as equipas dadas como argumentos na hashtable */
int verifica_equipas(char* equipa1, char *equipa2, Equipa* Hashtable, int tamanho_Hashtable){
    int Indice1 = procura_indice_equipas(Hashtable, equipa1, tamanho_Hashtable);
    int Indice2 = procura_indice_equipas(Hashtable, equipa2, tamanho_Hashtable);
    if (Indice1 != NAO_ENCONTRA && Indice2 != NAO_ENCONTRA){
        return 0;
    }
    return 1;
}

/* Funcao que adiciona uma equipa a lista de equipas alocando a memoria necessaria */
Lista_Equipas insere_lista_equipas(Lista_Equipas lista, Equipa equipa1){
    Lista_Equipas variavel = (Lista_Equipas) can_fail_malloc(sizeof(struct lista_equipas));
    variavel -> equipa = equipa1;
    variavel -> next = lista;
    return variavel;
}
/* Funcao que atraves do mergesort, ordena e escreve as equipas com mais vitorias por ordem lexicografica */
int print_lista_equipas(Lista_Equipas lista, int NL){
    int Max = 0, contador = 0, indice;
    Lista_Equipas variavel, melhores = NULL;
    char **arr;
    char **arr2;
    if (lista == NULL){
        return 0;
    }
    for (variavel = lista; variavel != NULL; variavel = variavel -> next){
        if (variavel -> equipa -> Vitorias > Max){
            Max = variavel -> equipa -> Vitorias;
        }
    }
    for (variavel = lista; variavel != NULL; variavel = variavel -> next){
        if (variavel -> equipa -> Vitorias == Max){
            melhores = insere_lista_equipas(melhores, variavel -> equipa);
            contador ++;
        }
    }
    arr = cria_array(melhores, contador);
    arr2 = cria_array(melhores, contador); /*criacao de dois arrays para usar no mergesort */
    mergesort(arr, 0, contador - 1, arr2);
    printf("%d Melhores %d\n", NL, Max);
    for (indice = 0; indice < contador; indice++){
        printf("%d * %s\n", NL, arr[indice]);
    }
    while(melhores){
        variavel = melhores;
        melhores = melhores -> next;
        free(variavel);
    }
    free(arr);
    free(arr2);

    
    return 0;
}
 /* Funcao que cria um array que contem as equipas com mais vitorias para ser posteriormente ordenado no mergesort */
char** cria_array(Lista_Equipas melhores, int contador){
    char **arr=can_fail_malloc(sizeof(char*)*contador);
    int indice;
    for (indice = 0; indice < contador; indice ++){
        arr[indice] = melhores -> equipa -> Nome;
        melhores = melhores -> next;
    }
    return arr;
}

void mergesort(char** arr, int l, int r, char **arr2){
    int meio = (r + l) / 2;
    if (r <= l){
        return;
    }
    mergesort(arr, l, meio, arr2);
    mergesort(arr, meio + 1, r, arr2);
    merge(arr, l, meio, r, arr2);
    }
    
void merge(char** arr, int l, int m, int r, char **arr2){
    int i, j, k;
for (i = m + 1; i > l; i--){
        arr2[i - 1] =arr[i - 1];
    }
    for (j = m; j < r; j++){
        arr2[r + m - j] = arr[j + 1];
    }
    for( k = l; k <= r; k++){
            if (strcmp(arr2[j] , arr2[i]) < 0){
                arr[k] = arr2[j--];
            }
            else{
                arr[k] = arr2[i++];
            }
        }
    }

/* Funcao que liberta todo a memoria alocado anteriormente referente a equipas */
int free_equipas(Lista_Equipas lista){
    Lista_Equipas variavel;
    if (lista == NULL){
        free(lista);
        return 0;
    }
    while ( lista){
        variavel = lista;
        lista = lista -> next;
        free(variavel -> equipa -> Nome);
        free(variavel -> equipa);
        free(variavel);
    }
    return 0;
}