#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE  0
#define TRUE 1


typedef struct Queue
{
    int* elemnts;
    int size;
    int end;
    int front;

}queue;

typedef struct Edge
{
    int capacity;
    int flow;
    int to;
    struct Edge *next ;
}edge;

typedef struct Node
{
    int vertex_id;
    int hasSuperMarket;
    int hasClient;
    edge * head;

}node;


typedef struct Graph
{
    int num_vertices;
    node *adjList;

}grph;


int bfs(grph *g, int source, int target, int parents[]);
int edmondsKarp(grph *g,int source, int target);
int min(int val1, int val2);


/*int num_vertices;*/
int num_avenues;
int num_streets;
int num_citiezens;
int num_supermarket;

/*queue functions*/
queue * init_queue(int size)
{
    queue * q;
    q = (queue*) can_fail_malloc(sizeof(queue));
    q->elemnts = (int*) can_fail_malloc (sizeof(int)*size);
    q->size = size;
    q->end=0;
    q->front=0;
    return q;
}

void addQueue(queue *queue, int element)
{
    if(queue->end != queue->size)            /* Queue isnt Full*/
    {
        queue->elemnts[queue->end] = element;    /* Add the element to the back */
        queue->end++;

    }
}


int pop( queue * queue) {
    int el= -1;
    if(queue->front != queue->end)            /*Queue isnt empty*/
    {
        el = queue->elemnts[queue->front];
        queue->elemnts[queue->front] = -1;        /* Delete the front element*/
        queue->front++;

    }
    return el;
}



int is_empty(queue* q)
{
    if(q->front == q->end )
    {
        return TRUE;
    }
    return FALSE;
}

void free_queue(queue* q)
{
    if (q != NULL)
    {
        free(q->elemnts);
        free(q);
    }
}
/* graph functions */


grph* createGraph(int vertices)
{

    grph * gr = (grph*) can_fail_malloc (sizeof(grph));
    int i;

    gr->num_vertices = vertices;
    gr->adjList = (node*)can_fail_malloc(vertices*sizeof(node));


    for(i=0; i < vertices; i++)
    {

         gr->adjList[i].head=NULL;

    }

    return gr;
}


void createNode(grph * g ,int vertex_id)
{
    g->adjList[vertex_id].vertex_id = vertex_id;
    g->adjList[vertex_id].hasClient=0;
    g->adjList[vertex_id].hasSuperMarket=0;

}

void addEdge(grph* G, int vertexU, int vertexV,int reverse)
{
    edge *e =(edge*)can_fail_malloc(sizeof(edge));
    edge *aux;

    e->flow = 0;
    e->to=vertexV;
    if(!reverse)
    {
       e->capacity=1;
    }
    else
    {
        e->capacity=0;

    }

    if(G->adjList[vertexU].head== NULL)
    {
        G->adjList[vertexU].head= e;
        e->next=NULL;
    }
    else
    {
        aux= G->adjList[vertexU].head;
        e->next= aux;
        G->adjList[vertexU].head=e;
    }


}


void addAllCityEdges(grph *g, int M, int N)
{
    int i;

    for(i = 1;i <= N*M; i++)
    {
        /*adicionar arestas do vin para o vout, em todos os vertices*/
        addEdge(g,i,i+(M*N),0);
        addEdge(g,i+(M*N),i,1); /*aresta residual*/


        if(i == 1) /*Canto superior esquerdo*/
        {
            if(M > 1)
            {
                addEdge(g,1+N*M,2,0); /* 1 out para 2in */
                addEdge(g,2,1+M*N,1); /*reverse edge*/
            }
            if(N > 1)
            {
                addEdge(g,1+N*M,1+M,0); /*1 out para vertice inferior in */
                addEdge(g,1+M,1+M*N,1); /*reverse edge */

            }
        }
        else if(i==M && M!=1) /*canto superior direito */
        {
            addEdge(g,i+N*M,i-1,0);/* iout para i-1 in (anterior) */
            addEdge(g,i-1,i+N*M,1); /*reverse*/


            if(N > 1)
            {
                addEdge(g,M+N*M,M+M,0); /*iout para i+M in (vertice em baixo)*/
                addEdge(g,M+M,M+M*N,1); /*reverseEdge; */
            }

        }
        else if(i == M*N && N > 1) /*canto inferior direito*/
        {
            addEdge(g,i+M*N, i-M,0); /*iout para i-M in, vertice de cima*/
            addEdge(g,i-M,i+M*N,1); /*reverse */

            addEdge(g,i+M*N,i-1,0); /*aresta para o vertice anterior */
            addEdge(g,i-1,i+M*N,1); /*reverse  */

        }
        else if(i==((M*N)-(M-1)) && N>1) /*canto inferior esquerdo*/
        {
            addEdge(g,i+M*N,i-M,0); /* aresta para o vertice superior*/
            addEdge(g,i-M,i+M*N,1); /*reverse*/

            addEdge(g,i+M*N,i+1,0); /*aresta para o vertice seguinte*/
            addEdge(g,i+1,i+M*N,1); /*reverse*/

        }
        else if(i>1 && i<M) /*vértices do lado superior do quadrado*/
        {
            addEdge(g,i+M*N,i-1,0); /*do iout para vertice anterior in */
            addEdge(g,i-1,i+M*N,1) ; /*reverse*/


            addEdge(g,i+M*N,i+1,0); /*vertice seguinte*/
            addEdge(g,i+1,i+M*N,1); /*reverse */

            addEdge(g,i+M*N,i+M,0); /*aresta para vertice de baixo*/
            addEdge(g,i+M, i+M*N,1); /*reverse*/

        }
        else if(i>M*N-(M-1) && i< N*M && N>1) /*lado inferior*/
        {
            addEdge(g,i+M*N,i-1,0); /*vertice anterior */
            addEdge(g,i-1,i+M*N,1) ; /*reverse*/


            addEdge(g,i+M*N,i+1,0); /*vertice seguinte*/
            addEdge(g,i+1,i+M*N,1); /*reverse*/


            addEdge(g,i+M*N,i-M,0); /*vertice de cima*/
            addEdge(g,i-M,i+M*N,1);/*reverse*/
        }
        else if(i%M == 1 && i!=1 && i!= N*M -M+1) /* vertices do lado esquerdo*/
        {
            addEdge(g,i+M*N,i-M,0); /*do i out para o de cima in*/
            addEdge(g,i-M,i+M*N,1); /* reverse*/


             addEdge(g,i+M*N,i+1,0); /* do i out para o de seguinte in*/
             addEdge(g,i+1,i+M*N,1);/*reverse*/


             addEdge(g,i+M*N,i+M,0); /* do i out para o de baixo */
             addEdge(g,i+M,i+M*N,1); /*reverse*/

        }
        else if(i%M==0 && i!=M-1 && i!= N*M) /* lado direito do quadrado */
        {
            addEdge(g,i+M*N,i-M,0); /* adiciona do i out para o vertice de cima in */
            addEdge(g,i-M,i+M+M*N,1); /*reverse*/


            addEdge(g,i+M*N,i-1,0); /* adiciona do i out para o anterior in */

            addEdge(g,i-1,i+M*N,1);/*reverse*/


            addEdge(g,i+M*N,i+M,0); /* adiciona do i out para o vertice de baixo in */
            addEdge(g,i+M,i+M+M*N,1); /*reverse*/
        }
        else /* todos os vertices no meio do grafo */
        {
            addEdge(g,i+M*N,i-M,0); /* adiciona do i out para o vertice de cima in */
            addEdge(g,i-M,i+M+M*N,1); /*reverse*/

            addEdge(g,i+M*N,i-1,0); /* adiciona do i out para o anterior in */
            addEdge(g,i-1,i+M*N,1);/*reverse  */


            addEdge(g,i+M*N,i+M,0); /* adiciona do i out para o vertice de baixo in */
            addEdge(g,i+M,i+M+M*N,1); /*reverse*/

            addEdge(g,i+M*N,i+1,0); /*vertice seguinte*/
            addEdge(g,i+1,i+M*N,1); /*reverse*/

        }
    }
}


void free_graphs(grph* gr)
{

     int i;
    edge* aux;

    for(i = 0; i < gr->num_vertices; i++)
    {
        aux=gr->adjList[i].head;
        while(aux!=NULL)
        {
           aux=aux->next;
           free(gr->adjList[i].head);
           gr->adjList[i].head = aux;
        }
    }

    free(gr->adjList);

    free(gr);


}

/*BFS and Edmonds-Karp functions*/
int bfs(grph *g, int source, int target, int parents[])
{
    int currentPathCapacity[g->num_vertices];
    int i;
    edge * temp;
    for(i = 0;i < g->num_vertices; i++)
    {
        parents[i] = -1;
        currentPathCapacity[i] = 0;
    }

    queue * q = init_queue(g->num_vertices);
    addQueue(q, source);

    parents[source] = -2;
    currentPathCapacity[source] = 999;

    while(!is_empty(q))
    {
        int currentNode = pop(q);

       for(temp=g->adjList[currentNode].head;temp!=NULL;temp=temp->next)
        {
           if(parents[temp->to]==-1)
            {
                if(temp->capacity - temp->flow >0)
               {
                    parents[temp->to]=currentNode;
                    currentPathCapacity[temp->to]= min(currentPathCapacity[currentNode],temp->capacity- temp->flow);

                    if(temp->to == target)
                    {
                        free_queue(q);
                        return currentPathCapacity[target];
                    }

                    addQueue(q,temp->to);
                }
            }
        }
    }
    free_queue(q);
   return 0;
}


int min(int val1, int val2)
{
    return val1 < val2 ? val1 : val2;
}


int edmondsKarp(grph *g,int source, int target)
{
    int maxFlow = 0;
    int flow;
    int currentNode;
    edge* temp , *aux;

    int parents[g->num_vertices];

    while(TRUE)
    {

        flow = bfs(g,source, target, parents);
        if (flow == 0) /* nao encontrou um caminho */
        {
            break;
        }

        maxFlow += flow;
        currentNode = target;

        while(currentNode != source)
        {
            temp=g->adjList[parents[currentNode]].head;
            while(temp!=NULL)
            {
                if(temp->to==currentNode)
                {

                    temp->flow+=flow;
                    break;

                }
                temp=temp->next;
            }
            aux= g->adjList[currentNode].head;
            while(aux!=NULL)
            {
                if(aux->to==parents[currentNode])
                {

                    aux->flow-=flow;
                    break;

                }
               aux = aux->next;

            }

            currentNode = parents[currentNode];
        }
    }
    free_graphs(g);
    return maxFlow;
}

int main(int argc, const char** argv)
{

    int i;
    int avenue, street;
    grph * G;

    scanf("%d %d", &num_avenues, &num_streets);
    scanf("%d %d", &num_supermarket, &num_citiezens);

   G = createGraph(num_avenues*num_streets*2+2);

    for(i = 0; i < num_avenues*num_streets*2+2; i++) /* vertices in e out + supersource + supertarget
    Assumindo que supersource fica na posição: 0 e o supertarget na posição 2*num_vertices + 1
   */
    {
        createNode(G,i);
    }


    for( i = 0; i < num_supermarket; i++)
    {
        scanf("%d %d", &avenue, &street);
        if(!G->adjList[(street-1)*num_avenues+avenue+((num_avenues*num_streets*2+2)-2)/2].hasSuperMarket)
        {
            addEdge(G,(street-1)*num_avenues+avenue+((num_avenues*num_streets*2+2)-2)/2,(num_avenues*num_streets*2+2)-1,0);
            addEdge(G,(num_avenues*num_streets*2+2)-1,(street-1)*num_avenues+avenue+((num_avenues*num_streets*2+2)-2)/2,1); /*reverse*/
            G->adjList[(street-1)*num_avenues+avenue+((num_avenues*num_streets*2+2)-2)/2].hasSuperMarket=1;
        }

    }

    for(i = 0; i < num_citiezens; i++)
    {
        scanf("%d %d", &avenue, &street);
        if(!G->adjList[(street-1)*num_avenues+avenue].hasClient)
        {
            addEdge(G,0,(street-1)*num_avenues+avenue,0);
            addEdge(G,(street-1)*num_avenues+avenue,0,1);/*reverse edge*/
            G->adjList[(street-1)*num_avenues+avenue].hasClient=1;
        }


    }

    addAllCityEdges(G,num_avenues,num_streets);

    for(i=0;i<G->num_vertices;i++)
    {
        edge* temp= G->adjList[i].head;
        while(temp!=NULL)
        {
           temp=temp->next;
        }

    }


    printf("%d\n",edmondsKarp(G,0,(num_avenues*num_streets*2+2)-1));



    return 0;
}
