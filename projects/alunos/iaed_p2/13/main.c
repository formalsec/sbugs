#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include "games.h"
#include "hash.h"
#include "list.h"



int main() {
    int c, count = 1;

    HASHinit();

    c = getchar();

    do {
        if(c == 'a') addGame(count++);
        else if (c == 'A') addTeam(count++);
        else if (c == 'l') listGames(count++);
        else if (c == 'p') searchGame(count++);
        else if (c == 'P') searchTeam(count++);
        else if (c == 'r') deleteGame(count++);
        else if (c == 's') changeScore(count++);
        else if (c == 'g') mostSuccessfulTeams(count++);

    } while ((c = getchar())!='x');

    clean();

    return 0;
}