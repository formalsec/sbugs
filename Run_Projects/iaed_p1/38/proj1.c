#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char description[64];
    int price;
    int weight;
    int stock; 
    int id_product;
} product;

typedef struct {
    int weight;
    int n_order;
    int n_product;
    product _product_[200];
} order;

/*VARIAVEIS*/
char input[6][64]={{0}};
int get_input(char string[]);
int idp_product=0; /*NUMERO DE PRODUTOS - INDICE NO VETOR*/
int ide_order=0; /*NUMERO DE ENCOMENDAS - INDICE NO VETOR*/
product products[10000]={0}; /*VETOR DAS ESTRUTURAS PRODUTOS*/
product aux;
order orders[500]={0}; /*VETOR DAS ESTRUTURAS ENCOMENDAS*/
order other_aux;
product a;
product b;

/*FUNCOES*/
int get_input(char string[]);
product new_product();
void add_product();
int error_product_inex1();
void add_stock();
void new_order();
int add_product_to_order();
int remov_stock();
int remov_product();
void calc_c(int ide);
void change_price();
void desc_stock_product();
void ide_product_more_often(int idp);
void list_products();
void insertion();
/*void insertion1(int ide);
void list_orders(int ide);*/

int main() {
    int i=0, j=0, ide=0, idp=0;
    char string[100], comando;
    while ((comando=getchar())!='x') {
        switch(comando) {
            case 'a':
                getchar(); /*LE O ESPACO ENTRE O COMANDO E O INPUT*/
                scanf("%[^\n]s", string);
                get_input(string);
                new_product();
                add_product();
                for(i=0; i<64; i++) {
                    for(j=0; j<6; j++) {
                        input[j][i]=0;
                    }
                }
                break;
            case 'q':
                getchar();
                scanf("%[^\n]s", string);
                get_input(string);
                add_stock(input);
                for(i=0; i<64; i++) {
                    for(j=0; j<6; j++) {
                        input[j][i]=0;
                    }
                }
                break;
            case 'N':
                new_order();
                break;
            case 'A':
                getchar();
                scanf("%[^\n]s", string);
                get_input(string);
                add_product_to_order(input);
                for(i=0; i<64; i++) {
                    for(j=0; j<6; j++) {
                        input[j][i]=0;
                    }
                }
                break;
            case 'r':
                getchar();
                scanf("%[^\n]s", string);
                get_input(string);
                remov_stock(input);
                for(i=0; i<64; i++) {
                    for(j=0; j<6; j++) {
                        input[j][i]=0;
                    }
                }
                break;
            case 'R':
                getchar();
                scanf("%[^\n]s", string);
                get_input(string);
                remov_product(input);
                for(i=0; i<64; i++) {
                    for(j=0; j<6; j++) {
                        input[j][i]=0;
                    }
                }  
                break;   
            case 'C':
                getchar();
                scanf("%d", &ide);
                calc_c(ide);
                break;
            case 'p':
                getchar();
                scanf("%[^\n]s", string);
                get_input(string);
                change_price(input);
                for(i=0; i<64; i++) {
                    for(j=0; j<6; j++) {
                        input[j][i]=0;
                    }
                }
                break;
            case 'E':
                getchar();
                scanf("%[^\n]s", string);
                get_input(string);
                desc_stock_product(input);
                for(i=0; i<64; i++) {
                    for(j=0; j<6; j++) {
                        input[j][i]=0;
                    }
                }
                break;
            case 'm':
                getchar();
                scanf("%d", &idp);
                ide_product_more_often(idp);
                break;
            case 'l':
                getchar();
                insertion();
                list_products();
                break;
           /* case 'L':
                getchar();
                scanf("%d", &ide);
                insertion1(ide);
                list_orders(ide);
                break;*/
        }
    }
    return 0;
}

/*TRATAR DO INPUT*/
int get_input(char string[]) {
    int i=0;
    char *val;
    /* vai buscar o primeiro 'token' */
    val = strtok(string, ":");
    /* percorre os restantes 'tokens' */
    while(val!=NULL) {
        strcpy(input[i], val);
        i++;
        val = strtok(NULL, ":");
    }
    return 0;
}

/*GUARDA O PRODUTO NO PRODUTO AUXILIAR E RETORNA-O*/
product new_product() {
    strcpy(aux.description, input[0]);
    aux.price=atoi(input[1]);
    aux.weight=atoi(input[2]);
    aux.stock=atoi(input[3]);
    return aux;
}

/*USANDO O PRODUTO AUXILIAR ADICIONAMO-LO AO VETOR DE PRODUTOS E INCREMENTAMOS O NMR DE PRODUTOS DO MESMO, INDICE DO VETOR*/
void add_product() {
    products[idp_product]=aux;
    aux.id_product=idp_product;
    idp_product++;
    printf("Novo produto %d.\n", aux.id_product);
}

/*ADICIONA STOCK A UM PRODUTO*/
void add_stock() {
    int idp=0, stock=0;
    idp=atoi(input[0]);
    stock=atoi(input[1]);
    if(idp>=idp_product) printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else {
        products[idp].stock+=stock;
    }
}

/*ADICIONA UMA ENCOMENDA AO VETOR DE ENCOMENDAS E INCREMENTA O NMR DE ENCOMENDAS, INDICE DO VETOR*/
void new_order() {
    orders[ide_order]=other_aux;
    other_aux.n_order=ide_order;
    ide_order++;
    printf("Nova encomenda %d.\n", other_aux.n_order);
}

/*ADICIONA O PRODUTO A UMA ENCOMENDA, PRIMEIRO CONFIRMA O STOCK, DEPOIS O PESO E DEPOIS VE SE O PRODUTO JA EXISTE NA ENCOMENDA. 
SE EXISTIR APENAS ADICIONA O STOCK, SE NAO EXISTIR ADICIONA O PRODUTO A ULTIMA POSICAO DO VETOR ENCOMENDAS*/
int add_product_to_order() {
    int ide=0, idp=0, stock=0, i=0;
    ide=atoi(input[0]);
    idp=atoi(input[1]);
    stock=atoi(input[2]);
    if(ide>=ide_order) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return 0;
    }
    if(idp>=idp_product) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return 0;
    }
    if(products[idp].stock>=stock) {
        if(((products[idp].weight)*stock)+orders[ide].weight<=200) {
            for(i=0; i<orders[ide].n_product; i++) {
                if(orders[ide]._product_[i].id_product==idp) {
                    strcpy(orders[ide]._product_[i].description,products[idp].description);
                    orders[ide]._product_[i].price=products[idp].price;
                    orders[ide]._product_[i].weight+=(products[idp].weight)*stock;
                    orders[ide]._product_[i].stock+=stock;
                    products[idp].stock-=stock;
                    break;
                }
            }
            if(i==orders[ide].n_product) { 
                strcpy(orders[ide]._product_[orders[ide].n_product].description,products[idp].description);
                orders[ide]._product_[orders[ide].n_product].price=products[idp].price;
                orders[ide]._product_[orders[ide].n_product].weight=(products[idp].weight)*stock;
                orders[ide]._product_[orders[ide].n_product].stock=stock;
                orders[ide]._product_[orders[ide].n_product].id_product=idp;
                products[idp].stock-=stock;
                orders[ide].n_product++;
            }
        }
        else printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return 0;
    }
    else printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return 0;
}

/*REMOVE STOCK A UM PRODUTO*/
int remov_stock() {
    int stock=0, idp=0;
    idp=atoi(input[0]);
    stock=atoi(input[1]);
    if(idp>=idp_product) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return 0;
    }
    if(products[idp].stock-stock<0) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock, idp);
        return 0;
    }
    else products[idp].stock-=stock;
    return 0;
}

/*REMOVE UM PRODUTO DE UMA ENCOMENDA, CRIANDO UMA VARIAVEL VAZIA QUE SUBSTITUI A ANTERIOR E LIBERTA A POSICAO DO VETOR*/
int remov_product() {
    int ide=0, idp=0, i=0, vazio_int={0};
    char vazio_char[]={0};
    ide=atoi(input[0]);
    idp=atoi(input[1]);
    if(ide>=ide_order) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return 0;
    }
    if(idp>=idp_product) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return 0;
    }
    for(i=0; i<orders[ide].n_product; i++) {
        if(orders[ide]._product_[i].id_product==idp) {
            strcpy(orders[ide]._product_[i].description, vazio_char);
            orders[ide]._product_[i].price=vazio_int;
            orders[ide]._product_[i].weight=vazio_int;
            orders[ide]._product_[i].stock=vazio_int;
            orders[ide]._product_[i].id_product=vazio_int;   
            orders[ide].n_product--;
            orders[ide]._product_[i]=orders[ide]._product_[i-1];
            break;
        }
        return 0;
    }
    return 0;
}

/*CALCULA O CUSTO DE UMA ENCOMENDA*/
void calc_c(int ide) {
    int custo=0, i=0;
    if(ide>=ide_order) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else {
        for(i=0; i<=orders[ide].n_product; i++) {
            custo+=((orders[ide]._product_[i].stock)*(orders[ide]._product_[i].price));
        }
        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}

/*MUDA O PRE?O DE UM PRODUTO, APENAS SUBSTITUI PELO NOVO DADO NO INPUT*/
void change_price() {
    int idp=0, price=0;
    idp=atoi(input[0]);
    price=atoi(input[1]);
    if(idp>=idp_product) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else {
        products[idp].price=price;
    }
}

/*DADO UMA ENCOMENDA E UM PRODUTO LISTA A QUANTIDADE E A DESCRICAO DO MESMO*/
void desc_stock_product() {
    int ide=0, idp=0;
    ide=atoi(input[0]);
    idp=atoi(input[1]);
    if(ide>=ide_order) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    if(idp>=idp_product) printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else {
        printf("<%s> <%d>", orders[ide]._product_[idp].description, orders[ide]._product_[idp].stock);
    }
}

/*TESTA QUAL A ENCOMENDA EM QUE O PRODUTO DADO TEM MAIOR STOCK, USANDO UMA VARIAVEL AUXILIAR PARA GUARDAR O MAX DE QUANTIDADE 
E O MAXIMO, OU SEJA, O INDICE DA ENCOMENDA EM QUE O MESMO ACONTECE*/
void ide_product_more_often(int idp) {
    int i=0, max=-1, max_quant=0, j=0;
    if(idp>=idp_product) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    for(i=0; i<ide_order; i++) { 
        for(j=0; j<orders[i].n_product; j++) {
            if(orders[i]._product_[j].id_product==idp) {
                if(orders[i]._product_[j].stock>max_quant) {
                    max_quant=orders[i]._product_[j].stock;
                    max=i;
                }
            }
            if(orders[i]._product_[j].id_product!=idp || i<0) break;
        }
    }
    if(max==-1) return;
    else printf("Maximo produto %d %d %d.\n", idp, max, max_quant);
}   

/*USEI O INSERTION PARA ORDENAR, PELO PRECO*/
void insertion() {
    int j=0,i=0;
    product v;
    for(i=0; i<idp_product; i++) {
        v=products[i];
        j=i-1;
        while(j>=0 && (products[j].price>v.price)) {
            products[j+1]=products[j];
            j--;
        }
    products[j+1]=v;
    }
}

/*FUNCAO PARA LISTAR OS PRODUTOS PELO PRECO*/
void list_products() {
    int i=0;
    printf("Produtos\n");
    for(i=0; i<idp_product; i++) {
        printf("* %s %d %d\n", products[i].description, products[i].price, products[i].stock);
    }
}

/*void insertion1(int ide) {
    int j=0,i=0;
    product v;
    for(i=0; i<orders[ide].n_product; i++) {
        v=products[i];
        j=i-1;
        while(j>=0 && ('a'>'b'>'c'>'d'>'e'>'f'>'g'>'h'>'i'>'j'>'k'>'l'>'m'>'n'>'o'>'p'>'q'>'r'>'s'>'t'>'u'>'w'>'x'>'y'>'z')) {
            products[j+1]=products[j];
            j--;
        }
    products[j+1]=v;
    }
}

void list_orders(int ide) {
    int i=0;
    if(ide>=ide_order) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else {
        printf("Encomenda %d\n", ide);
        for(i=0; i<orders[ide].n_product; i++) {
        printf("* %s %d %d\n", orders[ide]._product_[i].description, orders[ide]._product_[i].price, orders[ide]._product_[i].stock);
        }
    }
}*/