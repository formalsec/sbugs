#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
/*
Maximos e constantes utilizados
*/
#define IDENTIFICADORES 10000 /* Maximo de produtos diferentes em stock na loja*/
#define DESCRICAO 64 /*Tamanho maximo de caracteres da descricao (n-1) ex:64 -> 63 caracteres de descricao */
#define MAXENCOMENDAS 500 /*Numero maximo de encomendas diferentes*/
#define MAXPESO 200 /*Maximo de peso por encomenda*/

/*Estruturas utilizadas no programa*/
typedef struct produto{ /* Estrutura Produto representa 1 produto*/
    int identificador; /*Identificador do produtos*/
    char descricao[DESCRICAO]; /*Descricao do produto*/
    int preco; /*Preco do produto*/
    int peso; /*Peso do produto*/
    int quantidade; /*Quantidade do produto*/
} Produto;

typedef struct encomenda{ /*Estrutura Encomenda representa 1 encomenda*/
    Produto produto[MAXPESO]; /*Vetor de estruturas Produto na encomenda*/
    int prod_ids[MAXPESO]; /*Vetor de indices contem o id do produto+1 no mesmo indice em que este estah na encomenda*/
} Encomenda;

/*Variaveis globais do programa:*/
/*id_prod->id do produto a ser adicionado,id_enco->id da encomenda a ser adicionada*/
int id_prod = 0,id_enco = 0,sair = 0,inicio = 0; 
/*sair -> variavel de estado que ao ativar provoca a saida do programa, inicio -> ativa quando foi adicionado o produto de id 0 */

/*Sistema de armazenamento*/
Produto stockloja[IDENTIFICADORES];
Encomenda encomendas[MAXENCOMENDAS];
/*Lista de ids para ordenar*/
int lista_de_ids[IDENTIFICADORES];

/*Funcao do comando 'a' adiciona um produto ao sistema le do stdin a descricao,preco e quantidade do produto*/
void AdicionarProduto(){
    
    char descricao[DESCRICAO];
    int preco = 0,peso = 0,qtd = 0;
    getchar();/*eliminacao do espaco apos o comando*/
    scanf("%[^:]:%d:%d:%d",descricao,&preco,&peso,&qtd);
    /*Adicionar o produto e suas caracteristicas a estrutura do sistema*/
    strcpy(stockloja[id_prod].descricao,descricao);
    stockloja[id_prod].identificador = id_prod;
    stockloja[id_prod].preco = preco;
    stockloja[id_prod].peso = peso;
    stockloja[id_prod].quantidade = qtd;
    printf("Novo produto %d.\n",id_prod);
    id_prod++;
    if(id_prod == 0){
        inicio=1;       /*Quando o primeiro produto (id 0) ativa a variavel global "inicio"*/
    }
}

/*Funcao do comando 'q' adiciona stock de um produto ao sistema le do stdin o id do produto e a quantidade a adicionar*/
void AdicionarStock(){
    int nova_qtd = 0,id_do_prod = 0;
    getchar(); /*eliminacao do espaco apos o comando*/
    scanf("%d:%d",&id_do_prod,&nova_qtd);
    if (id_do_prod >= id_prod){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id_do_prod);
        return;
    }else{
        stockloja[id_do_prod].quantidade += nova_qtd;/*stock adicionado ao sistema*/
    }
    
}

/*Funcao do comando 'N' cria uma nova e escreve no stdout o seu id*/
void CriaEncomenda(){
    printf("Nova encomenda %d.\n",id_enco);
    id_enco++;
}

/*Funcao auxiliar que recebe o id de uma encomenda,uma quantidade e o id de um produto e verifica se a quantidade do produto
recebida pode ser adicionada a encomenda*/
int VerificaPeso(int id_e,int Quantidade,int id_p){
    int peso = 0,peso_novo = 0,cont;
    for(cont = 0;cont < MAXPESO;cont++){
        peso += (encomendas[id_e].produto[cont].peso * encomendas[id_e].produto[cont].quantidade);/*determinacao do peso atual da encomenda*/
    }
    peso_novo = Quantidade*stockloja[id_p].peso; /*peso da totalidade de produto a adicionar*/
    if ((peso+peso_novo)>MAXPESO){
        return 0;
    }
    return 1;
}

/*Funcao do comando 'A' que le do stdin o id de uma encomenda, o id de um produto e uma quantidade e adiciona um produto a uma encomenda*/
void AdicionaEncomenda(){
    int id_e,id_p,qtd,k,j,local;
    getchar(); /*eliminacao do espaco apos o comando*/
    scanf("%d:%d:%d",&id_e,&id_p,&qtd);
    local = id_p + 1; /*valor a encontrar no vetor de indices*/
    if (id_e >= id_enco)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_p,id_e);
        return;
    }else if (id_p >= id_prod && inicio == 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id_p,id_e);
        return;

    }else if (qtd > stockloja[id_p].quantidade){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id_p,id_e);
        return;

    }else if (!(VerificaPeso(id_e,qtd,id_p))){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_p,id_e);
        return;

    }else{
        /*Procura se o produto a adicionar ja esta na encomenda,adiciona-o e termina a funcao se estiver*/
        for(j = 0;j < MAXPESO;j++){ 
            if(encomendas[id_e].prod_ids[j] == local){
                encomendas[id_e].produto[j].quantidade += qtd;
                stockloja[id_p].quantidade -= qtd; /*retirar a quantidade adicionada do stock da loja*/
                return;
            }
        }
        /*Procura o primeiro "espaco" vazio na estrutura da encomenda e adiciona o produto e suas caracteristicas*/
        for(k = 0;k < MAXPESO;k++){
            if(encomendas[id_e].prod_ids[k] == 0){
                encomendas[id_e].prod_ids[k]= id_p + 1;
                encomendas[id_e].produto[k] = stockloja[id_p];
                encomendas[id_e].produto[k].quantidade = qtd;
                stockloja[id_p].quantidade -= qtd; /*retirar a quantidade adicionada do stock da loja*/
                return;
            }
        }
    }
}

/*Funcao do comando 'r' que le do stdin o id de um produto, e uma quantidade e remove stock de um produto do sistema*/
void RemoveStock(){
    int id_p,qtd;
    getchar();/*eliminacao do espaco apos o comando*/
    scanf("%d:%d",&id_p,&qtd);
    if (id_p >= id_prod){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id_p);
        return;
    }else if(stockloja[id_p].quantidade < qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,id_p);
        return;
    }else{
        stockloja[id_p].quantidade -= qtd;
    }


}

/*Funcao do comando 'R' que le do stdin o id de uma encomenda e de um produto e remove o produto da encomenda dada*/
void RemoverDaEncomenda(){
    int id_e,id_p,k,local;
    getchar();/*eliminacao do espaco apos o comando*/
    scanf("%d:%d",&id_e,&id_p);
    local = id_p+1;/*valor a encontrar no vetor de indices*/
    if (id_e >= id_enco){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id_p,id_e);
        return;
    }else if (id_p >= id_prod){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id_p,id_e);
        return;
    }else{
        for(k = 0;k < MAXPESO;k++){
            if(encomendas[id_e].prod_ids[k] == local){ /*A remocao do produto e suas carqacteristicas da encomenda*/
                stockloja[id_p].quantidade += encomendas[id_e].produto[k].quantidade;
                encomendas[id_e].produto[k].quantidade = 0;
                strcpy(encomendas[id_e].produto[k].descricao,"");
                encomendas[id_e].produto[k].peso = 0;
                encomendas[id_e].produto[k].preco = 0;
                encomendas[id_e].produto[k].identificador = 0;
                encomendas[id_e].prod_ids[k] = 0;
                return;
            }
        }
    }
   
}

/*Funcao do comando 'C' que le do stdin um id de uma encomenda ,calcula o seu custo e mostra no stdout */
void CalculaCusto(){
    int id_e,k,total=0;
    getchar();/*eliminacao do espaco apos o comando*/
    scanf("%d",&id_e);

    if (id_e >= id_enco){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id_e);
        return;
    }else{
        for(k = 0;k < MAXPESO;k++){
            total += encomendas[id_e].produto[k].preco * encomendas[id_e].produto[k].quantidade;
        }
        printf("Custo da encomenda %d %d.\n",id_e,total);
    }
}

/*Funcao do comando 'p' que le do stdin o id de um produto e um preco e altera o seu preco no stock e nas encomendas*/
void AlteraPreco(){
    int id_p,preco_novo,k,local,j;
    getchar();/*eliminacao do espaco apos o comando*/
    scanf("%d:%d",&id_p,&preco_novo);
    local = id_p+1;/*valor a encontrar no vetor de indices*/
    if (id_p >= id_prod){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id_p);
        return;
    }else{
        stockloja[id_p].preco = preco_novo;
        for(k = 0;k < MAXENCOMENDAS;k++){
            for(j = 0;j < MAXPESO;j++){
                if(encomendas[k].prod_ids[j] == local){
                    encomendas[k].produto[j].preco = preco_novo;
                }
            }
        }
    }
}

/*Funcao do comando 'E' que le do stdin o id de uma encomenda e de um produto e indica(stdout) o produto e a sua quantidade*/
void ListarQuantidade(){
    int id_e,id_p,k,local;
    getchar();/*eliminacao do espaco apos o comando*/
    scanf("%d:%d",&id_e,&id_p);
    local = id_p+1;/*valor a encontrar no vetor de indices*/
    if (id_e >= id_enco){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_e);
        return;
    }else if (id_p >= id_prod){
        printf("Impossivel listar produto %d. Produto inexistente.\n",id_p);
        return;
    }else{

        for (k = 0; k < MAXPESO; k++){
            if(encomendas[id_e].prod_ids[k] == local){
                printf("%s %d.\n",stockloja[id_p].descricao,encomendas[id_e].produto[k].quantidade);
                return;
            }   
        }
        printf("%s 0.\n",stockloja[id_p].descricao);/*Caso em que o produto nao se encontra na encomenda*/
    }
}

/*Funcao do comando 'm' que le do stdin o id de um produto e indica no stdout qual a encomenda em que este tem maior frequencia*/
void ListaMaiorFrequencia(){
    int id_p,k,j,local,maior = 0,lista[MAXENCOMENDAS],ultima_enc = 0,l;
    getchar();/*eliminacao do espaco apos o comando*/
    memset(lista,0,(id_enco)*sizeof(lista[0]));
    scanf("%d",&id_p);
    local = id_p + 1;/*valor a encontrar no vetor de indices*/
    if(id_p >= id_prod){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_p); 
        return;
    }else{
        if (id_enco == 0){
            return;
        }
        
        for (k = 0; k < id_enco; k++){
            for (j = 0; j < MAXPESO; j++){
                if(encomendas[k].prod_ids[j] == local){
                    lista[k] = encomendas[k].produto[j].quantidade; /*Lista a frequencia do produto em cada encomenda*/
                }
            }
        }
        for(l = 0; l < id_enco;l++){/*procura a maior frequencia e a sua posicao na lista = id da encomenda*/
            if(lista[l] > maior){
                ultima_enc = l;     
                maior = lista[l];
            }
        }
        if(maior != 0){
            printf("Maximo produto %d %d %d.\n",id_p,ultima_enc,maior);
        }
    }
}

/*Funcao auxiliar que aplica o algoritmo Merge Sort*/
void OrdenarProdutosMerge(int inicio_m, int fim) {
    
    int meio = (inicio_m + fim)/2,atual,i,interno1 = inicio_m,interno2 = meio + 1,lista_aux[IDENTIFICADORES];
    if (inicio_m == fim){
      return;
    }
  OrdenarProdutosMerge(inicio_m,meio);
  OrdenarProdutosMerge(meio+1,fim); 
    for (i = inicio_m; i <= fim; i++){
        lista_aux[i] = lista_de_ids[i];
    }
  
    for (atual = inicio_m; atual <= fim; atual++){
        if (interno1 == meio+1){

            lista_de_ids[atual] =  lista_aux[interno2++];

        }else if(interno2 > fim){ 
            
            lista_de_ids[atual] =  lista_aux[interno1++];

        }else if (stockloja[lista_aux[interno1]].preco <=  stockloja[lista_aux[interno2]].preco){ /*comparacao que rege a ordenacao da lista*/

            lista_de_ids[atual] =  lista_aux[interno1++];

        }else{

            lista_de_ids[atual] =  lista_aux[interno2++];

        } 
    }   
}

/*Funcao do comando 'l' que lista no stdout todos os produtos da loja e suas informacoes por ordem crescente do preco*/
void ListarStock(){
    int k,j;
    for(k = 0;k < id_prod;k++){
        lista_de_ids[k] = stockloja[k].identificador;
    }
    printf("Produtos\n");
    if (id_prod == 1){
        printf("* %s %d %d\n",stockloja[0].descricao,stockloja[0].preco,stockloja[0].quantidade);/*Caso apenas exista 1 produto no sistema*/
        return;
    }else if (id_prod > 1)
    {
        OrdenarProdutosMerge(0,id_prod-1);
        for(j = 0;j < id_prod;j++){
            printf("* %s %d %d\n",stockloja[lista_de_ids[j]].descricao,stockloja[lista_de_ids[j]].preco,stockloja[lista_de_ids[j]].quantidade);
        }
    }
}

/*Funcao do comando 'L' que lista no stdout todos os produtos de uma encomenda de que o id e lido do stdin por ordem alfabetica do nome dos produtos */
void ListarEncomenda(){
    int id_e,j,i,h,k,g,max = 0,lista_de_id[MAXPESO],aux,enc_zero = 0;
    char desc_aux[DESCRICAO][MAXPESO],temp[DESCRICAO];
    getchar();/*eliminacao do espaco apos o comando*/
    scanf("%d",&id_e);
    if(id_enco <= id_e){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_e);
        return;
    }else{
        for(k = 0;k < MAXPESO;k++){
            if(encomendas[id_e].prod_ids[k] != 0){
                lista_de_id[max] = k;
                strcpy(desc_aux[max],encomendas[id_e].produto[k].descricao);
                max++;
                i = k;
            }else{
                enc_zero++;
            }
        }
        printf("Encomenda %d\n",id_e);
        if(enc_zero == MAXPESO){
            return;
            }
        if(max == 1){
            printf("* %s %d %d\n",encomendas[id_e].produto[i].descricao,encomendas[id_e].produto[i].preco,encomendas[id_e].produto[i].quantidade);
            return;
        }
        for(h = 0;h < max-1;h++){   /*Algoritmo de ordenacao alfabetica*/
            for(j = 1;j < max;j++){
                if(strcmp(desc_aux[j-1],desc_aux[j]) > 0){
                    strcpy(temp,desc_aux[j-1]);
                    aux = lista_de_id[j-1];
                    strcpy(desc_aux[j-1],desc_aux[j]);
                    lista_de_id[j-1] = lista_de_id[j];
                    strcpy(desc_aux[j],temp);
                    lista_de_id[j] = aux;
                }
            }
        }

        for(g = 0;g < max;g++){
            if(encomendas[id_e].produto[lista_de_id[g]].preco != 0){
                printf("* %s %d %d\n",encomendas[id_e].produto[lista_de_id[g]].descricao,encomendas[id_e].produto[lista_de_id[g]].preco,encomendas[id_e].produto[lista_de_id[g]].quantidade); 
            }
        }
    }
}

/*Funcao principal do programa que le os comandos do stdin e executa todos os outros comandos(funcoes)*/
void Comando(){
    char comando;
    comando = getchar();
    switch (comando)
    {
    case 'a':
        AdicionarProduto();
        break;
    case 'q':
        AdicionarStock();
        break;
    case 'N':
        CriaEncomenda();
        break;
    case 'A':
        AdicionaEncomenda();
        break;
    case 'r':
        RemoveStock();
        break;
    case 'R':
        RemoverDaEncomenda();
        break;
    case 'C':
        CalculaCusto();
        break;
    case 'p':
        AlteraPreco();
        break;
    case 'E':
        ListarQuantidade();
        break;
    case 'm':
        ListaMaiorFrequencia();
        break;
    case 'l':
        ListarStock();
        break;
    case 'L':
        ListarEncomenda();
        break;
    case 'x':
        sair = 1;
        break;
    }

}
int main(){

    while(1){
        Comando();
        if (sair){ /*Verifica se deve sair do programa,ou seja se foi executado o comando 'x'*/
            break;
        }
    }
    return 0;
}
