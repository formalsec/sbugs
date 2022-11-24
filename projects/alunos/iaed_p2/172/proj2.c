#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "structs.h"

/* Adds a new Game to the system */
void a(int NL, int M, Game *stg, Team *stt, link *head, link *tail) {
    Game g;
    Team t;
    char name[MAX_Char], t1[MAX_Char], t2[MAX_Char];;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]", name, t1, t2);

    if (STsearchG(name, M, stg) == NULL) {
        if (STsearchT(t1, M, stt) != NULL && STsearchT(t2, M, stt) != NULL) {
            g = NewGame(head, tail, name, t1, t2);
            STinsertG(g, M, stg);
            /* gives a win to the team that won */
            if (g->s1 > g->s2) {
                t = STsearchT(t1, M, stt);
                t->wins += 1;
            }
            if (g->s1 < g->s2) {
                t = STsearchT(t2, M, stt);
                t->wins += 1;
            }
        }
        else
            printf("%d Equipa inexistente.\n", NL);
    }
    else
        printf("%d Jogo existente.\n", NL);
}

/* Adds a new Team to the system */
void A(int NL, int M, Team *stt, Team *head) {
    Team t;
    char name[MAX_Char];
    scanf(" %[^:\n]", name);

    if (STsearchT(name, M, stt) == NULL) {
        t = NewTeam(name, head);
        STinsertT(t, M, stt);
    }
    else
        printf("%d Equipa existente.\n", NL);
}

/* Prints every Game in the system */
void l(int NL, link *head) {
    PrintGame(head, NL);
}

/* Searches for a Game */
void p(int NL, int M, Game *stg) {
    Game g;
    char name[MAX_Char];
    scanf(" %[^:\n]", name);

    g = STsearchG(name, M, stg);
    if (g)
        printf("%d %s %s %s %d %d\n", NL, g->name, g->t1, g->t2, g->s1, g->s2);
    else
        printf("%d Jogo inexistente.\n", NL);
}

/* Searches for a Team */ 
void P(int NL, int M, Team *stt) {
    Team t;
    char name[MAX_Char];
    scanf(" %[^:\n]", name);

    t = STsearchT(name, M, stt);
    if (t)
        printf("%d %s %d\n", NL, t->name, t->wins);
    else
        printf("%d Equipa inexistente.\n", NL);
}

/* Deletes a Game */
void r(int NL, int M, Game *stg, Team *stt, link *head, link *tail) {   
    Game g;
    Team t;
    char name[MAX_Char];
    scanf(" %[^:\n]", name);

    g = STsearchG(name, M, stg);
    if (g) {
        if (g->s1 > g->s2) { /* Removes the win from the team */
            t = STsearchT(g->t1, M, stt);
            t->wins -= 1;
        }
        else if (g->s1 < g->s2) {
            t = STsearchT(g->t2, M, stt);
            t->wins -= 1;
        }
        RemoveGame(head, tail, name);
        STdeleteG(name, M, stg);
    }
    else
        printf("%d Jogo inexistente.\n", NL);
}

/* Changes the score of a Game */
void s(int NL, int M, Game *stg, Team *stt) {
    int s1, s2;
    Game g;
    Team t1, t2;
    char name[MAX_Char];
    scanf(" %[^:\n]:%d:%d", name, &s1, &s2);

    g = STsearchG(name, M, stg);
    if (g) {
        if (g->s1 > g->s2 && s1 < s2) {
            t1 = STsearchT(g->t1, M, stt);
            t1->wins -= 1;
            t2 = STsearchT(g->t2, M, stt);
            t2->wins += 1;
        }
        else if (g->s1 < g->s2 && s1 > s2) {
            t1 = STsearchT(g->t1, M, stt);
            t1->wins += 1;
            t2 = STsearchT(g->t2, M, stt);
            t2->wins -= 1;
        }
        else if (g->s1 == g->s2 && s1 < s2) {
            t2 = STsearchT(g->t2, M, stt);
            t2->wins += 1;
        }
        else if (g->s1 == g->s2 && s1 > s2) {
            t1 = STsearchT(g->t1, M, stt);
            t1->wins += 1;
        }
        else if (g->s1 > g->s2 && s1 == s2) {
            t1 = STsearchT(g->t1, M, stt);
            t1->wins -= 1;
        }
        else if (g->s1 < g->s2 && s1 == s2) {
            t2 = STsearchT(g->t2, M, stt);
            t2->wins -= 1;
        }
        g->s1 = s1;
        g->s2 = s2;
    }
    else
        printf("%d Jogo inexistente.\n", NL);
}

/* Function used by qsort to sort the Teams, by comparing two strings */
int compare(const void *a, const void *b) {
    const char *A = *(const char **)a; 
    const char *B = *(const char **)b;
    return strcmp(A, B);
}

/* Finds and prints the Teams with the most wins in a lexicographic order */
void g(int NL, Team *head) {
    int i, teams = 0;
    int *lst;
    char **sort;
    Team aux = *head;
    
    if (aux == NULL)
        return;
    lst = (int*)can_fail_malloc(sizeof(int)*2);
    lst = MaxWins(head, lst);
    sort = (char**)can_fail_malloc(sizeof(char*)*lst[1]);
    while (aux != NULL) {
        if (aux->wins == lst[0]) {
            sort[teams++] = aux->name;
        }
        aux = aux->next;
    }
    if (teams > 0) {
        qsort(sort, teams, sizeof(char*), compare);
        printf("%d Melhores %d\n", NL, lst[0]);
        for (i = 0; i < teams; i++)
            printf("%d * %s\n", NL, sort[i]);
    }
    free(lst);
    free(sort);
}

/* Ends the program and Frees the Hashtables, the Teams and the Games */
void x(link *head, link *tail, Team *thead, Game *stg, Team *stt) {
    link gaux;
    Team taux;
    link j = *head; 
    Team t = *thead; 

    while (j != NULL) {
        gaux = j->next;
        FreeGame(j->g);
        free(j);
        j = gaux;
    }
    while (t != NULL) {
        taux = t->next;
        FreeTeam(t);
        t = taux;
    }
    free(tail);
    free(stg);
    free(stt);
    free(head);
    free(thead);
}

/* Main function of the program */
int main() {
    int NL = 1, M = h_size;
    char c;
    Game *stg = NULL;
    Team *stt = NULL;
    Team *thead = (Team*)can_fail_malloc(sizeof(Team));
    link *ghead = (link*)can_fail_malloc(sizeof(link));
    link *gtail = (link*)can_fail_malloc(sizeof(link));
    *thead = NULL;
    *ghead = NULL;
    *gtail = NULL;
    stg = STinitG(M);
    stt = STinitT(M);

    /* Cicle do... while... that gets a command,
        and calls the function corresponding to it, 
        until it gets the command 'x', which ends the program */
    do {
        c = getchar();
        switch (c) {
            case 'a':
                a(NL, M, stg, stt, ghead, gtail);
                NL++;
                break;
            case 'A':
                A(NL, M, stt, thead);
                NL++;
                break;
            case 'l':
                l(NL, ghead);
                NL++;
                break;    
            case 'p':
                p(NL, M, stg);
                NL++;
                break;
            case 'P':
                P(NL, M, stt);
                NL++;
                break;
            case 'r':
                r(NL, M, stg, stt, ghead, gtail);
                NL++;
                break;    
            case 's':
                s(NL, M, stg, stt);
                NL++;
                break;
            case 'g':
                g(NL, thead);
                NL++;
                break;
        }
    }   while (c != 'x');
    x(ghead, gtail, thead, stg, stt);
    return 0;
}
