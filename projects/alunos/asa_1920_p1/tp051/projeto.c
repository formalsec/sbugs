#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*Grupo tp051 - Diogo Cunha Mendonca (93701) 
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct friend {
	struct student* info;
	struct friend* next;
} friend;

typedef struct student {
	struct friend* lastFriend;
	struct friend* friends;
	int originalScore;
	int predictedScore; /*-1: Nao calculado*/
} student;

/*Lista de alunos pela ordem em que foram inseridos*/
student** students = NULL;
int numStudents = 0;

/*Adiciona estudante a lista*/
student* addStudent(int score, int id) {
	students[id] = can_fail_malloc(sizeof(student));
	students[id]->friends = NULL;
	students[id]->lastFriend = NULL;
	students[id]->originalScore = score;
	students[id]->predictedScore = -1;
	return students[id];
}

/*Adiciona um amigo a um estudante*/
friend* addFriend(student* s, student* newFriend) {
	if (s->friends == NULL) {
		s->friends = can_fail_malloc(sizeof(friend));
		s->friends->info = newFriend;
		s->friends->next = NULL;
		s->lastFriend = s->friends;
		return s->friends;
	}
	s->lastFriend->next = can_fail_malloc(sizeof(friend));
	s->lastFriend->next->info = newFriend;
	s->lastFriend->next->next = NULL;
	s->lastFriend = s->lastFriend->next;
	return s->lastFriend;
}

/*Le a entrada*/
void read() {
	int relationsNumber;
	char line[900];
	int i = 0;
	int studentId, friendId;

	fgets(line, sizeof(line) / sizeof(char), stdin);
	sscanf(line, "%d,%d", &numStudents, &relationsNumber);
	students = can_fail_malloc(sizeof(student*) * numStudents);
	while (i < numStudents) {
		fgets(line, sizeof(line) / sizeof(char), stdin);
		sscanf(line, "%d", &studentId);	
		addStudent(studentId, i);
		i++;
	}
	i = 0;
	while (i < relationsNumber) {
		fgets(line, sizeof(line) / sizeof(char), stdin);
		sscanf(line, "%d %d", &friendId, &studentId);
		addFriend(students[studentId-1], students[friendId-1]);
		i++;
	}
}

/*Calcula a nota de um estudante*/
void setNewScore(student* s, int newScore) {
	friend* f = s->friends;
	if (s->predictedScore >= newScore || s->originalScore > newScore) {
		return;
	}
	s->predictedScore = newScore;
	while (f != NULL) {
		setNewScore(f->info, newScore);
		f = f->next;
	}
}

/*Calcula as notas de todos os estudantes*/
void setScores() {
	int i = 0;
	while (i < numStudents) {
		if (students[i]->predictedScore == -1) {
			setNewScore(students[i], students[i]->originalScore);
		}
		i++;
	}
}

/*Escreve as novas notas*/
void write() {
	int i = 0;
	while(i < numStudents) {
		printf("%d\n", students[i]->predictedScore);	
		i++;
	}
}

int main() {
	read();
	setScores();
	write();
	exit(0);
}