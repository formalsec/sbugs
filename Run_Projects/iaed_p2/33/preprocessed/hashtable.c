/*File generated by PreProcessor.py*/


#include "hashtable.h"


int hash(char *str)
{
  int chave;
  for (chave = 0; (*str) != '\0'; str++)
    chave = (((chave << 2) + chave) + (*str)) % 997;

  return chave;
}

void ht_init(Hashtable *ht)
{
  int i;
  *ht = (Hashtable) malloc(sizeof(struct hashtable_str));
  (*ht)->heads = (ht_link *) malloc((sizeof(ht_link)) * 997);
  for (i = 0; i < 997; i++)
    (*ht)->heads[i] = 0;

}

ht_link ht_cria(lst_link lst)
{
  ht_link link = (ht_link) malloc(sizeof(struct ht_node));
  link->lst = lst;
  return link;
}

ht_link ht_verifica(char *nome, Hashtable ht, int opcao, int NL)
{
  ht_link link = ht_procura(nome, ht);
  if ((opcao == 0) && (link == 0))
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    if ((opcao == 1) && (!(link == 0)))
    {
      printf("%d Jogo existente.\n", NL);
    }
    else
    {
      
    }

  }

  return link;
}

ht_link ht_procura(char *nome, Hashtable ht)
{
  int i;
  ht_link link;
  i = hash(nome);
  link = ht->heads[i];
  while (link != 0)
  {
    if (strcmp(link->lst->jogo->nome, nome) == 0)
    {
      return link;
    }
    else
    {
      
    }

    link = link->next;
  }

  return link;
}

void ht_insere(lst_link lst, Hashtable ht)
{
  int i;
  ht_link link;
  i = hash(lst->jogo->nome);
  link = ht_cria(lst);
  link->next = ht->heads[i];
  ht->heads[i] = link;
}

void ht_remove(ht_link link, Lista lst, Hashtable ht)
{
  int i;
  ht_link x;
  i = hash(link->lst->jogo->nome);
  if (ht->heads[i] == link)
  {
    ht->heads[i] = link->next;
  }
  else
  {
    {
      x = ht->heads[i];
      while (!(x->next == link))
        x = x->next;

      x->next = link->next;
    }
  }

  lst_remove(link->lst, lst);
  free(link);
}

void ht_free(Hashtable ht)
{
  int i;
  ht_link x;
  for (i = 0; i < 997; i++)
    while (!(ht->heads[i] == 0))
  {
    x = ht->heads[i];
    ht->heads[i] = x->next;
    lst_node_free(x->lst);
    free(x);
  }


  free(ht->heads);
  free(ht);
}
