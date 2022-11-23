#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define DIM 10000 /*numero max de produtos*/
#define maxwht 200

long len; /* Variavel do tamanho do input dado pelo utilizador */
int idp=0,ide=0; /* contador dos produtos e contador das encomendas */

/* struct com informacoes acerca do produto */
typedef struct Produtos{
    char descricao[62];
    int preco;
    int peso;
    int qtd;
} List_Prod; /* struct chamada de List_Prod */

/* struct de encomendas com a lista de produtos e a sua quantidade e peso total da encomenda */
typedef struct encomenda{
    int qtd_produto[maxwht];
    int iden_prod; /* quantidade de produtos na encomenda / seu identificador */
    int peso;
    int produtos[maxwht]; /* maximo de  200 produtos por encomenda ja que o o maximo de peso e 200 e o minimo de que um produto pesa e 1 */
}Encomenda; /* struct chamada de Encomenda */

List_Prod lista_main[DIM]; /* lista dos produtos, inicializacao de uma struct com um vetor */
Encomenda order[500]; /* encomendas, inicializacao de uam struck com um vetor, sendo 500 o numero maximo de encomendas */


/* funcao que devolve a identificacao do produto na encomenda, se nao encontrar devolve -1
   a funcao recebe a lista dos produtos da ecomenda, a identificacao do produto no stock e a quantidade de produtos que existem na encomenda */
int achar_produto(int s[maxwht],int idp,int qtd){
    int i;
    for(i=0;i<qtd;i++){
        if(idp==s[i]) return i;
    }
    return -1; /* -1 se o produto nao existir na encomenda */
}

/* funcao que adiciona um novo produto ao sistema, o input e dado por 'a descricao:preco:peso:qtd' e a saida e 'Novo produto <idp>.' onde '<idp>' e o didentificador do produto criado	*/
int Novo_Prod(char s[DIM]){
    int pontos=0, d=0, i;/*contador dois pontos / descricao */
    
    len=strlen(s); /*tamanho da string que foi introduzida */
    
    lista_main[idp].preco=lista_main[idp].peso=lista_main[idp].qtd=0; /* inicia a struct do novo produto */
    
    for(i=2;i<len-1;i++){ /* este ciclo for serve para separar o input nas varias opcoes do produto */
        if(s[i]==':'){ /* conta o numero de ':' foram encontrados */
            pontos++;
        }
        else if(pontos==0){
            lista_main[idp].descricao[d]=s[i]; /* retira do input a string da descricao */
            d++;
        }
        else if(pontos==1){
            lista_main[idp].preco=lista_main[idp].preco*10+s[i]-48; /* retira do input o preco e subtrai por 48 cada algarismo pois o input e dado por caracters e em ascii e o numero 0 e dado por 48 */
        }
        else if(pontos==2){
            lista_main[idp].peso=lista_main[idp].peso*10+s[i]-48; /* retira do input o peso */
        }
        else if(pontos==3){
            lista_main[idp].qtd=lista_main[idp].qtd*10+s[i]-48; /* retira do input o quantidade */
        }
    }
    idp++; /* numero de produtos diferentes no stock */
    return idp-1; /* identificacao do produto no stock, e dado de 0-9999 */
}

/* funcao que adiciona stock a um produto que ja existe no sistema, o input e dado por 'q idp:qtd' e nao devolve nada. Se o produto nao existir no sistema a funcao devolve um erro 'Impossivel adicionar produto <idp> ao stock. Produto inexistente.' */
void Add_Stock(char s[maxwht]){
    int pontos=0, d=0, n=0;
    int i;
    len=strlen(s);
    
    for(i=2;i<len-1;i++){
        if(s[i]==':'){ /* conta o numero de ':' foram encontrados */
            pontos++;
        }
        else if(pontos==0){
            d=d*10+s[i]-48; /* retira do input a identificacao do produto e subtrai por 48 cada algarismo pois o input e dado por caracters e em ascii e o numero 0 e dado por 48 */
        }
        else if(pontos==1){
            n=n*10+s[i]-48; /* retira do input a quantidade do produto */
        }
    }
    if(d>idp-1) printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",d);
    else lista_main[d].qtd+=n; /* aumenta na struct do produto a quantidade de produto adicionada */
}

/* funcao que cria uma nova encomenda e devolve a identificacao (<ide>) da nova encomenda 'Nova encomenda <ide>.', com o input 'N' */
int New_Order(){
    order[ide].peso=0; /* peso inicial == 0*/
    order[ide].iden_prod=0; /* contador ou num de produtos == 0 */
    ide++; /* e aumentado o numero de encomendas */
    return ide-1; /* identificacao da nova encomenda */
}

/* funcao que adiciona produtos a uma encomenda, input 'A ide:idp:qtd' e devolve nada excepto com e gerado um erro */
void New_Prod_Ord(char s[DIM]){
    int pontos=0, d=0, n=0, q=0;
    int i,num_lista; /* num_lista e o numero do produto na encomenda */
    len=strlen(s);
    for(i=2;i<len-1;i++){
        if(s[i]==':'){
            pontos++;
        }
        else if(pontos==0){ /* identificador encomenda */
            d=d*10+s[i]-48;
        }
        else if(pontos==1){ /* identificador produto */
            n=n*10+s[i]-48;
        }
        else if(pontos==2){ /* quantidade produto */
            q=q*10+s[i]-48;
        }
    }
    num_lista=achar_produto(order[d].produtos, n, order[d].iden_prod); /* e achado o numero do produto na encomenda, se nao for achado tem valor -1 */
    if(d>=ide){ /* se o ide da encomenda introduzido no input for maior que o numero de encomendas quer dizer que a mesma nao existe no sistema */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",n,d);
    }
    else if(n>idp-1){ /* se idp do produto introduzido no input for maior que o numero de produtos quer dizer que nao existe no sistema */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",n,d);
    }
    else if(q>lista_main[n].qtd){ /* se a quantidade introduzida no input for maior que a quantidade no stock do produto retorna um erro */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",n,d);
    }
    else if(order[d].peso+lista_main[n].peso*q>maxwht){ /* se o peso maximo de 200 for ultrapassado e gerado um erro */
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",n,d);
    }
    else{
        if(num_lista!=-1){ /* se o produto ja existe na encomenda */
            order[d].qtd_produto[num_lista]+=q; /* aumentar a qtd do produto */
            order[d].peso+=lista_main[n].peso*q; /* aumentar o peso total da encomenda */
            lista_main[n].qtd-=q; /* e retirado do stock */
        }
        else{ /* o produto nao existe na encomenda */
            order[d].produtos[order[d].iden_prod]=n; /* idp do produto na encomenda */
            order[d].qtd_produto[order[d].iden_prod]=q; /* defenir a quantidade do produto */
            order[d].peso+=lista_main[n].peso*q; /* aumentar o peso total da encomenda */
            lista_main[n].qtd-=q; /* e retirado do stock */
            order[d].iden_prod+=1; /* passar para o produto seguinte */
        }
    }
}

/* funcao que remove stock ao produto existente com o input 'r idp:qtd', nao devolve nada exceto se ocorrer um erro*/
void Remove_Stock(char s[DIM]){
    int pontos=0, d=0, n=0;
    int i;
    len=strlen(s);
    
    for(i=2;i<len-1;i++){
        if(s[i]==':'){
            pontos++;
        }
        else if(pontos==0){
            d=d*10+s[i]-48; /* identificador do produto */
        }
        else if(pontos==1){
            n=n*10+s[i]-48; /* quantidade pretendida para ser removida */
        }
    }
    
    if(d>idp-1){ /* se idp do produto introduzido no input for maior que o numero de produtos quer dizer que nao existe no sistema */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",d);
        
        }
    else if(n>lista_main[d].qtd){  /* se a quantidade introduzida no input for maior que a quantidade no stock do produto retorna um erro */
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",n,d);
        }
    else lista_main[d].qtd-=n; /* remover a quantidade pretendida */
}

/* funcao que remove produtos a uma encomenda, input 'R ide:idp', devolve nada exceto se ocorrer algum erro */
void Remove_Stock_Order(char s[DIM]){
    int pontos=0, d=0, n=0;
    int i,q;
    len=strlen(s);
                   
    for(i=2;i<len-1;i++){
        if(s[i]==':'){
            pontos++;
        }
        else if(pontos==0){
            d=d*10+s[i]-48; /* identificador encomenda */
        }
        else if(pontos==1){
            n=n*10+s[i]-48; /* identificador produto */
        }
    }
    
    q=achar_produto(order[d].produtos, n, order[d].iden_prod); /* identificacao do produto na encomenda */
    
    if(d>ide-1){ /* se o ide da encomenda introduzido no input for maior que o numero de encomendas quer dizer que a mesma nao existe no sistema */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",n,d);
    }
    else if(n>idp-1){ /* se idp do produto introduzido no input for maior que o numero de produtos quer dizer que nao existe no sistema */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",n,d);
    }
    
    else if(q!=-1){ /* se o produto estiver na encomenda */
        order[d].peso-=order[d].qtd_produto[q]*lista_main[n].peso; /* remocao do peso */
        lista_main[n].qtd+=order[d].qtd_produto[q]; /* aumentar a quantidade de stock */
        order[d].qtd_produto[q]=0; /* a quantidade do produto na encomenda e 0 */
    }
}

/* funcao que calcula o preco total de uma encomenda, input 'C <ide>', output 'Custo da encomenda <ide> <total>', onde o total e o valor total da da encomenda, devolve erro se a encomenda nao existir */
void Cal_Price(char s[DIM]){
    int n=0,total=0;
    int i;
    len=strlen(s);
    for(i=2;i<len-1;i++){
        n=n*10+s[i]-48;
    }
    if(n>ide-1){ /* se o ide da encomenda introduzido no input for maior que o numero de encomendas quer dizer que a mesma nao existe no sistema */
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",n);
    }
    else{
        for(i=0;i<order[n].iden_prod;i++){ /* sao percorridos todos os produtos da encomenda e somado o seu preco * quantidade na encomenda */
            total+=lista_main[order[n].produtos[i]].preco*order[n].qtd_produto[i];
        }
        printf("Custo da encomenda %d %d.\n",n,total);
    }
    return;
}

/* funcao que muda o preco de um produto, input 'p idp:preco', nao devolve nada apenas se ocorrer um erro */
void Change_Price(char s[DIM]){
    int pontos=0,d=0,p=0;
    int i;
    len=strlen(s);
    
    for(i=2;i<len-1;i++){
        if(s[i]==':'){
            pontos++;
        }
        else if(pontos==0){
            d=d*10+s[i]-48; /* identificador produto */
        }
        else if(pontos==1){
            p=p*10+s[i]-48; /* novo preco */
        }
    }
    
    if(idp-1<d){ /* se idp do produto introduzido no input for maior que o numero de produtos quer dizer que nao existe no sistema */
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",d);
    }
    else{
        lista_main[d].preco=p;
    }
}

/* funcao que devolve a descricao e quantidade de um produto numa certa encomenda, input 'E ide:idp', output  '<desc> <qtd>.' onde '<desc>' e a descri??o do produto '<idp>' e '<qtd>' e a quantidade desse produto na encomenda '<ide>', devolve um erro se o produto nao existir no stock ou se a encomenda nao existir */
void Des_Prod_Order(char s[DIM]){
    int pontos=0,e=0,p=0;
    int i,iden;
    len=strlen(s);
    for(i=2;i<len-1;i++){
        if(s[i]==':'){
            pontos++;
        }
        else if(pontos==0){
            e=e*10+s[i]-48; /* identificador encomenda */
        }
        else if(pontos==1){
            p=p*10+s[i]-48; /* identificador produto */
        }
        
    }
    iden=achar_produto(order[e].produtos, p, order[e].iden_prod);
    
    if(e>ide-1){ /* se o ide da encomenda introduzido no input for maior que o numero de encomendas quer dizer que a mesma nao existe no sistema */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",e);
    }
    else if(idp-1<p){ /* se idp do produto introduzido no input for maior que o numero de produtos quer dizer que nao existe no sistema */
        printf("Impossivel listar produto %d. Produto inexistente.\n",p);
    }
    else if(iden==-1){ /* se o produto nao foi adicionado a encomenda a sua quantidade na encomenda e 0 */
        printf("%s 0.\n",lista_main[p].descricao);
    }
    else{
        printf("%s %d.\n",lista_main[p].descricao,order[e].qtd_produto[iden]);
    }
}

/*  funcao que lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situa??o, devera imprimir a encomenda de menor 'id', input 'm idp', output 'Maximo produto <idp> <ide> <qtd>.' onde '<ide>' ? o n?mero da encomenda em que '<idp>' ocorre mais vezes, sendo essa quantidade '<qtd>', gera um erro se esse produto nao existir */
void Ocorre_mais(char s[DIM]){
    int i,p;
    int n=0,max_prod=0,max_enc=0;
    len=strlen(s);
    for(i=2;i<len-1;i++){
        n=n*10+s[i]-48; /* identificacao do produto */
    }
    if(n>idp-1) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",n);
    else{
        for(i=0;i<ide;i++){ /* percorrer todas as encomendas */
            p=achar_produto(order[i].produtos, n, order[i].iden_prod); /* achar o produto na encomenda */
            if(p!=-1){ /* se achar */
                if(order[i].qtd_produto[p]>max_prod){ /*compara com a quantidade maxima anteriormente estabeleciada, se for maior e estabeleciade uma nova quantidade maxima e a encomenda onde ocorre e guardada*/
                    max_enc=i;
                    max_prod=order[i].qtd_produto[p];
                }
            }
        }
        if(max_prod!=0){ /* se a encomenda nao existir devolve nada */
            printf("Maximo produto %d %d %d.\n",n,max_enc,max_prod);
        }
    }
}

/* junta os dois subarrays de arr, o primeiro subarray e arr[l..m], o segundo subarray e arr[m+1..r] */
void merge(int arr[], int l, int m, int r){
    int i,j,k;
    int n1=m-l+1;
    int n2=r-m;
  
    /* arrays esquerdo e direito*/
    int L[DIM/2],R[DIM/2];
  
    /* copia as metades do array inicial para o array e para o array R */
    for(i=0;i<n1;i++){
        L[i] = arr[l+i];
    }
    for (j=0;j<n2;j++){
        R[j]=arr[m+1+j];
    }
  
    /* juntar o arrays novamente para o arr[l..r] */
    i=0;
    j=0;
    k=l;
    
    while(i<n1 && j<n2){
        if (lista_main[L[i]].preco <= lista_main[R[j]].preco){
            arr[k]=L[i];
            i++;
        }
        else{
            arr[k]=R[j];
            j++;
        }
        k++;
    }
  
    /* e copiado o resto de L, se houver algum */
    while(i<n1){
        arr[k]=L[i];
        i++;
        k++;
    }
  
    /* e copiado o resto de L, se houver algum */
    while(j<n2){
        arr[k]=R[j];
        j++;
        k++;
    }
}

/* algoritmo de ordenacao merge sort levemente alterado para ordenar arrays de acordo com o preco dos produtos, l e o inicio do array, r o fim do array e m onde se faz o split do array */
void mergeSort(int arr[], int l, int r){
    if (l < r){ /* o mesmo que (l+r)/2, mas foge do overflow for */
        int m = l+(r-l)/2;
  
        /* ordena a primeira e a segunda parte */
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
  
        merge(arr, l, m, r);
    }
}
/* funcao que lista todos os produtos por ordem crescente de preco, input 'l', output 'Produtos \n
* <desc1> <preco1> <qtd1 em stock>\n (...) ' */
void Price_Growing(){
    int i,j;
    int arr[DIM];
    
    for (i=0;i<idp;i++){ /* mete todos os produtos num array*/
        arr[i] = i;
    }
    
    mergeSort(arr,0,idp-1);
    
    printf("Produtos\n");
    
    for(j=0;j<idp;j++){ /* percorre a lista organizada e imprime o produto e o sua repetiva descricao, preco e quantidade */
        printf("* %s %d %d\n",lista_main[arr[j]].descricao,lista_main[arr[j]].preco,lista_main[arr[j]].qtd);
    }
}
/* funcao que lista todos os produtos de uma encomenda por ordem alfabetica da descricao, input  'L <ide>', output 'Encomenda <ide>\n * <desc1> <preco1> <qtd1 na ide> (...)', esta funcao e usado o algoritmo de ordenacao insertion sort alterado para que orderne um array com stings por ordem alfabetica */
void Order_AZ(char s[DIM]){
    int i,j,V,tam;
    int e=0;
    char a[DIM][62];
    char v[62];
    int n[DIM];
    
    len=strlen(s);
    
    for(i=2;i<len-1;i++){
        e=e*10+s[i]-48; /* identificacao da encomenda */
    }
    
    if(e>ide-1){ /* se o ide da encomenda introduzido no input for maior que o numero de encomendas quer dizer que a mesma nao existe no sistema */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",e);
    }
    else{
        printf("Encomenda %d\n",e);
        tam = order[e].iden_prod; /* quantidade de produtos diferentes na encomenda */
        for(i=0;i<tam;i++) n[i]=order[e].produtos[i]; /* meter os produtos num array auxiliar para que possa ser ordenado */
        for(i=0;i<tam;i++) strcpy(a[i],lista_main[n[i]].descricao); /* meter a descricao num array para ser ordenado com o array da identificacao do produtos */

        for(i=0;i<tam;i++){
            for (i=1;i<tam;i++) {
                strcpy(v,a[i]);
                V=n[i];
                j = i-1;
                /* mover os elementos que sao maiores para uma posicao a frente */
                while (j>=0 && strcmp(v, a[j])<0){ /* strcmp se o primeiro elemento for maior que o segundo devolve um valor <0 */
                    strcpy(a[j+1],a[j]);
                    n[j+1] = n[j];
                    j--;
                }
                strcpy(a[j+1],v);
                n[j+1]=V;
            }
        }
        
        for(i=0;i<tam;i++){
            j=achar_produto(order[e].produtos, n[i], tam);
            if(order[e].qtd_produto[j]!=0){
                printf("* %s %d %d\n",a[i],lista_main[n[i]].preco,order[e].qtd_produto[j]);
            }
        }
    }
}

int main() {
    char entrada[DIM];
    
    while(entrada[0]!='x'){
        fgets(entrada,DIM,stdin); /* copia o input para uma string */
        switch (entrada[0]) { /* switch que perante o primeiro elemento da string chama uma funcao */
            case 'a':
                printf("Novo produto %d.\n",Novo_Prod(entrada));
                break;
                
            case 'q':
                Add_Stock(entrada);
                break;
                    
            case 'N':
                printf("Nova encomenda %d.\n",New_Order());
                break;
                
            case 'A':
                New_Prod_Ord(entrada);
                break;
                
            case 'r':
                Remove_Stock(entrada);
                break;
                
            case 'R':
                Remove_Stock_Order(entrada);
                break;
                
            case 'C':
                Cal_Price(entrada);
                break;
                
            case 'p':
                Change_Price(entrada);
                break;
                
            case 'E':
                Des_Prod_Order(entrada);
                break;
                
            case 'm':
                Ocorre_mais(entrada);
                break;
                
            case 'l':
                Price_Growing();
                break;
                
            case 'L':
                Order_AZ(entrada);
                break;
            
        }
    }
    return 0;
}
	
