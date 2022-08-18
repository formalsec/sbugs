/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  char desc[63];
  int preco;
  int peso;
  int stock;
} produto;
int conta_p = -1;
int conta_e = -1;
produto produtos[10000];
int encomendas[500][200][2];
void inicializaEncomendas()
{
  int i;
  int j;
  for (i = 0; i < 500; i++)
    for (j = 0; j < 200; j++)
    encomendas[i][j][0] = -1;


}

produto aux[10000];
void mergeDescricao(produto vetor[], int left, int m, int right)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = vetor[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = vetor[j + 1];

  for (k = left; k <= right; k++)
    if ((strcmp(aux[j].desc, aux[i].desc) < 0) || (i > m))
  {
    vetor[k] = aux[j--];
  }
  else
  {
    vetor[k] = aux[i++];
  }


}

void mergeSortDescricao(produto vetor[], int left, int right)
{
  int m = (left + right) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergeSortDescricao(vetor, left, m);
  mergeSortDescricao(vetor, m + 1, right);
  mergeDescricao(vetor, left, m, right);
}

void mergePreco(produto vetor[], int left, int m, int right)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = vetor[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = vetor[j + 1];

  for (k = left; k <= right; k++)
    if ((aux[j].preco < aux[i].preco) || (i > m))
  {
    vetor[k] = aux[j--];
  }
  else
  {
    vetor[k] = aux[i++];
  }


}

void mergeSortPreco(produto vetor[], int left, int right)
{
  int m = (left + right) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergeSortPreco(vetor, left, m);
  mergeSortPreco(vetor, m + 1, right);
  mergePreco(vetor, left, m, right);
}

void adicionaProdutoSistema()
{
  char desc[63];
  int preco;
  int peso;
  int qtd;
  for (int desc_index = 0; desc_index < 10; desc_index++)
  {
    desc[desc_index] = new_sym_var(sizeof(char) * 8);
  }

  desc[10 - 1] = '\0';
  preco = new_sym_var(sizeof(int) * 8);
  peso = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  conta_p++;
  strcpy(produtos[conta_p].desc, desc);
  produtos[conta_p].preco = preco;
  produtos[conta_p].peso = peso;
  produtos[conta_p].stock = qtd;
  printf("Novo produto %d.\n", conta_p);
}

void adicionaStock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if ((idp > conta_p) || (idp < 0))
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  produtos[idp].stock += qtd;
}

void criaEncomenda()
{
  conta_e++;
  printf("Nova encomenda %d.\n", conta_e);
}

void removeStock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if ((idp > conta_p) || (idp < 0))
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    if (produtos[idp].stock < qtd)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
      }
    }
    else
    {
      
    }

  }

  produtos[idp].stock -= qtd;
}

int calculaPeso(int ide)
{
  int i;
  int peso = 0;
  for (i = 0; i < 200; i++)
    if (encomendas[ide][i][0] != (-1))
  {
    peso += produtos[encomendas[ide][i][0]].peso * encomendas[ide][i][1];
  }
  else
  {
    
  }


  return peso;
}

void adicionaProdutoEncomenda()
{
  int ide;
  int idp;
  int qtd;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if ((idp > conta_p) || (idp < 0))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    if ((ide > conta_e) || (ide < 0))
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
      }
    }
    else
    {
      if (produtos[idp].stock < qtd)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
          return;
        }
      }
      else
      {
        if ((calculaPeso(ide) + (produtos[idp].peso * qtd)) > 200)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            return;
          }
        }
        else
        {
          
        }

      }

    }

  }

  for (i = 0; i < 200; i++)
    if (encomendas[ide][i][0] == idp)
  {
    {
      encomendas[ide][i][1] += qtd;
      produtos[idp].stock -= qtd;
      return;
    }
  }
  else
  {
    
  }


  for (i = 0; i < 200; i++)
    if (encomendas[ide][i][0] == (-1))
  {
    {
      encomendas[ide][i][0] = idp;
      encomendas[ide][i][1] = qtd;
      produtos[idp].stock -= qtd;
      return;
    }
  }
  else
  {
    
  }


}

void removeProdutoEncomenda()
{
  int ide;
  int idp;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if ((ide > conta_e) || (ide < 0))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    if ((idp > conta_p) || (idp < 0))
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
      }
    }
    else
    {
      
    }

  }

  for (i = 0; i < 200; i++)
    if (encomendas[ide][i][0] == idp)
  {
    {
      encomendas[ide][i][0] = -1;
      produtos[idp].stock += encomendas[ide][i][1];
      return;
    }
  }
  else
  {
    
  }


}

void calculaCusto()
{
  int ide;
  int i;
  long int custo = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if ((ide > conta_e) || (ide < 0))
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < 200; i++)
    if (encomendas[ide][i][0] != (-1))
  {
    custo += produtos[encomendas[ide][i][0]].preco * encomendas[ide][i][1];
  }
  else
  {
    
  }


  printf("Custo da encomenda %d %ld.\n", ide, custo);
}

void alteraPreco()
{
  int idp;
  int novo_preco;
  idp = new_sym_var(sizeof(int) * 8);
  novo_preco = new_sym_var(sizeof(int) * 8);
  if ((idp > conta_p) || (idp < 0))
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  produtos[idp].preco = novo_preco;
}

void listaProdutoNaEncomenda()
{
  int ide;
  int idp;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if ((ide > conta_e) || (ide < 0))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    if ((idp > conta_p) || (idp < 0))
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
      }
    }
    else
    {
      
    }

  }

  for (i = 0; i < 200; i++)
    if (encomendas[ide][i][0] == idp)
  {
    {
      printf("%s %d.\n", produtos[idp].desc, encomendas[ide][i][1]);
      return;
    }
  }
  else
  {
    
  }


  printf("%s %d.\n", produtos[idp].desc, 0);
}

void listaEncomendaComMaiorFrequencia()
{
  int idp;
  int i;
  int j;
  int maior_qtd = -1;
  int enc_a_listar;
  int encontrou_produto = 0;
  if (conta_e < 0)
  {
    return;
  }
  else
  {
    
  }

  idp = new_sym_var(sizeof(int) * 8);
  if ((idp > conta_p) || (idp < 0))
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < 500; i++)
    for (j = 0; j < 200; j++)
    if ((encomendas[i][j][0] == idp) && (encomendas[i][j][1] > maior_qtd))
  {
    {
      maior_qtd = encomendas[i][j][1];
      enc_a_listar = i;
      encontrou_produto = 1;
    }
  }
  else
  {
    
  }



  if (encontrou_produto == 1)
  {
    printf("Maximo produto %d %d %d.\n", idp, enc_a_listar, maior_qtd);
  }
  else
  {
    
  }

}

void listaProdutos()
{
  produto produtos_a_ordenar[10000];
  int i;
  printf("Produtos\n");
  for (i = 0; i <= conta_p; i++)
    produtos_a_ordenar[i] = produtos[i];

  mergeSortPreco(produtos_a_ordenar, 0, conta_p);
  for (i = 0; i <= conta_p; i++)
    printf("* %s %d %d\n", produtos_a_ordenar[i].desc, produtos_a_ordenar[i].preco, produtos_a_ordenar[i].stock);

}

void listaEncomenda()
{
  int ide;
  int i = 0;
  int j = 0;
  produto produtos_a_ordenar[200];
  ide = new_sym_var(sizeof(int) * 8);
  if ((ide > conta_e) || (ide < 0))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    
  }

  printf("Encomenda %d\n", ide);
  while (i < 200)
  {
    if (encomendas[ide][i][0] != (-1))
    {
      {
        produtos_a_ordenar[j] = produtos[encomendas[ide][i][0]];
        produtos_a_ordenar[j].stock = encomendas[ide][i][1];
        j++;
      }
    }
    else
    {
      
    }

    i++;
  }

  mergeSortDescricao(produtos_a_ordenar, 0, j - 1);
  for (i = 0; i < j; i++)
    printf("* %s %d %d\n", produtos_a_ordenar[i].desc, produtos_a_ordenar[i].preco, produtos_a_ordenar[i].stock);

}

int main()
{
  char command;
  inicializaEncomendas();
  while ((command = getchar()) != 'x')
  {
    switch (command)
    {
      case 'a':
        adicionaProdutoSistema();
        break;

      case 'q':
        adicionaStock();
        break;

      case 'N':
        criaEncomenda();
        break;

      case 'A':
        adicionaProdutoEncomenda();
        break;

      case 'r':
        removeStock();
        break;

      case 'R':
        removeProdutoEncomenda();
        break;

      case 'C':
        calculaCusto();
        break;

      case 'p':
        alteraPreco();
        break;

      case 'E':
        listaProdutoNaEncomenda();
        break;

      case 'm':
        listaEncomendaComMaiorFrequencia();
        break;

      case 'l':
        listaProdutos();
        break;

      case 'L':
        listaEncomenda();
        break;

    }

  }

  return 0;
}

