#include <stdio.h>
#include <string.h>
#define MAX_PROD 10000 /* numero maximo de produtos */
#define MAX_DESC 63 /* numero maximo de caracteres para a descricao de um produto */
#define MAX_ENC 500 /* numero maximo de encomendas */

int stop = 0; /* variavel que indica quando o programa acaba */

int idp = 0; /* identificacao de produto */

int ide = 0; /* identificacao de encomenda */

/* tipo "produto": tem a sua descricao,o seu preco,o seu peso e o seu stock disponivel*/
struct prod {   
    int price,weight,stock,id_prod;
    char desc[MAX_DESC];
};

/* vetor onde sao guardados os produtos */
struct prod produtos[MAX_PROD]; 

/* vetores onde os produtos vao ser ordenados para depois serem imprimidos */
struct prod aux2[MAX_PROD];
struct prod aux1[MAX_PROD];


/* vetor onde sao guardadas as encomendas (pode existir no maximo 200 produtos por encomenda, se cada 1 tiver 1 de peso)(o item extra (201) e a fatura(onde e guardado a quantidade de produtos,preco da encomenda e peso)) */
struct prod encomendas[MAX_ENC][201]; 



void add_prod(); 
void add_enc();
void remove_prod();
void remove_enc();
void add_stock_prod();
void cria_nova_enc();
void cost_enc();
void change_price_prod();
void check_stock();
void search_most_wanted();
void list_prod_value();
void list_enc_name();
void print_prod();
void print_enc(int x);
void mergesort(struct prod a[],int left,int right);
void merge(struct prod a[],int left,int m,int right);

/* Funcao onde vai ser selecionado o comando a executar */
int main() {

    /* enquanto a variavel stop nao tomar o valor 1, o programa continua a ler e a executar comandos */
    while (stop != 1){ 

        /* variavel onde vai ser registado o comando a ser utilizado */
        int op; 

        /* le o comando pretendido */
        op = getchar();

        /* verificacao do comando a ser executada */
        if (op == 'a')
            add_prod();

        else if (op == 'q')
            add_stock_prod();

        else if (op == 'N')
            cria_nova_enc();

        else if (op == 'A')
            add_enc();

        else if (op == 'r')
            remove_prod();

        else if (op == 'R')
            remove_enc();

        else if (op == 'C')
            cost_enc();

        else if (op == 'p') 
            change_price_prod();

        else if(op == 'E')
            check_stock();

        else if(op == 'm')
            search_most_wanted();

        else if(op == 'l')  
            list_prod_value();

        else if(op == 'L')
            list_enc_name();

        else if(op == 'x')
            stop = 1; /* faz com que o programa pare */

        else
            continue; /* caso seja lido um valor que nao seja um comando,o ciclo continua (mais usado para evitar "\n" ou " ")*/
    }
    return 0;
}

/* Cria um produto e adiciona - o ao vetor dos produtos (comando 'a') */
void add_prod(){

    int j,i = 0;
    int preco,peso,qtd;
    char descricao[MAX_DESC],aux;

    /* inicializacao do input
    (os "getchar()" e para saltar os espacos e os ":") */
    getchar();

    aux = getchar();
    for (j = 0; aux != ':'; j++){
        descricao[j] = aux;
        aux = getchar();}
    descricao[j] = '\0';

    scanf("%d",&preco);
    getchar();
    scanf("%d",&peso);
    getchar();
    scanf("%d",&qtd);
    
    
    /* criacao do "produto" */
    for (i = 0; descricao[i]!= '\0'; i++)
        produtos[idp].desc[i] = descricao[i];
    produtos[idp].price = preco;
    produtos[idp].weight = peso;     
    produtos[idp].stock = qtd;
    produtos[idp].id_prod = idp;

    printf("Novo produto %d.\n",idp);
    idp ++;
}

/* Adiciona um produto a uma encomenda (comando 'A') */
void add_enc(){
    
    /* criacao de variaveis uteis a funcao */
    int i,id_enc,id_prod,qtd,aux,in = 0;

    /* inicializacao do input */
    getchar();
    scanf("%d",&id_enc);
    getchar();
    scanf("%d",&id_prod);
    getchar();
    scanf("%d", &qtd);

    /* verifica se nao existe a encomenda */
    if (id_enc >= ide)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_enc);

    /* verifica se nao existe o produto */
    else if (id_prod >= idp)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_prod,id_enc);

    /*verifica se existe o stock necessario do produto em questao */
    else if (produtos[id_prod].stock < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id_prod,id_enc);

    /*verifica se a encomenda vai ultrapassar o peso maximo */
    else if (encomendas[id_enc][200].weight + produtos[id_prod].weight * qtd > 200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_prod,id_enc);

    /* caso nada acima aconteca, o programa vai adicionar o produto a encomenda */
    else{

        /* variavel auxiliar para saber quantos produtos tem a encomenda */
        aux = encomendas[id_enc][200].stock;

        /* ciclo para verificar se o produto ja esta na encomenda */
        for (i = 0; i < aux; i ++){
            
            /* se pertencer, adiciona o stock e modifica o preco e o peso da encomenda e o stock do produto */
            if(strcmp(produtos[id_prod].desc,encomendas[id_enc][i].desc) == 0){

                in = 1;

                encomendas[id_enc][i].stock += qtd;

                encomendas[id_enc][200].price += (qtd*produtos[id_prod].price);
                encomendas[id_enc][200].weight += (qtd*produtos[id_prod].weight);

                produtos[id_prod].stock -= qtd;
            }
        }

        /* se nao pertencer, cria um novo produto na encomenda e adiciona a quantidade desejada, modificando tambem o preco e o peso da encomenda e o stock do produto */   
        if (in == 0){

            encomendas[id_enc][aux].price = produtos[id_prod].price;
            encomendas[id_enc][aux].stock = qtd;
            encomendas[id_enc][aux].weight = produtos[id_prod].weight;
            strcpy(encomendas[id_enc][aux].desc,produtos[id_prod].desc);
       
            encomendas[id_enc][200].price += (produtos[id_prod].price * qtd);
            encomendas[id_enc][200].weight += (produtos[id_prod].weight * qtd);
            encomendas[id_enc][200].stock ++;

            produtos[id_prod].stock -= qtd;
        }   
    }    
}

/* retira stock a um produto (comando 'r') */
void remove_prod(){
    
    /* criacao de variaveis uteis a funcao */
    int id_prod,qtd;

    /* inicializacao do input */
    getchar();
    scanf("%d",&id_prod);
    getchar();
    scanf("%d",&qtd);

    /* verifica se o produto nao existe */
    if (id_prod >= idp)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_prod);
    
    /* verifica se o produto tem stock insuficiente ao desejado remover */
    else if (produtos[id_prod].stock - qtd < 0)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd,id_prod);

    /* caso nada acima se verifique, remove o stock desejado ao produto */
    else
        produtos[id_prod].stock -= qtd;    
}

/* Remove um produto de uma encomenda (comando 'R') */
void remove_enc(){

    /* criacao de variaveis uteis a funcao */
    int id_enc,id_prod,aux,i,in = 0;

    /*inicializacao do input */
    getchar();
    scanf("%d", &id_enc);
    getchar();
    scanf("%d", &id_prod);

    /* verifica se a encomenda nao existe */
    if (id_enc >= ide)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_prod, id_enc);
    
    /* verifica se o produto nao existe */
    else if (id_prod >= idp)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_prod,id_enc);

    /* caso nada acima se verifique, a funcao vai remover o produto da encomenda */
    else{

        /* nr de produtos na encomenda */
        aux = encomendas[id_enc][200].stock;

        /* verifica se o produto existe na encomenda */
        for (i = 0; i < aux; i++)
            /* se existir, a variavel in fica a 1(variavel em que 0 significa que o produto nao existe na encomenda e o contrario se in =1) e sai do ciclo, preservando o valor de i */
            if (strcmp(produtos[id_prod].desc,encomendas[id_enc][i].desc) == 0){
                in = 1;
                break;
            }

        /* caso o produto nao esteja na encomenda, nao se faz nada 
           caso o produto esteja na encomenda, retiramos o peso e o preco dele a encomenda e aumentamos o stock do produto com a quantidade deste na encomenda */
        if (in == 1){
            encomendas[id_enc][200].price -= produtos[id_prod].price * encomendas[id_enc][i].stock;
            encomendas[id_enc][200].weight -= produtos[id_prod].weight * encomendas[id_enc][i].stock;
            produtos[id_prod].stock += encomendas[id_enc][i].stock;
            encomendas[id_enc][i].stock = 0;
        }
    }
}

/* Adiciona stock a um produto (comando 'q')*/
void add_stock_prod(){
    
    int id,qtd;

    /* leitura dos valores */
    getchar(); 
    scanf("%d",&id);
    getchar();
    scanf("%d",&qtd);

    /* verifica se o produto nao existe */
    if (id >= idp) 
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);

    /* caso exista, adiciona "qtd" ao stock existente */
    else 
        produtos[id].stock += qtd;
}

/* Cria uma nova encomenda (comando 'N') */
void cria_nova_enc(){

    printf("Nova encomenda %d.\n",ide);

    /* cria o produto "Fatura" no ultimo elemento do vetor onde vai ser guardado o valor, o peso e o numero de produtos da encomenda */
    encomendas[ide][200].price = 0;
    encomendas[ide][200].weight = 0;
    encomendas[ide][200].stock = 0;
    encomendas[ide][200].id_prod = 200;
    strcpy(&encomendas[ide][200].desc[0],"Fatura");

    /* "reserva" o espaco para a encomenda no vetor */
    ide ++;
}

/* Calcula o custo da encomenda e imprime - o (comando 'C') */
void cost_enc(){
    
    /* criacao de variaveis uteis a funcao */
    int id_enc;

    /* inicializacao do input */
    getchar();
    scanf("%d",&id_enc);

    /* verifica se a encomenda nao existe */
    if (id_enc >= ide)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id_enc);

    /* caso exista, retorna o custo dela */
    else
        printf("Custo da encomenda %d %d.\n",id_enc,encomendas[id_enc][200].price);
}

/* Muda o preco de um produto (comando 'p') */
void change_price_prod(){
    
    /* criacao de variaveis uteis a funcao */
    int i,j,aux,id_prod,preco;

    /* inicializacao do input */
    getchar();
    scanf("%d",&id_prod);
    getchar();
    scanf("%d",&preco);

    /* verifica se o produto nao existe */
    if (id_prod >= idp)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_prod);

    /* caso exista, altera o preco */
    else{ 

        produtos[id_prod].price = preco;

        /* percorre as encomendas */
        for (i = 0; i < ide; i++){

            /* nr de produtos na encomenda */
            aux = encomendas[i][200].stock;

            /* percorre os produtos da encomenda */
            for (j = 0; j < aux; j++)

                /* verifica se o produto existe na encomenda,caso exista, muda-se o preco e ajusta-se o valor da encomenda */
                if (strcmp(produtos[id_prod].desc,encomendas[i][j].desc) == 0){

                    encomendas[i][200].price -= encomendas[i][j].stock * encomendas[i][j].price;
                    encomendas[i][j].price = preco;
                    encomendas[i][200].price += encomendas[i][j].stock * encomendas[i][j].price;
                }
        }
    }
}

/* Verifica a quantidade de um certo produto numa encomenda e imprime - a (comando 'E') */
void check_stock(){
    
    /*criacao de variaveis uteis a funcao */
    int not_in = 1,aux,i,id_enc,id_prod;

    /* inicializacao do input */
    getchar();
    scanf("%d", &id_enc);
    getchar();
    scanf("%d", &id_prod);

    /* verifica se a encomenda nao existe */
    if (id_enc >= ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_enc);

    /* verifica se o produto nao existe */
    else if (id_prod >= idp)
        printf("Impossivel listar produto %d. Produto inexistente.\n",id_prod);

    /*caso nada acima se verifica, a funcao procede */
    else{

        /* nr de produtos na encomenda */
        aux = encomendas[id_enc][200].stock;

        /* caso o produto esteja na encomenda, a funcao da print da descricao e a quantidade existente desse produto na encomenda */
        for (i = 0; i < aux; i++)
            if (strcmp(produtos[id_prod].desc,encomendas[id_enc][i].desc) == 0){
                printf("%s %d.\n",produtos[id_prod].desc,encomendas[id_enc][i].stock);
                not_in = 0; 
                break;
            }

        if (not_in == 1)
            printf("%s 0.\n",produtos[id_prod].desc);
    }
    
}

/* Verifica qual e a encomenda que tem a maior quantidade do produto em questao e imprime - a juntamente com a qtd do produto existente na encomenda (comando 'm') */
void search_most_wanted(){
    
    /* criacao de variaveis uteis a funcao */
    int aux,i,j,id_prod,maior = 0,qtd = 0;

    /* inicializacao do input */
    getchar();
    scanf("%d", &id_prod);
    
    /* verifica se o produto nao existe */
    if (id_prod >= idp)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_prod);

    /* caso o produto exista, a funcao prossegue */
    else{

        /* percorre as encomendas */
        for (i = 0; i < ide; i++){

            /* nr de produtos na encomenda */
            aux = encomendas[i][200].stock;

            /* percorre os produtos da encomenda i */
            for (j = 0; j < aux; j++){

                /* verifica se o produto esta na encomenda */
                if (strcmp(produtos[id_prod].desc,encomendas[i][j].desc)== 0)
                    /* caso esteja, ve se a quantidade e maior, e se for, o maior passa a ser a encomenda presente */
                    if (qtd < encomendas[i][j].stock){
                        
                        qtd = encomendas[i][j].stock;
                        maior = i;
                    }
            }
        }

        /* caso alguma encomenda exista e contenha o produto, o valor e imprimido no ecra */
        if (qtd != 0)
            printf("Maximo produto %d %d %d.\n",id_prod,maior,qtd);
    }
}

/* Lista todos os produtos por preco crescente (comando 'l') */
void list_prod_value(){
    
    /* criacao de variaveis uteis a funcao */
    int i;

    /* passa os valores para um dos vetores auxiliares (para nao estragar a posicao dos produtos no vetor original) */
    for(i = 0; i < idp; i++)
        aux2[i] = produtos[i];

    /* Ordena os produtos atraves do mergesort */
    mergesort(aux2,0,idp-1);

    /* Imprime os produtos ordenados */
    print_prod();
}

/* Lista os produtos existentes numa encomenda por ordem alfabetica (comando 'L') */
void list_enc_name(){
    
    /* criacao de variaveis uteis a funcao */
    int menor,nr_prods,id_enc,trade,i,j;
    char menor_d[MAX_DESC];
    struct prod aux;
    
    /* inicializacao do input */
    getchar();
    scanf("%d", &id_enc);

    /* verifica se a encomenda nao existe */
    if (id_enc >= ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_enc);

    /* se a encomenda existir, entao a funcao vai ordenar os produtos dentro da encomenda */
    else{

        nr_prods = encomendas[id_enc][200].stock;

        /* escolhe o produto a trocar com o mais pequeno alfabeticamente */
        for (i = 0; i < nr_prods; i++){

            trade = 0;
            strcpy(menor_d,encomendas[id_enc][i].desc);

            /* percorre os produtos da encomenda */
            for (j = i; j < nr_prods; j++)
                /* caso a descricao do produto j seja alfabeticamente mais pequena que a de menor_d, guarda-se o valor */ 
                if (strcmp(encomendas[id_enc][j].desc,menor_d) < 0){

                    menor = j;
                    strcpy(menor_d,encomendas[id_enc][j].desc);
                    trade = 1;
                } 
            
            /* caso se tenha encontrado alguma descricao mais pequena (trade = 1), troca-se a posicao desse produto, pela do produto i */
            if (trade == 1){

                aux = encomendas[id_enc][i];
                encomendas[id_enc][i] = encomendas[id_enc][menor];
                encomendas[id_enc][menor] = aux;
            }
        }

        /* imprime os valores da encomenda */
        print_enc(id_enc);
    }
}

/* Imprime os produtos existentes */
void print_prod(){

    int i;

    printf("Produtos\n");

    /* Da print dos produtos */
    for (i = 0; i < idp; i ++)
        printf("* %s %d %d\n",aux2[i].desc,aux2[i].price,aux2[i].stock);
}

/* Imprime os produtos existentes na encomenda em questao (x) */
void print_enc(int x){

    int i,aux;

    aux = encomendas[x][200].stock;
    printf("Encomenda %d\n",x);

    /* percorre os produtos da encomenda e imprime-os */
    for (i = 0; i < aux; i++)
        if (encomendas[x][i].stock != 0)
            printf("* %s %d %d\n", encomendas[x][i].desc,encomendas[x][i].price,encomendas[x][i].stock);
}

/* Algoritmo de ordenacao para ordenar os produtos */
void mergesort(struct prod a[],int left,int right){

    /* Calcula a posicao do meio do vetor */
    int m = (right + left)/2;

    /* Caso o limite esquerdo seja maior que o direito, a funcao acaba (caso terminal) */
    if (right <= left)
        return;

    /* Efetua o mergesort ao vetor dividido ao meio */
    mergesort (a,left,m);
    mergesort (a,m+1,right);

    /* Ordena os produtos */
    merge(a,left,m,right);
}

/* Algoritmo de ordenacao para ordenar os produtos */
void merge(struct prod a[],int left,int m,int right){

    int i,j,k;

    /* Passa os valores para outro vetor extra onde os produtos vao ser ordenados */
    for (i = m+1; i > left; i--)
        aux1[i-1] = a[i-1];

    for (j = m; j < right; j++)
        aux1[right+m-j] = a[j+1];

    /* Ordena os produtos por preco, e caso o preco seja igual, por numero de produto */
    for (k = left; k <= right; k++)
        if (aux1[j].price < aux1[i].price || (aux1[j].price == aux1[i].price && aux1[j].id_prod < aux1[i].id_prod))
                a[k] = aux1[j--];
        else
            a[k] = aux1[i++];       
}