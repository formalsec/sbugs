#include <stdio.h>
#include <stdlib.h>

struct node {
   int  id;
   int  capa;
};

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_NODES 1000
#define oo 1000000000

int n;  // number of nodes
int e;  // number of edges
int capacity[MAX_NODES][MAX_NODES]; // capacity matrix
int flow[MAX_NODES][MAX_NODES];     // flow matrix
int color[MAX_NODES]; // needed for breadth-first search               
int pred[MAX_NODES];  // array to store augmenting path

int min (int x, int y) {
    return x<y ? x : y;  // returns minimum of x and y
}

int head,tail;
int q[MAX_NODES+2];

void enqueue (int x) {
    q[tail] = x;
    tail++;
    color[x] = GRAY;
}

int dequeue () {
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}

int bfs (int start, int target) {
    int u,v;
    for (u=0; u<n; u++) {
	color[u] = WHITE;
    }   
    head = tail = 0;
    enqueue(start);
    pred[start] = -1;
    while (head!=tail) {
	u = dequeue();
        // Search all adjacent white nodes v. If the capacity
        // from u to v in the residual network is positive,
        // enqueue v.
	for (v=0; v<n; v++) {
	    if (color[v]==WHITE && capacity[u][v]-flow[u][v]>0) {
		enqueue(v);
		pred[v] = u;
	    }
	}
    }
    // If the color of the target node is black now,
    // it means that we reached it.
    return color[target]==BLACK;
}

int max_flow (int source, int sink) {
    int i,j,u;
    // Initialize empty flow.
    int max_flow = 0;
    for (i=0; i<n; i++) {
	for (j=0; j<n; j++) {
	    flow[i][j] = 0;
	}
    }
    // While there exists an augmenting path,
    // increment the flow along this path.
    while (bfs(source,sink)) {
        // Determine the amount by which we can increment the flow.
	int increment = oo;
	for (u=n-1; pred[u]>=0; u=pred[u]) {
	    increment = min(increment,capacity[pred[u]][u]-flow[pred[u]][u]);
	}
        // Now increment the flow.
	for (u=n-1; pred[u]>=0; u=pred[u]) {
	    flow[pred[u]][u] += increment;
	    flow[u][pred[u]] -= increment;
	}
	max_flow += increment;
    }
    // No augmenting path anymore. We are done.
    return max_flow;
}















int main(){
    int forn, abas, conec, v1, i, j, l, v2, v3, v4, v5, max=0;
    scanf("%d %d %d",&forn,&abas,&conec);

    struct node forn1[forn+abas];
    int matr[forn+abas][forn+abas];

    for(i=2;i<=forn+1;i++){
        scanf("%d",&v1);
        struct node a;
        a.id = i;
        a.capa = v1;
        forn1[i] = a;
    }


    for(j=0;j<=abas;j++){
        scanf("%d",&v2);
        struct node a1;
        a1.id = i;
        a1.capa = v2;
        forn1[i] = a1;
        i ++;
    }

    for (i=0; i<forn+abas; i++) {
	    for (j=0; j<forn+abas; j++) {
	        matr[i][j] = 0;
	    }
    }

    for(l=0;l<conec;l++){
        scanf("%d %d %d",&v3,&v4,&v5);
        if(forn1[v3].capa > v5){
            matr[v3][v4] = v5 - forn1[v3].capa;
        }else{
            matr[v3][v4] = forn1[v3].capa;
        }
    }

    int p,comp;
    for(p=2;p<forn + abas;p++){
        comp = max_flow(p,1); 
        if(comp >= max){
            max = comp;
        }
    }

    printf("%d", max);


    return 0;
}
