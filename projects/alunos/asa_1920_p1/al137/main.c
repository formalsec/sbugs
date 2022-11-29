#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --------------------------------------
GLOBAL VARIABLES
---------------------------------------*/
#define NR_ARGS 2
#define WHITE 0
#define GREY 1
#define BLACK 2

/* --------------------------------------
PARSING
---------------------------------------*/
static void displayUsage (const char* appName){
  printf("Usage: %s\n", appName);
  exit(EXIT_FAILURE);
}
static int *parseArgs (long argc, char* argv[]){
  static int args[2];

  argv[1][strlen(argv[1])-1] ='\0';
  args[0] = atoi(argv[1]);
  args[1] = atoi(argv[2]);

  if (argc != NR_ARGS+1) {
    fprintf(stderr, "Invalid number of arguments: ");
    displayUsage(argv[0]);
  }
  if (args[0] < 2 || args[1] < 1) {
    fprintf(stderr, "NOTE: Arg1 > 2 and Arg2 > 1: ");
    displayUsage(argv[0]);
  }
  return args;
}
/* --------------------------------------
FUNCTIONS
---------------------------------------*/
int DFS_visit(int n, int *notas, int *estado, int matriz_adj[n][n], int vertice){

  int i;
  estado[vertice] = GREY;

  for (i = 0; i < n; i++){
    if (matriz_adj[vertice][i] == 1 && estado[i] == WHITE){
      DFS_visit(n, notas, estado, matriz_adj, i);
      if (notas[vertice] < notas[i]) {notas[vertice] = notas[i];}
    }
  }

  estado[1] = BLACK;

  return notas[vertice];
}

int main(int argc, char* argv[]) {
  int *args = parseArgs(argc, argv);          /*args é um array com os valores N e M (nr de alunos e nr de ralacoes)*/
  int notas[args[0]];
  int estado[args[0]];                        /*diz se cada vertice esta a preto, cinzento ou branco*/
  int matriz_adj[args[0]][args[0]];
  int aluno, amigo;                           /*auxiliares para receber as relacoes */
  int i, j;


  for (i = 0; i < args[0]; i++) {

    scanf("%d", &notas[i]);
    estado[i] = WHITE;
    for (j = 0; j < args[0]; j++)
      matriz_adj[i][j] = 0;
  }


  for (i = 0; i < args[1]; i++) {

    scanf("%d %d", &aluno, &amigo);
    matriz_adj[aluno-1][amigo-1] = 1;
  }


  for (i = 0; i < args[0]; i++) {

    if (estado[i] == WHITE) { DFS_visit(args[0], notas, estado, matriz_adj, i); }
  }

  for (i = 0; i < args[0]; i++) { printf("%d\n", notas[i]); }


  return 0;
}
