#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#define NIL -1


typedef struct router {
    int dest;
    struct router* next;
}*Router;

typedef struct List {
    Router head;
    int verified;
}*Listpointer;

typedef struct graph {
    long v;
    Listpointer array;
}*Graph;

typedef struct stack { 
    int top; 
    int capacity; 
    int* array;
}*Stack;

int top(Stack stack);


Router newRouter(int dest);
Graph createGraph(long v);
void addEdge(Graph graph, int src, int dest);
Stack createStack(int capacity);
int top(Stack stack);
void deleteRouter(Router head,int id);
void deleteList(Router head);
void push(Stack stack, int item);
int pop(Stack stack);
Graph readInputs(       );
void Tarjan(Graph graph, int discovery[], int low[], int roots[],int pontes[],int aux[]);
void SCC_Tarjan(int u, int discovery[], int low[], Stack stack, 
        int stackMember[], Graph graph, int roots[],int parent[],int pontes[],int aux[]);
void free_func(Graph graph, Stack stack);
int min(int a, int b);
void fillThoseGaps(Graph graph,int d[],int l[]);
void heapsort(int a[], int n);

int scc = 0;
int a = 0;
int fourth =0;

void printGraph(Graph graph, int discovery[], int low[]) 
{ 
    int v;
    for (v = 1; v < graph->v + 1; ++v) 
    {   
        printf("\nDISCOVERY :%d, LOW :%d", discovery[v], low[v]);            
        Router pCrawl = graph->array[v].head; 
        printf("\n Adjacency list of vertex %d\n head ", v); 
        while (pCrawl != NULL)  
        { 
            printf("-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
}

int main (int argc, char *argv[]){
    Graph pGraph = readInputs();
    int *discovery = can_fail_malloc((pGraph->v + 1)  * sizeof(int));
    int *low = can_fail_malloc((pGraph->v + 1) * sizeof(int)); 
    int *roots = can_fail_malloc((pGraph->v) * sizeof(int));
    int *pontes= can_fail_malloc((pGraph->v+1) * sizeof(int));
    int *aux=can_fail_malloc((pGraph->v+1) * sizeof(int));
    int j;
    for(j=1;j<=pGraph->v;j++){
        pontes[j]=NIL;
        aux[j]=NIL;
    }
    int i;
    Tarjan(pGraph, discovery, low, roots,pontes,aux);
	fourth = 0;
    heapsort(roots,scc);
    printf("%d\n", scc);
    for(i=0;i<scc;i++){
        if (i < scc-1){
            printf("%d ",roots[i]);
        }
        else
            printf("%d",roots[i]);
    }
    printf("\n");
    printf("%d\n", a);
    
    Tarjan(pGraph, discovery, low, roots,aux,pontes);

    printf("%d\n",fourth);
    

    
    

    return 0;
}


void free_func(Graph graph, Stack stack){
    int v;
    Router r;
    for (v = 1; v < graph->v + 1; ++v) 
    {   
        Router pCrawl = graph->array[v].head;
        while (pCrawl != NULL) 
        {  
            r = pCrawl->next;
            free(pCrawl);
            pCrawl = r;
        }  
    }
    free(graph);
    free(stack);
}


Graph readInputs(){
    long nRouters, mLinks, source, destiny; 
    long iter;
    fscanf(stdin, "%ld", &nRouters);
    Graph pGraph = createGraph(nRouters);
    fscanf(stdin, "%ld", &mLinks);
    for (iter = 0; iter < mLinks; iter++){
        fscanf(stdin, "%ld %ld", &source, &destiny);
        addEdge(pGraph, source, destiny);        
    }
    return pGraph;
}



void Tarjan(Graph graph, int discovery[], int low[], int roots[],int pontes[],int aux[]) 
{ 
    int V = graph->v+1;
    int *stackMember = can_fail_malloc(V * sizeof(int));
    int *parent=can_fail_malloc(V * sizeof(int));
    Stack stack = createStack(V);
    int i;
    for (i = 1; i <= V; i++)
    {
        discovery[i] = NIL; 
        low[i] = NIL; 
        stackMember[i] = 0;
        parent[i] = NIL;
    } 

    for (i = 1; i <= graph->v; i++) 
        if (discovery[i] == NIL){
            if(pontes[i]==-1){
                SCC_Tarjan(i, discovery, low, stack, stackMember, graph, roots, parent,pontes,aux);
            }
        }
}

void SCC_Tarjan(int u, int discovery[], int low[], Stack stack, 
                    int stackMember[], Graph graph, int roots[], int parent[],int pontes[],int aux[])
{
    static int time = 0; 
    int adjacent = 0;
    discovery[u] = ++time;
    low[u] = time;
    push(stack, u); 
    stackMember[u] = 1; 
  
    Router iter=graph->array[u].head;
    for (; iter != NULL; iter = iter->next) 
    {
        int v = iter->dest;  
        if(pontes[v]==v){
            continue;
        }
        if (discovery[v] == -1){
            adjacent++;
            parent[v] = u;
            SCC_Tarjan(v, discovery, low, stack, stackMember,graph, roots, parent,pontes,aux); 
  
            low[u]  = min(low[u], low[v]);


            if (parent[u] == NIL && adjacent > 1)
            {
                if (graph->array[u].verified == 0){
                    graph->array[u].verified = 1;
                    aux[u]=u;
                    a++;
                }
            }
  
            if (parent[u] != NIL && low[v] >= discovery[u])
            {
                if (graph->array[u].verified == 0){
                    graph->array[u].verified = 1;
                    aux[u]=u;
                    a++;
                }
            }
               

        }

        else if (stackMember[v] == 1) 
            low[u] = min(low[u], discovery[v]);
    }

    int w = 0;  
    if (low[u] == discovery[u]) 
    { 
        int max=u;
        int max1=1;       
        while (top(stack) != u) 
        {
            if (max < top(stack)){
                max = top(stack);
            }
            max1++;
            w = top(stack);
            stackMember[w] = 0; 
            pop(stack); 
        }
        if(max1>fourth){
            fourth=max1;
        }
        roots[scc]=max;
        scc++;
        w = top(stack);
        stackMember[w] = 0; 
        pop(stack);
    }
}





int min(int a, int b){
    if (a < b){
        return a;
    }
    else{
        return b;
    }
}



void heapsort(int a[], int n) {
   int i = n / 2, father, child, t;
   while(1) {
      if (i > 0) {
          i--;
          t = a[i];
      } else {
          n--;
          if (n == 0) return;
          t = a[n];
          a[n] = a[0];
      }
      father = i;
      child = i * 2 + 1;
      while (child < n) {
          if ((child + 1 < n)  &&  (a[child + 1] > a[child]))
              child++;
          if (a[child] > t) {
             a[father] = a[child];
             father = child;
             child = father * 2 + 1;
          } else {
             break;
          }
      }
      a[father] = t;
   }
}


Router newRouter(int dest){
    Router newNode = (Router) can_fail_malloc(sizeof(struct router)); 
    newNode->dest = dest; 
    newNode->next = NULL; 
    return newNode; 
}

Graph createGraph(long v) 
{ 
    Graph graph = (Graph) can_fail_malloc(sizeof(struct graph)); 
    graph->v = v; 

    graph->array =  (Listpointer) can_fail_malloc((v+1) * sizeof(struct List)); 
  
    int i; 
    for (i = 1; i <= v; ++i){ 
        graph->array[i].head = NULL; 
        graph->array[i].verified=0;
    }
    return graph; 
}

void addEdge(Graph graph, int src, int dest) 
{ 
    
    Router newNode1 = newRouter(dest); 
    newNode1->next = graph->array[src].head; 
    graph->array[src].head = newNode1; 
  
    Router newNode2 = newRouter(src); 
    newNode2->next = graph->array[dest].head; 
    graph->array[dest].head = newNode2; 
}

Stack createStack(int capacity) 
{ 
    Stack stack = (Stack)can_fail_malloc(sizeof(struct stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*) can_fail_malloc((capacity) * sizeof(int)); 
    return stack; 
}

int isEmpty(Stack stack) {
    return stack->top == -1;
}


int isFull(Stack stack){
    return stack->top == stack->capacity-1;
}

void push(Stack stack, int item){ 
    if(isFull(stack)){
        return; 
    }
    stack->array[++stack->top] = item; 
    
}

int pop(Stack stack) {
    if (isEmpty(stack)){
        return -1;
    }
    return stack->array[stack->top--];
}

int top(Stack stack){
    if (isEmpty(stack)){
        return -1;
    }
    return stack->array[stack->top];
}


