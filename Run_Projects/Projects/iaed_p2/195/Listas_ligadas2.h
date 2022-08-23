#ifndef _Listas_ligadas2_
#define _Listas_ligadas2_

#include<stdlib.h> 
#include<stdio.h>
#include <string.h>

/*--------------------------- Estruturas das vitorias ------------------------------*/

/*---------------------- Estrutura que representa uma vitoria ---------------------*/
typedef struct vit
{
    int id;
    char *nome;
    int vit;
} vit;

/*--------- Estrutura que representa um nodo de uma lista de vitorias ------------*/

typedef struct node_v
{
    vit v;
    struct node_v *next;
} *link_v;

/*A funcao NEW_v cria um nodo da lista de vitorias.*/

link_v NEW_vit(char *nome,int val[])
{
    link_v x = (link_v) malloc(sizeof(struct node_v));
    x->v.nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(x->v.nome,nome);
    x->v.vit = 0;
    x->v.id = val[0];
    x->next = NULL;
    val[0]++;
    return x;
}

/*A funcao insertEnd_v insere o nodo criado por NEW_v na lista de vitorias.*/

link_v insertEnd_v(link_v head,char *nome,int val[])
{
    link_v x;
    if(head == NULL)
        return NEW_vit(nome,val);
    for(x = head; x->next != NULL; x = x->next)
    ;
    x->next = NEW_vit(nome,val);
    return head;
}

/*A funcao length_v percorre a lista de vitorias ate chegar ao final, devolvendo o
tamanho da lista.*/

int length_v(link_v head)
{
    int count=0;
    link_v x;
    for(x=head ; x!=NULL; x=x->next)
        count++;
    return count;
}

/*A funcao print_lista_v faz print da lista de vitorias*/

void print_lista_v(link_v head,int val[],int max)
{
    link_v t;
    for(t = head; t != NULL; t = t->next){
        if (t->v.vit == max)
            printf("%d * %s\n",val[1],t->v.nome);
    }
}


/*A funcao FREEnode_v liberta a memoria alocada para um nodo da lista de vitorias*/

void FREEnode_v(link_v t)
{
    free(t->v.nome);
    free(t);
}

/*A funcao delete_el_v remove um nodo da lista de vitorias*/

link_v delete_el_v(link_v head,char *nome)
{
    link_v t, prev;
    for(t = head, prev = NULL; t != NULL;
        prev = t, t = t->next) {
        if(strcmp(t->v.nome,nome) == 0) {
            if(t == head)
                head = t->next;
            else
                prev->next = t->next;
            FREEnode_v(t);
            break;
        }
    }
    return head;
}

/*A funcao lookup_v percorre a lista de vitorias ate encontrar o nodo correspondente, 
devolvendo o respetivo nodo.*/

link_v lookup_v(link_v head, char *nome)
{
    link_v t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->v.nome,nome) == 0)
            return t;
    return NULL;
}

#endif