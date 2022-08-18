/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  int id;
  char desc[64];
  int preco;
  int peso;
  int qtd;
} produto;
typedef struct dados_encomenda
{
  int id;
  int qtd;
} dados_encomenda;
typedef struct encomenda
{
  int id;
  dados_encomenda item[200];
} encomenda;
produto vetor_produtos[10000];
encomenda vetor_encomendas[500];
void a();
void q();
void N();
int pesoEncomenda(int ide);
void A();
void r();
void R();
void C();
int quantidadeProdutoEnc(int idp, int ide);
void p();
void E();
void m();
int maiorPreco(int id1, int id2);
int particaoPreco(int vec[], int i, int j);
void ordenaPreco(int vetor_id[], int inicio, int fim);
void l();
int maiorAlfab(dados_encomenda d1, dados_encomenda d2);
int particaoAlfab(dados_encomenda vec[], int inicio, int fim);
void ordenaAlfab(dados_encomenda vetor_dados[], int inicio, int fim);
void L();
int main()
{
  int continua_ciclo = 1;
  char comando;
  memset(vetor_produtos, -1, sizeof(vetor_produtos));
  memset(vetor_encomendas, -1, sizeof(vetor_encomendas));
  while (continua_ciclo)
  {
    comando = getchar();
    switch (comando)
    {
      case 'a':
        getchar();
        a();
        break;

      case 'q':
        getchar();
        q();
        break;

      case 'N':
        getchar();
        N();
        break;

      case 'A':
        getchar();
        A();
        break;

      case 'r':
        getchar();
        r();
        break;

      case 'R':
        getchar();
        R();
        break;

      case 'C':
        getchar();
        C();
        break;

      case 'p':
        getchar();
        p();
        break;

      case 'E':
        getchar();
        E();
        break;

      case 'm':
        getchar();
        m();
        break;

      case 'l':
        getchar();
        l();
        break;

      case 'L':
        getchar();
        L();
        break;

      case 'x':
        continua_ciclo = 0;
        break;

    }

  }

  return 0;
}

void a()
{
  static int i = 0;
  vetor_produtos[i].id = i;
  for (int vetor_produtos_index = 0; vetor_produtos_index < 10; vetor_produtos_index++)
  {
    vetor_produtos[i].desc[vetor_produtos_index] = new_sym_var(sizeof(char) * 8);
  }

  vetor_produtos[i].desc[10 - 1] = '\0';
  vetor_produtos[i].preco = new_sym_var(sizeof(int) * 8);
  vetor_produtos[i].peso = new_sym_var(sizeof(int) * 8);
  vetor_produtos[i].qtd = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", vetor_produtos[i++].id);
}

void q()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (vetor_produtos[idp].id != (-1))
  {
    {
      vetor_produtos[idp].qtd += qtd;
    }
  }
  else
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
  }

}

void N()
{
  static int i = 0;
  vetor_encomendas[i].id = i;
  printf("Nova encomenda %d.\n", vetor_encomendas[i++].id);
}

int pesoEncomenda(int ide)
{
  int i;
  int peso_enc = 0;
  for (i = 0; (i < 200) && (vetor_encomendas[ide].item[i].id != (-1)); i++)
  {
    peso_enc += vetor_produtos[vetor_encomendas[ide].item[i].id].peso * vetor_encomendas[ide].item[i].qtd;
  }

  return peso_enc;
}

void A()
{
  int ide;
  int idp;
  int qtd_prod;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd_prod = new_sym_var(sizeof(int) * 8);
  if (vetor_encomendas[ide].id == (-1))
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    if (vetor_produtos[idp].id == (-1))
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
    }
    else
    {
      if (vetor_produtos[idp].qtd < qtd_prod)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        }
      }
      else
      {
        {
          if ((pesoEncomenda(ide) + (vetor_produtos[idp].peso * qtd_prod)) > 200)
          {
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }
          }
          else
          {
            {
              vetor_produtos[idp].qtd -= qtd_prod;
              for (i = 0; i < 200; i++)
              {
                if (vetor_encomendas[ide].item[i].id == idp)
                {
                  {
                    vetor_encomendas[ide].item[i].qtd += qtd_prod;
                    break;
                  }
                }
                else
                {
                  
                }

                if (vetor_encomendas[ide].item[i].id == (-1))
                {
                  {
                    vetor_encomendas[ide].item[i].id = idp;
                    vetor_encomendas[ide].item[i].qtd = qtd_prod;
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

    }

  }

}

void r()
{
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (vetor_produtos[id].id != (-1))
  {
    {
      if ((vetor_produtos[id].qtd - qtd) < 0)
      {
        {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
        }
      }
      else
      {
        {
          vetor_produtos[id].qtd -= qtd;
        }
      }

    }
  }
  else
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
    }
  }

}

void R()
{
  int ide;
  int idp;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (vetor_encomendas[ide].id == (-1))
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    if (vetor_produtos[idp].id == (-1))
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
    }
    else
    {
      {
        for (i = 0; i < 200; i++)
        {
          if (vetor_encomendas[ide].item[i].id == idp)
          {
            {
              vetor_produtos[idp].qtd += vetor_encomendas[ide].item[i].qtd;
              while (i < (200 - 1))
              {
                vetor_encomendas[ide].item[i] = vetor_encomendas[ide].item[i + 1];
                i++;
              }

              vetor_encomendas[ide].item[i].id = -1;
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

void C()
{
  int ide;
  int i;
  int custo = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (vetor_encomendas[ide].id == (-1))
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      for (i = 0; (i < 200) && (vetor_encomendas[ide].item[i].id != (-1)); i++)
      {
        custo += vetor_produtos[vetor_encomendas[ide].item[i].id].preco * vetor_encomendas[ide].item[i].qtd;
      }

      printf("Custo da encomenda %d %d.\n", ide, custo);
    }
  }

}

void p()
{
  int idp;
  int novo_preco;
  idp = new_sym_var(sizeof(int) * 8);
  novo_preco = new_sym_var(sizeof(int) * 8);
  if (vetor_produtos[idp].id == (-1))
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      vetor_produtos[idp].preco = novo_preco;
    }
  }

}

int quantidadeProdutoEnc(int idp, int ide)
{
  int i;
  for (i = 0; (i < 200) && (vetor_encomendas[ide].item[i].id != (-1)); i++)
  {
    if (vetor_encomendas[ide].item[i].id == idp)
    {
      {
        return vetor_encomendas[ide].item[i].qtd;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

void E()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (vetor_encomendas[ide].id == (-1))
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    if (vetor_produtos[idp].id == (-1))
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      }
    }
    else
    {
      {
        printf("%s %d.\n", vetor_produtos[idp].desc, quantidadeProdutoEnc(idp, ide));
      }
    }

  }

}

void m()
{
  int idp;
  int i;
  int qtd_enc;
  int max_ide = -1;
  int max_qtd = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (vetor_produtos[idp].id == (-1))
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      for (i = 0; (i < 500) && (vetor_encomendas[i].id != (-1)); i++)
      {
        qtd_enc = quantidadeProdutoEnc(idp, i);
        if (qtd_enc > max_qtd)
        {
          {
            max_qtd = qtd_enc;
            max_ide = i;
          }
        }
        else
        {
          
        }

      }

      if (max_ide != (-1))
      {
        {
          printf("Maximo produto %d %d %d.\n", idp, max_ide, max_qtd);
        }
      }
      else
      {
        
      }

    }
  }

}

int maiorPreco(int id1, int id2)
{
  if (vetor_produtos[id1].preco > vetor_produtos[id2].preco)
  {
    {
      return 1;
    }
  }
  else
  {
    if (vetor_produtos[id1].preco < vetor_produtos[id2].preco)
    {
      {
        return 0;
      }
    }
    else
    {
      {
        return vetor_produtos[id1].id > vetor_produtos[id2].id;
      }
    }

  }

}

int particaoPreco(int vec[], int inicio, int fim)
{
  int i = inicio;
  int j = fim;
  int p;
  p = vec[j];
  while (i < j)
  {
    while (maiorPreco(p, vec[i]))
    {
      i++;
    }

    while (!maiorPreco(p, vec[--j]))
    {
      if (j == inicio)
      {
        {
          break;
        }
      }
      else
      {
        
      }

    }

    if (i < j)
    {
      {
        {
          int p = vec[j];
          vec[j] = vec[i];
          vec[i] = p;
        }
        ;
      }
    }
    else
    {
      
    }

  }

  {
    int p = vec[fim];
    vec[fim] = vec[i];
    vec[i] = p;
  }
  ;
  return i;
}

void ordenaPreco(int vetor_id[], int inicio, int fim)
{
  int i;
  if (inicio < fim)
  {
    {
      i = particaoPreco(vetor_id, inicio, fim);
      ordenaPreco(vetor_id, inicio, i - 1);
      ordenaPreco(vetor_id, i + 1, fim);
    }
  }
  else
  {
    
  }

}

void l()
{
  int j;
  int i;
  int vetor_id[10000];
  for (j = 0; (j < 10000) && (vetor_produtos[j].id != (-1)); j++)
  {
    vetor_id[j] = vetor_produtos[j].id;
  }

  ordenaPreco(vetor_id, 0, j - 1);
  printf("Produtos\n");
  for (i = 0; i < j; i++)
  {
    printf("* %s %d %d\n", vetor_produtos[vetor_id[i]].desc, vetor_produtos[vetor_id[i]].preco, vetor_produtos[vetor_id[i]].qtd);
  }

}

int maiorAlfab(dados_encomenda d1, dados_encomenda d2)
{
  return strcmp(vetor_produtos[d1.id].desc, vetor_produtos[d2.id].desc) > 0;
}

int particaoAlfab(dados_encomenda vec[], int inicio, int fim)
{
  int i = inicio;
  int j = fim;
  dados_encomenda p;
  p = vec[j];
  while (i < j)
  {
    while (maiorAlfab(p, vec[i]))
    {
      i++;
    }

    while (!maiorAlfab(p, vec[--j]))
    {
      if (j == inicio)
      {
        {
          break;
        }
      }
      else
      {
        
      }

    }

    if (i < j)
    {
      {
        {
          dados_encomenda p = vec[j];
          vec[j] = vec[i];
          vec[i] = p;
        }
        ;
      }
    }
    else
    {
      
    }

  }

  {
    dados_encomenda p = vec[fim];
    vec[fim] = vec[i];
    vec[i] = p;
  }
  ;
  return i;
}

void ordenaAlfab(dados_encomenda vetor_dados[], int inicio, int fim)
{
  int i;
  if (inicio < fim)
  {
    {
      i = particaoAlfab(vetor_dados, inicio, fim);
      ordenaAlfab(vetor_dados, 0, i - 1);
      ordenaAlfab(vetor_dados, i + 1, fim);
    }
  }
  else
  {
    
  }

}

void L()
{
  int i;
  int j;
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  if (vetor_encomendas[ide].id != (-1))
  {
    {
      for (j = 0; (j < 200) && (vetor_encomendas[ide].item[j].id != (-1)); j++)
        ;

      ordenaAlfab(vetor_encomendas[ide].item, 0, j - 1);
      printf("Encomenda %d\n", ide);
      for (i = 0; (i < 200) && (vetor_encomendas[ide].item[i].id != (-1)); i++)
      {
        idp = vetor_encomendas[ide].item[i].id;
        printf("* %s %d %d\n", vetor_produtos[idp].desc, vetor_produtos[idp].preco, vetor_encomendas[ide].item[i].qtd);
      }

    }
  }
  else
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }

}

