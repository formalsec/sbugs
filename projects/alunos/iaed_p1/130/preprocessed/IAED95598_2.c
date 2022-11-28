#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdbool.h>


typedef struct Produto
{
  char descricao[63];
  int idp;
  int preco;
  int peso;
  int stock;
} PRODUTO;
typedef struct Encomenda
{
  PRODUTO prods[10000];
  int ide;
  int len_prods;
  int peso_total;
} ENCOMENDA;
typedef struct Sistema
{
  PRODUTO conteudo[10000];
  ENCOMENDA compras[500];
  int len_produtos;
  int len_encomendas;
} SISTEMA;
SISTEMA sistema = {0};
PRODUTO aux[10000];
bool lessPreco(PRODUTO a, PRODUTO b)
{
  if (a.preco < b.preco)
  {
    return true;
  }
  else
  {
    return false;
  }

}

bool lessDescricao(PRODUTO a, PRODUTO b)
{
  if (a.descricao[0] < b.descricao[0])
  {
    return true;
  }
  else
  {
    return false;
  }

}

void mergePROD(PRODUTO a[], int left, int m, int right, bool (*teste)(PRODUTO a, PRODUTO b))
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = a[j + 1];

  for (k = left; k <= right; k++)
    if (teste(aux[j], aux[i]) || (i > m))
  {
    a[k] = aux[j--];
  }
  else
  {
    a[k] = aux[i++];
  }


}

void mergesortPROD(PRODUTO a[], int left, int right, bool (*teste)(PRODUTO a, PRODUTO b))
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesortPROD(a, left, m, teste);
  mergesortPROD(a, m + 1, right, teste);
  mergePROD(a, left, m, right, teste);
}

void listaEncomenda()
{
  int ide;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  printf("Encomenda %d\n", ide);
  for (i = 0; i < sistema.compras[ide].len_prods; i++)
  {
    PRODUTO prod = sistema.compras[ide].prods[i];
    printf("* %s %d %d\n", prod.descricao, prod.preco, prod.stock);
  }

}

void adicionaProduto()
{
  PRODUTO prod;
  for (int prod_index = 0; prod_index < 10; prod_index++)
  {
    prod.descricao[prod_index] = new_sym_var(sizeof(char) * 8);
  }

  prod.descricao[10 - 1] = '\0';
  prod.preco = new_sym_var(sizeof(int) * 8);
  prod.peso = new_sym_var(sizeof(int) * 8);
  prod.stock = new_sym_var(sizeof(int) * 8);
  prod.idp = sistema.len_produtos;
  printf("Novo produto %d.\n", sistema.len_produtos);
  sistema.conteudo[sistema.len_produtos++] = prod;
}

void alteraStock(char op, int idp, int qntd)
{
  if ((idp < 0) || (idp > (sistema.len_produtos - 1)))
  {
    switch (op)
    {
      case '+':
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        break;

      case '-':
        printf("Impossivel remover produto %d ao stock. Produto inexistente.\n", idp);
        break;

    }

    return;
  }
  else
  {
    
  }

  switch (op)
  {
    case '+':
      sistema.conteudo[idp].stock += qntd;
      break;

    case '-':
      if (qntd > sistema.conteudo[idp].stock)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qntd, idp);
      return;
    }
    else
    {
      
    }

      sistema.conteudo[idp].stock -= qntd;

  }

}

void alteraPreco()
{
  int idp;
  int preco;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if ((idp < 0) || (idp > (sistema.len_produtos - 1)))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  sistema.conteudo[idp].preco = preco;
}

void listaProdutos()
{
  int i;
  for (i = 0; i < sistema.len_produtos; i++)
  {
    PRODUTO prod = sistema.conteudo[i];
    printf("* %s %d %d", prod.descricao, prod.preco, prod.stock);
  }

}

void novaEncomenda()
{
  ENCOMENDA nova = {0};
  sistema.compras[sistema.len_encomendas] = nova;
  printf("Nova encomenda %d.\n", sistema.len_encomendas++);
}

void adicionaProdutoEncomenda()
{
  int i;
  int ide;
  int idp;
  int qntd;
  bool novo = true;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qntd = new_sym_var(sizeof(int) * 8);
  if ((ide < 0) || (ide > (sistema.len_encomendas - 1)))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if ((idp < 0) || (idp > (sistema.len_produtos - 1)))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (qntd > sistema.conteudo[idp].stock)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (((sistema.conteudo[idp].peso * qntd) + sistema.compras[ide].peso_total) > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < sistema.compras[ide].len_prods; i++)
  {
    if (sistema.compras[ide].prods[i].idp == idp)
    {
      novo = false;
      sistema.compras[ide].prods[i].stock += qntd;
    }
    else
    {
      
    }

  }

  if (novo)
  {
    sistema.compras[ide].prods[sistema.compras[ide].len_prods] = sistema.conteudo[idp];
    sistema.compras[ide].prods[sistema.compras[ide].len_prods].stock = qntd;
    sistema.compras[ide].len_prods++;
  }
  else
  {
    
  }

  sistema.compras[ide].peso_total += sistema.conteudo[idp].peso * qntd;
  alteraStock('-', idp, qntd);
}

void removeProdutoEncomenda()
{
  int i;
  int j;
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if ((ide < 0) || (ide > (sistema.len_encomendas - 1)))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if ((idp < 0) || (idp > (sistema.len_produtos - 1)))
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < sistema.compras[ide].len_prods; i++)
  {
    if (sistema.compras[ide].prods[i].idp == idp)
    {
      for (j = i; j < sistema.compras[ide].len_prods; j++)
      {
        sistema.compras[ide].prods[j] = sistema.compras[ide].prods[j + 1];
      }

      sistema.compras[ide].len_prods--;
      return;
    }
    else
    {
      
    }

  }

}

void infoProduto()
{
  int i;
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if ((ide < 0) || (ide > (sistema.len_encomendas - 1)))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  if ((idp < 0) || (idp > (sistema.len_produtos - 1)))
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < sistema.compras[ide].len_prods; i++)
  {
    if (sistema.compras[ide].prods[i].idp == idp)
    {
      printf("%s %d\n", sistema.compras[ide].prods[i].descricao, sistema.compras[ide].prods[i].stock);
    }
    else
    {
      
    }

  }

}

void calculaPreco()
{
  int i;
  int ide;
  int total;
  ide = new_sym_var(sizeof(int) * 8);
  if ((ide < 0) || (ide > (sistema.len_encomendas - 1)))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (i = 0, total = 0; i < sistema.compras[ide].len_prods; i++)
  {
    total += sistema.compras[ide].prods[i].preco * sistema.compras[ide].prods[i].stock;
  }

  printf("Custo da encomenda %d %d.\n", ide, total);
}

void maxProduto()
{
  int i;
  int j;
  int max;
  int idp;
  int ide;
  bool encontrou = false;
  idp = new_sym_var(sizeof(int) * 8);
  if ((idp < 0) || (idp > (sistema.len_produtos - 1)))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  for (i = 0, max = 0; i < sistema.len_encomendas; i++)
  {
    for (j = 0; j < sistema.compras[i].len_prods; j++)
    {
      if (sistema.compras[i].prods[j].idp == idp)
      {
        if (sistema.compras[i].prods[j].stock > max)
        {
          max = sistema.compras[i].prods[j].stock;
          ide = i;
          encontrou = true;
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

  if (encontrou)
  {
    printf("Maximo produto %d %d %d.\n", idp, ide, max);
  }
  else
  {
    
  }

}

void ordenaProdutos()
{
  int i;
  int len = sistema.len_produtos;
  PRODUTO prods[10000];
  for (i = 0; i < len; i++)
    prods[i] = sistema.conteudo[i];

  mergesortPROD(prods, 0, len - 1, lessPreco);
  printf("Produtos\n");
  for (i = 0; i < len; i++)
  {
    printf("* %s %d %d\n", prods[i].descricao, prods[i].preco, prods[i].stock);
  }

}

void ordenaEncomenda()
{
  PRODUTO prods[10000];
  int i;
  int ide;
  int len;
  ide = new_sym_var(sizeof(int) * 8);
  if ((ide < 0) || (ide > (sistema.len_encomendas - 1)))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  len = sistema.compras[ide].len_prods;
  for (i = 0; i < len; i++)
    prods[i] = sistema.compras[ide].prods[i];

  mergesortPROD(prods, 0, len - 1, lessDescricao);
  printf("Encomenda %d\n", ide);
  for (i = 0; i < len; i++)
  {
    printf("* %s %d %d\n", prods[i].descricao, prods[i].preco, prods[i].stock);
  }

}

int main()
{
  char c;
  int i1;
  int i2;
  while (true)
  {
    c = getchar();
    switch (c)
    {
      case 'a':
        adicionaProduto();
        break;

      case 'q':
        i1 = new_sym_var(sizeof(int) * 8);
        i2 = new_sym_var(sizeof(int) * 8);
        alteraStock('+', i1, i2);
        break;

      case 'r':
        i1 = new_sym_var(sizeof(int) * 8);
        i2 = new_sym_var(sizeof(int) * 8);
        alteraStock('-', i1, i2);
        break;

      case 'p':
        alteraPreco();
        break;

      case 'k':
        listaProdutos();
        break;

      case 'N':
        novaEncomenda();
        break;

      case 'A':
        adicionaProdutoEncomenda();
        break;

      case 'R':
        removeProdutoEncomenda();
        break;

      case 'K':
        listaEncomenda();
        break;

      case 'E':
        infoProduto();
        break;

      case 'C':
        calculaPreco();
        break;

      case 'm':
        maxProduto();
        break;

      case 'l':
        ordenaProdutos();
        break;

      case 'L':
        ordenaEncomenda();
        break;

      case 'x':
        return 0;
        c = getchar();

    }

  }

}
