/*File generated by PreProcessor.py*/


#include "Equipas.h"
#include "Jogos.h"
#include "func_hash.h"
#include "funcoes_cases.h"


int main()
{
  char c;
  int num_linhas;
  link_e *primeiras_e;
  link_e lista_equipas;
  link_j *primeiros_j;
  link_j lista_jogos;
  link_j *fim_jogos;
  num_linhas = 0;
  lista_jogos = 0;
  lista_equipas = 0;
  primeiros_j = 0;
  primeiras_e = 0;
  fim_jogos = (link_j *) malloc(sizeof(link_j));
  *fim_jogos = 0;
  primeiros_j = inicializa_j(primeiros_j);
  primeiras_e = inicializa_e(primeiras_e);
  while ((c = getchar()) != 'x')
  {
    switch (c)
    {
      case 'a':
      {
        num_linhas++;
        lista_jogos = letra_a(num_linhas, primeiros_j, primeiras_e, lista_jogos, fim_jogos);
        break;
      }

      case 'A':
      {
        num_linhas++;
        lista_equipas = letra_A(num_linhas, primeiras_e, lista_equipas);
        break;
      }

      case 'l':
      {
        num_linhas++;
        letra_l(num_linhas, lista_jogos);
        break;
      }

      case 'p':
      {
        num_linhas++;
        letra_p(num_linhas, primeiros_j);
        break;
      }

      case 'P':
      {
        num_linhas++;
        letra_P(num_linhas, primeiras_e);
        break;
      }

      case 'r':
      {
        num_linhas++;
        lista_jogos = letra_r(num_linhas, primeiros_j, primeiras_e, lista_jogos, fim_jogos);
        break;
      }

      case 's':
      {
        num_linhas++;
        letra_s(num_linhas, primeiros_j, primeiras_e);
        break;
      }

      case 'g':
      {
        num_linhas++;
        letra_g(num_linhas, lista_equipas);
        break;
      }
        getchar();

    }

  }

  frees_projeto(primeiros_j, primeiras_e, lista_jogos, lista_equipas);
  free(fim_jogos);
  return 0;
}

