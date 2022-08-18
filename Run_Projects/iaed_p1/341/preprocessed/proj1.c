/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  char descricao[64];
  int preco;
  int peso;
  int qtd;
  int id;
} Produto;
typedef struct encomenda
{
  int peso;
  int preco;
  int cont;
  Produto item[200];
} Encomenda;
int cont_produto = 0;
int cont_encomenda = 0;
Produto sistema_produtos[10000];
Produto auxiliar[10000];
Encomenda sistema_encomendas[500];
int mesmosProdutos(Produto p1, Produto p2)
{
  if (p1.id == p2.id)
  {
    return 1;
  }
  else
  {
    
  }

  return 0;
}

int eh_id_invalido(int id, int cont)
{
  if ((id >= cont) || (id < 0))
  {
    return 1;
  }
  else
  {
    
  }

  return 0;
}

void print_produtos(int cont, Produto vetor[])
{
  int i;
  for (i = 0; i < cont; i++)
  {
    printf("* %s %d %d\n", vetor[i].descricao, vetor[i].preco, vetor[i].qtd);
  }

}

void copia(Produto v1[], Produto v2[])
{
  int i;
  for (i = 0; i < cont_produto; i++)
  {
    v1[i] = v2[i];
  }

}

void troca(Produto vetor[], int i)
{
  Produto temp;
  temp = vetor[i + 1];
  vetor[i + 1] = vetor[i];
  vetor[i] = temp;
  temp = vetor[i];
}

void merge(Produto produtos[], int lim_esq, int meio, int lim_dir)
{
  int i;
  int j;
  int k;
  for (i = meio + 1; i > lim_esq; i--)
  {
    auxiliar[i - 1] = produtos[i - 1];
  }

  for (j = meio; j < lim_dir; j++)
  {
    auxiliar[(lim_dir + meio) - j] = produtos[j + 1];
  }

  for (k = lim_esq; k <= lim_dir; k++)
  {
    if (auxiliar[j].preco < auxiliar[i].preco)
    {
      {
        produtos[k] = auxiliar[j];
        j--;
      }
    }
    else
    {
      if (auxiliar[i].preco < auxiliar[j].preco)
      {
        {
          produtos[k] = auxiliar[i];
          i++;
        }
      }
      else
      {
        if (auxiliar[j].id < auxiliar[i].id)
        {
          {
            produtos[k] = auxiliar[j];
            j--;
          }
        }
        else
        {
          {
            produtos[k] = auxiliar[i];
            i++;
          }
        }

      }

    }

  }

}

void mergesort(Produto produtos[], int lim_esq, int lim_dir)
{
  int meio = (lim_dir + lim_esq) / 2;
  if (!(lim_dir <= lim_esq))
  {
    {
      mergesort(produtos, lim_esq, meio);
      mergesort(produtos, meio + 1, lim_dir);
      merge(produtos, lim_esq, meio, lim_dir);
    }
  }
  else
  {
    
  }

}

void ordena(Produto vetor[], int len)
{
  int i;
  int ha_troca;
  do
  {
    ha_troca = 0;
    for (i = 0; i < (len - 1); i++)
    {
      if (strcmp(vetor[i].descricao, vetor[i + 1].descricao) > 0)
      {
        {
          troca(vetor, i);
          ha_troca = 1;
        }
      }
      else
      {
        
      }

    }

  }
  while (ha_troca);
}

void func_a(Produto produto)
{
  printf("Novo produto %d.\n", cont_produto);
  produto.id = cont_produto;
  sistema_produtos[cont_produto] = produto;
  cont_produto++;
}

void func_q(int idp, int qtd)
{
  if (eh_id_invalido(idp, cont_produto))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    sistema_produtos[idp].qtd += qtd;
  }

}

void func_N()
{
  printf("Nova encomenda %d.\n", cont_encomenda);
  sistema_encomendas[cont_encomenda].peso = 0;
  sistema_encomendas[cont_encomenda].cont = 0;
  sistema_encomendas[cont_encomenda].preco = 0;
  cont_encomenda++;
}

void func_A(int ide, int idp, int qtd)
{
  int i;
  int contem = 0;
  if (eh_id_invalido(ide, cont_encomenda))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (eh_id_invalido(idp, cont_produto))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (sistema_produtos[idp].qtd < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if (((sistema_produtos[idp].peso * qtd) + sistema_encomendas[ide].peso) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          {
            for (i = 0; i < sistema_encomendas[ide].cont; i++)
            {
              if (mesmosProdutos(sistema_encomendas[ide].item[i], sistema_produtos[idp]))
              {
                {
                  contem = 1;
                  break;
                }
              }
              else
              {
                
              }

            }

            if (contem)
            {
              {
                sistema_encomendas[ide].item[i].qtd += qtd;
              }
            }
            else
            {
              {
                sistema_encomendas[ide].item[sistema_encomendas[ide].cont] = sistema_produtos[idp];
                sistema_encomendas[ide].item[sistema_encomendas[ide].cont].qtd = qtd;
                sistema_encomendas[ide].cont++;
              }
            }

            sistema_encomendas[ide].peso += sistema_produtos[idp].peso * qtd;
            sistema_encomendas[ide].preco += sistema_produtos[idp].preco * qtd;
            sistema_produtos[idp].qtd -= qtd;
          }
        }

      }

    }

  }

}

void func_r(int idp, int qtd)
{
  if (eh_id_invalido(idp, cont_produto))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if ((sistema_produtos[idp].qtd - qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      sistema_produtos[idp].qtd -= qtd;
    }

  }

}

void func_R(int ide, int idp)
{
  int i;
  int j;
  if (eh_id_invalido(ide, cont_encomenda))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (eh_id_invalido(idp, cont_produto))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      {
        for (i = 0; i < sistema_encomendas[ide].cont; i++)
        {
          if (mesmosProdutos(sistema_encomendas[ide].item[i], sistema_produtos[idp]))
          {
            {
              sistema_produtos[idp].qtd += sistema_encomendas[ide].item[i].qtd;
              sistema_encomendas[ide].peso -= sistema_encomendas[ide].item[i].qtd * sistema_encomendas[ide].item[i].peso;
              sistema_encomendas[ide].preco -= sistema_encomendas[ide].item[i].qtd * sistema_encomendas[ide].item[i].preco;
              j = i;
              while (j != sistema_encomendas[ide].cont)
              {
                sistema_encomendas[ide].item[j] = sistema_encomendas[ide].item[j + 1];
                j++;
              }

              sistema_encomendas[ide].cont--;
              break;
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

void func_C(int ide)
{
  if (eh_id_invalido(ide, cont_encomenda))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", ide, sistema_encomendas[ide].preco);
  }

}

void func_p(int idp, int preco)
{
  int i;
  int j;
  if (eh_id_invalido(idp, cont_produto))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    {
      sistema_produtos[idp].preco = preco;
      for (i = 0; i < cont_encomenda; i++)
      {
        for (j = 0; j < sistema_encomendas[i].cont; j++)
        {
          if (mesmosProdutos(sistema_encomendas[i].item[j], sistema_produtos[idp]))
          {
            {
              sistema_encomendas[i].preco -= sistema_encomendas[i].item[j].qtd * sistema_encomendas[i].item[j].preco;
              sistema_encomendas[i].item[j].preco = preco;
              sistema_encomendas[i].preco += sistema_encomendas[i].item[j].qtd * sistema_encomendas[i].item[j].preco;
              break;
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

void func_E(int ide, int idp)
{
  int i;
  if (eh_id_invalido(ide, cont_encomenda))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (eh_id_invalido(idp, cont_produto))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      {
        for (i = 0; i < sistema_encomendas[ide].cont; i++)
        {
          if (mesmosProdutos(sistema_encomendas[ide].item[i], sistema_produtos[idp]))
          {
            {
              printf("%s %d.\n", sistema_produtos[idp].descricao, sistema_encomendas[ide].item[i].qtd);
              return;
            }
          }
          else
          {
            
          }

        }

        printf("%s %d.\n", sistema_produtos[idp].descricao, 0);
      }
    }

  }

}

void func_m(int idp)
{
  int i;
  int j;
  int qtd = 0;
  int ide = 0;
  int contem = 0;
  if (eh_id_invalido(idp, cont_produto))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    {
      for (i = 0; i < cont_encomenda; i++)
      {
        for (j = 0; j < sistema_encomendas[i].cont; j++)
        {
          if (mesmosProdutos(sistema_encomendas[i].item[j], sistema_produtos[idp]) && (qtd < sistema_encomendas[i].item[j].qtd))
          {
            {
              qtd = sistema_encomendas[i].item[j].qtd;
              ide = i;
              contem = 1;
              break;
            }
          }
          else
          {
            
          }

        }

      }

      if (contem)
      {
        printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
      }
      else
      {
        
      }

    }
  }

}

void func_l()
{
  Produto syst_copia[10000];
  copia(syst_copia, sistema_produtos);
  mergesort(syst_copia, 0, cont_produto - 1);
  printf("Produtos\n");
  print_produtos(cont_produto, syst_copia);
}

void func_L(int ide)
{
  if (eh_id_invalido(ide, cont_encomenda))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    {
      ordena(sistema_encomendas[ide].item, sistema_encomendas[ide].cont);
      printf("Encomenda %d\n", ide);
      print_produtos(sistema_encomendas[ide].cont, sistema_encomendas[ide].item);
    }
  }

}

int main()
{
  int idp;
  int ide;
  int qtd;
  int preco;
  char comando;
  int run = 1;
  Produto produto;
  while (run)
  {
    comando = getchar();
    switch (comando)
    {
      case 'a':
        for (int produto_index = 0; produto_index < 10; produto_index++)
      {
        produto.descricao[produto_index] = new_sym_var(sizeof(char) * 8);
      }

        produto.descricao[10 - 1] = '\0';
        produto.preco = new_sym_var(sizeof(int) * 8);
        produto.peso = new_sym_var(sizeof(int) * 8);
        produto.qtd = new_sym_var(sizeof(int) * 8);
        func_a(produto);
        break;

      case 'q':
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        func_q(idp, qtd);
        break;

      case 'N':
        func_N();
        break;

      case 'A':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        func_A(ide, idp, qtd);
        break;

      case 'r':
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        func_r(idp, qtd);
        break;

      case 'R':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        func_R(ide, idp);
        break;

      case 'C':
        ide = new_sym_var(sizeof(int) * 8);
        func_C(ide);
        break;

      case 'p':
        idp = new_sym_var(sizeof(int) * 8);
        preco = new_sym_var(sizeof(int) * 8);
        func_p(idp, preco);
        break;

      case 'E':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        func_E(ide, idp);
        break;

      case 'm':
        idp = new_sym_var(sizeof(int) * 8);
        func_m(idp);
        break;

      case 'l':
        func_l();
        break;

      case 'L':
        ide = new_sym_var(sizeof(int) * 8);
        func_L(ide);
        break;

      case 'x':
        run = 0;
        break;

      default:
        continue;

    }

  }

  return 0;
}

