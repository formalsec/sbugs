#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* André Mendes 93684
   Vasco Simões 93761
   Grupo tp009
*/

#include <stdio.h>
#include <stdlib.h>
#define NIE -1

typedef struct Grafo {
    int numVertices;
    int** adjList; 
    int* numArcs;                                                                                    
} grafo;

typedef struct Pilha {
    int top;
    int* items;
} stack;

int N = 0;
int M = 0;

grafo graph;
int *grades;

stack st;
int time = 0;

int vSCC = 0; /* numero de vertices de um scc */
int numberSCC = 0; /* numero de scc's*/
int *memberSCC; /* cada posicao corresponde a um vertice e o valor nessa posicao corresponde ao scc a que pertence */
int *gradesSCC; /* cada posicao corresponde a um scc e o valor nessa posicao corresponde a nota max nesse scc */


void s_push(int v) {
	st.items[++st.top] = v;
}


int s_pop() {
    if (st.top < 0) return 0;
    return st.items[st.top--];
}


void insert(int src, int dest) {
    graph.adjList[src] = can_fail_realloc(graph.adjList[src], ((++graph.numArcs[src]) + 1)*sizeof(int));
    graph.adjList[src][graph.numArcs[src]] = 0;
    graph.adjList[src][graph.numArcs[src]-1] = dest;
}


void processInput() {
    int i, input1, input2;
    scanf("%d,%d", &N,&M);
    grades = can_fail_malloc(sizeof(int)*N);
    graph.numVertices = N;
    graph.adjList = (int **)can_fail_malloc(N * sizeof(int *));
    graph.numArcs = can_fail_malloc(sizeof(int)*N);
    
    for (i = 0; i < N; i++) {
        graph.adjList[i] = (int *)can_fail_malloc(sizeof(int));
        graph.adjList[i][0] = 0;
        graph.numArcs[i] = 0;
        scanf("%d", &input1);
        grades[i] = input1;
    }

    for(i = 0; i < M; i++) {
        scanf("%d %d", &input1, &input2);
		insert(input2 - 1, input1);
    }
}


int min(int a, int b) {
    return a < b ? a : b;
}


int max(int a, int b) {
    return a > b ? a : b;
}


void spread(int sequence[]) {
    int i, e;
    for(i = (N - 1); i >= 0; i--) {
        grades[sequence[i]] = gradesSCC[memberSCC[sequence[i]]];
        for(e = 0; graph.adjList[sequence[i]][e] != 0; e++) {
            if((memberSCC[sequence[i]] > memberSCC[graph.adjList[sequence[i]][e] - 1]) &&
                (gradesSCC[memberSCC[sequence[i]]] > gradesSCC[memberSCC[graph.adjList[sequence[i]][e] - 1]]))
                gradesSCC[memberSCC[graph.adjList[sequence[i]][e] - 1]] = grades[sequence[i]];
        }
    }
}


void SCCUtil(int u, int disc[], int low[], int inStack[], int sequence[]) {
    int i, maxGrade, w = 0;
    disc[u] = low[u] = ++time; 
    s_push(u); 
    inStack[u] = 1; 

    for (i = 0; graph.adjList[u][i] != 0; i++) { 
        int v = graph.adjList[u][i] - 1;  /* v is current adjacent of 'u' */

        if (disc[v] == NIE) { 
            SCCUtil(v, disc, low, inStack, sequence); 
            low[u] = min(low[u], low[v]); 
        } 

        else if (inStack[v] == 1) {
            low[u] = min(low[u], disc[v]); 
        }   
    }

    if (low[u] == disc[u]) { 
        i = 1;
        maxGrade = NIE;
        gradesSCC = can_fail_realloc(gradesSCC, sizeof(int)*(numberSCC + 1));
        while (i) {
            if (st.items[st.top] == u)
                i = 0;
            w = st.items[st.top];
            inStack[w] = 0;
            s_pop();

            maxGrade = max(grades[w], maxGrade);
            sequence[vSCC++] = w;
            memberSCC[w] = numberSCC;
        }

        gradesSCC[numberSCC++] = maxGrade;
    }
}


void SCC() { 
    int i;
    int *disc = can_fail_malloc(sizeof(int)*N); 
    int *low = can_fail_malloc(sizeof(int)*N); 
    int *inStack = can_fail_malloc(sizeof(int)*N);
    int *sequence = can_fail_malloc(sizeof(int)*N); /* sequencia inversa pela qual o spread deve atuar 
                                            (ordenado de maior para menor low mas o spread
                                            deve atuar de menor para maior) */
    memberSCC = can_fail_malloc(sizeof(int)*N);

    st.items = can_fail_malloc(sizeof(int)*N);
    st.top = -1;
    
    for (i = 0; i < N; i++) { 
        disc[i] = NIE; 
        low[i] = NIE; 
        inStack[i] = 0; 
    } 

    for (i = 0; i < N; i++) 
        if (disc[i] == NIE) 
            SCCUtil(i, disc, low, inStack, sequence); 

    spread(sequence);
}


void printGrades() {
    int i;
    for (i = 0; i < N; i++) {
        printf("%d\n", grades[i]);
    }
}
  
int main() { 
    processInput();
    SCC();
    printGrades();
    return 0; 
} 
