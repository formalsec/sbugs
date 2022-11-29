#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>


/* constantes guias */
#define MAX_IDENTIFICADOR 10000 
#define MAX_DESCRICAO 64 /* correspondendo a 63 caracteres diferentes de \0 */
#define MIN_PRECO 0
#define MIN_PESO 0
#define MIN_QUANDTIDADE 0
#define MAX_ENCOMENDA 500
#define MAX_PESO 200

#define TRUE 1
#define FALSE 0

#define EXISTE_ENCOMENDA procura_encomenda( ide )
#define N procura_produto( idp ) 
#define Q vetor_encomenda[ide].dados[idp].qtd - qtd
#define W ( vetor_produto[idp].qtd * vetor_produto[idp].peso) + vetor_encomenda[ide].peso  
#define S vetor_produto[idp].qtd - qtd
#define less( A, B) (vetor_produto[A].preco < vetor_produto[B].preco)
#define exch( A, B) { vetor_produto[t] = A; A = B; B = t; }
#define lessc( A, B) (strcmp( ha, hb) < 0)


/* estrutura produto */
typedef struct{
    char descricao[MAX_DESCRICAO]; 
    int preco;      /* pre?o */
    int peso;       /* peso */
    int qtd;        /* quantidade */
}produto;

/* estrutura encomenda */
typedef struct{
    produto dados[MAX_IDENTIFICADOR];
    int ide;
    int idp;
    int qtd;
    int peso;     /* peso da encomenda */        
}encomenda;



int contador_encomendas = 0;   /*  quantidade de encomendas existentes no sistema*/
int contador_produtos = 0;     /* quantidade de produtos no sistema */


int A,B;
char ha[MAX_DESCRICAO], hb[MAX_DESCRICAO];
char vaz[MAX_DESCRICAO] = " "; 


encomenda vetor_encomenda[MAX_ENCOMENDA];
produto vetor_produto[MAX_IDENTIFICADOR];

/* Funcoes auxiliares*/

void inicializa_vetor();
int compara_ids(int e, int i);
void sort(int i);
int procura_encomenda(int ide); 
int procura_produto(int idp); 
void mergesort(produto vetor_produto[MAX_IDENTIFICADOR], int left, int right);
void merge( produto vetor_produto[MAX_IDENTIFICADOR], int left, int y, int right);
void insertion( encomenda vetor_encomenda[MAX_ENCOMENDA], int left, int right);

/* Funcoes principais*/

void adiciona_produto(); 
void adiciona_stock_produto(); 
void cria_encomenda();
void adiciona_produto_encomenda(); 
void remove_produto_encomenda(); 
void remove_stock_produto();
void calcula_custo();
void muda_preco_produto();
void lista_quantidade_produto_enc();
void imprime_encomendas();
void lista_produtos_existentes(); 
void lista_encomendas_alfabeticamente(); 

/*====================================================================================================*/

/*                                        FUNCOES AUXILIARES                                          */

/*====================================================================================================*/

/* a funcao inicializa_vetor inicializa o vetor de encomendas com encomendas nulas.
*/

void inicializa_vetor(){
    int i, b , g, j;
    for ( i = 0; i< MAX_IDENTIFICADOR; i++) {
        vetor_produto[i].qtd = 0;
        vetor_produto[i].preco = 0;
        vetor_produto[i].peso = 0;
        for (j = 0; j < MAX_DESCRICAO; j++)
            vetor_produto[i].descricao[j] = '\0';
    }
    for( b = 0; b < MAX_ENCOMENDA; b++) {
        vetor_encomenda[b].ide = 0;
        vetor_encomenda[b].idp = 0;
        vetor_encomenda[b].qtd = 0;
        for ( g = 0; g < MAX_IDENTIFICADOR; g++) { 
            vetor_encomenda[b].dados[g].qtd = 0;
            vetor_encomenda[b].dados[g].preco = 0;
            vetor_encomenda[b].dados[g].peso = 0;
        }
    }
}

/* fun??o compara os identificadores e iguala o menor a b */
int compara_ids(int e, int i) { 
    if ( e - i < 0 ) {
        return  e;
    }
    else {
        return i;    
    }
}

/* fun??o que procura atrav?s do identificador de encomenda a mesma, verificando a sua exist?ncia */
int procura_encomenda( int ide ) {
    int i;
    for(i = 0 ; i < contador_encomendas; i++) {
        if ( (vetor_encomenda[i].ide - vetor_encomenda[ide].ide) == 0) {
            return i;
        }
    }
    return -1;
}

/* fun??o que procura atrav?s do identificador de produto o mesmo, verificando a sua exist?ncia */
int procura_produto(  int idp ) {
    int i,b;
    for( i = 0 ; i < contador_encomendas; i++) {
        for ( b = 0; b < contador_produtos; b++){ 
            if ( (vetor_encomenda[i].dados - idp) == 0) {
                break;
            }
        }
    }
    if ( i == contador_encomendas ) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, i);
        return -1;
    }
    return i;
}

/* A funcao ordena as encomendas por ordem alfabetica da sua respetiva descricao. */

int right, left, w, t, v, o, b;
int cicle,cond,i;
char help_i[MAX_DESCRICAO], help_j[MAX_DESCRICAO];
void insertion( encomenda vetor_encomenda[MAX_ENCOMENDA], int left, int right){
     for ( i = 0; i < contador_encomendas; i++) {
        for ( b = 0; i < contador_produtos; b++){ 
            for( cicle = left + 1; cicle <= right; i++){
                strcpy( help_i, vetor_encomenda[i].dados[b].descricao);
                strcpy( help_j, vetor_encomenda[i+1].dados[b].descricao);
                cond = cicle - 1;
                while ( cond >= left && lessc( help_i, vetor_encomenda[cond].dados[b].descricao)){
                    cond--;
                }
              strcpy(  help_i, vetor_encomenda[i+1].dados[b].descricao);
            }
        }
    }
}




/* A funcao sort ordena as encomendas sempre que estes sao adicionados ao vetor ou sempre que eh efetuada alguma alteracao.
*/
produto aux[MAX_IDENTIFICADOR];

void merge( produto vetor_produto[MAX_IDENTIFICADOR], int left, int v, int right)
{
    for (w = v+1; w > left; w--) { 
        aux[w-1].preco = vetor_produto[w-1].preco;
    }
    for (t = v; t < right; t++) { 
        aux[right+v-t].preco = vetor_produto[t+1].preco;
    }   
    for (o = left; o <= right; o++){ 
            if (less(aux[t].preco, aux[w].preco) || i > v){  
                vetor_produto[o].preco = aux[t--].preco;
            }
            else { 
                vetor_produto[o].preco = aux[w++].preco;
            }
    }
}

void mergesort( produto vetor_produto[MAX_IDENTIFICADOR], int left, int right) {
    v = (right+left) / 2;
    if (right <= left)
        return;
    mergesort(vetor_produto, left, v);
    mergesort(vetor_produto, v+1, right);
    merge(vetor_produto, left, v, right);
}



/*====================================================================================================*/

/*                                        FUNCOES PRINCIPAIS                                          */

/*====================================================================================================*/


/* A funcao adiciona_produto recebe um produto e adiciona-o ao vetor_produto, ordenando-os por ordem de indentificador.
*/
void adiciona_produto() {
    scanf(" %[^:]:%d:%d:%d\n", vetor_produto[contador_produtos].descricao, &vetor_produto[contador_produtos].preco, &vetor_produto[contador_produtos].peso, &vetor_produto[contador_produtos].qtd);
    printf("Novo produto %d.\n", contador_produtos);
    contador_produtos++;
}

/* A funcao adiciona_stock_produto recebe um identificador de produto e uma quantidade que sao atualizados caso j? contenham stock.*/
int i, n;
void adiciona_stock_produto() {
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    i = procura_produto( idp);
    n = vetor_produto[i].qtd + qtd;
    if ( n * vetor_produto[i].peso == MAX_PESO ) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
    else {
        vetor_produto[i].qtd = n;
    }
}

/* A funcao cria_encomenda cria uma nova encomenda identificando-a com o numero seguinte da identificacao.
*/
void cria_encomenda( ) {
    printf("Nova encomenda %d.\n", contador_encomendas);
    contador_encomendas++;
}


/* A funcao adiciona_produto_encomenda recebe um identificador de encomenda e outro  produto seguido por uma quantidade que atualizaram o conteudo do vetor_encomenda.
*/
void adiciona_produto_encomenda( ) {
    int ide, idp, qtd;
    scanf(" %d:%d:%d", &ide, &idp, &qtd);
     if ( EXISTE_ENCOMENDA > 0 &&  N > 0 )  { 
        if ( Q  ) { 
            if ( W <= MAX_PESO){ 
                vetor_encomenda[ide].dados[MAX_PESO] = vetor_produto[idp];
                remove_stock_produto(idp, qtd);
                vetor_encomenda[ide].peso = W ;
            }
            else {
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }
        }
        else {
            printf( "Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        }
    }
    else if ( EXISTE_ENCOMENDA < 0 && N > 0) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if ( N <= 0 && EXISTE_ENCOMENDA > 0 ) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
}

/* A funcao remove_produto_encomenda recebe um identificador de encomenda e outro de produto, efetuando a remocao do correspondente produto da encomenda. 
*/
int i;
void remove_produto_encomenda( ) {
    int ide, idp;
    scanf(" %d:%d", &ide, &idp);
    if ( EXISTE_ENCOMENDA > 0 &&    N > 0 ){
        vetor_encomenda[ide].peso = vetor_encomenda[ide].peso - vetor_produto[idp].peso;
        for( i = idp; i <= contador_encomendas ; i++) {
            vetor_encomenda[ide].dados[idp] = vetor_encomenda[ide].dados[idp + 1]; 
        }
        contador_encomendas = contador_encomendas - 1;
    }
    else if ( EXISTE_ENCOMENDA < 0 && N > 0) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if ( N < 0 && EXISTE_ENCOMENDA > 0 ) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
}

/* A funcao remove_stock_produto recebe um identificador de produto e uma quantidade que e subtaraida ao stock existente previamente.
 */
void remove_stock_produto( ){
    int idp,qtd;
    scanf(" %d:%d", &idp, &qtd);
    if ( N > 0 ){
        if ( S  ){ 
            vetor_produto[idp].qtd = vetor_produto[idp].qtd - qtd;
        }
        else {
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd,idp);
        }
    }
    else {
        printf( "Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
}


/* A funcao calcula_custo recebe um identificador de encomenda, de modo a calcular o custo da mesma encomenda.
*/
int K;
int c = 0;
void calcula_custo( ){
    int ide;
    scanf(" %d", &ide);
    if ( EXISTE_ENCOMENDA > 0){
        for ( K = 0; K <= ide ; K++){
            c = c + vetor_encomenda[ide].dados[K].qtd * vetor_encomenda[ide].dados[K].preco; 
            printf("Custo da encomenda %d %d.\n", ide, c);
        }
    }
    else{
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
}

/* A funcao muda_preco_produto recebe  um identitificador de produto e um preco que substitira opreco previamente estabelecido para o produto. 
*/
void muda_preco_produto( ) { 
    int idp, preco;
    scanf(" %d:%d", &idp, &preco);
    if ( N > 0 ) {
        vetor_produto[idp].preco = preco;   
    }
    else {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    }
}

/* A funcao lista_quantidade_produto_enc recebe um identificador de encomenda e outro de produto, lista a descricao e quantidade de um produto numa encomenda. 
*/
int q;
char d[64];
void lista_quantidade_produto_enc( ) {
    int ide, idp;
    scanf(" %d:%d", &ide, &idp);
    if ( EXISTE_ENCOMENDA > 0 &&  N > 0 ){
        strcpy( d, vetor_encomenda[ide].dados[idp].descricao);
        q = vetor_encomenda[ide].dados[idp].qtd;
        printf("%s %d.", d, q);
    }
       else if ( EXISTE_ENCOMENDA < 0 && N > 0) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if ( N < 0 && EXISTE_ENCOMENDA > 0 ) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
}

/* A funcao imprime_encomendas recebe um identificador de produto e lista o identificador da encomenda em que o produto dado ocorre mais vezes.  
*/
int m,j[MAX_ENCOMENDA],e,i;
void imprime_encomendas( ) {
    int idp;
    scanf(" %d", &idp);
    if ( N > 0 ) {
        for ( i = 0; i <= contador_encomendas; i++) {
            j[i] = j[i] + 1;
            if ( m < j[i] ) {
                m = j[i];
                e = i;
                printf("Maximo produto %d %d %d.\n", idp, e, j[i]);
            }
            else if( m == j[i]) {
                compara_ids(e,i);
                printf("Maximo produto %d %d %d.\n",idp, m, j[m]);
            }
        }
        printf("Maximo produto %d %d %d.\n", idp, m, vetor_encomenda[m].dados[idp].qtd);
    }
    else if ( N < 0 ) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
}


/* A funcao lista_produtos_existentes recebe um identificador de produto, lista todos os produtos existentes no sistema por ordem crescente de pre?o. 
*/

void lista_produtos_existentes( ) {
    int idp;
    scanf(" %d", &idp);
    left = idp % 2;
    right = left + 1;
    mergesort(vetor_produto, left, right);
    for(; i < idp ; i++) { 
        printf(" %s %d %d\n", vetor_produto[i].descricao, vetor_produto[i].preco, vetor_produto[i].qtd);
    }
    printf(" %s %d %d\n", vetor_produto[i].descricao, vetor_produto[i].preco, vetor_produto[i].qtd);
}

/* A funcao lista_encomendas_alfabeticamente recebe um indentificador de encomenda, lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o.
*/

void lista_encomendas_alfabeticamente( ) {
    int ide;
    scanf(" %d", &ide);
    if ( EXISTE_ENCOMENDA > 0){
        for ( i = 0; i < ide; i++) {
            for ( b = 0; i < contador_produtos; b++){ 
                insertion( vetor_encomenda,  left, right);
                printf(" %s %d %d\n", vetor_encomenda[i].dados[b].descricao, vetor_encomenda[i].dados[b].preco, vetor_encomenda[i].dados[b].qtd);
            }
        }
        printf(" %s %d %d\n", vetor_encomenda[ide].dados[contador_produtos].descricao, vetor_encomenda[ide].dados[contador_produtos].preco, vetor_encomenda[ide].dados[contador_produtos].qtd);
    }
   else {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
}



/*============================================================================================*/
/*============================================================================================*/


int main() {
    char c;
    int trabalha = TRUE;
    inicializa_vetor();
    while (trabalha) {
        switch (c = getchar()) {

            case 'a':
                adiciona_produto(); 
                break;

            case 'q':
                adiciona_stock_produto( );
                break;
    
            case 'N':
                cria_encomenda( );
                break;    
    
            case 'A':
                adiciona_produto_encomenda( );
                break;

            case 'R':
                remove_produto_encomenda( );
                break;

            case 'r':
                remove_stock_produto( );
                break;
                
            case 'C':
                calcula_custo( );
                break;
               
            case 'p':
                muda_preco_produto( );
                break;
            
            case 'E':
                lista_quantidade_produto_enc( );
                break;

            case 'm':
                imprime_encomendas( );
                break;
            
            case 'l':   
                lista_produtos_existentes( );
                break;
            
            case 'L':
                lista_encomendas_alfabeticamente( );
                break;

            case 'x':
                trabalha = FALSE;
                break;

            default:
                break;
        }   
    } 
    return 0;
}