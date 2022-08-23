#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define PERSON 2
#define SUPERMARKET 3
#define BOTH 4
#define NONE 5

typedef struct vertex {
    int id, type;
} Vertex;

typedef struct node {
    Vertex *vertex;
    struct node *next;
} Node;

typedef struct list {
    Node *head, *tail;
} List;

typedef struct int_number {
    int i;
    struct int_number *next;
} Int;

typedef struct queue {
    Int *head, *tail;
} Queue;

typedef struct edge {
    int capacity;
    int to;
    struct edge *next;
} Edge;

typedef struct edgeList {
    Edge *head, *tail;
} EdgeList;

int maxFlow = 0;

List* newList() {
    List *l= (List*) malloc(sizeof(List));
    l->head = l->tail = NULL;
    return l;
}

EdgeList* newEdgeList() {
    EdgeList *l= (EdgeList*) malloc(sizeof(EdgeList));
    l->head = l->tail = NULL;
    return l;
}

void addVertex(List *l, Vertex *v) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->vertex = v;
    if (l->head == NULL){
        l->head = l->tail = node;
        node->next = NULL;
        return;
    }
    l->tail->next = node;
    l->tail = node;
    node->next = NULL;
}

void freeList(List *l) {
    Node *n = l->head;
    Node *aux;

    while(n != NULL){
        aux = n->next;
        free(n);
        n = aux;
    }
    free(l); 
}

void freeGraph(List** graph, int graphSize) {
    int i;
    for (i = 0; i < graphSize; i++)
        free(graph[i]->head->vertex);
    for (i = 0; i < graphSize; i++)
        freeList(graph[i]);
    free(graph);
}

List** initGraph(int graphSize) {
    int i, c = 0, x = 0;
    List **list = (List**) malloc(sizeof(List*) * graphSize);
    for (i = 0; i < graphSize; i++) {
        list[i] = newList();
    }

    Vertex *source = (Vertex*) malloc(sizeof(Vertex));
    Vertex *sink = (Vertex*) malloc(sizeof(Vertex));
    source->id = c++; sink->id = c++;
    source->type = sink->type = NONE;
    addVertex(list[x++], source); addVertex(list[x++], sink);

    for (i = 0; i < (graphSize - 2)/2; i++) {
        Vertex *v_in = (Vertex*) malloc(sizeof(Vertex));
        Vertex *v_out = (Vertex*) malloc(sizeof(Vertex));
        v_in->id = c++; v_out->id = c++;
        v_in->type = v_out->type = NONE;
        addVertex(list[x], v_in);
        addVertex(list[x++], v_out); /* adiciona o v_out aos vizinhos de v_in */
        addVertex(list[x++], v_out);
    }
    return list;        
}

void processPositions(int numSupermarkets, int numPeople, int numStreets, List **graph) {
    int i, x, y, s;
    int n = numSupermarkets + numPeople;
    for (i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        s = 2 * numStreets * (x - 1) + 2 * y;
        if (i < numSupermarkets) {
            graph[s++]->head->vertex->type = SUPERMARKET;
            graph[s]->head->vertex->type = SUPERMARKET;
        }
        else {
            if (graph[s]->head->vertex->type == SUPERMARKET) {
                graph[s++]->head->vertex->type = BOTH;
                graph[s]->head->vertex->type = BOTH;
            }
            else if (graph[s]->head->vertex->type != BOTH) {
                graph[s++]->head->vertex->type = PERSON;
                graph[s]->head->vertex->type = PERSON;
            }
        }
    }
}

void addNeighbors(List** graph, int graphSize, int numStreets) {
    int i, x;
    for (i = 0; i < graphSize; i++) {
        if (graph[i]->head->vertex->type == PERSON) {
            addVertex(graph[0], graph[i]->head->vertex);
            i++; /* passa o v_out a frente */
        }
    }
    for (i = 3; i < graphSize; i += 2) {
        int type = graph[i]->head->vertex->type;
        if (type == SUPERMARKET)
            addVertex(graph[i], graph[1]->head->vertex);
        else if (type == BOTH)
            maxFlow++;
        else {
            x = i - (2 * numStreets + 1); /* lado esquerdo */
            if (x >= 2 && graph[x]->head->vertex->type != BOTH)
                addVertex(graph[i], graph[x]->head->vertex);

            x = i + (2 * numStreets - 1);  /* lado direito */
            if (x < graphSize && graph[x]->head->vertex->type != BOTH)
                addVertex(graph[i], graph[x]->head->vertex);

            x = i - 3;                     /* cima */ 
            if (x < numStreets*2 && x >= 2 && graph[x]->head->vertex->type != BOTH)
                addVertex(graph[i], graph[x]->head->vertex);    
            else if (x >= numStreets*2 && x%(numStreets*2) != 0 && graph[x]->head->vertex->type != BOTH)
                addVertex(graph[i], graph[x]->head->vertex);

            x = i + 1;                      /* baixo */
            if (x <= numStreets*2 && graph[x]->head->vertex->type != BOTH)
                addVertex(graph[i], graph[x]->head->vertex);
            else if (x < graphSize && x > numStreets*2 && (i - 1)%(numStreets*2) != 0 && graph[x]->head->vertex->type != BOTH)
                addVertex(graph[i], graph[x]->head->vertex);
        }
    }
}

void addEdge(EdgeList *list, int v, int capacity) {
    Edge *edge = (Edge*) malloc(sizeof(Edge));
    edge->to = v;
    edge->capacity = capacity;
    if (list->head == NULL){
        list->head = list->tail = edge;
        edge->next = NULL;
        return;
    }
    list->tail->next = edge;
    list->tail = edge;
    edge->next = NULL;
}

void freeEdgeList(EdgeList *l) {
    Edge *e = l->head;
    Edge *aux;

    while(e != NULL){
        aux = e->next;
        free(e);
        e = aux;
    }
    free(l);    
}

void freeEdges(EdgeList **edges, int graphSize) {
    int i;
    for (i = 0; i < graphSize; i++)
        freeEdgeList(edges[i]);
    free(edges);
}

EdgeList** createEdges(List** graph, int graphSize) {
    int i;
    Node *aux;
    EdgeList **list = (EdgeList**) malloc(sizeof(EdgeList*) * graphSize);
    for (i = 0; i < graphSize; i++) {
        list[i] = newEdgeList();
    }
    for (i = 0; i < graphSize; i++) {
        aux = graph[i]->head->next;
        while (aux != NULL) {
            addEdge(list[i], aux->vertex->id, 1);
            aux = aux->next;
        }
    }
    return list;
}

void push(Queue *queue, int i) {
    Int *number = (Int*) malloc(sizeof(Int));
    number->i = i;
    number->next = NULL;
    if (queue->head == NULL) {
        queue->head = queue->tail = number;
        return;
    }
    queue->tail->next = number;
    queue->tail = number;
}

int pop(Queue *queue) {
    Int *aux = queue->head;
    queue->head = queue->head->next;
    int i = aux->i;
    free(aux);
    return i;
} 

void freeQueue(Queue *queue) {
    Int *i = queue->head;
    Int *aux;
    while (i != NULL) {
        aux = i->next;
        free(i);
        i = aux;
    }
    free(queue);
}

int emptyQueue(Queue *queue) {
    return queue->head == NULL;
}

int min(int n_one, int n_two) {
    if (n_one <= n_two)
        return n_one;
    return n_two;
}

void setVector(int *vector, int value, int size) {
    int i;
    for (i = 0; i < size; i++)
        vector[i] = value; 
}

int bfs(int startNode, int endNode, EdgeList **edges, int *parentsList, int *currentPathCapacity, int graphSize) {
    setVector(parentsList, -1, graphSize);
    setVector(currentPathCapacity, 0, graphSize);
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    queue->head = queue->tail = NULL;
    push(queue, startNode);

    parentsList[startNode] = -2;
    currentPathCapacity[startNode] = 999;

    while (!emptyQueue(queue)) {
        Edge *edge;
        int currentNodeId = pop(queue);
        edge = edges[currentNodeId]->head;
        while (edge != NULL) {
            int to = edge->to;
            if (parentsList[to] == -1) {
                if(edge->capacity > 0) {
                    parentsList[to] = currentNodeId;
                    currentPathCapacity[to] = min(currentPathCapacity[currentNodeId], edge->capacity);
                    if (to == endNode) {
                        freeQueue(queue);
                        return currentPathCapacity[endNode];
                    }
                    push(queue, to);
                }
            }
            edge = edge->next;
        }
    }
    freeQueue(queue);
    return 0;
}

void addCapacity(int u, int v, int flow, EdgeList **edges) {
    Edge *aux = edges[u]->head;
    while (aux != NULL) {
        if (aux->to == v) {
            aux->capacity += flow;
            return;
        }
        aux = aux->next;
    }
    addEdge(edges[u], v, flow);
}

int edmondsKarp(int startNode, int endNode, EdgeList **edges, int graphSize) {
    int maxFlow = 0;
    int *parentsList = (int*) malloc(sizeof(int) * graphSize);
    int *currentPathCapacity = (int*) malloc(sizeof(int) * graphSize);;
    while (TRUE) {
        int flow = bfs(startNode, endNode, edges, parentsList, currentPathCapacity, graphSize);
        if (flow == 0) {
            break;
        }
        maxFlow += flow;
        int currentNode = endNode;
        while (currentNode != startNode) {
            int previousNode = parentsList[currentNode];
            addCapacity(previousNode, currentNode, -flow, edges);
            addCapacity(currentNode, previousNode, flow, edges);
            currentNode = previousNode;
        }   
    }
    free(parentsList);
    free(currentPathCapacity);
    return maxFlow;
}

int main() {
    int numAvenues, numStreets, numSupermarkets, numPeople;  
    scanf("%d %d %d %d", &numAvenues, &numStreets, &numSupermarkets, &numPeople);
    int graphSize = 2 * numAvenues * numStreets + 2;
    
    List **graph = initGraph(graphSize);
    processPositions(numSupermarkets, numPeople, numStreets, graph);
    addNeighbors(graph, graphSize, numStreets);
    
    EdgeList **edges = createEdges(graph, graphSize);
    freeGraph(graph, graphSize);
    maxFlow += edmondsKarp(0, 1, edges, graphSize);
    printf("%d\n", maxFlow);
    freeEdges(edges, graphSize);
    
    return 0;
}