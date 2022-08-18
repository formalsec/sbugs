#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 63
#define Nprods 9999
#define Pmax 200
#define Emax 500
/* Constantes */

typedef struct produto{   /* Estrutura do produto com as suas diferentes variaveis */
  char des[DIM];          /*descricao*/
  int preco;              /*preco*/
  int qtd;                /*quantidade*/
  int peso;               /*peso*/
  int idp;                /*identificador do produto*/
}P;

typedef struct encomenda{   /* Estrutura da encomenda com as suas propriedades */
  int peso;                 /*peso da encomenda*/
  int ide;                  /*identificador da encomenda*/
  P prode[Nprods];          /*Vetor de produtos dentro da encomenda*/
  int precoe;
  int cont;               /*preco da encomenda*/


}E;

/*Declaracao de variaveis globais*/

int prodE, m , cont;

P prod[Nprods];           /*Vetor produtos*/
int numero;


E enco[Emax];             /*Vetor encomendas*/
int nenco;

int pre;

void case_a()            /*Funcao do caso a*/
{

      printf("Novo produto %d.\n", numero );    /*Novo produto adicionado ao sistema*/

}

void case_q(int idp, int qtd)  /*Funcao do caso q*/
{

     if( idp == prod[idp].idp){  /*Caso o produto exista no sistema*/
       prod[idp].qtd += qtd;}    /*sera adicionada a quantidade desejada*/

     else{                       /*Caso nao exista da erro*/
       printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp );

     }

}

void case_N()       /*Funcao do caso N*/
{

     printf("Nova encomenda %d.\n", nenco );   /*Nova encomenda adicionada ao sistema*/
}

void case_A(int ide , int idp , int qtd)  /*Funcao do caso A*/
{

    if (ide != enco[ide].ide){      /*Caso a encomenda nao exista da erro*/
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp , ide );
    }
    else if (idp != prod[idp].idp){  /* Caso o produto nao exista da erro*/
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp , ide );
    }
    else if (qtd > prod[idp].qtd){   /*Caso a quantidade desejada seja superior a do stock do produto da erro*/
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide );
    }
    else if (enco[ide].peso + prod[idp].peso*qtd > 200){
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp , ide);
    }



    else if (ide == enco[ide].ide){  /*Se a encomenda existir*/
      if ( (idp != enco[ide].prode[idp].idp) || idp == 0 ){  /*Caso o produto nao exista na encomenda*/
        enco[ide].prode[idp] = prod[idp];     /*O produto e adicionado a encomenda*/
        enco[ide].prode[idp].idp = prod[idp].idp;
        enco[ide].prode[idp].qtd = qtd;       /*A quantidade do produto na encomenda e igual a desejada*/
        prod[idp].qtd = prod[idp].qtd -qtd;   /*E retirado ao stock do produto a quantidade adicionada a encomenda*/
        enco[ide].peso += prod[idp].peso * qtd;  /*E calculado o peso da encomenda, que aumenta com o maior numero de produtos*/
        enco[ide].cont ++;  /*O contador aumenta sempre que adicionamos um produto a encomenda e sera util mais tarde*/
      }
      else{      /*Caso o produto ja exista na encomenda*/
        enco[ide].prode[idp].qtd += qtd;   /*iremos apenas adicionar a quantidade desejada*/
        prod[idp].qtd = prod[idp].qtd -qtd;  /*retirar ao stock a quantidade adicionada a encomenda*/
        enco[ide].peso += prod[idp].peso * qtd;  /*E calculado o peso da encomenda, que aumenta com o maior numero de produtos*/

      }
    }

}

void case_r( int idp, int qtd)  /*Funcao do caso r*/
{


   if(idp != prod[idp].idp){   /*Caso o produto nao exista da erro*/
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp );
    }

    if (idp == prod[idp].idp){  /* se existir */
        if ( qtd > prod[idp].qtd ){  /*Caso a quantidade a retirar seja superior ao stock atual da erro*/
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd , idp );
        }    /* Caso contrario retiramos a quantidade desejada ao stock do produto*/
        else { prod[idp].qtd = prod[idp].qtd - qtd; }
    }
}

void case_R(int ide , int idp) /*Funcao do caso R*/
{
    if (ide == enco[ide].ide ){  /*Caso a encomenda exista*/
      if (idp == prod[idp].idp ){  /*Caso o produto exista*/
        prod[idp].qtd += enco[ide].prode[idp].qtd;  /*Voltamos a adiconar ao stock a quantidade de produto retirado da encomenda*/
        enco[ide].prode[idp].qtd = 0;  /*E a quantidade na encomenda desse produto fica a 0*/

      }
      else{  /* Caso o produto nao exista da erro*/
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp , ide );
      }
    }
    else if (ide != enco[ide].ide){  /*Se a encomenda nao existir da erro*/
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp , ide );
    }
}

void case_C(int ide)   /*Funcao do caso C*/
{
  int pre = 0, n;
   if (ide != enco[ide].ide){    /*Se a encomenda nao existir da erro*/
     printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide );
   }
   else if( ide == enco[ide].ide){   /* se a encomenda existir */
     for ( n = 0 ; n <= enco[ide].cont ; n++){  /* Ciclo de maneira a correr todos os produtos dentro da encomenda*/
       pre += enco[ide].prode[n].qtd * prod[n].preco; /*calcular o preco da encomenda*/

     }
     printf("Custo da encomenda %d %d.\n", ide , pre);
   }
 }

void case_p(int idp , int preco)  /*Funcao do caso p*/
{
  if (idp != prod[idp].idp){    /*Caso o produto nao exista da erro*/
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp );
  }
  else if (idp == prod[idp].idp){   /*Caso exista mudamos o preco do mesmo*/
    prod[idp].preco = preco;

  }
}

void case_E(int ide, int idp) /*Funcao do caso E*/
{
  if (ide != enco[ide].ide){   /*Se a encomenda nao existir da erro*/
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide );
  }
  if (idp != prod[idp].idp){   /*Se o produto nao existir da erro*/
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp );
  }
  if (ide == enco[ide].ide){     /*Caso o produto e a encomenda existam*/
    if ( idp == prod[idp].idp){
      printf("%s %d.\n", prod[idp].des , enco[ide].prode[idp].qtd );  /*devolve a quantidade do produto na encomenda*/
    }
  }
}

void case_m(int idp)  /*Funcao do caso m*/
{

  int x = 0, f = 0, ide = 0;
  if ( idp != prod[idp].idp){     /*Caso o produto nao exista da erro*/
   printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp );
 }
 else{                  /*Se existir*/
  while ( x < nenco) {       /*Enquanto a encomenda existir*/
      if (enco[x].prode[idp].qtd > f){   /* se a quantidade do produto nessa encomenda for maior do que f*/
        f = enco[x].prode[idp].qtd;    /*atualiza o f*/
        ide = x;
      }
    x ++;         /*X incrementa*/
  }
  printf("Maximo produto %d %d %d.\n",idp, ide, f );

 }
}

  void merge(int a[], int left, int m, int right) /*Funcao utilizada em l para ordenar*/
{
 int i, j, k , aux[10000];
 for (i = m+1; i > left; i--){
   aux[i-1] = a[i-1];}
 for (j = m; j < right; j++){
   aux[right+m-j] = a[j+1];}
 for (k = left; k <= right; k++){
   if ( prod[aux[j]].preco < prod[aux[i]].preco|| i > m){
     a[k] = aux[j--];}
   else{
     a[k] = aux[i++];}
   }

}

void mergesort(int a[], int l, int r)   /*Funcao utilizada em l para ordenar*/
{
  int m = (r+l)/2;
  if (r <= l) return;
  mergesort(a , l, m);
  mergesort(a , m+1 ,r);
  merge(a , l , m ,r);
}

void merge1(int a[], int left, int m, int right, int ide)   /*Funcao utilizada em L para ordenar*/
{
int i, j, k , aux[10000];
for (i = m+1; i > left; i--){
 aux[i-1] = a[i-1];}
for (j = m; j < right; j++){
 aux[right+m-j] = a[j+1];}
for (k = left; k <= right; k++){
 if ((strcmp(enco[ide].prode[aux[j]].des , enco[ide].prode[aux[i]].des) < 0 )) {
   a[k] = aux[j--];
 }
 else{
   a[k] = aux[i++];}
 }

}

 void mergesort1(int a[], int l, int r, int ide)   /*Funcao utilizada em L para ordenar*/
 {
   int m = (r+l)/2;
   if (r <= l) return;
   mergesort1(a , l, m, ide);
   mergesort1(a , m+1 ,r , ide);
   merge1(a , l , m ,r, ide);
 }

/*Corpo principal do programa*/

int main()
{

  char c;
  int qtd = 0, preco = 0 , idp = 0, ide = 0, x = 0 ,a[10000];   /*definicao de variaveis*/

  while (c != 'x')  /*Enquanto o programa nao acaba*/
  {
    switch (c = getchar())    /*Vamos analisar o primeiro espaco*/
    {

      case 'a':       /* se for a */
        getchar();    /* Passamos o espaco em branco */
        /* Iremos introduzir as variaveis pedidas de maneira a adicionarmos um novo produto ao sistema*/
        scanf("%[^:]:%d:%d:%d",prod[numero].des, &prod[numero].preco , &prod[numero].peso , &prod[numero].qtd );
        case_a(); /*Chamamos a funcao a */
        prod[numero].idp = numero;  /* numero variavel que incrementa conforme adicionamos novos  produtos*/
        numero ++;
        break;

      case 'q':   /* se for q */
        c = getchar(); /* Passamos o espaco em branco*/
        scanf("%d:%d", &idp , &qtd );  /* introduzir a quantidade de produto que queremos adicionar ao stock*/
        case_q(idp, qtd);   /* chamamos a funcao q */
        break;

      case 'N':   /* se for N */
        case_N();  /* Passamos o espaco em branco */
        enco[nenco].ide = nenco; /* nenco variavel que incrementa conforme adicionamos novas encomendas*/
        nenco ++;
        enco[nenco].cont = 0;
        break;

      case 'A':  /* se for A */
        getchar(); /* Passamos o espaco em branco */
        scanf("%d:%d:%d", &ide , &idp , &qtd ); /*introduzir qual a encomenda a que queremos adicionar uma certa quantidade de produto*/
        case_A(ide , idp , qtd); /* chamamos a funcao A */
        break;

      case 'r':    /* se for r */
        getchar();  /* passamos o espaco em branco*/
        scanf("%d:%d", &idp , &qtd );  /*introduzir qual a quantidade de produto que queremos retirar ao stock*/
        case_r( idp , qtd);   /* chamamos a funcao r */
        break;

      case 'R': /* se for R*/
        getchar();  /* passamos o espaco em branco*/
        scanf("%d:%d", &ide , &idp );  /*introduzir o produto que queremos retirar a encomenda*/
        case_R ( ide , idp); /* chamamos a funcao R*/
        break;

      case 'C':  /* se for C*/
        getchar();  /* passamos o espaco em branco*/
        scanf("%d", &ide );  /* introduzimos a encomenda cujo preco se pretende calcular */
        case_C(ide);  /* chamamos a funcao C */
        break;

      case 'p':   /* se for p */
        getchar(); /* passamos o espaco em branco */
        scanf("%d:%d", &idp , &preco ); /* introduzir o novo preco do produto que desejamos */
        case_p(idp , preco); /* chamamos a funcao p */
        break;

      case 'E':   /* se for E */
        getchar(); /* passamos o espaco em branco */
        scanf("%d:%d", &ide , &idp ); /* introduzir produto e encomenda que desejamos verificar */
        case_E(ide , idp);  /* chamamos a funcao E */
        break;

      case 'm':  /* caso seja m */
        getchar(); /* passamos o espaco em branco */
        scanf("%d", &idp ); /* Adicionamos o produto que queremos verificar onde mais existe */
        case_m( idp); /* chamamos a funcao m */
        break;

      case 'l':  /* se for l */
        while(x < numero){   /*enquanto x for menor do que numero produtos*/
          a[x] = x;
          x++;
        }
        mergesort(a , 0 , numero-1); /* chamar funcao que ordena */
        x = 0;
        printf("Produtos\n");
        while( x < numero){
        printf("* %s %d %d\n", prod[a[x]].des, prod[a[x]].preco , prod[a[x]].qtd ); x++;}
        break;

      case 'L':   /* caso seja L */
        getchar(); /* passamos espaco em branco */
        scanf("%d", &ide ); /* isnserimos o numero da encomenda cujos produtos desejamos ordenar */
        if ( enco[ide].ide != ide){
          printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide );
        }
        else{
          while(x < numero){   /*enquanto x for menor do que numero produtos*/
            a[x] = x;
            x++;
          }

          mergesort1(a , 0 , numero-1, ide); /* chamar funcao que ordena */
          x = 0;
          printf("Encomenda %d\n", ide);
          while( x < numero){
          if (enco[ide].prode[a[x]].idp == a[x]) {
                printf("* %s %d %d\n", enco[ide].prode[a[x]].des, prod[a[x]].preco , enco[ide].prode[a[x]].qtd );}
                x++;
        }
      }
        break;

      case 'x': /*caso seja x*/
        exit(0); /* acaba o programa */

    }
    c = getchar();
  }
  return 0;
}
