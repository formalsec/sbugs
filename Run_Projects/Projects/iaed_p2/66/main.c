#include "main.h"

int main()
{
    char command;
    int NL = 0; /*Used to count the number of the input line*/

    /*Initialize the games and the teams hashtable and the games list*/
    GameHash_ptr game_hash = GameHashInit(INITIAL_HASH_SIZE);
    Game_link game_list = NULL;
    TeamHash_ptr team_hash = TeamHashInit(INITIAL_HASH_SIZE);

    while ((command = getchar()) != 'x')
    {
        switch (command)
        {
        case 'a':
            NL++;
            AddGame(&game_hash, &game_list, team_hash, NL);
            break;

        case 'l':
            NL++;
            GameList(game_list, NL);
            break;

        case 'p':
            NL++;
            SearchGame(game_hash, NL);
            break;

        case 'r':
            NL++;
            DeleteGame(game_hash, &game_list, NL);
            break;

        case 's':
            NL++;
            ChangeScore(game_hash, NL);
            break;

        case 'A':
            NL++;
            AddTeam(&team_hash, NL);
            break;

        case 'P':
            NL++;
            SearchTeam(team_hash, NL);
            break;

        case 'g':
            NL++;
            SearchBestTeams(team_hash, NL);
            break;

        default:
            break;
        }
    }
    FreeAll(game_hash, game_list, team_hash);

    return 0;
}

/*Adds a game to the system*/
void AddGame(GameHash_ptr *game_hash, Game_link *game_list, TeamHash_ptr team_hash, int NL)
{
    int score1, score2;
    char name_buffer[1024], team1_buffer[1024], team2_buffer[1024];
    char *name, *team1_name, *team2_name;
    Game_ptr game;
    Team_ptr team1, team2;

    /*Input treatment*/
    scanf(" %" SIZE "[^:\n]:%" SIZE "[^:\n]:%" SIZE "[^:\n]:%d:%d", name_buffer, team1_buffer,
          team2_buffer, &score1, &score2);
    name = StringDup(name_buffer);
    team1_name = StringDup(team1_buffer);
    team2_name = StringDup(team2_buffer);

    /*If game already exists*/
    if (GameHashSearch(*game_hash, name) != NULL)
    {
        free(name);
        free(team1_name);
        free(team2_name);
        printf("%d Jogo existente.\n", NL);
        return;
    }

    /*Get both teams' pointers*/
    team1 = TeamHashSearch(team_hash, team1_name);
    team2 = TeamHashSearch(team_hash, team2_name);

    /*If any of the teams is non-existent*/
    if (team1 == NULL || team2 == NULL)
    {
        free(name);
        free(team1_name);
        free(team2_name);
        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    /*Adds a win to the winner*/
    if (score1 > score2)
        wins(team1)++;
    else if (score1 < score2)
        wins(team2)++;

    /*Adds the new game to both the list and the hashtable*/
    game = NewGame(name, team1, team2, score1, score2);
    *game_hash = GameHashInsert(*game_hash, game);
    *game_list = InsertGameBeginList(*game_list, game);

    free(name);
    free(team1_name);
    free(team2_name);
}

/*Adds a team to the system*/
void AddTeam(TeamHash_ptr *team_hash, int NL)
{
    char buffer[1024], *name;

    /*Input treatment*/
    scanf(" %" SIZE "[^:\n]", buffer);
    name = StringDup(buffer);

    /*If the team already exists*/
    if (TeamHashSearch(*team_hash, name) != NULL)
    {
        free(name);
        printf("%d Equipa existente.\n", NL);
        return;
    }

    /*Adds the new team to the team hashtable*/
    *team_hash = TeamHashInsert(team_hash, NewTeam(name));

    free(name);
}

/*Lists every game in the order they were introduced*/
void GameList(Game_link game_list, int NL)
{
    Game_link aux;

    /*If there are games, print every game*/
    if (game_list != NULL)
    {
        aux = game_list->prev;
        do
        {
            printf("%d ", NL);
            PrintGame(aux->game);
            aux = aux->prev;
        } while (aux != game_list->prev);
    }
}

/*Given a game name, searches for that game and prints its elements*/
void SearchGame(GameHash_ptr game_hash, int NL)
{
    char buffer[1024];
    char *name;
    Game_ptr game;

    /*Input treatment*/
    scanf(" %" SIZE "[^:\n]", buffer);
    name = StringDup(buffer);

    game = GameHashSearch(game_hash, name);

    /*If the game exists, print its elements*/
    if (game != NULL)
    {
        printf("%d ", NL);
        PrintGame(game);
    }
    else
        printf("%d Jogo inexistente.\n", NL);

    free(name);
}

/*Given a team name, searches for that team and prints its elements*/
void SearchTeam(TeamHash_ptr team_hash, int NL)
{
    char buffer[1024], *name;
    Team_ptr team;

    /*Input treatment*/
    scanf(" %" SIZE "[^:\n]", buffer);
    name = StringDup(buffer);

    team = TeamHashSearch(team_hash, name);

    /*If the team exists, print its elements*/
    if (team != NULL)
    {
        printf("%d ", NL);
        PrintTeam(team);
    }
    else
        printf("%d Equipa inexistente.\n", NL);

    free(name);
}

/*Removes a game from the system*/
void DeleteGame(GameHash_ptr game_hash, Game_link *game_list, int NL)
{
    char buffer[1024], *name;
    Game_ptr game;

    /*Input treatment*/
    scanf(" %" SIZE "[^:\n]", buffer);
    name = StringDup(buffer);

    game = GameHashSearch(game_hash, name);

    /*If the game doesn't exist*/
    if (game == NULL)
    {
        free(name);
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    /*If team1 won the deleted game, decrement its wins*/
    if (score1(game) > score2(game))
        DecrementWins(game->team1);

    /*If team2 won the deleted game, decrement its wins*/
    else if (score1(game) < score2(game))
        DecrementWins(game->team2);

    /*Removes the given game from both the hashtable and the list*/
    GameHashRemove(game_hash, name);
    *game_list = RemoveGameList(*game_list, name);

    free(name);
}

/*Changes the score of a given game*/
void ChangeScore(GameHash_ptr game_hash, int NL)
{
    char buffer[1024];
    char *name;
    int score1, score2;
    Team_ptr winner;
    Game_ptr game;

    /*Input treatment*/
    scanf(" %" SIZE "[^:\n]:%d:%d", buffer, &score1, &score2);
    name = StringDup(buffer);

    game = GameHashSearch(game_hash, name);

    /*If the dame doens't exist*/
    if (game == NULL)
    {
        free(name);
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    winner = game_winner(game); /*Get original winner*/

    if (winner != NULL)
        wins(winner)--;

    /*Update the game's score*/
    score1(game) = score1;
    score2(game) = score2;

    winner = game_winner(game); /*Get new winner*/

    if (winner != NULL)
        wins(winner)++;

    free(name);
}

/*Prints the teams with the most wins in lexographical order*/
void SearchBestTeams(TeamHash_ptr team_hash, int NL)
{
    int i, N = 0, most_wins = -1;
    int K = 0; /*Used to determine the index of the first of the best teams*/
    Team_ptr *best_teams = (Team_ptr *)malloc(sizeof(Team_ptr) * item_count(team_hash));

    /*Iterate through the team hashtable*/
    for (i = 0; i < hash_size(team_hash); i++)
        if (team_hash->hash_table[i] != NULL)
        {
            /*If the current team has more wins than the previous most_wins winner, update the most_wins,
            update K and add the current team to the array*/
            if (wins(team_hash->hash_table[i]) > most_wins)
            {
                most_wins = wins(team_hash->hash_table[i]);
                K = N;
                ArrayInsert(best_teams, team_hash->hash_table[i], &N);
            }

            /*If the current teams has the same wins as the most_wins add the team to the array*/
            else if (wins(team_hash->hash_table[i]) == most_wins)
                ArrayInsert(best_teams, team_hash->hash_table[i], &N);
        }

    /*If there are no teams*/
    if (N == 0)
    {
        free(best_teams);
        return;
    }

    /*Sort the array in lexicographical order*/
    mergesort(best_teams, K, N - 1, team_hash);

    printf("%d Melhores %d\n", NL, most_wins);

    /*Print the best teams*/
    for (; K < N; K++)
        printf("%d * %s\n", NL, name(best_teams[K]));

    free(best_teams);
}

/*Frees every malloc that hasn't been freed*/
void FreeAll(GameHash_ptr game_hash, Game_link game_list, TeamHash_ptr team_hash)
{
    DeleteTeamHash(team_hash);
    DeleteGameHash(game_hash);
    DeleteGameList(game_list);
}