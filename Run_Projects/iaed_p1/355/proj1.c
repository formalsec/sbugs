#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************/
/*Constantes*/
/************/

#define MAX_peso_produtos_encomenda 200
#define MAX_descricao 64
#define MAX_produtos 10000
#define MAX_encomendas 500

/************/
/*estruturas*/
/************/

struct product{
    int id;
    int peso;
    int preco;
    int quant;
    char descricao[MAX_descricao];
};

/**********************/
/*variaveis universais*/
/**********************/

struct product lista_produtos[MAX_produtos];   /*variavel que contem todos os produtos do sistema.*/
struct product encomendas[MAX_encomendas][MAX_peso_produtos_encomenda]; /*variavel que contem todas as encomendas.*/
struct product aux_produtos[MAX_produtos]; 
struct product aux_encomendas[MAX_peso_produtos_encomenda];
int idp_atual=0,ide_atual=0;    /*variaveis que guardam o identificador da proxima encomenda e do proximo produto a serem criados,respetivamente.*/

void init(){
    int cont,cont2;
    for(cont=0;cont<MAX_produtos;cont++)
        lista_produtos[cont].preco = 0;
    for(cont=0;cont<MAX_encomendas;cont++)
        for(cont2=0;cont2<MAX_peso_produtos_encomenda;cont2++)
            encomendas[cont][cont2].preco = 0;
}

/**********************/
/*funcoes de ordenacao*/
/**********************/

void merge_produtos(struct product produtos[],int l_inf,int meio, int l_sup){
    int i,j,k;
    for(i=meio+1;i>l_inf;i--)
        aux_produtos[i-1] = produtos[i-1];
    for(j=meio;j<l_sup;j++)
        aux_produtos[l_sup+meio-j] = produtos[j+1];
    for(k=l_inf;k<=l_sup;k++){
        if(aux_produtos[j].preco < aux_produtos[i].preco || (aux_produtos[j].preco == aux_produtos[i].preco && aux_produtos[j].id < aux_produtos[i].id))
            produtos[k] = aux_produtos[j--];
        else
            produtos[k] = aux_produtos[i++];
    }
}

void mergesort_produtos(struct product produtos[],int l_inf,int l_sup){
    int meio =(l_sup+l_inf)/2;
    if (l_sup <= l_inf) return;
    mergesort_produtos(produtos,l_inf,meio);
    mergesort_produtos(produtos,meio+1,l_sup);
    merge_produtos(produtos,l_inf,meio,l_sup);

}

void merge_encomenda(struct product encomenda[],int l_inf,int meio, int l_sup){
    int i,j,k;
    for(i=meio+1;i>l_inf;i--)
        aux_encomendas[i-1] = encomenda[i-1];
    for(j=meio;j<l_sup;j++)
        aux_encomendas[l_sup+meio-j] = encomenda[j+1];
    for(k=l_inf;k<=l_sup;k++){
        if(strcmp(aux_encomendas[j].descricao,aux_encomendas[i].descricao)<0)
            encomenda[k] = aux_encomendas[j--];
        else
            encomenda[k] = aux_encomendas[i++];
    }
}


void mergesort_encomendas(struct product encomenda[],int l_inf,int l_sup){
    int meio=(l_sup+l_inf)/2;
    if (l_sup <= l_inf) return;
    mergesort_encomendas(encomenda,l_inf,meio);
    mergesort_encomendas(encomenda,meio+1,l_sup);
    merge_encomenda(encomenda,l_inf,meio,l_sup);
}

/********************/
/*funcoes auxiliares*/
/********************/

int peso_encomenda(int id){
    int i,peso_total=0;
    for(i=0;i<MAX_peso_produtos_encomenda;i++){
        if(encomendas[id][i].preco == 0)
            break;
        else
            peso_total += (encomendas[id][i].peso)*(encomendas[id][i].quant);
    }
    return peso_total;
}

int produto_na_encomenda(int idp,int ide){
    /*Esta funcao retorna 1 se o produto em questao se encontra na encomenda referida, 
    e 0 caso contrario.*/
    int cont;
    for(cont=0;cont<MAX_peso_produtos_encomenda;cont++)
        if(encomendas[ide][cont].id == idp && encomendas[ide][cont].preco != 0)
            return 1;
    return 0;
}

/**********/
/*comandos*/
/**********/

void a(){
    /*Esta funcao adiciona um novo produto ao stock.*/
    struct product produto;
    scanf(" %[^:]:%d:%d:%d",produto.descricao,&produto.preco,&produto.peso,&produto.quant);
    produto.id = idp_atual;
    lista_produtos[idp_atual] = produto;
    printf("Novo produto %d.\n",idp_atual);
    idp_atual ++;
}

void q(){
    /*Esta funcao adiciona uma certa quantidade a um produto no stock.*/
    int id,qtd;
    scanf("%d:%d",&id,&qtd);
    if(id>=idp_atual)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
    else
        lista_produtos[id].quant += qtd;
}

void N(){
    /*Esta funcao cria uma nova encomenda.*/
    printf("Nova encomenda %d.\n",ide_atual);
    ide_atual++;
}

void A(){
    /*Esta funcao adiciona uma certa quantidade de um produto a uma encomenda.*/
    int ide,idp,qtd;
    scanf("%d:%d:%d",&ide,&idp,&qtd);
    if(ide>=ide_atual)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if(idp>=idp_atual)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else if(qtd > lista_produtos[idp].quant)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
    else if((peso_encomenda(ide)+ qtd*lista_produtos[idp].peso)> MAX_peso_produtos_encomenda)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
    else if(produto_na_encomenda(idp,ide)){
        int i;
        for(i=0;i<MAX_peso_produtos_encomenda;i++){
            if(encomendas[ide][i].id == idp && encomendas[ide][i].preco != 0){
                encomendas[ide][i].quant += qtd;
                lista_produtos[idp].quant -= qtd;
                return;
            }
        }
    }
    else{
        int i;
        for(i=0;i<MAX_peso_produtos_encomenda;i++){
            if(encomendas[ide][i].preco == 0){
                encomendas[ide][i] = lista_produtos[idp];
                encomendas[ide][i].quant = qtd;
                lista_produtos[idp].quant -= qtd;
                return;
            }
        }
    }

}

void r(){
    /*Esta funcao remove stock a um produto existente*/
    int idp,qtd;
    scanf("%d:%d",&idp,&qtd);
    if(idp>=idp_atual)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
    else if(lista_produtos[idp].quant  < qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
    else
        lista_produtos[idp].quant -= qtd;
}

void R(){
    /*Esta funcao remove um produto de uma determinada encomenda.*/
    int ide,idp;
    scanf("%d:%d",&ide,&idp);
    if(ide>=ide_atual)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if(idp>=idp_atual)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else{
        int i,j;
        struct product produto;
        for(i=0;i<MAX_peso_produtos_encomenda;i++){
            if(encomendas[ide][i].id == idp && encomendas[ide][i].preco != 0){
                encomendas[ide][i].preco = 0;
                lista_produtos[idp].quant += encomendas[ide][i].quant;
                break;
            }
        }
        for(j=i;j<MAX_peso_produtos_encomenda-1;j++){
            if(encomendas[ide][j+1].preco == 0)
                return;
            else{
                produto = encomendas[ide][j];
                encomendas[ide][j] = encomendas[ide][j+1];
                encomendas[ide][j+1] = produto;
            }
        }
    }
}

void C(){
    /*Esta funcao calcula o custo de uma determinada encomenda.*/
    int ide;
    scanf("%d",&ide);
    if(ide>=ide_atual)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    else{
        int i,custo=0;
        for(i=0;i<MAX_peso_produtos_encomenda;i++){
            if (encomendas[ide][i].preco == 0)
                break;
            else
                custo += (encomendas[ide][i].preco)*(encomendas[ide][i].quant);
        }
        printf("Custo da encomenda %d %d.\n",ide,custo);
    }
}

void p(){
    /*Esta funcao altera o preco de um produto no sistema.*/
    int idp,new_preco;
    scanf("%d:%d",&idp,&new_preco);
    if(idp>=idp_atual)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    else{
        int i,j;
        lista_produtos[idp].preco = new_preco;
        for(i=0;i<ide_atual;i++){
            for(j=0;j<MAX_peso_produtos_encomenda;j++){
                if(encomendas[i][j].preco == 0)
                    break;
                else if(encomendas[i][j].id == idp){
                    encomendas[i][j].preco = new_preco;
                    break;
                }
            }
        }
    }
}
void E(){
    /*Esta funcao retorna a descri??o e a quantidade de um produto numa dada encomenda*/
    int ide,idp;
    scanf("%d:%d",&ide,&idp);
    if(ide>=ide_atual)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else if(idp>=idp_atual)
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
    else if(!(produto_na_encomenda(idp,ide)))
        printf("%s 0.\n",lista_produtos[idp].descricao);
    else{
        int i;
        for(i=0;i<MAX_peso_produtos_encomenda;i++){
            if(encomendas[ide][i].preco == 0)
                return;
            else if(encomendas[ide][i].id == idp){
                printf("%s %d.\n",encomendas[ide][i].descricao,encomendas[ide][i].quant);
                return;
            }
        }
    }
}

void m(){
    /*Esta funcao retorna o identificador da encomenda em que um dado produto ocorre mais vezes.*/
    int idp;
    scanf("%d",&idp);
    if(idp>=idp_atual)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    else{
        int i,j,maior_qtd=0,ide=0;
        for(i=0;i<ide_atual;i++){
            for(j=0;j<MAX_peso_produtos_encomenda;j++){
                if(encomendas[i][j].preco == 0)
                    break;
                else if(encomendas[i][j].id==idp && ((encomendas[i][j].quant>maior_qtd) || (encomendas[i][j].quant==maior_qtd && i<ide))){
                    ide = i;
                    maior_qtd = encomendas[i][j].quant;
                }
            }
        }
        if(maior_qtd != 0)
            printf("Maximo produto %d %d %d.\n",idp,ide,maior_qtd);
    }
}

void l(){
    /*Esta funcao lista todos os produtos existentes no sistema por ordem crescente de preco.*/
    int i;
    struct product produtos[MAX_produtos];
    for(i=0;i<idp_atual;i++)
        produtos[i] = lista_produtos[i];
    printf("Produtos\n");
    mergesort_produtos(produtos,0,idp_atual-1);
    for(i=0;i<idp_atual;i++)
        printf("* %s %d %d\n",produtos[i].descricao,produtos[i].preco,produtos[i].quant);
    
}

void L(){
    /*Esta funcao lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o.*/
    int ide;
    scanf("%d",&ide);
    if(ide>=ide_atual)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else{
        int limit,i;
        struct product encomenda[MAX_peso_produtos_encomenda];
        for(i=0;i<MAX_peso_produtos_encomenda;i++){
            if(encomendas[ide][i].preco == 0)
                break;
            else
                encomenda[i] = encomendas[ide][i];
        }
        limit = i;
        printf("Encomenda %d\n",ide);
        mergesort_encomendas(encomenda,0,limit-1);
        for(i=0;i<limit;i++)
            printf("* %s %d %d\n",encomenda[i].descricao,encomenda[i].preco,encomenda[i].quant);
        
    }
}


/*******************/
/*corpo do programa*/
/*******************/

int main()
{
    char comando;
    init();
    comando = getchar();
    while(comando != 'x'){
        switch (comando){
            case 'a':
                a();
                break;
            case 'q':
                q();
                break;
            case 'N':
                N();
                break;
            case 'A':
                A();
                break;
            case 'r':
                r();
                break;
            case 'R':
                R();
                break;
            case 'C':
                C();
                break;
            case 'p':
                p();
                break;
            case 'E':
                E();
                break;
            case 'm':
                m();
                break;
            case 'l':
                l();
                break;
            case 'L':
                L();
                break;
            }
        comando = getchar();
    }
    return 0;
}
