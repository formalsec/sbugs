#include "hash.h"


/*funcoes de hash tables dos ponteiro para os jogos*/

int hashU_JOGOS(char *v, Hashtable_JOGOS HT) {
    int h = 0, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (HT->M-1))
        h = (a*h + *v) % HT->M;
    return h;
}


Hashtable_JOGOS HashtableInit_JOGOS(int M) {
    int i=0;
    /*aloca espaco para Hashtable_JOGOS*/
    Hashtable_JOGOS HT = malloc(sizeof(struct hashtable_jogos));
    HT->M = M;
    HT->adj = malloc(M * sizeof(linkPJogo));
    /*inicializacao de todas as heads a NULL*/
    for (i = 0; i < M; i++)
        HT->adj[i] = NULL;
    return HT;
}

void HashtableInsert_JOGOS(Hashtable_JOGOS HT, linkJogo j) {
    /*aloca espaco para novo nodo*/
    linkPJogo  a = (linkPJogo)malloc(sizeof(struct nodePJogo));
    /*obtem a chave para o nome do jogo*/
    int key = hashU_JOGOS(j->j.nome, HT);
    linkPJogo last = HT->adj[key];
    /*copia o ponteiro*/
    a->j = j;
    a->next = NULL;
    
    /*caso a lista esteja vazia*/
    if (HT->adj[key] == NULL) {
        HT->adj[key] = a;
       return;
    }

    /*caso a lista nao esteja vazia*/
    /*insere o nodo na ultima posicao da lista*/
    while (last->next != NULL)
        last = last->next;
    last->next = a;
    return;
}

int HashtableSearch_JOGOS (char *v, Hashtable_JOGOS HT) {
    linkPJogo j;
    /*obtem a chave para o nome do jogo*/
    int key = hashU_JOGOS(v, HT);
    for (j=HT->adj[key]; j!=NULL; j=j->next)
        if (!strcmp(j->j->j.nome, v))
            return 1;
    return 0;
}

void HashtableDelete_JOGOS (char *v, struct nodeJogo **head, Hashtable_JOGOS HT) {
    linkPJogo p;
    /*obtem a chave para o nome do jogo*/
    int key = hashU_JOGOS(v, HT);
    struct nodePJogo *temp = HT->adj[key], *prev;

    for (p=HT->adj[key]; p!=NULL; p=p->next) {
        if (!strcmp(p->j->j.nome, v)) {
            /*caso seja o primeiro nodo*/
            if (temp != NULL && !strcmp(temp->j->j.nome, v)) { 
                HT->adj[key] = temp->next;
                /*apaga o nodo da lista*/
                deleteNodeJogo(head, temp->j->j);
                free(temp);
                return; 
            }
            /*caso o nodo esteja no meio da lista*/
            while (temp != NULL && strcmp(temp->j->j.nome, v)) { 
                prev = temp;
                temp = temp->next;
            }
            /*caso o nodo esteja no fim da lista*/
            if (temp == NULL) return; 
            prev->next = temp->next;
            /*apaga o nodo da lista*/
            deleteNodeJogo(head, temp->j->j);
            free(temp);
        }
    }
}

void HashtableDeleteAll_JOGOS (Hashtable_JOGOS HT, linkJogo *head) {
    int i=0;
    linkPJogo temp, first;

    /*percorre toda a hash table e apaga todos os nodos*/
    for (i=0; i<HT->M; i++) {
        first = HT->adj[i];
        while(first != NULL) {
            temp = first;
            first=first->next;
            free(temp);
        }
    }
    HT->adj[i]=NULL;

    /*apaga toda lista*/
    deleteListJogo(head);
}

/*funcoes de hash tables dos ponteiro para as equipas*/

int hashU_EQUIPAS(char *v, Hashtable_EQUIPAS HT) {
    int h = 0, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (HT->M-1))
        h = (a*h + *v) % HT->M;
    return h;
}

Hashtable_EQUIPAS HashtableInit_EQUIPAS(int M) {
    int i=0;
    /*aloca espaco para Hashtable_EQUIPAS*/
    Hashtable_EQUIPAS HT = malloc(sizeof(struct hashtable_jogos));
    HT->M = M;
    HT->adj = malloc(M * sizeof(linkPEquipa));
    /*inicializacao de todas as heads a NULL*/
    for (i = 0; i < M; i++)
        HT->adj[i] = NULL;
    return HT;
}

void HashtableInsert_EQUIPAS(Hashtable_EQUIPAS HT, linkEquipa e) {
    /*aloca espaco para novo nodo*/
    linkPEquipa  a = (linkPEquipa)malloc(sizeof(struct nodePEquipa));
    /*obtem a chave para o nome da equipa*/
    int key = hashU_EQUIPAS(e->e.nome, HT);
    linkPEquipa last = HT->adj[key];
    /*copia o ponteiro*/
    a->e = e;
    a->next = NULL;
    
    /*caso a lista esteja vazia*/
    if (HT->adj[key] == NULL) {
        HT->adj[key] = a;
       return;
    }

    /*caso a lista nao esteja vazia*/
    /*insere o nodo na ultima posicao da lista*/
    while (last->next != NULL)
        last = last->next;
    last->next = a;
    return;
}

int HashtableSearch_EQUIPAS (char *v, Hashtable_EQUIPAS HT) {
    linkPEquipa p;
    /*obtem a chave para o nome da equipa*/
    int key = hashU_EQUIPAS(v, HT);
    for (p=HT->adj[key]; p!=NULL; p=p->next)
        if (!strcmp(p->e->e.nome, v)) 
            return 1;
    return 0;
}

void HashtableDelete_EQUIPAS (char *v, struct nodeEquipa **head, Hashtable_EQUIPAS HT) {
    linkPEquipa p;
    /*obtem a chave para o nome da equipa*/
    int key = hashU_EQUIPAS(v, HT);
    struct nodePEquipa *temp = HT->adj[key], *prev;

    for (p=HT->adj[key]; p!=NULL; p=p->next) {
        if (!strcmp(p->e->e.nome, v)) {
            /*caso seja o primeiro nodo*/
            if (temp != NULL && !strcmp(temp->e->e.nome, v)) { 
                HT->adj[key] = temp->next;
                /*apaga o nodo da lista*/
                deleteNodeEquipa(head, temp->e->e);
                free(temp);
                return; 
            }
            /*caso o nodo esteja no meio da lista*/
            while (temp != NULL && strcmp(temp->e->e.nome, v)) { 
                prev = temp;
                temp = temp->next;
            } 
            /*caso o nodo esteja no fim da lista*/
            if (temp == NULL) return; 
            prev->next = temp->next; 
            /*apaga o nodo da lista*/
            deleteNodeEquipa(head, temp->e->e);
            free(temp);
        }
    }
}

void HashtableDeleteAll_EQUIPAS (Hashtable_EQUIPAS HT, linkEquipa *head) {
    int i=0;
    linkPEquipa temp, first;

    /*percorre toda a hash table e apaga todos os nodos*/
    for (i=0; i<HT->M; i++) {
        first = HT->adj[i];
        while(first != NULL) {
            temp = first;
            first=first->next;
            free(temp);
        }
    }
    HT->adj[i]=NULL;

    /*apaga toda lista*/
    deleteListEquipa(head);
}