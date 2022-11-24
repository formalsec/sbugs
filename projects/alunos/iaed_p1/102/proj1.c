#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAXDES 63
#define MAXPROD 10000
#define MAXENCO 500
#define PESOMAX 200

/*variaveis globais*/
/*dim_prod e a variavel que guarda quantos produtos estao no sistema*/
/*dim_enc e a variavel que guarda quantas encomendas estao no sistema*/
int dim_prod,dim_enc;

typedef struct produto{
    int idt;
    char des[MAXDES];
    int preco;
    int peso;
    int qtd;
}produto;

typedef struct encomenda{
    int idt;
    int peso;
    int prod_idt[PESOMAX];
    int prod_qtd[PESOMAX];
    int len;
}encomenda;

/*funcoes auxiliares*/
/*funcao que ordena todos os produtos numa encomenda com o algoritmo insertionsort*/
void insertion(produto vetor[],int left, int right){
    int i,j;
    for (i = left+1; i <= right; i++) {
        /*uso uma variavel auxiliar que guarda o valor de preco,qtd e descricao vetor[i]*/
        produto v; 
        strcpy(v.des,vetor[i].des);
        v.preco=vetor[i].preco;
        v.qtd=vetor[i].qtd;
        j = i-1;
        /*j percorre o vetor a partir da posicao i-1 ate encontrar um elemento cuja descricao seja menor
        por ordem alfabetica que a descricao do vetor v*/
        while ( j >= left && strcmp(v.des,vetor[j].des)<0) {
            /*enquanto strcmp(v.des,vetor[j].des)<0 puxa-se os valores para a direita*/
            strcpy(vetor[j+1].des,vetor[j].des);
            vetor[j+1].preco=vetor[j].preco;
            vetor[j+1].qtd=vetor[j].qtd;
            j--;
        }
        /*quando terminar o ciclo significa que encontrou o slot*/
        vetor[j+1].preco = v.preco;
        strcpy(vetor[j+1].des,v.des);
        vetor[j+1].qtd=v.qtd;
    }
}

/*funcao que devolve um vetor ordenado vetor[left..right] dados dois vetores ordenados em vetor[left..m]
e vetor[m+1..right]*/
void merge(produto vetor[], int left, int m, int right){
    int i, j, k;
    int n1=m-left+1;
    int n2=right-m;
    /*cria vetores auxiliares*/
    produto Left[MAXPROD],Right[MAXPROD];
    /*copia os a descricao,preco e qtd para os vetores auxiliares*/ 
    for (i = 0; i < n1; i++){
        strcpy(Left[i].des,vetor[left+i].des);
        Left[i].preco=vetor[left+i].preco;
        Left[i].qtd = vetor[left+i].qtd;
    }
    for (j = 0; j < n2; j++){
        strcpy(Right[j].des,vetor[m+1+j].des);
        Right[j].preco=vetor[m+1+j].preco;
        Right[j].qtd = vetor[m+1+j].qtd;
    }
 
    i=0;
    j=0;
    k=left;
    /* junta os vetores auxiliares no vetor[l..r]*/
    while (i < n1 && j < n2) 
    { 
        if (Left[i].preco <= Right[j].preco) 
        { 
            strcpy(vetor[k].des,Left[i].des);
            vetor[k].preco=Left[i].preco;
            vetor[k].qtd=Left[i].qtd; 
            i++; 
        } 
        else
        { 
            strcpy(vetor[k].des,Right[j].des);
            vetor[k].preco=Right[j].preco;
            vetor[k].qtd=Right[j].qtd;
            j++; 
        } 
        k++; 
    } 
    /* Copia os elementos restantes de Left[], se existirem */
    while (i < n1) 
    { 
        strcpy(vetor[k].des,Left[i].des);
        vetor[k].preco=Left[i].preco;
        vetor[k].qtd=Left[i].qtd;
        i++; 
        k++; 
    } 
    /* Copia os elementos restantes de Left[], se existirem */
    while (j < n2) 
    { 
        strcpy(vetor[k].des,Right[j].des);
        vetor[k].preco=Right[j].preco;
        vetor[k].qtd=Right[j].qtd;
        j++; 
        k++; 
    } 
}
/*funcao recursiva que ordena todos os produtos do sistema por preco atraves do
algoritmo meergesort*/
void mergesort(produto vetor[], int left, int right) {
    int m = (right+left)/2;
    if (right <= left)
        return;
    mergesort(vetor, left, m);
    mergesort(vetor, m+1, right);
    merge(vetor, left, m, right);
}

/*funcao que procura o indice da encomenda no sistema atraves do seu identificador*/
int procura_enc(int ide,encomenda vetor_enc[]){
    int i;
    for(i=0;i<dim_enc;i++){
        if (vetor_enc[i].idt==ide){
            break;
        }
    }
    return i;
}

/*funcao que procura o indice do produto no sistema atraves do seu identificador*/
int procura_prod(int idp,produto vetor_prod[]){
    int a;
    for(a=0;a<dim_prod;a++){
        if(vetor_prod[a].idt==idp){
            break;
        }
    }
    return a;
}

void a(produto vetor_prod[]);

void q(produto vetor_prod[]);

void N(encomenda vetor_enc[]);

void A(encomenda vetor_enc[],produto vetor_prod[]);

void r(produto vetor_prod[]);

void R(encomenda vetor_enc[],produto vetor_prod[]);

void C(encomenda vetor_enc[],produto vetor_prod[]);

void p(produto vetor_prod[]);

void E(encomenda vetor_enc[],produto vetor_prod[]);

void m(encomenda vetor_enc[],produto vetor_prod[]);

void l(produto vetor_prod[]);

void L(encomenda vetor_enc[],produto vetor_prod[]);

int main(){
    produto sistema_prod[MAXPROD];
    encomenda sistema_enc[MAXENCO];
    char c;
    c=getchar();
    while(c!='x'){
        switch(c){
            case 'a':
                a(sistema_prod);
                break;
            case 'q':
                q(sistema_prod);
                break;
            case 'N':
                N(sistema_enc);
                break;
            case 'A':
                A(sistema_enc,sistema_prod);
                break;
            case 'r':
                r(sistema_prod);
                break;
            case 'R':
                R(sistema_enc,sistema_prod);
                break;
            case 'C':
                C(sistema_enc,sistema_prod);
                break;
            case 'p':
                p(sistema_prod);
                break;
            case 'E':
                E(sistema_enc,sistema_prod);
                break;
            case 'm':
                m(sistema_enc,sistema_prod);
                break;
            case 'l':
                l(sistema_prod);
                break;
            case 'L':
                L(sistema_enc,sistema_prod);
                break;
        }
        c=getchar();
    }
    return 0;
}

/*funcao que cria um novo produto*/
void a(produto vetor_prod[]){
    produto p1;
    scanf(" %[^:]:%d:%d:%d",p1.des,&p1.preco,&p1.peso,&p1.qtd);
    p1.idt = dim_prod;
    vetor_prod[dim_prod]=p1;
    printf("Novo produto %d.\n",p1.idt);
    /*adiciona um a variavel global dos produtos*/
    dim_prod = dim_prod +1;
}

/*adiciona stock a um produto existente*/
void q(produto vetor_prod[]){
    int idp, qtd,i;
    scanf("%d:%d",&idp,&qtd);
    i=procura_prod(idp,vetor_prod);
    if(i==dim_prod){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return;
    }
    vetor_prod[i].qtd+=qtd;
}

/*cria uma nova encomenda*/
void N(encomenda vetor_enc[]){
    encomenda e1;
    int i;
    e1.idt = dim_enc;
    e1.peso=0;
    e1.len=0;
    /*coloca todos os identificadores a -1 de modo a nao confundir com outros identificadores*/
    for(i=0;i<PESOMAX;i++){
        e1.prod_idt[i]=-1;
        e1.prod_qtd[i]=0;
    }
    vetor_enc[dim_enc]=e1;
    printf("Nova encomenda %d.\n",e1.idt);
    /*adiciona um a variavel global das encomendas*/
    dim_enc = dim_enc +1;
}

/*adiciona um produto a uma encomenda*/
void A(encomenda vetor_enc[],produto vetor_prod[]){
    int ide,idp,qtd,i,a,j,peso,var_controlo;
    scanf("%d:%d:%d",&ide,&idp,&qtd);
    a=procura_enc(ide,vetor_enc);
    if(a==dim_enc){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
        return;
    }
    peso=vetor_enc[a].peso;
    i=procura_prod(idp,vetor_prod);
    if(i==dim_prod){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        return;
    }
    if(vetor_prod[i].qtd-qtd<0){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
        return;
    }
    var_controlo=0;
    /*se o produto existir na encomenda e nao exceder o peso maximo adiciona a quantidade a encomenda*/
    for(j=0;j<vetor_enc[a].len;j++){
        if(vetor_enc[a].prod_idt[j]==idp){
            var_controlo=1;
            if((vetor_enc[a].peso+vetor_prod[i].peso*qtd)<=PESOMAX){
                vetor_enc[a].peso+=vetor_prod[i].peso*qtd;
                vetor_enc[a].prod_qtd[j]+=qtd;
                vetor_prod[i].qtd=vetor_prod[i].qtd-qtd;
                break;
            }
            else{
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
                return;
            }
        }
    }
    /*se o produto nao existir na encomenda e nao exceder o peso maximo coloca o novo produto na encomenda*/
    if(var_controlo==0 && peso==vetor_enc[a].peso && (vetor_enc[a].peso+vetor_prod[i].peso*qtd)<=PESOMAX){
            vetor_enc[a].peso+=vetor_prod[i].peso*qtd;
            vetor_enc[a].prod_idt[j]=idp;
            vetor_enc[a].prod_qtd[j]=qtd;
            vetor_enc[a].len+=1;
            vetor_prod[i].qtd=vetor_prod[i].qtd-qtd;
    }
    else if(var_controlo==0 && (vetor_enc[a].peso+vetor_prod[i].peso*qtd)>PESOMAX){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
    }
}

/*remove stock a um produto existente*/
void r(produto vetor_prod[]){
    int qtd,idp,i;
    scanf("%d:%d",&idp,&qtd);
    i=procura_prod(idp,vetor_prod);
    if(i==dim_prod){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
        return;
    }
    /*se existir stock suficiente remove stock*/
    if(vetor_prod[i].qtd-qtd>=0){
        vetor_prod[i].qtd=vetor_prod[i].qtd-qtd;
    }
    else{
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
        return;
    }
}

/*remove um produto de uma encomenda*/
void R(encomenda vetor_enc[],produto vetor_prod[]){
    int ide,idp,i,a,j;
    scanf("%d:%d",&ide,&idp);
    i=procura_enc(ide,vetor_enc);
    if(i==dim_enc){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
        return;
    }
    j=procura_prod(idp,vetor_prod);
    if(j==dim_prod){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        return;
    }
    /*encontra o produto na encomenda e remove-o*/
    for(a=0;a<vetor_enc[i].len;a++){
        if(vetor_enc[i].prod_idt[a]==idp){
            vetor_prod[j].qtd+=vetor_enc[i].prod_qtd[a];
            vetor_enc[i].peso=vetor_enc[i].peso-vetor_prod[j].peso*vetor_enc[i].prod_qtd[a];
            /*ciclo que a partir do indice do produto que se quer eliminar recua um de modo a eliminar
            o produto da encomenda*/
            for(j=a;j<vetor_enc[i].len;j++){
                vetor_enc[i].prod_idt[j]=vetor_enc[i].prod_idt[j+1];
                vetor_enc[i].prod_qtd[j]=vetor_enc[i].prod_qtd[j+1];
            }
            vetor_enc[i].len=vetor_enc[i].len-1;
            break;
        }
    }
}

/*calcula o custo de uma encomenda*/
void C(encomenda vetor_enc[],produto vetor_prod[]){
    int ide,total,i,j,a;
    total=0;
    scanf("%d",&ide);
    i=procura_enc(ide,vetor_enc);
    if(i==dim_enc){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }
    /*ciclo que percorre a encomenda e sucessivamente o sistema dos produtos de modo
    a encontrar o preco do produto*/
    for(j=0;j<vetor_enc[i].len;j++){
        for(a=0;a<dim_prod;a++){
            if(vetor_enc[i].prod_idt[j]==vetor_prod[a].idt){
                total=total+vetor_prod[a].preco*vetor_enc[i].prod_qtd[j];
            }
        }
    }
    printf("Custo da encomenda %d %d.\n",ide,total);
}

/*altera o preco de um produto existente no sistema*/
void p(produto vetor_prod[]){
    int idp,preco,i;
    scanf("%d:%d",&idp,&preco);
    i=procura_prod(idp,vetor_prod);
    if (i==dim_prod){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
        return;
    }
    vetor_prod[i].preco=preco;
}

/*lista a descricao e a quantidade de um produto numa encomenda */
void E(encomenda vetor_enc[],produto vetor_prod[]){
    int ide,idp,i,j,a;
    scanf("%d:%d",&ide,&idp);
    i=procura_enc(ide,vetor_enc);
    if(i==dim_enc){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }
    a=procura_prod(idp,vetor_prod);
    if(a==dim_prod){
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
        return;
    }
    /*encontra o produto na encomenda e lista-o*/
    for(j=0;j<vetor_enc[i].len;j++){
        if(vetor_enc[i].prod_idt[j]==idp){
            printf("%s %d.\n",vetor_prod[a].des,vetor_enc[i].prod_qtd[j]);
            break;
        }
    }
    /*se nao existir na encomenda print quantidade 0*/
    if(j==vetor_enc[i].len){
        printf("%s 0.\n",vetor_prod[a].des);
    }
}

/*lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
void m(encomenda vetor_enc[],produto vetor_prod[]){
    int idp,enc_max,qtd_max,i,j,a;
    enc_max=-1;
    qtd_max=0;
    scanf("%d",&idp);
    a=procura_prod(idp,vetor_prod);
    if(a==dim_prod){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
        return;
    }
    /*encontra o produto no sistema e sucessivamente na encomenda e atraves das variaveis
    enc_max e qtd_max encontra a encomenda onde o produto ocorre mais vezes*/
    for(i=0;i<dim_enc;i++){
        for(j=0;j<vetor_enc[i].len;j++){
            if(vetor_enc[i].prod_idt[j]==idp){
                if(vetor_enc[i].prod_qtd[j]>qtd_max){
                    qtd_max=vetor_enc[i].prod_qtd[j];
                    enc_max=vetor_enc[i].idt;
                    break;
                }
                else if(vetor_enc[i].prod_qtd[j]==qtd_max && enc_max>vetor_enc[i].idt){
                    enc_max=vetor_enc[i].idt;
                    break;
                }
            }
        }
    }
    if(enc_max!=-1){
        printf("Maximo produto %d %d %d.\n",idp,enc_max,qtd_max);
    }
}

/*lista todos os produtos existentes no sistema por ordem crescente de pre?o*/
void l(produto vetor_prod[]){
    int j,i;
    produto vetor[MAXPROD];
    /*copia a descricao,preco e quantidade de todos os produtos para um novo vetor*/
    for(i=0;i<dim_prod;i++){
        strcpy(vetor[i].des,vetor_prod[i].des);
        vetor[i].preco=vetor_prod[i].preco;
        vetor[i].qtd=vetor_prod[i].qtd;
    }
    /*chama a funcao para ordenar este vetor por preco*/
    mergesort(vetor,0,dim_prod-1);
    printf("Produtos\n");
    for(j=0;j<dim_prod;j++){
        printf("* %s %d %d\n",vetor[j].des,vetor[j].preco,vetor[j].qtd);
    }
}

/*lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
void L(encomenda vetor_enc[],produto vetor_prod[]){
    int ide,i,j,a,b;
    scanf("%d",&ide);
    i=procura_enc(ide,vetor_enc);
    if(i==dim_enc){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }
    else{
        produto vetor[PESOMAX];
        /*copia a descricao,preco e quantidade dos produtos da encomenda para um novo vetor*/
        for(j=0;j<vetor_enc[i].len;j++){
            for(a=0;a<dim_prod;a++){
                if(vetor_enc[i].prod_idt[j]==vetor_prod[a].idt){
                    strcpy(vetor[j].des,vetor_prod[a].des);
                    vetor[j].preco=vetor_prod[a].preco;
                    vetor[j].qtd=vetor_enc[i].prod_qtd[j];
                }
            }
        }
        /*chama a funcao para ordenar este vetor por ordem alfabetica*/
        insertion(vetor,0,vetor_enc[i].len-1);
        printf("Encomenda %d\n",ide);
        for(b=0;b<vetor_enc[i].len;b++){
            printf("* %s %d %d\n",vetor[b].des,vetor[b].preco,vetor[b].qtd);
        }
    }
}