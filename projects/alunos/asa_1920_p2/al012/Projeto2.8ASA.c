#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*Projeto ASA: Rodrigo Gomes n92548  Ines Silva n92484    Grupo:12*/
#include <stdio.h>
#include <stdlib.h>


int nLinhas;
int nColunas;
int nVertices;
int nMarkets;
int nCitizens;

typedef struct Aresta aresta;

typedef struct Vertice{
    int indice_vertice_l;
    int indice_vertice_c;
    int market;
    int visited;
    int capacidade;
    aresta **arestas;
    aresta *anterior;
    struct Vertice *anterior_vertice;
} vertice;

typedef struct Aresta{
    int capacity;
    vertice *vertex;
} aresta;


vertice **esquinas;
vertice **citizens;


void Initialize_Graph(){
    int i,j,k,f1,f2,f3;
    for(i=0;i<nLinhas;i++){
        for(j=0;j<nColunas;j++){
            esquinas[i*nColunas+j]->indice_vertice_c=j+1;
            esquinas[i*nColunas+j]->indice_vertice_l=i+1;
        }
    }
    

    for(i=0;i<nLinhas;i++){
        for(j=0;j<nColunas;j++){
            f1=0;
            f2=0;
            f3=0;
            for(k=0;k<4;k++){
                if(esquinas[i*nColunas+j]->indice_vertice_l-1 && !f1){
                    esquinas[i*nColunas+j]->arestas[k]=can_fail_malloc(sizeof(aresta));
                    esquinas[i*nColunas+j]->arestas[k]->vertex=esquinas[(i*nColunas)+j-nColunas];
                    esquinas[i*nColunas+j]->arestas[k]->capacity=1;
                    f1++;
                }
                else if(esquinas[i*nColunas+j]->indice_vertice_c-1 && !f2){
                    esquinas[i*nColunas+j]->arestas[k]=can_fail_malloc(sizeof(aresta));
                    esquinas[i*nColunas+j]->arestas[k]->vertex=esquinas[i*nColunas+j-1];
                    esquinas[i*nColunas+j]->arestas[k]->capacity=1;
                    f2++;
                }
                else if((esquinas[i*nColunas+j]->indice_vertice_l+1)<=nLinhas && !f3){
                    esquinas[i*nColunas+j]->arestas[k]=can_fail_malloc(sizeof(aresta));
                    esquinas[i*nColunas+j]->arestas[k]->vertex=esquinas[i*nColunas+j+nColunas];
                    esquinas[i*nColunas+j]->arestas[k]->capacity=1;
                    f3++;
                }
                else if((esquinas[i*nColunas+j]->indice_vertice_c+1)<=nColunas){
                    esquinas[i*nColunas+j]->arestas[k]=can_fail_malloc(sizeof(aresta));
                    esquinas[i*nColunas+j]->arestas[k]->vertex=esquinas[i*nColunas+j+1];
                    esquinas[i*nColunas+j]->arestas[k]->capacity=1;
                    break;
                }   
            }
        }
    }
}



int Edmonds_Karp(vertice* source){
    int i,front=0,back=0;
    vertice *current;
    vertice **fila;
    fila=(vertice**)can_fail_malloc(sizeof(vertice*)*nVertices);
    source->visited=1;
    fila[back]=source;
    back++;
    while(front!=back){
        current=fila[front];
        front++;
        for(i=0;i<4;i++){
            if(current->arestas[i]!=NULL && current->arestas[i]->capacity && !(current->arestas[i]->vertex->visited) && current->arestas[i]->vertex->capacidade){
                if(current->arestas[i]->vertex->market){
                    current->arestas[i]->capacity=0;
                    current->arestas[i]->vertex->capacidade=0;
                    while((current->indice_vertice_c != source->indice_vertice_c) || (current->indice_vertice_l != source->indice_vertice_l)) {
                        current->anterior->capacity=0;
                        current=current->anterior_vertice;
                    }
                    return 1;
                }

                if(!(current->arestas[i]->vertex->visited)){
                    current->arestas[i]->vertex->visited=1;
                    current->arestas[i]->vertex->anterior=current->arestas[i];
                    current->arestas[i]->vertex->anterior_vertice=current;
                }
                
                fila[back]=current->arestas[i]->vertex;
                back++;
            }
        }
    }
    return 0;
}



int main(){
    int i=0,j=0,k=0,h=0,n=0,coluna,linha,max_flow=0;
    
    scanf("%d %d", &nColunas, &nLinhas);
    scanf("%d %d", &nMarkets, &nCitizens);


    nVertices=nColunas*nLinhas;
    esquinas=(vertice**)can_fail_malloc(sizeof(vertice*)*nVertices);
    

    while(h<nVertices){
        esquinas[h]=can_fail_malloc(sizeof(vertice));
        esquinas[h]->indice_vertice_l=0;
        esquinas[h]->indice_vertice_c=0;
        esquinas[h]->market=0;
        esquinas[h]->visited=0;
        esquinas[h]->capacidade=1;
        esquinas[h]->anterior=can_fail_malloc(sizeof(aresta));
        esquinas[h]->anterior_vertice=can_fail_malloc(sizeof(vertice));
        esquinas[h]->anterior_vertice=NULL;
        esquinas[h]->arestas=(aresta**)can_fail_malloc(sizeof(aresta*)*4);
        for(i=0;i<4;i++){
            esquinas[h]->arestas[i]=can_fail_malloc(sizeof(aresta));
            esquinas[h]->arestas[i]=NULL;
        }
        h++;
    }
    
    citizens=(vertice**)can_fail_malloc(sizeof(vertice*)*nCitizens);

    Initialize_Graph();
    
    for(i=0;i<nMarkets;i++){
        scanf("%d %d", &coluna, &linha);
        esquinas[((linha-1)*nColunas)+(coluna-1)]->market=1;
    }

    while(n<nCitizens){
        scanf("%d %d", &coluna, &linha);
        for(k=0;k<n;k++){
            if(coluna==citizens[k]->indice_vertice_c && linha==citizens[k]->indice_vertice_l){
                nCitizens--;
                break;
            }
        }
        if(k==n){
            citizens[n]=can_fail_malloc(sizeof(vertice));
            citizens[n]=esquinas[((linha-1)*nColunas)+(coluna-1)];
            n++;
        }
    }


    while(j<nCitizens){
        if(citizens[j]->market && citizens[j]->capacidade){ /*unica alteracao ao 2.5*/
            max_flow++;
            citizens[j]->capacidade=0;
        }    
        else{
            max_flow= max_flow + Edmonds_Karp(citizens[j]);
            for(i=0;i<nVertices;i++){
                esquinas[i]->visited=0;
                esquinas[i]->anterior_vertice=NULL;
            }
        }
        j++;
    }

    printf("%d\n",max_flow);
    
    return 0;   
}