#include "stdio.h"
#include "stdlib.h"
#include <math.h>

#define min(x,y) (x<y) ? x:y
#define max(x,y) (x>y) ? x:y

typedef struct edge{
  int dest, cap, flow;
  struct edge* next;
}Edge;

typedef struct minE{
  int src, dest;
  struct minE* next;
}MinEdge;

typedef struct vertex{
  Edge* head;
  int id;
  int cap;
  int prod;
  int flow;
  int parent;
  int bottleneck;
  int bigger;
}Vertex;

typedef struct queue{
  int n;
  struct queue* next;
}Queue;

/*prototypes*/
int parseInput();
int createNetwork();
int addEdge();
int resetVisited();
void printQueue();
void BFS2();

/*globals*/

int nFor, nEst, nLig, nVert;
Vertex* network;
Vertex* network2;
Queue* visited2;
Queue* bigger=NULL;
MinEdge* minimal;
int sources_visited = 0;


int resetVisited(){
  int i;
  for(i=0;i<nVert;i++){
    network[i].parent = -1;
    network[i].bottleneck = network[0].cap; /*cant get a bigger value than this*/
  }
  return 1;
}

int parseInput(){
  scanf("%d %d %d", &nFor, &nEst, &nLig);
  nVert = nFor + nEst + 1;
  createNetwork();
  int i;
  for(i=0;i<nFor;i++){
    scanf("%d", &(network[i+1].prod)); /*production*/
    network[0].cap+=network[i+1].prod;
  }
  for(i=0;i<nEst;i++){ /*capacity*/
    scanf("%d", &(network[i+nFor+1].cap));
  }
  for(i=0;i<nLig;i++){
    int s, d, c;
    scanf("%d %d %d", &s, &d, &c);
    addEdge(s-1,d-1,c);
  }
  return 1;
}

int createNetwork(){
  network = (Vertex*) malloc(nVert*sizeof(Vertex));
  int i;
  for(i=0;i<nVert;i++){
    network[i].id=i+1;
    network[i].prod=0;
    network[i].head=NULL;
  }
  return 1;
}

int addEdge(int src, int des, int cap){
  Edge* e = (Edge*) malloc(sizeof(Edge));
  e->dest=des;
  e->cap=cap;
  e->flow=0;
  e->next=NULL;
  if(network[src].head==NULL){
    network[src].head=e;
  }
  else{
    Edge* current = network[src].head;
    while(current->next!=NULL){
      current=current->next;
    }
    current->next=e;
  }
  return 1;
}

int addEdge2(int src, int des, int cap){
  Edge* e = (Edge*) malloc(sizeof(Edge));
  e->dest=des;
  e->cap=cap;
  e->flow=0;
  e->next=NULL;
  if(network2[src].head==NULL){
    network2[src].head=e;
  }
  else{
    Edge* current = network2[src].head;
    while(current->next!=NULL){
      current=current->next;
    }
    current->next=e;
  }
  return 1;
}



int queue(int n, Queue* q){
  Queue* a = (Queue*) malloc (sizeof(Queue));
  a->n=n;
  a->next=NULL;
  Queue* current=q;
  while(current->next!=NULL){
    current=current->next;
  }
  current->next=a;
  return 1;
}

Queue* pop(Queue* q){
  Queue* next = q->next;
  free(q);
  return next;
}

void freeQueue(Queue* q){
  Queue* current;
  while(q!=NULL){
    current=q;
    q=q->next;
    free(current);
  }
}

int BFS(){
  Queue* q = (Queue*) malloc (sizeof(Queue));
  q->n = 1;
  q->next = NULL;
  network[1].parent = -1;
  int i;
  for(i=1;i<nFor;i++){
    queue(i+1,q);
    network[i+1].parent = -1;
  }

  int reachHiper = 0;
  while(q!=NULL && !reachHiper){
    Edge* adj = network[q->n].head;
    int maxProd=0;
    if(network[q->n].prod == -1){

      maxProd = 1;
    }
    while(!maxProd && adj!=NULL && !reachHiper){ /*can still pass flow thru the edge and vertex*/
      if(network[adj->dest].parent==-1 && (adj->cap>adj->flow) && (network[adj->dest].flow<network[adj->dest].cap)){
        network[adj->dest].bottleneck=min(adj->cap - adj->flow,network[q->n].bottleneck);
        network[adj->dest].bottleneck=min(network[adj->dest].cap-network[adj->dest].flow,network[adj->dest].bottleneck);
        network[adj->dest].parent=q->n;
        queue(adj->dest,q);
        if(adj->dest==0){

          reachHiper=1;
        }
      }
      adj=adj->next;
    }
    q=pop(q);
  }
  freeQueue(q);
  return reachHiper;
}

Queue* getPath(){
  Queue* path=NULL;
  Vertex v = network[0];
  while(v.parent!=-1){
    Queue* p = (Queue*) malloc(sizeof(Queue));
    p->n = v.id-1;
    p->next = path;
    path=p;
    v=network[v.parent];
  }
  Queue* p = (Queue*) malloc(sizeof(Queue));
  p->n = v.id-1;
  p->next = path;
  path=p;
  return path;
}

void printQueue(Queue* path){
  Queue* current = path;
  while(current!=NULL){
    if(current->next==NULL){
      printf("%d", current->n + 1);
    }
    else{
      printf("%d ", current->n + 1);
    }
    current=current->next;
  }
  printf("\n");
}

void flow(Queue* path){
  Queue* current = path;
  int flow = min(network[0].bottleneck, network[path->n].prod);
  network[path->n].prod-=flow;
  if(network[path->n].prod==0){
    network[path->n].prod=-1;
  }
  while(current->next!=NULL){
    Edge* adj = network[current->n].head;
    while(adj->dest != current->next->n){ /*get flow thru edges*/
      adj=adj->next;
    }
    adj->flow+=flow;
    network[current->next->n].flow+=flow; /*update vertex flow*/
    current=current->next;
  }
}

int EdmondsKarp(){
  while(BFS()){
    Queue* path = getPath();
    flow(path);
    resetVisited();
  }
  return 1;
}

int minimalCut(){
  network2 = (Vertex*) malloc(nVert*sizeof(Vertex));
  int i;
  for(i=0;i<nVert;i++){
    network2[i].id=i+1;
    network2[i].prod=0;
    network2[i].parent=-1;
    network2[i].head=NULL;
    network2[i].bigger=0;
  }
  for(i=0;i<nVert;i++){
    Edge* adj = network[i].head;
    while(adj!=NULL){
      addEdge2(adj->dest,i,adj->cap-adj->flow);
      adj=adj->next;
    }
  }
  BFS2();
  if(sources_visited!=nFor){
    for(i=0;i<nVert;i++){
      if(network2[i].parent == -1 && !network2[i].bigger){
        Edge* adj = network[i].head;
        while(adj!=NULL){
          if(network2[adj->dest].parent >= 0 && network2[adj->dest].bigger==0){
            MinEdge* m = malloc (sizeof(MinEdge));
            MinEdge* current = minimal;
            MinEdge* previous = NULL;
            m->src = i;
            m->dest = adj->dest;
            if(minimal==NULL){
              m->next = NULL;
              minimal = m;
            }
            else{
              while(current!=NULL && m->src>current->src){
                previous=current;
                current=current->next;
              }
              while(current!=NULL && m->dest>current->dest){
                previous=current;
                current=current->next;
              }
              if(previous!=NULL){
                previous->next=m;
                m->next=current;
              }
              else{
                m->next=minimal;
                minimal=m;
              }
            }
          }
          adj=adj->next;
        }
      }
    }
  }
  return 1;
}

void BFS2(){
  Queue* q = (Queue*) malloc (sizeof(Queue));
  q->n = 0;
  q->next = NULL;
  visited2 = (Queue*) malloc (sizeof(Queue));
  visited2->n=0;
  visited2->next=NULL;
  network2[0].parent = 0;
  while(q!=NULL){
    Edge* adj = network2[q->n].head;
    while(adj!=NULL){
      if(network2[adj->dest].parent==-1 && adj->cap>0){
        if(adj->dest!=0 && adj->dest<=nFor){
          sources_visited++;
        }
        network2[adj->dest].parent=q->n;
        if(network[adj->dest].cap-network[adj->dest].flow > 0){
          queue(adj->dest,q);
          queue(adj->dest,visited2);
        }
        if(adj->dest>nFor && network[adj->dest].cap-network[adj->dest].flow==0){
          network2[adj->dest].bigger=1;
          if(bigger==NULL){
            bigger = (Queue*) malloc (sizeof(Queue));
            bigger->n = adj->dest;
            bigger->next = NULL;
          }
          else{
            Queue* a = (Queue*) malloc (sizeof(Queue));
            a->n=adj->dest;
            a->next=NULL;
            Queue* previous = NULL;
            Queue* current=bigger;
            while(current!=NULL && a->n>current->n){
              previous=current;
              current=current->next;
            }
            if(previous!=NULL){
              previous->next=a;
              a->next=current;
            }
            else{
              a->next=bigger;
              bigger=a;
            }
          }
        }
      }
      adj=adj->next;
    }
    q=pop(q);
  }
}

void printEdges(){
  MinEdge* current = minimal;
  while(current!=NULL){
    printf("%d %d\n", current->src +1, current->dest +1);
    current=current->next;
  }
}

int main(int argc, char const *argv[]) {
  parseInput();
  resetVisited();
  EdmondsKarp();
  printf("%d\n", network[0].flow);
  minimalCut();
  printQueue(bigger);
  printEdges();
  return 0;
}
