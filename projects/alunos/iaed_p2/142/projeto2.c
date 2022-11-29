#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eq.h"
#include "j.h"
/* Tamanho da hashtable */
#define SIZE 1013
/* Tamanho de lista de caracteres */
#define MAXIJOGO 1024

int main()
{
    char c;
    int NL=0;
    /* Hashtable de jogos */
    HashTable *ht;
    /* Hashtable de equipas */
    HashTable2 *ht_eq;
    /* Lista de jogos */
    list2 *ls = list2_create();
    ht = ht_create();
    ht_eq = ht_create_eq();
    while((c=getchar())!= 'x')
    {
        if(c=='a')
        {
            NL++;
            a(NL, ht, ht_eq, ls);
        }
        else if(c=='l')
        {
            NL++;
            l(NL, ls);
        }
        else if(c=='p')
        {
            NL++;
            p(NL, ht);
        }
        else if(c=='r')
        {
            NL++;
            r(NL, ht, ls, ht_eq);
        }
        else if(c=='s')
        {
            NL++;
            s(NL, ht, ht_eq, ls);
        }
        else if(c=='A')
        {
            NL++;
            A(NL, ht_eq);
        }
        else if(c=='P')
        {
            NL++;
            P(NL, ht_eq);
        }
        else if(c=='g')
        {
            NL++;
            g(NL, ht_eq);
        }
        else
            continue;
    }
    free_hash_table_e(ht_eq);
    free_list2(ls);
    free_hash_table_j(ht); 
    return 0;
}




