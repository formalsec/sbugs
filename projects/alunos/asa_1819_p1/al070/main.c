#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Grupo 70
// 89423, Catarina Machuqueiro
// 89533, Raquel Santos
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Estruturas */

typedef struct router{
    int num;
    struct router *next;
}Router;


typedef struct{
    int nrouters, nsubnet;
    int* visited, *des, *low, *parent, *ap, *subnetids;
    Router** adjLists;
}Network;


Router* create_router(int n){
    Router* router = can_fail_malloc(sizeof(Router));
    router->num = n;
    router->next = NULL;
    return router;
}


Network* net;

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcoes auxiliares */

int min(int a, int b){
    return(a < b ? a : b);
}


int find_max (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


void create_network(int n){
    int i;

    net = can_fail_malloc(sizeof(Network));
    net->nrouters = n;
    net->nsubnet = 0;
    net->adjLists = can_fail_malloc(sizeof(Router*) * n);
    net->subnetids = can_fail_malloc(sizeof(int) * n);
    net->visited = can_fail_calloc(n,sizeof(int));
    net->des = can_fail_calloc(n, sizeof(int));
    net->low = can_fail_calloc(n, sizeof(int));
    net->parent = can_fail_calloc(n, sizeof(int));
    net->ap = can_fail_calloc(n, sizeof(int));

    for (i = 0; i < n; i++){
        net->adjLists[i] = NULL;
        create_router(i);
    }
}


void add_connection(int u, int v){
    Router* router = create_router(v);
    router->next = net->adjLists[u-1];
    net->adjLists[u-1] = router;

    router = create_router(u);
    router->next = net->adjLists[v-1];
    net->adjLists[v-1] = router;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


void read_input() {
    int nconnections, nrouters;
    int i, u, v;

    scanf("%d %d", &nrouters, &nconnections);

    create_network(nrouters);

    for (i = 0; i < nconnections; i++) {
        scanf("%d %d", &u, &v);
        add_connection(u, v);
    }
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


void recursive(int router, int* visited, int* cont){
    Router* next = net->adjLists[router - 1];
    visited[router - 1] = 1;
    *cont = *cont + 1;

    while (next != NULL){
        if (!visited[next->num - 1])
            recursive(next->num, visited, cont);
        next = next->next;
    }
}


void simple_DFS(){
    int i, cont;
    int max = 0;
    int *visited = net->visited;

    for (i = 0; i < net->nrouters; i++)
        if (!net->visited[i]) {
            cont = 0;
            recursive(i + 1, visited, &cont);
            if (cont > max)
                max = cont;
        }
    printf("\n%d\n", max);
}


void DFS_visit(int router, int* time, int* subnetids, int* visited, int* des, int* low, int* parent, int* ap){
    Router* next = net->adjLists[router - 1];
    int children = 0;
    visited[router-1] = 1;
    des[router-1] = low[router - 1] = *time;
    *time = *time + 1;

    while (next != NULL){
        if (!visited[next->num - 1]){

            if (next->num > *subnetids)
                *subnetids = next->num;

            children++;
            parent[next->num - 1] = router;
            DFS_visit(next->num, time, subnetids, visited, des, low, parent, ap);
            low[router - 1] = min(low[router - 1], low[next->num - 1]);

            if((parent[router - 1] == 0 && children > 1) /*raiz com mais de um filho*/
               || (parent[router - 1] != 0 && des[router - 1] <= low[next->num -1])){
                ap[router-1] = 1;
            }
        }

        else if ((next->num != parent[router - 1]))
            low[router - 1] = min(low[router - 1], des[next->num - 1]);

        next = next->next;
    }
}


int DFS(){
    int i, nsubnet = 0, time = 0;
    int *visited = net->visited, *des = net->des, *low = net->low,
            *subnetids = net->subnetids, *parent = net->parent, *ap = net->ap;

    for (i = 0; i < net->nrouters; i++)
        if (!net->visited[i]) {
            subnetids[nsubnet] = i + 1;
            DFS_visit(i + 1, &time, &subnetids[nsubnet], visited, des, low, parent, ap);
            nsubnet++;
        }
    return nsubnet;
}


void printOutput(int nsubnet){
    int i, breakrouters = 0;

    printf("%d\n",nsubnet);

    qsort(net->subnetids, nsubnet, sizeof(int), find_max);

    if(nsubnet > 1) {
        for (i = 0; i < (nsubnet - 1); i++)
            printf("%d ", net->subnetids[i]);
        printf("%d", net->subnetids[i]);
    }
    else{
        printf("%d", net->subnetids[0]);
    }

    for(i=0; i< net->nrouters;i++) {
        net->visited[i] = 0;
        if (net->ap[i] == 1) {
            breakrouters++;
            net->visited[i] = 1;
        }
    }
    printf("\n%d",breakrouters);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


int main() {
    read_input();
    int nsubnet = DFS();
    printOutput(nsubnet);
    simple_DFS();
    return 0;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/