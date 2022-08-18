#include "Equipas.h"
#include "Jogos.h"
#include "func_hash.h"
#include "funcoes_cases.h"
#define SIZE 1009
#define MAX 1024 /*numero maximo de caracteres nos nomes de jogos/equipas eh 1023*/

int main()
{
    char c;
    int num_linhas;
    link_e *primeiras_e, lista_equipas;
    link_j *primeiros_j, lista_jogos, *fim_jogos;

    /*inicializacao das hashtables e das listas*/
    num_linhas= 0;
    lista_jogos = NULL;
    lista_equipas = NULL;
    primeiros_j = NULL;
    primeiras_e = NULL;
    fim_jogos = (link_j*)malloc(sizeof(link_j));
    *fim_jogos = NULL;

    primeiros_j = inicializa_j(primeiros_j);
    primeiras_e = inicializa_e(primeiras_e);

    while ((c = getchar()) != 'x')
    {
        switch(c)
        {
            case 'a': /*adiciona novo jogo*/
            {
                num_linhas++;
                lista_jogos = letra_a(num_linhas, primeiros_j, primeiras_e, lista_jogos, fim_jogos);
                break;
            }

            case 'A': /*adiciona nova equipa*/
            {
                num_linhas++;
                lista_equipas = letra_A(num_linhas, primeiras_e, lista_equipas);
                break;
            }

            case 'l': /*lista todos os jogos pela ordem em que foram introduzidos*/
            {
                num_linhas++;
                letra_l(num_linhas, lista_jogos);
                break;
            }
            case 'p': /*procura um jogo*/
            {
                num_linhas++;
                letra_p(num_linhas, primeiros_j);
                break;
            }
            case 'P': /*procura uma equipa*/
            {
                num_linhas++;
                letra_P(num_linhas, primeiras_e);
                break;
            }
            case 'r': /*apaga um jogo*/
            {
                num_linhas++;
                lista_jogos = letra_r(num_linhas, primeiros_j, primeiras_e, lista_jogos, fim_jogos);
                break;
            }
            case 's': /*altera a pontuacao (score) de um jogo*/
            {
                num_linhas++;
                letra_s(num_linhas, primeiros_j, primeiras_e);
                break;
            }
            case 'g': /*encontra as equipas que venceram mais jogos*/
            {
                num_linhas++;
                letra_g(num_linhas, lista_equipas);
                break;
            }

            getchar();
        }
    }

    frees_projeto(primeiros_j, primeiras_e, lista_jogos, lista_equipas);
    free(fim_jogos);
    return 0;
}



