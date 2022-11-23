#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INFINITE 1111
#define MAX_INPUT 100
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct vertix{
    int numCidadaos;
    int numSupermercados;
    int numAvenida;
    int numRua;
} Vertix;

typedef struct lstNode{
    int dest_vertix;
    int val;
    struct lstNode *nextNode;
} LstNode;

int head, tail, *q, *color, *pred, *seen;
LstNode **capacity;
Vertix *vertices;

LstNode* newNode(int vertix, int val)
{
    LstNode* p = can_fail_malloc(sizeof(LstNode));
    if (NULL != p) {
        p->dest_vertix = vertix;
        p->val = val;
        p->nextNode  = NULL;
    }
    return p;
}

void printList(LstNode **list, int size){
  int i;
  LstNode *nodeAux = NULL;
  
  for (i = 0; i < size; i++){
    for (nodeAux = list[i]; nodeAux != NULL; nodeAux = nodeAux->nextNode){
      printf("vertix [%d] -> vertix [%d]\n", i, nodeAux->dest_vertix);
    }
  }
}

int inArray(int *array, int size, int val){
  int i = 0;

  for (i = 0; i < size; i++){
    if(array[i] ==val){
      return 1;
    }
  }
  return 0;
}

void insertNode(LstNode** lstAdjacencias, int vertix, LstNode *node){
    LstNode *auxNode = NULL;
    if (lstAdjacencias[vertix] == NULL){
        lstAdjacencias[vertix] = node;
        return;
    }
    else{
        for (auxNode = lstAdjacencias[vertix]; auxNode->nextNode != NULL; auxNode = auxNode->nextNode);
        auxNode->nextNode = node;
        return;
    }
}

void deleteNode(LstNode **head_ref, int key) 
{ 
  LstNode *temp = *head_ref, *prev; 
  
  if (temp != NULL && temp->dest_vertix == key) 
  { 
    *head_ref = temp->nextNode;   
    free(temp);              
    return; 
  } 
  
 
  while (temp != NULL && temp->dest_vertix != key) 
  { 
    prev = temp; 
    temp = temp->nextNode; 
  } 
  
     
  if (temp == NULL) return; 
  
  
  prev->nextNode = temp->nextNode; 
  
  free(temp); 
} 

void freeList(LstNode *head){
    LstNode *auxNode = NULL, *nextNodeAux = NULL;
    if (head == NULL){
        return;
    }
    auxNode = head;
    nextNodeAux = auxNode->nextNode;
    while(nextNodeAux != NULL){
        free(auxNode);
        auxNode = nextNodeAux;
        nextNodeAux = nextNodeAux->nextNode;
    }
    free(auxNode);
}

void freeLstAdjacencias(LstNode **lstAdjacencias, int size){
    int i;
    for (i = 0; i < size; i++){
        freeList(lstAdjacencias[i]);
    }
    free(lstAdjacencias);
}

void display(int **graph, int size) {
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            printf("%4d", graph[i][j]);
        printf("\n");
    }
}

int procuraVal(LstNode **hashtableHeads, int origem, int dest){
    LstNode *nodeAux = NULL;

    for (nodeAux = hashtableHeads[origem]; nodeAux != NULL; nodeAux = nodeAux->nextNode){
        if (dest == nodeAux->dest_vertix){
          return nodeAux->val;
        }
    }
    return 0;
}

void alteraVal(LstNode **hashtableHeads, int origem, int dest, int size){
  LstNode *nodeAux = NULL;

  deleteNode(&hashtableHeads[origem], dest);

  nodeAux = newNode(origem, 1);

  if (nodeAux != NULL){
    insertNode(capacity, dest, nodeAux);
  }

}

int min (int x, int y) {
    return x<y ? x : y;
}

void enqueue (int x) {
  q[tail] = x;
  tail++;
  color[x] = GRAY;
}

int dequeue () {
  int x = q[head];
  head++;
  color[x] = BLACK;
  return x;
}

int bfs (int start, int target, int size) {
  int u;
  LstNode *node1;

  for (u=0; u<size; u++) {
	  color[u] = WHITE;
  }

  head = tail = 0;

  enqueue(start);
  pred[start] = -1;

  while (head!=tail) {
    u = dequeue();
    if (u == target){
      return color[target]==BLACK;
    }
    for (node1 = capacity[u]; node1 != NULL; node1 = node1->nextNode){
      if (color[node1->dest_vertix]==WHITE){    
        enqueue(node1->dest_vertix);
	 	    pred[node1->dest_vertix] = u;
	    }
    }
  } 
  return color[target]==BLACK;
}

int max_flow (int source, int sink, int size) {
  int u, max_flow = 0, increment;
    
  while (bfs(source, sink, size)) {
	  increment = INFINITE;
	  for (u = size - 1; pred[u] >= 0; u = pred[u]) {
	    increment = min(increment, procuraVal(capacity, pred[u], u));
	  }
	  for (u = size - 1; pred[u] >= 0; u = pred[u]) {
      alteraVal(capacity, pred[u], u, size);
	  }
	  max_flow += increment;
  }
  return max_flow;
}

int main(){
  int i = 0, k, j, numAvenidas, numRuas, numCidadaos, numSupermercados, n1, n2, graphSize = 0, aux = 1, maxFlow, counter = 0;
  char s1[MAX_INPUT], s2[MAX_INPUT];

  scanf("%s %s", s1, s2);

  numAvenidas = atoi(s1);
  numRuas = atoi(s2);

  memset(s1, '\0', MAX_INPUT);
  memset(s2, '\0', MAX_INPUT);

  scanf("%s %s", s1, s2);

  numCidadaos = atoi(s2);
  numSupermercados = atoi(s1);

  graphSize = (numAvenidas*numRuas) + 2;

  vertices = (Vertix*) can_fail_malloc(sizeof(Vertix)*graphSize);
  memset(s1, '\0', MAX_INPUT);
  memset(s2, '\0', MAX_INPUT);

  seen = (int*) can_fail_malloc(sizeof(int)*((numAvenidas*numRuas) + 1));
  memset(seen, 0, sizeof(int)*((numAvenidas*numRuas) + 1)); 

  for (k = 1, i = 1; i < graphSize - 1; i++){

    if (aux > numAvenidas){
      aux = 1;
      k++;
    }

    vertices[i].numCidadaos = 0;
    vertices[i].numSupermercados = 0;
    vertices[i].numAvenida = aux++;
    vertices[i].numRua = k;
    seen[counter++] = i;
  } 

  for (i = 0; i < numSupermercados; i++){
    scanf("%s %s", s1, s2);

    n1 = atoi(s1);
    n2 = atoi(s2);

    vertices[((n2)*numAvenidas) - (numAvenidas - n1)].numSupermercados++;
  }

  for (i = 0; i < numCidadaos; i++){
    scanf("%s %s", s1, s2);

    n1 = atoi(s1) ;
    n2 = atoi(s2) ;
    
    vertices[((n2)*numAvenidas) - (numAvenidas - n1)].numCidadaos++;
  }

  graphSize = (2*(numAvenidas*numRuas)) + 2;
  capacity = (LstNode **) can_fail_malloc(sizeof(LstNode *)*graphSize);

  color = (int*) can_fail_malloc(sizeof(int)*graphSize);
  pred = (int*) can_fail_malloc(sizeof(int)*graphSize);
  q = (int*) can_fail_malloc(sizeof(int)*graphSize);

  memset(color, 0, graphSize);
  memset(pred, 0, graphSize);
  memset(q, 0, graphSize);
  
  for (i = 0; i < graphSize; i++){
    capacity[i] = NULL;
  }

  for (i = 1; i < (numAvenidas*numRuas) + 1; i++){
    LstNode *nodeAux;
    
    if ((vertices[i].numSupermercados > 0) ){
        for (j = 0; j < vertices[i].numSupermercados; j++){      
          LstNode *node1;
          node1 = newNode(graphSize - 1, 1);
          if (NULL != node1) {
            insertNode(capacity, (2*i), node1);
          }
        }  
      }  
    if ((vertices[i].numCidadaos > 0) ){
      for(j = 0; j < vertices[i].numCidadaos; j++){
        LstNode *node1;

        node1 = newNode((2*i) - 1, 1);
        if (NULL != node1) {
          insertNode(capacity, 0, node1);
        }
      }  
    }   
    
    nodeAux = newNode(2*i, 1);
    if (NULL != nodeAux) {
      insertNode(capacity, (2*i) - 1, nodeAux);
    }
    for(k = (i - 1); k < counter; k++){
      if (i != seen[k]){
        if (((vertices[i].numRua == vertices[seen[k]].numRua) && abs(i - seen[k]) == 1) || 
          ((vertices[i].numAvenida == vertices[seen[k]].numAvenida) && abs(i - seen[k]) == (numAvenidas))){
          LstNode *node1, *node2;


          node1 = newNode((2 * seen[k]) - 1, 1);
          node2 = newNode((2 *i) - 1, 1);

          if (NULL != node1) {
            insertNode(capacity, (2 * i), node1);
            insertNode(capacity, (2 * seen[k]), node2);
            }
          }
        }
    }
  }   

  maxFlow = max_flow(0, graphSize - 1, graphSize);
  printf("%d\n", maxFlow);

  freeLstAdjacencias(capacity, graphSize);
  free(vertices);
  free(color);
  free(q);
  free(pred);
  free(seen);

  return 0;
}    