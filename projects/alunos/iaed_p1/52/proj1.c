#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*numero maximo de caracteres de uma descricao de um produto*/
#define MAX_DESCR 63
/*numero maximo de produtos no sistema*/
#define MAX_PROD 10000
/*numero maximo de encomendas no sistema*/
#define MAX_ENC 500

/* Estrutura produto: um produto eh caracterizado pela sua descricao, preco, peso, quantidade em stock e idp */
typedef struct produto {
    char descr[MAX_DESCR];
    int preco;
    int peso;
    int qtd;
    int idp;
}prod;

/* Numero de produtos(respetivamente encomendas) no sistema */
int total_prod,total_enc;
/* Array com todos produtos em stock */
prod stock[MAX_PROD];
/* Tebela com a quantidade de cada produto em cada encomenda*/
int encomendas[MAX_ENC][MAX_PROD]; /* encomenda[i][j] e a quantidade do produto j na encomenda i */


/* Devolve o peso total de uma encomenda */
int peso_enc(int ide){
    int idp,peso_total=0; 

    for (idp=0;idp<total_prod;idp++) /* percorre todos os produtos criados */
        peso_total+= stock[idp].peso * encomendas[ide][idp]; /*adiciona ao peso total o peso de cada produto multiplicado pela sua quantidade na encomenda */

    return peso_total;
}


/* Retorna 1 se duas strings estiverem ordenadas alfabeticamente e 0 caso contrario*/
int ordem_alfabetica(char s1[MAX_DESCR],char s2[MAX_DESCR]){
    int i=0;

    /* Percorre as duas strings ate encontrar um caracter diferente */
    while (s1[i]==s2[i] && i<MAX_DESCR) 
        i++;

    /* retorna 1 caso as duas strings estejam ordenadas */
    if (s1[i]<s2[i])
        return 1;

    return 0; /* retorna 0 caso contrario */
}


/* Adiciona um novo produto ao sistema */
void comando_a(){
    getchar(); /* Le o espaco introduzido pelo utilizador entre o comando e a descricao do produto*/
    
    scanf("%[^:]:%d:%d:%d", stock[total_prod].descr, &stock[total_prod].preco, &stock[total_prod].peso, &stock[total_prod].qtd);

    /* O idp do novo produto sera igual ao total dos produtos em stock (total_prod) */
    stock[total_prod].idp = total_prod; 

    printf("Novo produto %d.\n",total_prod++); /* Incrementa o total de produto no sistema depois de realizar o printf() */
}


/* Adiciona stock a um produto existente no sistema */
void comando_q(){
    int idp,qtd;
    scanf("%d:%d",&idp,&qtd);

    if (idp>=total_prod) /* erro caso nao existir nenhum produto criado com esse identificador*/
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
    else
        /* Soma a quantida lida a quantidade do produto em stock */
        stock[idp].qtd+=qtd; 
}


/* Cria uma nova encomenda */
void comando_N(){
    int idp;

    /*altera a quantidade de todos os produtos da nova encomenda para 0 */
    for (idp=0;idp<MAX_PROD;idp++) 
        encomendas[total_enc][idp]=0; 

    printf("Nova encomenda %d.\n",total_enc++); /* Incrementa o total de encomendas no sistema depois de realizar o printf() */
}


/* Adiciona um produto a uma encomenda */
void comando_A(){
    int idp,ide,qtd;
    scanf("%d:%d:%d",&ide,&idp,&qtd);

    if (ide>=total_enc) /* Erro caso nao existir nenhuma encomenda criada com esse identificador */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);

    else if (idp>=total_prod) /* Erro caso nao existir nenhum produto criado com esse identificador */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);

    else if (stock[idp].qtd-qtd<0) /* Erro caso nao existir stock suficente para esse produto satisfazer a encomenda */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);

    else if (peso_enc(ide)+stock[idp].peso*qtd >200) /* Erro caso a adicao desse produto exceder o peso maximo da encomenda */
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);

    else {
        /* Adiciona a quantidade do produto dada pelo utilizador a encomenda*/
        encomendas[ide][idp]+=qtd; 
        /* Retira essa quantidade ao stock do produto */
        stock[idp].qtd-=qtd; 
    }
}


/* Remove stock a um produto existente */
void comando_r(){
    int idp,qtd;
    scanf("%d:%d",&idp,&qtd);

    if (idp>=total_prod) /* Erro caso nao existir nenhum produto criado com esse identificador */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);

    else if (stock[idp].qtd-qtd<0) /* Erro caso a quantidade de stock restante apos a remocao ser negativa */
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);

    else {
        /* subtrai a quantidade indicada pelo utilizador a quantidade de produto em stock */
        stock[idp].qtd-=qtd; 
    }
}


/* Remove um produto de uma encomenda */
void comando_R(){
    int idp,ide;
    scanf("%d:%d",&ide,&idp);

    if (ide>=total_enc) /* Erro caso nao existir nenhuma encomenda criada com esse identificador */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
 
    else if (idp>=total_prod) /* Erro caso nao existir nenhum produto criado com esse identificador */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
 
    else {
        /* Adiciona a quantidade de produto na encomenda a quantidade de produto em stock */
        stock[idp].qtd+=encomendas[ide][idp];
        /* Altera a quantidade de produto na encomenda para 0 */
        encomendas[ide][idp]=0;
    }
}


/* Calcula o custo de uma encomenda */
void comando_C(){
    int idp,ide,custo_total=0;
    scanf("%d",&ide);

    if (ide>=total_enc) /* Erro caso nao exista nenhuma encomenda criada com esse identificador */
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
 
    else {
        for (idp=0;idp<total_prod;idp++) /* Percorre todos os produtos criados */
            custo_total+= stock[idp].preco * encomendas[ide][idp]; /* Adiciona ao custo total o preco de cada produto multiplicado pela sua quantidade na encomenda */

        printf("Custo da encomenda %d %d.\n",ide,custo_total);
    }
}


/* Altera o pre?o de um produto existente no sistema */
void comando_p(){
    int idp,preco;
    scanf("%d:%d",&idp,&preco);

    if (idp>=total_prod) /* Erro caso nao exista nenhum produto criado com esse identificador */
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);

    else
        stock[idp].preco=preco; /* Altera o preco do produto */
}


/* Retorna a descri??o e a quantidade de um produto numa dada encomenda */
void comando_E(){
    int idp,ide;
    scanf("%d:%d",&ide,&idp);  
    
    if (ide>=total_enc) /* Erro caso nao exista nenhuma encomedna criada com esse identificador */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
 
    else if (idp>=total_prod) /* Erro caso nao exista nenhum produto criado com esse identificador */
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp); 
 
    else
        printf("%s %d.\n",stock[idp].descr,encomendas[ide][idp]); 
}


/* Retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
void comando_m(){
    int idp,ide,maior;
    scanf("%d",&idp);

    if (idp>=total_prod) /* Erro caso nao exista nenhum produto criado com esse identificador */
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
 
    else {
        maior=0; /* guarda o ide da encomenda em que produto ocorre mais vezes */
        
        for (ide=1;ide<total_enc;ide++)  /* percorre todas as encomendas criadas */
            /* caso exista uma encomenda onde o produto ocorre mais vezes, entao a variavel 'maior' passa a ter o valor do ide dessa encomenda */
            if (encomendas[ide][idp]>encomendas[maior][idp])
                maior=ide;
           
        /* nao lista nada caso o produto nao exista em nenhuma encomenda ou nao existam encomendas */
        if (total_enc>0 && encomendas[maior][idp]>0) 
            printf("Maximo produto %d %d %d.\n",idp,maior,encomendas[maior][idp]);
    }
}


/* Devolve um vetor ordenado em v[left...right] dados dois vetors ordenados v[left...m] e v[m+1...right]*/
void merge(prod v[],int left,int m,int right,char comando){
    int i,j,k;
    prod aux[MAX_PROD];

    /* Copia v[left...m] para o vetor auxiliar*/
    for (i=m+1;i>left;i--) 
        aux[i-1]=v[i-1]; 

    /* Copia v[m+1...right] para o vetor auxiliar por ordem contraria*/
    for (j=m;j<right;j++) 
        aux[right+m-j]=v[j+1]; 

    /* Compara as duas metades do vetor auxiliar (comecando pelas pontas) e coloca-as no vetor v ordenadas */
    for (k=left; k<=right;k++){ 
        /* se o comando for 'l', ordena os produtos por preco. Se o comando for 'L',ordena por ordem alfabetica */
        if((comando=='l' && (aux[j].preco<aux[i].preco || (aux[j].preco==aux[i].preco && aux[j].idp<aux[i].idp))) || (comando=='L' && ordem_alfabetica(aux[j].descr,aux[i].descr)))
            v[k]=aux[j--];
        else
            v[k]=aux[i++];

    }
}


/* Ordena um vetor de produtos. A ordem depende do comando dado ('l' ou 'L') */
void mergesort(prod v[],int left,int right,char comando){
    int m = (right + left)/2; /* meio do vetor a ordenar*/

    if (right<=left) 
        return;

    mergesort(v,left,m,comando); /* ordena a primeria metade do vetor */
    mergesort(v,m+1,right,comando); /* ordena a segunda metade do vetor */
    merge(v,left,m,right,comando); /* junta as duas metades */
}


/* Lista todos os produtos existentes no sistema por ordem crescente de pre?o */
void comando_l(){
    int i;
    prod prod_ordenados[MAX_PROD]; /* Array que vai ser ordenado */

    /* Copia todos os produtos existentes em stock para o novo array */
    for (i=0;i<total_prod;i++)
        prod_ordenados[i]=stock[i];

    mergesort(prod_ordenados,0,total_prod-1,'l'); /* Ordena o novo array por ordem crescente de preco */

    /* Imprime os produtos ordenado */
    printf("Produtos\n");
    for (i=0;i<total_prod;i++)
        printf("* %s %d %d\n",prod_ordenados[i].descr,prod_ordenados[i].preco,prod_ordenados[i].qtd);
    
}


/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void comando_L(){
    int ide,i,j=0;
    prod enc_ordenada[200]; /* Array que vai ser ordenado */

    scanf("%d",&ide);

    if (ide>=total_enc) /* Erro caso nao existir nenhuma encomenda criada com esse identificador */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);

    else{
        /* Copia todos os produtos da encomenda e respetivas quantidades para o novo array */
        for (i=0;i<total_prod;i++){
            if (encomendas[ide][i]!=0){ /* verifica se o produto existe na encomenda */
                enc_ordenada[j]=stock[i]; /* copia o produto para o array */
                enc_ordenada[j].qtd=encomendas[ide][i]; /* copia a quantdade de produto na encomenda para o array */
                j++; 
            }
        } 
        mergesort(enc_ordenada,0,j-1,'L'); /* ordena o novo array por ordem alfabetica */

        /* Imprime os produtos ordenados */
        printf("Encomenda %d\n",ide);
        for (i=0;i<=j-1;i++)
            printf("* %s %d %d\n",enc_ordenada[i].descr,enc_ordenada[i].preco,enc_ordenada[i].qtd);
    
    }
}



int main(){
    char c; /* comando dado pelo utilizador */
    while ((c=getchar())!='x'){ /* repete o ciclo ate receber o comando x */
        switch (c){ 
            case 'a': 
                comando_a();
                break;
            case 'q':
                comando_q();
                break;
            case 'N':
                comando_N();
                break;
            case 'A':
                comando_A();
                break;
            case 'r':
                comando_r();
                break;
            case 'R':
                comando_R();
                break;
            case 'C':
                comando_C();
                break;
            case 'p':
                comando_p();
                break;
            case 'E':
                comando_E();
                break;
            case 'm':
                comando_m();
                break;
            case 'l':
                comando_l();
                break;
            case 'L':
                comando_L();
                break;
        }
        getchar(); /* Le o '\n' introduzido pelo utilizador */
    }
    return 0;
}