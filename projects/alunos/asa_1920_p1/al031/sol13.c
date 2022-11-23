#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
Projeto 1 ASA
Alunos: Matheus Franco (92523), Guilherme Ribeiros Dias (93908)
*/
#include <stdio.h>
#include <stdlib.h>
#define WHITE 0
#define GRAY 1

typedef struct vertex{
        int grade;
        int number;
        int color;
        struct vertex * next;
} vertex;

int main(){

        /* N : number of vertexes, M : number of edges */
        int N, M, i;
        scanf("%d,%d",&N,&M);
        if(N < 2 || M < 1){
                perror("Invalid number of vertexes or edges\n");
                exit(EXIT_FAILURE);
        }
        int FIFO[N];

        /* create adjancency list of the graph */
        vertex * adjList = (vertex *)can_fail_malloc(sizeof(vertex)*N);
        if(!adjList){
                perror("Fail to allocate adjacent list\n");
                exit(EXIT_FAILURE);
        }
        
        /* takes student's grades input */
        for(i = 0; i < N; i++){
                adjList[i].next = NULL;
                scanf("%d",&adjList[i].grade);
                adjList[i].color = WHITE;

                FIFO[i] = -1;
        }

        /* takes edges input;  Note that we inverted the direction of the edges */
        vertex *u;
        int v;
        for(i = 0; i < M; i++){
                u = (vertex *)can_fail_malloc(sizeof(vertex));
                if(!u){
                        perror("Fail to allocate vertex\n");
                        exit(EXIT_FAILURE);    
                }
                scanf("%d %d",&u->number,&v);
                u->number--;
                v--;
                u->next = adjList[v].next;
                adjList[v].next = u;
        }
        
        /* Note that the Queue is a cyclic buffer of size N since
        a BFS will Enqueue at most N vertexes.
        Every time we Dequeue a value, the position in the buffer assumes -1 */

        int node, fifoIndex = 0, fifoNext = 0, fifoValue ;
        vertex *p;
        /* apply BFS for every node*/
        for(node = 0; node < N; node++){
                if(adjList[node].color == WHITE){

                        adjList[node].color = GRAY; /* turn gray */

                        /* put node in Queue */
                        fifoValue = 0;
                        FIFO[fifoIndex] = node;
                        fifoNext = (fifoIndex+1)%N; /* calculate Queue's next position */
                        
                        /* BFS */
                        while(FIFO[fifoIndex] != -1){ /* while Queue isn't empty */
                                /* take Queue value */
                                fifoValue = FIFO[fifoIndex];
                                FIFO[fifoIndex] = -1; /* clear position */
                                
                                /* take first adjacent node */ 
                                p = adjList[fifoValue].next;
                                while(p != NULL){
                                        /* if a grade is inferior, update and add it to Queue */
                                        if(adjList[p->number].grade < adjList[fifoValue].grade){
                                                FIFO[fifoNext] = p->number;
                                                fifoNext = (fifoNext + 1)%N;
                                                adjList[p->number].grade = adjList[fifoValue].grade;
                                                adjList[p->number].color = GRAY;
                                        }
                                        p = p->next;
                                }
                                fifoIndex = (fifoIndex+1)%N;
                        }
                }
        }
        /* print students grades */
        for(i = 0; i < N; i++){
                printf("%d\n",adjList[i].grade);
                /* release memory */
                p = adjList[i].next;
                while(p!=NULL){
                        u = p;
                        p = p->next;
                        free(u);
                }
        }
        free(adjList);

        return 0;
}

