#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "proj2.h"


linkjogo NEWjogo(char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
  linkjogo x = (linkjogo) malloc(sizeof(struct jogo));
  x->nome = (char *) malloc((sizeof(char)) * (strlen(nome) + 1));
  x->equipa1 = (char *) malloc((sizeof(char)) * (strlen(equipa1) + 1));
  x->equipa2 = (char *) malloc((sizeof(char)) * (strlen(equipa2) + 1));
  strcpy(x->nome, nome);
  strcpy(x->equipa1, equipa1);
  strcpy(x->equipa2, equipa2);
  x->score1 = score1;
  x->score2 = score2;
  x->next = 0;
  return x;
}

linkequipa NEWequipa(char *nome_equipa)
{
  linkequipa e = (linkequipa) malloc(sizeof(struct equipa));
  e->nome = (char *) malloc((sizeof(char)) * (strlen(nome_equipa) + 1));
  strcpy(e->nome, nome_equipa);
  e->next = 0;
  return e;
}

linkjogo insertEndJogo(linkjogo headjogo, char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
  linkjogo x;
  if (headjogo == 0)
  {
    return NEWjogo(nome, equipa1, equipa2, score1, score2);
  }
  else
  {
    
  }

  for (x = headjogo; x->next != 0; x = x->next)
  {
    ;
  }

  x->next = NEWjogo(nome, equipa1, equipa2, score1, score2);
  return headjogo;
}

linkequipa insertEndEquipa(linkequipa headequipa, char *nome_equipa)
{
  linkequipa e;
  if (headequipa == 0)
  {
    return NEWequipa(nome_equipa);
  }
  else
  {
    
  }

  for (e = headequipa; e->next != 0; e = e->next)
  {
    ;
  }

  e->next = NEWequipa(nome_equipa);
  return headequipa;
}

linkjogo removeJogo(linkjogo headjogo, char *nome_jogo)
{
  linkjogo prev;
  linkjogo t;
  for (t = headjogo, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->nome, nome_jogo) == 0)
    {
      if (t == headjogo)
      {
        headjogo = t->next;
      }
      else
      {
        prev->next = t->next;
      }

      free(t->nome);
      free(t->equipa1);
      free(t->equipa2);
      free(t);
      break;
    }
    else
    {
      
    }

  }

  return headjogo;
}

linkequipa removeEquipa(linkequipa headequipa, char *nome_equipa)
{
  linkequipa prev;
  linkequipa t;
  for (t = headequipa, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->nome, nome_equipa) == 0)
    {
      if (t == headequipa)
      {
        headequipa = t->next;
      }
      else
      {
        prev->next = t->next;
      }

      free(t->nome);
      free(t);
      break;
    }
    else
    {
      
    }

  }

  return headequipa;
}

void procuraEquipa(linkjogo headjogo, char *nome, int contlinha)
{
  linkjogo aux;
  int soma = 0;
  for (aux = headjogo; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->equipa1, nome) == 0)
    {
      if (aux->score1 > aux->score2)
      {
        soma++;
      }
      else
      {
        
      }

    }
    else
    {
      if (strcmp(aux->equipa2, nome) == 0)
      {
        if (aux->score2 > aux->score1)
        {
          soma++;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

  }

  printf("%d %s %d\n", contlinha, nome, soma);
}

int compare(const void *p1, const void *p2)
{
  char **a;
  char **b;
  a = (char **) p1;
  b = (char **) p2;
  return strcmp(*a, *b);
}

void listaGanhos(linkjogo headjogo, linkequipa headequipa, int contlinha, int max_g, int quant_g)
{
  linkjogo jogo;
  linkequipa equipa;
  int i = 0;
  int soma = 0;
  int max = max_g;
  int quant = quant_g;
  char buffer[1024];
  char **equipas;
  equipas = (char **) malloc((sizeof(char *)) * quant);
  if (headjogo == 0)
  {
    for (equipa = headequipa; equipa != 0; equipa = equipa->next)
    {
      strcpy(buffer, equipa->nome);
      equipas[i] = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
      strcpy(equipas[i], buffer);
      i++;
    }

  }
  else
  {
    for (equipa = headequipa; equipa != 0; equipa = equipa->next)
    {
      for (jogo = headjogo; jogo != 0; jogo = jogo->next)
      {
        if ((strcmp(equipa->nome, jogo->equipa1) == 0) && (jogo->score1 > jogo->score2))
        {
          soma++;
        }
        else
        {
          if ((strcmp(equipa->nome, jogo->equipa2) == 0) && (jogo->score2 > jogo->score1))
          {
            soma++;
          }
          else
          {
            
          }

        }

      }

      if (soma == max)
      {
        strcpy(buffer, equipa->nome);
        equipas[i] = (char *) malloc((sizeof(char)) * (strlen(buffer) + 1));
        strcpy(equipas[i], buffer);
        i++;
        soma = 0;
      }
      else
      {
        soma = 0;
      }

    }

  }

  qsort(equipas, quant, sizeof(char *), compare);
  printf("%d Melhores %d\n", contlinha, max);
  for (i = 0; i < quant; i++)
  {
    printf("%d * %s\n", contlinha, equipas[i]);
    free(equipas[i]);
  }

  free(equipas);
}

