/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int idp;
  char descricao[63 + 1];
  int preco;
  int peso;
  int qtd;
} Produto;
typedef struct 
{
  int prodenc[200];
  int nprodutos;
} Encomenda;
Produto listaprod[10000];
Encomenda listaenc[500];
int prodatuais = 0;
int encatuais = 0;
int varcontrolo;
void addlistaprod();
void addstockprod();
void addenc();
void addprodenc();
void delqtdprod();
void delprodenc();
void calculacusta();
void alterapreco();
void lista_descqtd();
void idppopularide();
void listaprod_preco();
void listaprod_desc();
int existe_prod(int idprod);
int existe_enc(int idenc);
int qtd_suficiente(int idprod, int qtdprod);
int peso_excesso(int idenc, int idprod, int qtdprod);
void produtos_existentes(int vp[]);
void merge(int v[], int l, int mid, int r);
void mergeSort(int v[], int l, int r);
int main()
{
  char comando;
  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      case 'a':
        addlistaprod();
        break;

      case 'q':
        addstockprod();
        break;

      case 'N':
        addenc();
        break;

      case 'A':
        addprodenc();
        break;

      case 'r':
        delqtdprod();
        break;

      case 'R':
        delprodenc();
        break;

      case 'C':
        calculacusta();
        break;

      case 'p':
        alterapreco();
        break;

      case 'E':
        lista_descqtd();
        break;

      case 'm':
        idppopularide();
        break;

      case 'l':
        listaprod_preco();
        break;

      case 'L':
        listaprod_desc();
        break;

      default:
        printf("ERRO: comando desconhecido.\n");
        break;

    }

    getchar();
  }

  return 0;
}

void addlistaprod()
{
  if (prodatuais < 10000)
  {
    {
      for (int listaprod_index = 0; listaprod_index < (63 + 1); listaprod_index++)
      {
        listaprod[prodatuais].descricao[listaprod_index] = new_sym_var(sizeof(char) * 8);
      }

      listaprod[prodatuais].descricao[(63 + 1) - 1] = '\0';
      listaprod[prodatuais].preco = new_sym_var(sizeof(int) * 8);
      listaprod[prodatuais].peso = new_sym_var(sizeof(int) * 8);
      listaprod[prodatuais].qtd = new_sym_var(sizeof(int) * 8);
      listaprod[prodatuais].idp = prodatuais;
      printf("Novo produto %d.\n", prodatuais);
      prodatuais++;
    }
  }
  else
  {
    
  }

}

void addstockprod()
{
  int idprod;
  int qtdprod;
  idprod = new_sym_var(sizeof(int) * 8);
  qtdprod = new_sym_var(sizeof(int) * 8);
  if (!existe_prod(idprod))
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idprod);
      return;
    }
  }
  else
  {
    
  }

  listaprod[idprod].qtd += qtdprod;
}

void addenc()
{
  encatuais++;
  printf("Nova encomenda %d.\n", encatuais - 1);
}

void addprodenc()
{
  int idenc;
  int idprod;
  int qtdprod;
  idenc = new_sym_var(sizeof(int) * 8);
  idprod = new_sym_var(sizeof(int) * 8);
  qtdprod = new_sym_var(sizeof(int) * 8);
  if (!existe_enc(idenc))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idprod, idenc);
      return;
    }
  }
  else
  {
    
  }

  if (!existe_prod(idprod))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idprod, idenc);
      return;
    }
  }
  else
  {
    
  }

  if (!qtd_suficiente(idprod, qtdprod))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idprod, idenc);
      return;
    }
  }
  else
  {
    
  }

  if (!peso_excesso(idenc, idprod, qtdprod))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idprod, idenc);
      return;
    }
  }
  else
  {
    
  }

  while (qtdprod > 0)
  {
    listaenc[idenc].prodenc[listaenc[idenc].nprodutos] = listaprod[idprod].idp;
    listaenc[idenc].nprodutos++;
    listaprod[idprod].qtd--;
    qtdprod--;
  }

}

void delqtdprod()
{
  int idprod;
  int qtdprod;
  idprod = new_sym_var(sizeof(int) * 8);
  qtdprod = new_sym_var(sizeof(int) * 8);
  if (!existe_prod(idprod))
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idprod);
      return;
    }
  }
  else
  {
    
  }

  if (!qtd_suficiente(idprod, qtdprod))
  {
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtdprod, idprod);
      return;
    }
  }
  else
  {
    
  }

  listaprod[idprod].qtd -= qtdprod;
}

void delprodenc()
{
  int idenc;
  int idprod;
  int i;
  idenc = new_sym_var(sizeof(int) * 8);
  idprod = new_sym_var(sizeof(int) * 8);
  if (!existe_enc(idenc))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idprod, idenc);
      return;
    }
  }
  else
  {
    
  }

  if (!existe_prod(idprod))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idprod, idenc);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < listaenc[idenc].nprodutos; i++)
  {
    if (listaenc[idenc].prodenc[i] == idprod)
    {
      {
        listaenc[idenc].prodenc[i] = listaenc[idenc].prodenc[listaenc[idenc].nprodutos - 1];
        listaenc[idenc].nprodutos--;
        listaprod[idprod].qtd++;
        i--;
      }
    }
    else
    {
      
    }

  }

}

void calculacusta()
{
  int idenc;
  int total = 0;
  int i;
  idenc = new_sym_var(sizeof(int) * 8);
  if (!existe_enc(idenc))
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idenc);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < listaenc[idenc].nprodutos; i++)
  {
    total += listaprod[listaenc[idenc].prodenc[i]].preco;
  }

  printf("Custo da encomenda %d %d.\n", idenc, total);
}

void alterapreco()
{
  int idprod;
  int precoprod;
  idprod = new_sym_var(sizeof(int) * 8);
  precoprod = new_sym_var(sizeof(int) * 8);
  if (!existe_prod(idprod))
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idprod);
      return;
    }
  }
  else
  {
    
  }

  listaprod[idprod].preco = precoprod;
}

void lista_descqtd()
{
  int idenc;
  int idprod;
  int i;
  int total = 0;
  idenc = new_sym_var(sizeof(int) * 8);
  idprod = new_sym_var(sizeof(int) * 8);
  if (!existe_enc(idenc))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idenc);
      return;
    }
  }
  else
  {
    
  }

  if (!existe_prod(idprod))
  {
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idprod);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < listaenc[idenc].nprodutos; i++)
  {
    if (listaenc[idenc].prodenc[i] == idprod)
    {
      {
        total++;
      }
    }
    else
    {
      
    }

  }

  printf("%s %d.\n", listaprod[idprod].descricao, total);
}

void idppopularide()
{
  int idprod;
  int enc = 0;
  int max = 0;
  int i;
  int encpopular;
  int contador = 0;
  idprod = new_sym_var(sizeof(int) * 8);
  if (!existe_prod(idprod))
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idprod);
      return;
    }
  }
  else
  {
    
  }

  while (enc <= encatuais)
  {
    for (i = 0; i < listaenc[enc].nprodutos; i++)
    {
      if (listaenc[enc].prodenc[i] == idprod)
      {
        {
          contador++;
        }
      }
      else
      {
        
      }

    }

    if (contador > max)
    {
      {
        max = contador;
        encpopular = enc;
      }
    }
    else
    {
      
    }

    contador = 0;
    enc++;
  }

  if (max > 0)
  {
    {
      printf("Maximo produto %d %d %d.\n", idprod, encpopular, max);
    }
  }
  else
  {
    
  }

}

void listaprod_preco()
{
  int vp[10000];
  int i;
  varcontrolo = 0;
  produtos_existentes(vp);
  mergeSort(vp, 0, prodatuais - 1);
  printf("Produtos\n");
  for (i = 0; i < prodatuais; i++)
  {
    printf("* %s %d %d\n", listaprod[vp[i]].descricao, listaprod[vp[i]].preco, listaprod[vp[i]].qtd);
  }

}

void listaprod_desc()
{
  int idenc;
  int i;
  int qtdprod = 1;
  varcontrolo = 1;
  idenc = new_sym_var(sizeof(int) * 8);
  if (!existe_enc(idenc))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idenc);
      return;
    }
  }
  else
  {
    
  }

  mergeSort(listaenc[idenc].prodenc, 0, listaenc[idenc].nprodutos - 1);
  printf("Encomenda %d\n", idenc);
  for (i = 0; i < listaenc[idenc].nprodutos; i++)
  {
    if (i == (listaenc[idenc].nprodutos - 1))
    {
      {
        printf("* %s %d %d\n", listaprod[listaenc[idenc].prodenc[i]].descricao, listaprod[listaenc[idenc].prodenc[i]].preco, qtdprod);
        return;
      }
    }
    else
    {
      
    }

    if (listaenc[idenc].prodenc[i] == listaenc[idenc].prodenc[i + 1])
    {
      {
        qtdprod++;
        continue;
      }
    }
    else
    {
      
    }

    printf("* %s %d %d\n", listaprod[listaenc[idenc].prodenc[i]].descricao, listaprod[listaenc[idenc].prodenc[i]].preco, qtdprod);
    qtdprod = 1;
  }

}

int existe_prod(int idprod)
{
  if (idprod >= prodatuais)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  return 1;
}

int existe_enc(int idenc)
{
  if (idenc >= encatuais)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  return 1;
}

int qtd_suficiente(int idprod, int qtdprod)
{
  if (listaprod[idprod].qtd < qtdprod)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  return 1;
}

int peso_excesso(int idenc, int idprod, int qtdprod)
{
  int i;
  int pesonaenc = 0;
  for (i = 0; i < listaenc[idenc].nprodutos; i++)
  {
    pesonaenc += listaprod[listaenc[idenc].prodenc[i]].peso;
  }

  if ((pesonaenc + (listaprod[idprod].peso * qtdprod)) > 200)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  return 1;
}

void produtos_existentes(int vp[])
{
  int i;
  for (i = 0; i < prodatuais; i++)
  {
    vp[i] = listaprod[i].idp;
  }

}

void merge(int v[], int l, int mid, int r)
{
  int i;
  int j;
  int k;
  int n1 = 0;
  int n2 = 0;
  int L[5001];
  int R[5000];
  n1 = (mid - l) + 1;
  n2 = r - mid;
  for (i = 0; i < n1; i++)
  {
    L[i] = v[l + i];
  }

  for (j = 0; j < n2; j++)
  {
    R[j] = v[(mid + 1) + j];
  }

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    switch (varcontrolo)
    {
      case 0:
        if (listaprod[L[i]].preco <= listaprod[R[j]].preco)
      {
        {
          v[k] = L[i];
          i++;
        }
      }
      else
      {
        {
          v[k] = R[j];
          j++;
        }
      }

        k++;
        break;

      case 1:
        if (strcmp(listaprod[L[i]].descricao, listaprod[R[j]].descricao) <= 0)
      {
        {
          v[k] = L[i];
          i++;
        }
      }
      else
      {
        {
          v[k] = R[j];
          j++;
        }
      }

        k++;
        break;

    }

  }

  while (i < n1)
  {
    v[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    v[k] = R[j];
    j++;
    k++;
  }

}

void mergeSort(int v[], int l, int r)
{
  int mid;
  if (l >= r)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  mid = (l + r) / 2;
  mergeSort(v, l, mid);
  mergeSort(v, mid + 1, r);
  merge(v, l, mid, r);
}

