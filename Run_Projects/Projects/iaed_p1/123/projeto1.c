#include <stdio.h>
#include <string.h>
/*numero maximo de caracteres para a descricao de um porduto*/
#define DIM 63
/*numero maximo de produtos*/
#define MAX_PRODUTOS 10000
/*numero maximo de encomendas*/
#define MAX_ENCOMENDAS 500

typedef struct stock {
  int quantidade;
  int preco;
  int peso;
  char descricao[DIM];
}stock;

typedef struct encomenda {
  stock produtos[MAX_PRODUTOS];
}encomenda;

encomenda encomendas[MAX_ENCOMENDAS]; /*estrutura que representa as encomendas*/

/*Esta funcao atribui valores a estrutura stocks que foi inicializada na main, dando depois print de "Novo produto %d.\n"*/
void cria_produto(int identificador_produtos, stock stocks[MAX_PRODUTOS])
{
  scanf(" %[^:]:%d:%d:%d",stocks[identificador_produtos].descricao, &stocks[identificador_produtos].preco, &stocks[identificador_produtos].peso, &stocks[identificador_produtos].quantidade );
  printf("Novo produto %d.\n", identificador_produtos);
}

/*Esta funcao verifica se o produto ja existe e adiciona lhe a quantidade pretendida, caso contrario emite um erro*/
void adiciona_produto(int idp, int qtd, int identificador_produtos, stock stocks[MAX_PRODUTOS])
{
  if (idp >= identificador_produtos)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    stocks[idp].quantidade += qtd;
  }
}

/*Esta funcao da print de "Nova encomenda %d.\n", o valor identificador_encomendas e depois incrementado na main */
void cria_encomenda(int identificador_encomendas)
{
  printf("Nova encomenda %d.\n", identificador_encomendas);
}

/*Esta funcao emite erros se o produto nao existir, se a encomenda nao existir, se nao houver quantidade em stock insuficiente para uma encomenda, ou se o peso da encomenda exceder 200, caso nao emita nenhum erro adiciona a encomenda a quantidade de um produto inserida, removendo-a assim do stock */
void adiciona_encomenda(int ide, int idp, int qtd, int identificador_produtos, int identificador_encomendas, int peso_total, stock stocks[MAX_PRODUTOS], encomenda encomendas[MAX_ENCOMENDAS])
{
  int i;
  if (idp >= identificador_produtos)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else if (ide >= identificador_encomendas)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide );
    return;
  }
  else if (stocks[idp].quantidade < qtd)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return;
  }
  else
  {
    for(i=0 ; i<MAX_PRODUTOS ; i++)
    {
      peso_total += encomendas[ide].produtos[i].peso;
    }
    peso_total += qtd*stocks[idp].peso;
    if (peso_total > 200)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
      return;
    }
    else
    {
      encomendas[ide].produtos[idp].peso += qtd* stocks[idp].peso;
      encomendas[ide].produtos[idp].quantidade += qtd ;
      encomendas[ide].produtos[idp].preco = stocks[idp].preco ;
      strcpy(encomendas[ide].produtos[idp].descricao, stocks[idp].descricao);
      stocks[idp].quantidade -= qtd;
    }
  }
}

/*Esta funcao remove ao stock de um porduto a quantidade inserida pelo utilizdor, emitindo erros se o produto nao existir ou se nao houver quantidade em stock suficiente*/
void remove_stock_produto(int identificador_produtos, int idp, int qtd, stock stocks[MAX_PRODUTOS])
{
  if (idp >= identificador_produtos)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else if(stocks[idp].quantidade < qtd)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd , idp);
    return;
  }
  else
  {
    stocks[idp].quantidade -=qtd;
  }
}

/*Esta funcao remove um porduto,inserido pelo utilizador, de uma encomenda, aumentando assim a qunatidade em stock desse produto*/
void remover_produto_encomenda(int ide, int idp, int identificador_produtos, int identificador_encomendas, stock stocks[MAX_PRODUTOS], encomenda encomendas[MAX_ENCOMENDAS])
{
  if (ide >= identificador_encomendas)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide );
    return;
  }
  else if (idp >= identificador_produtos)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    stocks[idp].quantidade += encomendas[ide].produtos[idp].quantidade;
    encomendas[ide].produtos[idp].peso = 0;
    encomendas[ide].produtos[idp].preco = 0;
    encomendas[ide].produtos[idp].quantidade = 0;
  }
}

/*Esta funcao calcula o preco total de uma encomenda e emite um erro caso essa encomenda nao exista*/
void calcula_preco_encomenda(int ide, int preco_total, int identificador_encomendas, int i,stock stocks[MAX_PRODUTOS], encomenda encomendas[MAX_ENCOMENDAS])
{
  if (ide >= identificador_encomendas)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide );
    return;
  }
  else
  {
    for(i=0 ; i<MAX_PRODUTOS ; i++)
    {
      preco_total += encomendas[ide].produtos[i].quantidade * stocks[i].preco;
    }
    printf("Custo da encomenda %d %d.\n", ide, preco_total);
  }
}
/*Esta funcao muda o preco de um produto,caso o produto nao exista emite um erro*/
void muda_preco(int idp, int preco, int identificador_produtos, stock stocks[MAX_PRODUTOS])
{
  if (idp >= identificador_produtos)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    stocks[idp].preco = preco;
  }
}

/*Esta funcao da print a descricao e  a quantidade de um produto numa encomenda, se a encomenda ou o produto nao existirem emite um erro*/
void produto_encomenda(int ide , int idp , int identificador_produtos, int identificador_encomendas, stock stocks[MAX_PRODUTOS], encomenda encomendas[MAX_ENCOMENDAS])
{
  if (ide >= identificador_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide );
    return;
  }
  else if (idp >= identificador_produtos)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    printf("%s %d.\n", stocks[idp].descricao, encomendas[ide].produtos[idp].quantidade);
  }
}

/*Esta funcao da print ao identificador da encomenda em que o produto inserido aparece mais vezes, seguido da quantidade desse produto na encomenda*/
void maximo_encomenda(int idp, int identificador_produtos, encomenda encomendas[MAX_ENCOMENDAS])
{
  int contador, encomenda_maxima, maximo = -1;
  if (idp >= identificador_produtos)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    for(contador=0 ; contador<MAX_ENCOMENDAS ; contador++)
    {
      if (maximo < encomendas[contador].produtos[idp].quantidade)
      {
        maximo = encomendas[contador].produtos[idp].quantidade;
        encomenda_maxima = contador;
      }
    }
  }
  if (maximo == 0)
  {
    return;
  }
  else
  {
    printf("Maximo produto %d %d %d.\n", idp, encomenda_maxima, encomendas[encomenda_maxima].produtos[idp].quantidade);
  }
}

void merge_1(int guarda_idp[], int left, int m , int right, stock stocks[MAX_PRODUTOS])
{
  int aux[MAX_PRODUTOS];
  int i, j, k;
  for(i=m+1 ; i>left ; i--)
  {
    aux[i-1] = guarda_idp[i-1];
  }
  for (j=m ; j<right ; j++)
  {
    aux[right+m-j] = guarda_idp[j+1];
  }
  for (k=left ; k<=right ; k++)
  {
    if ((stocks[aux[j]].preco < stocks[aux[i]].preco) || ((stocks[aux[j]].preco==stocks[aux[i]].preco) && aux[j]<aux[i]))
    {
      guarda_idp[k] = aux[j--];
    }
    else
    {
      guarda_idp[k] = aux[i++];
    }
  }
}
void mergesort_1(int guarda_idp[25], int left, int right, stock stocks[MAX_PRODUTOS])
{
  int m = (right+left)/2;
  if (right <= left)
  {
    return;
  }
  mergesort_1(guarda_idp,left,m,stocks);
  mergesort_1(guarda_idp,m+1,right,stocks);
  merge_1(guarda_idp,left,m,right,stocks);
}

/*Esta funcao vai ordenar por ordem crescente de precos todos os produtos inseridos no sistema, para isso recorre a funcao merge_sort1*/
void lista_produtos(int guarda_idp[MAX_PRODUTOS], int i, stock stocks[MAX_PRODUTOS])
{
  int left = 0, right = i-1, j;
  mergesort_1(guarda_idp, left, right, stocks);
  printf("Produtos\n");
  for(j=0 ; j<i ; j++)
  {
    printf("* %s %d %d\n", stocks[guarda_idp[j]].descricao, stocks[guarda_idp[j]].preco, stocks[guarda_idp[j]].quantidade);
  }
}

void merge_2(int guarda_idp[], int left, int m , int right, stock stocks[MAX_PRODUTOS])
{
  int aux[MAX_PRODUTOS];
  int i, j, k;
  for(i=m+1 ; i>left ; i--)
  {
    aux[i-1] = guarda_idp[i-1];
  }
  for (j=m ; j<right ; j++)
  {
    aux[right+m-j] = guarda_idp[j+1];
  }
  for (k=left ; k<=right ; k++)
  {
    if ((strcmp(stocks[aux[j]].descricao, stocks[aux[i]].descricao) < 0) || ((strcmp(stocks[aux[j]].descricao, stocks[aux[i]].descricao) == 0) && aux[j]<aux[i]))
    {
      guarda_idp[k] = aux[j--];
    }
    else
    {
      guarda_idp[k] = aux[i++];
    }
  }
}
void mergesort_2(int guarda_idp[25], int left, int right, stock stocks[MAX_PRODUTOS])
{
  int m = (right+left)/2;
  if (right <= left)
  {
    return;
  }
  mergesort_2(guarda_idp,left,m,stocks);
  mergesort_2(guarda_idp,m+1,right,stocks);
  merge_2(guarda_idp,left,m,right,stocks);
}

/*Esta funcao vai ordenar por ordem alfabetica todos os produtos presentes numa encomenda escolhida pelo utilizador, apra isoo recoore a funcao merge_sort2*/
void lista_encomenda(int ide , int identificador_encomendas, int guarda_idp[MAX_PRODUTOS], stock stocks[MAX_PRODUTOS], encomenda encomendas[MAX_ENCOMENDAS])
{
  int i = 0, contador , left = 0;
  if (ide >= identificador_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    for(contador=0 ; contador<MAX_PRODUTOS ; contador++)
    {
      if (encomendas[ide].produtos[contador].quantidade != 0)
      {
        guarda_idp[i] = contador;
        i++;
      }
    }
    mergesort_2(guarda_idp, left, (i-1), stocks);
    printf("Encomenda %d\n", ide);
    for(contador=0 ; contador<i ; contador++)
    {
      printf("* %s %d %d\n", stocks[guarda_idp[contador]].descricao, stocks[guarda_idp[contador]].preco, encomendas[ide].produtos[guarda_idp[contador]].quantidade);
    }
  }
}

/*Na main sao lidos os comandos inseridos pelo utilizador atraves do switch*/
int main()
{
  char letra;
  stock stocks[MAX_PRODUTOS];
  int i, idp, ide, qtd, identificador_produtos = 0, identificador_encomendas = 0, peso_total, preco_total, guarda_idp[MAX_PRODUTOS], preco;
  while ((letra=getchar()) != EOF)
  {
    switch(letra)
    {
      case 'a':
       cria_produto(identificador_produtos, stocks);
       identificador_produtos += 1 ;
       break;
      case 'q':
        scanf("%d:%d", &idp, &qtd);
        adiciona_produto(idp, qtd, identificador_produtos, stocks);
        break;
      case 'N':
        cria_encomenda(identificador_encomendas);
        identificador_encomendas +=1;
        break;
      case 'A':
        peso_total = 0;
        scanf("%d:%d:%d", &ide, &idp, &qtd);
        adiciona_encomenda(ide, idp, qtd, identificador_produtos, identificador_encomendas, peso_total, stocks, encomendas);
        break;
      case 'r':
        scanf("%d:%d", &idp, &qtd);
        remove_stock_produto(identificador_produtos, idp, qtd, stocks);
        break;
      case 'R':
        scanf(" %d:%d", &ide, &idp);
        remover_produto_encomenda(ide, idp, identificador_produtos, identificador_encomendas, stocks, encomendas);
        break;
      case 'C':
        preco_total = 0;
        scanf("%d", &ide);
        calcula_preco_encomenda(ide, preco_total, identificador_encomendas, i, stocks, encomendas);
        break;
      case 'p':
        scanf("%d:%d", &idp, &preco);
        muda_preco(idp, preco, identificador_produtos, stocks);
        break;
      case 'E':
        scanf("%d:%d", &ide, &idp);
        produto_encomenda(ide, idp, identificador_produtos, identificador_encomendas, stocks, encomendas);
        break;
      case 'm':
        scanf("%d", &idp);
        maximo_encomenda(idp, identificador_produtos, encomendas);
        break;
      case 'l':
        i = 0;
        while (stocks[i].peso != 0)
        {
          guarda_idp[i]=i;
          i++;
        }
        lista_produtos(guarda_idp, i, stocks);
        break;
      case 'L':
        scanf("%d", &ide);
        lista_encomenda(ide, identificador_encomendas, guarda_idp, stocks, encomendas);
        break;
      case 'x':
        break;
     }
  }
  return 0;
}
