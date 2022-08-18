/*File generated by PreProcessor.py*/


#include <stdio.h> 
#include <string.h>
#include <stdlib.h>


typedef struct 
{
  char descricao[64];
  int preco;
  int peso;
  int quantidade;
  int guarda_ids;
} Produto;
typedef struct 
{
  int ide_encomenda;
  Produto idp_encomenda[10000];
  int qtd_produtos;
  int peso_encomenda;
  int preco_encomenda;
} Encomenda;
Produto sistema[10000];
int contproduto = 0;
Encomenda encomenda[500];
int contencom = 0;
void adiciona_produto();
void adiciona_stock();
void lista_produto();
void altera_preco();
void remove_stock();
void nova_encomenda();
void adiciona_produto_encomenda();
void calcula_preco_encomenda();
void lista_desc_qtd();
void remove_produto_encomenda();
void maior_quantidade_produto_encomenda();
void lista_produtos_encomenda();
int main()
{
  char comando;
  while (1)
  {
    comando = getchar();
    switch (comando)
    {
      case 'x':
        return 0;

      case 'a':
        adiciona_produto();
        break;

      case 'q':
        adiciona_stock();
        break;

      case 'l':
        lista_produto();
        break;

      case 'p':
        altera_preco();
        break;

      case 'r':
        remove_stock();
        break;

      case 'N':
        nova_encomenda();
        break;

      case 'A':
        adiciona_produto_encomenda();
        break;

      case 'C':
        calcula_preco_encomenda();
        break;

      case 'E':
        lista_desc_qtd();
        break;

      case 'R':
        remove_produto_encomenda();
        break;

      case 'm':
        maior_quantidade_produto_encomenda();
        break;

      case 'L':
        lista_produtos_encomenda();
        break;

    }

    getchar();
  }

  return 0;
}

void adiciona_produto()
{
  Produto novo;
  for (int novo_index = 0; novo_index < 10; novo_index++)
  {
    novo.descricao[novo_index] = new_sym_var(sizeof(char) * 8);
  }

  novo.descricao[10 - 1] = '\0';
  novo.preco = new_sym_var(sizeof(int) * 8);
  novo.peso = new_sym_var(sizeof(int) * 8);
  novo.quantidade = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", contproduto);
  sistema[contproduto] = novo;
  contproduto++;
}

void adiciona_stock()
{
  int stock;
  int idp;
  idp = new_sym_var(sizeof(int) * 8);
  stock = new_sym_var(sizeof(int) * 8);
  if (idp >= contproduto)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  sistema[idp].quantidade = sistema[idp].quantidade + stock;
}

void remove_stock()
{
  int remove;
  int idp;
  idp = new_sym_var(sizeof(int) * 8);
  remove = new_sym_var(sizeof(int) * 8);
  if (idp >= contproduto)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  if (remove > sistema[idp].quantidade)
  {
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", remove, idp);
      return;
    }
  }
  else
  {
    
  }

  sistema[idp].quantidade = sistema[idp].quantidade - remove;
}

void merge(Produto vetor[], int inicio1, int j1, int inicio2, int j2)
{
  Produto guarda_todos[10000];
  int i;
  int j;
  int k = 0;
  i = inicio1;
  j = inicio2;
  while ((i <= j1) && (j <= j2))
  {
    if (vetor[i].preco <= vetor[j].preco)
    {
      guarda_todos[k++] = vetor[i++];
    }
    else
    {
      guarda_todos[k++] = vetor[j++];
    }

  }

  while (i <= j1)
    guarda_todos[k++] = vetor[i++];

  while (j <= j2)
    guarda_todos[k++] = vetor[j++];

  for (i = inicio1, j = 0; i <= j2; i++, j++)
    vetor[i] = guarda_todos[j];

}

void mergesort(Produto vetor[], int i, int j)
{
  int meio;
  if (i < j)
  {
    {
      meio = (i + j) / 2;
      mergesort(vetor, i, meio);
      mergesort(vetor, meio + 1, j);
      merge(vetor, i, meio, meio + 1, j);
    }
  }
  else
  {
    
  }

}

void lista_produto()
{
  Produto array[10000];
  int i;
  for (i = 0; i < contproduto; i++)
  {
    array[i].preco = sistema[i].preco;
    array[i].guarda_ids = i;
  }

  mergesort(array, 0, contproduto - 1);
  printf("Produtos\n");
  for (i = 0; i < contproduto; i++)
  {
    printf("* %s %d %d\n", sistema[array[i].guarda_ids].descricao, sistema[array[i].guarda_ids].preco, sistema[array[i].guarda_ids].quantidade);
  }

}

void nova_encomenda()
{
  printf("Nova encomenda %d.\n", contencom);
  contencom++;
}

void altera_preco()
{
  int idp;
  int novoPreco;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  novoPreco = new_sym_var(sizeof(int) * 8);
  if (idp >= contproduto)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < contencom; i++)
  {
    if (sistema[idp].preco == encomenda[i].idp_encomenda[idp].preco)
    {
      {
        encomenda[i].idp_encomenda[idp].preco = novoPreco;
      }
    }
    else
    {
      
    }

  }

  sistema[idp].preco = novoPreco;
}

void adiciona_produto_encomenda()
{
  int idp;
  int ide;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ide >= contencom)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  if (idp >= contproduto)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  if ((sistema[idp].quantidade == 0) || (sistema[idp].quantidade < qtd))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  if ((encomenda[ide].peso_encomenda + (sistema[idp].peso * qtd)) > 200)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  encomenda[ide].peso_encomenda += sistema[idp].peso * qtd;
  sistema[idp].quantidade = sistema[idp].quantidade - qtd;
  encomenda[ide].idp_encomenda[idp].quantidade += qtd;
  encomenda[ide].idp_encomenda[idp].preco = sistema[idp].preco;
  strcpy(encomenda[ide].idp_encomenda[idp].descricao, sistema[idp].descricao);
}

void calcula_preco_encomenda()
{
  int ide;
  int i;
  int preco = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= contencom)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < contproduto; i++)
  {
    if (encomenda[ide].idp_encomenda[i].preco == sistema[i].preco)
    {
      {
        preco += encomenda[ide].idp_encomenda[i].preco * encomenda[ide].idp_encomenda[i].quantidade;
      }
    }
    else
    {
      
    }

  }

  printf("Custo da encomenda %d %d.\n", ide, preco);
}

void lista_desc_qtd()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= contencom)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    
  }

  if (idp >= contproduto)
  {
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  printf("%s %d.\n", sistema[idp].descricao, encomenda[ide].idp_encomenda[idp].quantidade);
}

void remove_produto_encomenda()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= contencom)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  if (idp >= contproduto)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  encomenda[ide].preco_encomenda -= sistema[idp].preco * encomenda[ide].idp_encomenda[idp].quantidade;
  encomenda[ide].peso_encomenda -= sistema[idp].peso * encomenda[ide].idp_encomenda[idp].quantidade;
  sistema[idp].quantidade += encomenda[ide].idp_encomenda[idp].quantidade;
  encomenda[ide].idp_encomenda[idp].quantidade = 0;
}

void maior_quantidade_produto_encomenda()
{
  int idp;
  int i;
  int maior = 0;
  int maior_indice = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= contproduto)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  if ((contencom == 0) || (contproduto == 0))
  {
    {
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < contencom; i++)
  {
    if ((sistema[idp].preco == encomenda[i].idp_encomenda[idp].preco) && (encomenda[i].idp_encomenda[idp].quantidade > maior))
    {
      {
        maior = encomenda[i].idp_encomenda[idp].quantidade;
        maior_indice = i;
      }
    }
    else
    {
      
    }

  }

  if (maior == 0)
  {
    return;
  }
  else
  {
    
  }

  printf("Maximo produto %d %d %d.\n", idp, maior_indice, maior);
}

void lista_produtos_encomenda()
{
  int ide;
  int i;
  int j;
  int troca_idp;
  int cont = 0;
  int array_idp[10000];
  char array_descricao[10000][64];
  char troca[64];
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= contencom)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < contproduto; i++)
  {
    if ((encomenda[ide].idp_encomenda[i].preco == sistema[i].preco) && (encomenda[ide].idp_encomenda[i].quantidade != 0))
    {
      {
        strcpy(array_descricao[cont], encomenda[ide].idp_encomenda[i].descricao);
        array_idp[cont] = i;
        cont++;
      }
    }
    else
    {
      
    }

  }

  for (j = 0; j < (cont - 1); j++)
  {
    for (i = j + 1; i < cont; i++)
    {
      if (strcmp(array_descricao[j], array_descricao[i]) > 0)
      {
        {
          strcpy(troca, array_descricao[j]);
          strcpy(array_descricao[j], array_descricao[i]);
          strcpy(array_descricao[i], troca);
          troca_idp = array_idp[j];
          array_idp[j] = array_idp[i];
          array_idp[i] = troca_idp;
        }
      }
      else
      {
        
      }

    }

  }

  printf("Encomenda %d\n", ide);
  for (i = 0; i < cont; i++)
  {
    printf("* %s %d %d\n", encomenda[ide].idp_encomenda[array_idp[i]].descricao, encomenda[ide].idp_encomenda[array_idp[i]].preco, encomenda[ide].idp_encomenda[array_idp[i]].quantidade);
  }

}

