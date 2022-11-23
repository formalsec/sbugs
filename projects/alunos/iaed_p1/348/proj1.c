#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_NOME 64                     /*numero maximo de caracteres da descricao do produto*/
#define MAX_PRODUTO 10000               /*numero maximo de produtos no sistema*/
#define MAX_PRODUTO_POR_ENCOMENDA 200   /*numero maximo de peso por encomenda*/
#define MAX_ENCOMENDA 500               /*numero maximo de encomendas*/


/*criada uma estrutura para armazenar as caracteristicas do produto*/
typedef struct prod{
        int preco;				
        int peso;
        int qtd;
        char descricao[MAX_NOME];
        int id;
}Produto;
/*criada uma estrutura para armazenar as caracteristicas da encomenda*/
typedef struct encomenda{
		struct prod p[MAX_PRODUTO_POR_ENCOMENDA];         /*produtos existentes na encomenda*/
		int contador;                                     /*indice do ultimo produto adicionado*/
		int ide;
}Encomenda;


int id = 0;						               /* variavel global que regista o id do ultimo produto criado*/		
int ide = 0;					               /* variavel global que regista o ide da ultima encomenda criada*/
Produto sistema[MAX_PRODUTO];                  /* criado um array(sistema) onde se guardam produtos*/
Encomenda encomendas[MAX_ENCOMENDA];           /* criado um array(encomendas) onde se guardam as encomendas*/

/*le do input,cria um produto e adiciona ao sistema*/
void cria_e_adiciona_produto(){             

    Produto new;           
    scanf(" %[^:]:%d:%d:%d", new.descricao, &new.preco, &new.peso, &new.qtd);
    new.id = id;
    sistema[id] = new;
    printf("Novo produto %d.\n",id);
    id++;
}

/*adiciona stock a um produto que ja existe no sistema*/
void adiciona_stock(){                                              
	int current_id;          
	int current_qtd;       

	scanf("%d:%d", &current_id, &current_qtd);
	if (current_id > id-1){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", current_id);
	}
    else 
	   sistema[current_id].qtd += current_qtd;
}

/*cria uma nova encomenda*/
void cria_nova_encomenda(){             
	Encomenda new;
	new.ide = ide;
	new.contador = 0;
	printf("Nova encomenda %d.\n", ide);
	encomendas[ide++] = new;
}

/*adiciona um produto a uma encomenda se este nao existir,
caso ja exista, adiciona a nova quantidade a quantidade existente*/
void adiciona_produto_encomenda(){              
    int current_peso = 0;
    int current_id;         
    int current_qtd;        
    int current_ide;        
    int existe = 0;
    int i;

    scanf(" %d:%d:%d", &current_ide, &current_id, &current_qtd);
    if (current_ide > ide-1){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",current_id, current_ide);
        return;
    }
    else if (current_id > id-1){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",current_id, current_ide);
        return;
    }
    else if (sistema[current_id].qtd < current_qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",current_id, current_ide);
        return;
    }
    for(i=0; i<encomendas[current_ide].contador;i++){
        current_peso += encomendas[current_ide].p[i].peso * encomendas[current_ide].p[i].qtd;
    }
    current_peso += sistema[current_id].peso * current_qtd;
    if(current_peso > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",current_id, current_ide);
        return;
    }
    /*verifica se o produto ja existe na encomenda*/
    for (i = 0; i < encomendas[current_ide].contador; i++){
        if (strcmp(sistema[current_id].descricao,encomendas[current_ide].p[i].descricao)==0){
            existe = i;
        }
    }
    /*em qualquer um dos casos, a quantidade do produto e adicionada a encomenda e retirada do sistema*/
    if (existe != 0){
        encomendas[current_ide].p[existe].qtd += current_qtd;
        sistema[current_id].qtd -= current_qtd;
    }
    else{
        encomendas[current_ide].p[encomendas[current_ide].contador] = sistema[current_id];
        encomendas[current_ide].p[encomendas[current_ide].contador].qtd = current_qtd;
        sistema[current_id].qtd -= current_qtd;
        encomendas[current_ide].contador++;
    }
}

/*remove stock a um produto existente*/
void remove_stock(){                    
    int current_id;         
    int current_qtd;        

	scanf("%d:%d", &current_id, &current_qtd);

    if (current_id > id-1){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", current_id);
    }
    else if (current_qtd > sistema[current_id].qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",current_qtd, current_id);
    }
    else{
        sistema[current_id].qtd -= current_qtd;     
    }
}

/*remove um produto de uma encomenda*/
void remove_produto_encomenda(){           
    int current_ide;
    int current_id;
    int i;

	scanf("%d:%d", &current_ide, &current_id);
    if (current_ide > ide-1){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",current_id, current_ide);
    }
    if (current_id > id-1){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", current_id, current_ide);
    }
    else{
        /*percorre a encomenda a procura do produto e remove caso este exista*/
        for(i = 0; i < encomendas[current_ide].contador; i++){
            if(strcmp(sistema[current_id].descricao,encomendas[current_ide].p[i].descricao)==0){
                sistema[current_id].qtd += encomendas[current_ide].p[i].qtd;
                encomendas[current_ide].p[i].qtd = 0;
                encomendas[current_ide].contador--;
                return;   
            }
        }
    }
}

/*calcula o custo de uma encomenda*/
void calcula_custo_encomenda(){             
    int current_ide;
    int total=0;
    int i;

    scanf("%d", &current_ide);
    if (current_ide > ide-1){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",current_ide);
    }
    else{
        for(i=0; i < encomendas[current_ide].contador; i++){
                total += encomendas[current_ide].p[i].preco * encomendas[current_ide].p[i].qtd;   
        }
        printf("Custo da encomenda %d %d.\n",current_ide,total); 
    }
}

/*altera o pre?o de um produto existente no sistema*/
void altera_preco_produto_no_sistema(){            
    int current_id;
    int current_preco;
    int i;
    int j;

    scanf("%d:%d", &current_id, &current_preco);
    if(current_id > id-1){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",current_id);
    }
    else{
        /*percorre todas as encomendas a procura do produto e altera o preco se este existir*/
        for(i=0; i<ide; i++){
            for(j=0; j<encomendas[i].contador; j++){
                if(strcmp(sistema[current_id].descricao, encomendas[i].p[j].descricao)==0){
                    encomendas[i].p[j].preco = current_preco;
                }
            }
        }
        sistema[current_id].preco = current_preco;
    }
}

/*retorna a descricao e a quantidade de um produto numa encomenda*/
void retorna_descricao_e_quantidade_de_produto_na_encomenda(){   
    int current_id;
    int current_ide;
    int i;
    int current_qtd=0;



    scanf("%d:%d", &current_ide, &current_id);
    if (current_ide > ide-1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",current_ide);
    }
    else if (current_id > id-1){
        printf("Impossivel listar produto %d. Produto inexistente.\n",current_id);
    }
    else{
        /*procura o produto na encomenda e regista a quantidade caso ele exista*/
        for(i=0; i < encomendas[current_ide].contador; i++){
            if(strcmp(sistema[current_id].descricao,encomendas[current_ide].p[i].descricao)==0){
                current_qtd = encomendas[current_ide].p[i].qtd;
            }
        }
        printf("%s %d.\n",sistema[current_id].descricao, current_qtd);
    }
}

/*lista o identificador da encomenda em que o produto dado ocorre mais vezes,
caso hajam duas ou mais encomendas nesta situcao,vai imprimir a encomenda com menor id*/
void retorna_id_encomenda_ocorre_mais_vezes(){          
    int current_id;
    int maximo=0;
    int current_ide;
    int i;
    int j;

    scanf("%d", &current_id);
    if(current_id > id-1){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",current_id);
    }
    else{
        /*procura o produto em todas as encomendas e verifica se a ocorrencia e maior do que a
        que esta guardada*/
        for(i=0; i < ide; i++){
            for(j=0; j < encomendas[i].contador; j++){
                if(strcmp(sistema[current_id].descricao,encomendas[i].p[j].descricao)==0 && encomendas[i].p[j].qtd > maximo){
                    maximo = encomendas[i].p[j].qtd;
                    current_ide = i;
                }
            }
        }
        if (maximo != 0)
            printf("Maximo produto %d %d %d.\n", current_id,current_ide,maximo);
    }
}

/*lista todos os produtos existentes no sistema por ordem crescente de preco,caso hajam dois
 ou mais produtos com o mesmo preco, vai imprimir por ordem crescente de id de produto*/
void lista_produtos_ordem_crescente_preco(){        
    int i;
    Produto aux;
    Produto copia[MAX_PRODUTO];
    int contador;
    /*cria uma copia para reservar o array original*/
    for(i=0; i<id; i++){
        copia[i] = sistema[i];
    }
    /*algoritmo bubblesort utilizado em aula*/
    for (contador=0; contador < id ;contador++){
        for (i=0; i < id-contador -1; i++){
            if (copia[i].preco > copia[i+1].preco){
                aux = copia[i];
                copia[i] = copia[i+1];
                copia[i+1] = aux;
            }
        }
    }
    printf("Produtos\n");
    for(i=0; i<id; i++){
        printf("* %s %d %d\n", copia[i].descricao, copia[i].preco, copia[i].qtd);
    }
}

/*lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
void lista_produtos_encomenda_ordem_alfabetica(){           
    int current_ide;
    int i;
    Produto aux;
    Produto copia[MAX_PRODUTO_POR_ENCOMENDA];
    int contador;

    scanf("%d", &current_ide);
    if(current_ide > ide-1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",current_ide);
    }
    else{
        /*cria uma copia para reservar o array original*/
        for(i=0; i<encomendas[current_ide].contador; i++){
            copia[i] = encomendas[current_ide].p[i];
        }
        /*algoritmo bubblesort utilizado em aula*/
        for (contador=1; contador < encomendas[current_ide].contador ;contador++){
            for (i=0; i < encomendas[current_ide].contador-contador; i++){
                if (strcmp(copia[i].descricao, copia[i+1].descricao)>0){
                    aux = copia[i];
                    copia[i] = copia[i+1];
                    copia[i+1] = aux;
                }
            }
        }
        printf("Encomenda %d\n", current_ide);
        for(i=0; i<encomendas[current_ide].contador ; i++){
            printf("* %s %d %d\n", copia[i].descricao, copia[i].preco, copia[i].qtd);
        }
    }
}

int main(){
	char comando;         

	while(comando!='x'){					
		comando = getchar();
        /*le a letra do input e chama a respetiva funcao*/
		switch (comando) {
        	case 'a':
        	cria_e_adiciona_produto();
        		break;
        	case 'q':
        	adiciona_stock();
            	break;
        	case 'N':
        	cria_nova_encomenda();
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
        	calcula_custo_encomenda();
            	break;
        	case 'p':
        	altera_preco_produto_no_sistema();
            	break;
        	case 'E':
        	retorna_descricao_e_quantidade_de_produto_na_encomenda();
            	break;
        	case 'm':
        	retorna_id_encomenda_ocorre_mais_vezes();
            	break;
        	case 'l':
        	lista_produtos_ordem_crescente_preco();
            	break;
        	case 'L':
        	lista_produtos_encomenda_ordem_alfabetica();
            	break;
        	case 'x':
            	break;
        }
    }
    return 0;
}
