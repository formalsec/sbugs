/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


int pConta = 0;
int eConta = 0;
typedef struct 
{
  int id;
  char description[63 + 1];
  int price;
  int weight;
  int qtd;
  int exists;
} __produto__;
__produto__ produtos[10000] = {{0}};
typedef struct 
{
  int id;
  int weight;
  int qtd;
  int price;
  __produto__ p[10000];
} __encomenda__;
__encomenda__ encomendas[500] = {{0}};
__produto__ cria_produto()
{
  return produtos[pConta];
}

__produto__ elimina_produto(int idp)
{
  int i;
  int aux;
  __produto__ p_aux[10000];
  for (i = 0; i < pConta; i++)
  {
    if (produtos[i].id == idp)
    {
      p_aux[i] = produtos[i];
      aux = i;
      p_aux[i].exists = 0;
      p_aux[i].price = 0;
      p_aux[i].weight = 0;
      p_aux[i].qtd = 0;
    }
    else
    {
      
    }

  }

  return p_aux[aux];
}

void __a__(char description[63 + 1], int price, int weight, int qtd)
{
  __produto__ new;
  if (((price > 0) && (weight > 0)) && (qtd > 0))
  {
    new = cria_produto();
    strcpy(new.description, description);
    new.price = price;
    new.weight = weight;
    new.qtd = qtd;
    new.id = pConta;
    new.exists = 0;
    produtos[pConta] = new;
    printf("Novo produto %d.\n", pConta);
    pConta++;
  }
  else
  {
    
  }

}

void __k__()
{
  int i;
  for (i = 0; i < pConta; i++)
  {
    printf("idp %d\n", produtos[i].id);
    printf("%s\t", produtos[i].description);
    printf("preco %d\t", produtos[i].price);
    printf("peso %d\t", produtos[i].weight);
    printf("qtd %d\n", produtos[i].qtd);
  }

}

void __l__()
{
  int i;
  int k = 0;
  int j;
  int index = 0;
  int aux = 0;
  __produto__ paux[10000];
  __produto__ a[10000];
  for (i = 0; i < pConta; i++)
  {
    paux[i] = produtos[i];
    a[i] = paux[i];
  }

  for (i = 0; i < (pConta - 1); i++)
  {
    index = i;
    for (j = i + 1; j < pConta; j++)
    {
      if (paux[index].price > paux[j].price)
      {
        index = j;
      }
      else
      {
        
      }

      if (paux[index].price == paux[j].price)
      {
        if (paux[index].id > paux[j].id)
        {
          index = j;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

    if (index != j)
    {
      aux = paux[i].price;
      a[i].price = aux;
      a[i] = paux[i];
      paux[i] = paux[index];
      paux[index] = a[i];
    }
    else
    {
      
    }

  }

  printf("Produtos\n");
  for (k = 0; k < pConta; k++)
  {
    printf("* %s ", paux[k].description);
    printf("%d ", paux[k].price);
    printf("%d\n", paux[k].qtd);
    i++;
  }

}

bool not_encomenda_exists(int ide)
{
  if (ide > (eConta - 1))
  {
    return true;
  }
  else
  {
    return false;
  }

}

bool not_product_exists(int idp)
{
  if (idp > (pConta - 1))
  {
    return true;
  }
  else
  {
    return false;
  }

}

void __q__(int idp, int qtd)
{
  int i;
  if (not_product_exists(idp))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < pConta; i++)
    {
      if (idp == i)
      {
        produtos[idp].qtd += qtd;
        break;
      }
      else
      {
        
      }

    }

  }

}

__encomenda__ cria_Encomenda()
{
  return encomendas[eConta];
}

bool weight_exceeds(int ide, int idp, int qtd)
{
  int i;
  int j;
  int p_total = 0;
  for (i = 0; i < pConta; i++)
  {
    if (produtos[i].id == idp)
    {
      p_total = produtos[idp].weight * qtd;
      if (p_total > 200)
      {
        return true;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    for (j = 0; j < eConta; j++)
    {
      if (encomendas[j].id == ide)
      {
        if ((encomendas[ide].weight + p_total) > 200)
        {
          return true;
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

  return false;
}

bool not_enough_stock(int idp, int qtd)
{
  int i;
  for (i = 0; i < pConta; i++)
  {
    if (produtos[i].id == idp)
    {
      if (produtos[idp].qtd < qtd)
      {
        return true;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  return false;
}

void __N__()
{
  __encomenda__ new;
  new = cria_Encomenda();
  new.id = eConta;
  new.weight = 0;
  encomendas[eConta] = new;
  printf("Nova encomenda %d.\n", eConta);
  eConta++;
}

void __A__(int ide, int idp, int qtd)
{
  int i;
  int j;
  int peso = 0;
  int aux = 0;
  if (not_encomenda_exists(ide))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (not_product_exists(idp))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (not_enough_stock(idp, qtd))
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if (weight_exceeds(ide, idp, qtd))
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          for (i = 0; i < pConta; i++)
          {
            if (produtos[i].id == idp)
            {
              peso = produtos[i].weight;
              peso = peso * qtd;
            }
            else
            {
              
            }

          }

          aux = encomendas[ide].weight + peso;
          if (aux > 200)
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
          }
          else
          {
            for (j = 0; j < eConta; j++)
            {
              if (encomendas[j].id == ide)
              {
                encomendas[j].p[idp].weight = produtos[idp].weight;
                strcpy(encomendas[j].p[idp].description, produtos[idp].description);
                encomendas[j].p[idp].id = idp;
                encomendas[j].p[idp].exists = 1;
                encomendas[j].p[idp].price = produtos[idp].price;
                encomendas[j].price += produtos[idp].price * qtd;
                encomendas[j].weight += peso;
                encomendas[j].qtd += qtd;
                produtos[idp].qtd -= qtd;
                if (encomendas[j].qtd == qtd)
                {
                  encomendas[j].p[idp].qtd = qtd;
                }
                else
                {
                  encomendas[j].p[idp].qtd += qtd;
                }

              }
              else
              {
                
              }

            }

          }

        }

      }

    }

  }

}

void __C__(int ide)
{
  int j;
  if (not_encomenda_exists(ide))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (j = 0; j < eConta; j++)
    {
      if (encomendas[j].id == ide)
      {
        printf("Custo da encomenda %d %d.\n", ide, encomendas[ide].price);
        break;
      }
      else
      {
        
      }

    }

  }

}

void __r__(int idp, int qtd)
{
  int i;
  if (not_product_exists(idp))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (not_enough_stock(idp, qtd))
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      for (i = 0; i < pConta; i++)
      {
        if (i == idp)
        {
          produtos[idp].qtd -= qtd;
        }
        else
        {
          
        }

      }

    }

  }

}

void __R__(int ide, int idp)
{
  int i;
  int j;
  int qtd_idp_encomenda = 0;
  int price_del = 0;
  int weight_del = 0;
  if (not_encomenda_exists(ide))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (not_product_exists(idp))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      for (i = 0; i < eConta; i++)
      {
        for (j = 0; j < pConta; j++)
        {
          if ((i == ide) && (j == idp))
          {
            qtd_idp_encomenda = encomendas[i].p[j].qtd;
            price_del = encomendas[i].p[j].price;
            weight_del = encomendas[i].p[j].weight;
            encomendas[i].p[j] = elimina_produto(idp);
            price_del = qtd_idp_encomenda * price_del;
            weight_del = qtd_idp_encomenda * weight_del;
            encomendas[i].price -= price_del;
            encomendas[i].weight -= weight_del;
            encomendas[i].qtd -= qtd_idp_encomenda;
            produtos[idp].qtd += qtd_idp_encomenda;
          }
          else
          {
            
          }

        }

      }

    }

  }

}

void __K__(int ide)
{
  int j;
  int i = 0;
  printf("Encomenda %d\n", ide);
  while (i < pConta)
  {
    for (j = 0; j < eConta; j++)
    {
      if (encomendas[ide].id == j)
      {
        if (encomendas[ide].p[i].price > 0)
        {
          printf("%s\n", encomendas[j].p[i].description);
          printf("custa %d\t", encomendas[j].p[i].price);
          printf("existe %d\t", encomendas[j].p[i].qtd);
          printf("pesa %d\n", encomendas[j].p[i].weight);
        }
        else
        {
          
        }

        i++;
      }
      else
      {
        
      }

    }

  }

}

void __E__(int ide, int idp)
{
  int i;
  int j;
  if (not_product_exists(idp))
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (not_encomenda_exists(ide))
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else
    {
      for (i = 0; i < pConta; i++)
      {
        for (j = 0; j < eConta; j++)
        {
          if (i == idp)
          {
            if (j == ide)
            {
              printf("%s %d.\n", produtos[idp].description, encomendas[ide].p[idp].qtd);
              break;
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

    }

  }

}

void __p__(int idp, int price)
{
  int i;
  int j;
  int new_total_price = 0;
  int old_total_price = 0;
  if (not_product_exists(idp))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < pConta; i++)
    {
      if (produtos[i].id == idp)
      {
        produtos[i].price = price;
      }
      else
      {
        
      }

      for (j = 0; j < eConta; j++)
      {
        if (encomendas[j].p[i].id == idp)
        {
          old_total_price = encomendas[j].p[i].price * encomendas[j].p[i].qtd;
          new_total_price = price * encomendas[j].p[i].qtd;
          encomendas[j].p[i].price = price;
          encomendas[j].price -= old_total_price;
          encomendas[j].price += new_total_price;
        }
        else
        {
          
        }

      }

    }

  }

}

void __m__(int idp)
{
  int i = 0;
  int max = 0;
  int j = 0;
  int id_e = 0;
  int flag = 0;
  int aux[500] = {-1};
  if (not_product_exists(idp))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    while (i < pConta)
    {
      for (j = 0; j < eConta; j++)
      {
        if (((encomendas[j].p[i].id == idp) && (encomendas[j].p[idp].exists == 1)) && (encomendas[j].p[i].qtd > 0))
        {
          aux[j] = encomendas[j].p[i].qtd;
          flag = 1;
        }
        else
        {
          
        }

      }

      i++;
    }

    if (flag == 1)
    {
      for (i = 0; i < 500; i++)
      {
        if (aux[i] > 0)
        {
          if (aux[i] > max)
          {
            max = aux[i];
            id_e = i;
          }
          else
          {
            
          }

        }
        else
        {
          
        }

      }

      printf("Maximo produto %d ", idp);
      printf("%d ", id_e);
      printf("%d.\n", max);
    }
    else
    {
      
    }

  }

}

int countP_in_ide(int ide)
{
  int i;
  int j;
  int conta = 0;
  for (j = 0; j < eConta; j++)
  {
    if (j == ide)
    {
      for (i = 0; i < pConta; i++)
      {
        if (encomendas[j].p[i].exists == 1)
        {
          conta++;
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

  return conta;
}

void __L__(int ide)
{
  int i = 0;
  int j;
  int k;
  int conta = 0;
  __produto__ paux[10000] = {0};
  __produto__ aux[10000] = {0};
  if (not_encomenda_exists(ide))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    printf("Encomenda %d\n", ide);
    conta = countP_in_ide(ide);
    for (i = 0; i < pConta; i++)
    {
      if (encomendas[ide].p[i].exists == 1)
      {
        paux[i] = encomendas[ide].p[i];
        aux[i] = paux[i];
      }
      else
      {
        
      }

    }

    if (conta > 1)
    {
      for (k = 0; k < (pConta - 1); k++)
      {
        for (j = k + 1; j < pConta; j++)
        {
          if (strcmp(paux[k].description, paux[j].description) > 0)
          {
            aux[k] = paux[k];
            paux[k] = paux[j];
            paux[j] = aux[k];
          }
          else
          {
            
          }

        }

      }

    }
    else
    {
      
    }

    for (k = 0; k < pConta; k++)
    {
      if (paux[k].qtd > 0)
      {
        printf("* %s ", paux[k].description);
        printf("%d ", paux[k].price);
        printf("%d\n", paux[k].qtd);
      }
      else
      {
        
      }

    }

  }

}

int main()
{
  char description[63 + 1];
  int price;
  int weight;
  int qtd;
  int idp;
  int ide;
  char command;
  while (1)
  {
    command = getchar();
    switch (command)
    {
      case 'a':
        for (int description_index = 0; description_index < (63 + 1); description_index++)
      {
        description[description_index] = new_sym_var(sizeof(char) * 8);
      }

        description[(63 + 1) - 1] = '\0';
        price = new_sym_var(sizeof(int) * 8);
        weight = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        __a__(description, price, weight, qtd);
        break;

      case 'k':
        __k__();
        break;

      case 'K':
        ide = new_sym_var(sizeof(int) * 8);
        __K__(ide);
        break;

      case 'q':
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        __q__(idp, qtd);
        break;

      case 'N':
        __N__();
        break;

      case 'A':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        __A__(ide, idp, qtd);
        break;

      case 'r':
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        __r__(idp, qtd);
        break;

      case 'R':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        __R__(ide, idp);
        break;

      case 'C':
        ide = new_sym_var(sizeof(int) * 8);
        __C__(ide);
        break;

      case 'p':
        idp = new_sym_var(sizeof(int) * 8);
        price = new_sym_var(sizeof(int) * 8);
        __p__(idp, price);
        break;

      case 'E':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        __E__(ide, idp);
        break;

      case 'm':
        idp = new_sym_var(sizeof(int) * 8);
        __m__(idp);
        break;

      case 'l':
        __l__();
        break;

      case 'L':
        ide = new_sym_var(sizeof(int) * 8);
        __L__(ide);
        break;

      case 'x':
        return 0;

      default:
        printf("ERRO: comando desconhecido\n");

    }

    getchar();
  }

  return 0;
}
