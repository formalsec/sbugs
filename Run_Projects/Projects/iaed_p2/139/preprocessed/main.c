/*File generated by PreProcessor.py*/


#include "main.h"


int main()
{
  HashTable jogos = HASHinit(1000);
  HashTable equipas = HASHinit(1000);
  LinkedList jogos_list = list_init();
  LinkedList equipas_list = list_init();
  int NL = 0;
  while (1)
  {
    char comando;
    NL++;
    switch (comando = getchar())
    {
      case 'a':
        a(jogos, equipas, jogos_list, NL);
        break;

      case 'A':
        A(equipas, equipas_list, NL);
        break;

      case 'l':
        getchar();
        l(jogos_list, NL);
        break;

      case 'p':
        p(jogos, NL);
        break;

      case 'P':
        P(equipas, NL);
        break;

      case 'r':
        r(jogos, equipas, jogos_list, NL);
        break;

      case 's':
        s(jogos, equipas, NL);
        break;

      case 'g':
        getchar();
        g(equipas_list, NL);
        break;

      case 'x':
        destroy_hash(equipas);
        destroy_hash(jogos);
        destroy_list_nodes(jogos_list);
        destroy_list_nodes(equipas_list);
        return 0;

    }

  }

  return 1;
}

void a(HashTable jogos, HashTable equipas, LinkedList jogos_list, int NL)
{
  Jogo *j;
  Item new;
  char buffer[1024];
  char buffer1[1024];
  char buffer2[1024];
  int score1;
  int score2;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  for (int buffer1_index = 0; buffer1_index < 10; buffer1_index++)
  {
    buffer1[buffer1_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer1[10 - 1] = '\0';
  for (int buffer2_index = 0; buffer2_index < 10; buffer2_index++)
  {
    buffer2[buffer2_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (search(jogos, buffer))
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    if ((!search(equipas, buffer1)) || (!search(equipas, buffer2)))
    {
      printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
      j = malloc(sizeof(Jogo));
      j->nome = strdup(buffer);
      j->equipa1 = strdup(buffer1);
      j->equipa2 = strdup(buffer2);
      j->score1 = score1;
      j->score2 = score2;
      new = newItem(JOGO, j);
      insert(jogos, new);
      append(jogos_list, new);
      if (score1 > score2)
      {
        atualiza_score(equipas, buffer1, 1);
      }
      else
      {
        if (score2 > score1)
        {
          atualiza_score(equipas, buffer2, 1);
        }
        else
        {
          
        }

      }

    }

  }

}

void A(HashTable equipas, LinkedList equipas_list, int NL)
{
  Item new;
  Equipa *e;
  char buffer[1024];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  if (search(equipas, buffer))
  {
    printf("%d Equipa existente.\n", NL);
  }
  else
  {
    e = malloc(sizeof(Equipa));
    e->nome = strdup(buffer);
    e->jogos_ganhos = 0;
    new = newItem(EQUIPA, e);
    insert(equipas, new);
    append(equipas_list, new);
  }

}

void l(LinkedList jogos_list, int NL)
{
  Jogo *j;
  Link atual;
  if (!is_empty(jogos_list))
  {
    for (atual = jogos_list->head; atual != 0; atual = atual->next)
    {
      j = atual->item->data.jogo;
      printf("%d %s %s %s %d %d\n", NL, j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
    }

  }
  else
  {
    
  }

}

void p(HashTable jogos, int NL)
{
  Jogo *j;
  char buffer[1024];
  Item jogo_item;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  jogo_item = search(jogos, buffer);
  if (jogo_item)
  {
    j = jogo_item->data.jogo;
    printf("%d %s %s %s %d %d\n", NL, buffer, j->equipa1, j->equipa2, j->score1, j->score2);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void P(HashTable equipas, int NL)
{
  char buffer[1024];
  Item equipa_node;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  equipa_node = search(equipas, buffer);
  if (equipa_node)
  {
    printf("%d %s %d\n", NL, buffer, equipa_node->data.equipa->jogos_ganhos);
  }
  else
  {
    printf("%d Equipa inexistente.\n", NL);
  }

}

void r(HashTable jogos, HashTable equipas, LinkedList jogos_list, int NL)
{
  char buffer[1024];
  char *vencedor;
  Jogo *jogo;
  Item jogo_item;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  jogo_item = search(jogos, buffer);
  if (jogo_item)
  {
    jogo = jogo_item->data.jogo;
    if (encontra_vencedor(jogo))
    {
      vencedor = strdup(encontra_vencedor(jogo));
    }
    else
    {
      vencedor = 0;
    }

    destroy_list_node(jogos_list, buffer);
    delete(jogos, buffer);
    if (vencedor)
    {
      atualiza_score(equipas, vencedor, -1);
    }
    else
    {
      
    }

    free(vencedor);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void s(HashTable jogos, HashTable equipas, int NL)
{
  char buffer[1024];
  Key nome;
  Key vencedor;
  Key vencedor_apos_update;
  int score1;
  int score2;
  Item jogo_item;
  Jogo *jogo;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  nome = strdup(buffer);
  jogo_item = search(jogos, buffer);
  if (jogo_item)
  {
    jogo = jogo_item->data.jogo;
    vencedor = encontra_vencedor(jogo);
    jogo->score1 = score1;
    jogo->score2 = score2;
    vencedor_apos_update = encontra_vencedor(jogo);
    if (vencedor && vencedor_apos_update)
    {
      if (strcmp(vencedor, vencedor_apos_update) != 0)
      {
        atualiza_score(equipas, vencedor_apos_update, 1);
        atualiza_score(equipas, vencedor, -1);
      }
      else
      {
        
      }

    }
    else
    {
      if (vencedor && (!vencedor_apos_update))
      {
        atualiza_score(equipas, vencedor, -1);
      }
      else
      {
        if ((!vencedor) && vencedor_apos_update)
        {
          atualiza_score(equipas, vencedor_apos_update, 1);
        }
        else
        {
          
        }

      }

    }

  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

  free(nome);
}

void g(LinkedList equipas_list, int NL)
{
  int max;
  Item e;
  Link atual;
  LinkedList sortedMaxEquipas;
  sortedMaxEquipas = findMaxVitorias(equipas_list);
  if (!is_empty(sortedMaxEquipas))
  {
    max = get_first_item(sortedMaxEquipas)->data.equipa->jogos_ganhos;
    printf("%d Melhores %d\n", NL, max);
    for (atual = sortedMaxEquipas->head; atual != 0; atual = atual->next)
    {
      e = atual->item;
      printf("%d * %s\n", NL, e->value);
    }

  }
  else
  {
    
  }

  destroy_list_nodes(sortedMaxEquipas);
}

LinkedList findMaxVitorias(LinkedList equipas)
{
  Link current;
  int aux;
  LinkedList maxEquipas = list_init();
  int max = -1;
  for (current = equipas->head; current; current = current->next)
  {
    aux = current->item->data.equipa->jogos_ganhos;
    if (aux > max)
    {
      max = aux;
      destroy_list_nodes(maxEquipas);
      maxEquipas = list_init();
      insertInOrder(maxEquipas, current->item);
    }
    else
    {
      if (aux == max)
      {
        insertInOrder(maxEquipas, current->item);
      }
      else
      {
        
      }

    }

  }

  return maxEquipas;
}

void atualiza_score(HashTable equipas, Key equipa, int change)
{
  Equipa *e;
  Item item;
  item = search(equipas, equipa);
  e = item->data.equipa;
  e->jogos_ganhos += change;
}

char *encontra_vencedor(Jogo *jogo)
{
  if (jogo->score1 > jogo->score2)
  {
    return jogo->equipa1;
  }
  else
  {
    if (jogo->score2 > jogo->score1)
    {
      return jogo->equipa2;
    }
    else
    {
      
    }

  }

  return 0;
}
