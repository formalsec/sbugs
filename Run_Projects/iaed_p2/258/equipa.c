#include "equipa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* EQUIPAS */
/* strings presentes na hashtable da equipa so podem ter ate 1023 caracteres */
int hashequipa(char nome[1024])
{
	/* Numero ao calhas */
	int hash = 712364078;
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

void adicionaequipa(struct TodasEquipas *equipas, int num_comandos)
{
	char nome[1024];
	int nomehash, nome_len;
	struct Equipa *equipa;
	struct Equipa *equipa_cur;
	scanf(" %[^:\n]", nome);
	nomehash = hashequipa(nome) % TODAS_EQUIPAS_ELEMENTOS_NUM;
	/* Percorrer as equipas todas ate chegarmos a ultima */
	equipa_cur = equipas->elementos[nomehash];
	while (equipa_cur != NULL)
	{
		/* Se encontramos uma equipa igual, da erro */
		if (strncmp(nome, equipa_cur->nome, 1024) == 0)
		{
			printf("%d Equipa existente.\n", num_comandos);
			return;
		}
		/* Se estamos na ultima equipa, sai do ciclo */
		if (equipa_cur->next == NULL)
		{
			break;
		}
		/* Continuar para a proxima equipa */
		equipa_cur = equipa_cur->next;
	}
	/* Criar equipa */
	equipa = malloc(1 * sizeof(struct Equipa));
	nome_len = strlen(nome);
	equipa->nome = malloc( nome_len + 1 );
	strcpy(equipa->nome, nome);
	equipa->jogos_ganhos = 0;
	equipa->next = NULL;
	/* Se nao temos nenhuma equipa, colocar a nova equipa no inicio do vetor */
	if (equipa_cur == NULL)
	{
		equipas->elementos[nomehash] = equipa;
	}
	/* Caso contrario, adicionamos depois da ultima equipa */
	else
	{
		equipa_cur->next = equipa;
	}
	
	/* Adicionar 1 elemento ao vetor */
	equipas->vetor = realloc(equipas->vetor, (equipas->num_equipas + 1) * sizeof(struct Equipa *));

	/* Adicionar o elemento */
	equipas->vetor[equipas->num_equipas] = equipa;
	
	/* Aumentar o numero de equipas */
	equipas->num_equipas += 1;
}

void procuraequipa(struct TodasEquipas *equipas, int num_comandos)
{
	struct Equipa *equipa_cur;
	int nomehash;
	char nome[1024];
	scanf(" %[^:\n]", nome);
	nomehash = hashequipa(nome) % TODAS_EQUIPAS_ELEMENTOS_NUM;
	
	equipa_cur = equipas->elementos[nomehash];
	while (equipa_cur != NULL)
	{
		if (strcmp(equipa_cur->nome, nome) == 0) /* Se o nome que procuramos, corresponde ao nome da equipa, retorna a tal equipa */
		{
			printf("%d %s %d\n", num_comandos, equipa_cur->nome, equipa_cur->jogos_ganhos);
			return;
		}
		equipa_cur = equipa_cur->next;
	}
	printf("%d Equipa inexistente.\n", num_comandos);
}
/* Funcao auxiliar de listagem das equipas primeiro por numero de jogos ganhos e depois por ordem alfabetica */
int equipas_cmp(const void *a, const void *b)
{
	const struct Equipa *arg1 = *(const struct Equipa **)a;
	const struct Equipa *arg2 = *(const struct Equipa **)b;

	if (arg1->jogos_ganhos < arg2->jogos_ganhos) /* Ordenacao pelo numero de jogos ganhos das equipas */
		return 1;
	if (arg1->jogos_ganhos > arg2->jogos_ganhos) /* Ordenacao pelo numero de jogos ganhos das equipas */
		return -1;

	return strncmp(arg1->nome, arg2->nome, 1024); /* Ordenacao das equipas por ordem alfabetica */
}

void encontravitoriosos(struct TodasEquipas *equipas, int num_comandos)
{
	int n;
	int jogos_ganhos_max;
	struct Equipa *equipa;

	/* Se nao temos elementos, nao imprimir nada */
	if (equipas->vetor == NULL)
	{
		return;
	}
	
	/* Ordenar o vetor */
	qsort(equipas->vetor, equipas->num_equipas, sizeof(struct Equipa*), equipas_cmp);

	/* Buscar o maior numero de jogos ganhos */
	jogos_ganhos_max = equipas->vetor[0]->jogos_ganhos;
	
	/* Imprimir titulo */
	printf("%d Melhores %d\n", num_comandos, jogos_ganhos_max);
	
	/* Imprimir todos os elementos */
	for (n = 0; n < equipas->num_equipas; n++)
	{
		equipa = equipas->vetor[n];

		if (equipa->jogos_ganhos < jogos_ganhos_max)
		{
			return;
		}

		printf("%d * %s\n", num_comandos, equipa->nome);
	}
}
