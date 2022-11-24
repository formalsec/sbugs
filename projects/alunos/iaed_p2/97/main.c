#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include "proj2.h"

int main() {
    /* Caracter correspondente a funcao desejada e argumentos para as funcoes */
    /* (Vetores de tamanho MAX_STR + 1, para contar com o '\0') */
    char a1[MAX_STR + 1], a2[MAX_STR + 1], a3[MAX_STR + 1];
    int s, a4, a5, NL = 1; /* NL: contador da linha de comando */
    /* Declaracao e inicializacao das listas de jogos e de equipas */
    lista *jogos_ordem = cria_lista_jogos();
    lista **jogos = incializa_tabela_jogo();
    elem_eq **equipas = incializa_tabela_equipa();
    /* Segunda condicao de paragem */
    while ((s = getchar()) != EOF) {
        /* Interpretador dos casos dados */
        switch (s) {
            case 'a':
                /* scanf com limitador MAX_STR */
                scanf(" %" CHR(MAX_STR) "[^:\n]:%" CHR(MAX_STR) "[^:\n]:%"
                      CHR(MAX_STR) "[^:\n]:%d:%d", a1, a2, a3, &a4, &a5);
                novo_jogo(jogos, &jogos_ordem, equipas, NL, a1, a2, a3, a4, a5);
                break;
            
            case 'A':
                scanf(" %" CHR(MAX_STR) "[^:\n]", a1);
                nova_equipa(equipas, NL, a1);
                break;
            
            case 'l':
                LDL_jogos(&jogos_ordem, NL);
                break;
            
            case 'p':
                scanf(" %" CHR(MAX_STR) "[^:\n]", a1);
                procura_jogo(jogos, NL, a1);
                break;
            
            case 'P':
                scanf(" %" CHR(MAX_STR) "[^:\n]", a1);
                procura_equipa(equipas, NL, a1);
                break;
            
            case 'r':
                scanf(" %" CHR(MAX_STR) "[^:\n]", a1);
                apaga_jogo(jogos, &jogos_ordem, equipas, NL, a1);
                break;
            
            case 's':
                scanf(" %" CHR(MAX_STR) "[^:\n]:%d:%d", a1, &a4, &a5);
                altera_sc_jogo(jogos, equipas, NL, a1, a4, a5);
                break;

            case 'g':
                equipas_maior_pontuacao(equipas, NL);
                break;

            case 'x':
                /* Primeira condicao de paragem */
                apaga_todos_dados(jogos, &jogos_ordem, equipas);
                return 0;
            
            default:
                break;
        }
        /* Aumento do contador NL */
        NL++;
        getchar();
    }
    return 0;
}