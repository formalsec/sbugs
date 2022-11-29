#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*
 * File:	main.c
 * 
 * Author:	André Nascimento	92419
 * Author:	Francisco Malveiro	92465	
 * 
 * Serial: 	120320202126
 * 
 * A small algorithm to predict the marks of students based on their 
 * 	friendships.
 */



/*============================================================================*/
/*				Include directives			      */
/*============================================================================*/
#include <stdlib.h>
#include <stdio.h>



/*============================================================================*/
/*			File macros and constants			      */
/*============================================================================*/

/* Allows the usage of the TRUE and FALSE keywords. */
#define TRUE 	1
#define FALSE 	0

/* The number of possible marks (0 - 20). */
#define NMARKS 	21





/*============================================================================*/
/* 			Students' linked-list declaration		      */
/*============================================================================*/

typedef struct student Element;


/* Node structure - Each node contains an element of the list. */
typedef struct node
{
	Element *element;	/* The element stored on each node of the list. */
	struct node *next;		/* The next element of the list. */

} Node;


/* List structure - The list contains the first and the last node. */
typedef struct list 
{
	Node *head;		/* The first element of the list. */
	Node *tail;		/* The last element of the list. */

} *List;



/*! \brief Creates a new node.
 *
 *  Creates a new node with the specified data and returns its pointer.
 *
 * \param Element
 * 			The element to be stored in the node.
 * \return The node's pointer.
 */
Node *nodeCreate(Element *element);


/*! \brief Destroys a node.
 *
 *  Destroys the node given as argument and frees all the memory associated 
 *  with it.
 *
 * \param node
 * 			The node to destroy.
 * \return The element previously associated with the node.
 */
Element* nodeDestroy(Node *node);


/*! \brief Creates a new list.
 *
 *  Allocates a new list in memory.
 *
 * \return A pointer to the created list.
 */
List listCreate();


/*! \brief Destroys a list.
 *
 *  Destroys the list given as argument and frees all the memory associated 
 *  with it.
 *
 * \param list
 * 			The list to be destroyed.
 * \return Nothing.
 */
void listDestroy(List list);


/*! \brief Inserts a new element at the end of a list.
 *
 *  Creates a new node for the specified element and places it at the end of 
 *  the list. Note: linear time function - the pushFront method should be 
 *  preferred.
 *
 * \param  list
 * 		The list in which to insert the element.
 * \param  element
 * 		The element to be inserted.
 * \return Nothing.
 */
void listPushBack(List list, Element *element);


/*! \brief Inserts a new element at the beggining of a list.
 *
 *  Creates a new node for the specified element and places it at the front of 
 *  the list.
 *
 * \param  list
 * 		The list in which to insert the element.
 * \param  element
 * 		The element to be inserted.
 * \return Nothing.
 */
void listPushFront(List list, Element *element);


/*! \brief Removes the last element of a list.
 *
 *  Removes the last node of a given list, returning the element stored in it.
 *
 * \param  list
 * 			The list from which to remove the element.
 * \return The element contained in the removed node.
 */
Element* listPopBack(List list);


/*! \brief Removes the first element of a list.
 *
 *  Removes the first node of a given list, returning the element stored in it.
 *
 * \param  list
 * 			The list from which to remove the element.
 * \return The element contained in the removed node.
 */
Element* listPopFront(List list);


/*! \brief Returns an iterator to a list.
 *
 *  Returns the first node of a list that can then be with iterated with the 
 *  «next» pointer.
 *
 * \param list
 * 			The list whose iterator is going to be returned.
 * \return The list's iterator.
 */
Node* listIterator(List list);





/*============================================================================*/
/*				Student declaration			      */
/*============================================================================*/

typedef struct student 
{
	int mark;
	int visited;
	List friendships;

} Student;


/*! \brief Initialises a student.
 *
 *  Initialises a pre-allocated student with the specified mark.
 *
 * \param student 
 * 			The student to be initialised.
 * \param mark 
 * 			The student's mark.
 * \return The initialised student.
 */
Student* studentInit(Student *student, int mark);


/*! \brief Frees the memory associated with a student.
 *
 *  Frees all the memory allocated by the student without deleting him.
 *
 * \param student 
 * 			The student to be cleaned.
 * \return Nothing.
 */
void studentClear(Student *student);


/*! \brief Displays a student.
 *
 *  A student is displayed by showing their mark.
 *
 * \param student 
 * 			The student to be displayed.
 * \return Nothing.
 */
void studentDisplay(const Student *student);





/*============================================================================*/
/* 			Students' linked-list implementation		      */
/*============================================================================*/


/* Creates a new node. */
Node* nodeCreate(Element *element)
{
	Node *node = (Node*) can_fail_malloc(sizeof(Node));
	node->element = element;
	node->next = NULL;
	return node;
}


/* Destroys a node. */
Element *nodeDestroy(Node *node)
{
	Element *element = node->element;
	free(node);
	return element;
}


/* Creates a new list. */
List listCreate() 
{
	List list = (List) can_fail_malloc(sizeof(struct list));
	list -> head = NULL;
	list -> tail = NULL;
	return list;
}


/* Destroys a list. */
void listDestroy(List list)
{	
	Node *iterator = listIterator(list);
	while ((iterator = list->head) != NULL)
	{
		list->head = iterator->next;
		nodeDestroy(iterator);
	}

	free(list);
}


/* Inserts a new element at the end of the list. */
void listPushBack(List list, Element *element)
{
	Node *node = nodeCreate(element);

	if (list->head == NULL) 
		list->head = node;
	else
		list->tail->next = node;
	
	list->tail = node;
}


/* Inserts a new element at the beggining of the list. */
void listPushFront(List list, Element *element)
{
	Node *node = nodeCreate(element);

	if (list->head == NULL) 
		list->tail = node;
	else
		node->next = list->head;

	list->head = node;
}


/* Removes the last element of the list. */
Element* listPopBack(List list) 
{
	Node *temp, *iterator;

	/* empty list */
	if (list->head == NULL)
		return NULL;

	temp = list->tail;
	iterator = listIterator(list);

	/* list empty after the removal of the last element */
	if (iterator->next == NULL)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		/* gets the element before the last (linar time) */
		while (iterator->next != list->tail)	
			iterator = iterator->next;
		
		iterator->next = NULL;
		list->tail = iterator;
	}
	
	return nodeDestroy(temp);;
}

/* Removes the first element of the list. */
Element* listPopFront(List list)
{
	Node *temp;

	/* empty list */
	if (list->head == NULL)
		return NULL;
	
	temp = list->head;
	list->head = temp->next;
	list->tail = (list->head == NULL ? NULL : list->tail);
	return nodeDestroy(temp);
}


/* Removes an iterator to the list. */
Node* listIterator(List list)
{
	return list->head;
}





/*============================================================================*/
/*				Student implementation			      */
/*============================================================================*/


/* Initialises a student. */
Student* studentInit(Student *student, int mark) 
{
	student->mark = mark;
	student->visited = FALSE;
	student->friendships = listCreate();
	return student;
}


/* Frees the memory associated with a student. */
void studentClear(Student *student) 
{
	listDestroy(student->friendships);
}


/* Displays a student. */
void studentDisplay(const Student *student) 
{
	printf("%d\n", student->mark);
}



/*============================================================================*/
/*			Program basic functionality			      */
/*============================================================================*/


/*! \brief Reads the input file containing the students' info.
 *
 *  The input file is read, and the students are stored in an array. The 
 *  oldMarks array will also be filled as the students are read.
 *
 * \param students
 * 			A pointer to an array allocated by this function, where
 * 			the students will be stored.
 * \param oldMarks
 * 			An array containing 21 lists, where the students will
 * 			be organised by their old mark.
 * \return The number of students processed/in the students' array.
 */
int processInput(Student **students, List oldMarks[NMARKS])
{
	int i, mark, first, second, nStudents, nFriendships;
	Student *pStudents;
	

	/* Gets the total of students and friendships */
	scanf("%d,%d", &nStudents, &nFriendships);

	/* Allocates student array of size n */
	*students = (Student*) can_fail_malloc(nStudents * sizeof(Student));
	pStudents = *students;

	/* Reads the students and stores them */
	for (i = 0; i < nStudents; i++)
	{
		scanf("%d", &mark);
		studentInit(&pStudents[i], mark);
		listPushFront(oldMarks[mark], &pStudents[i]);
	}
	
	/* Reads the students friendships and stores them in each student */
	for (i = 0; i < nFriendships; i++)
	{
		scanf("%d %d", &first, &second);
	/*	listPushBack(pStudents[first - 1].friendships, &pStudents[second - 1]);*/
		listPushBack(pStudents[second - 1].friendships, &pStudents[first - 1]);
	}

	return nStudents;
}


/*! \brief Propagates one student's mark to each of his friends.
 *
 *  The student's mark is propagated to each of his friends, regardless of 
 *  their old mark. The propagation is done using a Breadth First Search
 *  (BFS) on the friendships tree.
 *
 * \param  student
 * 			The student whose mark will be propagated.
 * \return The number of students processed during the BFS.
 */
int propagateMark(Student *student)
{
	int mark = student->mark, studentsProcessed = 0;
    Student *friend;
	List queue = listCreate();
	listPushBack(queue, student);

	/* Processes the queue until its empty */
	while ((student = listPopFront(queue)) != NULL)	
	{
		/* Ignores students that have already been processed */
		if (student->visited)	
			continue;
		
		student->visited = 1;
		student->mark = mark;
		studentsProcessed++;
		while ((friend = listPopFront(student->friendships)) != NULL)
			listPushBack(queue, friend);
	}

	listDestroy(queue);
	return studentsProcessed;
}


/*! \brief Calculates the students' new predicted marks.
 *
 *  The students' marks are calculated based on their friendships. If a student
 *  is friends of another, then he'll have the same mark as his friend, since 
 *  they share their works.
 *
 * \param students
 * 			The array where the students are stored.
 * \param oldMarks
 * 			An array containing 21 lists, where the students are
 * 			organised by their old mark.
 * \param nStudents
 * 			The number of students stored in the students array.
 */
void calcNewMarks(Student *students, List oldMarks[NMARKS], int nStudents)
{
	int markIndex, studentsProcessed = 0;
	Student *student;

	/* Iterates through each of the possible marks: NMARKS [0-20] */
	for (markIndex = NMARKS - 1; markIndex > 0; markIndex--) 
	{
		/* Process the list while it's not empty */
		while ((student = listPopFront(oldMarks[markIndex])) != NULL)
			if (!student->visited)
				studentsProcessed += propagateMark(student);	
		
		/* Stops earlier if all the students have been processed */
		if (studentsProcessed == nStudents) 
			break;
	}
}


/*! \brief Outputs all the students' marks.
 *
 *	The marks are printed one in each line, from the first to the last student
 * 	read during the input processing stage.
 * 
 * 	\param students
 * 			The array where the students are stored.
 * 	\param nStudents
 * 			The number of students stored in the students array.
 */
void outputMarks(const Student *students, int nStudents)
{
	int i;
	for (i = 0; i < nStudents; i++)
		studentDisplay(&students[i]);
}


/*============================================================================*/
/*				main function				      */
/*============================================================================*/

int main(int argc, char *argv[])
{
	int i, nStudents;
	
	/* Array containing all students. */
	Student *students;

	/* Array containing 21 lists, one for each mark. */
	List oldMarks[NMARKS];
	
	/* Initialises the lists in the oldMarks array */
	for (i = 0; i < NMARKS; i++) {
		oldMarks[i] = listCreate();
	}


	/* Reads the input file and stores its data on the respective structures */
	nStudents = processInput(&students, oldMarks);

	/* Calculates the new marks of the students based on their friendships */
	calcNewMarks(students, oldMarks, nStudents);

	/* Outputs the new prediction of the students' marks */
	outputMarks(students, nStudents);


	/* Frees the memory associated with the oldMarks lists */
	for (i = 0; i < NMARKS; i++)
		listDestroy(oldMarks[i]);

	/* Frees the memory associated with each student */
	for (i = 0; i < nStudents; i++)
		studentClear(&students[i]);

	free(students);
	return 0;
}
