#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* -----------DEFINIR VALORES E OPECOES BASICAS ----------*/
#define MAXPRODUCTS 100000
#define MAXORDERS 500
#define MAXCHAR 64
#define MAXLINE 250
#define exch(A,X) {int t = A; A=X; X=t;}
#define exch_prod(A,X) {Product t = A; A=X; X=t;}


/*-------ESTRUTURAS USADAS PARA DEFINIR UM PRODUTO E UMA ENCOMENDA----------*/
typedef struct {
  int id;
  char descr[MAXCHAR];
  int price;
  int weight;
  int stock;
} Product;


typedef struct {
  int weight;
  int n_products;
  int products[1000]; /*Vetor com os produtos e a quantidade que t?m na encomenda.*/
  int prod_qnt[1000]; /*o valor de prod_qnt[i] esta sempre associado a products[i].*/
  int order_sort;
} Order;


Product product[MAXPRODUCTS];
Order order[MAXORDERS];

/*---------VARIAVEIS GLOBAIS---------------*/
int n_prod = 0;
int n_order = 0;
int prod_sort=0;
char input[5][MAXCHAR];


/*Declaracao das funcoes*/
void process_input(char buffer[MAXLINE]);
int lookfor(int id);
void merges_prod(int left, int right);
void mg_prod(int left, int m, int right);
void quick_sort(int o_id, int left, int right);
int partition(int o_id, int left, int right);

void a();
void q();
void r();
void p();
void N();
void A();
void R();
void C();
void E();
void m();
void l();
void L();
void k();
void K();

/*----------------FUNCOES AUXILIARES-------------------------*/
/*Process input
Recebe a linha do input e guarda no vetor input(variavel global).
Divide a linha atraves de espacos, dois pontos ou fim da linha(\n) e copia incrementalmente para o vetor*/
void process_input(char buffer[MAXLINE]){
  char* token;
  int i=1;
  token = strtok(buffer, "' '\n");
  strcpy(input[0], token);
  while((token = strtok(NULL, ":\n")) != NULL){
    strcpy(input[i], token);
    i++;
  }
}

/* Funcao auxiliar para encontrar o indice do produto id, na tabela product*/
int lookfor(int id){
  int i;
  for(i=0; i< n_prod; i++){
    if(id == product[i].id)
      return i;
  }
  return -1;
}

/*-----------------------------------------------------------------------*/


int main(){
  char buffer[MAXLINE];
  fgets(buffer,MAXLINE,stdin);
  process_input(buffer);
  while(atoi(input[0]) != EOF){
    switch(buffer[0]){
      case 'a': a(); break;
      case 'q': q(); break;
      case 'k': k(); break;
      case 'r': r(); break;
      case 'p': p(); break;
      case 'N': N(); break;
      case 'A': A(); break;
      case 'K': K(); break;
      case 'R': R(); break;
      case 'C': C(); break;
      case 'E': E(); break;
      case 'm': m(); break;
      case 'l': l(); break;
      case 'L': L(); break;
      case 'x':
          return 0;
    }
    fgets(buffer,MAXLINE,stdin);
    process_input(buffer);
  }
  return 0;
}


/*-------------Funcao a-----------
Adiciona produtos
Recebe os valores a partir do vetor "input" e guarda na posicao do numero de
  produtos existente. Incrementa de seguida este valor.*/
void a(){
  product[n_prod].id = n_prod;
  strcpy(product[n_prod].descr, input[1]);
  product[n_prod].price = atoi(input[2]);;
  product[n_prod].weight = atoi(input[3]);
  product[n_prod].stock = atoi(input[4]);

  printf("Novo produto %d.\n", n_prod);
  prod_sort = 0;
  n_prod++;
}

/*----------Funcao q-----------------
Altera stock de produtos
Verifica se existe o produto e em caso positivo, incrementa o stock*/
void q(){
  int i,id;
  id = atoi(input[1]);
  if(id >= n_prod){
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
  }
  else{
    i = lookfor(id);
    product[i].stock+= atoi(input[2]);
  }
}


/*----------Funcao r-----------------
Altera stock de produtos
Verifica se existe o produto e em caso positivo, decrementa o stock se o valor
a retirar nao for maior do que o existente.
*/
void r(){
  int i,id,qnt;
  id = atoi(input[1]);
  qnt = atoi(input[2]);
  if(id >= n_prod){
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
  }
  else{
    i = lookfor(id);
    if(product[i].stock >= qnt){
      product[i].stock -= qnt;
    }
    else{
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qnt, id);
    }
  }
}



/*----------Funcao p-----------------
Altera preco de produto
Verifica se existe o produto e em caso positivo, altera o preco do produto para o novo valor
*/
void p(){
  int i,id;
  id = atoi(input[1]);
  if(id >= n_prod)
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
  else{
    i = lookfor(id);
    product[i].price = atoi(input[2]);
  }
  prod_sort =0;
}


/*----------Funcao N-----------------
Cria nova encomenda.
Coloca os valores da estrutura a 0. Incrementa o numero de encomendas.
*/
void N(){
  order[n_order].weight = 0;
  order[n_order].n_products = 0;
  order[n_order].order_sort = 0;
  printf("Nova encomenda %d.\n", n_order);
  n_order++;
}

/*----------Funcao A----------------
Adiciona produto a encomenda
Verifica se existe o produto e a encomenda existem.
Se o produto ja estiver na encomenda, adiciona stock, senao adiciona o produto a encomenda
e a respetiva quantidade
*/
void A(){
  int i,j,o_id,id,qnt,flag=1;
  o_id = atoi(input[1]);
  id = atoi(input[2]);
  qnt = atoi(input[3]);


  if(o_id >= n_order){
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id, o_id);}
  else{
    if(id >= n_prod){
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id, o_id);
    }
    else{
      j = lookfor(id);
      if(qnt>product[j].stock){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id, o_id);
      }
      else{
        if((qnt*product[j].weight + order[o_id].weight) > 200){
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id, o_id);
        }
        else{
          for(i=0; i < order[o_id].n_products; i++){
              if(order[o_id].products[i] == id){
                order[o_id].weight += qnt*product[j].weight;
                order[o_id].prod_qnt[i] += qnt;
                flag = 0;
                break;
              }
          }
          if(flag){
            order[o_id].products[order[o_id].n_products] = id;
            order[o_id].weight += qnt*product[j].weight;
            order[o_id].prod_qnt[order[o_id].n_products] = qnt;
            order[o_id].n_products++;
          }
          product[j].stock -= qnt;
          order[o_id].order_sort = 0;
        }
      }
    }
  }
}

/*----------Funcao R-----------------
Remove produto de encomenda
Verifica se existe o produto e a encomenda e em caso positivo, remove o produto da encomenda
Incrementa o stock do produto a retirar com a quantidade que este tinha na encomenda
*/
void R(){
  int i,id,o_id, pos_prod;
  o_id = atoi(input[1]);
  id = atoi(input[2]);


  if(o_id >= n_order)
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id, o_id);

  else{
    if(id >= n_prod)
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id, o_id);

    for(i=0;i < order[o_id].n_products;i++){
      if(id == order[o_id].products[i]){
        pos_prod = lookfor(id);
        product[pos_prod].stock += order[o_id].prod_qnt[i];
        order[o_id].weight -= product[pos_prod].weight*order[o_id].prod_qnt[i];
        order[o_id].products[i] = order[o_id].products[order[o_id].n_products -1];    /*Troca-se de posicao com o ultimo produto na encomenda*/
        order[o_id].prod_qnt[i] = order[o_id].prod_qnt[order[o_id].n_products - 1];   /*Igual para as quantidades para que a relacao produto-quantidade se mantenha*/
        order[o_id].n_products--;
        order[o_id].order_sort = 0;
        break;
      }
    }
  }
}

/*----------Funcao C-----------------
Calcula preco de encomenda
Verifica se existe a encomenda existe e em caso positivo, procura cada produto na tabela product de forma
a econtrar o preco de cada produto ao qual se multiplica pela quantidade na encomenda e incrementa ? vari?vel da funcao "price"
*/
void C(){
  int i,price=0,id,o_id;
  o_id = atoi(input[1]);
  if(o_id >= n_order)
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", o_id);
  else{
    for(i=0; i < order[o_id].n_products; i++){
      id= lookfor(order[o_id].products[i]);
      price += product[id].price*order[o_id].prod_qnt[i];
    }
    printf("Custo da encomenda %d %d.\n", o_id, price);
  }

}

/*----------Funcao E-----------------
Lista produto da encomenda
Verifica se existe o produto e a encomenda existem e em caso positivo, percorre a encomenda para encontrar
a quantidade e procura o produto para obter a descricao.
*/
void E(){
  int i, o_id, id,real_id,qnt=0;
  o_id = atoi(input[1]);
  id = atoi(input[2]);
  real_id = lookfor(id);
  if(o_id >= n_order)
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
  else{
    if(id >= n_prod)
      printf("Impossivel listar produto %d. Produto inexistente.\n", id);
    else{
      for(i=0;i< order[o_id].n_products; i++){
        if(id == order[o_id].products[i]){
          qnt = order[o_id].prod_qnt[i];
          break;
        }
      }
      printf("%s %d.\n", product[real_id].descr, qnt);
    }
  }
}

/*----------Funcao m-----------------
Lista m?ximo de um produto
Percorre todas as encomendas, comparando a quantidade desse produto na encomenda
com a variavel "qnt" de forma a obter a encomenda em que aparece com maior quantidade
*/
void m(){
  int i,j,id, qnt=-1, o_id=-1;
  id = atoi(input[1]);
  if(id >= n_prod)
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id);
  else{
    for(i=0;i<n_order;i++){
      for(j=0;j<order[i].n_products;j++){
        if(id == order[i].products[j]){
          if(order[i].prod_qnt[j] > qnt){
            qnt = order[i].prod_qnt[j];
            o_id = i;
            break;
          }
        }
      }
    }
    if(qnt>0)
      printf("Maximo produto %d %d %d.\n", id, o_id, qnt);

  }
}

/*----------Funcao l-----------------
Lista os produtos ordenados pelo pre?o
Caso a flag prod_sort esteja a 0, usa o algoritmo merge sort para ordenar e de
seguida faz print dos produtos
*/
void l(){
  int i;
  if(!prod_sort){
    merges_prod(0,n_prod-1);
    prod_sort = 1;
  }

  printf("Produtos\n");
  for(i=0;i<n_prod;i++){
  printf("* %s %d %d\n", product[i].descr, product[i].price, product[i].stock);
  }
}

void L(){
  int i,p1,o_id;
  o_id = atoi(input[1]);

  if(o_id >= n_order)
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);

  else{
    if(!order[o_id].order_sort){
      quick_sort(o_id,0,order[o_id].n_products-1);
      order[o_id].order_sort = 1;
    }

    printf("Encomenda %d\n", o_id);
    for(i=0;i<order[o_id].n_products;i++){
      p1 = lookfor(order[o_id].products[i]);
      printf("* %s %d %d\n", product[p1].descr, product[p1].price, order[o_id].prod_qnt[i]);
    }
  }
}



void k(){
  int i;
  for(i=0; i < n_prod; i++){
    printf("Produto %s com preco %d, peso %d, stock %d\n", product[i].descr, product[i].price, product[i].weight, product[i].stock);
  }
}


void K(){
  int i,j;
  for(i=0; i < n_order; i++){
    printf("* Encomenda id: %d, numero produtos: %d, peso: %d\n", i, order[i].n_products, order[i].weight);
    for(j=0; j<order[i].n_products; j++){
      printf("* Produto: %d\n", order[i].products[j]);
    }
  }
}


/*------------Merge Sort----------
Ordena a tabela de produtos atraves do pre?o
*/
void merges_prod(int left, int right){
  int m = (right+left)/2;
  if (right <= left) return;
  merges_prod(left, m);
  merges_prod(m+1, right);
  mg_prod(left, m, right);
}

void mg_prod(int left, int m, int right){
  Product* aux;
  int i, j, k;
  aux = malloc(sizeof(Product)*n_prod);
  for (i = m+1; i > left; i--)
    aux[i-1] = product[i-1];
  for (j = m; j < right; j++)
    aux[right+m-j] = product[j+1];
  for (k = left; k <= right; k++){
    if (aux[j].price < aux[i].price){
      product[k] = aux[j--];
    }
    else if(aux[j].price == aux[i].price){
      if(aux[j].id < aux[i].id){
        product[k] = aux[j--];
      }
      else{
        product[k] = aux[i++];
      }
    }
    else{
      product[k] = aux[i++];
    }
  }
  free(aux);
}



/*---------QUICK SORT----------
Ordena o vetor de produtos de uma dada encomenda e o respetiva tabela
de quantidades de produto na encomenda*/
void quick_sort(int o_id, int left, int right){
  int m;

  if (left<right){
    m = partition(o_id, left, right);
    quick_sort(o_id, left, m-1);
    quick_sort(o_id, m+1, right);
  }
}

int partition(int o_id, int left, int right){
  int i = left, j, id;
  int id_r = lookfor(order[o_id].products[right]);

  for (j=left; j<right; j++){
    id = lookfor(order[o_id].products[j]);
    if (strcmp(product[id].descr, product[id_r].descr)<0){
      exch(order[o_id].products[i], order[o_id].products[j]);
      exch(order[o_id].prod_qnt[i], order[o_id].prod_qnt[j]);
      i++;
    }
  }
  exch(order[o_id].products[i], order[o_id].products[right]);
  exch(order[o_id].prod_qnt[i], order[o_id].prod_qnt[right]);
  return i;
}
