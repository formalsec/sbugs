#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "teams.h"
#include "commands.h"

int main()
{
    int cont = 1, nl = 1;
    char buf[4096] = "";
    teamList *t = NULL;
    gameList *g = NULL;

    while(cont)
    {
        fgets(buf, 4095, stdin);
        switch(buf[0])
        {
            case 'a':
                command_a(buf + 2, &t, &g, nl);
                nl++;
                break;

            case 'A':
                command_A(buf + 2, &t, nl);
                nl++;
                break;

            case 'l':
                command_l(&g, nl);
                nl++;
                break;

            case 'p':
                command_p(buf + 2, &g, nl);
                nl++;
                break;

            case 'P':
                command_P(buf + 2, &t, nl);
                nl++;
                break;

            case 'r':
                command_r(buf + 2, &g, nl);
                nl++;
                break;

            case 's':
                command_s(buf + 2, &g, nl);
                nl++;
                break;

            case 'g':
                command_g(&t, nl);
                nl++;
                break;
            
            case 'x':
                cont = 0;
                break;

            default:
                printf("%d Comando inexistente.\n", nl);
                nl++;
                break;
        }
    }

    freeTeams(t);
    freeGames(g);

    return 0;
}