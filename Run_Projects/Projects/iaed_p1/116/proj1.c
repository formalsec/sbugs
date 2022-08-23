#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define descricao_max 64
#define produtos_max 10000
#define encomendas_max 500
#define peso_max 20 /*esta constante tambem e usada como maximo de produtos numa encomenda*/


typedef struct {
    int idp;
    char descricao[descricao_max];
    int preco;
    int peso;
    int qtd;
} produto;

typedef struct {
    int ide;
    produto produt[peso_max];
    int pesoe; /*peso da encomenda*/
    int precoe; /*preco da encomenda*/
} encomenda;


/*prototipos*/

void colocarProdutosVazio(produto p[]); /*coloca o vetor de produtos com identificacao negativa*/
void colocarEncomendasVazias(encomenda e[]); /*coloca o vetor de encomendas com identificacao negativa*/
void adicionaProduto(produto p[]); /*acrescenta um produto ao vetor encomenda*/
void adicionaStock(produto p[]); /*acrescenta quantidade a um produto*/
void criaEncomenda(encomenda e[]); /*cria uma nova encomenda, colocando a sua identidade positiva */
void adicionaProdutoAEncomenda(produto p[], encomenda e[]); /*acrescenta quantidade de produto quer haja ou nao*/
void removeStock(produto p[]); /*retira quantidade a um produto*/
void removeProduto(produto p[], encomenda e[]); /*retira produto de uma encomenda de volta ao stock*/
void calculaCustoEncomenda(encomenda e[]); /*mostra o preco de uma encomenda*/
void alteraPreco(produto p[], encomenda e[]); /*altera o preco no stock e nas encomendas*/
void listaDescricaoQuantidade(encomenda e[]); /*lista a descricao e quantidade de um produto numa encomenda*/
void listaMaximoProduto(produto p[], encomenda e[]); /*lista a encomenda com mais um certo produto*/
void listaProdutos(produto p[]); /*lista os produtos em stock por preco*/
void listaProdutosEncomenda(encomenda e[]); /*lista produtos de uma encomenda*/


/*MAIN*/

int main() {
    char entrada; int i;
    produto prod[produtos_max];
    encomenda enc[encomendas_max];
    colocarProdutosVazio(prod);
    colocarEncomendasVazias(enc);
    while (1) {
        entrada=getchar();
        switch (entrada) {
        case 'a':
            getchar();
            adicionaProduto(prod);
            break;
        case 'q':
            getchar();
            adicionaStock(prod);
            break;
        case 'N':
            criaEncomenda(enc);
            break;
        case 'A':
            getchar();
            adicionaProdutoAEncomenda(prod, enc);
            break;
        case 'r':
            getchar();
            removeStock(prod);
            break;
        case 'R':
            getchar();
            removeProduto(prod, enc);
            break;
        case 'C':
            getchar();
            calculaCustoEncomenda(enc);
            break;
        case 'p':
            getchar();
            alteraPreco(prod, enc);
            break;
        case 'E':
            getchar();
            listaDescricaoQuantidade(enc);
            break;
        case 'm':
            getchar();
            listaMaximoProduto(prod, enc);
            break;
        case 'l':
            listaProdutos(prod);
            break;
        case 'L':
            getchar();
            listaProdutosEncomenda(enc);
            break;
        case 'z':
            for (i=0;prod[i].idp>-1;i++){
              printf("%d|%s|%d|%d|%d\n",prod[i].idp,prod[i].descricao,prod[i].preco,prod[i].peso,prod[i].qtd);
            }
            break;
        case 'Z':
            for (i=0;enc[i].ide>-1;i++){
              printf("%d|%d|%d\n",enc[i].ide,enc[i].precoe,enc[i].pesoe);
            }
            break;
        case 'x':
            return 0;
        }
    }
    return -1;
}



/*FUNCOES*/

void colocarProdutosVazio(produto p[]) {
    int i;
    for(i=0; i<produtos_max; i++) {
        p[i].idp=-1;
        p[i].qtd=0;
    }
}

void colocarEncomendasVazias(encomenda e[]) {
    int i,j;
    for(i=0; i<encomendas_max; i++) {
        e[i].ide=-1;
        for(j=0; j<produtos_max; j++) {
            e[i].produt[j].idp=-1;
            e[i].produt[j].qtd=0;
        }
    }
}

void adicionaProduto(produto p[]) {
    int i=0, contador=0;
    char c, caracteres[descricao_max];
    produto p1;
    while((c=getchar())!=EOF && c!='\n') {
        if(contador==0 && c!=':') {
            p1.descricao[i]=c;
            i++;
        }
        else if(c==':') {
            switch(contador) {
            case 1:
                p1.preco=atoi(caracteres);
                break;
            case 2:
                p1.peso=atoi(caracteres);
                break;
            case 3:
                p1.qtd=atoi(caracteres);
                break;
            }
            contador++;
            i=0;
        }
        else {
            caracteres[i]=c;
            i++;
        }
    }
    p1.qtd=atoi(caracteres);
    for (i=0; i<produtos_max; i++) {
        if (p[i].idp==-1) {
            p1.idp=i;
            p[i]=p1;
            break;
        }
    }
}

void adicionaStock(produto p[]) {
    int i=0,identidade,quantidade;
    char c,caracteres[descricao_max];
    while((c=getchar())!=EOF && c!='\n') {
        if(c==':') {
            identidade=atoi(caracteres);
            i=0;
        }
        else {
            caracteres[i]=c;
            i++;
        }
    }
    quantidade=atoi(caracteres);
    for (i=0; i<produtos_max; i++) {
        if(p[i].idp==-1) {
            printf("Impossivel adicionar produto %d ao stock. Produto inexistente.", identidade);
            return;
        }
        else if(identidade==p[i].idp) {
            p[i].qtd+=quantidade;
            break;
        }
    }
}

void criaEncomenda(encomenda e[]) {
    int i;
    for(i=0; i<encomendas_max; i++) {
        if (e[i].ide==-1) {
            e[i].ide=i;
            e[i].pesoe=0;
            e[i].precoe=0;
            break;
        }
    }
}

void adicionaProdutoAEncomenda(produto p[], encomenda e[]) {
    int i=0, j, k, contador=0, id_enc, id_prod, quant;
    char c, caracteres[64];
    while((c=getchar())!=EOF && c!='\n') {
        if(c==':') {
            i=0;
            contador++;
            switch(contador) {
            case 1:
                id_enc=atoi(caracteres);
                break;
            case 2:
                id_prod=atoi(caracteres);
                break;
            }
        }
        else {
            caracteres[i]=c;
            i++;
        }
    }
    quant=atoi(caracteres);
    if(id_enc>=encomendas_max) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.", id_enc, id_prod);
        return;
    }
    if(id_prod>=produtos_max) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.", id_enc, id_prod);
        return;
    }
    for (j=0; j<encomendas_max; j++) {
        if(e[j].ide==-1) {
            printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.", id_enc, id_prod);
            return;
        }
        else if(e[j].ide==id_enc) break;
    }
    for (i=0; i<produtos_max; i++) {
        if(p[i].idp==-1) {
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.", id_enc, id_prod);
            return;
        }
        else if(p[i].idp==id_prod) {
            if(p[i].qtd<quant) {
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.", id_enc, id_prod);
                return;
            }
            else if(p[i].qtd*p[i].peso+e[j].pesoe>peso_max) {
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.", id_enc, id_prod);
                return;
            }
            else {
                e[j].pesoe+=quant*p[i].peso; /*aumenta o peso total da encomenda*/ 
                e[j].precoe+=quant*p[i].preco; /*aumenta o preco total da encomenda*/ 
                for (k=0; k<peso_max; k++) {
                    if(e[j].produt[k].idp==id_prod){
                        e[j].produt[k].qtd+=quant; /*aumenta a quantidade do produto existente*/
                        break;
                    }
                    else {
                        e[j].produt[k].idp=p[i].idp; /*coloca as caracterisiticas do produto encomendado*/
                        strcpy(p[i].descricao,e[j].produt[k].descricao);
                        e[j].produt[k].preco=p[i].preco;
                        e[j].produt[k].peso=p[i].peso;
                        e[j].produt[k].qtd=quant; /*coloca a quantidade do produto encomendado*/
                        break;
                    }
                } 
                p[i].qtd-=quant; /*diminui a quantidade de produto em stock*/
                return;
            }
        }
    }
}

void removeStock(produto p[]){
    int i,identidade,quantidade;
    char c,caracteres[descricao_max];
    while((c=getchar())!=EOF && c!='\n') {
        if(c==':') {
            identidade=atoi(caracteres);
            i=0;
        }
        else {
            caracteres[i]=c;
            i++;
        }
    }
    quantidade=atoi(caracteres);
    for (i=0; i<produtos_max; i++) {
        if(p[i].idp==-1) {
            printf("Impossivel remover produto %d ao stock. Produto inexistente.", identidade);
            return;
        }
        else if(identidade==p[i].idp) {
            if(p[i].qtd<quantidade){
                printf("Impossivel remover produto %d ao stock. Quantidade insuficiente.", identidade);
                return;
            }
            else p[i].qtd-=quantidade;
            break;
        }
    }
}

void removeProduto(produto p[], encomenda e[]) {
    int i=0,j,k,m, id_prod,id_enc;
    char c,caracteres[descricao_max];
    while((c=getchar())!=EOF && c!='\n') {
        if(c==':') {
            id_prod=atoi(caracteres);
            i=0;
        }
        else {
            caracteres[i]=c;
            i++;
        }
    }
    id_enc=atoi(caracteres);
    if(id_enc>=encomendas_max) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.", id_enc, id_prod);
        return;
    }
    if(id_prod>=produtos_max) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.", id_enc, id_prod);
        return;
    }
    for (k=0; k<produtos_max; k++) {
        if(p[k].idp==id_prod) break;
        else if (p[k].idp==-1){ 
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.", id_enc, id_prod);
            return;
        }
    }
    for (i=0; i<encomendas_max; i++) {
        if(e[i].ide==-1) {
            printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.", id_enc, id_prod);
            return;
        }
        else if(e[i].ide==id_enc){
            for (j=0; j<peso_max; j++){
                if(e[i].produt[j].idp==id_prod){
                    e[i].pesoe-=e[i].produt[j].peso*e[i].produt[j].qtd; /*diminui o peso da encomenda*/
                    e[i].precoe-=e[i].produt[j].preco*e[i].produt[j].qtd; /*diminui o preco da encomenda*/
                    p[k].qtd+=e[i].produt[j].qtd; /*aumenta a quantidade do produto em stock*/
                    for (m=j; m<peso_max-1 && e[i].produt[m].idp!=-1; m++) {
                        e[i].produt[m]=e[i].produt[m+1];
                    } /*apagar o produto da encomenda, nao deixando buracos no vetor*/
                    e[i].produt[peso_max-1].idp=-1; 
                    return; 
                }
            }
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.", id_enc, id_prod);
            return;
        }
    }
}

void calculaCustoEncomenda(encomenda e[]) {
    int i=0, id_enc;
    char c,caracteres[descricao_max];
    while((c=getchar())!=EOF && c!='\n') {
        caracteres[i]=c;
        i++;
    }
    id_enc=atoi(caracteres);
    if(id_enc>=encomendas_max) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.", id_enc);
        return;
    }
    for (i=0; i<encomendas_max; i++) {
        if (e[i].ide==-1){
            printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.", id_enc);
            return;
        }
        else if (e[i].ide==id_enc){
            printf("Custo da encomenda %d %d.", id_enc, e[i].precoe);
            return;
        }
    }
}

void alteraPreco(produto p[], encomenda e[]) { 
    int i=0, j, id_prod, novo_preco;
    char c,caracteres[descricao_max];
    while((c=getchar())!=EOF && c!='\n') {
        if(c==':') {
            id_prod=atoi(caracteres);
            i=0;
        }
        else {
            caracteres[i]=c;
            i++;
        }
    }
    novo_preco=atoi(caracteres);
    for (i=0; i<produtos_max; i++){
        if (p[i].idp==-1){
            printf("Impossivel alterar preco do produto %d. Produto inexistente.",id_prod);
            return;
        }
        else if (p[i].idp==id_prod){
            p[i].preco=novo_preco; /*alterar o preco do produto no stock*/
            return;
        }
    }
    for (i=0; i<encomendas_max; i++){
        if (e[i].ide==-1) break;
        for (j=0; j<peso_max; j++){
            if (e[i].produt[j].idp==-1) break;
            else if (p[i].idp==id_prod) 
                p[i].preco=novo_preco; /*alterar o preco do produto nas encomendas*/
        }
    }
}

void listaDescricaoQuantidade(encomenda e[]) {
    int i=0, j, id_prod, id_enc;
    char c,caracteres[descricao_max];
    while((c=getchar())!=EOF && c!='\n') {
        if(c==':') {
            id_enc=atoi(caracteres);
            i=0;
        }
        else {
            caracteres[i]=c;
            i++;
        }
    }
    id_prod=atoi(caracteres);
    for (i=0; i<encomendas_max; i++){
        if (e[i].ide==-1){
            printf("Impossivel listar encomenda %d. Encomenda inexistente.", id_enc);
            return;
        }
        else if (e[i].ide==id_enc){
            for (j=0; j<peso_max; j++){
                if (e[i].produt[j].idp==-1) {
                    printf("Impossivel listar produto %d. Produto inexistente.", id_prod);
                    return;
                }
                else if (e[i].produt[j].idp==id_prod){
                    printf("%s %d.", e[i].produt[j].descricao, e[i].produt[j].qtd);
                    return;
                }
            }        
        }
    }
}

void listaMaximoProduto(produto p[], encomenda e[]) {
    int i=0, j, max=0, enc_max=-1, id_prod;
    char c,caracteres[descricao_max];
    while((c=getchar())!=EOF && c!='\n') {
        caracteres[i]=c;
        i++;
    }
    id_prod=atoi(caracteres);
    for (i=0; i<produtos_max; i++){
        if (p[i].idp==-1) {
            printf("Impossivel listar maximo do produto %d. Produto inexistente.", id_prod);
            return;
        }
        else if (p[i].idp==id_prod) break;
    }
    for (i=0; i<encomendas_max; i++) {
        for (j=0; j<peso_max; j++) {
            if (e[i].produt[j].idp==-1) break;
            else if (e[i].produt[j].idp==id_prod){
                if (max<e[i].produt[j].qtd) {
                    max=e[i].produt[j].qtd;
                    enc_max=e[i].ide;
                }
                break;
            }
        }
    }
    if (max>0) printf("Maximo produto %d %d %d.", id_prod, enc_max, max);
}


/*prototipo auxiliar de ordenacao*/
void quickSort1(produto arr[], int inicio, int fim);

void listaProdutos(produto p[]) {
    int k, n=0;
    for (k=0; k<produtos_max; k++){
        if (p[k].idp==-1) {
            n=k-1;
            break;
        }
    }
    quickSort1(p, 0, n);
    printf("Produtos\n");
    for (k=0; k<=n; k++){
        printf("%s %d %d\n", p[k].descricao, p[k].preco, p[k].qtd);
    }
}

/*funcao auxiliar de ordenacao de produtos*/
void quickSort1(produto arr[], int inicio, int fim) {
    int i=inicio, j=fim;
    produto pivot=arr[(inicio+fim)/2], troca;
        while (i<=j) {
            while (arr[i].preco<pivot.preco || 
            (arr[i].preco==pivot.preco && arr[i].idp<pivot.idp))
                i++;
            while (arr[i].preco>pivot.preco || 
            (arr[i].preco==pivot.preco && arr[i].idp>pivot.idp))
                j--;
            if (i<=j) {
                troca=arr[i];
                arr[i]=arr[j];
                arr[j]=troca;
                i++;
                j--;
            }
        }
        if(inicio<j) 
            quickSort1(arr, inicio, j);
        if(i<fim) 
            quickSort1(arr, i, fim);
    }

/*prototipo auxiliar de ordenacao*/
void quickSort2(produto arr[], int inicio, int fim);

void listaProdutosEncomenda(encomenda e[]) {
    int k=0, m, n=peso_max, id_enc;
    char c,caracteres[descricao_max];
    while((c=getchar())!=EOF && c!='\n') {
        caracteres[k]=c;
        k++;
    }
    id_enc=atoi(caracteres);
    for (k=0; k<encomendas_max; k++){
        if (e[k].ide==-1) {
            printf("Impossivel listar encomenda %d. Encomenda inexistente", id_enc);
            return;
        }
        else if (e[k].ide==id_enc) {
            for (m=0; m<peso_max; m++){
                if (e[k].produt[m].idp==-1){
                    n=m-1;
                    break;
                }
            }
        }
    }
    quickSort2(e[k].produt, 0, n);
    printf("Encomenda %d\n", id_enc);
    for (k=0; k<=n; k++){
        printf("* %s %d %d\n", e[k].produt[m].descricao, e[k].produt[m].preco, e[k].produt[m].qtd);
    }
}

/*funcao auxiliar de ordenacao de produtos na encomenda*/
void quickSort2(produto arr[], int inicio, int fim) {
    int i=inicio, j=fim;
    produto pivot=arr[(inicio+fim)/2], troca;
        while (i<=j) {
            while (arr[i].descricao<pivot.descricao)
                i++;
            while (arr[i].descricao>pivot.descricao)
                j--;
            if (i<=j) {
                troca=arr[i];
                arr[i]=arr[j];
                arr[j]=troca;
                i++;
                j--;
            }
        }
        if(inicio<j) 
            quickSort2(arr, inicio, j);
        if(i<fim) 
            quickSort2(arr, i, fim);
    }