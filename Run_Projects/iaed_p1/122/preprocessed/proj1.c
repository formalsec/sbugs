/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


int idp = 0;
int ide = 0;
typedef struct 
{
  int idp;
  char descricao[63];
  int preco;
  int peso;
  int qtd;
} produto;
produto sistema_produtos[10000] = {0};
produto sistema_encomendas[500][10000] = {0};
int aux[10000];
void merge_produtos(int a[], int left, int m, int right)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
  {
    aux[i - 1] = a[i - 1];
  }

  for (j = m; j < right; j++)
  {
    aux[(right + m) - j] = a[j + 1];
  }

  for (k = left; k <= right; k++)
  {
    if ((sistema_produtos[aux[j]].preco < sistema_produtos[aux[i]].preco) || (i > m))
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

void mergeSort_produtos(int a[], int left, int right)
{
  int m = left + ((right - left) / 2);
  if (right <= left)
  {
    {
      return;
    }
  }
  else
  {
    {
      mergeSort_produtos(a, left, m);
      mergeSort_produtos(a, m + 1, right);
      merge_produtos(a, left, m, right);
    }
  }

}

void novo_produto()
{
  for (int sistema_produtos_index = 0; sistema_produtos_index < 10; sistema_produtos_index++)
  {
    sistema_produtos[idp].descricao[sistema_produtos_index] = new_sym_var(sizeof(char) * 8);
  }

  sistema_produtos[idp].descricao[10 - 1] = '\0';
  sistema_produtos[idp].preco = new_sym_var(sizeof(int) * 8);
  sistema_produtos[idp].peso = new_sym_var(sizeof(int) * 8);
  sistema_produtos[idp].qtd = new_sym_var(sizeof(int) * 8);
  sistema_produtos[idp].idp = idp;
  printf("Novo produto %d.\n", idp);
  idp++;
  return;
}

void adiciona_stock()
{
  int extrastock;
  int idp_aux;
  idp_aux = new_sym_var(sizeof(int) * 8);
  extrastock = new_sym_var(sizeof(int) * 8);
  if (idp_aux > (idp - 1))
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_aux);
      return;
    }
  }
  else
  {
    {
      sistema_produtos[idp_aux].qtd += extrastock;
      return;
    }
  }

}

void cria_encomenda()
{
  printf("Nova encomenda %d.\n", ide);
  ide++;
  return;
}

void add_encomenda()
{
  int i;
  int ide_aux;
  int idp_aux;
  int qtd_aux;
  int peso_aux;
  peso_aux = 0;
  ide_aux = new_sym_var(sizeof(int) * 8);
  idp_aux = new_sym_var(sizeof(int) * 8);
  qtd_aux = new_sym_var(sizeof(int) * 8);
  if (ide_aux > (ide - 1))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
      return;
    }
  }
  else
  {
    if (idp_aux > (idp - 1))
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
        return;
      }
    }
    else
    {
      if (qtd_aux > sistema_produtos[idp_aux].qtd)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_aux, ide_aux);
          return;
        }
      }
      else
      {
        
      }

    }

  }

  peso_aux += qtd_aux * sistema_produtos[idp_aux].peso;
  for (i = 0; i < 10000; i++)
  {
    peso_aux += sistema_produtos[i].peso * sistema_encomendas[ide_aux][i].qtd;
  }

  if (peso_aux > 200)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_aux, ide_aux);
      return;
    }
  }
  else
  {
    {
      sistema_encomendas[ide_aux][idp_aux].idp = idp;
      sistema_encomendas[ide_aux][idp_aux].preco = sistema_produtos[idp_aux].preco;
      sistema_encomendas[ide_aux][idp_aux].qtd += qtd_aux;
      sistema_produtos[idp_aux].qtd -= qtd_aux;
      return;
    }
  }

}

void remove_stock()
{
  int idp_aux;
  int qtd_aux;
  idp_aux = new_sym_var(sizeof(int) * 8);
  qtd_aux = new_sym_var(sizeof(int) * 8);
  if (idp_aux > (idp - 1))
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_aux);
      return;
    }
  }
  else
  {
    if (qtd_aux > sistema_produtos[idp_aux].qtd)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_aux, idp_aux);
        return;
      }
    }
    else
    {
      {
        sistema_produtos[idp_aux].qtd -= qtd_aux;
        return;
      }
    }

  }

}

void remove_produto()
{
  int ide_aux;
  int idp_aux;
  int qtd_aux;
  int peso_aux;
  ide_aux = new_sym_var(sizeof(int) * 8);
  idp_aux = new_sym_var(sizeof(int) * 8);
  qtd_aux = 0;
  peso_aux = 0;
  if (ide_aux > (ide - 1))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
      return;
    }
  }
  else
  {
    if (idp_aux > (idp - 1))
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
        return;
      }
    }
    else
    {
      {
        qtd_aux = sistema_encomendas[ide_aux][idp_aux].qtd;
        peso_aux = sistema_encomendas[ide_aux][idp_aux].peso * sistema_encomendas[ide_aux][idp_aux].qtd;
        sistema_encomendas[ide_aux][idp_aux].qtd = 0;
        sistema_encomendas[ide_aux][idp_aux].preco = 0;
        sistema_encomendas[ide_aux][idp_aux].peso -= peso_aux;
        sistema_produtos[idp_aux].qtd += qtd_aux;
        return;
      }
    }

  }

}

void give_me_custo()
{
  int ide_aux;
  int i;
  int custo_encomenda;
  custo_encomenda = 0;
  ide_aux = new_sym_var(sizeof(int) * 8);
  if (ide_aux > (ide - 1))
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_aux);
      return;
    }
  }
  else
  {
    {
      for (i = 0; i < idp; i++)
      {
        custo_encomenda += sistema_encomendas[ide_aux][i].preco * sistema_encomendas[ide_aux][i].qtd;
      }

      printf("Custo da encomenda %d %d.\n", ide_aux, custo_encomenda);
      return;
    }
  }

}

void altera_preco()
{
  int e;
  int preco_aux;
  int idp_aux;
  idp_aux = new_sym_var(sizeof(int) * 8);
  preco_aux = new_sym_var(sizeof(int) * 8);
  if (idp_aux > (idp - 1))
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_aux);
      return;
    }
  }
  else
  {
    {
      sistema_produtos[idp_aux].preco = preco_aux;
      for (e = 0; e < ide; e++)
      {
        sistema_encomendas[e][idp_aux].preco = preco_aux;
      }

      return;
    }
  }

}

void lista_produto()
{
  int ide_aux;
  int idp_aux;
  ide_aux = new_sym_var(sizeof(int) * 8);
  idp_aux = new_sym_var(sizeof(int) * 8);
  if (ide_aux > (ide - 1))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
      return;
    }
  }
  else
  {
    if (idp_aux > (idp - 1))
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp_aux);
        return;
      }
    }
    else
    {
      {
        if (sistema_encomendas[ide_aux][idp_aux].qtd >= 0)
        {
          {
            printf("%s %d.\n", sistema_produtos[idp_aux].descricao, sistema_encomendas[ide_aux][idp_aux].qtd);
            return;
          }
        }
        else
        {
          
        }

        return;
      }
    }

  }

}

void ocorre_mais()
{
  int e;
  int i;
  int idp_aux;
  int enco_index;
  int product_index;
  int maior;
  maior = 0;
  product_index = 0;
  enco_index = 0;
  idp_aux = new_sym_var(sizeof(int) * 8);
  if (idp_aux > (idp - 1))
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_aux);
      return;
    }
  }
  else
  {
    
  }

  for (e = 0; e < ide; e++)
  {
    for (i = 0; i < idp; i++)
    {
      if (i == idp_aux)
      {
        {
          if (maior < sistema_encomendas[e][i].qtd)
          {
            {
              maior = sistema_encomendas[e][i].qtd;
              enco_index = e;
              product_index = i;
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

  if (maior != 0)
  {
    {
      printf("Maximo produto %d %d %d.\n", product_index, enco_index, maior);
      return;
    }
  }
  else
  {
    
  }

}

void ordena_price()
{
  int i;
  int ids[10000];
  for (i = 0; i < idp; i++)
  {
    ids[i] = i;
  }

  mergeSort_produtos(ids, 0, idp - 1);
  printf("Produtos\n");
  for (i = 0; i < idp; i++)
  {
    printf("* %s %d %d\n", sistema_produtos[ids[i]].descricao, sistema_produtos[ids[i]].preco, sistema_produtos[ids[i]].qtd);
  }

  return;
}

int main()
{
  int carater;
  while ((carater = getchar()) != EOF)
  {
    switch (carater)
    {
      case 'a':
      {
        novo_produto();
        break;
      }

      case 'q':
      {
        adiciona_stock();
        break;
      }

      case 'N':
      {
        cria_encomenda();
        break;
      }

      case 'A':
      {
        add_encomenda();
        break;
      }

      case 'r':
      {
        remove_stock();
        break;
      }

      case 'R':
      {
        remove_produto();
        break;
      }

      case 'C':
      {
        give_me_custo();
        break;
      }

      case 'p':
      {
        altera_preco();
        break;
      }

      case 'E':
      {
        lista_produto();
        break;
      }

      case 'm':
      {
        ocorre_mais();
        break;
      }

      case 'l':
      {
        ordena_price();
        break;
      }

      case 'x':
      {
        break;
      }

    }

  }

  return 0;
}
