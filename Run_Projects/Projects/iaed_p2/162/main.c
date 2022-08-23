#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"
#include "routines.h"

#define GSIZE 47
#define TSIZE 47


/* Main function that recieves the instructions to several actions */
int main(){
    int NL = 0;
    char comando;
    gametable table_g = InitGameTable(GSIZE);
    teamstable table_t = InitTeamTable(TSIZE);
    while((comando = getchar()) != EOF){
        switch (comando) {
            case 'a':
                ++NL;
                __a__(&table_t, &table_g, NL);
                break;
            case 'l':
                ++NL;
                __l__(&table_g, NL);
                break;
            case 'p':
                ++NL;
                __p__(&table_g, NL);
                break;
            case 'r':
                ++NL;
                __r__(&table_g, NL);
                break;
            case 's':
                ++NL;
                __s__(&table_g, NL);
                break;
            case 'A':
                ++NL;
                __A__(&table_t, NL);
                break;
            case 'P':
                ++NL;
                __P__(&table_t, NL);
                break;
            case 'g':
                ++NL;
                __g__(&table_t, NL);
                break;
            case 'x':
                __x__(&table_t, &table_g);
                return 0;
        }
    }
    return 0;
}
