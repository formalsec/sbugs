#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define max_pro 10000  /*numero maximo de produtos no sistema*/
#define max_enc 500    /*numero maximo de encomendas no sistema*/
#define max_p_enc 200  /*peso maximo por encomenda/max de produtos por encomenda*/
#define max_char 64    /*tamanho maximo da descricao de uma encomenda*/
#define not_in -1      /*variavel de selecao caso um produto esteja fora da encomenda*/
int np=0,ne=0;         /*numero de produtos / numero de encomendas*/
int sair=1;            /*variavel de paragem do programa*/

struct produto{        /*estrutra dos produtos do sistema*/
    int idp;
    char descricao[max_char];
    int preco;
    int peso;
    int stock;    
};
    
struct encomenda{       /*estrutura das encomendas do sistema*/
    int ide;
    int preco;
    int peso;
    int n_p_d;
    struct produto lista_p_enc[max_p_enc]; /*lista de produtos na encomenda*/
};

struct encomenda lista_e[max_enc];  /*lista de todas as encomendas*/
struct produto lista_p[max_pro];    /*lista de todos os produtos*/
struct produto p1;                  /*produto tipo*/
struct encomenda e1;                /*encomenda tipo*/

 /*verifica se um produto(idp) pertence a encomenda(ide)*/
int in_encomenda(int idp,int ide){    
    int i;
    for (i = 0; i < lista_e[ide].n_p_d; i++){
        if (lista_e[ide].lista_p_enc[i].idp==idp){
            return i;
        }   
    }
    return not_in;
}

/*troca as encomendas/produtos de posicao*/
void troca(struct produto lista[],int i,int r){  
    struct produto p4;
    p4=lista[i];
    lista[i]=lista[r];
    lista[r]=p4;
}

/*compara a descricao(k=0) ou o preco (k=1)*/
int ord_p_or_l(struct produto p2, struct produto p3,int k){ 
    if(k==0){
        return strcmp(p2.descricao,p3.descricao)<0;
    }
    else{
        if(p2.preco==p3.preco)
            return (p2.idp<p3.idp);
        return p2.preco<p3.preco;
    }
}

/*divide a lista a odernar pelo quicksort*/
int divisao(struct produto lista[],int l,int r,int k){  
    int a=l-1;
    int b=r;
    struct produto p2=lista[r];
    while(a<b){
        while(ord_p_or_l(lista[++a],p2,k));
        while(ord_p_or_l(p2,lista[--b],k))
            if(b==l)
            break;
        if(a<b)
            troca(lista,a,b);
    }
    troca(lista,a,r);
    return a;
}

/*quick sort*/
void q_s(struct produto lista[],int l,int r,int k){ 
    int i;
    if(r<=l)
        return;
    i=divisao(lista,l,r,k);
    q_s(lista,l,i-1,k);
    q_s(lista,i+1,r,k);
}



/*cria um produto novo em p1 e guarda-o na lista de produtos*/
void a(){    
    int idp; 
    scanf(" %[^:]:%d:%d:%d",p1.descricao,&p1.preco,&p1.peso,&p1.stock);
    idp=np;
    p1.idp=idp;
    lista_p[p1.idp]=p1;
    np++;
    printf("Novo produto %d.\n",p1.idp);
}

/*adiciona stock(qtd) ao produto(idp)*/
void q(){  
    int idp,qtd; 
    scanf("%d:%d",&idp,&qtd);
    if(idp>=np)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
    else{
        lista_p[idp].stock+=qtd;
    }
}

 /*cria uma encomenda nova em e1 e guarda-a na lista de encomendas*/
void N(){ 
    int ide; 
    ide=ne;
    e1.ide=ide;
    e1.preco=0;
    e1.peso=0;
    e1.n_p_d=0;
    lista_e[e1.ide]=e1;
    ne++;
    printf("Nova encomenda %d.\n",e1.ide);
}

/*adiciona a encomenda(ide) o produto(idp) com quantidade(stock)*/
void A(){  
    int ide,idp,qtd; 
    scanf("%d:%d:%d",&ide,&idp,&qtd);
    if(ide>=ne)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if (idp>=np)
       printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else if (qtd>lista_p[idp].stock)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
    else if (lista_e[ide].peso+(lista_p[idp].peso*qtd)>max_p_enc)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
    else if (in_encomenda(idp,ide)==not_in){ /*se o produto ainda nao existe na encomenda cria um novo espaco para ele*/
        lista_e[ide].lista_p_enc[lista_e[ide].n_p_d]=lista_p[idp];
        lista_e[ide].lista_p_enc[lista_e[ide].n_p_d].stock=qtd;
        lista_e[ide].peso+=lista_p[idp].peso*qtd;
        lista_p[idp].stock-=qtd;
        lista_e[ide].n_p_d++;
    }
    else{ /*se ja existe adiciona mais quantidade(qtd)*/
        lista_e[ide].lista_p_enc[in_encomenda(idp,ide)].stock+=qtd;
        lista_e[ide].peso+=lista_p[idp].peso*qtd;
        lista_p[idp].stock-=qtd;
    }
}

/*remove stock a um produto existente*/
void r(){ 
    int idp,qtd; 
    scanf("%d:%d",&idp,&qtd);
    if(idp>=np)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
    else if(qtd>lista_p[idp].stock)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
    else{
        lista_p[idp].stock-=qtd;
    }    
}

/*remove um produto existente a uma encomenda existente*/
void R(){ 
    int ide,idp;
    scanf("%d:%d",&ide,&idp);
    if(ide>=ne)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if (idp>=np)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else if(in_encomenda(idp,ide)!= not_in){ /*se o produto(idp) existe na encomenda(ide) remove-o(coloca o stock a 0)*/
        lista_p[idp].stock+=lista_e[ide].lista_p_enc[in_encomenda(idp,ide)].stock;
        lista_e[ide].peso-=lista_e[ide].lista_p_enc[in_encomenda(idp,ide)].stock*lista_p[idp].peso;
        lista_e[ide].lista_p_enc[in_encomenda(idp,ide)].stock=0;
    }
} 

/*calcula o custo de uma encomenda*/
void C(){ 
    int ide,i;
    scanf("%d",&ide);
    if(ide>=ne)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    else{
        lista_e[ide].preco=0;
        for (i=0;i<lista_e[ide].n_p_d;i++){
            if(lista_e[ide].lista_p_enc[i].stock!=0)
                lista_e[ide].preco+=lista_e[ide].lista_p_enc[i].preco*lista_e[ide].lista_p_enc[i].stock;     
        }
        printf("Custo da encomenda %d %d.\n",ide,lista_e[ide].preco);
    }
}

/*altera o preco de um produto existente*/
void p(){ 
    int idp,n_preco,j;
    scanf("%d:%d",&idp,&n_preco);
    if(idp>=np)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    else{
       lista_p[idp].preco=n_preco;
       for(j=0;j<ne;j++){ /*percorre todas as encomendas*/
           if(in_encomenda(idp,j)>=0){ /*se o produto existir dentro delas altera o seu preco*/
               lista_e[j].lista_p_enc[in_encomenda(idp,j)].preco=n_preco;
           }
       }     
    } 
}

/*imprime a quantidade de um produto existente(idp) numa encomenda existente(ide)*/
void E(){ 
    int idp,ide;
    scanf("%d:%d",&ide,&idp);
    if(ide>=ne)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else if(idp>=np)
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
    else if(in_encomenda(idp,ide)!=not_in){ /* se o produto existe na encomenda imprime a sua quantidade nesta*/
        printf("%s %d.\n",lista_p[idp].descricao,lista_e[ide].lista_p_enc[in_encomenda(idp,ide)].stock);
        }
    else{ /*se nao existe imprime 0*/
        printf("%s %d.\n",lista_p[idp].descricao,0);
    }
}

/*imprime a encomenda(ide) onde um produto existente(idp) aparece mais vezes*/
void m(){ 
    int idp,ide,max,a;
    scanf("%d",&idp);
    if(idp>=np)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    else{
        max=0;
        ide=-1; /*variavel de verificacao, permite verificar se o produto aparece em alguma encomenda*/ 
        for(a=0;a<ne;a++){
            if(in_encomenda(idp,a)!= not_in){
                if(lista_e[a].lista_p_enc[in_encomenda(idp,a)].stock>max){       /*comparacao apenas da True se for maior, pois os ide's ja estao por ordem crescente*/              
                    max= lista_e[a].lista_p_enc[in_encomenda(idp,a)].stock;
                    ide=a;
                }
            }
            }
        if (ide!=-1){
        printf("Maximo produto %d %d %d.\n",idp,ide,max);
        }
    }
}

/*imprime os produtos(descricao,preco,stock) do sistema por ordem crescente de preco e crescente idp caso tenham o mesmo preco*/    
void l(){ 
    struct produto lista_ord[max_pro];
    int k=1,i=0; /*k,variavel de selecao da comparacao no quicksort*/
    for (i=0;i<np;i++)
        lista_ord[i]=lista_p[i];
    q_s(lista_ord,0,np-1,k);
    printf("Produtos\n");
    for (i=0;i<np;i++)
        printf("* %s %d %d\n",lista_ord[i].descricao,lista_ord[i].preco,lista_ord[i].stock);
}

/*imprime os produtos(descricao,preco,quantidade na encomenda) de uma encomenda por ordem alfab?tica das descricoes*/
void L(){ 
    struct produto lista_ord[max_p_enc];
    int k=0,i,ide; /*k,variavel de selecao da comparacao no quicksort*/
    scanf("%d",&ide);
    if(ide>=ne)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else{
        for (i=0;i<lista_e[ide].n_p_d;i++)
            lista_ord[i]=lista_e[ide].lista_p_enc[i];
        q_s(lista_ord,0,lista_e[ide].n_p_d - 1,k);
        printf("Encomenda %d\n",ide);
        for (i=0;i<lista_e[ide].n_p_d;i++){ /*garante que os produtos com quantidade 0 dentro da encomenda(os que foram removidos) nao sao impressos*/
            if (lista_ord[i].stock>0)
                printf("* %s %d %d\n",lista_ord[i].descricao,lista_ord[i].preco,lista_ord[i].stock);
        }   
    }
}   

/* funcao main que manda executar as outras funcoes com base no input*/
int main(void){
    while(sair){      /*ciclo infinito que acaba com a mudanca da variavel sair para 0*/
        char c;  
        c=getchar();  /*le do terminal a letra correspondente ao comando*/
    switch(c){        /*associa essa letra a cada uma das funcoes que o sistema permite executar*/
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
        case 'x':
            sair=0; /*acaba o ciclo e o programa*/
            break;
        default:
            break;
        }
    }
    return 0;  
}


