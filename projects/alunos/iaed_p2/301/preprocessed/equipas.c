#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "structs.h"
#include <string.h>
#include <stdio.h>


NodeEq *adicionaEquipas(NodeEq *headEq, Hash_tableEq *equipasT, int nl)
{
  int h;
  int len;
  Hash_nodeEq *node;
  NodeEq *novaEquipa;
  char buffer[1024];
  char *aux_string;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  len = strlen(buffer) + 1;
  aux_string = (char *) malloc((sizeof(char)) * len);
  strcpy(aux_string, buffer);
  h = hash(aux_string, equipasT->capacity);
  node = equipasT->table[h];
  while (node != 0)
  {
    if (!strcmp(node->equipa->nome, aux_string))
    {
      printf("%d Equipa existente.\n", nl);
      free(aux_string);
      return headEq;
    }
    else
    {
      
    }

    node = node->next;
  }

  novaEquipa = (NodeEq *) malloc(sizeof(NodeEq));
  novaEquipa->nome = (char *) malloc((sizeof(char)) * len);
  strcpy(novaEquipa->nome, aux_string);
  novaEquipa->vitorias = 0;
  novaEquipa->next = headEq;
  headEq = novaEquipa;
  insertEquipa_T(equipasT, headEq);
  free(aux_string);
  return headEq;
}

void listaEquipas(NodeEq *head)
{
  if (head == 0)
  {
    return;
  }
  else
  {
    
  }

  listaEquipas(head->next);
  printf("%s %d\n", head->nome, head->vitorias);
}

void procuraEquipa(Hash_tableEq *equipasT, int nl)
{
  int h;
  int len;
  Hash_nodeEq *node;
  char buffer[1024];
  char *ptr_buffer;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  len = strlen(buffer) + 1;
  ptr_buffer = (char *) malloc((sizeof(char)) * len);
  strcpy(ptr_buffer, buffer);
  h = hash(ptr_buffer, equipasT->capacity);
  node = equipasT->table[h];
  while (node != 0)
  {
    if (!strcmp(node->equipa->nome, ptr_buffer))
    {
      printf("%d %s %d\n", nl, node->equipa->nome, node->equipa->vitorias);
      free(ptr_buffer);
      return;
    }
    else
    {
      
    }

    node = node->next;
  }

  printf("%d Equipa inexistente.\n", nl);
  free(ptr_buffer);
}

