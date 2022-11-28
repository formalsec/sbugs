#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int real;
  int pID;
  char desc[65];
  int preco;
  int peso;
  int stock;
} Produto;
typedef struct 
{
  int real;
  int eID;
  Produto produtos[200];
  int peso_e;
  int prodcount;
} Encomenda;
typedef struct 
{
  char desc[65];
  int pID;
  int qtd;
} L_AUX;
int pcount = 0;
int ecount = 0;
Produto sistema[10000];
Encomenda sistema_e[500];
L_AUX ordenada[200];
void adicionaProduto();
void adicionaStock();
void removeStock();
void alteraPreco();
void criaEncomenda();
void adiciona_ah_Encomenda();
void adicionaEnc_aux(int ide, int idp, int qtd);
void removeDaEncome();
void removeDaEncome_aux(int ide, int idp);
void custoEncome();
void prodNaEncom();
void ocorrenciaProd();
void ocorrenciaProd_aux(int idp);
void listaProdSistema();
void listaProdEncomenda();
void listaProdEncomenda_aux(int ide);
int main()
{
  char comando;
  comando = new_sym_var(sizeof(char) * 8);
  while (comando != 'x')
  {
    switch (comando)
    {
      case 'a':
        adicionaProduto();
        break;

      case 'q':
        adicionaStock();
        break;

      case 'r':
        removeStock();
        break;

      case 'p':
        alteraPreco();
        break;

      case 'N':
        criaEncomenda();
        break;

      case 'A':
        adiciona_ah_Encomenda();
        break;

      case 'R':
        removeDaEncome();
        break;

      case 'C':
        custoEncome();
        break;

      case 'E':
        prodNaEncom();
        break;

      case 'm':
        ocorrenciaProd();
        break;

      case 'l':
        listaProdSistema();
        break;

      case 'L':
        listaProdEncomenda();
        break;

    }

    comando = new_sym_var(sizeof(char) * 8);
  }

  return 0;
}

void adicionaProduto()
{
  for (int sistema_index = 0; sistema_index < 10; sistema_index++)
  {
    sistema[pcount].desc[sistema_index] = new_sym_var(sizeof(char) * 8);
  }

  sistema[pcount].desc[10 - 1] = '\0';
  sistema[pcount].preco = new_sym_var(sizeof(int) * 8);
  sistema[pcount].peso = new_sym_var(sizeof(int) * 8);
  sistema[pcount].stock = new_sym_var(sizeof(int) * 8);
  sistema[pcount].pID = pcount;
  sistema[pcount].real = 1;
  printf("Novo produto %d.\n", sistema[pcount].pID);
  pcount++;
}

void adicionaStock()
{
  int pid;
  int stockadicional;
  pid = new_sym_var(sizeof(int) * 8);
  stockadicional = new_sym_var(sizeof(int) * 8);
  if (sistema[pid].real == 1)
  {
    sistema[pid].stock = sistema[pid].stock + stockadicional;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", pid);
  }

}

void removeStock()
{
  int pid;
  int stockaremover;
  pid = new_sym_var(sizeof(int) * 8);
  stockaremover = new_sym_var(sizeof(int) * 8);
  if (sistema[pid].real == 1)
  {
    if (stockaremover <= sistema[pid].stock)
    {
      sistema[pid].stock = sistema[pid].stock - stockaremover;
    }
    else
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stockaremover, pid);
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", pid);
  }

}

void alteraPreco()
{
  int pid;
  int preconovo;
  pid = new_sym_var(sizeof(int) * 8);
  preconovo = new_sym_var(sizeof(int) * 8);
  if (sistema[pid].real == 1)
  {
    sistema[pid].preco = preconovo;
  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", pid);
  }

}

void criaEncomenda()
{
  sistema_e[ecount].eID = ecount;
  sistema_e[ecount].real = 1;
  printf("Nova encomenda %d.\n", sistema_e[ecount].eID);
  ecount++;
}

void adicionaEnc_aux(int ide, int idp, int qtd)
{
  int pesoprod = sistema[idp].peso * qtd;
  int pesoatual = sistema_e[ide].peso_e;
  int prodcount = sistema_e[ide].prodcount;
  int i;
  int match = -1;
  sistema_e[ide].peso_e = pesoprod + pesoatual;
  for (i = 0; i <= prodcount; i++)
  {
    if ((sistema_e[ide].produtos[i].pID == idp) && (sistema_e[ide].produtos[i].real == 1))
    {
      match = i;
      break;
    }
    else
    {
      
    }

  }

  if (match >= 0)
  {
    sistema_e[ide].produtos[match].stock = sistema_e[ide].produtos[match].stock + qtd;
  }
  else
  {
    sistema_e[ide].produtos[prodcount].pID = idp;
    sistema_e[ide].produtos[prodcount].real = 1;
    sistema_e[ide].produtos[prodcount].stock = qtd;
    strcpy(sistema_e[ide].produtos[prodcount].desc, sistema[idp].desc);
    sistema_e[ide].prodcount++;
  }

  sistema[idp].stock = sistema[idp].stock - qtd;
}

void adiciona_ah_Encomenda()
{
  int ide;
  int idp;
  int qtd;
  int pesototal;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  pesototal = sistema[idp].peso * qtd;
  pesototal = sistema_e[ide].peso_e + pesototal;
  if (sistema_e[ide].real == 1)
  {
    if (sistema[idp].real == 1)
    {
      if (sistema[idp].stock >= qtd)
      {
        if (pesototal <= 200)
        {
          adicionaEnc_aux(ide, idp, qtd);
        }
        else
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }

      }
      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }

    }
    else
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }

}

void removeDaEncome_aux(int ide, int idp)
{
  int prodcount = sistema_e[ide].prodcount;
  int i;
  int qtd;
  int pesoaremover;
  for (i = 0; i <= prodcount; i++)
  {
    if (sistema_e[ide].produtos[i].pID == idp)
    {
      qtd = sistema_e[ide].produtos[i].stock;
      sistema[idp].stock = sistema[idp].stock + qtd;
      sistema_e[ide].produtos[i].stock = 0;
      pesoaremover = sistema[idp].peso * qtd;
      sistema_e[ide].peso_e = sistema_e[ide].peso_e - pesoaremover;
      break;
    }
    else
    {
      
    }

  }

}

void removeDaEncome()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (sistema_e[ide].real == 1)
  {
    if (sistema[idp].real == 1)
    {
      removeDaEncome_aux(ide, idp);
    }
    else
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

  }
  else
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }

}

void custoEncome()
{
  int ide;
  int i;
  int prodcount;
  int soma = 0;
  int precoprod = 0;
  int indice;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  prodcount = sistema_e[ide].prodcount;
  if (sistema_e[ide].real == 1)
  {
    for (i = 0; i <= prodcount; i++)
    {
      if (sistema_e[ide].produtos[i].real == 1)
      {
        indice = sistema_e[ide].produtos[i].pID;
        qtd = sistema_e[ide].produtos[i].stock;
        precoprod = sistema[indice].preco * qtd;
        soma = soma + precoprod;
      }
      else
      {
        
      }

    }

    printf("Custo da encomenda %d %d.\n", ide, soma);
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }

}

void prodNaEncom()
{
  int ide;
  int idp;
  int i;
  int match = -1;
  int qtd;
  int prodcount;
  char desc[65];
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  prodcount = sistema_e[ide].prodcount;
  if (sistema_e[ide].real == 1)
  {
    if (sistema[idp].real == 1)
    {
      for (i = 0; i <= prodcount; i++)
      {
        if (sistema_e[ide].produtos[i].pID == idp)
        {
          match = i;
          qtd = sistema_e[ide].produtos[match].stock;
          strcpy(desc, sistema[idp].desc + 1);
          printf("%s %d.\n", desc, qtd);
          break;
        }
        else
        {
          
        }

      }

      if (match == (-1))
      {
        strcpy(desc, sistema[idp].desc + 1);
        printf("%s 0.\n", desc);
      }
      else
      {
        
      }

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

}

void ocorrenciaProd_aux(int idp)
{
  int maior = 0;
  int i;
  int prodcount;
  int n;
  int encomenda;
  for (i = 0; i < ecount; i++)
  {
    prodcount = sistema_e[i].prodcount;
    for (n = 0; n < prodcount; n++)
    {
      if ((sistema_e[i].produtos[n].pID == idp) && (sistema_e[i].produtos[n].stock > maior))
      {
        maior = sistema_e[i].produtos[n].stock;
        encomenda = i;
      }
      else
      {
        
      }

    }

  }

  if (maior > 0)
  {
    printf("Maximo produto %d %d %d.\n", idp, encomenda, maior);
  }
  else
  {
    
  }

}

void ocorrenciaProd()
{
  int idp;
  idp = new_sym_var(sizeof(int) * 8);
  if (sistema[idp].real == 1)
  {
    ocorrenciaProd_aux(idp);
  }
  else
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }

}

void listaProdSistema()
{
  int auxiliar[10000][2];
  int i;
  int left = 0;
  int right = pcount;
  int j;
  int idp;
  for (i = 0; i < pcount; i++)
  {
    auxiliar[i][0] = sistema[i].preco;
    auxiliar[i][1] = i;
  }

  for (i = left + 1; i < right; i++)
  {
    int v = auxiliar[i][0];
    int w = auxiliar[i][1];
    j = i - 1;
    while ((j >= left) && (auxiliar[j][0] > v))
    {
      auxiliar[j + 1][0] = auxiliar[j][0];
      auxiliar[j + 1][1] = auxiliar[j][1];
      j--;
    }

    auxiliar[j + 1][0] = v;
    auxiliar[j + 1][1] = w;
  }

  printf("Produtos\n");
  for (i = 0; i < pcount; i++)
  {
    idp = auxiliar[i][1];
    printf("*%s %d %d\n", sistema[idp].desc, sistema[idp].preco, sistema[idp].stock);
  }

}

void listaProdEncomenda_aux(int ide)
{
  int i;
  int j;
  char temp[65];
  int tempid;
  int tempqtd;
  int preco;
  for (i = 0; i < sistema_e[ide].prodcount; i++)
  {
    ordenada[i].pID = sistema_e[ide].produtos[i].pID;
    ordenada[i].qtd = sistema_e[ide].produtos[i].stock;
    strcpy(ordenada[i].desc, sistema_e[ide].produtos[i].desc);
  }

  for (i = 0; i <= sistema_e[ide].prodcount; i++)
  {
    for (j = i + 1; j < sistema_e[ide].prodcount; j++)
    {
      if (strcmp(ordenada[i].desc, ordenada[j].desc) > 0)
      {
        strcpy(temp, ordenada[i].desc);
        strcpy(ordenada[i].desc, ordenada[j].desc);
        strcpy(ordenada[j].desc, temp);
        tempid = ordenada[i].pID;
        ordenada[i].pID = ordenada[j].pID;
        ordenada[j].pID = tempid;
        tempqtd = ordenada[i].qtd;
        ordenada[i].qtd = ordenada[j].qtd;
        ordenada[j].qtd = tempqtd;
      }
      else
      {
        
      }

    }

  }

  printf("Encomenda %d\n", ide);
  for (i = 0; i < sistema_e[ide].prodcount; i++)
  {
    if (ordenada[i].qtd > 0)
    {
      tempid = ordenada[i].pID;
      preco = sistema[tempid].preco;
      printf("*%s %d %d\n", ordenada[i].desc, preco, ordenada[i].qtd);
    }
    else
    {
      
    }

  }

}

void listaProdEncomenda()
{
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (sistema_e[ide].real == 1)
  {
    if (sistema_e[ide].peso_e != 0)
    {
      listaProdEncomenda_aux(ide);
    }
    else
    {
      printf("Encomenda %d\n", ide);
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }

}
