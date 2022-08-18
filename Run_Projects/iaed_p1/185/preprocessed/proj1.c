/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
  int quantidade_especial;
} Produto;
typedef struct encomenda
{
  int peso;
  int produtos[200][2];
  int ponteiro;
} Encomenda;
Produto lista_produtos[10000];
Encomenda lista_encomendas[500];
int i_produtos;
int i_encomendas;
void ad_produto()
{
  Produto prod;
  for (int prod_index = 0; prod_index < 10; prod_index++)
  {
    prod.descricao[prod_index] = new_sym_var(sizeof(char) * 8);
  }

  prod.descricao[10 - 1] = '\0';
  prod.preco = new_sym_var(sizeof(int) * 8);
  prod.peso = new_sym_var(sizeof(int) * 8);
  prod.quantidade = new_sym_var(sizeof(int) * 8);
  lista_produtos[i_produtos] = prod;
  printf("Novo produto %d.\n", i_produtos);
  i_produtos++;
}

void ad_stock()
{
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id >= i_produtos)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
    }
  }
  else
  {
    {
      lista_produtos[id].quantidade += qtd;
    }
  }

}

void cria_encomenda()
{
  Encomenda encomenda;
  encomenda.peso = 0;
  encomenda.ponteiro = 0;
  lista_encomendas[i_encomendas] = encomenda;
  printf("Nova encomenda %d.\n", i_encomendas);
  i_encomendas += 1;
}

int prod_na_encomenda(int prod, Encomenda encomenda)
{
  int ponteiro = encomenda.ponteiro;
  int i;
  for (i = 0; i < ponteiro; i++)
  {
    if (encomenda.produtos[i][0] == prod)
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

void ad_prod_a_encomenda()
{
  int id_prod;
  int id_enc;
  int qtd;
  int i;
  id_enc = new_sym_var(sizeof(int) * 8);
  id_prod = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id_enc >= i_encomendas)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_prod, id_enc);
      return;
    }
  }
  else
  {
    
  }

  if (id_prod >= i_produtos)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_prod, id_enc);
      return;
    }
  }
  else
  {
    
  }

  if (qtd > lista_produtos[id_prod].quantidade)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_prod, id_enc);
      return;
    }
  }
  else
  {
    
  }

  if ((lista_encomendas[id_enc].peso + (lista_produtos[id_prod].peso * qtd)) > 200)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_prod, id_enc);
      return;
    }
  }
  else
  {
    
  }

  i = prod_na_encomenda(id_prod, lista_encomendas[id_enc]);
  if (i != (-1))
  {
    {
      lista_encomendas[id_enc].produtos[i][1] += qtd;
    }
  }
  else
  {
    {
      lista_encomendas[id_enc].produtos[lista_encomendas[id_enc].ponteiro][0] = id_prod;
      lista_encomendas[id_enc].produtos[lista_encomendas[id_enc].ponteiro][1] = qtd;
      lista_encomendas[id_enc].ponteiro += 1;
    }
  }

  lista_encomendas[id_enc].peso += lista_produtos[id_prod].peso * qtd;
  lista_produtos[id_prod].quantidade -= qtd;
}

void rm_stock()
{
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id >= i_produtos)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
      return;
    }
  }
  else
  {
    
  }

  if (qtd > lista_produtos[id].quantidade)
  {
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
      return;
    }
  }
  else
  {
    
  }

  lista_produtos[id].quantidade -= qtd;
}

void rm_prod()
{
  int id_prod;
  int id_enc;
  int i;
  id_enc = new_sym_var(sizeof(int) * 8);
  id_prod = new_sym_var(sizeof(int) * 8);
  if (id_enc >= i_encomendas)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_prod, id_enc);
      return;
    }
  }
  else
  {
    
  }

  if (id_prod >= i_produtos)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_prod, id_enc);
      return;
    }
  }
  else
  {
    
  }

  i = prod_na_encomenda(id_prod, lista_encomendas[id_enc]);
  if (i != (-1))
  {
    {
      lista_produtos[id_prod].quantidade += lista_encomendas[id_enc].produtos[i][1];
      lista_encomendas[id_enc].peso -= lista_produtos[id_prod].peso * lista_encomendas[id_enc].produtos[i][1];
      for (; i < (lista_encomendas[id_enc].ponteiro - 1); i++)
      {
        lista_encomendas[id_enc].produtos[i][0] = lista_encomendas[id_enc].produtos[i + 1][0];
        lista_encomendas[id_enc].produtos[i][1] = lista_encomendas[id_enc].produtos[i + 1][1];
      }

      lista_encomendas[id_enc].ponteiro = lista_encomendas[id_enc].ponteiro - 1;
    }
  }
  else
  {
    
  }

}

void calc_custo()
{
  int id;
  int custo = 0;
  int i;
  id = new_sym_var(sizeof(int) * 8);
  if (id >= i_encomendas)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < lista_encomendas[id].ponteiro; i++)
  {
    custo += lista_produtos[lista_encomendas[id].produtos[i][0]].preco * lista_encomendas[id].produtos[i][1];
  }

  printf("Custo da encomenda %d %d.\n", id, custo);
}

void alt_produto()
{
  int id;
  int preco;
  id = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (id >= i_produtos)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
      return;
    }
  }
  else
  {
    
  }

  lista_produtos[id].preco = preco;
}

void ret_desc_quant()
{
  int id_prod;
  int id_enc;
  int i;
  int qtd;
  id_enc = new_sym_var(sizeof(int) * 8);
  id_prod = new_sym_var(sizeof(int) * 8);
  if (id_enc >= i_encomendas)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_enc);
      return;
    }
  }
  else
  {
    
  }

  if (id_prod >= i_produtos)
  {
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", id_prod);
      return;
    }
  }
  else
  {
    
  }

  i = prod_na_encomenda(id_prod, lista_encomendas[id_enc]);
  if (i == (-1))
  {
    {
      qtd = 0;
    }
  }
  else
  {
    {
      qtd = lista_encomendas[id_enc].produtos[i][1];
    }
  }

  printf("%s %d.\n", lista_produtos[id_prod].descricao, qtd);
}

void maior_encomenda()
{
  int maior_quantidade = -1;
  int id_maior_encomenda;
  int i;
  int j;
  int id_prod;
  id_prod = new_sym_var(sizeof(int) * 8);
  if (id_prod >= i_produtos)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_prod);
    }
  }
  else
  {
    
  }

  if (i_encomendas == 0)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < i_encomendas; i++)
  {
    j = prod_na_encomenda(id_prod, lista_encomendas[i]);
    if (j != (-1))
    {
      {
        if (lista_encomendas[i].produtos[j][1] > maior_quantidade)
        {
          {
            maior_quantidade = lista_encomendas[i].produtos[j][1];
            id_maior_encomenda = i;
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

  if (maior_quantidade == (-1))
  {
    {
      return;
    }
  }
  else
  {
    
  }

  printf("Maximo produto %d %d %d.\n", id_prod, id_maior_encomenda, maior_quantidade);
}

int menor(int prod1, int prod2, int flag)
{
  if (flag == 1)
  {
    {
      if (strcmp(lista_produtos[prod1].descricao, lista_produtos[prod2].descricao) < 0)
      {
        {
          return 1;
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
      if (lista_produtos[prod1].preco <= lista_produtos[prod2].preco)
      {
        {
          return 1;
        }
      }
      else
      {
        
      }

    }
  }

  return 0;
}

void merge(int arr[], int l, int m, int r, int flag)
{
  int Left[10000];
  int Right[10000];
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  for (i = 0; i < n1; i++)
    Left[i] = arr[l + i];

  for (j = 0; j < n2; j++)
    Right[j] = arr[(m + 1) + j];

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (menor(Left[i], Right[j], flag))
    {
      {
        arr[k] = Left[i];
        i++;
      }
    }
    else
    {
      {
        arr[k] = Right[j];
        j++;
      }
    }

    k++;
  }

  while (i < n1)
  {
    arr[k] = Left[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = Right[j];
    j++;
    k++;
  }

}

void mergesort(int arr[], int l, int r, int flag)
{
  if (l < r)
  {
    {
      int m = l + ((r - l) / 2);
      mergesort(arr, l, m, flag);
      mergesort(arr, m + 1, r, flag);
      merge(arr, l, m, r, flag);
    }
  }
  else
  {
    
  }

}

void ordenar_p_preco()
{
  int lista_copia[10000];
  int i;
  for (i = 0; i < i_produtos; i++)
  {
    lista_copia[i] = i;
  }

  mergesort(lista_copia, 0, i_produtos - 1, 0);
  printf("Produtos\n");
  for (i = 0; i < i_produtos; i++)
  {
    ;
    printf("* %s %d %d\n", lista_produtos[lista_copia[i]].descricao, lista_produtos[lista_copia[i]].preco, lista_produtos[lista_copia[i]].quantidade);
  }

}

void ordenar_p_descricao()
{
  int lista_copia[10000];
  int i;
  int id;
  id = new_sym_var(sizeof(int) * 8);
  if (id >= i_encomendas)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id);
      return;
    }
  }
  else
  {
    
  }

  printf("Encomenda %d\n", id);
  for (i = 0; i < lista_encomendas[id].ponteiro; i++)
  {
    lista_produtos[lista_encomendas[id].produtos[i][0]].quantidade_especial = lista_encomendas[id].produtos[i][1];
    lista_copia[i] = lista_encomendas[id].produtos[i][0];
  }

  mergesort(lista_copia, 0, lista_encomendas[id].ponteiro - 1, 1);
  for (i = 0; i < lista_encomendas[id].ponteiro; i++)
  {
    printf("* %s %d %d\n", lista_produtos[lista_copia[i]].descricao, lista_produtos[lista_copia[i]].preco, lista_produtos[lista_copia[i]].quantidade_especial);
  }

}

int main()
{
  char cmd;
  i_produtos = 0;
  i_encomendas = 0;
  while (1)
  {
    cmd = new_sym_var(sizeof(char) * 8);
    switch (cmd)
    {
      case 'a':
        ad_produto();
        break;

      case 'q':
        ad_stock();
        break;

      case 'N':
        cria_encomenda();
        break;

      case 'A':
        ad_prod_a_encomenda();
        break;

      case 'r':
        rm_stock();
        break;

      case 'R':
        rm_prod();
        break;

      case 'C':
        calc_custo();
        break;

      case 'p':
        alt_produto();
        break;

      case 'E':
        ret_desc_quant();
        break;

      case 'm':
        maior_encomenda();
        break;

      case 'l':
        ordenar_p_preco();
        break;

      case 'L':
        ordenar_p_descricao();
        break;

      case 'x':
        return 0;
        break;

    }

  }

  return 0;
}

