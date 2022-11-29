#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define S 63 /*numero maximo de caracteres da descricao do produto*/
#define MAX 10000 /* numero maximo de produtos disponiveis na store*/
#define IDO 500 /*numero maximo de encomendas*/
#define MAX_O 200 /*numero maximo de produtos por encomenda*/
#define exch(A,B) {product t=A;A=B;B=t;}

/*definicao do produto*/

typedef struct product{

    char name[S];
    int weight;
    int price; 
    int qtd;
    int id;

} product; 
/*definicao de encomenda*/
typedef struct order{
    int ido;
    int number;
    int weight;
    int pro_id_qtd[MAX_O][2]; /* matriz pro_id_qtd: contem 200 elementos(produtos), em que o indice 0 corresponde ao id do produto e o indice 1 a quantidade desse */
    int price;
    int total; 
} order;

/* Array of products in the store */
product store[MAX];

/* Array of orders*/
order orders[IDO];


/* funcao: adiciona novo produto a store*/
void add_new_product(int n){ 
    int i=0; 
    char character; /*caracter do nome do produto*/

    character=getchar(); /*remove o espaco*/
    character=getchar();

    while(character!=':'){ 
        store[n].name[i++]=character; /*coloca cada caracter no vetor ate encontrar ":" */
        character=getchar(); 
    }

    store[n].name[i]='\0'; /* finaliza o vetor com \0 */

        scanf("%d:%d:%d",&store[n].price,&store[n].weight,&store[n].qtd); /* seguintes inputs correspondem ao preco, peso e quantidade respetivamente*/
        store[n].id=n;
        printf("Novo produto %d.\n",store[n].id); 

    n+=1; /*incrementa o numero de produtos na store*/

}

/* funcao: aumenta a quantidade do produto na store*/
void add_stock(int n){
    int id,qtd;
    scanf(" %d:%d",&id,&qtd); 
        if(id>n){ /*caso o id do produto seja maior que o numero de produtos na store e porque este nao existe*/
            printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
        }
        else{
                   
            store[id].qtd+=qtd;
            /*soma a quantidade do produto na store o valor */
        }
}

/*funcao auxiliar: calcula o peso total de uma dada encomenda*/
int weight_calcu(int ido){
    int soma=0,i=0,id,qtd;

    while(orders[ido].pro_id_qtd[i][0]!=-1){  /*percorre a matriz das encomendas, na encomenda ido, ate encontrar um produto com id=-1 */

        id=orders[ido].pro_id_qtd[i][0]; /* obtem o id do produto*/
        qtd=orders[ido].pro_id_qtd[i][1]; /* obtem a quantidade desse produto na encomenda*/
        soma+=store[id].weight*qtd; /*soma o peso (informacao no vetor store) multiplicado pela quantidade na encomenda*/
        i+=1;
    }
    return soma; 
}

/*funcao auxiliar: indica em que posicao da matriz "orders" um dado produto se encontra*/
int find_id(int ido,int id){
    int i;
     for(i=0;i<MAX_O;i++){ 
        if(orders[ido].pro_id_qtd[i][0]==id){ /*percorre a matriz ate encontrar um id igual ao do produto*/
            return i; /*devolve essa posicao*/
        }
    }
    return -1; /*caso esse produto nao se encontre na encomenda devolve -1*/
}

/*funcao: adiciona quantidade de um produto a uma dada encomenda*/
void add_product(int n, int no){

    /*variavel weight: contem o peso total da encomenda
    variavel index: */
    int ido,id,qtd,weight,index,i; 

    scanf(" %d:%d:%d",&ido,&id,&qtd); /* pede ao utilizador o id da encomenda, o do produto e a quantidade*/

               weight=(qtd*store[id].weight)+weight_calcu(ido); /*atribui a variavel weight o peso total da encomenda, apos adicionar essa quantidade do produto*/

                if(ido>no){
                    /*caso o id da encomenda seja maior do que o numero de encomendas e porque nao esta nao existe*/
                    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id,ido);
                }
                else if(id>n){
                    /*caso o id do produto seja maior do que o numero de produtos na store e porque este nao existe*/
                    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id,ido);
                }
                else if(store[id].qtd<qtd){
                    /*a quantidade inserida pelo utilizador e superior a quantidade do produto na store */
                    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id,ido);
                }
                else if(weight>MAX_O){
                    /*o peso da encomenda apos adicionar esse produto e superior a 200 kg*/
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id,ido); 
                    
                }
                /*caso contrario: e possivel adicionar o produto a encomenda*/
                else{
                     
                    index=find_id(ido,id); /*atribui a variavel index a posicao desse produto na matriz "orders" */
                    
                    if(index!=-1){ /* se diferente de -1: produto ja esta na encomenda ido*/
                        orders[ido].pro_id_qtd[index][1]+=qtd; /*aumenta a quantidade deste na encomenda ido*/
                       
                    }
                    else{ /*produto nao esta ainda na encomenda*/
                        for(i=0;i<MAX_O;i++){ 
                            if(orders[ido].pro_id_qtd[i][0]==-1 && index==-1){ /*procura uma posicao na matriz em que esteja sem nenhum produto (igual a -1) */
                                orders[ido].pro_id_qtd[i][0]=id; /*coloca nessa posicao da encoemenda ido, no indice 0 o id do produto */
                                orders[ido].pro_id_qtd[i][1]=qtd; /* coloca nessa posicao da encomenda ido, no indice 1 a quantidade do produto*/
                                orders[ido].total+=1; /*incrementa o numero de produtos da encomenda ido*/
                                index=1; /*index passa a ser 1: sai do ciclo*/
                            }
                        }
                        
                    }  
                       
                    store[id].qtd-=qtd;   /*altera a quantidade disponivel na store desse produto*/               
                }      
    }   
   


/*funcao: diminui a quantidade de um dado produto na store*/                    
void remove_stock(int n){
    int id,qtd;
    scanf(" %d:%d",&id,&qtd);
                if(id>n){
                    printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id);
                }
                else if(store[id].qtd<qtd){
                    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,id);
                }
                else{
                    store[id].qtd-=qtd; /*diminui "qtd" unidades a quantidade do produto na store*/
                }              
}

/*
funcao: remove produto de uma dada encomenda
comando "R"
*/
void remove_product(int n, int no){
    int ido,id,i,index;
     scanf(" %d:%d",&ido,&id); /*pede ao utilizador o id da encomenda, e o do produto respetivamente*/
            if(no<ido){
                    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id,ido);
            }
            else if(n<id){
                printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id,ido);   
            }
            else{
                index=find_id(ido,id); /*atribui a variavel index a posicao desse produto na matriz "orders" */
                if(index!=-1){ /*diferente de -1: o produto encontra-se na encomenda "ido" */
                   store[id].qtd+=orders[ido].pro_id_qtd[index][1]; /* repoe o stock na store */

                for(i=index;i<MAX_O-1;i++){ /* recua as posicoes dos produtos seguintes dessa encomenda*/
                    orders[ido].pro_id_qtd[i][0]=orders[ido].pro_id_qtd[i+1][0]; 
                    orders[ido].pro_id_qtd[i][1]=orders[ido].pro_id_qtd[i+1][1]; 
                }            
                orders[ido].pro_id_qtd[199][0]=-1; /*coloca o id do ultimo produto da encomenda a -1: lugar disponivel*/
                orders[ido].total-=1; /*decrementa 1 unidade o numero de produtos da encomenda "ido"*/
                }
            }
}

/*funcao auxiliar: calcula o custo total de uma dada encomenda*/
int price_calcu(int ido){
    int soma=0,i,id,qtd; 

    for(i=0;i<orders[ido].total;i++){ /*percorre a encomenda ate ao ultimo produto desta*/
        id=orders[ido].pro_id_qtd[i][0]; /*id do produto*/
        qtd=orders[ido].pro_id_qtd[i][1]; /*qtd desse produto na encomenda*/
        soma+=store[id].price*qtd; /* soma o preco desse produto (encontrado na store atraves do id),multiplicado pela sua quantidade */
    }
    return soma; /*devolve o custo total*/
}
/*
funcao: mostra o custo total de uma dade encomenda
comando: "C"
*/
void order_total(int no){
    int ido;
    scanf(" %d",&ido); /*utilzador introduz o numero da encomenda: ido*/
        if(no<ido){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ido);
        }                
        else{
            orders[ido].price=price_calcu(ido); /* atribui o preco da encomenda, calculado atraves da funcao auxiliar "price_calcu"*/
            printf("Custo da encomenda %d %d.\n",ido,orders[ido].price);            
        }
}
/*
funcao: altera o preco de um dado produto
comando: "p"
*/
void price_change(int n){
    int id,price;
    scanf(" %d:%d",&id,&price); /*utilizador introduz o id do produto e o novo preco*/
                if(id>n){
                    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id);
                }
                store[id].price=price; /*altera o valor na store*/
}
/*
funcao: lista o nome do produto e a sua quantidade numa dada encomenda
comando: "E"
*/
void orders_product(int n,int no){
    /*x: variavel de controlo*/
    int id,ido,i,x=0;
    scanf(" %d:%d",&ido,&id); 
    if(n<id){
        printf("Impossivel listar produto %d. Produto inexistente.\n",id);          
    }
    else if(no<ido){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ido);
    }
    else{
        for(i=0;i<MAX_O;i++){ /*percorre a encomenda "ido"*/
            if(orders[ido].pro_id_qtd[i][0]==id && x==0){ /*encontra o produto "id" na encomenda "ido"*/
                printf("%s %d.\n",store[id].name,orders[ido].pro_id_qtd[i][1]); /*print do seu nome(presente na store) e quantidade na encomenda*/
                x=1; /*x passa a ser 1: sai do ciclo*/
            }
        }
        if(x==0) /*caso x seja 0: nao existe esse produto na encomenda "ido"*/
        {
        printf("%s 0.\n",store[id].name); /*a sua quantidade na encomenda e portanto 0*/
        }
    }
}

/* 
funcao: lista o identificador da encomenda em que o produto dado ocorre mais vezes
comando: "m"*/
void maximum_product(int n){
    /*variavel maior: quantidade maior desse produto nas encomendas
    variavel ido: numero da encomenda onde se encontra a quantidade maior do produto "id"*/
    int id,i,j,maior=0,ido;
     scanf(" %d",&id); 
                
                    if(n<id){
                        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id);
                        
                    }
                    else{
                        for(i=0;i<IDO;i++){ /*percorre todas as encomendas da matriz "orders" */
                            for(j=0;j<MAX_O;j++){ /*percorre todos os produtos da encomenda*/
                                if(orders[i].pro_id_qtd[j][0]==id){ /*encontra na encomenda i o produto "id"*/
                                    if(orders[i].pro_id_qtd[j][1]>maior){ /*caso a sua quantidade seja superior a maior:*/
                                        maior=orders[i].pro_id_qtd[j][1]; /* atribui a "maior" a nova quantidade superior*/
                                        ido=i; /*atribui a "ido" o numero dessa encomenda onde a quantidade e maior*/
             
                                    }
                                }
                            }
                        }
                        if(maior!=0){ /*da print apenas se esse produto se encontrar numa das encomendas*/
                            printf("Maximo produto %d %d %d.\n",id,ido,maior); 
                            }
                    }    
}

product aux_1[MAX]; /*vetor auxiliar*/

void merge_price(product a[], int l, int m, int r){
    int i,j,k; 
    /*construcao do vetor auxiliar*/
    for(i=m+1;i>l;i--){
        aux_1[i-1]=a[i-1]; 
    }
    for(j=m;j<r;j++){ 
        aux_1[r+m-j]=a[j+1];
    }
    for(k=l;k<=r;k++){
        if(aux_1[j].price<aux_1[i].price){
            a[k]=aux_1[j--];
        }
        else if(aux_1[j].price==aux_1[i].price){/*caso os precos sejam iguais:*/ 
            if(aux_1[j].id<aux_1[i].id){ 
                a[k]=aux_1[j--]; 
            } /*o de menor id surge primeiro*/
            else{
                a[k]=aux_1[i++];
            }
           
        } 
        else{
            a[k]=aux_1[i++];
        }
    }   
}

void mergesort_price(product a[],int l,int r){ 
    int m=(r+l)/2;

    if(r<=l){
        return;
    }
    mergesort_price(a,l,m); 
    mergesort_price(a,m+1,r);
    merge_price(a,l,m,r); 
}

product store_copy[MAX]; /*vetor da estrutura "product", de tamanho "Max" */

/*
funcao: ordena todos os produtos da store por ordem crescente de preco
comando: "l"
*/
void sort_price(int n){
    int i;
    for(i=0;i<n+1;i++){
        store_copy[i]=store[i]; /*copia todos os produtos da store para um novo vetor copia*/
    }

    printf("Produtos\n");
    mergesort_price(store_copy,0,n); 
    for(i=0;i<n+1;i++){
        printf("* %s %d %d\n",store_copy[i].name,store_copy[i].price,store_copy[i].qtd); 
    }
} 

int aux[MAX_O]; /*vetor auxiliar*/

void merge_desc(int a[], int l, int m, int r){
    int i,j,k;
    /*contrucao do vetor auxiliar*/
    for(i=m+1;i>l;i--){
        aux[i-1]=a[i-1]; 
    }
    for(j=m;j<r;j++){ 
        aux[r+m-j]=a[j+1];
    }
    for(k=l;k<=r;k++){
        if(strcmp(store[aux[j]].name,store[aux[i]].name)<0){
            a[k]=aux[j--];
        }else{
            a[k]=aux[i++];
        }
    }
}

void mergesort_descr(int a[],int l,int r){ 
    int m=(r+l)/2;

    if(r<=l){
        return;
    }
    mergesort_descr(a,l,m); 
    mergesort_descr(a,m+1,r);
    merge_desc(a,l,m,r); 
}
/*
funcao:  lista todos os produtos de uma encomenda por ordem alfabetica da descricao
comando: "L" 
*/
void sort_description(int no){ 
    int ido,i,id;
    int list[MAX_O]; /*vetor que contem todos os ids dos produtos da encomenda "ido". diemnsao MAX_O */
    int list_qtds[MAX]; /*vetor que contem as quantidades de cada produto presente na encomenda "ido" . dimensao MAX*/
     
    scanf(" %d",&ido); 
    if(no<ido){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ido);
    }
    
    else{
        for(i=0;i<orders[ido].total;i++){
            id=orders[ido].pro_id_qtd[i][0]; 
            list[i]=id; /*coloca no vetor list o id do produto, sequencialmente*/
            list_qtds[id]=orders[ido].pro_id_qtd[i][1]; /*coloca na posicao id, a quantidade desse produto na encomenda*/
        }
        mergesort_descr(list,0,orders[ido].total-1);
        

        printf("Encomenda %d\n",ido);
        for(i=0;i<orders[ido].total;i++){
            printf("* %s %d %d\n",store[list[i]].name,store[list[i]].price,list_qtds[list[i]]); /*list[i] corresponde a um id. print: nome, preco e quantidade desse produto na encomenda*/
        }
    }
}


int main(){

   
    char action; 
/*
variavel n: numero de produtos na loja 
variavel no: numero de encomendas 
*/
   int n=-1,no=-1,i,j; 

    for(i=0;i<IDO;i++){
        for(j=0;j<MAX_O;j++){
            orders[i].pro_id_qtd[j][0]=-1; /* todos os ids dos produtos das encomendas sao colocados a -1*/
        }
    }
    

   
    action=getchar(); /*le o comando*/

    while(action!='x'){ /* quando for x, o programa termina */

        switch(action){
            
            case 'a': /*adiciona um novo produto ? store*/

                n+=1; /* numero de produtos aumenta 1 unidade*/
                add_new_product(n);
                break;
            
            case 'q': /* comando para aumentar a quantidade do produto disponivel */

                add_stock(n);
                break;
            
            case 'N': /* comando para criar uma novo encomenda */

                no+=1; /* numero de encomendas aumenta*/
                orders[no].ido=no;
                printf("Nova encomenda %d.\n",orders[no].ido);  
                break;
            
            case 'A': /* comando para adicionar quantidade de um dado produto a encomenda */
            
               add_product(n,no);
                break;

            case 'r': /* comando para diminuir a quantidade de um dado produto na store */
                remove_stock(n); 
                break;
            
            case 'R': /* comando para remover um dado produto de uma encomenda*/
                remove_product(n,no); 
                break;
            
            case 'C': /* comando para calcular o custo de uma encomenda*/
                order_total(no); 
                break;

            case 'p': /*comando para alterar o preco de um dado produto */
                price_change(n);
                break;

            case 'E': /* comando que lista a descricao de um produto e a sua quantidade numa dada encomenda */
                orders_product(n,no);
                break;
            
            case 'm':  /*  lista o identificador da encomenda em que o produto dado ocorre mais vezes */
                maximum_product(n);
                break; 

            case'l': /* lista todos os produtos existentes na store por ordem crescente de preco  */
                sort_price(n); 
                break;
            

            case 'L': /* lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
                sort_description(no);
                break;


            default:
                break;
        }

        action=getchar(); /*le o comnando*/
    }
    return 0;
    
}
