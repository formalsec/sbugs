#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_Produtos 10000
#define MAX_Encomendas 500
#define MAX_Description 64

char* inputFile;
int countP=0;
int countE=0;
int countEprodutos[MAX_Produtos];

typedef struct produto{
    int idp;
    char description [MAX_Description];
    int value;
    int weight;
    int stock;

}produto;

typedef struct encomenda{
    int ide;
    int idp[MAX];
    int units[MAX];
    char description[MAX][MAX_Description];
    int value[MAX];
    int weight;

}encomenda;

produto produtos[MAX_Produtos];
encomenda encomendas[MAX_Encomendas];
produto aux[MAX_Produtos];
encomenda auxE[MAX_Encomendas];

void mergeP(int left,int m,int right){

    int i,j,k;
        /*Utiliza um vetor auxiliar para guardar a informacao das estruturas*/
    for(i=m+1;i>left;i--){
        aux[i-1]=produtos[i-1];
    }
    for (j = m; j < right; j++){
        aux[right+m-j] = produtos[j+1];
    }
    for (k = left; k <= right; k++){
        if(aux[j].value<aux[i].value || i>m){   /*Organiza os produtos por valor, em ordem crescente*/
            produtos[k]=aux[j--];
        }
        else{
            if(aux[j].value>aux[i].value){
                produtos[k]=aux[i++];
            }
            else{                               /*Caso se trate do msm valor, o fator*/
                if(aux[j].idp<aux[i].idp){      /*que desempata e o menor id**********/
                    produtos[k]=aux[j--];
                }
                else{
                    produtos[k]=aux[i++];
                }
            }
            
        }
    }
    

}

void mergeE(int loc,int left,int m,int right){

    int i,j,k,y;

    /*Utiliza um vetor auxiliar para guardar a informacao das estruturas*/
    for(i=m+1;i>left;i--){
        auxE[loc].idp[i-1]=encomendas[loc].idp[i-1];
        auxE[loc].units[i-1]=encomendas[loc].units[i-1];
        strcpy(auxE[loc].description[i-1],encomendas[loc].description[i-1]);
    }
    for (j = m; j < right; j++){
        auxE[loc].idp[right+m-j] = encomendas[loc].idp[j+1];
        auxE[loc].units[right+m-j]=encomendas[loc].units[j+1];
        strcpy(auxE[loc].description[right+m-j],encomendas[loc].description[j+1]);
    }
    for (k = left; k <= right; k++){    /*Organiza os produtos por ordem alfabetica*/
        for(y=0;y<MAX_Description;y++){
            if(auxE[loc].description[j][y]<auxE[loc].description[i][y] || i>m){
                encomendas[loc].units[k]=auxE[loc].units[j];
                strcpy(encomendas[loc].description[k],encomendas[loc].description[j]);
                encomendas[loc].idp[k]=auxE[loc].idp[j--];
                break;
            }
            else{
                if(auxE[loc].description[j][y]>auxE[loc].description[i][y]){
                    encomendas[loc].units[k]=auxE[loc].units[i];
                    strcpy(encomendas[loc].description[k],encomendas[loc].description[i]);
                    encomendas[loc].idp[k]=auxE[loc].idp[i++];
                    break;
                }    
            }
        }
    }
    

}

void mergesort(int lL,int left,int right){
    
    int m=(right+left)/2;
    if(right<=left){
        return;
    }
    /*Divide o vetor ao meio*/
    mergesort(lL,left,m);
    mergesort(lL,m+1,right);

    /*Caso um terceiro argumento nao seja necessario,trata-se do caso l*/
    if(lL==-1){
        mergeP(left,m,right);
    }
    /*Contrariamente, trata-se do caso L*/
    else{
        mergeE(lL,left,m,right);
    }

}



void  processInput()
{
    int k;
    int variavel=0;
   
    /****************************************************************************
     Vai ler o ficheiro de input onde est?o os comandos
    ****************************************************************************/
    /*Ciclo que corre ate ao comando x, que simboliza o fim dos comandos*/
     while (variavel<10)
    { 
        char token='\0';
        char s[1];
        char text[100]={'\0'};
        int givenID=0,auxNum=0,qtd=0,savedloc=0,locE=0,y=0,h,i,j,lL,numTokens;
        /*vari?veis encontram-se dentro do ciclo para, se preciso, voltarem ao valor inicial*/        
        k=0;
    /*Caso o comando seja composto por mais que uma letra, faz-se um novo scanf para obter a string*/
        numTokens=scanf( "%s ", s);
        token=s[0];
        if(token!='N' && token!='l' && token!='x'){
            scanf("%s",text);
        }
        
        /* validacao minima*/ 
        if (numTokens < 1) 
        {
            printf("Erro, nada foi lido do input");
            continue;
        }

        switch (token) 
        {
            case 'a':
                /*cria um produto*/
                sscanf(text,"%[^:]:%d:%d:%d", produtos[countP].description, &(produtos[countP].value), &(produtos[countP].weight), &(produtos[countP].stock));
                produtos[countP].idp=countP;
                printf("Novo produto %d.\n", produtos[countP].idp);

                
                countP++;
                break;

            case 'q':
                
                sscanf(text,"%d:%d", &givenID, &auxNum);
                /*Se ainda nao existirem produos, ocorre erro*/ 
                if(countP==0){
                    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",givenID);
                    break;
                }
                /*Se o produto existir, adiciona-se ao mesmo stock*/
                for(i=0;i<countP;i++){
                    if(givenID==produtos[i].idp){
                        produtos[i].stock+=auxNum;
                        k=1;
                        break;
                    }
                   
                }
                /*Caso o produto nao exista, e enviada a mensagem de erro*/
                if(k==0){
                    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",givenID);
                }
                break;


            case 'N':
                /*Cria uma nova encomenda*/
                encomendas[countE].ide=countE;
                countEprodutos[countE]=0;
                printf("Nova encomenda %d.\n",encomendas[countE].ide);
                encomendas[countE].weight=0;
                
                /*idp inicializado a -1 pois existe idp=0*/
                for(i=0;i<MAX;i++){
                    encomendas[countE].idp[i]=-1;
                    encomendas[countE].units[i]=0;
                }

                countE++;
                break;

            case 'A':
                /*Adiciona um produto a uma encomenda*/
                sscanf(text,"%d:%d:%d", &givenID, &auxNum, &qtd);
                if(countE==0){
                    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",auxNum,givenID);
                    break;
                }
            /*Encontra a encomenda alvo*/
                for(i=0;i<countE;i++){
                    if(givenID==encomendas[i].ide){
                        locE=i;
                        k=1;
                        break;
                    }
                    
                }
                /*Caso a encomenda nao exista, e enviada a mensagem de erro*/
                if(k==0){
                    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",auxNum,givenID);
                    break;
                }
                k=0;

                if(countP==0){
                    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.",auxNum,givenID);
                    break;
                }
                /*Encontra o produto e verifica se ele ja existe na encomenda*/
                for(j=0;j<countP;j++){
                    if(auxNum==produtos[j].idp){
                        for(i=0;i<MAX;i++){
                            if(encomendas[locE].idp[i]==-1){
                                savedloc=i;
                                k=1;
                                break;
                            }
                            if(encomendas[locE].idp[i]==auxNum){
                                savedloc=i;
                                k=2;
                                break;
                            }

                        }
                        y=j;
                        break;
                    }
                    
                }
                /*Caso o produto nao exista, e enviada a mensagem de erro*/
                if(k==0){
                    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",auxNum,givenID);
                    break;
                }
                /*Caso o produto nao exista em quantidade suficiente, e enviada a mensagem de erro*/
                if(qtd>(produtos[y].stock)){
                    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",auxNum,givenID);
                    break;
                }
                /*Caso a encomenda supere o peso maximo permitido, e enviada a mensagem de erro*/
                if((((produtos[y].weight)*qtd)+encomendas[locE].weight)>200 ){
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",auxNum,givenID);
                    break;
                }
                /*Caso exista, somam-se as 2 quantidades*/
                if(k==2){
                    encomendas[locE].units[savedloc]+=qtd;
                    produtos[y].stock-=qtd;
                    encomendas[locE].weight+=(produtos[y].weight*qtd);
                    break;
                }
                /*Caso nao, adiciona-se o novo produto a encomenda*/
                else{
                    encomendas[locE].idp[savedloc]=auxNum;
                    produtos[y].stock-=qtd;
                    encomendas[locE].units[savedloc]+=qtd;
                    encomendas[locE].weight+=(produtos[y].weight*qtd);
                    strcpy(encomendas[locE].description[savedloc],produtos[y].description);
                    countEprodutos[locE]++;/*Conta quantos produtos tem a encomenda*/
                }
                    
                break;
                

            case 'E':
                /*lista a descri??o e a quantidade de um produto numa encomenda*/
                sscanf(text,"%d:%d", &givenID, &auxNum);
                if(countE==0){
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",givenID);
                    break;
                }
                for(i=0;i<countE;i++){
                    if(givenID==encomendas[i].ide){
                        locE=i;
                        k=1;
                        break;
                    }
                    
                }
                if(k==0){
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",givenID);
                    break;
                }
                k=0;
                /*Se o id for igual ou superior ao contador, o produto ainda nao existe*/
                if(countP<=auxNum){
                    printf("Impossivel listar produto %d. Produto inexistente.\n",auxNum);
                    break;
                }
                for(i=0;i<MAX;i++){
                    if(auxNum==encomendas[locE].idp[i]){
                        printf("%s %d.\n",encomendas[locE].description[i],encomendas[locE].units[i]);
                        k=1;
                        break;
                    }
                }
                if(k==0){
                    for(i=0;i<countP;i++){
                        if(auxNum==produtos[i].idp){
                            printf("%s %d.\n",produtos[i].description,0);
                        }
                    }
                }
                
                 break;

            case 'r':
                /*Retira stock a um produto*/
                sscanf(text,"%d:%d", &givenID, &qtd);
                if(countP==0){
                    printf("Impossivel remover stock do produto %d. Produto inexistente.\n",givenID);
                    break;
                }
                for(i=0;i<countP;i++){
                    if(givenID==produtos[i].idp){
                        if((produtos[i].stock)<qtd){
                            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,givenID);
                        }
                        else{
                            produtos[i].stock-=qtd;
                        }
                        k=1;
                        break;

                    }
        
                }
                if(k==0){
                    printf("Impossivel remover stock do produto %d. Produto inexistente.\n",givenID);
                }
                break;


            case 'R':
                /*Remove um produto de uma encomenda*/
                sscanf(text,"%d:%d", &givenID, &auxNum);
                if(countE==0){
                    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",auxNum,givenID);
                    break;
                }
                for(i=0;i<countE;i++){
                    if(givenID==encomendas[i].ide){
                        locE=i;
                        k=1;
                        break;
                    }
                   
                }
                if(k==0){
                    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",auxNum,givenID);
                    break;
                }
                k=0;

                if(countP==0){
                    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.",auxNum,givenID);
                    break;
                }
                /*Depois de verificar se o produto existe e de o encontrar na encomenda, faz-se um reset das informacoes no slot que acabou de vagar*/
                for(h=0;h<countP;h++){
                    if(auxNum==produtos[h].idp){
                        k=1;
                        for(i=0;i<MAX;i++){
                            if(encomendas[locE].idp[i]==auxNum){
                                encomendas[locE].idp[i]=-1;
                                for(j=0;j<MAX_Description;j++){
                                   encomendas[locE].description[i][j]='\0';
                                }
                                encomendas[locE].weight-=((encomendas[locE].units[i])*(produtos[h].weight));
                                produtos[h].stock+=encomendas[locE].units[i];
                                encomendas[locE].units[i]=0;
                                countEprodutos[locE]--;/*Como a encomenda perde um produto, o contador decrementa*/
                                /*Caso haja produtos nas seguintes posicoes, a ultima posicao passa a estar no slot que vagou*/
                                if(encomendas[locE].idp[(i+1)]>=0){
                                    for(y=(i+2);y<MAX;y++){
                                        if(encomendas[locE].idp[y]==-1){
                                            encomendas[locE].idp[i]=encomendas[locE].idp[(y-1)];
                                            encomendas[locE].idp[(y-1)]=-1;
                                            encomendas[locE].units[i]=encomendas[locE].units[(y-1)];
                                            encomendas[locE].units[(y-1)]=0;
                                            strcpy(encomendas[locE].description[i],encomendas[locE].description[(y-1)]);
                                            for(j=0;j<MAX_Description;j++){
                                                encomendas[locE].description[(y-1)][j]='\0';
                                            }
                                            break;
                                            
                                        }
                                    }
                                }  
                                    
                                break;
                            }

                        }
                        break;
                    }
                    
                }
                if(k==0){
                        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",auxNum,givenID);
                    }
                break;


            case 'C':
                /*Calcula o preco de uma encomenda*/
                sscanf(text,"%d", &givenID);
                auxNum=0;
                if(countE==0){
                    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",givenID);
                    break;
                }
                for(i=0;i<countE;i++){
                    if(givenID==encomendas[i].ide){
                        locE=i;
                        k=1;
                        break;
                    }
                    
                }
                if(k==0){
                    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",givenID);
                    break;
                }
                /*Como o valor de um produto pode ter sido alterado, este calculo nao pode ir sendo feito
                quando se adiciona um novo produto a encomenda*/
                for(i=0;i<MAX;i++){
                    if(encomendas[locE].idp[i]>-1){
                        for(j=0;j<countP;j++){
                            if(encomendas[locE].idp[i]==produtos[j].idp){
                                auxNum+=(produtos[j].value*encomendas[locE].units[i]);
                                break;
                
                            }
                            
                        }
                    
                    }
                            
                }
                printf("Custo da encomenda %d %d.\n",encomendas[locE].ide,auxNum);
                break;

            case 'p':
                /*Altera o preco de um produto*/
                sscanf(text,"%d:%d", &givenID, &auxNum);
                if(countP==0){
                    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",givenID);
                    break;
                }
                for(i=0;i<countP;i++){
                    if(givenID==produtos[i].idp){
                        produtos[i].value=auxNum;
                        k=1;
                        break;
                    }
                    
                }
                if(k==0){
                    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",givenID);
                }
                break;

            case 'm':
                /*lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
                sscanf(text,"%d", &givenID);

                if(countP==0){
                    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",givenID);
                    break;

                }

                if(countE==0){
                    break;
                }

                for(i=0;i<countP;i++){
                    if(givenID==produtos[i].idp){
                        k=1;
                        break;
                    }
                    
                }
                if(k==0){
                    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",givenID);
                    break;
                }

                savedloc=-1;
                for(j=0;j<countE;j++){
                    for(i=0;i<MAX;i++){
                        if(encomendas[j].idp[i]==givenID){
                            if(encomendas[j].units[i]>=auxNum){
                               if(encomendas[j].units[i]>auxNum){
                                   locE=j;                          /*Guardam-se as localizacoes da encomenda que, no momento tem mais do determinado produto*/
                                   savedloc=i;                      /*a localizacao do produto dentro da encomenda*/
                                   auxNum=encomendas[j].units[i];   /*O maior valor registado ate ao momento*/
                               }
                               else{
                                   if(encomendas[j].idp[i]<encomendas[locE].idp[savedloc]){/*Caso haja empate, e considerado o menor id da encomenda*/
                                       locE=j;
                                       savedloc=i;
                                       auxNum=encomendas[j].units[i];
                                   }
                               }
                                
                            }
                        }
                    }
                    
                }
                if(savedloc>=0){
                    printf("Maximo produto %d %d %d.\n",givenID,encomendas[locE].ide,encomendas[locE].units[savedloc]);
                }
                
                break;



            case 'l':  
                /*lista todos os produtos existentes no sistema por ordem crescente de preco*/
                printf("Produtos\n");
                lL=-1;                      /*Necessario para uma condicao na funcao mergesort*/
                mergesort(lL,0,(countP-1)); /*Funcao que realiza o algoritmo do mesmo nome*/

                for(i=0;i<countP;i++){
                    printf("* %s %d %d\n",produtos[i].description,produtos[i].value,produtos[i].stock);
                }
                break;

            case 'L':
                /* lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o*/
                sscanf(text,"%d", &givenID);
                
                if(countE==0 || givenID>=countE){
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",givenID);
                    break;
                }
                    /*Funcao que realiza o algoritmo do mesmo nome*/
                    mergesort(givenID,0,(countEprodutos[givenID]-1));   /*givenId guarda o id da encomenda*/ 
        
                printf("Encomenda %d\n",givenID);
                for(i=0;i<countEprodutos[givenID];i++){                /*Obtem o valor de um dado produto*/
                    for(j=0;j<MAX_Produtos;j++){
                        if(encomendas[givenID].idp[i]==produtos[j].idp){
                            encomendas[givenID].value[i]=produtos[j].value;
                            break;
                        }
                    }
                    printf("* %s %d %d\n",encomendas[givenID].description[i],encomendas[givenID].value[i],encomendas[givenID].units[i]);
                }
                
                

                break; 


            case 'x':
                /*Comando final, termina o programa*/
                variavel=100;
                break;
            default: 
                /*So ocorre caso haja um erro*/
            { printf("Erro default");
                break;
            }
        }
    }

    

}




int main()
{
/*Vai processar o input, tendo um papel fulcral neste projeto*/
  processInput();

    return 0;
}