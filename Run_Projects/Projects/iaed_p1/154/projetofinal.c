#include <stdio.h>
#include <string.h>



#define CARACTERES 64
#define IDENT 10000
#define NMR 200
#define TRUE 1
#define FALSE 0


typedef struct produtos{
    int idp;
    char descricao[CARACTERES]; 
    int preco;
    int peso;
    int qtd;
}produtos;


typedef struct encomenda_l{
    produtos l2_produtos[NMR];
    int peso;
    int ide;
    int n_produtos;
}encomenda_l;



void f_produto();
void listar_produtos();
void add_stock();
void add_encomenda();
void add_produto_enc();
void remove_stock();
void remove_produto();
void custo_encomenda();
void altera_preco();
void descricao_qtd();
void max_produto();
void listar_prod_encomenda();
void listar_preco();
void listar_preco_aux();
void comando_l();
void comando_L();
void insertion();


produtos produto[IDENT]; /*vetor com estrutura do produto*/
encomenda_l encomenda[500]; /*vetor com estrutura da encomenda*/


int idp = 0; /*conta o numero de produtos existentes no sistema*/ 
int ide = 0; /*conta o numero de encomendas existentes no sistema*/



int main(){

    char ch_main;

    while(ch_main != 'x'){

        switch((ch_main = getchar())){

            case 'a':
                f_produto();
                break;

            case 'k':
                listar_produtos();
                break;

            case 'q':
                add_stock();
                break;

            case 'N':
                add_encomenda();
                break;

            case 'A':
                add_produto_enc();
                break;

            case 'r':
                remove_stock();
                break;

            case 'R':
                remove_produto();
                break;

            case 'C':
                custo_encomenda();
                break;

            case 'p':
                altera_preco();
                break;

            case 'E':
                descricao_qtd();
                break;

            case 'm':
                max_produto();
                break;

            case 'K':
                listar_prod_encomenda();
                break;

            case 'l':
                comando_l();
                break;
            
            case 'L':
                comando_L();
                break;

            
        }
    }
    

    return 0;
}



/* a funcao adiciona um novo produto ao sitema*/
void f_produto(){

    scanf(" %[^:]:%d:%d:%d",produto[idp].descricao, &produto[idp].preco, &produto[idp].peso, &produto[idp].qtd);
    printf("Novo produto %d.\n", idp);
    produto[idp].idp = idp;
    idp++;
}


/*funcao auxiliar: lista todos os produtos existentes no sistema, com a descricao, o preco, o peso e a quantidade
de cada um*/
void listar_produtos(){

    int i;
    
    for (i = 0; i < idp; i++){
        printf("%s:%d:%d:%d\n",produto[i].descricao, produto[i].preco, produto[i].peso, produto[i].qtd);

    }
}


/* a funcao adiciona stock a um produto existente no sistema*/
void add_stock(){

    int id1, qtd;

    scanf("%d:%d",&id1,&qtd);

    if (id1 >= idp){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id1);
    }

    else{
        produto[id1].qtd += qtd;
    }
}


/* a funcao cria uma nova encomenda */
void add_encomenda(){

    printf("Nova encomenda %d.\n", ide);
    encomenda[ide].ide = ide;
    encomenda[ide].n_produtos = 0;
    encomenda[ide].peso = 0;
    ide++;

}


/* a funcao adiciona um produto a encomenda e, se ja existir esse produto, apenas adiciona a quantidade */
void add_produto_enc(){

    int d, id1, id2, qtd;
    int nmr, peso;
    int estado;
    estado = TRUE;
    

    scanf("%d:%d:%d",&id2,&id1,&qtd);

    
    if (id2 >= ide){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id1, id2);
        return;
    }

    if (id1 >= idp){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id1, id2);
        return;
    }

    if (qtd > produto[id1].qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id1, id2);
        return;
    }

    peso = encomenda[id2].peso + (produto[id1].peso * qtd);

    if (peso > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id1, id2);
        return;
    }


    nmr = encomenda[id2].n_produtos;

    for (d = 0; d < nmr ; d++){
        
        /* caso em que o produto ja existe na encomenda*/
        if (encomenda[id2].l2_produtos[d].idp == id1){
            encomenda[id2].peso += produto[id1].peso * qtd;
            encomenda[id2].l2_produtos[d].qtd += qtd;
            produto[id1].qtd -= qtd;
            estado = FALSE;
        }
    }

    /* caso em que o produto ainda nao exite na encomenda*/        
    if (estado == TRUE){
        strcpy(encomenda[id2].l2_produtos[nmr].descricao , produto[id1].descricao);
        encomenda[id2].peso += produto[id1].peso * qtd;
        encomenda[id2].l2_produtos[nmr].qtd = qtd;
        produto[id1].qtd -= qtd;
        encomenda[id2].n_produtos += 1;
        encomenda[id2].l2_produtos[nmr].idp = id1;
        encomenda[id2].l2_produtos[nmr].preco = produto[id1].preco;  
        estado = FALSE;
    
    }
}


/* a funcao remove stock a um produto existente */
void remove_stock(){

    int id1, qtd;
    

    scanf("%d:%d", &id1, &qtd);

    if (id1 >= idp){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id1);
        return;
    }

    if (qtd > produto[id1].qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id1);
        return;
    }
    else{
        produto[id1].qtd -= qtd;
    }
    
}


/* a funcao remove um produto de uma encomenda */
void remove_produto(){

    int id1, id2;
    int d;
    int nmr;

    scanf("%d:%d", &id2, &id1);

    if (id2 >= ide){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id1, id2);
        return;
    }

    if (id1 >= idp){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id1, id2);
        return;
    }

    
    nmr = encomenda[id2].n_produtos;

   
    for (d = 0; d < nmr ; d++){
        if (encomenda[id2].l2_produtos[d].idp == id1){
            /* quando so existe um produto ou quando e o ultimo produto da encomenda*/
            if (nmr == 1 || d == nmr - 1){
                produto[id1].qtd += encomenda[id2].l2_produtos[d].qtd;
                encomenda[id2].peso -= (encomenda[id2].l2_produtos[d].qtd * produto[id1].peso);
                strcpy(encomenda[id2].l2_produtos[d].descricao , ""); 
                encomenda[id2].l2_produtos[d].qtd = 0;
                encomenda[id2].l2_produtos[d].idp = -1;
                encomenda[id2].l2_produtos[d].preco = 0;
                encomenda[id2].l2_produtos[d].peso = 0;
                encomenda[id2].n_produtos -= 1;
                return;
            }

            else{
                
                produto[id1].qtd += encomenda[id2].l2_produtos[d].qtd; 
                encomenda[id2].peso -= (encomenda[id2].l2_produtos[d].qtd * produto[id1].peso);

                /*meter o ultimo produto da encomenda no lugar do produto que foi retirado da encomenda*/
                strcpy(encomenda[id2].l2_produtos[d].descricao , encomenda[id2].l2_produtos[nmr - 1].descricao); 
                encomenda[id2].l2_produtos[d].qtd = encomenda[id2].l2_produtos[nmr - 1].qtd;
                encomenda[id2].l2_produtos[d].idp = encomenda[id2].l2_produtos[nmr - 1].idp;
                encomenda[id2].l2_produtos[d].preco = encomenda[id2].l2_produtos[nmr - 1].preco;
                encomenda[id2].l2_produtos[d].peso = encomenda[id2].l2_produtos[nmr - 1].peso;

                encomenda[id2].n_produtos -= 1;
                return;
            }
        }
    }
}

    
    

    

/* a funcao calcula o custo de uma encomenda */
void custo_encomenda(){

    int id2;
    int d, nmr;
    int total = 0;

    scanf("%d", &id2);

    if (id2 >= ide){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id2);
        return;
    }

    
    else{
        nmr = encomenda[id2].n_produtos;

        for (d = 0; d < nmr ; d++){
            total += encomenda[id2].l2_produtos[d].preco * encomenda[id2].l2_produtos[d].qtd;
        }
        
        printf("Custo da encomenda %d %d.\n", id2, total);
    }


}


/* a funcao altera o preco de um produto existente no sistema */
void altera_preco(){

    int id1, preco;
    int i, d, nmr;

    scanf("%d:%d", &id1, &preco);

    if (id1 >= idp){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id1);
        return;
    }
    
    else{
        produto[id1].preco = preco;
        for (i = 0; i < ide; i++){
            nmr = encomenda[i].n_produtos;
            for (d = 0; d < nmr; d++){
                if (encomenda[i].l2_produtos[d].idp == id1){
                    encomenda[i].l2_produtos[d].preco = preco;
                }
            }
        }
    }

    
}


/* a funcao lista a descricao e quantidade existente de um produto numa encomenda*/
void descricao_qtd(){

    int id1, id2;
    int d, nmr, estado;
    estado = TRUE;

    scanf("%d:%d", &id2, &id1);

    if (id2 >= ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id2);
        return;
    }

    if (id1 >= idp){
        printf("Impossivel listar produto %d. Produto inexistente.\n", id1);
        return;
    }


    nmr = encomenda[id2].n_produtos;

    for (d = 0; d < nmr ; d++){
        if (encomenda[id2].l2_produtos[d].idp == id1){
            printf("%s %d.\n", encomenda[id2].l2_produtos[d].descricao, encomenda[id2].l2_produtos[d].qtd);
            estado = FALSE;
        }
    }

    /* quando o produto nao existe na encomenda*/
    if (estado == TRUE){    
        printf("%s 0.\n",produto[id1].descricao);
        return;
    }
}


/* a funcao lista o identificador da encomenda em que o produto dado ocorre mais vezes. 
se houver 2 ou mais encomendas nessa situa?ao, devolve a com menor ide */
void max_produto(){

    int id1, i, d, id2, estado;
    int nmr;
    int max = -1;
    estado = FALSE;


    scanf("%d", &id1);
    

    if (id1 >= idp){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id1);
        return;
    }

    for (i = 0; i < ide; i++){
        
        nmr = encomenda[i].n_produtos;
        
        for (d = 0; d < nmr; d++){
            if (encomenda[i].l2_produtos[d].idp == id1){
                if (encomenda[i].l2_produtos[d].qtd > max){
                    max = encomenda[i].l2_produtos[d].qtd;
                    id2 = i;
                    estado = TRUE;
                }
            }
        }
    }
    if (estado == TRUE) printf ("Maximo produto %d %d %d.\n", id1, id2, max);
}

/* funcao auxiliar: introduz-se o numero da encomenda e depois a funcao lista todos
os seus produtos com a sua respetiva quantidade*/ 
void listar_prod_encomenda(){

    int id2; /* numero encomenda*/
    int d, nmr;
    

    scanf("%d", &id2);

    nmr = encomenda[id2].n_produtos;
    
    for (d = 0; d < nmr; d++){
        printf("%s:%d\n", encomenda[id2].l2_produtos[d].descricao, encomenda[id2].l2_produtos[d].qtd); 
    }
}


/* merge sort que e usado na funcao comando_l*/
void listar_preco(int vetor[],int vetor2[], int left, int right){

    if (left < right){

        int m = left + (right - left)/2;

        listar_preco(vetor,vetor2, left, m);
        listar_preco(vetor,vetor2, m + 1, right);
        listar_preco_aux(vetor,vetor2, left, m, right);
    }   
}


/* funcao auxiliar do merge sort*/
void listar_preco_aux(int vetor[],int vetor2[], int left, int m, int right){

    int i, j, k;
    int n1 = m - left + 1;
    int n2 = right - m;

    int L[IDENT], L2[IDENT], R[IDENT], R2[IDENT];

    for (i = 0; i < n1; i++){
        L[i] = vetor[left + i];
        L2[i] = vetor2[left + i];
    }

    for (j = 0; j < n2; j++){
        R[j] = vetor[m + 1 + j];
        R2[j] = vetor2[m + 1 + j];
    }


    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            vetor[k] = L[i];
            vetor2[k] = L2[i];
            i++;
        }
        else{
            vetor[k] = R[j];
            vetor2[k] = R2[j];
            j++;
        }
        k++;
    }


    while (i < n1){
        vetor[k] = L[i];
        vetor2[k] = L2[i];
        i++;
        k++;
    }

    while (j < n2){
        vetor[k] = R[j];
        vetor2[k] = R2[j];
        j++;
        k++;
    }

}


/* a funcao lista todos os produtos existentes no sistema por ordem crescente de preco.
Se houver 2 ou mais produtos com o mesmo preco, imprime-os por ordem crescende de idp do produto.*/
void comando_l(){

    int i;
    int precos[IDENT];
    int idps[IDENT];
    
    

    for (i = 0; i < idp; i++){
        precos[i] = produto[i].preco;
        idps[i] = produto[i].idp;
    }

    
    listar_preco(precos,idps,0,idp-1);


    printf("Produtos\n");

    
    for (i = 0; i < idp; i++){
        printf("* %s %d %d\n", produto[idps[i]].descricao, produto[idps[i]].preco, produto[idps[i]].qtd);
    }
}


/* a funcao lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
void comando_L(){

    int id2, nmr;
    char nomes[NMR][CARACTERES];
    int indices[NMR];
    int i, n;

    scanf("%d", &id2);

    if (id2 >= ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id2);
        return;
    }

    nmr = encomenda[id2].n_produtos;

    for (i = 0; i < nmr; i++){
        strcpy(nomes[i] , encomenda[id2].l2_produtos[i].descricao);
        indices[i] = i;
        
    }

    insertion(nomes, indices, nmr);

    printf("Encomenda %d\n", id2);
    for (i = 0; i < nmr; i++){
        n = indices[i];
        printf("* %s %d %d\n", nomes[i], encomenda[id2].l2_produtos[n].preco, encomenda[id2].l2_produtos[n].qtd);
    }

}

/* insertion sort que e usado na funcao comando_L*/
void insertion(char vetor[][CARACTERES], int vetor1[], int n){

    int i, j, k1;
    char k[CARACTERES];
    

    for (i = 1; i < n; i++){
        strcpy(k , vetor[i]);
        k1 = vetor1[i];
        j = i - 1;

        while (j >= 0 && (strcmp(k, vetor[j]) < 0)){
            strcpy(vetor[j + 1] , vetor[j]);
            vetor1[j + 1] = vetor1[j];
            j = j - 1;
        }
        strcpy(vetor[j + 1], k);
        vetor1[j + 1] = k1;
    }
}