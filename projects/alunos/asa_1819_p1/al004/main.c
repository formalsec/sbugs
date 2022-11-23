#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)

int scc_max = 0;

typedef struct item_t
{
    struct list_node_t *head;
    unsigned d;     /* discovery */
    unsigned l;     /* low */
    unsigned v : 1; /* visited / exists */
    unsigned a : 1; /* articulation point */
    unsigned s : 1; /* stack */
    unsigned p : 1; /* parent */
} item;

typedef int item_key;

typedef struct list_node_t
{
    item_key i;
    struct list_node_t *n;
} list_node;

item_key get_current_item(list_node *n)
{
    return n->i;
}

list_node *insert_item(list_node *head, item_key i)
{
    list_node *new_node = (list_node *)can_fail_malloc(sizeof(list_node));
    new_node->i = i;
    new_node->n = head;

    return new_node;
}

list_node *delete_item(list_node *head, item_key k)
{
    list_node *aux;
    list_node *prev = NULL;

    if (head == NULL)
    {
        return NULL;
    }

    for (aux = head; aux != NULL; aux = aux->n)
    {
        if (aux->i == k)
        {
            if (aux == head)
            {
                head = aux->n;
            }
            else
            {
                prev->n = aux->n;
            }

            free(aux);
            return head;
        }

        prev = aux;
    }

    return head;
}

item_key pop_item(list_node **head)
{
    item_key i = (*head)->i;
    *head = delete_item(*head, i);
    return i;
}

item_key search_item(list_node *head, item_key k)
{
    list_node *aux;

    for (aux = head; aux != NULL; aux = aux->n)
    {
        if (aux->i == k)
        {
            return get_current_item(aux);
        }
    }

    return -1;
}

int get_list_size(list_node *head)
{
    list_node *aux;
    int size = 0;

    for (aux = head; aux != NULL; aux = aux->n)
    {
        size++;
    }

    return size;
}

void free_linked_list(list_node *head)
{
    list_node *aux = head;
    list_node *aux2;

    while (aux != NULL)
    {
        aux2 = aux->n;
        free(aux);
        aux = aux2;
    }
}

item *init_item(int id)
{
    item *n = (item *)can_fail_malloc(sizeof(item));
    n->head = NULL;
    n->d = 0;
    n->v = 0;
    n->a = 0;
    n->l = 0;
    n->s = 0;
    n->p = 0;

    return n;
}

void free_item(item *i)
{
    free_linked_list(i->head);
    free(i);
}

typedef struct graph_t
{
    item *g;
    int v_number;
    int e_number;
} graph;

int check_bounds(graph *g, item_key i1, item_key i2)
{
    if (i2 == -1)
    {
        return ((i1 < g->v_number) && (g->g[i1].v != -1));
    }

    return ((i1 < g->v_number) && (i2 < g->v_number) && (g->g[i1].v != -1) &&
            (g->g[i2].v != -1));
}

graph *init_graph(int V)
{
    int i = 0;

    graph *res = (graph *)can_fail_malloc(sizeof(graph));
    item *g = (item *)can_fail_malloc(sizeof(item) * V);
    res->g = g;
    res->v_number = V;
    res->e_number = 0;

    for (i = 0; i < V; i++)
    {
        res->g[i].head = NULL;
        res->g[i].d = 0;
        res->g[i].v = 0;
        res->g[i].a = 0;
        res->g[i].l = 0;
        res->g[i].s = 0;
        res->g[i].p = 0;
    }

    return res;
}

void insert_edge(graph *g, item_key i1, item_key i2)
{
    if (check_bounds(g, i1, i2))
    {
        g->g[i1].head = insert_item(g->g[i1].head, i2);
        g->g[i2].head = insert_item(g->g[i2].head, i1);
        g->e_number++;
    }
}

void remove_edge(graph *g, item_key i1, item_key i2)
{
    if (check_bounds(g, i1, i2))
    {
        g->g[i1].head = delete_item(g->g[i1].head, i2);
        g->g[i2].head = delete_item(g->g[i2].head, i1);
        g->e_number--;
    }
}

void remove_vertex(graph *g, item_key i1)
{
    if (check_bounds(g, i1, -1))
    {
        list_node *aux = g->g[i1].head;
        list_node *aux2;

        while (aux != NULL)
        {
            aux2 = aux->n;
            remove_edge(g, i1, aux->i);
            aux = aux2;
        }

        g->g[i1].v = -1;
    }
}

item *search_edge(graph *g, item_key id, item_key fid)
{
    if (check_bounds(g, id, fid))
    {
        return &g->g[search_item(g->g[id].head, fid)];
    }

    return NULL;
}

void reset_graph(graph *g)
{
    int i;

    for (i = 0; i < g->v_number; i++)
    {
        if (g->g[i].v != -1)
        {
            g->g[i].d = 0;
            g->g[i].v = 0;
            g->g[i].p = 0;
            g->g[i].a = 0;
            g->g[i].l = 0;
            g->g[i].s = 0;
        }
    }
}

void free_graph(graph *g)
{
    int(i);

    for (i = 0; i < g->v_number; i++)
    {
        free_linked_list(g->g[i].head);
    }

    free(g->g);
    free(g);
}

list_node *get_articulation_vertex(graph *g)
{
    int i;
    list_node *res = NULL;

    for (i = 0; i < g->v_number; i++)
    {
        if (g->g[i].a)
        {
            res = insert_item(res, i);
        }
    }

    return res;
}

void print_graph(graph *g)
{
    list_node *aux;
    int i;

    for (i = 0; i < g->v_number; i++)
    {
        if (g->g[i].v != -1)
        {
            printf("%d ", i);
            for (aux = g->g[i].head; aux != NULL; aux = aux->n)
            {
                printf("%d ", aux->i);
            }

            printf("\n");
        }
    }
}

void tarjan(graph *g, item_key ik, list_node **scc, list_node **stack, int time)
{
    int children = 0;
    list_node *edge;
    item *i2;
    item *i = &g->g[ik];

    i->v = 1;
    i->d = time;
    i->l = time;
    time++;

    *stack = insert_item(*stack, ik);
    i->s = 1;

    if (i->head != NULL)
    {
        for (edge = i->head; edge != NULL; edge = edge->n)
        {
            i2 = &g->g[edge->i];

            if (i2->v == 0)
            {
                i2->p = 1;
                children++;

                tarjan(g, edge->i, scc, stack, time);

                if (i->l > i2->l)
                {
                    i->l = i2->l;
                }

                if ((i->p == 0 && children > 1) || (i->p != 0 && i->d <= i2->l))
                {
                    i->a = 1;
                }
            }
            else if ((i2->s) && (i->l > i2->d))
            {
                i->l = i2->d;
            }
        }
    }

    if (i->l == i->d)
    {
        int scc_n = 1;
        int n = pop_item(stack);
        int max_item = n;

        while (ik != n)
        {
            n = pop_item(stack);
            g->g[n].s = 0;

            if (n > max_item)
            {
                max_item = n;
            }

            scc_n++;
        }

        *scc = insert_item(*scc, max_item);

        if (scc_n > scc_max)
        {
            scc_max = scc_n;
        }
    }
}

list_node *find_SCC(graph *g)
{
    list_node *scc = NULL;
    list_node *stack = NULL;
    int i = 0;

    scc_max = 0;

    for (i = g->v_number - 1; i >= 0; i--)
    {
        if (g->g[i].v != -1 && g->g[i].v == 0)
        {
            tarjan(g, i, &scc, &stack, 0);
        }
    }
    free_linked_list(stack);

    return scc;
}

int main()
{
    int N, M;
    int i, x, y;
    graph *g;
    list_node *aux;
    list_node *scc;
    int comp;
    list_node *adj;

    scanf("%d", &N);
    scanf("%d", &M);

    g = init_graph(N);

    for (i = 0; i < M; i++)
    {
        scanf("%d %d", &x, &y);
        insert_edge(g, x - 1, y - 1);
    }

    scc = find_SCC(g);
    comp = get_list_size(scc);
    printf("%d\n", comp);

    for (aux = scc; aux->n != NULL; aux = aux->n)
    {
        printf("%d ", aux->i + 1);
    }
    printf("%d\n", aux->i + 1);

    adj = get_articulation_vertex(g);
    printf("%d\n", get_list_size(adj));

    reset_graph(g);
    for (aux = adj; aux != NULL; aux = aux->n)
    {

        g->g[aux->i].v = 1; /* ignores vertice in tarjan */
    }

    free_linked_list(scc);
    scc = find_SCC(g);
    printf("%d\n", scc_max);

    free_linked_list(adj);
    free_linked_list(scc);
    free_graph(g);

    return 0;
}