#ifndef LIST_H
#define LIST_H


/*==========================NODE==========================*/
typedef struct node{

    /*Name of something*/
    char *name;
    /*Adress of the next node*/
    struct node *next;

}node;

/*Pointer to the node structure*/
typedef node *Node;


/*Creates a new node and returns its memory adress*/
Node NewNode(char *name);


/*Completely destoys the node*/
void DeleteNode(Node node);



/*==========================LISTS==========================*/
typedef struct list{

    /*Head of the list*/
    Node head;
    /*Tail of the list*/
    Node tail;

}list;

/*Pointer to the list structure*/
typedef list *List;


/*Creates a new list*/
List NewList();


/*Adds a name to the list*/
void Append_List(List list, char *name);


/*Removes a name from the list*/
void Remove_List(List list, char *name);


/*Deletes a list*/
void Delete_List(List list);


#endif