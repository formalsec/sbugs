/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct 
{
  char Descricao[64];
  int Preco;
  int Peso;
  int Quantidade;
} produto;
produto stock[9999];
typedef struct 
{
  char Descricao[64];
  int Preco;
  int Peso;
  int Quantidade;
  int Inicia;
} encomenda;
encomenda dataBase[500][200];
int proximoidp()
{
  int i = 0;
  if (strcmp(stock[i].Descricao, "") == 0)
  {
    return i;
  }
  else
  {
    
  }

  while (strcmp(stock[i].Descricao, "") != 0)
  {
    i++;
  }

  return i;
}

int proximoide()
{
  int i = 0;
  while (dataBase[i][0].Inicia != (-1))
  {
    i++;
  }

  return i;
}

int idpEnc(int ide, int idp)
{
  int i;
  for (i = 0; i < 200; i++)
  {
    if ((strcmp(dataBase[ide][i].Descricao, stock[idp].Descricao) == 0) || (dataBase[ide][i].Inicia == (-1)))
    {
      break;
    }
    else
    {
      
    }

  }

  return i;
}

int pesoTotalEnc(int ide)
{
  int i;
  int peso = 0;
  for (i = 0; i < 200; i++)
  {
    peso += dataBase[ide][i].Peso;
  }

  return peso;
}

int separarString(char entrada[64], char armazenado[5][64])
{
  int i;
  char *word = "";
  for (i = 0; i < 5; i++)
  {
    strncpy(armazenado[i], "", 64);
  }

  i = 0;
  word = strtok(entrada, ":");
  while (word != 0)
  {
    strncpy(armazenado[i], word, 64);
    word = strtok(0, ":");
    i++;
  }

  return i;
}

int readLine(char s[])
{
  char c;
  int n = 0;
  while ((((c = getchar()) != EOF) && (c != '\n')) && (c != '\0'))
  {
    s[n] = c;
    n++;
  }

  s[n] = '\0';
  return n;
}

void merge_l(int tab_final[], int start, int mid, int end)
{
  int i;
  int j;
  int k;
  int tab_aux[10000];
  for (i = mid + 1; i > start; i--)
    tab_aux[i - 1] = tab_final[i - 1];

  for (j = mid; j < end; j++)
    tab_aux[(end + mid) - j] = tab_final[j + 1];

  for (k = start; k <= end; k++)
  {
    if ((stock[tab_aux[j]].Preco < stock[tab_aux[i]].Preco) || (i > mid))
    {
      tab_final[k] = tab_aux[j--];
    }
    else
    {
      tab_final[k] = tab_aux[i++];
    }

  }

}

void mergeSort_l(int tab_final[10000], int start, int end)
{
  int mid = (start + end) / 2;
  if (end <= start)
  {
    return;
  }
  else
  {
    
  }

  mergeSort_l(tab_final, start, mid);
  mergeSort_l(tab_final, mid + 1, end);
  merge_l(tab_final, start, mid, end);
}

void merge_L(int tab_final[], int start, int mid, int end, int ide)
{
  int i;
  int j;
  int k;
  int tab_aux[10000];
  for (i = mid + 1; i > start; i--)
    tab_aux[i - 1] = tab_final[i - 1];

  for (j = mid; j < end; j++)
    tab_aux[(end + mid) - j] = tab_final[j + 1];

  for (k = start; k <= end; k++)
  {
    if ((strcmp(dataBase[ide][tab_aux[j]].Descricao, dataBase[ide][tab_aux[i]].Descricao) < 0) || (i > mid))
    {
      tab_final[k] = tab_aux[j--];
    }
    else
    {
      tab_final[k] = tab_aux[i++];
    }

  }

}

void mergeSort_L(int tab_final[10000], int start, int end, int ide)
{
  int mid = (start + end) / 2;
  if (end <= start)
  {
    return;
  }
  else
  {
    
  }

  mergeSort_L(tab_final, start, mid, ide);
  mergeSort_L(tab_final, mid + 1, end, ide);
  merge_L(tab_final, start, mid, end, ide);
}

int novoProd()
{
  int i = proximoidp();
  char args[5][64];
  char s[64];
  readLine(s);
  separarString(s, args);
  strncpy(stock[i].Descricao, args[0], 64);
  stock[i].Preco = atoi(args[1]);
  stock[i].Peso = atoi(args[2]);
  stock[i].Quantidade = atoi(args[3]);
  printf("Novo produto %d.\n", i);
  return 0;
}

int adStock()
{
  int idp;
  char args[5][64];
  char s[64];
  readLine(s);
  separarString(s, args);
  idp = atoi(args[0]);
  if (stock[idp].Peso == 0)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    stock[idp].Quantidade += atoi(args[1]);
  }

  return 0;
}

int novaEnc()
{
  int i = proximoide();
  dataBase[i][0].Inicia = 0;
  printf("Nova encomenda %d.\n", i);
  return 0;
}

int adProd()
{
  int idp;
  int ide;
  int produtoQtd;
  int i;
  char args[5][64];
  char s[64];
  readLine(s);
  separarString(s, args);
  ide = atoi(args[0]);
  idp = atoi(args[1]);
  produtoQtd = atoi(args[2]);
  if (dataBase[ide][0].Inicia == (-1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return 1;
  }
  else
  {
    
  }

  if (strcmp(stock[idp].Descricao, "") == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return 1;
  }
  else
  {
    
  }

  if (produtoQtd > stock[idp].Quantidade)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return 1;
  }
  else
  {
    
  }

  if ((pesoTotalEnc(ide) + (stock[idp].Peso * produtoQtd)) > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    return 1;
  }
  else
  {
    
  }

  i = idpEnc(ide, idp);
  strcpy(dataBase[ide][i].Descricao, stock[idp].Descricao);
  dataBase[ide][i].Preco = stock[idp].Preco;
  dataBase[ide][i].Quantidade += produtoQtd;
  dataBase[ide][i].Peso += produtoQtd * stock[idp].Peso;
  dataBase[ide][i].Inicia = 0;
  stock[idp].Quantidade -= produtoQtd;
  return 0;
}

int removeStock()
{
  int produtoQtd;
  int idp;
  char args[5][64];
  char s[64];
  readLine(s);
  separarString(s, args);
  idp = atoi(args[0]);
  produtoQtd = atoi(args[1]);
  if (strcmp(stock[idp].Descricao, "") == 0)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    return 1;
  }
  else
  {
    
  }

  if ((stock[idp].Quantidade - produtoQtd) < 0)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", produtoQtd, idp);
    return 1;
  }
  else
  {
    
  }

  stock[idp].Quantidade = stock[idp].Quantidade - produtoQtd;
  return 0;
}

int removeProd()
{
  int idp;
  int ide;
  int i;
  char args[5][64];
  char s[64];
  readLine(s);
  separarString(s, args);
  ide = atoi(args[0]);
  idp = atoi(args[1]);
  i = idpEnc(ide, idp);
  if (dataBase[ide][0].Inicia == (-1))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return 1;
  }
  else
  {
    
  }

  if (strcmp(stock[idp].Descricao, "") == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return 1;
  }
  else
  {
    
  }

  if (strcmp(dataBase[ide][i].Descricao, stock[idp].Descricao) != 0)
  {
    return 1;
  }
  else
  {
    
  }

  stock[idp].Quantidade += dataBase[ide][i].Quantidade;
  strcpy(dataBase[ide][i].Descricao, "");
  dataBase[ide][i].Preco = 0;
  dataBase[ide][i].Quantidade = 0;
  dataBase[ide][i].Peso = 0;
  dataBase[ide][i].Inicia = 1;
  return 0;
}

int custoEnc()
{
  int ide;
  int i;
  int total = 0;
  char args[5][64];
  char s[64];
  readLine(s);
  separarString(s, args);
  ide = atoi(args[0]);
  if (dataBase[ide][0].Inicia == (-1))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return 1;
  }
  else
  {
    
  }

  for (i = 0; i < 200; i++)
  {
    total += dataBase[ide][i].Preco * dataBase[ide][i].Quantidade;
  }

  printf("Custo da encomenda %d %d.\n", ide, total);
  return 0;
}

int alteraPreco()
{
  int i;
  int e;
  int produtoPreco;
  int idp;
  char args[5][64];
  char s[64];
  readLine(s);
  separarString(s, args);
  idp = atoi(args[0]);
  produtoPreco = atoi(args[1]);
  if (strcmp(stock[idp].Descricao, "") == 0)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    return 1;
  }
  else
  {
    
  }

  for (i = 0; i < 500; i++)
  {
    if (dataBase[i][0].Inicia != (-1))
    {
      e = idpEnc(i, idp);
      if ((strcmp(dataBase[i][e].Descricao, stock[idp].Descricao) == 0) && (dataBase[i][e].Inicia == 0))
      {
        dataBase[i][e].Preco = produtoPreco;
      }
      else
      {
        
      }

    }
    else
    {
      break;
    }

  }

  stock[idp].Preco = produtoPreco;
  return 0;
}

int descQtd()
{
  int idp;
  int ide;
  int i;
  char args[5][64];
  char s[64];
  readLine(s);
  separarString(s, args);
  ide = atoi(args[0]);
  idp = atoi(args[1]);
  i = idpEnc(ide, idp);
  if (dataBase[ide][0].Inicia != (-1))
  {
    if (strcmp(stock[idp].Descricao, "") != 0)
    {
      printf("%s %d.\n", stock[idp].Descricao, dataBase[ide][i].Quantidade);
    }
    else
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }

  return 0;
}

int identificadorMax()
{
  int idp;
  int i;
  int max = 0;
  int ide;
  int a;
  char args[5][64];
  char s[64];
  readLine(s);
  separarString(s, args);
  idp = atoi(args[0]);
  if (strcmp(stock[idp].Descricao, "") != 0)
  {
    for (i = 0; i < 500; i++)
    {
      if (dataBase[i][0].Inicia != (-1))
      {
        a = idpEnc(i, idp);
        if (strcmp(stock[idp].Descricao, dataBase[i][a].Descricao) == 0)
        {
          if (dataBase[i][a].Quantidade > max)
          {
            max = dataBase[i][a].Quantidade;
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
      else
      {
        break;
      }

    }

    if (max != 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, ide, max);
    }
    else
    {
      
    }

  }
  else
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }

  return 0;
}

int listaProd()
{
  int e;
  int i;
  int counter = 0;
  int tab_final[10000];
  for (e = 0; e < 10000; e++)
  {
    if (strcmp(stock[e].Descricao, "") != 0)
    {
      tab_final[e] = e;
      counter++;
    }
    else
    {
      break;
    }

  }

  mergeSort_l(tab_final, 0, counter - 1);
  printf("Produtos\n");
  for (i = 0; i < counter; i++)
  {
    printf("* %s %d %d\n", stock[tab_final[i]].Descricao, stock[tab_final[i]].Preco, stock[tab_final[i]].Quantidade);
  }

  return 0;
}

int listaProdEnc()
{
  int i;
  int counter = 0;
  int tab_final[200];
  int ide;
  char args[5][64];
  char s[64];
  readLine(s);
  separarString(s, args);
  ide = atoi(args[0]);
  if (dataBase[ide][0].Inicia == (-1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return 1;
  }
  else
  {
    
  }

  for (i = 0; i < 200; i++)
  {
    if ((strcmp(dataBase[ide][i].Descricao, "") != 0) && (dataBase[ide][i].Inicia == 0))
    {
      tab_final[counter] = i;
      counter++;
    }
    else
    {
      
    }

  }

  mergeSort_L(tab_final, 0, counter - 1, ide);
  printf("Encomenda %d\n", ide);
  for (i = 0; i < counter; i++)
  {
    printf("* %s %d %d\n", dataBase[ide][tab_final[i]].Descricao, dataBase[ide][tab_final[i]].Preco, dataBase[ide][tab_final[i]].Quantidade);
  }

  return 0;
}

int Selector()
{
  int running = 1;
  char op;
  while (running == 1)
  {
    op = getchar();
    getchar();
    switch (op)
    {
      case 'a':
        novoProd();
        break;

      case 'q':
        adStock();
        break;

      case 'N':
        novaEnc();
        break;

      case 'A':
        adProd();
        break;

      case 'r':
        removeStock();
        break;

      case 'R':
        removeProd();
        break;

      case 'C':
        custoEnc();
        break;

      case 'p':
        alteraPreco();
        break;

      case 'E':
        descQtd();
        break;

      case 'm':
        identificadorMax();
        break;

      case 'l':
        listaProd();
        break;

      case 'L':
        listaProdEnc();
        break;

      case 'x':
        running = 0;
        break;

    }

  }

  return 0;
}

int main()
{
  int i;
  int e;
  for (i = 0; i < 10000; i++)
  {
    strcpy(stock[i].Descricao, "");
    stock[i].Peso = 0;
    stock[i].Preco = 0;
    stock[i].Quantidade = 0;
  }

  for (i = 0; i < 500; i++)
  {
    for (e = 0; e < 200; e++)
    {
      strcpy(dataBase[i][e].Descricao, "");
      dataBase[i][e].Preco = 0;
      dataBase[i][e].Peso = 0;
      dataBase[i][e].Quantidade = 0;
      dataBase[i][e].Inicia = -1;
    }

  }

  Selector();
  return 0;
}

