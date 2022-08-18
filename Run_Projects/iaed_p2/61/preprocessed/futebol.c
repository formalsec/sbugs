/*File generated by PreProcessor.py*/


#include "futebol.h"


struct _equipa
{
  char *nome_equipa;
  int score;
};
struct _jogo
{
  char *nome_jogo;
  equipa *eq1;
  equipa *eq2;
  int sc1;
  int sc2;
};
ptr_jogo procurajogo(hashtable *hjogos, char *nome)
{
  ptr_jogo procura;
  link node_aux;
  list *l;
  l = lehash(hjogos, nome);
  if (l == 0)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  node_aux = headlista(l);
  while (node_aux != 0)
  {
    procura = (ptr_jogo) lenode(node_aux);
    if (!strcmp(procura->nome_jogo, nome))
    {
      {
        return procura;
      }
    }
    else
    {
      
    }

    node_aux = nextnode(node_aux);
  }

  return 0;
}

ptr_equipa procuraequipa(hashtable *hequipas, char *nome)
{
  ptr_equipa procura;
  link node_aux;
  list *l;
  l = lehash(hequipas, nome);
  if (l == 0)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  node_aux = headlista(l);
  while (node_aux != 0)
  {
    procura = (ptr_equipa) lenode(node_aux);
    if (!strcmp(procura->nome_equipa, nome))
    {
      {
        return procura;
      }
    }
    else
    {
      
    }

    node_aux = nextnode(node_aux);
  }

  return 0;
}

void adiciona_jogo(char *nome, char *eq1, char *eq2, int sc1, int sc2, hashtable *hequipas, hashtable *hjogos, list *ljogos, int NL)
{
  ptr_jogo j;
  ptr_equipa e1;
  ptr_equipa e2;
  if (procurajogo(hjogos, nome) != 0)
  {
    {
      printf("%d Jogo existente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  e1 = procuraequipa(hequipas, eq1);
  e2 = procuraequipa(hequipas, eq2);
  if ((e1 == 0) || (e2 == 0))
  {
    {
      printf("%d Equipa inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  j = (ptr_jogo) malloc(sizeof(jogo));
  j->nome_jogo = (char *) malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(j->nome_jogo, nome);
  j->eq1 = e1;
  j->eq2 = e2;
  j->sc1 = sc1;
  j->sc2 = sc2;
  if (sc1 > sc2)
  {
    {
      e1->score += 1;
    }
  }
  else
  {
    
  }

  if (sc2 > sc1)
  {
    {
      e2->score += 1;
    }
  }
  else
  {
    
  }

  adicionalista(ljogos, (Item) j);
  inserehash(hjogos, (Item) j, nome);
  return;
}

void lista_jogos(list *ljogos, int NL)
{
  link node_aux;
  ptr_jogo elemento;
  node_aux = headlista(ljogos);
  while (node_aux != 0)
  {
    elemento = (ptr_jogo) lenode(node_aux);
    printf("%d %s %s %s %d %d\n", NL, elemento->nome_jogo, elemento->eq1->nome_equipa, elemento->eq2->nome_equipa, elemento->sc1, elemento->sc2);
    node_aux = nextnode(node_aux);
  }

  return;
}

void procura_jogo(hashtable *hjogos, char *nome, int NL)
{
  ptr_jogo jogo_encontrar;
  jogo_encontrar = procurajogo(hjogos, nome);
  if (jogo_encontrar == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  printf("%d %s %s %s %d %d\n", NL, jogo_encontrar->nome_jogo, jogo_encontrar->eq1->nome_equipa, jogo_encontrar->eq2->nome_equipa, jogo_encontrar->sc1, jogo_encontrar->sc2);
  return;
}

void apaga_jogo(hashtable *hjogos, list *ljogos, char *nome, int NL)
{
  ptr_jogo jogo_eliminar;
  jogo_eliminar = procurajogo(hjogos, nome);
  if (jogo_eliminar == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  if (jogo_eliminar->sc1 > jogo_eliminar->sc2)
  {
    {
      jogo_eliminar->eq1->score -= 1;
    }
  }
  else
  {
    
  }

  if (jogo_eliminar->sc2 > jogo_eliminar->sc1)
  {
    {
      jogo_eliminar->eq2->score -= 1;
    }
  }
  else
  {
    
  }

  removehash(hjogos, (Item) jogo_eliminar, nome);
  removelista(ljogos, (Item) jogo_eliminar);
  freejogo(jogo_eliminar);
  return;
}

void altera_score(hashtable *hjogos, char *nome, int newsc1, int newsc2, int NL)
{
  ptr_jogo jogo_mudar;
  jogo_mudar = procurajogo(hjogos, nome);
  if (jogo_mudar == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  if (newsc1 > newsc2)
  {
    {
      if (jogo_mudar->sc2 > jogo_mudar->sc1)
      {
        {
          jogo_mudar->eq2->score -= 1;
          jogo_mudar->eq1->score += 1;
        }
      }
      else
      {
        
      }

      if (jogo_mudar->sc1 == jogo_mudar->sc2)
      {
        {
          jogo_mudar->eq1->score += 1;
        }
      }
      else
      {
        
      }

    }
  }
  else
  {
    
  }

  if (newsc2 > newsc1)
  {
    {
      if (jogo_mudar->sc1 > jogo_mudar->sc2)
      {
        {
          jogo_mudar->eq1->score -= 1;
          jogo_mudar->eq2->score += 1;
        }
      }
      else
      {
        
      }

      if (jogo_mudar->sc1 == jogo_mudar->sc2)
      {
        {
          jogo_mudar->eq2->score += 1;
        }
      }
      else
      {
        
      }

    }
  }
  else
  {
    
  }

  if (newsc2 == newsc1)
  {
    {
      if (jogo_mudar->sc1 > jogo_mudar->sc2)
      {
        {
          jogo_mudar->eq1->score -= 1;
        }
      }
      else
      {
        
      }

      if (jogo_mudar->sc2 > jogo_mudar->sc1)
      {
        {
          jogo_mudar->eq2->score -= 1;
        }
      }
      else
      {
        
      }

    }
  }
  else
  {
    
  }

  jogo_mudar->sc1 = newsc1;
  jogo_mudar->sc2 = newsc2;
  return;
}

void adiciona_equipa(char *nome, hashtable *hequipas, int NL)
{
  ptr_equipa e;
  if (procuraequipa(hequipas, nome) != 0)
  {
    {
      printf("%d Equipa existente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  e = (ptr_equipa) malloc(sizeof(equipa));
  e->nome_equipa = (char *) malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(e->nome_equipa, nome);
  e->score = 0;
  inserehash(hequipas, (Item) e, nome);
  return;
}

void procura_equipa(hashtable *hequipas, char *nome, int NL)
{
  ptr_equipa equipa_encontrar;
  equipa_encontrar = procuraequipa(hequipas, nome);
  if (equipa_encontrar == 0)
  {
    {
      printf("%d Equipa inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  printf("%d %s %d\n", NL, equipa_encontrar->nome_equipa, equipa_encontrar->score);
  return;
}

void freejogo(Item _item)
{
  ptr_jogo j;
  j = (ptr_jogo) _item;
  free(j->nome_jogo);
  free(j);
}

void freeequipa(Item _item)
{
  ptr_equipa e;
  e = (ptr_equipa) _item;
  free(e->nome_equipa);
  free(e);
}

void mais_vitorias(hashtable *hequipas, int M, int NL)
{
  list *ptr_lista;
  link ptr_node;
  ptr_equipa eq;
  list *vitorias;
  nodetree *arvore = 0;
  char *item_tree;
  int i;
  int max;
  max = 0;
  vitorias = crialista();
  for (i = 0; i < M; i++)
  {
    ptr_lista = indice_hastable(hequipas, i);
    if (ptr_lista == 0)
    {
      {
        continue;
      }
    }
    else
    {
      
    }

    for (ptr_node = headlista(ptr_lista); ptr_node != 0; ptr_node = nextnode(ptr_node))
    {
      eq = (ptr_equipa) lenode(ptr_node);
      if (max > eq->score)
      {
        {
          continue;
        }
      }
      else
      {
        
      }

      if (max == eq->score)
      {
        {
          adicionalista(vitorias, (Item) eq->nome_equipa);
          continue;
        }
      }
      else
      {
        
      }

      if (max < eq->score)
      {
        {
          max = eq->score;
          freelista(vitorias, 0, free);
          vitorias = crialista();
          adicionalista(vitorias, (Item) eq->nome_equipa);
          continue;
        }
      }
      else
      {
        
      }

    }

  }

  if (lista_vazia(vitorias))
  {
    {
      free(vitorias);
      return;
    }
  }
  else
  {
    
  }

  printf("%d Melhores %d\n", NL, max);
  for (ptr_node = headlista(vitorias); ptr_node != 0; ptr_node = nextnode(ptr_node))
  {
    item_tree = (char *) lenode(ptr_node);
    arvore = insere_tree(arvore, item_tree);
  }

  imprime_eq_vitorias(arvore, NL);
  freelista(vitorias, 0, free);
  return;
}

void imprime_eq_vitorias(nodetree *nt, int NL)
{
  if (nt != 0)
  {
    {
      imprime_eq_vitorias(nodetree_left(nt), NL);
      printf("%d * %s\n", NL, nodetree_item(nt));
      imprime_eq_vitorias(nodetree_right(nt), NL);
      free(nt);
    }
  }
  else
  {
    
  }

}

