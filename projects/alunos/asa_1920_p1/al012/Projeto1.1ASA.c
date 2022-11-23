#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/**
* Projeto de ASA - Parte 1
*   Grupo 12
* Inês Silva       N92484
* Rodrigo Gomes    N92548
*/


#include <stdio.h>
#include <stdlib.h>


int nAlunos;
int nAmizades;


typedef struct Aluno{
    int indice_aluno;
    int nota;
    int b_visited;
    int n_de_amigos;
    struct Aluno *anterior;
    struct Aluno **amigos;
} aluno;

aluno *alunos;
aluno *proximo;


void escreveNotas(){
    int i;
    
    for(i=0;i<nAlunos;i++){
        printf("%d\n",alunos[i].nota);
    }
}




void DFS_Alg(int indice){
    int i,j;
    
    alunos[indice].b_visited=1;
    
    for(i=0;i<alunos[indice].n_de_amigos;i++){

        if(alunos[indice].amigos[i]!=NULL){
            
            if(alunos[indice].amigos[i]->b_visited==0){
                proximo=alunos[indice].amigos[i];
                alunos[indice].amigos[i]=NULL;
                break;
            }
            else{
                if(alunos[indice].amigos[i]->nota>alunos[indice].nota)
                    alunos[indice].nota=alunos[indice].amigos[i]->nota;

                alunos[indice].amigos[i]=NULL;
            }

        }
    }

    if(i==alunos[indice].n_de_amigos){
        if(alunos[indice].anterior==NULL){
        
            for(j=0;j<nAlunos;j++){
                if(alunos[j].b_visited==0 && alunos[j].amigos[0]!=NULL){
                    break;
                }
            }
            if(j==nAlunos){
                escreveNotas();
                return;
            }
            else{
                alunos[j].anterior=NULL;
                DFS_Alg(alunos[j].indice_aluno-1);
            }
        }
        else{
            if(alunos[indice].nota > alunos[indice].anterior->nota){
                alunos[indice].anterior->nota=alunos[indice].nota;
            }
    
            DFS_Alg(alunos[indice].anterior->indice_aluno-1);

        }
    }
    else{
        proximo->anterior=&alunos[indice];
        DFS_Alg(proximo->indice_aluno-1);
    }

    
}






int main(){
	int i=0,j=0,k=0,h=0,Prev_Student,student=-1,friend;
    
    
    
    scanf("%d,%d", &nAlunos, &nAmizades);


    alunos=(aluno*)can_fail_malloc(sizeof(aluno)*nAlunos);
    proximo=can_fail_malloc(sizeof(aluno));


    while(h<nAlunos){
        alunos[h].indice_aluno=0;
        alunos[h].nota=0;
        alunos[h].amigos=(aluno**)can_fail_malloc(sizeof(aluno*));
        alunos[h].amigos[0]=NULL;
        alunos[h].n_de_amigos=0;
        alunos[h].anterior=can_fail_malloc(sizeof(aluno));
        alunos[h].b_visited=0;
        h++;
    }
    alunos[0].anterior=NULL;
    
    
    
    while(i<nAlunos){
        scanf("%d",&alunos[i].nota);
        alunos[i].indice_aluno=i+1;
        i++;
    }
    while(j<nAmizades){
        Prev_Student=student;
        scanf("%d %d",&student,&friend);
        student--;
        friend--;
        if(Prev_Student==student)
            k++;
        else
            k=0;
        alunos[student].amigos=(aluno**)can_fail_realloc(alunos[student].amigos,sizeof(aluno*)*(k+1));
        alunos[student].amigos[k]=&alunos[friend];
        alunos[student].n_de_amigos++;
        j++;
    }

    DFS_Alg(0);
    
    return 0;
}