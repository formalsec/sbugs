/*File generated by PreProcessor.py*/


#include "commands.h"


void cmd_a(link_jg *heads_jg, link_eq *heads_eq, list *jogos, int M, int m, int NL)
{
  char nome_jogo[1023];
  char nome1[1023];
  char nome2[1023];
  int score1 = 0;
  int score2 = 0;
  ptr_equipa equipa1 = 0;
  ptr_equipa equipa2 = 0;
  link_jogo novo_jogo = 0;
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  for (int nome1_index = 0; nome1_index < 10; nome1_index++)
  {
    nome1[nome1_index] = new_sym_var(sizeof(char) * 8);
  }

  nome1[10 - 1] = '\0';
  for (int nome2_index = 0; nome2_index < 10; nome2_index++)
  {
    nome2[nome2_index] = new_sym_var(sizeof(char) * 8);
  }

  nome2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  equipa1 = HT_eq_search(nome1, heads_eq, m);
  equipa2 = HT_eq_search(nome2, heads_eq, m);
  if (HT_jg_search(nome_jogo, heads_jg, M) != 0)
  {
    {
      printf("%d Jogo existente.\n", NL);
    }
  }
  else
  {
    if ((equipa1 == 0) || (equipa2 == 0))
    {
      {
        printf("%d Equipa inexistente.\n", NL);
      }
    }
    else
    {
      {
        novo_jogo = LS_jg_insert(newJogo(nome_jogo, equipa1, equipa2, score1, score2), jogos);
        HT_jg_insert(novo_jogo, heads_jg, M);
        if (score1 > score2)
        {
          {
            equipa1->jogos_ganhos++;
          }
        }
        else
        {
          
        }

        if (score2 > score1)
        {
          {
            equipa2->jogos_ganhos++;
          }
        }
        else
        {
          
        }

      }
    }

  }

}

void cmd_l(list *jogos, link_jg *heads_jg, int M, int NL)
{
  link_jogo t;
  link_jogo a;
  for (t = jogos->head; t != 0; t = t->next)
  {
    a = HT_jg_search(t->jogo->nome, heads_jg, M);
    printf("%d %s %s %s %d %d\n", NL, a->jogo->nome, a->jogo->equipa1->nome, a->jogo->equipa2->nome, a->jogo->score1, a->jogo->score2);
  }

}

void cmd_p(link_jg *heads_jg, int M, int NL)
{
  char nome_jogo[1023];
  link_jogo a = 0;
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  a = HT_jg_search(nome_jogo, heads_jg, M);
  if (a == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }
  else
  {
    {
      printf("%d %s %s %s %d %d\n", NL, a->jogo->nome, a->jogo->equipa1->nome, a->jogo->equipa2->nome, a->jogo->score1, a->jogo->score2);
    }
  }

}

void cmd_r(link_jg *heads_jg, list *jogos, int M, int NL)
{
  char nome_jogo[1023];
  link_jogo a = 0;
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  a = HT_jg_search(nome_jogo, heads_jg, M);
  if (a == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }
  else
  {
    {
      if (a->jogo->score1 > a->jogo->score2)
      {
        {
          a->jogo->equipa1->jogos_ganhos--;
        }
      }
      else
      {
        if (a->jogo->score1 < a->jogo->score2)
        {
          {
            a->jogo->equipa2->jogos_ganhos--;
          }
        }
        else
        {
          
        }

      }

      HT_jg_delete(a, heads_jg, M);
      LS_jg_delete(a, jogos);
    }
  }

}

void muda_score(ptr_equipa equipa1, ptr_equipa equipa2, ptr_jogo jogo, int novoscore1, int novoscore2)
{
  if ((jogo->score1 > jogo->score2) && (novoscore1 < novoscore2))
  {
    {
      equipa1->jogos_ganhos--;
      equipa2->jogos_ganhos++;
    }
  }
  else
  {
    if ((jogo->score2 > jogo->score1) && (novoscore1 > novoscore2))
    {
      {
        equipa1->jogos_ganhos++;
        equipa2->jogos_ganhos--;
      }
    }
    else
    {
      if ((jogo->score1 > jogo->score2) && (novoscore1 == novoscore2))
      {
        {
          equipa1->jogos_ganhos--;
        }
      }
      else
      {
        if ((jogo->score2 > jogo->score1) && (novoscore1 == novoscore2))
        {
          {
            equipa2->jogos_ganhos--;
          }
        }
        else
        {
          
        }

      }

    }

  }

}

void muda_score_igual(ptr_equipa equipa1, ptr_equipa equipa2, ptr_jogo jogo, int novoscore1, int novoscore2)
{
  if ((jogo->score2 == jogo->score1) && (novoscore1 < novoscore2))
  {
    {
      equipa2->jogos_ganhos++;
    }
  }
  else
  {
    if ((jogo->score2 == jogo->score1) && (novoscore1 > novoscore2))
    {
      {
        equipa1->jogos_ganhos++;
      }
    }
    else
    {
      
    }

  }

}

void cmd_s(link_jg *heads_jg, int M, int NL)
{
  char nome_jogo[1023];
  int novoscore1;
  int novoscore2;
  link_jogo a = 0;
  ptr_equipa equipa1 = 0;
  ptr_equipa equipa2 = 0;
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  novoscore1 = new_sym_var(sizeof(int) * 8);
  novoscore2 = new_sym_var(sizeof(int) * 8);
  a = HT_jg_search(nome_jogo, heads_jg, M);
  if (a == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }
  else
  {
    {
      equipa1 = a->jogo->equipa1;
      equipa2 = a->jogo->equipa2;
      muda_score(equipa1, equipa2, a->jogo, novoscore1, novoscore2);
      muda_score_igual(equipa1, equipa2, a->jogo, novoscore1, novoscore2);
      a->jogo->score1 = novoscore1;
      a->jogo->score2 = novoscore2;
    }
  }

}

void cmd_A(link_eq *heads_eq, int m, int *numeq, int NL)
{
  char nome[1023];
  ptr_equipa equipa = 0;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (HT_eq_search(nome, heads_eq, m) == 0)
  {
    {
      equipa = newEquipa(nome, 0);
      HT_eq_insert(equipa, heads_eq, m);
      *numeq = (*numeq) + 1;
    }
  }
  else
  {
    {
      printf("%d Equipa existente.\n", NL);
    }
  }

}

void cmd_P(link_eq *heads_eq, int M, int NL)
{
  char nome[1023];
  ptr_equipa equipa;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  equipa = HT_eq_search(nome, heads_eq, M);
  if (equipa == 0)
  {
    {
      printf("%d Equipa inexistente.\n", NL);
    }
  }
  else
  {
    {
      printf("%d %s %d\n", NL, equipa->nome, equipa->jogos_ganhos);
    }
  }

}

int comparador_por_vitorias(const void *a, const void *b)
{
  struct equipa *equipa1 = *((struct equipa **) a);
  struct equipa *equipa2 = *((struct equipa **) b);
  return strcmp(equipa1->nome, equipa2->nome);
}

void cmd_g(link_eq *heads_eq, int m, int *numeq, int NL)
{
  unsigned int j = 0;
  int i;
  int k = 0;
  link_eq temp = 0;
  ptr_equipa *array = 0;
  if ((*numeq) > 0)
  {
    {
      for (i = 0; i < m; i++)
      {
        temp = heads_eq[i];
        while (temp != 0)
        {
          if (temp->link_team->jogos_ganhos > j)
          {
            j = temp->link_team->jogos_ganhos;
          }
          else
          {
            
          }

          temp = temp->next;
        }

      }

      array = malloc((*numeq) * (sizeof(struct equipa)));
      for (i = 0; i < m; i++)
      {
        temp = heads_eq[i];
        while (temp != 0)
        {
          if (temp->link_team->jogos_ganhos == j)
          {
            {
              array[k] = temp->link_team;
              k++;
            }
          }
          else
          {
            
          }

          temp = temp->next;
        }

      }

      qsort(array, k, sizeof(struct equipa *), comparador_por_vitorias);
      printf("%d Melhores %d\n", NL, array[0]->jogos_ganhos);
      for (i = 0; i < k; i++)
      {
        printf("%d * %s\n", NL, array[i]->nome);
      }

      free(array);
    }
  }
  else
  {
    
  }

}

