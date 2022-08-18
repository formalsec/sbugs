#include <stdio.h>
#include "comandos.h"

/******************************************************************************
 * Constantes:
******************************************************************************/

/* O numero maximo de caracteres de um nome (mais caracter '/0'). */
#define MAX_NOME 1024

/******************************************************************************
 * Main:
******************************************************************************/

int main() {
    /*********************** Variaveis locais gerais *************************/

    /* Variavel local que armazena o caracter (de um comando) do standard input,
    e determina a acao a realizar. */
    char caracter;

    /* Variavel local onde e' armazenada a linha de input que esta a ser lida. */
    int linha = 1;

    /************************ Variaveis locais jogos *************************/

    /* Variavel local onde e' armazenada a lista duplamente ligada com os jogos 
    existentes. */
    List *jogos1 = mk_list();

    /* Variavel local onde e' armazenada a tabela de dispersao por procura 
    linear, onde e' feita a procura de jogos. */
    Lp *jogos2 = mk_lp(53);

    /*********************** Variaveis locais equipas ************************/

    /* Variavel local onde e' armazenada a arvore binaria com as equipas 
    existentes. */
    Bt *equipas1 = mk_bt();

    /* Variavel local onde e' armazenada a tabela de dispersao por procura 
    linear, onde e' feita a procura de equipas. */
    Lp *equipas2 = mk_lp(31);

    /******************************** Switch *********************************/

    while ((caracter = getchar()) != 'x' && caracter != EOF) {
        switch (caracter) {
            case 'a':
                adiciona_jogo(&jogos1, &jogos2, &equipas1, &equipas2, linha);
                break;
            case 'A':
                adiciona_equipa(&equipas1, &equipas2, linha);
                break;
            case 'l':
                lista_jogos(&jogos1, linha);
                break;
            case 'p':
                procura_jogo(&jogos2, linha);
                break;
            case 'P':
                procura_equipa(&equipas2, linha);
                break;
            case 'r':
                apaga_jogo(&jogos1, &jogos2, &equipas1, &equipas2, linha);
                break;
            case 's':
                altera_score(&jogos2, &equipas1, &equipas2, linha);
                break;
            case 'g':
                encontra_equipas(&equipas1, linha);
                break;
            default:
                linha++;
                break;
        }
    }
    liberta_estruturas(jogos1, jogos2, equipas1, equipas2);

    return 0;
}
