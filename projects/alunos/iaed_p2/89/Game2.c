#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Game2.h"

/* Adds a game to the system. Returns the team winner */
Team addGame(char *name, char *nteam1, char *nteam2, int s1, int s2,
     BGlink *BGhead, BTlink BThead, int *Elem, int NL){
    Game game;
    Team team1, team2;
    game = BGsearch(*BGhead, name);
    if (!game){
        team1 = BTsearch(BThead, nteam1);
        if (team1){
            team2 = BTsearch(BThead, nteam2);
            if (team2){
                (*Elem)++;
                game = Gnew(name, team1, team2, s1, s2, NL);
                *BGhead = BGinsert(*BGhead, game);

                if (s1 > s2)
                    return team1;
                else if (s2 > s1)
                    return team2;
            }
            else
                printf("%d Equipa inexistente.\n", NL);
        }
        else
            printf("%d Equipa inexistente.\n", NL);
    }
    else
        printf("%d Jogo existente.\n", NL);
    return NULL;
}

/* Lists all games in the system */
void listAllGames(BGlink BGhead, int Elem, int NL){
    int x;
    Game *games;
    if (Elem){
        games = (Game*) can_fail_malloc(sizeof(Game) * Elem);
        Traverse(BGhead, games, 0);
        qsort(games, Elem, sizeof(Game), Gqsort);
        for(x = 0; x < Elem; x++)
            printf("%d %s %s %s %d %d\n", NL, Ggetname(games[x]), Tgetname(Ggetteam1(games[x])),
                Tgetname(Ggetteam2(games[x])), Ggetscore1(games[x]), Ggetscore2(games[x]));
        free(games);
    }
}

/* Changes the score of the game */
void searchGame( char *name, BGlink BGhead, int NL){
    Game game = BGsearch(BGhead, name);
    if (game){
        printf("%d ", NL);
        printf("%s ", Ggetname(game));
        printf("%s ", Tgetname(Ggetteam1(game)));
        printf("%s ", Tgetname(Ggetteam2(game)));
        printf("%d ", Ggetscore1(game));
        printf("%d\n", Ggetscore2(game));
    }
    else
        printf("%d Jogo inexistente.\n", NL);
}

/* Searches for a game in the system */
Team deleteGame(char *name, BGlink *BGhead, int *Elem, int NL){
    Game game = BGsearch(*BGhead, name);
    Team team;
    if (game){
        (*Elem)--;
        *BGhead = BGdelete(*BGhead, game);
        team = Ggetwinner(game);
        Gdelete(game);
        return team;
    }
    else
        printf("%d Jogo inexistente.\n", NL);
    return NULL;
}

/* Deletes a game from the system */
void change_scores(char *name, int s1, int s2,  BGlink BGhead, int NL){
    Game game = BGsearch(BGhead, name);
    Team last, now;
    if(game){
        last = Ggetwinner(game);
        game->score1 = s1; 
        game->score2 = s2;
        now = Ggetwinner(game);

        if (last && now){
            /* There was a winner */
            /* There is a winner */
            if (!eq(key(last), key(now))){
                /* Winners are different */
                TchangeWins(last, -1);
                TchangeWins(now, 1);
            }
        }
        else{
            /* There wasn't or isn't a winner */
            if (last){
                /* There was a winner */
                TchangeWins(last, -1);
            }
            else if (now)
                /* There is a winner */
                TchangeWins(now, 1);
        }
    }
    else
        printf("%d Jogo inexistente.\n", NL);
}

/* Frees all memory allocations regarding games */
void freeAllGames(BGlink *BGhead){
    Game game;
    while (*BGhead != NULL){
        game = BGgetgame(*BGhead);
        *BGhead = BGdelete(*BGhead, game);
        Gdelete(game);
    }
}