#include "jogos_linked.h"
#include "jogos_hash.h"
#include "equipas.h"
#include "cmds.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int val = 1;
    int * nl = &val; /*inicializacao do contador de linhas do input*/
    char c;
    JOGO_LIST * lista_de_jogos = cria_lista_jogos(); /*inicializacao da lista ligada de jogos*/
    EQUIPA ** hashtable_equipas = init_hash_table(); /*inicializacao da hashtable de equipas*/
    JOGO_HASH ** hashtable_jogos = init_hash_jogos(); /*inicializacao da hashtable de jogos*/

    while(1)
    {
        scanf("%c", &c);

        if (c != '\n')
        {
            switch(c)
            {
                case 'a':
                    command_a(nl, hashtable_jogos, lista_de_jogos, hashtable_equipas); break;
                case 'l':
                    command_l(nl, lista_de_jogos); break;
                case 'p':
                    command_p(nl, hashtable_jogos); break;
                case 'r':
                    command_r(nl, hashtable_jogos, hashtable_equipas, lista_de_jogos); break;
                case 's':
                    command_s(nl, hashtable_jogos, hashtable_equipas); break;
                case 'A':
                    command_A(nl, hashtable_equipas); break;
                case 'P':
                    command_P(nl, hashtable_equipas); break;
                case 'g':
                    command_g(nl, hashtable_equipas); break;
                case 'x':
                    command_x(hashtable_equipas, lista_de_jogos, hashtable_jogos); return 0;
            }
            *nl += 1;
        }
    }
}