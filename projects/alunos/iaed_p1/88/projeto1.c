#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Defini??o de Limites*/
#define CARATERESMAX 64
#define PRODUTOSMAX 10000
#define ENCOMENDASMAX 500 
#define PESOMAX 200

/* Tipo Stocks*/
typedef struct {
  char descricao[CARATERESMAX];
  int preco;
  int peso;
  int qtd;
  int idp;
} Stocks;

Stocks produtos[PRODUTOSMAX];/*Vetor que guarda informacoes de todos os produtos em stock*/
int num_produtos=0;


/* Tipo Encomendas*/
typedef struct {  
  int ide;
  int idp[PRODUTOSMAX];
  int qtd[PRODUTOSMAX];
  int peso_total;
  int custo_encomenda;
} Encomendas;

Encomendas encomenda[ENCOMENDASMAX];/*Vetor que guarda informacoes de todas as encomendas*/
int num_encomendas=0;
int num_produtos_encomenda=0;

/*Prot?tipos*/

void adiciona_produto();/* a */
void adiciona_stock_produto();/* q */
void cria_nova_encomenda();/* N */
void adiciona_produto_encomenda();/* A */
void remove_stock_produto();/* r */
void remove_produto_encomenda();/* R */
void custo_encomenda();/* C */
void altera_preco_produto();/* p */
void descricao_e_quantidade_produto_encomenda();/* E */
void produto_encomenda_mais_vezes();/* m */
void lista_produtos_preco();/* l */
void lista_produtos_alfabeto();/* L */
void sair();/* x  */

int main(){
  char comando;
 
  do { /*comandos a executar*/
    comando=getchar();
    if (comando=='a'){
        adiciona_produto();}
    else if (comando=='N'){
        cria_nova_encomenda();}
    else if (comando=='q'){
      adiciona_stock_produto();}
    else if (comando=='A'){
        adiciona_produto_encomenda();}
    else if (comando=='r'){
        remove_stock_produto();}
    else if (comando=='R'){
        remove_produto_encomenda();}
    else if (comando=='C'){
        custo_encomenda();}
    else if (comando=='p'){
        altera_preco_produto();}
    else if (comando=='E'){
        descricao_e_quantidade_produto_encomenda();}
    else if (comando=='m'){
        produto_encomenda_mais_vezes();}
    else if (comando=='l'){
        lista_produtos_preco();}
    else if (comando=='L'){
        lista_produtos_alfabeto();}
  } while (comando != 'x'); /* Quando 'x' e introduzido o programa sai do ciclo */
  return 0;/* programa termina*/
}

/*funcao que adiciona um produto ao stock*/
void adiciona_produto(){ /*comando a*/
  scanf("%[^:]:%d:%d:%d", produtos[num_produtos].descricao, &produtos[num_produtos].preco, &produtos[num_produtos].peso, &produtos[num_produtos].qtd);
    
  printf("Novo produto %d.\n", num_produtos);
  produtos[num_produtos].idp = num_produtos;
  num_produtos++; /*num de produtos incrementa*/
}

/*funcao que cria uma nova encomenda*/
void cria_nova_encomenda(){/*comando  N*/
  printf("Nova encomenda %d.\n",num_encomendas);
  encomenda[num_encomendas].ide = num_encomendas;
  num_encomendas++; /*incrementa num de encomendas*/
}

/*funcao que adiciona stock a um produto*/
void adiciona_stock_produto(){/*comando q*/
  int id_produto;
  int quantidade;
  scanf("%d:%d",&id_produto,&quantidade);
  if (id_produto < 0 || id_produto > num_produtos-1){/* se nao existir o produto*/
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id_produto);
  }
  else {
    produtos[id_produto].qtd += quantidade; /*adiciona stock do produto*/
  }
}

/*funcao que adiciona um produto a uma encomenda*/
void adiciona_produto_encomenda(){/*comando A*/
  int id_encomenda;
  int id_produto;
  int quantidade;
  int contador;
  int produto_igual=0; /*se for igual a 1, ja existe o produto na encomenda*/

  scanf("%d:%d:%d",&id_encomenda,&id_produto,&quantidade);

  if (id_encomenda > num_encomendas-1) {/* se nao existir a encomenda*/
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_produto,id_encomenda);}

  else if (id_produto > num_produtos-1) {/* se nao existir o produto*/
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id_produto,id_encomenda);}

  else if (quantidade > produtos[id_produto].qtd) {/* se nao existir o produto em stock*/
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id_produto,id_encomenda);}

  else if ((produtos[id_produto].peso)*(quantidade) > 200) {/* se produto ultrapassar os 200kg*/
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_produto,id_encomenda);}

  else {
    for (contador = 0; contador < num_produtos_encomenda; ++contador) /*ciclo para ver se o peso da encomenda ultrapassa os 200*/
    {
    encomenda[id_encomenda].peso_total+=(produtos[encomenda[id_encomenda].idp[contador]].peso*quantidade); /*contar o peso total da encomenda*/
    }
    if (encomenda[id_encomenda].peso_total > 200) { /*se ultrapassar os 200 imprime erro*/
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_produto,id_encomenda);
      encomenda[id_encomenda].peso_total-=(produtos[encomenda[id_encomenda].idp[id_produto]].peso*quantidade);/*adi??o n?o ocorre*/
    }
    else { /*caraterizar o produto da encomenda*/
	  if (num_produtos_encomenda > 0){
	  for(contador=0;contador<num_produtos_encomenda;contador++){ /*ciclo para ver se produto ja existe na encomenda*/
		if (id_produto == encomenda[id_encomenda].idp[contador]){
		  encomenda[id_encomenda].qtd[contador]+=quantidade;/*indice encontrado*/	
		  produtos[id_produto].qtd-=quantidade;
		  produto_igual=1;}      
        }
        if (produto_igual != 1){
		  encomenda[id_encomenda].idp[num_produtos_encomenda]=id_produto;
		  encomenda[id_encomenda].qtd[num_produtos_encomenda]+=quantidade;
		  produtos[id_produto].qtd=produtos[id_produto].qtd-quantidade; /*remove do stock quantidade do produto usada na encomenda*/
		  num_produtos_encomenda++; /*incrementa o num de produtos da encomenda*/}
		}
    
        else {
		  encomenda[id_encomenda].peso_total+=(produtos[encomenda[id_encomenda].idp[0]].peso*quantidade); /*contar o peso total da encomenda*/
		  encomenda[id_encomenda].idp[num_produtos_encomenda]=id_produto;
		  encomenda[id_encomenda].qtd[num_produtos_encomenda]+=quantidade;
		  produtos[id_produto].qtd=produtos[id_produto].qtd-quantidade; /*remove do stock quantidade do produto usada na encomenda*/
		  num_produtos_encomenda++; /*incrementa o num de produtos da encomenda*/}
    
      }
  }
}

/*funcao que remove stock de um dado produto*/
void remove_stock_produto(){
  int id_produto;
  int quantidade;
  scanf("%d:%d",&id_produto,&quantidade);
  if (id_produto>num_produtos-1){ /*se produto nao existir*/
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id_produto);
  }
  else if (quantidade>produtos[id_produto].qtd){ /*se quantidade for insuficiente*/
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quantidade,id_produto);
  }
    
  else { /*remove do stock*/
    produtos[id_produto].qtd-=quantidade;
  }
}
  
/*funcao que calcula o custo da encomenda*/
void custo_encomenda(){
  int id_encomenda;
  int contador;
  int custo=0;
  scanf("%d",&id_encomenda);
  if (id_encomenda>num_encomendas-1){ /*se encomenda nao existir*/
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id_encomenda);  
  }
  else {
    for (contador = 0; contador < num_produtos_encomenda; ++contador) /*ciclo que soma o custo dos produtos da encomenda*/
    {
      custo+=produtos[encomenda[id_encomenda].idp[contador]].preco*(encomenda[id_encomenda].qtd[contador]);
    }
    encomenda[id_encomenda].custo_encomenda=custo;
    printf("Custo da encomenda %d %d.\n",id_encomenda,custo);
  }
}

/*funcao que altera o preco de um produto*/
void altera_preco_produto(){
  int id_produto;
  int preco;
  scanf("%d:%d",&id_produto,&preco);

  if (id_produto > num_produtos-1){ /*se produto nao existir*/
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id_produto);
  }
  else {
    produtos[id_produto].preco=preco; /*altera o preco*/
  }
}

/*funcao que lista a quantidade e a descricao de um produto numa encomenda*/
void descricao_e_quantidade_produto_encomenda(){
  int id_encomenda;
  int id_produto;
  scanf("%d:%d",&id_encomenda,&id_produto);
  if (id_produto > num_produtos-1){ /*se produto nao existir*/
    printf("Impossivel listar produto %d. Produto inexistente.\n",id_produto);
  }
  else if (id_encomenda>num_encomendas-1){ /*se encomenda nao existir*/
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_encomenda); 
  }
    
  else {
    printf ("%s %d.\n",produtos[id_produto].descricao,encomenda[id_encomenda].qtd[id_produto]);
  }

}
  
/*funcao que lista o identificador da encomenda onde o produto dado ocorre mais vezes*/
void produto_encomenda_mais_vezes() {
  int id_produto;
  int vezes_produto=0;
  int id_encomenda;
  int contador_produto;
  int contador_encomenda;
  scanf("%d",&id_produto);

  if (id_produto>num_produtos-1){ /*se produto nao existir*/
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_produto);
  }
    
  for (contador_encomenda = 0; contador_encomenda < num_produtos_encomenda; ++contador_encomenda) /*ciclo que passa pelas diferentes encomendas*/
  {
    for (contador_produto = 0; contador_produto < num_produtos_encomenda; ++contador_produto) /*ciclo que conta a qtd de produto na encomenda*/
    {
      if ((encomenda[contador_encomenda].idp[contador_produto] == id_produto) && (encomenda[contador_encomenda].qtd[contador_produto]>vezes_produto)) {
        vezes_produto=encomenda[contador_encomenda].qtd[contador_produto];
        id_encomenda=encomenda[contador_encomenda].ide;
      }
    
    }
  }
  if (vezes_produto==0){ /*se nao existir produto na encomenda*/
  }
  else {
    printf("Maximo produto %d %d %d.\n",id_produto,id_encomenda,vezes_produto);}
}

/*funcao que lista os produtos existentes no sistema por ordem crescente de preco*/
void lista_produtos_preco(){
  int id_produtos_ordenados[PRODUTOSMAX];
  int contador;
  int ultimo_elemento;
  int contador2;
  int flag=0;
  
  if (num_produtos==1){ /*se so existir um produto*/
    printf("Produtos\n");
    printf("* %s %d %d\n",produtos[0].descricao,produtos[0].preco,produtos[0].qtd);
  }
  else { /*insertion sort*/
	for (contador = 0; contador < num_produtos; contador++){
      id_produtos_ordenados[contador]=produtos[contador].idp;
    } /*vetor com os mesmos elementos*/

	for (contador = 1 ; contador <= num_produtos-1; contador++) {
      ultimo_elemento = id_produtos_ordenados[contador];/*ver o ultimo elemento do vetor*/

    for (contador2 = contador - 1 ; contador2 >= 0; contador2--) {
      if (produtos[id_produtos_ordenados[contador2]].preco > produtos[ultimo_elemento].preco) { /*se o preco for maior ordena e muda a flag para 1*/
        id_produtos_ordenados[contador2+1] = id_produtos_ordenados[contador2];
        flag = 1;
      }
      else 
		break;/*sai do ciclo*/
	  }
    if (flag)
      id_produtos_ordenados[contador2+1] = ultimo_elemento;
    }     
    printf("Produtos\n");
    for (contador = 0; contador < num_produtos; ++contador) /*ciclo que imprime os produtos ordenados*/
      {
      printf("* %s %d %d\n",produtos[id_produtos_ordenados[contador]].descricao,produtos[id_produtos_ordenados[contador]].preco,produtos[id_produtos_ordenados[contador]].qtd);
      }
  }
}
/*funcao que lista todos os produtos de uma encomenda por ordem alfab?tica de descricao*/
void lista_produtos_alfabeto(){
  int id_produtos_ordenados[PRODUTOSMAX];
  int contador;
  int id_encomenda;
  int contador2;
  int flag=0;
  int ultimo_elemento;
  int comparacao;
  scanf("%d",&id_encomenda);

  if (id_encomenda>num_encomendas-1){ /*se encomenda nao existir*/
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_encomenda);
  }
    
  else if (num_produtos_encomenda==1){ /*se so existir um produto na encomenda*/
    printf("Encomenda %d\n",id_encomenda);
	printf("* %s %d %d\n",produtos[encomenda[id_encomenda].idp[0]].descricao,produtos[encomenda[id_encomenda].idp[0]].preco,encomenda[id_encomenda].qtd[0]);}
    else{/*insertion sort*/
      for (contador = 0; contador < num_produtos_encomenda; contador++){
		id_produtos_ordenados[contador]=encomenda[id_encomenda].idp[contador];} /*vetor com os mesmos elementos*/

		for (contador = 1 ; contador <= num_produtos-1; contador++) {
		  ultimo_elemento = id_produtos_ordenados[contador];/*ver o ultimo elemento do vetor*/

			for (contador2 = contador - 1 ; contador2 >= 0; contador2--) {
			  comparacao=strcmp(produtos[id_produtos_ordenados[contador2]].descricao,produtos[ultimo_elemento].descricao); /*comparacao das descricoes*/
				if (comparacao>0) { /*se estiver desordenado ordena e muda a flag para 1*/
				  id_produtos_ordenados[contador2+1] = id_produtos_ordenados[contador2];
					flag = 1;
				}
				else 
					break;/*sai do ciclo*/
				}
         if (flag)
         id_produtos_ordenados[contador2+1] = ultimo_elemento;
	     }     
      
      printf("Encomenda %d\n",id_encomenda);
      for (contador = 0; contador < num_produtos_encomenda; ++contador) /*ciclo que imprime os produtos da encomenda ordenados alfabeticamente*/
        {
        printf("* %s %d %d\n",produtos[id_produtos_ordenados[contador]].descricao,produtos[id_produtos_ordenados[contador]].preco,encomenda[id_encomenda].qtd[contador]);
        }
    }
}

/*funcao que remove um dado produto de uma encomenda*/
void remove_produto_encomenda() { /* R */
  int id_produto;
  int id_encomenda;
  int contador;
  int contador2;
  int id_produto_encomenda;
  scanf("%d:%d",&id_encomenda,&id_produto);

  if (id_encomenda>num_encomendas-1){ /*se encomenda nao existir*/
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id_produto,id_encomenda);}
  
  else if (id_produto>num_produtos-1){ /*se produto nao existir*/
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id_produto,id_encomenda);}
  
  else {
    for(contador=0;contador<num_produtos_encomenda;contador++){ /*ciclo para encontrar o indice do produto na encomenda*/
	  if (id_produto == encomenda[id_encomenda].idp[contador]){
		id_produto_encomenda=contador;/*indice encontrado*/
		produtos[id_produto].qtd+=encomenda[id_encomenda].qtd[contador];/*stock do produto aumenta de novo*/
		if (id_produto_encomenda==num_produtos_encomenda-1){ /*se o produto a eliminar for o ultimo adicionado a encomenda*/
		  num_produtos_encomenda--;} /*decrementa num de produtos da encomenda*/
			
			else{			
			  for(contador2=id_produto_encomenda;contador2<num_produtos_encomenda-1;contador2++){ /*ciclo para eliminar o produto pedido da encomenda*/
				encomenda[id_encomenda].idp[contador2]=encomenda[id_encomenda].idp[contador2+1];
				encomenda[id_encomenda].qtd[contador2]=encomenda[id_encomenda].qtd[contador2+1];}
							
			  num_produtos_encomenda--; /*decrementa num de produtos da encomenda*/
			
             }
       }
     }
  }
}
