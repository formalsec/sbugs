#ifndef JOGOS_H
#define JOGOS_H

/* Etrutura dos jogos. */
typedef struct jogo{
	char *nome_jogo;
	char *equipa1;
	char *equipa2;
	int score1;
	int score2;
	struct jogo *next;
}Jogo;

typedef char *Chave_j;

#define nome_jogo(a) (a->nome_jogo)
#define equipa1_j(a) (a->equipa1)
#define equipa2_j(a) (a->equipa2)
#define score1_j(a) (a->score1)
#define score2_j(a) (a->score2)
#define proximo_j(a) (a->next) 

void free_jogo(Jogo *head);
Jogo *cria_jogo(char *nome_j, char *eq1, char *eq2, int score1, int score2);


#endif /* JOGOS_H */