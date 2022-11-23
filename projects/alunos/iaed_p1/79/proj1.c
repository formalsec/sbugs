#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IDP 100000
#define MAX_DESC 63
#define MAX_ENCOMENDAS 500
#define MAX_PRODUTOS 100000
#define MAX_PESO 200


typedef struct produto{
    int id;
    char desc[MAX_DESC];
    int preco;
    int peso;
    int stock;
}produto;
    

typedef struct encomenda_info{
    /*o stock no produto da encomenda indica a quantidade desse produto na encomenda diferente do conceito stock do sistema*/
    struct produto produtos[MAX_PESO];
    /*indica o indice onde vai ser adicionada o proximo produto e indica o numero de produtos diferentes na encomenda*/
    int ponteiro;
    /*peso total da encomenda*/
    int peso;
    /*custo total da encomenda*/
    int custo;
}encomenda_info;

/*contar num produtos*/
int tam_sistema;
/*contar o numero de encomendas*/
int ide_atual;  
/*id da encomenda id do produto quantidade*/   
int ide,idp,qtd;
int custo,preco;
/*variaveis usadas para ciclos for e while*/
int i,k,j;
/*vetor para colocar os produtos no sistema*/
produto sistema[MAX_PRODUTOS];
/*vetor com encomendas e cada encomenda e um vetor onde vai ter os produtos */
encomenda_info encomendas[MAX_ENCOMENDAS];  
/*funcoes principais*/
void adiciona_produtos();
void adiciona_stock();
void cria_nova_encomenda();
void adiciona_produto_encomenda();
void remover_stock_produto();
void remover_produto_encomenda();
void custo_encomenda();
void alterar_preco_produto();
void lista_descricao();
void max_produto();
void listar_produtos();
void listar_produtos_encomenda();

/*funcoes auxiliares*/
void resetar_produto_da_encomenda(int ide,int id_ide);
void acertar_lista(int ide, int idp);
int listar_encomendas(int, int idp);
int verifica_menor(char a[], char b[]);
void merge_sort_sistema(int esquerda, int direita,int a[],int aux[]);
void merge_sort_encomenda(int esquerda, int direita,int ide, int a[], int aux[]);
void merge_encomenda(int esquerda, int meio, int direita, int ide , int a[],int aux[]);
void merge_sistema(int esquerda, int meio, int direita, int a[],int aux[]);


/*int menor(Item a[],int ide,int i,int j);*/
int main(){
    char c;
    c=getchar();
    while(c!='x'){
        
        switch(c){
            case 'a':
                adiciona_produtos();
                break;
            case 'q':
                adiciona_stock();
                break;
            case 'N':
                cria_nova_encomenda();
                break;
            case 'A':
                adiciona_produto_encomenda();
                break;
            case 'r':
                remover_stock_produto();
                break;
            case 'R':
                remover_produto_encomenda();
                break;
            case 'C':
                custo_encomenda();
                break;
            case 'p':
                alterar_preco_produto();
                break;
            case 'E':
                lista_descricao();
                break;
            case 'm':
                max_produto();
                break;
            case 'l':
                listar_produtos();
                break;
            case 'L':
                listar_produtos_encomenda();
                break;
        }
    c=getchar();
    }
return 0;
}

/*adiciona um novo produto ao sistema*/
void adiciona_produtos(){
    scanf(" %[^:]:%d:%d:%d\n",sistema[tam_sistema].desc, &sistema[tam_sistema].preco, &sistema[tam_sistema].peso,&sistema[tam_sistema].stock);
    sistema[tam_sistema].id=tam_sistema;
    tam_sistema++;
    printf("Novo produto %d.\n",tam_sistema-1);
}

/*adiciona stock a um produto existente no sistema*/
void adiciona_stock(){
    scanf("%d:%d\n",&idp,&qtd);
    if( idp >= MAX_IDP || sistema[idp].peso==0)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
    
    sistema[idp].stock+=qtd;
}

/*cria uma nova encomenda*/
void cria_nova_encomenda(){
    printf("Nova encomenda %d.\n",ide_atual);
    /*aponta para um novo indice vazio do vetor encomendas e conta o numero de encomendas criadas*/
    ide_atual++;

}

/*adiciona um produto a uma encomenda*/
void adiciona_produto_encomenda(){
    int total_peso=0,id_ide;
    int stock;
    scanf("%d:%d:%d\n",&ide, &idp, &qtd);
    /*calcular o susposto stock do sistema para depois verificar se temos quantidade suficiente desse produto para adicionar ? encomenda*/
    stock=sistema[idp].stock-qtd;
    /*suposto peso total que vai servir para verificar se podemos ou nao adicionar o produto a encomenda consoante o peso exceda ou nao os 200*/
    total_peso+=encomendas[ide].peso+(sistema[idp].peso*qtd);
    if( (ide >= ide_atual))
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if((idp >= tam_sistema))
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else if(stock<0)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
    else if(total_peso>MAX_PESO)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
    else if(listar_encomendas(ide, idp)!=201){
        id_ide=listar_encomendas(ide, idp);
        encomendas[ide].produtos[id_ide].stock+=qtd;
        encomendas[ide].peso=total_peso;
        strcpy(encomendas[ide].produtos[id_ide].desc,sistema[idp].desc );
        remover_stock_produto(idp,qtd);
    }
    else{
        encomendas[ide].produtos[encomendas[ide].ponteiro]=sistema[idp];
        /* o stock do produto na encomenda indica o numero desse produto no cesto e diferente do significado para o stock do sistema*/
        encomendas[ide].produtos[encomendas[ide].ponteiro].stock=qtd;
        strcpy(encomendas[ide].produtos[encomendas[ide].ponteiro].desc, sistema[idp].desc );
        encomendas[ide].peso=total_peso;
        /* atualiza o ponteiro para o indice do proximo produto a adicionar*/
        encomendas[ide].ponteiro++; 
        remover_stock_produto(idp,qtd);
    }
}

/*remove stock a um produto existente*/
void remover_stock_produto(){
    scanf("%d:%d\n",&idp,&qtd);
    if(idp>=tam_sistema)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
    
    else if(qtd>sistema[idp].stock)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
    else
        /*atualiza o stock do produto x no sistema*/
        sistema[idp].stock-=qtd;
        
}

/*identificar o indice do produto no vetor das encomendas consoante o ide e o idp*/
int listar_encomendas(int ide, int idp){
    /*ler todas as encomendas criadas*/
    for(i=0;i<ide_atual;i++)
        if(i==ide){
            /*ler todos os produtos da encomenda*/
            for(k=0;k<encomendas[i].ponteiro;k++)
                /*verificar se o id do produto da encomenda e igual ao id do produto */
                if(encomendas[i].produtos[k].id==idp){
                    return k;
                }
        }
    /*como a encomenda tem no maximo 200 produtos entao e seguro retornar 201 porque k nunca tera esta valor*/
    return 201;
}

/*remove um produto de uma encomenda*/
void remover_produto_encomenda(){
    /*indice do produto, a remover, na encomenda*/
    int id_ide;
    scanf("%d:%d\n",&ide,&idp);
    if(ide>=ide_atual)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    else if(idp>=tam_sistema)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    else{
        /*id do produto selecionado a ser removido na encomenda*/
        id_ide=listar_encomendas(ide, idp);
        if(id_ide!=201){
            sistema[idp].stock+=encomendas[ide].produtos[id_ide].stock;
            /*atualizar peso da encomenda*/
            encomendas[ide].peso-=(encomendas[ide].produtos[id_ide].stock)*(encomendas[ide].produtos[id_ide].peso);
            /*colocar toda a informacao do antigo produto a a zero */
            resetar_produto_da_encomenda(ide,id_ide);
            acertar_lista(ide, idp);
        }
    }
}

/* tirar os espacos vazios do vetor encomenda na parte dos produtos deixados pelo remover_produto_encomenda*/
void acertar_lista(int ide, int idp){       
    int indice1;
    indice1=listar_encomendas(ide,idp);
    for(;indice1<=(encomendas[ide].ponteiro-2);indice1++){
            encomendas[ide].produtos[indice1].id=encomendas[ide].produtos[indice1+1].id;
            encomendas[ide].produtos[indice1].peso=encomendas[ide].produtos[indice1+1].peso;
            encomendas[ide].produtos[indice1].stock=encomendas[ide].produtos[indice1+1].stock;
            encomendas[ide].produtos[indice1].preco=encomendas[ide].produtos[indice1+1].preco;
            strcpy(encomendas[ide].produtos[indice1].desc,encomendas[ide].produtos[indice1+1].desc);
        }
    encomendas[ide].ponteiro=encomendas[ide].ponteiro-1;
}

void resetar_produto_da_encomenda(int ide,int id_ide){
    for(i=0;i<MAX_DESC;i++)
        /*resetar descricao*/
        encomendas[ide].produtos[id_ide].desc[i]=0;
    
    encomendas[ide].produtos[id_ide].stock=0;
    encomendas[ide].produtos[id_ide].preco=0;
    encomendas[ide].produtos[id_ide].peso=0;
}

/*calcula o custo de uma encomenda*/
void custo_encomenda(int ide){
    int custo_total=0;
    scanf("%d\n",&ide);
    if(ide>=ide_atual)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    else{
        /*ler todos os produtos da encomenda*/
        for(k=0;k<encomendas[ide].ponteiro;k++)
            custo_total+=encomendas[ide].produtos[k].stock*(encomendas[ide].produtos[k].preco); 
        
        encomendas[ide].custo=custo_total;
        printf("Custo da encomenda %d %d.\n", ide, encomendas[ide].custo);
        }
}
/*alterar o preco do produto tanto no sistema como em cada encomenda*/
void alterar_preco_produto(){
    scanf("%d:%d", &idp, &preco);
    if(idp>=tam_sistema)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    else{
        sistema[idp].preco=preco;
        /*ler todas as encomendas criadas*/
        for(i=0;i<ide_atual;i++)
            /*ler todos os produtos da encomenda*/
            for(k=0;k<encomendas[i].ponteiro;k++)
                /*verificar se o id do produto da encomenda e igual ao id do produto onde o preco mudou caso seja atualiza o preco do produto na encomenda*/
                if(encomendas[i].produtos[k].id==idp){
                    encomendas[i].produtos[k].preco=sistema[idp].preco;
                }
    }
}
/*retorna a descri??o e a quantidade de um produto numa dada encomenda*/
void lista_descricao(){
    scanf("%d:%d",&ide,&idp);
    if(ide >= ide_atual)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else if(idp >= tam_sistema)
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
    else
        if(listar_encomendas(ide,idp)!=201)
            /*este stock refere a quantidade desse produto na encomenda e nao ao stock no sistema*/
            printf("%s %d.\n",sistema[idp].desc,encomendas[ide].produtos[listar_encomendas(ide,idp)].stock);
        else
            /*caso o produto nao esteja na encomenda*/
            printf("%s %d.\n",sistema[idp].desc,0);
}

/*retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/
void max_produto(){
    /*a variavel dentro tem como objetivo ver se existe alguma encomenda com idp*/
    int max_produto=0,max_ide,dentro=0;
    scanf("%d",&idp);
    if(idp >= tam_sistema)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    else{
        /*ler encomendas*/
        for(i=0;i < ide_atual;i++)
            /*ler os produtos de forma a encotrar o idp escolhido*/                             
            for(k=0;k < encomendas[i].ponteiro;k++ ){ 
                /*verifica no primeiro caso se o produto da encomenda tem o mesmo id do idp*/              
                if(encomendas[i].produtos[k].id==idp && encomendas[i].produtos[k].stock>max_produto){
                   /*desta forma mesmo que haja duas encomendas com a mesma quantidade a com o ide mais baixa e a escolhida uma vez que o ciclo for esta a ler as encomendas por ordem de ide*/
                    max_produto=encomendas[i].produtos[k].stock;    
                    max_ide=i; 
                    dentro=1;                                                                                                         
                }
            }

        if(dentro==1)
            printf("Maximo produto %d %d %d.\n",idp,max_ide,max_produto);
    }
}

/*lista todos os produtos existentes no sistema por ordem crescente de pre?o*/
void listar_produtos(){
    /*vetor com os idps*/
    int v[MAX_PRODUTOS];
    /*vetor auxiliar no merge sort*/
    int aux[MAX_PRODUTOS];
    for(i=0;i<tam_sistema;i++){
        v[i]=i;
    }
    merge_sort_sistema(0, tam_sistema-1,v,aux);
    printf("Produtos\n");
    for(i=0;i<tam_sistema;i++)
        printf("* %s %d %d\n",sistema[v[i]].desc,sistema[v[i]].preco,sistema[v[i]].stock);
}

/*funcao que vai ordenar os produtos no sistema*/
void merge_sort_sistema(int esquerda, int direita, int a[], int aux[]) {         
    int meio = (esquerda + direita) / 2;
    if (direita <= esquerda)
        return;     
    
    merge_sort_sistema(esquerda, meio, a, aux);   
    merge_sort_sistema(meio + 1, direita, a, aux);    
    merge_sistema(esquerda,meio,direita,a,aux);
}
void merge_sistema(int esquerda, int meio, int direita, int a[],int aux[]){ 
  for (i = meio+1; i > esquerda; i--) 
    aux[i-1] = a[i-1];
  for (j = meio; j < direita; j++)
    aux[direita+meio-j] = a[j+1];
  for (k = esquerda; k <= direita; k++)
    if (sistema[aux[j]].preco<sistema[aux[i]].preco || i > meio)
      a[k] = aux[j--];
    else
      a[k] = aux[i++];
}



/*ordenar as encomenas alfabeticamente*/
void listar_produtos_encomenda(){
    int tamanho;
    /*vetor que vai servir para ordenar as encomendas pelos seus ides*/
    int vetor[MAX_PESO];
    int aux[MAX_PESO];
    scanf("%d",&ide);
    tamanho=encomendas[ide].ponteiro;
    if(ide>=ide_atual)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    else{
        for(i=0;i<tamanho;i++)
            vetor[i]=i;
        
        merge_sort_encomenda(0,tamanho-1,ide,vetor,aux);
        printf("Encomenda %d\n",ide);
        for(i=0;i<tamanho;i++)
            printf("* %s %d %d\n",encomendas[ide].produtos[vetor[i]].desc,encomendas[ide].produtos[vetor[i]].preco,encomendas[ide].produtos[vetor[i]].stock);
    }
}

/*algoritmo que vai ordenar os produtos da encomenda por ordem alfabetica da descricao*/
void merge_sort_encomenda(int esquerda, int direita,int ide, int a[], int aux[]) {         
    int meio = (esquerda + direita) / 2;
    if (direita <= esquerda)
        return;     
    
    merge_sort_encomenda(esquerda, meio,ide,a, aux);   
    merge_sort_encomenda(meio + 1, direita,ide, a, aux);    
    merge_encomenda(esquerda,meio,direita,ide,a,aux);
}
void merge_encomenda(int esquerda, int meio, int direita, int ide , int a[],int aux[]){
 
  for (i = meio+1; i > esquerda; i--) 
    aux[i-1] = a[i-1];
  for (j = meio; j < direita; j++)
    aux[direita+meio-j] = a[j+1];
  for (k = esquerda; k <= direita; k++)
    if ((verifica_menor(encomendas[ide].produtos[aux[j]].desc,encomendas[ide].produtos[aux[i]].desc))<0 || i > meio)
      a[k] = aux[j--];
    else
      a[k] = aux[i++];
}

int verifica_menor(char a[], char b[]){
    int i=0,comp=0;
    while(comp==0 && i<63){   
        comp=a[i]-b[i];/*o strcmp entre caracteres estava a dar erro dai eu ter feito assim*/
        i++;

    }
    return comp;
}
