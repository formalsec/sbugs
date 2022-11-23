#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*PROJETO 1 DE ASA*/
/*84721 - GONCALO J G CRUZ*/
#include <stdio.h>
#include <stdlib.h>

#define HIPER 0
#define SUPLIER 1
#define STATION 2

/*GLOBAL VARIABLES*/
int fSupliers = 0; /*numero de fornecedores*/
int eStations = 0; /*numero de estacoes*/
int tLinks = 0; /*numero de ligacoes*/
int nVertex = 0; /*numero de fornecedores + estacoes*/

/*STRUCTURES*/
struct Vertex {
  int id;
  int type;
  int capacity;
  struct Vertex *next;
};

struct Link {
  int source;
  int destination;
  int linkCapacity;
  struct Link* nextLink;
};

struct Network {
  int nVertex;
  int tLinks;
  struct Vertex** vertexList;
};

/*CREATE VERTEX*/
struct Vertex* createVertex(int id) {
  /*create a Vertex*/
  struct Vertex* newVertex;
  newVertex = (struct Vertex*)can_fail_malloc(sizeof(struct Vertex));
  /*error message in case of failure*/
  if(newVertex == NULL)
  {
      printf("Error creating a new Vertex.\n");
      exit(0);
  }
  /*set values*/
  newVertex->id = id;
  if (id == 1) {
    newVertex->type = HIPER;
  }
  else if (id > 2 && id <= fSupliers+1)  {
    newVertex->type = SUPLIER;
  }
  else if (id > fSupliers+1 && id <= nVertex) {
    newVertex->type = STATION;
  }
  newVertex->capacity = 0;
  newVertex->next = NULL;
  /*return the new Vertex*/
  return newVertex;
}

/*CREATE NETWORK*/
struct Network* createNetwork(int nVertex, int tLinks) {
  /*create a network*/
  struct Network* network = can_fail_malloc(sizeof(struct Network));
  /*set number of routers in the network*/
  network->nVertex = nVertex;
  network->tLinks = tLinks;
  /*allocate enough memory for the amount of routers*/
  network->vertexList = can_fail_malloc((nVertex+1) * sizeof(struct Vertex*));
  int i;
  /*initialize variables*/
  for (i = 1; i <= (nVertex+1); i++) {
    struct Vertex* newVertex = createVertex(i);
    network->vertexList[i] = newVertex;
  }
  /*return new Network*/
  return network;
}

/*[DEBUGGING] PRINT NETWORK: print network created*/
void printNetwork(struct Network* network) {
  int i;
  printf("\t------------------------------\n");
  for (i = 1; i <= network->nVertex; i++) {
    struct Vertex* auxVertex = network->vertexList[i];
    /*printf("i: %d e fSupliers(+1): %d\n", i, fSupliers+1);*/
    if(1 < i && i <=fSupliers+1){
      printf("\n\t[SUPLIER] ");
    }
    else if (i > fSupliers+1) {
      printf("\n\t[STATION] ");
    }
    else{
      printf("\n\t[HIPER] ");
    }
    printf("Adjacency list of vertex %d\n\t", i);
    while (auxVertex) {
      printf("%d -> ", auxVertex->id);
      auxVertex = auxVertex->next;
    }
    printf("NULL\n");
  }
  printf("\t------------------------------\n");
}

void printLinksINFO(struct Link* head) {
  while (head) {
    printf("\tLink de %d para %d com capacidade %d\n", head->source, head->destination, head->linkCapacity);
    head = head->nextLink;
  }
}
/*****************************************************/

void addLink(struct Network* network, int src, int dest, int cap) {
  struct Vertex* newVertex = createVertex(dest);
  struct Vertex* auxVertex = network->vertexList[src];
  while (auxVertex->next != NULL) {
    auxVertex = auxVertex->next;
  }
  auxVertex->next = newVertex;
}

struct Link* getLink (int src, int dest) {

}

int getCapacity (int src, int dest) {
  return getLink(src, dest)->linkCapacity;
}

/*MAIN*/
int main() {
  /*ler f (supliers) e (stations) t (links) e guardar em variaveis globais*/
  scanf("%d %d %d", &fSupliers, &eStations, &tLinks);
  nVertex = fSupliers + eStations + 1;
  struct Network* network = createNetwork(nVertex, tLinks);
  struct Link* head = NULL;
  if (fSupliers <= 0 || eStations < 0 || tLinks < 0) {
    exit(1);
  }
  int i;
  /*ler capacidade de cada suplier*/
  for (i = 2; i <= fSupliers+1; i++) {
    if (i < fSupliers+1) {
      scanf("%d ", &(network->vertexList[i]->capacity));
    }
	  else if (i == fSupliers+1) {
      scanf("%d", &(network->vertexList[i]->capacity));
    }
  }
  /*ler capacidade de cada station*/
  for (i = fSupliers+2; i <= nVertex; i++) {
    if (i < nVertex) {
      scanf("%d ", &(network->vertexList[i]->capacity));
    }
	  else if (i == nVertex) {
      scanf("%d", &(network->vertexList[i]->capacity));
    }
  }
  /*ler as ligacoes*/
  int auxSRC, auxDEST, auxCAP;
  for (i = 1; i <= tLinks; i++) {
    scanf("%d %d %d", &auxSRC, &auxDEST, &auxCAP);
    addLink(network, auxSRC, auxDEST, auxCAP);
    struct Link* newLink = can_fail_malloc(sizeof(struct Link));
    newLink->source = auxSRC;
    newLink->destination = auxDEST;
    newLink->linkCapacity = auxCAP;
    newLink->nextLink = head;
    head = newLink;
  }

  /*PRINTS**********************************************
  printf("\n\t----------- PRINTS -----------\n");
  printf("\tSUPLIERS:%d STATIONS:%d LINKS:%d\n", fSupliers, eStations, tLinks);
  printf("\tNumero de Vertex: %d\n", nVertex);
  printf("\t------------------------------\n");
  for (i = 2; i <= fSupliers+1; i++) {
    printf("\t[%d]Fornecedor %d tem capacidade: %d\n", i, i-1, network->vertexList[i]->capacity);
  }
  for (i = fSupliers+2; i <= nVertex; i++) {
    printf("\t[%d]Estacao %d tem capacidade: %d\n", i, i-(1+fSupliers), network->vertexList[i]->capacity);
  }
  printNetwork(network);
  printLinksINFO(head);
  printf("\n");
  *****************************************************/
  return 0;
}

/*LINKS
https://fenix.tecnico.ulisboa.pt/downloadFile/282093452059672/p1.pdf


[inspiracao 2] http://www.aduni.org/courses/algorithms/courseware/handouts/Reciation_09.html
https://gist.github.com/amici-fos/35d7bb1b4cdb0e4854bb3fa437335a1f
https://www.youtube.com/watch?v=hmIrJCGPPG4
https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/*/
