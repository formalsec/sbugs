#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PMAX 10000
#define EMAX 500
#define IMAX 78
#define DMAX 64
#define WMAX 200
#define PRECOMAX 20000

typedef struct{
   int Identificacao;
   int Preco;
   int Peso;
   int Quantidade;
   char Descricao[IMAX];
} produto;
produto todos_produtos[PMAX];
int qtd_produtos = 0;

typedef struct{
   int Quantidade[PMAX];
   int Peso;
} encomenda;
encomenda todas_encomendas[EMAX];
int qtd_encomendas = 0;

void err(char tipo[], int idp, int ide, int qtd){
  if (!strcmp(tipo,"q1")) printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  else if (!strcmp(tipo,"A1")) printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  else if (!strcmp(tipo,"A2")) printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  else if (!strcmp(tipo,"A3")) printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
  else if (!strcmp(tipo,"A4")) printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
  else if (!strcmp(tipo,"r1")) printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  else if (!strcmp(tipo,"r2")) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
  else if (!strcmp(tipo,"R1")) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  else if (!strcmp(tipo,"R2")) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  else if (!strcmp(tipo,"C1")) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  else if (!strcmp(tipo,"p1")) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  else if (!strcmp(tipo,"E1")) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  else if (!strcmp(tipo,"E2")) printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  else if (!strcmp(tipo,"m1")) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  else if (!strcmp(tipo,"L1")) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}
void adicionaproduto(char descricao[64], int preco, int peso, int qtd){
  strcpy(todos_produtos[qtd_produtos].Descricao,descricao);
  todos_produtos[qtd_produtos].Preco = preco;
  todos_produtos[qtd_produtos].Peso = peso;
  todos_produtos[qtd_produtos].Quantidade = qtd;
  todos_produtos[qtd_produtos].Identificacao = qtd_produtos;
  qtd_produtos++;
  printf("Novo produto %d.\n",qtd_produtos-1);
}
void adicionastock(int idp, int qtd){
  if(idp >= qtd_produtos)
    err("q1",idp,-1,-1);
  else
    todos_produtos[idp].Quantidade += qtd;
}
void criaencomenda(){
  printf("Nova encomenda %d.\n",qtd_encomendas);
  memset(todas_encomendas[qtd_encomendas].Quantidade,0,sizeof(todas_encomendas[qtd_encomendas].Quantidade));
  qtd_encomendas++;
}
void adicionaprodaenc(int ide, int idp, int qtd){
  if(ide >= qtd_encomendas)
    err("A1",idp,ide,-1);
  else if(idp >= qtd_produtos)
    err("A2",idp,ide,-1);
  else if(qtd > todos_produtos[idp].Quantidade)
    err("A3",idp,ide,-1);
  else if(todas_encomendas[ide].Peso + (qtd * todos_produtos[idp].Peso) > WMAX)
    err("A4",idp,ide,-1);
  else{
    todos_produtos[idp].Quantidade -= qtd;
    todas_encomendas[ide].Peso += todos_produtos[idp].Peso * qtd;
    todas_encomendas[ide].Quantidade[idp] += qtd;
    if(todas_encomendas[ide].Quantidade[idp] == 0)
      todas_encomendas[ide].Quantidade[idp] = qtd;
  }
}
void removestockaprod(int idp, int qtd){
  if(idp >= qtd_produtos)
    err("r1",idp,-1,-1);
  else if(todos_produtos[idp].Quantidade - qtd < 0)
    err("r2",idp,-1,qtd);
  else
    todos_produtos[idp].Quantidade -= qtd;
}
void removeprodenc(int ide, int idp){
  if(ide >= qtd_encomendas)
    err("R1",idp,ide,-1);
  else if(idp >= qtd_produtos)
    err("R2",idp,ide,-1);
  else{
    if(todas_encomendas[ide].Quantidade[idp] != 0){
      todos_produtos[idp].Quantidade += todas_encomendas[ide].Quantidade[idp];
      todas_encomendas[ide].Peso -= todos_produtos[idp].Peso * todas_encomendas[ide].Quantidade[idp];
      todas_encomendas[ide].Quantidade[idp] = 0;
    }
  }
}
void custoenc(int ide){
  int i, custo = 0;
  if(ide >= qtd_encomendas)
    err("C1",-1,ide,-1);
  else{
    for(i = 0; i < PMAX; i++)
      if(todas_encomendas[ide].Quantidade[i] > 0)
        custo += todas_encomendas[ide].Quantidade[i] * todos_produtos[i].Preco;
    printf("Custo da encomenda %d %d.\n", ide, custo);
  }
}
void alterapreco(int idp, int preco){
  if(idp >= qtd_produtos)
    err("p1",idp,-1,-1);
  else
    todos_produtos[idp].Preco = preco;
}
void descricaoequantidade(int ide, int idp){
  if(ide >= qtd_encomendas)
    err("E1",-1,ide,-1);
  else if(idp >= qtd_produtos)
    err("E2",idp,-1,-1);
  else
    printf("%s %d.\n",todos_produtos[idp].Descricao,todas_encomendas[ide].Quantidade[idp]);
}
void prodquantidademaisalta(int idp){
  int i, maxencomenda = 0;
  if(idp >= qtd_produtos)
    err("m1",idp,-1,-1);
  else{
    for(i = 0; i < qtd_encomendas; i++)
      if(todas_encomendas[i].Quantidade[idp] > todas_encomendas[maxencomenda].Quantidade[idp])
        maxencomenda = i;
    if(todas_encomendas[maxencomenda].Quantidade[idp] != 0)
      printf("Maximo produto %d %d %d.\n", idp, maxencomenda, todas_encomendas[maxencomenda].Quantidade[idp]);
  }
}

void countSort(produto arr[], int n, int k){
  produto output[PMAX];

  int count[PRECOMAX], i, total = 0, oldCount;
  memset(count,0,sizeof(count));

  for(i = 0; i < n; i++)
    count[arr[i].Preco]++;
  for(i = 0; i < k; i++){
    oldCount = count[i];
    count[i] = total;
    total += oldCount;
  }
  for(i = 0; i < n; i++){
    output[count[arr[i].Preco]] = arr[i];
    count[arr[i].Preco]++;
  }
  for(i = 0; i < n; i++)
    arr[i] = output[i];

}

/* fazer L() e adaptar countsort ou outro algoritmo para ordenar alfabeticamente */

void ordempreco(){
  produto copia[PMAX];
  int i;
  for(i = 0; i < qtd_produtos; i++)
   copia[i] = todos_produtos[i];

      
  countSort(copia,qtd_produtos,PRECOMAX);
  printf("Produtos\n");
  for(i = 0; i < qtd_produtos; i++)
    printf("* %s %d %d\n", copia[i].Descricao, copia[i].Preco, copia[i].Quantidade);
}

void Adjust(produto heap[],int i){
    int j;
    produto copy;
    int Number;
    int Reference = 1;

    Number=heap[0].Identificacao;

    while(2*i<=Number && Reference==1){
        j=2*i;

        if(j+1<=Number && strcmp(heap[j+1].Descricao,heap[j].Descricao)>0)
            j=j+1;
        if(strcmp(heap[j].Descricao,heap[i].Descricao) < 0)
            Reference=0;
        else{
            copy=heap[i];
            heap[i]=heap[j];
            heap[j]=copy;
            i=j;
        }
    }
}
void Make_Heap(produto heap[]){
    int i;
    int Number_of_Elements;
    Number_of_Elements=heap[0].Identificacao;
    for(i=Number_of_Elements/2;i>=1;i--)
        Adjust(heap,i);
}

void heapSort(produto heap[]){
    int LastElement;
    produto CopyVariable;


    Make_Heap(heap);

    while(heap[0].Identificacao > 1){
        LastElement=heap[0].Identificacao;
        CopyVariable=heap[1];
        heap[1]=heap[LastElement];
        heap[LastElement]=CopyVariable;
        heap[0].Identificacao--;
        Adjust(heap,1);
    }
}
void ordemalfabetica(int ide){
    produto copia[PMAX];
    int i,j = 1;

    if(ide >= qtd_encomendas)
        err("L1",-1,ide,-1);
    else{
        for (i = 0; i < PMAX; i++)
            if (todas_encomendas[ide].Quantidade[i] > 0) {
                copia[j] = todos_produtos[i];
                copia[j].Quantidade = todas_encomendas[ide].Quantidade[i];
                j++;
            }
        copia[0].Identificacao = j-1;
        heapSort(copia);
        printf("Encomenda %d\n", ide);
        for (i = 1; i < j; i++)
            printf("* %s %d %d\n", copia[i].Descricao, copia[i].Preco, copia[i].Quantidade);
    }

}

int main (){
  char primeiraletra, descricao[DMAX];
  int idp, ide, preco, peso, qtd;

  while(primeiraletra != 'x'){
    scanf("%c", &primeiraletra);
    switch(primeiraletra){
      case 'a':
        scanf(" %[^:]:%d:%d:%d", descricao,&preco,&peso,&qtd);
        adicionaproduto(descricao, preco, peso, qtd);
        break;

      case 'q':
        scanf(" %d:%d", &idp,&qtd);
        adicionastock(idp, qtd);
        break;

      case 'N':
        criaencomenda(); 
        break;

      case 'A':
        scanf(" %d:%d:%d", &ide,&idp,&qtd);
        adicionaprodaenc(ide,idp,qtd);
        break;

      case 'r':
        scanf(" %d:%d", &idp,&qtd); 
        removestockaprod(idp, qtd);
        break;

      case 'R':
        scanf(" %d:%d", &ide,&idp); 
        removeprodenc(ide,idp);
        break;

      case 'C':
        scanf(" %d", &ide); 
        custoenc(ide);
        break;

      case 'p':
        scanf(" %d:%d", &idp, &preco);
        alterapreco(idp, preco);
        break;

      case 'E':
        scanf(" %d:%d", &ide,&idp); 
        descricaoequantidade(ide, idp);
        break;

      case 'm':
        scanf(" %d",&idp); 
        prodquantidademaisalta(idp);
        break;

      case 'l':
        ordempreco();
        break;

      case 'L':
        scanf(" %d",&ide);
        ordemalfabetica(ide);
        break;
    }
  }
  return 0;
}
