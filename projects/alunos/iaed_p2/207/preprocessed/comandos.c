#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"


PRINCIPAL init_stPrincipal(PRINCIPAL p)
{
  int i;
  p->hashJogo = malloc((sizeof(JOGO)) * 20);
  p->hashEquipa = malloc((sizeof(EQUIPA)) * 20);
  p->lista_equipas = malloc((sizeof(EQUIPA)) * 20);
  p->lista_jogos = 0;
  for (i = 0; i < 20; i++)
  {
    p->hashJogo[i] = 0;
    p->hashEquipa[i] = 0;
  }

  p->input_contador = 0;
  p->tamanho_jogos = 0;
  p->tamanho_equipas = 0;
  p->cap_jogos = 20;
  p->cap_equipas = 20;
  return p;
}

int adiciona_jogo(JOGO j, PRINCIPAL p)
{
  if (procura_jogo(j->nome, p) != (-1))
  {
    printf("%d Jogo existente.\n", p->input_contador);
    return 1;
  }
  else
  {
    
  }

  if ((procura_equipa(j->equipa1, p) == (-1)) || (procura_equipa(j->equipa2, p) == (-1)))
  {
    printf("%d Equipa inexistente.\n", p->input_contador);
    return 1;
  }
  else
  {
    if (j->score1 > j->score2)
    {
      adiciona_vitoria(j->equipa1, p);
    }
    else
    {
      
    }

    if (j->score2 > j->score1)
    {
      adiciona_vitoria(j->equipa2, p);
    }
    else
    {
      
    }

    insert_jogo(j, p);
    p->lista_jogos = insert_node(p->lista_jogos, j);
    return 0;
  }

}

int adiciona_equipa_cmd(char *nome, PRINCIPAL p)
{
  if (procura_equipa(nome, p) != (-1))
  {
    printf("%d Equipa existente.\n", p->input_contador);
    return 1;
  }
  else
  {
    insert_equipa(nome, p);
    return 0;
  }

}

void lista_jogos(PRINCIPAL p)
{
  NODE x;
  for (x = p->lista_jogos; x != 0; x = x->next)
  {
    printf("%d %s %s %s %d %d\n", p->input_contador, x->jogo->nome, x->jogo->equipa1, x->jogo->equipa2, x->jogo->score1, x->jogo->score2);
  }

}

int procura_jogo_cmd(char *nome, PRINCIPAL p)
{
  int i = procura_jogo(nome, p);
  if (i == (-1))
  {
    printf("%d Jogo inexistente.\n", p->input_contador);
    return 1;
  }
  else
  {
    printf("%d %s %s %s %d %d\n", p->input_contador, p->hashJogo[i]->nome, p->hashJogo[i]->equipa1, p->hashJogo[i]->equipa2, p->hashJogo[i]->score1, p->hashJogo[i]->score2);
    return 0;
  }

}

int procura_equipa_cmd(char *nome, PRINCIPAL p)
{
  int i = procura_equipa(nome, p);
  if (i == (-1))
  {
    printf("%d Equipa inexistente.\n", p->input_contador);
    return 1;
  }
  else
  {
    printf("%d %s %d\n", p->input_contador, p->hashEquipa[i]->nome, p->hashEquipa[i]->vitorias);
    return 0;
  }

}

void remove_jogo_cmd(char *nome, PRINCIPAL p)
{
  int i = procura_jogo(nome, p);
  if (i == (-1))
  {
    printf("%d Jogo inexistente.\n", p->input_contador);
  }
  else
  {
    if (p->hashJogo[i]->score1 > p->hashJogo[i]->score2)
    {
      remove_vitoria(p->hashJogo[i]->equipa1, p);
    }
    else
    {
      
    }

    if (p->hashJogo[i]->score2 > p->hashJogo[i]->score1)
    {
      remove_vitoria(p->hashJogo[i]->equipa2, p);
    }
    else
    {
      
    }

    delete_jogo(nome, p);
    p->lista_jogos = delete_node(p->lista_jogos, nome);
  }

}

void altera_score_cmd(char *nome, int score1, int score2, PRINCIPAL p)
{
  int i = procura_jogo(nome, p);
  int vitoria1 = 0;
  int vitoria2 = 0;
  int empate = 0;
  if (i == (-1))
  {
    printf("%d Jogo inexistente.\n", p->input_contador);
  }
  else
  {
    if (p->hashJogo[i]->score1 > p->hashJogo[i]->score2)
    {
      vitoria1 = 1;
    }
    else
    {
      if (p->hashJogo[i]->score2 > p->hashJogo[i]->score1)
      {
        vitoria2 = 1;
      }
      else
      {
        empate = 1;
      }

    }

    p->hashJogo[i]->score1 = score1;
    p->hashJogo[i]->score2 = score2;
    if ((score1 > score2) && (vitoria2 == 1))
    {
      remove_vitoria(p->hashJogo[i]->equipa2, p);
      adiciona_vitoria(p->hashJogo[i]->equipa1, p);
    }
    else
    {
      if ((score2 > score1) && (vitoria1 == 1))
      {
        remove_vitoria(p->hashJogo[i]->equipa1, p);
        adiciona_vitoria(p->hashJogo[i]->equipa2, p);
      }
      else
      {
        if ((score1 > score2) && (empate == 1))
        {
          adiciona_vitoria(p->hashJogo[i]->equipa1, p);
        }
        else
        {
          if ((score2 > score1) && (empate == 1))
          {
            adiciona_vitoria(p->hashJogo[i]->equipa2, p);
          }
          else
          {
            if ((score1 == score2) && (empate == 0))
            {
              if (vitoria1 == 1)
              {
                remove_vitoria(p->hashJogo[i]->equipa1, p);
              }
              else
              {
                remove_vitoria(p->hashJogo[i]->equipa2, p);
              }

            }
            else
            {
              
            }

          }

        }

      }

    }

  }

}

int compare(const void *a, const void *b)
{
  const struct equipa *equipa_a = *((struct equipa **) a);
  const struct equipa *equipa_b = *((struct equipa **) b);
  if (equipa_a->vitorias == equipa_b->vitorias)
  {
    if (strcmp(equipa_a->nome, equipa_b->nome) < 0)
    {
      return -1;
    }
    else
    {
      return 1;
    }

  }
  else
  {
    if (equipa_a->vitorias < equipa_b->vitorias)
    {
      return -1;
    }
    else
    {
      return 1;
    }

  }

}

void lista_melhor_equipas(PRINCIPAL p)
{
  int i = p->tamanho_equipas - 1;
  if (p->tamanho_equipas > 0)
  {
    qsort(p->lista_equipas, p->tamanho_equipas, sizeof(struct equipa *), compare);
    printf("%d Melhores %d\n", p->input_contador, p->lista_equipas[i]->vitorias);
    while ((i >= 0) && (p->lista_equipas[p->tamanho_equipas - 1]->vitorias == p->lista_equipas[i]->vitorias))
    {
      i--;
    }

    i++;
    while (i < p->tamanho_equipas)
    {
      printf("%d * %s\n", p->input_contador, p->lista_equipas[i]->nome);
      i++;
    }

  }
  else
  {
    
  }

}

