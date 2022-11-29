#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operationsovertable.h"

char *strdup(const char *src) 
{
    /* Funcao utilizada para alocar memoria para uma string */
    char *dst = can_fail_malloc(strlen (src) + 1);  
    if (dst == NULL) return NULL;          
    strcpy(dst, src);                      
    return dst;                            
}

campeonato *init_array(campeonato *heads, int M)
{
    /* Inicializa a tabela a NULL */
    int i;
    heads = (campeonato*)can_fail_malloc(M*sizeof(struct item));
    for(i = 0; i < M; i++)
    {
        heads[i] = NULL;
    }
    return heads;
}

int hash(char *v, int M) 
{
    /* Gera um indice para a hashtable */
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a*h + *v) % M;
    return h;
}

campeonato *insert_hash(campeonato *heads, game j, int M)
{
    /* Insere um novo elemento na hash */
    int i = hash(j ->nome, M);
    heads[i] = insertBeginList(heads[i], j);
    return heads;
}

campeonato *removeEl(campeonato *heads, char *text, int M)
{
    /* Remove um determinado elemento na hash */
    int i = hash(text, M);
    heads[i] = removeHashEl(heads[i], text);
    return heads;
}

campeonato removeHashEl(campeonato head, char *text)
{
    campeonato t, prev;
    for (t = head, prev = NULL; t!= NULL; prev = t, t = t->next)
    {
        if (strcmp(t->j->nome, text) == 0)
        {
            if (t == head)
            {
                head = t->next;
            }
            else
                prev ->next = t->next;
            free(t->j->equipa1);
            free(t->j->equipa2);
            free(t->j->nome);
            free(t->j);
            free(t);
            return head;
        }
    }
    return head;
}

campeonato insertBeginList(campeonato head, game jogo)
{
    if (head != NULL)
    {
        campeonato new = (campeonato)can_fail_malloc(sizeof(struct item));
        /* new = NULL; */
        new ->j = (game)can_fail_malloc(sizeof(struct jogo));
        new ->j ->nome = (char*)can_fail_malloc(sizeof(char) * (strlen(jogo->nome) + 1));
        strcpy(new -> j ->nome, jogo->nome);
        new ->j->nome = strdup(jogo ->nome);
        new ->j->equipa1 = strdup(jogo->equipa1);
        new ->j->equipa2 = strdup(jogo->equipa2);
        new ->j->score1 = jogo ->score1;
        new ->j->score2 = jogo ->score2;
        new ->next = head;
        return new;
    }
    else
    {
        campeonato new = NEW_NODE(jogo);
        new ->next = head;
        return new;   
    }
}

campeonato NEW_NODE(game jogo)
{
    campeonato x = (campeonato)can_fail_malloc(sizeof(struct item));
    x ->j = (game)can_fail_malloc(sizeof(struct jogo));
    x ->j ->nome = (char*)can_fail_malloc(sizeof(char) * (strlen(jogo->nome) + 1));
    strcpy(x -> j ->nome, jogo->nome);
    x ->j ->equipa1 = (char*)can_fail_malloc(sizeof(char) * (strlen(jogo ->equipa1) + 1));
    strcpy(x ->j->equipa1, jogo ->equipa1);
    x ->j ->equipa2 = (char*)can_fail_malloc(sizeof(char) * (strlen(jogo ->equipa2) + 1));
    strcpy(x ->j ->equipa2, jogo->equipa2);
    x->j->score1 = jogo ->score1;
    x->j->score2 = jogo ->score2;
    x->next = NULL;
    return x;
}

campeonato search_hash(campeonato *heads, char *name)
{
    int M = MAX_TABEL;
    int i = hash(name, M);
    return searchList(heads[i], name);
}

campeonato searchList(campeonato head, char *name)
{
    campeonato cabeca;
    for (cabeca = head; cabeca != NULL; cabeca = cabeca-> next)
    {
        if (strcmp(cabeca->j->nome, name) == 0)
            return cabeca;
    }
    return NULL;
}

copa *NOVA_COPA(game head)
{
    /* Cria um elemento para colocar na lista organizada por ordem de insercao */
    copa *x = (copa*)can_fail_malloc(sizeof(struct copas)); 
    x->text = strdup(head->nome);
    x->Pequipa = strdup(head->equipa1);
    x->Sequipa = strdup(head->equipa2);
    x->Pscore = head->score1;
    x->Sscore = head->score2;
    x ->next= NULL;
    return x;
}

copa *InsereEnd(copa *head, game j)
{
    /* Insere este elemento no fim */
    copa *x;
    if (head == NULL)
    {
        return NOVA_COPA(j);
    }
    for (x = head; x->next != NULL; x = x->next);
    x->next = NOVA_COPA(j);
    return head;
}


copa *RLista(copa *head, char *nome)
{
    /* Remove um elemento organizado pela ordem de insercao*/
    copa *t, *prev;
    for (t = head, prev = NULL; t!= NULL; prev = t, t = t->next)
    {
        if (strcmp(t ->text, nome) == 0)
        {
            if (t == head)
            {
                head = t ->next;
            }
            else
                prev->next = t->next;
            free(t->text);
            free(t->Pequipa);
            free(t->Sequipa);
            free(t);
            return head; 
        }
    }
    return head;
}


copa *Search_Copas(copa *head, char *nome)
{
    /* Procura numa lista do tipo copas */
    copa *t;
    for (t = head; t != NULL;t = t->next)
    {
        if (strcmp(t ->text, nome) == 0)
        {
            return t;
        }
    }
    free(t);
    return NULL;
}


campeonato libertahashtable(campeonato jogo)
{
    /* daa free dos indices da hash */
    if (jogo != NULL)
    {    
        campeonato old;
        old = jogo;
        jogo = jogo->next;
        free(old->j->equipa1);
        free(old->j ->equipa2);
        free(old->j ->nome);
        free(old->j);
        free(old);
    }
    return jogo;
}

copa *libertalista(copa *lista)
{
    /* Da free da lista das copas */
    if (lista != NULL)
    {    
        copa *old;
        old = lista;
        lista = lista->next;

        free(old->Pequipa);
        free(old->Sequipa);
        free(old->text);
        free(old);
    }
    return lista;
}