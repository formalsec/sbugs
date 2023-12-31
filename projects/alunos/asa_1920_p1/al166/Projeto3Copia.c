#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct/* Lista*/
{
	int* numbers;
	int size;
	int realsize;
}Lista;

typedef struct/* Aluno*/
{
	int index;
	int notaInicial;
	int notaFinal;
	Lista amigosReceptores;
}Aluno;

void addToLista(Lista* tabela, int num);
int removeFromLista(Lista* tabela);
void initLista(Lista* tabela);
void freeLista(Lista* tabela);


char bufferStdIn[8192];
char bufferStdOut[8192];


Aluno* tabela_alunos;
int numAlunos;

char* alunosEmAlunosDadores;
Lista alunosDadores;

int main(int argc, char* argv[])
{
	int c;
	int num;
	int i, numAmizades, Aluno1, Aluno2;

	setvbuf(stdin, bufferStdIn, _IOFBF, sizeof(bufferStdIn));
	setvbuf(stdout, bufferStdOut, _IOFBF, sizeof(bufferStdOut));


	scanf("%d,%d", &numAlunos, &numAmizades);

	tabela_alunos = (Aluno*)can_fail_malloc(sizeof(Aluno) * numAlunos);
	for (i = 0; i < numAlunos; i++) {
		while (!isdigit(c = getchar()))
			;
		num = c - '0';
		while (isdigit(c = getchar()))
			num= num*10+ c - '0';
		tabela_alunos[i].index = i;
		tabela_alunos[i].notaInicial = num;

		tabela_alunos[i].notaFinal = -1;
		initLista(&tabela_alunos[i].amigosReceptores);
	}

	for (i = 0; i < numAmizades; i++)
	{
		while (!isdigit(c = getchar()))
			;
		Aluno1 = c - '0';
		while (isdigit(c = getchar()))
			Aluno1 = Aluno1 * 10 + c - '0';

		while (!isdigit(c = getchar()))
			;

		Aluno2 = c - '0';
		while (isdigit(c = getchar()))
			Aluno2 = Aluno2 * 10 + c - '0';

		addToLista(&tabela_alunos[Aluno2 - 1].amigosReceptores, Aluno1 - 1);
	}

	alunosEmAlunosDadores= (char*)can_fail_calloc(numAlunos, sizeof(char));
	initLista(&alunosDadores);
	for (i = 0; i < numAlunos; i++) {
		tabela_alunos[i].notaFinal = tabela_alunos[i].notaInicial;
		if (tabela_alunos[i].amigosReceptores.size > 0)
		{
			addToLista(&alunosDadores, i);
			alunosEmAlunosDadores[i] = 1;
		}
	}
	while (alunosDadores.size > 0)
	{
		int iAluno= removeFromLista(&alunosDadores);
		alunosEmAlunosDadores[iAluno] = 0;
		Aluno* pDador = tabela_alunos + iAluno;
		int* pTailIndex = pDador->amigosReceptores.numbers + pDador->amigosReceptores.size;
		int* pCurAmigoIndex = pDador->amigosReceptores.numbers;
		while (pCurAmigoIndex < pTailIndex)
		{
			Aluno* pReceptor = tabela_alunos + *pCurAmigoIndex++;
			if (pReceptor->notaFinal < pDador->notaFinal)
			{
				pReceptor->notaFinal = pDador->notaFinal;
				if (!alunosEmAlunosDadores[pReceptor->index])
				{
					addToLista(&alunosDadores, pReceptor->index);
					alunosEmAlunosDadores[pReceptor->index] = 1;
				}
			}
		}
	}

	freeLista(&alunosDadores);
	free(alunosEmAlunosDadores);

	for (i = 0; i < numAlunos; i++) {
		printf("%d\n", tabela_alunos[i].notaFinal);
		freeLista(&tabela_alunos[i].amigosReceptores);
	}
	free(tabela_alunos);
	return 0;
}





void initLista(Lista* tabela)
{
	tabela->realsize = 8;
	tabela->size = 0;
	tabela->numbers = (int*)can_fail_malloc(sizeof(int) * ((tabela->realsize)));
}
void freeLista(Lista* tabela)
{
	free(tabela->numbers);
}

void addToLista(Lista* tabela, int num)
{
	if (tabela->size >= tabela->realsize)
	{
		tabela->realsize = (tabela->size + 1) * 2;
		tabela->numbers = (int*)can_fail_realloc(tabela->numbers, sizeof(int) * ((tabela->realsize)));
	}
	tabela->numbers[((tabela)->size)++] = num;
}


int removeFromLista(Lista* tabela)
{
	tabela->size--;
	return tabela->numbers[tabela->size];
}
