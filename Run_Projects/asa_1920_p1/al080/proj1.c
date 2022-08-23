/* 1º Projeto ASA
   Miguel Moura Ramos ist192531 
   Grupo 80 ---> al080
*/

#include <stdlib.h>
#include <stdio.h>

#define NIL -1

#define FALSE 0
#define TRUE 1

#define GRAY 0
#define WHITE 1
#define BLACK 2

/* ----  Estruturas de Dados Utilizadas. ---- */

typedef struct Stack {
    int top;
    int size;
    int* values;
    int* onStack;
}Stack;

typedef struct Node {
    int dest;
    struct Node* next;
}Node;

typedef struct Graph {
    Node** adjList;
    int V;
    int time;      
    int SCCs;
    int* grade;
    int* d;
    int* color;
    int* low;
    int* SCCId;   /*Guarda em que SCC o vertice faz parte.*/
    int* SCCGrades;
}Graph;

/* Funcao Maximo e Minimo para facilitar a implementacao dos algoritmos. */
int Min(int a,int b) {
    return a < b ? a : b;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

/* Implementacao da Stack sem verificacao de argumentos. Assumi que estao sempre bem.*/

Stack* createStack(int size) {
    int i;
    Stack* s = malloc(sizeof(Stack));
    s->size = size;
    s->top = NIL;
    s->values = malloc(sizeof(int)*size);
    s->onStack = malloc(sizeof(int)*(size+1));

    for(i = 0; i < size; i++) {
        s->values[i] = NIL;
        s->onStack[i] = FALSE;
    }
    s->onStack[i] = FALSE;

    return s;
}

void push(Stack* s, int v) {
    s->values[++s->top] = v;
}

int pop(Stack* s) {
    return s->values[s->top--];
}

/* Implementacao do Grafo. */

Graph* createGraph(int V) {
    int i;
    Graph* g = malloc(sizeof(Graph));

    g->V = V;
    g->adjList = malloc(sizeof(Node)*(V+1));
    g->grade = malloc(sizeof(int)*(V+1));
    g->low = malloc(sizeof(int)*(V+1));
    g->d = malloc(sizeof(int)*(V+1));
    g->color = malloc(sizeof(int)*(V+1));
    g->SCCId = malloc(sizeof(int)*(V+1));
    g->SCCGrades = malloc(sizeof(int)*(V+1));

    for(i = 1; i <= g->V; i++) {
        g->adjList[i] = NULL;
        g->grade[i] = g->low[i] = g->d[i] = g->SCCId[i] = g->SCCGrades[i] = NIL;
    }
    g->SCCs = 1; /* SCC estao numeradas de 1 a V. */

    return g;
}

/* Adiciona uma aresta entre src e dest.*/
void addEdge(Graph* g,int src, int dest) {
    Node* newNode =  malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;
}

/* Algoritmo de Tarjan para encontrar as SCCs.*/
void Tarjan_Visit(Graph* g,Stack* s,int i) {
    Node* tmp;
    g->d[i] = g->low[i] = ++g->time;

    push(s,i);
    s->onStack[i] = TRUE;

    for(tmp = g->adjList[i]; tmp != NULL; tmp = tmp->next) {
        int v = tmp->dest;
        if(g->d[v] == NIL || s->onStack[v]) {
            if(g->d[v] == NIL) {
                Tarjan_Visit(g,s,v);
            }
            g->low[i] = Min(g->low[v],g->low[i]);
        }
    }
    
    if(g->low[i] == g->d[i]) {
        int u;
        while(s->values[s->top] != i) {
            u = pop(s);
            s->onStack[u] = FALSE;
            g->SCCId[u] = g->SCCs;
            g->SCCGrades[g->SCCs] = Max(g->SCCGrades[g->SCCs],g->grade[u]);
        }
        u = pop(s);
        s->onStack[u] = FALSE;
        g->SCCId[u] = g->SCCs;
        g->SCCGrades[g->SCCs] = Max(g->SCCGrades[g->SCCs],g->grade[u]);
        g->SCCs++;
    }
}

void SCC_Tarjan(Graph* g) {
    int i;
    int V = g->V;
    Stack* s = createStack(V);
    
    g->time = 0;

    for(i = 1; i <= V; i++)
        if(g->d[i] == NIL)
            Tarjan_Visit(g,s,i);

   free(s->onStack);    /*Liberta a Stack usada durante o algoritmo. */
   free(s->values);
   free(s);
}

/* DFS que servira para propagar as notas dos grupos de alunos. */
void DFSVisit(Graph* g, int v) {
    Node* ptr;
    g->color[v] = GRAY;
  
    for(ptr = g->adjList[v]; ptr != NULL; ptr = ptr->next) {
        if(g->color[ptr->dest] == WHITE) 
            DFSVisit(g,ptr->dest);
        g->grade[v] = Max(g->grade[v],g->grade[ptr->dest]);
    }

    g->color[v] = BLACK;
}

void DFS(Graph* g) {
    int i;

    for(i = 1; i <= g->V; i++) {
        g->color[i] = WHITE; 
    }

    for(i = 1; i <= g->V; i++) {
        if(g->color[i] == WHITE) {
            DFSVisit(g,i);
        }
    }
}

/* Algoritmo -> Encontrar as SCCs. Criar um grafo aciclico e fazer uma DFS.*/
Graph* doAlgorithm(Graph* g) {
    SCC_Tarjan(g);
    Graph* scc = createGraph(g->SCCs); 
    
    int v;
    for(v = 0; v < g->SCCs; v++) 
        scc->grade[v] = g->SCCGrades[v];
    
    Node* ptr;
    for(v = 1; v <= g->V; v++)
        for(ptr = g->adjList[v]; ptr != NULL; ptr = ptr->next) {
            if(g->SCCId[v] != g->SCCId[ptr->dest])
                addEdge(scc,g->SCCId[v],g->SCCId[ptr->dest]);
        }
    
    DFS(scc);
    return scc;
}


/* Funcoes para leitura do input e escrita do output. */
Graph* readInput() {
    int V, numE;
    if (scanf("%d,%d",&V,&numE) != 2) {
        fprintf(stderr,"Invalid input");
        exit(EXIT_FAILURE);
    }

    Graph * g = createGraph(V);
    int i;
    for(i = 1; i <= V; i++) {
        int grade; 
        if (scanf("%d",&grade) != 1) {
            fprintf(stderr,"Invalid input");
            exit(EXIT_FAILURE);
        }
        g->grade[i] = grade;
    }

    for(i = 0; i < numE; i++) {
        int src,dest; 
        if (scanf("%d %d",&src,&dest) != 2) {
            fprintf(stderr,"Invalid input");
            exit(EXIT_FAILURE);
        };
        addEdge(g,src,dest);
    }
    return g;
}

void writeOutput(Graph* g,Graph* scc) {
    int i;
    for(i = 1; i <= g->V; i++)
        printf("%d\n",scc->grade[g->SCCId[i]]);
}

/* Liberta toda a memoria utilizada. */
void freeMemory(Graph* g, Graph* scc) {
    Node* ptr;
    int i;
    for(i = 1; i <= g->V; i++) {
        while(g->adjList[i]) {
            ptr = g->adjList[i];
            g->adjList[i] = g->adjList[i]->next;
            free(ptr);
        }
    }
     for(i = 1; i <= scc->V; i++) {
        while(scc->adjList[i]) {
            ptr = scc->adjList[i];
            scc->adjList[i] = scc->adjList[i]->next;
            free(ptr);
        }
    }

    free(g->adjList);
    free(g->color);
    free(g->d);
    free(g->grade);
    free(g->low);
    free(g->SCCId);
    free(g->SCCGrades);
    free(g);
    
    free(scc->adjList);
    free(scc->color);
    free(scc->d);
    free(scc->grade);
    free(scc->low);
    free(scc->SCCId);
    free(scc->SCCGrades);
    free(scc);
}

int main() {
    Graph* g = readInput();
    Graph* scc = doAlgorithm(g);
    writeOutput(g,scc);
    freeMemory(g,scc);
    return 0; 
}