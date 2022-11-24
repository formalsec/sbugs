#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HASHTABLE.h"

/* Ficheiro contem as funcoes utilizadas
para implementar a hashtable. */


/* Funcao hash
   Input: String
   Output: Chave(Indice para o bucket da hashtable)
   Descricao: Recebe uma string e calcula qual o 
   bucket adequado para a mesma na hashtable.
*/
unsigned int hash(char* str)
{
	unsigned int hash = 5381;

	while (*str)
	{
		hash = 33 * hash ^ (unsigned char) *str++;
	}
	return hash;
}

/* Funcao createDomainHash
   Input: Nada
   Output: Hashtable (inicializada)
   Descricao: Inicializa a hashtable alocando
   a memoria para a hashtable dos jogos e inicializa
   todos os buckets a NULL.
*/
equipaHash** criaEquipaHash()
{
	int i;
	equipaHash** equipaTable = can_fail_malloc(sizeof(equipaHash) * EQUIPAHASHMAX);

	for (i = 0; i < EQUIPAHASHMAX; i++)
	{
		*(equipaTable + i) = NULL;
	}

	return equipaTable;
}

/* Funcao freeDomainHash
   Input: Hashtable
   Output: Nada
   Descricao: Liberta toda a memoria alocada
   para a hashtable das equipas.
*/
void freeEquipaHash(equipaHash** equipaTable) 
{
	int i;
	equipaHash *current, *next;
	for (i=0; i < EQUIPAHASHMAX; i++) 
	{
		current = *(equipaTable + i);
		while (current != NULL)
		{
			next = current->collision;
			
			free(current->equipa);
			free(current);
			
			current = next;
		}
	}

	free(equipaTable);
}

/* Funcao encontraEquipa
   Input: Hashtable e nome equipa
   Output: Equipa (se existir) 
*/
equipaHash* encontraEquipa(equipaHash** equipaTable, char* chave)
{
	equipaHash* equipaPtr;
	int equipaIndex = hash(chave) % EQUIPAHASHMAX;
/* Este for percorre todos os elementos do bucket ate este
  ser NULL ou ate encontrar a equipa que pretendo */
	for (equipaPtr =*(equipaTable + equipaIndex);                  \
		equipaPtr != NULL && strcmp(equipaPtr->equipa, chave) != 0;  \
		equipaPtr = equipaPtr->collision);

	return equipaPtr;
}


/* Funcao AddEquipa
   Input: Hashtable e nome equipa
   Output: Nada
   Descricao: Calcula em que bucket adicionar a equipa.
*/
void AddEquipa(equipaHash** equipaTable, char* chave)
{
	equipaHash* equipaPtr;
  int n = 0;
	int equipaIndex = hash(chave) % EQUIPAHASHMAX;
  equipaPtr = *(equipaTable + equipaIndex);
  if (equipaPtr != NULL)
  {
    n = equipaPtr->bucketCheio;
  }

	equipaPtr = encontraEquipa(equipaTable, chave);
  equipaPtr = can_fail_malloc(sizeof(equipaHash));

  if (n > 0)
  {
    equipaPtr->bucketCheio = n + 1;
  }else
  {
    equipaPtr->bucketCheio = 1;
  }

	equipaPtr->equipa = can_fail_malloc(sizeof(char) * (strlen(chave) + 1));
	strcpy(equipaPtr->equipa, chave);

	equipaPtr->jogosGanhos = 0;
	equipaPtr->collision = *(equipaTable + equipaIndex);
	*(equipaTable + equipaIndex) = equipaPtr;
}

/* Funcao jogosGanhos
   Input: Hashtable e nome equipa
   Output: numero de jogos ganhos
   Descricao: Calcula quantos jogos foram ganhos
   por uma determinada equipa.
*/
int jogosGanhos(equipaHash** equipaTable, char* chave)
{
	equipaHash* equipaPtr;
	equipaPtr = encontraEquipa(equipaTable, chave);

	if (equipaPtr != NULL)
	{
		return equipaPtr->jogosGanhos;
	}
	return 0;
}

/* Funcao adicionaVitoria
   Input: Hashtable e nome equipa
   Output: NADA
   Descricao: Adiciona uma vitoria a uma equipa
*/
void adicionaVitoria(equipaHash** equipaTable, char* chave)
{
	equipaHash* equipaPtr;
	equipaPtr = encontraEquipa(equipaTable, chave);

	equipaPtr->jogosGanhos++;
}

/* Funcao removeVitoria
   Input: Hashtable e nome equipa
   Output: NADA
   Descricao: Remove uma vitoria a uma equipa
*/
void removeVitoria(equipaHash** equipaTable, char* chave)
{
	equipaHash* equipaPtr;
	equipaPtr = encontraEquipa(equipaTable, chave);

	if (equipaPtr->jogosGanhos > 0)
	{
		equipaPtr->jogosGanhos--;
	}
}

/* Funcao equipasMaisJogos
   Input: Hashtable e nome equipa
   Output: numero de equipas com mais jogos ganhos
   Descricao: Percorre toda a hashtable e descobre quais as equipas
   com mais jogos ganhos.
*/
int equipasMaisJogos(equipaHash** equipaTable, char* tab_final[EQUIPAHASHMAX])
{
    int i, e = 0, n, max = 0, a;
    char* tab_equipa[EQUIPAHASHMAX];
    equipaHash *current, *equipaPtr;

    for (i = 0; i < EQUIPAHASHMAX; i++)
    {
        equipaPtr = *(equipaTable + i);
        if (equipaPtr != NULL)
        {
          /* ciclo que corre os elementos do bucket ate 
          encontrar todos os jogos dentro desse bucket */
          for (a = 1; a <= equipaPtr->bucketCheio; a++)
          {
            for (current = *(equipaTable + i); current != NULL && current->bucketCheio != a; \
              current = current->collision);
            if (current->jogosGanhos >= max)
            {
              max = current->jogosGanhos;
              tab_equipa[e] = can_fail_malloc(sizeof(char) * (strlen(current->equipa) + 1));
              strcpy(tab_equipa[e], current->equipa);
              e++;
            }
          }
        }
    }
    if (e > 0)
    {
    	i = 0;
    	for (n = 0; n < e; n++)
    	{
        	if (jogosGanhos(equipaTable, tab_equipa[n]) == max)
        	{
        		tab_final[i] = can_fail_malloc(sizeof(char) * (strlen(tab_equipa[n]) + 1));
            strcpy(tab_final[i], tab_equipa[n]);
            i++;
        	}
    	}
    	n = 0;
    	while (n < e)
    	{
    		free(tab_equipa[n]);
    		n++;
    	}
    	return i;
    }
    return 0;
}