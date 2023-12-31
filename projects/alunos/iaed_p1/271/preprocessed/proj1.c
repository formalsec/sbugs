#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> /*PODE USAR-SE? ATOI DEPENDE DISTO*/


char argument[64];
char *get_arg()
{
  char input_char;
  int i = 0;
  while (true)
  {
    input_char = getchar();
    if (input_char == '\n')
    {
      argument[i] = '\0';
      return argument;
    }
    else
    {
      
    }

    if (input_char == ':')
    {
      argument[i] = '\0';
      return argument;
    }
    else
    {
      
    }

    argument[i] = input_char;
    i++;
  }

}

int id_prox_produto = 0;
int id_prox_encomenda = 0;
int aux[10000];
int idps_ordenados[10000];
struct produto
{
  char descricao[63 + 1];
  int peso;
  int preco;
  int qtd;
} produtos[10000];
int existe_produto(int id_produto)
{
  return id_produto < id_prox_produto;
}

struct produto_na_encomenda
{
  int qtd;
};
struct encomenda
{
  struct produto_na_encomenda produtos[10000];
  int pso;
} encomendas[500];
int existe_encomenda(int id_encomenda)
{
  return id_encomenda < id_prox_encomenda;
}

void handler_a()
{
  int preco;
  int peso;
  int qtd;
  strcpy(produtos[id_prox_produto].descricao, get_arg());
  preco = atoi(get_arg()), peso = atoi(get_arg()), qtd = atoi(get_arg());
  produtos[id_prox_produto].preco = preco;
  produtos[id_prox_produto].peso = peso;
  produtos[id_prox_produto].qtd = qtd;
  printf("Novo produto %d.\n", id_prox_produto);
  ++id_prox_produto;
}

void handler_q()
{
  int idp = atoi(get_arg());
  int qtd = atoi(get_arg());
  if (!existe_produto(idp))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  produtos[idp].qtd += qtd;
}

void handler_N()
{
  printf("Nova encomenda %d.\n", id_prox_encomenda);
  id_prox_encomenda++;
}

void handler_A()
{
  int ide = atoi(get_arg());
  int idp = atoi(get_arg());
  int qtd = atoi(get_arg());
  int peso_final = encomendas[ide].pso + (produtos[idp].peso * qtd);
  char msg_err[64];
  sprintf(msg_err, "Impossivel adicionar produto %d a encomenda %d.", idp, ide);
  if (!existe_encomenda(ide))
  {
    printf("%s Encomenda inexistente.\n", msg_err);
    return;
  }
  else
  {
    
  }

  if (!existe_produto(idp))
  {
    printf("%s Produto inexistente.\n", msg_err);
    return;
  }
  else
  {
    
  }

  if (qtd > produtos[idp].qtd)
  {
    printf("%s Quantidade em stock insuficiente.\n", msg_err);
    return;
  }
  else
  {
    
  }

  if (peso_final > 200)
  {
    printf("%s Peso da encomenda excede o maximo de %d.\n", msg_err, 200);
    return;
  }
  else
  {
    encomendas[ide].pso = peso_final;
  }

  encomendas[ide].produtos[idp].qtd += qtd;
  produtos[idp].qtd -= qtd;
}

void handler_r()
{
  int idp = atoi(get_arg());
  int qtd = atoi(get_arg());
  char msg_err[64];
  sprintf(msg_err, "Impossivel remover stock do produto %d. ", idp);
  if (!existe_produto(idp))
  {
    printf("%sProduto inexistente.\n", msg_err);
    return;
  }
  else
  {
    
  }

  if ((produtos[idp].qtd - qtd) < 0)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    return;
  }
  else
  {
    
  }

  produtos[idp].qtd -= qtd;
}

void handler_R()
{
  int ide = atoi(get_arg());
  int idp = atoi(get_arg());
  char msg_err[64];
  sprintf(msg_err, "Impossivel remover produto %d a encomenda %d. ", idp, ide);
  if (!existe_encomenda(ide))
  {
    printf("%sEncomenda inexistente.\n", msg_err);
    return;
  }
  else
  {
    
  }

  if (!existe_produto(idp))
  {
    printf("%sProduto inexistente.\n", msg_err);
    return;
  }
  else
  {
    
  }

  produtos[idp].qtd += encomendas[ide].produtos[idp].qtd;
  encomendas[ide].pso -= encomendas[ide].produtos[idp].qtd * produtos[idp].peso;
  encomendas[ide].produtos[idp].qtd = 0;
}

void handler_C()
{
  int ide = atoi(get_arg());
  int custo = 0;
  int i;
  if (!existe_encomenda(ide))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < 10000; i++)
    custo += produtos[i].preco * encomendas[ide].produtos[i].qtd;

  printf("Custo da encomenda %d %d.\n", ide, custo);
}

void handler_p()
{
  int idp = atoi(get_arg());
  int preco = atoi(get_arg());
  if (!existe_produto(idp))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  produtos[idp].preco = preco;
}

void handler_E()
{
  int ide = atoi(get_arg());
  int idp = atoi(get_arg());
  if (!existe_encomenda(ide))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  if (!existe_produto(idp))
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  printf("%s %d.\n", produtos[idp].descricao, encomendas[ide].produtos[idp].qtd);
}

void handler_m()
{
  int idp = atoi(get_arg());
  int i;
  int ide_res = -1;
  int qtd = 0;
  if (!existe_produto(idp))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < 500; i++)
  {
    if (i >= id_prox_encomenda)
    {
      break;
    }
    else
    {
      
    }

    if (encomendas[i].produtos[idp].qtd > qtd)
    {
      ide_res = i;
      qtd = encomendas[i].produtos[idp].qtd;
    }
    else
    {
      
    }

  }

  if (ide_res == (-1))
  {
    return;
  }
  else
  {
    
  }

  printf("Maximo produto %d %d %d.\n", idp, ide_res, qtd);
}

int less(int a, int b)
{
  if (produtos[a].preco == produtos[b].preco)
  {
    return a < b;
  }
  else
  {
    
  }

  return produtos[a].preco < produtos[b].preco;
}

void merge(int a[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
    if (less(aux[j], aux[i]))
  {
    a[k] = aux[j--];
  }
  else
  {
    a[k] = aux[i++];
  }


}

void mrge_srt(int p[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mrge_srt(p, l, m);
  mrge_srt(p, m + 1, r);
  merge(p, l, m, r);
}

void handler_l()
{
  int p;
  int idps[10000];
  printf("Produtos\n");
  if (id_prox_produto == 0)
  {
    return;
  }
  else
  {
    
  }

  for (p = 0; p < id_prox_produto; p++)
    idps[p] = p;

  mrge_srt(idps, 0, id_prox_produto - 1);
  for (p = 0; p < id_prox_produto; p++)
    printf("* %s %d %d\n", produtos[idps[p]].descricao, produtos[idps[p]].preco, produtos[idps[p]].qtd);

}

int ch_to_s_nr(char char_atual)
{
  char_atual = (int) char_atual;
  if (char_atual >= 97)
  {
    char_atual -= 32;
  }
  else
  {
    
  }

  return char_atual - 65;
}

int alfa_srt(int *ls_idps, int index_range[2], int c, int recursive)
{
  int ch_atual;
  int p;
  int n;
  int e;
  int index = 0;
  int iter_nr[26] = {0};
  int ch_slot[26] = {0};
  int scope_low[26] = {0};
  int indx_rge[2] = {0};
  for (p = index_range[0]; p <= index_range[1]; p++)
  {
    ch_atual = ch_to_s_nr(produtos[ls_idps[p]].descricao[c]);
    ch_slot[ch_atual]++;
  }

  for (e = 0; e < 26; e++)
  {
    for (n = 0; n < e; n++)
      index += ch_slot[n];

    scope_low[e] = index;
    index = 0;
  }

  for (p = index_range[0]; p <= index_range[1]; p++)
  {
    if (((signed int) strlen(produtos[ls_idps[p]].descricao)) <= (c + 1))
    {
      return -1;
    }
    else
    {
      
    }

    ch_atual = ch_to_s_nr(produtos[ls_idps[p]].descricao[c]);
    if (ch_atual < 0)
    {
      return -1;
    }
    else
    {
      
    }

  }

  for (p = index_range[0]; p <= index_range[1]; p++)
  {
    ch_atual = ch_to_s_nr(produtos[ls_idps[p]].descricao[c]);
    index = (scope_low[ch_atual] + iter_nr[ch_atual]) + index_range[0];
    idps_ordenados[index] = ls_idps[p];
    iter_nr[ch_atual]++;
  }

  if (recursive == 0)
  {
    return 0;
  }
  else
  {
    
  }

  indx_rge[0] = 0;
  for (e = 1; e < 26; e++)
  {
    if (scope_low[e] != 0)
    {
      indx_rge[0] += scope_low[e] + 1;
    }
    else
    {
      indx_rge[0] += scope_low[e];
    }

    indx_rge[1] = (ch_slot[e] + scope_low[e]) - 1;
    alfa_srt(idps_ordenados, indx_rge, 1, 0);
    indx_rge[0] = 0;
    indx_rge[1] = 0;
  }

  return 0;
}

void handler_L()
{
  int ide = atoi(get_arg());
  int i;
  int p;
  int nr_ids;
  int ls_idps[10000];
  int index_range[2] = {0};
  struct produto pdt;
  if (!existe_encomenda(ide))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  printf("Encomenda %d\n", ide);
  for (i = 0, nr_ids = -1; i < 10000; i++)
  {
    if (encomendas[ide].produtos[i].qtd > 0)
    {
      nr_ids++;
      ls_idps[nr_ids] = i;
    }
    else
    {
      
    }

  }

  index_range[1] = nr_ids;
  if (nr_ids == (-1))
  {
    return;
  }
  else
  {
    
  }

  if (index_range[1] == 0)
  {
    pdt = produtos[ls_idps[0]];
    printf("* %s %d %d\n", pdt.descricao, pdt.preco, encomendas[ide].produtos[ls_idps[0]].qtd);
    return;
  }
  else
  {
    
  }

  alfa_srt(ls_idps, index_range, 0, 1);
  for (p = 0; p <= nr_ids; p++)
  {
    pdt = produtos[idps_ordenados[p]];
    printf("* %s %d %d\n", pdt.descricao, pdt.preco, encomendas[ide].produtos[idps_ordenados[p]].qtd);
  }

}

int main()
{
  char command;
  while (true)
  {
    command = getchar();
    if (command == 'x')
    {
      break;
    }
    else
    {
      
    }

    getchar();
    switch (command)
    {
      case 'a':
        handler_a();
        break;

      case 'q':
        handler_q();
        break;

      case 'N':
        handler_N();
        break;

      case 'A':
        handler_A();
        break;

      case 'r':
        handler_r();
        break;

      case 'R':
        handler_R();
        break;

      case 'C':
        handler_C();
        break;

      case 'p':
        handler_p();
        break;

      case 'E':
        handler_E();
        break;

      case 'm':
        handler_m();
        break;

      case 'l':
        handler_l();
        break;

      case 'L':
        handler_L();
        break;

    }

  }

  return 0;
}

