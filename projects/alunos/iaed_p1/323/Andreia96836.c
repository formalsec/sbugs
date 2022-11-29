#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
/* Maximo de caracteres que a descricao do produto pode ter */
#define MAXdescricao 64
/* Quantidadade maxima de produtos */
#define MAXprodutos 10000
/* Quantidade maxima de encomendas */
#define MAXencomendas 500
/* Peso maximo de cada encomenda */
#define MAXpesoencomendas 200

/* Estrutura que define cada produto */
typedef struct Produto
{
  int idp;
  char descricao[MAXdescricao];
  int preco;
  int peso;
  int qtd;
}Produto;
/* Tabela que contem todos os produtos em sistema */
Produto sistema[MAXprodutos];
Produto vetor[MAXprodutos];
/* Estrutura que define cada encomenda */
typedef struct Encomenda
{
  int ide;
  int peso_encomenda;
  int custo_encomenda;
  int tabela[MAXprodutos];
}Encomenda;
/* Tabela que tem todas as encomendas contidas */
Encomenda conjunto[MAXencomendas];
/* Prototipos das funcoes definidas no projeto, sendo que cada uma esta associada a um comando */
int comando_a(Produto sistema[]);
int comando_q(Produto sistema[]);
int comando_N(Encomenda conjunto[]);
int comando_A(Encomenda conjunto[], Produto sistema[]);
int comando_r(Produto sistema[]);
int comando_R(Encomenda conjunto[]);
int comando_C(Encomenda conjunto[], Produto sistema[]);
int comando_p(Produto sistema[]);
int comando_E(Encomenda conjunto[], Produto sistema[]);
int comando_m(Produto sistema[], Encomenda conjunto[]);
int comando_l (Produto sistema[], Produto vetor[]);
int comando_L (Encomenda conjunto[], Produto sistema [], Produto vetor[]);
/* Prototipos de funcoes auxiliares */
void mergesort1l(Produto vetor[], int left, int right);
void merge1l(Produto vetor[], int left, int m, int right);
void mergesort2L(Produto vetor[], int left, int right);
void merge2L(Produto vetor[], int left, int m, int right);
/* Variaveis que indicam o numero de produtos/encomendas existentes */
int num_produtos = 0;
int num_encomendas = 0;

int main()
{
  char caracter;
  /* Atribuicao que serve para determinar se existe ou nao(=-1) encomenda */
  conjunto[0].ide=-1;
  sistema[0].idp=-1;
  caracter = getchar();
  /* Enquanto o programa nao acabar - comando x */
  while (caracter != 'x')
  {
    switch (caracter)
    {
    case 'a':
      comando_a(sistema);
      /* Incrementa o numero de produtos em sistema */
      num_produtos++;
      break;
    case 'q':
      comando_q(sistema);
      break;
    case 'N':
      comando_N(conjunto);
      /* Incrementa o numero de encomendas em sistema */
      num_encomendas++;
      break;
    case 'A':
      comando_A(conjunto, sistema);
      break;
    case 'R':
      comando_R(conjunto);
      break;
    case 'r':
      comando_r(sistema);
      break;
    case 'C':
      comando_C(conjunto, sistema);
      break;
    case 'p':
      comando_p(sistema);
      break;
    case 'E':
      comando_E(conjunto, sistema);
      break;
    case 'm':
      comando_m(sistema, conjunto);
      break;
    case 'l':
      comando_l(sistema, vetor);
      break;
    case 'L':
      comando_L(conjunto, sistema, vetor);
      break;
    }
    caracter=getchar();
  }
  return 0;
}

/* Funcao respetiva ao comando a que adiciona um novo produto ao sistema */
int comando_a(Produto sistema[])
{
  static int i = 0;
  if (i<MAXprodutos)
  {
    scanf(" %[^:]:%d:%d:%d", sistema[i].descricao, &sistema[i].preco, &sistema[i].peso, &sistema[i].qtd);
    printf("Novo produto %d.\r\n", i);
    sistema[i].idp = i;
  }
  return i++;
}

/* Funcao associada ao comando q que adiciona stock a um produto existente em sistema */
int comando_q(Produto sistema[])
{
  int produto, quantidade_adicionada, identificador;
  scanf(" %d:%d", &identificador, &quantidade_adicionada);
  /* Verifica se existe o produto 0 */
  if( identificador == 0 && sistema[0].idp==-1)
  {
    printf("Impossivel adicionar produto 0 ao stock. Produto inexistente.\r\n");
    return 0;
  }
  for (produto=0;produto<=MAXprodutos; produto++){
    if (sistema[produto].idp==identificador)
    {
      sistema[produto].qtd = sistema[produto].qtd + quantidade_adicionada;
      return 0;
    }
  }
  printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\r\n", identificador);
  return 0;
}

/* Funcao respetiva ao comando N que cria uma nova encomenda */
int comando_N(Encomenda conjunto[])
{
  static int j = 0;
  if (j<MAXencomendas)
  {
    printf("Nova encomenda %d.\r\n", j);
    conjunto[j].ide=j;
  }
  return j++;
}

/* Funcao respetiva ao comando A que adiciona produto a uma encomenda */
int comando_A(Encomenda conjunto[], Produto sistema[])
{
  int enc, prod, ide_dado, idp_dado, qtd_dada;
  scanf(" %d:%d:%d", &ide_dado, &idp_dado, &qtd_dada);
  /* Se nao tiver sido criada qualquer encomenda gera erro e acaba */
  if (conjunto[0].ide==-1 && ide_dado==0)
  {
    printf("Impossivel adicionar produto %d a encomenda 0. Encomenda inexistente.\r\n", idp_dado);
    return 0;
  }
  if (idp_dado == 0 && sistema[0].idp == -1)
  {
    printf("Impossivel adicionar produto 0 a encomenda %d. Produto inexistente.\r\n", ide_dado);
    return 0;
  }
  /* Ciclo que verifica se existe a encomenda. Se nao existir, gera erro */
  for (enc=0; enc<=MAXencomendas; enc++)
  {
    if (ide_dado == conjunto[enc].ide)
    {
      break;
    }
    else if(enc==MAXencomendas)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\r\n", idp_dado, ide_dado);
      return 0;
    }
  }
  /* Ciclo que verifica se existe o produto. Se nao existir, gera erro */
  for (prod=0; prod<=MAXprodutos; prod++)
  {
    if (idp_dado == sistema[prod].idp)
    {
      break;
    }
    else if(prod==MAXprodutos)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\r\n", idp_dado, ide_dado);
      return 0;
    }
  }
  if (qtd_dada <= sistema[idp_dado].qtd)
  {
    /* adicionar quantidade de produto a encomenda */
    conjunto[ide_dado].tabela[idp_dado] = conjunto[ide_dado].tabela[idp_dado] + qtd_dada;
    /* retirar a respetiva quantidade do stock */
    sistema[idp_dado].qtd = sistema[idp_dado].qtd - qtd_dada;
    /* peso total na encomenda depois de ser adicionado produto */
    conjunto[ide_dado].peso_encomenda = conjunto[ide_dado].peso_encomenda + sistema[idp_dado].peso*qtd_dada;

    if(conjunto[ide_dado].peso_encomenda>MAXpesoencomendas)
    {
      /* Voltar a colocar em stock pois o peso excedeu */
      sistema[idp_dado].qtd = sistema[idp_dado].qtd + qtd_dada;
      /* Tirar a quantidade de produto adicionado da encomenda, pois o peso excedeu */
      conjunto[ide_dado].tabela[idp_dado] = conjunto[ide_dado].tabela[idp_dado] - qtd_dada;
      /* Retirar peso que excedeu da encomenda */
      conjunto[ide_dado].peso_encomenda = conjunto[ide_dado].peso_encomenda - (sistema[idp_dado].peso*qtd_dada);
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\r\n", idp_dado, ide_dado);
      return 0;
    }
  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\r\n", idp_dado, ide_dado);
    return 0;
  }
  return 0;
}

/* Funcao respetiva ao comando r que retira stock a um produto existente */
int comando_r(Produto sistema[])
{
  int j=0, quantidade_retirada, identificador;
  scanf(" %d:%d", &identificador, &quantidade_retirada);
  if( identificador == 0 && sistema[0].idp==-1)
  {
    printf("Impossivel remover stock do produto 0. Produto inexistente.\r\n");
    return 0;
  }

  for (j=0;j<=MAXprodutos; j++)
  {
    if (sistema[j].idp==identificador)
    {
      /* Retirar respetiva quantidade de produtos do sistema */
      sistema[j].qtd = sistema[j].qtd - quantidade_retirada;
      /* O stock nao pode ficar negativo, logo e adicionado stock retirado */
      if (sistema[j].qtd<0)
      {
        sistema[j].qtd=sistema[j].qtd + quantidade_retirada;
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\r\n", quantidade_retirada, identificador);
        return 0;
      }
      return 0;
    }
  }
  printf("Impossivel remover stock do produto %d. Produto inexistente.\r\n", identificador);
  return 0;
}

/* Funcao respetiva ao comando R que retira um produto de uma encomenda */
int comando_R(Encomenda conjunto[])
{
  int ide_dado, idp_dado, prod, i;
  scanf(" %d:%d", &ide_dado, &idp_dado);
  if (conjunto[0].ide==-1 && ide_dado==0)
  {
    printf("Impossivel remover produto %d a encomenda 0. Encomenda inexistente.\r\n", idp_dado);
    return 0;
  }
  for (i=0; i<=MAXencomendas; i++)
  {
    if (ide_dado == conjunto[i].ide)
    {
      break;
    }
    else if(i==MAXencomendas)
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\r\n", idp_dado, ide_dado);
      return 0;
    }
  }
  for (prod=0; prod<=MAXprodutos; prod++)
  {
    if (idp_dado == sistema[prod].idp)
    {
      break;
    }
    else if(prod==MAXprodutos)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\r\n", idp_dado, ide_dado);
      return 0;
    }
  }
  /* Garantir que o produto deixa de existir na encomenda */
  sistema[idp_dado].qtd = sistema[idp_dado].qtd + conjunto[ide_dado].tabela[idp_dado];
  conjunto[ide_dado].peso_encomenda = conjunto[ide_dado].peso_encomenda - (sistema[idp_dado].peso*conjunto[ide_dado].tabela[idp_dado]);
  conjunto[ide_dado].tabela[idp_dado]=0;
  return 0;
}

/* Funcao associada ao comando C que calcula o custo de uma encomenda */
int comando_C(Encomenda conjunto[], Produto sistema[])
{
  int ide_dado, i, j, custo=0;
  scanf(" %d", &ide_dado);
  if (conjunto[0].ide==-1 && ide_dado==0)
  {
    printf("Impossivel calcular custo da encomenda 0. Encomenda inexistente.\r\n");
    return 0;
  }
  for (i=0; i<=MAXencomendas; i++)
  {
    if (ide_dado == conjunto[i].ide)
    {
      break;
    }
    else if(i==MAXencomendas)
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\r\n", ide_dado);
      return 0;
    }
  }
  /* Calculo do custo total da encomenda */
  for (j=0;j<MAXprodutos; j++)
  {
    if (conjunto[ide_dado].tabela[j]!=0)
    {
    custo = custo + sistema[j].preco*conjunto[ide_dado].tabela[j];
    }
  }
  printf("Custo da encomenda %d %d.\r\n", ide_dado,  custo);
  return 0;
}

/* Funcao respetiva ao comando p que altera o preco de um produto existente */
int comando_p(Produto sistema[])
{
  int i,idp_dado, preco_novo;
  scanf(" %d:%d", &idp_dado, &preco_novo);
  for (i=0;i<=MAXprodutos; i++)
  {
    if (sistema[i].idp==idp_dado)
    {
      /* Eliminar preco antigo e colocar o novo preco */
      sistema[i].preco = 0;
      sistema[i].preco= sistema[i].preco + preco_novo;
      return 0;
    }
  }
  printf("Impossivel alterar preco do produto %d. Produto inexistente.\r\n", idp_dado);
  return 0;
}

/* Funcao associada ao comando E que lista a descricao e a quantidade de um produto numa encomenda */
int comando_E (Encomenda conjunto[], Produto sistema[])
{
  int i, j, ide_dado, idp_dado;
  scanf(" %d:%d", &ide_dado, &idp_dado);
  if (conjunto[0].ide==-1 && ide_dado==0)
  {
    printf("Impossivel listar encomenda 0. Encomenda inexistente.\r\n");
    return 0;
  }
  if (idp_dado==0 && sistema[0].idp==-1)
  {
    printf("Impossivel listar produto 0. Produto inexistente.\r\n");
    return 0;
  }
  for (i=0; i<=MAXencomendas; i++)
  {
    if (ide_dado == conjunto[i].ide)
    {
      break;
    }
    else if(i==MAXencomendas)
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\r\n", ide_dado);
      return 0;
    }
  }
  for (j=0; j<=MAXprodutos; j++)
  {
    if (idp_dado == sistema[j].idp)
    {
      break;
    }
    else if(j==MAXprodutos)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\r\n", idp_dado);
      return 0;
    }
  }
  printf("%s %d.\r\n", sistema[idp_dado].descricao, conjunto[ide_dado].tabela[idp_dado]);
  return 0;
}

/* Funcao associada ao comando m que lista o identificador da encomenda em que o produto dado ocorre mais vezes */
int comando_m(Produto sistema[], Encomenda conjunto[])
{
  int encomenda, j, idp_dado, qtd=0, ide=0;
  scanf(" %d", &idp_dado);
  if (idp_dado==0 && sistema[0].idp==-1)
  {
    printf("Impossivel listar maximo do produto 0. Produto inexistente.\r\n");
    return 0;
  }
  for (j=0; j<=MAXprodutos; j++)
  {
    if (idp_dado == sistema[j].idp)
    {
      break;
    }
    else if(j==MAXprodutos)
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\r\n", idp_dado);
      return 0;
    }
  }
  if (conjunto[0].ide==-1)
  {
    return 0;
  }
  for (encomenda=0; encomenda<MAXencomendas; encomenda++)
  {
    /* Verifica qual a encomenda em que um tal produto existe em maior quantidade */
    if(conjunto[encomenda].tabela[idp_dado]>qtd)
    {
      qtd = conjunto[encomenda].tabela[idp_dado];
      ide=encomenda;
    }
    else if (encomenda==MAXencomendas-1)
    {
      break;
    }
  }
  if (qtd==0)
  {
    return 0;
  }
  printf("Maximo produto %d %d %d.\r\n", idp_dado, ide, qtd);
  return 0;
}

/* Funcao auxiliar associada ao comando l que lista todos os produtos existentes no sistema por ordem crescente de preco */
int comando_l (Produto sistema[], Produto vetor[])
{
  int left = 0;
  int right = num_produtos;
  int i;
  /* Copia o que ha em sistema para um auxiliar(vetor) */
  for (i=0; i<num_produtos; i++)
  {
    vetor[i]=sistema[i];
  }
  mergesort1l(vetor, left, right-1);
  printf("Produtos\r\n");
  for (i=left; i<right; i++)
  {
    if (vetor[i].preco !=0)
    {
      printf("* %s %d %d\r\n", vetor[i].descricao, vetor[i].preco, vetor[i].qtd);
    }
  }
  return 0;
}

/* Funcao associada ao comando L que lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
int comando_L (Encomenda conjunto[], Produto sistema [], Produto vetor[])
{
  int left = 0;
  int right = num_produtos;
  int i;
  int ide;
  scanf(" %d", &ide);
  /* Copia o que ha em sistema para um auxiliar(vetor) */
  for (i=0; i<num_produtos; i++)
  {
    vetor[i]=sistema[i];
  }
 /* Verificacao da encomenda */
  for (i=0; i<=num_encomendas; i++)
  {
    if (conjunto[i].ide==ide)
    {
      mergesort2L(vetor, left, right-1);
      printf("Encomenda %d\r\n", ide);
      for(i=0; i<num_produtos; i++)
      {
        if (conjunto[ide].tabela[vetor[i].idp]!=0)
        {
        printf("* %s %d %d\r\n", vetor[i].descricao, vetor[i].preco, conjunto[ide].tabela[vetor[i].idp]);
        }
      }
      return 0;
    }
    else if (i==num_encomendas)
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\r\n", ide);
    }
  }
  return 0;
}

/* Funcoes auxiliares a comando_l */
void mergesort1l(Produto vetor[], int left, int right)
{
  int m = (right+left)/2;

  if (right<=left)
  {
    return;
  }
  mergesort1l(vetor, left, m);
  mergesort1l(vetor, m+1, right);
  merge1l(vetor, left, m, right);
}
void merge1l(Produto vetor[], int left, int m, int right)
{
  Produto aux[MAXprodutos];
  int i, j, k;
  for(i=m+1; i>left; i--)
    aux[i-1] = vetor[i-1];
  for (j=m; j<right; j++)
    aux[right+m-j] = vetor[j+1];

  for(k= left; k<= right; k++)
  {
    if (aux[j].preco<aux[i].preco)
      vetor[k] = aux[j--];
    else if (aux[j].preco == aux[i].preco)
    {
      if (aux[j].idp<aux[i].idp)
      {
        vetor[k] = aux[j--];
      }
      else
      {
        vetor[k]= aux[i++];
      }
    }
    else
      vetor[k]=aux[i++];
  }
}

/* Funcoes auxiliares a comando_L */
void mergesort2L(Produto vetor[], int left, int right)
{
  int m = (right+left)/2;

  if (right<=left)
  {
    return;
  }
  mergesort2L(vetor, left, m);
  mergesort2L(vetor, m+1, right);
  merge2L(vetor, left, m, right);
}
void merge2L(Produto vetor[], int left, int m, int right)
{
  Produto aux[MAXprodutos];
  int i, j, k;
  for(i=m+1; i>left; i--)
    aux[i-1] = vetor[i-1];
  for (j=m; j<right; j++)
    aux[right+m-j] = vetor[j+1];

  for(k= left; k<= right; k++)
  {
    if (strcmp(aux[j].descricao, aux[i].descricao)<0)
      vetor[k] = aux[j--];
    else
      vetor[k]=aux[i++];
  }
}
