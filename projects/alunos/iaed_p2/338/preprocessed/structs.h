#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct jogos{
	char *nome;
	char *equipa1;
	char *equipa2;
	int score1;
	int score2;
}*jogo;

typedef struct equipas {
	char *nome_equipa;
	int vitorias;
} *equipa;

typedef struct nodes{
	char *nome_jogo;
	struct nodes *link;
} *node;

typedef struct tuple{
	int max_vitorias;
	int conta_eq_c_max_vit;
} *tuplio;
#endif