/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  char descricao[64];
  int preco;
  int peso;
  int stock;
  int idp;
} produto;
typedef struct 
{
  produto prod_encomenda[100];
  int peso;
  int ide;
  int num_prod;
} encomenda;
void a(produto *a, int *n);
void q(produto arr[]);
void N(encomenda *a, int *n);
void A(produto arrp[], encomenda arre[]);
void r(produto arr[]);
void R(produto arrp[], encomenda arre[]);
void C(encomenda arr[]);
void p(produto arrp[], encomenda arre[], int n);
void E(produto arrp[], encomenda arre[]);
void m(produto arrp[], encomenda arre[], int n);
void l(produto arr[], int n);
void L(encomenda arr[]);
int main()
{
  produto lista_produtos[10000];
  encomenda lista_encomendas[500];
  int num_prod = 0;
  int num_enc = 0;
  int c;
  c = getchar();
  while (c != 'x')
  {
    if (c == 'a')
    {
      a(&lista_produtos[num_prod], &num_prod);
    }
    else
    {
      if (c == 'q')
      {
        q(lista_produtos);
      }
      else
      {
        if (c == 'N')
        {
          N(&lista_encomendas[num_enc], &num_enc);
        }
        else
        {
          if (c == 'A')
          {
            A(lista_produtos, lista_encomendas);
          }
          else
          {
            if (c == 'r')
            {
              r(lista_produtos);
            }
            else
            {
              if (c == 'R')
              {
                R(lista_produtos, lista_encomendas);
              }
              else
              {
                if (c == 'C')
                {
                  C(lista_encomendas);
                }
                else
                {
                  if (c == 'p')
                  {
                    p(lista_produtos, lista_encomendas, num_enc);
                  }
                  else
                  {
                    if (c == 'E')
                    {
                      E(lista_produtos, lista_encomendas);
                    }
                    else
                    {
                      if (c == 'm')
                      {
                        m(lista_produtos, lista_encomendas, num_enc);
                      }
                      else
                      {
                        if (c == 'l')
                        {
                          l(lista_produtos, num_prod);
                        }
                        else
                        {
                          if (c == 'L')
                          {
                            L(lista_encomendas);
                          }
                          else
                          {
                            
                          }

                        }

                      }

                    }

                  }

                }

              }

            }

          }

        }

      }

    }

    c = getchar();
  }

  return 0;
}

void merge1(produto a[], int left, int m, int right)
{
  produto aux[10000];
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = a[j + 1];

  for (k = left; k <= right; k++)
  {
    if (((aux[j].preco < aux[i].preco) || (i > m)) || ((aux[j].preco == aux[i].preco) && (aux[j].idp < aux[i].idp)))
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }

  }

}

void mergesort1(produto a[], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort1(a, left, m);
  mergesort1(a, m + 1, right);
  merge1(a, left, m, right);
}

void merge2(produto a[], int left, int m, int right)
{
  produto aux[150];
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = a[j + 1];

  for (k = left; k <= right; k++)
  {
    if ((strcmp(aux[j].descricao, aux[i].descricao) < 0) || (i > m))
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }

  }

}

void mergesort2(produto a[], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort2(a, left, m);
  mergesort2(a, m + 1, right);
  merge2(a, left, m, right);
}

void a(produto *a, int *n)
{
  int k = *n;
  for (int a_index = 0; a_index < 10; a_index++)
  {
    a->descricao[a_index] = new_sym_var(sizeof(char) * 8);
  }

  a->descricao[10 - 1] = '\0';
  a->preco = new_sym_var(sizeof(int) * 8);
  a->peso = new_sym_var(sizeof(int) * 8);
  a->stock = new_sym_var(sizeof(int) * 8);
  a->idp = k;
  printf("Novo produto %d.\n", k);
  *n += 1;
}

void q(produto arr[])
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (arr[idp].idp != idp)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    arr[idp].stock += qtd;
  }

}

void N(encomenda *a, int *n)
{
  a->num_prod = 0;
  a->peso = 0;
  a->ide = *n;
  printf("Nova encomenda %d.\n", *n);
  *n += 1;
}

void A(produto arrp[], encomenda arre[])
{
  int idp;
  int ide;
  int qtd;
  int i;
  int estado;
  estado = 0;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (arre[ide].ide == ide)
  {
    if (arrp[idp].idp == idp)
    {
      if (arrp[idp].stock >= qtd)
      {
        if ((arre[ide].peso + (arrp[idp].peso * qtd)) <= 200)
        {
          for (i = 0; i < arre[ide].num_prod; i++)
            if ((arre[ide].prod_encomenda[i].idp == idp) && (arre[ide].prod_encomenda[i].stock > 0))
          {
            arre[ide].prod_encomenda[i].stock += qtd;
            arre[ide].peso += arrp[idp].peso * qtd;
            estado = 1;
          }
          else
          {
            
          }


          if (estado == 0)
          {
            int j;
            j = arre[ide].num_prod;
            arre[ide].prod_encomenda[j].idp = arrp[idp].idp;
            arre[ide].prod_encomenda[j].peso = arrp[idp].peso;
            arre[ide].prod_encomenda[j].preco = arrp[idp].preco;
            arre[ide].prod_encomenda[j].stock = qtd;
            strcpy(arre[ide].prod_encomenda[j].descricao, arrp[idp].descricao);
            arre[ide].num_prod += 1;
            arre[ide].peso += arrp[idp].peso * qtd;
          }
          else
          {
            
          }

          arrp[idp].stock -= qtd;
        }
        else
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }

      }
      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }

    }
    else
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }

}

void r(produto arr[])
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (arr[idp].idp == idp)
  {
    if ((arr[idp].stock - qtd) >= 0)
    {
      arr[idp].stock -= qtd;
    }
    else
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }

}

void R(produto arrp[], encomenda arre[])
{
  int idp;
  int ide;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (arre[ide].ide == ide)
  {
    if (arrp[idp].idp == idp)
    {
      for (i = 0; i < arre[ide].num_prod; i++)
        if (arre[ide].prod_encomenda[i].idp == idp)
      {
        arrp[idp].stock += arre[ide].prod_encomenda[i].stock;
        arre[ide].peso -= arre[ide].prod_encomenda[i].peso * arre[ide].prod_encomenda[i].stock;
        arre[ide].prod_encomenda[i].stock = 0;
        break;
      }
      else
      {
        
      }


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

void C(encomenda arr[])
{
  int ide;
  int total = 0;
  int i;
  int preco;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  if (arr[ide].ide == ide)
  {
    for (i = 0; i < arr[ide].num_prod; i++)
      if (arr[ide].prod_encomenda[i].stock > 0)
    {
      preco = arr[ide].prod_encomenda[i].preco;
      qtd = arr[ide].prod_encomenda[i].stock;
      total += preco * qtd;
    }
    else
    {
      
    }


    printf("Custo da encomenda %d %d.\n", ide, total);
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }

}

void p(produto arrp[], encomenda arre[], int n)
{
  int idp;
  int preco;
  int i;
  int j;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (arrp[idp].idp == idp)
  {
    arrp[idp].preco = preco;
    for (i = 0; i < n; i++)
      for (j = 0; j < arre[i].num_prod; j++)
      if (arre[i].prod_encomenda[j].idp == idp)
    {
      arre[i].prod_encomenda[j].preco = preco;
      break;
    }
    else
    {
      
    }



  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }

}

void E(produto arrp[], encomenda arre[])
{
  int idp;
  int ide;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (arre[ide].ide == ide)
  {
    if (arrp[idp].idp == idp)
    {
      for (i = 0; i < arre[ide].num_prod; i++)
        if (arre[ide].prod_encomenda[i].idp == idp)
      {
        printf("%s %d.\n", arre[ide].prod_encomenda[i].descricao, arre[ide].prod_encomenda[i].stock);
        break;
      }
      else
      {
        
      }


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

void m(produto arrp[], encomenda arre[], int n)
{
  int idp;
  int ide;
  int i;
  int j;
  int num_max = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (arrp[idp].idp == idp)
  {
    for (i = 0; i < n; i++)
      for (j = 0; j < arre[ide].num_prod; j++)
      if (arre[i].prod_encomenda[j].idp == idp)
    {
      num_max = arre[i].prod_encomenda[j].stock;
      ide = i;
      break;
    }
    else
    {
      
    }



    if (num_max > 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, ide, num_max);
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

void l(produto arr[], int n)
{
  int i;
  mergesort1(arr, 0, n - 1);
  printf("Produtos\n");
  for (i = 0; i < n; i++)
    printf("* %s %d %d\n", arr[i].descricao, arr[i].preco, arr[i].stock);

}

void L(encomenda arr[])
{
  int i;
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (arr[ide].ide == ide)
  {
    mergesort2(arr[ide].prod_encomenda, 0, arr[ide].num_prod - 1);
    printf("Encomenda %d\n", ide);
    for (i = 0; i < arr[ide].num_prod; i++)
      if (arr[ide].prod_encomenda[i].stock > 0)
    {
      printf("* %s %d %d\n", arr[ide].prod_encomenda[i].descricao, arr[ide].prod_encomenda[i].preco, arr[ide].prod_encomenda[i].stock);
    }
    else
    {
      
    }


  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }

}

