#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
     
typedef struct node {
  int id;
  int grade;
  struct node** friend; 
  int totalFriends; 
}node;

typedef struct data {
  node** studentsArray; 
  node** friendshipsArray; 
  int* visited;  
  int listsCounter; 
}Data;

Data* studentData; 

int* queue;
int top = -1; 


int isEmpty();
int isFull();
int pop(); 
void push(int vertex); 
void BFS(int firstStudent); 

node* createNode(int id, int grade) {

  node* student = (node*)can_fail_malloc(sizeof(node)); 
  student->totalFriends = 0; 
  student->friend = (node**)can_fail_malloc(sizeof(node*));
  student->id = id; 
  student->grade = grade;
  student->friend[0] = NULL; 
  
  return student; 
}

void addFriendship(int studentId, int friendId) {
  node* student = studentData->studentsArray[studentId]; 
  node* friend =  studentData->studentsArray[friendId];
  int relation = 0;
  student->totalFriends++;
  student->friend = (node**)can_fail_realloc(student->friend, sizeof(node*)*(student->totalFriends+1));
  if (student->friend[relation] == NULL) {
    student->friend[relation] = friend; 
    student->friend[relation+1] = NULL;
    studentData->friendshipsArray[studentData->listsCounter] = student;
    studentData->listsCounter++; 
  }
  else {
    relation = student->totalFriends-1; 
    student->friend[relation] = friend; 
    student->friend[relation+1] = NULL;
  } 
}

Data* initStudentData(int nStudents, int nFriendships){
  Data* data = (Data*) can_fail_malloc(sizeof(Data));  
  int student; 

  data->studentsArray = (node**)can_fail_malloc(sizeof(node*)*nStudents);
  data->friendshipsArray = (node**)can_fail_malloc(sizeof(node*)*nStudents);
  data->visited = (int*)can_fail_malloc(sizeof(int)*nStudents);
  data->listsCounter = 0; 

  for (student = 0; student < nStudents; student++) {
    data->studentsArray[student] = NULL; 
    data->visited[student] = 0; 
  }
  for (student = 0; student < nStudents; student++) {
    data->friendshipsArray[student] = NULL; 
  }

  return data; 
}

void merge(int l, int m, int r) { 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 

    node* L[n1];
    node* R[n2]; 
    
    for (i = 0; i < n1; i++) 
        L[i] = studentData->friendshipsArray[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = studentData->friendshipsArray[m + 1+ j]; 
  
    i = 0; 
    j = 0;
    k = l; 
    while (i < n1 && j < n2) { 
        if (L[i]->grade <= R[j]->grade) { 
            studentData->friendshipsArray[k] = L[i]; 
            i++; 
        } 
        else { 
            studentData->friendshipsArray[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) { 
        studentData->friendshipsArray[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) { 
        studentData->friendshipsArray[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void mergeSort(int l, int r) { 
    if (l < r) { 
        int m = l+(r-l)/2; 
  
        mergeSort(l, m); 
        mergeSort(m+1, r); 
        merge(l, m, r); 
    } 
} 

int isEmpty() {
   if(top == -1)
      return 1;
   else
      return 0;
}

int isFull() {
  
   if(top == 50)
      return 1;
   else
      return 0;
}  

void push(int vertex) {

   if(!isFull()) {
      top = top + 1;   
      queue[top] = vertex;
   } 
}

int pop() {

   int data;
   
   if(!isEmpty()) {
      data = queue[top];
      top = top - 1;   
      return data;
   } else {
      return -1; 
   }
}


void BFS(int firstStudent) {
  queue = (int*)can_fail_malloc(sizeof(int)*50); 
  int flag, friend; 

  studentData->visited[firstStudent] = 1; 
  push(firstStudent);

  while(!isEmpty()) {
    int currentVertex = pop();
    if(currentVertex == -1) break;
    node* student = studentData->studentsArray[currentVertex]; 

    while(student != NULL ) { 

        flag = 0;  

        for (friend = 0; friend < student->totalFriends; friend++) {
            if (student->friend[friend] != NULL) {
                int studentId = student->friend[friend]->id;
                if(studentData->visited[studentId] == 0) {
                    studentData->visited[studentId] = 1; 
                    push(studentId); 
                    if(student->grade > student->friend[friend]->grade) {
                        student->friend[friend]->grade = student->grade;
                    }   
                } 
            else {        
                flag = 1;  
            }
            } else {
                flag = 1;  
            } 
        }
        if (flag == 1) {
            break; 
        }
        int currentVertex = pop();  
        if(currentVertex == -1) break;
        student = studentData->studentsArray[currentVertex];
    } 
  }
  free(queue);
}

void freeStudentsArray(int nStudents) {
  int student;   
  for(student = 0; student < nStudents; student++) {
    free(studentData->studentsArray[student]->friend);
    free(studentData->studentsArray[student]);
  }
  free(studentData->studentsArray);
  free(studentData->friendshipsArray);
  free(studentData->visited);  
  free (studentData);
}

void processInput() {
  int nStudents, nFriendships, student, friend, grade, relation = 0, studentId; 
 
  scanf("%d,%d", &nStudents, &nFriendships);

  if (nStudents < 2 || nFriendships < 1) {
    exit(1);
  } 
  studentData = initStudentData(nStudents, nFriendships);

  for (studentId = 0; studentId < nStudents; studentId++) {  
    scanf("%d", &grade);
    studentData->studentsArray[studentId] = createNode(studentId, grade); 
  }

  for (relation = 0; relation < nFriendships; relation++) { 
    scanf("%d %d", &student, &friend);
    addFriendship(friend-1, student-1); 
  }

  mergeSort(0, studentData->listsCounter - 1);
 
  for (relation = studentData->listsCounter-1; relation >= 0; relation--) {
    if (studentData->visited[studentData->friendshipsArray[relation]->id] == 0)
        BFS(studentData->friendshipsArray[relation]->id);
    else continue; 
  }
  
  for (student = 0; student < nStudents; student++) {
    printf("%d\n", studentData->studentsArray[student]->grade);
  }

  freeStudentsArray(nStudents);
}

int main() {
  processInput();
  return 0;
}
