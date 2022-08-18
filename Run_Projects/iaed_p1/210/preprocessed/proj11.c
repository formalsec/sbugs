/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int id;
  char descricao[64];
  int preco;
  int peso;
  int stock;
} Produto;
typedef struct 
{
  Produto produtosNumaEcomenda[9999];
} Encomenda;
Produto produtos[9999];
Encomenda encomendas[500];
int produtoID = 0;
int encomendaID = 0;
int numProdutosNumaEcomenda[500] = {0};
void adicionaNovoProduto();
void adicionaStock();
void criaNovoEncomenda();
void adicionaProdutoNumEncomenda();
void removeStockDeProduto();
void removeProdutoNumaEncomenda();
void calculaCustaDaEncomenda();
void alteraPrecoDoProduto();
void listaDescricaoQuantidadeDeProduto();
void listaIdEncomendaEmQueProdutoOcorreMaisVezes();
void listaTodosOsProdutosExistentes();
void listaTodosProdutosNumaEncomenda();
void selectionSort(Produto p[], int num);
int seachIdProdutoNumaEncomenda(int ide, int idp);
int pesoTotalDaEncomenda(int ide, int idp, int quantidade);
void mergesort(Produto a[], int left, int right);
void merge(Produto a[], int left, int m, int right);
int main()
{
  char comando;
  do
  {
    comando = getchar();
    switch (comando)
    {
      case 'a':
        adicionaNovoProduto();
        break;

      case 'q':
        adicionaStock();
        break;

      case 'N':
        criaNovoEncomenda();
        break;

      case 'A':
        adicionaProdutoNumEncomenda();
        break;

      case 'r':
        removeStockDeProduto();
        break;

      case 'R':
        removeProdutoNumaEncomenda();
        break;

      case 'C':
        calculaCustaDaEncomenda();
        break;

      case 'p':
        alteraPrecoDoProduto();
        break;

      case 'E':
        listaDescricaoQuantidadeDeProduto();
        break;

      case 'm':
        listaIdEncomendaEmQueProdutoOcorreMaisVezes();
        break;

      case 'l':
        listaTodosOsProdutosExistentes();
        break;

      case 'L':
        listaTodosProdutosNumaEncomenda();
        break;

    }

  }
  while (comando != 'x');
  return 0;
}

void adicionaNovoProduto()
{
  for (int produtos_index = 0; produtos_index < 10; produtos_index++)
  {
    produtos[produtoID].descricao[produtos_index] = new_sym_var(sizeof(char) * 8);
  }

  produtos[produtoID].descricao[10 - 1] = '\0';
  produtos[produtoID].preco = new_sym_var(sizeof(int) * 8);
  produtos[produtoID].peso = new_sym_var(sizeof(int) * 8);
  produtos[produtoID].stock = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", produtoID);
  produtos[produtoID].id = produtoID;
  produtoID++;
}

void adicionaStock()
{
  int id;
  int quantidadeStock;
  id = new_sym_var(sizeof(int) * 8);
  quantidadeStock = new_sym_var(sizeof(int) * 8);
  if ((id < 0) || (id > (produtoID - 1)))
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
    }
  }
  else
  {
    {
      produtos[id].stock += quantidadeStock;
    }
  }

}

void criaNovoEncomenda()
{
  printf("Nova encomenda %d.\n", encomendaID);
  encomendaID++;
}

void adicionaProdutoNumEncomenda()
{
  int ide;
  int idp;
  int quantidade;
  int num;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if ((ide < 0) || (ide > (encomendaID - 1)))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    if ((idp < 0) || (idp > (produtoID - 1)))
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
    }
    else
    {
      if (produtos[idp].stock < quantidade)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        }
      }
      else
      {
        if (pesoTotalDaEncomenda(ide, idp, quantidade) > 200)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
          }
        }
        else
        {
          {
            num = seachIdProdutoNumaEncomenda(ide, idp);
            if (num == (-1))
            {
              {
                encomendas[ide].produtosNumaEcomenda[numProdutosNumaEcomenda[ide]].id = idp;
                encomendas[ide].produtosNumaEcomenda[numProdutosNumaEcomenda[ide]].preco = produtos[idp].preco;
                encomendas[ide].produtosNumaEcomenda[numProdutosNumaEcomenda[ide]].peso = produtos[idp].peso;
                encomendas[ide].produtosNumaEcomenda[numProdutosNumaEcomenda[ide]].stock = quantidade;
                strcpy(encomendas[ide].produtosNumaEcomenda[numProdutosNumaEcomenda[ide]].descricao, produtos[idp].descricao);
                produtos[idp].stock -= quantidade;
                numProdutosNumaEcomenda[ide]++;
              }
            }
            else
            {
              {
                encomendas[ide].produtosNumaEcomenda[num].stock += quantidade;
                produtos[idp].stock -= quantidade;
              }
            }

          }
        }

      }

    }

  }

}

int pesoTotalDaEncomenda(int ide, int idp, int quantidade)
{
  int i;
  int total = 0;
  for (i = 0; i < numProdutosNumaEcomenda[ide]; i++)
  {
    total += encomendas[ide].produtosNumaEcomenda[i].stock * encomendas[ide].produtosNumaEcomenda[i].peso;
  }

  total += quantidade * produtos[idp].peso;
  return total;
}

void removeStockDeProduto()
{
  int idp;
  int quantidade;
  idp = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if ((idp < 0) || (idp > (produtoID - 1)))
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    if (produtos[idp].stock < quantidade)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
      }
    }
    else
    {
      {
        produtos[idp].stock -= quantidade;
      }
    }

  }

}

void removeProdutoNumaEncomenda()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if ((ide < 0) || (ide > (encomendaID - 1)))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    if ((idp < 0) || (idp > (produtoID - 1)))
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
    }
    else
    {
      {
        int num = seachIdProdutoNumaEncomenda(ide, idp);
        if (num != (-1))
        {
          {
            produtos[idp].stock += encomendas[ide].produtosNumaEcomenda[num].stock;
            encomendas[ide].produtosNumaEcomenda[num].stock = 0;
          }
        }
        else
        {
          
        }

      }
    }

  }

}

void calculaCustaDaEncomenda()
{
  int ide;
  int i;
  int total = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if ((ide < 0) || (ide > (encomendaID - 1)))
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      int num = numProdutosNumaEcomenda[ide];
      for (i = 0; i < num; i++)
      {
        total += encomendas[ide].produtosNumaEcomenda[i].preco * encomendas[ide].produtosNumaEcomenda[i].stock;
      }

      printf("Custo da encomenda %d %d.\n", ide, total);
    }
  }

}

void alteraPrecoDoProduto()
{
  int idp;
  int preco;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if ((idp < 0) || (idp > (produtoID - 1)))
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      produtos[idp].preco = preco;
      for (i = 0; i < encomendaID; i++)
      {
        int num = seachIdProdutoNumaEncomenda(i, idp);
        if (num != (-1))
        {
          {
            encomendas[i].produtosNumaEcomenda[num].preco = preco;
          }
        }
        else
        {
          
        }

      }

    }
  }

}

void listaDescricaoQuantidadeDeProduto()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if ((ide < 0) || (ide > (encomendaID - 1)))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    if ((idp < 0) || (idp > (produtoID - 1)))
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      }
    }
    else
    {
      {
        int id = seachIdProdutoNumaEncomenda(ide, idp);
        if (id != (-1))
        {
          {
            printf("%s %d.\n", encomendas[ide].produtosNumaEcomenda[id].descricao, encomendas[ide].produtosNumaEcomenda[id].stock);
          }
        }
        else
        {
          {
            printf("%s %d.\n", produtos[idp].descricao, 0);
          }
        }

      }
    }

  }

}

int seachIdProdutoNumaEncomenda(int ide, int idp)
{
  int i;
  for (i = 0; i < numProdutosNumaEcomenda[ide]; i++)
  {
    if (encomendas[ide].produtosNumaEcomenda[i].id == idp)
    {
      {
        return i;
      }
    }
    else
    {
      
    }

  }

  return -1;
}

void listaIdEncomendaEmQueProdutoOcorreMaisVezes()
{
  int idp;
  idp = new_sym_var(sizeof(int) * 8);
  if ((idp < 0) || (idp > (produtoID - 1)))
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      int i;
      int j;
      int contador = 0;
      int idP;
      int id;
      int v[500];
      int max = -1;
      int maxIdE;
      int maxIdP;
      for (i = 0; i < encomendaID; i++)
      {
        idP = seachIdProdutoNumaEncomenda(i, idp);
        if (idP != (-1))
        {
          {
            v[contador] = i;
            contador++;
          }
        }
        else
        {
          
        }

      }

      for (j = 0; j < contador; j++)
      {
        id = seachIdProdutoNumaEncomenda(v[j], idp);
        if (max < encomendas[v[j]].produtosNumaEcomenda[id].stock)
        {
          {
            max = encomendas[v[j]].produtosNumaEcomenda[id].stock;
            maxIdE = v[j];
            maxIdP = id;
          }
        }
        else
        {
          
        }

      }

      if ((contador > 0) && (encomendas[maxIdE].produtosNumaEcomenda[maxIdP].stock != 0))
      {
        {
          printf("Maximo produto %d %d %d.\n", idp, maxIdE, encomendas[maxIdE].produtosNumaEcomenda[maxIdP].stock);
        }
      }
      else
      {
        
      }

    }
  }

}

void listaTodosOsProdutosExistentes()
{
  Produto p[9999];
  int x;
  int i;
  for (x = 0; x < produtoID; x++)
  {
    p[x] = produtos[x];
  }

  mergesort(p, 0, produtoID - 1);
  printf("Produtos\n");
  for (i = 0; i < produtoID; i++)
  {
    printf("* %s %d %d\n", p[i].descricao, p[i].preco, p[i].stock);
  }

}

void mergesort(Produto a[], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort(a, left, m);
  mergesort(a, m + 1, right);
  merge(a, left, m, right);
}

void merge(Produto a[], int left, int m, int right)
{
  Produto aux[9999];
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = a[j + 1];

  for (k = left; k <= right; k++)
    if (aux[j].preco < aux[i].preco)
  {
    {
      a[k] = aux[j--];
    }
  }
  else
  {
    if (aux[i].preco < aux[j].preco)
    {
      {
        a[k] = aux[i++];
      }
    }
    else
    {
      {
        if (aux[j].id < aux[i].id)
        {
          {
            a[k] = aux[j--];
          }
        }
        else
        {
          {
            a[k] = aux[i++];
          }
        }

      }
    }

  }


}

void listaTodosProdutosNumaEncomenda()
{
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if ((ide < 0) || (ide > (encomendaID - 1)))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      Produto p[9999];
      int x;
      int i;
      int num = numProdutosNumaEcomenda[ide];
      for (x = 0; x < num; x++)
      {
        p[x] = encomendas[ide].produtosNumaEcomenda[x];
      }

      selectionSort(p, num);
      printf("Encomenda %d\n", ide);
      for (i = 0; i < num; i++)
      {
        if (p[i].stock != 0)
        {
          {
            printf("* %s %d %d\n", p[i].descricao, p[i].preco, p[i].stock);
          }
        }
        else
        {
          
        }

      }

    }
  }

}

void selectionSort(Produto p[], int num)
{
  int i;
  int j;
  for (i = 0; i < num; i++)
  {
    Produto aux;
    int min = i;
    for (j = i + 1; j < num; j++)
    {
      if (strcmp(p[j].descricao, p[min].descricao) < 0)
      {
        {
          min = j;
        }
      }
      else
      {
        
      }

    }

    aux = p[i];
    p[i] = p[min];
    p[min] = aux;
  }

}

