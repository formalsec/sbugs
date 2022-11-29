#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hashtable_jogos.h"

/*Funcao que inicializa a NULL os elementos da hashtable
de estruturas Jogo.*/
void HTinic_jogos(Jogo **jogos, int max)
{
	int i;

	for(i = 0; i < max; i++)
		jogos[i] = NULL;
}

/*Funcao que insere na hashtable um jogo.*/
void HTinsere_jogo(Jogo *jogo, Jogo **jogos, int dim)
{
	int chave;
	char *nome;
	Jogo *jogo_aux;
	nome = jogo->nome;

	/*Nota: a funcao 'hash' encontra-se no ficheiro "funcoes_aux.h"*/
	chave = hash(nome, dim);

	/*Se o elemento de chave 'chave' da hashtable for NULL,
	 coloca o jogo nessa posicao da tabela.*/
	if(jogos[chave] == NULL)
		jogos[chave] = jogo;

	/*Caso contrario, percorre a lista auto-referenciada de elementos
	com essa chave, e insere o jogo no fim da mesma. */
	else
	{
		jogo_aux = jogos[chave];

		while(jogo_aux->next != NULL)
			jogo_aux = jogo_aux->next;

		jogo_aux->next = jogo;
	}
}

/*Quicksort de estrutras Jogo, pela ordem em que foram introduzidas.*/
void quicksort_jogos(Jogo **jogos, int first, int last){
   int i, j, prim;
   Jogo *temp;

   if(first < last)
   {
      prim = first;
      i = first;
      j = last;

      while(i < j)
      {
         while((jogos[i]->linha_n <= jogos[prim]->linha_n) && (i < last))
            i++;

         while(jogos[j]->linha_n > jogos[prim]->linha_n)
            j--;

         if(i < j)
         {
            temp = jogos[i];
            jogos[i] = jogos[j];
            jogos[j] = temp;
         }
      }

      temp=jogos[prim];

      jogos[prim]=jogos[j];

      jogos[j]=temp;

      quicksort_jogos(jogos,first,j-1);
      quicksort_jogos(jogos,j+1,last);
   }
}

/*Funcao que lista os jogos de uma hashtable de jogos e
das suas listas ligadas.*/
void HTlista_jogos(Jogo **jogos, int dim, int conta_linhas)
{
	Jogo **tabela_jogos;
	Jogo *aux;
	int i, j = 0;

	tabela_jogos = (Jogo**) can_fail_malloc(sizeof(Jogo));

	/*Percorrer a hashtable de jogos.*/
	for(i = 0; i < dim; i++)
	{
		aux = jogos[i];

		/*Percorrer cada lista ligada da hashtable, e inserir
		cada jogo em tabel_jogos.*/
		while(aux != NULL)
		{
			tabela_jogos[j] = aux;
			aux = aux->next;
			j++;
			tabela_jogos = can_fail_realloc(tabela_jogos, (j+1)*sizeof(Jogo));
		}
	}

	/*Ordenacao de tabela_jogos pela ordem em que os respetivos jogos
	foram introduzidos.*/
	quicksort_jogos(tabela_jogos, 0, j-1);
	
	/*Print dos jogos da tabela_jogos*/
	for(i = 0; i < j; i++)
	{	
		printJogo(tabela_jogos[i], conta_linhas);
	}

	free(tabela_jogos);
}

/*Funcao que remove um jogo da hashtable.*/
void HTremove_jogo(Jogo* jogo, Jogo **jogos, int dim)
{
	int chave;
	Jogo *aux, *jogo_aux;
	char *nome;
	nome = jogo->nome;

	/*Nota: a funcao 'hash' encontra-se no ficheiro "funcoes_aux.h"*/
	chave = hash(nome, dim);

	aux = NULL;
	jogo_aux = jogos[chave];

	/*Encontrar o jogo na lista ligada do elemento da hashtable
	com a respetiva	chave.*/
	while(strcmp(nome, jogo_aux->nome) != 0)
	{
		aux = jogo_aux;
		jogo_aux = jogo_aux->next;
	}

	/*Se o jogo for o primeiro da lista ligada, sendo tambem o
	elemento da hashtable com a respetiva 'chave', esse elemento
	passa a ser o proximo jogo (o segundo) da lista ligada. */
	if(aux == NULL)
		jogos[chave] = jogo_aux->next;

	/*Caso contrario, 'recuar uma posicao' na lista ligada do
	jogo que se segue ao jogo desejado.*/
	else
		aux->next = jogo_aux->next;

	/*Libertar da memoria esse jogo.*/
	freeJogo(jogo_aux);
}

/*Funcao que procura um jogo pelo seu nome na hashtable.*/
Jogo* HTprocura_jogo(char *nome, Jogo **jogos, int dim)
{
	Jogo *jogo_aux;

	/*Nota: a funcao 'hash' encontra-se no ficheiro "funcoes_aux.h"*/
	int chave = hash(nome, dim);

	/*Se o elemento de chave 'chave' da hashtable for NULL,
	o jogo procurado nao existe, devolve NULL.*/
	if(jogos[chave] == NULL)
		return NULL;

	/*Caso contrario, percorre a lista ligada de jogos
	com essa chave.*/
	else
	{
		jogo_aux = jogos[chave];
		while((strcmp(nome, jogo_aux->nome) != 0) && (jogo_aux->next != NULL))
			jogo_aux = jogo_aux->next;

		/*Se se encontrar um jogo com o nome desejado, devolve
		esse jogo.*/
		if(strcmp(nome, jogo_aux->nome) == 0)
			return jogo_aux;

		/*Caso contrario, o jogo nao existe e devolve NULL.*/
		else
			return NULL;
	}

}

/*Funcao que liberta da memoria a hashtable, os seus elementos, e os
elementos das respetivas listas ligadas.*/
void HTfree_jogos(Jogo **jogos, int dim)
{
	Jogo *jogo_aux_1;
	Jogo *jogo_aux_2;
	int i;
	
	for(i = 0; i < dim ; i++)
	{
		jogo_aux_1 = jogos[i];

		while(jogo_aux_1 != NULL)
		{
			jogo_aux_2 = jogo_aux_1;
			jogo_aux_1 = jogo_aux_1->next;
			freeJogo(jogo_aux_2);
		}
	}

	free(jogos);
}