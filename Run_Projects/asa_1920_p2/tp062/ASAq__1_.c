#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	int n;
	struct node *next;
}*Node;

typedef struct vertex{
	int pos;
	int color;
	int pi;
	Node first, tail;
}*Vertex;

typedef struct queue{
    int data;
    struct queue *next;
}*Queue;

Queue rear, front;
unsigned int size;
int *res;

int convertCoor(int x, int y, int width){
	return x + (y * width);
}

int isEmpty()
{
    return (size <= 0);
}

void enqueue(int data){
    Queue newNode = NULL;
    newNode = (Queue)malloc(sizeof(struct queue));
    newNode->data = data;
    newNode->next = NULL;
    if (rear)
    {
        rear->next = newNode;
    }
    rear = newNode;
    if ( !front )
    {
        front = rear;
    }
    size++;
}

int dequeue()
{
    Queue toDequque = NULL;
    int data;
    if (isEmpty()){
		return -1;
	}
    toDequque = front;
    data = toDequque->data;
    front = front->next;
    size--;
    free(toDequque);
    return data;
}

int BFS(Vertex* graph, int N, int v, int sink){
	/* -1 -> black
		0 -> gray
		1 -> white
	*/
	int i;
	int popped;
	Node aux;
	int foundPath = 0;
	for(i=0; i<N; i++){
		if(graph[i]->color==2){}
		else{
			graph[i]->color = 1;
			graph[i]->pi = -1;
		}
	}
	graph[i]->color = 1;
	graph[i]->pi = -1;
	graph[i+1]->color = 1;
	graph[i+1]->pi = -1;

	graph[v]->color = 0;
	graph[v]->pi= -1;
	enqueue(v);
	while (!isEmpty()){
		popped = dequeue();
		for(aux=graph[popped]->first; aux!=NULL; aux=aux->next){
			if(graph[aux->n]->color ==1 && res[convertCoor(popped, aux->n, N+2)] >0){
				graph[aux->n]->color = 0;
				graph[aux->n]->pi=popped;
				enqueue(aux->n);
				if(graph[aux->n]->pos == graph[sink]->pos){
					foundPath =1;
					break;
				}
			}
		}
		if(aux!=NULL){
			graph[aux->n]->color = -1;
		}
	}
	return foundPath;
}

int maxFlow(Vertex* graph, int source, int sink, int N){
	Vertex v;
	int u;
	int maxFlow = 0;
	while(BFS(graph, N, source, sink)){
		int flow = 999;
		v = graph[sink];
		while(v->pos!=source){
			v->color = 2;
			u = v->pi;
			if(flow>res[convertCoor(u, v->pos, N+2)]){
				flow = res[convertCoor(u, v->pos, N+2)];
			}
			v = graph[u];
		}
		graph[source]->color = 2;
		maxFlow+=flow;
		v = graph[sink];
		while(v->pos!=source){
			u = v->pi;
			res[convertCoor(u, v->pos, N+2)] -= flow;
			res[convertCoor(v->pos, u, N+2)] += flow;
			v = graph[u];
		}
	}
	return maxFlow;
}
Vertex newVertex(int pos){
	Vertex v = (Vertex)malloc(sizeof(struct vertex));
	v->color=1;
	v->pi=-1;
	v->pos=pos;
	v->first=NULL;
	v->tail=NULL;
	return v;
}

Node newNode(int pos){
	Node new = (Node)malloc(sizeof(struct node));
	new->n = pos;
	new->next = NULL;
	return new;
}


int *to2D(int index, int width){
	int *coor=(int*)malloc(2*sizeof(int));
	coor[0] = index % width;
	coor[1] = index / width;
	return coor;
}

Vertex insEnd(Vertex v, int newPos){
	Node new = newNode(newPos);
	if(v->tail == NULL){
		v->first=new;
		v->tail=new;
		return v;
	}
	v->tail->next= new;
	v->tail = new;
	return v;
}

Vertex *initUrb(int N, int width, int height){
	int i;
	int *coor;
	int newcoor;
	Vertex *sect=(Vertex*)malloc((N+2)*sizeof(struct vertex));
	res=(int*)malloc((N+2)*(N+2)*sizeof(int));
	for(i=0; i<N; i++){
		sect[i]=newVertex(i);
		coor = to2D(i, width);
		if (coor[1]-1>=0){
			newcoor = convertCoor(coor[0],coor[1]-1, width);
			insEnd(sect[i], newcoor);
			res[convertCoor(i, newcoor, N+2)] = 1;
		}
		if (coor[0]-1 >= 0){
			newcoor = convertCoor(coor[0]-1,coor[1], width);
			insEnd(sect[i], newcoor);
			res[convertCoor(i, newcoor, N+2)] = 1;
		}
		if (coor[0]+1<=width-1){
			newcoor = convertCoor(coor[0]+1,coor[1], width);
			insEnd(sect[i], newcoor);
			res[convertCoor(i, newcoor, N+2)] = 1;
		}
		if (coor[1]+1<=height-1){
			newcoor = convertCoor(coor[0],coor[1]+1, width);
			insEnd(sect[i], newcoor);
			res[convertCoor(i, newcoor, N+2)] = 1;
		}
		free(coor);
	}
	sect[i]=newVertex(i);
	sect[i+1]=newVertex(i+1);
	return sect;
}


/*void printGraph(Vertex* graph, int sects) 
{ 
    int v; 
    for (v = 0; v < sects; v++) 
    { 
        Node pCrawl = graph[v]->first;
        printf("%d Adjacency list of vertex %d\nNumero de casas: %d\nNumero de supermercados: %d\n head ",graph[v]->d, graph[v]->pos, graph[v]->home, graph[v]->market); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->n); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    }
    printf("\n"); 
}*/



int main(){
	int i;
	int width, height;
	int markets, citizens;
	int x, y;
	Vertex *urb;
	scanf("%d %d", &width, &height);
	/*
	Avenidas - width
	Ruas - height 
	*/
	urb = initUrb(width*height, width, height);
	scanf("%d %d", &markets, &citizens);
	for (i=0; i<markets; i++){
		scanf("%d %d", &x, &y);
		insEnd(urb[convertCoor(x-1, y-1, width)], width*height+1);
		res[convertCoor(convertCoor(x-1, y-1, width), width*height+1, width*height+2)] = 1; 

	}
	for (i=0; i<citizens; i++){
		scanf("%d %d", &x, &y);
		insEnd(urb[width*height], convertCoor(x-1, y-1, width));
		res[convertCoor(width*height,convertCoor(x-1, y-1, width), width*height+2)] = 1;

	}
	/*printGraph(urb, (width*height)+2);
	for(i=0; i<width*height+2; i++){
		for(j=0; j<width*height+2; j++){
			printf("%d ",res[convertCoor(j, i, width*height+2)]);
		}
	printf("\n");
	}*/
	printf("%d\n", maxFlow(urb, width*height, width*height+1, width*height));
	return 0;
}