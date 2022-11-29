#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



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

void addConnection(Graph g, int n1, int n2, int cap, int flow);

void destroyGraph(Graph g);

void printGraph(Graph g);

void addCut(List l, int v1, int v2);

/*******************************************************************************
  List funciton headers and structures
 *******************************************************************************/

struct list{
    ListNode first;
    ListNode last;
};

struct list_node{
    int value;/*positon in the main graph array of an adjacent vertex*/
    int flow;
    int capacity;
    struct list_node *next;
};

List newList();

ListNode newListNode(int value, int cap, int flow);

int isListEmpty(List list);

void insertBegin(List list, int value, int cap, int flow);

void insertEnd(List list, int value, int cap, int flow);

void printList(List l);

void destroyList(List l);

void DFS(Graph g, int *visitedFlag, int nProvider, int nSuplStation, List cuts, int *heights);

void DFSVisit(Graph g, int src, int *visitedFlag, int nProveider, int nSuplStation, List cuts, int *heights);

void printCuts(List l);
/*******************************************************************************
  Queue functions definition
 *******************************************************************************/

typedef List Queue;

Queue newQueue();

void queuePush(Queue q, int value);

int queuePop(Queue q);

int isQueueEmpty(Queue q);

/*******************************************************************************
  Push-Relabel functions definition
 *******************************************************************************/

void preFlow(Graph g, Queue queue, int *heights, int *excess, int *inQueue);

void reverseEdgeFlow(Graph g, int n1, int n2, int flow);

int push(Graph g, Queue queue, int n, int *heights, int *excess, int *capacities, int *inQueue);

void relabel(Graph g, int n, int *heights);


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

void addConnection(Graph g, int n1, int n2, int cap, int flow){
    ListNode newNode = newListNode(n2-1, cap, flow);
    newNode->next = g->adj[n1-1].first;
    g->adj[n1-1].first = newNode;
}

void addCut(List l, int v1, int v2){
    ListNode newNode = newListNode(v1, v2, 0);
    newNode->next = l->first;
    l->first = newNode;
}

void printGraph(Graph g){
    int i;
    ListNode j;
    for(i=0; i < g->nodeCount;  i++){
        printf("%d ->\n", i+1);
        for(j=g->adj[i].first; j!=NULL; j=j->next){
            printf("Adj: %d\n",j->value+1);
            printf("Cap: %d\n", j->capacity);
            printf("Flow: %d\n", j->flow);
            printf("\n");
        }
        printf("\n");
    }
}


void preFlow(Graph g, Queue queue, int *heights, int *excess, int *inQueue){
    ListNode n;
    heights[0] = g->nodeCount;

    for(n = g->adj[0].first; n != NULL; n = n->next){
        n->flow = n->capacity;
        excess[0] -= n->flow;
        excess[n->value] += n->flow;
        addConnection(g, n->value + 1, 1, 0, -n->flow);
        if (n->value != 0 && n->value != g->nodeCount-1){
            queuePush(queue, n->value);
            inQueue[n->value] = 1;
        }
    }
}

void reverseEdgeFlow(Graph g, int n1, int n2, int flow){
    ListNode n;
    for (n = g->adj[n1-1].first; n != NULL; n = n->next){
        if (n->value == n2-1){
            n->flow -= flow;
            return;
        }
    }
    addConnection(g, n1, n2, flow, 0);
}

int push(Graph g, Queue queue, int n1, int *heights, int *excess, int
*capacities, int *inQueue){
    int flow=0; 
    ListNode n;
    for(n = g->adj[n1-1].first; n !=NULL ; n = n->next){
        if (n->flow == n->capacity)
            continue;

        if(heights[n->value] < heights[n1-1]){
            if (excess[n1-1] <= n->capacity - n->flow)
                flow = excess[n1-1];
            else flow = n->capacity - n->flow;


            excess[n1-1] -= flow;
            excess[n->value] += flow;
            n->flow += flow;

            reverseEdgeFlow(g, n->value + 1, n1, flow);
            if (inQueue[n->value] == 0 && n->value != 0 && n->value != g->nodeCount-1){
                queuePush(queue, n->value);
                inQueue[n->value] = 1;
            }

            return 1;
        }
    }
    return 0;

}


void relabel(Graph g, int n1, int *heights){
    int maxH = INT_MAX;
    ListNode n;
    for(n = g->adj[n1-1].first; n != NULL; n = n->next){
        if (n->flow == n->capacity)
            continue;
        if (heights[n->value] < maxH){
            maxH = heights[n->value];
            heights[n1-1] = maxH + 1;
        }
    }
}


void DFS(Graph g, int* visitedFlag, int nProvider, int nSuplStation, List cuts, int* heights){
    int i = 0;
    for(i = 0; i < g->nodeCount; i++){
        visitedFlag[i]=0;
    }

    DFSVisit(g, 0, visitedFlag, nProvider, nSuplStation, cuts, heights);

}

void DFSVisit(Graph g, int src, int *visitedFlag, int nProvider, int nSuplStation, List cuts, int* heights){
    ListNode i = NULL;
    visitedFlag[src]=1;
    for(i = g->adj[src].first; i !=NULL; i=i->next){
        if(i != NULL && visitedFlag[i->value] == 0 && i->capacity - i->flow > 0 ){
            DFSVisit(g, i->value, visitedFlag, nProvider, nSuplStation, cuts, heights);
        }
    }
}

void printCuts(List cuts){
    ListNode i=NULL;
    for(i=cuts->first; i != NULL; i=i->next){
        printf("%d %d\n", i->value, i->capacity);
    }

}

void swap(ListNode *a, ListNode *b){
    ListNode t = *a;
    *a = *b;
    *b = t;
}

int partition(ListNode *array, int low, int high){
    int pivot = array[high]->value;
    int pivot2 = array[high]->capacity;
    int i = low - 1;
    int j;

    for (j = low; j < high; j++){
        if (array[j]->value < pivot){
            i++;
            swap(&array[i], &array[j]);
        }else if (array[j]->value == pivot){
            if(array[j]->capacity <= pivot2){
                i++;
                swap(&array[i], &array[j]);
            }
        }
    }
    swap(&array[i+1], &array[high]);
    return (i+1);
}

void quickSort(ListNode *array, int low, int high){
    if(low < high){
        int pi = partition(array, low, high);

        quickSort(array, low, pi-1);
        quickSort(array, pi+1, high);
    }
}

/*******************************************************************************
  List functions definition
 *******************************************************************************/
List newList(){
    List l = (List)can_fail_malloc(sizeof(struct list));
    l->first=l->last=NULL;
    return l;
}


ListNode newListNode(int value, int cap, int flow){
    ListNode newNode = (ListNode)can_fail_malloc(sizeof(struct list_node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->capacity=cap;
    newNode->flow=flow;
    return newNode; 
}

int isListEmpty(List list){
    return (list->first==NULL && list->last==NULL ? 1 : 0 );
}

void insertBegin(List list, int value, int cap, int flow){
    ListNode node = newListNode(value, cap, flow);
    if(isListEmpty(list)){
        list->first=list->last=node;
        node->next = NULL;
    }else{
        node->next = list->first;
        list->first = node;
    }
}

void insertEnd(List list, int value, int cap, int flow){
    ListNode node = newListNode(value, cap, flow);
    if(isListEmpty(list)){
        list->first = list->last = node; 
        node->next=NULL;
    }else{
        list->last->next = node;
        node->next=NULL;
        list->last=node;
    }
}

int listRemoveFirst(List list){
    int x=0;
    ListNode n = list->first;
    if(n!=NULL) x = n->value;

    list->first = list->first->next;
    if (list->first == NULL)
        list->last = NULL;
    
    free(n);
    return x;
}

void printList(List l){
    ListNode i;
    for(i=l->first; i!=NULL ; i=i->next){
        printf("%d -> ", i->value);
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
  Queue functions definition
 *******************************************************************************/


Queue newQueue(){
    Queue new = newList();
    return new;
}
void queuePush(Queue q, int value){
    insertEnd(q, value, 0, 0);
}
int queuePop(Queue q){
    return listRemoveFirst(q);
}
int isQueueEmpty(Queue q){
    return isListEmpty(q);
}


/*******************************************************************************
  Main Program
 *******************************************************************************/



int main(){
    int nProviders;
    int nSuplStation;
    int nConnections;

    int src, dest, cap; 

    int *heights, *excess, *capacities, *inQueue, *orderedCap, *suplyAdded;
    
    int *visitedFlag;

    Graph network;
    int networkSize;
    
    Queue queue = newQueue();

    int i = 0, j = 0, space = 0, aux = 0;
    
    List cuts = newList();
    ListNode n;
    ListNode *orderedConnec;

    scanf("%d %d %d", &nProviders, &nSuplStation, &nConnections);
    networkSize = nProviders+2*nSuplStation+2;
    network = newGraph(networkSize);
    
    heights = (int*)can_fail_malloc(sizeof(int)*networkSize);
    excess = (int*)can_fail_malloc(sizeof(int)*networkSize);
    suplyAdded = (int*)can_fail_malloc(sizeof(int)*networkSize);
    capacities = (int*)can_fail_malloc(sizeof(int)*networkSize);
    inQueue = (int*)can_fail_malloc(sizeof(int)*networkSize);
    orderedCap = (int*)can_fail_malloc(sizeof(int)*networkSize);
    orderedConnec = (ListNode*)can_fail_malloc(sizeof(ListNode)*nConnections);

    for(i=0 ; i < networkSize; i++){
        heights[i]=excess[i]=suplyAdded[i]=inQueue[i]=orderedCap[i]=0;
        capacities[i]=-1;
    }

   

    for(i=1; i < 1+nProviders; i++){
        scanf("%d", &cap);
        addConnection(network, i+1, networkSize, cap, 0);
    }

    for( ;i < 1+nProviders+nSuplStation ; i++){
        scanf("%d", &(capacities[i]));
    }

    
    for(i=0; i < nConnections; i++){
        scanf("%d %d %d", &src, &dest, &cap);
        if(src > nProviders+1){

            addConnection(network, dest, src+nSuplStation, cap, 0);
            
            if(!suplyAdded[src-1]){
                addConnection(network, src+nSuplStation, src, capacities[src-1], 0);
                suplyAdded[src-1] = 1;
            }

        }else{
            addConnection(network, dest, src, cap, 0);
        }

    }

    preFlow(network, queue, heights, excess, inQueue);

    i = 0;
    while(!isQueueEmpty(queue)){
        int vert = queuePop(queue) + 1;
        inQueue[vert-1] = 0;
        while(excess[vert-1] != 0){
            if (heights[vert-1] == 0 || !push(network, queue, vert, heights,
            excess, capacities, inQueue)){
                relabel(network, vert, heights);
            }
        }
    }


    visitedFlag = (int*)can_fail_calloc(networkSize, sizeof(int));
    

    printf("%d\n", -excess[0]);
    DFS(network, visitedFlag, nProviders, nSuplStation, cuts, heights);

    for(i = 0; i < networkSize; i++){
        for (n = network->adj[i].first; n != NULL; n = n->next){
            if(n->value + 1 == networkSize) continue;
            aux = visitedFlag[i];
            if(aux == 1 && visitedFlag[n->value] == 0){
                if(i >= networkSize - nSuplStation - 1 && i == n->value + nSuplStation)
                    addCut(cuts, n->value + 1, -1);
                else if (n->value >= networkSize - nSuplStation - 1)
                    addCut(cuts, n->value - nSuplStation + 1, i + 1);
                else addCut(cuts, n->value + 1, i + 1);
            }
        }
    }

    i = 0;
    for (n = cuts->first; n != NULL; n = n->next){
        if (n->capacity == -1)
            orderedCap[n->value-1] = 1;
        else{
            orderedConnec[i]=n;
            i++;
        }
    } 

    for (j = 0; j < networkSize; j++){
        if(orderedCap[j] == 1){
            if(!space){
                printf("%d", j+1);
                space = 1;
            }else
                printf(" %d",j+1);
        }
    }

    printf("\n");

    quickSort(orderedConnec, 0, i-1);

    for(j = 0; j < i; j++){
        printf("%d %d\n", orderedConnec[j]->value, orderedConnec[j]->capacity);
    }

    free(heights);
    free(excess);
    free(suplyAdded);
    free(capacities);
    free(inQueue);
    free(visitedFlag);
    free(orderedCap);
    free(orderedConnec);
    destroyList(queue);
    free(queue);
    destroyList(cuts);
    free(cuts);
    destroyGraph(network);
    return 0;
}
