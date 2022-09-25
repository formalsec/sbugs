/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_equipa.h"


int M;
equipa **head_hash_e;
jogo **head_hash_j;
int string_cmp(const void *a, const void *b)
{
  const char **ia = (const char **) a;
  const char **ib = (const char **) b;
  return strcmp(*ia, *ib);
}

int maior_aux(lista_e *principal, lista_e *temp)
{
  int maior = 0;
  equipa *d;
  equipa *d1;
  for (d = principal->head; d; d = d->next)
  {
    if (d->vitorias > maior)
    {
      for (d1 = temp->head; d1; d1 = temp->head)
        rm_equipa(temp, d1);

      maior = d->vitorias;
    }
    else
    {
      
    }

    if (d->vitorias == maior)
    {
      add_last_equipa(temp, d->nome);
    }
    else
    {
      
    }

  }

  return maior;
}

int main()
{
  int y = 0;
  int o;
  int k = 0;
  jogo *n;
  char d;
  char t[1023];
  char s[1023];
  char r[1023];
  lista_e *ls = mk_lista_e();
  lista_j *lk = mk_lista_j();
  M = 50077;
  init_hash_equipa(M);
  init_hash_jogo(M);
  do
  {
    switch (d = getchar())
    {
      case 'a':
        getchar();
        y++;
        for (int t_index = 0; t_index < 10; t_index++)
      {
        t[t_index] = new_sym_var(sizeof(char) * 8);
      }

        t[10 - 1] = '\0';
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        for (int r_index = 0; r_index < 10; r_index++)
      {
        r[r_index] = new_sym_var(sizeof(char) * 8);
      }

        r[10 - 1] = '\0';
        k = new_sym_var(sizeof(int) * 8);
        o = new_sym_var(sizeof(int) * 8);
        if (lookup_j(t) == 0)
      {
        if ((lookup_e(s) != 0) && (lookup_e(r) != 0))
        {
          add_last_jogo(lk, t, lookup_e(s), lookup_e(r), k, o);
          hash_jogo_insert(lk->last);
          if (k > o)
          {
            lookup_e(s)->vitorias += 1;
            break;
          }
          else
          {
            
          }

          if (k < o)
          {
            lookup_e(r)->vitorias += 1;
            break;
          }
          else
          {
            
          }

        }
        else
        {
          printf("%d Equipa inexistente.\n", y);
        }

      }
      else
      {
        printf("%d Jogo existente.\n", y);
      }

        break;

      case 'A':
        getchar();
        y++;
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        if (lookup_e(s) != 0)
      {
        printf("%d Equipa existente.\n", y);
      }
      else
      {
        add_last_equipa(ls, s);
        hash_equipa_insert(ls->last);
      }

        break;

      case 'P':
        getchar();
        y++;
        for (int r_index = 0; r_index < 10; r_index++)
      {
        r[r_index] = new_sym_var(sizeof(char) * 8);
      }

        r[10 - 1] = '\0';
        if (lookup_e(r) == 0)
      {
        printf("%d Equipa inexistente.\n", y);
      }
      else
      {
        printf("%d %s %d\n", y, lookup_e(r)->nome, lookup_e(r)->vitorias);
      }

        break;

      case 'p':
        getchar();
        y++;
        for (int t_index = 0; t_index < 10; t_index++)
      {
        t[t_index] = new_sym_var(sizeof(char) * 8);
      }

        t[10 - 1] = '\0';
        if (lookup_j(t) == 0)
      {
        printf("%d Jogo inexistente.\n", y);
      }
      else
      {
        printf("%d %s %s %s %d %d\n", y, lookup_j(t)->nome, lookup_j(t)->e1->nome, lookup_j(t)->e2->nome, lookup_j(t)->resultado1, lookup_j(t)->resultado2);
      }

        break;

      case 'l':
        y++;
        for (n = lk->head; n; n = n->next)
      {
        if (lookup_j(n->nome) != 0)
        {
          printf("%d %s %s %s %d %d\n", y, n->nome, n->e1->nome, n->e2->nome, n->resultado1, n->resultado2);
        }
        else
        {
          
        }

      }

        break;

      case 's':
      {
        jogo *a;
        getchar();
        y++;
        for (int t_index = 0; t_index < 10; t_index++)
        {
          t[t_index] = new_sym_var(sizeof(char) * 8);
        }

        t[10 - 1] = '\0';
        k = new_sym_var(sizeof(int) * 8);
        o = new_sym_var(sizeof(int) * 8);
        a = lookup_j(t);
        if (a != 0)
        {
          if ((k > o) && (a->resultado1 < a->resultado2))
          {
            a->e1->vitorias += 1;
            a->e2->vitorias -= 1;
          }
          else
          {
            if ((k > o) && (a->resultado1 == a->resultado2))
            {
              a->e1->vitorias += 1;
            }
            else
            {
              if ((k == o) && (a->resultado1 > a->resultado2))
              {
                a->e1->vitorias -= 1;
              }
              else
              {
                if ((k == o) && (a->resultado1 < a->resultado2))
                {
                  a->e2->vitorias -= 1;
                }
                else
                {
                  if ((k < o) && (a->resultado1 > a->resultado2))
                  {
                    a->e1->vitorias -= 1;
                    a->e2->vitorias += 1;
                  }
                  else
                  {
                    if ((k < o) && (a->resultado1 == a->resultado2))
                    {
                      a->e2->vitorias += 1;
                    }
                    else
                    {
                      
                    }

                  }

                }

              }

            }

          }

          a->resultado1 = k;
          a->resultado2 = o;
        }
        else
        {
          printf("%d Jogo inexistente.\n", y);
        }

        break;
      }

      case 'r':
      {
        jogo *a;
        getchar();
        y++;
        for (int t_index = 0; t_index < 10; t_index++)
        {
          t[t_index] = new_sym_var(sizeof(char) * 8);
        }

        t[10 - 1] = '\0';
        a = lookup_j(t);
        if (a != 0)
        {
          if (a->resultado1 > a->resultado2)
          {
            a->e1->vitorias -= 1;
          }
          else
          {
            if (a->resultado1 < a->resultado2)
            {
              a->e2->vitorias -= 1;
            }
            else
            {
              
            }

          }

          hash_delete_j(t);
          rm_jogo(lk, a);
        }
        else
        {
          printf("%d Jogo inexistente.\n", y);
        }

        break;
      }

      case 'g':
      {
        int i;
        int count;
        int maior;
        char **temp;
        equipa *t;
        lista_e *ls_temp = mk_lista_e();
        maior = maior_aux(ls, ls_temp);
        y++;
        count = 0;
        for (t = ls_temp->head; t; t = t->next)
          count++;

        temp = malloc((sizeof(char *)) * (count + 1));
        for (i = 0, t = ls_temp->head; t; i++, t = t->next)
        {
          temp[i] = malloc((sizeof(char)) * (strlen(t->nome) + 1));
          strcpy(temp[i], t->nome);
        }

        qsort(temp, i, sizeof(char *), string_cmp);
        for (i = 0; i != count; i++)
        {
          if (i == 0)
          {
            printf("%d Melhores %d\n", y, maior);
          }
          else
          {
            
          }

          printf("%d * %s\n", y, temp[i]);
        }

        for (i = 0; i != count; i++)
        {
          free(temp[i]);
        }

        for (t = ls_temp->head; t; t = ls_temp->head)
          rm_equipa(ls_temp, t);

        free(ls_temp);
        free(temp);
        break;
      }

    }

  }
  while (d != 'x');
  free(head_hash_e);
  free(head_hash_j);
  free_list_equipa(ls);
  free_list_jogo(lk);
  return 0;
}

