#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* funcoes da hash */

int hash(char *str);

void inicializar_hash_equipas ();

void inicializar_hash_jogos ();

void liberta_memoria();

/* funcoes comando */

void adiciona_novo_jogo (char *nome, char *eq1, char *eq2, int s1, int s2);

void adiciona_nova_equipa (char *nome);

void lista_jogos ();

void procura_jogo (char *nome);

void procura_equipa (char *nome);

void apaga_jogo (char *nome);

void altera_score (char *nome, int s1, int s2);

void lista_vencedores ();

/* funcoes auxiliares */

int cstrcmp(const void *a, const void *b);

void print_jogo (int cdg);

void altera_vitorias_equipa (char *eq1, char *eq2, int s1, int s2, int est);

void incrementa_linha();