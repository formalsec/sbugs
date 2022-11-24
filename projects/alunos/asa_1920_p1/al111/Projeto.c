#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct number{
  int id;
  int nota;
};

struct node{
    int student;
    struct node* next;
};

struct Graph{
    int V;
    int P;
    int* Visitado;
    int* Notas;
    int* copianotas;
    int* Listord;
    struct number* ListaOrdenada;
    struct node** Lista;
};

void parser(struct Graph* G);
void createGraph(int n, int m, struct Graph* G);
void inserirAresta( int origem , int destino,struct Graph* G);
struct node* createNode(int v);
void DFS(struct Graph* G, int student);
void algorithm(struct Graph* G);
int procuraVertice(struct Graph* G);
void finish(struct Graph* G);
void heapsort(struct number* lista, int);
void heapify(struct number* lista, int);
void ajusta(struct number* lista, int);

int main(){
  struct Graph* G = can_fail_malloc(sizeof(struct Graph));
  parser(G);
  algorithm(G);
  finish(G);
  return 0;
}

void parser(struct Graph* G){
  int n=0,m=0;
  char* string = can_fail_malloc(sizeof(char*));
  fgets(string,100, stdin);
  n = atoi(strtok(string,","));
  m = atoi(strtok(NULL,""));
  createGraph(n,m,G);
  free(string);
}

void createGraph(int n, int m, struct Graph* G){
  int i;
  char* string = can_fail_malloc(sizeof(char*));
  int destino=0,origem=0;

  G->V = n;
  G->P = n;
  G->Lista = can_fail_malloc((n + 10) * sizeof(struct node*));
  G->Notas = can_fail_malloc((n + 10) * sizeof(int));
  G->Visitado = can_fail_malloc((n + 10) * sizeof(int));
  G->Lista[0] = NULL;
  G->ListaOrdenada = can_fail_malloc(sizeof(struct number*) * (n+10));

  for(i = 1; i <= n+m; i++){
    strcpy(string,"");
    fgets(string,100,stdin);
    if(i <= n){
      /* Cria um vertice no grafo */
      G->Lista[i] = NULL;
      G->Visitado[i] = 0; /* inicializar como sem ter sido visitado */
      G->Notas[i] = atoi(string); /* Adiciona a nota na posicao da tabela */
      G->ListaOrdenada[i-1].nota = atoi(string);
      G->ListaOrdenada[i-1].id =  i;
    }
    else{
      /* Cria uma aresta no grafo */
      destino = atoi(strtok(string," "));
      origem = atoi(strtok(NULL,""));
      inserirAresta(origem,destino,G);
    }
  }
  free(string);
}

void inserirAresta(int origem, int destino, struct Graph* G){
    struct node* newNode = createNode(destino);
    newNode->next = G->Lista[origem];
    G->Lista[origem] = newNode;
}

struct node* createNode(int v){
    struct node* newNode = can_fail_malloc(sizeof(struct node));
    newNode->student = v;
    newNode->next = NULL;
    return newNode;
}

void DFS(struct Graph* G, int student) {
        struct node* adjacentes = G->Lista[student];
        int connectedVertex;
        G->Visitado[student] = 1;
        G->P--;
        while( adjacentes != NULL ) {
            connectedVertex = adjacentes->student;
            if(G->Visitado[connectedVertex] == 0){
              G->Notas[connectedVertex] = G->Notas[student];
              DFS(G, connectedVertex);
            }
            adjacentes = adjacentes->next;
        }
}

void heapsort(struct number lista[],int n) {
	int i,t,l;
	heapify(lista ,n);

  for (i = n - 1; i > 0 ; i--) {
		t = lista[0].nota;
    l = lista[0].id;
		lista[0].nota = lista[i].nota;
    lista[0].id = lista[i].id;
		lista[i].nota = t;
    lista[i].id = l;
		ajusta(lista ,i);
	}
}

void heapify(struct number lista[], int n) {
	int k, i, j, item,l;
	for (k=1; k<n; k++) {
		item = lista[k].nota;
    l = lista[k].id;
		i = k;
		j = (i-1)/2;
		while( (i>0) && (item>lista[j].nota) ) {
			lista[i].nota = lista[j].nota;
      lista[i].id = lista[j].id;
			i = j;
			j = (i-1)/2;
		}
		lista[i].nota = item;
    lista[i].id = l;
	}
}

void ajusta(struct number lista[],int n) {
	int i, j, item, l;
	j = 0;
	item = lista[j].nota;
  l = lista[j].id;
	i = 2 * j + 1;
  while(i < n) {
		if(i + 1 < n){
      if(lista[i].nota < lista[i+1].nota){
        i++;
      }
    }
		if(item < lista[i].nota) {
			lista[j].nota = lista[i].nota;
      lista[j].id = lista[i].id;
			j = i;
			i = 2 * j + 1;
		} else{
      break;
    }
	}
	lista[j].nota = item;
  lista[j].id = l;
}

void algorithm(struct Graph* G){
  int k = G->V-1, i;
  heapsort(G->ListaOrdenada,G->V);
  while(G->P != 0) {
    i = G->ListaOrdenada[k].id;
    if(G->Visitado[i] == 0){
      DFS(G,i);
    }
    k--;
  }
}


void finish(struct Graph* G){
  int i;
  for (i = 0; i <= G->V; i++){
    if(i==0){
      free(G->Lista[i]);
    }
    else{
      free(G->Lista[i]);
      printf("%d\n",G->Notas[i]);
    }
  }
  free(G->ListaOrdenada);
  free(G->Lista);
  free(G->Visitado);
  free(G->Notas);
  free(G);
}
