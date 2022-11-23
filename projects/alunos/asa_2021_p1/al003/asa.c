#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define STACK_IS_EMPTY -1
#define STACK_IS_NOT_EMPTY 0

typedef enum
{
    WHITE,
    GRAY,
    BLACK,
} Color;

typedef struct dependence
{
    int id_domino;
    struct dependence *next_dep;
} Dependence;

typedef struct domino
{
    int idDomino;
    int does_depend;
    int color;
    Dependence *first;
    Dependence *last;
    struct domino *nextAfterSort;
    struct domino *previousAfterSort;
} Domino;

typedef struct game
{
    int num_pieces;
    int sources;
    int maxSequence;
    Domino *dominos;
    Domino *firstAfterSort;
    Domino *lastAfterSort;
} Game;

typedef struct stack_el
{
    int id;
    struct stack_el *next;
    struct stack_el *previous;
} StackEl;

typedef struct stack
{
    StackEl *first;
    StackEl *last;
} Stack;

StackEl *newStackEl(int id)
{
    StackEl *el = (StackEl *)can_fail_malloc(sizeof(StackEl));
    el->id = id;
    el->next = NULL;
    el->previous = NULL;
    return el;
}

void freeStackEl(StackEl *el)
{
    free(el);
}

Stack *newStack()
{
    Stack *s = (Stack *)can_fail_malloc(sizeof(Stack));
    s->first = NULL;
    s->last = NULL;
    return s;
}

void freeStack(Stack *s)
{
    StackEl *aux1, *aux2;
    aux1 = s->first;
    while (aux1)
    {
        aux2 = aux1->next;
        freeStackEl(aux1);
        aux1 = aux2;
    }
    free(s);
}

int isStackEmpty(Stack *s)
{
    if (!s->first)
    {
        return STACK_IS_EMPTY;
    }
    return STACK_IS_NOT_EMPTY;
}

void push(Stack *s, int id)
{
    StackEl *el = newStackEl(id);
    if (isStackEmpty(s))
    {
        /*a stack esta vazia*/
        s->first = el;
    }
    else
    {
        /*a stack nao esta vazia*/
        s->last->next = el;
        el->previous = s->last;
    }
    s->last = el;
}

int pop(Stack *s)
{
    StackEl *el;
    int id;
    if (isStackEmpty(s))
        return STACK_IS_NOT_EMPTY; /*stack esta vazia*/
    el = s->last;
    if (!s->first->next)
    { /*e o unico elemento da stack*/
        s->first = NULL;
        s->last = NULL;
    }
    else
    {
        s->last->previous->next = NULL;
        s->last = el->previous;
    }
    id = el->id;
    freeStackEl(el);
    return id;
}

Game *createGame(int num_pieces)
{
    Game *g = (Game *)can_fail_malloc(sizeof(Game));
    g->num_pieces = num_pieces;
    g->sources = 0;
    g->maxSequence = 0;
    g->dominos = can_fail_malloc(num_pieces * sizeof(Domino));
    g->firstAfterSort = can_fail_malloc(sizeof(Domino));
    g->firstAfterSort = NULL;
    g->lastAfterSort = can_fail_malloc(sizeof(Domino));
    g->lastAfterSort = NULL;
    return g;
}

void addDomino(Domino *domino, int id)
{
    domino->idDomino = id;
    domino->does_depend = FALSE;
    domino->color = WHITE;
    domino->first = NULL;
    domino->last = NULL;
    domino->nextAfterSort = NULL;
    domino->previousAfterSort = NULL;
}

void addDependence(Game *game, int piece, int dependence)
{
    Dependence *dep = (Dependence *)can_fail_malloc(sizeof(Dependence));
    Domino *d = game->dominos + piece - 1;
    Domino *aux = game->dominos + dependence - 1;
    dep->next_dep = NULL;
    dep->id_domino = dependence;
    if (d->first == NULL)
    {
        d->first = dep;
    }
    else
    {
        d->last->next_dep = dep;
    }
    d->last = dep;
    aux->does_depend = TRUE;
}

void countSources(Game *g)
{
    int i, counter = 0;
    for (i = 0; i < g->num_pieces; i++)
    {
        Domino *d = g->dominos + i;
        if (!d->does_depend)
        {
            counter++;
        }
    }
    g->sources = counter;
}

void longestPath(Game *g)
{
    int i;
    int levels[g->num_pieces];
    for (i = 0; i < g->num_pieces; i++)
    {
        levels[i] = 1;
    }
    Domino *d = g->firstAfterSort;
    while (d)
    {
        if (d->first != NULL)
        {
            Dependence *dep = d->first;
            while (dep)
            {
                if (levels[d->idDomino - 1] + 1 > levels[dep->id_domino - 1])
                {
                    levels[dep->id_domino - 1] = levels[d->idDomino - 1] + 1;
                }
                dep = dep->next_dep;
            }
        }
        d = d->nextAfterSort;
    }
    for (i = 0; i < g->num_pieces; i++)
    {
        if (levels[i] > g->maxSequence)
        {
            g->maxSequence = levels[i];
        }
    }
}

void topSort(Game *g, Domino *d)
{
    if (g->lastAfterSort == NULL)
    {
        g->lastAfterSort = d;
    }
    else
    {
        g->firstAfterSort->previousAfterSort = d;
        d->nextAfterSort = g->firstAfterSort;
    }
    g->firstAfterSort = d;
}

void dfs(Game *g)
{
    Stack *s = newStack();
    int i, id;
    Domino *d1;
    for (i = 0; i < g->num_pieces; i++)
    {
        Domino *d = g->dominos + i;
        if (d->color == WHITE)
        {
            push(s, d->idDomino);
            while (!isStackEmpty(s))
            {
                StackEl *el = s->last;
                id = el->id;
                d = g->dominos + id - 1;
                if (d->first == NULL)
                {
                    id = pop(s);
                    d = g->dominos + id - 1;
                    topSort(g, d);
                    d->color = BLACK;
                }
                else
                {
                    if (d->color == GRAY)
                    {
                        id = pop(s);
                        d = g->dominos + id - 1;
                        topSort(g, d);
                        d->color = BLACK;
                    }
                    else
                    {
                        Dependence *dep;
                        for (dep = d->first; dep != NULL; dep = dep->next_dep)
                        {
                            id = dep->id_domino;
                            d1 = g->dominos + id - 1;
                            if (d1->color == WHITE)
                            {
                                push(s, d1->idDomino);
                            }
                        }
                        d->color = GRAY;
                    }
                }
            }
        }
    }
}

int main()
{
    int num_pieces, num_dependences, i;
    int tmp1, tmp2;
    Domino *domino;

    if (scanf("%d %d", &num_pieces, &num_dependences))
    {
        Game *game = createGame(num_pieces);
        for (i = 0; i < num_pieces; i++)
        {
            domino = game->dominos + i;
            addDomino(domino, i + 1);
        }
        for (i = 0; i < num_dependences; i++)
        {
            if (scanf("%d %d", &tmp1, &tmp2))
            {
                addDependence(game, tmp1, tmp2);
            }
        }
        countSources(game);
        dfs(game);
        longestPath(game);
        printf("%d %d\n", game->sources, game->maxSequence);
    }

    return 0;
}
