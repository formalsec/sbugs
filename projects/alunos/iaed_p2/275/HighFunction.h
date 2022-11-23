#include "LowFunction.h"

void addJogo(TableJogos * table_jogos, linkJogo jogo,char *nome_jogo, char *nome_equipa1, char *nome_equipa2, int golos_equipa1,int golos_equipa2);

void addEquipa(TableEquipas * table_equipas, linkEquipa equipa,char nome_equipa[SIZE_CHAR]);

void findJogo(TableJogos * table_jogos, linkJogo jogo);

void findEquipa(TableEquipas* table_equipas, linkEquipa equipa);

void removeJogo(TableJogos* table_jogos, linkJogo jogo);

void changeScore(TableJogos* table_jogos, linkJogo jogo, int score1_aux , int score2_aux);

