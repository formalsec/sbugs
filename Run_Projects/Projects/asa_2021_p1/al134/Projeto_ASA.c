#include <stdio.h>
#include <stdlib.h>

int n_vertex, n_edges, dominoes_to_move = 0, longest_chain = 1;

typedef struct l link;
struct l{

    int number;
    int longest_path;
    link *next;
};

link *vertexArray;

/*finding the number of sources = number of dominos to put down*/
int *sourcesToFind;

/*the sources of the graph*/
int *sourcesToUse;

/*adiciona um novo link ao vertice correspondente*/
void addLink(int vertexNumber,link* vertex){

    link *inicial_vertex = &vertexArray[vertexNumber];
    int i;

    for(i = 0;; i++){
        if(inicial_vertex->next == NULL){
            inicial_vertex->next = vertex;
            break;
        }
        else
            inicial_vertex = inicial_vertex->next;
    }
}

/*lê o input do IO*/
void readInput(){

    /*lê os valores do nº de vertices e do nº de edges*/
    if(scanf("%d %d", &n_vertex, &n_edges) == 2){
        vertexArray = malloc(sizeof(link) * n_vertex);
        sourcesToFind = malloc(sizeof(int) * n_vertex);
        if(vertexArray == NULL || sourcesToFind == NULL){
            exit(EXIT_FAILURE);
        }
    }
    else printf("Failed to read integers.\n");

    /*estado inicial do vetor de vertices*/
    int i;
    for(i = 0; i < n_vertex; i++){
        vertexArray[i].number = i + 1;
        vertexArray[i].next = NULL;
        vertexArray[i].longest_path = 0;
        sourcesToFind[i] = 0;
    }

    /*lê as ligações*/
    for(i = 1; i <= n_edges; i++){
        int vertex1, vertex2;
        if(scanf("%d %d", &vertex1, &vertex2) == 2){
            link *vertex = malloc(sizeof(link));
            vertex->number = vertex2; vertex->next = NULL; vertex->longest_path = 0;
            addLink(vertex1 - 1, vertex);
            sourcesToFind[vertex2 - 1]++;
        }
        else printf("Failed to read integers.\n");
    }
}

/*encontra o numero de sources do grafo, ou seja, o numero de dominos a mexer*/
void findSources(){

    int i;
    for(i = 0; i < n_vertex; i++){
        if(sourcesToFind[i] == 0){
            dominoes_to_move++;
            sourcesToUse = realloc(sourcesToUse, sizeof(int) * dominoes_to_move);
            sourcesToUse[dominoes_to_move - 1] = i + 1;
        }
    }
}

void findLongestPath(){

    int sourceToUse = dominoes_to_move;
    link *visited = malloc(sizeof(link));
    link vertex = vertexArray[sourcesToUse[sourceToUse - 1]- 1];
    int path;

    for(path = 0;;){

        if(path <= 0 && vertex.next == NULL){
            if(sourceToUse-1 == 0)
                break;
            else{
                path = 0;
                sourceToUse--;
                vertex = vertexArray[sourcesToUse[sourceToUse - 1]- 1];
            }
        }

        else if(vertex.next == NULL || path < vertex.longest_path){

            if(longest_chain < path + 1)
                longest_chain = path + 1;

            vertex = visited[path-1];
            visited = realloc(visited, sizeof(link) * path);
            path--;
        }


        else{
            vertex = *vertex.next;
            path++;
            visited = realloc(visited, sizeof(link)* path);
            visited[path-1] = vertex;
            vertex = vertexArray[vertex.number - 1];
            vertexArray[vertex.number - 1].longest_path = path;  
        }
    }
}


int main(){

    readInput();
    findSources();
    findLongestPath();
    /*prints Output*/
    printf("%d %d\n", dominoes_to_move, longest_chain);
    return 0;
}