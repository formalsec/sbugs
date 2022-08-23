#ifndef JOGO_H
#define JOGO_H

/* Estrutura de um jogo */
typedef struct jg {
    char *nome; /* Nome do jogo */
    Equipa equipa1; /* Ponteiro para a equipa 1 */
    Equipa equipa2; /* Ponteiro para a equipa 2 */
    int score1; /* Score da equipa 1 */
    int score2; /* Score da equipa 2 */
} *Jogo;


/*------------------------| Prototipos das funcoes |--------------------------------------*/

Jogo novo_jogo(char* nome, Equipa eq1, Equipa eq2, int score1, int score2);
char* nome_jogo(Jogo jg);
void escreve_jogo(Jogo jg, int NL);
Equipa vencedor_jogo(Jogo jogo);
void atualiza_scores_jg(Jogo jg, int score1, int score2);
void apaga_jogo(Jogo jogo);


#endif