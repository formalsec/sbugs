#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN(x,y) x<y ? x : y
#define MAX(x,y) x>y ? x : y

typedef struct Vertices{
  int id;
  int d_time;
  int parent;
  int low;
  int num_edges;
  int found;
  int* adjacent;
} Vertex;

/*PROTOTYPES*/

void readInput();
void freeNetwork();
void addEdge(int v1, int v2);
void dfs(Vertex v);
void reset_visited();
int isVisited(Vertex v);
void printSubredes();
void addBreakPointID(int id);
int checkChildren(Vertex v);
int getParentID(int id);
void removeVertex(int id);
void removeEdge(int id, int edge);
void removeBreakpoints();
int getVertexIndex(int id);
void findBreakingPoints(Vertex v);

/*globals*/
int current_time, nvert, nedges;
int nsubredes = 0;
int subrede_id=0;
int nr_visited = 0;
Vertex* graph;
int n_break_points=0;
int len_subrede=0;
int* break_points;
int* subredes;

int compare(const void* int1, const void* int2) {
   return *(int*)int1 - *(int*)int2;
}


int main() {
  readInput();
  /*calculate number of sub networks */
  int i;
  for(i = 0;i<nvert && nr_visited<nvert;i++){
    if(!isVisited(graph[i])){
      current_time=1;
      subrede_id=0;
      findBreakingPoints(graph[i]);
      subredes[nsubredes] = subrede_id;
      nsubredes++;
    }
  }
  printf("%d\n",nsubredes);
  qsort(subredes, nsubredes, sizeof(int), compare);
  printSubredes();
  printf("%d\n", n_break_points);
  removeBreakpoints();
  reset_visited();
  int biggest=0;
  for(i = 0;i<nvert && nr_visited<nvert;i++){
    if(!isVisited(graph[i])){
      len_subrede = 0;
      dfs(graph[i]);
      biggest=MAX(biggest,len_subrede);
    }
  }
  printf("%d\n", biggest);
  freeNetwork();
  return 0;
}

void findBreakingPoints(Vertex v){
  v.d_time = current_time++;
  v.low = v.d_time;
  graph[v.id-1]=v;
  nr_visited++;
  subrede_id = MAX(subrede_id, v.id);
  int i;
  for(i=0;i<v.num_edges;i++){
    Vertex neigh = graph[v.adjacent[i]-1];
    if(!isVisited(neigh)){
      neigh.parent = v.id;
      graph[neigh.id-1]=neigh;
      findBreakingPoints(neigh);
      neigh = graph[v.adjacent[i]-1];
      if(!v.found && v.parent!=0 && neigh.low >= v.d_time){
        v.found=1;
        graph[v.id-1]=v;
        addBreakPointID(v.id);
      }
      v.low = MIN(v.low, neigh.low);
      graph[v.id-1]=v;

    }
    else{
      if(v.parent != neigh.id){
        v.low = MIN(v.low, neigh.d_time);
        graph[v.id-1]=v;
      }
    }
  }
  if(v.parent==0){ /*/root check if break*/
    if(checkChildren(v)>1){
      addBreakPointID(v.id);
    }
  }
}

void dfs(Vertex v){
  v.d_time = 1;
  graph[getVertexIndex(v.id)]=v;
  len_subrede++;
  int i=0;
  i=0;
  while(i<v.num_edges){/*changed for (;i<len(v.adjacent);i++), confirm with ze*/
    int index = getVertexIndex(v.adjacent[i]);
    if (!isVisited(graph[index])){
      dfs(graph[index]);
    }
    i++;
  }
}

void readInput(){
  scanf("%d", &nvert);
  graph = (Vertex*) can_fail_malloc(nvert*sizeof(Vertex));
  break_points = (int*) can_fail_malloc(nvert*sizeof(int));
  subredes = (int*) can_fail_malloc(nvert*sizeof(int));
  int i;
  for(i=0;i<nvert;i++){
    graph[i].id=i+1;
    graph[i].d_time=0;
    graph[i].num_edges=0;
    graph[i].low=0;
    graph[i].found=0;
    graph[i].parent=0;
    graph[i].adjacent = (int*) can_fail_malloc(nvert*sizeof(int));
  }

  scanf("%d", &nedges);  
  int v1, v2;
  while(scanf("%d %d", &v1, &v2)>0){
    addEdge(v1,v2);
  }

}

void freeNetwork(){
  int i;
  for(i=0;i<nvert;i++){
    free(graph[i].adjacent);
  }
  free(break_points);
  free(subredes);
  free(graph);
}

void addEdge(int v1, int v2){
  Vertex c1, c2;
  c1 = graph[v1-1];
  c2 = graph[v2-1];

  c1.adjacent[c1.num_edges++]=v2;
  c2.adjacent[c2.num_edges++]=v1;
  graph[v1-1]=c1;
  graph[v2-1]=c2;
}

int isVisited(Vertex v){
  return v.d_time>0;
}

void reset_visited(){
  int i;
  for(i=0; i<nvert; i++){
    graph[i].d_time = 0;
  }
  nr_visited=0;
}





int checkChildren(Vertex v){
  int count=0;
  int i;
  for(i=0;v.adjacent[i]>0 && count<=1;i++){
    if(getParentID(v.adjacent[i])==v.id){
      count++;
    }
  }
  return count;
}

int getParentID(int id){
  return graph[id-1].parent;
}

void addBreakPointID(int id){
  break_points[n_break_points]=id;
  n_break_points++;
}

void printSubredes(){
  int i;
  for(i=0;i<nsubredes-1;i++){
    printf("%d ", subredes[i]);
  }
  printf("%d", subredes[i]);
  printf("\n");
}



void removeBreakpoints(){
  int i,j;
  for(i=0; i<n_break_points;i++){
    Vertex v = graph[getVertexIndex(break_points[i])];
    for(j=0; j<v.num_edges;j++){
      removeEdge(v.adjacent[j], v.id);
    }
  }
  for(i=0;i<n_break_points;i++){
    removeVertex(break_points[i]);
  }
}

void removeVertex(int id){
  int i;
  for(i=getVertexIndex(id); i<nvert; i++){
    graph[i]=graph[i+1];
  }
  nvert--;
}

void removeEdge(int id, int edge){
  int index = getVertexIndex(id);
  int i;    
  int jump = 0;
  for(i=0; i<graph[index].num_edges;i++){
    if(graph[index].adjacent[i] == edge){
      jump=1;
    }
    graph[index].adjacent[i]=graph[index].adjacent[i+jump];
  }
  graph[index].adjacent[i-1]=0;
  graph[index].num_edges--;
}

int getVertexIndex(int id){
  int i,r=0;
  for(i=0;i<nvert;i++){
    if(graph[i].id==id){
      r=i;
      break;
    }
  }
  return r;
}