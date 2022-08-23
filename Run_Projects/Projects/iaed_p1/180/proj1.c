#include <stdio.h>

#include <string.h>

#include <stdlib.h>

/*tamanho maximo das descricoes*/
#define DIM 63

/*numero maximo de produtos*/
#define NUM1 10000

/*numero maximo de encomendas*/
#define NUM2 500

/*identificador da encomenda e do produto respetivamente*/
int ide = 0, idp = 0; 

/*estrutura do produto*/
typedef struct {

    int preco, peso, qtd;

    char descricao[DIM];

}Produto;

Produto produto[NUM1];

/*estrutura da encomenda*/
typedef struct {
    
    Produto prod[NUM1];
    int peso_total, preco_total, n_menor, n_maior, n_prod;

}Encomenda;

Encomenda encomenda[NUM2];

/*funcao que adiciona um produto ao stock*/
void adiciona_produto(){

    scanf("%[^:]:%d:%d:%d", produto[idp].descricao, &produto[idp].preco, &produto[idp].peso, &produto[idp].qtd);
    printf("Novo produto %d.\n", idp);
    ++idp;
}

/*funcao que adiciona a um produto existente no stock uma determinada quantidade*/
void adiciona_stock(){

    int num1, qtd;

    scanf("%d:%d", &num1, &qtd);
    if (num1 >= idp){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", num1);
    }
    else {
        produto[num1].qtd = produto[num1].qtd + qtd;
    }
}

/*funcao que cria uma encomenda*/
void cria_encomenda(){

    printf("Nova encomenda %d.\n", ide);
    ++ide;
    encomenda[ide].n_menor = 9999;
    encomenda[ide].n_maior = 0;
    encomenda[ide].n_prod = 0;
}

/*funcao que adiciona uma determinada quantidade de um produto selecionado a uma encomenda selecionada */
void adiciona_encomenda(){ 

    int num1, num2, qtd;

    scanf("%d:%d:%d", &num2, &num1, &qtd);
    if (num2 >= ide){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", num1, num2);
    }
    else if (num1 >= idp){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", num1, num2);
    }
    else if (qtd > produto[num1].qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", num1, num2);
    }
    else if (encomenda[num2].peso_total + (produto[num1].peso * qtd) > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", num1, num2);
    }
    else {
        (encomenda[num2].prod[num1]).qtd = (encomenda[num2].prod[num1]).qtd + qtd;
        produto[num1].qtd = produto[num1].qtd - qtd; 
        encomenda[num2].peso_total = (produto[num1].peso) * qtd + encomenda[num2].peso_total;
        if (num1 > encomenda[num2].n_maior){
            encomenda[num2].n_maior = num1;
        }
        if (num1 < encomenda[num2].n_menor){
            encomenda[num2].n_menor = num1;
        }
    }
}

/*funcao que remove uma quantidade selecionada a um produto do stock*/
void remove_stock(){

    int num1, qtd;

    scanf("%d:%d", &num1, &qtd);
    if (num1 >= idp){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", num1);
    }
    else if (qtd > produto[num1].qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, num1);
    }
    else {
        produto[num1].qtd = produto[num1].qtd - qtd;
    }
}

/*funcao que remove um produto selecionado de uma encomenda selecionada*/
void remove_produto(){

    int num1, num2;

    scanf("%d:%d", &num2, &num1);
    if (num2 >= ide){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", num1, num2);
    }
    else if (num1 >= idp){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", num1, num2);
    }
    else {
        produto[num1].qtd = produto[num1].qtd + (encomenda[num2].prod[num1]).qtd; 
        encomenda[num2].peso_total = encomenda[num2].peso_total - (encomenda[num2].prod[num1]).qtd * produto[num1].peso;
        (encomenda[num2].prod[num1]).qtd = 0;
    }
}

/*funcao que calcula o custo de uma encomenda escolhida*/
void calcula_custo(){

    int i, num2;

    scanf("%d", &num2);
    if (num2 >= ide){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", num2);
    }
    else {
        encomenda[num2].preco_total = 0;
        for (i = 0; i < idp; i++){
            encomenda[num2].preco_total = encomenda[num2].preco_total + (produto[i].preco * (encomenda[num2].prod[i]).qtd);
        }
        printf("Custo da encomenda %d %d.\n", num2, encomenda[num2].preco_total);
    }
}

/*funcao que altera o preco de um produto escolhido*/
void altera_preco(){

    int i, num1, preco;

    scanf("%d:%d", &num1, &preco);
    if (num1 >= idp){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", num1);
    }
    else {
        produto[num1].preco = preco;
        for (i = 0; i < ide; i++){
            (encomenda[i].prod[num1]).preco = preco;
        }
    }
}

/*funcao que devolve a descricao e a quantidade do produto na encomenda selecionada*/
void lista(){

    int num1, num2;

    scanf("%d:%d", &num2, &num1);
    if (num2 >= ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", num2);
    }
    else if (num1 >= idp){
        printf("Impossivel listar produto %d. Produto inexistente.\n", num1);
    }
    else {
        printf("%s %d.\n", produto[num1].descricao, (encomenda[num2].prod[num1]).qtd);
    }
}

/*funcao que devolve o numero da encomenda que tem maior quantidade do produto selecionado*/
void lista_identificador(){

    int i, num1, num_encomenda, maior_qtd = 0;

    scanf("%d", &num1);
    if (num1 >= idp){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", num1);
    }
    else {
        for (i = 0; i < ide; i++){
            if ((encomenda[i].prod[num1]).qtd > maior_qtd){
                maior_qtd = (encomenda[i].prod[num1]).qtd;
                num_encomenda = i;
            }  
        }
        if (ide != 0 && maior_qtd != 0){
            printf("Maximo produto %d %d %d.\n", num1, num_encomenda, maior_qtd);
        }
    }
}

/*algoritmo de ordenacao*/
void merge(int a[NUM1], int left, int m, int right){ 

    int i, j, k, aux[NUM1];
    for (i = m+1; i > left; i--) 
        aux[i-1] = a[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    for (k = left; k <= right; k++)
        if ((produto[aux[j]].preco < produto[aux[i]].preco) || i > m)
            a[k] = aux[j--];
    else
        a[k] = aux[i++];
}

/*algoritmo de ordenacao*/
void mergesort(int a[NUM1], int left, int right){

    int m = (right+left)/2;
    if (right <= left){
        return;
    }
    mergesort(a, left, m);
    mergesort(a, m+1, right);
    merge(a, left, m, right);
}

/*funcao que devolve uma lista de todos os produtos do stock por ordem crescente de peso e idp*/
void lista_stock(){

    int i, a[NUM1];

    for (i = 0; i < idp ; i++){
        a[i] = i;
    }
    mergesort(a, 0, idp - 1);
    printf("Produtos\n");
    for (i = 0; i < idp ; i++){
        printf("* %s %d %d\n", produto[a[i]].descricao, produto[a[i]].preco, produto[a[i]].qtd);
    } 
}

/*algoritmo de ordenacao*/
void SelectionSort(int a[NUM1], int left, int right){

    int i, j;

    for (i = left; i < right; i++){
        int aux, min = i;
        for (j = i + 1; j <= right; j++){
            if (strcmp(produto[a[j]].descricao, produto[a[min]].descricao) < 0){
                min = j;   
            }   
        }
        aux = a[i]; a[i] = a[min]; a[min] = aux;
    }  
}

/*funcao que lista todos os produtos da encomenda selecionada por ordem alfabetica*/
void lista_encomenda(){

    int i, num2, a[NUM1], n = 0;

    scanf("%d", &num2);
    if (num2 >= ide){   
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", num2);
    }
    else{
        for (i = encomenda[num2].n_menor; i <= encomenda[num2].n_maior ; i++){
            if ((encomenda[num2].prod[i]).qtd != 0){
                a[n] = i;
                ++n;
            }
        }
        SelectionSort(a, 0, n - 1);
        printf("Encomenda %d\n", num2);
        for (i = 0; i < n; i++){
            printf("* %s %d %d\n", produto[a[i]].descricao, produto[a[i]].preco, (encomenda[num2].prod[a[i]]).qtd);
        } 
    }   
}

/*recebe caracteres e realiza as funcoes dependendo do comando que for escolhido, acaba o programa se o comando for x*/
int main(){
    
    char c;

    for (;;){

        switch (c = getchar()){
            
            case 'a':

                c = getchar();
                adiciona_produto();
                break;

            case 'q':

                c = getchar();
                adiciona_stock();
                break;

            case 'N':

                cria_encomenda();
                break;

            case 'A':

                c = getchar();
                adiciona_encomenda();
                break;

            case 'r':

                c = getchar();
                remove_stock();
                break;

            case 'R':

                c = getchar();
                remove_produto();
                break;

            case 'C':

                c = getchar();
                calcula_custo();
                break;

            case 'p':
             
                c =  getchar();
                altera_preco();
                break;

            case 'E':

                c = getchar();
                lista();
                break;

            case 'm':

                c = getchar();
                lista_identificador();
                break;

            case 'l':

                lista_stock();
                break;

            case 'L':

                c = getchar();
                lista_encomenda();
                break;
            
            case 'x':

                return 0;
                break;
        }
    }
    return 0;
}