/*File generated by PreProcessor.py*/


#include "hash.h"
#include "linkedlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void adiciona_jogo(link1 *hashtable1, link2 *hashtable2, list *lista, int m)
{
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
  if (STsearchJ(nome, hashtable1, 1009) != 0)
  {
    printf("%d Jogo existente.\n", m);
  }
  else
  {
    if ((STsearchE(equipa1, hashtable2, 1009) == 0) || (STsearchE(equipa2, hashtable2, 1009) == 0))
    {
      printf("%d Equipa inexistente.\n", m);
    }
    else
    {
      STinsertJ(nome, equipa1, equipa2, score1, score2, hashtable1, 1009);
      add_last(lista, nome);
      if (score1 > score2)
      {
        link2 hashtable = STsearchE(equipa1, hashtable2, 1009);
        ++hashtable->vitorias;
      }
      else
      {
        if (score2 > score1)
        {
          link2 hashtable = STsearchE(equipa2, hashtable2, 1009);
          ++hashtable->vitorias;
        }
        else
        {
          
        }

      }

    }

  }

}

void lista_jogos(link1 *hashtable, list *lista, int m)
{
  link1 x;
  for (x = lista->head; x != 0; x = x->next)
  {
    link1 hash = STsearchJ(x->Jogo->nome, hashtable, 1009);
    printf("%d %s %s %s %d %d\n", m, hash->Jogo->nome, hash->Jogo->equipa1, hash->Jogo->equipa2, hash->Jogo->score1, hash->Jogo->score2);
  }

}

void procura_jogo(link1 *hashtable, int m)
{
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (STsearchJ(nome, hashtable, 1009) == 0)
  {
    printf("%d Jogo inexistente.\n", m);
  }
  else
  {
    link1 hash = STsearchJ(nome, hashtable, 1009);
    printf("%d %s %s %s %d %d\n", m, nome, hash->Jogo->equipa1, hash->Jogo->equipa2, hash->Jogo->score1, hash->Jogo->score2);
  }

}

void apaga_jogo(link1 *hashtable1, link2 *hashtable2, list *lista, int m)
{
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (STsearchJ(nome, hashtable1, 1009) == 0)
  {
    printf("%d Jogo inexistente.\n", m);
  }
  else
  {
    link1 hash1 = STsearchJ(nome, hashtable1, 1009);
    link2 hash2 = STsearchE(hash1->Jogo->equipa1, hashtable2, 1009);
    link2 hash3 = STsearchE(hash1->Jogo->equipa2, hashtable2, 1009);
    link1 node = search(lista, nome);
    if (hash1->Jogo->score1 > hash1->Jogo->score2)
    {
      --hash2->vitorias;
    }
    else
    {
      if (hash1->Jogo->score1 < hash1->Jogo->score2)
      {
        --hash3->vitorias;
      }
      else
      {
        
      }

    }

    rm_node(lista, node);
    STdelete(nome, hashtable1, 1009);
  }

}

void altera_score(link1 *hashtable1, link2 *hashtable2, int m)
{
  char nome[1023];
  int score1;
  int score2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (STsearchJ(nome, hashtable1, 1009) == 0)
  {
    printf("%d Jogo inexistente.\n", m);
  }
  else
  {
    link1 hash1 = STsearchJ(nome, hashtable1, 1009);
    link2 hash2 = STsearchE(hash1->Jogo->equipa1, hashtable2, 1009);
    link2 hash3 = STsearchE(hash1->Jogo->equipa2, hashtable2, 1009);
    if (score1 > score2)
    {
      if (hash1->Jogo->score1 < hash1->Jogo->score2)
      {
        ++hash2->vitorias;
        --hash3->vitorias;
      }
      else
      {
        if (hash1->Jogo->score1 == hash1->Jogo->score2)
        {
          ++hash2->vitorias;
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (score1 < score2)
      {
        if (hash1->Jogo->score1 > hash1->Jogo->score2)
        {
          --hash2->vitorias;
          ++hash3->vitorias;
        }
        else
        {
          if (hash1->Jogo->score1 == hash1->Jogo->score2)
          {
            ++hash3->vitorias;
          }
          else
          {
            
          }

        }

      }
      else
      {
        if (score1 == score2)
        {
          if (hash1->Jogo->score1 < hash1->Jogo->score2)
          {
            --hash3->vitorias;
          }
          else
          {
            if (hash1->Jogo->score1 > hash1->Jogo->score2)
            {
              --hash2->vitorias;
            }
            else
            {
              
            }

          }

        }
        else
        {
          
        }

      }

    }

    hash1->Jogo->score1 = score1;
    hash1->Jogo->score2 = score2;
  }

}

void adiciona_equipa(link2 *hashtable, int m)
{
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (STsearchE(nome, hashtable, 1009) != 0)
  {
    printf("%d Equipa existente.\n", m);
  }
  else
  {
    STinsertE(nome, hashtable, 1009);
  }

}

void procura_equipa(link2 *hashtable, int m)
{
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (STsearchE(nome, hashtable, 1009) == 0)
  {
    printf("%d Equipa inexistente.\n", m);
  }
  else
  {
    link2 hash = STsearchE(nome, hashtable, 1009);
    printf("%d %s %d\n", m, nome, hash->vitorias);
  }

}

int ordena(const void *a, const void *b)
{
  node2 *x = *((node2 **) a);
  node2 *y = *((node2 **) b);
  return strcmp(x->equipa, y->equipa);
}

void lista_equipas(link2 *hashtable, int m)
{
  int i;
  int n = 0;
  int max_vitorias = 0;
  link2 x;
  link2 a[1009];
  for (i = 0; i < 1009; i++)
  {
    for (x = hashtable[i]; x != 0; x = x->next)
    {
      if (x->vitorias > max_vitorias)
      {
        max_vitorias = x->vitorias;
      }
      else
      {
        
      }

    }

  }

  for (i = 0; i < 1009; i++)
  {
    for (x = hashtable[i]; x != 0; x = x->next)
    {
      if (x->vitorias == max_vitorias)
      {
        a[n] = x;
        ++n;
      }
      else
      {
        
      }

    }

  }

  if (n != 0)
  {
    qsort(a, n, sizeof(node2 *), ordena);
    printf("%d Melhores %d\n", m, max_vitorias);
    for (i = 0; i < n; i++)
    {
      printf("%d * %s\n", m, a[i]->equipa);
    }

  }
  else
  {
    
  }

}

void termina(link1 *hashtable1, link2 *hashtable2, list *lista)
{
  int i;
  link1 w;
  link1 x;
  link2 y;
  link2 z;
  for (i = 0; i < 1009; i++)
  {
    x = hashtable1[i];
    while (x != 0)
    {
      w = x->next;
      free(x->Jogo->nome);
      free(x->Jogo->equipa1);
      free(x->Jogo->equipa2);
      free(x->Jogo);
      free(x);
      x = w;
    }

    y = hashtable2[i];
    while (y != 0)
    {
      z = y->next;
      free(y->equipa);
      free(y);
      y = z;
    }

  }

  free_list(lista);
  free(hashtable1);
  free(hashtable2);
}

int main()
{
  char c;
  int NL = 1;
  link2 *hashequipa = STinitE(1009);
  link1 *hashjogo = STinitJ(1009);
  list *lista = mk_list();
  for (;;)
  {
    switch (c = getchar())
    {
      case 'a':
        adiciona_jogo(hashjogo, hashequipa, lista, NL);
        ++NL;
        break;

      case 'l':
        lista_jogos(hashjogo, lista, NL);
        ++NL;
        break;

      case 'p':
        procura_jogo(hashjogo, NL);
        ++NL;
        break;

      case 'r':
        apaga_jogo(hashjogo, hashequipa, lista, NL);
        ++NL;
        break;

      case 's':
        altera_score(hashjogo, hashequipa, NL);
        ++NL;
        break;

      case 'A':
        adiciona_equipa(hashequipa, NL);
        ++NL;
        break;

      case 'P':
        procura_equipa(hashequipa, NL);
        ++NL;
        break;

      case 'g':
        lista_equipas(hashequipa, NL);
        ++NL;
        break;

      case 'x':
        termina(hashjogo, hashequipa, lista);
        return 0;
        break;

    }

  }

  return 0;
}
