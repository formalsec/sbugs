#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LISTAS.h"
#include "HASHTABLES.h"


link_jogo novo_jogo_lista(pJogo jogo)
{
  link_jogo x = (link_jogo) malloc(sizeof(struct no_jogo));
  x->jogo = jogo;
  x->next = 0;
  return x;
}

link_jogo insere_jogo_lista(link_jogo head, pJogo jogo)
{
  link_jogo x = head;
  head = novo_jogo_lista(jogo);
  head->next = x;
  return head;
}

link_jogo apaga_jogo_lista(link_jogo head, char *nome)
{
  link_jogo x = 0;
  link_jogo prev = 0;
  for (x = head; x != 0; prev = x, x = x->next)
  {
    if (x->jogo->nome[0] == nome[0])
    {
      if (x->jogo->nome[1] == nome[1])
      {
        if (!strcmp(x->jogo->nome, nome))
        {
          if (x == head)
          {
            head = x->next;
          }
          else
          {
            prev->next = x->next;
          }

          free(x);
          return head;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  return head;
}

void free_jogos_lista(link_jogo head)
{
  link_jogo x = 0;
  link_jogo x_next = 0;
  for (x = head; x != 0; x = x_next)
  {
    x_next = x->next;
    free(x);
  }

  return;
}

link_equipa nova_equipa_lista(char *equipa)
{
  link_equipa x = 0;
  x = (link_equipa) malloc(sizeof(struct no_equipa));
  x->equipa = (char *) malloc((sizeof(char)) * (strlen(equipa) + 1));
  strcpy(x->equipa, equipa);
  x->vitorias = 0;
  x->size_e = strlen(equipa);
  x->next = 0;
  return x;
}

void insere_equipa_lista(link_equipa *tab_equipas, char *equipa)
{
  link_equipa x = 0;
  link_equipa n = 0;
  unsigned int h;
  h = funcao_tab_equipas(equipa);
  n = nova_equipa_lista(equipa);
  if (tab_equipas[h] == 0)
  {
    tab_equipas[h] = n;
  }
  else
  {
    for (x = tab_equipas[h]; x->next != 0; x = x->next)
      ;

    x->next = n;
  }

  return;
}

link_equipa procura_equipa_lista(link_equipa *tab_equipas, char *equipa)
{
  link_equipa x = 0;
  unsigned int h;
  int comp;
  h = funcao_tab_equipas(equipa);
  comp = strlen(equipa);
  for (x = tab_equipas[h]; x != 0; x = x->next)
  {
    if (x->size_e == comp)
    {
      if (!strcmp(x->equipa, equipa))
      {
        return x;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  return 0;
}

