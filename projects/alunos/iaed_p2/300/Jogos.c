#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Jogos.h"
#include "ListaLigada.h"

int hashJ(char *nome, int m) /* Funcao que identifica em que index da hastable e que o jogo esta */
{
    int h, a = 31415, b = 27183;
    for (h = 0; strcmp(nome, "\0") != 0; nome++, a = a * b % (m - 1))
        h = (a * h + *nome) % m;
    return h;
}

node *insertBeginListJ(node *head, node *node_jogo) /* Funcao auxiliar de STinsertJ*/
{
    node *x = can_fail_malloc(sizeof(node)); /* Aloca a memoria necessaria para os nodes dos jogos e cria o jogo*/
    x->previous = NULL;
    x->jogo = node_jogo->jogo;
    x->next = head;
    return x;
}

node *removeJogoListJ(node *head, char *nome) /* Funcao auxiliar de STdeleteJ */
{
    node *t, *prev, *temp;
    for (t = head, prev = NULL; t != NULL;) /* Percorre a "gaveta" da hastable que o jogo esta e quando encontra o jogo remove*/
    {
        if (strcmp(t->jogo->nome, nome) == 0)
        {
            if (t == head)
                head = t->next;
            else
                prev->next = t->next;
            free(t);
            break;
        }
        temp = t->next;
        prev = t;
        t = temp;
    }
    return head;
}

node *searchListJ(node *head, char *nome) /* Funcao auxiliar de STsearchJ */
{
    node *t;
    for (t = head; t != NULL;) /* Percorre a "gaveta" da hastable que o jogo esta e quando encontra o jogo retorna-o*/
    {
        if (strcmp(t->jogo->nome, nome) == 0)
        {
            return t;
        }
        t = t->next;
    }
    return NULL;
}

node **STinitJ(int m) /* Funcao que inicializa a hashtable dos jogos*/
{
    node **heads;
    heads = can_fail_calloc(m, sizeof(node *)); /* Aloca a memoria necessaria*/
    return heads;
}

void STinsertJ(node **heads, node *node_jogo, int m) /* Funcao que insere um node ao inicio da lista de um determinado index da hashtable*/
{
    int i = hashJ(node_jogo->jogo->nome, m); /*Encontra o index da hashtable onde se destina esse node e insere-o */
    heads[i] = insertBeginListJ(heads[i], node_jogo);
}

void STdeleteJ(node **heads, char *nome, int m) /* Funcao que remove um node duma lista de um determinado index da hashtable */
{
    int i = hashJ(nome, m); /*Encontra o index da hashtable onde se encontra esse node e remove-o */
    heads[i] = removeJogoListJ(heads[i], nome);
}

node *STsearchJ(node **heads, char *nome, int m) /* Funcao que procura se um node faz parte da hashtable */
{
    int i = hashJ(nome, m); /*Encontra o index da hashtable onde se encontra essa equipa e retorna-o */
    return searchListJ(heads[i], nome);
}

void printJogo(node *a, int nl) /* Funcao que da print ao nome do jogo, das equipas e do seu resultado */
{
    printf("%d %s %s %s %d %d\n", nl, a->jogo->nome, a->jogo->equipa1, a->jogo->equipa2, a->jogo->score1, a->jogo->score2);
}
