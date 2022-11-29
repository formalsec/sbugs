#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hashtable.h"
#include "hashtableEquipa.h"
#include <stdlib.h>
#include <string.h>


int hash(char* str,int m){
    int key = 0;
    unsigned int i;
    for (i = 0; i < strlen(str); ++i) {
        key = key + str[i];
    }
    key = key % m;
    return key;
}

char* key(Item item) {
    return item->nome;
}

void init(int m) {
    int i;
    heads = NULL;
    heads = (Node**)can_fail_malloc(m*sizeof(Node*));
    for (i = 0; i < m; i++) heads[i] = NULL;
}

void insert(int tamHash, Item item) {
    int i = hash(key(item), tamHash);
    Node* newNode = NULL;
    newNode = (Node*) can_fail_malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = heads[i];
    heads[i] = newNode;
}

void delete(int tamHash, char *text, int tamHashEquipa) {
    Node* head = NULL;
    Node* prev = NULL;
    Node* aux = NULL;
    ItemEquipa ptr;
    int i = hash(text, tamHash);
    head = heads[i];
    while (strcmp(head->item->nome,text) != 0){
        prev = head;
        head = head->next;
    }
    if (prev == NULL) {
        if (head->item->pontos.score1 > head->item->pontos.score2) {
            ptr = searchEquipa(tamHashEquipa,head->item->equipa1);
            ptr->pontosVencedores = ptr->pontosVencedores - 1;
        }
        if (head->item->pontos.score2 > head->item->pontos.score1) {
            ptr = searchEquipa(tamHashEquipa, head->item->equipa2);
            ptr->pontosVencedores = ptr->pontosVencedores - 1;
        }
        aux = heads[i]->next;
        free(heads[i]->item->nome);
        free(heads[i]->item->equipa1);
        free(heads[i]->item->equipa2);
        free(heads[i]->item);
        free(heads[i]);
        heads[i] = aux;
    }

    else {
        aux = head->next;
        if (head->item->pontos.score1 > head->item->pontos.score2) {
            ptr = searchEquipa(tamHashEquipa,head->item->equipa1);
            ptr->pontosVencedores = ptr->pontosVencedores - 1;
        }
        if (head->item->pontos.score2 > head->item->pontos.score1) {
            ptr = searchEquipa(tamHashEquipa, head->item->equipa2);
            ptr->pontosVencedores = ptr->pontosVencedores - 1;
        }
        free(head->item->nome);
        free(head->item->equipa1);
        free(head->item->equipa2);
        free(head->item);
        free(head);
        prev->next = aux;
    }
}

Item search(int tamHash, char* text) {
    Node* head = NULL;
    Node* t = NULL;

    int i = hash(text, tamHash);
    head = heads[i];
    for(t = head; t != NULL; t = t->next){
        if (strcmp(t->item->nome,text) == 0)
            return t->item;
    }
    return NULL;
}

void deleteTudo(int i) {
    Node* head;
    Node* prev = NULL;
    Node* aux = NULL;
    head = heads[i];
    if(head != NULL){
        aux = head->next;
        while (aux != NULL){
            prev = aux;
            aux = aux->next;
            free(prev->item->equipa2);
            free(prev->item->equipa1);
            free(prev->item->nome);
            free(prev->item);

            free(prev);
        }
        free(heads[i]->item->nome);
        free(heads[i]->item->equipa1);
        free(heads[i]->item->equipa2);
        free(heads[i]->item);
        free(heads[i]);
    }

}

void deleteHeads() {
    free(heads);
}

Item* HashToArray(int tamHash, int contadorJogos) {
    Item *array = NULL;
    int i, j = 0;
    Node *head;
    if (contadorJogos == 0)
        return NULL;
    else {
        array = (Item *) can_fail_malloc(sizeof(Item) * contadorJogos);
        for (i = 0; i < contadorJogos; i++) array[i] = NULL;
        for (i = 0; i < tamHash; ++i) {
            head = heads[i];
            while (head != NULL) {
                array[j] = head->item;
                head = head->next;
                ++j;
            }
        }
        return array;
    }
}

void chk_hashtable(int* tamHash, int contadorJogos){
    int prev = *tamHash;
    Item* array;
    Node* head;
    Node* aux;
    int i;

    array = HashToArray(*tamHash, contadorJogos);

    for ( i = 0; i < prev; ++i) {
        head = heads[i];
        while (head != NULL) {
           aux = head->next;
           free(head);
           head = aux;
        }
    }
    free(heads);


    *tamHash = *tamHash + 500;
    init(*tamHash);

    for ( i = 0; i < contadorJogos; ++i) {
        insert(*tamHash,array[i]);
    }
    free(array);
}