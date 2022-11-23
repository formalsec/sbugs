#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*numero maximo de caracteres da descricao*/
#define NOME 64
/*numero maximo de produtos*/
#define MAXPROD 10000
/*peso maximo das encomendas*/
#define MAXPESO 200
/*numero maximo de encomendas*/
#define MAXENC 500
/*valores booleanos*/
#define TRUE 1
#define FALSE 0

/*caracteristicas do produto*/
typedef struct produto{
    int idp;
    char descricao[NOME];
    int preco;
    int pesoprod;
    int stock;
}produto;

/*caracteristicas da encomenda*/
typedef struct ecomenda{
    produto Vprodutos[MAXPESO];
    int ide;
    int pesoenc;
    int elementos;
}encomenda;


/*as variaveis utilizadosprod e utilizadosenc correspondem aos idps ja utilizados+1*/
int utilizadosprod = 0, utilizadosenc = 0;
/*variavel global dos produtos*/
produto prod;
/*variavel global das encomendas*/
encomenda enc;
/*o vetor sistemaprod contem todos os produtos que se encontram no sistema esta organizado pelo idp*/
produto sistemaprod[MAXPROD];
/*o vetor sistemaenc contem todas as encomendas do sistema esta organizado pelo ide*/
encomenda sistemaenc[MAXENC];


/*funcao com valor booleano que verifica se o ide eh valido*/
int VerificaEncomenda(int utilizadosenc, int ide)
{
    /*prod.ide > utilizadosenc nao existe*/
    if(ide >= utilizadosenc){
        return FALSE;
   }
    else{
        return TRUE;
    }
}
/*funcao com valor booleano que verifica se o idp eh valido*/
int VerificaProduto(int utilizadosprod, int idp)
{
    if(idp >= utilizadosprod){
            return FALSE;
        }
    else{
        return TRUE;
    }
}
/*funcao com valor booleano que verifica se ha quantidade suficiente em stock*/
int VerificaStock(int idp, int  qtd)
{
    if(sistemaprod[idp].stock >= qtd){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
/*funcao com valor booleano que verifica se o peso nao ultrapassa o valor maximo*/
int VerificaPeso(int ide, int idp, int qtd)
{
    if((sistemaenc[ide].pesoenc + (sistemaprod[idp].pesoprod * qtd)) > 200){
        return FALSE;
    }
    return TRUE;
}
/*funcao com valor booleano que informa se existe ou nao o produto na encomenda e caso exista adicioma a quantidade*/
int EncontraProduto(int qtd, int ide, int idp)
{
    int i;
    for(i = 0; i < sistemaenc[ide].elementos; i++){
        if(sistemaenc[ide].Vprodutos[i].idp == sistemaprod[idp].idp){
            sistemaenc[ide].Vprodutos[i].stock += qtd;
            sistemaprod[idp].stock -= qtd;
            sistemaenc[ide].pesoenc += sistemaprod[idp].pesoprod*qtd;
            return TRUE;
        }
    }
    return FALSE;
}
/*funcao a uma encomenda adiciona um produto ainda nao nela presente*/
void AdicionaProdEncomenda(int qtd, int ide, int idp)
{
    sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos].idp = sistemaprod[idp].idp;
    sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos].stock = qtd;
    sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos].preco = sistemaprod[idp].preco;
    strcpy(sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos].descricao, sistemaprod[idp].descricao);
    sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos].pesoprod = sistemaprod[idp].pesoprod;
    sistemaenc[ide].pesoenc += sistemaprod[idp].pesoprod*qtd;
    sistemaprod[idp].stock -= qtd;
    sistemaenc[ide].elementos++;
}
/*a funcao remove um produto de uma encomenda copiando para a posicao do vetor removido o ultimo vetor
e o ultimo produto que ja estava replicado para a posicao -1 do vetor e inicialiazdo*/
void RemoveDaEncomenda(int ide, int idp)
{
    int i;
    for(i = 0; i < sistemaenc[ide].elementos; i++){
        if(sistemaenc[ide].Vprodutos[i].idp == idp){
            sistemaprod[idp].stock += sistemaenc[ide].Vprodutos[i].stock;
            sistemaenc[ide].pesoenc -= sistemaenc[ide].Vprodutos[i].stock*sistemaenc[ide].Vprodutos[i].pesoprod;
            sistemaenc[ide].Vprodutos[i].idp = sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos-1].idp;
            sistemaenc[ide].Vprodutos[i].stock = sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos-1].stock;
            sistemaenc[ide].Vprodutos[i].pesoprod = sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos-1].pesoprod;
            sistemaenc[ide].Vprodutos[i].preco = sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos-1].preco;
            strcpy(sistemaenc[ide].Vprodutos[i].descricao, sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos-1].descricao);
            sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos-1].idp = -1;
            sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos-1].stock = 0;
            sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos-1].pesoprod = 0;
            sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos-1].preco = 0;
            strcpy(sistemaenc[ide].Vprodutos[sistemaenc[ide].elementos-1].descricao, "");
            sistemaenc[ide].elementos--;
            break;
        }
    }
}
/*Devolve 2 vetores ordenados desde left ate ao right dados dois vectores ordenados
correspondentes a cada um dos vetores desde left ate centro e desde centro ate right*/
void merge(int precos[], int esquerda, int centro, int direita, int indices[])
{
    int i1, i2, f, auxp1[MAXPROD], auxp2[MAXPROD], auxid1[MAXPROD], auxid2[MAXPROD];
    /*cria os vetores auxiliares*/
    for (i1 = 0; i1 < centro-esquerda+1; i1++){
        auxp1[i1] = precos[esquerda+i1];
        auxid1[i1] = indices[esquerda+i1];
    }
    for (i2 = 0; i2 <  direita-centro; i2++){
        auxp2[i2] = precos[centro+1+i2];
        auxid2[i2] = indices[centro +1+i2];
    }
    i1 = 0;
    i2 = 0;
    f = esquerda;
    while (i1 < centro-esquerda+1 && i2 <  direita-centro){
        if (auxp1[i1] <= auxp2[i2]){
            precos[f] = auxp1[i1];
            indices[f] = auxid1[i1];
            i1++;
        }
        else{
            precos[f] = auxp2[i2];
            indices[f] = auxid2[i2];
            i2++;
        }
        f++;
    }
    while (i1 < centro-esquerda+1){
        precos[f] = auxp1[i1];
        indices[f] = auxid1[i1];
        i1++;
        f++;
    }
    while (i2 < direita-centro){
        precos[f] = auxp2[i2];
        indices[f] = auxid2[i2];
        i2++;
        f++;
    }
}
void mergesort(int precos[], int esquerda, int direita, int indices[])
{
    if (esquerda < direita){
        int centro = esquerda+(direita-esquerda)/2;

        mergesort(precos, esquerda, centro, indices);
        mergesort(precos, centro+1, direita, indices);

        merge(precos, esquerda, centro, direita, indices);
    }
}
/*algoritmo de ordenacao*/
void quicksort(char descricao[][NOME], int left, int right, int indices[])
{
    int pivot = left, i, j, aux;
    char str[NOME];
    for(i = left+1; i <= right; i++){
        j = i;
        if(strcmp(descricao[j], descricao[pivot]) < 0){
            strcpy(str, descricao[j]);
            aux = indices[j];
            while(j > pivot){
                strcpy(descricao[j] ,descricao[j-1]);
                indices[j] = indices[j-1];
                j--;
            }
            strcpy(descricao[j], str);
            indices[j] = aux;
            pivot++;
        }
    }
    if(pivot-1 >= left){
        quicksort(descricao, left, pivot-1, indices);
    }
    if(pivot+1 <= right){
        quicksort(descricao, pivot+1, right, indices);
    }
}
/*adiciona um novo produto ao sistema*/
void comando_a(char descricao[], int preco, int peso, int stock)
{
    prod.idp = utilizadosprod;
    utilizadosprod++;
    sistemaprod[prod.idp].idp = prod.idp;
    sistemaprod[prod.idp].stock = stock;
    sistemaprod[prod.idp].pesoprod = peso;
    strcpy(sistemaprod[prod.idp].descricao, descricao);
    sistemaprod[prod.idp].preco = preco;
    printf("Novo produto %d.\n", prod.idp);
}
/*adiciona stock a um produto existente*/
void comando_q(int idp, int utilizadosprod, int qtd)
{
    int i;
    for(i = 0; i < utilizadosprod; i++){
        if(idp == sistemaprod[i].idp){
            sistemaprod[i].stock += qtd;
            break;
        }
    }
    if(i >= utilizadosprod){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}
/*cria uma nova encomenda*/
void comando_N()
{
    enc.ide = utilizadosenc;
    utilizadosenc++;
    sistemaenc[enc.ide].pesoenc = 0;
    sistemaenc[enc.ide].elementos = 0;
    printf("Nova encomenda %d.\n", enc.ide);
}
/*adiciona um produto a uma encomenda*/
void comando_A(int qtd, int ide, int idp)
{
    if (VerificaEncomenda(utilizadosenc, ide) == FALSE){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if(VerificaProduto(utilizadosprod, idp) == FALSE){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",  idp, ide);
    }
    else if(VerificaStock(idp, qtd) == FALSE){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",  idp, ide);
    }
    else if(VerificaPeso(ide, idp, qtd) == FALSE){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",  idp, ide);
    }
    else if(EncontraProduto(qtd, ide, idp) == TRUE){
        return;
    }
    else{
        AdicionaProdEncomenda(qtd, ide, idp);
    }
}
/*remove stock a um produto existente*/
void comando_r(int qtd, produto prod)
{
    if(VerificaProduto(utilizadosprod, prod.idp) == FALSE){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod.idp);
    }
    else if(VerificaStock(prod.idp, qtd) == FALSE){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, prod.idp);
    }
    else{
        sistemaprod[prod.idp].stock -= qtd;
    }
}
/*remove um produto de uma encomenda*/
void comando_R(int ide, int idp)
{
    if(VerificaEncomenda(utilizadosenc, ide) == FALSE){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if(VerificaProduto(utilizadosprod, idp) == FALSE){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else{
        RemoveDaEncomenda(ide, idp);
    }
}
/*calcula o custo de uma encomenda*/
void comando_C(int ide)
{
    int i, custo = 0;
    if (VerificaEncomenda(utilizadosenc, ide) == FALSE){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        for(i = 0; i < sistemaenc[ide].elementos; i++){
            custo += sistemaenc[ide].Vprodutos[i].preco*sistemaenc[ide].Vprodutos[i].stock;
        }
        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}
/*altera o pre?o de um produto existente no sistema*/
void comando_p(int idp, int preco)
{
    int i, j;
    if(VerificaProduto(utilizadosprod, idp) == FALSE){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        sistemaprod[idp].preco = preco;
        for(i = 0; i < utilizadosenc; i++){
            for (j = 0; j < sistemaenc[i].elementos; j++) {
                if(sistemaenc[i].Vprodutos[j].idp == idp){
                    sistemaenc[i].Vprodutos[j].preco = preco;
                }
            }
        }
    }
}
/*lista a descri??o e a quantidade de um produto numa encomenda*/
void comando_E(int ide, int idp)
{
    int i;
    if (VerificaEncomenda(utilizadosenc, ide) == FALSE){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if(VerificaProduto(utilizadosprod, idp) == FALSE){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else{
        for(i = 0; i < sistemaenc[ide].elementos; i++){
            if(sistemaenc[ide].Vprodutos[i].idp == idp){
                printf("%s %d.\n", sistemaenc[ide].Vprodutos[i].descricao, sistemaenc[ide].Vprodutos[i].stock);
                return;
            }
        }
        printf("%s 0.\n", sistemaprod[idp].descricao);
    }
}
/*lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
void comando_m(int idp)
{
    int flag = 0, qtd = 0, ide, i, j;
    if(VerificaProduto(utilizadosprod, idp) == FALSE){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else{
       for(i = 0; i < utilizadosenc; i++){
           for(j = 0; j < sistemaenc[i].elementos; j++){
               if(sistemaenc[i].Vprodutos[j].idp == idp ){
                   if(sistemaenc[i].Vprodutos[j].stock > qtd){
                       qtd = sistemaenc[i].Vprodutos[j].stock;
                       ide = i;
                       flag = 1;
                   }
               }
           }
        }
        if (flag == 1){
            printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
        }
    }
}
/*lista todos os produtos existentes no sistema por ordem crescente de pre?o*/
void comando_l()
{
    int i, indices[MAXPROD], precos[MAXPROD];
    for(i = 0; i < utilizadosprod; i++){
        indices[i] = i;
        precos[i] = sistemaprod[i].preco;
    }
    mergesort(precos, 0, utilizadosprod-1, indices);
    printf("Produtos\n");
    for(i = 0; i < utilizadosprod; i++){
        printf("* %s %d %d\n", sistemaprod[indices[i]].descricao, sistemaprod[indices[i]].preco, sistemaprod[indices[i]].stock);
    }
}
/*lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o*/
void comando_L(int ide){
    int i;
    char descricoes[MAXPESO][NOME];
    int indices[MAXPESO];
    if (VerificaEncomenda(utilizadosenc, ide) == FALSE){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        for(i = 0; i <= sistemaenc[ide].elementos; i++){
            strcpy(descricoes[i], sistemaenc[ide].Vprodutos[i].descricao);
            indices[i] = i;
        }
        quicksort(descricoes, 0, sistemaenc[ide].elementos-1, indices);
        printf("Encomenda %d\n",ide);
        for(i = 0; i < sistemaenc[ide].elementos; i++){
            printf("* %s %d %d\n",sistemaenc[ide].Vprodutos[indices[i]].descricao, sistemaenc[ide].Vprodutos[indices[i]].preco, sistemaenc[ide].Vprodutos[indices[i]].stock);
        }
    }
}
/*funcao principal que contem o loop principal*/
int main()
{
    int qtd, preco;
    /* o comando eh uma letra que indica uma determinada acao*/
    char comando;
    while((comando = getchar()) != EOF){
        switch (comando) {
            case 'a':
                scanf(" %[^:]:%d:%d:%d", prod.descricao, &prod.preco, &prod.pesoprod, &prod.stock);
                comando_a(prod.descricao, prod.preco, prod.pesoprod, prod.stock);
                break;
            case 'q':
                scanf("%d:%d", &prod.idp, &qtd);
                comando_q(prod.idp, utilizadosprod, qtd);
                break;
            case 'N':
                comando_N();
                break;
            case 'A':
                scanf("%d:%d:%d", &enc.ide, &prod.idp, &qtd);
                comando_A(qtd, enc.ide, prod.idp);
                break;
            case 'r':
                scanf("%d:%d", &prod.idp, &qtd);
                comando_r(qtd, prod);
                break;
            case 'R':
                scanf("%d:%d", &enc.ide, &prod.idp);
                comando_R(enc.ide, prod.idp);
                break;
            case 'C':
                scanf("%d", &enc.ide);
                comando_C(enc.ide);
                break;
            case 'p':
                scanf("%d:%d", &prod.idp, &preco);
                comando_p(prod.idp, preco);
                break;
            case 'E':
                scanf("%d:%d", &enc.ide, &prod.idp);
                comando_E(enc.ide, prod.idp);
                break;
            case 'm':
                scanf("%d", &prod.idp);
                comando_m(prod.idp);
                break;
            case 'l':
                comando_l();
                break;
            case 'L':
                scanf("%d", &enc.ide);
                comando_L(enc.ide);
                break;
            /*termina o programa*/
            case 'x':
                return 0;
        }
    }
return -1;
}
