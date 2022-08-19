/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int act = 0;
int order_act = 0;
typedef struct 
{
  int prod_id;
  char prod_desc[64];
  int prod_price;
  int prod_w;
  int prod_st;
} prod;
typedef struct 
{
  int order_id;
  int order_w;
  int order_prods[200];
  int order_qnt[200];
  int order_prod_act;
} order;
int existE(int a, int active_E, int ide, order t[])
{
  while (a < active_E)
  {
    if (ide == t[a].order_id)
    {
      break;
    }
    else
    {
      
    }

    a++;
  }

  return a;
}

int existP(int b, int active_P, int idp, prod v[])
{
  while (b < active_P)
  {
    if (idp == v[b].prod_id)
    {
      break;
    }
    else
    {
      
    }

    b++;
  }

  return b;
}

int existPinE(int c, int active_P_E, int idp, int E, order t[])
{
  while (c < active_P_E)
  {
    if (idp == t[E].order_prods[c])
    {
      break;
    }
    else
    {
      
    }

    c++;
  }

  return c;
}

void insertionSort(prod vetor[], int l, int r)
{
  int a;
  int b;
  for (a = l + 1; a <= r; a++)
  {
    prod v;
    strcpy(v.prod_desc, vetor[a].prod_desc);
    v.prod_price = vetor[a].prod_price;
    v.prod_st = vetor[a].prod_st;
    b = a - 1;
    while ((b >= l) && (v.prod_price < vetor[b].prod_price))
    {
      strcpy(vetor[b + 1].prod_desc, vetor[b].prod_desc);
      vetor[b + 1].prod_price = vetor[b].prod_price;
      vetor[b + 1].prod_st = vetor[b].prod_st;
      b--;
    }

    vetor[b + 1].prod_price = v.prod_price;
    strcpy(vetor[b + 1].prod_desc, v.prod_desc);
    vetor[b + 1].prod_st = v.prod_st;
  }

}

int partition(prod a[], int l, int r)
{
  int i = l - 1;
  int j = r;
  prod v;
  prod ta;
  prod tb;
  v.prod_id = a[r].prod_id;
  strcpy(v.prod_desc, a[r].prod_desc);
  v.prod_price = a[r].prod_price;
  v.prod_st = a[r].prod_st;
  while (i < j)
  {
    while (strcmp(a[++i].prod_desc, v.prod_desc) < 0)
      ;

    while (strcmp(v.prod_desc, a[--j].prod_desc) < 0)
    {
      if (j == l)
      {
        break;
      }
      else
      {
        
      }

    }

    if (i < j)
    {
      {
        ta.prod_id = a[i].prod_id;
        strcpy(ta.prod_desc, a[i].prod_desc);
        ta.prod_price = a[i].prod_price;
        ta.prod_st = a[i].prod_st;
        a[i].prod_id = a[j].prod_id;
        strcpy(a[i].prod_desc, a[j].prod_desc);
        a[i].prod_price = a[j].prod_price;
        a[i].prod_st = a[j].prod_st;
        a[j].prod_id = ta.prod_id;
        strcpy(a[j].prod_desc, ta.prod_desc);
        a[j].prod_price = ta.prod_price;
        a[j].prod_st = ta.prod_st;
      }
    }
    else
    {
      
    }

  }

  tb.prod_id = a[i].prod_id;
  strcpy(tb.prod_desc, a[i].prod_desc);
  tb.prod_price = a[i].prod_price;
  tb.prod_st = a[i].prod_st;
  a[i].prod_id = a[r].prod_id;
  strcpy(a[i].prod_desc, a[r].prod_desc);
  a[i].prod_price = a[r].prod_price;
  a[i].prod_st = a[r].prod_st;
  a[r].prod_id = tb.prod_id;
  strcpy(a[r].prod_desc, tb.prod_desc);
  a[r].prod_price = tb.prod_price;
  a[r].prod_st = tb.prod_st;
  return i;
}

void quicksort(prod a[], int l, int r)
{
  int i;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  i = partition(a, l, r);
  quicksort(a, l, i - 1);
  quicksort(a, i + 1, r);
}

void addProd(prod v[])
{
  for (int v_index = 0; v_index < 10; v_index++)
  {
    v[act].prod_desc[v_index] = new_sym_var(sizeof(char) * 8);
  }

  v[act].prod_desc[10 - 1] = '\0';
  v[act].prod_price = new_sym_var(sizeof(int) * 8);
  v[act].prod_w = new_sym_var(sizeof(int) * 8);
  v[act].prod_st = new_sym_var(sizeof(int) * 8);
  v[act].prod_id = act;
  printf("Novo produto %d.\n", v[act].prod_id);
  act++;
}

void addStock(prod v[])
{
  int idp;
  int qtd;
  int PP;
  int e = 0;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  PP = existP(e, act, idp, v);
  if ((idp != v[PP].prod_id) || (strcmp(v[PP].prod_desc, "") == 0))
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    {
      v[PP].prod_st += qtd;
      return;
    }
  }

}

void newOrder(order t[])
{
  t[order_act].order_id = order_act;
  t[order_act].order_w = 0;
  t[order_act].order_prod_act = 0;
  printf("Nova encomenda %d.\n", t[order_act].order_id);
  order_act++;
}

void addProdToOrder(prod v[], order t[])
{
  int i = 0;
  int e = 0;
  int o = 0;
  int EE;
  int PP;
  int LL;
  int ide;
  int idp;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  EE = existE(i, order_act, ide, t);
  if ((ide != t[EE].order_id) || (order_act == 0))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  PP = existP(e, act, idp, v);
  if ((idp != v[PP].prod_id) || (strcmp(v[PP].prod_desc, "") == 0))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  if (v[PP].prod_st < qtd)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  if (((v[PP].prod_w * qtd) + t[EE].order_w) > 200)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  LL = existPinE(o, t[EE].order_prod_act, idp, EE, t);
  if (v[PP].prod_id == t[EE].order_prods[LL])
  {
    {
      t[EE].order_qnt[LL] += qtd;
      t[EE].order_w += v[PP].prod_w * qtd;
      v[PP].prod_st -= qtd;
      t[EE].order_prod_act++;
    }
  }
  else
  {
    {
      t[EE].order_prods[t[EE].order_prod_act] = v[PP].prod_id;
      t[EE].order_qnt[t[EE].order_prod_act] += qtd;
      t[EE].order_w += v[PP].prod_w * qtd;
      v[PP].prod_st -= qtd;
      t[EE].order_prod_act++;
    }
  }

}

void removeStockProd(prod v[])
{
  int idp;
  int qtd;
  int PP;
  int e = 0;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  PP = existP(e, act, idp, v);
  if ((idp != v[PP].prod_id) || (strcmp(v[PP].prod_desc, "") == 0))
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  if ((v[PP].prod_st - qtd) < 0)
  {
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
      return;
    }
  }
  else
  {
    v[PP].prod_st -= qtd;
  }

}

void removeProdFromOrder(prod v[], order t[])
{
  int EE;
  int PP;
  int LL;
  int ide;
  int idp;
  int u;
  int i = 0;
  int e = 0;
  int o = 0;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  EE = existE(i, order_act, ide, t);
  if ((ide != t[EE].order_id) || (order_act == 0))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  PP = existP(e, act, idp, v);
  if ((idp != v[PP].prod_id) || (strcmp(v[PP].prod_desc, "") == 0))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    
  }

  LL = existPinE(o, t[EE].order_prod_act, idp, EE, t);
  if ((idp != t[EE].order_prods[LL]) || (t[EE].order_prod_act == 0))
  {
    return;
  }
  else
  {
    {
      v[PP].prod_st += t[EE].order_qnt[LL];
      t[EE].order_w -= v[PP].prod_w * t[EE].order_qnt[LL];
      for (u = LL; u < (t[EE].order_prod_act + 1); u++)
      {
        t[EE].order_prods[u] = t[EE].order_prods[u + 1];
        t[EE].order_qnt[u] = t[EE].order_qnt[u + 1];
      }

    }
  }

}

void costOrder(prod v[], order t[])
{
  int EE;
  int x;
  int ide;
  int total = 0;
  int i = 0;
  ide = new_sym_var(sizeof(int) * 8);
  EE = existE(i, order_act, ide, t);
  if ((ide != t[EE].order_id) || (order_act == 0))
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    {
      {
        for (x = 0; x < t[EE].order_prod_act; x++)
        {
          total += t[EE].order_qnt[x] * v[t[EE].order_prods[x]].prod_price;
        }

      }
      printf("Custo da encomenda %d %d.\n", ide, total);
    }
  }

}

void changeProdPrice(prod v[])
{
  int idp;
  int preco;
  int PP;
  int e = 0;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  PP = existP(e, act, idp, v);
  if ((idp != v[PP].prod_id) || (strcmp(v[PP].prod_desc, "") == 0))
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    {
      v[PP].prod_price = preco;
    }
  }

}

void listProdQ(prod v[], order t[])
{
  int EE;
  int PP;
  int LL;
  int ide;
  int idp;
  int i = 0;
  int e = 0;
  int o = 0;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  EE = existE(i, order_act, ide, t);
  if ((ide != t[EE].order_id) || (order_act == 0))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    
  }

  PP = existP(e, act, idp, v);
  if ((idp != v[PP].prod_id) || (strcmp(v[PP].prod_desc, "") == 0))
  {
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  LL = existPinE(o, t[EE].order_prod_act, idp, EE, t);
  if (t[EE].order_prods[LL] != v[PP].prod_id)
  {
    printf("%s %d.\n", v[PP].prod_desc, 0);
  }
  else
  {
    printf("%s %d.\n", v[PP].prod_desc, t[EE].order_qnt[LL]);
  }

}

void maxProd(prod v[], order t[])
{
  int PP;
  int i;
  int x;
  int idp;
  int e = 0;
  int idMin = 500;
  int qntMax = 0;
  idp = new_sym_var(sizeof(int) * 8);
  PP = existP(e, act, idp, v);
  if ((idp != v[PP].prod_id) || (strcmp(v[PP].prod_desc, "") == 0))
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  if (order_act == 0)
  {
    return;
  }
  else
  {
    
  }

  for (i = 0; i < order_act; i++)
  {
    for (x = 0; x < t[i].order_prod_act; x++)
    {
      if ((idp == t[i].order_prods[x]) && (qntMax < t[i].order_qnt[x]))
      {
        {
          idMin = t[i].order_id;
          qntMax = t[i].order_qnt[x];
        }
      }
      else
      {
        
      }

    }

  }

  if (qntMax == 0)
  {
    return;
  }
  else
  {
    
  }

  printf("Maximo produto %d %d %d.\n", idp, idMin, qntMax);
}

void listProdInSys(prod v[])
{
  prod r[10000];
  int x;
  int z;
  for (z = 0; z < act; z++)
  {
    r[z].prod_id = v[z].prod_id;
    strcpy(r[z].prod_desc, v[z].prod_desc);
    r[z].prod_price = v[z].prod_price;
    r[z].prod_st = v[z].prod_st;
  }

  insertionSort(r, 0, act - 1);
  printf("Produtos\n");
  for (x = 0; x < act; x++)
  {
    printf("* %s %d %d\n", r[x].prod_desc, r[x].prod_price, r[x].prod_st);
  }

}

void listProdInOrd(prod v[], order t[])
{
  prod c[200];
  int EE;
  int x;
  int z;
  int n;
  int ide;
  int i = 0;
  ide = new_sym_var(sizeof(int) * 8);
  EE = existE(i, order_act, ide, t);
  if ((ide != t[EE].order_id) || (order_act == 0))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    
  }

  if ((t[EE].order_prod_act == 0) || (t[EE].order_w == 0))
  {
    {
      printf("Encomenda %d\n", ide);
      return;
    }
  }
  else
  {
    
  }

  for (n = 0; n < t[EE].order_prod_act; n++)
  {
    for (z = 0; z < act; z++)
    {
      if (t[EE].order_prods[n] == v[z].prod_id)
      {
        {
          strcpy(c[n].prod_desc, v[z].prod_desc);
          c[n].prod_price = v[z].prod_price;
          c[n].prod_st = t[EE].order_qnt[n];
        }
      }
      else
      {
        
      }

    }

  }

  quicksort(c, 0, t[EE].order_prod_act - 1);
  printf("Encomenda %d\n", ide);
  for (x = 0; x < t[EE].order_prod_act; x++)
  {
    if (c[x].prod_st != 0)
    {
      printf("* %s %d %d\n", c[x].prod_desc, c[x].prod_price, c[x].prod_st);
    }
    else
    {
      
    }

  }

  return;
}

int main()
{
  prod system[10000];
  order orders[500];
  char sel = getchar();
  while (sel != 'x')
  {
    switch (sel)
    {
      case 'a':
        addProd(system);
        break;

      case 'q':
        addStock(system);
        break;

      case 'N':
        newOrder(orders);
        break;

      case 'A':
        addProdToOrder(system, orders);
        break;

      case 'r':
        removeStockProd(system);
        break;

      case 'R':
        removeProdFromOrder(system, orders);
        break;

      case 'C':
        costOrder(system, orders);
        break;

      case 'p':
        changeProdPrice(system);
        break;

      case 'E':
        listProdQ(system, orders);
        break;

      case 'm':
        maxProd(system, orders);
        break;

      case 'l':
        listProdInSys(system);
        break;

      case 'L':
        listProdInOrd(system, orders);
        break;

    }

    sel = getchar();
  }

  return 0;
}
