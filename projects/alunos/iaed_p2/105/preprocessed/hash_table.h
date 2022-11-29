#ifndef HASH
#define HASH
#define MAX_TABELA 1000



typedef struct jogo{
    char *nome; /*nome do jogo*/
    char *equipa1; /*nome de uma equipa*/
    char *equipa2; /*nome da equipa adversaria*/
    int score1; /*pontuacao de uma equipa*/
    int score2; /*pontuacao da equipa adversaria*/
    struct jogo* next;
}jogo;

unsigned int funcao_tabela(char *nome);
void inserir_tabela(jogo *j,jogo *tabela_hash[MAX_TABELA]);
jogo *procura_tabela(char *nome,jogo *tabela_hash[MAX_TABELA]);
void apaga_tabela(char *nome,jogo *tabela_hash[MAX_TABELA]);
void apaga_mem_jogo(jogo *tabela_hash[MAX_TABELA]);

#endif


