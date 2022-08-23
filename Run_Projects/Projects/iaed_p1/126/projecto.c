#include <stdio.h>
#include <string.h>

#define MAX_DES 63  /* A descricao tem no maximo 63 caracteres */
#define MAX_COM 80 /* Um comando tem no maximo 80 caracteres */
#define MAX_PRO 10000 /* Ha no maximo 10 000 produtos */
#define MAX_ENC 500 /* Ha no maximo 500 encomendas */
#define MAX_PESO 200 /* Peso maximo de uma encomenda eh 200 */
#define MAX_PRO_ENC 200 /* Ha no maximo 200 produtos numa encomenda */


/* Estrutura produto: caracterizado por um id, uma descricao, um preco, peso e uma quantidade */
typedef struct p{
    int id;
    char descricao[MAX_DES];
    int preco;
    int peso;
    int qntd;
}Produto;

/* Estrutura encomenda: caracterizada por um id e peso */
typedef struct encomenda{
    int peso;
    int custo;
}Encomenda;

/* Definicao de variaveis globais */
Produto produtos[MAX_PRO]; /* Vetor que contem os produtos do sistema */
Produto produtos_encomendas[MAX_ENC][MAX_PRO_ENC]; /* Matriz que contem os produtos em cada encomenda */
Encomenda encomendas[MAX_ENC]; /* Matriz que contem as encomendas */
char comando[MAX_COM]={0}; /* O comando eh uma string */
Produto produtos_ordena[MAX_PRO]; /* Vetor auxiliar para as funcoes 'l' e 'L' */
int i[1]; /* Vetor que contem uma variavel de contagem */
int ids[2]; /* Vetor que guarda ide e idp (por esta ordem) quando sao introduzidos num comando */
int ide[]={-1}; /* Contem o ide atual (comeca no -1 antes da introducao da primera encomenda) */
int idp[]={-1}; /* Contem o idp atual (comeca no -1 antes da introducao do primeiro produto) */

/* Auxiliar as funcoes de ordenacao para melhorar eficiencia*/
typedef Produto Item;
#define key(A) (A)
#define less(A,B) (key(A)<key(B))
#define exch(A,B) {Item t=A;A=B;B=t;};

/* Funcao que ordena um vetor de produtos por ordem de preco */
void quicksortP(Item a[],int left, int right)
{

    int i = left-1;
    int j = right;
    Item v = a[right];
    if (right <= left) return;

    while (i < j) {
            while (less(a[++i].preco,v.preco) || (a[i].preco == v.preco && a[i].id<v.id));
            while (less(v.preco, a[--j].preco) || (v.preco == a[j].preco && v.id<a[j].id)){
                if (j == left)
                    break;
            }
            if (i < j){
            exch(a[i], a[j]);
            }
        }
        exch(a[i], a[right]);

    quicksortP(a, left, i-1);
    quicksortP(a, i+1, right);
}

/* Funcao que ordena os produtos de uma encomenda por ordem alfabetica usando bubble sort */
void bubbleD(Produto a[],int l, int r){
    int i,j;
    for(i=l;i<r;i++){
        for(j=l;j< r+(l-i);j++){
            if((strcmp(a[j+1].descricao,a[j].descricao))<0){
                exch(a[j+1],a[j]);
            }
        }
    }
}

/* Funcao auxiliar que guarda a informacao de um comando (linha introduzida) num vetor */
void obtemComando(){
    int c; /* Variavel de leitura */
    int i;

    c=getchar();
    for (i=0;c!='\n' && c!=EOF ;i++){ /* Percorre a linha */
        comando[i]=c; /* Guarda a linha num vetor 'comando' */
        c=getchar();
    }
    comando[i]='.'; /* '.' indica o fim de um comando*/
}

/* Funcao auxiliar que percorre strings e converte caracteres para inteiros */
int obtemInteiro(){
    int total=0;

    while(comando[i[0]]!=':' && comando[i[0]]!='.'){ /* Percorre os indices onde a string tem numeros */
        total=total*10+(comando[i[0]]-'0'); /* Contabiliza o valor convertendo cada caracter para inteiro e somando */
        i[0]++;
    }
    return total;
}

/* Funcao que adiciona um produto ao sistema*/
Produto adicionaProduto(){
    int total=0,n=0;
    Produto product; /* Inicializa a estrutura */

    i[0]=2; /* A informacao comeca no indice dois do input */

    product.id=idp[0];

    for (n=0; comando[i[0]]!=':';n++){ /* repete o ciclo ate ao ':' */
        product.descricao[n]=comando[i[0]]; /* copia cada caracter de c para a descricao */
        i[0]++;
    }

    product.descricao[n]='\0'; /* Adiciona o caracter de final de string */
    i[0]++; /* Passa para o indice a seguir ao ':' */

    total=obtemInteiro();

    product.preco=total;
    i[0]++;

    total=obtemInteiro();

    product.peso=total;
    i[0]++;

    total=obtemInteiro();

    product.qntd=total;

    return product;
}

/* Funcao que adiciona stock a um produto */
Produto adicionaStock(){
    int id,quantidade;

    i[0]=2; /* O id esta na segunda posicao da linha de entrada*/

    id=obtemInteiro();

    i[0]++; /* Salta o indice com ':'*/

    quantidade=obtemInteiro();

    if (id>idp[0]){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
    }
    else{
        produtos[id].qntd+=quantidade;
    }
    return produtos[id];

}

/* Funcao que adiciona um produto novo a matriz dos produtos em encomendas*/
Produto adicionaNovoProdutoEncomenda(int quantidade){
    int n,p;

    for(p=0;p<MAX_PRO_ENC;p++){
        if(produtos_encomendas[ids[0]][p].id==-1){ /* Se a posicao estiver livre adicona produto nessa posicao */
            produtos_encomendas[ids[0]][p].id=ids[1];
            produtos_encomendas[ids[0]][p].qntd=quantidade;
            produtos_encomendas[ids[0]][p].preco=produtos[ids[1]].preco;
            produtos_encomendas[ids[0]][p].peso=produtos[ids[1]].peso;
            for(n=0; produtos[ids[1]].descricao[n]!='\0';n++){
                produtos_encomendas[ids[0]][p].descricao[n]=produtos[ids[1]].descricao[n];
            }
            produtos_encomendas[ids[0]][p].descricao[n]='\0';
            break; /* Se adicionou sai do ciclo */
        }
    }
    return produtos_encomendas[ids[0]][p];
}

/* Funcao que adiciona quantidade a um produto ja existente numa encomenda*/
Produto adicionaProdutoExistenteEncomenda(int indice, int quantidade){
    produtos_encomendas[ids[0]][indice].qntd+=quantidade;

    return produtos_encomendas[ids[0]][indice];
}

/* Funcao que remove um produto da matriz dos produtos em encomendas*/
Produto removeProdutoEncomenda(int id){
    produtos_encomendas[ids[0]][id].id=-1; /* Repoe o id de controlo */
    produtos_encomendas[ids[0]][id].qntd=0; /* Repoe todos os valores a 0 */
    produtos_encomendas[ids[0]][id].preco=0;
    produtos_encomendas[ids[0]][id].peso=0;

    return produtos_encomendas[ids[0]][id];
}

/* Funcao que remove stock a um produto no sistema */
Produto removeStock(){
    int id,quantidade;
    i[0]=2;
    id=obtemInteiro();
    i[0]++;
    quantidade=obtemInteiro();

    if (id>idp[0]){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id);
    }
    else if (quantidade>produtos[id].qntd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quantidade, id);
    }
    else{
        produtos[id].qntd-=quantidade;
    }
    return produtos[id];
}

/* Funcao que altera o preco de um produto no sistema */
Produto alteraPrecoProduto(int id, int preco){
    produtos[id].preco=preco;

    return produtos[id];
}

/* Funcao que altera o peso e custo de uma encomenda quando adicionado um produto */
Encomenda alteraEncomendaNovoProduto(int qntd){
    encomendas[ids[0]].peso+=qntd*(produtos[ids[1]].peso);
    encomendas[ids[0]].custo+=qntd*(produtos[ids[1]].preco);

    return encomendas[ids[0]];
}

/* Funcao que altera o peso e custo de uma encomenda quando retirado um produto*/
Encomenda alteraEncomendaRetiraProduto(int id){
    encomendas[ids[0]].peso-=(produtos_encomendas[ids[0]][id].qntd)*(produtos_encomendas[ids[0]][id].peso);
    encomendas[ids[0]].custo-=(produtos_encomendas[ids[0]][id].qntd)*(produtos_encomendas[ids[0]][id].preco);

    return encomendas[ids[0]];
}

/* Funcao que lista a descricao e quantidade de um produto numa encomenda */
void listaE(){

    int p, cont=0;
    Produto produto;
    i[0]=2;
    ids[0]=obtemInteiro();
    i[0]++;
    ids[1]=obtemInteiro();

    if (ids[0]>ide[0]){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ids[0]);
    }
    else if (ids[1]>idp[0]){
        printf("Impossivel listar produto %d. Produto inexistente.\n",ids[1]);
    }
    else{
        for(p=0; p<MAX_PRO_ENC; p++){
            if(produtos_encomendas[ids[0]][p].id==ids[1]){ /* Quando encontrar o produto com o idp introduzido */
                produto=produtos_encomendas[ids[0]][p];
                cont=1; /* Ativa o controlo -> Produto esta na encomenda */
                break;
            }
        }
        if(cont!=1){ /* Produto nao esta na encomenda -> Vai buscar descricao ao sistema */
            printf("%s 0.\n", produtos[ids[1]].descricao);
        }
        else{
            printf("%s %d.\n", produto.descricao,produto.qntd);
        }
    }
}

/* Funcao que diz qual a encomenda onde o produto esta em maior quantidade */
void maximoProduto(){
    int e,maior_qntd=0,maior_id=0,id,p;
    i[0]=2;
    id=obtemInteiro();

    if(id>idp[0]){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id);
    }
    else{
        for(e=0;e<MAX_ENC;e++){ /* Percorre todas as encomendas e produtos */
            for(p=0;p<MAX_PRO_ENC;p++){
                if(produtos_encomendas[e][p].id==id && produtos_encomendas[e][p].qntd>maior_qntd){ /* Quando encontra o produto confirma a quantidade */
                    maior_qntd=produtos_encomendas[e][p].qntd;
                    maior_id=e;
                }
            }
        }

        if(maior_qntd!=0 && ide[0]!=-1){ /* Se o produto estiver em alguma encomenda e se houver alguma encomenda */
            printf("Maximo produto %d %d %d.\n",id,maior_id,maior_qntd);
        }
    }
}

/* Funcao que lista todos os produtos de uma encomenda por ordem alfabetica */
void listaL(){
    int id,comp=0,p;
    int z=0; /* Variavel auxiliar para nao deixar "espacos em branco" no vetor */
    i[0]=2;
    id=obtemInteiro();

    if (id>ide[0]){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id);
    }
    else{
        printf("Encomenda %d\n", id);
        for(p=0;p<MAX_PRO_ENC;p++){ /* Copia os produtos da encomenda para um vetor auxiliar */
            produtos_ordena[p].id=-1; /* Inicializar o id para controlo */
            if(produtos_encomendas[id][p].id!=-1){
                produtos_ordena[z]=produtos_encomendas[id][p];
                comp++; /*Incrementa o controlo do numero de produtos no vetor auxiliar */
                z++;
            }
        }

        if(comp==1){ /*Se so houver um produto na encomenda -> Imprime esse produto */
            printf("* %s %d %d\n",produtos_ordena[0].descricao,produtos_ordena[0].preco,produtos_ordena[0].qntd);
        }
        else{ /* Se hover mais de um produto -> Ordena */
            bubbleD(produtos_ordena,0,comp-1);

            for(p=0;p<comp;p++){
                printf("* %s %d %d\n",produtos_ordena[p].descricao,produtos_ordena[p].preco,produtos_ordena[p].qntd);
            }
        }
    }
}

/* Funcao que lista todos os produtos do sistema por ordem de preco */
void listal(){
    int p;

    printf("Produtos\n");

    for(p=0;p<=idp[0];p++){ /* Copia os produtos do sistema para um vetor auxiliar */
        produtos_ordena[p]=produtos[p];
    }

    quicksortP(produtos_ordena,0,idp[0]);

    for(p=0;p<=idp[0];p++){
        printf("* %s %d %d\n", produtos_ordena[p].descricao,produtos_ordena[p].preco,produtos_ordena[p].qntd);
    }
}

/* Funcao principal */
int main(){

    char letra; /* Variavel que vai ter o comando */
    int n,p;

    /* Inicializacao de valores */
    for (n=0;n<MAX_ENC;n++){
        for (p=0;p<MAX_PRO_ENC;p++){
            produtos_encomendas[n][p].id=-1;
            produtos_encomendas[n][p].qntd=0;
            produtos_encomendas[n][p].peso=0;
            produtos_encomendas[n][p].preco=0;
        }
    }


    obtemComando(); /* Le a primeira linha e guarda num vetor 'comando' */
    letra=comando[0]; /* Vai buscar a letra e guarda na variavel */

    while (letra!='x'){ /* Enquanto a letra nao for 'x' o programa e executado */

        if (letra =='a'){
            idp[0]++; /* Foi adicionado um novo produto -> id passa para o seguinte */
            produtos[idp[0]]=adicionaProduto(); /* Guarda o produto no vetor no indice igual ao id */
            printf("Novo produto %d.\n",idp[0]);
        }

        else if (letra =='q'){
            adicionaStock();
        }

        else if (letra=='N'){
            ide[0]++; /* Foi adicionada uma nova encomenda -> id passa para o seguinte */
            encomendas[ide[0]].custo=0; /* Inicializacao de variaveis */
            encomendas[ide[0]].peso=0;

            printf("Nova encomenda %d.\n",ide[0]);
        }

        else if (letra=='A'){
            int quantidade, cont=0;
            i[0]=2;
            ids[0]=obtemInteiro(); /* ide introduzido */
            i[0]++;
            ids[1]=obtemInteiro(); /* idp introduzido */
            i[0]++;
            quantidade=obtemInteiro();

            if(ids[0]>ide[0]){
                printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", ids[1],ids[0]);
            }
            else if (ids[1]>idp[0]){
                printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", ids[1],ids[0]);
            }
            else if (produtos[ids[1]].qntd<quantidade){
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", ids[1],ids[0]);
            }
            else if (encomendas[ids[0]].peso+ quantidade*produtos[ids[1]].peso >MAX_PESO){
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", ids[1],ids[0]);
            }
            else{
                for(p=0;p<MAX_PRO_ENC;p++){
                    if (produtos_encomendas[ids[0]][p].id==ids[1]){ /* Se ja havia um produto com o id introduzido */
                        adicionaProdutoExistenteEncomenda(p, quantidade);
                        cont=1; /* Aciona o controlo -> Produto ja la estava */
                    }
                }
                if (cont!=1){ /* Cont=0 -> Adiciona produto novo */
                    adicionaNovoProdutoEncomenda(quantidade);
                }

                alteraEncomendaNovoProduto(quantidade);

                produtos[ids[1]].qntd-=quantidade; /* Retira quantidade ao produto no sistema */
            }
        }    

        else if (letra=='r'){
            removeStock();
        }

        else if (letra=='R'){
            i[0]=2;

            ids[0]=obtemInteiro();
            i[0]++;
            ids[1]=obtemInteiro();

            if (ids[0]>ide[0]){
                printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", ids[1], ids[0]);
            }
            else if (ids[1]>idp[0]){
                printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", ids[1], ids[0]);
            }
            else{

                for(p=0;p<MAX_PRO_ENC; p++){
                    if (produtos_encomendas[ids[0]][p].id==ids[1]){ /* Quando encontra o produto com o id introduzido */
                        alteraEncomendaRetiraProduto(p); /* Retira peso e custo a encomenda */
                        produtos[ids[1]].qntd+=produtos_encomendas[ids[0]][p].qntd; /* Adiciona ao sistema o stock que estava na encomenda */
                        removeProdutoEncomenda(p);
                        break;
                    }
                }
            }
        }

        else if (letra=='C'){
            int id;
            i[0]=2;
            id=obtemInteiro();

            if (id>ide[0]){
                printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id);
            }
            else{
                printf("Custo da encomenda %d %d.\n",id,encomendas[id].custo);
            }
        }

        else if(letra=='p'){

            int id, novo_preco, e, p;
            i[0]=2;
            id=obtemInteiro();
            i[0]++;
            novo_preco=obtemInteiro();

            if(id>idp[0]){
                printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
            }
            else{
                alteraPrecoProduto(id, novo_preco); /* Altera o preco dos produtos no sistema */

                for(e=0; e<MAX_ENC; e++){ /* Altera o preco dos produtos nas encomendas e o custo das encomendas*/
                    for(p=0; p<MAX_PRO_ENC; p++){
                        if(produtos_encomendas[e][p].id==id){ /* Se o produto estiver na encomenda */
                            encomendas[e].custo-=(produtos_encomendas[e][p].qntd)*(produtos_encomendas[e][p].preco); /* Tira o custo antigo da encomenda */
                            produtos_encomendas[e][p].preco=novo_preco; /* Altera o preco do produto na encomenda */
                            encomendas[e].custo+=(produtos_encomendas[e][p].qntd)*(produtos_encomendas[e][p].preco); /* Soma o custo novo da encomenda */
                        }
                    }
                }
            }
        }

        else if(letra=='E'){
            listaE();
        }

        else if(letra=='m'){
            maximoProduto();
        }

        else if(letra=='l'){
            listal();
        }

        else if(letra=='L'){
            listaL();
        }

        obtemComando();
        letra=comando[0];
    }

    return 0;
}