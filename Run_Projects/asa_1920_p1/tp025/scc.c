#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct stru_student
{
    int d, low, grade, in_stack, num_friends, group, visited;
    struct stru_student **frients;
} * Student;

typedef struct stru_stack
{
    int top;
    Student *array;
} Stack;

Stack *stack;
Student *students;
int *group;
int time = 0, g = 0;

void initialize(int *num_students, int *num_relations);
void DFS(int n);
void DFS_visit(Student current);
void Tarjan(int size);
void Tarjan_visite(Student student);
void print_grade(int n);
Student create_student(int id, int grade);
void add_relation(int src, int dest);

Stack *create_stack(int size);
int is_empty();
void push(Student student);
Student pop();

int main()
{
    int num_students, num_relations;
    initialize(&num_students, &num_relations);
    Tarjan(num_students);
    DFS(num_students);
    print_grade(num_students);
    return 0;
}

void initialize(int *num_students, int *num_relations)
{
    scanf("%d,%d", num_students, num_relations);
    students = malloc(*num_students * sizeof(Student));
    group = malloc(*num_students * sizeof(int));
    stack = malloc(sizeof(Stack));
    stack->top = -1;
    int grade, i, src, dest;
    for (i = 0; i < *num_students; i++)
    {
        scanf("%d", &grade);
        students[i] = create_student(i, grade);
    }
    for (i = 0; i < *num_relations; i++)
    {
        scanf("%d %d", &src, &dest);
        add_relation(src - 1, dest - 1);
    }
}

void print_grade(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d\n", group[students[i]->group]);
    }
}

void DFS(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (students[i]->visited == FALSE)
            DFS_visit(students[i]);
    }
}

void DFS_visit(Student current)
{
    current->visited = TRUE;
    int i;
    for (i = 0; i < current->num_friends; i++)
    {
        Student temp = current->frients[i];
        if (temp->visited == FALSE)
            DFS_visit(temp);
        if (current->group != temp->group)
            group[current->group] = MAX(group[current->group], group[temp->group]);
    }
}

void Tarjan(int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (students[i]->d == -1)
            Tarjan_visite(students[i]);
    }
}

void Tarjan_visite(Student student)
{
    student->d = time;
    student->low = time;
    time++;
    push(student);
    int i, max;
    Student next_student;
    for (i = 0; i < student->num_friends; i++)
    {
        next_student = student->frients[i];
        if (next_student->d == -1 || next_student->in_stack == TRUE)
        {
            if (next_student->d == -1)
                Tarjan_visite(next_student);
            student->low = MIN(student->low, next_student->low);
        }
    }
    if (student->d == student->low)
    {
        Student temp = pop();
        temp->group = g;
        max = temp->grade;
        while (temp->d != student->d && temp != NULL)
        {
            temp = pop();
            temp->group = g;
            max = MAX(temp->grade, max);
        }
        group[g++] = max;
    }
}

Student create_student(int id, int grade)
{
    Student new_student = malloc(sizeof(struct stru_student));
    new_student->d = -1;
    new_student->in_stack = FALSE;
    new_student->grade = grade;
    new_student->frients = NULL;
    new_student->num_friends = 0;
    new_student->group = -1;
    new_student->visited = FALSE;
    return new_student;
}

void add_relation(int src, int dest)
{
    Student friend = students[dest];
    Student student = students[src];
    student->frients = realloc(student->frients, (student->num_friends + 1) * sizeof(Student));
    student->frients[student->num_friends] = friend;
    student->num_friends++;
}

Stack *create_stack(int size)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->top = -1;
    stack->array = malloc(size * sizeof(Student));
    return stack;
}

int is_empty()
{
    return stack->top == -1;
}

void push(Student student)
{
    stack->top++;
    stack->array = realloc(stack->array, (stack->top + 1) * sizeof(Student));
    stack->array[stack->top] = student;
    student->in_stack = TRUE;
}

Student pop()
{
    if (is_empty(stack))
        return NULL;
    Student student = stack->array[stack->top];
    stack->top--;
    stack->array = realloc(stack->array, (stack->top + 1) * sizeof(Student));
    student->in_stack = FALSE;
    return student;
}

/*
https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
*/