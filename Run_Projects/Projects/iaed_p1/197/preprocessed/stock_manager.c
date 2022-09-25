/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct Produto
{
  int idp;
  int preco;
  int peso;
  int stock;
  char descricao[64];
} Produto;
typedef struct Item
{
  int idp;
  int qtd;
} Item;
typedef struct Encomenda
{
  Item items[200];
  int peso;
  int num_items_distintos;
} Encomenda;
struct Armazem
{
  Produto produtos[10000];
  int num_produtos;
  Encomenda encomendas[500];
  int num_encomendas;
} armazem = {0};
typedef enum 
{
  preco,
  descricao
} criterio;
int indice_produto_armazem(int idp);
int indice_produto_encomenda(int ide, int idp);
int inferior(Produto a, Produto b, criterio c);
void quicksort(Produto p[], int lo, int hi, criterio c);
void novo_prod_encomenda(int ide, int idp, int qtd, int indice);
void novo_produto();
void add_stock();
void nova_encomenda();
void add_prod_encomenda();
int copiar_produtos(Produto p[]);
void remove_stock();
void remove_prod_encomenda();
void calcula_custo_encomenda();
void set_preco_prod();
void lista_descricao_qtd_prod_encomenda();
void lista_ide_max_produto();
void lista_produtos_por_preco();
void lista_produtos_alfabeticamente_descricao();
int main()
{
  int ch;
  while (1)
  {
    switch (ch = getchar())
    {
      case 'a':
        novo_produto();
        break;

      case 'q':
        add_stock();
        break;

      case 'N':
        nova_encomenda();
        break;

      case 'A':
        add_prod_encomenda();
        break;

      case 'r':
        remove_stock();
        break;

      case 'R':
        remove_prod_encomenda();
        break;

      case 'C':
        calcula_custo_encomenda();
        break;

      case 'p':
        set_preco_prod();
        break;

      case 'E':
        lista_descricao_qtd_prod_encomenda();
        break;

      case 'm':
        lista_ide_max_produto();
        break;

      case 'l':
        lista_produtos_por_preco();
        break;

      case 'L':
        lista_produtos_alfabeticamente_descricao();
        break;

      case 'x':
        return 0;

    }

  }

}

int indice_produto_armazem(int idp)
{
  int i;
  for (i = idp; i < armazem.num_produtos; i++)
  {
    if (armazem.produtos[i].idp == idp)
    {
      return i;
    }
    else
    {
      
    }

  }

  for (i = idp - 1; i > 0; i--)
  {
    if (armazem.produtos[i].idp == idp)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

int indice_produto_encomenda(int ide, int idp)
{
  int i;
  for (i = 0; i < armazem.encomendas[ide].num_items_distintos; i++)
  {
    if (armazem.encomendas[ide].items[i].idp == idp)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

int inferior(Produto a, Produto b, criterio c)
{
  switch (c)
  {
    case preco:
      return (a.preco < b.preco) || ((a.preco == b.preco) && (a.idp < b.idp));

    case descricao:
      return (strcmp(a.descricao, b.descricao) < 0) ? (1) : (0);

    default:
      return -1;

  }

}

void quicksort(Produto p[], int lo, int hi, criterio c)
{
  int i;
  int j;
  Produto pivot;
  Produto temp;
  i = lo;
  j = hi;
  pivot = p[(lo + hi) / 2];
  while (i <= j)
  {
    while (inferior(p[i], pivot, c) && (i < hi))
    {
      i++;
    }

    while (inferior(pivot, p[j], c) && (j > lo))
    {
      j--;
    }

    if (i <= j)
    {
      temp = p[i];
      p[i] = p[j];
      p[j] = temp;
      i++;
      j--;
    }
    else
    {
      
    }

  }

  if (j > lo)
  {
    quicksort(p, lo, j, c);
  }
  else
  {
    
  }

  if (i < hi)
  {
    quicksort(p, i, hi, c);
  }
  else
  {
    
  }

}

void novo_produto()
{
  int idp = armazem.num_produtos;
  for (int armazem_index = 0; armazem_index < 10; armazem_index++)
  {
    armazem.produtos[idp].descricao[armazem_index] = new_sym_var(sizeof(char) * 8);
  }

  armazem.produtos[idp].descricao[10 - 1] = '\0';
  armazem.produtos[idp].preco = new_sym_var(sizeof(int) * 8);
  armazem.produtos[idp].peso = new_sym_var(sizeof(int) * 8);
  armazem.produtos[idp].stock = new_sym_var(sizeof(int) * 8);
  armazem.produtos[idp].idp = idp;
  printf("Novo produto %d.\n", idp);
  armazem.num_produtos++;
}

void add_stock()
{
  int idp;
  int qtd;
  int indice;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  indice = indice_produto_armazem(idp);
  if (indice >= 0)
  {
    armazem.produtos[indice].stock += qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

}

void nova_encomenda()
{
  int ide = armazem.num_encomendas;
  armazem.encomendas[ide].peso = 0;
  armazem.encomendas[ide].num_items_distintos = 0;
  printf("Nova encomenda %d.\n", armazem.num_encomendas);
  armazem.num_encomendas++;
}

void add_prod_encomenda()
{
  int ide;
  int idp;
  int qtd;
  int i;
  int indice;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ide >= armazem.num_encomendas)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  indice = indice_produto_armazem(idp);
  if (indice < 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (qtd > armazem.produtos[indice].stock)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if ((armazem.encomendas[ide].peso + (armazem.produtos[indice].peso * qtd)) > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < armazem.encomendas[ide].num_items_distintos; i++)
  {
    if (armazem.encomendas[ide].items[i].idp == idp)
    {
      armazem.encomendas[ide].items[i].qtd += qtd;
      armazem.produtos[indice].stock -= qtd;
      armazem.encomendas[ide].peso += armazem.produtos[indice].peso * qtd;
      return;
    }
    else
    {
      
    }

  }

  novo_prod_encomenda(ide, idp, qtd, indice);
}

void novo_prod_encomenda(int ide, int idp, int qtd, int indice)
{
  int num_item = armazem.encomendas[ide].num_items_distintos;
  armazem.encomendas[ide].items[num_item].idp = idp;
  armazem.encomendas[ide].items[num_item].qtd = qtd;
  armazem.encomendas[ide].peso += armazem.produtos[indice].peso * qtd;
  armazem.encomendas[ide].num_items_distintos++;
  armazem.produtos[indice].stock -= qtd;
}

void remove_stock()
{
  int idp;
  int qtd_a_remover;
  int indice_prod;
  idp = new_sym_var(sizeof(int) * 8);
  qtd_a_remover = new_sym_var(sizeof(int) * 8);
  indice_prod = indice_produto_armazem(idp);
  if (indice_prod < 0)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  if (qtd_a_remover > armazem.produtos[indice_prod].stock)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_a_remover, idp);
  }
  else
  {
    armazem.produtos[indice_prod].stock -= qtd_a_remover;
  }

}

void remove_prod_encomenda()
{
  int ide;
  int idp;
  int qtd;
  int indice_prod;
  int indice_prod_encomenda;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= armazem.num_encomendas)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  indice_prod = indice_produto_armazem(idp);
  if (indice_prod < 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  indice_prod_encomenda = indice_produto_encomenda(ide, idp);
  if (indice_prod_encomenda < 0)
  {
    return;
  }
  else
  {
    
  }

  qtd = armazem.encomendas[ide].items[indice_prod_encomenda].qtd;
  armazem.produtos[indice_prod].stock += qtd;
  armazem.encomendas[ide].peso -= armazem.produtos[indice_prod].peso * qtd;
  armazem.encomendas[ide].items[indice_prod_encomenda].qtd = 0;
}

void calcula_custo_encomenda()
{
  int i;
  int qtd;
  int ide;
  int idp;
  int indice_prod;
  int custo = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= armazem.num_encomendas)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < armazem.encomendas[ide].num_items_distintos; i++)
  {
    idp = armazem.encomendas[ide].items[i].idp;
    qtd = armazem.encomendas[ide].items[i].qtd;
    indice_prod = indice_produto_armazem(idp);
    custo += armazem.produtos[indice_prod].preco * qtd;
  }

  printf("Custo da encomenda %d %d.\n", ide, custo);
}

void set_preco_prod()
{
  int idp;
  int preco;
  int indice_prod;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  indice_prod = indice_produto_armazem(idp);
  if (indice_prod >= 0)
  {
    armazem.produtos[indice_prod].preco = preco;
  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }

}

void lista_descricao_qtd_prod_encomenda()
{
  int ide;
  int idp;
  int qtd;
  int indice_prod;
  int indice_prod_encomenda;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= armazem.num_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  indice_prod = indice_produto_armazem(idp);
  if (indice_prod >= 0)
  {
    indice_prod_encomenda = indice_produto_encomenda(ide, idp);
    if (indice_prod_encomenda >= 0)
    {
      qtd = armazem.encomendas[ide].items[indice_prod_encomenda].qtd;
      printf("%s %d.\n", armazem.produtos[indice_prod].descricao, qtd);
    }
    else
    {
      printf("%s 0.\n", armazem.produtos[indice_prod].descricao);
    }

  }
  else
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  }

}

void lista_ide_max_produto()
{
  int i;
  int ide;
  int idp;
  int indice_prod;
  int ide_max_produto = 10000;
  int max_quantidade = 0;
  Item item;
  idp = new_sym_var(sizeof(int) * 8);
  indice_prod = indice_produto_armazem(idp);
  if (indice_prod < 0)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  for (ide = 0; ide < armazem.num_encomendas; ide++)
  {
    for (i = 0; i < armazem.encomendas[ide].num_items_distintos; i++)
    {
      item = armazem.encomendas[ide].items[i];
      if (item.idp == idp)
      {
        if ((item.qtd > max_quantidade) || ((item.qtd == max_quantidade) && (ide < ide_max_produto)))
        {
          ide_max_produto = ide;
          max_quantidade = item.qtd;
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

  if (max_quantidade > 0)
  {
    printf("Maximo produto %d %d %d.\n", idp, ide_max_produto, max_quantidade);
  }
  else
  {
    
  }

}

int copiar_produtos(Produto p[])
{
  int i;
  int len = armazem.num_produtos;
  for (i = 0; i < len; i++)
  {
    p[i] = armazem.produtos[i];
  }

  return len;
}

void lista_produtos_por_preco()
{
  int i;
  int len;
  criterio c = preco;
  Produto produtos[10000];
  len = copiar_produtos(produtos);
  quicksort(produtos, 0, len - 1, c);
  printf("Produtos\n");
  for (i = 0; i < len; i++)
  {
    printf("* %s %d %d\n", produtos[i].descricao, produtos[i].preco, produtos[i].stock);
  }

}

void lista_produtos_alfabeticamente_descricao()
{
  int i;
  int ide;
  int idp;
  int indice_prod;
  int len = 0;
  Produto produtos[10000];
  criterio c = descricao;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= armazem.num_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < armazem.encomendas[ide].num_items_distintos; i++)
  {
    idp = armazem.encomendas[ide].items[i].idp;
    indice_prod = indice_produto_armazem(idp);
    if (indice_prod >= 0)
    {
      produtos[len] = armazem.produtos[indice_prod];
      produtos[len].stock = armazem.encomendas[ide].items[i].qtd;
      len++;
    }
    else
    {
      
    }

  }

  quicksort(produtos, 0, len - 1, c);
  printf("Encomenda %d\n", ide);
  for (i = 0; i < len; i++)
  {
    if (produtos[i].stock > 0)
    {
      printf("* %s %d %d\n", produtos[i].descricao, produtos[i].preco, produtos[i].stock);
    }
    else
    {
      
    }

  }

}

