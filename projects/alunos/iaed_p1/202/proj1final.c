#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAX_PRODUTOS 10000 /*maximo de produtos possivel*/
#define MAX_P_ENC 200   /*maximo de produtos/peso por encomenda*/
#define MAX_ENC 500     /*maximo de encomendas possivel*/
#define STRING 63     /*tamanho maximo das descricoes*/


/*############################################################ESTRUTURAS##########################################################################*/
typedef struct produto{
        int id;
        char descricao[STRING];   
        int preco;
        int peso;
        int qtd;
}produto;

typedef struct order{
        int id;
        produto produtos[MAX_P_ENC];
        int preco;
}order;



/*###########################################VARIAVEIS GLOBAIS###############################################################*/

/* conjunto de encomendas vazias,conjunto de produtos vazio,produto vazio e contador de produtos de armazem,respetivamente. */

order conj_encomendas[MAX_ENC];
produto armazem[MAX_PRODUTOS];                  

int cont;
int n;

/*############################################################################################################################*/










/*###########################################################FUNCOES################################################################################*/




/*   Comando "a"
 Esta funcao percorre o armazem adicionando lhe produtos.*/

void adiciona_novo_produto(){
        
        produto p;
        
                scanf(" %[^:]:%d:%d:%d", p.descricao, &p.preco, &p.peso,&p.qtd);
                

                p.id=cont;
                armazem[cont]=p;
                
                printf("Novo produto %d.\n", p.id);
                
                cont++;

}




/*   Comando "q"
 Esta funcao acrescenta stock a um produto existente,verificado pelo facto 
 pelo facto de ser inferior a variavel cont (que apenas incrementa quando um 
 novo produto e criado)*/

void adiciona_stock(){

        int possivel_qtd=0;
        int idp_inserido=0;
        
        
        
                scanf("%d:%d", &idp_inserido, &possivel_qtd);
                

                if (idp_inserido>=cont|| idp_inserido<0){
                       
                        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_inserido);
                
                }
                        
                else{
                        armazem[idp_inserido].qtd += possivel_qtd;
                }
                 
}




/* Comando "r"
Esta funcao faz exatamente o contrario do comando anterior,fazendo a mesma
verificacao(se existe) e averigua se existe quantidade em armazem disponivel
para remover.*/

void remove_stock(){

        int qtd_inserida=0;
        int idp_inserido=0;       
        
                scanf("%d:%d", &idp_inserido, &qtd_inserida);


                if(idp_inserido>=cont || idp_inserido<0 ){  /*se o produto existe*/
                        
                        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_inserido);
                
                return;
                }

                if(qtd_inserida>armazem[idp_inserido].qtd){  /*se a qtd resultante da diferenca e negativa*/
                        
                        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_inserida, idp_inserido);
                
                return;
                }
                
                else{
                        armazem[idp_inserido].qtd -= qtd_inserida;
                }
        
return;
        
}




/* Comando "p"
Esta funcao altera os precos dos produtos verificando a sua existencia.*/

void altera_precos(){

        int idp_inserido;        
        int novo_preco;        
                
                scanf("%d:%d", &idp_inserido, &novo_preco);


                if(idp_inserido>=cont||idp_inserido<0){ /*se o produto existe*/
                        
                        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_inserido);
               
                }

                else{
                        
                        armazem[idp_inserido].preco = novo_preco;     
                
                }
        
}




/*
Funcao inicializadora de produtos de uma encomenda,inicia todos os id's a '-1'.*/

void func_auxiliar(int n){
        
        int i=0;
        
                for(i=0;i<MAX_P_ENC;i++){
                        
                        conj_encomendas[n].produtos[i].id = -1;
                }

}





/*Comando "N"
Esta funcao cria uma nova encomenda e incrementa a variavel n(numero de
 encomendas criadas),inicializando-o os id's dos produtos a '-1' 
,convencionando se que este espa?o se encontra vazio */

void cria_nova_encomenda(){
        
        if (n<MAX_ENC){
                conj_encomendas[n].id=n;
                func_auxiliar(n);
              
        printf("Nova encomenda %d.\n",n);
                n++;
        }
          
}




/*   
 Esta e uma funcao auxiliar ,calcula o peso de uma encomenda*/

int calcula_peso(int ide_inserido,int idp_inserido,int qtd_a_inserir){
        
        int i=0;
        int soma=0;
        int peso_total=0;
        
                for(i=0;i<MAX_P_ENC;i++){ /*percorre tds os elementos de uma encomenda*/
                        
                        if(conj_encomendas[ide_inserido].produtos[i].id >-1){
                        
                                soma+=(conj_encomendas[ide_inserido].produtos[i].qtd*armazem[(conj_encomendas[ide_inserido].produtos[i].id)].peso);       
                        }
                        
                        else{
                                continue;
                        }      
                
                }
                peso_total=(armazem[idp_inserido].peso*qtd_a_inserir)+soma;

return peso_total;
}




/*Comando "A"
Esta funcao adiciona produtos a uma determinada encomenda.Os erros decorrentes
desta funcao prendem se com o facto de:nao existir encomenda com o
ide inserido criada,o produto nao existir em armazem,a quantidade
que se procura adicionar ser superior a disponivel em stock(no armazem) 
e o peso exceder o peso maximo de cada encomenda.*/

void adiciona_produto_a_encomenda(){
        
        int ide_inserido=0;
        int idp_inserido=0;
        int qtd_a_inserir=0;
        int i=0;   
        int peso_total=0;
           
           
                scanf("%d:%d:%d",&ide_inserido,&idp_inserido,&qtd_a_inserir);  
                

                if(ide_inserido>=n || ide_inserido<0){ /*se a encomenda existe*/
                        
                        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_inserido, ide_inserido);
                
                return ;
                }
                        
                if(idp_inserido>=cont || idp_inserido<0){ /*se o produto existe em armazem*/                
                        
                        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_inserido, ide_inserido);
                
                return ;       
                }        
                                
                if(armazem[idp_inserido].qtd<qtd_a_inserir){ /*se ha stock disponivel*/
                        
                        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_inserido, ide_inserido);
                
                return ;
                }         
                                
                peso_total=calcula_peso(ide_inserido,idp_inserido,qtd_a_inserir);              
                
                if(peso_total>MAX_P_ENC){   /*se excede o peso*/
                        
                        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_inserido, ide_inserido); 
                
                return ;
                }                


                else{
                        for(i=0;i<MAX_P_ENC;i++){
                                
                                if(conj_encomendas[ide_inserido].produtos[i].id==idp_inserido){
                                                                        
                                        conj_encomendas[ide_inserido].produtos[i].qtd+=qtd_a_inserir;
                                        armazem[idp_inserido].qtd-=qtd_a_inserir;
                                        
                                return;
                                }
                                
                                else if(conj_encomendas[ide_inserido].produtos[i].id == -1){
                                        
                                        conj_encomendas[ide_inserido].produtos[i].id = idp_inserido;
                                        strcpy(conj_encomendas[ide_inserido].produtos[i].descricao,armazem[idp_inserido].descricao);
                                        conj_encomendas[ide_inserido].produtos[i].qtd = qtd_a_inserir;
                                        conj_encomendas[ide_inserido].produtos[i].preco = armazem[idp_inserido].preco;
                                        conj_encomendas[ide_inserido].produtos[i].peso = armazem[idp_inserido].peso;
                                
                                break;                                      
                                }

                        }        
                
                }
        
        armazem[idp_inserido].qtd-=qtd_a_inserir;
                                                    
return ;
}




/*   Comando "R"
 Esta funcao tal como o nome indica remove produtos a uma encomenda nunca 
 permitindo que haja espa?os vazios entre produtos,apos o produto ser removido.
 Tal acontece pois o vetor de produtos da encomenda 'avanca'/'puxa' uma casa para
  a frente atribuindo a esse vazio o valor do produto procedente.Note se novamente
  que novamente nesta funcao ocorrem algumas verificacoes ja enunciadas.  */

void remove_produto_encomenda(){
        
        int ide_inserido=0;
        int idp_inserido=0;
        int i=0;
        int posicao=-1;
        
                scanf("%d:%d",&ide_inserido,&idp_inserido);


                if(ide_inserido>=n || ide_inserido<0){ /*se a encomenda existe*/
                        
                        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp_inserido,ide_inserido);
                
                return ;
                }

                if(idp_inserido>=cont || idp_inserido<0){ /*se o produto existe em armazem*/                
                        
                        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp_inserido,ide_inserido);
                
                return ;       
                }                
                
                else {

                        for(i=0;i<MAX_P_ENC;i++){
                                
                                if(conj_encomendas[ide_inserido].produtos[i].id == idp_inserido){
                                        
                                        posicao=i; /*aqui fixa se a posicao a remover*/
                                        armazem[idp_inserido].qtd += conj_encomendas[ide_inserido].produtos[i].qtd;
                                
                                break;
                                }

                        }
                        if(posicao!=-1){
                                
                                for(i=posicao+1;i<MAX_P_ENC;i++){  /*neste ciclo,a partir do espaco a seguir a posicao igualamos o elemento anterior(o primeiro deles posicao)
                                                                                                              ao procedente   */
                                        
                                        conj_encomendas[ide_inserido].produtos[i-1].id = conj_encomendas[ide_inserido].produtos[i].id;
                                        conj_encomendas[ide_inserido].produtos[i-1].qtd = conj_encomendas[ide_inserido].produtos[i].qtd;
                                        conj_encomendas[ide_inserido].produtos[i-1].preco = conj_encomendas[ide_inserido].produtos[i].preco;
                                        conj_encomendas[ide_inserido].produtos[i-1].peso = conj_encomendas[ide_inserido].produtos[i].peso;
                                        strcpy(conj_encomendas[ide_inserido].produtos[i-1].descricao,conj_encomendas[ide_inserido].produtos[i].descricao);
                                        
                                        if(conj_encomendas[ide_inserido].produtos[i].id==-1){   /*assim que comecar a encontrar espacos vazio(com id's =-1)*/
                                        
                                                break;
                                        }
                                
                                        if(i==MAX_P_ENC){ /*caso a encomenda esteja cheia*/
                                        
                                                conj_encomendas[ide_inserido].produtos[i].id=-1;
                                
                                        }    

                                }
                        
                        }    
                
                }
                                
return;
}


       

/*Comando "C"
Esta funcao calcula o somatorio dos precos de todos os produtos
existentes na encomenda,se a encomenda existir*/
                                                        
void calcula_custo_encomenda(){
        
        int ide_inserido;                
        int i=0;   
        int soma=0;

                scanf("%d",&ide_inserido);


                if(ide_inserido<n && ide_inserido>=0){  /*se existe a encomenda*/
                       
                        for(i=0;i<MAX_P_ENC;i++){
                                
                                if(conj_encomendas[ide_inserido].produtos[i].id>-1){        /*se tivesse apenas conj_encomendas[ide_inserido].produtos[i].preco nao estaria a aceder a informacao pretendida*/
                                        
                                        soma += ((conj_encomendas[ide_inserido].produtos[i].qtd)*(armazem[conj_encomendas[ide_inserido].produtos[i].id].preco));
                                
                                }
                        
                                else {
                                        
                                        break;
                                
                                }
                        }       

                        printf("Custo da encomenda %d %d.\n",ide_inserido,soma);         
                
                return;
                
                }
                
                else{
                       
                        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide_inserido);
                
                return;
                }

return;
}                                                        




/*Comando "m"
Esta funcao percorre todas as encomendas criadas ate entao averiguando
a quantidade do produto inserido em cada uma delas,imprimindo no final
a primeira encomenda em que se regista a maior quantidade e a quantidade.*/

void avaliadora_qtd_produto(){
        
        int idp_inserido=0;
        int i=0;                                            /*nesta funcao as variaveis qtd_cpm e ide_cmp correspondem a quantidade comparativa */                                                                      
        int qtd_cmp=0;                                       /*e ide de comparacao que tomam novos valores assim que a qtd_cmp encontra um valor que lhe e superior */
        int ide_cmp=0;
        int j=0;
        
                scanf("%d",&idp_inserido);

                
                if(idp_inserido>=cont || idp_inserido<0){   /*se existe encomenda criada*/                    
                        
                        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_inserido);   /*se existe esse produto no armazem*/
                
                return;
                
                }
                
                else{
                        
                        for(i=0;i<n;i++){
                                
                                for(j=0;j<MAX_P_ENC;j++){  
                                        
                                        if(conj_encomendas[i].produtos[j].id == idp_inserido  &&  conj_encomendas[i].produtos[j].qtd > qtd_cmp){
                                                
                                                ide_cmp = i;
                                                qtd_cmp = conj_encomendas[i].produtos[j].qtd;
                                        
                                        }
                                        
                                }
                                
                        }
                                        
                }
        
        if(qtd_cmp>0){
                
                printf("Maximo produto %d %d %d.\n",idp_inserido,ide_cmp,qtd_cmp);
   
        }
        
return;         
        
}




/*Comando "E"
Esta funcao imprime a descricao e a quantidade de um produto numa encomenda(se existir) 
se este existir em armazem.*/

void lista_descricao_qtd(){
        
        int ide_inserido=0;   
        int idp_inserido=0;
        int i=0;        
        
                scanf("%d:%d",&ide_inserido,&idp_inserido);


                if(ide_inserido>=n||ide_inserido<0){  /*se existe encomenda criada*/
                       
                        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide_inserido);
                
                return;
                }
                
                if(idp_inserido>=cont||idp_inserido<0){  /*se existe produto criado*/
                
                        printf("Impossivel listar produto %d. Produto inexistente.\n",idp_inserido);
                
                return;
                }
                
                else{
                
                        for(i=0;i<MAX_P_ENC;i++){
                
                                if (conj_encomendas[ide_inserido].produtos[i].id==idp_inserido){
                
                                        printf("%s %d.\n",conj_encomendas[ide_inserido].produtos[i].descricao,conj_encomendas[ide_inserido].produtos[i].qtd);
                                        
                                return;
                                }

                                else{
                                        continue;
                                }
                                                                       
                        }
                        
                printf("%s %d.\n",armazem[idp_inserido].descricao,0);
                
                return;    
                
                }           
return;        

}




/*As seguintes funcoes merge representam o algoritmo merge sort implementado
 que sera usado na funcao lista_produtos_preco */

int aux[MAX_PRODUTOS];

void merge_preco(int vetor[], int left, int m, int right) { 
        
        int i, j, k;
                
                for (i = m+1; i > left; i--) {
                
                        aux[i-1] = vetor[i-1];
                
                }
                
                for (j = m; j < right; j++) {
                        
                        aux[right+m-j] = vetor[j+1];
                }
                
                for (k = left; k <= right; k++) {
                        
                        if (armazem[aux[j]].preco < armazem[aux[i]].preco || i > m) {
                        
                        vetor[k] = aux[j--];
                        
                        } 
                        
                        else {
                        
                        vetor[k] = aux[i++];
                        
                        }
                }
}


void mergesort1(int vetor[], int left, int right) {
        
        int m = (left + right) / 2;
        
                if (right <= left) 
                
                {
                
                        return;
                }
                
                mergesort1(vetor, left, m);
                
                mergesort1(vetor, m + 1, right);
                
                merge_preco(vetor, left, m, right);
                
}                           




/*Comando 'l'
 Esta funcao lista os produtos ja criados em armazem por ordem crescente
  de preco*/

void lista_produtos_preco(){
       
        int i=0;
        int j=0;
        int vetor[MAX_PRODUTOS];
        
                for(i=0;i<cont;i++){
                        vetor[i]=i;  /*guardar indices criados*/
                        
                }

                mergesort1(vetor,0,cont-1);   /*o vetor fica ordenado*/

                printf("Produtos\n");
                
                for(j=0;j<cont;j++){
                
                        printf("* %s %d %d\n",armazem[vetor[j]].descricao,armazem[vetor[j]].preco,armazem[vetor[j]].qtd);
                }

}




/*Comando 'L'
Esta funcao lista os produtos de uma encomenda(existente) por ordem alfabetica da sua descricao*/

void lista_descricao() {
        
        int ide_inserido=0;
        int i=0;
        int j=0;
        int k=0;
        produto aux;
        
                scanf("%d", &ide_inserido);
                

                if(ide_inserido>=n || ide_inserido<0){ /*se a encomenda existe */                
                        
                        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_inserido);
                        
                return;
                }

                for (i=0;i<MAX_P_ENC;i++){     /*percorrer os produtos da encomenda*/
                                                /*condicao do espaco estar vazio*/
                        if(conj_encomendas[ide_inserido].produtos[i].id ==-1){
                                
                                break;
                        
                        }

                        for(j=i+1;j<MAX_P_ENC;j++){
                                                        /*condicao do espaco estar vazio*/
                                if(conj_encomendas[ide_inserido].produtos[j].id==-1){
                                        
                                        break;
                                
                                }

                                                /*compara as strings*/
                                if (strcmp(conj_encomendas[ide_inserido].produtos[i].descricao, conj_encomendas[ide_inserido].produtos[j].descricao) > 0){
                                        
                                        aux = conj_encomendas[ide_inserido].produtos[i];
                                        conj_encomendas[ide_inserido].produtos[i] = conj_encomendas[ide_inserido].produtos[j];
                                        conj_encomendas[ide_inserido].produtos[j] = aux;
                                }
                        }
                }
                
                printf("Encomenda %d\n", ide_inserido);
                
                for (k=0;k<MAX_P_ENC;k++){                         
                        
                        if (conj_encomendas[ide_inserido].produtos[k].id > -1){
                                
                                
                                printf("* %s %d %d\n", armazem[conj_encomendas[ide_inserido].produtos[k].id].descricao,
                                                armazem[conj_encomendas[ide_inserido].produtos[k].id].preco,
                                                conj_encomendas[ide_inserido].produtos[k].qtd);
                        }
                }
}




void menu_informativo(){
        
        printf("                 M E N U\n\n");
        printf("Comando                        Acao.\n\n");
        printf("  a               Adiciona um produto ao armazem.\n\n");
        printf("  A               Adiciona um produto a uma encomenda.\n\n");
        printf("  q               Adciona stock de um produto ao armazem.\n\n");
        printf("  r               Remove stock de um produto em armazem.\n\n");
        printf("  R               Remove um produto de uma encomenda.\n\n");
        printf("  C               Calcula o preco de uma encomenda.\n\n");
        printf("  E               Imprime descricao e quantidade de produto numa encomenda.\n\n");
        printf("  m               Encomenda de maior quantidade de um produto.\n\n");
        printf("  l               Lista os produtos do armazem por ordem (crescente) de preco.\n\n");
        printf("  L               Lista os produtos de uma encomenda por ordem alfabetica.\n\n");
        printf("ENTER             Acede a menu informativo.\n\n");
        printf("  x               QUIT.\n\n");


return;
}










/*################################################################################################################################################*/

                                                                /* M A I N */

/*################################################################################################################################################*/
                        
                        
                         /* Na funcao main deste projeto associou se a variavel comando as teclas pressionadas pelo
                                             utilizador,terminando o programa com a tecla 'x'. */


int main(){
        
     int comando;

        while((comando=getchar())!='x'){           
                
                switch(comando){
                        /*
                        case '\n':
                               menu_informativo();  NOTA:criei este comando apesar de nao estar no enunciado porque achei que tornaria o programa mais user friendly
                               break; */

                        case 'a':  
                                                
                                adiciona_novo_produto();            
                                break;
                                                                                                
                        

                        case 'q':  
                                                
                                adiciona_stock();
                                break;
                                                                                                

                                      
                        case 'r':  
                                                
                                remove_stock();
                                break;
                                        

                                       
                        case 'p':  

                                altera_precos();
                                break;
                                     

                        case 'N':
                        
                                cria_nova_encomenda();             
                                break;
                                        
                                        
                        case 'A':
                                
                                adiciona_produto_a_encomenda();
                                break;
                                        
                                        
                        
                        case 'R':
                                        
                                remove_produto_encomenda();
                                break;
                                     

                        case 'C':
                                
                                calcula_custo_encomenda();
                                break;
                                        
                                       
                        case 'E':
                                
                                lista_descricao_qtd();
                                break;
                                        
                                      
                        case 'm':
                        
                                avaliadora_qtd_produto();
                                break;
                                       
                                        
                        case 'l':
                                
                                lista_produtos_preco();
                                break;
                                        
                                      
                        case 'L':
                                
                                lista_descricao();
                                break;


                                     
                }
        }      
        

return 0;
}