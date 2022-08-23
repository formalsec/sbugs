#include <stdlib.h>
#include <stdio.h>
#include<limits.h>

typedef struct List{
	struct Link* tail;
}* list;

typedef struct Link{
	struct Student* student;
	struct Link* prev;
}* link;

typedef struct Graph{
	struct Student** students;
	int n_students;
	int visited;
	struct List* tarj_list;
}* graph;

typedef struct Student{
	int id;
	int d;
	int low;
	int in_list;
	int color;
	int grade_est;
	int* new_estim;
	struct FriendLink* rel;
}* student;

typedef struct FriendLink{
	struct Student* friend;
	struct FriendLink* next;
}* friendLink;



graph newGraph(int n_students);
list newList();
link newLink(student s);
void push(list lst, student s);
student pop(list lst);
int min(int n, int m);
student newStudent(int id, int grade);
void newFriend(student stud, student friend);
void dfs(graph studentGraph);
void dfsVisit(student stud);
void tarjan(graph studentGraph);
void tarjanVisit(graph sGraph, student s);



graph newGraph(int n_students){
	graph new = (graph) malloc(sizeof(struct Graph));
	new->students = (student*) malloc(sizeof(student) * n_students);
	new->n_students = n_students;
	new->visited = 0;
	new->tarj_list = newList();
	return new;
}

list newList(){
	list new = (list) malloc(sizeof(struct List));
	new->tail = NULL;
	return new;
}

link newLink(student s){
	link new = (link) malloc(sizeof(struct Link));
	new->student = s;
	new->prev = NULL;
	return new;
}

void push(list lst, student s){
	link lnk = newLink(s);
	lnk->prev = lst->tail;
	lst->tail = lnk;
}

student pop(list lst){
	link aux = lst->tail;
	student aux_s = aux->student;
	lst->tail = aux->prev;
	free(aux);
	return aux_s;
}

int min(int n, int m){
	if (n < m)
		return n;
	else
		return m;
}

student newStudent(int id, int grade){
	student new = (student) malloc(sizeof(struct Student));
	new->color = 0;
	new->in_list = 0;
	new->d = INT_MAX;
	new->low = INT_MAX;
	new->id = id;
	new->grade_est = grade;
	new->rel = NULL;
	new->new_estim = NULL;
	return new;
}

void newFriend(student stud, student friend){
	friendLink new_rel = (friendLink) malloc(sizeof(struct FriendLink));
	new_rel->friend = friend;
	new_rel->next = stud->rel;
	stud->rel = new_rel;
}

void dfs(graph studentGraph){
	int i;
	/*for (i = 0; i < studentGraph->n_students; i++){
		studentGraph->students[i]->color = 0;
	}*/
	for (i = 0; i < studentGraph->n_students; i++){
		if (studentGraph->students[i]->color == 0)
			dfsVisit(studentGraph->students[i]);
	}
}

void dfsVisit(student stud){
	friendLink relationship = stud->rel;
	stud->color = 1;
	while (relationship != NULL){
		if (relationship->friend->color == 0){
			dfsVisit(relationship->friend);
		}
		if ( *(stud->new_estim) < *(relationship->friend->new_estim)){
			*(stud->new_estim) = *(relationship->friend->new_estim);
		}
		relationship = relationship->next;
	}
}

void tarjan(graph studentGraph){
	int i;
	/*for(i=0; i < studentGraph->n_students; i++){
		studentGraph->students[i]->d = INT_MAX;
		studentGraph->students[i]->low = INT_MAX;
		studentGraph->students[i]->in_list = 0;
	}*/
	for(i=0; i < studentGraph->n_students; i++){
		if(studentGraph->students[i]->d == INT_MAX){
			tarjanVisit(studentGraph, studentGraph->students[i]);
		}
	}
}

void tarjanVisit(graph sGraph, student s){
	student stack_s;
	int* shared_estim_ptr;
	friendLink adj = s->rel;
	sGraph->visited++;
	s->d = sGraph->visited;
	s->low = sGraph->visited;
	s->in_list = 1;
	push(sGraph->tarj_list, s);
	while (adj != NULL){
		if(adj->friend->d == INT_MAX){
			tarjanVisit(sGraph, adj->friend);
			s->low = min(s->low, adj->friend->low);
		}
		else if(adj->friend->in_list == 1){
			s->low = min(s->low, adj->friend->d);
		}
		adj = adj->next;
	}
	if (s->low == s->d){
		shared_estim_ptr = (int*) malloc(sizeof(int));
		*shared_estim_ptr = INT_MIN;
		do{
			stack_s = pop(sGraph->tarj_list);
			if (*shared_estim_ptr < stack_s->grade_est){
				*shared_estim_ptr = stack_s->grade_est;
			}
			stack_s->new_estim = shared_estim_ptr;
			stack_s->in_list = 0;
		} while(s->id != stack_s->id);
	}
}


int main(int argc, char* argv[]){
	int n_rel, n_students, grade, stud_id, friend_id, i;
	friendLink rel, aux_rel;
	graph studentGraph;

	scanf("%d,%d", &n_students, &n_rel);
	studentGraph = newGraph(n_students);
	for (i = 0; i < n_students; i++){
		scanf("%d", &grade);
		studentGraph->students[i] = newStudent(i, grade);
	}
	for (i = 0; i < n_rel; i++){
		scanf("%d %d", &stud_id, &friend_id);
		newFriend(studentGraph->students[stud_id-1],studentGraph->students[friend_id-1]);
	}

	tarjan(studentGraph);
	dfs(studentGraph);

	for (i = 0; i < n_students; i++){
		printf("%d\n", *(studentGraph->students[i]->new_estim));
	}

	for (i = 0; i < n_students; i++){
		rel = studentGraph->students[i]->rel;
		while(rel != NULL){
			aux_rel = rel->next;
			free(rel);
			rel = aux_rel;
		}
		if (studentGraph->students[i]->new_estim != NULL){
			free(studentGraph->students[i]->new_estim);
		}
		free(studentGraph->students[i]);
	}
	free(studentGraph->students);
	free(studentGraph->tarj_list);
	free(studentGraph);

	return 0;
}