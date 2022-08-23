#include <stdio.h>
#include <string.h>
#define maxprod 10000
#define maxenc 500
#define maxchar 63
#define maxpeso 200

typedef struct produto{
    int idp;
    char desc[maxchar];
    int preco;
    int peso;
    int quantidade;
} produto;
typedef struct encomenda{
    produto produtos[maxprod];
    int peso;
} encomenda;
produto produtos[maxprod];
encomenda encomendas[maxenc];

/*Funcao que adiciona um produto ao sistema*/
void a(produto produtos[maxprod],int i){
    scanf("%[^:]:%d:%d:%d\n",produtos[i].desc,
    &produtos[i].preco,&produtos[i].peso,&produtos[i].quantidade);
    produtos[i].idp=i;
    printf("Novo produto %d.\n",produtos[i].idp);
}

/*Funcao que adiciona stock a um produto existente*/
void q(produto produtos[maxprod],int i){
    /*Uma variavel para armazenar id do produto e outra para a quantidade*/
    int id,qtd;
    scanf("%d:%d\n",&id,&qtd);
    if(id>=i){
        printf("Impossivel adicionar produto %d ao stock. "
        "Produto inexistente.\n",id);
    }
    else{
        produtos[id].quantidade+=qtd;
    }
}

/*Funcao que cria uma nova encomenda*/
void N(encomenda encomendas[maxenc],int e){
    scanf("\n");
    encomendas[e].peso=0;
    printf("Nova encomenda %d.\n",e);
}

/*Funcao que adiciona um produto a uma encomenda ou aumenta a quantidade
de um produto j? existente numa encomenda*/
void A(encomenda encomendas[maxenc],produto produtos[maxprod],int e,int i){
    /*Variaveis para armazenar o id da encomenda, o id do produto
    e a quantidade a adicionar,respetivamente*/
    int ide,id,qtd;
    scanf("%d:%d:%d\n",&ide,&id,&qtd);
    if(ide>=e){
        printf("Impossivel adicionar produto %d a encomenda %d. "
        "Encomenda inexistente.\n",id,ide);
    }
    else if(id>=i){
        printf("Impossivel adicionar produto %d a encomenda %d. "
        "Produto inexistente.\n",id,ide);
    }
    else if(qtd>produtos[id].quantidade){
        printf("Impossivel adicionar produto %d a encomenda %d. "
        "Quantidade em stock insuficiente.\n",id,ide);
    }
    else if((encomendas[ide].peso + (produtos[id].peso * qtd))>maxpeso){
        printf("Impossivel adicionar produto %d a encomenda %d. "
        "Peso da encomenda excede o maximo de 200.\n",id,ide);
    }
    else{
        produtos[id].quantidade-=qtd;
        encomendas[ide].peso+=(produtos[id].peso * qtd);
        encomendas[ide].produtos[id].idp=id;
        strcpy(encomendas[ide].produtos[id].desc, produtos[id].desc);
        encomendas[ide].produtos[id].preco=produtos[id].preco;
        encomendas[ide].produtos[id].peso=produtos[id].peso;
        if(encomendas[ide].produtos[id].quantidade>0){
            encomendas[ide].produtos[id].quantidade+=qtd;
        }
        else{
            encomendas[ide].produtos[id].quantidade=qtd;
        }
    }
}

/*Funcao que remove stock de um produto existente*/
void r(produto produtos[maxprod],int i){
    /*Variaveis, uma para armazenar o id do produto, uma a sua quantidade*/
    int id,qtd;
    scanf("%d:%d\n",&id,&qtd);
    if(id>=i){
        printf("Impossivel remover stock do produto %d. "
        "Produto inexistente.\n",id);
    }
    else if((produtos[id].quantidade - qtd)<0){
        printf("Impossivel remover %d unidades do produto %d do stock. "
        "Quantidade insuficiente.\n",qtd,id);
    }
    else{
        produtos[id].quantidade-=qtd;
    }
}

/*Funcao que remove um produto de uma encomenda*/
void R(encomenda encomendas[maxenc],produto produtos[maxprod],int e,int i){
    /*Variavel para armazenar o id da encomenda e outra o id do produto*/
    int ide,id;
    scanf("%d:%d\n",&ide,&id);
    if(ide>=e){
        printf("Impossivel remover produto %d a encomenda %d. "
        "Encomenda inexistente.\n",id,ide);
    }
    else if(id>=i){
        printf("Impossivel remover produto %d a encomenda %d. "
        "Produto inexistente.\n",id,ide);
    }
    else{
        produtos[id].quantidade+=encomendas[ide].produtos[id].quantidade;
        encomendas[ide].peso-=(encomendas[ide].produtos[id].peso *
        encomendas[ide].produtos[id].quantidade);
        encomendas[ide].produtos[id].peso=0;
        encomendas[ide].produtos[id].preco=0;
        encomendas[ide].produtos[id].quantidade=0;
    }
}

/*Funcao que calcula o custo de uma encomenda*/
void C(encomenda encomendas[maxenc],int e){
    /*Duas variaveis criadas em que uma armazena o id da encomenda
    e a outra cont?m o total do custo da encomenda*/
    int ide,custo=0,i;
    scanf("%d\n",&ide);
    if(ide>=e){
        printf("Impossivel calcular custo da encomenda %d. "
        "Encomenda inexistente.\n",ide);
    }
    else{
        for(i=0;i<maxprod;i++){
            custo+=(encomendas[ide].produtos[i].preco *
            encomendas[ide].produtos[i].quantidade);
        }
        printf("Custo da encomenda %d %d.\n",ide,custo);
    }
}

/*Funcao que altera o preco de um produto existente no sistema*/
void p(produto produtos[maxprod],encomenda encomendas[maxenc],int i){
    /*Variaveis para guardar o id do produto e o seu novo custo,respetivamente*/
    int id,custo,a;
    scanf("%d:%d\n",&id,&custo);
    if(id>=i){
        printf("Impossivel alterar preco do produto %d. "
        "Produto inexistente.\n",id);
    }
    else{
        produtos[id].preco=custo;
        for(a=0;a<maxenc;a++){
            if(encomendas[a].produtos[id].preco>0){
                encomendas[a].produtos[id].preco=custo;
            }
        }
    }
}

/*Funcao que lista a descricao e a quantidade de um produto numa encomenda*/
void E(encomenda encomendas[maxenc],produto produtos[maxprod],int e, int i){
    /*Variaveis usadas para armazenar o id da encomenda 
    e outra o id do produto*/
    int ide,id;
    scanf("%d:%d\n",&ide,&id);
    if(ide>=e){
        printf("Impossivel listar encomenda %d. "
        "Encomenda inexistente.\n",ide);
    }
    else if(id>=i){
        printf("Impossivel listar produto %d. "
        "Produto inexistente.\n",id);
    }
    else{
        printf("%s %d.\n",produtos[id].desc,
        encomendas[ide].produtos[id].quantidade);
    }
}

/*Funcao que lista o id da encomenda em que o produto dado ocorre mais vezes.
Se houver 2 ou mais encomendas nessa situacao, vai imprimir a encomenda 
de menor id*/
void m(encomenda encomendas[maxenc],int e,int i){
    /*Criada uma variavel (id) para armazenar o id do produto, 
    uma variavel (qtd[]) para armazenar as quantidades dos produtos nas 
    varias encomendas, uma variavel (ide[]) para armazenar os ids das
    encomendas em que o produro ocorre, uma variavel (menoride) 
    para armazenar a encomenda de menor id e uma variavel (maiorqtd) 
    para guardar a maior quantidade do produto nas encomendas*/
    int id,a,b,qtd[maxenc]={0},ide[maxenc]={0},menoride=0,maiorqtd=0,c=0;
    scanf("%d\n",&id);
    if(id>=i){
        printf("Impossivel listar maximo do produto %d. "
        "Produto inexistente.\n",id);
    }
    else if(e==0){
        ;
    }
    else{
        for(a=0;a<maxenc;a++){
            for(b=0;b<maxprod;b++){
                if(encomendas[a].produtos[b].idp==id){
                    ide[c]=a;
                    qtd[c]=encomendas[a].produtos[b].quantidade;
                    c++;
                    break;
                }
            }
        }
        for(a=0;a<maxenc;a++){
            if(qtd[a]>maiorqtd){
                maiorqtd=qtd[a];
                menoride=ide[a];
            }
            ide[a]=0;
            qtd[a]=0;
        }
        if(maiorqtd>0){
            printf("Maximo produto %d %d %d.\n",id,menoride,maiorqtd);
        }
        else{
            ;
        }
    }
}

/*Funcao que devolve um vetor ordenado a partir de dois vetores ordenados 
mais pequenos*/
void merge(int a[], int left, int m, int right){
    int i,j,k;
    int aux[maxprod];    /*Variavel auxiliar usada para armazenar valores*/
    for(i=m+1;i>left;i--){
        aux[i-1]=a[i-1];
    }
    for(j=m;j<right;j++){
        aux[right+m-j]=a[j+1];
    }
    for(k=left;k<=right;k++){
        if(aux[j]<aux[i] || i>m){
            a[k]=aux[j--];
        }
        else{
            a[k]=aux[i++];
        }
    }
}

/*Funcao que ordena os elementos de um vetor de inteiros*/
void mergesort(int a[], int left, int right){
    int m=(right+left)/2;
    if(right<=left){
        return;
    }
    mergesort(a,left,m);
    mergesort(a,m+1,right);
    merge(a,left,m,right);
}

/*Funcao que lista todos os produtos no sistema por ordem crescente de preco.
Se houver 2 ou mais produtos com o mesmo preco, a funcao imprime esses 
por ordem crescente de id de produto*/
void l(produto produtos[maxprod],int i){
    /*Variavel (precos[]) usada para armazenar os precos dos produtos;
    variavel (ids[]) usada para armazenar os ids dos produtos;
    variaveis (l) e (r) usadas como extremos do quicksort;
    variavel (contador) usada para determinar se um id de um produto 
    ja foi ou nao usado quando 2 ou mais tem o mesmo preco*/
    int precos[maxprod]={0},ids[maxprod]={0},a,j,k,contador,aux,l,r,c;
    contador=aux=l=r=c=0;
    scanf("\n");
    for(a=0;a<i;a++){
        if(produtos[a].preco > 0){
            precos[c]=produtos[a].preco;
            c++;
            r++;
        }
    }
    r--;
    mergesort(precos,l,r);
    printf("Produtos\n");
    r++;
    for(a=0;a<r;a++){
        for(j=0;j<i;j++){
            if(precos[a]==produtos[j].preco){
                if(a!=0 && precos[a]==precos[a-1]){
                    for(k=0;k<aux;k++){
                        if(produtos[j].idp==ids[k]){
                            contador++;
                            break;
                        }
                    }
                    if(contador==1){
                        contador=0;
                    }
                    else{
                        ids[aux]=produtos[j].idp;
                        aux++;
                        printf("* %s %d %d\n",produtos[j].desc,
                        precos[a],produtos[j].quantidade);
                        break;
                    }
                }
                else{
                    ids[aux]=produtos[j].idp;
                    aux++;
                    printf("* %s %d %d\n",produtos[j].desc,
                    precos[a],produtos[j].quantidade);
                    break;
                }
            }
        }
    }
}

/*Funcao que devolve um vetor ordenado a partir de dois vetores ordenados 
mais pequenos*/
void merge2(char a[][maxchar], int left, int m, int right){
    int i,j,k;
    char aux[maxprod][maxchar];
    for(i=m+1;i>left;i--){
        strcpy(aux[i-1],a[i-1]);
    }
    for(j=m;j<right;j++){
        strcpy(aux[right+m-j],a[j+1]);
    }
    for(k=left;k<=right;k++){
        if(strcmp(aux[j],aux[i])<0 || i>m){
            strcpy(a[k],aux[j--]);
        }
        else{
            strcpy(a[k],aux[i++]);
        }
    }
}

/*Funcao que ordena os elementos de um vetor de strings*/
void mergesort2(char a[][maxchar], int left, int right){
    int m=(right+left)/2;
    if(right<=left){
        return;
    }
    mergesort2(a,left,m);
    mergesort2(a,m+1,right);
    merge2(a,left,m,right);
}

/*Funcao que lista todos os produtos de uma encomenda 
por ordem alfabetica de descricao*/
void L(encomenda encomendas[maxenc],int e){
    /*Variavel criada para armazenar o id da encomenda, outra (l) para 
    indicar o elemento onde comeca o quicksort e outra (r) para indicar 
    o elemento final*/
    int ide,i,a,aux=0,l=0,r=0;
    char desc[maxprod][maxchar];
    scanf("%d\n",&ide);
    if(ide>=e){
        printf("Impossivel listar encomenda %d. "
        "Encomenda inexistente.\n",ide);
    }
    else{
        printf("Encomenda %d\n",ide);
        for(i=0;i<maxprod;i++){
            if(encomendas[ide].produtos[i].quantidade>0){
                strcpy(desc[aux],encomendas[ide].produtos[i].desc);
                aux++;
                r++;
            }
        }
        r--;
        mergesort2(desc,l,r);
        for(i=0;i<aux;i++){
            for(a=0;a<maxprod;a++){
                if(strcmp(desc[i],encomendas[ide].produtos[a].desc)==0){
                    printf("* %s %d %d\n",desc[i],
                    encomendas[ide].produtos[a].preco,
                    encomendas[ide].produtos[a].quantidade);
                    break;
                }
            }
        }
    }
}

/*Funcao principal que inicializa o peso das encomendas a 0 e que 
le o caracter no inicio de cada linha do input para escolher que comando 
devera executar*/
int main(){
    /*Variavel (i) criada para contar quantos produtos ja foram criados e 
    comparar com os ids nas funcoes de modo a dar erros quando necessario; 
    variavel (e) criada com o mesmo efeito que a 'i' mas para encomendas;
    variavel (c) criada para armazenar o caracter no inicio de cada 
    linha do input*/
    int i=0,e=0,b,c;
    c=getchar();
    for(b=0;b<maxenc;b++){
        encomendas[b].peso=0;
    }
    while(c!=EOF && c!='\n'){
        if(c=='a'){
            getchar();
            a(produtos,i);
            i++;
        }
        if(c=='q'){
            getchar();
            q(produtos,i);
        }
        if(c=='N'){
            N(encomendas,e);
            e++;
        }
        if(c=='A'){
            getchar();
            A(encomendas,produtos,e,i);
        }
        if(c=='r'){
            getchar();
            r(produtos,i);
        }
        if(c=='R'){
            getchar();
            R(encomendas,produtos,e,i);
        }
        if(c=='C'){
            getchar();
            C(encomendas,e);
        }
        if(c=='p'){
            getchar();
            p(produtos,encomendas,i);
        }
        if(c=='E'){
            getchar();
            E(encomendas,produtos,e,i);
        }
        if(c=='m'){
            getchar();
            m(encomendas,e,i);
        }
        if(c=='l'){
            l(produtos,i);
        }
        if(c=='L'){
            getchar();
            L(encomendas,e);
        }
        /*usado para terminar o programa*/
        if(c=='x'){
            break;
        }
        c=getchar();
    }
    return 0;
}