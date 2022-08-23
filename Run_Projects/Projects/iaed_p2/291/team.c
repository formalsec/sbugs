#include "team.h"
#include "default.h"

void add_team(link *teams,char buffer[1024]){ /* adiciona uma equipa a link *teams */
    link aux;
    aux = malloc(sizeof(struct node));
    aux->name = malloc(sizeof(char)*(strlen(buffer)+1));    /*aloca apenas a memoria necessaria*/
    strcpy(aux->name, buffer);
    aux->next = teams[hashU(buffer)];   
    teams[hashU(buffer)] = aux;     /*acrescenta o termo antes do primeiro termo*/
    /*print_teams(teams);
    printf("\n\n");*/
    return;
}

void print_teams(link* teams){      /* escreve todas as equipas existentes, usada para debug */
    int i;
    link aux;
    for(i=0;i<M;i++){
        if(teams[i]==NULL)
            printf("Equipa %d: vazia\n", i);
        else{
            aux = teams[i];
            printf("Equipa %d", i);
            while(aux != NULL){
                printf(":-:%s", aux->name);
                aux = aux->next;
            }
            printf("\n");
        }
    }
    return;
}

int find(link *teams, char buffer[1024],int contador){  /*funcao que indica se encontrou(dai ser int) e escreve o nome da equipa encontrada*/
    link aux;
    aux = teams[hashU(buffer)];

    while(aux != NULL){ 
        if(strcmp(aux->name, buffer)){      /*verifica todos os nomes das equipas*/
            aux = aux->next;
        }

        else{                   /*se encontrou escreve o nome da equipa e diz que encontrou*/
            printf("%d %s ",contador , aux->name);
            return 0;
        }
    }
    printf("%d Equipa inexistente.\n", contador);   /* se nao encontrou escreve que a equipa nao existe e diz que nao encontrou */
    return 1;
}

int existing_team(link *hashtable,char buffer[1024]){   /* verifica se uma equipa existe */
    link aux;       
    aux = hashtable[hashU(buffer)];
    while(aux != NULL){
        if(strcmp(aux->name, buffer)){  /*verifica todos as equipas*/
            aux = aux->next;
        }
        else{
            return 1;       /*equipa existe*/
        }
    }
    return 0;       /*equipa nao existe*/
}

void free_list(link *teams){  /* da free a toda a memoria de uma lista de links */
    int i;
    link aux, aux2;
    for(i=0;i<M;i++){
        aux = teams[i];
        aux2 = teams[i];
        while(aux2 != NULL){
            aux = aux2;
            aux2 = aux->next;
            free_node(aux);
        }
    }
    return;
}

void free_node(link n){
    free(n->name);
    free(n);
    return;
}
