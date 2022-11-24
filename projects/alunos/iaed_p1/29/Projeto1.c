#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constantes */
#define MAX 100
#define MAXP 10000
#define MAXO 500

/* Estruturas */
typedef struct product{
  int id;
  char description[MAX];
  int price;
  int weight;
  int qtty;
} Product;

typedef struct order{
  int id;
  int weight;
  int numOrders;
  Product ordered[MAX];
} Order;

/* Variaveis Globais  */
Product products[MAXP]; /* Vetor que contem todos os produtos que sao criados */
Order orders[MAXO]; /* Vetor que contem todas as encomendas que sao criadas */
int numP= 0; /* Inteiro que indica o numero de produtos existentes no sistema */
int numO = 0; /* Inteiro que indica o numero de encomendas existentes no sistema */


/* Prototipos dos Comandos */
void comando_a(char* input);
void comando_q(char* input);
void comando_r(char* input);
void comando_p(char* input);
void comando_l();
void comando_N();
void comando_A(char* input);
void comando_R(char* input);
void comando_C(char* input);
void comando_E(char* input);

/* Prototipos das funcoes auxiliares */
void addOrder(int qtty, int orderID, int productID);
void removeOrder(int orderID, int productID);
void calculatePrice(int orderID);
void sortAlphabetic(Product* sortedArray, int max);
void mergesort(Product* sortedArray, int start, int end);
void merge(Product* array, int l, int m, int r);


/* Comandos */
void comando_a(char* input){
  Product newP;
  newP.id = numP;
  strcpy(newP.description,strtok(input,":"));
  newP.price = atoi(strtok(NULL,":"));
  newP.weight = atoi(strtok(NULL,":"));
  newP.qtty = atoi(strtok(NULL,":"));
  products[numP] = newP;
  printf("Novo produto %d.\n",numP);
}

void comando_q(char* input){
  int id, stock;
  id = atoi(strtok(input,":"));
  stock = atoi(strtok(NULL,""));
  if(id < 0 || id >= numP){
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
  }
  else{
    products[id].qtty += stock;
  }
}

void comando_r(char* input){
  int id, stock;
  id = atoi(strtok(input,":"));
  stock = atoi(strtok(NULL,""));
  if(id < 0 || id >= numP){
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
  }
  else if ( stock > products[id].qtty){
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",stock,id);
  }
  else{
    products[id].qtty -= stock;
  }
}

void comando_p(char* input){
  int id, newPrice;
  id = atoi(strtok(input,":"));
  newPrice = atoi(strtok(NULL,""));
  if(id < 0 || id >= numP){
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
  }
  else{
    products[id].price = newPrice;
  }
}

void comando_l(){
  int i;
  Product sortedArray[MAXP]; /* Vetor que vai ser posteriormente ordenado pelo preco de cada produto */
  for(i = 0; i < numP; i++){
    sortedArray[i] = products[i];
  }
  mergesort(sortedArray,0,numP-1);
  printf("Produtos\n");
  for(i = 0; i < numP; i++){
    printf("* %s %d %d\n",sortedArray[i].description,sortedArray[i].price, sortedArray[i].qtty);
  }
}

void comando_N(){
  Order newOrder;
  newOrder.id = numO;
  newOrder.weight = 0;
  newOrder.numOrders = 0;
  orders[numO] = newOrder;
  printf("Nova encomenda %d.\n",newOrder.id);
}

void comando_A(char* input){
  int productID, orderID, qtty;
  orderID = atoi(strtok(input,":"));
  productID = atoi(strtok(NULL,":"));
  qtty = atoi(strtok(NULL,""));
  if(orderID < 0 || orderID >= numO){
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",productID,orderID);
    return;
  }
  else if( productID < 0 || productID >= numP){
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",productID,orderID);
    return;
  }
  else if( products[productID].qtty < qtty){
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",productID,orderID);
    return;
  }
  else if( orders[orderID].weight + qtty * products[productID].weight > 200){
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",productID,orderID);
      return;
    }
  else{
    /* Se chegar aqui, quer dizer que podemos adicionar o produto a encomenda */
    addOrder(qtty, orderID ,productID);
    return;
  }
}

void comando_R(char* input){
  int productID, orderID;
  orderID = atoi(strtok(input,":"));
  productID = atoi(strtok(NULL,":"));
  if(orderID < 0 || orderID >= numO){
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",productID,orderID);
    return;
  }
  else if( productID < 0 || productID >= numP){
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",productID,orderID);
    return;
  }
  else{
    removeOrder(orderID,productID);
  }
}

void comando_C(char* input){
  int orderID ;
  orderID = atoi(input);
  if(orderID < 0 || orderID >= numO){
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",orderID);
    return;
  }
  else{
    calculatePrice(orderID);
  }
}

void comando_E(char* input   ){
  int productID, orderID, i;
  orderID = atoi(strtok(input,":"));
  productID = atoi(strtok(NULL,":"));
  if(orderID < 0 || orderID >= numO){
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",orderID);
    return;
  }
  else if( productID < 0 || productID >= numP){
    printf("Impossivel listar produto %d. Produto inexistente.\n",productID);
    return;
  }
  else{
    /* Ciclo for para procurar o produto na encomenda */
    for(i = 0; i < orders[orderID].numOrders; i++){
      if(orders[orderID].ordered[i].id == productID){
        printf("%s %d.\n",products[productID].description, orders[orderID].ordered[i].qtty);
        return;
      }
    }
    /* Se chegar aqui, e porque o produto nao se encontra na encomenda */
    printf("%s %d.\n",products[productID].description,0);
  }
}

void comando_m(char* input  ){
  int productID, i, j, orderID, max;
  productID = atoi(input);
  if( productID < 0 || productID >= numP){
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",productID);
    return;
  }
  if(numO == 0) return; /* Caso nao existam encomendas  */
  max = 0;
  orderID = 0;
  /* Duplo ciclo for para encontrar a encomenda onde o produto esta em maior quantidade,
  onde max fica com o valor da quantidade e orderID fica com o indice da encomenda */
  for(i = 0; i < numO; i++){
    for(j = 0; j < orders[i].numOrders; j++){
      if(orders[i].ordered[j].id == productID && orders[i].ordered[j].qtty > max ){
          max = orders[i].ordered[j].qtty;
          orderID = i;
      }
    }
  }
  /* Condicao para verificar se o produto existe em pelo menos uma encomenda com
   a quantidade diferente de zero */
  if (max == 0){
    return;
  }
  else{
    printf("Maximo produto %d %d %d.\n", productID , orderID, max);
  }
}


void comando_L(char* input   ){
  int orderID, i, j ,productID;
  Product sortedArray[MAXP];
  orderID = atoi(input);
  if(orderID < 0 || orderID >= numO){
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",orderID);
    return;
  }
  /* Criacao do vetor dos produtos que estao na encomenda com quantidade diferente de zero*/
  j = 0;
  for(i = 0; i < orders[orderID].numOrders; i++){
    if(orders[orderID].ordered[i].qtty != 0){
      sortedArray[j] = orders[orderID].ordered[i];
      j++;
    }
  }
  sortAlphabetic(sortedArray,j);
  /*alphaInsertionSort(sortedArray,j);*/
  printf("Encomenda %d\n",orderID);
  for(i = 0; i < j ; i++){
    productID = sortedArray[i].id;
    printf("* %s %d %d\n",products[productID].description, products[productID].price, sortedArray[i].qtty);
    }
}

void sortAlphabetic(Product* sortedArray,int max){
  int i, j;
  Product swap;
  for (i = 0; i < max; i++){
    for (j = 0; j < max; j++){
      if (strcmp(sortedArray[j].description,sortedArray[i].description) > 0){
        swap = sortedArray[i];
        sortedArray[i] = sortedArray[j];
        sortedArray[j] = swap;
      }
    }
  }
}

void calculatePrice(int orderID){
  int i, sum, price, qtty;
  sum = 0;
  price = 0;
  qtty = 0;
  for(i = 0; i < orders[orderID].numOrders; i++){
    price = products[orders[orderID].ordered[i].id].price;
    qtty = orders[orderID].ordered[i].qtty;
    sum +=  qtty * price;
  }
  printf("Custo da encomenda %d %d.\n",orderID,sum);
}

void addOrder( int qtty, int orderID, int productID){
  int i, peso;
  Product newProduct;
  /* Ciclo for para verificar se o produto ja foi colocado nesta encomenda (mesmo que ja tenha sido removido) */
  for(i = 0; i < orders[orderID].numOrders; i++){
    if(orders[orderID].ordered[i].id == products[productID].id){
      peso = products[productID].weight;
      orders[orderID].ordered[i].qtty += qtty;
      orders[orderID].weight += qtty * peso;
      products[productID].qtty -= qtty;
      return;
    }
  }
  /* Se chegar aqui, e porque ainda nao tinha sido colocado na encomenda */
  i = orders[orderID].numOrders;
  orders[orderID].numOrders++;
  newProduct.id = products[productID].id;
  newProduct.qtty = qtty;
  strcpy(newProduct.description,products[productID].description);
  orders[orderID].ordered[i] = newProduct;
  orders[orderID].weight += qtty * products[productID].weight;
  products[productID].qtty -= qtty;
  return;
}

/* O comando R vai apenas colocar a quantidade do produto na encomenda a zero, e todas as
implicacoes que ocorrerem dessa diminuicao de quantidade */
void removeOrder( int orderID, int productID){
  int i;
  for(i = 0; i < orders[orderID].numOrders; i++){
    if(orders[orderID].ordered[i].id == productID){
      products[productID].qtty += orders[orderID].ordered[i].qtty;
      orders[orderID].weight -=  orders[orderID].ordered[i].qtty * products[productID].weight;
      orders[orderID].ordered[i].qtty = 0;
      return;
    }
  }
}

void merge(Product* array, int l, int m, int r){
  int i, j, k;
  Product aux[MAXP];
  for (i = m+1; i > l; i--){
    aux[i-1] = array[i-1];
  }
  for (j = m; j < r; j++){
    aux[r+m-j] = array[j+1];
  }
  for (k = l; k <= r; k++){
    if (aux[j].price < aux[i].price){
      array[k] = aux[j--];
    }
    else{
      if(aux[j].id < aux[i].id && aux[j].price == aux[i].price){
        array[k] = aux[j--];
      }
      else{
        array[k] = aux[i++];
      }
    }
  }
}

void mergesort(Product* sortedArray, int start, int end){
	int m;
	if(start < end){
		m = (start + end)/2;
		mergesort(sortedArray, start, m);
		mergesort(sortedArray, m+1, end);
		merge(sortedArray, start, m, end);
	}
}

int main(){
  char control;
  char input[MAX];
  int end;
  end = 0;
  while(end == 0){
    scanf("%s",&control);
    switch (control) {
      case 'a':
        scanf("%s",input);
        comando_a(input);
        numP++;
        break;
      case 'q':
        scanf("%s",input);
        comando_q(input);
        break;
      case 'r':
        scanf("%s",input);
        comando_r(input);
        break;
      case 'p':
        scanf("%s",input);
        comando_p(input);
        break;
      case 'l':
        comando_l();
        break;
      case 'N':
        comando_N();
        numO++;
        break;
      case 'A':
        scanf("%s",input);
        comando_A(input);
        break;
      case 'R':
        scanf("%s",input);
        comando_R(input);
        break;
      case 'C':
        scanf("%s",input);
        comando_C(input);
        break;
      case 'E':
        scanf("%s",input);
        comando_E(input);
        break;
      case 'm':
        scanf("%s",input);
        comando_m(input);
        break;
      case 'L':
        scanf("%s",input);
        comando_L(input);
        break;
      case 'x':
        end = 1;
        break;
    }
  }
  return 0;
}
