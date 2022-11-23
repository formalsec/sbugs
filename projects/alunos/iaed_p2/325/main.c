#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Estrutura_jogos.h"
#include "Hash_equipas.h"
#include "Hash_jogos.h"
#include "comandos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_JOGOS 1000   /* Tamanho da Hashtable dos jogos. */
#define TAM_EQUIPAS 1000 /* Tamanho da Hashtable das equipas. */

int main() {
    int total_equipas = 0; /* Variavel que armazena o numero total de equipas que existem. */
    int NL = 1;
    char v;                      /* Variavel que le qual e o comando que ira executar. */
    Jogos *jogos = init_Jogos(); /* Lista duplamente ligada que armazena os jogos(nome do jogo, nome
                                    das equipas e os golos de cada equipa). */
    Jogo_hash *j = init_j(TAM_JOGOS);      /*Variavel que armazena a Hashtable dos jogos. */
    Equipas_hash *e = init_e(TAM_EQUIPAS); /*Variavel que armazena a Hashtable das equipas. */
    scanf("%c ", &v);
    while (v != 'x') {
        switch (v) {
            case 'a': comando_a(jogos, j, e, TAM_JOGOS, TAM_EQUIPAS, NL++); break;
            case 'A': total_equipas = comando_A(e, TAM_JOGOS, total_equipas, NL++); break;
            case 'l': comando_l(jogos, NL++); break;
            case 'p': comando_p(j, TAM_JOGOS, NL++); break;
            case 'P': comando_P(e, TAM_JOGOS, NL++); break;
            case 'r': comando_r(jogos, j, e, TAM_JOGOS, TAM_EQUIPAS, NL++); break;
            case 's': comando_s(j, e, TAM_JOGOS, TAM_EQUIPAS, NL++); break;
            case 'g': comando_g(e, TAM_JOGOS, total_equipas, NL++); break;
        }
        scanf("%c ", &v);
    }
    destroy_jogos(j, TAM_JOGOS);
    free_Jogos(jogos);
    destroy_equipas(e, TAM_EQUIPAS);
    return 0;
}
