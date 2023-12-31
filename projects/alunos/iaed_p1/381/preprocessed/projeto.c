#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


struct Stock
{
  char nome[63 + 1];
  int preco;
  int peso;
  int qtd;
  int idp;
};
struct Encomendas
{
  int n_produtos;
  int peso;
  int preco;
  struct Stock produto_encomenda[200];
};
struct Stock produto[10000];
struct Encomendas encomenda[500];
int p = -1;
int e = -1;
char c;
int partition(int a[], int l, int r)
{
  int i = l - 1;
  int j = r;
  int v = a[r];
  while (i < j)
  {
    if (c == 'l')
    {
      while ((produto[a[++i]].preco < produto[v].preco) || ((produto[a[i]].preco == produto[v].preco) && (a[i] < v)))
        ;

      while ((produto[v].preco < produto[a[--j]].preco) || ((produto[a[j]].preco == produto[v].preco) && (a[j] > v)))
        if (j == l)
      {
        break;
      }
      else
      {
        
      }


    }
    else
    {
      if (c == 'L')
      {
        while (strcmp(produto[a[++i]].nome, produto[v].nome) < 0)
          ;

        while (strcmp(produto[v].nome, produto[a[--j]].nome) < 0)
          if (j == l)
        {
          break;
        }
        else
        {
          
        }


      }
      else
      {
        
      }

    }

    if (i < j)
    {
      int t = a[i];
      a[i] = a[j];
      a[j] = t;
    }
    else
    {
      
    }

    ;
  }

  {
    int t = a[i];
    a[i] = a[r];
    a[r] = t;
  }
  ;
  return i;
}

void quicksort(int a[], int l, int r)
{
  int i;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  i = partition(a, l, r);
  quicksort(a, l, i - 1);
  quicksort(a, i + 1, r);
}

void a_Command()
{
  p = p + 1;
  for (int produto_index = 0; produto_index < (63 + 1); produto_index++)
  {
    produto[p].nome[produto_index] = new_sym_var(sizeof(char) * 8);
  }

  produto[p].nome[(63 + 1) - 1] = '\0';
  produto[p].preco = new_sym_var(sizeof(int) * 8);
  produto[p].peso = new_sym_var(sizeof(int) * 8);
  produto[p].qtd = new_sym_var(sizeof(int) * 8);
  produto[p].idp = p;
  printf("Novo produto %d.\n", p);
}

void q_Command()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp > p)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    produto[idp].qtd += qtd;
  }

}

void r_Command()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp > p)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if ((produto[idp].qtd - qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      produto[idp].qtd -= qtd;
    }

  }

}

void p_Command()
{
  int idp;
  int preco;
  int j;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp > p)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (e == (-1))
    {
      produto[idp].preco = preco;
    }
    else
    {
      for (j = 0; j <= e; j++)
      {
        for (i = 0; i <= encomenda[j].n_produtos; i++)
        {
          if (encomenda[j].produto_encomenda[i].idp == idp)
          {
            encomenda[j].preco -= encomenda[j].produto_encomenda[i].preco * encomenda[j].produto_encomenda[i].qtd;
            encomenda[j].produto_encomenda[i].preco = preco;
            encomenda[j].preco += preco * encomenda[j].produto_encomenda[i].qtd;
            break;
          }
          else
          {
            
          }

        }

      }

      produto[idp].preco = preco;
    }

  }

}

void m_Command()
{
  int idp;
  int maxqtd;
  int ide;
  int i;
  int j;
  idp = new_sym_var(sizeof(int) * 8);
  maxqtd = 0;
  ide = -1;
  if (idp > p)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (j = 0; j <= e; j++)
    {
      for (i = 0; i <= encomenda[j].n_produtos; i++)
      {
        if (encomenda[j].produto_encomenda[i].idp == idp)
        {
          if (encomenda[j].produto_encomenda[i].qtd > maxqtd)
          {
            maxqtd = encomenda[j].produto_encomenda[i].qtd;
            ide = j;
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

    if (maxqtd)
    {
      printf("Maximo produto %d %d %d.\n", idp, ide, maxqtd);
    }
    else
    {
      
    }

  }

}

void l_Command()
{
  int i;
  int a[10000];
  printf("Produtos\n");
  for (i = 0; i <= p; i++)
  {
    a[i] = i;
  }

  quicksort(a, 0, p);
  for (i = 0; i <= p; i++)
  {
    printf("* %s %d %d\n", produto[a[i]].nome, produto[a[i]].preco, produto[a[i]].qtd);
  }

}

void N_Command()
{
  printf("Nova encomenda %d.\n", ++e);
  encomenda[e].n_produtos = -1;
}

void A_Command()
{
  int ide;
  int idp;
  int qtd;
  int i;
  int a = 0;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ide > e)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp > p)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (qtd > produto[idp].qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((encomenda[ide].peso + (produto[idp].peso * qtd)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          for (i = 0; i <= encomenda[ide].n_produtos; i++)
          {
            if (encomenda[ide].produto_encomenda[i].idp == idp)
            {
              encomenda[ide].preco += produto[idp].preco * qtd;
              encomenda[ide].peso += produto[idp].peso * qtd;
              encomenda[ide].produto_encomenda[i].qtd += qtd;
              produto[idp].qtd -= qtd;
              a = 1;
            }
            else
            {
              
            }

          }

          if (a == 0)
          {
            encomenda[ide].peso += produto[idp].peso * qtd;
            encomenda[ide].preco += produto[idp].preco * qtd;
            produto[idp].qtd -= qtd;
            encomenda[ide].n_produtos += 1;
            strcpy(encomenda[ide].produto_encomenda[encomenda[ide].n_produtos].nome, produto[idp].nome);
            encomenda[ide].produto_encomenda[encomenda[ide].n_produtos].preco = produto[idp].preco;
            encomenda[ide].produto_encomenda[encomenda[ide].n_produtos].peso = produto[idp].peso;
            encomenda[ide].produto_encomenda[encomenda[ide].n_produtos].idp = produto[idp].idp;
            encomenda[ide].produto_encomenda[encomenda[ide].n_produtos].qtd = qtd;
          }
          else
          {
            
          }

        }

      }

    }

  }

}

void R_Command()
{
  int ide;
  int idp;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide > e)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp > p)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      for (i = 0; i <= encomenda[ide].n_produtos; i++)
      {
        if (encomenda[ide].produto_encomenda[i].idp == idp)
        {
          encomenda[ide].peso -= produto[idp].peso * encomenda[ide].produto_encomenda[i].qtd;
          encomenda[ide].preco -= produto[idp].preco * encomenda[ide].produto_encomenda[i].qtd;
          produto[idp].qtd += encomenda[ide].produto_encomenda[i].qtd;
          encomenda[ide].produto_encomenda[i].qtd = 0;
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void C_Command()
{
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide > e)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", ide, encomenda[ide].preco);
  }

}

void E_Command()
{
  int ide;
  int idp;
  int i;
  int qtd = 0;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide > e)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp > p)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      for (i = 0; i <= encomenda[ide].n_produtos; i++)
      {
        if (encomenda[ide].produto_encomenda[i].idp == idp)
        {
          qtd = encomenda[ide].produto_encomenda[i].qtd;
          break;
        }
        else
        {
          
        }

      }

      printf("%s %d.\n", produto[idp].nome, qtd);
    }

  }

}

void L_Command()
{
  int ide;
  int i;
  int a[200];
  int qtd;
  int j;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide > e)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    printf("Encomenda %d\n", ide);
    for (i = 0; i <= encomenda[ide].n_produtos; i++)
    {
      a[i] = encomenda[ide].produto_encomenda[i].idp;
    }

    quicksort(a, 0, encomenda[ide].n_produtos);
    for (i = 0; i <= encomenda[ide].n_produtos; i++)
    {
      for (j = 0; j <= encomenda[ide].n_produtos; j++)
      {
        if (a[i] == encomenda[ide].produto_encomenda[j].idp)
        {
          qtd = encomenda[ide].produto_encomenda[j].qtd;
          break;
        }
        else
        {
          
        }

      }

      if (qtd != 0)
      {
        printf("* %s %d %d\n", encomenda[ide].produto_encomenda[j].nome, encomenda[ide].produto_encomenda[j].preco, qtd);
      }
      else
      {
        
      }

    }

  }

}

int main()
{
  while (1)
  {
    c = new_sym_var(sizeof(char) * 8);
    switch (c)
    {
      case 'a':
        a_Command();
        break;

      case 'q':
        q_Command();
        break;

      case 'r':
        r_Command();
        break;

      case 'p':
        p_Command();
        break;

      case 'm':
        m_Command();
        break;

      case 'l':
        l_Command();
        break;

      case 'N':
        N_Command();
        break;

      case 'A':
        A_Command();
        break;

      case 'R':
        R_Command();
        break;

      case 'C':
        C_Command();
        break;

      case 'E':
        E_Command();
        break;

      case 'L':
        L_Command();
        break;

      case 'x':
        return 0;

    }

  }

  return 0;
}

