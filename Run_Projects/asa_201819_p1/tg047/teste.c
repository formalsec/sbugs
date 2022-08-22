#include <stdio.h>
#include <stdlib.h>
/*ADJACENCY MATRIX*/
int source,V,E,time, numeorDeNodesAux = 0,numeroDeIlhas = 0,numeroDeIl = 0,pontosC = 0,cont = 0,contAux=1;

/*
Swap function serves as a aux for the bubbleSort
*/
void swap(int *xp, int *yp) { 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

/*
BubbleSort function for organization
*/
void bubbleSort(int arr[], int n) { 
   int i, j; 
   for (i = 0; i < n-1; i++)          
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
}

/*
DFS function
*/
void DFS(int i,int t, int G[t][t],int visited[t]){
    int j;
    visited[i]=1;
    cont++;
    if (i+1 >= numeorDeNodesAux) {
        numeorDeNodesAux = i+1;
    }
    for(j=0;j<E;j++){
        if(G[i][j]==1&&visited[j]==0){
            G[i][j] = 2;
            G[j][i] = 2;
            DFS(j,t,G,visited);
        }else if (G[i][j]==1&&visited[j]==1) {
            G[i][j] = 2;
        }
    }
}



/*
DFS function
*/
void DFSAux(int i,int t, int G[t][t],int visited[t],int nodes[t], int cont){
    int j;
    visited[i]=1;
    if (i+1 >= numeorDeNodesAux) {
        numeorDeNodesAux = i+1;
    }
    nodes[cont++] = i;
    for(j=0;j<E;j++){
        if(G[i][j]==1&&visited[j]==0){
            G[i][j] = 2;
            G[j][i] = 2;
            DFSAux(j,t,G,visited,nodes,cont);
        }else if (G[i][j]==1&&visited[j]==1) {
            G[i][j] = 2;
        }
    }
}

/*

*/
void numeroIlhasAux(int tamanho, int mat[tamanho][tamanho],int visited[tamanho],int nodes[tamanho],int cont){
    int i,j;
    for( i = 0; i < tamanho; i++){
        for(j = 0; j < tamanho; j++){
            if (mat[i][j] == 1) {
                DFSAux(i,tamanho,mat,visited,nodes,cont);
                numeroDeIl++;
                numeorDeNodesAux = 0;
            }   
        }   
    } 
}


/*
Function to print the nodes that identify the ilands
*/
int *identificadores(int tamanho, int mat[tamanho][tamanho],int visited[tamanho]){
    int i,j,v= 0,i1;
    int *arr = (int*)malloc(tamanho*sizeof(int)); 
    for(i1 = 0; i1 < tamanho; i1++){
        arr[i1] = 0;
    }
    for( i = 0; i < tamanho; i++){
        for(j = 0; j < tamanho; j++){
            if (mat[i][j] == 1) {
                DFS(i,tamanho,mat,visited);
                arr[v++] = numeorDeNodesAux;
                numeroDeIlhas++;
                numeorDeNodesAux = 0;
            }   
        }   
    }
    printf("%d\n",numeroDeIlhas);
    return arr;   
}


/*

*/
void numeroIlhas(int tamanho, int mat[tamanho][tamanho],int visited[tamanho]){
    int i,j;
    for( i = 0; i < tamanho; i++){
        for(j = 0; j < tamanho; j++){
            if (mat[i][j] == 1) {
                DFS(i,tamanho,mat,visited);
                numeroDeIlhas++;
                numeorDeNodesAux = 0;
            }   
        }   
    }
    printf("%d\n",numeroDeIlhas);   
}

void delete(int d, int tamanho ,int mat[tamanho][tamanho]){
    int i;
    for(i = 0; i < tamanho; i++){
        mat[d][i] = 0;
        mat[i][d] = 0;
        
    } 
}

int *pontesCriticos(int tamanho, int mat[tamanho][tamanho],int visited[tamanho],int visitedAux[tamanho],int nodes[tamanho], int cont){
    int i,j,matAux[tamanho][tamanho],i1,i2,bla=0,i5,i6,i7,i8,i9=0,k;
    int *arr = (int*)malloc(tamanho*sizeof(int));
    for(k = 0; k < tamanho; k++){
        arr[k] = -1;
    }
    for(i = 0; i < tamanho; i++){
        for(i6 = 0; i6 < tamanho; i6++){
            for(i7 = 0; i7 < tamanho; i7++){
                matAux[i6][i7] = mat[i6][i7];
            }
        }
        delete(i,tamanho,matAux);
        numeroIlhasAux(tamanho,matAux,visitedAux,nodes,cont);

        

        for(i1 = 0; i1 < tamanho; i1++){
            if (visited[i1] == 1&&visitedAux[i1] == 0&& i1!=i) {
                numeroDeIl++;
            } 
        }
        if (numeroDeIl > numeroDeIlhas) {
            pontosC++;
            arr[i9++] = i;
        }
        for(i5 = 0; i5 < tamanho; i5++){
            visitedAux[i5] = 0;
        }
        numeroDeIl = 0;
    }
    printf("\n%d\n",pontosC);
    return arr;
}

void remo(int tamanho,int mat[tamanho][tamanho],int visited[tamanho],int arr[tamanho]){
    int i,i1,j,i3,j3;
    for(i = 0; i < tamanho; i++){
        if (arr[i] != -1) {
            delete(arr[i],tamanho,mat);
        }
    }
    for( i1 = 0; i1 < tamanho; i1++){
        for(j = 0; j < tamanho; j++){
            if (mat[i1][j] == 1) {
                DFS(i1,tamanho,mat,visited);
                if (cont > contAux) {
                    contAux = cont;
                }
                
            }
            cont = 0;   
        }   
    }
    printf("%d\n",contAux);
    
}





int main()
{
    int i,j,v1,v2,i1,i2;
    printf("\t\t\tGraphs\n");
    scanf("%d",&E);
    scanf("%d",&V);
    
    int visited[E],visitedAux[E],G[E][E],nodes[E],cont= 0;
    int K[E][E];
    int *arr = (int*)malloc(E*sizeof(int));
    int *arr1 = (int*)malloc(E*sizeof(int)); 
    

    /*----Poe tuda a 0's----*/
    for(i=0;i<E;i++){
        for(j=0;j<E;j++){
            G[i][j]=0;
        }
    }
    for(i1 = 0; i1 < E; i1++){
        visited[i1] = 0;
        visitedAux[i1] = 0;
    }

    /*---------------------*/

    /*    creating edges :P    */
    for(i=0;i<V;i++){
        scanf("%d%d",&v1,&v2);
        G[v1-1][v2-1]=1;
        G[v2-1][v1-1]=1;
        
    }


    /*----Print dos identificadores das ilhas----*/
    arr =identificadores(E, G,visited);

    bubbleSort(arr, E); 

    for(i2 = 0; i2 < E; i2++){
        if (arr[i2] == 0) {
            continue;
        }else{
            printf("%d ",arr[i2]);
        }   
    }
    /*-----------------------------------------*/

    /*----Reset matrix----*/
    for(i=0;i<E;i++){
        for(j=0;j<E;j++){
            if (G[i][j] == 2) {
                G[i][j] = 1;
            }
        }
    }
    /*------------------*/
    arr1 = pontesCriticos(E,G,visited,visitedAux,nodes,cont);

    for(i1 = 0; i1 < E; i1++){
        visited[i1] = 0;
    }


    remo(E,G,visited,arr1);

    




    return 0;
}