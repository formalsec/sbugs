#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Comandos.h"
#include "Estruturas.h"
#define MIL_VINTE_QUATRO 1024   /* Tamanho maximo do nome de uma equipa e jogo */
#define VALOR_HASH 10000        /* Numero utilizado na funcao de hash */

/* Funcao principal */
int main() {
    lista_equipas * conj_equipas;
    lista_equipas_aux * conj_equipas_aux;
    lista_jogos * conj_jogos;
    lista_jogos_aux * conj_jogos_aux;
    int a = 0, nl = 1;
    char c;
    conj_equipas = malloc(sizeof(lista_equipas));
    inicia_lista_equipas(conj_equipas);

    conj_equipas_aux = malloc(sizeof(lista_equipas_aux));
    inicia_lista_equipas_aux(conj_equipas_aux);

    conj_jogos = malloc(sizeof(lista_jogos));
    inicia_lista_jogos(conj_jogos);

    conj_jogos_aux = malloc(sizeof(lista_jogos_aux));
    inicia_lista_jogos_aux(conj_jogos_aux);

    c = getchar();
    while (1){
        if (c == 'x') { /* Em caso de x, liberta toda a memoria e acaba o programa */
            free_geral(conj_equipas, conj_equipas_aux, conj_jogos, conj_jogos_aux);
            break;
        }
        direciona(c, nl, conj_equipas, conj_equipas_aux, conj_jogos, conj_jogos_aux);
        a++;
        if (a % 2 == 0){ /* O nl so incrementa a cada duas vezes que passa neste ciclo */
            nl++;
        }
        c = getchar();
    }
    return 0;
}