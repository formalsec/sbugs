#include <stdio.h>
#include <string.h>

/* numero maximo de produtos que podem existir no sistema */
#define MAX_produtos 10000 
/* numero maximo de caracteres que uma descricao pode ter */
#define MAX_str 63 
/* numero maximo de encomendas que podem existir no sistema */
#define MAX_encomendas 500 
/* numero maximo de produtos que podem existir numa encomenda (peso maximo de 200 por encomenda; peso minimo de um produto eh 1 ) */
#define MAX_produtos_por_encomenda 200 

/* conta o numero de produtos existentes */
int cont_produto = 0; 
/* conta o numero de encomendas existentes */
int cont_encomenda = 0; 
/* conta o numero de produtos dentro de uma encomenda */ 
int cont_produtos_encomenda[MAX_produtos_por_encomenda]; 

/* estrutura que define um produto. a cada produto eh associado uma descricao, preco, peso e quantidade, fornecidos pelo utiliador, 
   e um identificador, retornado pelo sistema */
typedef struct produto{ 
    int idp;
    char desc[MAX_str];
    int preco;
    int peso;
    int qtd;
} Produto;

/* guarda os produtos por ordem de introducao */
Produto produto[MAX_produtos]; 
/* guarda os produtos ordenados por ordem cresente de preco */
Produto l_p_ordenados[MAX_produtos]; 
/* guarda encomendas e os respetivos produtos */
Produto encomenda[MAX_encomendas][MAX_produtos]; 


/* Recebe como argumento um inteiro idp correspondente a um produto e altera o preco 
   desse produto na lista 'p_l_produtos' de maneira a que seja igual ao preco da lista 'produto' */
void copiaQuantidade(int idp){

    int i;

    for (i=0;i<cont_produto;i++){
        if (idp == l_p_ordenados[i].idp){
            l_p_ordenados[i].qtd = produto[idp].qtd;
            break;
        } 
    }      
}


/* Recebe um inteiro ide correspondente a uma encomenda e retorna o peso total dos produtos dessa encomenda */
int pesoEncomenda(int ide){
     
    int i,peso;

    peso = 0;

    for (i=0;i<cont_produtos_encomenda[ide];i++){
        peso += encomenda[ide][i].peso*encomenda[ide][i].qtd;
    }

    return peso;
}    


/* Recebe um n correspondente aa posicao de um produto na lista 'l_p_ordenados'. 
   Assume-se que este produto eh o unico elemente desordenado da lista e que todos os produtos ah sua direita teem precos iguais ou maiores.
   Ordena os produtos por ordem crescente de preco */ 
void ordenaProdutosVetorDecrescente(int n){

    int i;
    Produto aux;

    for (i=n;i>0;i--){                              /* caso dois produtos tenham mesmo preco, ordena por ordem crescente de idp */
        if (l_p_ordenados[i-1].preco > l_p_ordenados[i].preco || (l_p_ordenados[i].preco == l_p_ordenados[i-1].preco && l_p_ordenados[i].idp < l_p_ordenados[i-1].idp)){
            aux = l_p_ordenados[i-1];
            l_p_ordenados[i-1] = l_p_ordenados[i];
            l_p_ordenados[i] = aux;
        } 
        else{
            break;
        }
    }
}


/* Recebe um n correspondente aa posicao de um produto na lista 'l_p_ordenados. 
   Assume-se que este produto eh o unico elemente desordenado da lista e que todos os produtos ah sua esquerda teem precos iguais ou menores.
   Ordena os produtos por ordem crescente de preco */ 
void ordenaProdutosVetorCrescente(int n){

    int i;
    Produto aux;

    for (i=n;i<cont_produto-1;i++){                              /* caso dois produtos tenham mesmo preco, ordena por ordem crescente de idp */
        if (l_p_ordenados[i].preco > l_p_ordenados[i+1].preco || (l_p_ordenados[i].preco == l_p_ordenados[i+1].preco && l_p_ordenados[i].idp > l_p_ordenados[i+1].idp)){
            aux = l_p_ordenados[i];
            l_p_ordenados[i] = l_p_ordenados[i+1];
            l_p_ordenados[i+1] = aux;
        } 
        else{
            break;
        }
    }
}


/* Recebe um inteiro ide e ordena a encomenda correspondente a esse ide por ordem alfabetica crescente de descricao.
   Assume-se que existe no maximo um elemento nao ordenado */
void ordenaEncomenda(int ide){

    int i;
    Produto aux;

    for (i=cont_produtos_encomenda[ide];i>0;i--){                              
        if (strcmp(encomenda[ide][i].desc, encomenda[ide][i-1].desc) < 0){
            aux = encomenda[ide][i];
            encomenda[ide][i] = encomenda[ide][i-1];
            encomenda[ide][i-1] = aux;
        }       
        else{
            break;
        }
    }
}


/* Adiciona um novo prodto ao sistema */
void a_criaProduto(){ 
    
    Produto p;

    scanf(" %[^:]:%d:%d:%d",p.desc,&p.preco,&p.peso,&p.qtd);

    p.idp = cont_produto;
    l_p_ordenados[cont_produto] = p;
    produto[cont_produto] = p;

    printf("Novo produto %d.\n", cont_produto);

    ordenaProdutosVetorDecrescente(cont_produto); /* a lista 'l_p_ordenados' eh ordenada sempre que se introduz um novo produto */
    cont_produto++;

}


/* Adiciona stock a um produto existente no sistema */
void q_adicionaProduto(){

    int idp,qtd;

    scanf(" %d:%d",&idp,&qtd);
    
    if (idp >= cont_produto){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
    }
    else{
        produto[idp].qtd += qtd;
        copiaQuantidade(idp);
    }
}


/* Cria uma nova encomenda */
void N_criaEncomenda(){

    printf("Nova encomenda %d.\n",cont_encomenda);
    
    cont_produtos_encomenda[cont_encomenda] = 0;   
    cont_encomenda++;
}


/* Adiciona um produto a uma encomenda. 
   Se o produto ja existir na encomenda, adiciona a nova quantidade aa quantidade existente */
void A_adicionaProdutoEncomenda(){

    int ide,idp,qtd,existe,i;

    scanf(" %d:%d:%d",&ide,&idp,&qtd);

    if (ide >= cont_encomenda){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    }
    else if (idp >= cont_produto){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    }
    else if (produto[idp].qtd < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
    }
    else if (qtd*produto[idp].peso + pesoEncomenda(ide) > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
    }
    else{
        existe = 0;

        for (i=0;i<cont_produtos_encomenda[ide];i++){ /* verifica se o produto ja existe na encomenda */
            if (encomenda[ide][i].idp == produto[idp].idp){   
                encomenda[ide][i].qtd += qtd;
                existe = 1;   
                break;
            }
        }
        
        if (existe == 0){ /* adiciona o produto aa encomenda caso nao exista*/
            encomenda[ide][cont_produtos_encomenda[ide]] = produto[idp]; 
            encomenda[ide][cont_produtos_encomenda[ide]].qtd = qtd;

            ordenaEncomenda(ide); /* a encomenda eh ordenada por ordem afabetica sempre que se adiciona um novo produto */
            cont_produtos_encomenda[ide]++;
        }

        produto[idp].qtd -= qtd; /* retira stock aa lista 'produtos', corresponde aa que foi adicionada aa encomenda */
        copiaQuantidade(idp);
    }
}


/* Remove stock a um produto existente */
void r_removeStock(){

    int idp,qtd;

    scanf(" %d:%d",&idp,&qtd);
    
    if (idp >= cont_produto){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
    }
    else if (qtd > produto[idp].qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
    }
    else{
        produto[idp].qtd -= qtd;
        copiaQuantidade(idp);    
    }
}


/* Remove um produto de uma encomenda */
void R_removeProdutoEncomenda(){

    int i,ide,idp,remove,n;

    scanf(" %d:%d",&ide,&idp);

    if (ide >= cont_encomenda){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    }
    else if (idp >= cont_produto){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    }
    else{
        remove = 0;
        n = cont_produtos_encomenda[ide];

        for (i=0;i<cont_produtos_encomenda[ide];i++){
            if (encomenda[ide][i].idp == idp){
                produto[idp].qtd += encomenda[ide][i].qtd; /* adiciona a quantidade removida ao stock */
                copiaQuantidade(idp);

                cont_produtos_encomenda[ide]--; 
                n--;
                remove = 1;
            }
            if (remove == 1){ /* depois de encontar o produto que se pretende remover, mover todos os produtos seguintes um vetor para atras */
                encomenda[ide][i] = encomenda[ide][i+1];
            }
        }      
    }
}


/* Calcula o custo de uma encomenda */
void C_calculaCustoEncomenda(){

    int ide,i,custo = 0;

    scanf(" %d",&ide);

    if (ide >= cont_encomenda){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    }
    else{
        for (i=0;i<cont_produtos_encomenda[ide];i++){
            custo += encomenda[ide][i].preco * encomenda[ide][i].qtd;
        }
        printf("Custo da encomenda %d %d.\n",ide,custo);
    }
}


/* Altera o preco de um produto existente no sistema */
void p_alteraPrecoProduto(){

    int idp,preco,i,j,maior;

    scanf(" %d:%d",&idp,&preco);

    if (idp >= cont_produto){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    }
    else{
        /* ve se o novo valor do preco eh menor ou maior que o antigo, para fazer uma ordenacao mais eficiente da lista 'l_p_ordenados' */
        if (preco > produto[idp].preco){ 
            maior = 1;
        }

        if (preco < produto[idp].preco){
            maior = 0;
        }

        produto[idp].preco = preco; 
        
        for (i=0;i<cont_produto;i++){ /* altera o preco do produto na lista 'produto' */
            if (idp == l_p_ordenados[i].idp){
                l_p_ordenados[i].preco = preco; 
                break;
            }
        }

        if (maior == 1){ /* altera o preco do produto na lista 'l_p_ordenados' */
            ordenaProdutosVetorCrescente(i);
        }
        else{
            ordenaProdutosVetorDecrescente(i);
        }

        for (i=0;i<cont_encomenda;i++){ /* altera o preco do produto nas encomendas */
            for (j=0;j<cont_produtos_encomenda[i];j++){
                if (encomenda[i][j].idp == idp){
                    encomenda[i][j].preco = preco;
                    break;
                }
            }
        }
    } 
}


/* Lista a descricao e a quantidade de um produto numa encomenda */
void E_listaUmProdutoEncomenda(){

    int ide,idp,i,existe;

    scanf(" %d:%d",&ide,&idp);
    
    if (ide >= cont_encomenda){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    }
    else if (idp >= cont_produto){
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
    }
    else{
        existe = 0;

        for (i=0;i<cont_produtos_encomenda[ide];i++){
            if (encomenda[ide][i].idp == idp){
                printf("%s %d.\n",encomenda[ide][i].desc,encomenda[ide][i].qtd);

                existe = 1;
                break;
            }
        }

        if (existe == 0){ /* da o valor de 0 aa quantidade caso o produto nao exista na ecomenda*/
            printf("%s 0.\n",produto[idp].desc);
        }
    }
}


/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes */
void m_listaEncomendaMaisVezesProduto(){

    int i,j,idp,maior_ide,maior_qtd,existe;

    scanf(" %d",&idp);

    if (idp >= cont_produto){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    }
    else{
        existe = maior_ide = maior_qtd = 0;
       
        for (i=0;i<cont_encomenda;i++){ 
            for (j=0;j<cont_produtos_encomenda[i];j++){
                if (encomenda[i][j].idp == idp){
                    existe = 1;

                    if (encomenda[i][j].qtd > maior_qtd){
                        maior_ide = i;
                        maior_qtd = encomenda[i][j].qtd;
                    }

                    break;
                }
            }
        }  
        /* nao ha output caso nao exista nenhuma encomenda com o produto */
        if (existe == 1){
            printf("Maximo produto %d %d %d.\n",idp,maior_ide,maior_qtd);
        }
    }
}


/* Lista todos os produtos existentes no sistema por ordem crescente de preCo */
void l_listaTodosProdutosPorPreco(){
    
    int i;

    printf("Produtos\n");

    /* a lista 'l_p_ordenados' ja esta ordenada por ordem crescente de preco */
    for (i=0;i<cont_produto;i++){
        printf("* %s %d %d\n",l_p_ordenados[i].desc,l_p_ordenados[i].preco,l_p_ordenados[i].qtd);
    }
}


/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
void L_listaProdutosEncomendaPorOrdemAlfabetica(){
    
    int i,ide;

    scanf(" %d",&ide);

    if (ide >= cont_encomenda){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    }
    else{
        printf("Encomenda %d\n",ide);

        /* os produtos no vetor 'encomenda' ja se encontram ordenados por ordem alfabetica crescente de descricao */
        for (i=0;i<cont_produtos_encomenda[ide];i++){
            printf("* %s %d %d\n",encomenda[ide][i].desc,encomenda[ide][i].preco,encomenda[ide][i].qtd);
        }
    }

}


int main(){

    int c,i;
    
    for (i=0;(c = getchar()) != 'x';i++){ /* programa acaba quando eh detetado como imput o caracter 'x' */
        
        /* deteta o comando inserido pelo utilizador */
        if (c == 'a'){
            a_criaProduto();
        }
        else if (c == 'q'){
            q_adicionaProduto();
        }
        else if (c == 'N'){
            N_criaEncomenda();
        }
        else if (c == 'A'){
            A_adicionaProdutoEncomenda();
        }
        else if (c == 'r'){
            r_removeStock();
        }
        else if (c == 'R'){
            R_removeProdutoEncomenda();
        }
        else if (c == 'C'){
            C_calculaCustoEncomenda();
        }
        else if (c == 'p'){
            p_alteraPrecoProduto();
        }
        else if (c == 'E'){
            E_listaUmProdutoEncomenda();
        }
        else if (c == 'm'){
            m_listaEncomendaMaisVezesProduto();
        }
        else if (c == 'l'){
            l_listaTodosProdutosPorPreco();
        }
        else if (c == 'L'){
            L_listaProdutosEncomendaPorOrdemAlfabetica();
        }
    }    

    return 0;
}