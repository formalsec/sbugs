#include "hash.h"
#include "lista_jogos.h"
typedef struct tabela_jogos
{
    unsigned int num_jogos; /* numero de jogos na tabela*/
    unsigned int tamanho; /* tamanho da tabela */
    pJogo * jogos; /* os jogos */
} *pTabela_jogos;

/* prototipos ---------------------------------------------------------------------------------- */

/* cria uma tabela de jogos vazia e devolve o seu ponteiro */
pTabela_jogos inicializa_tabela_jogos();

/* adiciona um jogo 'a tabela */
void adiciona_jogo_tabela(pTabela_jogos, pJogo);

/* se o jogo existir devolve o seu ponteiro, senao, devolve NULL  */
pJogo procura_jogo_tabela(pTabela_jogos, char*);
pJogo remove_jogo_tabela(pTabela_jogos, char*);
void destroi_tabela_jogos(pTabela_jogos);