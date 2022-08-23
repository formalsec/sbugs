#include <stdio.h>
#include <string.h>
#define DIM 10000
#define DESCRICAO 63
#define QUINHENTOS 500
#define DUZENTOS 200

int z = 0, i = 0, t = 0, novo[DIM]; /*z variavel que corresponde ao numero de produtos no sistema, i ao numero de encomendas */

struct produtos
{
    char descricao[DESCRICAO];
    int preco;
    int peso;
    int qtd;
};

struct produtos produtos[DIM];


struct encomendas
{  struct produtos produto[DUZENTOS]; /*estrutura de produtos*/
   int chegada[DUZENTOS];    /*recebe o numero correspondente ao numero de chegada a uma certa encomenda e devolve o idp desse produto*/
   int casamaxima;           /*numero de produtos distintos numa encomenda*/

};

struct encomendas encomendas[QUINHENTOS];


/*-----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/



/*-----------------------------------------------------------------*/                                /*1*/


void funcaoa(char arg1[], int arg2, int arg3, int arg4) /* adiciona um novo produto ao sistema */
{
    strcpy(produtos[z].descricao,arg1);
    produtos[z].preco = arg2;
    produtos[z].peso = arg3;
    produtos[z].qtd = arg4;

    printf("Novo produto %d.\n", z);

}


/*-----------------------------------------------------------------*/                                 /*2*/


void funcaoq(int arg2, int arg3) {                  /* adiciona stock a um produto existente no sistema*/

  if (arg2>z-1) {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n" , arg2);
  }
  else{
    produtos[arg2].qtd=produtos[arg2].qtd+arg3;


  }

}

/*-----------------------------------------------------------------*/                                   /*3*/

void funcaoN() {                                  /*cria uma nova encomenda*/
  printf("Nova encomenda %d.\n",i );
  i++;
}



/*-----------------------------------------------------------------*/



int peso_da_encomenda(int ide) {          /*calcular peso numa encomenda*/
  int x=0,t=0;

  while (x!=encomendas[ide].casamaxima){

    t+=encomendas[ide].produto[x].peso;        /*somar pesos de todos os produtos da encomenda*/

    x++;

  }
  return t;
}

/*-----------------------------------------------------------------*/                                   /*4*/

void funcaoA(int ide, int idp,int qtd) { /*adiciona um produto a uma encomenda.
  Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente*/

  int x=0;

  if (ide>i-1) {                                  /*ide> numero encomendas */
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n" , idp, ide);
    return;
  }
  else if (idp>z-1) {                             /*idp> numero produtos */
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n" , idp,ide);
    return;
  }
  else if (qtd>produtos[idp].qtd) {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n" , idp,ide);
    return;
  }
  else if((peso_da_encomenda(ide)+(produtos[idp].peso)*qtd)>DUZENTOS){   /*peso encomenda mais peso da qtd adicionada*/
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
    return;
  }

  while (x!=encomendas[ide].casamaxima){        /*percorrer casas numa encomenda*/
    if ((idp==encomendas[ide].chegada[x]))  {   /*se a encomenda ja tivesse idp atualizar respetivas qtds preco peso*/

        encomendas[ide].produto[x].qtd+= qtd;
        encomendas[ide].produto[x].preco=(produtos[idp].preco)*(encomendas[ide].produto[x].qtd);
        encomendas[ide].produto[x].peso=(produtos[idp].peso)*(encomendas[ide].produto[x].qtd);
        produtos[idp].qtd-=qtd;

        return;
      }
    x++;
  }

  x=encomendas[ide].casamaxima;           /*caso contrario ao de cima vamos meter quantidade e dar as caracteristicas do produto numa nova casa na encomenda ide casamaxima++;*/

    encomendas[ide].produto[x].qtd=qtd;
    encomendas[ide].produto[x].preco=(produtos[idp].preco)*(encomendas[ide].produto[x].qtd);
    encomendas[ide].produto[x].peso=(produtos[idp].peso)*(encomendas[ide].produto[x].qtd);
    encomendas[ide].chegada[x]=idp;
    produtos[idp].qtd-=qtd;
    strcpy(encomendas[ide].produto[x].descricao,produtos[idp].descricao) ;
    encomendas[ide].casamaxima++;

    return;



  }


/*-----------------------------------------------------------------*/                                   /*5*/

void funcaor(int idp, int qtd) {             /*remove stock a um produto existente*/

  if (idp>z-1) {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n" , idp);
    return;
  }
  else if((produtos[idp].qtd-qtd)<0){
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd, idp );
    return;
  }
  else{
  produtos[idp].qtd-=qtd;
  }
}

/*-----------------------------------------------------------------*/                                   /*6*/

void funcaoR(int ide, int idp) {          /*remove um produto de uma encomenda*/
  int x=0;
  if (ide>i-1) {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n" , idp,ide);
    return;
  }
  else if (idp>z-1) {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n" , idp,ide);
    return;
  }

    while (x!=encomendas[ide].casamaxima) {     /*remover todas qtd e peso na encomenda, somar qtd ao stock*/
      if (encomendas[ide].chegada[x]==idp){
        produtos[idp].qtd+=encomendas[ide].produto[x].qtd;
        encomendas[ide].produto[x].qtd=0;
        encomendas[ide].produto[x].peso=0;

        return;
        }
      x++;
      }

}

/*-----------------------------------------------------------------*/                                   /*7*/

void funcaoc(int ide) {   /*calcula o custo de uma encomenda*/

  int x=0,total=0,idp=0;

  if (ide>i-1) {

    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n" , ide);
    return;
  }
  while (x!=encomendas[ide].casamaxima){          /*percorrer todos produtos encomenda*/
    idp=encomendas[ide].chegada[x];
    encomendas[ide].produto[x].preco=(produtos[idp].preco)*(encomendas[ide].produto[x].qtd);    /*preco do produto vezes qtd na encomenda*/
    total=total+encomendas[ide].produto[x].preco;

    x=x+1;
  }
  printf("Custo da encomenda %d %d.\n",ide, total );
}





/*-----------------------------------------------------------------*/

void precos_encomendas(int idp) {       /*atualiza o preco dos produtos em cada encomenda*/
  int x=0,y=0;

  while (x<i){
    while (y<encomendas[x].casamaxima){
      if (encomendas[x].chegada[y]==idp){

    encomendas[x].produto[y].preco=(produtos[idp].preco)*(encomendas[x].produto[y].qtd);

  }
    y=y+1;
  }
  x++;
}

}

/*-----------------------------------------------------------------*/                                   /*8*/

void funcaop (int idp, int preco)  { /* altera o pre?o de um produto existente no sistema*/

  if (idp>z-1) {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n" , idp);
    return;
  }

  produtos[idp].preco=preco;
  precos_encomendas(idp);

}



/*-----------------------------------------------------------------*/                                   /*9*/

void funcaoE(int ide, int idp) {    /*lista a descricao e a quantidade de um produto numa encomenda*/
  int x=0;
  if (idp>z-1) {
    printf("Impossivel listar produto %d. Produto inexistente.\n" , idp);
    return;
  }
  else if (ide>i-1) {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n" , ide);
    return;
  }
    while (x!=encomendas[ide].casamaxima){

      if (idp==encomendas[ide].chegada[x]){

        printf("%s %d.\n",produtos[idp].descricao, encomendas[ide].produto[x].qtd );
        return;
      }


      x++;
    }
  printf("%s 0.\n",produtos[idp].descricao);                /*se produto nao tiver na encomenda*/
}

/*-----------------------------------------------------------------*/                                   /*10*/

void funcaom(int idp) { /*lista o identificador da encomenda em que o produto dado ocorre mais vezes.
   Se houver 2 ou mais encomendas nessa situacao, dever? imprimir a encomenda de menor id*/
  int x=0,p=0,max=0, idezao=0;

  if (idp>z-1) {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n" , idp);
    return;
  }

  while (p!=i) {      /*percorrer todas as encomendas ver se o id dado se encontra la*/


    while  (x<encomendas[p].casamaxima){

      if (idp==encomendas[p].chegada[x] && (encomendas[p].produto[x].qtd>max)){
        max=encomendas[p].produto[x].qtd;   /*novo maximo*/
        idezao=p;
      }
      x++;
    }
    p++;
    x=0;
  }
  if (max==0){
  return;
}
  printf("Maximo produto %d %d %d.\n",idp,idezao,max );

}

/*-----------------------------------------------------------------*/                                   /*11 */

int partition(int a[], int left, int right) {  /*quicksort*/

int i = left-1;
int t[DIM];
int j = right;
int v = a[right];

while (i < j) {

  while ((produtos[a[++i]].preco< produtos[v].preco)|| (v>a[i] && produtos[v].preco ==produtos[a[i]].preco ));    /*while less(a[++i], v) ou para v>a[i] e produtos[v]=produtos[a[i]]preco*/

  while ((produtos[v].preco< produtos[a[--j]].preco)|| (v<a[j] && produtos[v].preco ==produtos[a[j]].preco )){     /*while less*/

    if (j == left)
      break;
}
    if (i < j){

      t[0]=a[i];          /*mudanca de variavel*/
      a[i]=a[j];
      a[j]=t[0];}

}

t[0]=a[i];                  /*mudanca de variavel*/
a[i]=a[right];
a[right]=t[0];
return i;
}



/*-----------------------------------------------------------------*/




void quicksort(int a[], int left, int right)  /*recursiva*/
{

int i;

if (right <= left)
  return;
i = partition(a, left, right);
quicksort(a, left, i-1);
quicksort(a, i+1, right);


}

/*-----------------------------------------------------------------*/


void funcaol() {      /*inicializacao do quicksort, ordenar produtos por ordem de preco*/

  int o=0,t=0;
      while (o < z)
        {
          novo[o] = o;
          o++;
        }

    printf("Produtos\n" );
    quicksort(novo, 0, z - 1);
    while (t<z) {
      printf("* %s %d %d\n",produtos[novo[t]].descricao,produtos[novo[t]].preco, produtos[novo[t]].qtd);
        t++;
    }
}


/*-----------------------------------------------------------------*/                                   /*12*/

void mergedois(int a[], int left, int m, int right, int ide)        /*mergesort*/
{
int b, j, k ;
int aux[DIM];

for (b = m+1; b > left; b--){
  aux[b-1] = a[b-1];
}

for (j = m; j < right; j++) {
  aux[right+m-j] = a[j+1];
}

for (k = left; k <= right; k++){
  if ((strcmp(encomendas[ide].produto[aux[j]].descricao, encomendas[ide].produto[aux[b]].descricao)<0)|| b > m){  /*comparar string correspondente ao indice [aux[j]] com a do [aux[b]]*/
    a[k] = aux[j--];
  }

  else{
    a[k] = aux[b++];
  }
}

}


/*-----------------------------------------------------------------*/


void mergesortdois(int a[], int left, int right, int ide) /*recursiva*/
{

int m = (right+left)/2;

if (right <= left) {
  return;
}
mergesortdois(a, left, m, ide);
mergesortdois(a, m+1, right, ide);
mergedois(a, left, m, right, ide);
}


/*----------------------------------------------------------------*/


void funcaoL(int ide) { /*inicializar merge sort, ordenar produtos por ordem alfabetica numa encomenda*/

  int arg2=0,t=0,idps=0;

  if (ide>i-1) {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide );
    return;
  }
  printf("Encomenda %d\n",ide );


  while (arg2!=encomendas[ide].casamaxima) {    /*numero de produtos numa encomenda*/

    novo[arg2] = arg2;
    arg2++;
  }
  mergesortdois(novo, 0, encomendas[ide].casamaxima-1, ide);
  while (t<encomendas[ide].casamaxima) {                    /*correr produtos na encomenda*/
        idps=encomendas[ide].chegada[novo[t]];
        if (encomendas[ide].produto[novo[t]].qtd!=0) {
        printf("* %s %d %d\n",encomendas[ide].produto[novo[t]].descricao,produtos[idps].preco, encomendas[ide].produto[novo[t]].qtd);
        }

         t++;
     }
}

/*-----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/
int main()    /*MAIN*/
{

    char c, arg1[DIM];
    int arg2, arg3, arg4 ,ide;

    for (;;)
    {

        switch (c = getchar())
        {
        case 'a':
            scanf(" %[^:]:%d:%d:%d", arg1, &arg2, &arg3, &arg4);
            funcaoa(arg1, arg2, arg3, arg4);
            z++;

            break;

        case 'q':
            scanf(" %d:%d", &arg2,&arg3);
            funcaoq(arg2,arg3);
            break;

        case 'N':
            funcaoN();
            break;

        case 'A':
            scanf(" %d:%d:%d", &arg2,&arg3,&arg4);
            funcaoA(arg2,arg3,arg4);

            break;

        case 'r':
            scanf(" %d:%d", &arg2, &arg3);
            funcaor(arg2, arg3);

            break;

        case 'R':
            scanf(" %d:%d", &arg2, &arg3);
            funcaoR(arg2, arg3);
            break;

        case 'C':
            scanf(" %d", &arg2);
            funcaoc(arg2);
            break;

        case 'p':
            scanf(" %d:%d", &arg2, &arg3);
            funcaop(arg2, arg3);


            break;

        case 'E':
            scanf(" %d:%d", &arg2, &arg3);
            funcaoE(arg2, arg3);


            break;

        case 'm':

            scanf( "%d", &arg2);
            funcaom(arg2);
            break;

        case 'l':
            funcaol();
            break;

        case 'L':
          scanf(" %d",&ide );
          funcaoL(ide);

            break;

        case 'x':

            return 0;

            break;

        default:

          break;
      }
    }
return 0;
}
