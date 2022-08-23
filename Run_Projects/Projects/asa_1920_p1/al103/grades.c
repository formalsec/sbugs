#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20
#define UNDEFINED -1
#define FRIENDS 1

typedef struct STUDENTS
{
	int grade;
	int friendCount;
	int *friends;
} STUDENTS;

STUDENTS *create_array_structs(int *numStudents, int *totalFriendships);
void read_input(int numStudents, int totalFriendships, int *maxGrade, STUDENTS *students);
void new_grades(int numStudents, int maxGrade, STUDENTS *students);
void free_mem(int numStudents, STUDENTS *students);

int main(void)
{
	int numStudents = 0, totalFriendships = 0, maxGrade = 0;
	STUDENTS *students = create_array_structs(&numStudents, &totalFriendships);
	read_input(numStudents, totalFriendships, &maxGrade, students);
	new_grades(numStudents, maxGrade, students);
	free_mem(numStudents, students);
	return 0;
}

STUDENTS *create_array_structs(int *numStudents, int *totalFriendships)
{
	int i = 0;
	char buff[MAX_SIZE];
	fgets(buff, MAX_SIZE, stdin);
	*numStudents = atoi(strtok(buff, ","));
	*totalFriendships = atoi(strtok(NULL, "\n"));
	STUDENTS *structure = (STUDENTS *) malloc(*numStudents * sizeof(STUDENTS));
	for (i = 0;  i < *numStudents; i++)
	{
		structure[i].grade = UNDEFINED;
		structure[i].friendCount = 0;
		structure[i].friends = (int *) malloc(1 * sizeof(int));
	}
	return structure;
}

void read_input(int numStudents, int totalFriendships, int *maxGrade, STUDENTS *students)
{
	char buff[MAX_SIZE];
	int i = 0, student1 = UNDEFINED, student2 = UNDEFINED;
	for (i = 0; i < numStudents; i++)
	{
		fgets(buff, MAX_SIZE, stdin);
		students[i].grade = atoi(buff);
		if (atoi(buff) > *maxGrade)
			*maxGrade = atoi(buff); 
	}
	for (i = 0; i < totalFriendships; i++)
	{
		fgets(buff, MAX_SIZE, stdin);
		student1 = atoi(strtok(buff," "))-1;
		student2 = atoi(strtok(NULL, "\n"))-1;
		students[student1].friends[students[student1].friendCount] = student2;
		students[student1].friendCount += 1;
		students[student1].friends = (int *) realloc(students[student1].friends, (students[student1].friendCount + 1) * sizeof(int));
	}
}

void new_grades(int numStudents, int maxGrade, STUDENTS *students)
{
	int student1 = 0, student2 = 0, i = 0, friend = 0, flag = 0;
	for (i = 0; i < numStudents; i++)
	{
		flag = 0;
		for (student1 = 0; student1 < numStudents; student1++)
		{
			if (students[student1].grade != maxGrade)
			{
				for (student2 = 0; student2 < students[student1].friendCount; student2++)
				{
					friend = students[student1].friends[student2];
					if (students[friend].grade > students[student1].grade)
					{
						students[student1].grade = students[friend].grade;
						flag = 1;
					}
				}
			}
		}
		if (flag == 0)
			break;
	}
	for (i = 0; i < numStudents; i++)
		printf("%d\n", students[i].grade);
}

void free_mem(int numStudents, STUDENTS *students)
{
	int i = 0;
	for (i = 0; i < numStudents; i++)
		free(students[i].friends);
	free(students);
}
