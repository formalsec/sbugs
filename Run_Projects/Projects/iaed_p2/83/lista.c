#include <stdio.h>
#include <stdlib.h>
#include "JogoEquipa.h"
#include "lista.h"


/* Funcao auxiliar que cria um novo No */
link NewNode(Jogo Jogo)
{
    link x = (link)malloc(sizeof(struct node));

    x -> Jogo = Jogo;
    x -> next = NULL;

    return x;
}


/* Funcao auxiliar que insere um novo no no fim da lista */
void insertEnd(link* head, link* tail, Jogo Jogo)
{
    link x = NewNode(Jogo);

    if (*head == NULL)
    {
        *head = x;
        *tail = *head;
    }

    else
    {
        ((*tail) -> next) = x;
        *tail = x;
    }
}


/* Funcao auxiliar que remove um dado no da lista */
void delete(link* head, link* tail, Jogo Jogo)
{
    link t, prev;

    t = *head;
    prev = NULL;

    while (t != NULL) 
    {
        if (Jogo == (t -> Jogo))
        {
            if(t == *head)
            {
                *head = t->next;
                free(t);
                return;
                
            }

            else if (t == *tail)
            {
                prev->next = t->next;
                free(t);
                *tail = prev;
                return;
            }

            else
            {
                prev->next = t->next;
                free(t);
                return;
            }
        }
    
        prev = t;
        t = t->next;
    }
}


/* Funcao auxiliar que imprime o conteudo da lista */
void printLista(link head, int* N_linhas)
{
    link t;

    for (t = head; t != NULL ; t = (t -> next))
    {
        printf("%d ", *N_linhas);
        printJogo((t -> Jogo));
    } 
}


/* Funcao auxiliar que dar free aos nos da lista */
void freeLista(link head)
{
    link t = head;
    link next;
    
    while (t != NULL)
    {
        next = t -> next;
        free(t);
        t = next;
    }
}