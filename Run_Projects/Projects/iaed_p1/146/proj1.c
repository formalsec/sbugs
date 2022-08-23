#include <stdio.h>
#include <string.h>

/* Valor m?ximo de produtos diferentes */
#define MAX_PRODUTO 10000
/* Valor m?ximo de encomendas */
#define MAX_ENCOMENDAS 500
/* Valor m?ximo de produtos dentro de uma encomenda */
#define MAX_ENC_PRODUTOS 200
/* N?mero m?ximo de caracteres da descri??o do produto */
#define MAX_CHAR_DESCRICAO 63
/* Valor que permite a fun??o de ordena??o segundo o pre?o do produto */
#define PRECO 0
/* Valor que permite a fun??o de ordena??o segundo a descro??o do produto*/
#define DESCRICAO 1

/* Defini??o de estruturas */
/* Estrutura Produto */
typedef struct {
    int idp;    
    char descricao[MAX_CHAR_DESCRICAO+1];
    int preco;
    int peso;
    int quantidade;
}produto;

/* Estrutura Encomenda */
typedef struct {
    int ide;
    produto produto[MAX_ENC_PRODUTOS];
}encomenda;

typedef produto Item;

/* Vari?vies globais */

/* Vetor onde guarda todos os produtos do sistema */
produto sistema[MAX_PRODUTO];
/* Vetor onde guarda todas as encomendas */
encomenda portofolio[MAX_ENCOMENDAS];
/* Vari?vel que conta o n?mero de produtos no sistema */
int n_produtos=0;
/* Vari?vel que conta o n?mero de encomendas */
int n_encomendas=0;

/* Prototipos das Fun??es */
void ini_produtos(produto tab[],int dim);
void ini_encomendas(encomenda tab[],int dim);
void adiciona_novo_produto(char desc[],int preco,int peso, int qtd);
void adiciona_stock(int idp, int qtd);
void cria_nova_encomenda();
void adiciona_produto_encomenda(int ide,int idp,int qtd);
void remove_stock(int idp, int qtd);
void remove_produto_encomenda(int ide,int idp);
void calcula_custo(int ide);
void altera_preco(int idp, int preco);
void lista_descricao_quantidade_produto(int ide,int idp);
void lista_identificador_encomenda(int idp);
void lista_produto_sistema();
void lista_produto_encomenda(int ide);
void mergesort(Item arr[],int l, int r,int componente);
void merge(Item a[],int left, int m, int right, int componente);
void k();
void K(int ide);

/* Fun??o principal
 * Recebe um comando e os argumentos (se houver), e faz o que a a??o que
 * est? definida para o comando
*/
int main(){
    int input;

    char desc[MAX_CHAR_DESCRICAO+1];
    int preco,peso,qtd,idp,ide;

    /* Inicializa??o dos vetores */
    ini_produtos(sistema,MAX_PRODUTO);
    ini_encomendas(portofolio,MAX_ENCOMENDAS);

    while ((input=getchar())!='x'){
        
        /* Identifica o comando e faz a a??o */
        switch (input){
            case 'a':
                scanf(" %[^:]:%d:%d:%d", desc, &preco, &peso, &qtd);
                adiciona_novo_produto(desc,preco,peso,qtd);
                break;
            case 'q':
                scanf(" %d:%d", &idp, &qtd);
                adiciona_stock(idp,qtd);
                break;
            case 'N':
                cria_nova_encomenda();
                break;
            case 'A':
                scanf(" %d:%d:%d", &ide, &idp, &qtd);
                adiciona_produto_encomenda(ide,idp,qtd);
                break;
            case 'r':
                scanf(" %d:%d", &idp, &qtd);
                remove_stock(idp,qtd);
                break;
            case 'R':
                scanf(" %d:%d", &ide, &idp);
                remove_produto_encomenda(ide,idp);
                break;
            case 'C':
                scanf(" %d",&ide);
                calcula_custo(ide);
                break;
            case 'p':
                scanf(" %d:%d", &idp, &preco);
                altera_preco(idp,preco);
                break;
            case 'E':
                scanf(" %d:%d", &ide, &idp);
                lista_descricao_quantidade_produto(ide,idp);
                break;
            case 'm':
                scanf(" %d", &idp);
                lista_identificador_encomenda(idp);
                break;
            case 'l':
                lista_produto_sistema();
                break;
            case 'L':
                scanf(" %d", &ide);
                lista_produto_encomenda(ide);
                break;
        }
        getchar();  /*le o '\n' introduzido pelo utilizador*/
    }
    return 0;
}

/* Implementacao das Funcoes */

/* Inicializa o vetor do tipo produto a -1 (vazio) */
void ini_produtos(produto tab[],int dim){
    int i;

    for(i=0;i<dim;i++){
        tab[i].idp=-1;
    }
}

/* Inicializa o vetor do tipo encomenda a -1(vazio) */
void ini_encomendas(encomenda tab[],int dim){
    int i;

    for (i=0;i<dim;i++){
        tab[i].ide=-1;
    }
}

/* (Comando a) Adiciona um novo produto ao sistena */
void adiciona_novo_produto(char desc[MAX_CHAR_DESCRICAO+1],int preco,int peso, int qtd){
    sistema[n_produtos].idp=n_produtos;
    sistema[n_produtos].preco=preco;
    sistema[n_produtos].quantidade=qtd;
    sistema[n_produtos].peso=peso;
    strcpy(sistema[n_produtos].descricao,desc);
    printf("Novo produto %d.\n",n_produtos);
    n_produtos++;
}

/* (Comando q) Adiciona stock a um produto existente no sistema */
void adiciona_stock(int idp, int qtd){
    if (sistema[idp].idp==-1){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
    }else{
        sistema[idp].quantidade+=qtd;
    }
}

/* (Comando N) Cria uma nova encomenda */
void cria_nova_encomenda(){
    portofolio[n_encomendas].ide=n_encomendas;
    ini_produtos(portofolio[n_encomendas].produto,MAX_ENC_PRODUTOS);
    printf("Nova encomenda %d.\n",n_encomendas);
    n_encomendas++;
}

/* (Comando A) Adiciona um produto a uma encomenda */
void adiciona_produto_encomenda(int ide,int idp,int qtd){
    int i=0,k=1;
    int stock,qtd_encomenda,peso_total=0;

    if (portofolio[ide].ide==-1){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    }else if(sistema[idp].idp==-1){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    }else{
        stock=sistema[idp].quantidade;
        qtd_encomenda=stock-qtd;
        if(qtd_encomenda<0){
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
        }else{
            /* Calculo do peso da encomenda */
            for(i=0;i<MAX_ENC_PRODUTOS;i++){
                if(portofolio[ide].produto[i].idp!=-1){
                    peso_total+=(portofolio[ide].produto[i].peso*portofolio[ide].produto[i].quantidade);
                }
            }
            peso_total=peso_total+(sistema[idp].peso*qtd);
            if(peso_total>MAX_ENC_PRODUTOS){
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
            }else{
                /* Situa??o onde o produto j? foi adicionado ? encomenda */
                for(i=0;i<MAX_ENC_PRODUTOS;i++){
                    if(portofolio[ide].produto[i].idp==idp){
                        portofolio[ide].produto[i].quantidade+=qtd;
                        k=0;
                        break;
                    }
                }
                /* Situa??o onde o produto ainda n?o foi adicionado ? encomenda */
                if(k){
                    for(i=0;i<MAX_ENC_PRODUTOS;i++){
                        if(portofolio[ide].produto[i].idp==-1){
                            portofolio[ide].produto[i].idp=sistema[idp].idp;
                            portofolio[ide].produto[i].peso=sistema[idp].peso;
                            portofolio[ide].produto[i].preco=sistema[idp].preco;
                            strcpy(portofolio[ide].produto[i].descricao,sistema[idp].descricao);                        
                            portofolio[ide].produto[i].quantidade=qtd;
                            break;
                        }
                    }
                }
                sistema[idp].quantidade=qtd_encomenda;
            }
        }
    }
}

/* (Comando r) Remove stock a um produto existente */
void remove_stock(int idp, int qtd){
    if(sistema[idp].idp==-1){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }else if((sistema[idp].quantidade-qtd)<0){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
    }else{
        sistema[idp].quantidade-=qtd;
    }
}

/* (Comando R) Remove um produto de uma encomenda */
void remove_produto_encomenda(int ide,int idp){
    int i;
    if(portofolio[ide].ide==-1){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    }else if(sistema[idp].idp==-1){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    }else{
        for(i=0;i<MAX_ENC_PRODUTOS;i++){
            if(portofolio[ide].produto[i].idp==idp){
                sistema[idp].quantidade+=portofolio[ide].produto[i].quantidade;
                portofolio[ide].produto[i].idp=-1;
                break;
            }
        }
    }
}

/* (Comando C) Calcula o custo de uma encomenda */
void calcula_custo(int ide){
    int i,custo=0;
    if(portofolio[ide].ide==-1){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    }else{
        for(i=0;i<MAX_ENC_PRODUTOS;i++){
            if(portofolio[ide].produto[i].idp!=-1){
                custo=custo + (portofolio[ide].produto[i].preco*portofolio[ide].produto[i].quantidade);
            }
        }
        printf("Custo da encomenda %d %d.\n",ide,custo);
    }
}

/* (Comando p) Altera o pre?o de um produto existente no sistema */
void altera_preco(int idp, int preco){
    int i,j;

    if(sistema[idp].idp==-1){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    }else{
        /* Altera??o no sistema */
        sistema[idp].preco=preco;
        /* Altera??o nas encomendas */
        for(i=0;i<n_encomendas;i++){
            for(j=0;j<MAX_ENC_PRODUTOS;j++){
                if(portofolio[i].produto[j].idp==idp){
                    portofolio[i].produto[j].preco=preco;
                }
            }
        }
    }
    
}

/* (Comando E) Lista a descri??o e a quantidade de um produto numa encomenda */
void lista_descricao_quantidade_produto(int ide, int idp){
    int i;
    if(portofolio[ide].ide==-1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    }else if(sistema[idp].idp==-1){
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
    }else{
        /* Situa??o onde o produto existe na encomenda */
        for(i=0;i<MAX_ENC_PRODUTOS;i++){
            if(portofolio[ide].produto[i].idp==idp){
                printf("%s %d.\n",sistema[idp].descricao,portofolio[ide].produto[i].quantidade);
                break;
            }
        }
        /* Situa??o onde o produto n?o existe na encomenda */
        if(i==MAX_ENC_PRODUTOS){
            printf("%s 0.\n",sistema[idp].descricao);
        }
    }
}

/* (Comando m) Lista o identificador da encomenda em que o produto ocorre mais vezes */
void lista_identificador_encomenda(int idp){
    int prod_maior_qtd=0,ide_maior=-1;
    int i,j;
    if(sistema[idp].idp==-1){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    }else{
        for(i=0;i<n_encomendas;i++){
            for(j=0;j<MAX_ENC_PRODUTOS;j++){
                if(portofolio[i].produto[j].idp==idp){
                    if(portofolio[i].produto[j].quantidade>prod_maior_qtd){
                        prod_maior_qtd=portofolio[i].produto[j].quantidade;
                        ide_maior=i;
                    }
                }
            }
        }
        if(ide_maior!=-1){
            printf("Maximo produto %d %d %d.\n",idp,ide_maior,prod_maior_qtd);
        }
    }
}

/* (Comando l) Lista todos os produtos existentes no sistema por ordem crescente de pre?o */
void lista_produto_sistema(){
    int i;
    produto aux_sistema[MAX_PRODUTO];
    /* Copia do vetor dos produtos */ 
    for(i=0;i<n_produtos;i++){
        aux_sistema[i]=sistema[i];
    }
    /* Ordena??o do vetor por ordem crescente do peso */
    mergesort(aux_sistema,0,n_produtos-1,PRECO);

    printf("Produtos\n");
    for(i=0;i<n_produtos;i++){
        printf("* %s %d %d\n",aux_sistema[i].descricao,aux_sistema[i].preco,aux_sistema[i].quantidade);
    }

}

/* (Comando L) Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o*/
void lista_produto_encomenda(int ide){
    int i,j=0;
    int n_enc_produtos=0;
    encomenda encomenda;
    if(portofolio[ide].ide==-1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    }else{
        /* Copia da encomenda e do vetor dos produtos na encomenda */
        encomenda.ide=portofolio[ide].ide;
        ini_produtos(encomenda.produto,MAX_ENC_PRODUTOS);
        for(i=0;i<MAX_ENC_PRODUTOS;i++){
            if(portofolio[ide].produto[i].idp!=-1){
                encomenda.produto[j]=portofolio[ide].produto[i];
                j++;
                n_enc_produtos++;
            }
        }
        /* Ordena??o do vetor por ordem alfab?tica */
        mergesort(encomenda.produto,0,n_enc_produtos-1,DESCRICAO);
        
        printf("Encomenda %d\n",ide);
        for(i=0;i<n_enc_produtos;i++){
            if(encomenda.produto[i].idp!=-1){
                printf("* %s %d %d\n",encomenda.produto[i].descricao,encomenda.produto[i].preco,encomenda.produto[i].quantidade);
            }
        }
    }
}

/* Algoritmo de ordena??o - MergeSort 
 * A vari?vel componente decide a componenete que a ordena??o vai utilizar
 * como metodo de compara??o,por exemplo, se componente for igual a PRECO ent?o
 * ordena por ordem crescente de preco
*/
void mergesort(Item arr[],int l, int r, int componente){
    if(l<r){
        int m=l+(r-l)/2;
        mergesort(arr,l,m,componente);
        mergesort(arr,m+1,r,componente);
        merge(arr,l,m,r,componente);
    }
}

/* Fun??o auxiliar do algoritmo de ordena??o - MergeSort */
void merge(Item a[],int left, int m, int right, int componente){
    int i,j,k;
    int n1= m-left+1;
    int n2= right-m;

    /* Vetores auxiliares */
    Item L[MAX_PRODUTO],R[MAX_PRODUTO];
    /* Copia dos dados para os vetores auxiliares */
    for(i=0;i<n1;i++){
        L[i]=a[left+i];
    }
    for(j=0;j<n2;j++){
        R[j]=a[m+1+j];    
    }
    
    /* Junta os vetores auxiliares para o vetor original  por ordem */
    i=0;
    j=0;
    k=left;
    /* Identifica a ordem que deve fazer */
    switch (componente){
    case PRECO:
        while(i<n1 && j<n2){
            if(L[i].preco<= R[j].preco){
                a[k]=L[i++];
            }else{
                a[k]=R[j++];
            }
            k++;
        }
        break;
    case DESCRICAO:
        while(i<n1 && j<n2){
            if(strcmp(L[i].descricao,R[j].descricao)<0){
                a[k]=L[i++];
            }else{
                a[k]=R[j++];
            }
            k++;
        }
        break;
    }
    
    /* Copia os restantes elementos do vetor L[], se houver */
    while(i<n1){
        a[k]=L[i++];
        k++;
    }

    /* Copia os restantes elementos do vetor R[], se houver */
    while(j<n2){
        a[k]=R[j++];
        k++;
    }
}

/* Fun??es de auxiliares de debugging */

/* Lista todos os produtos existentes no sistema */
void k(){
    int i;
    for(i=0;i<n_produtos;i++){
        printf("/%d %s %d %d %d\n",sistema[i].idp,sistema[i].descricao,sistema[i].preco,sistema[i].peso,sistema[i].quantidade);
    }
    printf("\n");
}

/* Lista todos os produtos de uma encomenda */
void K(int ide){
    int i;
    for(i=0;i<MAX_ENC_PRODUTOS;i++){
        if(portofolio[ide].produto[i].idp!=-1){
            printf(":%d:%d %s %d %d %d\n",portofolio[ide].produto[i].idp,i,portofolio[ide].produto[i].descricao,portofolio[ide].produto[i].preco,portofolio[ide].produto[i].quantidade,portofolio[ide].produto[i].peso);
        }
    }
    printf("\n");
}
