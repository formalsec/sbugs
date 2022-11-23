#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/******************************************************************************/
/*                                  Grupo 114                                 */
/*                            Carolina Marçal 92417                           */
/*                            Sofia Rodrigues 92558                           */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define NONE -1
#define WHITE 0 /*vertex never visited*/
#define GRAY 1 /*vertex visited*/
#define BLACK 2 /*vertex cant be visited anymore*/

int nStreets = 0, nAvenues = 0, nSuperM = 0, nCitizens = 0, nVertexs = 0;
int head, tail;

typedef struct vertex{
  int colour;
  int citizen; /* != -1 if it is a citizen */
  int supermarket; /* != -1 if it is a citizen */
  int nNeighbours;
  int* neighbours;
  int* flow;
  int parent;
} Vertex;

Vertex* vertexList;
int* queue; /* bfs' queue */

/* finds vertex index */
int findVertexIndex(int avenue, int street){
  return 2*((avenue-1)*nStreets+street-1);
}

void initialize(){
  int i, j, index;

  for(i=1; i<=nAvenues; i++){
    for(j=1; j<=nStreets; j++){

      /*vertex in*/
      index = findVertexIndex(i,j);
      vertexList[index].colour = WHITE;
      vertexList[index].citizen = NONE;
      vertexList[index].supermarket = NONE;
      vertexList[index].neighbours = (int*)can_fail_malloc(sizeof(int));
      vertexList[index].flow = (int*)can_fail_malloc(sizeof(int));
      vertexList[index].flow[0] = 0;
      vertexList[index].neighbours[0] = index+1;
      vertexList[index].nNeighbours = 1;
      vertexList[index].parent = NONE;

      /*vertex out*/
      index++;
      vertexList[index].colour = WHITE;
      vertexList[index].citizen = NONE;
      vertexList[index].supermarket = NONE;
      vertexList[index].flow = NULL;
      vertexList[index].neighbours = NULL;
      vertexList[index].nNeighbours = 0;
      vertexList[index].parent = index -1;
    }
  }
}

void initializeSourceSink(){
  int sourceIndex, sinkIndex;
    sourceIndex = nVertexs;
    vertexList[sourceIndex].colour = WHITE;
    vertexList[sourceIndex].citizen = NONE;
    vertexList[sourceIndex].supermarket = NONE;
    vertexList[sourceIndex].flow = NULL;
    vertexList[sourceIndex].neighbours = NULL;
    vertexList[sourceIndex].nNeighbours = 0;
    vertexList[sourceIndex].parent = NONE;

    sinkIndex = nVertexs +1;
    vertexList[sinkIndex].colour = WHITE;
    vertexList[sinkIndex].citizen = NONE;
    vertexList[sinkIndex].supermarket = NONE;
    vertexList[sinkIndex].flow = NULL;
    vertexList[sinkIndex].neighbours = NULL;
    vertexList[sinkIndex].nNeighbours = 0;
    vertexList[sinkIndex].parent = NONE;
}

/* adds neighbours to vertex's neighbours list */
void addNeighbour(int index, int indexN){

  vertexList[index].nNeighbours ++;
  vertexList[index].neighbours = (int*)can_fail_realloc(vertexList[index].neighbours, sizeof(int)*vertexList[index].nNeighbours);
  vertexList[index].flow = (int*)can_fail_realloc(vertexList[index].flow, sizeof(int)*vertexList[index].nNeighbours);
  vertexList[index].neighbours[vertexList[index].nNeighbours-1] = indexN;
  vertexList[index].flow[vertexList[index].nNeighbours-1] = 0;
}

/* finds vertex's neighbours */
void findNeighboursOut(){
  int d, avenue, street, aa, ss, index, indexN;
  int dAvenues[] = {-1, +1, 0, 0};
  int dStreets[] = {0, 0, -1, +1};

  for (avenue = 1; avenue <= nAvenues; avenue++){
    for (street = 1; street <= nStreets; street++){
      for (d = 0; d < 4; d++){
        aa = avenue + dAvenues[d];
        ss = street + dStreets[d];

        if (!(aa <= 0 || ss <= 0 || ss > nStreets || aa > nAvenues)){
          index = findVertexIndex(avenue, street);
          indexN = findVertexIndex(aa, ss);
          addNeighbour(index+1, indexN);
        }
      }
    }
  }
}

/* finds neighbour's vertex's index*/
int findNeighbourIndex(int pai, int filho){
  int i;
  for (i=0; i<vertexList[pai].nNeighbours;i++){
    if(vertexList[pai].neighbours[i] == filho){
      return i;
    }
  }
  return -1;
}

void enqueue(int vertexIndex){
    queue[tail] = vertexIndex;
    tail++;
    vertexList[vertexIndex].colour = GRAY;
}

int dequeue(){
    int vertexIndex = queue[head];
    head++;
    vertexList[vertexIndex].colour = BLACK;
    return vertexIndex;
}

int bfs(){
    int source = nVertexs;
    int sink = nVertexs+1;
    int i, vertexIndex;
    for (i = 0; i < nVertexs +2; i++){
        vertexList[i].colour = WHITE;
    }
    head = tail = 0;
    enqueue(source);
    while (head != tail){
        vertexIndex = dequeue();
        for (i = 0; i < vertexList[vertexIndex].nNeighbours; i++){

            /* checks if vertex was already visited and if the edge has flow 0 */
            if (vertexList[vertexList[vertexIndex].neighbours[i]].colour == WHITE && vertexList[vertexIndex].flow[i]==0){
                /* checks if neighbour is sink */
                if(vertexList[vertexIndex].neighbours[i] == nVertexs+1){
                  vertexList[vertexList[vertexIndex].neighbours[i]].parent = vertexIndex;
                  return 1;
                }
                /* checks if neighbour isn't a citizen and if vertex isn't sink */
                else if(vertexList[vertexList[vertexIndex].neighbours[i]].citizen != NONE && vertexIndex != nVertexs){
                  continue;
                }
                else{
                  enqueue(vertexList[vertexIndex].neighbours[i]);
                  vertexList[vertexList[vertexIndex].neighbours[i]].parent = vertexIndex;
                }
            }
        }
    }
    return vertexList[sink].colour == BLACK;
}

int edmondsKarp(){
    int sink = nVertexs+1;
    int i, o, index, max_flow = 0;

    while (bfs()){
        for (i = sink; vertexList[i].parent != nVertexs; i = vertexList[i].parent){
          o = vertexList[i].parent;
          index = findNeighbourIndex(o, i);
          vertexList[o].flow[index] = 1;
          addNeighbour(i, o);
        }
        max_flow ++;
    }
    return max_flow;
}

int main() {
  int i, street, avenue, index;

  scanf("%d %d\n%d %d", &nAvenues, &nStreets, &nSuperM, &nCitizens);

  nVertexs = 2*nAvenues*nStreets;

  vertexList = (Vertex*)can_fail_malloc(sizeof(Vertex)*(nVertexs +2));
  queue = (int*)can_fail_malloc(sizeof(int)*(nVertexs +2));

  initialize();
  initializeSourceSink();
  findNeighboursOut();

  for (i=0; i<nSuperM; i++){
    scanf("%d %d",&avenue, &street);
    index = findVertexIndex(avenue, street);
    vertexList[index].supermarket = i;
    free(vertexList[index+1].neighbours);
    vertexList[index+1].neighbours = (int*)can_fail_malloc(sizeof(int));
    vertexList[index+1].neighbours[0] = nVertexs +1;
    vertexList[index+1].nNeighbours = 1;
  }

  for (i=0; i<nCitizens; i++){
    scanf("%d %d",&avenue, &street);
    index = findVertexIndex(avenue, street);
    if (vertexList[index].citizen == NONE){
      addNeighbour(nVertexs, index);
      vertexList[index].citizen = i;
    }
  }
  printf("%d\n",edmondsKarp() );

  for (i = 0; i < nVertexs +2; i++){
      free(vertexList[i].neighbours);
      free(vertexList[i].flow);
  }
  free(queue);
  free(vertexList);

  return 0;
}
