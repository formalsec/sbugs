/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h> 


int ip = 0;
int ie = 0;
typedef struct produto
{
  char desc[63];
  int preco;
  int peso;
  int qtd;
} produto;
produto stock[10000] = {{"", 0, 0, 0}};
produto encomenda[500][10000] = {{{"", 0, 0, 0}}};
void ad_produto();
void ad_stock();
void nova_encomenda();
void ad_encomenda();
int peso(int ide);
void remove_stock();
void remove_encomenda();
void custo();
void alt_preco();
void desc_quant();
void max_produto();
void lista_stock();
void lista_encomenda();
void mergesort(int lista[10000], int esquerda, int direita, int criterio);
void merge(int lista[10000], int esquerda, int m, int direita, int criterio);
int condicao(int criterio, int a, int b);
void imprime_lista(int lista[10000], int i_max, produto vetor[10000]);
int main()
{
  char letra;
  while (1)
  {
    switch (letra = getchar())
    {
      case 'a':
        ad_produto();
        break;

      case 'q':
        ad_stock();
        break;

      case 'N':
        nova_encomenda();
        break;

      case 'A':
        ad_encomenda();
        break;

      case 'r':
        remove_stock();
        break;

      case 'R':
        remove_encomenda();
        break;

      case 'C':
        custo();
        break;

      case 'p':
        alt_preco();
        break;

      case 'E':
        desc_quant();
        break;

      case 'm':
        max_produto();
        break;

      case 'l':
        lista_stock();
        break;

      case 'L':
        lista_encomenda();
        break;

      case 'x':
        return 0;

    }

  }

}

void ad_produto()
{
  for (int stock_index = 0; stock_index < 10; stock_index++)
  {
    stock[ip].desc[stock_index] = new_sym_var(sizeof(char) * 8);
  }

  stock[ip].desc[10 - 1] = '\0';
  stock[ip].preco = new_sym_var(sizeof(int) * 8);
  stock[ip].peso = new_sym_var(sizeof(int) * 8);
  stock[ip].qtd = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", ip);
  ip++;
}

void ad_stock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= ip)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    stock[idp].qtd += qtd;
  }

}

void nova_encomenda()
{
  printf("Nova encomenda %d.\n", ie);
  ie++;
}

int peso(int ide)
{
  int idp;
  int peso_total = 0;
  for (idp = 0; idp < ip; idp++)
    peso_total += stock[idp].peso * encomenda[ide][idp].qtd;

  return peso_total;
}

void ad_encomenda()
{
  int ide;
  int idp;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ide >= ie)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= ip)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (stock[idp].qtd < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((peso(ide) + (qtd * stock[idp].peso)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idp, ide, 200);
        }
        else
        {
          {
            encomenda[ide][idp].qtd += qtd;
            stock[idp].qtd -= qtd;
          }
        }

      }

    }

  }

}

void remove_stock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= ip)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (stock[idp].qtd < qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      stock[idp].qtd -= qtd;
    }

  }

}

void remove_encomenda()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= ie)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= ip)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      {
        stock[idp].qtd += encomenda[ide][idp].qtd;
        encomenda[ide][idp].qtd = 0;
      }
    }

  }

}

void custo()
{
  int ide;
  int idp;
  int custo = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= ie)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    {
      for (idp = 0; idp < ip; idp++)
        custo += stock[idp].preco * encomenda[ide][idp].qtd;

      printf("Custo da encomenda %d %d.\n", ide, custo);
    }
  }

}

void alt_preco()
{
  int idp;
  int novo_preco;
  idp = new_sym_var(sizeof(int) * 8);
  novo_preco = new_sym_var(sizeof(int) * 8);
  if (idp >= ip)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    stock[idp].preco = novo_preco;
  }

}

void desc_quant()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= ie)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp >= ip)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      printf("%s %d.\n", stock[idp].desc, encomenda[ide][idp].qtd);
    }

  }

}

void max_produto()
{
  int ide = 0;
  int idp;
  int i_max = 0;
  int vazia = 1;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= ip)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    {
      while (ide < ie)
      {
        if (encomenda[ide][idp].qtd > 0)
        {
          {
            if (encomenda[ide][idp].qtd > encomenda[i_max][idp].qtd)
            {
              i_max = ide;
            }
            else
            {
              
            }

            vazia = 0;
          }
        }
        else
        {
          
        }

        ide++;
      }

      if ((ide > 0) && (vazia == 0))
      {
        printf("Maximo produto %d %d %d.\n", idp, i_max, encomenda[i_max][idp].qtd);
      }
      else
      {
        
      }

    }
  }

}

void lista_stock()
{
  int idp;
  int lista[10000];
  printf("Produtos\n");
  for (idp = 0; idp < ip; idp++)
    lista[idp] = idp;

  mergesort(lista, 0, idp - 1, 1);
  imprime_lista(lista, idp, stock);
}

void lista_encomenda()
{
  int idp;
  int ide;
  int k = 0;
  int lista[10000];
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= ie)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    {
      printf("Encomenda %d\n", ide);
      for (idp = 0; idp < ip; idp++)
        if (encomenda[ide][idp].qtd > 0)
      {
        {
          lista[k] = idp;
          k++;
        }
      }
      else
      {
        
      }


      mergesort(lista, 0, k - 1, 0);
      imprime_lista(lista, k, encomenda[ide]);
    }
  }

}

void mergesort(int lista[10000], int esquerda, int direita, int criterio)
{
  int m = (direita + esquerda) / 2;
  if (direita <= esquerda)
  {
    return;
  }
  else
  {
    
  }

  mergesort(lista, esquerda, m, criterio);
  mergesort(lista, m + 1, direita, criterio);
  merge(lista, esquerda, m, direita, criterio);
}

void merge(int lista[10000], int esquerda, int m, int direita, int criterio)
{
  int i;
  int j;
  int k;
  int aux[10000];
  for (i = m + 1; i > esquerda; i--)
    aux[i - 1] = lista[i - 1];

  for (j = m; j < direita; j++)
    aux[(direita + m) - j] = lista[j + 1];

  for (k = esquerda; k <= direita; k++)
    if (condicao(criterio, aux[i], aux[j]) == 1)
  {
    lista[k] = aux[j--];
  }
  else
  {
    lista[k] = aux[i++];
  }


}

int condicao(int criterio, int a, int b)
{
  if (criterio == 1)
  {
    {
      if (stock[a].preco == stock[b].preco)
      {
        return a > b;
      }
      else
      {
        
      }

      return stock[a].preco > stock[b].preco;
    }
  }
  else
  {
    if (criterio == 0)
    {
      return strcmp(stock[a].desc, stock[b].desc) > 0;
    }
    else
    {
      return 0;
    }

  }

}

void imprime_lista(int lista[10000], int i_max, produto vetor[10000])
{
  int i;
  for (i = 0; i < i_max; i++)
    printf("* %s %d %d\n", stock[lista[i]].desc, stock[lista[i]].preco, vetor[lista[i]].qtd);

}

