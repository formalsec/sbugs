#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h> 


typedef struct 
{
  int idp;
  char descricao[64];
  int preco;
  int peso;
  int stock;
} Produto;
Produto inventario[10000];
Produto Encomendas[500][200];
int idp;
int ide;
void adicionaProduto();
void adicionaStock();
void criaEncomenda();
void adicionaProdEncomenda();
void removeStock();
void removeProdEncomenda();
void calculaCustoEncomenda();
void alteraPreco();
void listaDescricaoQtdProd();
void listaIdpEncomendaProdMaisVezes();
void listaProdExistentesPreco();
void listaProdAlfaDescricao();
void inicializa();
int calculapesoencomenda(int iden, int pesototal, int i);
void bubblel(Produto a[], int left, int right);
int lesspreco(Produto i, Produto j);
void swap(Produto i, Produto j);
void bubbleL(Produto a[], int left, int right);
int lessalfabeto(Produto i, Produto j);
int main()
{
  char comando = ' ';
  inicializa();
  while (comando != 'x')
  {
    comando = new_sym_var(sizeof(char) * 8);
    switch (comando)
    {
      case 'a':
        adicionaProduto();
        break;

      case 'q':
        adicionaStock();
        break;

      case 'N':
        criaEncomenda();
        break;

      case 'A':
        adicionaProdEncomenda();
        break;

      case 'r':
        removeStock();
        break;

      case 'R':
        removeProdEncomenda();
        break;

      case 'C':
        calculaCustoEncomenda();
        break;

      case 'p':
        alteraPreco();
        break;

      case 'E':
        listaDescricaoQtdProd();
        break;

      case 'l':
        listaProdExistentesPreco();
        break;

      case 'm':
        listaIdpEncomendaProdMaisVezes();
        break;

      case 'L':
        listaProdAlfaDescricao();
        break;

      case 'x':
        break;

    }

  }

  return 0;
}

void adicionaProduto()
{
  int i;
  for (i = 0; i <= idp; i++)
  {
    if (inventario[i].peso == 0)
    {
      break;
    }
    else
    {
      
    }

  }

  inventario[i].idp = idp;
  for (int inventario_index = 0; inventario_index < 10; inventario_index++)
  {
    inventario[i].descricao[inventario_index] = new_sym_var(sizeof(char) * 8);
  }

  inventario[i].descricao[10 - 1] = '\0';
  inventario[i].preco = new_sym_var(sizeof(int) * 8);
  inventario[i].peso = new_sym_var(sizeof(int) * 8);
  inventario[i].stock = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", idp);
  idp++;
}

void adicionaStock()
{
  int id;
  int qtd;
  int i;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id >= idp)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < idp; i++)
  {
    if (inventario[i].idp == id)
    {
      inventario[i].stock += qtd;
      break;
    }
    else
    {
      
    }

  }

}

void criaEncomenda()
{
  printf("Nova encomenda %d.\n", ide);
  ide++;
}

void adicionaProdEncomenda()
{
  int iden;
  int id;
  int qtd;
  int pesototal;
  int i;
  int j;
  pesototal = 0;
  i = 0;
  iden = new_sym_var(sizeof(int) * 8);
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (iden >= ide)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id, iden);
    return;
  }
  else
  {
    
  }

  if (id >= idp)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id, iden);
    return;
  }
  else
  {
    
  }

  for (j = 0; j < idp; j++)
  {
    if (inventario[j].idp == id)
    {
      if (inventario[j].stock < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id, iden);
        return;
      }
      else
      {
        
      }

      break;
    }
    else
    {
      
    }

  }

  calculapesoencomenda(iden, pesototal, i);
  pesototal += qtd * inventario[j].peso;
  if (pesototal > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id, iden);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < idp; i++)
  {
    if (Encomendas[iden][i].idp == inventario[j].idp)
    {
      Encomendas[iden][i].stock += qtd;
      inventario[j].stock -= qtd;
      return;
    }
    else
    {
      
    }

  }

  for (i = 0; i < idp; i++)
  {
    if (Encomendas[iden][i].stock == 0)
    {
      Encomendas[iden][i].idp = inventario[j].idp;
      Encomendas[iden][i].stock = qtd;
      inventario[j].stock -= qtd;
      Encomendas[iden][i].peso = inventario[j].peso;
      Encomendas[iden][i].preco = inventario[j].preco;
      strcpy(Encomendas[iden][i].descricao, inventario[j].descricao);
      break;
    }
    else
    {
      
    }

  }

}

void removeStock()
{
  int id;
  int qtd;
  int i;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id >= idp)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < idp; i++)
  {
    if (inventario[i].idp == id)
    {
      break;
    }
    else
    {
      
    }

  }

  if (qtd > inventario[i].stock)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
    return;
  }
  else
  {
    
  }

  inventario[i].stock -= qtd;
}

void removeProdEncomenda()
{
  int id;
  int iden;
  int i;
  int j;
  iden = new_sym_var(sizeof(int) * 8);
  id = new_sym_var(sizeof(int) * 8);
  if (iden >= ide)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id, iden);
    return;
  }
  else
  {
    
  }

  if (id >= idp)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id, iden);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < idp; i++)
  {
    if (inventario[i].idp == id)
    {
      break;
    }
    else
    {
      
    }

  }

  for (j = 0; j < idp; j++)
  {
    if (Encomendas[iden][j].idp == id)
    {
      break;
    }
    else
    {
      
    }

  }

  inventario[i].stock += Encomendas[iden][j].stock;
  Encomendas[iden][j].stock = 0;
}

void calculaCustoEncomenda()
{
  int iden;
  int total;
  int i;
  total = 0;
  iden = new_sym_var(sizeof(int) * 8);
  if (iden >= ide)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", iden);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < idp; i++)
  {
    total += Encomendas[iden][i].preco * Encomendas[iden][i].stock;
  }

  printf("Custo da encomenda %d %d.\n", iden, total);
}

void alteraPreco()
{
  int id;
  int preco;
  int i;
  int j;
  id = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (id >= idp)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < idp; i++)
  {
    if (inventario[i].idp == id)
    {
      inventario[i].preco = preco;
      break;
    }
    else
    {
      
    }

  }

  for (i = 0; i < ide; i++)
  {
    for (j = 0; j < idp; j++)
    {
      if (Encomendas[i][j].idp == id)
      {
        Encomendas[i][j].preco = preco;
        break;
      }
      else
      {
        
      }

    }

  }

}

void listaDescricaoQtdProd()
{
  int iden;
  int id;
  int i;
  iden = new_sym_var(sizeof(int) * 8);
  id = new_sym_var(sizeof(int) * 8);
  if (iden >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", iden);
    return;
  }
  else
  {
    
  }

  if (id >= idp)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < idp; i++)
  {
    if (Encomendas[iden][i].idp == id)
    {
      break;
    }
    else
    {
      
    }

  }

  printf("%s %d.\n", Encomendas[iden][i].descricao, Encomendas[iden][i].stock);
}

void listaProdExistentesPreco()
{
  int i;
  bubblel(inventario, 0, idp);
  printf("Produtos\n");
  for (i = 0; i < idp; i++)
  {
    printf("* %s %d %d\n", inventario[i].descricao, inventario[i].preco, inventario[i].stock);
  }

}

void bubblel(Produto a[], int left, int right)
{
  int i;
  int j;
  int done;
  for (i = left; i < right; i++)
  {
    done = 1;
    for (j = right; j > i; j--)
      if (lesspreco(a[j], a[j - 1]))
    {
      swap(a[j - 1], a[j]);
      done = 0;
    }
    else
    {
      
    }


    if (done)
    {
      break;
    }
    else
    {
      
    }

  }

}

int lesspreco(Produto i, Produto j)
{
  if (i.preco > j.preco)
  {
    return 0;
  }
  else
  {
    
  }

  if (i.preco < j.preco)
  {
    return 1;
  }
  else
  {
    
  }

  if (i.preco == j.preco)
  {
    if (i.idp < j.idp)
    {
      return 1;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

  return 0;
}

void swap(Produto i, Produto j)
{
  Produto k;
  strcpy(k.descricao, i.descricao);
  k.peso = i.peso;
  k.preco = i.preco;
  k.stock = i.stock;
  k.idp = i.idp;
  i.peso = j.peso;
  i.preco = j.preco;
  i.stock = j.stock;
  i.idp = j.idp;
  strcpy(i.descricao, j.descricao);
  j.idp = k.idp;
  j.stock = k.stock;
  j.preco = k.preco;
  j.peso = k.peso;
  strcpy(j.descricao, k.descricao);
}

void listaIdpEncomendaProdMaisVezes()
{
  int id;
  int i;
  int j;
  int max;
  int aux;
  max = 0;
  aux = 0;
  id = new_sym_var(sizeof(int) * 8);
  if (id >= idp)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  if (ide == 0)
  {
    return;
  }
  else
  {
    
  }

  for (i = 0; i < ide; i++)
  {
    for (j = 0; j < idp; j++)
    {
      if (Encomendas[i][j].idp == id)
      {
        if (Encomendas[i][j].stock > max)
        {
          aux = i;
          max = Encomendas[i][j].stock;
        }
        else
        {
          if ((Encomendas[i][j].stock == max) && (max != 0))
          {
            if (aux > i)
            {
              aux = i;
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
      else
      {
        
      }

    }

    if (max != 0)
    {
      printf("Maximo produto %d %d %d\n", id, aux, max);
    }
    else
    {
      
    }

  }

}

void listaProdAlfaDescricao()
{
  int iden;
  int i;
  iden = new_sym_var(sizeof(int) * 8);
  if (iden >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", iden);
    return;
  }
  else
  {
    
  }

  bubbleL(Encomendas[iden], 0, idp);
  printf("Encomenda %d\n", iden);
  for (i = 0; i < idp; i++)
  {
    if (Encomendas[iden][i].stock != 0)
    {
      printf("* %s %d %d\n", Encomendas[iden][i].descricao, Encomendas[iden][i].preco, Encomendas[iden][i].stock);
    }
    else
    {
      
    }

  }

}

void bubbleL(Produto a[], int left, int right)
{
  int i;
  int j;
  int done;
  for (i = left; i < right; i++)
  {
    done = 1;
    for (j = right; j > i; j--)
      if (lessalfabeto(a[j], a[j - 1]))
    {
      swap(a[j - 1], a[j]);
      done = 0;
    }
    else
    {
      
    }


    if (done)
    {
      break;
    }
    else
    {
      
    }

  }

}

int lessalfabeto(Produto i, Produto j)
{
  if (strcmp(i.descricao, j.descricao) < 0)
  {
    return 1;
  }
  else
  {
    
  }

  return 0;
}

void inicializa()
{
  int i;
  int j;
  idp = 0;
  ide = 0;
  for (i = 0; i < 500; i++)
  {
    for (j = 0; j < 200; j++)
    {
      Encomendas[i][j].idp = -1;
      Encomendas[i][j].peso = 0;
      Encomendas[i][j].preco = 0;
      Encomendas[i][j].stock = 0;
    }

  }

}

int calculapesoencomenda(int iden, int pesototal, int i)
{
  for (i = 0; i < idp; i++)
  {
    pesototal = pesototal + (Encomendas[iden][i].stock * Encomendas[iden][i].peso);
  }

  return pesototal;
}
