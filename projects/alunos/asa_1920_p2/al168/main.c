#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Vertex_State { UNVISITED, VISITED, CLOSED };

#define for_each_node(node, head) for(node = head; node != NULL; node = node->next)
#define id_from_coords(n, m, lin, col, dir) (2*(col - 1) + (lin - 1)*(2*m) + dir)
#define min(a,b) ((a) < (b) ? (a) : (b))

typedef struct Node {
    void* content;
    struct Node* next;
} node;

typedef struct Edge {
    int flow;
    int to_id;
} edg;

typedef struct Vertex {
    int id;
    node* edges;
    enum Vertex_State state;
} vtx;

typedef struct Graph {
    int n, m;
    vtx** vertices;
    vtx* source;
    vtx* sink;
} gph;

gph* graph;

node* new_node(void* e) {
    node* n = (node*) can_fail_malloc(sizeof(struct Node));
    n->content = e;
    n->next = NULL;
    return n;
}

void add_node(node** head, node* node) {
    if(*head == NULL){ *head = node;}
    else {
        node->next = *head;
        *head = node;
    }
}

void free_list(node* head) {
    node* tmp, *n = head;
    while (n != NULL) {
       tmp = n;
       n = n->next;
       free(tmp->content);
       free(tmp);
    }
}

vtx* new_vertex(int id) {
    vtx* v = (vtx*)can_fail_malloc(sizeof(struct Vertex));
    v->id = id;
    v->edges = NULL;
    v->state = UNVISITED;
    return v;
}

edg* new_edge(int id, int flow) {
    edg* e = can_fail_malloc(sizeof(struct Edge));
    e->flow = flow;
    e->to_id = id;
    return e;
}

void add_edge(vtx* v, edg* e) {
    add_node(&v->edges, new_node((void*)e));
}

void connect_source(gph* g, int id) {
    add_edge(g->source, new_edge(id, 0));
    add_edge(g->vertices[id], new_edge(g->source->id, 1));
}

void connect_sink(gph* g, int id) {
    add_edge(g->vertices[id], new_edge(g->sink->id, 0));
}

void free_vertex(vtx* v) {
    free_list(v->edges);
    free(v);
}
void free_graph(gph* g) {
    int i, n = 2*g->n*g->m;
    for(i = 0; i < n; i++)
        free_vertex(g->vertices[i]);
    free(g->sink);
    free(g->source);
    free(g);
}

gph* new_graph(int n, int m) {
    gph* g = can_fail_malloc(sizeof(struct Graph));
    int id_1, id_2;
    int i, j;

    g->m = m;
    g->n = n;

    g->vertices = can_fail_malloc(sizeof(struct Vertex*)*(2*n*m + 2));

    for(i = 1; i <= n; i++) {
        for(j = 1; j <= m; j++){
            id_1 = id_from_coords(n, m, i, j, 0);
            id_2 = id_from_coords(n, m, i, j, 1);

            g->vertices[id_1] = new_vertex(id_1);
            g->vertices[id_2] = new_vertex(id_2);

            add_edge(g->vertices[id_1], new_edge(id_2, 0));
            add_edge(g->vertices[id_2], new_edge(id_1, 1));

            if(j != 1) {
                add_edge(g->vertices[id_2], new_edge(id_from_coords(n, m, i, j - 1, 0), 0));
                add_edge(g->vertices[id_1], new_edge(id_from_coords(n, m, i, j - 1, 1), 1));
            }
            if(j != m) {
                add_edge(g->vertices[id_1], new_edge(id_from_coords(n, m, i, j + 1, 1), 1));
                add_edge(g->vertices[id_2], new_edge(id_from_coords(n, m, i, j + 1, 0), 0));
            }
            if(i != 1) {
                add_edge(g->vertices[id_1], new_edge(id_from_coords(n, m, i - 1, j, 1), 1));
                add_edge(g->vertices[id_2], new_edge(id_from_coords(n, m, i - 1, j, 0), 0));
            }
            if(i != n) {
                add_edge(g->vertices[id_1], new_edge(id_from_coords(n, m, i + 1, j, 1), 1));
                add_edge(g->vertices[id_2], new_edge(id_from_coords(n, m, i + 1, j, 0), 0));
            }
        }
    }

    id_1 = 2*n*m;
    id_2 = 2*n*m + 1;

    g->sink = new_vertex(id_1);
    g->source = new_vertex(id_2);

    g->vertices[id_1] = g->sink;
    g->vertices[id_2] = g->source;

    return g;
}

int is_head(vtx* v, int id) {
    edg* e = (edg*)v->edges->content;
    if(e != NULL && e->to_id == id) return 1;
    else return 0;
}

void empty_residual_edge(vtx* vertex, int id) {
    node* node;
    for_each_node(node, vertex->edges) {
        edg* edge = (edg*) node->content;
        if (edge->to_id == id) edge->flow = 0;
    }
}

int dfs(vtx* source, vtx* sink) {
    node* node;
    /* notify graph if sink has been reached */
    if (source->id == sink->id) {
        return 1;
    } else {
        /* if this is normal vtx, mark as visited or return */
        if (source->state == VISITED) return 0;
        source->state = VISITED;

        /* entering recursive wonderland */
        for_each_node(node, source->edges) { /* see loop definition */
            edg* edge = (edg*) node->content;

            /* if there is no flow, visit other edgesqq */
            if (edge->flow == 0) {
                vtx* next_vtx = graph->vertices[edge->to_id];
                if(dfs(next_vtx, sink)){/* if the path has been found */

                    /*put flow in edge */
                    edge->flow = 1;
                    /* empty residual edge */
                    empty_residual_edge(next_vtx, source->id);
                    /* leave */
                    return 1;
                }
            }
        }
    }
    return 0;
}

int ford_fulkerson(int max_flow, int n, int m) {
    int i, flow = 0;

    while(dfs(graph->source, graph->sink)) {
        flow++;
        if (flow == max_flow) return flow;

        /* dar reset aos vertices */
        graph->source->state = UNVISITED;
        for (i = 0; i < 2*n*m; i++)
            graph->vertices[i]->state = UNVISITED;
    }
    return flow;
}

int main() {
    int n, m;
    int s, c;
    int i, id;
    int lin, col;

    scanf("%d %d", &m, &n);
    scanf("%d %d", &s, &c);

    if(m == 0 || n == 0 || s == 0 || c == 0) { printf("0\n"); return 0; }

    graph = new_graph(n, m);

    for(i = 0; i < s; i++) {
        scanf("%d %d", &col, &lin);
        id = id_from_coords(n, m, lin, col, 1);
        if(!is_head(graph->vertices[id], graph->sink->id))
            connect_sink(graph, id);
    }
    for(i = 0; i < c; i++) {
        scanf("%d %d", &col, &lin);
        id = id_from_coords(n, m, lin, col, 0);
        if(!is_head(graph->vertices[id], graph->source->id))
            connect_source(graph, id);
    }

    printf("%d\n",ford_fulkerson(min(s,c), n, m));

    free_graph(graph);

    return 0;
}
