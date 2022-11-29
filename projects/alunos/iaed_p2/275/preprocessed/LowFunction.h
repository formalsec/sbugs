#define SIZE_HASH 5281  
/*Maximo de caracteres do nome de um jogo e do nome das equipas*/
#define SIZE_CHAR 1023


typedef struct node{
	char *nome;
	struct node *next;
	int wins;
}*linkEquipa;

typedef struct nodejogo{
	char *nome, *equipa1, *equipa2;
	struct nodejogo *next;
	int score1, score2;
}*linkJogo;

typedef struct table_equipa{
	linkEquipa *headsEquipa;
	int M;
}TableEquipas;

typedef struct table_jogo{
	linkJogo *headsJogo;
	int M;
}TableJogos;


typedef char* Key;

linkEquipa NEWequipa(char* new_equipa);

linkJogo NEWjogo(char* new_jogo, char* new_equipa1, char* new_equipa2, int new_score1, int new_score2);

linkEquipa insertBeginListEquipa(linkEquipa head, char* name);

linkJogo insertBeginListJogo(linkJogo head, char *jogo_nome, char *equipa1_nome, char *equipa2_nome, int resultado1, int resultado2);

linkEquipa searchListEquipa(linkEquipa head, char* name);

linkJogo searchListJogo(linkJogo head, char* name);

linkEquipa removeFromListEquipa(linkEquipa head, char* name);

linkJogo removeFromListJogo(linkJogo head, char* name);

linkJogo insertEnd(linkJogo head, char *jogo_nome, char *equipa1_nome, char *equipa2_nome, int resultado1, int resultado2);

int hash(char *v);

void freeEquipa(linkEquipa a);

void freeJogo(linkJogo a);

void printEquipa(linkEquipa a);

void printJogo(linkJogo a);

TableEquipas*  STinitEquipa();

TableJogos*  STinitJogo();

void STinsertEquipa(char *nome, TableEquipas* table_equipas);

void STinsertJogo(TableJogos* table_jogos, char *jogo_nome, char *equipa1_nome, char *equipa2_nome, int resultado1, int resultado2);

void STdeleteEquipa(linkEquipa equipa, TableEquipas* table_equipas);

void STdeleteJogo(linkJogo jogo, TableJogos* table_jogos);

linkEquipa STsearchEquipa(Key v, TableEquipas* table_equipas);

linkJogo STsearchJogo(Key v, TableJogos* table_jogos);
