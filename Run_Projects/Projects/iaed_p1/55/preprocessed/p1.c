/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int idp;
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
} produto;
typedef struct 
{
  int identificador;
  int quantidade;
} produtosEncomenda;
typedef struct 
{
  produtosEncomenda produtosEncomenda[200];
  int pesoTotal;
  int indiceVetor;
} encomenda;
int numProdutos = 0;
int numEncomendas = 0;
int arg1;
int arg2;
int arg3;
int idpEncomenda;
produto produtos[10000];
encomenda encomendas[500];
void exch(int produtos[], int a, int b)
{
  int temp = produtos[a];
  produtos[a] = produtos[b];
  produtos[b] = temp;
}

void sort(int tab[], int l, int r, int flag)
{
  int left = l;
  int right = r;
  int pivot = tab[(left + right) / 2];
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  while (left <= right)
  {
    for (; (flag == 0) ? (strcmp(produtos[tab[left]].descricao, produtos[pivot].descricao) < 0) : (((produtos[tab[left]].preco - produtos[pivot].preco) == 0) ? (produtos[tab[left]].idp < produtos[pivot].idp) : (produtos[tab[left]].preco < produtos[pivot].preco)); left++)
      ;

    for (; (flag == 0) ? (strcmp(produtos[pivot].descricao, produtos[tab[right]].descricao) < 0) : (((produtos[pivot].preco - produtos[tab[right]].preco) == 0) ? (produtos[pivot].idp < produtos[tab[right]].idp) : (produtos[pivot].preco < produtos[tab[right]].preco)); right--)
      ;

    if (right >= left)
    {
      exch(tab, left, right);
      right--;
      left++;
    }
    else
    {
      
    }

  }

  sort(tab, left, r, flag);
  sort(tab, l, right, flag);
}

void adicionarProduto()
{
  for (int produtos_index = 0; produtos_index < 10; produtos_index++)
  {
    produtos[numProdutos].descricao[produtos_index] = new_sym_var(sizeof(char) * 8);
  }

  produtos[numProdutos].descricao[10 - 1] = '\0';
  produtos[numProdutos].preco = new_sym_var(sizeof(int) * 8);
  produtos[numProdutos].peso = new_sym_var(sizeof(int) * 8);
  produtos[numProdutos].quantidade = new_sym_var(sizeof(int) * 8);
  produtos[numProdutos].idp = numProdutos;
  printf("Novo produto %d.\n", numProdutos++);
}

void adicionarStock(int idp, int qtd)
{
  if (idp < numProdutos)
  {
    produtos[idp].quantidade += qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", arg1);
  }

}

void removerStock(int idp, int qtd)
{
  if (idp >= numProdutos)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", arg1);
  }
  else
  {
    if (qtd > produtos[idp].quantidade)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", arg2, arg1);
    }
    else
    {
      produtos[idp].quantidade -= qtd;
    }

  }

}

void alterarPreco()
{
  arg1 = new_sym_var(sizeof(int) * 8);
  arg2 = new_sym_var(sizeof(int) * 8);
  if (arg1 >= numProdutos)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", arg1);
  }
  else
  {
    produtos[arg1].preco = arg2;
  }

}

void listarProdutos(int produtosSorted[])
{
  int i;
  printf("Produtos\n");
  for (i = 0; i < numProdutos; i++)
  {
    printf("* %s %d %d\n", produtos[produtosSorted[i]].descricao, produtos[produtosSorted[i]].preco, produtos[produtosSorted[i]].quantidade);
  }

}

int ordenarProdutos(int produtosSorted[], int indiceProdutoSort)
{
  int i;
  for (i = indiceProdutoSort; i < numProdutos; i++)
  {
    produtosSorted[i] = i;
  }

  sort(produtosSorted, 0, numProdutos - 1, 1);
  listarProdutos(produtosSorted);
  return numProdutos;
}

void adicionarEncomenda()
{
  printf("Nova encomenda %d.\n", numEncomendas++);
}

int encontrarprodutosEncomenda(int ide, int idp)
{
  int i;
  for (i = 0; i < encomendas[ide].indiceVetor; i++)
  {
    if (idp == encomendas[ide].produtosEncomenda[i].identificador)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

int verificaAdicaoEncomenda(int ide, int idp, int qtd)
{
  int peso;
  if (ide >= numEncomendas)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return 0;
  }
  else
  {
    
  }

  if (idp >= numProdutos)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return 0;
  }
  else
  {
    
  }

  if (qtd > produtos[idp].quantidade)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return 0;
  }
  else
  {
    
  }

  peso = encomendas[arg1].pesoTotal + (arg3 * produtos[arg2].peso);
  if (peso > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", arg2, arg1);
    return 0;
  }
  else
  {
    
  }

  return peso;
}

void adicionarprodutosEncomenda()
{
  int peso;
  arg1 = new_sym_var(sizeof(int) * 8);
  arg2 = new_sym_var(sizeof(int) * 8);
  arg3 = new_sym_var(sizeof(int) * 8);
  if ((peso = verificaAdicaoEncomenda(arg1, arg2, arg3)) != 0)
  {
    if ((idpEncomenda = encontrarprodutosEncomenda(arg1, arg2)) == (-1))
    {
      idpEncomenda = encomendas[arg1].indiceVetor;
      encomendas[arg1].indiceVetor++;
    }
    else
    {
      
    }

    removerStock(arg2, arg3);
    encomendas[arg1].pesoTotal = peso;
    encomendas[arg1].produtosEncomenda[idpEncomenda].quantidade += arg3;
    encomendas[arg1].produtosEncomenda[idpEncomenda].identificador = arg2;
  }
  else
  {
    
  }

}

int verificaRemocaoEncomenda(int ide, int idp)
{
  if (ide >= numEncomendas)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", arg2, arg1);
    return 0;
  }
  else
  {
    if (idp >= numProdutos)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", arg2, arg1);
      return 0;
    }
    else
    {
      
    }

  }

  return 1;
}

void removerprodutosEncomenda()
{
  int quantidade;
  arg1 = new_sym_var(sizeof(int) * 8);
  arg2 = new_sym_var(sizeof(int) * 8);
  if (verificaRemocaoEncomenda(arg1, arg2))
  {
    idpEncomenda = encontrarprodutosEncomenda(arg1, arg2);
    quantidade = encomendas[arg1].produtosEncomenda[idpEncomenda].quantidade;
    if (idpEncomenda != (-1))
    {
      adicionarStock(arg2, quantidade);
      encomendas[arg1].pesoTotal -= quantidade * produtos[arg2].peso;
      encomendas[arg1].produtosEncomenda[idpEncomenda] = encomendas[arg1].produtosEncomenda[--encomendas[arg1].indiceVetor];
      encomendas[arg1].produtosEncomenda[encomendas[arg1].indiceVetor].quantidade = 0;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

}

void custoEncomenda()
{
  int i;
  int custo;
  arg1 = new_sym_var(sizeof(int) * 8);
  if (arg1 >= numEncomendas)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", arg1);
  }
  else
  {
    for (i = 0, custo = 0; i <= numProdutos; i++)
    {
      idpEncomenda = encontrarprodutosEncomenda(arg1, i);
      if (idpEncomenda != (-1))
      {
        custo += encomendas[arg1].produtosEncomenda[idpEncomenda].quantidade * produtos[i].preco;
      }
      else
      {
        
      }

    }

    printf("Custo da encomenda %d %d.\n", arg1, custo);
  }

}

void listarprodutosEncomenda()
{
  int quantidade;
  arg1 = new_sym_var(sizeof(int) * 8);
  arg2 = new_sym_var(sizeof(int) * 8);
  idpEncomenda = encontrarprodutosEncomenda(arg1, arg2);
  if (arg2 >= numProdutos)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", arg2);
  }
  else
  {
    if (arg1 >= numEncomendas)
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", arg1);
    }
    else
    {
      if (idpEncomenda == (-1))
      {
        quantidade = 0;
      }
      else
      {
        quantidade = encomendas[arg1].produtosEncomenda[idpEncomenda].quantidade;
      }

      printf("%s %d.\n", produtos[arg2].descricao, quantidade);
    }

  }

}

void maxprodutosEncomenda()
{
  int encomendaM;
  int idp;
  int maxOcorrencias;
  int i;
  arg1 = new_sym_var(sizeof(int) * 8);
  if (arg1 >= numProdutos)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", arg1);
  }
  else
  {
    encomendaM = -1, maxOcorrencias = 0;
    for (i = 0; i < numEncomendas; i++)
    {
      idp = encontrarprodutosEncomenda(i, arg1);
      if ((encomendas[i].produtosEncomenda[idp].quantidade > maxOcorrencias) && (idp != (-1)))
      {
        encomendaM = i;
        maxOcorrencias = encomendas[i].produtosEncomenda[idp].quantidade;
      }
      else
      {
        
      }

    }

    if (encomendaM != (-1))
    {
      printf("Maximo produto %d %d %d.\n", arg1, encomendaM, maxOcorrencias);
    }
    else
    {
      
    }

  }

}

void listarProdutosEncomendas(int produtosSorted[], int len, int ide)
{
  int i;
  int quantidade;
  int IDProduto;
  for (i = 0; i < len; i++)
  {
    IDProduto = produtosSorted[i];
    idpEncomenda = encontrarprodutosEncomenda(ide, IDProduto);
    if ((quantidade = encomendas[ide].produtosEncomenda[idpEncomenda].quantidade) != 0)
    {
      printf("* %s %d %d\n", produtos[IDProduto].descricao, produtos[IDProduto].preco, quantidade);
    }
    else
    {
      
    }

  }

}

void ordenarProdutosEncomendas()
{
  int i;
  int indiceVetor;
  int produtosSortedEncomenda[200];
  arg1 = new_sym_var(sizeof(int) * 8);
  indiceVetor = encomendas[arg1].indiceVetor;
  if (arg1 >= numEncomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", arg1);
  }
  else
  {
    for (i = 0; i < indiceVetor; i++)
    {
      produtosSortedEncomenda[i] = encomendas[arg1].produtosEncomenda[i].identificador;
    }

    sort(produtosSortedEncomenda, 0, indiceVetor - 1, 0);
    printf("Encomenda %d\n", arg1);
    listarProdutosEncomendas(produtosSortedEncomenda, indiceVetor, arg1);
  }

}

int main()
{
  char c;
  int indiceProdutoSort = 0;
  int produtosSorted[10000];
  while ((c = getchar()) != 'x')
  {
    switch (c)
    {
      case 'a':
        adicionarProduto();
        break;

      case 'q':
        arg1 = new_sym_var(sizeof(int) * 8);
        arg2 = new_sym_var(sizeof(int) * 8);
        adicionarStock(arg1, arg2);
        break;

      case 'N':
        adicionarEncomenda();
        break;

      case 'A':
        adicionarprodutosEncomenda();
        break;

      case 'r':
        arg1 = new_sym_var(sizeof(int) * 8);
        arg2 = new_sym_var(sizeof(int) * 8);
        removerStock(arg1, arg2);
        break;

      case 'R':
        removerprodutosEncomenda();
        break;

      case 'C':
        custoEncomenda();
        break;

      case 'p':
        alterarPreco();
        break;

      case 'E':
        listarprodutosEncomenda();
        break;

      case 'm':
        maxprodutosEncomenda();
        break;

      case 'l':
        indiceProdutoSort = ordenarProdutos(produtosSorted, indiceProdutoSort);
        break;

      case 'L':
        ordenarProdutosEncomendas();
        break;

    }

  }

  return 0;
}
