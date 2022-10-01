/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


int aux_produtos[10000];
int aux_encomenda[10000];
typedef struct produto
{
  char descricao[63];
  int preco;
  int peso;
  int qtd;
} Produto;
typedef struct encomenda
{
  int qtd;
  int preco;
} Encomenda;
static Encomenda encomenda[500][10000];
static Produto produto[10000];
void cria_produto(int lista_idp[10000], int idp);
void adiciona_stock(int lista_idp[10000]);
void cria_encomenda(int lista_ide[500], int ide);
void adiciona_encomenda(int lista_idp[10000], int lista_ide[500], int peso_total[500]);
void remove_stock(int lista_idp[10000]);
void altera_preco(int lista_idp[10000], int lista_ide[500]);
void custo_encomenda(int lista_ide[500], int lista_idp[10000]);
void remove_produto(int lista_ide[500], int lista_idp[10000], int peso_total[500]);
void desc_produto_enc(int lista_idp[10000], int lista_ide[500]);
void maior_quantidade(int lista_ide[500], int lista_idp[10000]);
void lista_produtos(int lista_idp[10000]);
void lista_produtos_encomenda(int lista_ide[500], int lista_idp[10000]);
void preenche_estrutura();
void preenche_peso(int peso_total[500]);
void junta_encomenda(int a[10000], int esq, int m, int dir);
void ordena(int a[10000], int esq, int dir, char key);
void junta_produtos(int a[10000], int esq, int m, int dir);
int main()
{
  char comando;
  int lista_idp[10000];
  int lista_ide[500];
  int idp = 0;
  int ide = 0;
  int peso_total[500];
  preenche_estrutura(encomenda);
  preenche_peso(peso_total);
  comando = new_sym_var(sizeof(char) * 8);
  while (comando != 'x')
  {
    switch (comando)
    {
      case 'a':
        cria_produto(lista_idp, idp);
        idp = idp + 1;
        break;

      case 'q':
        adiciona_stock(lista_idp);
        break;

      case 'N':
        cria_encomenda(lista_ide, ide);
        ide = ide + 1;
        break;

      case 'A':
        adiciona_encomenda(lista_idp, lista_ide, peso_total);
        break;

      case 'r':
        remove_stock(lista_idp);
        break;

      case 'R':
        remove_produto(lista_ide, lista_idp, peso_total);
        break;

      case 'C':
        custo_encomenda(lista_ide, lista_idp);
        break;

      case 'p':
        altera_preco(lista_idp, lista_ide);
        break;

      case 'E':
        desc_produto_enc(lista_idp, lista_ide);
        break;

      case 'm':
        maior_quantidade(lista_ide, lista_idp);
        break;

      case 'l':
        lista_produtos(lista_idp);
        break;

      case 'L':
        lista_produtos_encomenda(lista_ide, lista_idp);
        break;

    }

    comando = new_sym_var(sizeof(char) * 8);
  }

  return 0;
}

void cria_produto(int lista_idp[10000], int idp)
{
  for (int produto_index = 0; produto_index < 10; produto_index++)
  {
    produto[idp].descricao[produto_index] = new_sym_var(sizeof(char) * 8);
  }

  produto[idp].descricao[10 - 1] = '\0';
  produto[idp].preco = new_sym_var(sizeof(int) * 8);
  produto[idp].peso = new_sym_var(sizeof(int) * 8);
  produto[idp].qtd = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", idp);
  lista_idp[idp] = 'P';
}

void adiciona_stock(int lista_idp[10000])
{
  int idp_aux;
  int qtd_aux;
  idp_aux = new_sym_var(sizeof(int) * 8);
  qtd_aux = new_sym_var(sizeof(int) * 8);
  if (lista_idp[idp_aux] != 'P')
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_aux);
  }
  else
  {
    produto[idp_aux].qtd = produto[idp_aux].qtd + qtd_aux;
  }

}

void cria_encomenda(int lista_ide[500], int ide)
{
  lista_ide[ide] = 'E';
  printf("Nova encomenda %d.\n", ide);
}

void adiciona_encomenda(int lista_idp[10000], int lista_ide[500], int peso_total[500])
{
  int ide_aux;
  int idp_aux;
  int qtd_aux;
  ide_aux = new_sym_var(sizeof(int) * 8);
  idp_aux = new_sym_var(sizeof(int) * 8);
  qtd_aux = new_sym_var(sizeof(int) * 8);
  if (lista_idp[idp_aux] != 'P')
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
  }
  else
  {
    if (lista_ide[ide_aux] != 'E')
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
    }
    else
    {
      if (produto[idp_aux].qtd < qtd_aux)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_aux, ide_aux);
      }
      else
      {
        if ((peso_total[ide_aux] + (qtd_aux * produto[idp_aux].peso)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_aux, ide_aux);
        }
        else
        {
          encomenda[ide_aux][idp_aux].qtd = encomenda[ide_aux][idp_aux].qtd + qtd_aux;
          encomenda[ide_aux][idp_aux].preco = encomenda[ide_aux][idp_aux].preco + (qtd_aux * produto[idp_aux].preco);
          peso_total[ide_aux] = peso_total[ide_aux] + (qtd_aux * produto[idp_aux].peso);
          produto[idp_aux].qtd = produto[idp_aux].qtd - qtd_aux;
        }

      }

    }

  }

}

void remove_stock(int lista_idp[10000])
{
  int idp_aux;
  int qtd_aux;
  idp_aux = new_sym_var(sizeof(int) * 8);
  qtd_aux = new_sym_var(sizeof(int) * 8);
  if (lista_idp[idp_aux] != 'P')
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_aux);
  }
  else
  {
    if ((produto[idp_aux].qtd - qtd_aux) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_aux, idp_aux);
    }
    else
    {
      produto[idp_aux].qtd = produto[idp_aux].qtd - qtd_aux;
    }

  }

}

void altera_preco(int lista_idp[10000], int lista_ide[500])
{
  int idp_aux;
  int preco_aux;
  int i = 0;
  idp_aux = new_sym_var(sizeof(int) * 8);
  preco_aux = new_sym_var(sizeof(int) * 8);
  if (lista_idp[idp_aux] != 'P')
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_aux);
  }
  else
  {
    produto[idp_aux].preco = preco_aux;
    while (lista_ide[i] == 'E')
    {
      if (encomenda[i][idp_aux].qtd != 0)
      {
        encomenda[i][idp_aux].preco = encomenda[i][idp_aux].qtd * preco_aux;
      }
      else
      {
        
      }

      ++i;
    }

  }

}

void custo_encomenda(int lista_ide[500], int lista_idp[10000])
{
  int ide_aux;
  int i = 0;
  int total = 0;
  ide_aux = new_sym_var(sizeof(int) * 8);
  if (lista_ide[ide_aux] != 'E')
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_aux);
  }
  else
  {
    while (lista_idp[i] == 'P')
    {
      if (encomenda[ide_aux][i].qtd != 0)
      {
        total = total + encomenda[ide_aux][i].preco;
      }
      else
      {
        
      }

      ++i;
    }

    printf("Custo da encomenda %d %d.\n", ide_aux, total);
  }

}

void remove_produto(int lista_ide[500], int lista_idp[10000], int peso_total[500])
{
  int ide_aux;
  int idp_aux;
  ide_aux = new_sym_var(sizeof(int) * 8);
  idp_aux = new_sym_var(sizeof(int) * 8);
  if (lista_ide[ide_aux] != 'E')
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
  }
  else
  {
    if (lista_idp[idp_aux] != 'P')
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
    }
    else
    {
      peso_total[ide_aux] = peso_total[ide_aux] - (encomenda[ide_aux][idp_aux].qtd * produto[idp_aux].peso);
      produto[idp_aux].qtd = produto[idp_aux].qtd + encomenda[ide_aux][idp_aux].qtd;
      encomenda[ide_aux][idp_aux].qtd = 0;
      encomenda[ide_aux][idp_aux].preco = 0;
    }

  }

}

void desc_produto_enc(int lista_idp[10000], int lista_ide[500])
{
  int ide_aux;
  int idp_aux;
  ide_aux = new_sym_var(sizeof(int) * 8);
  idp_aux = new_sym_var(sizeof(int) * 8);
  if (lista_ide[ide_aux] != 'E')
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
  }
  else
  {
    if (lista_idp[idp_aux] != 'P')
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp_aux);
    }
    else
    {
      printf("%s %d.\n", produto[idp_aux].descricao, encomenda[ide_aux][idp_aux].qtd);
    }

  }

}

void maior_quantidade(int lista_ide[500], int lista_idp[10000])
{
  int idp_aux;
  int ide_aux;
  int i = 0;
  int maior;
  idp_aux = new_sym_var(sizeof(int) * 8);
  if (lista_idp[idp_aux] != 'P')
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_aux);
  }
  else
  {
    maior = encomenda[0][idp_aux].qtd;
    ide_aux = 0;
    while (lista_ide[i] == 'E')
    {
      if ((lista_ide[i + 1] == 'E') && (encomenda[i + 1][idp_aux].qtd > maior))
      {
        maior = encomenda[i + 1][idp_aux].qtd;
        ide_aux = i + 1;
      }
      else
      {
        if ((lista_ide[i + 1] == 'E') && (encomenda[i + 1][idp_aux].qtd == maior))
        {
          maior = encomenda[i + 1][idp_aux].qtd;
        }
        else
        {
          
        }

      }

      ++i;
    }

    if (maior != 0)
    {
      printf("Maximo produto %d %d %d.\n", idp_aux, ide_aux, maior);
    }
    else
    {
      
    }

  }

}

void lista_produtos(int lista_idp[10000])
{
  int j;
  int i = 0;
  int dir;
  int esq;
  int vetor_aux[10000];
  printf("Produtos\n");
  while (lista_idp[i] == 'P')
  {
    vetor_aux[i] = i;
    ++i;
  }

  dir = i - 1;
  esq = 0;
  ordena(vetor_aux, esq, dir, 'P');
  for (j = 0; j <= dir; ++j)
  {
    printf("* %s %d %d\n", produto[vetor_aux[j]].descricao, produto[vetor_aux[j]].preco, produto[vetor_aux[j]].qtd);
  }

}

void lista_produtos_encomenda(int lista_ide[500], int lista_idp[10000])
{
  int ide_aux;
  int cont = 0;
  int i;
  int k = 0;
  int dir;
  int lista_idps[200];
  ide_aux = new_sym_var(sizeof(int) * 8);
  if (lista_ide[ide_aux] != 'E')
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
  }
  else
  {
    printf("Encomenda %d\n", ide_aux);
    while (lista_idp[k] == 'P')
    {
      if (encomenda[ide_aux][k].qtd != 0)
      {
        lista_idps[cont] = k;
        ++cont;
      }
      else
      {
        
      }

      ++k;
    }

    dir = cont - 1;
    ordena(lista_idps, 0, dir, 'E');
    for (i = 0; i <= (cont - 1); i++)
    {
      printf("* %s %d %d\n", produto[lista_idps[i]].descricao, produto[lista_idps[i]].preco, encomenda[ide_aux][lista_idps[i]].qtd);
    }

  }

}

void preenche_estrutura()
{
  int k;
  int l;
  for (k = 0; k < 500; ++k)
  {
    for (l = 0; l < 10000; ++l)
    {
      encomenda[k][l].preco = 0;
      encomenda[k][l].qtd = 0;
    }

  }

}

void preenche_peso(int peso_total[500])
{
  int i;
  for (i = 0; i < 500; ++i)
  {
    peso_total[i] = 0;
  }

}

void ordena(int a[10000], int esq, int dir, char key)
{
  int m = (esq + dir) / 2;
  if (dir <= esq)
  {
    return;
  }
  else
  {
    
  }

  ordena(a, esq, m, key);
  ordena(a, m + 1, dir, key);
  if (key == 'P')
  {
    junta_produtos(a, esq, m, dir);
  }
  else
  {
    if (key == 'E')
    {
      junta_encomenda(a, esq, m, dir);
    }
    else
    {
      
    }

  }

}

void junta_encomenda(int a[10000], int esq, int m, int dir)
{
  int i;
  int j;
  int k;
  int idp1;
  int idp2;
  for (i = m + 1; i > esq; i--)
  {
    aux_encomenda[i - 1] = a[i - 1];
  }

  for (j = m; j < dir; j++)
  {
    aux_encomenda[(dir + m) - j] = a[j + 1];
  }

  for (k = esq; k <= dir; k++)
  {
    idp1 = aux_encomenda[j];
    idp2 = aux_encomenda[i];
    if (strcmp(produto[idp1].descricao, produto[idp2].descricao) < 0)
    {
      a[k] = aux_encomenda[j--];
    }
    else
    {
      a[k] = aux_encomenda[i++];
    }

  }

}

void junta_produtos(int a[10000], int esq, int m, int dir)
{
  int i;
  int j;
  int k;
  int idp1;
  int idp2;
  for (i = m + 1; i > esq; i--)
  {
    aux_produtos[i - 1] = a[i - 1];
  }

  for (j = m; j < dir; j++)
  {
    aux_produtos[(dir + m) - j] = a[j + 1];
  }

  for (k = esq; k <= dir; k++)
  {
    idp1 = aux_produtos[j];
    idp2 = aux_produtos[i];
    if (produto[idp1].preco < produto[idp2].preco)
    {
      a[k] = aux_produtos[j--];
    }
    else
    {
      if (produto[idp1].preco == produto[idp2].preco)
      {
        if (idp1 < idp2)
        {
          a[k] = aux_produtos[j--];
        }
        else
        {
          a[k] = aux_produtos[i++];
        }

      }
      else
      {
        a[k] = aux_produtos[i++];
      }

    }

  }

}
