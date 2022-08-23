/*File generated by PreProcessor.py*/


#include "linkedlist.h"


void printlist_equipa(int cont, int vitorias, node_equipa *head)
{
  node_equipa *tmp = head;
  while ((tmp != 0) && (tmp->vitorias == vitorias))
  {
    printf("%d * %s\n", cont, tmp->nome);
    tmp = tmp->next;
  }

}

void printlist_jogo(node_jogo *head, int cont)
{
  node_jogo *tmp = head;
  while (tmp != 0)
  {
    printf("%d %s %s %s %d %d\n", cont, tmp->nome, tmp->t1, tmp->t2, tmp->s1, tmp->s2);
    tmp = tmp->next_list;
  }

}

node_jogo *cria_node_jg(char *nome, char *t1, char *t2, int s1, int s2)
{
  node_jogo *resultado = malloc(sizeof(node_jogo));
  resultado->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(resultado->nome, nome);
  resultado->t1 = malloc((sizeof(char)) * (strlen(t1) + 1));
  strcpy(resultado->t1, t1);
  resultado->t2 = malloc((sizeof(char)) * (strlen(t2) + 1));
  strcpy(resultado->t2, t2);
  resultado->s1 = s1;
  resultado->s2 = s2;
  resultado->next = 0;
  resultado->next_list = 0;
  resultado->prev_list = 0;
  return resultado;
}

node_equipa *cria_node_eq(char *nome)
{
  node_equipa *resultado = malloc(sizeof(node_equipa));
  resultado->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(resultado->nome, nome);
  resultado->vitorias = 0;
  resultado->next = 0;
  return resultado;
}

node_jogo *insere_jogo_lista(node_jogo *head, node_jogo *jogo)
{
  node_jogo *tmp = head;
  if (tmp == 0)
  {
    return head = jogo;
  }
  else
  {
    
  }

  while (tmp->next != 0)
  {
    tmp = tmp->next;
  }

  tmp->next = jogo;
  return head;
}

node_jogo *_insere_jogo_lista(node_jogo *head, node_jogo *jogo, node_jogo **last)
{
  if (head == 0)
  {
    {
      *last = jogo;
      return head = jogo;
    }
  }
  else
  {
    
  }

  (*last)->next_list = jogo;
  jogo->prev_list = *last;
  *last = jogo;
  return head;
}

node_equipa *insere_equipa_lista(node_equipa *head, node_equipa *equipa)
{
  node_equipa *tmp = head;
  if (tmp == 0)
  {
    return head = equipa;
  }
  else
  {
    
  }

  while (tmp->next != 0)
  {
    tmp = tmp->next;
  }

  tmp->next = equipa;
  return head;
}

node_equipa *encontra_listnode_eq(node_equipa *head, char *nome)
{
  node_equipa *tmp = head;
  while (tmp != 0)
  {
    if (strcmp(tmp->nome, nome) == 0)
    {
      return tmp;
    }
    else
    {
      
    }

    tmp = tmp->next;
  }

  return 0;
}

node_jogo *encontra_listnode_jg(node_jogo *head, char *nome)
{
  node_jogo *tmp = head;
  while (tmp != 0)
  {
    if (strcmp(tmp->nome, nome) == 0)
    {
      return tmp;
    }
    else
    {
      
    }

    tmp = tmp->next;
  }

  return 0;
}

void free_node_eq(node_equipa *node)
{
  free(node->nome);
  free(node);
}

void free_node_jg(node_jogo *node)
{
  free(node->nome);
  free(node->t1);
  free(node->t2);
  free(node);
}

node_jogo *delete_node_list(node_jogo *head, char *nome)
{
  node_jogo *tmp = head;
  node_jogo *prev;
  if ((tmp != 0) && (strcmp(tmp->nome, nome) == 0))
  {
    {
      head = tmp->next;
      free_node_jg(tmp);
      return head;
    }
  }
  else
  {
    
  }

  while ((tmp != 0) && (strcmp(tmp->nome, nome) != 0))
  {
    prev = tmp;
    tmp = tmp->next;
  }

  if (tmp == 0)
  {
    return head;
  }
  else
  {
    
  }

  prev->next = tmp->next;
  free_node_jg(tmp);
  return head;
}

node_jogo *remove_node_list(node_jogo *head, node_jogo *jogo, node_jogo **last)
{
  node_jogo *tmp = head;
  if ((*last) == jogo)
  {
    *last = jogo->prev_list;
  }
  else
  {
    
  }

  if (tmp == jogo)
  {
    {
      head = tmp->next_list;
    }
  }
  else
  {
    
  }

  if (jogo->next_list != 0)
  {
    {
      jogo->next_list->prev_list = jogo->prev_list;
    }
  }
  else
  {
    
  }

  if (jogo->prev_list != 0)
  {
    {
      jogo->prev_list->next_list = jogo->next_list;
    }
  }
  else
  {
    
  }

  return head;
}

void destroy_list_eq(node_equipa *head)
{
  node_equipa *tmp;
  while (head != 0)
  {
    tmp = head;
    head = head->next;
    free_node_eq(tmp);
  }

  free(head);
}

void destroy_list_jg(node_jogo *head)
{
  node_jogo *tmp;
  while (head != 0)
  {
    tmp = head;
    head = head->next;
    free_node_jg(tmp);
  }

  free(head);
}

int compara(const void *a, const void *b)
{
  const char **ia = (const char **) a;
  const char **ib = (const char **) b;
  return strcmp(*ia, *ib);
}

