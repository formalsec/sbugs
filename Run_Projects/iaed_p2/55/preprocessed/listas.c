/*File generated by PreProcessor.py*/


#include "listas.h"
#include "estruturas.h"


lista_equipa *cria_lista_equipa()
{
  lista_equipa *novaLista = (lista_equipa *) malloc(sizeof(lista_equipa));
  if (novaLista == 0)
  {
    puts("cria_lista: Error. malloc returned NULL\n");
  }
  else
  {
    
  }

  novaLista->inicio = 0;
  novaLista->fim = 0;
  return novaLista;
}

lista *cria_lista()
{
  lista *novaLista = (lista *) malloc(sizeof(lista));
  if (novaLista == 0)
  {
    puts("cria_lista: Error. malloc returned NULL\n");
  }
  else
  {
    
  }

  novaLista->inicio = 0;
  novaLista->fim = 0;
  return novaLista;
}

lista_ponteiro *cria_lista_ponteiros()
{
  lista_ponteiro *novaLista = (lista_ponteiro *) malloc(sizeof(lista_ponteiro));
  if (novaLista == 0)
  {
    puts("cria_lista: Error. malloc returned NULL\n");
  }
  else
  {
    
  }

  novaLista->inicio = 0;
  novaLista->fim = 0;
  return novaLista;
}

int eh_vazia_equipa(const lista_equipa *l)
{
  return (l->inicio == 0) && (l->fim == 0);
}

int eh_vazia(const lista *l)
{
  return (l->inicio == 0) && (l->fim == 0);
}

int eh_vazia_ponteiros(const lista_ponteiro *l)
{
  return (l->inicio == 0) && (l->fim == 0);
}

void adiciona_equipa_fim(lista_equipa *l, elo_equipa novo_no)
{
  if ((l->inicio == 0) && (l->fim == 0))
  {
    {
      if (0)
      {
        puts("Lista vazia");
      }
      else
      {
        
      }

      l->inicio = novo_no;
      l->fim = novo_no;
      novo_no->proximo = 0;
    }
  }
  else
  {
    {
      if (0)
      {
        puts("Lista com elemento");
      }
      else
      {
        
      }

      novo_no->proximo = 0;
      l->fim->proximo = novo_no;
      l->fim = novo_no;
    }
  }

  return;
}

void adiciona_fim(lista *l, elo_jogo novo_no)
{
  if ((l->inicio == 0) && (l->fim == 0))
  {
    {
      if (0)
      {
        puts("Lista vazia");
      }
      else
      {
        
      }

      l->inicio = novo_no;
      l->fim = novo_no;
      novo_no->proximo = 0;
    }
  }
  else
  {
    {
      if (0)
      {
        puts("Lista com elemento");
      }
      else
      {
        
      }

      l->fim->proximo = novo_no;
      l->fim = novo_no;
      novo_no->proximo = 0;
    }
  }

  return;
}

void adiciona_fim_ponteiro(lista_ponteiro *l, elo_ponteiro novo_no)
{
  if ((l->inicio == 0) && (l->fim == 0))
  {
    {
      if (0)
      {
        puts("Lista vazia");
      }
      else
      {
        
      }

      l->inicio = novo_no;
      l->fim = novo_no;
      novo_no->proximo = 0;
    }
  }
  else
  {
    {
      if (0)
      {
        puts("Lista com elemento");
      }
      else
      {
        
      }

      l->fim->proximo = novo_no;
      l->fim = novo_no;
      novo_no->proximo = 0;
    }
  }

  return;
}

void adiciona_inicio(lista *l, elo_jogo novo_no)
{
  if ((l->inicio == 0) && (l->fim == 0))
  {
    {
      if (0)
      {
        puts("Lista vazia");
      }
      else
      {
        
      }

      l->inicio = novo_no;
      l->fim = novo_no;
      novo_no->proximo = 0;
    }
  }
  else
  {
    {
      if (0)
      {
        puts("Lista com elemento");
      }
      else
      {
        
      }

      novo_no->proximo = l->inicio;
      l->inicio = novo_no;
    }
  }

  return;
}

void remove_no_equipa(lista_equipa *l, elo_equipa no)
{
  elo_equipa no_velho = no;
  if (!eh_vazia_equipa(l))
  {
    {
      if (l->inicio == l->fim)
      {
        {
          liberta_no_equipa(no);
          l->inicio = 0;
          l->fim = 0;
        }
      }
      else
      {
        if (l->inicio == no)
        {
          {
            if (0)
            {
              printf("Remove primeiro da lista\n");
            }
            else
            {
              
            }

            l->inicio = no->proximo;
            liberta_no_equipa(no_velho);
          }
        }
        else
        {
          if (l->fim == no)
          {
            {
              if (0)
              {
                printf("Remove ultimo da lista\n");
              }
              else
              {
                
              }

              liberta_no_equipa(no_velho);
            }
          }
          else
          {
            {
              liberta_no_equipa(no_velho);
            }
          }

        }

      }

      return;
    }
  }
  else
  {
    
  }

  return;
}

void remove_no_jogo(lista *l, elo_jogo no)
{
  char *jogo = *no->jogo;
  elo_jogo no_velho = no;
  elo_jogo seguidor = 0;
  elo_jogo t = l->inicio;
  if (!eh_vazia(l))
  {
    {
      if (l->inicio == l->fim)
      {
        {
          liberta_no_jogo(no);
          l->inicio = 0;
          l->fim = 0;
          return;
        }
      }
      else
      {
        
      }

      if (l->inicio == no)
      {
        {
          if (0)
          {
            printf("Remove primeiro da lista\n");
          }
          else
          {
            
          }

          l->inicio = no->proximo;
          liberta_no_jogo(no_velho);
          return;
        }
      }
      else
      {
        
      }

      for (t = l->inicio, seguidor = 0; t != 0; seguidor = t, t = t->proximo)
      {
        if (strcmp(*t->jogo, jogo) == 0)
        {
          {
            if (t == l->inicio)
            {
              l->inicio = t->proximo;
            }
            else
            {
              if (t == l->fim)
              {
                {
                  l->fim = seguidor;
                  seguidor->proximo = 0;
                }
              }
              else
              {
                seguidor->proximo = t->proximo;
              }

            }

            liberta_no_jogo(t);
            return;
          }
        }
        else
        {
          
        }

      }

      return;
    }
  }
  else
  {
    
  }

  puts("remove_no_jogo: Erro -> argumento eh lista vazia\n");
  return;
}

void remove_no_ponteiro(lista_ponteiro *l, elo_ponteiro no)
{
  char *jogo = *no->ponteiro->jogo;
  elo_ponteiro no_velho = no;
  elo_ponteiro seguidor = 0;
  elo_ponteiro t = l->inicio;
  if (!eh_vazia_ponteiros(l))
  {
    {
      if (l->inicio == l->fim)
      {
        {
          liberta_no_ponteiro(no);
          l->inicio = 0;
          l->fim = 0;
          return;
        }
      }
      else
      {
        
      }

      if (l->inicio == no)
      {
        {
          if (0)
          {
            printf("Remove primeiro da lista\n");
          }
          else
          {
            
          }

          l->inicio = no->proximo;
          liberta_no_ponteiro(no_velho);
          return;
        }
      }
      else
      {
        
      }

      for (t = l->inicio, seguidor = 0; t != 0; seguidor = t, t = t->proximo)
      {
        if (strcmp(*t->ponteiro->jogo, jogo) == 0)
        {
          {
            if (t == l->inicio)
            {
              l->inicio = t->proximo;
            }
            else
            {
              if (t == l->fim)
              {
                {
                  l->fim = seguidor;
                  seguidor->proximo = 0;
                }
              }
              else
              {
                seguidor->proximo = t->proximo;
              }

            }

            liberta_no_ponteiro(t);
            return;
          }
        }
        else
        {
          
        }

      }

      return;
    }
  }
  else
  {
    
  }

  puts("remove_no_ponteiro: Erro -> argumento eh lista vazia\n");
  return;
}

int Retorna_max_vitorias(const lista_equipa *le)
{
  int max_vitorias = 0;
  elo_equipa inicio = le->inicio;
  if (!eh_vazia_equipa(le))
  {
    {
      while (inicio != 0)
      {
        if ((*inicio->vitorias) > max_vitorias)
        {
          {
            max_vitorias = *inicio->vitorias;
          }
        }
        else
        {
          
        }

        inicio = inicio->proximo;
      }

      return max_vitorias;
    }
  }
  else
  {
    
  }

  return 0;
}

int Retorna_contador_max_vitorias(const lista_equipa *le, int max_vitorias)
{
  int contador_vitorias = 0;
  elo_equipa inicio = le->inicio;
  if (!eh_vazia_equipa(le))
  {
    {
      while (inicio != 0)
      {
        if ((*inicio->vitorias) == max_vitorias)
        {
          {
            contador_vitorias++;
          }
        }
        else
        {
          
        }

        if ((*inicio->vitorias) > max_vitorias)
        {
          {
            printf("Erro RRRRetorna_max_vitorias: vitorias > max_vitorias\n");
          }
        }
        else
        {
          
        }

        inicio = inicio->proximo;
      }

      return contador_vitorias;
    }
  }
  else
  {
    
  }

  return 0;
}

elo_equipa procura_no_equipa(const lista_equipa *le, char *equipa)
{
  elo_equipa inicio = le->inicio;
  if (!eh_vazia_equipa(le))
  {
    {
      while (inicio != 0)
      {
        if (strcmp(*inicio->equipa, equipa) == 0)
        {
          {
            return inicio;
          }
        }
        else
        {
          
        }

        inicio = inicio->proximo;
      }

      return 0;
    }
  }
  else
  {
    
  }

  return 0;
}

elo_jogo procura_no_jogo(const lista *l, char *jogo)
{
  elo_jogo inicio = l->inicio;
  if (!eh_vazia(l))
  {
    {
      while (inicio != 0)
      {
        if (strcmp(*inicio->jogo, jogo) == 0)
        {
          {
            return inicio;
          }
        }
        else
        {
          
        }

        inicio = inicio->proximo;
      }

      return 0;
    }
  }
  else
  {
    
  }

  return 0;
}

void altera_vitorias_empate(int s1, int s2, int s1v, int s2v, elo_equipa no1, elo_equipa n2)
{
  int score1 = s1;
  int score2 = s2;
  int score_velho1 = s1v;
  int score_velho2 = s2v;
  elo_equipa No_equipa1 = no1;
  elo_equipa No_equipa2 = n2;
  if ((score_velho1 == score_velho2) && (score1 > score2))
  {
    {
      *No_equipa1->vitorias += 1;
      return;
    }
  }
  else
  {
    
  }

  if ((score_velho1 == score_velho2) && (score1 < score2))
  {
    {
      *No_equipa2->vitorias += 1;
      return;
    }
  }
  else
  {
    
  }

}

void altera_vitorias_equipa1(int s1, int s2, int s1v, int s2v, elo_equipa no1, elo_equipa n2)
{
  int score1 = s1;
  int score2 = s2;
  int score_velho1 = s1v;
  int score_velho2 = s2v;
  elo_equipa No_equipa1 = no1;
  elo_equipa No_equipa2 = n2;
  if ((score_velho1 > score_velho2) && (score1 == score2))
  {
    {
      *No_equipa1->vitorias -= 1;
      return;
    }
  }
  else
  {
    
  }

  if ((score_velho1 > score_velho2) && (score1 < score2))
  {
    {
      *No_equipa1->vitorias -= 1;
      *No_equipa2->vitorias += 1;
      return;
    }
  }
  else
  {
    
  }

  return;
}

void altera_vitorias_equipa2(int s1, int s2, int s1v, int s2v, elo_equipa no1, elo_equipa n2)
{
  int score1 = s1;
  int score2 = s2;
  int score_velho1 = s1v;
  int score_velho2 = s2v;
  elo_equipa No_equipa1 = no1;
  elo_equipa No_equipa2 = n2;
  if ((score_velho1 < score_velho2) && (score1 == score2))
  {
    {
      *No_equipa2->vitorias -= 1;
      return;
    }
  }
  else
  {
    
  }

  if ((score_velho1 < score_velho2) && (score1 > score2))
  {
    {
      *No_equipa1->vitorias += 1;
      *No_equipa2->vitorias -= 1;
      return;
    }
  }
  else
  {
    
  }

}

void altera_score(int score1, int score2, elo_jogo no)
{
  *no->score1 = score1;
  *no->score2 = score2;
  return;
}

void liberta_lista_equipa(lista_equipa *l)
{
  lista_equipa *lista_velha = l;
  elo_equipa inicio = l->inicio;
  elo_equipa no_velho;
  while (inicio != 0)
  {
    no_velho = inicio;
    inicio = inicio->proximo;
    liberta_no_equipa(no_velho);
  }

  free(lista_velha);
  return;
}

void liberta_lista_jogo(lista *l)
{
  lista *lista_velha = l;
  elo_jogo inicio = l->inicio;
  elo_jogo no_velho;
  while (inicio != 0)
  {
    no_velho = inicio;
    inicio = inicio->proximo;
    liberta_no_jogo(no_velho);
  }

  free(lista_velha);
  return;
}

void liberta_lista_ponteiro(lista_ponteiro *l)
{
  lista_ponteiro *lista_velha = l;
  elo_ponteiro inicio = l->inicio;
  elo_ponteiro no_velho;
  while (inicio != 0)
  {
    no_velho = inicio;
    inicio = inicio->proximo;
    liberta_no_ponteiro(no_velho);
  }

  free(lista_velha);
  return;
}
