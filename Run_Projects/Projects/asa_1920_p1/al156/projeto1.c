/*Joao Jose Carreto Moreira Fernandes  92492  grupo 156
*/

#include <stdio.h>
#include <stdlib.h>

#define ZERO 0
#define UM 1
#define less(A,B) (A<B)

int*CriaVectorNotas(int tamanho){
    int*v,i,num;
    v = (int*)malloc(tamanho*sizeof(int));
    for (i=0;i<tamanho;i++){
        scanf("%d",&num);
        v[i]= num;
    }
    return v;
}


void freeRelaALun(int **v,int tamanho){
    int i=0;
    for (i = 0;i<tamanho;i++){
        free(v[i]);
    }
    free(v);
}

void printvector1(int*v,int tamanho){
    int i;
    for (i =0; i<tamanho;i++){
        printf("%d\n",v[i]);
    }
}


/* Vai percorrer a matriz das relacoes do fim ate ao inicio
para o caso se houver alguma alteracao, mudar o que foi
percorrido*/
void percorreRela(int **r,int *a, int tamanho,int valor){
    int j;
    for (j=0;j<tamanho;j++){
        if((r[j][valor]== UM) && a[j] < a[valor]){
            a[j] = a[valor];
            percorreRela(r,a,tamanho,j);

        }
    }
}

/*vai percorrer a matriz das relaçoes e vai usar a funcao
verificaNota da relacao de dois alunos especificos*/
void estudoNota(int **r, int *a,int numALunos){
    int i,j;

    for (i=0;i<numALunos;i++){
        for(j=0;j<numALunos;j++){
            if((r[i][j]==UM) && less(a[i], a[j])){
                a[i] = a[j];
                percorreRela(r,a,numALunos,i);
            }
        }
    }

    printvector1(a,numALunos);  
}


int main(){
    int num1,num2,i,*notas, **adj_matrix, r, c, nodes,numrel;
    
    scanf ("%d,%d", &nodes,&numrel);
    
    adj_matrix = (int **) malloc (sizeof(int **)*nodes);

    for (r = 0; r < nodes; r++) {
        adj_matrix[r] = (int *) malloc(sizeof(int)*nodes);
    }
    
    for (r = 0; r < nodes; r++) {
        for (c = 0; c < nodes; c++) {
            adj_matrix[r][c] = 0;
        }
    } 

    notas = CriaVectorNotas(nodes);

    for (i=0; i<numrel;i++){
        scanf("%d %d", &num1,&num2);
        adj_matrix[num1-1][num2-1]=1;
    }
    estudoNota(adj_matrix,notas,nodes);
    
    freeRelaALun(adj_matrix,nodes);
    free(notas);

    return 0;  

}