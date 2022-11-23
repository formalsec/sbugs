#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*PROJETO 1 DE ASA*/
/*84721 - GONCALO J G CRUZ*/
#include <stdio.h>
#include <stdlib.h>


struct Router {
   int id;
   struct Router *next;
};

struct Network {
  int nRouters;
  int* visited;
  int* ap;
  int* identList;
  struct Router** adjLists;
};

/*GLOBAL VARIABLES*/
int nRouters = 0;
int mLinks = 0;
int auxSRC, auxDEST;
int routerMax = 1;
int nRouterMax = 0;
int nRouterMaxAUX = 0;
int subNetworks = 0;

/*AUXILIAR FUNCTIONS*/
int min(int a,int b)
{
    return(a<b?a:b);
}

/*CREATE ROUTER: create and set values in structure with 'id'*/
struct Router* createRouter(int id) {
  /*create a router*/
  struct Router* newRouter;
  newRouter = (struct Router*)can_fail_malloc(sizeof(struct Router));
  /*error message in case of failure*/
  if(newRouter == NULL)
  {
      printf("Error creating a new router.\n");
      exit(0);
  }
  /*set values*/
  newRouter->id = id;
  newRouter->next = NULL;
  /*return the new Router*/
  return newRouter;
}

/*CREATE NETWORK: creates a Network big enough for the number of Routers*/
struct Network* createNetwork(int routers) {
  /*create a network*/
  struct Network* network = can_fail_malloc(sizeof(struct Network));
  /*set number of routers in the network*/
  network->nRouters = routers;
  /*allocate enough memory for the amount of routers*/
  network->visited = can_fail_malloc((routers+1) * sizeof(int));
  network->adjLists = can_fail_malloc((routers+1) * sizeof(struct Router*));
  network->ap = (int*)can_fail_malloc(sizeof(int)*network->nRouters);
  int i;
  /*initialize variables*/
  for (i = 1; i <= routers; i++) {
    network->adjLists[i] = NULL;
    network->visited[i] = 0;
  }
  /*return new Network*/
  return network;
}

/*QUICKSORT: sorts list of identifiers using Quick Sort*/
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 

int partition (int identList[], int low, int high) 
{ 
    int pivot = identList[high]; 
    int i = (low - 1);   
    int j;
  
    for ( j = low; j <= high- 1; j++) 
    { 
        if (identList[j] <= pivot) 
        { 
            i++;
            swap(&identList[i], &identList[j]); 
        } 
    } 
    swap(&identList[i + 1], &identList[high]); 
    return (i + 1); 
} 

void quickSort(int identList[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[pi] is now
           at right place */
        int pi = partition(identList, low, high);

        quickSort(identList, low, pi - 1);
        quickSort(identList, pi + 1, high);
    }
}

/*UPDATE LINKS: update int list of links given 'src' and 'dest'*/
void addLink(struct Network* network, int src, int dest) {
  /*add link from src to dest*/
  struct Router* newRouter = createRouter(dest);
  newRouter->next = network->adjLists[src];
  network->adjLists[src] = newRouter;

  /*add link from dest to search*/
  newRouter = createRouter(src);
  newRouter->next = network->adjLists[dest];
  network->adjLists[dest] = newRouter;
}

/*[DEBUGGING] PRINT NETWORK: print network created*/
void printNetwork(struct Network* network) {
  int i;
  for (i = 1; i <= network->nRouters; i++) {
    struct Router* auxRouter = network->adjLists[i];
    printf("----------------------------\nAdjacency list of router %d\n", i);
    while (auxRouter) {
      printf("%d -> ", auxRouter->id);
      auxRouter = auxRouter->next;
    }
    printf("NULL\n");
  }
  printf("----------------------------\n");
}

/*DFS: Depth First Search Algorithm to determine sub-networks*/
int DFS(struct Network* network, int router, int routerMax) {
  struct Router* adjList = network->adjLists[router];
  struct Router* auxAdjList = adjList;
  network->visited[router] = 1;
  /*printf("Visited router %d\n", router);*/
  while(auxAdjList!=NULL) {
    int currentRouter = auxAdjList->id;
    if (currentRouter > routerMax) {
      routerMax = currentRouter;
    }
    if (network->visited[currentRouter] == 0 && network->ap[currentRouter]!=1) {
      nRouterMaxAUX++;
      routerMax = DFS(network, currentRouter, routerMax);
    }
    auxAdjList = auxAdjList->next; 
  }
  return routerMax;
}

void apUtil(struct Network* network, int id, int* visited, int* des, int* parent, int* low)
{
    struct Router* auxRouter=NULL;
    static int time=0;
    int children=0;
    auxRouter = network->adjLists[id];
    visited[id]=1;
    time++;
    des[id]=low[id]=time;

    while(auxRouter!=NULL)
    {       
       if(!visited[auxRouter->id])
        {
          children++;
          parent[auxRouter->id]=id;
          apUtil(network,auxRouter->id,visited,des,parent,low);

      low[id]= min(low[id],low[auxRouter->id]);

          if(parent[id]==-1 && children>1)
             network->ap[id]=1;

      if(parent[id]!=-1 && des[id]<=low[auxRouter->id])
            network->ap[id]=1;           
        }    
        else if(auxRouter->id!=parent[id])
        {
            low[id]=min(low[id],des[auxRouter->id]);
        }
       auxRouter= auxRouter->next;
      }
}
int AP(struct Network* network)
{
    int i;
    int vertexCounter=0;
    int* des = (int*)can_fail_malloc(sizeof(int)*network->nRouters);
    int* visited = (int*)can_fail_malloc(sizeof(int)*network->nRouters);
    int* parent = (int*)can_fail_malloc(sizeof(int)*network->nRouters);
    int* low = (int*)can_fail_malloc(sizeof(int)*network->nRouters);
    for(i=0;i<network->nRouters;i++)
    {
        visited[i]=0;
        parent[i]=-1;
        network->ap[i]=0;
    }
    for(i=0;i<network->nRouters;i++)
    {
        if(visited[i]==0)
        {
            apUtil(network,i,visited,des,parent,low);
        }
    }
    for(i=0;i<network->nRouters;i++)
    {
       
        if(network->ap[i]==1)
    {
    vertexCounter++;
    }
  }
  return vertexCounter;
}

/*MAIN*/
int main()
{
  int vertexCounter;
  /*read number N of routers*/
  while (nRouters < 2) {
    scanf("%d", &nRouters);
    if (nRouters < 2) {
      printf("ERROR:The number of routers must be greater than 2\n");
    }
  }
  /*create list  of ints to store the identifiers*/
  int identIndex = 0;
  /*create Network for N routers (Adjacency List)*/
  struct Network* network = createNetwork(nRouters);
  /*read number M of links*/
  while (mLinks < 1) {
    scanf("%d", &mLinks);
    if (mLinks < 1) {
      printf("ERROR:The number of links must be greater than 1\n");
    }
  }
  /*update routers with the links*/
  int i;
  for (i = mLinks; i > 0; i--) {
    scanf("%d %d", &auxSRC, &auxDEST);
    addLink(network, auxSRC, auxDEST);
  }

  /*print Network for debugging*/
  /*printNetwork(network);*/

  /*find first router in the network*/
  for(i = 1; i <= nRouters; i++) {
    routerMax = 1;
    if (network->adjLists[i] != NULL && network->visited[i] == 0)
    {
      routerMax = DFS(network, i, routerMax);
      subNetworks++;
      network->identList = can_fail_realloc(network->identList, subNetworks*(sizeof(int)));
      network->identList[identIndex] = routerMax;
      identIndex++;
      /*printf("subNetworks: %d\n", subNetworks);*/
    }
  }
  quickSort(network->identList, 0, subNetworks-1);

  vertexCounter = AP(network);

  /*OUTPUT PRINT*/
  /*print number of sub-networks*/
  printf("%d\n", subNetworks);
  /*print identifiers*/
  for (i = 0; i < subNetworks; i++) {
    if (i == subNetworks-1) {
      printf("%d\n", network->identList[i]);
    } else {
      printf("%d ", network->identList[i]);
    }
  }
  printf("%d\n", vertexCounter);
  for (i = 0; i <= nRouters; i++)
  {
    network->visited[i] = 0;
  }
  nRouterMax = 0;
  for (i = 1; i <= nRouters; i++)
  {
    if(network->adjLists[i] != NULL && network->ap[i-1] != 1 && network->visited[i] == 0) {
      nRouterMaxAUX = 0;
      DFS(network, i, routerMax);
      if (nRouterMaxAUX > nRouterMax)
      {
        nRouterMax = nRouterMaxAUX;
      }
    }
  }
  printf("%d\n", nRouterMax+1);
  return 0;
}
