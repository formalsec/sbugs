#include "structs.h"
#include <string.h>
#include <stdio.h>


/*funcao que inicializa a hash table dos jogos*/
Hash_table *init_table(int size_table){
	Hash_table  *new_t = (Hash_table *) malloc(sizeof(Hash_table));
	new_t->table = (Hash_node **) calloc(size_table, sizeof(Hash_node *));
	new_t->capacity = size_table;
	return new_t;
}

/*funcao que insere um novo jogo*/
void insertJogo_T(Hash_table *t, Node *jogoIns){
	int i = hash(jogoIns->nome, t->capacity);
	/*verifica se o primeiro no esta livre e insere*/
	if(t->table[i] == NULL){
		Hash_node *head = NULL;
		head = insertJogo_N(head, jogoIns);
		t->table[i] = head;
		/*caso contrario vai procurar*/
	}else{
		Hash_node *head = t->table[i];
		insertJogo_N(head, jogoIns);
	}
}


/*funcao auxiliar que insere o novo no do jogo que queremos adicionar*/
Hash_node *insertJogo_N(Hash_node *head, Node *jogoIns){
	Hash_node *new = (Hash_node *) malloc(sizeof(Hash_node));
	new->jogo = jogoIns;
	new->next = NULL;
	if(head == NULL){
		head = new;
		return head;
	}else{
		/*procura ate haver um espaco livre para adicionar o no*/
		Hash_node *actual = head;
		while(actual->next != NULL){
			actual = actual->next;
		}
		actual->next = new;
	}
	return new;
}



/*funcao que remove um jogo da hash table dos jogos*/
Node* removeTable(Hash_table *t, Hash_tableEq *equipasT, char *aux, int nl){
	Hash_node *node, *prev;
	Node *nodeList;
	Hash_nodeEq *nodeVit;
	int h, h1, h2;
	h = hash(aux, t->capacity);
	node = t->table[h];
	/*verifica se o primeiro no (no indice h) da hash table e o jogo que queremos*/
	if(node != NULL && !strcmp(node->jogo->nome, aux)){
		h1 = hash(node->jogo->equipa1, equipasT->capacity);
		h2 = hash(node->jogo->equipa2, equipasT->capacity);
		/*a equipa que ganhou o jogo que vamos remover perde uma vitoria e em seguida
		e atualizada a lista de vencedores*/
		if(node->jogo->score1 > node->jogo->score2){
			nodeVit = equipasT->table[h1];
			while(strcmp(nodeVit->equipa->nome, node->jogo->equipa1)){
				nodeVit = nodeVit->next;
			} 
			nodeVit->equipa->vitorias--;
		}else if(node->jogo->score1 < node->jogo->score2){
			nodeVit = equipasT->table[h2];
			while(strcmp(nodeVit->equipa->nome, node->jogo->equipa2)){
				nodeVit = nodeVit->next;
			}
			nodeVit->equipa->vitorias--;
		}
		nodeList = node->jogo;
		t->table[h] = node->next;
		free(node);
		return nodeList;
	}
	/*caso nao se encontre no primeiro no entao procura na lista ligada do indice h*/
	while(node != NULL && strcmp(node->jogo->nome, aux)){
		prev = node;
		node = node->next;
	}
	/*se acabar a null e porque nao encontramos o jogo que queriamos*/
	if(node == NULL){
		printf("%d Jogo inexistente.\n", nl);
		nodeList = NULL;
		return nodeList;
	}
	nodeList = node->jogo;
	prev->next = node->next;
	h1 = hash(node->jogo->equipa1, equipasT->capacity);
	h2 = hash(node->jogo->equipa2, equipasT->capacity);
	/*a equipa que ganhou o jogo que vamos remover perde uma vitoria e em seguida
		e atualizada a lista de vencedores*/
	if(node->jogo->score1 > node->jogo->score2){
		nodeVit = equipasT->table[h1];
		while(strcmp(nodeVit->equipa->nome, node->jogo->equipa1)){
			nodeVit = nodeVit->next;
		}
		nodeVit->equipa->vitorias--;
	}else if(node->jogo->score1 < node->jogo->score2){
		nodeVit = equipasT->table[h2];
		while(strcmp(nodeVit->equipa->nome, node->jogo->equipa2)){
			nodeVit = nodeVit->next;
		}
		nodeVit->equipa->vitorias--;
	}
	free(node);
	return nodeList;
}



/*funcao que liberta toda a memoria ocupada por uma hash table
de equipas ou de vencedores*/
void destroyTable(Hash_table *t){
	int i;
	Hash_node *node;
	for(i = 0; i < t->capacity;  i++){
		while(t->table[i]){
			node = t->table[i]->next;
			free(t->table[i]);
			t->table[i] = node;
		}
	}
	free(t->table);
	free(t);
}

/*funcao auxiliar que imprime a hash table dos jogos*/
void printTable(Hash_table *t){
	int i, vazios = 0, colisoes = 0;
	for (i = 0; i < t->capacity; i++){
		Hash_node *head = t->table[i];
		printf("%d: ", i);
		if(head == NULL){
			vazios++;
			printf("NULL");
		}else{
			Hash_node *current = head;
			colisoes--;
			while(current != NULL){
				colisoes++;
				printf("%s ", current->jogo->nome);
				current = current->next;
			}
		}
		printf("\n");
	}
	printf("Numero de vazios: %d\n", vazios);
	printf("Numero de colisoes: %d\n", colisoes);
}


