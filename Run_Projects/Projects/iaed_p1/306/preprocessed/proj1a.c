/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef int Item;
Item aux[10000];
Item aux1[10000];
int idp = 0;
int ide = 0;
int idp_aux;
int ide_aux;
int qtd;
int preco_aux;
typedef struct 
{
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
} produto;
typedef struct 
{
  int qtd_prod[10000];
  int preco;
  int peso;
  int contador;
} encomenda;
produto produtos[10000];
encomenda encomendas[500] = {0};
void merge(Item a[], Item b[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
  {
    aux[i - 1] = a[i - 1];
    aux1[i - 1] = b[i - 1];
  }

  for (j = m; j < r; j++)
  {
    aux[(r + m) - j] = a[j + 1];
    aux1[(r + m) - j] = b[j + 1];
  }

  for (k = l; k <= r; k++)
    if ((aux[j] < aux[i]) || (i > m))
  {
    {
      b[k] = aux1[j];
      a[k] = aux[j--];
    }
  }
  else
  {
    {
      b[k] = aux1[i];
      a[k] = aux[i++];
    }
  }


}

void mergesort(Item a[], Item b[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort(a, b, l, m);
  mergesort(a, b, m + 1, r);
  merge(a, b, l, m, r);
}

void InsertionSort_str(char a[10000][63], int l, int r)
{
  int i;
  for (i = l + 1; i <= r; i++)
  {
    int j;
    char v[63];
    strcpy(v, a[i]);
    j = i - 1;
    while ((j >= l) && (strcmp(v, a[j]) < 0))
    {
      strcpy(a[j + 1], a[j]);
      j--;
    }

    strcpy(a[j + 1], v);
  }

}

void a()
{
  for (int produtos_index = 0; produtos_index < 10; produtos_index++)
  {
    produtos[idp].descricao[produtos_index] = new_sym_var(sizeof(char) * 8);
  }

  produtos[idp].descricao[10 - 1] = '\0';
  produtos[idp].preco = new_sym_var(sizeof(int) * 8);
  produtos[idp].peso = new_sym_var(sizeof(int) * 8);
  produtos[idp].quantidade = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", idp);
  idp++;
}

void q()
{
  idp_aux = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp_aux < idp)
  {
    produtos[idp_aux].quantidade += qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_aux);
  }

}

void N()
{
  printf("Nova encomenda %d.\n", ide);
  ide++;
}

void A()
{
  ide_aux = new_sym_var(sizeof(int) * 8);
  idp_aux = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ide_aux >= ide)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
  }
  else
  {
    if (idp_aux >= idp)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
    }
    else
    {
      if (qtd > produtos[idp_aux].quantidade)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_aux, ide_aux);
      }
      else
      {
        if (((qtd * produtos[idp_aux].peso) + encomendas[ide_aux].peso) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_aux, ide_aux);
        }
        else
        {
          {
            encomendas[ide_aux].qtd_prod[idp_aux] += qtd;
            encomendas[ide_aux].peso += produtos[idp_aux].peso * qtd;
            encomendas[ide_aux].preco += produtos[idp_aux].preco * qtd;
            encomendas[ide_aux].contador++;
            produtos[idp_aux].quantidade -= qtd;
          }
        }

      }

    }

  }

}

void r()
{
  idp_aux = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp_aux >= idp)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_aux);
  }
  else
  {
    if ((produtos[idp_aux].quantidade - qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp_aux);
    }
    else
    {
      produtos[idp_aux].quantidade -= qtd;
    }

  }

}

void R()
{
  ide_aux = new_sym_var(sizeof(int) * 8);
  idp_aux = new_sym_var(sizeof(int) * 8);
  if (ide_aux >= ide)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
  }
  else
  {
    if (idp_aux >= idp)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
    }
    else
    {
      {
        qtd = encomendas[ide_aux].qtd_prod[idp_aux];
        if (qtd > 0)
        {
          {
            produtos[idp_aux].quantidade += qtd;
            encomendas[ide_aux].peso -= produtos[idp_aux].peso * qtd;
            encomendas[ide_aux].preco -= produtos[idp_aux].preco * qtd;
            encomendas[ide_aux].qtd_prod[idp_aux] = 0;
            encomendas[ide_aux].contador--;
          }
        }
        else
        {
          
        }

      }
    }

  }

}

void C()
{
  ide_aux = new_sym_var(sizeof(int) * 8);
  if (ide_aux >= ide)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_aux);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", ide_aux, encomendas[ide_aux].preco);
  }

}

void p()
{
  idp_aux = new_sym_var(sizeof(int) * 8);
  preco_aux = new_sym_var(sizeof(int) * 8);
  if (idp_aux >= idp)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_aux);
  }
  else
  {
    {
      int i;
      for (i = 0; i < ide; i++)
      {
        qtd = encomendas[i].qtd_prod[idp_aux];
        encomendas[i].preco -= produtos[idp_aux].preco * qtd;
        encomendas[i].preco += preco_aux * qtd;
      }

      produtos[idp_aux].preco = preco_aux;
    }
  }

}

void E()
{
  ide_aux = new_sym_var(sizeof(int) * 8);
  idp_aux = new_sym_var(sizeof(int) * 8);
  if (ide_aux >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
  }
  else
  {
    if (idp_aux >= idp)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp_aux);
    }
    else
    {
      printf("%s %d.\n", produtos[idp_aux].descricao, encomendas[ide_aux].qtd_prod[idp_aux]);
    }

  }

}

void m()
{
  idp_aux = new_sym_var(sizeof(int) * 8);
  if (idp_aux >= idp)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_aux);
  }
  else
  {
    {
      int i;
      int max = 0;
      for (i = 0; i < ide; i++)
        if (encomendas[i].qtd_prod[idp_aux] > max)
      {
        {
          max = encomendas[i].qtd_prod[idp_aux];
          ide_aux = i;
        }
      }
      else
      {
        
      }


      if (max > 0)
      {
        printf("Maximo produto %d %d %d.\n", idp_aux, ide_aux, max);
      }
      else
      {
        
      }

    }
  }

}

void l()
{
  int i;
  int precos[10000];
  int indices[10000];
  printf("Produtos\n");
  for (i = 0; i < idp; i++)
  {
    precos[i] = produtos[i].preco;
    indices[i] = i;
  }

  mergesort(precos, indices, 0, idp - 1);
  for (i = 0; i < idp; i++)
    printf("* %s %d %d\n", produtos[indices[i]].descricao, produtos[indices[i]].preco, produtos[indices[i]].quantidade);

}

void L_aux(char str[10000][63], int contador)
{
  int i;
  int j;
  for (i = 0; i < contador; i++)
    for (j = 0; j < idp; j++)
    if (strcmp(str[i], produtos[j].descricao) == 0)
  {
    {
      printf("* %s %d %d\n", str[i], produtos[j].preco, encomendas[ide_aux].qtd_prod[j]);
      break;
    }
  }
  else
  {
    
  }



}

void L()
{
  ide_aux = new_sym_var(sizeof(int) * 8);
  if (ide_aux >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
  }
  else
  {
    {
      int i;
      int j = 0;
      int contador;
      char str[10000][63] = {0};
      contador = encomendas[ide_aux].contador;
      printf("Encomenda %d\n", ide_aux);
      for (i = 0; i < idp; i++)
        if (encomendas[ide_aux].qtd_prod[i] > 0)
      {
        {
          strcpy(str[j], produtos[i].descricao);
          j++;
        }
      }
      else
      {
        
      }


      InsertionSort_str(str, 0, contador - 1);
      L_aux(str, contador);
    }
  }

}

int main()
{
  char command;
  while ((command = getchar()) != 'x')
  {
    switch (command)
    {
      case 'a':
        a();
        break;

      case 'q':
        q();
        break;

      case 'N':
        N();
        break;

      case 'A':
        A();
        break;

      case 'r':
        r();
        break;

      case 'R':
        R();
        break;

      case 'C':
        C();
        break;

      case 'p':
        p();
        break;

      case 'E':
        E();
        break;

      case 'm':
        m();
        break;

      case 'l':
        l();
        break;

      case 'L':
        L();
        break;

    }

    getchar();
  }

  return 0;
}

