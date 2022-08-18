/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


int id_atual_prod = 0;
int id_atual_enc = 0;
typedef struct produto
{
  int id;
  char desc[64];
  int preco;
  int peso;
  int stock;
} Produto;
typedef struct encomenda
{
  int quantidades[10000];
  int peso;
} Encomenda;
Produto produtos[10000];
Encomenda encomendas[500];
int verifEncomenda(int ide)
{
  if (ide >= id_atual_enc)
  {
    return 0;
  }
  else
  {
    
  }

  return 1;
}

int verifProduto(int idp)
{
  if (idp >= id_atual_prod)
  {
    return 0;
  }
  else
  {
    
  }

  return 1;
}

int contido(Produto produto, Encomenda enc)
{
  if (enc.quantidades[produto.id] > 0)
  {
    return 1;
  }
  else
  {
    
  }

  return 0;
}

int less(Produto p1, Produto p2, char modo)
{
  if (modo == 's')
  {
    {
      if (strcmp(p1.desc, p2.desc) < 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }

    }
  }
  else
  {
    {
      if (p1.preco < p2.preco)
      {
        return 1;
      }
      else
      {
        {
          if (p1.preco == p2.preco)
          {
            return p1.id < p2.id;
          }
          else
          {
            return 0;
          }

        }
      }

    }
  }

}

void merge(Produto produtos[], int left, int m, int right, char modo)
{
  Produto aux[10000];
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = produtos[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = produtos[j + 1];

  for (k = left; k <= right; k++)
  {
    if (less(aux[j], aux[i], modo) || (i > m))
    {
      produtos[k] = aux[j--];
    }
    else
    {
      produtos[k] = aux[i++];
    }

  }

}

void mergeSort(Produto produtos[], int left, int right, char modo)
{
  int m = (right + left) / 2;
  if (left < right)
  {
    {
      mergeSort(produtos, left, m, modo);
      mergeSort(produtos, m + 1, right, modo);
      merge(produtos, left, m, right, modo);
    }
  }
  else
  {
    
  }

}

void func_a()
{
  Produto a;
  a = produtos[id_atual_prod];
  for (int a_index = 0; a_index < 10; a_index++)
  {
    a.desc[a_index] = new_sym_var(sizeof(char) * 8);
  }

  a.desc[10 - 1] = '\0';
  a.preco = new_sym_var(sizeof(int) * 8);
  a.peso = new_sym_var(sizeof(int) * 8);
  a.stock = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", id_atual_prod);
  a.id = id_atual_prod;
  produtos[id_atual_prod] = a;
  ++id_atual_prod;
}

void func_q()
{
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id >= id_atual_prod)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
  }
  else
  {
    produtos[id].stock += qtd;
  }

}

void func_N()
{
  int contador = 0;
  printf("Nova encomenda %d.\n", id_atual_enc);
  encomendas[id_atual_enc].peso = 0;
  while (contador <= 10000)
  {
    encomendas[id_atual_enc].quantidades[contador] = 0;
    ++contador;
  }

  ++id_atual_enc;
}

void func_A()
{
  int ide;
  int idp;
  int qtdpedida;
  int novopeso;
  Encomenda e;
  Produto p;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtdpedida = new_sym_var(sizeof(int) * 8);
  if (!verifEncomenda(ide))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    {
      e = encomendas[ide];
      if (!verifProduto(idp))
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
      else
      {
        {
          p = produtos[idp];
          if (qtdpedida > p.stock)
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
          }
          else
          {
            {
              novopeso = e.peso + (p.peso * qtdpedida);
              if (novopeso > 200)
              {
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idp, ide, 200);
              }
              else
              {
                {
                  e.peso = novopeso;
                  e.quantidades[idp] += qtdpedida;
                  p.stock -= qtdpedida;
                  encomendas[ide] = e;
                  produtos[idp] = p;
                }
              }

            }
          }

        }
      }

    }
  }

}

void func_r()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= id_atual_prod)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    {
      if (produtos[idp].stock < qtd)
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
      }
      else
      {
        {
          produtos[idp].stock -= qtd;
        }
      }

    }
  }

}

void func_R()
{
  int ide;
  int idp;
  Encomenda e;
  Produto p;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (!verifEncomenda(ide))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    {
      e = encomendas[ide];
      if (!verifProduto(idp))
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
      else
      {
        {
          p = produtos[idp];
          e.peso -= p.peso * e.quantidades[idp];
          p.stock += e.quantidades[idp];
          e.quantidades[idp] = 0;
          encomendas[ide] = e;
          produtos[idp] = p;
        }
      }

    }
  }

}

void func_C()
{
  int ide;
  int total = 0;
  int contador = id_atual_prod;
  Encomenda e;
  Produto p;
  ide = new_sym_var(sizeof(int) * 8);
  if (!verifEncomenda(ide))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    {
      e = encomendas[ide];
      while ((--contador) >= 0)
      {
        p = produtos[contador];
        total += p.preco * e.quantidades[contador];
      }

      printf("Custo da encomenda %d %d.\n", ide, total);
    }
  }

}

void func_p()
{
  int idp;
  int novopreco;
  idp = new_sym_var(sizeof(int) * 8);
  novopreco = new_sym_var(sizeof(int) * 8);
  if (!verifProduto(idp))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    produtos[idp].preco = novopreco;
  }

}

void func_E()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (!verifEncomenda(ide))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    {
      if (!verifProduto(idp))
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        {
          printf("%s %d.\n", produtos[idp].desc, encomendas[ide].quantidades[idp]);
        }
      }

    }
  }

}

void func_m()
{
  int idp;
  int contador = 0;
  int ide_mais_ocorrencias = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (!verifProduto(idp))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    {
      while ((++contador) < id_atual_enc)
        if (encomendas[contador].quantidades[idp] > encomendas[ide_mais_ocorrencias].quantidades[idp])
      {
        ide_mais_ocorrencias = contador;
      }
      else
      {
        
      }


      if ((encomendas[ide_mais_ocorrencias].quantidades[idp] > 0) && (id_atual_enc > 0))
      {
        printf("Maximo produto %d %d %d.\n", idp, ide_mais_ocorrencias, encomendas[ide_mais_ocorrencias].quantidades[idp]);
      }
      else
      {
        
      }

    }
  }

}

void func_l()
{
  Produto a[10000];
  int contador = -1;
  while ((++contador) < id_atual_prod)
    a[contador] = produtos[contador];

  mergeSort(a, 0, id_atual_prod - 1, 'p');
  printf("Produtos\n");
  contador = -1;
  while ((++contador) < id_atual_prod)
    printf("* %s %d %d\n", a[contador].desc, a[contador].preco, a[contador].stock);

}

void func_L()
{
  Produto a[10000];
  int contador_a = 0;
  int contador_e = -1;
  int ide;
  int indicefinal;
  ide = new_sym_var(sizeof(int) * 8);
  if (!verifEncomenda(ide))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    {
      while ((++contador_e) < id_atual_prod)
        if (encomendas[ide].quantidades[contador_e] > 0)
      {
        {
          a[contador_a] = produtos[contador_e];
          ++contador_a;
        }
      }
      else
      {
        
      }


      indicefinal = contador_a;
      mergeSort(a, 0, indicefinal, 's');
      contador_a = -1;
      printf("Encomenda %d\n", ide);
      while ((++contador_a) < indicefinal)
        printf("* %s %d %d\n", a[contador_a].desc, a[contador_a].preco, encomendas[ide].quantidades[a[contador_a].id]);

    }
  }

}

int main()
{
  char c;
  while ((c = getchar()) != 'x')
    switch (c)
  {
    case 'a':
      func_a();
      break;

    case 'q':
      func_q();
      break;

    case 'N':
      func_N();
      break;

    case 'A':
      func_A();
      break;

    case 'r':
      func_r();
      break;

    case 'R':
      func_R();
      break;

    case 'C':
      func_C();
      break;

    case 'p':
      func_p();
      break;

    case 'E':
      func_E();
      break;

    case 'm':
      func_m();
      break;

    case 'l':
      func_l();
      break;

    case 'L':
      func_L();

    default:
      break;

  }


  return 0;
}

