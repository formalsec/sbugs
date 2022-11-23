#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>


/* definicao de constantes a utilizar ao longo do programa */
/* a descricao do produto tem no maximo 63 caracteres */
#define MAX_DESCRICAO 63
/* existem no maximo 10000 produtos diferentes */
#define MAX_PRODUTOS 10000
/* existem no maximo um numero de 500 encomendas */
#define MAX_ENCOMENDAS 500
/* cada encomenda podera pesar no maximo 200 unidades de peso */
#define MAX_PESO 200


/* inicializacao da estrutura produto e da estrutura encomenda */
typedef struct Produto{
  int identificador;
  char descricao[MAX_DESCRICAO];
  int preco;
  int peso;
  int quantidade;
}Produto;

typedef struct Encomenda{
  int ide;
  int tabela[MAX_PRODUTOS];
}Encomenda;


/* inicializacao de funcoes a utilizar */
int a(Produto sistema[]);
int q(Produto sistema[]);
int N(Encomenda encomendas[]);
int A(Encomenda encomendas[], Produto sistema[]);
int r(Produto sistema[]);
int R(Encomenda encomendas[]);
int C(Encomenda encomendas[], Produto sistema[]);
int p(Produto sistema[]);
int E(Encomenda encomendas[], Produto sistema[]);
int m(Encomenda encomendas[]);
int l(Produto sistema[], Produto auxiliar[]);
int L(Encomenda encomendas[], Produto sistema[], Produto auxiliar[]);

void copia(Produto sistema[], Produto auxiliar[]);
void mergesort_L(Produto auxiliar[], int left, int right);
void merge_L(Produto auxiliar[], int left, int m, int right);
void mergesort_l(Produto auxiliar[], int left, int right);
void merge_l(Produto auxiliar[], int left, int m, int right);


/* inicializacao de variaveis globais */
/* sistema[] vai ter todos os produtos existentes */
Produto sistema[MAX_PRODUTOS];
/* encomendas[] vai ter todas as encomendas existentes */
Encomenda encomendas[MAX_ENCOMENDAS];
/* auxiliar[] vai ser utilizado para ordenar os produtos do sistema */
Produto auxiliar[MAX_PRODUTOS];
/* contador que guarda o numero de produtos criados */
int num_produtos = 0;
/* contador que guarda o numero de encomendas criadas */
int num_encomendas = 0;


/* funcao principal int main() */
int main(){
  char c;
  /* para verificar a existencia da encomenda 0 e do produto 0 */
  encomendas[0].ide = -1;
  sistema[0].identificador = -1;

  c = getchar();
  while (c!='x'){
    switch (c){
        case 'a':
          a(sistema);
          num_produtos++;
          break;
        case 'q':
          q(sistema);
          break;
        case 'N':
          N(encomendas);
          num_encomendas++;
          break;
        case 'A':
          A(encomendas, sistema);
          break;
        case 'r':
          r(sistema);
          break;
        case 'R':
          R(encomendas);
          break;
        case 'C':
          C(encomendas, sistema);
          break;
        case 'p':
          p(sistema);
          break;
        case 'E':
          E(encomendas, sistema);
          break;
        case 'm':
          m(encomendas);
          break;
        case 'l':
          l(sistema, auxiliar);
          break;
        case 'L':
          L(encomendas, sistema, auxiliar);
          break;
    }
    c = getchar();
  }
  return 0;
}


/* 1? comando: a - adiciona um novo produto ao sistema */
int a(Produto sistema[]){
  /* variavel estatica i1 que vai armazenar o numero do produto a criar */
  static int i1 = 0;

  if (i1<MAX_PRODUTOS){
    scanf(" %[^:]:%d:%d:%d", sistema[i1].descricao, &sistema[i1].preco, &sistema[i1].peso, &sistema[i1].quantidade);
    /* criacao do produto por atribuicao de valor i1 a identificador */
    sistema[i1].identificador = i1;
    printf("Novo produto %d.\r\n", i1);
  }
  return i1++;
}


/* 2? comando: q - adiciona stock a um produto existente no sistema */
int q(Produto sistema[]){
  int idp;
  int qtd, i2;

  scanf(" %d:%d", &idp, &qtd);
  /* caso em que o produto 0 ainda nao foi criado */
  if (idp==0 && sistema[0].identificador == -1){
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\r\n", idp);
    return 0;
  }
  for (i2=0; i2<MAX_PRODUTOS;i2++){
    if(sistema[i2].identificador==idp){
      sistema[i2].quantidade = sistema[i2].quantidade + qtd;
      return 0;
    }
  }
  printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\r\n", idp);
  return 0;
}


/* 3? comando: N - cria um nova encomenda */
int N(Encomenda encomendas[]){
  /* variavel estatica i3 que vai armazenar o numero da encomenda a criar */
  static int i3 = 0;

  if (i3<MAX_ENCOMENDAS){
    printf("Nova encomenda %d.\r\n", i3);
    /* criacao da encomenda por atribuicao de valor i3 a ide */
    encomendas[i3].ide=i3;
  }
  return i3++;
}


/* 4? comando: A - adiciona um produto a uma encomenda */
int A(Encomenda encomendas[], Produto sistema[]){
  int ide, idp, qtd;
  int i4;
  int pesototal=0;
  scanf(" %d:%d:%d", &ide, &idp, &qtd);

  /* verificacao da existencia do produto */
  if (idp>=num_produtos){
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\r\n", idp, ide);
    return 0;
  }
  /* verificacao da existecia da encomenda */
  if (ide>=num_encomendas){
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\r\n", idp, ide);
    return 0;
  }

  /* calculo do peso da encomenda */
  for (i4=0; i4<num_produtos; i4++){
    pesototal=pesototal+(encomendas[ide].tabela[i4]*sistema[i4].peso);
  }
  /* verificacao da quantidade e do peso */
  if (sistema[idp].quantidade>=qtd){
    if (((qtd*sistema[idp].peso) + pesototal) <= 200){
      pesototal = pesototal + (qtd*sistema[idp].peso);
      /* atualizar a quantidade na encomenda e no stock */
      encomendas[ide].tabela[idp]=encomendas[ide].tabela[idp]+qtd;
      sistema[idp].quantidade=sistema[idp].quantidade-qtd;
      return 0;
    }
    else{
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\r\n", idp, ide);
      return 0;
    }
  }
  else{
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\r\n", idp, ide);
    return 0;
  }
}


/* 5? comando: r - remove stock a um produto existente */
int r(Produto sistema[]){
  int i5;
  int idp, qtd;

  scanf(" %d:%d", &idp, &qtd);

 /* procura nas encomendas o produto introduzido e coloca a quantidade a 0 */
  for (i5=0; i5<=num_produtos; i5++){
    if (sistema[i5].identificador==idp){
      if (sistema[i5].quantidade-qtd>=0){
        sistema[i5].quantidade=sistema[i5].quantidade-qtd;
        return 0;
      }
      else{
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\r\n", qtd, idp);
        return 0;
      }
    }
    else if(sistema[i5].identificador!=idp){
      if (i5==num_produtos){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\r\n", idp);
        return 0;
      }
      continue;
    }
  }
  return 0;
}


/* 6? comando: R - remove um produto de uma encomenda */
int R(Encomenda encomendas[]){
  int ide, idp;
  int i6, j6;
  /* quantidade a remover do produto, adicionando no sistema */
  int remover;

  scanf(" %d:%d", &ide, &idp);

  for (i6=0; i6<=num_encomendas; i6++){
    if (encomendas[i6].ide == ide){
      for (j6=0; j6<=num_produtos; j6++){
        if (sistema[j6].identificador==idp){
          remover=encomendas[i6].tabela[j6];
          encomendas[i6].tabela[j6] = 0;
          sistema[idp].quantidade = sistema[idp].quantidade + remover;
          return 0;
        }
        else if(sistema[j6].identificador!=idp){
          if (j6==num_produtos){
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\r\n", idp, ide);
            return 0;
          }
          continue;
        }
      }
    }
    else if(encomendas[i6].ide!=ide){
      if (i6==num_encomendas){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\r\n", idp, ide);
        return 0;
      }
      continue;
    }
  }
  return 0;
}


/* 7? comando: C - calcula o custo de uma encomenda */
int C(Encomenda encomendas[], Produto sistema[]){
  int i7, j7;
  int ide;
  int custo=0;

  scanf(" %d", &ide);

  for (i7=0; i7<=num_encomendas; i7++){
    if (encomendas[i7].ide==ide){
      for (j7=0; j7<num_produtos; j7++){
        if(encomendas[i7].tabela[j7]!=0){
          custo = custo + (encomendas[i7].tabela[j7] * sistema[j7].preco);
        }
      }
      printf("Custo da encomenda %d %d.\r\n", ide, custo);
      return 0;
    }
    else if(encomendas[i7].ide!=ide){
      if (i7==num_encomendas){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\r\n", ide);
        return 0;
      }
      continue;
    }
  }
  return 0;
}


/* 8? comando: p - altera o preco de um produto existente no sistema */
int p(Produto sistema[]){
  int i8;
  int idp, preco;

  scanf(" %d:%d", &idp, &preco);

  for (i8=0; i8<=num_produtos; i8++){
    if (sistema[i8].identificador==idp){
      sistema[i8].preco = preco;
      return 0;
    }
    else if(sistema[i8].identificador!=idp){
      if (i8==num_produtos){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\r\n", idp);
        return 0;
      }
    continue;
    }
  }
  return 0;
}


/* 9? comando: E - retorna a descricao e a quantidade de um produto numa dada encomenda */
int E(Encomenda encomendas[], Produto sistema[]){
  int i9, j9=0;
  int ide, idp;

  scanf(" %d:%d", &ide, &idp);

  /* caso do produto 0 nao existir */
  if (idp==0 && sistema[0].identificador == -1){
    printf("Impossivel listar produto %d. Produto inexistente.\r\n", idp);
    return 0;
  }
  for (i9=0; i9<=num_encomendas;i9++){
      if (encomendas[i9].ide==ide){
        for (j9=0; j9<=num_produtos; j9++){
          if (sistema[j9].identificador == idp){
            /* encontrei o produto */
            printf("%s %d.\r\n", sistema[j9].descricao, encomendas[i9].tabela[idp]);
            return 0;
          }
          else if(sistema[j9].identificador!=idp){
            if (j9==num_produtos){
              printf("Impossivel listar produto %d. Produto inexistente.\r\n", idp);
              return 0;
            }
            continue;
          }
        }
      }
      else if(encomendas[i9].ide!=ide){
        if (i9==num_encomendas){
          printf("Impossivel listar encomenda %d. Encomenda inexistente.\r\n", ide);
          return 0;
        }
        continue;
      }
    }
    return 0;
  }


/* 10? comando: m - retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
int m(Encomenda encomendas[]){
  int idp;
  int i;
  /* int maior -> maior quantidade encontrada do produto */
  int maior=0;
  /* int idefinal -> identificador da encomenda que tem o produto com maior quantidade */
  int idefinal=0;
  int idpexiste=0;

  scanf(" %d", &idp);

  /* verificacao da existencia do produto */
  if (idp>=num_produtos){
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\r\n", idp);
    return 0;
  }

  /* percorrer as encomendas, e encontrar o valor maior para o produto */
  for(i=0; i<num_encomendas; i++){
    if(encomendas[i].tabela[idp]>maior){
      maior=encomendas[i].tabela[idp];
      idefinal=i;
      idpexiste++;
    }
  }
  if(idpexiste!=0){
    printf("Maximo produto %d %d %d.\r\n", idp, idefinal, maior);
    return 0;
  }
  else if (idpexiste==0){
    return 0;
  }
  return 0;
}


/* 11? comando: l - lista todos os produtos existentes no sistema por ordem crescente de pre?o */
int l(Produto sistema[], Produto auxiliar[]){
  int i;
  int left=0;
  int right=num_produtos;

  /* copiar todos os produtos do sistema para um auxiliar para ordenar */
  copia(sistema, auxiliar);
  /* utilizacao do algoritmo de ordenacao mergesort_l */
  mergesort_l(auxiliar, left, right-1);

  printf("Produtos\r\n");
  for (i=left; i<right; i++){
    /* quer dizer que produto existe */
    if (auxiliar[i].preco!=0){
      printf("* %s %d %d\r\n", auxiliar[i].descricao, auxiliar[i].preco, auxiliar[i].quantidade);
    }
  }
  return 0;
}


/* 12? comando: L - lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
int L(Encomenda encomendas[], Produto sistema[], Produto auxiliar[]){
  int ide, i;
  int left=0;
  int right=num_produtos;

  scanf(" %d", &ide);

  /* caso da encomenda 0 nao existir */
  if (ide==0 && encomendas[0].ide==-1){
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\r\n", ide);
    return 0;
  }

  /* se a encomenda nao exitir, o ide dado >= ao numero de encomendas */
   if (ide>=num_encomendas){
     printf("Impossivel listar encomenda %d. Encomenda inexistente.\r\n", ide);
     return 0;
   }
   /* copiar todos os produtos do sistema para um auxiliar para ordenar */
   copia(sistema, auxiliar);

   mergesort_L(auxiliar, left, right-1);
   printf("Encomenda %d\r\n", ide);

   for (i=0; i<num_produtos; i++){
     if (encomendas[ide].tabela[auxiliar[i].identificador]!=0 && auxiliar[i].preco !=0){
       printf("* %s %d %d\r\n", auxiliar[i].descricao, auxiliar[i].preco, encomendas[ide].tabela[auxiliar[i].identificador]);
     }
   }
   return 0;
 }


/* funcao que copia produtos do sistema para vetor de produtos auxiliar */
void copia(Produto sistema[], Produto auxiliar[]){
  int i;
  for(i=0; i<num_produtos; i++){
    auxiliar[i]=sistema[i];
  }
}

/* algoritmo para ordenar por descricao no comando L */
void mergesort_L(Produto auxiliar[], int left, int right){
  int m = (right+left)/2;
  if(right<=left)
    return;
  mergesort_L(auxiliar, left, m);
  mergesort_L(auxiliar, m+1, right);
  merge_L(auxiliar, left, m, right);
}
/* funcao chamada no mergesort_L */
void merge_L(Produto auxiliar[], int left, int m, int right){
  int i, j, k;
  Produto aux[MAX_PRODUTOS];

  for(i=m+1; i>left; i--)
    aux[i-1]= auxiliar[i-1];
  for(j=m; j<right; j++)
    aux[right+m-j] = auxiliar[j+1];

  for(k=left; k<=right; k++){
    if(strcmp(aux[j].descricao, aux[i].descricao)<0)
      auxiliar[k] = aux[j--];
    else
      auxiliar[k]=aux[i++];
  }
}

/* algortimo para ordenar por preco no comando l */
void mergesort_l(Produto auxiliar[], int left, int right){
  int m = (right+left)/2;
  if(right<=left)
    return;
  mergesort_l(auxiliar, left, m);
  mergesort_l(auxiliar, m+1, right);
  merge_l(auxiliar, left, m, right);
}
/* funcao chamada no mergesort_l */
void merge_l(Produto auxiliar[], int left, int m, int right){
  int i, j, k;
  Produto aux[MAX_PRODUTOS];

  for(i=m+1; i>left; i--)
    aux[i-1]= auxiliar[i-1];
  for(j=m; j<right; j++)
    aux[right+m-j] = auxiliar[j+1];

  for(k=left; k<=right; k++){
    if(aux[j].preco < aux[i].preco)
      auxiliar[k] = aux[j--];
    /* caso o preco seja igual, tenho que comparar os identificadores */
    else if(aux[j].preco==aux[i].preco){
      if (aux[j].identificador<aux[i].identificador){
        auxiliar[k] = aux[j--];
      }
      else{
        auxiliar[k]=aux[i++];
      }
    }
    else
      auxiliar[k]=aux[i++];
  }
}
