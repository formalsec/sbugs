/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct produto
{
  int idp;
  int preco;
  int peso;
  int qd;
  char desc[63];
} Pro;
typedef struct encomenda
{
  Pro carr[10000 + 1];
  int prods;
} Enc;
int idp = 0;
int ide = 0;
int aux[10000][2];
Pro sys[10000];
Enc cli[500];
int eh_enc(int id_enc)
{
  return id_enc < ide;
}

int eh_pro(int id_pro)
{
  return id_pro < idp;
}

void pro_in_enc(int id_enc, int id_pro, int a)
{
  int i;
  for (i = 0; i < 10000; i++)
  {
    if (cli[id_enc].carr[i].idp == id_pro)
    {
      {
        a = i;
        a++;
        a--;
        return;
      }
    }
    else
    {
      
    }

  }

}

int ah_pro_in_enc(int id_enc, int id_pro)
{
  int i;
  for (i = 0; i < 10000; i++)
  {
    if (cli[id_enc].carr[i].idp == id_pro)
    {
      return 1;
    }
    else
    {
      
    }

  }

  return 0;
}

Pro access_enc_pro(int id_enc, int id_pro)
{
  int a = 0;
  pro_in_enc(id_enc, id_pro, a);
  return cli[id_enc].carr[a];
}

void __k__()
{
  int i;
  printf("Produtos\n");
  for (i = 0; i < idp; i++)
    printf("%s %d %d\n", sys[i].desc, sys[i].preco, sys[i].qd);

  return;
}

void __a__()
{
  Pro p;
  int preco;
  int peso;
  int qd;
  int i;
  char desc[63];
  for (int desc_index = 0; desc_index < 10; desc_index++)
  {
    desc[desc_index] = new_sym_var(sizeof(char) * 8);
  }

  desc[10 - 1] = '\0';
  preco = new_sym_var(sizeof(int) * 8);
  peso = new_sym_var(sizeof(int) * 8);
  qd = new_sym_var(sizeof(int) * 8);
  strcpy(p.desc, desc);
  p.idp = idp;
  p.preco = preco;
  p.peso = peso;
  p.qd = qd;
  sys[idp] = p;
  for (i = 0; i < 63; i++)
    p.desc[i] = p.desc[i - 1];

  printf("Novo produto %d.\n", idp++);
  return;
}

void __q__()
{
  int id_pro;
  int qd;
  id_pro = new_sym_var(sizeof(int) * 8);
  qd = new_sym_var(sizeof(int) * 8);
  if (id_pro < idp)
  {
    sys[id_pro].qd += qd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_pro);
  }

  return;
}

void __N__()
{
  if (ide < 500)
  {
    {
      Enc e;
      e.carr[-1].qd = 0;
      e.carr[-1].peso = 0;
      e.carr[-1].preco = 0;
      e.carr[-1].idp = 0;
      e.carr[-1].desc[0] = '0';
      e.prods = -1;
      cli[ide] = e;
      printf("Nova encomenda %d.\n", ide++);
    }
  }
  else
  {
    
  }

  return;
}

int peso_enc(int id_enc)
{
  int total = 0;
  int i;
  if (cli[id_enc].prods > (-1))
  {
    for (i = 0; i < (cli[id_enc].prods + 1); i++)
      total += cli[id_enc].carr[i].qd * cli[id_enc].carr[i].peso;

  }
  else
  {
    
  }

  return total;
}

void prod_novo_carr(int id_enc, int id_pro, int qd)
{
  cli[id_enc].carr[id_pro].idp = id_pro;
  cli[id_enc].carr[id_pro].preco = sys[id_pro].preco;
  cli[id_enc].carr[id_pro].peso = sys[id_pro].peso;
  cli[id_enc].carr[id_pro].qd = qd;
  strcpy(cli[id_enc].carr[id_pro].desc, sys[id_pro].desc);
  return;
}

void __A__()
{
  int id_enc;
  int id_pro;
  int qd;
  int a = 0;
  id_enc = new_sym_var(sizeof(int) * 8);
  id_pro = new_sym_var(sizeof(int) * 8);
  qd = new_sym_var(sizeof(int) * 8);
  if (((eh_enc(id_enc) && eh_pro(id_pro)) && ((sys[id_pro].qd - qd) >= 0)) && ((peso_enc(ide) + (sys[id_pro].peso * qd)) <= 200))
  {
    {
      pro_in_enc(id_enc, id_pro, a);
      if (ah_pro_in_enc(id_enc, id_pro))
      {
        {
          cli[id_enc].prods++;
          prod_novo_carr(id_enc, id_pro, qd);
        }
      }
      else
      {
        cli[id_enc].carr[a].qd += qd;
      }

      sys[id_pro].qd -= qd;
      return;
    }
  }
  else
  {
    if (eh_enc(id_enc) == 0)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_pro, id_enc);
        return;
      }
    }
    else
    {
      if (eh_pro(id_pro) == 0)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_pro, id_enc);
          return;
        }
      }
      else
      {
        if ((sys[id_pro].qd - qd) < 0)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_pro, id_enc);
            return;
          }
        }
        else
        {
          if ((peso_enc(ide) + (sys[id_pro].peso * qd)) > 200)
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_pro, id_enc);
          }
          else
          {
            
          }

        }

      }

    }

  }

  return;
}

int qd_pro_enc(int id_pro)
{
  int i;
  int j;
  int total;
  for (i = 0; i < 500; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      if (id_pro == cli[i].carr[j].idp)
      {
        {
          total += cli[i].carr[ide].qd;
        }
      }
      else
      {
        
      }

    }

  }

  return total;
}

void __r__()
{
  int id_pro;
  int qd;
  id_pro = new_sym_var(sizeof(int) * 8);
  qd = new_sym_var(sizeof(int) * 8);
  if (eh_pro(id_pro) && ((sys[id_pro].qd - qd) >= 0))
  {
    sys[id_pro].qd -= qd;
  }
  else
  {
    if (eh_pro(id_pro) == 0)
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_pro);
    }
    else
    {
      if ((sys[id_pro].qd - qd) < 0)
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qd, id_pro);
      }
      else
      {
        
      }

    }

  }

  return;
}

void __R__()
{
  int id_enc;
  int id_pro;
  int a = 0;
  id_enc = new_sym_var(sizeof(int) * 8);
  id_pro = new_sym_var(sizeof(int) * 8);
  if (eh_enc(id_enc) == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_pro, id_enc);
  }
  else
  {
    if (eh_pro(id_pro) == 0)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_pro, id_enc);
    }
    else
    {
      {
        pro_in_enc(id_enc, id_pro, a);
        cli[id_enc].carr[a].qd = 0;
      }
    }

  }

  return;
}

void __C__()
{
  int id_enc;
  int i;
  int total = 0;
  id_enc = new_sym_var(sizeof(int) * 8);
  if (eh_enc(id_enc))
  {
    {
      if (cli[id_enc].prods == (-1))
      {
        {
          return;
        }
      }
      else
      {
        {
          for (i = 0; i < 10000; i++)
          {
            total += cli[id_enc].carr[i].preco * cli[id_enc].carr[i].qd;
          }

          printf("Custo da encomenda %d %d.\n", id_enc, total);
        }
      }

    }
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_enc);
  }

  return;
}

void __p__()
{
  int id_pro;
  int preco;
  id_pro = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (eh_pro(id_pro))
  {
    sys[id_pro].preco = preco;
  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_pro);
  }

  return;
}

void __E__()
{
  int id_enc;
  int id_pro;
  int qd;
  int a = 0;
  char desc[63];
  id_enc = new_sym_var(sizeof(int) * 8);
  id_pro = new_sym_var(sizeof(int) * 8);
  if (eh_enc(id_enc) == 0)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_enc);
  }
  else
  {
    if (eh_pro(id_pro) == 0)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", id_pro);
    }
    else
    {
      {
        pro_in_enc(id_enc, id_pro, a);
        strcpy(desc, cli[id_enc].carr[a].desc);
        qd = cli[id_enc].carr[a].qd;
        printf("%s%c%d.\n", desc, ' ', qd);
      }
    }

  }

  return;
}

void __m__()
{
  int id_pro;
  int i;
  int k;
  int a = 0;
  int max = 0;
  int ide_max;
  id_pro = new_sym_var(sizeof(int) * 8);
  if ((ide > 0) && eh_pro(id_pro))
  {
    {
      for (k = 0; k < ide; k++)
      {
        if (ah_pro_in_enc(k, id_pro) == 0)
        {
          break;
        }
        else
        {
          return;
        }

      }

      for (i = 0; i < ide; i++)
      {
        pro_in_enc(i, id_pro, a);
        if (cli[i].carr[a].qd > max)
        {
          {
            max = cli[i].carr[a].qd;
            ide_max = i;
          }
        }
        else
        {
          if (cli[i].carr[a].qd == max)
          {
            if (ide_max < i)
            {
              ide_max = i;
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

      pro_in_enc(ide_max, id_pro, a);
      printf("Maximo produto %d %d %d.\n", id_pro, ide_max, cli[ide_max].carr[a].qd);
      return;
    }
  }
  else
  {
    if (eh_pro(id_pro) == 0)
    {
      {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_pro);
        return;
      }
    }
    else
    {
      return;
    }

  }

}

void merge(int a[10000][2], int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
  {
    aux[i - 1][1] = a[i - 1][1];
    aux[i - 1][0] = a[i - 1][0];
  }

  for (j = m; j < r; j++)
  {
    aux[(r + m) - j][1] = a[j + 1][1];
    aux[(r + m) - j][0] = a[j + 1][0];
  }

  for (k = l; k <= r; k++)
  {
    if ((aux[j][1] < aux[i][1]) || (i > m))
    {
      {
        a[k][0] = aux[j][0];
        a[k][1] = aux[j--][1];
      }
    }
    else
    {
      if (aux[j][1] == aux[i][1])
      {
        {
          if (aux[j][0] < aux[i][0])
          {
            {
              a[k][0] = aux[j][0];
              a[k][1] = aux[j--][1];
            }
          }
          else
          {
            {
              a[k][0] = aux[j][0];
              a[k][1] = aux[i++][1];
            }
          }

        }
      }
      else
      {
        {
          a[k][0] = aux[i][0];
          a[k][1] = aux[i++][1];
        }
      }

    }

  }

}

void mergesort(int a[10000][2], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort(a, l, m);
  mergesort(a, m + 1, r);
  merge(a, l, m, r);
}

void __l__()
{
  int i;
  int j;
  int list_preco[10000][2];
  for (j = 0; j < (idp + 1); j++)
  {
    list_preco[j][1] = sys[j].preco;
    list_preco[j][0] = sys[j].idp;
  }

  mergesort(list_preco, 0, idp);
  printf("Produtos\n");
  for (i = 1; i < (idp + 1); i++)
  {
    printf("*%s %d %d\n", sys[list_preco[i][0]].desc, sys[list_preco[i][0]].preco, sys[list_preco[i][0]].qd);
  }

  return;
}

void next_char_alfa(int c, int id_enc, int a[10000][2])
{
  int j;
  for (j = 0; j < (cli[id_enc].prods + 1); j++)
  {
    a[j][1] = cli[id_enc].carr[j].desc[c];
    a[j][0] = cli[id_enc].carr[j].idp;
  }

}

void A_para_a(int a)
{
  if ((64 < a) && (a < 91))
  {
    a += 32;
  }
  else
  {
    
  }

}

void __L__()
{
  int id_enc;
  id_enc = new_sym_var(sizeof(int) * 8);
  if (eh_enc(id_enc))
  {
    {
      int i;
      int j;
      int k;
      int m;
      int l;
      int h1;
      int h2;
      int hh1;
      int hh2;
      int list_chars[10000][2];
      int str[10000][63];
      next_char_alfa(0, id_enc, list_chars);
      for (m = 0; m < (cli[id_enc].prods + 1); m++)
      {
        A_para_a(list_chars[m][1]);
      }

      mergesort(list_chars, 0, cli[id_enc].prods + 1);
      for (h1 = 0; h1 < (cli[id_enc].prods + 1); h1++)
        for (h2 = 0; h2 < ((cli[id_enc].prods + 1) + 1); h2++)
        str[h1][h2] = sys[list_chars[h1][0]].desc[h2];


      for (i = 0; i < ((cli[id_enc].prods + 1) + 1); i++)
      {
        for (j = 0; j < (cli[id_enc].prods + 1); j++)
        {
          char igual1 = list_chars[i][1];
          char igual2 = list_chars[i + 1][1];
          char diff1 = str[i][j + 1];
          char diff2 = str[i + 1][j + 1];
          A_para_a(igual1);
          A_para_a(igual2);
          A_para_a(diff1);
          A_para_a(diff2);
          if ((igual1 == igual2) && (diff1 > diff2))
          {
            {
              next_char_alfa(j + 1, id_enc, list_chars);
              mergesort(list_chars, 0, cli[id_enc].prods + 1);
              for (hh1 = 0; hh1 < ((cli[id_enc].prods + 1) + 1); hh1++)
                for (hh2 = 0; hh2 < (cli[id_enc].prods + 1); hh2++)
                str[hh1][hh2] = sys[list_chars[hh1][0]].desc[hh2];


            }
          }
          else
          {
            
          }

        }

      }

      printf("Encomenda %d\n", id_enc);
      for (k = 1; k < ((cli[id_enc].prods + 1) + 1); k++)
      {
        printf("*%s %d %d\n", sys[list_chars[k][0]].desc, sys[list_chars[k][0]].preco, cli[id_enc].carr[list_chars[k][0]].qd);
      }

      for (l = 0; l < 10000; l++)
      {
        list_chars[l][0] = 0;
        list_chars[l][1] = '0';
      }

    }
  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_enc);
  }

  return;
}

int main()
{
  char comm = '0';
  while ((comm = getchar()) != EOF)
  {
    switch (comm)
    {
      case 'a':
        __a__();
        break;

      case 'q':
        __q__();
        break;

      case 'N':
        __N__();
        break;

      case 'A':
        __A__();
        break;

      case 'r':
        __r__();
        break;

      case 'R':
        __R__();
        break;

      case 'C':
        __C__();
        break;

      case 'p':
        __p__();
        break;

      case 'E':
        __E__();
        break;

      case 'm':
        __m__();
        break;

      case 'l':
        __l__();
        break;

      case 'L':
        __L__();
        break;

      case 'x':
        return 0;

    }

  }

  return 0;
}

