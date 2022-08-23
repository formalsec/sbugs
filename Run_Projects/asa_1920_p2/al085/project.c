/* Duarte Penalva Boto n92457 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 128

#define INCOMING 0
#define OUTGOING 1

int nBoulevards, nStreets;
int nMarkets, nCitizens;

typedef struct node {
    int adj;
    struct node* next;
} node;
node **adjList;

int sIndex, tIndex;

int *colors;
int *parents;

int found;
int done;
int flux;

void DFSvisit(int u);
void clearDFS();
void increasePath();
void increaseArc(int u, int v);

int getIndex(int b, int s, int out);
void processInput();
void initGraph();
void freeGraph();
void addAdjacency(int u, int v);
int removeAdjacency(int u, int v);

int main() {
    processInput();
    /*printf("Done with Input\n");*/

    /* Init DFS */
    clearDFS();
    found = 0;
    done = 0;
    flux = 0;

    /* Ford-Fulkerson */ 
    while (!done) {
        DFSvisit(sIndex);
        if (!found) done = 1;
        else {
            clearDFS();
            found = 0;
        }
    }

    printf("%d\n", flux);

    freeGraph();
    return 0;
}

void DFSvisit(int u) {
    if (found) return;
    colors[u] = 1;
    node *adj = adjList[u];
    while (adj != NULL) {
        int v = adj->adj;
        if (colors[v] == 0) {
            parents[v] = u;
            if (v == tIndex) {
                found = 1;
                increasePath();
            } else {
                DFSvisit(v);
            }
        }
        if (found) break;
        adj = adj->next;
    }
    colors[u] = 2;
}

void clearDFS() {
    memset(colors, 0, ((nBoulevards * nStreets * 2) + 2) * sizeof(int));
    int i;
    for (i = 0; i < (nBoulevards * nStreets * 2) + 2; i++) {
        parents[i] = -1;
    }
}

void increasePath() {
    if (!found) return;
    int current = tIndex;
    while (parents[current] != -1) {
        increaseArc(parents[current], current);
        current = parents[current];
    }
    flux++;
}

void increaseArc(int u, int v) {
    int suc = removeAdjacency(u, v);
    if (suc) addAdjacency(v, u);
}

void processInput() {
    int i;
    char buffer[BUFFER_SIZE];

    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%d %d", &nBoulevards, &nStreets);

    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%d %d", &nMarkets, &nCitizens);

    initGraph();

    char *indexKeeper = malloc((nBoulevards * nStreets * 2) * sizeof(char));

    memset(indexKeeper, 0, (nBoulevards * nStreets * 2) * sizeof(char));
    for (i = 0; i < nMarkets; i++) {
        int b, s;
        fgets(buffer, BUFFER_SIZE, stdin);
        sscanf(buffer, "%d %d", &b, &s);

        indexKeeper[getIndex(b, s, OUTGOING)] = 1;
    }
    for (i = 0; i < (nBoulevards * nStreets * 2); i++) {
        if (indexKeeper[i]) {
            addAdjacency(i, tIndex);
        }
    }

    memset(indexKeeper, 0, (nBoulevards * nStreets * 2) * sizeof(char));
    for (i = 0; i < nCitizens; i++) {
        int b, s;
        fgets(buffer, BUFFER_SIZE, stdin);
        sscanf(buffer, "%d %d", &b, &s);

        indexKeeper[getIndex(b, s, INCOMING)] = 1;
    }
    for (i = 0; i < (nBoulevards * nStreets * 2); i++) {
        if (indexKeeper[i]) {
            addAdjacency(sIndex, i);
        }
    }

    free(indexKeeper);
}

int getIndex(int b, int s, int out) {
    return ((s - 1) * nBoulevards + (b - 1)) * 2 + out; 
}

void initGraph() {
    int i = 0;

    adjList = malloc(((nBoulevards * nStreets * 2) + 2) * sizeof(node*));
    memset(adjList, 0, ((nBoulevards * nStreets * 2) + 2) * sizeof(node*));

    for (i = 0; i < (nBoulevards * nStreets * 2); i++) {
        if (i % 2 == 0) {
            addAdjacency(i, i + 1);
        } else {
            if (i >= nBoulevards * 2) {
                addAdjacency(i, (i - nBoulevards * 2) - 1);
            }
            if (i < (nBoulevards * nStreets * 2) - nBoulevards * 2) {
                addAdjacency(i, (i + nBoulevards * 2) - 1);
            }
            if (i % (nBoulevards * 2) > 1) {
                addAdjacency(i, i - 3);
            }
            if (i % (nBoulevards * 2) < nBoulevards * 2 - 2) {
                addAdjacency(i, i + 1);
            }
        }     
    }

    sIndex = (nBoulevards * nStreets * 2) + 1;
    tIndex = (nBoulevards * nStreets * 2);

    colors = malloc(((nBoulevards * nStreets * 2) + 2) * sizeof(int));
    parents = malloc(((nBoulevards * nStreets * 2) + 2) * sizeof(int));
    clearDFS();
}

void freeGraph() {
    int i;
    for (i = 0; i < (nBoulevards * nStreets * 2) + 2; i++) {
        node *adj = adjList[i];
        while (adj != NULL) {
            node *temp = adj;
            adj = adj->next;
            free(temp);
        }
    }
    free(adjList);
    free(colors);
    free(parents);
}

void addAdjacency(int u, int v) {
    node *new = malloc(sizeof(node));
    new->next = adjList[u];
    new->adj = v;
    adjList[u] = new;
}

int removeAdjacency(int u, int v) {
    node *temp = adjList[u];
    node *prev = NULL;
    while (temp != NULL) {
        if (temp->adj == v) {
            if (prev != NULL) prev->next = temp->next;
            else adjList[u] = temp->next;
            free(temp);
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}
