#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/** Projecto 2 -- ASA -- LEIC-A -- IST -- 2019/2020
 * 

Joao Branco - 93880 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINPUT 100
#define MAXINPUTSMALL 20
#define INF 10000000
#define DIREITA 1
#define BAIXO 2
#define SIZE 10
#define SOURCE 's'
#define SINK 't'
#define SOURCEINDEX 0
#define SINKINDEX -5

typedef struct Vertex {
    struct Vertex* parent;
    char id;
    int primary;
    int e_flow;
    int height;
    struct Adjacent* head;
} Vertex;

typedef struct Edge {
    Vertex* u;
    Vertex* v;
    int flow;
    int cap;
} Edge;

typedef struct Node {
    Vertex* inNode;
    struct Node* next;
}Node;

typedef struct Queue {
    Node* head;
} Queue;

typedef struct PrimaryVertex {
    char id; /*'S', 'C', 'B', '-', 't' ou 's'*/
    Vertex in;
    Vertex out;
} PrimaryVertex;

typedef struct Adjacent {
    Edge* edge;
    struct Adjacent* next;
} Adjacent;

typedef struct AdjList {
    Adjacent* head;
} AdjList;


PrimaryVertex* graph;
Node* front;
Node* rear;
Node* head;
Vertex sink, source; /*Sink and source vertex*/
Queue queue; /*Queue para Overflow Vertexes*/

int cidadaos, supermercados, ruas, avenidas, 
    nVertexes, nPrimaryVertexes, currentHeight;

int giveMatrixIndex(int rua, int avenida) {
    /*printf("Returned Index from function: %d\n", rua*avenidas - (avenidas - avenida));*/
    return rua*avenidas - (avenidas - avenida) -1;
}

int giveIndexV(int rua, int avenida, int dir) {
    if (dir == DIREITA) {
        return giveMatrixIndex(rua, avenida + 1);
    }
    /*dir == BAIXO*/
    else {
        return giveMatrixIndex(rua +1, avenida);
    }
}

/*VERTEX FUNCTIONS*/
struct Vertex newVertex(int pri, char type) { 
    struct Vertex new;
    new.primary = pri;
    new.id = type;
    new.height = 0;
    new.e_flow = 0;
    new.parent = NULL;
    new.head = NULL;
    return new;
}

PrimaryVertex * initGraph() {
    int i;
    PrimaryVertex * grafo = can_fail_malloc((nPrimaryVertexes)* sizeof(*grafo));


    /*initialize the graph*/
    for (i = 0; i < nPrimaryVertexes; i++) {
        grafo[i].id = '-';
        grafo[i].in = newVertex(i+1, 'i');
        grafo[i].out = newVertex(i+1, 'o');
    }

    source = newVertex(SOURCEINDEX, 's');
    sink = newVertex(SINKINDEX, 't');
    return grafo;
}

void freegraph() {
    free(graph);
}

void printGraph() {
    int i, j, n;
    n = 0;
    for (i = 0; i < ruas; i++) {
        for (j = 0; j < avenidas; j++) {
            printf("%c(E:%d,H:%d)\t",graph[n].id, graph[n].in.e_flow, graph[n].in.height);
            n++;
        }
        printf("\n");
    }
    printf("\n");
    printf("%c(E:%d,H:%d)\t %c(E:%d,H:%d)\n", source.id, source.e_flow, source.height,
         sink.id, sink.e_flow, sink.height);
}

void printAllVertexes() {
    int i;
    for (i = 0; i < nPrimaryVertexes; i++) {
        printf("Vertice-%d \tin:%c out:%c\n", i+1, graph[i].in.id, graph[i].out.id);
    }
}

Vertex* getParent(Vertex son) {
    return son.parent;
}

void resetParents() {
    int i;
    for (i = 0; i < nPrimaryVertexes; i++){
        graph[i].in.parent = NULL;
        graph[i].out.parent = NULL;
    }
}

void printVertex(Vertex* in) {
    printf("Vertex:%d\t%c (E:%d,H:%d)\n", in->primary, in->id, in->e_flow, in->height);
}



/*QUEUE FUNCTIONS*/
void initQueue() {
    queue.head = NULL;
    front = NULL;
    rear = NULL;
    head = NULL;
}

void enQueue(Vertex* in) {
    Node* new = can_fail_malloc(sizeof(Node));
    /*printf("ADDED Vertex: %d %c to the Queue\n", in->primary, in->id);*/
    new->inNode = in;
    if((front==NULL)&&(rear==NULL)) {
        front = new;
        rear = new;
        new->next=NULL;
    }
    else {
        rear->next=new;
        new->next=NULL;
        rear=new;
    }
}

int isEmpty() {
    if (front == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

Vertex* deQueue() {
    Node* temp = front;
    Vertex* q = temp->inNode;
    /*printf("Removed: %d %c\n", temp->inNode->primary, temp->inNode->id);*/
    if (isEmpty()) {
        return NULL;
    }
    if(front==rear) {
        free(temp);
        front=NULL;
        rear=NULL;
    }
    else{
        front = front->next;
        free(temp);
    }
    return q;
}

Vertex* getWhatsInQueue() {
    Node* temp = front;
    Vertex* q = temp->inNode;
    if (isEmpty()) {
        return NULL;
    }
    return q;
}

void displayQueue() {
    int i;
    Node* ptr = front;
    i=1;
    printf("THA QUEUE:\n");
    while(ptr != NULL) {
        printf("Node %d : Vertex:%d \t%c\n", i, ptr->inNode->primary, ptr->inNode->id);
        ptr=ptr->next;
        i++;
    }
    printf("\n");
}

void cleanQueue() {
   Node* temp;
   while (front != NULL)
    {
       temp = front;
       front = front->next;
       free(temp);
    }
    front = NULL;
    rear = NULL;
}



/*ADJLIST FUNCTIONS*/
Adjacent* newAdjacent() {
    Adjacent * new = can_fail_malloc(sizeof(*new));
    new->edge = NULL;
    new->next = NULL;
    return new;
}

void addEdgeToVList(Vertex* Uvertex, Edge* edge) {
    Adjacent* new = newAdjacent();

    new->next = Uvertex->head;
    new->edge = edge;
    Uvertex->head = new;
}

void removeSpecificEdgeFromVList(Vertex* Uvertex, Edge* edge) {
    Adjacent* temp = Uvertex->head;
    Adjacent* prev;
    /*se for o primeiro*/
    if (temp->edge == edge) {
        Uvertex->head = Uvertex->head->next;
        free(temp);
        return;
    }
    /*se estiver no meio*/
    while(temp != NULL) {
        /*se encontrou o node*/
        if (temp->edge == edge) {
            prev->next = temp->next;
            free(temp);
            return;
        }
        /*se nao encontrou*/
        prev = temp;
        temp = temp->next;
    }
}

void printEdgesList(Vertex* vertex) {
    int n = 1;
    Adjacent* temp;
    temp = vertex->head;
    printf("PVERTEX:%d %c\n", vertex->primary, vertex->id);
    while (temp != NULL ) {
        printf("Edge:%d \t U:%d %c\tV:%d %c\n", n, temp->edge->u->primary, temp->edge->u->id, 
            temp->edge->v->primary, temp->edge->v->id);
    temp = temp->next;
    }
}

void printAllEdgesList() {
    int i;
    printf("ALL EDGES:\n");
    for (i = 0; i < nPrimaryVertexes; i++) {
        printEdgesList(&graph[i].in);
        printEdgesList(&graph[i].out);
    }
    printEdgesList(&source);
    printEdgesList(&sink);
}

void freeEdgesFromSpecificVertexList(Vertex* u) {
    Adjacent* temp = u->head;
    while (u->head != NULL) {
        u->head = u->head->next;
        free(temp->edge);
        free(temp);
        temp = u->head;
    }
}

void freeAllEdgesLists() {
    int i;
    for (i = 0; i < nPrimaryVertexes; i++) {
        freeEdgesFromSpecificVertexList(&graph[i].in);
        freeEdgesFromSpecificVertexList(&graph[i].out);
    }

    /*free do sink e source*/
    freeEdgesFromSpecificVertexList(&sink);
    freeEdgesFromSpecificVertexList(&source);
}

void reverseEdge(Edge* edge) {
    Vertex* temp = edge->u;
    edge->u = edge->v;
    edge->v = temp;
}

void switchEdgesInLists(Vertex* u, Edge* edge) {
    Vertex* temp = edge->v;
    
    /*apagar antigo edge*/
    removeSpecificEdgeFromVList(u, edge);
    /*reversethe Edge*/
    reverseEdge(edge);
    /*criar novo edge*/
    addEdgeToVList(temp, edge);
}



/*EDGES FUNCTIONS*/
Edge* newEdge(Vertex* u, Vertex* v) {
    Edge * new = can_fail_malloc(sizeof(Edge));
    new->cap = 1;
    new->flow = 0;
    new->u = u;
    new->v = v;
    return new;
}

void addEdgesSupCid(PrimaryVertex* Pvertex, char id) {
    if (id == 's') {
        addEdgeToVList(&source, newEdge(&source, &Pvertex->in));
    }
    else {
        addEdgeToVList(&Pvertex->out, newEdge(&Pvertex->out, &sink));
    }
}

void addInternalEdge(PrimaryVertex* Pvertex) {
    addEdgeToVList(&Pvertex->in, newEdge(&Pvertex->in, &Pvertex->out));
}

void addALLInternalEdges() {
    int i;
    for (i = 0; i < nPrimaryVertexes; i++) {
        addInternalEdge(&graph[i]);
    }
}

void addEdge(int rua, int avenida, int dir) {
    int a, b;

    a = giveMatrixIndex(rua, avenida);
    b = giveIndexV(rua, avenida, dir);

    addEdgeToVList(&graph[a].out, newEdge(&graph[a].out, &graph[b].in));
    addEdgeToVList(&graph[b].out, newEdge(&graph[b].out, &graph[a].in));
}

void processEdges(int rua, int avenida) {
    /*UM SO VERTICE*/
    if (avenidas == 1 && ruas == 1) {
        /*Nao ha vizinhos*/
        return;
    }

    if (rua < ruas && avenida < avenidas) {
        addEdge(rua, avenida, DIREITA);
        addEdge(rua, avenida, BAIXO);
        return;
    }
    else if (rua < ruas && avenida == avenidas) {
        addEdge(rua, avenida, BAIXO);
        return;
    }
    else if (rua == ruas && avenida < avenidas) {
        addEdge(rua, avenida, DIREITA);
        return;
    }
    else {
        /*Last Vertex, sem edges*/
    }
}

void initEdges() {
    int i, j;

    addALLInternalEdges();

    for (i = 0; i < ruas; i++) {
        for (j = 0; j < avenidas; j++) {
            processEdges(i+1, j+1);
        }
    }
}





void initializeADSs() {
    nPrimaryVertexes = (ruas * avenidas);
    nVertexes = (2*nPrimaryVertexes) +2;

    initQueue();
    graph = initGraph();
    initEdges();
}

void freeADSs() {
    freeAllEdgesLists();
    freegraph();
}


/*INPUT FUNCTIONS*/
void processInput() {
    char input[MAXINPUT];
    int i = 0;
    int j = 0;

    char nAvenidas[MAXINPUTSMALL];
    char nRuas[MAXINPUTSMALL];
    char nSupermercados[MAXINPUTSMALL];
    char nCidadaos[MAXINPUTSMALL];

    /*Linha com numero de Avenidas e Ruas */
    if( fgets(input, MAXINPUT, stdin) == NULL ) {
        /*ERRO*/
    }

    /*Numero de Avenidas */
    for(; input[i] != ' '; i++) {
        nAvenidas[i] = input[i];
    }
    nAvenidas[i] = 0;

    /*Numero de Ruas */
    for(; input[i] != 0; i++) {
        nRuas[j] = input[i];
        j++;
    }
    nRuas[j] = 0;

    /*Linha com numero de Supermercados e Cidadaos */
    if( fgets(input, MAXINPUT, stdin) == NULL ) {
        /*ERRO*/
    }

    /*Numero de Supermercados*/
    for(i = 0; input[i] != ' '; i++) {
        nSupermercados[i] = input[i];
    }
    nSupermercados[i] = 0;

    /*Numero de Cidadaos*/
    for(j = 0; input[i] != 0; i++, j++) {
        nCidadaos[j] = input[i];
    }
    nCidadaos[j] = 0;

    avenidas = atoi(nAvenidas);
    ruas = atoi(nRuas);
    supermercados = atoi(nSupermercados);
    cidadaos = atoi(nCidadaos);
}

void processCandSAux(PrimaryVertex* vertex, char type) {
    if (vertex->id == 'B') {
        return;
    }
    if (vertex->id == 'C' && type == 'C') {
        return;
    }
    if (vertex->id == 'S' && type == 'S') {
        return;
    }
    if (vertex->id == 'C' && type == 'S') {
        vertex->id = 'B';
        addEdgesSupCid(vertex, 't');
        return;    
    }
    if (vertex->id == 'S' && type == 'C') {
        vertex->id = 'B';
        addEdgesSupCid(vertex, 's');
        return;    
    }
    else {
        vertex->id = type;
        if (type == 'S') {
            addEdgesSupCid(vertex, 't');
        }
        else {
            addEdgesSupCid(vertex, 's');
        }
    }
}

void processSupermercadosCidadaos() {
    int i, j, k;
    int nRua, nAvenida;
    char input[MAXINPUT];
    char rua[MAXINPUTSMALL], avenida[MAXINPUTSMALL];

    /*Supermercados*/
    for( k = 0; k < supermercados; k++) {
        if( fgets(input, MAXINPUT, stdin) == NULL ) {
        /*ERRO*/
        }

        i = 0;
        j = 0;
        /*Numero de Avenidas */
        for(; input[i] != ' '; i++) {
            avenida[i] = input[i];
        }
        avenida[i] = 0;

        /*Numero de Ruas */
        for(; input[i] != 0; i++) {
            rua[j] = input[i];
            j++;
        }
        rua[j] = 0;

        nRua = atoi(rua);
        nAvenida = atoi(avenida);

        if (nRua > ruas) {
            fputs("Rua Invalida\n", stderr);
        }
        if (nAvenida > avenidas) {
            fputs("Avenida Invalida\n", stderr);
        }

        processCandSAux(&graph[giveMatrixIndex(nRua, nAvenida)], 'S');
    }

    /*Cidadaos*/
    for( k = 0; k < cidadaos; k++) {
        if( fgets(input, MAXINPUT, stdin) == NULL ) {
        /*ERRO*/
        }

        i = 0;
        j = 0;
        /*Numero de Avenidas */
        for(; input[i] != ' '; i++) {
        avenida[i] = input[i];
        }
        avenida[i] = 0;

        /*Numero de Ruas */
        for(; input[i] != 0; i++) {
            rua[j] = input[i];
            j++;
        }
        rua[j] = 0;

        nRua = atoi(rua);
        nAvenida = atoi(avenida);

        if (nRua > ruas) {
            fputs("Rua Invalida\n", stderr);
        }
        if (nAvenida > avenidas) {
            fputs("Avenida Invalida\n", stderr);
        }

        processCandSAux(&graph[giveMatrixIndex(nRua, nAvenida)], 'C');
    }
}



/*PUSH-RELABEL*/
void preFlow() {
    Adjacent* temp = source.head;
    while (temp != NULL) {
        temp->edge->v->e_flow = 1;
        enQueue(temp->edge->v);
        addEdgeToVList(temp->edge->v, newEdge(temp->edge->v, temp->edge->u));
        temp = temp->next;
    }
    source.height = nVertexes;
    sink.height = -1;
}

int push(Vertex* u) {
    int flow;
    Adjacent* temp = u->head; /*temp is the current edge*/

    while (temp != NULL) {
        
        if(temp->edge->flow == temp->edge->cap) {
            
            temp = temp->next;
            continue;
        }
        
        /*Check if u height is higher than v*/
        if (temp->edge->u->height > temp->edge->v->height) {
            
            /*amount to be pushed*/
            flow = 1;

            /*Changes the excess flow of vertex u*/
            temp->edge->u->e_flow -= flow;

            /*Changes excess flow of vertex v*/
            temp->edge->v->e_flow += flow; 

            /*Changes flow of edge u to v*/
            /*temp->edge->flow += flow;*/

            /*dequeue u*/
            deQueue();

            /*Push vertex v to the queue*/

            if(temp->edge->v != &sink && temp->edge->v != &source) {
                enQueue(temp->edge->v);
            }
            

            /*REVERSE EDGE*/
            if (temp->edge->v != &source && temp->edge->v != &sink) {
                switchEdgesInLists(temp->edge->u, temp->edge);
            }
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void relabel(Vertex* u) {
    int minHeight = INF;
    Adjacent* temp = u->head;

    /*Find v with minimun height*/
    while (temp != NULL) {

        /*if the flow of the edge equals its capacity, then dont relabel*/
        if (temp->edge->flow == temp->edge->cap) {
            
            temp = temp->next;
            continue;
        }

        if (temp->edge->v->height < minHeight) {
            minHeight = temp->edge->v->height; 
  
            /* update height of u */
            temp->edge->u->height = minHeight + 1;
            currentHeight = minHeight + 1;
        }
        temp = temp->next;
    }
}

int getMaxFlow() {
    Vertex* vert;
    while ( !isEmpty() ) {
        vert = getWhatsInQueue(); 
        if (!push(vert)) {
            relabel(vert);
        }
        if (currentHeight > nVertexes) {
            break;
        }
    }
    return sink.e_flow;
}


int main () {
    processInput();

    initializeADSs();
    processSupermercadosCidadaos();

    preFlow();

    printf("%d\n",getMaxFlow());

    freeADSs();

    return 0;
}