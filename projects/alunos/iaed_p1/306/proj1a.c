#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
typedef int Item;
#define key(A) (A) /* abstracoes algoritmos ordenacao */
#define less(A, B) (key(A) < key(B))
#define less_str(A, B) (strcmp(key(A), key(B)) < 0)
#define exch(A, B) { Item t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)
#define MAX_P 10000 /* max produtos diferentes */
#define MAX_DESC 63 /* max chars da descricao de um produto */
#define MAX_E 500  /* max encomendas possiveis */
#define MAX_PESO  200 /* max peso de uma encomenda */
#define ZERO 0
Item aux[MAX_P]; /* vetores auxilixares mergesort */
Item aux1[MAX_P];
int idp = 0, ide = 0;  /* identificador de cada produto / encomenda */
int idp_aux, ide_aux, qtd, preco_aux;/*vars para ler o input/aceder as structs*/

typedef struct{  /* guarda os dados de cada produto */
  char descricao[MAX_DESC];
  int preco, peso, quantidade;
} produto;

typedef struct{ /* guarda os dados de cada encomenda */
  int qtd_prod[MAX_P]; /* quantidade de um certo produto na encomenda */
  int preco, peso; /* total na encomenda */
  int contador; /* numero de produtos por encomenda */
} encomenda;

produto produtos[MAX_P]; /* vetor para guardar todos os produtos */
encomenda encomendas[MAX_E] = {0}; /* vetor para guardar todas as encomendas */

void merge(Item a[], Item b[], int l, int m, int r){ /* funcao aux mergesort */
  int i, j, k;
  for (i = m + 1; i > l; i--){ /*copia os vetores para vetores auxiliares */
    aux[i - 1] = a[i - 1];
    aux1[i - 1] = b[i - 1];
  }
  for (j = m; j < r; j++){
    aux[r + m - j] = a[j + 1];
    aux1[r + m - j] = b[j + 1];
  }
  for(k = l; k <= r; k++)
    if (less(aux[j],aux[i]) || i > m){ /* compara os precos */
      b[k] = aux1[j];  /* ordena os idps */
      a[k] = aux[j--]; /* ordena os precos */
    }
    else{
      b[k] = aux1[i];
      a[k] = aux[i++];
    }
}

void mergesort(Item a[],Item b[], int l, int r){ /*ordena os precos e os idps*/
  int m = (r + l) / 2; /* indice do meio do vetor a ordenar */
  if (r <= l)
    return;
  mergesort(a, b, l, m); /* ordena a primeira metade do vetor */
  mergesort(a, b, m + 1, r); /* ordena a segunda metade */
  merge (a, b, l, m, r); /* junta cada parte por ordem */
}

void InsertionSort_str(char a[MAX_P][MAX_DESC], int l, int r){
  int i;
  for (i = l + 1; i <= r; i++){
    int j;
    char v[MAX_DESC];
    strcpy(v, a[i]);
    j = i-1;
    while (j >= l && less_str(v,a[j])){ /* verifica a ordem das strings */
      strcpy(a[j + 1], a[j]); /* troca se a ordem for incorreta */
      j--;
    }
    strcpy(a[j + 1], v);
  }
}

void a (){ /* cria um novo produto*/
  scanf(" %[^:]:%d:%d:%d", produtos[idp].descricao, &produtos[idp].preco,
    &produtos[idp].peso, &produtos[idp].quantidade);
  printf("Novo produto %d.\n", idp);
  idp ++;
}


void q(){ /* adiciona stock a um produto */
  scanf("%d:%d", &idp_aux, &qtd);
  if (idp_aux < idp)  /* so altera se o produto existir */
    produtos[idp_aux].quantidade += qtd;
  else
    printf("Impossivel adicionar produto %d ao stock."
    " Produto inexistente.\n", idp_aux);
}

void N (){ /* cria uma nova encomenda */
  printf("Nova encomenda %d.\n", ide);
  ide ++;
}

void A(){  /* adiciona um produto a uma encomenda */
  scanf("%d:%d:%d", &ide_aux, &idp_aux, &qtd);
  if (ide_aux >= ide)
    printf("Impossivel adicionar produto %d a encomenda %d."
    " Encomenda inexistente.\n", idp_aux, ide_aux);
  else if (idp_aux >= idp)
    printf("Impossivel adicionar produto %d a encomenda %d."
    " Produto inexistente.\n", idp_aux, ide_aux);
  else if (qtd > produtos[idp_aux].quantidade)
    printf("Impossivel adicionar produto %d a encomenda %d."
    " Quantidade em stock insuficiente.\n", idp_aux, ide_aux);
  else if ((qtd * produtos[idp_aux].peso) + encomendas[ide_aux].peso > MAX_PESO)
    printf("Impossivel adicionar produto %d a encomenda %d."
    " Peso da encomenda excede o maximo de 200.\n", idp_aux, ide_aux);
  else{
    encomendas[ide_aux].qtd_prod[idp_aux] += qtd; /* qtd de cada produto */
    encomendas[ide_aux].peso += (produtos[idp_aux].peso * qtd);
    encomendas[ide_aux].preco += (produtos[idp_aux].preco * qtd);
    encomendas[ide_aux].contador ++;
    produtos[idp_aux].quantidade -= qtd;/*retira do produto o stock adicionado*/
  }
}

void r(){ /* remove stock a um produto */
  scanf("%d:%d", &idp_aux, &qtd);
  if (idp_aux >= idp)
    printf("Impossivel remover stock do produto %d."
    " Produto inexistente.\n", idp_aux);
  else if (produtos[idp_aux].quantidade - qtd < 0) /* qtd total-qtd a retirar */
    printf("Impossivel remover %d unidades do produto %d do stock."
    " Quantidade insuficiente.\n",qtd, idp_aux);
  else
    produtos[idp_aux].quantidade -= qtd;
}

void R(){ /* remove um produto de uma encomenda */
  scanf("%d:%d", &ide_aux, &idp_aux);
  if (ide_aux >= ide)
    printf("Impossivel remover produto %d a encomenda %d."
    " Encomenda inexistente.\n", idp_aux, ide_aux);
  else if (idp_aux >= idp)
    printf("Impossivel remover produto %d a encomenda %d."
    " Produto inexistente.\n", idp_aux, ide_aux);
  else{
    qtd = encomendas[ide_aux].qtd_prod[idp_aux];
    if (qtd > 0){ /* apenas se o produto existir na encomenda */
      produtos[idp_aux].quantidade += qtd; /* repoe o stock */
      encomendas[ide_aux].peso -= (produtos[idp_aux].peso * qtd);
      encomendas[ide_aux].preco -= (produtos[idp_aux].preco * qtd);
      encomendas[ide_aux].qtd_prod[idp_aux] = 0;
      encomendas[ide_aux].contador --;
    }
  }
}

void C(){ /* calcula o custo de uma encomenda */
  scanf("%d", &ide_aux);
  if (ide_aux >= ide)
    printf("Impossivel calcular custo da encomenda %d."
    " Encomenda inexistente.\n", ide_aux);
  else
    printf("Custo da encomenda %d %d.\n", ide_aux, encomendas[ide_aux].preco);
}

void p(){ /* altera o preco de um produto */
  scanf("%d:%d", &idp_aux, &preco_aux);
  if (idp_aux >= idp)
    printf("Impossivel alterar preco do produto %d."
    " Produto inexistente.\n", idp_aux);
  else{
    int i;
    for (i = 0; i < ide; i++){ /*altera o preco do produto nas encomendas*/
      qtd = encomendas[i].qtd_prod[idp_aux];
      encomendas[i].preco -= (produtos[idp_aux].preco * qtd);
      encomendas[i].preco += (preco_aux * qtd);
    }
    produtos[idp_aux].preco = preco_aux; /* altera o preco do produto */
  }
}

void E(){ /* lista a descricao e a quantidade de um prod numa encomenda */
  scanf("%d:%d", &ide_aux, &idp_aux);
  if (ide_aux >= ide)
    printf("Impossivel listar encomenda %d."
    " Encomenda inexistente.\n", ide_aux);
  else if (idp_aux >= idp)
    printf("Impossivel listar produto %d."
    " Produto inexistente.\n", idp_aux);
  else
    printf("%s %d.\n", produtos[idp_aux].descricao,
    encomendas[ide_aux].qtd_prod[idp_aux]);
}

void m(){ /* lista o ide em que um produto ocorre mais vezes */
  scanf("%d", &idp_aux);
  if (idp_aux >= idp)
    printf("Impossivel listar maximo do produto %d."
    " Produto inexistente.\n", idp_aux);
  else{
    int i, max = 0; /* max = maior qtd do prod numa certa encomenda */
    for (i = 0; i < ide; i++)
      if (encomendas[i].qtd_prod[idp_aux] > max){
        max = encomendas[i].qtd_prod[idp_aux]; /* atualiza o max */
        ide_aux = i; /* ide onde o produto ocorre mais */
      }
    if (max > 0) /* so se existir alguma encomenda com o produto */
      printf("Maximo produto %d %d %d.\n", idp_aux, ide_aux, max);
  }
}

void l (){ /* lista todos os produtos por ordem crescente de preco */
  int i, precos[MAX_P], indices[MAX_P];
  printf("Produtos\n");
  for (i = 0; i < idp; i++){  /* cria vetores com todos os precos / idps */
    precos[i] = produtos[i].preco;
    indices[i] = i;
  }
  mergesort(precos, indices, 0, idp - 1);/*sort dos idps de acordo com os precos*/
  for (i = 0; i < idp; i++) /* print a partir dos idps ordenados */
    printf("* %s %d %d\n", produtos[indices[i]].descricao,
    produtos[indices[i]].preco, produtos[indices[i]].quantidade);
}

void L_aux(char str[MAX_P][MAX_DESC], int contador){ /*atribui strs -> prods */
  int i, j;
  for (i = 0; i < contador; i++)
    for (j = 0; j < idp; j++)  /*verifica se a str corresponde ao produto[j]*/
      if (strcmp(str[i], produtos[j].descricao) == 0){
        printf("* %s %d %d\n", str[i], /*se corresponder faz print do produto*/
        produtos[j].preco,
        encomendas[ide_aux].qtd_prod[j]);
        break; /* passa ao proximo produto */
      }
}

void L(){  /* lista todos os produtos de uma encomenda por ordem alfabetica */
  scanf("%d", &ide_aux);
  if (ide_aux >= ide)
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
  else{
    int i, j = 0, contador;
    char str[MAX_P][MAX_DESC] = {0};
    contador = encomendas[ide_aux].contador;/*numero de produtos na encomenda*/
    printf("Encomenda %d\n", ide_aux);
    for (i = 0; i < idp; i++) /* itera sobre todos os produtos da encomenda */
        /* se o prod existir na encomenda */
        if (encomendas[ide_aux].qtd_prod[i] > 0){
          strcpy(str[j], produtos[i].descricao);/*copia desc -> vetor de strs*/
          j ++; /* itera sobre o vetor das descricoes */
        }
    /* ordena o vetor das descricoes alfabeticamente */
    InsertionSort_str(str, 0, contador - 1);
    L_aux(str, contador); /*lista os prods da encomenda com as strs ordenadas*/
  }
}

int main(){  /* Le n comandos do stdin e executa cada um deles  */
  char command; /* guarda o comando a ler / executar */
  while ((command = getchar()) != 'x'){  /* x para terminar o programa */
    switch (command) { /* le e executa cada comando */
      case 'a': a(); break;
      case 'q': q(); break;
      case 'N': N(); break;
      case 'A': A(); break;
      case 'r': r(); break;
      case 'R': R(); break;
      case 'C': C(); break;
      case 'p': p(); break;
      case 'E': E(); break;
      case 'm': m(); break;
      case 'l': l(); break;
      case 'L': L(); break;
    }
    getchar();  /* Le o '\n' */
  }
  return 0;
}
