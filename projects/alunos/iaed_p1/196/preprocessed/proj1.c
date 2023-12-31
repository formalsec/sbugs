#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct produto
{
  int id;
  int preco;
  int peso;
  int stock;
  char desc[64];
} prd;
typedef struct encomenda
{
  int peso;
  int interior[10000];
} enc;
int idp_gb = 0;
int ide_gb = 0;
int igb;
prd memoriaPRD[10000];
enc memoriaENC[500];
void novo_prd(char info[]);
void adiciona_stock(char info[]);
void nova_enc(void);
void adiciona_prd(char info[]);
void retira_stock(char info[]);
void retira_prd(char info[]);
void custo_enc(char info[]);
void muda_preco(char info[]);
void prd_em_enc(char info[]);
void max_prd(char info[]);
void l_prd_preco(void);
void l_prds_enc(char info[]);
int inteiro(char info[]);
void ini_interior(int interior[]);
void ordena_precos(prd prds[], int n, int max);
void ordena_descs(int esq, int dir, prd prds[]);
void merge_desc(int esq, int med, int dir, prd prds[]);
int main()
{
  char com;
  char info[100];
  while (1)
  {
    switch (com = getchar())
    {
      case 'a':
      {
        for (int info_index = 0; info_index < 10; info_index++)
        {
          info[info_index] = new_sym_var(sizeof(char) * 8);
        }

        info[10 - 1] = '\0';
        novo_prd(info);
        break;
      }

      case 'q':
      {
        for (int info_index = 0; info_index < 10; info_index++)
        {
          info[info_index] = new_sym_var(sizeof(char) * 8);
        }

        info[10 - 1] = '\0';
        adiciona_stock(info);
        break;
      }

      case 'N':
      {
        nova_enc();
        break;
      }

      case 'A':
      {
        for (int info_index = 0; info_index < 10; info_index++)
        {
          info[info_index] = new_sym_var(sizeof(char) * 8);
        }

        info[10 - 1] = '\0';
        adiciona_prd(info);
        break;
      }

      case 'r':
      {
        for (int info_index = 0; info_index < 10; info_index++)
        {
          info[info_index] = new_sym_var(sizeof(char) * 8);
        }

        info[10 - 1] = '\0';
        retira_stock(info);
        break;
      }

      case 'R':
      {
        for (int info_index = 0; info_index < 10; info_index++)
        {
          info[info_index] = new_sym_var(sizeof(char) * 8);
        }

        info[10 - 1] = '\0';
        retira_prd(info);
        break;
      }

      case 'C':
      {
        for (int info_index = 0; info_index < 10; info_index++)
        {
          info[info_index] = new_sym_var(sizeof(char) * 8);
        }

        info[10 - 1] = '\0';
        custo_enc(info);
        break;
      }

      case 'p':
      {
        for (int info_index = 0; info_index < 10; info_index++)
        {
          info[info_index] = new_sym_var(sizeof(char) * 8);
        }

        info[10 - 1] = '\0';
        muda_preco(info);
        break;
      }

      case 'E':
      {
        for (int info_index = 0; info_index < 10; info_index++)
        {
          info[info_index] = new_sym_var(sizeof(char) * 8);
        }

        info[10 - 1] = '\0';
        prd_em_enc(info);
        break;
      }

      case 'm':
      {
        for (int info_index = 0; info_index < 10; info_index++)
        {
          info[info_index] = new_sym_var(sizeof(char) * 8);
        }

        info[10 - 1] = '\0';
        max_prd(info);
        break;
      }

      case 'l':
      {
        l_prd_preco();
        break;
      }

      case 'L':
      {
        for (int info_index = 0; info_index < 10; info_index++)
        {
          info[info_index] = new_sym_var(sizeof(char) * 8);
        }

        info[10 - 1] = '\0';
        l_prds_enc(info);
        break;
      }

      case 'x':
        return 0;

    }

    getchar();
    igb = 0;
  }

  return 1;
}

void novo_prd(char info[])
{
  prd novo;
  for (igb = 0; (info[igb] != ':') && (igb < 100); igb++)
    novo.desc[igb] = info[igb];

  novo.desc[igb] = '\0';
  novo.preco = inteiro(info);
  novo.peso = inteiro(info);
  novo.stock = inteiro(info);
  novo.id = idp_gb;
  printf("Novo produto %d.\n", novo.id);
  memoriaPRD[idp_gb++] = novo;
}

void adiciona_stock(char info[])
{
  int idp = inteiro(info);
  int qtd = inteiro(info);
  if (idp >= idp_gb)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    memoriaPRD[idp].stock += qtd;
  }

}

void nova_enc(void)
{
  enc nova;
  ini_interior(nova.interior);
  nova.peso = 0;
  printf("Nova encomenda %d.\n", ide_gb);
  memoriaENC[ide_gb++] = nova;
}

void adiciona_prd(char info[])
{
  int ide = inteiro(info);
  int idp = inteiro(info);
  int qtd = inteiro(info);
  if (ide >= ide_gb)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= idp_gb)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (memoriaPRD[idp].stock < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((memoriaENC[ide].peso + (memoriaPRD[idp].peso * qtd)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          memoriaENC[ide].peso += memoriaPRD[idp].peso * qtd;
          memoriaPRD[idp].stock -= qtd;
          if (memoriaENC[ide].interior[idp] == (-1))
          {
            memoriaENC[ide].interior[idp] = qtd;
          }
          else
          {
            memoriaENC[ide].interior[idp] += qtd;
          }

        }

      }

    }

  }

}

void retira_stock(char info[])
{
  int idp = inteiro(info);
  int qtd = inteiro(info);
  if (idp >= idp_gb)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (qtd > memoriaPRD[idp].stock)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      memoriaPRD[idp].stock -= qtd;
    }

  }

}

void retira_prd(char info[])
{
  int ide = inteiro(info);
  int idp = inteiro(info);
  if (ide >= ide_gb)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= idp_gb)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (memoriaENC[ide].interior[idp] != (-1))
      {
        memoriaPRD[idp].stock += memoriaENC[ide].interior[idp];
        memoriaENC[ide].peso -= memoriaENC[ide].interior[idp] * memoriaPRD[idp].peso;
        memoriaENC[ide].interior[idp] = -1;
      }
      else
      {
        
      }

    }

  }

}

void custo_enc(char info[])
{
  int total = 0;
  int idp;
  int ide = inteiro(info);
  if (ide >= ide_gb)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (idp = 0; idp < idp_gb; idp++)
    {
      if (memoriaENC[ide].interior[idp] != (-1))
      {
        total += memoriaPRD[idp].preco * memoriaENC[ide].interior[idp];
      }
      else
      {
        
      }

    }

    printf("Custo da encomenda %d %d.\n", ide, total);
  }

}

void muda_preco(char info[])
{
  int idp = inteiro(info);
  int pnovo = inteiro(info);
  if (idp >= idp_gb)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    memoriaPRD[idp].preco = pnovo;
  }

}

void prd_em_enc(char info[])
{
  int ide = inteiro(info);
  int idp = inteiro(info);
  if (ide >= ide_gb)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp >= idp_gb)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      if (memoriaENC[ide].interior[idp] != (-1))
      {
        printf("%s %d.\n", memoriaPRD[idp].desc, memoriaENC[ide].interior[idp]);
      }
      else
      {
        printf("%s 0.\n", memoriaPRD[idp].desc);
      }

    }

  }

}

void max_prd(char info[])
{
  int ide;
  int max_ide = -1;
  int max_stock = 0;
  int idp = inteiro(info);
  if (idp >= idp_gb)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  for (ide = 0; ide < ide_gb; ide++)
  {
    if (memoriaENC[ide].interior[idp] > max_stock)
    {
      max_stock = memoriaENC[ide].interior[idp];
      max_ide = ide;
    }
    else
    {
      
    }

  }

  if (max_ide != (-1))
  {
    printf("Maximo produto %d %d %d.\n", idp, max_ide, max_stock);
  }
  else
  {
    
  }

}

void l_prd_preco(void)
{
  prd produto;
  int idp;
  int preco_max = 0;
  int total = idp_gb;
  prd *copia_produtos = (prd *) malloc(total * (sizeof(prd)));
  for (idp = 0; idp < idp_gb; idp++)
  {
    copia_produtos[idp] = memoriaPRD[idp];
    if (memoriaPRD[idp].preco > preco_max)
    {
      preco_max = memoriaPRD[idp].preco;
    }
    else
    {
      
    }

  }

  ordena_precos(copia_produtos, total, preco_max);
  printf("Produtos\n");
  for (idp = 0; idp < total; idp++)
  {
    produto = copia_produtos[idp];
    printf("* %s %d %d\n", produto.desc, produto.preco, produto.stock);
  }

  free(copia_produtos);
}

void l_prds_enc(char info[])
{
  int ide;
  int idp;
  int idp_max;
  prd produto;
  prd copia_produtos[200];
  int total_prd = 0;
  int j = 0;
  ide = inteiro(info);
  if (ide >= ide_gb)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (idp = 0; idp < idp_gb; idp++)
    {
      if (memoriaENC[ide].interior[idp] != (-1))
      {
        copia_produtos[j++] = memoriaPRD[idp];
        total_prd++;
      }
      else
      {
        
      }

    }

    idp_max = total_prd - 1;
    ordena_descs(0, idp_max, copia_produtos);
    printf("Encomenda %d\n", ide);
    for (idp = 0; idp <= idp_max; idp++)
    {
      produto = copia_produtos[idp];
      printf("* %s %d %d\n", produto.desc, produto.preco, memoriaENC[ide].interior[produto.id]);
    }

  }

}

int inteiro(char info[])
{
  int res = 0;
  if (info[igb] == ':')
  {
    igb++;
  }
  else
  {
    
  }

  for (; (info[igb] != ':') && (info[igb] != '\0'); igb++)
  {
    res *= 10;
    res += info[igb] - '0';
  }

  return res;
}

void ini_interior(int interior[])
{
  int idp;
  for (idp = 0; idp <= 10000; idp++)
    interior[idp] = -1;

}

void ordena_precos(prd prds[], int n, int max)
{
  int i;
  prd *ordenado = malloc(n * (sizeof(prd)));
  int *conta = calloc(max + 1, sizeof(int));
  for (i = 0; i < n; i++)
  {
    conta[prds[i].preco]++;
  }

  for (i = 1; i <= max; i++)
  {
    conta[i] += conta[i - 1];
  }

  for (i = n - 1; i >= 0; i--)
  {
    ordenado[conta[prds[i].preco] - 1] = prds[i];
    conta[prds[i].preco]--;
  }

  for (i = n - 1; i >= 0; i--)
  {
    prds[i] = ordenado[i];
  }

  free(conta);
  free(ordenado);
}

void ordena_descs(int esq, int dir, prd prds[])
{
  int med = (esq + dir) / 2;
  if (dir <= esq)
  {
    return;
  }
  else
  {
    
  }

  ordena_descs(esq, med, prds);
  ordena_descs(med + 1, dir, prds);
  merge_desc(esq, med, dir, prds);
}

void merge_desc(int esq, int med, int dir, prd prds[])
{
  prd prds_aux[200];
  int i;
  int j;
  int k;
  for (i = med + 1; i > esq; i--)
    prds_aux[i - 1] = prds[i - 1];

  for (j = med; j < dir; j++)
    prds_aux[(dir + med) - j] = prds[j + 1];

  for (k = esq; k <= dir; k++)
  {
    if ((strcmp(prds_aux[j].desc, prds_aux[i].desc) < 0) || (i > med))
    {
      prds[k] = prds_aux[j--];
    }
    else
    {
      prds[k] = prds_aux[i++];
    }

  }

}

