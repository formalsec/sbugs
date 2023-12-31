#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*
Projeto realizado por:
Pedro Gomes-ist193747
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct aluno {
	int numero;
	int nota;
	int d;
	int low;
	struct aluno* next;
};

void addVertex(int nAlunos,struct aluno** listaAlunos);
void addEdge(int nRelacoes,struct aluno** listaAlunos);
void SCC_Tarjan(struct aluno** listaAlunos, int nAlunos);
void Tarjan_Visit(struct aluno** listaAlunos, int u, int* stack, int visited,int pos);
void pushStack(int* stack,int u,int pos);
int popStack(int* stack,int v,int pos);
int  checkStack(int n,int* stack,int pos);
void mostraNotas(struct aluno** listaAlunos,int nAlunos);

int main(){
	int nAlunos, nRelacoes;
	scanf("%d,%d", &nAlunos, &nRelacoes);
	struct aluno* listaAlunos[nAlunos];
	addVertex(nAlunos,listaAlunos);      
	addEdge(nRelacoes,listaAlunos);
	SCC_Tarjan(listaAlunos,nAlunos);
	mostraNotas(listaAlunos,nAlunos);
	return 0;
}

void addVertex(int nAlunos,struct aluno** listaAlunos){
	int novaNota,i;
	for(i = 0; i < nAlunos; i ++){
		struct aluno* newAluno = can_fail_malloc(sizeof(struct aluno*));
		scanf("%d", &novaNota);
		newAluno->nota = novaNota;
		newAluno->numero = i;
		newAluno->low = -1;
		newAluno->d = -1;
		listaAlunos[i] = newAluno;
	}
}

void addEdge(int nRelacoes,struct aluno** listaAlunos){
	int a1, a2,i;
	for(i = 0; i < nRelacoes; i++){
		scanf("%d %d", &a1 , &a2); 
		a1--;a2--;
		struct aluno* nextAluno = listaAlunos[a2];
		struct aluno* loopAluno = listaAlunos[a1]->next;
		if(!listaAlunos[a1]->next){
			listaAlunos[a1]->next = nextAluno;
		}
		else{
			while(loopAluno->next){
				loopAluno = loopAluno->next;
				loopAluno->next = nextAluno;
				nextAluno->next = NULL;
			}
		}
	}
}

void SCC_Tarjan(struct aluno** listaAlunos, int nAlunos){
	int visited = 0, pos = 0,i;
	int stack[nAlunos];
	for(i = 0;i < nAlunos;i ++){
		if(listaAlunos[i]->d < 0)
			Tarjan_Visit(listaAlunos, i, stack, visited, pos);
	}
}

void Tarjan_Visit(struct aluno** listaAlunos, int u, int* stack, int visited,int pos){ 
	listaAlunos[u]->d = listaAlunos[u]->low = visited;
	visited ++;
	pushStack(stack,u,pos);
	if(listaAlunos[u]->next){
		struct aluno* nextAluno = listaAlunos[u]->next;
		while(nextAluno){
			if(nextAluno->d < 0 || checkStack(nextAluno->numero,stack,pos)){
				if(nextAluno->d < 0){
					Tarjan_Visit(listaAlunos, nextAluno->numero, stack, visited, pos);
				}
				listaAlunos[u]->low =  (((listaAlunos[u]->low) < (listaAlunos[nextAluno->numero]->low)) ? (listaAlunos[u]->low) : (listaAlunos[nextAluno->numero]->low));
				listaAlunos[u]->nota =  (((listaAlunos[u]->nota) > (listaAlunos[nextAluno->numero]->nota)) ? (listaAlunos[u]->nota) : (listaAlunos[nextAluno->numero]->nota));
			}
			nextAluno = nextAluno->next;
		}
	}
	if(listaAlunos[u]->low == listaAlunos[u]->d){
		visited = visited - popStack(stack, pos, u);
	}
}

void pushStack(int* stack,int u,int pos){
	stack[pos] = u;
	pos++;
}

int popStack(int* stack,int pos,int u){
	int counter = 0;
	while(stack[pos] != u){
		pos--;
		counter++;
	}
	return counter;
}

int checkStack(int n,int* stack,int pos){
	int i;
	for(i = 0;i < pos;i ++){
		if(stack[i] == n)
			return 1;
	}
	return 0;
}

void mostraNotas(struct aluno** listaAlunos,int nAlunos){
	int i;
	for(i = 0;i < nAlunos;i ++){
		printf("%d\n",listaAlunos[i]->nota);
	}
}