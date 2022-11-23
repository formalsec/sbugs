#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdlib.h>
#include "tabela_jogos.h"
#include "tabela_equipas.h"
#include "lista_j.h"

/** ? info: defines relativos ao numero maximo de caracteres dos buffers
 *  e outros dependentes do tipo estao nos ficheiros.h do tipo de dados respectivo */

/*  == Representacao do tipo estrutura de dados
 
 *  - hashtable de jogos
 *  - hashtable de equipas
 *  - lista simplesmente ligada de jogos inseridos

 *  == Fim da representacao */

/*--------------------------------------Estruturas--------------------------------------*/

/*  Estrutura do sistema de dados de jogos de futebol */
typedef struct str_sistema{
    jogos* tb_j;
    equipas* tb_e;
    lista* l;
}sistema;

/*----------------------------------Funcoes de leitura----------------------------------*/

int rd_cmd(void);           /* Le o comando feito pelo utilizador */
char rd_ws(void);           /* Verifica se ha espaco em branco e consome-o */

/*----------------------------Prototipos->Funcoes Principais----------------------------*/

/*  Inicializa sistema alocando o espaco suficiente para as tabelas e para a lista */
sistema* inic_sistema(void);

/*  Comando a: Adiciona um novo jogo ao sistema - tabela de jogos */
void cmd_a(size_t count, sistema* s);

/*  Comando l: Lista todos os jogos pela ordem em que foram introduzidos no sistema */
void cmd_l(size_t count, sistema* s);

/*  Comando p: Procura um jogo no sistema - tabela de jogos */
void cmd_p(size_t count, sistema* s);

/*  Comando r: Apaga um jogo. Remove-o definitivamente do sistema - tabela de jogos */
void cmd_r(size_t count, sistema* s);

/*  Comando s: Altera a pontuacao de um jogo afetando o numero de vitorias das equipas */
void cmd_s(size_t count, sistema* s);

/*  Comando A: Adiciona uma nova equipa ao sistema - tabela de equipas */
void cmd_A(size_t count, sistema* s);

/*  Comando P: Procura uma equipa no sistema - tabela de equipas */
void cmd_P(size_t count, sistema* s);

/*  Comando g: Encontra as equipas que venceram mais jogos */
void cmd_g(size_t count, sistema* s);

/*  Liberta toda memoria alocada no programa */
void free_sistema(sistema* s);

#endif
