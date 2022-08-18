#include <stdio.h>
#include <string.h>
#define PROD 10000
#define ENC 500
#define STR 63
typedef struct produto{
  int id,preco,peso,qnt,vezes,auxiliar,preco_unidade;
  char des[STR];
} produto;
typedef struct encomenda{
  int id,peso,custo,vezes;
  char des[STR];
  struct produto prod[PROD];
} encomenda;
  produto  auxiliar[PROD];
  produto preco_unidade[PROD];
  encomenda peso={0};
  produto prod[PROD]={0};
  encomenda enc[ENC];
  encomenda vezes[ENC]={0};
  produto prod_na_enc[PROD];
  produto auxiliar_char[STR];
  int left,right,final;
  int maximo,custo,maior_enc,m=0,on=0,on_prod=0,maior=0,u=0,vezes_rep,encom=ENC,ultimo=0,j=0,k=0,i=0,contador=0,x=0,quantidade_na_encomenda,max_enc,id,quantidade,a,b,d,quantidade_enc,quantidades=0;
  void merge_char(produto prod_na_enc[],int left,int meio,int right);
  void mergesort_char(produto prod_na_enc[],int left,int right);
  void adiciona_produto(int i);
  void sort_myarray(produto preco_unidade []);
  void sort_mystr(encomenda prod_na_enc []);
  void adiciona_stock();
  void adiciona_enc();
  void adiciona_prod_enc();
  void remove_stock_prod();
  void remove_prod_enc();
  void calcula_custo_enc();
  void altera_preco();
  void mostra_prod_encomenda();
  void encomenda_prod_repete();
  void mergesort(produto preco_unidade[],int left,int right);
  void merge(produto preco_unidade[],int left,int meio,int right);
  void lista_encomenda();
  void adiciona_produto(int i){               /* adiciona um produto uma estrutura de dados */
    prod[i].id=i;
    maximo=i;
    scanf(" %[^:]:%d:%d:%d",prod[i].des,&prod[i].preco,&prod[i].peso,&prod[i].qnt);
    printf("Novo produto %d.\n",prod[i].id);
  }
  void adiciona_stock(){
    scanf("%d:%d",&id,&quantidade);
    if ((id>maximo)||(on_prod==0))
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
    else{
      prod[id].qnt=prod[id].qnt+quantidade;
  }
}
  void adiciona_enc(){
    max_enc=j;
    enc[j].id=j;
    printf("Nova encomenda %d.\n",enc[j++].id);
  }
  void adiciona_prod_enc(){
    scanf("%d:%d:%d",&a,&b,&d);    /*como o id do produto e inicializado a 0 como  o id da encomenda*/
    if ((a>max_enc) || (on==0))   /* a variavel on serve para verificar se foi adicionado uma encomenda 0 ao sistema caso contrario o a>maximo de encomendas deixaria passar */
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",b,a);
    else if ((b>maximo) || (on_prod==0)) /* o mesmo logica se aplica a variavel on_prod mas para as encomendas*/
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",b,a);
    else if (d>prod[b].qnt)
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",b,a);
    else if (enc[a].peso+(prod[b].peso*d)>200)
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",b,a);
    else
    {
      for(u=0;u<maximo+2;u++){
        if (strlen(enc[a].prod[u].des)==0){
          strcpy(enc[a].prod[u].des,prod[b].des);
          enc[a].prod[u].id=prod[b].id;
          enc[a].prod[u].qnt=d;
          enc[a].peso=enc[a].peso+prod[b].peso*d;
          break;
        }
        else if (enc[a].prod[u].id==b){
          enc[a].prod[u].qnt=enc[a].prod[u].qnt+d;
          enc[a].peso=enc[a].peso+prod[b].peso*d;
          break;
        }
        }
        prod[b].qnt=prod[b].qnt-d;
      }
  }

  void remove_stock_prod(){
    scanf("%d:%d",&a,&b);
    if ((a>maximo)||(on_prod==0))
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n",a);
    else if (prod[a].qnt<b)
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",b,a);
    else
      prod[a].qnt=prod[a].qnt-b;
  }
  void remove_prod_enc(){
    scanf("%d:%d",&a,&b);
    if ((a>max_enc)||(on==0))
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",b,a);
    else if (b>maximo)
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",b,a);
    else{
      quantidade_enc=0;
      for(k=0;k<maximo+1;k++){
        if (enc[a].prod[k].id==b){
        quantidade_enc=quantidade_enc+enc[a].prod[k].qnt;
        enc[a].prod[k].qnt=0;
        break;
      }
      }
    enc[a].peso=enc[a].peso-quantidade_enc*prod[b].peso;
    prod[b].qnt=prod[b].qnt+quantidade_enc;
    if (enc[a].custo-quantidade_enc*prod[b].preco<0)
      enc[a].custo=0;
    else
      enc[a].custo=enc[a].custo-quantidade_enc*prod[b].preco;

  }
}
  void calcula_custo_enc(){
  scanf("%d",&a);
  if (a>max_enc)
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",a);
  else
  {
    custo=0;
    for(k=0;k<maximo+1;k++){
      if (enc[a].prod[k].qnt>0){
        custo=custo+prod[enc[a].prod[k].id].preco*enc[a].prod[k].qnt;
}
}
    printf("Custo da encomenda %d %d.\n",a,custo);
}
}
  void altera_preco(){
    scanf("%d:%d",&a,&b);
    if ((a>maximo)||(on_prod==0))
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",a);
    else{
    prod[a].preco=b;
  }
  }
  void mostra_prod_encomenda(){
    scanf("%d:%d",&a,&b);
    if ((a>max_enc)||(on==0))
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",a);
    else if ((b>maximo)||(on_prod==0))
    printf("Impossivel listar produto %d. Produto inexistente.\n",b);
    else{
      quantidade_na_encomenda=0;
      for(k=0;k<maximo+1;k++){
        if (enc[a].prod[k].id==b){
          quantidade_na_encomenda=enc[a].prod[k].qnt;
          break;
        }
      }
        printf("%s %d.\n",prod[b].des,quantidade_na_encomenda);
    }
  }

  void encomenda_prod_repete(){
    scanf("%d",&a);
    if ((a>maximo)||(on_prod==0))
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",a);
    else
    {
      maior=0;
      for(k=0;k<max_enc+1;k++){
        if (enc[k].peso>0){
          for(m=0;m<maximo+1;m++){
            if ((enc[k].prod[m].id==a)&&(enc[k].prod[m].qnt>maior)) {
            maior=enc[k].prod[m].qnt;
            maior_enc=k;
            break;
        }
        }
        }
      }
       if (maior>0)                                                                                     /* procura o id do produto na encomenda e atribui a variavel quantidade a quantidade desse produto na encomenda*/
      printf("Maximo produto %d %d %d.\n",a,maior_enc,maior);
}
}
  int lista_sistema(){   /* vetor copia do sistema que e alterado em funcao do preco*/
    for(k=0;k<maximo+1;k++){
      preco_unidade[k]=prod[k];
    }
    left=0;
    right=maximo;
    mergesort(preco_unidade,left,right);
    printf("Produtos\n");
      for(m=0;m<maximo+1;m++){
        if (strlen(preco_unidade[m].des)!=0)
          printf("* %s %d %d\n",preco_unidade[m].des,preco_unidade[m].preco,preco_unidade[m].qnt);
        }
    return 0;
  }
  void mergesort(produto preco_unidade[],int left,int right){
      int meio=(left+right)/2;
      if (right<=left)
        return;
      mergesort(preco_unidade,left,meio);
      mergesort(preco_unidade,meio+1,right);
      merge(preco_unidade,left,meio,right);
    }
void merge(produto preco_unidade[],int left,int meio,int right){
      for(k=meio+1;k>left;k--){
        auxiliar[k-1]=preco_unidade[k-1];
      }
      for(m=meio;m<right;m++){
        auxiliar[right+meio-m]=preco_unidade[m+1];
      }
      for(x=left;x<=right;x++){
        if (auxiliar[m].preco<auxiliar[k].preco)
          preco_unidade[x]=auxiliar[m--];
        else if (auxiliar[m].preco>auxiliar[k].preco)
          preco_unidade[x]=auxiliar[k++];
        else
          {
            if (auxiliar[m].id<auxiliar[k].id)
              preco_unidade[x]=auxiliar[m--];
            else
              preco_unidade[x]=auxiliar[k++];
          }
      }
  }



  void lista_encomenda(){
    scanf("%d",&a);
    if ((a>max_enc)||(on==0))
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",a);
    else {
      contador=0;     /*verifica se a encomenda tem algum produto adicionado */
        if (strlen(enc[a].prod[0].des)==0){     /* caso verifique-se que nao tem elementos na encomenda imprime a encomenda id*/
          printf("Encomenda %d\n",a);
        }
      else
      {
          final=0;
        for(k=0;k<maximo+1;k++){                      /*procura se saber quantos elementos tem uma encomenda*/
          if (strlen(enc[a].prod[k].des)!=0)
            final=final+1;
          else if (strlen(enc[a].prod[k].des)==0)
          break;
          }
          for(k=0;k<final+1;k++){
            if (enc[a].prod[k].des!=0)                                 /* prod_na_enc corresponde a uma estrutura copia*/
              prod_na_enc[k]=enc[a].prod[k];
            else
              break;
            }
      left=0;
      right=final;
      mergesort_char(prod_na_enc,left,right); /* invocamos a funcao que ordena a nome dos produtos por ordem alfabetica */

      printf("Encomenda %d\n",a);

      for(k=0;k<final+1;k++){
          if ((strlen(prod_na_enc[k].des)!=0)&&(prod_na_enc[k].qnt>0)) {                      /* finalmente como temos a nossa array de strings ordenada verificamos na encomenda se o nome corresponde ao nome do produto na encomenda */                     /*em caso afirmativo imprimimos o seu nome ,preco e quantidade nessa encomenda*/
              printf("* %s",prod_na_enc[k].des);
              printf(" %d ",prod[prod_na_enc[k].id].preco);
              printf("%d\n",prod_na_enc[k].qnt);
            }
          else if (strlen(enc[a].prod[k].des)==0)
            break;
          }
      }
    }
  }



  void mergesort_char(produto prod_na_enc[],int left,int right){
      int meio=(left+right)/2;
      if (right<=left)
        return;
      mergesort_char(prod_na_enc,left,meio);
      mergesort_char(prod_na_enc,meio+1,right);
      merge_char(prod_na_enc,left,meio,right);
    }
    void merge_char(produto prod_na_enc[],int left,int meio,int right){
      for(k=meio+1;k>left;k--)
        auxiliar_char[k-1]=prod_na_enc[k-1];
      for(m=meio;m<right;m++)
        auxiliar_char[right+meio-m]=prod_na_enc[m+1];
      for(x=left;x<=right;x++){
        if (strcmp(auxiliar_char[m].des,auxiliar_char[k].des)<0)
          prod_na_enc[x]=auxiliar_char[m--];
        else
          prod_na_enc[x]=auxiliar_char[k++];
      }
  }






int main(){
  int c;
  while (((c=getchar())!=EOF)&&(c!='x')) {
    switch(c){
      case 'a':
      {
        on_prod=1;
        adiciona_produto(i++);
        break;
      }
      case 'q':
      {
        adiciona_stock();
        break;
      }
      case 'N':
      {
        adiciona_enc();
        on=1;
        break;
      }
      case 'A':
      {
        adiciona_prod_enc();
        break;
      }
      case 'r':
      {
        remove_stock_prod();
        break;
      }
      case 'R':
      {
          remove_prod_enc();
          break;
        }
      case 'C':
      {
          calcula_custo_enc();
          break;
        }
      case 'p':
      {
        altera_preco();
        break;
      }
      case 'E':
      {
        mostra_prod_encomenda();
        break;
      }
      case 'm':
      {
        encomenda_prod_repete();
        break;
      }
      case 'l':
      {
        lista_sistema();
        break;
      }
      case 'L':
      {
        lista_encomenda();
        break;
      }
      case 'x':{
        return 0;
      }
      }
    }
  return 0;
}
