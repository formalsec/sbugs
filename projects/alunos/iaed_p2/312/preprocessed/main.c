#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estruturas.h"


void que_func(int NL, char *letra, lista_equipas *lista_ligada_equipas, acede_jogos *lista_ligada_jogos, acede_jogo_normal *jogos_normais, acede_equipa_normal *equipas_normais);
void free_da_hash_jogo(acede_jogos *lista_ligada_jogos);
void free_da_hash_equipa(lista_equipas *lista_ligada_equipas);
void free_jogos_normais(acede_jogo_normal *jogos_normais);
void free_equipas_normais(acede_equipa_normal *equipas_normais);
int main()
{
  int contador = 0;
  int *conta_linha = malloc(sizeof(int));
  char *letra = malloc(sizeof(char));
  acede_jogo_normal *jogos_normais = malloc(sizeof(acede_jogo_normal));
  acede_equipa_normal *equipas_normais = malloc(sizeof(acede_equipa_normal));
  acede_jogos *lista_ligada_jogos = malloc(sizeof(acede_jogos));
  lista_equipas *lista_ligada_equipas = malloc(sizeof(lista_equipas));
  inicia_normais(equipas_normais, jogos_normais);
  lista_ligada_jogos = inicializa_jogo(lista_ligada_jogos);
  lista_ligada_equipas = inicializa_equipa(lista_ligada_equipas);
  *conta_linha = 0;
  *letra = getchar();
  while ((*letra) != 'x')
  {
    contador += 1;
    if ((contador % 2) != 0)
    {
      *conta_linha += 1;
    }
    else
    {
      
    }

    que_func(*conta_linha, letra, lista_ligada_equipas, lista_ligada_jogos, jogos_normais, equipas_normais);
    *letra = getchar();
  }

  free(conta_linha);
  free(letra);
  free_da_hash_jogo(lista_ligada_jogos);
  free_da_hash_equipa(lista_ligada_equipas);
  free_equipas_normais(equipas_normais);
  free_jogos_normais(jogos_normais);
  return 0;
}

