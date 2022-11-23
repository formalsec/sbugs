#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct VNode{
  int vert;
  struct VNode* next;
}VNode;

typedef struct Alists{
  int length;
  VNode** lists;
}Alists;

typedef struct SCC{
  int nverts;
  int* elements;
  int num;
  int grade;
}SCC;

typedef struct stack{
  int length;
  VNode* top;
}stack;

int* gradearray;
int* SCCassarray;
SCC** SCCarray;
int SCCnum;

VNode* newNode(int vert);
Alists* newAlist(int len);
SCC* newSCC(int num, int* elements, int nverts);
void freeNodes(VNode* node);
void freeAlist(Alists* al);
void freeSCC(SCC* scc);
void setSCCgrade(int grade, SCC* scc);
void addEdge(int out, int in, Alists* al);
void push(stack* st, int vert);
int pop(stack* st);
stack* newstack();
void freestack();
void printAdjacencies(Alists* al);
void Tarjan_Visit(int vertex, Alists* graph, int* visited, stack* l, int* stackoccupancy, int* d, int* low, int length);
void SCC_Tarjan(Alists* graph);
void init_SCCarrays(int length);
void init_gradearray(int length);
void free_gradearray();
void free_SCCarrays();
void addSCC(int* elements, int length, int grade);
void printSCC(SCC* scc);
Alists* convert2dag(Alists* al);
void gradeDFS(Alists* dag);
void gradeDFS_visit(int vertex, Alists* dag, int* time, int* color, int* pi, int* d, int* f);


VNode* newNode(int vert){
  if(vert<0){
    perror("newNode: invalid params\n");
    exit(0);
  }
  VNode* nn = (VNode*)can_fail_malloc(sizeof(VNode));
  nn->vert = vert;
  nn->next = NULL;
  return nn;
}

Alists* newAlist(int len){
  if(len<1){
    perror("newAlist: invalid params\n");
    exit(0);
  }
  Alists* nl = (Alists*)can_fail_malloc(sizeof(Alists));
  nl->lists = (VNode**)can_fail_malloc(sizeof(VNode*)*len);
  nl->length = len;
  int i = 0;
  for(i = 0; i < len; i++){
    nl->lists[i] = newNode(i);
  }
  return nl;
}

SCC* newSCC(int num, int* elements, int nverts){
  if(num<0 || elements == NULL || nverts<1){
    perror("newSCC: invalid params\n");
    exit(0);
  }
  SCC* nscc = (SCC*)can_fail_malloc(sizeof(SCC));
  nscc->nverts = nverts;
  nscc->elements = (int*)can_fail_malloc(sizeof(int)*nverts);
  nscc->num = num;
  nscc->grade = -1;
  int i = 0;
  for(i = 0; i < nverts; i++){
    nscc->elements[i] = elements[i];
  }
  return nscc;
}

void setSCCgrade(int grade, SCC* scc){
  if(grade<0){
    perror("setSCCgrade: invalid params\n");
    exit(0);
  }
  scc->grade = grade;
}

void addEdge(int out, int in, Alists* al){
  if(al == NULL || out<0 || out>=al->length || in<0 || out>=al->length){
    perror("addEdge: invalid params\n");
    exit(0);
  }

  if(in == out){
    return;
  }

  VNode* curr = al->lists[out];

  while(curr->next != NULL && curr->vert != in){
    curr = curr->next;
  }

  if(curr->vert != in)
    curr->next = newNode(in);

}

void freeAlist(Alists* al){
  VNode* curr = NULL;
  int i = 0;
  for(i = 0; i < al->length; i++){
    curr = al->lists[i];
    freeNodes(curr);
  }
  free(al->lists);
  free(al);
}

void freeSCC(SCC* scc){
  if(scc == NULL)
    return;
  free(scc->elements);
  free(scc);
}

void freeNodes(VNode* node){
  if(node == NULL)
    return;
  VNode* curr = node;
  VNode* next = NULL;
  while(curr != NULL){
    next = curr->next;
    free(curr);
    curr = next;
  }
}

void push(stack* st, int vert){
  VNode* nnode = newNode(vert);
  nnode->next = st->top;
  st->top = nnode;
  st->length = (st->length + 1);
}

int pop(stack* st){
  if(st->length<1){
    perror("pop: stack empty\n");
    exit(0);
  }
  VNode* popped = st->top;
  int ret = popped->vert;
  st->top = (st->top)->next;
  free(popped);
  st->length--;
  return ret;
}

stack* newstack(){
  stack* newst = (stack*)can_fail_malloc(sizeof(stack));
  newst->length = 0;
  newst->top = NULL;
  return newst;
}

void freestack(stack* st){
  VNode* curr = st->top;
  VNode* next = NULL;
  while(curr != NULL){
    next = curr->next;
    free(curr);
    curr = next;
  }
  free(st);
}

void printAdjacencies(Alists* al){
  int length = al->length;
  VNode* curr = NULL;
  int i = 0;
  for(i = 0; i < length; i++){
    curr = al->lists[i];
    printf("printing %d:\n", i);
    while(curr->next!=NULL){
      curr = curr->next;
      printf("  %d\n", curr->vert);

    }
  }
}

void SCC_Tarjan(Alists* graph){
  int visited = 0;
  stack* l = newstack();
  int length = graph->length;
  int* d = (int*)can_fail_malloc(sizeof(int)*length);
  int* low= (int*)can_fail_malloc(sizeof(int)*length);
  int* stackoccupancy = (int*)can_fail_malloc(sizeof(int)*length);
  int i = 0;
  for(i = 0; i < length; i++){
    d[i] = INT_MAX;
    low[i] = INT_MAX;
    stackoccupancy[i] = 0;
  }
  for(i = 0; i < length; i++){
    if(d[i]==INT_MAX){
      Tarjan_Visit(i, graph, &visited, l, stackoccupancy, d, low, length);
    }
  }

  freestack(l);
  free(d);
  free(low);
  free(stackoccupancy);
}

int min(int a, int b){
  if(a < b)
    return a;
  else return b;
}

int max(int a, int b){
  if(a > b)
    return a;
  else return b;
}

void init_SCCarrays(int length){
  SCCnum = 0;
  SCCarray = (SCC**)can_fail_malloc(sizeof(SCC*)*length);
  SCCassarray = (int*)can_fail_malloc(sizeof(int)*length);
  int i = 0;
  for(i = 0; i < length; i++){
    SCCassarray[i] = -1;
    SCCarray[i] = NULL;
  }
}

void init_gradearray(int length){
  gradearray = (int*)can_fail_malloc(sizeof(int)*length);
}

void free_gradearray(){
  free(gradearray);
}

void free_SCCarrays(){
  free(SCCassarray);
  int i = 0;
  for(i = 0; i < SCCnum; i++){
    freeSCC(SCCarray[i]);
  }
  free(SCCarray);

}

void addSCC(int* elements, int length, int grade){
  SCCarray[SCCnum] = newSCC(SCCnum, elements, length);
  setSCCgrade(grade, SCCarray[SCCnum]);
  int i = 0;
  for(i = 0; i < length; i++){
    SCCassarray[elements[i]]=SCCnum;
  }
  SCCnum++;
}

void Tarjan_Visit(int vertex, Alists* graph, int* visited, stack* l, int* stackoccupancy, int* d, int* low, int length){
  d[vertex] = *visited;
  low[vertex] = *visited;
  *visited = *visited + 1;
  int* sccelems = (int*)can_fail_malloc(sizeof(int)*length);
  int scclen = 0;
  push(l, vertex);
  int v = -1;
  int grademax = -1;
  stackoccupancy[vertex] = 1;
  VNode* curr = (graph->lists[vertex])->next;
  while(curr != NULL){
    if(d[curr->vert]==INT_MAX || stackoccupancy[curr->vert]==1){
      if(d[curr->vert]==INT_MAX){
        Tarjan_Visit(curr->vert, graph, visited, l, stackoccupancy, d, low, length);
      }
      low[vertex] = min(low[vertex], low[curr->vert]);
    }

    curr = curr->next;

  }
  if(d[vertex] == low[vertex]){
    while(vertex != v){

      v = pop(l);
      stackoccupancy[v] = 0;
      sccelems[scclen++]=v;
      grademax = max(grademax, gradearray[v]);
      SCCassarray[v] = SCCnum;
    }
    addSCC(sccelems, scclen, grademax);
  }
  free(sccelems);
}

Alists* convert2dag(Alists* al){
  Alists* converted = newAlist(SCCnum);
  int i = 0;
  for(i = 0; i < al->length; i++){
    VNode* curr = (al->lists[i])->next;
    while(curr != NULL){
      addEdge(SCCassarray[i], SCCassarray[curr->vert], converted);
      curr = curr->next;
    }
  }
  return converted;
}

void printSCC(SCC* scc){
  printf("printing SCC %d with grade %d:\n", scc->num, scc->grade);
  int i = 0;
  for(i = 0; i < scc->nverts; i++){
    printf("    %d\n", scc->elements[i]);
  }
}

void gradeDFS(Alists* dag){
  int daglen = dag->length;
  int* d  = (int*)can_fail_malloc(sizeof(int)*daglen);
  int* pi  = (int*)can_fail_malloc(sizeof(int)*daglen);
  int* color  = (int*)can_fail_malloc(sizeof(int)*daglen);
  int* f = (int*)can_fail_malloc(sizeof(int)*daglen);
  int time = 1;
  int i = 0;

  for(i = 0; i < daglen; i++){
    d[i] = -1;
    pi[i] = -1;
    color[i] = 2;
    f[i] = -1;
  }

  for(i = 0; i < daglen; i++){
    if(color[i] == 2){
      gradeDFS_visit(i, dag, &time, color, pi, d, f);
    }
  }

  free(d);
  free(pi);
  free(color);
  free(f);
}
void gradeDFS_visit(int vertex, Alists* dag, int* time, int* color, int* pi, int* d, int* f){
  color[vertex] = 1;
  d[vertex] = *time;
  ++(*time);
  VNode* curr = (dag->lists[vertex])->next;
  while(curr != NULL){
    if(color[curr->vert] == 2){
      pi[curr->vert] = vertex;
      gradeDFS_visit(curr->vert, dag, time, color, pi, d, f);
    }
    setSCCgrade(max(SCCarray[vertex]->grade, SCCarray[curr->vert]->grade), SCCarray[vertex]);
    curr = curr->next;
  }
}




int main(int argc, char* argv[]){

  int verts = 0;
  int edges = 0;
  int curgrade = 0;
  int curin = -1;
  int curout = -1;
  scanf("%d,%d", &verts, &edges);

  Alists* al = newAlist(verts);
  init_gradearray(verts);

  int i = 0;
  for(i = 0; i < verts; i++){
    scanf("%d", &curgrade);
    gradearray[i] = curgrade;
  }

  for(i = 0; i < edges; i++){
    scanf("%d %d", &curout, &curin);
    addEdge((curout-1), (curin-1), al);
  }

  init_SCCarrays(verts);
  SCC_Tarjan(al);
  Alists* converted = convert2dag(al);
  gradeDFS(converted);
  for(i = 0; i < verts; i++){
    printf("%d\n", SCCarray[SCCassarray[i]]->grade);
  }

  freeAlist(al);
  freeAlist(converted);
  free_SCCarrays();
  free_gradearray();

  return 0;

}
