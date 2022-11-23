#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/***************************************************/
/*                                                 */
/*               1 PROJETO DE ASA                  */
/*                                                 */
/***************************************************/


#include <stdlib.h>
#include <stdio.h>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))



/****************** DECLARATIONS *******************/

typedef struct node *link;
struct node {
	int v;
	link next;
};


typedef struct graph *Graph;
struct graph {
	int V;
	int E;
	link *adj; /* array of lists */
};


typedef struct {
	int d;
	int f;
	int pred;
	int low;
    char visited;
	char ap;
} Info;

link InsertBegin(int v, link head);
Graph GRAPHinit(int V);
void GRAPHinsertE(Graph G, int v, int w);
void DFS(Graph G, Info *list);
void DFSaux(Graph G, Info *list, int u);
int* reverseDFS(Graph G, Info *list, int size);
void tarjan(Graph G, Info *list);
void tarjanAux(Graph G, Info *list, int u);
int countV(Graph G, Info *list);
void countAux(Graph G, Info *list, int u);


/************************************************/



/**************AUXILIAR FUNCTIONS****************/


link InsertBegin(int v, link head) {
    link x = can_fail_malloc(sizeof(struct node));
    x->v = v;
    x->next = head;
    return x;
}

Graph GRAPHinit(int V) {
    int v;
    Graph G = can_fail_malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->adj = can_fail_malloc(V * sizeof(link));

    for (v = 0; v < V; v++) {
        G->adj[v] = NULL;
    }
    return G;
}

void GRAPHinsertE(Graph G, int v, int w) {
    G->adj[v] = InsertBegin(w, G->adj[v]);
    G->adj[w] = InsertBegin(v, G->adj[w]);
    G->E++;
}

/************************************************/



/******************* DFS ************************/

void DFS(Graph G, Info *list) {
    int v;
    for (v = 0; v < G->V; v++) {
        list[v].f = 0;
        list[v].d = 0;
        list[v].pred = 0;
        list[v].visited = 0;
    }

    for(v = 1; v < G->V; v++) {
        if(list[v].visited == 0)
            DFSaux(G, list, v);
    }
}


void DFSaux(Graph G, Info *list, int u) {
    static int time = 1;
    list[u].visited = 1;
    list[u].d = time;
    time = time + 1;
    link p;
    
    for (p = G->adj[u]; p != NULL; p = p->next) {
        int v = p->v;
        if(list[v].visited == 0) {
            list[v].pred = u;
            DFSaux(G, list, v);
        }
    }

    list[u].visited = 2;
    list[u].f = time;
    time = time + 1;
}


int* reverseDFS(Graph G, Info *list, int size) {
    int* ids = (int*)can_fail_malloc(size*sizeof(int));
    int v, i = size-1;

    for (v = 0; v < G->V; v++) {
        list[v].f = 0;
        list[v].d = 0;
        list[v].pred = 0;
        list[v].visited = 0;
    }

    for(v = G->V - 1; v > 0; v--) {
        if(list[v].visited == 0) {
            ids[i--] = v;
            DFSaux(G, list, v);
        }
    }
    return ids;
}

/************************************************/




/***************** TARJAN ***********************/

void tarjan(Graph G, Info *list) {
    int v;
    for (v = 0; v < G->V; v++) {
        list[v].d = 0;
        list[v].pred = 0;
        list[v].visited = 0;
        list[v].low = 0;
        list[v].ap = 0;
    }

    for(v = 1; v < G->V; v++) {
        if(list[v].visited == 0)
            tarjanAux(G, list, v);
    }
}


void tarjanAux(Graph G, Info *list, int u) {

    int successor = 0;
    static int time = 0;
    time = time + 1;
    list[u].d = time;
    list[u].low = time;
    list[u].visited = 1;

    link p = G->adj[u];
    while (p != NULL) {
    	int v = p->v;

        if (list[v].visited == 0) {
            list[v].pred = u;
            successor++;
            tarjanAux(G, list, v);

            list[u].low = MIN(list[u].low, list[v].low);

            if(list[u].pred == 0 && successor >= 2)
                list[u].ap = 1;
            
            if(list[u].pred != 0 && list[v].low >= list[u].d) 
                list[u].ap = 1;
        }

        else if (v != list[u].pred)
            list[u].low = MIN(list[u].low, list[v].d);

        p = p->next;
    }
}

/************************************************/



/*************** COUNTING VERTEX ****************/

int maxcount = 0;
int count = 0;

int countV(Graph G, Info *list) {
    int v;
    for (v = 0; v < G->V; v++) {
        list[v].visited = 0;
    }

    for(v = 1; v < G->V; v++) {
        if (list[v].visited == 0 && list[v].ap == 0) {
            count = 0;
            countAux(G, list, v);
        }
    }
    return maxcount;
}


void countAux(Graph G, Info *list, int u) {
    list[u].visited = 1;
    count++;
    link p;
    if (count >= maxcount)
        maxcount = count;

    for (p = G->adj[u]; p != NULL; p = p->next) {
        int v = p->v;
        if(list[v].visited == 0 && list[v].ap == 0) {
            list[v].pred = u;
            countAux(G, list, v);
        }
        else if (list[v].ap == 1) {
            count = 0;
            break;
        }
    }
    list[u].visited = 2;
}

/************************************************/


int main(int argc, char** argv) {
    /**
    * N - number of routers
    * M - number of connections
    * */
    int N, M;
    int j = 0, temp[2];
    Graph routerG;

    scanf("%d", &N);
    scanf("%d", &M);

    /** init graph */
    routerG = GRAPHinit(N+1);

    /** scan input */
    while(j < M) {
        scanf("%d %d", &temp[0], &temp[1]);
        GRAPHinsertE(routerG, temp[0], temp[1]);
        j++;
    }

    /** list with info about each vertex **/
    Info* list = (Info*)can_fail_malloc((N+1)*sizeof(Info));


    /** find number of subnets **/
  	DFS(routerG, list); 

  	/** find articulation points **/
    tarjan(routerG, list);

  	int subnets = 0;  /** value of R **/
  	int ap = 0;		  /** value of C **/

	for(j = 1; j < routerG->V; j++) {
    	Info node = list[j];
    	if (node.pred == 0)
    		subnets++;
    	if (list[j].ap == 1)
    		ap++;
    }

    /** list of R ids **/
    int* ids = reverseDFS(routerG, list, subnets);

    printf("%d\n", subnets);
    for (j = 0; j < subnets; j++) {
    	if (j == subnets-1)
    		printf("%d\n", ids[j]);
    	else
    		printf("%d ", ids[j]);
    }
    printf("%d\n", ap);
    printf("%d\n", countV(routerG, list)); 
    				 /** value of m **/

    free(ids);
    free(list);

    link f, tmp;
    for(j = 0; j < routerG->V; j++) {
        for(f = routerG->adj[j]; f != NULL; ) {
            tmp = f;
            f = f->next;
            free(tmp);
        }
    }
    free(routerG->adj);
    free(routerG);

    return 0;
}
