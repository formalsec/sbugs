#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tables.h"

/*Declaration of the variables used in the code */
static int Nequipas, Mequipas, Njogos, Mjogos;
static int sizeArrayE, sizeArrayJ;

/*Hash Tables
  Used to save time in search of teams or games */
static equipa *tableEquipas;
static element *tableJogos;

/*Lists
  Used to preserve order of insertion of teams and games */
static equipa *listaEquipas;
static jogo *listaJogos;


/*_________________________Initialization Functions________________________*/

/* Initializates the hash table of teams */
void tableEInit(int max) {
	int i;
	Nequipas = ZERO;
	Mequipas = findPrime(DOIS*max);
	tableEquipas = malloc(Mequipas*sizeof(equipa));
	for (i = ZERO; i < Mequipas; i++) {
		tableEquipas[i] = NULL;
	}
}

/* Initializates the hash table of games */
void tableJInit(int max) {
	int i;
	Njogos = ZERO;
	Mjogos = findPrime(DOIS*max);
	tableJogos = malloc(Mjogos*sizeof(element));
	for (i = ZERO; i< Mjogos; i++) {
		tableJogos[i] = malloc(sizeof(struct element));
		tableJogos[i]->game = NULL;
		tableJogos[i]->ocupado = ZERO;
	}
}

/* Initializates the list of teams */
void initArrayE(int max) {
	int i;
	sizeArrayE = DOIS*max;
	listaEquipas = malloc(sizeArrayE * sizeof(equipa));
	for (i = ZERO; i < sizeArrayE; i++) {
		listaEquipas[i] = NULL;
	}
}

/* Initializates the list of games */
void initArrayJ(int max) {
	int i;
	sizeArrayJ = DOIS*max;
	listaJogos = malloc(sizeArrayJ * sizeof(jogo));
	for (i = ZERO; i < sizeArrayJ; i++) {
		listaJogos[i] = NULL;
	}
}


/*______________________________Hash Functions________________________________*/
int hash1 (char *v, int M) {
	int h = ZERO, a = HASH_VALUE_1;

	for (; *v != '\0'; v++) {
		h = (a*h + *v) % M;
	}
	return h;
}

int hash2(char *v, int M) {
	int h, a = HASH_VALUE_2, b = HASH_VALUE_3;

	for (h = ZERO; *v != '\0'; v++, a = a*b % (M-UM)) {
		h = (a*h + *v) % M;
	}
	return h;
}


/*____________________________Insertion Functions_____________________________*/

/* Inserts a team to the list of teams
   Uses the auxiliar function expandArrayE(), when the number of teams is half of the
   size of the list, to make it dynamic */
void insertArrayE(equipa e) {
	listaEquipas[Nequipas] = e;
	if(Nequipas+UM > sizeArrayE/DOIS) {
		expandArrayE();
	}
}

/* Inserts a game to the list of games
   Uses the auxiliar function expandArrayJ(), when the number of games is half of the
   size of the list, to make it dynamic */
int insertArrayJ(jogo e) {
	listaJogos[Njogos] = e;
	if(Njogos+UM > sizeArrayJ/DOIS) {
		expandArrayJ();
	}
	return Njogos;
}

/* Inserts a team to the hash table
   Uses the auxiliar function expandTableE(), when the number of teams is half of the
   size of the table, to make it dynamic */
void tableEInsert(equipa a) {
	char *name = a->name;
	int i = hash1(name, Mequipas);
	int k = hash2(name, Mequipas);
	while (tableEquipas[i] != NULL) {
		/* If the hash value repeats itself, the hash table will expand
		to avoid an infinite cycle */
		if (i == (i+k) % Mequipas) {
			expandTableE();
			i = hash1(name, Mequipas);
			k = hash2(name, Mequipas);
		} else {
			i = (i+k) % Mequipas;
		}
	}
	tableEquipas[i] = a;
	if (Nequipas++ > Mequipas/DOIS) {
		expandTableE();
	}
}

/* Inserts a game to the hash table
   Uses the auxiliar function expandTableJ(), when the number of games is half of the
   size of the table, to make it dynamic */
void tableJInsert(jogo a, int pos) {
	char *name = a->name;
	int i = hash1(name, Mjogos);
	int k = hash2(name, Mjogos);
	while (tableJogos[i]->game != NULL) {
		/* If the hash value repeats itself, the hash table will expand
		to avoid an infinite cycle */
		if (i == (i+k) % Mjogos) {
			expandTableJ();
			i = hash1(name, Mjogos);
			k = hash2(name, Mjogos);
		} else {
			i = (i+k) % Mjogos;
		}
	}
	tableJogos[i]->game = a;
	tableJogos[i]->ocupado = UM;
	tableJogos[i]->game->idNumber = pos;
	if (Njogos++ > Mjogos/DOIS) {
		expandTableJ();
	}
}


/*_____________________________Searching Functions________________________________*/

/* Searches a team by its name on the hash table of teams and returns its pointer,
   if found, or NULL, if not. */
equipa tableESearch(char *name) {
	int i = hash1(name, Mequipas);
	int k = hash2(name, Mequipas);
	int aux = i;
	while (tableEquipas[i] != NULL) {
		if (strcmp(name, tableEquipas[i]->name) == ZERO) {
			return tableEquipas[i];
		}
		i = (i+k) % Mequipas;
		if (i == aux) {
			break;
		}
	}
	return NULL;
}

/* Searches a game by its name on the hash table of games and returns its pointer,
   if found, or NULL, if not. */
element tableJSearch(char *name) {
	int i = hash1(name, Mjogos);
	int k = hash2(name, Mjogos);
	int aux = i;
	while (tableJogos[i]->ocupado != ZERO) {
		if (tableJogos[i]->game != NULL && strcmp(name, tableJogos[i]->game->name) == ZERO) {
			return tableJogos[i];
		}
		i = (i+k) % Mjogos;
		if (i == aux) {
			break;
		}
	}
	return NULL;
}


/*______________________________Removing Functions__________________________________*/

/* Removes a game from the list of games 
   Note: This function receives the idNumber of a game and accesses the list directly
   in the wanted position to save time. */
void removeArrayJ(int pos) {
	int i;
	if (pos+UM == Njogos){
		listaJogos[pos] = NULL;
	} else {
		for (i = pos; i < Njogos-UM; i++) {
			listaJogos[i] = listaJogos[i+UM];
			listaJogos[i]->idNumber--;
		}
	}
}

/* Removes a game from the hash table of games
   Note: This function also updates the number of victorys of the teams
   in the game that was removed. */
void tableJDelete(jogo j) {
	removeArrayJ(j->idNumber);
	if (j->r1 > j->r2) {
		removeVictory(j->equipa1);
	}
	if (j->r2 > j->r1) {
		removeVictory(j->equipa2);
	}
	Njogos--;
}


/*______________________________Printing Functions________________________________*/

/* Prints all the games by order of insertion using the list of games */
void printJogos(int linha) {
	int i;
	for (i = ZERO; i < Njogos; i++) {
		printf("%d ", linha);
		printJogo(listaJogos[i]);
	}
}

/* Prints the teams with the most wins by alphabetical order */
void printEquipas(int linha, int n) {
	int i;
	printf("%d Melhores %u\n", linha, listaEquipas[ZERO]->victorys);
	for (i = ZERO; i < n; i++) {
		printf("%d * %s\n", linha, listaEquipas[i]->name);
	}
}


/*_____________________________Destructor Functions_______________________________*/

/* Frees all the memory allocated for the teams and for the list of teams */
void freeArrayE() {
	int i;
	for (i = ZERO; i < Nequipas; i++) {
		freeEquipa(listaEquipas[i]);
	}
	free(listaEquipas);
}

/* Frees all the memory allocated for the games and for the list of games */
void freeArrayJ() {
	int i;
	for (i = ZERO; i < Njogos; i++) {
		freeJogo(listaJogos[i]);
	}
	free(listaJogos);
}

/* Frees the allocated memory for the hash table of teams
   Note: It doesnt free the memory allocated for each team, because
   that memory was already freed when the list of teams was freed. */
void freeTableE() {
	free(tableEquipas);
}

/* Frees the allocated memory for the hash table of games
   Note: It doesnt free the memory allocated for each game, because
   that memory was already freed when the list of games was freed. */
void freeTableJ() {
	int i;
	for (i = ZERO; i < Mjogos; i++) {
		free(tableJogos[i]);
	}
	free(tableJogos);
}


/*______________________________Auxiliar Functions______________________________*/

/* Function that finds the biggest prime number before a bigger number
   Note: The prime numbers are used in the hashing to avoid collisions */
int findPrime(int n) {
	int i, j, flag=ZERO;
    for(i=n; i>UM; i--) {
        for (j = i/DOIS; j >= UM; j--) {
            if(i%j==ZERO && j!=UM) {
	            flag = ZERO;
	            break;
	        } else {
	        	flag = UM;
	        }
    	}
    	if(flag == UM) {
        	break;
      	}
   }
   return i;
}

/* Function that expands the hash table of teams by re-initializing it with double
   the size. */
void expandTableE() {
	int i, auxM = Mequipas;
	equipa *aux = tableEquipas;
	tableEInit(Mequipas+Mequipas);
	for (i = ZERO; i < auxM; i++) {
		if (aux[i] != NULL) {
			tableEInsert(aux[i]);
		}
	}
	free(aux);
}

/* Function that expands the hash table of games by re-initializing it with double
   the size. */
void expandTableJ() {
	int i, auxM = Mjogos;
	element *aux = tableJogos;
	tableJInit(Mjogos+Mjogos);
	for (i = ZERO; i < auxM; i++) {
		if (aux[i]->game != NULL) {
			tableJInsert(aux[i]->game, aux[i]->game->idNumber);
		}
		free(aux[i]);
	}
	free(aux);
}

/* Function that expands the list of teams by re-initializing it with double
   the size. */
void expandArrayE() {
	int i, auxS = sizeArrayE;
	equipa *aux = listaEquipas;
	initArrayE(sizeArrayE+sizeArrayE);
	for (i = ZERO; i < auxS; i++) {
		if (aux[i] != NULL) {
			listaEquipas[i] = aux[i];
		}
	}
	free(aux);
}

/* Function that expands the list of games by re-initializing it with double
   the size. */
void expandArrayJ() {
	int i, auxS = sizeArrayJ;
	jogo *aux = listaJogos;
	initArrayJ(sizeArrayJ+sizeArrayJ);
	for (i = ZERO; i < auxS; i++) {
		if (aux[i] != NULL) {
			listaJogos[i] = aux[i];
		}
	}
	free(aux);
}

/* Function that puts the teams with the most wins at the top of the list */
int putBiggerOnTop() {
	int i, j = UM;
	equipa aux;
	unsigned int vit = listaEquipas[ZERO]->victorys;
	for (i = UM; i < Nequipas; i++) {
		if (listaEquipas[i]->victorys > vit) {
			aux = listaEquipas[ZERO];
			listaEquipas[ZERO] = listaEquipas[i];
			listaEquipas[i] = aux;
			vit = listaEquipas[ZERO]->victorys;
			j = UM;
		}
		if (listaEquipas[i]->victorys == vit && j != i) {
			aux = listaEquipas[j];
			listaEquipas[j] = listaEquipas[i];
			listaEquipas[i] = aux;
			j++;
		}
		if (listaEquipas[i]->victorys == vit && j == i) {
			j++;
		}
	}
	return j;
}

/* Part of the heapsort algorithm */
void heapify(int n, int i) {
	/* Find largest among root, left child and right child */
	int largest = i;
	int left = DOIS * i + UM;
	int right = DOIS * i + DOIS;
	equipa aux;

	if (left < n && strcmp(listaEquipas[left]->name, listaEquipas[largest]->name) > ZERO) {
		largest = left;
	}

	if (right < n && strcmp(listaEquipas[right]->name, listaEquipas[largest]->name) > ZERO) {
		largest = right;
	}

	/* Swap and continue heapifying if root is not largest */
	if (largest != i) {
		aux = listaEquipas[i];
		listaEquipas[i] = listaEquipas[largest];
		listaEquipas[largest] = aux;
		heapify(n, largest);
	}
}

/* Heapsort - algorithm with good time and space complexity
   Used to sort alphabetically, the teams with the most wins, which are at the top
   of the list of teams. */
void heapsort(int n) {
	int i;
	equipa aux;
	/* Build max heap */
	for (i = n / DOIS - UM; i >= ZERO; i--) {
		heapify(n, i);
	}

	/* Heap sort */
	for (i = n - UM; i >= ZERO; i--) {
		aux = listaEquipas[ZERO];
		listaEquipas[ZERO] = listaEquipas[i];
		listaEquipas[i] = aux;
		/* Heapify root element to get highest element at root again */
		heapify(i, ZERO);
	}
}

/* Function that returns the number of teams on the list */
int getNequipas() {
	return Nequipas;
}
