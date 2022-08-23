#ifndef STRUCT
#define STRUCT

#define MAXINPUT 1024

/*estrutura que representa uma equipa*/
/*equipas organizadas numa hash*/ 
typedef struct{
	char *nome;
	int ganhos;
}equipa;

/*estrutura que representa um jogo*/
/*jogos organizados numa linked list*/
typedef struct jogo{
	char *nome;
	/*ponteiro para as duas equipas*/
	equipa *equipa1, *equipa2;
	int score1, score2;
	/*ant -> estrutura anterior na lista*/
	/*next -> proxima estrutura na lista*/
	struct jogo *next, *ant;
}jogo;

/*variaves globais*/
int NL;
equipa **hash_e;

/*funcoes do programa*/
int hash(char *str);
void createHash();
void destroyHash();
int A();
void insert(equipa *aux);
void expand();
int procuraEquipa(char *nome);
void printHash();
void P();
int a();
void createJogos();
void destroyJogos();
void l();
jogo* procurarJogo(char *nome);
void r();
void p();
void s();
void troca(equipa **array, int pai, int filho);
void heapify(equipa **array, int t, int i);
void g();

#endif