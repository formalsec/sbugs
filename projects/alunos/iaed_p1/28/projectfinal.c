#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#define MAXPRODUCTS 10000
#define MAXORDERS 500
#define MAXCHAR 64
#define MAXWEIGHT 200
#define STR 200

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*______ESTRUTURAS______*/
/*Produto.*/
typedef struct product{
  int id; /*identificador*/
  char desc[MAXCHAR]; /*descri??o*/
  int price; /*pre?o*/
  int weight; /*peso*/
  int stock; /*quantidade em stock*/
} Product;

/*Encomenda.*/
typedef struct order{
  int products[MAXORDERS]; /*vetor de IDs dos produtos que constituem a encomenda*/
  int quantProducts[MAXORDERS]; /*vetor com o stock do produto, cujo ID se encontra na mesma posi??o do vetor products */
  int weight; /*peso total da encomenda*/
  int numProducts; /*numero de produtos da encomenda*/
  int productsSorted; /*/*flag que indica se o vetor products est? ordenado ou
  n?o, caso esteja, respetivamente a 1 ou 0*/
} Orders;

/*______VARIAVEIS GLOBAIS______*/
Product productsList[MAXPRODUCTS]; /*vetor que guarda os produtos do sistema*/
Orders ordersList[MAXORDERS]; /*vetor que guarda as encomendas do sistema*/
int nProducts = 0; /*contador do numero de produtos do sistema*/
int nOrders = 0; /*contador do numero de encomendas do sistema*/
int priceSorted = 0; /*flag que indica se o vetor productsList est?
ordenado ou n?o, caso esteja, respetivamente a 1 ou 0*/

/*______PROTOTIPOS______*/
int getProductsListPosition(int id);
int getOrdersListPosition(int ide, int idp);
void ordersMerge(int ide, int l, int m, int r);
void ordersMergeSort(int ide, int l, int r);
void productsMerge(int l, int m, int r);
void productsMergeSort(int l, int r);
void fa(char c[]);
void fq(char c[]);
void fN();
void fA(char c[]);
void fr(char c[]);
void fR(char c[]);
void fC(char c[]);
void fp(char c[]);
void fE(char c[]);
void fm(char c[]);
void fl();
void fL(char c[]);


int main(){
   int c;
  char buffer[STR];
  /*processamento do input*/
  while((c=getchar()) != EOF){
    getchar();
    switch(c){
      case 'a': (fgets(buffer,STR,stdin)); fa(buffer); break;
      case 'q': (fgets(buffer,STR,stdin)); fq(buffer); break;
      case 'N':  fN(); break;
      case 'A': (fgets(buffer,STR,stdin)); fA(buffer); break;
      case 'r': (fgets(buffer,STR,stdin)); fr(buffer); break;
      case 'R': (fgets(buffer,STR,stdin)); fR(buffer); break;
      case 'C': (fgets(buffer,STR,stdin)); fC(buffer); break;
      case 'p': (fgets(buffer,STR,stdin)); fp(buffer); break;
      case 'E': (fgets(buffer,STR,stdin)); fE(buffer); break;
      case 'm': (fgets(buffer,STR,stdin)); fm(buffer); break;
      case 'l':  fl(); break;
      case 'L': (fgets(buffer,STR,stdin)); fL(buffer); break;
      case 'x':
          return 0;
    }
  }
  return 0;
}


/*______FUNCOES AUXILIARES______*/
/*Retorna a posicao, no vetor productsList, do produto de identificador, id.
Retorna -1 casoo produto nao esteja no vetor*/
int getProductsListPosition(int id){
  int i;

  for (i=0; i<nProducts; i++){
    if (productsList[i].id == id){
      return i;
    }
  }
  return -1;
}

/*Retorna a posicao, no vetor products da encomenda de identificador ide,
do produto de identificador, id. Retorna -1 caso o produto nao esteja no vetor*/
int getOrdersListPosition(int ide, int idp){
  int i;

  for (i=0; i<ordersList[ide].numProducts; i++){
    if (ordersList[ide].products[i] == idp){
      return i;
    }
  }
  return -1;
}

/*As fun??es ordersMerge e ordersMergeSort s?o responsaveis, atrav?s do
algoritmo merge sort, pela ordena??o, do vetor products e, consequentemente,
do vetor quantProducts, da encomenda de identificador ide,
por ordem alfabetica da descricao dos produtos.*/
void ordersMerge(int ide, int l, int m, int r){
  int* auxIDs;
  int* auxQuants;
  int i, j, k, indexI, indexJ;

  auxIDs = can_fail_malloc(sizeof(int)*ordersList[ide].numProducts);
  auxQuants = can_fail_malloc(sizeof(int)*ordersList[ide].numProducts);

  for(i=m+1; i>l; i--){
    auxIDs[i-1] = ordersList[ide].products[i-1];
    auxQuants[i-1] = ordersList[ide].quantProducts[i-1];
  }
  for(j=m; j<r; j++){
    auxIDs[r+m-j] = ordersList[ide].products[j+1];
    auxQuants[r+m-j] = ordersList[ide].quantProducts[j+1];
  }
  for(k=l; k<=r; k++){
    indexI = getProductsListPosition(auxIDs[i]);
    indexJ = getProductsListPosition(auxIDs[j]);
    if(strcmp(productsList[indexJ].desc, productsList[indexI].desc) < 0){
      ordersList[ide].products[k] = auxIDs[j];
      ordersList[ide].quantProducts[k] = auxQuants[j--];
    }
    else{
      ordersList[ide].products[k] = auxIDs[i];
      ordersList[ide].quantProducts[k] = auxQuants[i++];
    }
  }
  free(auxIDs);
  free(auxQuants);
}

void ordersMergeSort(int ide, int l, int r){
  int m = (r+l)/2;
  if (r<=l){
    return;
  }
  ordersMergeSort(ide, l, m);
  ordersMergeSort(ide, m+1, r);
  ordersMerge(ide, l, m, r);
}

/*As fun??es productsMerge e productsMergeSort s?o responsaveis, atrav?s do
algoritmo merge sort, pela ordena??o do vetor productsList por ordem crescente
de pre?o dos produtos e, caso estes sejam iguais, por ordem crescente de id.*/
void productsMerge(int l, int m, int r){
  Product* aux;
  int i, j, k;

  aux = can_fail_malloc(sizeof(Product)*nProducts);
  for(i=m+1; i>l; i--){
    aux[i-1] = productsList[i-1];
  }
  for(j=m; j<r; j++){
    aux[r+m-j] = productsList[j+1];
  }
  for(k=l; k<=r; k++){
    if(aux[j].price < aux[i].price){
      productsList[k] = aux[j--];
    }
    else if(aux[j].price == aux[i].price){
      if(aux[j].id < aux[i].id){
        productsList[k] = aux[j--];
      }
      else{
        productsList[k] = aux[i++];
      }
    }
    else{
      productsList[k] = aux[i++];
    }
  }
  free(aux);
}

void productsMergeSort(int l, int r){
  int m = (r+l)/2;
  if (r<=l){
    return;
  }
  productsMergeSort(l, m);
  productsMergeSort(m+1, r);
  productsMerge(l, m, r);
}

/*______FUNCOES PRINCIPAIS______*/
/*NOTA: Se a fun??o gerar mais do que um erro, apenas ? impresso o primeiro.*/

/*Adiciona um produto ao sistema*/
void fa(char c[]){
  char * token;

  token = strtok(c, ":");
  strcpy(productsList[nProducts].desc, token);

  token = strtok(NULL, ":");
  productsList[nProducts].price = atoi(token);

  token = strtok(NULL, ":");
  productsList[nProducts].weight = atoi(token);

  token = strtok(NULL, "\n");
  productsList[nProducts].stock = atoi(token);

  productsList[nProducts].id = nProducts;

  printf("Novo produto %d.\n", nProducts);
  nProducts++;
  priceSorted = 0;
}

/*Adiciona stock a um produto, idp, existente no sistema.
Imprime um erro caso o produto n?o exista.*/
void fq(char c[]){
  char * token;
  int idp, qnt, index;

  token = strtok(c, ":");
  idp = atoi(token);

  token = strtok(NULL, "\n");
  qnt = atoi(token);

  if (idp < nProducts){
    index = getProductsListPosition(idp);
    productsList[index].stock += qnt;
  }
  else{
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
  }
}

/*Cria uma nova encomenda.*/
void fN(){
  printf("Nova encomenda %d.\n", nOrders);
  nOrders++;
}

/*Adiciona um produto, idp, de stock qtd, a uma encomenda, ide.
Os erros possiveis s?o: a encomenda ide n?o existe, o produto idp n?o existe
e a quantidade qtd em stock do produto idp n?o ? suficiente.*/
void fA(char c[]){
  char * token;
  int ide, idp, qtd, indexP, indexO;
  token = strtok(c, ":");
  ide = atoi(token);

  token = strtok(NULL, ":");
  idp = atoi(token);

  token = strtok(NULL, "\n");
  qtd = atoi(token);

  indexP = getProductsListPosition(idp);
  if (ide < nOrders){
    if (idp < nProducts){
      if (qtd > productsList[indexP].stock){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else{
        if (ordersList[ide].weight + qtd*productsList[indexP].weight <= MAXWEIGHT){
          ordersList[ide].weight += qtd*productsList[indexP].weight;
          productsList[indexP].stock -= qtd;
          indexO = getOrdersListPosition(ide, idp);
          if (indexO == -1){
            ordersList[ide].products[ordersList[ide].numProducts] = idp;
            ordersList[ide].quantProducts[ordersList[ide].numProducts] = qtd;
            ordersList[ide].numProducts++;
          }
          else {
            ordersList[ide].quantProducts[indexO] += qtd;
          }
          ordersList[ide].productsSorted = 0;

        }
        else printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
      }
    }
    else printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  }
  else printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/*Remove stock, qtd, a um produto, idp, existente. Caso o produto idp n?o exista no
sistema, caso a quantidade, qtd, seja insuficiente, s?o impressos os erros respetivos.*/
void fr(char c[]){
  char * token;
  int idp, qtd, index;

  token = strtok(c, ":");
  idp = atoi(token);

  token = strtok(NULL, "\n");
  qtd = atoi(token);

  if (idp < nProducts){
    index = getProductsListPosition(idp);
    if (qtd > productsList[index].stock){
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else {
      productsList[index].stock -=qtd;
    }
  }
  else printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
}

/*Remove o produto, idp, da encomenda, ide. Os erros possiveis s?o a inexistencia,
quer da encomenda ide, quer do produto, idp.*/
void fR(char c[]){
  char * token;
  int ide, idp, indexO, indexP;

  token = strtok(c, ":");
  ide = atoi(token);

  token = strtok(NULL, "\n");
  idp = atoi(token);

  if (ide < nOrders){
    if (idp < nProducts){
      indexO = getOrdersListPosition(ide, idp);
      indexP = getProductsListPosition(idp);
      if (indexO != -1){
        productsList[indexP].stock += ordersList[ide].quantProducts[indexO];
        ordersList[ide].weight -= productsList[indexP].weight*ordersList[ide].quantProducts[indexO];
        ordersList[ide].numProducts--;
        ordersList[ide].products[indexO] = ordersList[ide].products[ordersList[ide].numProducts];
        ordersList[ide].quantProducts[indexO] = ordersList[ide].quantProducts[ordersList[ide].numProducts];
      }
      ordersList[ide].productsSorted = 0;
    }
    else printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  }
  else printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/*Calcula custo da encomenda, ide. Se a encomenda n?o existir, ? impresso um erro.*/
void fC(char c[]){
  char * token;
  int ide, total=0, i, index;

  token = strtok(c, "\n");
  ide = atoi(token);

  if (ide < nOrders){
    for (i=0; i<ordersList[ide].numProducts; i++){
      index = getProductsListPosition(ordersList[ide].products[i]);
      total += productsList[index].price*ordersList[ide].quantProducts[i];
    }
    printf("Custo da encomenda %d %d.\n", ide, total);
  }
  else printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
}

/*Altera o pre?o, newPrice, de um produto, idp. ? retornado um erro caso o
produto n?o exista.*/
void fp(char c[]){
  char * token;
  int idp, newPrice, index;

  token = strtok(c, ":");
  idp = atoi(token);

  token = strtok(NULL, "\n");
  newPrice = atoi(token);

  if (idp < nProducts){
    index = getProductsListPosition(idp);
    productsList[index].price = newPrice;
    priceSorted = 0;
  }
  else printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
}

/*Imprime produto, idp, da encomenda, ide, e das caracteristicas do produto,
descri??o e quantidade na encomenda. Imprime um erro caso a encomenda ou o
produto n?o existam.*/
void fE(char c[]){
  char * token;
  int ide, idp, indexO, indexP;

  token = strtok(c, ":");
  ide = atoi(token);

  token = strtok(NULL, "\n");
  idp = atoi(token);

  if (ide < nOrders){
    if (idp < nProducts){
      indexO = getOrdersListPosition(ide, idp);
      indexP = getProductsListPosition(idp);
      printf("%s %d.\n", productsList[indexP].desc, ordersList[ide].quantProducts[indexO]);
    }
    else printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
  }
  else printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
}

/*Imprime o identificador da encomenda em que o produto dado ocorre mais vezes.
Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de
menor identificador. Devolve um erro se o produto, idp, n?o existir.*/
void fm(char c[]){
  char * token;
  int idp, max=0, ide, productIndex, i, index;
  token = strtok(c, "\n");
  idp = atoi(token);

  if (idp < nProducts){
    for (i=0; i<nOrders; i++){
      index = getOrdersListPosition(i, idp);
      if (ordersList[i].quantProducts[index] > max){
        max = ordersList[i].quantProducts[index];
        ide = i;
        productIndex = index;
      }
    }
    if (max != 0) printf("Maximo produto %d %d %d.\n",idp, ide, ordersList[ide].quantProducts[productIndex]);
  }
  else printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
}

/*Lista todos os produtos existentes no sistema por ordem crescente de pre?o.
Se houver 2 ou mais produtos com o mesmo pre?o, dever? imprimir esses por ordem
crescente de identificador de produto*/
void fl(){
  int i;

  if (priceSorted == 0){
    productsMergeSort(0, nProducts-1);
    priceSorted = 1;
  }
  printf("Produtos\n");
  for (i=0; i<nProducts; i++){
    printf("* %s %d %d\n", productsList[i].desc, productsList[i].price, productsList[i].stock);
  }
}

/*Lista todos os produtos da encomenda, ide, por ordem alfab?tica da descri??o.
Se a encomenda n?o existir, dever? imprimir um erro.*/
void fL(char c[]){
  char * token;
  int ide;
  int j, indexJ;
  token = strtok(c, "\n");
  ide = atoi(token);

  if (ide < nOrders){
    if (ordersList[ide].productsSorted == 0){
      ordersMergeSort(ide, 0, ordersList[ide].numProducts-1);
      ordersList[ide].productsSorted = 1;
    }
    printf("Encomenda %d\n", ide);
    for (j=0; j<ordersList[ide].numProducts; j++){
      indexJ = getProductsListPosition(ordersList[ide].products[j]);
      printf("* %s %d %d\n",productsList[indexJ].desc,productsList[indexJ].price, ordersList[ide].quantProducts[j]);
    }
  }
  else printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
}
