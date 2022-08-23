#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/* Macros */
#define MAX_CHAR_DESCR 64  /* Maximo de caracteres da descricao mais um para o \0. */
#define MAX_PRODUTOS 10000 /* Maximo de produtos no sistema. */
#define MAX_ENCOMENDAS 500 /* Maximo de encomendas no sistema. */
#define MAX_PESO 200       /* Peso maximo de uma encomenda. */
#define TRUE 1 /* Representao o valor booleano verdadeiro. */
#define ENCOMENDA_EXISTE(ide) (ide < num_encomendas)
#define PRODUTO_EXISTE(idp) (idp < num_produtos)
#define PRECO 'p'
#define DESCRICAO 'd'

/* Estruturas de Dados */
typedef struct
{
  int id;
  char desc[MAX_CHAR_DESCR];
  int preco;
  int peso;
  int quant;
  int quantEmEncomendas;
} Produto;

typedef struct
{
  int ordenado[MAX_PESO];
  int peso;
  int numero_produtos;
} Encomenda;

int matriz[MAX_ENCOMENDAS][MAX_PRODUTOS]; /* matriz com as quantidades de cada produto por encomenda. */
Produto stock[MAX_PRODUTOS];          /* Vetor com produtos em stock. */
int stock_ordenado[MAX_PRODUTOS];     /* Vetor com id dos produtos ordenados por preco. */
Encomenda encomendas[MAX_ENCOMENDAS]; /* Vetor com encomendas do sistema. */
int num_encomendas;                   /* Numero de encomendas no sistema. */
int num_produtos;                     /* Numero de produtos no sistema. */

/* Prototipos. */
void a();
void q();
void N();
void A();
void r();
void R();
void C();
void p();
void m();
void E();
void l();
void L();
void adicionaOrdenado(int arr[], int n, int idp, char key);
void removeOrdenado(int arr[], int n, int idp);
int cmpProdutos(Produto p1, Produto p2, char key);
int procura(int arr[], int n, int id);

/* Funcao principal do programa que le e executa os comandos. */
int main()
{
  while (TRUE)
  {
    /* Consoante o caracter fornecido eh chamada a funcao correspondente. */
    switch (getchar())
    {
    case 'a':
      a();
      break;
    case 'q':
      q();
      break;
    case 'N':
      N();
      break;
    case 'A':
      A();
      break;
    case 'r':
      r();
      break;
    case 'R':
      R();
      break;
    case 'C':
      C();
      break;
    case 'p':
      p();
      break;
    case 'E':
      E();
      break;
    case 'm':
      m();
      break;
    case 'l':
      l();
      break;
    case 'L':
      L();
      break;
    case 'x':
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}

/* Adiciona um produto ao sistema. */
void a()
{
  Produto p = {0};
  scanf(" %[^:]:%d:%d:%d", p.desc, &p.preco, &p.peso, &p.quant);
  stock[(p.id = num_produtos)] = p;
  printf("Novo produto %d.\n", p.id);
  /* Adiciona o id ao array ordendado pelo preco. */
  adicionaOrdenado(stock_ordenado, num_produtos, p.id, PRECO);
  num_produtos++;
}

/* Caso o produto exista adiciona quantidade ao produto. */
void q()
{
  int idp, quant;
  scanf("%d:%d", &idp, &quant);
  if (PRODUTO_EXISTE(idp))
    stock[idp].quant += quant;
  else
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/* Adiciona uma encomenda ao sistema. */
void N()
{
  printf("Nova encomenda %d.\n", num_encomendas);
  num_encomendas++;
}

/* Adiciona um produto a uma encomenda.Excepto em condicoes de erro. */
void A()
{
  int ide, idp, quant;
  scanf(" %d:%d:%d", &ide, &idp, &quant);
  /* Possiveis condicoes de erro. */
  if (!ENCOMENDA_EXISTE(ide))
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  else if (!PRODUTO_EXISTE(idp))
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  else if (stock[idp].quantEmEncomendas + quant > stock[idp].quant)
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
  else if (stock[idp].peso * quant + encomendas[ide].peso > MAX_PESO)
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
  else
  {
    /* Se o produto ainda nao esta na encomenda. */
    if (!matriz[ide][idp])
    {
      /* Adiciona o id ao array ordendado por ordem alfabetica. */
      adicionaOrdenado(encomendas[ide].ordenado, encomendas[ide].numero_produtos, idp, DESCRICAO);
      encomendas[ide].numero_produtos++;
    }
    matriz[ide][idp] += quant;
    encomendas[ide].peso += stock[idp].peso * quant;
    stock[idp].quantEmEncomendas += quant;
  }
}

/* Remove quantidade de um produto em stock.Excepto em condicoes de erro.*/
void r()
{
  int idp, quant;
  scanf(" %d:%d", &idp, &quant);
  /* Possiveis condicoes de erro. */
  if (!PRODUTO_EXISTE(idp))
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  else if (stock[idp].quant - quant < stock[idp].quantEmEncomendas)
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, idp);
  else
    stock[idp].quant -= quant;
}

/* Remove um produto de uma encomenda.Excepto em condicoes de erro. */
void R()
{
  int ide, idp, quant;
  scanf(" %d:%d", &ide, &idp);
  /* Possiveis condicoes de erro. */
  if (!ENCOMENDA_EXISTE(ide))
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  else if (!PRODUTO_EXISTE(idp))
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  else
  {
    /* Se a encomenda tem produtos. */
    if (encomendas[ide].numero_produtos)
    {
      quant = matriz[ide][idp];
      /* Se o produto esta na encomenda. */
      if (quant)
      {
        matriz[ide][idp] = 0;
        encomendas[ide].peso -= stock[idp].peso * quant;
        stock[idp].quantEmEncomendas -= quant;
        removeOrdenado(encomendas[ide].ordenado, encomendas[ide].numero_produtos, idp);
        encomendas[ide].numero_produtos--;
      }
    }
  }
}

/* Caso a encomenda exista calcula o custo da encomenda. */
void C()
{
  int ide, i, j, max, custo = 0;
  scanf("%d", &ide);
  max = encomendas[ide].numero_produtos;
  /* Possiveis condicoes de erro. */
  if (!ENCOMENDA_EXISTE(ide))
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  else
  {
    /* Ciclo que percorre os produtos dentro de uma encomenda calculando o custo. */
    for (i = 0, j = 0; i < MAX_PRODUTOS && j < max; i++)
    {
      if (matriz[ide][i])
      {
        j++;
        custo += matriz[ide][i] * stock[i].preco;
      }
    }
    printf("Custo da encomenda %d %d.\n", ide, custo);
  }
}

/* Caso o produto exista no sistema o seu preco eh alterado. */
void p()
{
  int idp, preco;
  scanf(" %d:%d", &idp, &preco);
  /* Possiveis condicoes de erro. */
  if (!PRODUTO_EXISTE(idp))
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  else
  {
    /* Retira o indice do produto cujo o preco sera alterado. */
    removeOrdenado(stock_ordenado, num_produtos, idp); 
    num_produtos--;
    stock[idp].preco = preco; /* Altera o preco do produto. */
    /* Adiciona o indice do produto ao array ordenado. */
    adicionaOrdenado(stock_ordenado, num_produtos, idp, PRECO); 
    num_produtos++;
  }
}

/* Imprime para o stdout a descricao de um produto e a sua quantidade numa dada encomenda.
 * Excepto em condicoes de erro.
 */
void E()
{
  int ide, idp;
  scanf(" %d:%d", &ide, &idp);
  /* Possiveis condicoes de erro. */
  if (!ENCOMENDA_EXISTE(ide))
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  else if (!PRODUTO_EXISTE(idp))
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  else
    printf("%s %d.\n", stock[idp].desc, matriz[ide][idp]);
}

/* Imprime para o stdout a encomenda e a quantidade desse produto nessa 
* encomenda, sendo que o produto existe em maior quantidade nessa encomenda. 
* Excepto em condicoes de erro.
*/
void m()
{
  int idp, i, max, maxValor, valor;
  scanf(" %d", &idp);
  /* Possiveis condicoes de erro. */
  if (!PRODUTO_EXISTE(idp))
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  else
  {
    /* Ciclo que procura a encomenda onde o produto existe em maior quantidade. */
    maxValor = INT_MIN;
    for (i = 0; i < MAX_ENCOMENDAS; i++)
    {
      valor = matriz[i][idp];
      if (valor > maxValor)
      {
        maxValor = valor;
        max = i;
      }
    }
    /* Imprime o valor se este for diferente de 0. */
    if (maxValor)
      printf("Maximo produto %d %d %d.\n", idp, max, maxValor);
  }
}

/* Lista todos os produtos existentes no sistema por ordem crescente de pre?o. */
void l()
{
  int i, quant;
  Produto p;
  printf("Produtos\n");
  for (i = 0; i < num_produtos; i++)
  {
    /* Calcula a quantidade de produto que nao esta em encomendas. */
    quant = stock[stock_ordenado[i]].quant - stock[stock_ordenado[i]].quantEmEncomendas;
    p = stock[stock_ordenado[i]];
    printf("* %s %d %d\n", p.desc, p.preco, quant);
  }
}

/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o. Excepto em condicoes de erro. */
void L()
{
  int i, ide, n;
  Produto p;
  scanf(" %d", &ide);
  /* Possiveis condicoes de erro. */
  if (!ENCOMENDA_EXISTE(ide))
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  else
  {
    n = encomendas[ide].numero_produtos;
    printf("Encomenda %d\n", ide);
    /* Percorre o array que contem os indices dos produtos da encomenda ordenados por ordem alfabetica. */
    for (i = 0; i < n; i++)
    {
      p = stock[encomendas[ide].ordenado[i]];
      printf("* %s %d %d\n", p.desc, p.preco, matriz[ide][p.id]);
    }
  }
}

/* Compara dois produtos consoate a chave fornecida. */
int cmpProdutos(Produto p1, Produto p2, char key)
{
  /* Se a chave for preco entao compara os precos dos produtos. */
  if (key == PRECO)
  {
    if (p1.preco == p2.preco)
      return 0;
    return (p1.preco > p2.preco ? 1 : -1);
  }
  /* Senao compara as descricoes dos produtos. */
  else
    return strcmp(p1.desc, p2.desc);
}

/* Adiciona o id p ao array ordenado mantendo a ordem. */
void adicionaOrdenado(int arr[], int n, int p, char key)
{
  int i, j;
  /* Percorre o array em ordem inversa enquanto arr[i] for maior que p. */
  for (i = n - 1; (i >= 0 && cmpProdutos(stock[arr[i]], stock[p], key) > 0); i--)
  {
    arr[i + 1] = arr[i];
  }
  /* Continua a percorrer o array enquanto arr[i] == p e o identificador de p for menor , mantendo assim a ordem relativa. */
  for (j = i; (j >= 0 && p < arr[j] && cmpProdutos(stock[arr[j]], stock[p], key) == 0); j--)
  {
    arr[j + 1] = arr[j];
  }

  arr[j + 1] = p;
}

/* Remove o id p ao array ordenado mantendo a ordem. */
void removeOrdenado(int arr[], int n, int p)
{
  int i;
  int pos = procura(arr, n - 1, p); /* Encontra a pos de p no array. */
  for (i = pos; i < n - 1; i++) /* Aplica um shift ao array para preencher arr[pos]. */
    arr[i] = arr[i + 1];
}

/* Retorna o indice de id no array. */
int procura(int arr[], int n, int id)
{
  int i;
  for (i = 0; i < n; i++)
  {
    if (arr[i] == id)
      return i;
  }
  return i;
}
