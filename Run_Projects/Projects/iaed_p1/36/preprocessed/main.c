/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "dlist.h"


void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int *arr, int low, int high, produto *lista)
{
  int pivot = arr[high];
  int i = low - 1;
  int j;
  for (j = low; j <= (high - 1); j++)
  {
    if (strcmp(lista[arr[j]].descricao, lista[pivot].descricao) < 0)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
    else
    {
      
    }

    if ((strcmp(lista[arr[j]].descricao, lista[pivot].descricao) == 0) && (lista[arr[j]].id < lista[pivot].id))
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
    else
    {
      
    }

  }

  swap(&arr[i + 1], &arr[high]);
  return i + 1;
}

void quickSort(int *arr, int low, int high, produto *lista)
{
  if (low < high)
  {
    int pi = partition(arr, low, high, lista);
    quickSort(arr, low, pi - 1, lista);
    quickSort(arr, pi + 1, high, lista);
  }
  else
  {
    
  }

}

void merge(produto *lista, int left, int med, int right)
{
  int i;
  int j;
  int k;
  int s1 = (med - left) + 1;
  int s2 = right - med;
  produto arr1[10000];
  produto arr2[10000];
  for (i = 0; i < s1; i++)
  {
    arr1[i] = lista[left + i];
  }

  for (j = 0; j < s2; j++)
  {
    arr2[j] = lista[(med + 1) + j];
  }

  i = 0;
  j = 0;
  k = left;
  while ((i < s1) && (j < s2))
  {
    if (arr1[i].preco <= arr2[j].preco)
    {
      lista[k] = arr1[i];
      i++;
    }
    else
    {
      lista[k] = arr2[j];
      j++;
    }

    k++;
  }

  while (i < s1)
  {
    lista[k] = arr1[i];
    i++;
    k++;
  }

  while (j < s2)
  {
    lista[k] = arr2[j];
    j++;
    k++;
  }

}

void merge_sort(produto *lista, int left, int right)
{
  if (left < right)
  {
    int med = left + ((right - left) / 2);
    merge_sort(lista, left, med);
    merge_sort(lista, med + 1, right);
    merge(lista, left, med, right);
  }
  else
  {
    
  }

}

produto command_a(char *des, char *preco, char *peso, char *qtd, int id)
{
  int _preco = atoi(preco);
  int _peso = atoi(peso);
  int _qtd = atoi(qtd);
  produto prod;
  strcpy(prod.descricao, des);
  prod.id = id;
  prod.peso = _peso;
  prod.preco = _preco;
  prod.qtd = _qtd;
  prod.encomendado = 0;
  prod.head = 0;
  printf("Novo produto %d.\n", id);
  return prod;
}

void command_q(char *idp, char *qtd, produto *lista, int id)
{
  int _idp = atoi(idp);
  int _qtd = atoi(qtd);
  if (_idp >= id)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", _idp);
    return;
  }
  else
  {
    
  }

  lista[_idp].qtd += _qtd;
}

encomenda command_N(int id)
{
  encomenda enc;
  enc.id = id;
  enc.peso = 0;
  enc.head = 0;
  printf("Nova encomenda %d.\n", id);
  return enc;
}

void command_A(char *ide, char *idp, char *qtd, produto *lista, encomenda *encomendas, int id, int encid)
{
  int _ide = atoi(ide);
  int _idp = atoi(idp);
  int _qtd = atoi(qtd);
  node *p;
  node *p2;
  if (_ide >= encid)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", _idp, _ide);
    return;
  }
  else
  {
    
  }

  if (_idp >= id)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", _idp, _ide);
    return;
  }
  else
  {
    
  }

  if ((lista[_idp].qtd - lista[_idp].encomendado) < _qtd)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", _idp, _ide);
    return;
  }
  else
  {
    
  }

  if ((encomendas[_ide].peso + (lista[_idp].peso * _qtd)) > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", _idp, _ide);
    return;
  }
  else
  {
    
  }

  encomendas[_ide].peso += lista[_idp].peso * _qtd;
  lista[_idp].encomendado += _qtd;
  p = find(encomendas[_ide].head, _idp);
  if (p != 0)
  {
    p->qtd += _qtd;
  }
  else
  {
    p = push(&encomendas[_ide].head, _qtd, _idp);
    p2 = push(&lista[_idp].head, 0, _ide);
    set_connection(p, p2);
  }

}

void command_r(char *idp, char *qtd, produto *lista, int id)
{
  int _idp = atoi(idp);
  int _qtd = atoi(qtd);
  if (_idp >= id)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", _idp);
    return;
  }
  else
  {
    
  }

  if (((lista[_idp].qtd - _qtd) < 0) || (lista[_idp].encomendado > (lista[_idp].qtd - _qtd)))
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", _qtd, _idp);
    return;
  }
  else
  {
    
  }

  lista[_idp].qtd -= _qtd;
}

void command_R(char *ide, char *idp, produto *lista, encomenda *encomendas, int id, int encid)
{
  int _ide = atoi(ide);
  int _idp = atoi(idp);
  node *p;
  if (_ide >= encid)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", _idp, _ide);
    return;
  }
  else
  {
    
  }

  if (_idp >= id)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", _idp, _ide);
    return;
  }
  else
  {
    
  }

  p = find(encomendas[_ide].head, _idp);
  if (p)
  {
    encomendas[_ide].peso -= lista[_idp].peso * p->qtd;
    lista[_idp].encomendado -= p->qtd;
    deleteNode(&lista[_idp].head, p->connection);
    deleteNode(&encomendas[_ide].head, p);
  }
  else
  {
    
  }

}

void command_C(char *ide, produto *lista, encomenda *encomendas, int encid)
{
  int _ide = atoi(ide);
  int val = 0;
  node *current;
  if (_ide >= encid)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", _ide);
    return;
  }
  else
  {
    
  }

  current = encomendas[_ide].head;
  while (current != 0)
  {
    val += lista[current->prodId].preco * current->qtd;
    current = current->next;
  }

  printf("Custo da encomenda %d %d.\n", _ide, val);
}

void command_p(char *idp, char *preco, produto *lista, int id)
{
  int _idp = atoi(idp);
  int _preco = atoi(preco);
  if (_idp >= id)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", _idp);
    return;
  }
  else
  {
    
  }

  lista[_idp].preco = _preco;
}

void command_E(char *ide, char *idp, produto *lista, encomenda *encomendas, int id, int encid)
{
  int _ide = atoi(ide);
  int _idp = atoi(idp);
  node *p;
  if (_ide >= encid)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", _ide);
    return;
  }
  else
  {
    
  }

  if (_idp >= id)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", _idp);
    return;
  }
  else
  {
    
  }

  p = find(encomendas[_ide].head, _idp);
  if (p != 0)
  {
    printf("%s %d.\n", lista[p->prodId].descricao, p->qtd);
  }
  else
  {
    printf("%s 0.\n", lista[_idp].descricao);
  }

}

void command_m(char *idp, produto *lista, int id)
{
  int _idp = atoi(idp);
  int max = -1;
  node *current;
  node *maximum;
  current = lista[_idp].head;
  maximum = 0;
  if (_idp >= id)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", _idp);
    return;
  }
  else
  {
    
  }

  while (current != 0)
  {
    if (current->connection->qtd == max)
    {
      if (current->prodId < maximum->prodId)
      {
        maximum = current;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    if (current->connection->qtd > max)
    {
      max = current->connection->qtd;
      maximum = current;
    }
    else
    {
      
    }

    current = current->next;
  }

  if (max != (-1))
  {
    printf("Maximo produto %d %d %d.\n", _idp, maximum->prodId, max);
  }
  else
  {
    
  }

}

void command_l(produto *lista, int id)
{
  int i;
  produto array[10000];
  for (i = 0; i != id; i++)
  {
    array[i] = lista[i];
  }

  merge_sort(array, 0, id - 1);
  printf("Produtos\n");
  for (i = 0; i != id; i++)
  {
    printf("* %s %d %d\n", array[i].descricao, array[i].preco, array[i].qtd - array[i].encomendado);
  }

}

void command_L(char *ide, produto *lista, encomenda *encomendas, int encid)
{
  int _ide = atoi(ide);
  int array[200];
  node *current;
  int i = 0;
  int n;
  current = encomendas[_ide].head;
  if (_ide >= encid)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", _ide);
    return;
  }
  else
  {
    
  }

  printf("Encomenda %d\n", _ide);
  while (current != 0)
  {
    array[i] = current->prodId;
    i++;
    current = current->next;
  }

  if (encomendas[_ide].head)
  {
    quickSort(array, 0, i - 1, lista);
    for (n = 0; n != i; n++)
      printf("* %s %d %d\n", lista[array[n]].descricao, lista[array[n]].preco, find(lista[array[n]].head, _ide)->connection->qtd);

  }
  else
  {
    
  }

}

void free_lists(produto *lista, encomenda *encomendas, int id, int encid)
{
  int i = 0;
  for (i = 0; i != id; i++)
  {
    free_dlist(lista[i].head);
  }

  for (i = 0; i != encid; i++)
  {
    free_dlist(encomendas[i].head);
  }

}

int main()
{
  char line[1000];
  char token;
  char name[1000];
  char des[64];
  char preco[64];
  char peso[64];
  char qtd[64];
  char idp[64];
  char ide[64];
  char *tok;
  produto lista[10000];
  encomenda encomendas[500];
  produto prod;
  encomenda enc;
  static int id;
  static int encid;
  id = 0;
  encid = 0;
  while (fgets(line, (sizeof(line)) / (sizeof(char)), stdin))
  {
    token = new_sym_var(sizeof(char) * 8);
    for (int name_index = 0; name_index < 10; name_index++)
    {
      name[name_index] = new_sym_var(sizeof(char) * 8);
    }

    name[10 - 1] = '\0';
    if (token == 'x')
    {
      break;
    }
    else
    {
      
    }

    switch (token)
    {
      case 'a':
        tok = strtok(name, ":");
        strcpy(des, tok);
        tok = strtok(0, ":");
        strcpy(preco, tok);
        tok = strtok(0, ":");
        strcpy(peso, tok);
        tok = strtok(0, ":");
        strcpy(qtd, tok);
        tok = strtok(0, ":");
        prod = command_a(des, preco, peso, qtd, id++);
        lista[prod.id] = prod;
        break;

      case 'q':
        tok = strtok(name, ":");
        strcpy(idp, tok);
        tok = strtok(0, ":");
        strcpy(qtd, tok);
        tok = strtok(0, ":");
        command_q(idp, qtd, lista, id);
        break;

      case 'N':
        enc = command_N(encid++);
        encomendas[enc.id] = enc;
        break;

      case 'A':
        tok = strtok(name, ":");
        strcpy(ide, tok);
        tok = strtok(0, ":");
        strcpy(idp, tok);
        tok = strtok(0, ":");
        strcpy(qtd, tok);
        tok = strtok(0, ":");
        command_A(ide, idp, qtd, lista, encomendas, id, encid);
        break;

      case 'r':
        tok = strtok(name, ":");
        strcpy(idp, tok);
        tok = strtok(0, ":");
        strcpy(qtd, tok);
        tok = strtok(0, ":");
        command_r(idp, qtd, lista, id);
        break;

      case 'R':
        tok = strtok(name, ":");
        strcpy(ide, tok);
        tok = strtok(0, ":");
        strcpy(idp, tok);
        tok = strtok(0, ":");
        command_R(ide, idp, lista, encomendas, id, encid);
        break;

      case 'C':
        tok = strtok(name, ":");
        strcpy(ide, tok);
        tok = strtok(0, ":");
        command_C(ide, lista, encomendas, encid);
        break;

      case 'p':
        tok = strtok(name, ":");
        strcpy(idp, tok);
        tok = strtok(0, ":");
        strcpy(preco, tok);
        tok = strtok(0, ":");
        command_p(idp, preco, lista, id);
        break;

      case 'E':
        tok = strtok(name, ":");
        strcpy(ide, tok);
        tok = strtok(0, ":");
        strcpy(idp, tok);
        tok = strtok(0, ":");
        command_E(ide, idp, lista, encomendas, id, encid);
        break;

      case 'm':
        tok = strtok(name, ":");
        strcpy(idp, tok);
        tok = strtok(0, ":");
        command_m(idp, lista, id);
        break;

      case 'l':
        command_l(lista, id);
        break;

      case 'L':
        tok = strtok(name, ":");
        strcpy(ide, tok);
        tok = strtok(0, ":");
        command_L(ide, lista, encomendas, encid);
        break;

    }

  }

  free_lists(lista, encomendas, id, encid);
  return 0;
}

