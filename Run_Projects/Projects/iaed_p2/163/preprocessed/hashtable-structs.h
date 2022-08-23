#ifndef __HASHTABLE__
#define __HASHTABLE__


typedef struct team{
    char* team_name;
    int games_won;
    struct team * next;
}*team_ptr;

typedef struct game{
    char * game_name;
    char * team1;
    char * team2;
    int score_team1;
    int score_team2;
}*game_ptr;

typedef struct node{
    struct node * next;
    game_ptr this_game;
}*link;


/* LIST FOR TEAMS*/
team_ptr NewTeamLink(char * team_name_var);
team_ptr InsertBeginTeamList(team_ptr head, char* team_name_var);
team_ptr LookUpTeams(team_ptr head, char * team_name_var);
void freeTeamList(team_ptr head);

/*LIST FOR GAMES TO SORT*/
link InsertGameList(link head, char* game_name_var, char*team1_var
                        , char*team2_var,
            int score1, int score2);

link ChangeScore(link head, char* game_name_var
                , int score1, int score2);


/*LIST FOR GAMES*/
link NewLink(char* game_name_var, char* team1_var, char*team2_var,
            int score1, int score2);
link InsertBegin(link head, char* game_name_var,char*team1_var, char*team2_var, 
            int score1, int score2);
link LookUp(link head, char * game_name_var);

link Remove(link head, char* game_name_var);

void freeLink(link head);
void print_list(link head);

/*HASHTABLE*/
int hash(char* game_name_var ,int size_table);
link* Init(link * heads, int size_table);
void InsertInTable(link* hashtable, int size_table,
                    char* game_name_var, char*team1_var, char*team2_var,
            int score1, int score2);

void RemoveFromTable(link* hashtable, int size_table, char * game_name_var);

game_ptr LookUpInTable(link* hashtable, char * game_name_var, int size_table);
void PrintTable(link* hashtable, int size_table);

void DeleteHashtable(link* hastable, int size_table);

#endif