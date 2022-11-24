#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*==============================================================================
                                ASA - PROJECT 1
                                    GROUP 8
                              Maria Duarte nº90415
                              Laura Baeta nº92507
==============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define UNVISITED -1
#define NONE -1
#define FALSE 0
#define TRUE !(FALSE)

/*Macros that will compare two values*/
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

struct Stack* createStack(int capacity);
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
struct Node* newNode(int dest);
struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest);
void dfs(int at, int id, int n, int* ids, int* low, int* onStack,
  struct Stack* stack, struct Graph* graph);
void orderFriends(int n, struct Graph* graph);
void addGrade(int* grades, int numStudents);
void addFriend(int numConnections, struct Graph* graph);
void printGrade(int*grades, int numStudents);
void freeList(struct Node* head);

/*Struct that represents a stack*/
struct Stack {
    int top;
    /*Array that will held the vertices that have already been visited*/
    int* array;
    int capacity;
};

/*Struct that represents a node in a adjacency list*/
struct Node {
    int dest;
    struct Node* next;
};

/*Struct that represents a Graph in a form of an array of adjacency lists*/
struct Graph {
    /*Number of vertices*/
    int V;
    /*Array that holds the grades of each student*/
    int* grades;
    struct Node** array;
};
/*==============================================================================
                                    STACK
==============================================================================*/
/*Function that initializes the stack*/
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)can_fail_calloc(1, sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = NONE;
    stack->array = (int*)can_fail_calloc(capacity, sizeof(int));
    return stack;
}

/*Function to add an item to stack*/
void push(struct Stack* stack, int item) {
    assert (stack->top <= (stack->capacity));
    stack->array[++stack->top] = item;
}

/*Function to remove an item from stack*/
int pop(struct Stack* stack) {
    if (stack->top == NONE)
        return NONE;
    return stack->array[stack->top--];
}

/*==============================================================================
                                    GRAPH
==============================================================================*/
/*Function to create a new adjacency list node*/
struct Node* newNode(int dest) {
    struct Node* node = (struct Node*)can_fail_malloc(sizeof(struct Node));
    node->dest = (dest-1);
    node->next = NULL;
    return node;
}

/*Function that creates a graph of V vertices*/
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)can_fail_malloc(sizeof(struct Graph));
    graph->V = V;
    /*Create an array of adjacency lists.*/
    graph->array = (struct Node**)can_fail_calloc(V, sizeof(struct Node*));
    graph->grades = (int*)can_fail_calloc(V, sizeof(int));
    return graph;
}

/*Function that adds an edge to the graph */
void addEdge(struct Graph* graph, int src, int dest) {
  /*Add an edge from src to dest.
  A new node is added to the adjacency list of (src-1).
  The node is added at the end*/
    struct Node* node = newNode(dest);

    if (graph->array[src-1] == NULL) {
        graph->array[src-1] = node;
    }
    else {
        struct Node* temp = graph->array[src-1];
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

/*==============================================================================
                              TARJAN ALGORITHM
==============================================================================*/
/*A recursive function that findsstrongly connected components
using DFS traversal */
void dfs(int at, int id, int n, int* ids, int* low, int* onStack,
  struct Stack* stack, struct Graph* graph) {
    int to;
    int node;

    push(stack, at);
    onStack[at] = TRUE;
    ids[at]=low[at]=id++;
    struct Node* pCrawl=graph->array[at];

    while (pCrawl) {
        /*vertex current adjacent to vertex at*/
        to = pCrawl->dest;
        /*This will atribute to the current vertex (aka student) the
        higher grade value between itself and the adjacent vertex*/
        graph->grades[at]=max(graph->grades[at], graph->grades[to]);

        if (ids[to]==UNVISITED) {
            dfs(to, id, n, ids, low, onStack, stack, graph);
            low[ (at)]=min(low[ (at)], low[ (to)]);
            /*This will atribute to the current vertex (aka student) the
            higher grade value between itself and the adjacent vertex*/
            graph->grades[at]=max(graph->grades[at], graph->grades[to]);
        }
        else if (onStack[(to)] == TRUE) {
            low[(at)]=min(low[at], low[to]);
            /*This will atribute to the current vertex (aka student) the
            higher grade value between itself and the adjacent vertex*/
            graph->grades[at] = max(graph->grades[at], graph->grades[to]);
        }
        else{
            /*This will atribute to the current vertex (aka student) the
            higher grade value between itself and the adjacent vertex*/
            graph->grades[at] = max(graph->grades[at], graph->grades[to]);
        }

        pCrawl = pCrawl->next;
    }

    /*When the head node is found again, pop the stack and updates the grades*/
    if (ids[at]==low[at]) {
      node = pop(stack);
      onStack[node]=FALSE;
      graph->grades[node] = graph->grades[at];

        while (node != at){
            onStack[node]=FALSE;
            graph->grades[node] = graph->grades[at];
            node = pop(stack);
        }
    }
}

/*Function to do DFS traversal. It uses the function dfs*/
void orderFriends(int n, struct Graph* graph) {
    int id = 0;
    int i;
    int ids[n];
    int* low;
    int onStack[n];

    low = (int*)can_fail_calloc(n, sizeof(int));
    struct Stack* stack = createStack(n);

    for (i = 0; i < n; i++) {
        ids[i] = UNVISITED;
        low[i] = -1;
        onStack[ (i)] = FALSE;
    }

    /*Calls the recursive helper function to find strongly connected components
    in DFS graph with vertex 'i'*/
    for (i = 0; i < n; i++) {
        if (ids[i] == UNVISITED) {
            dfs(i, id, n, ids, low, onStack, stack, graph);
        }
    }
    free(stack->array);
    free(stack);
    free(low);
}

/*==============================================================================
                              AUXILIARY FUNCTIONS
==============================================================================*/
/*Function that will add the values read from stdin to array of int 'grades'
in the struct Graph graph*/
void addGrade(int* grades, int numStudents) {
    int i;
    int grade;
    char buffer[60];

    for (i = 0; i <numStudents; i++) {
      fgets(buffer, 60, stdin);
      sscanf(buffer, "%d", &grade);
      grades[i] = grade;
    }
}
/*Function that will add the values read from stdin to array of adjacency lists
'array' in the   struct Graph graph*/
void addFriend(int numConnections, struct Graph* graph) {
    int i;
    int std1, std2;
    char buffer[100];

    for (i = 0; i<numConnections; i++) {
        fgets(buffer, 100, stdin);
        sscanf(buffer, "%d %d", &std1, &std2);
        addEdge(graph, std1, std2);
    }
}

/*Function that will print to stdin the ordered grades of each student*/
void printGrade(int* grades, int numStudents) {
    int i;

    for (i = 0; i<numStudents; i++) {
        printf("%d\n", grades[i]);
    }
}

/*Function that will free an adjacency list*/
void freeList(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

/*==============================================================================
                                      MAIN
==============================================================================*/
int main() {
    int numStudents, numConnections;
    char buffer[100];
    int i;


    fgets(buffer, 100, stdin);
    sscanf(buffer, "%d, %d", &numStudents, &numConnections);

    /*Asserts that number of students will always be a above zero*/
    assert(numStudents>0);
    struct Graph* graph = createGraph(numStudents);
    addGrade(graph->grades, numStudents);

    /*The traversal of the graph will only occur if numConnections
    is above zero*/
    if(numConnections>0){
        addFriend(numConnections, graph);
        orderFriends(numStudents, graph);
    }

    printGrade(graph->grades, numStudents);

    /*Free array of adjacency lists*/
    for (i = 0; i < numStudents; i++) {
        freeList(graph->array[i]);
    }

    /*Free th graph*/
    free(graph->grades);
    free(graph->array);
    free(graph);

    return 0;
}
