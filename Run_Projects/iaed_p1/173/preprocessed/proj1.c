/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  int idp;
  char descricao[64];
  int preco;
  int pesoprod;
  int stock;
} produto;
typedef struct ecomenda
{
  produto Vprodutos[200];
  int ide;
  int pesoenc;
  int elementos;
} encomenda;
int utilizadosprod = 0;
int utilizadosenc = 0;
produto prod;
encomenda enc;
produto sistemaprod[10000];
encomenda sistemaenc[500];
int VerificaEncomenda(int utilizadosenc, int ide)
{
  if (ide >= utilizadosenc)
  {
    {
      return 0;
    }
  }
  else
  {
    {
      return 1;
    }
  }

}

int VerificaProduto(int utilizadosprod, int idp)
{
  if (idp >= utilizadosprod)
  {
    {
      return 0;
    }
  }
  else
  {
    {
      return 1;
    }
  }

}

int VerificaStock(int idp, int qtd)
{
  if (sistemaprod[idp].stock >= qtd)
  {
    {
      return 1;
    }
  }
  else
  {
    {
      return 0;
    }
  }

}

int VerificaPeso(int ide, int idp, int qtd)
{
  if ((sistemaenc[ide].pesoenc + (sistemaprod[idp].pesoprod * qtd)) > 200)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  return 1;
}

int EncontraProduto(int qtd, int ide, int idp)
{
  int i;
  for (i = 0; i < sistemaenc[ide].elementos; i++)
  {
    if (sistemaenc[ide].Vprodutos[i].idp == sistemaprod[idp].idp)
    {
      {
        sistemaenc[ide].Vprodutos[i].stock += qtd;
        sistemaprod[idp].stock -= qtd;
        sistemaenc[ide].pesoenc += sistemaprod[idp].pesoprod * qtd;
        return 1;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

void AdicionaProdEncomenda(int qtd, int ide, int idp)
{
  sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos].idp = sistemaprod[idp].idp;
  sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos].stock = qtd;
  sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos].preco = sistemaprod[idp].preco;
  strcpy(sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos].descricao, sistemaprod[idp].descricao);
  sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos].pesoprod = sistemaprod[idp].pesoprod;
  sistemaenc[ide].pesoenc += sistemaprod[idp].pesoprod * qtd;
  sistemaprod[idp].stock -= qtd;
  sistemaenc[ide].elementos++;
}

void RemoveDaEncomenda(int ide, int idp)
{
  int i;
  for (i = 0; i < sistemaenc[ide].elementos; i++)
  {
    if (sistemaenc[ide].Vprodutos[i].idp == idp)
    {
      {
        sistemaprod[idp].stock += sistemaenc[ide].Vprodutos[i].stock;
        sistemaenc[ide].pesoenc -= sistemaenc[ide].Vprodutos[i].stock * sistemaenc[ide].Vprodutos[i].pesoprod;
        sistemaenc[ide].Vprodutos[i].idp = sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos - 1].idp;
        sistemaenc[ide].Vprodutos[i].stock = sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos - 1].stock;
        sistemaenc[ide].Vprodutos[i].pesoprod = sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos - 1].pesoprod;
        sistemaenc[ide].Vprodutos[i].preco = sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos - 1].preco;
        strcpy(sistemaenc[ide].Vprodutos[i].descricao, sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos - 1].descricao);
        sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos - 1].idp = -1;
        sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos - 1].stock = 0;
        sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos - 1].pesoprod = 0;
        sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos - 1].preco = 0;
        strcpy(sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos - 1].descricao, "");
        sistemaenc[ide].elementos--;
        break;
      }
    }
    else
    {
      
    }

  }

}

void merge(int precos[], int esquerda, int centro, int direita, int indices[])
{
  int i1;
  int i2;
  int f;
  int auxp1[10000];
  int auxp2[10000];
  int auxid1[10000];
  int auxid2[10000];
  for (i1 = 0; i1 < ((centro - esquerda) + 1); i1++)
  {
    auxp1[i1] = precos[esquerda + i1];
    auxid1[i1] = indices[esquerda + i1];
  }

  for (i2 = 0; i2 < (direita - centro); i2++)
  {
    auxp2[i2] = precos[(centro + 1) + i2];
    auxid2[i2] = indices[(centro + 1) + i2];
  }

  i1 = 0;
  i2 = 0;
  f = esquerda;
  while ((i1 < ((centro - esquerda) + 1)) && (i2 < (direita - centro)))
  {
    if (auxp1[i1] <= auxp2[i2])
    {
      {
        precos[f] = auxp1[i1];
        indices[f] = auxid1[i1];
        i1++;
      }
    }
    else
    {
      {
        precos[f] = auxp2[i2];
        indices[f] = auxid2[i2];
        i2++;
      }
    }

    f++;
  }

  while (i1 < ((centro - esquerda) + 1))
  {
    precos[f] = auxp1[i1];
    indices[f] = auxid1[i1];
    i1++;
    f++;
  }

  while (i2 < (direita - centro))
  {
    precos[f] = auxp2[i2];
    indices[f] = auxid2[i2];
    i2++;
    f++;
  }

}

void mergesort(int precos[], int esquerda, int direita, int indices[])
{
  if (esquerda < direita)
  {
    {
      int centro = esquerda + ((direita - esquerda) / 2);
      mergesort(precos, esquerda, centro, indices);
      mergesort(precos, centro + 1, direita, indices);
      merge(precos, esquerda, centro, direita, indices);
    }
  }
  else
  {
    
  }

}

void quicksort(char descricao[][64], int left, int right, int indices[])
{
  int pivot = left;
  int i;
  int j;
  int aux;
  char str[64];
  for (i = left + 1; i <= right; i++)
  {
    j = i;
    if (strcmp(descricao[j], descricao[pivot]) < 0)
    {
      {
        strcpy(str, descricao[j]);
        aux = indices[j];
        while (j > pivot)
        {
          strcpy(descricao[j], descricao[j - 1]);
          indices[j] = indices[j - 1];
          j--;
        }

        strcpy(descricao[j], str);
        indices[j] = aux;
        pivot++;
      }
    }
    else
    {
      
    }

  }

  if ((pivot - 1) >= left)
  {
    {
      quicksort(descricao, left, pivot - 1, indices);
    }
  }
  else
  {
    
  }

  if ((pivot + 1) <= right)
  {
    {
      quicksort(descricao, pivot + 1, right, indices);
    }
  }
  else
  {
    
  }

}

void comando_a(char descricao[], int preco, int peso, int stock)
{
  prod.idp = utilizadosprod;
  utilizadosprod++;
  sistemaprod[prod.idp].idp = prod.idp;
  sistemaprod[prod.idp].stock = stock;
  sistemaprod[prod.idp].pesoprod = peso;
  strcpy(sistemaprod[prod.idp].descricao, descricao);
  sistemaprod[prod.idp].preco = preco;
  printf("Novo produto %d.\n", prod.idp);
}

void comando_q(int idp, int utilizadosprod, int qtd)
{
  int i;
  for (i = 0; i < utilizadosprod; i++)
  {
    if (idp == sistemaprod[i].idp)
    {
      {
        sistemaprod[i].stock += qtd;
        break;
      }
    }
    else
    {
      
    }

  }

  if (i >= utilizadosprod)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
  }
  else
  {
    
  }

}

void comando_N()
{
  enc.ide = utilizadosenc;
  utilizadosenc++;
  sistemaenc[enc.ide].pesoenc = 0;
  sistemaenc[enc.ide].elementos = 0;
  printf("Nova encomenda %d.\n", enc.ide);
}

void comando_A(int qtd, int ide, int idp)
{
  if (VerificaEncomenda(utilizadosenc, ide) == 0)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    if (VerificaProduto(utilizadosprod, idp) == 0)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
    }
    else
    {
      if (VerificaStock(idp, qtd) == 0)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        }
      }
      else
      {
        if (VerificaPeso(ide, idp, qtd) == 0)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
          }
        }
        else
        {
          if (EncontraProduto(qtd, ide, idp) == 1)
          {
            {
              return;
            }
          }
          else
          {
            {
              AdicionaProdEncomenda(qtd, ide, idp);
            }
          }

        }

      }

    }

  }

}

void comando_r(int qtd, produto prod)
{
  if (VerificaProduto(utilizadosprod, prod.idp) == 0)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod.idp);
    }
  }
  else
  {
    if (VerificaStock(prod.idp, qtd) == 0)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, prod.idp);
      }
    }
    else
    {
      {
        sistemaprod[prod.idp].stock -= qtd;
      }
    }

  }

}

void comando_R(int ide, int idp)
{
  if (VerificaEncomenda(utilizadosenc, ide) == 0)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    if (VerificaProduto(utilizadosprod, idp) == 0)
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
    }
    else
    {
      {
        RemoveDaEncomenda(ide, idp);
      }
    }

  }

}

void comando_C(int ide)
{
  int i;
  int custo = 0;
  if (VerificaEncomenda(utilizadosenc, ide) == 0)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      for (i = 0; i < sistemaenc[ide].elementos; i++)
      {
        custo += sistemaenc[ide].Vprodutos[i].preco * sistemaenc[ide].Vprodutos[i].stock;
      }

      printf("Custo da encomenda %d %d.\n", ide, custo);
    }
  }

}

void comando_p(int idp, int preco)
{
  int i;
  int j;
  if (VerificaProduto(utilizadosprod, idp) == 0)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      sistemaprod[idp].preco = preco;
      for (i = 0; i < utilizadosenc; i++)
      {
        for (j = 0; j < sistemaenc[i].elementos; j++)
        {
          if (sistemaenc[i].Vprodutos[j].idp == idp)
          {
            {
              sistemaenc[i].Vprodutos[j].preco = preco;
            }
          }
          else
          {
            
          }

        }

      }

    }
  }

}

void comando_E(int ide, int idp)
{
  int i;
  if (VerificaEncomenda(utilizadosenc, ide) == 0)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    if (VerificaProduto(utilizadosprod, idp) == 0)
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      }
    }
    else
    {
      {
        for (i = 0; i < sistemaenc[ide].elementos; i++)
        {
          if (sistemaenc[ide].Vprodutos[i].idp == idp)
          {
            {
              printf("%s %d.\n", sistemaenc[ide].Vprodutos[i].descricao, sistemaenc[ide].Vprodutos[i].stock);
              return;
            }
          }
          else
          {
            
          }

        }

        printf("%s 0.\n", sistemaprod[idp].descricao);
      }
    }

  }

}

void comando_m(int idp)
{
  int flag = 0;
  int qtd = 0;
  int ide;
  int i;
  int j;
  if (VerificaProduto(utilizadosprod, idp) == 0)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      for (i = 0; i < utilizadosenc; i++)
      {
        for (j = 0; j < sistemaenc[i].elementos; j++)
        {
          if (sistemaenc[i].Vprodutos[j].idp == idp)
          {
            {
              if (sistemaenc[i].Vprodutos[j].stock > qtd)
              {
                {
                  qtd = sistemaenc[i].Vprodutos[j].stock;
                  ide = i;
                  flag = 1;
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

      if (flag == 1)
      {
        {
          printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
        }
      }
      else
      {
        
      }

    }
  }

}

void comando_l()
{
  int i;
  int indices[10000];
  int precos[10000];
  for (i = 0; i < utilizadosprod; i++)
  {
    indices[i] = i;
    precos[i] = sistemaprod[i].preco;
  }

  mergesort(precos, 0, utilizadosprod - 1, indices);
  printf("Produtos\n");
  for (i = 0; i < utilizadosprod; i++)
  {
    printf("* %s %d %d\n", sistemaprod[indices[i]].descricao, sistemaprod[indices[i]].preco, sistemaprod[indices[i]].stock);
  }

}

void comando_L(int ide)
{
  int i;
  char descricoes[200][64];
  int indices[200];
  if (VerificaEncomenda(utilizadosenc, ide) == 0)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      for (i = 0; i <= sistemaenc[ide].elementos; i++)
      {
        strcpy(descricoes[i], sistemaenc[ide].Vprodutos[i].descricao);
        indices[i] = i;
      }

      quicksort(descricoes, 0, sistemaenc[ide].elementos - 1, indices);
      printf("Encomenda %d\n", ide);
      for (i = 0; i < sistemaenc[ide].elementos; i++)
      {
        printf("* %s %d %d\n", sistemaenc[ide].Vprodutos[indices[i]].descricao, sistemaenc[ide].Vprodutos[indices[i]].preco, sistemaenc[ide].Vprodutos[indices[i]].stock);
      }

    }
  }

}

int main()
{
  int qtd;
  int preco;
  char comando;
  while ((comando = getchar()) != EOF)
  {
    switch (comando)
    {
      case 'a':
        for (int prod_index = 0; prod_index < 10; prod_index++)
      {
        prod.descricao[prod_index] = new_sym_var(sizeof(char) * 8);
      }

        prod.descricao[10 - 1] = '\0';
        prod.preco = new_sym_var(sizeof(int) * 8);
        prod.pesoprod = new_sym_var(sizeof(int) * 8);
        prod.stock = new_sym_var(sizeof(int) * 8);
        comando_a(prod.descricao, prod.preco, prod.pesoprod, prod.stock);
        break;

      case 'q':
        prod.idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        comando_q(prod.idp, utilizadosprod, qtd);
        break;

      case 'N':
        comando_N();
        break;

      case 'A':
        enc.ide = new_sym_var(sizeof(int) * 8);
        prod.idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        comando_A(qtd, enc.ide, prod.idp);
        break;

      case 'r':
        prod.idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        comando_r(qtd, prod);
        break;

      case 'R':
        enc.ide = new_sym_var(sizeof(int) * 8);
        prod.idp = new_sym_var(sizeof(int) * 8);
        comando_R(enc.ide, prod.idp);
        break;

      case 'C':
        enc.ide = new_sym_var(sizeof(int) * 8);
        comando_C(enc.ide);
        break;

      case 'p':
        prod.idp = new_sym_var(sizeof(int) * 8);
        preco = new_sym_var(sizeof(int) * 8);
        comando_p(prod.idp, preco);
        break;

      case 'E':
        enc.ide = new_sym_var(sizeof(int) * 8);
        prod.idp = new_sym_var(sizeof(int) * 8);
        comando_E(enc.ide, prod.idp);
        break;

      case 'm':
        prod.idp = new_sym_var(sizeof(int) * 8);
        comando_m(prod.idp);
        break;

      case 'l':
        comando_l();
        break;

      case 'L':
        enc.ide = new_sym_var(sizeof(int) * 8);
        comando_L(enc.ide);
        break;

      case 'x':
        return 0;

    }

  }

  return -1;
}

