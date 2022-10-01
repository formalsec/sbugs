/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


int contador_idp_produto = 0;
int contador_ide_encomenda = 0;
typedef struct produto
{
  int identificador;
  int preco;
  int peso;
  int quantidade;
  char string[64];
} Produto;
Produto total_produtos[10000];
typedef struct encomenda
{
  Produto n_produtos[200];
  int identificador_en;
  int peso_total;
  int numero_prd;
} Encomenda;
Encomenda total_encomendas[500];
void adiciona_prd()
{
  Produto novo;
  for (int novo_index = 0; novo_index < 10; novo_index++)
  {
    novo.string[novo_index] = new_sym_var(sizeof(char) * 8);
  }

  novo.string[10 - 1] = '\0';
  novo.preco = new_sym_var(sizeof(int) * 8);
  novo.peso = new_sym_var(sizeof(int) * 8);
  novo.quantidade = new_sym_var(sizeof(int) * 8);
  novo.identificador = contador_idp_produto;
  total_produtos[contador_idp_produto] = novo;
  printf("Novo produto %d.\n", contador_idp_produto);
  contador_idp_produto++;
}

void adiciona_stck()
{
  int idp;
  int stock_novo;
  idp = new_sym_var(sizeof(int) * 8);
  stock_novo = new_sym_var(sizeof(int) * 8);
  if (idp > (contador_idp_produto - 1))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    total_produtos[idp].quantidade += stock_novo;
  }

}

void nova_encomeda()
{
  Encomenda nova;
  nova.identificador_en = contador_ide_encomenda;
  nova.peso_total = 0;
  nova.numero_prd = 0;
  total_encomendas[contador_ide_encomenda] = nova;
  contador_ide_encomenda++;
  printf("Nova encomenda %d.\n", nova.identificador_en);
}

void adiciona_prd_encomenda()
{
  int idp;
  int ide;
  int quantidade;
  int i;
  int peso_produto;
  int flag = 0;
  int numero_prd;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  peso_produto = total_produtos[idp].peso * quantidade;
  if (ide > (contador_ide_encomenda - 1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp > (contador_idp_produto - 1))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (quantidade > total_produtos[idp].quantidade)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((total_encomendas[ide].peso_total + peso_produto) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          numero_prd = total_encomendas[ide].numero_prd;
          for (i = 0; i < numero_prd; i++)
          {
            if (idp == total_encomendas[ide].n_produtos[i].identificador)
            {
              total_encomendas[ide].n_produtos[i].quantidade += quantidade;
              total_encomendas[ide].peso_total += peso_produto;
              total_produtos[idp].quantidade -= quantidade;
              flag = 1;
              break;
            }
            else
            {
              
            }

          }

          if (flag == 0)
          {
            total_encomendas[ide].n_produtos[total_encomendas[ide].numero_prd] = total_produtos[idp];
            total_encomendas[ide].peso_total += peso_produto;
            total_produtos[idp].quantidade -= quantidade;
            total_encomendas[ide].n_produtos[total_encomendas[ide].numero_prd].quantidade = quantidade;
            total_encomendas[ide].numero_prd++;
          }
          else
          {
            
          }

        }

      }

    }

  }

}

void remove_stk()
{
  int idp;
  int quantidade;
  idp = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if (idp > (contador_idp_produto - 1))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if ((total_produtos[idp].quantidade - quantidade) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
    }
    else
    {
      total_produtos[idp].quantidade -= quantidade;
    }

  }

}

void remove_prd_encomenda()
{
  int ide;
  int idp;
  int i;
  int j;
  int numero_produtos_en;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  numero_produtos_en = total_encomendas[ide].numero_prd;
  if (ide > (contador_ide_encomenda - 1))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp > (contador_idp_produto - 1))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      for (i = 0; i < numero_produtos_en; i++)
      {
        if (total_encomendas[ide].n_produtos[i].identificador == idp)
        {
          total_encomendas[ide].numero_prd--;
          total_encomendas[ide].peso_total -= total_encomendas[ide].n_produtos[i].peso * total_encomendas[ide].n_produtos[i].quantidade;
          total_produtos[idp].quantidade += total_encomendas[ide].n_produtos[i].quantidade;
          for (j = i; j < numero_produtos_en; j++)
            total_encomendas[ide].n_produtos[j] = total_encomendas[ide].n_produtos[j + 1];

          total_encomendas[ide].n_produtos[j].identificador = 0;
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void custo_encomenda()
{
  int ide;
  int total = 0;
  int numero_prd_encomenda;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  numero_prd_encomenda = total_encomendas[ide].numero_prd;
  if (ide > (contador_ide_encomenda - 1))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i < numero_prd_encomenda; i++)
      total += total_encomendas[ide].n_produtos[i].preco * total_encomendas[ide].n_produtos[i].quantidade;

    printf("Custo da encomenda %d %d.\n", ide, total);
  }

}

void altera_preco()
{
  int idp;
  int preco_novo;
  int i;
  int j;
  idp = new_sym_var(sizeof(int) * 8);
  preco_novo = new_sym_var(sizeof(int) * 8);
  if (idp > (contador_idp_produto - 1))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    total_produtos[idp].preco = preco_novo;
    for (i = 0; i < contador_ide_encomenda; i++)
    {
      for (j = 0; j < total_encomendas[i].numero_prd; j++)
      {
        if (total_encomendas[i].n_produtos[j].identificador == idp)
        {
          total_encomendas[i].n_produtos[j].preco = preco_novo;
        }
        else
        {
          
        }

      }

    }

  }

}

void dercricao_prd_en()
{
  int ide;
  int idp;
  int flag = -1;
  int numero_prd;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide > (contador_ide_encomenda - 1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp > (contador_idp_produto - 1))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      numero_prd = total_encomendas[ide].numero_prd;
      for (i = 0; i < numero_prd; i++)
      {
        if (idp == total_encomendas[ide].n_produtos[i].identificador)
        {
          flag = i;
          break;
        }
        else
        {
          
        }

      }

      if (flag == (-1))
      {
        printf("%s 0.\n", total_produtos[idp].string);
      }
      else
      {
        printf("%s %d.\n", total_produtos[idp].string, total_encomendas[ide].n_produtos[flag].quantidade);
      }

    }

  }

}

void listar_prd()
{
  int idp;
  int quantidade = 0;
  int i;
  int posicao;
  int flag = 0;
  int j;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp > (contador_idp_produto - 1))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < contador_ide_encomenda; i++)
    {
      for (j = 0; j < total_encomendas[i].numero_prd; j++)
      {
        if (total_encomendas[i].n_produtos[j].identificador == idp)
        {
          if (total_encomendas[i].n_produtos[j].quantidade > quantidade)
          {
            quantidade = total_encomendas[i].n_produtos[j].quantidade;
            posicao = i;
            flag = 1;
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

  }

  if (flag == 1)
  {
    printf("Maximo produto %d %d %d.\n", idp, total_encomendas[posicao].identificador_en, quantidade);
  }
  else
  {
    
  }

}

void ordena(Produto vetor[], int esquerda, int meio, int direita)
{
  int i;
  int j;
  int k;
  int indice_esquerda;
  int indice_direita;
  Produto Esquerda[10000];
  Produto Direita[10000];
  indice_esquerda = (meio - esquerda) + 1;
  indice_direita = direita - meio;
  for (i = 0; i < indice_esquerda; i++)
    Esquerda[i] = vetor[esquerda + i];

  for (j = 0; j < indice_direita; j++)
    Direita[j] = vetor[(meio + 1) + j];

  i = 0;
  j = 0;
  k = esquerda;
  while ((i < indice_esquerda) && (j < indice_direita))
  {
    if (Esquerda[i].preco <= Direita[j].preco)
    {
      vetor[k] = Esquerda[i];
      i++;
    }
    else
    {
      vetor[k] = Direita[j];
      j++;
    }

    k++;
  }

  while (i < indice_esquerda)
  {
    vetor[k] = Esquerda[i];
    i++;
    k++;
  }

  while (j < indice_direita)
  {
    vetor[k] = Direita[j];
    j++;
    k++;
  }

}

void ordena_partes(Produto vetor[], int esquerda, int direita)
{
  if (esquerda < direita)
  {
    int meio;
    meio = esquerda + ((direita - esquerda) / 2);
    ordena_partes(vetor, esquerda, meio);
    ordena_partes(vetor, meio + 1, direita);
    ordena(vetor, esquerda, meio, direita);
  }
  else
  {
    
  }

}

void printa_vetor(Produto vetor_ord[])
{
  int i;
  printf("Produtos\n");
  for (i = 0; i < contador_idp_produto; i++)
    printf("* %s %d %d\n", vetor_ord[i].string, vetor_ord[i].preco, vetor_ord[i].quantidade);

}

void lista_produtos()
{
  int i;
  Produto vetor_ord[10000];
  for (i = 0; i < contador_idp_produto; i++)
    vetor_ord[i] = total_produtos[i];

  ordena_partes(vetor_ord, 0, contador_idp_produto - 1);
  printa_vetor(vetor_ord);
}

void ordena_encomenda(Produto vetor[], int esquerda, int meio, int direita)
{
  int i;
  int j;
  int k;
  int res;
  int indice_esquerda;
  int indice_direita;
  Produto Esquerda[200];
  Produto Direita[200];
  indice_esquerda = (meio - esquerda) + 1;
  indice_direita = direita - meio;
  for (i = 0; i < indice_esquerda; i++)
    Esquerda[i] = vetor[esquerda + i];

  for (j = 0; j < indice_direita; j++)
    Direita[j] = vetor[(meio + 1) + j];

  i = 0;
  j = 0;
  k = esquerda;
  while ((i < indice_esquerda) && (j < indice_direita))
  {
    res = strcmp(Esquerda[i].string, Direita[j].string);
    if (res <= 0)
    {
      vetor[k++] = Esquerda[i++];
    }
    else
    {
      vetor[k++] = Direita[j++];
    }

  }

  while (i < indice_esquerda)
  {
    vetor[k] = Esquerda[i];
    i++;
    k++;
  }

  while (j < indice_direita)
  {
    vetor[k] = Direita[j];
    j++;
    k++;
  }

}

void ordena_partes_encomenda(Produto vetor[], int esquerda, int direita)
{
  if (esquerda < direita)
  {
    int meio;
    meio = esquerda + ((direita - esquerda) / 2);
    ordena_partes_encomenda(vetor, esquerda, meio);
    ordena_partes_encomenda(vetor, meio + 1, direita);
    ordena_encomenda(vetor, esquerda, meio, direita);
  }
  else
  {
    
  }

}

void printa_vetor_en(Produto vetor_ord[], int ide)
{
  int i;
  int numero_prd;
  printf("Encomenda %d\n", ide);
  numero_prd = total_encomendas[ide].numero_prd;
  for (i = 0; i < numero_prd; i++)
    printf("* %s %d %d\n", vetor_ord[i].string, vetor_ord[i].preco, vetor_ord[i].quantidade);

}

void lista_produtos_encomedas()
{
  int ide;
  int i;
  int n_prd;
  Produto vetor_ord[200];
  ide = new_sym_var(sizeof(int) * 8);
  if (ide > (contador_ide_encomenda - 1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    n_prd = total_encomendas[ide].numero_prd;
    for (i = 0; i < n_prd; i++)
    {
      vetor_ord[i] = total_encomendas[ide].n_produtos[i];
    }

    ordena_partes_encomenda(vetor_ord, 0, total_encomendas[ide].numero_prd - 1);
    printa_vetor_en(vetor_ord, ide);
  }

}

int main()
{
  char comando = '\0';
  while (comando != 'x')
  {
    comando = new_sym_var(sizeof(char) * 8);
    switch (comando)
    {
      case 'a':
        adiciona_prd();
        break;

      case 'q':
        adiciona_stck();
        break;

      case 'N':
        nova_encomeda();
        break;

      case 'A':
        adiciona_prd_encomenda();
        break;

      case 'r':
        remove_stk();
        break;

      case 'R':
        remove_prd_encomenda();
        break;

      case 'C':
        custo_encomenda();
        break;

      case 'p':
        altera_preco();
        break;

      case 'E':
        dercricao_prd_en();
        break;

      case 'm':
        listar_prd();
        break;

      case 'l':
        lista_produtos();
        break;

      case 'L':
        lista_produtos_encomedas();
        break;

    }

  }

  return 0;
}
