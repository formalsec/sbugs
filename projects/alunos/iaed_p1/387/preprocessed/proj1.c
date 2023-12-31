#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int idp;
  char des[63];
  int preco;
  int peso;
  int stock;
} Produto;
typedef struct 
{
  int qnt_prod;
  Produto lista[10000];
} Encomenda;
Produto prod_exis[10000];
Encomenda enc_exis[500];
int idp_atual = 0;
int ide_atual = 0;
int opcao;
int existe_enc(int id)
{
  return id < ide_atual;
}

int existe_prod_lista(int idp, Produto list[], int limite)
{
  int i;
  for (i = 0; i < limite; i++)
    if (list[i].idp == idp)
  {
    return i;
  }
  else
  {
    
  }


  return -1;
}

void ad_prod()
{
  Produto p;
  for (int p_index = 0; p_index < 10; p_index++)
  {
    p.des[p_index] = new_sym_var(sizeof(char) * 8);
  }

  p.des[10 - 1] = '\0';
  p.preco = new_sym_var(sizeof(int) * 8);
  p.peso = new_sym_var(sizeof(int) * 8);
  p.stock = new_sym_var(sizeof(int) * 8);
  p.idp = idp_atual;
  prod_exis[idp_atual] = p;
  printf("Novo produto %d.\n", idp_atual++);
}

void ad_encomenda()
{
  printf("Nova encomenda %d.\n", ide_atual++);
}

void ad_stock()
{
  int idp;
  int stock;
  idp = new_sym_var(sizeof(int) * 8);
  stock = new_sym_var(sizeof(int) * 8);
  if (existe_prod_lista(idp, prod_exis, idp_atual) > (-1))
  {
    prod_exis[idp].stock += stock;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

}

void ad_prod_enc()
{
  int ide;
  int idp;
  int stock;
  int idp_enc;
  int id_qtd_encomendas;
  int i;
  int peso_total = 0;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  stock = new_sym_var(sizeof(int) * 8);
  if (!existe_enc(ide))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (existe_prod_lista(idp, prod_exis, idp_atual) == (-1))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (prod_exis[idp].stock < stock)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        id_qtd_encomendas = enc_exis[ide].qnt_prod;
        for (i = 0; i < id_qtd_encomendas; i++)
        {
          peso_total += enc_exis[ide].lista[i].stock * enc_exis[ide].lista[i].peso;
        }

        if ((peso_total + (stock * prod_exis[idp].peso)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          if (existe_prod_lista(idp, enc_exis[ide].lista, enc_exis[ide].qnt_prod) == (-1))
          {
            enc_exis[ide].lista[id_qtd_encomendas] = prod_exis[idp];
            enc_exis[ide].lista[id_qtd_encomendas].stock = stock;
            enc_exis[ide].qnt_prod++;
            prod_exis[idp].stock -= stock;
          }
          else
          {
            idp_enc = existe_prod_lista(idp, enc_exis[ide].lista, enc_exis[ide].qnt_prod);
            enc_exis[ide].lista[idp_enc].stock += stock;
            prod_exis[idp].stock -= stock;
          }

        }

      }

    }

  }

}

void remove_stock()
{
  int id_p;
  int qtd;
  id_p = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (existe_prod_lista(id_p, prod_exis, idp_atual) == (-1))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_p);
  }
  else
  {
    if ((prod_exis[id_p].stock - qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id_p);
    }
    else
    {
      prod_exis[id_p].stock -= qtd;
    }

  }

}

void remove_prod_enc()
{
  int ide;
  int idp;
  int idprod_enc;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (!existe_enc(ide))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (existe_prod_lista(idp, prod_exis, idp_atual) == (-1))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      idprod_enc = existe_prod_lista(idp, enc_exis[ide].lista, enc_exis[ide].qnt_prod);
      if (idprod_enc > (-1))
      {
        prod_exis[idp].stock += enc_exis[ide].lista[idprod_enc].stock;
        enc_exis[ide].lista[idprod_enc].stock = 0;
      }
      else
      {
        
      }

    }

  }

}

void custo_enc()
{
  int i;
  int ide;
  int total = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (!existe_enc(ide))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i < enc_exis[ide].qnt_prod; i++)
      total += enc_exis[ide].lista[i].stock * enc_exis[ide].lista[i].preco;

    printf("Custo da encomenda %d %d.\n", ide, total);
  }

}

void altera_preco()
{
  int i;
  int idp;
  int novo_preco;
  int idprod_enc;
  idp = new_sym_var(sizeof(int) * 8);
  novo_preco = new_sym_var(sizeof(int) * 8);
  if (existe_prod_lista(idp, prod_exis, idp_atual) == (-1))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    prod_exis[idp].preco = novo_preco;
    for (i = 0; i < ide_atual; i++)
    {
      idprod_enc = existe_prod_lista(idp, enc_exis[i].lista, enc_exis[i].qnt_prod);
      if (idprod_enc != (-1))
      {
        enc_exis[i].lista[idprod_enc].preco = novo_preco;
      }
      else
      {
        
      }

    }

  }

}

void desc_qtd_prod_enc()
{
  int ide;
  int idp;
  int idprod_enc;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (!existe_enc(ide))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (existe_prod_lista(idp, prod_exis, idp_atual) == (-1))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      idprod_enc = existe_prod_lista(idp, enc_exis[ide].lista, enc_exis[ide].qnt_prod);
      if (idprod_enc > (-1))
      {
        printf("%s %d.\n", prod_exis[idp].des, enc_exis[ide].lista[idprod_enc].stock);
      }
      else
      {
        printf("%s 0.\n", prod_exis[idp].des);
      }

    }

  }

}

void max_prod()
{
  int i;
  int idp;
  int idprod_enc;
  int qtd_max = -1;
  int ide_max = -1;
  idp = new_sym_var(sizeof(int) * 8);
  if (existe_prod_lista(idp, prod_exis, idp_atual) == (-1))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < ide_atual; i++)
    {
      idprod_enc = existe_prod_lista(idp, enc_exis[i].lista, enc_exis[i].qnt_prod);
      if (idprod_enc != (-1))
      {
        if (enc_exis[i].lista[idprod_enc].stock > qtd_max)
        {
          qtd_max = enc_exis[i].lista[idprod_enc].stock;
          ide_max = i;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

    if (qtd_max > 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, ide_max, qtd_max);
    }
    else
    {
      
    }

  }

}

int compara_prod(Produto a, Produto v)
{
  if (opcao == 0)
  {
    if (a.preco == v.preco)
    {
      return a.idp < v.idp;
    }
    else
    {
      return a.preco < v.preco;
    }

  }
  else
  {
    return strcmp(a.des, v.des) < 0;
  }

}

void quicksort(Produto a[], int l, int r)
{
  int i;
  int j;
  Produto v;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  i = l - 1;
  j = r;
  v = a[r];
  while (i < j)
  {
    while (compara_prod(a[++i], v))
      ;

    while (compara_prod(v, a[--j]))
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
      Produto t = a[i];
      a[i] = a[j];
      a[j] = t;
    }
    else
    {
      
    }

    ;
  }

  {
    Produto t = a[i];
    a[i] = a[r];
    a[r] = t;
  }
  ;
  quicksort(a, l, i - 1);
  quicksort(a, i + 1, r);
}

void ordena_prod_exis()
{
  int i;
  Produto copia[10000];
  for (i = 0; i < idp_atual; i++)
  {
    copia[i] = prod_exis[i];
  }

  opcao = 0;
  quicksort(copia, 0, idp_atual - 1);
  printf("Produtos\n");
  for (i = 0; i < idp_atual; i++)
  {
    printf("* %s %d %d\n", copia[i].des, copia[i].preco, copia[i].stock);
  }

}

void ordena_encomenda()
{
  int i;
  int qtd;
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (!existe_enc(ide))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    qtd = enc_exis[ide].qnt_prod;
    opcao = 1;
    quicksort(enc_exis[ide].lista, 0, qtd - 1);
    printf("Encomenda %d\n", ide);
    for (i = 0; i < qtd; i++)
    {
      if (enc_exis[ide].lista[i].stock > 0)
      {
        printf("* %s %d %d\n", enc_exis[ide].lista[i].des, enc_exis[ide].lista[i].preco, enc_exis[ide].lista[i].stock);
      }
      else
      {
        
      }

    }

  }

}

int main()
{
  char c;
  while ((1 != EOF) && (c != 'x'))
  {
    c = new_sym_var(sizeof(char) * 8);
    switch (c)
    {
      case 'a':
        ad_prod();
        break;

      case 'q':
        ad_stock();
        break;

      case 'N':
        ad_encomenda();
        break;

      case 'A':
        ad_prod_enc();
        break;

      case 'r':
        remove_stock();
        break;

      case 'R':
        remove_prod_enc();
        break;

      case 'C':
        custo_enc();
        break;

      case 'p':
        altera_preco();
        break;

      case 'E':
        desc_qtd_prod_enc();
        break;

      case 'm':
        max_prod();
        break;

      case 'l':
        ordena_prod_exis();
        break;

      case 'L':
        ordena_encomenda();
        break;

    }

  }

  return 0;
}

