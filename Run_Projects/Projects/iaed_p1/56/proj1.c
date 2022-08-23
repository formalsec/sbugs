#include <stdio.h>
#include <string.h>

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define MAXDESC 64     /*Comprimento maximo de uma descricao*/
#define MAXPROD 10000  /*Maximo de produtos*/
#define MAXENC 500     /*Maximo de encomendas*/
#define MAXPESO 200    /*Peso maximo de uma encomenda (consequentemente 
                         maximo de produtos por encomenda)*/

/*------Estruturas------*/

typedef struct{
    /* Definicao da estrutura Produto*/
    int identificador;          /*Numero identificador da encomenda*/
    char descricao[MAXDESC];
    int preco ;
    int peso ;
    int stock;

}Produto;

typedef struct{
    /* Definicao da estrutura Encomenda*/
    int identificador;          /*Numero identificador da encomenda*/
    Produto produtos[MAXPESO];  /*Lista de produtos na encomenda*/
    int numProd;                /*Numero identificador do ultimo produto adicionado a encomenda*/
    int pesoTotal ;

}Encomenda;

/*------Variaveis Globais------*/

Produto produtos[MAXPROD];      /*Lista de produtos no sistema.
                                (Esta lista estar? sempre ordenada 
                                por ordem de identificadores)*/

Encomenda encomendas[MAXENC];   /*Lista de encomendas no sistema.
                                (Esta lista estar? sempre ordenada 
                                por ordem de identificadores)*/

int idp = -1;                   /*Numero identificador do ultimo produto adicionado*/
int ide = -1;                   /*Numero identificador do ultima encomenda adicionada ao sistema*/
/*------Funcoes------*/

void CopyProd(Produto *colar, Produto copiar){
    /*Funcao copia um certo produto para outra variavel 
      do tipo "Produto" atribuindo-lhe os valores da copia*/
    colar->identificador = copiar.identificador;
    strcpy(colar->descricao,copiar.descricao);
    colar->preco = copiar.preco;
    colar->peso = copiar.peso;
    colar->stock = copiar.stock;

}

void Merge(int a[MAXPROD], int ids[MAXPROD], int l, int m, int r){
    /*Funcao recebe duas metades de uma lista ja 
      previamente ordenadas e une-as numa so lista
      em ordem crescente e aplica as mesmas trocas 
      de elementos a lista "ids" de maneira a guardar 
      a ordem correta dos valores*/
    int i , j, k;
    int aux[MAXPROD];
    int auxid[MAXPROD];
    
    /*Construcao das listas auxiliares*/
    for (i = m+1; i > l; i--){ 
        aux[i-1] = a[i-1];
        auxid[i-1] = ids[i-1];
    }
    for (j = m; j < r; j++){
        aux[r+m-j] = a[j+1];
        auxid[r+m-j] = ids[j+1];
    }

    /*Uneao das listas escolhendo o elemento de menor valor*/
    for (k = l; k <= r; k++){        
        if (less(aux[j], aux[i]) || i > m){        
            a[k] = aux[j--];
            ids[k] = auxid[j+1];
        }
        else{
            a[k] = aux[i++];
            ids[k] = auxid[i-1];
            }
    }
}

void MergeSort(int a[MAXPROD], int ids[MAXPROD], int left, int right){
    /*Funcao implementa o MergeSort ordenando os valores 
      da lista "a" fazendo os mesmos movimentos na lista
      "ids" que guarda as posi?oes de cada objeto*/

    int m = (right+left)/2;

    if (right <= left)
    return;

    MergeSort(a, ids, left, m);
    MergeSort(a, ids, m+1, right);
    Merge(a, ids, left, m, right);

}

void MergeStrings(char strings[MAXPESO][MAXDESC], int ordemStr[MAXPESO], int l, int m, int r){
    /*Funcao recebe duas metades de uma tabela de strings
      ja previamente ordenadas e une-as numa so tabela
      alfabeticamente*/

    int i , j, k;
    char aux[MAXPESO][MAXDESC];
    int auxOrd[MAXPESO];

    /*Construcao das listas auxiliares*/
    for (i = m+1; i > l; i--){     
        strcpy(aux[i-1], strings[i-1]);
        auxOrd[i-1] = ordemStr[i-1];
    }
    for (j = m; j < r; j++){
        strcpy(aux[r+m-j], strings[j+1]);
        auxOrd[r+m-j] = ordemStr[j+1];
    }
    
    /*Uneao das listas escolhendo a primeira descricao alfabeticamente*/
    for (k = l; k <= r; k++){            
        if (strcmp(aux[j],aux[i]) < 0){  
            strcpy(strings[k], aux[j--]);
            ordemStr[k] = auxOrd[j+1];
        }
        else{
            strcpy(strings[k], aux[i++]);
            ordemStr[k] = auxOrd[i-1];
        }
    }

}

void MergeSortString(char strings[MAXPESO][MAXDESC], int ordemStr[MAXPESO], int left, int right){
    /*Funcao implementa o MergeSort ordenando por 
      ordem alfabetica a tabela de strings 'strings'
      fazendo os mesmos movimentos na lista 'ordemStr'
      que guarda as posi?oes das strings*/

    int m = (right+left)/2;

    if (right <= left)
    return;

    MergeSortString(strings, ordemStr, left, m);
    MergeSortString(strings, ordemStr, m+1, right);
    MergeStrings(strings, ordemStr, left, m, right);
}

void NovoProduto(){
    /*Funcao adiciona um novo produto ao sistema*/
    int i = 0;
    char c;
    
    /*avancar o identificador*/
    idp++;
    getchar();                  /*espaco*/

    /*Define a descricao do produto*(mais rapido que scanf("%[^:]:%d:%d:%d",...)*/
    c = getchar();
    while (c != ':'){
        produtos[idp].descricao[i] = c;
        i++;
        c = getchar();
    }

    /*Atribui os valores do produto*/
    scanf("%d:%d:%d", &produtos[idp].preco, &produtos[idp].peso, &produtos[idp].stock);
    produtos[idp].identificador = idp;

    printf("Novo produto %d.\n", idp);

}

void AddStock(){
    /*Funcao adiciona stock a um produto existente no sistema*/
    int prod, qnt;
    scanf("%d:%d", &prod, &qnt);

    /*Condicao de erro*/
    if (prod <= idp && prod >= 0)     
        produtos[prod].stock += qnt;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prod);

}

void NovaEncomenda(){
    /*Funcao adiciona uma nova encomenda ao sistema*/
    
    /*avancar o identificador*/
    ide++;                      

    encomendas[ide].identificador = ide;
    encomendas[ide].numProd = -1;
    encomendas[ide].pesoTotal = 0;

    printf("Nova encomenda %d.\n", ide);
}

void AddProduto(){
    /*Funcao adiciona um produto a uma encomenda existente no sistema*/
    int i, qnt, n, enc, prod;
    scanf("%d:%d:%d", &enc, &prod, &qnt);
    /*condicoes de erro*/
    if (enc > ide || enc < 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
        return;
    }
    else if (prod > idp || prod < 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
        return;
    }
    else if (qnt > produtos[prod].stock){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod, enc);
        return;
    }
    else if (encomendas[enc].pesoTotal + qnt * produtos[prod].peso > MAXPESO){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod, enc);  
        return;
    }
    /*Verifica se ja existe este produto na encomenda*/
    n = encomendas[enc].numProd;
    for (i=0; i <= n ; i++){  
        if (prod == encomendas[enc].produtos[i].identificador){
            encomendas[enc].pesoTotal += produtos[prod].peso*qnt;
            encomendas[enc].produtos[i].stock += qnt;
            produtos[prod].stock -= qnt;
            return;
        }
    }
    /*Caso nao la esteja acrescenta-o*/
    encomendas[enc].numProd++; 
    n++;
    encomendas[enc].pesoTotal += produtos[prod].peso*qnt;
    encomendas[enc].produtos[n].identificador = prod;
    encomendas[enc].produtos[n].preco = produtos[prod].preco;
    encomendas[enc].produtos[n].peso = produtos[prod].peso;
    encomendas[enc].produtos[n].stock = qnt;
    produtos[prod].stock -= qnt;
    strcpy(encomendas[enc].produtos[n].descricao, produtos[prod].descricao);
}

void RemStock(){
    /*Funcao remove stock a um produto existente no sistema*/
    int prod, qnt;
    scanf("%d:%d", &prod, &qnt);
    
    /*Condicoes de erro*/
    if (prod <= idp && prod >= 0){
        if (produtos[prod].stock >= qnt) 
            produtos[prod].stock -= qnt;
        else
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qnt, prod);
    }
    else
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod);
}

void RemProdEnc(){
    /*Funcao remove um produto a uma encomenda existente no sistema*/
    int enc, prod, i, n;
    scanf("%d:%d", &enc, &prod);

    if (enc > ide || enc < 0){  /*Condicoes de erro*/
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod, enc);
        return;
    }
    else if (prod > idp || prod < 0){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod, enc);
        return;
    }
    
    n = encomendas[enc].numProd;
    /*Percorre a encomenda e caso esta tenha o produto, remove-o*/
    for (i=0; i <= n ; i++){                
        if (prod == encomendas[enc].produtos[i].identificador){
            produtos[prod].stock += encomendas[enc].produtos[i].stock;
            encomendas[enc].pesoTotal -= encomendas[enc].produtos[i].stock * encomendas[enc].produtos[i].peso;    
            for (; i<= n ; i++)   /*Ao remover um produto avanca todos os restantes que foram adicionados depois dele*/
                CopyProd(&encomendas[enc].produtos[i],encomendas[enc].produtos[i+1]);
            encomendas[enc].numProd--;
            return;
        }
    }
    
}

void CalcPreco(){
    /*Funcao calcula o preco de uma encomenda existente no sistema*/
    int enc, soma = 0, i;
    scanf("%d", &enc);
    if (enc > ide || enc < 0){ /*condicao de erro*/
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", enc);
        return;
    }
    for (i=0; i<=encomendas[enc].numProd; i++) /*percorre a encomenda somando os custos*/
        soma += encomendas[enc].produtos[i].preco * encomendas[enc].produtos[i].stock;
    printf("Custo da encomenda %d %d.\n",enc, soma);
}

void AltPreco(){
    /*Funcao altera o preco de um produto existente no sistema*/
    int prod, novoPreco, i, e;
    scanf("%d:%d", &prod, &novoPreco);
    if (prod > idp || prod < 0){  /*condicao de erro*/
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prod);
        return;
    }

    produtos[prod].preco = novoPreco; /*Atribui o novo preco e atualiza-o nas encomendas*/
    for (i=0; i<=ide; i++){
        int n =encomendas[i].numProd;
        for(e=0; e<=n; e++)
            if (prod == encomendas[i].produtos[e].identificador){
                encomendas[i].produtos[e].preco = novoPreco;
                break;
            }
    }
}

void ListProdEnc(){
    /*Funcao lista a descri??o e a quantidade de um produto numa encomenda existente no sistema*/
    int enc, prod, i, n;
    scanf("%d:%d", &enc, &prod);
    
    if (enc > ide || enc < 0){ /*condicoes de erro*/
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
        return;
    }
    else if (prod > idp || prod < 0){
        printf("Impossivel listar produto %d. Produto inexistente.\n", prod);
        return;
    }

    n = encomendas[enc].numProd;
    for (i=0; i <= n ; i++) /*Procura e imprime a informacao se o poduto estiver na encomenda*/
        if (prod == encomendas[enc].produtos[i].identificador){
            printf("%s %d.\n", produtos[prod].descricao, encomendas[enc].produtos[i].stock);
            return;
        }
    printf("%s 0.\n", produtos[prod].descricao);  /*Caso nao esteja*/

}

void ProdMaiorQnt(){
    /*Funcao lista o identificador da encomenda em que um dado produto ocorre mais vezes.*/
    int prod, max = 0, enc =-1, i, e;
    scanf("%d", &prod);
    if (prod > idp || prod < 0){ /*Condicao de erro*/
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod);
        return;
    }

    for (i=0; i<=ide; i++){  /*Procura o produto pelas encomendas*/
        int n = encomendas[i].numProd;
        for(e=0; e<=n; e++)
            if(prod == encomendas[i].produtos[e].identificador && encomendas[i].produtos[e].stock > max){  /*Simbolo de maior e a condicao de */
                max = encomendas[i].produtos[e].stock;                                                     /*desempate (manter o de menor id)*/
                enc = i;
            }
    }
    if (enc != -1)  /*Caso tenha encontrado o produto imprime o que tem maior quantidade*/
        printf("Maximo produto %d %d %d.\n", prod, enc, max);
}

void ListPorPreco(){
    /*Funcao lista todos os produtos existentes no sistema por ordem crescente de preco.*/
    int precosProd[MAXPROD];     /*Lista com precos a ordenar*/
    int idPrecos[MAXPROD];       /*Lista guarda identificadores dos
                                 produtos por ordem crescente de preco*/
    int i;
    
    /*Atribui as listas os valores dos precos e ids dos produtos*/
    for (i = 0; i <= idp; i++){ 
        precosProd[i] = produtos[i].preco;
        idPrecos[i] = i;
    }

    /*Poe a lista "idPrecos" pela ordem que organiza os produtos por ordem crescente de preco*/
    MergeSort(precosProd, idPrecos, 0, idp); 
    
    /*Imprime pela ordem da lista "idPrecos"*/
    printf("Produtos\n");
    for (i=0; i<= idp; i++){ 
        int e = idPrecos[i];
        printf("* %s %d %d\n", produtos[e].descricao, produtos[e].preco, produtos[e].stock);
    }

}

void ListEncAlf(){
    /*Funcao lista todos os produtos de uma encomenda por ordem alfabetica da descri??o.*/
    int enc, i, n;
    char descs[MAXPESO][MAXDESC];
    int ordemDesc[MAXPESO];
    scanf("%d", &enc);

    if (enc > ide || enc < 0){  /*Condicao de erro*/
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", enc);
        return;
    }

    /*Atribui as listas as descricoes e  o ids dos produtos*/
    n = encomendas[enc].numProd;
    for (i=0; i<= n; i++){
        strcpy(descs[i], encomendas[enc].produtos[i].descricao);
        ordemDesc[i] = i;
    }

    /*Poe a lista "ordemDesc" pela ordem que organiza os produtos por ordem alfabetica de descricao*/
    MergeSortString(descs, ordemDesc, 0, n);

    /*Imprime pela ordem da lista "ordemDesc"*/
    printf("Encomenda %d\n", enc);
    for(i=0; i<=n; i++)
        printf("* %s %d %d\n", descs[i],  encomendas[enc].produtos[ordemDesc[i]].preco, encomendas[enc].produtos[ordemDesc[i]].stock);
}

int main(){
    int c=0;

    /*Recebe o caracter do comando e executa a funcao correspondente (Mais compacto que switch)*/
    c = getchar();
    while (c != 'x'){
        if (c == 'a')
            NovoProduto();
        else if (c == 'q')
            AddStock();
        else if (c == 'N')
            NovaEncomenda();
        else if (c == 'A')
            AddProduto();
        else if (c == 'r')
            RemStock();
        else if (c == 'R')
            RemProdEnc();
        else if (c == 'C')
            CalcPreco();
        else if (c == 'p')
            AltPreco();
        else if (c == 'E')
            ListProdEnc();
        else if (c == 'm')
            ProdMaiorQnt();
        else if (c == 'l')
            ListPorPreco();
        else if (c == 'L')
            ListEncAlf();

        c = getchar();
    }
    
    
    return 0;
}
