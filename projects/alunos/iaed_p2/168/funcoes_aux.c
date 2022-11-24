#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "funcoes_aux.h"

/*Funcao hash, cujo return sera a chave de uma estrutura na hashtable,
que sera: (soma dos ASCII dos caracteres do nome da estrutura) % (dimensao
da hashtable).*/
int hash(char *nome, int dim)
{
	int tamanho = 0, res, i = 0;

	while(nome[i] != '\0')
	{
		tamanho += nome[i];
		i++;
	}
	
	res = tamanho % dim;
	return res;
}


/*Funcao que cria um 'duplicado' de uma string.*/
/*char *strdup(char *palavra)
{
	char *palavra_dup;
	int size;

	size = strlen(palavra);
	palavra_dup =(char*) can_fail_malloc((size+1)* sizeof(char));
	strcpy(palavra_dup, palavra);

	return palavra_dup;
}*/