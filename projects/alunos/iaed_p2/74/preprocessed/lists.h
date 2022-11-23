#ifndef list_h
#define list_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/*---------------------------------------Structs--------------------------------*/

/*Estrutura list que contem uma string e os pointers das estruturas seguinte e anterior*/
typedef struct nlist{
    struct nlist *next;
    struct nlist *ant;
    char *str;
   
}list;

/*--------------------------------------prototipos-------------------------------*/
/*funcao que aloca espaco na memoria para uma string e a insere*/
char *stringdup(char *org);

/*funcao cria lista*/
list *create(char *txt);
/*funcao que adiciona elementos a uma lista*/
list *list_insert(char *txt,list *lis);
/*funcao que devolve o tamanho da lista*/
int list_size(list *lis);
/*funcao que elimina elementos de uma lista*/
list *list_remove(char *txt, list *lis);
/*funcao que procura elementos numa lista*/
list *list_search(char *txt,list *lis);
/*funcao que da free na lista*/
void free_list(list *lis);

#endif /* list_h */
