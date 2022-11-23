#ifndef PROJ2
#define PROJ2

/* Inclusao das funcoes para gestao das equipas e jogos */
#include "tab_equipas.h"
#include "tab_jogos.h"

/* Funcoes usadas para colocar limites no scanf */
#define CHR_AUX(X) #X
#define CHR(X) CHR_AUX(X)

/* Tamanho maximo de strings */
#define MAX_STR 1023

/* Auxiliar: Elimina toda a memoria asssociada aos jogos e as equipas */
void apaga_todos_dados(lista **jogos, lista **jogos_ordem, elem_eq **equipas);

/* Adiciona um novo jogo ao sistema (comando 'a') */
void novo_jogo(lista **j, lista **j_o, elem_eq **e, int NL,
               char *nome, char *eq1, char *eq2, int sc1, int sc2);

/* Adiciona uma nova equipa ao sistema (comando 'A') */
void nova_equipa(elem_eq **e, int NL, char *nome);

/* Lista todos os jogos, pela ordem em que foram introduzidos (comando 'l') */
void LDL_jogos(lista **j_o, int NL);

/* Procura um jogo no sistema, dado o nome (comando 'p') */
void procura_jogo(lista **j, int NL, char *nome);

/* Procura um jogo no sistema, dado o nome (comando 'P') */
void procura_equipa(elem_eq **e, int NL, char *nome);

/* Apago um jogo do sistema, dado o nome (comando 'r') */
void apaga_jogo(lista **j, lista **j_o, elem_eq **e, int NL, char *nome);

/* Auxiliar: altera o numero de jogos ganhos das equipas */
void altera_ganhos_equipas(int sc1, int sc2, int ant1, int ant2,
                                    elem_eq *aux1, elem_eq *aux2);

/* Altera o score de um jogo, dado o nome (comando 's') */
void altera_sc_jogo(lista **j, elem_eq **e, int NL, char *nome, 
                                                    int sc1, int sc2);

/* Auxiliar: compara str1 com str2 */
int compara(const void *str1, const void *str2);

/* Lista as equipas que ganharam mais jogos lexicograficamente (comando 'g') */
void equipas_maior_pontuacao(elem_eq **e, int NL);

#endif