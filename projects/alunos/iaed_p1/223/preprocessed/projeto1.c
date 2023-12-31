#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int id;
  char *descricao[64];
  int preco;
  int peso;
  int stock;
} Produto;
typedef struct 
{
  int id;
  Produto produtosEncomenda[200];
  int numeroProdutos;
} Encomenda;
void novoProduto(char *descricao, int preco, int peso, int quantidade);
void adicionaStock(int idp, int quantidade);
void novaEncomenda();
void adicionaProduto(int ide, int idp, int quantidade);
void removeStockProduto(int idp, int quantidade);
void removeProdutoEncomenda(int ide, int idp);
void custoEncomenda(int ide);
void alteraPreco(int idp, int preco);
void listaProdutoEncomenda(int ide, int idp);
void encomendaComMaisProduto(int idp);
void listaTodosProdutos();
void listaTodosProdutosEncomenda(int ide);
void terminaPrograma();
int id_prod = 0;
int id_enc = 0;
Produto produtos[10000];
Encomenda encomendas[500];
int main()
{
  char arg[64];
  char command;
  int arg2;
  int arg3;
  int arg4;
  while (1)
  {
    command = new_sym_var(sizeof(char) * 8);
    switch (command)
    {
      case 'a':
        for (int arg_index = 0; arg_index < 10; arg_index++)
      {
        arg[arg_index] = new_sym_var(sizeof(char) * 8);
      }

        arg[10 - 1] = '\0';
        arg2 = new_sym_var(sizeof(int) * 8);
        arg3 = new_sym_var(sizeof(int) * 8);
        arg4 = new_sym_var(sizeof(int) * 8);
        novoProduto(arg, arg2, arg3, arg4);
        break;

      case 'q':
        arg2 = new_sym_var(sizeof(int) * 8);
        arg3 = new_sym_var(sizeof(int) * 8);
        adicionaStock(arg2, arg3);
        break;

      case 'N':
        novaEncomenda();
        break;

      case 'A':
        arg2 = new_sym_var(sizeof(int) * 8);
        arg3 = new_sym_var(sizeof(int) * 8);
        arg4 = new_sym_var(sizeof(int) * 8);
        adicionaProduto(arg2, arg3, arg4);
        break;

      case 'r':
        arg2 = new_sym_var(sizeof(int) * 8);
        arg3 = new_sym_var(sizeof(int) * 8);
        removeStockProduto(arg2, arg3);
        break;

      case 'R':
        arg2 = new_sym_var(sizeof(int) * 8);
        arg3 = new_sym_var(sizeof(int) * 8);
        removeProdutoEncomenda(arg2, arg3);
        break;

      case 'C':
        arg2 = new_sym_var(sizeof(int) * 8);
        custoEncomenda(arg2);
        break;

      case 'p':
        arg2 = new_sym_var(sizeof(int) * 8);
        arg3 = new_sym_var(sizeof(int) * 8);
        alteraPreco(arg2, arg3);
        break;

      case 'E':
        arg2 = new_sym_var(sizeof(int) * 8);
        arg3 = new_sym_var(sizeof(int) * 8);
        listaProdutoEncomenda(arg2, arg3);
        break;

      case 'm':
        arg2 = new_sym_var(sizeof(int) * 8);
        encomendaComMaisProduto(arg2);
        break;

      case 'l':
        listaTodosProdutos();
        break;

      case 'L':
        arg2 = new_sym_var(sizeof(int) * 8);
        listaTodosProdutosEncomenda(arg2);
        break;

      case 'x':
        terminaPrograma();
        break;

      default:
        break;

    }

    ;
  }

  ;
  return -1;
}

void novoProduto(char *descricao, int preco, int peso, int quantidade)
{
  Produto prod;
  prod.id = id_prod;
  prod.descricao[64] = descricao;
  prod.preco = preco;
  prod.peso = peso;
  prod.stock = quantidade;
  produtos[id_prod] = prod;
  printf("Novo produto %d\n", id_prod);
  id_prod++;
}

void adicionaStock(int idp, int quantidade)
{
  int p;
  for (p = 0; p < 10000; p++)
  {
    if (produtos[p].id == idp)
    {
      produtos[idp].stock += quantidade;
      break;
    }
    else
    {
      
    }

  }

  printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

void novaEncomenda()
{
  Encomenda enc;
  enc.id = id_enc;
  enc.numeroProdutos = 0;
  encomendas[id_enc] = enc;
  printf("Nova encomenda %d\n", id_enc);
  id_enc++;
}

void adicionaProduto(int ide, int idp, int quantidade)
{
  encomendas[ide].produtosEncomenda[encomendas[ide].numeroProdutos] = produtos[idp];
  encomendas[ide].produtosEncomenda[encomendas[ide].numeroProdutos].stock = quantidade;
  encomendas[ide].numeroProdutos++;
}

void removeStockProduto(int idp, int quantidade)
{
  int p;
  for (p = 0; p < 10000; p++)
  {
    if (produtos[p].id == idp)
    {
      if ((produtos[idp].stock - quantidade) < 0)
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
        break;
      }
      else
      {
        produtos[idp].stock -= quantidade;
        break;
      }

    }
    else
    {
      
    }

  }

  printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

void removeProdutoEncomenda(int ide, int idp)
{
  int p;
  int q;
  int e;
  int aux;
  int c;
  for (q = 0; q < 10000; q++)
  {
    if (produtos[q].id == idp)
    {
      for (e = 0; e < 500; e++)
      {
        if (encomendas[e].id == ide)
        {
          for (p = 0; p < encomendas[ide].numeroProdutos; p++)
          {
            if (encomendas[p].id == idp)
            {
              aux = p;
            }
            else
            {
              
            }

          }

          for (c = aux; c < encomendas[ide].numeroProdutos; c++)
          {
            encomendas[ide].produtosEncomenda[c] = encomendas[ide].produtosEncomenda[c + 1];
          }

          break;
        }
        else
        {
          
        }

      }

      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      break;
    }
    else
    {
      
    }

  }

  printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
}

void custoEncomenda(int ide)
{
  int custo;
  int p;
  int e;
  for (e = 0; e < 500; e++)
  {
    if (encomendas[e].id == ide)
    {
      for (p = 0; p < encomendas[ide].numeroProdutos; p++)
        custo += encomendas[ide].produtosEncomenda[p].preco;

      printf("Custo da encomenda %d %d.\n", ide, custo);
      break;
    }
    else
    {
      
    }

  }

  printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}

void alteraPreco(int idp, int preco)
{
  int p;
  for (p = 0; p < 10000; p++)
  {
    if (produtos[p].id == idp)
    {
      produtos[p].preco = preco;
      break;
    }
    else
    {
      
    }

  }

  printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}

void listaProdutoEncomenda(int ide, int idp)
{
  int p;
  int q;
  int e;
  for (q = 0; q < 10000; q++)
  {
    if (produtos[q].id == idp)
    {
      for (e = 0; e < 500; e++)
      {
        if (encomendas[e].id == ide)
        {
          for (p = 0; p < encomendas[ide].numeroProdutos; p++)
          {
            if (encomendas[ide].produtosEncomenda[p].id == idp)
            {
              printf("%s %d.\n", *encomendas[ide].produtosEncomenda[p].descricao, encomendas[ide].produtosEncomenda[p].stock);
            }
            else
            {
              
            }

          }

          break;
        }
        else
        {
          
        }

      }

      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      break;
    }
    else
    {
      
    }

  }

  printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
}

void encomendaComMaisProduto(int idp)
{
  int e;
  int p;
  int q;
  int aux_qtd;
  int aux_nr_enc;
  for (q = 0; q < 10000; q++)
  {
    if (produtos[q].id == idp)
    {
      for (e = 0; e < 500; e++)
      {
        for (p = 0; p < encomendas[e].numeroProdutos; p++)
        {
          if (encomendas[e].produtosEncomenda[p].id == idp)
          {
            if (encomendas[e].produtosEncomenda[p].stock >= aux_qtd)
            {
              aux_qtd = encomendas[e].produtosEncomenda[p].stock;
              aux_nr_enc = e;
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

      printf("Maximo produto %d %d %d.\n", idp, aux_nr_enc, aux_qtd);
      break;
    }
    else
    {
      
    }

  }

  printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
}

void listaTodosProdutos()
{
}

void listaTodosProdutosEncomenda(int ide)
{
  int p;
  p = ide;
  printf("ola %d", p);
}

void terminaPrograma()
{
}

