#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "champs.h"


/*Estas duas funcoes sao respetivamente usadas para auxiliar e efetuar o bubbleSort
* de modo a ordenar a lista auxiliar para retonar alfabeticamente as equipas com mais
* jogos ganhos.*/
void swap(char *s1, char *s2){

	char aux[MAXC];

	strcpy(aux, s1);
	strcpy(s1, s2);
	strcpy(s2, aux);

}


void bubble(list *aux){

	int flag;
	node *ptr;

	do{
		flag = 0;
		ptr = aux->head;

		while(ptr){
			
			if(getHashKey(ptr->name) > getHashKey(ptr->next->name)){
				swap(ptr->name, ptr->next->name);
				flag = 1;
			}

			ptr = ptr->next;
		}
	}
	while(flag);
}


/*Esta funcao recebe a lista principal de equipas, procede a copia para uma lista auxiliar
* e, por ultimo, imprime a lista das equipas ordenadas alfabeticamente que ganharam o maior
* numero de jogos.*/
void findChamps(list *tms){

	int m_wins = 0;
	list *aux = startList();
	node *ptr = tms->head;

	if(tms == NULL){
		free(aux);
		return;
	}

	else{
		while(ptr){
			if(m_wins < ptr->won){
				m_wins = ptr->won;
			}

			ptr = ptr->next;
		}

		ptr = tms->head;

		while(ptr){
			if(m_wins == ptr->won){
				if(aux->head == NULL){
					aux->head = ptr;
				}

				else{
					ptr->previous = aux->end;
					aux->end->next = ptr;
				}

				aux->end = ptr;
			}
			printf("%s\n", ptr->name);
			ptr = ptr->next;
		}

		bubble(aux);

		if(aux != NULL){
			printf("%d Melhores %d\n", counter, m_wins);
			
			ptr = aux->head;

			while(ptr){
				printf("%d * %s\n", counter, ptr->name);
				ptr = ptr->next;
			}
		}
	}

	deleteList(aux, 1);
	free(aux);
}