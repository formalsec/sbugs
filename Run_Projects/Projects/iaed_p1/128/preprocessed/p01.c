/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef int Item;
typedef struct produto
{
  char identificacao[63];
  int preco;
  int peso;
  int stock;
} Produto;
typedef struct encomeda
{
  int descricao[10000];
  int Estado;
  int peso_e;
} Encomenda;
Produto identificador[10000];
Encomenda numero[500];
Produto Leproduto()
{
  Produto a;
  int indice;
  char c_aux;
  for (indice = 0; ((c_aux = getchar()) != ':') && (indice < 63); indice++)
  {
    a.identificacao[indice] = c_aux;
  }

  a.identificacao[indice] = '\0';
  a.peso = new_sym_var(sizeof(int) * 8);
  a.preco = new_sym_var(sizeof(int) * 8);
  a.stock = new_sym_var(sizeof(int) * 8);
  return a;
}

void Soma_quantidade(int qtd, int idp)
{
  identificador[idp].stock = identificador[idp].stock + qtd;
}

Item auxiliar[10000];
void merge(Item a[], int left, int m, int right)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    auxiliar[i - 1] = a[i - 1];

  for (j = m; j < right; j++)
    auxiliar[(right + m) - j] = a[j + 1];

  for (k = left; k <= right; k++)
    if ((identificador[auxiliar[j]].preco < identificador[auxiliar[i]].preco) || (i > m))
  {
    a[k] = auxiliar[j--];
  }
  else
  {
    a[k] = auxiliar[i++];
  }


}

void mergesort(Item a[], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort(a, left, m);
  mergesort(a, m + 1, right);
  merge(a, left, m, right);
}

void ordena_protudo()
{
  int len;
  int aux;
  int b[10000];
  len = 0;
  for (aux = 0; aux < 10000; aux++)
  {
    if (identificador[aux].preco != 0)
    {
      b[len] = aux;
      len += 1;
    }
    else
    {
      
    }

  }

  mergesort(b, 0, len - 1);
  printf("Produtos\n");
  for (aux = 0; aux < len; aux++)
  {
    printf("* %s %d %d\n", identificador[b[aux]].identificacao, identificador[b[aux]].preco, identificador[b[aux]].stock);
  }

}

int Custo_encomenda(int ide)
{
  int aux;
  int sum;
  int n;
  int l;
  sum = 0;
  for (aux = 0; aux < 10000; aux++)
  {
    if (numero[ide].descricao[aux] != 0)
    {
      n = numero[ide].descricao[aux];
      l = identificador[aux].preco;
      sum = sum + (n * l);
    }
    else
    {
      
    }

  }

  return sum;
}

void Remove_pro_e(int idp, int ide)
{
  int aux;
  aux = identificador[idp].peso * numero[ide].descricao[idp];
  identificador[idp].stock = identificador[idp].stock + numero[ide].descricao[idp];
  numero[ide].descricao[idp] = 0;
  numero[ide].peso_e = numero[ide].peso_e - aux;
}

int Maximo_p(int idp)
{
  int c;
  int res;
  res = 0;
  for (c = 0; c < 500; c++)
  {
    if (numero[c].descricao[idp] > numero[res].descricao[c])
    {
      res = c;
    }
    else
    {
      
    }

  }

  return res;
}

int partition(Item a[], int left, int right)
{
  int i = left - 1;
  int j = right;
  int aux;
  char v[63];
  for (aux = 0; (aux < 63) && (identificador[a[right]].identificacao[aux] != '\0'); aux++)
  {
    v[aux] = identificador[a[right]].identificacao[aux];
  }

  v[aux] = '\0';
  while (i < j)
  {
    while (strcmp(identificador[a[++i]].identificacao, v) < 0)
      ;

    while (strcmp(v, identificador[a[--j]].identificacao) < 0)
      if (j == left)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      Item t = a[i];
      a[i] = a[j];
      a[j] = t;
    }
    else
    {
      
    }

    ;
  }

  {
    Item t = a[i];
    a[i] = a[right];
    a[right] = t;
  }
  ;
  return i;
}

void quicksort(Item a[], int left, int right)
{
  int i;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  i = partition(a, left, right);
  quicksort(a, left, i - 1);
  quicksort(a, i + 1, right);
}

void Ordena_enc(int ide)
{
  int aux;
  int len;
  int d[10000];
  len = 0;
  for (aux = 0; aux < 10000; aux++)
  {
    if (numero[ide].descricao[aux] > 0)
    {
      d[len] = aux;
      len = len + 1;
    }
    else
    {
      
    }

  }

  quicksort(d, 0, len - 1);
  for (aux = 0; aux < len; aux++)
  {
    printf("* %s %d %d\n", identificador[d[aux]].identificacao, identificador[d[aux]].preco, numero[ide].descricao[d[aux]]);
  }

}

void altera(int idp, int prize)
{
  identificador[idp].preco = prize;
}

void adiciona(int ide, int idp, int qtd)
{
  numero[ide].descricao[idp] = numero[ide].descricao[idp] + qtd;
  identificador[idp].stock = identificador[idp].stock - qtd;
  numero[ide].peso_e = numero[ide].peso_e + (identificador[idp].peso * qtd);
}

int main()
{
  char comando;
  int indice1;
  int indice2;
  int ide;
  int idp;
  int qtd;
  int prize;
  int estado;
  comando = getchar();
  while (comando != 'x')
  {
    if (comando == 'a')
    {
      estado = 0;
      getchar();
      for (indice1 = 0; (estado != 1) && (indice1 < 10000); indice1++)
      {
        if ((identificador[indice1].preco == 0) && (identificador[indice1].peso == 0))
        {
          identificador[indice1] = Leproduto();
          printf("Novo produto %d.\n", indice1);
          estado = 1;
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (comando == 'q')
      {
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        if (identificador[idp].preco != 0)
        {
          Soma_quantidade(qtd, idp);
        }
        else
        {
          printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        }

      }
      else
      {
        if (comando == 'N')
        {
          estado = 0;
          for (indice1 = 0; (estado != 1) && (indice1 < 500); indice1++)
          {
            if (numero[indice1].Estado == 0)
            {
              numero[indice1].Estado = 1;
              printf("Nova encomenda %d.\n", indice1);
              estado = 1;
            }
            else
            {
              
            }

          }

        }
        else
        {
          if (comando == 'A')
          {
            ide = new_sym_var(sizeof(int) * 8);
            idp = new_sym_var(sizeof(int) * 8);
            qtd = new_sym_var(sizeof(int) * 8);
            if (numero[ide].Estado == 0)
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
            }
            else
            {
              if (identificador[idp].preco == 0)
              {
                printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
              }
              else
              {
                if (qtd > identificador[idp].stock)
                {
                  printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
                }
                else
                {
                  if (((identificador[idp].peso * qtd) + numero[ide].peso_e) > 200)
                  {
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                  }
                  else
                  {
                    adiciona(ide, idp, qtd);
                  }

                }

              }

            }

          }
          else
          {
            if (comando == 'r')
            {
              idp = new_sym_var(sizeof(int) * 8);
              qtd = new_sym_var(sizeof(int) * 8);
              if (identificador[idp].preco == 0)
              {
                printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
              }
              else
              {
                if (identificador[idp].stock < qtd)
                {
                  printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
                }
                else
                {
                  identificador[idp].stock = identificador[idp].stock - qtd;
                }

              }

            }
            else
            {
              if (comando == 'R')
              {
                ide = new_sym_var(sizeof(int) * 8);
                idp = new_sym_var(sizeof(int) * 8);
                if (numero[ide].Estado == 0)
                {
                  printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
                }
                else
                {
                  if (identificador[idp].preco == 0)
                  {
                    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
                  }
                  else
                  {
                    Remove_pro_e(idp, ide);
                  }

                }

              }
              else
              {
                if (comando == 'C')
                {
                  ide = new_sym_var(sizeof(int) * 8);
                  if (numero[ide].Estado == 0)
                  {
                    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
                  }
                  else
                  {
                    printf("Custo da encomenda %d %d.\n", ide, Custo_encomenda(ide));
                  }

                }
                else
                {
                  if (comando == 'p')
                  {
                    idp = new_sym_var(sizeof(int) * 8);
                    prize = new_sym_var(sizeof(int) * 8);
                    if (identificador[idp].preco == 0)
                    {
                      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
                    }
                    else
                    {
                      altera(idp, prize);
                    }

                  }
                  else
                  {
                    if (comando == 'E')
                    {
                      ide = new_sym_var(sizeof(int) * 8);
                      idp = new_sym_var(sizeof(int) * 8);
                      if (numero[ide].Estado == 0)
                      {
                        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
                      }
                      else
                      {
                        if (identificador[idp].preco == 0)
                        {
                          printf("Impossivel listar protudo %d. Produto inexistente.\n", idp);
                        }
                        else
                        {
                          printf("%s %d.\n", identificador[idp].identificacao, numero[ide].descricao[idp]);
                        }

                      }

                    }
                    else
                    {
                      if (comando == 'm')
                      {
                        idp = new_sym_var(sizeof(int) * 8);
                        if (identificador[idp].preco == 0)
                        {
                          printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
                        }
                        else
                        {
                          indice2 = Maximo_p(idp);
                          if (numero[indice2].descricao[idp] != 0)
                          {
                            printf("Maximo produto %d %d %d.\n", idp, indice2, numero[indice2].descricao[idp]);
                          }
                          else
                          {
                            
                          }

                        }

                      }
                      else
                      {
                        if (comando == 'l')
                        {
                          ordena_protudo();
                        }
                        else
                        {
                          if (comando == 'L')
                          {
                            ide = new_sym_var(sizeof(int) * 8);
                            if (numero[ide].Estado == 0)
                            {
                              printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
                            }
                            else
                            {
                              printf("Encomenda %d\n", ide);
                              Ordena_enc(ide);
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

              }

            }

          }

        }

      }

    }

    comando = getchar();
  }

  return 0;
}

