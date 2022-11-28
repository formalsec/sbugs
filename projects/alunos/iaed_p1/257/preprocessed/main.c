#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "structs.h"


produto produtos[10000];
encomenda encomendas[500];
int nextprdctid = 0;
int nextencid = 0;
produto elimina_produto(produto prdct)
{
  prdct.id = -1;
  strcpy(prdct.descricao, "\0");
  prdct.preco = 0;
  prdct.peso = 0;
  prdct.stock = 0;
  prdct.posfull = 0;
  return prdct;
}

int exist_em_encomenda(int pid, int eid)
{
  int i;
  encomenda enc = encomendas[eid];
  for (i = 0; i < enc.totalprdcts; i++)
  {
    if (enc.prdcts[i].id == pid)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

void Merge(produto *arr, int low, int mid, int high)
{
  int mergedSize = (high - low) + 1;
  produto *temp = (produto *) malloc(mergedSize * (sizeof(produto)));
  int mergePos = 0;
  int leftPos = low;
  int rightPos = mid + 1;
  while ((leftPos <= mid) && (rightPos <= high))
  {
    if (arr[leftPos].preco < arr[rightPos].preco)
    {
      temp[mergePos++] = arr[leftPos++];
    }
    else
    {
      if ((arr[leftPos].preco == arr[rightPos].preco) && (arr[leftPos].id < arr[rightPos].id))
      {
        temp[mergePos++] = arr[leftPos++];
      }
      else
      {
        temp[mergePos++] = arr[rightPos++];
      }

    }

  }

  while (leftPos <= mid)
  {
    temp[mergePos++] = arr[leftPos++];
  }

  while (rightPos <= high)
  {
    temp[mergePos++] = arr[rightPos++];
  }

  assert(mergePos == mergedSize);
  for (mergePos = 0; mergePos < mergedSize; ++mergePos)
    arr[low + mergePos] = temp[mergePos];

  free(temp);
}

static void MergeSort(produto *arr, int low, int high)
{
  if (low < high)
  {
    int mid = (low + high) / 2;
    MergeSort(arr, low, mid);
    MergeSort(arr, mid + 1, high);
    Merge(arr, low, mid, high);
  }
  else
  {
    
  }

}

void commando_a(char in[100])
{
  produto tmp;
  tmp.id = nextprdctid;
  strcpy(tmp.descricao, strtok(in, ":"));
  tmp.preco = atoi(strtok(0, ":"));
  tmp.peso = atoi(strtok(0, ":"));
  tmp.stock = atoi(strtok(0, "\n"));
  tmp.posfull = 1;
  produtos[nextprdctid++] = tmp;
  printf("Novo produto %d.\n", tmp.id);
}

void commando_q(char in[100])
{
  produto tmp;
  int pid = atoi(strtok(in, ":"));
  int qtd = atoi(strtok(0, "\n"));
  tmp = produtos[pid];
  if (tmp.posfull != 1)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", pid);
  }
  else
  {
    tmp.stock += qtd;
    produtos[pid] = tmp;
  }

}

void commando_N()
{
  encomenda tmp;
  tmp.id = nextencid;
  tmp.totalprdcts = 0;
  tmp.pesototal = 0;
  tmp.precototal = 0;
  tmp.posfull = 1;
  encomendas[nextencid++] = tmp;
  printf("Nova encomenda %d.\n", tmp.id);
}

void commando_A(char in[100])
{
  int eid = atoi(strtok(in, ":"));
  int pid = atoi(strtok(0, ":"));
  int qtd = atoi(strtok(0, "\n"));
  encomenda tmp = encomendas[eid];
  produto ogprdct = produtos[pid];
  produto prdcttoadd;
  if (tmp.posfull != 1)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", pid, eid);
  }
  else
  {
    if (ogprdct.posfull != 1)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", pid, eid);
    }
    else
    {
      if ((qtd > ogprdct.stock) && (ogprdct.posfull == 1))
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", pid, eid);
      }
      else
      {
        if ((((tmp.pesototal + (qtd * ogprdct.peso)) > 200) && (ogprdct.posfull == 1)) && (tmp.posfull == 1))
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", pid, eid, 200);
        }
        else
        {
          int pos = exist_em_encomenda(pid, eid);
          if (pos != (-1))
          {
            tmp.prdcts[pos].stock += qtd;
            tmp.precototal += tmp.prdcts[pos].preco * qtd;
            tmp.pesototal += tmp.prdcts[pos].peso * qtd;
          }
          else
          {
            prdcttoadd.id = ogprdct.id;
            strcpy(prdcttoadd.descricao, ogprdct.descricao);
            prdcttoadd.preco = ogprdct.preco;
            prdcttoadd.peso = ogprdct.peso;
            prdcttoadd.stock = qtd;
            prdcttoadd.posfull = 1;
            tmp.prdcts[tmp.totalprdcts++] = prdcttoadd;
            tmp.pesototal += prdcttoadd.peso * qtd;
            tmp.precototal += prdcttoadd.preco * qtd;
          }

          encomendas[eid] = tmp;
          ogprdct.stock -= qtd;
          produtos[pid] = ogprdct;
        }

      }

    }

  }

}

void commando_r(char in[100])
{
  int pid = atoi(strtok(in, ":"));
  int qtd = atoi(strtok(0, "\n"));
  produto tmp = produtos[pid];
  if (tmp.posfull != 1)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", pid);
  }
  else
  {
    if (((tmp.stock - qtd) < 0) && (tmp.posfull == 1))
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, pid);
    }
    else
    {
      tmp.stock -= qtd;
      produtos[pid] = tmp;
    }

  }

}

void commando_R(char in[100])
{
  int i;
  int j;
  int qtd = 0;
  int eid = atoi(strtok(in, ":"));
  int pid = atoi(strtok(0, "\n"));
  int pos = exist_em_encomenda(pid, eid);
  encomenda tmp = encomendas[eid];
  if (tmp.posfull != 1)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", pid, eid);
  }
  else
  {
    if (produtos[pid].posfull != 1)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", pid, eid);
    }
    else
    {
      
    }

    if (((produtos[pid].posfull == 1) && (tmp.posfull == 1)) && (pos != (-1)))
    {
      produto tochange = produtos[pid];
      for (i = 0; i < tmp.totalprdcts; i++)
      {
        if (tmp.prdcts[i].id == pid)
        {
          tmp.precototal -= tmp.prdcts[i].preco * tmp.prdcts[i].stock;
          tmp.pesototal -= tmp.prdcts[i].peso * tmp.prdcts[i].stock;
          qtd = tmp.prdcts[i].stock;
          tmp.prdcts[i] = elimina_produto(tmp.prdcts[i]);
          for (j = i; j < (tmp.totalprdcts - 1); j++)
          {
            tmp.prdcts[j] = tmp.prdcts[j + 1];
          }

          break;
        }
        else
        {
          
        }

      }

      tochange.stock += qtd;
      produtos[pid] = tochange;
      tmp.totalprdcts -= 1;
      encomendas[eid] = tmp;
    }
    else
    {
      
    }

  }

}

void commando_C(char in[100])
{
  int eid = atoi(strtok(in, "\n"));
  encomenda tmp = encomendas[eid];
  if (tmp.posfull != 1)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", eid);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", eid, tmp.precototal);
  }

}

void commando_p(char in[100])
{
  int i;
  int j;
  int pid = atoi(strtok(in, ":"));
  int npreco = atoi(strtok(0, "\n"));
  produto tmp = produtos[pid];
  if (tmp.posfull != 1)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", pid);
  }
  else
  {
    produtos[pid].preco = npreco;
    for (i = 0; i < nextencid; i++)
    {
      encomenda enc = encomendas[i];
      for (j = 0; j < enc.totalprdcts; j++)
      {
        if (enc.prdcts[j].id == pid)
        {
          enc.precototal -= enc.prdcts[j].preco * enc.prdcts[j].stock;
          enc.prdcts[j].preco = npreco;
          enc.precototal += npreco * enc.prdcts[j].stock;
          encomendas[i] = enc;
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void commando_E(char in[100])
{
  int eid = atoi(strtok(in, ":"));
  int pid = atoi(strtok(0, "\n"));
  int i;
  encomenda tmp = encomendas[eid];
  produto encomendado;
  if (tmp.posfull != 1)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", eid);
  }
  else
  {
    if (produtos[pid].posfull != 1)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", pid);
    }
    else
    {
      i = exist_em_encomenda(pid, eid);
      if (i != (-1))
      {
        encomendado = tmp.prdcts[i];
        printf("%s %d.\n", encomendado.descricao, encomendado.stock);
      }
      else
      {
        encomendado = produtos[pid];
        printf("%s 0.\n", encomendado.descricao);
      }

    }

  }

}

void commando_m(char in[100])
{
  int pid = atoi(strtok(in, "\n"));
  int maxval = 0;
  int maxeid = 0;
  int i;
  int j;
  encomenda tmp;
  if (produtos[pid].posfull != 1)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", pid);
  }
  else
  {
    for (i = 0; i < nextencid; i++)
    {
      tmp = encomendas[i];
      for (j = 0; j < tmp.totalprdcts; j++)
      {
        if ((tmp.prdcts[j].id == pid) && (tmp.prdcts[j].stock > maxval))
        {
          maxval = tmp.prdcts[j].stock;
          maxeid = tmp.id;
        }
        else
        {
          
        }

        if (((tmp.prdcts[j].id == pid) && (tmp.prdcts[j].stock == maxval)) && (tmp.id < maxeid))
        {
          maxeid = tmp.id;
        }
        else
        {
          
        }

      }

    }

    if (maxval > 0)
    {
      printf("Maximo produto %d %d %d.\n", pid, maxeid, maxval);
    }
    else
    {
      
    }

  }

}

void commando_l()
{
  produto *arr = (produto *) malloc(10000 * (sizeof(produto)));
  int i;
  for (i = 0; i < nextprdctid; i++)
  {
    arr[i] = produtos[i];
  }

  MergeSort(arr, 0, nextprdctid - 1);
  printf("Produtos\n");
  for (i = 0; i < nextprdctid; i++)
    printf("* %s %d %d\n", arr[i].descricao, arr[i].preco, arr[i].stock);

  free(arr);
}

void commando_L(char in[100])
{
  int i;
  int j;
  int eid = atoi(strtok(in, "\n"));
  encomenda tmp = encomendas[eid];
  if (tmp.posfull != 1)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", eid);
  }
  else
  {
    produto temp;
    produto ordalf[200];
    for (i = 0; i < tmp.totalprdcts; i++)
      ordalf[i] = tmp.prdcts[i];

    for (i = 0; i < tmp.totalprdcts; i++)
    {
      for (j = i + 1; j < tmp.totalprdcts; j++)
      {
        if (strcmp(ordalf[i].descricao, ordalf[j].descricao) > 0)
        {
          temp = ordalf[i];
          ordalf[i] = ordalf[j];
          ordalf[j] = temp;
        }
        else
        {
          
        }

      }

    }

    printf("Encomenda %d\n", eid);
    for (i = 0; i < tmp.totalprdcts; i++)
      printf("* %s %d %d\n", ordalf[i].descricao, ordalf[i].preco, ordalf[i].stock);

  }

}

void commando_x()
{
  exit(0);
}

int main()
{
  char line[100];
  while (fgets(line, 100, stdin))
  {
    char command;
    char input[100];
    command = new_sym_var(sizeof(char) * 8);
    for (int input_index = 0; input_index < 10; input_index++)
    {
      input[input_index] = new_sym_var(sizeof(char) * 8);
    }

    input[10 - 1] = '\0';
    switch (command)
    {
      case 'a':
        commando_a(input);
        break;

      case 'q':
        commando_q(input);
        break;

      case 'N':
        commando_N();
        break;

      case 'A':
        commando_A(input);
        break;

      case 'r':
        commando_r(input);
        break;

      case 'R':
        commando_R(input);
        break;

      case 'C':
        commando_C(input);
        break;

      case 'p':
        commando_p(input);
        break;

      case 'E':
        commando_E(input);
        break;

      case 'm':
        commando_m(input);
        break;

      case 'l':
        commando_l();
        break;

      case 'L':
        commando_L(input);
        break;

      case 'x':
        commando_x();
        break;

    }

  }

  return 0;
}
