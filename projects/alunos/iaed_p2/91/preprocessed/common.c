#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "common.h"


int hash(char *key, int capacidade)
{
  int h;
  int a = 31713;
  int b = 27985;
  for (h = 0; (*key) != '\0'; key++)
  {
    h = ((a * h) + (*key)) % capacidade;
    a = (a * b) % (capacidade - 1);
  }

  return h;
}

char *copiar_texto(char *input)
{
  int length = strlen(input);
  char *texto = malloc((length + 1) * (sizeof(char)));
  strcpy(texto, input);
  return texto;
}

