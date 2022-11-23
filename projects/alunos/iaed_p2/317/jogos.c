#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "jogos.h"

/*-----------------------funcoes hashtable jogos-----------------------*/

/*funcao de dispersao*/
int JH_hash(char *v, int M) {
	int h, a = 17, b = 19;
	for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
		h = (a*h + *v) % M;
	return h;
}

/*inicializa a hashtable de jogos colocando cada head a null*/
void inicializa_jogos_hash(JHnode *Jhash){
	int i;
	for (i = 0; i < HASH_M; i++) 
		Jhash[i] = NULL;
}

/*procura um jogo na hashtable de jogos*/
Jogo *JHsearch(JHnode *Jhash, char *nome) {
	int i = JH_hash(nome, HASH_M);
	JHnode node;

	/*procurar o jogo na lista ligada que comeca a partir da cabeca selecionada por "JH_hash"*/
	for(node = Jhash[i]; node != NULL; node = node -> next)
		if (strcmp(node -> jogo -> nome, nome) == 0)
			return node -> jogo;
	return NULL; /*return NULL se o jogo nao foi encontrado*/
}

/*insere um jogo na hashtable de jogos*/
void JHinsert(JHnode *Jhash, Jogo *jogo) {
	int i = JH_hash(jogo -> nome, HASH_M);
	JHnode node;
	node = can_fail_malloc(sizeof(struct node_jogo));
	node -> jogo = jogo;
	node -> next = Jhash[i];
	Jhash[i] = node;
}

/*apaga um jogo da hashtable de jogos*/
void JHdelete(JHnode *Jhash, char *nome) {
	int i = JH_hash(nome, HASH_M);
	JHnode node, node_ant;
	node = Jhash[i];
	/*verifica se o jogo que queremos apagar e a cabeca, ou seja, o primeiro elemento*/
	if (strcmp(node -> jogo -> nome, nome) == 0)
	    Jhash[i] = node -> next;
	/*procura o resto da lista ate encontrar o elemento a ser apagado*/
	else{
		for(node_ant = Jhash[i], node = node -> next; strcmp(node -> jogo -> nome, nome) != 0; node = node -> next)
			node_ant = node;
		node_ant -> next = node -> next;
	}

	/*dar free ao node retirado da lista e ao jogo dentro do node*/
	free_jogo(node -> jogo);
	free(node);
}

/*-----------------------funcoes jogos sistema-----------------------*/

void inicializa_jogos_sistema(Jogos_sistema *jogos_sis){
	jogos_sis -> tail = NULL;
	jogos_sis -> head = NULL;
}

void JSinsert(Jogos_sistema *jogos_sis, Jogo *jogo) {
	JHnode node = can_fail_malloc(sizeof(struct node_jogo));
	node -> jogo = jogo;
	node -> next = NULL;
	/*colocar o jogo na head se head for vazia*/
	if(jogos_sis -> head == NULL){
		jogos_sis -> head = node;
		jogos_sis -> tail = node;
		return;
	}
	/*colocar o jogo na tail*/
	jogos_sis -> tail -> next = node;
	jogos_sis -> tail = node;
}
void JSdelete(Jogos_sistema *jogos_sis, char *nome) {
	JHnode node, node_ant;
	node = jogos_sis -> head;
	/*verifica se o jogo a apagar esta na head*/ 
	if (strcmp(node -> jogo -> nome, nome) == 0){
	    jogos_sis -> head = node -> next;
	}
	/*procura no resto da lista removendo o node que possui o jogo*/
	else{
	    node_ant = jogos_sis -> head;
	    node = node -> next;
		while(strcmp(node -> jogo -> nome, nome) != 0) {
			node_ant = node;
			node = node -> next;
		}
		if(strcmp(node -> jogo -> nome, jogos_sis -> tail -> jogo -> nome) == 0)
			jogos_sis -> tail = node_ant;

		node_ant -> next = node -> next;
	}
	free(node);
}

/*-----------------------frees-----------------------*/

void free_jogo(Jogo *jogo){
	free(jogo -> nome);
	free(jogo);
}

void free_jogos_sis(Jogos_sistema *jogos_sis){
	JHnode JHnode_aux, JHtmp;
	for(JHnode_aux = jogos_sis -> head; JHnode_aux != NULL; ){
		JHtmp = JHnode_aux -> next;
		free(JHnode_aux);
		JHnode_aux = JHtmp;
	}
	free(jogos_sis);
}