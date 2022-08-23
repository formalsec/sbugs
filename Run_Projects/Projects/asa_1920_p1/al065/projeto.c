/* Francisco Lisboa 92464 */
/* Freddy De Lima 92466 */
#include <stdio.h>
#include <stdlib.h>


/*									+--------------------+
									|        Stack       |
									+--------------------+
*/

typedef struct stack {
    int val;
    struct stack *next;
} Stack; 

Stack *last;

void stack_init(){
    last = NULL;
}

void push(int val){
    Stack *new_elem = malloc(sizeof(Stack));
    new_elem->val = val;
    if(last == NULL){
        new_elem->next = NULL;
    }
    else{
        new_elem->next = last;
    }
    last = new_elem;
}

int pop(){
    if(last==NULL) return -1; /* ERROR*/
    int val = last->val;
    Stack *d = last;
    last = last->next;
    free(d);
    return val;
}

/*									+--------------------+
									|       Student      |
									+--------------------+
*/

typedef struct node {
    int num;
    struct node *next;
} Node;

typedef struct {
    int grade;
    
    /* For Tarjan Algorithm*/
    int d;
    int low;
    int inStack;
    
    Node *friends;
} Student;


Student *students;

int visited;

void init_students(int num_students){
    students = malloc(num_students * sizeof(Student));
    int i;
    for(i = 0; i < num_students; i++){
        students[i].friends = NULL;
        students[i].low = 0;
        students[i].d = -1;
        students[i].inStack = 0;
    }
}

void addGrade(int index,int grade){
    students[index].grade = grade;
}

void addFriendship(int from, int to){
    if(students[from].friends){
        Node* iter = students[from].friends;
        while(iter->next){
            iter = iter->next;
        }
        iter->next = (Node*)malloc(sizeof(Node));
        iter->next->num = to;
        iter->next->next = NULL;
    }
    else{
        students[from].friends = (Node*)malloc(sizeof(Node));
        students[from].friends->num = to;
        students[from].friends->next = NULL;
    }
    
}

void freeStudents(int num_students){
    Node *aux;
    int i;
    for(i = 0; i < num_students; i++){
        while(students[i].friends){
            aux = students[i].friends;
            students[i].friends = aux->next;
            free(aux);
        }
    }
    free(students);
}


void tarjan_visit(int i, int num_students){
    students[i].d = students[i].low = visited;
    visited++;
    push(i);
    students[i].inStack = 1;
    Node *iter;
    iter = students[i].friends;
    while(iter){
        if(students[iter->num].d == -1 || students[iter->num].inStack){
            if(students[iter->num].d == -1){
                tarjan_visit(iter->num, num_students);
            }
            if(students[i].low > students[iter->num].low)
                students[i].low = students[iter->num].low;
        }
        if(students[i].grade < students[iter->num].grade)
            students[i].grade = students[iter->num].grade;
        iter = iter->next;
    }
    if(students[i].low == students[i].d){
        int SCC[num_students];
        int j, k = 1, biggrade = students[i].grade;
        students[i].inStack = 0;
        SCC[0] = i;
        for(j = pop(); i != j; j = pop(), k++){
            students[j].inStack = 0;
            SCC[k] = j;
            if(students[j].grade > biggrade) biggrade = students[j].grade;
        }
        for(j = 0; j != k; j++){
            students[SCC[j]].grade = biggrade;
        }
    }
}

void findSCCs(int num_students){
    visited = 0;
    int i;
    for(i = 0; i < num_students; i++){
        if(students[i].d == -1)
            tarjan_visit(i, num_students);
    }
}

/*APAGAR*/
void test(int val){
        
    findSCCs(val);

    int i;
    for(i = 0; i < val; i++)
        printf("%d\n", students[i].grade);
}

/*									+--------------------+
									|        Main        |
									+--------------------+
*/

int main(){

    int num_students, num_friends;

    scanf("%d,%d", &num_students, &num_friends); 

    init_students(num_students);

    int grade;
    int i;
    for(i = 0; i < num_students; i++){
        scanf("%d", &grade);
        addGrade(i, grade);
    }

    int from, to;
    for(i = 0; i < num_friends; i++){
        scanf("%d %d", &from, &to);
        addFriendship(from - 1, to - 1);
    }
    test(num_students);

    freeStudents(num_students);

    return 0;

}


