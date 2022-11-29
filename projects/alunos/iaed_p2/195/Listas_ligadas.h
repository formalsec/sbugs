#ifndef _Listas_ligadas_
#define _Listas_ligadas_

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

/*--------------------------- Estruturas dos jogos ----------------------------*/

/*---------------------- Estrutura que representa um jogo ---------------------*/
typedef struct jogo
{
    int id;
    char *equipas[2];
    int pont[2];
    char *nome;
}jogo;

/*--------- Estrutura que representa um nodo de uma lista de jogos ------------*/

typedef struct node
{
    jogo game;
    struct node *next;
} *link;

/*A funcao NEW_jog cria um nodo da lista de jogos.*/

link NEW_jog(char *nome,char *equipa1,char *equipa2,int pont1,int pont2,int val[])
{
    link x = (link) malloc(sizeof(struct node));
    x->game.nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    x->game.equipas[0] = (char*) malloc(sizeof(char)*(strlen(equipa1)+1));
    x->game.equipas[1] = (char*) malloc(sizeof(char)*(strlen(equipa2)+1));
    strcpy(x->game.nome,nome);
    strcpy(x->game.equipas[0],equipa1);
    strcpy(x->game.equipas[1],equipa2);
    x->game.pont[0] = pont1;
    x->game.pont[1] = pont2;
    x->game.id = val[2];
    x->next = NULL;
    val[2]++;
    return x;
}

/*A funcao insertEnd_jog insere o nodo criado por NEW_jog na lista de jogos.*/

link insertEnd_jog(link head,char *nome,char *equipa1,char *equipa2,int pont1,int pont2,int val[])
{
    link x;
    if(head == NULL)
        return NEW_jog(nome,equipa1,equipa2,pont1,pont2,val);
    for(x = head; x->next != NULL; x = x->next)
    ;
    x->next = NEW_jog(nome,equipa1,equipa2,pont1,pont2,val);
    return head;
}

/*A funcao length_jog percorre a lista de jogos ate chegar ao final, devolvendo o
tamanho da lista.*/

int length_jog(link head)
{
    int count=0;
    link x;
    for(x=head ; x!=NULL; x=x->next)
        count++;
    return count;
}

/*A funcao print_lista_jog faz print da lista de jogos*/

void print_lista_jog(link head,int val[])
{
    link t;
    for(t = head; t != NULL; t = t->next){
        printf("%d %s %s %s %d %d\n",val[1],t->game.nome,t->game.equipas[0],t->game.equipas[1],
        t->game.pont[0],t->game.pont[1]);
    }
}

/*A funcao baixa_id_jog baixa o id de todos os jogos removidos apos a remocao de um certo jogo*/

void baixa_id_jog(link head)
{
    link t;int i;
    i = 0;
    for(t = head; t != NULL; t = t->next){
        t->game.id = i++;
    }
}

/*A funcao FREEnode_jog liberta a memoria alocada para um nodo da lista de jogos*/

void FREEnode_jog(link t)
{
    free(t->game.nome);
    free(t->game.equipas[0]);
    free(t->game.equipas[1]);
    free(t);
}

/*A funcao delete_el_jog remove um nodo da lista de jogos*/

link delete_el_jog(link head,char *nome)
{
    link t, prev;
    for(t = head, prev = NULL; t != NULL;
        prev = t, t = t->next) {
        if(strcmp(t->game.nome,nome) == 0) {
            if(t == head)
                head = t->next;
            else
                prev->next = t->next;
            FREEnode_jog(t);
            break;
        }
    }
    return head;
}

/*A funcao lookup_jog percorre a lista de jogos ate encontrar o nodo correspondente, 
devolvendo o respetivo nodo.*/

link lookup_jog(link head, char *nome)
{
    link t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->game.nome,nome) == 0)
            return t;
    return NULL;
}

#endif