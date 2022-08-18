#include "hash.h"
#include <stdio.h>
#define M 1777   /* tamanho da hashtable (numero de indices) */


int main(){
    pListas* listas = {0};
    pLst_Ord lista_ordenada = {0};
    char c;
    int NL = 0;  /* indica o numero da linha do input */
    listas = inicializa_listas(listas, M);
    lista_ordenada = inicializa_lista_ordenada(lista_ordenada);
    while ((c = getchar()) != 'x'){
        switch(c){
            case 'A':
                NL++;
                adiciona_equipa(NL, listas, lista_ordenada, M);
                break;
            case 'P':
                NL++;
                consulta_equipa(NL, listas, M);
                break;
            case 'a':
                NL++;
                adiciona_jogo(NL, listas, lista_ordenada, M);
                break;
            case 'p':
                NL++;
                consulta_jogo(NL, listas, M);
                break;
            case 'l':
                NL++;
                jogos_ordenados(NL, lista_ordenada);
                break;
            case 'r':
                NL++;
                remove_jogo(NL, listas, lista_ordenada, M);
                break;
            case 's':
                NL++;
                altera_pontuacao(NL, listas, M);
                break;
            case 'g':
                NL++;
                ordena_equipas_vitorias(NL, lista_ordenada);
                break;
        }
        while (c != '\n')
            c = getchar();
    }
    free_listas(listas, M);
    free_lista_ordenada(lista_ordenada);
    return 0;
}