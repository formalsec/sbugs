#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

/*valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./a.out <tests_p1/T01_clique.in> output.out */

#define WHITE 0
#define BLACK 1

typedef struct {
	int nota;
	int cor;
 	int nAmigos;
 	int* amigos;
} Node;

Node* graph;
int nAlunos;

void inputHandler();
void addAluno(int aluno, int nota);
void addAmigo(int aluno, int amigo);
void graphExecute();
void visitNode(int node, int nota);
void printGraph();

int main(){
    inputHandler();
    graphExecute();
    printGraph();
    return 0;
}

void inputHandler(){
    char token;
    int i, nota, nAmizades, aluno, amigo;

    scanf("%d %c %d", &nAlunos, &token, &nAmizades);

    graph = can_fail_malloc(nAlunos*sizeof(Node));

    for(i = 0; i<nAlunos; i++){
        scanf("%d",&nota);
        addAluno(i, nota);
    }

    for(i = 0; i<nAmizades; i++){
        scanf("%d %d", &amigo, &aluno);
        addAmigo(aluno, amigo);
    }
}

void addAluno(int aluno, int nota){
    graph[aluno].nota = nota;
    graph[aluno].cor = WHITE;
    graph[aluno].nAmigos = 0;
    graph[aluno].amigos = NULL;
}

void addAmigo(int aluno, int amigo){
    /* correcao porque o grafo comeca no indice zero */
    aluno--;
    amigo--;
    if(graph[aluno].nAmigos==0){
		graph[aluno].amigos = can_fail_malloc(sizeof(int));
    }
    else{
        graph[aluno].amigos = can_fail_realloc(graph[aluno].amigos, (graph[aluno].nAmigos+1)*sizeof(int));
    }
    graph[aluno].amigos[graph[aluno].nAmigos] = amigo;
    graph[aluno].nAmigos++;
}

void graphExecute(){
    int i;
    for(i = 0; i<nAlunos; i++){
        if(graph[i].cor == WHITE){
            visitNode(i,0);
        } 
    }
}

void visitNode(int node, int nota){
    int i;
    /*printf("visiting node:%d with grade:%d\n", node, nota); */
    if(nota > graph[node].nota){
        graph[node].nota = nota;
    }
    graph[node].cor = BLACK;
    for(i = 0; i<graph[node].nAmigos; i++){
        if(graph[graph[node].amigos[i]].nota < graph[node].nota ){
            /*printf("node %d called visit to %d\n", node, graph[node].amigos[i]); */
            visitNode(graph[node].amigos[i], graph[node].nota);
        }
    }
}

void printGraph(){
    int i;
    for(i = 0; i<nAlunos; i++)
        printf("%d\n", graph[i].nota);
}