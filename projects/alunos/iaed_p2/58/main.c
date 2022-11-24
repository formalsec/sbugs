#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogos.h"
#include "LISTAS.h"
#include "HASHTABLES.h"

int main () {
    int NL = 1;
    int i;
    int unsigned NJ = 0; /* numeros de jogos introduzidos no sistema */
    unsigned int M = 1000; /* inicializacao do tamanho da tabela de dispersao */
    char c ='b'; /* inicializacao com um comando inexistente no sistema */
    
    link_jogo Jogos_head = NULL; /* inicializacao da cabeca da lista de jogos a NULL */
    pJogo *tab_dispersao = NULL; /* tabela de ponteiros de jogos */
    link_equipa tab_equipas[MAX_TAB]; /* tabela de equipas */

    /* inicializacao da tabela de equipas*/
    for(i = 0; i < MAX_TAB; i++)
        tab_equipas[i] = NULL; /* inicializo tudo a NULL */

    tab_dispersao = init_tab_dispersao(M);

    while (c != 'x') {
        switch (c = getchar()) {
            case 'a':
                /* quando a tabela de dispersao atinge metade da carga, o seu tamanho e duplicado */
                if(NJ >= M/2) {
                    M = 2*M ;
                    tab_dispersao = expande(tab_dispersao, M);
                }
                Jogos_head = AdicionaJogo(tab_equipas, tab_dispersao, Jogos_head, NL, M, &NJ);
                NL++;
                break;

            case 'A':
                AdicionaEquipa(tab_equipas, NL);
                NL++;
                break;

            case 'l':
                ListaJogos(Jogos_head, NL);
                NL++;
                break;

            case 'p':
                ProcuraJogo(tab_dispersao, NL, M);
                NL++;
                break;  

            case 'P':
                ProcuraEquipa(tab_equipas, NL);
                NL++;
                break;

            case 'r':
                Jogos_head = ApagaJogo(tab_equipas, tab_dispersao, Jogos_head, M, NL, &NJ);
                NL++;
                break;

            case 's':
                AlteraPontuacao(tab_equipas, tab_dispersao, NL, M);
                NL++;
                break;
    
            case 'g':
                EquipasVencedoras(tab_equipas, NL);
                NL++;
                break;
        }
    }
    /* libertacao de memoria */
    free_tab_dispersao(tab_dispersao, M);

    free_tab_equipas(tab_equipas);
    
    free_jogos_lista(Jogos_head);

    return 0;
}