#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
/*max_p-maximo produtos
max_e-maximo encomendas
max_w-maximo peso
max_desc-numero de caracteres numa descricao*/

#define max_p 10000
#define max_e 500
#define max_w 200
#define max_desc 63
#define idp_inicial 0
#define ide_inicial 0
#define TRUE 1
#define FALSE 0
#define STRING_VAZIA '\0'

/* representacao de produtos: elementos basicos(idp,desc,preco,peso,quantidade)e estado(se existem numa determinada encomenda) */

typedef struct produto{
    int idp;
    char desc[max_desc];
    int preco;
    int peso;
    int quant;
    int estado;
}produto;

produto produtos[max_p];

/* representacao de encomendas: elementos basicos(ide, preco(total), peso(total),numero(de produtos na encomenda)),estado 
(se foi criada), e um vetor de produtos */

typedef struct encomenda{
    int ide;
    produto produtos[max_p] ;
    int estado;
    int peso;
    int preco;
    int numero;
}encomenda;

/* encomendas[]- vetor de encomendas onde estas vao ser armazenadas
   encomenda sistema[]-vetor de produtos 
   aux[]-vetor de produtos usado nas funcoes de sorting
   resultado[]-vetor resultado da funcao l(para nao interferir com a ordem original do sistema)
   resultado_string[]-vetor resultado da funcao L*/

encomenda encomendas[max_e];
produto sistema[max_p];
produto aux[max_p];
produto resultado[max_p];
produto resultado_string[max_p];

int len,i,e,stock_plus,n,quant,idp_i,ide_i,quant_i,custo,max_produto,l,m,r,n_encomenda;
void adiciona_produto(int idp);
void adiciona_stock();
void adiciona_encomenda(int ide);
void adiciona_produto_encomenda();
void remove_stock();
void custo_encomenda();
void altera_preco();
void display_produto_encomenda();
void maximo_produto();
void ordena_sistema();
void ordena_encomenda();
void merge(produto sistema[max_p],int l, int m, int r);
void merge_sort(produto sistema[max_p],int l,int r);
void merge_string(produto a[max_p],int l, int m, int r);
void merge_sort_string(produto a[max_p],int l, int r);
void remove_produto_encomenda();
void inicializa_vetor(produto resultado_string[max_p]);

int main(){
    char c;
    /*sao criadas variaveis para atribuir aos produtos adicionados ao sistema(idp) e as encomendas criadas(ide)*/
    int idp,ide;
    idp=idp_inicial;
    ide=ide_inicial;
    while ((c=getchar())!='x'){
        switch (c){
        case 'a':
            getchar();
            adiciona_produto(idp);
            idp++;
            break;
        case 'q':
            getchar();
            adiciona_stock();
            break;
        case 'N':
            getchar();
            adiciona_encomenda(ide);
            ide++;
            break;
        case 'A':
            getchar();
            adiciona_produto_encomenda();
            break;
        case 'r':
            getchar();
            remove_stock();
            break;
        case 'R':
            getchar();
            remove_produto_encomenda();
            break;
        case 'C':
            getchar();
            custo_encomenda();
            break;
        case 'p':
            getchar();
            altera_preco();
            break;
        case 'E':
            getchar();
            display_produto_encomenda();
            break;
        case 'm':
            getchar();
            maximo_produto();
            break;
        case 'l':
            getchar();
            ordena_sistema(idp);
            break;
        case 'L':
            getchar();
            ordena_encomenda();
            break;   
        }
    }
    return 0;
}

void adiciona_produto(int idp_i){
    sistema[idp_i].idp=idp_i;
    sistema[idp_i].estado=TRUE;
    scanf("%[^:]:%d:%d:%d", sistema[idp_i].desc, &sistema[idp_i].preco, &sistema[idp_i].peso, &sistema[idp_i].quant);
    printf("Novo produto %d.\n", idp_i);
}

void adiciona_stock(){
    scanf("%d:%d",&n,&stock_plus);
            /*funcao da componente estado: permite rapidamente verificar que o produto existe*/
            if (sistema[n].estado==TRUE){
                sistema[n].quant+=stock_plus;
            }
            else {
                printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",n);
            }

}

void adiciona_encomenda(int ide){
    encomendas[ide].estado=TRUE;
    encomendas[ide].ide=ide;
    encomendas[ide].peso=0;
    encomendas[ide].preco=0;
    encomendas[ide].numero=0;
    printf("Nova encomenda %d.\n",ide);
}

void adiciona_produto_encomenda(){
    scanf("%d:%d:%d",&ide_i,&idp_i,&quant_i);
            /*verificacao de erros; terceiro if verifica se existe quantidade suficiente no sistema
            e quarto if verifica se a threshold do peso eh ultrapassada*/
            if (encomendas[ide_i].estado!=TRUE){
                printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp_i,ide_i);
            }
            else if (sistema[idp_i].estado!=TRUE){
                printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp_i,ide_i);
            }   
            else if (quant_i>sistema[idp_i].quant){
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp_i,ide_i);
            }
            else if ((encomendas[ide_i].peso+(sistema[idp_i].peso*quant_i))>max_w){
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp_i,ide_i);
            }    
            else{
                /*verificar se o produto ja esta na encomenda*/
                /*se nao estiver, associar os valores necessarios aos componentes*/
                if (encomendas[ide_i].produtos[idp_i].estado!=TRUE){
                    encomendas[ide_i].produtos[idp_i].idp=sistema[idp_i].idp;
                    strcpy(encomendas[ide_i].produtos[idp_i].desc,sistema[idp_i].desc);            
                    encomendas[ide_i].produtos[idp_i].preco=sistema[idp_i].preco;
                    encomendas[ide_i].produtos[idp_i].peso=sistema[idp_i].peso;
                    encomendas[ide_i].produtos[idp_i].estado=TRUE; 
                    encomendas[ide_i].numero++;
                }
                /*incrementar os valores basicos como o preco peso e quantidade,e retirar quantidade do sistema*/
                encomendas[ide_i].produtos[idp_i].quant+=quant_i;
                encomendas[ide_i].peso+=(sistema[idp_i].peso*quant_i);
                encomendas[ide_i].preco+=(sistema[idp_i].preco*quant_i);
                sistema[idp_i].quant-=quant_i;     
            }
}

void remove_stock(){
    scanf("%d:%d",&idp_i,&quant_i);
    if (sistema[idp_i].estado!=TRUE){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp_i);
    }
    /*verificar que a quantidade do input nao eh superior a do sistema*/
    else if (quant_i>sistema[idp_i].quant){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quant_i,idp_i);
    }
    else {
        sistema[idp_i].quant-=quant_i;
    }
}

void remove_produto_encomenda(){
    scanf("%d:%d",&ide_i,&idp_i);
    if (encomendas[ide_i].estado!=TRUE){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp_i,ide_i);
    }
    else if (sistema[idp_i].estado!=TRUE){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp_i,ide_i);
    }
    else{
        if (encomendas[ide_i].produtos[idp_i].estado==TRUE){
            sistema[idp_i].quant+=(encomendas[ide_i].produtos[idp_i].quant);
            encomendas[ide_i].peso-=(encomendas[ide_i].produtos[idp_i].quant*encomendas[ide_i].produtos[idp_i].peso);
            encomendas[ide_i].preco-=(encomendas[ide_i].produtos[idp_i].quant*encomendas[ide_i].produtos[idp_i].preco);
            encomendas[ide_i].produtos[idp_i].estado=FALSE;
            encomendas[ide_i].produtos[idp_i].peso=0;
            encomendas[ide_i].produtos[idp_i].preco=0;
            encomendas[ide_i].produtos[idp_i].quant=0;
            encomendas[ide_i].numero--;
        }
    }  
}

void custo_encomenda(){
    scanf("%d",&ide_i);
    if (encomendas[ide_i].estado!=TRUE){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide_i);
    }
    else{
        printf("Custo da encomenda %d %d.\n",ide_i, encomendas[ide_i].preco);
    }
}

void altera_preco(){
    scanf("%d:%d",&idp_i,&n);
    if (sistema[idp_i].estado!=TRUE){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp_i);
    }
    else{
        sistema[idp_i].preco=n;
        for (i=0;i<max_e;i++){
            /*subtrair o preco antigo do produto as encomendas, e depois adicionar o preco novo*/
            if (encomendas[i].produtos[idp_i].estado==TRUE){
                encomendas[i].preco-=(encomendas[i].produtos[idp_i].preco*encomendas[i].produtos[idp_i].quant);
                encomendas[i].produtos[idp_i].preco=n;
                encomendas[i].preco+=(encomendas[i].produtos[idp_i].preco*encomendas[i].produtos[idp_i].quant);
            }
        }           
    }
}

void display_produto_encomenda(){
    scanf("%d:%d",&ide_i,&idp_i);
    if (encomendas[ide_i].estado!=TRUE){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide_i);
    }
    else if (sistema[idp_i].estado!=TRUE){
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp_i);
    }
    else {
        printf("%s %d.\n",sistema[idp_i].desc,encomendas[ide_i].produtos[idp_i].quant);
    }     
}

void maximo_produto(){
    scanf("%d",&idp_i);
    if (sistema[idp_i].estado!=TRUE){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp_i);
    }
    else{
        max_produto=0;
        n_encomenda=0;
        for (e=0;e<=max_e;e++){
        /*verificar se o produto existe em cada encomenda, e guardar o numero da 
        encomenda e o valor se este for o maximo */
            if (encomendas[e].produtos[idp_i].estado==TRUE){
                if (encomendas[e].produtos[idp_i].quant>max_produto){
                    n_encomenda=e;
                    max_produto=encomendas[e].produtos[idp_i].quant;
                }
            }
        }
        /*verificar que a variavel max_produto foi alterada*/
        if (max_produto>0){
            printf("Maximo produto %d %d %d.\n", idp_i, encomendas[n_encomenda].ide, max_produto);
        }
    }
}

void ordena_sistema(int idp_i){
    /*copiar os valores do produto no sistema para o vetor resultado*/
    for (i=0;i<idp_i;i++){
        strcpy(resultado[i].desc,sistema[i].desc);
        resultado[i].idp=sistema[i].idp;
        resultado[i].peso=sistema[i].peso;
        resultado[i].preco=sistema[i].preco;
        resultado[i].quant=sistema[i].quant;
    }
    /*dar sort ao vetor resultado*/
    merge_sort(resultado,idp_inicial,idp_i-1);
    printf("Produtos\n");
    for (i=0;i<idp_i;i++){
        printf("* %s %d %d\n",resultado[i].desc,resultado[i].preco, resultado[i].quant);
    }
}
void ordena_encomenda(){
    scanf("%d",&ide_i);
    /*caso alguma encomenda tenha sido esvaziada, eh necessario inicializar o vetor 
    resultado de novo*/
    inicializa_vetor(resultado_string);
    if (encomendas[ide_i].estado!=TRUE){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide_i );
    }
    else{
        i=0;
        e=0;
        /*percorre o numero de produtos na encomenda e copia os valores 
        para o vetor resultado*/
        while(e<encomendas[ide_i].numero){
            if (encomendas[ide_i].produtos[i].estado==TRUE){
                strcpy(resultado_string[e].desc,encomendas[ide_i].produtos[i].desc);
                resultado_string[e].idp=encomendas[ide_i].produtos[i].idp;
                resultado_string[e].peso=encomendas[ide_i].produtos[i].peso;
                resultado_string[e].preco=encomendas[ide_i].produtos[i].preco;
                resultado_string[e].quant=encomendas[ide_i].produtos[i].quant;
                e++;
            }
            i++; 
        }
        printf("Encomenda %d\n",ide_i);
        /*dar sort ao vetor resultado*/
        merge_sort_string(resultado_string,idp_inicial,e-1);
        for (i=0;i<e;i++){
            printf("* %s %d %d\n",resultado_string[i].desc,resultado_string[i].preco, resultado_string[i].quant);
        }
    }
}

void inicializa_vetor(produto resultado_string[max_p]){
    for (i=0;i<=max_p;i++){
        resultado_string[i].desc[0]=STRING_VAZIA;
        resultado_string[i].idp=0;
        resultado_string[i].peso=0;
        resultado_string[i].preco=0;
        resultado_string[i].quant=0;
    }
}

/*o sorting faz se com o merge sort*/

void merge(produto a[max_p],int l, int m, int r){
    int i,j,k;
    for (i=m+1;i>l;i--){
        aux[i-1]=a[i-1];
    }
    for (j=m;j<r;j++){
        aux[r+m-j]=a[j+1];
    }
    /*primeiro os precos dos produtos na encomenda sao comparados*/
    for(k=l;k<=r;k++){
        if (aux[j].preco<aux[i].preco){
            resultado[k]=aux[j--];
        }
        /*se os precos forem iguais , o fator decisivo e o id*/
        else if (aux[j].preco==aux[i].preco){
            if (aux[j].idp<aux[i].idp){
                resultado[k]=aux[j--];
            }
            else {
                resultado[k]=aux[i++];
            }
        }
        else {
            resultado[k]=aux[i++];
        }
    }
}

void merge_sort(produto a[max_p],int l, int r){
    int m=(l+r)/2;
    if (r<=l){
        return;
    }
    merge_sort(a,l,m);
    merge_sort(a,m+1,r);
    merge(a,l,m,r);
}

void merge_string(produto a[max_p],int l, int m, int r){
    int i,j,k;
    for (i=m+1;i>l;i--){
        aux[i-1]=a[i-1];
    }
    for (j=m;j<r;j++){
        aux[r+m-j]=a[j+1];
    }
    for(k=l;k<=r;k++){
        if (strcmp(aux[j].desc,aux[i].desc)<0){
            resultado_string[k]=aux[j--];
        }
        else {
            resultado_string[k]=aux[i++];
        }
    }
}

void merge_sort_string(produto a[max_p],int l, int r){
    int m=(l+r)/2;
    if (r<=l){
        return;
    }
    merge_sort_string(a,l,m);
    merge_sort_string(a,m+1,r);
    merge_string(a,l,m,r);
}
