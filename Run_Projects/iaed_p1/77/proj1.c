#include <stdio.h>
#include <string.h>

/* definir valores para limitar as variaveis */

#define MAX 10000
#define VECMAX 64
#define MAXENCOM 500
#define MAX_PESO_ENCOMENDA 200


/*inicializar variaveis que vao servir para identificar produtos e encomendas a
medida que sao criadoss*/

int cont_produto=0;
int cont_encomenda=0;

/* criar uma estrutura para produtos */

typedef struct produto{
  char descricao[VECMAX];
  int preco;
  int peso;
  int stock;
  int id;
} Produto;

/*inicializar o sistema, que sera um array de produtos */

Produto sistema[MAX];

/*inicializar as encomendas, que funcionarao em tabelas bidimensionais, onde
cada coluna sera uma encomenda e as linhas corresponderao ao produto*/

Produto encomendas[MAXENCOM][MAX];


/*funcao para comando 'a', adiciona um novo produto ao sistema */

void adiciona_produto(char descricao[],int preco,int peso,int stock){
  strcpy(sistema[cont_produto].descricao, descricao);
  sistema[cont_produto].preco = preco;
  sistema[cont_produto].peso = peso;
  sistema[cont_produto].stock = stock;
  sistema[cont_produto].id = cont_produto;
  printf("Novo produto %d.\n",cont_produto);
  cont_produto++;
}

/*funcao pra comando q, adiciona stock a um produto existente no sistema*/

void adiciona_stock(int idp,int stock){
  /* verifica se o idp eh maior que a contagem que indica a quantidade de produtos diferentes*/
  if (idp>=cont_produto){
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
  }
  else{
    sistema[idp].stock = sistema[idp].stock + stock;
  }
}

/*funcao para comando N, cria uma nova encomenda*/

void cria_encomenda(){
  printf("Nova encomenda %d.\n",cont_encomenda);
  cont_encomenda++;
}


/*funcao para comando A, adiciona produto a uma encomenda*/

void adiciona_produto_encomenda(int ide,int idp,int stock){
  int i,peso_total=0;
  /* calcular o peso atual na encomenda*/
  for (i=0;i<cont_produto;i++){
    peso_total += encomendas[ide][i].peso * encomendas[ide][i].stock;
  }
  peso_total += sistema[idp].peso * stock;

  /*verificar se existem erros*/

  if (ide>=cont_encomenda){
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
  }
  else if (idp>=cont_produto){
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
  }
  else if (sistema[idp].stock < stock){
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
  }
  else if (peso_total > MAX_PESO_ENCOMENDA){
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
  }

  /*caso o produto ja exista na encomenda, adiciona a nova quantidade a
  quantidade existente */

  else if (encomendas[ide][idp].preco == sistema[idp].preco){
    encomendas[ide][idp].stock += stock;
    sistema[idp].stock -= stock;
  }

  /* coloca nas encomendas o produto com o stock pedido e remove stock desse
  produto no sistema*/

  else{
    encomendas[ide][idp] = sistema[idp];
    encomendas[ide][idp].stock = stock;
    sistema[idp].stock -= stock;
  }
}

/*funcao para comando r, remove stock a um produto existente*/

void remove_stock(int idp,int stock){
  if (idp >= cont_produto){
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp );
  }
  else if (sistema[idp].stock<stock){
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",stock,idp);
  }
  else{
    sistema[idp].stock -= stock;
  }
}

/* funcao para comando R, remove um produto de uma encomenda */

void remove_produto(int ide, int idp){
  if (ide >= cont_encomenda){
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
  }
  else if (idp >= cont_produto){
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
  }
  else{

    /*remover todo o stock desse produto na encomenda*/
    sistema[idp].stock += encomendas[ide][idp].stock;
    encomendas[ide][idp].stock = 0;
  }
}

/*funcao para comando C, calcular custo duma encomenda*/
void calcula_custo(int ide){
  int i,soma = 0;
  if (ide >= cont_encomenda){
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
  }
  else{
    for (i=0;i<cont_produto;i++){
      soma += encomendas[ide][i].preco* encomendas[ide][i].stock;
    }
    printf("Custo da encomenda %d %d.\n",ide,soma);
  }
}


/*funcao para comando p, alterar o preco de um produto existente no sistema */
void altera_preco(int idp, int preco){
  int i;
  if (idp >= cont_produto){
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else{
    sistema[idp].preco = preco;
    for (i=0; i<cont_encomenda;i++){

      /* se for != 0, eh porque o produto existe na encomenda*/

      if (encomendas[i][idp].preco != 0){
      encomendas[i][idp].preco = preco;
      }
    }
  }
}

/* funcao para comando E, retorna a descricao e a quantidade de um produto numa
dada encomenda*/

void lista_descricao_stock(int ide,int idp){
  if (ide >= cont_encomenda){
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
  }
  else if (idp >= cont_produto){
    printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
  }
  else{
    printf("%s %d.\n" ,sistema[idp].descricao, encomendas[ide][idp].stock);
  }
}

/*funcao para comando m, retorna o identificador da encomenda em que um dado
produto ocorre mais vezes*/

void lista_identificador(int idp){
  int i;
  int ide, max_ocorrencias=0;
  if (idp>=cont_produto){
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
  }
  for (i=0;i<cont_encomenda;i++){

    /* no caso de serem iguais as ocorrencias fica o ide de menor ide, como tal nao pomos '>=' */

    if (encomendas[i][idp].stock > max_ocorrencias){
      ide = i;
      max_ocorrencias = encomendas[i][idp].stock;
    }
  }
  if (max_ocorrencias > 0){
    printf("Maximo produto %d %d %d.\n",idp, ide, encomendas[ide][idp].stock);
  }
}

/*implementacao do mergesort, algoritmo de ordenacao usado para ordenar por preco
os produtos no sistema*/

void merge(Produto a[], int left, int m, int right){
  Produto aux[MAX];
  int i, j, k;
  for (i = m+1; i > left; i--){
    aux[i-1] = a[i-1];
  }
  for (j = m; j < right; j++){
    aux[right+m-j] = a[j+1];
  }
  for (k = left; k <= right; k++){
    if (aux[j].preco < aux[i].preco){
      a[k] = aux[j--];
    }
    else if (aux[j].preco > aux[i].preco){
      a[k] = aux[i++];
    }
    else{
      if (aux[j].id < aux[i].id){
        a[k] = aux[j--];
      }
      else{
        a[k] = aux[i++];
      }
    }
  }
}

void mergesort(Produto a[], int left, int right){
  int m = (right+left)/2;
  if (right<=left) return;
  mergesort(a,left,m);
  mergesort(a,m+1,right);
  merge(a,left,m,right);
}



/* funcao para o comando l, lista todos os produtos existentes no sistema por
ordem crescente de preco */

void lista_por_preco(){
  Produto lista_ordenada[MAX];
  int i;

  /*copia de produtos para uma nova lista, que sera posteriormente destruida
  para ordenacao dos produtos */

  for (i=0;i<cont_produto;i++){
    lista_ordenada[i] = sistema[i];
  }

  mergesort(lista_ordenada, 0, cont_produto-1);

  printf("Produtos\n");
  for (i=0;i<cont_produto;i++){
    printf("* %s %d %d\n",lista_ordenada[i].descricao, lista_ordenada[i].preco, lista_ordenada[i].stock);
  }
}

/* funcao auxiliar insertion para poder ordenar os produtos por ordem alfabetica
*/

void insertion(Produto a[], int left, int right){
  int i,j;
  for (i = left+1; i < right; i++){
    Produto v = a[i];
    j = i-1;
    while ( j >= left && strcmp(v.descricao, a[j].descricao)<0) {
      a[j+1] = a[j];
      j--;
    }
    a[j+1] = v;
  }
}


/*funcao para o comando L, lista todos os produtos de uma encomenda por ordem
alfabetica da descricao*/

void lista_encomenda(int ide){
  int i;
  Produto lista_nova[MAX];
  if (ide >= cont_encomenda){
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
  }
  else{

    /* atribui a lista nova todos os produtos na encomenda, para esta poder ser ordenada*/

    for (i=0;i<cont_produto;i++){
      lista_nova[i] = encomendas[ide][i];
    }
    insertion(lista_nova, 0, cont_produto);


    printf("Encomenda %d\n",ide);

    for (i=0;i<cont_produto;i++){
      if (lista_nova[i].stock !=0){
        printf("* %s %d %d\n",lista_nova[i].descricao, lista_nova[i].preco, lista_nova[i].stock);
      }
    }
  }
}

/*funcao principal do programa, onde se vai chamar todas as outras funcoes*/

int main(){
  char x;
  x = getchar();

  /*quando o comando for igual a 'x', o programa termina */
  while (x != 'x'){
    if (x=='a'){
      int preco,peso,stock;
      char descricao[VECMAX];
      scanf(" %[^:]:%d:%d:%d",descricao,&preco,&peso,&stock);
      adiciona_produto(descricao,preco,peso,stock);
    }
    else if (x=='q'){
      int idp,stock;
      scanf(" %d:%d",&idp,&stock);
      adiciona_stock(idp,stock);
    }
    else if (x=='N'){
      cria_encomenda();
    }
    else if (x=='A'){
      int ide,idp,stock;
      scanf(" %d:%d:%d",&ide,&idp,&stock);
      adiciona_produto_encomenda(ide,idp,stock);
    }
    else if (x=='r'){
      int idp,stock;
      scanf(" %d:%d",&idp,&stock);
      remove_stock(idp,stock);
    }
    else if (x== 'R'){
      int ide,idp;
      scanf(" %d:%d",&ide,&idp);
      remove_produto(ide,idp);
    }
    else if (x=='C'){
      int ide;
      scanf(" %d", &ide);
      calcula_custo(ide);
    }
    else if (x=='p'){
      int idp,preco;
      scanf(" %d:%d",&idp,&preco);
      altera_preco(idp,preco);
    }
    else if (x=='E'){
      int ide,idp;
      scanf(" %d:%d",&ide,&idp);
      lista_descricao_stock(ide,idp);
    }
    else if (x=='m'){
      int idp;
      scanf(" %d",&idp);
      lista_identificador(idp);
    }
    else if (x == 'l'){
      lista_por_preco();
    }
    else if (x == 'L'){
      int ide;
      scanf(" %d",&ide);
      lista_encomenda(ide);
    }
    x=getchar();
  }
  return 0;
}
