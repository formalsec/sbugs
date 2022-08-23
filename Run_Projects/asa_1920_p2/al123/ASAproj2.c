#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct index {
    int id;
    int capacity;
    struct index* pnext;
};

struct vertex{
    int x;
    int y;
};

struct node {
    int id;
    bool visited;
    struct index* index_adj;
    struct vertex* vertex;
    struct node* next;
};

struct Graph {
    int numVertices;
    struct node** adjLists;
};

bool pathfound = false;
int pathcount = 0;


struct node* getNode(struct Graph* graph, int id){
    return graph->adjLists[id];
}

void atCapacities(struct node* node, struct node* auxnode, struct Graph* graph){
    struct index* naux = node->index_adj;
    while(naux->id != auxnode->id){
        naux = naux->pnext;
    }
    naux->capacity = 0;
    struct index* aux = auxnode->index_adj;
    while(aux->id != node->id){
        aux = aux->pnext;
    }
    aux->capacity = 1;
}

bool dfsvisited(int v, struct Graph* graph, struct node* sink){
    struct index* naux = sink->index_adj;
    while (naux!=NULL) {
        if (v == naux->id) {
            pathfound = true;
            pathcount++;
            return pathfound;
        }
        naux = naux->pnext;
    }
    graph->adjLists[v]->visited = true;
    struct index* paux = graph->adjLists[v]->index_adj;
    while (paux != NULL){
        int nextvertice = paux->id;
        if(graph->adjLists[nextvertice]->visited == false && paux->capacity == 1){
            dfsvisited(nextvertice, graph, sink);
            if(pathfound){
                atCapacities(graph->adjLists[v], graph->adjLists[paux->id], graph);
                return true;
            }
        }
        paux = paux->pnext;
    }
    return false;
}

int dfs(struct node* source, struct Graph* graph, struct node* sink){
    int j;
    struct index* paux = source->index_adj;
    while(paux != NULL) {
            for (j = 0; j < graph->numVertices; j++) {
                graph->adjLists[j]->visited = false;
            }
            dfsvisited(paux->id, graph, sink);
            pathfound = false;
            paux = paux->pnext;
    }
    return pathcount;
}

struct node* createNode(int id, int x , int y) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->id = id;
    newNode->visited = false;
    newNode->index_adj = NULL;
    newNode->vertex = calloc(1, sizeof(struct vertex));
    newNode->vertex->x = x;
    newNode->vertex->y = y;
    newNode->next = NULL;
    return newNode;
}


void addEdge(struct node* node, int id){
    if (node->index_adj == NULL) {
        struct index *index = calloc(1, sizeof(struct index));
        node->index_adj = index;
        node->index_adj->id = id;
        node->index_adj->capacity = 1;
    } else {
        struct index *paux = node->index_adj;
        while (paux->pnext != NULL) {
            paux = paux->pnext;
        }
        paux->pnext = calloc(1, sizeof(struct index));
        paux->pnext->id = id;
        paux->pnext->capacity = 0;
        paux->pnext->pnext = NULL;
    }

}

void addEdgeout(struct node* node, int id){
    if (node->index_adj == NULL) {
        struct index *index = calloc(1, sizeof(struct index));
        node->index_adj = index;
        node->index_adj->id = id;
        node->index_adj->capacity = 0;
    } else {
        struct index *paux = node->index_adj;
        while (paux->pnext != NULL) {
            paux = paux->pnext;
        }
        paux->pnext = calloc(1, sizeof(struct index));
        paux->pnext->id = id;
        paux->pnext->capacity = 1;
        paux->pnext->pnext = NULL;
    }

}

struct Graph* createGraph(int n_avenues, int n_streets) {
    int i, j, x = 1, y = 1;
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = 2 * n_avenues * n_streets + 2;
    graph->adjLists = calloc(graph->numVertices,sizeof(struct node*));

    for(i = 0; i < n_avenues; i++, x++) {
        for (j = 0; j < n_streets; j++, y++) {
            struct node* newNode = createNode(i*n_streets+j, x, y);
            newNode->next = graph->adjLists[i*n_streets+j];
            graph->adjLists[i*n_streets+j] = newNode;
        }
        y = 1;
    }
    x = 1;
    y = 1;
    for(i = 0; i < n_avenues; i++, x++) {
        for (j = 0; j < n_streets; j++, y++) {
            struct node* newNode = createNode((n_avenues*n_streets) + i*n_streets+j, x, y);
            newNode->next = graph->adjLists[(n_avenues*n_streets) + i*n_streets+j];
            graph->adjLists[(n_avenues*n_streets) + i*n_streets+j] = newNode;
        }
        y = 1;
    }
    x = 1;
    y = 1;
    for(i = 0; i < n_avenues; i++, x++) {
        for (j = 0; j < n_streets; j++, y++) {
            struct node* auxNode = getNode(graph, (i*n_streets)+j);
            addEdge(auxNode, (n_avenues*n_streets) + (i*n_streets)+j);
            if (y > 1){
                addEdge(auxNode, (n_avenues*n_streets) + i*n_streets + j - 1);
            }
            if(x > 1){
                addEdge(auxNode, (n_avenues*n_streets) + (i-1)*n_streets + j);
            }
            if (y < n_streets){
                addEdge(auxNode, (n_avenues*n_streets) + i*n_streets + j + 1);
            }
            if (x < n_avenues){
                addEdge(auxNode, (n_avenues*n_streets) + (i+1)*n_streets + j);
            }
        }
        y = 1;
    }
    x = 1;
    y = 1;
    for(i = 0; i < n_avenues; i++, x++) {
        for (j = 0; j < n_streets; j++, y++) {
            struct node* auxNode = getNode(graph, (n_avenues*n_streets) + (i*n_streets)+j);
            addEdgeout(auxNode, (i*n_streets)+j);
            if (y > 1){
                addEdgeout(auxNode, i*n_streets + j - 1);
            }
            if(x > 1){
                addEdgeout(auxNode, (i-1)*n_streets + j);
            }
            if (y < n_streets){
                addEdgeout(auxNode, i*n_streets + j + 1);
            }
            if (x < n_avenues){
                addEdgeout(auxNode, (i+1)*n_streets + j);
            }
        }
        y = 1;
    }
    struct node* source = createNode(2 * n_avenues * n_streets, 0, 0);
    source->next = graph->adjLists[2 * n_avenues * n_streets];
    graph->adjLists[2 * n_avenues * n_streets] = source;
    struct node* sink = createNode(2 * n_avenues * n_streets + 1, 0, 0);
    sink->next = graph->adjLists[2 * n_avenues * n_streets + 1];
    graph->adjLists[2 * n_avenues * n_streets + 1] = sink;
    return graph;
}

void addPessoa(int x, int y, struct node* node, int n_streets){
    addEdge(node, (x-1)*n_streets + (y-1));
}

void addMall(int n_avenues, int x, int y, struct node* node, int n_streets){
    addEdge(node, (n_avenues*n_streets) + (x-1)*n_streets + (y-1));
}

int main(){
    int i, j, c;
    int x, y;
    int n_avenues, n_streets, n_malls, n_persons;
    scanf("%d %d", &n_avenues, &n_streets);
    scanf("%d %d", &n_malls, &n_persons);
    struct Graph* graph = createGraph(n_avenues , n_streets);
    for (i = 0; i < n_malls; i++) {
        scanf("%d %d", &x, &y);
        addMall(n_avenues, x, y, graph->adjLists[2 * n_avenues * n_streets + 1], n_streets);
    }
    for (j = 0; j < n_persons; j++) {
        scanf("%d %d", &x, &y);
        addPessoa(x, y, graph->adjLists[2 * n_avenues * n_streets], n_streets);
    }
    c = dfs(graph->adjLists[2 * n_avenues * n_streets], graph, graph->adjLists[2 * n_avenues * n_streets + 1]);
    printf("%d\n", c);
    return 0;
}
