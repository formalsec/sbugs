#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

/* To compile:  g++ -O3 -Wall -Wextra -Werror -pedantic -o proj project2.1.c -lm */

/**
 * ======================================================================= 
 * ============================[[ Constants ]]============================
 * =======================================================================aa
 */
#define X -1
#define Y -2
#define TRUE 1
#define FALSE 0

/**
 * ======================================================================= 
 * =============================[[ Structs ]]=============================
 * =======================================================================
 */
typedef struct fifoStruct *FIFO;
typedef struct stackStruct *Stack;
typedef struct edgeStruct *Edge;
typedef struct nodeStruct *Node;
typedef struct graphStruct *Graph;


typedef struct fifoStruct {
    int head;
    int tail;
    int maxSize;
    Node* list;
} fifoObject;

typedef struct stackStruct {
    int top;
    Edge* list;
} stackObject;

typedef struct edgeStruct {
    Node node;
    int maxCapacity;
    int capacity;
} edgeObject;

typedef struct nodeStruct {
	int number;
 	int edgeNumber;
    int discovered;
    Node parent;
    Edge parentEdge;
 	Edge* edgeList;
} nodeObject;

typedef struct graphStruct {
    int nodeNumber;
    Node source, sink;
    Node *nodeList;
} graphObject;

/**
 * ======================================================================= 
 * ========================[[ Function Headers ]]=========================
 * =======================================================================
 */

void pushFIFO(FIFO fifo, Node node);
Node popFIFO(FIFO fifo);
int emptyFIFO(FIFO fifo);
FIFO createFIFO(int maxSize);
void deleteFIFO(FIFO fifo);

void pushStack(Stack stack, Edge node);
Edge popStack(Stack stack);
int emptyStack(Stack stack);
Stack createStack(int maxSize);
void deleteStack(Stack stack);

void setEdgeNode(Edge edge, Node node);
Node getEdgeNode(Edge edge);
void setEdgeMaxCapacity(Edge edge, int maxcapacity);
int getEdgeMaxCapacity(Edge edge);
void setEdgeCapacity(Edge edge, int capacity);
int getEdgeCapacity(Edge edge);
Edge createEdge(Node node, int capacity);
void deleteEdge(Edge edge);

void setNodeNumber(Node node, int number);
int getNodeNumber(Node node);
void setNodeEdgeNumber(Node node, int number);
int getNodeEdgeNumber(Node node);
void setNodeDiscovered(Node node, int discovered);
int getNodeDiscovered(Node node);
void setNodeParent(Node node, Node parent);
Node getNodeParent(Node node);
void setNodeParentEdge(Node node, Edge edge);
Edge getNodeParentEdge(Node node);
void addNodeEdge(Node node, Edge edge);
Edge getNodeEdge(Node node, int position);
Edge getNodeEdgeByNode(Node node, Node other);
void setNodeEdgeList(Node node, Edge *list);
Edge *getNodeEdgeList(Node node);
Node createNode(int number);
void deleteNode(Node node);
int isNodeEquals(Node node, Node other);

void setGraphNodeNumber(Graph graph, int number);
int getGraphNodeNumber(Graph graph);
void setGraphSource(Graph graph, Node node);
Node getGraphSource(Graph graph);
void setGraphSink(Graph graph, Node node);
Node getGraphSink(Graph graph);
void setGraphNodeList(Graph graph, Node *list);
Node *getGraphNodeList(Graph graph);
void addGraphNode(Graph graph, int index, Node node);
Node getGraphNode(Graph graph, int index);
Graph createGraph();
void deleteGraph(Graph graph);
void inicializeGraph(Graph graph, int size);
void inicializeGraphNodeList(Graph graph);
void inicializeGraphSource(Graph graph);
void inicializeGraphSink(Graph graph);

void readTwoInts(int *first, int *second);
void readThreeInts(int *first, int *second, int *third);
void readFirstLine(int *processNumber, int *relationsNumber);
void readProcessCosts(Graph graph);
void readRelationCosts(Graph graph, int relationsNumber);
void readInput(Graph graph);
void printSolution(Graph graph);

void resetBFSSetup(Graph graph);
void BFS(Graph graph);
int getAugmentationPath(Graph graph, Stack stack);
void EdmondsKarp(Graph graph);

void debugGraph(Graph graph);
void debugFIFO(FIFO fifo);
void debugStack(Stack stack);

/**
 * ======================================================================= 
 * =========================[[ FIFO Functions ]]==========================
 * =======================================================================
 */
/* Getters and Setters */
void pushFIFO(FIFO fifo, Node node) { fifo->list[(fifo->tail)++] = node; }
Node popFIFO(FIFO fifo) { return fifo->list[(fifo->head)++]; }
int emptyFIFO(FIFO fifo) { return (fifo->tail - fifo->head) == 0; }

/* Inicialize and Delete */
FIFO createFIFO(int maxSize) {

    FIFO fifo = (FIFO)can_fail_malloc(sizeof(fifoObject));
    fifo->head = 0;
    fifo->tail = 0;
    fifo->maxSize=maxSize;
    fifo->list = (Node*)can_fail_malloc(sizeof(Node)*maxSize);
    return fifo;
}

void deleteFIFO(FIFO fifo) {
    free(fifo->list);
    free(fifo);
}


/**
 * ======================================================================= 
 * =========================[[ Stack Functions ]]=========================
 * =======================================================================
 */
/* Getters and Setters */
void pushStack(Stack stack, Edge edge) {
    stack->list[++(stack->top)] = edge;
}

Edge popStack(Stack stack) {
    return stack->list[(stack->top)--];
}

int emptyStack(Stack stack) {
    return stack->top == -1;
}

/* Inicialize and Delete */
Stack createStack(int maxSize) {

    Stack stack = (Stack)can_fail_malloc(sizeof(stackObject));
    stack->top = -1;
    stack->list = (Edge*)can_fail_malloc(sizeof(Edge*)*maxSize);
    return stack;
}

void deleteStack(Stack stack) {
    free(stack->list);
    free(stack);
}

void resetStack(Stack stack) {
    while(!emptyStack(stack))
        popStack(stack);
}

/**
 * ======================================================================= 
 * =========================[[ Edge Functions ]]==========================
 * =======================================================================
 */

/* Getters and Setters */
void setEdgeNode(Edge edge, Node node) { edge->node = node;}
Node getEdgeNode(Edge edge) { return edge->node; }

void setEdgeMaxCapacity(Edge edge, int maxCapacity) { edge->maxCapacity = maxCapacity; }
int getEdgeMaxCapacity(Edge edge) { return edge->maxCapacity; }

void setEdgeCapacity(Edge edge, int capacity) { 
    assert(edge->maxCapacity >= capacity);
    edge->capacity = capacity; 
}

int getEdgeCapacity(Edge edge) { return edge->capacity; }


/* Inicialize and Delete */
Edge createEdge(Node node, int maxCapacity) { 

    Edge edge = (Edge)can_fail_malloc(sizeof(edgeObject));
    setEdgeNode(edge, node);
    setEdgeMaxCapacity(edge, maxCapacity);
    setEdgeCapacity(edge, maxCapacity);

    return edge;
}

void deleteEdge(Edge edge) {
    free(edge);
}

/**
 * ======================================================================= 
 * =========================[[ Node Functions ]]==========================
 * =======================================================================
 */

/* Getters and Setters */
void setNodeNumber(Node node, int number) { node->number = number; }
int getNodeNumber(Node node) { return node->number; }


void setNodeEdgeNumber(Node node, int number) { node->edgeNumber = number; }
int getNodeEdgeNumber(Node node) { return node->edgeNumber; }

void setNodeDiscovered(Node node, int discovered) { node->discovered = discovered; }
int getNodeDiscovered(Node node) { return node->discovered; }

void setNodeParent(Node node, Node parent) { node->parent = parent; }
Node getNodeParent(Node node) { return node->parent; }

void setNodeParentEdge(Node node, Edge edge) { node->parentEdge = edge; }
Edge getNodeParentEdge(Node node) { return node->parentEdge; }

void addNodeEdge(Node node, Edge edge) { 

    int i;
    int edgeNumber = getNodeEdgeNumber(node);
    Edge* aux = (Edge*)can_fail_malloc(sizeof(Edge) * (edgeNumber + 1));

    for( i=0 ; i<edgeNumber ; i++) {
        aux[i] = getNodeEdge(node, i);
    }
    aux[i] = edge;

    if (edgeNumber != 0)
        free(getNodeEdgeList(node));

    setNodeEdgeNumber(node, edgeNumber+1);
    setNodeEdgeList(node, aux);

}

Edge getNodeEdge(Node node, int position) { return node->edgeList[position]; }

Edge getNodeEdgeByNode(Node node, Node other) { 

    int i, edgeNumber;
    Edge edge;
    Node neighborNode;

    edgeNumber = getNodeEdgeNumber(node);
    edge = NULL;

    for( i=0 ; i<edgeNumber ; i++ ) {

        edge = getNodeEdge(node, i);
        neighborNode = getEdgeNode(edge);

        if( isNodeEquals(neighborNode, other))
            break;
    }

    return edge;
}

void setNodeEdgeList(Node node, Edge *list) { node->edgeList = list; }
Edge *getNodeEdgeList(Node node) { return node->edgeList; }


/* Inicialize and Delete */
Node createNode(int number) { 

    Node node = (Node)can_fail_malloc(sizeof(nodeObject));
    setNodeNumber(node, number);
    setNodeEdgeNumber(node, 0);

    return node;
}

void deleteNode(Node node) { 

    int i, edgeNumber;
    edgeNumber = getNodeEdgeNumber(node);

    for( i=0 ; i<edgeNumber ; i++) {
        deleteEdge(getNodeEdge(node, i));
    }

    free(getNodeEdgeList(node));
    free(node);
}

int isNodeEquals(Node node, Node other) { return getNodeNumber(node) == getNodeNumber(other); }

/**
 * ======================================================================= 
 * =========================[[ Graph Functions ]]=========================
 * =======================================================================
 */

/* Getters and Setters */
void setGraphNodeNumber(Graph graph, int number) { graph->nodeNumber = number; }
int getGraphNodeNumber(Graph graph) { return graph->nodeNumber; }


void setGraphSource(Graph graph, Node node) { graph->source = node; }
Node getGraphSource(Graph graph) { return graph->source; }


void setGraphSink(Graph graph, Node node) { graph->sink = node; }
Node getGraphSink(Graph graph) { return graph->sink; }


void setGraphNodeList(Graph graph, Node *list) { graph->nodeList = list; }
Node *getGraphNodeList(Graph graph) { return graph->nodeList; }


void addGraphNode(Graph graph, int index, Node node) { graph->nodeList[index] = node; }
Node getGraphNode(Graph graph, int index) { return graph->nodeList[index]; }


/* Inicialize and Delete */
Graph createGraph() { return (Graph)can_fail_malloc(sizeof(graphObject)); }

void deleteGraph(Graph graph) { 

    int i, nodeNumber;
    nodeNumber = getGraphNodeNumber(graph);

    deleteNode(getGraphSource(graph));
    deleteNode(getGraphSink(graph));

    for( i=1 ; i<=nodeNumber ; i++) {
        deleteNode(getGraphNode(graph, i));
    }

    free(getGraphNodeList(graph));
    free(graph);
}

void inicializeGraph(Graph graph, int size) {

    setGraphNodeNumber(graph, size);

    inicializeGraphNodeList(graph);

    inicializeGraphSource(graph);

    inicializeGraphSink(graph);
}

void inicializeGraphNodeList(Graph graph) { 

    int i;
    int size = getGraphNodeNumber(graph);
    Node *list = (Node*)can_fail_malloc(sizeof(Node) * (size+1));
    
    for ( i = 1; i <= size; i++)
    {
        list[i] = createNode(i);
    }

    setGraphNodeList(graph, list);
}

void inicializeGraphSource(Graph graph) { setGraphSource(graph, createNode(X)); }

void inicializeGraphSink(Graph graph) { setGraphSink(graph, createNode(Y)); }


/**
 * ======================================================================= 
 * ==========================[[ I/O Functions ]]==========================
 * =======================================================================
 */
void readTwoInts(int *first, int *second) { scanf("%d %d", first, second); }

void readThreeInts(int *first, int *second, int *third) { scanf("%d %d %d", first, second, third); }

void readFirstLine(int *processNumber, int *relationsNumber) { readTwoInts(processNumber, relationsNumber); }

void readProcessCosts(Graph graph) { 

    int i, costX, costY;
    int processNumber = getGraphNodeNumber(graph);
    Node source = getGraphSource(graph);
    Node sink = getGraphSink(graph);
    Node node;
    Edge edge;

    for ( i=1 ; i<=processNumber ; i++ ) {

        node = getGraphNode(graph, i);

        readTwoInts(&costX, &costY);

        edge = createEdge(node, costX);
        addNodeEdge(source, edge);
        edge = createEdge(source, costX);
        setEdgeCapacity(edge, 0);
        addNodeEdge(node, edge);
        
        edge = createEdge(sink, costY);
        addNodeEdge(node, edge);
        edge = createEdge(node, costY);
        setEdgeCapacity(edge, 0);
        addNodeEdge(sink, edge);
    }
}

void readRelationCosts(Graph graph, int relationsNumber) { 

    int i, p1, p2, cost;
    Node node1, node2;
    Edge edge;

    for ( i=0 ; i<relationsNumber ; i++ ) {

        readThreeInts(&p1, &p2, &cost);

        node1 = getGraphNode(graph, p1);
        node2 = getGraphNode(graph, p2);

        edge = createEdge(node2, 2*cost);
        setEdgeCapacity(edge, cost);
        addNodeEdge(node1, edge);

        
        edge = createEdge(node1, 2*cost);
        setEdgeCapacity(edge, cost);
        addNodeEdge(node2, edge);
    }
}

void readInput(Graph graph) {

    int processNumber, relationsNumber;

    readFirstLine(&processNumber, &relationsNumber);

    inicializeGraph(graph, processNumber);

    readProcessCosts(graph);

    readRelationCosts(graph, relationsNumber);
}

void printSolution(Graph graph) { 

    int i, edgeNumber, maxFlux;
    Edge edge;

    Node source = getGraphSource(graph);
    edgeNumber = getNodeEdgeNumber(source);
    maxFlux = 0;

    for( i=0 ; i<edgeNumber ; i++) {
        
        edge = getNodeEdge(source, i);
        maxFlux = maxFlux + getEdgeMaxCapacity(edge) - getEdgeCapacity(edge);
    }

    printf("%d\n", maxFlux);
}


/**
 * ======================================================================= 
 * ============================[[ Algorithms ]]============================
 * =======================================================================
 */

void resetBFSSetup(Graph graph) { 

    int i, graphSize;
    Node node;
    graphSize = getGraphNodeNumber(graph);



    for( i=1 ; i<=graphSize ; i++) {

        node = getGraphNode(graph, i);
        setNodeDiscovered(node, FALSE);
        setNodeParent(node, NULL);
        setNodeParentEdge(node, NULL);
    }

    node = getGraphSource(graph);
    setNodeDiscovered(node, FALSE);
    setNodeParent(node, NULL);
    setNodeParentEdge(node, NULL);

    node = getGraphSink(graph);
    setNodeDiscovered(node, FALSE);
    setNodeParent(node, NULL);
    setNodeParentEdge(node, NULL);
}

void BFS(Graph graph) {

    int i, edgeNumber;
    Node node, childNode, source, sink;
    Edge edge;

    FIFO fifo = createFIFO(getGraphNodeNumber(graph)+2);
    source = getGraphSource(graph);
    sink = getGraphSink(graph);

    resetBFSSetup(graph);

    pushFIFO(fifo, source);
    setNodeDiscovered(source, TRUE);

    while(!emptyFIFO(fifo)) {
        
        
        node = popFIFO(fifo);
        edgeNumber = getNodeEdgeNumber(node);

        for( i=0 ; i<edgeNumber ; i++ ) {

            edge = getNodeEdge(node, i);

            if( getEdgeCapacity(edge) != 0 ) {

                childNode = getEdgeNode(edge);

                if( !getNodeDiscovered(childNode)) {
                    setNodeDiscovered(childNode, TRUE);
                    setNodeParent(childNode, node);
                    setNodeParentEdge(childNode, edge);
                    pushFIFO(fifo, childNode);

                    if( isNodeEquals(childNode, sink))
                        break;
                }
            }
        }
        if(getNodeDiscovered(sink))
            break;
    }

    deleteFIFO(fifo);
}

int getAugmentationPath(Graph graph, Stack stack) { 

    int maxCapacity, edgeCurrentCapacity;
    Node childNode, source, sink;
    Edge edge;

    source = getGraphSource(graph);
    sink = getGraphSink(graph);

    BFS(graph);

    if( !getNodeDiscovered(sink) )
        return 0;

    edge = getNodeParentEdge(sink);
    maxCapacity = getEdgeCapacity(edge);
    pushStack(stack, edge);
    childNode = getNodeParent(sink);

    while( !isNodeEquals(childNode, source) ) {

        edge = getNodeParentEdge(childNode);
        edgeCurrentCapacity = getEdgeCapacity(edge);
        pushStack(stack, edge);
        childNode = getNodeParent(childNode);

        if(edgeCurrentCapacity < maxCapacity)
            maxCapacity = edgeCurrentCapacity;
    }

    return maxCapacity;
}

void EdmondsKarp(Graph graph) { 

    int fluxInc, newCapacity;
    Edge edge;
    Node receiverNode, senderNode;

    Stack stack = createStack(getGraphNodeNumber(graph)+2);

    fluxInc = 1;

    while(fluxInc != 0) { 

        fluxInc = getAugmentationPath(graph, stack);

        while( !emptyStack(stack) ) {

            edge = popStack(stack);
            receiverNode = getEdgeNode(edge);
            senderNode = getNodeParent(receiverNode);

            newCapacity = getEdgeCapacity(edge)-fluxInc;
            setEdgeCapacity(edge, newCapacity);

            edge = getNodeEdgeByNode(receiverNode, senderNode);
            newCapacity = getEdgeCapacity(edge)+fluxInc;
            setEdgeCapacity(edge, newCapacity);
        }
    }
}


/**
 * ======================================================================= 
 * ==============================[[ Debug ]]==============================
 * =======================================================================
 */
void debugGraph(Graph graph) { 

    int i, j;
    Node node;
    Edge edge;

    /* graph */
    printf("Graph->   node number: %d\n", getGraphNodeNumber(graph));
    /* source */
    node = getGraphSource(graph);
    printf("     Source->   node number: %d     || edge number: %d\n", getNodeNumber(node), getNodeEdgeNumber(node));
    for( i=0 ; i<getNodeEdgeNumber(node) ; i++ ){
        edge = getNodeEdge(node, i);
        printf("          Edge->    node number: %d     || max capacity: %d     || capacity: %d \n", getNodeNumber(getEdgeNode(edge)), getEdgeMaxCapacity(edge), getEdgeCapacity(edge));
    }
    /* sink */
    node = getGraphSink(graph);
    printf("     Sink->   node number: %d     || edge number: %d\n", getNodeNumber(node), getNodeEdgeNumber(node));
    for( i=0 ; i<getNodeEdgeNumber(node) ; i++ ){
        edge = getNodeEdge(node, i);
        printf("          Edge->    node number: %d     || max capacity: %d     || capacity: %d \n", getNodeNumber(getEdgeNode(edge)),getEdgeMaxCapacity(edge), getEdgeCapacity(edge));
    }
    /* nodes */
    for( i=1 ; i<=getGraphNodeNumber(graph) ; i++ ){
        node = getGraphNode(graph, i);
        printf("     Node->    node number: %d     ||edge number: %d\n", getNodeNumber(node), getNodeEdgeNumber(node));
        for( j=0 ; j<getNodeEdgeNumber(node) ; j++ ){
            edge = getNodeEdge(node, j);
            printf("          Edge->    node number: %d     || max capacity: %d     || capacity: %d \n", getNodeNumber(getEdgeNode(edge)), getEdgeMaxCapacity(edge), getEdgeCapacity(edge));
        }
    }
}

void debugFIFO(FIFO fifo) {
    
    puts("------ FIFO ------");
    printf("head: %d     tail: %d     maxSize: %d\nvalues:", fifo->head, fifo->tail, fifo->maxSize);
    int i;
    for(i=0;i<fifo->tail;i++) {
        printf(" %d", fifo->list[i]->number);
    }
    puts("");
    puts("-------------------");
}

void debugStack(Stack stack) {
    
    puts("------ Stack ------");
    printf("top: %d\nvalues:", stack->top);
    int i;
    for( i=0 ; i<=stack->top ; i++) {
        printf(" %d", stack->list[i]->node->number);
    }
    puts("");
    puts("-------------------");
}


/**
 * ======================================================================= 
 * ==============================[[ Main ]]===============================
 * =======================================================================
 */
int main() {

    /* start clock 
    clock_t begin = clock();
    */

    Graph graph = createGraph();
    readInput(graph);
    EdmondsKarp(graph);
    printSolution(graph);
    /*debugGraph(graph);*/
    deleteGraph(graph);

    /* print clock 
    clock_t end = clock();
    printf("tempo: %f\n", ((double)(end - begin) / CLOCKS_PER_SEC));
    */
	return 0;
}