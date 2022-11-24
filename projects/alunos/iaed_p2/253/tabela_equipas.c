#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "TABELA_HASH_E.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************************************
*			           FUNCOES AUXILIARES DAS EQUIPAS / HASH TABLE                             *
***********************************************************************************************/

/* Aloca espaco na memoria para uma hash table nova e inicializa os atributos. */
Tabela_hash *cria_tabela_hash()
{
	Tabela_hash *nova_t = can_fail_malloc(sizeof(Tabela_hash));
	nova_t->capacidade = T_INICIAL;
	nova_t->topos = can_fail_calloc(nova_t->capacidade, sizeof(No_hash*));
	return nova_t;
}

/* Funcao de dispersao dado uma string */
int hash(const char *nome, int M)	/* M primo minimiza colisoes */
{
	int h = 0, a = 127;

	for (; *nome != '\0'; nome++)	/* Calcula uma soma ponderada dos caracteres */
		h=(a*h + *nome) % M;		/* Modulo utilizado para nao sair dos limites da tabela*/
	return h;
}


/* Aloca espaco na memoria para uma lista (linked list) de equipas */
listE* cria_listE()
{
	listE *l = can_fail_malloc(sizeof(listE));
	l->topo = NULL;
	return l;
}

/* Liberta o espaco na memoria alocado na criacao da equipa */
void free_Equipa(Equipa *n)
{
	free(n->nome);
	free(n);
}

/* Liberta o espaco na memoria alocado na criacao da lista de equipas */
void free_list(listE *l)
{
	while (l->topo)
	/* Percorre a lista ate nao haver mais equipas */
	{
		Equipa *temp = l->topo->proximo;
		free_Equipa(l->topo);
		l->topo = temp;
	}
	free(l);
}


/* Liberta o espaco na memoria alocado na criacao da hash table. */
void free_tabela_hash(Tabela_hash *t)
{
	No_hash *a;
	size_t i;
	for (i=0; i<t->capacidade; i++)
	/* Percorre todos os no's */
	{
		while(t->topos[i])
		/* Percorre a todas as equipas no no' ate este estar vazio */	
		{
			a = t->topos[i]->proximo;
			free(t->topos[i]);
			t->topos[i]=a;
		}
	}
	free(t->topos);
	free(t);
}

/* Aloca espaco para cada atributo e substitui pela informacao dada.
Constroi ou aumenta a lista de equipas e adiciona a equipa na hash table correspondente. */
void cria_Equipa(listE *l, const char *nome, Tabela_hash *tabela)
{
	const size_t i = hash(nome, tabela->capacidade);
	Equipa *novo = can_fail_malloc(sizeof(Equipa));
	novo->proximo = l->topo;
	novo->nome = can_fail_malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(novo->nome, nome);
	novo->pontos=0;
	l->topo = novo;
	/* Atualiza o no */
	tabela->topos[i] = cria_Equipa_hash(tabela->topos[i], novo); 

}

/* Aloca espaco para a nova equipa no no'(da hash table) correspondente. */
No_hash *cria_Equipa_hash(No_hash *topo, Equipa *nova_E)
{
	No_hash *nn = can_fail_malloc(sizeof(No_hash));
	nn->ponteiro = nova_E;
	nn->proximo = topo;
	return nn;

}

/* Dado um nome verifica se essa equipa esta na hash table correspondente. */
/* Devolve 0 se sim, 1 se nao.                                           */
int verifica_e(Tabela_hash *tabela, const char *nome)
{
	const size_t i = hash(nome, tabela->capacidade);	    /* i = no correspondente */
	No_hash *no;
	for (no=tabela->topos[i]; no != NULL; no=no->proximo)   /* Percorre as equipas do no */
		if (strcmp(no->ponteiro->nome, nome)==0)
			return 0;
	return 1;
}



/* Dado um nome, aumenta em 1 os pontos totais da equipa correspondente */
void aumenta_pontos(Tabela_hash *tabela, const char *nome)
{
	const size_t i = hash(nome, tabela->capacidade);
	No_hash *no;
	for (no=tabela->topos[i]; no != NULL; no=no->proximo)
		if (strcmp(no->ponteiro->nome, nome)==0)
		{
			no->ponteiro->pontos +=1;
			return;
		}
	return;
}

/* Dado um nome, retira 1 ponto aos pontos totais da equipa correspondente */
void retira_pontos(Tabela_hash *tabela, const char *nome)
{
	const size_t i = hash(nome, tabela->capacidade);
	No_hash *no;
	for (no=tabela->topos[i]; no != NULL; no=no->proximo)
		if (strcmp(no->ponteiro->nome, nome)==0)
		{
			no->ponteiro->pontos -=1;
			return;
		}
	return;
}




/***********************************************************************************************
*							FUNCOES PRINCIPAIS DAS EQUIPAS                                     *
***********************************************************************************************/


/* Adiciona uma nova equipa com nome unico. */
/* (Comando A) */
void adiciona_equipa(listE *lista_equipas, Tabela_hash *tabela, int contador)
{
	char nome[MAX_NOME];

	getchar();
	scanf("%[^:\n]", nome);
	if (verifica_e(tabela, nome) == 1)	/* Verifica que ainda nao existe aquela equipa */
		cria_Equipa(lista_equipas, nome, tabela);

	else printf("%d Equipa existente.\n", contador);

}


/* Procura uma equipa com o nome dado. Imprime tambem os pontos correspondentes. */
/* (Comando P) */
void procura_equipa(Tabela_hash *tabela,int contador)
{
	char nome[MAX_NOME];
	No_hash *equipa;

	getchar();
	scanf("%[^:\n]", nome);
	if(verifica_e(tabela, nome) == 1)
		printf("%d Equipa inexistente.\n", contador);
	else 
	{
		const size_t i = hash(nome, tabela->capacidade);
		for (equipa=tabela->topos[i]; equipa != NULL; equipa=equipa->proximo)
		/* Percorre as equipas do no correspondente */
			if (strcmp(equipa->ponteiro->nome, nome)==0)
			{
				printf("%d %s %d\n",contador, nome, equipa->ponteiro->pontos);
				return;
			}
	}
}

/* Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica. */
/* (Comando g) */
void vencedores(listE *lista_equipas, int contador)
{
	int max_pontos=0, n_equipas=0, i=0, n, j;
	Equipa *e_atual=lista_equipas->topo;
	char *guarda_nome, **vencedores;

	if (e_atual == NULL)								/* Lista de equipas vazia */
		return;
	for( ; e_atual != NULL; e_atual=e_atual->proximo)   
	{
		if (e_atual->pontos > max_pontos)
		{
			max_pontos = e_atual->pontos;				/* Atualiza o max.pontos */
			n_equipas = 1;								/* Reinicia a contagem de equipas */
		} 
		else if (e_atual->pontos == max_pontos)
			n_equipas+=1;
	}
		
	vencedores = can_fail_malloc(sizeof(char*) * n_equipas);		/* Aloca memoria para as eqs vencedoras */
	e_atual=lista_equipas->topo;
	for (; e_atual != NULL; e_atual=e_atual->proximo)
	{
		if(e_atual->pontos==max_pontos)					/* Faz a atribuicao dos nomes */
		{
			vencedores[i] = can_fail_malloc(sizeof(char)*strlen(e_atual->nome)+1);
			strcpy(vencedores[i++], e_atual->nome);
		} 
	}

	for(n=0; n< n_equipas - 1; n++)						/* Ordena por ordem lexicografica(nomes)*/
	{										
    	for(j=n+1; j< n_equipas;j++)
    	{
        	if(strcmp(vencedores[n], vencedores[j])>0)	
        	{
	            guarda_nome = vencedores[n];	
	            vencedores[n]= vencedores[j];
	            vencedores[j] = guarda_nome;
        	}
    	}
	}
	printf("%d Melhores %d\n", contador, max_pontos);
	for (i=0; i < n_equipas; i++)					   /* Imprime e liberta o espaco alocado */
	{
		printf("%d * %s\n", contador, vencedores[i]);
		free(vencedores[i]);
	}
	free(vencedores);
}



