#ifndef LINKED_LISTS_H_INCLUDED
#define LINKED_LISTS_H_INCLUDED

/*--------struct for chars---------*/
typedef struct index_node{
    struct index_node *next;
    int s;
} indexNode;


/*--------struct for games---------*/
typedef struct{
    char * name;
    int id;
    int score1;
    int score2;
    char * team1;
    char * team2;
}Game;


/*--------struct for teams----------*/
typedef struct{
    char * name;
    int wins;
}Team;


/*------------struct for teams nodes-------------*/
typedef struct node_team{
    Team * team;
    struct node_team * next;
}nodeTeam;


/*------------struct for games nodes-------------*/
typedef struct node_game{
    Game * game;
    struct node_game * next;
}nodeGame;





/*------------functions for list of strings/ints-------------*/
indexNode * _add_index_(indexNode *, int);

indexNode * _destroy_list_(indexNode *);





/*------------functions for list of teams-------------*/
nodeTeam * _push_team_(nodeTeam *, char *);

nodeTeam * _destroy_team_(nodeTeam *);

int _change_wins_(nodeTeam *, char *, int);

nodeTeam * _is_team_(nodeTeam *, char *);





/*------------functions for list of games-------------*/
nodeGame * _push_game_(nodeGame *, char *, int, int, int, char *, char *);

nodeGame * _del_game_(nodeGame *, char *);

nodeGame * _is_game_(nodeGame *, char *);

nodeGame * _destroy_game_(nodeGame *);

#endif