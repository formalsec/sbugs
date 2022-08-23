/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct produto
{
  int idp;
  char desc[63];
  int preco;
  int peso;
  int qtd;
} Produto;
typedef struct encomenda
{
  int ide;
  int peso;
  Produto lista_prod[200];
} Encomenda;
Produto lista_produtos[10000];
Encomenda lista_encomendas[500];
void a(char *atr1, char *atr2, char *atr3, char *atr4, Produto lista_produtos[]);
void q(char *atr1, char *atr2, Produto lista_produtos[]);
void N(Encomenda lista_encomendas[]);
void A(char *atr1, char *atr2, char *atr3, Produto lista_produtos[], Encomenda lista_encomendas[]);
void r(char *atr1, char *atr2, Produto lista_produtos[]);
void R(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[]);
void C(char *atr1, Encomenda lista_encomendas[]);
void p(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[]);
void E(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[]);
void m(char *atr1, Produto lista_produtos[], Encomenda lista_encomendas[]);
void l(Produto lista_produtos[]);
void L(char *atr1, Encomenda lista_encomendas[]);
int main()
{
  int i;
  int e;
  char *atr1;
  char *atr2;
  char *atr3;
  char *atr4;
  char entrada[1000];
  char *comando;
  for (i = 0; i < 10000; i++)
  {
    lista_produtos[i].idp = -1;
    strcpy(lista_produtos[i].desc, "NULL");
    lista_produtos[i].preco = 0;
    lista_produtos[i].peso = 0;
    lista_produtos[i].qtd = 0;
  }

  for (i = 0; i < 500; i++)
  {
    lista_encomendas[i].ide = -1;
    lista_encomendas[i].peso = 0;
    for (e = 0; e < 200; e++)
    {
      lista_encomendas[i].lista_prod[e].idp = -1;
      strcpy(lista_encomendas[i].lista_prod[e].desc, "NULL");
      lista_encomendas[i].lista_prod[e].preco = 0;
      lista_encomendas[i].lista_prod[e].peso = 0;
      lista_encomendas[i].lista_prod[e].qtd = 0;
    }

  }

  while (1)
  {
    fgets(entrada, 1000, stdin);
    comando = strtok(entrada, " ");
    switch (*comando)
    {
      case 'a':
        atr1 = strtok(0, ":");
        atr2 = strtok(0, ":");
        atr3 = strtok(0, ":");
        atr4 = strtok(0, "\n");
        a(atr1, atr2, atr3, atr4, lista_produtos);
        break;

      case 'q':
        atr1 = strtok(0, ":");
        atr2 = strtok(0, "\n");
        q(atr1, atr2, lista_produtos);
        break;

      case 'N':
        N(lista_encomendas);
        break;

      case 'A':
        atr1 = strtok(0, ":");
        atr2 = strtok(0, ":");
        atr3 = strtok(0, "\n");
        A(atr1, atr2, atr3, lista_produtos, lista_encomendas);
        break;

      case 'r':
        atr1 = strtok(0, ":");
        atr2 = strtok(0, "\n");
        r(atr1, atr2, lista_produtos);
        break;

      case 'R':
        atr1 = strtok(0, ":");
        atr2 = strtok(0, "\n");
        R(atr1, atr2, lista_produtos, lista_encomendas);
        break;

      case 'C':
        atr1 = strtok(0, "\n");
        C(atr1, lista_encomendas);
        break;

      case 'p':
        atr1 = strtok(0, ":");
        atr2 = strtok(0, "\n");
        p(atr1, atr2, lista_produtos, lista_encomendas);
        break;

      case 'E':
        atr1 = strtok(0, ":");
        atr2 = strtok(0, "\n");
        E(atr1, atr2, lista_produtos, lista_encomendas);
        break;

      case 'm':
        atr1 = strtok(0, "\n");
        m(atr1, lista_produtos, lista_encomendas);
        break;

      case 'l':
        l(lista_produtos);
        break;

      case 'L':
        atr1 = strtok(0, "\n");
        L(atr1, lista_encomendas);
        break;

      case 'x':
        exit(0);

    }

  }

}

void a(char *atr1, char *atr2, char *atr3, char *atr4, Produto lista_produtos[])
{
  int i = 0;
  while (lista_produtos[i].idp != (-1))
  {
    i = i + 1;
  }

  lista_produtos[i].idp = i;
  strcpy(lista_produtos[i].desc, atr1);
  lista_produtos[i].preco = atoi(atr2);
  lista_produtos[i].peso = atoi(atr3);
  lista_produtos[i].qtd = atoi(atr4);
  printf("Novo produto %d.\n", i);
}

void q(char *atr1, char *atr2, Produto lista_produtos[])
{
  if (lista_produtos[atoi(atr1)].idp == (-1))
  {
    {
      printf("Impossivel adicionar produto %s ao stock. Produto inexistente.\n", atr1);
    }
  }
  else
  {
    {
      lista_produtos[atoi(atr1)].qtd += atoi(atr2);
    }
  }

}

void N(Encomenda lista_encomendas[])
{
  int i = 0;
  while (lista_encomendas[i].ide != (-1))
  {
    i = i + 1;
  }

  lista_encomendas[i].ide = i;
  printf("Nova encomenda %d.\n", i);
}

void A(char *atr1, char *atr2, char *atr3, Produto lista_produtos[], Encomenda lista_encomendas[])
{
  int i = 0;
  int peso_total = 0;
  int ja_existe = 0;
  peso_total = lista_encomendas[atoi(atr1)].peso + (lista_produtos[atoi(atr2)].peso * atoi(atr3));
  if (lista_encomendas[atoi(atr1)].ide == (-1))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", atoi(atr2), atoi(atr1));
    }
  }
  else
  {
    if (lista_produtos[atoi(atr2)].idp == (-1))
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", atoi(atr2), atoi(atr1));
      }
    }
    else
    {
      if (lista_produtos[atoi(atr2)].qtd < atoi(atr3))
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", atoi(atr2), atoi(atr1));
        }
      }
      else
      {
        if (peso_total > 200)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", atoi(atr2), atoi(atr1));
          }
        }
        else
        {
          {
            for (i = 0; i < 200; i++)
            {
              if (lista_encomendas[atoi(atr1)].lista_prod[i].idp == atoi(atr2))
              {
                {
                  ja_existe = 1;
                }
              }
              else
              {
                
              }

            }

            if (ja_existe == 1)
            {
              {
                i = 0;
                while (lista_encomendas[atoi(atr1)].lista_prod[i].idp != atoi(atr2))
                {
                  i = i + 1;
                }

                lista_encomendas[atoi(atr1)].peso = peso_total;
                lista_encomendas[atoi(atr1)].lista_prod[i].qtd += atoi(atr3);
                lista_produtos[atoi(atr2)].qtd -= atoi(atr3);
              }
            }
            else
            {
              {
                i = 0;
                while (lista_encomendas[atoi(atr1)].lista_prod[i].idp != (-1))
                {
                  i = i + 1;
                }

                lista_encomendas[atoi(atr1)].peso = peso_total;
                lista_encomendas[atoi(atr1)].lista_prod[i].idp = lista_produtos[atoi(atr2)].idp;
                strcpy(lista_encomendas[atoi(atr1)].lista_prod[i].desc, lista_produtos[atoi(atr2)].desc);
                lista_encomendas[atoi(atr1)].lista_prod[i].preco = lista_produtos[atoi(atr2)].preco;
                lista_encomendas[atoi(atr1)].lista_prod[i].peso = lista_produtos[atoi(atr2)].peso;
                lista_encomendas[atoi(atr1)].lista_prod[i].qtd = atoi(atr3);
                lista_produtos[atoi(atr2)].qtd -= atoi(atr3);
              }
            }

          }
        }

      }

    }

  }

}

void r(char *atr1, char *atr2, Produto lista_produtos[])
{
  int qtd_final = lista_produtos[atoi(atr1)].qtd - atoi(atr2);
  if (lista_produtos[atoi(atr1)].idp == (-1))
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", atoi(atr1));
    }
  }
  else
  {
    if (qtd_final < 0)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", atoi(atr2), atoi(atr1));
      }
    }
    else
    {
      {
        lista_produtos[atoi(atr1)].qtd -= atoi(atr2);
      }
    }

  }

}

void R(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[])
{
  int i;
  int j;
  if (lista_encomendas[atoi(atr1)].ide == (-1))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", atoi(atr2), atoi(atr1));
    }
  }
  else
  {
    if (lista_produtos[atoi(atr2)].idp == (-1))
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", atoi(atr2), atoi(atr1));
      }
    }
    else
    {
      {
        for (i = 0; i < 200; i++)
        {
          if (lista_encomendas[atoi(atr1)].lista_prod[i].idp == atoi(atr2))
          {
            {
              while (lista_encomendas[atoi(atr1)].lista_prod[i].idp != atoi(atr2))
              {
                i = i + 1;
              }

              lista_produtos[atoi(atr2)].qtd += lista_encomendas[atoi(atr1)].lista_prod[i].qtd;
              lista_encomendas[atoi(atr1)].peso -= lista_encomendas[atoi(atr1)].lista_prod[i].peso * lista_encomendas[atoi(atr1)].lista_prod[i].qtd;
              for (j = i; j < (200 - 1); j++)
              {
                if (lista_encomendas[atoi(atr1)].lista_prod[j + 1].idp != (-1))
                {
                  {
                    lista_encomendas[atoi(atr1)].lista_prod[j].idp = lista_encomendas[atoi(atr1)].lista_prod[j + 1].idp;
                    strcpy(lista_encomendas[atoi(atr1)].lista_prod[j].desc, lista_encomendas[atoi(atr1)].lista_prod[j + 1].desc);
                    lista_encomendas[atoi(atr1)].lista_prod[j].preco = lista_encomendas[atoi(atr1)].lista_prod[j + 1].preco;
                    lista_encomendas[atoi(atr1)].lista_prod[j].peso = lista_encomendas[atoi(atr1)].lista_prod[j + 1].peso;
                    lista_encomendas[atoi(atr1)].lista_prod[j].qtd = lista_encomendas[atoi(atr1)].lista_prod[j + 1].qtd;
                  }
                }
                else
                {
                  {
                    lista_encomendas[atoi(atr1)].lista_prod[j].idp = -1;
                    strcpy(lista_encomendas[atoi(atr1)].lista_prod[j].desc, "NULL");
                    lista_encomendas[atoi(atr1)].lista_prod[j].preco = 0;
                    lista_encomendas[atoi(atr1)].lista_prod[j].peso = 0;
                    lista_encomendas[atoi(atr1)].lista_prod[j].qtd = 0;
                  }
                }

              }

            }
          }
          else
          {
            
          }

        }

      }
    }

  }

}

void C(char *atr1, Encomenda lista_encomendas[])
{
  int i;
  int custo = 0;
  if (lista_encomendas[atoi(atr1)].ide == (-1))
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", atoi(atr1));
    }
  }
  else
  {
    {
      for (i = 0; i < 200; i++)
      {
        if (lista_encomendas[atoi(atr1)].lista_prod[i].idp != (-1))
        {
          {
            custo += lista_encomendas[atoi(atr1)].lista_prod[i].preco * lista_encomendas[atoi(atr1)].lista_prod[i].qtd;
          }
        }
        else
        {
          
        }

      }

      printf("Custo da encomenda %d %d.\n", atoi(atr1), custo);
    }
  }

}

void p(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[])
{
  int i;
  int e;
  if (lista_produtos[atoi(atr1)].idp == (-1))
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", atoi(atr1));
    }
  }
  else
  {
    {
      for (i = 0; i < 500; i++)
      {
        for (e = 0; e < 200; e++)
        {
          if (lista_encomendas[i].lista_prod[e].idp == atoi(atr1))
          {
            {
              lista_encomendas[i].lista_prod[e].preco = atoi(atr2);
            }
          }
          else
          {
            
          }

        }

      }

      lista_produtos[atoi(atr1)].preco = atoi(atr2);
    }
  }

}

void E(char *atr1, char *atr2, Produto lista_produtos[], Encomenda lista_encomendas[])
{
  int i;
  int existe = 0;
  if (lista_encomendas[atoi(atr1)].ide == (-1))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(atr1));
    }
  }
  else
  {
    if (lista_produtos[atoi(atr2)].idp == (-1))
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", atoi(atr2));
      }
    }
    else
    {
      {
        for (i = 0; i < 200; i++)
        {
          if (lista_encomendas[atoi(atr1)].lista_prod[i].idp == atoi(atr2))
          {
            {
              existe = 1;
            }
          }
          else
          {
            
          }

        }

        if (existe == 1)
        {
          {
            i = 0;
            while (lista_encomendas[atoi(atr1)].lista_prod[i].idp != atoi(atr2))
            {
              i = i + 1;
            }

            printf("%s %d.\n", lista_produtos[atoi(atr2)].desc, lista_encomendas[atoi(atr1)].lista_prod[i].qtd);
          }
        }
        else
        {
          {
            printf("%s 0.\n", lista_produtos[atoi(atr2)].desc);
          }
        }

      }
    }

  }

}

void m(char *atr1, Produto lista_produtos[], Encomenda lista_encomendas[])
{
  int i;
  int e;
  int max = 0;
  int ide = -1;
  if (lista_produtos[atoi(atr1)].idp == (-1))
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", atoi(atr1));
    }
  }
  else
  {
    {
      for (i = 0; i < 500; i++)
      {
        for (e = 0; e < 200; e++)
        {
          if (lista_encomendas[i].lista_prod[e].idp == atoi(atr1))
          {
            {
              if (lista_encomendas[i].lista_prod[e].qtd == max)
              {
                {
                  max = max;
                  ide = ide;
                }
              }
              else
              {
                if (lista_encomendas[i].lista_prod[e].qtd < max)
                {
                  {
                    max = max;
                    ide = ide;
                  }
                }
                else
                {
                  {
                    max = lista_encomendas[i].lista_prod[e].qtd;
                    ide = lista_encomendas[i].ide;
                  }
                }

              }

            }
          }
          else
          {
            
          }

        }

      }

      if ((max != 0) && (ide != (-1)))
      {
        {
          printf("Maximo produto %d %d %d.\n", atoi(atr1), ide, max);
        }
      }
      else
      {
        
      }

    }
  }

}

void l(Produto lista_produtos[])
{
  int i;
  int j;
  Produto p;
  for (i = 0; i < (10000 - 1); i++)
  {
    for (j = 1; j < ((10000 - i) - 1); j++)
    {
      if ((lista_produtos[i].idp != (-1)) && (lista_produtos[i + j].idp != (-1)))
      {
        {
          if (lista_produtos[i].preco > lista_produtos[i + j].preco)
          {
            {
              p = lista_produtos[i];
              lista_produtos[i] = lista_produtos[i + j];
              lista_produtos[i + j] = p;
            }
          }
          else
          {
            
          }

        }
      }
      else
      {
        
      }

    }

  }

  printf("Produtos\n");
  for (i = 0; i < 10000; i++)
  {
    if (lista_produtos[i].idp != (-1))
    {
      {
        printf("* %s %d %d\n", lista_produtos[i].desc, lista_produtos[i].preco, lista_produtos[i].qtd);
      }
    }
    else
    {
      
    }

  }

}

void L(char *atr1, Encomenda lista_encomendas[])
{
  int i;
  int j;
  Produto p;
  if (lista_encomendas[atoi(atr1)].ide == (-1))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(atr1));
    }
  }
  else
  {
    {
      for (i = 0; i < (200 - 1); i++)
      {
        for (j = 1; j < ((200 - i) - 1); j++)
        {
          if ((lista_encomendas[atoi(atr1)].lista_prod[i].idp != (-1)) && (lista_encomendas[atoi(atr1)].lista_prod[i + j].idp != (-1)))
          {
            {
              if (strcmp(lista_encomendas[atoi(atr1)].lista_prod[i].desc, lista_encomendas[atoi(atr1)].lista_prod[i + j].desc) > 0)
              {
                {
                  p = lista_encomendas[atoi(atr1)].lista_prod[i];
                  lista_encomendas[atoi(atr1)].lista_prod[i] = lista_encomendas[atoi(atr1)].lista_prod[i + j];
                  lista_encomendas[atoi(atr1)].lista_prod[i + j] = p;
                }
              }
              else
              {
                
              }

            }
          }
          else
          {
            
          }

        }

      }

      printf("Encomenda %d\n", atoi(atr1));
      for (i = 0; i < 200; i++)
      {
        if (lista_encomendas[atoi(atr1)].lista_prod[i].idp != (-1))
        {
          {
            printf("* %s %d %d\n", lista_encomendas[atoi(atr1)].lista_prod[i].desc, lista_encomendas[atoi(atr1)].lista_prod[i].preco, lista_encomendas[atoi(atr1)].lista_prod[i].qtd);
          }
        }
        else
        {
          
        }

      }

    }
  }

}

