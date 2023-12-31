#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


struct Produto
{
  char d[64];
  int preco;
  int peso;
  int qtd;
  int id;
};
struct Produto produtos[10000];
int num_produtos = 0;
void criaproduto()
{
  struct Produto produto;
  int produto_id = num_produtos;
  produto.id = produto_id;
  for (int produto_index = 0; produto_index < 10; produto_index++)
  {
    produto.d[produto_index] = new_sym_var(sizeof(char) * 8);
  }

  produto.d[10 - 1] = '\0';
  produto.preco = new_sym_var(sizeof(int) * 8);
  produto.peso = new_sym_var(sizeof(int) * 8);
  produto.qtd = new_sym_var(sizeof(int) * 8);
  produtos[num_produtos] = produto;
  num_produtos++;
  printf("Novo produto %d.\n", produto_id);
}

void adicionastock()
{
  int n;
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id >= num_produtos)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  for (n = 0; n < num_produtos; n++)
  {
    if (produtos[n].id == id)
    {
      produtos[n].qtd += qtd;
      break;
    }
    else
    {
      
    }

  }

}

void removestock()
{
  int n;
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id >= num_produtos)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  for (n = 0; n < num_produtos; n++)
  {
    if (produtos[n].id == id)
    {
      if (qtd <= produtos[n].qtd)
      {
        produtos[n].qtd -= qtd;
        return;
      }
      else
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
      }

    }
    else
    {
      
    }

  }

}

void mudapreco()
{
  int n;
  int id;
  int preco;
  id = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (id >= num_produtos)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  for (n = 0; n < num_produtos; n++)
  {
    if (produtos[n].id == id)
    {
      produtos[n].preco = preco;
      break;
    }
    else
    {
      
    }

  }

}

int a[10000];
void merge(int a[], int left, int m, int right)
{
  int i;
  int j;
  int k;
  int aux[10000];
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
    if ((produtos[aux[j]].preco < produtos[aux[i]].preco) || (i > m))
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
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

void listaproduto()
{
  int i;
  int n;
  for (i = 0; i < num_produtos; i++)
  {
    a[i] = i;
  }

  mergesort(a, 0, num_produtos - 1);
  printf("Produtos\n");
  for (n = 0; n < num_produtos; n++)
  {
    printf("* %s %d %d\n", produtos[a[n]].d, produtos[a[n]].preco, produtos[a[n]].qtd);
  }

}

struct Encomenda
{
  int peso;
  int id;
  int produto_ids[200];
  int produto_qtds[200];
  int num_produtos;
};
struct Encomenda encomendas[500];
int num_encomendas = 0;
void criaencomenda()
{
  struct Encomenda encomenda;
  int encomenda_id = num_encomendas;
  encomenda.peso = 0;
  encomenda.num_produtos = 0;
  encomendas[num_encomendas] = encomenda;
  num_encomendas++;
  printf("Nova encomenda %d.\n", encomenda_id);
}

void adicionaproduto()
{
  int idp;
  int ide;
  int qtdp;
  int n;
  int produto_id;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtdp = new_sym_var(sizeof(int) * 8);
  if (ide >= num_encomendas)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (idp >= num_produtos)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  for (n = 0; n < num_produtos; n++)
  {
    if (produtos[n].id == idp)
    {
      produto_id = n;
      break;
    }
    else
    {
      
    }

  }

  if (qtdp > produtos[produto_id].qtd)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if ((encomendas[ide].peso + (produtos[produto_id].peso * qtdp)) <= 200)
  {
    for (n = 0; n < encomendas[ide].num_produtos; n++)
    {
      if (idp == encomendas[ide].produto_ids[n])
      {
        encomendas[ide].produto_qtds[n] += qtdp;
        encomendas[ide].peso += produtos[produto_id].peso * qtdp;
        produtos[produto_id].qtd -= qtdp;
        return;
      }
      else
      {
        
      }

    }

  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    return;
  }

  encomendas[ide].produto_ids[encomendas[ide].num_produtos] = idp;
  encomendas[ide].produto_qtds[encomendas[ide].num_produtos] = qtdp;
  encomendas[ide].num_produtos += 1;
  produtos[produto_id].qtd -= qtdp;
  encomendas[ide].peso += produtos[produto_id].peso * qtdp;
}

void removeproduto()
{
  int idp;
  int ide;
  int n;
  int i;
  int produto_id;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= num_encomendas)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (idp >= num_produtos)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  for (n = 0; n < encomendas[ide].num_produtos; n++)
  {
    if (idp == encomendas[ide].produto_ids[n])
    {
      for (i = 0; i < num_produtos; i++)
      {
        if (produtos[i].id == idp)
        {
          produto_id = i;
          break;
        }
        else
        {
          
        }

      }

      produtos[produto_id].qtd += encomendas[ide].produto_qtds[n];
      encomendas[ide].peso -= produtos[produto_id].peso * encomendas[ide].produto_qtds[n];
      encomendas[ide].produto_ids[n] = encomendas[ide].produto_ids[encomendas[ide].num_produtos - 1];
      encomendas[ide].produto_qtds[n] = encomendas[ide].produto_qtds[encomendas[ide].num_produtos - 1];
      encomendas[ide].num_produtos -= 1;
      return;
    }
    else
    {
      
    }

  }

}

int b[200];
void merge_L(int b[], int left, int m, int right, int ide)
{
  int i;
  int j;
  int k;
  int aux[200];
  for (i = m + 1; i > left; i--)
    aux[i - 1] = b[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = b[j + 1];

  for (k = left; k <= right; k++)
  {
    if (strcmp(produtos[encomendas[ide].produto_ids[aux[j]]].d, produtos[encomendas[ide].produto_ids[aux[i]]].d) < 0)
    {
      b[k] = aux[j--];
    }
    else
    {
      b[k] = aux[i++];
    }

  }

}

void mergesort_L(int b[], int l, int r, int ide)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort_L(b, l, m, ide);
  mergesort_L(b, m + 1, r, ide);
  merge_L(b, l, m, r, ide);
}

void listaencomenda()
{
  int i;
  int n;
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= num_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < encomendas[ide].num_produtos; i++)
    b[i] = i;

  mergesort_L(b, 0, encomendas[ide].num_produtos - 1, ide);
  printf("Encomenda %d\n", ide);
  for (n = 0; n < encomendas[ide].num_produtos; n++)
    printf("* %s %d %d\n", produtos[encomendas[ide].produto_ids[b[n]]].d, produtos[encomendas[ide].produto_ids[b[n]]].preco, encomendas[ide].produto_qtds[b[n]]);

}

void listaidrepetido()
{
  int id;
  int n;
  int ide;
  int qtd;
  int idemax;
  int qtdmax;
  qtdmax = -1;
  idemax = -1;
  id = new_sym_var(sizeof(int) * 8);
  if (id >= num_produtos)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  for (ide = 0; ide < num_encomendas; ide++)
  {
    for (n = 0; n < encomendas[ide].num_produtos; n++)
    {
      if (encomendas[ide].produto_ids[n] == id)
      {
        qtd = encomendas[ide].produto_qtds[n];
        if (qtd > qtdmax)
        {
          qtdmax = qtd;
          idemax = ide;
        }
        else
        {
          if ((qtd == qtdmax) && (ide < idemax))
          {
            qtdmax = qtd;
            idemax = ide;
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

  if (idemax != (-1))
  {
    printf("Maximo produto %d %d %d.\n", id, idemax, qtdmax);
  }
  else
  {
    
  }

}

void listadesceqtd()
{
  int idp;
  int ide;
  int n;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= num_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  if (idp >= num_produtos)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  for (n = 0; n < encomendas[ide].num_produtos; n++)
  {
    if (encomendas[ide].produto_ids[n] == idp)
    {
      for (i = 0; i < num_produtos; i++)
      {
        if (produtos[i].id == idp)
        {
          printf("%s %d.\n", produtos[i].d, encomendas[ide].produto_qtds[n]);
          return;
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

  for (i = 0; i < num_produtos; i++)
  {
    if (produtos[i].id == idp)
    {
      printf("%s 0.\n", produtos[i].d);
      return;
    }
    else
    {
      
    }

  }

}

void calculacusto()
{
  int ide;
  int custo;
  int n;
  int produto_id;
  int i;
  custo = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= num_encomendas)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (n = 0; n < encomendas[ide].num_produtos; n++)
  {
    for (i = 0; i < num_produtos; i++)
    {
      if (produtos[i].id == encomendas[ide].produto_ids[n])
      {
        produto_id = i;
        break;
      }
      else
      {
        
      }

    }

    custo += encomendas[ide].produto_qtds[n] * produtos[produto_id].preco;
  }

  printf("Custo da encomenda %d %d.\n", ide, custo);
}

int main()
{
  int c;
  while (1)
  {
    c = getchar();
    if (c == EOF)
    {
      return 0;
    }
    else
    {
      
    }

    switch (c)
    {
      case 'a':
        criaproduto();
        break;

      case 'q':
        adicionastock();
        break;

      case 'r':
        removestock();
        break;

      case 'p':
        mudapreco();
        break;

      case 'l':
        listaproduto();
        break;

      case 'N':
        criaencomenda();
        break;

      case 'A':
        adicionaproduto();
        break;

      case 'R':
        removeproduto();
        break;

      case 'L':
        listaencomenda();
        break;

      case 'm':
        listaidrepetido();
        break;

      case 'E':
        listadesceqtd();
        break;

      case 'C':
        calculacusto();
        break;

      case 'x':
        return 0;

    }

  }

  return 0;
}

