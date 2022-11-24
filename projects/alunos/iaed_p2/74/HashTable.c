#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "HashTable.h"

static games *g;
static pTeam *t;

int unsigned hash(char *name,int tamanho){
    int unsigned hash_value=0;
    long lenght = strlen(name);
    int i;
    for(i=0;i<lenght;i++){
        hash_value = hash_value * 251 + name[i]; /*multiplicar por um numero primo para dispersar mais a tabela*/
    }
    return (hash_value % tamanho);
}

void Ginit(){
    int i;
    g = (games*)can_fail_malloc(sizeof(games)*TAM_G);
    for(i = 0; i < TAM_G; i++) g[i] = NULL;
    }


void Ginsert(char *name, char *t1, char *t2, int s1, int s2) {
        int key = hash(name,TAM_G);
        games newNode = can_fail_malloc(sizeof(struct node));
    
        newNode->game_name = stringdup(name);
        newNode->team1= stringdup(t1);
        newNode->team2 = stringdup(t2);
        newNode->score1=s1;
        newNode->score2=s2;
        newNode->next = NULL;
    
        /*ve se o g[key] esta nulo*/
        if(g[key] == NULL)
            g[key] = newNode;
        /*se houver colisao*/
        else
        {
            /*adionar um node no fim de g[key].*/
            games temp = g[key];
            while(temp->next)
            {
                temp = temp->next;
            }

            temp->next = newNode;
        }
    }


games Gsearch(char *name){

        int key = hash(name,TAM_G) ;
        games temp = g[key];
        while(temp)
        {
            if(strcmp(temp->game_name, name)==0)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }


void Gdelete(char *name)
    {
        int key = hash(name,TAM_G);
        games temp = g[key], dealloc,ant=g[key];
        if(strcmp(temp->game_name,name)==0){ /*quando o primeiro elemento */
            g[key]=temp->next;
            free(temp->game_name);
            free(temp->team1);
            free(temp->team2);
            free(temp);
        }
        else{
            temp=temp->next;
            while(temp)
                {
                if(strcmp(temp->game_name, name)==0)
                {
                    dealloc = temp;
                    temp = temp->next;
                    ant->next=temp;
                    free(dealloc->game_name);  /*Liberta memoria e coloca a NULL a posicao*/
                    free(dealloc->team1);
                    free(dealloc->team2);
                    free(dealloc);
                    return;
                    }
                    ant=temp;
                    temp = temp->next;
                    }
        }
    }


void Gfree_hash() /*dar free a hash table*/
    {
        int i;
            games temp,ant;
            for(i=0;i<TAM_G;i++){
                temp=g[i];
                while(temp!=NULL){
                        free(temp->game_name);
                        free(temp->team1);
                        free(temp->team2);
                        ant = temp;
                        temp = temp->next;
                        free(ant);
                    }
            }
            free(g);
            
        }

/*===============================================================================*/
                                /*Hash equipas*/
void Tinit(){
    int i;
    t = (pTeam*)can_fail_malloc(TABLE_SIZE*sizeof(pTeam));
    for (i = 0; i < TABLE_SIZE; i++)
        t[i] = NULL; /* inicializo tudo a NULL */
}

pTeam Thash(int i){
    return t[i];
}

void Tinsert(char *name){
    int i = hash(name,TABLE_SIZE);
    pTeam temp;
    while (t[i]!=NULL) i = (i+1) % TABLE_SIZE; /* ve se a posicao ja esta ocupada, estiver vai ate a proxima posicao*/
    temp = (pTeam)can_fail_malloc(sizeof(struct team));
    temp->team_name = stringdup(name);
    temp->wins = 0;
    t[i] = temp;
}

pTeam Tsearch(char *id){
    int i = hash(id,TABLE_SIZE);
    while (t[i] != NULL){
        if (strcmp(t[i]->team_name, id)==0)
            return t[i];
        else
            i = (i+1) % TABLE_SIZE;
    }
    return NULL; /*Se nao encontrar devolve NULL*/
}

int max_wins(){
    int i,wins,max_wins=0;
    for(i=0;i<TABLE_SIZE;i++){
        if(t[i]!=NULL){
            wins=t[i]->wins;
            if(wins>max_wins) max_wins=wins;
        }
    }
    return max_wins;
}

void Tfree_hash(){ /*dar free a hash table*/
    int i;
    for(i=0;i<TABLE_SIZE;i++){
        if(t[i]!=NULL){
            free(t[i]->team_name);
            free(t[i]);
        }
    }
    free(t);
}
