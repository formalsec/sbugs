#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista.h"


int key(char nome[Max]){
    int i,j=0;
    for (i=0;nome[i]!='\0';i++){
        j=nome[i]+j;
    }
    return j;
}



/*HASHTABLE DAS EQUIPAS: FUNCOES*/

equipa** init_eq(equipa** equipas,int m) {
    int i;
    for (i = 0; i<m; i++){
        equipas[i]=NULL;
    }
    return equipas;
}



equipa* insertBeginList_eq(equipa* head, char nome[Max]){
    int i;
    equipa* t; 
    t=(equipa*)malloc(sizeof(equipa));
    i=strlen(nome);
    i++;
    t->nome=(char*) malloc(sizeof(char)*i);
    strcpy(t->nome,nome);
    t->i=0;
    t->next=head;
    return t;
}



void insere_equipa(equipa** head,char nome[Max],int m){
    int i = key(nome)%m;
    head[i]=insertBeginList_eq(head [i], nome);
}


equipa* searchteam(equipa* equipas, char item[Max]){
    equipa* t;
    for (t=equipas;t!=NULL;t=t->next){
        if (strcmp(item,t->nome)==0){
            return t;
        }
    }
    return NULL;
}

equipa* encontra_equipa(equipa**equipas,char item[Max],int m) {
    int i = key(item)%m;
    return searchteam(equipas[i], item);
}


int ent_meh(equipa* head, int sc1, int*i){
    equipa* t;
    for (t=head;t!=NULL;t=t->next){
        if (t->i==sc1)
            (*i)++;
        else if (sc1<(t->i)){
            sc1=t->i;
            (*i)=1;
        }
    }
    return sc1;
}


int encontr_melhor(equipa** equipas,int m, int sc1,int* i){
    int f;
    for (f=0;f<m;f++)
        sc1=ent_meh(equipas[f],sc1,i);
    return sc1;
}

void procurar(equipa* hash, equipa**haed,int sc1,int sc2, int *i){
    equipa* t;
    for (t=hash;t!=NULL;t=t->next){
        if (t->i==sc1){
            haed[(*i)]=t;
            if ((*i)<sc2){
                (*i)++;
            }
            else
                break;
            
        }
    }
}


void proc(equipa** hash,equipa**haed,int sc1,int m,int sc2){
    int f,*i=malloc(sizeof(int));
    (*i)=0;
    for (f=0;f<m;f++){
        procurar(hash[f],haed,sc1,sc2,i);
        if (sc2==(*i))
            break;
    }
    free(i);
}




int particao(equipa**  head,int inicio,int fim)
{
    int i=inicio-1;
    int j=fim;
    equipa* v=head[fim],*aux;
    while(i<j){
        while (strcmp(head[++i]->nome,v->nome)<0);
        while (strcmp(head[--j]->nome,v->nome)>0)
            if (j==inicio)
                break;
        if (i<j){
            aux=head[i];
            head[i]=head[j];
            head[j]=aux;
        }
    }
    aux=head[i];
    head[i]=head[fim];
    head[fim]=aux;
    return i;

}

void ordena_lista(equipa** head,int inicio, int fim)
{
    int i;
    if (fim<=inicio)
        return;
    i=particao(head,inicio,fim);
    ordena_lista(head,inicio,i-1);
    ordena_lista(head,i+1,fim);
}

void end_q(equipa** equipas, int m){
    int i;
    equipa* t;
    for (i=0;i<m;i++){
        while (equipas[i]!=NULL)
        {
            free(equipas[i]->nome);
            t=equipas[i];
            equipas[i]=equipas[i]->next;
            free(t);
        }
        free(equipas[i]);
        
    }
    free(equipas);
}




/* HASHTABLES DOS JOGOS: FUNCOES*/



hash_jogo** init(hash_jogo** hash_game,int m) {
    int i;
    for (i = 0; i < m; i++){
        hash_game[i]=NULL;
    }
    return hash_game;
}


hash_jogo* insertBeginList(hash_jogo* hash_game, jogo* jog){
    hash_jogo* t= malloc(sizeof(hash_jogo));
    t->nome=jog;
    t->next=hash_game;
    return t;
}

void insere_jogo(hash_jogo **hash_game,char nome[Max],jogo* jog ,int m) {
    int i = key(nome)%m;
    hash_game[i]=insertBeginList(hash_game[i], jog);
}

hash_jogo* remove_jogo(hash_jogo* hash_game,l_jogo *l,char nome[Max], int nl){
    hash_jogo* pre=NULL,*t=hash_game;
    for (;t!=NULL;pre=t,t=t->next){
        if (strcmp(nome,t->nome->n_jogo)==0){
            if (t->nome==l->head){
                l->head=l->head->next;
            }
            else if (t->nome==l->last){
                l->last=l->last->previous;
                l->last->next=NULL;
            }
            else{
                t->nome->previous->next=t->nome->next;
                t->nome->next->previous=t->nome->previous;
            }
            free(t->nome->n_jogo);
            if (t->nome->sc1>t->nome->sc2)
                t->nome->equipa1->i--;
            else if (t->nome->sc2>t->nome->sc1)
                t->nome->equipa2->i--;
            free(t->nome);
            if (pre!=NULL){
                pre->next=t->next;
                free(t);
                return hash_game;
                }
            else{
                pre=t->next;
                free(t);
                return pre;
            }
        }
    }
    if (t==NULL)
        printf("%d Jogo inexistente.\n",nl);

    return hash_game;
}

void remo_jog(hash_jogo**hash_game,char item[Max],l_jogo *l,int m,int nl) {
    int i = key(item)%m;
    hash_game[i]=remove_jogo(hash_game[i],l,item, nl);
}

jogo* searchList(hash_jogo* hash_game, char item[Max]){
    hash_jogo *t;
    for (t=hash_game;t!=NULL;t=t->next){
        if (strcmp(item,t->nome->n_jogo)==0){
            return t->nome;
        }
    }
    return NULL;
}

jogo* encontra_jogo(hash_jogo **hash_game,char item[Max],int m) {
    int i = key(item)%m;
    return searchList(hash_game[i], item);
}

void end(hash_jogo** equipas, int m){
    int i;
    hash_jogo* t;
    for (i=0;i<m;i++){
        while (equipas[i]!=NULL)
        {
            free(equipas[i]->nome->n_jogo);
            free(equipas[i]->nome);
            t=equipas[i];
            equipas[i]=equipas[i]->next;
            free(t);
        }
        free(equipas[i]);
        
    }
    free(equipas);
}



/* LISTA DE JOGOS: FUNCOES*/


l_jogo* cria_list_jogo(l_jogo* l){
    l->head=NULL;
    l->last=NULL;
    return l;
}

void add_jogo(l_jogo* l, char jog[Max],equipa* eq1,equipa* eq2,int sc1,int sc2){
    jogo *n = malloc(sizeof(jogo));
    int e;
    e=strlen(jog);
    n->n_jogo= (char*) malloc(sizeof(char)*(e+1));
    strcpy(n->n_jogo,jog);
    n->equipa1=eq1;
    n->equipa2=eq2;
    n->sc1=sc1;
    n->sc2=sc2;
    n->next = NULL;
    n->previous = l->last;
    if (l->head == NULL){
        l->head=n;
        l->last=n;
    }
    else{
        l->last->next = n;
        l->last = n;
    }
}

void print(l_jogo *head,int nl){
    jogo *jog;
    jog=head->head;
    while (jog != NULL){
        printf("%d %s %s %s %d %d\n",nl,jog->n_jogo,jog->equipa1->nome,jog->equipa2->nome,jog->sc1,jog->sc2);
        jog = jog->next;
        }
}

