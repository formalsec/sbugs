/*File generated by PreProcessor.py*/


#include "projeto.h"


void lista_todos(int contador, pList l)
{
  pJogo t;
  for (t = l->head; t != 0; t = t->next)
  {
    printf("%d %s %s %s %d %d\n", contador, t->nome, t->equipa1, t->equipa2, t->score1, t->score2);
  }

}

void adiciona_jogo(int contador, pHash h, pHash_e h_e, pList l)
{
  char nome[1024];
  char equipa1[1024];
  char equipa2[1024];
  int score1;
  int score2;
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
  if (ht_search(h, nome) != 0)
  {
    {
      printf("%d Jogo existente.\n", contador);
    }
  }
  else
  {
    if ((ht_search_e(h_e, equipa1) == 0) || (ht_search_e(h_e, equipa2) == 0))
    {
      {
        printf("%d Equipa inexistente.\n", contador);
      }
    }
    else
    {
      {
        pEquipa e;
        pJogo novo;
        novo = cria_jogo(nome, equipa1, equipa2, score1, score2);
        if (novo->vencedora != 0)
        {
          {
            e = ht_search_e(h_e, novo->vencedora);
            e->wins += 1;
          }
        }
        else
        {
          
        }

        ht_insert(h, novo);
        list_insert(l, novo);
      }
    }

  }

}

void lista_jogo(int contador, pHash h)
{
  pJogo j;
  char nome[1024];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  j = ht_search(h, nome);
  if (j == 0)
  {
    {
      printf("%d Jogo inexistente.\n", contador);
    }
  }
  else
  {
    {
      printf("%d %s %s %s %d %d\n", contador, nome, j->equipa1, j->equipa2, j->score1, j->score2);
    }
  }

}

void apaga_jogo(int contador, pHash h, pHash_e h_e, pList l)
{
  pJogo j;
  pEquipa e;
  char nome[1024];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  j = ht_search(h, nome);
  if (j == 0)
  {
    {
      printf("%d Jogo inexistente.\n", contador);
    }
  }
  else
  {
    {
      if (j->vencedora != 0)
      {
        {
          e = ht_search_e(h_e, j->vencedora);
          e->wins -= 1;
        }
      }
      else
      {
        
      }

      list_delete(l, j);
      ht_delete(h, nome);
    }
  }

}

void altera_score(int contador, pHash h, pHash_e h_e)
{
  pJogo j;
  char nome[1024];
  int score1;
  int score2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  j = ht_search(h, nome);
  if (j == 0)
  {
    {
      printf("%d Jogo inexistente.\n", contador);
    }
  }
  else
  {
    {
      pEquipa e;
      pEquipa e1;
      pJogo j_atualizado;
      j_atualizado = cria_jogo(j->nome, j->equipa1, j->equipa2, score1, score2);
      if ((j->vencedora != 0) && (j_atualizado->vencedora != 0))
      {
        {
          if (strcmp(j->vencedora, j_atualizado->vencedora) != 0)
          {
            {
              e = ht_search_e(h_e, j_atualizado->vencedora);
              e->wins += 1;
              e1 = ht_search_e(h_e, j->vencedora);
              e1->wins -= 1;
              free(j->vencedora);
              j->vencedora = dup(j_atualizado->vencedora);
            }
          }
          else
          {
            
          }

        }
      }
      else
      {
        if ((j->vencedora == 0) && (j_atualizado->vencedora != 0))
        {
          {
            e = ht_search_e(h_e, j_atualizado->vencedora);
            e->wins += 1;
            j->vencedora = dup(j_atualizado->vencedora);
          }
        }
        else
        {
          if ((j->vencedora != 0) && (j_atualizado->vencedora == 0))
          {
            {
              e = ht_search_e(h_e, j->vencedora);
              e->wins -= 1;
              free(j->vencedora);
              j->vencedora = 0;
            }
          }
          else
          {
            
          }

        }

      }

      j->score1 = score1;
      j->score2 = score2;
      free_jogo(j_atualizado);
    }
  }

}

void adiciona_equipa(int contador, pHash_e h_e)
{
  char nome_e[1024];
  for (int nome_e_index = 0; nome_e_index < 10; nome_e_index++)
  {
    nome_e[nome_e_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_e[10 - 1] = '\0';
  if (ht_search_e(h_e, nome_e) != 0)
  {
    {
      printf("%d Equipa existente.\n", contador);
    }
  }
  else
  {
    {
      pEquipa e = cria_equipa(nome_e);
      ht_insert_e(h_e, e);
    }
  }

}

void lista_equipa(int contador, pHash_e h_e)
{
  pEquipa e;
  char nome_e[1024];
  for (int nome_e_index = 0; nome_e_index < 10; nome_e_index++)
  {
    nome_e[nome_e_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_e[10 - 1] = '\0';
  e = ht_search_e(h_e, nome_e);
  if (e == 0)
  {
    {
      printf("%d Equipa inexistente.\n", contador);
    }
  }
  else
  {
    {
      printf("%d %s %d\n", contador, nome_e, e->wins);
    }
  }

}

int cmpstr(const void *p1, const void *p2)
{
  char **v1;
  char **v2;
  v1 = (char **) p1;
  v2 = (char **) p2;
  return strcmp(*v1, *v2);
}

void lista_melhores(int contador, pHash_e h_e)
{
  int i;
  int j;
  int k;
  int max_wins = 0;
  int n_max_wins = 0;
  int c = 0;
  char **melhores;
  pLink_e temp;
  for (i = 0; i < h_e->M; i++)
  {
    temp = h_e->heads_e[i];
    while (temp)
    {
      if (temp->e->wins > max_wins)
      {
        {
          max_wins = temp->e->wins;
          n_max_wins = 1;
        }
      }
      else
      {
        if (temp->e->wins == max_wins)
        {
          {
            n_max_wins += 1;
          }
        }
        else
        {
          
        }

      }

      temp = temp->next;
    }

  }

  if (n_max_wins != 0)
  {
    {
      melhores = (char **) malloc((sizeof(char *)) * n_max_wins);
      for (k = 0; (k < h_e->M) && (c != n_max_wins); k++)
      {
        temp = h_e->heads_e[k];
        while (temp)
        {
          if (temp->e->wins == max_wins)
          {
            {
              melhores[c] = dup(temp->e->nome_e);
              c++;
            }
          }
          else
          {
            
          }

          temp = temp->next;
        }

      }

      qsort(melhores, n_max_wins, sizeof(char *), cmpstr);
      printf("%d Melhores %d\n", contador, max_wins);
      for (j = 0; j < n_max_wins; j++)
      {
        printf("%d * %s\n", contador, melhores[j]);
        free(melhores[j]);
      }

      free(melhores);
    }
  }
  else
  {
    
  }

}

int main()
{
  char comando;
  int contador = 0;
  pList l = list_init();
  pHash h = ht_init(1123);
  pHash_e h_e = ht_init_e(1123);
  while ((comando = getchar()) != EOF)
  {
    contador++;
    switch (comando)
    {
      case 'A':
        adiciona_equipa(contador, h_e);
        break;

      case 'P':
        lista_equipa(contador, h_e);
        break;

      case 'a':
        adiciona_jogo(contador, h, h_e, l);
        break;

      case 'p':
        lista_jogo(contador, h);
        break;

      case 'l':
        lista_todos(contador, l);
        break;

      case 'r':
        apaga_jogo(contador, h, h_e, l);
        break;

      case 's':
        altera_score(contador, h, h_e);
        break;

      case 'g':
        lista_melhores(contador, h_e);
        break;

      case 'x':
        ht_e_destroy(h_e);
        ht_destroy(h);
        free(l);
        return 0;

      default:
        printf("Comando invalido!");
        return 1;

    }

    getchar();
  }

  return 0;
}

