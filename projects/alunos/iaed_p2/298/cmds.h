#ifndef CMDS_file
#define CMDS_file

void command_a(int * nl, JOGO_HASH ** hashtable_jogos, 
                    JOGO_LIST * lista_de_jogos, EQUIPA ** hash_equipas);

void command_l(int * nl, JOGO_LIST * lista_de_jogos);

void command_A(int * nl, EQUIPA ** hashtable_equipas);

void command_P(int * nl, EQUIPA ** hashtable_equipas);

void command_p(int * nl, JOGO_HASH ** hashtable_jogos);

void command_r(int * nl, JOGO_HASH ** hashtable_jogos, 
                    EQUIPA ** hashtable_equipas, JOGO_LIST * lista_de_jogos);

void command_s(int * nl, JOGO_HASH ** hashtable_jogos, EQUIPA ** hashtable_equipas);

void command_g(int * nl, EQUIPA ** hashtable_equipas);

void command_x(EQUIPA ** hashtable_equipas, JOGO_LIST * lista_de_jogos, 
                    JOGO_HASH ** hashtable_jogos);

#endif 