#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>            /* Biblioteca de Inputs e Outputs  */
#include <string.h>           /* Biblioteca de manipulacao de Strings  */
#include <stdlib.h>           /* Biblioteca de utilidade (atoi())  */                  
#define TOTAL_PRODUTOS 10000
#define TOTAL_ENCOMENDAS 500
#define MAX_CARACTERES_D 64
#define MAXIMO_VARIAVEIS 80
#define DETALHES_P_OU_E 3
#define MAXIMO_P_NA_E 201
/* Os 6 #define usados limitam, respetivamente:

1-O Total de Produtos
2-O Total de Encomendas
3-O maximo de caracteres da descricao
4-O tamanho maximo da string dada pelo utlizador (com o comando, descricoes e dados)
5-Os detalhes dos produtos (peso,preco,qtd no sistema) e das encomendas (o produto,o preco e a qtd na encomenda)
6-O maximo de produtos da encomenda (Com uma linha a mais para os detalhes gerais da encomenda-(se existe,o num de produtos e o peso total))

*/

char descricao[TOTAL_PRODUTOS][MAX_CARACTERES_D],dados[MAXIMO_VARIAVEIS];
int np=0,stock[TOTAL_PRODUTOS][DETALHES_P_OU_E],encomendas[TOTAL_ENCOMENDAS][MAXIMO_P_NA_E][DETALHES_P_OU_E];

/* Foram definidos 4 vetores e 1 constante, por ordem:

1- Um vetor que armazena todas as descricoes dos produtos
2- Um vetor que recebe o input
3- Uma constante que guarda o numero de produtos adicionado ao armazem
4- Um vetor que guarda os detalhes dos produtos (preco,peso,qtd)
    Ex: 
    stock[593][0]- tem o preco do produto com id 593
    stock[593][1]- tem o peso do produto com id 593
    stock[593][2]- tem a qtd do produto com id 593
5- Um vetor que guarda os detalhes das encomendas
    Ex:
    encomendas[27][0][0]- varia entre 0 (se a encomenda 27 nao existe) e 1 (se a encomenda 27 ja foi criada)
    encomendas[27][0][1]- contem o peso total da encomenda 27 (que nao pode ultrapassar 200 unidades)
    encomendas[27][0][2]- contem o numero de produtos que foram adicionados a encomenda 27
    encomendas[27][4][0]- tem o id do quarto produto adicionado a encomenda 27
    encomendas[27][4][1]- tem a qtd do quarto produto adicionado a encomenda 27
    encomendas[27][4][2]- tem o preco TOTAL (preco idp * qtd na encomenda) do quarto produto adicionado a encomenda 27

A funcao main esta definida na linha 254, sendo precedida por todas as outras funcoes.
*/

/*FUNCOES AUXILIARES MERGE E MERGESORT PARA A FUNCAO 'l' e 'L' */
void Merge(int a[],int l,int m,int r){                  /*Merge para unir os vetores partidos pelo MergeSort*/
    int i,j,k,aux[TOTAL_PRODUTOS];                      /*Indicadores i,j,k e vetor aux para ajudar na ordenacao*/       
    for (i=m+1;i>l;i--){aux[i-1]=a[i-1];}               /* Preenche o vetor aux pela esquerda ate ao meio,com menores valores na ponta */
    for (j=m;j<r;j++){aux[r+m-j]=a[j+1];}               /* Preenche o vetor aux pela direita ate ao meio,com menores valores na ponta */           
    for (k=l;k<=r;k++){                                 /* Preenche o vetor a desde a[l] ate a[r] utilizando os indicadores i e j */
        if (aux[j]<aux[i]){a[k]=aux[j--];}              /* Se aux[j]<aux[i], a[k] ser? a[j], e j sera decrementado. (i permanece igual) */
        else{a[k]=aux[i++];}                            /* Se aux[i]<aux[j], a[k] ser? a[i], e i sera incrementado. (j permanece igual) */
    }
}
void MergeSort(int a[],int l,int r){                    /*MergeSort para ordenar os precos (MergeSort parte os vetores,Merge une-os)*/
    int m=(l+r)/2;                                      /*Identifica o meio dos vetores*/
    if (r<=l){return;}                                  /*Quebra quando o vetor a s? tem um elemento*/
    MergeSort(a,l,m);                                   /*Parte o vetor da esquerda*/
    MergeSort(a,m+1,r);                                 /*Parte o vetor da direita*/
    Merge(a,l,m,r);                                     /*Une os vetores consecutivos*/
}
void OrdenarDes(char a[][MAX_CARACTERES_D],int l,int r){    /*Selection Sort para ordenar as Descricoes*/
    char temp[MAX_CARACTERES_D];
    int i,j;

    for(i=l;i<r-1;i++){             /*Percorre o vetor a. Quando i incrementa, a[i] ja esta na sua posicao final    */
        for(j=i+1;j<r;j++){         /*Percorre o vetor a, come?ando em a[i+1]. Se strcmp(a[i],a[j])>0, troca-os.    */
            if (strcmp(a[i],a[j])>0){
                strcpy(temp,a[i]);
                strcpy(a[i],a[j]);
                strcpy(a[j],temp);
            }
        }
    }
}
/* FIM DAS FUNCOES AUXILIARES PARA FUNCAO 'l' e 'L' */
void AdicionarSistema(){
    strcpy(descricao[np], strtok(dados,":"));       /*Copia a string dados at? ao simbolo ":" para descricao[np]*/
    stock[np][0]=atoi(strtok(NULL,":"));            /*Copia o preco do produto para stock[np][0] (usando a funcao atoi() str->int)*/
    stock[np][1]=atoi(strtok(NULL,":"));            /*Copia o peso do produto para stock[np][1] (usando a funcao atoi())*/
    stock[np][2]=atoi(strtok(NULL,":"));            /*Copia a qtd do produto para stock[np][2] (usando a funcao atoi())*/
    printf("Novo produto %d.\n",np);
    np++;                                           /*Aumenta o total de produtos*/
}
void AdicionaStock(){
    int idp,qtd;
    idp=atoi(strtok(dados,":"));
    qtd=atoi(strtok(NULL,":"));
    if (idp>=np){printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);return;}
    stock[idp][2]=stock[idp][2]+qtd; 
}
void CriarEncomenda(){
    static int ide=0;
    encomendas[ide][0][0]=1; /*existencia da encomenda*/
    encomendas[ide][0][1]=0; /*peso total da encomenda*/    
    encomendas[ide][0][2]=0; /*numero de produtos da encomenda*/
    printf("Nova encomenda %d.\n",ide);
    ide++; /*aumenta o total de encomendas criadas para uso futuro*/
}
void AdicionarProdutoEncomenda(){
    int ide,idp,qtd,a;
    ide=atoi(strtok(dados,":"));
    idp=atoi(strtok(NULL,":"));
    qtd=atoi(strtok(NULL,":"));
    if (encomendas[ide][0][0]!=1){printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);return;}
    if (idp>=np){printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);return;}
    if (stock[idp][2]<qtd){printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);return;}
    if((encomendas[ide][0][1]+stock[idp][1]*qtd)>200){printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);return;}
    
    for(a=1;encomendas[ide][a][1]!=0;a++){
        if(encomendas[ide][a][0]==idp){encomendas[ide][0][2]=encomendas[ide][0][2]-1;break;} /*verifica se <idp> esta na encomenda*/
    }
    encomendas[ide][a][0]=idp; /*Copia o idp do produto para encomendas[ide][a][0] (usando a funcao(atoi))*/
    encomendas[ide][a][1]=encomendas[ide][a][1]+qtd; /*Adiciona a <qtd> a encomendas[ide][a][1](0 se o produto for adicionado pela 1a vez)*/
    encomendas[ide][a][2]=encomendas[ide][a][2]+stock[idp][0]*qtd; /*Adiciona o preco(stock[idp][0]*qtd) a encomendas[ide][a][2]*/
    stock[idp][2]=stock[idp][2]-qtd; /*Retira <qtd> unidades do produto <idp> ao stock*/
    encomendas[ide][0][1]=encomendas[ide][0][1]+stock[idp][1]*qtd; /*Aumenta o peso total da encomenda <ide>*/
    encomendas[ide][0][2]=encomendas[ide][0][2]+1; /*Aumenta o numero de produtos da encomenda <ide>*/
}
void RemoveStock(){
    int idp,qtd;
    idp=atoi(strtok(dados,":"));
    qtd=atoi(strtok(NULL,":"));
    if (idp>=np){printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);return;}
    if (stock[idp][2]<qtd){printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);return;}
    stock[idp][2]=stock[idp][2]-qtd; /*Retira a qtd do stock*/
}
void RemoveProdutoEncomenda(){
    int ide,idp,a;
    ide=atoi(strtok(dados,":"));
    idp=atoi(strtok(NULL,":"));
    if (encomendas[ide][0][0]!=1){printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);return;}
    if (idp>=np){printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);return;}
    for(a=1;encomendas[ide][a][2]!=0;a++){
        if(encomendas[ide][a][0]==idp){         /*encontra o produto <idp> na encomenda <ide> */
            encomendas[ide][0][1]=encomendas[ide][0][1]-stock[idp][1]*encomendas[ide][a][1]; /*Altera o peso total da encomenda*/
            stock[idp][2]=stock[idp][2]+encomendas[ide][a][1]; /*devolve os a qtd do produto <idp> ao stock*/
            while(a<=encomendas[ide][0][2]){    /*Apaga as informacoes de <idp> na encomenda, antecipando as informacoes seguintes uma linha*/
                encomendas[ide][a][0]=encomendas[ide][a+1][0];
                encomendas[ide][a][1]=encomendas[ide][a+1][1];
                encomendas[ide][a][2]=encomendas[ide][a+1][2];
                a++;
            }
            encomendas[ide][0][2]=encomendas[ide][0][2]-1; /*remove um produto a encomenda <ide>*/
            break;
        }
    }
}
void CustoEncomenda(){
    int ide,total=0,a;
    ide=atoi(dados);
    if (encomendas[ide][0][0]!=1){printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);return;}
    for(a=1;a<=encomendas[ide][0][2];a++){
        total=total+encomendas[ide][a][2]; /*Soma os precos da encomenda <ide> e devolve o seu total*/
    }
    printf("Custo da encomenda %d %d.\n",ide,total);
}
void AlterarPreco(){
    int idp,preco,ide,a;
    idp=atoi(strtok(dados,":"));
    preco=atoi(strtok(NULL,":"));
    if(idp>=np){printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);return;}
    stock[idp][0]=preco;
    for(ide=0;encomendas[ide][0][0]==1;ide++){ /*Percorre as encomendas existentes e altera os precos de <idp> nas mesmas*/
        for(a=1;a<=encomendas[ide][0][2];a++){
            if(encomendas[ide][a][0]==idp){
            encomendas[ide][a][2]=preco*encomendas[ide][a][1];
            break;
            }
        }
    }

}
void DeQdoProdutonaEncomenda(){
    int idp,ide,a,qtd=0;
    ide=atoi(strtok(dados,":"));
    idp=atoi(strtok(NULL,":"));
    if (encomendas[ide][0][0]!=1){printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);return;}
    if (idp>=np){printf("Impossivel listar produto %d. Produto inexistente.\n",idp);return;}
    for(a=1;a<=encomendas[ide][0][2];a++){  /*Enconta a encomenda <ide> e devolve a qtd de <idp> na mesma e a sua descricao*/
        if(encomendas[ide][a][0]==idp){
            qtd=encomendas[ide][a][1];
            break;
        }
    }                                       /*Se <idp> n?o estiver na encomenda, devolve a sua descricao e 0*/
    printf("%s %d.\n",descricao[idp],qtd);
}
void EncomendaOndeApareceMais(){
    int idp,a,ide,e,qtd=0;
    idp=atoi(dados);
    if(idp>=np){printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);return;}
    for(ide=0;encomendas[ide][0][0]==1;ide++){                          /*Percorre as encomendas                            */
        for(a=1;a<=encomendas[ide][0][2];a++){                          /*Percorre os produtos na encomeda                  */
            if(encomendas[ide][a][0]==idp){                             /*Se o produto estiver na encomenda                 */
                if(encomendas[ide][a][1]>qtd){                          /*Se for a encomenda onde o produto esta mais vezes */
                    e=ide;                                              /*Guarda <ide>                                      */
                    qtd=encomendas[e][a][1];                            /*Guarda a qtd de <idp> em <ide>                    */
                }
            }
        }
    }
    if(qtd!=0){printf("Maximo produto %d %d %d.\n",idp,e,qtd);}    /*Se o produto <idp> nao estiver em nenhuma encomenda, nao imprime nada*/
}    
void ProdutosDoMaisBaratoParaOMaisCaro(){
    int precos[TOTAL_PRODUTOS],a,c=0;
    for(a=0;a<np;a++){                              /*preenche o vetor precos com o preco dos produtos que estao no sistema at? np-1*/
        precos[a]=stock[a][0];
    }
    MergeSort(precos,0,np-1);                      /*ordena o vetor precos at? np-1*/
    printf("Produtos\n");
    while(c<np){                                    /*enquanto ainda houver produtos para imprimir*/
        for(a=0;a<np;a++){                          /*Percorre os produtos do sistema*/                
            if(precos[c]==stock[a][0]){             /*Se o valor de precos[c] corresponder a um preco do sistema*/
               printf("* %s %d %d\n",descricao[a],stock[a][0],stock[a][2]);
               c++;                                 /*Aumenta o numero de produtos ja impressos*/
               if(precos[c-1]!=precos[c]){break;}   /*Quebra o ciclo quando o preco fica diferente,ou seja, quando ja nao ha produtos com aquele preco*/
            }
        }
    }
}
void ProdutosDaEncomendaPorOrdemAlfabetica(){  
    int idp,ide,a,i;
    char des[MAXIMO_P_NA_E][MAX_CARACTERES_D];
    ide=atoi(dados);
    if (encomendas[ide][0][0]!=1){printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);return;}
    for(i=1;i<=encomendas[ide][0][2];i++){
        idp=encomendas[ide][i][0];                   
        strcpy(des[i-1],descricao[idp]);             /*Preenche o vetor des com as descricoes dos produtos na encomenda*/
    }
    OrdenarDes(des,0,encomendas[ide][0][2]);              /*Ordena o vetor des por ordem alfabetica*/
    printf("Encomenda %d\n",ide);
    for(i=0;i<encomendas[ide][0][2];i++){                       /*Percorre as descricoes do vetor des */
        for(idp=0;strcmp(des[i],descricao[idp])!=0;idp++){}     /*Percorre os produtos do sistema ate encontrar a descricao pretendida */                             
            for(a=1;idp!=encomendas[ide][a][0];a++){}
                printf("* %s %d %d\n",descricao[idp],stock[idp][0],encomendas[ide][a][1]);  /*Imprime*/
                  
    }       
}

int main(){
    char c;
    while(1){
    fgets(dados,80,stdin);
    c=dados[0];
    memmove(dados,dados+2,78);
        switch(c){
            case 'a':AdicionarSistema();break;                      /*Recebe <descricao:preco:peso:qtd> e adiciona um produto com estes dados*/                        
            case 'q':AdicionaStock();break;                         /*Recebe <idp:qtd> e adiciona qtd unidades ao produto idp*/                                           
            case 'N':CriarEncomenda();break;                        /*Cria uma nova encomenda*/                                                                          
            case 'A':AdicionarProdutoEncomenda();break;             /*Recebe <ide:idp:qtd> e adiciona qtd unidades do produto idp a encomenda ide*/            
            case 'r':RemoveStock();break;                           /*Recebe <idp:qtd> e tira qtd unidades ao produto idp*/                                                  
            case 'R':RemoveProdutoEncomenda();break;                /*Recebe <ide:idp> e remove o produto idp da encomenda ide*/                                  
            case 'C':CustoEncomenda();break;                        /*Recebe <ide> e calcula o custo da encomenda ide */                                                  
            case 'p':AlterarPreco();break;                          /*Recebe <idp:preco> e muda o preco do produto idp*/                                                    
            case 'E':DeQdoProdutonaEncomenda();break;               /*Recebe <ide:idp> e devolve a descri??o e quantidade do produto na encomenda*/              
            case 'm':EncomendaOndeApareceMais();break;              /*Recebe <idp> e devolve a encomenda onde este aparece mais vezes*/                         
            case 'l':ProdutosDoMaisBaratoParaOMaisCaro();break;     /*Lista todos os produtos existentes no sistema por ordem crescente de preco*/     
            case 'L':ProdutosDaEncomendaPorOrdemAlfabetica();break; /*Recebe <ide> e devolve os produtos de uma encomenda por ordem alfabetica*/   
            case 'x':return 0;                                      /*Sai do programa*/   
        }                                                                                       
    }
/*
A funcao main define apenas uma variavel c de tipo char (que recebe o comando). 
Funciona depois num ciclo infinito apenas quebrado quando o comando ? x.
A funcao memmove apaga o comando e o espa?o que o segue, deixando a string apenas com os dados necessarios para cada funcao.
A funcao switch recebe c e corre a funcao correspondente.
----------------------------------------------------------------------------------------------------------------------------
Verificacoes por ordem utilizadas nas funcoes:
if (encomendas[ide][0][0]!=1)                                   Verifica se a encomenda <ide> existe.
if (idp>=np)                                                    Verifica se o produto <idp> existe.
if (stock[idp][2]<qtd)                                          Verifica se existe <qtd> suficiente do produto <idp>.
if ((encomendas[ide][0][1]+stock[idp][1]*qtd)>200)              Verifica se o limite de peso do produto (200) seria excedido.
*/
}

/*
OBSERVACOES:
1-Nas ordenacoes das funcoes 'l' e 'L' foram verificados os tempos de execucao de cada um dos metodos de ordenacao(Insertion,Selection,Merge etc.),
sendo os escolhidos aqueles que apresentavam um menor tempo de execucao
2-Todas as funcoes estao definidas pela ordem em que aparecem no menu da funcao main, exceto as funcoes auxiliares que se encontram logo no inicio.
*/
