#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertex {
    int el, visited, augmented, parent, visitedBFS, height, excess, onQueue;
    int tipo; /*tipo = { 0:Hiper, 1:Fornecedor, 2:Posto, 3:Source}*/
    struct connection* parentEdge;
    struct list* edgesSelf, *adj;
} *vertexLink;

typedef struct connection {
    int vI, vF, flow, cap, inverted;
} *connectionLink;

typedef struct list {
    connectionLink connection;
	struct list *prev, *next;
} *ListLink;

typedef struct queueItem {
    int value;
    struct queueItem *prev, *next, *tail;
} *QueueLink;

/*Heads*/
int parseArgs(vertexLink* fListEl, int* edges, int* capForn, int* nPost, int* nFornecedor);

void insertConnection(ListLink* listAdj, connectionLink connection);
void invertConnections(vertexLink listEl, int size, int contrary);

connectionLink* BFS(vertexLink listEl, int size, int source, int target, int markFound, int* startPath);

void relabel(vertexLink listEl, int vertex);
void pushFlow(vertexLink listEl, connectionLink edge, int vI, int vF, int rightWay);
void discharge(vertexLink listEl, int vertex);
int relabelToFront(vertexLink listEl, int source, int target, int size, int nForn);

int maximumFlow(vertexLink listEl, int size);
int findToImprove(vertexLink listEl, int size, int edges, int nPostos, int nFornecedor);

void startQueue(QueueLink* queue, QueueLink* lastEmpty);
void pushQueue(QueueLink* queue, int value, QueueLink* lastEmpty);
int popQueue(QueueLink* queue, QueueLink* lastEmpty);
int isEmptyQueue(QueueLink* queue);
void freeQueue(QueueLink* queue);

void freeVertex(vertexLink listEl, int size);
/**/

int main(int argc, char **argv){
    int size = 0, flow=0, edges = 0, capForn=0, nPostos=0, nForn=0;
    int source = 1, target = 0;
	vertexLink listEl;                         /*Estrutura com informacao dos fornecedores e postos de abastecimentos e Hiper*/
	size = parseArgs(&listEl, &edges, &capForn, &nPostos, &nForn); 
    flow = relabelToFront(listEl, source, target, size, nForn); /*Esta shit continua a ocupar muita memoria-> melhorar memoria*/
    if (flow < capForn || BFS(listEl, size, source, target, 0, NULL) == NULL) findToImprove(listEl, size, edges, nPostos, nForn);
    freeVertex(listEl, size);
    return 0;
}

int parseArgs(vertexLink* fListEl, int* edges, int* capForn, int* nPost, int* nFornecedor){
    int nForn, nPostos, nLigacoes, size;

    scanf("%d %d %d", &nForn, &nPostos, &nLigacoes);
    size = nForn + 2*nPostos + 1 + 1; /*+1 -> Hiper(target), +1 -> Source*/

    vertexLink listEl = (vertexLink) can_fail_malloc(sizeof(struct vertex) * size);

    /*Source*/
    listEl[0].el = 0; listEl[0].tipo = 3; listEl[0].visited = 0; listEl[0].augmented = 0; 
    listEl[0].height = size; listEl[0].excess = 0; listEl[0].onQueue = 0;
    listEl[0].edgesSelf = NULL; 
    listEl[0].adj = NULL; 

    /*Hiper (Target)*/
    listEl[1].el = 1; listEl[1].tipo = 0; listEl[1].visited = 0; listEl[1].augmented = 0; 
    listEl[1].height = 0; listEl[1].excess = 0; listEl[1].onQueue = 0;
    listEl[1].edgesSelf = NULL; 
    listEl[1].adj = NULL; 

    int currentI = 2, i=currentI;

    /*Introduz capacidade dos fornecedores*/
    for (; i<(nForn+currentI); i++){
        int cap;
        scanf("%d", &cap);
        *capForn += cap;
        listEl[i].el = i;
        listEl[i].tipo = 1;
        listEl[i].visited = 0;
        listEl[i].augmented = 0;
        listEl[i].excess = cap;
        listEl[i].height = 0;
        listEl[i].edgesSelf = NULL;
        listEl[i].adj = NULL;
        listEl[i].onQueue = 0;
        listEl[i].edgesSelf = NULL; 
        listEl[i].adj = NULL; 

        /*Liga a source aos fornecedores*/
        connectionLink connection = (connectionLink) can_fail_malloc(sizeof(struct connection));
        connection->vF = i;
        connection->vI = 0;
        connection->cap = cap;
        /*connection->residual = 0;*/
        connection->flow = cap;
        connection->inverted = 0;
        insertConnection(&(listEl[i].adj), connection);
        insertConnection(&(listEl[i].edgesSelf), connection);
    }

    currentI = i;
    listEl[0].excess = -(*capForn);

    /*Introduz capacidade dos postos de abastecimento*/
    for (; i<(+nPostos+currentI); i++){
        int cap;
        scanf("%d", &cap);
        listEl[i].el = i;
        listEl[i].tipo = 2;
        listEl[i].visited = 0;
        listEl[i].augmented = 0;
        listEl[i].height = 0;
        listEl[i].excess = 0;
        listEl[i].edgesSelf = NULL;
        listEl[i].adj = NULL;
        listEl[i].onQueue = 0;
        listEl[i].edgesSelf = NULL; 
        listEl[i].adj = NULL; 

        listEl[i+nPostos].el = i+nPostos;
        listEl[i+nPostos].tipo = 2;
        listEl[i+nPostos].visited = 0;
        listEl[i+nPostos].augmented = 0;
        listEl[i+nPostos].excess = 0;
        listEl[i+nPostos].height = 0;
        listEl[i+nPostos].edgesSelf = NULL;
        listEl[i+nPostos].adj = NULL;
        listEl[i+nPostos].onQueue = 0;
        listEl[i+nPostos].edgesSelf = NULL; 
        listEl[i+nPostos].adj = NULL; 

        /*Liga posto de abastecimento a posto linha (simboliza a sua capacidade)*/
        connectionLink connection = (connectionLink) can_fail_malloc(sizeof(struct connection));
        connection->vF = i+nPostos;
        connection->vI = i;
        connection->cap = cap;
        /*connection->residual = cap;*/
        connection->flow = 0;
        connection->inverted = 0;
        insertConnection(&(listEl[i].adj), connection);
        insertConnection(&(listEl[i+nPostos].edgesSelf), connection);
    }

    /*Insere conexões*/
    for (i=0; i<nLigacoes; i++){
        connectionLink connection = (connectionLink) can_fail_malloc(sizeof(struct connection));
        int o, d, c;
        scanf("%d %d %d", &o, &d, &c);
        connection->vF = d;
        connection->vI = o;
        connection->cap = c;
        /*connection->residual = c;*/
        connection->flow = 0;
        connection->inverted = 0;
        
        if ( o <= (nForn+1)) insertConnection(&(listEl[o].adj), connection);
        else {
            connection->vI = o+nPostos;
            insertConnection(&(listEl[o+nPostos].adj), connection);
        }
        insertConnection(&(listEl[d].edgesSelf),connection);
    }

    *nFornecedor = nForn;
    *nPost = nPostos;
    *edges = nLigacoes;
    *fListEl = listEl;
    return size;
}

void insertConnection(ListLink* listAdj, connectionLink connection){
    ListLink new = (ListLink) can_fail_malloc(sizeof(struct list));
    ListLink head = *listAdj;
    new->prev = NULL;
    new->connection = connection;

    /*Insere ordenado*/
    if (head == NULL){
        *listAdj = new;
        new->next = NULL;
    }
    else {
        ListLink aux, last;
        for (aux = head; aux != NULL; aux = aux->next){
            if (aux->next == NULL) last = aux;
            if (aux->connection->vF > new->connection->vF){
                new->next = aux;
                new->prev = aux->prev;
                if (aux->prev != NULL) aux->prev->next = new;
                aux->prev = new;
                if (aux == head) *listAdj = new;
                break;
            }
        }
        if (aux == NULL){
            new->next = NULL;
            new->prev = last;
            last->next = new;
        }
    }

}

void invertConnections(vertexLink listEl, int size, int contrary){
    int i;
    for (i=0; i<size; i++){
        ListLink adj = listEl[i].adj;
        while (adj != NULL){
            ListLink aux = adj->next;
            int el = adj->connection->vF;
            if (adj->connection->inverted == 0){
                connectionLink connection = (connectionLink) can_fail_malloc(sizeof(struct connection));
                connection->vI = el;
                connection->vF = i;
                connection->cap = adj->connection->cap;
                /*connection->residual = adj->connection->residual;*/
                connection->flow = adj->connection->flow;
                connection->inverted = 1;
                insertConnection(&(listEl[el].adj), connection);

                /*adj->connection->residual = adj->connection->flow;*/
                adj->connection->flow = adj->connection->cap - adj->connection->flow;
                adj->connection->inverted = 1;
            }
            adj = aux;
        }
    }
}

connectionLink* BFS(vertexLink listEl, int size, int source, int target, int markFound, int* startPath){
    int i, currentV=0, maxDepth=0;

    /*Inicializa a queue*/
    for (i=0; i<size; i++){
        listEl[i].visitedBFS = 0;
    }

    /*Insere a source*/
    QueueLink queue, lastEmpty;
    startQueue(&queue, &lastEmpty);
    pushQueue(&queue, source, &lastEmpty);
    listEl[source].visitedBFS = 1;

    i=0;
    
    while (!isEmptyQueue(&queue)){
        currentV = popQueue(&queue, &lastEmpty);

        ListLink adj = listEl[currentV].adj;

        while (adj != NULL){
            int u = adj->connection->vF, res = adj->connection->cap - adj->connection->flow;

            /*Verifica se consegue passar*/
            if (listEl[u].visitedBFS == 0 && res != 0){
                maxDepth++;
                if (markFound) listEl[u].visited = 1;
                pushQueue(&queue, u, &lastEmpty);
                listEl[u].visitedBFS = 1;
                listEl[u].parent = currentV;
                listEl[u].parentEdge = adj->connection;

                /*Se chegamos ao target fazemos o caminho de volta*/
                if (u == target && !markFound){
                    connectionLink* path = (connectionLink*) can_fail_malloc(sizeof(connectionLink) * (maxDepth + 1));
                    while (u != source){
                        path[maxDepth--] = listEl[u].parentEdge;
                        u = listEl[u].parent;
                    }
                    if (startPath != NULL) *startPath = maxDepth+1;
                    freeQueue(&queue);
                    return path;
                }
            }
            adj = adj->next;
        }
    }
    /*Nao chegamos ao target*/
    freeQueue(&queue);
    return NULL;
}

/*Obter fluxo maximo*/

void relabel(vertexLink listEl, int vertex){
    int minH = -1;
    ListLink adj = listEl[vertex].edgesSelf;
    while (adj != NULL){
        int h = listEl[adj->connection->vI].height;
        if  (adj->connection->flow > 0 && (h < minH || minH == -1)) minH = h;
        adj = adj->next;
    }

    adj = listEl[vertex].adj;
    while (adj != NULL){
        int h = listEl[adj->connection->vF].height, res = adj->connection->cap - adj->connection->flow;
        if  (res > 0 && (h < minH || minH == -1)) minH = h;
        adj = adj->next;
    }
    listEl[vertex].height = minH + 1;
    /*printf("relabel -> h[%d]=%d\n", vertex, listEl[vertex].height);*/
}

void pushFlow(vertexLink listEl, connectionLink edge, int vI, int vF, int rightWay){
    int eU = listEl[vI].excess, res = (rightWay) ? (edge->cap - edge->flow) : edge->flow;
    int minFlow = (eU < res) ? eU : res;
    if (rightWay){
        edge->flow += minFlow;
    }
    else {
        edge->flow -= minFlow;
    }
    listEl[vI].excess -= minFlow;
    listEl[vF].excess += minFlow;
    /*printf("push(%d,%d), e[%d]=%d, e[%d]=%d\n", vI, vF, vI, listEl[vI].excess, vF, listEl[vF].excess);*/
}

int relabelToFront(vertexLink listEl, int source, int target, int size, int nForn) {
    QueueLink queue, lastEmpty;
    startQueue(&queue, &lastEmpty);
    int i;

    for (i=2; i<(2+nForn); i++){
        pushQueue(&queue, i, &lastEmpty);
    }

    /**/
    int currentV = popQueue(&queue, &lastEmpty);

    while (currentV != -1){
        /*printf("u=%d\n", currentV);*/

        if (listEl[currentV].excess > 0){

            /*Discharge*/
            int vertex = currentV;
            vertexLink currentVertex;
    
            while(listEl[vertex].excess > 0) {

                ListLink adj = listEl[vertex].edgesSelf;
                while(adj != NULL) {
                    currentVertex = &listEl[adj->connection->vI];

                    /*Se tem altura menor damos push*/
                    if (currentVertex->height < listEl[vertex].height && adj->connection->flow > 0) {
                        pushFlow(listEl, adj->connection, vertex, currentVertex->el, 0);
                        if (currentVertex->el != 0 && currentVertex->el != 1 && !listEl[currentVertex->el].onQueue) {
                            pushQueue(&queue, currentVertex->el, &lastEmpty);
                            listEl[currentVertex->el].onQueue = 1;
                        }
                        break;
                    }
                    adj = adj->next;
                }

                ListLink adj2 = listEl[vertex].adj;
                while (adj2 != NULL) {
                    currentVertex = &listEl[adj2->connection->vF];
                    int res = adj2->connection->cap - adj2->connection->flow;

                    /*Se tem altura menor damos push*/
                    if (currentVertex->height < listEl[vertex].height && res > 0) {
                        pushFlow(listEl, adj2->connection, vertex, currentVertex->el, 1);
                        if (currentVertex->el != 0 && currentVertex->el != 1 && !listEl[currentVertex->el].onQueue){
                            pushQueue(&queue, currentVertex->el, &lastEmpty);
                            listEl[currentVertex->el].onQueue = 1;
                        } 
                        break;
                    }
                    adj2 = adj2->next;
                }

                if (adj == NULL && adj2 == NULL) relabel(listEl, vertex);        
            }
            /**/
        } 

        listEl[currentV].onQueue = 0;

        /*printf("\n");*/
        currentV = popQueue(&queue, &lastEmpty);
    }

    printf("%d\n", listEl[1].excess); /*Fluxo maximo*/
    freeQueue(&queue);
    return listEl[1].excess;
}

/*Obter corte minimo*/

int findToImprove(vertexLink listEl, int size, int edges, int nPostos, int nFornecedor) {
    int* vertixesToAugment = (int*) can_fail_malloc(sizeof(int) * 1);
    int** edgesToAugment = (int**) can_fail_malloc(sizeof(int*) * 1);
    int vertixesPointer = 0, edgesPointer = 0, i;

    invertConnections(listEl, size, 1);
    
    listEl[1].visited = 1;
    BFS(listEl, size, 1, 0, 1, NULL);

    for (i=1; i<size; i++){
        if (!listEl[i].visited){
            ListLink adj = listEl[i].adj;
            while (adj != NULL){
                int target = adj->connection->vF;
                if (listEl[adj->connection->vF].visited == 1){
                    if ( (i + nPostos) == target && target > (nPostos+nFornecedor+1)){
                        vertixesToAugment[vertixesPointer++] = i;
                        listEl[i].augmented = 1;
                        vertixesToAugment = (int*) can_fail_realloc(vertixesToAugment, (vertixesPointer+1)*sizeof(int));
                    }
                    else if (listEl[i].augmented == 0) {
                        int source = i;
                        if (i > (nPostos+nFornecedor+1)) source -= nPostos;
                        int* edges = (int*) can_fail_malloc(sizeof(int)*2);
                        edges[0] = source; edges[1] = target;
                        edgesToAugment[edgesPointer++] = edges;
                        edgesToAugment = (int**) can_fail_realloc(edgesToAugment, (edgesPointer+1)*sizeof(int*));
                    }
                }
                adj = adj->next;
            }
        }
    }

    for (i=0; i < vertixesPointer; i++) {
        if (i == (vertixesPointer - 1)) printf("%d\n", vertixesToAugment[i]);
        else printf("%d ", vertixesToAugment[i]);
    }

    if(vertixesPointer==0) printf("\n");
    
    for (i=0; i < edgesPointer; i++) {
        if ((i == (edgesPointer - 1)) && listEl[edgesToAugment[i][0]].augmented == 0) printf("%d %d\n", edgesToAugment[i][0], edgesToAugment[i][1]);
        else if (listEl[edgesToAugment[i][0]].augmented == 0) printf("%d %d\n", edgesToAugment[i][0], edgesToAugment[i][1]);
        free(edgesToAugment[i]);
    }
    free(vertixesToAugment);
    free(edgesToAugment);
    return 0;
}

/*Funcoes sobre Queue*/

void startQueue(QueueLink* queue, QueueLink* lastEmpty){
    *queue = (QueueLink) can_fail_malloc(sizeof(struct queueItem));
    *lastEmpty = (QueueLink) can_fail_malloc(sizeof(struct queueItem));
    (*queue)->next = *lastEmpty;
    (*queue)->prev = NULL;
    (*queue)->value = -1;
    (*queue)->tail = *queue;

    (*lastEmpty)->next = NULL;
    (*lastEmpty)->prev = *queue;
    (*lastEmpty)->value = -1;
    (*lastEmpty)->tail = *queue;
}

void pushQueue(QueueLink* queue, int value, QueueLink* lastEmpty){
    /*printf("push do: %d\n", value);*/
    if ((*queue)->value == -1){
        (*queue)->value = value;
        (*queue)->tail = (*queue);
    }
    else if ((*queue)->tail->next == *lastEmpty){
        QueueLink newLastEmpty = (QueueLink) can_fail_malloc(sizeof(struct queueItem));
        newLastEmpty->next = NULL;
        newLastEmpty->value = -1;
        newLastEmpty->prev = *lastEmpty;
        newLastEmpty->tail = *lastEmpty;

        (*lastEmpty)->value = value;
        (*lastEmpty)->next = newLastEmpty;
        (*queue)->tail->next = *lastEmpty;
        (*queue)->tail->tail = *lastEmpty;
        (*queue)->tail = *lastEmpty;
        *lastEmpty = newLastEmpty;
    }
    else {
        QueueLink aux = (*queue)->tail->next;
        aux->value = value;
        (*queue)->tail->tail = aux;
        (*queue)->tail = aux;
    }
/*
    QueueLink aux2 = *queue;
    while (aux2 != NULL){
        printf("%d, ", aux2->value);
        aux2 = aux2->next;
    }
    printf("\n");*/
}

int popQueue(QueueLink* queue, QueueLink* lastEmpty){
    QueueLink adj = *queue;
    int value = (*queue)->value;
    /*printf("pop do: %d\n", value);*/

    if ((*queue)->next->value == -1){
        (*queue)->value = -1;
    }
    else {
        (*queue) = adj->next;
        (*queue)->tail = adj->tail;
        (*lastEmpty)->next = adj;
        adj->value = -1;
        adj->next = NULL;
        adj->prev = *lastEmpty;
        *lastEmpty = adj;
    }

    /*QueueLink aux2 = *queue;
    while (aux2 != NULL){
        printf("%d, ", aux2->value);
        aux2 = aux2->next;
    }
    printf("\n");*/

    return value;
}

int isEmptyQueue(QueueLink* queue){
    return ((*queue)->value == -1)?1:0;
}

void freeQueue(QueueLink* queue){
    QueueLink current = *queue;
    QueueLink next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void freeVertex(vertexLink listEl, int size) {
    int i;
    ListLink list, aux;

    for (i=0; i<size; i++) {
        /*printf("%d->%d\n", listEl[i].edgesSelf->connection->vI->el, listEl[i].edgesSelf->connection->vF->el);*/

        list = listEl[i].adj;
        while (list != NULL) {
            aux = list->next;
            if (list->connection != NULL) {
                /*printf("%d->%d\n", list->connection->vI->el, list->connection->vF->el);*/
                free(list->connection);
            }
            free(list);
            list = aux;
        }
        /*free(listEl[i].adj);*/
        list = listEl[i].edgesSelf;
        while (list != NULL) {
            aux = list->next;
            free(list);
            list = aux;
        }
        /*free(listEl[i].edgesSelf);*/
    }
    free(listEl);
}