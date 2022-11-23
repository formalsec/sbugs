#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX_INPUT 150        /* Maximo de input por comando */
#define MAX_DESC 64          /* Numero maximo de caracteres na descricao de um produto */
#define MAX_ORDERS 500       /* Numero Maximo de Encomendas no sistema */
#define MAX_PRODUCTS 10000   /* Numero Maximo de Produtos no sistema */


int ID_products=0;           /* Contador de produtos no sistema */
int ID_Orders=0;             /* Contador de encomendas no sistema */
char input[MAX_INPUT];       /* Armazenador do input de cada comando */
char *palavra;               /* Armezenador de cada parte do input */


typedef struct Product{      /* Produto */
    int ID;                  /* Identificador do produto */   
    char desc[MAX_DESC];     /* descricao do produto */
    int price;               /* preco do produto */
    int weight;              /* peso do produto */
    int quant;               /* quantidade do produto em stock */   
    int modif;               /* flag que indica se produto foi modificado */
} product;


typedef struct Order{        /* Encomenda */
    int ID_Order;            /* identificador da encomenda */
    int N_de_Prods;          /* numero de produtos na encomenda */
    int weight_order;        /* peso total da encomenda */   
    product order_products[MAX_PRODUCTS];   /* tabela com produtos na encomenda */
} order;


order orders[MAX_ORDERS];           /* tabela com todas as encomendas no sistema */
product products[MAX_PRODUCTS];     /* tabela com todos os produtos no sistema */


/* verifica se produto esta registado no sistema retornando 1 caso seja verificado que sim */
int verifica_produto(int id){
    if(id<ID_products && id>=0)
        return 1;
    else
        return 0;
}


/* verifica se encomenda esta registado no sistema retornando 1 caso seja verificado que sim */
int verifica_encomenda(int id){
    if(id<ID_Orders && id>=0)
        return 1;
    else
        return 0;
}


/*adiciona um novo produto ao sistema*/
void cria_produto(){
    int i=0;
    
    scanf("%s",input);
    palavra=strtok(input,":");
    while(palavra!=NULL){
        if(i==0)
            strcpy(products[ID_products].desc,palavra);
        else if(i==1)
            products[ID_products].price=atoi(palavra);
        else if(i==2)
            products[ID_products].weight=atoi(palavra);
        else
            products[ID_products].quant=atoi(palavra);
        palavra=strtok(NULL,":");
        i++;
    }
    
    products[ID_products].ID=ID_products;
    products[ID_products].modif=0;
    printf("Novo produto %d.\n",ID_products);
    ID_products++;
}


/* aumenta quantidade de um produto no sistema */
void adiciona_stock(){
    int id,new_qtd;
    
    scanf("%s",input);
    palavra=strtok(input,":");
    id=atoi(palavra);
    palavra=strtok(NULL,":");
    new_qtd=atoi(palavra);
    
    if(verifica_produto(id))
        products[id].quant=products[id].quant+new_qtd;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
}


/* adiciona uma nova encomenda ao sistema */
void cria_encomenda(){
    orders[ID_Orders].ID_Order=ID_Orders;
    orders[ID_Orders].N_de_Prods=0;
    orders[ID_Orders].weight_order=0;
    printf("Nova encomenda %d.\n",ID_Orders);
    ID_Orders++;
}


/* adiciona um produto a uma encomenda */
void adiciona_produto(){
    int idp,ide,qtd,i;
    
    scanf("%s",input);
    palavra=strtok(input,":");
    ide=atoi(palavra);
    palavra=strtok(NULL,":");
    idp=atoi(palavra);
    palavra=strtok(NULL,":");
    qtd=atoi(palavra);

    if(!verifica_produto(idp))
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else if(!verifica_encomenda(ide))
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if(qtd>products[idp].quant)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
    else if((orders[ide].weight_order+(qtd*products[idp].weight))>200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
    else{
        for(i=0;i<orders[ide].N_de_Prods;i++){
            if(orders[ide].order_products[i].ID==idp){      /*Se Produto ja se encontra na encomeda */
                orders[ide].order_products[i].quant=orders[ide].order_products[i].quant + qtd;
                break;
            }
        }
        if(i==orders[ide].N_de_Prods && qtd!=0){ 
            orders[ide].order_products[orders[ide].N_de_Prods]=products[idp];
            orders[ide].order_products[orders[ide].N_de_Prods].quant=qtd;
            orders[ide].N_de_Prods++;
        }
        products[idp].quant=products[idp].quant-qtd;
        orders[ide].weight_order=orders[ide].weight_order + (qtd*products[idp].weight);
    }
}


/* diminui a quantidade de um produto no sistema */
void remove_stock(){
    int id,new_qtd;
    
    scanf("%s",input);
    palavra=strtok(input,":");
    id=atoi(palavra);
    palavra=strtok(NULL,":");
    new_qtd=atoi(palavra);

    if(!verifica_produto(id))
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id);
    else if(new_qtd>products[id].quant)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",new_qtd,id);
    else
        products[id].quant=products[id].quant-new_qtd;
}


/* remove um produto de uma encomenda */
void remove_produto_encomenda(){
     int i,ide,idp;
    
    scanf("%s",input);
    palavra=strtok(input,":");
    ide=atoi(palavra);
    palavra=strtok(NULL,":");
    idp=atoi(palavra);

    if(!verifica_encomenda(ide))
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if(!verifica_produto(idp))
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else{
        for(i=0;i<orders[ide].N_de_Prods;i++){
            if(orders[ide].order_products[i].ID==idp){
                products[idp].quant=products[idp].quant + orders[ide].order_products[i].quant;
                orders[ide].weight_order=orders[ide].weight_order - (orders[ide].order_products[i].quant*products[idp].weight);
                orders[ide].order_products[i].quant=0;
                break;
            }
        }
    }
}


/* calcula o preco total de uma encomenda */
void calcula_preco(){
    int id,i,soma=0,idp;
    
    scanf("%s",input);
    palavra=strtok(input,":");
    id=atoi(palavra);

    if(!verifica_encomenda(id))
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id);
    else{
        for(i=0;i<orders[id].N_de_Prods;i++){
            idp=orders[id].order_products[i].ID;
            if(products[idp].modif)         /* verifica se preco do produto foi alguma vez modificado */
                orders[id].order_products[i].price=products[idp].price; 
                
            soma=soma+(orders[id].order_products[i].price*orders[id].order_products[i].quant);
        }
    printf("Custo da encomenda %d %d.\n",id,soma);
    }
}


/*altera preco de um produto*/
void altera_preco(){
    int id,new_price;
    
    scanf("%s",input);
    palavra=strtok(input,":");
    id=atoi(palavra);
    palavra=strtok(NULL,":");
    new_price=atoi(palavra);

    if(!verifica_produto(id))
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id);
    else{
        products[id].price=new_price;
        products[id].modif=1;
    }
}


/* mostra a descricao de um produto e a sua quantidade numa encomenda */
void mostra_produto(){
    int ide,idp,i;
    
    scanf("%s",input);
    palavra=strtok(input,":");
    ide=atoi(palavra);
    palavra=strtok(NULL,":");
    idp=atoi(palavra);

    if(!verifica_produto(idp))
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
    else if(!verifica_encomenda(ide))
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else{
        for(i=0;i<orders[ide].N_de_Prods;i++){
            if(orders[ide].order_products[i].ID==idp){
                printf("%s %d.\n",orders[ide].order_products[i].desc,orders[ide].order_products[i].quant);
                break;
            }
        }
	    if(i==orders[ide].N_de_Prods)
            printf("%s 0.\n",products[idp].desc);
    }
}


/*encontra a encomenda com a maior quantidade de um produto */
void mostra_maior_n_produtos(){
    int id,i,j;
    int vals[2];        
    
    scanf("%s",input);
    palavra=strtok(input,":");
    id=atoi(palavra);

    if(!verifica_produto(id))
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id);
    else{
        vals[1]=0;
        for(i=0;i<ID_Orders;i++){
            for(j=0;j<orders[i].N_de_Prods;j++){
                if(id==orders[i].order_products[j].ID){
                    if(vals[1]<orders[i].order_products[j].quant){
                        vals[0]=orders[i].ID_Order;
                        vals[1]=orders[i].order_products[j].quant;
                    }
                    break;
                }
            }
        }
        if(vals[1]!=0)
            printf("Maximo produto %d %d %d.\n",id,vals[0],vals[1]);
    }

}


/* ordena os produtos do sistema em ordem crescente baseado no preco dos produtos,
usando o algoritmo bubble sort e lista os produtos */
void lista_produtos(){
    int i,finish;
    product aux;
    product *produtos;

    produtos=(product*)can_fail_malloc(sizeof(product)*ID_products);
    
    for(i=0;i<ID_products;i++)
        produtos[i]=products[i];

    while(1){
        finish=1;
        for(i=0;i<ID_products-1;i++){
            if(produtos[i].price>produtos[i+1].price || (produtos[i].price==produtos[i+1].price && produtos[i].ID>produtos[i+1].ID )){
                aux=produtos[i];
                produtos[i]=produtos[i+1];
                produtos[i+1]=aux;
                finish=0;
            }
        }
        if(finish)
            break;
    }
    
    printf("Produtos\n");
    for(i=0;i<ID_products;i++)
        printf("* %s %d %d\n",produtos[i].desc,produtos[i].price,produtos[i].quant);
    
}


/* ordena alfabeticamente os produtos de uma encomenda usando o algoritmo bubble sort e lista-os */
void lista_produtos_encomenda(){
    int i,finish,id;
    product *produtos;
    product aux;
    
    scanf("%s",input);
    palavra=strtok(input,":");
    id=atoi(palavra);
    
    produtos=(product*)can_fail_malloc(sizeof(product)*orders[id].N_de_Prods);

    if(!verifica_encomenda(id))
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id);
    else{
        for(i=0;i<orders[id].N_de_Prods;i++)
            produtos[i]=orders[id].order_products[i];

        while(1){
            finish=1;
            for(i=0;i<orders[id].N_de_Prods-1;i++){
                if(strcmp(produtos[i].desc,produtos[i+1].desc)>0){
                    aux=produtos[i];
                    produtos[i]=produtos[i+1];
                    produtos[i+1]=aux;
                    finish=0;
                }
            }
            if(finish)
                break;
        }   

        printf("Encomenda %d\n",id);
        for(i=0;i<orders[id].N_de_Prods;i++){
            if(products[produtos[i].ID].modif)
                produtos[i].price=products[produtos[i].ID].price;
	    if(produtos[i].quant!=0)	
            	printf("* %s %d %d\n",produtos[i].desc,produtos[i].price,produtos[i].quant);
        }
    }
}




/* obtem o comando a ser executado */
int main(){
    char comando;
    while((comando = getchar()) && comando!='x'){
        if(comando=='a')
            cria_produto();
        else if(comando=='q')
            adiciona_stock();
        else if(comando=='N')
            cria_encomenda();
        else if(comando=='A')
            adiciona_produto();
        else if(comando=='r')
            remove_stock();
        else if(comando=='R')
            remove_produto_encomenda();
        else if(comando=='C')
            calcula_preco();
        else if(comando=='p')
            altera_preco();
        else if(comando=='E')
            mostra_produto();
        else if(comando=='m')
            mostra_maior_n_produtos();
        else if(comando=='l')
            lista_produtos();
        else if(comando=='L')
            lista_produtos_encomenda();
    }
    return 0;
}

