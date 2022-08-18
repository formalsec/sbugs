#ifndef STRUCTS_H
#define STRUCTS_H

#define MAXNOME 1024
#define MAXHASH 1657

/*
NOTA: para nao causar trocas decidi escrever os links 
para as equipas no feminino (proxima, primeira, ultima)
e para os jogos no masculino (proximo, primeiro, ultimo)
*/

typedef struct equipa
{
    char * nome;
    int total_ganhos;
} * Equipa;

typedef struct jogo
{
    char * nome;
    Equipa eq1, eq2, vencedora;
    int res1, res2;
} * Jogo;


/*******************/
/****Hash Tables****/
/*******************/

/* elink */

struct node_equipas
{
	Equipa equipa;
	struct node_equipas *proxima;
};

typedef struct node_equipas *elink;

/* jlink */
struct node_jogos
{
	Jogo jogo;
    /* proximo refere-se a hash table e 
    seguinte a lista ligada */
	struct node_jogos *proximo;
};

typedef struct node_jogos *jlink;



/********************/
/***Listas Ligadas***/
/********************/

/* jog_lig */

struct jogo_ligado
{
	Jogo jogo;
	struct jogo_ligado *seguinte;
};

typedef struct jogo_ligado* jog_lig;

typedef struct lista_ligada
{
	jog_lig primeiro;
	jog_lig ultimo;
}* Lista_Jogos;

/* eq_ligs */

struct equipa_ligada
{
	Equipa equipa;
    /* vai ser de acordo com a ordem da strcmp() */
	struct equipa_ligada *seguinte;
};

typedef struct equipa_ligada* eq_lig;

typedef struct eq_ligadas
{
	eq_lig primeira;
	eq_lig ultima;
}* Lista_Equipas;



/* Devolve a chave do link, para introduzir hash table*/
int hash(char * nome);

/* Da free() ao jogo e ao seu nome */
void FREEjogo(Jogo jogo);

/* Chama FREEjogo e da free() ao link */
void FREEjlink(jlink link);

/* Da free() a equipa e ao seu nome */
void FREEequipa(Equipa equipa);

/* Chama FREEequipa e da free() ao link */
void FREEelink(elink link);

#endif
