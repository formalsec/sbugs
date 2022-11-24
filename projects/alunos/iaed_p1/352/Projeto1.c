#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAX 63
#define TOTAL 80
#define MAXENC 500
#define MAXPROD 10000
#define SETE 7
#define DUZENTOS 200
int var[3];                    /* tabela que guarda as variaveis(nao contando com a descricao), tamanho 3 porque e o numero maximo de variaveis intruduzidas
                                para alem da descricao*/
char descricao[MAX];           /* variavel(string) que guarda a descricao de um produto caso o comando intrudizido seja a*/
char v1[1];                    /* variavel que serve para verificar a primeira letra de um input,ou seja, o proximo comando a executar*/
int contadorp=0,contadorenc=0; /* contadorp--> variavel que conta o numero de produtos que existem, aumenta sempre que um produto seja criado
                                  contadorenc--> variavel que conta o numero de encomendas existentes, aumenta sempre que uma encomenda seja criada*/

/* a funcao le_input vai ler a a linha de comandos intruduzida(tirando a primeira letra), primeiro verifica se a primeira letra guardada e um a,
   se for, primeiro vai guardar a descricao e so depois vai guardar o resto das variaveis, caso seja qualquer outra letra, vai guardar logo as
   variaveis sem passar pela leitura da string*/
void le_input(){
    int i,c,o=0;
    if (v1[0]=='a'){                         /* caso a primeira letra seja a, antes de guardar as variaveis numericas tem que se guardar a descricao */
        for (i=0;i<TOTAL;i++){               /* ciclo que vai guardar a descricao, da break quando encontrar ':' */
            c=getchar();
            if (c=='\n' || c==EOF){
                break; }
            else{
                if (c==':'){
                    break;
                }
                else if (c!=' '){
                    descricao[i-1]=c;
                    descricao[i]='\0';
                }
            }
        }
    }
    var[0]=0;
    var[1]=0;
    var[2]=0;
    for (i=0;i<MAX;i++){                   /* ciclo que ira guardar as variaveis numericas numa tabela com tamanho 3, porque e o maximo de variaveis numericas 
                                              que se recebe de uma vez */      
        c=getchar();
        if (c=='\n' || c==EOF){
            break; }
        else{
            if (c==':'){
                o+=1;
            }
            else if (c !=' '){            /* caso o c seja diferente a \n, EOF, ' ' e :, significa que se trata de informacao referente as variaveis */
                var[o]=var[o]*10 + c -'0';
            }
        }
    }
}

typedef struct produtos{
    int peso,qtd,idp,preco;
    char descr[MAX];
} prod;

prod stock[MAXPROD];

typedef struct encomenda{
    int peso,ide,qtd[MAXPROD],idp;
    char prod[MAXPROD];
}encomenda;

encomenda encomendas[MAXENC];

/* compara_s--> funcao auxiliar a merge_L que vai retornar 1 se as strings estiver desorgaganizadas alfabeticamente ,retorna 0 caso contrario*/
int compara_s(char a[],char b[]){
    int r;
    for (r=0; r < MAX ;r++){
        if (a[r]>b[r])
            return 1;
        else if (a[r]<b[r])
            return 0;
    }
    return 0;
}

/* funcao auxiliar a mergesort_l que vai ordenar os pre?os por ordem crescente */
void merge_l(int a[],int l,int m,int r){
    int aux[MAXPROD];
    int i,j,k;
    for (i=m+1;i>l;i--)
        aux[i-1]=a[i-1];
    for (j=m;j<r;j++)
        aux[r+m-j]=a[j+1];
    for (k=l;k<=r;k++)
        if (stock[aux[j]].preco<stock[aux[i]].preco || (stock[aux[j]].preco == stock[aux[i]].preco && aux[j]<aux[i])) 
        /* condicao que compara o preco dos dois ids(aux[j] e aux[i])*/
            a[k]=aux[j--];
        else
            a[k]=aux[i++];
}

/* Algoritmo do merge sort para ordenar por ordem crescente a lista de precos */
void mergesort_l(int a[],int l,int r){
    int m=(r+l)/2;
    if (r<=l)
        return;
    mergesort_l(a,l,m);
    mergesort_l(a,m+1,r);
    merge_l(a,l,m,r);
}

/* funcao auxiliar a mergesort_L que vai ordenar os ids dos produtos alfabeticamente tendo em conta a descricao que lhes esta associada */
void merge_L(int a[],int l,int m,int r){
    int aux[MAXPROD];
    int i,j,k;
    for (i=m+1;i>l;i--)
        aux[i-1]=a[i-1];
    for (j=m;j<r;j++)
        aux[r+m-j]=a[j+1];
    for (k=l;k<=r;k++)
        if (compara_s(stock[aux[i]].descr,stock[aux[j]].descr))             /* condicao que vai comparar as descricricoes dos ids aux[i] e aux[j],executa a 
                                                                               condicao caso a descricao estas nao estejam por ordem alfabetica */
            a[k]=aux[j--];
        else
            a[k]=aux[i++];
}

/* Algoritmo do merge sort para ordenar alfabeticamente a lista de ids relativamente a sua descricao */
void mergesort_L(int a[],int l,int r){
    int m=(r+l)/2;
    if (r<=l)
        return;
    mergesort_L(a,l,m);
    mergesort_L(a,m+1,r);
    merge_L(a,l,m,r);
}

/* a func_a vai adicionar um novo produto ao stock(utilizando a estrutura produtos) e vai-lhe atribuir o seu peso, descricao,
   quantidade e preco(utilizando a estrutura produtos)*/
void func_a(){
    int i;
    stock[contadorp].idp=contadorp;
    for(i=0;i<MAX;i++){                                          /* ciclo for que fara com que a descricao do produto fique guardada*/
        if(descricao[i]=='\n' || descricao[i]==EOF)
            break;
        else {
            stock[contadorp].descr[i] = descricao[i];
            stock[contadorp].descr[i+1] = '\0';
        }
    }
    stock[contadorp].preco=var[0];                             
    stock[contadorp].peso=var[1];
    stock[contadorp].qtd=var[2];
    printf("Novo produto %d.\n",stock[contadorp].idp);
    contadorp+=1;
}

/* a func_q adiciona stock verifica se o produto intruduzido existe, se existir adiciona-lhe stock*/
void func_q(){
    if (var[0]<contadorp){                   /*caso o id introduzido seja menor que o numero de produtos existentes significa que esse produto existe*/
        stock[var[0]].qtd+=var[1];
    }
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",var[0]);
    }
}

/* a func_N cria uma nova encomenda , define a quantidade de todos os produtos que lhe possam vir a ser adicionados como 0 e define o peso dessa
   encomenda como 0*/
void func_N(){
    int o;
    encomendas[contadorenc].idp=0;                        /* define o nr de produtos de uma encomenda a 0 */
    encomendas[contadorenc].ide=contadorenc;
    for (o=0;o<MAXPROD;o++){                    /* ciclo for que ira definir a quantidade de todos os produtos possiveis(10000) a 0 nesta encomenda */
        encomendas[contadorenc].qtd[o]=0;
    }
    encomendas[contadorenc].peso=0;                            
    printf("Nova encomenda %d.\n",encomendas[contadorenc].ide);
    contadorenc+=1;
}

/* a func_A adiciona uma quantidade de um produto a uma encomenda, atualiza o peso dessa encomenda e subtrai essa quantidade ao stock */
void func_A(){
    if (var[0]>=contadorenc)              /* se o id da encomenda for maior do que o contador de encomendas e porque a encomenda nao existe*/
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",var[1],var[0]);
    else if(var[1]>=contadorp)      /*caso o id introduzido seja maior ou igual que o contador de produtos existentes significa que esse produto nao existe*/
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",var[1],var[0]);
    else if(stock[var[1]].qtd<var[2])                    /* verifica se a quantidade a adicionar existe em stock*/
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",var[1],var[0]);
    else if((encomendas[var[0]].peso+(var[2]*stock[var[1]].peso))>200)              /* calcula o peso com o novo produto e ve se e maior do que 200*/
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",var[1],var[0]);
    else{
        encomendas[var[0]].idp+=1;                                       
        encomendas[var[0]].qtd[var[1]]+=var[2];                         
        encomendas[var[0]].peso=encomendas[var[0]].peso+(var[2]*stock[var[1]].peso);       
        stock[var[1]].qtd-=var[2];
    }
}

/* a func_r remove stock a um produto existente */
void func_r(){
    if (var[0]>=contadorp)         /*caso o id introduzido seja maior ou igual do que o contador de produtos existentes significa que esse produto nao existe */
       printf("Impossivel remover stock do produto %d. Produto inexistente.\n",var[0]);
    else if(stock[var[0]].qtd<var[1])      /* verifica se existe em stock quantidade suficiente para remover do produto */
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",var[1],var[0]);
    else
        stock[var[0]].qtd-=var[1];               
}

/* a func_R remove a toda a quantidade de um produto a uma encomenda, devolve essa quantidade ao stock e recalcula o peso da encomenda */
void func_R(){
    int n;
    if (var[0]>=contadorenc)                    /* se o id da encomenda for maior do que o contador de encomendas e porque a encomenda nao existe*/
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",var[1],var[0]);
    else if (var[1]>=contadorp)   /*caso o id introduzido seja maior ou igual do que o contador de produtos existentes significa que esse produto nao existe */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",var[1],var[0]);
    else{
        n=encomendas[var[0]].qtd[var[1]];                     
        encomendas[var[0]].qtd[var[1]]=0;                      
        stock[var[1]].qtd+=n;
        encomendas[var[0]].peso-= (n*(stock[var[1]].peso));   
    }

}

/* a func_C calcula o custo de uma encomenda */
void func_C(){
    int i,custo=0;
    if (var[0]>=contadorenc)                              /* se o id da encomenda for maior do que o contador de pencomendas e porque nao existe*/
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",var[0]);
    else{
        for (i=0;i<MAXPROD;i++){
            custo+=((encomendas[var[0]].qtd[i])*stock[i].preco);            
        }
        printf("Custo da encomenda %d %d.\n",var[0],custo);
    }
}

/* a func_p altera o preco de um produto no sistema */
void func_p(){
    if (var[0]>=contadorp)                        /* se o id do produto for maior ou igual do que o contador de produtos e porque nao existe*/
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",var[0]);
    else{
        stock[var[0]].preco=var[1];
    }
}

/* a func_E lista a descricao e a quantidade de um produto numa encomenda*/
void func_E(){
    if (var[0]>=contadorenc)                           /* se o id da encomenda for maior ou igual do que o contador de encomendas e porque a encomenda nao existe*/
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",var[0]);
    else if (var[1]>=contadorp)                       /* se o id do produto for maior ou igual do que o contador de produtos e porque nao existe*/
        printf("Impossivel listar produto %d. Produto inexistente.\n",var[1]);
    else{
        printf("%s %d.\n",stock[var[1]].descr,encomendas[var[0]].qtd[var[1]]);
    }
}

/* a func_m lista o id da encomenda em que um certo produto ocorre o mais vezes indicando o id do produto, a sua quantidade e o id da encomenda*/
void func_m(){
    int i,maximo=0,idatual,estado=0;
    for (i=0;i<contadorenc;i++){                     /* ciclo for que vai verificar se o produto introduzido ocorre em alguma das encomendas */
        if ((encomendas[i].qtd[var[0]])>0){          /* se ocorrer, troca a variavel estado para 1 */
            estado=1;
            break;
        }
    }
    if (var[0]>=contadorp)                                /* se o id do produto for maior ou igual do que o contador de produtos e porque nao existe*/
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",var[0]);
    else if (contadorenc<1 || estado==0){          /* caso nao hajam encomendas ou o produto introduzido nao ocorra em nenhuma encomenda nao faz se faz nada*/
    }
    else{
        for (i=0;i<contadorenc;i++){
            if((encomendas[i].qtd[var[0]])>maximo){           /* caso a quantidade do produto nesta encomenda seja maior do que a quantidade maxima ja registada*/
                maximo=(encomendas[i].qtd[var[0]]);           /* atualiza-se o maximo ja registado e o id da encomenda onde tal ocorreu*/
                idatual=i;
            }
        }
        printf("Maximo produto %d %d %d.\n",var[0],idatual,maximo);
    }
}

/* a func_l vai listar todos os produtos existentes por ordem crescente de preco, para isso comeco por criar uma lista com todos os ids e
 vai ordena-la por ordem crescente de precos*/
void func_l(){
    int z,o,l_precos[(MAXPROD)];
    for (o=0;o<contadorp;o++){           /* ciclo que adiciona a uma tabela todos os ids de produtos ja existentes*/
        l_precos[o]=o;
    }
    mergesort_l(l_precos,0,(contadorp-1));            /* funcao que vai ordenar a lista com os precos */
    printf("Produtos\n");
    for(z=0;z<contadorp;z++){         /* ciclo que percorre a lista l_precos e escreve no output a descricao, preco e quantidade correspondentes ao id em questao */
        printf("* %s %d %d\n",(stock[l_precos[z]].descr),(stock[l_precos[z]].preco),(stock[l_precos[z]].qtd));
    }
}

/* a func_L vai listar todos os produtos existentes numa encomenda por ordem alfabetica de descricao, para isso comeco por criar uma tabela
   com todos os ids dos produtos que nessa encomenda tem uma quantidade maior que 0 e vou ordena-la de acordo com as suas descricoes*/
void func_L(){
    int enc_d[DUZENTOS];
    int i,u,o=0;
    if (var[0]>=contadorenc)              /* se o id da encomenda for maior ou igual do que o contador de encomendas e porque a encomenda nao existe */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",var[0]);
    else{
        for (u=0;u<(MAXPROD);u++){                   /* ciclo for que verifica se a quantidade de um produto numa encomenda e maior que 0 */
            if ((encomendas[var[0]].qtd[u])>0){
                enc_d[o]=stock[u].idp;          /* se for vai passar o seu id para a tabela que vai guardar todos os ids de produtos que estao nesta encomenda*/
                o+=1;
                if ((o-1)==encomendas[var[0]].idp)   /* este if compara se o numero de produtos na tabela dos ids ja chegou ao maximo de produtos nessa encomenda*/
                break;                                    /* se isto se verificar termina este ciclo */
            }
        }
        mergesort_L(enc_d,0,o-1);           /* funcao que vai ordenar alfabeticamente os ids de acordo com a sua descricao*/
        printf("Encomenda %d\n",var[0]);
        for (i=0;i<o;i++) {                  
            printf("* %s %d %d\n", stock[enc_d[i]].descr, (stock[enc_d[i]].preco), (encomendas[var[0]].qtd[enc_d[i]]));
        }
    }
}

/* que_func--> funcao que apos ler a primeira lera do comando, verifica qual a funcao que tem que chamar em funcao do dessa primeira letra */
void que_func(){
    switch(v1[0]){
        case 'a':
            func_a();
            break;
        case 'q':
            func_q();
            break;
        case 'N':
            func_N();
            break;
        case 'A':
            func_A();
            break;
        case 'r':
            func_r();
            break;
        case 'R':
            func_R();
            break;
        case 'C':
            func_C();
            break;
        case 'p':
            func_p();
            break;
        case 'E':
            func_E();
            break;
        case 'm':
            func_m();
            break;
        case 'l':
            func_l();
            break;
        case 'L':
            func_L();
            break;
    }
}

/* funcao main--> vai guardar a primeira letra do input numa variavel e chama a funcao que le o resto do input, apos isto, chama a funcao que verifica
   que letra esta guardada em v1[0] e depois fica a espera de um novo input para ler ate que este comece por x, onde para e termina o programa*/
int main(){
    v1[0]=getchar();
    while (v1[0]!='x'){
        le_input();
        que_func();
        v1[0]=getchar();
    }
    return 0;
}