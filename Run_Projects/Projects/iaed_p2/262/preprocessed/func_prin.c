/*File generated by PreProcessor.py*/


#include "estruturas.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void cmd_A(char *nome, equipa *HTequipa, int NL)
{
  if (SearchEquipa(nome, HTequipa) == 0)
  {
    InsertEquipa(nome, HTequipa);
  }
  else
  {
    printf("%d Equipa existente.\n", NL);
  }

}

int cmd_a(char *nome, char *eq1, char *eq2, int sc1, int sc2, jogo *HTjogo, equipa *HTequipa, int NL, int id)
{
  if (SearchJogo(nome, HTjogo) == 0)
  {
    {
      if ((SearchEquipa(eq1, HTequipa) != 0) && (SearchEquipa(eq2, HTequipa) != 0))
      {
        {
          InsertJogo(nome, eq1, eq2, sc1, sc2, HTjogo, id);
          if (sc1 > sc2)
          {
            {
              equipa aux = SearchEquipa(eq1, HTequipa);
              aux->vitorias += 1;
            }
          }
          else
          {
            if (sc2 > sc1)
            {
              {
                equipa aux = SearchEquipa(eq2, HTequipa);
                aux->vitorias += 1;
              }
            }
            else
            {
              
            }

          }

          return 1;
        }
      }
      else
      {
        printf("%d Equipa inexistente.\n", NL);
      }

    }
  }
  else
  {
    printf("%d Jogo existente.\n", NL);
  }

  return 0;
}

void cmd_p(char *nome, jogo *HTjogo, int NL)
{
  jogo aux = SearchJogo(nome, HTjogo);
  if (aux)
  {
    printf("%d %s %s %s %d %d\n", NL, aux->nome, aux->eq1, aux->eq2, aux->sc1, aux->sc2);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void cmd_P(char *nome, equipa *HTequipa, int NL)
{
  equipa aux = SearchEquipa(nome, HTequipa);
  if (aux)
  {
    printf("%d %s %d\n", NL, aux->nome, aux->vitorias);
  }
  else
  {
    printf("%d Equipa inexistente.\n", NL);
  }

}

void cmd_l(jogo *HTjogo, int NL, int id)
{
  int i;
  int j;
  jogo aux;
  for (i = 0; i < id; i++)
  {
    for (j = 0; j < 1097; j++)
    {
      for (aux = HTjogo[j]; aux != 0; aux = aux->nextJ)
      {
        if (aux->id == i)
        {
          {
            printf("%d %s %s %s %d %d\n", NL, aux->nome, aux->eq1, aux->eq2, aux->sc1, aux->sc2);
            break;
          }
        }
        else
        {
          
        }

      }

    }

  }

}

void cmd_r(char *nome, jogo *HTjogo, equipa *HTequipa, int NL)
{
  int i = Hash(nome, 1097);
  jogo aux = SearchJogo(nome, HTjogo);
  equipa temp;
  if (aux)
  {
    {
      if (aux->sc1 > aux->sc2)
      {
        {
          temp = SearchEquipa(aux->eq1, HTequipa);
          temp->vitorias -= 1;
        }
      }
      else
      {
        if (aux->sc2 > aux->sc1)
        {
          {
            temp = SearchEquipa(aux->eq2, HTequipa);
            temp->vitorias -= 1;
          }
        }
        else
        {
          
        }

      }

      HTjogo[i] = RemoveJogo(HTjogo[i], nome);
    }
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void cmd_s(char *nome, jogo *HTjogo, int sc1, int sc2, equipa *HTequipa, int NL)
{
  jogo aux = SearchJogo(nome, HTjogo);
  equipa eq1;
  equipa eq2;
  if (aux)
  {
    {
      eq1 = SearchEquipa(aux->eq1, HTequipa);
      eq2 = SearchEquipa(aux->eq2, HTequipa);
      if (sc1 > sc2)
      {
        {
          if (aux->sc1 == aux->sc2)
          {
            eq1->vitorias += 1;
          }
          else
          {
            if (aux->sc1 < aux->sc2)
            {
              {
                eq2->vitorias -= 1;
                eq1->vitorias += 1;
              }
            }
            else
            {
              
            }

          }

        }
      }
      else
      {
        if (sc2 > sc1)
        {
          {
            if (aux->sc1 == aux->sc2)
            {
              eq2->vitorias += 1;
            }
            else
            {
              if (aux->sc2 < aux->sc1)
              {
                {
                  eq1->vitorias -= 1;
                  eq2->vitorias += 1;
                }
              }
              else
              {
                
              }

            }

          }
        }
        else
        {
          if (sc1 == sc2)
          {
            {
              if (aux->sc1 > aux->sc2)
              {
                eq1->vitorias -= 1;
              }
              else
              {
                if (aux->sc2 > aux->sc1)
                {
                  eq2->vitorias -= 1;
                }
                else
                {
                  
                }

              }

            }
          }
          else
          {
            
          }

        }

      }

      aux->sc1 = sc1;
      aux->sc2 = sc2;
    }
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void cmd_g(equipa *HTequipa, int NL)
{
  int i;
  int maior = 0;
  equipa aux;
  equipa lista = 0;
  for (i = 0; i < 1097; i++)
  {
    for (aux = HTequipa[i]; aux != 0; aux = aux->nextE)
    {
      if (aux->vitorias >= maior)
      {
        maior = aux->vitorias;
      }
      else
      {
        
      }

    }

  }

  for (i = 0; i < 1097; i++)
  {
    for (aux = HTequipa[i]; aux != 0; aux = aux->nextE)
    {
      if (aux->vitorias == maior)
      {
        {
          lista = ListaEquipas(lista, aux->nome, aux->vitorias);
        }
      }
      else
      {
        
      }

    }

  }

  if (lista)
  {
    {
      printf("%d Melhores %d\n", NL, maior);
      for (aux = lista; aux != 0; aux = aux->nextE)
        printf("%d * %s\n", NL, aux->nome);

      FreeListE(lista);
    }
  }
  else
  {
    
  }

}

