#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "produto.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_BUFFER 256
#define SIZE 9999
#define SIZEE 500

/*Definir variaveis globais*/
typedef unsigned char bool;
//enum { false = 0, true = 1 };
int id = -1;
int ide = -1;
Produto lista_produtos[SIZE];
Produto lista_aux_produtos[SIZE];
Produto aux_produtos[SIZE];
Encomenda lista_encomenda[SIZEE];

/*Adicionar produto ao vetor de produtos
varivael id inicializada a -1 e automaticamente incrementada no inicio da funcao de maneira a poder comecar a 0
id do produto corresponde tambem ao index no vetor de produto.
Recebemos os dados por input do command line e distribuimos pelos atributos do produto*/

void adiciona(char * frase){
    Produto produto;
    int i = 0;
    int dados[3];
    id++;
    lista_produtos[id].produto_id = id;
    memset(&produto, 0, sizeof(Produto));
    
    frase = strtok(frase, ":");
    if(strlen(frase)>=63){
        return;
        
    }
    strcpy(lista_produtos[id].descricao, frase);
    

    while(i < 3){
        dados[i++] = atoi(strtok(NULL, ":"));
    } i=0;
    lista_produtos[id].preco = dados[0];
    lista_produtos[id].peso = dados[1];
    lista_produtos[id].stock = dados[2];




    printf("Novo produto %d.\n", lista_produtos[id].produto_id);
}

/*Adiciona stock ao produto
percorremos o vetor de produtos ate encontrar o id correspondente ao valor que queremos (dado por input) e
adicionamos o stock dado por input.
Caso o produto nao exista e retornada mensagem de erro*/

void adiciona_stock(char * frase){
    int i = 0;
    int m = 0;
    int j;
    int n=-1;

    frase = strtok(frase, ":");
    m = atoi(frase);


    j = atoi(strtok(NULL, ":"));
 
  
    
    
    for(i = 0; i <= id; i++){
       
        if(lista_produtos[i].produto_id == m){
            lista_produtos[i].stock += j; 
            n = j;
            break;
        }
    }

    if(n == -1){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", m);
        
    }
    
}

/*Executado o mesmo processo para adicionar o produto
ide iniciado a -1 e incrmentado logo no inicio da funcao
o ide da encomenda corresponde ao index dessa encomenda no vetor de encomendas*/

void cria_encomenda(){
    Encomenda encomenda;
    ide ++;
    encomenda.encomenda_id = ide;
    encomenda.encomenda_peso = 0;
    lista_encomenda[ide] = encomenda;

    
    printf("Nova encomenda %d.\n", ide);
}

/*Funcao auxiliar criada para verificar se uma encomenda existe
Recebe um id referente ao id de uma encomenda e a sua posicao no vetor de encomendas
percorre o vetor e se encontrar a encomenda pedida retorna 1
caso contrario retorna 0*/

int auxilia_encomenda(int m){
    int n,j= 0;
    for(n = 0; n <= ide; n++){
        if(lista_encomenda[n].encomenda_id == m){
            j++;
            break;
        }
    }
    if(j == 1){
        return 1;
    }
    else{
        return 0;
    }
}

/*Funcao para verificar se um dado produto existe numa dada encomenda.
Recebe como input o id da encomenda e o id do produto.
Percorre o vetor de produtos que se enonontra na encomenda especificada.
Se encontrar o produto retorna 1. Caso contrario retorna 0.*/

int auxilia_produto(int m, int i){
    int n, j = 0;

    for(n = 0; n <= id; n++){
        if(lista_encomenda[m].encomenda_produto[n].produto_id == i){
            j = n;
        }

    }

    if(j >= 0){
        return 1;
    }
    else{
        return 0;
    }
}

/*Funcao auxiliar para verificar se um produto existe.
Percorre o vetor de protudos e verifica se o produto dado como output existe.
Se encontrar o produto retorna 1. Caso contrario retorna 0.*/

int existe_produto(int m){
    int n = 0;
    for(n = 0; n<=id; n++){
        if(lista_produtos[n].produto_id == m){
            return 1;
        }
    }

    return 0;
}

/*Funcao auxiliar que verifica se existe produto em stock de um determinado produto
e que tambem compara se um valor dado por input e maior que o stock existente.
Uma vez que esta funcao e usada para verificar se se pode retirar stock de um produto.
E dado como input o valor a retirar do tock e o id do respetivo produto.
Caso se verifiquem as condicoes acima retorna o valor em stock, caso contarrio retorna 0.*/

int auxilia_stock(int n, int m){
    int j = 0;
    
    
    if(lista_produtos[n].stock >= m && lista_produtos[n].stock > 0){
        j = lista_produtos[n].stock;

    }
    
    
    if(j > 0){
        return j;
    }
    else{
        return 0;
    }
}

/*Funcao que adiciona um produto a uma encomenda. Recebe de input o id da encomenda, do produto e a quantidade de produto a adicionar.
Sao verificadas todas as condicoes necessarias atraves das funcoes auxiliares referidas acima, e tambem atraves de uma condicao que 
verifica se o peso da encomenda nao vai ultrapassar o valor permitido, caso alguma retorne 0,
sao imprimidas as mensagens de erro correspondentes as condicoes nao verificadas.
Caso contrario, se o produto ja existe no vetor de produtos da encomenda, adicionamos a quantidade de produto a encomenda
adicionamos o peso correspondente a esta quandtidade a encomenda, e diminuimos a quantidade de produto em stock.
Caso o produto nao exista na encomenda, faz se exatamente o mesmo que foi feito em cima, mas tambem copiamos o produto existente
para a encomenda, adicionando assim o produto a encomenda.*/

void adiciona_produto(char * frase){
    int m = 0;
    int i = 0;
    int dados[2];
    frase = strtok(frase, ":");
    m = atoi(frase);
    
    while(i < 2){
        dados[i++] = atoi(strtok(NULL, ":"));
    }i = 0;

    if(auxilia_encomenda(m)){
        if(existe_produto(dados[0])){
            if(auxilia_stock(dados[0],dados[1])){
                if((lista_encomenda[m].encomenda_peso + (lista_produtos[dados[0]].peso * dados[1])) <= 200){
                    if(auxilia_produto(m, dados[0])){ 
                        lista_produtos[dados[0]].stock -= dados[1];
                        lista_encomenda[m].encomenda_produto[dados[0]].stock += dados[1];
                        lista_encomenda[m].encomenda_peso += lista_produtos[dados[0]].peso * dados[1];
                        lista_encomenda[m].encomenda_produto[dados[0]].preco += lista_produtos[dados[0]].preco * dados[1];
                    }
                    else{
                        memcpy(&lista_encomenda[m].encomenda_produto[dados[0]], &lista_produtos[dados[0]], sizeof(Produto));
                        lista_encomenda[m].encomenda_produto[dados[0]].produto_id = dados[0];
                        lista_encomenda[m].encomenda_produto[dados[0]].preco = lista_produtos[dados[0]].preco * dados[1];
                        lista_produtos[dados[0]].stock -= dados[1];
                        lista_encomenda[m].encomenda_produto[dados[0]].stock += dados[1];
                        lista_encomenda[m].encomenda_peso += lista_produtos[dados[0]].peso * dados[1];

                    }
                }
                else{
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", dados[0], m);
                }

            }
            else{
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", dados[0], m);
            }
        }
                    
        
        else{
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", dados[0], m);
        }

        
    }
    
    else{
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", dados[0], m);
    }

}

/*Verifica se um dado produto existe, recebendo como input o id do produto*/

int auxilia_produto_stock(int m){
    int n;
    int j = -1;
    for(n = 0; n <= id; n++){
        if(lista_produtos[n].produto_id == m){
            j = n;
            break;
        }
    }
    return j + 1;
}

/*Funcao que remove a quantidade de produto existente num stock. Recebe de input o produto e a quantidade a ser retirada.
Usa-se a funcao auxilar para verificar se o produto dado existe e se tem stock suficiente para ser retirado, caso contrario retorna mensagem de erro.
Se o produto existir retira a quantidade dada do stock do produto especificado.
Acedendo ao vetor de produtos no index correspondente ao id dado via input.*/

void remove_stock(char * frase){
    int m, j = 0;
    int p = 0;


    frase = strtok(frase, ":");
    m = atoi(frase);


    j = atoi(strtok(NULL, ":"));

    if(auxilia_produto_stock(m)){
        p = auxilia_produto_stock(m) - 1;
        if(lista_produtos[p].stock >= j){
            lista_produtos[p].stock = lista_produtos[p].stock - j;
            
        }
        else{
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", j, m);
        }
    }
    
    else{
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", m);
    }

}

/*Funcao que remove um produto de uma encomenda, recebe de input a encomenda e o produto que vai ser retirado.
Faz as verificacoes todas ja referidas atraves de funcoes auxiliares (ver se a encomenda e o produto existem e se o produto existe na encomenda).
Se nao verificar as condicoes imprime as mensagens de erro, caso contrario define todos os elementos do produto a zero.*/

void remove_encomenda(char * frase){
    int m,j;
    frase = strtok(frase, ":");
    m = atoi(frase);


    j = atoi(strtok(NULL, ":"));
    if(auxilia_encomenda(m)){
        if(existe_produto(j)){
            if(auxilia_produto(m,j)){
                lista_encomenda[m].encomenda_produto[j].peso = 0;
                lista_encomenda[m].encomenda_produto[j].preco = 0;
                lista_encomenda[m].encomenda_produto[j].stock = 0;
                lista_encomenda[m].encomenda_peso -= lista_encomenda[m].encomenda_produto[j].peso * lista_encomenda[m].encomenda_produto[j].stock;


            }

        }
        else{
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", j, m);
        }

    }
    else{
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", j, m);
    }

}


/*Funcao que recebe de input o id de uma encomenda.
Verifica se a encomenda existe com a ajuda de uma funcao auxiliar, caso contrario imprime a mensagem de erro.
Se a encomenda existir, usamos a funcao auxiliar para verificar se o produto existe na encomenda dada.
Caso existe adicionamos o preco desse produto na encomenda a variavel criada no inicio da funcao e inicializada a 0.
Depois de se verificar todos os produtos existentes e de verificar aqueles que existem na encomenda,
imprime -se a variavel custo.
 */

void calcula_custo(char * frase){
    int m, n= 0;
    int custo = 0;

    frase = strtok(frase, ":");
    m = atoi(frase);
    if(auxilia_encomenda(m)){
        for(n = 0; n <= id; n++){ /*nao preciso deste ciclo, posso apagar*/
            if(auxilia_produto(m,n)){
                custo += lista_encomenda[m].encomenda_produto[n].preco;
            }
        }
        printf("Custo da encomenda %d %d.\n", m, custo);
    }
    else{
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", m);
    }
}

/*Funcao que altera o preco de um produto, recebe por input o id do produto e o valor de preco a alterar.
Verifica se o produto existe com a ajuda da funcao auxiliar, caso contrario imprime a mensagem de erro.
Caso o produto exista, igualamos o preco desse produto a variavel dada por input.
Posto isto temos tambem de mudar o preco deste produto nas encomendas em que ele se encontra.
Percorremos entao o vetor de encomendas e procuramos o produto, caso este exista, igualamos o seu preco ao valor dado por input. */

void altera_preco(char * frase){
    int m, j, n= 0;

    frase = strtok(frase, ":");
    m = atoi(frase);


    j = atoi(strtok(NULL, ":"));

    if(existe_produto(m)){
        lista_produtos[m].preco = j;
        for(n = 0; n <= ide; n++){
            if(lista_encomenda[n].encomenda_produto[m].produto_id >= 0){
                lista_encomenda[n].encomenda_produto[m].preco = j;
            }
        }
    }
    else{
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", m);
    }
    
}

/*Funcao responsavel por listar a descrciao e a quantidade em stock de um produto na encomenda, valores dados por input.
Primeiro verifica se encomenda dada existe, se o produto dado existe, e se este existe dentro da encomenda. Caso os dois primeiros retornem falso
sao imprimidas as mensagens de erro. Caso o produto exista na encomenda, sao imprimidos a sua descricao e quantidade em stock.*/

void lista_descricao(char * frase){
    int m, j = 0;

    frase = strtok(frase, ":");
    m = atoi(frase);


    j = atoi(strtok(NULL, ":"));
    if(auxilia_encomenda(m)){
        if(existe_produto(j)){
            if(auxilia_produto(m,j)){
                printf("%s %d\n", lista_produtos[j].descricao, lista_encomenda[m].encomenda_produto[j].stock);
            }
        }
        else{
            printf("Impossivel listar produto %d. Produto inexistente.\n", j);
        }
    }
    else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", m); /*verificar os printfs, podem nao estar de acordo com o output pedido*/
    }
}

/*Funcao que lista o id da encomenda em que o produto dado ocorre mais vezes.
Primeiro criamos uma varivel com valor 0 e depois verificamos se o produto dado existe. Caso contrario
imprime mensagem de erro. Se o produto existir, percorremos o vetor de encomendas
em que o produto existe everificamos se a sua quantidade em stock e maior que 0
e se o seu valor e maior que a variavel counter, desta forma garantimos que ele vai sempre guardar o menor id de encomenda.
Posto isto guaradamos a quantidade em stock do produto no counter e o id da encomenda que queremos noutra variavel.
No fim imprime se o id do produto, da encomendda e o valor em stock do produto.*/

void lista_ocorrencia(char * frase){
    int m, j,l, counter = 0;

    frase = strtok(frase, ":");
    m = atoi(frase);

    if(existe_produto(m)){
        for( j = 0; j<=ide; j++){
            if(lista_encomenda[j].encomenda_produto[m].stock > 0 && lista_encomenda[j].encomenda_produto[m].stock > counter){
                counter += lista_encomenda[j].encomenda_produto[m].stock;
                l = j;

            }
        }

        if(counter == 0){
            return;
        }
        else{
             printf("Maximo produto %d %d %d.\n", m, l, counter);
        }
       
    }
    else{
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", m);
    }
}
/*void merge_aux_produtos(int l, int m, int h){
    int i, n, j = 0;
    for (n = l; n <= h; n++){
        memcpy(&aux_produtos[n], &lista_aux_produtos[n], sizeof(Produto));
    }
    n = l;
    i = m + 1;
    j = l;

    while(n <= m && i <= h){
        if(aux_produtos[n].preco < aux_produtos[i].preco){
            lista_aux_produtos[j].produto_id = aux_produtos[n].produto_id;
            lista_aux_produtos[j].peso = aux_produtos[n].peso;
            lista_aux_produtos[j].stock = aux_produtos[n].stock;
            lista_aux_produtos[j].preco = aux_produtos[n].preco;
            strcpy(lista_aux_produtos[j].descricao, aux_produtos[n].descricao);
            n++;
        }

        else{
            lista_aux_produtos[j].produto_id = aux_produtos[i].produto_id;
            lista_aux_produtos[j].peso = aux_produtos[i].peso;
            lista_aux_produtos[j].stock = aux_produtos[i].stock;
            lista_aux_produtos[j].preco = aux_produtos[i].preco;
            strcpy(lista_aux_produtos[j].descricao, aux_produtos[i].descricao);
            i++; 
        }
        j++;
    }
    while(n <= m){
        lista_aux_produtos[j] = aux_produtos[n];
        lista_aux_produtos[j].peso = aux_produtos[n].peso;
        lista_aux_produtos[j].stock = aux_produtos[i].stock;
        lista_aux_produtos[j].preco = aux_produtos[i].preco;
        strcpy(lista_aux_produtos[j].descricao, aux_produtos[i].descricao);
        j++;
        n++;
    }
}

void merge_preco(int l, int h){
    int m = 0;
    if(l < h){
        m = (l + h) / 2;
        merge_preco(l, m);
        merge_preco(m + 1, h);
        merge_aux_produtos(l, m, h);
    }
}

void listar_produtos(){
    int n = 0;
    for(n = 0; n <= id; n++){
        memcpy(&lista_aux_produtos[n], &lista_produtos[n], sizeof(Produto));
    }
     merge_preco(0 , id);
     for(n = 0; n <= id; n++){
         if(lista_aux_produtos[n].preco > 0){
             printf("* %s %d %d\n", lista_aux_produtos[n].descricao, lista_aux_produtos[n].preco, lista_aux_produtos[n].stock);
         }
     }
}

void listar_encomenda(char * frase){
    int m = 0;

    frase = strtok(frase, ":");
    m = atoi(frase);

    if(auxilia_encomenda(m)){
        
    }
}*/

int main() {
	bool loop = 1;
	char command;
	char input[TAM_BUFFER];

	while (loop){
		/* buscar comando do input e removendo o \n */
		fgets(input, TAM_BUFFER, stdin);
        /*input[strlen(input)-1] = 0;*/
		command = input[0];

		switch(command){
			case 'a': /*chama a fun??o que adiciona eventos, comando a*/
				adiciona(input + 2);
				break;
            case 'q':
                adiciona_stock(input + 2);
                break;
            case 'N':
                cria_encomenda(input);
                break;
            case 'A':
                adiciona_produto(input + 2);
                break;
            case 'r':
                remove_stock(input + 2);
                break;
            case 'R':
                remove_encomenda(input + 2);
                break;
            /*case 'l':
                listar_produtos();
                break;*/
            case 'C':
                calcula_custo(input + 2);
                break;
            case 'p':
                altera_preco(input +2);
                break;
            case 'E':
                lista_descricao(input + 2);
                break;
            case 'm':
                lista_ocorrencia(input + 2);
                break;
            /*case 'L':
                listar_encomenda(input);
                break;*/
            case 'x':
                return 0;





		}
	}

	return 0;
}
