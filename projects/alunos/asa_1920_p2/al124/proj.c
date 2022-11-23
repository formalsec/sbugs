#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* Projeto 2 
   Grupo 124
   Bernardo Pereira n89420 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/*//////////////////////////////////////////
                Estruturas
//////////////////////////////////////////*/

typedef struct node *link;

struct node
{
    int s1;
    int s2;
    int t1;
    int t2;
    int C;
    int flow;
    link next;
};

typedef struct cruz
{
    bool flow;
    int level;
    link adj;
    link adj_end;
} * Cruz;

typedef struct stack *Stack;

struct stack
{
    Cruz vert;
    Stack next;
};

typedef struct graph
{
    int M;
    int N;
    Cruz **mat;
} * Graph;

Graph g;
Stack stack_end;
Stack stack;

void stack_add(Cruz vert)
{ /* cria uma nova aresta */
    Stack x = (Stack)can_fail_malloc(sizeof(struct stack));
    x->vert = vert;
    x->next = NULL;
    if (stack == NULL)
    {
        stack = x;
        stack_end = x;
    }
    else
    {
        stack_end->next = x;
        stack_end = stack_end->next;
    }
}

Stack stack_popbegin()
{
    Stack aux;
    aux = stack;
    stack = stack->next;
    return aux;
}

link NEW(int s1, int s2, int t1, int t2)
{ /* cria uma nova aresta */
    link x = (link)can_fail_malloc(sizeof(struct node));
    x->s1 = s1;
    x->s2 = s2;
    x->t1 = t1;
    x->t2 = t2;
    x->C = 1;
    x->flow = 0;
    x->next = NULL;
    return x;
}

Cruz NEW_cruz()
{ /* cria um novo elemento */
    Cruz x = (Cruz)can_fail_malloc(sizeof(struct cruz));
    x->flow = false;
    return x;
}

void cruz_flow(int i, int j, bool v)
{
    if (!(i == 0 && j == 0) || (i == g->M + 1 && j == 0))
    {
        g->mat[i][j]->flow = v;
    }
}

void cruz_level(int i, int j, int v)
{
    g->mat[i][j]->level = v;
}
void GRAPHinsertE(int s1, int s2, int t1, int t2)
{
    if (g->mat[s1][s2]->adj == NULL)
    {
        link aux = NEW(s1, s2, t1, t2);
        g->mat[s1][s2]->adj = aux;
        g->mat[s1][s2]->adj_end = aux;
    }
    else
    {
        g->mat[s1][s2]->adj_end->next = NEW(s1, s2, t1, t2);
        g->mat[s1][s2]->adj_end = g->mat[s1][s2]->adj_end->next;
    }
}

void GRAPHinitiateEdges()
{
    int i = 1;
    for (; i <= g->M; i++)
    {
        int j = 1;
        for (; j <= g->N; j++)
        {
            if (i == 1)
            {
                if (j == 1)
                {
                    GRAPHinsertE(i, j, i, j + 1);
                    GRAPHinsertE(i, j, i + 1, j);
                }
                else if (j == g->N)
                {
                    GRAPHinsertE(i, j, i + 1, j);
                    GRAPHinsertE(i, j, i, j - 1);
                }
                else
                {
                    GRAPHinsertE(i, j, i + 1, j);
                    GRAPHinsertE(i, j, i, j - 1);
                    GRAPHinsertE(i, j, i, j + 1);
                }
            }
            else if (i == g->M)
            {
                if (j == 1)
                {
                    GRAPHinsertE(i, j, i - 1, j);
                    GRAPHinsertE(i, j, i, j + 1);
                }
                else if (j == g->N)
                {
                    GRAPHinsertE(i, j, i - 1, j);
                    GRAPHinsertE(i, j, i, j - 1);
                }
                else
                {
                    GRAPHinsertE(i, j, i - 1, j);
                    GRAPHinsertE(i, j, i, j - 1);
                    GRAPHinsertE(i, j, i, j + 1);
                }
            }
            else
            {
                if (j == 1)
                {
                    GRAPHinsertE(i, j, i - 1, j);
                    GRAPHinsertE(i, j, i, j + 1);
                    GRAPHinsertE(i, j, i + 1, j);
                }
                else if (j == g->N)
                {
                    GRAPHinsertE(i, j, i - 1, j);
                    GRAPHinsertE(i, j, i, j - 1);
                    GRAPHinsertE(i, j, i + 1, j);
                }
                else
                {
                    GRAPHinsertE(i, j, i - 1, j);
                    GRAPHinsertE(i, j, i, j - 1);
                    GRAPHinsertE(i, j, i, j + 1);
                    GRAPHinsertE(i, j, i + 1, j);
                }
            }
        }
    }
}

Graph GRAPHinit(int M, int N)
{
    Graph G = can_fail_malloc(sizeof(struct graph));
    G->M = M;
    G->N = N;
    G->mat = (Cruz **)can_fail_malloc((M + 2) * sizeof(Cruz *));
    int i = 0;
    for (; i <= M; i++)
    {
        int j = 0;
        G->mat[i] = (Cruz *)can_fail_malloc((N + 1) * sizeof(Cruz));
        for (; j <= N; j++)
        {
            G->mat[i][j] = NEW_cruz();
        }
    }
    G->mat[M + 1] = (Cruz *)can_fail_malloc(sizeof(Cruz)); /*sink*/
    G->mat[M + 1][0] = NEW_cruz();
    return G;
}

/*//////////////////////////////////////////
            LEITURA DE INPUT
//////////////////////////////////////////*/

int read_input()
{
    int output = 0;
    int M, N, S, C;
    if (scanf("%d %d", &M, &N) == 0)
    {
        exit(1);
    }

    getchar();

    if (scanf("%d %d", &S, &C) == 0)
    {
        exit(1);
    }
    getchar();
    g = GRAPHinit(M, N);
    GRAPHinitiateEdges();
    int i = 0;
    int supermercado[S][2];
    for (; i < S; i++)
    {
        int s1, s2;
        bool flag = false;
        if (scanf("%d %d", &s1, &s2) == 0)
        {
            exit(1);
        }
        getchar();
        int j = 0;
        for (; j < i; j++)
        {
            if (supermercado[j][0] == s1 && supermercado[j][1] == s2)
            {
                flag = true;
            }
        }
        if (!flag)
        {
            supermercado[i][0] = s1;
            supermercado[i][1] = s2;
            GRAPHinsertE(s1, s2, M + 1, 0); /* criar ligacao entre cada supermercado e um sink imaginario fora do grafo*/
        }
    }
    i = 0;
    for (; i < C; i++)
    {
        int t1, t2;
        if (scanf("%d %d", &t1, &t2) == 0)
        {
            exit(1);
        }
        getchar();
        int j = 0;
        for (; j < S; j++)
        {
            if (t1 == supermercado[j][0] && t2 == supermercado[j][1] && !g->mat[t1][t2]->flow)
            {
                output++;
                g->mat[t1][t2]->flow = true;
            }
        }
        bool flag = false;
        link a;
        for (a = g->mat[0][0]->adj; a != NULL; a = a->next)
        {
            if (a->t1 == t1 && a->t2 == t2)
            {
                a->C++;
                flag = true;
            }
        }
        if (!flag)
            GRAPHinsertE(0, 0, t1, t2); /* criar ligacao entre uma source imaginaria fora do grafo e cada cidadao*/
    }
    return output;
}

/*//////////////////////////////////////////
     Resolver o problema max flow
//////////////////////////////////////////*/

bool bfs()
{
    int i = 0;
    for (; i <= g->M; i++)
    {
        int j = 0;
        for (; j <= g->N; j++)
        {
            if (i == 0 && j == 0)
            {
                cruz_level(0, 0, 0);
            }
            else
            {
                cruz_level(i, j, -1);
                link aux;
                for (aux = g->mat[i][j]->adj; aux != NULL; aux = aux->next)
                {
                    if (aux->flow >= aux->C)
                    {
                        g->mat[i][j]->flow = true;
                    }
                }
            }
        }
    }
    cruz_level(g->M + 1, 0, -1);
    stack_add(g->mat[0][0]);
    while (stack != NULL)
    {
        Stack aux = stack_popbegin();
        Cruz cruz = aux->vert;
        link ar;
        for (ar = cruz->adj; ar != NULL; ar = ar->next)
        {
            int t1 = ar->t1;
            int t2 = ar->t2;
            if (g->mat[t1][t2]->level < 0 && ar->flow < ar->C && !g->mat[t1][t2]->flow)
            {
                cruz_level(t1, t2, cruz->level + 1);
                stack_add(g->mat[t1][t2]);
            }
        }
    }
    if (g->mat[g->M + 1][0]->level < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int send_flow(Cruz cruz, int flow)
{
    if (cruz == g->mat[g->M + 1][0])
    {
        return flow;
    }

    link ar = cruz->adj;
    while (ar != NULL)
    {
        Cruz v;
        v = g->mat[ar->t1][ar->t2];
        if ((v->level == (cruz->level + 1)) && ar->flow < ar->C && !v->flow)
        {
            int curr_flow = MIN(flow, ar->C - ar->flow);

            int temp_flow = send_flow(v, curr_flow);

            if (temp_flow > 0)
            {
                ar->flow += temp_flow;
                return temp_flow;
            }
        }
        ar = ar->next;
    }
    return 0;
}

/*//////////////////////////////////////////
            ALGORITMO DINIC
//////////////////////////////////////////*/

int dinic()
{
    int total = 0;
    int flow;
    while (bfs() == true)
    {
        while ((flow = send_flow(g->mat[0][0], (g->M * g->N * 2))))
        { /* Valor g->N* g->M*4 e um valor inobtivel dai o uso dele, poderia se usar infinito*/
            total += flow;
        }
    }
    return total;
}
/*//////////////////////////////////////////
                  MAIN
//////////////////////////////////////////*/

int main(int argc, char *argv[])
{
    int output = read_input();
    output = output + dinic();
    printf("%d\n", output);
    return 0;
}