#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "list.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*==========================NODE==========================*/
Node NewNode(char *name){
    /*Reserves memory for a node*/
    Node new = (Node) can_fail_malloc(sizeof(node));

    /*Adds a name*/
    new->name = NewString(name);

    /*The node is always the last on the list 
    when created*/
    new->next = NULL;

    return new;
}


void DeleteNode(Node node){
    /*Frees the memory allocated for the name*/
    free(node->name);

    /*Frees the memory allocated for the node*/
    free(node);
}



/*==========================LIST==========================*/
List NewList(){
    /*Reserves memory for a list*/
    List new_list = (List) can_fail_malloc(sizeof(list));

    /*Points the head and tail to NULL*/
    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
}


void Append_List(List list, char *name){
    /*Creates a Node*/
    Node new = NewNode(name);

    /*First node added to the list*/
    if(!(list->head)){
        list->head = new;
        list->tail = new;

        return;
    }

    /*Changes the adress of next in last Node on the
    list and the tail, to the new Node*/
    (list->tail)->next = new;
    list->tail = new;
}


void Remove_List(List list, char *name){
    /*The node before the one that has the same name
    as the input*/
    Node tmp_aux = NULL;
    /*The node thas going to point to the one that has
    the same name as the input*/
    Node tmp = list->head;

    /*Searches for the node*/
    while(strcmp(tmp->name, name) != 0){
        tmp_aux = tmp;
        tmp = tmp->next;
    }

    /*If its the first node in the list*/
    if(tmp == list->head){
        list->head = tmp->next;   
    }
    
    else{
        tmp_aux->next = tmp->next;
    }

    /*If its the last one*/
    if(tmp == list->tail){
        list->tail = tmp_aux;
    }

    /*Deletes the node*/
    DeleteNode(tmp);
}


void Delete_List(List list){
    Node aux;

    /*Goes through the list deleting all present nodes*/
    while((list->head) != NULL){

        aux = list->head->next;
        DeleteNode(list->head);
        list->head = aux;
    }

    free(list);
}