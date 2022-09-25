/*File generated by PreProcessor.py*/


#include <stdio.h>				/*Livrarias */
#include <string.h>				/*Livrarias */


typedef struct produto
{
  int identificador;
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
} produto;
produto stock_produto[10000];
int num_total_produtos = 0;
void adiciona_stock(int prodident, int prodqtd)
{
  if (prodident >= num_total_produtos)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prodident);
  }
  else
  {
    stock_produto[prodident].quantidade += prodqtd;
  }

}

void remove_stock_prod(int prodident, int prodqtd)
{
  if (prodident >= num_total_produtos)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prodident);
  }
  else
  {
    if (stock_produto[prodident].quantidade < prodqtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", prodqtd, prodident);
    }
    else
    {
      stock_produto[prodident].quantidade -= prodqtd;
    }

  }

}

void adiciona_produto(char proddesc[], int prodpreco, int prodpeso, int prodqtd)
{
  int novo_prod_id;
  int lendesc;
  if (num_total_produtos == 10000)
  {
    return;
  }
  else
  {
    
  }

  novo_prod_id = num_total_produtos++;
  stock_produto[novo_prod_id].identificador = novo_prod_id;
  lendesc = strlen(proddesc);
  strncpy(stock_produto[novo_prod_id].descricao, proddesc, lendesc);
  stock_produto[novo_prod_id].preco = prodpreco;
  stock_produto[novo_prod_id].peso = prodpeso;
  stock_produto[novo_prod_id].quantidade = prodqtd;
  printf("Novo produto %d.\n", novo_prod_id);
}

void altera_prod_preco(int prodident, int prodpreco)
{
  if (prodident >= num_total_produtos)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prodident);
  }
  else
  {
    stock_produto[prodident].preco = prodpreco;
  }

}

void mostra_produto(produto prod)
{
  printf("* %s %d %d\n", prod.descricao, prod.preco, prod.quantidade);
}

typedef struct prod_qtd
{
  int produto_id;
  int quantidade;
} prod_qtd;
typedef struct encomenda
{
  int identificador;
  prod_qtd prods[10000];
  int num_prods;
  int peso_total;
} encomenda;
encomenda encomendas[500];
int num_total_encomendas = 0;
void nova_encomenda()
{
  int nova_encom_id;
  if (num_total_encomendas == 500)
  {
    return;
  }
  else
  {
    
  }

  nova_encom_id = num_total_encomendas++;
  encomendas[nova_encom_id].identificador = nova_encom_id;
  encomendas[nova_encom_id].num_prods = 0;
  encomendas[nova_encom_id].peso_total = 0;
  printf("Nova encomenda %d.\n", nova_encom_id);
}

void adiciona_produto_encomenda(int encident, int prodident, int prodqtd)
{
  int peso_adicional;
  int prod_enc_id;
  int i;
  if (encident >= num_total_encomendas)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prodident, encident);
    return;
  }
  else
  {
    
  }

  if (prodident >= num_total_produtos)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prodident, encident);
    return;
  }
  else
  {
    
  }

  if (prodqtd > stock_produto[prodident].quantidade)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prodident, encident);
    return;
  }
  else
  {
    
  }

  peso_adicional = stock_produto[prodident].peso * prodqtd;
  if ((encomendas[encident].peso_total + peso_adicional) > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prodident, encident);
    return;
  }
  else
  {
    
  }

  stock_produto[prodident].quantidade -= prodqtd;
  encomendas[encident].peso_total += peso_adicional;
  prod_enc_id = -1;
  for (i = 0; i < encomendas[encident].num_prods; i++)
    if (encomendas[encident].prods[i].produto_id == prodident)
  {
    prod_enc_id = i;
  }
  else
  {
    
  }


  if (prod_enc_id == (-1))
  {
    prod_enc_id = encomendas[encident].num_prods++;
    encomendas[encident].prods[prod_enc_id].produto_id = prodident;
    encomendas[encident].prods[prod_enc_id].quantidade = 0;
  }
  else
  {
    
  }

  encomendas[encident].prods[prod_enc_id].quantidade += prodqtd;
}

void remove_prod_enc(int encident, int prodident)
{
  int prod_enc_id;
  int i;
  int qtd_add_stock;
  int peso_remover;
  int numprods;
  if (encident >= num_total_encomendas)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prodident, encident);
    return;
  }
  else
  {
    
  }

  if (prodident >= num_total_produtos)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prodident, encident);
    return;
  }
  else
  {
    
  }

  prod_enc_id = -1;
  for (i = 0; i < encomendas[encident].num_prods; i++)
    if (encomendas[encident].prods[i].produto_id == prodident)
  {
    prod_enc_id = i;
  }
  else
  {
    
  }


  if (prod_enc_id == (-1))
  {
    return;
  }
  else
  {
    
  }

  qtd_add_stock = encomendas[encident].prods[prod_enc_id].quantidade;
  peso_remover = stock_produto[prodident].peso * qtd_add_stock;
  encomendas[encident].peso_total -= peso_remover;
  numprods = encomendas[encident].num_prods;
  if ((numprods > 1) && (prodident != encomendas[encident].prods[numprods - 1].produto_id))
  {
    for (i = prod_enc_id; i < (numprods - 1); i++)
    {
      encomendas[encident].prods[i].produto_id = encomendas[encident].prods[i + 1].produto_id;
      encomendas[encident].prods[i].quantidade = encomendas[encident].prods[i + 1].quantidade;
    }

  }
  else
  {
    
  }

  encomendas[encident].num_prods--;
  stock_produto[prodident].quantidade += qtd_add_stock;
}

void custo_enc(int encident)
{
  int custo_total;
  int id_aux;
  int qtd_aux;
  int i;
  if (encident >= num_total_encomendas)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", encident);
    return;
  }
  else
  {
    
  }

  custo_total = 0;
  for (i = 0; i < encomendas[encident].num_prods; i++)
  {
    id_aux = encomendas[encident].prods[i].produto_id;
    qtd_aux = encomendas[encident].prods[i].quantidade;
    custo_total += stock_produto[id_aux].preco * qtd_aux;
  }

  printf("Custo da encomenda %d %d.\n", encident, custo_total);
  ;
}

void procuramax_prod_enc(int prodident)
{
  int maxqtd;
  int encid;
  int eid;
  int i;
  encid = -1;
  maxqtd = -1;
  if (prodident >= num_total_produtos)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prodident);
    return;
  }
  else
  {
    
  }

  for (eid = 0; eid < num_total_encomendas; eid++)
    for (i = 0; i < encomendas[eid].num_prods; i++)
    if (encomendas[eid].prods[i].produto_id == prodident)
  {
    if (encomendas[eid].prods[i].quantidade > maxqtd)
    {
      encid = eid;
      maxqtd = encomendas[eid].prods[i].quantidade;
    }
    else
    {
      
    }

  }
  else
  {
    
  }



  if (encid > (-1))
  {
    printf("Maximo produto %d %d %d.\n", prodident, encid, maxqtd);
  }
  else
  {
    
  }

}

void lista_quant_prod_encomenda(int encident, int prodident)
{
  int ind_prodenc;
  int i;
  if (encident >= num_total_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", encident);
    return;
  }
  else
  {
    
  }

  if (prodident >= num_total_produtos)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", prodident);
    return;
  }
  else
  {
    
  }

  ind_prodenc = -1;
  for (i = 0; i < encomendas[encident].num_prods; i++)
  {
    if (encomendas[encident].prods[i].produto_id == prodident)
    {
      ind_prodenc = i;
    }
    else
    {
      
    }

  }

  if (ind_prodenc == (-1))
  {
    printf("%s %d.\n", stock_produto[prodident].descricao, 0);
  }
  else
  {
    printf("%s %d.\n", stock_produto[prodident].descricao, encomendas[encident].prods[ind_prodenc].quantidade);
  }

}

void mostra_prod_enc(int encident, int prodidenc)
{
  int prodident = encomendas[encident].prods[prodidenc].produto_id;
  printf("* %s %d %d\n", stock_produto[prodident].descricao, stock_produto[prodident].preco, encomendas[encident].prods[prodidenc].quantidade);
}

int stock_prodids_ord[10000];
void init_prodord_array(int num_prods)
{
  int i;
  for (i = 0; i < num_prods; i++)
    stock_prodids_ord[i] = i;

}

void troca(int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int compara_prods(int encident, int idprod1, int idprod2)
{
  int resultado;
  if (encident == (-1))
  {
    if (stock_produto[idprod1].preco < stock_produto[idprod2].preco)
    {
      resultado = 1;
    }
    else
    {
      if ((stock_produto[idprod1].preco == stock_produto[idprod2].preco) && (idprod1 <= idprod2))
      {
        resultado = 1;
      }
      else
      {
        resultado = 0;
      }

    }

  }
  else
  {
    resultado = strcmp(stock_produto[encomendas[encident].prods[idprod1].produto_id].descricao, stock_produto[encomendas[encident].prods[idprod2].produto_id].descricao);
    if (resultado <= 0)
    {
      resultado = 1;
    }
    else
    {
      resultado = 0;
    }

  }

  return resultado;
}

void merge(int encident, int l, int m, int r)
{
  int i;
  int j;
  int k;
  const int n1 = (m - l) + 1;
  const int n2 = r - m;
  int L[10000];
  int R[10000];
  for (i = 0; i < n1; i++)
    L[i] = stock_prodids_ord[l + i];

  for (j = 0; j < n2; j++)
    R[j] = stock_prodids_ord[(m + 1) + j];

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (compara_prods(encident, L[i], R[j]))
    {
      stock_prodids_ord[k] = L[i];
      i++;
    }
    else
    {
      stock_prodids_ord[k] = R[j];
      j++;
    }

    k++;
  }

  while (i < n1)
  {
    stock_prodids_ord[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    stock_prodids_ord[k] = R[j];
    j++;
    k++;
  }

}

void mergeSort(int encident, int l, int r)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSort(encident, l, m);
    mergeSort(encident, m + 1, r);
    merge(encident, l, m, r);
  }
  else
  {
    
  }

}

void lista_prods_ordenado()
{
  int i;
  printf("Produtos\n");
  for (i = 0; i < num_total_produtos; i++)
    mostra_produto(stock_produto[stock_prodids_ord[i]]);

}

void lista_prods_encomenda_alf(int encident)
{
  int numprodsenc;
  int i;
  numprodsenc = encomendas[encident].num_prods;
  printf("Encomenda %d\n", encident);
  for (i = 0; i < numprodsenc; i++)
  {
    mostra_prod_enc(encident, stock_prodids_ord[i]);
  }

}

void lista_prods_ordenados(int encident)
{
  int numprodsenc;
  if (encident == (-1))
  {
    init_prodord_array(num_total_produtos);
    mergeSort(-1, 0, num_total_produtos - 1);
    lista_prods_ordenado();
  }
  else
  {
    if (encident >= num_total_encomendas)
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", encident);
      return;
    }
    else
    {
      
    }

    numprodsenc = encomendas[encident].num_prods;
    init_prodord_array(numprodsenc);
    mergeSort(encident, 0, numprodsenc - 1);
    lista_prods_encomenda_alf(encident);
  }

}

char cmd[1024];
char proddesc[63];
int encident;
int prodident;
int prodpreco;
int prodpeso;
int prodqtd;
void ler_comando()
{
  char *posnl;
  char *resultado;
  resultado = fgets(cmd, 100, stdin);
  if (resultado == 0)
  {
    cmd[0] = 'x';
    cmd[1] = 0;
  }
  else
  {
    
  }

  if ((posnl = strchr(cmd, '\n')) != 0)
  {
    *posnl = 0;
  }
  else
  {
    
  }

}

void processa_comando()
{
  int ncmds;
  switch (cmd[0])
  {
    case 'a':
      ncmds = 4;
      for (int proddesc_index = 0; proddesc_index < 10; proddesc_index++)
    {
      proddesc[proddesc_index] = new_sym_var(sizeof(char) * 8);
    }

      proddesc[10 - 1] = '\0';
      prodpreco = new_sym_var(sizeof(int) * 8);
      prodpeso = new_sym_var(sizeof(int) * 8);
      prodqtd = new_sym_var(sizeof(int) * 8);
      if (ncmds == 4)
    {
      adiciona_produto(proddesc, prodpreco, prodpeso, prodqtd);
    }
    else
    {
      
    }

      break;

    case 'l':
      lista_prods_ordenados(-1);
      break;

    case 'q':
      ncmds = 2;
      prodident = new_sym_var(sizeof(int) * 8);
      prodqtd = new_sym_var(sizeof(int) * 8);
      if (ncmds == 2)
    {
      adiciona_stock(prodident, prodqtd);
    }
    else
    {
      
    }

      break;

    case 'N':
      nova_encomenda();
      break;

    case 'A':
      ncmds = 3;
      encident = new_sym_var(sizeof(int) * 8);
      prodident = new_sym_var(sizeof(int) * 8);
      prodqtd = new_sym_var(sizeof(int) * 8);
      if (ncmds == 3)
    {
      adiciona_produto_encomenda(encident, prodident, prodqtd);
    }
    else
    {
      
    }

      break;

    case 'E':
      ncmds = 2;
      encident = new_sym_var(sizeof(int) * 8);
      prodident = new_sym_var(sizeof(int) * 8);
      if (ncmds == 2)
    {
      lista_quant_prod_encomenda(encident, prodident);
    }
    else
    {
      
    }

      break;

    case 'r':
      ncmds = 2;
      prodident = new_sym_var(sizeof(int) * 8);
      prodqtd = new_sym_var(sizeof(int) * 8);
      if (ncmds == 2)
    {
      remove_stock_prod(prodident, prodqtd);
    }
    else
    {
      
    }

      break;

    case 'R':
      ncmds = 2;
      encident = new_sym_var(sizeof(int) * 8);
      prodident = new_sym_var(sizeof(int) * 8);
      if (ncmds == 2)
    {
      remove_prod_enc(encident, prodident);
    }
    else
    {
      
    }

      break;

    case 'L':
      ncmds = 1;
      encident = new_sym_var(sizeof(int) * 8);
      if (ncmds == 1)
    {
      lista_prods_ordenados(encident);
    }
    else
    {
      
    }

      break;

    case 'C':
      ncmds = 1;
      encident = new_sym_var(sizeof(int) * 8);
      if (ncmds == 1)
    {
      custo_enc(encident);
    }
    else
    {
      
    }

      break;

    case 'p':
      ncmds = 2;
      prodident = new_sym_var(sizeof(int) * 8);
      prodpreco = new_sym_var(sizeof(int) * 8);
      if (ncmds == 2)
    {
      altera_prod_preco(prodident, prodpreco);
    }
    else
    {
      
    }

      break;

    case 'm':
      ncmds = 1;
      prodident = new_sym_var(sizeof(int) * 8);
      if (ncmds == 1)
    {
      procuramax_prod_enc(prodident);
    }
    else
    {
      
    }

      break;

    case 'x':
      break;

  }

}

int main()
{
  do
  {
    ler_comando();
    processa_comando();
  }
  while (cmd[0] != 'x');
  return 0;
}

