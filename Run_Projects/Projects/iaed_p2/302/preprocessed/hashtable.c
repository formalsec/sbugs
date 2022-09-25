/*File generated by PreProcessor.py*/


#include "hashtable.h"


size_t hash(const char *s, size_t capacidade)
{
  int i;
  int valor = 0;
  int len = strlen(s);
  for (i = 0; i < len; i++)
  {
    valor = (valor * 29) + s[i];
  }

  return valor % capacidade;
}

hash_table_jogo *mk_hash_table_jg(int capacidade)
{
  hash_table_jogo *rv = malloc(sizeof(hash_table_jogo));
  rv->capacidade = capacidade;
  rv->tb = calloc(rv->capacidade, sizeof(node_jogo *));
  rv->last = 0;
  return rv;
}

hash_table_equipa *mk_hash_table_eq(int capacidade)
{
  hash_table_equipa *rv = malloc(sizeof(hash_table_jogo));
  rv->capacidade = capacidade;
  rv->tb = calloc(rv->capacidade, sizeof(node_equipa *));
  return rv;
}

void insere_jogo_hash(hash_table_jogo *table, node_jogo *jogo)
{
  size_t i = hash(jogo->nome, table->capacidade);
  if (jogo == 0)
  {
    return;
  }
  else
  {
    
  }

  table->tb[i] = insere_jogo_lista(table->tb[i], jogo);
}

void insere_eq_hash(hash_table_equipa *table, node_equipa *equipa)
{
  size_t i = hash(equipa->nome, table->capacidade);
  if (equipa == 0)
  {
    return;
  }
  else
  {
    
  }

  table->tb[i] = insere_equipa_lista(table->tb[i], equipa);
}

node_jogo *encontra_hash_jg(hash_table_jogo *table, char *nome)
{
  size_t i = hash(nome, table->capacidade);
  node_jogo *tmp;
  if (table->tb[i] != 0)
  {
    tmp = encontra_listnode_jg(table->tb[i], nome);
    if (tmp != 0)
    {
      return tmp;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

  return 0;
}

node_equipa *encontra_hash_eq(hash_table_equipa *table, char *nome)
{
  size_t i = hash(nome, table->capacidade);
  node_equipa *tmp;
  if (table->tb[i] != 0)
  {
    tmp = encontra_listnode_eq(table->tb[i], nome);
    if (tmp != 0)
    {
      return tmp;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

  return 0;
}

void remove_jogo_hash(hash_table_jogo *table, char *nome)
{
  size_t i = hash(nome, table->capacidade);
  int cont = 0;
  node_jogo *tmp;
  if (table->tb[i] != 0)
  {
    tmp = table->tb[i];
    while (tmp != 0)
    {
      if (cont == 1)
      {
        table->tb[i] = delete_node_list(table->tb[i], nome);
        return;
      }
      else
      {
        
      }

      tmp = tmp->next;
      cont++;
    }

    tmp = encontra_listnode_jg(table->tb[i], nome);
    if (tmp != 0)
    {
      table->tb[i] = delete_node_list(table->tb[i], nome);
      table->tb[i] = 0;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

}

void free_hashtable_jg(hash_table_jogo *table)
{
  size_t i;
  for (i = 0; i < table->capacidade; i++)
  {
    destroy_list_jg(table->tb[i]);
  }

  free(table->tb);
  free(table);
}

void free_hashtable_eq(hash_table_equipa *table)
{
  size_t i;
  for (i = 0; i < table->capacidade; i++)
  {
    destroy_list_eq(table->tb[i]);
  }

  free(table->tb);
  free(table);
}

void diminui_vitorias(node_equipa *hash_eq)
{
  hash_eq->vitorias--;
}

void aumenta_vitorias(node_equipa *hash_eq)
{
  hash_eq->vitorias++;
}

