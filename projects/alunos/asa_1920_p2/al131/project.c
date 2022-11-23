#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct {
	int x;
	int y;
}Point;


int **createMatrix(int linhas, int colunas) {
	int i;
	int **mat;
	mat = (int **)can_fail_malloc(sizeof(int*) * linhas);
	for (i=0;i<linhas;i++)
		mat[i] = (int *)can_fail_malloc(sizeof(int) * colunas);
	return mat;
}

void copyMat(int **matA, int **matB, int linhas, int colunas) {
 	int j;  
	for(j=0; j<colunas; j++) {
        memcpy(matB[j], matA[j], colunas * sizeof(int));
   }
}

int *cria_lista(int n) {
	int *v;
	v = (int *) can_fail_malloc(sizeof(int) * n);
	return v;
}

void apaga_matriz(int linhas, int **M) {
	int i;
	for(i=0;i<linhas;i++) free(M[i]);
	free(M);
}

Point *createListPoint(int n) {
	Point *v;
	v = (Point *) can_fail_malloc (n * sizeof(Point) );
	return v;
}

void readList(Point *v,int n) {
	int i;
	for (i=0;i<n;i++) scanf("%d %d",&v[i].x,&v[i].y);
}

/* A structure to represent a queue */
struct Queue { 
    int front, rear, size; 
    unsigned capacity; 
    int* array; 
}; 
  
/* function to create a queue of given capacity.  
 It initializes size of queue as 0 */
struct Queue* createQueue(unsigned capacity) { 
    struct Queue* queue = (struct Queue*) can_fail_malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1; 
    queue->array = (int*) can_fail_malloc(queue->capacity * sizeof(int)); 
    return queue; 
} 
  
/*Queue is full when size becomes equal to the capacity  */
int isFull(struct Queue* queue) {  
	return (queue->size == queue->capacity);  
} 
  
/* Queue is empty when size is 0 */
int isEmpty(struct Queue* queue) {  
	return (queue->size == 0); 
} 
  
/* Function to add an item to the queue */
void enqueue(struct Queue* queue, int item) { 
    if (isFull(queue)) return; 
    queue->rear = (queue->rear + 1)%queue->capacity; 
    queue->array[queue->rear] = item; 
    queue->size = queue->size + 1; 
} 
  
/* Function to remove an item from queue */
int dequeue(struct Queue* queue) { 
    if (isEmpty(queue)) return -9999; 
    int item = queue->array[queue->front]; 
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
} 
  
/* Function to get front of queue */
int front(struct Queue* queue) { 
    if (isEmpty(queue)) return -9999; 
    return queue->array[queue->front]; 
} 
  
/* Function to get rear of queue */
int rear(struct Queue* queue) { 
    if (isEmpty(queue)) return -9999; 
    return queue->array[queue->rear]; 
} 
  
/*
void printMaze(int **mat, int M, int N) {
	int i, j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			printf("%2d", mat[i][j]);
		}
		printf("\n");
	}
}*/


void printLista(int *mat, int M) {
	int i;
	for (i = 0; i < M; i++) {
		printf("%3d", mat[i]);
	}
	printf("\n");
}

/* 	Returns true if there is a path from source 's' to sink 't' in 
	residual graph. Also fills parent[] to store the path */
int bfs(int **rGraph, int s, int t, int *parent) { 
	int V = t + 1;
	int *visited = cria_lista(V); 
	memset(visited, 0, V * sizeof(int));

	struct Queue* q = createQueue(V + 1);  
	enqueue(q, s); 
	visited[s] = 1; 
	parent[s] = -1; 

	while (!isEmpty(q)) 
	{ 
		int u =dequeue(q);
		int v;
		for (v = 0; v < V; v++) { 
			if (visited[v] == 0 && rGraph[u][v] > 0) { 
				enqueue(q, v); 
				parent[v] = u; 
				visited[v] = 1; 
			} 
		} 
	} 

	return (visited[t] == 1); 
} 

/* Returns the maximum flow from s to t in the given graph */
int fordFulkerson(int **graph, int s, int t) { 
	int u, v; 
	int V = t + 1;

	int **rGraph = createMatrix(V, V); 
	copyMat(graph, rGraph, V, V);

	int *parent = cria_lista(V); 

	int max_flow = 0;

	while (bfs(rGraph, s, t, parent)) { 
		int path_flow = 9999; 
		for (v = t; v != s; v = parent[v]) { 
			u = parent[v]; 
			path_flow = ((path_flow < rGraph[u][v]) ? path_flow : rGraph[u][v]); 
		} 

		for (v = t; v != s; v = parent[v]) { 
			u = parent[v]; 
			rGraph[u][v] -= path_flow; 
			/*rGraph[v][u] += path_flow; */
		}
		max_flow += path_flow; 
	} 
	return max_flow; 
} 


bool inMaze(Point pt,int M,int N) {
	return (pt.x >= 0 && pt.y >= 0 && pt.x < M && pt.y < N);
}

void fillMaze(int **mat, int M, int N, int fillValue) {
	int i, j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			mat[i][j] = fillValue;
		}
	}
}

void fillMazeCS(int **mat, int M, int N, Point *v, int size, int fillValue) {
	int i;
	for (i = 0; i < size; i++) {
		mat[v[i].x-1][v[i].y-1] = fillValue;
	}
}

int getVertice(int i, int j, int N){
	return (i * N + j);
}



int main() {
	int nC, M;
	int nS, N;
	int i, j, k;

	scanf("%d %d", &M ,&N);
	scanf("%d %d", &nS, &nC);

	Point *listCitizens = createListPoint(nC);
	Point *listSupermarkets  = createListPoint(nS);
	int **maze = createMatrix(M, N);

	readList(listSupermarkets,nS);
	readList(listCitizens,nC);

	fillMaze(maze, M, N, 1);
	fillMazeCS(maze, M, N, listSupermarkets, nS, 3);
	fillMazeCS(maze, M, N, listCitizens, nC, 2);

	int dx[4] = {-1, 0, 0, 1};
	int dy[4] = {0, -1, 1, 0};

	int max = M * N + 1;
	int **graph = createMatrix(max+1,max+1);
	fillMaze(graph, max + 1, max + 1, 0);

	Point pt, ptx;
	int no, nox;
	for (i = 0; i < nC; i++){
		no = getVertice(listCitizens[i].x-1, listCitizens[i].y-1, N) + 1; 
		graph[0][no] = 1;
	}

	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++){ 
			pt.x = i;
			pt.y = j;
			no = getVertice(pt.x, pt.y, N) + 1;
			for (k = 0; k < 4; k++) {
				ptx.x = dx[k] + pt.x;
				ptx.y = dy[k] + pt.y;
				nox = getVertice(ptx.x, ptx.y, N) + 1;
				if (maze[i][j] != 3) {
					if (inMaze(ptx, M, N)) {
						if (maze[ptx.x][ptx.y] != 2){
							graph[no][nox] = 1;
						}
					}
				}
				if (inMaze(ptx, M, N)) {
					if ((maze[i][j] == 1 || maze[i][j] == 3) && maze[ptx.x][ptx.y] == 1){
						graph[nox][no] = 1;
					} 
				}
			}
		}
	}

	for (i = 0; i < nS; i++){
		nox = getVertice(listSupermarkets[i].x-1, listSupermarkets[i].y-1, N) + 1; 
		graph[nox][max] = 1;
	}

	apaga_matriz(M, maze);
	free(listSupermarkets);
	free(listCitizens);
	
	int maxFlow = fordFulkerson(graph, 0, max);

	printf("%d\n",maxFlow);
    return 0;
}

