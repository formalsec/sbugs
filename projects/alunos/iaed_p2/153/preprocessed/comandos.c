#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "proj2.h"


linkjogo a(linkjogo headjogo, linkequipa headequipa, int contlinha)
{
  char nome[1024];
  char equipa1[1024];
  char equipa2[1024];
  int score1;
  int score2;
  int cont = 0;
  int cont1 = 0;
  int cont2 = 0;
  linkjogo a;
  linkequipa b;
  linkequipa c;
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
  if (headjogo != 0)
  {
    for (a = headjogo; a != 0; a = a->next)
    {
      if (strcmp(a->nome, nome) == 0)
      {
        cont++;
        break;
      }
      else
      {
        
      }

    }

    if (cont == 1)
    {
      printf("%d Jogo existente.\n", contlinha);
    }
    else
    {
      for (b = headequipa; b != 0; b = b->next)
      {
        if ((strcmp(b->nome, equipa1) == 0) || (strcmp(b->nome, equipa2) == 0))
        {
          cont1++;
        }
        else
        {
          
        }

      }

      if (cont1 != 2)
      {
        printf("%d Equipa inexistente.\n", contlinha);
      }
      else
      {
        headjogo = insertEndJogo(headjogo, nome, equipa1, equipa2, score1, score2);
      }

    }

  }
  else
  {
    if (headequipa == 0)
    {
      printf("%d Equipa inexistente.\n", contlinha);
    }
    else
    {
      if (headequipa != 0)
      {
        for (c = headequipa; c != 0; c = c->next)
        {
          if ((strcmp(c->nome, equipa1) == 0) || (strcmp(c->nome, equipa2) == 0))
          {
            cont2++;
          }
          else
          {
            
          }

        }

        if (cont2 != 2)
        {
          printf("%d Equipa inexistente.\n", contlinha);
        }
        else
        {
          headjogo = insertEndJogo(headjogo, nome, equipa1, equipa2, score1, score2);
        }

      }
      else
      {
        
      }

    }

  }

  return headjogo;
}

linkequipa A(linkequipa headequipa, int contlinha)
{
  linkequipa aux;
  char nome_equipa[1024];
  int cont = 0;
  for (int nome_equipa_index = 0; nome_equipa_index < 10; nome_equipa_index++)
  {
    nome_equipa[nome_equipa_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_equipa[10 - 1] = '\0';
  if (headequipa == 0)
  {
    headequipa = insertEndEquipa(headequipa, nome_equipa);
  }
  else
  {
    for (aux = headequipa; aux != 0; aux = aux->next)
    {
      if (strcmp(aux->nome, nome_equipa) == 0)
      {
        cont++;
      }
      else
      {
        
      }

    }

    if (cont > 0)
    {
      printf("%d Equipa existente.\n", contlinha);
    }
    else
    {
      headequipa = insertEndEquipa(headequipa, nome_equipa);
    }

  }

  return headequipa;
}

linkjogo s(linkjogo headjogo, int contlinha)
{
  linkjogo aux;
  char nome_jogo[1024];
  int score1;
  int score2;
  int cont = 0;
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  for (aux = headjogo; aux != 0; aux = aux->next)
  {
    if (strcmp(nome_jogo, aux->nome) == 0)
    {
      cont++;
      break;
    }
    else
    {
      
    }

  }

  if (cont != 1)
  {
    printf("%d Jogo inexistente.\n", contlinha);
  }
  else
  {
    aux->score1 = score1;
    aux->score2 = score2;
  }

  return headjogo;
}

linkjogo r(linkjogo headjogo, int contlinha)
{
  linkjogo aux;
  char nome_jogo[1024];
  int cont = 0;
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  for (aux = headjogo; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->nome, nome_jogo) == 0)
    {
      cont++;
      break;
    }
    else
    {
      
    }

  }

  if (cont != 1)
  {
    printf("%d Jogo inexistente.\n", contlinha);
  }
  else
  {
    headjogo = removeJogo(headjogo, nome_jogo);
  }

  return headjogo;
}

void P(linkjogo headjogo, linkequipa headequipa, int contlinha)
{
  linkequipa aux;
  char nome[1024];
  int cont = 0;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  for (aux = headequipa; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->nome, nome) == 0)
    {
      cont++;
      break;
    }
    else
    {
      
    }

  }

  if (cont != 1)
  {
    printf("%d Equipa inexistente.\n", contlinha);
  }
  else
  {
    procuraEquipa(headjogo, nome, contlinha);
  }

}

void p(linkjogo headjogo, int contlinha)
{
  linkjogo aux;
  char nome_jogo[1024];
  int cont = 0;
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  for (aux = headjogo; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->nome, nome_jogo) == 0)
    {
      cont++;
      break;
    }
    else
    {
      
    }

  }

  if (cont != 1)
  {
    printf("%d Jogo inexistente.\n", contlinha);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", contlinha, nome_jogo, aux->equipa1, aux->equipa2, aux->score1, aux->score2);
  }

}

void l(linkjogo headjogo, int contlinha)
{
  linkjogo aux;
  if (headjogo == 0)
  {
    ;
  }
  else
  {
    for (aux = headjogo; aux != 0; aux = aux->next)
    {
      printf("%d %s %s %s %d %d\n", contlinha, aux->nome, aux->equipa1, aux->equipa2, aux->score1, aux->score2);
    }

  }

}

void g(linkjogo headjogo, linkequipa headequipa, int contlinha)
{
  linkjogo jogo;
  linkequipa equipa;
  int soma = 0;
  int max = 0;
  int quant = 1;
  if (headequipa == 0)
  {
    ;
  }
  else
  {
    if (headjogo == 0)
    {
      for (equipa = headequipa; equipa != 0; equipa = equipa->next)
      {
        quant++;
      }

      quant--;
      listaGanhos(headjogo, headequipa, contlinha, max, quant);
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

        if (soma > max)
        {
          max = soma;
          soma = 0;
          quant = 1;
        }
        else
        {
          if (soma == max)
          {
            soma = 0;
            quant++;
          }
          else
          {
            soma = 0;
          }

        }

      }

      listaGanhos(headjogo, headequipa, contlinha, max, quant);
    }

  }

}
