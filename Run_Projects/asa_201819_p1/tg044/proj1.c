#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define TIME 0
#define DISCOVERY    1
#define LOW  2
#define ANTECESSOR   3
#define ARTICULATION    4
#define CONTADOR 0
#define INFINITY -1
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

typedef int verticeId;

typedef struct node verticeDoGrafo;

typedef struct grafo Grafo;

struct node {
  verticeId Id;
  verticeDoGrafo *next;
};

struct grafo {
  int V, E, numeroDeArvores;
  verticeDoGrafo **listaAdjacencias;
};

int *maiorVerticeLista;
int maiorVertice=0;
int *subtreeIds;
int tamanhoArvoreFinal =0;
int tamanhoArvoreInstancia=0;
bool ciclo=false;

Grafo *initGraph(int V) {
  Grafo *grafo = NULL;
  
  if(V > 0 && (grafo = (Grafo*)malloc(sizeof(struct grafo))) != NULL) {
    grafo->V = V;
    grafo->E = 0;
    grafo->numeroDeArvores = 0;
    grafo->listaAdjacencias = (verticeDoGrafo**)malloc(V * sizeof(struct node*));
  }  
  return grafo;
}

void libertaGrafo(Grafo *grafo) {
  int i; 
  for(i = 0; i < grafo->V; ++i) {
    verticeDoGrafo *cabeca = grafo->listaAdjacencias[i];
    while(cabeca != NULL) {
      verticeDoGrafo *temp = cabeca;
      cabeca = cabeca->next;
      free(temp);
    }
  }
  free(grafo->listaAdjacencias);
  free(grafo);
}

void adicionaPonteAoGrafo(Grafo *grafo, verticeId u, verticeId v) {
  if((u > 0 && u <= grafo->V) && (v > 0 && v <= grafo->V)) {
    verticeDoGrafo *w = (verticeDoGrafo*)malloc(sizeof(struct node));
    verticeDoGrafo *x = (verticeDoGrafo*)malloc(sizeof(struct node));
      
    w->Id = u;
    x->Id = v;
    w->next = grafo->listaAdjacencias[v - 1];      
    x->next = grafo->listaAdjacencias[u - 1];
    grafo->listaAdjacencias[v - 1] = w;
    grafo->listaAdjacencias[u - 1] = x;
    grafo->E++;
  }
}


void tarjanVisit(Grafo *grafo, verticeId u, int **lista, int pontosDeArticulacao[1]) {
  verticeDoGrafo *node = grafo->listaAdjacencias[u - 1];
  verticeId adj;
  bool pontoDeArticulacaoCandidato = false;
  int outDegree = 0;

  lista[DISCOVERY][u - 1] = lista[TIME][0];
  lista[LOW][u - 1] = lista[TIME][0];
  ++lista[TIME][0];
  tamanhoArvoreFinal=MAX(tamanhoArvoreFinal, tamanhoArvoreInstancia);

  if(maiorVertice<u){
    subtreeIds[u]=1;
    subtreeIds[maiorVertice] = 0;
    maiorVertice=MAX(maiorVertice, u);
  }

  maiorVerticeLista[grafo->numeroDeArvores] = MAX(maiorVerticeLista[grafo->numeroDeArvores],u);

  while(node != NULL) {
    adj = node->Id;

    if(lista[ARTICULATION][u-1] == 1){
      tamanhoArvoreFinal = MAX(tamanhoArvoreFinal, tamanhoArvoreInstancia);
      tamanhoArvoreInstancia=0;
      break;
    }

    else if(lista[DISCOVERY][adj - 1] == INFINITY) {
      lista[ANTECESSOR][adj - 1] = u;
      tamanhoArvoreInstancia++;
      outDegree++;
      tarjanVisit(grafo, adj, lista, pontosDeArticulacao);

      if((lista[DISCOVERY][u - 1] <= lista[LOW][adj - 1]) && (lista[ARTICULATION][u-1] != 1)) {
        tamanhoArvoreFinal = MAX(tamanhoArvoreFinal, tamanhoArvoreInstancia);
        tamanhoArvoreInstancia=0;
        ciclo=true;
        pontoDeArticulacaoCandidato = true;
      }
      else {
        lista[LOW][u - 1] = MIN(lista[LOW][u - 1], lista[LOW][adj - 1]);

      }
    }

    else if(adj != lista[ANTECESSOR][u - 1]) {
      lista[LOW][u - 1] = MIN(lista[LOW][u - 1], lista[DISCOVERY][adj - 1]);
    }
    node = node->next;
  }

  tamanhoArvoreFinal=MAX(tamanhoArvoreFinal, tamanhoArvoreInstancia);

  if((lista[ANTECESSOR][u - 1] == INFINITY && outDegree > 1) || (lista[ANTECESSOR][u - 1] != INFINITY && pontoDeArticulacaoCandidato)) {
    ++pontosDeArticulacao[CONTADOR]; 
    lista[ARTICULATION][u-1] = 1;
  }
}


void inicializaTarjan(Grafo *grafo, int pontosDeArticulacao[1], int** lista) {
  int  i; 

  pontosDeArticulacao[CONTADOR] = 0;

  for(i=0; i<grafo->V;i++){
    if(lista[DISCOVERY][i++] == INFINITY){
      grafo->numeroDeArvores++;
      maiorVerticeLista[grafo->numeroDeArvores] = 1;
      maiorVertice=0;
      tarjanVisit(grafo, i, lista, pontosDeArticulacao);
    }
  }
}

int compare(const void* a, const void* b){
  return(*(int*)a - *(int*)b);
}


int main() {
  int V=0, E=0, i, origem=0, destino=0, **lista;
  int pontosDeArticulacao[1];
  Grafo *grafo;
  lista = (int**)malloc(5 * sizeof(int*));

  scanf("%d", &V);
  scanf("%d", &E);
  int a[V+1], s[V+1];
  for(i=0;i<=V;i++){
    s[i]=0;
  }
  subtreeIds=s;
  maiorVerticeLista = a;
  grafo = initGraph(V);


  if(lista != NULL) {
    lista[TIME] = (int*)malloc(sizeof(int));
    lista[DISCOVERY] = (int*)malloc(grafo->V * sizeof(int));
    lista[LOW] = (int*)malloc(grafo->V * sizeof(int));
    lista[ANTECESSOR] = (int*)malloc(grafo->V * sizeof(int));
    lista[ARTICULATION] = (int*)malloc(grafo->V * sizeof(int));
  }

  lista[TIME][0] = 0;
  for(i = 0; i < grafo->V; i++) {
    s[i]=0;
    lista[DISCOVERY][i] = INFINITY;
    lista[ANTECESSOR][i] = INFINITY;
    lista[ARTICULATION][i] = INFINITY;
  }

  for(i=0;i<E;i++){
    scanf("%d %d", &origem, &destino);
    adicionaPonteAoGrafo(grafo, origem, destino);
  }

  inicializaTarjan(grafo, pontosDeArticulacao, lista);

  printf("%d\n", grafo->numeroDeArvores);

  maiorVerticeLista[0] = INFINITY;

  /*qsort(maiorVerticeLista, grafo->numeroDeArvores+1, sizeof(int), compare);*/

  /*printf("%d\n", maiorVerticeLista[grafo->numeroDeArvores]);*/
  for(i=0;i<=V;i++){
    if(subtreeIds[i] == 1){
      printf("%d", i);
      if(i < grafo->V){
        printf(" ");
      }
    }
  }
  printf("\n");

  printf("%d\n", pontosDeArticulacao[0]);
  
  lista[TIME][0] = 0;
  for(i = 0; i < grafo->V; i++) {
    lista[ANTECESSOR][i] = INFINITY;
    lista[LOW][i]= INFINITY;
    lista[DISCOVERY][i] = INFINITY;
  }


  tamanhoArvoreFinal =0;
  tamanhoArvoreInstancia=0;
  inicializaTarjan(grafo, pontosDeArticulacao, lista);
  if(ciclo){
    printf("%d\n", tamanhoArvoreFinal+1);
  }
  else{     
    printf("%d\n", tamanhoArvoreFinal);
  }

  libertaGrafo(grafo);
  free(lista[TIME]);
  free(lista[DISCOVERY]);
  free(lista[LOW]);
  free(lista[ANTECESSOR]);
  free(lista[ARTICULATION]);
  free(lista);

  return 0;
}