/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include "jogo.h"
#include "common.h"


Jogo *criar_jogo()
{
  Jogo *jogo = malloc(sizeof(Jogo));
  char input[1024];
  char input1[1024];
  char input2[1024];
  for (int input_index = 0; input_index < 10; input_index++)
  {
    input[input_index] = new_sym_var(sizeof(char) * 8);
  }

  input[10 - 1] = '\0';
  for (int input1_index = 0; input1_index < 10; input1_index++)
  {
    input1[input1_index] = new_sym_var(sizeof(char) * 8);
  }

  input1[10 - 1] = '\0';
  for (int input2_index = 0; input2_index < 10; input2_index++)
  {
    input2[input2_index] = new_sym_var(sizeof(char) * 8);
  }

  input2[10 - 1] = '\0';
  jogo->scores[0] = new_sym_var(sizeof(int) * 8);
  jogo->scores[1] = new_sym_var(sizeof(int) * 8);
  jogo->nome = copiar_texto(input);
  jogo->equipas[0] = copiar_texto(input1);
  jogo->equipas[1] = copiar_texto(input2);
  return jogo;
}

void free_jogo(Jogo *jogo)
{
  free(jogo->nome);
  free(jogo->equipas[0]);
  free(jogo->equipas[1]);
  free(jogo);
}

