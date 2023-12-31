#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  char descricao[64];
  int preco;
  int peso;
  int quantidade;
} tipo_produto;
typedef struct 
{
  int lista_produtos[200][2];
  int n_produtos;
  int peso;
} tipo_encomenda;
int max_idp;
tipo_produto produtos[10000];
int max_ide;
tipo_encomenda encomendas[500];
int EncontraProduto_Encomenda(int ide, int idp)
{
  int i;
  int posicao = -1;
  int n_produtos;
  n_produtos = encomendas[ide].n_produtos;
  for (i = 0; i < n_produtos; i++)
  {
    if (encomendas[ide].lista_produtos[i][0] == idp)
    {
      posicao = i;
      break;
    }
    else
    {
      
    }

  }

  return posicao;
}

int Compara(int idp_a, int idp_b, int modo)
{
  int resultado = 0;
  if (modo == 0)
  {
    if (produtos[idp_a].preco < produtos[idp_b].preco)
    {
      resultado = -1;
    }
    else
    {
      if (produtos[idp_a].preco > produtos[idp_b].preco)
      {
        resultado = 1;
      }
      else
      {
        
      }

    }

  }
  else
  {
    if (modo == 1)
    {
      if (strcmp(produtos[idp_a].descricao, produtos[idp_b].descricao) < 0)
      {
        resultado = -1;
      }
      else
      {
        resultado = 1;
      }

    }
    else
    {
      
    }

  }

  return resultado;
}

void Merge(int vetor[10000], int esq, int meio, int dir, int modo)
{
  int i;
  int r;
  int k;
  int res;
  int vetor_aux[10000];
  for (i = meio + 1; i > esq; i--)
  {
    vetor_aux[i - 1] = vetor[i - 1];
  }

  for (r = meio; r < dir; r++)
  {
    vetor_aux[(dir + meio) - r] = vetor[r + 1];
  }

  for (k = esq; k <= dir; k++)
  {
    res = Compara(vetor_aux[r], vetor_aux[i], modo);
    if (res == (-1))
    {
      vetor[k] = vetor_aux[r--];
    }
    else
    {
      if (res == 1)
      {
        vetor[k] = vetor_aux[i++];
      }
      else
      {
        if (vetor_aux[r] < vetor_aux[i])
        {
          vetor[k] = vetor_aux[r--];
        }
        else
        {
          vetor[k] = vetor_aux[i++];
        }

      }

    }

  }

}

void MergeSort(int vetor[10000], int esq, int dir, int modo)
{
  int meio = (esq + dir) / 2;
  if (dir <= esq)
  {
    return;
  }
  else
  {
    
  }

  MergeSort(vetor, esq, meio, modo);
  MergeSort(vetor, meio + 1, dir, modo);
  Merge(vetor, esq, meio, dir, modo);
}

void NovoProduto(void)
{
  for (int produtos_index = 0; produtos_index < 10; produtos_index++)
  {
    produtos[max_idp].descricao[produtos_index] = new_sym_var(sizeof(char) * 8);
  }

  produtos[max_idp].descricao[10 - 1] = '\0';
  produtos[max_idp].preco = new_sym_var(sizeof(int) * 8);
  produtos[max_idp].peso = new_sym_var(sizeof(int) * 8);
  produtos[max_idp].quantidade = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", max_idp);
  max_idp++;
}

void AdicionaProduto(int idp, int qtd)
{
  if (idp >= max_idp)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    produtos[idp].quantidade += qtd;
  }

}

void RemoveProduto(int idp, int qtd)
{
  if (idp >= max_idp)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (qtd > produtos[idp].quantidade)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      produtos[idp].quantidade -= qtd;
    }

  }

}

void AlteraPreco(void)
{
  int idp;
  int novo_preco;
  idp = new_sym_var(sizeof(int) * 8);
  novo_preco = new_sym_var(sizeof(int) * 8);
  if (idp >= max_idp)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    produtos[idp].preco = novo_preco;
  }

}

void CriaEncomenda()
{
  printf("Nova encomenda %d.\n", max_ide);
  max_ide++;
}

void AdicionaProduto_Encomenda()
{
  int ide;
  int idp;
  int qtd;
  int peso;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  peso = encomendas[ide].peso + (produtos[idp].peso * qtd);
  if (ide >= max_ide)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= max_idp)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (qtd > produtos[idp].quantidade)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if (peso > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          int posicao;
          int n_produtos;
          n_produtos = encomendas[ide].n_produtos;
          if ((posicao = EncontraProduto_Encomenda(ide, idp)) != (-1))
          {
            encomendas[ide].lista_produtos[posicao][1] += qtd;
          }
          else
          {
            encomendas[ide].lista_produtos[n_produtos][0] = idp;
            encomendas[ide].lista_produtos[n_produtos][1] = qtd;
            encomendas[ide].n_produtos++;
          }

          RemoveProduto(idp, qtd);
          encomendas[ide].peso = peso;
        }

      }

    }

  }

}

void RemoveProduto_Encomenda()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= max_ide)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= max_idp)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      int n_produtos;
      int posicao;
      int qtd;
      if ((posicao = EncontraProduto_Encomenda(ide, idp)) != (-1))
      {
        qtd = encomendas[ide].lista_produtos[posicao][1];
        encomendas[ide].peso -= qtd * produtos[idp].peso;
        --encomendas[ide].n_produtos;
        n_produtos = encomendas[ide].n_produtos;
        for (; posicao < n_produtos; posicao++)
        {
          encomendas[ide].lista_produtos[posicao][0] = encomendas[ide].lista_produtos[posicao + 1][0];
          encomendas[ide].lista_produtos[posicao][1] = encomendas[ide].lista_produtos[posicao + 1][1];
        }

        AdicionaProduto(idp, qtd);
      }
      else
      {
        
      }

    }

  }

}

void EncomendaProduto_MaiorQuantidade()
{
  int idp;
  int ide;
  int posicao;
  int qtd;
  int maior_ide = 0;
  int maior_qtd = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= max_idp)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (ide = 0; ide < max_ide; ide++)
    {
      if ((posicao = EncontraProduto_Encomenda(ide, idp)) != (-1))
      {
        qtd = encomendas[ide].lista_produtos[posicao][1];
        if (qtd > maior_qtd)
        {
          maior_qtd = qtd;
          maior_ide = ide;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

    if (maior_qtd != 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, maior_ide, maior_qtd);
    }
    else
    {
      
    }

  }

}

void ProdutoEmEncomenda()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= max_ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp >= max_idp)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      int qtd = 0;
      int posicao;
      if ((posicao = EncontraProduto_Encomenda(ide, idp)) != (-1))
      {
        qtd = encomendas[ide].lista_produtos[posicao][1];
      }
      else
      {
        
      }

      printf("%s %d.\n", produtos[idp].descricao, qtd);
    }

  }

}

void PrecoEncomenda(void)
{
  int i;
  int ide;
  int idp;
  int n_produtos;
  int qtd;
  int preco;
  int total = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= max_ide)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    n_produtos = encomendas[ide].n_produtos;
    for (i = 0; i < n_produtos; i++)
    {
      idp = encomendas[ide].lista_produtos[i][0];
      qtd = encomendas[ide].lista_produtos[i][1];
      preco = produtos[idp].preco;
      total += qtd * preco;
    }

    printf("Custo da encomenda %d %d.\n", ide, total);
  }

}

void OrdenaProdutos()
{
  int produtos_copia[10000];
  int idp;
  int i;
  for (i = 0; i < max_idp; i++)
  {
    produtos_copia[i] = i;
  }

  MergeSort(produtos_copia, 0, max_idp - 1, 0);
  printf("Produtos\n");
  for (i = 0; i < max_idp; i++)
  {
    idp = produtos_copia[i];
    printf("* %s %d %d\n", produtos[idp].descricao, produtos[idp].preco, produtos[idp].quantidade);
  }

}

void OrdenaProdutos_Encomenda()
{
  int ide;
  int lista_produtos_copia[200];
  int n_produtos;
  int idp;
  int qtd;
  int i;
  int r;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= max_ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    n_produtos = encomendas[ide].n_produtos;
    for (i = 0; i < n_produtos; i++)
    {
      lista_produtos_copia[i] = encomendas[ide].lista_produtos[i][0];
    }

    MergeSort(lista_produtos_copia, 0, n_produtos - 1, 1);
    printf("Encomenda %d\n", ide);
    for (i = 0; i < n_produtos; i++)
    {
      idp = lista_produtos_copia[i];
      for (r = 0; r < n_produtos; r++)
      {
        if (encomendas[ide].lista_produtos[r][0] == idp)
        {
          qtd = encomendas[ide].lista_produtos[r][1];
        }
        else
        {
          
        }

      }

      printf("* %s %d %d\n", produtos[idp].descricao, produtos[idp].preco, qtd);
    }

  }

}

int main()
{
  int idp;
  int qtd;
  int fim = 0;
  char comando;
  while (fim == 0)
  {
    switch (comando = getchar())
    {
      case 'x':
      {
        fim = 1;
        break;
      }

      case 'a':
      {
        NovoProduto();
        break;
      }

      case 'q':
      {
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        AdicionaProduto(idp, qtd);
        break;
      }

      case 'r':
      {
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        RemoveProduto(idp, qtd);
        break;
      }

      case 'p':
      {
        AlteraPreco();
        break;
      }

      case 'N':
      {
        CriaEncomenda();
        break;
      }

      case 'A':
      {
        AdicionaProduto_Encomenda();
        break;
      }

      case 'R':
      {
        RemoveProduto_Encomenda();
        break;
      }

      case 'm':
      {
        EncomendaProduto_MaiorQuantidade();
        break;
      }

      case 'E':
      {
        ProdutoEmEncomenda();
        break;
      }

      case 'C':
      {
        PrecoEncomenda();
        break;
      }

      case 'l':
      {
        OrdenaProdutos();
        break;
      }

      case 'L':
      {
        OrdenaProdutos_Encomenda();
        break;
      }

    }

  }

  return 0;
}

