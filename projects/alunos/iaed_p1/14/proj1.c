#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCRICAO 64
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500

void inicializar_tabelas();
void cria_produto();
void adiciona_stock();
void remove_stock();
void cria_encomenda();
void adiciona_produto_encomenda();
void remove_produto_encomenda();
void calcula_custo();
void altera_preco_produto();
void descricao_encomenda();
void encontra_encomenda();
void lista_produtos_ordem_alfabetica();
void lista_produtos_ordem_preco();
void altera_stock(int, int);
void altera_encomenda(int, int, int);

typedef struct {
  int id;
  char descricao[MAX_DESCRICAO];
  int preco;
  int peso;
  int qtd;
} Produto;

typedef struct {
  int id;
  int produtos[MAX_PRODUTOS];
  int peso;
} Encomenda;

int numero_produtos=0, numero_encomendas=0;
Produto produtos[MAX_PRODUTOS];
Encomenda encomendas[MAX_ENCOMENDAS];

int main()
{
		char command;
    inicializar_tabelas();
		while (1) {
			command = getchar();
			switch (command){
			case 'a':
				cria_produto();
				break;
			case 'q':
				adiciona_stock();
				break;
			case 'N':
				cria_encomenda();
				break;
			case 'A':
				adiciona_produto_encomenda();
				break;
      case 'r':
        remove_stock();
        break;
      case 'R':
        remove_produto_encomenda();
        break;
      case 'C':
        calcula_custo();
        break;
      case 'p':
        altera_preco_produto();
        break;
      case 'E':
        descricao_encomenda();
        break;
      case 'm':
        encontra_encomenda();
        break;
      case 'l':
        lista_produtos_ordem_preco();
        break;
      case 'L':
        lista_produtos_ordem_alfabetica();
        break;
      case 'x':
        return 0;
		}
	}
return 0;
}


void inicializar_tabelas(){
  int i=0;
  for (i=0; i<MAX_PRODUTOS; i++){
    produtos[i].id = i;
    produtos[i].qtd = 0;
  }
}

void cria_produto (){
  scanf (" %[^:]:%d:%d:%d",produtos[numero_produtos].descricao, &produtos[numero_produtos].preco, &produtos[numero_produtos].peso, &produtos[numero_produtos].qtd);
  printf("Novo produto %d.\n",numero_produtos);
  numero_produtos++;
}

void adiciona_stock(){
  int idp, qtd;
  scanf("%d:%d", &idp, &qtd);
  if (idp>numero_produtos-1)
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  altera_stock(idp, qtd);
}

void cria_encomenda(){
  printf("Nova encomenda %d.\n",numero_encomendas);
  numero_encomendas++;
}

void adiciona_produto_encomenda(){
  int ide, idp, qtd;
  scanf("%d:%d:%do", &ide, &idp, &qtd);
  if (ide>numero_encomendas-1)
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  else if (idp>numero_produtos-1)
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  else if (qtd>produtos[idp].qtd)
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
  else if ((encomendas[ide].peso+(produtos[idp].peso*qtd))>200)
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
  else
    altera_encomenda (ide, idp, qtd);
}

void remove_stock (){
  int idp, qtd;
  scanf("%d:%d", &idp, &qtd);
  if (idp>numero_produtos-1)
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  else if (produtos[idp].qtd < qtd)
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd, idp);
  else
    altera_stock(idp, -qtd);
}

void remove_produto_encomenda (){
  int ide, idp;
  scanf("%d:%d", &ide, &idp);
  if (ide>numero_encomendas-1)
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  else if (idp>numero_produtos-1)
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
  else{
    altera_stock (idp, encomendas[ide].produtos[idp]);
    encomendas[ide].produtos[idp]=0;
  }
}

void calcula_custo(){
  int i, c=0, ide;
  scanf("%d",&ide);
  if (ide>numero_encomendas-1)
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  else{
    for (i=0; i<numero_produtos; i++)
      if (encomendas[ide].produtos[i]>0)
        c = (c + (produtos[i].preco * encomendas[ide].produtos[i]));
    printf("Custo da encomenda %d %d.\n", ide, c);
  }
}

void altera_preco_produto(){
  int idp, c;
  scanf("%d:%d", &idp, &c);
  if (idp>numero_produtos-1)
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  else
    produtos[idp].preco=c;
}

void descricao_encomenda(){
  int ide, idp;
  scanf("%d:%d", &ide, &idp);
  if (ide>numero_encomendas-1)
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  else if (idp>numero_produtos-1)
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  else
    printf("%s %d.\n", produtos[idp].descricao, encomendas[ide].produtos[idp]);
}

void encontra_encomenda(){
  int idp, ide, m=0, i=0;
  scanf ("%d", &idp);
  if (idp>numero_produtos-1)
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  else
    for (i=0; i<numero_encomendas-1; i++)
      if (encomendas[i].produtos[idp]>m){
        m=encomendas[i].produtos[idp];
        ide=i;
      }
  if (m>0)
    printf("Maximo produto %d %d %d\n", idp, ide, m);
}


void lista_produtos_ordem_preco(){
  int i, j, lista_ordenada[MAX_PRODUTOS], produtos_ordenados=0;
  for (i=0; i<numero_produtos; i++){
    for (j=i-1; j>=-1; j--){
      if ((j == -1)){
        lista_ordenada[0]=i;
        produtos_ordenados++;
        break;
      }
      else if (produtos[i].preco >= produtos[lista_ordenada[j]].preco){
        lista_ordenada[j+1]=i;
        produtos_ordenados++;
        break;
      }
      else
        lista_ordenada[j+1]=lista_ordenada[j];
    }
  }
  printf("Produtos\n");
  for (i=0; i<produtos_ordenados; i++)
    printf("* %s %d %d\n", produtos[lista_ordenada[i]].descricao, produtos[lista_ordenada[i]].preco, produtos[lista_ordenada[i]].qtd);
}

void lista_produtos_ordem_alfabetica(){
  int ide, i, j, lista_ordenada[MAX_PRODUTOS], produtos_ordenados=0;
  scanf("%d", &ide );
      if (ide>numero_encomendas-1)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      else{
        for (i=0; i<numero_produtos; i++)
          if (encomendas[ide].produtos[i]==0)
            break;
          else{
            for (j=i-1; j>=-1; j++){
              if (j==-1){
                lista_ordenada[j+1]=i;
                produtos_ordenados++;
                break;
              }
              else if (strcmp(produtos[i].descricao, produtos[lista_ordenada[j]].descricao)>=1){
                lista_ordenada[j+1]=i;
                produtos_ordenados++;
                break;
              }
              else
                lista_ordenada[j+1]=lista_ordenada[j];
            }
          }

      printf("Encomenda %d\n", ide);
      for (i=0; i<produtos_ordenados; i++)
        printf("* %s %d %d\n", produtos[lista_ordenada[i]].descricao, produtos[lista_ordenada[i]].preco, encomendas[ide].produtos[lista_ordenada[i]]);
      }
}

void altera_stock(int idp, int qtd){
  produtos[idp].qtd=produtos[idp].qtd+qtd;
}

void altera_encomenda (int ide, int idp, int qtd){
  encomendas[ide].produtos[idp]=encomendas[ide].produtos[idp] + qtd;
  encomendas[ide].peso = encomendas[ide].peso + produtos[idp].peso*qtd;
  altera_stock (idp, -qtd);
}
