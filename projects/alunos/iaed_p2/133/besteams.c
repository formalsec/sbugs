#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*including the functions that handle teams*/
#include "teams.h"
/*including the functions that handle the best teams*/
#include "besteams.h"
/*including the functions shared from every auxiliary file*/
#include "shared.h"



/*000000000000000000000000000000000
00000000000000000000000000000000000

    init_list_teams

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*initializing the list of best teams*/
void init_list_teams(char **best_teams, int N)
{
    int i; 
    /*for every indice of the list*/
    for(i = 0; i<N; i++)
    {
        /*pointing them all to NULL*/
        best_teams[i] = NULL; 
    }
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    clear_list_teams

00000000000000000000000000000000000
0000000000000000000000000000000000*/

/*clear the list so it can be used again*/
void clear_list_teams(char **best_teams, int N)
{
    char *i;
    int j;
    /*for every none NULL pointer in the list*/
    for(j=0; best_teams[j]!=NULL && j<N; j++)
    {
        /*free the memory space used*/
        i=best_teams[j];
        free(i);
        best_teams[j]=NULL;
    }
}






/*000000000000000000000000000000000
00000000000000000000000000000000000

    search_and_add_teams_list

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*search in the list teams every team that has a certain nummber of victories*/
void search_and_add_teams_list(teams **lst_teams, char **best_teams, int number)
{
    teams *i;
    int j, n=0;
    /*for every linked list in the hash teams*/
    for(j=0; j<517; j++)
    {
        /*for every pointer in the linked list*/
        for(i = lst_teams[j]; i!=NULL; i = i->next)
        {
            /*if the number of victories of the team matches with the name given*/
            if(i->games_w == number)
            {
                /*if so adding it to the list of best teams*/
                best_teams[n] = strduplicate(i->name);
                n++;
            }
        }
    }
}






/*000000000000000000000000000000000
00000000000000000000000000000000000

    free_list_teams

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*free the memory space used by the list*/
void free_list_teams(char **best_teams)
{
    int j;
    /*for every element of the list*/
    for(j=0; j<100 && best_teams[j]!=NULL; j++)
    {
        free(best_teams[j]);
    }
    /*free the list*/
    free(best_teams);
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    print_best_teams

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*print the bst teams accordingly*/
void print_best_teams(char **best_teams, int nl, int max)
{
    int i=0;
    /*if there is at least one team*/
    if(best_teams[0]!=NULL)
    {
        printf("%d Melhores %d\n", nl, max);
    }
    
    /*for every team in the list of best teams*/
    for(; best_teams[i]!=NULL; i++)
    {
        printf("%d * %s\n", nl, best_teams[i]);
    }
}






/*000000000000000000000000000000000
00000000000000000000000000000000000

    cmpstrings

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*auxiliary function for the qsort*/
int cmpstrings(const void*a, const void*b)
{
    char **str1, **str2;
    str1=(char **)a;
    str2=(char **)b;
    return strcmp(*str1, *str2);
}




/*000000000000000000000000000000000
00000000000000000000000000000000000

    sort_the_list
    
00000000000000000000000000000000000
000000000000000000000000000000000*/

/*sorting the list*/
void sort_the_list(char **best_teams)
{
    int j=0, n=0;
    for(; best_teams[j] != NULL; j++)
    {
        /*knowing the number of best teams*/
        n++;
    }
    /*if there is more than one best team*/
    if(n>1)
    {
        /*sorting the list*/
        qsort(best_teams, n, sizeof(char *), cmpstrings);
    }
    
}
