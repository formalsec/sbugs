#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
typedef struct Lig{
    int weight;
    int des;
    int flow;
    struct Lig* reverse;
    struct Lig* next;
}Lig;

typedef struct Listlig{
    int local;
    struct Listlig* next;
}Listlig;
typedef struct Listligarch{
    int des;
    int ori;
    struct Listligarch* next;
}Listligarch;
void cria_listlig(int local,Listlig* head){
  
    Listlig* v=(Listlig*) malloc (sizeof(Listlig));
    v->local=local;
  
    if(head->next==NULL){
        head->next=v;
        return;
    }
  
    Listlig* last;
    Listlig* current= head;
    last=head;
    while(current->next != NULL && current->local< local){
        last=current;
        current=current->next;
    }
    if(current->local > local){
        v->next=last->next;
        last->next = v;
    }
    else {
        last->next->next=v;
    }
}
void cria_listligarch(int des,int ori,Listligarch* head){
  
    Listligarch* v=(Listligarch*) malloc (sizeof(Listligarch));
    v->des=des;
    v->ori=ori;
  
    if(head->next==NULL){
        head->next=v;
        return;
    }
    Listligarch* last;
    Listligarch* current= head;
    last=head;
    while(current->next != NULL && current->ori< ori){
        last=current;
        current=current->next;
    }
    if(v->ori==current->ori){
        while(current->next != NULL && current->des< des){
            last=current;
            current=current->next;
        }
    }
    if(current->ori > ori || current->des>des){
        v->next=last->next;
        last->next = v;
    }
    else{
        last->next->next=v;
    }
}
struct Lig* cria_lig(int weight, int des, int flow,Lig* firstOfvector,int nlig){
    if(nlig == 1){
        firstOfvector->weight=weight;
        firstOfvector->des=des;
        firstOfvector->flow=flow;
        firstOfvector->next=NULL;
        return firstOfvector;
    }
    Lig* v=(Lig*) malloc (sizeof(Lig));
    v->weight=weight;
    v->des=des;
    v->flow=flow;
    v->next=NULL;
    Lig* last;
    last=firstOfvector;
    while(last->next != NULL)
    {
        last=last->next;
    }
    last->next = v;
    return v;
}
void moveParaPri(Listlig* anterior,Listlig* current,Listlig* v){
    if(anterior==NULL){
        return;
    }
    anterior->next=current->next;
    current->next=v;

}
void push(int* vectorflow, Lig* lig_origem,int vector_ori){
    int deferenca;
    if(vectorflow[vector_ori-1]<lig_origem->weight - lig_origem->flow){
        deferenca=vectorflow[vector_ori-1];
    }
    else{
        deferenca = lig_origem->weight - lig_origem->flow;
    }
    lig_origem->flow = lig_origem->flow + deferenca;
    lig_origem->reverse->flow = -lig_origem->flow;
    vectorflow[vector_ori-1] -= deferenca;
    vectorflow[lig_origem->des-1] += deferenca;
}
void relable(Lig* matriz,int* hights,int u){
    Lig *v= &matriz[u-1];
    int min= INT_MAX;
    while(v!=NULL){
        if (0 < (v->weight - v->flow)){
            if(min>hights[v->des-1]){
                min=hights[v->des-1];
            }
        }
        v= v->next;
    }
    hights[u-1]=1+min;
}
void discharge(Lig* matriz,int* hights,int *vectorflow ,int u){
    Lig *v= &matriz[u-1];

    while(vectorflow[u-1]>0){
        if(v == NULL){

            relable(matriz,hights,u);
            v= &matriz[u-1];
        }
        if(0 < (v->weight - v->flow) && hights[u-1]>hights[ v->des - 1]){
            push(vectorflow,v,u);
        }
        else{
            v= v->next;
        }
    }
}
void relabel_to_front(Lig* matriz,int* vnlig,int Nparagens,int* vectorflow, int* hights){
    int i;
    int oldhight;
    Listlig* v;
    Listlig *current =(Listlig*) malloc (sizeof(Listlig));
    Listlig *head= current;
    current->local=2;
 
    /*cria a Linked list*/
    for(i=1; i<Nparagens-2 ;i++){
        v=(Listlig*) malloc (sizeof(Listlig));
        v->local=i+2;
        current->next= v;
        current= current->next;
    }
    current=head;
    Listlig *anterior=NULL;

    while(current != NULL){
        oldhight=hights[current->local-1];

        discharge(matriz,hights,vectorflow,current->local);
        if(hights[current->local-1]>oldhight){
            v=head;
            head=current;
            moveParaPri(anterior,current,v);
        }
      
        anterior=current;
        current=current->next;
    }
    /*fix me add free*/;
}
void DFSvisiter(Lig* matriz,int u,Listlig* estacoes,Listligarch* archos,int* visitado,int NFornec,int NEstAbast){
    visitado[u-1]=1;
    Lig* j=&matriz[u-1];
    if(u!= matriz[1].des){
        while(j!=NULL){
            if(j->des == matriz[1].des && visitado[j->des -1]==0)
                 DFSvisiter(matriz,j->des,estacoes,archos,visitado,NFornec,NEstAbast);
            else{
                if(j->reverse->weight - j->reverse->flow==0 && j->flow < 0 && visitado[j->des -1]==0){
                }
                else {
                    if(visitado[j->des -1]==0 && j->flow < 0){
                        DFSvisiter(matriz,j->des,estacoes,archos,visitado,NFornec,NEstAbast);
                    }
                }
            }    
            j= j->next;
        }
    }
}
/*faz um dfs desde o sink para emcontrar o curte*/
void Cutter(Lig* matriz,int Nparagens,Listlig* estacoes,Listligarch* archos,int NFornec,int NEstAbast, int* visitado){
    Lig* j= &matriz[0];
    /*lembrar todos os que saiem do sink sao necessariamente reverses*/
    while(j!=NULL){
        if(j->des == matriz[1].des || j->reverse->weight - j->reverse->flow!=0){
            if(visitado[j->des -1]==0){
                DFSvisiter(matriz,j->des,estacoes,archos,visitado,NFornec,NEstAbast);
            }
        }
        j= j->next;
    }
}

int main()
{
    int NFornec;
    int NEstAbast;
    int NLig;
    int i,j;
    int ConOrigin,ConDes,ConWeight;
    scanf("%d %d %d\n", &NFornec,&NEstAbast,&NLig);
    int PesosFornecedores;
    int PesosEstacoes;
    int NDados=NFornec+NEstAbast+1;
    /*cria uma matriz com super source(o ultimo da lista) e extra estacoes de paragens (numeros superioes a soma dos dados
    ate ao penultimo) para transformar o flow com vertices pesados nom flow normal com uma so source*/
    int Nparagens=NFornec+2*NEstAbast+2;
    Lig matriz[Nparagens];
    int hights[Nparagens];
    int vectorflow[Nparagens];
    int visitado[Nparagens];
    int* vnlig;
    Lig* u;
    Lig* v;
    Listlig* estacoes=(Listlig*) malloc (sizeof(Listlig));
    Listligarch* archos=(Listligarch*) malloc (sizeof(Listligarch));
    vnlig=(int*) malloc (Nparagens*sizeof(int));
    for(i=0;i<Nparagens;i++)
        vnlig[i]=0;   
     
    /*prenche a matriz prod*/
    i=0;
    if(NFornec>1){
        for(;i<NFornec-1;i++){
            vnlig[Nparagens-1]++;
            scanf("%d ",&PesosFornecedores);
            v = cria_lig(PesosFornecedores,i+2,PesosFornecedores,&matriz[Nparagens-1],vnlig[Nparagens-1]);
            vnlig[i+1]++;
            u = cria_lig(0,Nparagens,-PesosFornecedores,&matriz[i+1],vnlig[i+1]);
            v->reverse = u;
            u->reverse = v;
        }
    }
    vnlig[Nparagens-1]++;
    scanf("%d\n",&PesosFornecedores);
    v = cria_lig(PesosFornecedores,i+2,PesosFornecedores,&matriz[Nparagens-1],vnlig[Nparagens-1]);
    vnlig[i+1]++;
    u = cria_lig(0,Nparagens,-PesosFornecedores,&matriz[i+1],vnlig[i+1]);
    v->reverse = u;
    u->reverse = v;
 
    /*prenche a matriz est*/
    i=0;
    if(NEstAbast>1){
        for(;i<NEstAbast - 1;i++){
            scanf("%d ",&PesosEstacoes);
            vnlig[i+NDados]++;
            u=cria_lig(PesosEstacoes,i+2+NFornec,0,&matriz[i+NDados],vnlig[i+NDados]);
            vnlig[i+NFornec+1]++;
            v=cria_lig(0,i+NDados+1,0,&matriz[i+NFornec+1],vnlig[i+NFornec+1]);
            v->reverse = u;
            u->reverse = v;
        }
    }
 
    scanf("%d\n",&PesosEstacoes);
    vnlig[i+NDados]++;
    u=cria_lig(PesosEstacoes,i+2+NFornec,0,&matriz[i+NDados],vnlig[i+NDados]);
    vnlig[i+NFornec+1]++;
    v=cria_lig(0,i+NDados+1,0,&matriz[i+NFornec+1],vnlig[i+NFornec+1]);
    v->reverse = u;
    u->reverse = v;
    /*preenche a matriz com o id da paragem e o peso limite da ligacao*/
    for(i=0;i<NLig;i++){
        scanf("%d %d %d\n", &ConOrigin,&ConDes,&ConWeight);
        if(ConDes>NFornec+1){
            ConDes=ConDes+NEstAbast;
        }
        vnlig[ConOrigin-1]++;
        v=cria_lig(ConWeight,ConDes,0,&matriz[ConOrigin-1],vnlig[ConOrigin-1]);
        vnlig[ConDes-1]++;
        u=cria_lig(0,ConOrigin,0,&matriz[ConDes-1],vnlig[ConDes-1]);
        v->reverse = u;
        u->reverse = v;
    }

    /*inicia hights e vector flow*/
    for(i=0;i<Nparagens-1;i++){
        vectorflow[i]=0;
        hights[i]=0;
    }
 
    vectorflow[Nparagens-1]=0;
    hights[Nparagens-1]=Nparagens;
  
    for(i=1;i<=vnlig[Nparagens-1];i++){
        vectorflow[i]= -matriz[i].flow;
    }

    /*comessa push relable*/
    relabel_to_front(matriz,vnlig,Nparagens,vectorflow, hights);
 
    printf("%d\n",vectorflow[0]);
    /*faz o curte minimo da red residual a partir do sink e cria duas linked lists(ordenadas) uma para os arcos outra para as estacoes*/
    visitado[0]=1;
    for(i=1;i<Nparagens;i++){
        visitado[i]=0;
    }
    visitado[Nparagens-1]=0;
    Listlig* m=estacoes;
    Listligarch* n=archos;
    Listlig* lastm=estacoes;
    Listligarch* lastn=archos;
    Cutter(matriz,Nparagens,estacoes,archos,NFornec,NEstAbast, visitado);
    for(i=0;i<Nparagens-1;i++){
        if(visitado[i]==1){
        v = &matriz[i];
            for(j=0;j<vnlig[i];j++){
                if(visitado[v->des-1]==0){
                    if(i>NFornec && i < NDados){
                        cria_listlig(i+1,estacoes);
                    }       
                    else{
                        cria_listligarch(i+1, v->des, archos);
                    }
                }
                v=v->next;
            }
        }
    }
    /*percorre as Linked listes libertando(free) o termo atriour e escrevendo o termo atual*/
    if(estacoes->next!=NULL){
        while(m->next->next!=NULL){
            printf("%d ",m->next->local);
            lastm=m;
            m=m->next;
            free(lastm);
        }
        printf("%d\n",m->next->local);
        lastm=m;
        m=m->next;
        free(lastm);
        free(m);
    }
    else{
        free(estacoes);
        printf("\n");
    }
    if(n->next!=NULL){
        while(n->next->next!=NULL){
            printf("%d %d\n",n->next->ori,n->next->des);
            lastn=n;
            n=n->next;
            free(lastn);
        }
        printf("%d %d\n",n->next->ori,n->next->des);
        lastn=n;
        n=n->next;
        free(lastn);
        free(n);
    }
    else{
        free(archos);
    }
    /*faz free de todo e acaba*/
    for (i = 0; i < Nparagens; i++){
        u=matriz[i].next;
        while(u!=NULL){
            v=u;
            u=u->next;
            free(v);
        }
    }
    free(vnlig);
    return 0;
}