#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define NPRODUTOS 10000  /*Numero maximo de produtos existentes no sistema.*/
#define ENCOMENDA 500   /*Numero maximo de encomendas.*/
#define PESOLIM 200     /*Limite maximo de peso por encomenda.*/
#define DIM 63         /*Numero maximo de caracteres da descricao.*/



/*Definicao da estrutura produto.*/
typedef struct produto{
    int identificador;
    char descricao[DIM];
    int preco;
    int peso;
    int quantidade;
}produto;

/*Definicao da estrutura encomenda.*/
typedef struct encomenda{
    produto produto[NPRODUTOS];
}encomenda;

/*Inicializacao das variaveis globais.*/
char comando;  /*Caracter correspondente ao comando que pretendemos executar.*/
int i=0, e=0;  /* i - numero de produtos no sistema. e - numero de encomendas. */
int nenc[ENCOMENDA]; /*Numero de produtos presentes em cada encomenda.*/
produto sistema[NPRODUTOS];   /* Vetor onde ficam guardados no maximo 10000 produtos.*/
encomenda encomendas[ENCOMENDA];  /*Vetor onde ficam guardadas no maximo 500 encomendas.*/
produto aux[NPRODUTOS];  /*Vetor auxiliar da funcao merge.*/

/*Copia as caracteristicas do produto sistema[m] para o produto sistemarep[r].*/
void copia(produto sistemarep[], produto sistema[], int r, int m){
    sistemarep[r].identificador=sistema[m].identificador;
    strcpy(sistemarep[r].descricao,sistema[m].descricao);
    sistemarep[r].preco=sistema[m].preco;
    sistemarep[r].peso=sistema[m].peso;
    sistemarep[r].quantidade=sistema[m].quantidade;
}

/*Adiciona um novo produto ao sistema.*/
void __a__( int i,produto sistema[]){
    scanf(" %[^:]:%d:%d:%d", sistema[i].descricao, &sistema[i].preco, &sistema[i].peso, &sistema[i].quantidade);
    sistema[i].identificador=i;

}

/*Adiciona stock a um produto existente no sistema.*/
void __q__(int i, produto sistema[]){
    /*idp - identificador do produto. quant - stock que vai ser adicionado ao produto.*/
    int idp, quant;  
    scanf(" %d:%d", &idp, &quant);
    /*Caso o produto nao esteja no sistema.*/
    if (idp>=i){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
    /*Adiciona a quantidade recebida como argumento a quantidade existente anteriormente no sistema.*/
    else{
        sistema[idp].quantidade+=quant;
    }
}

/*Adiciona um produto a uma encomenda.*/
void __A__(int e,int i, encomenda encomendas[], produto sistema[], int nenc[]){
    /*ide - identificador da encomenda. idp - identificador do produto. 
    quant - quantidade do produto que se vai adicionar a encomenda. peso - peso total da encomenda.*/
    int ide, idp, quant, s, peso=0, n=1, num;
    scanf(" %d:%d:%d", &ide, &idp, &quant);
    num=nenc[ide];
    /*Caso a encomenda nao exista.*/
    if (ide>=e){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    /*Caso o produto nao esteja no sistema.*/
    else if(idp>=i){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    /*Caso a quantidade do produto que se pretende adicionar a encomenda seja superior a quantidade do produto existente no sistema.*/
    else if(quant>sistema[idp].quantidade){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else{   
        /*Calcula o peso da encomenda.*/
        for (s=0; s<nenc[ide]; s++){  
            peso=encomendas[ide].produto[s].peso*encomendas[ide].produto[s].quantidade+peso;
        } 
        peso=sistema[idp].peso*quant+peso;
        /*Caso a encomenda exceda o peso limite de 200 unidades de peso.*/
        if (peso>PESOLIM){
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else{
            /*Ciclo que verifica se o produto ja esta na encomenda e em caso afirmativo 
            a quantidade recebida como argumento e acrescentada a quantidade existente na encomenda.*/
            for (s=0; s<num; s++){
                if (idp==encomendas[ide].produto[s].identificador){
                    encomendas[ide].produto[s].quantidade+=quant;
                    n=0;
                    /*Sai do ciclo.*/
                    s=num;
                }
            }
            /*n=1 significa que o produto ainda nao esta na encomenda e por isso e adicionado a encomenda.*/
            if (n==1){
                encomendas[ide].produto[nenc[ide]]=sistema[idp];
                encomendas[ide].produto[nenc[ide]].quantidade=quant;
                nenc[ide]+=1;
            }
            /*A quantidade do produto existente no sistema diminui.*/
            sistema[idp].quantidade-=quant;
        }
    }
}

/*Remove stock a um produto existente.*/
void __r__(int i, produto sistema[]){
    /*idp - identificador do produto. quant - stock que vai ser removido ao produto.*/
    int idp, quant;
    scanf(" %d:%d", &idp, &quant);
    /*Caso o produto nao exista no sistema.*/
    if (idp>=i){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
    /*Caso a quantidade de stock restante apos a remocao ser negativa.*/
    else if(quant>sistema[idp].quantidade){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, idp);
    }
    else{
        sistema[idp].quantidade-=quant;
    }
}

/*Remove um produto de uma encomenda.*/
void __R__(int i, int e, encomenda encomendas[], int nenc[], produto sistema[]){
    /*ide - identificador da encomenda. idp - identificador do produto.*/
    int ide, idp, n, num;
    /*Produto vazio, ou seja, inicializado a 0.*/
    produto prodvazio[1]; 
    scanf(" %d:%d", &ide, &idp);
    num=nenc[ide];
    /*Caso a encomenda nao exista.*/
    if (ide>=e){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    /*Caso o produto nao esteja no sistema.*/
    else if(idp>=i){   
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else{
        for (n=0; n<num; n++){
            if (encomendas[ide].produto[n].identificador==idp){
                /*Caso o produto seja o ultimo produto existente na encomenda.*/
                if (n==nenc[ide]-1){
                    sistema[idp].quantidade+=encomendas[ide].produto[n].quantidade;
                    /*O produto e eliminado.*/
                    copia(encomendas[ide].produto, prodvazio, n, 0);
                    
                }
                /*Caso contrario.*/
                else{
                    sistema[idp].quantidade+=encomendas[ide].produto[n].quantidade;
                    /*O produto que se pretende remover fica com as caracteristicas do ultimo produto da encomenda.*/
                    copia(encomendas[ide].produto, encomendas[ide].produto, n, nenc[ide]-1);
                    /*O ultimo produto fica repetido e por isso o produto presente na ultima posicao do vetor e eliminado.*/
                    copia(encomendas[ide].produto, prodvazio, nenc[ide]-1, 0);
                    /*Sai do ciclo.*/
                    n=num;
                }
            nenc[ide]-=1;   
            }
        }
    }
}

/*Calcula o custo de uma encomenda.*/
void __C__(int e, encomenda encomendas[], int nenc[]){
    /*ide - identificador da encomenda. total - custo total da encomenda.*/
    int ide, n, total=0, num;  
    scanf(" %d", &ide);
    num=nenc[ide];
    /*Caso a encomenda nao exista.*/
    if (ide>=e){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        for (n=0; n<num; n++){
            total=encomendas[ide].produto[n].preco*encomendas[ide].produto[n].quantidade+total;
        }
        printf("Custo da encomenda %d %d.\n", ide, total);
    }

}

/*Altera o preco de um produto existente no sitema.*/
void __p__(int i, int e, produto sistema[], encomenda encomendas[], int nenc[]){
    /*idp - identificador da encomenda. preco - valor para o qual se pretende alterar o preco da encomenda.*/
    int idp, prec, n, m;
    scanf(" %d:%d", &idp, &prec);
    /*Caso o produto nao esteja no sistema.*/
    if (idp>=i){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        /*Altera o preco do produto no sistema.*/
        sistema[idp].preco=prec;
        /*Verifica se o produto esta presente em alguma encomenda e em caso afirmativo altera o seu preco.*/
        for (n=0; n<e; n++){
            for (m=0; m<nenc[n]; m++){
                if (encomendas[n].produto[m].identificador==idp){
                    encomendas[n].produto[m].preco=prec;
                    /*Sai do segundo ciclo.*/
                    m=nenc[n];
                }
            }
        }
    }
}

/*Retorna a descricao e a quantidade de um produto numa dada encomenda.*/
void __E__(int i, int e, encomenda encomendas[], int nenc[], produto sistema[]){
    /*ide - identificador da encomenda. idp - identificador do produto.*/
    int ide, idp, n, m=1, num;
    scanf(" %d:%d", &ide, &idp);
    num = nenc[ide];
    /*Caso a encomenda nao exista.*/
    if (ide>=e){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    /*Caso o produto nao esteja no sistema.*/
    else if(idp>=i){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else{
        for (n=0; n<num; n++){
            /*Caso o produto esteja na encomenda.*/
            if (encomendas[ide].produto[n].identificador==idp){
                printf("%s %d.\n", encomendas[ide].produto[n].descricao, encomendas[ide].produto[n].quantidade);
                m=0;
                /*Sai do ciclo.*/
                n=num;
            }
        }
        /*Caso m=1 significa que o produto nao esta na encomenda e por isso a sua quantidade e 0.*/
        if (m==1){
            printf("%s 0.\n", sistema[idp].descricao);
        }
    }
}

/*Retorna o identificador da encomenda em que um dado produto ocorre mais vezes.*/
void __m__(int i, int e, encomenda encomendas[], int nenc[]){
    /*idp - identificador do produto. qtd - quantidade do produto na encomenda em que ocorre mais vezes.
    en - identificador da encomenda.*/
    int idp, n, m, qtd=0, en, se=1;
    scanf(" %d", &idp);
    /*Caso o produto nao esteja no sistema.*/
    if (idp>=i){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else{
        /*Verifica se o produto esta em alguma encomenda.*/
        for (n=0; n<e; n++){
            for (m=0; m<nenc[n]; m++){
                /*Caso o produto esteja na encomenda e seja o caso em que ate agora se encontra em maior quantidade.*/
                if (encomendas[n].produto[m].identificador==idp && encomendas[n].produto[m].quantidade>qtd){
                    qtd=encomendas[n].produto[m].quantidade;
                    en=n;
                    se=0;
                    /*Sai do segundo ciclo.*/
                    m=nenc[n];
                }
            }
        }
        /*Caso o produto esteja presente em alguma encomenda e retornado o seu identificador,
         a encomenda em que ocorre mais vezes e a quantidade em que ocorre.*/
        if (se==0){
            printf("Maximo produto %d %d %d.\n", idp, en, qtd);
        }
    }
}

/*Algoritmo de ordenacao.*/
void merge(produto a[], int l, int m, int r){ 
    int i, j, k;
    /*Constroi o vetor auxiliar.*/
    for (i = m+1; i > l; i--){ 
        aux[i-1] = a[i-1];
    }
    for (j = m; j < r; j++){
        aux[r+m-j] = a[j+1];
    }
    /*Escolhe os produtos da ponta para ordenar o vetor a por ordem crescente de preco.*/
    for (k = l; k <= r; k++){
        /*Troca caso o produto na posicao j tenha preco mais baixo ou preco igual ao da posicao i mas menos identificador.*/
        if (aux[j].preco<aux[i].preco || (aux[j].preco==aux[i].preco && aux[j].identificador<aux[i].identificador)){
            a[k] = aux[j--];
        }
        else{
            a[k] = aux[i++];
        }
    }
}

/*Algoritmo de ordenacao.*/
void mergesort(produto a[], int l, int r) { 
    int m = (r+l)/2;
    if (r <= l){
        return;
    }
    mergesort(a, l, m);
    mergesort(a, m+1, r);
    merge(a, l, m, r);
}

/*Lista todos os produtos existentes no sistema por ordem crescente de preco.*/
void __l__(int i, produto sistema[]){
    int n;
    /*Variavel que vai servir de copia do sistema para posteriormente ser ordenada.*/
    produto sistemarep[NPRODUTOS];  
    for (n=0; n<i; n++){
        /*Os produtos presentes no sistema sao copiados para o sistemarep.*/
        copia(sistemarep, sistema, n, n);
        
    }
    /*Os produtos presentes na copia do sistema sao ordenados por ordem crescente de preco.*/
    mergesort(sistemarep, 0, i-1);
    printf("Produtos\n");
    for (n=0; n<i; n++){
        
        printf("* %s %d %d\n", sistemarep[n].descricao, sistemarep[n].preco, sistemarep[n].quantidade);
        
    }
}

/*Algoritmo de ordenacao que ordena cadeias de caracteres por ordem alfabetica.*/
int partitionstr(encomenda encomendas[], int l, int r, int ide) {
    /*l - posicao mais a esquerda do vetor. r - posicao mais a direita do vetor*/
    int i = l-1, j = r;
    /*Variavel auxiliar para se fazer a troca de posicoes entre dois produtos.*/
    produto t[1]; 
    char v[DIM];
    /*encomendas[ide].produto[r].descricao e o pivot.*/
    strcpy(v, encomendas[ide].produto[r].descricao);
    /*Enquanto o iterador da esquerda for menor que o iterador da direita.*/
    while (i < j) {

        /*Enquanto encomendas[ide].produto[i]<v avanca com o i para a direita.*/
        while (strcmp(encomendas[ide].produto[++i].descricao, v)<0);
        /*Enquanto v<encomendas[ide].produto[j] avanca com o j para a esquerda.*/
        while (strcmp(v, encomendas[ide].produto[--j].descricao)<0){
            /*Caso o elemento onde se faz a particao seja o primeiro.*/
            if (j == l) 
            break;
        }
    /*Troca, se for o caso.*/ 
        if (i < j){
            copia(t, encomendas[ide].produto, 0, i);
            copia(encomendas[ide].produto, encomendas[ide].produto, i, j);
            copia(encomendas[ide].produto, t, j, 0);
        }
    }
    /*Coloca o pivot na posicao i.*/
    copia(t, encomendas[ide].produto, 0, i);
    copia(encomendas[ide].produto, encomendas[ide].produto, i, r);
    copia(encomendas[ide].produto, t, r, 0);
    /*Retorna posicao onde ocorreu a particao.*/
    return i;
}

/*Algoritmo de ordenacao.*/
void quicksortstr(encomenda encomendas[], int l, int r, int ide) 
{
    int i;
    if (r <= l){
        return;
    }
    i = partitionstr(encomendas, l, r, ide);
    quicksortstr(encomendas, l, i-1, ide);
    quicksortstr(encomendas, i+1, r, ide);
}

/*Lista todos os produtos existentes numa encomenda por ordem alfabetica de descricao.*/
void __L__(int e, int nenc[], encomenda encomendas[]){
    /*ide - identificador da encomenda.*/
    int ide, n;
    scanf(" %d", &ide);
    /*Caso a encomenda nao exista.*/
    if (ide>=e){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        /*Os produtos presentes na encomenda sao ordenados por ordem alfabetica de descricao.*/
        quicksortstr(encomendas, 0, nenc[ide]-1, ide);
        printf("Encomenda %d\n", ide);
        for (n=0; n<nenc[ide]; n++){
            printf("* %s %d %d\n", encomendas[ide].produto[n].descricao, encomendas[ide].produto[n].preco, encomendas[ide].produto[n].quantidade);
        }
    }

}

/*Le caracteres correspondentes a comandos e executa uma instrucao dependendo do comando lido.*/
int main(){
    /*O programa le o primeiro comando a ser executado.*/
    scanf("%c", &comando);
    /*O comando x termina o programa.*/
    while (comando!='x'){
        switch (comando){
            case 'a':
            __a__(i,sistema);
            printf("Novo produto %d.\n", i);
            i+=1;
            break;

            case 'q':
            __q__(i, sistema);
            break;

            case 'N':
            printf("Nova encomenda %d.\n", e);
            nenc[e]=0;
            e+=1;
            break;

            case 'A':
            __A__(e, i, encomendas, sistema, nenc);
            break;

            case 'r':
            __r__(i, sistema);
            break;

            case 'R':
            __R__(i, e, encomendas, nenc, sistema);
            break;

            case 'C':
            __C__(e, encomendas, nenc);
            break;

            case 'p':
            __p__(i, e, sistema, encomendas, nenc);
            break;

            case 'E':
            __E__(i, e, encomendas, nenc, sistema);
            break;

            case 'm':
            __m__(i, e, encomendas, nenc);
            break;

            case 'l':
            __l__(i, sistema);
            break;

            case 'L':
            __L__(e, nenc, encomendas);
            break;
        }
        scanf("%c",&comando);
    }

    return 0;
    
}