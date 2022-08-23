#include "MainFunctions.h"
/* Initial size of both hash tables.*/
#define M 1021

int main(){
    /* Initialization of every variable and structure needed to the well functioning of the program.*/
    char c;
    int NL = 1, m_games_init = M, m_teams_init = M, n_games_init = 0, n_teams_init = 0;
    int *m_games = &m_games_init, *m_teams = &m_teams_init, *n_games = &n_games_init, *n_teams = &n_teams_init;
    Node * hash_game = HashGamesInit(m_games);
    Team * hash_team = HashTeamsInit(m_teams);  
    List l = InitList();
    /* While the command is not 'x', the program continues and the line number "NL" is incremented.*/
    for (; (c = getchar()) != 'x'; NL++){ 
        switch (c){
            case 'a':
                NewGame(hash_game, hash_team, l, NL, m_games, m_teams, n_games);
                break;
            case 'A':
                NewTeam(hash_team, m_teams, NL, n_teams);
                break;
            case 'l':
                ListGames(NL, l);
                break;
            case 'p':
                SearchGame(hash_game, m_games, NL);
                break;
            case 'P':
                SearchTeam(hash_team, m_teams, NL);
                break;
            case 'r':
                DeleteGame(hash_game, l, m_games, NL, n_games);
                break;
            case 's':
                ChangeScore(hash_game, m_games, NL);
                break;
            case 'g':
                FindBest(hash_team, n_teams, NL); 
                break;
        }
        /* If the command is, either to add a Game or to add a Team, the hash tables capacity must be evaluated.*/
        if (c == 'a' || c == 'A'){
            if (CheckHashGame(n_games, m_games))
                hash_game = ExpandGames(hash_game, n_games, m_games);
            else if (CheckHashTeam(n_teams, m_teams))
                hash_team = ExpandTeams(hash_team, n_teams, m_teams);
        }
    }
    /* If the command is 'x', the program ends and every structure must be destroyed.*/
    Clean(l, hash_game, hash_team, n_teams);

    return 0;
}