#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "estrutura.h"


/*
*****************************
****Funcoes da hash table****
**********dos jogos**********
*****************************
*/

/*
*****************************
****Funcao que inicializa****
****a hash table dos jogos***
*****************************
*/
void inic_hash_j(jogo * aux[]){
	int i;
	for(i = 0; i < M_jogos; i++){
		/*poe a head das listas a NULL*/
		aux[i] = NULL;
	}
}


/*
*****************************
*****Funcao que liberta******
****a memoria de um jogo*****
*****************************
*/
void free_no(jogo * aux){
	free(aux -> nome);
	free(aux);
}

/*
*****************************
*****Funcao que liberta******
****a hash table dos jogos***
*****************************
*/
void free_hash_j(jogo * heads[]){
	jogo * aux;
	int i;
	for(i = 0; i < M_jogos; i++){
		while(heads[i]){
			aux = heads[i] -> next;
			free_no(heads[i]);
			heads[i] = aux;
		}
	}
}

/*
*****************************
***Funcao que da a posicao***
****da equipa ou do jogo*****
********na hash table********
*****************************
*/
int hash_s(char * nome){
	int h, a = 31245, b = 27183;
	for(h = 0; *nome != '\0'; nome++, a = a * b % (M_jogos - 1)){
		h = (a * h + *nome) % M_jogos;
	}
	return h;
}


/*
*****************************
*Funcao que adiciona um jogo*
********a hash table*********
*****************************
*/
jogo * adi_no(jogo * heads[], char nome[], equipa * equipa1, 
	        equipa * equipa2, int golos1, int golos2){
	int i = hash_s(nome);
	jogo * aux = can_fail_malloc(sizeof(jogo));
	aux -> next = heads[i];
	aux -> nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
	strcpy(aux -> nome, nome);
	aux -> equipa1 = equipa1;
	aux -> equipa2 = equipa2;
	aux -> golos1 = golos1;
	aux -> golos2 = golos2;
	heads[i] = aux;
	return aux;
}

/*
*****************************
****Funcao que retorna o*****
******ponteiro do jogo*******
*****************************
*/
jogo * procura_j(jogo * heads[], char * nome){
	int i = hash_s(nome);
	jogo * aux;
	for(aux = heads[i]; aux != NULL; aux = aux -> next){
		if(!strcmp(aux->nome, nome)){
			return aux;
		}
	}
	return NULL;
}

/*
*****************************
**Funcao que remove um jogo**
********da hash table********
*****************************
*/
void rem_no(jogo * heads[], char * nome){
	int i = hash_s(nome);
	jogo * aux, * aux_ant;
	for(aux = heads[i], aux_ant = NULL; aux != NULL; aux_ant = aux,
	    aux = aux -> next){
		if(!strcmp(aux->nome, nome)){
			if(aux == heads[i])
				heads[i] = aux -> next;
			else
				aux_ant -> next = aux -> next;
			free_no(aux);
			break;
		}
	}
}

/*
*****************************
****Funcoes da hash table****
*********das equipas*********
*****************************
*/

/*
*****************************
****Funcao que inicializa****
***a hash table das equipas**
*****************************
*/
void inic_hash_e(equipa * aux[]){
	int i;
	for(i = 0; i < M_jogos; i++){
		aux[i] = NULL;
	}
}

/*
*****************************
*****Funcao que liberta******
***a memoria de uma equipa***
*****************************
*/
void free_eq(equipa * aux){
	free(aux -> nome);
	free(aux);
}

/*
*****************************
*****Funcao que liberta******
**a hash table das equipas***
*****************************
*/
void free_hash_e(equipa * heads[]){
	equipa * aux;
	int i;
	for(i = 0; i < M_jogos; i++){
		while(heads[i]){
			aux = heads[i] -> next;
			free_eq(heads[i]);
			heads[i] = aux;
		}
	}
}

/*
*****************************
*****Funcao que adiciona*****
***uma equipa a hash table***
*****************************
*/
void adi_eq(equipa * heads[], char nome[]){
	int i = hash_s(nome);
	equipa * aux = can_fail_malloc(sizeof(equipa));
	aux -> next = heads[i];
	aux -> nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
	strcpy(aux -> nome, nome);
	aux -> vitoria = 0;
	heads[i] = aux;
}

/*
*****************************
****Funcao que retorna o*****
*****ponteiro da equipa******
*****************************
*/
equipa * procura_e(equipa * heads[], char * nome){
	int i = hash_s(nome);
	equipa * aux;
	for(aux = heads[i]; aux != NULL; aux = aux -> next){
		if(!strcmp(aux->nome, nome)){
			return aux;
		}
	}
	return NULL;
}

/*
*****************************
****Funcao que remove uma****
****equipa da hash table*****
*****************************
*/
void rem_eq(equipa * heads[], char * nome){
	int i = hash_s(nome);
	equipa * aux, * aux_ant;
	for(aux = heads[i], aux_ant = NULL; aux != NULL; aux_ant = aux,
	    aux = aux -> next){
		if(!strcmp(aux -> nome, nome)){
			if(aux == heads[i])
				heads[i] = aux -> next;
			else
				aux_ant -> next = aux -> next;
			free_eq(aux);
			break;
		}
	}
}

/*
*****************************
*******Funcoes da lista******
***********dos jogos*********
*****************************
*/

/*
*****************************
****Funcao que inicializa****
******a lista dos jogos******
*****************************
*/
lista_jogo * inic_lista(){
	lista_jogo * lista = can_fail_malloc(sizeof(lista_jogo));
	lista -> head = lista -> last = NULL;
	return lista;
}

/*
*****************************
*****Funcao que liberta******
******a lista dos jogos******
*****************************
*/
void free_lista(lista_jogo * lista){
	jogo_l * aux;
	while(lista -> head){
		aux = lista -> head -> next;
		free(lista -> head);
		lista -> head = aux;
	}
	free(lista);
}

/*
*****************************
*****Funcao que adiciona*****
*******um jogo a lista*******
*****************************
*/
void adiciona_fim(lista_jogo * lista, jogo * jogo){
	jogo_l * aux = can_fail_malloc(sizeof(jogo_l));
	aux -> prev = lista -> last;
	aux -> next = NULL;
	aux -> jogo_lista = jogo;
	if(lista -> last) 
		lista -> last -> next = aux;
	else{
		/*se for vazia*/
		lista -> head = aux;
	}
	lista -> last = aux;
}

/*
*****************************
****Funcao que remove um*****
*******jogo da lista*********
*****************************
*/
jogo * elimina_jo(lista_jogo * lista, char * nome){
	jogo_l * aux;
	jogo * aux_ret;
	/*encontra o jogo*/
	for(aux = lista -> head; aux != NULL; aux = aux -> next){
		if(!strcmp(aux -> jogo_lista -> nome, nome)){
			/*se for no incio*/
			if(aux -> prev == NULL)
				lista -> head = aux -> next;
			else
				aux -> prev -> next = aux -> next;
			/*se for no fim*/
			if(aux -> next == NULL)
				lista -> last = aux -> prev;
			else
				aux -> next -> prev = aux -> prev;
			aux_ret = aux -> jogo_lista;
			free(aux);
			return aux_ret;
		}
	}
	return NULL;
}

/*
*****************************
*******Funcoes da lista******
*********das equipas*********
*****************************
*/

/*
*****************************
****Funcao que inicializa****
*****a lista das equipas*****
*****************************
*/
lista_equipa * inic_lista_e(){
	lista_equipa * lista = can_fail_malloc(sizeof(lista_equipa));
	lista -> head = lista -> last = NULL;
	return lista;
}

/*
*****************************
*****Funcao que liberta******
*****a lista das equipas*****
*****************************
*/
void free_lista_e(lista_equipa * lista){
	equipa_l * aux;
	while(lista -> head){
		aux = lista -> head -> next;
		free(lista -> head);
		lista -> head = aux;
	}
	free(lista);
}

/*
*****************************
*****Funcao que adiciona*****
*****uma equipa a lista******
******ja no seu lugar********
*****************************
*/
int adiciona_lex(lista_equipa * lista, equipa * equipa){
	equipa_l * aux = can_fail_malloc(sizeof(equipa_l)), * aux_comp;
	aux -> equipa_lista = equipa;
	/*se a lista for vazia ou for para introduzir na ultima posicao*/
	if(!lista -> head || strcmp(equipa -> nome, lista -> last -> equipa_lista -> nome) > 0){
		aux -> prev = lista -> last;
		aux -> next = NULL;
		if(lista -> last) 
			lista -> last -> next = aux;
		else
			lista -> head = aux;
		lista -> last = aux;

		return 0;
	}
	/*percorre toda a lista*/
	for(aux_comp = lista -> head; aux_comp; aux_comp = aux_comp -> next){
		/*ve se e nessa posicao*/
		if(strcmp(equipa -> nome, aux_comp -> equipa_lista -> nome) < 0){
			aux -> next = aux_comp;
			/*se for para por no inicio*/
			if(lista -> head == aux_comp){
				lista -> head = aux;
				aux -> prev = NULL;
			}
			else {
				/*se for para por no meio*/
				aux -> prev = aux_comp -> prev;
				aux_comp -> prev -> next = aux;
			}
			aux_comp -> prev = aux;
			return 0;
		}
	}
	return 1;
}

