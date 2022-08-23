#include "MainFunctions.h"

/* Command: a
Receives a hash of Nodes, a hash of Teams, a List, a line number, a size for the hash of Nodes,
a size for the hash of Teams and a number of Games. Creates a new Game if the Game does not exist and the Teams do.*/
void NewGame(Node * hash_game, Team * hash_team, List l, int NL, int * m_game, int * m_team, int * n_games){
    char name[MAX_STR], team_1[MAX_STR], team_2[MAX_STR];
    int score_1, score_2;
    Game g;
    Team t1, t2, winner;
    /* Information scan.*/
    getchar();
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team_1, team_2, &score_1, &score_2);
    getchar();
    /* If the Game name already exists, an error message is printed.*/
    if (GameSearch(name, m_game, hash_game) != DOES_NOT_EXIST)
        printf("%d Jogo existente.\n", NL);
    /* If one of the Teams does not exist, an error message is printed.*/
    else if ((t1 = TeamSearch(team_1, m_team, hash_team)) == NULL || (t2 = TeamSearch(team_2, m_team, hash_team)) == NULL)
        printf("%d Equipa inexistente.\n", NL);
    /* Else, a new Game is created.*/
    else{
        /* Game initialization, name, score and Teams set up.*/
        g = InitGame();
        SetName(name, g);
        SetScore(score_1, score_2, g);
        SetTeams(t1, t2, g);
        /* The new Game is inserted in the end of the List.*/
        InsertEnd(l, g);
        /* The Node with the new Game is inserted in the hash of Nodes.*/
        HashGamesInsert(hash_game, End(l), m_game);
        /* If there is a winner of the Game, its wins are incremented.*/
        if ((winner = Winner(g)) != NULL)
            IncWins(winner);
        /* The number of existing Games gets incremented.*/
        (*n_games)++;
    }
}

/* Command: A 
Receives a hash of Teams, its size, a line number and a number of Teams. 
If the Team does not exist, a new Team is created.*/
void NewTeam(Team * hash_team, int * m, int NL, int * n_teams){
    char name[MAX_STR];
    Team t;
    /* Information scan.*/
    getchar();
    scanf("%[^:\n]", name);
    getchar();
    /* If the Team does already exist, an error message is printed.*/
    if (TeamSearch(name, m, hash_team) != NULL)
        printf("%d Equipa existente.\n", NL);
    /* Else, a new Team gets created.*/
    else{
        /* Team creation and name setup.*/
        t = InitTeam();
        SetTeamName(t, name);
        /* The new Team gets inserted in the hash of Teams.*/
        HashTeamsInsert(hash_team, t, m);
        /* The number of Teams is incremented.*/
        (*n_teams)++;
    }
}

/* Command: l 
Receives a line number and a List. Writes every Game on the List by order of insertion.*/
void ListGames(int NL, List l){
    Node head = Head(l);
    
    getchar();
    /* While the List is not over, the Node Game gets printed.*/
    for (; head != NULL; head = Next(head))
        WriteGame(NodeGame(head), NL);
}

/* Command: p 
Receives a hash table of Nodes, its size and a line number. Searches for a Game.*/
void SearchGame(Node * hash_game, int * m, int NL){
    char name[MAX_STR];
    int i;
    /* Information scan.*/
    getchar();
    scanf("%[^:\n]", name);
    getchar();
    /* If the Game exists, it gets printed.*/
    if ((i = GameSearch(name, m , hash_game)) != DOES_NOT_EXIST)
        WriteGame(NodeGame(hash_game[i]), NL);
    /* Else, an error message gets printed.*/
    else 
        printf("%d Jogo inexistente.\n", NL);
}

/* Command: P 
Receives a hash table of Teams, its size and a line number. Searches for a Team.*/
void SearchTeam(Team * hash_team, int * m, int NL){
    char name[MAX_STR];
    Team t;  
    /* Information scan.*/
    getchar();
    scanf("%[^:\n]", name);
    getchar();
    /* If the Team exists, it gets printed.*/
    if ((t = TeamSearch(name, m, hash_team)) != NULL)
        WriteTeam(t, NL);
    /* Else, an error message gets printed.*/ 
    else 
        printf("%d Equipa inexistente.\n", NL);
}

/* Command: r 
Receives a hash table of Nodes, a List, a size of the hash table, a line number and a number of Games.
Deletes a Game.*/
void DeleteGame(Node * hash_game, List l, int * m, int NL, int * n_games){
    char name[MAX_STR];
    Node node;
    /* Information scan.*/
    getchar();
    scanf("%[^:\n]", name);
    getchar();
    /* If the Game to be removed exists, it gets removed and the number of Games are decremented.
    First it is removed from the hash of Nodes, and then from the List.*/
    if ((node = HashRemoveGame(name, m, hash_game)) != NULL){
        RemoveGame(node, l);
        (*n_games)--;
    }
    /* Else, an error message gets printed.*/
    else
        printf("%d Jogo inexistente.\n", NL);
}

/* Command: s 
Receives a hash table of Nodes, its size and a line number.*/
void ChangeScore(Node * hash_game, int * m, int NL){
    char name[MAX_STR];
    Node node;
    int i, score_1, score_2;
    Team old_winner, new_winner;
    /* Information scan.*/
    getchar();
    scanf("%[^:\n]:%d:%d", name, &score_1, &score_2);
    getchar();
    /* If the Game does not exist, an error message gets printed, and the function ends.*/
    if ((i = GameSearch(name, m, hash_game)) == DOES_NOT_EXIST){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    /* To change the score, there needs to be a record of the old winner of the Game changed.*/
    node = hash_game[i];
    old_winner = Winner(NodeGame(node));
    /* Score is changed.*/
    SetScore(score_1, score_2, NodeGame(node));
    new_winner = Winner(NodeGame(node));
    /* Analysis of every possible situation to update the wins of each Team that are part of the Game changed.*/
    if (old_winner == new_winner)
        return;
    else if (old_winner == NULL)
        IncWins(new_winner);
    else if (new_winner == NULL)
        DecWins(old_winner);
    else {
        DecWins(old_winner);
        IncWins(new_winner);
    }
}

/* Command: g 
Receives a hash table of Teams, a number of Teams and a line number. Prints the Teams with
the best number of Wins by lexicographic order.*/
void FindBest(Team * hash_team, int * n_teams, int NL){
    int i = 0, best = 0, count = 0, n = 0;
    char ** team_names = NULL;

    getchar();
    /* If there are no Teams, the function ends.*/
    if (!*n_teams)
        return;
    /* First step, we find the best number of wins and how many Teams have it.*/
    for (; n < *n_teams; i++){
        if (hash_team[i] != NULL){
            n++;
            /* For every Team found if its wins are more than the best, then the best is updated and 
            the "count" of best Team is set to 1.*/
            if (Wins(hash_team[i]) > best){
                best = Wins(hash_team[i]);
                count = 1;
            }
            /* If the Team's wins equals the best, the "count" is incremented.*/
            else if (Wins(hash_team[i]) == best)
                count++;
        }
    }
    /* Second step, the array of strings "team_names" is created with only the necessary amount to fit the best Teams.*/
    team_names = CreatesTeamNames(team_names, hash_team, count, best);

    /* Third step, lexicographic sorting of the array of Team names.*/
    Quick_Sort(team_names, 0, count-1);
    
    printf("%d Melhores %d\n", NL, best);
    /* Final step, for every string on "team_names", the name gets printed and simultaneously destroyed.*/
    for (i = 0; i < count; i++){
        printf("%d * %s\n", NL, team_names[i]);
        free(team_names[i]);
    }
    /* The "team_names" array is destroyed.*/
    free(team_names);
}