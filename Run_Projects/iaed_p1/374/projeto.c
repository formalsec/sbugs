#include <stdio.h>
#include <string.h>
#define LimS 10000
#define LimE 500
#define LimD 63
#define pesoMax 200



int qtd, prec, idpX, ideX, idp = 0, ide = 0;
char chr;

/* Estrutura que trata de armazenar os produtos e todas as suas caracteristicas */
typedef struct produtos{
    int preco, peso, stock;
    char desc[LimD];
}produtos;
produtos prods[LimS];

/* Estrutura que trata de armazenar as encomendas e os seus produtos */
typedef struct encomendas{
    int qnt;
}encomendas;
encomendas encs[LimE][LimS];
int pesos[LimE]; /* array que guarda o peso de cada encomenda*/

/* a - Funcao que adiciona novos produtos ao sistema */
void func_a(){
    scanf(" %[^:]:%d:%d:%d", prods[idp].desc, &prods[idp].preco, &prods[idp].peso, &prods[idp].stock);
    printf("Novo produto %d.\n", idp++);
}

/* q - Funcao que adiciona stock a um produto existente no sistema */
void func_q(){
    scanf(" %d:%d", &idpX, &qtd);
    if(idpX >= idp){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idpX);
    }
    else{
        prods[idpX].stock = (prods[idpX].stock + qtd);
    }
}

/* N - Funcao que cria uma nova encomenda */
void func_N(){
    for(idpX = 0; idpX < LimS; idpX++){
        encs[ide][idpX].qnt = 0;
    }
    pesos[ide] = 0;
    printf("Nova encomenda %d.\n", ide++);
}

/* A - Funcao que adiciona um produto a uma encomenda */
void func_A(){
    scanf(" %d:%d:%d", &ideX, &idpX, &qtd);
    if(ideX >= ide){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idpX, ideX);
    }
    else if(idpX >= idp){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idpX, ideX);
    }
    else if(qtd > prods[idpX].stock){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idpX, ideX);
    }
    else if(pesoMax < pesos[ideX] + (prods[idpX].peso * qtd)){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idpX, ideX);
    }
    else{
        encs[ideX][idpX].qnt = encs[ideX][idpX].qnt + qtd;
        pesos[ideX] += qtd * prods[idpX].peso;
        prods[idpX].stock = prods[idpX].stock - qtd;
    }
}

/* r - Funcao que remove stock a um produto existente */
void func_r(){
    scanf(" %d:%d", &idpX, &qtd);
    if(idpX>=idp){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idpX);
    }
    else if(prods[idpX].stock < qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idpX);
    }
    else{
        prods[idpX].stock = prods[idpX].stock - qtd;
    }
}

/* R - Funcao que remove um produto de uma encomenda */
void func_R(){
    scanf(" %d:%d", &ideX, &idpX);
    if(ideX >= ide){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idpX, ideX);
    }
    else if(idpX >= idp){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idpX, ideX);
    }
    else{
        prods[idpX].stock += encs[ideX][idpX].qnt;
        pesos[ideX] -= encs[ideX][idpX].qnt * prods[idpX].peso;
        encs[ideX][idpX].qnt = 0;
    }
}

/* C - Funcao que calcula o custo de uma encomenda */
void func_C(){
    int prodX, precoATM = 0;
    scanf(" %d", &ideX);
    if(ideX >= ide){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ideX);
    }
    else{
        for(prodX = 0; prodX < LimS; prodX++){
            precoATM = (precoATM + (encs[ideX][prodX].qnt * prods[prodX].preco));
        }
        printf("Custo da encomenda %d %d.\n", ideX, precoATM);
    }
}

/* p - Funcao que altera o pre?o de um produto existente no sistema */
void func_p(){
    scanf(" %d:%d", &idpX, &prec);
    if(idpX>=idp){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idpX);
    }
    else{
        prods[idpX].preco = prec;
    }
}

/* E - Funcao que retorna a descri??o e a quantidade de um produto numa dada encomenda */
void func_E(){
    scanf(" %d:%d", &ideX, &idpX);
    if(ideX >= ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ideX);
    }
    else if(idpX >= idp){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idpX);
    }
    else{
        printf("%s %d.\n", prods[idpX].desc, encs[ideX][idpX].qnt);
    }
}

/* m - Funcao que retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
void func_m(){
    int ideC, MAX = 0, ideM;
    scanf(" %d", &idpX);
    if(idpX >= idp){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idpX);
    }
    else{
        if(ide != 0){
            for(ideC = 0; ideC < ide; ideC++){
                if(encs[ideC][idpX].qnt > MAX){
                    MAX = encs[ideC][idpX].qnt;
                    ideM = ideC;
                }
            }
            if(MAX != 0){
                printf("Maximo produto %d %d %d.\n", idpX, ideM, encs[ideM][idpX].qnt);
            }
        }
    }
}

/* Funcao less, que faz parte da organizacao pedida no comando L, comparando os precos e organizando por ordem crescente */
int less_l(int y, int z){
    if (prods[y].preco < prods[z].preco){
        return 1;
    }
    else if (prods[y].preco == prods[z].preco){
        if (y<z){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

/* Funcao merge, que faz parte da organizacao pedida no comando l */
void merge_l(int a[], int l, int m, int r){
    int i, j, k;
    int aux[LimS];
    for (i = m+1; i > l; i--){
        aux[i-1] = a[i-1];
    }
    for(j = m; j < r; j++){
        aux[r+m-j] = a[j+1];
    }
    for(k = l; k <= r; k++){
        if(less_l(aux[j], aux[i])){
            a[k] = aux[j--];
        }
        else{
            a[k] = aux [i++];
        }
    }
}

/* Funcao mergesort, que faz parte da organizacao pedida no comando l */
void mergesort_l(int a[], int l, int r){
    int m = (r+l)/2;
    if(r <= l) return;
    mergesort_l(a, l, m);
    mergesort_l(a, m+1, r);
    merge_l(a, l, m, r);
}

/* l - Funcao que lista todos os produtos existentes no sistema por ordem crescente de pre?o */
void func_l(){
    int listaP[LimS], idprod, k;
    for(idpX = 0; idpX < idp; idpX++){
        listaP[idpX] = idpX;
    }
    mergesort_l(listaP, 0, (idp-1));
    printf("Produtos\n");
    for(k = 0; k < idp; k++){
        idprod = listaP[k];
        printf("* %s %d %d\n", prods[idprod].desc, prods[idprod].preco, prods[idprod].stock);
    }
}

/* Funcao less, que faz parte da organizacao pedida no comando L, comparando as letras de forma a organizar por ordem alfabetica */
int less_L(char y[], char z[]){
    int k;
    for(k = 0; k < LimD; k++){
        if (y[k] > z[k]){
            return 1;
        }
        else if (y[k] < z[k]){
            return 0;
        }
    }
    return 0;
}

/* Funcao merge, que faz parte da organizacao pedida no comando L */
void merge_L(int a[], int l, int m, int r){
    int i, j, k;
    int aux[LimS];
    for (i = m+1; i > l; i--){
        aux[i-1] = a[i-1];
    }
    for(j = m; j < r; j++){
        aux[r+m-j] = a[j+1];
    }
    for(k = l; k <= r; k++){
        if(less_L(prods[aux[i]].desc, prods[aux[j]].desc)){
            a[k] = aux[j--];
        }
        else{
            a[k] = aux [i++];
        }
    }
}

/* Funcao mergesort, que faz parte da organizacao pedida no comando L*/
void mergesort_L(int a[], int l, int r){
    int m = (r+l)/2;
    if(r <= l) return;
    mergesort_L(a, l, m);
    mergesort_L(a, m+1, r);
    merge_L(a, l, m, r);
}

/* L - Funcao que lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void func_L(){
    int listaP[LimS], idprod, k = 0, c = 0;
    scanf(" %d", &ideX);
    if (ideX >= ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ideX);
    }
    else{
        for(idprod = 0; idprod < LimS; idprod++){
            if (encs[ideX][idprod].qnt != 0){
                listaP[k++] = idprod;
            }
        }
        mergesort_L(listaP, 0, (k-1));
        printf("Encomenda %d\n", ideX);
        for(idprod = 0; idprod < k; idprod++){
            c = listaP[idprod];
            if (encs[ideX][c].qnt != 0){
                printf("* %s %d %d\n", prods[c].desc, prods[c].preco, encs[ideX][c].qnt);
            }
        }
    }
}

/* Funcao que trata de identificar que comando foi chamado e redireciona o programa para a funcao certa */
void lista_comandos(){
    char c;
    c = chr;
    switch(c){
        case 'a':
            func_a();
            break;
        case 'q':
            func_q();
            break;
        case 'N':
            func_N();
            break;
        case 'A':
            func_A();
            break;
        case 'r':
            func_r();
            break;
        case 'R':
            func_R();
            break;
        case 'C':
            func_C();
            break;
        case 'p':
            func_p();
            break;
        case 'E':
            func_E();
            break;
        case 'm':
            func_m();
            break;
        case 'l':
            func_l();
            break;
        case 'L':
            func_L();
            break;
    }
}

/* Funcao main que inicialmente recebe um caracter que posteriormente sera atualizado cada vez que for
introduzido um novo comando no input */
int main(){
    char c, x;
    chr = getchar();
    c = chr;
    x = 'x';
    while(c != x) {
        c = chr;
        lista_comandos();
        chr = getchar();
    }
    return 0;
}