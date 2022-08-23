/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct produto
{
  int idedoproduto;
  char nomedoproduto[63];
  int precodoproduto;
  int pesodoproduto;
  int qtddoproduto;
} produto;
typedef struct encomenda
{
  int idedaencomenda;
  int pesodaencomenda;
  int infoencomenda[200][2];
} encomenda;
produto loja[10000];
encomenda encomendas[500];
int lerlinha(char linha[])
{
  char c;
  int i = 0;
  while ((c = getchar()) != '\n')
  {
    linha[i] = c;
    i++;
  }

  linha[i] = '\0';
  return 0;
}

int separarstring(char linha[], char dadosdoinput[][63])
{
  int i;
  int a = 0;
  int b = 0;
  int c = 0;
  for (i = 0; i < 4; i++)
  {
    strncpy(dadosdoinput[i], "", 63);
  }

  while (linha[c] != '\0')
  {
    if (linha[c] == ':')
    {
      {
        dadosdoinput[a][b] = '\0';
        b = 0;
        a++;
      }
    }
    else
    {
      {
        dadosdoinput[a][b] = linha[c];
        b++;
      }
    }

    c++;
  }

  return 0;
}

void merge(int l, int r, int m, int tabela_indices[], int alfabetica)
{
  int a;
  int b;
  int c;
  int tabela_auxiliar[10000];
  int tabela_alfabetica[200];
  if (alfabetica == 0)
  {
    {
      for (a = m + 1; a > l; a--)
      {
        tabela_auxiliar[a - 1] = tabela_indices[a - 1];
      }

      for (b = m; b < r; b++)
      {
        tabela_auxiliar[(r + m) - b] = tabela_indices[b + 1];
      }

      for (c = l; c <= r; c++)
      {
        if (loja[tabela_auxiliar[b]].precodoproduto < loja[tabela_auxiliar[a]].precodoproduto)
        {
          {
            tabela_indices[c] = tabela_auxiliar[b--];
          }
        }
        else
        {
          if ((loja[tabela_auxiliar[b]].idedoproduto < loja[tabela_auxiliar[a]].idedoproduto) && (loja[tabela_auxiliar[b]].precodoproduto == loja[tabela_auxiliar[a]].precodoproduto))
          {
            {
              tabela_indices[c] = tabela_auxiliar[b--];
            }
          }
          else
          {
            {
              tabela_indices[c] = tabela_auxiliar[a++];
            }
          }

        }

      }

    }
  }
  else
  {
    {
      for (a = m + 1; a > l; a--)
      {
        tabela_alfabetica[a - 1] = tabela_indices[a - 1];
      }

      for (b = m; b < r; b++)
      {
        tabela_alfabetica[(r + m) - b] = tabela_indices[b + 1];
      }

      for (c = l; c <= r; c++)
      {
        if (strcmp(loja[tabela_alfabetica[b]].nomedoproduto, loja[tabela_alfabetica[a]].nomedoproduto) < 0)
        {
          {
            tabela_indices[c] = tabela_alfabetica[b--];
          }
        }
        else
        {
          {
            tabela_indices[c] = tabela_alfabetica[a++];
          }
        }

      }

    }
  }

}

void mergesort(int tabela_indices[], int l, int r, int alfabetica)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort(tabela_indices, l, m, alfabetica);
  mergesort(tabela_indices, m + 1, r, alfabetica);
  merge(l, r, m, tabela_indices, alfabetica);
}

void addproduto()
{
  int i = 0;
  int a = 0;
  char linha[63];
  char dadosdoinput[4][63];
  getchar();
  lerlinha(linha);
  separarstring(linha, dadosdoinput);
  while (i < 10000)
  {
    if (loja[i].idedoproduto != (-1))
    {
      {
        a++;
      }
    }
    else
    {
      {
        break;
      }
    }

    i++;
  }

  loja[a].idedoproduto = a;
  strcpy(loja[a].nomedoproduto, dadosdoinput[0]);
  loja[a].precodoproduto = atoi(dadosdoinput[1]);
  loja[a].pesodoproduto = atoi(dadosdoinput[2]);
  loja[a].qtddoproduto = atoi(dadosdoinput[3]);
  printf("Novo produto %d.\n", a);
}

void addstock()
{
  char linha[63];
  char dadosdoinput[4][63];
  getchar();
  lerlinha(linha);
  separarstring(linha, dadosdoinput);
  if (loja[atoi(dadosdoinput[0])].idedoproduto != (-1))
  {
    {
      loja[atoi(dadosdoinput[0])].qtddoproduto += atoi(dadosdoinput[1]);
    }
  }
  else
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", atoi(dadosdoinput[0]));
    }
  }

}

void criaencomenda()
{
  int i = 0;
  int a = 0;
  getchar();
  while (i < 500)
  {
    if (encomendas[i].idedaencomenda != (-1))
    {
      a++;
    }
    else
    {
      break;
    }

    i++;
  }

  encomendas[i].idedaencomenda = a;
  printf("Nova encomenda %d.\n", a);
}

void addqtdprodutoaencomenda()
{
  int i;
  char linha[63];
  char dadosdoinput[4][63];
  getchar();
  lerlinha(linha);
  separarstring(linha, dadosdoinput);
  if (encomendas[atoi(dadosdoinput[0])].idedaencomenda != (-1))
  {
    {
      if (loja[atoi(dadosdoinput[1])].idedoproduto != (-1))
      {
        {
          if (loja[atoi(dadosdoinput[1])].qtddoproduto >= atoi(dadosdoinput[2]))
          {
            {
              if (((atoi(dadosdoinput[2]) * loja[atoi(dadosdoinput[1])].pesodoproduto) + encomendas[atoi(dadosdoinput[0])].pesodaencomenda) <= 200)
              {
                {
                  for (i = 0; i < 200; i++)
                  {
                    if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] == atoi(dadosdoinput[1]))
                    {
                      {
                        encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1] += atoi(dadosdoinput[2]);
                        loja[atoi(dadosdoinput[1])].qtddoproduto -= atoi(dadosdoinput[2]);
                        encomendas[atoi(dadosdoinput[0])].pesodaencomenda += atoi(dadosdoinput[2]) * loja[atoi(dadosdoinput[1])].pesodoproduto;
                        break;
                      }
                    }
                    else
                    {
                      if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] == (-1))
                      {
                        {
                          encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] = atoi(dadosdoinput[1]);
                          encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1] = atoi(dadosdoinput[2]);
                          loja[atoi(dadosdoinput[1])].qtddoproduto -= atoi(dadosdoinput[2]);
                          encomendas[atoi(dadosdoinput[0])].pesodaencomenda += atoi(dadosdoinput[2]) * loja[atoi(dadosdoinput[1])].pesodoproduto;
                          break;
                        }
                      }
                      else
                      {
                        
                      }

                    }

                  }

                }
              }
              else
              {
                {
                  printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
                }
              }

            }
          }
          else
          {
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
            }
          }

        }
      }
      else
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
        }
      }

    }
  }
  else
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
    }
  }

}

void removestock()
{
  char linha[63];
  char dadosdoinput[4][63];
  getchar();
  lerlinha(linha);
  separarstring(linha, dadosdoinput);
  if (loja[atoi(dadosdoinput[0])].idedoproduto != (-1))
  {
    {
      if (loja[atoi(dadosdoinput[0])].qtddoproduto >= atoi(dadosdoinput[1]))
      {
        {
          loja[atoi(dadosdoinput[0])].qtddoproduto -= atoi(dadosdoinput[1]);
        }
      }
      else
      {
        {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
        }
      }

    }
  }
  else
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", atoi(dadosdoinput[0]));
    }
  }

}

void removeprodutodaencomenda()
{
  int i;
  int quantidade;
  int indice;
  char linha[63];
  char dadosdoinput[4][63];
  getchar();
  lerlinha(linha);
  separarstring(linha, dadosdoinput);
  if (encomendas[atoi(dadosdoinput[0])].idedaencomenda != (-1))
  {
    {
      if (loja[atoi(dadosdoinput[1])].idedoproduto != (-1))
      {
        {
          for (i = 0; i < 200; i++)
          {
            if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] == atoi(dadosdoinput[1]))
            {
              {
                quantidade = encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1];
                indice = encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0];
                encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1] = 0;
                encomendas[atoi(dadosdoinput[0])].pesodaencomenda -= quantidade * loja[atoi(dadosdoinput[1])].pesodoproduto;
                loja[indice].qtddoproduto += quantidade;
              }
            }
            else
            {
              
            }

          }

        }
      }
      else
      {
        {
          printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
        }
      }

    }
  }
  else
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
    }
  }

}

void custoencomenda()
{
  int i;
  int indice;
  int quantidade;
  int custo = 0;
  char linha[63];
  char dadosdoinput[4][63];
  getchar();
  lerlinha(linha);
  separarstring(linha, dadosdoinput);
  if (encomendas[atoi(dadosdoinput[0])].idedaencomenda != (-1))
  {
    {
      for (i = 0; i < 200; i++)
      {
        if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] != (-1))
        {
          {
            indice = encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0];
            quantidade = encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1];
            custo += loja[indice].precodoproduto * quantidade;
          }
        }
        else
        {
          
        }

      }

      printf("Custo da encomenda %d %d.\n", atoi(dadosdoinput[0]), custo);
    }
  }
  else
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", atoi(dadosdoinput[0]));
    }
  }

}

void alteraprecodoproduto()
{
  char linha[63];
  char dadosdoinput[4][63];
  getchar();
  lerlinha(linha);
  separarstring(linha, dadosdoinput);
  if (loja[atoi(dadosdoinput[0])].idedoproduto != (-1))
  {
    {
      loja[atoi(dadosdoinput[0])].precodoproduto = atoi(dadosdoinput[1]);
    }
  }
  else
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", atoi(dadosdoinput[0]));
    }
  }

}

void descqtdprodutonaencomenda()
{
  int i;
  int quantidade = 0;
  char linha[63];
  char dadosdoinput[4][63];
  getchar();
  lerlinha(linha);
  separarstring(linha, dadosdoinput);
  if (encomendas[atoi(dadosdoinput[0])].idedaencomenda != (-1))
  {
    {
      if (loja[atoi(dadosdoinput[1])].idedoproduto != (-1))
      {
        {
          for (i = 0; i < 200; i++)
          {
            if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] == atoi(dadosdoinput[1]))
            {
              {
                quantidade += encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1];
              }
            }
            else
            {
              
            }

          }

          printf("%s %d.\n", loja[atoi(dadosdoinput[1])].nomedoproduto, quantidade);
        }
      }
      else
      {
        {
          printf("Impossivel listar produto %d. Produto inexistente.\n", atoi(dadosdoinput[1]));
        }
      }

    }
  }
  else
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(dadosdoinput[0]));
    }
  }

}

int encomendacommaisproduto()
{
  int i;
  int j;
  int qtdmax = 0;
  int idedaencomendacomqtdmax;
  char linha[63];
  char dadosdoinput[4][63];
  getchar();
  lerlinha(linha);
  separarstring(linha, dadosdoinput);
  if (loja[atoi(dadosdoinput[0])].idedoproduto != (-1))
  {
    {
      for (i = 0; i < 500; i++)
      {
        if (encomendas[i].idedaencomenda != (-1))
        {
          {
            for (j = 0; j < 200; j++)
            {
              if ((encomendas[i].infoencomenda[j][0] == atoi(dadosdoinput[0])) && (qtdmax < encomendas[i].infoencomenda[j][1]))
              {
                {
                  qtdmax = encomendas[i].infoencomenda[j][1];
                  idedaencomendacomqtdmax = encomendas[i].idedaencomenda;
                }
              }
              else
              {
                
              }

            }

          }
        }
        else
        {
          break;
        }

      }

      if (qtdmax != 0)
      {
        {
          printf("Maximo produto %d %d %d.\n", atoi(dadosdoinput[0]), idedaencomendacomqtdmax, qtdmax);
        }
      }
      else
      {
        
      }

    }
  }
  else
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", atoi(dadosdoinput[0]));
    }
  }

  return 0;
}

void ordemdeprodutos()
{
  int tabela_indices[10000];
  int r = 0;
  int i;
  int j;
  for (i = 0; i < 10000; i++)
  {
    if (loja[i].idedoproduto != (-1))
    {
      {
        tabela_indices[i] = loja[i].idedoproduto;
        r++;
      }
    }
    else
    {
      break;
    }

  }

  mergesort(tabela_indices, 0, r - 1, 0);
  printf("Produtos\n");
  for (j = 0; j < r; j++)
  {
    printf("* %s %d %d\n", loja[tabela_indices[j]].nomedoproduto, loja[tabela_indices[j]].precodoproduto, loja[tabela_indices[j]].qtddoproduto);
  }

}

void ordemalfabeticadeprodnumaencomenda()
{
  int tabela_idpnaencomenda[200];
  int r = 0;
  int i;
  int j;
  char linha[63];
  char dadosdoinput[4][63];
  getchar();
  lerlinha(linha);
  separarstring(linha, dadosdoinput);
  if (encomendas[atoi(dadosdoinput[0])].idedaencomenda != (-1))
  {
    {
      for (i = 0; i < 200; i++)
      {
        if ((encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] != (-1)) && (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1] > 0))
        {
          {
            tabela_idpnaencomenda[r] = i;
            r++;
          }
        }
        else
        {
          break;
        }

      }

      mergesort(tabela_idpnaencomenda, 0, r - 1, 1);
      printf("Encomenda %d\n", atoi(dadosdoinput[0]));
      for (j = 0; j < r; j++)
      {
        printf("* %s %d %d\n", loja[tabela_idpnaencomenda[j]].nomedoproduto, loja[tabela_idpnaencomenda[j]].precodoproduto, encomendas[atoi(dadosdoinput[0])].infoencomenda[tabela_idpnaencomenda[j]][1]);
      }

    }
  }
  else
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(dadosdoinput[0]));
    }
  }

}

int main()
{
  int i;
  int j;
  int k;
  int command;
  int run = 1;
  for (i = 0; i < 10000; i++)
  {
    loja[i].idedoproduto = -1;
  }

  for (j = 0; j < 500; j++)
  {
    encomendas[j].pesodaencomenda = 0;
    encomendas[j].idedaencomenda = -1;
    for (k = 0; k < 200; k++)
    {
      encomendas[j].infoencomenda[k][0] = -1;
    }

  }

  while (run)
  {
    command = getchar();
    switch (command)
    {
      case 'a':
        addproduto();
        break;

      case 'q':
        addstock();
        break;

      case 'N':
        criaencomenda();
        break;

      case 'A':
        addqtdprodutoaencomenda();
        break;

      case 'r':
        removestock();
        break;

      case 'R':
        removeprodutodaencomenda();
        break;

      case 'C':
        custoencomenda();
        break;

      case 'p':
        alteraprecodoproduto();
        break;

      case 'E':
        descqtdprodutonaencomenda();
        break;

      case 'm':
        encomendacommaisproduto();
        break;

      case 'l':
        ordemdeprodutos();
        break;

      case 'L':
        ordemalfabeticadeprodnumaencomenda();
        break;

      case 'x':
        run = 0;
        break;

    }

  }

  return 0;
}

