/*  2º Projeto - ASA 2019/20
    António Lopes- 89415
    Pedro Galhardo - 89517    */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int C = 0;                  /* número de cidadaos */
int S = 0;                  /* número de supermercados */
int M = 0;                  /* número de avenidas (vertical) */
int N = 0;                  /* número de ruas (horizontal) */
int V = 0;                  /* número de vértices */


typedef struct queue queue;
typedef struct element element;
typedef struct node *link;


struct element { /*queue element*/ 
    int data;
    element *next;
};

struct queue {  /*queue structure*/
    int count;
    element *front;
    element *rear;
};

struct node { /*graph vertex*/
    int n;
    int flow;
    link next;
};


void initializeQueue(queue *q) { /*initialize the queue*/
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

int isQueueEmpty(queue *q) { /*returns 1 if there are no elements in the queue*/
    return (q->rear == NULL);
}

void enQueue(queue *q, int value) { /*adds elements to the queue the end*/
    element *tmp;
    tmp = malloc(sizeof(element));

    tmp->data = value;
    tmp->next = NULL;
    
    if(!isQueueEmpty(q)) {
        q->rear->next = tmp;
        q->rear = tmp;
    }

    else {
        q->front = tmp; 
        q->rear = tmp;
    }
    
    q->count++;
}

int deQueue(queue *q) { /*removes and frees first element of the queue*/
    int n;
    element *tmp;
    n = q->front->data;
    
    tmp = q->front;
    q->front = q->front->next;
    
    q->count--;
    if (q->count == 0) {
        q->rear = NULL;
    }
    free(tmp);
    return n;
}


int getN(int av, int st) {  /*calculates number of vertex depending on position on graph*/
    return (((av + (st-1) * M) * 2) - 1);
}

void getCoords(int n, int *av, int *st) { /*calculates street and avenue depending on vertex number*/
    *av = ((n + 1) % (M * 2)) / 2;
    *st = ((n + 1) / (M * 2));

    if (*av == 0)
        *av = M;
    else
        (*st)++;
}

void getNeighbours(int node, int neighbours[]) { /*lists all vertex neighbours*/
    int i, av, st;

    getCoords(node, &av, &st);

    for (i = 0; i < 4; i++) {
        if (i == 0 && (av + 1) <= M)
            neighbours[i] = node + 1;
        else if (i == 1 && (av - 1) > 0)
            neighbours[i] = node - 3;
        else if (i == 2 && (st + 1) <= N)
            neighbours[i] = node + ((M * 2) - 1);
        else if (i == 3 && (st - 1) > 0)
            neighbours[i] = node - ((M * 2) + 1);
        else
            neighbours[i] = 0;
    }
}


link createLink(int n, int flow) { /*creates link to graph vertex with flow from another vertex to this one*/
    link l;
    l = malloc(sizeof(struct node));
    l->n = n;
    l->flow = flow;
    l->next = NULL;
    return l;
}

link lastLink(link* G, int n) { /*returns last link of the vertex n*/
    link m;
    m = G[n];
    while (m->next != NULL) {
        m = m->next; 
    }
    return m;
}

link findLink(link* G, int n, int find) { /*returns link of vertex n to vertex find*/
    link m;
    m = G[n];
    while (m != NULL && m->n != find) {
        m = m->next; 
    }
    
    return m;
}


link* initializeGraph() {   /*prepares the graph, initializes flows and connections and reads the remaining input*/
    int i, j, node, av, st;
    link* G;
    int neighbours[4];
    link m, n;
    

    G = malloc(V * sizeof(link));
    for (i = 0; i < V; i++) {
        G[i] = malloc(sizeof(struct node));
        G[i]->n = i;
        G[i]->next = NULL;
    }

    for (i = 1; i < V-2; i += 2) {
        n = malloc(sizeof(struct node));
        n->n = i+1;
        n->flow = 1;
        n->next = NULL;
        G[i]->next = n;
    }

    for (i = 2; i < V-1; i += 2) {
        getNeighbours(i, neighbours);
        m = G[i];
        for(j = 0; j < 4; j++) {
            if (neighbours[j] != 0) {
                n = malloc(sizeof(struct node));
                n->n = neighbours[j];
                n->flow = 1;
                n->next = NULL;
                m->next = n;
                m = m->next;
            }
        }
    }

    for (i = 0; i < S; i++) {
        scanf("%d %d", &av, &st);

        node = getN(av, st) + 1;
        m = lastLink(G, node);
        n = malloc(sizeof(struct node));
        n->n = V-1;
        n->flow = 1;
        n->next = NULL;
        m->next = n;
    }

    for (i = 0; i < C; i++) {
        scanf("%d %d", &av, &st);

        node = getN(av, st);
        m = lastLink(G, 0);
        n = malloc(sizeof(struct node));
        n->n = node;
        n->flow = 1;
        n->next = NULL;
        m->next = n;
    }
    return G;
}


int bfs(link *G, int s, int t, int parent[]) { /*visiting algorithm*/
    int i, u;
    int* visited;
    link l;
    queue *q;
    q = malloc(sizeof(queue));
    visited = malloc(V*sizeof(int));
    /*array that marks vertexes as visited when added to queue*/
    for (i = 0; i < V; i++)
        visited[i] = 0;
    
    initializeQueue(q);
    /*adds source to queue as first node*/
    enQueue(q, s);
    visited[s] = 1;
    parent[s] = -1;


    while(!isQueueEmpty(q)) {
        u = deQueue(q);
        l = G[u]->next;
        while (l != NULL) {
            /*adds vertexes that haven't been visited and that you can reach from where you're at*/
            if (visited[l->n] == 0 && l != NULL && l->flow > 0) {
                enQueue(q, l->n);
                parent[l->n] = u;
                visited[l->n] = 1;
            }
            l = l->next;
        }
    }

    free(q);

    if(visited[t] == 1) {
        free(visited);
        return 1;
    }
    else {
        free(visited);
        return 0;
    }
}

int edmondsKarp(link *G, int s, int t) { /*runs the bfs algorithm and updates the graphs and flows*/
    int u, v;
    int maxFlow = 0;
    link l, m;
    int* parent;
    parent = malloc(V*sizeof(int));

    while (bfs(G, s, t, parent)) { /*if bfs finds a solution*/
        for (v = t; v != s; v = parent[v]) { /*updates flows from parent array*/
            u = parent[v];
            l = findLink(G, u, v);
            l->flow -= 1;
            l = findLink(G, v, u);
            if (l == NULL) {
                l = createLink(u, 0);
                m = lastLink(G, v);
                m->next = l;
            }
            l->flow += 1;
        }

        maxFlow += 1;
        if (maxFlow == S || maxFlow == C) {
            return maxFlow;
        }
    }

    return maxFlow;
}


int main() {
    link *graph;

    scanf("%d %d", &M, &N);
    scanf("%d %d", &S, &C);
    V = (2 * (M * N)) + 2;
    
    graph = initializeGraph();

    printf("%d\n", edmondsKarp(graph, 0, V-1));

    return 0;
}