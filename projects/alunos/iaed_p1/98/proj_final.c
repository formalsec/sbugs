#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*limites maximos*/
#define DESCRMAX 64   
#define PRODMAX 10000
#define ENCMAX 500 
#define LISTMAX 200
#define PESOMAX 200

/*forma de ordenacao*/
#define PRECO 0
#define ALFA 1

/*elementos de cada sub-array do array a ordenar*/
#define ELS 2

/*conteudo de um indice num sub-array*/
#define ID 0
#define QTD 1


/*ESTRUTURAS UTILIZADAS*/

/*Um produto e caracterizado por uma descricao, um preco, um peso
*e uma quantidade em stock
*/
typedef struct {

    char descr[DESCRMAX];
    int preco;
    int peso;
    int stock;

} produto;

/*Uma compra e caracterizada por um identificador e por uma quantidade
 *do produto associado
*/
typedef struct {

    int id_prod;
    int quant;

} compra;

/*Uma encomenda e caracterizada por uma lista de compras, pelo numero de
 *compras e pelo seu peso
*/
typedef struct {

    compra lista[LISTMAX];
    int peso;
    int num_compras;

} encomenda;


/*VARIAVEIS GLOBAIS*/

/*sistema de produtos (tabela com todos os produtos)*/
produto sist_prods[PRODMAX];

/*sistema de encomendas (tabela com todas as encomendas)*/
encomenda sist_encs[ENCMAX];

/*numero de elementos de cada um dos sistemas*/
int prod_max;
int enc_max;


/*PROTOTIPOS DE FUNCOES*/

/*Construir*/
produto cria_produto(char descr[DESCRMAX], int preco, int peso, int stock);
encomenda cria_enc_vazia(void);

/*Adicionar*/
int add_produto(void);
void add_stock(void);
int add_encomenda(void);
void add_prod_encomenda(void);

/*Remover*/
void remove_stock(void);
void remove_prod_encomenda(void);

/*Calcular*/
void calcula_custo_enc(void);
int qtd_prod_enc(int id_prod,int id_enc);

/*Alterar*/
void change_preco(void);

/*Mostrar*/
void lista_info_prod(void);
void lista_prod_ordenados(void);
void lista_prod_enc_alfa(void);

/*Procurar*/
int find_prod_encomenda(int id_prod,int id_enc);
void enc_max_prod(void);

/*Ordenar*/
void mergesort(int lista[][ELS],int low,int high,int modo);

/*Funcoes auxiliares*/
void merge(int lista[][ELS],int low,int med,int high,int modo);
int compare(int id1,int id2,int modo);


/*MAIN:Processa cada comando dado*/
int main() {

    char ch_menu;

    while(1){

        ch_menu = getchar();

        switch(ch_menu){

            case 'a': 
                add_produto();
                break;

            case 'q':
                add_stock();
                break;

            case 'N':
                add_encomenda();
                break;

            case 'A':
                add_prod_encomenda();
                break;

            case 'r':
                remove_stock();
                break;

            case 'R':
                remove_prod_encomenda();
                break;

            case 'C':
                calcula_custo_enc();
                break;

            case 'p':
                change_preco();
                break;

            case 'E':
                lista_info_prod();
                break;

            case 'm':
                enc_max_prod();
                break;

            case 'l':
                lista_prod_ordenados();
                break;

            case 'L':
                lista_prod_enc_alfa();
                break;
            
            /*terminar interacao*/
            case 'x':
                return 0;

            default:break;
        
        }

    }

    /*ocorrencia inesperada*/
    return -1;

}

/*funcao que recebe uma descricao (string), um preco, um peso e uma quantidade
em stock e retorna o produto com essas caracteristicas*/
produto cria_produto(char descr[DESCRMAX], int preco, int peso, int stock) {

    produto prod_aux;

    strcpy(prod_aux.descr,descr);
    prod_aux.preco=preco;
    prod_aux.peso=peso;
    prod_aux.stock=stock;

    return prod_aux;

}

/*cria uma encomenda vazia (sem produtos e sem peso)*/
encomenda cria_enc_vazia(void) {

    encomenda enc_aux;
    enc_aux.peso=0;
    enc_aux.num_compras = 0;

    return enc_aux;

}

/*Adiciona um produto ao sistema e retorna o numero total de produtos*/
int add_produto(void) {

    char descr[DESCRMAX];
    int preco, peso, stock;
    
    scanf(" %[^:]:%d:%d:%d",descr,&preco,&peso,&stock);

    sist_prods[prod_max]=cria_produto(descr,preco,peso,stock);

    printf("Novo produto %d.\n",prod_max);

    return ++prod_max;
}

/*Adiciona uma quantidade de stock introduzida pelo utilizador
 *a um produto existente no sistema
*/
void add_stock(void){

    int id_prod,qtd;

    scanf(" %d:%d",&id_prod,&qtd);

    /*se nao existir produto criado com o id*/
    if (id_prod>=prod_max){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id_prod);
        return ;
    }

    /*atualizar no sistema quantidade do produto em stock*/
    sist_prods[id_prod].stock+=qtd;

    return ;
    
}

/*Adiciona uma encomenda vazia ao sistema e retorna o total de encomendas*/
int add_encomenda(void){

    sist_encs[enc_max]=cria_enc_vazia();

    printf("Nova encomenda %d.\n",enc_max);

    return ++enc_max;
}

/*Retorna o indice de um id de um produto numa certa encomenda,
 *dada pelo seu id, retorna -1 se a encomenda nao contiver o produto
*/
int find_prod_encomenda(int id_prod, int id_enc){

    int i;
    encomenda enc_aux;

    /*encomenda a analisar*/
    enc_aux=sist_encs[id_enc];

    for(i=0;i<enc_aux.num_compras;i++){
        
        if(enc_aux.lista[i].id_prod==id_prod){
            return i;
        }

    }

    return -1;
}

/*Adiciona uma quantidade de produto a uma encomenda*/
void add_prod_encomenda(void){

    int id_enc,id_prod,qtd;
    int novo_peso;
    int indice;

    encomenda enc_aux;      /*encomenda em questao*/
    produto prod_aux;       /*produto em questao*/

    scanf(" %d:%d:%d",&id_enc,&id_prod,&qtd);

    if (id_enc>=enc_max){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_enc);
        return ;
    }

    if (id_prod>=prod_max){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id_prod,id_enc);
        return ;
    }

    /*se a quantidade requerida for superior ao stock do produto*/
    if (qtd>sist_prods[id_prod].stock){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id_prod,id_enc);
        return ;
    }

    enc_aux=sist_encs[id_enc];
    prod_aux=sist_prods[id_prod];

    /*calcular peso da encomenda*/
    novo_peso=(enc_aux.peso)+qtd*(prod_aux.peso);

    /*se exceder limite*/
    if (novo_peso>PESOMAX){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n",id_prod,id_enc,PESOMAX);
        return ;
    }

    indice=find_prod_encomenda(id_prod,id_enc);

    /*se se encontrou o produto na encomenda, atualizar quantidade*/
    if(indice!=-1){
        sist_encs[id_enc].lista[indice].quant+=qtd;
    }

    /*se nao, adicionar produto com a quantidade e atualizar numero de compras da encomenta*/
    else{
        enc_aux=sist_encs[id_enc];
        sist_encs[id_enc].lista[enc_aux.num_compras].id_prod=id_prod;
        sist_encs[id_enc].lista[enc_aux.num_compras].quant=qtd;
        sist_encs[id_enc].num_compras++;
    }

    /*atualizar stock no sistema de produtos*/
    sist_prods[id_prod].stock-=qtd;

    /*atualizar peso da encomenda e numero de compras na encomenda*/
    sist_encs[id_enc].peso=novo_peso;

    return ;

}

/*Remove uma quantidade de stock de um produto do sistema*/
void remove_stock(void){

    int id_prod,qtd;

    scanf(" %d:%d",&id_prod,&qtd);

    if (id_prod>=prod_max){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id_prod);
        return ;
    }

    if (qtd>sist_prods[id_prod].stock){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,id_prod);
        return ;
    }

    sist_prods[id_prod].stock-=qtd;

    return ;

}

/*Remove um produto de uma encomenda*/
void remove_prod_encomenda(void){

    int id_prod,id_enc;
    int indice,qtd;

    scanf(" %d:%d",&id_enc,&id_prod);

    if (id_enc>=enc_max){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_enc);
        return ;
    }

    if (id_prod>=prod_max){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id_prod,id_enc);
        return ;
    }

    /*enc_aux=sist_encs[id_enc];*/
    indice=find_prod_encomenda(id_prod,id_enc);

    /*se encontrou o produto na encomenda*/
    if (indice!=-1){

        /*guardar quantidade existente do produto a eliminar*/
        qtd=sist_encs[id_enc].lista[indice].quant;

        /*colocar qtd do produto na encomenda a 0*/
        sist_encs[id_enc].lista[indice].quant=0;

        /*atualizar peso da encomenda*/
        sist_encs[id_enc].peso-=(sist_prods[id_prod].peso*qtd);

        /*atualizar quantidade do produto em stock no sistema de produtos*/
        sist_prods[id_prod].stock+=qtd;

    }

    return ;

}

/*Calcula o custo de uma encomenda a partir de um identificador introduzido*/
void calcula_custo_enc(void){

    encomenda enc_aux;
    compra compra_aux;
    produto prod_aux;
    int i,id_enc;
    int total=0;

    scanf(" %d",&id_enc);

    if(id_enc>=enc_max){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id_enc);
        return ;
    }

    /*aceder ah encomenda a partir do sistem*/
    enc_aux=sist_encs[id_enc];
    
    for(i=0;i<enc_aux.num_compras;i++){

        /*analisar cada compra da encomenda individualmente*/
        compra_aux=enc_aux.lista[i];

        /*aceder ao preco do produto de uma compra no sistema*/
        prod_aux=sist_prods[compra_aux.id_prod];

        total+=(prod_aux.preco)*(compra_aux.quant);

    }

    printf("Custo da encomenda %d %d.\n",id_enc,total);

    return ;

}

/*Altera o preco de um produto a partir de um identificador introduzido*/
void change_preco(void){

    int preco,id_prod;

    scanf(" %d:%d",&id_prod,&preco);

    if(id_prod>=prod_max){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id_prod);
        return ;
    }

    sist_prods[id_prod].preco=preco;

    return ;
}

/*Lista a descricao e quantidade de um produto dado por um identificador numa
 *encomenda dada por um identificador
*/
void lista_info_prod(void){

    encomenda enc_aux;
    compra compra_aux;
    produto prod_aux;
    int id_prod,id_enc,indice;
    
    scanf(" %d:%d",&id_enc,&id_prod);

    if(id_enc>=enc_max){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_enc);
        return ;
    }

    if(id_prod>=prod_max){
        printf("Impossivel listar produto %d. Produto inexistente.\n",id_prod);
        return ;
    }

    /*encontrar indice da lista na compra associada ao produto*/
    indice=find_prod_encomenda(id_prod,id_enc);

    /*aceder ao produto pretendido a partir do sistema*/
    prod_aux=sist_prods[id_prod];

    /*se a encomenda tiver o produto*/
    if(indice!=-1){

        /*aceder ah encomenda a partir do sistema*/
        enc_aux=sist_encs[id_enc];

        /*aceder ah compra pretendedida*/
        compra_aux=enc_aux.lista[indice];

        printf("%s %d.\n",prod_aux.descr,compra_aux.quant);
    
    }

    /*caso contrario, mostrar quantidade a 0*/
    else{
        printf("%s %d.\n",prod_aux.descr,0);
    }
   
    return ;

}

/*Lista o id da encomenda em que um produto dado por um identificador ocorre mais vezes*/
void enc_max_prod(void){

    int id_prod;
    int id_enc,qtd;
    int id_enc_max=0;
    int qtd_max=0;

    scanf(" %d",&id_prod);

    if(id_prod>=prod_max){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_prod);
        return ;
    }

    /*percorrer cada encomenda no sistema*/
    for(id_enc=0;id_enc<enc_max;id_enc++){

        /*aceder ah encomenda no sistema*/
        qtd=qtd_prod_enc(id_prod,id_enc);

        if (qtd>qtd_max){
            qtd_max=qtd;
            id_enc_max=id_enc;
        }

    }

    /*se nenhuma encomenda analisada tinha o produto, nao retornar nada*/ 
    if (qtd_max==0){
        return ;
    }

    printf("Maximo produto %d %d %d.\n",id_prod,id_enc_max,qtd_max);

    return ;

}

/*Retorna a quantidade de um produto numa dada encomenda*/
int qtd_prod_enc(int id_prod,int id_enc){

    encomenda enc_aux;
    compra compra_aux;
    int i;

    /*Aceder a encomenda a partir do sistema*/
    enc_aux=sist_encs[id_enc];

    for(i=0;i<enc_aux.num_compras;i++){

        /*Aceder a cada compra na encomenda*/
        compra_aux=enc_aux.lista[i];

        /*Se o id do produto corresponder, retorna quantidade*/
        if(compra_aux.id_prod==id_prod){
            return compra_aux.quant;
        }
    }

    /*Se o produto nao existir na encomenda*/
    return 0;

}

/*Ordena um array de id's de produtos, tendo dois modos:
    PRECO-> de acordo com o seu preco;
    ALFA->alfabeticamete(pela sua descricao)
*/
void mergesort(int lista[][ELS],int low,int high,int modo){

    int med=(low+high)/2;

    /*base da recursao: nao se pode subdivir o array*/
    if(high<=low){
        return ;
    }

    /*aplicar mergesort a cada uma das metades do array*/
    mergesort(lista,low,med,modo);
    mergesort(lista,med+1,high,modo);

    /*merge dos dois arrays ja ordenados*/
    merge(lista,low,med,high,modo);

    return ;

}

/*Junta num so array ordenado as duas metades ordenadas*/
void merge(int lista[][ELS],int low, int med,int high,int modo){

    /*criar array auxiliar que junta cada metade*/
    int aux[PRODMAX][ELS];
    int i,j,k,status;

    /*construir array auxiliar*/
    for(i=med+1;i>low;i--){
        aux[i-1][ID]=lista[i-1][ID];
        aux[i-1][QTD]=lista[i-1][QTD];
    }

    for(j=med;j<high;j++){
        aux[high+med-j][ID]=lista[j+1][ID];
        aux[high+med-j][QTD]=lista[j+1][QTD];
    }

    /*merge*/
    for(k=low;k<=high;k++){

        status=compare(aux[j][ID],aux[i][ID],modo);

        if(status<0){
            lista[k][ID]=aux[j][ID];
            lista[k][QTD]=aux[j][QTD];
            j--;
        }

        /*em caso de igualdade de preco, colocar produto com menor id*/
        else if(status==0){

            if(aux[j][ID]<aux[i][ID]){
                lista[k][ID]=aux[j][ID];
                lista[k][QTD]=aux[j][QTD];
                j--;
            }

            else{
                lista[k][ID]=aux[i][ID];
                lista[k][QTD]=aux[i][QTD];
                i++;
            }

        }

        else{
            lista[k][ID]=aux[i][ID];
            lista[k][QTD]=aux[i][QTD];
            i++;
        }
    }

    return ;

}

/*Compara dois produtos, ou pelo preco ou pela descricao*/
int compare(int id1,int id2,int modo){

    produto prod1=sist_prods[id1];
    produto prod2=sist_prods[id2];

    if(modo==PRECO){

        if(prod1.preco<prod2.preco){
            return -1;
        }

        else if(prod1.preco==prod2.preco){
            return 0;
        }

        else{
            return 1;
        }
    }

    /*caso alfabetico*/
    else{
    
        if(strcmp(prod1.descr,prod2.descr)<0){
            return -1;
        }

        else if(strcmp(prod1.descr,prod2.descr)==0){
            return 0;
        }

        else{
            return 1;
        }
    }

}

/*Lista todos os produtos no sistema por ordem crescente de preco*/
void lista_prod_ordenados(void){

    /*lista auxiliar com os id's produtos a ordenar*/
    int lista[PRODMAX][ELS];
    int i;
    produto prod_aux;

    printf("Produtos\n");

    /*copiar id's dos produtos para a lista
    Despreza-se o segundo indice com as quantidades*/
    for(i=0;i<prod_max;i++){
        lista[i][ID]=i;
    }

    /*ordenar id's de acordo com o preco dos produtos correspodentes*/
    mergesort(lista,0,prod_max-1,PRECO);

    for(i=0;i<prod_max;i++){
        
        /*aceder ah informacao do produto no sistema e lista-la*/
        prod_aux=sist_prods[lista[i][ID]];
        printf("* %s %d %d\n",prod_aux.descr,prod_aux.preco,prod_aux.stock);
    }

    return ;
}

/*Lista todos os produtos de uma encomenda por ordem alfabetica*/
void lista_prod_enc_alfa(void){

    int id_enc,i,qtd;
    int lista[LISTMAX][ELS];
    encomenda enc_aux;
    produto prod_aux;

    scanf(" %d",&id_enc);

    if(id_enc>=enc_max){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_enc);
        return ;
    }

    /*consultar encomenda no sistema*/
    enc_aux=sist_encs[id_enc];

    /*copiar para lista auxiliar id's ,juntamente com as qtds na encomenda*/
    for(i=0;i<enc_aux.num_compras;i++){
        lista[i][ID]=enc_aux.lista[i].id_prod;
        lista[i][QTD]=enc_aux.lista[i].quant;
    }

    /*Ordenar id's dos produtos alfabeticamente, pela descricao do produto*/
    mergesort(lista,0,enc_aux.num_compras-1,ALFA);
   
    printf("Encomenda %d\n",id_enc);

    /*Listar produtos da encomenda na forma descricao, preco, qtd*/
    for(i=0;i<enc_aux.num_compras;i++){

        /*consultar no sistema o produto com o id da compra*/
        prod_aux=sist_prods[lista[i][ID]];
        
        qtd=lista[i][QTD];

        if(qtd>0){
            printf("* %s %d %d\n",prod_aux.descr,prod_aux.preco,qtd);
        }

    }

    return ;

}









