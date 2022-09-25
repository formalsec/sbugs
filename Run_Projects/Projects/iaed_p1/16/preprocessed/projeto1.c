/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct 
{
  int idp;
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
} produto;
typedef struct 
{
  int ide;
  int lista[200][2];
  int peso_total;
  int custo_total;
  int total_produtos;
} encomenda;
void cria_produto();
void adiciona_s();
void cria_encomenda();
void adiciona_e();
void remove_s();
void remove_e();
void custo_e();
void altera_preco();
void lista_e();
void lista_ide();
void lista_produtos();
void lista_encomenda();
void mergesort_f(int a[][2], int l, int r);
void merge_f(int a[][2], int l, int m, int r);
void StringSort(char a[][63], int b[][2], int l, int r);
static int idp_atual = 0;
static int ide_atual = 0;
produto Produtos[10000];
encomenda Encomendas[500];
int aux[10000][2];
int main()
{
  char comando;
  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      case 'a':
        cria_produto();
        break;

      case 'q':
        adiciona_s();
        break;

      case 'N':
        cria_encomenda();
        break;

      case 'A':
        adiciona_e();
        break;

      case 'r':
        remove_s();
        break;

      case 'R':
        remove_e();
        break;

      case 'C':
        custo_e();
        break;

      case 'p':
        altera_preco();
        break;

      case 'E':
        lista_e();
        break;

      case 'm':
        lista_ide();
        break;

      case 'l':
        lista_produtos();
        break;

      case 'L':
        lista_encomenda();
        break;

      default:
        break;

    }

  }

  return 0;
}

void cria_produto()
{
  int qtd;
  int preco;
  int peso;
  char descricao[65];
  produto p;
  getchar();
  for (int descricao_index = 0; descricao_index < 10; descricao_index++)
  {
    descricao[descricao_index] = new_sym_var(sizeof(char) * 8);
  }

  descricao[10 - 1] = '\0';
  preco = new_sym_var(sizeof(int) * 8);
  peso = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  strcpy(p.descricao, descricao);
  p.idp = idp_atual;
  p.peso = peso;
  p.preco = preco;
  p.quantidade = qtd;
  Produtos[idp_atual] = p;
  printf("Novo produto %d.\n", idp_atual);
  idp_atual++;
}

void adiciona_s()
{
  int idp;
  int qtd;
  getchar();
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp_atual <= idp)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    Produtos[idp].quantidade += qtd;
  }

}

void cria_encomenda()
{
  Encomendas[ide_atual].ide = ide_atual;
  Encomendas[ide_atual].custo_total = 0;
  Encomendas[ide_atual].peso_total = 0;
  Encomendas[ide_atual].total_produtos = 0;
  printf("Nova encomenda %d.\n", ide_atual);
  ide_atual++;
}

void adiciona_e()
{
  int ide;
  int idp;
  int qtd;
  getchar();
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ide >= ide_atual)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= idp_atual)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (qtd > Produtos[idp].quantidade)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if (((Produtos[idp].peso * qtd) + Encomendas[ide].peso_total) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          encomenda e = Encomendas[ide];
          int procura = 1;
          int i = 0;
          while ((i < e.total_produtos) && procura)
          {
            if (e.lista[i][0] == idp)
            {
              procura = 0;
              Encomendas[ide].lista[i][1] += qtd;
              Encomendas[ide].peso_total += Produtos[idp].peso * qtd;
              Encomendas[ide].custo_total += Produtos[idp].preco * qtd;
              Produtos[idp].quantidade -= qtd;
            }
            else
            {
              
            }

            i++;
          }

          if (procura == 1)
          {
            Encomendas[ide].lista[e.total_produtos][0] = idp;
            Encomendas[ide].lista[e.total_produtos][1] = qtd;
            Encomendas[ide].total_produtos += 1;
            Encomendas[ide].peso_total += Produtos[idp].peso * qtd;
            Encomendas[ide].custo_total += Produtos[idp].preco * qtd;
            Produtos[idp].quantidade -= qtd;
          }
          else
          {
            
          }

        }

      }

    }

  }

}

void remove_s()
{
  int idp;
  int qtd;
  getchar();
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= idp_atual)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if ((Produtos[idp].quantidade - qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      Produtos[idp].quantidade -= qtd;
    }

  }

}

void remove_e()
{
  int ide;
  int idp;
  getchar();
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= ide_atual)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= idp_atual)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      int qtd;
      int k;
      int i;
      encomenda e = Encomendas[ide];
      for (i = 0; i < e.total_produtos; i++)
      {
        if (e.lista[i][0] == idp)
        {
          qtd = e.lista[i][1];
          for (k = i; k < (e.total_produtos - 1); k++)
          {
            Encomendas[ide].lista[k][0] = e.lista[k + 1][0];
            Encomendas[ide].lista[k][1] = e.lista[k + 1][1];
          }

          Encomendas[ide].total_produtos -= 1;
          Encomendas[ide].custo_total -= Produtos[idp].preco * qtd;
          Encomendas[ide].peso_total -= Produtos[idp].peso * qtd;
          Produtos[idp].quantidade += qtd;
        }
        else
        {
          
        }

      }

    }

  }

}

void custo_e()
{
  int ide;
  getchar();
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= ide_atual)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", ide, Encomendas[ide].custo_total);
  }

}

void altera_preco()
{
  int idp;
  int preco;
  getchar();
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp >= idp_atual)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    int i;
    int j;
    int diff;
    diff = preco - Produtos[idp].preco;
    Produtos[idp].preco = preco;
    for (i = 0; i < ide_atual; i++)
    {
      encomenda e = Encomendas[i];
      for (j = 0; j < e.total_produtos; j++)
      {
        int p = e.lista[j][0];
        int q = e.lista[j][1];
        if (p == idp)
        {
          Encomendas[i].custo_total += diff * q;
        }
        else
        {
          
        }

      }

    }

  }

}

void lista_e()
{
  int ide;
  int idp;
  getchar();
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= ide_atual)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp >= idp_atual)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      encomenda e = Encomendas[ide];
      int q;
      int i;
      q = 0;
      for (i = 0; i < e.total_produtos; i++)
      {
        if (e.lista[i][0] == idp)
        {
          q = e.lista[i][1];
        }
        else
        {
          
        }

      }

      printf("%s %d.\n", Produtos[idp].descricao, q);
    }

  }

}

void lista_ide()
{
  int idp;
  int max;
  int ide;
  int i;
  int j;
  getchar();
  idp = new_sym_var(sizeof(int) * 8);
  max = -1;
  if (idp >= idp_atual)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < ide_atual; i++)
    {
      encomenda e = Encomendas[i];
      for (j = 0; j < e.total_produtos; j++)
      {
        if ((e.lista[j][0] == idp) && (e.lista[j][1] > max))
        {
          max = e.lista[j][1];
          ide = e.ide;
        }
        else
        {
          
        }

      }

    }

    if (max >= 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, ide, max);
    }
    else
    {
      
    }

  }

}

void lista_produtos()
{
  int idp;
  int i;
  int id;
  int preco;
  int lista[10000][2];
  for (idp = 0; idp < idp_atual; idp++)
  {
    lista[idp][0] = Produtos[idp].preco;
    lista[idp][1] = Produtos[idp].idp;
  }

  mergesort_f(lista, 0, idp_atual - 1);
  printf("Produtos\n");
  for (i = 0; i < idp_atual; i++)
  {
    id = lista[i][1];
    preco = lista[i][0];
    printf("* %s %d %d\n", Produtos[id].descricao, preco, Produtos[id].quantidade);
  }

}

void lista_encomenda()
{
  int ide;
  int i;
  int idp;
  encomenda e;
  char lista[200][63];
  getchar();
  ide = new_sym_var(sizeof(int) * 8);
  e = Encomendas[ide];
  if (ide >= ide_atual)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i < e.total_produtos; i++)
    {
      idp = e.lista[i][0];
      strcpy(lista[i], Produtos[idp].descricao);
    }

    StringSort(lista, e.lista, 0, e.total_produtos - 1);
    printf("Encomenda %d\n", ide);
    for (i = 0; i < e.total_produtos; i++)
    {
      idp = e.lista[i][0];
      printf("* %s %d %d\n", lista[i], Produtos[idp].preco, e.lista[i][1]);
    }

  }

}

void merge_f(int a[][2], int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
  {
    aux[i - 1][0] = a[i - 1][0];
    aux[i - 1][1] = a[i - 1][1];
  }

  for (j = m; j < r; j++)
  {
    aux[(r + m) - j][0] = a[j + 1][0];
    aux[(r + m) - j][1] = a[j + 1][1];
  }

  for (k = l; k <= r; k++)
  {
    if ((aux[j][0] < aux[i][0]) || ((aux[j][0] == aux[i][0]) && (aux[j][1] < aux[i][1])))
    {
      a[k][0] = aux[j][0];
      a[k][1] = aux[j][1];
      j--;
    }
    else
    {
      a[k][0] = aux[i][0];
      a[k][1] = aux[i][1];
      i++;
    }

  }

}

void mergesort_f(int a[][2], int l, int r)
{
  int m;
  if (r > l)
  {
    m = (r + l) / 2;
    mergesort_f(a, l, m);
    mergesort_f(a, m + 1, r);
    merge_f(a, l, m, r);
  }
  else
  {
    
  }

}

void StringSort(char a[][63], int b[][2], int l, int r)
{
  int i;
  int j;
  int min;
  for (i = l; i < r; i++)
  {
    char aux[63];
    int id_aux[2];
    min = i;
    for (j = i + 1; j <= r; j++)
    {
      if (strcmp(a[j], a[min]) <= 0)
      {
        min = j;
      }
      else
      {
        
      }

    }

    strcpy(aux, a[i]);
    id_aux[0] = b[i][0];
    id_aux[1] = b[i][1];
    strcpy(a[i], a[min]);
    b[i][0] = b[min][0];
    b[i][1] = b[min][1];
    strcpy(a[min], aux);
    b[min][0] = id_aux[0];
    b[min][1] = id_aux[1];
  }

}

