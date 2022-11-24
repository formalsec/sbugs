#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>


/*funcao que recebe um jogo no formato - a nome-jogo:equipa1:equipa2:score1:socre2*/
Node* adicionaJogo(Node *head, Hash_table *jogosT, Hash_tableEq *equipasT, int nl){
	int h1, h2, h3, control = 0, len1, len2, len3;
	Node *novoJogo;
	Hash_node *node;
	Hash_nodeEq *nodeEq1, *nodeEq2;
	char *aux_string, *aux_equipa1, *aux_equipa2;
	char nome_buffer[MAX_NOME], equipa1_buffer[MAX_NOME], equipa2_buffer[MAX_NOME];
	int score1_buffer, score2_buffer;
	/*recebe as informacoes do jogo num buffer*/
	scanf(" %[^:\n]s", nome_buffer);
	scanf(":%[^:\n]s", equipa1_buffer);
	scanf(":%[^:\n]s", equipa2_buffer);
	scanf(":%d:%d", &score1_buffer, &score2_buffer);
	/*guarda o tamanho do buffer para podermos allocar sem ocupar demasiado espaco*/
	len1 = strlen(nome_buffer) + 1;
	len2 = strlen(equipa1_buffer) + 1;
	len3 = strlen(equipa2_buffer) + 1;
	aux_string = (char *) can_fail_malloc(sizeof(char) * len1);
	aux_equipa1 = (char *) can_fail_malloc(sizeof(char) * len2);
	aux_equipa2 = (char *) can_fail_malloc(sizeof(char) * len3);
	strcpy(aux_string, nome_buffer);
	strcpy(aux_equipa1, equipa1_buffer);
	strcpy(aux_equipa2, equipa2_buffer);
	h1 = hash(aux_string, jogosT->capacity);
	node = jogosT->table[h1];
	/*verifica se o jogo ja existe na hash table dos jogos*/
	while(node != NULL){
		if(!strcmp(node->jogo->nome, aux_string)){
			printf("%d Jogo existente.\n", nl);
			free(aux_string);
			free(aux_equipa1);
			free(aux_equipa2);
	    	return head;
		}
		node = node->next;
	}
	/*indices da primeira e segunda equipa do jogo na hash table das equipas*/
	h2 = hash(aux_equipa1, equipasT->capacity);
	h3 = hash(aux_equipa2, equipasT->capacity);
	nodeEq1 = equipasT->table[h2];
	nodeEq2 = equipasT->table[h3];
	/*verifica se ambas as equipas existem*/
	while(nodeEq1 != NULL){
		if(!strcmp(nodeEq1->equipa->nome, aux_equipa1)){
			control++;
			break;
		} 
		nodeEq1 = nodeEq1->next;
	}
	while(nodeEq2 != NULL){
		if(!strcmp(nodeEq2->equipa->nome, aux_equipa2)){
			control++;
			break;
		} 
		nodeEq2 = nodeEq2->next;
	}
	if(control < 2){
		printf("%d Equipa inexistente.\n", nl);
		free(aux_string);
		free(aux_equipa1);
		free(aux_equipa2);
		return head;
	}
	/*adiciona uma vitoria na equipa que ganhou o jogo*/
	if(score1_buffer > score2_buffer){
		nodeEq1->equipa->vitorias++;
	}else if(score2_buffer > score1_buffer){
		nodeEq2->equipa->vitorias++;
	}
	/*adiciona no na lista ligada*/
	novoJogo = (Node *) can_fail_malloc(sizeof(Node));
	novoJogo->nome = (char *) can_fail_malloc(sizeof(char) * len1);
	novoJogo->equipa1 = (char *) can_fail_malloc(sizeof(char) * len2);
	novoJogo->equipa2 = (char *) can_fail_malloc(sizeof(char) * len3);
	strcpy(novoJogo->nome, nome_buffer);
	strcpy(novoJogo->equipa1, equipa1_buffer);
	strcpy(novoJogo->equipa2, equipa2_buffer);
	novoJogo->score1 = score1_buffer;
	novoJogo->score2 = score2_buffer;
	novoJogo->next = head;
	if(head != NULL) head->prev = novoJogo;
	head = novoJogo;
	/*chama funcao que insere o novo jogo na hash table dos jogos*/
	insertJogo_T(jogosT, head);
	free(aux_string);
	free(aux_equipa1);
	free(aux_equipa2);
	return head;
}




/*funcao que recebe um certo nome de um jogo e remove-o*/
Node* removeJogo(Hash_table *jogosT, Hash_tableEq *equipasT, Node *head, int nl){
	int len;
	char nome_buffer[MAX_NOME];
	char *nome_ptr;
	Node *node;
	node = head;
	scanf(" %[^:\n]s", nome_buffer);
	len = strlen(nome_buffer) + 1;
	nome_ptr = (char *) can_fail_malloc(sizeof(char) * len);
	strcpy(nome_ptr, nome_buffer);
	/*se a head da lista ligada estiver a null entao nao ha jogo para remover*/
	if(head == NULL){
		free(nome_ptr);
		printf("%d Jogo inexistente.\n", nl);
		return head;
	}
	/*se a head for o jogo que procuramos, removemos a head e chamamos a 
	funcao que remove o jogo da hash table dos jogos*/
	if(!strcmp(head->nome, nome_ptr)){
		node = head->next;
		if(node != NULL) node->prev = NULL;
		removeTable(jogosT, equipasT, nome_ptr, nl);
		free(nome_ptr);
		free(head->nome);
		free(head->equipa1);
		free(head->equipa2);
		free(head);
		return node;
	}else{
	/*procura o no que contem o jogo que procuramos e remove*/
		node = removeTable(jogosT, equipasT, nome_ptr, nl);
		if(!node){
			free(nome_ptr);
			return head;
		}
		node->prev->next = node->next;
		if(node->next != NULL) node->next->prev = node->prev;
		free(nome_ptr);
		free(node->nome);
		free(node->equipa1);
		free(node->equipa2);
		free(node);
		return head;
	}
}



/*funcao que altera o score de um certo jogo*/
void alteraScore(Hash_table *jogosT, Hash_tableEq *equipasT, int nl){
	Hash_node *node;
	Hash_nodeEq *nodeEq1, *nodeEq2;
	int h, h2, h3, new_score1, new_score2, len;
	char nome_buffer[MAX_NOME];
	char *buffer, *equipa1, *equipa2;
	scanf(" %[^:\n]s", nome_buffer);
	scanf(":%d:%d", &new_score1, &new_score2);
	len = strlen(nome_buffer) + 1;
	buffer = (char *) can_fail_malloc(sizeof(char) * len);
	strcpy(buffer, nome_buffer);
	h = hash(buffer, jogosT->capacity);
	node = jogosT->table[h];
	/*encontra o no na hash table dos jogo (no indice h) correspondente ao 
	jogo que queremos alterar*/
	while(node != NULL && strcmp(node->jogo->nome, buffer)) node = node->next;
	if(node == NULL){
		free(buffer);
		printf("%d Jogo inexistente.\n", nl);
		return;
	} 
	equipa1 = node->jogo->equipa1;
	equipa2 = node->jogo->equipa2;
	h2 = hash(equipa1, equipasT->capacity);
	h3 = hash(equipa2, equipasT->capacity);
	while(node != NULL){
		if(!strcmp(node->jogo->nome, buffer)){
			nodeEq1 = equipasT->table[h2];
			nodeEq2 = equipasT->table[h3];
			/*procura os nos na hash table das equipas correspondentes a primeira 
			e segunda equipa do jogo que queremos alterar*/
			while(strcmp(nodeEq1->equipa->nome, equipa1)) nodeEq1 = nodeEq1->next;
			while(strcmp(nodeEq2->equipa->nome, equipa2)) nodeEq2 = nodeEq2->next;
			/*consoante o novo resultado e o antigo adicionamos, retirarmos ou mantemos
			igual o numero de vitorias de cada equipa*/
			if(node->jogo->score1 > node->jogo->score2 && new_score1 < new_score2){
				nodeEq1->equipa->vitorias--;
				nodeEq2->equipa->vitorias++;
			}else if(node->jogo->score1 < node->jogo->score2 && new_score1 > new_score2){
				nodeEq1->equipa->vitorias++;
				nodeEq2->equipa->vitorias--;
			}else if(node->jogo->score1 == node->jogo->score2 && new_score1 > new_score2){
				nodeEq1->equipa->vitorias++;
			}else if(node->jogo->score1 == node->jogo->score2 && new_score1 < new_score2){
				nodeEq2->equipa->vitorias++;
			}else if(node->jogo->score1 > node->jogo->score2 && new_score1 == new_score2){
				nodeEq1->equipa->vitorias--;
			}else if(node->jogo->score1 < node->jogo->score2 && new_score1 == new_score2){
				nodeEq2->equipa->vitorias--;
			}
			node->jogo->score1 = new_score1;
			node->jogo->score2 = new_score2;
			free(buffer);
			return;
		}
		node = node->next;
	}
	printf("%d Jogo inexistente.\n", nl);
}


/*funcao que lista todos os jogos existentes*/
void listaJogos(Node *h, int nl){
	if(h == NULL) return;
	listaJogos(h->next, nl);
	printf("%d %s %s %s %d %d\n", nl, h->nome, h->equipa1, h->equipa2, h->score1, h->score2);
}


/*funcao que procura um certo jogo na hash table dos jogos*/
void procuraJogo(Hash_table *t, int nl){
	int h, len;
	char nome_buffer[MAX_NOME];
	char *nomeJogo;
	Hash_node *node;
	Node *nodeJ;
	scanf(" %s", nome_buffer);
	len = strlen(nome_buffer) + 1;
	nomeJogo = (char *) can_fail_malloc(sizeof(char) * len);
	strcpy(nomeJogo, nome_buffer);
	h = hash(nomeJogo, t->capacity);
	node = t->table[h];
	/*encontra o no correspondente ao jogo que queremos*/
	while(node != NULL){
		if(!strcmp(node->jogo->nome, nomeJogo)){
			nodeJ = node->jogo;
			printf("%d %s %s %s %d %d\n", nl, nodeJ->nome, nodeJ->equipa1, nodeJ->equipa2, 
				nodeJ->score1, nodeJ->score2);
			free(nomeJogo);
			return;	
		}
		node = node->next;
	}
	printf("%d Jogo inexistente.\n", nl);	
	free(nomeJogo);
}
