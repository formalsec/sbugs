#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Produtos_MAX 10000             /* Maximo de Produtos permitidos no sistema                  */
#define Encomendas_MAX 500             /* Maximo de Encomendas permitidas no sistema                */
#define Descricao_Do_Produto_MAXC 63   /* Maximo de caracteres permitidos na Descricao nos Produtos */
#define Peso_Da_Encomenda_MAX 200      /* Maximo de Unidades de Peso permitidos nas Encomendas      */


/* Declaracao das funcoes que vao ser usadas no programa para alem da main para poderem ser usadas na mesma */

int getId();
int get_Number();
void Novo_Produto();
void Add_Quantidade();
void Nova_Encomenda();
void Add_Produto_Encomenda();
void Remove_Stock();
void Remove_Produto();
void Calcula_Custo();
void Altera_Preco();
void Lista_Um_Produto();
void Encomenda_Com_Mais_Produto();
void Lista_Produtos_Sistema_Preco_Crescente();
void Lista_Produtos_Encomenda_Alfabeticamente();
void mergesort();
void merge();


/* Criacao de 2 estruturas. A 1a carateriza os Produtos e a 2a, as Encomendas. */

struct Produto{
    int  Identificador;
    int  Preco;
    int  Peso;
    int  Quantidade_Stock;
    int  Quantidade_Encomenda;
    char Descricao[Descricao_Do_Produto_MAXC];
};

struct Encomenda{
    struct Produto arr_Produto[Produtos_MAX];
    int Peso;
    int Numero_Da_Encomenda;
    int Custo;
};

/* Inicializacao de 4 Variaveis Globais. As primeiras 2 servem como repositorio dos produtos e das encomendas respetivamente. As outras duas servem como copia do conjunto dos produtos que vao ser ordenadas nos comnados l e L. */
struct Produto arr_Produto[Produtos_MAX];
struct Encomenda arr_Encomenda[Encomendas_MAX];
struct Produto arr_Produto2[Produtos_MAX];
struct Produto arr2[Produtos_MAX];

/* Inicializacao de 6 variaveis globais que vao ser usadas ao longo do programa */
int Id = -1;
int Number = -1;
int Escolhe_Lista = 2;
int idp = 0;
int ide = 0;
int qnt = 0;

/* Funcao principal composta por um ciclo constantemente a espera de comandos e executando esses comandos (atraves de funcoes) ate que o comando seja o fim do programa */
int main(){
    char comando;
    comando = getchar();
    while (comando != 'x'){
        switch(comando){
            case 'a':
            Novo_Produto();
            break;

            case 'q':
            Add_Quantidade();
            break;

            case 'N':
            Nova_Encomenda();
            break;

            case 'A':
            Add_Produto_Encomenda();
            break;
            
            case 'r':
            Remove_Stock();
            break;

            case 'R':
            Remove_Produto();
            break;

            case 'C':
            Calcula_Custo();
            break;

            case 'p':
            Altera_Preco();
            break;

            case 'E':
            Lista_Um_Produto();
            break;

            case 'm':
            Encomenda_Com_Mais_Produto();
            break;

            case 'l':
            Lista_Produtos_Sistema_Preco_Crescente();
            break;

            case 'L':
            Lista_Produtos_Encomenda_Alfabeticamente();
            break;    
        }
        comando = getchar();
    }
    return 0;
}

/* As funcoes do tipo int get_Id e get_Number sao funcoes bastante simples e intuitivas que servem para dar um identificador a um produto e dar um numero a uma encomenda, resspetivamente */
int get_Id(){
    Id ++;
    return Id;
}

int get_Number(){
    Number ++;
    return Number;
}

/* Funcao referente ao primeiro comando exposto na main (a) que cria um novo produto no sistema. Atraves desta funcao, o produto recebe um identificador e, atraves do input, uma descricao, preco, peso e quantidade em stock */
void Novo_Produto(){
    Id = get_Id();
    arr_Produto[Id].Identificador = Id; 
    scanf(" %[^:]:%d:%d:%d", arr_Produto[Id].Descricao, &arr_Produto[Id].Preco, &arr_Produto[Id].Peso, &arr_Produto[Id].Quantidade_Stock);
    printf("Novo produto %d.\n", arr_Produto[Id].Identificador);
}

/* Funcao referente ao segundo comando exposto na main (q) que adiciona quantidade a um produto no stock. Caso esse produto nao exista, sera emitido um erro. */
void Add_Quantidade(){
    scanf("%d:%d", &idp, &qnt);
    if (arr_Produto[idp].Peso > 0){
        arr_Produto[idp].Quantidade_Stock += qnt;
    }
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}

/* Funcao referente ao terceiro comando exposto na main (N) que cria uma nova encomenda a qual e atribuida um numero. */
void Nova_Encomenda(){
    Number = get_Number();
    arr_Encomenda[Number].Numero_Da_Encomenda = Number;
    printf("Nova encomenda %d.\n", Number);
}

/* Funcao referente ao quarto comando exposto na main (A) que adiciona um determinado produto numa determinada quantidade a uma encomenda. Caso a encomenda ou o produto nao existam ou nao haja quantidade em stock suficiente ou ainda atraves desta adicao o peso da encomenda exceda o seu maximo, serao emitidos erros. */
void Add_Produto_Encomenda(){
    scanf(" %d:%d:%d", &ide, &idp, &qnt);
    if (ide > Number){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (idp > Id){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else if (qnt > arr_Produto[idp].Quantidade_Stock){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else if(arr_Encomenda[ide].Peso + (arr_Produto[idp].Peso * qnt) > Peso_Da_Encomenda_MAX){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }
    else{
        arr_Produto[idp].Quantidade_Stock -= qnt;
        arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda += qnt;
        arr_Encomenda[ide].Peso += arr_Produto[idp].Peso * qnt;
        arr_Encomenda[ide].Custo += arr_Produto[idp].Preco * qnt;
        arr_Encomenda[ide].arr_Produto[idp].Preco = arr_Produto[idp].Preco;
        arr_Encomenda[ide].arr_Produto[idp].Peso = arr_Produto[idp].Peso;
        strcpy(arr_Encomenda[ide].arr_Produto[idp].Descricao, arr_Produto[idp].Descricao);
    }
}

/* Funcao referente ao quinto comando exposto na main (r) que remove quantidade em stock de um determinado produto. Caso o produto nao exista ou a quantidade que se pretende remover for maio que a quantidade em stock, serao emitidos erros. */
void Remove_Stock(){
    scanf("%d:%d", &idp, &qnt);
    if (idp > Id){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
    else if (qnt > arr_Produto[idp].Quantidade_Stock){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qnt, idp);
    }
    else{
        arr_Produto[idp].Quantidade_Stock -= qnt;
    }
}

/* Funcao referente ao sexto comando na main (R) que, teoricamente, remove um determindado produto de uma determinada encomenda. Praticamente, altera a quantidade do produto na encomenda para 0 e e modifica os valores do preco e peso da encomenda. Caso a encomenda ou o produo nao existam, serao emitidos erros. */
void Remove_Produto(){
    scanf("%d:%d", &ide, &idp);
    if (ide > Number){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (idp > Id){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else{
        arr_Encomenda[ide].Custo -= arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda * arr_Produto[idp].Preco;
        arr_Encomenda[ide].Peso -= arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda * arr_Produto[idp].Peso;
        arr_Produto[idp].Quantidade_Stock += arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda;
        arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda = 0;
    }
}

/* Funcao referente ao setimo comando exposto na main (C) que, teoricamente, calcula o custo de uma determinada encomenda. Na pratica, este valor ja esta associado a encomenda atraves de funcoes anteriores entao e apenas exposto esta sua carateristica. Caso a encomenda nao exista, sera emitido um erro. */
void Calcula_Custo(){
    scanf("%d", &ide);
    if (ide > Number){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        printf("Custo da encomenda %d %d.\n", ide, arr_Encomenda[ide].Custo);
    }
}

/* Funcao referente ao oitavo comando exposto na main (p) que altera o preco de um produto no sistema. Logicamente, altera tambem o preco do produto nas encomendas em que este exista alterando os seus custos. Caso o produto nao exista, sera emitido um erro. */
void Altera_Preco(){
    int Novo_Preco;
    scanf("%d:%d", &idp, &Novo_Preco);
    if(idp > Id){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        /* este ciclo for corre todas as encomendas, ve se existe o produto e caso exista, atualiza o custo da encomenda conforme o novo preco do produto */
        for (ide = 0; ide <= Number; ide++){
                if (arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda != 0){
                    arr_Encomenda[ide].Custo -= arr_Produto[idp].Preco * arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda; 
                    arr_Encomenda[ide].Custo += Novo_Preco * arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda;
                    arr_Encomenda[ide].arr_Produto[idp].Preco = Novo_Preco;
                }
        }
        arr_Produto[idp].Preco = Novo_Preco;
    }
}

/* Funcao referente ao nono comando exposto na main (E) que lista a descricao e quantidade de  um determinado produto numa determinada encomenda. Caso o produto ou a encomenda nao existam, serao emitidos erros. */
void Lista_Um_Produto(){
    scanf("%d:%d", &ide, &idp);
    if (ide > Number){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if (idp > Id){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else{
        printf("%s %d.\n", arr_Produto[idp].Descricao, arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda);
    }
}

/* Funcao referente ao decimo comando exposto na main (m) que devolve o numero da encomenda onde um determinado produto existe em maior quantidade. Devolve tambem o identificador do produto e a quantidade do mesmo na encomenda devolvida antes. */
void Encomenda_Com_Mais_Produto(){
    int ide_resposta;
    scanf("%d", &idp);
    if (idp > Id){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else{
        qnt = 0;
        /* este ciclo for corre todas as encomendas e vai guardando aquela em que o produto existe em maior quantidade e a quantidade em si. */
        for (ide = 0; ide <= Number; ide ++){ 
            if (arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda > qnt){
                qnt = arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda;
                ide_resposta = ide;
            }
        }if (qnt > 0){
            printf("Maximo produto %d %d %d.\n", idp, ide_resposta, qnt);
        }
    }
}

/* Funcao referente ao decimo primeiro comando exposto na main (l) que lista todos os produtos no sistema por preco crescente. Esta funcao e uma das duas funcoes que usam um algoritmo de ordenacao(merge) definido em ultimo lugar no programa. */
void Lista_Produtos_Sistema_Preco_Crescente(){
    int contador=0, idp2=0;
    /* Escolhe_Lista a 0 para na funcao de ordenacao saber qual caminho seguir visto que ha duas funcoes que utilizam a funcao de ordenacao embora para comparar e organizar segundo coisas distintas. */
    Escolhe_Lista = 0;
    /* Este ciclo for server para criar um novo array dos Produtos no sistema ,igual ao array original, que vai ser ordenado. Assim, perserva-se o array original. */
    for(idp = 0; idp<=Id; idp ++){
        if (arr_Produto[idp].Peso != 0){
            arr_Produto2[idp2] = arr_Produto[idp];
            idp2 ++;    
        }
        /* esta variavel funciona como contador para saber o extremo do array com vista a ser usado na proxima linha ao aplicar a funcao mergesort. */
        else{
            contador++;  
        }
    }
    /* da-se agora a ordenacao do array criado e no ciclo for, listamos entao os produtos no sistema por ordem crescente de precos */
    mergesort(arr_Produto2, 0, Id-contador);
    printf("Produtos\n");
    for (idp = 0; idp <= Id-contador; idp ++){
        printf("* %s %d %d\n", arr_Produto2[idp].Descricao, arr_Produto2[idp].Preco, arr_Produto2[idp].Quantidade_Stock);
    }
}

/* Funcao referente ao ultimo comando exposto na main (L) que lista os produtos numa determinada encomenda por ordem alfabetica. Esta funcao funciona de maneira semelhante a funcao antes descrita. No entanto, a variavel Escolhe_Lista fica a 1 para a funcao de ordenacao comparar as descricoes dos produtos. Caso a encomenda nao exista, sera emitido um erro. */
void Lista_Produtos_Encomenda_Alfabeticamente(){
    int contador=0, idp2=0;
    Escolhe_Lista = 1;
    scanf("%d", &ide);
    if (ide > Number){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        for(idp = 0; idp<=Id; idp ++){
            if (arr_Encomenda[ide].arr_Produto[idp].Quantidade_Encomenda != 0){
                arr_Produto2[idp2] = arr_Encomenda[ide].arr_Produto[idp];
                idp2 ++;
            }
            else{
                contador++;
            }
        }    
        mergesort(arr_Produto2, 0, Id-contador);
        printf("Encomenda %d\n", ide);
        for (idp = 0; idp <= Id-contador; idp ++){
            printf("* %s %d %d\n", arr_Produto2[idp].Descricao, arr_Produto2[idp].Preco, arr_Produto2[idp].Quantidade_Encomenda);
        }
    }
}

/* As funcoes mergesort e merge sao a representacao do algoritmo mergesort. A unica alteracao e o existirem dois termos de comparacao (preco e descricao). Atraves da variavel global Escolhe_Lista, a funcao de ordenacao sabe qual dos termos comparar */
void mergesort(struct Produto arr[], int l, int r){
    int meio = (r + l) / 2;
    if (r <= l){
        return;
    }
    mergesort(arr, l, meio);
    mergesort(arr, meio + 1, r);
    merge(arr, l, meio, r);
    }
    
void merge(struct Produto arr[], int l, int m, int r){
    int i, j, k;
for (i = m + 1; i > l; i--){
        arr2[i - 1] =arr[i - 1];
    }
    for (j = m; j < r; j++){
        arr2[r + m - j] = arr[j + 1];
    }
    for( k = l; k <= r; k++){
        /* Caso se pretenda comparar os precos, Escolhe_Lista estara a 0 e seguira estes termos de comparacao. */
        if (Escolhe_Lista == 0){
            if(arr2[j].Preco < arr2[i].Preco){
                arr[k] = arr2[j--];
            }
            else if(arr2[j].Preco == arr2[i].Preco && arr2[j].Identificador < arr2[i].Identificador){
                arr[k] = arr2[j--];
            }
            else{
                arr[k] = arr2[i++];
            }
        }
        /* Caso se pretenda comparar as descricoes, Escolhe_Lista estara a 1 e seguira estes termos de comparacao. */
        else if (Escolhe_Lista == 1){
            if (strcmp(arr2[j].Descricao, arr2[i].Descricao) < 0){
                arr[k] = arr2[j--];
            }
            else{
                arr[k] = arr2[i++];
            }
        }
    }
}

 /* Projecto realizado no ambito da cadeira de Introducao a Algoritmos e Estrutura de Dados.*/
 /* Instituto Superior Tecnico (Taguspark)*/

/********************************************************FIM***DO***PROJETO*****************************************/