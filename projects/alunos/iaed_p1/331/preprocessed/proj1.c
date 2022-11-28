#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  char descricao[64];
  int idP;
  int preco;
  int peso;
  int quantidade;
} Produto;
typedef struct encomenda
{
  Produto ProdutosEnc[10000];
  int lista_idsProd_Enc[10000];
  int contador;
  int pesoEnc;
  int precoEnc;
} Encomenda;
Encomenda lista_Enc[500];
void a(int ContadorProd, Produto armazem[10000])
{
  int i = 0;
  char lixo;
  char c;
  char vartab[64];
  c = getchar();
  while ((c = getchar()) != ':')
  {
    vartab[i++] = c;
  }

  vartab[i] = '\0';
  for (i = 0; i < 64; i++)
  {
    armazem[ContadorProd].descricao[i] = vartab[i];
  }

  armazem[ContadorProd].preco = new_sym_var(sizeof(int) * 8);
  lixo = new_sym_var(sizeof(char) * 8);
  armazem[ContadorProd].peso = new_sym_var(sizeof(int) * 8);
  lixo = new_sym_var(sizeof(char) * 8);
  armazem[ContadorProd].quantidade = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", ContadorProd);
}

void q(int ContadorProd, Produto armazem[10000])
{
  char lixo;
  int id;
  int qtd;
  lixo = new_sym_var(sizeof(char) * 8);
  id = new_sym_var(sizeof(int) * 8);
  lixo = new_sym_var(sizeof(char) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id < ContadorProd)
  {
    armazem[id].quantidade += qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
  }

}

void r(int ContadorProd, Produto armazem[10000])
{
  char lixo;
  int id;
  int qtd;
  lixo = new_sym_var(sizeof(char) * 8);
  id = new_sym_var(sizeof(int) * 8);
  lixo = new_sym_var(sizeof(char) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id < ContadorProd)
  {
    if ((armazem[id].quantidade - qtd) >= 0)
    {
      armazem[id].quantidade -= qtd;
    }
    else
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
  }

}

void p(int ContadorProd, int ContadorEnc, Produto armazem[10000], Encomenda lista_Enc[500])
{
  char lixo;
  int id;
  int price;
  int e;
  lixo = new_sym_var(sizeof(char) * 8);
  id = new_sym_var(sizeof(int) * 8);
  lixo = new_sym_var(sizeof(char) * 8);
  price = new_sym_var(sizeof(int) * 8);
  if (id < ContadorProd)
  {
    for (e = 0; e < ContadorEnc; e++)
    {
      if (lista_Enc[e].lista_idsProd_Enc[id] == id)
      {
        lista_Enc[e].precoEnc -= armazem[id].preco * lista_Enc[e].ProdutosEnc[id].quantidade;
        armazem[id].preco = price;
        lista_Enc[e].precoEnc += armazem[id].preco * lista_Enc[e].ProdutosEnc[id].quantidade;
      }
      else
      {
        
      }

    }

    armazem[id].preco = price;
  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
  }

}

void N(int ContadorEnc)
{
  printf("Nova encomenda %d.\n", ContadorEnc);
}

void A(int ContadorEnc, int ContadorProd, Encomenda lista_Enc[500], Produto armazem[10000])
{
  int IdEnc;
  int IdProd;
  int qtd;
  int VarEstado = 5;
  int e;
  char lixo;
  lixo = new_sym_var(sizeof(char) * 8);
  IdEnc = new_sym_var(sizeof(int) * 8);
  lixo = new_sym_var(sizeof(char) * 8);
  IdProd = new_sym_var(sizeof(int) * 8);
  lixo = new_sym_var(sizeof(char) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (IdEnc > (ContadorEnc - 1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", IdProd, IdEnc);
  }
  else
  {
    if (IdProd > (ContadorProd - 1))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", IdProd, IdEnc);
    }
    else
    {
      if ((armazem[IdProd].quantidade - qtd) < 0)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", IdProd, IdEnc);
      }
      else
      {
        if (((armazem[IdProd].peso * qtd) + lista_Enc[IdEnc].pesoEnc) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", IdProd, IdEnc);
        }
        else
        {
          for (e = 0; e < lista_Enc[IdEnc].contador; e++)
          {
            if (lista_Enc[IdEnc].ProdutosEnc[e].descricao == armazem[IdProd].descricao)
            {
              VarEstado = 1;
            }
            else
            {
              
            }

          }

          if (VarEstado == 1)
          {
            lista_Enc[IdEnc].precoEnc += armazem[IdProd].preco * qtd;
            lista_Enc[IdEnc].pesoEnc += armazem[IdProd].peso * qtd;
            lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade += qtd;
            armazem[IdProd].quantidade -= qtd;
          }
          else
          {
            lista_Enc[IdEnc].precoEnc += armazem[IdProd].preco * qtd;
            lista_Enc[IdEnc].pesoEnc += armazem[IdProd].peso * qtd;
            strcpy(lista_Enc[IdEnc].ProdutosEnc[IdProd].descricao, armazem[IdProd].descricao);
            lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade += qtd;
            armazem[IdProd].quantidade -= qtd;
            lista_Enc[IdEnc].contador += 1;
            lista_Enc[IdEnc].lista_idsProd_Enc[IdProd] = IdProd;
          }

        }

      }

    }

  }

}

void C(int ContadorEnc, Encomenda lista_Enc[500])
{
  int IdEnc;
  IdEnc = new_sym_var(sizeof(int) * 8);
  if (IdEnc > (ContadorEnc - 1))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", IdEnc);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", IdEnc, lista_Enc[IdEnc].precoEnc);
  }

}

void R(int ContadorProd, int ContadorEnc, Encomenda lista_Enc[500], Produto armazem[10000])
{
  int IdEnc;
  int IdProd;
  char lixo;
  lixo = new_sym_var(sizeof(char) * 8);
  IdEnc = new_sym_var(sizeof(int) * 8);
  lixo = new_sym_var(sizeof(char) * 8);
  IdProd = new_sym_var(sizeof(int) * 8);
  if (IdEnc > (ContadorEnc - 1))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", IdProd, IdEnc);
  }
  else
  {
    if (IdProd > (ContadorProd - 1))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", IdProd, IdEnc);
    }
    else
    {
      armazem[IdProd].quantidade += lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade;
      lista_Enc[IdEnc].pesoEnc -= armazem[IdProd].peso * lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade;
      lista_Enc[IdEnc].precoEnc -= armazem[IdProd].preco * lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade;
      lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade = 0;
    }

  }

}

void E(int ContadorEnc, int ContadorProd, Encomenda lista_Enc[500], Produto armazem[10000])
{
  int IdEnc;
  int IdProd;
  char lixo;
  lixo = new_sym_var(sizeof(char) * 8);
  IdEnc = new_sym_var(sizeof(int) * 8);
  lixo = new_sym_var(sizeof(char) * 8);
  IdProd = new_sym_var(sizeof(int) * 8);
  if (IdEnc > (ContadorEnc - 1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", IdEnc);
  }
  else
  {
    if (IdProd > (ContadorProd - 1))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", IdProd);
    }
    else
    {
      if (lista_Enc[IdEnc].lista_idsProd_Enc[IdProd] == IdProd)
      {
        strcpy(lista_Enc[IdEnc].ProdutosEnc[IdProd].descricao, armazem[IdProd].descricao);
        printf("%s", lista_Enc[IdEnc].ProdutosEnc[IdProd].descricao);
        printf(" %d.\n", lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade);
      }
      else
      {
        printf("%s", armazem[IdProd].descricao);
        printf(" 0.\n");
      }

    }

  }

}

void m(int ContadorEnc, int ContadorProd, Encomenda lista_Enc[500])
{
  int IdProd;
  int e;
  int maiorQTD = 0;
  int EncAlvo = 0;
  char lixo;
  lixo = new_sym_var(sizeof(char) * 8);
  IdProd = new_sym_var(sizeof(int) * 8);
  if ((ContadorEnc == 0) || (IdProd > (ContadorProd - 1)))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", IdProd);
  }
  else
  {
    for (e = 0; e < ContadorEnc; e++)
    {
      if (lista_Enc[e].ProdutosEnc[IdProd].quantidade > maiorQTD)
      {
        maiorQTD = lista_Enc[e].ProdutosEnc[IdProd].quantidade;
        EncAlvo = e;
      }
      else
      {
        
      }

    }

    if (maiorQTD <= 0)
    {
      return;
    }
    else
    {
      
    }

    printf("Maximo produto %d %d %d.\n", IdProd, EncAlvo, maiorQTD);
  }

}

void merge(Produto arr[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  Produto L[10000];
  Produto R[10000];
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];

  for (j = 0; j < n2; j++)
    R[j] = arr[(m + 1) + j];

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (L[i].preco <= R[j].preco)
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }

    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }

}

void mergeSort(Produto arr[], int l, int r)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
  else
  {
    
  }

}

void l(int ContadorProd, Produto armazem[10000])
{
  Produto lista_Preco_Id[10000];
  int e;
  for (e = 0; e < ContadorProd; e++)
  {
    lista_Preco_Id[e].preco = armazem[e].preco;
    lista_Preco_Id[e].idP = e;
  }

  mergeSort(lista_Preco_Id, 0, ContadorProd - 1);
  printf("Produtos\n");
  for (e = 0; e < ContadorProd; e++)
  {
    printf("* %s %d %d\n", armazem[lista_Preco_Id[e].idP].descricao, armazem[lista_Preco_Id[e].idP].preco, armazem[lista_Preco_Id[e].idP].quantidade);
  }

}

void L(int ContadorEnc, int ContadorProd, Produto armazem[10000])
{
  int IdEnc;
  int i;
  int j;
  int e;
  char lixo;
  char aux[10000][64];
  char temp[64];
  lixo = new_sym_var(sizeof(char) * 8);
  IdEnc = new_sym_var(sizeof(int) * 8);
  if (IdEnc > (ContadorEnc - 1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.", IdEnc);
  }
  else
  {
    for (e = 0; e < (lista_Enc[IdEnc].contador - 1); e++)
    {
      strcpy(aux[e], lista_Enc[IdEnc].ProdutosEnc[e].descricao);
    }

    for (i = 0; i < (lista_Enc[IdEnc].contador - 1); i++)
    {
      for (j = i + 1; j <= lista_Enc[IdEnc].contador; j++)
      {
        if (strcmp(aux[i], aux[j]) > 0)
        {
          strcpy(temp, aux[i]);
          strcpy(aux[i], aux[j]);
          strcpy(aux[j], temp);
        }
        else
        {
          
        }

      }

    }

    printf("Produtos\n");
    for (e = 0; e <= lista_Enc[IdEnc].contador; e++)
    {
      for (i = 0; i < ContadorProd; i++)
      {
        if (strcmp(lista_Enc[IdEnc].ProdutosEnc[e].descricao, armazem[i].descricao) == 0)
        {
          printf("* %s %d %d\n", aux[e], armazem[i].preco, armazem[i].quantidade);
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
  int ContadorProd = 0;
  int ContadorEnc = 0;
  int c;
  Produto armazem[10000];
  while ((c = getchar()) != 'x')
  {
    if (c == 'a')
    {
      a(ContadorProd, armazem);
      ContadorProd++;
      continue;
    }
    else
    {
      
    }

    if (c == 'q')
    {
      q(ContadorProd, armazem);
      continue;
    }
    else
    {
      
    }

    if (c == 'N')
    {
      N(ContadorEnc);
      ContadorEnc++;
      continue;
    }
    else
    {
      
    }

    if (c == 'A')
    {
      A(ContadorEnc, ContadorProd, lista_Enc, armazem);
      continue;
    }
    else
    {
      
    }

    if (c == 'r')
    {
      r(ContadorProd, armazem);
      continue;
    }
    else
    {
      
    }

    if (c == 'R')
    {
      R(ContadorProd, ContadorEnc, lista_Enc, armazem);
      continue;
    }
    else
    {
      
    }

    if (c == 'C')
    {
      C(ContadorEnc, lista_Enc);
      continue;
    }
    else
    {
      
    }

    if (c == 'p')
    {
      p(ContadorProd, ContadorEnc, armazem, lista_Enc);
      continue;
    }
    else
    {
      
    }

    if (c == 'E')
    {
      E(ContadorEnc, ContadorProd, lista_Enc, armazem);
      continue;
    }
    else
    {
      
    }

    if (c == 'm')
    {
      m(ContadorEnc, ContadorProd, lista_Enc);
      continue;
    }
    else
    {
      
    }

    if (c == 'l')
    {
      l(ContadorProd, armazem);
      continue;
    }
    else
    {
      
    }

    if (c == 'L')
    {
      L(ContadorEnc, ContadorProd, armazem);
      continue;
    }
    else
    {
      
    }

  }

  return 0;
}
