#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "TABELA_HASH_E.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************************************
*							  FUNCOES AUXILIARES DOS JOGOS                                     *
***********************************************************************************************/


/* Liberta o espaco na memoria alocado na criacao do jogo */
void free_Jogo(Jogo *n)
{
	free(n->nome);
	free(n->eqcasa);
	free(n->eqfora);
	free(n);
}


/* Liberta o espaco na memoria alocado na criacao da lista de jogos */
void free_listJ(listJogos *l)
{
	while (l->primeiro) 
	/* Percorre a lista ate nao haver mais jogos */
	{
		Jogo *temp = l->primeiro->proximo;
		free_Jogo(l->primeiro);
		l->primeiro = temp;
	}

	free(l);
}

/* Dado um nome verifica se esse jogo esta na hash table correspondente. */
/* Devolve 0 se sim, 1 se nao.                                           */
int verifica_j(Tabela_hash *calendario, const char *nome)
{
	const size_t i = hash(nome, calendario->capacidade);	  /* i = no correspondente */
	No_hash *no;
	for (no=calendario->topos[i]; no != NULL; no=no->proximo) /* Percorre os jogos do no */
		if (strcmp(no->pont_jogo->nome, nome)==0)
			return 0;
	return 1;
}


/* Aloca espaco na memoria para uma lista (linked list) de jogos e inicializa os atributos */
listJogos* cria_listJogos()
{
	listJogos *jogos = can_fail_malloc(sizeof(listJogos));
	jogos->primeiro = NULL;
	jogos->ultimo = NULL;
	return jogos;
}



/* Aloca espaco para cada atributo e substitui pela informacao dada.
Constroi ou aumenta a lista de jogos e adiciona o jogo na hash table correspondente. */
void cria_Jogo(listJogos *jogos, const char *nome, const char *casa, const char *fora, \
	int g_casa, int g_fora, Tabela_hash *calendario)
{
	const size_t i = hash(nome, calendario->capacidade);
	Jogo *novo = can_fail_malloc(sizeof(Jogo));

	novo->nome = can_fail_malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(novo->nome, nome);
	novo->eqcasa = can_fail_malloc(sizeof(char)*(strlen(casa)+1));
	strcpy(novo->eqcasa, casa);
	novo->eqfora = can_fail_malloc(sizeof(char)*(strlen(fora)+1));
	strcpy(novo->eqfora, fora);
	novo->golos_casa = g_casa;
	novo->golos_fora = g_fora;

	novo->anterior = jogos->ultimo;
	novo->proximo = NULL;
	if (jogos->ultimo)  					/* Se existe um jogo na lista */
		jogos->ultimo->proximo = novo;
	else 
		jogos->primeiro = novo;				/* Se nao, passa a ser o primeiro elemento */
	jogos->ultimo= novo;
	calendario->topos[i]= cria_Jogo_hash(calendario->topos[i], novo); /* Atualiza o no */

}
/* Aloca espaco para o novo jogo no no'(da hash table) correspondente. */
No_hash *cria_Jogo_hash(No_hash *ultimo, Jogo *novo_J)
{
	No_hash *nn = can_fail_malloc(sizeof(No_hash));
	nn->pont_jogo = novo_J;
	nn->proximo = ultimo;
	return nn;
}

/* Remove o jogo dado da linked list correspondente */
void rm_jogo(listJogos *lista_jogos, Jogo *jogo)
{
	if (jogo->anterior == NULL)						/* Caso seja primeiro elemento */
		lista_jogos->primeiro = jogo->proximo;
	else
		jogo->anterior->proximo = jogo->proximo;
	if (jogo->proximo == NULL)						/* Caso seja ultimo elemento */
		lista_jogos->ultimo = jogo->anterior;
	else
		jogo->proximo->anterior = jogo->anterior;
	free_Jogo(jogo);
}
/***********************************************************************************************
*							  FUNCOES PRINCIPAIS DOS JOGOS                                     *
***********************************************************************************************/

/* Adiciona um novo jogo onde ambas as equipas existam e recebe um nome unico. */
/* (Comando a) */
void adiciona_jogo(listJogos *lista_jogos, Tabela_hash *calendario, Tabela_hash *tabela,\
 int contador)
{
	char nome[MAX_NOME], casa[MAX_NOME], fora[MAX_NOME];
	int g_casa, g_fora;

	getchar();
	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, casa, fora, &g_casa, &g_fora);
	/* Se alguma das condicoes se verificar, a adicao do novo jogo nao e valida */
	if (verifica_j(calendario, nome)==0)
	{	
		printf("%d Jogo existente.\n", contador);
		return;
	}
	if ((verifica_e(tabela, casa)==1) || (verifica_e(tabela, fora)==1))
	{
		printf("%d Equipa inexistente.\n", contador);
		return;
	}
	
	cria_Jogo(lista_jogos, nome, casa, fora, g_casa, g_fora, calendario);
	/* O vencedor recebe um ponto (caso haja vitoria) */
	if (g_casa > g_fora)
		aumenta_pontos(tabela, casa);
	if (g_casa < g_fora)
		aumenta_pontos(tabela, fora);

}


/* Imprime todos os jogos por ordem de insercao, caso nao exista nenhum jogo nao imprime nada. */
/* (Comando l) */
void lista_todos_jogos(listJogos *lista_jogos, int contador)
{
	Jogo *jogo;
	/* Se a lista nao tem nenhum jogo */
	if (lista_jogos->primeiro == NULL)
		return;

	for (jogo = lista_jogos->primeiro; jogo != NULL; jogo=jogo->proximo)
		printf("%d %s %s %s %d %d\n", contador, jogo->nome, jogo->eqcasa, jogo->eqfora, \
			jogo->golos_casa, jogo->golos_fora);
}


/* Procura um jogo com o nome dado. */
/* (Comando p) */
void procura_jogo(Tabela_hash *calendario, int contador)
{
	char nome[MAX_NOME];
	No_hash *no;

	getchar();
	scanf("%[^:\n]", nome);
	if(verifica_j(calendario, nome) == 1)
		printf("%d Jogo inexistente.\n", contador);
	else 
	{
		const size_t i = hash(nome, calendario->capacidade); 
		/* Percorre o no ate encontrar o respetivo jogo */
		for (no=calendario->topos[i]; no != NULL; no=no->proximo) 
			if (strcmp(no->pont_jogo->nome, nome)==0)
			{
				printf("%d %s %s %s %d %d\n",contador,no->pont_jogo->nome, no->pont_jogo->eqcasa,\
					no->pont_jogo->eqfora, no->pont_jogo->golos_casa, no->pont_jogo->golos_fora);
				return;
			}
	}

}

/* Apaga um jogo dado um nome, tanto da linked list como da hash table. */
/* (Comando r) */
void apaga_jogo(Tabela_hash *calendario,Tabela_hash *tabela, listJogos *lista_jogos, int contador)
{
	char nome[MAX_NOME];
	No_hash *jogo, *ant;
	long int i;

	getchar();
	scanf("%[^:\n]", nome);
	i = hash(nome, calendario->capacidade);
	jogo=calendario->topos[i];
	if (verifica_j(calendario, nome)==1)
	{
		printf("%d Jogo inexistente.\n", contador);
		return;
	}

	/* Jogo na primeira posicao do no e' o escolhido */
	if(jogo != NULL && (strcmp(jogo->pont_jogo->nome, nome)==0))
	{
		/* Atribuicao anterior de pontos e' eliminada */
		if (jogo->pont_jogo->golos_casa > jogo->pont_jogo->golos_fora)
			retira_pontos(tabela, jogo->pont_jogo->eqcasa);
		if (jogo->pont_jogo->golos_casa < jogo->pont_jogo->golos_fora)
			retira_pontos(tabela, jogo->pont_jogo->eqfora);

		rm_jogo(lista_jogos, jogo->pont_jogo); /* Remove da linked list */
		calendario->topos[i]=jogo->proximo;    /* Primeiro elemento e agora o proximo */
		free(jogo);                            
		return;
	}
	else 
		while(jogo != NULL && (!strcmp(jogo->pont_jogo->nome, nome)==0))
		/* Enquanto nao e o jogo, guarda o jogo anterior */
		{
			ant = jogo;
			jogo = jogo->proximo;
		}
	/* Ajusta os pontos anteriormente atribuidos */
	if (jogo->pont_jogo->golos_casa > jogo->pont_jogo->golos_fora)
			retira_pontos(tabela, jogo->pont_jogo->eqcasa);
	if (jogo->pont_jogo->golos_casa < jogo->pont_jogo->golos_fora)
			retira_pontos(tabela, jogo->pont_jogo->eqfora);

	rm_jogo(lista_jogos, jogo->pont_jogo); 	   /* Remove da linked list */
	ant->proximo = jogo->proximo;			   /* Mantem a ordem/ligacao entre os jogos */
	free(jogo);								   
	
}

/* Altera o score de um jogo dado o nome. */
/* (Comando s) */
void altera_resultado(Tabela_hash *calendario, Tabela_hash *tabela, int contador)
{
	char nome[MAX_NOME];
	No_hash *jogo;
	int score_casa, score_fora;

	getchar();
	scanf("%[^:\n]:%d:%d", nome, &score_casa, &score_fora);
	if(verifica_j(calendario, nome) == 1)
		printf("%d Jogo inexistente.\n", contador);
	else 
	{
		const size_t i = hash(nome, calendario->capacidade);
		for (jogo=calendario->topos[i]; jogo != NULL; jogo=jogo->proximo)
			/* Percorre a lista ate encontrar o jogo */
			if (strcmp(jogo->pont_jogo->nome, nome)==0)
			{
				altera_pontos(tabela, jogo, score_casa, score_fora);
						/* Atribui os novos scores */
				jogo->pont_jogo->golos_casa = score_casa;
				jogo->pont_jogo->golos_fora = score_fora;
			}

	}
}



/* Altera os pontos das equipas devido a mudanca do score do jogo. */
void altera_pontos(Tabela_hash *tabela, No_hash *jogo, int score_casa, int score_fora)
{
/* Analisa todas as situacoes possiveis e ajusta as novas pontuacoes */
	if (jogo->pont_jogo->golos_casa > jogo->pont_jogo->golos_fora)
	{
					/* Equipa da casa ganhava antes */
		if (score_casa < score_fora)
		{
			retira_pontos(tabela, jogo->pont_jogo->eqcasa);
			aumenta_pontos(tabela, jogo->pont_jogo->eqfora);
		}
		else if (score_casa == score_fora)
			retira_pontos(tabela, jogo->pont_jogo->eqcasa);
	}
	else if (jogo->pont_jogo->golos_casa < jogo->pont_jogo->golos_fora)
	{
					/* Equipa de fora ganhava antes */
		if (score_casa > score_fora)
		{
			aumenta_pontos(tabela, jogo->pont_jogo->eqcasa);
			retira_pontos(tabela, jogo->pont_jogo->eqfora);
		}
		else if(score_casa == score_fora)
		{
			retira_pontos(tabela, jogo->pont_jogo->eqfora);
		}
	}
	else if (jogo->pont_jogo->golos_casa == jogo->pont_jogo->golos_fora)
	{
						/* Equipas empataram */
		if (score_casa > score_fora)
			aumenta_pontos(tabela, jogo->pont_jogo->eqcasa);
		else if(score_casa < score_fora)
			aumenta_pontos(tabela, jogo->pont_jogo->eqfora);
	}
}
