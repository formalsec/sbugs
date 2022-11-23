#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>



/*******************************************************************************
                    Graph function headers and structures
*******************************************************************************/

typedef struct graph *Graph;

typedef struct list *List;

typedef struct list_node *ListNode;

struct graph{
    int nodeCount;
    List adj;
};

Graph newGraph(int nodeCount);

void addConnection(Graph g, int n1, int n2);

void destroyGraph(Graph g);

int tarjan(Graph g, char *representative, int *maxCompCount, int *critical);

int tarjanVisit(Graph g, int src, int *time, char *visited, int *distance, int *low,
 int *pred, char *critical, int *max, int *compCount);



/*******************************************************************************
                    List unciton headers and structures
*******************************************************************************/

struct list{
    ListNode first;
    ListNode last;
};

struct list_node{
    int value;
    struct list_node *next;
};

ListNode newListNode(int value);

int isListEmpty(List list);

void insertBegin(List list, int value);

void insertEnd(List list, int value);

void destroyList(List l);

/*******************************************************************************
                    Graph functions definition
*******************************************************************************/


void destroyGraph(Graph g){
    int i = 0;
    for(i=0; i<g->nodeCount; i++){
        destroyList(&g->adj[i]);
    }
    free(g->adj);
    free(g);
}

Graph newGraph(int nodeCount){
    int i;
    Graph newGraph = (Graph)can_fail_malloc(sizeof(struct graph));
    newGraph->nodeCount = nodeCount;
    newGraph->adj = (List)can_fail_malloc(sizeof(struct list)*(nodeCount));

    for(i = 0; i < nodeCount; i++)
    	newGraph->adj[i].first = NULL;

    return newGraph;
}

void addConnection(Graph g, int n1, int n2){
    ListNode newNode = newListNode(n2-1);
    newNode->next = g->adj[n1-1].first;
    g->adj[n1-1].first = newNode;

    newNode = newListNode(n1-1);
    newNode->next = g->adj[n2-1].first;
    g->adj[n2-1].first = newNode;
}


int tarjan(Graph g, char *representative, int *maxCompCount, int *nCritical){
    int time = 0;
    int i, subNetWorkCount=0, compCount = -1;
    int max;
    char *visited = (char*)can_fail_malloc(sizeof(char)*g->nodeCount);
    int *distance = (int*)can_fail_malloc(sizeof(int)*g->nodeCount);
    int *low = (int*)can_fail_malloc(sizeof(int)*g->nodeCount);
    int *pred = (int*)can_fail_malloc(sizeof(int)*g->nodeCount);
    char *critical = (char*)can_fail_malloc(sizeof(char)*g->nodeCount);
    

    for (i = 0; i < g->nodeCount; i++){
    	visited[i] = critical[i] = representative[i] = 0;
    	pred[i] = -1;
    }


    for(i = 0; i < g->nodeCount;i++){
        if (visited[i] == 0){
            max = 0;
            compCount = 1;
            tarjanVisit(g, i, &time, visited,
             	distance, low, pred, critical, &max, &compCount);
            subNetWorkCount++;
            representative[max] = 1;
            if(compCount > *maxCompCount)
                *maxCompCount = compCount;
        }
    }

    for(i = 0; i < g->nodeCount;i++)
    	if(critical[i])
    		*nCritical += 1;

    for(i = 0; i < g->nodeCount; i++)
        if(critical[i] == 1){
            destroyList(&g->adj[i]);
        	g->adj[i].first = NULL;    
        }
   
    
    free(visited);
    free(distance);
    free(low);
    free(pred);
    free(critical);
   
    return subNetWorkCount;
}

int tarjanVisit(Graph g, int src, int *time, char *visited, int *distance, int *low,
 int *pred, char *critical,int *max, int *compCount){
    ListNode i = NULL;
    int children = 0;
    int aux;
    visited[src] = 1;
    distance[src] = low[src] = *time;
    *time += 1;

    if(g->adj[src].first == NULL) return 0;
    for(i = g->adj[src].first; i != NULL; i = i->next){
        aux = i->value;
        if(!(visited[aux])){
            children++;

            if(i != NULL && g->adj[aux].first != NULL)
                *compCount = (*compCount) +1;
            
            pred[aux] = src;

            tarjanVisit(g, aux, time, visited, distance, low, pred, critical, max, compCount);

            if (src > *max)
            	*max = src;
            
            if (aux > *max)
            	*max = aux;

            if (low[src] > low[aux])
                low[src] = low[aux];

            if (pred[src] == -1 && children > 1)
                critical[src] = 1;
            

            if (pred[src] != -1 && distance[src] <= low[aux])
            	critical[src] = 1;
            

        }
        else if (aux != pred[src]){
            if (low[src] > distance[aux])
                low[src] = distance[aux];
        }
    }
    
    
    return 0;
}
/*******************************************************************************
                    List functions definition
*******************************************************************************/

ListNode newListNode(int value){
    ListNode newNode = (ListNode)can_fail_malloc(sizeof(struct list_node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode; 
}

int isListEmpty(List list){
    return (list->first==NULL && list->last==NULL ? 1 : 0 );
}

void insertBegin(List list, int value){
    ListNode node = newListNode(value);
    if(isListEmpty(list)){
        list->first=list->last=node;
        node->next = NULL;
    }else{
        node->next = list->first;
        list->first = node;
    }
}

void insertEnd(List list, int value){
    ListNode node = newListNode(value);
    if(isListEmpty(list)){
        list->first = list->last = node; 
        node->next=NULL;
    }else{
        list->last->next = node;
        node->next=NULL;
        list->last=node;
    }
}

void destroyList(List l){
    ListNode i = NULL, aux=NULL;
    for(i=l->first; i!=NULL;){
        aux = i; 
        i = i->next;
        free(aux);
    }
}


/*******************************************************************************
                    Main Program
*******************************************************************************/


int main(){
    int i;
    int nRouters;
    int nConnections;
    int node1, node2;
    int subnetworks = 0;
    int maxCompCount = 0;
    int nCritical = 0;
    Graph g;
    char *representative;

    scanf("%d", &nRouters);
    g = newGraph(nRouters);
    
    representative = (char*)can_fail_malloc(sizeof(char)*g->nodeCount);

    scanf("%d", &nConnections);
    for (i = 0; i < nConnections; i++){
        scanf("%d %d", &node1, &node2);
        addConnection(g, node1, node2);
    }


    subnetworks = tarjan(g, representative, &maxCompCount, &nCritical);
    printf("%d\n", subnetworks);
    for(i = 0; i < g->nodeCount;i++)
    	if(representative[i]){
    		printf("%d", i+1);
    		if(i != g->nodeCount-1) printf(" ");
    	}
    	
    printf("\n");

    printf("%d\n", nCritical);

    maxCompCount=0;
    nCritical = 0;
    tarjan(g, representative, &maxCompCount, &nCritical);
    printf("%d\n", maxCompCount);

    destroyGraph(g);
    free(representative);



    return 0;
}
