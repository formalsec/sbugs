#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* Grupo 126 Alameda
Beatriz Domingos 93026
ASA - Projecto 1 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct node{     
    int n;              
    struct node *next;
}*Node;

typedef struct vertice{     
    int id, low, d;
    int CFL;
    Node first, tail;       
    struct vertice *down;   
}*Vertice;


Vertice stackHead;
int *vStack;

Vertice *GruposInternos;
int visitados=0;
int grupos=0;
int notaMaior=0;
int numInternos;
int sccAtual=0;


int *initvStack(int N);

void Push(Vertice v,int *vStack);
Vertice Pop(int *vStack);

void SCC_Tarjan(Vertice *amigos, int N, int* vStack);
void Tarjan_Visit(Vertice *amigos, int casa, int *vStack);

Vertice InsFimLista(Vertice head, int newID);
Node newNode(int n);
Vertice newVertex(int id);
Vertice *novaListaDeAmigos(int N);
Vertice novaListaAdj(Vertice head, Vertice *amigos, int **Matrix, int idAmigos);
void imprimeGrafo(Vertice *amigos, int numVer);
void imprimeVertice(Vertice v);
void debugImprimeAmigos(Vertice *amigos, int lenAmigos);


int main(){

    int N, P, i, a, b;
   

    Vertice *friends; 

    if(scanf("%d %d", &N, &P)==2){};    
    friends=novaListaDeAmigos(N);       
    stackHead=(Vertice)can_fail_malloc(sizeof(struct vertice)); 
    vStack = initvStack(N);            

    for(i=0; i<P; i++){                 
        if(scanf("%d %d", &a, &b)==2){};
        InsFimLista(friends[a-1], b);   
    }

    SCC_Tarjan(friends, N, vStack);     
    printf("%d\n%d\n%d\n", grupos, notaMaior, numInternos);

    return 0;
}


void SCC_Tarjan(Vertice *amigos, int N, int* vStack){

    int i, *sccRegistados;
    Node aux;

	for (i=0;i<N;i++){
        if(amigos[i]->d==-1){   
            Tarjan_Visit(amigos, i, vStack); 
        }
	}



	sccRegistados=(int*)can_fail_malloc(sizeof(int)*grupos);
	for(i=0; i<grupos; i++){
        sccRegistados[i]=0;
	}

    for(i=0; i<N; i++){

        for(aux=amigos[i]->first; aux!=NULL; aux=aux->next){
            if(sccRegistados[amigos[i]->CFL]==0){
                if(amigos[i]->CFL != amigos[aux->n]->CFL){
                    sccRegistados[amigos[i]->CFL]=1;
                    numInternos--;
                }
            }
        }
    }
    numInternos=numInternos+grupos;
}

void Tarjan_Visit(Vertice *amigos, int casa, int *vStack){

    Vertice v = amigos[casa];

    Vertice popped;
    Node aux;

    int notaAtual;

	v->d = visitados;
	v->low = visitados;
    visitados++;

	Push(v, vStack);    

    for(aux=v->first; aux!=NULL ;aux=aux->next){
        if((amigos[(aux->n)]->d)==-1){
                Tarjan_Visit(amigos, amigos[(aux->n)]->id, vStack);
                if(amigos[(aux->n)]->low < v->low)
                    v->low= amigos[(aux->n)]->low;
        }
        else if(vStack[(aux->n)]==1){
            if(amigos[(aux->n)]->d < v->low)
                v->low= amigos[(aux->n)]->low;
            }
    }
    if(v->d == v->low){
        notaAtual=0;
        do{                

            popped = Pop(vStack);
            popped->CFL=sccAtual;
            notaAtual++;  
        }while(popped->id != v->id);

        sccAtual++;

        if(notaAtual >= notaMaior){ 
            notaMaior=notaAtual;
        }

        grupos++;

    }
}

void Push(Vertice v, int *vStack){
    v->down = stackHead; 
    stackHead = v;      
    vStack[(v->id)]=1;   
}

Vertice Pop(int* vStack){
    Vertice taken;
    if(stackHead==NULL){    
        return NULL;
    }
    taken = stackHead; 
    stackHead = stackHead->down; 
    vStack[(taken->id)]=0; 
    return taken;

}


Vertice newVertex(int id){
    Vertice v = (Vertice)can_fail_malloc(sizeof(struct vertice));
    v->id=id;
    v->low=-1;
    v->d=-1;
    v->first=NULL;
    v->tail=NULL;
    return v;
}

Node newNode(int id){
    Node novo = (Node)can_fail_malloc(sizeof(struct node));
    novo->n = id-1;
    novo->next=NULL;
    return novo;
}

Vertice *novaListaDeAmigos(int N){
    int i;
    Vertice *amigos=(Vertice*)can_fail_malloc(N*sizeof(struct vertice));

    for(i=0; i<N; i++){
        amigos[i]=newVertex(i);
    }
    return amigos;
}


Vertice InsFimLista(Vertice v, int newID){
    Node new = newNode(newID);

    if(v->tail==NULL){
        v->first=new;
        v->tail=new;
        return v;
    }

    v->tail->next = new;
    v->tail = new;
    return v;
}


int* initvStack(int N){
    int i;
    int *vet = (int*)can_fail_malloc(sizeof(int)*N);
    for(i=0; i<N; i++){
        vet[i]=0;
    }
    return vet;
}


