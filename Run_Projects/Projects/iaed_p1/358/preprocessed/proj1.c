/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Produto
{
  int id_produto;
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
} Produto;
typedef struct encomenda
{
  Produto prod[200];
  int id_encomenda;
  int n_produtos;
  int peso;
} encomenda;
encomenda criaEncomenda(int id_encomenda)
{
  encomenda a;
  a.id_encomenda = id_encomenda;
  a.n_produtos = 0;
  a.peso = 0;
  printf("Nova encomenda %d.\n", id_encomenda);
  return a;
}

void adicionaEncomenda(Produto Stock[10000], encomenda Lista[500], int id_encomenda, int id_produto)
{
  int ide = 0;
  int idp = 0;
  int qtd = 0;
  int i;
  int len;
  int add = 0;
  Produto a;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ide >= id_encomenda)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= id_produto)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (Stock[idp].quantidade < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if (((Stock[idp].peso * qtd) + Lista[ide].peso) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          len = Lista[ide].n_produtos;
          for (i = 0; i < len; i++)
          {
            a = Lista[ide].prod[i];
            if (a.id_produto == idp)
            {
              Lista[ide].prod[i].quantidade += qtd;
              Lista[ide].peso += Stock[idp].peso * qtd;
              Stock[idp].quantidade -= qtd;
              add = 1;
            }
            else
            {
              
            }

          }

          if (add == 0)
          {
            Lista[ide].prod[len] = Stock[idp];
            Lista[ide].prod[len].quantidade = qtd;
            Stock[idp].quantidade -= qtd;
            Lista[ide].peso += Stock[idp].peso * qtd;
            Lista[ide].n_produtos += 1;
          }
          else
          {
            
          }

        }

      }

    }

  }

}

void removeEncomenda(Produto Stock[10000], encomenda Lista[500], int id_encomenda, int id_produto)
{
  int ide;
  int idp;
  int i;
  Produto a;
  Produto temp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= id_encomenda)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= id_produto)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      for (i = 0; i < Lista[ide].n_produtos; i++)
      {
        a = Lista[ide].prod[i];
        if (a.id_produto == idp)
        {
          Lista[ide].peso -= Lista[ide].prod[i].quantidade * Lista[ide].prod[i].peso;
          Stock[idp].quantidade += Lista[ide].prod[i].quantidade;
          temp = Lista[ide].prod[i];
          Lista[ide].prod[i] = Lista[ide].prod[Lista[ide].n_produtos - 1];
          Lista[ide].prod[Lista[ide].n_produtos - 1] = temp;
          Lista[ide].n_produtos -= 1;
        }
        else
        {
          
        }

      }

    }

  }

}

Produto leProduto(int id_produto)
{
  Produto a;
  memset(a.descricao, 0, 63);
  a.preco = 0;
  a.peso = 0;
  a.quantidade = 0;
  a.id_produto = id_produto;
  for (int a_index = 0; a_index < 10; a_index++)
  {
    a.descricao[a_index] = new_sym_var(sizeof(char) * 8);
  }

  a.descricao[10 - 1] = '\0';
  a.preco = new_sym_var(sizeof(int) * 8);
  a.peso = new_sym_var(sizeof(int) * 8);
  a.quantidade = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", a.id_produto);
  return a;
}

void addStock(Produto Stock[10000], int id_produto)
{
  int idp = 0;
  int qtd = 0;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp < id_produto)
  {
    Stock[idp].quantidade += qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

}

void removeStock(Produto Stock[10000], int id_produto)
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= id_produto)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (Stock[idp].quantidade < qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      Stock[idp].quantidade -= qtd;
    }

  }

}

void custoEncomenda(encomenda Lista[500], int id_encomenda)
{
  int i;
  int custo = 0;
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= id_encomenda)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i < Lista[ide].n_produtos; i++)
    {
      custo += Lista[ide].prod[i].preco * Lista[ide].prod[i].quantidade;
    }

    printf("Custo da encomenda %d %d.\n", ide, custo);
  }

}

void alteraPreco(Produto Stock[10000], encomenda Lista[500], int id_encomenda, int id_produto)
{
  int idp;
  int novoPreco;
  int i;
  int e;
  idp = new_sym_var(sizeof(int) * 8);
  novoPreco = new_sym_var(sizeof(int) * 8);
  if (idp >= id_produto)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    Stock[idp].preco = novoPreco;
    for (i = 0; i < id_encomenda; i++)
    {
      for (e = 0; e < Lista[i].n_produtos; e++)
      {
        if (Lista[i].prod[e].id_produto == idp)
        {
          Lista[i].prod[e].preco = novoPreco;
        }
        else
        {
          
        }

      }

    }

  }

}

void produtoEncomenda(Produto Stock[10000], encomenda Lista[500], int id_encomenda, int id_produto)
{
  int ide;
  int idp;
  int i;
  int encontrou = 0;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= id_encomenda)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp >= id_produto)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      for (i = 0; i < Lista[ide].n_produtos; i++)
      {
        if (Lista[ide].prod[i].id_produto == idp)
        {
          printf("%s %d.\n", Lista[ide].prod[i].descricao, Lista[ide].prod[i].quantidade);
          encontrou = 1;
        }
        else
        {
          
        }

      }

      if (encontrou == 0)
      {
        printf("%s 0.\n", Stock[idp].descricao);
      }
      else
      {
        
      }

    }

  }

}

void ocorreProduto(encomenda Lista[500], int id_encomenda, int id_produto)
{
  int idp;
  int i;
  int e;
  int maior_ide = -1;
  int qtd = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= id_produto)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < id_encomenda; i++)
    {
      for (e = 0; e < Lista[i].n_produtos; e++)
      {
        if ((Lista[i].prod[e].id_produto == idp) && (Lista[i].prod[e].quantidade > qtd))
        {
          qtd = Lista[i].prod[e].quantidade;
          maior_ide = Lista[i].id_encomenda;
        }
        else
        {
          
        }

      }

    }

    if (maior_ide >= 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, maior_ide, qtd);
    }
    else
    {
      
    }

  }

}

void mergeStock(Produto arr[10000], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  Produto L[10000];
  Produto R[10000];
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];

  for (j = 0; j < n2; j++)
    R[j] = arr[(m + 1) + j];

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (L[i].preco <= R[j].preco)
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }

    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }

}

void mergeSortStock(Produto arr[10000], int l, int r)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSortStock(arr, l, m);
    mergeSortStock(arr, m + 1, r);
    mergeStock(arr, l, m, r);
  }
  else
  {
    
  }

}

void listStock(Produto Stock[10000], int id_produto)
{
  int i;
  Produto org[10000];
  for (i = 0; i < id_produto; i++)
    org[i] = Stock[i];

  mergeSortStock(org, 0, id_produto - 1);
  printf("Produtos\n");
  for (i = 0; i < id_produto; i++)
  {
    printf("* ");
    printf("%s ", org[i].descricao);
    printf("%d ", org[i].preco);
    printf("%d\n", org[i].quantidade);
  }

}

int maior(char um[20], char dois[20])
{
  int i;
  int len;
  int maior = 2;
  if (strlen(um) > strlen(dois))
  {
    len = strlen(dois);
  }
  else
  {
    len = strlen(um);
  }

  for (i = 0; i < len; i++)
  {
    if (um[i] > dois[i])
    {
      maior = 1;
      break;
    }
    else
    {
      if (um[i] < dois[i])
      {
        maior = 2;
        break;
      }
      else
      {
        
      }

    }

  }

  return maior;
}

void mergeEncomenda(Produto arr[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  Produto L[200];
  Produto R[200];
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];

  for (j = 0; j < n2; j++)
    R[j] = arr[(m + 1) + j];

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (maior(L[i].descricao, R[j].descricao) == 2)
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }

    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }

}

void mergeSortEncomenda(Produto arr[], int l, int r)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSortEncomenda(arr, l, m);
    mergeSortEncomenda(arr, m + 1, r);
    mergeEncomenda(arr, l, m, r);
  }
  else
  {
    
  }

}

void listEncomenda(encomenda Lista[500], int id_encomenda)
{
  int ide;
  int i;
  encomenda enc;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= id_encomenda)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    enc = Lista[ide];
    mergeSortEncomenda(enc.prod, 0, enc.n_produtos - 1);
    printf("Encomenda %d\n", ide);
    for (i = 0; i < enc.n_produtos; i++)
    {
      printf("* %s %d %d\n", enc.prod[i].descricao, enc.prod[i].preco, enc.prod[i].quantidade);
    }

  }

}

int menu(Produto Stock[10000], encomenda Lista[500], int id_produto, int id_encomenda)
{
  char opcao = ' ';
  while (opcao != 'x')
  {
    opcao = new_sym_var(sizeof(char) * 8);
    if (opcao == 'a')
    {
      Stock[id_produto] = leProduto(id_produto);
      id_produto++;
    }
    else
    {
      if (opcao == 'l')
      {
        listStock(Stock, id_produto);
      }
      else
      {
        if (opcao == 'q')
        {
          addStock(Stock, id_produto);
        }
        else
        {
          if (opcao == 'N')
          {
            Lista[id_encomenda] = criaEncomenda(id_encomenda);
            id_encomenda++;
          }
          else
          {
            if (opcao == 'A')
            {
              adicionaEncomenda(Stock, Lista, id_encomenda, id_produto);
            }
            else
            {
              if (opcao == 'r')
              {
                removeStock(Stock, id_produto);
              }
              else
              {
                if (opcao == 'R')
                {
                  removeEncomenda(Stock, Lista, id_encomenda, id_produto);
                }
                else
                {
                  if (opcao == 'L')
                  {
                    listEncomenda(Lista, id_encomenda);
                  }
                  else
                  {
                    if (opcao == 'C')
                    {
                      custoEncomenda(Lista, id_encomenda);
                    }
                    else
                    {
                      if (opcao == 'p')
                      {
                        alteraPreco(Stock, Lista, id_encomenda, id_produto);
                      }
                      else
                      {
                        if (opcao == 'E')
                        {
                          produtoEncomenda(Stock, Lista, id_encomenda, id_produto);
                        }
                        else
                        {
                          if (opcao == 'm')
                          {
                            ocorreProduto(Lista, id_encomenda, id_produto);
                          }
                          else
                          {
                            
                          }

                        }

                      }

                    }

                  }

                }

              }

            }

          }

        }

      }

    }

  }

  return 0;
}

int main()
{
  static Produto Stock[10000] = {0};
  static encomenda Lista[500] = {0};
  int id_produto = 0;
  int id_encomenda = 0;
  menu(Stock, Lista, id_produto, id_encomenda);
  return 0;
}

