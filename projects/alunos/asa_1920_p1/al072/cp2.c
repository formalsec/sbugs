#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 20
int source,V,E,time,maxNotaG;
int *N, *visited;
int **G;
void DFS(int i);
int main()
{
    int i,j,v1,v2,nota;
    
    
    scanf("%d,%d",&V,&E);
    if(V>=2&&E>=1){
        N = (int *)can_fail_malloc(V * sizeof(int));
        visited = (int *)can_fail_malloc(V * sizeof(int));
        G = (int **)can_fail_malloc(V* sizeof(int*));
        for(i=0;i<V;i++){
            G[i]= (int *)can_fail_malloc(V* sizeof(int*));
        }
        for(i=0;i<V;i++){
            for(j=0;j<V;j++)
                G[i][j]=0;
        }
        for(i=0;i<V;i++){
            N[i] = 0;
        }
        
        for(i=0;i<V;i++){
            scanf("%d",&nota);
            N[i] = nota;
        }

        for(i=0;i<E;i++){
            scanf("%d%d",&v1,&v2);
            G[v1-1][v2-1]=1;
        }
    }else{
        printf("erro inserir o numero das displinas ou o numero da relacao.");
    }
    

    maxNotaG= 0;
    for(source = 1; source<= V;source++){
        DFS(source-1);
        N[source-1] = maxNotaG;
         for(i=0;i<V;i++)
        {
           visited[i]=0; 
        }
        maxNotaG= 0;
    }

    for(i=0;i<V;i++)
    {
        printf("%d\n",N[i]);
    }

    return 0;
}

void DFS(int i)
{   int pessoa = i;
    int j;
    visited[i]=1;

    if(maxNotaG<N[pessoa]){
        maxNotaG = N[pessoa];
    }
    for(j=0;j<V;j++)
    {
        if(G[i][j]==1&&visited[j]==0)
            DFS(j);
    }
}
