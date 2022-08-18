/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct produto
{
  char descricao[64];
  int preco;
  int peso;
  int qtd;
  int identificador;
} Produto;
typedef struct encomenda
{
  Produto p[200];
  int peso;
  int preco;
  int variedade;
} Encomenda;
Produto nprodutos[10000];
Encomenda n_encomendas[500];
Produto copia_p[10000];
Encomenda copia_e[500];
char *separador(char s[80], char v[8][64])
{
  int i;
  char *str;
  i = 0;
  str = strtok(s, ":");
  while (str != 0)
  {
    strcpy(v[i], str);
    str = strtok(0, ":");
    i++;
  }

  return (char *) v;
}

int a(Produto nprodutos[10000], char s[80], int idp)
{
  char v[8][64];
  separador(s, v);
  strcpy(nprodutos[idp].descricao, v[0]);
  nprodutos[idp].preco = atoi(v[1]);
  nprodutos[idp].peso = atoi(v[2]);
  nprodutos[idp].qtd = atoi(v[3]);
  nprodutos[idp].identificador = idp;
  printf("Novo produto %d.\n", idp);
  return ++idp;
}

void q(Produto nprodutos[10000], char s[80], int idp)
{
  char v[8][64];
  int idp_aux;
  int adiciona_quantidade;
  separador(s, v);
  idp_aux = atoi(v[0]);
  adiciona_quantidade = atoi(v[1]);
  if (idp_aux >= idp)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_aux);
    }
  }
  else
  {
    {
      nprodutos[idp_aux].qtd += adiciona_quantidade;
    }
  }

}

void r(Produto nprodutos[10000], char s[80], int idp)
{
  char v[8][64];
  int idp_aux;
  int retira_quantidade;
  separador(s, v);
  idp_aux = atoi(v[0]);
  retira_quantidade = atoi(v[1]);
  if (idp_aux >= idp)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_aux);
    }
  }
  else
  {
    if (retira_quantidade > nprodutos[idp_aux].qtd)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", retira_quantidade, idp_aux);
      }
    }
    else
    {
      {
        nprodutos[idp_aux].qtd -= retira_quantidade;
      }
    }

  }

}

void p(Produto nprodutos[10000], char s[80], int idp, int ide, Encomenda n_encomendas[500])
{
  char v[8][64];
  int idp_aux;
  int preco_novo;
  int i;
  separador(s, v);
  idp_aux = atoi(v[0]);
  preco_novo = atoi(v[1]);
  if (idp_aux >= idp)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_aux);
    }
  }
  else
  {
    {
      nprodutos[idp_aux].preco = preco_novo;
      for (i = 0; i < ide; i++)
      {
        n_encomendas[i].p[idp_aux].preco = preco_novo;
      }

    }
  }

}

int peso_encomenda(Encomenda n_encomendas[500], int ide_aux, int idp)
{
  int i;
  n_encomendas[ide_aux].peso = 0;
  for (i = 0; n_encomendas[ide_aux].p[i].descricao < n_encomendas[ide_aux].p[idp].descricao; i++)
  {
    n_encomendas[ide_aux].peso += n_encomendas[ide_aux].p[i].qtd * n_encomendas[ide_aux].p[i].peso;
  }

  return n_encomendas[ide_aux].peso;
}

void A(Encomenda n_encomendas[500], Produto nprodutos[10000], char s[80], int ide, int idp)
{
  char v[8][64];
  int ide_aux;
  int idp_aux;
  int adiciona_quantidade;
  int soma = 0;
  separador(s, v);
  ide_aux = atoi(v[0]);
  idp_aux = atoi(v[1]);
  adiciona_quantidade = atoi(v[2]);
  if (ide_aux >= ide)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
    }
  }
  else
  {
    if (idp_aux >= idp)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
      }
    }
    else
    {
      if (adiciona_quantidade > nprodutos[idp_aux].qtd)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_aux, ide_aux);
        }
      }
      else
      {
        {
          soma += adiciona_quantidade * nprodutos[idp_aux].peso;
          soma += peso_encomenda(n_encomendas, ide_aux, idp);
          if (soma <= 200)
          {
            {
              if (n_encomendas[ide_aux].p[idp_aux].qtd == 0)
              {
                {
                  nprodutos[idp_aux].qtd -= adiciona_quantidade;
                  n_encomendas[ide_aux].p[idp_aux].qtd = adiciona_quantidade;
                  n_encomendas[ide_aux].p[idp_aux].preco = nprodutos[idp_aux].preco;
                  n_encomendas[ide_aux].p[idp_aux].peso = nprodutos[idp_aux].peso;
                  strcpy(n_encomendas[ide_aux].p[idp_aux].descricao, nprodutos[idp_aux].descricao);
                  n_encomendas[ide_aux].p[idp_aux].identificador = nprodutos[idp_aux].identificador;
                  n_encomendas[ide_aux].variedade += 1;
                }
              }
              else
              {
                {
                  n_encomendas[ide_aux].p[idp_aux].qtd += adiciona_quantidade;
                  nprodutos[idp_aux].qtd -= adiciona_quantidade;
                }
              }

            }
          }
          else
          {
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_aux, ide_aux);
            }
          }

        }
      }

    }

  }

}

void R(Encomenda n_encomendas[500], Produto nprodutos[10000], char s[80], int ide, int idp)
{
  char v[8][64];
  int ide_aux;
  int idp_aux;
  separador(s, v);
  ide_aux = atoi(v[0]);
  idp_aux = atoi(v[1]);
  if (ide_aux >= ide)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
    }
  }
  else
  {
    if (idp_aux >= idp)
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
      }
    }
    else
    {
      {
        nprodutos[idp_aux].qtd += n_encomendas[ide_aux].p[idp_aux].qtd;
        n_encomendas[ide_aux].p[idp_aux].qtd = 0;
        n_encomendas[ide_aux].p[idp_aux].preco = nprodutos[idp_aux].preco;
        n_encomendas[ide_aux].p[idp_aux].peso = nprodutos[idp_aux].peso;
        strcpy(n_encomendas[ide_aux].p[idp_aux].descricao, nprodutos[idp_aux].descricao);
        n_encomendas[ide_aux].p[idp_aux].identificador = nprodutos[idp_aux].identificador;
      }
    }

  }

}

void C(Encomenda n_encomendas[500], int ide, int idp)
{
  int ide_aux;
  int i;
  int total = 0;
  ide_aux = new_sym_var(sizeof(int) * 8);
  if (ide_aux >= ide)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_aux);
    }
  }
  else
  {
    {
      for (i = 0; n_encomendas[ide_aux].p[i].descricao < n_encomendas[ide_aux].p[idp].descricao; i++)
      {
        total += n_encomendas[ide_aux].p[i].qtd * n_encomendas[ide_aux].p[i].preco;
      }

      printf("Custo da encomenda %d %d.\n", ide_aux, total);
    }
  }

}

int E(Encomenda n_encomendas[500], char s[80], int ide, int idp, Produto nprodutos[10000])
{
  char v[8][64];
  int ide_aux;
  int idp_aux;
  separador(s, v);
  ide_aux = atoi(v[0]);
  idp_aux = atoi(v[1]);
  if (ide_aux >= ide)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
    }
  }
  else
  {
    if (idp_aux >= idp)
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp_aux);
      }
    }
    else
    {
      {
        printf("%s %d.\n", nprodutos[idp_aux].descricao, n_encomendas[ide_aux].p[idp_aux].qtd);
      }
    }

  }

  return 0;
}

void m(Encomenda n_encomendas[500], int ide, int idp)
{
  int idp_aux;
  int maior;
  int i;
  int ide_aux;
  idp_aux = new_sym_var(sizeof(int) * 8);
  if (idp_aux >= idp)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_aux);
    }
  }
  else
  {
    {
      maior = 0;
      ide_aux = 0;
      if (ide >= ide_aux)
      {
        {
          for (i = 0; n_encomendas[i].p[idp_aux].descricao <= n_encomendas[ide].p[idp_aux].descricao; i++)
          {
            if ((n_encomendas[i].p[idp_aux].qtd != 0) && (n_encomendas[i].p[idp_aux].qtd > maior))
            {
              {
                maior = n_encomendas[i].p[idp_aux].qtd;
                ide_aux = i;
              }
            }
            else
            {
              
            }

          }

          if (maior > 0)
          {
            {
              printf("Maximo produto %d %d %d.\n", idp_aux, ide_aux, maior);
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

}

void copia(Produto nprodutos[10000], Produto copia_p[10000], int idp)
{
  int i;
  for (i = 0; i < idp; i++)
  {
    strcpy(copia_p[i].descricao, nprodutos[i].descricao);
    copia_p[i].preco = nprodutos[i].preco;
    copia_p[i].peso = nprodutos[i].peso;
    copia_p[i].qtd = nprodutos[i].qtd;
    copia_p[i].identificador = nprodutos[i].identificador;
  }

}

void exch_p(Produto copia_p[], int i, int j)
{
  Produto a = copia_p[i];
  copia_p[i] = copia_p[j];
  copia_p[j] = a;
}

int particao_preco(Produto copia_p[], int l, int r)
{
  int i;
  int j;
  Produto v = copia_p[r];
  i = l - 1;
  for (j = l; j <= (r - 1); j++)
  {
    if (copia_p[j].preco < v.preco)
    {
      {
        i++;
        exch_p(copia_p, i, j);
      }
    }
    else
    {
      if (copia_p[j].preco == v.preco)
      {
        {
          if (v.identificador > copia_p[j].identificador)
          {
            {
              i++;
              exch_p(copia_p, i, j);
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

  exch_p(copia_p, i + 1, r);
  return i + 1;
}

void ordena_preco(Produto copia_p[], int l, int r)
{
  int i;
  if (l < r)
  {
    {
      i = particao_preco(copia_p, l, r);
      ordena_preco(copia_p, l, i - 1);
      ordena_preco(copia_p, i + 1, r);
    }
  }
  else
  {
    
  }

}

void l(Produto nprodutos[10000], Produto copia_p[10000], int idp)
{
  int i;
  copia(nprodutos, copia_p, idp);
  printf("Produtos\n");
  ordena_preco(copia_p, 0, idp - 1);
  for (i = 0; i < idp; i++)
  {
    printf("* %s %d %d\n", copia_p[i].descricao, copia_p[i].preco, copia_p[i].qtd);
  }

}

void copia_encomenda(Encomenda n_encomendas[500], Encomenda copia_e[500], int ide_aux)
{
  int i;
  for (i = 0; i < n_encomendas[ide_aux].variedade; i++)
  {
    strcpy(copia_e[ide_aux].p[i].descricao, n_encomendas[ide_aux].p[i].descricao);
    copia_e[ide_aux].p[i].preco = n_encomendas[ide_aux].p[i].preco;
    copia_e[ide_aux].p[i].peso = n_encomendas[ide_aux].p[i].peso;
    copia_e[ide_aux].p[i].qtd = n_encomendas[ide_aux].p[i].qtd;
    copia_e[ide_aux].p[i].identificador = n_encomendas[ide_aux].p[i].identificador;
    copia_e[ide_aux].peso = n_encomendas[ide_aux].peso;
    copia_e[ide_aux].preco = n_encomendas[ide_aux].preco;
    copia_e[ide_aux].variedade = n_encomendas[ide_aux].variedade;
  }

}

void exch_e(Encomenda copia_e[], int i, int j, int ide_aux)
{
  Encomenda a[500];
  a[ide_aux].p[0] = copia_e[ide_aux].p[i];
  copia_e[ide_aux].p[i] = copia_e[ide_aux].p[j];
  copia_e[ide_aux].p[j] = a[ide_aux].p[0];
}

int particao(Encomenda copia_e[], int l, int r, int ide_aux)
{
  int i = l - 1;
  int j = r;
  Encomenda v = copia_e[r];
  while (i < j)
  {
    while (strcmp(copia_e[ide_aux].p[++i].descricao, v.p[r].descricao) < 0)
      ;

    while (strcmp(v.p[r].descricao, copia_e[ide_aux].p[--j].descricao) < 0)
      if (j == l)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      exch_e(copia_e, i, j, ide_aux);
    }
    else
    {
      
    }

  }

  exch_e(copia_e, i, r, ide_aux);
  return i;
}

void ordena_descricao(Encomenda copia_e[], int l, int r, int ide_aux)
{
  int i;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  i = particao(copia_e, l, r, ide_aux);
  ordena_descricao(copia_e, l, i - 1, ide_aux);
  ordena_descricao(copia_e, i + 1, r, ide_aux);
}

void L(Encomenda n_encomendas[500], Encomenda copia_e[500], int ide)
{
  int ide_aux;
  int i;
  int len;
  ide_aux = new_sym_var(sizeof(int) * 8);
  if (ide_aux >= ide)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
    }
  }
  else
  {
    {
      copia_encomenda(n_encomendas, copia_e, ide_aux);
      len = n_encomendas[ide_aux].variedade;
      printf("Encomenda %d\n", ide_aux);
      ordena_descricao(copia_e, 0, len - 1, ide_aux);
      for (i = 0; i < len; i++)
      {
        if (copia_e[ide_aux].p[i].qtd != 0)
        {
          {
            printf("* %s %d %d\n", copia_e[ide_aux].p[i].descricao, copia_e[ide_aux].p[i].preco, copia_e[ide_aux].p[i].qtd);
          }
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
  char n;
  char s[80];
  int idp = 0;
  int ide = 0;
  while (1)
  {
    n = new_sym_var(sizeof(char) * 8);
    switch (n)
    {
      case 'a':
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        idp = a(nprodutos, s, idp);
        break;

      case 'q':
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        q(nprodutos, s, idp);
        break;

      case 'N':
        printf("Nova encomenda %d.\n", ide++);
        break;

      case 'A':
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        A(n_encomendas, nprodutos, s, ide, idp);
        break;

      case 'r':
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        r(nprodutos, s, idp);
        break;

      case 'R':
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        R(n_encomendas, nprodutos, s, ide, idp);
        break;

      case 'C':
        C(n_encomendas, ide, idp);
        break;

      case 'p':
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        p(nprodutos, s, idp, ide, n_encomendas);
        break;

      case 'E':
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        E(n_encomendas, s, ide, idp, nprodutos);
        break;

      case 'm':
        m(n_encomendas, ide, idp);
        break;

      case 'l':
        l(nprodutos, copia_p, idp);
        break;

      case 'L':
        L(n_encomendas, copia_e, ide);
        break;

      case 'x':
        return 0;
        break;

    }

  }

}

