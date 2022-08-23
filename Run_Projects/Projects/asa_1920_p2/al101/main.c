/* Miguel Gonçalves Jardim */

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE !(FALSE)

#define INFINITY 9

struct node;
typedef struct node* link;

typedef struct node {
    struct node* next;
    int value;
} node;

struct vertice;
typedef struct vertice* edge;

typedef struct vertice {
    struct vertice* next;
    int id;
    int cap;
} vertice;

typedef struct queue {
    node* head;
    node* tail;
} queue;

typedef struct list {
    vertice* head;
    vertice* tail;
} list;

int *parentsList;       
int *currentPathCapacity;

/* Vector of adjancency list */
list** adj;

/* Total number of vertices in graph G' */
int g;

int min(int a, int b) {
    return a < b ? a:b;
}

list* newList() {
    list* new = (list*) malloc(sizeof(list));
    new->head = new->tail = NULL;
    return new;
}

void deleteList(list* l) {
    if (l->head == NULL) free(l);
    else {
        edge current = l->head;
        l->head = l->head->next;
        free(current);
        deleteList(l);
    }
}

void addEdge(int from, int to, int cap) {
    list* adjList = adj[from];

    edge new = (edge) malloc(sizeof(vertice));
    new->next = NULL;
    new->id = to;
    new->cap = cap;
    
    if (adjList->head == NULL) {
        adjList->head = adjList->tail = new;
    }
    else {
        adjList->tail->next = new;
        adjList->tail = new;
    }
}

queue* newQueue() {
    queue* q = (queue*) malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;

    return q;
}

void deleteQueue(queue* q) {
    link prev = q->head;
    link next = prev;
    while (next != NULL) {
        next = prev->next;
        free(prev);
        prev = next;
    }
    free(q);
}

void push(queue* q, int value) {

    if (q == NULL) {
        q = newQueue();
    }

    link new = (link) malloc(sizeof(node));
    new->value = value;
    new->next = NULL;
    if (q->head == NULL) {
        q->head = q->tail = new;
    }
    else {
        q->tail->next = new;
        q->tail = new;
    }
}

int pop(queue* q) {
    if (q == NULL || q->head == NULL) {
        return -1;
    }
    else if (q->head == q->tail) {
        int value = q->head->value;
        free(q->head);
        q->head = q->tail = NULL;

        return value;
    }
    else {
        int value = q->head->value;
        link old = q->head;
        q->head = q->head->next;
        free(old);
        return value;
    }
}

int isEmpty(queue* q) {
    return q->head == NULL;
}

void deleteAll() {
    
    int i;

    for (i = 0; i < g; i++) {
        deleteList(adj[i]);
    }
    free(adj);

    free(parentsList);
    free(currentPathCapacity);
}

void processInput() {

    int m, n, s, c;
    scanf("%d %d %d %d", &m, &n, &s, &c);

    g = m*n*2 + 2;

    adj = (list**) malloc(sizeof(list*) * g);

    int i;
    for (i = 0; i < g; i++) {
        adj[i] = newList();
    }

    /* Edges from supermarket to source */
    for (i = 0; i < s; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(0, 1 + m*2*(y-1) + 2*(x - 1), 1);
    }

    /* Edges from citizen to sink */
    for (i = 0; i < c; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(1 + m*2*(y-1) + 2*(x - 1) + 1, g - 1, 1);
    }

    /* Edges between Vin and Vout */
    for (i = 1; i < g - 2; i+=2) {
        addEdge(i, i+1, 1);
    }

    /* Edges from each vertice to it's neighbours */
    for (i = 2; i < g - 1; i += 2) {
        /* Right */
        if (i % (2 * m) != 0 ) {
            addEdge(i, i + 1, 1);
        }
        /* Left */
        if ((i - 2) % (2 * m) != 0) {
            addEdge(i, i - 3, 1);
        }
        /* Up */
        if (i - (2 * m) > 0) {
            addEdge(i, i - (2 * m) - 1, 1);
        }
        /* Down */
        if (i + (2 * m) < g - 1) {
            addEdge(i, i + (2 * m) - 1, 1);
        }
    }
}

/* Edmonds Karp and bfs algorythm's adapted from https://sahebg.github.io/computersceince/maximum-flow-edmond-karp-algorithm-c-program-example/ */
int bfs(int startNode, int endNode) {

    int i;

    for (i = 0; i < g; i++) {
        parentsList[i] = -1;
        currentPathCapacity[i] = 0;
    }

    queue* q = newQueue();

    push(q, startNode);

    parentsList[startNode] = INFINITY;

    currentPathCapacity[startNode] = INFINITY;

    while(!isEmpty(q)) {

        int currentNode = pop(q);
        
        edge current = adj[currentNode]->head;
        while (current != NULL) {

            int to = current->id;

            if(parentsList[to] == -1) {

                if(current->cap == 1) {
                    
                    parentsList[to] = currentNode;
                    currentPathCapacity[to] = min(currentPathCapacity[currentNode], current->cap);

                    if(to == endNode) {
                        deleteQueue(q);
                        return currentPathCapacity[endNode];
                    }
                    push(q, to);
                }
            }
            current = current->next;
        }
    }

    deleteQueue(q);
    return 0;
}

int edmondsKarp(int startNode, int endNode) {

    int maxFlow = 0;

    parentsList = (int*) malloc(sizeof(int) * g);
    currentPathCapacity = (int*) malloc(sizeof(int) * g);

    while(TRUE){

        int flow = bfs(startNode, endNode);

        if (flow == 0) {
            break;
        }

        maxFlow += flow;

        int currentNode = endNode;

        while(currentNode != startNode) {
            int previousNode = parentsList[currentNode];

            edge head = adj[previousNode]->head;
            while (head != NULL) {
                if (head->id == currentNode) {
                    head->cap -= flow;
                    break;
                }
                head = head->next;
            }

            int done = FALSE;
            head = adj[currentNode]->head;
            while (head != NULL) {
                if (head->id == previousNode) {
                    head->cap += flow;
                    done = TRUE;
                    break;
                }
                head = head->next;
            }
            if (done == FALSE) {
                /* residual network edges are only added when they are needed */
                addEdge(currentNode, previousNode, flow);
            }
            
            currentNode = previousNode;
        }

    }

    return maxFlow;
}

int main() {
    processInput();

    printf("%d\n", edmondsKarp(0, g-1));

    deleteAll();

    return 0;
}