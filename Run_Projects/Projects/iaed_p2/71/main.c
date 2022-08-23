#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos.h"

/***** main ******/

int main()
{
    /* Linha do input */
    int linha = 1;

    /* Le o comando */
    char comando = getchar();

    /* Inicializam-se as hash tables */
    jlink * hash_jogos = init_jogos();
    elink * hash_equipas = init_equipas();
    
    /* Inicializam-se a lista ligada para os jogos */
    Lista_Jogos lista = init_lista_jogos();
    
    while (comando != 'x')
    {
        switch (comando)
        {
            case 'a':
                comando_a(linha, hash_jogos, hash_equipas, lista);
                break;
            case 'A':
                comando_A(linha, hash_equipas);
                break;
            case 'l':
                comando_l(linha, lista);
                break;
            case 'p':
                comando_p(linha, hash_jogos);
                break;
            case 'P':
                comando_P(linha, hash_equipas);
                break;
            case 'r':
                comando_r(linha, hash_jogos, lista);
                break;
            case 's':
                comando_s(linha, hash_jogos);
                break;
            case 'g':
                comando_g(linha, hash_equipas);
                break;
            default:
                linha++;
                break;
        }
        comando = getchar();
    }

    /* Apagamos as hash tables e as listas ligadas */

    limpa_hash_eq(hash_equipas);

    limpa_hash_jogos(hash_jogos);

    destroi_jog_ligados(lista);

    return 0;
}