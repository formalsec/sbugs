#include "hashEQ.h"

HLink inicializaHash(int m){
    HLink head;
    int i;
    head = (HLink)malloc(sizeof(Link)*m);
    for (i = 0; i < m; i++){
        head[i] = NULL;
    } 
    return head; 
}

int hashEQ(char* v, int m){
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (m-1)){  
        h = (a*h + *v) % m;
    }
    return h; 
}

void addHash(HLink head, Equipa* equipa,int m){
    int index = hashEQ(equipa->nome,m);
    head[index] = addEqLista(head[index],equipa);
}

Equipa* procuraEqHash(HLink head, int m, char* nome){
    return procuraEquipa(head[hashEQ(nome,m)],nome);
}

HLink limpaHash(HLink head,int m){
    int i;
    for (i = 0; i < m; i++){
        limpaLista(head[i]);
    }
    free(head);
    return NULL;
}