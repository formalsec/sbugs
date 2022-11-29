#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "geral.h"
#include "structs.h"

#define M_HASH 1001

int main()
{
    int comando;
    int cont=1;

    table_eq tab_eq;
    table_jogos tab_j;

    listagem lst;
    lst = list();

    tab_eq = Init_eq(M_HASH);
    tab_j = Init_jogo(M_HASH);

    while((comando=getchar())!=EOF)
    {
        switch(comando)
        {
            case 'a':
                a(cont,tab_eq,tab_j,lst);
                break;
            case 'l':
                l(cont,lst);
                break;
            case 'p':
                p(cont,tab_j);
                break;
            case 'r':
                r(cont,tab_j,tab_eq,lst);
                break;
            case 's':
                s(cont,tab_j,tab_eq);
                break;
            case 'A':
                A(cont,tab_eq);
                break;
            case 'P':
                P(cont,tab_eq);
                break;
            case 'g':
                g(cont,tab_eq);
                break;
            case 'x':
                liberta_hash_eq(tab_eq);
                liberta_hash_j(tab_j);
                free(lst);
                break;
        }
        cont++;
        getchar();
    }
    return 0;
}