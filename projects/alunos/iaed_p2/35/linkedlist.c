#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "linkedlist.h"

/*funcoes que manipulam a lista de jogos*/

linkJogo insertNodeJogo(linkJogo *head, jogo j) {
    linkJogo  newNode  = (linkJogo)can_fail_malloc(sizeof(struct nodeJogo));
    linkJogo last = *head;

    /*copia dos dados do jogo para o nodo*/
    strcpy(newNode->j.nome, j.nome);
    strcpy(newNode->j.equipa1, j.equipa1);
    strcpy(newNode->j.equipa2, j.equipa2);
    newNode->j.score1 = j.score1;
    newNode->j.score2 = j.score2;
    newNode->next = NULL;

    /*insere o nodo no inicio*/
    if (*head == NULL) {
       *head = newNode ;
       return newNode;
    }

    /*insere o nodo no fim*/
    while (last->next != NULL)
        last = last->next;
    last->next = newNode ;
    return newNode;
}

void deleteNodeJogo(struct nodeJogo **head, jogo j) { 
    struct nodeJogo *temp = *head, *prev;
    
    /*apaga o nodo no inicio*/
    if (temp != NULL && !strcmp(temp->j.nome,j.nome)) { 
        *head = temp->next;
        free(temp);
        return; 
    } 
    
    /*apaga o nodo no meio*/
    while (temp != NULL && strcmp(temp->j.nome,j.nome)) { 
        prev = temp;
        temp = temp->next;
    } 
    /*apaga o nodo no fim*/
    if (temp == NULL) return; 
    prev->next = temp->next; 
    free(temp); 
}

void deleteListJogo(linkJogo *head) {
    linkJogo temp, first;
    first = *head;

    /*percore a lista e apaga todos os nodos*/
    while(first != NULL) {
        temp = first;
        first=first->next;
        free(temp);
    }
    *head=NULL;
}

/*funcoes que manipulam a lista de equipas*/

linkEquipa insertNodeEquipa(linkEquipa *head, equipa e) {
    linkEquipa  newNode  = (linkEquipa)can_fail_malloc(sizeof(struct nodeEquipa));
    linkEquipa last = *head;

    /*copia dos dados da equipa para o nodo*/
    strcpy(newNode->e.nome, e.nome);
    newNode->e.vitorias = e.vitorias;
    newNode->next = NULL;

    /*insere o nodo no inicio*/
    if (*head == NULL) {
       *head = newNode ;
       return newNode;
    }

    /*insere o nodo no fim*/
    while (last->next != NULL)
        last = last->next;
    last->next = newNode ;
    return newNode;
}

void deleteNodeEquipa(struct nodeEquipa **head, equipa e) { 
    struct nodeEquipa *temp = *head, *prev;

    /*apaga o nodo no inicio*/
    if (temp != NULL && !strcmp(temp->e.nome, e.nome)) { 
        *head = temp->next;
        free(temp);
        return; 
    } 

    /*apaga o nodo no meio*/
    while (temp != NULL && strcmp(temp->e.nome, e.nome)) { 
        prev = temp;
        temp = temp->next;
    } 
    
    /*apaga o nodo no fim*/
    if (temp == NULL) return; 
    prev->next = temp->next; 

    free(temp);
}

void deleteListEquipa(linkEquipa *head) {
    linkEquipa temp, first;
    first = *head;

    /*percore a lista e apaga todos os nodos*/
    while(first != NULL) {
        temp = first;
        first=first->next;
        free(temp);
    }
    *head=NULL;
}



