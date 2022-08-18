#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EQUIPA.h"


/*Funcao que utiliza a hashtable da lista das equipas para encontrar uma Equipa a partir do seu nome*/
Equipa* FindTeam(team_list* l, char buffer[DIM_STR]) 
{
    Equipa* toFind;

    int numHash = string_hash(buffer) % HASHSIZE;

    for (toFind = *(l->hashtable + numHash); toFind && strcmp(toFind->nome, buffer) != 0; toFind = toFind->collision);
    
    return toFind;
}

/* Funcao que inicializa comando 'P' e le o nome da Equipa.
  Vai usar o nome para chamar a funcao SearchTeam.*/
void comando_P(team_list* l, int NL)
{
  char buffer[DIM_STR];
  scanf("%[^:\n]:",buffer);
  SearchTeam(l,buffer,NL);

  return;
}

/* Funcao que vai usar um nome duma equipa para procura na lista de Equipas e dar print aos seus valores*/
void SearchTeam(team_list* l,char buffer[DIM_STR], int NL) 
{
    Equipa* toFind;
    if ((toFind = FindTeam(l, buffer))) 
        {
            printf("%d ", NL);
            printf("%s ",toFind->nome);
            printf("%d\n",toFind->vitorias);
            return;
        }

    printf("%d Equipa inexistente.\n", NL); 

}


/* Funcao respetiva do comando 'A', que cria uma nova Equipa e adiciona a lista de Equipas*/
team_list* teamAdd(team_list* l, char* buffer) 
{
    Equipa* nova_equipa;
    nova_equipa = malloc(sizeof(Equipa));

    nova_equipa->nome = malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(nova_equipa->nome, buffer);
    nova_equipa -> vitorias = 0;

    HashEquipa(l,nova_equipa);
    return l;
}




