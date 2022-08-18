#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 10000
#define PACKAGE 500
#define STRING 63
#define MAX 100
#define OVERWEIGHT 200

/* estrutura usada para definir um produto*/
typedef struct produto{
    char descricao[STRING];
    int preco;
    int peso;
    int quantidade;
    int id;
}produto;

/*estrutura usada para definir uma encomenda
  pode ter ate 10000 produtos*/
typedef struct encomenda{
    produto produtos[SIZE];
    int peso;
    int id;
    int lastP;
}encomenda;

/*armazem usado para gerir os produtos disponiveis
  pode ter ate 10000 produtos*/
produto armazem[SIZE];
/*encomendas e um vetor que pode ter ate 500 estruturas encomenda*/
encomenda encomendas[PACKAGE];
/*lastA indica a posicao do ultimo produto no armazem*/
int lastA = -1;
/*lastE regista a posicao da ultima encomenda em encomendas*/
int lastE = -1;

/*funcao auxiliar usada para localizar o produto com id idp
  na encomenda com id ide*/
int find(int idp, int ide){
    int i;
    /*percorre todas as posicoes de encomendas ate a posicao do ultimo produto nessa encomenda*/
    for(i = 0; i <= encomendas[ide].lastP; i++){
        /*caso encontre o produto com id idp na encomenda ide*/
        if(encomendas[ide].produtos[i].id == idp){
            /*retorna a posicao do produto idp na encomenda ide*/
            return i;
        }
    }
    /*caso nao encontre o produto com id idp na encomenda de id ide, retorna -1*/
    return -1;
}

/*funcao auxiliar que devolve a posicao para o produto, com id idp, que se quer inserir no vetor produtos da encomenda com id ide*/
int newPosPE(int idp, int ide){
    int i, j;
    /*percorre todos os produtos da encomenda ide*/
    for(i = 0; i <= encomendas[ide].lastP; i++){
        /*caso a descricao do produto idp seja alfabeticamente anterior a descricao do produto encontrado na posicao i*/
        if(strcmp(armazem[idp].descricao, encomendas[ide].produtos[i].descricao) < 0){
            /*copia todos os produtos, que se encontrem posteriormente a essa posicao i, para a posicao seguinte*/
            for(j = encomendas[ide].lastP; j >= i; j--){
                encomendas[ide].produtos[j+1] = encomendas[ide].produtos[j];
            }
            /*soma 1 a variavel que garda a ultima posicao dos produtos na encomenda ide*/
            encomendas[ide].lastP++;
            /*retorna a posicao onde pode inserir o novo produto idp*/
            return i;
        }
    }
    /*caso nao haja produtos na encomenda ide, ou a descricao do produto idp e alfabeticamente posterior ao ultimo produto
      aumenta 1 a variavel que guarda a ultima posicao dos produtos na encomenda ide*/
    encomendas[ide].lastP++;
    /*retorna a ultima posicao*/
    return encomendas[ide].lastP;
}

/*funcao auxiliar usada para inserir todos os produtos de armazem
  num vetor temporario*/
void copy(produto *arr){
    int i;
    /*percorre todas as posicoes de armazem ate a posicao do ultimo produto nele inserido*/ 
    for(i = 0; i <= lastA; i++){
        /*copia o produto do armazem com posicao i para o novo vetor*/
        arr[i] = armazem[i];
    }
}

/*funcao qure aplica heapify a subtree com raiz i, que e uma posicao  
   no vetor arr. n e o size do heap*/ 
void heapify(produto *arr, int n, int i){ 
    /*inicia a posicao do maximo como a raiz*/
    int largest = i; 
    int l = 2*i + 1;
    int r = 2*i + 2;  
    produto temp; 
  
    /* caso o no esquerdo seja maior que a raiz*/ 
    if (l < n && (arr[l].preco > arr[largest].preco || (arr[l].preco == arr[largest].preco && arr[l].id > arr[largest].id))){
        largest = l; 
    }
  
    /* caso o no direito seja maior que o largest de momento*/ 
    if (r < n && (arr[r].preco > arr[largest].preco || (arr[r].preco == arr[largest].preco && arr[r].id > arr[largest].id))){
        largest = r; 
    }
  
    /* caso o largest nao seja raiz*/ 
    if (largest != i){
        /*troca a estrutura produto da posicao i com a da posicao largest*/ 
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        /* recursivamente aplica a funcao heapify a sub tree*/
        heapify(arr, n, largest); 
    } 
} 
  
/* funcao principal para o algoritmo heap sort*/ 
void heapSort(produto *arr, int n){ 
    int i;
    produto temp;
    /* cria o heap (reorganiza o vetor temporario arr)*/ 
    for (i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i); 
    }
  
    /* extrai um elemento de cada vez do heap*/ 
    for (i = n-1; i > 0; i--){ 
        /* move a atual raiz para o fim do array*/ 
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
  
        /* aplica heapify ao heap reduzido*/ 
        heapify(arr, i, 0); 
    } 
} 

/*funcao que adiciona produtos ao armazem*/
void add(){
    char input[MAX], description[STRING];
    int price, weight, qtd;
    /*le o input do terminal e guarda-o na variavel input*/
    fgets(input, sizeof(input), stdin);
    /*separa o input pelos : guarda cada numa variavel*/
    strcpy(description, strtok(input, ":"));
    price = atoi(strtok(NULL, ":"));
    weight = atoi(strtok(NULL, ":"));
    qtd = atoi(strtok(NULL, ":"));
    /*guarda o produto na posicao posterior a lastA*/
    strcpy(armazem[++lastA].descricao, description);
    armazem[lastA].preco = price;
    armazem[lastA].peso = weight;
    armazem[lastA].quantidade = qtd;
    armazem[lastA].id = lastA;
    printf("Novo produto %d.\n", lastA);
}

/*funcao que adiciona quantidade ao produto idp*/
void addStock(){
    int idp, qtd;
    char input[MAX];
    /*le o input do terminal e guarda-o na variavel input*/
    fgets(input, sizeof(input), stdin);
    /*reparte o input
      so aplica a funcao se ler 2 valores*/
    if(sscanf(input, "%d:%d", &idp, &qtd) == 2){
        /*caso o idp pedido seja superior ao ultimo criado, no produto nao existe*/
        if(idp > lastA){
            printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        }
        /*caso contrario, soma a quantidade existente a pretendida*/
        else{
            armazem[idp].quantidade += qtd;
        }
    }
}

/*funcao que cria uma nova encomenda*/
void novaE(){
    /*aumenta 1 a variavel que indica a pos da ultima encomenda*/
    lastE++;
    /*guarda o id*/
    encomendas[lastE].id = lastE;
    /*inicializa a variavel que guarda a pos do ultimo produto nessa encomenda a -1*/
    encomendas[lastE].lastP = -1;
    printf("Nova encomenda %d.\n", lastE);
}

/*funcao que adiciona um produto a uma encomenda*/
void addToE(){
    int posPE, ide, idp, qtd;
    char input[MAX];
    /*le o input do terminal e guarda-o na variavel input*/
    fgets(input, sizeof(input), stdin);
    /*so aplica a funcao caso leia 3 valores do input*/
    if(sscanf(input, "%d:%d:%d", &ide, &idp, &qtd) == 3){
        /*caso o idp pretendido for superior a pos do ultimo produto no armazem, nao existe*/
        if(idp > lastA){
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        /*caso o ide pretendido for superior a pos da ultima encomenda, nao existe*/
        else if(ide > lastE){
            printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        }
        /*verifica se e possivel retirar a quantidade pretendida ao produto idp no armazem*/
        else if(armazem[idp].quantidade < qtd){
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        }
        /*verifica se, adicionando ao peso ja existente na encomenda ide, o peso do produto a adicionar supera o peso limite de 200*/
        else if((encomendas[ide].peso + armazem[idp].peso*qtd) > OVERWEIGHT){
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        /*caso passe aos erros*/
        else{
            /*retira a quantidade pretendida ao armazem*/
            armazem[idp].quantidade -= qtd;
            /*aumenta o peso da encomenda ide*/
            encomendas[ide].peso += armazem[idp].peso*qtd;
            /*caso o produto idp ja exista na encomenda ide, basta adicionar quantidade*/
            if((posPE = find(idp, ide)) != -1){
                encomendas[ide].produtos[posPE].quantidade += qtd;
            }
            /*caso contrario*/
            else{
                /*descobre-se a posicao para o produto que se deseja adicionar*/
                posPE = newPosPE(idp, ide);
                /*guardam-se os valores na encomenda ide*/
                strcpy(encomendas[ide].produtos[posPE].descricao, armazem[idp].descricao);
                encomendas[ide].produtos[posPE].preco = armazem[idp].preco;
                encomendas[ide].produtos[posPE].peso = armazem[idp].peso;
                encomendas[ide].produtos[posPE].quantidade = qtd;
                encomendas[ide].produtos[posPE].id = armazem[idp].id;
            }
        }
    }
}

/*funcao que retira quantidade a um produto do armazem*/
void removeFromA(){
    int idp, qtd;
    char input[MAX];
    /*le o input do terminal e guarda-o na variavel input*/
    fgets(input, sizeof(input), stdin);
    /*so aplica a funcao caso leia 2 valores do input*/
    if(sscanf(input, "%d:%d", &idp, &qtd) == 2){
        /*caso o idp pretendido for superior a pos do ultimo produto no armazem, nao existe*/
        if(idp > lastA){
            printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        }
        /*verifica se e possivel retirar a quantidade pretendida ao produto idp no armazem*/
        else if(armazem[idp].quantidade < qtd){
                printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        }
        /*caso contrario retira qtd a quantidade existente do produto idp*/
        else{
            armazem[idp].quantidade -= qtd;
        }
    }
}

/*funcao que remove um produto de uma encomenda*/
void removeFromE(){
    int posPE, ide, idp;
    char input[MAX];
    /*le o input do terminal e guarda-o na variavel input*/
    fgets(input, sizeof(input), stdin);
    /*so aplica a funcao se ler 2 valores do input*/
    if(sscanf(input, "%d:%d", &ide, &idp) == 2){
        /*caso o ide pretendido for superior a pos da ultima encomenda, nao existe*/
        if(ide > lastE){
            printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        }
        /*caso o idp pretendido for superior a pos do ultimo produto no armazem, nao existe*/
        else if(idp > lastA){
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        /*caso o produto idp esteja na encomenda ide*/
        else if((posPE = find(idp, ide)) != -1){
            /*recoloca no armazem a quantidade que existia na encomenda*/
            armazem[idp].quantidade += encomendas[ide].produtos[posPE].quantidade;
            /*reduz o peso da encomenda*/
            encomendas[ide].peso -= encomendas[ide].produtos[posPE].quantidade*encomendas[ide].produtos[posPE].peso;
            /*coloca a quantidade do produto idp na encomenda ide a 0*/
            encomendas[ide].produtos[posPE].quantidade = 0;
        }
    }
}

/*funcao que calcula o preco total de uma encomenda*/
void totalPrice(){
    int ide, sum = 0, i;
    char input[MAX];
    /*le o input do terminal e guarda-o na variavel input*/
    fgets(input, sizeof(input), stdin);
    /*a funcao corre apenas se ler um e um so valor do input*/
    if(sscanf(input, "%d", &ide) == 1){
        /*caso o ide pretendido for superior a pos da ultima encomenda, nao existe*/
        if(ide > lastE){
            printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        }
        /*caso contrario*/
        else{
            /*percorre todos os produtos existentes na encomenda ide*/
            for(i = 0; i <= encomendas[ide].lastP; i++){
                /*aumenta ao custo total o valor total do produto*/
                sum += encomendas[ide].produtos[i].preco*encomendas[ide].produtos[i].quantidade;
            }
            printf("Custo da encomenda %d %d.\n", ide, sum);
        }
    }
}

/*funcao que altera o preco de um produto*/
void changePrice(){
    int ide, posPE, idp, price;
    char input[MAX];
    /*le o input do terminal e guarda-o na variavel input*/
    fgets(input, sizeof(input), stdin);
    /*a funcao so se realiza caso se leiam 2 valores do input*/
    if(sscanf(input, "%d:%d", &idp, &price) == 2){
        /*caso o idp pretendido for superior a pos do ultimo produto no armazem, nao existe*/
        if(idp > lastA){
            printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        }
        /*caso contrario*/
        else{
            /*altera o preco do produto idp*/
            armazem[idp].preco = price;
            /*para todas as encomendas existentes*/
            for(ide = 0; ide <= lastE; ide++){
                /*caso o produto idp esteja presente nessa encomenda*/
                if((posPE = find(idp, ide)) != -1){
                    /*altera o preco tambem*/
                    encomendas[ide].produtos[posPE].preco = price;
                }
            }
        }
    }
}

/*funcao que demonstra a descricao, preco e quantidade de um produto existente numa encomenda*/
void showPInE(){
    int posPE, ide, idp;
    char input[MAX];
    /*le o input do terminal e guarda-o na variavel input*/
    fgets(input, sizeof(input), stdin);
    /*a funcao so acontece caso leia do input 2 valores*/
    if(sscanf(input, "%d:%d", &ide, &idp) == 2){
        /*caso o ide pretendido for superior a pos da ultima encomenda, nao existe*/
        if(ide > lastE){
            printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        }
        /*caso o idp pretendido for superior a pos do ultimo produto no armazem, nao existe*/
        else if(idp > lastA){
            printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        }
        /*caso o produto idp esteja na encomenda ide*/
        else if((posPE = find(idp, ide)) != -1){
            printf("%s %d.\n", armazem[idp].descricao, encomendas[ide].produtos[posPE].quantidade);
        }
        /*caso contrario aparece a 0*/
        else{
            printf("%s 0.\n", armazem[idp].descricao);
        }
    }
}

/*funcao que apresenta a encomenda com mais produto*/
void eWithMostP(){
    int ide, max = 0, posPE, posE, idp;
    char input[MAX];
    /*le o input do terminal e guarda-o na variavel input*/
    fgets(input, sizeof(input), stdin);
    /*apenas realiza caso leia um valor do imput*/
    if(sscanf(input, "%d", &idp) == 1){
        /*caso o idp pretendido for superior a pos do ultimo produto no armazem, nao existe*/
        if(idp > lastA){
            printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        }
        /*caso contrario*/
        else{
            /*para todas as encomendas criadas*/
            for(ide = 0; ide <= lastE; ide++){
                /*caso o produto idp exista na encomenda ide*/
                if((posPE = find(idp, ide)) != -1){
                    /*caso a quantidade do produto idp na encomenda ide seja superior ao max*/
                    if(encomendas[ide].produtos[posPE].quantidade > max){
                        /*guarda um novo maximo em max e a posicao da encomenda em posE*/
                        max = encomendas[ide].produtos[posPE].quantidade;
                        posE = ide;
                    }
                }
            }
            /*caso o max mude, apresenta o resultado*/
            if(max != 0){
                printf("Maximo produto %d %d %d.\n", idp, encomendas[posE].id, max);    
            }
        }
    }
}

/*funcao que apresenta todos os produtos do armazem por ordem ascendente de preco*/
void printA(){
    int i;
    /*cria um ponteiro para produto temporario que sera usado para guardar e ordenar todos os produtos no armazem*/
    produto *sortedArmazem = (produto*)malloc(SIZE*sizeof(produto));
    /*copia o armazem para o sortedArmazem*/
    copy(sortedArmazem);
    /*ordena o sortedArmazem*/
    heapSort(sortedArmazem, lastA+1);
    printf("Produtos\n");
    /*imprime todos os produtos ate a ultima posicao com produto*/
    for(i = 0; i <= lastA; i++){
        printf("* %s %d %d\n", sortedArmazem[i].descricao, sortedArmazem[i].preco, sortedArmazem[i].quantidade);
    }
    /*liberta a memoria utilizada no sortedArmazem*/
    free(sortedArmazem);
}

/*funcao que mostra todos os produtos numa certa encomenda*/
void printE(){
    int i, ide;
    char input[MAX];
    /*le o input do terminal e guarda-o na variavel input*/
    fgets(input, sizeof(input), stdin);
    /*a funcao apenas corre caso leia um valor do input*/
    if(sscanf(input, "%d", &ide) == 1){
        /*caso o ide pretendido for superior a pos da ultima encomenda, nao existe*/
        if(ide > lastE){
            printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        }
        /*caso contrario*/
        else {
            printf("Encomenda %d\n", ide);
            /*para todos os produtos na encomenda ide*/
            for(i = 0; i <= encomendas[ide].lastP; i++){
                /*caso a quantidade do produto na posicao i nao seja nula, imprime no output*/
                if(encomendas[ide].produtos[i].quantidade > 0){
                    printf("* %s %d %d\n", encomendas[ide].produtos[i].descricao, encomendas[ide].produtos[i].preco, encomendas[ide].produtos[i].quantidade);
                }
            }
        }
    }
}

/*funcao principal do programa*/
int main(){
    /*variavel que guarda o comando a executar*/
    char comand = getchar();
    /*caso o comando seja x, termina o programa*/
    while(comand != 'x'){
        /*le um espaco, sem o guardar*/
        getchar();
        /*caso leia o comando a*/
        if(comand == 'a'){
            /*executa-se a funcao associada a a*/
            add();
        }
        /*caso leia o comando q*/
        else if(comand == 'q'){
            /*executa-se a funcao associada a q*/
            addStock();
        }
        /*caso leia o comando N*/
        else if(comand == 'N'){
            /*executa-se a funcao associada a N*/
            novaE();
        }
        /*caso leia o comando A*/
        else if(comand == 'A'){
            /*executa-se a funcao associada a A*/
            addToE();
        }
        /*caso leia o comando r*/
        else if(comand == 'r'){
            /*executa-se a funcao associada a r*/
            removeFromA();
        }
        /*caso leia o comando R*/
        else if(comand == 'R'){
            /*executa-se a funcao associada a R*/
            removeFromE();
        }
        /*caso leia o comando C*/
        else if(comand == 'C'){
            /*executa-se a funcao associada a C*/
            totalPrice();
        }
        /*caso leia o comando p*/
        else if(comand == 'p'){
            /*executa-se a funcao associada a p*/
            changePrice();
        }
        /*caso leia o comando E*/
        else if(comand == 'E'){
            /*executa-se a funcao associada a E*/
            showPInE();
        }
        /*caso leia o comando m*/
        else if(comand == 'm'){
            /*executa-se a funcao associada a m*/
            eWithMostP();
        }
        /*caso leia o comando l*/
        else if(comand == 'l'){
            /*executa-se a funcao associada a l*/
            printA();
        }
        /*caso leia o comando L*/
        else if(comand == 'L'){
            /*executa-se a funcao associada a L*/
            printE();
        }
        /*variavel que guarda o comando a executar*/
        comand = getchar();
    }
    return 0;
}