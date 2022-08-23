#ifndef EQUIPA
#define EQUIPA
/* Define o numero de espacos no qual os elementos contidos no vetor definido na estrutura equipa se vao dividir */
#define TODAS_EQUIPAS_ELEMENTOS_NUM 1000
/* EQUIPAS */
/* Criacao da equipa e especificacao da varias funcionalidades no programa */
/* Criacao da estrutura equipa */
struct Equipa
{
	char* nome;
	int jogos_ganhos;
	struct Equipa *next;
};

/* Criacao da estrutura que contem todas as equipas */
struct TodasEquipas
{
	/* A primeira equipa (ou vetor com espacos nulos se nao houver nenhuma equipa) */
	struct Equipa *elementos[TODAS_EQUIPAS_ELEMENTOS_NUM];
	int num_equipas;
	/* Vetor ordenado de elementos das equipas */
	struct Equipa **vetor;
};
/* strings presentes na hashtable da equipa so podem ter ate 1023 caracteres */
int hashequipa(char nome[1024]);
/* Funcao que adiciona uma nova equipa ao sistema */
void adicionaequipa(struct TodasEquipas *equipas, int num_comandos);
/* Funcao que procura uma equipa no sistema atraves do nome e retorna nao so a equipa mas tambem o numero de jogos que ela ganhou */
void procuraequipa(struct TodasEquipas *equipas, int num_comandos);
/* Funcao que procura e lista por ordem alfabetica as equipas com maior numero de jogos ganhos */
void encontravitoriosos(struct TodasEquipas *equipas, int num_comandos);

#endif
