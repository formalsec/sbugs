#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hashJG.h"

HLink_ inicializaHash_(int m){
    HLink_ head;
    int i;
    head = (HLink_)can_fail_malloc(sizeof(Link_)*m);
    for (i = 0; i < m; i++){
        head[i] = NULL;
    }  
    return head;
}

int hashJG(char* v, int m){
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (m-1)){  
        h = (a*h + *v) % m;
    }
    return h; 
}

void addHash_(HLink_ head, Jogo* jogo,int m){
    int index = hashJG(jogo->nome,m);
    head[index] = addJgLista(head[index],jogo);
}

Jogo* procuraJgHash(HLink_ head, int m, char* nome){
    return procuraJogo(head[hashJG(nome,m)],nome);
}

void remHash_(HLink_ head,char* nome,int m){
    int index = hashJG(nome,m);
    head[index] = apagaNode_(head[index],procuraJogo(head[index],nome));
    
}

void remHash_caso(HLink_ head,char* nome,int m){
    int index = hashJG(nome,m);
    head[index] = apagaNode_caso(head[index],procuraJogo(head[index],nome));
}

HLink_ limpaHash_(HLink_ head,int m){
    int i;
    for (i = 0; i < m; i++){
        limpaLista_(head[i]);
    }
    free(head);
    return NULL;
}


