#include <stdio.h>
#include <string.h> 

#define MAXPRODUTOS 10000  /*n?mero m?ximo de produtos*/
#define MAXENCOMENDAS 500  /*n?mero m?ximo de encomendas*/
#define MAXPESO 200        /*peso m?ximo de uma encomenda*/
#define MAXDESCRICAO 64    /*n?mero m?ximo de caracteres da descri??o de produtos*/

/*Def estrutura de dados */
typedef struct {
        int idp; /*identificador do produto */
        char descricao[MAXDESCRICAO];/*nome do produto */
        int preco;/*preco do produto */
        int peso;/* peso do produto*/
        int stock;/* numero de unidades em stock*/
}Produto;

Produto inventario[MAXPRODUTOS]; /*vetor onde ir?o ser registados os produtos*/
Produto Encomendas[MAXENCOMENDAS][MAXPESO];/*Matriz onde ir?o ser registadas as encomendas e seus respetivos produtos*/
int idp,ide; /*idp e ide contam o numero de produtos e de encomendos registados, respetivamente */



/*prototipo*/
void adicionaProduto();                                          /*comando a*/
void adicionaStock();                                            /*comando q*/
void criaEncomenda();                                            /*comando N*/
void adicionaProdEncomenda();                                    /*comando A*/
void removeStock();                                              /*comando r*/
void removeProdEncomenda();                                      /*comando R*/
void calculaCustoEncomenda();                                    /*comando C*/
void alteraPreco();                                              /*comando p*/
void listaDescricaoQtdProd();                                    /*comando E*/
void listaIdpEncomendaProdMaisVezes();                           /*comando m*/
void listaProdExistentesPreco();                                 /*comando l*/
void listaProdAlfaDescricao();                                   /*comando L*/
void inicializa();                                               /*funcao que inicializa a matriz de encomendas*/    
int calculapesoencomenda(int iden,int pesototal,int i);          /*funcao que calcula o peso de uma encomenda*/
void bubblel(Produto a[], int left, int right);                  /*funcao sort para o comando l*/
int lesspreco(Produto i,Produto j);                              /*funcao auxiliar da funcao bubblel*/
void swap(Produto i,Produto j);                                  /*funcao auxiliar dos sorts*/
void bubbleL(Produto a[], int left, int right);                  /*funcao sort para o comando L*/
int lessalfabeto(Produto i, Produto j);                          /*funcao auxiliar da funcao bubbleL*/

/*main*/ 
int main(){
    char comando = ' ';    /*variavel que ir? definir o comando a ser executado*/
    inicializa();          /*inicializa??o da matriz de encomendas*/
    while (comando != 'x') 
    {
        scanf("%c",&comando);
        switch (comando)
        {
        case 'a':
            adicionaProduto();
            break;
        
        case 'q':
            adicionaStock();
            break;
        
        case 'N':
            criaEncomenda();
            break;
        case 'A':
            adicionaProdEncomenda();
            break;
        case 'r':
            removeStock();
            break;
        case 'R':
            removeProdEncomenda();
            break;
        case 'C':
            calculaCustoEncomenda();
            break;
        case 'p':
            alteraPreco();
            break;
        case 'E':
            listaDescricaoQtdProd();
            break;
        case 'l':
            listaProdExistentesPreco();
            break;
        
        case 'm':
            listaIdpEncomendaProdMaisVezes();
            break; 
        
        case 'L':
            listaProdAlfaDescricao();
            break;
        case 'x':
            break;
        }
    }
    return 0; 
}    

void adicionaProduto(){         /*funcao que recebe uma descricao, um preco um peso e uma quantidade e armazena-a num indice do vetor invent?rio vazio*/
    int i;
    for ( i = 0; i <= idp; i++)
    {
        if (inventario[i].peso == 0)
        {
           break; 
        }
        
    }
    inventario[i].idp=idp;
    scanf(" %[^:]:%d:%d:%d", inventario[i].descricao, &inventario[i].preco, &inventario[i].peso, &inventario[i].stock);
    printf("Novo produto %d.\n",idp);
    idp++;
}


void adicionaStock(){               /*funcao que recebe um id e uma quantidade qtd e caso exista um produto id no sistema, adiciona essa quantidade ao seu stock.*/
    int id,qtd,i;
    scanf("%d:%d",&id,&qtd);
    if (id >= idp ) 
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);      /*caso o produto n?o existe a funcao imprime erro*/
        return;
    }
    for(i=0; i < idp ;i++)
    {
        if (inventario[i].idp == id)            /*este ciclo ir? aparecer imensas vezes: ? este que permite percorrer o vetor invent?rio de modo a encontrar o id do produto em quest?o e de seguida obter o par?metro relevante ? opera??o a efetuar   */
        {   inventario[i].stock += qtd;
            break;
        }
    }
}

void criaEncomenda(){                           /*funcao que cria uma nova encomenda, o que corresponde a incrementar a vari?vel que conta as encomendas criadas, ide*/
    printf("Nova encomenda %d.\n",ide);
    ide++;
}

void adicionaProdEncomenda(){               /*funcao que cria uma nova encomenda, recebe o numero da encomenda, o id do produto e a quantidade a adicionar */
    int iden,id,qtd,pesototal,i,j;
    pesototal = 0;                          /*uma vez que uma encomenda tem um peso m?ximo de PESOMAX, ? necess?rio criar uma vari?vel de modo a garantir que a encomenda n?o exceda este peso  */
    i=0;
    scanf("%d:%d:%d",&iden,&id,&qtd);
    if (iden >= ide)                                    /*caso n?o tenho sido criada uma encomenda com identificador iden, a funcao retorna um erro*/
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id,iden);
        return;
    }

    if (id >= idp)                              /*caso o produto n?o exista a funcao  imprime erro*/
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id,iden);
        return;
    }
    for (j = 0; j < idp; j++)
    {                                             
        if (inventario[j].idp == id)
        {
            if (inventario[j].stock < qtd)              /*verifica se existe quantidade suficiente em stock, caso n?o exista imprime erro*/
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id,iden); 
              return; 
            }
            break;
        }
    }
    calculapesoencomenda(iden,pesototal,i);         /*salta para a funcao que calcula o pesototal de uma encomenda iden*/
    pesototal += (qtd * inventario[j].peso);        /* verifica se ao adicionar a quantidade de produto id nao excede o peso max  */
    if (pesototal > MAXPESO)                        /*se exceder imprime erro*/
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id,iden);
        return;   
    }
    for ( i = 0; i < idp; i++)     /*ciclo que testa se o produto j? se encontra na encomenda*/
    {
        if ((Encomendas[iden][i].idp) == inventario[j].idp)
        {                                                           /*caso o produto j? se encontre na encomenda, apenas ? necess?rio atualizar a sua quantidade*/
            Encomendas[iden][i].stock += qtd;
            inventario[j].stock -= qtd ;
            return;
        }
    }
    for ( i = 0; i < idp; i++) /*ciclo que encontra uma posicao vazia na encomenda*/
    {
        if ((Encomendas[iden][i].stock) == 0 )       /*caso o produto n?o esteja na encomenda, ele ? inserido na primeira posi??o livre da encomenda, que corresponde a uma posi??o com quantidade 0 */
        {   
            Encomendas[iden][i].idp = inventario[j].idp ;
            Encomendas[iden][i].stock = qtd;
            inventario[j].stock -= qtd ;
            Encomendas[iden][i].peso = inventario[j].peso;
            Encomendas[iden][i].preco = inventario[j].preco ;
            strcpy(Encomendas[iden][i].descricao,inventario[j].descricao);
            break;
        }
    }
    
}

void removeStock(){                             /*funcao que remove uma quantidade qtd do produto id*/
    int id,qtd,i;
    scanf("%d:%d",&id,&qtd);
    if (id >= idp)                              
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id);
        return;
    }
    for ( i = 0; i < idp ; i++)
    {                                           /*obtem a posicao do produto no vetor */
        if (inventario[i].idp == id)
        {
            break;
        }
    }
    
    if (qtd > inventario[i].stock )         /*verifica se a quantidade que se deseja remover ? superior ? existente */
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd , id);
        return;
    }
    inventario[i].stock -= qtd;                 /*caso n?o o seja remove essa quantidade ao stock do produto*/
}


void removeProdEncomenda(){   /*funcao que remove um produto de uma encomenda, o que eu escolhi que corresponde a reduzir o seu stock a 0 dentro da encomenda */
    int id,iden,i,j;
    scanf("%d:%d",&iden,&id);
    if (iden >= ide)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id,iden); 
        return;
    }
    if (id >= idp)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id,iden);
        return;
    }
    for ( i = 0; i < idp; i++)
    {
        if (inventario[i].idp == id)
        {
            break;
        }
    }
    for ( j = 0; j < idp; j++)                                          
    {
        if (Encomendas[iden][j].idp ==id)
        {
            break;
        }
    }
    inventario[i].stock += Encomendas[iden][j].stock ;        /*adiciona a quantidade presente na encomenda ? quantidade do produto em invent?rio */
    Encomendas[iden][j].stock = 0;
}
void calculaCustoEncomenda(){               /*funcao que calcula o custo de uma encomenda*/
    int iden,total,i;
    total=0;
    scanf("%d",&iden);
    if (iden >= ide)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",iden);
        return;
    }
    for ( i = 0; i < idp; i++)              /*percorre a encomenda calculando o preco de todos os seus produtos tendo em conta a quantidade e adiciona ? vari?vel total */
    {
        total += (Encomendas[iden][i].preco * Encomendas[iden][i].stock) ;
    }
    printf("Custo da encomenda %d %d.\n",iden,total);
}
void alteraPreco(){                    /*funcao que altera o preco de um determinado produto */
    int id,preco,i,j;
    scanf("%d:%d",&id,&preco);

    if (id >= idp)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id);
        return;
    }
    for ( i = 0; i < idp; i++)                      /*altera o preco do produto id no vetor inventario*/
    {
        if (inventario[i].idp == id)        
        {
            inventario[i].preco = preco;
            break;
        }
    }
    for ( i = 0; i < ide; i++)                          /*altera o preco nas encomendas que contenham o produto id */
    {
        for ( j = 0; j < idp ; j++)
        {
            if (Encomendas[i][j].idp == id)
            {
                Encomendas[i][j].preco = preco;
                break;
            }
        }
    }
}
void listaDescricaoQtdProd(){       /*Funcao que lista a descricao e a quantidade de um produto id numa encomenda iden */
    int iden,id,i;
    scanf("%d:%d",&iden,&id);
    if (iden >= ide)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",iden);
        return;
    }
    if (id >= idp)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n",id);
        return;
    }
    for ( i = 0; i < idp; i++)                          /*pesquisa na encomenda a posicao do produto id*/
    {
        if (Encomendas[iden][i].idp == id)
        {
            break;
        }
    }
    printf("%s %d.\n",Encomendas[iden][i].descricao,Encomendas[iden][i].stock);
}

void listaProdExistentesPreco(){   /*Funcao que lista os produtos por ordem crescente do seu preco */
    int i;
    bubblel(inventario,0,idp);     /*para esta funcao recorri a um bubble sorte para organizar o vetor invent?rio*/
    printf("Produtos\n");
    for ( i = 0; i < idp; i++)
    {
        printf("* %s %d %d\n",inventario[i].descricao,inventario[i].preco,inventario[i].stock);
        
    }
}
void bubblel(Produto a[], int left, int right)
{
    int i, j, done;
    for (i = left; i < right; i++){
        done=1;                                 
        for (j = right; j > i; j--)
            if (lesspreco(a[j], a[j-1]))
            {
                swap(a[j-1] , a[j]);
                done=0;
            }
        if (done) break;
        }
}
int lesspreco(Produto i,Produto j){

    if (i.preco > j.preco)          
    {
        return 0;
    }
    if (i.preco < j.preco)
    {
        return 1;
    }
    if (i.preco == j.preco)
    {
        if (i.idp < j.idp)
        {
            return 1;
        }
    }
    return 0;
}

void swap(Produto i,Produto j){
    Produto k;
    strcpy(k.descricao,i.descricao);
    k.peso = i.peso;
    k.preco = i.preco;
    k.stock = i.stock;
    k.idp = i.idp;
    i.peso = j.peso;
    i.preco = j.preco;
    i.stock = j.stock;
    i.idp = j.idp;
    strcpy(i.descricao,j.descricao);
    j.idp = k.idp;
    j.stock = k.stock;
    j.preco = k.preco;
    j.peso = k.peso;
    strcpy(j.descricao,k.descricao);
    
}

void listaIdpEncomendaProdMaisVezes(){      /*funcao que lista o iden em que o produto id ocorre mais vezes */
    int id,i,j,max,aux;
    max=0;                                   /*para esta funcao recorri a duas variaveis, em que numa armazeno (aux) a encomenda que tem mais produto id e na outra (max) o numero dessas ocorrencias, assim posso percorrer todas as encomendas e no final o indice aux ser? a encomenda que procuramos */
    aux=0;
    scanf("%d",&id);
    if (id >= idp)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id);
        return;
    }
    if (ide == 0)
    {
        return;
    }
    
    for ( i = 0; i < ide; i++)
    {
        for ( j = 0; j < idp; j++)
        {
            if (Encomendas[i][j].idp == id)
            {
             if (Encomendas[i][j].stock > max)
             {
                aux = i;
                max= Encomendas[i][j].stock;
             }
             else if (Encomendas[i][j].stock == max && max != 0 )
             {
                 if (aux>i)
                 {                      
                     aux=i;                                 /*caso a quantidade seja a mesma, a que permance ? a com menor indice*/
                 }
                 
             }
                    
            }
            
        }
    if (max != 0)        /*Se a variavel max for sempre 0 significa que nenhuma encomenda contem esse produto e entao a funcao nao retorna nada*/
    {
        printf("Maximo produto %d %d %d\n",id,aux,max);
    }
        
    }
       


} 

void listaProdAlfaDescricao(){   /* funcao que lista os produtos numa encomenda por ordem alfab?tica*/
    int iden,i;
    scanf("%d",&iden);
    if (iden >= ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",iden);
        return;
    }
    bubbleL(Encomendas[iden],0,idp);            /*recorri a um bubble sort para esta funcao */
    printf("Encomenda %d\n",iden);
    for ( i = 0; i < idp; i++)
    {
        if (Encomendas[iden][i].stock != 0)    /*produtos com quantidade 0 numa encomenda n?o s?o lidos*/
        {
        printf("* %s %d %d\n",Encomendas[iden][i].descricao, Encomendas[iden][i].preco,Encomendas[iden][i].stock);
        }
    }
    
    

} 
void bubbleL(Produto a[], int left, int right)
{
    int i, j, done;
    for (i = left; i < right; i++){
        done=1;
        for (j = right; j > i; j--)
            if (lessalfabeto(a[j], a[j-1]))
            {
                swap(a[j-1] , a[j]);
                done=0;
            }
        if (done) break;
        }
}

int lessalfabeto(Produto i, Produto j){
    if (strcmp(i.descricao,j.descricao) < 0) /* i.descricao for menor que j.descricao corresponde a ter de haver troca de indices */
    {
        return 1;
    }
    return 0;
}

void inicializa(){
    int i,j ;               /*inicializa as encomendas */
    idp=0;
    ide=0;
    
    for ( i = 0; i < MAXENCOMENDAS; i++)
    {
        for ( j = 0 ; j < MAXPESO ; j++)
        {
            Encomendas[i][j].idp = -1 ;
            Encomendas[i][j].peso = 0 ;
            Encomendas[i][j].preco = 0 ;
            Encomendas[i][j].stock = 0 ; 
        }
        
    }
}
int calculapesoencomenda(int iden,int pesototal,int i){
    for ( i = 0 ; i < idp ; i++)
    {
        pesototal = pesototal + Encomendas[iden][i].stock * Encomendas[iden][i].peso ;
    }
    return pesototal;
}