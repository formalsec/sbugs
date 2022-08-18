#include "Generic_Linked_List.h"

/*
Cria uma nova lista ligada
*/
Link linkedlist_create(){
    return NULL;
}

/*
Cria um elemento de lista ligada
*/
Link create_node(void *data,int size){
    int i;
    Link node_link = (Link) malloc(sizeof(Node));
    node_link->next = NULL;
    node_link->length = 0;
    node_link->data = malloc(size);

    /* Como "char" apenas ocupa 1 byte, uso isto para copiar a informacao byte por byte */
    for (i = 0; i<size; i++){
        *((char *)node_link->data + i) = *((char *)data+i); 
    }
    
    return node_link;
}

/*
Liberta um elemento da lista
*/
void free_node(Link head,void (*free_data)(void*)){
    free_data(head->data);
    free(head);
}

/*
Adiciona um elemento a uma lista ligada
*/
void linkedlist_add_item(Link *list,void *data,int size){
    if (*list == NULL){
        *list = create_node(data,size);
        linkedlist_set_length(*list,1);
        return;
    }
    linkedlist_add_item(&((*list)->next),data,size);
    linkedlist_set_length(*list,linkedlist_get_length(*list) + 1);
}

/*
Funcao auxiliar que remove um elmento que nao seja o primeiro
*/
void delete_item_aux(Link previous,Link item,void(*free_data)(void *)){
    Link aux= item;
    previous->next = item->next;
    free_node(aux,free_data);
}

/*
Funcao auxiliar
*/
void linkedlist_delete_item_aux(Link *head,int i,int *count,void (*free_data)(void *)){

    if ((*head)->next == NULL) return;
    if (*count!= i-1){
        (*count)++;
        linkedlist_delete_item_aux(&(*head)->next,i,count,free_data);
    }else
        delete_item_aux(*head,(*head)->next,free_data);
}


/* 
Remove,de uma lista ligada, o elemento de uma dada posicao
*/
void linkedlist_delete_item(Link *head,int i,void (*free_data)(void *)){
    int count = 0;
    if (*head == NULL){
        free_node(*head,free_data);
        *head = NULL;
    }
    
    linkedlist_delete_item_aux(head,i,&count,free_data);
}

/*
Funcao auxiliar
*/
void linkedlist_delete_item_cmp_aux(Link *head,void *info,void *(*get_info)(void *),void(*free_data)(void *),int (*compare)(void *,void *)){
    if ((*head)->next == NULL) return;
    if (compare(info,get_info((*head)->next->data))){
        delete_item_aux(*head,(*head)->next,free_data);
        return;
    }
    linkedlist_delete_item_cmp_aux(&(*head)->next,info,get_info,free_data,compare);
}

/*
Remove,de uma lista ligada, o primeiro elemento com informacao igual a dada
*/
void linkedlist_delete_item_cmp(Link *head,void *info,void *(*get_info)(void *),void(*free_data)(void*),int (*compare)(void *,void *)){
    if (*head == NULL) return;
    if (compare(info,get_info((*head)->data))){
        free_node(*head,free_data);
        *head = NULL;
        return;
    }
    linkedlist_delete_item_cmp_aux(head,info,get_info,free_data,compare);
}

/*
Liberta uma lista ligada
*/
void linkedlist_free(Link head,void (*free_data)(void*)){
    if (head != NULL){
        linkedlist_free(head->next,free_data);
        free_node(head,free_data);
    }
}

/*
Percorre uma lista ligada e realiza uma acao sobre cada item
*/
void linkedlist_traverse(Link head,void (*func)(void *)){
    if (head != NULL){
        func(head->data);
        linkedlist_traverse(head->next,func);
    }
}

/*
Funcao auxiliar
*/
void *linkedlist_get_item_aux(Link head,int i,int *count){
    if (head == NULL) return NULL;
    if (i != *count){
        (*count)++;
        return linkedlist_get_item_aux(head->next,i,count);
    }
    return head->data;

}

/*
Obtem um item de uma lista ligada consoante a posicao
*/
void *linkedlist_get_item(Link head,int i){
    int count = 0;
    return linkedlist_get_item_aux(head,i,&count);
}

/*
Obtem um item de uma lista ligada consoante a informacao
*/
/*
compare deve devolver 0 caso os elementos sejam diferentes e 1 caso contrario
*/
void *linkedlist_get_item_cmp(Link head,void *info,void *(*get_info)(void *),int (*compare)(void *,void *)){
    int cmp_aux;

    if (head == NULL){
        return NULL;
    }
    cmp_aux = compare(info,get_info(head->data));

    if (cmp_aux)
        return head->data;
    else
        return linkedlist_get_item_cmp(head->next,info,get_info,compare);
}

/*
Faz reset de uma lista
*/
Link linkedlist_reset(Link head,void (*free_data)(void*)){
    linkedlist_free(head,free_data);
    return NULL;
}

/*
Altera a informacao da length de uma lista
*/
void linkedlist_set_length(Link head,int n){
    if (head == NULL) return;
    head->length = n;
}

/*
Obtem a informacao da length de uma lista
*/
int linkedlist_get_length(Link head){
    if (head == NULL) return 0;
    return head->length;
}
