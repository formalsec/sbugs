#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"

/*
*************************************************
*                                               *
*                  FUNCAO MAIN                  *
*                                               *
*************************************************
*/
/*Funcao Principal que vai correr todo o programa, como um Menu*/
int main()
{
    char caracter;
    int NL= 0;
    /*Criacao de uma lista duplamente ligada de jogos*/
    jogos *lista_jogos = mk_list_jg();
    /*Criacao de uma hash para os jogos*/
    node ** table = get_hashtables();
    /*Criacao de uma hash para as equipas*/
    e_node ** equipas = get_hashtable_equipa();

    /*Ciclo de verificacao de comandos, que recebe o primeiro caracter do input. Termina coma tecla 'x'*/
    while((caracter =getchar()) != 'x')
    {
        /*Variavel que vai incrementando um valor int com cada ciclo, para determinar o numero da linha*/
        NL++;
        switch(caracter)
        {
            case 'a':
                a_comando(lista_jogos,table, equipas, NL);
                break;
            case 'l':
                l_comando(lista_jogos, NL);
                getchar();
                break;
            case 'p':
                p_comando(table, NL);
                break;
            case 'r':
                r_comando(lista_jogos,table, equipas, NL);
                break;
            case 's':
                s_comando(table, equipas,NL);
                break;
            case 'A':
                A_comando(equipas,NL);
                break;
            case 'P':
                P_comando(equipas, NL);
                break;
            case 'g':
                g_comando(equipas, NL);
                getchar();
                break;
        }
    }
    /*Libertacao de todas a memoria criada ao longo do programa*/
    free_all(lista_jogos, table, equipas);
    return 0;
}