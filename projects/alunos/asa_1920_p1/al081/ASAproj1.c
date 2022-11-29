#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

int V, E;

struct Node{
  int value;
  struct Node* next;
};

struct Node *grades; /*vector que guarda notas dos alunos*/

struct Edges{
  struct Node *head;
};

struct Graph{
  int V;  /*Numero de vertices*/
  struct Edges* edges;  /*conjunto de ligacoes entre vertices*/
};

struct Node* newNode(int value){
  struct Node* node = (struct Node*) can_fail_malloc(sizeof(struct Node));
  node->value = value;
  node->next = NULL;
  return node;
}

struct Graph* createGraph(){
  int i;
  struct Graph* graph = (struct Graph*) can_fail_malloc(sizeof(struct Graph));
  graph->V = V;
  graph->edges = (struct Edges*) can_fail_malloc(V * sizeof(struct Edges));
  for (i = 0; i < V; ++i){
    graph->edges[i].head = NULL;
  }
  return graph;
}

struct Node* checkMaximum(int origem, int novoDestino){
  int i;
  struct Node* first = grades; /*ponteiro para primeira posicao das notas*/
  struct Node* second = grades; /*segundo ponteiro para primeira posicao das notas*/
  for (i=0; i<origem; i++){ /*procura valor onde esta a nota do aluno origem*/
    first=first->next;
  }
  for (i=0; i<novoDestino; i++){ /*procura valor onde esta a nota do aluno destino*/
    second=second->next;
  }
  if(first->value<second->value)
    first->value=second->value; /*Visto que aluno origem consegue comunicar com aluno destino, se tal aluno destino tiver melhor nota, entao aluno origem copia e tem melhor nota*/
  return grades;
}

void addEdge(struct Graph* graph, int src, int dest){
  struct Node* x= graph->edges[src].head;
  struct Node* node = newNode(dest);
  if(graph->edges[src].head == NULL) /*se ainda nao existir nenhuma edge nesta origem adiciono no inicio*/
    graph->edges[src].head=node;
  else{
    for(; x->next != NULL; x = x->next);
    x->next = node;
  }
  checkMaximum(src, dest); /*vou ver se esta nova adicao tem melhor nota*/
}

int neighbors(struct Graph* graph, int u, int v){
  int x;
  for (x=0; x<V; ++x){
    int encontreiOrigem=0;
    int encontreiDestino=0;
    struct Node* y= graph->edges[x].head;
    if(u==x) return 0;
    while (y){
      if(u==y->value){  /*se a origem ja esta no vetor*/
        encontreiOrigem=1;
        y = y->next;
      }
      else if(v==y->value){ /*se o destino ja esta no vetor*/
        encontreiDestino=1;
        y=NULL;
      }
      else{
        y = y->next;
      }
    }
    if(encontreiOrigem==1 && encontreiDestino!=1 ){ /*so se a origem estiver no vetor e nao o destino e que adiciono o novo destino*/
      addEdge(graph, x, v);
    }
  }return 0;
}



struct Node* getGrades(){
  struct Node* x;
  int g, i;
  for (i=0; i<V; i++){
    scanf("%d", &g);
    if(grades == NULL)
      grades=newNode(g);
    else {
      for(x = grades; x->next != NULL; x = x->next);
      x->next = newNode(g);
    }
  }
  return grades;
}

void printGrades(){
  struct Node* grade = grades;
    while (grade){
      printf("%d\n", grade->value);
      grade = grade->next;
    }
}



int main(){
  int u, v, i;
  scanf("%d,%d", &V, &E);
  getGrades();
  struct Graph* graph = createGraph();
  for (i=0; i<E; i++){
    scanf("%d %d", &u, &v);
    addEdge(graph, u-1, v-1);
    neighbors(graph, u-1, v-1);
  }
  printGrades();
  return 0;
}
