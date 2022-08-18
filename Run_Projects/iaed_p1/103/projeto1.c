#include <stdio.h>
#include <string.h>

/* ===========================================================================*/
/*                              Constantes                                    */
/* ===========================================================================*/
#define TRUE 1
#define FALSE -1
#define NOME_MAXDIM 64  /*numero maximo de caracteres do nome de um produto */
#define MAX_PRODS 10000 /*numero maximo de produtos introduziveis no sistema*/
#define MAX_PESO 200    /*peso maximo de uma encomenda                      */
#define MAX_ENC 500     /*numero maximo de encomendas permitidas            */


/* ===========================================================================*/
/*                                 Produto                                    */
/* ===========================================================================*/
  typedef struct produto{
      char nome[NOME_MAXDIM];
      int preco;
      int peso;
      int stock;
  }produto;

void cria_produto(produto vetor[],int i,char c[],int preco, int peso,int stock);
void cria_copia_produto(produto vetor1[],int d, produto vetor[],int f);
int produto_in_stock(produto p,int qtd);
int eh_idp(int n);
void altera_stock_produto(produto vetor[],int idp,int qtd);

/* ===========================================================================*/
/*                              Encomenda                                     */
/* ===========================================================================*/
  typedef struct encomenda{
      int peso;
      produto produtos[MAX_PESO];
      int n_produtos;
      int idps[MAX_PESO];
  }encomenda;


int calcula_peso(encomenda e);
void novo_produto_encomenda(int ide,int idp, int qtd);
void adiciona_qtd_encomenda(int ide,int indice, int qtd);
int eh_ide(int ide);
int produto_em_encomenda(encomenda e,int ide);



/* ===========================================================================*/
/*                        Comandos do Sistema                                 */
/* ===========================================================================*/
void __a__();
void __q__();
void __N__();
void __A__();
void __r__();
void __R__();
void __C__();
void __p__();
void __E__();
void __m__();
void __l__();
void __L__();
void __x__();

/* ===========================================================================*/
/*                         Funcoes de ordenacao                               */
/* ===========================================================================*/
void Merge_int(int A[],int esquerdo,int direito,int Fim,int B[],int v[],int v2[]);
void CopiaVetor_int(int B[],int A[],int n,int v2[],int v[]);
void MergeSort_int(int A[],int B[],int n,int v[],int v2[]);
    /*igual, mas para strings:*/
void Merge_str(char A[][NOME_MAXDIM],int esquerdo,int direito,int Fim, char B[][NOME_MAXDIM],int v[],int v2[]);
void CopiaVetor_str(char B[][NOME_MAXDIM],char A[][NOME_MAXDIM],int n,int v2[],int v[]);
void MergeSort_str(char A[][NOME_MAXDIM],char B[][NOME_MAXDIM],int n,int v[],int v2[]);


/*========================= variaveis globais ================================*/

produto sistema[MAX_PRODS];   /*vetor de produtos do sistema*/
encomenda encomendas[MAX_ENC];/*vetor de encomendas*/
int ultimo_idp;/*'ultimo_idp' eh o indicador do idp do ultimo produto criado*/
int ultimo_ide;/*'ultimo_ide' eh o indicador do ide da ultima encomenda criada */



/*================================== MAIN ======================================
  Estrutura principal do programa.
  Aqui o programa le do input os varios comandos e dados e direciona o programa
  para a funcao correspondente.
==============================================================================*/
int main() {
    char c;
    ultimo_idp=-1;
    ultimo_ide=-1;
    while ((c=getchar())!=EOF)
    {
        switch (c) {
            case 'a':
                __a__();
                break;
            case 'q':
                __q__();
                break;
            case 'N':
                __N__();
                break;
            case 'A':
                __A__();
                break;
            case 'r':
                __r__();
                break;
            case 'R':
                __R__();
                break;
            case 'C':
                __C__();
                break;
            case 'p':
                __p__();
                break;
            case 'E':
                __E__();
                break;
            case 'm':
                __m__();
                break;
            case 'l':
                __l__();
                break;
            case 'L':
                __L__();
                break;
            case 'x':
                return 0;
        }
    }
    return 0;
}

/* ===========================================================================*/
/*                         Comandos do sistema                                */
/*                             (definicao)                                    */
/* ===========================================================================*/
void __a__() {
    /*Adidiciona um produto ao sistema.
      Imprime uma mensagem: 'Novo produto <idp>.',sendo idp o numero do produto
      do sistema (sendo <idp>='ultimo_idp').*/

    int preco,peso,qtd;
    char descricao[NOME_MAXDIM];
    ++ultimo_idp;
    scanf(" %[^:]:%d:%d:%d",descricao,&preco,&peso,&qtd );
    cria_produto(sistema,ultimo_idp,descricao,preco,peso,qtd);
    printf("Novo produto %d.\n",ultimo_idp);
}
void __q__() {
    /*Adiciona stock a um produto <idp> existente no sistema.
      Gera um erro caso o produto que se queira alterar nao exista no sistema*/

    int idp,qtd;
    scanf("%d:%d", &idp, &qtd);
    if (eh_idp(idp)==TRUE) {
        altera_stock_produto(sistema,idp,qtd);
    }
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp );
    }
}
void __N__() {
    /*Inicializa uma nova encomenda, colocando as suas 'caracteristicas' a 0.
      Imprime a mensagem: 'Nova encomenda <ide>.'   (sendo <ide>='ultimo_ide')*/

    ultimo_ide++;
    encomendas[ultimo_ide].peso=0;
    encomendas[ultimo_ide].n_produtos=0;
    printf("Nova encomenda %d.\n", ultimo_ide);
}
void __A__() {
    /*Adiciona produto a uma encomenda. Se o produto estiver na encomenda
      soma ah quantidade existente a quantidade que se pretende adicionar.
      Gera mensagens de erro se:
      * encomenda nao existir.
      * produto nao existir no sistema
      * nao hexistir stock de produto suficiente no sistema.
      * a quantidade que se quiser adicionar fizer com que o peso total da encomenda seja superior a 200 unidades.*/

    int ide,idp,qtd,indice;
    scanf("%d:%d:%d",&ide,&idp,&qtd);
    if (eh_ide(ide)==FALSE)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if (eh_idp(idp)==FALSE)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else if (produto_in_stock(sistema[idp],qtd)==FALSE)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
    else if (((encomendas[ide].peso)+(qtd*(sistema[idp].peso)))>200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
    else {
        indice=produto_em_encomenda(encomendas[ide],idp);
        if (indice==FALSE) {
            novo_produto_encomenda(ide,idp,qtd);
        }
        else{
            adiciona_qtd_encomenda(ide,indice,qtd);
            altera_stock_produto(sistema,idp,(-1)*qtd);
        }
    }
}
void __r__() {
    /*Remove stock a um produto do sistema.
      Gera mensagem de erro se:
      * produto nao existir no sistema.
      * quantidade que se pretende remover for superior ao stock existente.*/

    int idp,qtd;
    scanf("%d:%d",&idp,&qtd);
    if (eh_idp(idp)==TRUE) {
        if (produto_in_stock(sistema[idp],qtd)==TRUE) {
            altera_stock_produto(sistema,idp,(-1)*qtd);
        }
        else{
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp );
        }
    }
    else{
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp );
    }
}
void __R__() {
    /*Remove um produto de uma encomenda.
      Gera mensagem de erro se:
      * encomenda nao tiver sido criada.
      * produto a remover nao exisitr no sistema.*/


    int ide,idp,qtd,peso,indice,prods_enc;
    scanf("%d:%d", &ide, &idp);
    if (eh_ide(ide)==FALSE)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else{
        if (eh_idp(idp)==FALSE)
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        else{
            indice = produto_em_encomenda(encomendas[ide],idp);
            if (indice != FALSE) {

                qtd = encomendas[ide].produtos[indice].stock;
                peso = encomendas[ide].produtos[indice].peso;
                prods_enc=encomendas[ide].n_produtos-1;

                encomendas[ide].peso -= qtd * peso;
                altera_stock_produto(sistema, idp, qtd);

                if ( indice < (prods_enc) ) {
                    /*se o produto a ser removido nao eh o ultimo da encomenda,
                    copia o ultimo produto para a posicao do que se pretende apagar*/
                    cria_copia_produto(encomendas[ide].produtos, prods_enc, encomendas[ide].produtos, indice);

                    encomendas[ide].idps[indice]=encomendas[ide].idps[prods_enc];
                    encomendas[ide].produtos[indice].stock = encomendas[ide].produtos[prods_enc].stock;
                }
                /* invalida-se o ultimo produto, colocando idp a -1 e tudo o resto a 0*/
                cria_produto(encomendas[ide].produtos,prods_enc,"",0,0,0);
                encomendas[ide].idps[prods_enc] = -1;

                encomendas[ide].n_produtos -= 1;
            }
        }
    }
}
void __C__() {
    /* Imprime uma mensagem com o custo total da encomenda <ide>.
       Gera mensagem de erro se:
       * encomenda nao tiver sido criada.*/

    int ide,d,total;
    scanf("%d",&ide);
    if (eh_ide(ide)==TRUE) {
        total=0;

        for (d = 0; d < encomendas[ide].n_produtos; d++) {
            total+=encomendas[ide].produtos[d].stock*encomendas[ide].produtos[d].preco;
        }
        printf("Custo da encomenda %d %d.\n",ide,total);
    }
    else{
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    }
}
void __p__() {
    /*Altera o preco de um produto em todas as encomendas e no sistema.
      Gera mensagem de erro se:
      * produto nao existir no sistema.*/

    int idp,preco,d,indice;
    scanf("%d:%d",&idp,&preco);
    if (eh_idp(idp)==TRUE) {
        sistema[idp].preco=preco;
        for (d = 0; d<=ultimo_ide; d++) {
            indice=produto_em_encomenda(encomendas[d],idp);
            if (indice != FALSE) {
                encomendas[d].produtos[indice].preco=preco;
            }
        }
    }
    else{
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp );
    }
}
void __E__() {
    /*Imprime a descricao e a quantidade de um produto numa encomenda.
      Gera mesagem de erro se:
      * a encomenda nao tiver sido ainda criada.
      * o produto nao existir no sistema. */

    int ide,idp,indice;
    scanf("%d:%d",&ide,&idp);
    if (eh_ide(ide)==TRUE) {
        if (eh_idp(idp)==TRUE) {
            indice = produto_em_encomenda(encomendas[ide],idp);
            if (indice != FALSE)
                printf("%s %d.\n",encomendas[ide].produtos[indice].nome,encomendas[ide].produtos[indice].stock);
            else     /*Se o produto nao estiver na encomenda, imprime o valor 0.*/
                printf("%s 0.\n",sistema[idp].nome);
        }
        else{
            printf("Impossivel listar produto %d. Produto inexistente.\n",idp );
        }
    }
    else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide );
    }
}
void __m__() {
    /* Percorre todas as encomendas e imprime a a maior quantidade de produto<idp> que encontrar
       Gera uma mensagem de erro se o produto nao tiver sido introduzido no sistema.*/
    int idp,ide,qtd,d,indice;
    scanf("%d",&idp);
    if (eh_idp(idp)==TRUE) {
        ide=-1;
        qtd=-1;  /*vao ser utilizadas para guardar o menor ide vs maior stock.*/
        for (d = 0; d <= ultimo_ide; d++) {
            indice = produto_em_encomenda(encomendas[d],idp);
            if (indice != FALSE) {
                if (encomendas[d].produtos[indice].stock>qtd) {
                    qtd=encomendas[d].produtos[indice].stock;
                    ide=d;
                }
            }
        }
        if (ide>=0) {
            printf("Maximo produto %d %d %d.\n",idp,ide,qtd);
        }
    }
    else{
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp );
    }
}

void __l__(){
    /*Lista todos os produtos do sistema por ordem crescente de preco.
      1-criacao de 2 vetores. um precos e um de idps.
      2-ordenacao dos idps por ordem crescente de preco (cada idp corresponde uma preco).
        Utilizacao do metodo MergeSort.
      3-listagem dos produtos a partir dos idps ordenados.*/

    int vetor_idps[MAX_PRODS],vetor_precos[MAX_PRODS];
    int d,v_precos_aux[MAX_PRODS],v_idps_aux[MAX_PRODS];
    /*vetor_idps_aux e vetor_precos_aux sao vetores auxiliares ah ordenacao*/


    for (d = 0; d <=ultimo_idp; d++) {
        vetor_precos[d]=sistema[d].preco;
        vetor_idps[d]=d;
    }

    MergeSort_int(vetor_precos,v_precos_aux,ultimo_idp+1,vetor_idps,v_idps_aux);

    printf("Produtos\n");
    for (d = 0; d <= ultimo_idp; d++) {
        printf("* %s %d %d\n",sistema[vetor_idps[d]].nome,
               sistema[vetor_idps[d]].preco,sistema[vetor_idps[d]].stock);
    }
}
void __L__(){
    /*lista os produtos da encomenda <ide> por ordem alfabetica.
      1-criacao de 2 vetores. um strings e um de indices
      2-ordenacao dos indices por ordem alfabetica (cada indice corresponde uma string).
        Utilizacao do metodo MergeSort.
      3-listagem dos produtos a partir dos indices ordenados.

      Gera um erro se a encomenda nao tiver ainda sido criada.*/

    int i,ide;
    int vetor_indices[MAX_PESO],vetor_indices_aux[MAX_PESO];
    char tab_aux[MAX_PESO][NOME_MAXDIM],tab[MAX_PESO][NOME_MAXDIM];
    /*'vetor_indices_aux' e 'tab_aux' sao vetores auxiliares para a ordenacao*/
    scanf("%d",&ide);
    if (eh_ide(ide)==TRUE) {
        printf("Encomenda %d\n",ide );
        for (i = 0; i < encomendas[ide].n_produtos; i++) {
            strcpy(tab[i],encomendas[ide].produtos[i].nome);
            vetor_indices[i]=i;
        }

        MergeSort_str(tab,tab_aux,encomendas[ide].n_produtos,vetor_indices,vetor_indices_aux);

        for (i = 0; i < encomendas[ide].n_produtos; i++) {
            printf("* %s %d %d\n",tab[i],
            encomendas[ide].produtos[vetor_indices[i]].preco,
            encomendas[ide].produtos[vetor_indices[i]].stock );
        }
    }
    else printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);

}




/* ===========================================================================*/
/*                                 Produto                                    */
/* ===========================================================================*/

void cria_produto(produto vetor[],int i, char c[],int preco,int peso,int stock){
/*cria um produto com as caracteristicas dadas em argumento, no vetor de produtos 'vetor[]' posicao 'i'*/
    vetor[i].preco = preco;
    vetor[i].stock = stock;
    vetor[i].peso = peso;
    strcpy(vetor[i].nome,c);
}
void cria_copia_produto(produto vetor1[],int d, produto vetor[],int f){
    /*cria copia das caracteristicas principais do produto que esta em 'vetor1[d]' para 'vetor[d]'*/
    vetor[f].preco = vetor1[d].preco;
    vetor[f].peso = vetor1[d].peso;
    strcpy(vetor[f].nome,vetor1[d].nome);
}

int eh_idp(int idp){
    /*Verifica do o inteiro idp corresponde ao idp de um produto existente*/
    if (idp>ultimo_idp) {
        return FALSE;
    }
    else{
        return TRUE;
    }
}

int produto_in_stock(produto p,int qtd){
    /*Verifica se o produto 'p' tem stock superior a 'qtd'*/
    if (p.stock<qtd) {
        return FALSE;
    }
    else{
        return TRUE;
    }
}

void altera_stock_produto(produto vetor[],int idp,int qtd){
    /*soma 'qtd' ao stock do produto 'vetor['idp']'.*/
    vetor[idp].stock+=qtd;
}

/* ===========================================================================*/
/*                                Encomenda                                   */
/* ===========================================================================*/

void novo_produto_encomenda(int ide,int idp,int qtd){
    /*Adicioona um novo produto a uma encomenda. Copia as caracteristicas do produtos
      acedendo ao sistema.*/
    cria_copia_produto(sistema,idp,encomendas[ide].produtos,encomendas[ide].n_produtos);
    encomendas[ide].produtos[encomendas[ide].n_produtos].stock=qtd;
    altera_stock_produto(sistema,idp,(-1)*qtd);
    encomendas[ide].peso+=(sistema[idp].peso*qtd);
    encomendas[ide].idps[encomendas[ide].n_produtos]=idp;
    encomendas[ide].n_produtos++;
}
void adiciona_qtd_encomenda(int ide,int indice, int qtd){
    /*adicona quantidade de produto a uma encomenda onde o produto ja exista.*/
    altera_stock_produto(encomendas[ide].produtos,indice,qtd);
    encomendas[ide].peso+=(encomendas[ide].produtos[indice].peso*qtd);
}

int eh_ide(int ide){
    /*Verifica se a encomenda<ide> eh uma encomenda valida*/
    if (ide > ultimo_ide) {
        return FALSE;
    }
    else{
        return TRUE;
    }
}

int produto_em_encomenda(encomenda encomenda,int idp){
    /*esta funcao verifica se o produto com o idp <idp> esta na encomenda <encomenda>
      e retorna o indice do produto no vetor de produtos na encomenda, caso este exista.*/
    int i;
    for (i = 0; i < encomenda.n_produtos; i++) {
        if (encomenda.idps[i]==idp)
            return i;
    }
    return FALSE;
}

/* ===========================================================================*/
/*                        Funcoes de Ordenacao                                */
/* ===========================================================================*/
int min(int a,int b){
    /*auxiliar aos dois sorts, retorna o menor de 2 numeros.*/
    if (a < b) {
        return a;
    }
    else return b;
}


void MergeSort_int(int A[],int B[],int n,int v[],int v2[])
{
    /* Ordena 2 vetores de inteiros A e v ao mesmo tempo, com 'key' em A.
       B e v2 sao vetores auxiliares ah ordenacao.*/
    int i,tamanho;
    for (tamanho = 1; tamanho < n; tamanho = 2 * tamanho)
    {
        for (i = 0; i < n; i = i + 2 * tamanho)
        {
            Merge_int(A, i, min(i+tamanho, n), min(i+2*tamanho, n), B,v,v2);
        }

        CopiaVetor_int(B, A, n,v2,v);
    }
}


void Merge_int(int A[],int esquerdo,int direito,int Fim,int B[],int v[],int v2[])
{
    /*auxiliar da funcao mergeSort_int.
      junta, ordenados as particoes A[esquerdo :direito-1] com A[direito:Fim-1].
      As alteracoes que faz a 'A', faz a 'v'*/
    int i = esquerdo, j = direito,k;

    for (k = esquerdo; k < Fim; k++) {

        if (i < direito && (j >= Fim || A[i] <= A[j])) {
            v2[k]=v[i];
            B[k] = A[i];
            i = i + 1;
        }
        else {
            v2[k]=v[j];
            B[k] = A[j];
            j = j + 1;
        }
    }
}

void CopiaVetor_int(int B[],int A[],int n,int v2[],int v[])
{
    /*auxiliar da funcao mergeSort_int.*/
    int i;
    for(i = 0; i < n; i++){
        A[i] = B[i];
        v[i] = v2[i];
    }
}

void MergeSort_str(char A[][NOME_MAXDIM],char B[][NOME_MAXDIM],int n,int v[],int v2[])
{
    /*ordena 2 vetores em simultaneo(um de strings e um de inteiros), com chave no vetor de strings.*/
    int i,tamanho;
    for (tamanho = 1; tamanho < n; tamanho = 2 * tamanho)
    {
        for (i = 0; i < n; i = i + 2 * tamanho)
        {
            Merge_str(A, i, min(i+tamanho, n), min(i+2*tamanho, n), B,v,v2);
        }

        CopiaVetor_str(B, A, n,v2,v);
    }
}


void Merge_str(char A[][NOME_MAXDIM],int esquerdo,int direito,int iEnd,char B[][NOME_MAXDIM],int v[],int v2[])
{
    /*auxiliar da funcao mergeSort_str.
      junta, ordenadamente as particoes A[esquerdo :direito-1] com A[direito:Fim-1].
      As alteracoes que faz a 'A', faz a 'v'*/
    int i = esquerdo, j = direito,k;

    for (k = esquerdo; k < iEnd; k++) {

        if (i < direito && (j >= iEnd || (strcmp(A[i], A[j])<=0))) {
            v2[k]=v[i];
            strcpy(B[k],A[i]);
            i = i + 1;
        }
        else {
            v2[k]=v[j];
            strcpy(B[k],A[j]);
            j = j + 1;
        }
    }
}

void CopiaVetor_str(char B[][NOME_MAXDIM],char A[][NOME_MAXDIM],int n,int v2[],int v[])
{
    /*auxiliar da funcao mergeSort_str.*/
    int i;
    for(i = 0; i < n; i++){
        strcpy(A[i], B[i]);
        v[i] = v2[i];
    }
}
