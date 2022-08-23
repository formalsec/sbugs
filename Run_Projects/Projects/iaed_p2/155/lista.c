#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "hash_table_jogo.h"

/*Lista para guardar ordem dos jogos introduzidos */
node * lista_insert(jogo *j, node *head)
{
    node *novo, *aux;
    novo = (node*) malloc(sizeof(node)); /*cria espaco para o novo node*/
    novo->jogo = j;
    novo->next = NULL;
    if (head == NULL)
    {
        head = novo;
        return head;
    }
    else
    {
        aux = head;
        while (aux->next != NULL) /*percorre a lista toda */
        {
            aux = aux->next;
        }
        aux->next = novo; /* insere o node no fim */
        return head;
    }
}

/* Funcao para procurar um jogo pelo nome na lista */
node * lista_lookup(char *nome, node *head)
{
    node *aux;
    jogo *jogo_aux;
    for (aux = head; aux != NULL; aux = aux->next) /*percorre a lista*/
    {
        jogo_aux = aux->jogo;
        if (strcmp(jogo_aux->nome_jogo, nome) == 0) /*compara os nomes*/
        {
            return aux;
        }
    }
    return NULL; /*se o jogo nao estiver na lista retorna-se NULL*/
}

/* Funcao que apaga um jogo e que faz os frees necessarios*/
node * lista_delete(char *nome, node *head)
{
    if (head == NULL)
    {
        return NULL; /*nada e feito se a cabeca for NULL*/
    }
    else
    {
        node *aux, *aux_ant;
        if (lista_lookup(nome, head) == NULL)
        {
            return head; /*se o jogo nao estiver na lista nada e alterado*/
        }
        else if (head->next == NULL && strcmp(head->jogo->nome_jogo, nome) == 0)
        {
            free(head->jogo->equipa_1);
            free(head->jogo->equipa_2);
            free(head->jogo->nome_jogo);
            free(head->jogo);
            free(head);
            return NULL;
        }
        else if (strcmp(head->jogo->nome_jogo, nome) == 0)
        {
            aux = head->next;
            free(head->jogo->equipa_1);
            free(head->jogo->equipa_2);
            free(head->jogo->nome_jogo);
            free(head->jogo);
            free(head);
            return aux;
        }
        else
        {
            aux = head;
            aux_ant = NULL;
            while (strcmp(aux->jogo->nome_jogo, nome) != 0)/*percorre a lista*/
            {
                aux_ant = aux;
                aux = aux->next;
            }
            aux_ant->next = aux->next;/*salta o node com o jogo*/
            free(aux->jogo->equipa_1);
            free(aux->jogo->equipa_2);
            free(aux->jogo->nome_jogo);
            free(aux->jogo);
            free(aux);
            return head;
        }
    }
}
