#ifndef AUX_file
#define AUX_file

void escreve_jogo(int * nl, JOGO * jogo);

void remove_jogo(JOGO_HASH ** hashtable_jogos, JOGO_LIST * lista_de_jogos, char * nome);

void destroy_jogos(JOGO_HASH ** hashtable_jogos, JOGO_LIST * lista_de_jogos);

void cria_lista_nomes(char ** lista_nomes, EQUIPA ** hashtable_equipas, int maior_score);

int compara_nomes(const void *equipa1, const void *equipa2);

#endif