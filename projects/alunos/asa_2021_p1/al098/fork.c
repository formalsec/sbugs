#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
/* vê quais as raizes quando lê os dados e faz a BFS para cada raiz para saber qual gera uma arvore maior
*/

/* --------------------------------------------------------- */
/* ----------------------- Constants ----------------------- */
/* --------------------------------------------------------- */
#define FALSE 0
#define TRUE 1

/* --------------------------------------------------------- */
/* ---------------------- node struct ---------------------- */
/* --------------------------------------------------------- */
typedef struct {
	int number;
    int discovered;
	int level;
 	int edgeNo;
 	int* edges;
} Node;

typedef struct {
    int size;
    Node* list;
    int rootNo;
    int* roots;
} Graph;

typedef struct {
    int top;
    Node** list;
} Stack;

/* --------------------------------------------------------- */
/* ------------------- Functions Headers ------------------- */
/* --------------------------------------------------------- */
Graph* readInput();
void exec(Graph* graph);
int DFS(Graph* graph, Node* root);

/* graph */
Graph* createGraph(int size);
void deleteGraph(Graph* graph);
void addNodeEdge(Graph* graph, int node, int edge);

/* Stack */
Stack* createStack(int maxSize);
void deleteStack(Stack* stack);
void pushStack(Stack* stack, Node* node);
Node* popStack(Stack* stack);
int emptyStack(Stack* stack);

/* debug */
void debugList(Graph* graph);
void debugStack(Stack* Stack);

/* --------------------------------------------------------- */
/* ------------------------- main -------------------------- */
/* --------------------------------------------------------- */
int main() {
    
    /*clock_t begin = clock();*/

    Graph* graph = readInput();

    /*debugList(graph);*/
    exec(graph);
    /*debugList(graph);*/

    deleteGraph(graph);
    /*
    clock_t end = clock();
    printf("tempo: %f\n", ((double)(end - begin) / CLOCKS_PER_SEC));
    */
	return 0;
}

/* --------------------------------------------------------- */
/* ----------------- Functions Definitions ----------------- */
/* --------------------------------------------------------- */
Graph* readInput() {

    int i, nodeNo, edgeNo, first, second;
    int* roots;
    Node* node;

    scanf("%d %d", &nodeNo, &edgeNo);
    Graph* graph = createGraph(nodeNo);

    /* List with nodeNo positions. If node i is root, then roots[i]=1. */
    roots = (int*)can_fail_malloc(sizeof(int)*(nodeNo+1));
    graph->rootNo = nodeNo;

    /**/
    for ( i=1 ; i<=nodeNo ; i++) {
        node = &(graph->list[i]); 
        node->number = i;
        node->level = 0;
        node->edgeNo = 0;
        roots[i] = 1;
    }
    /**/
    for ( i=0 ; i<edgeNo ; i++) {
		scanf("%d %d", &first, &second);
        addNodeEdge(graph, first, second);

        if(roots[second] == 1) {
            roots[second] = 0;
            graph->rootNo--;
        }
	}

    graph->roots = (int*)can_fail_malloc(sizeof(int)*graph->rootNo);
    int head=0;
    for( i=1 ; i<=nodeNo ; i++) {
        if(roots[i] == 1) {
            graph->roots[head++] = i;
        }
    }

    return graph;
}

void exec(Graph* graph) {

    int i, maxTreeLen=0, treeLen;
    Node* node;
    for( i=0 ; i<graph->rootNo ; i++) {

        node = &(graph->list[graph->roots[i]]);
        treeLen = DFS(graph, node);

        if(treeLen > maxTreeLen) {
            maxTreeLen = treeLen;
        }
    }

    printf("%d %d\n", graph->rootNo, maxTreeLen);
    /*
    printf("roots:");
    for(i=0;i<graph->rootNo;i++) {
        printf(" %d", graph->roots[i]);
    }
    puts("");
    */
}

int DFS(Graph* graph, Node* root) {

    int i, maxLevel=0;
    Node *node, *childNode;
    Stack* stack = createStack(graph->size);

    /* Reset discovered. */
    for( i=1 ; i<=graph->size ; i++) {
        graph->list[i].discovered = FALSE;
    }

    root->level = 1;
    pushStack(stack, root);

    while(!emptyStack(stack)) {
        
        node = popStack(stack);
        root->discovered = TRUE;

        for( i=0 ; i<node->edgeNo ; i++ ) {

            childNode = &(graph->list[node->edges[i]]);

            if(childNode->level <= node->level){
                childNode->level = node->level + 1;
                pushStack(stack, childNode);

                if(childNode->level > maxLevel) {
                    maxLevel = childNode->level;
                }
            }
            
        }
    }
    /*debugStack(stack);*/
    deleteStack(stack);
    return maxLevel;
}

/* -------------------- Graph Functions -------------------- */
Graph* createGraph(int size) {
    Graph* graph = (Graph*)can_fail_malloc(sizeof(Graph));
    graph->list = (Node*)can_fail_malloc(sizeof(Node)*(size+1));
    graph->size = size;
    return graph;
}

void deleteGraph(Graph* graph) {
    free(graph->list);
    free(graph);
}

void addNodeEdge(Graph* graph, int n, int edge) {

    Node* node = &(graph->list[n]);

    if( node->edgeNo == 0) {
        node->edgeNo++;
        node->edges = (int*)can_fail_malloc(sizeof(int));
        node->edges[0] = edge;
    }
    else {
        node->edgeNo++;
        int* aux = (int*)can_fail_malloc(sizeof(int) * node->edgeNo);

        int i;
        for( i=0 ; i<(node->edgeNo-1) ; i++) {
            aux[i] = node->edges[i];
        }
        aux[i] = edge;
        free(node->edges);
        node->edges = aux;
    }
}

/* -------------------- Stack Functions -------------------- */
Stack* createStack(int maxSize) {

    Stack* stack = (Stack*)can_fail_malloc(sizeof(Stack));
    stack->top = -1;
    stack->list = (Node**)can_fail_malloc(sizeof(Node*)*maxSize);
    return stack;
}

void deleteStack(Stack* stack) {
    free(stack->list);
    free(stack);
}

void pushStack(Stack* stack, Node* node) {
    stack->list[++(stack->top)] = node;
}

Node* popStack(Stack* stack) {
    return stack->list[(stack->top)--];
}

int emptyStack(Stack* stack) {
    return stack->top == -1;
}

/* ------------------------- Debug ------------------------- */
void debugList(Graph* graph) {

    int i, j;
    puts("------ Graph ------");
    printf("rootNo: %d   roots:", graph->rootNo);
    for(i=0 ; i<graph->rootNo ; i++) {
        printf(" %d", graph->roots[i]);
    }
    puts("");
    
    for( i=1 ; i <= graph->size ; i++ ) {
        printf("node: %d  |-> level: %d  |-> adgeNo: %d  |-> adges:", graph->list[i].number, graph->list[i].level, graph->list[i].edgeNo);
        for( j=0 ; j<graph->list[i].edgeNo ; j++) {
            printf(" %d", graph->list[i].edges[j]);
        }
        puts("");
    }
    puts("-------------------");
}

void debugStack(Stack* stack) {
    
    puts("------ Stack ------");
    printf("top: %d\n", stack->top);
    puts("-------------------");
}