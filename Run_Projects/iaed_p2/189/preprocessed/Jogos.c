/*File generated by PreProcessor.py*/


#include "Jogos.h"
#include "func_hash.h"


ptr_jogo novo_jogo(char *nome, char *eq1, char *eq2, int score1, int score2)
{
  ptr_jogo novo = (ptr_jogo) malloc(sizeof(struct jogo));
  novo->nome = nome;
  novo->equipa1 = eq1;
  novo->equipa2 = eq2;
  novo->score1 = score1;
  novo->score2 = score2;
  return novo;
}

link_j insere_fim_j(link_j ultimo_jogo, link_j j1)
{
  if (ultimo_jogo == 0)
  {
    return j1;
  }
  else
  {
    
  }

  ultimo_jogo->proximo = j1;
  j1->proximo = 0;
  return j1;
}

link_j procura_j(link_j primeiro_jogo, char *nome)
{
  link_j x;
  for (x = primeiro_jogo; x != 0; x = x->proximo)
    if (strcmp(x->jogo->nome, nome) == 0)
  {
    return x;
  }
  else
  {
    
  }


  return 0;
}

void FreeNomes_j(link_j x)
{
  free(x->jogo->nome);
  free(x->jogo->equipa1);
  free(x->jogo->equipa2);
  free(x->jogo);
}

void FreeNode_j(link_j x)
{
  free(x->jogo);
  free(x);
}

link_j apaga_j(link_j *primeiros_j, link_j primeiro_jogo, char *nome, link_j *fim_lista)
{
  link_j x;
  link_j y;
  link_j anterior;
  for (x = primeiro_jogo, anterior = 0; x != 0; anterior = x, x = x->proximo)
  {
    if (strcmp(x->jogo->nome, nome) == 0)
    {
      {
        if (x == primeiro_jogo)
        {
          {
            primeiro_jogo = x->proximo;
            if ((*fim_lista) == x)
            {
              *fim_lista = x->proximo;
            }
            else
            {
              
            }

          }
        }
        else
        {
          {
            anterior->proximo = x->proximo;
            if ((*fim_lista) == x)
            {
              *fim_lista = anterior;
            }
            else
            {
              
            }

          }
        }

        y = apaga_jogo(primeiros_j, nome);
        free(x->jogo->nome);
        free(x->jogo->equipa1);
        free(x->jogo->equipa2);
        FreeNode_j(x);
        free(y);
        return primeiro_jogo;
      }
    }
    else
    {
      
    }

  }

  return primeiro_jogo;
}

link_j *inicializa_j(link_j *primeiros_j)
{
  int k;
  primeiros_j = (link_j *) malloc(1009 * (sizeof(link_j)));
  for (k = 0; k < 1009; k++)
    primeiros_j[k] = 0;

  return primeiros_j;
}

void insere_jogo(link_j *primeiros_j, link_j j1)
{
  int i = func_hash(j1->jogo->nome);
  primeiros_j[i] = insere_inicio_j(primeiros_j[i], j1);
}

link_j insere_inicio_j(link_j inicio, link_j j1)
{
  j1->proximo = inicio;
  return j1;
}

link_j procura_jogo(link_j *primeiros_j, char *nome)
{
  link_j k;
  int i = func_hash(nome);
  k = procura_j(primeiros_j[i], nome);
  return k;
}

link_j apaga_jogo(link_j *primeiros_j, char *nome)
{
  link_j primeiro_jogo;
  link_j anterior;
  link_j x;
  int i = func_hash(nome);
  primeiro_jogo = primeiros_j[i];
  for (x = primeiro_jogo, anterior = 0; x != 0; anterior = x, x = x->proximo)
  {
    if (strcmp(x->jogo->nome, nome) == 0)
    {
      {
        if (x == primeiro_jogo)
        {
          primeiros_j[i] = x->proximo;
        }
        else
        {
          anterior->proximo = x->proximo;
        }

        break;
      }
    }
    else
    {
      
    }

  }

  return x;
}
