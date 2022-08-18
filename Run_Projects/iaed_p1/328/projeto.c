#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define tamanho_descricao 65
#define nr_produtos 10001
#define nr_encomendas 501
#define max_command_size 300
char comando[max_command_size];  /* usado para guardar o ultimo comando */
char *ptr_comando = comando + 2;	/* usado como pointer para os valores do comando */
char *ptr_novo_comando = comando;	/* usado para reiniciar o pointer */
char char_aux[max_command_size];	/* string auxiliar */
int i = 0; 							/* var aux usada para varias coisas */
int maior;						
int lista[11000][tamanho_descricao + 3];
int ult_valor = 0;
int aux_main[tamanho_descricao + 3];
int b = 0;						
int var_aux = 0;					/* variaveis auxiliares usadas no heapsort */
int len;						/* usada para dizer o nr de variaveis relevantes no heapsort */

int extrai_nr()  /* extrai o numero no comando ate aos : */
		{
		i = 0;
		while(ptr_comando[0] != ':' && ptr_comando[0] != '\0')
			{
			char_aux[i] = ptr_comando[0];
			ptr_comando += 1;
			i += 1;
			}
		char_aux[i] = '\0';
		i = 0;
		return atoi(char_aux);
		}

int parent(int k){		/* funcao que devolve o indice do pai do indice k (relacionado com o heapsort) */
    return ((k+1)/2)-1;
}
int left(int k){		/* funcao que devolve o indice do elemento a esquerda do k (relacionado com o heapsort) */
    return (k * 2) + 1;
} 
int right(int k){	/* funcao que devolve o indice do elemento a direita do k (relacionado com o heapsort) */
    return k * 2 + 2;
}
void fixdown(){				                /* faz o fixdown do elemento de indice i */
    static int aux[tamanho_descricao + 3];	/* var usada para trocar elementos */
    if(left(i) > ult_valor){
        return;		            /* verifica se o left do indice i pertence a parte desordenada da lista */
    }			                /* se nao pertencer para ciclo de fixdown */
    maior = left(i);		    /* vou assumir que o valor da esquerda e o maior e verificar se isso e verdade */
    if(right(i) <= ult_valor){	/* o valor da direita esta na parte desordenada?*/
        if(lista[right(i)][0] > lista[left(i)][0])	/* o primeiro valor(o mais prioritario) do da direita e maior que o da esquerda? */
        {
            maior = right(i);
        }
        if(lista[right(i)][0] == lista[left(i)][0])                         /* se forem iguais vamos ver elementos com menos prioridade */
        {
			var_aux = 1;
			while (lista[right(i)][var_aux] == lista[left(i)][var_aux])		/* encontra primeiros elementos diferentes*/
				{	
					var_aux += 1;}		
            if(lista[right(i)][var_aux] > lista[left(i)][var_aux]){		    /* ve qual e o maior */
                maior = right(i);
            }
        }}
    if(lista[i][0] > lista[maior][0]){		/* ve se o maior e maior que o valor que queremos dar fixdown da mesma forma que para o right e left */
        return;
    }		/* se o elemento que queremos far fixdown for o maior o ciclo de fixdown para */
    if(lista[i][0] == lista[maior][0])
			{
        	var_aux = 1;
			while (lista[i][var_aux] == lista[maior][var_aux])
				{var_aux += 1;
				}
			if(lista[i][var_aux] > lista[maior][var_aux])
				{            	
				return;					/* se o elemento que queremos far fixdown for o maior o ciclo de fixdown para */
            	}
    		}
	var_aux = 0;
	while(var_aux != len + 1)		/* troca o elemento que queremos fazer fixdown com o maior dos filhos */
		{
		aux[var_aux] = lista[i][var_aux];
		lista[i][var_aux] = lista[maior][var_aux];
		lista[maior][var_aux] = aux[var_aux];
		var_aux += 1;
		}
	
	var_aux = 0;
    i = maior;		/* fixdown continua no indice do maior filho */
    fixdown();
}
void buildheap() {
    static int aux_i;
    aux_i = (((ult_valor + 1) / 2) - 1); /* valor do ultimo pai */
    while(aux_i > 0){
        i = aux_i;			/* da fixdown de todos os pais, do menor para o maior criando um heap */
        fixdown();
        aux_i = aux_i - 1;
    }
    i = 0;
    fixdown();
    return;
}

typedef struct produto{			/* estrutura usada para os produtos */
	char descricao[tamanho_descricao];
	int preco;
	int peso;
	int qtd;
	int idp;
} produto;

typedef struct encomenda{	/* estrutura usada para as encomendas */
	int produto[nr_produtos];
	int peso;
	int preco;			/* o preco so e atualisado com o comando C */
} encomenda;

encomenda lista_encomendas[nr_encomendas]; /* inicializa a lista de encomendas */

int main(){
	int idf = 0;
	int ide = 0;
	int idf_produto;
	int stock;
	int idf_encomenda;
	produto lista_produtos[nr_produtos]; /* inicializa variaveis */
	scanf("%[^\n]", comando);      	/* ve o comando */
	while(comando[0] != 'x') {		/* no caso do primeiro valor do comando ser x o ciclo para */
		switch(comando[0]) {	/* consoante a primeira letra do comando faz: */
			case 'a': {		/* no caso do primeiro valor do comando ser a: */
				i = 0;
				while(ptr_comando[0] != ':' && i < 64) {
					lista_produtos[idf].descricao[i] = ptr_comando[0];
					i += 1;
					ptr_comando += 1;
				}		    /* ve a descricao */
				ptr_comando += 1;
				lista_produtos[idf].preco = extrai_nr();
				ptr_comando += 1;
				lista_produtos[idf].peso = extrai_nr();
				ptr_comando += 1;
				lista_produtos[idf].qtd = extrai_nr();
				printf("Novo produto %d.\n", idf);
				lista_produtos[idf].idp = idf;		/* obtem os valores como foi pedido no enunciado */
				idf += 1;					/* aumenta o idp do proximo produto */		
				break;
			}
			case 'q': {		/* no caso do primeiro valor do comando ser q: */
				idf_produto = extrai_nr();		/* obtem o idp do produto a q se pretende adicionar qnt*/
				if(idf_produto >= idf) {
					printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idf_produto);
					break;
				}
				ptr_comando += 1;
				lista_produtos[idf_produto].qtd += extrai_nr();		/* adiciona a qnt ao produto */
				break;
				}
				case 'N': {		/* no caso do primeiro valor do comando ser N: */
					lista_encomendas[ide].peso = 0;				/* incializa o peso da encomenda a 0 */
					printf("Nova encomenda %d.\n", ide);
					ide += 1;							/* aumenta o ide da proxima encomenda */
					break;
				}
			case 'A': {		/* no caso do primeiro valor do comando ser A: */
				idf_encomenda = extrai_nr();
				ptr_comando += 1;
				idf_produto = extrai_nr();
				ptr_comando += 1;
				stock = extrai_nr();			/* obtem os valores necessarios */
				if(idf_encomenda >= ide) {		/* verifica se os valores sao possiveis */
					printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idf_produto, idf_encomenda);
					break;
				}
				if(idf_produto >= idf) {
					printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idf_produto, idf_encomenda);
					break;
				}
				if(stock > lista_produtos[idf_produto].qtd) {
					printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idf_produto, idf_encomenda);
					break;
				}
				i = (stock * lista_produtos[idf_produto].peso) + lista_encomendas[idf_encomenda].peso;
				if(i > 200) {
					i = 0;
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idf_produto, idf_encomenda);
					break;
				}			/* se for possivel tira ao produto a qnt que ira ser posta no sotpck e aumenta-se o peso da encomenda */
				lista_produtos[idf_produto].qtd += (-1 * stock);
				lista_encomendas[idf_encomenda].peso = i;
				lista_encomendas[idf_encomenda].produto[idf_produto] += stock;
				i = 0;
				break;
			}
			case 'd': {        /* usado para escrever as caracteristicas do produto(util para debugging) */
				idf_produto = extrai_nr();
				printf("%s\n%d\n%d\n%d\n",lista_produtos[idf_produto].descricao,lista_produtos[idf_produto].peso,lista_produtos[idf_produto].preco,lista_produtos[idf_produto].qtd);
				break;
			}
			case 'D': {		/* usado para escrever as caracteristicas do encomenda(util para debugging) */
				idf_encomenda = extrai_nr();
				i = 0;
				while(i < idf) {
					printf("%d-%d\n",i, lista_encomendas[idf_encomenda].produto[i]);
					i += 1;
				}
				i = 0;
				break;
			}
			case 'r': {		/* no caso do primeiro valor do comando ser r: */
				idf_produto = extrai_nr();     /* obtem o idp do produto */
				if(idf_produto >= idf) {		/* verifica se o produto existe */
					printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idf_produto);
					break;
				}
				ptr_comando += 1;
				i = extrai_nr();	/* ve a quantidade a remover e verifica se e possivel remove-la */
				if(lista_produtos[idf_produto].qtd < i) {
					printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", i, idf_produto);
					break;
				}		/* remove a quantidade ao stock do produto */
				lista_produtos[idf_produto].qtd += -1 * i;
				break;
			}
			case 'R': {		/* no caso do primeiro valor do comando ser R: */
				idf_encomenda = extrai_nr();
				ptr_comando += 1;
				idf_produto = extrai_nr();
				if(idf_encomenda >= ide) {		/* obtem o idp e o ide e verifica se existem */
					printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idf_produto, idf_encomenda);
					break;
				}
				if(idf_produto >= idf) {
					printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idf_produto,idf_encomenda);
					break;
				}		/* se existirem remove a quantidade do produto da encomenda e devolve essa quantidade ao stock */
				lista_encomendas[idf_encomenda].peso -= lista_encomendas[idf_encomenda].produto[idf_produto] * lista_produtos[idf_produto].peso;
				lista_produtos[idf_produto].qtd += lista_encomendas[idf_encomenda].produto[idf_produto];
				lista_encomendas[idf_encomenda].produto[idf_produto] = 0;
				break;
			}
			case 'C': {		/* no caso do primeiro valor do comando ser C: */
				idf_encomenda = extrai_nr();
				if(idf_encomenda >= ide) {		/* obtem o ide e verifica se existe */
					printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idf_encomenda);
					break;
				}
				i = 0;
				lista_encomendas[idf_encomenda].preco = 0; /* inicializa ou define o valor do preco para 0 */
				while(i < idf) {   /* ve se existe o produto na encomenda e se existir acrescenta o preco dos produtos a encomenda */
					lista_encomendas[idf_encomenda].preco += lista_encomendas[idf_encomenda].produto[i] * lista_produtos[i].preco;
					i = i+1;
				}
				printf("Custo da encomenda %d %d.\n", idf_encomenda, lista_encomendas[idf_encomenda].preco);
				break;
				}
			case 'p':{		/* no caso do primeiro valor do comando ser p: */
				idf_produto = extrai_nr(); /* obtem o idp do produto */
				if(idf_produto >= idf) {
					printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idf_produto);
					break;
				}
				ptr_comando += 1;
				i = extrai_nr();	/* obtem o novo preco */
				lista_produtos[idf_produto].preco = i;  /* altera o preco */
				break;
			}
			case 'E': {     /* no caso do primeiro valor do comando ser E: */
				idf_encomenda = extrai_nr();
				ptr_comando += 1;
				idf_produto = extrai_nr();
				if(idf_encomenda >= ide) {	/* extrai o valor do ide e do idf e verifica se existem */
					printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idf_encomenda);
					break;
				}
				if(idf_produto >= idf){
					printf("Impossivel listar produto %d. Produto inexistente.\n", idf_produto);
					break;
				}    	/* retoma a descricao e quantidade do produto na encomenda*/
				printf("%s %d.\n",lista_produtos[idf_produto].descricao,lista_encomendas[idf_encomenda].produto[idf_produto]);
				break;
			}
			case 'm': {		/* no caso do primeiro valor do comando ser m: */
					idf_produto = extrai_nr();  /* extrai o idp */
					if(idf_produto >= idf) {   /* verifica se existe o idp */
						printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idf_produto);
						break;
					}
					i = 0;
					idf_encomenda = 0;
					while(ide > i) {  /* verifica a quantidade do produto em cada emcomenda, e guarda a maior */
						if(lista_encomendas[idf_encomenda].produto[idf_produto] < lista_encomendas[i].produto[idf_produto]) {
								idf_encomenda = i;
						}
						i = i+1;
					}
					if(lista_encomendas[idf_encomenda].produto[idf_produto] ==0) {
						break;
					}		/* se a quantidade for 0 nao faz nada pois a encomenda nao tem produtos */
					printf("Maximo produto %d %d %d.\n", idf_produto, idf_encomenda,lista_encomendas[idf_encomenda].produto[idf_produto]);
					break;
			}
			case 'l':		/* no caso do primeiro valor do comando ser l: */
				{
				i = 0;
				len = 2;				/* indica o numero de variaveis relevantes ao heapsort */
				if(idf == 0){
					printf("Produtos\n");
					break;					/*se nao existirem produtos*/
				}
				while(i < idf){			/* adiciona as informacoes relevantes ao heap sort */
					lista[i][0] = lista_produtos[i].preco;
					lista[i][1] = lista_produtos[i].idp;
					i +=1;
				}
				ult_valor = i - 1;		/* indica o ultimo valor da lista e guarda */
				b = ult_valor;			
				buildheap();
    			while(ult_valor != 0){  /* troca o primeiro termo com o ultimo desordenado */
        			aux_main[0] = lista[ult_valor][0];
        			aux_main[1] = lista[ult_valor][1]; 
        			lista[ult_valor][0] = lista[0][0];
        			lista[ult_valor][1] = lista[0][1];
        			lista[0][0] = aux_main[0];
        			lista[0][1] = aux_main[1];
        			ult_valor -= 1;			/* faz com que o fixdown nao altere os ordenados*/
        			i = 0;
        			fixdown();				/* faz fixdown ao termo de posicao 0 */
        			}
				i = 0;
				printf("Produtos\n");
    			while(i <= b){			/* printa os produtos ordenados */
					ult_valor = lista[i][1];
        			printf("* %s %d %d\n",lista_produtos[ult_valor].descricao,lista_produtos[ult_valor].preco, lista_produtos[ult_valor].qtd);
        			i = i + 1;
    			}
				break;
			}
			case 'L': {		/* no caso do primeiro valor do comando ser L: */
				static int indice_counter;
				len = tamanho_descricao + 2;		/* indica o numero de variaveis relevantes */ 
				i = 0;
				idf_encomenda = extrai_nr();		/* obtem o ide */
				i = 0;
				if(idf_encomenda >= ide) {    /* verifica se existe a encomenda */
					printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idf_encomenda);
					break;				
				}
				if(idf == 0) {			/* se nao existirem produtos */
					printf("Encomenda %d\n", idf_encomenda);	
					break;
				}
				indice_counter = 0;
				while(i < idf) {		/* enquanto existirem mais produtos: */
					var_aux = 0;
					if(lista_encomendas[idf_encomenda].produto[i] == 0) { 
						i = i + 1;
						continue;
					}			/* se a qnt do produto for 0 passa ao proximo produto */
					while(lista_produtos[i].descricao[var_aux] != '\0') {
						lista[indice_counter][var_aux] = lista_produtos[i].descricao[var_aux];
						if(lista[indice_counter][var_aux] > 96) {
							lista[indice_counter][var_aux] -= 32;
						}											
						var_aux += 1;				/* converte a descricao para numeros, fazendo as minusculas passarem para o valor de maiusculas */
					}								/* a alteracao nao e relevante para outros chars, embora aconteca */
					lista[indice_counter][var_aux] = 255;  /* caracter usado para desempatar se strings tiverem tamanhos diferentes */
					lista[indice_counter][len] = i;			/* guarda o idp para quando estiver ordenado saber qual produto e qual */
					i = i + 1;
					indice_counter += 1;
					}
				if(indice_counter == 1) {
					printf("Encomenda %d\n", idf_encomenda);
					printf("* %s %d %d\n",lista_produtos[lista[0][len]].descricao,lista_produtos[lista[0][len]].preco, lista_encomendas[idf_encomenda].produto[lista[0][len]]);
					break;
				}
				if(indice_counter == 0){
					printf("Encomenda %d\n", idf_encomenda);
					break;
				}								/* verifica se o ha 1 ou 0 arrays na lista pois estes valores causavam problemas */
				ult_valor = indice_counter - 1;			/* indica o ultimo valor */
				b = ult_valor;							/* guarda o ult_valor*/
				buildheap();							/* constroi o heap */
				i = 0;
    			while(ult_valor != 0) {			/* enquanto a lista nao estiver ordenada: */
					var_aux = 0;
					while(var_aux != len + 1) {
        				aux_main[var_aux] = lista[ult_valor][var_aux];
        				lista[ult_valor][var_aux] = lista[0][var_aux];
						lista[0][var_aux] = aux_main[var_aux]; 
						var_aux += 1;							/* troca o primeiro termo com o ultimo */
					}
        			ult_valor -= 1;
        			i = 0;
        			fixdown();		/* faz fixdown do primeiro termo */
        		}
				i = 0;
				ult_valor = 10500;						/* evita que o ult_valor seja o dp do primeiro produto */
				printf("Encomenda %d\n", idf_encomenda);
    			while(i <= b) {								/* escreve todos os produtos da lista ordenada */
					if(ult_valor == lista[i][len]) {
						i +=1;
						continue;
					}		/* evita repeticao de valores(devido a um bug) */
					ult_valor = lista[i][len];
					if(lista_encomendas[idf_encomenda].produto[ult_valor] == 0) {	/* evita que escrevam valores que nao estao na encomenda */
							i +=1;
							continue;
					}
        			printf("* %s %d %d\n",lista_produtos[ult_valor].descricao,lista_produtos[ult_valor].preco, lista_encomendas[idf_encomenda].produto[ult_valor]);
        			i = i + 1;		/* passa ao proximo valor da lista */
				}
					break;
			}
		}
		scanf(" %[^\n]", comando);  /* extrai o novo comando */
		ptr_comando = ptr_novo_comando + 2;   /* reinicia a posicao do ponteiro */
	}
return 0;
}