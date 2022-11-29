#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Guilherme Jardim 92471
Vasco Cabral 92568
ASA - 2º Projeto*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGET 0
#define SUPERMARKET 1
#define HOME 2
#define NOTHING 3
#define SOURCE 5
#define TWIN 6

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

#define UNREACHABLE -1
#define REACHABLE 0

#define BACKWARDS 0
#define FORWARDS 1

#define IN 0
#define OUT 1

#define TRUE 1
#define FALSE 0

#define EXISTS 1
#define NIL 0

typedef struct corner {  /* Estrutura que define as esquinas */
    int type;                   /* Definimos se e um supermercado, uma casa, uma esquina sem nada, a target ou a source */
    int *corners;     /* Lista de adjacencias, ordenamos por NORTH, EAST, SOUTH e WEST, null significa nao existente */
    int *flow;
    int visited;                /* Guarda se o vertice ja foi visitado */
    int arrivedFrom;            /* Guarda a partir de que direção e que o vertice foi descoberto, podera ser removido */
    int h;                      /* Altura e excesso do vertice para o algoritmo push relabel */
    int e;
} Corner;

typedef struct coord {
    int x;
    int y;
} Coord;

typedef struct vertex
{
    int index;
    int realIndex;
    struct vertex * next;
} OverflowingVertex;


int V, avenues, streets;
int nMarkets;
OverflowingVertex* head;

int order[2][6] = {{TWIN, LEFT, UP, RIGHT, DOWN, SOURCE}, {TARGET, LEFT, UP, RIGHT, DOWN, TWIN}};
int way[2][6] = {{FORWARDS, BACKWARDS, BACKWARDS, BACKWARDS, BACKWARDS, BACKWARDS}, {FORWARDS, FORWARDS, FORWARDS, FORWARDS, FORWARDS, BACKWARDS}};

void newOverflowingList() {
    head = NULL;
}

void freeVertex(OverflowingVertex* vertex) {
    OverflowingVertex* destroy;

    destroy = head;
    head = head->next;
    free(destroy);
}

void freeOverflowingList() {

    while(head != NULL) {
        freeVertex(head);
    }
}

void addVertex(int index) {
    OverflowingVertex* temp;
    OverflowingVertex* newVertex = can_fail_malloc(sizeof(OverflowingVertex));
    newVertex->index = index;
    index = index % (V - 1);
    newVertex->realIndex = index;

    if((head == NULL) || (head->realIndex > index)) {
        newVertex->next = head;
        head = newVertex;
    } else {
        temp = head;

        while((temp->next != NULL) && (temp->next->realIndex < index)) {
            temp = temp->next;
        }

        newVertex->next = temp->next;
        temp->next = newVertex;
    }
}

int popVertex() {
    if (head == NULL)
        return -1;
    int index = head->index;
    freeVertex(head);
    return index;
}

void printList() {
    OverflowingVertex* printing = head;
    while(printing != NULL) {
        printf("Index: %d\n", printing->index);
        printing = printing->next;
    }
}

int neighbour(int index, int direction, int way) {
    int neighbour;
    neighbour = index % (V - 1);
    switch (direction) {
        case UP:
            neighbour -= avenues;
            break;
        case LEFT:
            neighbour -= 1;
            break;
        case DOWN: 
            neighbour += avenues;
            break;
        case RIGHT: 
            neighbour += 1;
            break;
        case SOURCE:
            return 0;
            break;
        case TWIN:
            return ((index + V - 1) % (V * 2 - 2));
            break;
        default:
            return V - 1;
            break;
    }

    if (way == BACKWARDS)
        neighbour += V - 1;

    return neighbour;
}

int oppositeDirection(int direction) {
    if (direction == TWIN) return TWIN;
    direction--;
    return ((direction + 2) % 4) + 1;
}

int cornerID(int avenue, int street) { /* Vamos guardar as esquinas num array unidimensional, e este metodo transforma coordenadas bidimensionais numa coord apenas */
    street--;
    return street * avenues + avenue;
}

Coord* cornerCoord(int index, int avenues) {
    Coord *coord = can_fail_malloc(sizeof(Coord));
    index--;
    coord->x = (index % avenues) + 1;
    coord->y = (index / avenues) + 1;
    return coord;
}

int firstOverflowingVertex(Corner* map) {
    return popVertex();
}

int isHigher(Corner * map, int index, int neighbourI) {
    return map[index].h > map[neighbourI].h;
}

int canGoThere(Corner * map, int candidate, int direction, int way, int place) {
    
    if (way == FORWARDS) {
        return ((map[candidate].flow[direction] == 0) && (map[place].visited != UNREACHABLE));
    } else {
        return (map[candidate].flow[direction] == -1);
    }
}

void relabel(Corner * map, int index, int lowestNeighbour) {
    map[index].h = map[lowestNeighbour].h + 1;
}

void push(Corner * map, int index) {
    int direction; 
    int picker;
    int i, j;
    int neighbourI;
    j = 0;

    if (index < V - 1) { 
        picker = IN;
    } else {
        picker = OUT;
    }
    int chosenDirection = -1;
    int lowestNeighbour = -1;
    for (i = 0; i < 6; i++) {
        direction = order[picker][i];
        if (map[index].corners[direction] == NIL)
            continue;

        neighbourI = neighbour(index, direction, way[picker][i]);

        if (canGoThere(map, index, direction, way[picker][i], neighbourI)) {
            if (lowestNeighbour == -1 || map[neighbourI].h < lowestNeighbour) {
                lowestNeighbour = map[neighbourI].h;
                j = i;
            }
        }
    }
    
    chosenDirection = order[picker][j];
    neighbourI = neighbour(index, chosenDirection, way[picker][j]);

    if (!(isHigher(map, index, neighbourI))) {
        relabel(map, index, neighbourI);
    }

    if ((chosenDirection == SOURCE) || (chosenDirection == TARGET)) {
        map[index].e--;
        map[neighbourI].e++;

        map[index].flow[chosenDirection]++;
        
    } else {
        map[index].e--;
        map[neighbourI].e++;
        addVertex(neighbourI);

        map[index].flow[chosenDirection]++;
        map[neighbourI].flow[oppositeDirection(chosenDirection)]--;

        if(chosenDirection != TWIN) {
            map[neighbour(index, TWIN, 0)].flow[chosenDirection]++;
            map[neighbour(neighbourI, TWIN, 0)].flow[oppositeDirection(chosenDirection)]--;
        }
    }
}

int getMaxFlow(Corner * map) {
    int u;
    while(((u = firstOverflowingVertex(map)) > 0) && (nMarkets > map[V - 1].e)) {
        push(map, u);
    }
    return map[V - 1].e;
}

int main() {
    int i; 
    scanf("%d %d", &avenues, &streets);
    V = avenues * streets + 2;

    Corner * map = can_fail_malloc(sizeof(Corner) * (V + (avenues * streets)));
    newOverflowingList();

    map[0].type = SOURCE;
    map[0].h = V;

    map[V - 1].type = TARGET;
    map[V - 1].h = 0;
    map[V - 1].e = 0;
    
    for(i = 1; i < V - 1; i++) {
        int twin = neighbour(i, TWIN, FORWARDS);
        map[i].type = NOTHING;
        map[twin].type = NOTHING;
        map[i].corners = can_fail_malloc(sizeof(int) * 7);
        map[twin].corners = can_fail_malloc(sizeof(int) * 7);
        map[i].flow = can_fail_malloc(sizeof(int) * 7);
        map[twin].flow = can_fail_malloc(sizeof(int) * 7);

        Coord* coord = cornerCoord(i, avenues);
        int x = coord->x;
        int y = coord->y;
        free(coord);

        map[i].corners[TWIN] = EXISTS;
        map[i].flow[TWIN] = 0;

        map[twin].corners[TWIN] = EXISTS;
        map[twin].flow[TWIN] = 0;
        
        if(x != 1) {
            map[i].corners[LEFT] = EXISTS;
            map[i].flow[LEFT] = 0;

            map[twin].corners[LEFT] = EXISTS;
            map[twin].flow[LEFT] = 0; 
        } else {
            map[i].corners[LEFT] = NIL;
            map[twin].corners[LEFT] = NIL;
        }

        if(y != 1) {
            map[i].corners[UP] = EXISTS;
            map[i].flow[UP] = 0;

            map[twin].corners[UP] = EXISTS;
            map[twin].flow[UP] = 0;
        } else {
            map[i].corners[UP] = NIL;
            map[twin].corners[UP] = NIL;
        }

        if (x != avenues) {
            map[i].corners[RIGHT] = EXISTS;
            map[i].flow[RIGHT] = 0;

            map[twin].corners[RIGHT] = EXISTS;
            map[twin].flow[RIGHT] = 0;
        } else {
            map[i].corners[RIGHT] = NIL;
            map[twin].corners[RIGHT] = NIL;
        }

        if (y != streets) {
            map[i].corners[DOWN] = EXISTS;
            map[i].flow[DOWN] = 0;

            map[twin].corners[DOWN] = EXISTS;
            map[twin].flow[DOWN] = 0;
        } else {
            map[i].corners[DOWN] = NIL;
            map[twin].corners[DOWN] = NIL;
        }

        map[i].corners[SOURCE] = NIL;
        map[i].corners[TARGET] = NIL;
        map[i].flow[SOURCE] = 0;
        map[i].flow[TARGET] = 0;

        map[twin].corners[SOURCE] = NIL;
        map[twin].corners[TARGET] = NIL;
        map[twin].flow[SOURCE] = 0;
        map[twin].flow[TARGET] = 0;


        map[i].h = 0;
        map[i].e = 0;
        map[twin].h = 0;
        map[twin].e = 0;
    }
    
    int nHouses;
    scanf("%d %d", &nMarkets, &nHouses);
    map[0].e = -nHouses;
    int direction;

    for(i = 0; i < nMarkets; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        int index = cornerID(x, y);
        int twin = neighbour(index, TWIN, FORWARDS);

        map[index].type = SUPERMARKET;

        for (direction = 1; direction < 5; direction++) {
            map[twin].corners[direction] = NIL;
        }
        map[twin].corners[TARGET] = EXISTS;
    }

    for (i = 0; i < nHouses; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        int index = cornerID(x, y);
        
        if(map[index].type == SUPERMARKET && map[index].visited == REACHABLE) {
            map[index].visited = UNREACHABLE;
            map[V - 1].e ++;
        } else if ((map[index].type != SUPERMARKET) && (map[index].visited == REACHABLE)) {

            if (map[index].e == 0) {
                map[index].corners[SOURCE] = EXISTS;
                for (direction = 1; direction < 5; direction++) {
                    map[index].corners[direction] = NIL;
                }
                map[index].flow[SOURCE] = -1;
                map[index].visited = UNREACHABLE;
                map[index].e = 1;
                addVertex(index);
            }

        }
    }

    int maxFlow = getMaxFlow(map);
    printf("%d\n", maxFlow);

    for (i = 0; i < V * 2 - 2; i++) {
        free(map[i].corners);
        free(map[i].flow);
    }
    freeOverflowingList();
    return 0; 
}
