#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* tp051 - Diogo Mendona 93701
*/


#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct pile {
	struct node* element;
	struct pile* next;
	struct pile* last;
} pile;

typedef struct place {
	int x;
	int y;
} place;

typedef struct connection {
	struct node* in;
	struct node* out;
	struct connection* reverse;
	int status;
} connection;

typedef struct node {
	struct crossroad* place;
	connection* parent;
	int visited;
	int connectionNumber;
	int currentConnections;
	int hasConnectedToEnd;
	connection* connections;
} node;

typedef struct crossroad {
	int x;
	int y;
	node in;
	node out;
} crossroad;


place* citizens;
int numCitizens;
place* stores;
int numStores;

int sizeX; /*Avenidas*/
int sizeY; /*Ruas*/

pile* head;

crossroad** city;

node source;
node destination;

void fifoAdd(node* element) 
{
	head->last->element = element;
	head->last->next = can_fail_malloc(sizeof(pile));
	head->last->next->element = NULL;
	head->last = head->last->next;
}

node* fifoRemove()
{
	pile* old;
	node* n;
	if (head->element == NULL)
	{
		return NULL;
	}
	old = head;
	head = head->next;
	head->last = old->last;
	n = old->element;
	free(old);
	return n;
}

int fifoEmpty() 
{
	if (head->element == NULL) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int getMaxFlux()
{
	connection* curr;
	int maxFlow = 0;
	int i;
	int bfsDone = 0;
	while (TRUE) {
		fifoAdd(&source);
		bfsDone = 0;
		while (!fifoEmpty()) {
			node* curr = fifoRemove();

			for (i = 0; i < curr->connectionNumber; i++)
			{
				if (curr->connections[i].out->visited < maxFlow && curr->connections[i].status < 1) {
					curr->connections[i].out->parent = &curr->connections[i];
					curr->connections[i].out->visited = maxFlow;
					if (curr->connections[i].out == &destination) {
						bfsDone = 1;
						break;
					}
					fifoAdd(curr->connections[i].out);
				}
			}
			if (bfsDone == 1) {
				break;
			}
		}

		while (!fifoEmpty()) {
			fifoRemove();
		}

		if (destination.parent == NULL) {
			break;
		}
		curr = destination.parent;
		while (curr != NULL) {
			curr->status += 1;
			if (curr->in != &source && curr->out != &destination)
			{
				curr->reverse->status -= 1;			
			}
			curr = curr->in->parent;
		}
		destination.parent = NULL;
		maxFlow += 1;
		if (maxFlow == numCitizens || maxFlow == numStores) {
			break;
		}
	}
	return maxFlow;
}
			
void connectInnerNodes(node* in, node* out) {
	in->connections[in->currentConnections].in = in;
	in->connections[in->currentConnections].out = out;
	in->connections[in->currentConnections].status = 0;
	in->connections[in->currentConnections].reverse = &out->connections[out->currentConnections];
	out->connections[out->currentConnections].in = out;
	out->connections[out->currentConnections].out = in;
	out->connections[out->currentConnections].status = 1;
	out->connections[out->currentConnections].reverse = &in->connections[in->currentConnections];
	in->currentConnections++;
	out->currentConnections++;
}

connection* connectOutterNodes(node* in, node* out, int value) {
	in->connections[in->currentConnections].in = in;
	in->connections[in->currentConnections].out = out;
	in->connections[in->currentConnections].status = value;
	in->currentConnections++;
	return &in->connections[in->currentConnections - 1];
}

void connectCrossroads(crossroad* a, crossroad* b)
{
	connection* aOutToBIn;
	connection* bOutToAIn;
	connection* bInToAOut;
	connection* aInToBOut;
	aOutToBIn = connectOutterNodes(&a->out, &b->in, 0);
	bInToAOut = connectOutterNodes(&b->in, &a->out, 1);
	bOutToAIn = connectOutterNodes(&b->out, &a->in, 0);
	aInToBOut = connectOutterNodes(&a->in, &b->out, 1);
	aOutToBIn->reverse = bInToAOut;
	bInToAOut->reverse = aOutToBIn;
	bOutToAIn->reverse = aInToBOut;
	aInToBOut->reverse = bOutToAIn;
}

void read() {
	char line[900];
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	fgets(line, sizeof(line) / sizeof(char), stdin);
	sscanf(line, "%d %d", &sizeX, &sizeY);
	city = can_fail_malloc(sizeof(crossroad*) * sizeX);

	while (i < sizeX)
	{
		city[i] = can_fail_malloc(sizeof(crossroad) * sizeY);
		j = 0;
		while (j < sizeY)
		{
			city[i][j].x = i;
			city[i][j].y = j;
			city[i][j].in.parent = NULL;
			city[i][j].out.parent = NULL;
			city[i][j].in.place = &city[i][j];
			city[i][j].out.place = &city[i][j];
			city[i][j].in.currentConnections = 0;
			city[i][j].out.currentConnections = 0;
			city[i][j].in.connectionNumber = 1;
			city[i][j].out.connectionNumber = 1;
			city[i][j].in.visited = -1;
			city[i][j].out.visited = -1;
			city[i][j].in.hasConnectedToEnd = 0;
			city[i][j].out.hasConnectedToEnd = 0;
			if (i > 0) {		/*Conexao a esquerda*/
				city[i][j].out.connectionNumber++;
				city[i][j].in.connectionNumber++;
			}
			if (i < sizeX - 1) {		/*Conexao a direita*/
				city[i][j].out.connectionNumber++;
				city[i][j].in.connectionNumber++;
			}
			if (j > 0) {		/*Conexao acima*/
				city[i][j].out.connectionNumber++;
				city[i][j].in.connectionNumber++;
			}
			if (j < sizeY - 1) {		/*Conexao abaixo*/
				city[i][j].out.connectionNumber++;
				city[i][j].in.connectionNumber++;
			}
			city[i][j].out.connections = can_fail_malloc(sizeof(connection) * (city[i][j].out.connectionNumber + 1));
			city[i][j].in.connections = can_fail_malloc(sizeof(connection) * city[i][j].in.connectionNumber);
			connectInnerNodes(&city[i][j].in, &city[i][j].out);
			if (i > 0)
				connectCrossroads(&city[i][j], &city[i - 1][j]);
			if (j > 0)
				connectCrossroads(&city[i][j], &city[i][j - 1]);
			j++;
		}
		i++;
	}

	fgets(line, sizeof(line) / sizeof(char), stdin);
	sscanf(line, "%d %d", &numStores, &numCitizens);
	citizens = can_fail_malloc(sizeof(place) * numCitizens);
	stores = can_fail_malloc(sizeof(place) * numStores);
	i = 0;
	while (i < numStores) {
		fgets(line, sizeof(line) / sizeof(char), stdin);
		sscanf(line, "%d %d", &x, &y);
		stores[i].x = x - 1;
		stores[i].y = y - 1;
		i++;
	}
	i = 0;
	while (i < numCitizens) {
		fgets(line, sizeof(line) / sizeof(char), stdin);
		sscanf(line, "%d %d", &x, &y);
		citizens[i].x = x - 1;
		citizens[i].y = y - 1;
		i++;
	}
}

void setSource() {
	source.connectionNumber = numCitizens;
	source.connections = can_fail_malloc(source.connectionNumber * sizeof(connection));
	source.parent = NULL;
	source.place = can_fail_malloc(sizeof(crossroad));
	source.place->x = -2;
	source.place->y = -2;
	source.visited = -1;
	for (source.currentConnections = 0; source.currentConnections < source.connectionNumber; source.currentConnections++) {
		source.connections[source.currentConnections].in = &source;
		source.connections[source.currentConnections].out = &city[citizens[source.currentConnections].x][citizens[source.currentConnections].y].in;
		source.connections[source.currentConnections].reverse = NULL;
		source.connections[source.currentConnections].status = 0;
	}
}

void setDestination() {
	node* curr;
	int i;
	destination.connectionNumber = 0;
	destination.connections = NULL;
	destination.parent = NULL;
	destination.place = can_fail_malloc(sizeof(crossroad));
	destination.place->x = -1;
	destination.place->y = -1;
	destination.visited = -1;
	for (i = 0; i < numStores; i++) {
		curr = &city[stores[i].x][stores[i].y].out;
		if (curr->hasConnectedToEnd == 1) {
			continue;
		}
		curr->connections[curr->currentConnections].in = curr;
		curr->connections[curr->currentConnections].out = &destination;
		curr->connections[curr->currentConnections].reverse = NULL;
		curr->connections[curr->currentConnections].status = 0;
		curr->connectionNumber++;
		curr->currentConnections++;
		curr->hasConnectedToEnd = 1;
	}
}

void initiatePile() {
	head = can_fail_malloc(sizeof(pile));
	head->last = head;
	head->element = NULL;
	head->next = NULL;
}

int main() {
	int value;
	read();
	setSource();
	setDestination();
	initiatePile();
	value = getMaxFlux();
	printf("%d\n", value);
	exit(0);
}