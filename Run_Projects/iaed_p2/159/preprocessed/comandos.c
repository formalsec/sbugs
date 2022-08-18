/*File generated by PreProcessor.py*/


#include "comandos.h"
#include "tabelas_disp.h"
#include "estruturas.h"


void comando_a(ST_jg Tj, ST_eq Te, Jogo *Jogos, int num_linhas)
{
  char nome[1024];
  char n_equipa1[1024];
  char n_equipa2[1024];
  unsigned int score1;
  unsigned int score2;
  Equipa e1;
  Equipa e2;
  Jogo novo_jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  for (int n_equipa1_index = 0; n_equipa1_index < 10; n_equipa1_index++)
  {
    n_equipa1[n_equipa1_index] = new_sym_var(sizeof(char) * 8);
  }

  n_equipa1[10 - 1] = '\0';
  for (int n_equipa2_index = 0; n_equipa2_index < 10; n_equipa2_index++)
  {
    n_equipa2[n_equipa2_index] = new_sym_var(sizeof(char) * 8);
  }

  n_equipa2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(unsigned int) * 8);
  score2 = new_sym_var(sizeof(unsigned int) * 8);
  if (ST_jg_search(Tj, nome) != 0)
  {
    {
      printf("%u Jogo existente.\n", num_linhas);
    }
  }
  else
  {
    if ((ST_eq_search(Te, n_equipa1) == 0) || (ST_eq_search(Te, n_equipa2) == 0))
    {
      {
        printf("%u Equipa inexistente.\n", num_linhas);
      }
    }
    else
    {
      {
        e1 = ST_eq_search(Te, n_equipa1);
        e2 = ST_eq_search(Te, n_equipa2);
        adiciona_scores(e1, e2, score1, score2);
        novo_jogo = new_Jogo(nome, e1, e2, score1, score2);
        Jogos[Tj->N] = novo_jogo;
        ST_jg_insert(Tj, novo_jogo);
      }
    }

  }

}

void comando_A(ST_eq Te, int num_linhas)
{
  char nome[1024];
  Equipa nova_equipa;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (ST_eq_search(Te, nome) != 0)
  {
    {
      printf("%u Equipa existente.\n", num_linhas);
    }
  }
  else
  {
    {
      nova_equipa = new_Equipa(nome);
      ST_eq_insert(Te, nova_equipa);
    }
  }

}

void comando_l(ST_jg Tj, Jogo *Jogos, int num_linhas)
{
  long j;
  Jogo jogo;
  if (Tj->N > 0)
  {
    {
      for (j = 0; j < Tj->N; j++)
      {
        jogo = Jogos[j];
        print_Jogo(jogo, num_linhas);
      }

    }
  }
  else
  {
    return;
  }

}

void comando_p(ST_jg Tj, int num_linhas)
{
  char nome[1024];
  Jogo jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  jogo = ST_jg_search(Tj, nome);
  if (jogo != 0)
  {
    {
      print_Jogo(jogo, num_linhas);
    }
  }
  else
  {
    {
      printf("%u Jogo inexistente.\n", num_linhas);
    }
  }

}

void comando_P(ST_eq Te, int num_linhas)
{
  char nome[1024];
  Equipa equipa;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  equipa = ST_eq_search(Te, nome);
  if (equipa != 0)
  {
    {
      print_Equipa(equipa, num_linhas);
    }
  }
  else
  {
    {
      printf("%u Equipa inexistente.\n", num_linhas);
    }
  }

}

void comando_s(ST_jg Tj, ST_eq Te, int num_linhas)
{
  char nome[1024];
  unsigned int s1;
  unsigned int s2;
  Jogo jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(unsigned int) * 8);
  s2 = new_sym_var(sizeof(unsigned int) * 8);
  jogo = ST_jg_search(Tj, nome);
  if (jogo != 0)
  {
    {
      altera_scores(Te, jogo, s1, s2);
    }
  }
  else
  {
    {
      printf("%u Jogo inexistente.\n", num_linhas);
    }
  }

}

void comando_r(ST_jg Tj, ST_eq Te, Jogo *Jogos, int num_linhas)
{
  char nome[1024];
  Jogo jogo;
  long i;
  long j;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  jogo = ST_jg_search(Tj, nome);
  if (jogo != 0)
  {
    {
      for (i = 0; i < Tj->N; i++)
      {
        if (jogo == Jogos[i])
        {
          break;
        }
        else
        {
          
        }

      }

      for (j = i; j < (Tj->N - 1); j++)
      {
        Jogos[j] = Jogos[j + 1];
      }

      elimina_scores(Te, jogo);
      ST_jg_delete(Tj, nome);
    }
  }
  else
  {
    {
      printf("%u Jogo inexistente.\n", num_linhas);
    }
  }

}

void comando_g(ST_eq Te, int num_linhas)
{
  unsigned int J_Ganhos_max = 0;
  long i;
  long j = 0;
  long *indice_equipas;
  char **nomes_equipas;
  if (Te->N == 0)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  indice_equipas = malloc((sizeof(long)) * Te->N);
  for (i = 0; i < Te->M; i++)
  {
    if (Te->st[i] != 0)
    {
      {
        if (Te->st[i]->jogos_ganhos > J_Ganhos_max)
        {
          {
            J_Ganhos_max = Te->st[i]->jogos_ganhos;
            j = 0;
            indice_equipas[j] = i;
            j++;
          }
        }
        else
        {
          if (Te->st[i]->jogos_ganhos == J_Ganhos_max)
          {
            {
              indice_equipas[j] = i;
              j++;
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
      
    }

  }

  nomes_equipas = malloc((sizeof(char *)) * j);
  for (i = 0; i < j; i++)
  {
    nomes_equipas[i] = strdup(Te->st[indice_equipas[i]]->nome);
  }

  qsort(nomes_equipas, j, sizeof(char *), comparador);
  printf("%u Melhores %d\n", num_linhas, J_Ganhos_max);
  for (i = 0; i < j; i++)
  {
    printf("%u * %s\n", num_linhas, nomes_equipas[i]);
  }

  for (i = 0; i < j; i++)
  {
    free(nomes_equipas[i]);
  }

  free(nomes_equipas);
  free(indice_equipas);
}

void adiciona_scores(Equipa e1, Equipa e2, unsigned int s1, unsigned int s2)
{
  if (s1 < s2)
  {
    {
      e2->jogos_ganhos++;
    }
  }
  else
  {
    if (s2 < s1)
    {
      {
        e1->jogos_ganhos++;
      }
    }
    else
    {
      
    }

  }

}

void altera_scores(ST_eq Te, Jogo jogo, unsigned int s1, unsigned int s2)
{
  Equipa e1;
  Equipa e2;
  e1 = ST_eq_search(Te, jogo->e1->nome);
  e2 = ST_eq_search(Te, jogo->e2->nome);
  if ((jogo->s1 != s1) || (jogo->s2 != s2))
  {
    {
      if (jogo->s1 != jogo->s2)
      {
        {
          if (jogo->s1 < jogo->s2)
          {
            {
              e2->jogos_ganhos--;
            }
          }
          else
          {
            {
              e1->jogos_ganhos--;
            }
          }

        }
      }
      else
      {
        
      }

      if (s1 != s2)
      {
        {
          if (s1 < s2)
          {
            {
              e2->jogos_ganhos++;
            }
          }
          else
          {
            {
              e1->jogos_ganhos++;
            }
          }

        }
      }
      else
      {
        
      }

      jogo->s1 = s1;
      jogo->s2 = s2;
    }
  }
  else
  {
    
  }

}

void elimina_scores(ST_eq Te, Jogo jogo)
{
  Equipa e1;
  Equipa e2;
  e1 = ST_eq_search(Te, jogo->e1->nome);
  e2 = ST_eq_search(Te, jogo->e2->nome);
  if (jogo->s1 != jogo->s2)
  {
    {
      if (jogo->s1 < jogo->s2)
      {
        {
          e2->jogos_ganhos--;
        }
      }
      else
      {
        {
          e1->jogos_ganhos--;
        }
      }

    }
  }
  else
  {
    
  }

}

int comparador(const void *a, const void *b)
{
  return strcmp(*((char * const *) a), *((char * const *) b));
}

