/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h> 


void adiciona_produto();
void aumenta_stock();
void cria_encomenda();
void aumenta_encomenda();
void diminui_stock();
void diminui_encomenda();
void custo_encomenda();
void altera_preco();
void produto_na_encomenda();
void maximo_produto();
void lista_produtos_crescente();
void lista_produtos_alfabetico();
void lista_produtos();
void descricao_encomenda();
typedef struct 
{
  char descricao[63];
  int preco;
  int peso;
  int qtd_stock;
} produto;
typedef struct 
{
  int quantidades[10000];
  int peso;
} encomenda;
produto stock[10000];
int conta_stock;
encomenda encomendas[500];
int conta_encomendas;
int ordem[10000];
int mudancas;
int sorted;
int mudanca_preco;
int main()
{
  int comando;
  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      case 'a':
        adiciona_produto();
        break;

      case 'q':
        aumenta_stock();
        break;

      case 'N':
        cria_encomenda();
        break;

      case 'A':
        aumenta_encomenda();
        break;

      case 'r':
        diminui_stock();
        break;

      case 'R':
        diminui_encomenda();
        break;

      case 'C':
        custo_encomenda();
        break;

      case 'p':
        altera_preco();
        break;

      case 'E':
        produto_na_encomenda();
        break;

      case 'm':
        maximo_produto();
        break;

      case 'l':
        lista_produtos_crescente();
        break;

      case 'L':
        lista_produtos_alfabetico();
        break;

      case 'k':
        lista_produtos();
        break;

      case 'K':
        descricao_encomenda();
        break;

      default:
        break;

    }

  }

  return 0;
}

int preco(int produto)
{
  return stock[produto].preco;
}

int peso_p(int produto)
{
  return stock[produto].peso;
}

int qtd_p(int produto)
{
  return stock[produto].qtd_stock;
}

int peso_e(int encomenda)
{
  return encomendas[encomenda].peso;
}

int qtd_e(int encomenda, int produto)
{
  return encomendas[encomenda].quantidades[produto];
}

int encomenda_falsa(int encomenda)
{
  return conta_encomendas <= encomenda;
}

int produto_falso(int produto)
{
  return conta_stock <= produto;
}

int menor_preco(int a, int b)
{
  return (stock[a].preco < stock[b].preco) || ((stock[a].preco == stock[b].preco) && (a < b));
}

int alfabetico(int a, int b)
{
  return strcmp(stock[a].descricao, stock[b].descricao) < 0;
}

void merge(int v[], int inicio, int m, int fim, int (*condicao)(int, int))
{
  int aux[10000];
  int i;
  int j;
  int k;
  for (i = m + 1; i > inicio; i--)
  {
    aux[i - 1] = v[i - 1];
  }

  for (j = m; j < fim; j++)
  {
    aux[(fim + m) - j] = v[j + 1];
  }

  for (k = inicio; k <= fim; k++)
  {
    if (condicao(aux[j], aux[i]))
    {
      {
        v[k] = aux[j--];
      }
    }
    else
    {
      {
        v[k] = aux[i++];
      }
    }

  }

}

void merge_sort(int inicio, int fim, int v[], int (*condicao)(int, int))
{
  int m = (fim + inicio) / 2;
  if (fim <= inicio)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  merge_sort(inicio, m, v, condicao);
  merge_sort(m + 1, fim, v, condicao);
  merge(v, inicio, m, fim, condicao);
}

void insert_sort(int inicio, int fim, int (*condicao)(int, int))
{
  int i;
  int k;
  int inserir;
  for (i = inicio; i != (fim + 1); i++)
  {
    inserir = ordem[i];
    k = i - 1;
    while ((k >= 0) && condicao(inserir, ordem[k]))
    {
      ordem[k + 1] = ordem[k];
      k--;
    }

    ordem[k + 1] = inserir;
  }

}

void adiciona_produto()
{
  for (int stock_index = 0; stock_index < 10; stock_index++)
  {
    stock[conta_stock].descricao[stock_index] = new_sym_var(sizeof(char) * 8);
  }

  stock[conta_stock].descricao[10 - 1] = '\0';
  stock[conta_stock].preco = new_sym_var(sizeof(int) * 8);
  stock[conta_stock].peso = new_sym_var(sizeof(int) * 8);
  stock[conta_stock].qtd_stock = new_sym_var(sizeof(int) * 8);
  ordem[conta_stock] = conta_stock;
  mudancas += 1;
  printf("Novo produto %d.\n", conta_stock++);
}

void aumenta_stock()
{
  int qtd;
  int produto;
  produto = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (produto_falso(produto))
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", produto);
    }
  }
  else
  {
    {
      stock[produto].qtd_stock += qtd;
    }
  }

}

void cria_encomenda()
{
  printf("Nova encomenda %d.\n", conta_encomendas++);
}

void aumenta_encomenda()
{
  int encomenda;
  int produto;
  int qtd;
  encomenda = new_sym_var(sizeof(int) * 8);
  produto = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (encomenda_falsa(encomenda))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", produto, encomenda);
    }
  }
  else
  {
    if (produto_falso(produto))
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", produto, encomenda);
      }
    }
    else
    {
      if (qtd > qtd_p(produto))
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", produto, encomenda);
        }
      }
      else
      {
        if ((peso_e(encomenda) + (peso_p(produto) * qtd)) > 200)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", produto, encomenda);
          }
        }
        else
        {
          {
            encomendas[encomenda].quantidades[produto] += qtd;
            stock[produto].qtd_stock -= qtd;
            encomendas[encomenda].peso += qtd * peso_p(produto);
          }
        }

      }

    }

  }

}

void diminui_stock()
{
  int qtd;
  int produto;
  produto = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (produto_falso(produto))
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", produto);
    }
  }
  else
  {
    if (qtd > qtd_p(produto))
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, produto);
      }
    }
    else
    {
      {
        stock[produto].qtd_stock -= qtd;
      }
    }

  }

}

void diminui_encomenda()
{
  int encomenda;
  int produto;
  encomenda = new_sym_var(sizeof(int) * 8);
  produto = new_sym_var(sizeof(int) * 8);
  if (encomenda_falsa(encomenda))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", produto, encomenda);
    }
  }
  else
  {
    if (produto_falso(produto))
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", produto, encomenda);
      }
    }
    else
    {
      {
        stock[produto].qtd_stock += qtd_e(encomenda, produto);
        encomendas[encomenda].peso -= peso_p(produto) * qtd_e(encomenda, produto);
        encomendas[encomenda].quantidades[produto] = 0;
      }
    }

  }

}

void custo_encomenda()
{
  int encomenda;
  int custo = 0;
  int i;
  encomenda = new_sym_var(sizeof(int) * 8);
  if (encomenda_falsa(encomenda))
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", encomenda);
    }
  }
  else
  {
    {
      for (i = 0; i != conta_stock; i++)
      {
        if (qtd_e(encomenda, i))
        {
          {
            custo += preco(i) * qtd_e(encomenda, i);
          }
        }
        else
        {
          
        }

      }

      printf("Custo da encomenda %d %d.\n", encomenda, custo);
    }
  }

}

void altera_preco()
{
  int produto;
  int preco;
  produto = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (produto_falso(produto))
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", produto);
    }
  }
  else
  {
    {
      stock[produto].preco = preco;
      mudanca_preco = 1;
    }
  }

}

void produto_na_encomenda()
{
  int encomenda;
  int produto;
  encomenda = new_sym_var(sizeof(int) * 8);
  produto = new_sym_var(sizeof(int) * 8);
  if (encomenda_falsa(encomenda))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", encomenda);
    }
  }
  else
  {
    if (produto_falso(produto))
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", produto);
      }
    }
    else
    {
      {
        printf("%s %d.\n", stock[produto].descricao, qtd_e(encomenda, produto));
      }
    }

  }

}

void maximo_produto()
{
  int produto;
  int k;
  int maximo = 0;
  int maior;
  produto = new_sym_var(sizeof(int) * 8);
  if (produto_falso(produto))
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", produto);
    }
  }
  else
  {
    {
      for (k = 0; k != conta_encomendas; k++)
      {
        if (qtd_e(k, produto) > maximo)
        {
          {
            maior = k;
            maximo = qtd_e(k, produto);
          }
        }
        else
        {
          
        }

      }

      if (maximo)
      {
        {
          printf("Maximo produto %d %d %d.\n", produto, maior, maximo);
        }
      }
      else
      {
        
      }

    }
  }

}

void lista_produtos_crescente()
{
  int j;
  printf("Produtos\n");
  if (((mudancas > 15) || (!sorted)) || mudanca_preco)
  {
    {
      merge_sort(0, conta_stock - 1, ordem, menor_preco);
      mudancas = 0;
      sorted = 1;
      mudanca_preco = 0;
    }
  }
  else
  {
    if (mudancas)
    {
      {
        insert_sort(conta_stock - mudancas, conta_stock - 1, menor_preco);
      }
    }
    else
    {
      
    }

  }

  for (j = 0; j != conta_stock; j++)
  {
    printf("* %s %d %d\n", stock[ordem[j]].descricao, preco(ordem[j]), qtd_p(ordem[j]));
  }

}

void lista_produtos_alfabetico()
{
  int encomenda;
  int ordem_e[10000];
  int n_produtos = 0;
  int i;
  int k;
  encomenda = new_sym_var(sizeof(int) * 8);
  if (encomenda_falsa(encomenda))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", encomenda);
    }
  }
  else
  {
    {
      printf("Encomenda %d\n", encomenda);
      for (i = 0; i != conta_stock; i++)
      {
        if (qtd_e(encomenda, i))
        {
          {
            ordem_e[n_produtos++] = i;
          }
        }
        else
        {
          
        }

      }

      merge_sort(0, n_produtos - 1, ordem_e, alfabetico);
      for (k = 0; k != n_produtos; k++)
      {
        printf("* %s %d %d\n", stock[ordem_e[k]].descricao, preco(ordem_e[k]), qtd_e(encomenda, ordem_e[k]));
      }

    }
  }

}

void lista_produtos()
{
  int k;
  printf("Produtos\n");
  for (k = 0; k != conta_stock; k++)
  {
    printf("%s %d %d\n", stock[k].descricao, preco(k), qtd_p(k));
  }

}

void descricao_encomenda()
{
  int encomenda;
  int p;
  encomenda = new_sym_var(sizeof(int) * 8);
  printf("Produtos na encomenda %d\n", encomenda);
  for (p = 0; p != conta_stock; p++)
  {
    if (qtd_e(encomenda, p))
    {
      {
        printf("%s %d\n", stock[p].descricao, qtd_e(encomenda, p));
      }
    }
    else
    {
      
    }

  }

}
