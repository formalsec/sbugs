#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int identificador;
  char descricao[63];
  int preco;
  int peso;
  int qtd;
  int insideEncomenda;
} Produto;
typedef struct 
{
  Produto ENC[10000];
  int IDE;
  int Weight;
  int Price;
} Encomenda;
void a(int i, Produto Stock[10000]);
void q(Produto Stock[10000], int SIZEofSTOCK);
void N(int NrEncomendas, Encomenda ListEnc[500]);
void A(Encomenda ListEnc[500], Produto Stock[10000], int SIZEofE, int SIZEofSTOCK);
void r(Produto Stock[10000], int SIZEofV);
void R(Encomenda ListEnc[500], Produto Stock[10000], int SIZEofSTOCK, int SIZEofE);
void C(Encomenda ListENC[500], Produto Stock[10000], int SIZEofE);
void p(Encomenda ListENC[500], Produto Stock[10000], int SIZEofE, int SIZEofSTOCK);
void E(Encomenda ListENC[500], Produto Stock[10000], int SIZEofSTOCK);
void mm(Encomenda ListaENC[500], Produto Stock[10000], int SIZEofE);
void l(Produto Stock[10000], int SIZEofV);
void L(Encomenda ListENC[500], int SIZEofE);
Produto Stock[10000] = {0};
Encomenda ListaE[500] = {0};
int i = 0;
int m = 0;
int main()
{
  char c;
  while (((c = getchar()) != 'x') && (c != EOF))
  {
    switch (c)
    {
      case 'a':
        a(i, Stock);
        i += 1;
        break;

      case 'q':
        q(Stock, i);
        break;

      case 'N':
        N(m, ListaE);
        m += 1;
        break;

      case 'A':
        A(ListaE, Stock, m, i);
        break;

      case 'r':
        r(Stock, i);
        break;

      case 'R':
        R(ListaE, Stock, i, m);
        break;

      case 'C':
        C(ListaE, Stock, m);
        break;

      case 'p':
        p(ListaE, Stock, m, i);
        break;

      case 'E':
        E(ListaE, Stock, i);
        break;

      case 'm':
        mm(ListaE, Stock, m);
        break;

      case 'l':
        l(Stock, i);
        break;

      case 'L':
        L(ListaE, m);
        break;

      default:
        break;

    }

  }

  return 0;
}

void a(int i, Produto Stock[10000])
{
  Produto produto;
  for (int produto_index = 0; produto_index < 10; produto_index++)
  {
    produto.descricao[produto_index] = new_sym_var(sizeof(char) * 8);
  }

  produto.descricao[10 - 1] = '\0';
  produto.preco = new_sym_var(sizeof(int) * 8);
  produto.peso = new_sym_var(sizeof(int) * 8);
  produto.qtd = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", i);
  Stock[i].identificador = i;
  Stock[i].preco = produto.preco;
  Stock[i].peso = produto.peso;
  Stock[i].qtd = produto.qtd;
  strcpy(Stock[i].descricao, produto.descricao);
}

void q(Produto Stock[10000], int SIZEofSTOCK)
{
  int idp;
  int qtd;
  int G = 1;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if ((idp == Stock[idp].identificador) && (SIZEofSTOCK != 0))
  {
    Stock[idp].qtd += qtd;
    G = 0;
  }
  else
  {
    
  }

  if (G != 0)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

}

void N(int NrEncomendas, Encomenda ListEnc[500])
{
  printf("Nova encomenda %d.\n", NrEncomendas);
  ListEnc[NrEncomendas].IDE = NrEncomendas;
}

void A(Encomenda ListEnc[500], Produto Stock[10000], int SIZEofE, int SIZEofSTOCK)
{
  int ide;
  int idp;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if ((ide == 0) && (SIZEofE == 0))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (ListEnc[ide].IDE != ide)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else
    {
      if ((idp == 0) && (SIZEofSTOCK == 0))
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
      else
      {
        if (Stock[idp].identificador != idp)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        else
        {
          if (Stock[idp].qtd < qtd)
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
          }
          else
          {
            if ((ListEnc[ide].Weight + (Stock[idp].peso * qtd)) <= 200)
            {
              if (ListEnc[ide].ENC[idp].identificador == idp)
              {
                ListEnc[ide].Weight += Stock[idp].peso * qtd;
                ListEnc[ide].ENC[idp].qtd += qtd;
                Stock[idp].qtd -= qtd;
              }
              else
              {
                ListEnc[ide].ENC[idp] = Stock[idp];
                ListEnc[ide].ENC[idp].qtd = qtd;
                ListEnc[ide].Weight += Stock[idp].peso * qtd;
                Stock[idp].qtd -= qtd;
              }

            }
            else
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }

          }

        }

      }

    }

  }

}

void r(Produto Stock[10000], int SIZEofV)
{
  int idp;
  int quantidade;
  idp = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if ((Stock[idp].identificador == idp) && (SIZEofV != 0))
  {
    if (quantidade > Stock[idp].qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
    }
    else
    {
      Stock[idp].qtd = Stock[idp].qtd - quantidade;
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }

}

void R(Encomenda ListEnc[500], Produto Stock[10000], int SIZEofSTOCK, int SIZEofE)
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if ((ListEnc[ide].IDE == ide) && (SIZEofE != 0))
  {
    if ((Stock[idp].identificador == idp) && (SIZEofSTOCK != 0))
    {
      Stock[idp].qtd += ListEnc[ide].ENC[idp].qtd;
      ListEnc[ide].Weight -= ListEnc[ide].ENC[idp].qtd * Stock[idp].peso;
      ListEnc[ide].Price -= ListEnc[ide].ENC[idp].qtd * Stock[idp].preco;
      ListEnc[ide].ENC[idp].qtd = 0;
    }
    else
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

  }
  else
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }

}

void C(Encomenda ListEnc[500], Produto Stock[10000], int SIZEofE)
{
  int ide;
  int i;
  int STOTAL = 0;
  int j = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if ((ListEnc[ide].IDE == ide) && (SIZEofE != 0))
  {
    for (i = 0; i < 10000; i++)
    {
      j = ListEnc[ide].ENC[i].identificador;
      STOTAL += Stock[j].preco * ListEnc[ide].ENC[i].qtd;
    }

    ListEnc[ide].Price = STOTAL;
    printf("Custo da encomenda %d %d.\n", ide, STOTAL);
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }

}

void p(Encomenda ListaENC[500], Produto Stock[10000], int SIZEofE, int SIZEofSTOCK)
{
  int idp;
  int preco;
  int i;
  int j;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (Stock[idp].identificador == idp)
  {
    Stock[idp].preco = preco;
    for (j = 0; j < SIZEofE; j++)
    {
      for (i = 0; i < SIZEofSTOCK; i++)
      {
        if (ListaENC[j].ENC[i].identificador == idp)
        {
          ListaENC[j].ENC[i].preco = preco;
        }
        else
        {
          
        }

      }

    }

  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }

}

void E(Encomenda ListENC[500], Produto Stock[10000], int SIZEofSTOCK)
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ListENC[ide].IDE == ide)
  {
    if ((Stock[idp].identificador == idp) && (SIZEofSTOCK != 0))
    {
      printf("%s %d.\n", Stock[idp].descricao, ListENC[ide].ENC[idp].qtd);
    }
    else
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }

}

void mm(Encomenda ListEnc[500], Produto Stock[10000], int SIZEofE)
{
  int idp;
  int k = 0;
  int maximo = 0;
  int soma = 0;
  int G = 0;
  int ide = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (Stock[idp].identificador == idp)
  {
    for (k = 0; k < SIZEofE; k++)
    {
      if (ListEnc[k].ENC[idp].identificador == idp)
      {
        soma = ListEnc[k].ENC[idp].qtd;
        G = k;
      }
      else
      {
        
      }

      if (soma > maximo)
      {
        maximo = soma;
        ide = G;
      }
      else
      {
        
      }

    }

    if (ListEnc[ide].ENC[idp].qtd > 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, ide, maximo);
    }
    else
    {
      
    }

  }
  else
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }

}

void l(Produto Stock[10000], int SIZEofSTOCK)
{
  int i;
  int j;
  int k;
  Produto ARR[10000];
  Produto last;
  printf("Produtos\n");
  for (k = 0; k < SIZEofSTOCK; k++)
  {
    ARR[k] = Stock[k];
  }

  for (i = 1; i < SIZEofSTOCK; i++)
  {
    last = ARR[i];
    j = i - 1;
    while ((j >= 0) && (last.preco < ARR[j].preco))
    {
      ARR[j + 1] = ARR[j];
      j--;
    }

    ARR[j + 1] = last;
  }

  for (i = 0; i < SIZEofSTOCK; i++)
    printf("* %s %d %d\n", ARR[i].descricao, ARR[i].preco, ARR[i].qtd);

}

void L(Encomenda ListENC[500], int SIZEofE)
{
  int i;
  int j;
  int k;
  int ide;
  Produto ARR[10000];
  Produto last;
  ide = new_sym_var(sizeof(int) * 8);
  if ((ListENC[ide].IDE == ide) && (SIZEofE > 0))
  {
    printf("Encomenda %d\n", ide);
    for (k = 0; k < 10000; k++)
    {
      ARR[k] = ListENC[ide].ENC[k];
      strcpy(ARR[k].descricao, ListENC[ide].ENC[k].descricao);
    }

    for (i = 1; i < 10000; i++)
    {
      strcpy(last.descricao, ARR[i].descricao);
      j = i - 1;
      {
        while ((j >= 0) && (last.descricao[0] < ARR[j].descricao[0]))
        {
          ARR[j + 1] = ARR[j];
          j--;
        }

        ARR[j + 1] = last;
      }
    }

    for (i = 0; i < 10000; i++)
    {
      if ((ARR[i].identificador >= 0) && (ARR[i].qtd > 0))
      {
        printf("* %s %d %d\n", ARR[i].descricao, ARR[i].preco, ARR[i].qtd);
      }
      else
      {
        
      }

    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }

}
