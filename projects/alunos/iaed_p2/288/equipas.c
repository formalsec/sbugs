#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "equipas.h"
#include "jogos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* funcoes auxiliares aos comandos*/
void alphasort(char **nomes, int count)  							/* Ordena alfabticamente uma array de strings (descricoes de produtos)*/
{
	int i, j;
	char *temp;
	count--;
	for(i=0;i<=count;i++)											/* Ciclos for que ordenam a array atraves de strcmp*/
	{
      	for(j=i+1;j<=count;j++)
      	{
        	if(strcmp(nomes[i],nomes[j])>0)
        	{														
            	temp=can_fail_malloc(sizeof(char)*(strlen(nomes[i])+1)); 	/* alocacao da var temp com o tamanho de nomes[i]+1 para permitir a copia seguinte*/
            	strcpy(temp,nomes[i]);
            	nomes[i]=can_fail_realloc(nomes[i], (strlen(nomes[j])+1)); 	/* realocacao da var nomes[i] com o tamanho de nomes[j]+1 para permitir a copia seguinte*/
            	strcpy(nomes[i],nomes[j]);
            	nomes[j]=can_fail_realloc(nomes[j], (strlen(temp)+1)); 	  	/* realocacao da var nomes[j] com o tamanho de temp+1 para permitir a copia seguinte*/
           		strcpy(nomes[j],temp);
           		free(temp);											/* libertar a var temp da memoria*/
        	}
        }
	}
}

int hash(char *string, int capacity)					/* funcao que obtem o valor do hash para uma dada string*/
{
	int h = 0, a = 127;
	for (; *string!= '\0'; string++)
	h = (a*h + *string) % capacity;
	return h;
}

int checkins(char *equipa, hashtable_equipas *h_equipas, int hash)
{														/* funcao que descobre se uma equipa esta na lista ligada, TRUE se nao estiver*/
	hash_node_equipas *checker;
	for (checker= h_equipas->tb[hash]; checker!=NULL; checker=checker->next)
		if(strcmp(checker->pointer->equipa, equipa)== 0)
			return 0;
	return 1;
}

/* funcoes de inicializacao das estruturas*/
hashtable_equipas *mk_hash_table_e() 
{
	hashtable_equipas * hash_equipas = can_fail_malloc(sizeof(hashtable_equipas));
	hash_equipas->capacity = CAP;
	hash_equipas->tb = can_fail_calloc(hash_equipas->capacity, sizeof(hash_node_equipas*));
	return hash_equipas;
}

hash_node_equipas *make_hashnode_e(hash_node_equipas *head, node_equipas *node)
{
	hash_node_equipas * hashnode_equipas = can_fail_malloc(sizeof(hash_node_equipas));
	hashnode_equipas->next=head;
	hashnode_equipas->pointer=node;
	head = hashnode_equipas;
	return head;
}

node_equipas *make_node_e(char *equipa, node_equipas *n_equipas)
{
	node_equipas * new_node = can_fail_malloc(sizeof(node_equipas));
	new_node->next= n_equipas;
	new_node->equipa=can_fail_malloc(sizeof(char)*(strlen(equipa)+1));
	strcpy(new_node->equipa, equipa);
	new_node->pontos=0;
	n_equipas = new_node;
	return n_equipas;
}

/* funcao que liberta memoria alocada as estruturas das equipas*/
void lib_espaco_equipas(node_equipas *n_equipas, hashtable_equipas *h_equipas)
{
	hash_node_equipas *tmp2;
    size_t i;
	node_equipas *tmp;
    while (n_equipas != NULL)							/* ciclo que percorre a lista ligada e liberta a memoria*/
    {
   		tmp = n_equipas;
       	n_equipas = n_equipas->next;
       	free(tmp->equipa);
       	free(tmp);
    }
    for (i=0; i<h_equipas->capacity; i++)
    {													/* ciclo que percorre a hashtable e liberta a memoria*/
    	while(h_equipas->tb[i])
    	{
    		tmp2= h_equipas->tb[i]->next;
    		free(h_equipas->tb[i]);
    		h_equipas->tb[i]= tmp2;
    	}
    }
    free(h_equipas->tb);
    free(h_equipas);
}

/* Funcoes responsaveis por executar os comandos do utilizador*/
node_equipas * A(int NL, node_equipas *n_equipas, hashtable_equipas *h_equipas)
{
	char equipa[MAX_NOME];
	int hash_e;
	getchar();
	scanf("%[^:\n]", equipa); 							/* linha de scan que e utilizada para ler uma string do input*/
	hash_e = hash(equipa, h_equipas->capacity);
	if(checkins(equipa, h_equipas, hash_e))				/* se a equipa ainda nao existir entao acrescenta a mesma na lista e na hashtable*/
	{
		n_equipas = make_node_e(equipa, n_equipas);		
		h_equipas->tb[hash_e]=make_hashnode_e(h_equipas->tb[hash_e], n_equipas);
	}
	else
		printf("%d Equipa existente.\n", NL);
	return n_equipas;
}

void P(int NL, hashtable_equipas *h_equipas)
{
	char equipa[MAX_NOME];
	int hash_e;
	hash_node_equipas *checker;
	getchar();
	scanf("%[^:\n]", equipa);
	hash_e = hash(equipa, h_equipas->capacity);
	if(checkins(equipa, h_equipas, hash_e))
		printf("%d Equipa inexistente.\n", NL);
	else												/* ciclo for que utiliza a variavel temporaria checker para percorrer o hash node ate encontrar a equipa procurada*/ 
		for (checker= h_equipas->tb[hash_e]; checker!=NULL; checker=checker->next)
			if(strcmp(checker->pointer->equipa, equipa)== 0)
				printf("%d %s %d\n", NL, checker->pointer->equipa, checker->pointer->pontos);
}

void g(int NL, hashtable_equipas *h_equipas)
{
	size_t i;
	char ** equipas;
	hash_node_equipas *checker;
	int MAX=-1, contador=0, x=0, y;
	for (i=0; i<h_equipas->capacity; i++)				/* ciclo que percorre a hash table toda para obter o maximo de vitorias e quantas equipas atingem este maximo*/            
    {
    	for (checker= h_equipas->tb[i]; checker!=NULL; checker=checker->next)
    	{
    		if (checker->pointer->pontos > MAX)
    		{
    			MAX= checker->pointer->pontos;
    			contador = 1;
    		}
    		else if (checker->pointer->pontos == MAX)
    			contador++;
   	  	}
    }
    if (MAX!=-1)                                 		/* se a variavel max ainda estiver a -1, quer dizer que nao existem equipas em memoria logo nao printa nada*/
    {
	    equipas = can_fail_malloc(sizeof(char*)*(contador+1));
	    for (i=0; i<h_equipas->capacity; i++)           /* ciclo semelhante ao anterior mas que guarda as equipas que tem aquele maximo de vitorias numa lista*/
	    {
	    	for (checker= h_equipas->tb[i]; checker!=NULL; checker=checker->next)
	    	{
	    		if (checker->pointer->pontos == MAX)
	    		{
	    			*(equipas+x)= can_fail_malloc(sizeof(char)*(strlen(checker->pointer->equipa)+1));
	    			strcpy(*(equipas+x), checker->pointer->equipa);
	    			x++;
	    		}
	   	  	}
	    }	
	    *(equipas+x) = '\0';
	    printf("%d Melhores %d\n", NL, MAX);			
	    alphasort(equipas, contador);					/* funcao auxiliar que ordena a lista de equipas por ordem alfabetica (lexicografica)*/
	    for (y=0; y<contador; y++)						/* ciclo que printa a lista ordenada*/
	    {
	    	printf("%d * %s\n", NL, equipas[y]);
	    	free(equipas[y]);
	    }
	    free(equipas);									/* liberta a memoria da lista utilizada nesta funcao (apaga a mesma)S*/ 
	}

}