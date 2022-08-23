/*Pedro Nora numero 92536 grupo 149*/ 
 
#include <stdio.h>  
#include <string.h>   
#include <stdlib.h> 


int alunos; 
int amizades;   
int i;  
int j; 
int linha; 
int coluna;


int findmax(int array[], int size){
    int max = array[0];  
    int index;
    for( index=1;index<size;index++){ 
        if(array[index]> max){ 
            max = array[index];
        }
    } 
    return max;
}


void dfs(int i, int len, int vec[], int grades[], int visit[],int **matrix){ 
    int j; 
    vec[i]=grades[i]; 
    visit[i]=1; 
    for(j=1;j<len;j++){ 
        if(matrix[i][j]!=0 && visit[j]==0){ 
            dfs(j,len,vec,grades,visit,matrix);}
    }  
}

int main(){   

    scanf("%d,%d", &alunos, &amizades); 

    int tamanho = alunos +1;
    int notas[tamanho]; 
    int visitados[tamanho]; 
    int dfsvec[tamanho];   
    /*int graph[tamanho][tamanho];*/ 
    int **graph=(int **)malloc(tamanho * sizeof(int *));
    for(i=0;i<tamanho;i++){
     graph[i]=(int *)malloc(tamanho *  sizeof(int)); }
     

    if(alunos<2 || amizades <1)
        exit(0);
    

    for(i=0;i<tamanho;i++){ 
        notas[i]=0;  
        visitados[i]=0; 
        dfsvec[i]=0;}


    for(i=0;i<tamanho;i++){
        for(j=0;j<tamanho;j++){ 
            graph[i][j]=0;} 
    }

    for(i=1;i<tamanho;i++) 
        scanf("%d", &notas[i]);  

    for(i=0;i<amizades;i++){ 
        scanf("%d %d", &linha,&coluna); 
        graph[linha][coluna]=1;}   
    for(i=0; i<tamanho; i++){  
        dfs(i,tamanho,dfsvec,notas,visitados,graph); 
        notas[i]=findmax(dfsvec,tamanho);  
        for(j=0;j<tamanho;j++) 
            visitados[j]=0;   
        for(j=0;j<tamanho;j++)
            dfsvec[j]=0;

     
    }

    for(i=1;i<tamanho;i++)
        printf("%d\n", notas[i]);  
    for(i=0;i<tamanho;i++){  
        free(graph[i]);}  
    free(graph);

    return 0;
}