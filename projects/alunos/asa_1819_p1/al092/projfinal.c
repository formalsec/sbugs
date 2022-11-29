#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define NOT_VISITED -1
#define IGNORED -10
#define TRUE 1
#define FALSE 0

char* inputFile = NULL;

typedef struct RouterR RouterR;
typedef struct NodeR NodeR;
typedef struct Problem Problem;

void printProblem(Problem* problem);
int* countSubnets(Problem* problem);
int isAllVisited(int visited[],  int size);
int getFirstNotVisited(int visited[], int size);
void visit(RouterR** listaRouters, RouterR* router, int visited[], int size, int cycle);
int* getSubNets(int* visited, int size, int nnets);
int getNumSubnets(int* visited, int size);
int countMaxRoutersInSubnet(int* visited, int size);
int contains(int array[], int size, int elem);
int* visitDFS(Problem* problem, int* visited);
void getBreakSubnets(Problem* problem, int nnets, int breakSubNets[]);
void printVisited(int visited[], int size);

typedef struct NodeR {
    int link;
    NodeR* next;
} NodeR;

typedef struct RouterR {
    int id;
    NodeR* adj;
} RouterR;

typedef struct Problem {
    int numRouters;
    RouterR** routerList;
    int* visited;
} Problem;

static Problem* parseArgs (long argc, char* const argv[]){

    /*if(argv[1] == NULL){
        printf("Missing input file.\n");
        exit(-1);
        inputFile = argv[1];
        fp = fopen(inputFile, "r");
        
    }
    FILE *fp;
    */
    int numRouters, numConnections;

    int u,v, i;
    scanf("%d%d", &numRouters, &numConnections);

    RouterR** routersR;
    routersR = can_fail_malloc(numRouters * sizeof(RouterR*));
    for (i = 0; i < numRouters; i++) {
        routersR[i] = (RouterR*)can_fail_malloc(sizeof(RouterR));
        routersR[i]->id = i;
        routersR[i]->adj = NULL;
    }

    for(i = 0; i < numConnections; i++) {
        scanf("%d%d", &u, &v);
        --u;
        --v;
        NodeR* newAdj = can_fail_malloc(sizeof(NodeR));
        newAdj->next = routersR[u]->adj;
        newAdj->link = v;
        routersR[u]->adj = newAdj;

        newAdj = can_fail_malloc(sizeof(NodeR));
        newAdj->next = routersR[v]->adj;
        newAdj->link = u;
        routersR[v]->adj = newAdj;
    }

    /* fclose(fp); */

    Problem* problem = can_fail_malloc(sizeof(Problem));
    problem->routerList = routersR;
    problem->numRouters = numRouters;
    return problem;
}

int main(int argc, char** argv){
    /* Get the problem structure */
    Problem* problem = parseArgs(argc, argv);
    int i;
    /* printProblem(problem); 

       Initialize the visited */
    int* visited = can_fail_malloc(sizeof(int) * problem->numRouters);
    for (i = 0; i < problem->numRouters; i++) {
        visited[i] = NOT_VISITED;
    }
    /* Visit nodes */
    visitDFS(problem, visited);
    /* printVisited(visited, problem->numRouters);

      Print number of subnets */
    int nnets = getNumSubnets(visited, problem->numRouters);
    printf("%d\n", nnets);

    /* Get IDs of subnets */
    int* subNets = getSubNets(visited, problem->numRouters, nnets);

    for (i = nnets - 1; i > 0; i--) {
        printf("%d ", subNets[i] + 1);
    }
    printf("%d\n", subNets[0]+1);

    /* Get number of routers that break subnets */
    int* breaksSubnets = can_fail_malloc(sizeof(int) * problem->numRouters);
    getBreakSubnets(problem, nnets, breaksSubnets);
    int numRoutersThatBreakSubnet = 0;
    for (i = 0; i < problem->numRouters; i++) {
        if (breaksSubnets[i]) {
            ++numRoutersThatBreakSubnet;
        }
    }
    printf("%d\n", numRoutersThatBreakSubnet);


    /* Number of subnets if all that break subnets are removed */
    for (i = 0; i < problem->numRouters; i++) {
        visited[i] = breaksSubnets[i] ? IGNORED : NOT_VISITED;
    }
    visitDFS(problem, visited);
    int maxInSubnet = countMaxRoutersInSubnet(visited, problem->numRouters); 
    printf("%d\n", maxInSubnet);


    for(i=0; i< problem->numRouters;i++){
        NodeR* adj = problem->routerList[i]->adj;
        while(adj != NULL){
            NodeR* temp = adj->next;
            free(adj);
            adj = temp;
        }
        free(problem->routerList[i]);
    }
    free(problem->routerList);
    free(problem);
    free(breaksSubnets);
    free(subNets);
    free(visited);
    return 0;
}

void getBreakSubnets(Problem* problem, int nnets, int breaksSubnets[]) {
    int i, j;
    for (i = 0; i < problem->numRouters; i++) {
        breaksSubnets[i] = FALSE;
    }
    int* visited = can_fail_malloc(sizeof(int) * problem->numRouters);
    for (j = 0; j < problem->numRouters; j++) {
        for (i = 0; i < problem->numRouters; i++) {
            /* STUCK */

            visited[i] = NOT_VISITED;

        }
        visited[j] = IGNORED;
        visitDFS(problem, visited);
        if (getNumSubnets(visited, problem->numRouters) > nnets) {
            breaksSubnets[j] = TRUE;
        }
    }
    free(visited);
}

void printVisited(int visited[], int size) {
    printf("VISITED: ");
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", visited[i]);
    }
    printf("\n");
}

int* getSubNets(int* visited, int size, int nnets) {
    int array[nnets];
    int i, j;
    int* subNets = can_fail_malloc(sizeof(int) * nnets);
    for (i = 0; i < nnets; i++) {
        array[i] = NOT_VISITED;
    }
    for (j= 0; j < nnets; j++) {
        for (i = size - 1; i >= 0; i--) {
            if (contains(array, nnets, visited[i]) == FALSE) {
                subNets[j] = i;
                array[j] = visited[i];
                break;
            }
        }
    }
    return subNets;
}

int contains(int array[], int size, int elem) {
    int i;
    for (i = 0; i < size; i++) {
        if (array[i] == elem) {
            return TRUE;
        }
    }
    return FALSE;
}

int getNumSubnets(int* visited, int size) {
    int max = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (max < visited[i]) {
            max = visited[i];
        }
    }
    ++max;
    return max;
}

int countMaxRoutersInSubnet(int* visited, int size){
    int maxOcc = 0;
    int i;
    int array[size];
    for(i = 0; i < size; i++){
        array[i]=0;
    }

    for(i = 0; i < size; i++){
        array[visited[i]]++;
    }

    for(i = 0; i < size; i++){
        if (array[i] > maxOcc){
            maxOcc = array[i];
        }
    }
    return maxOcc;
}

int* visitDFS(Problem* problem, int* visited) {
    int i;
    for (i = 0; !isAllVisited(visited, problem->numRouters) && i < problem->numRouters; i++) {
        RouterR* next = problem->routerList[getFirstNotVisited(visited, problem->numRouters)];
        visit(problem->routerList, next, visited, problem->numRouters, i);
    }
    return visited;
}

void visit(RouterR** listaRouters, RouterR* router, int visited[], int size, int cycle) {
    NodeR* adj = router->adj;
    visited[router->id] = cycle;
    while (adj != NULL) {
        if (visited[adj->link] == NOT_VISITED) {
            visit(listaRouters, listaRouters[adj->link], visited, size, cycle);
        }
        adj = adj->next;
    }
}

int getFirstNotVisited(int visited[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (visited[i] == NOT_VISITED) {
            return i;
        }
    }
    return -1;
}

int isAllVisited(int visited[], int size) {
    int isAll = TRUE;
    int i;
    for (i = 0; i < size; i++) {
        if (visited[i] == NOT_VISITED) {
            isAll = FALSE;
            break;
        }
    }
    return isAll;
}

void printProblem(Problem* problem) {
    printf("Problem\n");
    printf("Num of routers: %d\n", problem->numRouters);
    int i;
    for (i = 0; i < problem->numRouters; i++) {
        printf("Router %d links: ", i);
        NodeR* no = problem->routerList[i]->adj;
        while (no != NULL) {
            printf("%d ", no->link);
            no = no->next;
        }
        printf("\n");
    }
}
