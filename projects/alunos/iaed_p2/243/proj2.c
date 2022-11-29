#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "proj2.h"

lista *l;
lista2 *l2;

/*****************************************************************************************
 * Funcao responsavel por inicializar todas as estruturas listas com ponteiros a NULL.   *
 *****************************************************************************************/

void inicia_listas()
{
	int i;
	l=(lista *)can_fail_malloc(sizeof(lista)); 
	l2=(lista2 *)can_fail_malloc(sizeof(lista2));        
	l -> head =	l -> last = NULL;
	l2 -> head2 =l2 -> last2 = NULL;
	for (i=0; i<HASHTABLE_SIZE; i++)
	{
	    l -> HashTable_Jogo[i] =  NULL;
	    l2 -> HashTable_Equipas[i] = NULL;
	}
}

/***********************************************************************
 * Funcao procura se o jogo inserido ja existe na hashtable de jogos.  *
 ***********************************************************************/
jogo * procura_jogo(char* Nome)
{
    int h = hash(Nome); /*gera o indice da hashtable de acordo com o nome do jogo*/
    /*obtem o primeiro endereco da linked list guardada na hashtable para o indice gerado*/
    jogo *j = l->HashTable_Jogo[h];
    /*procura ver se o nome existe na hashtable para o index calculado*/
    while (j!=NULL)
    {
    	if (strcmp( j->nome, Nome) == 0) /*se o nome encontrado e o inserido forem iguais*/
    		return j;
    	j=j->next_HashTable_Jogo;
    }
    return NULL; /*se nao encontrar nada retorna NULL*/
}

/***************************************************************************
 * Funcao procura se a equipa inserida ja existe na hashtable de equipas.  *
 ***************************************************************************/
equipas * procura_equipa(char* Equipa)
{
    int h = hash(Equipa);
    equipas *e = l2->HashTable_Equipas[h];
    /*funcionamento semelhante a funcao de cima, mas para a hashtable equipas*/
    while(e!=NULL)
    {
        if (strcmp (e->nomeE, Equipa) == 0) /*se o nome encontrado e o inserido forem iguais*/
        	return e;
        e=e->next_HashTable_Equipas;
    }
    return NULL;
}

/**************************************************************************************
 * Esta funcao recebe um node da lista e liberta a memoria alocada para o mesmo.      *
 **************************************************************************************/
void free_jogo(jogo *j)
{
	free(j->nome);  
	free(j->team1);
	free(j->team2);
	free(j->score1);
	free(j->score2);
	free(j);
}

/**************************************************************************************
 * Esta funcao recebe um node da lista e liberta a memoria alocada para o mesmo.      *
 **************************************************************************************/
void free_equipas(equipas *e)
{
	free(e->nomeE);  
	free(e);
}

/*******************************************************
 * Funcao que lista os dados de um determinado jogo.   *
 *******************************************************/
void lista_jogos(jogo *j)
{
    printf("%s %s %s %s %s\n", j->nome, j->team1, j->team2, j->score1, j->score2);
}

/**********************************************************
 * Funcao que lista os dados de uma determinada equipa.   *
 **********************************************************/
void lista_equipa(equipas *e)
{
    printf("%s %d\n", e->nomeE, e->contador);
}


/**********************************************************
 * Funcao que lista o nome de uma determinada equipa.     *
 **********************************************************/
void lista_equipas_vencedoras(equipas *e)
{
	printf("%s \n", e->nomeE);
}

/*********************************************************************************************************************************
 * Funcao que dada toda a informacao de um jogo, adiciona o mesmo na doubly linked list, e se necessario,                        *
 * tambem atualiza os enderecos relativos ao inicio e ao fim dessa mesma linked list (ponteiros armazenados na estrutura Lista). *
 *********************************************************************************************************************************/
void adiciona_Node_jogo(char *Nome, char *Equipa1, char *Equipa2, char *Score1, char *Score2)
{
	int a, b; 
	jogo *aux = can_fail_malloc(sizeof(jogo));
	 /*atribuicao de enderecos no node do jogo criado*/
	aux->next = NULL;
	aux->previous = l->last;
	aux->next_HashTable_Jogo = NULL;
	  /*no caso de nao haver nenhum jogo inserido, na adicao de um novo jogo o endereco de inicio e fim da linked list 
	   *passam a ser iguais, caso contrario o penultimo jogo da lista guarda o endereco (*next) do novo jogo*/
	if (l->last==NULL)
		l->head=aux;
	else
		l->last->next=aux;
	l->last=aux; /*atualizacao da last (da estrutura lista)*/
	/*alocacao dinamica da informacao associada ao jogo*/
	/*depois de lermos a string introduzida, para criar uma copia e necessario alocar o conjunto de caracteres significativos que existe na string
	 * isto e, temos que alocar strlen(s) caracteres. No entanto, temos que colocar um '\0' no final do vector para que este se possa considerar uma string
	 * Assim teremos que alocar strlen(s)+1 bytes, pois cada caracter ocupa um byte*/
	/*void *memcpy(void *dest, const void * src, size_t n)
	 *dest - Este e o ponteiro para a matriz de destino onde o conteudo deve ser copiado, convertido em tipo para um ponteiro do tipo nulo *.
	 *src - Este e um ponteiro para a fonte de dados a ser copiada, convertido em tipo para um ponteiro do tipo void *.
	 *n - este e o numero de bytes a serem copiados. */
	aux->nome = (char *) memcpy(can_fail_malloc(sizeof(char)*(strlen(Nome)+1)), Nome, sizeof(char)*(strlen(Nome)+1));              
	aux->team1 = (char *) memcpy(can_fail_malloc(sizeof(char)*(strlen(Equipa1)+1)), Equipa1, sizeof(char)*(strlen(Equipa1)+1));
	aux->team2 = (char *) memcpy(can_fail_malloc(sizeof(char)*(strlen(Equipa2)+1)), Equipa2, sizeof(char)*(strlen(Equipa2)+1));
	aux->score1 = (char *) memcpy(can_fail_malloc(sizeof(char)*(strlen(Score1)+1)), Score1, sizeof(char)*(strlen(Score1)+1));
	aux->score2 = (char *) memcpy(can_fail_malloc(sizeof(char)*(strlen(Score2)+1)), Score2, sizeof(char)*(strlen(Score2)+1));
	a = atoi(aux->score1);
	b = atoi(aux->score2);
	if (a>b) /*Se a vencedora do jogo for a equipa 1*/
	{
		equipas *e = procura_equipa(Equipa1);
		e->contador +=1;
	}
	if (a<b) /*Se a vencedora do jogo for a equipa 2*/
	{
		equipas *e = procura_equipa(Equipa2);
		e->contador +=1;
	}
}

/****************************************************************************
 * Funcao que dado um jogo, elimina o node associado na doubly linked list. *
 ****************************************************************************/
void remove_Node_jogo(jogo *j)
{
    /*os ciclos apresentados permitem a ligacao direta entre os nodes adjacentes ao jogo a ser apagado (caso o jogo se encontre no inicio ou fim da
     *linked list, a estrutura lista e atualizada com a nova head/last)*/
    if (j->previous == NULL)
    	l->head = j->next;
   	else
   		j->previous->next = j->next;
    
    if (j->next == NULL) 
    	l->last = j->previous;
    else 
    	j->next->previous = j->previous;
    
    free_jogo(j);
}

/*********************************************************************************************************************************
 * Funcao que dada toda a informacao de um jogo, adiciona o mesmo na doubly linked list, e se necessario,                        *
 * tambem atualiza os enderecos relativos ao inicio e ao fim dessa mesma linked list (ponteiros armazenados na estrutura Lista). *
 *********************************************************************************************************************************/
void adiciona_Node_equipas(char *Equipa)
{
	equipas *aux2 = can_fail_malloc(sizeof(equipas));
	/*atribuicao de enderecos no node da equipa criada*/
	aux2->next2 = NULL;
	aux2->previous2 = l2->last2;
	aux2->next_HashTable_Equipas = NULL;
	/*no caso de nao haver nenhuma equipa inserido, na adicao de uma nova equipa o endereco de inicio e fim da linked list 
	 *passam a ser iguais, caso contrario a penultima equipa da lista guarda o endereco (*next) da nova equipa*/
	if (l2->last2 == NULL)
		l2->head2 = aux2;
	else
		l2->last2->next2 = aux2;
	l2->last2 = aux2; /*atualizacao da last (da estrutura lista)*/
	/*alocacao dinamica da informacao associada a equipa*/
	aux2->nomeE = (char *) memcpy(can_fail_malloc(sizeof(char)*(strlen(Equipa)+1)), Equipa, sizeof(char)*(strlen(Equipa)+1));     
	aux2->contador=0;
}

/*******************************************************************************
 * Funcao que dado uma equipa, elimina o node associado na doubly linked list. *
 *******************************************************************************/
void remove_Node_equipas(equipas *e)
{
    /*os ciclos apresentados permitem a ligacao direta entre os nodes adjacentes a equipa a ser apagada (caso a equipa se encontre no inicio ou fim da
    *linked list, a estrutura lista e atualizada com a nova head/last)*/
    if (e->previous2 == NULL)
    	l2->head2 = e->next2;
    else
    	e->previous2->next2 = e->next2;
    
    if (e->next2 == NULL)
    	l2->last2 =e->previous2;
    else
    	e->next2->previous2 = e->previous2;

    free_equipas(e);
}

/********************************************************************************************
 * Funcao hash e usada nas hashtables jogos e equipas, encontra-se nos slides dados em aula.*
 ********************************************************************************************/
int hash(char *v)
{
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a*h + *v) % HASHTABLE_SIZE;
    return h;
}

/***********************************************************************************
 * Funcao que dado um nome, adiciona o node correspondente na hashtable dos jogos. *
 ***********************************************************************************/
void adiciona_HashTable_Jogo(char *Nome)
{
    int h = hash(Nome); /*gera o indice da hashtable de acordo com o nome*/
    jogo *j = l->HashTable_Jogo[h]; /*obtem o primeiro endereco da linked list guardado na hashtable para o indice gerado*/
    for (;j != NULL ;j = j->next_HashTable_Jogo) /*procura chegar ao ultimo node da linked list desse indice*/
        if (j->next_HashTable_Jogo == NULL)
            break; /*a busca e interrompida quando o endereco procurado e encontrado*/
    /*quando encontra o ultimo node atribui um novo endereco de continuidade da hashtable (next_HashTable_Jogo), ou no caso de nao haver
     * nenhum jogo nesse indice, o vetor de ponteiros, para o indice calculado, guarda o endereco de inicio da linked list*/
    if (j != NULL)
    	j->next_HashTable_Jogo = l->last;
    else
    	l->HashTable_Jogo[h] = l->last;
}

/**********************************************************************************
 * Funcao que dado um nome, elimina o node correspondente na hashtable dos jogos. *
 **********************************************************************************/
void remove_HashTable_Jogo(char* Nome)
{
    int h = hash(Nome); /*gera o indice da hashtable de acordo com o nome*/
    /*obtem o primeiro endereco da linked list guardado na hashtable para o indice gerado*/
    jogo *j = l->HashTable_Jogo[h], *prevJogo = NULL; /*ponteiro que indica o node anterior a j. */
    /*procura pelo node na linked list com o indice correspondente*/
    for (; j!=NULL; j=j->next_HashTable_Jogo) {
        if (strcmp(j->nome, Nome) == 0)
            break; /*a busca e interrompida quando o endereco pretendido e encontrado*/
      /*durante a busca, se o nome do buffer for diferente do nome no node a ser testado, o endereco e guardado no ponteiro prevJogo antes de ser atualizado*/
        prevJogo = j;
    }
    /*o node do jogo anterior (prevJogo) passa a "ligar" ao node a seguir ao   jogo
     *a ser apagado, atualizando assim os seus enderecos respetivos, ou no caso deste ser o
     *primeiro jogo nesse index, o vetor passa a guardar o novo inicio da linked list*/
    if (prevJogo == NULL)
    	l->HashTable_Jogo[h] = j->next_HashTable_Jogo;
    else
    	prevJogo->next_HashTable_Jogo = j->next_HashTable_Jogo;
}

/****************************************************************************************************
* Funcao que dado um nome de uma equipa, adiciona o node correspondente na hashtable das equipas    *                                 
 ****************************************************************************************************/
void adiciona_HashTable_Equipas(char *Equipa)
{
    int h = hash(Equipa); /*gera o indice da hashtable de acordo com a equipa*/
    /*obtem o primeiro endereco da linked list guardado na hashtable para o indice gerado*/
    equipas *e = l2->HashTable_Equipas[h];
    /*procura pelo node na linked list com o indice correspondente*/
    for (;e != NULL ;e = e->next_HashTable_Equipas) /*procura chegar ao ultimo node da linked list desse indice*/
        if (e->next_HashTable_Equipas == NULL)
            break; /*a busca e interrompida quando o endereco pretendido e encontrado*/ 
    /*quando encontra o ultimo node atribui um novo endereco de continuidade da hashtable (next_HashTable_Equipas), ou no caso de nao haver
     * nenhum jogo nesse indice, o vetor de ponteiros, para o indice calculado, guarda o endereco de inicio da linked list*/
    if (e!=NULL) 
    	e->next_HashTable_Equipas=l2->last2;
    else
    	l2->HashTable_Equipas[h]=l2->last2;
}

/************************************************************************************
* Funcao que compara os nomes das equipas para os poder ordenar lexicograficamente  *                                 
 ************************************************************************************/
int compararNome (const void *a, const void *b) 
{
    return strcmp(((equipas*)a)->nomeTeam,((equipas*)b)->nomeTeam);
}

/***********************************************************************
 *                             MAIN                                    *                                                          
 ***********************************************************************/

int main()
{
    char Nome[MAXNOME], Equipa1[MAXTEAM], Equipa2[MAXTEAM], Score1[MAXSCORE], Score2[MAXSCORE], Equipa[MAXTEAM];
    char comando;
    int conta=0, maior=0, num=0, i=0;
    int a, b, j;
    equipas item[800];
    jogo *aux, *store;
    equipas *aux2, *store2;
    inicia_listas(); /*inicializa todos os ponteiros das estruturas listas dos jogos e das equipas a NULL*/
    while (1)
    {
	    scanf("%c", &comando); /*recebe o comando que se pretende realizar*/
	    switch (comando)
	    {
	      	case 'a': 
		        scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%[^:]:%s", Nome, Equipa1,  Equipa2, Score1, Score2);
				conta++;
		        if (procura_jogo(Nome) != NULL) /*se o jogo ja existir, entao:*/
		        	printf("%d Jogo existente.\n", conta); 	
		        else
		        {
		        	if (procura_equipa(Equipa1) == NULL || procura_equipa(Equipa2) == NULL) /*no caso de uma das equipas ou ambas nao existirem no sistema, entao:*/
		        		printf("%d Equipa inexistente.\n", conta); 
		        	else
		        	{
		        		adiciona_Node_jogo(Nome, Equipa1, Equipa2, Score1, Score2); /*adiciona o node na doubly linked list*/
		            	adiciona_HashTable_Jogo(Nome); /*adiciona o node na hashtable jogo*/
		        	}
		        }
		        break;
	      	case 'l': 
		        aux = l->head;
		        conta++;
		        for (; aux!=NULL; aux=aux->next) /*print do todos os jogos*/
		    	{
		        	printf("%d ", conta);
		        	lista_jogos(aux);
		        }
		        break;
	      	case 'p': 
		        scanf(" %[^\n]", Nome);
		        aux = procura_jogo(Nome); /*verifica se o jogo esta na base de dados*/
				conta++;
		        if (aux != NULL) /*existindo -> entao*/
		        {
		        	printf("%d ", conta);
		            lista_jogos(aux);/*se existir imprime os dados de um determinado jogo*/
		        }
		        else
		            printf("%d Jogo inexistente.\n", conta); /*caso imprime um erro, pois o jogo nao existe*/
		        break;
	      	case 'r': 
		        scanf(" %[^\n]", Nome);
		        aux = procura_jogo(Nome); /*verifica se o jogo esta na base de dados*/
		       	conta++;
		        if (aux != NULL) /* e se este existir entao -> sera removido*/
		        { 
		        	a = atoi(aux->score1);
					b = atoi(aux->score2);
					if (a>b)
					{
						equipas *e = procura_equipa(aux->team1);
						if (e->contador == maior)
							maior--;
						e->contador -=1;
					}
					if (a<b)
					{
						equipas *e = procura_equipa(aux->team2);
						if (e->contador == maior)
							maior--;
						e->contador -=1;
		        	}
		            remove_HashTable_Jogo(Nome); /*primeiro removendo o node da hashtable dos jogos*/
		            remove_Node_jogo(aux); /* e remove o node da linked list*/
		        }
		        else
		            printf("%d Jogo inexistente.\n", conta); /*imprime um erro, pois o jogo nao existe*/
		        break;
		    case 's': 
		        scanf(" %[^:]:%[^:]:%s", Nome, Score1, Score2);
		        aux = procura_jogo(Nome); /*verifica se o jogo esta na base de dados*/
		        conta++;
		        if (aux != NULL)
		        { /*Se estiver entao -> realoca a memoria para a nova score do jogo, remove o score antigo da hashtable e mete o novo*/
		        	a = atoi(aux->score1);
					b = atoi(aux->score2);
		        	if (a>b){
		        		equipas *e = procura_equipa(aux->team1);
		        		if (e->contador ==maior)
							maior--;
						e->contador -=1;
		        	}
		        	if (b>a){
		        		equipas *e = procura_equipa(aux->team2);
		        		if (e->contador ==maior)
							maior--;
						e->contador -=1;
		        	}
		        	/*realocacao dinamica da informacao associada a um determinado jogo*/
		            aux->score1 = (char *) memcpy(can_fail_realloc(aux->score1, sizeof(char)*(strlen(Score1)+1)),Score1, sizeof(char)*(strlen(Score1)+1));
		            aux->score2 = (char *) memcpy(can_fail_realloc(aux->score2, sizeof(char)*(strlen(Score2)+1)),Score2, sizeof(char)*(strlen(Score2)+1));
					a = atoi(aux->score1);
					b = atoi(aux->score2);
					if (a>b)
					{
						equipas *e = procura_equipa(aux->team1);
						e->contador +=1;
					}
					if (a<b)
					{
						equipas *e = procura_equipa(aux->team2);
						e->contador +=1;
		        	}
		        }
		        else
		            printf("%d Jogo inexistente.\n", conta); /* No caso de nao existir nenhum jogo com esse nome no sistema*/
		        break;
		   	case 'A': 
		        scanf(" %[^\n]", Equipa);
		        conta++;
		        if (procura_equipa(Equipa) != NULL) /*se a equipa existir -> entao:*/
		        	printf("%d Equipa existente.\n", conta); /* No caso de ja existir uma equipa com esse nome no sistema*/
		        else
		        {
		            adiciona_Node_equipas(Equipa); /*adiciona o node na doubly linked list*/
		            adiciona_HashTable_Equipas(Equipa); /*adiciona o node na hashtable jogo*/
		        }
		        break;
		    case 'P': 
		        scanf(" %[^\n]", Equipa);
		        aux2 = procura_equipa(Equipa); /*verifica se a equipa esta na base de dados*/
		        conta++;
		        if (aux2 != NULL)/*se a equipa existir -> entao:*/
		        {
		            printf("%d ", conta); 
		            lista_equipa(aux2); /*se existir imprime toda a informacao associada a essa equipa*/
		        }
		        else
		            printf("%d Equipa inexistente.\n", conta); /*no caso de nao existir nenhuma equipa com esse nome no sistema*/
		        break;
		    case 'g': 
		    	aux2 = l2->head2;
		        conta++;
                if (aux2 != NULL) /*se existirem equipas entao*/
                {
	                for (; aux2!=NULL; aux2=aux2->next2) /*corre todos as equipas*/
					{
						if (aux2->contador!=0) /*se o numero de viorias da equipa for diferente de zero*/
						{
       						if (aux2->contador > maior)
           						maior = aux2->contador;
        				}
    				}
    				printf("%d Melhores %d\n",conta, maior);
	                aux2 = l2->head2;
	                for (; aux2!=NULL; aux2=aux2->next2) /*corre todos as equipas*/
	                {
	                	if(aux2->contador == maior)
	                	{
	                		num++;
        					strcpy(item[i].nomeTeam, aux2->nomeE); /*adiciona ao vetor o nome das equipas que tem o numero de vitorias = ao max vitorias*/
        					i++;
        				}
	                }
	                qsort(item, num, sizeof(equipas), compararNome); /*ordena lexicograficamente*/
		
		            for(j=0; j<num; j++){
		            	if (strcmp(item[j].nomeTeam,"\0")!=0)
		                	printf("%d * %s\n", conta, item[j].nomeTeam);
		            }
		            for(j=0; j<num; j++){
		                strcpy(item[j].nomeTeam,"\0");
		            }
	            }
		        break;
        	case 'x':
		        aux = l->head;
		        /*Recorre a funcao remove_Node_jogo de modo a dar free() a toda a memoria associada ao jogo especificado. Este processo
		         *acontece em ciclo de modo a que toda a memoria previamente alocada para cada um dos jogos passe a estar disponivel*/
		        for(; aux!=NULL; aux=store)
		        {
		            store = aux->next; /*guarda o endereco do proximo jogo a ser apagado*/
		            remove_Node_jogo(aux);
		        }
		        aux2 = l2->head2;
		        /*Recorre a funcao remove_Node_equipas de modo a dar free() a toda a memoria associada a equipa especificada. Este processo
		         *acontece em ciclo de modo a que toda a memoria previamente alocada para  cada uma das equipas passe a estar disponivel*/
		        for(; aux2!=NULL; aux2=store2)
		        {
		            store2 = aux2->next2; /*guarda o endereco da proxima equipa a ser apagado*/
		            remove_Node_equipas(aux2);
		        }
		        free (l); /*da free na estrutura lista dos jogos*/
		        free (l2); /*da free na estrutura lista das equipas*/
		        return 0;
	    }
  	}
    return 0;
}
