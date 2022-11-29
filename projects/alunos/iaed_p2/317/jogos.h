#include "equipas.h" /*necessario para a estrutura do jogo*/

typedef struct {

	char *nome; /*nome do jogo*/
	Equipa *e1; /*ponteiro para a equipa 1*/
	Equipa *e2; /*ponteiro para a equipa 2*/
	int s1; /*score da equipa 1*/
	int s2; /*score da equipa 2*/
} Jogo;

/* node para a hashtable de jogos e para a lista ligada de jogos do sistema*/
typedef struct node_jogo {
	Jogo *jogo;
	struct node_jogo *next;
} *JHnode;

typedef struct jogos_sistema{
	JHnode head;
	JHnode tail;
}Jogos_sistema;

int JH_hash(char *v, int M);
void inicializa_jogos_hash(JHnode *Jhash);
Jogo *JHsearch(JHnode *Jhash, char *nome);
void JHinsert(JHnode *Jhash, Jogo *jogo);
void JHdelete(JHnode *Jhash, char *nome);
void inicializa_jogos_sistema(Jogos_sistema *jogos_sis);
void JSinsert(Jogos_sistema *jogos_sis, Jogo *jogo);
void JSdelete(Jogos_sistema *jogos_sis, char *nome);
void free_jogo(Jogo *jogo);
void free_jogos_sis(Jogos_sistema *jogos_sis);
