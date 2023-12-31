#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


struct Produto
{
  int id;
  int preco;
  int peso;
  int stock;
  char desc[63];
};
struct Encomenda
{
  int id;
  int preco;
  int peso;
  int n_prod;
  struct Produto prod_arr[1000];
};
struct Produto v_prod[10000];
struct Encomenda v_enc[500];
int pont_prod = 0;
int pont_enc = 0;
void calcula_preco_enc(int ide)
{
  int i;
  v_enc[ide].preco = 0;
  for (i = 0; i < v_enc[ide].n_prod; i++)
    v_enc[ide].preco += v_enc[ide].prod_arr[i].stock * v_enc[ide].prod_arr[i].preco;

}

int verifica_prod_em_enc(int idp, struct Produto prods[], int n_prod)
{
  int i;
  for (i = 0; i < n_prod; i++)
  {
    if (idp == prods[i].id)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

void f_a()
{
  for (int v_prod_index = 0; v_prod_index < 10; v_prod_index++)
  {
    v_prod[pont_prod].desc[v_prod_index] = new_sym_var(sizeof(char) * 8);
  }

  v_prod[pont_prod].desc[10 - 1] = '\0';
  v_prod[pont_prod].preco = new_sym_var(sizeof(int) * 8);
  v_prod[pont_prod].peso = new_sym_var(sizeof(int) * 8);
  v_prod[pont_prod].stock = new_sym_var(sizeof(int) * 8);
  v_prod[pont_prod].id = pont_prod;
  printf("Novo produto %d.\n", pont_prod++);
}

void f_q()
{
  int idp;
  int stock;
  idp = new_sym_var(sizeof(int) * 8);
  stock = new_sym_var(sizeof(int) * 8);
  if (idp < pont_prod)
  {
    v_prod[idp].stock += stock;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

}

void f_N()
{
  v_enc[pont_enc].id = pont_enc;
  v_enc[pont_enc].n_prod = 0;
  v_enc[pont_enc].peso = 0;
  v_enc[pont_enc].preco = 0;
  printf("Nova encomenda %d.\n", pont_enc++);
}

void f_A()
{
  int x;
  int ide;
  int idp;
  int stock;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  stock = new_sym_var(sizeof(int) * 8);
  if (ide >= pont_enc)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= pont_prod)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (v_prod[idp].stock < stock)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((v_enc[ide].peso + (stock * v_prod[idp].peso)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          x = verifica_prod_em_enc(idp, v_enc[ide].prod_arr, v_enc[ide].n_prod);
          if (x != (-1))
          {
            v_enc[ide].prod_arr[x].stock += stock;
            v_enc[ide].peso += stock * v_prod[idp].peso;
          }
          else
          {
            v_enc[ide].prod_arr[v_enc[ide].n_prod] = v_prod[idp];
            v_enc[ide].prod_arr[v_enc[ide].n_prod].stock = stock;
            v_enc[ide].peso += stock * v_prod[idp].peso;
            v_enc[ide].n_prod++;
          }

          v_prod[idp].stock -= stock;
        }

      }

    }

  }

}

void f_r()
{
  int idp;
  int stock;
  idp = new_sym_var(sizeof(int) * 8);
  stock = new_sym_var(sizeof(int) * 8);
  if (idp >= pont_prod)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (v_prod[idp].stock < stock)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock, idp);
    }
    else
    {
      v_prod[idp].stock -= stock;
    }

  }

}

void f_R()
{
  int ide;
  int idp;
  int x;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= pont_enc)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= pont_prod)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      x = verifica_prod_em_enc(idp, v_enc[ide].prod_arr, v_enc[ide].n_prod);
      v_enc[ide].peso -= v_enc[ide].prod_arr[x].stock * v_prod[idp].peso;
      v_prod[idp].stock += v_enc[ide].prod_arr[x].stock;
      v_enc[ide].prod_arr[x].stock = 0;
    }

  }

}

void f_C()
{
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= pont_enc)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    calcula_preco_enc(ide);
    printf("Custo da encomenda %d %d.\n", ide, v_enc[ide].preco);
  }

}

void f_p()
{
  int idp;
  int preco;
  int a;
  int b;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp >= pont_prod)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    v_prod[idp].preco = preco;
    for (a = 0; a < pont_enc; a++)
    {
      b = verifica_prod_em_enc(idp, v_enc[a].prod_arr, v_enc[a].n_prod);
      if (b != (-1))
      {
        v_enc[a].prod_arr[b].preco = preco;
      }
      else
      {
        
      }

    }

  }

}

void f_E()
{
  int ide;
  int idp;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= pont_enc)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp >= pont_prod)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      i = verifica_prod_em_enc(idp, v_enc[ide].prod_arr, v_enc[ide].n_prod);
      if (i != (-1))
      {
        printf("%s %d.\n", v_enc[ide].prod_arr[i].desc, v_enc[ide].prod_arr[i].stock);
      }
      else
      {
        printf("%s %d.\n", v_prod[idp].desc, 0);
      }

    }

  }

}

void f_m()
{
  int idp;
  int i;
  int j;
  int qtd = -1;
  int ide;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= pont_prod)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < pont_enc; i++)
    {
      j = verifica_prod_em_enc(idp, v_enc[i].prod_arr, v_enc[i].n_prod);
      if (j != (-1))
      {
        if (v_enc[i].prod_arr[j].stock > qtd)
        {
          qtd = v_enc[i].prod_arr[j].stock;
          ide = i;
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

  if (qtd > 0)
  {
    printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
  }
  else
  {
    
  }

}

int compara_produtos(struct Produto p1, struct Produto p2, int estado_l)
{
  if (estado_l)
  {
    if (p1.preco == p2.preco)
    {
      return p1.id < p2.id;
    }
    else
    {
      
    }

    return p1.preco < p2.preco;
  }
  else
  {
    
  }

  return strcmp(p1.desc, p2.desc) < 0;
}

void swap(struct Produto prods[], int i, int j)
{
  struct Produto p3 = prods[i];
  prods[i] = prods[j];
  prods[j] = p3;
}

int partition(struct Produto prods[], int l, int r, int estado_l)
{
  int i = l - 1;
  int j = r;
  struct Produto v = prods[r];
  while (i < j)
  {
    while (compara_produtos(prods[++i], v, estado_l))
      ;

    while (compara_produtos(v, prods[--j], estado_l))
      if (j == l)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      swap(prods, i, j);
    }
    else
    {
      
    }

  }

  swap(prods, i, r);
  return i;
}

void quicksort(struct Produto prods[], int l, int r, int estado_l)
{
  int i;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  i = partition(prods, l, r, estado_l);
  quicksort(prods, l, i - 1, estado_l);
  quicksort(prods, i + 1, r, estado_l);
}

void f_l()
{
  int i = 0;
  struct Produto v_prod_c[10000];
  for (i = 0; i < pont_prod; i++)
    v_prod_c[i] = v_prod[i];

  quicksort(v_prod_c, 0, pont_prod - 1, 1);
  printf("Produtos\n");
  for (i = 0; i < pont_prod; i++)
    printf("* %s %d %d\n", v_prod_c[i].desc, v_prod_c[i].preco, v_prod_c[i].stock);

}

void f_L()
{
  int ide;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= pont_enc)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    struct Produto v_prod_enc_c[1000];
    for (i = 0; i < v_enc[ide].n_prod; i++)
      v_prod_enc_c[i] = v_enc[ide].prod_arr[i];

    printf("Encomenda %d\n", ide);
    quicksort(v_prod_enc_c, 0, v_enc[ide].n_prod - 1, 0);
    for (i = 0; i < v_enc[ide].n_prod; i++)
      if (v_prod_enc_c[i].stock > 0)
    {
      printf("* %s %d %d\n", v_prod_enc_c[i].desc, v_prod_enc_c[i].preco, v_prod_enc_c[i].stock);
    }
    else
    {
      
    }


  }

}

int main()
{
  char comando;
  while (1)
  {
    comando = getchar();
    getchar();
    switch (comando)
    {
      case 'a':
        f_a();
        break;

      case 'q':
        f_q();
        break;

      case 'N':
        f_N();
        break;

      case 'A':
        f_A();
        break;

      case 'r':
        f_r();
        break;

      case 'R':
        f_R();
        break;

      case 'C':
        f_C();
        break;

      case 'p':
        f_p();
        break;

      case 'E':
        f_E();
        break;

      case 'm':
        f_m();
        break;

      case 'l':
        f_l();
        break;

      case 'L':
        f_L();
        break;

      case 'x':
        return 0;

    }

  }

}

