#include "commands.h"

/* Command a reads name, team 1, team 2, and scores from each team
 * and stores it into a binary tree pointing to a double linked list. */
void cmd_a(link *head, link *last, Tree **g, Tree2 **t, int nl){
	struct jogo game;
	link aux = NULL;
	Tree2 *f = NULL,*h = NULL;
	char line[4][LINEMAX];

	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%u:%u", line[0], line[1], line[2], &game.score1, &game.score2);

	/* If there is already a game returns. */
	if (searchTree(*g, line[0]) != NULL){
		printf("%d Jogo existente.\n", nl);
		return;
	}
	
	/* Searches the teams and checks if they exist. */
	h = searchTree2(*t, line[1]);
	if (h == NULL){ printf("%d Equipa inexistente.\n", nl); return;}
	
	f = searchTree2(*t, line[2]);
	if (f == NULL){ printf("%d Equipa inexistente.\n", nl); return;}

	game.nome = malloc(sizeof(char)*(strlen(line[0])+1));
	strcpy(game.nome, line[0]);

	game.equipa1 = malloc(sizeof(char)*(strlen(line[1])+1));
	strcpy(game.equipa1, line[1]);

	game.equipa2 = malloc(sizeof(char)*(strlen(line[2])+1));
	strcpy(game.equipa2, line[2]);

	if (game.score1 > game.score2) h->win += 1;
	if (game.score1 < game.score2) f->win += 1;
	
	/* Creates a new node in the list and creates a pointer to it. */
	*head = insertEnd(*head, last, game, &aux);
	/* With the pointer to the linked list it's created a new node in the tree. */
	*g = insertTree(*g, aux);
}

/* Command A reads a name and stores it into a binary tree. */
void cmd_A(Tree2 **g, int nl){
	char *name, line[LINEMAX];

	scanf("%[^:\n]", line);

	if (searchTree2(*g, line) != NULL){ printf("%d Equipa existente.\n", nl); return;}

	name = malloc(sizeof(char)*(strlen(line)+1));
	strcpy(name, line);
	*g = insertTree2(*g, name);
}

/* Command l prints all games in order of insertion. */
void cmd_l(link head, int nl){
	print(head, nl);
}

/* Command p reads a name of a game and prints it. */
void cmd_p(Tree **g, int nl){
	Tree *f = NULL;
	char line[LINEMAX];

	scanf("%[^:\n]", line);

	f = searchTree(*g, line);
	if (f == NULL) {printf("%d Jogo inexistente.\n", nl); return;}
	
	printSingle(f->x, nl);
}

/* Command P reads a name of a team and prints it. */
void cmd_P(Tree2 **g, int nl){
	Tree2 *f = NULL;
	char line[LINEMAX];

	scanf("%[^:\n]", line);

	f = searchTree2(*g, line);
	if (f == NULL) {printf("%d Equipa inexistente.\n", nl); return;}
	
	printf("%d %s %d\n", nl, f->x, f->win);	
}

/* Command r reads a name of a game and removes it from the tree and the linked list. */
void cmd_r(link *head, link *last, Tree **g, Tree2 **t, int nl){
	char line[LINEMAX];
	Tree *f;
	Tree2 *e1, *e2;
	int sAux1, sAux2;

	scanf("%[^:\n]", line);

	f = searchTree(*g, line);
	if (f == NULL){ printf("%d Jogo inexistente.\n", nl); return;}
	
	sAux1 = f->x->game.score1;
	sAux2 = f->x->game.score2;

	if (sAux1 > sAux2) {							/* Removes a win from the winning team. */
		e1 = searchTree2(*t, f->x->game.equipa1);	/* Only searches for a team if needs to change score. */
		e1->win--;
	}
	if (sAux1 < sAux2) {
		e2 = searchTree2(*t, f->x->game.equipa2);
		e2->win--;
	}
	
	*g = deleteR(*g, line, head, last, nl);			/* Removes from tree and list. */
}

/* Command r reads a name, score 1 and score 2 of a game and changes the score to the new one. */
void cmd_s(Tree **g, Tree2 **t, int nl){
	Tree *f = NULL;
	Tree2 *e1, *e2;		/* Auxiliary trees to change the wins. */
	int s1, s2, sAux1, sAux2;
	char line[LINEMAX];

	scanf("%[^:\n]:%d:%d", line, &s1, &s2);

	f = searchTree(*g, line);
	if (f == NULL){ printf("%d Jogo inexistente.\n", nl); return;}
	
	sAux1 = f->x->game.score1;
	sAux2 = f->x->game.score2;

	f->x->game.score1 = s1;	/* Replaces the old score. */
	f->x->game.score2 = s2;

	e1 = searchTree2(*t, f->x->game.equipa1);	/* Searches the two teams. */
	e2 = searchTree2(*t, f->x->game.equipa2);
	
	/* Case 1 team 2 was previously winning. */
	if (sAux1 < sAux2){
		if (s1 == s2) e2->win--;	/* Teams are tied now. */
		if (s1 > s2){				/* First team is now winning. */
			e2->win--;
			e1->win++;
		}
	}
	/* Case 2 team 1 was previously winning. */
	if (sAux1 > sAux2){
		if (s1 == s2) e1->win--;	/* Teams are tied now. */
		if (s1 < s2){				/* Second team is now winning. */
			e1->win--;
			e2->win++;
		}
	}
	/* Case 3 the teams had tied. */
	if (sAux1 == sAux2){
		if (s1 < s2) e2->win++;		/* Second team is now winning. */
		if (s1 > s2) e1->win++;		/* First team is now winning. */
	}
}

/* Command g finds teams with the most wins and lists them in alphabetical order. */
void cmd_g(Tree2 *g, int nl){
	int win = 0;
	if (g != NULL){
		traverse(g, &win);
		printf("%d Melhores %d\n", nl, win);
		printMostWins(g, win, nl);
	}
}

/* Command x frees all the dynamicaly allocated memory. */
void cmd_x(Tree *g, Tree2 *t){
	freeTree(g);
	freeTree2(t);
}