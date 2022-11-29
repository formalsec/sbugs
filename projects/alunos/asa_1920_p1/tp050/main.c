#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
    int grade;
    struct student** friends;
    int numfriends;
    int isChecked; 
} student;

student** list;
int contador = 0;
int auxGrade;

void merge(student** friends, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    student *L[n1], *R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = friends[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = friends[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; /* Initial index of first subarray */
    j = 0; /* Initial index of second subarray */
    k = l; /* Initial index of merged subarray */
    while (i < n1 && j < n2) 
    { 
        if (L[i]->grade >= R[j]->grade) 
        { 
            friends[k] = L[i]; 
            i++; 
        } 
        else
        { 
            friends[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        friends[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        friends[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(student** friends, int l, int r) 
{ 
    if (l < r) 
    {        
        int m = l+(r-l)/2; 
  
        mergeSort(friends, l, m); 
        mergeSort(friends, m+1, r); 
  
        merge(friends, l, m, r); 
    } 
}

void visit(student* person){
	int j;
	if(!person->isChecked){
		person->grade = auxGrade;
		person->isChecked = 1;
		contador++;
		for(j = 0; j < person->numfriends; j++){
			visit(person->friends[j]);
		}
	}
}

int main(){
	int i, students, friendships, person, friendId;
    student** auxList;
    
	scanf("%d,%d", &students, &friendships);
	
	list = can_fail_malloc(students * sizeof(student*));
    auxList = can_fail_malloc(students * sizeof(student*));

	for(i = 0; i < students; i++){
		list[i] = can_fail_malloc(sizeof(struct student));
		scanf("%d", &(list[i]->grade));
		list[i]->isChecked = 0;
		list[i]->numfriends = 0;
	}
	for(i = 0; i < friendships; i++){
		scanf("%d %d", &friendId, &person);
		list[person-1]->numfriends++;	

		if(list[person-1]->numfriends == 1){
			list[person-1]->friends = can_fail_malloc(sizeof(student*));
		}
		else{
			list[person-1]->friends = can_fail_realloc(list[person-1]->friends, (list[person-1]->numfriends)*sizeof(student*));
		}
		list[person-1]->friends[list[person-1]->numfriends-1] = list[friendId-1];
	}

    for(i = 0; i < students; i++){
        auxList[i] = list[i];
    }
	mergeSort(auxList, 0, students-1);
    
    for(i = 0; i < students; i++){
    	auxGrade = auxList[i]->grade;
        visit(auxList[i]);
        if(contador == students){
        	break;
        }
    }

	for(i = 0; i < students; i++){
		printf("%d\n", list[i]->grade);
	}

	return 0;
}