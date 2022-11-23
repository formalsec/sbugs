#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "tab_jogos.h"

/* bases arbitrarias primas entre si */
#define BASE1 31415         
#define BASE2 27183

/* funcao de dispersao para tabelas de jogos */
int disp_jogos(void *nome, int size) {
    
    char *ptr_aux = (char *) nome;
    int res = 0;
    int base1 = BASE1;             
    int base2 = BASE2;

    for (; *ptr_aux != '\0'; ptr_aux++, base1 = (base1 * base2) % size) {
        res = (res + base1 * (*ptr_aux)) % size;
    }

    return res;
}

/* retorna a chave de dispersao de jogos */
void* chave_jogos(void *j) {
    return (void *)(((jogo)(j))->nome);
}

/* insere um jogo na tabela */
void insere_tab_jogo(tab_disp tab_jogos, jogo j) {
    insere_tab(tab_jogos, (void *)j, &chave_jogos, &disp_jogos);
}

/* apaga um jogo na tabela */
void retira_tab_jogo(tab_disp tab_jogos, char *nome) {
    retira_tab(tab_jogos, (void *)nome, &disp_jogos, &jogo_nome_igual, &liberta_jogo);
}

/* liberta a memoria associada a uma tabela */
void liberta_tab_jogos(tab_disp tab_jogos) {
    liberta_tab(tab_jogos, &liberta_jogo);
}

/* procura um jogo pelo nome numa tabela, retorna NULL se nao existir */
jogo procura_tab_jogo(tab_disp tab_jogos, char *nome) {
    return (jogo) procura_tab(tab_jogos, (void *)nome, &disp_jogos, &jogo_nome_igual);
}




