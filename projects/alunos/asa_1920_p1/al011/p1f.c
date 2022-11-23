#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
 * Grupo 11
 * Manuel Carvalho-87237
 * Miguel Coelho-89509
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int nota;
	int numamigos;
	int *amigos;
	int visitado;
} aluno;

typedef struct{
	int numalunos;
	int *alunos;
} amigo;

aluno* tab;
amigo* atab;

int N, M;

void initNotas(){

	int i, nota;

	for (i = 0; i < N; i++){

		scanf("%d", &nota);

		tab[i].nota = nota;
		tab[i].numamigos = 0;
		tab[i].amigos = NULL;
		tab[i].visitado = 0;

		atab[i].numalunos = 0;
		atab[i].alunos = NULL;
	}
}

void initAmigos(){

	int i, aluno, amigo;

	for (i = 0; i < M; i++){

		scanf("%d %d", &aluno, &amigo);
		aluno--;
		amigo--;

		tab[aluno].amigos = can_fail_realloc(tab[aluno].amigos, sizeof(int) * (tab[aluno].numamigos + 1));
		tab[aluno].amigos[tab[aluno].numamigos] = amigo;
		tab[aluno].numamigos++;

		atab[amigo].alunos = can_fail_realloc(atab[amigo].alunos, sizeof(int) * (atab[amigo].numalunos + 1));
		atab[amigo].alunos[atab[amigo].numalunos] = aluno;
		atab[amigo].numalunos++;
	}
}

void printNotas(){

	int i;

	for (i = 0; i < N; i++){

		printf("%d\n", tab[i].nota);
		free(tab[i].amigos);
		free(atab[i].alunos);
	}

	free(tab);
	free(atab);
}

void refresh(int amigo){

	int i, numalunos, aluno, new;

	numalunos = atab[amigo].numalunos;
	new = tab[amigo].nota;

	for (i = 0; i < numalunos; i++){

		aluno = atab[amigo].alunos[i];

		if (new > tab[aluno].nota){
			tab[aluno].nota = new;
			refresh(aluno);
		}
	}
}

void recalcula(int aluno){

	if (tab[aluno].visitado == 1) return;

	int i, numamigos, amigo, old, new;

	numamigos = tab[aluno].numamigos;
	old = tab[aluno].nota;
	new = old;
	tab[aluno].visitado = 1;

	for (i = 0; i < numamigos; i++){

		amigo = tab[aluno].amigos[i];

		if (tab[amigo].visitado == 0)
			recalcula(tab[aluno].amigos[i]);

		if (tab[amigo].nota > new)
			new = tab[amigo].nota;
	}

	if (new > old){
		tab[aluno].nota = new;
		refresh(aluno);
	}
}

int main(){

	int i;

	scanf("%d,%d", &N, &M);

	tab = can_fail_malloc(sizeof(aluno) * N);
	atab = can_fail_malloc(sizeof(amigo) * N);

	initNotas();
	initAmigos();

	for (i = 0; i < N; i++){
		recalcula(i);
	}

	printNotas();

	return 0;
}