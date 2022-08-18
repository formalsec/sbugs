#include <stdio.h>
#include <string.h>

#define DESC_MAX 64
#define PROD_CAP 10000
#define ENC_CAP 500
#define PROD_POR_ENC_CAP 200

typedef int booleano;

/* falta fazer com que o mudar preco altere o prod_por_preco */

typedef struct
{
  char desc[DESC_MAX];
  int preco;
  int peso;
  int qtd;
  int idp;
} Produto;

typedef struct
{
  int idp[PROD_POR_ENC_CAP],qtd[PROD_POR_ENC_CAP],alfa[PROD_POR_ENC_CAP],peso,preco; /* idp e o array dos idps dos produtos da encomenda por ordem crescente*/
  signed int n; /*alfa e o array dos idps dos produtos da encomenda por ordem alfabetica*/
} Encomenda;

Produto prod[PROD_CAP+1];
Encomenda enc[ENC_CAP];
int naturais[PROD_CAP],aux[PROD_CAP];
signed int idp_max= -1 , ide_max = -1;

/*----------------------------------------------------------------
Devolve o index de um valor no array. Caso o valor nao esteja no array, o ultimo argumento define se queremos receber
(-1) ou o valor mais proximo ao local onde deveria estar*/

int binarySearch(int v[], int left, int b, int proc, int negativo)
{
    int meio = left + (b - left) / 2;
    if (b >= left)
    {
      if (v[meio] == proc)
        return meio;

      if (v[meio] > proc)
        return binarySearch(v, left, meio - 1, proc, negativo);

      return binarySearch(v, meio + 1, b, proc, negativo);
    }
    if (negativo==1)
      return -1;

    else
      return meio;
}

/*----------------------------------------------------------------
Binary search personalizado que ordena por ordem alfabetica a partir do array do idps, idps estes associados a uma string*/

int binarySearchStr(int v[], int left, int b, int idp)
{
    int meio = left + (b - left) / 2;
    if (b >= left)
    {
      if (strcmp( prod[v[meio]].desc , prod[idp].desc ) == 0 )
        return meio;

      if (strcmp( prod[v[meio]].desc , prod[idp].desc ) > 0)
        return binarySearchStr(v, left, meio - 1, idp);

      return binarySearchStr(v, meio + 1, b, idp);
    }
    return meio;
}

/*----------------------------------------------------------------
As duas funcoes abaixo juntas fazem o algoritmo merge sort*/

void merge(int a[], int left, int m, int right)
{
 int i, j, k;
 for (i = m+1; i > left; i--)
  aux[i-1] = a[i-1];
 for (j = m; j < right; j++)
  aux[right+m-j] = a[j+1];
 for (k = left; k <= right; k++)
  if ( (prod[aux[j]].preco < prod[aux[i]].preco) || i > m )
    a[k] = aux[j--];
  else
    a[k] = aux[i++];
}

void mergesort(int a[], int left, int right)
{
 int m = (right+left)/2;
 if (right <= left)
  return;
 mergesort(a, left, m);
 mergesort(a, m+1, right);
 merge(a, left, m, right);
}

/*----------------------------------------------------------------
Funcao que desloca um array a partir de um index chamado ponto, um numero de casas para a esquerda ou para a direita*/

void mover_array( int v[] , int dim , int ponto , int casas )
{
  int contador;
  if (casas<0)
  {
    for (contador=ponto+1; contador <=dim ; contador++)
        v[casas+contador] = v[contador];
  }

  else
  {
    for (contador = dim; contador>=ponto; contador--)
        v[casas+contador]= v[contador];
  }
}


/*----------------------------------------------------------------
Adiciona um produto ao sistema*/

void a()
{
  char desc[DESC_MAX];
  int preco,peso,qtd;

  scanf(" %[^:]:%d:%d:%d",desc,&preco,&peso,&qtd);

  idp_max++;

  strcpy(prod[idp_max].desc,desc);
  prod[idp_max].preco = preco;
  prod[idp_max].peso = peso;
  prod[idp_max].qtd = qtd;

  printf("Novo produto %d.\n",idp_max);

}

/*----------------------------------------------------------------
Adiciona stock a um produto*/

void q()
{
  int idp,qtd;

  scanf(" %d:%d",&idp,&qtd);

  if (idp>idp_max)
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);

  else
    prod[idp].qtd += qtd ;

}

/*----------------------------------------------------------------
Cria uma encomenda vazia*/

void N()
{
  ide_max++;
  enc[ide_max].n = -1 ;
  enc[ide_max].peso = 0;
  enc[ide_max].preco = 0;
  printf("Nova encomenda %d.\n",ide_max) ;
}

/*----------------------------------------------------------------
Adiciona um produto a uma encomenda*/

void A()
{
  int ide,idp,qtd,index;

  scanf(" %d:%d:%d",&ide,&idp,&qtd);

  if (ide>ide_max)
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);

  else if (idp>idp_max)
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);

  else if (prod[idp].qtd<qtd)
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);

  else
  {
    /*Agora ha duas opcoes, e o primeiro produto da encomenda ou nao*/

    if ( enc[ide].n == (-1) )
    {
      enc[ide].peso = prod[idp].peso * qtd ;

      if (enc[ide].peso <= 200)
      {
        enc[ide].n++;
        enc[ide].idp[0] = idp;
        enc[ide].qtd[0] = qtd;
        enc[ide].alfa[0] = idp;
        enc[ide].preco = prod[idp].preco * qtd ;

        prod[idp].qtd -= qtd ;
      }

      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp,ide) ;
        enc[ide].peso = 0 ;
      }
    }

    else
    {
      enc[ide].peso += prod[idp].peso * qtd ;

      if (enc[ide].peso <= 200)
      {
        index = binarySearch( enc[ide].idp , 0 , enc[ide].n , idp , 1 );

        if (index < 0) /* igual a dizer caso este produto ainda nao esteja na encomenda*/
        {
          index = binarySearch( enc[ide].idp , 0 , enc[ide].n , idp , 0 );/*posicao que o novo produto vai assumir na encomenda*/

          mover_array( (enc[ide].idp) , enc[ide].n , index, 1 );
          enc[ide].idp[index] = idp;

          mover_array( (enc[ide].qtd) , enc[ide].n , index, 1 );
          enc[ide].qtd[index] = qtd;

          index = binarySearchStr ( enc[ide].alfa , 0 , enc[ide].n , idp );

          mover_array( (enc[ide].alfa) , enc[ide].n , index, 1 );
          enc[ide].alfa[index] = idp;

          enc[ide].n++;
        }

        else
          enc[ide].qtd[index] += qtd ;

        enc[ide].preco += prod[idp].preco * qtd ;
        prod[idp].qtd -= qtd ;
      }

      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp,ide) ;
        enc[ide].peso -= prod[idp].peso * qtd ;
      }
    }


  }

}

/*----------------------------------------------------------------
Remove stock a um produto*/

void r()
{
  int idp,qtd;
  scanf(" %d:%d",&idp,&qtd);

  if (idp>idp_max)
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);

  else if (prod[idp].qtd < qtd)
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);

  else
    prod[idp].qtd -= qtd ;
}

/*----------------------------------------------------------------
Remove um produto a uma encomenda*/

void R()
{
  int ide,idp,index;
  scanf(" %d:%d",&ide,&idp);

  if (ide>ide_max)
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);

  else if (idp>idp_max)
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);

  index = binarySearch( enc[ide].idp , 0 , enc[ide].n , idp , 1 );

  if (index >= 0) /*Igual a dizer caso o produto esteja na encomenda*/
  {
    enc[ide].peso -= ( enc[ide].qtd[index] * prod[idp].peso ) ;
    enc[ide].preco -= ( enc[ide].qtd[index] * prod[idp].preco ) ;

    prod[idp].qtd += enc[ide].qtd[index] ;

    mover_array ( (enc[ide].idp) , enc[ide].n + 1  , index , -1 );
    mover_array ( (enc[ide].qtd) , enc[ide].n + 1  , index , -1 );

    index = binarySearchStr ( enc[ide].alfa , 0 , enc[ide].n , idp );

    mover_array ( (enc[ide].alfa) , enc[ide].n + 1 , index , -1 );
    enc[ide].n--;
  }


}

/*----------------------------------------------------------------
Printa o preco da encomenda, que ja esta esta guardado na instancia preco da struct*/

void C()
{
  int ide;
  scanf(" %d",&ide);

  if (ide>ide_max)
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);

  else
    printf("Custo da encomenda %d %d.\n",ide,enc[ide].preco);
}

/*----------------------------------------------------------------
Muda o preco de um produto*/

void p()
{
  int idp,preco,contador,index;
  scanf(" %d:%d",&idp,&preco);

  if (idp>idp_max)
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);

  else
  {
    for (contador = 0 ; contador <= ide_max ; contador++ ) /*Atualizo os precos das encomendas */
    {
      index = binarySearch( enc[contador].idp , 0 , enc[contador].n , idp , 1 );

      if (index>=0)
      {
        enc[contador].preco -= enc[contador].qtd[index] * prod[idp].preco ;
        enc[contador].preco += enc[contador].qtd[index] * preco ;
      }
    }

    prod[idp].preco = preco ;

  }
}

/*----------------------------------------------------------------
Printa a descricao e quantidade de um produto numa encomenda*/

void E()
{
  int ide,idp,index;
  scanf(" %d:%d",&ide,&idp);

  if (ide>ide_max)
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);

  else if (idp>idp_max)
    printf("Impossivel listar produto %d. Produto inexistente.\n",idp);

  else
  {
    index = binarySearch( enc[ide].idp , 0 , enc[ide].n , idp , 1 );
    printf("%s ", prod[idp].desc);

    if (index >= 0)
      printf("%d.\n",enc[ide].qtd[index]);

    else
      printf("0.\n");
  }
}

/*----------------------------------------------------------------
Retorna a encomenda que tem maior quantidade de um certo produto*/

void m()
{
  int idp,index,contador,qtd=0,ide_procurado;
  scanf(" %d",&idp);

  if (idp > idp_max)
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);

  else
  {
    for (contador = 0 ; contador <= ide_max ; contador++)
    {
      index = binarySearch (enc[contador].idp , 0 , enc[contador].n , idp , 1);

      if (index >= 0)
      {
        if ( enc[contador].qtd[index] > qtd )
        {
          ide_procurado = contador ;
          qtd = enc[contador].qtd[index] ;
        }
      }
    }

    if (qtd>0)
      printf("Maximo produto %d %d %d.\n",idp,ide_procurado,qtd);
  }

}

/*----------------------------------------------------------------
Printa os produtos por ordem de preco*/

void l()
{
  int contador,idp;

  printf("Produtos\n");

  for (contador=0;contador<=idp_max ; contador++)
    naturais[contador] = contador ;
  mergesort(naturais , 0 , idp_max);

  for (contador=0; contador<=idp_max; contador++)
  {
    idp = naturais[contador];
    printf("* %s %d %d\n",prod[idp].desc , prod[idp].preco , prod[idp].qtd);
  }
}

/*----------------------------------------------------------------
Lista os produtos de uma encomenda por ordem alfabetica*/

void L()
{
  int ide,idp,index,contador;
  scanf(" %d",&ide);

  if (ide>ide_max)
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);

  else
  {
    printf("Encomenda %d\n",ide);

    for (contador=0; contador<=enc[ide].n ; contador++)
    {
      idp = enc[ide].alfa[contador];
      index = binarySearch ( enc[ide].idp , 0 , enc[ide].n , idp , 1);
      printf("* %s %d %d\n", prod[idp].desc , prod[idp].preco , enc[ide].qtd[index] );
    }
  }
}

int main()
{

  char comando;

  while (comando!='x')
  {
    scanf("%s", &comando);

    switch(comando)
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
    }

  }
  return 0;
}
