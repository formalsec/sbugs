#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 

#define MAXLINE 20

typedef struct Node { 
    int value; 
    struct Node* next; 
} node;  

typedef struct student {
	node* relationshipsHead;
	node* relationshipsCurrent;
	bool finale; 
	int grade;
} Student;

int findBest();
void dfs(int a, int b);

Student* student;
int bestStudent = -1;
int bestGrade = -1;
int numStudents, numRelationships;


int main(int argc, char* argv[]) {
	int giver, receiver;
    int i;

	scanf("%d,%d", &numStudents, &numRelationships);
	student = malloc(numStudents * sizeof(Student));

	/*read the grades and initialise the rest of the variables in student*/
	for (i = 0; i < numStudents; i++) {
		scanf("%d", &student[i].grade);
		student[i].finale = false;
		student[i].relationshipsHead = malloc(sizeof(node));
		student[i].relationshipsHead->value = -1;
		student[i].relationshipsHead->next = NULL;
		student[i].relationshipsCurrent = student[i].relationshipsHead;
	}
	
	/*read the relationships and put them in the giver's relationship list*/
	for (i = 0; i < numRelationships; i++) {
		scanf("%d %d", &receiver, &giver);

		/*in case it's the head of the list*/
		if (student[giver - 1].relationshipsCurrent->value == -1) {
			student[giver - 1].relationshipsCurrent->value = receiver - 1;
		}

		else {
			student[giver - 1].relationshipsCurrent->next = malloc(sizeof(node));
			student[giver - 1].relationshipsCurrent = student[giver - 1].relationshipsCurrent->next;
			student[giver - 1].relationshipsCurrent->value = receiver - 1; 
			student[giver - 1].relationshipsCurrent->next = NULL;
		}
	}
	
	/*set current to head, for every student (so it's possible to iterate from the beginning)*/
	for (i = 0; i < numStudents; i++) {
		student[i].relationshipsCurrent = student[i].relationshipsHead;
	}

	/*until no more students exist, do dfs()*/
	while (findBest() != -1) {
		dfs(bestStudent, bestGrade);
		bestStudent = -1;
		bestGrade = -1;
	}
	
	/*print every grade*/
	for (i=0; i < numStudents; i++) {
        printf("%d\n", student[i].grade);
    }

	return 0;
}

/*propagate a student's grade to its relationship list*/
void dfs(int a, int b) {
	/*only needs to pass each student once*/
	student[a].finale = true;

	/*in case the student has no relationships, return*/
	if (student[a].relationshipsHead->value == -1)
		return;

	/*iterate the student's relationships list*/
	while (student[a].relationshipsCurrent != NULL)	{

		/*only if this student hasn't received any grade (if it has, then its previous is surely better)*/
		if (student[student[a].relationshipsCurrent->value].finale == false) {
			student[student[a].relationshipsCurrent->value].grade = b;

			/*propagate the receiving student's new grade*/
			dfs(student[a].relationshipsCurrent->value, b);
		}

		student[a].relationshipsCurrent=student[a].relationshipsCurrent->next;
	}

	return;
}

/*will find the best grade and student, if the student's grade isn't final*/
int findBest() {
	int i;

	for (i = 0; i < numStudents; i++) {
		if (student[i].finale == false) {
			if (student[i].grade > bestGrade) {
				bestStudent = i;
				bestGrade = student[i].grade;
			}
		}
	}

	return bestStudent;
}