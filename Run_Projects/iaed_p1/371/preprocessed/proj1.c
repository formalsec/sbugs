/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  int id;
  char descricao[64];
  int preco;
  int peso;
  int stock;
} Produto;
Produto produtos_main[10000];
typedef struct encomenda
{
  Produto tab[10000];
  int preco_total;
  int peso_total;
  int prods;
  int maior_id;
} Encomenda;
Encomenda encomenda_main[500];
Encomenda aux_L[500];
void addProd(Produto sistema[10000], int idp)
{
  int c;
  int e = 0;
  char desc_copy[10000];
  getchar();
  while ((c = getchar()) != ':')
  {
    desc_copy[e++] = c;
  }

  desc_copy[e] = '\0';
  strcpy(sistema[idp].descricao, desc_copy);
  sistema[idp].preco = new_sym_var(sizeof(int) * 8);
  sistema[idp].peso = new_sym_var(sizeof(int) * 8);
  sistema[idp].stock = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", idp);
}

void addStock(Produto sistema[10000], int i)
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp > (i - 1))
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      sistema[idp].stock += qtd;
    }
  }

}

void criaEncomenda(int ide)
{
  printf("Nova encomenda %d.\n", ide);
}

void addProd_Encomenda(Produto sistema[10000], Encomenda encomendas[500], int i, int e, Encomenda aux_L[500])
{
  int idp;
  int qtd;
  int ide;
  int j;
  int flag = 2;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  for (j = 0; j < encomendas[ide].maior_id; j++)
  {
    if (strcmp(encomendas[ide].tab[j].descricao, sistema[idp].descricao) == 0)
    {
      {
        flag = 0;
      }
    }
    else
    {
      
    }

  }

  strcpy(encomendas[ide].tab[idp].descricao, sistema[idp].descricao);
  encomendas[ide].tab[idp].peso = sistema[idp].peso;
  encomendas[ide].tab[idp].preco = sistema[idp].preco;
  if (ide > (e - 1))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      flag = 0;
    }
  }
  else
  {
    {
      if (idp > (i - 1))
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
          flag = 0;
        }
      }
      else
      {
        {
          if (sistema[idp].stock < qtd)
          {
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
              flag = 0;
            }
          }
          else
          {
            {
              if ((encomendas[ide].peso_total + (encomendas[ide].tab[idp].peso * qtd)) > 200)
              {
                {
                  printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                  flag = 0;
                }
              }
              else
              {
                {
                  encomendas[ide].peso_total += encomendas[ide].tab[idp].peso * qtd;
                  encomendas[ide].preco_total += sistema[idp].preco * qtd;
                  encomendas[ide].tab[idp].stock += qtd;
                  sistema[idp].stock -= qtd;
                }
              }

              if (flag != 0)
              {
                {
                  encomendas[ide].prods++;
                  strcpy(aux_L[ide].tab[idp].descricao, sistema[idp].descricao);
                }
              }
              else
              {
                
              }

              if ((encomendas[ide].maior_id - 1) < idp)
              {
                {
                  encomendas[ide].maior_id = idp + 1;
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

void removestk(Produto sistema[10000], int i)
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp > (i - 1))
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    if (qtd > sistema[idp].stock)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
      }
    }
    else
    {
      {
        sistema[idp].stock -= qtd;
      }
    }

  }

}

void removeProd_Encomenda(Produto sistema[10000], Encomenda encomendas[500], int i, int e)
{
  int ide;
  int idp;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide > (e - 1))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    {
      if (idp > (i - 1))
      {
        {
          printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
      }
      else
      {
        {
          if (encomendas[ide].tab[idp].stock != 0)
          {
            {
              encomendas[ide].prods -= 1;
            }
          }
          else
          {
            
          }

          qtd = encomendas[ide].tab[idp].stock;
          encomendas[ide].tab[idp].stock = 0;
          encomendas[ide].peso_total -= encomendas[ide].tab[idp].peso * qtd;
          encomendas[ide].tab[idp].peso = 0;
          encomendas[ide].preco_total -= sistema[idp].preco * qtd;
          sistema[idp].stock += qtd;
        }
      }

    }
  }

}

void CalculaCusto(Encomenda encomendas[500], int e)
{
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide > (e - 1))
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      printf("Custo da encomenda %d %d.\n", ide, encomendas[ide].preco_total);
    }
  }

}

void alteraPreco(Produto sistema[10000], Encomenda encomendas[500], int i, int e)
{
  int idp;
  int novo_preco;
  int j;
  int ide;
  idp = new_sym_var(sizeof(int) * 8);
  novo_preco = new_sym_var(sizeof(int) * 8);
  if (idp > (i - 1))
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      for (ide = 0; ide < e; ide++)
      {
        for (j = 0; j < encomendas[ide].maior_id; j++)
        {
          if (strcmp(encomendas[ide].tab[j].descricao, sistema[idp].descricao) == 0)
          {
            {
              encomendas[ide].preco_total -= sistema[idp].preco * encomendas[ide].tab[j].stock;
              sistema[idp].preco = novo_preco;
              encomendas[ide].preco_total += sistema[idp].preco * encomendas[ide].tab[j].stock;
            }
          }
          else
          {
            
          }

        }

      }

      sistema[idp].preco = novo_preco;
    }
  }

}

void descreveProd(Produto sistema[10000], Encomenda encomendas[500], int i, int e)
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide > (e - 1))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      if (idp > (i - 1))
      {
        {
          printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        }
      }
      else
      {
        {
          if (encomendas[ide].tab[idp].stock != 0)
          {
            {
              printf("%s %d.\n", encomendas[ide].tab[idp].descricao, encomendas[ide].tab[idp].stock);
            }
          }
          else
          {
            
          }

          if (encomendas[ide].tab[idp].stock == 0)
          {
            {
              printf("%s %d.\n", sistema[idp].descricao, encomendas[ide].tab[idp].stock);
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

void prodRepetido_encomenda(Encomenda encomendas[500], int i)
{
  int idp;
  int ide;
  int maior = 0;
  int enc = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp > (i - 1))
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      for (ide = 0; ide <= i; ide++)
      {
        if (encomendas[ide].tab[idp].stock == maior)
        {
          {
            if (ide < enc)
            {
              {
                enc = ide;
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

        if (encomendas[ide].tab[idp].stock > maior)
        {
          {
            maior = encomendas[ide].tab[idp].stock;
            enc = ide;
          }
        }
        else
        {
          
        }

      }

    }
  }

  if (maior > 0)
  {
    {
      printf("Maximo produto %d %d %d.\n", idp, enc, maior);
    }
  }
  else
  {
    
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
      {
        arr[k] = L[i];
        i++;
      }
    }
    else
    {
      {
        arr[k] = R[j];
        j++;
      }
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

void ordena_arr(Produto arr[], int l, int r)
{
  if (l < r)
  {
    {
      int m = l + ((r - l) / 2);
      ordena_arr(arr, l, m);
      ordena_arr(arr, m + 1, r);
      merge(arr, l, m, r);
    }
  }
  else
  {
    
  }

}

void precoProd(Produto sistema[10000], int r)
{
  int i;
  Produto arr_ordenado[10000];
  if (r == 0)
  {
    {
      printf("Produtos\n");
    }
  }
  else
  {
    {
      for (i = 0; i < r; i++)
      {
        arr_ordenado[i].preco = sistema[i].preco;
        arr_ordenado[i].id = i;
      }

      ordena_arr(arr_ordenado, 0, r - 1);
      printf("Produtos\n");
      for (i = 0; i < r; i++)
      {
        printf("* %s %d %d\n", sistema[arr_ordenado[i].id].descricao, arr_ordenado[i].preco, sistema[arr_ordenado[i].id].stock);
      }

    }
  }

}

void ordenaProd_Encomenda(Encomenda encomendas[500], Encomenda aux_L[500], int r, int idp, Produto sistema[10000])
{
  int ide;
  int j;
  int i;
  char ord[500];
  ide = new_sym_var(sizeof(int) * 8);
  if (ide > (r - 1))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    if (encomendas[ide].prods == 0)
    {
      {
        printf("Encomenda %d\n", ide);
      }
    }
    else
    {
      {
        if (encomendas[ide].prods == 1)
        {
          {
            printf("Encomenda %d\n", ide);
            for (j = 0; j < idp; j++)
            {
              if ((strcmp(aux_L[ide].tab[j].descricao, sistema[j].descricao) == 0) && (encomendas[ide].tab[j].stock > 0))
              {
                printf("* %s %d %d\n", encomendas[ide].tab[j].descricao, encomendas[ide].tab[j].preco, encomendas[ide].tab[j].stock);
              }
              else
              {
                
              }

            }

          }
        }
        else
        {
          {
            for (i = 0; i <= encomendas[ide].prods; i++)
            {
              for (j = i + 1; j <= encomendas[ide].prods; j++)
              {
                if (strcmp(aux_L[ide].tab[i].descricao, aux_L[ide].tab[j].descricao) > 0)
                {
                  {
                    strcpy(ord, aux_L[ide].tab[i].descricao);
                    strcpy(aux_L[ide].tab[i].descricao, aux_L[ide].tab[j].descricao);
                    strcpy(aux_L[ide].tab[j].descricao, ord);
                  }
                }
                else
                {
                  
                }

              }

            }

            printf("Encomenda %d\n", ide);
            for (i = 0; i <= encomendas[ide].maior_id; i++)
            {
              for (j = 0; j < idp; j++)
              {
                if ((strcmp(aux_L[ide].tab[i].descricao, sistema[j].descricao) == 0) && (encomendas[ide].tab[i].stock > 0))
                {
                  {
                    printf("* %s %d %d\n", aux_L[ide].tab[i].descricao, sistema[j].preco, encomendas[ide].tab[j].stock);
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

int main()
{
  char comando;
  int contador_indice = 0;
  int contador_indice2 = 0;
  while (comando != 'x')
  {
    comando = new_sym_var(sizeof(char) * 8);
    if (comando == 'a')
    {
      {
        addProd(produtos_main, contador_indice);
        contador_indice++;
      }
    }
    else
    {
      
    }

    if (comando == 'q')
    {
      {
        addStock(produtos_main, contador_indice);
      }
    }
    else
    {
      
    }

    if (comando == 'N')
    {
      {
        criaEncomenda(contador_indice2);
        contador_indice2++;
      }
    }
    else
    {
      
    }

    if (comando == 'A')
    {
      {
        addProd_Encomenda(produtos_main, encomenda_main, contador_indice, contador_indice2, aux_L);
      }
    }
    else
    {
      
    }

    if (comando == 'r')
    {
      {
        removestk(produtos_main, contador_indice);
      }
    }
    else
    {
      
    }

    if (comando == 'R')
    {
      {
        removeProd_Encomenda(produtos_main, encomenda_main, contador_indice, contador_indice2);
      }
    }
    else
    {
      
    }

    if (comando == 'C')
    {
      {
        CalculaCusto(encomenda_main, contador_indice2);
      }
    }
    else
    {
      
    }

    if (comando == 'p')
    {
      {
        alteraPreco(produtos_main, encomenda_main, contador_indice, contador_indice2);
      }
    }
    else
    {
      
    }

    if (comando == 'E')
    {
      {
        descreveProd(produtos_main, encomenda_main, contador_indice, contador_indice2);
      }
    }
    else
    {
      
    }

    if (comando == 'm')
    {
      {
        prodRepetido_encomenda(encomenda_main, contador_indice);
      }
    }
    else
    {
      
    }

    if (comando == 'l')
    {
      {
        precoProd(produtos_main, contador_indice);
      }
    }
    else
    {
      
    }

    if (comando == 'L')
    {
      {
        ordenaProd_Encomenda(encomenda_main, aux_L, contador_indice2, contador_indice, produtos_main);
      }
    }
    else
    {
      
    }

  }

  return 0;
}

