#include <stdio.h>
#include <stdlib.h>

#define MAX_PESO 200    /*peso maximo de um produto*/    
#define MAX_TAM_STR 64  /*tam string + espaco para\0 */
#define MAX_PRODUTOS 10000  /*quantidade maxima de produtos diferentes*/
#define MAX_ENCOMENDAS 500  /*quantidade maxima de encomendas*/
#define MAX_PROD_POR_ENCOMENDA 200    /*quantidade maxima de produtos numa encomenda(como o peso e
                                      inteiro,entao, o peso minimo e 1, logo se a encomenda tiver
                                      100 desse produto, a encomenda pesaria 200)*/
#define MAX_CHAR_ID_PRODUTO 5 

typedef struct produto{
    /*o id do produto ? a sua posicao no vetor de produtos*/
    char descricao[MAX_TAM_STR];
    int preco,peso,stock;
}Produto;

typedef struct encomenda{
    int id,qnt;
}Encomenda;
/*listaProdutos
    -vetor onde e armazenada toda a informacao dos produtos
    -cada posicao corresponde a um produto, e o seu indice corresponde ao seu id
  listaEncomendas
    -vetor onde e armazenada toda a informacao das encomendas
    -cada linha corresponde a uma encomenda(primeiro indice)
    -cada coluna corresponde a uma unidade de um determinado produto
  listaSort
    -lista usada para a ordenacao do vetor de produtos
  tamListaProdutos
    -numero de produtos existentes
    -todos os produtos tem id menor que ele
  tamEncomenda
    -vetor onde e armazenada a quantidade de produtos total em cada encomenda
    -cada posicao corresponde ao id do encomenda de um produto
  tamListaEncomendas
    -numero de encomendas existentes*/
Produto listaProdutos[MAX_PRODUTOS];
Encomenda listaEncomendas[MAX_ENCOMENDAS][MAX_PROD_POR_ENCOMENDA];
int listaSort[MAX_PRODUTOS],tamListaProdutos=0,tamEncomenda[MAX_ENCOMENDAS],tamListaEncomendas=0;




void a(){
    int c,i;
    char preco[MAX_TAM_STR],peso[MAX_TAM_STR],stock[MAX_TAM_STR];
    
    /*para ignorar o espaco entre a opcao e o comando*/
    getchar();
    /*ciclos para receber os valores necessarios, e escrita da descricao logo
    no produto*/
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!=':'; i++){
        listaProdutos[tamListaProdutos].descricao[i] = c;
    }
    listaProdutos[tamListaProdutos].descricao[i] = '\0';
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!=':'; i++){
        preco[i]=c;
    }
    preco[i]='\0';
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!=':'; i++){
        peso[i]=c;
    }
    peso[i]='\0';
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!='\n'; i++){
        stock[i]=c;
    }
    stock[i]='\0';

    /*copia o que est? nas strings do input e converte para int e 
    passa as para o seu respetivo lugar no novo produto*/
    listaProdutos[tamListaProdutos].preco = atoi(preco);
    listaProdutos[tamListaProdutos].peso = atoi(peso);
    listaProdutos[tamListaProdutos].stock = atoi(stock);
    printf("Novo produto %d.\n",tamListaProdutos++);
}



void q(){
    int c,i;
    char idP[MAX_CHAR_ID_PRODUTO],qnt[MAX_TAM_STR];/*maximo do id do produto e 9999 + \0*/

    /*para ignorar o espaco entre a opcao e o comando*/
    getchar();
    /*ciclos para receber os valores necessarios*/
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!=':'; i++){
        idP[i]=c;
    }
    
    idP[i]='\0';
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!='\n'; i++){
        qnt[i]=c;
    }
    qnt[i]='\0';
    /*levantamento de erros*/
    if(atoi(idP) >= tamListaProdutos){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",atoi(idP));
        return;
    }
    else
        listaProdutos[atoi(idP)].stock += atoi(qnt);
}



void N(){
    /*inicializa os parametros da encomenda e aumenta o num de encomendas*/
    listaEncomendas[tamListaEncomendas][0].id = MAX_PRODUTOS;
    listaEncomendas[tamListaEncomendas][0].qnt = 0;
    tamEncomenda[tamListaEncomendas] = 0;
    printf("Nova encomenda %d.\n",tamListaEncomendas++);
}



/*funcao que devolve o peso de uma encomenda*/
int peso(int idE) {
    int i,idP,ret=0;
    for(i=0; i<tamEncomenda[idE]; i++){
        idP = listaEncomendas[idE][i].id;
        ret += (listaProdutos[idP].peso * listaEncomendas[idE][i].qnt);
    }
    return ret;
}

void A(){
    int c,i,pesoAdd,naEncomenda=0,indiceEncomenda;
    char idE[MAX_TAM_STR],idP[MAX_TAM_STR],qnt[MAX_TAM_STR];
    
    /*para ignorar o espaco entre a opcao e o comando*/
    getchar();
    /*ciclos para receber os valores necessarios*/
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!=':'; i++){
        idE[i] = c;
    }
    idE[i]='\0';
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!=':'; i++){
        idP[i]=c;
    }
    idP[i]='\0';
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!='\n'; i++){
        qnt[i]=c;
    }
    qnt[i]='\0';

    /*levantamento de erros*/
    if(atoi(idE) >= tamListaEncomendas){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",
        atoi(idP),atoi(idE));
        return;
    }
    else if(atoi(idP) >= tamListaProdutos){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",
        atoi(idP),atoi(idE));
        return;
    }

    if(atoi(qnt)==0){
            return;
    }   
    /*precorre a encomenda e se o produto:
        -estiver na encomenda
        adiciona a quantidade nova a atual na encomenda
        -nao estiver na encomenda
        preenche os parametros da encomenda e aumenta o tamanho dela*/
    for(i=0;i<tamEncomenda[atoi(idE)];i++){
        if(listaEncomendas[atoi(idE)][i].id == atoi(idP)){
            indiceEncomenda=i;
            naEncomenda=1;            
            break;
        }
    }

    /*variavel com o peso que sera adicionado pela adicao deste produto a encomenda*/
    pesoAdd=listaProdutos[atoi(idP)].peso * atoi(qnt);

    /*levantamento de erros*/
    if(atoi(qnt) > listaProdutos[atoi(idP)].stock){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",
        atoi(idP),atoi(idE)); 
        return;
    }
    else if(peso(atoi(idE))+pesoAdd > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",
        atoi(idP),atoi(idE)); 
        return;
        }
    else{
        if(naEncomenda){
            listaEncomendas[atoi(idE)][indiceEncomenda].id = atoi(idP);
            listaEncomendas[atoi(idE)][indiceEncomenda].qnt += atoi(qnt);
            listaProdutos[atoi(idP)].stock-=atoi(qnt);
        }
        /*se o produto nao existir na encomenda, aumentar o seu tamanho e passar
         o id do produto e a quantidade total para a encomenda*/
        else{
            listaEncomendas[atoi(idE)][tamEncomenda[atoi(idE)]].id=atoi(idP);
            listaEncomendas[atoi(idE)][tamEncomenda[atoi(idE)]].qnt = atoi(qnt);
            listaProdutos[atoi(idP)].stock-=atoi(qnt); 
            tamEncomenda[atoi(idE)]++;
        }
    }
}




void r(){
    int c,i;
    char idP[MAX_CHAR_ID_PRODUTO],qnt[MAX_TAM_STR];/*maximo do id do produto e 9999*/

    /*para ignorar o espaco entre a opcao e o comando*/
    getchar();
    /*ciclos para receber os valores necessarios*/
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!=':'; i++){
        idP[i]=c;
    }
    idP[i]='\0';
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!='\n'; i++){
        qnt[i]=c;
    }
    qnt[i]='\0';

    /*levantamento de erros*/
    if(atoi(idP) >= tamListaProdutos){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",atoi(idP));
        return;
    }
    else if(atoi(qnt) > listaProdutos[atoi(idP)].stock){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n"
        ,atoi(qnt),atoi(idP));
        return;
    }

    else
        listaProdutos[atoi(idP)].stock -= atoi(qnt);
}


void R(){
    int c,i,naEncomenda=-1;
    char idE[MAX_TAM_STR],idP[MAX_TAM_STR];
    Encomenda t;
    
    /*para ignorar o espaco entre a opcao e o comando*/
    getchar();
    /*ciclos para receber os valores necessarios*/
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!=':'; i++){
        idE[i] = c;
    }
    idE[i]='\0';
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!='\n'; i++){
        idP[i]=c;
    }
    idP[i]='\0';
    
    /*levantamento de erros*/
    if(atoi(idE) >= tamListaEncomendas){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",
        atoi(idP),atoi(idE));
        return;
    }
    else if(atoi(idP) >= tamListaProdutos){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",
        atoi(idP),atoi(idE));
        return;
    }

    else{  
        /*ciclo que procura o produto desejado*/
        for(i=0;i<tamEncomenda[atoi(idE)];i++){
            if(listaEncomendas[atoi(idE)][i].id == atoi(idP)){
                naEncomenda=i;
                break;
            }
        }
        if(naEncomenda >= 0){
            /*adiciona ao stock a quantidade da encomenda*/
            listaProdutos[atoi(idP)].stock += listaEncomendas[atoi(idE)][naEncomenda].qnt;
            /*passa se todos os produtos que vem a seguir na lista um lugar para tras
            -1(decremento de indice)*/
            for(i=naEncomenda;i<tamEncomenda[atoi(idE)]-1;i++){  
                t=listaEncomendas[atoi(idE)][i];
                listaEncomendas[atoi(idE)][i]=listaEncomendas[atoi(idE)][i+1];
                listaEncomendas[atoi(idE)][i+1]=t;
                
            }

            tamEncomenda[atoi(idE)]--;
        }
    }
}


void C(){
    /*preco parcial e o valor presente na encomenda de um produto(qnt*preco)
      preco total e a soma dos parciais de todos os produtos
      idP e o id do produto a que o preco parcial se refere na altura*/
    int c,i,precoTotal=0,precoParcial,idP;
    char idE[MAX_TAM_STR];
    
    /*para ignorar o espaco entre a opcao e o comando*/
    getchar();
    /*ciclo para receber o valor necessario*/
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!='\n'; i++){
        idE[i] = c;
    }
    idE[i]='\0';

    /*levantamento de erros*/
    if(atoi(idE) >= tamListaEncomendas)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",
        atoi(idE));

    else{
        /*precorre a lista da encomenda, e soma ao peso total, a quantidade * o preco do produto */
        for(i=0;i<tamEncomenda[atoi(idE)];i++){
            idP=listaEncomendas[atoi(idE)][i].id;
            precoParcial= listaEncomendas[atoi(idE)][i].qnt * listaProdutos[idP].preco;
            precoTotal+=precoParcial;
        }
        printf("Custo da encomenda %d %d.\n",atoi(idE),precoTotal);
    }
}



void p(){
    int c,i;
    char idP[MAX_CHAR_ID_PRODUTO],preco[MAX_TAM_STR];/*maximo do id do produto e 9999*/

    /*para ignorar o espaco entre a opcao e o comando*/
    getchar();
    /*ciclos para receber os valores necessarios*/
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!=':'; i++){
        idP[i]=c;
    }
    idP[i]='\0';
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!='\n'; i++){
        preco[i]=c;
    }
    preco[i]='\0';

    /*levantamento de erros*/
    if(atoi(idP) >= tamListaProdutos)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",atoi(idP));
    
    else
        listaProdutos[atoi(idP)].preco = atoi(preco);
}



void E(){
    int c,i,naEncomenda=0;
    char idE[MAX_TAM_STR],idP[MAX_TAM_STR];
    
    /*para ignorar o espaco entre a opcao e o comando*/
    getchar();
    /*ciclos para receber os valores necessarios*/
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!=':'; i++){
        idE[i] = c;
    }
    idE[i]='\0';
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!='\n'; i++){
        idP[i]=c;
    }
    idP[i]='\0';

    /*levantamento de erros*/
    if(atoi(idE) >= tamListaEncomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",atoi(idE));
        return;
    }
    else if(atoi(idP) >= tamListaProdutos){
        printf("Impossivel listar produto %d. Produto inexistente.\n",atoi(idP));
        return;
    }

    else{ 
        /*precorre a lista da encomenda, e se o produto estiver na lista, sai do ciclo 
        e imprime o output expectado*/
        for(i=0;i<tamEncomenda[atoi(idE)];i++){
            if(listaEncomendas[atoi(idE)][i].id == atoi(idP)){
                naEncomenda=1;
                break;
            }
        }
        if(naEncomenda)
            printf("%s %d.\n",listaProdutos[atoi(idP)].descricao,listaEncomendas[atoi(idE)][i].qnt);
        else
            printf("%s 0.\n",listaProdutos[atoi(idP)].descricao);
    }
}


void m(){
    /*max e um vetor onde fica guardarda a quantidade maxima e encomenda respetiva*/
    int c,i,j,max[2];
    char idP[MAX_TAM_STR];
    max[0]=-1;
    max[1]=-1;
    /*para ignorar o espaco entre a opcao e o comando*/
    getchar();
    /*ciclo para receber o valor necessario*/
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!='\n'; i++){
        idP[i]=c;
    }
    idP[i]='\0';

    /*levantamento de erros*/
    if(atoi(idP)>=tamListaProdutos){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",atoi(idP));
    }

    else{
        for(i=0;i<tamListaEncomendas;i++){
            for(j=0;j<tamEncomenda[i];j++){
                if(listaEncomendas[i][j].id == atoi(idP)){
                    /*como a lista de encomendas esta ordenada por indice de encomenda, entao
                    se aparecer uma lista tambem com o maximo, fica apenas a de menor id*/
                    if(max[1] < listaEncomendas[i][j].qnt){
                        max[0]=i;
                        max[1]=listaEncomendas[i][j].qnt;
                    }
                }
            }
        }
        /*apenas imprime se o id for validom, isto e se o produto existir na encomenda*/
        if(max[0]>=0)
            printf("Maximo produto %d %d %d.\n",atoi(idP),max[0],max[1]);
    }
}



/*partition do quick sort dado nas aulas teoricas*/
int partition(int a[],int l,int r){
    int i=l, j=r, v=listaProdutos[a[r]].preco, t;
    while(i<j){
        /*mover o "cursor" para a posicao onde o preco no i seja maior que o pivot*/
        while(listaProdutos[a[i]].preco<=v){
            if(i==r)
                break;
            /*parar o cursor se os precos forem iguais e o id do i for maior do que o do pivot*/
            else if(listaProdutos[a[i]].preco==v && a[i]>a[r])
                break;
            else
                i++;
        }
        /*mover o "cursor"para a posicao onde o preco no j seja menor que o pivot*/
        while(listaProdutos[a[j]].preco>=v){
            if(j==l)
                break;
            /*parar o cursor se os precos forem iguais e o id do i for menor do que o do pivot*/
            else if(listaProdutos[a[j]].preco==v && a[j]<a[r])
                break;
            else
                j--;
        }
        if(i<j){
            t=a[j];
            a[j]=a[i];
            a[i]=t;
        }
    }
    t=a[r];
    a[r]=a[i];
    a[i]=t;
    return i;
}

/*quicksort dado nas aulas teoricas*/
void quicksort(int a[], int l, int r){
    int i;
    if (r <= l)
    return;
    i = partition(a, l, r);    
    quicksort(a, l, i-1);
    quicksort(a, i+1, r);
}

void l(){
    int i;
    /*cria uma lista com os indices que da lista de produtos*/
    for(i=0;i<tamListaProdutos;i++){
        listaSort[i]=i;
    }
    /*ordena essa lista por ordem crescente de preco*/
    quicksort(listaSort,0,tamListaProdutos-1);
    printf("Produtos\n");
    /*escreve pela ordem do quicksort a lista dos produtos*/
    for(i=0;i<tamListaProdutos;i++){
        printf("* %s %d %d\n",listaProdutos[listaSort[i]].descricao, listaProdutos[listaSort[i]].preco,
         listaProdutos[listaSort[i]].stock);
    }
}


/*funcao que retorna:
    - 1 se a primeira for maior que a segunda
    - 0 se as strings forem iguais
    - -1 se a segunda for maior que a primeira*/
int compString(char c1[],char c2[]){
    int i=0,ret=0;
    /*caso alguma das strings acabe, parar a comparacao*/
    while(c1[i] != '\0'|| c2[i] != '\0')
    {
        if(c1[i]>c2[i]){
            ret=1;
            break;
        }
        else if(c1[i]<c2[i]){
            ret=-1;
            break;
        }
        i++;
    }
    return ret;
}

/*funcao que ordena o array de "produtos" na encomenda pedida por ordem alfabetica da descricao dos
produtos usando um selection sort*/
void descSort(int idE,int start){   
    /*prodIdMin - guarda o id do produto com menor descricao
    prodIdTemp  - guarda o id do produto no indice atual do ciclo
    idMin       - guarda o indice da encomenda na lista onde esta o prodIdMin*/ 
    int i,idMin,prodIdMin,prodIdTemp;
    Encomenda t;
    if(start >= tamEncomenda[idE]-1){
        return;
    }
    else{
        prodIdMin=listaEncomendas[idE][start].id;
        idMin=start;
        /*procura na lista o elemento com a primeira descricao(da ordem),exclindo o start*/        
        for(i=start+1;i<=tamEncomenda[idE]-1;i++){
            /*id do produto atual*/
            prodIdTemp=listaEncomendas[idE][i].id;
            /*se o minimo for maior que o atual*/
            if (compString(listaProdutos[prodIdMin].descricao,listaProdutos[prodIdTemp].descricao)>=1)
            {
                prodIdMin=prodIdTemp;
                idMin=i;
            }
        }
        if(start!=idMin){
            /*troca o minimo com o inicio*/
            t=listaEncomendas[idE][start];
            listaEncomendas[idE][start]=listaEncomendas[idE][idMin];
            listaEncomendas[idE][idMin]=t; 
        }
        /*agora que o menor elemento esta no inicio, reprtir a funcao mas a comecar no indice a seguir*/
        descSort(idE,start+1);
    }
        
}

/*funcao que imprime os produtos pertencentes a uma encomenda do modo pedido pela funcao L*/
void printEncomenda(int idE){
    int i,id;
    printf("Encomenda %d\n",idE);
    for(i=0;i<tamEncomenda[idE];i++){
        id=listaEncomendas[idE][i].id;
        printf("* %s %d %d\n",listaProdutos[id].descricao,listaProdutos[id].preco,
        listaEncomendas[idE][i].qnt);
    }
}

void L(){
    int c,i;
    char idE[MAX_TAM_STR];
    /*para ignorar o espaco entre a opcao e o comando*/
    getchar();
    /*ciclo para receber o valor necessario*/
    for(i=0; i< MAX_TAM_STR && (c=getchar())!= EOF && c!='\n'; i++){
        idE[i] = c;
    }
    idE[i]='\0';

    /*levantamento de erros*/
    if(atoi(idE) >= tamListaEncomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",atoi(idE));
        return;
    }
    /*se a lista for vazia, n se faz a ordenacao*/
    if(tamEncomenda[atoi(idE)] >= 1){
        /*ordena a encomenda pedida*/
        descSort(atoi(idE),0);
    }
    /*print da encomenda ordenada*/
    printEncomenda(atoi(idE));
}



int main(){
    char opt;
    while(1){
        scanf("%s",&opt);

        switch (opt)
        {
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
            return 0;
        }
    }
}
