#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>				/*Livrarias */
#include <string.h>				/*Livrarias */

/* Declaracao de constantes para todo o c?digo */

#define DIMDESC 63
#define MAXPRODS 10000
#define MAXENCOM 500
#define MAXENCOMPESO 200

/* Gestao de produtos */

typedef struct produto		/* Define-se um estrutura de variaveis */
{
  int identificador;
  char descricao[DIMDESC];
  int preco;
  int peso;
  int quantidade;
} produto;

/* Produtos existentes em stock */

produto stock_produto[MAXPRODS];     /*define-se array stock_produto com base na estrutura produtos com um tamanho de MAXPRODS */
int num_total_produtos = 0;

void adiciona_stock(int prodident, int prodqtd)
{
  if(prodident>=num_total_produtos)
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prodident);
  else
    stock_produto[prodident].quantidade += prodqtd;
}

void remove_stock_prod(int prodident, int prodqtd)
{
  if(prodident>=num_total_produtos)
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prodident);
  else if(stock_produto[prodident].quantidade<prodqtd)
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", prodqtd, prodident);
  else
    stock_produto[prodident].quantidade -= prodqtd;
}

void adiciona_produto(char proddesc[],int prodpreco,int prodpeso,int prodqtd)
{
  int novo_prod_id, lendesc;
  if(num_total_produtos==MAXPRODS)
    return;
  novo_prod_id=num_total_produtos++;
  stock_produto[novo_prod_id].identificador = novo_prod_id;
  lendesc=strlen(proddesc);
  strncpy(stock_produto[novo_prod_id].descricao, proddesc, lendesc);
  stock_produto[novo_prod_id].preco = prodpreco;
  stock_produto[novo_prod_id].peso = prodpeso;
  stock_produto[novo_prod_id].quantidade = prodqtd;
  printf("Novo produto %d.\n", novo_prod_id);
}

void altera_prod_preco(int prodident, int prodpreco)
{
  if(prodident>=num_total_produtos)
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prodident);
  else
    stock_produto[prodident].preco=prodpreco;
}

void mostra_produto(produto prod) /* <desc1> <preco1> <qtd1 em stock> */
{
  printf("* %s %d %d\n",prod.descricao, prod.preco, prod.quantidade);
}

/* Gestao de encomendas */

typedef struct prod_qtd     		/* Define-se um estrutura de variaveis para STOCK? */
{
  int produto_id;
  int quantidade;
} prod_qtd;					            /* Quantidade de produtos em stock */

typedef struct encomenda
{
  int identificador;
  prod_qtd prods[MAXPRODS];
  int num_prods;						    /* Numero de produtos numa encomenda */
  int peso_total;
} encomenda; 							      /*Estrutura de uma encomenda */

encomenda encomendas[MAXENCOM]; /*Numero maximo de encomendas (500) */
int num_total_encomendas = 0;		/* Contador a zeros */

void nova_encomenda()           /*Instrucao para gerar uma encomenda */
{
  int nova_encom_id;
  if(num_total_encomendas==MAXENCOM)
    return;
  nova_encom_id=num_total_encomendas++;					            /* Adiciona produtos a encomenda */
  encomendas[nova_encom_id].identificador = nova_encom_id;  /* Adiciona encomendas */
  encomendas[nova_encom_id].num_prods = 0;					        /* Comeca com 0 produtos */
  encomendas[nova_encom_id].peso_total = 0;					        /* Comeca com peso 0 */
  printf("Nova encomenda %d.\n",nova_encom_id);
}

void adiciona_produto_encomenda(int encident, int prodident, int prodqtd)
{
    int peso_adicional;
    int prod_enc_id;
    int i;
    /* Validar id encomenda */
    if(encident>=num_total_encomendas)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prodident, encident);
      return;
    }
    /* Validar id produto */
    if(prodident>=num_total_produtos)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prodident, encident);
      return;
    }
    /* Validar quantidade em stock */
    if(prodqtd>stock_produto[prodident].quantidade)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prodident, encident);
      return;
    }
    /* Validar o peso total da encomenda */
    peso_adicional=stock_produto[prodident].peso*prodqtd;
    if(encomendas[encident].peso_total+peso_adicional>200)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prodident, encident);
      return;
    }
    /* Decrementar a quantidade do stock do produto */
    stock_produto[prodident].quantidade -= prodqtd;
    /* Incrementar o peso adicional dos produtos adicionados na encomenda */
    encomendas[encident].peso_total += peso_adicional;
    /* Validar se o id do produto ja existe na encomenda */
    prod_enc_id=-1;
    for(i=0; i<encomendas[encident].num_prods; i++)
      if(encomendas[encident].prods[i].produto_id==prodident)
        prod_enc_id=i;
    /* Caso nao exista insere o novo produto na encomenda; */
    if(prod_enc_id==-1)
    {
      prod_enc_id=encomendas[encident].num_prods++;
      encomendas[encident].prods[prod_enc_id].produto_id = prodident;
      encomendas[encident].prods[prod_enc_id].quantidade = 0;
    }
    /* Adicionar quantidade produtos a encomenda */
    encomendas[encident].prods[prod_enc_id].quantidade += prodqtd;
}

void remove_prod_enc(int encident, int prodident)
{
  int prod_enc_id;
  int i;
  int qtd_add_stock;
  int peso_remover;
  int numprods;
  /* Validar id encomenda */
  if(encident>=num_total_encomendas)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prodident, encident);
    return;
  }
  /* Validar id produto */
  if(prodident>=num_total_produtos)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prodident, encident);
    return;
  }
  /* Validar se o id do produto ja existe na encomenda */
  prod_enc_id=-1;
  for(i=0; i<encomendas[encident].num_prods; i++)
    if(encomendas[encident].prods[i].produto_id==prodident)
      prod_enc_id=i;
  if(prod_enc_id==-1)
  {
    return;
  }
  /* Remover o produto da encomenda e ajusta o peso */
  /* Ajusta o peso da encomenda - decrementa o produto a retirar */
  qtd_add_stock=encomendas[encident].prods[prod_enc_id].quantidade;
  peso_remover=stock_produto[prodident].peso*qtd_add_stock;
  encomendas[encident].peso_total-=peso_remover;
  /* Remove o elemento do array e move todos os outros produtos */
  numprods=encomendas[encident].num_prods;
  if((numprods>1) && (prodident!=encomendas[encident].prods[numprods-1].produto_id))
    for(i=prod_enc_id; i<(numprods-1); i++)
    {
      encomendas[encident].prods[i].produto_id=encomendas[encident].prods[i+1].produto_id;
      encomendas[encident].prods[i].quantidade=encomendas[encident].prods[i+1].quantidade;
    }
  /* Decrementa o numero de produtos da encomenda */
  encomendas[encident].num_prods--;
  /* Acrescenta o numero de produtos no stock */
  stock_produto[prodident].quantidade += qtd_add_stock;
}

void custo_enc(int encident)
{
  int custo_total;
  int id_aux;
  int qtd_aux;
  int i;
  /* Validar id encomenda */
  if(encident>=num_total_encomendas)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", encident);
    return;
  }
  /* Calcular o custo total da encomenda */
  custo_total = 0;
  for (i = 0; i < encomendas[encident].num_prods; i++)		/* Ciclo de calculo do custo total */
  {
    id_aux = encomendas[encident].prods[i].produto_id;        /* Identificador id produto no stock */
    qtd_aux = encomendas[encident].prods[i].quantidade;       /* Quantidade do produto na encomenda */
    custo_total += stock_produto[id_aux].preco*qtd_aux;       /* Adiciona o custo do produto ao total */
  }
  printf("Custo da encomenda %d %d.\n", encident, custo_total);;
}

void procuramax_prod_enc(int prodident)
{
  int maxqtd, encid;
  int eid, i;
  encid=-1;
  maxqtd = -1;
  /* Validar id produto */
  if(prodident>=num_total_produtos)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prodident);
    return;
  }
  for (eid=0; eid<num_total_encomendas; eid++)
    for(i=0; i<encomendas[eid].num_prods; i++)
      if(encomendas[eid].prods[i].produto_id==prodident)
        if(encomendas[eid].prods[i].quantidade>maxqtd)
        {
          encid=eid;
          maxqtd = encomendas[eid].prods[i].quantidade;
        }
  if(encid>-1)
    printf("Maximo produto %d %d %d.\n",prodident, encid, maxqtd);
}

void lista_quant_prod_encomenda(int encident, int prodident)
{
  int ind_prodenc;
  int i;
  /*Validar ID encomenda */
  if(encident >= num_total_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", encident);
    return;
  }
  /* Validar id produto - se existe no stock de produtos */
  if(prodident >= num_total_produtos)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n",prodident);
    return;
  }
  /* Validar id produto - se existe na encomenda */
  ind_prodenc=-1;                                   /* Indice do produto na encomenda - valida se existe */
  for(i=0; i<encomendas[encident].num_prods; i++)
  {
    if(encomendas[encident].prods[i].produto_id==prodident)
    ind_prodenc=i;
  }
  if(ind_prodenc==-1)
    printf("%s %d.\n", stock_produto[prodident].descricao, 0);
  else
    printf("%s %d.\n", stock_produto[prodident].descricao, encomendas[encident].prods[ind_prodenc].quantidade);
}

void mostra_prod_enc(int encident, int prodidenc)
{
  int prodident=encomendas[encident].prods[prodidenc].produto_id;
  printf("* %s %d %d\n",stock_produto[prodident].descricao, stock_produto[prodident].preco, encomendas[encident].prods[prodidenc].quantidade);
}

/* Funcoes de Ordenacao */

/* 1)- Ordenacao de produtos - do Stock de produtos - Ordenacao crescente preco, id */
/* 2)- Ordenacao de produtos - da encomenda - Ordenacao crescente descricao */

int stock_prodids_ord[MAXPRODS];

void init_prodord_array(int num_prods) 
{
  /* Inicializa o array de ordenacao de IDs 1) com a ordem original do Stock 2) Ordem ids da encomenda */
  int i;
  for(i=0; i<num_prods; i++)
    stock_prodids_ord[i]=i;
}

void troca(int *xp, int *yp)                /* 1) 2) troca os ids no array de indices */
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int compara_prods(int encident, int idprod1, int idprod2)  /* menor ou igual - usado na ordenacao */
{                                           /* 1) encident = -1 (stock produtos)  ;  2) encident = indent encomenda */
    int resultado;                          /* -1- menor: troca os ids ; -0- maior: nao troca os ids */
    if(encident==-1)                        /* 1) retorna: idprod1.preco < idprod2.preco 1-true 0-false */
    {                                       /* 1) retorna: idprod1.id < idprod2.id 1-true 0-false */
      if(stock_produto[idprod1].preco<stock_produto[idprod2].preco)
        resultado=1;
      else if((stock_produto[idprod1].preco==stock_produto[idprod2].preco) && (idprod1<=idprod2))
        resultado=1;
      else
        resultado = 0;
    } else {                                /* 2) retorna: idprod1.descricao < idprod2.descricao 1-true 0-false */
      resultado = strcmp(stock_produto[encomendas[encident].prods[idprod1].produto_id].descricao,stock_produto[encomendas[encident].prods[idprod2].produto_id].descricao);
      if(resultado<=0)
        resultado=1;
      else
        resultado=0;
    }
    return resultado;
}

/* Codigo de ordenacao MERGE */
void merge(int encident, int l, int m, int r) /* Junta dois arrays, subarray arr[l..m] e arr[m+1..r] */
{
  int i, j, k;
  const int n1 = m - l + 1;
  const int n2 =  r - m;
  /* Cria arrays temporarios */
  int L[MAXPRODS];
  int R[MAXPRODS];
  /* copia os dados para L[] and R[] */
  for (i = 0; i < n1; i++)
    L[i] = stock_prodids_ord[l + i];
  for (j = 0; j < n2; j++)
    R[j] = stock_prodids_ord[m + 1+ j];
  /* junta os arraytemp em stock_prodids_ord[l..r]*/
  i = 0;                                              /* Indice inicial de subarray 1 */
  j = 0;                                              /* Indice inicial de subarray 2 */
  k = l;                                              /* Indice inicial de subarray 3 */
  while (i < n1 && j < n2)
  {
    if (compara_prods(encident, L[i], R[j]))
    {
      stock_prodids_ord[k] = L[i];
      i++;
    }else{
      stock_prodids_ord[k] = R[j];
      j++;
    }
      k++;
  }
  /* Copia os ultimos elementos de L[], caso existam */
  while (i < n1)
  {
    stock_prodids_ord[k] = L[i];
    i++;
    k++;
  }
  /* Copia os ultimos elementos de R[], caso existam */
    while (j < n2)
    {
      stock_prodids_ord[k] = R[j];
      j++;
      k++;
    }
}
/* l paa indices da esquerda e r para direita do sub-array do arr a ser ordenado */
void mergeSort(int encident, int l, int r)
{
  if (l < r)
  {
    /* O mesmo que (l+r)/2, evitando overflow para l e h grandes */
    int m = l+(r-l)/2;
    /* ordena as primeiras e segundas metades */
    mergeSort(encident, l, m);
    mergeSort(encident, m+1, r);
    merge(encident, l, m, r);
  }
}
/* Fim do codigo de ordenacao */

void lista_prods_ordenado()                       /* 1) Mostra o array ordenado de produtos do stock de produtos */
{
  int i;
  printf("Produtos\n");
  for (i = 0; i < num_total_produtos; i++)
    mostra_produto (stock_produto[stock_prodids_ord[i]]);
}

void lista_prods_encomenda_alf(int encident)      /* 2) lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
{
  int numprodsenc;
  int i;
  numprodsenc=encomendas[encident].num_prods;
  printf("Encomenda %d\n", encident);
  for(i=0; i<numprodsenc; i++) 							      /* Ciclo para mostrar os produtos da encomenda */
  {
      mostra_prod_enc(encident, stock_prodids_ord[i]);
  }
}

void lista_prods_ordenados(int encident)
{
  int numprodsenc;
  if(encident==-1)                                /* 1) Ordenacao de produtos do stock por ordem crescente preco, id */
  {            
    init_prodord_array(num_total_produtos);
    mergeSort(-1, 0, num_total_produtos - 1);
    lista_prods_ordenado();
  } else {                                        /* 2) lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
    /* Validar ID encomenda */
    if(encident >= num_total_encomendas)
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", encident);
      return;
    }
      numprodsenc=encomendas[encident].num_prods;
      init_prodord_array(numprodsenc);
      mergeSort(encident, 0, numprodsenc - 1);
      lista_prods_encomenda_alf(encident);
    }
}

/* Parsing dos comandos */

char cmd[1024];         /* Confirmar a dimensao maxima possivel dos comandos */
char proddesc[DIMDESC]; /* Descricao do Produto */
int encident;           /* Identificador encomenda */
int prodident;          /* Identificador de produto */
int prodpreco;          /* Preco do produto */
int prodpeso;           /* Peso do produto */
int prodqtd;            /* Quantidade do produto */

void ler_comando()
{
  char *posnl, *resultado;
  resultado=fgets(cmd,100,stdin);
  if(resultado==NULL){
    cmd[0]='x';        /* Exit - End of file inesperado */
    cmd[1]=0;
  }
  if ((posnl=strchr(cmd, '\n')) != NULL)
    *posnl = 0;
}

void processa_comando() /* Execucao dos Comandos */
{
  int ncmds;
  switch(cmd[0])
  {
    case 'a':                                           /* adiciona um novo produto ao sistema */
    ncmds=sscanf(cmd,"a %[^:]:%d:%d:%d",proddesc,&prodpreco,&prodpeso,&prodqtd);
    if(ncmds==4)                                    
      adiciona_produto(proddesc, prodpreco, prodpeso, prodqtd);
    break;
    case 'l':                                           /* lista todos os produtos existentes no sistema por ordem crescente de preco. */
      lista_prods_ordenados(-1);  
    break;
    case 'q':                                           /* adiciona stock a um produto existente no sistema */
      ncmds=sscanf(cmd,"q %d:%d",&prodident,&prodqtd);  
      if(ncmds==2)
        adiciona_stock(prodident, prodqtd);
      break;
    case 'N':                                           /* cria uma nova encomenda */
      nova_encomenda();             
      break;
    case 'A':                                           /* adiciona um produto a uma encomenda */
      ncmds=sscanf(cmd,"A %d:%d:%d",&encident,&prodident,&prodqtd);
      if(ncmds==3) 
        adiciona_produto_encomenda(encident, prodident, prodqtd);
      break;
    case 'E':                                           /* lista a descricao e a quantidade de um produto numa encomenda */
      ncmds=sscanf(cmd, "E %d:%d",&encident,&prodident);
      if(ncmds==2)
        lista_quant_prod_encomenda(encident, prodident);
      break;
    case 'r':                                           /* remove stock a um produto existente */
      ncmds=sscanf(cmd, "r %d:%d",&prodident,&prodqtd);
      if(ncmds==2)
        remove_stock_prod(prodident, prodqtd);
      break;
    case 'R':                                           /* remove um produto de uma encomenda */
      ncmds=sscanf(cmd, "R %d:%d",&encident,&prodident);
      if(ncmds==2)
        remove_prod_enc(encident, prodident);
      break;
    case 'L':                                           /* lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
      ncmds=sscanf(cmd, "L %d",&encident);
      if(ncmds==1)
        lista_prods_ordenados(encident);
      break;
    case 'C':                                           /* calcula o custo de uma encomenda */
    ncmds=sscanf(cmd, "C %d",&encident);
    if(ncmds==1)
      custo_enc(encident);
     break;
    case 'p':                                           /* altera o preco de um produto existente no sistema */
      ncmds=sscanf(cmd, "p %d:%d",&prodident,&prodpreco);
      if(ncmds==2)
        altera_prod_preco(prodident, prodpreco);
      break;
    case 'm':                                           /* lista o identificador da encomenda em que o produto dado ocorre mais vezes */
      ncmds=sscanf(cmd, "m %d",&prodident);
      if(ncmds==1)
        procuramax_prod_enc(prodident);
      break;
    case 'x':                                            /* termina o programa */
      break;
  }
}

/*------------------------------ Funcao main ---------------------------------*/
int main ()
{
  do 
  {
    ler_comando();
    processa_comando();
  } while (cmd[0]!='x');
  return 0;
}
