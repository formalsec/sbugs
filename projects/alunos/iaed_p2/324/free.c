#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"


void free_node_jg(jg_node * n)
{
    /*Liberta a memoria das strings do jg_node*/
    free(n->value);
    free(n->equipa1);
    free(n->equipa2);
}

/**************************************************************************************************/

void free_list_jg(jogos *l)
{
    /*Ciclo que vai a tds os elementos da lista, nao NULL*/
    while(l->head){
        /*Liberta a memoria de cada no, e refaz a coneccao dos restantes nos*/
        jg_node *tmp =l->head->next;
        free_node_jg(l->head);
        l->head = tmp;
    }
    /*Apos libertada a memoria de cada no, liberta a memoria alocada para a estrutura da lista*/
    free(l);
}

/**************************************************************************************************/

void free_equipas(e_node ** equipas)
{
    e_node *aux;
    int i;
    /*Ciclo que vai a todos os indices da hash*/
    for(i=0;i<HASHTABLE_SIZE;i++)
    {
        /*Enquanto esse indice nao estiver vazio*/
        while(equipas[i] != NULL)
        {
            /*Liberta a memoria de cada no, bem como os seus argumentos, e refaz a coneccao dos restantes nos*/
            aux = equipas[i]->next;
            free(equipas[i]->nome);
            free(equipas[i]);
            equipas[i] = aux;            
        }
    }
    /*Apos cada indice estar vazio de nos, liberta a memoria alocada para criar cada indice*/
    for(i=0;i<HASHTABLE_SIZE;i++)
    {
        free(equipas[i]);
    }
    /*Liberta a memoria alocada para criar a hash das equipas*/
    free(equipas);
}

/**************************************************************************************************/

void free_table(node ** table, jogos *lista_jogos)
{
    node *aux_2;
    int i;
    /*Ciclo que vai a todos os indices da hash*/
    for(i=0;i<HASHTABLE_SIZE;i++)
    {   
        /*Enquanto esse indice nao estiver vazio*/
        while(table[i] != NULL)
        {   
            /*guarda o elemento seguinte*/
            aux_2 = table[i]->next;
            /*Caso o no de um jogo eliminado anteriormente*/
            if(strcmp(table[i]->nome_jogo, "") == 0)
            {
                /*Liberta a memoria alocada para criar a string*/
                free(table[i]->nome_jogo);
                /*Liberta a memoria alocada para criar cada argumento do no da lista de jogos*/
                free_node_jg(table[i]->jogo);
                /*Liberta a memoria alocada para criar o ponteiro que liga ao no da lista de jogos*/
                free(table[i]->jogo);
                /*Liberta a memoria alocada para criar o no da hash*/
                free(table[i]);
                /*Reconecta a hash aos restantes elementos*/
                table[i] = aux_2;
            }
            /*Caso seja um no de um jogo existente*/
            else
            {
                free(table[i]->nome_jogo);
                /*Liberta as coneccoes do no da lista de jogos e reconecta os restantes nos*/
                if(table[i]->jogo->previous == NULL) lista_jogos->head = table[i]->jogo->next;
                else table[i]->jogo->previous->next = table[i]->jogo->next;
                if(table[i]->jogo->next == NULL) lista_jogos->last = table[i]->jogo->previous;
                else table[i]->jogo->next->previous = table[i]->jogo->previous;

                free_node_jg(table[i]->jogo);
                free(table[i]->jogo);
                free(table[i]);
                table[i] = aux_2;
            }
        }
    }
    /*Apos cada indice estar vazio de nos, liberta a memoria alocada para criar cada indice*/
    for(i=0;i<HASHTABLE_SIZE;i++)
    {
        free(table[i]);
    }
    /*Liberta a memoria alocada para criar a hash dos jogos*/
    free(table);
}

/**************************************************************************************************/

void free_all(jogos *lista_jogos, node ** table, e_node ** equipas)
{
    /*Liberta a memoria alocada para criar a hash das quipas e para mexer nela*/
    free_equipas(equipas);
    /*Liberta a memoria alocada para criar a hash dos jogos e para mexer nela*/
    free_table(table, lista_jogos);
    /*Liberta a memoria alocada para criar a lista ligada de jogos e de mexer nela*/
    free_list_jg(lista_jogos);
}
/**************************************************************************************************/