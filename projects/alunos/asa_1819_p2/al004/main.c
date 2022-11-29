#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#pragma pack(1)

typedef struct item_key_t
{
    unsigned _from;
    unsigned _to;
} item_key;

typedef struct item_t /* Edge representation */
{
    item_key *_key;
    unsigned _c; /* capacity */
    int _f;      /* flux */
} item;

typedef item edge;

item *init_item(unsigned from, unsigned to, unsigned c)
{
    item *new = (item *)can_fail_malloc(sizeof(item));
    new->_key = (item_key *)can_fail_malloc(sizeof(item_key));
    new->_key->_from = from;
    new->_key->_to = to;
    new->_c = c;
    new->_f = 0;

    return new;
}

unsigned get_residual_capacity_item(item *i1)
{
    return i1->_c - i1->_f;
}

unsigned get_from_item(item *i1)
{
    return i1->_key->_from;
}

unsigned get_to_item(item *i1)
{
    return i1->_key->_to;
}

unsigned get_capacity_item(item *i1)
{
    return i1->_c;
}

int get_flux_item(item *i1)
{
    return i1->_f;
}

int get_flux_inverse_item(item *i1)
{
    return -i1->_f;
}

int get_residual_capacity_inverse_item(item *i1)
{
    return i1->_f;
}

int equal_items(item *i1, item *i2)
{
    if ((i1 == NULL) || (i2 == NULL))
    {
        return 0;
    }

    return (i1->_key->_from == i2->_key->_from) && (i1->_key->_to == i2->_key->_to);
}

int compare_to_key(item *i1, item_key k)
{
    if (i1 == NULL)
    {
        return 0;
    }

    return (i1->_key->_from == k._from) && (i1->_key->_to == k._to);
}

void set_flux_item(item *i, int f)
{
    i->_f = f;
}

void set_capacity_item(item *i, unsigned c)
{
    i->_c = c;
}

void free_item(item *i)
{
    free(i->_key);
    free(i);
}

item_key *init_item_key(unsigned from, unsigned to)
{
    item_key *res = (item_key *)can_fail_malloc(sizeof(item_key *));
    res->_from = from;
    res->_to = to;

    return res;
}

void free_item_key(item_key *i)
{
    free(i);
}

void insertion_sort(item *edges[], unsigned size)
{
    unsigned i = 1, j;
    item *aux;

    while (i < size)
    {
        j = i;

        while ((j > 0) && ((get_from_item(edges[j - 1]) > get_from_item(edges[j])) || ((get_from_item(edges[j - 1]) == get_from_item(edges[j])) && (get_to_item(edges[j - 1]) > get_to_item(edges[j])))))
        {
            aux = edges[j - 1];
            edges[j - 1] = edges[j];
            edges[j] = aux;
            j--;
        }

        i++;
    }
}

void merge(item *edges[], unsigned i, unsigned m, unsigned f)
{
    unsigned size = f - i + 1;
    unsigned n1 = i;
    unsigned n2 = m + 1;

    unsigned k;

    item **aux = (item **)can_fail_malloc(sizeof(item *) * size);
    unsigned aux_n = 0;

    while (n1 <= m && n2 <= f)
    {
        if (get_from_item(edges[n1]) < get_from_item(edges[n2]))
        {
            aux[aux_n] = edges[n1];
            n1++;
        }
        else if (get_from_item(edges[n1]) == get_from_item(edges[n2]) && get_to_item(edges[n1]) < get_to_item(edges[n2]))
        {
            aux[aux_n] = edges[n1];
            n1++;
        }

        else
        {
            aux[aux_n] = edges[n2];
            n2++;
        }

        aux_n++;
    }

    while (n1 <= m)
    {
        aux[aux_n] = edges[n1];
        n1++;
        aux_n++;
    }

    while (n2 <= f)
    {
        aux[aux_n] = edges[n2];
        n2++;
        aux_n++;
    }

    for (k = i; k <= f; k++)
    {
        edges[k] = aux[k - i];
    }

    free(aux);
}

void merge_sort(item *edges[], unsigned i, unsigned f)
{
    if (i < f)
    {
        unsigned m = (f + i) / 2;
        merge_sort(edges, i, m);
        merge_sort(edges, m + 1, f);
        merge(edges, i, m, f);
    }
}

typedef struct list_node_t
{
    item *_i;
    struct list_node_t *_n;
} list_node;

item *get_current_item(list_node *n)
{
    return n->_i;
}

list_node *insert_item(list_node *head, item *i)
{
    list_node *new_node = (list_node *)can_fail_malloc(sizeof(list_node));
    new_node->_i = i;
    new_node->_n = head;

    return new_node;
}

list_node *insert_item_end(item *i, list_node *tail)
{
    list_node *new_node = (list_node *)can_fail_malloc(sizeof(list_node));
    new_node->_i = i;
    new_node->_n = NULL;

    if (tail != NULL)
    {
        tail->_n = new_node;
    }

    return new_node;
}

item *search_item(list_node *head, item_key k)
{
    list_node *aux;

    for (aux = head; aux != NULL; aux = aux->_n)
    {
        if (compare_to_key(head->_i, k))
        {
            return get_current_item(aux);
        }
    }

    return NULL;
}

list_node *delete_item(list_node *head, item *i)
{
    list_node *aux;
    list_node *prev = NULL;

    if (head == NULL)
    {
        return NULL;
    }

    for (aux = head; aux != NULL; aux = aux->_n)
    {
        if (equal_items(aux->_i, i))
        {
            if (aux == head)
            {
                head = aux->_n;
            }
            else
            {
                prev->_n = aux->_n;
            }

            free_item(aux->_i);
            free(aux);
            return head;
        }

        prev = aux;
    }

    return head;
}

item *pop_item(list_node **head)
{
    list_node *aux;

    item *res = (*head)->_i;
    aux = *head;
    *head = (*head)->_n;
    free(aux);
    return res;
}

unsigned get_list_size(list_node *head)
{
    list_node *aux;
    unsigned size = 0;

    for (aux = head; aux != NULL; aux = aux->_n)
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
        aux2 = aux->_n;
        free_item(aux->_i);
        free(aux);
        aux = aux2;
    }
}

typedef struct vertex_t
{
    unsigned _id;
    list_node *_edges;
    list_node *_edges_in;
    list_node *_current;
    unsigned _visited : 1;
    unsigned _d;
    unsigned _h; /* height */
    int _e;      /* excess */
    unsigned _topkek : 1;
} vertex;

vertex *init_vertex(unsigned id)
{
    vertex *v = (vertex *)can_fail_malloc(sizeof(vertex));

    v->_id = id;
    v->_edges = NULL;
    v->_edges_in = NULL;
    v->_current = NULL;
    v->_visited = 0;
    v->_topkek = 0;
    v->_d = 0;
    v->_h = 0;
    v->_e = 0;

    return v;
}

void free_vertex(vertex *v)
{
    list_node *aux;
    list_node *next;

    if (v->_edges != NULL)
    {
        free_linked_list(v->_edges);
    }

    aux = v->_edges_in;

    while (aux != NULL)
    {
        next = aux->_n;
        free(aux);
        aux = next;
    }

    free(v);
}

void set_height_vertex(vertex *v, unsigned h)
{
    v->_h = h;
}

void set_excess_vertex(vertex *v, int e)
{
    v->_e = e;
}

void add_edge_vertex(vertex *v, item *item)
{
    v->_edges = insert_item(v->_edges, item);
}

void add_edge_in_vertex(vertex *v, item *item)
{
    v->_edges_in = insert_item(v->_edges_in, item);
}

unsigned get_height_vertex(vertex *v)
{
    return v->_h;
}

int get_excess_vertex(vertex *v)
{
    return v->_e;
}

typedef struct graph_t
{
    vertex **_vertexs;
    unsigned v_number;
    unsigned e_number;
} graph;

unsigned check_bounds(graph *g, int i1, int i2)
{
    if (i2 == -1)
    {
        return ((i1 < (int)g->v_number) && (g->_vertexs[i1] != NULL));
    }

    return ((i1 < (int)g->v_number) && (i2 < (int)g->v_number) && (g->_vertexs[i1] != NULL) &&
            (g->_vertexs[i1] != NULL));
}

graph *init_graph(unsigned V)
{
    unsigned i = 0;

    graph *res = (graph *)can_fail_malloc(sizeof(graph));
    res->_vertexs = (vertex **)can_fail_malloc(sizeof(vertex *) * V);
    res->v_number = V;
    res->e_number = 0;

    for (i = 0; i < V; i++)
    {
        res->_vertexs[i] = init_vertex(i);
    }

    return res;
}

edge *insert_edge(graph *g, unsigned from, unsigned to, unsigned c)
{
    vertex *v = g->_vertexs[from];

    if (check_bounds(g, from, to))
    {
        item *i = init_item(from, to, c);
        v->_edges = insert_item(v->_edges, i);
        g->_vertexs[to]->_edges_in = insert_item(g->_vertexs[to]->_edges_in, i);
        g->e_number++;
    }

    else
    {
        printf("%d %d\n", from + 1, to + 1);
    }

    return v->_edges->_i;
}

void remove_edge(graph *g, unsigned from, unsigned to)
{
    vertex *v = g->_vertexs[from];
    item_key *k = init_item_key(from, to);
    item *i = search_item(v->_edges, *k);

    if (check_bounds(g, from, to) && (i != NULL))
    {
        v->_edges = delete_item(v->_edges, i);
        g->e_number--;
    }

    free_item_key(k);
}

void remove_vertex(graph *g, unsigned v1)
{
    if (check_bounds(g, v1, -1))
    {
        list_node *aux = g->_vertexs[v1]->_edges;
        list_node *aux2;

        while (aux != NULL)
        {
            aux2 = aux->_n;
            remove_edge(g, v1, get_to_item(aux->_i));
            aux = aux2;
        }

        free_vertex(g->_vertexs[v1]);
        g->_vertexs[v1] = NULL;
    }
}

item *search_edge(graph *g, unsigned from, unsigned to)
{
    if (check_bounds(g, from, to))
    {
        item_key *k = init_item_key(from, to);
        item *i = search_item(g->_vertexs[from]->_edges, *k);
        free_item_key(k);

        return i;
    }

    return NULL;
}

void free_graph(graph *g)
{
    unsigned i;

    for (i = 0; i < g->v_number; i++)
    {
        if (g->_vertexs[i] != NULL)
        {
            free_vertex(g->_vertexs[i]);
        }
    }

    free(g->_vertexs);
    free(g);
}

void reset_graph(graph *g)
{
    unsigned i;
    list_node *aux;

    for (i = 0; i < g->v_number; i++)
    {
        if (g->_vertexs[i] != NULL)
        {
            g->_vertexs[i]->_e = 0;
            g->_vertexs[i]->_h = 0;

            for (aux = g->_vertexs[i]->_edges; aux != NULL; aux = aux->_n)
            {
                set_flux_item(aux->_i, 0);
            }
        }
    }
}

void transpose_graph(graph *g)
{
    unsigned i;
    list_node *aux;
    int aux2;

    for (i = 0; i < g->v_number; i++)
    {
        for (aux = g->_vertexs[i]->_edges; aux != NULL; aux = aux->_n)
        {
            aux2 = get_to_item(aux->_i);
            aux->_i->_key->_to = get_from_item(aux->_i);
            aux->_i->_key->_from = aux2;
        }

        aux = g->_vertexs[i]->_edges;
        g->_vertexs[i]->_edges = g->_vertexs[i]->_edges_in;
        g->_vertexs[i]->_edges_in = aux;
    }
}

void print_graph(graph *g)
{
    list_node *aux;
    unsigned i;

    for (i = 0; i < g->v_number; i++)
    {
        if (g->_vertexs[i] != NULL)
        {
            printf("%d ", g->_vertexs[i]->_id + 1);
            for (aux = g->_vertexs[i]->_edges; aux != NULL; aux = aux->_n)
            {
                printf("%d(c=%d f=%d) ", get_to_item(aux->_i) + 1, aux->_i->_c, aux->_i->_f);
            }

            printf("\n");
        }
    }
}

void DFS_visit(graph *g, vertex *v)
{
    list_node *edge;

    v->_visited = 1;

    if (v->_edges != NULL)
    {
        for (edge = v->_edges; edge != NULL; edge = edge->_n)
        {
            if (get_residual_capacity_item(edge->_i) != 0 && g->_vertexs[get_to_item(edge->_i)]->_visited == 0)
            {
                DFS_visit(g, g->_vertexs[get_to_item(edge->_i)]);
            }
        }

        for (edge = v->_edges_in; edge != NULL; edge = edge->_n)
        {
            if (get_residual_capacity_inverse_item(edge->_i) != 0 && g->_vertexs[get_from_item(edge->_i)]->_visited == 0)
            {
                DFS_visit(g, g->_vertexs[get_from_item(edge->_i)]);
            }
        }
    }
}

void DFS(graph *g, unsigned source)
{
    unsigned i;

    for (i = 0; i < g->v_number; i++)
    {
        if (g->_vertexs[i] != NULL)
        {
            g->_vertexs[i]->_visited = 0;
        }
    }

    DFS_visit(g, g->_vertexs[source]);
}

void initialize_preflow(graph *g, unsigned s)
{
    list_node *aux;

    reset_graph(g);
    g->_vertexs[s]->_h = g->v_number;

    for (aux = g->_vertexs[s]->_edges; aux != NULL; aux = aux->_n)
    {
        aux->_i->_f = aux->_i->_c;
        g->_vertexs[s]->_e = g->_vertexs[s]->_e - aux->_i->_c;
        g->_vertexs[get_to_item(aux->_i)]->_e = aux->_i->_c;
    }
}

void push(graph *g, edge *i, int in, list_node **head, list_node **tail, unsigned s, unsigned t)
{
    vertex *v1;
    vertex *v2;
    unsigned olde;
    unsigned d;

    if (in == 0)
    {
        v1 = g->_vertexs[get_from_item(i)];
        v2 = g->_vertexs[get_to_item(i)];

        if (v1->_e < (int)get_residual_capacity_item(i))
        {
            d = v1->_e;
        }
        else
        {
            d = get_residual_capacity_item(i);
        }

        i->_f = i->_f + d;
    }
    else
    {
        v1 = g->_vertexs[get_to_item(i)];
        v2 = g->_vertexs[get_from_item(i)];

        if (v1->_e < get_residual_capacity_inverse_item(i))
        {
            d = v1->_e;
        }
        else
        {
            d = get_residual_capacity_inverse_item(i);
        }

        i->_f = i->_f - d;
    }

    olde = v2->_e;
    v1->_e = v1->_e - d;
    v2->_e = v2->_e + d;

    if ((olde == 0) && (v2->_e != 0) && (v2->_id != s) && (v2->_id != t))
    {
        *tail = insert_item_end(init_item(v2->_id, 0, 0), *tail);

        if (*head == NULL)
        {
            *head = *tail;
        }
    }
}

void update_height_vertex(graph *g, vertex *v, int height, unsigned *labels)
{
    unsigned i;

    if (v->_h < g->v_number)
    {
        labels[v->_h]--;

        if (labels[v->_h] == 0)
        {
            for (i = 0; i < g->v_number; i++)
            {
                if ((g->_vertexs[i]->_h > v->_h) && (g->_vertexs[i]->_h < g->v_number))
                {
                    g->_vertexs[i]->_h = g->v_number + 1;
                }
            }
        }
    }

    v->_h = height;

    if (v->_h < g->v_number)
    {
        labels[v->_h]++;
    }
}

void relabel(graph *g, vertex *v, unsigned *labels)
{
    list_node *aux;
    unsigned min_h = INT_MAX;

    for (aux = v->_edges; aux != NULL; aux = aux->_n)
    {
        if ((g->_vertexs[get_to_item(aux->_i)]->_h < min_h) && (get_residual_capacity_item(aux->_i) > 0))
        {
            min_h = g->_vertexs[get_to_item(aux->_i)]->_h;
        }
    }

    for (aux = v->_edges_in; aux != NULL; aux = aux->_n)
    {
        if ((g->_vertexs[get_from_item(aux->_i)]->_h < min_h) && (get_residual_capacity_inverse_item(aux->_i) > 0))
        {
            min_h = g->_vertexs[get_from_item(aux->_i)]->_h;
        }
    }

    update_height_vertex(g, v, 1 + min_h, labels);
}

void discharge(graph *g, vertex *u, unsigned *labels, list_node **head, list_node **tail, int s, int t)
{
    vertex *v;
    int in_list = 0;

    while (u->_e > 0)
    {
        if ((u->_current != NULL) && (in_list == 0))
        {
            v = g->_vertexs[get_to_item(u->_current->_i)];
        }
        else if ((u->_current != NULL) && (in_list == 1))
        {
            v = g->_vertexs[get_from_item(u->_current->_i)];
        }
        else if ((u->_current == NULL) && (in_list == 0))
        {
            u->_current = u->_edges_in;
            v = g->_vertexs[get_from_item(u->_current->_i)];
            in_list = 1;
        }
        else
        {
            v = NULL;
        }

        if (v == NULL)
        {
            relabel(g, u, labels);
            u->_current = u->_edges;
            in_list = 0;
        }
        else if ((u->_h == v->_h + 1) && ((get_residual_capacity_item(u->_current->_i) > 0) && in_list == 0))
        {
            push(g, u->_current->_i, 0, head, tail, s, t);
        }
        else if ((u->_h == v->_h + 1) && (get_residual_capacity_inverse_item(u->_current->_i) > 0) && (in_list == 1))
        {
            push(g, u->_current->_i, 1, head, tail, s, t);
        }
        else
        {
            u->_current = u->_current->_n;
        }
    }
}

void BFS(graph *g, unsigned s)
{
    unsigned i;
    item *it;
    list_node *edge;
    list_node *fifo = NULL;
    list_node *tail = NULL;

    for (i = 0; i < g->v_number; i++)
    {
        g->_vertexs[i]->_d = 0;
    }

    tail = insert_item_end(init_item(s, 0, 0), tail);
    fifo = tail;

    while (fifo != NULL)
    {
        if (fifo == tail)
        {
            tail = NULL;
        }

        it = pop_item(&fifo);

        for (edge = g->_vertexs[get_from_item(it)]->_edges; edge != NULL; edge = edge->_n)
        {
            if ((get_to_item(edge->_i) != s) && (g->_vertexs[get_to_item(edge->_i)]->_d == 0) && (get_residual_capacity_item(edge->_i) > 0))
            {
                tail = insert_item_end(init_item(get_to_item(edge->_i), 0, 0), tail);

                if (fifo == NULL)
                {
                    fifo = tail;
                }

                g->_vertexs[get_to_item(edge->_i)]->_d = g->_vertexs[get_from_item(it)]->_d + 1;
            }
        }

        for (edge = g->_vertexs[get_from_item(it)]->_edges_in; edge != NULL; edge = edge->_n)
        {
            if ((get_from_item(edge->_i) != s) && (g->_vertexs[get_from_item(edge->_i)]->_d == 0) && (get_residual_capacity_inverse_item(edge->_i) > 0))
            {
                tail = insert_item_end(init_item(get_from_item(edge->_i), 0, 0), tail);

                if (fifo == NULL)
                {
                    fifo = tail;
                }

                g->_vertexs[get_from_item(edge->_i)]->_d = g->_vertexs[get_from_item(it)]->_d + 1;
            }
        }

        free_item(it);
    }
}

void BFS_backwards(graph *g, unsigned s)
{
    unsigned i;
    item *it;
    list_node *edge;
    list_node *fifo = NULL;
    list_node *tail = NULL;

    for (i = 0; i < g->v_number; i++)
    {
        g->_vertexs[i]->_d = 0;
    }

    tail = insert_item_end(init_item(s, 0, 0), tail);
    fifo = tail;

    while (fifo != NULL)
    {
        if (fifo == tail)
        {
            tail = NULL;
        }

        it = pop_item(&fifo);

        for (edge = g->_vertexs[get_from_item(it)]->_edges; edge != NULL; edge = edge->_n)
        {
            if ((get_to_item(edge->_i) != s) && (g->_vertexs[get_to_item(edge->_i)]->_d == 0) && (get_residual_capacity_inverse_item(edge->_i) > 0))
            {
                tail = insert_item_end(init_item(get_to_item(edge->_i), 0, 0), tail);

                if (fifo == NULL)
                {
                    fifo = tail;
                }

                g->_vertexs[get_to_item(edge->_i)]->_d = g->_vertexs[get_from_item(it)]->_d + 1;
            }
        }

        for (edge = g->_vertexs[get_from_item(it)]->_edges_in; edge != NULL; edge = edge->_n)
        {
            if ((get_from_item(edge->_i) != s) && (g->_vertexs[get_from_item(edge->_i)]->_d == 0) && (get_residual_capacity_item(edge->_i) > 0))
            {
                tail = insert_item_end(init_item(get_from_item(edge->_i), 0, 0), tail);

                if (fifo == NULL)
                {
                    fifo = tail;
                }

                g->_vertexs[get_from_item(edge->_i)]->_d = g->_vertexs[get_from_item(it)]->_d + 1;
            }
        }

        free_item(it);
    }
}

void global_relabeling(graph *g, unsigned s, unsigned t, unsigned *labels)
{
    unsigned i;

    for (i = 0; i < g->v_number; i++)
    {
        g->_vertexs[i]->_d = 0;
        g->_vertexs[i]->_topkek = 0;
    }

    BFS_backwards(g, t);

    for (i = 0; i < g->v_number; i++)
    {
        if (g->_vertexs[i]->_d != 0)
        {
            update_height_vertex(g, g->_vertexs[i], g->_vertexs[i]->_d, labels);
            g->_vertexs[i]->_topkek = 1;
        }
    }

    BFS(g, s);

    for (i = 0; i < g->v_number; i++)
    {
        if ((g->_vertexs[i]->_d != 0) && (g->_vertexs[i]->_topkek != 1))
        {
            update_height_vertex(g, g->_vertexs[i], g->_vertexs[i]->_d + g->v_number, labels);
        }
    }
}

unsigned relabel_to_front(graph *g, unsigned s, unsigned t)
{
    unsigned i;
    unsigned *labels = (unsigned *)can_fail_malloc(sizeof(unsigned) * g->v_number);
    vertex *u = NULL;
    item *it;
    list_node *head = NULL;
    list_node *tail = NULL;

    initialize_preflow(g, s);

    for (i = 0; i < g->v_number; i++)
    {
        if ((i != s) && (i != t))
        {
            g->_vertexs[i]->_current = g->_vertexs[i]->_edges;

            if (g->_vertexs[i]->_e > 0)
            {
                tail = insert_item_end(init_item(i, 0, 0), tail);

                if (head == NULL)
                {
                    head = tail;
                };
            }
        }

        labels[i] = 0;
    }

    if (head != NULL)
    {
        labels[0] = g->v_number - 1;
        it = pop_item(&head);
        u = g->_vertexs[get_from_item(it)];
        free_item(it);
    }

    for (i = 0; u != NULL; i++)
    {
        if (i % g->v_number == 0)
        {
            global_relabeling(g, s, t, labels);
        }

        discharge(g, u, labels, &head, &tail, s, t);

        if (head == NULL)
        {
            u = NULL;
        }
        else
        {
            if (head == tail)
            {
                tail = NULL;
            }

            it = pop_item(&head);
            u = g->_vertexs[get_from_item(it)];
            free_item(it);
        }
    }

    free(labels);
    free_linked_list(head);
    return g->_vertexs[t]->_e;
}

int main()
{
    unsigned x = 0;
    unsigned i;
    unsigned o, d, c;
    unsigned f, e, t;
    graph *g;
    list_node *edge;
    item **edges;
    unsigned edge_count = 0;
    i = x;
    i = 0;

    x = scanf("%u %u %u", &f, &e, &t);
    /* 
    0 - Hiper 
    1 to f - providers
    f + 1 to f + e - supply and control stations
    f + e + 1 to f + 2 * e - supply and control stations auxiliar
    f + 2 * e + 1 - source
    */
    g = init_graph(f + 2 * e + 2);

    /* Edges from source to providers */
    for (i = 0; i < f; i++)
    {
        x = scanf("%u", &c);
        insert_edge(g, f + 2 * e + 1, i + 1, c);
    }

    /* Edges from supply and control stations to auxiliars */
    for (i = 0; i < e; i++)
    {
        x = scanf("%u", &c);
        insert_edge(g, f + 1 + i, f + e + 1 + i, c);
    }

    /* Given edges, between providers and supply and control stations */
    for (i = 0; i < t; i++)
    {
        x = scanf("%u %u %u", &o, &d, &c);

        /* auxiliar to sink instead of supply and control to sink or auxiliar to supply and control station */
        if (((d == 1) || ((d > f + 1) && (d <= f + e + 1))) && (o > f + 1) && (o <= f + e + 1))
        {
            insert_edge(g, o - 1 + e, d - 1, c);
        }
        else
        {
            insert_edge(g, o - 1, d - 1, c);
        }
    }

    printf("%u\n", relabel_to_front(g, f + 2 * e + 1, 0));
    transpose_graph(g);
    DFS(g, 0);
    transpose_graph(g);

    c = 0; /* first print */
    for (i = 0; i < g->v_number; i++)
    {
        for (edge = g->_vertexs[i]->_edges; edge != NULL; edge = edge->_n)
        {
            if (((g->_vertexs[i]->_visited == 1 && g->_vertexs[get_to_item(edge->_i)]->_visited == 0 && get_residual_capacity_item(edge->_i) == 0) || (g->_vertexs[i]->_visited == 0 && g->_vertexs[get_to_item(edge->_i)]->_visited == 1 && get_residual_capacity_item(edge->_i) == 0)) && get_capacity_item(edge->_i) != 0)
            {
                /* Edge is a supply and control station to auxiliar */
                if ((g->_vertexs[i]->_id > f && g->_vertexs[i]->_id <= f + e) && (get_to_item(edge->_i) > f + e) && (get_to_item(edge->_i) <= f + 2 * e) && get_capacity_item(edge->_i) != 0)
                {
                    if (c == 0)
                    {
                        printf("%u", g->_vertexs[i]->_id + 1);
                        c = 1;
                    }

                    else
                    {
                        printf(" %u", g->_vertexs[i]->_id + 1);
                    }
                }

                /* Edge is not a supply and control station nor a provider
                Is one of the edges obtained directly from input */
                else if (g->_vertexs[i]->_id > 0 && g->_vertexs[i]->_id <= f)
                {
                    edge_count++;
                }

                /* Edge comes from an auxiliar */
                else if ((g->_vertexs[i]->_id > f + e) && (g->_vertexs[i]->_id <= f + 2 * e) && get_capacity_item(edge->_i) != 0)
                {
                    edge_count++;
                }
            }
        }
    }

    printf("\n");

    edges = (item **)can_fail_malloc(sizeof(item *) * edge_count);

    x = 0;

    for (i = 0; i < g->v_number; i++)
    {
        for (edge = g->_vertexs[i]->_edges; edge != NULL; edge = edge->_n)
        {
            if (((g->_vertexs[i]->_visited == 1 && g->_vertexs[get_to_item(edge->_i)]->_visited == 0 && get_residual_capacity_item(edge->_i) == 0) || (g->_vertexs[i]->_visited == 0 && g->_vertexs[get_to_item(edge->_i)]->_visited == 1 && get_residual_capacity_item(edge->_i) == 0)) && get_capacity_item(edge->_i) != 0)
            {
                /* Edge is not a supply and control station nor a provider
                Is one of the edges obtained directly from input */
                if (g->_vertexs[i]->_id > 0 && g->_vertexs[i]->_id <= f)
                {
                    edges[x++] = edge->_i;
                }

                /* Edge comes from an auxiliar */
                else if ((g->_vertexs[i]->_id > f + e) && (g->_vertexs[i]->_id <= f + 2 * e) && get_capacity_item(edge->_i) != 0)
                {
                    edges[x++] = edge->_i;
                }
            }
        }
    }

    if (edge_count > 0)
        merge_sort(edges, 0, edge_count - 1);

    for (i = 0; i < edge_count; i++)
    {
        if (get_from_item(edges[i]) > 0 && get_from_item(edges[i]) <= f && get_capacity_item(edges[i]) != 0)
        {
            printf("%u %u\n", get_from_item(edges[i]) + 1, get_to_item(edges[i]) + 1);
        }

        else if ((get_from_item(edges[i]) > f + e) && (get_from_item(edges[i]) <= f + 2 * e) && get_capacity_item(edges[i]) != 0)
        {
            printf("%d %d\n", g->_vertexs[get_from_item(edges[i])]->_id + 1 - e, get_to_item(edges[i]) + 1);
        }
    }

    free_graph(g);
    free(edges);
    return 0;
}