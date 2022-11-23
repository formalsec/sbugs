#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash_defines.h"
#include "jogos_linked.h"
#include "jogos_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Funcao que inicializa uma lista_de_jogos.*/
JOGO_LIST * cria_lista_jogos()
{
/*aloca memoria do tipo JOGO_LIST*/
    JOGO_LIST * lista_de_jogos = can_fail_malloc(sizeof(JOGO_LIST));
    lista_de_jogos -> head = NULL;
    lista_de_jogos -> last = NULL;
    return lista_de_jogos;
}

/*Funcao que cria um novo_jogo dado o nome do jogo e das equipas e o score que 
    cada uma das equipas obteve nesse jogo adicionando-o a lista_de_jogos.*/
JOGO * cria_jogo(JOGO_LIST * lista_de_jogos, char * nome, 
                    char * equipa1, char * equipa2, int score1, int score2)
{
    JOGO * novo_jogo = can_fail_malloc(sizeof(JOGO));
    int len_nome = strlen(nome), len_equipa1 = strlen(equipa1), len_equipa2 = strlen(equipa2);

/*aloca memoria do tipo char necessaria para guardar a string referente ao seu nome*/
    novo_jogo -> nome = can_fail_malloc(sizeof(char)*(len_nome + 1));
    strcpy(novo_jogo -> nome, nome);

/*aloca memoria do tipo char necessaria para guardar a string referente a equipa1*/
    novo_jogo -> equipa1 = can_fail_malloc(sizeof(char)*(len_equipa1 + 1));
    strcpy(novo_jogo -> equipa1, equipa1);
    
/*aloca memoria do tipo char necessaria para guardar a string referente a equipa2*/
    novo_jogo -> equipa2 = can_fail_malloc(sizeof(char)*(len_equipa2 + 1));
    strcpy(novo_jogo -> equipa2, equipa2);

    novo_jogo -> score1 = score1;
    novo_jogo -> score2 = score2;

/*novo_jogo e adicionado no fim da lista_de_jogos*/
    novo_jogo -> prev = lista_de_jogos -> last;
    novo_jogo -> next = NULL;

    if (lista_de_jogos -> last == NULL) lista_de_jogos -> head = novo_jogo;
    else lista_de_jogos -> last -> next = novo_jogo;

    lista_de_jogos -> last = novo_jogo;

    return novo_jogo;
}

/*Funcao que remove um jogo de uma lista_de_jogos.*/
void remove_jogo_linked(JOGO_LIST * lista_de_jogos, JOGO * jogo)
{
    if (jogo -> prev == NULL)
    {
/*caso o jogo a remover e a cabeca da lista_de_jogos*/
        lista_de_jogos -> head = jogo -> next;
    } else {
        jogo -> prev -> next = jogo -> next;
    }
    if (jogo -> next == NULL)
    {
/*caso o jogo a remover e o ultimo no da lista_de_jogos*/
        lista_de_jogos -> last = jogo -> prev;
    } else {
        jogo -> next -> prev = jogo -> prev;
    }
    destroy_jogo(jogo);
}

/*Funcao que liberta memoria alocada para um jogo.*/
void destroy_jogo(JOGO * jogo)
{
    free(jogo -> nome);
    free(jogo -> equipa1);
    free(jogo -> equipa2);
    free(jogo);
}

/*Funcao que liberta a memoria alocada por uma lista_de_jogos 
    e dos jogos existentes na mesma.*/
void destroy_jogos_linked(JOGO_LIST * lista_de_jogos)
{
    while(lista_de_jogos -> head != NULL) 
    {
/*tmp representa o segundo jogo existente na lista ligada de jogos atual*/
        JOGO * tmp = lista_de_jogos -> head -> next;
        destroy_jogo(lista_de_jogos -> head);
        lista_de_jogos -> head = tmp;
    }
    free(lista_de_jogos);
}
