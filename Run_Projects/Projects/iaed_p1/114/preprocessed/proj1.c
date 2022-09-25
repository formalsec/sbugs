/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  char desc[64];
  int idp;
  int preco;
  int peso;
  int stock;
} produto;
typedef struct 
{
  int idp[200];
  int qtd[200];
  int peso;
  int preco;
  int num_prods;
} encomenda;
void novo_prod();
void mais_stock();
void nova_enc();
void novo_prod_enc();
void menos_stock();
void remover_prod_enc();
void custo_enc();
void alt_preco();
void quant_prod_enc();
void enc_maior_qtd_prod();
void listar_prods();
void listar_prods_enc();
void inicializar_vetor(int [], int, int);
void remover_elemento(int, int [], int, int);
void mergesort(produto [], int, int, int);
void merge_preco(produto [], int, int, int);
void merge_desc(produto [], int, int, int);
produto reg_prods[10000];
encomenda reg_encs[500];
produto aux[10000];
static int idp;
static int ide;
int main()
{
  char c;
  while ((c = getchar()) != 'x')
    switch (c)
  {
    case 'a':
      novo_prod();
      break;

    case 'q':
      mais_stock();
      break;

    case 'N':
      nova_enc();
      break;

    case 'A':
      novo_prod_enc();
      break;

    case 'r':
      menos_stock();
      break;

    case 'R':
      remover_prod_enc();
      break;

    case 'C':
      custo_enc();
      break;

    case 'p':
      alt_preco();
      break;

    case 'E':
      quant_prod_enc();
      break;

    case 'm':
      enc_maior_qtd_prod();
      break;

    case 'l':
      listar_prods();
      break;

    case 'L':
      listar_prods_enc();

  }


  return 0;
}

void novo_prod()
{
  produto prod;
  for (int prod_index = 0; prod_index < 10; prod_index++)
  {
    prod.desc[prod_index] = new_sym_var(sizeof(char) * 8);
  }

  prod.desc[10 - 1] = '\0';
  prod.preco = new_sym_var(sizeof(int) * 8);
  prod.peso = new_sym_var(sizeof(int) * 8);
  prod.stock = new_sym_var(sizeof(int) * 8);
  prod.idp = idp;
  reg_prods[idp] = prod;
  printf("Novo produto %d.\n", idp);
  idp++;
}

void mais_stock()
{
  int prod;
  int qtd;
  prod = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (prod >= idp)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prod);
  }
  else
  {
    reg_prods[prod].stock += qtd;
  }

}

void nova_enc()
{
  encomenda enc = {{0}, {0}, 0, 0, 0};
  inicializar_vetor(enc.idp, 200, -1);
  reg_encs[ide] = enc;
  printf("Nova encomenda %d.\n", ide);
  ide++;
}

void novo_prod_enc()
{
  int i;
  int id;
  int enc;
  int prod;
  int qtd;
  int existe = 0;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (enc >= ide)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
  }
  else
  {
    if (prod >= idp)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
    }
    else
    {
      if ((reg_prods[prod].stock - qtd) < 0)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod, enc);
      }
      else
      {
        if (((reg_prods[prod].peso * qtd) + reg_encs[enc].peso) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod, enc);
        }
        else
        {
          for (i = 0; i < reg_encs[enc].num_prods; i++)
            if (reg_encs[enc].idp[i] == prod)
          {
            existe = 1;
            id = i;
            break;
          }
          else
          {
            
          }


          if (existe)
          {
            reg_encs[enc].qtd[id] += qtd;
          }
          else
          {
            id = reg_encs[enc].num_prods;
            reg_encs[enc].idp[id] = prod;
            reg_encs[enc].qtd[id] = qtd;
            reg_encs[enc].num_prods++;
          }

          reg_encs[enc].peso += reg_prods[prod].peso * qtd;
          reg_encs[enc].preco += reg_prods[prod].preco * qtd;
          reg_prods[prod].stock -= qtd;
        }

      }

    }

  }

}

void menos_stock()
{
  int prod;
  int qtd;
  prod = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (prod >= idp)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod);
  }
  else
  {
    if ((reg_prods[prod].stock - qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, prod);
    }
    else
    {
      reg_prods[prod].stock -= qtd;
    }

  }

}

void remover_prod_enc()
{
  int enc;
  int prod;
  int id = -1;
  int i;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  if (enc >= ide)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
  }
  else
  {
    if (prod >= idp)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
    }
    else
    {
      for (i = 0; i < reg_encs[enc].num_prods; i++)
        if (reg_encs[enc].idp[i] == prod)
      {
        id = i;
        break;
      }
      else
      {
        
      }


      if (id >= 0)
      {
        reg_encs[enc].peso -= reg_prods[prod].peso * reg_encs[enc].qtd[id];
        reg_encs[enc].preco -= reg_prods[prod].preco * reg_encs[enc].qtd[id];
        reg_prods[prod].stock += reg_encs[enc].qtd[id];
        remover_elemento(id, reg_encs[enc].idp, -1, 200);
        remover_elemento(id, reg_encs[enc].qtd, 0, 200);
        reg_encs[enc].num_prods--;
      }
      else
      {
        
      }

    }

  }

}

void custo_enc()
{
  int enc;
  enc = new_sym_var(sizeof(int) * 8);
  if (enc >= ide)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", enc, reg_encs[enc].preco);
  }

}

void alt_preco()
{
  int prod;
  int preco;
  int id;
  int i;
  int j;
  int existe = 0;
  prod = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (prod >= idp)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prod);
  }
  else
  {
    for (i = 0; i < ide; i++)
    {
      for (j = 0; j < reg_encs[i].num_prods; j++)
      {
        if (reg_encs[i].idp[j] == prod)
        {
          existe = 1;
          id = j;
          break;
        }
        else
        {
          
        }

      }

      if (existe)
      {
        reg_encs[i].preco += reg_encs[i].qtd[id] * (preco - reg_prods[prod].preco);
        existe = 0;
      }
      else
      {
        
      }

    }

    reg_prods[prod].preco = preco;
  }

}

void quant_prod_enc()
{
  int enc;
  int prod;
  int i;
  int id;
  int existe = 0;
  int qtd = 0;
  enc = new_sym_var(sizeof(int) * 8);
  prod = new_sym_var(sizeof(int) * 8);
  if (enc >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    if (prod >= idp)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", prod);
    }
    else
    {
      for (i = 0; i < reg_encs[enc].num_prods; i++)
        if (reg_encs[enc].idp[i] == prod)
      {
        id = i;
        existe = 1;
        break;
      }
      else
      {
        
      }


      if (existe)
      {
        qtd = reg_encs[enc].qtd[id];
      }
      else
      {
        
      }

      printf("%s %d.\n", reg_prods[prod].desc, qtd);
    }

  }

}

void enc_maior_qtd_prod()
{
  int prod;
  int qtd = 0;
  int enc = -1;
  int i;
  int j;
  int id;
  int existe = 0;
  prod = new_sym_var(sizeof(int) * 8);
  if (prod >= idp)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod);
  }
  else
  {
    if (ide > 0)
    {
      for (i = 0; i < ide; i++)
      {
        for (j = 0; j < reg_encs[i].num_prods; j++)
          if (reg_encs[i].idp[j] == prod)
        {
          existe = 1;
          id = j;
          break;
        }
        else
        {
          
        }


        if (existe && (qtd < reg_encs[i].qtd[id]))
        {
          qtd = reg_encs[i].qtd[id];
          enc = i;
        }
        else
        {
          
        }

        existe = 0;
      }

      if (qtd > 0)
      {
        printf("Maximo produto %d %d %d.\n", prod, enc, qtd);
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

void listar_prods()
{
  int i;
  produto prods[10000];
  for (i = 0; i < idp; i++)
    prods[i] = reg_prods[i];

  mergesort(prods, 0, idp - 1, 1);
  printf("Produtos\n");
  for (i = 0; i < idp; i++)
    printf("* %s %d %d\n", prods[i].desc, prods[i].preco, prods[i].stock);

}

void listar_prods_enc()
{
  int enc;
  int i;
  int j;
  int id;
  produto prods[200];
  enc = new_sym_var(sizeof(int) * 8);
  if (enc >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
  }
  else
  {
    for (i = 0; i < reg_encs[enc].num_prods; i++)
    {
      id = reg_encs[enc].idp[i];
      prods[i] = reg_prods[id];
    }

    mergesort(prods, 0, reg_encs[enc].num_prods - 1, 0);
    printf("Encomenda %d\n", enc);
    for (i = 0; i < reg_encs[enc].num_prods; i++)
    {
      for (j = 0; j < reg_encs[enc].num_prods; j++)
        if (prods[i].idp == reg_encs[enc].idp[j])
      {
        id = j;
        break;
      }
      else
      {
        
      }


      printf("* %s %d %d\n", prods[i].desc, prods[i].preco, reg_encs[enc].qtd[id]);
    }

  }

}

void inicializar_vetor(int v[], int dim, int valor)
{
  int i;
  for (i = 0; i < dim; i++)
    v[i] = valor;

}

void remover_elemento(int id, int v[], int valor, int dim)
{
  int i;
  for (i = id; i < (dim - 1); i++)
    v[i] = v[i + 1];

  v[dim - 1] = valor;
}

void mergesort(produto v[], int esq, int dir, int preco)
{
  int meio = (dir + esq) / 2;
  if (dir <= esq)
  {
    return;
  }
  else
  {
    
  }

  mergesort(v, esq, meio, preco);
  mergesort(v, meio + 1, dir, preco);
  if (preco)
  {
    merge_preco(v, esq, meio, dir);
  }
  else
  {
    merge_desc(v, esq, meio, dir);
  }

}

void merge_preco(produto v[], int esq, int meio, int dir)
{
  int i;
  int j;
  int k;
  for (i = meio + 1; i > esq; i--)
    aux[i - 1] = v[i - 1];

  for (j = meio; j < dir; j++)
    aux[(dir + meio) - j] = v[j + 1];

  for (k = esq; k <= dir; k++)
    if ((aux[j].preco < aux[i].preco) || (i > meio))
  {
    v[k] = aux[j--];
  }
  else
  {
    v[k] = aux[i++];
  }


}

void merge_desc(produto v[], int esq, int meio, int dir)
{
  int i;
  int j;
  int k;
  for (i = meio + 1; i > esq; i--)
    aux[i - 1] = v[i - 1];

  for (j = meio; j < dir; j++)
    aux[(dir + meio) - j] = v[j + 1];

  for (k = esq; k <= dir; k++)
    if (strcmp(aux[j].desc, aux[i].desc) < 0)
  {
    v[k] = aux[j--];
  }
  else
  {
    v[k] = aux[i++];
  }


}

