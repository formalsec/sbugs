#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "equipa.h"
#include "jogo.h"
#include "comandos.h"


/*----------------------------------------------------------------------------*/
/*                              FUNCOES                                       */
/*----------------------------------------------------------------------------*/

int main() {
    /* 'le' e a lista de equipas*/
    lista_equipa le;
    /* 'lj' e a lista de jogos*/
    lista_jogos lj;
    /* 'cont' e o numero do comando de input que originou esse output*/
    int cont = 0;
    /* 'letra' e o caracter a ser lido*/
    char letra;
    /* 'ht_e' e a estrutura da hastable das equipas*/
    ht_equipas ht_e;
    /* 'ht_j' e a estrutura da hastable dos jogos*/
    ht_jogos ht_j;
    /* 'head_hash_equipas' aponta para a hashtable das equipas*/
    pequipa* head_hash_equipas;
    /* 'head_hash_jogos' aponta para a hashtable dos jogos*/
    jlink* head_hash_jogos;

    /*inicializar a estrutura e a hashtable das equipas*/
    ht_e = iniciar_tabela_equipas();
    head_hash_equipas = iniciar_hash_equipas(MAX_H_EQUIPAS);
    ht_e->hash_equipas= head_hash_equipas;

    /*inicializar a estrutura e a hastable dos jogos*/
    ht_j = iniciar_tabela_jogos();
    head_hash_jogos = iniciar_hash_jogos(MAX_J_JOGOS);
    ht_j->hash_jogos = head_hash_jogos;

    /*inicializar a lista das equipas e de jogos*/
    le = inicia_lista_equipa();
    lj = inicia_lista_jogos();


    while (scanf("%c", &letra) != EOF) {
        switch (letra) {
            case 'A':
                cont ++;
                comando_A(cont, le, ht_e);

                break;

            case 'P':
                cont ++;
                comando_P(cont, ht_e);
                break;

            case 'a':
                cont ++;
                comando_a(cont, lj, ht_j, ht_e);
                break;


            case 'l':
                cont ++;
                comando_l(cont, lj);
                break;

            case 'p' :
                cont ++;
                comando_p(cont, ht_j);
                break;


            case 's':
                cont ++;
                comando_s(cont, ht_j);
                break;

            case 'r':
                cont ++;
                comando_r(cont, ht_j, lj);
                break;

            case 'g':
                cont ++;
                comando_g(cont, le);
                break;

            case 'x':
                comando_x(le, lj, ht_e, ht_j);

                return 0;

            default:
                break;
        }

    }

    return 0;
}