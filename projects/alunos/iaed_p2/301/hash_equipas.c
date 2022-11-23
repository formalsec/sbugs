#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>


/*funcao hash que gera um indice para a hash table consoante um certo nome*/
int hash(char *nome, int M){
	int h = 0, a = 127;
	for (; *nome != '\0'; nome++)
		h = (a*h + *nome) % M;
	return h;
}


/*funcao que inicializa a hash table das equipas ou dos vencedores*/
Hash_tableEq *init_tableEq(int size_table){
	Hash_tableEq  *new_t = (Hash_tableEq *) can_fail_malloc(sizeof(Hash_tableEq));
	new_t->capacity = size_table;
	new_t->table = (Hash_nodeEq **) can_fail_calloc(new_t->capacity, sizeof(Hash_nodeEq *));
	return new_t;
}


/*funcao que insere uma nova equipa na hash table*/
void insertEquipa_T(Hash_tableEq *t, NodeEq *equipaIns){
	int i = hash(equipaIns->nome, t->capacity);
	/*verifica se o primeiro no esta livre e insere*/
	if(t->table[i] == NULL){
		Hash_nodeEq *head = NULL;
		head = insertEquipa_N(head, equipaIns);
		t->table[i] = head;
	/*caso contrario vai procurar*/
	}else{
		Hash_nodeEq *head = t->table[i];
		insertEquipa_N(head, equipaIns);
	}
}


/*funcao auxiliar que insere o novo no da equipa que queremos adicionar*/
Hash_nodeEq *insertEquipa_N(Hash_nodeEq *head, NodeEq *equipaIns){
	Hash_nodeEq *new = (Hash_nodeEq *) can_fail_malloc(sizeof(Hash_nodeEq));
	new->equipa = equipaIns;
	new->next = NULL;
	if(head == NULL){
		head = new;
		return head;
	}else{
		/*procura ate haver um espaco livre para adicionar o no*/
		Hash_nodeEq *actual = head;
		while(actual->next != NULL){
			actual = actual->next;
		}
		actual->next = new;
	}
	return new;
}


/*funcao auxiliar que imprime a hash table das equipas ou dos vencedores*/
void printTableEq(Hash_tableEq *t){
	int i, vazios = 0, colisoes = 0;
	for (i = 0; i < t->capacity; i++){
		Hash_nodeEq *head = t->table[i];
		printf("%d: ", i);
		if(head == NULL){
			vazios++;
			printf("NULL");
		}else{
			Hash_nodeEq *current = head;
			colisoes--;
			while(current != NULL){
				colisoes++;
				printf("%s ", current->equipa->nome);
				current = current->next;
			}
		}
		printf("\n");
	}
	printf("Numero de vazios: %d\n", vazios);
	printf("Numero de colisoes: %d\n", colisoes);
}


/*funcao que liberta toda a memoria ocupada por uma hash table
de equipas ou de vencedores*/
void destroyTableEq(Hash_tableEq *t){
	int i;
	Hash_nodeEq *node, *next;
	for(i = 0; i < t->capacity;  i++){
		node = t->table[i];
		while(node != NULL){
			next = node->next;
			free(node);
			node = next;
		}
	}
	free(t->table);
	free(t);
}