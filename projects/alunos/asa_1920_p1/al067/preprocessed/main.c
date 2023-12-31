#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>


typedef struct student Element;
typedef struct node
{
  Element *element;
  struct node *next;
} Node;
typedef struct list
{
  Node *head;
  Node *tail;
} *List;
Node *nodeCreate(Element *element);
Element *nodeDestroy(Node *node);
List listCreate();
void listDestroy(List list);
void listPushBack(List list, Element *element);
void listPushFront(List list, Element *element);
Element *listPopBack(List list);
Element *listPopFront(List list);
Node *listIterator(List list);
typedef struct student
{
  int mark;
  int visited;
  List friendships;
} Student;
Student *studentInit(Student *student, int mark);
void studentClear(Student *student);
void studentDisplay(const Student *student);
Node *nodeCreate(Element *element)
{
  Node *node = (Node *) malloc(sizeof(Node));
  node->element = element;
  node->next = 0;
  return node;
}

Element *nodeDestroy(Node *node)
{
  Element *element = node->element;
  free(node);
  return element;
}

List listCreate()
{
  List list = (List) malloc(sizeof(struct list));
  list->head = 0;
  list->tail = 0;
  return list;
}

void listDestroy(List list)
{
  Node *iterator = listIterator(list);
  while ((iterator = list->head) != 0)
  {
    list->head = iterator->next;
    nodeDestroy(iterator);
  }

  free(list);
}

void listPushBack(List list, Element *element)
{
  Node *node = nodeCreate(element);
  if (list->head == 0)
  {
    list->head = node;
  }
  else
  {
    list->tail->next = node;
  }

  list->tail = node;
}

void listPushFront(List list, Element *element)
{
  Node *node = nodeCreate(element);
  if (list->head == 0)
  {
    list->tail = node;
  }
  else
  {
    node->next = list->head;
  }

  list->head = node;
}

Element *listPopBack(List list)
{
  Node *temp;
  Node *iterator;
  if (list->head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  temp = list->tail;
  iterator = listIterator(list);
  if (iterator->next == 0)
  {
    list->head = 0;
    list->tail = 0;
  }
  else
  {
    while (iterator->next != list->tail)
      iterator = iterator->next;

    iterator->next = 0;
    list->tail = iterator;
  }

  return nodeDestroy(temp);
  ;
}

Element *listPopFront(List list)
{
  Node *temp;
  if (list->head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  temp = list->head;
  list->head = temp->next;
  list->tail = (list->head == 0) ? (0) : (list->tail);
  return nodeDestroy(temp);
}

Node *listIterator(List list)
{
  return list->head;
}

Student *studentInit(Student *student, int mark)
{
  student->mark = mark;
  student->visited = 0;
  student->friendships = listCreate();
  return student;
}

void studentClear(Student *student)
{
  listDestroy(student->friendships);
}

void studentDisplay(const Student *student)
{
  printf("%d\n", student->mark);
}

int processInput(Student **students, List oldMarks[21])
{
  int i;
  int mark;
  int first;
  int second;
  int nStudents;
  int nFriendships;
  Student *pStudents;
  nStudents = new_sym_var(sizeof(int) * 8);
  nFriendships = new_sym_var(sizeof(int) * 8);
  *students = (Student *) malloc(nStudents * (sizeof(Student)));
  pStudents = *students;
  for (i = 0; i < nStudents; i++)
  {
    mark = new_sym_var(sizeof(int) * 8);
    studentInit(&pStudents[i], mark);
    listPushFront(oldMarks[mark], &pStudents[i]);
  }

  for (i = 0; i < nFriendships; i++)
  {
    first = new_sym_var(sizeof(int) * 8);
    second = new_sym_var(sizeof(int) * 8);
    listPushBack(pStudents[second - 1].friendships, &pStudents[first - 1]);
  }

  return nStudents;
}

int propagateMark(Student *student)
{
  int mark = student->mark;
  int studentsProcessed = 0;
  Student *friend;
  List queue = listCreate();
  listPushBack(queue, student);
  while ((student = listPopFront(queue)) != 0)
  {
    if (student->visited)
    {
      continue;
    }
    else
    {
      
    }

    student->visited = 1;
    student->mark = mark;
    studentsProcessed++;
    while ((friend = listPopFront(student->friendships)) != 0)
      listPushBack(queue, friend);

  }

  listDestroy(queue);
  return studentsProcessed;
}

void calcNewMarks(Student *students, List oldMarks[21], int nStudents)
{
  int markIndex;
  int studentsProcessed = 0;
  Student *student;
  for (markIndex = 21 - 1; markIndex > 0; markIndex--)
  {
    while ((student = listPopFront(oldMarks[markIndex])) != 0)
      if (!student->visited)
    {
      studentsProcessed += propagateMark(student);
    }
    else
    {
      
    }


    if (studentsProcessed == nStudents)
    {
      break;
    }
    else
    {
      
    }

  }

}

void outputMarks(const Student *students, int nStudents)
{
  int i;
  for (i = 0; i < nStudents; i++)
    studentDisplay(&students[i]);

}

int main(int argc, char *argv[])
{
  int i;
  int nStudents;
  Student *students;
  List oldMarks[21];
  for (i = 0; i < 21; i++)
  {
    oldMarks[i] = listCreate();
  }

  nStudents = processInput(&students, oldMarks);
  calcNewMarks(students, oldMarks, nStudents);
  outputMarks(students, nStudents);
  for (i = 0; i < 21; i++)
    listDestroy(oldMarks[i]);

  for (i = 0; i < nStudents; i++)
    studentClear(&students[i]);

  free(students);
  return 0;
}

