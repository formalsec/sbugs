#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct{
  int pessoa;
  int market;
  int* edges;
  int* flow;
  int n_edge;
  bool onQueue;
  int parent;
} Crossing;

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

int avenues, streets, markets, person;
int n_vertex;
int* queue;
int front=-1, rear = -1;
Crossing* corners;
int max_flow = 0;



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

void inicialize_corners();
void addEdge(int a, int b);
void build_matrix();
void edmonds_karp();
int BFS();
void augment(int end);
int find_edge(int a, int b);
int min(int a, int b);
bool isEmpty();
void push(int n);
int pop();
void reset();

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

int main(){
  int i,l,c,node;
  scanf("%d %d", &avenues, &streets);
  scanf("%d %d", &markets, &person);
  n_vertex = avenues*streets;


  inicialize_corners();
  queue = can_fail_malloc(sizeof(int)*(n_vertex*2+2));

  for(i=0;i<markets;i++){
    scanf("%d %d", &l, &c);
    node = 2*((c-1)*avenues + l);
    corners[node-1].market = 1;
    addEdge(node, n_vertex*2+1);
  }

  for(i=0;i<person;i++){
    scanf("%d %d", &l, &c);
    node = 2*((c-1)*avenues + l);
    if(corners[node-1].pessoa != 1){
      corners[node-1].pessoa = 1;
      addEdge(0,node-1);
    }
  }

  build_matrix();

  edmonds_karp();
  printf("%d\n", max_flow);
  for(i=0;i<(n_vertex*2+2);i++){
    free(corners[i].flow);
    free(corners[i].edges);
  }
  free(corners);
  return 0;
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/



void inicialize_corners(){
  int i;
  corners = (Crossing*)can_fail_malloc(sizeof(Crossing)*(n_vertex*2+2));
  for(i=0; i<(n_vertex*2+2);i++){
    corners[i].pessoa = 0;
    corners[i].market = 0;
    corners[i].n_edge = 0;
    corners[i].edges = NULL;
    corners[i].flow = NULL;
    corners[i].parent = -1;
    corners[i].onQueue = false;
  }
}

void addEdge(int a, int b){
  int i;

  int* new_edges;
  int* new_flow;


  if(corners[a].n_edge == 0){
    corners[a].edges = can_fail_malloc(sizeof(int));
    corners[a].edges[0] = b;
    corners[a].flow = can_fail_malloc(sizeof(int));
    corners[a].flow[0] = 1;
    corners[a].n_edge++;
  }
  else{
    corners[a].n_edge++;
    new_edges = can_fail_malloc(sizeof(int)*corners[a].n_edge);
    new_flow = can_fail_malloc(sizeof(int)*corners[a].n_edge);
    for(i = 0; i < corners[a].n_edge-1; i++){
      new_edges[i] = corners[a].edges[i];
      new_flow[i] = corners[a].flow[i];
    }
    new_edges[i] = b;
    new_flow[i] = 1;
    corners[a].edges = new_edges;
    corners[a].flow = new_flow;

  }
}

void build_matrix(){
  int i;
  for(i=1;i<n_vertex*2;i += 2){ /*para o lado direito*/
    addEdge(i, i+1);
  }

  for(i=2;i<n_vertex*2+1; i+=2){
    if(i+2*avenues < n_vertex*2+1){  /*para cima e baixo*/
      addEdge(i,i+2*avenues-1);
      addEdge(i+2*avenues,i-1);
    }
    if(i%(2*avenues) != 0){
      addEdge(i, i+1);
      addEdge(i+2,i-1);
    }
  }
 /*-----------------------------------------------*/
}





bool isEmpty(){
  return front == -1 || rear == -1;
}

int pop(){
  int i;
  if(isEmpty())
    return -1;
  if(front==rear){
    i = rear;
    rear = -1; front = -1;
    return queue[i];
  }
  else{
    return queue[front++];
  }
}

void push(int n){
  if(isEmpty()){
    front = 0; rear=0;
    queue[rear] = n;
  }
  else{
    rear++;
    queue[rear] = n;
  }
}


int min(int a, int b){
    return ((a<b)?a:b);
}


void edmonds_karp(){/*Recebe Grafo, sink, source : Edmonds-Karp(G,s,t) */
  int end;

  push(0);
  end = BFS();
  if(end>0){
    augment(end);
    max_flow++;
  }

  while(end != -1 && !(max_flow == min(person,markets))) {
    reset();
    push(0);
    end = BFS();
    if(end>0){
      augment(end);
      max_flow++;
    }
  }
}

int BFS(){
  int i,node,destino;
  while(!isEmpty()){
    node = pop();
    for(i=0; i< corners[node].n_edge; i++){
      destino = corners[node].edges[i];
      if(corners[destino].onQueue || corners[node].flow[i] == 0){
        continue;
      }
      else{
        if(destino == n_vertex*2+1){ /*se for a sink*/
          corners[node].flow[i] = 0;
          return node;
        }
        else if(corners[destino].pessoa == 1 && node != 0){
          continue;
        }
        else{
          push(destino);
          corners[destino].parent = node;
          corners[destino].onQueue = true;
        }
      }
    }
  }
  return -1;
}

void reset(){
  int i;
  for(i=0;i< n_vertex*2+2;i++){
    corners[i].onQueue = false;
    corners[i].parent = -1;
    front = -1; rear = -1;
  }
}

void augment(int end){
  int n,prev, aux;
  prev = corners[end].parent;
  n = find_edge(prev, end);
  corners[prev].flow[n] = 0;
  addEdge(end, prev);

  while(prev != 0){
    aux = corners[prev].parent;
    n = find_edge(aux, prev);
    corners[aux].flow[n] = 0;
    addEdge(prev, aux);
    prev = corners[prev].parent;
  }
}

int find_edge(int a, int b){
  int i;
  for(i=0; i<corners[a].n_edge;i++){
    if(corners[a].edges[i] == b) return i;
  }
  return -1;
}
