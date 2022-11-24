#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct equipa
{
	char* nome;
	int nJogos;
}Equipa;

typedef struct score
{
	int n1;
	int n2;
}Score;

typedef struct jogo
{
	char* nome;
	Equipa* equipa1;
	Equipa* equipa2;
	Score* resultado;
}Jogo;

typedef struct no
{
	void* info;
	struct no* Prox;
}NO;

typedef struct no No;

typedef struct Lista
{
	NO* Inicio;
	int NEL;
}Lista;

char* corrigeString(char* c)
{
	char* string = (char*)can_fail_malloc(sizeof(char) * (strlen(c) + 1));
	strcpy(string, c);
	return string;
}

NO* criarNo(void *info)
{
	NO* P = (NO*)can_fail_malloc(sizeof(NO));
	P->Prox = NULL;
	P->info = info;
	return P;
}

Lista* criarLista()
{
	Lista* L = (Lista*)can_fail_malloc(sizeof(Lista));
	L->Inicio = NULL;
	L->NEL = 0;
	return L;
}

void inserirNoFimDaLista(Lista* L, void* info)
{
	NO* P;
	NO* aux;
	if (!L) return;
	P = criarNo(info);

	if (!L->Inicio)
	{
		L->Inicio = P;
		return;
	}

	aux = L->Inicio;
	while (aux->Prox)
	{
		aux = aux->Prox;
	}

	aux->Prox = P;

	
}

Score* criarScore(int n1, int n2)
{
	Score* Res = (Score*)can_fail_malloc(sizeof(Score));
	Res->n1 = n1;
	Res->n2 = n2;
	return Res;
}

Equipa* criarEquipa(char* nome)
{
	Equipa* E = (Equipa*)can_fail_malloc(sizeof(Equipa));
	E->nome = nome;
	E->nJogos = 0;
	return E;
}

Jogo* criarJogo(char* nome, Equipa* equipa1, Equipa* equipa2, Score* resultado)
{
	Jogo* J = (Jogo*)can_fail_malloc(sizeof(Jogo));
	J->equipa1 = equipa1;
	J->equipa2 = equipa2;
	J->nome = corrigeString(nome);
	J->resultado = resultado;
	return J;
}

void mostrarScore(void* P)
{
	Score* S = (Score*)P;
	printf("%d %d", S->n1, S->n2);
}

void mostrarEquipa(void* P, int NL)
{
	Equipa* E = (Equipa*)P;
	printf("%d %s %d", NL,  E->nome, E->nJogos);
}

void mostrarJogo(void* P, int NL)
{
	Jogo* J = (Jogo*)P;
	printf("%d %s %s %s %d %d ", NL, J->nome, J->equipa1->nome, J->equipa2->nome, J->resultado->n1, J->resultado->n2);
}

void mostrarLista(Lista* L, void (*func)(void*, int), int NL)
{
	NO* P;
	if (!L) return;
	P = L->Inicio;
	while (P)
	{
		(*func)(P->info, NL);
		printf("\n");
		P = P->Prox;
	}
}

Equipa* procurarEquipa(Lista* L, char* nome)
{
	Equipa* equipa1;
	No* aux;
	if (!L) return NULL;
	if (!L->Inicio) return NULL;
	aux = L->Inicio;
	while (aux)
	{
		equipa1 = (Equipa*)aux->info;
		if (strcmp(equipa1->nome, nome) == 0)
			return equipa1;
		aux = aux->Prox;
	}
	return NULL;

}

int quemGanhou(Score* res)
{
	if (res->n1 > res->n2)
		return 0; /*Equipa da esquerda*/
	if (res->n2 > res->n1)
		return 1; /*Equipa da direita*/
	else
		return 2; /*Empate*/
}

Jogo* procurarJogo(Lista* L, char* nome)
{
	No* aux;
	Jogo* jogo1;
	if (!L) return NULL;
	if (!L->Inicio) return NULL;
	aux = L->Inicio;
	while (aux)
	{
		jogo1 = (Jogo*)aux->info;
		if (strcmp(jogo1->nome, nome) == 0)
			return jogo1;
		aux = aux->Prox;
	}
	return NULL;

}

void LibertaNoJogo(NO* P)
{
	Jogo* jogo1 = (Jogo*)P->info;
	free(jogo1->nome);
	free(jogo1->resultado);
	free(jogo1);
}

int equipaMaisJogosGanhos(Lista* L)
{
	No* P;
	Equipa* E;
	int maior;
	if (!L) return -1;
	if (!L->Inicio) return -1;
	maior = 0;
	P = L->Inicio;
	while (P)
	{
		E = (Equipa*)P->info;
		if (maior < E->nJogos)
			maior = E->nJogos;
		P = P->Prox;
	}
	return maior;
}

void mostrarEquipaNJogosGanhos(Lista* L, int n, int NL)
{
	Equipa* E;
	No* P;
	if (!L) return;
	if (!L->Inicio) return;
	printf("%d Melhores %d\n", NL, n);
	P = L->Inicio;
	while (P)
	{
		E = (Equipa*)P->info;
		if (E->nJogos == n)
		{
			printf("%d * %s", NL, E->nome);
			printf("\n");
		}
		P = P->Prox;
	}

}

void actualizarResultados(Lista* LJ, Lista* LE)
{
	Equipa* E;
	Jogo* J;
	No* P;
	int n;
	if (!LE) return;
	if (!LE->Inicio) return;
	if (!LJ) return;
	if (!LJ->Inicio) return;
	/*Inicializar tudo a 0's*/
	P = LE->Inicio;
	while (P)
	{
		E = (Equipa*)P->info;
		E->nJogos = 0;
		P = P->Prox;
	}

	P = LJ->Inicio;
	while (P)
	{
	    J = (Jogo*)P->info;
		n = quemGanhou(J->resultado);
		if (n == 0)
		{
			J->equipa1->nJogos++;
		}
		else if (n == 1)
		{
			J->equipa2->nJogos++;
		}
		P = P->Prox;
	}
}

void eliminarNoListaJogos(Lista* L, Jogo* J)
{
	No* P;
	No* Antes;
	Jogo* aux;
	if (!L) return;
	if (!L->Inicio) return;
	P = L->Inicio;
	Antes = P;
	aux = (Jogo*)P->info;

	if (strcmp(aux->nome, J->nome) == 0)
	{
		L->Inicio = P->Prox;
		LibertaNoJogo(P);
		free(P);
		return;
	}

	while (P)
	{
		aux = (Jogo*)P->info;
		if (strcmp(aux->nome, J->nome) == 0)
			break;
		Antes = P;
		P = P->Prox;
	}

	if (!P) return;

	Antes->Prox = P->Prox;
	LibertaNoJogo(P);
	free(P);
}

int main()
{
	int score1;
	int score2;
	Score* res;
	Equipa* equipa1;
	Equipa* equipa2;
	Jogo* jogo1;
	int n;
	int NL = 0;
	char buffer[200];
	char* string;
	char* token;
	char* nome;
	Lista* Lista_Jogos = criarLista();
	Lista* Lista_Equipas = criarLista();
	


	do
	{
		actualizarResultados(Lista_Jogos, Lista_Equipas);
		scanf(" %[^\n]", buffer);
		string = corrigeString(buffer);
		/*a - Adiciona um novo jogo   Formato de entrada: a nome:equipa1:equipa2:score1:score2*/
		if (string[0] == 'a')
		{
			token = strtok(string, " ");

			token = strtok(NULL, ":"); /*Le nome*/
			nome = token;
			jogo1 = procurarJogo(Lista_Jogos, nome);
			if (jogo1)
			{
				printf("%d Jogo existente.", NL);
				NL++;
				continue;
			}
			token = strtok(NULL, ":"); /*Le equipa1*/
			equipa1 = procurarEquipa(Lista_Equipas, token);
			if (!equipa1)
			{
				printf("%d Equipa inexistente.\n", NL);
				continue;
			}
			token = strtok(NULL, ":"); /*Le equipa2*/
			equipa2 = procurarEquipa(Lista_Equipas, token);
			if (!equipa2)
			{
				printf("%d Equipa inexistente.\n", NL);
				continue;
			}
			token = strtok(NULL, ":"); /*Le score1*/
			score1 = atoi(token);
			token = strtok(NULL, ":"); /*Le score2*/
			score2 = atoi(token);
			res = criarScore(score1, score2);
			jogo1 = criarJogo(nome, equipa1, equipa2, res);
			inserirNoFimDaLista(Lista_Jogos, jogo1);

			
		}
		/*l - Lista todos os jogos introduzidos.*/
		if (string[0] == 'l')
		{
			mostrarLista(Lista_Jogos, mostrarJogo, NL);
		}
		/*p - Procura um jogo com o nome dado.*/
		if (string[0] == 'p')
		{
			token = strtok(string, " ");
			token = strtok(NULL, " ");
			jogo1 = procurarJogo(Lista_Jogos, token);
			if (!jogo1)
			{
				printf("%d Jogo inexistente.", NL);
				printf("\n");
				NL++;
				continue;
			}
			mostrarJogo(jogo1, NL);
			printf("\n");
		}
		/*r - Apaga um jogo dado um nome.*/
		if (string[0] == 'r')
		{
			token = strtok(string, " ");
			token = strtok(NULL, " ");
			nome = corrigeString(token);
			jogo1 = procurarJogo(Lista_Jogos, nome);
			if (!jogo1)
			{
				printf("%d Jogo inexistente.", NL);
				printf("\n");
				NL++;
				continue;
			}
			eliminarNoListaJogos(Lista_Jogos, jogo1);

		}
		/*s - Altera o score de um jogo dado o nome.*/
		if (string[0] == 's')
		{
			token = strtok(string, " ");

			token = strtok(NULL, ":");
			jogo1 = procurarJogo(Lista_Jogos, corrigeString(token));
			if (!jogo1)
			{
				printf("%d NL Jogo inexistente.", NL);
				NL++;
				continue;
			}
			token = strtok(NULL, ":");
			jogo1->resultado->n1 = atoi(token);
			token = strtok(NULL, ":");
			jogo1->resultado->n2 = atoi(token);
		}
		/*A - Adiciona uma nova equipa*/
		if (string[0] == 'A')
		{
			token = strtok(string, " ");
			token = strtok(NULL, " ");
			nome = corrigeString(token);
			equipa1 = procurarEquipa(Lista_Equipas, nome);
			if (equipa1)
			{
				printf("%d Equipa existente.", NL);
				NL++;
				continue;
			}
			equipa1 = criarEquipa(nome);
			inserirNoFimDaLista(Lista_Equipas, equipa1);
		}
		/*P - Procura uma equipa dado um nome.*/
		if (string[0] == 'P')
		{
			token = strtok(string, " ");
			token = strtok(NULL, " ");
			nome = corrigeString(token);
			equipa1  = procurarEquipa(Lista_Equipas, nome);
			if (!equipa1)
			{
				printf("%d Equipa inexistente.", NL);
				printf("\n");
				NL++;
				continue;
			}
			printf("%d ", NL);
			mostrarEquipa(equipa1, NL);
			printf("\n");
		}
		/*g - Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa)*/
		if (string[0] == 'g')
		{
			n = equipaMaisJogosGanhos(Lista_Equipas);
			mostrarEquipaNJogosGanhos(Lista_Equipas, n, NL);
		}
		NL++;
	}while (string[0] != 'x');
	return 0;
}