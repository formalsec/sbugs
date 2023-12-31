#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int CURRENT_IDP = 0;
int CURRENT_IDE = 0;
typedef struct 
{
  int idp;
  char desc[63];
  int preco;
  int peso;
  int qtd;
} Produto;
typedef struct 
{
  int ide;
  int peso;
  int nprodutos;
  int produtos[200][2];
} Encomenda;
int less_price(Produto p1, Produto p2);
int less_abc(Produto p1, Produto p2);
void exch(Produto *p1, Produto *p2);
int partition(Produto produto[], int left, int right, char method);
void quicksort(Produto produto[], int left, int right, char method);
void copiarProdutos(Produto dest[], Produto src[]);
void copiarProdutosfromEncomenda(Produto dest[], Encomenda enc_src, Produto prod_src[]);
void imprimirProdutos(Produto produtos[], int size);
int procuraProduto_Encomenda(int idp, Encomenda enc);
void novoProduto(char *command, Produto produtos[]);
void adicionarStock(char *command, Produto produtos[]);
void novaEncomenda(Encomenda encomendas[]);
void encomendarProduto(char *command, Produto produtos[], Encomenda encomendas[]);
void removerStock(char *command, Produto produtos[]);
void removerProdutoDeEncomenda(char *command, Produto produtos[], Encomenda encomendas[]);
void calcularCustoEncomenda(char *command, Produto produtos[], Encomenda encomendas[]);
void alterarPreco(char *command, Produto produtos[]);
void listarProdutoEmEncomenda(char *command, Produto produtos[], Encomenda encomendas[]);
void listarEncomendaComProdutoMax(char *command, Encomenda encomendas[]);
void listarProdutosPorPreco(Produto produtos[]);
void listarProdutosEmEncomendaPorABC(char *command, Produto produtos[], Encomenda encomendas[]);
int main()
{
  Produto produtos[10000];
  Encomenda encomendas[500];
  char command[100];
  while (1)
  {
    fgets(command, 100, stdin);
    switch (command[0])
    {
      case 'a':
        novoProduto(command, produtos);
        break;

      case 'q':
        adicionarStock(command, produtos);
        break;

      case 'N':
        novaEncomenda(encomendas);
        break;

      case 'A':
        encomendarProduto(command, produtos, encomendas);
        break;

      case 'r':
        removerStock(command, produtos);
        break;

      case 'R':
        removerProdutoDeEncomenda(command, produtos, encomendas);
        break;

      case 'C':
        calcularCustoEncomenda(command, produtos, encomendas);
        break;

      case 'p':
        alterarPreco(command, produtos);
        break;

      case 'E':
        listarProdutoEmEncomenda(command, produtos, encomendas);
        break;

      case 'm':
        listarEncomendaComProdutoMax(command, encomendas);
        break;

      case 'l':
        listarProdutosPorPreco(produtos);
        break;

      case 'L':
        listarProdutosEmEncomendaPorABC(command, produtos, encomendas);
        break;

      case 'x':
        return 0;

      default:
        printf("ERROR: Unknown command\n");

    }

  }

  return 1;
}

int less_price(Produto p1, Produto p2)
{
  int res = p1.preco - p2.preco;
  if ((res < 0) || ((res == 0) && (p1.idp < p2.idp)))
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

int less_abc(Produto p1, Produto p2)
{
  int res = strcmp(p1.desc, p2.desc);
  if ((res < 0) || ((res == 0) && (p1.idp < p2.idp)))
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

void exch(Produto *p1, Produto *p2)
{
  Produto ptemp;
  ptemp = *p1;
  *p1 = *p2;
  *p2 = ptemp;
}

int partition(Produto produtos[], int left, int right, char method)
{
  int i = left - 1;
  int j = right;
  Produto p1 = produtos[left];
  Produto p2 = produtos[((right - left) / 2) + left];
  Produto p3 = produtos[right - 1];
  switch (method)
  {
    case 'l':
      if ((less_price(p1, p2) && less_price(p2, p3)) || (less_price(p3, p2) && less_price(p2, p1)))
    {
      p1 = p2;
    }
    else
    {
      if ((less_price(p1, p3) && less_price(p3, p2)) || (less_price(p2, p3) && less_price(p3, p1)))
      {
        p1 = p3;
      }
      else
      {
        
      }

    }

      while (1)
    {
      j--;
      while (less_price(p1, produtos[j]))
      {
        j--;
      }

      i++;
      while (less_price(produtos[i], p1))
      {
        i++;
      }

      if (i < j)
      {
        exch(&produtos[i], &produtos[j]);
      }
      else
      {
        return j + 1;
      }

    }

      break;

    case 'L':
      if ((less_abc(p1, p2) && less_abc(p2, p3)) || (less_abc(p3, p2) && less_abc(p2, p1)))
    {
      p1 = p2;
    }
    else
    {
      if ((less_abc(p1, p3) && less_abc(p3, p2)) || (less_abc(p2, p3) && less_abc(p3, p1)))
      {
        p1 = p3;
      }
      else
      {
        
      }

    }

      while (1)
    {
      j--;
      while (less_abc(p1, produtos[j]))
      {
        j--;
      }

      i++;
      while (less_abc(produtos[i], p1))
      {
        i++;
      }

      if (i < j)
      {
        exch(&produtos[i], &produtos[j]);
      }
      else
      {
        return j + 1;
      }

    }

      break;

    default:
      break;

  }

  return -1;
}

void quicksort(Produto produtos[], int left, int right, char method)
{
  if (left < (right - 1))
  {
    int i = partition(produtos, left, right, method);
    quicksort(produtos, left, i, method);
    quicksort(produtos, i, right, method);
  }
  else
  {
    
  }

}

void copiarProdutos(Produto dest[], Produto src[])
{
  int i;
  for (i = 0; i < CURRENT_IDP; i++)
  {
    dest[i] = src[i];
  }

}

void copiarProdutosDeEncomenda(Produto dest[], Encomenda enc_src, Produto prod_src[])
{
  int i;
  int n = enc_src.nprodutos;
  for (i = 0; i < n; i++)
  {
    dest[i] = prod_src[enc_src.produtos[i][0]];
    dest[i].qtd = enc_src.produtos[i][1];
  }

}

void imprimirProdutos(Produto produtos[], int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    printf("* %s %d %d\n", produtos[i].desc, produtos[i].preco, produtos[i].qtd);
  }

}

int procuraProduto_Encomenda(int idp, Encomenda enc)
{
  int i;
  for (i = 0; i < enc.nprodutos; i++)
  {
    if (enc.produtos[i][0] == idp)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

void novoProduto(char *command, Produto produtos[])
{
  int idp;
  int preco;
  int peso;
  int qtd;
  char *token;
  char *desc;
  token = strtok(command, " ");
  idp = CURRENT_IDP;
  desc = (token = strtok(0, ":"));
  preco = atoi(token = strtok(0, ":"));
  peso = atoi(token = strtok(0, ":"));
  qtd = atoi(token = strtok(0, "\n"));
  produtos[idp].idp = idp;
  strcpy(produtos[idp].desc, desc);
  produtos[idp].preco = preco;
  produtos[idp].peso = peso;
  produtos[idp].qtd = qtd;
  CURRENT_IDP++;
  printf("Novo produto %d.\n", idp);
}

void adicionarStock(char *command, Produto produtos[])
{
  int idp;
  int qtd;
  char *token;
  token = strtok(command, " ");
  idp = atoi(token = strtok(0, ":"));
  if (idp >= CURRENT_IDP)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  qtd = atoi(token = strtok(0, "\n"));
  produtos[idp].qtd += qtd;
}

void novaEncomenda(Encomenda encomendas[])
{
  int ide;
  ide = CURRENT_IDE;
  encomendas[ide].ide = ide;
  encomendas[ide].peso = 0;
  encomendas[ide].nprodutos = 0;
  CURRENT_IDE++;
  printf("Nova encomenda %d.\n", ide);
}

void encomendarProduto(char *command, Produto produtos[], Encomenda encomendas[])
{
  int ide;
  int idp;
  int qtd;
  int id;
  int n;
  char *token;
  token = strtok(command, " ");
  ide = atoi(token = strtok(0, ":"));
  idp = atoi(token = strtok(0, ":"));
  if (ide >= CURRENT_IDE)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (idp >= CURRENT_IDP)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  qtd = atoi(token = strtok(0, "\n"));
  if ((qtd - produtos[idp].qtd) > 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if ((encomendas[ide].peso + (qtd * produtos[idp].peso)) > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  id = procuraProduto_Encomenda(idp, encomendas[ide]);
  if (id != (-1))
  {
    encomendas[ide].produtos[id][1] += qtd;
  }
  else
  {
    n = encomendas[ide].nprodutos++;
    encomendas[ide].produtos[n][0] = idp;
    encomendas[ide].produtos[n][1] = qtd;
  }

  encomendas[ide].peso += qtd * produtos[idp].peso;
  produtos[idp].qtd -= qtd;
}

void removerStock(char *command, Produto produtos[])
{
  int idp;
  int qtd;
  char *token;
  token = strtok(command, " ");
  idp = atoi(token = strtok(0, ":"));
  if (idp >= CURRENT_IDP)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  qtd = atoi(token = strtok(0, "\n"));
  if ((qtd - produtos[idp].qtd) > 0)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    return;
  }
  else
  {
    
  }

  produtos[idp].qtd -= qtd;
}

void removerProdutoDeEncomenda(char *command, Produto produtos[], Encomenda encomendas[])
{
  int ide;
  int idp;
  int id;
  int qtd;
  int i;
  int n;
  char *token;
  token = strtok(command, " ");
  ide = atoi(token = strtok(0, ":"));
  idp = atoi(token = strtok(0, "\n"));
  if (ide >= CURRENT_IDE)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (idp >= CURRENT_IDP)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  id = procuraProduto_Encomenda(idp, encomendas[ide]);
  if (id != (-1))
  {
    qtd = encomendas[ide].produtos[id][1];
    encomendas[ide].peso -= qtd * produtos[idp].peso;
    produtos[idp].qtd += qtd;
    n = encomendas[ide].nprodutos--;
    for (i = id; i < n; i++)
    {
      encomendas[ide].produtos[i][0] = encomendas[ide].produtos[i + 1][0];
      encomendas[ide].produtos[i][1] = encomendas[ide].produtos[i + 1][1];
    }

  }
  else
  {
    
  }

}

void calcularCustoEncomenda(char *command, Produto produtos[], Encomenda encomendas[])
{
  int ide;
  int i;
  int n;
  int total;
  char *token;
  token = strtok(command, " ");
  ide = atoi(token = strtok(0, "\n"));
  if (ide >= CURRENT_IDE)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  total = 0;
  n = encomendas[ide].nprodutos;
  for (i = 0; i < n; i++)
  {
    total += encomendas[ide].produtos[i][1] * produtos[encomendas[ide].produtos[i][0]].preco;
  }

  printf("Custo da encomenda %d %d.\n", ide, total);
}

void alterarPreco(char *command, Produto produtos[])
{
  int idp;
  int preco;
  char *token;
  token = strtok(command, " ");
  idp = atoi(token = strtok(0, ":"));
  if (idp >= CURRENT_IDP)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  preco = atoi(token = strtok(0, "\n"));
  produtos[idp].preco = preco;
}

void listarProdutoEmEncomenda(char *command, Produto produtos[], Encomenda encomendas[])
{
  int ide;
  int idp;
  int id;
  int qtd;
  char *token;
  token = strtok(command, " ");
  ide = atoi(token = strtok(0, ":"));
  if (ide >= CURRENT_IDE)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  idp = atoi(token = strtok(0, ":"));
  if (idp >= CURRENT_IDP)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  id = procuraProduto_Encomenda(idp, encomendas[ide]);
  if (id != (-1))
  {
    qtd = encomendas[ide].produtos[id][1];
  }
  else
  {
    qtd = 0;
  }

  printf("%s %d.\n", produtos[idp].desc, qtd);
}

void listarEncomendaComProdutoMax(char *command, Encomenda encomendas[])
{
  int idp;
  int max;
  int max_ide;
  int id;
  int i;
  char *token;
  token = strtok(command, " ");
  idp = atoi(token = strtok(0, "\n"));
  if (idp >= CURRENT_IDP)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  if (CURRENT_IDE <= 0)
  {
    return;
  }
  else
  {
    
  }

  max = 0;
  max_ide = -1;
  for (i = 0; i < CURRENT_IDE; i++)
  {
    id = procuraProduto_Encomenda(idp, encomendas[i]);
    if ((id != (-1)) && (encomendas[i].produtos[id][1] > max))
    {
      max = encomendas[i].produtos[id][1];
      max_ide = encomendas[i].ide;
    }
    else
    {
      
    }

  }

  if (max_ide != (-1))
  {
    printf("Maximo produto %d %d %d.\n", idp, max_ide, max);
  }
  else
  {
    
  }

}

void listarProdutosPorPreco(Produto produtos[])
{
  Produto tempProdutos[10000];
  copiarProdutos(tempProdutos, produtos);
  quicksort(tempProdutos, 0, CURRENT_IDP, 'l');
  printf("Produtos\n");
  imprimirProdutos(tempProdutos, CURRENT_IDP);
}

void listarProdutosEmEncomendaPorABC(char *command, Produto produtos[], Encomenda encomendas[])
{
  Produto tempProdutos[10000];
  int ide;
  char *token;
  token = strtok(command, " ");
  ide = atoi(token = strtok(0, "\n"));
  if (ide >= CURRENT_IDE)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  copiarProdutosDeEncomenda(tempProdutos, encomendas[ide], produtos);
  quicksort(tempProdutos, 0, encomendas[ide].nprodutos, 'L');
  printf("Encomenda %d\n", ide);
  imprimirProdutos(tempProdutos, encomendas[ide].nprodutos);
}

