#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "estruturasAlgoritmos.h"

/* Funcoes da lista */

/* Inicializa uma lista de tamanho m */
lista* novaLista(int m){
    lista* newQ;
    newQ = (lista*)malloc(sizeof(lista));
    newQ ->vetor = (item*)malloc(sizeof(item)*m);
    memset((void*)(newQ->vetor),0,sizeof(item)*m);
    newQ -> m = m;
    newQ -> n = 0;
    return newQ;
}

/* funcao que aumenta o tamanho da lista caso esta ja se encontre totalmente preenchida */
lista* dupTamanhoLista(lista *q){
    if(q == NULL) return NULL;
    q->m = 2 * q->m;
    q->vetor = realloc(q->vetor,sizeof(item)*q->m);
    return q;
}

/* Coloca um elemento no final da lista caso haja espaco caso contrario realoca a lista primeiro */
lista* insereFinalLista(lista *q,item item){
    if(q == NULL)
        q = novaLista(5);
    if(q->n < q->m){
        q->vetor[q->n++] = item;
        return q;
    } else {
        q = dupTamanhoLista(q);
        return insereFinalLista(q,item);
    }
}

/* funcao que para uma dada lista, L da free em L->vetor e em L */
void libLista(lista *q){
    free(q->vetor);
    free(q);
}

/* Funcao que liberta a memoria ocupada por uma lista */
void destroiLista(lista* q){
    int i;
    if(q == NULL) return;
    for(i = 0;i < q->n; i++){
        libItem(q->vetor[i]);
        free(q->vetor[i]);
    }
    libLista(q);
}

/* Funcao que remove um item de uma lista */
lista* removeItemLista(lista* q,item Item){
    int i;
    if(q == NULL) return NULL;
    for(i = 0;i < q->n; i++)
        if(!strcmp(q->vetor[i]->nome,Item->nome)){
            q->vetor[i]->scr[1] = ITEM_APAGADO;
        }
    return q;
}

/* funcao que procura um item numa lista e devolve um ponteiro para esse item caso o encontre
 caso contrario devolve um ponteiro para NULL */
item procuraLista(lista* q,char *chave){
    int i;
    if(q == NULL) return NULL;
    for(i = 0;i<q->n;i++){
        if(equal(q->vetor[i],chave))
            return q->vetor[i];
    }
    return NULL;
}

/* funcao que cria a tabela de dispersao */
tabela* novaTabela(int m){
    tabela *new = (tabela*)malloc(sizeof(tabela));
    new->m = m;
    new->n = 0;
    new->itens = (lista**)malloc(sizeof(lista*)*m);
    memset((void*)new->itens,0,sizeof(lista*)*m);
    return new;
}

/* funcao que insere um item na tabela de dispersao */
void insereTabela(tabela* st,item Item){
    int i = hash(chave(Item),st->m);
    st->itens[i] = insereFinalLista(st->itens[i],Item);
}

/* funcao que remove um item da tabela de dispersao */
void removeTabela(tabela* st,item Item){
    int i = hash(chave(Item),st->m);
    st->itens[i] = removeItemLista(st->itens[i],Item);
}

/* funcao que verifica se um item se encontra na tabela de dispersao */
item procuraTabela(tabela* st,Chave v){
    int i = hash(v,st->m);
    return procuraLista(st->itens[i],v);
}

/* funcao que liberta toda a memoria ocupada por uma tabela de dispersao */
void destroiTabela(tabela* st){
    int i;
    for(i = 0;i < st->m; i++){
        destroiLista(st->itens[i]);
    }
    free(st->itens);
    free(st);
}

/* Algoritmo de ordenacao para a estrutra de dados lista */
void insertionSort(lista *v,int l,int r){
    int i,j;
    item Item;
    for(i = l+1;i < r;i++){
        Item = v->vetor[i];
        j = i - 1;
        while(j >= l && menor(Item->nome,chaveLista(v,j))){
            atribui(v,j+1,j);
            j--;
        }
        v->vetor[j+1] = Item;
    }
}
