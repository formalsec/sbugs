#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "match.h"
#include "hashtable.h"
#include "stack.h"
#include "list.h"

int main() {

    int lineCounter = 0;    /* keeps track of the number of commands given*/
    char command;   /* the selected command*/
    link matches;   /* linked list of matches's names*/
    tSTACK teams;   /* stack of teams*/

    STinit();
    teams = tSTACKinit();
    matches = NULL;

    do {
        scanf("%c", &command);
        if(command == 'a') {
            lineCounter++;
            matches = a(matches, teams, lineCounter);
        }
        else if(command == 'A') {
            lineCounter++;
            A(teams, lineCounter);
        }
        else if(command == 'l') {
            lineCounter++;
            l(matches, lineCounter);
        }
        else if(command == 'p') {
            lineCounter++;
            p(lineCounter);
        }
        else if(command == 'P') {
            lineCounter++;
            P(matches, teams, lineCounter);
        }
        else if(command == 'r') {
            lineCounter++;
            matches = r(matches, lineCounter);
        }
        else if(command == 's') {
            lineCounter++;
            s(lineCounter);
        }
        else if(command == 'g') {
            lineCounter++;
            g(matches, teams, lineCounter);
        }
    } while(command != 'x');
    matches = x(matches, teams);
    return 0;
}