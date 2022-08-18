#include <stdio.h>
#include <string.h>
#define IDP 10000
#define DESCRICAO 63
#define IDE 500


typedef struct produto{
    int idp;
    char descricao[DESCRICAO];
    int preco;
    int peso;
    int quantidade;
    }produto;
produto sistemap[IDP] = {0};
produto sistemae[IDE][IDP] = {0};
produto sistemap_organizado[IDP] = {0};
produto sistemap_organizado_aux[IDP] = {0};
produto vetor_produtos_encomenda[IDP] = {0};
produto vetor_produtos_encomenda_aux[IDP] = {0};


/*adiciona um novo produto ao sistemap (sistema de produtos)*/

void adiciona_produto(int i){
    scanf(" %[^:]:%d:%d:%d", sistemap[i].descricao, &sistemap[i].preco, &sistemap[i].peso, &sistemap[i].quantidade);
    sistemap[i].idp = i;
    }

/*adiciona stock(quantidade) a um produto existente no sistemap*/

void adiciona_stock(int idp){
    int quantidade, idp_dado;
    scanf(" %d:%d", &idp_dado, &quantidade);
    if (idp >= idp_dado){ /*como o idp e incrementado, o valor atual do idp corresponde ao do ultimo produto adicionado, 
logo se o idp for menor que o idp_dado, significa que este ultimo nao existe */
        sistemap[idp_dado].quantidade += quantidade;
    }
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_dado);
    }
}

/*remove stock a um produto existente*/

void remove_stock(int idp){
    int idp_dado, quantidade_dada;
    scanf(" %d:%d", &idp_dado, &quantidade_dada);
    if (idp >= idp_dado){
        if (sistemap[idp_dado].quantidade >= quantidade_dada){  
            sistemap[idp_dado].quantidade = sistemap[idp_dado].quantidade - quantidade_dada;
        }
        else{
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade_dada, idp_dado);
        }
    }
    else{
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_dado);
    }
}

/*altera o preco de um produto existente no sistemap*/

void altera_preco(int idp){
    int idp_dado, preco;
    scanf(" %d:%d", &idp_dado, &preco);
    if (idp >= idp_dado){
        sistemap[idp_dado].preco = preco;
    }
    else{
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_dado);
    }
}

/*adiciona um produto a uma encomenda. se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente*/

void adiciona_produto_a_encomenda(int idp, int ide){
    int ide_dado, idp_dado, quantidade_dada, i, peso_tot = 0;
    scanf(" %d:%d:%d", &ide_dado, &idp_dado, &quantidade_dada);
    if (ide >= ide_dado){ /*aplica-se o mesmo racicionio de verificacao do identificador efetuado nas anteriores funcoes e explicado na funcao adiciona_stock*/
        if (idp >= idp_dado){
            if (sistemap[idp_dado].quantidade >= quantidade_dada){
                peso_tot = peso_tot + quantidade_dada * sistemap[idp_dado].peso; /*se houver quantidade suficiente em stock, calcula-se o peso introduzido*/
                for (i = 0; i< IDP; i++){
                    peso_tot = peso_tot + ((sistemap[i].peso) * (sistemae[ide_dado][i].quantidade)); /*percorre a encomenda e vai atualizando o valor do seu peso*/                 
                }
                if  (peso_tot <= 200){
                    sistemae[ide_dado][idp_dado].quantidade += quantidade_dada; 
                    sistemap[idp_dado].quantidade = sistemap[idp_dado].quantidade - quantidade_dada;
                } /*se o valor final do peso (peso da encomenda mais o do produto adicionado) for menor ou igual a 200, adiciona-se a quantidade de produto
                 a encomenda e retira-se a mesma do stock*/
                else{
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_dado, ide_dado);
                }
            }
            else{
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_dado, ide_dado);
            }
        }
        else{
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_dado, ide_dado);
        }
    }
    else{
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_dado, ide_dado);
    }
}

/*remove um produto de uma encomenda*/

void remove_produto_da_encomenda(int ide, int idp){
    int ide_dado, idp_dado;
    scanf(" %d:%d", &ide_dado, &idp_dado);
    if (ide >= ide_dado){
        if (idp >= idp_dado){
            sistemap[idp_dado].quantidade = sistemap[idp_dado].quantidade + sistemae[ide_dado][idp_dado].quantidade;  
            sistemae[ide_dado][idp_dado].quantidade = 0;
        }/*trasnfere a quantidade de produto da encomenda para o sistema de produtos*/
        else{
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_dado, ide_dado);
        }
    }
    else{
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_dado, ide_dado);
    }
}

/*calcula o custo de uma encomenda*/

void custo_encomenda(int ide){
    int ide_dado, custo = 0, i ;
    scanf(" %d", &ide_dado);
    if (ide >= ide_dado){
        for (i =0 ; i < IDP; i++){  
            custo += (sistemap[i].preco * sistemae[ide_dado][i].quantidade); /*percorre a encomenda e atualiza o valor do seu preco*/
        } 
        printf("Custo da encomenda %d %d.\n", ide_dado, custo);
    }
    else{
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_dado);
    }
}

/*lista a descricao e quantidade de um produto numa encomenda*/

void lista_produto_de_encomenda(int ide, int idp){
    int ide_dado, idp_dado;
    scanf(" %d:%d", &ide_dado, &idp_dado);
    if (ide >= ide_dado){
        if (idp >= idp_dado){
            printf("%s %d.\n", sistemap[idp_dado].descricao, sistemae[ide_dado][idp_dado].quantidade );
        }
        else{
            printf("Impossivel listar produto %d. Produto inexistente.\n", idp_dado);
        }
    }
    else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_dado);
    }
}

/*lista o identificador da encomenda em que o produto dado ocorre mais vezes. 
se houver duas ou mais encomendas na mesma situacao, devera imprimir a encomenda de menor indice(ide)*/

void maior_produto(int idp){
    int idp_dado, maior = 0, i, ide_menor = 0;
    scanf(" %d", &idp_dado);
    if (idp >= idp_dado){
        for (i = 0; i<IDE; i++){
            if (sistemae[i][idp_dado].quantidade > maior){
                maior = sistemae[i][idp_dado].quantidade;
                ide_menor = i;
            } /*como o indice das encomendas vai incrementando, se existirem duas encomendas com a mesma quantidade de um produto, 
            a com ide menor sera sempre o output*/
        }
        if (maior != 0){
        printf("Maximo produto %d %d %d.\n", idp_dado, ide_menor, maior);
        }
    }
    else{
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_dado);
    }
}

/*funcoes auxiliares da ordena_produtos. permitem ordenar os precos existentes no sistemap*/

void merge_ordena_produtos(produto sistemap_organizado[], int left, int meio, int right){
    int i, j, k;
    for (i = meio + 1; i > left; i--){
        sistemap_organizado_aux[i-1] = sistemap_organizado[i-1];
    }
    for (j = meio; j < right ; j++){
        sistemap_organizado_aux[right + meio - j] = sistemap_organizado[j+1];
    }
    for(k = left; k <= right; k++){
        if (sistemap_organizado_aux[j].preco < sistemap_organizado_aux[i].preco){
            sistemap_organizado[k] = sistemap_organizado_aux[j--];
        }
        else if(sistemap_organizado_aux[j].preco > sistemap_organizado_aux[i].preco){
            sistemap_organizado[k] = sistemap_organizado_aux[i++];            
        }
        else{
            if (sistemap_organizado_aux[j].idp < sistemap_organizado_aux[i].idp){
                sistemap_organizado[k] = sistemap_organizado_aux[j--];
            }
            else{
                sistemap_organizado[k] = sistemap_organizado_aux[i++];
            }
        }
    }
}

void mergesort_ordena_produtos(produto sistemap_organizado[], int left, int right){
    int meio = (left+right) /2;;
    if(right <= left) return;
    mergesort_ordena_produtos(sistemap_organizado, left, meio);
    mergesort_ordena_produtos(sistemap_organizado, meio + 1, right);
    merge_ordena_produtos(sistemap_organizado, left, meio, right);
}

/*lista todos os produtos existentes no sistema por ordem crescente de preco.
 se houver 2 ou mais produtos com o mesmo preco, devera imprimir esses por ordem crescente de idp(identificador de produto)*/

void ordena_produtos(int idp){
    int i;
    for(i = 0; i<=idp; i++){
        sistemap_organizado[i] = sistemap[i];
    }
    mergesort_ordena_produtos(sistemap_organizado, 0, idp);
    printf("Produtos\n");
    for(i = 0; i<= idp; i++){
        printf("* %s %d %d\n",sistemap_organizado[i].descricao, sistemap_organizado[i].preco, sistemap_organizado[i].quantidade);
    }
}

/*funcoes auxliares de ordena_encomenda. 
permitem ordenar a encomenda por ordem alfabetica da descricao dos produtos*/

void merge_ordena_encomenda(produto vetor_produtos_encomenda[], int left, int m, int right){
    int i, j, k;
    for(i = m+1; i > left; i--)
        vetor_produtos_encomenda_aux[i - 1] = vetor_produtos_encomenda[i - 1];
    for(j = m; j < right; j++)
        vetor_produtos_encomenda_aux[right + m - j] = vetor_produtos_encomenda[j + 1];
    for(k = left; k <= right; k++)
        if(strcmp(vetor_produtos_encomenda_aux[j].descricao, vetor_produtos_encomenda_aux[i].descricao) < 0)
            vetor_produtos_encomenda[k] = vetor_produtos_encomenda_aux[j--];
        else
            vetor_produtos_encomenda[k] = vetor_produtos_encomenda_aux[i++];
}

void mergesort_ordena_encomenda(produto vetor_produtos_encomenda[], int left, int right){
    int m = (right + left) /2;
    if(right <= left) return;
    mergesort_ordena_encomenda(vetor_produtos_encomenda, left, m);
    mergesort_ordena_encomenda(vetor_produtos_encomenda, m + 1, right);
    merge_ordena_encomenda(vetor_produtos_encomenda, left, m, right);
}

/*lista todos os produtos de uma encomenda por ordem alfabetica de descricao*/

void ordena_encomenda(int ide, int idp){
    int ide_dado, i;
    scanf(" %d", &ide_dado);
    if (ide >= ide_dado){
        printf("Encomenda %d\n", ide_dado);
        for(i = 0; i <= idp; i++){
            vetor_produtos_encomenda[i] = sistemap[i];
        }
        mergesort_ordena_encomenda(vetor_produtos_encomenda, 0, idp);
        for(i = 0; i <= idp; i++){
            if (sistemae[ide_dado][vetor_produtos_encomenda[i].idp].quantidade != 0){
                printf("* %s %d %d\n", vetor_produtos_encomenda[i].descricao, vetor_produtos_encomenda[i].preco,sistemae[ide_dado][vetor_produtos_encomenda[i].idp].quantidade);
            }
        }        
    }    
    else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_dado);
    }
}
int main(){
    int car, idp = -1, i = 0, ide = -1, j = 0; /*idp- identificador de produto  ide- identificador de encomendas*/
    while ((car = getchar()) != 'x'){
        switch(car){
            case 'a':
                if (i < IDP){ /*cria produto caso o numero maximo de produtos permitidos ainda nao tiver sido atingido*/
                    adiciona_produto(i);
                    idp = i;
                    printf("Novo produto %d.\n", idp);
                    i++;
                    }
                break;
            case 'q':
                adiciona_stock(idp);
                break;
            case 'N':
                if (j < IDE){  /*cria encomenda se o numero maximo de encomendas ainda nao tiver sido atingido*/
                    ide = j;
                    printf("Nova encomenda %d.\n", ide); 
                    j++;
                    }               
                break;
            case 'r':
                remove_stock(idp);
                break;
            case 'p':
                altera_preco(idp);
                break;
            case 'A':
                adiciona_produto_a_encomenda(idp, ide);
                break;
            case 'R':
                remove_produto_da_encomenda(ide, idp);
                break;
            case 'C':
                custo_encomenda(ide);
                break;
            case 'E':
                lista_produto_de_encomenda(ide, idp);
                break;
            case 'm':
                maior_produto(idp);
                break;
            case 'l':
                ordena_produtos(idp);
                break;
            case 'L':
                ordena_encomenda(ide, idp);
                break;
            case'x':
                break;
        }   
    }
    return 0;
}


    


