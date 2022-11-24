#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Equipa.h"

/*Funcao que liberta da memoria uma estrutura 'Equipa' e as suas
componentes que foram alocadas.*/
void freeEquipa(Equipa* equipa)
{
	free(equipa->nome);
	free(equipa);
}

/*Funcao que da print a uma estrutura Equipa de acordo com o enunciado.*/
void printEquipa(Equipa* equipa, int conta_linhas)
{
	printf("%d %s %d\n", conta_linhas, equipa->nome, equipa->numero_vitorias);
}

/*Funcao que da print apenas ao nome da equipa, de acordo com o enunciado.*/
void printNome_Equipa(Equipa* equipa, int conta_linhas)
{
	printf("%d * %s\n", conta_linhas, equipa->nome);
}

/*Funcao que adiciona uma vitoria a uma equipa.*/
void soma_vitorias(Equipa* equipa)
{
	(equipa->numero_vitorias)++;
}

/*Funcao que retira uma vitoria a uma equipa.*/
void subtrai_vitorias(Equipa* equipa)
{
	(equipa->numero_vitorias)--;
}

/*Funcao que cria uma nova estrutura Equipa. Aloca em memoria a nova
estrutura e os parametros que necessitam ser alocados.*/
Equipa* novaEquipa(char *nome)
{
	Equipa *nova;
	int contagem_vit = 0;
	nova = (Equipa*) can_fail_malloc(sizeof(Equipa));

	/*Nota: a funcao 'strdup' encontra-se no ficheiro "funcoes_aux.h".*/
	nova->nome = strdup(nome);

	nova->numero_vitorias = contagem_vit;

	nova->next = NULL;

	return nova;
}






