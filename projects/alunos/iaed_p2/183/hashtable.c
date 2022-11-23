#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

/* ========================= ESTRUTURAS  ============================= */
/* LISTA LIGADA (GENERICA): contem uma chave (string), um valor do tipo void (generico) e um 
   ponteiro para o node seguinte */
struct node {
    char *chave;
    void *valor;
    struct node *next;
};


/* LISTA DE CHAVES: array dinamico que mantem conta da ordem pela qual
   um item foi introduzido na hashtable, guardando a sua chave  */
typedef struct chaves {
    char **lista_chaves;
    int tamanho;           /* capacidade alocada */
    int ultima_chave;
} chaves;

/* HASHTABLE GENERICA: contem uma lista de nodes, o tamanho e uma lista de chaves. */
struct tabela {
    node **tabela;
    int tamanho;
    chaves chaves;
};


/* equivalente a strdup, duplica uma string */
char *dupstring(const char *src) {
    char *dest = (char *) can_fail_malloc((strlen(src) + 1) * sizeof(char));

    if (dest != NULL) {
        strcpy(dest, src);
        return dest;
    }
    
    return NULL;
}

/* ========================= FUNCOES DE NODES  ============================= */

node *cria_elemento(char *chave, void *valor, void *(* copiar)(void *valor)) {

    node *new_node = (node *) can_fail_malloc(sizeof(node));

    /* verificar que foi alocada memoria */
    if (new_node == NULL) return NULL;

    new_node->chave = dupstring(chave);
    new_node->valor = copiar(valor);

    if (new_node->chave != NULL && new_node->valor !=NULL) { 
        return new_node;
    }

    return NULL;
}

/* destroi um elemento duma tabela e a memoria associada a ele */
void destroi_elemento(node *elemento, void (* destroi)(void *valor)) {
    destroi(elemento->valor);
    free(elemento->chave);
    free(elemento);
}


/* ========================= FUNCOES DE CHAVES  ============================= */

bool cria_chaves(chaves *c, int tamanho) {
    c->lista_chaves = (char **) can_fail_malloc(tamanho * sizeof(char *));
    if (c->lista_chaves == NULL) return false;
    c->tamanho = tamanho;
    c->ultima_chave = -1;
    return true;
}

bool insere_chave(chaves *c, char *chave) {

    /* ve se esta cheio */
    if (c->ultima_chave == c->tamanho - 1) {
        /* duplicar capacidade da lista de chaves*/
        c->lista_chaves = (char **) can_fail_realloc(c->lista_chaves, c->tamanho * 2 * sizeof(char *));
        if (c->lista_chaves == NULL) return false;
        c->tamanho = c->tamanho * 2;
    }
    c->ultima_chave++;
    c->lista_chaves[c->ultima_chave] = chave;

    return true;
}

bool remove_chave(chaves *c, char *chave) {
    int i;
    char *temp;

    for (i = 0; i <= c->ultima_chave; i++) {
        temp = c->lista_chaves[i];
        if (temp != NULL && strcmp(temp, chave) == 0) {
            c->lista_chaves[i] = NULL; /* lazy remove */ 
            return true;
        }
    }

    return false;
}

/* ========================= FUNCOES DA HASHTABLE  ============================= */

/* Implementacao do algoritmo de Dan Bernstein, "djb2"*/
int hash(tabela *t, char *chave) {

    int hash = 5381;
    int c;

    while ((c = *chave++)) {
        hash = (((hash << 5) + hash) + c) % t->tamanho; /* (hash*33 + c) % tamanho */
    }

    return hash;
}

/* funcao que cria hash table com um dado size*/
tabela *cria_tabela(int tamanho) { 

    int i;

    tabela *t = (tabela *) can_fail_malloc(sizeof(tabela));

    t->tamanho = tamanho;
    t->tabela = (node**) can_fail_malloc(tamanho * sizeof(node*));
    if (t->tabela == NULL) return NULL;

    /* inicializa a tabela com ponteiros nulos (tb podia usar can_fail_calloc()) */
    for (i = 0; i < tamanho; i++)
        t->tabela[i] = NULL;

    if (!cria_chaves(&t->chaves, tamanho)) return NULL;

    return t;
}

/* funcao que insere/atualiza valor numa tabela 
   Nota: precisamos de uma funcao para alocar e copiar o valor 
   porque o valor contem ponteiros e nao basta copia o ponteiro mas sim o conteudo */
bool insere_tabela(tabela *t, char *chave, void *valor, void *(* copiar)(void *valor)) { 

    int pos = hash(t, chave);
    node *lista = t->tabela[pos];
    node *new_node; /* alocar so se for necessario! */
    node *temp;
    void *valor_anterior;

    for (temp = lista; temp != NULL; temp = temp->next) { 

        /* se encontrarmos a nossa chave, atualizar o valor */
        if (strcmp(temp->chave, chave) == 0) {
            valor_anterior = temp->valor;
            temp->valor = copiar(valor);
            if (valor_anterior != NULL) free(valor_anterior);
            return temp->valor != NULL ? true : false;
        }
    }

    /* alocar e inserir no fim */
    new_node = cria_elemento(chave, valor, copiar);

    if (new_node != NULL) {
        new_node->next = lista;
        t->tabela[pos] = new_node;
        
        return insere_chave(&t->chaves, new_node->chave);
    }

    return false;
}

/* funcao que retorna ponteiro para o valor ou NULL se nao existir */
void *procura_tabela(tabela *t, char *chave) {

    int pos = hash(t, chave);
    node *temp;

    for (temp = t->tabela[pos]; temp != NULL; temp = temp->next) {
        /* se encontrar, retornar pointeiro */
        if (strcmp(temp->chave, chave) == 0) {
            return temp->valor;
        }
    }
    return NULL;
}

/* funcao que remove valor numa tabela, pela chave */
bool remove_tabela(tabela *t, char *chave, void (* destroi)(void *valor)) { 

    int pos = hash(t, chave);
    node *temp = t->tabela[pos];
    node *prev = NULL;

    while (temp != NULL) { 
        
        /* encontrado o elemento */
        if (strcmp(temp->chave, chave) == 0) {

            /* se for a head da lista*/
            if (prev == NULL) {
                t->tabela[pos] = temp->next;
            } else {
                prev->next = temp->next;
            }
            remove_chave(&t->chaves, chave);
            destroi_elemento(temp, destroi);
            return true;
        }

        prev = temp;
        temp = temp->next;
    }
    return false;
}

/* implementar um "foreach" sobre a tabela de hash */
void iterar_tabela(tabela *t, bool (* funcao)(char *chave, void *valor, void *contexto), void *contexto) {

    int i;
    node *temp;

    for (i = 0; i < t->tamanho; i++) {
        
        for (temp = t->tabela[i]; temp != NULL; temp = temp->next) {
            /* para quando a funcao retorna false */
            if (!funcao(temp->chave, temp->valor, contexto)) return;
        }
    }

}

/* implementar um "foreach" sobre a tabela de hash - pela ordem de insercao */
void iterar_ordenado(tabela *t, bool (* funcao)(char *chave, void *valor, void *contexto), void *contexto) {

    int i;
    void *valor;
    char *chave;

    /* iterar por todas as chaves na ordem de insercao, filtrando NULLs */
    for (i = 0; i <= t->chaves.ultima_chave; i++) {

        chave = t->chaves.lista_chaves[i];

        if (chave != NULL) {
            /* procura a chave na hashtable */
            valor = procura_tabela(t, chave);

            if (valor != NULL) {                
                /* chama a funcao e parar a iteracao se retornar false */
               if (!funcao(chave, valor, contexto)) return; 
            }
        }
    }
}

/* funcao que apaga toda a memoria associada a tabela */
void destroi_tabela(tabela *t, void (* destroi)(void *valor)) {

    int i;
    node *temp, *next;

    for (i = 0; i < t->tamanho; i++) {
        temp = t->tabela[i];

        /* apagar todos os elementos da tabela */
        while (temp != NULL) {
            next = temp->next;
            destroi_elemento(temp, destroi);
            temp = next;
        }
    }

    /* apaga a estrutura em si e a lista de chaves */
    free(t->chaves.lista_chaves);
    free(t->tabela);
    free(t);
}
