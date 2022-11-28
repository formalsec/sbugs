#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "hashtable.h"


unsigned int hash(char *nome)
{
  int comprimento = strlen(nome);
  int chave = 0;
  int i;
  for (i = 0; i < comprimento; i++)
  {
    chave = chave + nome[i];
    chave = (chave * nome[i]) % 10007;
  }

  return chave;
}

void init_hashtable(Item **hashtable)
{
  int i;
  for (i = 0; i < 10007; i++)
  {
    hashtable[i] = 0;
  }

}

void insere_hashtable(Item *item, Item **hashtable)
{
  int chave = hash(item->nome);
  if (!hashtable[chave])
  {
    hashtable[chave] = item;
  }
  else
  {
    item->next_hash = hashtable[chave];
    hashtable[chave] = item;
  }

}

Item *procura_item(char *nome, Item **hashtable)
{
  int chave = hash(nome);
  Item *item;
  item = hashtable[chave];
  if (!item)
  {
    return 0;
  }
  else
  {
    while (item)
    {
      if (strcmp(item->nome, nome) == 0)
      {
        return item;
      }
      else
      {
        
      }

      item = item->next_hash;
    }

    return 0;
  }

}

Item *equipa_vencedora(Item **hashtable, Item *jogo)
{
  if (jogo->score1 > jogo->score2)
  {
    return procura_item(jogo->equipa1, hashtable);
  }
  else
  {
    return procura_item(jogo->equipa2, hashtable);
  }

}

void adiciona_vitoria(Item **hashtable, Item *jogo)
{
  if (jogo->score1 != jogo->score2)
  {
    Item *vencedor = equipa_vencedora(hashtable, jogo);
    vencedor->vitorias++;
  }
  else
  {
    
  }

}

void retira_vitoria(Item **hashtable, Item *jogo)
{
  if (jogo->score1 != jogo->score2)
  {
    Item *vencedor = equipa_vencedora(hashtable, jogo);
    vencedor->vitorias--;
  }
  else
  {
    
  }

}

int apaga_jogo(char *nome, Item **hashtable_jogo, Item **hashtable_equipa, lista_jogo *lst_jogo)
{
  int chave = hash(nome);
  int cont = 0;
  Item *jogo = hashtable_jogo[chave];
  Item *anterior;
  if (!jogo)
  {
    return 0;
  }
  else
  {
    
  }

  while (jogo)
  {
    cont++;
    if (strcmp(nome, jogo->nome) == 0)
    {
      retira_vitoria(hashtable_equipa, jogo);
      if ((!jogo->next_hash) && (cont == 1))
      {
        hashtable_jogo[chave] = 0;
      }
      else
      {
        if (jogo == hashtable_jogo[chave])
        {
          hashtable_jogo[chave] = jogo->next_hash;
        }
        else
        {
          anterior->next_hash = jogo->next_hash;
        }

      }

      if (jogo == lst_jogo->head)
      {
        lst_jogo->head = jogo->next;
      }
      else
      {
        jogo->prev->next = jogo->next;
      }

      if (jogo == lst_jogo->last)
      {
        lst_jogo->last = jogo->prev;
      }
      else
      {
        jogo->next->prev = jogo->prev;
      }

      free(jogo->nome);
      free(jogo->equipa1);
      free(jogo->equipa2);
      free(jogo);
      return 1;
    }
    else
    {
      
    }

    anterior = jogo;
    jogo = jogo->next_hash;
  }

  return 0;
}
