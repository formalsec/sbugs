/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  int idp;
  char descricao[64];
  int preco;
  int peso;
  int qtd;
} produto;
produto geral[10000];
int next_idp = 0;
typedef struct encomenda
{
  int ide;
  produto conteudo[200];
  int preco;
  int peso;
  int next_prod;
} encomenda;
encomenda pedidos[500];
int next_ide = 0;
int aux[10000];
int a[10000];
char nomes[500][64];
char copia[64];
char comando;
produto adiciona_sistema()
{
  produto novo;
  char desc[64];
  int price;
  int weight;
  int quant;
  int i;
  for (int desc_index = 0; desc_index < 10; desc_index++)
  {
    desc[desc_index] = new_sym_var(sizeof(char) * 8);
  }

  desc[10 - 1] = '\0';
  price = new_sym_var(sizeof(int) * 8);
  weight = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  novo.idp = next_idp;
  for (i = 0; desc[i] != '\0'; i++)
  {
    novo.descricao[i] = desc[i];
  }

  novo.descricao[i] = '\0';
  novo.preco = price;
  novo.peso = weight;
  novo.qtd = quant;
  return novo;
}

void adiciona_stock()
{
  int prod;
  int somar;
  prod = new_sym_var(sizeof(int) * 8);
  somar = new_sym_var(sizeof(int) * 8);
  if (prod < next_idp)
  {
    geral[prod].qtd += somar;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prod);
  }

}

void lista_auxiliar()
{
  int i;
  printf("Produtos\n");
  for (i = 0; i < next_idp; i++)
  {
    printf("* %s id%d %d %d em stock\n", geral[i].descricao, geral[i].idp, geral[i].preco, geral[i].qtd);
  }

}

void cria_encomenda()
{
  encomenda nova;
  nova.ide = next_ide;
  nova.preco = 0;
  nova.peso = 0;
  nova.next_prod = 0;
  pedidos[next_ide] = nova;
  printf("Nova encomenda %d.\n", next_ide);
}

void adiciona_prod_encomenda()
{
  int enc;
  int prod;
  int quant;
  int i;
  int verif = 0;
  int repetido = 0;
  produto acrescentar;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (enc >= next_ide)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
  }
  else
  {
    if (prod >= next_idp)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
    }
    else
    {
      if (geral[prod].qtd < quant)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod, enc);
      }
      else
      {
        if ((pedidos[enc].peso + (quant * geral[prod].peso)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod, enc);
        }
        else
        {
          if (pedidos[enc].next_prod != 0)
          {
            for (i = 0; i < pedidos[enc].next_prod; i++)
            {
              if (pedidos[enc].conteudo[i].idp == prod)
              {
                verif += i;
                repetido = 1;
              }
              else
              {
                
              }

            }

            if ((verif == 0) && (repetido != 0))
            {
              pedidos[enc].conteudo[verif].qtd += quant;
            }
            else
            {
              
            }

          }
          else
          {
            
          }

          if ((verif == 0) && (repetido == 0))
          {
            acrescentar = geral[prod];
            acrescentar.qtd = quant;
            pedidos[enc].conteudo[pedidos[enc].next_prod] = acrescentar;
            pedidos[enc].next_prod += 1;
          }
          else
          {
            if ((verif != 0) && (repetido != 0))
            {
              pedidos[enc].conteudo[verif].qtd += quant;
            }
            else
            {
              
            }

          }

          geral[prod].qtd -= quant;
          pedidos[enc].preco += geral[prod].preco * quant;
          pedidos[enc].peso += geral[prod].peso * quant;
        }

      }

    }

  }

}

void encomenda_auxiliar()
{
  int i;
  int id;
  id = new_sym_var(sizeof(int) * 8);
  if (id >= next_ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id);
  }
  else
  {
    printf("Encomenda %d\n", id);
    for (i = 0; i < pedidos[id].next_prod; i++)
    {
      printf("* %s %d %d na %d\n", pedidos[id].conteudo[i].descricao, pedidos[id].conteudo[i].preco, pedidos[id].conteudo[i].qtd, id);
    }

  }

}

void remove_stock()
{
  int prod;
  int quant;
  prod = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (prod >= next_idp)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod);
  }
  else
  {
    if (quant > geral[prod].qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, prod);
    }
    else
    {
      geral[prod].qtd -= quant;
    }

  }

}

void remove_prod_encomenda()
{
  int enc;
  int prod;
  int i;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  if (enc >= next_ide)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
  }
  else
  {
    if (prod >= next_idp)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
    }
    else
    {
      for (i = 0; i < pedidos[enc].next_prod; i++)
      {
        if (pedidos[enc].conteudo[i].idp == prod)
        {
          pedidos[enc].preco -= pedidos[enc].conteudo[i].preco * pedidos[enc].conteudo[i].qtd;
          pedidos[enc].peso -= pedidos[enc].conteudo[i].peso * pedidos[enc].conteudo[i].qtd;
          geral[prod].qtd += pedidos[enc].conteudo[i].qtd;
          pedidos[enc].conteudo[i].qtd = 0;
        }
        else
        {
          
        }

      }

    }

  }

}

void calcula_custo()
{
  int enc;
  enc = new_sym_var(sizeof(int) * 8);
  if (enc >= next_ide)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", enc, pedidos[enc].preco);
  }

}

void altera_custo()
{
  int prod;
  int custo;
  int i;
  int j;
  prod = new_sym_var(sizeof(int) * 8);
  custo = new_sym_var(sizeof(int) * 8);
  if (prod >= next_idp)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prod);
  }
  else
  {
    geral[prod].preco = custo;
    for (i = 0; i < next_ide; i++)
    {
      for (j = 0; j < pedidos[i].next_prod; j++)
      {
        if (pedidos[i].conteudo[j].idp == prod)
        {
          pedidos[i].preco -= pedidos[i].conteudo[j].preco * pedidos[i].conteudo[j].qtd;
          pedidos[i].conteudo[j].preco = custo;
          pedidos[i].preco += pedidos[i].conteudo[j].preco * pedidos[i].conteudo[j].qtd;
        }
        else
        {
          
        }

      }

    }

  }

}

void lista_prod_encomenda()
{
  int enc;
  int prod;
  int i;
  int verif = 0;
  int existe = 0;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  if (enc >= next_ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    if (prod >= next_idp)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", prod);
    }
    else
    {
      for (i = 0; i < pedidos[enc].next_prod; i++)
      {
        if (pedidos[enc].conteudo[i].idp == prod)
        {
          verif += i;
          existe = 1;
        }
        else
        {
          
        }

      }

      if ((verif == 0) && (existe == 0))
      {
        printf("%s %d.\n", geral[prod].descricao, verif);
      }
      else
      {
        printf("%s %d.\n", geral[prod].descricao, pedidos[enc].conteudo[verif].qtd);
      }

    }

  }

}

void lista_maior_quantidade()
{
  int prod;
  int i;
  int j;
  int maior_enc;
  int maior = 0;
  prod = new_sym_var(sizeof(int) * 8);
  if (prod >= next_idp)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod);
  }
  else
  {
    for (i = 0; i < next_ide; i++)
    {
      for (j = 0; j < pedidos[i].next_prod; j++)
      {
        if ((pedidos[i].conteudo[j].idp == prod) && (pedidos[i].conteudo[j].qtd > maior))
        {
          maior = pedidos[i].conteudo[j].qtd;
          maior_enc = i;
        }
        else
        {
          
        }

      }

    }

    if (maior != 0)
    {
      printf("Maximo produto %d %d %d.\n", prod, maior_enc, maior);
    }
    else
    {
      
    }

  }

}

void mergesort(int a[], int l, int r);
void merge(int a[], int l, int m, int r);
void lista_ordem_sistema()
{
  int i;
  int j;
  for (i = 0; i < next_idp; i++)
  {
    a[i] = geral[i].preco;
  }

  mergesort(a, 0, next_idp - 1);
  printf("Produtos\n");
  for (i = 0; i < next_idp; i++)
  {
    if (a[i] != a[i - 1])
    {
      for (j = 0; j < next_idp; j++)
      {
        if (a[i] == geral[j].preco)
        {
          printf("* %s %d %d\n", geral[j].descricao, geral[j].preco, geral[j].qtd);
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

void lista_ordem_encomenda()
{
  int enc;
  int i;
  int j;
  enc = new_sym_var(sizeof(int) * 8);
  if (enc >= next_ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    for (i = 0; i < pedidos[enc].next_prod; i++)
    {
      strcpy(nomes[i], pedidos[enc].conteudo[i].descricao);
    }

    for (i = 0; i < pedidos[enc].next_prod; i++)
    {
      for (j = i + 1; j < pedidos[enc].next_prod; j++)
      {
        if (strcmp(nomes[i], nomes[j]) > 0)
        {
          strcpy(copia, nomes[i]);
          strcpy(nomes[i], nomes[j]);
          strcpy(nomes[j], copia);
        }
        else
        {
          
        }

      }

    }

    printf("Encomenda %d\n", enc);
    for (i = 0; i < pedidos[enc].next_prod; i++)
    {
      for (j = 0; j < pedidos[enc].next_prod; j++)
      {
        if ((strcmp(nomes[i], pedidos[enc].conteudo[j].descricao) == 0) && (pedidos[enc].conteudo[j].qtd > 0))
        {
          printf("* %s %d %d\n", pedidos[enc].conteudo[j].descricao, pedidos[enc].conteudo[j].preco, pedidos[enc].conteudo[j].qtd);
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void mergesort(int a[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort(a, l, m);
  mergesort(a, m + 1, r);
  merge(a, l, m, r);
}

void merge(int a[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
  {
    aux[i - 1] = a[i - 1];
  }

  for (j = m; j < r; j++)
  {
    aux[(r + m) - j] = a[j + 1];
  }

  for (k = l; k <= r; k++)
  {
    if ((aux[j] < aux[i]) || (i > m))
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }

  }

}

int main()
{
  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      case 'a':
        geral[next_idp] = adiciona_sistema();
        printf("Novo produto %d.\n", next_idp);
        next_idp += 1;
        break;

      case 'q':
        adiciona_stock();
        break;

      case 'N':
        cria_encomenda();
        next_ide += 1;
        break;

      case 'A':
        adiciona_prod_encomenda();
        break;

      case 'r':
        remove_stock();
        break;

      case 'R':
        remove_prod_encomenda();
        break;

      case 'C':
        calcula_custo();
        break;

      case 'p':
        altera_custo();
        break;

      case 'E':
        lista_prod_encomenda();
        break;

      case 'm':
        lista_maior_quantidade();
        break;

      case 'l':
        lista_ordem_sistema();
        break;

      case 'L':
        lista_ordem_encomenda();
        break;

      case 'k':
        lista_auxiliar();
        break;

      case 'K':
        encomenda_auxiliar();
        break;

    }

    getchar();
  }

  return 0;
}

