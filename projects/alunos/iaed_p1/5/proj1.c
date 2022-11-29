#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_PRODUCTS_NUMBER 10000 /*  Numero  maximo de produtos. */
#define MAX_ORDERS_NUMBER 500 /*  Numero  maximo de encomendas. */
#define MAX_NAME_LEN 64 /*  Comprimento  maximo da descricao do produto. */
#define MAX_ORDER_WEIGHT 200 /*  Peso  maximo de cada encomenda. */

/**
 * Estrutura que representa um produto do sistema.
 */
typedef struct {
  char name[MAX_NAME_LEN]; /* Descricao do produto com um maximo de 
			      64 caracteres, incluindo o '\0'. */
  int price; /*  Preco do produto, numero inteiro maior que 0. */
  int weight; /*  Peso do produto, numero inteiro maior que 0. */
  int stock; /* Quantidade em stock do produto, numero inteiro maior ou igual a 0. */
} product_t;

/**
 * Estrutura que representa um produto de uma encomenda.
 */
typedef struct {
  int id; /* Identificador do produto, numero inteiro entre 0 e 9999. */
  char name[MAX_NAME_LEN]; /* Descricao do produto com um maximo de 
			      64 caracteres, incluindo o '\0'. */
  int qty; /* Quantidade encomendada do produto, numero inteiro maior ou igual a 0. */
} productOrdered_t;

/**
 * Estrutura que representa uma encomenda.
 */
typedef struct {
  productOrdered_t productOrdered[MAX_PRODUCTS_NUMBER]; /* Vetor com os 
							   produtos da encomenda. */
  int totalWeight; /* Peso da encomenda, numero inteiro entre 0 e 200. */
  int productsNumber; /* Numero total de produtos da encomenda. */
} order_t;

/**
 * Variaveis locais ao programa.
 */ 
static product_t product[MAX_PRODUCTS_NUMBER]; /* Vetor com os produtos. */
static order_t order[MAX_ORDERS_NUMBER]; /* Vetor com as encomendas. */
static int productsNumber; /* Numero total de produtos no sistema. */
static int ordersNumber; /* Numero total de encomendas no sistema. */
int idOrder; /* Identificador da encomenda cujos produtos se pretenda ordenar 
	      por ordem alfabetica da sua descricao. */

/**
 * Declaracao das funcoes utilizadas neste programa.
 */
void comando_a();
void comando_q();
void comando_N();
void comando_A();
void comando_r();
void comando_R();
void comando_C();
void comando_p();
void comando_E();
void comando_m();
void comando_l();
void comando_L();
void comando_x();

int find_product(int ido, int idp);
void remove_product(int ido, int idp);
int evaluate_order_price(int ido);
void quicksort(int v[], int left, int right, int cmp (int , int ));
void swap(int v[], int i, int j);
int pcmp(int pa, int pb);
int pocmp(int poa, int pob);

/**
 * Funcao main.
 */
int main() {

  while(1) {
    /* Comandos: a(4), q(2), N(0), A(3), r(2), R(2), C(1), p(2), E(2), m(1), l(0), L(1), x(0). */
    char comando = getchar();
    
    /* Processa o comando. */
    switch(comando) {
    case 'a':
      comando_a();
      break;
    case 'q':
      comando_q();
      break;
    case 'N':
      comando_N();
      break;
    case 'A':
      comando_A();
      break;
    case 'r':
      comando_r();
      break;
    case 'R':
      comando_R();
      break;
    case 'C':
      comando_C();
      break;
    case 'p':
      comando_p();
      break;
    case 'E':
      comando_E();
      break;
    case 'm':
      comando_m();
      break;
    case 'l':
      comando_l();
      break;
    case 'L':
      comando_L();
      break;
    case 'x':
      /* Termina o programa com sucesso. */
      return EXIT_SUCCESS;
    default:
      /* Nao devemos chegar aqui. */
      assert(0);
    }

    getchar(); /* Remover o '\n' no final do comando stdin. */
  }
  
    /* Nao devemos chegar aqui em condicoes normais. */
    return EXIT_FAILURE;
}

/* Funcao para processar o comando 'a'. */
void comando_a() {
  if (productsNumber < MAX_PRODUCTS_NUMBER) {
    /* Ler informacao e atualizar o vetor com os produtos. */
    scanf(" %63[^:]%*c%d%*c%d%*c%d", product[productsNumber].name,
	  &product[productsNumber].price, &product[productsNumber].weight,
	  &product[productsNumber].stock);
   
    /* Imprimir a informacao pretendida. */
    printf("Novo produto %d.\n", productsNumber);

    /* Atualizar o numero total de produtos no sistema. */
    productsNumber++;
  }
}

/* Funcao para processar o comando 'q'. */
void comando_q() {
  int idp, qty;

  scanf(" %d%*c%d", &idp, &qty);
  if (idp <productsNumber)
    product[idp].stock += qty;
  else
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/* Funcao para processar o comando 'N'. */
void comando_N() {
  if (ordersNumber< MAX_ORDERS_NUMBER) {
    /* Imprimir a informacao pretendida e inicializar os campos totalWeight e 
     * productsNumber da encomenda acabada de criar. */
    printf("Nova encomenda %d.\n", ordersNumber);
    order[ordersNumber].totalWeight = 0;
    order[ordersNumber].productsNumber = 0;
    /*  Atualizar o numero total de encomendas.*/
    ordersNumber++;
  }
}

/* Funcao para processar o comando 'A'. */
void comando_A() {
  int ido, idp, qty, i;

  scanf(" %d%*c%d%*c%d", &ido, &idp, &qty);
  if (ido >= ordersNumber)
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",
	   idp, ido);
  else if (idp >= productsNumber)
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",
	   idp, ido);
  else if (qty > product[idp].stock)
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",
	   idp, ido);
  else if (product[idp].weight * qty + order[ido].totalWeight > MAX_ORDER_WEIGHT)
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",
	   idp, ido);
  else {
    /* Procurar o produto na encomenda. */
    i = find_product(ido, idp);
    /* Atualizar os vetores com os produtos do sistema e com os produtos da encomenda e, 
     * se for o caso, o numero de produtos encomendados.*/
    if (i < order[ido].productsNumber) /* Se o produto existir na encomenda... */
      order[ido].productOrdered[i].qty += qty; /* Adicionar a nova quantidade a quantidade existente. */
    else { /* Se o produto ainda nao existir na encomenda...*/
      /* Adicionar o produto a encomenda. */
      order[ido].productOrdered[i].id = idp;
      strcpy(order[ido].productOrdered[i].name, product[idp].name);
      order[ido].productOrdered[i].qty = qty;
      /* Adicionar uma unidade ao numero de produtos da encomenda. */
      order[ido].productsNumber++; 
    }
    /* Atualizar o peso da encomenda. */
    order[ido].totalWeight += product[idp].weight * qty;
    /* Atualizar o stock do produto no sistema. */
    product[idp].stock -= qty;
  }
}

/* Funcao para processar o comando 'r'. */
void comando_r() {
  int idp, qty;

  scanf(" %d%*c%d", &idp, &qty);
  if (idp >= productsNumber)
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  else if (qty > product[idp].stock)
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",
	   qty, idp);
  else
    /* Atualizar o stock do produto no sistema. */
    product[idp].stock -= qty;
}

/* Funcao para processar o comando 'R'. */
void comando_R() {
  int ido, idp;

  scanf(" %d%*c%d", &ido, &idp);
  if (ido >= ordersNumber)
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",
	   idp, ido);
  else if (idp >= productsNumber)
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",
	   idp, ido);
  else 
    /* Remover o produto do vetor de produtos da encomenda e atualizar os dados ... */
    remove_product(ido, idp);
}

/* Funcao para processar o comando 'C'. */
void comando_C() {
  int ido;

  scanf(" %d", &ido);
  if (ido >= ordersNumber)
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ido);
  else
    printf("Custo da encomenda %d %d.\n", ido, evaluate_order_price(ido));
}

/* Funcao para processar o comando 'p'. */
void comando_p() {
  int idp, price;

  scanf(" %d%*c%d", &idp, &price);
  if (idp >= productsNumber)
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  else
    product[idp].price = price;
}

/* Funcao para processar o comando 'E'. */
void comando_E() {
  int ido, idp, i;

  scanf(" %d%*c%d", &ido, &idp);
  if (ido >= ordersNumber)
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
  else if (idp >= productsNumber)
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  else {
    /* Comeca-se por procurar o produto na encomenda. */
    i = find_product(ido, idp);
    /* Se o produto existir na encomenda ... */
    if (i < order[ido].productsNumber)
      printf("%s %d.\n", order[ido].productOrdered[i].name,
	     order[ido].productOrdered[i].qty);
    /* Se o produto nao existir na encomenda ... */
    else
      printf("%s 0.\n", product[idp].name);
  }
}

/* Funcao para processar o comando 'm'. */
void comando_m() {
  int i, idp, maxProductQuantity = 0, maxIDOrder = -1;

  scanf(" %d", &idp);
  if (idp >= productsNumber)
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  /* O produto existe no sistema. */
  else
    /* Como os vetores com os produtos das encomendas nao estao ordenados, temos de os percorrer
       de forma linear ate encontrar o produto dado. */
    for (i = 0; i < ordersNumber; i++) {
      /* Comeca-se por procurar o produto na encomenda. */
      int j = find_product(i, idp);
      /* Se o produto existe na encomenda ...*/
      if (j < order[i].productsNumber)
	if (order[i].productOrdered[j].qty > maxProductQuantity) {
	  maxProductQuantity = order[i].productOrdered[j].qty;
	  maxIDOrder = i;
	}
    }
  /* Se ha encomendas e o produto ocorre em pelo menos uma delas ... */
  if (maxIDOrder != -1)
    printf("Maximo produto %d %d %d.\n", idp, maxIDOrder, maxProductQuantity);
}

/* Funcao para processar o comando 'l'. */
void comando_l() {
  int indP[MAX_PRODUCTS_NUMBER], i;

  /* Preencher o vetor auxiliar de indices de produtos, 'indP', para comparacao indireta.
   * 'indP' vai conter os indices dos produtos ordenados, de acordo com a funcao de
   * comparacao 'pcmp'. Na pratica, vamos estar a ordenar os indices do vetor de produtos.
   */ 
  for (i = 0; i < productsNumber; i++)
    indP[i] = i;

  /* Ordenar com base na funcao pcmp que implementa os criterios de comparacao. */
  quicksort(indP, 0, productsNumber - 1, pcmp);

  /* Imprimir os produtos ordenados. Notar  o acesso indireto ao vetor com os produtos. */
  printf("Produtos\n");
  for (i = 0; i < productsNumber; i++)
    printf("* %s %d %d\n", product[indP[i]].name, product[indP[i]].price,
	   product[indP[i]].stock);
}

/* Funcao para processar o comando 'L'. */
void comando_L() {
  
  scanf(" %d", &idOrder);
  if (idOrder >= ordersNumber)
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idOrder);
  else { /* A encomenda existe... */
    int indPO[MAX_PRODUCTS_NUMBER], i;

  /* Preencher o vetor auxiliar de indices de produtos da encomenda, 'indPO', para comparacao 
   * indireta. 'indPO' vai conter os indices dos produtos da encomenda ordenados, de acordo 
   * com a funcao de comparacao 'pocmp'. Na pratica, vamos estar a ordenar os indices do vetor 
   * de produtos da encomenda.
   */ 
  for (i = 0; i < productsNumber; i++)
   indPO[i] = i;

  /* Ordenar com base na funcao pocmp que implementa os criterios de comparacao. */
  quicksort(indPO, 0, order[idOrder].productsNumber - 1, pocmp);

  /* Imprimir os produtos da encomenda ordenados. Notar  o acesso indireto ao vetor com 
   * os produtos da encomenda. */
  printf("Encomenda %d\n", idOrder);
  for (i = 0; i < order[idOrder].productsNumber; i++)
    printf("* %s %d %d\n", order[idOrder].productOrdered[indPO[i]].name,
	   product[order[idOrder].productOrdered[indPO[i]].id].price,
	   order[idOrder].productOrdered[indPO[i]].qty);
  }
}

/** 
 * Funcao para procurar um produto numa encomenda.
 * Se o valor de retorno for maior ou igual ao numero de produtos da encomenda, 
 * entao o produto indicado nao existe na encomenda.
*/
int find_product(int ido, int idp) {
  int i;

  /* Como o vetor de produtos da encomenda nao esta ordenado, vamos ter de o 
   * percorrer de forma linear, eventualmente, ate ao fim. */
  for (i = 0; i < order[ido].productsNumber; i++)
    if (order[ido].productOrdered[i].id == idp) /* O produto existe na encomenda. */
      break;
  return i;
}

/** 
* Funcao para remover um produto de uma encomenda .
* Por forma a manter as posicoes ocupadas de forma contigua, i.e., sem buracos, 
* sempre que removemos um produto do vetor de produtos da encomenda em 
* questao, vamos copiar o elemento na ultima posicao para a posicao que fica livre. 
* A copia ocorre campo a campo, em particular temos de utilizar o strcpy para 
* copiar a descricao do produto.
*/
void remove_product(int ido, int idp) {
  int i = 0;

  /* Comecar por procurar o produto na encomenda. */
  i = find_product(ido, idp);
    /* Se o produto existir na encomenda ... */
  if (i < order[ido].productsNumber) {
    /* Atualizar o peso da encomenda. */
    order[ido].totalWeight -=
	product[idp].weight * order[ido].productOrdered[i].qty;
      /* Atualizar o stock do produto no sistema. */
      product[idp].stock += order[ido].productOrdered[i].qty;
      /* Copiar dados do produto na ultima posicao do vetor de produtos da encomenda, 
       * caso i nao seja a ultima posicao. */
      /* Comecamos por reduzir  o numero de produtos, i.e., descartar a ultima posicao
       * do vetor de produtos da encomenda. */
      order[ido].productsNumber--;
      if (i != order[ido].productsNumber) {
	order[ido].productOrdered[i].id =
	  order[ido].productOrdered[order[ido].productsNumber].id;
	strcpy(order[ido].productOrdered[i].name,
	       order[ido].productOrdered[order[ido].productsNumber].name);
	order[ido].productOrdered[i].qty =
	  order[ido].productOrdered[order[ido].productsNumber].qty;
      }
  }
}

/**
 * Funcao para calcular o custo de uma encomenda.
 */
int evaluate_order_price(int ido) {
  int i, price = 0;

  for (i = 0; i < order[ido].productsNumber; i++)
    price += product[order[ido].productOrdered[i].id].price *
      order[ido].productOrdered[i].qty;
  return price;
}

/**
 * Funcao para ordenar por ordem ascendente um vetor v[left] ... v[right], 
 * de acordo com a funcao cmp.
 * A funcao cmp deve retornar um valor negativo se o seu primeiro argumento for 
 * menor que o segundo, zero se forem iguais e um valor positivo se for maior. 
 */
void quicksort(int v[], int left, int right, int cmp(int , int )) {
  int i, last;

  /* Nao faz nada se o vetor tiver menos que dois elementos. */
  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (cmp (v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  quicksort(v, left, last - 1, cmp);
  quicksort(v, last + 1, right, cmp);
}

/**
 * Funcao para trocar v[i] com v[j].
 */
void swap(int v[], int i, int j) {
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/**
 * Funcao de comparacao para produtos, ordenados por ordem crescente de preco.
 * Se existirem dois ou mais produtos com o mesmo preco, ordena por ordem crescente
 * de identificador, i.e., respeita a ordem de introducao no sistema.
 *
 *  Devolve 0 se os produtos tiverem o mesmo preco e o mesmo identificador, -1 se o 
 * primeiro produto tiver um preco inferior ao segundo, ou sendo os precos iguais, se o 
 * identificador do primeiro for menor do que o do segundo, 1 caso contrario. 
*/
int pcmp(int pa, int pb) {
 
  /* Comparar pelos precos. */
  if (product[pa].price < product[pb].price)
    return -1;

  else if (product[pa].price > product[pb].price)
    return 1;
  else
    /*  Os produtos tem o mesmo preco, comparar identificadores*/
    return pa - pb;
}

/**
 * Funcao de comparacao para produtos de uma encomenda, ordenados por ordem
 * alfabetica da sua descricao.
 *
 *  Devolve 0 se os produtos da encomenda tiverem a mesma descricao, -1 se o primeiro 
 * produto tiver uma descricao lexicograficamente inferior ao segundo, 1 caso contrario. 
*/

int pocmp(int poa, int pob) {

  /* Comparar pela ordem lexicografica. */
  if (strcmp(order[idOrder].productOrdered[poa].name, order[idOrder].productOrdered[pob].name)  < 0)
    return -1;
  else if (strcmp(order[idOrder].productOrdered[poa].name, order[idOrder].productOrdered[pob].name)  > 0)
    return 1;
  else
    return 0;
}
