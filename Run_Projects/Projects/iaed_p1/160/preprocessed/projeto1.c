/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


int id_num = 0;
int id_encomenda = 0;
typedef struct produto
{
  int id;
  char descricao[63];
  int preco;
  int peso;
  int stock;
} produto;
typedef struct encomenda
{
  int id;
  struct produto fila[10000];
  int peso_total;
  int existe;
} encomenda;
struct encomenda encomendas[500];
struct produto produtos[10000];
void executa_a()
{
  if (id_num < 10000)
  {
    produtos[id_num].id = id_num;
    for (int produtos_index = 0; produtos_index < 10; produtos_index++)
    {
      produtos[id_num].descricao[produtos_index] = new_sym_var(sizeof(char) * 8);
    }

    produtos[id_num].descricao[10 - 1] = '\0';
    produtos[id_num].preco = new_sym_var(sizeof(int) * 8);
    produtos[id_num].peso = new_sym_var(sizeof(int) * 8);
    produtos[id_num].stock = new_sym_var(sizeof(int) * 8);
    printf("Novo produto %d.\n", produtos[id_num].id);
    id_num = id_num + 1;
  }
  else
  {
    
  }

}

void executa_q()
{
  int id_local;
  int qtd;
  id_local = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (produtos[id_local].preco == 0)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_local);
  }
  else
  {
    produtos[id_local].stock = produtos[id_local].stock + qtd;
  }

}

void executa_N()
{
  if (id_encomenda < 500)
  {
    encomendas[id_encomenda].peso_total = 0;
    encomendas[id_encomenda].id = id_encomenda;
    encomendas[id_encomenda].existe = 1;
    printf("Nova encomenda %d.\n", id_encomenda);
    id_encomenda = id_encomenda + 1;
  }
  else
  {
    
  }

}

void executa_A()
{
  int ide;
  int idp;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (encomendas[ide].existe != 1)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (produtos[idp].preco == 0)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (produtos[idp].stock < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if (((produtos[idp].peso * qtd) + encomendas[ide].peso_total) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idp, ide, 200);
        }
        else
        {
          if (encomendas[ide].fila[idp].peso != 0)
          {
            encomendas[ide].fila[idp].stock = encomendas[ide].fila[idp].stock + qtd;
          }
          else
          {
            encomendas[ide].fila[idp] = produtos[idp];
            encomendas[ide].fila[idp].stock = qtd;
          }

          produtos[idp].stock = produtos[idp].stock - qtd;
          encomendas[ide].peso_total = encomendas[ide].peso_total + (produtos[idp].peso * qtd);
        }

      }

    }

  }

}

void executa_E()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (encomendas[ide].existe != 1)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (produtos[idp].preco == 0)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      printf("%s %d.\n", produtos[idp].descricao, encomendas[ide].fila[idp].stock);
    }

  }

}

void quicksort_l(int ordenado[10000], int first, int last)
{
  int i;
  int j;
  int pivot;
  int temp;
  if (first < last)
  {
    pivot = first;
    i = first;
    j = last;
    while (i < j)
    {
      while ((produtos[ordenado[i]].preco <= produtos[ordenado[pivot]].preco) && (i < last))
      {
        if (produtos[ordenado[i]].preco == produtos[ordenado[pivot]].preco)
        {
          if (produtos[ordenado[i]].id > produtos[ordenado[pivot]].id)
          {
            break;
          }
          else
          {
            
          }

        }
        else
        {
          
        }

        i++;
      }

      while ((produtos[ordenado[j]].preco >= produtos[ordenado[pivot]].preco) && (j > first))
      {
        if (produtos[ordenado[j]].preco == produtos[ordenado[pivot]].preco)
        {
          if (produtos[ordenado[j]].id < produtos[ordenado[pivot]].id)
          {
            break;
          }
          else
          {
            
          }

        }
        else
        {
          
        }

        j--;
      }

      if (i < j)
      {
        temp = ordenado[i];
        ordenado[i] = ordenado[j];
        ordenado[j] = temp;
      }
      else
      {
        
      }

    }

    temp = ordenado[pivot];
    ordenado[pivot] = ordenado[j];
    ordenado[j] = temp;
    quicksort_l(ordenado, first, j - 1);
    quicksort_l(ordenado, j + 1, last);
  }
  else
  {
    
  }

}

void executa_l()
{
  int maior;
  int i;
  int ordenado[10000];
  maior = id_num;
  for (i = 0; i < maior; i++)
  {
    ordenado[i] = i;
  }

  quicksort_l(ordenado, 0, maior - 1);
  printf("Produtos\n");
  for (i = 0; i < maior; i++)
  {
    printf("* %s %d %d\n", produtos[ordenado[i]].descricao, produtos[ordenado[i]].preco, produtos[ordenado[i]].stock);
  }

}

void executa_r()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (produtos[idp].preco == 0)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if ((produtos[idp].stock - qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      produtos[idp].stock = produtos[idp].stock - qtd;
    }

  }

}

void executa_R()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (encomendas[ide].existe != 1)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (produtos[idp].preco == 0)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (encomendas[ide].fila[idp].peso != 0)
      {
        produtos[idp].stock = encomendas[ide].fila[idp].stock + produtos[idp].stock;
        encomendas[ide].peso_total = encomendas[ide].peso_total - (encomendas[ide].fila[idp].stock * produtos[idp].peso);
        encomendas[ide].fila[idp].stock = 0;
      }
      else
      {
        
      }

    }

  }

}

void quicksort_L(int ordenado[500], int first, int last, int ide)
{
  int i;
  int j;
  int pivot;
  int temp;
  if (first < last)
  {
    pivot = first;
    i = first;
    j = last;
    while (i < j)
    {
      while ((strcmp(encomendas[ide].fila[ordenado[i]].descricao, encomendas[ide].fila[ordenado[pivot]].descricao) <= 0) && (i < last))
      {
        i++;
      }

      while (strcmp(encomendas[ide].fila[ordenado[j]].descricao, encomendas[ide].fila[ordenado[pivot]].descricao) > 0)
      {
        j--;
      }

      if (i < j)
      {
        temp = ordenado[i];
        ordenado[i] = ordenado[j];
        ordenado[j] = temp;
      }
      else
      {
        
      }

    }

    temp = ordenado[pivot];
    ordenado[pivot] = ordenado[j];
    ordenado[j] = temp;
    quicksort_L(ordenado, first, j - 1, ide);
    quicksort_L(ordenado, j + 1, last, ide);
  }
  else
  {
    
  }

}

void executa_L()
{
  int maior;
  int i;
  int ide;
  int ordenado[10000];
  maior = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (encomendas[ide].existe != 1)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i != id_num; i++)
    {
      if (encomendas[ide].fila[i].peso != 0)
      {
        ordenado[maior] = encomendas[ide].fila[i].id;
        maior = maior + 1;
      }
      else
      {
        
      }

    }

    quicksort_L(ordenado, 0, maior - 1, ide);
    printf("Encomenda %d\n", ide);
    for (i = 0; i < maior; i++)
    {
      if (encomendas[ide].fila[ordenado[i]].stock > 0)
      {
        printf("* %s %d %d\n", encomendas[ide].fila[ordenado[i]].descricao, produtos[ordenado[i]].preco, encomendas[ide].fila[ordenado[i]].stock);
      }
      else
      {
        
      }

    }

  }

}

void executa_C()
{
  int ide;
  int total;
  int i;
  total = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (encomendas[ide].existe != 1)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i < id_num; i++)
    {
      if (encomendas[ide].fila[i].stock != 0)
      {
        total = (encomendas[ide].fila[i].stock * encomendas[ide].fila[i].preco) + total;
      }
      else
      {
        
      }

    }

    printf("Custo da encomenda %d %d.\n", ide, total);
  }

}

void executa_p()
{
  int idp;
  int price;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  price = new_sym_var(sizeof(int) * 8);
  if (produtos[idp].preco == 0)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    produtos[idp].preco = price;
    for (i = 0; encomendas[i].existe == 1; i++)
    {
      if (encomendas[i].fila[idp].preco != 0)
      {
        encomendas[i].fila[idp].preco = price;
      }
      else
      {
        
      }

    }

  }

}

void executa_m()
{
  int idp;
  int i;
  int id_do_maximo;
  int numero_maximo;
  idp = new_sym_var(sizeof(int) * 8);
  if (produtos[idp].peso != 0)
  {
    numero_maximo = 0;
    id_do_maximo = 0;
    for (i = 0; encomendas[i].existe == 1; i++)
    {
      if (encomendas[i].fila[idp].stock > numero_maximo)
      {
        numero_maximo = encomendas[i].fila[idp].stock;
        id_do_maximo = i;
      }
      else
      {
        
      }

    }

    if (numero_maximo > 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, id_do_maximo, numero_maximo);
    }
    else
    {
      
    }

  }
  else
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }

}

int main()
{
  char command;
  while (1)
  {
    command = getchar();
    switch (command)
    {
      case 'a':
        executa_a();
        break;

      case 'q':
        executa_q();
        break;

      case 'N':
        executa_N();
        break;

      case 'A':
        executa_A();
        break;

      case 'E':
        executa_E();
        break;

      case 'l':
        executa_l();
        break;

      case 'r':
        executa_r();
        break;

      case 'R':
        executa_R();
        break;

      case 'L':
        executa_L();
        break;

      case 'C':
        executa_C();
        break;

      case 'p':
        executa_p();
        break;

      case 'm':
        executa_m();
        break;

      case 'x':
        return 0;

    }

  }

  return 1;
}

