#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "jogo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* JOGOS */
/* strings presentes na hashtable do jogo so podem ter ate 1023 caracteres */
int hashjogo(char nome[1024])
{
	/* Numero ao calhas */
	int hash = 893478917;
	int n = 0;
	
	while ( nome[n] != '\0' ) {
		hash *= nome[n];
		n++;
	}
	
	if (hash < 0)
	{
		return -hash;
	}
	else
	{
		return hash;
	}
}

void adicionajogo(struct TodosJogos *jogos, struct TodasEquipas *equipas, int num_comandos)
{
	struct Jogo *jogo;
	struct Jogo *jogo_cur;
	struct Equipa *equipa_cur;
	struct Equipa *equipa1 = NULL;
	struct Equipa *equipa2 = NULL;
	char nome[1024];
	int nome_len;
	char nome_e1[1024];
	char nome_e2[1024];
	int score1;
	int score2;
	int nomehash, equipa1hash, equipa2hash;
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, nome_e1, nome_e2, &score1, &score2);
	
	nomehash = hashjogo(nome) % TODOS_JOGOS_ELEMENTOS_NUM;
	equipa1hash = hashequipa(nome_e1) % TODAS_EQUIPAS_ELEMENTOS_NUM;
	equipa2hash = hashequipa(nome_e2) % TODAS_EQUIPAS_ELEMENTOS_NUM;
	
	/* Percorrer os jogos todos ate chegarmos ao ultimo */
	jogo_cur = jogos->elementos[nomehash];
	while (jogo_cur != NULL)
	{
		/* Se encontramos um jogo igual, da erro */
		if (strcmp(nome, jogo_cur->nome) == 0)
		{
			printf("%d Jogo existente.\n", num_comandos);
			return;
		}

		/* Se estamos no ultimo jogo, sai do ciclo */
		if (jogo_cur->next == NULL)
		{
			break;
		}

		/* Continuar para o proximo jogo */
		jogo_cur = jogo_cur->next;
	}
	
	/* Percorrer equipas ate as encontrarmos */
	equipa_cur = equipas->elementos[equipa1hash];
	while (equipa_cur != NULL)
	{
		/* Se encontramos a equipa1, vamos po-la */
		if (equipa1 == NULL && strncmp(nome_e1, equipa_cur->nome, 1024) == 0)
		{
			equipa1 = equipa_cur;
			break;
		}
		
		/* E vamos para a proxima equipa */
		equipa_cur = equipa_cur->next;
	}
	
	equipa_cur = equipas->elementos[equipa2hash];
	while (equipa_cur != NULL)
	{
		/* Se encontramos a equipa2, vamos po-la */
		if (equipa2 == NULL && strncmp(nome_e2, equipa_cur->nome, 1024) == 0)
		{
			equipa2 = equipa_cur;
			break;
		}
		
		/* E vamos para a proxima equipa */
		equipa_cur = equipa_cur->next;
	}

	/* Se chegamos aqui e uma das equipas nos jogos nao existir, entao um dos jogos (ou os dois) nao existem */
	if (equipa1 == NULL || equipa2 == NULL)
	{
		printf("%d Equipa inexistente.\n", num_comandos);
		return;
	}
	
	/* Criar jogo */
	jogo = can_fail_malloc( 1 * sizeof(struct Jogo) );
	jogo->equipa1 = equipa1;
	jogo->equipa2 = equipa2;
	jogo->next    = NULL;
	jogo->score1  = score1;
	jogo->score2  = score2;
	nome_len = strlen(nome);
	jogo->nome = can_fail_malloc( nome_len + 1 );
	strcpy(jogo->nome, nome);
	
	if (score1 > score2)
	{
		equipa1->jogos_ganhos += 1; /* Atualizacao do numero de jogos ganhos da equipa */
	}
	else if (score2 > score1)
	{
		equipa2->jogos_ganhos += 1; /* Atualizacao do numero de jogos ganhos da equipa */
	}
	
	/* Se nao temos nenhum jogo, colocar o novo jogo no inicio do vetor */
	if (jogo_cur == NULL)
	{
		jogos->elementos[nomehash] = jogo;
	}
	
	/* Caso contrario, adicionamos depois do ultimo jogo */
	else
	{
		jogo_cur->next = jogo;
	}
	
	/* Adicionar 1 elemento ao vetor */
	jogos->vetor = can_fail_realloc(jogos->vetor, (jogos->num_jogos + 1) * sizeof(struct Jogo*));

	/* Adicionar o elemento */
	jogos->vetor[jogos->num_jogos] = jogo;
	
	/* Aumentar o numero de jogos */
	jogos->num_jogos += 1;
}

void listajogo(struct TodosJogos *jogos, int num_comandos)
{
	int n;
	for (n = 0; n < jogos->num_jogos; n++)
	{
		if ( jogos->vetor[n] == NULL ) /* Se o vetor for diferente de nulo, sai do ciclo */
		{
			continue;
		}
		
		printf("%d %s %s %s %d %d\n", num_comandos,
		jogos->vetor[n]->nome,
		jogos->vetor[n]->equipa1->nome,
		jogos->vetor[n]->equipa2->nome,
		jogos->vetor[n]->score1,
		jogos->vetor[n]->score2);
	}
}
void apagajogo(struct TodosJogos *jogos, int num_comandos)
{
	struct Jogo *jogo_cur;
	struct Jogo *jogo_prev = NULL;
	char nome[1024];
	int nomehash;
	int n;
	scanf(" %[^:\n]", nome);
	nomehash = hashjogo(nome) % TODOS_JOGOS_ELEMENTOS_NUM;
	
	jogo_cur = jogos->elementos[nomehash];
	while (jogo_cur != NULL)
	{
		if (strcmp(nome, jogo_cur->nome) == 0)
		{
			/* Remover jogos ganhos */
			if (jogo_cur->score1 > jogo_cur->score2) {
				jogo_cur->equipa1->jogos_ganhos -= 1;
			}
			if (jogo_cur->score1 < jogo_cur->score2) {
				jogo_cur->equipa2->jogos_ganhos -= 1;
			}
			
			/* Se nao tinhamos o jogo anterior, apagar o primeiro */
			if (jogo_prev == NULL)
			{
				jogos->elementos[nomehash] = jogo_cur->next;
			}
			else
			{
				jogo_prev->next = jogo_cur->next; /* Se nao houver jogo anterior, passamos ao atual */
			}
			
			for (n = 0; n < jogos->num_jogos; n++)
			{
				if ( jogos->vetor[n] == jogo_cur )
				{
					jogos->vetor[n] = NULL; /* Apagar o jogo */
					break;
				}
			}
			
			free(jogo_cur->nome); /* Libertar a memoria */
			free(jogo_cur); /* Libertar a memoria */
			return;
		}
		jogo_prev = jogo_cur;
		jogo_cur = jogo_cur->next;
	}
	printf("%d Jogo inexistente.\n", num_comandos);
}
void procurajogo(struct TodosJogos *jogos, int num_comandos)
{
	struct Jogo *jogo;
	char nome[1024];
	int nomehash;
	scanf(" %[^:\n]", nome);
	nomehash = hashjogo(nome) % TODOS_JOGOS_ELEMENTOS_NUM;
	
	jogo = jogos->elementos[nomehash];
	while (jogo != NULL) 
	{
		if (strcmp(jogo->nome, nome) == 0) /* Se o nome que procuramos, corresponde ao nome do jogo, retorna o tal jogo */
		{
			printf("%d %s %s %s %d %d\n", num_comandos, jogo->nome, jogo->equipa1->nome, jogo->equipa2->nome, jogo->score1, jogo->score2);
			return;
		}
		jogo = jogo->next;
	}
	printf("%d Jogo inexistente.\n", num_comandos);
}
void alterascore(struct TodosJogos *jogos, int num_comandos)
{
	struct Jogo *jogo;
	int score1;
	int score2;
	int nomehash;
	char nome[1024];
	scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
	nomehash = hashjogo(nome) % TODOS_JOGOS_ELEMENTOS_NUM;
	
	jogo = jogos->elementos[nomehash];
	while (jogo != NULL)
	{
		if (strcmp(jogo->nome, nome) == 0) /* Se o nome corresponder ao nome do jogo que procuramos */
		{
			if (jogo->score1 > jogo->score2)
			{
				jogo->equipa1->jogos_ganhos -= 1; /* Atualizacao do numero de jogos ganhos da equipa, retirando o resultado antigo */
			}
			if (jogo->score1 < jogo->score2)
			{
				jogo->equipa2->jogos_ganhos -= 1; /* Atualizacao do numero de jogos ganhos da equipa, retirando o resultado antigo */
			}
			if (score1 > score2)
			{
				jogo->equipa1->jogos_ganhos += 1; /* Atualizacao do numero de jogos ganhos da equipa de acordo com o novo resultado */
			}
			if (score1 < score2)
			{
				jogo->equipa2->jogos_ganhos += 1; /* Atualizacao do numero de jogos ganhos da equipa de acordo com o novo resultado */
			}
			jogo->score1 = score1; /* Atualizacao do resultado do jogo */
			jogo->score2 = score2; /* Atualizacao do resultado do jogo */
			return;
		}
		
		jogo = jogo->next; 
	}
	
	printf("%d Jogo inexistente.\n", num_comandos);
}
