#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Structs_Jogos.h"
#include "Structs_Equipas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Funcao que cria a Hashtable. */
hashtable2 * CreateHash2(){
	
	hashtable2 * tb = can_fail_malloc(sizeof(hashtable2));
	tb->heads2 = can_fail_calloc(HASH_SIZE, sizeof(hash_node2*));
	return tb; 
}


/* Funcao que cria um no na Hashtable. */
hash_node2 * AddNode2(Node_Jogo * new, hash_node2 * next){
	
	hash_node2 * nn = can_fail_malloc(sizeof(hash_node2));
	nn->pointer2 = new;
	nn->next2 = next;
	return nn;
}


/* Funcao que elimina um no na Hashtable. */
void DeleteNode2(hashtable2 * hash2, hash_node2 * n, int key){
	
	hash_node2 * atual, * seguinte;
	atual = hash2->heads2[key];
	seguinte = hash2->heads2[key]->next2;

	/* Verifica se o no que vai ser eliminado e igual a cabeca da gaveta da Hashtable. */
	if(n == atual){
		hash2->heads2[key] = seguinte;
		free(atual);
	}
	else{
		while(n != seguinte){
			atual = atual->next2;
			seguinte = seguinte->next2;
		}
		/* Verifica se o no que vai ser eliminado e o ultimo da gaveta da Hashtable. */
		if (seguinte->next2 == NULL){
			atual->next2 = NULL;
			free(seguinte);
		}
		else{
			atual->next2 = seguinte->next2;
			free(seguinte);
		}
	}
}


/* Funcao que cria uma lista duplamente ligada. */
Jogo * CreateGameList(){

	Jogo * l = can_fail_malloc(sizeof(Jogo));
	l->head = l->last = NULL;
	return l;
}


/* Funcao que verifica se o jogo existe. */
int CheckGame(hashtable2 * tb, char * buffer, int key){
	
	hash_node2 * n;
	for(n = tb->heads2[key]; n!=NULL; n = n->next2){
		if(strcmp(n->pointer2->nomej, buffer) == 0){
			return 0;
		}
	}
	return 1;
}


/* Funcao que acrescenta uma vitoria a uma certa equipa. */
void IncreaseWins(hashtable *tb, char * buffer, int key){
	
	hash_node * n;

	for(n = tb->heads[key]; n!=NULL; n = n->next){
		if(strcmp(n->pointer->nome, buffer) == 0){
			n->pointer->cont_ganhos += 1;
			break;
		}
	}	
}


/* Funcao que retira uma vitoria a uma certa equipa. */
void DecreaseWins(hashtable *tb, char * buffer, int key){
	
	hash_node * n;

	for(n = tb->heads[key]; n!=NULL; n = n->next){
		if(strcmp(n->pointer->nome, buffer) == 0){
			if (n->pointer->cont_ganhos == 0){
				break;
			}
			else{
				n->pointer->cont_ganhos -= 1;
				break;
			}
		}
	}
}


/* Funcao que gera as vitorias de cada equipa consoante o resultado alterado. */
void ChangeWins(int s1, int s2, int snew1, int snew2, hashtable * hash, hash_node2 * n){

	int key2 = Hashcode(n->pointer2->equipa1);
	int key3 = Hashcode(n->pointer2->equipa2);

	/* Caso o resultado antigo tenha sido a equipa1 a ganhar e o novo resultado seja a equipa2 a ganhar. */
	if((s1>s2) && (snew1<snew2)){
		DecreaseWins(hash, n->pointer2->equipa1, key2);
		IncreaseWins(hash, n->pointer2->equipa2, key3);
	}

	/* Caso o resultado antigo tenha sido a equipa2 a ganhar e o novo resultado seja a equipa1 a ganhar. */
	else if((s2>s1) && (snew2<snew1)){
		DecreaseWins(hash, n->pointer2->equipa2, key3);
		IncreaseWins(hash, n->pointer2->equipa1, key2);
	}

	/* Caso o resultado antigo tenha sido um empate. */
	else if(s1==s2){
		
		/* Caso o novo resultado seja a equipa1 a ganhar. */
		if(snew2<snew1) 
			IncreaseWins(hash, n->pointer2->equipa1, key2);
		
		/* Caso o novo resultado seja a equipa2 a ganhar. */
		else if(snew1<snew2)
			IncreaseWins(hash, n->pointer2->equipa2, key3);
	}

	/* Caso o novo resultado seja um empate. */
	else if(snew1==snew2){
		
		/* Caso o resultado antigo tenha sido a equipa1 a ganhar. */
		if((s1>s2)) 
			DecreaseWins(hash, n->pointer2->equipa1, key2);
		
		/* Caso o resultado antigo tenha sido a equipa2 a ganhar. */
		else if((s2>s1)) 
			DecreaseWins(hash, n->pointer2->equipa2, key3);
	}
}


/* Funcao que adiciona um novo jogo. */
void AddGame(int NL, Jogo * headJ, hashtable * hash, hashtable2 * hash2){
	
	Node_Jogo * new;
	char buffer1[C_MAX], buffer2[C_MAX], buffer3[C_MAX];
	int s1, s2, key, key2, key3;
	getchar();
	scanf("%1023[^:\n]:%1023[^:\n]:%1023[^:\n]:%d:%d",buffer1, buffer2, buffer3, &s1, &s2);
	key  = Hashcode(buffer1), key2 = Hashcode(buffer2), key3 = Hashcode(buffer3);
	
	if((CheckGame(hash2, buffer1, key))){
		if((!CheckTeam(hash, buffer2, key2)) && (!CheckTeam(hash, buffer3, key3))){
			
			/* Adiciona o novo no a lista duplamente ligada dos jogos. */
			new = can_fail_malloc(sizeof(Node_Jogo));
			new->previous2 = headJ->last;
			new->next2 = NULL;
			new->nomej = can_fail_malloc(sizeof(char) * (strlen(buffer1)+1));
			new->equipa1 = can_fail_malloc(sizeof(char) * (strlen(buffer2)+1));
			new->equipa2 = can_fail_malloc(sizeof(char) * (strlen(buffer3)+1));
			strcpy(new->nomej,buffer1);
			strcpy(new->equipa1,buffer2);
			strcpy(new->equipa2,buffer3);
			new->score1= s1;
			new->score2 = s2;
			if(headJ->last){
				headJ->last->next2 = new;
			}
			else{ 
				headJ->head =new;
			}
			headJ->last = new;

			/* Adiciona a vitoria a equipa que venceu. */
			if (s1>s2){
				IncreaseWins(hash, buffer2, key2);
			}
			else if(s2>s1){
				IncreaseWins(hash, buffer3, key3);
			}

			/* Adiciona o novo no a Hashtable dos Jogos. */
			hash2->heads2[key] = AddNode2(new, hash2->heads2[key]);
		}
		else{
			printf("%d Equipa inexistente.\n", NL);
		}
	}
	else{
		printf("%d Jogo existente.\n", NL);
	}
}


/* Funcao que procura um jogo. */
void SearchGame(int NL, hashtable2 * hash2){

	hash_node2 * n;
	char buffer[C_MAX];
	int key;
	getchar();
	scanf("%1023[^:\n]", buffer);
	key = Hashcode(buffer);
	
	if(!CheckGame(hash2, buffer, key)){
		for(n =hash2->heads2[key]; n!=NULL; n = n->next2){
			if(strcmp(n->pointer2->nomej, buffer) == 0){
				printf("%d %s %s %s %d %d\n", NL, n->pointer2->nomej, n->pointer2->equipa1, n->
					pointer2->equipa2, n->pointer2->score1, n->pointer2->score2);
				break;
			}
		}
	}
	else{
		printf("%d Jogo inexistente.\n", NL);
	}
}


/* Funcao que altera o resultado de um jogo. */
void ChangeScore(int NL, hashtable * hash, hashtable2 * hash2){

	hash_node2 * n;
	char buffer[C_MAX];
	int key, snew1, snew2;
	getchar();
	scanf("%1023[^:\n]:%d:%d", buffer, &snew1, &snew2);
	key = Hashcode(buffer);
	
	if(!CheckGame(hash2, buffer, key)){
		for(n = hash2->heads2[key]; n!= NULL; n = n->next2){
			if(strcmp(n->pointer2->nomej, buffer) == 0){
				int s1 = (n->pointer2->score1);
				int s2 = (n->pointer2->score2);
				n->pointer2->score1 = snew1;
				n->pointer2->score2 = snew2;

				/* Gera as vitorias consoante os novos resultados. */
				ChangeWins(s1, s2, snew1, snew2, hash, n);

				break;
			}
		}
	}
	else{
		printf("%d Jogo inexistente.\n", NL);
	}
}


/* Funcao que apaga um jogo. */
void DeleteGame(int NL, Jogo * headJ, hashtable * hash, hashtable2 * hash2){

	hash_node2 * n;
	char buffer[C_MAX];
	int key;
	getchar();
	scanf("%1023[^:\n]", buffer);
	key = Hashcode(buffer);
	
	if(!CheckGame(hash2, buffer, key)){
		for(n = hash2->heads2[key]; n!= NULL; n = n->next2){
			if(strcmp(n->pointer2->nomej, buffer) == 0){
				int key2 = Hashcode(n->pointer2->equipa1);
				int key3 = Hashcode(n->pointer2->equipa2);
				
				/* Retira a vitoria a equipa que tinha ganho- */
				if(n->pointer2->score1 > n->pointer2->score2){
					DecreaseWins(hash, n->pointer2->equipa1, key2);
				}
				else if(n->pointer2->score2 > n->pointer2->score1){
					DecreaseWins(hash, n->pointer2->equipa2, key3);
				}

				/* Retira o no a lista duplamente ligada dos jogos. */
				if(n->pointer2->previous2 == NULL){
					headJ->head = n->pointer2->next2;
				}
				else{
					n->pointer2->previous2->next2 = n->pointer2->next2;
				}
				if(n->pointer2->next2 == NULL){
					headJ->last = n->pointer2->previous2;
				}
				else {
					n->pointer2->next2->previous2 = n->pointer2->previous2;
				}
				free(n->pointer2->nomej);
				free(n->pointer2->equipa1);
				free(n->pointer2->equipa2);
				free(n->pointer2);

				/* Retira o no na Hashtable dos Jogos. */
				DeleteNode2(hash2, n, key);
				
				break;
			}
		}
	}
	else {
		printf("%d Jogo inexistente.\n", NL);
	}
}


/* Funcao que imprime todas os jogos existentes. */
void PrintGames(int NL, Jogo * headJ){

	Node_Jogo * atual = headJ->head;
	
	while(atual != NULL){
    	printf("%d %s %s %s %d %d\n", NL, atual->nomej, atual->equipa1, atual->equipa2,
    	 							  atual->score1, atual->score2);
        atual = atual->next2;
    }
}


/* Funcao que liberta a memoria alocada pela lista duplamente ligada. */
void DestroyJ(Jogo * headJ){
	
	Node_Jogo * temp;
	
	while(headJ->head) {
		temp = headJ->head->next2;
		free(headJ->head->nomej);
		free(headJ->head->equipa1);
		free(headJ->head->equipa2);
		free(headJ->head);
		headJ->head= temp;
	}
	free(headJ);
}


/* Funcao que liberta a memoria alocada pela Hashtable. */
void DestroyH2(hashtable2 * tb){

	hash_node2 * temp;
	size_t i;
	
	for (i=0; i < HASH_SIZE; i++){
		while(tb->heads2[i]){
			temp=tb->heads2[i]->next2;
			free(tb->heads2[i]);
			tb->heads2[i]=temp;
		}
	}
	free(tb->heads2);
	free(tb);
}