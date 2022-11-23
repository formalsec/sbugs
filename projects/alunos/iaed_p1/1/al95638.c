#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*-- CONSTANTES --*/

#define TAMANHO_STRING 63
#define MAX_PROD 10000
#define METADE_MAX_PROD 5000
#define MAX_ENC 500
#define PESO_MAX 200
#define KEY_PRECO 1
#define KEY_DESCR 0

/*-- ESTRUTURAS --*/

typedef struct produto{
    char descricao[TAMANHO_STRING];
    int preco, peso, qtd;
}produto;

typedef struct encomenda{
    produto produtos[MAX_PROD];
    int peso;
}encomenda;

/*-- VARIAVEIS GLOBAIS --*/

int numero_prod = -1;
int numero_enc = -1;
char comando;
produto lista_prod[MAX_PROD];
encomenda lista_enc[MAX_ENC];
/* produto lista_ord[MAX_PROD];
produto lista_esq[METADE_MAX_PROD];
produto lista_dir[METADE_MAX_PROD];
*/

/* Criacao de duas listas auxiliares */
produto lista_esq[METADE_MAX_PROD];
produto lista_dir[METADE_MAX_PROD];
produto lista_ord[MAX_PROD];

/*-- FUNCOES AUXILIARES --*/
void merge(produto lista_ord[],int esq, int m, int dir, int key);
void mergesort( produto lista_ord[],int esq, int dir, int key);

/*-- FUNCOES PRINCIPAIS --*/

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


int main(){
    scanf("%s",&comando);

    while (comando != 'x'){
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
        }
        scanf("%s",&comando);
    }

    return 0;
}




/*-- CORPO DAS FUNCOES --*/

void adiciona_produto(){
    produto novo;
    scanf(" %[^:]:%d:%d:%d", novo.descricao, &novo.preco, &novo.peso, &novo.qtd);
    numero_prod++;
    lista_prod[numero_prod] = novo;
    printf("Novo produto %d.\n", numero_prod);

}

void add_stock(){
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    if (idp > numero_prod)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);

    else
        lista_prod[idp].qtd += qtd;

}

void cria_encomenda(){
    numero_enc++;
    printf("Nova encomenda %d.\n", numero_enc);
}

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

    strcpy(lista_enc[ide].produtos[idp].descricao,lista_prod[idp].descricao);
    lista_enc[ide].produtos[idp].preco = lista_prod[idp].preco;
    lista_enc[ide].produtos[idp].qtd += qtd;

    lista_enc[ide].peso += lista_prod[idp].peso * qtd;
    lista_prod[idp].qtd -= qtd;

}

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

    lista_enc[ide].peso -= lista_enc[ide].produtos[idp].qtd * lista_prod[idp].peso;
    lista_prod[idp].qtd += lista_enc[ide].produtos[idp].qtd;
    lista_enc[ide].produtos[idp].qtd = 0;

}

void calcula_custo_enc(){
    int ide,i = 0,soma = 0, max_prod = 0;
    scanf(" %d",&ide);
    if (ide > numero_enc){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }
    while ( i <= numero_prod && max_prod != PESO_MAX){
        if (lista_enc[ide].produtos[i].qtd != 0){
            soma += lista_enc[ide].produtos[i].qtd * lista_prod[i].preco;
            max_prod++;
        }
        i++;
    }

    printf("Custo da encomenda %d %d.\n",ide,soma);

}

void altera_preco(){
    int idp, preco, i;
    scanf(" %d:%d",&idp,&preco);
    if (idp > numero_prod){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
        return;
    }
    lista_prod[idp].preco = preco;
    for ( i = 0; i <= numero_enc; i++){
        /* if (lista_enc[i].produtos[idp].preco != 0){ */
        lista_enc[i].produtos[idp].preco = preco;
    }

}

void lista_desc_qtd(){
    int ide,idp;
    scanf(" %d:%d",&ide,&idp);
    if (ide > numero_enc){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    else if (idp > numero_prod){
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
        return;
    }

    printf("%s %d.\n",lista_prod[idp].descricao, lista_enc[ide].produtos[idp].qtd);

}

void lista_ident(){
    int i, idp;
    int max = 0, ide;
    scanf(" %d",&idp);
    if (idp > numero_prod){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
        return;
    }

    for (i=0; i <= numero_enc;i++){
        if (lista_enc[i].produtos[idp].qtd > max){
            max = lista_enc[i].produtos[idp].qtd;
            ide = i;
        }
    }

    if (max != 0)
        printf("Maximo produto %d %d %d.\n",idp,ide,max);

}

void ordena_prod_preco(){

    int i;

    for (i = 0; i <= numero_prod; i++){
        lista_ord[i] = lista_prod[i];
    }
    mergesort(lista_ord,0,numero_prod, KEY_PRECO);

    puts("Produtos");
    for (i = 0; i <= numero_prod; i++){
        printf("* %s %d %d\n",lista_ord[i].descricao,lista_ord[i].preco,lista_ord[i].qtd);
    }
}

void ordena_enc_alf(){

    int ide,i, n_prod_enc_ord = 0;

    scanf(" %d",&ide);
    if (ide > numero_enc){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }

    for (i = 0; i <= numero_prod; i++){
        if (lista_enc[ide].produtos[i].qtd != 0){
            lista_ord[n_prod_enc_ord] = lista_enc[ide].produtos[i];
            n_prod_enc_ord++;
        }
        if (n_prod_enc_ord == PESO_MAX)
            break;
    }

    mergesort(lista_ord,0,n_prod_enc_ord-1, KEY_DESCR);

    printf("Encomenda %d\n",ide);
    for (i = 0; i < n_prod_enc_ord; i++)
        printf("* %s %d %d\n",lista_ord[i].descricao,lista_ord[i].preco,lista_ord[i].qtd);
}

void merge(produto lista_ord[],int esq, int m, int dir, int key){

    int i, j, k;
    int tam_v_esq = m - esq + 1;
    int tam_v_dir = dir - m;



    for (i = 0; i < tam_v_esq; i++)
        lista_esq[i] = lista_ord[esq + i];

    for (j = 0; j < tam_v_dir; j++)
        lista_dir[j] = lista_ord[m + j + 1];

    /* Reiniciar as variaveis de contagem*/
    i = 0; j = 0; k = esq;

    while (i < tam_v_esq && j < tam_v_dir){
        if (key == KEY_PRECO){
            if (lista_esq[i].preco <= lista_dir[j].preco)
                lista_ord[k] = lista_esq[i++];
            else
                lista_ord[k] = lista_dir[j++];
        }
        else {
            if (strcmp(lista_esq[i].descricao,lista_dir[j].descricao) < 0)
                lista_ord[k] = lista_esq[i++];
            else
                lista_ord[k] = lista_dir[j++];
        }
        k++;
    }

    while (i < tam_v_esq){
        lista_ord[k] = lista_esq[i++];
        k++;
    }

    while (j < tam_v_dir){
        lista_ord[k] = lista_dir[j++];
        k++;
    }
}

void mergesort(produto lista_ord[],int esq, int dir, int key){

    if (esq < dir){

        int m = (dir+esq)/2;

        mergesort(lista_ord,esq, m, key);
        mergesort(lista_ord,m+1, dir, key);

        merge(lista_ord,esq, m, dir, key);
    }
}
