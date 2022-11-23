#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************************
 +         Definicao de constantes globais          +
 ****************************************************/

#define MAX 3200         /* numero arbitrario para definir um valor maximo de caracteres do input */
#define MAX_S 1023       /* valor maximo de caracteres para cada string                           */

/***************************************************************************************
 +         Estruturas de organizacao para cada Equipa e Jogo, respetivamente           +
 ***************************************************************************************/

typedef struct equipas
{
	char equipa[MAX_S];
	int vitorias;
} equipas;

/*****************************************/

typedef struct jogos
{
	char nome[MAX_S], equipa_1[MAX_S], equipa_2[MAX_S];
	int score_1, score_2;
} jogos;

/********************************************************************************
 +       Definicao das variaveis estaticas e arrays de memoria dinamica         +
 ********************************************************************************/

static struct equipas *Equipa;  /* inicializa array dinamica para as equipas          */

static struct jogos *Jogo;      /* inicializa array dinamica para os jogos            */

static int n_teams = -1;        /* inicializa contagem de numero de equipas           */

static int n_jogos = -1;        /* inicializa contagem de numero de jogos             */

static int NL = 0;              /* contador global que guarda valor da linha de input */

/********************************************
 +            Funcoes principais            +
 +                                          +
 + Observacoes: as funcoes sao apresentadas +
 +              por ordem que foram feitas  +
 +              de forma a facilitar o      +
 +              processo de criacao do proj +
 ********************************************/

/*
 + Funcao: Funcao_A (correspondente o "case 'A'" na Funcao Main)
 + Recebe: char argum[]
 + Formato de saida: -NADA- exceto erro
 + Objetivo: Adiciona a struct de equipas a nova equipa. Devolve erro caso a 
 +           equipa a adicionar ja esteja no sistema.
 +
 ****************************************************************************/

int Funcao_A(char argum[])
{
	const char fim[2] = "\n";                                            /* serve para correr a string de input ate ao separador do fim */
	char *var_aux, team[MAX_S];
	int i = 0;

	var_aux = strtok(argum, fim);
	strcpy(team, var_aux);

	if(n_teams < 0)                                                      /* caso nao existam equipas no sistema */
	{
		n_teams = 0;
		Equipa = can_fail_malloc(sizeof(equipas)*1);                              /* aloca a memoria necessaria na estrutura */

		strcpy(Equipa[n_teams].equipa, team);
		Equipa[n_teams].vitorias = 0;

		return 0;                                                        /* retorna sem erro */
	}
	else                                                                 /* caso ja existam equipas no sistema */
	{
		for(i = 0; i <= n_teams; i++)
		{
			if(strcmp(Equipa[i].equipa, team) == 0)
			{
				printf("%d Equipa existente.\n", NL);

				return 1;                                                /* retorna com erro */
			}
		}
		
		n_teams++;
		Equipa = can_fail_realloc(Equipa, sizeof(equipas)*(n_teams + 1));

		strcpy(Equipa[n_teams].equipa, team);
		Equipa[n_teams].vitorias = 0;
	}

	return 0;	
}

/*
 + Funcao: Funcao_P (correspondente o "case 'P'" na Funcao Main)
 + Recebe: char argum[]
 + Formato de saida: "NL nome numero-de-jogos-ganhos." ou erro
 + Objetivo: Procura uma equipa no sistema dado um nome.
 +
 ****************************************************************************/

int Funcao_P(char argum[])
{
	const char fim[2] = "\n";
	char *var_aux, nome[MAX_S];
	int i = 0;

	var_aux = strtok(argum, fim);
	strcpy(nome, var_aux);

	for(i = 0; i <= n_teams; i++)
	{
		if(strcmp(Equipa[i].equipa, nome) == 0)
		{
			printf("%d %s %d\n", NL, Equipa[i].equipa, Equipa[i].vitorias);

			return 0;
		}
	}

	printf("%d Equipa inexistente.\n", NL);

	return 1;
}

/*
 + Funcao: Funcao_a (correspondente o "case 'a'" na Funcao Main)
 + Recebe: char argum[]
 + Formato de saida: -NADA- exceto erro
 + Objetivo: Adiciona a struct de jogos um novo jogo. averigua se o jogo ja
 +           existe no sistema ou se alguma das equipas nao esta no sistema.
 +
 ****************************************************************************/

int Funcao_a(char argum[])
{
	const char separador[2] = ":", fim[2] = "\n";                          /* separadores para "cortar" a string de input para cada variavel */
	char *var_aux, nome[MAX_S], team_1[MAX_S], team_2[MAX_S];
	int score_1, score_2, i = 0, j = 0;

	var_aux = strtok(argum, separador);
	strcpy(nome, var_aux);

	var_aux = strtok(NULL, separador);
	strcpy(team_1, var_aux);

	var_aux = strtok(NULL, separador);
	strcpy(team_2, var_aux);

	var_aux = strtok(NULL, separador);
	score_1 = atoi(var_aux);

	var_aux = strtok(NULL, fim);
	score_2 = atoi(var_aux);

	if(n_jogos < 0)                                                         /* nao ha jogos guardados ainda */
	{
		for(i = 0; i <= n_teams; i++)
		{
			if(strcmp(Equipa[i].equipa, team_1) == 0)
			{
				for(j = 0; j <= n_teams; j++)
				{
					if(strcmp(Equipa[j].equipa, team_2) == 0)
					{
						n_jogos = 0;
						Jogo = can_fail_malloc(sizeof(jogos)*1);                    /* aloca memoria dinamica necessaria para a struct de jogos */

						strcpy(Jogo[0].nome, nome);
						strcpy(Jogo[0].equipa_1, team_1);
						strcpy(Jogo[0].equipa_2, team_2);
						Jogo[0].score_1 = score_1;
						Jogo[0].score_2 = score_2;

						if(score_1 > score_2)                               /* faz update no sistema de equipas em relacao as vitorias */
						{
							Equipa[i].vitorias++;
						}
						else if(score_1 < score_2)
						{
							Equipa[j].vitorias++;
						}

						return 0;
					}
				}
			}
		}

		printf("%d Equipa inexistente.\n", NL);

		return 2;                                                           /* sai com erro, equipas inexistentes */
	}
	else if(n_jogos >= 0)                                                   /* ha jogos guardados no sistema */
	{
		for(i = 0; i <= n_jogos; i++)
		{
			if(strcmp(Jogo[i].nome, nome) == 0)
			{
				printf("%d Jogo existente.\n", NL);

				return 1;                                                   /* erro caso jogo esteja no sistema*/
			}
		}

		/* apos averiguar a existencia do jogo no sistema, averigua a existencia de cada equipa no sistema 
		 **************************************************************************************************/

		for(i = 0; i <= n_teams; i++)
		{
			if(strcmp(Equipa[i].equipa, team_1) == 0)
			{
				for(j = 0; j <= n_teams; j++)
				{
					if(strcmp(Equipa[j].equipa, team_2) == 0)
					{
						n_jogos++;
						Jogo = can_fail_realloc(Jogo, sizeof(jogos)*(n_jogos + 1));

						strcpy(Jogo[n_jogos].nome, nome);
						strcpy(Jogo[n_jogos].equipa_1, team_1);
						strcpy(Jogo[n_jogos].equipa_2, team_2);
						Jogo[n_jogos].score_1 = score_1;
						Jogo[n_jogos].score_2 = score_2;

						if(score_1 > score_2)
						{
							Equipa[i].vitorias++;
						}
						else if(score_1 < score_2)
						{
							Equipa[j].vitorias++;
						}

						return 0;
					}
				}
			}
		}

		printf("%d Equipa inexistente.\n", NL);

		return 2;                                                             /* sai com erro, equipas inexistentes */
	}

	return 3;                                                                 /* retorno que evita erro por void-type function devido ao uso de else if's */
}

/*
 + Funcao: Funcao_l (correspondente o "case 'l'" na Funcao Main)
 + Recebe: -NADA-
 + Formato de saida: uma linha por jogo no formato
 +                   "NL nome-jogo nome-equipa1 nome-equipa2 score1 score2"
 + Objetivo: lista todos os jogos pela ordem que foram introduzidos. se
 +           nao existirem jogos no sistema o comando nao imprime nada.
 +
 ****************************************************************************/

int Funcao_l()
{
	int i = 0;

	if(n_jogos >= 0)
	{
		for(i = 0; i <= n_jogos; i++)
		{
			printf("%d %s %s %s %d %d\n", NL, Jogo[i].nome, Jogo[i].equipa_1, Jogo[i].equipa_2, Jogo[i].score_1, Jogo[i].score_2);
		}

		return 0;
	}
	else
	{
		return 1; /* nao existem jogos no sistema */
	}
}

/*
 + Funcao: Funcao_p (correspondente o "case 'p'" na Funcao Main)
 + Recebe: char argum[]
 + Formato de saida: igual ao da funcao_l mas apenas para o jogo em questao
 +                   exceto erro
 + Objetivo: procura um jogo dado um nome. Retorna erro caso o jogo nao esteja
 +           no sistema.
 +
 ****************************************************************************/

int Funcao_p(char argum[])
{
	const char fim[2] = "\n";
	char *var_aux, nome[MAX_S];
	int i = 0;

	var_aux = strtok(argum, fim);
	strcpy(nome, var_aux);

	for(i = 0; i <= n_jogos; i++)
	{
		if(strcmp(Jogo[i].nome, nome) == 0)
		{
			printf("%d %s %s %s %d %d\n", NL, Jogo[i].nome, Jogo[i].equipa_1, Jogo[i].equipa_2, Jogo[i].score_1, Jogo[i].score_2);

			return 0;
		}
	}

	printf("%d Jogo inexistente.\n", NL);

	return 1; /* retorna com mensagem de erro */
}

/*
 + Funcao: Funcao_s (correspondente o "case 's'" na Funcao Main)
 + Recebe: char argum[]
 + Formato de saida: -NADA- exceto erro
 + Objetivo: altera o score de um jogo dado o nome. Caso se aplique, tambem
 +           o valor das vitorias para as equipas em questao.
 +
 ****************************************************************************/

int Funcao_s(char argum[])
{
	const char separador[2] = ":", fim[2] = "\n";
	char *var_aux, nome[MAX_S];
	int score_1, score_2, i = 0, j = 0, a, b;

	var_aux = strtok(argum, separador);
	strcpy(nome, var_aux);

	var_aux = strtok(NULL, separador);
	score_1 = atoi(var_aux);

	var_aux = strtok(NULL, fim);
	score_2 = atoi(var_aux);

	for(i = 0; i <= n_jogos; i++)
	{
		if(strcmp(nome, Jogo[i].nome) == 0)
		{
			a = Jogo[i].score_1;
			b = Jogo[i].score_2;
			Jogo[i].score_1 = score_1;
			Jogo[i].score_2 = score_2;

			if((a-b) < 0 && (score_1-score_2) > 0)                       /* caso antes equipa2 tinha ganho mas agora ganha a equipa1 */
			{
				for(j = 0; j <= n_teams; j++)
				{
					if(strcmp(Jogo[i].equipa_2, Equipa[j].equipa) == 0)
					{
						Equipa[j].vitorias = Equipa[j].vitorias - 1;
					}
				}

				for(j = 0; j <= n_teams; j++)
				{
					if(strcmp(Jogo[i].equipa_1, Equipa[j].equipa) == 0)
					{
						Equipa[j].vitorias++;
					}
				}

				return 0;
			}
			else if((a-b) > 0 && (score_1-score_2) < 0)                  /* caso antes equipa1 tinha ganho mas agora ganha a equipa2 */
			{
				for(j = 0; j <= n_teams; j++)
				{
					if(strcmp(Jogo[i].equipa_2, Equipa[j].equipa) == 0)
					{
						Equipa[j].vitorias++;
					}
				}

				for(j = 0; j <= n_teams; j++)
				{
					if(strcmp(Jogo[i].equipa_1, Equipa[j].equipa) == 0)
					{
						Equipa[j].vitorias = Equipa[j].vitorias - 1;
					}
				}

				return 0;
			}
			else if((a-b) == 0 && (score_1-score_2) < 0)                /* caso antes empate mas agora ganha a equipa2 */
			{
				for(j = 0; j <= n_teams; j++)
				{
					if(strcmp(Jogo[i].equipa_2, Equipa[j].equipa) == 0)
					{
						Equipa[j].vitorias++;
					}
				}

				return 0;
			}
			else if((a-b) == 0 && (score_1-score_2) > 0)                /* caso antes empate mas agora ganha a equipa1 */
			{
				for(j = 0; j <= n_teams; j++)
				{
					if(strcmp(Jogo[i].equipa_1, Equipa[j].equipa) == 0)
					{
						Equipa[j].vitorias++;
					}
				}

				return 0;
			}
			else if((a-b) > 0 && (score_1-score_2) == 0)                /* caso antes equipa1 tinha ganho mas agora empate */
			{
				for(j = 0; j <= n_teams; j++)
				{
					if(strcmp(Jogo[i].equipa_1, Equipa[j].equipa) == 0)
					{
						Equipa[j].vitorias = Equipa[j].vitorias - 1;
					}
				}

				return 0;
			}
			else if((a-b) < 0 && (score_1-score_2) == 0)                /* caso antes equipa2 tinha ganho mas agora empate */
			{
				for(j = 0; j <= n_teams; j++)
				{
					if(strcmp(Jogo[i].equipa_2, Equipa[j].equipa) == 0)
					{
						Equipa[j].vitorias = Equipa[j].vitorias - 1;
					}
				}

				return 0;
			}

			return 0;                                                  /* caso de empate em ambos os scores ou nao se alterar as vitorias */
		}
	}

	printf("%d Jogo inexistente.\n", NL);

	return 1;                                                          /* jogo nao existe */
}

/*
 + Funcao: Funcao_r (correspondente o "case 'r'" na Funcao Main)
 + Recebe: char argum[]
 + Formato de saida: -NADA- exceto erro
 + Objetivo: apaga um jogo do sistema dado o nome.
 +
 ****************************************************************************/

int Funcao_r(char argum[])
{
	const char fim[2] = "\n";
	char *var_aux, nome[MAX_S];
	int i = 0, j = 0, game, flag_existe = -1;

	var_aux = strtok(argum, fim);
	strcpy(nome, var_aux);

	for(i = 0; i <= n_jogos; i++)                                         /* procura o jogo e caso exista altera as vitorias das equipas em questao */
	{
		if(strcmp(Jogo[i].nome, nome) == 0)
		{
			game = i;
			flag_existe = 0;                                              /* flag sinaliza que o jogo existe quando nao negativa (0 neste caso) */

			if((Jogo[i].score_1 - Jogo[i].score_2) > 0)
			{
				for (j = 0; j <= n_teams; j++)
				{
					if(strcmp(Equipa[j].equipa, Jogo[i].equipa_1) == 0)
					{
						Equipa[j].vitorias = Equipa[j].vitorias - 1;
					}
				}
			}
			else if((Jogo[i].score_1 - Jogo[i].score_2) < 0)
			{
				for (j = 0; j <= n_teams; j++)
				{
					if(strcmp(Equipa[j].equipa, Jogo[i].equipa_2) == 0)
					{
						Equipa[j].vitorias = Equipa[j].vitorias - 1;
					}
				}
			}
		}
	}

	if(flag_existe >= 0)                                                   /* procede a eliminacao do jogo do sistema */
	{
		for(i = game; i < n_jogos; i++)
		{
			strcpy(Jogo[i].nome, Jogo[i+1].nome);
			strcpy(Jogo[i].equipa_1, Jogo[i+1].equipa_1);
			strcpy(Jogo[i].equipa_2, Jogo[i+1].equipa_2);
			Jogo[i].score_1 = Jogo[i+1].score_1;
			Jogo[i].score_2 = Jogo[i+1].score_2;
		}

		Jogo = can_fail_realloc(Jogo, sizeof(jogos)*n_jogos);                      /* realoca o espaco necessario, de novo, para a memoria dinamica */
		n_jogos = n_jogos - 1;

		return 0;
	}
	else
	{
		printf("%d Jogo inexistente.\n", NL);

		return 1;
	}
}

/*
 + Funcao: Funcao_g (correspondente o "case 'g'" na Funcao Main)
 + Recebe: -NADA_
 + Formato de saida: listagem lexicografica das equipas com mais vitorias
 +                   "NL Melhores numero-de-jogos-ganhos
 +                    NL * nome-equipa1
 +                    ...                               "
 + Objetivo: Encontra as equipas que ganharam mais jogos e ordena-as por
 +           ordem lexicografica do nome da equipa.
 +
 ****************************************************************************/

int funcao_g()
{
	if(n_teams >= 0)
	{
		int i = 0, j = 0, max_v = 0, *posicoes, array_size = 0, pos_aux = -1, temp;

		for(i = 0; i <= n_teams; i++)                                                      /* obter max de vitorias */
		{
			if(Equipa[i].vitorias > max_v)
			{
				max_v = Equipa[i].vitorias;
			}
		}

		for(i = 0; i <= n_teams; i++)                                                      /* obter N# de equipas com essas vitorias */
		{
			if(Equipa[i].vitorias == max_v)
			{
				array_size++;
			}
		}

		posicoes = can_fail_malloc(sizeof(int)*array_size);

		for(i = 0; i <= n_teams; i++)                                                      /* obter cada equipa */
		{
			if(Equipa[i].vitorias == max_v)
			{
				pos_aux++;
				posicoes[pos_aux] = i;
			}
		}

		for(i = 0; i < array_size; i++)                                                    /* organizacao bubble sort */
		{
			for(j = i + 1; j < array_size; j++)
			{
				if(strcmp(Equipa[posicoes[i]].equipa, Equipa[posicoes[j]].equipa) > 0)
				{
					temp = posicoes[i];
					posicoes[i] = posicoes[j];
					posicoes[j] = temp;
				}
			}
		}

		printf("%d Melhores %d\n", NL, max_v);

		for(i = 0; i < array_size; i++)
		{
			printf("%d * %s\n", NL, Equipa[posicoes[i]].equipa);
		}

		free(posicoes);

		return 0;		
	}
	else
	{
		return 1;
	}
}

/********************************
 +          Funcao Main         +
 ********************************/

/*
 + -> Funcao Main contem apenas 2 variaveis declaradas (c, que refere qual o case do switch;
 + argum[MAX] que ira conter a string toda obtida do input); utilizacao da operacao 'getchar'
 + para obter o char 'c' que ditara cada case do switch, seguido de um 'getchar()' vazio
 + propositado para retirar o espaco entre a operacao e as instrucoes da operacao; obtencao
 + da restante string a partir de 'fgets'; cada case depende da primeira instrucao dada na
 + string do input inicial; operacao 'x' termina o programa com sucesso; caso o input seja
 + invalido, termina o programa apresentado um output de erro correspondente. Em caso de fim do
 + programa, liberta a memoria ocupada pelas memorias dinamicas das estruturas.
 +
 ***********************************************************************************************/

int main()
{
	char c, argum[MAX];

	while((c = getchar()) != EOF)
	{
		getchar();

		switch(c)
		{
			case 'a':
			{
				fgets(argum, MAX, stdin);

				NL++;

				Funcao_a(argum);

				break;
			}
			case 'A':
			{
				fgets(argum, MAX, stdin);

				NL++;

				Funcao_A(argum);

				break;
			}
			case 'g':
			{
				NL++;

				funcao_g();

				break;
			}
			case 'l':
			{
				NL++;

				Funcao_l();

				break;
			}
			case 'p':
			{
				fgets(argum, MAX, stdin);

				NL++;

				Funcao_p(argum);

				break;
			}
			case 'P':
			{
				fgets(argum, MAX, stdin);

				NL++;

				Funcao_P(argum);

				break;
			}
			case 'r':
			{
				fgets(argum, MAX, stdin);

				NL++;

				Funcao_r(argum);

				break;
			}
			case 's':
			{
				fgets(argum, MAX, stdin);

				NL++;

				Funcao_s(argum);

				break;
			}
			case 'x':
			{
				free(Equipa);         /* liberta memoria ocupada pelas memorias dinamicas */
				free(Jogo);

				return EXIT_SUCCESS;
			}
			default:
			{
				free(Equipa);         /* liberta memoria ocupada pelas memorias dinamicas */
				free(Jogo);

				fprintf(stderr, "Erro: operacao invalida!\n");

				return EXIT_FAILURE;
			}
		}
	}

	return 0;
}