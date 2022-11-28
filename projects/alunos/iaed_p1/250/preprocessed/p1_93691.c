#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct 
{
  int idp;
  int preco;
  int peso;
  int stock;
  char descricao[64];
} Produto;
typedef struct 
{
  int idp;
  int quantidade;
} Elemento_Encomenda;
typedef struct 
{
  Elemento_Encomenda produto[200];
  int peso;
  int max_prod_enc_atual;
} Encomenda;
char SepararInput(char input[99], char input_separado[4][64]);
void InicializarProduto(Produto lista[]);
void AdicionarNovoProduto(char input_separado[4][64], Produto lista_produtos[10000], int idp_atual);
void AdicionarStockProduto(char input_separado[4][64], Produto lista_produtos[10000], int idp_atual);
void InicializarEncomenda(Encomenda lista[]);
void CriarEncomenda(int ide_atual);
void AdicionarProdutoEncomenda(char input_separado[4][64], Encomenda lista_encomendas[500], Produto lista_produtos[10000], int ide_atual, int idp_atual);
void RemoverStockProduto(char input_separado[4][64], Produto lista_produtos[10000], int idp_atual);
void RemoverProdutoEncomenda(char input_separado[4][64], Encomenda lista_encomendas[500], Produto lista_produtos[10000], int ide_atual, int idp_atual);
void CalcularCustoEncomenda(char input_separado[4][64], Encomenda lista_encomendas[500], Produto lista_produtos[10000], int ide_atual, int idp_atual);
void AlterarPrecoProduto(char input_separado[4][64], Produto lista_produtos[10000], int idp_atual);
void ListarProdutoEncomenda(char input_separado[4][64], Encomenda lista_encomendas[500], Produto lista_produtos[10000], int ide_atual, int idp_atual);
void ListarMaxProdutoEncomenda(char input_separado[4][64], Encomenda lista_encomendas[500], int idp_atual, int ide_atual);
void MergingSistema(Produto lista_produtos[10000], int menor, int meio, int maior);
void SortSistema(Produto lista_produtos[10000], int menor, int maior);
void OrdenarProdutosSistema(int idp_atual, Produto lista_produtos[10000]);
void MergingEncomenda(Elemento_Encomenda produtos_encomenda[], Produto lista_produtos[10000], int menor, int meio, int maior);
void SortEncomenda(Elemento_Encomenda produtos_encomenda[], Produto lista_produtos[10000], int menor, int maior);
void OrdenarProdutosEncomenda(char input_separado[4][64], int ide_atual, int idp_atual, Produto lista_produtos[10000], Encomenda lista_encomendas[500]);
int main()
{
  Produto lista_produtos[10000];
  Encomenda lista_encomendas[500];
  char input[99] = "\0";
  char input_separado[4][64] = {"\0"};
  int idp_atual = 0;
  int ide_atual = 0;
  InicializarProduto(lista_produtos);
  InicializarEncomenda(lista_encomendas);
  while (1)
  {
    if (fgets(input, 99 - 1, stdin) != 0)
    {
      switch (SepararInput(input, input_separado))
      {
        case 'a':
          AdicionarNovoProduto(input_separado, lista_produtos, idp_atual);
          idp_atual++;
          break;

        case 'q':
          AdicionarStockProduto(input_separado, lista_produtos, idp_atual);
          break;

        case 'N':
          CriarEncomenda(ide_atual);
          ide_atual++;
          break;

        case 'A':
          AdicionarProdutoEncomenda(input_separado, lista_encomendas, lista_produtos, ide_atual, idp_atual);
          break;

        case 'r':
          RemoverStockProduto(input_separado, lista_produtos, idp_atual);
          break;

        case 'R':
          RemoverProdutoEncomenda(input_separado, lista_encomendas, lista_produtos, ide_atual, idp_atual);
          break;

        case 'C':
          CalcularCustoEncomenda(input_separado, lista_encomendas, lista_produtos, ide_atual, idp_atual);
          break;

        case 'p':
          AlterarPrecoProduto(input_separado, lista_produtos, idp_atual);
          break;

        case 'E':
          ListarProdutoEncomenda(input_separado, lista_encomendas, lista_produtos, ide_atual, idp_atual);
          break;

        case 'm':
          ListarMaxProdutoEncomenda(input_separado, lista_encomendas, idp_atual, ide_atual);
          break;

        case 'l':
          OrdenarProdutosSistema(idp_atual, lista_produtos);
          break;

        case 'L':
          OrdenarProdutosEncomenda(input_separado, ide_atual, idp_atual, lista_produtos, lista_encomendas);
          break;

        case 'x':
          return 0;
          break;

      }

    }
    else
    {
      
    }

  }

  return 0;
}

char SepararInput(char input[99], char input_separado[4][64])
{
  int a = 0;
  int i = 0;
  char *token = strtok(input, " ");
  char comando = *token;
  token = strtok(0, ":");
  for (a = 0; a < 4; a++)
    strcpy(input_separado[a], "\0");

  while (token != 0)
  {
    strcpy(input_separado[i], token);
    token = strtok(0, ":");
    i++;
  }

  return comando;
}

void InicializarProduto(Produto lista[])
{
  int prod;
  for (prod = 0; prod < 10000; prod++)
  {
    lista[prod].idp = -1;
    lista[prod].preco = 0;
    lista[prod].peso = 0;
    lista[prod].stock = 0;
    lista[prod].descricao[0] = '\0';
  }

}

void AdicionarNovoProduto(char input_separado[4][64], Produto lista_produtos[10000], int idp_atual)
{
  int preco = atoi(input_separado[1]);
  int peso = atoi(input_separado[2]);
  int qtd = atoi(input_separado[3]);
  if (idp_atual == 10000)
  {
    return;
  }
  else
  {
    
  }

  strcpy(lista_produtos[idp_atual].descricao, input_separado[0]);
  lista_produtos[idp_atual].idp = idp_atual;
  lista_produtos[idp_atual].preco = preco;
  lista_produtos[idp_atual].peso = peso;
  lista_produtos[idp_atual].stock = qtd;
  printf("Novo produto %d.\n", idp_atual);
}

void AdicionarStockProduto(char input_separado[4][64], Produto lista_produtos[10000], int idp_atual)
{
  int idp = atoi(input_separado[0]);
  int qtd = atoi(input_separado[1]);
  int id_prod;
  for (id_prod = 0; id_prod < idp_atual; id_prod++)
  {
    if (idp == lista_produtos[id_prod].idp)
    {
      lista_produtos[id_prod].stock += qtd;
      return;
    }
    else
    {
      
    }

  }

  printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

void InicializarEncomenda(Encomenda lista[])
{
  int enc;
  int prod;
  for (enc = 0; enc < 500; enc++)
  {
    for (prod = 0; prod < 200; prod++)
    {
      lista[enc].produto[prod].idp = -1;
      lista[enc].produto[prod].quantidade = 0;
    }

    lista[enc].peso = 0;
    lista[enc].max_prod_enc_atual = 0;
  }

}

void CriarEncomenda(int ide_atual)
{
  if (ide_atual == 500)
  {
    return;
  }
  else
  {
    
  }

  printf("Nova encomenda %d.\n", ide_atual);
}

void AdicionarProdutoEncomenda(char input_separado[4][64], Encomenda lista_encomendas[500], Produto lista_produtos[10000], int ide_atual, int idp_atual)
{
  int ide = atoi(input_separado[0]);
  int idp = atoi(input_separado[1]);
  int qtd = atoi(input_separado[2]);
  int prod;
  int id_prod;
  if (ide < ide_atual)
  {
    if (idp < idp_atual)
    {
      for (id_prod = 0; id_prod < idp_atual; id_prod++)
      {
        if (idp == lista_produtos[id_prod].idp)
        {
          break;
        }
        else
        {
          
        }

      }

      if (lista_produtos[id_prod].stock >= qtd)
      {
        if ((lista_encomendas[ide].peso + (qtd * lista_produtos[id_prod].peso)) <= 200)
        {
          for (prod = 0; prod < lista_encomendas[ide].max_prod_enc_atual; prod++)
          {
            if (idp == lista_encomendas[ide].produto[prod].idp)
            {
              lista_encomendas[ide].produto[prod].quantidade += qtd;
              lista_encomendas[ide].peso += qtd * lista_produtos[id_prod].peso;
              lista_produtos[id_prod].stock -= qtd;
              return;
            }
            else
            {
              
            }

          }

          for (prod = 0; prod < (lista_encomendas[ide].max_prod_enc_atual + 1); prod++)
          {
            if (lista_encomendas[ide].produto[prod].idp == (-1))
            {
              lista_encomendas[ide].produto[prod].idp = idp;
              lista_encomendas[ide].produto[prod].quantidade += qtd;
              lista_encomendas[ide].peso += qtd * lista_produtos[id_prod].peso;
              if (prod >= lista_encomendas[ide].max_prod_enc_atual)
              {
                lista_encomendas[ide].max_prod_enc_atual++;
              }
              else
              {
                
              }

              lista_produtos[id_prod].stock -= qtd;
              return;
            }
            else
            {
              
            }

          }

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

  return;
}

void RemoverStockProduto(char input_separado[4][64], Produto lista_produtos[10000], int idp_atual)
{
  int idp = atoi(input_separado[0]);
  int qtd = atoi(input_separado[1]);
  int id_prod;
  for (id_prod = 0; id_prod < idp_atual; id_prod++)
  {
    if (lista_produtos[id_prod].idp == idp)
    {
      if (qtd <= lista_produtos[id_prod].stock)
      {
        lista_produtos[id_prod].stock -= qtd;
      }
      else
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
      }

      return;
    }
    else
    {
      
    }

  }

  printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}

void RemoverProdutoEncomenda(char input_separado[4][64], Encomenda lista_encomendas[500], Produto lista_produtos[10000], int ide_atual, int idp_atual)
{
  int ide = atoi(input_separado[0]);
  int idp = atoi(input_separado[1]);
  int prod;
  int id_prod;
  if (ide < ide_atual)
  {
    if (idp < idp_atual)
    {
      for (id_prod = 0; id_prod < idp_atual; id_prod++)
      {
        if (idp == lista_produtos[id_prod].idp)
        {
          break;
        }
        else
        {
          
        }

      }

      for (prod = 0; prod < lista_encomendas[ide].max_prod_enc_atual; prod++)
      {
        if (idp == lista_encomendas[ide].produto[prod].idp)
        {
          int qtd = lista_encomendas[ide].produto[prod].quantidade;
          lista_encomendas[ide].peso -= lista_produtos[id_prod].peso * qtd;
          lista_encomendas[ide].produto[prod].quantidade = 0;
          lista_encomendas[ide].produto[prod].idp = -1;
          lista_produtos[id_prod].stock += qtd;
          return;
        }
        else
        {
          
        }

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

  return;
}

void CalcularCustoEncomenda(char input_separado[4][64], Encomenda lista_encomendas[500], Produto lista_produtos[10000], int ide_atual, int idp_atual)
{
  int ide = atoi(input_separado[0]);
  int prod;
  int total = 0;
  int id_prod;
  if (ide < ide_atual)
  {
    for (prod = 0; prod < lista_encomendas[ide].max_prod_enc_atual; prod++)
    {
      for (id_prod = 0; id_prod < idp_atual; id_prod++)
      {
        if (lista_encomendas[ide].produto[prod].idp == lista_produtos[id_prod].idp)
        {
          total += lista_encomendas[ide].produto[prod].quantidade * lista_produtos[id_prod].preco;
          break;
        }
        else
        {
          
        }

      }

    }

    printf("Custo da encomenda %d %d.\n", ide, total);
    return;
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }

  return;
}

void AlterarPrecoProduto(char input_separado[4][64], Produto lista_produtos[10000], int idp_atual)
{
  int idp = atoi(input_separado[0]);
  int preco = atoi(input_separado[1]);
  int id_prod;
  for (id_prod = 0; id_prod < idp_atual; id_prod++)
  {
    if (idp == lista_produtos[id_prod].idp)
    {
      lista_produtos[id_prod].preco = preco;
      return;
    }
    else
    {
      
    }

  }

  printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}

void ListarProdutoEncomenda(char input_separado[4][64], Encomenda lista_encomendas[500], Produto lista_produtos[10000], int ide_atual, int idp_atual)
{
  int ide = atoi(input_separado[0]);
  int idp = atoi(input_separado[1]);
  int prod;
  int id_prod;
  if (ide < ide_atual)
  {
    if (idp < idp_atual)
    {
      for (id_prod = 0; id_prod < idp_atual; id_prod++)
      {
        if (idp == lista_produtos[id_prod].idp)
        {
          break;
        }
        else
        {
          
        }

      }

      for (prod = 0; prod < lista_encomendas[ide].max_prod_enc_atual; prod++)
      {
        if (idp == lista_encomendas[ide].produto[prod].idp)
        {
          printf("%s %d.\n", lista_produtos[id_prod].descricao, lista_encomendas[ide].produto[prod].quantidade);
          return;
        }
        else
        {
          
        }

      }

      printf("%s %d.\n", lista_produtos[id_prod].descricao, 0);
      return;
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

  return;
}

void ListarMaxProdutoEncomenda(char input_separado[4][64], Encomenda lista_encomendas[500], int idp_atual, int ide_atual)
{
  int idp = atoi(input_separado[0]);
  int prod;
  int enc;
  int max[3] = {0, 0, -1};
  max[0] = idp;
  if (ide_atual == 0)
  {
    return;
  }
  else
  {
    
  }

  if (idp < idp_atual)
  {
    for (enc = 0; enc < ide_atual; enc++)
    {
      for (prod = 0; prod < lista_encomendas[enc].max_prod_enc_atual; prod++)
      {
        if (idp == lista_encomendas[enc].produto[prod].idp)
        {
          if (lista_encomendas[enc].produto[prod].quantidade > max[2])
          {
            max[1] = enc;
            max[2] = lista_encomendas[enc].produto[prod].quantidade;
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

    if (max[2] != (-1))
    {
      printf("Maximo produto %d %d %d.\n", max[0], max[1], max[2]);
      return;
    }
    else
    {
      
    }

  }
  else
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }

  return;
}

void MergingSistema(Produto lista_produtos[10000], int menor, int meio, int maior)
{
  int i;
  int j;
  int k;
  int n1 = (meio - menor) + 1;
  int n2 = maior - meio;
  Produto esq[10000 / 2];
  Produto drt[10000 / 2];
  for (i = 0; i < n1; i++)
    esq[i] = lista_produtos[menor + i];

  for (j = 0; j < n2; j++)
    drt[j] = lista_produtos[(meio + 1) + j];

  i = 0;
  j = 0;
  k = menor;
  while ((i < n1) && (j < n2))
  {
    if (esq[i].preco < drt[j].preco)
    {
      lista_produtos[k] = esq[i];
      i++;
    }
    else
    {
      if ((esq[i].preco == drt[j].preco) && (esq[i].idp < drt[j].idp))
      {
        lista_produtos[k] = esq[i];
        i++;
      }
      else
      {
        lista_produtos[k] = drt[j];
        j++;
      }

    }

    k++;
  }

  while (i < n1)
  {
    lista_produtos[k] = esq[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    lista_produtos[k] = drt[j];
    j++;
    k++;
  }

}

void SortSistema(Produto lista_produtos[10000], int menor, int maior)
{
  if (menor < maior)
  {
    int meio = menor + ((maior - menor) / 2);
    SortSistema(lista_produtos, menor, meio);
    SortSistema(lista_produtos, meio + 1, maior);
    MergingSistema(lista_produtos, menor, meio, maior);
  }
  else
  {
    
  }

}

void OrdenarProdutosSistema(int idp_atual, Produto lista_produtos[10000])
{
  int prod;
  SortSistema(lista_produtos, 0, idp_atual - 1);
  printf("Produtos\n");
  for (prod = 0; prod < idp_atual; prod++)
    printf("* %s %d %d\n", lista_produtos[prod].descricao, lista_produtos[prod].preco, lista_produtos[prod].stock);

}

void MergingEncomenda(Elemento_Encomenda produtos_encomenda[], Produto lista_produtos[10000], int menor, int meio, int maior)
{
  int i;
  int j;
  int k;
  int prod1;
  int prod2;
  int n1 = (meio - menor) + 1;
  int n2 = maior - meio;
  Elemento_Encomenda esq[200 / 2];
  Elemento_Encomenda drt[200 / 2];
  for (i = 0; i < n1; i++)
    esq[i] = produtos_encomenda[menor + i];

  for (j = 0; j < n2; j++)
    drt[j] = produtos_encomenda[(meio + 1) + j];

  i = 0;
  j = 0;
  k = menor;
  while ((i < n1) && (j < n2))
  {
    for (prod1 = 0; prod1 < 10000; prod1++)
    {
      if (esq[i].idp == lista_produtos[prod1].idp)
      {
        break;
      }
      else
      {
        
      }

    }

    for (prod2 = 0; prod2 < 10000; prod2++)
    {
      if (drt[j].idp == lista_produtos[prod2].idp)
      {
        break;
      }
      else
      {
        
      }

    }

    if (strcmp(lista_produtos[prod2].descricao, lista_produtos[prod1].descricao) > 0)
    {
      produtos_encomenda[k] = esq[i];
      i++;
    }
    else
    {
      produtos_encomenda[k] = drt[j];
      j++;
    }

    k++;
  }

  while (i < n1)
  {
    produtos_encomenda[k] = esq[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    produtos_encomenda[k] = drt[j];
    j++;
    k++;
  }

}

void SortEncomenda(Elemento_Encomenda produtos_encomenda[], Produto lista_produtos[10000], int menor, int maior)
{
  if (menor < maior)
  {
    int meio = menor + ((maior - menor) / 2);
    SortEncomenda(produtos_encomenda, lista_produtos, menor, meio);
    SortEncomenda(produtos_encomenda, lista_produtos, meio + 1, maior);
    MergingEncomenda(produtos_encomenda, lista_produtos, menor, meio, maior);
  }
  else
  {
    
  }

}

void OrdenarProdutosEncomenda(char input_separado[4][64], int ide_atual, int idp_atual, Produto lista_produtos[10000], Encomenda lista_encomendas[500])
{
  int ide = atoi(input_separado[0]);
  int prod;
  int id_prod;
  int k = 0;
  if (ide < ide_atual)
  {
    Elemento_Encomenda produtos_encomenda[200];
    for (prod = 0; prod < lista_encomendas[ide].max_prod_enc_atual; prod++)
    {
      if (lista_encomendas[ide].produto[prod].idp != (-1))
      {
        produtos_encomenda[k] = lista_encomendas[ide].produto[prod];
        k++;
      }
      else
      {
        
      }

    }

    SortEncomenda(produtos_encomenda, lista_produtos, 0, k - 1);
    printf("Encomenda %d\n", ide);
    for (prod = 0; prod < k; prod++)
    {
      for (id_prod = 0; id_prod < idp_atual; id_prod++)
      {
        if (produtos_encomenda[prod].idp == lista_produtos[id_prod].idp)
        {
          break;
        }
        else
        {
          
        }

      }

      printf("* %s %d %d\n", lista_produtos[id_prod].descricao, lista_produtos[id_prod].preco, produtos_encomenda[prod].quantidade);
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }

  return;
}
