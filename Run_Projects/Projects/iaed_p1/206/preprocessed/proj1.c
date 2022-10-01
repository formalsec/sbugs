/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  int preco;
  int peso;
  int qtd;
  int idp;
  char descricao[63];
} Produto;
typedef struct simpProdEnc
{
  int idp;
  int qtd;
} SimpProd;
typedef struct encomenda
{
  SimpProd lstSimpProd[200];
  int pesoTotalEnc;
  int qtdprodutos;
} Encomenda;
signed int contadorProdutos = 0;
signed int contadorEncomendas = 0;
char str[100];
Produto lstProdutos[10000];
Encomenda lstEncomendas[500];
void a();
void l();
void N();
int A();
int L();
int C();
int p();
int r();
int R();
int m();
int q();
int E();
int main()
{
  while (1)
  {
    int c;
    int i2;
    for (i2 = 0; ((i2 < (100 - 1)) && ((c = getchar()) != EOF)) && (c != '\n'); i2++)
    {
      str[i2] = c;
    }

    str[i2] = '\0';
    switch (str[0])
    {
      case 'a':
        a();
        break;

      case 'l':
        l();
        break;

      case 'N':
        N();
        break;

      case 'L':
        L();
        break;

      case 'C':
        C();
        break;

      case 'A':
        A();
        break;

      case 'p':
        p();
        break;

      case 'r':
        r();
        break;

      case 'R':
        R();
        break;

      case 'm':
        m();
        break;

      case 'q':
        q();
        break;

      case 'E':
        E();
        break;

      case 'x':
        return 0;

    }

  }

}

void ordenarString(int qtd, SimpProd lstOrd[], SimpProd enc[])
{
  int i1;
  int i2;
  int i3;
  int i4;
  char alist[200][63] = {0};
  char key[63] = {0};
  int keyQt = 0;
  int keyID = 0;
  for (i3 = 0; i3 < qtd; ++i3)
  {
    lstOrd[i3].idp = enc[i3].idp;
    lstOrd[i3].qtd = enc[i3].qtd;
  }

  for (i4 = 0; i4 < qtd; ++i4)
  {
    strcpy(alist[i4], lstProdutos[enc[i4].idp].descricao);
  }

  for (i1 = 1; i1 < qtd; i1++)
  {
    keyID = lstOrd[i1].idp;
    keyQt = lstOrd[i1].qtd;
    strcpy(key, alist[i1]);
    i2 = i1 - 1;
    while ((i2 >= 0) && (strcmp(alist[i2], key) > 0))
    {
      lstOrd[i2 + 1].idp = lstOrd[i2].idp;
      lstOrd[i2 + 1].qtd = lstOrd[i2].qtd;
      strcpy(alist[i2 + 1], alist[i2]);
      i2 = i2 - 1;
    }

    strcpy(alist[i2 + 1], key);
    lstOrd[i2 + 1].idp = keyID;
    lstOrd[i2 + 1].qtd = keyQt;
  }

}

void copiarLstProdutos(Produto source[], Produto dest[])
{
  int i;
  for (i = 0; i < contadorProdutos; i++)
  {
    dest[i].preco = source[i].preco;
    dest[i].qtd = source[i].qtd;
    dest[i].peso = source[i].peso;
    dest[i].idp = source[i].idp;
    strcpy(dest[i].descricao, source[i].descricao);
  }

}

void merge(Produto arr[], int l, int m, int r)
{
  int i1;
  int i2;
  int i3;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  Produto L[10000 / 2];
  Produto R[10000 / 2];
  for (i1 = 0; i1 < n1; i1++)
    L[i1] = arr[l + i1];

  for (i2 = 0; i2 < n2; i2++)
    R[i2] = arr[(m + 1) + i2];

  i1 = 0;
  i2 = 0;
  i3 = l;
  while ((i1 < n1) && (i2 < n2))
  {
    if (L[i1].preco <= R[i2].preco)
    {
      arr[i3] = L[i1];
      i1++;
    }
    else
    {
      arr[i3] = R[i2];
      i2++;
    }

    i3++;
  }

  while (i1 < n1)
  {
    arr[i3] = L[i1];
    i1++;
    i3++;
  }

  while (i2 < n2)
  {
    arr[i3] = R[i2];
    i2++;
    i3++;
  }

}

void mergeSort(Produto arr[], int l, int r)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
  else
  {
    
  }

}

int encontrarPosicao(int idpPedido, int idePedido)
{
  int pos = 0;
  int i;
  for (i = 0; i < lstEncomendas[idePedido].qtdprodutos; ++i)
  {
    if (lstEncomendas[idePedido].lstSimpProd[i].idp == idpPedido)
    {
      pos = i;
      return pos;
    }
    else
    {
      
    }

  }

  return -1;
}

void a()
{
  for (int lstProdutos_index = 0; lstProdutos_index < 10; lstProdutos_index++)
  {
    lstProdutos[contadorProdutos].descricao[lstProdutos_index] = new_sym_var(sizeof(char) * 8);
  }

  lstProdutos[contadorProdutos].descricao[10 - 1] = '\0';
  lstProdutos[contadorProdutos].preco = new_sym_var(sizeof(int) * 8);
  lstProdutos[contadorProdutos].peso = new_sym_var(sizeof(int) * 8);
  lstProdutos[contadorProdutos].qtd = new_sym_var(sizeof(int) * 8);
  lstProdutos[contadorProdutos].idp = contadorProdutos;
  printf("%s %d%s\n", "Novo produto", contadorProdutos, ".");
  contadorProdutos = contadorProdutos + 1;
}

void l()
{
  int i;
  Produto novoV[10000];
  copiarLstProdutos(lstProdutos, novoV);
  mergeSort(novoV, 0, contadorProdutos - 1);
  printf("%s\n", "Produtos");
  for (i = 0; i < contadorProdutos; ++i)
  {
    printf("%c %s %d %d\n", '*', novoV[i].descricao, novoV[i].preco, novoV[i].qtd);
  }

}

void N()
{
  printf("%s %d%s\n", "Nova encomenda", contadorEncomendas, ".");
  contadorEncomendas++;
}

int A()
{
  int idePedido = 0;
  int idpPedido = 0;
  int qtdPedida = 0;
  int i1 = 0;
  idePedido = new_sym_var(sizeof(int) * 8);
  idpPedido = new_sym_var(sizeof(int) * 8);
  qtdPedida = new_sym_var(sizeof(int) * 8);
  if (idePedido > (contadorEncomendas - 1))
  {
    printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idpPedido, "a encomenda", idePedido, ". Encomenda inexistente.");
    return 0;
  }
  else
  {
    
  }

  if (idpPedido > (contadorProdutos - 1))
  {
    printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idpPedido, "a encomenda", idePedido, ". Produto inexistente.");
    return 0;
  }
  else
  {
    
  }

  if (qtdPedida > lstProdutos[idpPedido].qtd)
  {
    printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idpPedido, "a encomenda", idePedido, ". Quantidade em stock insuficiente.");
    return 0;
  }
  else
  {
    
  }

  if ((lstEncomendas[idePedido].pesoTotalEnc + (qtdPedida * lstProdutos[idpPedido].peso)) > 200)
  {
    printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idpPedido, "a encomenda", idePedido, ". Peso da encomenda excede o maximo de 200.");
    return 0;
  }
  else
  {
    
  }

  for (i1 = 0; i1 < lstEncomendas[idePedido].qtdprodutos; ++i1)
  {
    if (lstEncomendas[idePedido].lstSimpProd[i1].idp == idpPedido)
    {
      lstEncomendas[idePedido].lstSimpProd[i1].qtd += qtdPedida;
      lstProdutos[idpPedido].qtd -= qtdPedida;
      lstEncomendas[idePedido].pesoTotalEnc += lstProdutos[idpPedido].peso * qtdPedida;
      return 0;
    }
    else
    {
      
    }

  }

  lstEncomendas[idePedido].lstSimpProd[lstEncomendas[idePedido].qtdprodutos].idp = idpPedido;
  lstProdutos[idpPedido].qtd -= qtdPedida;
  lstEncomendas[idePedido].lstSimpProd[lstEncomendas[idePedido].qtdprodutos].qtd = qtdPedida;
  lstEncomendas[idePedido].pesoTotalEnc += lstProdutos[idpPedido].peso * qtdPedida;
  lstEncomendas[idePedido].qtdprodutos++;
  return 0;
}

int L()
{
  int idePedido = 0;
  int i;
  SimpProd lstSProdOrd[200] = {0};
  idePedido = new_sym_var(sizeof(int) * 8);
  if (idePedido > (contadorEncomendas - 1))
  {
    printf("%s %d%s\n", "Impossivel listar encomenda", idePedido, ". Encomenda inexistente.");
    return 0;
  }
  else
  {
    
  }

  ordenarString(lstEncomendas[idePedido].qtdprodutos, lstSProdOrd, lstEncomendas[idePedido].lstSimpProd);
  printf("%s %d\n", "Encomenda", idePedido);
  for (i = 0; i < lstEncomendas[idePedido].qtdprodutos; ++i)
  {
    printf("%c %s %d %d\n", '*', lstProdutos[lstSProdOrd[i].idp].descricao, lstProdutos[lstSProdOrd[i].idp].preco, lstSProdOrd[i].qtd);
  }

  return 0;
}

int C()
{
  int idePedido = 0;
  int total = 0;
  int i;
  idePedido = new_sym_var(sizeof(int) * 8);
  if (idePedido > (contadorEncomendas - 1))
  {
    printf("%s%d%s\n", "Impossivel calcular custo da encomenda ", idePedido, ". Encomenda inexistente.");
    return 0;
  }
  else
  {
    
  }

  for (i = 0; i < lstEncomendas[idePedido].qtdprodutos; ++i)
  {
    total += lstProdutos[lstEncomendas[idePedido].lstSimpProd[i].idp].preco * lstEncomendas[idePedido].lstSimpProd[i].qtd;
  }

  printf("%s %d %d%c\n", "Custo da encomenda", idePedido, total, '.');
  return 0;
}

int p()
{
  int idpPedido;
  int preco;
  idpPedido = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idpPedido > (contadorProdutos - 1))
  {
    printf("%s%d%s\n", "Impossivel alterar preco do produto ", idpPedido, ". Produto inexistente.");
    return 0;
  }
  else
  {
    
  }

  lstProdutos[idpPedido].preco = preco;
  return 0;
}

int r()
{
  int idpPedido;
  int qtd;
  idpPedido = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idpPedido > (contadorProdutos - 1))
  {
    printf("%s %d%s\n", "Impossivel remover stock do produto", idpPedido, ". Produto inexistente.");
    return 0;
  }
  else
  {
    
  }

  if (qtd > lstProdutos[idpPedido].qtd)
  {
    printf("%s %d %s %d %s\n", "Impossivel remover", qtd, "unidades do produto", idpPedido, "do stock. Quantidade insuficiente.");
    return 0;
  }
  else
  {
    
  }

  lstProdutos[idpPedido].qtd -= qtd;
  return 0;
}

int R()
{
  int idpPedido;
  int idePedido;
  int pos = 0;
  int i2;
  idePedido = new_sym_var(sizeof(int) * 8);
  idpPedido = new_sym_var(sizeof(int) * 8);
  if (idePedido > (contadorEncomendas - 1))
  {
    printf("%s %d %s %d%s\n", "Impossivel remover produto", idpPedido, "a encomenda", idePedido, ". Encomenda inexistente.");
    return 0;
  }
  else
  {
    
  }

  if (idpPedido > (contadorProdutos - 1))
  {
    printf("%s %d %s %d%s\n", "Impossivel remover produto", idpPedido, "a encomenda", idePedido, ". Produto inexistente.");
    return 0;
  }
  else
  {
    
  }

  pos = encontrarPosicao(idpPedido, idePedido);
  if (pos != (-1))
  {
    lstEncomendas[idePedido].pesoTotalEnc -= lstProdutos[idpPedido].peso * lstEncomendas[idePedido].lstSimpProd[pos].qtd;
    lstProdutos[idpPedido].qtd += lstEncomendas[idePedido].lstSimpProd[pos].qtd;
    for (i2 = pos; i2 < lstEncomendas[idePedido].qtdprodutos; ++i2)
    {
      lstEncomendas[idePedido].lstSimpProd[i2] = lstEncomendas[idePedido].lstSimpProd[i2 + 1];
      lstEncomendas[idePedido].lstSimpProd[i2 + 1].idp = 0;
      lstEncomendas[idePedido].lstSimpProd[i2 + 1].qtd = 0;
    }

    lstEncomendas[idePedido].qtdprodutos -= 1;
    return 0;
  }
  else
  {
    
  }

  return 0;
}

int m()
{
  int idpPedido;
  int ideKey = -1;
  int qtdKey = 0;
  int pos = 0;
  int i1;
  idpPedido = new_sym_var(sizeof(int) * 8);
  if (contadorEncomendas == 0)
  {
    return 0;
  }
  else
  {
    
  }

  if (idpPedido > (contadorProdutos - 1))
  {
    printf("%s %d%s\n", "Impossivel listar maximo do produto", idpPedido, ". Produto inexistente.");
    return 0;
  }
  else
  {
    
  }

  for (i1 = 0; i1 < contadorEncomendas; ++i1)
  {
    pos = encontrarPosicao(idpPedido, i1);
    if ((pos > (-1)) && (lstEncomendas[i1].lstSimpProd[pos].qtd > qtdKey))
    {
      qtdKey = lstEncomendas[i1].lstSimpProd[pos].qtd;
      ideKey = i1;
    }
    else
    {
      
    }

  }

  if (ideKey == (-1))
  {
    return 0;
  }
  else
  {
    printf("%s %d %d %d%c\n", "Maximo produto", idpPedido, ideKey, qtdKey, '.');
    return 0;
  }

}

int q()
{
  int idpPedido;
  int qtdAd;
  idpPedido = new_sym_var(sizeof(int) * 8);
  qtdAd = new_sym_var(sizeof(int) * 8);
  if (idpPedido > (contadorProdutos - 1))
  {
    printf("%s %d %s\n", "Impossivel adicionar produto", idpPedido, "ao stock. Produto inexistente.");
    return 0;
  }
  else
  {
    
  }

  lstProdutos[idpPedido].qtd += qtdAd;
  return 0;
}

int E()
{
  int idePedido;
  int idpPedido;
  int pos = 0;
  idePedido = new_sym_var(sizeof(int) * 8);
  idpPedido = new_sym_var(sizeof(int) * 8);
  if (idePedido > (contadorEncomendas - 1))
  {
    printf("%s %d%s\n", "Impossivel listar encomenda", idePedido, ". Encomenda inexistente.");
    return 0;
  }
  else
  {
    
  }

  if (idpPedido > (contadorProdutos - 1))
  {
    printf("%s %d%s\n", "Impossivel listar produto", idpPedido, ". Produto inexistente.");
    return 0;
  }
  else
  {
    
  }

  pos = encontrarPosicao(idpPedido, idePedido);
  if (pos != (-1))
  {
    printf("%s %d%c\n", lstProdutos[idpPedido].descricao, lstEncomendas[idePedido].lstSimpProd[pos].qtd, '.');
    return 0;
  }
  else
  {
    printf("%s %d%c\n", lstProdutos[idpPedido].descricao, 0, '.');
    return 0;
  }

}
