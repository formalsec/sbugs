/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Equipas.h"
#include "Jogos.h"
#include "ListaLigada.h"


void funcao_a(node **headsJ, pEquipa *heads, list *Lista, int nl, int m)
{
  char nome[1024];
  char equipa1[1024];
  char equipa2[1024];
  int score1;
  int score2;
  pEquipa Primeira;
  pEquipa Segunda;
  node *a;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  for (int equipa1_index = 0; equipa1_index < 10; equipa1_index++)
  {
    equipa1[equipa1_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa1[10 - 1] = '\0';
  for (int equipa2_index = 0; equipa2_index < 10; equipa2_index++)
  {
    equipa2[equipa2_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (STsearchJ(headsJ, nome, m) != 0)
  {
    {
      printf("%d Jogo existente.\n", nl);
    }
  }
  else
  {
    {
      if ((STsearch(heads, equipa1, m) == 0) || (STsearch(heads, equipa2, m) == 0))
      {
        {
          printf("%d Equipa inexistente.\n", nl);
        }
      }
      else
      {
        {
          if (score1 > score2)
          {
            {
              Primeira = STsearch(heads, equipa1, m);
              Primeira->vitorias++;
            }
          }
          else
          {
            if (score1 < score2)
            {
              {
                Segunda = STsearch(heads, equipa2, m);
                Segunda->vitorias++;
              }
            }
            else
            {
              
            }

          }

          a = add_last(Lista, nome, equipa1, equipa2, score1, score2);
          STinsertJ(headsJ, a, m);
        }
      }

    }
  }

}

void funcao_l(list *Lista, int nl)
{
  printList(Lista->head, nl);
}

void funcao_p(node **headsJ, int nl, int m)
{
  char nome[1024];
  node *Search;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  Search = STsearchJ(headsJ, nome, m);
  if (Search == 0)
  {
    {
      printf("%d Jogo inexistente.\n", nl);
    }
  }
  else
  {
    {
      printJogo(Search, nl);
    }
  }

}

void funcao_r(node **headsJ, pEquipa *heads, int nl, list *Lista, int m)
{
  char nome[1024];
  node *Search;
  node *node;
  pEquipa Primeira;
  pEquipa Segunda;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  Search = STsearchJ(headsJ, nome, m);
  if (Search == 0)
  {
    {
      printf("%d Jogo inexistente.\n", nl);
    }
  }
  else
  {
    {
      Primeira = STsearch(heads, Search->jogo->equipa1, m);
      Segunda = STsearch(heads, Search->jogo->equipa2, m);
      if (Search->jogo->score1 > Search->jogo->score2)
      {
        {
          Primeira->vitorias--;
        }
      }
      else
      {
        if (Search->jogo->score1 < Search->jogo->score2)
        {
          {
            Segunda->vitorias--;
          }
        }
        else
        {
          
        }

      }

      STdeleteJ(headsJ, nome, m);
      node = Lista->head;
      while (node != 0)
      {
        if (strcmp(node->jogo->nome, nome) == 0)
        {
          {
            rm_node(Lista, node);
            break;
          }
        }
        else
        {
          
        }

        node = node->next;
      }

    }
  }

}

void funcao_s(node **headsJ, pEquipa *heads, int nl, int m)
{
  char nome[1024];
  int score1;
  int score2;
  node *Search;
  pEquipa Primeira;
  pEquipa Segunda;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (STsearchJ(headsJ, nome, m) == 0)
  {
    {
      printf("%d Jogo inexistente.\n", nl);
    }
  }
  else
  {
    {
      Search = STsearchJ(headsJ, nome, m);
      Primeira = STsearch(heads, Search->jogo->equipa1, m);
      Segunda = STsearch(heads, Search->jogo->equipa2, m);
      if (Search->jogo->score1 > Search->jogo->score2)
      {
        {
          if (score1 > score2)
          {
            {
              Search->jogo->score1 = score1;
              Search->jogo->score2 = score2;
            }
          }
          else
          {
            if (score2 > score1)
            {
              {
                Primeira->vitorias--;
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
                Segunda->vitorias++;
              }
            }
            else
            {
              {
                Primeira->vitorias--;
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
              }
            }

          }

        }
      }
      else
      {
        if (Search->jogo->score1 < Search->jogo->score2)
        {
          {
            if (score1 < score2)
            {
              {
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
              }
            }
            else
            {
              if (score1 > score2)
              {
                {
                  Segunda->vitorias--;
                  Search->jogo->score1 = score1;
                  Search->jogo->score2 = score2;
                  Primeira->vitorias++;
                }
              }
              else
              {
                {
                  Segunda->vitorias--;
                  Search->jogo->score1 = score1;
                  Search->jogo->score2 = score2;
                }
              }

            }

          }
        }
        else
        {
          {
            if (score1 < score2)
            {
              {
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
                Segunda->vitorias++;
              }
            }
            else
            {
              if (score1 > score2)
              {
                {
                  Search->jogo->score1 = score1;
                  Search->jogo->score2 = score2;
                  Primeira->vitorias++;
                }
              }
              else
              {
                {
                  Search->jogo->score1 = score1;
                  Search->jogo->score2 = score2;
                }
              }

            }

          }
        }

      }

    }
  }

}

void funcao_A(pEquipa *heads, int nl, int m)
{
  char nome[1024];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (STsearch(heads, nome, m) != 0)
  {
    {
      printf("%d Equipa existente.\n", nl);
    }
  }
  else
  {
    {
      STinsert(heads, nome, m);
    }
  }

}

void funcao_P(pEquipa *heads, int nl, int m)
{
  char nome[1024];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (STsearch(heads, nome, m) == 0)
  {
    {
      printf("%d Equipa inexistente.\n", nl);
    }
  }
  else
  {
    {
      printEquipa(STsearch(heads, nome, m), nl);
    }
  }

}

int Compare(const void *a, const void *b)
{
  char *pa;
  char *pb;
  pa = *((char **) a);
  pb = *((char **) b);
  return strcmp(pa, pb);
}

void funcao_g(pEquipa *heads, int nl, int m)
{
  pEquipa aux;
  char **maiores = 0;
  int i;
  int maior = 0;
  int equipas = 0;
  int v = 0;
  for (i = 0; i < m; i++)
  {
    aux = heads[i];
    while (aux != 0)
    {
      if (aux->vitorias > maior)
      {
        {
          maior = aux->vitorias;
        }
      }
      else
      {
        
      }

      aux = aux->next;
    }

  }

  for (i = 0; i < m; i++)
  {
    aux = heads[i];
    while (aux != 0)
    {
      if (aux->vitorias == maior)
      {
        {
          equipas++;
        }
      }
      else
      {
        
      }

      aux = aux->next;
    }

  }

  if (equipas == 0)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  maiores = malloc((sizeof(char *)) * equipas);
  for (i = 0; i < m; i++)
  {
    aux = heads[i];
    while (aux != 0)
    {
      if (aux->vitorias == maior)
      {
        {
          maiores[v] = aux->nome;
          v++;
        }
      }
      else
      {
        
      }

      aux = aux->next;
    }

  }

  qsort(maiores, v, sizeof(char *), Compare);
  printf("%d Melhores %d\n", nl, maior);
  for (i = 0; i < v; i++)
  {
    printf("%d * %s\n", nl, maiores[i]);
  }

  free(maiores);
}

void funcao_x(pEquipa *heads, node **headsJ, list *Lista, int m)
{
  int i;
  pEquipa destruir;
  pEquipa tempE = 0;
  node *destruirJ;
  node *temp = 0;
  for (i = 0; i < m; i++)
  {
    for (destruir = heads[i]; destruir != 0;)
    {
      tempE = destruir->next;
      freeEquipa(destruir);
      destruir = tempE;
    }

    for (destruirJ = headsJ[i]; destruirJ != 0;)
    {
      temp = destruirJ->next;
      free(destruirJ);
      destruirJ = temp;
    }

  }

  free(heads);
  free(headsJ);
  free_list(Lista);
}

int main()
{
  pEquipa *heads;
  node **headsJ;
  list *Lista;
  char comando;
  int nl = 1;
  int m = 7349;
  Lista = mk_list();
  headsJ = STinitJ(m);
  heads = STinit(m);
  while (1)
  {
    comando = new_sym_var(sizeof(char) * 8);
    switch (comando)
    {
      case 'a':
        funcao_a(headsJ, heads, Lista, nl, m);
        nl++;
        break;

      case 'l':
        funcao_l(Lista, nl);
        nl++;
        break;

      case 'p':
        funcao_p(headsJ, nl, m);
        nl++;
        break;

      case 'r':
        funcao_r(headsJ, heads, nl, Lista, m);
        nl++;
        break;

      case 's':
        funcao_s(headsJ, heads, nl, m);
        nl++;
        break;

      case 'A':
        funcao_A(heads, nl, m);
        nl++;
        break;

      case 'P':
        funcao_P(heads, nl, m);
        nl++;
        break;

      case 'g':
        funcao_g(heads, nl, m);
        nl++;
        break;

      case 'x':
        funcao_x(heads, headsJ, Lista, m);
        return 0;

    }

  }

  return 0;
}
