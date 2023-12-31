#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


struct produto
{
  int idp;
  char descricao[64];
  int preco;
  int peso;
  int qtd;
};
int idp = 0;
int ide = 0;
struct artigo
{
  int idp;
  int qtd;
};
struct encomenda
{
  int ide;
  struct artigo lista_artigos[200];
  int peso;
  int last;
};
struct produto sistema[10000];
struct encomenda lista_enc[500];
int left;
int right;
void executa_a(char descricao[], int preco, int peso, int qtd);
void executa_q(int identificador, int qtd);
void executa_N();
void executa_A(int enc, int identificador, int qtd);
void executa_r(int dentificador, int qtd);
void executa_R(int enc, int identificador);
void executa_C(int enc);
void executa_p(int identificador, int preco);
void executa_E(int enc, int identificador);
void executa_m(int identificador);
void executa_l();
void executa_L(int enc);
void mergesort(struct artigo desord[], int left, int right);
void merge(struct artigo desord[], int left, int m, int right);
void quicksort(struct produto desordenado[], int left, int right);
int partition(struct produto desordenado[], int left, int right);
int less(struct produto a, struct produto b);
void exch(struct produto desordenado[], int a, int b);
int less_a(struct artigo a, struct artigo b);
int main()
{
  char descricao[64];
  int preco;
  int peso;
  int qtd;
  int identificador;
  int enc;
  char comando;
  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      case 'a':
        for (int descricao_index = 0; descricao_index < 10; descricao_index++)
      {
        descricao[descricao_index] = new_sym_var(sizeof(char) * 8);
      }

        descricao[10 - 1] = '\0';
        preco = new_sym_var(sizeof(int) * 8);
        peso = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        executa_a(descricao, preco, peso, qtd);
        break;

      case 'q':
        identificador = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        executa_q(identificador, qtd);
        break;

      case 'N':
        executa_N();
        break;

      case 'A':
        enc = new_sym_var(sizeof(int) * 8);
        identificador = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        executa_A(enc, identificador, qtd);
        break;

      case 'r':
        identificador = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        executa_r(identificador, qtd);
        break;

      case 'R':
        enc = new_sym_var(sizeof(int) * 8);
        identificador = new_sym_var(sizeof(int) * 8);
        executa_R(enc, identificador);
        break;

      case 'C':
        enc = new_sym_var(sizeof(int) * 8);
        executa_C(enc);
        break;

      case 'p':
        identificador = new_sym_var(sizeof(int) * 8);
        preco = new_sym_var(sizeof(int) * 8);
        executa_p(identificador, preco);
        break;

      case 'E':
        enc = new_sym_var(sizeof(int) * 8);
        identificador = new_sym_var(sizeof(int) * 8);
        executa_E(enc, identificador);
        break;

      case 'm':
        identificador = new_sym_var(sizeof(int) * 8);
        executa_m(identificador);
        break;

      case 'l':
        executa_l();
        break;

      case 'L':
        enc = new_sym_var(sizeof(int) * 8);
        executa_L(enc);
        break;

    }

    getchar();
  }

  return 0;
}

void executa_a(char descricao[], int preco, int peso, int qtd)
{
  sistema[idp].idp = idp;
  strcpy(sistema[idp].descricao, descricao);
  sistema[idp].preco = preco;
  sistema[idp].peso = peso;
  sistema[idp].qtd = qtd;
  printf("Novo produto %d.\n", idp++);
}

void executa_q(int identificador, int qtd)
{
  if (identificador < idp)
  {
    sistema[identificador].qtd += qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", identificador);
  }

}

void executa_N()
{
  lista_enc[ide].ide = ide;
  lista_enc[ide].peso = 0;
  lista_enc[ide].last = 0;
  printf("Nova encomenda %d.\n", ide++);
}

void executa_A(int enc, int identificador, int qtd)
{
  int i;
  if (enc >= ide)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", identificador, enc);
    return;
  }
  else
  {
    if (identificador >= idp)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", identificador, enc);
      return;
    }
    else
    {
      if (sistema[identificador].qtd < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", identificador, enc);
        return;
      }
      else
      {
        if ((lista_enc[enc].peso + (sistema[identificador].peso * qtd)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", identificador, enc);
          return;
        }
        else
        {
          
        }

      }

    }

  }

  for (i = 0; i < lista_enc[enc].last; i++)
  {
    if (lista_enc[enc].lista_artigos[i].idp == identificador)
    {
      lista_enc[enc].lista_artigos[i].qtd += qtd;
      lista_enc[enc].peso += qtd * sistema[identificador].peso;
      sistema[identificador].qtd -= qtd;
      return;
    }
    else
    {
      
    }

  }

  lista_enc[enc].lista_artigos[lista_enc[enc].last].idp = identificador;
  lista_enc[enc].lista_artigos[lista_enc[enc].last].qtd = qtd;
  lista_enc[enc].peso += qtd * sistema[identificador].peso;
  sistema[identificador].qtd -= qtd;
  lista_enc[enc].last++;
}

void executa_r(int identificador, int qtd)
{
  if (identificador >= idp)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", identificador);
  }
  else
  {
    if (sistema[identificador].qtd < qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, identificador);
    }
    else
    {
      sistema[identificador].qtd -= qtd;
    }

  }

}

void executa_R(int enc, int identificador)
{
  int i;
  int j = lista_enc[enc].last;
  if (enc >= ide)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", identificador, enc);
  }
  else
  {
    if (identificador >= idp)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", identificador, enc);
    }
    else
    {
      for (i = 0; i < lista_enc[enc].last; i++)
      {
        if (lista_enc[enc].lista_artigos[i].idp == identificador)
        {
          sistema[identificador].qtd += lista_enc[enc].lista_artigos[i].qtd;
          lista_enc[enc].peso -= sistema[identificador].peso * lista_enc[enc].lista_artigos[i].qtd;
          lista_enc[enc].last--;
          break;
        }
        else
        {
          
        }

      }

      for (; i < (j - 1); i++)
      {
        lista_enc[enc].lista_artigos[i] = lista_enc[enc].lista_artigos[i + 1];
      }

    }

  }

}

void executa_C(int enc)
{
  int i;
  int preco_enc = 0;
  if (enc >= ide)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    for (i = 0; i < lista_enc[enc].last; i++)
      preco_enc += sistema[lista_enc[enc].lista_artigos[i].idp].preco * lista_enc[enc].lista_artigos[i].qtd;

    printf("Custo da encomenda %d %d.\n", enc, preco_enc);
  }

}

void executa_p(int identificador, int preco)
{
  if (identificador >= idp)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", identificador);
  }
  else
  {
    sistema[identificador].preco = preco;
  }

}

void executa_E(int enc, int identificador)
{
  int i;
  if (identificador >= idp)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", identificador);
  }
  else
  {
    if (enc >= ide)
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
    }
    else
    {
      for (i = 0; i < lista_enc[enc].last; i++)
      {
        if (lista_enc[enc].lista_artigos[i].idp == identificador)
        {
          printf("%s %d.\n", sistema[identificador].descricao, lista_enc[enc].lista_artigos[i].qtd);
          return;
        }
        else
        {
          
        }

      }

      printf("%s 0.\n", sistema[identificador].descricao);
    }

  }

}

void executa_m(int identificador)
{
  int max = 0;
  int i;
  int j;
  int max_enc = 0;
  if (identificador >= idp)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", identificador);
    return;
    ;
  }
  else
  {
    for (j = 0; j < ide; j++)
    {
      for (i = 0; i < lista_enc[j].last; i++)
      {
        if ((lista_enc[j].lista_artigos[i].idp == identificador) && (lista_enc[j].lista_artigos[i].qtd > max))
        {
          max = lista_enc[j].lista_artigos[i].qtd;
          max_enc = j;
          break;
        }
        else
        {
          
        }

      }

    }

    if (max == 0)
    {
      return;
    }
    else
    {
      printf("Maximo produto %d %d %d.\n", identificador, max_enc, max);
    }

  }

}

void executa_l()
{
  struct produto desordenado[10000];
  int i;
  for (i = 0; i < idp; i++)
    desordenado[i] = sistema[i];

  quicksort(desordenado, 0, idp - 1);
  printf("Produtos\n");
  for (i = 0; i < idp; i++)
    printf("* %s %d %d\n", desordenado[i].descricao, desordenado[i].preco, desordenado[i].qtd);

}

void executa_L(int enc)
{
  struct artigo desord[200];
  int i;
  if (enc >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    for (i = 0; i < lista_enc[enc].last; i++)
      desord[i] = lista_enc[enc].lista_artigos[i];

    mergesort(desord, 0, lista_enc[enc].last - 1);
    printf("Encomenda %d\n", enc);
    for (i = 0; i < lista_enc[enc].last; i++)
      printf("* %s %d %d\n", sistema[desord[i].idp].descricao, sistema[desord[i].idp].preco, desord[i].qtd);

  }

}

void quicksort(struct produto desordenado[], int left, int right)
{
  int i;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  i = partition(desordenado, left, right);
  quicksort(desordenado, left, i - 1);
  quicksort(desordenado, i + 1, right);
}

int partition(struct produto desordenado[], int left, int right)
{
  int i = left - 1;
  int j = right;
  struct produto pivo = desordenado[right];
  while (i < j)
  {
    while (less(desordenado[++i], pivo))
      ;

    while (less(pivo, desordenado[--j]))
      if (j == left)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      exch(desordenado, i, j);
    }
    else
    {
      
    }

  }

  exch(desordenado, i, right);
  return i;
}

void mergesort(struct artigo desord[], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort(desord, left, m);
  mergesort(desord, m + 1, right);
  merge(desord, left, m, right);
}

void merge(struct artigo desord[], int left, int m, int right)
{
  struct artigo aux[200];
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = desord[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = desord[j + 1];

  for (k = left; k <= right; k++)
    if (less_a(aux[j], aux[i]))
  {
    desord[k] = aux[j--];
  }
  else
  {
    desord[k] = aux[i++];
  }


}

int less(struct produto a, struct produto b)
{
  return ((a.idp < b.idp) && (a.preco == b.preco)) || (a.preco < b.preco);
}

void exch(struct produto desordenado[], int a, int b)
{
  struct produto c = desordenado[b];
  desordenado[b] = desordenado[a];
  desordenado[a] = c;
}

int less_a(struct artigo a, struct artigo b)
{
  return strcmp(sistema[a.idp].descricao, sistema[b.idp].descricao) < 0;
}

