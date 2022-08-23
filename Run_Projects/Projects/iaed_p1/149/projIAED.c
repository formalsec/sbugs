#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Numero maximo possivel de produtos registados.*/
#define MAX_ID 10000
/*Dimensao maxima da descricao dos produtos.*/
#define MAX_DESC 63
/*Numero maximo possivel de encomendas.*/
#define MAX_ENC 500
/*Numero maximo possivel de produtos numa encomenda*/
#define MAX_PROD_ENC 200

/*Estrutura do produto com as seguintes caracteristicas: ID, quantidade, preco, peso e a sua descricao.*/
typedef struct{
  int ID,QNTD,PRECO,PESO;
  char DESC[MAX_DESC];
} Produto;

/*Estrutura da encomenda com as seguintes caracteristicas: array de produtos e peso.*/
typedef struct{
  Produto produto[MAX_ID];
  int PESO;
} Encomenda;

/*-------------------VETORES GRANDES----------------------*/
/*Array dos produtos em stock.*/
Produto produto[MAX_ID] = {0};
/*Array copia dos produtos em stock para ser ordenado.*/
Produto produtos_p_ordenar[MAX_ID] = {0};
/*Array de encomendas*/
Encomenda encomenda[MAX_ENC] = {0};
/*Array copia de encomendas para ser ordenado.*/
Produto encomenda_p_ordenar[MAX_PROD_ENC] = {0};
/*IDs do produtos no stock*/
int stock[MAX_ID]= {0};
/*IDs das encomendas feitas.*/
int IDeS[MAX_ENC]={0};
/*-----------------------------------------*/

/*Funcao que retira os ":" do input e os substitui por " " para ser utilizado posteriormente o sscanf().*/
char* tira_doispontos(char input[]){
  int len,i;

  len = strlen(input);

  for (i=0;i<len;i++){
    if (input[i] == ':'){
      input[i] = ' ';
    }
  }
  return input;
}

/*Funcao que permite ver se um inteiro esta num array ou nao.*/
int in(int n, int array[]){
  int i;
  for (i=0;i<MAX_ID;i++){
    if(array[i] == n){
      return 1;
    }
  }
  return 0;
}

/*Verifica se encomenda existe no sistema*/
int encomenda_existente(int IDe,int n_IDe){
  if(IDeS[IDe]!=IDe || n_IDe == 0){ 
    return 0;
  }
  else{
    return 1;
  }
}

/*Verifica se produto existe no sistema*/
int produto_existente(int IDp,int n_IDp){
  if(stock[IDp]!=IDp || n_IDp == 0){ 
    return 0;
  }
  else{
    return 1;
  }
}

/*Funcao de ordenacao merge sort.*/
void merge(Produto produto[], int e, int m, int d, int ativado){ 
    int i, j, k; 
    int n1 = m - e + 1; 
    int n2 =  d - m; 
  
    Produto E[MAX_ID], D[MAX_ID]; 
  
    for (i = 0; i < n1; i++){
        E[i] = produto[e + i];
        }
    for (j = 0; j < n2; j++){ 
        D[j] = produto[m + 1 + j];
    } 
  
    i = 0;
    j = 0;
    k = e;
    while (i < n1 && j < n2){ 
      if(ativado == 0){
        if (E[i].PRECO <= D[j].PRECO){ 
            produto[k] = E[i]; 
            i++; 
        } 
        else{ 
            produto[k] = D[j]; 
            j++; 
        } 
        k++; 
      }
      else if (ativado == 1){
        if (strcmp(D[j].DESC,E[i].DESC)>= 0){ 
            produto[k] = E[i]; 
            i++; 
        } 
        else{ 
            produto[k] = D[j]; 
            j++; 
        } 
        k++; 
      }
    } 
    while (i < n1){ 
        produto[k] = E[i]; 
        i++; 
        k++; 
    } 
    while (j < n2){ 
        produto[k] = D[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergeSort(Produto produto[], int e, int d, int ativado){ 
  /*e index da esquerda, d index da direita.*/
    if (e < d){ 
        /*m index do elemento em que vai ser dividido array.*/
        int m = e+(d-e)/2; 
  
        /*ordenar primeira e segunda partes.*/
        mergeSort(produto, e, m, ativado); 
        mergeSort(produto, m+1, d, ativado); 
  
        merge(produto, e, m, d, ativado); 
    } 
}

/*Adiciona novo produto ao stock.*/
void novo_produto(char input[],int n_IDp){
  /* input onde estao as caracteristicas do produto e ID para o numero caracteristico do produto.*/
  char throwaway;
  /*sscanf para retirar o que e relevante do input.*/
  sscanf(tira_doispontos(input),"%c %s %d %d %d",&throwaway,produto[n_IDp].DESC,&produto[n_IDp].PRECO,&produto[n_IDp].PESO,&produto[n_IDp].QNTD);

  produto[n_IDp].ID = n_IDp;
  printf("Novo produto %d.\n",n_IDp);
  stock[n_IDp] = n_IDp;
}

/*adiciona quantidade a um produto no stock.*/
void adicionar_stock(char input[],int n_IDp){
  char throwaway;
  int IDp,qntd;
  sscanf(tira_doispontos(input),"%c %d %d",&throwaway,&IDp,&qntd);

  if (stock[IDp]==IDp && n_IDp > 0){
    produto[IDp].QNTD += qntd;
  }
  else {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",IDp);
  }
}

/*cria uma nova encomenda*/
void nova_encomenda(int n_IDe){
  /*Coloca novo IDe em IDeS e incrementa o contador de encomendas*/
    printf("Nova encomenda %d.\n",n_IDe);
    IDeS[n_IDe] = n_IDe;
}

/*Adiciona uma quantidade de um produto a uma encomenda.*/
int adicionar_a_encomenda(char input[],int n_IDe,int n_IDp){
  char throwaway;
  int IDe,IDp,qntd;

  sscanf(tira_doispontos(input), "%c %d %d %d",&throwaway, &IDe, &IDp, &qntd);
  
  if(encomenda_existente(IDe, n_IDe) == 0){ 
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",IDp,IDe);
    return 0;
  }
  if(produto_existente(IDp, n_IDp) == 0){
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",IDp,IDe);
    return 0;
  }
  if (produto[IDp].QNTD - qntd < 0){
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",IDp,IDe);
    return 0;
  }
  if (encomenda[IDe].PESO + qntd * produto[IDp].PESO > 200){
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",IDp,IDe);
    return 0;
  }

  /*encomenda numero x, produto numero y da encomenda e igual a produto[idp]*/
  encomenda[IDe].produto[IDp].ID = produto[IDp].ID;
  encomenda[IDe].produto[IDp].PRECO = produto[IDp].PRECO;
  strcpy(encomenda[IDe].produto[IDp].DESC,produto[IDp].DESC);
  
  /*alterar quantidade da encomenda e decrementar produto em si*/
  encomenda[IDe].PESO += qntd * produto[IDp].PESO;
  encomenda[IDe].produto[IDp].QNTD += qntd;

  produto[IDp].QNTD -= qntd;

  return 0;
} 

/*remove x quantidade do stock a um produto.*/
int remover_stock(char input[],int n_IDp){
  char throwaway;
  int IDp,qntd;

  sscanf(tira_doispontos(input),"%c %d %d",&throwaway,&IDp,&qntd);

  if (stock[IDp]==IDp && n_IDp > 0){
    if (produto[IDp].QNTD - qntd < 0){
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qntd,IDp);
      return 0;
    }
    else {
      produto[IDp].QNTD -= qntd;
      return 0;
    } 
  }
  else {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n",IDp);
  }
  return 0;
}

/*remove um produto duma encomenda*/
int remove_produto_enc(char input[], int n_IDe, int n_IDp){
  int IDe,IDp;
  char throwaway;
  
  sscanf(tira_doispontos(input),"%c %d %d",&throwaway,&IDe,&IDp);

  if(encomenda_existente(IDe, n_IDe) == 0){ 
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",IDp,IDe);
    return 0;
  }
  if(produto_existente(IDp, n_IDp) == 0){
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",IDp,IDe);
    return 0;
  }
  /*remove produto de uma encomenda ao colocar a sua quantidade a 0, remover o peso que o produto ocupava na encomenda e voltar a repor a quantidade retirada da encomenda no stock.*/
  encomenda[IDe].PESO -= encomenda[IDe].produto[IDp].QNTD*produto[IDp].PESO;
  produto[IDp].QNTD += encomenda[IDe].produto[IDp].QNTD;

  encomenda[IDe].produto[IDp].QNTD = 0;
  return 0;
}

/*calcula o custo de uma encomenda.*/
int calcula_custo_encomenda(char input[],int n_IDe, int n_IDp){
  int IDe,custo,i;
  char throwaway;

  sscanf(input,"%c %d",&throwaway,&IDe);

  if(encomenda_existente(IDe, n_IDe) == 0){ 
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",IDe);
    return 0;
  }
  /*ciclo que percorre todos os produtos da encomenda e soma os seus precos com a quantidade do produto obtendo o custo.*/
  custo = 0;
  for (i=0;i<n_IDp;i++){
    custo += encomenda[IDe].produto[i].PRECO * encomenda[IDe].produto[i].QNTD;
  }
  printf("Custo da encomenda %d %d.\n",IDe,custo);
  return 0;
}

/*altera preco do produto no stock e nas encomendas em que esta presente.*/
void altera_preco(char input[],int n_IDp,int n_IDe){
  char throwaway;
  int IDp,preco,IDe;

  sscanf(tira_doispontos(input),"%c %d %d",&throwaway,&IDp,&preco);

  if(stock[IDp]==IDp && n_IDp>0){
    produto[IDp].PRECO = preco;
    /*ver se IDp que se quer alterar esta nas encomendas.*/
    for(IDe=0;IDe<n_IDe;IDe++){
      if(encomenda[IDe].produto[IDp].PRECO != 0){
        encomenda[IDe].produto[IDp].PRECO = preco;
      }
    }
  }
  else {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",IDp);
  }
}

/*retorna a descri??o e a quantidade de um produto numa dada encomenda.*/
int lista_produto_enc(char input[],int n_IDp,int n_IDe){
  char throwaway;
  int IDe,IDp;

  sscanf(tira_doispontos(input),"%c %d %d",&throwaway,&IDe,&IDp);

  if(encomenda_existente(IDe, n_IDe) == 0){ 
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",IDe);
    return 0;
  }
  if(produto_existente(IDp, n_IDp) == 0){
    printf("Impossivel listar produto %d. Produto inexistente.\n",IDp);
    return 0;
  }

  printf("%s %d.\n",produto[IDp].DESC,encomenda[IDe].produto[IDp].QNTD);
  return 0;
}

/*retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/
int listar_produto_max(char input[],int n_IDp,int n_IDe){
  int IDp,IDe,res_IDe,qntd_max,IDe_menor;
  char throwaway;

  sscanf(input,"%c %d",&throwaway,&IDp);

  if(produto_existente(IDp, n_IDp) == 0){
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",IDp);
    return 0;
  }

  qntd_max = -1;
  res_IDe = -1;
  IDe_menor = -1;
  for (IDe=0;IDe<n_IDe;IDe++){
    /*Se a quanitdade do produto na encomenda for maior a quantidade maxima guardar o IDe, se for igual guardar IDe noutra variavel para imprimir o IDe menor*/
    if (encomenda[IDe].produto[IDp].QNTD >= qntd_max){
      if(qntd_max > 0 && encomenda[IDe].produto[IDp].QNTD == qntd_max){
        IDe_menor = res_IDe;
      }
      else{
        qntd_max = encomenda[IDe].produto[IDp].QNTD;
        res_IDe = IDe;
        IDe_menor = -1;
      }
    }
  }
  /*no caso de haver duas quantidades iguais guardar IDe numa lista e depois imprimir a menor*/
  if (qntd_max > 0){ 
    if (IDe_menor == -1){
      printf("Maximo produto %d %d %d.\n",IDp,res_IDe,qntd_max);
    }
    else{
      printf("Maximo produto %d %d %d.\n",IDp,IDe_menor,qntd_max);
    }
  }
  return 0;
}

/*lista todos os produtos existentes no sistema por ordem crescente de preco.*/
void listar_stock(int n_IDp){
  int i,ativado;

  /*copia produtos para outro vetor para ordenar de acordo com o preco.*/
  for(i=0;i<n_IDp;i++){
    produtos_p_ordenar[i] = produto[i];
  }

  ativado = 0;
  mergeSort(produtos_p_ordenar,0,n_IDp-1,ativado);
    
  printf("Produtos\n");
  for (i=0;i<n_IDp;i++){
    printf("* %s %d %d\n",produtos_p_ordenar[i].DESC,produtos_p_ordenar[i].PRECO,produtos_p_ordenar[i].QNTD);
  }
}

/*lista todos os produtos de uma encomenda por ordem alfabetica da descricao.*/
int listar_encomenda(char input[], int n_IDp,int n_IDe){
  /*criar copia dos produtos da encomenda a ordenar e imprimi-la com as descricoes ordenadas alfabeticamente*/
  char throwaway;
  int i,j,IDe,ativado;

  sscanf(input,"%c %d",&throwaway,&IDe);

  if(encomenda_existente(IDe, n_IDe) == 0){ 
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",IDe);
    return 0;
  }

  j=0;
  for(i=0;i<n_IDp;i++){
    if (encomenda[IDe].produto[i].QNTD > 0){
      encomenda_p_ordenar[j] = encomenda[IDe].produto[i];
      j++;
    }
  }

  ativado = 1;
  mergeSort(encomenda_p_ordenar,0,j-1,ativado);

  printf("Encomenda %d\n",IDe);

  for (i=0;i<j;i++){
      printf("* %s %d %d\n",encomenda_p_ordenar[i].DESC,encomenda_p_ordenar[i].PRECO,encomenda_p_ordenar[i].QNTD);
  }
  return 0;
}
/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
int main() {
  char input[100] = {0};
  int n_IDp,n_IDe;
  
  n_IDp = 0;
  n_IDe = 0;

  while (1>0){
    fgets(input,100,stdin);

    if (input[0] == 'a'){
      novo_produto(input,n_IDp);
      n_IDp++;
    }
    if (input[0] == 'q'){
      adicionar_stock(input,n_IDp);
    }
    if (input[0] == 'N'){
      nova_encomenda(n_IDe);
      n_IDe++;
    }
    if (input[0] == 'A'){
      adicionar_a_encomenda(input,n_IDe,n_IDp);
    }
    if (input[0] == 'r'){
      remover_stock(input,n_IDp);
    }
    if (input[0] == 'R'){ 
      remove_produto_enc(input,n_IDe,n_IDp);
    }
    if (input[0] == 'C'){
      calcula_custo_encomenda(input,n_IDe,n_IDp);
    }
    if (input[0] == 'p'){
      altera_preco(input,n_IDp,n_IDe);
    }
    if (input[0] == 'E'){
      lista_produto_enc(input,n_IDp,n_IDe);
    }
    if (input[0] == 'm'){
      listar_produto_max(input,n_IDp,n_IDe);
    }
    if (input[0] == 'l'){
      listar_stock(n_IDp);
    }
    if (input[0] == 'L'){
      listar_encomenda(input,n_IDp,n_IDe);
    }
    if (input[0] == 'x'){
      return 0;
    }
  }
}