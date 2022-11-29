#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Hash.h"

/* Constroi uma hashtable. */
HashTable HASHinit()
{
	int i;
	HashTable hashtable;
	hashtable = (LinkedList *)can_fail_malloc(M * sizeof(LinkedList));
	for (i = 0; i < M; i++)
	{
		hashtable[i] = list_init();
	}
	return hashtable;
}

/* hash function */
int hash(char *v)
{
	int h = 0, a = 127;
	for (; *v != '\0'; v++)
	{
		h = (a * h + *v) % M;
	}
	return h;
}

/* Insere item na hashtable. */
void insert(HashTable hashtable, Item item)
{
	int i = hash(key(item));
	push(hashtable[i], item);
}

/* Apaga o item com chave k da hashtable. */
void delete (HashTable hashtable, Key k)
{
	int i = hash(k);
	remove_element(hashtable[i], k);
}

/* Retorna o item com chave k da hashtable. */
Item search(HashTable hashtable, Key k)
{
	int i = hash(k);
	return get_item(search_list(hashtable[i], k));
}

/* Destroi a hashTable e todas as estruturas associadas. */
void destroy_hash(HashTable hashtable)
{
	int i;
	for (i = 0; i < M; i++)
	{
		destroy_list(hashtable[i]);
	}
	free(hashtable);
}
