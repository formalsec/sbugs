#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INFINITY 1


/* ------------ LINKEDLIST ------------ */
    /* Structures */

typedef struct node
{
    struct node *next;
    int value;
} node;


typedef struct linkedList {

    node *head;
} LinkedList;

    /* Functions */

void initList(LinkedList *list)
{
    /* Initialization of the list as a empty list */
    list->head = NULL;
}

int pop(LinkedList *list) {
    /* Removes the first element in the list */
    node *removedElement;
    int value;

    if (list->head == NULL)
        return -1;

    /* Store locally the fist element so it can be freed */
    removedElement = list->head;
    value = removedElement->value;

    /* Update list head */
    list->head = list->head->next;

    free(removedElement);
    return value;
}

void push(LinkedList *list, int value) {
    /* Adds a new element to the begining of the list */
    node *newNode;

    /* Allocate memory */
    newNode = (node*) can_fail_malloc(sizeof(node));

    /* Define newNode */
    newNode->value = value;
    newNode->next = list->head;
    
    list->head = newNode;

}

void destroyList(LinkedList *list) {
    /* Frees all the memory associated with the list */
    node *node_, *nextNode;

    node_ = list->head;

    while(node_ != NULL) {
        nextNode = node_->next;
        free(node_);
        node_ = nextNode;
    }
}

int isEmpty(LinkedList list) {
    if (list.head == NULL)
        return 1;
    else
        return 0;
}



/* ------------ GRAPH ------------ */
    /* Structure */

typedef struct graph {
    /* Graph representation with adjency list */

    int vertices, edges;
    LinkedList *outGoingEdges;
} Graph;

    /* Functions */

void initGraph(Graph *graph, int vertices, int edges) {
    /* Initialization of the graph properties */
    int i;

    graph->vertices = vertices;
    graph->edges = edges;

    graph->outGoingEdges = (LinkedList *) can_fail_malloc(sizeof(LinkedList) * vertices);

    for (i = 0; i < vertices; i++) {
        initList(&(graph->outGoingEdges[i]));
    }
}

LinkedList getAdj(Graph graph, int vertice) {
    return graph.outGoingEdges[vertice];
}

int* getSources(Graph graph, int *numSources) {
    /* Gets all vertices that are sources */
    int i;

    /* numIncomingEdges[v] = number of incoming edges of v */
    int *numIncomingEdges = (int*) can_fail_malloc(sizeof(int) * graph.vertices);

    *numSources = graph.vertices;
    LinkedList adjencies;
    node *adjVertice;

    /* Calculate the number of incoming edges for all vertices */
    for (i = 0; i < graph.vertices; i++) {

        adjencies = getAdj(graph, i);
        adjVertice = adjencies.head;
        
        for (; adjVertice != NULL; adjVertice = adjVertice->next) {

            if (numIncomingEdges[adjVertice->value] == 0) {
                /* The vertice adjacent vertice is not a source (was a income edge) */
                (*numSources)--;
            }
            
            numIncomingEdges[adjVertice->value]++;
        }
    }

    /* Check which vertices are sources  */
    int sourceIndex = 0;
    int *sources = (int*) can_fail_malloc(sizeof(int) * (*numSources));

    for (i = 0; sourceIndex < (*numSources); i++) {
        if (numIncomingEdges[i] == 0) {
            sources[sourceIndex] = i;
            sourceIndex++;
        }
    }

    free(numIncomingEdges); 
    return sources;
}


void destroyGraph(Graph *graph) {
    /* Frees the memory associated with the graph */
    int i;
    
    for (i = 0; i < graph->vertices; i++){
        destroyList(&(graph->outGoingEdges[i]));
    }    

    free(graph->outGoingEdges);
}



/* ------------ MAIN ------------ */

void processInput(Graph *graph) {
    
    int vertices, edges, i;
    scanf("%d %d", &vertices, &edges);

    initGraph(graph, vertices, edges);

    for (i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        push(&(graph->outGoingEdges[u - 1]), v - 1);
    }

}

int calculateLargestPath(Graph graph, int *sources, int sourcesSize) {
    /* Calculates the overall largest path in the hole graph */
    int i;

    /* DEBUG : int time = 0; */
    
    /* color[v] = State of vertice v:
        - WHITE : Not visited
        - GRAY : Being processed
        - BLACK : Processed
    */
    char *color = (char*) can_fail_malloc(sizeof(char) * graph.vertices);

    /* longestPath[v] = longest path from v */
    int *longestPath = (int*) can_fail_malloc(sizeof(int) * graph.vertices);

    /* Current vertice that is being process */
    int visitingVertice;
    
    /* visitingVertice adjacencies */
    LinkedList adj;
    node *adjVertice;

    /* Longest path between all adjacencies */
    int longestAdjPath;


    LinkedList stack;
    initList(&stack);

    /* Setup, all vertices start:
        - Unvisited (color = white)
        - Longest Path = -Infinity 
    */
    for (i = 0; i < graph.vertices; i++) {
         color[i] = WHITE;
         longestPath[i] = -INFINITY;
    }

    /* For each source do a modified DFS to calculate 
       the largest path from source to all the reachable 
       vertices 
    */
    for (i = 0; i < sourcesSize; i++) {
        /* Insert the starting vertice in the stack */
        push(&stack, sources[i]);
        
        while (isEmpty(stack) != TRUE) {
            visitingVertice = stack.head->value;

            if (color[visitingVertice] == WHITE) {
                /* Vertice wasnt visited yet so visit it */
                
                /* DEBUG : printf("Node = %d -> Init Time = %d\n", visitingVertice + 1, ++time); */
                color[visitingVertice] = GRAY;

                adj = getAdj(graph, visitingVertice);
                for (adjVertice = adj.head; adjVertice != NULL; adjVertice = adjVertice->next) {
                    if (color[adjVertice->value] == WHITE) 
                        push(&stack, adjVertice->value);
                }

            } else {
                /* Vertice was completely visited so calculate 
                   finish it and calculate the largest path */
                   
                visitingVertice = pop(&stack);
                if (color[visitingVertice] == GRAY) {
                    /* DEBUG : printf("Node = %d -> End Time = %d\n", visitingVertice + 1, ++time); */
                    color[visitingVertice] = BLACK;

                    /* Calculate the finished vertice longest path
                        Vertice is black => All of his childs where 
                        processed */
                    adj = getAdj(graph, visitingVertice);

                    /* Is a sink => LongestPath from a sink = 0 */
                    if (isEmpty(adj)) 
                        longestPath[visitingVertice] = 1;
                    
                    /* Check which adjacent vertice was the highest longestPath so 
                        the visitingVertice longestPath his child biggest path + 1 */
                    longestAdjPath = -INFINITY;
                    for (adjVertice = adj.head; adjVertice != NULL; adjVertice = adjVertice->next) {
                        if (longestPath[adjVertice->value] > longestAdjPath)
                            longestAdjPath = longestPath[adjVertice->value];
                    }

                    /* Set the visiting vertice longestPath */
                    longestPath[visitingVertice] = longestAdjPath + 1;
                }
    
            }             
        }
    }

    /* Check which source has the biggest largest path */
    int overallLongestPath = - INFINITY;
    for (i = 0; i < sourcesSize; i++) {
        if (overallLongestPath < longestPath[sources[i]])
            overallLongestPath = longestPath[sources[i]];
    }

    free(color);
    free(longestPath);

    return overallLongestPath + 1;  
}


int main() {
    
    int k, l;
    
    Graph graph;
    int *sources;  
    
    processInput(&graph);
    sources = getSources(graph, &k);

    l = calculateLargestPath(graph, sources, k);
    printf("%d %d\n", k, l);

    destroyGraph(&graph);
    free(sources);
    return 0;   
}