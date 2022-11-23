#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>


/*funcao que adiciona uma nova equipa*/
NodeEq* adicionaEquipas(NodeEq *headEq, Hash_tableEq *equipasT, int nl){
	int h, len;
	Hash_nodeEq *node;
	NodeEq *novaEquipa;
	char buffer[MAX_NOME];
	char *aux_string;
	/*recebe o nome da equipa*/
	scanf(" %[^\n]", buffer);
	len = strlen(buffer) + 1;
	aux_string = (char *) can_fail_malloc(sizeof(char) * len);
	strcpy(aux_string, buffer);
	h = hash(aux_string, equipasT->capacity);
	node = equipasT->table[h];
	/*verifica se a equipa ja existe*/
	while(node != NULL){
		if(!strcmp(node->equipa->nome, aux_string)){
			printf("%d Equipa existente.\n", nl);
			free(aux_string);
			return headEq;
		}
		node = node->next;
	}
	/*adiciona a equipa na lista ligada das equipas*/
	novaEquipa = (NodeEq *) can_fail_malloc(sizeof(NodeEq));
	novaEquipa->nome = (char *) can_fail_malloc(sizeof(char) * len);
	strcpy(novaEquipa->nome, aux_string);
	novaEquipa->vitorias = 0;
	novaEquipa->next = headEq;
	headEq = novaEquipa;
	/*insere a nova equipa na hash table das equipas*/
	insertEquipa_T(equipasT, headEq);
	/*atualiza a lista de vencedores*/
	free(aux_string);
	return headEq;
}


/*funcao auxiliar que lista todas as equipas*/
void listaEquipas(NodeEq *head){
	if(head == NULL) return;
	listaEquipas(head->next);
	printf("%s %d\n", head->nome, head->vitorias);
}


/*funcao que procura uma certa equipa e mostra as suas vitorais*/
void procuraEquipa(Hash_tableEq *equipasT, int nl){
	int h, len;
	Hash_nodeEq *node;
	char buffer[MAX_NOME];
	char *ptr_buffer;
	scanf(" %[^\n]", buffer);
	len = strlen(buffer) + 1;
	ptr_buffer = (char *) can_fail_malloc(sizeof(char) * len);
	strcpy(ptr_buffer, buffer);
	h = hash(ptr_buffer, equipasT->capacity);
	node = equipasT->table[h];
	/*procura o no na hash table das equipas correspondente a equipa que procuramos*/
	while(node != NULL){
		if(!strcmp(node->equipa->nome, ptr_buffer)){
			printf("%d %s %d\n", nl, node->equipa->nome, node->equipa->vitorias);
			free(ptr_buffer);
			return;
		}
		node = node->next;
	}
	printf("%d Equipa inexistente.\n", nl);
	free(ptr_buffer);
}