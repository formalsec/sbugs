/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct produtos
{
  int idp;
  int preco;
  int peso;
  int qtd;
  char descricao[63];
} Produto;
Produto produto[10000];
int p_size[500];
int p_size_out = 0;
typedef struct encomendas
{
  int ide;
  Produto produto[10000];
  int peso_t;
} Encomenda;
Encomenda encomenda[500];
int e_size = 0;
void adicionaProduto()
{
  char descricao[63];
  int preco;
  int peso;
  int qtd;
  for (int descricao_index = 0; descricao_index < 10; descricao_index++)
  {
    descricao[descricao_index] = new_sym_var(sizeof(char) * 8);
  }

  descricao[10 - 1] = '\0';
  preco = new_sym_var(sizeof(int) * 8);
  peso = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  strcpy(produto[p_size_out].descricao, descricao);
  produto[p_size_out].preco = preco;
  produto[p_size_out].peso = peso;
  produto[p_size_out].qtd = qtd;
  printf("Novo produto %d.\n", p_size_out);
  p_size_out++;
}

void adicionaStock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp < p_size_out)
  {
    produto[idp].qtd = produto[idp].qtd + qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

}

int searchForProductInEcom(int ide, int idp)
{
  int i;
  for (i = 0; i < p_size[ide]; i++)
  {
    if (encomenda[ide].produto[i].idp == idp)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

void A()
{
  int ide;
  int i;
  int idp;
  int qtd;
  int p;
  int q;
  int peso_max;
  int n = 200;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  q = produto[idp].qtd;
  p = produto[idp].peso;
  peso_max = (p * qtd) + encomenda[ide].peso_t;
  if (ide > (e_size - 1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    if (idp > (p_size_out - 1))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return;
    }
    else
    {
      if (qtd > q)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
      }
      else
      {
        if (peso_max > n)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
          return;
        }
        else
        {
          
        }

      }

    }

  }

  i = searchForProductInEcom(ide, idp);
  if (i != (-1))
  {
    encomenda[ide].produto[i].qtd = encomenda[ide].produto[i].qtd + qtd;
    produto[idp].qtd = produto[idp].qtd - qtd;
    encomenda[ide].peso_t = peso_max;
  }
  else
  {
    encomenda[ide].produto[p_size[ide]].qtd = qtd;
    encomenda[ide].produto[p_size[ide]].peso = produto[idp].peso;
    encomenda[ide].produto[p_size[ide]].preco = produto[idp].preco;
    strcpy(encomenda[ide].produto[p_size[ide]].descricao, produto[idp].descricao);
    encomenda[ide].produto[p_size[ide]].idp = idp;
    p_size[ide]++;
    produto[idp].qtd = produto[idp].qtd - qtd;
    encomenda[ide].peso_t = peso_max;
  }

}

void r()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp < p_size_out)
  {
    if ((produto[idp].qtd - qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      produto[idp].qtd = produto[idp].qtd - qtd;
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }

}

void R()
{
  int i;
  int p;
  int q;
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide > (e_size - 1))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (idp > (p_size_out - 1))
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < p_size[ide]; i++)
  {
    if (encomenda[ide].produto[i].idp == idp)
    {
      p = encomenda[ide].produto[i].peso;
      q = encomenda[ide].produto[i].qtd;
      encomenda[ide].peso_t = encomenda[ide].peso_t - (p * q);
      produto[idp].qtd = produto[idp].qtd + q;
      strcpy(encomenda[ide].produto[i].descricao, "");
      encomenda[ide].produto[i].idp = -1;
      encomenda[ide].produto[i].peso = 0;
      encomenda[ide].produto[i].preco = 0;
      encomenda[ide].produto[i].qtd = 0;
    }
    else
    {
      
    }

  }

}

int C()
{
  int ide;
  int i;
  int soma = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide < e_size)
  {
    for (i = 0; i <= p_size[ide]; i++)
    {
      soma = soma + (encomenda[ide].produto[i].preco * encomenda[ide].produto[i].qtd);
    }

    printf("Custo da encomenda %d %d.\n", ide, soma);
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }

  return 0;
}

void p()
{
  int idp;
  int i;
  int j;
  int preco;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp < p_size_out)
  {
    for (i = 0; i < e_size; i++)
    {
      for (j = 0; j < p_size[i]; j++)
      {
        if (encomenda[i].produto[j].idp == idp)
        {
          encomenda[i].produto[j].preco = preco;
          break;
        }
        else
        {
          
        }

      }

    }

    produto[idp].preco = preco;
  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }

}

int E()
{
  int ide;
  int idp;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  i = searchForProductInEcom(ide, idp);
  if (ide < e_size)
  {
    if (idp < p_size_out)
    {
      if (i != (-1))
      {
        printf("%s %d.\n", encomenda[ide].produto[i].descricao, encomenda[ide].produto[i].qtd);
      }
      else
      {
        printf("%s 0.\n", produto[idp].descricao);
      }

    }
    else
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }

  return 0;
}

int m()
{
  int idp;
  int i;
  int j;
  int aux;
  int x = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp < p_size_out)
  {
    for (i = 0; i < e_size; i++)
    {
      for (j = 0; j < p_size[i]; j++)
      {
        if (encomenda[i].produto[j].idp == idp)
        {
          if (x < encomenda[i].produto[j].qtd)
          {
            x = encomenda[i].produto[j].qtd;
            aux = i;
            break;
          }
          else
          {
            
          }

        }
        else
        {
          
        }

      }

    }

    if (x != 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, aux, x);
    }
    else
    {
      
    }

  }
  else
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }

  return 0;
}

int main()
{
  char comando;
  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      case 'a':
        getchar();
        adicionaProduto();
        break;

      case 'q':
        adicionaStock();
        break;

      case 'N':
        printf("Nova encomenda %d.\n", e_size);
        e_size++;
        break;

      case 'A':
        getchar();
        A();
        break;

      case 'r':
        r();
        break;

      case 'R':
        R();
        break;

      case 'C':
        C();
        break;

      case 'p':
        p();
        break;

      case 'E':
        E();
        break;

      case 'm':
        m();
        break;

    }

  }

  return 0;
}
