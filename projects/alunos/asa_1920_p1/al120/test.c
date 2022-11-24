#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

struct Student {
	int visited;
	int number;
	int grade;
	int best_grade;
	int numberoffriends;
	int list[];
};

void Propagacao(struct Student ** class,int i, int num_comp){
	int j;
	if(class[i]->number != class[num_comp-1]->visited){
		class[num_comp-1]->visited = class[i]->number;
		if (class[i]->best_grade < class[num_comp-1]->best_grade){
				class[i]->best_grade = class[num_comp-1]->best_grade;
		}
		for(j = 0; j< class[num_comp-1]->numberoffriends; j++){
			Propagacao(class, i,class[num_comp-1]->list[j]);
		}
	}
}

void readfromfile(){
	int number_students, number_friends, i, infosize, j, friendp, friendnumber;
	char c;
	int size, studentnumber , numberfriendslist = 0;
	fscanf (stdin, "%d%c", &number_students, &c);
	fscanf (stdin, "%d", &number_friends);
	size = 2 * number_friends;
	infosize= number_students + size;
	struct Student* class[number_students];
	for(i = 0; i < number_students;i++){
		class[i] = (struct Student*) can_fail_malloc (sizeof(struct Student)+ (number_friends * sizeof(int)));
	}
	for(i = 0; i< number_students; i++){
		class[i]->number = 0;
		class[i]->grade = 0;
		class[i]->best_grade = 0;
		class[i]->numberoffriends = 0;
		class[i]->visited = 0;
		for(j=0; j< number_friends; j++){
			class[i]->list[j] = 0;
		}
	}
	for (i=0 ; i<number_students ; i++){
		class[i]->number = i+1;
		fscanf (stdin, "%d", &class[i]->grade);
		class[i]->best_grade = class[i]->grade;
	}
	for(i= number_students ; i<infosize ; i += 2){
		fscanf (stdin, "%d", &studentnumber);
		fscanf (stdin, "%d", &friendnumber);
		numberfriendslist = class[studentnumber-1]->numberoffriends;
		class[studentnumber-1]->list[numberfriendslist] = friendnumber;
		class[studentnumber-1]->numberoffriends += 1;
	}
	for(i = 0; i< number_students ; i++){
		for(j= 0; j< class[i]->numberoffriends; j++){
			friendp = class[i]->list[j];
			Propagacao(class,i, friendp );
		}
	}
	/*write to file*/
	for (i=0; i< number_students; i++){
		fprintf(stdout, "%d\n", class[i]->best_grade);
	}
}



int main(void) {
	readfromfile();
	return 0;
}


