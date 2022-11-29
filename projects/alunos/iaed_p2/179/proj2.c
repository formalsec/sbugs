#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "auxiliary_funcs.h"

/* ------ Prototypes ------ */

/* Adds a game to the database */
void addGame(Ht_games *htg, Ht_teams htt, nodeGame *head_games,\
                char name[MAXLEN], char team1[MAXLEN], char team2[MAXLEN],\
                int score1, int score2, int inL);
/* Searchs for a game using its name */
void findGame(Ht_games ht, char *game_name, int inL);
/* Erases a game from the database */
nodeGame eraseGame(Ht_games ht, Ht_teams ht_teams, nodeGame head,\
                    char *game_name, int inL);
/* Lists every game in the database by the order that they were introduced */
void listGames(nodeGame head, int inL);
/* Adds a new team */
void addTeam(Ht_teams *ht, nodeTeam *head, char *team_name, int inL);
/* Searchs for a team using its name */
void findTeam(Ht_teams ht, char *team_name, int inL);
/* Changes the scores of a game */
void updateScore(Ht_games ht, Ht_teams ht_teams, char *game_name,\
                int score1, int score2, int inL);
/* Outputs every team ordered from most games won to least games won */
void bestTeams(nodeTeam head, int inL);


/* ------ Main functions ------ */

int main(){
    /* Counter for the number of lines of input */
    int NL = 1, not_finished = 1, score1, score2;
    char ch, name[MAXLEN] = {0}, team1[MAXLEN] = {0}, team2[MAXLEN] = {0};
    nodeGame head_games = {NULL};
    nodeTeam head_teams = {NULL};
    Ht_games ht_games = HTGinit(H_SIZE_GAME);
    Ht_teams ht_teams = HTTinit(H_SIZE_TEAM);

    while(not_finished){
        switch(ch = getchar()){
            case 'a':
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2,\
                                                        &score1, &score2);
                addGame(&ht_games, ht_teams, &head_games,\
                        name, team1, team2, score1, score2, NL);
                break;

            case 'p':
                scanf(" %[^:\n]", name);
                findGame(ht_games, name, NL);
                break;

            case 'r':
                scanf(" %[^:\n]", name);
                head_games = eraseGame(ht_games, ht_teams, head_games, name, NL);
                break;
            
            case 'l':
                listGames(head_games, NL);
                break;

            case 'A':
                scanf(" %[^:\n]", team1);
                addTeam(&ht_teams, &head_teams, team1, NL);
                break;

            case 'P':
                scanf(" %[^:\n]", team1);
                findTeam(ht_teams, team1, NL);
                break;

            case 's':
                scanf(" %[^:\n]:%d:%d", name, &score1, &score2);
                updateScore(ht_games, ht_teams, name, score1, score2, NL);
                break;

            case 'g':
                bestTeams(head_teams, NL);
                break;
            
            /* case 'x' */
            default:
                not_finished = 0;
        }

        NL++;
        getchar();  /* Gets the '\n' left */
    }

    freeMemory(ht_games, ht_teams, head_games, head_teams);
    return 0;
}

void addGame(Ht_games *htg, Ht_teams htt, nodeGame *head_games,\
            char name[MAXLEN], char team1[MAXLEN], char team2[MAXLEN],\
            int score1, int score2, int inL){

    Team t1, t2;
    
    t1 = HTsearchTeam(htt, team1);
    t2 = HTsearchTeam(htt, team2);
    
    /* Checking if the game already exists */
    if(HTsearchGame(*htg, name) != NULLgame){
        printf("%d Jogo existente.\n", inL);
        return;
    }

    /* Checking if the teams exist */
    else if(t1 == NULLteam || t2 == NULLteam){
        printf("%d Equipa inexistente.\n", inL);
        return;
    }

    else{
        /* Allocate memory for the strings */
        char *pname = allocateWrite(name);
        char *pteam1 = allocateWrite(team1);
        char *pteam2 = allocateWrite(team2);
        Game new_game = newGame(pname, pteam1, pteam2, score1, score2);
        *htg = HTinsertGame(*htg, new_game);
        *head_games = pushGame(*head_games, new_game);

        if(score1 > score2)
            t1->won++;

        else if(score1 < score2)
            t2->won++;
        
        pname = pteam1 = pteam2 = NULL;
    }
    t1 = t2 = NULL;
}

void findGame(Ht_games ht, char *game_name, int inL){
    Game g = HTsearchGame(ht, game_name);

    if(g == NULLgame)
        printf("%d Jogo inexistente.\n", inL);
    else
        outputGame(g, inL);
}

nodeGame eraseGame(Ht_games ht_games, Ht_teams ht_teams,\
                    nodeGame head, char *game_name, int inL){
    Game aux = HTsearchGame(ht_games, game_name);

    if(aux == NULLgame){
        printf("%d Jogo inexistente.\n", inL);
        return head;
    }

    if(aux->score1 > aux->score2)
        withdrawVictory(ht_teams, aux->team1);

    else if(aux->score2 > aux->score1)
        withdrawVictory(ht_teams, aux->team2);

    head = popGame(head, game_name);
    HTdeleteGame(ht_games, game_name);
    aux = NULL;
    return head;
}

void listGames(nodeGame head, int inL){
    if(head == NULL)
        return;
    /* Delaying operations to get to the last element */
    listGames(head->next, inL);
    outputGame(head->ptr, inL);
}

void addTeam(Ht_teams *ht, nodeTeam *head, char *team_name, int inL){
    char *name;
    Team t, aux = HTsearchTeam(*ht, team_name);

    if(aux == NULLteam){
        name = allocateWrite(team_name);
        t = newTeam(name, 0);
        *ht = HTinsertTeam(*ht, t);
        *head = pushTeam(*head, t);
        name = NULL;
        return;
    }

    printf("%d Equipa existente.\n", inL);
}

void findTeam(Ht_teams ht, char *team_name, int inL){
    Team t = HTsearchTeam(ht, team_name);

    if(t != NULLteam){
        outputTeam(t, inL);
        return;
    }

    /* If it doesnt exist */
    printf("%d Equipa inexistente.\n", inL);
}

void updateScore(Ht_games ht_games, Ht_teams ht_teams,\
                char *game_name, int score1, int score2, int inL){
                    
    int prevS1, prevS2;
    Game game = HTsearchGame(ht_games, game_name);

    if(game == NULLgame){
        printf("%d Jogo inexistente.\n", inL);
        return;
    }

    prevS1 = game->score1;
    prevS2 = game->score2;
    game->score1 = score1;
    game->score2 = score2;
    changeWins(ht_teams, &game, score1, score2, prevS1, prevS2);
    game = NULLgame;
}

void bestTeams(nodeTeam head, int inL){
    if(head == NULL)
        return;
    
    else{
        int i, w = mostWins(head);
        int n = countTeams(head, w);
        Team *teams = nWinsTeams(head, n, w);
        qsort(teams, n, sizeof(Team*), compareQsort);

        printf("%d Melhores %d\n", inL, w);
        for(i = 0; i < n; i++)
            printf("%d * %s\n", inL, teams[i]->name);
        
        free(teams);
        teams = NULL;
    }
}
