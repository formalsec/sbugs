#include <stdio.h>
#include <string.h>


/*---------------------Constantes---------------------*/
/* Numero maximo de caracteres de uma descricao. */
#define MD 63
/* Numero maximo de produtos. */
#define MP 10000
/* Numero maximo de encomendas. */
#define ME 500
/* Peso maximo de uma encomenda. */
#define MW 200


/*---------------------Estruturas---------------------*/
/* Defini??o de um produto. */
typedef struct produto{
   int id;
   char descricao[MD];
   int preco;
   int peso;
   int quantidade;
}Produto;


/*---------------------Variaveis globais---------------------*/
/* Identificador do pr?ximo produto a ser registado. */
int idp_atual=0;
/* Identificador da pr?ximo encomenda a ser registada. */
int ide_atual=0;
/* Lista de todos os produtos registados. */
Produto stock_produtos[MP];
/* Lista de todas as encomendas registadas. */
Produto encomendas[ME][MW];
/* Vetor auxiliar para merge sort. */
Produto aux[MP];

/*---------------------Prototipos---------------------*/
/* Adiciona um novo produto ao sistema. */
void comando_a(char descricao[], int preco, int peso, int qtd);

/* Adiciona stock a um produto existente no sistema. */
void comando_q(int idp, int qtd);

/* Cria uma nova encomenda. */
void comando_N();

/* Adiciona um produto a uma encomenda */
void comando_A(int ide, int idp, int qtd);

/* Remove stock a um produto existente. */
void comando_r(int idp, int qtd);

/* Remove um produto de uma encomenda. */
void comando_R(int ide, int idp);

/* Calcula o custo de uma encomenda. */
void comando_C(int ide);

/* Altera o pre?o de um produto existente no sistema. */
void comando_p(int idp, int preco);

/* Retorna a descri??o e a quantidade de um produto numa dada encomenda. */
void comando_E(int ide, int idp);

/* Retorna o identificador da encomenda em que um dado produto ocorre mais vezes. */
void comando_m(int idp);

/* Lista todos os produtos existentes no sistema por ordem crescente de pre?o. */
void comando_l();

/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o. */
void comando_L(int ide);

/* Funcao auxiliar que determina o peso de uma encomenda. */
int peso_encomenda(int ide);

/* Algoritmo de ordenacao mergesort. */
void mergesort(Produto a[], int l, int r);

/* Funcao auxiliar para algoritmo mergesort. */
void merge(Produto a[], int l, int m, int r);


/*---------------------Main---------------------*/
/* Aplica o comando correspondente ao caracter lido. */
int main(){
   char c='0', descricao[MD];
   int preco, peso, qtd, idp, ide;

   while(c!='x'){
      scanf("%c ", &c);

      switch(c){
         case 'a':
         scanf("%[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
         comando_a(descricao, preco, peso, qtd);
         break;

         case 'q':
         scanf("%d:%d", &idp, &qtd);
         comando_q(idp, qtd);
         break;

         case 'N':
         comando_N();
         break;

         case 'A':
         scanf("%d:%d:%d", &ide, &idp, &qtd);
         comando_A(ide, idp, qtd);
         break;

         case 'r':
         scanf("%d:%d", &idp, &qtd);
         comando_r(idp, qtd);
         break;

         case 'R':
         scanf("%d:%d", &ide, &idp);
         comando_R(ide, idp);
         break;

         case 'C':
         scanf("%d", &ide);
         comando_C(ide);
         break;

         case 'p':
         scanf("%d:%d", &idp, &preco);
         comando_p(idp, preco);
         break;

         case 'E':
         scanf("%d:%d", &ide, &idp);
         comando_E(ide, idp);
         break;

         case 'm':
         scanf("%d", &idp);
         comando_m(idp);
         break;

         case 'l':
         comando_l();
         break;

         case 'L':
         scanf("%d", &ide);
         comando_L(ide);
         break;

         case 'x':
         break;

      }
   }
   return 0;
}


/*---------------------Funcoes---------------------*/
void comando_a(char descricao[], int preco, int peso, int qtd){
   stock_produtos[idp_atual].id=idp_atual;
   strcpy(stock_produtos[idp_atual].descricao, descricao);
   stock_produtos[idp_atual].preco=preco;
   stock_produtos[idp_atual].peso=peso;
   stock_produtos[idp_atual].quantidade=qtd;
   printf("Novo produto %d.\n", idp_atual);
   idp_atual++;
}

void comando_q(int idp, int qtd){
   if(idp>=idp_atual){
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
   }
   else{
      stock_produtos[idp].quantidade+=qtd;
   }
}

void comando_N(){
   printf("Nova encomenda %d.\n", ide_atual);
   ide_atual++;
}

void comando_A(int ide, int idp, int qtd){
   if(ide>=ide_atual){
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
   }
   else if(idp>=idp_atual){
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
   }
   else if(stock_produtos[idp].quantidade<qtd){
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
   }
   else if(peso_encomenda(ide)+stock_produtos[idp].peso*qtd>MW){
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
   }
   else{
      int i, a=0;
      for(i=0; encomendas[ide][i].peso!=0; i++){
         if(encomendas[ide][i].id==idp){
            stock_produtos[idp].quantidade-=qtd;
            encomendas[ide][i].quantidade+=qtd;
            a=1;
            break;
         }
      }
      if(a==0){
         stock_produtos[idp].quantidade-=qtd;
         encomendas[ide][i]=stock_produtos[idp];
         encomendas[ide][i].quantidade=qtd;
      }
   }
}

void comando_r(int idp, int qtd){
   if(idp>=idp_atual){
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
   }
   else if(stock_produtos[idp].quantidade<qtd){
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
   }
   else{
      stock_produtos[idp].quantidade-=qtd;
   }
}

void comando_R(int ide, int idp){
   if(ide>=ide_atual){
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
   }
   else if(idp>=idp_atual){
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
   }
   else{
      int i;
      for(i=0; encomendas[ide][i].peso!=0; i++){
         if(encomendas[ide][i].id==idp){
            stock_produtos[idp].quantidade+=encomendas[ide][i].quantidade;
            encomendas[ide][i].quantidade=0;
         }
      }
   }
}

void comando_C(int ide){
   if(ide>=ide_atual){
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
   }
   else{
      int i, r=0;
      for(i=0; encomendas[ide][i].peso!=0; i++){
         r+=encomendas[ide][i].preco*encomendas[ide][i].quantidade;
      }
      printf("Custo da encomenda %d %d.\n", ide, r);
   }
}

void comando_p(int idp, int preco){
   if(idp>=idp_atual){
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
   }
   else{
      int i, j;
      stock_produtos[idp].preco=preco;
      for(i=0; i<ide_atual; i++){
         for(j=0; encomendas[i][j].peso!=0; j++){
            if(encomendas[i][j].id==idp){
               encomendas[i][j].preco=preco;
            }
         }
      }
   }
}

void comando_E(int ide, int idp){
   if(ide>=ide_atual){
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
   }
   else if(idp>=idp_atual){
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
   }
   else{
      int i, a=0;
      for(i=0; encomendas[ide][i].peso!=0; i++){
         if(encomendas[ide][i].id==idp){
            printf("%s %d.\n", encomendas[ide][i].descricao, encomendas[ide][i].quantidade);
            a=1;
            break;
         }
      }
      if(a==0){
         printf("%s 0.\n", stock_produtos[idp].descricao);
      }
   }
}

void comando_m(int idp){
   if(idp>=idp_atual){
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
   }
   else{
      int i, j, r=-1, l=idp_atual;
      for(i=0; i<ide_atual; i++){
         for(j=0; encomendas[i][j].peso!=0;j++){
            if((encomendas[i][j].id==idp && encomendas[i][j].quantidade>r) || (encomendas[i][j].id==idp && encomendas[i][j].quantidade==r  && i<l)){
               r=encomendas[i][j].quantidade;
               l=i;
            }
         }
      }
      if(r>0){
         printf("Maximo produto %d %d %d.\n", idp, l, r);
      }
   }
}

void comando_l(){
   int i;
   Produto k[MP]={{0}};
   for(i=0; i<idp_atual; i++){
      k[i]=stock_produtos[i];
   }
   mergesort(k, 0, idp_atual);
   printf("Produtos\n");
   for(i=1; i<idp_atual+1; i++){
      printf("* %s %d %d\n", k[i].descricao, k[i].preco, k[i].quantidade);
   }
}

void comando_L(int ide){
   if(ide>=ide_atual){
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
   }
   else{
      int i, j;
      Produto k[MW]={{0}}, a;
      for(i=0; encomendas[ide][i].peso!=0; i++){
         k[i]=encomendas[ide][i];
      }
      for(i=0; k[i].peso!=0; i++){
         for(j=i+1; k[j].peso!=0; j++){
            if(strcmp(k[i].descricao, k[j].descricao) > 0){
               a=k[i];
               k[i]=k[j];
               k[j]=a;
            }
         }
      }
      printf("Encomenda %d\n", ide);
      for(i=0; k[i].peso!=0; i++){
         if(k[i].quantidade!=0){
            printf("* %s %d %d\n", k[i].descricao, k[i].preco, k[i].quantidade);
         }
      }
   }
}

int peso_encomenda(int ide){
   int i, r=0;
   for(i=0; encomendas[ide][i].peso!=0; i++){
      r+=encomendas[ide][i].peso*encomendas[ide][i].quantidade;
   }
   return r;
}

void merge(Produto a[], int l, int m, int r){
   int i, j, k;
   for (i=m+1; i>l; i--){
      aux[i-1]=a[i-1];
   }
   for (j=m; j<r; j++){
      aux[r+m-j]=a[j+1];
   }
   for (k=l; k<=r; k++){
      if ((aux[j].preco<aux[i].preco) || (aux[j].preco==aux[i].preco && aux[j].id<aux[i].id)){
         a[k]=aux[j--];
      }
      else{
         a[k]=aux[i++];
      }
   }
}

void mergesort(Produto a[], int l, int r){
   int m=(r+l)/2;
   if (r<=l){
      return;
   }
   mergesort(a, l, m);
   mergesort(a, m+1, r);
   merge(a, l, m, r);
}
