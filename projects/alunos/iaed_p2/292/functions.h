#ifndef functions_H
#define functions_H

/* =========== estrutura para os jogos =============*/
typedef struct Jogos{
    char *ID, *team_1, *team_2;
    int score1, score2;
    struct Jogos* next, *prev, *next_tabela;
}*games;

/* ========= estrutura para as equipas =============*/
typedef struct Equipas{
	char *ID;
	int wins;
	struct Equipas *next;
	}*teams;

/* ========= funcoes de <<table_finders>> =============*/
long int hash(char palavra[],int M);

struct Jogos *encontraJogo(struct Jogos **jogos, char nome[],\
bool print, int M, int NL,struct Jogos *false_g);

struct Equipas *encontraEquipa(struct Equipas **Team, char nome[],\
bool print, int N, int NL, struct Equipas *false_t);

void showByDate(struct Jogos *jogos, int NL);

void lista(struct Equipas **elemento, int Nequipas, int NL, int max, int N);
int FindMax(struct Equipas **games_list, int N);

/* ========= funcoes de <<table_changers>> =============*/
void Inseret(struct Jogos **jogos, struct Jogos** first, char rest[],\
int M,int NL, struct Equipas **equipas, struct Equipas *false_t, \
struct Jogos **top, struct Jogos *false_g, int N);

int InseretEquipa(struct Equipas **equipas, char ID[],int N, int NL, \
struct Equipas *false_t);

void alteraScore(struct Jogos **jogos, char resto[],int M,int NL, \
struct Equipas **equipas, struct Equipas *false_t, int N);

void deleteGame(struct Jogos **jogos,struct Jogos **tabela,char nome[],\
 struct Equipas **equipas, struct Equipas *false_t, int M, int NL, \
 struct Jogos *false_g, struct Jogos **top, int N);
 
void freeStruct(struct Jogos **head, struct Equipas **equipas, int N);

int compara_palavras(const void * a, const void * b );

#endif
