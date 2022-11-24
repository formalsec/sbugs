#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
/* O numero maximo de caracteres para a descricao de um produto.  */
#define MAX 63
#define MAX2 10000
/* O numero maximo de produtos em stock. */
#define MAXS 10000
/* O numero maximo de encomendas. */
#define MAXE 500

#define DUZENTOS 200

/* Numero de produtos existentes. */
int idp = 0;
/* Numero de encomendas existentes. */
int ide = 0;


/* Estrutura que define o stock. */
typedef struct Stock{
    char desc[MAX];
    int preco, peso, qtd;
}Stock;

Stock stock[MAXS];

/* Estrutura que define as encomendas. */
typedef struct Encomenda{
    int preco, peso;
    int produtos[MAXS];
    int idps[MAXS];
}Encomenda;

Encomenda encomenda[MAXE];



/* funcao que cria um vetor auxiliar, ordena os precos dos produtos. */
void merge_l(int p[], int l, int m, int r){
    int i, j, k,aux[MAXS];
    for(i = m+1; i > l; i--)
        aux[i-1] = p[i-1];
    for(j = m; j < r; j++)
        aux[r+m-j] = p[j+1];
    for(k = l; k <= r; k++){
        if(stock[aux[i]].preco > stock[aux[j]].preco || (stock[aux[i]].preco == stock[aux[j]].preco && aux[i] > aux[j]))
            p[k] = aux[j--];
        else
            p[k] = aux[i++];
    }
}

/* funcao que divide, recursivamente, um vetor com todos os idps. */
void mergesort_l(int p[],int l, int r){
    int m = (r+l)/2;
    if (r <= l)
        return;
    mergesort_l(p, l, m);
    mergesort_l(p, m+1, r);
    merge_l(p, l, m, r);
}

/* funcao que compara duas arrays de caracteres por ordem alfabetica. */
int ordena_desc(char a[], char b[]){
    int i;
    for (i = 0; i < MAX; i++) {
        if (a[i] > b[i])
            return 1;
        else if (a[i] < b[i])
            return 0;
    }
    return 0;
}

/* funcao que cria um vetor auxiliar, e ordena os produtos
   por ordem alfabetica. */
void merge_L(int p[], int l, int m, int r){
    int i, j, k,aux[MAXS];
    for(i = m+1; i > l; i--)
        aux[i-1] = p[i-1];
    for(j = m; j < r; j++)
        aux[r+m-j] = p[j+1];
    for(k = l; k <= r; k++)
        if(ordena_desc(stock[aux[i]].desc,stock[aux[j]].desc))
            p[k] = aux[j--];
        else
            p[k] = aux[i++];
}

/* funcao que divide, recursivamente, um vetor com os idps
   de uma encomenda. */
void mergesort_L(int p[],int l, int r){
    int m = (r+l)/2;
    if (r <= l) 
        return;
    mergesort_L(p, l, m);
    mergesort_L(p, m+1, r);
    merge_L(p, l, m, r);
}

/* funcao do comanda a, que recebe uma descricao, um preco,
um peso, e a quantida em stock de um produto e apresenta ao utilizador
o id do produto. */
void comando_a(){
    char s,desc[MAX];
    int i,preco = 0,peso = 0,qtd = 0;
    for (i = 0; i < MAX; i++){  /* ciclo que constroi uma array com caracteres */
        s = getchar();          /* da descricao do produtos */
        if (s != ' ') {
            if (s == ':')
                break;
            else {
                desc[i - 1] = s;
                desc[i] = '\0';
            }
        }
    }
    for(i = 0; i < MAXS; i++){   /*ciclo que controi um numero inteiro*/
        s = getchar();           /*que representa o preco do produto*/
        if (s == ':')
            break;
        else{
            s = s - '0';
            preco = (preco*10) + s;
        }
    }
    for(i = 0; i < MAXS; i++){   /*ciclo que constroi um numero inteiro*/
        s = getchar();           /*que representa o peso do produto*/
        if (s == ':')
            break;
        else{
            s = s - '0';
            peso = (peso*10) + s;
        }
    }
    for(i = 0; i < MAXS; i++){   /*ciclo que constroi um numero inteiro*/
        s = getchar();           /*que representa a quantidade em stock do produto*/
        if (s == '\n')
            break;
        else{
            s = s - '0';
            qtd = (qtd*10) + s;
        }
    }
    for(i = 0; i < MAX; i++){               /* ciclo que gaurda a descricao */
        if (desc[i] == '\0')                /* na estrutura do produto. */
            break;
        else{
            stock[idp].desc[i] = desc[i];
            stock[idp].desc[i + 1] = '\0';
        }
    }
    stock[idp].preco = preco;  /* guarda o preco na estrutura. */
    stock[idp].peso = peso;    /* guarda o peso na estrutura. */
    stock[idp].qtd = qtd;      /* guarda a quantidade na estrutura. */

    printf("Novo produto %d.\n", idp);
    idp++;
}

/* funcao do comando q, que adiciona stock a um produto. */
void comando_q(){
    int indice, qtd;
    scanf(" %d:%d",&indice, &qtd);
    if (idp - 1 < indice)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", indice);
    else
        stock[indice].qtd = stock[indice].qtd + qtd;
}

/* funcao do comando N, que cria um produto
   e a sua respetiva estrutura. */
void comando_N(){
    int i;
    printf("Nova encomenda %d.\n", ide);
    encomenda[ide].preco = 0;           /*inicia o preco da encomenda <ide> a zero.*/
    encomenda[ide].peso = 0;            /*inicia o peso da encomenda <ide> a zero.*/
    encomenda[ide].produtos[MAXS] = 0;  /*inicia a quantidade dos produtos na encomenda <ide> a zero.*/
    for (i = 0; i < MAXS; i++)          /*ciclo que inicia todos os produtos a -1 na */
        encomenda[ide].idps[i] = -1;    /*encomenda <ide> para depois saber quais sao os produtos existentes na encomenda.*/
    ide++;
}

/* funcao do comando A, que adiciona uma quantidade
   de um produto em stock a uma encomenda. */
void comando_A(){
    int indice_e, indice_p, qtd;
    scanf(" %d:%d:%d",&indice_e, &indice_p, &qtd);
    if(ide - 1 < indice_e)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", indice_p, indice_e);
    else if(idp - 1 < indice_p)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", indice_p, indice_e);
    else if(qtd > stock[indice_p].qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", indice_p, indice_e);
    else if((qtd*stock[indice_p].peso) + encomenda[indice_e].peso > 200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", indice_p, indice_e);
    else{
        encomenda[indice_e].peso = encomenda[indice_e].peso + (qtd*stock[indice_p].peso);       /*Adiciona peso a encomenda.*/
        encomenda[indice_e].preco = encomenda[indice_e].preco + (qtd*stock[indice_p].preco);    /*Atualiza o preco da encomenda*/
        stock[indice_p].qtd = stock[indice_p].qtd - qtd;                                        /*Retira quantidade ao stock*/
        encomenda[indice_e].produtos[indice_p] = encomenda[indice_e].produtos[indice_p] + qtd;  /*Adiciona quantidade a encomenda*/
        encomenda[indice_e].idps[indice_p] = indice_p;                                          /*Introduz o numero do produto a encomenda*/
    }
}
/* funcao do comando r, que remove uma quantidade
   a um produto do stock. */
void comando_r(){
    int indice_p, qtd;
    scanf(" %d:%d",&indice_p,&qtd);
    if (idp - 1 < indice_p)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", indice_p);
    else if(stock[indice_p].qtd - qtd < 0)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, indice_p);
    else{
        stock[indice_p].qtd = stock[indice_p].qtd - qtd;

    }
}

/* funcao do comando R, que remove um produto da encomenda. */
void comando_R(){
    int indice_e, indice_p;
    scanf(" %d:%d",&indice_e,&indice_p);
    if (ide - 1 < indice_e)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", indice_p, indice_e);
    else if (idp - 1< indice_p)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", indice_p, indice_e);
    else{
        encomenda[indice_e].peso = encomenda[indice_e].peso - (encomenda[indice_e].produtos[indice_p]*stock[indice_p].peso);     /*Retira peso a encomenda.*/
        encomenda[indice_e].preco = encomenda[indice_e].preco - (encomenda[indice_e].produtos[indice_p]*stock[indice_p].preco);  /*Atualiza o preco da encomenda.*/
        stock[indice_p].qtd = stock[indice_p].qtd + encomenda[indice_e].produtos[indice_p];                                      /*Repoe stock a encomenda.*/
        encomenda[indice_e].produtos[indice_p] = 0;                                                                              /*Remete a qunatidade do produto na encomenda a zero*/
        encomenda[indice_e].idps[indice_p] = -1;                                                                                 /*Volta a meter a indicador de produto na encomenda a menos um.*/
    }


}
/* funcao do comando C, que apresenta ao utilizador
   o preco de uma encomenda. */
void comando_C(){
    int indice_e;
    scanf(" %d",&indice_e);
    if (ide - 1 < indice_e)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", indice_e);
    else
        printf("Custo da encomenda %d %d.\n", indice_e, encomenda[indice_e].preco);


}

/* funcao do comando p, que altera o preco de um produto. */
void comando_p(){
    int i, indice_p, preco;
    scanf(" %d:%d",&indice_p,&preco);
    if (idp - 1 < indice_p)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", indice_p);
    else{
        for(i = 0; i < ide; i++){
            /*Atualiza o preco das encomendas com o produto de preco alterado*/
            encomenda[i].preco = encomenda[i].preco - (encomenda[i].produtos[indice_p]*stock[indice_p].preco) + (encomenda[i].produtos[indice_p]*preco);
        }
        stock[indice_p].preco = preco;
    }
}

/* Funcao do comando E, que lista a descricao e a
   qunatidade de um produto numa encomenda. */
void comando_E(){
    int i, indice_e, indice_p;
    scanf(" %d:%d",&indice_e,&indice_p);
    if (ide - 1 < indice_e)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", indice_e);
    else if (idp - 1 < indice_p)
        printf("Impossivel listar produto %d. Produto inexistente.\n", indice_p);
    else{
        for(i = 0; i < MAX;i++)
            if(stock[indice_p].desc[i] == '\0')
                break;
            else
                printf("%c", stock[indice_p].desc[i]);
        printf(" %d.\n",encomenda[indice_e].produtos[indice_p]);
    }
}

/* funcao do comando m, que lista o identificador da encomenda
   em que um produto ocorre mais vezes, e a sua qunatidade. */
void comando_m(){
    int i,e,maiorqtd, indice_p;
    scanf(" %d",&indice_p);    
    if(idp - 1 < indice_p)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", indice_p);
    else {
        maiorqtd = 0;
        /*Ciclo que descobre a encomenda com a maior quantidade do produto <indice_p> e essa quantidade.*/ 
        for (i = 0; i < ide; i++) {
            if (encomenda[i].produtos[indice_p] > maiorqtd){          
                maiorqtd = encomenda[i].produtos[indice_p];
                e = i;
            }
        }
        if (maiorqtd > 0)
            printf("Maximo produto %d %d %d.\n", indice_p, e, encomenda[e].produtos[indice_p]);
    }
}

/* Funcao do comando l, que lista os produtos por ordem
   crescente dos precos e apresenta a sua descricao, preco
   e quantidade em stock. */
void comando_l(){
    int i, a[MAXS], l = 0;
    for (i = 0; i < idp; i++)
        a[i] = i;
    mergesort_l(a,l,(idp-1));
    printf("Produtos\n");
    for (i = 0; i < idp;i++){
        printf("* %s %d %d\n", stock[a[i]].desc, stock[a[i]].preco, stock[a[i]].qtd);
    }
}

/* Funcao do comando L, que lista os produtos de uma
   encomenda por ordem alfabetica, apresentando
   a descricao, o preco e a quantidade na encomenda. */
void comando_L(){
    int i, indice_e = 0, produtos[DUZENTOS],q,l = 0;
    scanf(" %d",&indice_e);
    if (indice_e > ide - 1)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", indice_e);
    else{
        q = 0;
        /*Ciclo que forma o vetor com os idps dos produtos presentes na encomenda, para depois ordenar.*/
        for(i = 0;i < MAXS; i++) {
            if (encomenda[indice_e].idps[i] != -1) {
                produtos[q++] = encomenda[indice_e].idps[i];
            }
        }
        mergesort_L(produtos,l,(q-1));
        printf("Encomenda %d\n", indice_e);
        for(i=0; i < q; i++)
            printf("* %s %d %d\n", stock[produtos[i]].desc, stock[produtos[i]].preco, encomenda[indice_e].produtos[produtos[i]]);
    }
}

/* Funcao auxiliar que le o comando escolhido
   e redireciona para a funcao correspondente. */
void lercomando(char c){
    switch(c) {
        case 'a' :
            comando_a();
            break;
        case 'q' :
            comando_q();
            break;
        case 'N' :
            comando_N();
            break;
        case 'A' :
            comando_A();
            break;
        case 'r' :
            comando_r();
            break;
        case 'R' :
            comando_R();
            break;
        case 'C' :
            comando_C();
            break;
        case 'p' :
            comando_p();
            break;
        case 'E' :
            comando_E();
            break;
        case 'm' :
            comando_m();
            break;
        case 'l' :
            comando_l();
            break;
        case 'L' :
            comando_L();
            break;
    }
}
/* Le a letra do comando. */
int main(){
    char c;
    c = getchar();
    while (c != 'x'){
        lercomando(c);
        c = getchar();
    }
    return 0;
}