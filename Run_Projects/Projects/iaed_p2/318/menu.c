#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heads.h"
/* Funcao principal que chama as outras funcoes dependendo do input */
int main(void)
{
    char comando = ' '; /*Comando inicializado "vazio"*/
    int NL = 1;         /*NL --> Numero do comando executado (efeitos de debug)*/
    int HT_tam = 1889;  /* Tamanho das hashtables */
    list_jogos *jogos = mk_list();
    list_equipas *teams = mk_list_eq();
    HT_jogos *HT_jogos = makeHTJ(HT_tam);
    HT_equipas *HT_equipas = makeHTE(HT_tam);

    while (comando != 'x')
    {
        scanf("%c", &comando);

        if (comando == 'a') /*Adiciona um novo jogo ao sistema*/
        {
            add_jovo(NL, jogos, HT_jogos, HT_equipas, HT_tam);
            NL = NL + 1;
        }
        if (comando == 'l') /* Lista os jogos por ordem de introducao no sistema */
        {
            lista_jogos(NL, jogos);
            NL = NL + 1;
        }
        if (comando == 'p') /*Verifica se um certo jogo existe no sistema*/
        {
            procura_jogo(NL, HT_jogos, HT_tam);
            NL = NL + 1;
        }
        if (comando == 'r') /*Apaga um certo jogo do sistema*/
        {
            apaga_jogo(NL, jogos, HT_jogos, HT_equipas, HT_tam);
            NL = NL + 1;
        }
        if (comando == 's') /*Altera o resultado de um jogo no sistema*/
        {
            altera_score(NL, HT_jogos, HT_equipas, HT_tam);
            NL = NL + 1;
        }
        if (comando == 'A') /*Adiciona uma nova equipa ao sistema*/
        {
            add_equipa(NL, teams, HT_equipas, HT_tam);
            NL = NL + 1;
        }
        if (comando == 'P') /*Verifica se uma dada equipa esta registada no sistema*/
        {
            procura_equipa(NL, HT_equipas, HT_tam);
            NL = NL + 1;
        }
        if (comando == 'g') /*Verifica as equipas com maior numero de jogos ganhos*/
        {
            encontra_equipas(NL, teams);
            NL = NL + 1;
        }
    }
    freeHTE(HT_equipas, HT_tam); /*Libertar a memoria da hashtable das equipas*/
    freeHTJ(HT_jogos, HT_tam);   /*Libertar a memoria da hashtable dos jogos*/
    free_list_equipas(teams);    /*Libertar a memoria da lista ligada das equipas*/
    free_list_jogos(jogos);      /*Libertar a memoria da lista ligada dos jogos*/

    return 0;
}