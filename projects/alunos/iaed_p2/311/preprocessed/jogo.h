#ifndef JOGO
#define JOGO

typedef struct jogo
{
	int score1, score2;
	char *nome, *equipa1, *equipa2;
} *Jogo;

typedef struct lista_jogo
{
	Jogo jogo;
	struct lista_jogo *next;
} *link_J;

typedef link_J *hashJ;

/* a maior parte das funcoes aqui encontram-se nos slides ou sao self-explanatory*/

Jogo inicializa_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2);

int lengthJ(link_J head);

link_J NewJ(Jogo jogo);

link_J insertBeginJ(link_J head, Jogo jogo);

link_J lookupJ(link_J head, char *nome);

void free_nodeJ(link_J x);

link_J semi_deleteJ(link_J head, char *nome);

link_J deleteJ(link_J head);

void free_listaJ(link_J head);

void printNodeJ(link_J head);

void print_inverso(link_J head, int contador);

hashJ inicia_hash_jogo(int M);

hashJ insere_hash_jogo(hashJ jogos, Jogo jogo, int M);

hashJ retira_hash_jogo(hashJ jogos, char *nome, int M);

link_J procura_hash_jogo(hashJ jogos, char *nome, int M);

void free_hashJ(hashJ jogos, int M);

#endif