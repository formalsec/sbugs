#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 10000 /*Maximo de produtos no sistema*/
#define MAX_ENCOMENDAS 500 /*Maximo de encomendas no sistema*/
#define MAX_PESO 200 /*Maximo de peso por encomenda*/
#define MAX_DESCRICAO 63 /*Maximo de caracteres por descricao de produto*/

typedef struct produto{
    int idp; /*identificador de produto*/
    char descricao[MAX_DESCRICAO]; /*vetor de 63 caracteres para a descricao do produto*/
    int preco; /*preco do produto*/
    int peso; /*peso do produto*/
    int qtd; /*quantidade/stock existente do produto no sistema*/
}Produto;

typedef struct encomenda{
    int ide; /*identificador de encomenda*/
    int peso; /*peso da encomenda*/
    int cont_produtos; /*contader de produtos diferentes na encomenda*/
    Produto lista_p[MAX_PESO]; /*vetor correspondente a lista de produtos na encomenda*/
}Encomenda;

int cont_idp = 0; /*contador de produtos no sistema*/
int cont_ide = 0; /*contador de encomendas no sistema*/

Produto catalogo[MAX_PRODUTOS] = {0}; /*vetor onde serao adicionados todos os produtos adicionados ao sistema(catalogo)*/
Encomenda encomendas[MAX_ENCOMENDAS] = {0}; /*vetor onde serao adicionadas todas as encomendas criadas no sistema*/

#define menor_preco(A, B) (A <= B)
/*verifica se A aparece antes de B alfabeticamente*/
#define menor_alfabetica(A, B) (strcmp(A, B) < 0)
#define preco_igual(A, B) (A == B)
#define menor_id(A, B) (A < B)

Produto aux_preco[MAX_PRODUTOS]; /*vetor auxiliar para ordenar por preco*/
Produto aux_descricao[MAX_PESO]; /*vetor auxiliar para ordenar por descricao*/

/*
* Argumentos: vetor de produtos, limite a esquerda, meio e limite a direita.
*
* Descricao: auxilia a funcao merge_sort quando ordena por preco.
*
* Funcionamento: compara os vetores elemento a elemento e junta-os de forma ordenada.
*/
void merge_preco(Produto a[], int esquerda, int meio, int direita){
    int i,j,k;
    /*constroi a parte da esquerda do vetor auxiliar*/
    for (i = meio+1; i > esquerda; i--){
        aux_preco[i-1] = a[i-1];
    }
    /*constroi a parte da direita do vetor auxiliar*/
    for(j = meio; j < direita; j++){
        aux_preco[direita+meio-j] = a[j+1];
    }
    /*percorre o vetor a[] e vai-lhe inserindo elementos de forma ordenada a partir das pontas do auxiliar*/
    for (k = esquerda; k <= direita; k++){
        /*se o preco mais a direita for menor ou igual ao preco mais a esquerda*/
        if (menor_preco(aux_preco[j].preco, aux_preco[i].preco)){
            /*se os precos forem iguais e o identificador da esquerda for menor que o da direita*/
            if (preco_igual(aux_preco[j].preco, aux_preco[i].preco) && menor_id(aux_preco[i].idp, aux_preco[j].idp)){
                /*coloca no vetor principal o produto mais a esquerda e incrementa o i de seguida*/
                a[k] = aux_preco[i++];
                continue;
            }
            /*coloca no vetor principal o produto mais a direita e decrementa o j de seguida*/
            a[k] = aux_preco[j--];
        }
        else{
            /*coloca no vetor principal o produto mais a esquerda e incrementa o i de seguida*/
            a[k] = aux_preco[i++];
        }
    }
    return;
}

/*
* Argumentos: vetor de produtos, limite a esquerda, meio e limite a direita.
*
* Descricao: auxilia a funcao merge_sort quando ordena por descricao.
*
* Funcionamento: compara os vetores elemento a elemento e junta-os de forma ordenada.
*/
void merge_descricao(Produto a[], int esquerda, int meio, int direita){
    int i,j,k;
    /*constroi a parte da esquerda do vetor auxiliar*/
    for (i = meio+1; i > esquerda; i--){
        aux_descricao[i-1] = a[i-1];
    }
    /*constroi a parte da direita do vetor auxiliar*/
    for(j = meio; j < direita; j++){
        aux_descricao[direita+meio-j] = a[j+1];
    }
    /*percorre o vetor a[] e vai-lhe inserindo elementos de forma ordenada a partir das pontas do auxiliar*/
    for (k = esquerda; k <= direita; k++){
        /*se a descricao do produto mais a direita aparecer antes alfabeticamente em relacao a do produto mais a esquerda*/
        if (menor_alfabetica(aux_descricao[j].descricao, aux_descricao[i].descricao)){
            /*coloca no vetor principal o produto mais a direita e decrementa o j de seguida*/
            a[k] = aux_descricao[j--];
        }
        else{
            /*coloca no vetor principal o produto mais a esquerda e incrementa o i de seguida*/
            a[k] = aux_descricao[i++];
        }
    }
    return;
}

/*
* Argumentos: vetor de produtos, limite a esquerda e a direita, 
*             caracter que indica o criterio de ordenacao.
*
* Descricao: ordena uma lista de produtos atraves do algoritmo merge sort.
*
* Funcionamento: separa o vetor original em vetores com metade do tamanho 
*                e junta-os de forma ordenada recursivamente.
*/
void merge_sort(Produto a[], int esquerda, int direita, char funcao){
    /*calcula o meio do vetor a ordenar*/
    int meio = (direita + esquerda) / 2;
    if (direita <= esquerda){
        return;
    }
    /*faz o algoritmo para a metade da esquerda*/
    merge_sort(a, esquerda, meio, funcao);
    /*faz o algoritmo para a metade da direita*/
    merge_sort(a, meio+1, direita, funcao);
    /*se o argumento funcao for 'l', ordena por preco*/
    if (funcao == 'l'){
        merge_preco(a, esquerda, meio, direita);
    }
    /*se o argumento funcao for 'L', ordena por ordem alfabetica*/
    else if (funcao == 'L'){
        merge_descricao(a, esquerda, meio, direita);
    }
    return;
}

/*
* Comando: a
* Descricao: adiciona um novo produto ao sistema.
*/
void adiciona_produto(){
    Produto p;
    scanf(" %[^:]:%d:%d:%d", p.descricao, &p.preco, &p.peso, &p.qtd);
    /*o identificador do novo produto corresponde ao contador de produtos*/
    p.idp = cont_idp;
    /*guarda no vetor de produtos, o novo produto*/
    catalogo[cont_idp] = p;
    cont_idp++; 
    printf("Novo produto %d.\n", p.idp);
    return;
}

/*
* Comando: q
* Descricao: adiciona stock a um produto existente no sistema.
*/
void adiciona_stock(){
    int id_produto;
    int stock;
    scanf("%d:%d", &id_produto, &stock);
    if (id_produto < cont_idp){
        /*adicionar o stock fornecido ao stock existente correspondente a esse produto no sistema(catalogo)*/
        catalogo[id_produto].qtd += stock;
        return;
    }
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_produto);
    return;
}

/*
* Comando: N
* Descricao: cria uma nova encomenda.
*/
void nova_encomenda(){
    Encomenda e;
    /*o identificador da nova encomenda corresponde ao contador de encomendas*/
    e.ide = cont_ide;
    /*guarda a nova encomenda no vetor das encomendas*/
    encomendas[cont_ide] = e;
    cont_ide++;
    printf("Nova encomenda %d.\n", e.ide);
    return;
}

/*
* Comando: A
* Descricao: adiciona um produto a uma encomenda.
*/
void adiciona_produto_encomenda(){
    int id_encomenda;
    int id_produto;
    int quantidade;
    int i;
    /*flag que indica se o produto que queremos adicionar ja existia na encomenda*/
    int encontrou = 0;
    scanf("%d:%d:%d", &id_encomenda, &id_produto, &quantidade);
    if (id_encomenda >= cont_ide){;
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);
        return;
    }
    if (id_produto >= cont_idp){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
        return;
    }
    if (quantidade > catalogo[id_produto].qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_produto, id_encomenda);
        return;
    }
    /*adiciona ao peso da encomenda o peso do produto fornecido multiplicado pela quantidade indicada*/
    encomendas[id_encomenda].peso += catalogo[id_produto].peso * quantidade;
    if (encomendas[id_encomenda].peso > MAX_PESO){
        /*remove do peso da encomenda o valor adicionado previamente para fazer a verificacao e apresenta o erro*/
        encomendas[id_encomenda].peso -= catalogo[id_produto].peso * quantidade;
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_produto, id_encomenda);
        return;
    }
    /*percorre os produtos na encomenda*/
    for (i = 0; i < encomendas[id_encomenda].cont_produtos; i++){
        /*se o identificador do produto i da lista de produtos na encomenda for igual ao identificador do produto fornecido*/
        if(encomendas[id_encomenda].lista_p[i].idp == id_produto){
            /*ativa a flag que indica que o produto foi encontrado, pois ja la estava*/
            encontrou = 1;
            /*adiciona a quantidade indicada a quantidade do produto ja existente na encomenda e sai do ciclo*/
            encomendas[id_encomenda].lista_p[i].qtd += quantidade;
            /*retira a quantidade indicada ao stock do produto no sistema(catalogo)*/
            catalogo[id_produto].qtd -= quantidade;
            return;
        }
    }
    if (encontrou == 0){
        /*adiciona o produto a lista de produtos presentes na encomenda*/
        encomendas[id_encomenda].lista_p[encomendas[id_encomenda].cont_produtos] = catalogo[id_produto];
        /*coloca a sua quantidade dentro da encomenda a 0*/
        encomendas[id_encomenda].lista_p[encomendas[id_encomenda].cont_produtos].qtd = 0;
        encomendas[id_encomenda].lista_p[i].qtd += quantidade;
        /*incrementa o contador de produtos da encomenda*/
        encomendas[id_encomenda].cont_produtos++;
        catalogo[id_produto].qtd -= quantidade;
    }
    return;
}

/*
* Comando: r
* Descricao: remove stock a um produto existente.
*/
void remove_stock(){
    int id_produto;
    int quantidade;
    scanf("%d:%d", &id_produto, &quantidade);
    if (id_produto >= cont_idp){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_produto);
        return;
    }
    if (catalogo[id_produto].qtd < quantidade){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, id_produto);
        return;
    }
    /*retira a quantidade indicada ao stock do produto no sistema(catalogo)*/
    catalogo[id_produto].qtd -= quantidade;
    return;
}

/*
* Comando: R
* Descricao: remove um produto de uma encomenda.
*/
void remove_produto_encomenda(){
    int i;
    int id_produto;
    int id_encomenda;
    /*flag que indica que o produto foi encontrado*/
    int encontrou = 0;
    scanf("%d:%d", &id_encomenda, &id_produto);
    if (id_encomenda >= cont_ide){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);
        return;
    }
    if(id_produto >= cont_idp){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
        return;
    }
    for(i = 0; i < encomendas[id_encomenda].cont_produtos; i++){
        if (encomendas[id_encomenda].lista_p[i].idp == id_produto){
            /*adiciona a quantidade do produto presente na encomenda ao stock do produto no sistema(catalogo)*/
            catalogo[id_produto].qtd += encomendas[id_encomenda].lista_p[i].qtd;
            /*remove ao peso da encomenda o peso do produto indicado multiplicado pela quantidade que estava presente na encomenda*/
            encomendas[id_encomenda].peso -= (catalogo[id_produto].peso * encomendas[id_encomenda].lista_p[i].qtd);
            encontrou = 1;
        }
        if (encontrou == 1){
            /*"puxa" o produto seguinte para o seu lugar, acabando por elimina-lo. A cada iteracao acaba por "puxar" o produto seguinte para a devida posicao acertando a lista*/
            encomendas[id_encomenda].lista_p[i] = encomendas[id_encomenda].lista_p[i+1];
        }
    }
    if (encontrou == 1){
        /*decrementa o contador de produtos presentes na encomenda, pois um produto foi removido*/
        encomendas[id_encomenda].cont_produtos--;
    }
    return;
}

/*
* Comando: C
* Descricao: calcula o custo de uma encomenda.
*/
void custo_encomenda(){
    int id_encomenda;
    int i;
    int custo = 0;
    scanf("%d", &id_encomenda);
    if (id_encomenda >= cont_ide){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_encomenda);
        return;
    }
    for (i = 0; i < encomendas[id_encomenda].cont_produtos; i++){
        /*a cada iteracao adiciona ao custo o preco do produto multiplicado pela quantidade de produto presente na encomenda*/
        custo += encomendas[id_encomenda].lista_p[i].preco * encomendas[id_encomenda].lista_p[i].qtd;
    }
    printf("Custo da encomenda %d %d.\n", id_encomenda, custo);
    return;
}

/*
* Comando: p
* Descricao: altera o preco de um produto existente no sistema.
*/
void altera_preco(){
    int id_produto;
    int novo_preco;
    int i, j;
    scanf("%d:%d", &id_produto, &novo_preco);
    if (id_produto >= cont_idp){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_produto);
        return;
    }
    /*altera para o novo preco*/
    catalogo[id_produto].preco = novo_preco;
    /*percorre as encomendas*/
    for (i = 0; i < cont_ide; i++){
        /*percorre os produtos da encomenda*/
        for (j = 0; j < encomendas[i].cont_produtos; j++){
            if (encomendas[i].lista_p[j].idp == id_produto){
                /*altera para o novo preco*/
                encomendas[i].lista_p[j].preco = novo_preco;
                break;
            }
        }
    }
    return;
}

/*
* Comando: E
* Descricao: retorna a descricao e a quantidade de um produto numa dada encomenda.
*/
void lista_descricao_qtd(){
    int id_produto;
    int id_encomenda;
    int i;
    scanf("%d:%d", &id_encomenda, &id_produto);
    if (id_encomenda >= cont_ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_encomenda);
        return;
    }
    if (id_produto >= cont_idp){
        printf("Impossivel listar produto %d. Produto inexistente.\n", id_produto);
        return;
    }
    /*percorre os produtos da encomenda*/
    for (i = 0; i < encomendas[id_encomenda].cont_produtos; i++){
        if (encomendas[id_encomenda].lista_p[i].idp == id_produto){
            printf("%s %d.\n", encomendas[id_encomenda].lista_p[i].descricao, encomendas[id_encomenda].lista_p[i].qtd);
            return;
        }
    }
    /*se nao encontrou o produto a sua quantidade e 0*/
    printf("%s 0.\n", catalogo[id_produto].descricao);
    return;
}

/*
* Comando: m
* Descricao: retorna o identificador da encomenda em que um dado produto ocorre mais vezes.
*/
void encomenda_mais_produto(){
    int id_produto;
    int i, j;
    int maior_qtd = 0;
    int encontrou = 0;
    int id_encomenda;
    scanf("%d", &id_produto);
    if (id_produto >= cont_idp){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_produto);
        return;
    }
    /*percorre as encomendas*/
    for (i = 0; i < cont_ide; i++){
        /*percorre os produtos da encomenda*/
        for (j = 0; j < encomendas[i].cont_produtos; j++){
            /*se o identificador do produto j da lista de produtos na encomenda i for igual ao identificador do produto fornecido e a sua quantidade for maior que a maior quantidade atual*/
            if ((encomendas[i].lista_p[j].idp == id_produto) && (encomendas[i].lista_p[j].qtd > maior_qtd)){
                maior_qtd = encomendas[i].lista_p[j].qtd;
                id_encomenda = i;
                encontrou = 1;
            }
        }
    }
    if (encontrou == 1){
        printf("Maximo produto %d %d %d.\n", id_produto, id_encomenda, maior_qtd);
    }
    return;
}

/*
* Comando: l
* Descricao: lista todos os produtos existentes no sistema por ordem crescente de preco.
*/
void lista_por_preco(){
    int i;
    /*lista temporaria de produtos*/
    Produto lista[MAX_PRODUTOS];
    /*copia para a lista temporaria todos os produtos presentes no sistema(catalogo)*/
    for (i = 0; i < cont_idp; i++){
        lista[i] = catalogo[i];
    }
    /*ordena a copia da lista por preco*/
    merge_sort(lista, 0, cont_idp - 1, 'l');
    printf("Produtos\n");
    /*percorre a lista temporaria ja ordenada e apresenta os produtos*/
    for (i = 0; i < cont_idp; i++){
        printf("* %s %d %d\n", lista[i].descricao, lista[i].preco, lista[i].qtd);
    }
    return;
}

/*
* Comando: L
* Descricao: lista todos os produtos de uma encomenda por ordem alfabetica da descricao.
*/
void lista_alfabeticamente(){
    int id_encomenda;
    int i;
    scanf("%d", &id_encomenda);
    if (id_encomenda >= cont_ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_encomenda);
        return;
    }
    /*ordena os produtos da encomenda alfabeticamente*/
    merge_sort(encomendas[id_encomenda].lista_p, 0, encomendas[id_encomenda].cont_produtos - 1, 'L');
    printf("Encomenda %d\n", id_encomenda);
    /*percorre a lista de produtos de encomenda ja ordenada e apresenta os produtos*/
    for (i = 0; i < encomendas[id_encomenda].cont_produtos; i++){
        printf("* %s %d %d\n", encomendas[id_encomenda].lista_p[i].descricao, encomendas[id_encomenda].lista_p[i].preco, encomendas[id_encomenda].lista_p[i].qtd);
    }
    return;
}

/*vai lendo os camandos ate terminar o programa*/
int main(){
    char c;
    /*enquanto o program nao ler o caracter 'x', vai lendo caracteres*/
    while ((c = getchar()) != 'x'){
        /*consoante o caracter lido, o programa chama a funcao correspondente a esse comando e depois passa ao comando seguinte*/
        switch(c){
            case 'a':
                adiciona_produto();
                break;
            case 'q':
                adiciona_stock();
                break;
            case 'N':
                nova_encomenda();
                break;
            case 'A':
                adiciona_produto_encomenda();
                break;
            case 'r':
                remove_stock();
                break;
            case 'R':
                remove_produto_encomenda();
                break;
            case 'C':
                custo_encomenda();
                break;
            case 'p':
                altera_preco();
                break;
            case 'E':
                lista_descricao_qtd();
                break;
            case 'm':
                encomenda_mais_produto();
                break;
            case 'l':
                lista_por_preco();
                break;
            case 'L':
                lista_alfabeticamente();
                break;
            default:
                break;
        }
    }
    return 0;
}