#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "Game_Hash.h"
#include "Team.h"
#include "Team_Hash.h"

/* ================================ COMMANDS & CONSTANTS =================================== */

#define ADD_GAME 'a'
#define LIST_GAMES 'l'
#define SEARCH_GAME 'p'
#define DEL_GAME 'r'
#define CHG_GAME 's'
#define ADD_TEAM 'A'
#define SEARCH_TEAM 'P'
#define MOST_WINS 'g'
#define END 'x'

#define MAX_NAME 1024             /* Max size of names */
#define SIZE_TEAM_HASH 13997      /* Size of Hash Table of teams */
#define SIZE_GAME_HASH 4789       /* Size of Hash Table of games */


/* ====================================== PROTOTYPES ===================================== */

lnk_dblist add_game(int nl, lnk_dblist p_auxlist, link_game* head_ghash, link_team* head_thash, char* gm_name, char* t1_name, char* t2_name, int t1_score, int t2_score);
void list_games(int nl, lnk_dblist ptr_auxlist);
void search_game(int nl, link_game* head_ghash, char* g_name);
lnk_dblist delete_game(int nl, lnk_dblist p_auxlist, link_game* head_ghash, char* g_name);
void change_game(int nl, link_game* head_ghash, char* g_name, int score_t1, int score_t2);
void add_team(int nl, link_team* head, char* name);
void search_team(int nl, link_team* head, char* name);
void most_win(int nl, int size, link_team* head);
int compare(const void* a, const void* b);

/* ====================================== MAIN ============================================= */

int main(){
    char command, game_name[MAX_NAME], team1_name[MAX_NAME], team2_name[MAX_NAME];
    int score_t1, score_t2;
    int line_nr = 0;  /* variable counts line nr for output */
    
    /* Initialize structures */
    lnk_dblist pauxlist_games = initGHash_auxList();
    link_game* phash_games = initGame_Hash(SIZE_GAME_HASH);
    link_team* phash_teams = initTeam_Hash(SIZE_TEAM_HASH);

    scanf("%c", &command);   /*Get command  */
    while (command != END){
        switch (command){
            /* Receive parameters of corresponding command */
            case ADD_GAME:
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", game_name, team1_name, team2_name, &score_t1, &score_t2);
                pauxlist_games = add_game(++line_nr, pauxlist_games, phash_games, phash_teams, game_name, team1_name, team2_name, score_t1, score_t2);
                break;
            case LIST_GAMES:
                list_games(++line_nr, pauxlist_games);
                break;
            case SEARCH_GAME:
                scanf(" %[^:\n]", game_name);
                search_game(++line_nr, phash_games, game_name);
                break;
            case DEL_GAME:
                scanf(" %[^:\n]", game_name);
                pauxlist_games = delete_game(++line_nr, pauxlist_games, phash_games, game_name);
                break;
            case CHG_GAME:
                scanf(" %[^:\n]:%d:%d", game_name, &score_t1, &score_t2);
                change_game(++line_nr, phash_games, game_name, score_t1, score_t2);
                break;
            case ADD_TEAM:
                scanf(" %[^:\n]", team1_name);
                add_team(++line_nr, phash_teams, team1_name);
                break;
            case SEARCH_TEAM:
                scanf(" %[^:\n]", team1_name);
                search_team(++line_nr, phash_teams, team1_name);
                break;
            case MOST_WINS:
                most_win(++line_nr, SIZE_TEAM_HASH, phash_teams);
                break;
        }
        scanf("%c", &command);
    }
    /* Destorying all structures */
    destroyTeam_Hash(SIZE_TEAM_HASH, phash_teams);
    destroyGame_Hash(SIZE_GAME_HASH, phash_games);
    destroyAux_List(pauxlist_games);
    return 0;
}

/* ======================================= FUNCTIONS ============================================ */

/* Function creates game and adds pointer to it in hash table of games and in auxiliary double linked list*/    
lnk_dblist add_game(int nl, lnk_dblist p_auxlist , link_game* head_ghash, link_team* head_thash, char* gm_name, char* t1_name, char* t2_name, int t1_score, int t2_score){
    
    Team* paux_team1 = searchTeam_Hash(SIZE_TEAM_HASH, head_thash, t1_name);
    Team* paux_team2 = searchTeam_Hash(SIZE_TEAM_HASH, head_thash, t2_name);
    
    if(searchGame_Hash(SIZE_GAME_HASH, head_ghash, gm_name) != NULL){                    /* Verify if game doesnt exist already */
        printf("%d Jogo existente.\n", nl);
        return p_auxlist;
    }                                           
    else if(paux_team1 == NULL || paux_team2 == NULL){                                   /* Verify that teams exist */
        printf("%d Equipa inexistente.\n", nl);
        return p_auxlist;
    }
    else{
        Game* ptr_ng = newGame(gm_name, paux_team1, paux_team2, t1_score, t2_score);
        Team* ptr_winner = who_won(ptr_ng);

        /* Both the auxiliary list and the hash table will add the same game pointer */
        insertGame_Hash(SIZE_GAME_HASH, head_ghash, ptr_ng);
        
        if (ptr_winner != NULL) change_victory(ptr_winner, WIN);                         /* Add a win to winner if not draw */
        return insrtGHash_auxList(p_auxlist, ptr_ng);                                    /* Returns pointer to head of auxiliary list */
    }
}


/* Function lists all games by order of entrance in the system */
void list_games(int nl, lnk_dblist ptr_auxlist){
    
    for(; ptr_auxlist != NULL; ptr_auxlist = ptr_auxlist -> next){ /* Run through entire double linked list */

        printf("%d %s %s %s %d %d\n", nl, ptr_auxlist->pgame->pname, ptr_auxlist->pgame->pteam1->name, 
        ptr_auxlist->pgame->pteam2->name, ptr_auxlist->pgame->score1, ptr_auxlist->pgame->score2);
    }
}


/* Function searches for game of name g_name in hash table pointed by head_ghash and lists it */
void search_game(int nl, link_game* head_ghash, char* g_name){
    Game* p_game = searchGame_Hash(SIZE_GAME_HASH, head_ghash, g_name);
    if (p_game == NULL) printf("%d Jogo inexistente.\n", nl);
    else printf ("%d %s %s %s %d %d\n", nl, p_game->pname, p_game->pteam1->name, p_game->pteam2->name, p_game->score1, p_game->score2);
}


/* Function deletes any record of game g_name, makes necessary changes to teams affected */
lnk_dblist delete_game(int nl, lnk_dblist p_auxlist, link_game* head_ghash, char* g_name){
    lnk_dblist new_head;
    Game* p_game = searchGame_Hash(SIZE_GAME_HASH, head_ghash, g_name);

    if(p_game == NULL){
        printf("%d Jogo inexistente.\n", nl);
        return p_auxlist;                                              /* Return unaltered head of auxiliary list */
    }
    else{
        Team* ptr_winner = who_won(p_game);

        if (ptr_winner != NULL) change_victory(ptr_winner, LOSS);      /* Reduce wins of winner of deleted game if there is a winner */
        /* Delete game from auxiliary list and Hash Table */
        new_head = removGHash_auxList(p_auxlist, p_game);
        deleteGame_Hash(SIZE_GAME_HASH, head_ghash, g_name);

        return new_head;                                               /* Return pointer to new head of auxiliary list */
    }
}


/* Function recieves new score and adjusts accordingly game g_name, makes necessary changes to teams affected */
void change_game(int nl, link_game* head_ghash, char* g_name, int score_t1, int score_t2){
    Game* p_game = searchGame_Hash(SIZE_GAME_HASH, head_ghash, g_name);

    if (p_game == NULL) printf("%d Jogo inexistente.\n", nl);
    else{
        Team* ptr_winner = who_won(p_game);

        if (ptr_winner != NULL){
            change_victory(ptr_winner, LOSS);                        /* If game had a winner remove win from winner */
        }
        /* Alter score of game and check new winner */
        p_game -> score1 = score_t1;
        p_game -> score2 = score_t2;
        ptr_winner = who_won(p_game);

        if (ptr_winner != NULL){
            change_victory(ptr_winner, WIN);                        /* Add win to new winner if exists */
        }
    }
}


/* Function adds team of name name to hash table for teams pointed by head */
void add_team(int nl, link_team* head, char* name){
    Team* p_team = searchTeam_Hash(SIZE_TEAM_HASH, head, name);

    if(p_team != NULL) printf("%d Equipa existente.\n", nl);
    else{
        p_team = newTeam(name);
        insertTeam_Hash(SIZE_TEAM_HASH, head, p_team);
    }
}


/* Function searches for team of name name in hash table pointed by head */
void search_team(int nl, link_team* head, char* name){
    Team* p_team = searchTeam_Hash(SIZE_TEAM_HASH, head, name);

    if(p_team == NULL) printf("%d Equipa inexistente.\n", nl);
    else printf("%d %s %d\n", nl, p_team -> name, p_team -> victories);
}


/* Functions lists teams with most wins */
void most_win(int nl, int size, link_team* head){
    int i, max=0, nr_teams=0;
    link_team p_aux;
    
    /* Run through entire Team Hash table to verify max wins (max) */
    for(i=0; i < size; i++){
        p_aux = head[i];
        while(p_aux != NULL){
            if (p_aux->pteam->victories == max){       /* Increase nr of teams with max victories if they have max victories */
                nr_teams++;
            }
            else if (p_aux->pteam->victories > max){   /* If victories of pteam bigger than max, update max & reset nr of teams to 1 */
                max = p_aux->pteam->victories;  
                nr_teams = 1;
            }
            p_aux = p_aux->next;
            
        }
    }

    /* If nr_of teams >0 run through Hash Table again and chose teams with max victories */
    if (nr_teams > 0){
        Team** vector = (Team**)can_fail_malloc(sizeof(Team*)*nr_teams);  /* vector of team pointers for teams with max victories */
        int count = 0;

        for(i=0; i < size; i++){
            p_aux = head[i];
            while(p_aux != NULL){
                if (p_aux -> pteam -> victories == max){  
                    vector[count] = p_aux->pteam;              /* Add team to vector if it has max victories */
                    count++;
                }
                p_aux = p_aux->next;
            }
            if (count == nr_teams) break;                     /* Exist cycle if vector is completed */
        }
      
        qsort(vector, nr_teams, sizeof(Team*), compare);      /* Order vector */
        
        printf("%d Melhores %d\n", nl, max);
        for(i = 0; i < nr_teams; i++){                         /* Run through entire vector outputing teams */
            printf("%d * %s\n", nl, vector[i]->name);
        }
        free(vector);
    }
}


/* Function compares names of teams given as pointers, used for qsort */
int compare(const void *a, const void *b){
    Team** t1 = (Team**)a;
    Team** t2 = (Team**)b;
    
    return strcmp((*t1)->name, (*t2)->name);
}