#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATCHTABLESIZE 40897    /* maximum number of matches stored */
#define TEAMTABLESIZE 20111 /* maximum number of teams stored */
#define STRMAX 1024 /* maximum number of input characters */

int nl = 0; /* input counter */
int entry = 1;  /* match entries counter */  

typedef struct team{    /* a structure destined to store teams and their total wins */
    char *name;
    int wins;
} *pteam;

typedef struct team Team;
static pteam *teamtable;    /* table where every team and their stats will be stored */

void Teamtableinit(){   /* initiates the teams' table*/
    int i;
    teamtable = (pteam*) malloc (TEAMTABLESIZE * sizeof(pteam));
    for (i = 0; i < TEAMTABLESIZE; i++)
        teamtable[i] = NULL;
}

int hash(char *name, int M){    /* hashing algorythm for the tables */
    int h, a = 31415, b = 27183;
    for (h = 0; *name != '\0'; name++, a = a * b % (M -1))
        h = (a * h + *name) % M;
    return h;
}

void add_team_to_table(pteam team){ /* stores a team in the table */
    int i = hash(team -> name, TEAMTABLESIZE);
    while(teamtable[i] != NULL)
        i = (i + 1) % TEAMTABLESIZE;
    teamtable[i] = team;
}

void add_team(char *new_name){  /* creates a new team in the database */
    pteam new_team;
    new_team = (pteam) malloc (sizeof (Team));
    new_team -> name = (char*) malloc (strlen (new_name) + 1);
    strncpy(new_team -> name, new_name, strlen (new_name) + 1);
    new_team -> wins = 0;
    add_team_to_table(new_team);
}

pteam search_team_in_table(char *team_name){ /* finds a team in the database */
    int i = hash(team_name, TEAMTABLESIZE);
    while (teamtable[i] != NULL){
        if (strncmp(teamtable[i] -> name, team_name, strlen(team_name)+1)==0)
            return teamtable[i];
        else
            i = (i + 1) % TEAMTABLESIZE;
    }
    return NULL;
}

void search_team(char *team_name){  /* returns a team's stats */
    pteam current_team = search_team_in_table(team_name);
    if (search_team_in_table(team_name) != NULL)
        printf("%d %s %d\n", nl, current_team -> name, current_team -> wins);
    else
        printf("%d Equipa inexistente.\n", nl);
}

typedef struct match{   /* a structure destined to store a match's participants and final result */
    char *id;
    char *team1;
    char *team2;
    int score1;
    int score2;
    int entry;
} *pmatch;

typedef struct match Match;
static pmatch *matchtable; /* table where every match andits info will be stored */

void Matchtableinit(){  /* inititates the matches' table */
    int i;
    matchtable = (pmatch*) malloc (MATCHTABLESIZE * sizeof(Match));
    for (i = 0; i < MATCHTABLESIZE; i++)
        matchtable[i] = NULL;
}

void add_match_to_table(pmatch match){  /* stores a match in the table */
    int i = hash(match -> id, MATCHTABLESIZE);
    while(matchtable[i] != NULL)
        i = (i + 1) % MATCHTABLESIZE;
    matchtable[i] = match;
}

void add_match(char *name, char *team_1, char *team_2, int score_1, int score_2){   /* creates a new match in the database */
    pmatch new_match;
    new_match = (pmatch) malloc (sizeof (Match));
    new_match -> id = (char*) malloc (strlen(name) + 1);
    new_match -> team1 = (char*) malloc (strlen(team_1) + 1);
    new_match -> team2 = (char*) malloc (strlen(team_2) + 1);
    strcpy(new_match -> id, name);
    strcpy(new_match -> team1, team_1);
    strcpy(new_match -> team2, team_2);
    new_match -> score1 = score_1;
    new_match -> score2 = score_2;
    new_match -> entry = entry;
    add_match_to_table(new_match);    
}

void winner(char *team_1, char *team_2, int score_1, int score_2){  /* determines a match's winner */
    pteam current_team;
    if (score_1 > score_2){
        current_team = search_team_in_table(team_1);
        current_team -> wins++;
    }
    else if (score_2 > score_1){
        current_team = search_team_in_table(team_2);
        current_team -> wins++;
    }
}

void remove_win(char *team_1, char *team_2, int score_1, int score_2){  /* removes a win to a team accordingly to the new result */
    pteam current_team;
    if (score_1 > score_2){
        current_team = search_team_in_table(team_1);
        current_team -> wins--;
    }
    else if (score_2 > score_1){
        current_team = search_team_in_table(team_2);
        current_team -> wins--;
    }
}

pmatch search_match_in_table(char *match_id){   /* finds a match in the database */
    int i = hash(match_id, MATCHTABLESIZE);
    while (matchtable[i] != NULL){
        if (strncmp(matchtable[i] -> id, match_id, strlen(match_id)+1)==0)
            return matchtable[i];
        else
            i = (i + 1) % MATCHTABLESIZE;
    }
    return NULL;
}

int matchSort(const void* a, const void* b) /* algorythm for numerical entry match comparison */
{
    const pmatch pa = *(const pmatch *)a;
    const pmatch pb = *(const pmatch *)b;
    return (pa -> entry - pb -> entry);
}

void list_games(){  /* lists every game in the database by numerical entry order */
    int i;
    int nrMatches = 0;
    pmatch matches[MATCHTABLESIZE];
    for(i = 0; i < MATCHTABLESIZE; i++)
    {
        if(matchtable[i] != NULL)
        {
            matches[nrMatches] = matchtable[i];
            nrMatches++;
        }
    }
    if(nrMatches > 0)
    {
        qsort(matches, nrMatches, sizeof(pmatch), matchSort);   /* sorts matches */ 
        for(i=0; i < nrMatches; i++)
            printf("%d %s %s %s %d %d\n", nl, matches[i] ->  id, matches[i]  -> team1, matches[i]  -> team2, matches[i] -> score1, matches[i] -> score2);
    }
           
}

void edit_result(pmatch game, int new_s1, int new_s2){  /* rectifies a match's result */
    remove_win(game -> team1, game -> team2, game -> score1, game -> score2);
    winner(game -> team1, game -> team2, new_s1, new_s2);
    game -> score1 = new_s1;
    game -> score2 = new_s2;
}

void free_match(pmatch game){   /* frees all memory allocated for a match */
    free(game -> id);
    free(game -> team1);
    free(game -> team2);
    free(game);
}

void remove_match(pmatch game){ /* deletes a match from the database */
    int j, i = hash(game -> id, MATCHTABLESIZE); 
    pmatch aux;
    while(matchtable[i] != NULL)
        if (strcmp(matchtable[i] -> id, game -> id) == 0)
            break;
        else
            i = (i + 1) % MATCHTABLESIZE;
    if (matchtable[i] == NULL)
        return;
    free_match(matchtable[i]);
    matchtable[i] = NULL;
    for (j = (i + 1) % MATCHTABLESIZE; matchtable[j] != NULL; j = (j + 1) % MATCHTABLESIZE){
        aux = matchtable[j];
        matchtable[j] = NULL;
        add_match_to_table(aux);
    }    
}

char* str_treatment(char str[STRMAX]){  /* processes the input strings */
    char* new_str;
    str[strlen(str)+1] = '\0';
    new_str = (char*) malloc(sizeof(char)*(strlen(str)+1));
    strncpy(new_str, str, strlen(str)+1);
    return new_str;
}

int sortComp(const void* a, const void* b)  /* algorythm for alphabetical string comparison */
{
    const char * pa = *(const char **)a;
    const char * pb = *(const char **)b;
    return strcmp(pa,pb);
}

void best_teams(){  /* determines team/s with the most wins */
    int i, max_wins = 0, verify = 0, team_counter = 0;
    char *team_array[TEAMTABLESIZE];
    for(i = 0; i < TEAMTABLESIZE; i++)
        if (teamtable[i] != NULL){
            verify = 1;
            if(teamtable[i] -> wins > max_wins)
                max_wins = teamtable[i] -> wins;
        }
    if (verify == 1){
        printf("%d Melhores %d\n", nl, max_wins);
        for(i = 0; i < TEAMTABLESIZE; i++)
            if (teamtable[i] != NULL)
                if(teamtable[i] -> wins == max_wins)
                {
                    team_array[team_counter] = teamtable[i] -> name;
                    team_counter++;
                }
    }
    if(team_counter > 0)
    {
        int j;
        qsort(team_array, team_counter, sizeof(char *), sortComp); /* sorts teams in alphabetical order */
        for(j= 0; j < team_counter; j++)
        {
            printf("%d * %s\n", nl, team_array[j]);
        }
    }
                
}

void flush_in(){    /* clears input buffer */
    int ch;
    do{
        ch = fgetc(stdin);
    }
    while (ch != EOF && ch != '\n');
}

void free_all(){    /* frees all memory allocated for the database */
    int i;
    for(i = 0; i < MATCHTABLESIZE; i++)
        if (matchtable[i] != NULL){
            free_match(matchtable[i]);
        }
    free(matchtable);
    for(i = 0; i < TEAMTABLESIZE; i++)
        if (teamtable[i] != NULL){
            free(teamtable[i] -> name);
            free(teamtable[i]);
        }
    free(teamtable);
}

int main() {

    int command;
    char match_id[STRMAX];
    char t1[STRMAX];
    char t2[STRMAX];    
    char t[STRMAX];
    char* taux;
    int s1, s2;
    pmatch found_match;
    pmatch match_to_remove;
    pmatch current_match;
    
    Teamtableinit();
    Matchtableinit();

    while((command=getchar()) != 'x') {   /* input selector */
        nl++;
        switch(command) {
            
            
            case 'a':   /* adds a new match to the database */
            
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", match_id, t1, t2, &s1, &s2);
                
                if (search_match_in_table( match_id) != NULL)
                    printf("%d Jogo existente.\n", nl);
                
                else if(search_team_in_table(t1) == NULL || search_team_in_table(t2) == NULL){
                    printf("%d Equipa inexistente.\n", nl);
                }
                
                else{
                    winner(t1, t2, s1, s2);
                    add_match(match_id, t1, t2, s1, s2);
                    entry++;
                }
                
                break;

            case 'A':   /* adds a new team to the database */

                scanf(" %[^:\n]", t);
                taux = str_treatment(t);
                
                if (search_team_in_table(taux) == NULL)
                    add_team(taux);
                
                else
                    printf("%d Equipa existente.\n", nl);
                
                free(taux);
                break;
            
            case 'l':   /* lists every game in the database */
                
                list_games();
                break;

            case 'p':   /* finds a match in the database */

                scanf(" %[^:\n]", match_id);
                found_match = search_match_in_table(match_id);
                
                if(found_match != NULL)
                    printf("%d %s %s %s %d %d\n", nl, found_match -> id, found_match -> team1, found_match -> team2, found_match -> score1, found_match -> score2);
                
                else
                    printf("%d Jogo inexistente.\n", nl);
                
                break;

            case 'P':   /* finds a team the database */

                scanf(" %[^:\n]", t);
                taux = str_treatment(t);
                search_team(taux);
                free(taux);
                break;

            case 'r':   /* deletes a team from the database */

                scanf(" %[^:\n]", match_id);
                match_to_remove = search_match_in_table(match_id);
                
                if (match_to_remove == NULL)
                    printf("%d Jogo inexistente.\n", nl);
                
                else{
                    remove_win(match_to_remove -> team1, match_to_remove -> team2, match_to_remove -> score1, match_to_remove -> score2);
                    remove_match(match_to_remove);
                }
               
                break;

            case 's':   /* rectifies a match's final result */

                scanf(" %[^:\n]:%d:%d", match_id, &s1, &s2);
                current_match = search_match_in_table( match_id);
                
                if (current_match == NULL)
                    printf("%d Jogo inexistente.\n", nl);
               
                else
                    edit_result(current_match, s1, s2);
                
                break;

            case 'g':   /* finds the team/s with most wins */
                
                best_teams();
                break;

            case 'x':   /* shuts down database */
                  
                break;
            
        }
        flush_in();
    }
    free_all();
    return 0;
}