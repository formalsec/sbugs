/*File generated by PreProcessor.py*/


#include "estruturas.h"
#include "tabelas_disp.h"


long hash(char *v, long M)
{
  long h;
  long a = 31415;
  long b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (M - 1))
  {
    h = ((a * h) + (*v)) % M;
  }

  return h;
}

ST_jg ST_jg_init(long max)
{
  long i;
  ST_jg new = (ST_jg) malloc(sizeof(struct hash_table_jg));
  new->N = 0;
  new->M = 2 * max;
  new->st = (Jogo *) malloc(new->M * (sizeof(Jogo)));
  for (i = 0; i < new->M; i++)
  {
    new->st[i] = 0;
  }

  return new;
}

void ST_jg_insert(ST_jg T, Jogo jogo)
{
  Key value = jogo->nome;
  long i = hash(value, T->M);
  while (T->st[i] != 0)
  {
    i = (i + 1) % T->M;
  }

  T->st[i] = jogo;
  T->N++;
}

void ST_jg_delete(ST_jg T, Key value)
{
  long j;
  long i = hash(value, T->M);
  Jogo aux;
  while (T->st[i] != 0)
  {
    if (!strcmp(value, T->st[i]->nome))
    {
      {
        break;
      }
    }
    else
    {
      {
        i = (i + 1) % T->M;
      }
    }

  }

  if (T->st[i] == 0)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  free_Jogo(T->st[i]);
  T->st[i] = 0;
  T->N--;
  for (j = (i + 1) % T->M; T->st[j] != 0; j = (j + 1) % T->M, T->N--)
  {
    aux = T->st[j];
    T->st[j] = 0;
    ST_jg_insert(T, aux);
  }

}

Jogo ST_jg_search(ST_jg T, Key value)
{
  long i = hash(value, T->M);
  while (T->st[i] != 0)
  {
    if (!strcmp(value, T->st[i]->nome))
    {
      {
        return T->st[i];
      }
    }
    else
    {
      {
        i = (i + 1) % T->M;
      }
    }

  }

  return 0;
}

ST_eq ST_eq_init(long max)
{
  long i;
  ST_eq new = (ST_eq) malloc(sizeof(struct hash_table_eq));
  new->N = 0;
  new->M = 2 * max;
  new->st = (Equipa *) malloc(new->M * (sizeof(Equipa)));
  for (i = 0; i < new->M; i++)
  {
    new->st[i] = 0;
  }

  return new;
}

void ST_eq_insert(ST_eq T, Equipa equipa)
{
  Key value = equipa->nome;
  long i = hash(value, T->M);
  while (T->st[i] != 0)
  {
    i = (i + 1) % T->M;
  }

  T->st[i] = equipa;
  T->N++;
}

Equipa ST_eq_search(ST_eq T, Key value)
{
  long i = hash(value, T->M);
  while (T->st[i] != 0)
  {
    if (!strcmp(value, T->st[i]->nome))
    {
      {
        return T->st[i];
      }
    }
    else
    {
      {
        i = (i + 1) % T->M;
      }
    }

  }

  return 0;
}

ST_jg expand_j(ST_jg Tj)
{
  ST_jg new;
  long i;
  new = ST_jg_init(Tj->M + Tj->M);
  for (i = 0; i < Tj->M; i++)
  {
    if (Tj->st[i] != 0)
    {
      {
        ST_jg_insert(new, Tj->st[i]);
      }
    }
    else
    {
      
    }

  }

  free(Tj->st);
  free(Tj);
  return new;
}

ST_eq expand_e(ST_eq Te)
{
  ST_eq new;
  long i;
  new = ST_eq_init(Te->M + Te->M);
  for (i = 0; i < Te->M; i++)
  {
    if (Te->st[i] != 0)
    {
      {
        ST_eq_insert(new, Te->st[i]);
      }
    }
    else
    {
      
    }

  }

  free(Te->st);
  free(Te);
  return new;
}

void free_HTe(ST_eq T)
{
  long i;
  for (i = 0; i < T->M; i++)
  {
    free_Equipa(T->st[i]);
  }

  free(T->st);
  free(T);
}

void free_HTj(ST_jg T)
{
  long i;
  for (i = 0; i < T->M; i++)
  {
    free_Jogo(T->st[i]);
  }

  free(T->st);
  free(T);
}
