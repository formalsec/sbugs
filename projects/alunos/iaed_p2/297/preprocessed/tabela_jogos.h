#ifndef TABELA_JOGOS_H
#define TABELA_JOGOS_H
#include <stdlib.h>

#define INIC_CAP_J   1013           /*  Capacidade da tabela dos jogos */
#define MAX_NAMEJ_SZ 1023           /*  Numero maximo de caracteres do nome do jogo */    
#define INVALID_J    -1             /*  Indicacao de que algo nao pertence a esta representacao */

/*  Verifica igualdade entre strings */
#define equal_j(A, B) strcmp(A, B) == 0

/*  == Representacao do tipo estrutura de dados
 
 *  - hashtable de procura linear cujos elementos sao estruturas de jogo
 *  - organizados de acordo com a sua hash
 *  - referencia o proprio pointer do jogo

 *  == Fim da representacao */

/*------------------------------------Estruturas------------------------------------*/

/*  Estrutura de um jogo */
typedef struct str_jogo{
    char* nome, *equipa1, *equipa2;
    size_t score1, score2;
}jogo;

/*  Estrutura da tabela de jogos */
typedef struct h_t_jogos{
    jogo** tb;
    size_t capacidade, sz;
}jogos;

/*--------------------------Prototipos->Funcoes Principais--------------------------*/

/*  Inicializa tabela de jogos alocando o espaco suficiente */
jogos* inic_jogos(size_t max);

/*  Cria um jogo dadas as suas caracteristicas alocando o espaco necessario */
jogo* make_jogo(const char* nome, const char* neq1, const char* neq2,
                size_t s1, size_t s2);

/*  Procura um jogo. Se nao existir retorna NULL, caso contrario a hash do j */
int procura_j(const char* nome, jogos* tb_j);

/*  Aloca o espaco necessario e insere a string dada.
 *  Devolve o ponteiro correspondente */
char* insere_str(const char* esp);

/*  Adiciona um jogo a tabela de acordo com as suas caracteristicas */
jogos* insere_j(jogo* j, jogos* tb_j);

/*  Remove um jogo da tabela libetando toda a memoria respetiva dele.
 *  Reinsere todos os jogos que estejam em posicoes consecutivas */
void remove_jogo(size_t hash, jogos* tb_j);

/*  Liberta toda a memoria alocada dos jogos e da tabela */
void free_jogos(jogos* tb_j);

#endif