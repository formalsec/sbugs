#ifndef projectIAED1920
#define projectIAED1920
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxSizeName 1024
#define TableSize  6701


/*##################################################################################################

Struct team contains all the information about a team, most specifically the name and the number of   
victories that team has and a pointer to  the next team wich will point to all the information about                                                                            
another team.

##################################################################################################*/
typedef struct team{
    char *name;
    int v;
    struct team *next;
}*link_team;


/*##################################################################################################

Struct game contains all the information about a game, most specifically the name, home 
team(element_t1), away team(element_t2), goals of hometeam(r1), goals of away team(r2) and a pointer 
to the next game wich will point to all the information about another game.

element_t1 and element_t2 are both pointers to the struct team and there will be the information
about the team envolved in that game.

##################################################################################################*/
typedef struct game{
    char *name;
    link_team element_t1;
    link_team element_t2;
    int r1;
    int r2;
    struct game *next;
}*link_game;


/*##################################################################################################

Struct order_game is created in order to assist command_l so we can create a linked list and print 
the games in the order they were entered. This struct contains an elemente that points to a struct 
game where all the information about a specific game is and a pointer next that points to the next
game on the linked list.                                                                     

##################################################################################################*/
typedef struct order_game{
    link_game element;           
    struct order_game *next;
}*link_game_order;

/*##################################################################################################

Struct Team_lexicographical_order is created in order to assist command_g so we can create a linked 
list and print the games in the lexicographical order. This struct contains an elemente that points 
to a struct team where all the information about a specific team is and a pointer next that points
to the next game on the linked list.                                                                     

##################################################################################################*/
typedef struct Team_lexicographical_order{
    link_team elemente;           
    struct Team_lexicographical_order *next;
}*link_Team_lexicographical_order;


/*############################

Functions that will be used

############################*/

link_game * init_j();
link_team * init_t();
int hash(char *nome);
link_game command_a(link_game *htable_game,link_team *htable_team, char *name, char *t1, char *t2, 
int r1, int r2, int NL_counter);
void command_A(link_team *htable_team, char *name, int NL_counter);
void command_p(link_game *htable_game, char *name, int NL_counter);
void command_P(link_team *htable_team, char * name, int NL_counter);
void command_l(link_game_order ordergamelist, int NL_counter);
link_game_order command_r(link_game *htable_game, link_game_order head, char* text, int NL_counter);
int command_s(link_game *htable_game, char *GameName, int score1, int score2, int NL_counter);
void command_g(link_team *htable_team, int mostvictories, int NL_counter);
link_game NEWgame(char *name, link_team t1, link_team t2, int r1, int r2);
link_team NEWteam(char *name);
link_game lookup_game(link_game *htable_game, char *nome);
link_team lookup_team(link_team *htable_team, char *nome);
link_game_order insertBegin(link_game_order head, link_game game);
void freeHTteam(link_team *htable_team);
void freeHTgame(link_game *htable_game);
void freeGame(link_game game);
link_game deletegame(link_game head, char *name);
int Lookup_BiggerNumVictories(link_team *head);
link_Team_lexicographical_order insert_lexicographical_order(link_Team_lexicographical_order *head, 
link_team target);
void print_list_betterTeams(link_Team_lexicographical_order list_betterTeams, int NL_counter);
void freebetterLIST(link_Team_lexicographical_order *head);
void freeordergamelist(link_game_order head);
#endif