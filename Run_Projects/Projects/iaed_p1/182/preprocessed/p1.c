/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


int tam_produtos = 0;
int tam_encomendas = 0;
typedef struct produto
{
  int identificador;
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
} produto;
typedef struct encomenda
{
  int ident;
  int peso;
  int len;
  int produto_id[200];
  int produto_quantidade[200];
} encomenda;
void insertionSort_L(produto vetor[], int left, int right)
{
  int i;
  int j;
  for (i = left + 1; i <= right; i++)
  {
    produto v;
    strcpy(v.descricao, vetor[i].descricao);
    v.preco = vetor[i].preco;
    v.quantidade = vetor[i].quantidade;
    j = i - 1;
    while ((j >= left) && (strcmp(v.descricao, vetor[j].descricao) < 0))
    {
      strcpy(vetor[j + 1].descricao, vetor[j].descricao);
      vetor[j + 1].preco = vetor[j].preco;
      vetor[j + 1].quantidade = vetor[j].quantidade;
      j--;
    }

    vetor[j + 1].preco = v.preco;
    strcpy(vetor[j + 1].descricao, v.descricao);
    vetor[j + 1].quantidade = v.quantidade;
  }

}

void merge(produto arr[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  produto L[10000];
  produto R[10000];
  for (i = 0; i < n1; i++)
  {
    strcpy(L[i].descricao, arr[l + i].descricao);
    L[i].preco = arr[l + i].preco;
    L[i].quantidade = arr[l + i].quantidade;
  }

  for (j = 0; j < n2; j++)
  {
    strcpy(R[j].descricao, arr[(m + 1) + j].descricao);
    R[j].preco = arr[(m + 1) + j].preco;
    R[j].quantidade = arr[(m + 1) + j].quantidade;
  }

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (L[i].preco <= R[j].preco)
    {
      strcpy(arr[k].descricao, L[i].descricao);
      arr[k].preco = L[i].preco;
      arr[k].quantidade = L[i].quantidade;
      i++;
    }
    else
    {
      strcpy(arr[k].descricao, R[j].descricao);
      arr[k].preco = R[j].preco;
      arr[k].quantidade = R[j].quantidade;
      j++;
    }

    k++;
  }

  while (i < n1)
  {
    strcpy(arr[k].descricao, L[i].descricao);
    arr[k].preco = L[i].preco;
    arr[k].quantidade = L[i].quantidade;
    i++;
    k++;
  }

  while (j < n2)
  {
    strcpy(arr[k].descricao, R[j].descricao);
    arr[k].preco = R[j].preco;
    arr[k].quantidade = R[j].quantidade;
    j++;
    k++;
  }

}

void mergeSort(produto arr[], int l, int r)
{
  int m;
  if (l < r)
  {
    m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
  else
  {
    
  }

}

void a(produto v[])
{
  for (int v_index = 0; v_index < 10; v_index++)
  {
    v[tam_produtos].descricao[v_index] = new_sym_var(sizeof(char) * 8);
  }

  v[tam_produtos].descricao[10 - 1] = '\0';
  v[tam_produtos].preco = new_sym_var(sizeof(int) * 8);
  v[tam_produtos].peso = new_sym_var(sizeof(int) * 8);
  v[tam_produtos].quantidade = new_sym_var(sizeof(int) * 8);
  v[tam_produtos].identificador = tam_produtos;
  printf("Novo produto %d.\n", v[tam_produtos].identificador);
  tam_produtos = tam_produtos + 1;
}

void q(produto v[])
{
  int idp;
  int qtd;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < tam_produtos; i++)
  {
    if (v[i].identificador == idp)
    {
      v[i].quantidade += qtd;
      return;
    }
    else
    {
      
    }

  }

  if (i == tam_produtos)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

}

void N(encomenda v[])
{
  encomenda e;
  e.ident = tam_encomendas;
  e.peso = 0;
  e.len = 0;
  v[tam_encomendas] = e;
  printf("Nova encomenda %d.\n", e.ident);
  tam_encomendas = tam_encomendas + 1;
}

void A(encomenda v[], produto u[])
{
  int ide;
  int idp;
  int qtd;
  int i;
  int j;
  int k;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  for (k = 0; k < tam_encomendas; k++)
  {
    if (v[k].ident == ide)
    {
      break;
    }
    else
    {
      
    }

  }

  if (k == tam_encomendas)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < tam_produtos; i++)
  {
    if (u[i].identificador == idp)
    {
      if ((u[i].quantidade - qtd) >= 0)
      {
        u[i].quantidade = u[i].quantidade - qtd;
        break;
      }
      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
      }

    }
    else
    {
      
    }

  }

  if (i == tam_produtos)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  for (j = 0; j < v[k].len; j++)
  {
    if ((v[k].produto_id[j] == idp) && ((v[k].peso + (u[i].peso * qtd)) <= 200))
    {
      v[k].produto_quantidade[j] += qtd;
      v[k].peso = v[k].peso + (u[i].peso * qtd);
      return;
    }
    else
    {
      
    }

    if ((v[k].produto_id[j] == idp) && ((v[k].peso + (u[i].peso * qtd)) > 200))
    {
      u[i].quantidade = u[i].quantidade + qtd;
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
      return;
    }
    else
    {
      
    }

  }

  if ((v[k].peso + (u[i].peso * qtd)) <= 200)
  {
    v[k].produto_id[j] = idp;
    v[k].produto_quantidade[j] = qtd;
    v[k].len = v[k].len + 1;
    v[k].peso = v[k].peso + (u[i].peso * qtd);
    return;
  }
  else
  {
    u[i].quantidade = u[i].quantidade + qtd;
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    return;
  }

}

void r(produto v[])
{
  int qtd;
  int idp;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < tam_produtos; i++)
  {
    if (v[i].identificador == idp)
    {
      if ((v[i].quantidade - qtd) >= 0)
      {
        v[i].quantidade = v[i].quantidade - qtd;
        return;
      }
      else
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
      }

    }
    else
    {
      
    }

  }

  if (i == tam_produtos)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

}

void R(encomenda v[], produto u[])
{
  int ide;
  int idp;
  int i;
  int k;
  int x;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < tam_encomendas; i++)
  {
    if (v[i].ident == ide)
    {
      break;
    }
    else
    {
      
    }

  }

  if (i == tam_encomendas)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  for (x = 0; x < v[i].len; x++)
  {
    if (v[i].produto_id[x] == idp)
    {
      v[i].peso = v[i].peso - (v[i].produto_quantidade[x] * u[idp].peso);
      break;
    }
    else
    {
      
    }

  }

  for (k = 0; k < tam_produtos; k++)
  {
    if (u[k].identificador == idp)
    {
      u[k].quantidade = u[k].quantidade + v[i].produto_quantidade[x];
      break;
    }
    else
    {
      
    }

  }

  if (k == tam_produtos)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  v[i].produto_quantidade[x] = 0;
}

void C(encomenda v[], produto u[])
{
  int ide;
  int i;
  int j;
  int total = 0;
  ide = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < tam_encomendas; i++)
  {
    if (v[i].ident == ide)
    {
      break;
    }
    else
    {
      
    }

  }

  if (i == tam_encomendas)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (j = 0; j < v[i].len; j++)
  {
    total += v[i].produto_quantidade[j] * u[v[i].produto_id[j]].preco;
  }

  printf("Custo da encomenda %d %d.\n", ide, total);
  return;
}

void p(produto v[])
{
  int idp;
  int preco;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < tam_produtos; i++)
  {
    if (v[i].identificador == idp)
    {
      v[i].preco = preco;
      return;
    }
    else
    {
      
    }

  }

  if (i == tam_produtos)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

}

void E(encomenda v[], produto u[])
{
  int ide;
  int idp;
  int i;
  int j;
  int k;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < tam_encomendas; i++)
  {
    if (v[i].ident == ide)
    {
      break;
    }
    else
    {
      
    }

  }

  if (i == tam_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (k = 0; k < tam_produtos; k++)
  {
    if (u[k].identificador == idp)
    {
      break;
    }
    else
    {
      
    }

  }

  if (k == tam_produtos)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  for (j = 0; j < v[i].len; j++)
  {
    if (v[i].produto_id[j] == idp)
    {
      printf("%s %d.\n", u[k].descricao, v[i].produto_quantidade[j]);
      return;
    }
    else
    {
      
    }

  }

  printf("%s %d.\n", u[k].descricao, 0);
}

void m(encomenda v[], produto u[])
{
  int idp;
  int i;
  int j;
  int k;
  int ident_min = 0;
  int quantidade = 0;
  idp = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < tam_produtos; i++)
  {
    if (u[i].identificador == idp)
    {
      break;
    }
    else
    {
      
    }

  }

  if (i == tam_produtos)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  if (tam_encomendas == 0)
  {
    return;
  }
  else
  {
    
  }

  for (j = 0; j < tam_encomendas; j++)
  {
    for (k = 0; k < v[j].len; k++)
    {
      if (v[j].produto_id[k] == idp)
      {
        if (v[j].produto_quantidade[k] > quantidade)
        {
          ident_min = v[j].ident;
          quantidade = v[j].produto_quantidade[k];
        }
        else
        {
          
        }

        if ((v[j].produto_quantidade[k] == quantidade) && (v[j].ident < ident_min))
        {
          ident_min = v[j].ident;
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

  if ((j == tam_encomendas) && (quantidade == 0))
  {
    return;
  }
  else
  {
    
  }

  printf("Maximo produto %d %d %d.\n", idp, ident_min, quantidade);
  return;
}

void l(produto v[])
{
  produto auxiliar[10000];
  int i;
  int b;
  for (i = 0; i < tam_produtos; i++)
  {
    strcpy(auxiliar[i].descricao, v[i].descricao);
    auxiliar[i].preco = v[i].preco;
    auxiliar[i].quantidade = v[i].quantidade;
  }

  mergeSort(auxiliar, 0, tam_produtos - 1);
  printf("Produtos\n");
  for (b = 0; b < tam_produtos; b++)
  {
    printf("* %s %d %d\n", auxiliar[b].descricao, auxiliar[b].preco, auxiliar[b].quantidade);
  }

}

void L(encomenda v[], produto b[])
{
  int ide;
  int k;
  int a;
  int i;
  int j;
  produto aux[10000];
  ide = new_sym_var(sizeof(int) * 8);
  for (k = 0; k < tam_encomendas; k++)
  {
    if (v[k].ident == ide)
    {
      break;
    }
    else
    {
      
    }

  }

  if (k == tam_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < v[k].len; i++)
  {
    for (j = 0; j < tam_produtos; j++)
    {
      if (v[k].produto_id[i] == b[j].identificador)
      {
        strcpy(aux[i].descricao, b[j].descricao);
        aux[i].preco = b[j].preco;
        aux[i].quantidade = v[k].produto_quantidade[i];
      }
      else
      {
        
      }

    }

  }

  insertionSort_L(aux, 0, v[k].len - 1);
  printf("Encomenda %d\n", ide);
  for (a = 0; a < v[k].len; a++)
  {
    if (aux[a].quantidade > 0)
    {
      printf("* %s %d %d\n", aux[a].descricao, aux[a].preco, aux[a].quantidade);
    }
    else
    {
      
    }

  }

}

int main()
{
  char c;
  produto sistema[10000];
  encomenda sistema_encomendas[500];
  c = getchar();
  while (c != 'x')
  {
    switch (c)
    {
      case 'a':
        a(sistema);
        break;

      case 'q':
        q(sistema);
        break;

      case 'N':
        N(sistema_encomendas);
        break;

      case 'A':
        A(sistema_encomendas, sistema);
        break;

      case 'r':
        r(sistema);
        break;

      case 'R':
        R(sistema_encomendas, sistema);
        break;

      case 'C':
        C(sistema_encomendas, sistema);
        break;

      case 'p':
        p(sistema);
        break;

      case 'E':
        E(sistema_encomendas, sistema);
        break;

      case 'm':
        m(sistema_encomendas, sistema);
        break;

      case 'l':
        l(sistema);
        break;

      case 'L':
        L(sistema_encomendas, sistema);
        break;

    }

    c = getchar();
  }

  return 0;
}

