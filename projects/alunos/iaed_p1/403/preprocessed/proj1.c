#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct produto
{
  int identificador;
  char descricao[63];
  int preco;
  int peso;
  int qtd;
} produto;
produto vetorprodutos[10000];
produto b;
produto ordenado[10000];
typedef struct produtoenco
{
  int qtd_e;
  int idp_e;
  int preco;
} produtoenco;
typedef struct 
{
  int identificador;
  produtoenco produto[10000];
} encomenda;
encomenda p;
encomenda vetorencomenda[500];
void d_a()
{
  int incrimentador = 0;
  char nome[63];
  int c = 0;
  printf("insira o preco: ");
  c = new_sym_var(sizeof(int) * 8);
  b.preco = c;
  printf("insira o peso: ");
  c = new_sym_var(sizeof(int) * 8);
  b.peso = c;
  printf("insira a quantidade em stock: ");
  c = new_sym_var(sizeof(int) * 8);
  b.qtd = c;
  printf("insira a discricao: ");
  nome[63] = new_sym_var(sizeof(char) * 8);
  strcpy(b.descricao, nome);
  b.identificador++;
  if (b.identificador < 10000)
  {
    vetorprodutos[incrimentador] = b;
    incrimentador++;
    printf("Novo produto %d\n", vetorprodutos[incrimentador - 1].identificador);
  }
  else
  {
    
  }

}

void d_q()
{
  int a = 0;
  int i = 0;
  int c = 0;
  printf("insira o identificador do produto: ");
  a = new_sym_var(sizeof(int) * 8);
  printf("insira o stock: ");
  c = new_sym_var(sizeof(int) * 8);
  while (vetorprodutos[i].identificador > 0)
  {
    if (vetorprodutos[i].identificador == a)
    {
      vetorprodutos[i].qtd = vetorprodutos[i].qtd + c;
    }
    else
    {
      printf("Impossivel adicionar produto <idp> ao stock. Produto inexistente.\n");
    }

    i++;
  }

}

void d_N()
{
  int j = 0;
  p.identificador++;
  vetorencomenda[j] = p;
  vetorencomenda[j].identificador = p.identificador;
  j++;
}

void d_A()
{
  int corer = 0;
  int i = 0;
  int h = 0;
  int bh = 0;
  int qtd;
  int ide = 0;
  int idp = 0;
  printf("insira o identificador da encomenda: ");
  ide = new_sym_var(sizeof(int) * 8);
  printf("insira o identificador do produto: ");
  idp = new_sym_var(sizeof(int) * 8);
  printf("insira a quantidade de stock: ");
  qtd = new_sym_var(sizeof(int) * 8);
  int j;
  for (j = 0; j < 500; ++j)
  {
    if (vetorencomenda[i].identificador == ide)
    {
      int i = 0;
      for (int i = 0; i < 10000; ++i)
      {
        if (b.identificador == idp)
        {
          if (vetorprodutos[i].peso <= 200)
          {
            if (vetorprodutos[i].identificador == vetorencomenda[j].produto[i].idp_e)
            {
              if (vetorprodutos[i].qtd >= qtd)
              {
                vetorencomenda[j].produto[i].qtd_e += qtd;
              }
              else
              {
                
              }

            }
            else
            {
              if (vetorprodutos[i].qtd >= qtd)
              {
                vetorprodutos[i].qtd -= qtd;
                vetorencomenda[j].produto[i].qtd_e = qtd;
                vetorencomenda[j].produto[i].idp_e = b.identificador;
                vetorencomenda[j].produto[i].preco = vetorprodutos[i].preco;
              }
              else
              {
                if (vetorprodutos[i].qtd < qtd)
                {
                  printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                }
                else
                {
                  
                }

              }

            }

          }
          else
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200\n", idp, ide);
          }

        }
        else
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }

      }

    }
    else
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }

  }

}

void d_r()
{
  int idp = 0;
  int i = 0;
  int c = 0;
  int q = 0;
  printf("insira o identificador: ");
  idp = new_sym_var(sizeof(int) * 8);
  printf("insira o stock: ");
  c = new_sym_var(sizeof(int) * 8);
  while (vetorprodutos[i].identificador > 0)
  {
    if (p.identificador == idp)
    {
      if (vetorencomenda[i].produto[i].idp_e == idp)
      {
        if ((vetorprodutos[i].qtd - vetorencomenda[i].produto[i].qtd_e) >= c)
        {
          vetorprodutos[i].qtd = vetorprodutos[i].qtd - c;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }
    else
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }

    i++;
  }

}

void d_R()
{
  int ide = 0;
  int idp = 0;
  printf("insira o identificador da encomenda: ");
  ide = new_sym_var(sizeof(int) * 8);
  printf("insira o identificador do produto: ");
  idp = new_sym_var(sizeof(int) * 8);
  for (int i = 0; i < 500; ++i)
  {
    if (p.identificador == ide)
    {
      if (vetorencomenda[i].produto[i].idp_e == idp)
      {
        vetorencomenda[i].produto[i].idp_e = 0;
        vetorencomenda[i].identificador = 0;
        vetorencomenda[i].produto[i].qtd_e = 0;
      }
      else
      {
        if (((vetorencomenda[i].produto[i].idp_e == idp) != 0) && (i == 4))
        {
          printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
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

  ;
}

void d_C()
{
  int ide = 0;
  printf("insira o identificador da encomenda: ");
  ide = new_sym_var(sizeof(int) * 8);
  int total = 0;
  int qtd = 0;
  int resultado = 0;
  int total1 = 0;
  for (int i = 0; i < 500; ++i)
  {
    for (int j = 0; j < 10000; ++j)
    {
      if (ide == p.identificador)
      {
        total += vetorencomenda[i].produto[j].preco;
        qtd += vetorencomenda[i].produto[j].qtd_e;
      }
      else
      {
        
      }

    }

  }

  resultado = total * qtd;
  printf("Custo da encomenda %d %d.\n", ide, resultado);
}

void d_p()
{
  int idp = 0;
  int preco = 0;
  printf("insira o identificador do produto: ");
  idp = new_sym_var(sizeof(int) * 8);
  printf("insira o preco: ");
  preco = new_sym_var(sizeof(int) * 8);
  for (int i = 0; i < 500; ++i)
  {
    for (int j = 0; j < 10000; ++j)
    {
      if ((idp == vetorprodutos[i].identificador) && (idp == vetorencomenda[i].produto[i].idp_e))
      {
        vetorprodutos[j].preco = preco;
        vetorencomenda[i].produto[j].preco = preco;
      }
      else
      {
        
      }

    }

  }

}

void d_E()
{
  int ide = 0;
  int idp = 0;
  printf("insira o identificador da encomenda: ");
  ide = new_sym_var(sizeof(int) * 8);
  printf("insira o identificador do produto: ");
  idp = new_sym_var(sizeof(int) * 8);
  for (int i = 0; i < 500; ++i)
  {
    for (int j = 0; j < 10000; ++j)
    {
      if (ide == vetorencomenda[i].identificador)
      {
        if (idp == vetorencomenda[i].produto[i].idp_e)
        {
          printf("%s %d:", vetorprodutos[j].descricao, vetorencomenda[i].produto[i].qtd_e);
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

}

void d_m()
{
  int vetor[10000];
  for (int i = 0; i < 10000; ++i)
  {
    for (int j = 0; j < 10000; ++j)
    {
      if (vetorencomenda[i].identificador > vetorencomenda[i + 1].identificador)
      {
        vetor[i] = vetorencomenda[i].identificador;
        vetorprodutos[i].identificador = vetorprodutos[i + 1].identificador;
        vetorprodutos[i + 1].identificador = vetor[i];
      }
      else
      {
        
      }

    }

  }

  int i;
  int po = 0;
  int maior;
  maior = vetor[0];
  for (i = 0; i < 10000; i++)
  {
    if (vetor[i] > maior)
    {
      maior = vetor[i];
      po = i;
    }
    else
    {
      
    }

  }

  printf("Maximo produto%d", maior);
}

void d_l()
{
  int num;
  for (int i = 0; i < 10000; ++i)
  {
    for (int j = 0; j < 10000; ++j)
    {
      if (vetorprodutos[i].preco > vetorprodutos[i + 1].preco)
      {
        ordenado[i] = vetorprodutos[i];
        vetorprodutos[i] = vetorprodutos[i + 1];
        vetorprodutos[i + 1] = ordenado[i];
      }
      else
      {
        
      }

    }

  }

  for (int k = 0; k < 10000; ++k)
  {
    printf("%s %d %d\n", vetorprodutos[k].descricao, vetorprodutos[k].preco, vetorprodutos[k].qtd);
  }

}

void d_L()
{
}

int main()
{
  int controlador = 0;
  while (1)
  {
    char comando;
    printf("insira o comnado: ");
    comando = new_sym_var(sizeof(char) * 8);
    switch (comando)
    {
      case 'a':
        d_a();
        break;

      case 'q':
        d_q();
        break;

      case 'N':
        d_N();
        break;

      case 'A':
        d_A();
        break;

      case 'r':
        d_r();
        break;

      case 'R':
        d_R();
        break;

      case 'C':
        d_C();
        break;

      case 'p':
        d_p();
        break;

      case 'E':
        d_E();
        break;

      case 'm':
        d_m();
        break;

      case 'l':
        d_l();
        break;

      case 'L':
        d_L();
        break;

      case 'x':
        return 0;

      default:
        printf("ERRO: Comando l [%c] desconhecido\n", comando);
        break;

    }

  }

}

