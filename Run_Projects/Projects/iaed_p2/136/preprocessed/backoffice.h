#include "hash.h"
#include "jogo.h"
#include "equipa.h"
#include "gestao.h"
#include "arvore.h"

/* PROTOTIPOS DAS FUNCOES - EXECUCAO DOS COMANDOS */

/* funcao que executa o comando a - criar um novo jogo */
void executa_a(int nL, fila jogos, fila equipas, fila jogos_ord);
/* funcao que executa o comando A - criar uma nova equipa */
void executa_A(int nL, fila equipas, fila equipas_ord);
/* funcao que executa o comando l - listar os jogos pela ordem de criacao */
void executa_l(int nL, fila jogos_ord);
/* funcao que executa o comando p - procurar um jogo */
void executa_p(int nL, fila jogos);
/* funcao que executa o comando P - procurar uma equipa */
void executa_P(int nL, fila equipas); 
/* funcao que executa o comando r - apagar um jogo */
void executa_r(int nL, fila jogos, fila jogos_ord);
/* funcao que executa o comando s - alterar o score de um jogo */
void executa_s(int nL, fila jogos);
/* funcao que executa o comando g - listar as equipas com mais vitorias */
void executa_g(int nL, fila equipas_ord);

