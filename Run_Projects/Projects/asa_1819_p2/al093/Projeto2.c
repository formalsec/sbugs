#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

struct Node{
    int idParent;
    int id;            /*Node's dest id*/
    int edgeCapacity;    /*Edge Capacity*/
    int flow;
    int invCapacity;
    struct Node* next;
};

struct AdjList{
    int val;
    int id;
    int height;
    int excess;
    int nChilds;
    int visited;
    int t;
    struct Node* head_out;
};

struct Net{
  int nProviders;        /*Number of providers*/
  int nSupplyStation;    /*Number of supply stations*/
  int nConnections;      /*Number of connections*/
  int nodesNumber;       /*Number of vertices*/
  int sourceID;
  struct AdjList* array; /*Array where will be stored linked lists representing net*/
};


struct nodeSet {
  int src;
  int dest;
  struct nodeSet* next;
};

struct output {
  struct nodeSet* h2;
  struct nodeSet* h3;
  struct nodeSet* o2;
  struct nodeSet* o3;
};


struct output* output;
struct nodeSet* cutEdge;
struct nodeSet* head;
struct Net* net;

int* list;

void printNet();

void addEdge(int src, int dest, int cap, int invcap) {

  struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

  newNode->idParent = src;
  newNode->id = dest;
  newNode->edgeCapacity = cap;
  newNode->invCapacity = invcap;
  net->array[src].nChilds += 1;
  newNode->next = net->array[src].head_out;
  net->array[src].head_out = newNode;

}

void initializeGraph() {
  int i;
  int aux = net->nProviders + net->nSupplyStation + 1; /*Index to create aux vertice*/

  net->array[net->sourceID - 1].head_out = NULL;
  net->array[net->sourceID - 1].id = net->sourceID - 1;
  net->array[net->sourceID - 1].height = net->nodesNumber+1;
  net->array[net->sourceID - 1].excess = 0;

  for(i = 0; i < net->nodesNumber; i++) {
    net->array[i].head_out = NULL;
    net->array[i].id = i;
    net->array[i].height = 0;
    net->array[i].excess = 0;
    net->array[i].visited = 0;
    net->array[i].t = 0;
  }

  for(i = 0; i < net->nodesNumber; i++) { /*Initialize graph*/

    if(i > 0 && i < net->nProviders + 1) { /*If the vertices are providers*/

      scanf("%d\n", &net->array[i].val);

      net->array[i].excess = net->array[i].val;

      addEdge(net->sourceID-1, i, net->array[i].val, 0);

      addEdge(i, net->sourceID-1, 0, net->array[i].val);

    }

    else if(i > net->nProviders && i < net->nProviders + net->nSupplyStation + 1) { /*If the vertices are supply stations*/

      scanf("%d\n", &net->array[i].val);

      addEdge(i, aux, net->array[i].val, 0);
      addEdge(aux, i, 0, net->array[i].val);

      aux++;

    }

  }

}

void createGraph() {
  int i;

  net = (struct Net*) malloc(sizeof(struct Net));

  scanf("%d %d %d", &net->nProviders, &net->nSupplyStation, &net->nConnections); /*Read from input num providers, supply stations and connections*/

  if(net->nProviders <= 0 || net->nSupplyStation < 0 || net->nConnections < 0) exit(1);

  net->nodesNumber = net->nProviders + net->nSupplyStation*2 + 1; /* 2 vertices for each supply station, hiper and source*/

  net->sourceID = net->nodesNumber + 1;

  net->array = (struct AdjList*)malloc((net->nodesNumber + 1)*sizeof(struct AdjList));

  initializeGraph();

  for(i = 0; i < net->nConnections; i++) { /*Add edges and capacities*/

    int src, dest, cap;

    scanf("%d %d %d", &src, &dest, &cap);

    if(src < 2 || dest < 1 || cap < 1) exit(1);

    if(src > net->nProviders + 1) { /*If the source vertice of edge is a supply station*/

      addEdge(src + net->nSupplyStation - 1, dest-1, cap, 0);
      addEdge(dest-1, src + net->nSupplyStation - 1, 0, cap);


    }

    else {

      addEdge(src-1, dest-1, cap, 0);
      addEdge(dest-1, src-1, 0, cap);

    }
  }

}

void moveToFront(int index){
  int aux = list[index];
  int i = 0;
  for(i = index; i > 0; i--) {
    list[i] = list[i - 1];
  }

  list[0] = aux;
}

struct Node* findInverse(int v, int u){
  struct Node* aux = net->array[v].head_out;

  while (aux) {
    if(aux->id == u) break;
    aux = aux->next;
  }

  return aux;

}

void push(int u, struct Node* v) {
  int send = MIN(net->array[u].excess, v->edgeCapacity - v->flow);
  v->flow += send;
  struct Node* aux = findInverse(v->id, u);
  aux->flow -= send;
  net->array[u].excess -= send;
  net->array[v->id].excess += send;
}

void relabel(int u) {
  int min = INT_MAX;
  struct Node* aux = net->array[u].head_out;

  while(aux) {

    if(aux->edgeCapacity - aux->flow > 0){
      min = MIN(min, net->array[aux->id].height);
      net->array[u].height = min + 1;
    }
    aux = aux->next;
  }
}

void discharge(int u) {

  struct Node* aux = net->array[u].head_out;

  /*printf("Discharging vertex %d\n", net->array[u].id+1);*/

  int n = 0;

  while(net->array[u].excess > 0) {

    /*printf("Excess vertex %d = %d\n", u+1, net->array[u].excess );*/


    if(n == net->array[u].nChilds) {
      /*printf("RELABEL\n");*/
      relabel(u);
      n = 0;
      /*printf("New height of %d = %d\n", u, net->array[u].height);*/
      aux = net->array[u].head_out;
    }

    else {
      /*printf("AUX ID: %d  || %d - %d > 0 && %d > %d\n", aux->id+1, aux->edgeCapacity, aux->flow, net->array[u].height, net->array[aux->id].height);*/
      if(aux->edgeCapacity - aux->flow > 0 && net->array[u].height > net->array[aux->id].height) {
        push(net->array[u].id, aux);
      }
      else {
        aux = aux->next;
        n++;
      }
    }

  }

}

void relabelToFront() {

  list = (int*)malloc((net->nodesNumber-1)*sizeof(int));
  int i;

  for(i = 0; i < net->nodesNumber - 1; i++){
    list[i] = i+1;
  }

  struct Node* aux = net->array[net->sourceID - 1].head_out;

  while (aux) {
    aux->flow = aux->edgeCapacity;
    struct Node* tmp = findInverse(aux->id, net->sourceID-1);
    tmp->flow = -aux->edgeCapacity;
    net->array[aux->id].excess = aux->edgeCapacity;
    net->array[net->sourceID-1].excess -= aux->edgeCapacity;
    aux = aux->next;
  }

  i = 0;

  while(i < net->nodesNumber - 1) {
    int u = list[i];
    int hgt = net->array[u].height;

    discharge(u);
    if (net->array[u].height > hgt) {
      moveToFront(i); /*Move vertice to the front of the list*/
      i = 1;
    }
    else {
      i++;
    }
  }
}

void addLL(int src, int dest, struct nodeSet** set, int mode) {
  struct nodeSet *newNode = (struct nodeSet*)malloc(sizeof(struct nodeSet));

  newNode->src = src;
  newNode->dest = dest;
  newNode->next = NULL;

  if((*set) == NULL) {
    *set = newNode;
    if(mode == 1) head = *set;
    else if(mode == 2) output->h2 = *set;
    else if(mode == 3) output->h3 = *set;
  }

  else{
    (*set)->next = newNode;
    *set = newNode;
  }

}

void DFS(int i) {

  struct Node* aux = net->array[i].head_out;

  net->array[i].visited = 1;
  net->array[i].t = 1;

  while(aux) {

    int tmp = aux->id;

    if(net->array[tmp].visited == 0) {
      if(aux->edgeCapacity == 0){
        if(aux->flow == -(aux->invCapacity)){
          addLL(aux->id, net->array[i].id, &cutEdge, 1); /*CORTE*/
          if(aux->next == NULL) return;
        }
        else {
          DFS(tmp);
        }
      }

      else {
        DFS(tmp);
      }
    }

    aux = aux->next;
  }

}

void printLL(struct nodeSet* set, int c){

  struct nodeSet* current = set;

  while(current){
    if(c == 0) printf("%d", current->src);
    else printf("%d %d\n", current->src, current->dest);
    current = current->next;
  }
}



void printNet(){
  int i;
  for(i = 0; i < net->nodesNumber + 1; i++) {
    struct Node* aux = net->array[i].head_out;

    printf("\nAdjacency list of vertex %d h(%d) E(%d) t(%d)\n", i+1, net->array[i].height,net->array[i].excess, net->array[i].t);

    while (aux) {
      printf("-> %d (%d/%d) INV(%d)", (aux->id)+1, aux->flow, aux->edgeCapacity, aux->invCapacity);
      aux = aux->next;
      if(i==5){

      }
    }
    printf("\n");

  }

}


void handleEdge(struct nodeSet** set) {

  while(*set){
    if((*set)->src > net->nProviders && (*set)->src < net->nProviders + net->nSupplyStation + 1){ /*If source is a supply station*/
      addLL((*set)->src+1, 0, &output->o2,2);
    }
    else if((*set)->src > net->nProviders + net->nSupplyStation && (*set)->src < net->sourceID - 1){
      (*set)->src = (*set)->src - net->nSupplyStation;
      addLL((*set)->src+1, (*set)->dest+1, &output->o3,3);
    }
    else if((*set)->src > 0 && (*set)->src < net->nProviders+1){
      addLL((*set)->src+1, (*set)->dest+1, &output->o3,3);
    }
    (*set) = (*set)->next;
  }

}

void initializeOutput() {
  output = (struct output*)malloc(sizeof(struct output));

  output->o2 = NULL;
  output->o3 = NULL;

}

void splitLists(struct nodeSet* s, struct nodeSet** front, struct nodeSet** back){
  struct nodeSet* fast;
  struct nodeSet* slow;
  slow = s;
  fast = s->next;

  if(s == NULL || s->next == NULL){
    *front = s; /*&l*/
    *back = NULL; /*&r*/
  }

  else{

    while (fast != NULL) {
      fast = fast->next;
      if (fast != NULL) {
        slow = slow->next;
        fast = fast->next;
      }
    }

    *front = s; /*l*/
    *back = slow->next; /*r*/
    slow->next = NULL;

  }

}


struct nodeSet* merge(struct nodeSet* l, struct nodeSet* r) {

  struct nodeSet* res = NULL;

  if (l == NULL) return r;

  else if (r == NULL) return l;

  if (l->src < r->src) {
    res = l;
    res->next = merge(l->next, r);
  }
  else if(l->src == r->src) {
    if (l->dest < r->dest) {
      res = l;
      res->next = merge(l->next, r);
    }
    else {
      res = r;
      res->next = merge(l, r->next);
    }
  }
  else {
    res = r;
    res->next = merge(l, r->next);
  }
  return res;

}

void mergeSort(struct nodeSet** set) {

  struct nodeSet* h = *set;
  struct nodeSet* l;
  struct nodeSet* r;

  if(h == NULL || h->next == NULL){
    return;
  }
  splitLists(h, &l, &r);

  mergeSort(&l);
  mergeSort(&r);

  *set = merge(l, r);
}



int main(){

  createGraph();

  relabelToFront();

  cutEdge = NULL;

  DFS(0);

  mergeSort(&head);

  initializeOutput();

  printf("%d\n", net->array[0].excess);

  handleEdge(&head);

  if(output->h2 != NULL) {
    printLL(output->h2, 0);
    printf("\n");
  }
  else printf("\n");

  if(output->h3 != NULL) {
    printLL(output->h3, 1);
  }

  return 0;
}
