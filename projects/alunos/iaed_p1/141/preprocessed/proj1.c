#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef unsigned int uint;
typedef struct Produto
{
  uint Id;
  char Descricao[63];
  uint Preco;
  uint Peso;
  uint Stock;
} Produto;
uint Cont_Prod = 0;
uint Cont_Eco = 0;
Produto Vet_Prod[10000] = {{0}, {'\0'}, {0}, {0}, {0}};
Produto Vet_Eco[500][200] = {{{0}, {'\0'}, {0}, {0}, {0}}};
Produto Copia_Prod[10000] = {{0}, {'\0'}, {0}, {0}, {0}};
Produto Vet_Ordenado[10000] = {{0}, {'\0'}, {0}, {0}, {0}};
uint Calcula_Peso(uint Id_Eco);
uint Devolve_Quant(uint Id_Eco, uint Id_Prod);
Produto Le_Prod();
void Comando_q();
void Comando_r();
void Comando_N();
void Comando_R();
void Comando_A();
void Comando_C();
void Comando_E();
void Comando_p();
void Comando_m();
void Comando_L();
void Comando_l();
void Mergesort(int esq, int dto);
void Merge(int esq, int m, int dto);
int main()
{
  int car = getchar();
  while (car != 'x')
  {
    switch (car)
    {
      case 'a':
        Vet_Prod[Cont_Prod] = Le_Prod();
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
        Comando_r();
        break;

      case 'R':
        Comando_R();
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

    }

    car = getchar();
  }

  return 0;
}

Produto Le_Prod()
{
  Produto P;
  char dois_pts;
  int i;
  int c = getchar();
  c = getchar();
  P.Id = Cont_Prod;
  for (i = 0; (i < (63 - 1)) && (c != ':'); i++)
  {
    P.Descricao[i] = c;
    c = getchar();
  }

  P.Descricao[i] = '\0';
  P.Preco = new_sym_var(sizeof(uint) * 8);
  dois_pts = new_sym_var(sizeof(char) * 8);
  P.Peso = new_sym_var(sizeof(uint) * 8);
  dois_pts = new_sym_var(sizeof(char) * 8);
  P.Stock = new_sym_var(sizeof(uint) * 8);
  printf("Novo produto %u.\n", Cont_Prod);
  Cont_Prod++;
  return P;
}

void Comando_q()
{
  uint Id;
  uint Quant;
  char dois_pts;
  Id = new_sym_var(sizeof(uint) * 8);
  dois_pts = new_sym_var(sizeof(char) * 8);
  Quant = new_sym_var(sizeof(uint) * 8);
  if (Id >= Cont_Prod)
  {
    printf("Impossivel adicionar produto %u ao stock. Produto inexistente.\n", Id);
  }
  else
  {
    Vet_Prod[Id].Stock += Quant;
  }

}

void Comando_N()
{
  printf("Nova encomenda %u.\n", Cont_Eco);
  ++Cont_Eco;
}

void Comando_r()
{
  uint Id_Prod;
  uint Quant;
  char dois_pts;
  Id_Prod = new_sym_var(sizeof(uint) * 8);
  dois_pts = new_sym_var(sizeof(char) * 8);
  Quant = new_sym_var(sizeof(uint) * 8);
  if (Id_Prod >= Cont_Prod)
  {
    printf("Impossivel remover stock do produto %u. Produto inexistente.\n", Id_Prod);
  }
  else
  {
    if (Vet_Prod[Id_Prod].Stock < Quant)
    {
      printf("Impossivel remover %u unidades do produto %u do stock. Quantidade insuficiente.\n", Quant, Id_Prod);
    }
    else
    {
      Vet_Prod[Id_Prod].Stock -= Quant;
    }

  }

}

void Comando_R()
{
  uint Id_Eco;
  uint Id_Prod;
  char dois_pts;
  Id_Eco = new_sym_var(sizeof(uint) * 8);
  dois_pts = new_sym_var(sizeof(char) * 8);
  Id_Prod = new_sym_var(sizeof(uint) * 8);
  if (Id_Eco >= Cont_Eco)
  {
    printf("Impossivel remover produto %u a encomenda %u. Encomenda inexistente.\n", Id_Prod, Id_Eco);
  }
  else
  {
    if (Id_Prod >= Cont_Prod)
    {
      printf("Impossivel remover produto %u a encomenda %u. Produto inexistente.\n", Id_Prod, Id_Eco);
    }
    else
    {
      uint i;
      for (i = 0; (i < 200) && Vet_Eco[Id_Eco][i].Preco; i++)
      {
        if (Vet_Eco[Id_Eco][i].Id == Id_Prod)
        {
          Vet_Prod[Id_Prod].Stock += Vet_Eco[Id_Eco][i].Stock;
          Vet_Eco[Id_Eco][i].Stock = 0;
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void Comando_A()
{
  uint Id_Eco;
  uint Id_Prod;
  uint Quant;
  char dois_pts;
  Id_Eco = new_sym_var(sizeof(uint) * 8);
  dois_pts = new_sym_var(sizeof(char) * 8);
  Id_Prod = new_sym_var(sizeof(uint) * 8);
  dois_pts = new_sym_var(sizeof(char) * 8);
  Quant = new_sym_var(sizeof(uint) * 8);
  if (Id_Eco >= Cont_Eco)
  {
    printf("Impossivel adicionar produto %u a encomenda %u. Encomenda inexistente.\n", Id_Prod, Id_Eco);
  }
  else
  {
    if (Id_Prod >= Cont_Prod)
    {
      printf("Impossivel adicionar produto %u a encomenda %u. Produto inexistente.\n", Id_Prod, Id_Eco);
    }
    else
    {
      if (Vet_Prod[Id_Prod].Stock < Quant)
      {
        printf("Impossivel adicionar produto %u a encomenda %u. Quantidade em stock insuficiente.\n", Id_Prod, Id_Eco);
      }
      else
      {
        if ((Calcula_Peso(Id_Eco) + (Vet_Prod[Id_Prod].Peso * Quant)) > 200)
        {
          printf("Impossivel adicionar produto %u a encomenda %u. Peso da encomenda excede o maximo de 200.\n", Id_Prod, Id_Eco);
        }
        else
        {
          uint i;
          for (i = 0; i < 200; i++)
          {
            if (!Vet_Eco[Id_Eco][i].Preco)
            {
              Vet_Eco[Id_Eco][i] = Vet_Prod[Id_Prod];
              Vet_Eco[Id_Eco][i].Stock = Quant;
              break;
            }
            else
            {
              if (Vet_Eco[Id_Eco][i].Id == Id_Prod)
              {
                Vet_Eco[Id_Eco][i].Stock += Quant;
                break;
              }
              else
              {
                
              }

            }

          }

          Vet_Prod[Id_Prod].Stock -= Quant;
        }

      }

    }

  }

}

void Comando_C()
{
  uint Id_Eco;
  Id_Eco = new_sym_var(sizeof(uint) * 8);
  if (Id_Eco >= Cont_Eco)
  {
    printf("Impossivel calcular custo da encomenda %u. Encomenda inexistente.\n", Id_Eco);
  }
  else
  {
    uint i;
    uint Custo = 0;
    for (i = 0; (i < 200) && Vet_Eco[Id_Eco][i].Preco; i++)
      Custo += Vet_Eco[Id_Eco][i].Preco * Vet_Eco[Id_Eco][i].Stock;

    printf("Custo da encomenda %u %u.\n", Id_Eco, Custo);
  }

}

void Comando_E()
{
  uint Id_Eco;
  uint Id_Prod;
  char dois_pontos;
  Id_Eco = new_sym_var(sizeof(uint) * 8);
  dois_pontos = new_sym_var(sizeof(char) * 8);
  Id_Prod = new_sym_var(sizeof(uint) * 8);
  if (Id_Eco >= Cont_Eco)
  {
    printf("Impossivel listar encomenda %u. Encomenda inexistente.\n", Id_Eco);
  }
  else
  {
    if (Id_Prod >= Cont_Prod)
    {
      printf("Impossivel listar produto %u. Produto inexistente.\n", Id_Prod);
    }
    else
    {
      printf("%s %u.\n", Vet_Prod[Id_Prod].Descricao, Devolve_Quant(Id_Eco, Id_Prod));
    }

  }

}

void Comando_p()
{
  uint Id_Prod;
  uint Preco;
  char dois_pontos;
  Id_Prod = new_sym_var(sizeof(uint) * 8);
  dois_pontos = new_sym_var(sizeof(char) * 8);
  Preco = new_sym_var(sizeof(uint) * 8);
  if (Id_Prod >= Cont_Prod)
  {
    printf("Impossivel alterar preco do produto %u. Produto inexistente.\n", Id_Prod);
  }
  else
  {
    uint i;
    uint j;
    Vet_Prod[Id_Prod].Preco = Preco;
    for (i = 0; i < Cont_Eco; i++)
    {
      for (j = 0; (j < 200) && Vet_Eco[i][j].Preco; j++)
      {
        if (Vet_Eco[i][j].Id == Id_Prod)
        {
          Vet_Eco[i][j].Preco = Preco;
          break;
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
  uint Id_Prod;
  Id_Prod = new_sym_var(sizeof(uint) * 8);
  if (Id_Prod >= Cont_Prod)
  {
    printf("Impossivel listar maximo do produto %u. Produto inexistente.\n", Id_Prod);
  }
  else
  {
    uint i;
    uint Maior_Id = 0;
    for (i = 0; i < Cont_Eco; i++)
    {
      if (Devolve_Quant(i, Id_Prod) > Devolve_Quant(Maior_Id, Id_Prod))
      {
        Maior_Id = i;
      }
      else
      {
        
      }

    }

    if (Devolve_Quant(Maior_Id, Id_Prod))
    {
      printf("Maximo produto %u %u %u.\n", Id_Prod, Maior_Id, Devolve_Quant(Maior_Id, Id_Prod));
    }
    else
    {
      
    }

  }

}

void Comando_L()
{
  uint Id_Eco;
  Produto Copia_Eco[200];
  Id_Eco = new_sym_var(sizeof(uint) * 8);
  if (Id_Eco >= Cont_Eco)
  {
    printf("Impossivel listar encomenda %u. Encomenda inexistente.\n", Id_Eco);
  }
  else
  {
    int i;
    int j;
    int k;
    int lim = -1;
    printf("Encomenda %u\n", Id_Eco);
    for (i = 0, k = 0; (i < 200) && Vet_Eco[Id_Eco][i].Preco; i++, k++)
    {
      if (!Vet_Eco[Id_Eco][i].Stock)
      {
        k--;
      }
      else
      {
        Copia_Eco[k] = Vet_Eco[Id_Eco][i];
        lim++;
      }

    }

    for (i = 1; i <= lim; i++)
    {
      Produto P = Copia_Eco[i];
      for (j = i - 1; (j >= 0) && (strcmp(P.Descricao, Copia_Eco[j].Descricao) < 0); j--)
        Copia_Eco[j + 1] = Copia_Eco[j];

      Copia_Eco[j + 1] = P;
    }

    for (i = 0; i <= lim; i++)
      printf("* %s %u %u\n", Copia_Eco[i].Descricao, Copia_Eco[i].Preco, Copia_Eco[i].Stock);

  }

}

void Mergesort(int esq, int dto)
{
  int m = (dto + esq) / 2;
  if (dto <= esq)
  {
    return;
  }
  else
  {
    
  }

  Mergesort(esq, m);
  Mergesort(m + 1, dto);
  Merge(esq, m, dto);
}

void Merge(int esq, int m, int dto)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > esq; i--)
    Copia_Prod[i - 1] = Vet_Ordenado[i - 1];

  for (j = m; j < dto; j++)
    Copia_Prod[(dto + m) - j] = Vet_Ordenado[j + 1];

  for (k = esq; k <= dto; k++)
    if ((Copia_Prod[j].Preco < Copia_Prod[i].Preco) || ((Copia_Prod[j].Preco == Copia_Prod[i].Preco) && (Copia_Prod[j].Id < Copia_Prod[i].Id)))
  {
    Vet_Ordenado[k] = Copia_Prod[j--];
  }
  else
  {
    Vet_Ordenado[k] = Copia_Prod[i++];
  }


}

void Comando_l()
{
  if (!Cont_Prod)
  {
    printf("Produtos\n");
  }
  else
  {
    uint i;
    for (i = 0; i <= (Cont_Prod - 1); i++)
      Vet_Ordenado[i] = Vet_Prod[i];

    Mergesort(0, Cont_Prod - 1);
    printf("Produtos\n");
    for (i = 0; i <= (Cont_Prod - 1); i++)
      printf("* %s %u %u\n", Vet_Ordenado[i].Descricao, Vet_Ordenado[i].Preco, Vet_Ordenado[i].Stock);

  }

}

uint Devolve_Quant(uint Id_Eco, uint Id_Prod)
{
  uint i;
  uint Quant = 0;
  for (i = 0; (i < 200) && Vet_Eco[Id_Eco][i].Preco; i++)
  {
    if (Vet_Eco[Id_Eco][i].Id == Id_Prod)
    {
      Quant = Vet_Eco[Id_Eco][i].Stock;
      break;
    }
    else
    {
      
    }

  }

  return Quant;
}

uint Calcula_Peso(uint Id_Eco)
{
  uint i;
  uint Peso = 0;
  for (i = 0; (i < 200) && Vet_Eco[Id_Eco][i].Preco; i++)
    Peso += Vet_Eco[Id_Eco][i].Peso * Vet_Eco[Id_Eco][i].Stock;

  return Peso;
}

