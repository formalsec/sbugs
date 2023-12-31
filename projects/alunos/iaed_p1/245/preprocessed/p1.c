#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "p1.h"


int main()
{
  char comando;
  char parametros[100];
  do
  {
    comando = getchar();
    fgets(parametros, 100, stdin);
    switch (comando)
    {
      case 'a':
        comando_a(parametros);
        break;

      case 'q':
        comando_q(parametros);
        break;

      case 'N':
        comando_N();
        break;

      case 'A':
        comando_A(parametros);
        break;

      case 'r':
        comando_r(parametros);
        break;

      case 'R':
        comando_R(parametros);
        break;

      case 'C':
        comando_C(parametros);
        break;

      case 'p':
        comando_p(parametros);
        break;

      case 'E':
        comando_E(parametros);
        break;

      case 'm':
        comando_m(parametros);
        break;

      case 'l':
        comando_l();
        break;

      case 'L':
        comando_L(parametros);
        break;

    }

  }
  while (comando != 'x');
  return 0;
}

void separaInput(char arg[100], char res[][100])
{
  int i = 0;
  char *token;
  char delim[3];
  strcpy(delim, ":");
  token = strtok(arg, delim);
  while (token != 0)
  {
    strcpy(res[i], token);
    token = strtok(0, delim);
    i++;
  }

}

void removeEspaco(char *str)
{
  int i;
  int cont = 0;
  for (i = 0; str[i]; i++)
    if (str[i] != ' ')
  {
    str[cont++] = str[i];
  }
  else
  {
    
  }


  str[cont] = '\0';
}

void comando_a(char arg[])
{
  char inputSeparado[4][100];
  separaInput(arg, inputSeparado);
  removeEspaco(inputSeparado[0]);
  strcpy(produtos[contaProdutos].descricao, inputSeparado[0]);
  produtos[contaProdutos].preco = atoi(inputSeparado[1]);
  produtos[contaProdutos].peso = atoi(inputSeparado[2]);
  produtos[contaProdutos].stock = atoi(inputSeparado[3]);
  produtos[contaProdutos].flag = 1;
  printf("Novo produto %d.\n", contaProdutos);
  ++contaProdutos;
}

int comando_q(char arg[])
{
  int idp;
  int qtd;
  char inputSeparado[2][100];
  separaInput(arg, inputSeparado);
  idp = atoi(inputSeparado[0]);
  qtd = atoi(inputSeparado[1]);
  if (produtos[idp].flag == 1)
  {
    produtos[idp].stock = produtos[idp].stock + qtd;
    return 0;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    return -1;
  }

}

void comando_N()
{
  encomendas[contaEncomendas].flag = 1;
  printf("Nova encomenda %d.\n", contaEncomendas);
  ++contaEncomendas;
}

int comando_A(char arg[])
{
  int ide;
  int idp;
  int qtd;
  char inputSeparado[3][100];
  separaInput(arg, inputSeparado);
  ide = atoi(inputSeparado[0]);
  idp = atoi(inputSeparado[1]);
  qtd = atoi(inputSeparado[2]);
  if (encomendas[ide].flag == 1)
  {
    if (produtos[idp].flag == 1)
    {
      if ((produtos[idp].stock - qtd) >= 0)
      {
        if ((encomendas[ide].peso + (qtd * produtos[idp].peso)) <= 200)
        {
          encomendas[ide].produtosEncomendas[idp] = produtos[idp];
          produtos[idp].stock = produtos[idp].stock - qtd;
          encomendas[ide].peso = encomendas[ide].peso + (qtd * produtos[idp].peso);
          encomendas[ide].quantidade[idp] = encomendas[ide].quantidade[idp] + qtd;
          encomendas[ide].contaProdEnc++;
          return 0;
        }
        else
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
          return -1;
        }

      }
      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return -1;
      }

    }
    else
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return -1;
    }

  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return -1;
  }

}

int comando_r(char arg[])
{
  int idp;
  int qtd;
  char inputSeparado[2][100];
  separaInput(arg, inputSeparado);
  idp = atoi(inputSeparado[0]);
  qtd = atoi(inputSeparado[1]);
  if (produtos[idp].flag == 1)
  {
    if ((produtos[idp].stock - qtd) >= 0)
    {
      produtos[idp].stock = produtos[idp].stock - qtd;
    }
    else
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
      return -1;
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    return -1;
  }

  return -1;
}

int comando_R(char arg[])
{
  int ide;
  int idp;
  char inputSeparado[2][100];
  separaInput(arg, inputSeparado);
  ide = atoi(inputSeparado[0]);
  idp = atoi(inputSeparado[1]);
  if (encomendas[ide].flag == 1)
  {
    if (produtos[idp].flag == 1)
    {
      if (encomendas[ide].produtosEncomendas[idp].flag == 1)
      {
        encomendas[ide].contaProdEnc = encomendas[ide].contaProdEnc - 1;
      }
      else
      {
        
      }

      encomendas[ide].peso = encomendas[ide].peso - (encomendas[ide].quantidade[idp] * produtos[idp].peso);
      produtos[idp].stock = produtos[idp].stock + encomendas[ide].quantidade[idp];
      encomendas[ide].produtosEncomendas[idp].flag = 0;
      strcpy(encomendas[ide].produtosEncomendas[idp].descricao, "vazio");
      encomendas[ide].quantidade[idp] = 0;
      return 0;
    }
    else
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return -1;
    }

  }
  else
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return -1;
  }

  return -1;
}

int comando_C(char arg[])
{
  int i;
  int ide;
  int total = 0;
  char inputSeparado[1][100];
  separaInput(arg, inputSeparado);
  ide = atoi(inputSeparado[0]);
  if (encomendas[ide].flag == 1)
  {
    for (i = 0; i <= (contaProdutos - 1); i++)
    {
      if (encomendas[ide].produtosEncomendas[i].flag == 1)
      {
        total = total + (produtos[i].preco * encomendas[ide].quantidade[i]);
      }
      else
      {
        
      }

    }

    printf("Custo da encomenda %d %d.\n", ide, total);
    return 0;
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return -1;
  }

  return -1;
}

int comando_p(char arg[])
{
  int idp;
  int preco;
  char inputSeparado[2][100];
  separaInput(arg, inputSeparado);
  idp = atoi(inputSeparado[0]);
  preco = atoi(inputSeparado[1]);
  if (produtos[idp].flag == 1)
  {
    produtos[idp].preco = preco;
    return 0;
  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    return -1;
  }

  return -1;
}

int comando_E(char arg[])
{
  int ide;
  int idp;
  char inputSeparado[2][100];
  separaInput(arg, inputSeparado);
  ide = atoi(inputSeparado[0]);
  idp = atoi(inputSeparado[1]);
  if (encomendas[ide].flag == 1)
  {
    if (produtos[idp].flag == 1)
    {
      printf("%s %d.\n", produtos[idp].descricao, encomendas[ide].quantidade[idp]);
      return 0;
    }
    else
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      return -1;
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return -1;
  }

  return -1;
}

int comando_m(char arg[])
{
  int i;
  int idp;
  int idFinal = -1;
  int qtdFinal = -1;
  int qtd = -1;
  char inputSeparado[1][100];
  separaInput(arg, inputSeparado);
  idp = atoi(inputSeparado[0]);
  if (produtos[idp].flag == 1)
  {
    for (i = 0; i <= (contaEncomendas - 1); i++)
    {
      if (encomendas[i].produtosEncomendas[idp].flag == 1)
      {
        qtd = encomendas[i].quantidade[idp];
        if (qtd > qtdFinal)
        {
          qtdFinal = qtd;
          idFinal = i;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

    if ((contaEncomendas == 0) || (idFinal == (-1)))
    {
      return 0;
    }
    else
    {
      printf("Maximo produto %d %d %d.\n", idp, idFinal, qtdFinal);
      return 0;
    }

  }
  else
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    return -1;
  }

  return -1;
}

void comando_l()
{
  int i;
  int f;
  int l = 1;
  Produto auxl[10000];
  for (i = 0; i <= (contaProdutos - 1); i++)
    auxl[i] = produtos[i];

  mergeSort(auxl, 0, contaProdutos - 1, l);
  printf("Produtos\n");
  for (f = 0; f <= (contaProdutos - 1); f++)
    printf("* %s %d %d\n", auxl[f].descricao, auxl[f].preco, auxl[f].stock);

}

int comando_L(char arg[])
{
  int i;
  int j;
  int k;
  int t;
  int l = 2;
  int ide;
  Produto auxprod[10000];
  char inputSeparado[1][100];
  separaInput(arg, inputSeparado);
  ide = atoi(inputSeparado[0]);
  for (k = 0; k <= (contaProdutos - 1); k++)
  {
    auxprod[k].flag = 0;
    strcpy(auxprod[k].descricao, " ");
  }

  if (encomendas[ide].flag == 1)
  {
    for (i = 0; i <= (contaProdutos - 1); i++)
    {
      if (strcmp(encomendas[ide].produtosEncomendas[i].descricao, produtos[i].descricao) == 0)
      {
        auxprod[i] = produtos[i];
      }
      else
      {
        
      }

    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return -1;
  }

  mergeSort(auxprod, 0, contaProdutos - 1, l);
  printf("Encomenda %d\n", ide);
  for (j = 0; j <= (contaProdutos - 1); j++)
  {
    for (t = 0; t <= (contaProdutos - 1); t++)
    {
      if (encomendas[ide].contaProdEnc > 0)
      {
        if (strcmp(auxprod[j].descricao, encomendas[ide].produtosEncomendas[t].descricao) == 0)
        {
          printf("* %s %d %d\n", auxprod[j].descricao, auxprod[j].preco, encomendas[ide].quantidade[t]);
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

  return 0;
}

void mergeSort(Produto a[], int i, int j, int f)
{
  int mid;
  if (i < j)
  {
    if (f == 1)
    {
      mid = (i + j) / 2;
      mergeSort(a, i, mid, f);
      mergeSort(a, mid + 1, j, f);
      merge(a, i, mid, mid + 1, j, f);
    }
    else
    {
      if (f == 2)
      {
        mid = (i + j) / 2;
        mergeSort(a, i, mid, f);
        mergeSort(a, mid + 1, j, f);
        merge(a, i, mid, mid + 1, j, f);
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

void merge(Produto a[], int i1, int j1, int i2, int j2, int f)
{
  Produto temp[10000];
  int i;
  int j;
  int k;
  i = i1;
  j = i2;
  k = 0;
  if (f == 1)
  {
    while ((i <= j1) && (j <= j2))
    {
      if (a[i].preco < a[j].preco)
      {
        temp[k++] = a[i++];
      }
      else
      {
        if ((a[i].preco == a[j].preco) && (i < j))
        {
          temp[k++] = a[i++];
        }
        else
        {
          temp[k++] = a[j++];
        }

      }

    }

  }
  else
  {
    if (f == 2)
    {
      while ((i <= j1) && (j <= j2))
      {
        if (strcmp(a[i].descricao, a[j].descricao) < 0)
        {
          temp[k++] = a[i++];
        }
        else
        {
          temp[k++] = a[j++];
        }

      }

    }
    else
    {
      
    }

  }

  while (i <= j1)
    temp[k++] = a[i++];

  while (j <= j2)
    temp[k++] = a[j++];

  for (i = i1, j = 0; i <= j2; i++, j++)
    a[i] = temp[j];

}

