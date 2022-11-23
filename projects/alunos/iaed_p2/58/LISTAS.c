#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LISTAS.h"
#include "HASHTABLES.h"

/*-----------------------------------------------------------------------*/
/* novo_jogo_lista(pJogo jogo): esta funcao recebe um ponteiro para o    */
/*    nome de um jogo para guardar num no e devolve este novo no para    */
/*    inserir na lista de jogos.                                         */
/*-----------------------------------------------------------------------*/
link_jogo novo_jogo_lista(pJogo jogo) {
    link_jogo x = (link_jogo) can_fail_malloc(sizeof(struct no_jogo));
    x->jogo = jogo;
    x->next = NULL;
    return x;
}

/*------------------------------------------------------------------------*/
/* insere_jogo_lista(link_jogo head, pJogo jogo): esta funcao recebe o    */
/*    ponteiro para a cabeca de uma lista de ponteiros para nomes de      */ 
/*    jogos e o ponteiro para o nome de um jogo, e insere o no com o      */
/*    ponteiro do jogo na lista de jogos e devolve a cabeca da lista.     */
/*------------------------------------------------------------------------*/
link_jogo insere_jogo_lista(link_jogo head, pJogo jogo) {
    link_jogo x = head;
    head = novo_jogo_lista(jogo);
    head->next = x;
    return head;
}

/*------------------------------------------------------------------------*/
/* apaga_jogo_lista(link_jogo head, char* nome): esta funcao recebe o     */
/*    ponteiro para a cabeca de uma lista de ponteiros para nomes de      */ 
/*    jogos e o nome de um jogo, e apaga da lista o no desse jogo.        */
/*------------------------------------------------------------------------*/
link_jogo apaga_jogo_lista(link_jogo head, char* nome) {
    link_jogo x = NULL, prev = NULL;

    for(x = head; x != NULL; prev = x, x = x->next) {
        /* varios ifs de modo a acelerar a procura do jogo na lista */
        if(x->jogo->nome[0] == nome[0]) {
           if(x->jogo->nome[1] == nome[1]) {
                if(!strcmp(x->jogo->nome, nome)) {
                    if (x == head)
                        head = x->next;
                    else
                        prev->next = x->next;
                    free(x);
                    return head;
                }
            }
        }
    }
    return head;
}

/*------------------------------------------------------------------------*/
/* free_jogos_lista(link_jogo head): esta funcao recebe o ponteiro para a */
/*    cabeca de uma lista de ponteiros para nomes de jogos e faz a        */ 
/*    libertacao da memoria reservada para essa lista.                    */
/*------------------------------------------------------------------------*/
void free_jogos_lista(link_jogo head) {  
    link_jogo x = NULL, x_next = NULL;
    
    for(x = head; x != NULL; x = x_next) {
        x_next = x->next;
        free(x);
    }
    return;
}

/*------------------------------------------------------------------------*/
/* nova_equipa_lista(char* equipa): esta funcao recebe o nome de uma      */
/*    equipa para guardar num no e devolve este novo no para inserir na   */
/*    lista de equipas pertencente a tabela de equipas.                   */
/*------------------------------------------------------------------------*/
link_equipa nova_equipa_lista(char* equipa) {
    link_equipa x = NULL;

    x = (link_equipa) can_fail_malloc(sizeof(struct no_equipa));
    x->equipa = (char*) can_fail_malloc(sizeof(char)*(strlen(equipa)+1));
    
    strcpy(x->equipa, equipa);
    x->vitorias = 0;
    x->size_e = strlen(equipa);
    x->next = NULL;
    
    return x;
}

/*------------------------------------------------------------------------*/
/* insere_equipa_lista(link_equipa *tab_equipas, char* equipa): esta      */
/*    funcao recebe o ponteiro para a tabela com listas de equipas e o    */           
/*    nome de uma equipa, e insere o novo no na lista correspondente.     */
/*------------------------------------------------------------------------*/
void insere_equipa_lista(link_equipa *tab_equipas, char* equipa) {
    link_equipa x = NULL, n = NULL;
    unsigned int h;

    h = funcao_tab_equipas(equipa);
    n = nova_equipa_lista(equipa);

    if (tab_equipas[h] == NULL){
        tab_equipas[h] = n;
    }
    else {
        for (x = tab_equipas[h]; x->next != NULL; x = x->next);
        x->next = n;
    }
    return;
}

/*----------------------------------------------------------------------*/
/* procura_equipa_lista(link_equipa *tab_equipas, char* equipa): esta   */
/*    funcao recebe o ponteiro para a tabela com listas de equipas e o  */        
/*    nome de uma equipa, e procura na tabela de equipas no indice onde */
/*    a equipa estaria. Se a encontrar na lista devolve o ponteiro para */
/*    o no da lista onde esta a equipa. Caso contrario, devolve NULL.   */
/*----------------------------------------------------------------------*/
link_equipa procura_equipa_lista(link_equipa *tab_equipas, char* equipa) {
    link_equipa x = NULL;
    unsigned int h;
    int comp;
    
    h = funcao_tab_equipas(equipa);
    comp = strlen(equipa);

    for (x = tab_equipas[h]; x != NULL; x = x->next) {
        if(x->size_e == comp) {
            if(!strcmp(x->equipa, equipa)) {
                return x;
            }
        }  
    }
    return NULL;
}