#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DESCRIPTION 64
#define MAX_ID 10000
#define MAX_WEIGHT 200
#define MAX_DELIVERIES 500
#define MAX_PRODUCTS_DELIVERIES 200 /* todos estes nomes sao intuitivos em relacao ao que representam */

typedef struct produto /* vetor estrutura que guarda todas as informacoes do produto */
{
  int idp;
  char NOME_PRODUTO[MAX_DESCRIPTION];
  int peso;
  int preco;
  int stock;
}produto;

typedef struct encomenda /* estrutura da encomenda que guarda o peso, o ide e o idp e qtd de cada produto presente em cada encomenda */
{
  int peso; 
  int ide;
  int produtos[200][2]; /* vetor que guarda todos os produtos presentes na encomenda, sendo o primeiro indice o idp, e o segundo a qtd/peso, (se o peso for 1, o peso total e igual a qtd) */
}encomenda;

encomenda vetor_encomendas[500]; /* vetor estrutura que guarda toda a informacao das encomendas */
produto vetor_produtos[10000]; /* vetor estrutura que guarda toda a informacao dos produtos */
char linha_input[100]; /* vetor usado para guardar o input na ReadsInput*/
int aux[MAX_ID]; /* vetor auxiliar usado no Merge */

/* FUNCOES AUXILIARES */

void readsInput(char linha_input[]) {
  char c;
  int n = 0;
  while ((c=getchar()) != '\n'){ /* esta funcao e usada em todas as funcoes principais que recebem informacao do input sem ser a letra do comando */
    linha_input[n] = c;
    n++;
  }
  linha_input[n] = '\0'; /* nesta funcao auxiliar, guardo todos os caracteres do input, exceto a letra e o espaco inicial, num vetor de caracteres */
}

void InitializesMinusOne(produto vetor_produtos[MAX_ID], encomenda vetor_encomendas[MAX_DELIVERIES]){
  int i, e;
  for (i=0; i < MAX_ID; i++){
      vetor_produtos[i].idp = -1; /* todos os indices onde sao guardados os idps no vetor estrutura produtos, sao igualados a -1 para mostrar que nao ha la nada guardado */
      for (e = 0; e < MAX_DESCRIPTION; e++){
        vetor_produtos[i].NOME_PRODUTO[e] = ' '; /* os indices destinados a guardar a descricao dos produtos sao postos vazios */
      }
  }
  for (i = 0; i < MAX_DELIVERIES; i++){ 
    vetor_encomendas[i].ide = -1; /* todos os indices onde sao guardados os ides no vetor estrutura encomendas, sao igualados a -1 para mostrar que nao ha la nada guardado */
    for (e = 0; e < MAX_WEIGHT; e++){
      vetor_encomendas[i].produtos[e][0] = -1; /* os indices destinados a guardar os idps dos produtos presentes nas encomendas sao igualados a -1, mostrando que nao ha produtos guardados na encomenda */
    }
  }
}

/* A FUNCAO CreatesDelivery E PRINCIPAL */

void CreatesDelivery(){
  int i;
  for (i = 0; i < MAX_DELIVERIES; i++){
    if (vetor_encomendas[i].ide == -1){ /* verifica que nao existe nenhuma encomenda com esse indice*/
      vetor_encomendas[i].peso = 0; /* poe o peso da nova encomenda a zero */
      vetor_encomendas[i].ide = i; /* poe o ide da encomenda igual ao indice */
      break;
    }
  }
  printf("Nova encomenda %d.\n", vetor_encomendas[i].ide);
}

void Merge(int vetor_idps[], int l, int m, int r){
  int i, j, k;
  int aux[10000];
  for (i = m+1; i > l; i--){
    aux[i-1] = vetor_idps[i-1];
  }
  for (j = m; j < r; j++){
    aux[r+m-j] = vetor_idps[j+1];
  }
  for (k = l; k <= r; k++){
    if (vetor_produtos[aux[j]].preco < vetor_produtos[aux[i]].preco){
      vetor_idps[k] = aux[j--];
    } /* eu desordeno os idps, e ordeno os precos associados aos mesmos */
    else if ((vetor_produtos[aux[j]].preco == vetor_produtos[aux[i]].preco) && (vetor_produtos[aux[j]].idp < vetor_produtos[aux[i]].idp)){
      vetor_idps[k] = aux[j--]; /* se dois produtos tiverem o mesmo preco, e o de menor idp estiver mais avancado que o de maior idp, o de maior avanca e o de menor recua */
    }
    else{
      vetor_idps[k] = aux[i++];
    }
  }
}

void MergeSort(int vetor_idps[], int l, int r){
  int m = (r+l)/2;

  if (r <= l){
    return;
  }

  MergeSort(vetor_idps, l, m);
  MergeSort(vetor_idps, m+1, r);
  Merge(vetor_idps, l, m, r); /* sendo uma funcao recursiva, chama se a si propria sempre que o vetor a ordenar ainda nao estiver partido em varios vetores unitarios */
}

/* LER DE BAIXO PARA CIMA POR FAVOR, FUNCOES PRINCIPAIS */

void OrdersProductsByPrice(){
  int vetor_idps[MAX_ID];
  int i, e, l=0, r, contador = 0;

  for (i=0; i < MAX_ID; i++){
    if (vetor_produtos[i].idp == i){
      vetor_idps[i] = vetor_produtos[i].idp; /* vetor a ordenar com todos os idps */
      contador++; /* contador que serve para saber quantos produtos existem, para saber quantos printar e o comprimento do vetor a ordenar*/
    }
  }
  r = contador;
  MergeSort(vetor_idps, l, r-1);
  printf("Produtos\n");
  for (e=0; e < contador; e++){
    printf("* %s %d %d\n", vetor_produtos[vetor_idps[e]].NOME_PRODUTO, vetor_produtos[vetor_idps[e]].preco, vetor_produtos[vetor_idps[e]].stock);
  }
}

void ListsIdeWhereIdpMoreFrequent(char linha_input[]){
  int i,e,p=0,b=0,a=0, idp=0, ide=0;
  char guarda_idp[1][10000];
  int tamanho0, qtd=0;
  getchar();
  readsInput(linha_input);
  while (linha_input[p] != '\0'){
    if (linha_input[p] != ':'){
      guarda_idp[a][b] = linha_input[p];
      b++;
    }
    else{
      guarda_idp[a][b] = '\0';
      b = 0;
      a++;
    }
    p++;
  }
  guarda_idp[a][b] = '\0';

  tamanho0 = strlen(guarda_idp[0]);

  for (i=0; i < tamanho0; i++){
    idp = (idp*10) + (guarda_idp[0][i] - '0');
  }

  if (vetor_produtos[idp].idp == -1){
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else{
    for (e=0; e < MAX_DELIVERIES; e++){
      if (vetor_encomendas[e].produtos[idp][0] == vetor_produtos[idp].idp){ /* verifica que o idp do produto na loja e igual ao idp desse produto na encomenda */
        if (vetor_encomendas[e].produtos[idp][1] > qtd){ /* verifica que a qtd desse produto na encomenda e maior que zero */
          qtd = vetor_encomendas[e].produtos[idp][1]; /* a variavel qtd passa a tomar o valor da qtd do produto que se encontra na encomenda, com o idp dado no input */
          ide = e; /* o ide da encomenda e igual ao indice do for, sempre que as condicoes anteriores nos ifs se verificam */
        }
      }
    }
    if (qtd > 0){ /* se a qtd for maior que zero, ou seja, se tomou algum valor, imprime idp, ide e qtd */
      printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
    }
  }
}

void ListsDescriptionQuantity(char linha_input[]){
  int i,p=0,b=0,a=0,idp=0, ide=0;
  char guarda_ide_idp[2][10000];
  int tamanho0, tamanho1;
  getchar();
  readsInput(linha_input);
  while (linha_input[p] != '\0'){
    if (linha_input[p] != ':'){
      guarda_ide_idp[a][b] = linha_input[p];
      b++;
    }
    else{
      guarda_ide_idp[a][b] = '\0';
      b = 0;
      a++;
    }
    p++;
  }
  guarda_ide_idp[a][b] = '\0';

  tamanho0 = strlen(guarda_ide_idp[0]);
  tamanho1 = strlen(guarda_ide_idp[1]);

  for (i=0; i < tamanho0; i++){
    ide = (ide*10) + (guarda_ide_idp[0][i] - '0');
  }
  for (i=0; i < tamanho1; i++){
    idp = (idp*10) + (guarda_ide_idp[1][i] - '0');
  }

  if (vetor_encomendas[ide].ide == -1){
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else if (vetor_produtos[idp].idp == -1){
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  }
  else{
    printf("%s %d.\n", vetor_produtos[idp].NOME_PRODUTO, vetor_encomendas[ide].produtos[idp][1]);
  } /* esta funcao simplesmente printa a descricao do produto com o idp dado no input, e a sua qtd,  na encomenda com o ide dado no input */
}

void CalculatesPriceDelivery(char linha_input[]){
  int i,p=0,b=0,a=0,total=0, idp=0, ide=0;
  char guarda_ide[1][10000];
  int tamanho0;
  getchar();
  readsInput(linha_input);
  while (linha_input[p] != '\0'){
    if (linha_input[p] != ':'){
      guarda_ide[a][b] = linha_input[p];
      b++;
    }
    else{
      guarda_ide[a][b] = '\0';
      b = 0;
      a++;
    }
    p++;
  }
  guarda_ide[a][b] = '\0';

  tamanho0 = strlen(guarda_ide[0]);

  for (i=0; i < tamanho0; i++){
    ide = (ide*10) + (guarda_ide[0][i] - '0');
  }

  for (i=0; i < MAX_PRODUCTS_DELIVERIES; i++){ /* percorre todos os produtos existentes na encomenda */
    idp = vetor_encomendas[ide].produtos[i][0]; /* a constante idp passa a tomar o valor do idp, de um produto existente na encomenda */
    total += (vetor_encomendas[ide].produtos[i][1] * vetor_produtos[idp].preco); 
  } /* o total do preco da encomenda e calculado atraves da qtd do produto na encomenda vezes o preco desse produto registado na loja */

  if (vetor_encomendas[ide].ide == -1){
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else{
    printf("Custo da encomenda %d %d.\n", ide, total);
  }
}

void RemovesProductToDelivery(char linha_input[]){
  int i,p=0,b=0,a=0,peso;
  int ide=0, idp=0;
  char guarda_ide_idp[2][10000];
  int tamanho0, tamanho1;
  getchar();
  readsInput(linha_input);
  while (linha_input[p] != '\0'){
    if (linha_input[p] != ':'){
      guarda_ide_idp[a][b] = linha_input[p];
      b++;
    }
    else{
      guarda_ide_idp[a][b] = '\0';
      b = 0;
      a++;
    }
    p++;
  }
  guarda_ide_idp[a][b] = '\0';

  tamanho0 = strlen(guarda_ide_idp[0]);
  tamanho1 = strlen(guarda_ide_idp[1]);

  for (i=0; i < tamanho0; i++){
    ide = (ide*10) + (guarda_ide_idp[0][i] - '0');
  }
  for (i=0; i < tamanho1; i++){
    idp = (idp*10) + (guarda_ide_idp[1][i] - '0');
  }
  for (i=0; i < MAX_ID; i++){
    if (vetor_produtos[i].idp == idp){
      peso = vetor_produtos[i].peso; 
    }
  }
  if (vetor_encomendas[ide].ide == -1){ /* verificacao de dois erros iguais a funcao AddsProductToDelivery */
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide); 
  }
  else if (vetor_produtos[idp].idp == -1){
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  }

  else{
      vetor_encomendas[ide].peso -= (peso * vetor_encomendas[ide].produtos[idp][1]); /* retiro ao peso da encomenda ja existente, o novo peso dos produtos que se querem retirar */
      vetor_encomendas[ide].produtos[idp][0] = idp; /* atualizo o idp com o dado no input */
      vetor_produtos[ide].stock += vetor_encomendas[ide].produtos[idp][1]; /* adiciono ao stock da loja a qtd dos produtos que foi retirada na encomenda */
      vetor_encomendas[ide].produtos[idp][1] = 0; /* a qtd do produto dado no input, na encomenda, passa a ser zero */
      }
    }
  
void AddsProductToDelivery(char linha_input[]){
  int i,p=0,b=0,a=0,peso;
  int ide=0, idp=0, qtd=0;
  char guarda_ide_idp_stock[3][10000];
  int tamanho1, tamanho2, tamanho0;
  getchar();
  readsInput(linha_input);
  while (linha_input[p] != '\0'){
    if (linha_input[p] != ':'){
      guarda_ide_idp_stock[a][b] = linha_input[p];
      b++;
    }
    else{
      guarda_ide_idp_stock[a][b] = '\0';
      b = 0;
      a++;
    }
    p++;
  }
  guarda_ide_idp_stock[a][b] = '\0';

  tamanho1 = strlen(guarda_ide_idp_stock[1]);
  tamanho2 = strlen(guarda_ide_idp_stock[2]);
  tamanho0 = strlen(guarda_ide_idp_stock[0]);

  for (i=0; i < tamanho0; i++){
    ide = (ide*10) + (guarda_ide_idp_stock[0][i] - '0');
  }
  for (i=0; i < tamanho1; i++){
    idp = (idp*10) + (guarda_ide_idp_stock[1][i] - '0');
  }
  for (i=0; i < tamanho2; i++){
    qtd = (qtd*10) + (guarda_ide_idp_stock[2][i] - '0');
  }
  peso = vetor_produtos[idp].peso; /* passo o peso para uma variavel isolada */
  if (vetor_encomendas[ide].ide == -1){ /* se nao existir nenhuma encomenda registada com o ide dado, imprime erro */
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else if (vetor_produtos[idp].idp == -1){ /* se nao exitir nenhum produto na loja com o idp dado, imprime erro */
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  }
  else if (qtd > vetor_produtos[idp].stock){ /* se o stock de um certo produto na loja nao chega para satisfazer a encomenda, imprime erro */
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
  }
  else if (vetor_encomendas[ide].peso + qtd*peso > 200){ /* se o peso que se encontra na encomenda mais o peso dos produtos que se querem adicionar excedem 200, imprime erro */
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
  }
  else{ /* se nada das restricoes anteriores se verificarem, acontece o seguinte */
      vetor_encomendas[ide].peso += qtd*peso; /* e adicionado ao peso da encomenda ja existente, o novo peso dos produtos que se querem adicionar */
      vetor_produtos[idp].stock -= qtd; /* e retirado da loja o stock dos produtos que se querem adicionar a nova encomenda */
      vetor_encomendas[ide].produtos[idp][0] = idp; /* o idp e a qtd do ide da encomenda dado no input, sao atualizados com os novos valores do mesmo */
      vetor_encomendas[ide].produtos[idp][1] += qtd;
  }
}

void ChangesPrice(char linha_input[]){
  int i,p=0,b=0,a=0,e,contador=0;
  int preco=0, idp=0;
  char guarda_idp_preco[2][1000];
  int tamanho0, tamanho1;
  getchar();
  readsInput(linha_input);
  while (linha_input[p] != '\0'){
    if (linha_input[p] != ':'){
      guarda_idp_preco[a][b] = linha_input[p];
      b++;
    }
    else{
      guarda_idp_preco[a][b] = '\0';
      b = 0;
      a++;
    }
    p++;
  }
  guarda_idp_preco[a][b] = '\0';

  tamanho0 = strlen(guarda_idp_preco[0]);
  tamanho1 = strlen(guarda_idp_preco[1]);

  for (i=0; i < tamanho0; i++){
    idp = (idp*10) + (guarda_idp_preco[0][i] - '0');
  }
  for (i=0; i < tamanho1; i++){
    preco = (preco*10) + (guarda_idp_preco[1][i] - '0');
  }
  for (e=0; e < MAX_ID; e++){
    if (vetor_produtos[e].idp == idp){
      contador++;
      vetor_produtos[e].preco = preco; /* igual as duas funcoes anteriores, mas aqui atualiza o preco do produto na loja para o dado no input */
      break;
    }
  }
  if (contador==0){
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
}

void RemovesQuantity(char linha_input[]){
  int i,p=0, b=0, a=0, e, contador=0;
  int qtd = 0, idp = 0;
  char guarda_idp_stock[2][1000];
  int tamanho0, tamanho1;
  getchar();
  readsInput(linha_input);
  while (linha_input[p] != '\0'){
    if (linha_input[p] != ':'){
      guarda_idp_stock[a][b] = linha_input[p];
      b++;
    }
    else{
      guarda_idp_stock[a][b] = '\0';
      b = 0;
      a++;
    }
    p++;
  }
  guarda_idp_stock[a][b] = '\0';

  tamanho0 = strlen(guarda_idp_stock[0]);
  tamanho1 = strlen(guarda_idp_stock[1]);

  for (i=0; i < tamanho0; i++){
    idp = (idp*10) + (guarda_idp_stock[0][i] - '0');
  }

  for (i=0; i < tamanho1; i++){
    qtd = (qtd*10) + (guarda_idp_stock[1][i] - '0');
  }

  for (e=0; e < MAX_ID; e++){
    if (vetor_produtos[e].idp == idp){ /* mesmo raciocinio que na AddsQuantity, so que retira ao stock em vez de adicionar */
      contador++;
      if (vetor_produtos[e].stock < qtd){ 
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        break; /* se o stock da loja for menor que a quantidade do input que se quer retirar, imprime erro, a loja nao pode ter stock negativo */
      }
    }
    vetor_produtos[e].stock -= qtd;
  }
  if (contador == 0){
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
}

void AddsQuantity(char linha_input[]){
  int i,p=0, b=0, a=0, e, contador=0;
  int qtd = 0, idp = 0;
  char guarda_idp_stock[2][1000]; /* eu uso o mesmo raciocinio para todas as funcoes para guardar o input*/
  int tamanho0, tamanho1;
  getchar(); 
  readsInput(linha_input);
  while (linha_input[p] != '\0'){
    if (linha_input[p] != ':'){
      guarda_idp_stock[a][b] = linha_input[p];
      b++;
    }
    else{
      guarda_idp_stock[a][b] = '\0';
      b = 0;
      a++;
    }
    p++;
  }
  guarda_idp_stock[a][b] = '\0';

  tamanho0 = strlen(guarda_idp_stock[0]); 
  tamanho1 = strlen(guarda_idp_stock[1]); 

  for (i=0; i < tamanho0; i++){
    idp = (idp*10) + (guarda_idp_stock[0][i] - '0');
  }

  for (i=0; i < tamanho1; i++){
    qtd = (qtd*10) + (guarda_idp_stock[1][i] - '0');
  }

  for (e=0; e < MAX_ID; e++){
    if (vetor_produtos[e].idp == idp){ /* verifica se existe um idp guardado na estrutura produtos igual ao dado no input */
      vetor_produtos[e].stock += qtd; /* adiciona ao stock da estrutura produtos, ou seja, a loja, a qtd dada no input */
      contador++; /* contador para indicar se existe ou nao idp, imprime o erro se for zero, incrementa se existir */
    }
  }
  if (contador == 0){ 
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
}

void AddsNewProduct(char linha_input[100]){
  int i, e, p = 0, a = 0, b = 0;
  int preco = 0, peso=0, stock = 0;
  char guarda_produto[4][MAX_DESCRIPTION]; /* vetor em que guardo as diferentes informacoes do input, neste caso, descricao, preco, peso e stock/qtd. */
  int tamanho1, tamanho2, tamanho3;
  getchar(); /* tiro o espaco a seguir ao primeiro caracter em todas as funcoes */
  readsInput(linha_input); /* chamo esta auxiliar em todas as funcoes, explicado melhor na auxiliar em si */
  while (linha_input[p] != '\0'){
    if(linha_input[p] == ':'){
      guarda_produto[a][b] = '\0'; /* passo os caracteres do vetor em que esta guardado o input para um vetor que guarda as diferentes informacoes organizadas por ordem e sem os dois pontos. */
      b = 0;
      a++;
    }
    else{
      guarda_produto[a][b] = linha_input[p];
      b++;
    }
    p++;
  }
  guarda_produto[a][b] = '\0';

  tamanho1 = strlen(guarda_produto[1]);
  tamanho2 = strlen(guarda_produto[2]); /* estas variaveis representam o comprimento de cada informacao do input */
  tamanho3 = strlen(guarda_produto[3]);

  for (i=0; i < tamanho1; i++){
    preco = (preco*10) + (guarda_produto[1][i] - '0'); /* adiciona cada informacao a uma variavel individual de nome intuitivo, e passa de caracter para inteiro, cada digito. */
  }
  for (i=0; i < tamanho2; i++){
    peso = (peso*10) + (guarda_produto[2][i] - '0');
  }
  for (i=0; i < tamanho3; i++){
    stock = (stock*10) + (guarda_produto[3][i] - '0');
  }
  for (e=0; e < MAX_ID; e++){
    if (vetor_produtos[e].idp == -1){ /* verifica se nao existe algum idp guardado no vetor estrutura dos produtos */
      for (i = 0; i < MAX_DESCRIPTION; i++) {
        vetor_produtos[e].NOME_PRODUTO[i] = guarda_produto[0][i]; /* se nao houver, passa os caracteres guardados no vetor com a descricao do input, para o vetor NOME_PRODUTO que faz parte da estrutura. */
      }
      vetor_produtos[e].NOME_PRODUTO[i] = '\0';
      vetor_produtos[e].preco = preco; /* nao so passa a descricao, como passa o resto da informacao do input tambem. */
      vetor_produtos[e].peso = peso;
      vetor_produtos[e].stock = stock;
      vetor_produtos[e].idp = e; /* o idp guardado vai ser igual ao indice percorrido pelo for */
      break;
  }
}
  printf("Novo produto %d.\n", vetor_produtos[e].idp); 
}

/* Funcao main que dependendo da primeira letra do input realiza as diferentes funcoes do sistema */

int main(){
  int running = 1;
  int c;
  InitializesMinusOne(vetor_produtos, vetor_encomendas); /* Chamo esta funcao auxiliar na main para que se aplique a todas as outras funcoes */
  while (running == 1){
    switch(c = getchar()) { /* Tiro e leio o primeiro caracter */
      case 'a':
        AddsNewProduct(linha_input);
        break;
      case 'q':
        AddsQuantity(linha_input);
        break;
      case 'r':
        RemovesQuantity(linha_input);
        break;
      case 'p':
        ChangesPrice(linha_input);
        break;
      case 'N':
        CreatesDelivery();
        break;
      case 'A':
        AddsProductToDelivery(linha_input);
        break;
      case 'R':
        RemovesProductToDelivery(linha_input);
        break;
      case 'C':
        CalculatesPriceDelivery(linha_input);
        break;
      case 'E':
        ListsDescriptionQuantity(linha_input);
        break;
      case 'm':
        ListsIdeWhereIdpMoreFrequent(linha_input);
        break;
      case 'l':
        OrdersProductsByPrice();
        break;
      case 'x':
        running = 0; /* a letra x termina o programa */
        break;

    }
  }
  return 0;
}
