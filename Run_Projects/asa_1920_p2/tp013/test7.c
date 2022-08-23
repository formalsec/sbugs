/*+-----------------------------------------------------------+
  |  Second Project  Analisys and Sythesys of Algorthims      |
  |-----------------------------------------------------------+
  |Programers : David Miranda (93697) & Joao Salgueiro (93725)|
  +-----------------------------------------------------------+*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BigBoss ruas*avenidas*2
typedef struct node
{
	int id;
	int num_connections;
	int* connections;
}node;


int ruas, avenidas, supermercados, pessoas, max_possible, queue_size = 0, size = -1, front = -1, rear = -1;
int * queue,* parent, *visited;
node ** adjGraph;

int convertID(int x, int y, int side)/* Left = 1, right = 0*/
{
	return ((y - 1)*avenidas + x -1) * 2 + side;
}

node* createEmptyNode(int id)
{
	node *brotha;
	node * some = malloc(sizeof(node));
	some -> id = id;
	some -> num_connections = 0;
	brotha = some;
	return brotha;
}
void addEdge(int source, int sink)
{
	adjGraph[source] -> connections[adjGraph[source] -> num_connections ++] = sink;
}
void createNode(int i)
{
	adjGraph[i] -> connections = malloc(7*sizeof(int));
	if(i == 0)
	{
		addEdge(0,1);
		return;
	}
	else if(i % 2 != 0)
	{
		/*end node IMPARES*/
		if(i == avenidas * 2 - 1) /* primeiro da ultima avenida*/
		{
			addEdge(i,i-3);
			addEdge(i, 2 * i);
			return;
		}
		if( (i + 1) == avenidas * ruas * 2 ) /* ultimo no da ultima avenida*/
		{
			addEdge(i,i -(avenidas * 2 + 1));
			addEdge(i, i - 3);
			return ;
		}
		if((i + 1) % (avenidas * 2) == 0 ) /* nos na ultima avenida meio*/
		{
			addEdge(i,i - (avenidas * 2 + 1));
			addEdge(i,i - 3);
			addEdge(i,i + (avenidas * 2 - 1));
			return ;

		}
		if(i == 1)/*no no inicio da primeira avenida( nao vai entrar em conflito se for a ultima fila)*/
		{
			addEdge(i,i + 1);
			addEdge(i,i + (avenidas * 2 - 1));
			return;
		}
		if(i == avenidas*2*(ruas - 1) + 1)/*no no fim da primeira avenida*/
		{
			addEdge(i,i - (avenidas * 2 + 1));
			addEdge(i,i + 1);
			return;
		}
		if((i - 1) % (avenidas * 2) == 0)/*nos na primeira avenida meio*/
		{
			addEdge(i,i - (avenidas * 2 + 1));
			addEdge(i,i + 1);
			addEdge(i,i + (avenidas * 2 - 1));
			return;
		}
		if(i > 0 && i < (avenidas * 2 - 1))/*nos na primeira rua meio*/
		{
			addEdge(i,i + 1);
			addEdge(i,i - 3);
			addEdge(i,i + (avenidas * 2- 1));
			return ;
		}
		if(i > (avenidas*2*(ruas - 1) + 1) && i < (avenidas * ruas* 2 - 1))/*nos na ultima rua meio*/
		{
			addEdge(i,i - (avenidas * 2 + 1));
			addEdge(i,i + 1);
			addEdge(i,i - 3);
			return;
		}
		/* nos impares no meio do grafo*/
		addEdge(i,i - (avenidas * 2 + 1));
		addEdge(i,i + 1);
		addEdge(i,i - 3);
		addEdge(i,i + (avenidas * 2 - 1));
		return;

	}
	else
	{
		addEdge(i,i+1);
		return;
	}
}
void createInitializeParent()
{
	parent[ruas * avenidas * 2] = -1;
	parent[ruas * avenidas * 2 + 1] = -1;
}
void addBigSuperToSupermarket(int id)/* Impedir q o Supersupermarket volte para tras*/
{
	addEdge(id,avenidas * ruas * 2 + 1);/*Adicionar ao supermercado*/
}
void addPersonToBigPerson(int id)/*Adcionar ah big pessoa*/
{
	addEdge(avenidas * ruas * 2,id);
}
int min(int a, int b)
{
	return a > b ? b : a;
}
node* createBigNode(int id, int type)
{
	node *some, *brotha;
	some = malloc(sizeof(node));
	some -> num_connections = 0;
	if(type == 0)
	{
		some-> connections = malloc(pessoas *sizeof(int));
		brotha = some;
		return some;
	}
	some -> connections = malloc(supermercados *sizeof(int));
	brotha = some;
	return brotha;
}
void initializeAdjGraph()
{
	int i;
	adjGraph = malloc((avenidas * ruas * 2 + 2)*sizeof(node*));
	parent = malloc((avenidas * ruas * 2 + 2)*sizeof(int));
	for(i = 0; i < avenidas * ruas * 2; i++)
	{
		adjGraph[i] = createEmptyNode(i);
		createNode(i);
		parent[i] = -1;
	}
	adjGraph[avenidas * ruas * 2] = createBigNode(i,0);
	adjGraph[avenidas * ruas * 2 + 1] = createBigNode(i,1);
}
int inArray(int id, int size, int *array)
{
	int i;
	for(i = 0; i < size;i++)
	{
		if(array[i] == id)
			return 1;
	}
	return 0;
}
void parseArgs()
{
	int i, x, y, id;
	int *array,size = 0;
	scanf("%d %d", &avenidas, &ruas);
	scanf("%d %d", &supermercados,&pessoas);
	array = calloc(supermercados,sizeof(int));
	initializeAdjGraph();
	createInitializeParent();
	for(i = 0; i < supermercados; i++)
	{
		scanf("%d %d", &x,&y);
		id = convertID(x,y,1);/*End node*/
		if(inArray(id,size,array) == 0){
			addBigSuperToSupermarket(id);
			array[size++] = id;
		}

	}
	free(array);
	array = calloc(pessoas,sizeof(int));
	size = 0;
	for(i = 0; i < pessoas; i++)
	{
		scanf("%d %d", &x,&y);
		id = convertID(x,y,0);/*Start node*/
		if(inArray(id,size,array) == 0){
			addPersonToBigPerson(id);
			array[size++] = id;
		}
	}
	max_possible = min(pessoas, supermercados);
	free(array);
}


void insertQueue(int id)
{
	if(size < BigBoss + 2)
	{
		if(size < 0)
		{
			queue[0] = id;
			front = rear = 0;
			size = 1;
		}
		else if(rear == BigBoss + 1)
		{
			queue[0] = id;
			rear = 0;
			size++;
		}
		else
		{ 
			queue[rear + 1] = id;
			rear++;
			size++;
		}
	}
}
int popQueue()
{
	int id = queue[front];
	size--;
	front++;
	return id;
}

int BFS()
{
	int vertex_id,adjVertex_id, num_con,i;
	for(i = 0; i < ruas*avenidas*2 + 2; i++)
		visited[i] = 0;
	visited[ruas * avenidas * 2] = 1;/*Big person*/
	insertQueue(ruas * avenidas * 2);
	parent[ruas * avenidas * 2] = -1;

	while(size != 0)
	{
		vertex_id = popQueue();
		num_con = adjGraph[vertex_id] -> num_connections;
		for(i = 0; i < num_con ;i++)
		{
			adjVertex_id = adjGraph[vertex_id] -> connections[i];
			if(visited[adjVertex_id] == 0)
			{
				parent[adjVertex_id] = vertex_id;
				visited[adjVertex_id] = 1;
				if(adjVertex_id == BigBoss + 1){
					return 1;
				}
				insertQueue(adjVertex_id);
			}
			
		}
	}
	return 0;/* encontrou supe super*/
}

void deleteAdjGraph(int u, int v)
{
	int i,e,num_con;
	num_con = adjGraph[u] -> num_connections;
	for(i = 0; i < num_con; i++)
	{
		if(adjGraph[u] -> connections[i] == v)
		{
			for(e = i; e < num_con - 1; e++)
			{
				adjGraph[u] -> connections[e] = adjGraph[u] -> connections[e+1];
			}
			adjGraph[u] -> num_connections --;
			return;
		}
	}
}
int edmondsKARPA()
{
	int flo,max_flow = 0,v,u;
	while(1)
	{
		if(max_flow == max_possible)
			return max_flow;
		flo = BFS();
		if(flo == 0)
		{
			return max_flow;
		}
		for(v = ruas * avenidas * 2 + 1; v != ruas * avenidas * 2; v=parent[v]) 
        { 
            u = parent[v];
            if(v !=ruas * avenidas * 2 + 1 && u !=ruas * avenidas * 2){
           		deleteAdjGraph(u,v);
            }
           	addEdge(v,u);
        }
        for(u = 0; u < ruas*avenidas*2 + 2; u++)
        	queue[u] = 0;
        size = -1;
        rear = -1;
        front = -1;
        max_flow++;
	}
	return max_flow;
}

int main(int argc, char const *argv[])
{	
	int flo = 0;
	parseArgs();
	queue = malloc((BigBoss+ 2)*sizeof(int));
	visited = calloc(ruas * avenidas * 2 + 2,sizeof(int));
	flo = edmondsKARPA();
	free(queue);
	free(parent);
	printf("%d\n", flo);

	return 0;
}