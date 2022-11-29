#ifndef STRUCTURES_H
#define STRUCTURES_H


/*#####################################################################*/
/*	ESTRUTURAS														   */
/*#####################################################################*/

typedef struct struct_node_jogo{
	struct struct_node_jogo *next, *previous;
	char* nomeJogo;
	char* nomeEquipa1;
	char* nomeEquipa2;
	int resultado1;
	int resultado2;
}nodeJogo;

typedef struct struct_node_equipa{
	struct struct_node_equipa *next, *previous;
	char* nomeEquipa;
	int vitorias;
}nodeEquipa;

typedef struct struct_list_jogo{
	nodeJogo *head, *last;
}listJogo;

typedef struct struct_list_equipa{
	nodeEquipa *head, *last;
}listEquipa;


/*#####################################################################*/
/*	PROTOTIPOS														   */
/*#####################################################################*/

int __a__(listJogo *jogos, listEquipa *equipas, int NL);	/* adiciona um novo jogo */
int __A__(listEquipa *equipas, int NL);	/* adiciona uma nova equipa */
int __l__(listJogo *jogos, int NL);	/* lista todos os jogos pela ordem em que foram introduzidos */
int __p__(listJogo *jogos, int NL);	/* procura um jogo */
int __P__(listEquipa *equipas, int NL);	/* procura uma equipa */
int __r__(listJogo *jogos, listEquipa *equipas, int NL);	/* apaga um jogo */
int __s__(listJogo *jogos, listEquipa *equipas, int NL);	/* altera a pontuacao (score) de um jogo */
int __g__(listEquipa *equipas, int NL);	/* encontra as equipas que venceram mais jogos */
listJogo* mkListJogo();		/* Cria a Lista dos Jogos */
listEquipa* mkListEquipa();	/* Cria a Lista das Equipas */
void freeNodeJogo(nodeJogo* n);		/* Liberta um no da lista dos Jogos */
void freeNodeEquipa(nodeEquipa* n);	/* Liberta um no da lista das Equipas */
void freeListJogo(listJogo* l);		/* Liberta a lista inteira dos Jogos */
void freeListEquipa(listEquipa* l);	/* Liberta a lista inteira das Equipas */
void removeNodeJogo(listJogo* l, nodeJogo* n);	/* Remove um no da lista de Jogos */
void removeNodeEquipa(listEquipa* l, nodeEquipa* n);	/* Remove um no da lista de Equipas */
void addNodeJogo(listJogo* l, const char* _nomeJogo, const char* _nomeEquipa1, const char* _nomeEquipa2, int _resultado1, int _resultado2); /* Adiciona um novo no no fim da lista de Jogos */
void addNodeEquipa(listEquipa* l, const char* _nomeEquipa); /* Adiciona um novo no no fim da lista de Equipas */
nodeJogo* searchListJogo(listJogo *lstJogo, char* _nomeJogo);	/* Procura um no na lista de Jogos */
nodeEquipa* searchListEquipa(listEquipa *lstEquipa, char* _nomeEquipa);	/* Procura um no na lista de Equipas */
int existJogo(listJogo *lstJogo, char* _nomeJogo);	/* Verifica se o jogo existe */
int existEquipa(listEquipa *lstEquipa, char* _nomeEquipa);	/* Verifica se a equipa existe */

/*#####################################################################*/

#endif /* STRUCTURES_H */