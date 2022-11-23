#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#include "backoffice.h"

/* NOTA: uma tabela e um ponteiro para a sua primeira posicao, por isso aceder-
    -lhe diretamente ou atraves do ponteiro e (em termos de eficacia) mesma coisa. 
    No entanto, a diferenca e a eficiencia -> quando passarmos como parametro vamos
    usar apenas 8 bytes e nao os 8 * MAX_DIM da tabela toda */

int main()
{
    struct str_list teamHash[MAX_DIM]; /* tabela de dispersao das equipas */
    fila equipas = teamHash; /* ponteiro para a tab. dispersao das equipas */

    struct str_list gameHash[MAX_DIM]; /* tabela de dispersao dos jogos */
    fila jogos = gameHash; /* ponteiro para a tab. dispersao dos jogos */

    struct str_list jogosOrd[UNIT_FILA]; /* fila ordenada dos jogos - comando l */
    fila jogos_ord = jogosOrd; /* ponteiro para a fila ordenada dos jogos */

    struct str_list equipasOrd[UNIT_FILA]; /* fila ordenada das equipas - comando g */
    fila equipas_ord = equipasOrd; /* ponteiro para a fila ordenada das equipas */

    /* linha do input / flag de controlo de execucao */
    int nL = 0, flag = EXECUTA; 
    
    /* inicializacao da memoria */
    inicializa(equipas, jogos, jogos_ord, equipas_ord);

    while(flag == EXECUTA) /* enquanto a flag mandar executar ... */
    {
        int comando = getchar(); /* le o comando */
        nL++; /* incrementa a linha de input */

        /* seleciona a operacao correta para cada comando inserido */
        switch(comando)
        {
            case 'a': /* inserir um jogo */
                executa_a(nL, jogos, equipas, jogos_ord); /* executa o comando a */
                break;
            case 'A': /* inserir uma equipa */
                executa_A(nL, equipas, equipas_ord); /* executa o comando A */
                break;
            case 'l': /* listar os jogos pela ordem de introducao */            
                executa_l(nL, jogos_ord); /* executa o comando l */
                break;
            case 'p': /* procurar um jogo */
                executa_p(nL, jogos); /* executa o comando p */
                break;
            case 'P': /* procurar uma equipa */    
                executa_P(nL, equipas); /* executa o comando P */
                break;
            case 'r': /* apagar um jogo */
                executa_r(nL, jogos, jogos_ord); /* executa o comando r*/
                break;
            case 's': /* alterar o score de um jogo */
                executa_s(nL, jogos);
                break;
            case 'g': /* encontra as equipas que venceram mais jogos */
                executa_g(nL, equipas_ord);
                break;
            case 'x':
                flag = NAO_EXECUTA; /* indica que nao se pedem mais comandos */
        }
        getchar(); /* le o '\n' introduzido */
    }
    /* libertacao da memoria */
    liberta(equipas, jogos, jogos_ord, equipas_ord);
    return EXIT_SUCCESS;
}

