#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/*-------------------------------------------------------------------------------------------------------------------
Constants
-------------------------------------------------------------------------------------------------------------------*/

#define NEIGHBORS_AMOUNT 6
#define NULL_ID -1

/*-------------------------------------------------------------------------------------------------------------------
Structs
-------------------------------------------------------------------------------------------------------------------*/

/*Represents a node in the max flow problem. Holds the IDs of the neighbor nodes. Each node (except the sink) may only have at most 6 neighbors*/
typedef struct {
    int neighbors[NEIGHBORS_AMOUNT];
    int visitedIteration;
} Node;

typedef struct {
    int* neighbors;
} Source;

/*List of adjacencies*/
typedef struct {
    Node* nodes;
    int size;
} AdjacenciesList;

/*-------------------------------------------------------------------------------------------------------------------
Enums
-------------------------------------------------------------------------------------------------------------------*/
enum Direction {SINK = 0, BROTHER, UP, DOWN, LEFT, RIGHT};

/*-------------------------------------------------------------------------------------------------------------------
Global variables
-------------------------------------------------------------------------------------------------------------------*/
AdjacenciesList list;
Source source;
int amountCrossings;
int inverted;

/*Input related*/
int amountAvenues;
int amountStreets;
int amountMarkets;
int amountPeople;

/*ID related*/
int sinkID;

/*-------------------------------------------------------------------------------------------------------------------
Auxiliary functions
-------------------------------------------------------------------------------------------------------------------*/

/*Returns the ID corresponding to the given ID's brother*/
int getBrotherID(int id) {
    return id + amountCrossings;
}

/*Returns the ID of the node that represents the crossing in the given avenue and street*/
int getNodeID(int avenue, int street) {
    return avenue * amountStreets + street;
}

/*Adjecencies list related*/

/*Inserts the given adjacencyID into the nodeID's adjacency list
The direction is the adjacency's relative position to the node*/
void insertAdjacency(int nodeID, int adjacencyID, int direction) {
    list.nodes[nodeID].neighbors[direction] = adjacencyID;
}

/*Debug*/
void printList() {
    int i, j;

    for(i = 0; i < list.size; i++) {
        printf("Node number %d's neighbors are: ", i);

        for(j = 0; j < NEIGHBORS_AMOUNT; j++) {
            if(list.nodes[i].neighbors[j] != NULL_ID) {
                printf("%d, ", list.nodes[i].neighbors[j]);
            }
        }

        printf("\n");
    }

    printf("The source is connected to: ");

    for(i = 0; i < amountPeople; i++) {
        printf("%d, ", source.neighbors[i]);
    }

    printf("\n");
}

/*-------------------------------------------------------------------------------------------------------------------
Main
-------------------------------------------------------------------------------------------------------------------*/
int main() {
    int i, j, aux, iteration = 0, index, brotherIndex, avenue, street, flow = 0, pathI, reverseDirection, flowUpperBound, direction;
    int *currentPathIDs, *neighborVisitDirection;
    int directions[] = {UP, DOWN, LEFT, RIGHT};

    /*----------------------
    Reading the input
    ------------------------*/


    /*Reading the first 2 input lines*/
    scanf("%d %d", &amountAvenues, &amountStreets);
    scanf("%d %d", &amountMarkets, &amountPeople);

    amountCrossings = amountAvenues * amountStreets;

    /*If the amount of people is greater than the amount of markets, then the problem will be reversed: the markets will be the people and vice-versa.
    This greatly optimizes this algorithm*/
    if(amountPeople > amountMarkets) {
        inverted = 1;
    }
    else {
        inverted = 0;
    }

    /*Setting an upper bound for the max flow*/
    flowUpperBound = inverted ? amountPeople : amountMarkets;

    /*Every node will have a brother node so that the node may have a "capacity". That explains the "* 2". the "+ 1" is due to the sink*/
    list.size = amountCrossings * 2 + 1; 

    sinkID = list.size - 1;

    /*Allocating space for all the nodes*/
    list.nodes = (Node*) can_fail_malloc(sizeof(Node) * list.size);

    /*Initializing the adjacencies list*/
    for(i = 0; i < list.size; i++) {
        for(j = 0; j < NEIGHBORS_AMOUNT; j++) {
            insertAdjacency(i, NULL_ID, j);
        }
        list.nodes[i].visitedIteration = -1;
    }

    /*Setting the neighbors of the nodes that represent crossings*/
    for(i = 0; i < amountAvenues; i++) {
        for(j = 0; j < amountStreets; j++) {
            index = getNodeID(i, j); /*Index of the node in the list*/
            brotherIndex = getBrotherID(index);

            /*Setting the node's brother as its first adjencency*/
            insertAdjacency(index, brotherIndex, BROTHER);

            if(i != 0) {
                /*Adding an upper neighbor*/
                insertAdjacency(brotherIndex, index - amountStreets, UP);
            }
            if(j != 0) {
                /*Adding a left neighbor*/
                insertAdjacency(brotherIndex, index - 1, LEFT);
            }
            if(i != amountAvenues - 1) {
                /*Adding a downwards neighbor*/
                insertAdjacency(brotherIndex, index + amountStreets, DOWN);
            }
            if(j != amountStreets - 1) {
                /*Adding a right neighbor*/
                insertAdjacency(brotherIndex, index + 1, RIGHT);
            }
        }
    }  

    /*Allocating memory for the source*/
    source.neighbors = (int*) can_fail_malloc(sizeof(int) * (inverted ? amountMarkets : amountPeople));

    /*Making every node, that represents a crossing that has at least 1 market, point to the sink*/
    for(i = 0; i < amountMarkets; i++) {
        scanf("%d %d", &avenue, &street);

        avenue--;
        street--;

        index = getNodeID(avenue, street);
        
        if(inverted) {
            source.neighbors[i] = index;
        }
        else {
            /*The brother is the one adding the sink to its adjacencies list*/
            brotherIndex = getBrotherID(index);

            if(list.nodes[brotherIndex].neighbors[SINK] != NULL_ID) {
                /*If the brother node is already pointing at the sink, then the maximum flow may not be as large as previously thought*/
                flowUpperBound--;
            }
            else {
                list.nodes[brotherIndex].neighbors[SINK] = sinkID;
            }
        }
    }

    /*Initializing the source*/
    for(i = 0; i < amountPeople; i++) {
        scanf("%d %d", &avenue, &street);

        avenue--;
        street--;

        index = getNodeID(avenue, street);

        if(!inverted) {
            source.neighbors[i] = index;
        }
        else {
            /*The brother is the one adding the sink to its adjacencies list*/
            brotherIndex = getBrotherID(index);

            if(list.nodes[brotherIndex].neighbors[SINK] != NULL_ID) {
                /*If the brother node is already pointing at the sink, then the maximum flow may not be as large as previously thought*/
                flowUpperBound--;
            }
            else {
                list.nodes[brotherIndex].neighbors[SINK] = sinkID;
            }
        }
    }


    /*----------------------
    Applying the algorithm - Ford Fulkerson
    ------------------------*/


    currentPathIDs = (int*) can_fail_malloc(sizeof(int) * list.size);
    neighborVisitDirection = (int*) can_fail_malloc(sizeof(int) * list.size);

    for(i = 0; i < (inverted ? amountMarkets : amountPeople); i++) {
        index = source.neighbors[i];
        pathI = 0;

        /*If the flow can't go any higher due to the amount and placement of markets, then break*/
        if(flow >= flowUpperBound) {
            break;
        }

        while(1) {
            currentPathIDs[pathI] = index;
            list.nodes[index].visitedIteration = iteration;
            
            aux = NULL_ID;

            /*Selecting an available neighbor to visit*/
            for(j = 0; j < NEIGHBORS_AMOUNT; j++) {
                aux = list.nodes[index].neighbors[j];

                if(j < 2) {
                    /*Always check if there's a connection to the sink or the brother first, for optimization purposes*/
                    direction = j;
                }
                else {
                    /*Alternating between several directions so that it doesn't always go, for example, up*/
                    direction = directions[j - 2];
                }

                aux = list.nodes[index].neighbors[direction];

                if(aux != NULL_ID && list.nodes[aux].visitedIteration != iteration) {
                    /*If aux isn't null and if the neighbor hasn't been visited yet, proceed*/
                    neighborVisitDirection[pathI] = direction;
                    break;
                }
                else {
                    aux = NULL_ID;
                }
            }

            if(aux == NULL_ID) {
                /*A dead end has been reached*/
                pathI--;

                if(pathI < 0) {
                    /*Reaching this point means there is no path from the source to the sink*/
                    break;
                }
                else {
                    /*Go back to try another path*/
                    index = currentPathIDs[pathI];
                    continue;
                }
            }

            if(aux == sinkID) {
                /*The sink has been reached*/
                flow++;

                /*Changing the orders in the directions array. This will promote different path lookups*/
                direction = directions[0];
                directions[0] = directions[1];
                directions[1] = directions[2];
                directions[2] = directions[3];
                directions[3] = direction;

                /*Reversing all the "pipes"'s ways*/
                for(j = 0; j < pathI; j++) {

                    switch(neighborVisitDirection[j]) {
                        case UP:
                            reverseDirection = DOWN;
                            break;
                        case DOWN:
                            reverseDirection = UP;
                            break;
                        case LEFT:
                            reverseDirection = RIGHT;
                            break;
                        case RIGHT:
                            reverseDirection = LEFT;
                            break;
                        case BROTHER:
                            reverseDirection = BROTHER;
                            break;
                        case SINK:
                            reverseDirection = SINK;
                            break;
                        default:
                            /*This shouldn't be reached*/
                            reverseDirection = 0;
                            break;
                    }

                    /*The current node will no longer point to the neighbor it visited*/
                    list.nodes[currentPathIDs[j]].neighbors[neighborVisitDirection[j]] = NULL_ID;

                    /*The visited node will now point to the node that visited him*/
                    list.nodes[currentPathIDs[j + 1]].neighbors[reverseDirection] = currentPathIDs[j];

                }
                /*The current node will no longer point to the sink*/
                list.nodes[currentPathIDs[pathI]].neighbors[SINK] = NULL_ID;

                break;
            }
            else {
                /*Going to visit the node of ID aux*/
                index = aux;
                pathI++;
            }
        }

        iteration++;
    }


    /*----------------------
    Printing the result
    ------------------------*/


    printf("%d\n", flow);

    /*----------------------
    Debugging
    ------------------------*/

    /*Printing stuff*/
    


    /*----------------------
    Concluding program
    ------------------------*/


    /*Freeing all allocated memory*/
    free(list.nodes);
    free(source.neighbors);
    free(currentPathIDs);
    free(neighborVisitDirection);

    return 0;
}