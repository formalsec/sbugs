/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct Produto
{
  int Idp;
  char Descricao[63];
  int Preco;
  int Peso;
  int Stock;
} produto;
typedef struct Encomenda
{
  int Ide;
  produto Lista_Produtos[200];
  int Contador;
} encomenda;
int IdentProduto = -1;
int IdentEncom = -1;
produto VetorProdutos[10000];
encomenda VetorEncomendas[500];
char LeCaracterInicial()
{
  char CaracterInicial;
  CaracterInicial = new_sym_var(sizeof(char) * 8);
  return CaracterInicial;
}

void Aux_q_r(int idp, int qtd, char operacao)
{
  int i;
  produto Produto_Aux;
  for (i = 0; i <= IdentProduto; i++)
  {
    Produto_Aux = VetorProdutos[i];
    if (Produto_Aux.Idp == idp)
    {
      {
        if (operacao == 'q')
        {
          {
            Produto_Aux.Stock = Produto_Aux.Stock + qtd;
            VetorProdutos[idp] = Produto_Aux;
          }
        }
        else
        {
          if (operacao == 'r')
          {
            {
              Produto_Aux.Stock = Produto_Aux.Stock - qtd;
              VetorProdutos[idp] = Produto_Aux;
            }
          }
          else
          {
            
          }

        }

        break;
      }
    }
    else
    {
      
    }

  }

}

int Calcula_Peso(int ide)
{
  int i;
  int Peso = 0;
  encomenda Encomenda_aux = VetorEncomendas[ide];
  for (i = 0; i <= Encomenda_aux.Contador; i++)
  {
    Peso = Peso + (Encomenda_aux.Lista_Produtos[i].Peso * Encomenda_aux.Lista_Produtos[i].Stock);
  }

  return Peso;
}

void Comando_a()
{
  produto NovoProduto;
  IdentProduto++;
  for (int NovoProduto_index = 0; NovoProduto_index < 10; NovoProduto_index++)
  {
    NovoProduto.Descricao[NovoProduto_index] = new_sym_var(sizeof(char) * 8);
  }

  NovoProduto.Descricao[10 - 1] = '\0';
  NovoProduto.Preco = new_sym_var(sizeof(int) * 8);
  NovoProduto.Peso = new_sym_var(sizeof(int) * 8);
  NovoProduto.Stock = new_sym_var(sizeof(int) * 8);
  NovoProduto.Idp = IdentProduto;
  VetorProdutos[IdentProduto] = NovoProduto;
  printf("Novo produto %d.\n", IdentProduto);
}

void Comando_q()
{
  int idp_q;
  int qtd_q;
  idp_q = new_sym_var(sizeof(int) * 8);
  qtd_q = new_sym_var(sizeof(int) * 8);
  if (idp_q > IdentProduto)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_q);
    }
  }
  else
  {
    {
      Aux_q_r(idp_q, qtd_q, 'q');
    }
  }

}

void Comando_N()
{
  int i;
  encomenda NovaEncomenda;
  IdentEncom++;
  for (i = 0; i < 200; i++)
  {
    NovaEncomenda.Lista_Produtos[i].Stock = 0;
  }

  NovaEncomenda.Ide = IdentEncom;
  NovaEncomenda.Contador = -1;
  ;
  VetorEncomendas[IdentEncom] = NovaEncomenda;
  printf("Nova encomenda %d.\n", IdentEncom);
}

void Comando_A()
{
  int ide_A;
  int idp_A;
  int qtd_A;
  int i;
  int dentro = 0;
  encomenda Encomenda_A;
  produto Produto_A;
  ide_A = new_sym_var(sizeof(int) * 8);
  idp_A = new_sym_var(sizeof(int) * 8);
  qtd_A = new_sym_var(sizeof(int) * 8);
  Produto_A = VetorProdutos[idp_A];
  Encomenda_A = VetorEncomendas[ide_A];
  if (ide_A > IdentEncom)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_A, ide_A);
    }
  }
  else
  {
    if (idp_A > IdentProduto)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_A, ide_A);
      }
    }
    else
    {
      if (VetorProdutos[idp_A].Stock < qtd_A)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_A, ide_A);
        }
      }
      else
      {
        if ((Calcula_Peso(ide_A) + (qtd_A * VetorProdutos[idp_A].Peso)) > 200)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_A, ide_A);
          }
        }
        else
        {
          {
            for (i = 0; i <= Encomenda_A.Contador; i++)
            {
              if (Encomenda_A.Lista_Produtos[i].Idp == idp_A)
              {
                {
                  Encomenda_A.Lista_Produtos[i].Stock = Encomenda_A.Lista_Produtos[i].Stock + qtd_A;
                  dentro = 1;
                  break;
                }
              }
              else
              {
                
              }

            }

            if (dentro != 1)
            {
              {
                Encomenda_A.Contador++;
                Encomenda_A.Lista_Produtos[Encomenda_A.Contador] = Produto_A;
                Encomenda_A.Lista_Produtos[Encomenda_A.Contador].Stock = qtd_A;
              }
            }
            else
            {
              
            }

            Produto_A.Stock = Produto_A.Stock - qtd_A;
            VetorEncomendas[ide_A] = Encomenda_A;
            VetorProdutos[idp_A] = Produto_A;
          }
        }

      }

    }

  }

}

void comando_r()
{
  int idp_r;
  int qtd_r;
  idp_r = new_sym_var(sizeof(int) * 8);
  qtd_r = new_sym_var(sizeof(int) * 8);
  if (idp_r > IdentProduto)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_r);
    }
  }
  else
  {
    if ((VetorProdutos[idp_r].Stock - qtd_r) < 0)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_r, idp_r);
      }
    }
    else
    {
      {
        Aux_q_r(idp_r, qtd_r, 'r');
      }
    }

  }

}

void comando_R()
{
  int ide_R;
  int idp_R;
  int i;
  encomenda Encomenda_R;
  produto Produto_R;
  ide_R = new_sym_var(sizeof(int) * 8);
  idp_R = new_sym_var(sizeof(int) * 8);
  Encomenda_R = VetorEncomendas[ide_R];
  Produto_R = VetorProdutos[idp_R];
  if (ide_R > IdentEncom)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_R, ide_R);
    }
  }
  else
  {
    if (idp_R > IdentProduto)
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_R, ide_R);
      }
    }
    else
    {
      {
        for (i = 0; i <= Encomenda_R.Contador; i++)
        {
          if (Encomenda_R.Lista_Produtos[i].Idp == idp_R)
          {
            {
              Produto_R.Stock = Produto_R.Stock + Encomenda_R.Lista_Produtos[i].Stock;
              Encomenda_R.Lista_Produtos[i].Stock = 0;
              break;
            }
          }
          else
          {
            
          }

        }

        VetorEncomendas[ide_R] = Encomenda_R;
        VetorProdutos[idp_R] = Produto_R;
      }
    }

  }

}

void Comando_C()
{
  int ide_C;
  int i;
  int PrecoEncomenda = 0;
  encomenda Encomenda_C;
  produto Produto_C;
  ide_C = new_sym_var(sizeof(int) * 8);
  Encomenda_C = VetorEncomendas[ide_C];
  if (ide_C > IdentEncom)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_C);
    }
  }
  else
  {
    {
      for (i = 0; i <= Encomenda_C.Contador; i++)
      {
        Produto_C = Encomenda_C.Lista_Produtos[i];
        PrecoEncomenda = PrecoEncomenda + (Produto_C.Stock * Produto_C.Preco);
      }

      printf("Custo da encomenda %d %d.\n", ide_C, PrecoEncomenda);
    }
  }

}

void Comando_p()
{
  int idp_p;
  int preco_p;
  int i;
  int k;
  encomenda Encomenda_p;
  produto Produto_p;
  idp_p = new_sym_var(sizeof(int) * 8);
  preco_p = new_sym_var(sizeof(int) * 8);
  Produto_p = VetorProdutos[idp_p];
  if (idp_p > IdentProduto)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_p);
    }
  }
  else
  {
    {
      Produto_p.Preco = preco_p;
      VetorProdutos[idp_p] = Produto_p;
      for (i = 0; i <= IdentEncom; i++)
      {
        Encomenda_p = VetorEncomendas[i];
        for (k = 0; k <= Encomenda_p.Contador; k++)
        {
          if (Encomenda_p.Lista_Produtos[k].Idp == idp_p)
          {
            {
              Encomenda_p.Lista_Produtos[k].Preco = preco_p;
            }
          }
          else
          {
            
          }

        }

        VetorEncomendas[i] = Encomenda_p;
      }

    }
  }

}

void Comando_E()
{
  int ide_E;
  int idp_E;
  int i;
  int dentro = 0;
  encomenda Encomenda_E;
  produto Produto_E;
  ide_E = new_sym_var(sizeof(int) * 8);
  idp_E = new_sym_var(sizeof(int) * 8);
  Encomenda_E = VetorEncomendas[ide_E];
  Produto_E = VetorProdutos[idp_E];
  if (ide_E > IdentEncom)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_E);
    }
  }
  else
  {
    if (idp_E > IdentProduto)
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp_E);
      }
    }
    else
    {
      {
        for (i = 0; i <= Encomenda_E.Contador; i++)
        {
          if (Encomenda_E.Lista_Produtos[i].Idp == idp_E)
          {
            {
              printf("%s %d.\n", Encomenda_E.Lista_Produtos[i].Descricao, Encomenda_E.Lista_Produtos[i].Stock);
              dentro = 1;
              break;
            }
          }
          else
          {
            
          }

        }

        if (dentro == 0)
        {
          {
            printf("%s %d.\n", Produto_E.Descricao, 0);
          }
        }
        else
        {
          
        }

      }
    }

  }

}

void Comando_m()
{
  int idp_m;
  int i;
  int k;
  int Stock_max = 0;
  int dentro = 0;
  encomenda Encomenda_m;
  encomenda Encomenda_max;
  produto Produto_m;
  idp_m = new_sym_var(sizeof(int) * 8);
  if (idp_m > IdentProduto)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_m);
    }
  }
  else
  {
    {
      for (i = 0; i <= IdentEncom; i++)
      {
        Encomenda_m = VetorEncomendas[i];
        for (k = 0; k <= Encomenda_m.Contador; k++)
        {
          Produto_m = Encomenda_m.Lista_Produtos[k];
          if ((Produto_m.Idp == idp_m) && (Produto_m.Stock > 0))
          {
            {
              dentro = 1;
              if (Produto_m.Stock > Stock_max)
              {
                {
                  Stock_max = Produto_m.Stock;
                  Encomenda_max = Encomenda_m;
                }
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

    }
  }

  if ((IdentEncom >= 0) && (dentro == 1))
  {
    {
      printf("Maximo produto %d %d %d.\n", idp_m, Encomenda_max.Ide, Stock_max);
    }
  }
  else
  {
    
  }

}

void Comando_l()
{
  int l;
  int i;
  int j;
  int k;
  produto Vetor_Copia[10000];
  for (l = 0; l <= IdentProduto; l++)
  {
    Vetor_Copia[l] = VetorProdutos[l];
  }

  printf("Produtos\n");
  for (i = 0; i < IdentProduto; i++)
  {
    produto aux;
    int min = i;
    for (j = i + 1; j <= IdentProduto; j++)
    {
      if (Vetor_Copia[j].Preco < Vetor_Copia[min].Preco)
      {
        {
          min = j;
        }
      }
      else
      {
        
      }

    }

    aux = Vetor_Copia[i];
    Vetor_Copia[i] = Vetor_Copia[min];
    Vetor_Copia[min] = aux;
  }

  for (k = 0; k <= IdentProduto; k++)
  {
    printf("* %s %d %d\n", Vetor_Copia[k].Descricao, Vetor_Copia[k].Preco, Vetor_Copia[k].Stock);
  }

}

void Comando_L()
{
  int ide_L;
  int i;
  int j;
  int k;
  int l;
  produto Produtos_ide[200];
  produto Produto_L;
  ide_L = new_sym_var(sizeof(int) * 8);
  if (ide_L > IdentEncom)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_L);
    }
  }
  else
  {
    {
      for (i = 0; i <= VetorEncomendas[ide_L].Contador; i++)
      {
        Produtos_ide[i] = VetorEncomendas[ide_L].Lista_Produtos[i];
      }

      printf("Encomenda %d\n", ide_L);
      for (j = 0; j < VetorEncomendas[ide_L].Contador; j++)
      {
        produto aux;
        int min = j;
        for (k = j + 1; k <= VetorEncomendas[ide_L].Contador; k++)
        {
          if (strcmp(Produtos_ide[k].Descricao, Produtos_ide[min].Descricao) < 0)
          {
            {
              min = k;
            }
          }
          else
          {
            
          }

        }

        aux = Produtos_ide[j];
        Produtos_ide[j] = Produtos_ide[min];
        Produtos_ide[min] = aux;
      }

      for (l = 0; l <= VetorEncomendas[ide_L].Contador; l++)
      {
        if (Produtos_ide[l].Stock > 0)
        {
          {
            Produto_L = Produtos_ide[l];
            printf("* %s %d %d\n", Produto_L.Descricao, Produto_L.Preco, Produto_L.Stock);
          }
        }
        else
        {
          
        }

      }

    }
  }

}

int main()
{
  char Comando = LeCaracterInicial();
  while (Comando != 'x')
  {
    switch (Comando)
    {
      case 'a':
        Comando_a();
        break;

      case 'q':
        Comando_q();
        break;

      case 'N':
        Comando_N();
        break;

      case 'A':
        Comando_A();
        break;

      case 'r':
        comando_r();
        break;

      case 'R':
        comando_R();
        break;

      case 'C':
        Comando_C();
        break;

      case 'p':
        Comando_p();
        break;

      case 'E':
        Comando_E();
        break;

      case 'm':
        Comando_m();
        break;

      case 'l':
        Comando_l();
        break;

      case 'L':
        Comando_L();
        break;

      default:
        break;

    }

    Comando = LeCaracterInicial();
  }

  return 0;
}
