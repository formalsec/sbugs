#include "sistema.h"
#include <stdio.h>

/* Funcao principal do programa, chama funcoes para os diferentes comandos. */
int main() {
    Sistema *sistema = novoSistema(); /* Variavel que guarda toda a informacao da base de dados de
                                         jogos de futebol amigaveis. */
    char comando;
    int NL = 1; /* Numero da linha do comando de input. */

    while (scanf("%c", &comando) == 1) {
        switch (comando) {
            case 'a': adiciona_jogo(sistema, NL++); break;    /* comando - a */
            case 'A': adiciona_equipa(sistema, NL++); break;  /* comando - A */
            case 'l': lista_jogos(sistema, NL++); break;      /* comando - l */
            case 'p': procura_jogo(sistema, NL++); break;     /* comando - p */
            case 'P': procura_equipa(sistema, NL++); break;   /* comando - P */
            case 'r': apaga_jogo(sistema, NL++); break;       /* comando - r */
            case 's': altera_score(sistema, NL++); break;     /* comando - s */
            case 'g': encontra_equipas(sistema, NL++); break; /* comando - g */
            case 'x': destroy_sistema(sistema); return 0;     /* comando - x */
        }
    }
    return -1;
}
