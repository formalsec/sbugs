#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"

/** A funcao main do programa invoca todas as funcoes responsaveis para o
 *  funcionamento de comandos individuais */ 
int main(void){
    int cmd = EOF;
    size_t count = 0;               /* inicializa contador de linhas de comando (as NL) */
    sistema* s = inic_sistema();    /* inicializa sistema do programa */
    do {
        switch (cmd = rd_cmd()){
        case 'a': cmd_a(++count, s); rd_ws(); break;
        case 'A': cmd_A(++count, s); rd_ws(); break;
        case 'p': cmd_p(++count, s); rd_ws(); break;
        case 'P': cmd_P(++count, s); rd_ws(); break;
        case 's': cmd_s(++count, s); rd_ws(); break;
        case 'l': cmd_l(++count, s); break;
        case 'r': cmd_r(++count, s); rd_ws(); break;
        case 'g': cmd_g(++count, s); break;
        }
    }while (cmd != 'x');
    free_sistema(s);                /* liberta toda a memoria correspondente ao programa */
    return EXIT_SUCCESS;
}