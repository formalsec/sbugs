/*File generated by PreProcessor.py*/


#include <stdio.h>


struct Detalhes_Produtos
{
  char descricao[63];
  int preco;
  int peso;
  int quantidade_stock;
} produtos[9999];
struct Detalhes_Produtos;
int Encomendas[500][10000];
int main()
{
  int Correr = 1;
  int Produto = 0;
  int Encomenda = -1;
  char Comando;
  while (Correr == 1)
  {
    Comando = getchar();
    getchar();
    if (Comando == 'a')
    {
      for (int produtos_index = 0; produtos_index < 10; produtos_index++)
      {
        produtos[Produto].descricao[produtos_index] = new_sym_var(sizeof(char) * 8);
      }

      produtos[Produto].descricao[10 - 1] = '\0';
      produtos[Produto].preco = new_sym_var(sizeof(int) * 8);
      produtos[Produto].peso = new_sym_var(sizeof(int) * 8);
      produtos[Produto].quantidade_stock = new_sym_var(sizeof(int) * 8);
      printf("Novo produto %d.\n", Produto);
      Produto++;
    }
    else
    {
      
    }

    if (Comando == 'q')
    {
      int produto;
      int quantidade;
      produto = new_sym_var(sizeof(int) * 8);
      quantidade = new_sym_var(sizeof(int) * 8);
      if (Produto < produto)
      {
        printf("Impossivel adicionar produto %d ao stock.Produto inexistente.\n", produto);
      }
      else
      {
        produtos[produto].quantidade_stock = produtos[produto].quantidade_stock + quantidade;
      }

    }
    else
    {
      
    }

    if (Comando == 'N')
    {
      Encomenda++;
      printf("Nova encomenda %d.\n", Encomenda);
    }
    else
    {
      
    }

    if (Comando == 'A')
    {
      int ide;
      int idp;
      int qtd;
      ide = new_sym_var(sizeof(int) * 8);
      idp = new_sym_var(sizeof(int) * 8);
      qtd = new_sym_var(sizeof(int) * 8);
      if (Encomenda < ide)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Ecomenda inexistente.\n", idp, ide);
      }
      else
      {
        
      }

      if (Produto < idp)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
      else
      {
        
      }

      if (produtos[idp].quantidade_stock < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        int prod = 0;
        int peso = 0;
        while (prod <= Produto)
        {
          peso = peso + (produtos[prod].peso * Encomendas[ide][prod]);
        }

        peso = peso + (produtos[idp].peso * qtd);
        if (200 < peso)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idp, ide, 200);
        }
        else
        {
          produtos[idp].quantidade_stock = produtos[idp].quantidade_stock - qtd;
          Encomendas[ide][idp] = Encomendas[ide][idp] + ide;
        }

      }

    }
    else
    {
      
    }

    if (Comando == 'r')
    {
      int produto;
      int quantidade;
      int qtd_final;
      produto = new_sym_var(sizeof(int) * 8);
      quantidade = new_sym_var(sizeof(int) * 8);
      if (Produto < produto)
      {
        printf("Impossivel remover stock do produto %d.Produto inexistente.\n", produto);
      }
      else
      {
        
      }

      qtd_final = produtos[produto].quantidade_stock - quantidade;
      if (qtd_final <= 0)
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insoficiente.\n", quantidade, produto);
      }
      else
      {
        produtos[produto].quantidade_stock = produtos[produto].quantidade_stock - quantidade;
      }

    }
    else
    {
      
    }

    if (Comando == 'R')
    {
      int ide;
      int idp;
      ide = new_sym_var(sizeof(int) * 8);
      idp = new_sym_var(sizeof(int) * 8);
      if (Encomenda < ide)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Ecomenda inexistente.\n", idp, ide);
      }
      else
      {
        
      }

      if (Produto < idp)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
      else
      {
        produtos[idp].quantidade_stock = produtos[idp].quantidade_stock + Encomendas[ide][idp];
        Encomendas[ide][idp] = 0;
      }

    }
    else
    {
      
    }

    if (Comando == 'C')
    {
      int ide;
      int prod = 0;
      int custo = 0;
      ide = new_sym_var(sizeof(int) * 8);
      if (Encomenda < ide)
      {
        printf("Impossivel calcular custo da encomenda %d. Ecomenda inexistente.\n", ide);
      }
      else
      {
        while (prod <= Produto)
        {
          custo = custo + (produtos[prod].preco * Encomendas[ide][prod]);
        }

        printf("Custo da encomenda %d %d.\n", ide, custo);
      }

    }
    else
    {
      
    }

    if (Comando == 'p')
    {
      int idp;
      int preco;
      idp = new_sym_var(sizeof(int) * 8);
      preco = new_sym_var(sizeof(int) * 8);
      if (Produto < idp)
      {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    if (Comando == 'E')
    {
      int ide;
      int idp;
      ide = new_sym_var(sizeof(int) * 8);
      idp = new_sym_var(sizeof(int) * 8);
      if (Encomenda < ide)
      {
        printf("Impossivel listar encomenda %d. Ecomenda inexistente.", ide);
      }
      else
      {
        
      }

      if (Produto < idp)
      {
        printf("Impossivel listar produto %d.Produto enexistente.", idp);
      }
      else
      {
        printf("%s %d\n", produtos[idp].descricao, Encomendas[ide][idp]);
      }

    }
    else
    {
      
    }

    if (Comando == 'm')
    {
      int cont = 0;
      int idp;
      int total = 0;
      int posicao = 0;
      idp = new_sym_var(sizeof(int) * 8);
      if (Produto < idp)
      {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        
      }

      while (cont != Encomenda)
      {
        if (total < Encomendas[cont][idp])
        {
          total = Encomendas[cont][idp];
          posicao = cont;
        }
        else
        {
          
        }

        cont++;
      }

      printf("Maximo produto %d %d %d\n", idp, posicao, total);
    }
    else
    {
      
    }

    if (Comando == 'l')
    {
    }
    else
    {
      
    }

    if (Comando == 'L')
    {
    }
    else
    {
      
    }

    if (Comando == 'x')
    {
      Correr = 0;
    }
    else
    {
      
    }

  }

  return 0;
}

