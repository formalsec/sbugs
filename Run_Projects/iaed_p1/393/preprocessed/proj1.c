/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  char desc[63];
  int idp;
  int preco;
  int peso;
  int qtd;
} Produto;
typedef struct encomenda
{
  int distintos;
  Produto produtos[200];
} Encomenda;
int idpGlobal = 0;
int ideGlobal = 0;
Produto sistema[10000];
Produto ordenados[10000];
Encomenda encomendas[500];
int existeProduto(Produto lista[], int idp, int limite)
{
  int i;
  for (i = 0; i < limite; i++)
  {
    if (lista[i].idp == idp)
    {
      return 1;
    }
    else
    {
      
    }

  }

  return 0;
}

int existeEncomenda(int ide)
{
  return ideGlobal > ide;
}

int peso(int ide)
{
  int i;
  int peso = 0;
  for (i = 0; i < encomendas[ide].distintos; i++)
  {
    peso += encomendas[ide].produtos[i].peso * encomendas[ide].produtos[i].qtd;
  }

  return peso;
}

int posicao(int ide, int idp)
{
  int i;
  for (i = 0; i < encomendas[ide].distintos; i++)
  {
    if (encomendas[ide].produtos[i].idp == idp)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

int less(Produto a, Produto b, int tipo)
{
  if (tipo == 1)
  {
    {
      if (a.preco == b.preco)
      {
        return a.idp < b.idp;
      }
      else
      {
        
      }

      return a.preco < b.preco;
    }
  }
  else
  {
    return strcmp(a.desc, b.desc) < 0;
  }

}

void quickSort(Produto lista[], int l, int r, int tipo)
{
  int i = l - 1;
  int j = r;
  Produto v = lista[r];
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  while (i < j)
  {
    while (less(lista[++i], v, tipo))
      ;

    while (less(v, lista[--j], tipo))
      if (j == l)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      {
        Produto t = lista[i];
        lista[i] = lista[j];
        lista[j] = t;
      }
    }
    else
    {
      
    }

    ;
  }

  {
    Produto t = lista[i];
    lista[i] = lista[r];
    lista[r] = t;
  }
  ;
  quickSort(lista, l, i - 1, tipo);
  quickSort(lista, i + 1, r, tipo);
}

void casoa(Produto p)
{
  p.idp = idpGlobal;
  sistema[idpGlobal++] = p;
  printf("Novo produto %d.\n", p.idp);
}

void casoq(int idp, int qtd)
{
  if (!existeProduto(sistema, idp, idpGlobal))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    sistema[idp].qtd += qtd;
  }

}

void casoN()
{
  Encomenda e;
  e.distintos = 0;
  encomendas[ideGlobal] = e;
  printf("Nova encomenda %d.\n", ideGlobal++);
}

void casoA(int ide, int idp, int qtd)
{
  if (!existeEncomenda(ide))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (!existeProduto(sistema, idp, idpGlobal))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (sistema[idp].qtd < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((peso(ide) + (sistema[idp].peso * qtd)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          {
            sistema[idp].qtd -= qtd;
            if (existeProduto(encomendas[ide].produtos, idp, encomendas[ide].distintos))
            {
              encomendas[ide].produtos[posicao(ide, idp)].qtd += qtd;
            }
            else
            {
              {
                encomendas[ide].produtos[encomendas[ide].distintos] = sistema[idp];
                encomendas[ide].produtos[encomendas[ide].distintos++].qtd = qtd;
              }
            }

          }
        }

      }

    }

  }

}

void casor(int idp, int qtd)
{
  if (!existeProduto(sistema, idp, idpGlobal))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (sistema[idp].qtd < qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      sistema[idp].qtd -= qtd;
    }

  }

}

void casoR(int ide, int idp)
{
  if (!existeEncomenda(ide))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (!existeProduto(sistema, idp, idpGlobal))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (existeProduto(encomendas[ide].produtos, idp, encomendas[ide].distintos))
      {
        {
          sistema[idp].qtd += encomendas[ide].produtos[posicao(ide, idp)].qtd;
          encomendas[ide].produtos[posicao(ide, idp)].qtd = 0;
        }
      }
      else
      {
        
      }

    }

  }

}

void casoC(int ide)
{
  if (!existeEncomenda(ide))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    {
      int preco = 0;
      int i;
      for (i = 0; i < encomendas[ide].distintos; i++)
      {
        preco += encomendas[ide].produtos[i].qtd * encomendas[ide].produtos[i].preco;
      }

      printf("Custo da encomenda %d %d.\n", ide, preco);
    }
  }

}

void casop(int idp, int preco)
{
  if (!existeProduto(sistema, idp, idpGlobal))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    {
      int i;
      sistema[idp].preco = preco;
      for (i = 0; i < ideGlobal; i++)
        encomendas[i].produtos[posicao(i, idp)].preco = preco;

    }
  }

}

void casoE(int ide, int idp)
{
  if (!existeEncomenda(ide))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (!existeProduto(sistema, idp, idpGlobal))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      {
        if (existeProduto(encomendas[ide].produtos, idp, encomendas[ide].distintos))
        {
          printf("%s %d.\n", sistema[idp].desc, encomendas[ide].produtos[posicao(ide, idp)].qtd);
        }
        else
        {
          printf("%s %d.\n", sistema[idp].desc, 0);
        }

      }
    }

  }

}

void casom(int idp)
{
  if (!existeProduto(sistema, idp, idpGlobal))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    {
      int i;
      int maxID;
      int numero = 0;
      for (i = 0; i < ideGlobal; i++)
      {
        if (existeEncomenda(i))
        {
          {
            if (existeProduto(encomendas[i].produtos, idp, encomendas[i].distintos))
            {
              {
                if (encomendas[i].produtos[posicao(i, idp)].qtd > numero)
                {
                  numero = encomendas[i].produtos[posicao(i, idp)].qtd, maxID = i;
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
        else
        {
          
        }

      }

      if (numero > 0)
      {
        printf("Maximo produto %d %d %d.\n", idp, maxID, numero);
      }
      else
      {
        
      }

    }
  }

}

void casol()
{
  int i;
  for (i = 0; i < idpGlobal; i++)
    ordenados[i] = sistema[i];

  quickSort(ordenados, 0, idpGlobal - 1, 1);
  printf("Produtos\n");
  for (i = 0; i < idpGlobal; i++)
    printf("* %s %d %d\n", ordenados[i].desc, ordenados[i].preco, ordenados[i].qtd);

}

void casoL(int ide)
{
  if (!existeEncomenda(ide))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    {
      int i;
      quickSort(encomendas[ide].produtos, 0, encomendas[ide].distintos - 1, 2);
      printf("Encomenda %d\n", ide);
      for (i = 0; i < encomendas[ide].distintos; i++)
        if (encomendas[ide].produtos[i].qtd > 0)
      {
        printf("* %s %d %d\n", encomendas[ide].produtos[i].desc, encomendas[ide].produtos[i].preco, encomendas[ide].produtos[i].qtd);
      }
      else
      {
        
      }


    }
  }

}

int main()
{
  char caso;
  int ide;
  Produto p1;
  caso = new_sym_var(sizeof(char) * 8);
  while (caso != 'x')
  {
    switch (caso)
    {
      case 'a':
        for (int p1_index = 0; p1_index < 10; p1_index++)
      {
        p1.desc[p1_index] = new_sym_var(sizeof(char) * 8);
      }

        p1.desc[10 - 1] = '\0';
        p1.preco = new_sym_var(sizeof(int) * 8);
        p1.peso = new_sym_var(sizeof(int) * 8);
        p1.qtd = new_sym_var(sizeof(int) * 8);
        casoa(p1);
        break;

      case 'q':
        p1.idp = new_sym_var(sizeof(int) * 8);
        p1.qtd = new_sym_var(sizeof(int) * 8);
        casoq(p1.idp, p1.qtd);
        break;

      case 'N':
        casoN();
        break;

      case 'A':
        ide = new_sym_var(sizeof(int) * 8);
        p1.idp = new_sym_var(sizeof(int) * 8);
        p1.qtd = new_sym_var(sizeof(int) * 8);
        casoA(ide, p1.idp, p1.qtd);
        break;

      case 'r':
        p1.idp = new_sym_var(sizeof(int) * 8);
        p1.qtd = new_sym_var(sizeof(int) * 8);
        casor(p1.idp, p1.qtd);
        break;

      case 'R':
        ide = new_sym_var(sizeof(int) * 8);
        p1.idp = new_sym_var(sizeof(int) * 8);
        casoR(ide, p1.idp);
        break;

      case 'C':
        ide = new_sym_var(sizeof(int) * 8);
        casoC(ide);
        break;

      case 'p':
        p1.idp = new_sym_var(sizeof(int) * 8);
        p1.preco = new_sym_var(sizeof(int) * 8);
        casop(p1.idp, p1.preco);
        break;

      case 'E':
        ide = new_sym_var(sizeof(int) * 8);
        p1.idp = new_sym_var(sizeof(int) * 8);
        casoE(ide, p1.idp);
        break;

      case 'm':
        p1.idp = new_sym_var(sizeof(int) * 8);
        casom(p1.idp);
        break;

      case 'l':
        casol();
        break;

      case 'L':
        ide = new_sym_var(sizeof(int) * 8);
        casoL(ide);
        break;

    }

    caso = new_sym_var(sizeof(char) * 8);
  }

  return 0;
}
