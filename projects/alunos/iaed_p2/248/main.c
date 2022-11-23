#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "acoes.h"

/*
 * Functions
*/

int main(){
    Lista_jogo *jogos_lista = cria_lista_jogo();
    Hashtable_jogo *jogos_hashtable = cria_hashtable_jogo(151);
    Hashtable_equipa *equipas_hashtable =cria_hashtable_equipa(151);
    int linha_input = 1;
    char comando;

    while ((comando = getchar()) != 'x'){
        if (comando == 'a'){
            getchar(); /* retira o espaco entre o comando e os dados. */
            a(jogos_lista, jogos_hashtable, equipas_hashtable, linha_input);
            linha_input++;
        }
        else if (comando == 'A'){
            getchar();
            A(equipas_hashtable, linha_input);
            linha_input++;
        }
        else if (comando == 'l'){
            l(jogos_lista, linha_input);
            linha_input++;
        }
        else if (comando == 'p'){
            getchar();
            p(jogos_hashtable, linha_input);
            linha_input++;
        }
        else if (comando == 'P'){
            getchar();
            P(equipas_hashtable, linha_input);
            linha_input++;
        }
        else if (comando == 'r'){
            getchar();
            r(jogos_lista, jogos_hashtable, equipas_hashtable, linha_input);
            linha_input++;
        }
        else if (comando == 's'){
            getchar();
            s(jogos_hashtable, equipas_hashtable, linha_input);
            linha_input++;
        }
        else if (comando == 'g'){
            g(equipas_hashtable, linha_input);
            linha_input++;
        }
    }

    /* libertar a memoria previamente alocada no fim do programa */
    liberta_hashtable_equipa(equipas_hashtable);
    liberta_hashtable_jogo(jogos_hashtable);
    liberta_lista_jogo(jogos_lista);
    return 0;
}
