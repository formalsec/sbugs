#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* --------CONSTANTES------------*/

/* Maximo de caracteres numa string de descricao */
#define TAMANHO_STRING 63

/* Maximo de produtos no sistema */
#define MAX_PROD 10000

/* Maximo de encomendas no sistema */
#define MAX_ENC 500

/* Peso maximo em cada encomenda */
#define PESO_MAX 200

/* Chaves para distinguir o tipo de mergesort */
#define KEY_PRECO 1
#define KEY_DESCR 0

/*----------- ESTRUTURAS --------------*/

/* Estrutura produto */
typedef struct produto {
    char descricao[TAMANHO_STRING];
    int preco;
    int peso;
    int qtd;
} produto;

/* Estrutura encomenda */
typedef struct encomenda {
    produto produtos[MAX_PROD];
    int peso;
} encomenda;


/*----------- VARIAVEIS GLOBAIS -----------*/

/* Posicao do produto no vetor produtos */
int numero_prod = -1;

/* Posicao da encomenda no vetor das encomendas */
int numero_enc = -1;

/* Letra que determinara o comando a executar */
char comando;

/* Lista de todos os produtos */
produto lista_prod[MAX_PROD];

/* Lista de todas as encomendas */
encomenda lista_enc[MAX_ENC];

/* Lista de produtos que sera ordenada */
produto lista_ord[MAX_PROD];

/* Listas auxiliares no mergesort */
produto lista_esq[MAX_PROD/2];
produto lista_dir[MAX_PROD/2];


/*---------- FUNCOES AUXILIARES -------------*/
void merge(int esq, int m, int dir, int key);
void mergesort(int esq, int dir, int key);


/*--------- FUNCOES PRINCIPAIS ------------*/
void adiciona_produto();
void add_stock();
void cria_encomenda();
void adiciona_prod_enc();
void remove_stock();
void remove_produto_enc();
void calcula_custo_enc();
void altera_preco();
void lista_desc_qtd();
void lista_ident();
void ordena_prod_preco();
void ordena_enc_alf();


/* -------------MAIN-------------- */

/* dependendo da letra escrita, executa uma determinada instrucao 
com os valores escritos posteriormente (os comandos possiveis estao
listados em cada funcao) */
int main(){

    while ((comando = getchar()) != 'x'){
        switch (comando){
            case 'a':
                adiciona_produto();
                break;

            case 'q':
                add_stock();
                break;
            
            case 'N':
                cria_encomenda();
                break;

            case 'A':
                adiciona_prod_enc();
                break;

            case 'r':
                remove_stock();
                break;

            case 'R':
                remove_produto_enc();
                break;

            case 'C':
                calcula_custo_enc();
                break;

            case 'p':
                altera_preco();
                break;

            case 'E':
                lista_desc_qtd();
                break;

            case 'm':
                lista_ident();
                break;

            case 'l':
                ordena_prod_preco();                
                break;

            case 'L':
                ordena_enc_alf();
                break;

            default:
                break;
        }
    }

    return 0;
}

/*-- CORPO DAS FUNCOES --*/

/* Funcao que adiciona um produto ao sistema.
               -INPUT-                         -OUTPUT-
    a <nome>:<preco>:<peso>:<qtd>          Novo produto <idp>.
*/   
void adiciona_produto(){ 

    produto novo;
    scanf(" %[^:]:%d:%d:%d", novo.descricao, &novo.preco, &novo.peso, &novo.qtd);
    numero_prod++;
    lista_prod[numero_prod] = novo;

    printf("Novo produto %d.\n", numero_prod);

}


/* Funcao que adiciona stock a um produto ja existente no sistema.
           -INPUT-                 -OUTPUT-
        q <idp>:<qtd>               ------
*/
void add_stock(){

    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    if (idp > numero_prod)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    
    else 
        lista_prod[idp].qtd += qtd;
    
}


/* Funcao que cria uma encomenda nova.
           -INPUT-             -OUTPUT-
              N            Nova encomenda <ide>.
*/
void cria_encomenda(){

    numero_enc++;
    printf("Nova encomenda %d.\n", numero_enc);
}


/* Funcao que adiciona um produto a uma encomenda.
            -INPUT-                -OUTPUT-
        A <ide>:<idp>:<qtd>         ------
*/
void adiciona_prod_enc(){

    int ide, idp, qtd;
    scanf(" %d:%d:%d", &ide, &idp, &qtd);

    if (ide > numero_enc){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
        return;
    }
    
    if (idp > numero_prod){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        return;
    }
    
    if (lista_prod[idp].qtd < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
        return;
    }
    
    if (lista_enc[ide].peso + lista_prod[idp].peso * qtd > PESO_MAX){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
        return;
    }

    /* Se o produto estiver nao estiver na encomenda */
    if ( lista_enc[ide].produtos[idp].qtd == 0 ){
        strcpy(lista_enc[ide].produtos[idp].descricao,lista_prod[idp].descricao);
        lista_enc[ide].produtos[idp].preco = lista_prod[idp].preco;
        lista_enc[ide].produtos[idp].qtd = qtd;
    }
    /* Se o produto estiver na encomenda */
    else 
        lista_enc[ide].produtos[idp].qtd += qtd;
    
    /* Aumenta o peso da encomenda e diminui o stock do produto */
    lista_enc[ide].peso += lista_prod[idp].peso * qtd;
    lista_prod[idp].qtd -= qtd;
    
}


/* Funcao que remove stock de um produto do sistema.
            -INPUT-             -OUTPUT-
          r <idp>:<qtd>         -------
*/
void remove_stock(){

    int idp, qtd;

    scanf(" %d:%d", &idp, &qtd);
    if (idp > numero_prod){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
        return;
    }

    if (lista_prod[idp].qtd < qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
        return;
    }
    
    lista_prod[idp].qtd -= qtd;
    
}


/* Funcao que remove um produto de uma encomenda.
            -INPUT-                 -OUTPUT-
          R <ide>:<idp>             -------
*/
void remove_produto_enc(){

    int ide,idp;
    scanf(" %d:%d",&ide, &idp);

    if (ide > numero_enc){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    if (idp > numero_prod){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    /* Retira o peso do produto retirado, aumenta o stock desse produto no sistema */
    lista_enc[ide].peso -= lista_enc[ide].produtos[idp].qtd * lista_prod[idp].peso;
    lista_prod[idp].qtd += lista_enc[ide].produtos[idp].qtd;

    /* Retira o produto da encomenda, resetando todos os valores relevantes */
    memset(lista_enc[ide].produtos[idp].descricao,0,TAMANHO_STRING);
    lista_enc[ide].produtos[idp].preco = 0;
    lista_enc[ide].produtos[idp].qtd = 0;

}


/* Funcao que calcula o custo de uma encomenda.
           -INPUT-                       -OUTPUT-
           C <ide>                 Custo da encomenda <ide> <custo>.
*/
void calcula_custo_enc(){

    int ide,i = 0,soma = 0, max_prod = 0;
    scanf(" %d",&ide);

    if (ide > numero_enc){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }

    /* Percorrer a lista da encomenda ate ao numero de produtos do sistema ou ate a encomenda
    ter o numero maximo de produtos (200) */
    while ( i <= numero_prod && max_prod != PESO_MAX){
        if (lista_enc[ide].produtos[i].qtd != 0){
            soma += lista_enc[ide].produtos[i].qtd * lista_prod[i].preco;
            max_prod++;
        }
        i++;
    }
        
    printf("Custo da encomenda %d %d.\n",ide,soma);

}


/* Funcao que altera o preco de um produto no sistema e em todas as encomendas.
            -INPUT-                 -OUTPUT-
           p <idp>:<preco>          --------
*/
void altera_preco(){

    int idp, preco, i;
    scanf(" %d:%d",&idp,&preco);

    if (idp > numero_prod){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
        return;
    }

    /* Alterar o preco do produto no sistema */
    lista_prod[idp].preco = preco;

    /* Alterar o preco do produto em todas as encomendas */
    for ( i = 0; i <= numero_enc; i++){
        if (lista_enc[i].produtos[idp].qtd != 0)
            lista_enc[i].produtos[idp].preco = preco;
    }
    
}


/* Funcao que lista a quantidade de um produto numa encomenda.
             -INPUT-                    -OUPUT-
           E <ide>:<idp>          <nome do produto> <qtd>.
*/
void lista_desc_qtd(){

    int ide,idp;
    scanf(" %d:%d",&ide,&idp);
    if (ide > numero_enc){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    
    if (idp > numero_prod){
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
        return;
    }
    
    printf("%s %d.\n",lista_prod[idp].descricao, lista_enc[ide].produtos[idp].qtd);
    
}


/* Funcao que determina a encomenda na qual um produto aparece em maior quantidade.
           -INPUT-                  -OUTPUT-
           m <idp>         Maximo produto <idp> <ide> <qtd>.
*/
void lista_ident(){

    int i, idp;
    int max = 0, ide;
    scanf(" %d",&idp);

    if (idp > numero_prod){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
        return;
    }

    /* Percorre todas as encomendas existentes para descobrir a quantidade maxima
    do produto e em que em que encomenda essa ocorrencia se da */
    for (i=0; i <= numero_enc;i++){
        if (lista_enc[i].produtos[idp].qtd > max){
            max = lista_enc[i].produtos[idp].qtd;
            ide = i;
        }
    }

    if (max > 0)
        printf("Maximo produto %d %d %d.\n",idp,ide,max);
    
}


/* Funcao que ordena todos os produtos do sistema por preco.
            -INPUT-                          -OUTPUT-
                                  Produtos
               l                  * <nome_prod1> <preco1> <qtd em stock>.
                                  * <nome_prod2> <preco2> <qtd em stock>.
                                  * ...
*/
void ordena_prod_preco(){

    int i;

    /* Copia de todos os produtos para o vetor que sera ordenado */
    for (i = 0; i <= numero_prod; i++){
        lista_ord[i] = lista_prod[i];
    }

    /* Ordenacao dos produtos do sistema segundo o seu preco */
    mergesort(0,numero_prod, KEY_PRECO);

    puts("Produtos");
    for (i = 0; i <= numero_prod; i++){
        printf("* %s %d %d\n",lista_ord[i].descricao,lista_ord[i].preco,lista_ord[i].qtd);
    }
}


/* Funcao que ordena os produtos de uma encomenda por ordem alfabetica.
            -INPUT-                         -OUTPUT-
                                    Encomenda <ide>
            L <ide>                 * <nome_prod1> <preco1> <qtd na encomenda>.
                                    * <nome_prod2> <preco2> <qtd em encomenda>.
                                    * ...
*/
void ordena_enc_alf(){

    int ide,i, n_prod_enc_ord = 0;

    scanf(" %d",&ide);
    if (ide > numero_enc){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }
    
    /* Copia de todos os produtos de uma encomenda para o vetor que sera ordenado */
    for (i = 0; i <= numero_prod; i++){
        if (lista_enc[ide].produtos[i].qtd != 0){
            lista_ord[n_prod_enc_ord] = lista_enc[ide].produtos[i];
            n_prod_enc_ord++;
        }
        if (n_prod_enc_ord == PESO_MAX)
            break;
    }

    /* Ordenacao dos produtos da encomenda segundo a sua descricao */
    mergesort(0,n_prod_enc_ord-1, KEY_DESCR);
    
    printf("Encomenda %d\n",ide);
    for (i = 0; i < n_prod_enc_ord; i++)
        printf("* %s %d %d\n",lista_ord[i].descricao,lista_ord[i].preco,lista_ord[i].qtd);
}

/* Funcao que compara os items de duas listas e os adiciona a uma lista ordenada */
void merge(int esq, int m, int dir, int key){

    int i, j, k;
    int tam_v_esq = m - esq + 1;
    int tam_v_dir = dir - m;

    /* Divisao do vetor original em duas metades */
    for (i = 0; i < tam_v_esq; i++)
        lista_esq[i] = lista_ord[esq + i];
    
    for (j = 0; j < tam_v_dir; j++)
        lista_dir[j] = lista_ord[m + j + 1];

    /* Reiniciar as variaveis de contagem*/
    i = 0; j = 0; k = esq;


    while (i < tam_v_esq && j < tam_v_dir){
        /* Verifica se e para ordenar segundo preco ou segundo descricao */

        /* Segundo o preco: */
        if (key == KEY_PRECO){
            if (lista_esq[i].preco <= lista_dir[j].preco)
                lista_ord[k] = lista_esq[i++];

            else
                lista_ord[k] = lista_dir[j++];
        }

        /* Segundo a descricao: */
        else {
            if (strcmp(lista_esq[i].descricao,lista_dir[j].descricao) < 0)
                lista_ord[k] = lista_esq[i++];

            else
                lista_ord[k] = lista_dir[j++];
        }
        k++;
    }

    /* Copiar os restantes itens depois de uma das listas ser totalmente copiada */
    while (i < tam_v_esq){
        lista_ord[k] = lista_esq[i++];
        k++;
    }

    while (j < tam_v_dir){
        lista_ord[k] = lista_dir[j++];
        k++;
    }
}


/* Funcao do merge sort que e responsavel pela ordenacao de produtos, dividindo
    sucessivamente a lista inicial em lista unitarias e ordenando-as sucessivamente */
void mergesort(int esq, int dir, int key){
    
    if (esq < dir){

        int m = (dir+esq)/2;
        
        mergesort(esq, m, key);
        mergesort(m+1, dir, key);

        merge(esq, m, dir, key);
    }
}