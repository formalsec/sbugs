#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>

/************************************************/
/* Analise e Sintese de Algoritmos*/

/*68160 João Rodrigues*/
/*Grupo tg043*/

/*************************************************/

int NODES;
int INFINITO = 999999;
int INFINITE;

int min(int a, int b) {
    return a<b ? a : b;
}
void push(int **C, int ** F, int *excess, int u, int v) {
    
    int send = min(excess[u], C[u][v] - F[u][v]);
    F[u][v] += send;
    F[v][u] -= send;
    excess[u] -= send;
    excess[v] += send;
}
 
void relabel(int **C,int **F, int *height, int u) {
    int v;
    int min_height = INFINITE;
    for (v = 0; v < NODES; v++) {
            if (C[u][v] - F[u][v] > 0) {
                min_height = min(min_height, height[v]);
                height[u] = min_height + 1;
            }
    }
}
 
void discharge(int **C, int ** F, int *excess, int *height, int *seen, int u) {
    while (excess[u] > 0) {
            if (seen[u] < NODES) {
                int v = seen[u];
                if ((C[u][v] - F[u][v] > 0) && (height[u] > height[v])){
                    push(C, F, excess, u, v);
                }
            else
                seen[u] += 1;
            } else {
                relabel(C, F, height, u);
                seen[u] = 0;
            }
    }
}
 
void moveToFront(int i, int *A) {
    int temp = A[i];
    int n;
    for (n = i; n > 0; n--){
            A[n] = A[n-1];
    }
    A[0] = temp;
}
 
int pushRelabel(int **C, int ** F, int source, int sink, int inf) {

    int *excess, *height, *list, *seen, i, p;
    int maxflow = 0;
    INFINITE = inf;
    excess = (int *) can_fail_calloc(NODES, sizeof(int));
    height = (int *) can_fail_calloc(NODES, sizeof(int));
    seen = (int *) can_fail_calloc(NODES, sizeof(int));
 
    list = (int *) can_fail_calloc((NODES-2), sizeof(int));
 
    for (i = 0, p = 0; i < NODES; i++){
            if((i != source) && (i != sink)) {
                list[p] = i;
                p++;
            }
    }
 
    height[source] = NODES;
    excess[source] = INFINITE;
    for (i = 0; i < NODES; i++)
            push(C, F, excess, source, i);
 
    p = 0;
    while (p < NODES - 2) {
            int u = list[p];
            int old_height = height[u];
            discharge(C, F, excess, height, seen, u);
            if (height[u] > old_height) {
                moveToFront(p,list);
                p=0;
            }
            else
                p += 1;
    }
    
    for (i = 0; i < NODES; i++)
            maxflow += F[source][i];
 
    free(list);
 
    free(seen);
    free(height);
    free(excess);
 
    return maxflow;
}
 
/*void printMatrix(int ** M) {
    int i,j;
    for (i = 0; i < NODES; i++) {
            for (j = 0; j < NODES; j++)
                printf("%d\t",M[i][j]);
                printf("\n");
    }
}*/

int main() {
    int i, j;
    int k = 0;

    /*read input*/
    int f;
    int e;
    int t;


    int origin;
    int destination;
    int cap;

    int *hi, *hiAux, *hiFinal, *aumentarOrig, *aumentarDest, *abast, **flow, **capacities;

    int a ;

    scanf("%d %d %d", &f, &e, &t);
    NODES= f+e+1;

    flow = (int **) can_fail_calloc(NODES, sizeof(int*));
    capacities = (int **) can_fail_calloc(NODES, sizeof(int*));
    for (i = 0; i < NODES; i++) {
        flow[i] = (int *) can_fail_calloc(NODES, sizeof(int));
        capacities[i] = (int *) can_fail_calloc(NODES, sizeof(int));
    }

    hi = (int *) can_fail_calloc(NODES, sizeof(int*));
    hiAux = (int *) can_fail_calloc(NODES, sizeof(int*));
    hiFinal = (int *) can_fail_calloc(NODES, sizeof(int*));
    abast = (int *) can_fail_calloc(e, sizeof(int*));

    aumentarOrig =(int *) can_fail_calloc(t, sizeof(int*));
    aumentarDest =(int *) can_fail_calloc(t, sizeof(int*));


	for(i=0; i < f; i++){
    	scanf("%d", &hi[1+i]);
        hiAux[1+i] = hi[1+i];
        hiFinal[1+i] = 0;
	}

    for(i=0; i < e; i++){
        scanf("%d", &hi[f+1+i]);
        hiAux[f+1+i] = hi[f+1+i];
        hiFinal[f+1+i] = 0;
    }

    for(i=0; i < t; i++){
        scanf("%d %d %d", &origin, &destination, &cap);
        capacities[origin-1][destination-1] = cap;
    }
    hi[0] = 0;
    hiAux[0] = 0;
    hiFinal[0] = 0;

    for (i = 1; i < f+1; i++){
        for(j=0; j<NODES; j++ ){
            if (capacities[i][j] > 0) {
                if(j==0){
                    hi[j] = hi[j] + min(hi[i], capacities[i][j]);
                    hiAux[j] = 0;
                    if( hi[i] > capacities[i][j] || hi[i] == capacities[i][j]){
                        aumentarOrig[k] = i+1;
                        aumentarDest[k] = j+1;
                        k = k+1;

                    }
                }
                else{

                    a =  min(pushRelabel(capacities, flow, i, j, hi[i]),  hiAux[j]);
                    if(j>= e+1){
                        if (hi[i] > capacities[i][j] && capacities[i][j] > hiAux[j]){
                            abast[j-f-1] = j+1;
                        }  
                    }


                    hiAux[j] = hiAux[j] - a;
                    if( (hi[i]-a)> 0  && hiAux[j] >0 ){
                        aumentarOrig[k] = i+1;
                        aumentarDest[k] = j+1;
                        k = k+1;

                    }
                    hiFinal[j] = hiFinal[j] + a;

                }

                
            }
        }
    }






    for (i = f+1; i < NODES; i++){
        for(j=0; j<NODES; j++ ){
            if (capacities[i][j] > 0) {
                if(j==0){
                    hi[j] = hi[j] + min(hiFinal[i], capacities[i][j]);
                    hiAux[j] = 0;
                    if( hi[i] > capacities[i][j] || hi[i] == capacities[i][j] ){
                        aumentarOrig[k] = i+1;
                        aumentarDest[k] = j+1;
                        k = k+1;

                    }
                 
                }
                else{
                    a =  min(pushRelabel(capacities, flow, i, j, hiFinal[i]),  hiAux[j]);
                    hiAux[j] = hiAux[j] - a;
                }

                
            }
        }
    }



    printf("%d\n", hi[0]);

    for(i=0; i<e; i++){
        if(abast[i]>0){
            printf("%d", abast[i]);
        
            if(i != e-1 ){
                printf(" ");
            }
        }
    }
    printf("\n");

    for(i=0; i<t; i++){
        if(aumentarOrig[i]>0 && aumentarDest[i]>0){
            printf("%d %d\n", aumentarOrig[i], aumentarDest[i]);
        
        }
    }


    free(hi);
    free(hiAux);
    free(hiFinal);
    free(abast);
    free(aumentarOrig);
    free(aumentarDest);


    return 0;
}

