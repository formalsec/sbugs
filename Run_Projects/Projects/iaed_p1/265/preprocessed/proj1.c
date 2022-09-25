/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char line[100];
char *p;
int comando;
int num_produtos = 0;
int num_encomendas = 0;
int num_prod_in_encom[9999];
int peso_inicial = 0;
typedef struct produto
{
  char descricao[64];
  int preco;
  int peso;
  int stock;
  int referencia;
} Produto;
typedef struct encomenda
{
  int id;
  int peso;
  int custo;
  int items[9999];
  struct produto rede[9999];
} Encomenda;
void readLine(char buffer[]);
void criaProduto();
void adicionaStock();
void criaEncomenda();
void adicionaProduto();
void removeStock();
void removeStockEncomenda();
void alteraPreco();
struct produto rede[9999];
struct encomenda track[500];
int main(void)
{
  while (1)
  {
    switch (comando = getchar())
    {
      case 'a':
        criaProduto();
        break;

      case 'q':
        adicionaStock();
        break;

      case 'N':
        criaEncomenda();
        break;

      case 'A':
        adicionaProduto();
        break;

      case 'r':
        removeStock();
        break;

      case 'R':
        removeStockEncomenda();
        break;

      case 'C':
        break;

      case 'p':
        alteraPreco();
        break;

      case 'E':
        break;

      case 'm':
        break;

      case 'l':
        break;

      case 'L':
        break;

      case 'x':
        break;

      case 'k':
        break;

      default:
        printf("[ERRO Comando n?o reconhecido]\n");
        break;

    }

    getchar();
  }

  return -1;
}

void criaProduto()
{
  char descricao[64];
  int preco;
  int peso;
  int stock;
  getchar();
  readLine(line);
  p = strtok(line, ":");
  strcpy(descricao, p);
  preco = atoi(strtok(0, ":"));
  peso = atoi(strtok(0, ":"));
  stock = atoi(strtok(0, ":"));
  strcpy(rede[num_produtos].descricao, descricao);
  rede[num_produtos].preco = preco;
  rede[num_produtos].peso = peso;
  rede[num_produtos].stock = stock;
  rede[num_produtos].referencia = num_produtos;
  printf("Novo produto %d.\n", num_produtos);
  num_produtos++;
}

void adicionaStock()
{
  int referencia;
  int stock;
  int i;
  getchar();
  readLine(line);
  referencia = atoi(strtok(line, ":"));
  stock = atoi(strtok(0, ":"));
  if (num_produtos == 0)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", referencia);
  }
  else
  {
    for (i = 0; i < num_produtos; i++)
    {
      if (referencia > (num_produtos - 1))
      {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", referencia);
        break;
      }
      else
      {
        if (i != referencia)
        {
          continue;
        }
        else
        {
          rede[referencia].stock += stock;
          break;
        }

      }

    }

  }

}

void criaEncomenda()
{
  getchar();
  track[num_encomendas].id = num_encomendas;
  printf("Nova encomenda %d.\n", track[num_encomendas].id);
  num_encomendas++;
}

void adicionaProduto()
{
  int id;
  int referencia;
  int stock;
  int i;
  getchar();
  readLine(line);
  id = atoi(strtok(line, ":"));
  referencia = atoi(strtok(0, ":"));
  stock = atoi(strtok(0, ":"));
  if ((num_encomendas == 0) || (id > (num_encomendas - 1)))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", referencia, id);
  }
  else
  {
    if (referencia > (num_produtos - 1))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", referencia, id);
    }
    else
    {
      if (stock > rede[referencia].stock)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", referencia, id);
      }
      else
      {
        if (((rede[referencia].peso * stock) + track[id].peso) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", referencia, id);
        }
        else
        {
          if (num_prod_in_encom == 0)
          {
            strcpy(track[id].rede[num_prod_in_encom[id]].descricao, rede[referencia].descricao);
            track[id].rede[num_prod_in_encom[id]].preco = rede[referencia].preco;
            track[id].rede[num_prod_in_encom[id]].peso = rede[referencia].peso;
            track[id].rede[num_prod_in_encom[id]].stock = stock;
            track[id].peso = rede[referencia].peso * stock;
            rede[referencia].stock -= stock;
            num_prod_in_encom[id]++;
          }
          else
          {
            for (i = 0; i <= (num_prod_in_encom[id] + 1); i++)
            {
              if ((strcmp(track[id].rede[i].descricao, rede[referencia].descricao) == 0) && (i < num_prod_in_encom[id]))
              {
                track[id].rede[i].stock += stock;
                track[id].peso += rede[referencia].peso * stock;
                rede[referencia].stock -= stock;
                num_prod_in_encom[id]++;
                break;
              }
              else
              {
                if ((strcmp(track[id].rede[i].descricao, rede[referencia].descricao) != 0) && (i < num_prod_in_encom[id]))
                {
                  continue;
                }
                else
                {
                  if ((strcmp(track[id].rede[i].descricao, rede[referencia].descricao) != 0) && (i == num_prod_in_encom[id]))
                  {
                    strcpy(track[id].rede[num_prod_in_encom[id]].descricao, rede[referencia].descricao);
                    track[id].rede[num_prod_in_encom[id]].preco = rede[referencia].preco;
                    track[id].rede[num_prod_in_encom[id]].peso = rede[referencia].peso;
                    track[id].rede[num_prod_in_encom[id]].stock = stock;
                    track[id].peso += rede[referencia].peso * stock;
                    rede[referencia].stock -= stock;
                    num_prod_in_encom[id]++;
                    break;
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

void removeStock()
{
  int referencia;
  int stock;
  getchar();
  readLine(line);
  referencia = atoi(strtok(line, ":"));
  stock = atoi(strtok(0, ":"));
  if ((num_produtos == 0) || (referencia > (num_produtos - 1)))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", referencia);
  }
  else
  {
    if (rede[referencia].stock < stock)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock, referencia);
    }
    else
    {
      rede[referencia].stock -= stock;
    }

  }

}

void removeStockEncomenda()
{
  int id;
  int referencia;
  int i;
  getchar();
  readLine(line);
  id = atoi(strtok(line, ":"));
  referencia = atoi(strtok(0, ":"));
  if ((num_encomendas == 0) || (id > (num_encomendas - 1)))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", referencia, id);
  }
  else
  {
    if ((num_produtos == 0) || (referencia > (num_produtos - 1)))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", referencia, id);
    }
    else
    {
      for (i = 0; i <= num_prod_in_encom[id]; i++)
      {
        if ((strcmp(track[id].rede[i].descricao, rede[referencia].descricao) == 0) && (i < num_prod_in_encom[id]))
        {
          strcpy(track[id].rede[num_prod_in_encom[id]].descricao, "\0");
          track[id].rede[num_prod_in_encom[id]].preco = 0;
          track[id].peso -= rede[referencia].peso * track[id].rede[num_prod_in_encom[id]].stock;
          track[id].rede[num_prod_in_encom[id]].peso = 0;
          rede[referencia].stock += track[id].rede[num_prod_in_encom[id]].stock;
          track[id].rede[num_prod_in_encom[id]].stock = 0;
          num_prod_in_encom[id]--;
        }
        else
        {
          
        }

      }

    }

  }

}

void alteraPreco()
{
  int referencia;
  int preco;
  int i;
  getchar();
  readLine(line);
  referencia = atoi(strtok(line, ":"));
  preco = atoi(strtok(0, ":"));
  if (num_produtos == 0)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.", referencia);
  }
  else
  {
    for (i = 0; i < num_produtos; i++)
    {
      if (referencia > (num_produtos - 1))
      {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.", referencia);
        break;
      }
      else
      {
        if (i != referencia)
        {
          continue;
        }
        else
        {
          rede[referencia].preco = preco;
          printf("Preco atualizado:%d\n", rede[i].preco);
          break;
        }

      }

    }

  }

}

void readLine(char buffer[])
{
  int i = 0;
  char character;
  do
  {
    character = getchar();
    buffer[i] = character;
    ++i;
  }
  while (character != '\n');
  buffer[i - 1] = '\0';
}

