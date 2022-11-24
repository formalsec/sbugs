#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* ASA - projeto 1
   Diogo Marques - 93703 */

#include <stdio.h>
#include <stdlib.h>


/* struct that saves the information of each student */
typedef struct student {
	int grade;
	int* friends;
	int numb_of_friends;
	int state;			/* 0-white 1-grey 2-black */
} student;

void dfs_visit(int student);
void dfs();

student* class;
int students, relations, control = 1;

int main(){

	int i, aux, aux2;
	char first_line[5];
	
	scanf("%s", first_line);								/* computes the first input line */
	students = atoi(&first_line[0]);
	relations = atoi(&first_line[2]);

	class = (student*) can_fail_malloc(sizeof(student) * (students + 1)); 

	for(i = 1; i <= students; i++)							/* sets the original grades for each student */
		scanf("%d", &class[i].grade);
	
	for(i = 1; i <= students; i++){							/* initializes each student */
		class[i].numb_of_friends = 0;
		class[i].state = 0;
	}
	
	for(i = 0; i < relations; i++){							/* sets every friend relation to each student */
		scanf("%d %d", &aux, &aux2);
		if(class[aux].numb_of_friends != 0){
			class[aux].friends = (int*) can_fail_realloc(class[aux].friends, sizeof(int) * (class[aux].numb_of_friends + 1));
			class[aux].friends[class[aux].numb_of_friends] = aux2;
			class[aux].numb_of_friends ++;
		}
		else{
			class[aux].friends = (int*) can_fail_malloc(sizeof(int));
			class[aux].friends[class[aux].numb_of_friends] = aux2;
			class[aux].numb_of_friends ++;
		}
	}

	while(control == 1)									/* performs the dfs until no student grade is changed */
		dfs();	

	for(i = 1; i <= students; i++)						/* prints each student final grade */
		printf("%d\n", class[i].grade);
	
	return 0;
}

/* permorfs the dfs for each student */
void dfs(){

	int i;
	control = 0;
	for(i = 1; i <= students; i++){
		if(class[i].state == 0 || class[i].state == 2){
			dfs_visit(i);
		}
	}
}
/* visits each student friends */
void dfs_visit(int student){

	int i;

	class[student].state = 1;

	for(i = 0; i < class[student].numb_of_friends; i++){
		if(class[class[student].friends[i]].state == 0)
			dfs_visit(class[student].friends[i]);
		if(class[class[student].friends[i]].grade > class[student].grade){
			class[student].grade = class[class[student].friends[i]].grade;
			control = 1;			/* flag that controls if any grade was changed */
		}
	}
	class[student].state = 2;
}
