#ifndef LIST_H_
#define LIST_H_

typedef struct node {
	int id;
	char *name;
	char *team1;
	char *team2;
	int score1;
	int score2;
	struct node *next;
} *link;

/* Create a match node */
link create(char *pbuffer[], int score1, int score2, int id);
link insert(char *pbuffer[], int score1, int score2, int id, link head);
void print(int nl, link head);

#endif