#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*  -----------------------------------------------
                ASA - Grupo 26 - LeicTP
            Carolina Resende    Tomas Nunes
                87640              90780
    -----------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define  MIN(x,y) ((x<y)?x:y)
#define  INFINITE  2147483646


int* verticeslist=NULL;
int* breaks;
int* nredes=NULL;

 
/* Estrutura de um vertice, que para o proximo na stack. */
typedef struct vertex {
    int _vertex;
    struct vertex *_nextNode;
} VertexNode;
 
/* Nodo de uma lista de ligacoes. */
typedef struct edgenode {
    int _end;
    struct edgenode *_nextNode;
}   EdgeNode;
 
/* Estrutura com o numero de vertices e de ligacoes, e com a lista de adjacencias
contendo as ligacoes dos vertices. */
typedef struct graph {
    int _v;
    int _e;
    EdgeNode** _adjacencyList;
}   Graph;
 
typedef struct info {
    int _V;
    int _numSCCs;
    int _visited;
    bool* _AP;                          
    int* _parent;                       
    int* _d;                            
    int* _low;                          
    int* _isInStack;                   
    int* _SCCid;                        
    VertexNode* _stackHead;             
} TarjanInfo;
 
Graph* inicGraph (int v, int e );
void insertInGraph (Graph* G, int u, int v);
TarjanInfo* inicTarjanInfo(int v);
TarjanInfo* Tarjan (Graph* g );
void TarjanVisit(Graph* g, TarjanInfo *ti, int u);
void pushStackVertex (TarjanInfo *ti, int u);
void popStackVertex (TarjanInfo *ti);
int find_SCCid (TarjanInfo* ti, int u);
void count_remove_AD (Graph* g, TarjanInfo *ti);


/*  -------------------- INPUT --------------------
    (line 1)   N number of routers (aka vertices)
    (line 2)   M number of links between routers
    (M lines)  pairs of vertices representing a link
    ------------------------------------------------
*/
Graph* readInput (int *Vptr, int *Eptr) {
    int V = 0, E = 0, u, v;
    Graph *g;

    if (fscanf(stdin, "%d", &V) != 1) {
        printf("Erro ao ler de stdin \n");
        exit (1);
    }
 
    if (fscanf(stdin, "%d", &E) != 1 ) {
        printf("Erro ao ler de stdin \n");
        exit (1);
    }
 
    *Vptr = V;
    *Eptr = E;
 
    g = inicGraph(V, E);
    while (E > 0) {
        if (fscanf(stdin, "%d %d", &u, &v ) != 2) {
            printf("Erro ao ler de stdin \n");
            exit (1);
        }
        insertInGraph(g, u - 1, v - 1);
        insertInGraph(g, v - 1, u - 1);
        E--;
    }
 
    return g;
}


/*  ------------------ inicGraph -------------------
    Alocates space for the Graph and AdjacencyList 
    and initializes all values to NULL
    ------------------------------------------------
*/
Graph* inicGraph (int v, int e ) {
    Graph *g;
    int i = 0;
    g = can_fail_malloc(sizeof(Graph));

    if (g == NULL ) {
        printf("erro em inicGraph\n");
        exit(0);
    }

    g->_v = v;
    g->_e = e;
    g->_adjacencyList = can_fail_malloc(sizeof(EdgeNode*) * v);
 
    if (g->_adjacencyList == NULL ) {
        printf("erro em inicGraph\n");
        exit(0);
    }
 
    for (i = 0; i < v; i++)
        g->_adjacencyList[i] = NULL;
 
    return g;

}


/*  ---------------- insertInGraph -----------------
    Adds links onto the AdjacencyList
    (all graphs are undirected, 
    therefore the link between u and v also refers 
    to the link between v and u)
    ------------------------------------------------
*/
void insertInGraph (Graph* G, int u, int v) {
    EdgeNode* e = can_fail_malloc(sizeof(EdgeNode));

    if (e == NULL) {
        printf("erro ao fazer push para graph\n");
        exit(0);
    }
 
    e->_end = v;
    e->_nextNode = G->_adjacencyList[u];
    G->_adjacencyList[u] = e; 
}


/*  --------------- inicTarjanInfo ----------------
    Alocates space and initializes all fields 
    related to structure TarjanInfo
    -----------------------------------------------
*/ 
TarjanInfo* inicTarjanInfo(int v) {
    int i = 0;
    TarjanInfo *ti = can_fail_malloc(sizeof(TarjanInfo));

    if (ti == NULL ) {
        printf("erro no inicTarjan\n");
        exit(0);
    }

    ti->_V         = v;
    ti->_numSCCs   = 0;
    ti->_visited   = 0;
    ti->_AP        = can_fail_malloc(sizeof(int) * v);
    ti->_parent    = can_fail_malloc(sizeof(int) * v);
    ti->_d         = can_fail_malloc(sizeof(int) * v);
    ti->_low       = can_fail_malloc(sizeof(int) * v);
    ti->_isInStack = can_fail_malloc(sizeof(int) * v);
    ti->_SCCid     = can_fail_malloc(sizeof(int) * v);
    

    if (ti->_parent == NULL || ti->_d == NULL || ti->_low == NULL || ti->_isInStack == NULL ) {
        printf("erro no inicTarjanInfo\n");
        exit(0);
    }

    ti->_stackHead = NULL;
 
    for (i = 0; i < v; i++) {
        ti->_parent[i]    = -1;
        ti->_d[i]         = INFINITE;
        ti->_low[i]       = INFINITE;
        ti->_isInStack[i] = false;
        ti->_SCCid[i]     = -1;
    }
 
    return ti;
}
 


/*  ------------------- Tarjan --------------------
    Tarjan's Algorithm function calls TarjanVisit
    for each non discovered vertex it encounters
    -----------------------------------------------
*/
TarjanInfo* Tarjan (Graph* g ) {
    breaks=can_fail_malloc(sizeof(int));
    *breaks=1;

    nredes=NULL;
    nredes=can_fail_malloc((sizeof(int))*2);

    int i = 0;
    int max = g->_v;
    
    verticeslist=can_fail_malloc((sizeof(int))*2);

    TarjanInfo* ti = inicTarjanInfo(g->_v);

    for (i = 0; i < max; i++) {

        if (ti->_d[i] == INFINITE) {

            if(i==0){
                nredes[0]=1;
                TarjanVisit(g, ti, i);
            }

            else{
                *breaks=*breaks+1;

                verticeslist=(int*) can_fail_realloc(verticeslist, (sizeof(int))*(*(breaks)-1));
                nredes=(int*) can_fail_realloc(nredes, (sizeof(int))*(*breaks-1));
             
                verticeslist[*breaks-2]=i;
                nredes[*breaks-1]=nredes[*breaks-1]+1;

                TarjanVisit(g, ti, i);
            }
        }
    }
    verticeslist[*breaks-1]=max;

    return ti;
}
 


/*  ----------------- TarjanVisit ------------------
    Vertex u was seen as undiscovered by Tarjan, 
    therefore it must be put into the visited list.
    Same logic applied to the vertices in u's 
    adjacencyList where Articulation points are also 
    recognized
    -----------------------------------------------
*/
void TarjanVisit(Graph* g, TarjanInfo *ti, int u) {
    EdgeNode* aux = NULL;
    int v;
    int aux2;
    int min;
    int child = 0;

    ti->_visited ++ ;
    ti->_d[u] = ti->_visited;
    ti->_low[u] = ti->_visited;
   
    pushStackVertex (ti, u);


    for (aux = g->_adjacencyList[u]; aux != NULL ; aux = aux->_nextNode) {
        v = aux->_end;
        
        if (ti->_d[v] == INFINITE || ti->_isInStack[v] == true ) {
            
            if (ti->_d[v] == INFINITE) {
                nredes[*breaks-1]=nredes[*breaks-1]+1;
                child ++;
                ti->_parent[v] = u;
                
                TarjanVisit(g, ti, v);

                ti->_low[u] = MIN(ti->_low[v], ti->_low[u]);
              
                if ((ti->_parent[u] != -1) && (ti->_low[v]>=ti->_d[u])) {
                    ti->_AP[u] = true;
                }

                /* Checks if u is the root node or not and child > 1 */
                if ((ti->_parent[u] == -1) && (child>1)){
                    ti->_AP[u] = true;
                }
            }

            else if (v !=ti->_parent[u]) {
                    ti->_low[u]=MIN(ti->_low[u],ti->_d[v]);
            }

            ti->_low[u] = MIN(ti->_low[v], ti->_low[u]);
        }
    }             
    
    if (ti->_d[u] == ti->_low[u]) {
        /* If the discovery value is equal to the vertex low value, the algorithm removes from stack all vertices together, forming a SCC */
        min = find_SCCid(ti, u);
 
        while (1) {
            aux2 = ti->_stackHead->_vertex;
            ti->_SCCid[aux2] = min + 1;
            popStackVertex(ti);
            if (aux2 == u) {
                ti->_numSCCs ++;
                break;
            }
        }
    }

}
 



/*  ----------------- find_SCCid ------------------
    Identifies a SCC's id
    -----------------------------------------------
*/
int find_SCCid (TarjanInfo* ti, int u) {
    VertexNode* aux = NULL;
    int min = ti->_V + 1;

    for (aux = ti->_stackHead; aux != NULL; aux = aux->_nextNode) {
        min = MIN(min, aux->_vertex);

        if (aux->_vertex == u) { return min; }
    }
    return -1;
}



/*  -------------- push & pop vertex --------------
    Functions that add or remove a vertex from the
    stack's head
    -----------------------------------------------
*/
void pushStackVertex (TarjanInfo *ti, int u) {
    VertexNode *new = can_fail_malloc(sizeof(VertexNode));

    if (new == NULL) {
        printf("erro no push TARJAN\n");
        exit(0);
    }
    new->_vertex = u;
    new->_nextNode = ti->_stackHead;
    ti->_stackHead = new;
    ti->_isInStack[u] = true;
}
 
void popStackVertex (TarjanInfo *ti) {
    int u = ti->_stackHead->_vertex;
    VertexNode *newhead = ti->_stackHead->_nextNode;
    free(ti->_stackHead);
    ti->_stackHead = newhead;
    ti->_isInStack[u] = false;
}
 


/*  --------------- count_remove_AP ---------------
    Function counts the number of articulation 
    points and at the same time, removes its links
    with other vertices from its adjacency list
    -----------------------------------------------
*/
void count_remove_AP (Graph* g, TarjanInfo *ti) {
    int i = 0;
    int count = 0;
    int N = g->_v;

    for (i = 0 ; i < N ; i++) {
        if (ti->_AP[i] == true) {
                count++;
                g->_adjacencyList[i] = NULL;
            }
    }
    
    printf("%d\n", count);
}
 




/*  -----------------------------------------------
    -----------------------------------------------
    -----------------------------------------------
*/
int main(int argc, char *argv[]) {
    int V = 0;
    int maxnum=0;
    int max = 0;
    int E = 0;
    int i=0;
 
    Graph* g = NULL;
    TarjanInfo *ti = NULL;

 
    g = readInput( &V, &E);
    ti = Tarjan(g);

    puts("\nOutput:");
    printf("%d\n", ti->_numSCCs);

    for (i=0;i<*breaks;i++){
        if (maxnum < nredes[i]) { maxnum = nredes[i]; }
        printf("%d ",verticeslist[i]);
    }
    
    printf("\n");

    count_remove_AP(g, ti);

    Tarjan(g);

    for (i = 0; i < *breaks; i++){
        if (max < nredes[i]) { max = nredes[i]; }
    }
    printf("%d\n", max);

    return 0;
}