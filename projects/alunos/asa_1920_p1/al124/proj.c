#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Projeto 1 
   Grupo 124
   Bernardo Pereira n89420 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/*//////////////////////////////////////////
                Estruturas
//////////////////////////////////////////*/

typedef struct node *link;

struct node
{
    int v;
    link next;
};

typedef struct graph
{
    int V;
    link *adj;
} * Graph;

Graph g;
int *notas;
Graph redes;
link stack;
int nrede = 0;

link NEW(int v)
{ /* cria um novo elemento */
    link x = (link)can_fail_malloc(sizeof(struct node));
    x->v = v;
    x->next = NULL;
    return x;
}

int pop(bool *onStack) /* retira o elemento no topo da stack */
{
    int aux = stack->v;
    onStack[aux] = false;
    link aux_l = stack;
    stack = stack->next;
    free(aux_l);
    return aux;
}

void push(int n, bool *onStack) /* adiciona um elemento no topo da stack */
{
    link x = stack;
    stack = NEW(n);
    stack->next = x;
    onStack[n] = true;
}

Graph GRAPHinit(int V)
{
    Graph G = can_fail_malloc(sizeof(struct graph));
    G->adj = (link *)can_fail_malloc(sizeof(link) * V);
    G->V = V;
    return G;
}

void GRAPHinsertE(int v1, int v2)
{
    link x;
    if (g->adj[v1] == NULL)
    {
        g->adj[v1] = NEW(v2);
    }
    else
    {
        for (x = g->adj[v1]; x->next != NULL; x = x->next)
        {
            ;
        }
        x->next = NEW(v2);
    }
}

/*//////////////////////////////////////////
            LEITURA DE INPUT
//////////////////////////////////////////*/

void read_input()
{
    int nAlunos;
    int nRelacoes;
    if (scanf("%d", &nAlunos) == 0)
    {
        exit(1);
    }
    getchar();
    if (nAlunos < 2) /* Erro de input no numero de alunos */
    {
        exit(1);
    }

    g = GRAPHinit(nAlunos);
    notas = (int *)can_fail_malloc(nAlunos * sizeof(int));

    if (scanf("%d", &nRelacoes) == 0)
    {
        exit(1);
    }

    getchar();
    int i = 0;
    for (; nAlunos > 0; nAlunos--)
    {
        int nota;
        if (scanf("%d", &nota) == 0)
        {
            exit(1);
        }
        getchar();
        notas[i] = nota;
        i++;
    }
    for (; nRelacoes > 0; nRelacoes--)
    {
        int r1, r2;
        if (scanf("%d %d", &r1, &r2) == 0)
        {
            exit(1);
        }
        getchar();
        GRAPHinsertE(r1 - 1, r2 - 1);
    }
}

/*//////////////////////////////////////////
     VER ELEMENTOS FORTEMENTE LIGADOS
//////////////////////////////////////////*/

void tarjan_aux(int node, int *dist, bool *onStack, int *low)
{
    static int distance = 0;
    link aux = g->adj[node];
    distance++;
    dist[node] = low[node] = distance;
    push(node, onStack);

    while (aux != NULL)
    {
        if (dist[aux->v] == -1)
        {
            tarjan_aux(aux->v, dist, onStack, low);
            low[node] = MIN(low[node], low[aux->v]);
        }
        else if (onStack[aux->v])
        {
            low[node] = MIN(low[node], dist[aux->v]);
        }
        aux = aux->next;
    }

    if (low[node] == dist[node])
    {
        int maxNota = 0;
        while (stack->v != node)
        {
            if (notas[stack->v] > maxNota) /* Verifica qual a nota max dos elementos fortemente ligados */
            {
                maxNota = notas[stack->v];
            }
            if (redes->adj[nrede] == NULL) /* Guarda os elementos fortemente ligados numa lista ligada */
            {
                redes->adj[nrede] = NEW(stack->v);
            }
            else
            {
                link aux = redes->adj[nrede];
                redes->adj[nrede] = NEW(stack->v);
                redes->adj[nrede]->next = aux;
            }
            pop(onStack);
        }
        if (notas[stack->v] > maxNota)
        {
            maxNota = notas[stack->v];
        }
        if (redes->adj[nrede] == NULL)
        {
            redes->adj[nrede] = NEW(stack->v);
        }
        else
        {
            link aux = redes->adj[nrede];
            redes->adj[nrede] = NEW(stack->v);
            redes->adj[nrede]->next = aux;
        }
        pop(onStack);
        link x;
        for (x = redes->adj[nrede]; x != NULL; x = x->next) /* Modifica as notas de todos os elementos para a nota maxima deles */
        {
            notas[x->v] = maxNota;
        }
    }
    nrede++;
}

/*//////////////////////////////////////////
          OUTUPUT DO PROGRAMA
//////////////////////////////////////////*/
void print_notas()
{
    int i = 0;
    for (; i < g->V; i++)
    {
        printf("%d\n", notas[i]);
    }
}

bool rede_check(int nrede, int n) /*Verifica se é fortemente ligado*/
{
    link el_rede;
    for (el_rede = redes->adj[nrede]; el_rede != NULL; el_rede = el_rede->next)
    {
        if (el_rede->v == n)
        {
            return true;
        }
    }
    return false;
}

void change_notas_rede(int nrede, int nota) /*troca todas as notas de todos os elementos fortemente ligados */
{
    link el_rede;
    for (el_rede = redes->adj[nrede]; el_rede != NULL; el_rede = el_rede->next)
    {
        notas[el_rede->v] = nota;
    }
}

/*//////////////////////////////////////////
            ALGORITMO TARJAN
//////////////////////////////////////////*/
void tarjan()
{
    int i;
    int *dist = (int *)can_fail_malloc(sizeof(int) * g->V);
    bool *onStack = (bool *)can_fail_malloc(sizeof(bool) * g->V);
    int *low = (int *)can_fail_malloc(sizeof(int) * g->V);
    redes = GRAPHinit(g->V);
    for (i = 0; i < g->V; i++)
    {
        dist[i] = -1;
        onStack[i] = false;
    }
    for (i = 0; i < g->V; i++)
    {
        if (dist[i] == -1)
        {
            tarjan_aux(i, dist, onStack, low);
        }
    }
    int nrede;
    for (nrede = 0; nrede < g->V; nrede++)
    {
        link el_rede;
        for (el_rede = redes->adj[nrede]; el_rede != NULL; el_rede = el_rede->next)
        {
            link el_adj;
            for (el_adj = g->adj[el_rede->v]; el_adj != NULL; el_adj = el_adj->next)
            {
                if (!rede_check(nrede, el_adj->v)) /* Se um elemento tiver ligacao a outro q nao seja fortemente ligado a ele, recalcula a nota de todos os fortemente ligados a ele */
                {
                    if (notas[el_adj->v] > notas[el_rede->v])
                    {
                        change_notas_rede(nrede, notas[el_adj->v]);
                    }
                }
            }
        }
    }
}

/*//////////////////////////////////////////
                  MAIN
//////////////////////////////////////////*/

int main(int argc, char *argv[])
{
    read_input();
    tarjan();
    print_notas();
    return 0;
}