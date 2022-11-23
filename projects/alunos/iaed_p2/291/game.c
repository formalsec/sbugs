#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "default.h"
#include "team.h"
#include "game.h"

void add_game(game_link *games,char buffer[1024], char t1[1024], char t2[1024], char s1[100], char s2[100], game_list *games_sorted){
    game_link aux;          /*adiciona um jogo a lista de jogos e a lista de ponteiros de jogos ordenados*/
    game_list auxiliar;
    aux = can_fail_malloc(sizeof(struct game_node));
    
    aux->name = can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(aux->name, buffer);      /*adiciona o nome*/
    
    aux->team1 = can_fail_malloc(sizeof(char)*(strlen(t1)+1));
    strcpy(aux->team1, t1);     /*o nome da equipa 1*/
    
    aux->team2 = can_fail_malloc(sizeof(char)*(strlen(t2)+1));
    strcpy(aux->team2, t2);     /*o nome da equipa 2*/
    
    aux->score1 = atoi(s1);
    aux->score2 = atoi(s2); /*os scores*/
    
    aux->next = games[hashU(buffer)];
    games[hashU(buffer)] = aux; /*adiciona o jogo antes do primeiro termo dos jogos*/

    auxiliar = can_fail_malloc(sizeof(struct game_pointers));
    auxiliar->game = aux;
    auxiliar->next = *games_sorted;
    auxiliar->prev = NULL;  
    (*games_sorted)->prev = auxiliar;       /* adiciona a lista ordenada*/
    *games_sorted = auxiliar;
    /*print_games(games);*/
    return;
}
void print_games(game_link* games){ /* escreve todas as equipas existentes, usada para debug */
    int i;
    game_link aux;
    for(i=0;i<M;i++){
        if(games[i]==NULL)
            printf("Jogo %d: vazio\n", i);
        else{
            aux = games[i];
            printf("Jogo %d", i);
            while(aux != NULL){
                printf(":-:%s", aux->name);
                aux = aux->next;
            }
            printf("\n");
        }
    }
    return;
}

int existing_game(game_link *hashtable,char buffer[1024]){  /*verifica se um jogo existe*/
    game_link aux;
    aux = hashtable[hashU(buffer)];
    while(aux != NULL){
        if(strcmp(aux->name, buffer)){  /*verifica todos os jogos*/
            aux = aux->next;
        }
        else{
            return 1;      /*jogo existe*/
        }
    }   
    return 0;       /*jogo nao existe*/
}

game_link get_game(game_link *games,char buffer[1024]){     /*encontra um jogo com base num nome*/
    game_link aux;
    aux = games[hashU(buffer)];         /*esta funcao assume que o jogo existe por isso tem de ser usada com a existing game*/
    while(strcmp(aux->name, buffer)){
        aux = aux->next;}
    return aux;
}

game_link prev(game_link *games, game_link atual){
    game_link aux = games[hashU(atual->name)];  /* obtem o jogo anterior a outro jogo pois a lista e simplesmente ligada */
    if(!strcmp(aux->name, atual->name)){    /* nao foi usada devido a ineficiencia */
        return NULL;
    }
    while(strcmp(aux->next->name, atual->name)){
        aux = aux->next;
    }
    return aux;
}

void free_game_list(game_link *games){  /* da free a uma lista de game_link */
    int i;
    game_link aux, aux2;
    for(i=0;i<M;i++){
        aux = games[i];
        aux2 = games[i];
        while(aux2 != NULL){
            aux = aux2;
            aux2 = aux->next;
            free_game_node(aux);
        }
    }
    return;
}

void free_game_node(game_link n){   /* da free a um game_link */
    free(n->name);
    free(n->team1);
    free(n->team2);
    free(n);
    return;
}

void free_ord(game_list n){     /* da free a lista que tem ponteiros para jogos ordenados por ordem de entrada */
    game_list aux;
    if(n->game == NULL){
        free(n);
        return;
    }
    aux = n->next;
    free(n);
    free_ord(aux);
}