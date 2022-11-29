#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define DIM 63                                                                  /* Constante para definir tamanho da descricao */
#define PROD 10000                                                              /* Constante para definir quantos produtos podem haver */
#define ENC 500                                                                 /* Constante para definir quantas encomendas podem haver */
#define ID 200                                                                  /* Constante para definir quantos produtos dentro das encomendas podem haver */

int idp=0;                                                                      /* Contador de produtos */
int ide=0;                                                                      /* Contador de encomendas */
int arrayL[PROD], array[PROD];                                                  /* Vetores auxiliares para realizar o merge sort */

typedef struct{                                                                 /* Estrutura que define os produtos */
  int preco, peso, qtd, id;                                                     /*                                  */
  char desc[DIM];                                                               /*                                  */
}Produto;                                                                       /*                                  */
Produto produto[PROD];                                                          /*----------------------------------*/

typedef struct{                                                                 /* Estrutura que define as encomendas */
  Produto prods[ID];                                                            /*                                    */
  int idpe;                                                                     /*                                    */
}Encomenda;                                                                     /*                                    */
Encomenda encomenda[ENC];                                                       /*------------------------------------*/

/*--------------------*/
/* FUNCOES AUXILIARES */
/*--------------------*/

int id_para_idpe(int enc, int id){                                              /* Funcao auxiliar que recebe a encomenda e o id de um produto e se j? existir */
  int idpe;                                                                     /* esse produto na encomenda entao retorna o indice desse produto na encomenda */
  for (idpe=0; idpe<encomenda[enc].idpe; idpe++){
    if (encomenda[enc].prods[idpe].id == id){
      return idpe;
    }
  }
  return encomenda[enc].idpe;
}

void cout(int idp){                                                             /* Funcao auxiliar que recebe o numero de produtos e cria um vetor com todos os ids */
  int i;
  for(i=0; i<idp; i++){
    array[i]=i;
  }
}

void coutL(int idpe){                                                           /* Mesma funcao usada noutro caso */
  int i;
  for(i=0; i<idpe; i++){
    arrayL[i]=i;
  }
}

int pesoaux(int enc, int prod, int qua){                                        /* Funcao auxiliar que calcula o peso com que a encomenda vai ficar, para ter a informacao */
  int i, peso=0;                                                                /* se na funcaoA da erro de peso maximo ou se passa */
  peso += qua * produto[prod].peso;
  for (i=0; i<encomenda[enc].idpe; i++){
    peso += encomenda[enc].prods[i].qtd * encomenda[enc].prods[i].peso ;
    }
  return peso;
}

/*-------------------------*/
/* ALGORITMOS DE ORDENACAO */
/*-------------------------*/

void mergel(int a[], int left, int m, int right){                               /* Algoritmos de ordenacao (merge sort), usado para ordenar os protudos todos, usado para */
  int i, j, k, aux[PROD];                                                       /* resolver a funcaol pois e um algoritmo estavel */
for (i = m+1; i > left; i--)
  aux[i-1] = a[i-1];
for (j = m; j < right; j++)
  aux[right+m-j] = a[j+1];
for (k = left; k <= right; k++)
  if ((produto[aux[j]].preco < produto[aux[i]].preco) || i > m)                 /* Compara os precos dos produtos e o que for menor e colocado primeiro */
    a[k] = aux[j--];
  else
    a[k] = aux[i++];
}

void mergeSortl(int a[], int l, int r){                                         /* Algoritmos de ordenacao (merge sort), usado para ordenar os protudos todos, usado para */
  if (l < r){                                                                   /* resolver a funcaol pois e um algoritmo estavel*/
    int m = l+(r-l)/2;
    mergeSortl(a, l, m);
    mergeSortl(a, m+1, r);
    mergel(a, l, m, r);
  }
}

void mergeL(int a[], int left, int m, int right, int enc){                      /* Algoritmos de ordenacao (merge sort), usado para ordenar os protudos todos da encomenda(enc), usado para */
  int i, j, k;                                                                  /* resolver a funcaoL */
  int aux[PROD];
  for (i = m+1; i > left; i--)
    aux[i-1] = a[i-1];
  for (j = m; j < right; j++)
    aux[right+m-j] = a[j+1];
  for (k = left; k <= right; k++)
    if (strcmp(encomenda[enc].prods[id_para_idpe(enc, aux[j])].desc, encomenda[enc].prods[id_para_idpe(enc, aux[i])].desc)<0) /* Compara as strings e a que for menor e colocada primeiro */
      a[k] = aux[j--];
    else
      a[k] = aux[i++];
}

void mergeSortL(int a[], int l, int r, int enc){                                /* Algoritmos de ordenacao (merge sort), usado para ordenar os protudos todos da encomenda(enc), usado para */
  if (l < r){                                                                   /* resolver a funcaoL */
    int m = l+(r-l)/2;
    mergeSortL(a, l, m, enc);
    mergeSortL(a, m+1, r, enc);
    mergeL(a, l, m, r, enc);
  }
}

/*--------------------*/
/* FUNCOES PRINCIPAIS */
/*--------------------*/

void funcaoa(){                                                                 /* Funcao que cria os produtos , com um scan vai criando produtos com o indice idp */
  scanf(" %[^:]:%d:%d:%d", produto[idp].desc, &produto[idp].preco, &produto[idp].peso, &produto[idp].qtd);
  printf("Novo produto %d.\n", idp);
  idp++;
}

void funcaoq(){                                                                 /* Funcao que adiciona stock a um produto ja existente */
  int prod, addstock;
  scanf(" %d:%d", &prod, &addstock);
  if (prod>=idp){                                                               /* Se o produto ainda nao existir da um erro de produto inexistente */
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prod);
  }
  else{                                                                         /* Se existir, entao adiciona stock ao produto */
    produto[prod].qtd += addstock;
  }
}

void funcaoN(){                                                                 /* Funcao que cria uma nova encomenda, ainda vazia */
  printf("Nova encomenda %d.\n", ide);
  encomenda[ide].idpe = 0;
  ide++;
}

void funcaoA(){                                                                 /* Funcao que adiciona uma quantidade de um produto a uma encomenda */
  int enc, prod, quant;
  scanf(" %d:%d:%d", &enc, &prod, &quant);
  if (enc >= ide){                                                              /* Se a encomenda ainda nao existir entao da erro de Encomenda Inexistente */
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
  }
  else if (prod >= idp){                                                        /* Se o produto nao existir entao da erro de Produto inexistente */
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
  }
  else if (produto[prod].qtd - quant < 0){                                      /* Se colocarem mais quantidade do que o produto tem, na encomenda entao da erro de quantidade em stock insuficiente */
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod, enc);
  }
  else if (pesoaux(enc, prod, quant)>200){                                      /* Se a encomenda exceder as 200 unidades de peso entao da erro de peso maximo */
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod, enc);
  }
  else if (encomenda[enc].prods[id_para_idpe(enc, prod)].qtd==0){               /* Se ainda nao existir este produto na encomenda entao adiciona esse produto com uma certa quantidade a encomenda */
    encomenda[enc].prods[id_para_idpe(enc, prod)].qtd += quant;                 /* e retira essa quantidade ao stock do produto */
    encomenda[enc].prods[id_para_idpe(enc, prod)].preco = produto[prod].preco;
    encomenda[enc].prods[id_para_idpe(enc, prod)].peso = produto[prod].peso;
    strcpy(encomenda[enc].prods[id_para_idpe(enc, prod)].desc, produto[prod].desc);
    encomenda[enc].prods[id_para_idpe(enc, prod)].id = prod;
    produto[prod].qtd -= quant;
    encomenda[enc].idpe++;
  }

  else{                                                                         /* Se ja existir esse produto na encomenda adiciona so a quantidade e remove essa do stock do produto */
    encomenda[enc].prods[id_para_idpe(enc, prod)].qtd += quant;
    produto[prod].qtd -= quant;
  }
}

void funcaor(){                                                                 /* Funcao que remove stock a um produto existente */
  int prod, remstock;
  scanf(" %d:%d", &prod, &remstock);
  if (prod >= idp){                                                             /* Se o produto nao existir entao da erro */
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod);
  }
  else if (produto[prod].qtd - remstock < 0){                                   /* Se a quantidade de stock pretendida a retirar for maior que o stock do produto entoa da erro */
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", remstock, prod);
  }
  else {                                                                        /* Se nao for erro, entao retira o stock ao produto */
    produto[prod].qtd -= remstock;
  }
}

void funcaoR(){                                                                 /* Funcao que remove um produto da encomenda */
  int enc, prod;
  scanf(" %d:%d", &enc, &prod);
  if (enc >= ide){                                                              /* Se a encomenda nao existir da erro */
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
  }
  else if (prod >= idp){                                                        /* Se o produto nao existir da erro */
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
  }
  else{                                                                         /* Se nao der nenhum erro entao remove o produto da encomenda e volta a por a quantidade removida no strock do produto */
    produto[prod].qtd += encomenda[enc].prods[id_para_idpe(enc, prod)].qtd;
    encomenda[enc].prods[id_para_idpe(enc, prod)].qtd = 0;
  }
}

void funcaoC(){                                                                 /* Funcao que Calcula o preco de uma encomenda */
  int enc, preco = 0, i;
  scanf(" %d", &enc);
  if (enc >= ide){                                                              /* Se a encomenda nao existir da erro */
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
  }
  else{
    for (i=0; i<encomenda[enc].idpe; i++){                                      /* Se nao der erro, precorre todos os produtos da encomenda e adiciona o preco deles ao preco total */
      preco += produto[encomenda[enc].prods[i].id].preco * encomenda[enc].prods[i].qtd;
    }
    printf("Custo da encomenda %d %d.\n", enc, preco);
  }
}

void funcaop(){                                                                 /* Funcao que altera o preco de um produto existente no sistema */
  int prod, mudpreco, i;
  scanf(" %d:%d", &prod, &mudpreco);
  if (prod >= idp){                                                             /* Se o produto nao existir da erro */
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prod);
  }
  else{
    produto[prod].preco = mudpreco;                                             /* Se nao der erro o produto muda de preco e todas as encomendas com esse produto tambem muda de preco */
    for (i=0; i<ide; i++){
      encomenda[i].prods[id_para_idpe(i, prod)].preco = mudpreco;
    }
  }
}

void funcaoE(){                                                                 /* Funcao que retorna a descricao e a quantidade de um produto numa dada encomenda */
  int enc, prod;
  scanf(" %d:%d", &enc, &prod);
  if (enc>=ide){                                                                /* Se a encomenda nao existir da erro */
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
  }
  else if (prod>=idp){                                                          /* Se o produto nao existir da erro */
    printf("Impossivel listar produto %d. Produto inexistente.\n", prod);
  }
  else{                                                                         /* Se nao der erro a funcao retorna a descricao e a quantidade desse produto na encomenda */
    printf("%s %d.\n", produto[prod].desc, encomenda[enc].prods[id_para_idpe(enc, prod)].qtd);
  }
}

void funcaom(){                                                                 /* Funcao que retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
  int prod, i, maior=0, imaior = 0;
  scanf(" %d", &prod);
  if (prod>=idp){                                                               /* Se o produto nao existir da erro */
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod);
  }
  else{
    for (i=0; i<ide; i++){                                                      /* Se nao der erro entao percorre todas as encomendas e na encomenda que tiver maior quantidade guarda a quantidade */
      if (encomenda[i].prods[id_para_idpe(i, prod)].qtd > maior){               /* e o identificador da encomenda e se a quantidade for maior que 0 (ou seja exista na encomenda) retorna o identificador */
        maior = encomenda[i].prods[id_para_idpe(i, prod)].qtd;                  /* do produto, da encomenda e a quantidade desse produto na encomenda */
        imaior = i;
      }
    }
    if (maior>0){
      printf("Maximo produto %d %d %d.\n", prod, imaior, maior);
    }
  }
}

void funcaol(){                                                                 /* Funcao que lista todos os produtos existentes no sistema por ordem crescente de preco */
  int i;
  cout(idp);                                                                    /* Cria uma lista auxiliar com todos os ids dos produtos */
  mergeSortl(array, 0, idp-1);                                                  /* Ordena pro oredem crescente essa lista de acordo com o preco */
  printf("Produtos\n");
  for (i=0; i <idp; i++){                                                       /* Percorre todos os produtos ja ordenados e retorna a descricao, o preco e a quantidade de cada um */
    printf("* %s %d %d\n", produto[array[i]].desc, produto[array[i]].preco, produto[array[i]].qtd);
  }
}

void funcaoL(){                                                                 /* Funcao que lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
  int i, enc, id;
  scanf(" %d", &enc);
  if (enc>=ide){                                                                /* Se a encomenda nao existir da erro */
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
  }
  else{                                                                         /* Se existir */
    coutL(idp);                                                                 /* Cria uma lista auxiliar com todos os produtos possiveis dentro da encomenda */
    mergeSortL(arrayL, 0, idp-1, enc);                                          /* Ordena alfabeticamente essa lista de acordo com a descricao */
    printf("Encomenda %d\n", enc);
    for (i=0; i<idp; i++){                                                      /* Percorre a lista ja ordenada e retorna a descricao, o preco e a quantidade de todos os produtos nessa encomenda */
      id = id_para_idpe(enc, arrayL[i]);
      if (encomenda[enc].prods[id].qtd>0){
        printf("* %s %d %d\n", produto[encomenda[enc].prods[id].id].desc, produto[encomenda[enc].prods[id].id].preco, encomenda[enc].prods[id].qtd);
      }
    }
  }
}

/*-------------*/
/* FUNCAO MAIN */
/*-------------*/

int main() {
  char comando;
  while(1) {                                                                    /* Um ciclo infinito para pedir os comandos e continuar o programa sempre a funcionar, ate o comando ser x que acaba o programa */
    scanf("%c", &comando);                                                      /* Pede um comando e consoante esse comando vai para cada funcao */
    switch(comando){
      case 'a':
        funcaoa();
        break;
      case 'q':
        funcaoq();
        break;
      case 'N':
        funcaoN();
        break;
      case 'A':
        funcaoA();
        break;
      case 'r':
        funcaor();
        break;
      case 'R':
        funcaoR();
        break;
      case 'C':
        funcaoC();
        break;
      case 'p':
        funcaop();
        break;
      case 'E':
        funcaoE();
        break;
      case 'm':
        funcaom();
        break;
      case 'l':
        funcaol();
        break;
      case 'L':
        funcaoL();
        break;
      case 'x':
        return 0;
    }
  }
  return 0;
}
