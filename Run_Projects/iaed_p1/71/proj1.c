#include <stdio.h>
#include <string.h>



/*------Definicao de Constantes------*/

/*maximo de caracteres na descricao dos produtos*/
#define MAXDESC 63                                  
/*maximo de produtos diferentes (idp) no sistema*/
#define MAXPROD 10000  
/*maximo de encomendas*/                             
#define MAXENC 500   
 /*maximo de peso que cada encomenda pode levar*/                               
#define MAXPESO 200                                



/*------ Definicao de Estruturas de Dados ------*/
typedef struct{

    int idp;
    char descricao[MAXDESC+1];
    int preco;
    int peso;
    int qtd;

} Produto;

typedef struct {

    /*vetor com idps dos produtos de cada encomenda*/
    int prodenc[MAXPESO];
    /*numero de produtos por encomenda*/                           
    int nprodutos;  

} Encomenda;



/*------Variaveis Globais------*/

/*vetor de produtos do sistema, onde o indice corresponde ao idp*/
Produto listaprod[MAXPROD];

/*vetor de encomendas, onde o indice corresponde ao ide*/
Encomenda listaenc[MAXENC];   

/*numero total de produtos no sistema*/
int prodatuais = 0;

/*numero total de encomendas no sistema*/
int encatuais=0; 

/*seleciona o tipo de ordenacao a fazer nos comandos l e L*/
int varcontrolo;       



/*------Prototipos------*/

void addlistaprod();
void addstockprod();
void addenc();
void addprodenc();
void delqtdprod();
void delprodenc();
void calculacusta();
void alterapreco();
void lista_descqtd();
void idppopularide();
void listaprod_preco();
void listaprod_desc();
int existe_prod(int idprod);
int existe_enc(int idenc);
int qtd_suficiente(int idprod, int qtdprod);
int peso_excesso(int idenc, int idprod, int qtdprod);
void produtos_existentes(int vp[]);
void merge(int v[], int l, int mid, int r);
void mergeSort(int v[], int l, int r);



/*-------------------------MAIN---------------------------*/
/*                                                        */
/*  le a letra inserida pelo utilizador e executa o       */
/*  comando respetivo                                     */                                        
/*                                                        */
/*--------------------------------------------------------*/
int main()
{
    char comando;

    while ((comando = getchar())!='x') {

        switch(comando) {

            case 'a':
                addlistaprod();
                break;

            case 'q':
                addstockprod();
                break;

            case 'N':
                addenc();
                break;

            case 'A':
                addprodenc();
                break;
            
            case 'r':
                delqtdprod();
                break;
            
            case 'R':
                delprodenc();
                break;
            
            case 'C':
                calculacusta();
                break;

            case 'p':
                alterapreco();
                break;
            
            case 'E':
                lista_descqtd();
                break;
            
            case 'm':
                
                idppopularide();
                break;

            case 'l':
                listaprod_preco();
                break;
            
            case 'L':
                listaprod_desc();
                break;

            default:
                printf("ERRO: comando desconhecido.\n");
                break;


        }

        /*le \n introduzido pelo utilizador*/
        getchar();                                          

    }

    return 0;

}



/*-----------------------comando a------------------------*/
/*                                                        */
/*  adiciona um novo produto ao sistema                   */
/*                                                        */
/*--------------------------------------------------------*/
void addlistaprod() {

    if (prodatuais < MAXPROD) {

        scanf(" %[^:]:%d:%d:%d", listaprod[prodatuais].descricao,&listaprod[prodatuais].preco,&listaprod[prodatuais].peso,&listaprod[prodatuais].qtd);
        
        /*o idp do produto ainda corresponde ao numero de prodatuais (pois ainda nao foi incrementado)*/
        listaprod[prodatuais].idp = prodatuais;
        
        printf("Novo produto %d.\n", prodatuais);
        
        prodatuais++;

    }

}



/*-----------------------comando q------------------------*/
/*                                                        */
/*  adiciona stock a um produto do sistema                */
/*                                                        */
/*--------------------------------------------------------*/
void addstockprod() {

    int idprod, qtdprod;

    scanf("%d:%d",&idprod,&qtdprod);

    if (!existe_prod(idprod)) {

        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idprod);
        
        return;
        
    }

    listaprod[idprod].qtd += qtdprod;       

}



/*-----------------------comando N------------------------*/
/*                                                        */
/*  cria uma nova encomenda no sistema                    */
/*                                                        */
/*--------------------------------------------------------*/
void addenc() {

    encatuais++;                                                    
    
    printf("Nova encomenda %d.\n",encatuais-1);
}



/*--------------------------comando A---------------------*/
/*                                                        */
/* adiciona uma dada quantidade de um produto a uma       */ 
/* encomenda                                              */
/*                                                        */
/*--------------------------------------------------------*/
void addprodenc() {

    int idenc, idprod, qtdprod;

    scanf("%d:%d:%d",&idenc,&idprod,&qtdprod);

    if (!existe_enc(idenc)) {
        
        printf ("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idprod,idenc);
        
        return;
    }
    
    if (!existe_prod(idprod)) {
        
        printf ("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idprod,idenc);
        
        return;

    }

    if (!qtd_suficiente(idprod,qtdprod)) {
        
        printf ("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idprod,idenc);
        
        return;
    }


    if (!(peso_excesso(idenc, idprod, qtdprod))) {

        printf ("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idprod,idenc);
        
        return;

    }

    /*como se adiciona um a um, vai-se decrementando a qtd inserida ate ser 0*/
    while (qtdprod > 0) {
        

        listaenc[idenc].prodenc[listaenc[idenc].nprodutos] = listaprod[idprod].idp;
        
        listaenc[idenc].nprodutos ++;
        
        listaprod[idprod].qtd --;

        qtdprod --;


    }

}



/*-----------------------comando r------------------------*/
/*                                                        */
/* remove uma certa quantidade a um produto               */
/*                                                        */
/*--------------------------------------------------------*/
void delqtdprod() {

    int idprod, qtdprod;

    scanf("%d:%d",&idprod,&qtdprod);

    if (!existe_prod(idprod)) {

        printf ("Impossivel remover stock do produto %d. Produto inexistente.\n", idprod);

        return;
    }

    if (!qtd_suficiente(idprod,qtdprod)) {

        printf ("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtdprod, idprod);

        return;
    }

    listaprod[idprod].qtd -= qtdprod;


}



/*-----------------------comando R------------------------*/
/*                                                        */
/* remove um produto de uma encomenda                     */
/*                                                        */
/*--------------------------------------------------------*/
void delprodenc() {

    int idenc, idprod,i;

    scanf("%d:%d",&idenc,&idprod);

    if (!existe_enc(idenc)) {

        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idprod, idenc);
        
        return;
        
    }

    if (!existe_prod(idprod)) {

        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idprod, idenc);
        
        return;

    }


    for (i=0; i < listaenc[idenc].nprodutos; i++) {
        
        /* produto na encomenda coincide com o que queremos remover*/
        if (listaenc[idenc].prodenc[i] == idprod) {                                                 

            /*movemos o ultimo produto do vetor de produtos para o lugar do produto que se quer eliminar (para evitar espacos vazios)*/
            listaenc[idenc].prodenc[i] = listaenc[idenc].prodenc[(listaenc[idenc].nprodutos)-1];

            listaenc[idenc].nprodutos --;   

            listaprod[idprod].qtd ++;

            /*reverificar o produto que foi movido*/
            i--;                                                                                      

        }

    }

}



/*-----------------------comando C------------------------*/
/*                                                        */
/* calcula o custo de uma encomenda                       */
/*                                                        */
/*--------------------------------------------------------*/
void calculacusta() {

    int idenc, total = 0, i;

    scanf("%d", &idenc);

    if (!existe_enc(idenc)) {
        
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",idenc);
        
        return;
    }

    for (i=0; i< listaenc[idenc].nprodutos;i++) {

        total += listaprod[listaenc[idenc].prodenc[i]].preco;
    }

    printf("Custo da encomenda %d %d.\n", idenc, total);

    
}



/*-----------------------comando p------------------------*/
/*                                                        */
/* altera o preco de um produto do sistema                */
/*                                                        */
/*--------------------------------------------------------*/
void alterapreco() {

    int idprod, precoprod;

    scanf("%d:%d",&idprod,&precoprod);

    if (!existe_prod(idprod)) {

        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idprod);
        
        return;

    }

    listaprod[idprod].preco = precoprod;

}



/*-----------------------comando E------------------------*/
/*                                                        */
/* lista a descricao e a quantidade de produto numa       */ 
/* encomenda                                              */
/*                                                        */
/*--------------------------------------------------------*/
void lista_descqtd() {

    int idenc, idprod,i,total=0;

    scanf("%d:%d",&idenc,&idprod);

    if (!existe_enc(idenc)) {

        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idenc);
        
        return;

    }

    if (!existe_prod(idprod)) {

        printf("Impossivel listar produto %d. Produto inexistente.\n",idprod);
        
        return;

    }

    for (i=0; i< listaenc[idenc].nprodutos;i++) {

        /*aumentar a quantidade do produto de idp pretendido (idprod), sempre que o encontra na encomenda*/
        if (listaenc[idenc].prodenc[i] == idprod ) {

            total++;
        }

    }

    printf("%s %d.\n", listaprod[idprod].descricao,total);


}



/*-----------------------comando m------------------------*/
/*                                                        */
/* lista o ide da encomenda em que o produto dado ocorre  */
/* mais vezes                                             */
/*                                                        */
/*--------------------------------------------------------*/
void idppopularide() {

    int idprod, enc=0, max=0, i;
    /*encomenda em que ocorre mais vezes*/
    int encpopular;
    /*quantidade do produto numa dada encomenda*/
    int contador=0;

    scanf("%d",&idprod);

    if (!existe_prod(idprod)) {

        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idprod);
        
        return;
    }

    /*inicio na encomenda registada de menor ide e e verificada a quantidade do produto pretendido, uma a uma*/
    while (enc<=encatuais) {

        for (i=0; i < listaenc[enc].nprodutos;i++) {                      

            if (listaenc[enc].prodenc[i] == idprod) {

                contador++;                                                     

            }

        }

        /*quantidade do produto idprod na encomenda enc seja maior que o max*/
        if (contador > max) {

            max = contador;
            encpopular = enc;

        }

        contador = 0;

        enc++;

    }

    /*caso o produto ocorra de facto em alguma das encomendas*/
    if (max>0) {

    printf ("Maximo produto %d %d %d.\n",idprod,encpopular,max);

    }


}



/*-----------------------comando l------------------------*/
/*                                                        */
/* lista os produtos registados no sistema por ordem      */
/* crescente de preco                                     */
/*                                                        */
/*--------------------------------------------------------*/
void listaprod_preco() {

    /*vp e o vetor com os idps dos produtos existentes no sistema*/
    int vp[MAXPROD];
    int i ; 

    /*no merge queremos ordenar pela ordem de preco*/                  
    varcontrolo = 0;

    /*copiamos para um vetor os idps para nao alterar a ordem de listaprod[]*/
    produtos_existentes(vp);

    mergeSort(vp, 0, prodatuais-1);

    printf("Produtos\n");

    for (i = 0; i < prodatuais; i++) {

        printf("* %s %d %d\n",listaprod[vp[i]].descricao,listaprod[vp[i]].preco,listaprod[vp[i]].qtd);
    }

}



/*-----------------------comando L------------------------*/
/*                                                        */
/* lista os produtos de uma dada encomenda por ordem      */
/* alfabetica da descricao de cada produto, imprimindo    */
/* tambem a respetiva quantidade dos mesmos               */
/*                                                        */
/*--------------------------------------------------------*/
void listaprod_desc() {

    int idenc, i; 
    
    /*contador para a quantidade de cada produto*/
    int qtdprod=1;

    /*no merge queremos ordenar pela ordem de preco*/                  
    varcontrolo = 1;

    scanf("%d",&idenc);

    if (!existe_enc(idenc)) {

        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",idenc);

        return;
    }

    mergeSort(listaenc[idenc].prodenc,0,listaenc[idenc].nprodutos-1);

    printf("Encomenda %d\n",idenc);

    for (i=0; i < listaenc[idenc].nprodutos; i++) {

        /*o indice coincide com o fim da encomenda*/
        if (i== (listaenc[idenc].nprodutos-1)) {

            printf("* %s %d %d\n", listaprod[listaenc[idenc].prodenc[i]].descricao, listaprod[listaenc[idenc].prodenc[i]].preco, qtdprod);
            return;
        }

        /*sempre que o idp se repita, incrementamos a quantidade para o produto em questao*/
        if (listaenc[idenc].prodenc[i]==listaenc[idenc].prodenc[i+1]) {

            qtdprod++;
            continue;
        }

        
        printf("* %s %d %d\n", listaprod[listaenc[idenc].prodenc[i]].descricao, listaprod[listaenc[idenc].prodenc[i]].preco, qtdprod);
        /*voltar a colocar a qtd a 1 para contar as quantidades dos produtos seguintes*/
        qtdprod = 1;

    }


}



/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*                   FUNCOES AUXILIARES                   */
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/



/*----------------------existe_prod-----------------------*/
/*                                                        */
/* verifica se o produto de idp igual a idprod existe no  */
/* sistema                                                */
/*                                                        */
/*--------------------------------------------------------*/
int existe_prod(int idprod) {

    if (idprod >= prodatuais) {
        return 0;
    }

    return 1;

}



/*----------------------existe_enc------------------------*/
/*                                                        */
/* verifica se a encomenda de ide igual a idenc existe no */
/* sistema                                                */
/*                                                        */
/*--------------------------------------------------------*/
int existe_enc(int idenc) {

    if (idenc >= encatuais) {
        return 0;
    
    }

    return 1;

}



/*---------------------qtd_suficiente---------------------*/
/*                                                        */
/* verifica se ha em quantidade suficiente no sistema o   */
/* produto de idp <idprod>, para se efetuar altera?oes no */
/* stock                                                  */
/*                                                        */
/*--------------------------------------------------------*/
int qtd_suficiente(int idprod, int qtdprod) {

    if (listaprod[idprod].qtd < qtdprod) {

        return 0;

    }

    return 1;

}



/*---------------------peso_excesso-----------------------*/
/*                                                        */
/* verifica se o peso da encomenda ultrapassa as 200      */
/* unidades                                               */
/*                                                        */
/*--------------------------------------------------------*/

int peso_excesso(int idenc, int idprod, int qtdprod) {

    int i, pesonaenc=0;

    for (i=0; i<listaenc[idenc].nprodutos;i++) {
        
        pesonaenc += listaprod[listaenc[idenc].prodenc[i]].peso;
    }

    if ((pesonaenc + listaprod[idprod].peso * qtdprod)>MAXPESO) {

        return 0;
    }

    return 1;
}

/*-------------------produtos_existentes------------------*/
/*                                                        */
/* cria um vetor com os idps dos produtos existentes no   */
/* sistema                                                */
/*                                                        */
/*--------------------------------------------------------*/
void produtos_existentes(int vp[]) {

    int i;

    for (i=0;i<prodatuais;i++ ) {

        vp[i]=listaprod[i].idp;

    }

}


/*------------------------merge--------------------------*/
/*                                                       */
/* funcao auxiliar ao algoritmo de ordenacao mergeSort   */
/*                                                       */
/*-------------------------------------------------------*/
void merge(int v[], int l, int mid, int r) {

    int i, j, k;
    int n1=0, n2=0;

    /*arrays temporarias, cujo valor max eh MAXPROD/2*/
    int L[5001],R[5000];         

    /*definir valor limite para cada uma da array temporaria*/
    n1 = mid - l + 1;
    n2 = r - mid;

    /*Copiar os elementos para as arrays temporarias*/
    for (i=0;i<n1;i++) {

        L[i] = v[l+i];
    }

    for(j=0; j<n2;j++) {

        R[j] = v[mid+1+j];
    }

    /*indice inicial da primeira array temporaria */
    i = 0;                                
    /*indice inicial da segunda array temporaria  */
    j = 0;                                                         
    /*indice inicial da array que surge da juncao */
    k = l;                                                         


    /*juntar as arrays temporarias a array original*/
    while (i < n1 && j < n2) {

        switch (varcontrolo) {
            
            /*ordenar por ordem crescente de preco*/
            case 0:
        
                if (listaprod[L[i]].preco <= listaprod[R[j]].preco) {

                    v[k] = L[i];

                    i++;

                }

                else {

                    v[k] = R[j];

                    j++;
                }

                k++;
                
                break;
            
            
            /*ordenar por ordem alfabetica de descricao*/
            case 1:
                if (strcmp(listaprod[L[i]].descricao,listaprod[R[j]].descricao) <= 0) {

                    v[k] = L[i];

                    i++;

                }

                else {

                    v[k] = R[j];

                    j++;
                }

                k++;
                break;
        }

        
    }

    /*Copiar os elementos que sobram de L[], caso hajam*/
    while (i < n1) {

        v[k] = L[i];
        i++;
        k++;
        
    }

    /*Copiar os elementos que sobram de R[], caso hajam*/
    while (j < n2) {

        v[k] = R[j];
        j++;
        k++;

    }
}



/*----------------------mergeSort------------------------*/
/*                                                       */
/* algoritmo de ordenacao                                */
/*                                                       */
/*-------------------------------------------------------*/
void mergeSort(int v[], int l, int r) {

    /*valor do indice do centro do vetor*/
    int mid;

    /* Caso base: 1 ou 0 elementos*/
    if (l>=r) {

        return;

    }

    /*1. Descobrir mid*/
    mid = (l+r)/2;

    /*Recursivamente ordenar as arrays resultantes: [l,mid] e [mid+1,r]*/

    mergeSort(v,l,mid);

    mergeSort(v,mid+1,r);

    /*Juntar as duas arrays*/
    merge(v,l,mid,r);

}
