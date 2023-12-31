#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "common_code.h"

/*Returns a can_fail_malloc'd string with the same chars as the argument given*/
char *StringDup(char *string)
{
    char *new = (char *)can_fail_malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(new, string);
    return new;
}

/*Hash function used in both hashtables*/
int HashU(char *string, int M)
{
    int h = 0;
    for (; *string != '\0'; string++)
        h = (A * h + *string) % M;
    return h;
}