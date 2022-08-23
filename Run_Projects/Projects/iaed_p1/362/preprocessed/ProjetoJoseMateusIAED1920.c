/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int parse_instructions();
typedef struct product
{
  char desc[63];
  int price;
  int weight;
  int quant;
  int idp;
} Product;
typedef struct prod_ord
{
  int idp;
  int quant;
} Prod_order;
typedef struct encomenda
{
  int ide;
  int weight;
  int counter;
  Prod_order prod_list[200];
} Encomenda;
Product lista_produtos[10000];
Encomenda lista_encomendas[500];
int Product_Counter = 0;
int Encomenda_Counter = 0;
int comando_a();
int comando_q();
int comando_h();
int comando_N();
int comando_A();
int comando_r();
int comando_R();
int comando_C();
int comando_p();
int comando_E();
int comando_m();
int comando_l();
int comando_L();
void merge(Product list_to_order[], int left, int middle, int right, int type_flag);
void mergeSort(Product list_to_order[], int left, int right, int type_flag);
Product Laux[10000];
Product Raux[10000];
Product ordered_prod[10000];
char comando;
char junk;
int main()
{
  while (1)
  {
    comando = getchar();
    parse_instructions();
  }

  return 0;
}

int parse_instructions()
{
  int junk_flag = 0;
  getchar();
  switch (comando)
  {
    case 65:
      junk_flag = comando_A();
      break;

    case 67:
      junk_flag = comando_C();
      break;

    case 69:
      junk_flag = comando_E();
      break;

    case 76:
      junk_flag = comando_L();
      break;

    case 78:
      junk_flag = comando_N();
      break;

    case 82:
      junk_flag = comando_R();
      break;

    case 97:
      junk_flag = comando_a();
      break;

    case 104:
      junk_flag = comando_h();
      break;

    case 108:
      junk_flag = comando_l();
      break;

    case 109:
      junk_flag = comando_m();
      break;

    case 112:
      junk_flag = comando_p();
      break;

    case 113:
      junk_flag = comando_q();
      break;

    case 114:
      junk_flag = comando_r();
      break;

    case 120:
      exit(0);

    default:
      break;

  }

  if (junk_flag)
  {
    {
      junk = getchar();
    }
  }
  else
  {
    
  }

  return 0;
}

int comando_a()
{
  Product new_product;
  for (int new_product_index = 0; new_product_index < 10; new_product_index++)
  {
    new_product.desc[new_product_index] = new_sym_var(sizeof(char) * 8);
  }

  new_product.desc[10 - 1] = '\0';
  new_product.price = new_sym_var(sizeof(int) * 8);
  new_product.weight = new_sym_var(sizeof(int) * 8);
  new_product.quant = new_sym_var(sizeof(int) * 8);
  new_product.idp = Product_Counter;
  lista_produtos[Product_Counter] = new_product;
  Product_Counter++;
  printf("Novo produto %d.\n", new_product.idp);
  return 1;
}

int comando_h()
{
  int counter;
  Product prod;
  printf("PRODUTOS\n");
  for (counter = 0; counter < Product_Counter; counter++)
  {
    prod = lista_produtos[counter];
    printf("  Price: %d\n", prod.price);
    printf("  Weight: %d\n", prod.weight);
    printf("  Quant: %d\n", prod.quant);
    printf("  ID: %d\n", prod.idp);
    printf("  Desc: %s\n", prod.desc);
    putchar('\n');
  }

  return 0;
}

int comando_q()
{
  int idp;
  int quant;
  idp = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (idp >= Product_Counter)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
      return 1;
    }
  }
  else
  {
    
  }

  lista_produtos[idp].quant += quant;
  return 1;
}

int comando_N()
{
  Encomenda new_encomenda;
  new_encomenda.ide = Encomenda_Counter;
  new_encomenda.counter = 0;
  new_encomenda.weight = 0;
  lista_encomendas[Encomenda_Counter] = new_encomenda;
  printf("Nova encomenda %d.\n", Encomenda_Counter++);
  return 0;
}

int comando_A()
{
  int counter;
  int ide;
  int idp;
  int quant;
  Encomenda enco;
  Product prod;
  Prod_order prod_order;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (ide >= Encomenda_Counter)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      return 1;
    }
  }
  else
  {
    
  }

  if (idp >= Product_Counter)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return 1;
    }
  }
  else
  {
    
  }

  prod = lista_produtos[idp];
  enco = lista_encomendas[ide];
  if (prod.quant < quant)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      return 1;
    }
  }
  else
  {
    
  }

  if ((enco.weight + (prod.weight * quant)) > 200)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
      return 1;
    }
  }
  else
  {
    
  }

  for (counter = 0; counter < enco.counter; counter++)
  {
    prod_order = enco.prod_list[counter];
    if (prod_order.idp == idp)
    {
      {
        prod_order.quant += quant;
        enco.weight += prod.weight * quant;
        enco.prod_list[counter] = prod_order;
        lista_produtos[idp].quant -= quant;
        lista_encomendas[ide] = enco;
        return 1;
      }
    }
    else
    {
      
    }

  }

  prod_order.idp = idp;
  prod_order.quant = quant;
  enco.weight += prod.weight * quant;
  enco.prod_list[enco.counter] = prod_order;
  enco.counter++;
  lista_produtos[idp].quant -= quant;
  lista_encomendas[ide] = enco;
  return 1;
}

int comando_r()
{
  int idp;
  int quant;
  idp = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (idp >= Product_Counter)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
      return 1;
    }
  }
  else
  {
    
  }

  if (quant > lista_produtos[idp].quant)
  {
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, idp);
      return 1;
    }
  }
  else
  {
    
  }

  lista_produtos[idp].quant -= quant;
  return 1;
}

int comando_R()
{
  int ide;
  int idp;
  int counter;
  Encomenda enco;
  Prod_order prod_order;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= Encomenda_Counter)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      return 1;
    }
  }
  else
  {
    
  }

  if (idp >= Product_Counter)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return 1;
    }
  }
  else
  {
    
  }

  enco = lista_encomendas[ide];
  for (counter = 0; counter < enco.counter; counter++)
  {
    prod_order = enco.prod_list[counter];
    if (prod_order.idp == idp)
    {
      {
        enco.weight -= prod_order.quant * lista_produtos[idp].weight;
        lista_produtos[idp].quant += prod_order.quant;
        prod_order.quant = 0;
        enco.prod_list[counter] = prod_order;
        lista_encomendas[ide] = enco;
        return 1;
      }
    }
    else
    {
      
    }

  }

  return 1;
}

int comando_C()
{
  int ide;
  int total;
  int counter;
  Encomenda enco;
  Product prod;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= Encomenda_Counter)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
      return 1;
    }
  }
  else
  {
    
  }

  enco = lista_encomendas[ide];
  total = 0;
  for (counter = 0; counter < enco.counter; counter++)
  {
    prod = lista_produtos[enco.prod_list[counter].idp];
    total += prod.price * enco.prod_list[counter].quant;
  }

  printf("Custo da encomenda %d %d.\n", ide, total);
  return 1;
}

int comando_p()
{
  int idp;
  int preco;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp >= Product_Counter)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
      return 1;
    }
  }
  else
  {
    
  }

  lista_produtos[idp].price = preco;
  return 1;
}

int comando_E()
{
  int ide;
  int idp;
  int counter;
  int quant = 0;
  Encomenda enco;
  Prod_order prod_order;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= Encomenda_Counter)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return 1;
    }
  }
  else
  {
    
  }

  if (idp >= Product_Counter)
  {
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      return 1;
    }
  }
  else
  {
    
  }

  enco = lista_encomendas[ide];
  for (counter = 0; counter < enco.counter; counter++)
  {
    prod_order = enco.prod_list[counter];
    if (prod_order.idp == idp)
    {
      {
        quant = prod_order.quant;
      }
    }
    else
    {
      
    }

  }

  printf("%s %d.\n", lista_produtos[idp].desc, quant);
  return 1;
}

int comando_m()
{
  int idp;
  int ide;
  int counter;
  int aux_counter;
  int quant;
  int max_quant;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= Product_Counter)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
      return 1;
    }
  }
  else
  {
    
  }

  max_quant = 0;
  for (counter = 0; counter < Encomenda_Counter; counter++)
  {
    for (aux_counter = 0; aux_counter < lista_encomendas[counter].counter; aux_counter++)
    {
      if (idp == lista_encomendas[counter].prod_list[aux_counter].idp)
      {
        {
          quant = lista_encomendas[counter].prod_list[aux_counter].quant;
          if (quant > max_quant)
          {
            {
              max_quant = quant;
              ide = counter;
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

  if (max_quant)
  {
    {
      printf("Maximo produto %d %d %d.\n", idp, ide, max_quant);
    }
  }
  else
  {
    
  }

  return 1;
}

int comando_l()
{
  int counter;
  for (counter = 0; counter < Product_Counter; counter++)
  {
    ordered_prod[counter] = lista_produtos[counter];
  }

  mergeSort(ordered_prod, 0, Product_Counter - 1, 1);
  printf("Produtos\n");
  for (counter = 0; counter < Product_Counter; counter++)
  {
    printf("* %s %d %d\n", ordered_prod[counter].desc, ordered_prod[counter].price, ordered_prod[counter].quant);
  }

  return 0;
}

int comando_L()
{
  int ide;
  int counter;
  int idp;
  int quant;
  int aux_counter;
  Encomenda enco;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= Encomenda_Counter)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return 1;
    }
  }
  else
  {
    
  }

  enco = lista_encomendas[ide];
  for (counter = 0; counter < enco.counter; counter++)
  {
    idp = enco.prod_list[counter].idp;
    ordered_prod[counter] = lista_produtos[idp];
  }

  mergeSort(ordered_prod, 0, enco.counter - 1, 0);
  printf("Encomenda %d\n", ide);
  for (counter = 0; counter < enco.counter; counter++)
  {
    idp = ordered_prod[counter].idp;
    for (aux_counter = 0; aux_counter < enco.counter; aux_counter++)
    {
      if (idp == enco.prod_list[aux_counter].idp)
      {
        {
          quant = enco.prod_list[aux_counter].quant;
        }
      }
      else
      {
        
      }

    }

    if (quant)
    {
      printf("* %s %d %d\n", ordered_prod[counter].desc, ordered_prod[counter].price, quant);
    }
    else
    {
      
    }

  }

  return 1;
}

void mergeSort(Product list_to_order[], int left, int right, int type_flag)
{
  int middle = left + ((right - left) / 2);
  if (left < right)
  {
    {
      mergeSort(list_to_order, left, middle, type_flag);
      mergeSort(list_to_order, middle + 1, right, type_flag);
      merge(list_to_order, left, middle, right, type_flag);
    }
  }
  else
  {
    
  }

}

void merge(Product list_to_order[], int left, int middle, int right, int type_flag)
{
  int i;
  int j;
  int k;
  int n1 = (middle - left) + 1;
  int n2 = right - middle;
  for (i = 0; i < n1; i++)
  {
    Laux[i] = list_to_order[left + i];
  }

  for (j = 0; j < n2; j++)
  {
    Raux[j] = list_to_order[(middle + 1) + j];
  }

  i = 0;
  k = left;
  j = 0;
  while ((i < n1) && (j < n2))
  {
    if (type_flag)
    {
      {
        if (Laux[i].price <= Raux[j].price)
        {
          {
            list_to_order[k] = Laux[i++];
          }
        }
        else
        {
          {
            list_to_order[k] = Raux[j++];
          }
        }

        k++;
      }
    }
    else
    {
      {
        if (strcmp(Laux[i].desc, Raux[j].desc) <= 0)
        {
          {
            list_to_order[k] = Laux[i++];
          }
        }
        else
        {
          {
            list_to_order[k] = Raux[j++];
          }
        }

        k++;
      }
    }

  }

  while (i < n1)
  {
    list_to_order[k++] = Laux[i++];
  }

  while (j < n2)
  {
    list_to_order[k++] = Raux[j++];
  }

}

