#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_g.h"

/* Funcao que server para comparar as equipas, tendo em conta o numero de 
vitorias, como tambem a ordem lexicografica em caso de empate*/
int compara_vitorias(const void * p, const void * q)
{
  Equipa **a = (Equipa **)p;
  Equipa **b = (Equipa **)q;
  int compara;

  if (((*b)->vitorias - (*a)->vitorias) == 0){   /*comparar strings para o caso em que ambas tem o msm numero de vitorias*/
    compara = strcmp((*a)->nome,(*b)->nome);
    if(compara < 0) {
      /*nome do a < nome do b*/
      return -1;
    } 
    else if(compara > 0) {
      /*nome do b < nome do a*/
      return 1;
    } 

  }
  return (*b)->vitorias - (*a)->vitorias;
}


/* Funcao que ordena as equipas no comando 'g', mostrando aquelas que tem o maior numero de vitorias*/
void ordenaEquipas(team_list* l,int num_equipas, int NL) 
{
    Equipa* temp = l->head;
    Equipa **Copy;
    int i;
    int maior;

    Copy = malloc(sizeof(Equipa*) * num_equipas);
    
    if (temp == NULL)  
    {
        free(Copy);
        return;
    }
    
    /*Guarda valores para Copy*/
    for (i = 0; (i < num_equipas) && temp!= NULL ; i++)  {
        *(Copy+i) = temp ;
        temp = temp->next;
    }

    /*Algoritmo de ordenacao QuickSort, que vai servir para ordernar a lista de
     equipas, tendo como criterito de comparacao a funcao compara_vitorias */
    qsort(Copy, num_equipas, sizeof(Equipa*), compara_vitorias);

    
    
    maior = (**(Copy)).vitorias; /*a primeira equipa em copy apos a ordenacao tera sempre a melhor pontuacao*/
    printf("%d Melhores %d\n", NL, maior);

    for (i = 0; i < num_equipas; i++)  {
        if((**(Copy+i)).vitorias != maior){
          break;
        }
        printf("%d * %s\n", NL, (**(Copy+i)).nome);
    }

    free(Copy);

    return; 
 }
