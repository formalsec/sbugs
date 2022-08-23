
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

typedef struct Vertex {
    int student;
    struct Vertex* next;
} Vertex;


typedef struct Graph {
    int numVertices;
    Vertex** adjLists;
    int* grades;
} Graph;

Vertex* stack = NULL;

Graph* createGraph(int numVertices);
void destroyGraph(Graph* graph);
Vertex* createVertex(int student);
void addEdge(Graph* graph, int src, int dest);
void search(Graph* graph);

Graph* processInput();
void printGraph(struct Graph* graph);

Graph* processInput() {
    char line[20];
    int src, dest,i;
    int numVertices;
    int numRelations;
    
    fgets(line, sizeof(line)/sizeof(char), stdin);
    numVertices = atoi(strtok(line, ","));
    numRelations = atoi(strtok(NULL, ","));

    Graph* graph = createGraph(numVertices);
    
    for(i = 1; i <= numVertices; i++) {
        fgets(line,sizeof(line)/sizeof(char), stdin);
        graph->grades[i] = atoi(line);
    }
    for(i = 1; i <= numRelations; i++) {
        fgets(line, sizeof(line)/sizeof(char), stdin);
        src = atoi(strtok(line, " "));
        dest = atoi(strtok(NULL, " "));
        addEdge(graph, src, dest);
    }
    return graph;
}
Graph* createGraph(int numVertices) {
    int i;
    Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (Vertex**)malloc((numVertices+1)*sizeof(Vertex*));
    graph->grades = (int*)malloc((numVertices + 1) *sizeof(int));

    for(i = 1; i <= numVertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void destroyGraph(Graph* graph) {
    int i;
    for(i = 1; i <= graph->numVertices; i++) {
        Vertex* vertexAux = graph->adjLists[i];
        while(vertexAux != NULL) {
            Vertex* vextexNext = vertexAux->next;
            free(vertexAux);
            vertexAux = vextexNext;
        }
    }
    free(graph->grades);
    free(graph->adjLists);
    free(graph);
}

Vertex* createVertex(int student) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->student = student;
    return newVertex;
}

void addEdge(Graph* graph, int src, int dest) {
    Vertex* destVertex = createVertex(dest);
    destVertex->next = graph->adjLists[src];
    graph->adjLists[src] = destVertex;
}

void searchAux(Graph* graph, int v, int time, int* disc, int* low, bool* stackMember) {
    int vtemp = 0;
    Vertex *vertex;
    Vertex* vertexAux;

    vertex = graph->adjLists[v];
    vtemp = v;

    disc[v] = low[v] = ++time;

    vertexAux = createVertex(v);
    vertexAux->next = stack;
    stack = vertexAux;

    stackMember[v] = true;
    
    for(; vertex != NULL; vertex = vertex->next) {

        v = vertex->student;
      
        if(disc[v] == -1){
            searchAux(graph, v, time, disc, low, stackMember);

            if(low[v] < low[vtemp]) {
                low[vtemp] = low[v];
            }       
        }    
          
        else if(stackMember[v] == true) {
            if(disc[v] < low[vtemp]) {
                low[vtemp] = disc[v];
            }
        }    

        if(graph->grades[v] > graph->grades[vtemp]) {
        graph->grades[vtemp] = graph->grades[v];
    }   
    } 
    int w = 0;
    int max = graph->grades[vtemp];
    Vertex* aux = stack;
    if(low[vtemp] == disc[vtemp]) {
        while(aux->student != vtemp) {
            if(graph->grades[aux->student] > max) {
                max = graph->grades[aux->student];  
            }
            aux = aux->next;
        }
        while(stack->student != vtemp) {
            w = stack->student;
            graph->grades[w] = max;
            stackMember[w] = false;
            stack = stack->next;
        }
        w = stack->student;
        graph->grades[w] = max;
        stackMember[w] = false;
        stack = stack->next;
    }
    
} 

void search(Graph* graph) {
    int* disc = (int*)malloc(sizeof(int)*(graph->numVertices+1));
    int* low = (int*)malloc(sizeof(int)*(graph->numVertices + 1));
    bool* stackMember = (bool*)malloc(sizeof(int)*(graph->numVertices + 1));

    int i;
    int time = 0;

    for(i = 1; i <= graph->numVertices; i++) {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }


    for(i = 1; i<= graph->numVertices; i++) {   
        if(disc[i] == -1) { 
            searchAux(graph, i, time, disc, low, stackMember); 
        }  
    }
    free(disc);
    free(stackMember);
    free(low);
}


int main() {
    int i;
    Graph* graph = processInput();

    search(graph);

    for(i = 1; i <= graph->numVertices; i++) {
        printf("%d\n", graph->grades[i]);
    }

    destroyGraph(graph);
    return 0;
}




