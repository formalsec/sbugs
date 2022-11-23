#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


int nVertices;
int nSCC=0;
int nCutVertices=0;
int gray =0;
int white = -1;
int black = 1;
int *nVerticesRede;
int MAX=0;
int c=1;

/*--------------------GRAPH-----------------------*/
typedef struct edge *Edge;
struct edge {
    int v;
    int w;
};

Edge EDGE(int x, int y){
    Edge edge;
    edge = can_fail_malloc(sizeof(struct edge));
    edge->v =x;
    edge->w =y;
    return edge;
}

typedef struct node *link;
struct node {
    int v;
    link next;
};

link InsertBegin(int w) {
    link x = can_fail_malloc(sizeof(struct node));
    x->v = w;
    x->next = NULL;
    return x;
}

typedef struct graph {
    int V;
    int E;
    link* adj;
}*Graph;

Graph GRAPHinit(int V) {
    int v;
    Graph G = can_fail_malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->adj = can_fail_malloc((V+1) * sizeof(link));
    for (v = 1; v < V+1; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertE(Graph G, Edge e) {
    int v = e->v, w = e->w;
    link x = InsertBegin(w);
    x->next = G->adj[v];
    G->adj[v] = x;
    G->E++;
}


void graphDestroyAdjList(link n){
    if (n == NULL){
        return;
    }
    graphDestroyAdjList(n->next);
    free(n);

}


void graphRemoveConnection(Graph g, int v, int w){
    link prv_ptr = NULL;
    link cur_ptr = g->adj[v];

    while(cur_ptr != NULL && cur_ptr->v != w){
        prv_ptr = cur_ptr;
        cur_ptr = cur_ptr->next;
    }

    if (cur_ptr == NULL){
        return;
    }

    if (prv_ptr == NULL){
        g->adj[v] = cur_ptr->next;
    } else {
        prv_ptr->next = cur_ptr->next;
    }
    free(cur_ptr);
}

int GraphCheckConneted(Graph g, int v, int w){
    link ptr = g->adj[v];
    while(ptr != NULL){
        if (ptr->v == w){
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}


void GraphRemoveEdge(Graph g, int v, int w){
    if (!(v < nVertices+1 && w<nVertices+1)){
        perror("Trying to add an invalid edge into graph");
        exit(-1);
    }
    if (GraphCheckConneted(g, v, w) != 0){
        graphRemoveConnection(g, v, w);
    }
    if (GraphCheckConneted(g, w, v) != 0){
        graphRemoveConnection(g, w, v);

    }
}

void GraphRemoveNode(Graph g, int v){
    while(g->adj[v] != NULL ){
        link adjList = g->adj[v];
        GraphRemoveEdge(g, v, adjList->v);
    }
}


void GraphDestroy(Graph g){
    int i;
    if (g == NULL){
        return;
    }
    if (g->adj != NULL){
        for(i = 1; i < nVertices+1; i++ ){
            graphDestroyAdjList(g->adj[i]);
        }
        free(g->adj);
    }
    free(g);
}


/*-----------------STACK---------------------------*/

typedef struct _StackItem* STACK_ITEM;
typedef struct _StackItem{
    int data;
    STACK_ITEM next;
}StackItem;

typedef struct _Stack* STACK;
typedef struct _Stack{
    STACK_ITEM header;
}Stack;

STACK StackCreate(){
    STACK ptr;
    ptr = (STACK)can_fail_malloc(sizeof(Stack));
    if (ptr == NULL) {
        perror("fail to allocate memory to create 'Stack'");
        exit(-1);
    }
    ptr->header = NULL;
    return ptr;
}

STACK_ITEM StackPop(STACK s){
    STACK_ITEM item;
    item = s->header;
    s->header = item->next;
    return item;
}

void StackPush(STACK s, int data){
    STACK_ITEM item = (STACK_ITEM)can_fail_malloc(sizeof(StackItem));
    if (item == NULL) {
        perror("fail to allocate memory to create 'Stack'");
        exit(-1);}
    item->data = data;
    item->next = s->header;
    s->header = item;
}

int StackCheckExists(STACK s, int data){
    STACK_ITEM data_ptr;
    data_ptr = s->header;
    while(data_ptr != NULL){
        if(data_ptr->data == data){
            return 1;}
        data_ptr = data_ptr->next;
    }
    return 0;
}


/*----------------------------------------------------------------*/

static int time=0;

typedef struct item *Item;
struct item {
    int  item;
    Item l;
    Item r;
};

Item head=NULL;

Item NEW(int i, Item l, Item r) {
    Item x = (Item)can_fail_malloc(sizeof(struct item));
    x->item = i;
    x->l = l;
    x->r = r;
    return x;
}


Item insert(Item h, int valor) {
    int v = valor;
    if (h == NULL)
        return NEW(valor, NULL, NULL);
    if (v < h->item)
        h->l = insert(h->l, valor);
    else
        h->r = insert(h->r, valor);
    return h;
}

void visit(Item i)
{
    if(c==nSCC) {
        printf("%d",i->item);
    }
    else{
        printf("%d ",i->item);
        c++;
    }
}

void traverse(Item h)
{
    if (h == NULL)
        return;
    traverse(h->l);
    visit(h);
    traverse(h->r);

}

void freeBinaryTree(Item h){
    if(h==NULL) return;
    freeBinaryTree(h->l);
    freeBinaryTree(h->r);
    free(h);
}


/*---------------------DFS----------------------------------------*/

int min(int a1, int a2){
    if(a1<a2)
        return a1;
    else
        return a2;
}

int max(int a1, int a2){
    if(a1>a2)
        return a1;
    else
        return a2;
}

void auxCutVertices(Graph g, int u, int* color, int* pi,int* d, int* f, bool* ap){
    link node;
    int children = 0;
    color[u] = gray;
    d[u] = f[u] = time;
    time++;

    for (node = g->adj[u]; node != NULL; node = node->next){
        int v = node->v;

        if (color[v] == white){
            children++;
            pi[v] = u;

            auxCutVertices(g,v, color, pi, d, f,ap);
            f[u]  = min(f[u], f[v]);

            if ((pi[u] == 0 && children > 1) || (pi[u] != 0 && f[v] >= d[u]))
                ap[u] = true;

        }
        else if (v != pi[u])
            f[u]  = min(f[u], d[v]);
    }

    color[u]=black;
}


void cutVerticesDFS(Graph g, bool *ap) {
    int i;
    int *d = (int *) can_fail_malloc(sizeof(int) * (nVertices + 1));
    int *f = (int *) can_fail_malloc(sizeof(int) * (nVertices + 1));
    int *pi = (int *) can_fail_malloc(sizeof(int) * (nVertices + 1));
    int *color = (int *) can_fail_malloc(sizeof(int) * (nVertices + 1));

    for (i = 1; i < nVertices + 1; i++) {
        color[i] = white;
        f[i] = -1;
        d[i] = INT_MAX;
        pi[i] = 0;
        ap[i] = false;
    }

    for (i = 1; i < nVertices + 1; i++) {
        if (color[i] == white)
            auxCutVertices(g, i, color, pi, d, f, ap);
    }

    free(d);
    free(f);
    free(pi);
    free(color);


    for (i = 1; i < nVertices + 1; i++) {
        if (ap[i] == true){
            nCutVertices++;
            GraphRemoveNode(g,i);

        }
    }

    printf("%d\n", nCutVertices);

    free(ap);

}

int done=0;
/*-------------------TARJAN-----------------------*/
void tarjan_Visit(Graph g, int u, int *d, int *low, STACK stack, int idRouter, int *idSubRedes) {

    if(done==1){
        MAX=0;
        done=0;
    }
    int cont =0;
    link node;
    StackPush(stack, u);
    d[u] = low[u] = time;
    time = time + 1;


    for (node = g->adj[u]; node != NULL; node = node->next){
        int v = node->v;
        if (d[v] == INT_MAX){
            tarjan_Visit(g, v, d, low, stack,idRouter,idSubRedes);}
        if(StackCheckExists(stack,v)==1)
            low[u] = min(low[u], low[v]);
    }

    if (d[u] == low[u]){
        STACK_ITEM item;
        for(item = StackPop(stack);; item=StackPop(stack)){
            cont++;
            low[item->data]=low[u];
            if (item->data == u){
                break;
            }
            else{
                if(idRouter==-1)    {idRouter=item->data; }
                else                {idRouter=max(idRouter,item->data); }
            }
        }
        if(cont > MAX){
            MAX = cont;
        }
        head = insert(head,idRouter);
        nSCC++;


    }
}

void sccTarjan(Graph g, STACK stack){
    int *low = (int*) can_fail_malloc(sizeof(int)*(nVertices+1));
    int *vDisc = (int*) can_fail_malloc(sizeof(int)*(nVertices+1));
    int *idSubRedes = (int*) can_fail_malloc(sizeof(int)*(nVertices));
    int idRouter=-1;
    int i;

    for(i = 1; i<nVertices+1; i++) {
        nVerticesRede[i]=0;
        vDisc[i] = INT_MAX;
        low[i] = -1;
    }

    for(i = 1; i< nVertices+1; i++) {
        if (vDisc[i] == INT_MAX){
            tarjan_Visit(g, i, vDisc, low, stack,idRouter,idSubRedes);
        }
    }


    if(done==0){
        done=1;
    }

    free(low);
    free(vDisc);
    free(idSubRedes);
}

int main(){

    int i,nEdges,src,dest;
    Graph graph;
    STACK stack;
    Edge edge;
    if((scanf("%d",&nVertices))==1){};
    if((scanf("%d",&nEdges)==1)){};

    bool *ap = (bool *) can_fail_malloc(sizeof(bool) * (nVertices + 1));
    graph = GRAPHinit(nVertices);

    nVerticesRede = (int*) can_fail_malloc(sizeof(int)*(nVertices+1));
    for(i=0; i<nEdges; i++){
        if((scanf("%d %d",&src,&dest)) ==2){};
        edge = EDGE(src, dest);
        GRAPHinsertE(graph, edge);
        free(edge);
        edge = EDGE(dest, src);
        GRAPHinsertE(graph, edge);
        free(edge);
    }

    stack = StackCreate();
    sccTarjan(graph,stack);
    printf("%d\n",nSCC);
    traverse(head);
    printf("\n");
    cutVerticesDFS(graph, ap);

    sccTarjan(graph,stack);

    printf("%d\n", MAX);

    GraphDestroy(graph);

    return 0;
}