#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaLigada.h"
#include "Jogos.h"

list *mk_list() /* Funcao que cria uma lista */
{
    list *l = can_fail_calloc(1, sizeof(list)); /* Aloca a memoria na lista a NULL */
    return l;                          /* retorna a lista inicializada */
}

void free_node(node *n) /* Funcao que da free ao node */
{
    free(n->jogo->nome); /* Free ao node para ajudar nas funcoes de remocao do node */
    free(n->jogo->equipa1);
    free(n->jogo->equipa2);
    free(n->jogo);
    free(n);
}

void free_list(list *l) /* Funcao que da free ha lista e ao node */
{
    while (l->head != NULL) /* Free a lista para ajudar na funcao_x para dar free a tudo o que esta na lista */
    {
        node *tmp = l->head->next;
        free_node(l->head);
        l->head = tmp;
    }
    free(l);
}

void rm_node(list *l, node *n) /* Funcao que remove o node da lista */
{
    if (n->previous == NULL) /* Se o node for a head entao o a head passa a ser o proximo node */
    {
        l->head = n->next;
    }
    else /* Se o node nao for a head entao o proximo do node atual vai ser o proximo do anterior */
    {
        n->previous->next = n->next;
    }
    if (n->next == NULL) /* Se o node for o ultimo elemento da lista entao o last passa a ser o node anterior */
    {
        l->last = n->previous;
    }
    else /* Se o node nao for o ultimo elemento da lista entao o anterior node do node atual vai ser o anterior do proximo node */
    {
        n->next->previous = n->previous;
    }
    free_node(n); /* E no fim da free a esse node para eleminar da memoria */
}

node *add_last(list *l, char *n, char *equipa1, char *equipa2, int score1, int score2) /* Funcao que adiciona um node ha lista */
{
    node *nn = can_fail_malloc(sizeof(node)); /* Aloca a memoria para o node, e para os seus ponteiros */
    nn->previous = l->last;
    nn->jogo = can_fail_malloc(sizeof(struct Jogo));
    nn->jogo->nome = can_fail_malloc(sizeof(char) * (strlen(n) + 1));
    nn->jogo->equipa1 = can_fail_malloc(sizeof(char) * (strlen(equipa1) + 1));
    nn->jogo->equipa2 = can_fail_malloc(sizeof(char) * (strlen(equipa2) + 1));
    strcpy(nn->jogo->nome, n); /* E coloca a o nome dado, as equipas e os scores na memorias */
    strcpy(nn->jogo->equipa1, equipa1);
    strcpy(nn->jogo->equipa2, equipa2);
    nn->jogo->score1 = score1;
    nn->jogo->score2 = score2;
    nn->next = NULL; /* Coloca o node criado dentro da lista sempre ordenado por colocacao */
    if (l->last != NULL)
    {
        l->last->next = nn;
    }
    else
    {
        l->head = nn;
    };
    l->last = nn;
    return nn;
}

void printList(node *head, int nl) /* Funcao que da print a todos os jogos que estao na lista */
{
    node *temporario = head;
    while (temporario != NULL) /* Enquanto o node nao for null , vai printar todos os nodes(jogos) dentro dessa lista*/
    {
        printf("%d %s %s %s %d %d\n", nl, temporario->jogo->nome, temporario->jogo->equipa1,
               temporario->jogo->equipa2, temporario->jogo->score1,
               temporario->jogo->score2);

        temporario = temporario->next;
    }
}