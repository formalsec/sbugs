/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Produtos
{
  int id;
  char descricao[64];
  int preco;
  int peso;
  int qtdPedidaNaEnc;
  int qtdEmStock;
  int exite;
  int numerodeVezesEnc;
  int idpNaEnc;
} Produto;
typedef struct Encomendas
{
  Produto encomendado[200];
  int encPeso;
  int idEnc;
  int numeroDeProdutos;
  int existeEncomenda;
  int custo;
  int idsProdEnc[10000];
} Encomenda;
Produto ListaDeProdutos[10000];
Produto ListaAuxProd[10000];
Produto ListaOrdProd[10000];
Encomenda ListaDeEncomendas[500];
int contador = 0;
int contadorEnc = 0;
void adicionaProduto();
void adicionaStock();
void criaNovaEncomenda();
void adicionaProdEncomenda();
void removeProdStock();
void removeProdEncomenda();
void calculaCustoDeEncomenda();
void alteraPrecoDoProduto();
void listaProdDescQuant();
void listaIdEncMaxProd();
void listaProdPorOrdemDePreco();
void listaProdPorDescricao();
void ordenaPorNome(Produto encomendados[], int tam);
void ordenaPorPreco();
int existeProd(int idProd);
int existeEnc(int idEnc);
int produtoExistenteNaEncomenda(int idp, int idenc);
int idProdNaEnc(int ide, int idp);
int main()
{
  char comando;
  do
  {
    comando = getchar();
    switch (comando)
    {
      case 'a':
        adicionaProduto();
        break;

      case 'q':
        adicionaStock();
        break;

      case 'N':
        criaNovaEncomenda();
        break;

      case 'A':
        adicionaProdEncomenda();
        break;

      case 'r':
        removeProdStock();
        break;

      case 'R':
        removeProdEncomenda();
        break;

      case 'C':
        calculaCustoDeEncomenda();
        break;

      case 'p':
        alteraPrecoDoProduto();
        break;

      case 'E':
        listaProdDescQuant();
        break;

      case 'm':
        listaIdEncMaxProd();
        break;

      case 'l':
        listaProdPorOrdemDePreco();
        break;

      case 'L':
        listaProdPorDescricao();
        break;

      default:
        break;

    }

  }
  while (comando != 'x');
  return 0;
}

void adicionaProduto()
{
  char descricao[64];
  int preco;
  int peso;
  int qtd;
  Produto p;
  getchar();
  for (int descricao_index = 0; descricao_index < 10; descricao_index++)
  {
    descricao[descricao_index] = new_sym_var(sizeof(char) * 8);
  }

  descricao[10 - 1] = '\0';
  preco = new_sym_var(sizeof(int) * 8);
  peso = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  strcpy(p.descricao, descricao);
  p.preco = preco;
  p.peso = peso;
  p.qtdPedidaNaEnc = 0;
  p.qtdEmStock = qtd;
  p.id = contador;
  p.exite = 1;
  p.numerodeVezesEnc = 0;
  p.idpNaEnc = -1;
  ListaDeProdutos[contador++] = p;
  printf("Novo produto %d.\n", p.id);
}

void adicionaStock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp < contador)
  {
    ListaDeProdutos[idp].qtdEmStock += qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

}

void criaNovaEncomenda()
{
  Encomenda novaEncomenda;
  novaEncomenda.idEnc = contadorEnc;
  novaEncomenda.encPeso = 0;
  novaEncomenda.numeroDeProdutos = 0;
  novaEncomenda.existeEncomenda = 1;
  novaEncomenda.custo = 0;
  ListaDeEncomendas[contadorEnc++] = novaEncomenda;
  printf("Nova encomenda %d.\n", novaEncomenda.idEnc);
}

void adicionaProdEncomenda()
{
  int idEnc;
  int idp;
  int qtdPedida;
  int idpEnc;
  Encomenda e;
  Produto p;
  idEnc = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtdPedida = new_sym_var(sizeof(int) * 8);
  if (idEnc < contadorEnc)
  {
    if (idp < contador)
    {
      p = ListaDeProdutos[idp];
      e = ListaDeEncomendas[idEnc];
      if (ListaDeProdutos[idp].qtdEmStock < qtdPedida)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, idEnc);
      }
      else
      {
        if ((ListaDeEncomendas[idEnc].encPeso + (p.peso * qtdPedida)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, idEnc);
        }
        else
        {
          idpEnc = produtoExistenteNaEncomenda(idp, idEnc);
          if (idpEnc == (-1))
          {
            p.preco = ListaDeProdutos[idp].preco;
            strcpy(p.descricao, ListaDeProdutos[idp].descricao);
            p.id = ListaDeProdutos[idp].id;
            p.qtdPedidaNaEnc += qtdPedida;
            p.peso = ListaDeProdutos[idp].peso;
            p.idpNaEnc = e.numeroDeProdutos;
            ListaDeEncomendas[idEnc].encomendado[e.numeroDeProdutos] = p;
            ListaDeEncomendas[idEnc].encPeso += p.peso * qtdPedida;
            ListaDeProdutos[idp].qtdEmStock -= qtdPedida;
            ListaDeEncomendas[idEnc].numeroDeProdutos++;
            ListaDeEncomendas[idEnc].encomendado[e.numeroDeProdutos].numerodeVezesEnc++;
          }
          else
          {
            ListaDeEncomendas[idEnc].encomendado[idpEnc].qtdPedidaNaEnc += qtdPedida;
            ListaDeEncomendas[idEnc].encPeso += qtdPedida * p.peso;
            ListaDeProdutos[idp].qtdEmStock -= qtdPedida;
            ListaDeEncomendas[idEnc].encomendado[idpEnc].numerodeVezesEnc++;
          }

        }

      }

    }
    else
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, idEnc);
    }

  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, idEnc);
  }

}

void removeProdStock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp < contador)
  {
    if (ListaDeProdutos[idp].qtdEmStock < qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      ListaDeProdutos[idp].qtdEmStock -= qtd;
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }

}

void removeProdEncomenda()
{
  int ide;
  int idp;
  int peso;
  int qtd;
  int i;
  int limite;
  int idpEnc;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide < contadorEnc)
  {
    if (idp < contador)
    {
      idpEnc = produtoExistenteNaEncomenda(idp, ide);
      if (idpEnc != (-1))
      {
        peso = ListaDeEncomendas[ide].encomendado[idpEnc].peso;
        qtd = ListaDeEncomendas[ide].encomendado[idpEnc].qtdPedidaNaEnc;
        ListaDeProdutos[idp].qtdEmStock += qtd;
        ListaDeEncomendas[ide].encPeso -= qtd * peso;
        ListaDeEncomendas[ide].encomendado[idpEnc].qtdPedidaNaEnc = 0;
        ListaDeEncomendas[ide].encomendado[idpEnc].idpNaEnc = -1;
        limite = ListaDeEncomendas[ide].numeroDeProdutos - 1;
        for (i = idpEnc; i < limite; i++)
        {
          ListaDeEncomendas[ide].encomendado[i] = ListaDeEncomendas[ide].encomendado[i + 1];
        }

        ListaDeEncomendas[ide].numeroDeProdutos--;
      }
      else
      {
        
      }

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

void calculaCustoDeEncomenda()
{
  int ide;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide < contadorEnc)
  {
    for (i = 0; i < ListaDeEncomendas[ide].numeroDeProdutos; i++)
    {
      ListaDeEncomendas[ide].custo += ListaDeEncomendas[ide].encomendado[i].preco * ListaDeEncomendas[ide].encomendado[i].qtdPedidaNaEnc;
    }

    printf("Custo da encomenda %d %d.\n", ide, ListaDeEncomendas[ide].custo);
    ListaDeEncomendas[ide].custo = 0;
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }

}

void alteraPrecoDoProduto()
{
  int idp;
  int preco;
  int i;
  int idpEnc = -1;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp < contador)
  {
    ListaDeProdutos[idp].preco = preco;
    for (i = 0; i < contadorEnc; i++)
    {
      idpEnc = idProdNaEnc(i, idp);
      if (idpEnc != (-1))
      {
        ListaDeEncomendas[i].encomendado[idpEnc].preco = preco;
      }
      else
      {
        
      }

    }

  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }

}

int idProdNaEnc(int ide, int idp)
{
  int i;
  int existe = -1;
  for (i = 0; (i < ListaDeEncomendas[ide].numeroDeProdutos) && (existe == (-1)); i++)
  {
    if (idp == ListaDeEncomendas[ide].encomendado[i].id)
    {
      existe = i;
    }
    else
    {
      
    }

  }

  return existe;
}

void listaProdDescQuant()
{
  int ide;
  int idp;
  int qtd;
  int existe = -1;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide < contadorEnc)
  {
    if (idp < contador)
    {
      existe = idProdNaEnc(ide, idp);
      qtd = 0;
      if (existe != (-1))
      {
        printf("%s %d.\n", ListaDeEncomendas[ide].encomendado[existe].descricao, ListaDeEncomendas[ide].encomendado[existe].qtdPedidaNaEnc);
      }
      else
      {
        printf("%s %d.\n", ListaDeProdutos[idp].descricao, qtd);
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

void listaIdEncMaxProd()
{
  int idp;
  int i;
  int maior;
  int ide;
  int idpEnc = -1;
  idp = new_sym_var(sizeof(int) * 8);
  ide = (maior = (i = 0));
  if (idp < contador)
  {
    for (; i < contadorEnc; i++)
    {
      idpEnc = idProdNaEnc(i, idp);
      if (idpEnc != (-1))
      {
        if (ListaDeEncomendas[i].encomendado[idpEnc].qtdPedidaNaEnc > maior)
        {
          maior = ListaDeEncomendas[i].encomendado[idpEnc].qtdPedidaNaEnc;
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

    if ((ide < contadorEnc) && (maior != 0))
    {
      printf("Maximo produto %d %d %d.\n", idp, ide, maior);
    }
    else
    {
      
    }

  }
  else
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }

}

void listaProdPorOrdemDePreco()
{
  int i;
  Produto temp;
  for (i = 0; i < contador; i++)
  {
    ListaOrdProd[i] = ListaDeProdutos[i];
  }

  ordenaPorPreco();
  printf("Produtos\n");
  for (i = 0; i < contador; i++)
  {
    temp = ListaOrdProd[i];
    printf("* %s %d %d\n", temp.descricao, temp.preco, temp.qtdEmStock);
  }

}

void listaProdPorDescricao()
{
  int ide;
  int numDeProdutos;
  int i;
  int preco;
  Produto aux;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide < contadorEnc)
  {
    numDeProdutos = ListaDeEncomendas[ide].numeroDeProdutos;
    for (i = 0; i < numDeProdutos; i++)
    {
      ListaOrdProd[i] = ListaDeEncomendas[ide].encomendado[i];
    }

    ordenaPorNome(ListaOrdProd, numDeProdutos);
    printf("Encomenda %d\n", ide);
    for (i = 0; i < numDeProdutos; i++)
    {
      aux = ListaOrdProd[i];
      preco = ListaDeProdutos[aux.id].preco;
      printf("* %s %d %d\n", aux.descricao, preco, aux.qtdPedidaNaEnc);
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }

}

int produtoExistenteNaEncomenda(int idp, int idenc)
{
  int i;
  int existe = -1;
  for (i = 0; (i < ListaDeEncomendas[idenc].numeroDeProdutos) && (existe == (-1)); i++)
  {
    if (ListaDeEncomendas[idenc].encomendado[i].id == idp)
    {
      if (ListaDeEncomendas[idenc].encomendado[i].idpNaEnc != (-1))
      {
        existe = i;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  return existe;
}

int comparador(Produto p1, Produto p2, int codigo)
{
  int comp;
  if (codigo == 1)
  {
    return (p1.preco < p2.preco) || ((p1.preco == p2.preco) && (p1.id < p2.id));
  }
  else
  {
    comp = strcmp(p1.descricao, p2.descricao);
    return (comp < 0) || ((comp == 0) && (p1.id < p2.id));
  }

}

void merge(Produto a[], int left, int m, int right, int codigo)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
  {
    ListaAuxProd[i - 1] = a[i - 1];
  }

  for (j = m; j < right; j++)
  {
    ListaAuxProd[(right + m) - j] = a[j + 1];
  }

  for (k = left; k <= right; k++)
  {
    if (comparador(ListaAuxProd[j], ListaAuxProd[i], codigo) || (i > m))
    {
      a[k] = ListaAuxProd[j--];
    }
    else
    {
      a[k] = ListaAuxProd[i++];
    }

  }

}

void mergesort(Produto a[], int l, int r, int codigo)
{
  int m;
  m = (l + r) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort(a, l, m, codigo);
  mergesort(a, m + 1, r, codigo);
  merge(a, l, m, r, codigo);
}

void ordenaPorPreco()
{
  mergesort(ListaOrdProd, 0, contador - 1, 1);
}

void ordenaPorNome(Produto encomendados[], int tam)
{
  mergesort(encomendados, 0, tam - 1, 2);
}

