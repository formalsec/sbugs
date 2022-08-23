#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proj_aux.h"



int main () {
    /* ponteiro para no da equipa */
    elink *heads_eq;
    /* ponteiro para no de jogos */
    jlink *heads_j;
    /* ponteiro para no da lista de jogos */
    list_j list_j;
    int nl = 1;
    char comando;

    /* inicializacao das hashtables dos jogos e equipas*/
    heads_j = init_jog();
    heads_eq = init_eq();

    /* inicializacao da lista de jogos */
    list_j.head = NULL;
    list_j.tail = NULL;

    while ((comando = getchar()) != 'x') { /* enquanto nao receber o x, entra no switch */
        switch (comando) {
            case 'a':
                executa_a(heads_j, &list_j, heads_eq, nl);
                break;
            case 'l':
                executa_l(&list_j, nl);
                break;
             case 'p':
                executa_p(heads_j, nl);  /* ERROR I DON'T UNSTERSTAND HERE */
                break;
           case 'r':
                executa_r(heads_j, &list_j, nl);
                break;
            case 's':
                executa_s(heads_j, nl);
                break;
            case 'A':
                executa_A(heads_eq, nl);
                break;
            case 'P':
                executa_P(heads_eq, nl);
                break;
/*            case 'g':
                executa_g();
                break; */
        }
        /* no fim de cada comando, nl incrementa 1 */
        nl += 1;
        getchar(); /* tirar o '\n' do input */
    }
    free_hash_eq(heads_eq);
    free_hash_jog(heads_j);
    free_list_j(&list_j);
    return 0;
}

