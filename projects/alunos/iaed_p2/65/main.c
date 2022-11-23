#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_lists.h"
#include "hashtables.h"

/*Dimensao maxima das strings dos nomes de jogos e equipas*/
#define MAXSIZE 1024

/*Dimensao das hashtables de jogos e equipas, e modulo das hashes*/
#define HTSIZE 7919

#define INC 1
#define DEC -1

void add_game(int, nodeGame *[], nodeTeam *[], indexNode **, int *, int *);
void list_all(int, nodeGame * [], indexNode *, int, int);
void copy_addr_games(Game **, nodeGame * [], indexNode *);
void copy_addr_g(Game **, nodeGame *);
void search_game(int, nodeGame * []);
void del_game(int, nodeGame * [], nodeTeam * [], int *);
void edit_score(int, nodeGame * [], nodeTeam * []);
void add_team(int, nodeTeam * [], indexNode **, int *);
void search_team(int, nodeTeam * []);
void list_winners(int, nodeTeam * [], indexNode * , int);
int copy_addr_teams(Team * [], nodeTeam * [], indexNode *);
void copy_addr_t(int *, Team * [], nodeTeam *, int *);
int not_in_list_t(int, char *, Team **);
int compare(const void *, const void *);
int compare_indexNodes(indexNode *, indexNode *);
void change_win(int, int, nodeGame *, nodeTeam * [], int);



int main(void){

    /*current_g eh o numero de jogos no sistema
    total_g eh o numero total de jogos ja inseridos*/
    /*t eh o numero total de equipas no sistema*/
    int command, i, total_g = 0, current_g = 0, t = 0, NL = 1;

    /*hashtables para jogos e equipas*/
    nodeGame * games_ht[HTSIZE];
    nodeTeam * teams_ht[HTSIZE];

    /*listas que armazenam as posicoes das hashtables
    que estao ocupadas*/
    indexNode * index_games, * index_teams;

    /*incializa*/
    for(i = 0; i < HTSIZE; i++){
        games_ht[i] = NULL;
        teams_ht[i] = NULL;
    }

    /*incializa as listas*/
    index_games = NULL;
    index_teams = NULL;

    /*recolhe a primeira letra dos comandos ate terminar
    ao receber 'x'*/
    while((command = getchar())!='x'){


        switch(command){

                case 'a':
                    add_game(NL, games_ht, teams_ht, &index_games, &total_g, &current_g);
                    NL++;
                    break;
                
                case 'l':
                    list_all(NL, games_ht, index_games, current_g, total_g);
                    NL++;
                    break;
                
                case 'p':
                    search_game(NL, games_ht);
                    NL++;
                    break;

                case 'r':
                    del_game(NL, games_ht, teams_ht, &current_g);
                    NL++;
                    break;
                
                case 's':
                    edit_score(NL, games_ht, teams_ht);
                    NL++;
                    break;
                
                case 'A':
                    add_team(NL, teams_ht, &index_teams, &t);
                    NL++;
                    break;
                
                case 'P':
                    search_team(NL, teams_ht);
                    NL++;
                    break;
                
                case 'g':
                    list_winners(NL, teams_ht, index_teams, t);
                    NL++;
                    break;

            }


    }
    /*free da memoria alocada para a ht de jogos*/
    destroy_games_ht(games_ht, index_games);

    /*free da memoria alocada para a ht de equipas*/
    destroy_teams_ht(teams_ht, index_teams);

    /*free das listas de index*/
    _destroy_list_(index_games);
    _destroy_list_(index_teams);

    return 0;
}



/*-------------------------commands----------------------------*/



/*------------a-------------*/
/* Adiciona um novo jogo ao sistema desde que ele ainda nao exista 
e que existam as equipas envolvidas */
void add_game(int NL, nodeGame * games_ht[], nodeTeam * teams_ht[],
            indexNode ** index_games, int * total_g, int * current_g){

    char game_name[MAXSIZE], team1_name[MAXSIZE], team2_name[MAXSIZE];
    int score1, score2;
    nodeTeam * team1_addr, * team2_addr;
    nodeGame * game_addr;
    
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", game_name, team1_name, team2_name,
                                                    &score1, &score2);
    
    /*verifica se as equipas e o jogo ja existem e armazena
    a posicao em memoria*/
    team1_addr = search_team_ht(teams_ht, team1_name, HTSIZE);
    team2_addr = search_team_ht(teams_ht, team2_name, HTSIZE);
    game_addr = search_game_ht(games_ht, game_name, HTSIZE);

    if(game_addr!=NULL){

        printf("%d Jogo existente.\n", NL);

    }else if(team1_addr == NULL || team2_addr == NULL){

        printf("%d Equipa inexistente.\n", NL);

    }else{

        /*armazena o jogo*/
        add_game_ht(games_ht, index_games, game_name, *total_g, score1, score2,
        team1_name, team2_name, HTSIZE);
        game_addr = search_game_ht(games_ht, game_name, HTSIZE);

        /*incrementa as vitorias da equipa vencedora*/
        change_win(score1, score2, game_addr, teams_ht, INC);
        (*current_g)++;
        (*total_g)++;
    }


}



/*-------------l------------*/
/* Imprime no ecra todos os jogos guardados no sistema por
ordem de adicao */
void list_all(int NL, nodeGame * games_ht[], indexNode * index_games, 
                int current_g, int total_g){
    
    Game ** games_played;
    int i, j;

    /*Se o numero de jogos atual no sistema for nulo
    nao imprime nada no ecra*/
    if(current_g==0)
        return;

    /*Em games_played armazena se todos os jogos do sistema*/
    games_played = (Game **) can_fail_malloc(sizeof(Game *)*total_g);

    for(j = 0; j < total_g; j++){
        games_played[j] = NULL;
    }

    /*copia os jogos da hashtable para games_played, colocando_os 
    ja por ordem de id*/
    copy_addr_games(games_played, games_ht, index_games);

    /*imprime cada jogo da lista ignorando os espacos vazios*/
    for(i = 0; i < total_g; i++){
        print_game(NL, games_played[i]);
    }

    free(games_played);
    
}

/* Em cada iteracao recolhe uma das posicoes guardadas em index_games
e chama a funcao que guardara os jogos em games_played */
void copy_addr_games(Game ** games_played, nodeGame * games_ht[], indexNode * index_games){
    
    while(index_games != NULL){
        copy_addr_g(games_played, games_ht[index_games->s]);
        index_games = index_games->next;
    }

}

/* Itera por games_list, um encadeamento da ht dos jogos, e 
copia os jogos para games_played*/
void copy_addr_g(Game ** games_played, nodeGame * games_list){

    while(games_list != NULL){

        games_played[games_list->game->id] = games_list->game;
        games_list = games_list->next;

    }

}





/*-----------p--------------*/
/* Imprime a informacao de um jogo designado pelo nome
desde que exista no sistema */
void search_game(int NL, nodeGame * games_ht[]){

    nodeGame * addr;
    char game_name[MAXSIZE];

    scanf(" %[^:\n]", game_name);

    /*recolhe o endereco do jogo se ele existir*/
    addr = search_game_ht(games_ht, game_name, HTSIZE);
    if(addr == NULL){
        printf("%d Jogo inexistente.\n", NL);
    }else{
        print_game(NL, addr->game);
    }

}





/*------------r--------------*/
/* Elimina um jogo cujo nome eh indicado desde que ele exista */
void del_game(int NL, nodeGame * games_ht[], nodeTeam * teams_ht[], int * current_g){

    nodeGame * game_addr;
    char game_name[MAXSIZE];
    int score1, score2;

    scanf(" %[^:\n]", game_name);

    game_addr = search_game_ht(games_ht, game_name, HTSIZE);

    if(game_addr == NULL){

        printf("%d Jogo inexistente.\n", NL);

    }else{

        score1 = game_addr->game->score1;
        score2 = game_addr->game->score2;

        /*caso o jogo fosse uma vitoria decrementa uma vitoria
        da equipa vencedora*/
        change_win(score1, score2, game_addr, teams_ht, DEC);

        /*elimina o jogo da hashtable*/
        del_game_ht(games_ht, game_name, HTSIZE);

        (*current_g)--;

    }

}





/*-------------s--------------*/
/* Edita o resultado de um jogo desde que ele exista no sistema */
void edit_score(int NL, nodeGame * games_ht[], nodeTeam * teams_ht[]){

    nodeGame * game_addr;
    char game_name[MAXSIZE];
    int score1, score2, new_score1, new_score2;

    scanf(" %[^:\n]:%d:%d", game_name, &new_score1, &new_score2);

    /*obtem o endereco do jogo se ele existir*/
    game_addr = search_game_ht(games_ht, game_name, HTSIZE);

    if(game_addr == NULL){

        printf("%d Jogo inexistente.\n", NL);

    }else{

        score1 = game_addr->game->score1;
        score2 = game_addr->game->score2;

        /*anula a vitoria do resultado anterior*/
        change_win(score1, score2, game_addr, teams_ht, DEC);

        /*adiciona uma vitoria se houver uma equipa vencedora
        no novo resultado*/
        change_win(new_score1, new_score2, game_addr, teams_ht, INC);

        game_addr->game->score1 = new_score1;
        game_addr->game->score2 = new_score2;
    
    }


}





/*------------A--------------*/
/* Adiciona uma nova equipa ao sistema se ela ainda nao existir */
void add_team(int NL, nodeTeam * teams_ht[], indexNode ** index_teams, int * t){

    nodeTeam * team_addr;
    char team_name[MAXSIZE];
    scanf(" %[^:\n]", team_name);

    team_addr = search_team_ht(teams_ht, team_name, HTSIZE);

    if(team_addr != NULL){
        
        printf("%d Equipa existente.\n", NL);

    }else{
        /*adiciona a nova equipa na hashtable*/
        add_team_ht(teams_ht, index_teams, team_name, HTSIZE);
        (*t)++;

    }

}





/*-------------P------------*/
/* Imprime no ecra a informacao relativa a uma equipa desde que ela exista */
void search_team(int NL, nodeTeam * teams_ht[]){

    nodeTeam * team_addr;
    char team_name[MAXSIZE];
    scanf(" %[^:\n]", team_name);

    team_addr = search_team_ht(teams_ht, team_name, HTSIZE);

    if(team_addr == NULL){

        printf("%d Equipa inexistente.\n", NL);

    }else{
        
        /*print do nome e vitorias da equipa*/
        print_team(NL, team_addr->team);
    
    }

}





/*--------------g------------*/
/* Imprime no ecra as equipas com mais vitorias por ordem lexicografica*/
void list_winners(int NL, nodeTeam * teams_ht[], indexNode * index_teams, int t){

    Team ** teams; 
    int i, j, length;

    /*caso nao haja equipas no sistema a funcao nao faz nada*/
    if(t == 0) return;

    /*aloca memoria suficiente para uma situcao em que todas as
    equipas tem o mesmo numero de vitorias*/
    teams = (Team ** ) can_fail_malloc(sizeof(Team *) * t);

    for(i = 0; i < t; i++){
        teams[i]= NULL;
    }

    /*copia para teams as equipas que contem o maior numero de vitorias
    e retorna o total de equipas com essas vitorias*/
    length = copy_addr_teams(teams, teams_ht, index_teams);

    /*ordena as equipas por ordem lexicografica*/
    qsort(teams, length, sizeof(Team *), compare);

    printf("%d Melhores %d\n", NL, teams[0]->wins);
    
    /*so se faz print ate a posicao length porque a partir dai a tabela
    tem garbage values, NULL ou equipas com menos vitorias*/
    for(j = 0; j < length; j++){
        printf("%d * %s\n", NL, teams[j]->name);
    }

    free(teams);
}

/* Para cada posicao de index_teams na ht das equipas copia as equipas
com o maximo de vitorias, e retorna o total de equipas copiadas */
int copy_addr_teams(Team ** teams, nodeTeam * teams_ht[], indexNode * index_teams){
    
    int acc = 0, most_wins = 0;

    while(index_teams != NULL){
        copy_addr_t(&acc, teams, teams_ht[index_teams->s], &most_wins);
        index_teams = index_teams->next;
    }
    
    return acc;
}

/* copia para teams as equipas de teams_list com o maximo de vitorias
e armazena o numero de equipas(acc)*/
void copy_addr_t(int * acc, Team ** teams, nodeTeam * teams_list, int * wins){

    while(teams_list != NULL){

        /*verifica que o numero de vitorias eh igual ao max e que a equipa
        ainda nao foi guardada*/
        if(teams_list->team->wins == *wins && not_in_list_t(*acc, teams_list->team->name, teams)){

            teams[*acc]  = teams_list->team;
            (*acc)++;

        /*caso a equipa tenha maior numero de vitorias que o atual max
        faz se um reset de teams, recomecando se a guardar a partir da posicao 0*/
        }else if(teams_list->team->wins > *wins){

            *acc = 0;
            teams[*acc] = teams_list->team;
            *wins = teams_list->team->wins;
            (*acc)++;

        }
        teams_list = teams_list->next;
        
    }

}

/* Retorna 1 se uma equipa de nome team_name nao se encontra em teams,
e retorna 0 em caso contrario*/
int not_in_list_t(int boundary, char * team_name, Team ** teams){
    int i;
    for(i = 0; i < boundary; i++){
        if(strcmp(team_name, teams[i]->name)==0)
            return 0;
    }
    return 1;
}

/*funcao de comparacao lexicografica do qsort*/
int compare(const void * team1, const void * team2){

    const Team *t1 = *(const Team **)team1;
    const Team *t2 = *(const Team **)team2;

    return strcmp(t1->name, t2->name);
}







/*-------------auxiliary------------*/
/* Para a equipa vencedora consoante os scores alterara o numero de vitorias
incrementando_as ou decrementando_as*/
void change_win(int score1, int score2, nodeGame * game_addr, nodeTeam * teams_ht[], int value){

    nodeTeam * winner_addr;

    if(score1 > score2){

        /*equipa1 vencedora*/
        winner_addr = search_team_ht(teams_ht, game_addr->game->team1, HTSIZE);
        change_wins_directly(winner_addr, value);

    }else if(score2 > score1){

        /*equipa2 vencedora*/
        winner_addr = search_team_ht(teams_ht, game_addr->game->team2, HTSIZE);
        change_wins_directly(winner_addr, value);

    }

}
