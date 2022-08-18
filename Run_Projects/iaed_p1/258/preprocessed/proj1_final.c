/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>


struct produto
{
  int id;
  char descricao[64];
  int preco;
  int peso;
  int quantStock;
  int quantNecessaria;
};
struct prodEnc
{
  int id;
  int quant;
};
struct encomenda
{
  int id;
  int numProdutos;
  struct prodEnc listaProdutos[200];
};
int dados[4];
char dado1[64];
struct produto produtos[10000];
int quantProd = 0;
struct encomenda encomendas[500];
int quantEnc = 0;
void processaDados();
void trocaProdutos(int i);
void sortProdutos();
void trocaListaProdutos(struct prodEnc listaProdutos[], int i);
void sortListaProdutos(struct prodEnc listaProdutos[], int size);
int procuraProduto(int idP);
int procuraEncomenda(int idE);
int calculaPeso(int indE);
int calculaCusto(int indE);
void adicionaListaProdutos(int idP, int indE, int quant);
void troca(int indP, struct prodEnc listaProdutos[], int size);
void removeListaProdutos(int idP, int indE);
void comando_a();
void comando_q();
void comando_N();
void comando_A();
void comando_r();
void comando_R();
void comando_C();
void comando_p();
void comando_E();
void comando_m();
void comando_l();
void comando_L();
void processaDados()
{
  int i = 0;
  char input[200];
  char *token;
  getchar();
  fgets(input, 200, stdin);
  token = strtok(input, ":\n");
  strcpy(dado1, token);
  while (token != 0)
  {
    token = strtok(0, ":\n");
    if (token != 0)
    {
      {
        dados[i] = atoi(token);
        i++;
      }
    }
    else
    {
      
    }

  }

}

void trocaProdutos(int i)
{
  struct produto temp;
  temp = produtos[i];
  produtos[i] = produtos[i + 1];
  produtos[i + 1] = temp;
}

void sortProdutos()
{
  int i;
  for (i = 0; i < (quantProd - 1); i++)
  {
    if (produtos[i].preco > produtos[i + 1].preco)
    {
      {
        trocaProdutos(i);
        while ((produtos[i - 1].preco >= produtos[i].preco) && (i > 0))
        {
          if (produtos[i - 1].preco > produtos[i].preco)
          {
            {
              trocaProdutos(i - 1);
            }
          }
          else
          {
            if ((produtos[i].preco == produtos[i - 1].preco) && (produtos[i - 1].id > produtos[i].id))
            {
              {
                trocaProdutos(i - 1);
              }
            }
            else
            {
              
            }

          }

          i--;
        }

      }
    }
    else
    {
      if ((produtos[i].preco == produtos[i + 1].preco) && (produtos[i].id > produtos[i + 1].id))
      {
        {
          trocaProdutos(i);
        }
      }
      else
      {
        
      }

    }

  }

}

void trocaListaProdutos(struct prodEnc listaProdutos[], int i)
{
  struct prodEnc temp;
  temp = listaProdutos[i];
  listaProdutos[i] = listaProdutos[i + 1];
  listaProdutos[i + 1] = temp;
}

void sortListaProdutos(struct prodEnc listaProdutos[], int size)
{
  int i;
  int mudanca = 1;
  int indP1;
  int indP2;
  if (size < 2)
  {
    return;
  }
  else
  {
    
  }

  while (mudanca)
  {
    mudanca = 0;
    indP2 = procuraProduto(listaProdutos[0].id);
    for (i = 0; i < (size - 1); i++)
    {
      indP1 = indP2;
      indP2 = procuraProduto(listaProdutos[i + 1].id);
      if (strcmp(produtos[indP1].descricao, produtos[indP2].descricao) > 0)
      {
        {
          trocaListaProdutos(listaProdutos, i);
          mudanca = 1;
        }
      }
      else
      {
        
      }

    }

  }

}

int procuraProduto(int idP)
{
  int i;
  for (i = 0; i < quantProd; i++)
  {
    if (produtos[i].id == idP)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

int procuraEncomenda(int idE)
{
  if (idE < quantEnc)
  {
    return idE;
  }
  else
  {
    
  }

  return -1;
}

int calculaPeso(int indE)
{
  int i;
  int idP;
  int indP;
  int peso = 0;
  for (i = 0; i < encomendas[indE].numProdutos; i++)
  {
    idP = encomendas[indE].listaProdutos[i].id;
    indP = procuraProduto(idP);
    peso += encomendas[indE].listaProdutos[i].quant * produtos[indP].peso;
  }

  return peso;
}

int calculaCusto(int indE)
{
  int i;
  int indP;
  int custo = 0;
  for (i = 0; i < encomendas[indE].numProdutos; i++)
  {
    indP = procuraProduto(encomendas[indE].listaProdutos[i].id);
    custo += encomendas[indE].listaProdutos[i].quant * produtos[indP].preco;
  }

  return custo;
}

void adicionaListaProdutos(int idP, int indE, int quant)
{
  int i;
  int numProdutos;
  int indP;
  indP = procuraProduto(idP);
  for (i = 0; i < encomendas[indE].numProdutos; i++)
  {
    if (idP == encomendas[indE].listaProdutos[i].id)
    {
      {
        encomendas[indE].listaProdutos[i].quant += quant;
        produtos[indP].quantStock -= quant;
        produtos[indP].quantNecessaria += quant;
        return;
      }
    }
    else
    {
      
    }

  }

  numProdutos = encomendas[indE].numProdutos;
  encomendas[indE].listaProdutos[numProdutos].id = idP;
  encomendas[indE].listaProdutos[numProdutos].quant = quant;
  produtos[indP].quantStock -= quant;
  produtos[indP].quantNecessaria += quant;
  encomendas[indE].numProdutos += 1;
}

void troca(int indP, struct prodEnc listaProdutos[], int size)
{
  listaProdutos[indP].id = listaProdutos[size - 1].id;
  listaProdutos[indP].quant = listaProdutos[size - 1].quant;
  listaProdutos[size - 1].id = 0;
  listaProdutos[size - 1].quant = 0;
}

void removeListaProdutos(int idP, int indE)
{
  int i;
  int size;
  int indP;
  size = encomendas[indE].numProdutos;
  indP = procuraProduto(idP);
  for (i = 0; i < size; i++)
  {
    if (idP == encomendas[indE].listaProdutos[i].id)
    {
      {
        produtos[indP].quantStock += encomendas[indE].listaProdutos[i].quant;
        produtos[indP].quantNecessaria -= encomendas[indE].listaProdutos[i].quant;
        troca(i, encomendas[indE].listaProdutos, encomendas[indE].numProdutos);
        encomendas[indE].numProdutos -= 1;
        return;
      }
    }
    else
    {
      
    }

  }

}

void comando_a()
{
  processaDados();
  strcpy(produtos[quantProd].descricao, dado1);
  produtos[quantProd].id = quantProd;
  produtos[quantProd].preco = dados[0];
  produtos[quantProd].peso = dados[1];
  produtos[quantProd].quantStock = dados[2];
  produtos[quantProd].quantNecessaria = 0;
  printf("Novo produto %d.\n", produtos[quantProd].id);
  quantProd += 1;
}

void comando_q()
{
  int idProduto;
  int indP;
  processaDados();
  idProduto = atoi(dado1);
  if (procuraProduto(idProduto) < 0)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idProduto);
      return;
    }
  }
  else
  {
    
  }

  indP = procuraProduto(idProduto);
  produtos[indP].quantStock += dados[0];
}

void comando_N()
{
  encomendas[quantEnc].id = quantEnc;
  encomendas[quantEnc].numProdutos = 0;
  printf("Nova encomenda %d.\n", encomendas[quantEnc].id);
  quantEnc += 1;
}

void comando_A()
{
  int idEncomenda;
  int idProduto;
  int quantidade;
  int pesoProduto;
  int indP;
  int indE;
  processaDados();
  idEncomenda = atoi(dado1);
  idProduto = dados[0];
  quantidade = dados[1];
  if ((indE = procuraEncomenda(idEncomenda)) < 0)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idProduto, idEncomenda);
      return;
    }
  }
  else
  {
    
  }

  if ((indP = procuraProduto(idProduto)) < 0)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idProduto, idEncomenda);
      return;
    }
  }
  else
  {
    
  }

  if (produtos[indP].quantStock < quantidade)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idProduto, idEncomenda);
      return;
    }
  }
  else
  {
    
  }

  pesoProduto = produtos[indP].peso * quantidade;
  if ((pesoProduto + calculaPeso(indE)) > 200)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idProduto, idEncomenda, 200);
      return;
    }
  }
  else
  {
    
  }

  adicionaListaProdutos(idProduto, indE, quantidade);
}

void comando_r()
{
  int idProduto;
  int quantRetirar;
  int indP;
  processaDados();
  idProduto = atoi(dado1);
  quantRetirar = dados[0];
  if ((indP = procuraProduto(idProduto)) < 0)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idProduto);
      return;
    }
  }
  else
  {
    
  }

  if (quantRetirar > produtos[indP].quantStock)
  {
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantRetirar, idProduto);
      return;
    }
  }
  else
  {
    
  }

  produtos[indP].quantStock -= quantRetirar;
}

void comando_R()
{
  int idEncomenda;
  int idProduto;
  int indP;
  int indE;
  processaDados();
  idEncomenda = atoi(dado1);
  idProduto = dados[0];
  if ((indE = procuraEncomenda(idEncomenda)) < 0)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idProduto, idEncomenda);
      return;
    }
  }
  else
  {
    
  }

  if ((indP = procuraProduto(idProduto)) < 0)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idProduto, idEncomenda);
      return;
    }
  }
  else
  {
    
  }

  removeListaProdutos(idProduto, indE);
}

void comando_C()
{
  int idEncomenda;
  int indE;
  processaDados();
  idEncomenda = atoi(dado1);
  if ((indE = procuraEncomenda(idEncomenda)) < 0)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idEncomenda);
      return;
    }
  }
  else
  {
    
  }

  printf("Custo da encomenda %d %d.\n", idEncomenda, calculaCusto(indE));
}

void comando_p()
{
  int idProduto;
  int preco;
  int indP;
  processaDados();
  idProduto = atoi(dado1);
  preco = dados[0];
  if ((indP = procuraProduto(idProduto)) < 0)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idProduto);
      return;
    }
  }
  else
  {
    
  }

  produtos[indP].preco = preco;
}

void comando_E()
{
  int j = 0;
  int idEncomenda;
  int idProduto;
  int quantidade = 0;
  int indP;
  int indE;
  processaDados();
  idEncomenda = atoi(dado1);
  idProduto = dados[0];
  if ((indE = procuraEncomenda(idEncomenda)) < 0)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idEncomenda);
      return;
    }
  }
  else
  {
    
  }

  if ((indP = procuraProduto(idProduto)) < 0)
  {
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idProduto);
      return;
    }
  }
  else
  {
    
  }

  for (j = 0; j < encomendas[indE].numProdutos; j++)
  {
    if (idProduto == encomendas[indE].listaProdutos[j].id)
    {
      {
        printf("%s %d.\n", produtos[indP].descricao, encomendas[indE].listaProdutos[j].quant);
        return;
      }
    }
    else
    {
      
    }

  }

  printf("%s %d.\n", produtos[indP].descricao, quantidade);
}

void comando_m()
{
  int idProduto;
  int i = 0;
  int j = 0;
  int quantMax = 0;
  int idEnc;
  int prodEmEnc = 0;
  processaDados();
  idProduto = atoi(dado1);
  if (procuraProduto(idProduto) < 0)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idProduto);
      return;
    }
  }
  else
  {
    
  }

  if (quantEnc == 0)
  {
    return;
  }
  else
  {
    
  }

  for (i = 0; i < quantEnc; i++)
  {
    for (j = 0; j < encomendas[i].numProdutos; j++)
    {
      if (idProduto == encomendas[i].listaProdutos[j].id)
      {
        {
          prodEmEnc = 1;
          if (encomendas[i].listaProdutos[j].quant > quantMax)
          {
            {
              quantMax = encomendas[i].listaProdutos[j].quant;
              idEnc = encomendas[i].id;
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

  }

  if (prodEmEnc == 0)
  {
    return;
  }
  else
  {
    
  }

  printf("Maximo produto %d %d %d.\n", idProduto, idEnc, quantMax);
}

void comando_l()
{
  int i;
  sortProdutos();
  printf("Produtos\n");
  for (i = 0; i < quantProd; i++)
  {
    printf("* %s %d %d\n", produtos[i].descricao, produtos[i].preco, produtos[i].quantStock);
  }

}

void comando_L()
{
  int idEncomenda;
  int i = 0;
  int indE;
  int indP;
  int idP;
  processaDados();
  idEncomenda = atoi(dado1);
  if (idEncomenda >= quantEnc)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idEncomenda);
      return;
    }
  }
  else
  {
    
  }

  indE = idEncomenda;
  sortListaProdutos(encomendas[indE].listaProdutos, encomendas[indE].numProdutos);
  printf("Encomenda %d\n", idEncomenda);
  for (i = 0; i < encomendas[indE].numProdutos; i++)
  {
    idP = encomendas[indE].listaProdutos[i].id;
    indP = procuraProduto(idP);
    printf("* %s %d %d\n", produtos[indP].descricao, produtos[indP].preco, encomendas[indE].listaProdutos[i].quant);
  }

}

int main()
{
  char comando;
  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      case 'a':
        comando_a();
        break;

      case 'q':
        comando_q();
        break;

      case 'N':
        comando_N();
        break;

      case 'A':
        comando_A();
        break;

      case 'r':
        comando_r();
        break;

      case 'R':
        comando_R();
        break;

      case 'C':
        comando_C();
        break;

      case 'p':
        comando_p();
        break;

      case 'E':
        comando_E();
        break;

      case 'm':
        comando_m();
        break;

      case 'l':
        comando_l();
        break;

      case 'L':
        comando_L();
        break;

    }

  }

  return 0;
}

