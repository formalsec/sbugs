#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "estruturas.h"
#include "tabelas_disp.h"

/*Funcao de dispersao para strings*/

/*Calcula o indice com base no nome tanto de uma Equipa
como de um Jogo*/
long hash(char *v, long M)
{
	long h, a=31415, b=27183;

	for (h=0;*v != '\0';v++,a=a*b % (M-1))
	{
		h= (a*h+*v) % M;
	}	
	return h;
}



/*HASH TABLE JOGOS*/



/*Inicializa uma hash table para os jogos. Devolve um 
ponteiro que aponta para a mesma*/

ST_jg ST_jg_init(long max)
{
	long i;
	ST_jg new=(ST_jg) can_fail_malloc (sizeof(struct hash_table_jg));
	
	/*Numero de elementos iniciado a zero*/
	new->N = 0; 
	
	/*Capacidade iniciada como o dobro do valor passado 
	como argumento */
	new->M = 2*max; 
	
	/*Reserva a memoria para a tabela e inicia todas as suas 
	posicoes a NULL*/
	new->st = (Jogo*) can_fail_malloc(new->M*sizeof(Jogo));
	
	for(i=0 ; i<(new->M) ; i++)
	{
		new->st[i]= NULL;
	}
	return new;
}


/*Insere um elemento numa tabla de jogos, dada a 
tabela e o jogo a ser inserido*/

void ST_jg_insert(ST_jg T,Jogo jogo)
{
	Key value = key(jogo);
	/*Calcula o indice i, atraves da hash function*/
	long i=hash(value,T->M);
	
	/*Procura a primeira posicao vazia, se a 
	posicao do indice i estiver ocupada*/
	while (T->st[i] != NULL) 
	{
		i=(i+1) % T->M;
	}
	T->st[i]=jogo;
	/*Incrementa o numero de elementos da tabela*/
	T->N++;
	
}


/*Remove um elemento numa tabela de jogos, 
dada a tabela e o jogo a ser eliminado*/
void ST_jg_delete(ST_jg T,Key value)
{
	long j, i=hash(value,T->M);
	Jogo aux; 
	
	/*Procura o elemento que vai ser eliminado.
	Se for igual ao da posicao i entao foi encontrado e para o ciclo.
	Caso contrario, procura ate encontrar um espaco vazio*/
	while(T->st[i]!=NULL)
	{
		
		if(eq(value,key(T->st[i])))
		{
			break;
		}
		else
		{
			i=(i+1)%(T->M);
		}
	}

	/*Se o ciclo acabar e o elemento nao for encontrado,
	entao nao existe na tabela e nao pode ser eliminado*/
	if(T->st[i]==NULL)
	{
		return;
	}

	/*Liberta o espaco do elemento a ser eliminado e elimina-o*/
	free_Jogo(T->st[i]);
	T->st[i]=NULL;
	T->N--;
	
	/*Recoloca os elementos na tabela, de forma a ficarem ordenados,
	novamente*/
	for(j=(i+1)% (T->M); T->st[j]!=NULL; j=(j+1)%(T->M),T->N--)
	{
		aux=T->st[j];
		T->st[j]=NULL;
		ST_jg_insert(T,aux);
	}
}


/*Procura um jogo numa tabela, dado o nome do jogo
e a tabela. Devolve um ponteiro para o jogo*/
Jogo ST_jg_search(ST_jg T,Key value)
{
	long i=hash(value,T->M);
	
	/*Procura ate encotrar ou encontrar um
	espaco vazio.*/
	while(T->st[i]!= NULL)
	{
		if(eq(value,key(T->st[i])))
		{
			return T->st[i];
		}
		else
		{
			i=(i+1)%(T->M);
		}
	}
	/*Caso nao encontrar*/
	return NULL;
	
}



/*HASH TABLE EQUIPAS*/


/*Inicializa uma tabela para equipas. Devolve um ponteiro para a mesma*/
ST_eq ST_eq_init(long max)
{
	long i;
	ST_eq new=(ST_eq) can_fail_malloc(sizeof(struct hash_table_eq));
	
	/*Numero de elementos iniciado a zero*/
	new->N = 0; 
	
	/*Capacidade iniciada como o dobro do valor passado 
	como argumento */
	new->M = 2*max; 
	
	/*Reserva a memoria para a tabela e inicia todas as suas 
	posicoes a NULL*/
	new->st = (Equipa*) can_fail_malloc(new->M*sizeof(Equipa));
	
	for(i=0 ; i<(new->M) ; i++)
	{
		new->st[i]= NULL;
	}
	return new;
}



/*Insere uma equipa numa tabela para equipas, dada a tabela e a equipa*/
void ST_eq_insert(ST_eq T, Equipa equipa)
{
	Key value = key(equipa);
	long i=hash(value,T->M);
	
	/*Procura a primeira posicao vazia apos o 
	calculo da chave de dispersao*/
	while (T->st[i] != NULL) 
	{
		i=(i+1) % (T->M);
	}
	T->st[i]=equipa;
	/*Incrementa o numero de elementos da tabela*/
	T->N++;

}



/*Procura uma equipa numa tabela para equipas, dada a tabela e a equipa.
Devolve um ponteiro para a equipa*/
Equipa ST_eq_search(ST_eq T,Key value)
{
	long i=hash(value,T->M);
	
	/*Procura ate encontrar ou ate encontrar 
	um espaco vazio*/
	while(T->st[i]!= NULL)
	{
		if(eq(value,key(T->st[i])))
		{
			return T->st[i];
		}
		else
		{
			i=(i+1)%(T->M);
		}
	}
	return NULL;
	
}



/*Aumenta a capacidade de uma tabela de jogos, dada a tabela*/
ST_jg expand_j(ST_jg Tj)
{
	
	ST_jg new;
	long i;
	/*Aloca espaco para uma nova tabela*/
	new=ST_jg_init(Tj->M+Tj->M);
	
	/*Copia os elementos da tabela antiga para nova*/
	for(i=0;i<Tj->M;i++)
	{
		if(Tj->st[i]!=NULL)
		{
			ST_jg_insert(new,Tj->st[i]);
		}
	}
	/*Liberta o espaco reservado pela tabela antiga*/
	free(Tj->st);
	free(Tj);
	
	/*Devolve um ponteiro para a nova tabela*/
	return new;
}



/*Aumenta a capacidade de uma tabela para equipas,dada a tabela*/
ST_eq expand_e(ST_eq Te)
{
	
	ST_eq new;
	long i;
	
	/*Reserva espaco para uma nova tabela*/
	new=ST_eq_init(Te->M+Te->M);
	
	/*Copia os elementos da tabela antiga para a tabela nova*/
	for(i=0;i<Te->M;i++)
	{
		if(Te->st[i]!=NULL)
		{
			ST_eq_insert(new,Te->st[i]);
		}
	}
	
	/*Liberta o espaco ocupado pela tabela antiga*/
	free(Te->st);
	free(Te);
	
	/*Devolve um ponteiro para a nova tabela*/
	return new;

}




/*Liberta o espaco reservado por uma tabela de jogos*/
void free_HTe(ST_eq T)
{
	long i;
	for(i=0;i<T->M;i++)
	{
		free_Equipa(T->st[i]);
	}
	
	free(T->st);
	free(T);
}


/*Liverta o espaco reservado por uma tabela de equipas*/
void free_HTj(ST_jg T)
{
	long i;
	for(i=0;i<T->M;i++)
	{
		free_Jogo(T->st[i]);
	}
	
	free(T->st);
	free(T);
}

