#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int x, y;
    struct node* next;
    struct node* previous;
    struct node* nearest;
    float bestDistance;
    struct node* nextInColumn;
    int populated;
    int store;
    int usedInPath;
    int connecting;
} Node;

Node** map;

int M = 0, N = 0;
int S = 0, C = 0;

void addNodeToMap(Node* node){
    int x = node->x;
    Node* currentNode;
    if(map[x] == NULL){
        map[x] = node;
        return;
    }else{
        currentNode = map[x];
        while(currentNode->nextInColumn != NULL) currentNode = currentNode->nextInColumn;

        currentNode->nextInColumn = node;
    }
}

Node* newNode(int posX, int posY){
    Node* new = (Node*)can_fail_malloc(sizeof(Node));

    new->x = posX;
    new->y = posY;
    new->next = NULL;
    new ->previous = NULL;
    new->nearest = NULL;
    new->bestDistance = -1;

    new->nextInColumn = NULL;

    new->populated = 0;
    new->store = 0;

    new->usedInPath = 0;
    new->connecting = 0;

    return new;
}

int nodeUsed(Node* node){
    return node->next != NULL || node->previous != NULL;
    /*return ((node->next != NULL || node->previous != NULL) && !node->store) || node->populated;*/
}

Node* getNode(int x, int y){
    if(x < 0 || x >= M || y < 0 || y >= N)
        return NULL;
    Node* currentNode = map[x];

    while(currentNode != NULL && currentNode->y != y) currentNode = currentNode->nextInColumn;

    if(currentNode == NULL){
        Node* new = newNode(x, y);
        addNodeToMap(new);
        currentNode = new;
    }

    return currentNode;
}

/*
QUEUE FUNCTIONS--------------------------------------------------------------------------------
*/

/* FIXME: dar rework na queue para comecar a contar da tail (melhora os pushs apenas, piora pops) */
typedef struct queueElement{
    Node* node;
    struct queueElement* next;
} QueueElement;

void printQueue(QueueElement* head){
    QueueElement* current = head->next;
    printf("\nQUEUE-----------------------\n");
    while(current != NULL){
        printf("(%d,%d)\n", current->node->x, current->node->y);
        current = current->next;
    }
    printf("END QUEUE-----------------------\n\n");
}

QueueElement* newQueueElement(Node* node){
    QueueElement* newEl = can_fail_malloc(sizeof(QueueElement));
    newEl->node = node;
    newEl->next = NULL;
    return newEl;
}

void push(Node* node, QueueElement* head){
    QueueElement* newEl = newQueueElement(node);

    QueueElement* temp = head;
    while(temp->next != NULL) temp = temp->next;

    temp->next = newEl;    

}

QueueElement* popLast(QueueElement* head){
    QueueElement* temp = head;
    QueueElement* prev = NULL;
    while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
    }

    prev->next = NULL;
    return temp;
}

QueueElement* popFirst(QueueElement* head){
    QueueElement* first = head->next;
    if(first != NULL)
        head->next = first->next;
    return first;
}

QueueElement* startQueue(){
    QueueElement* head = newQueueElement(NULL);

    return head;
}

int queueEmtpy(QueueElement* head){
    return head->next == NULL;
}

/*
-------------------------------------------------------------------------------------------
*/

float distanceBetweenNodes(Node* a, Node* b){
    float dX = a->x - b->x;
    float dY = a->y - b->y;

    return dX + dY; /* FIXME: distancia de improviso */
}

void sortClosest(int* closest, int size){
    int lowest = 0;
    int temp = 0;
    int i = 0, j = 0;
    for( i = 0; i < size; i++){
        lowest = i;
        for( j = i; j < size; j++){
            if(closest[j] < closest[lowest])
                lowest = j;
        }

        if(lowest != i){
            temp = closest[i];
            closest[i] = closest[lowest];
            closest[lowest] = temp;
        }
    }
}

void sortConnecting(Node** connecting, int size){
    Node* temp;
    int lowest = 0, l = 0;;
    int i = 0, j = 0;

    for(i = 0; i < size; i++){
        lowest = connecting[i]->connecting;
        l = i;
        for(j = i; j < size; j++){
            if(connecting[j]->connecting < lowest){
                lowest = connecting[j]->connecting;
                l = j;
            }
        }

        if(l != i){
            temp = connecting[i];
            connecting[i] = connecting[l];
            connecting[l] = temp;
        }

    }

}

void pushNeighbour(Node* start, Node* origin, int d_x, int d_y, QueueElement* head){
    Node* neighbour = getNode(origin->x + d_x, origin->y + d_y);
    if(neighbour == NULL || nodeUsed(neighbour) || (neighbour->store && start->store) || (neighbour->populated && start->populated)) return;
    neighbour->previous = origin;
    push(neighbour, head);
}

void visitNode(Node* start, Node* node, QueueElement* head){
    pushNeighbour(start, node, 1, 0, head);
    pushNeighbour(start, node, 0, 1, head);
    pushNeighbour(start, node, -1, 0, head);
    pushNeighbour(start, node, 0, -1, head);
}

int connectNode(Node* start){
    int result = 0;
    QueueElement* head = startQueue();
    QueueElement* trash = startQueue();

    push(start, head);

    QueueElement* current = NULL;
    while(!queueEmtpy(head)){
        current = popFirst(head);

        if((((current->node)->store && start->populated) || (current->node->populated && start->store)) && (current->node)->usedInPath != 1){
            Node* node = current->node;
            Node* prev = node->previous;
            
            /* create path to store */
            while(prev != NULL && prev->next == NULL){
                node->usedInPath = 1;
                prev->next = node;
                node = prev;
                prev = node->previous;
            }
            result = 1;

            start->usedInPath = 1;

            free(current);
            break;
        }

        push(current->node, trash);
        visitNode(start, current->node, head);
        free(current);
    }

    /* empty queue */
    while(!queueEmtpy(head)){
        current = popFirst(head);
        (current->node)->previous = NULL;
        free(current);
    }

    /* reset checked nodes */
    while(!queueEmtpy(trash)){
        current = popFirst(trash);
        if(current->node->usedInPath != 1) (current->node)->previous = NULL;
        free(current);
    }

    free(head);
    free(trash);
    return result;
}

int countConnections(Node* start){
    QueueElement* head = startQueue();
    QueueElement* trash = startQueue();

    push(start, head);

    QueueElement* current = NULL;
    int found = 0;
    while(!queueEmtpy(head)){
        current = popFirst(head);

        if((current->node->store && start->populated) || (current->node->populated && start->store)){
            start->nearest = current->node;
            found++;
        }else{
            visitNode(start, current->node, head);
        }

        push(current->node, trash);
        free(current);
    }

    if(found == 1){
        Node* node = start->nearest;
        Node* prev = node->previous;
        
        /* create path to store */
        while(prev != NULL && prev->next == NULL){
            node->usedInPath = 1;
            prev->next = node;
            node = prev;
            prev = node->previous;
        }

        start->usedInPath = 1;
    }

    /* empty queue */
    while(!queueEmtpy(head)){
        current = popFirst(head);
        (current->node)->previous = NULL;
        free(current);
    }

    /* reset checked nodes */
    while(!queueEmtpy(trash)){
        current = popFirst(trash);
        if(current->node->usedInPath != 1) (current->node)->previous = NULL;
        free(current);
    }

    free(head);
    free(trash);

    start->connecting = found;

    return found;
}

int main(){

    int x = 0, y = 0;

    int i = 0;

    Node** citizens;
    Node** supermarkets;

    int* closest; /* list of citizen indexes in order of proximity to any supermarket */

    /* gather initial data */
    if(scanf("%d %d", &M, &N) <= 0) return -1;
    if(scanf("%d %d", &S, &C) <= 0) return -1;

    /* start map */
    map = can_fail_malloc(M*sizeof(Node*));
    for(i = 0; i < M; i++) map[i] = NULL;

    /* register supermarkets */
    supermarkets = can_fail_malloc(S*sizeof(Node*));

    for(i = 0; i < S; i++){
        if(scanf("%d %d", &x, &y) <= 0) return -1;
        supermarkets[i] = newNode(x-1, y-1);
        supermarkets[i]->store = 1;
        addNodeToMap(supermarkets[i]);
    }

    /* register citizens */
    citizens = can_fail_malloc(C*sizeof(Node*));
    closest = can_fail_malloc(sizeof(int)*C);

    for(i = 0; i < C; i++){
        if(scanf("%d %d", &x, &y) <= 0) return -1;
        citizens[i] = newNode(x-1, y-1);
        citizens[i]->populated = 1;
        addNodeToMap(citizens[i]);
        closest[i] = i;
    }

    /* search nearest supermarket for each citizen */
    /*int c = 0;
    int s = 0;
    for(c = 0; c < C; c++){
        Node* citizen = citizens[c];
        Node* store;
        float distance = 0;
        for(s = 0; s < S; s++){
            store = supermarkets[s];
            distance = distanceBetweenNodes(citizen, store);
            if(citizen->bestDistance == -1 || citizen->bestDistance < distance){
                citizen->nearest = store;
                citizen->bestDistance = distance;
            }
        }
    }

    sortClosest(closest, C);*/

    int changed = 1;
    int k = 0;
    int* countSup = can_fail_malloc(S * sizeof(int));
    int* countCit = can_fail_malloc(C * sizeof(int));
    while(changed != 0){
        changed = 0;
        /* count connections */
        for(i = 0; i < S; i++){
            if(supermarkets[i]->usedInPath) continue;
            countSup[i] = countConnections(supermarkets[i]);

            if(countSup[i] == 1)
                changed = 1;
        }
        
        for(i = 0; i < C; i++){
            if(citizens[i]->usedInPath) continue;
            countCit[i] = countConnections(citizens[i]);

            if(countCit[i] == 1)
                changed = 1;
        }      
    }

    sortConnecting(citizens, C);

    for(i = 0; i < C; i++){
        if(!citizens[i]->usedInPath){
            k = connectNode(citizens[i]);
            sortConnecting(citizens, C);
        }
    }
    k++;

    /*Node* currentNode;
    int total = 0;

    for(i = 0; i < C; i++){
        currentNode = citizens[closest[i]];
        total += connectNode(currentNode);
    }

    printf("%d\n", total);*/

    int numberOfConnections = 0;

    for(i = 0; i < S; i++){
        if(supermarkets[i]->usedInPath == 1){
            numberOfConnections++;
        }
    }

    printf("%d\n", numberOfConnections);


    /* freeing remaining memory */
    for(i = 0; i < M; i++){
        Node* current = map[i];
        Node* next = NULL;
        while(current->nextInColumn != NULL){
            next = current->nextInColumn;
            free(current);
            current = next;
        }

    }

    free(countSup);
    free(countCit);

    free(map);
    free(supermarkets);
    free(citizens);
    free(closest);

    return 0;
}