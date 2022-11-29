#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "main.h"

/* Initialize the list */
Node_ptr init(){
    Node_ptr top;
    top = NULL;
    return top;
}

/* Push a value to the top of the list */
Node_ptr push(char *value, Node_ptr top){
    Node_ptr new;
    int size;
    new = can_fail_malloc(sizeof(struct node));
    
    if(top==NULL){
        new->value = value;
        new->next=NULL;
        new->prev=NULL;
        top=new;
        top->size = 0;
        top->first = top;

        return top;    
    }
    new->value = value;
    new->next = top;
    new->first = top->first;
    new->prev = NULL;
    top->prev = new;
    
    size = top->size;
    
    top = new;
    new->size = size + 1;
    
    return top;
}

/*  Check if the list is empty */
int is_empty(Node_ptr top){
    return top == NULL;
}

/* Delete the value at a certain index */
Node_ptr delete_index(int index, Node_ptr top){
    int amount, counter;
    Node_ptr aux;
    amount = top->size - index;
    aux = top;
    /* Find what I want to delete */
    for(counter = 0; counter < amount; counter++){
        top->size = top->size - 1;
        top = top->next;
    }

    /* If its the only one */
    if(top->prev == NULL && top->next == NULL){
        free(top);
        top = NULL;
        return top;
    }

    /* If its in the middle */
    if(top->prev != NULL && top->next != NULL){
        top->prev->next = top->next;
        top->next->prev = top->prev;
    }

    /* If its at the beggining */
    if(top->next == NULL && top->prev != NULL){
        top->prev->next = NULL;
        aux->first = top->prev;
    }

    /* If its at the top */
    if(top->prev == NULL && top->next != NULL){
        aux = top->next;
        aux->first = top->first;
        top->next->prev = NULL;
    }

    /* free(top->value); */
    free(top);
    return aux;
}

/* Delete all of the values in the list */
void clear_all(Node_ptr top){
    Node_ptr aux;
    
    while(top != NULL){
        aux = top->next;
        free(top);
        top = aux;
    }

    return;
}

/* Print all of the values (if flag set to 1 the direction will be right to left) */
void print_all(int side_flag, Node_ptr top){
    Node_ptr aux;
    aux = top;
    while(aux != NULL){
        printf("%d %s\n", aux->size, aux->value);
        if(side_flag==1)aux = aux->next;
        else aux = aux->prev;
    }

    return; 
}

/* Return the pointer to the node corresponding to the given index */
Node_ptr get_index(int index, Node_ptr top){
    int amount, counter;

    amount = top->size - index;
    for(counter = 0; counter < amount; counter++){
        top = top->next;
    }
    return top;
}
