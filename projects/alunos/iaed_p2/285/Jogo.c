#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Jogo.h"

/* Implementacao das funcoes referentes aos Jogos */

/* Funcao que cria um jogo alocando memoria para um jogo e alocando apenas a memoria necessaria para cada string
(nome do jogo, nome da equipa1 e nome da equipa2) */
Jogo novo_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2){
    Jogo novo = (Jogo) can_fail_malloc(sizeof(struct jogo));
    novo -> Nome = can_fail_malloc(sizeof(char)*(strlen(nome) + 1));
    strcpy(novo -> Nome, nome);
    novo -> Equipa_Casa = can_fail_malloc(sizeof(char)*(strlen(equipa1) + 1));
    strcpy(novo -> Equipa_Casa, equipa1);
    novo -> Equipa_Fora = can_fail_malloc(sizeof(char)*(strlen(equipa2) + 1));
    strcpy(novo -> Equipa_Fora, equipa2);
    novo -> Score_Equipa_Casa = score1;
    novo -> Score_Equipa_Fora = score2;
    return novo;     
}

/* Funcao que procura e retorna um jogo da hashtable atraves de um nome dado. Caso nao exista
nenhum jogo na hashtable com esse nome, retorna NULL */
Jogo procura(char *nome, Jogo* Hashtable, int tamanho_Hashtable){
    int indice = procura_indice(Hashtable, nome, tamanho_Hashtable);
    if (indice != NAO_ENCONTRA){
        return Hashtable[indice];
    }
    return NULL;
}

/* Funcao que adiciona um jogo a lista de jogos */
Lista insere_lista(Lista lista, Jogo jogo1){
    Lista variavel = (Lista) can_fail_malloc(sizeof(struct lista));
    variavel -> jogo = jogo1;
    variavel -> next = lista;
    return variavel;
}

/* Funcao que apaga o jogo com o nome dado da lista de jogos */
Lista apaga_na_lista(Lista lista, char *nome){
    Lista variavel, variavel2;
    for (variavel = lista, variavel2 = NULL; variavel != NULL; variavel2 = variavel, variavel = variavel -> next){
        if (strcmp(variavel -> jogo -> Nome , nome) == 0){
            if (variavel == lista){
                lista = variavel -> next;
            }
            else{
                variavel2 -> next = variavel -> next;
            }
            free(variavel);
            break;
        }
    }
    return lista;
}

/* Funcao que escreve cada jogo da lista de jogos antecedida por NL */
int print_lista(Lista lista, int NL){
    if (lista == NULL){
        return 0;
    }
    print_lista(lista -> next, NL);
    printf("%d %s %s %s %d %d\n", NL, lista -> jogo -> Nome, lista -> jogo -> Equipa_Casa,
         lista -> jogo -> Equipa_Fora, lista -> jogo -> Score_Equipa_Casa, lista -> jogo -> Score_Equipa_Fora);
    return 0;
}

/* Funcao que liberta todo a memoria alocado anteriormente referente a jogos */
int free_jogos(Lista lista){
    Lista variavel;
    if (lista == NULL){
        free(lista);
        return 0;
    }
    while ( lista){
        variavel = lista;
        lista = lista -> next;
        free(variavel -> jogo -> Nome);
        free(variavel -> jogo -> Equipa_Casa);
        free(variavel -> jogo -> Equipa_Fora);
        free(variavel -> jogo);
        free(variavel);
    }
    return 0;
}
