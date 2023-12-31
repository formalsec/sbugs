#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int identificador;
  char descricao[64];
  int preco;
  int peso;
  int stock;
} Produto;
typedef struct 
{
  int identificador;
  Produto produtos[200];
  int numProd;
  int pesoTotal;
} Encomenda;
Produto produtos[10000];
Encomenda encomendas[500];
int idp = -1;
int ide = -1;
void CopyProd(Produto *colar, Produto copiar)
{
  colar->identificador = copiar.identificador;
  strcpy(colar->descricao, copiar.descricao);
  colar->preco = copiar.preco;
  colar->peso = copiar.peso;
  colar->stock = copiar.stock;
}

void Merge(int a[10000], int ids[10000], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int aux[10000];
  int auxid[10000];
  for (i = m + 1; i > l; i--)
  {
    aux[i - 1] = a[i - 1];
    auxid[i - 1] = ids[i - 1];
  }

  for (j = m; j < r; j++)
  {
    aux[(r + m) - j] = a[j + 1];
    auxid[(r + m) - j] = ids[j + 1];
  }

  for (k = l; k <= r; k++)
  {
    if ((aux[j] < aux[i]) || (i > m))
    {
      a[k] = aux[j--];
      ids[k] = auxid[j + 1];
    }
    else
    {
      a[k] = aux[i++];
      ids[k] = auxid[i - 1];
    }

  }

}

void MergeSort(int a[10000], int ids[10000], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  MergeSort(a, ids, left, m);
  MergeSort(a, ids, m + 1, right);
  Merge(a, ids, left, m, right);
}

void MergeStrings(char strings[200][64], int ordemStr[200], int l, int m, int r)
{
  int i;
  int j;
  int k;
  char aux[200][64];
  int auxOrd[200];
  for (i = m + 1; i > l; i--)
  {
    strcpy(aux[i - 1], strings[i - 1]);
    auxOrd[i - 1] = ordemStr[i - 1];
  }

  for (j = m; j < r; j++)
  {
    strcpy(aux[(r + m) - j], strings[j + 1]);
    auxOrd[(r + m) - j] = ordemStr[j + 1];
  }

  for (k = l; k <= r; k++)
  {
    if (strcmp(aux[j], aux[i]) < 0)
    {
      strcpy(strings[k], aux[j--]);
      ordemStr[k] = auxOrd[j + 1];
    }
    else
    {
      strcpy(strings[k], aux[i++]);
      ordemStr[k] = auxOrd[i - 1];
    }

  }

}

void MergeSortString(char strings[200][64], int ordemStr[200], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  MergeSortString(strings, ordemStr, left, m);
  MergeSortString(strings, ordemStr, m + 1, right);
  MergeStrings(strings, ordemStr, left, m, right);
}

void NovoProduto()
{
  int i = 0;
  char c;
  idp++;
  getchar();
  c = getchar();
  while (c != ':')
  {
    produtos[idp].descricao[i] = c;
    i++;
    c = getchar();
  }

  produtos[idp].preco = new_sym_var(sizeof(int) * 8);
  produtos[idp].peso = new_sym_var(sizeof(int) * 8);
  produtos[idp].stock = new_sym_var(sizeof(int) * 8);
  produtos[idp].identificador = idp;
  printf("Novo produto %d.\n", idp);
}

void AddStock()
{
  int prod;
  int qnt;
  prod = new_sym_var(sizeof(int) * 8);
  qnt = new_sym_var(sizeof(int) * 8);
  if ((prod <= idp) && (prod >= 0))
  {
    produtos[prod].stock += qnt;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prod);
  }

}

void NovaEncomenda()
{
  ide++;
  encomendas[ide].identificador = ide;
  encomendas[ide].numProd = -1;
  encomendas[ide].pesoTotal = 0;
  printf("Nova encomenda %d.\n", ide);
}

void AddProduto()
{
  int i;
  int qnt;
  int n;
  int enc;
  int prod;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  qnt = new_sym_var(sizeof(int) * 8);
  if ((enc > ide) || (enc < 0))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
    return;
  }
  else
  {
    if ((prod > idp) || (prod < 0))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
      return;
    }
    else
    {
      if (qnt > produtos[prod].stock)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod, enc);
        return;
      }
      else
      {
        if ((encomendas[enc].pesoTotal + (qnt * produtos[prod].peso)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod, enc);
          return;
        }
        else
        {
          
        }

      }

    }

  }

  n = encomendas[enc].numProd;
  for (i = 0; i <= n; i++)
  {
    if (prod == encomendas[enc].produtos[i].identificador)
    {
      encomendas[enc].pesoTotal += produtos[prod].peso * qnt;
      encomendas[enc].produtos[i].stock += qnt;
      produtos[prod].stock -= qnt;
      return;
    }
    else
    {
      
    }

  }

  encomendas[enc].numProd++;
  n++;
  encomendas[enc].pesoTotal += produtos[prod].peso * qnt;
  encomendas[enc].produtos[n].identificador = prod;
  encomendas[enc].produtos[n].preco = produtos[prod].preco;
  encomendas[enc].produtos[n].peso = produtos[prod].peso;
  encomendas[enc].produtos[n].stock = qnt;
  produtos[prod].stock -= qnt;
  strcpy(encomendas[enc].produtos[n].descricao, produtos[prod].descricao);
}

void RemStock()
{
  int prod;
  int qnt;
  prod = new_sym_var(sizeof(int) * 8);
  qnt = new_sym_var(sizeof(int) * 8);
  if ((prod <= idp) && (prod >= 0))
  {
    if (produtos[prod].stock >= qnt)
    {
      produtos[prod].stock -= qnt;
    }
    else
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qnt, prod);
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod);
  }

}

void RemProdEnc()
{
  int enc;
  int prod;
  int i;
  int n;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  if ((enc > ide) || (enc < 0))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
    return;
  }
  else
  {
    if ((prod > idp) || (prod < 0))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
      return;
    }
    else
    {
      
    }

  }

  n = encomendas[enc].numProd;
  for (i = 0; i <= n; i++)
  {
    if (prod == encomendas[enc].produtos[i].identificador)
    {
      produtos[prod].stock += encomendas[enc].produtos[i].stock;
      encomendas[enc].pesoTotal -= encomendas[enc].produtos[i].stock * encomendas[enc].produtos[i].peso;
      for (; i <= n; i++)
        CopyProd(&encomendas[enc].produtos[i], encomendas[enc].produtos[i + 1]);

      encomendas[enc].numProd--;
      return;
    }
    else
    {
      
    }

  }

}

void CalcPreco()
{
  int enc;
  int soma = 0;
  int i;
  enc = new_sym_var(sizeof(int) * 8);
  if ((enc > ide) || (enc < 0))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
    return;
  }
  else
  {
    
  }

  for (i = 0; i <= encomendas[enc].numProd; i++)
    soma += encomendas[enc].produtos[i].preco * encomendas[enc].produtos[i].stock;

  printf("Custo da encomenda %d %d.\n", enc, soma);
}

void AltPreco()
{
  int prod;
  int novoPreco;
  int i;
  int e;
  prod = new_sym_var(sizeof(int) * 8);
  novoPreco = new_sym_var(sizeof(int) * 8);
  if ((prod > idp) || (prod < 0))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prod);
    return;
  }
  else
  {
    
  }

  produtos[prod].preco = novoPreco;
  for (i = 0; i <= ide; i++)
  {
    int n = encomendas[i].numProd;
    for (e = 0; e <= n; e++)
      if (prod == encomendas[i].produtos[e].identificador)
    {
      encomendas[i].produtos[e].preco = novoPreco;
      break;
    }
    else
    {
      
    }


  }

}

void ListProdEnc()
{
  int enc;
  int prod;
  int i;
  int n;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  if ((enc > ide) || (enc < 0))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
    return;
  }
  else
  {
    if ((prod > idp) || (prod < 0))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", prod);
      return;
    }
    else
    {
      
    }

  }

  n = encomendas[enc].numProd;
  for (i = 0; i <= n; i++)
    if (prod == encomendas[enc].produtos[i].identificador)
  {
    printf("%s %d.\n", produtos[prod].descricao, encomendas[enc].produtos[i].stock);
    return;
  }
  else
  {
    
  }


  printf("%s 0.\n", produtos[prod].descricao);
}

void ProdMaiorQnt()
{
  int prod;
  int max = 0;
  int enc = -1;
  int i;
  int e;
  prod = new_sym_var(sizeof(int) * 8);
  if ((prod > idp) || (prod < 0))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod);
    return;
  }
  else
  {
    
  }

  for (i = 0; i <= ide; i++)
  {
    int n = encomendas[i].numProd;
    for (e = 0; e <= n; e++)
      if ((prod == encomendas[i].produtos[e].identificador) && (encomendas[i].produtos[e].stock > max))
    {
      max = encomendas[i].produtos[e].stock;
      enc = i;
    }
    else
    {
      
    }


  }

  if (enc != (-1))
  {
    printf("Maximo produto %d %d %d.\n", prod, enc, max);
  }
  else
  {
    
  }

}

void ListPorPreco()
{
  int precosProd[10000];
  int idPrecos[10000];
  int i;
  for (i = 0; i <= idp; i++)
  {
    precosProd[i] = produtos[i].preco;
    idPrecos[i] = i;
  }

  MergeSort(precosProd, idPrecos, 0, idp);
  printf("Produtos\n");
  for (i = 0; i <= idp; i++)
  {
    int e = idPrecos[i];
    printf("* %s %d %d\n", produtos[e].descricao, produtos[e].preco, produtos[e].stock);
  }

}

void ListEncAlf()
{
  int enc;
  int i;
  int n;
  char descs[200][64];
  int ordemDesc[200];
  enc = new_sym_var(sizeof(int) * 8);
  if ((enc > ide) || (enc < 0))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
    return;
  }
  else
  {
    
  }

  n = encomendas[enc].numProd;
  for (i = 0; i <= n; i++)
  {
    strcpy(descs[i], encomendas[enc].produtos[i].descricao);
    ordemDesc[i] = i;
  }

  MergeSortString(descs, ordemDesc, 0, n);
  printf("Encomenda %d\n", enc);
  for (i = 0; i <= n; i++)
    printf("* %s %d %d\n", descs[i], encomendas[enc].produtos[ordemDesc[i]].preco, encomendas[enc].produtos[ordemDesc[i]].stock);

}

int main()
{
  int c = 0;
  c = getchar();
  while (c != 'x')
  {
    if (c == 'a')
    {
      NovoProduto();
    }
    else
    {
      if (c == 'q')
      {
        AddStock();
      }
      else
      {
        if (c == 'N')
        {
          NovaEncomenda();
        }
        else
        {
          if (c == 'A')
          {
            AddProduto();
          }
          else
          {
            if (c == 'r')
            {
              RemStock();
            }
            else
            {
              if (c == 'R')
              {
                RemProdEnc();
              }
              else
              {
                if (c == 'C')
                {
                  CalcPreco();
                }
                else
                {
                  if (c == 'p')
                  {
                    AltPreco();
                  }
                  else
                  {
                    if (c == 'E')
                    {
                      ListProdEnc();
                    }
                    else
                    {
                      if (c == 'm')
                      {
                        ProdMaiorQnt();
                      }
                      else
                      {
                        if (c == 'l')
                        {
                          ListPorPreco();
                        }
                        else
                        {
                          if (c == 'L')
                          {
                            ListEncAlf();
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

    c = getchar();
  }

  return 0;
}

