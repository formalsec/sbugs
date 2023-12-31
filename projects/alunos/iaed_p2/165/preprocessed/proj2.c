#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>


int hash(char *v, int M)
{
  int h = 0;
  int a = 127;
  for (; (*v) != '\0'; v++)
    h = ((a * h) + (*v)) % M;

  return h;
}

typedef struct Jogos
{
  char *nome;
  char *equipa1;
  char *equipa2;
  int score1;
  int score2;
} *Jogo;
typedef struct node
{
  Jogo j;
  struct node *next;
} *link;
static link *heads;
static int M;
struct Jogos *jogos[1000];
static int counter_jogos = 0;
void Init_Jogos(int m)
{
  int i;
  M = m;
  heads = (link *) malloc(M * (sizeof(link)));
  for (i = 0; i < M; i++)
    heads[i] = 0;

}

Jogo create_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
  Jogo jogo;
  jogo = (Jogo) malloc(sizeof(struct Jogos));
  jogo->nome = (char *) malloc((sizeof(char)) * (strlen(nome) + 1));
  jogo->equipa1 = (char *) malloc((sizeof(char)) * (strlen(equipa1) + 1));
  jogo->equipa2 = (char *) malloc((sizeof(char)) * (strlen(equipa2) + 1));
  strcpy(jogo->nome, nome);
  strcpy(jogo->equipa1, equipa1);
  strcpy(jogo->equipa2, equipa2);
  jogo->score1 = score1;
  jogo->score2 = score2;
  return jogo;
}

link NEW_Jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
  Jogo p;
  link x;
  x = (link) malloc(sizeof(struct node));
  p = create_jogo(nome, equipa1, equipa2, score1, score2);
  x->j = p;
  x->next = 0;
  return x;
}

link insertList_Jogo(link h, Jogo j)
{
  link x;
  if (h == 0)
  {
    return NEW_Jogo(j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
  }
  else
  {
    
  }

  for (x = h; x->next != 0; x = x->next)
    ;

  x->next = NEW_Jogo(j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
  return h;
}

void STinsert_Jogo(Jogo j)
{
  int i;
  i = hash(j->nome, M);
  heads[i] = insertList_Jogo(heads[i], j);
}

link lookup_Jogo(link h, char *nome)
{
  link t;
  for (t = h; t != 0; t = t->next)
    if (strcmp(t->j->nome, nome) == 0)
  {
    return t;
  }
  else
  {
    
  }


  return 0;
}

link STsearch_Jogo(char *nome)
{
  int i;
  i = hash(nome, M);
  return lookup_Jogo(heads[i], nome);
}

link delete_Jogo(link h, char *nome)
{
  link t;
  link prev;
  for (t = h, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->j->nome, nome) == 0)
    {
      if (t == h)
      {
        h = t->next;
      }
      else
      {
        prev->next = t->next;
      }

      free(t->j);
      free(t);
      break;
    }
    else
    {
      
    }

  }

  return h;
}

void STdelete_Jogo(char *nome)
{
  int i;
  i = hash(nome, M);
  heads[i] = delete_Jogo(heads[i], nome);
}

int hash_equipa(char *v, int L)
{
  int h = 0;
  int a = 127;
  for (; (*v) != '\0'; v++)
    h = ((a * h) + (*v)) % L;

  return h;
}

typedef struct Equipas
{
  char *nome;
  int jogos_ganhos;
} *Equipa;
typedef struct node_equipa
{
  Equipa e;
  struct node_equipa *next;
} *link_equipa;
static link_equipa *heads_equipa;
static int L;
void Init_Equipas(int m)
{
  int i;
  L = m;
  heads_equipa = (link_equipa *) malloc(L * (sizeof(link_equipa)));
  for (i = 0; i < L; i++)
    heads_equipa[i] = 0;

}

Equipa create_equipa(char *nome)
{
  Equipa equipa;
  equipa = (Equipa) malloc(sizeof(struct Equipas));
  equipa->nome = (char *) malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(equipa->nome, nome);
  equipa->jogos_ganhos = 0;
  return equipa;
}

link_equipa NEW_Equipa(char *nome)
{
  Equipa p;
  link_equipa x;
  x = (link_equipa) malloc(sizeof(struct node_equipa));
  p = create_equipa(nome);
  x->e = p;
  x->next = 0;
  return x;
}

link_equipa insertList_Equipa(link_equipa h, Equipa e)
{
  link_equipa x;
  if (h == 0)
  {
    return NEW_Equipa(e->nome);
  }
  else
  {
    
  }

  for (x = h; x->next != 0; x = x->next)
    ;

  x->next = NEW_Equipa(e->nome);
  return h;
}

void STinsert_Equipa(Equipa e)
{
  int i;
  i = hash_equipa(e->nome, L);
  heads_equipa[i] = insertList_Equipa(heads_equipa[i], e);
}

link_equipa lookup_Equipa(link_equipa h, char *nome)
{
  link_equipa t;
  for (t = h; t != 0; t = t->next)
    if (strcmp(t->e->nome, nome) == 0)
  {
    return t;
  }
  else
  {
    
  }


  return 0;
}

link_equipa STsearch_Equipa(char *nome)
{
  int i;
  i = hash_equipa(nome, L);
  return lookup_Equipa(heads_equipa[i], nome);
}

void a(int NL)
{
  link_equipa t;
  Jogo j;
  char nome[1023];
  char equipa1[1023];
  char equipa2[1023];
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
  if ((STsearch_Equipa(equipa1) == 0) || (STsearch_Equipa(equipa2) == 0))
  {
    printf("%d Equipa inexistente\n", NL);
    return;
  }
  else
  {
    if (STsearch_Jogo(nome) != 0)
    {
      printf("%d Jogo existente\n", NL);
      return;
    }
    else
    {
      if (score1 > score2)
      {
        t = STsearch_Equipa(equipa1);
        t->e->jogos_ganhos++;
      }
      else
      {
        if (score2 > score1)
        {
          t = STsearch_Equipa(equipa2);
          t->e->jogos_ganhos++;
        }
        else
        {
          
        }

      }

      j = create_jogo(nome, equipa1, equipa2, score1, score2);
      STinsert_Jogo(j);
      jogos[counter_jogos] = j;
      counter_jogos++;
    }

  }

}

void l(int NL)
{
  int i;
  for (i = 0; i < counter_jogos; i++)
  {
    printf("%d %s %s %s %d %d\n", NL, jogos[i]->nome, jogos[i]->equipa1, jogos[i]->equipa2, jogos[i]->score1, jogos[i]->score2);
  }

}

void p(int NL)
{
  link t;
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (STsearch_Jogo(nome) == 0)
  {
    printf("%d Jogo inexistente\n", NL);
    return;
  }
  else
  {
    t = STsearch_Jogo(nome);
    printf("%d %s %s %s %d %d\n", NL, t->j->nome, t->j->equipa1, t->j->equipa2, t->j->score1, t->j->score2);
  }

}

void r(int NL)
{
  link t;
  link_equipa p;
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (STsearch_Jogo(nome) == 0)
  {
    printf("%d Jogo inexistente", NL);
    return;
  }
  else
  {
    t = STsearch_Jogo(nome);
    if (t->j->score1 > t->j->score2)
    {
      p = STsearch_Equipa(t->j->equipa1);
      p->e->jogos_ganhos--;
    }
    else
    {
      if (t->j->score2 > t->j->score1)
      {
        p = STsearch_Equipa(t->j->equipa2);
        p->e->jogos_ganhos--;
      }
      else
      {
        
      }

    }

    STdelete_Jogo(nome);
  }

}

void s(int NL)
{
  link_equipa t1;
  link_equipa t2;
  link t;
  char nome[1023];
  int newscore1;
  int newscore2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  newscore1 = new_sym_var(sizeof(int) * 8);
  newscore2 = new_sym_var(sizeof(int) * 8);
  if (STsearch_Jogo(nome) == 0)
  {
    printf("%d Jogo inexistente\n", NL);
    return;
  }
  else
  {
    t = STsearch_Jogo(nome);
    if (t->j->score1 > t->j->score2)
    {
      if (newscore1 > newscore2)
      {
        t->j->score1 = newscore1;
        t->j->score2 = newscore2;
        return;
      }
      else
      {
        if (newscore2 > newscore1)
        {
          t1 = STsearch_Equipa(t->j->equipa1);
          t1->e->jogos_ganhos--;
          t2 = STsearch_Equipa(t->j->equipa2);
          t2->e->jogos_ganhos++;
          t->j->score1 = newscore1;
          t->j->score2 = newscore2;
          return;
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (t->j->score2 > t->j->score1)
      {
        if (newscore1 > newscore2)
        {
          t1 = STsearch_Equipa(t->j->equipa1);
          t1->e->jogos_ganhos++;
          t2 = STsearch_Equipa(t->j->equipa2);
          t2->e->jogos_ganhos--;
          t->j->score1 = newscore1;
          t->j->score2 = newscore2;
          return;
        }
        else
        {
          if (newscore2 > newscore1)
          {
            t->j->score1 = newscore1;
            t->j->score2 = newscore2;
            return;
          }
          else
          {
            
          }

        }

      }
      else
      {
        if (newscore1 > newscore2)
        {
          t1 = STsearch_Equipa(t->j->equipa1);
          t1->e->jogos_ganhos++;
          t->j->score1 = newscore1;
          t->j->score2 = newscore2;
          return;
        }
        else
        {
          if (newscore2 > newscore1)
          {
            t2 = STsearch_Equipa(t->j->equipa2);
            t2->e->jogos_ganhos++;
            t->j->score1 = newscore1;
            t->j->score2 = newscore2;
            return;
          }
          else
          {
            t->j->score1 = newscore1;
            t->j->score2 = newscore2;
            return;
          }

        }

      }

    }

  }

}

void A(int NL)
{
  Equipa t;
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (STsearch_Equipa(nome) != 0)
  {
    printf("%d Equipa existente\n", NL);
    return;
  }
  else
  {
    t = create_equipa(nome);
    STinsert_Equipa(t);
    return;
  }

}

void P(int NL)
{
  link_equipa t;
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (STsearch_Equipa(nome) == 0)
  {
    printf("%d Equipa inexistente\n", NL);
    return;
  }
  else
  {
    t = STsearch_Equipa(nome);
    printf("%d %s %d\n", NL, t->e->nome, t->e->jogos_ganhos);
    return;
  }

}

void g(int NL)
{
  int i;
  int j;
  int cnt;
  int max;
  struct Equipas *tmp;
  struct Equipas *max_jogos[499];
  link_equipa t;
  cnt = 0;
  max = 0;
  for (i = 0; i < M; i++)
  {
    for (t = heads_equipa[i]; t != 0; t = t->next)
    {
      if (t->e->jogos_ganhos > max)
      {
        max = t->e->jogos_ganhos;
      }
      else
      {
        
      }

    }

  }

  for (i = 0; i < M; i++)
  {
    for (t = heads_equipa[i]; t != 0; t = t->next)
    {
      if (t->e->jogos_ganhos == max)
      {
        max_jogos[cnt] = t->e;
        cnt++;
      }
      else
      {
        
      }

    }

  }

  for (i = 0; i < cnt; i++)
  {
    for (j = 0; j < cnt; j++)
    {
      if (strcmp(max_jogos[i]->nome, max_jogos[j]->nome) < 0)
      {
        tmp = max_jogos[i];
        max_jogos[i] = max_jogos[j];
        max_jogos[j] = tmp;
      }
      else
      {
        
      }

    }

  }

  if (cnt > 0)
  {
    printf("%d Melhores  %d\n", NL, max);
    for (i = 0; i < cnt; i++)
    {
      printf("%d * %s\n", NL, max_jogos[i]->nome);
    }

  }
  else
  {
    
  }

}

void x()
{
  exit(0);
}

int main()
{
  int NL;
  char c;
  NL = 1;
  Init_Equipas(109);
  Init_Jogos(109);
  do
  {
    c = new_sym_var(sizeof(char) * 8);
    if (c == 'a')
    {
      a(NL);
      NL++;
    }
    else
    {
      
    }

    if (c == 'l')
    {
      l(NL);
      NL++;
    }
    else
    {
      
    }

    if (c == 'p')
    {
      p(NL);
      NL++;
    }
    else
    {
      
    }

    if (c == 'r')
    {
      r(NL);
      NL++;
    }
    else
    {
      
    }

    if (c == 's')
    {
      s(NL);
      NL++;
    }
    else
    {
      
    }

    if (c == 'A')
    {
      A(NL);
      NL++;
    }
    else
    {
      
    }

    if (c == 'P')
    {
      P(NL);
      NL++;
    }
    else
    {
      
    }

    if (c == 'x')
    {
      x();
    }
    else
    {
      
    }

    if (c == 'g')
    {
      g(NL);
      NL++;
    }
    else
    {
      
    }

  }
  while (1);
}

