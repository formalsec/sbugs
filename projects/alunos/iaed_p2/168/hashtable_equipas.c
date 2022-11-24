#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hashtable_equipas.h"

/*Funcao que inicializa a NULL os elementos da hashtable
de estruturas Equipa.*/
void HTinic_equipas(Equipa **equipas, int max)
{
	int i;

	for(i = 0; i < max; i++)
		equipas[i] = NULL;
}

/*Funcao que insere na hashtable uma equipa.*/
void HTinsere_equipa(Equipa *equipa, Equipa **equipas, int dim)
{
	int chave;
	char *nome;
	Equipa *equipa_aux;
	nome = equipa->nome;

	/*Nota: a funcao 'hash' encontra-se no ficheiro "funcoes_aux.h"*/
	chave = hash(nome, dim);

	/*Se o elemento de chave 'chave' da hashtable for NULL,
	 coloca a equipa nessa posicao da tabela.*/
	if(equipas[chave] == NULL)
		equipas[chave] = equipa;

	/*Caso contrario, percorre a lista auto-referenciada de elementos
	com essa chave, e insere a equipa no fim da mesma. */
	else
	{
		equipa_aux = equipas[chave];

		while(equipa_aux->next != NULL)
			equipa_aux = equipa_aux->next;

		equipa_aux->next = equipa;
	}
}

/*Funcao que procura uma equipa pelo seu nome na hashtable.*/
Equipa* HTprocura_equipa(char *nome, Equipa **equipas, int dim)
{
	Equipa *equipa_aux;

	/*Nota: a funcao 'hash' encontra-se no ficheiro "funcoes_aux.h"*/
	int chave = hash(nome, dim);

	/*Se o elemento de chave 'chave' da hashtable for NULL,
	a equipa procurada nao existe, devolve NULL.*/
	if((equipas[chave] == NULL))
		return NULL;

	/*Caso contrario, percorre a lista ligada de equipas
	com essa chave.*/
	else
	{
		equipa_aux = equipas[chave];
		while((strcmp(nome, equipa_aux->nome) != 0) && (equipa_aux->next != NULL))
			equipa_aux = equipa_aux->next;

		/*Se se encontrar uma equipa com o nome desejado, devolve
		essa equipa.*/
		if(strcmp(nome, equipa_aux->nome) == 0)
			return equipa_aux;

		/*Caso contrario, a equipa nao existe e devolve NULL.*/
		else
			return NULL;
	}
}

/*Quicksort de estrutras Equipa, por ordem lexicografica.*/
void quicksort_equipas(Equipa **equipas, int first, int last){
   int i, j, prim;
   Equipa *temp;

   if(first < last)
   {
      prim = first;
      i = first;
      j = last;

      while(i < j)
      {
         while((strcmp(equipas[i]->nome,equipas[prim]->nome) <= 0) && (i < last))
            i++;

         while(strcmp(equipas[j]->nome,equipas[prim]->nome) > 0)
            j--;

         if(i < j)
         {
            temp = equipas[i];
            equipas[i] = equipas[j];
            equipas[j] = temp;
         }
      }

      temp = equipas[prim];
      equipas[prim] = equipas[j];
      equipas[j] = temp;

      quicksort_equipas(equipas,first,j-1);
      quicksort_equipas(equipas,j+1,last);
   }
}

/*Funcao que lista sa equipas com maior numero de vitorias
de uma hashtable de equipas e das suas listas ligadas.*/
void HTencontra_mais_vitorias(Equipa **equipas, int dim, int conta_linhas)
{
	Equipa **equipas_vencedoras;
	Equipa *aux;
	int max_vitorias = 0;
	int i, j = 0;

	equipas_vencedoras = (Equipa**) can_fail_malloc(sizeof(Equipa));

	/*Encontra o maior numero de vitorias entre todas
	as equipas na base de dados de equipas
	(hashtable e listas ligadas).*/
	for(i = 0; i< dim; i++)
	{
		aux = equipas[i];
		while(aux != NULL)
		{
			if(aux->numero_vitorias > max_vitorias)
				max_vitorias = aux->numero_vitorias;
			aux = aux->next;
		}
	}

	/*Percorre a hashtable de equipas e as respetivas
	listas ligadas,	e insere as equipas com o maior numero 
	de vitorias em equipas_vencedoras*/
	for(i = 0;i < dim; i++)
	{
		aux = equipas[i];
		while(aux != NULL)
		{
			if(aux->numero_vitorias == max_vitorias)
			{
				equipas_vencedoras[j] = aux;
				j++;
				equipas_vencedoras = can_fail_realloc(equipas_vencedoras, (j+1)*sizeof(Equipa));
			}
			aux = aux->next;
		}
	}

	/*Se o maior numero de vitorias for '0', nao devolver nada.*/
	if(j == 0)
	{
		free(equipas_vencedoras);
		return;
	}

	/*Ordenacao de equipas_vencedoras por ordem lexicografica das equipas.*/
	quicksort_equipas(equipas_vencedoras, 0, j-1);


	printf("%d Melhores %d\n", conta_linhas, max_vitorias);

	/*Print de todas as equipas de 'equipas_vencedoras', ja ordenadas.*/
	for(i = 0; i < j; i++)
		printNome_Equipa(equipas_vencedoras[i], conta_linhas);

	/*Libertar da memoria 'equipas_vencedoras'.*/
	free(equipas_vencedoras);
}

/*Funcao que liberta da memoria a hashtable, os seus elementos, e os
elementos das respetivas listas ligadas.*/
void HTfree_equipas(Equipa **equipas, int dim)
{
	Equipa *equipa_aux_1;
	Equipa *equipa_aux_2;
	int i;
	
	for(i = 0;i < dim; i++)
	{
		equipa_aux_1 = equipas[i];
		while(equipa_aux_1 != NULL)
		{
			equipa_aux_2 = equipa_aux_1;
			equipa_aux_1 = equipa_aux_1->next;
			freeEquipa(equipa_aux_2);
		}
	}

	free(equipas);
}