#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"


/*______________________________Destructor Functions______________________________*/

/* Frees allocated memory for a team */
void freeEquipa(equipa a) {
	free(a->name);
	free(a);
}

/* Frees allocated memory for a game */
void freeJogo(jogo a) {
	free(a->name);
	free(a);
}

/*_______________________________Print Functions_________________________________*/

/* Prints the name and number of victorys of a team */
void printEquipa(equipa a) {
	printf("%s %u\n", a->name, a->victorys);
}

/* Prints the name, the teams and the result of a game */
void printJogo(jogo a) {
	printf("%s %s %s %u %u\n", a->name, a->equipa1->name, a->equipa2->name, a->r1, a->r2);
}

/*_______________________________Constructor Functions___________________________*/

/* Allocates memory for a new team, creates it and returns a pointer to it */
equipa newEquipa(char *name) {
	equipa new = can_fail_malloc(sizeof(struct equipa));
	new->name = can_fail_malloc(sizeof(char)*strlen(name)+1);
	strcpy(new->name, name);
	new->victorys = ZERO;
	return new;
}

/* Allocates memory for a new game, creates it and returns a pointer to it */
jogo newJogo(char *name, equipa equipa1, equipa equipa2, int score1, int score2) {
	jogo new = can_fail_malloc(sizeof(struct jogo));
	new->name = can_fail_malloc(sizeof(char)*strlen(name)+1);
	strcpy(new->name, name);
	new->equipa1 = equipa1;
	new->equipa2 = equipa2;
	new->r1 = score1;
	new->r2 = score2;
	return new;
}

/*___________________________Manipulators_of_the_Data_Elements___________________*/

/* Removes a victory to a certain team */
void removeVictory(equipa a) {
	a->victorys--;
}

/* Adds a victory to a certain team */
void addVictory(equipa a) {
	a->victorys++;
}

/* Changes the score of a certain game */
void changeScore(jogo a, int s1, int s2) {
	a->r1 = s1;
	a->r2 = s2;
}