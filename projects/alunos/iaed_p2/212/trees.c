#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "trees.h"

/*		Games Tree 	 	*/

/* Initialization of games tree. */
Tree *initTree(){
  return NULL;
}

/* Creates new node. */
Tree *newNode(struct node *x){
  Tree *n = (Tree*) can_fail_calloc(1,sizeof(Tree));
  n -> x = x;
  n -> height = 1;
  n -> l = n -> r = NULL;
  return n;
}

/* Returns the height of a tree. */
int height(Tree *h){
	if (h == NULL) return 0;
	return h->height;
}

/* Inerts a node in a tree. */
Tree *insertTree(Tree *t,struct node *x){
  Tree *n;
  if(t==NULL){
    n = newNode(x);
    return n;
  }
  else if(strcmp(x -> game.nome,t -> x -> game.nome) < 0){
    t -> l = insertTree(t -> l,x);
  }
  else{
    t -> r = insertTree(t -> r,x);
  }
  t = AVLbalance(t);
  return t;
}

/* Searches a game given its name. */
Tree *searchTree(Tree *t, char *nome){
	if(t == NULL) return NULL;
	if( strcmp( nome, t->x->game.nome) == 0) return t;
	if( strcmp(nome,t->x->game.nome) < 0)
		return searchTree(t-> l, nome);
	else
		return searchTree(t-> r, nome);
}

/* Goes to the max of a tree. */
Tree *max(Tree *h) {
	if (h==NULL || h->r==NULL) return h;
	else return max(h->r);
}

/* Removes a node from a tree and frees the memory. */
Tree *deleteR(Tree *h, char *nome, link *head, link *last, int nl) {
	Tree *aux;
	struct node *x;
	if (h == NULL) {
		printf("%d Jogo inexistente.\n", nl);
		return h;
	}
	else if (strcmp(nome,h->x->game.nome) < 0) h->l=deleteR(h->l,nome, head, last, nl);
	else if (strcmp(h->x->game.nome, nome) < 0) h->r=deleteR(h->r,nome, head, last, nl) ;
	else{
		if (h->l != NULL && h->r != NULL ) { /* caso 3 */
		aux=max(h->l);
		x = h->x;
		h->x = aux->x;
		aux->x = x;
		h->l=deleteR(h->l, aux->x->game.nome, head, last, nl);
		} else {
			aux=h;
			if ( h->l == NULL && h->r == NULL ) h=NULL; /* caso 1 */
			else if (h->l == NULL) h=h->r; /* caso 2a */
			else h=h->l; /* caso 2b */
			rmNode(aux->x, head, last);
			free(aux);
		}
	}
	h = AVLbalance(h);
	return h;
}

/* Frees the allocated memory of a node. */
Tree *freeR(Tree *h, link head, link last){
	if (h==NULL)return h;
	h->l=freeR(h->l, head, last);
	h->r=freeR(h->r, head, last);
	return deleteR(h,h->x->game.nome, &head, &last, 0);
}

/* Frees the entire tree. */
void freeTree(Tree *node){
       if (node != NULL) {
        freeTree(node->r);
        
        free(node->x->game.nome);
		free(node->x->game.equipa1);
		free(node->x->game.equipa2);
        free(node->x);

        freeTree(node->l);
        free(node);
    }
}

/* Left rotation. */
Tree *rotL(Tree *h){
	int hleft, hright, xleft, xright;
	Tree *x = h->r;
	h->r = x->l;
	x->l = h;

	hleft = height(h->l);
	hright = height(h->r);
	h->height = hleft > hright ? hleft + 1 : hright + 1;

	xleft = height(x->l);
	xright = height(x->r);
	x->height = xleft > xright ? xleft + 1 : xright + 1;

	return x;
}

/* Right rotation. */
Tree *rotR(Tree *h){
	int hleft, hright, xleft, xright;
	Tree *x = h->l;
	h->l = x->r;
	x->r = h;

	hleft = height(h->l);
	hright = height(h->r);
	h->height = hleft > hright ? hleft + 1 : hright + 1;

	xleft = height(x->l);
	xright = height(x->r);
	x->height = xleft > xright ? xleft + 1 : xright + 1;

	return x;
}

/* Double rotation Left Right. */
Tree *rotLR(Tree *h){
	if (h == NULL) return h;
	h->l = rotL(h->l);
	return rotR(h);
}

/* Double rotation Right Left. */
Tree *rotRL(Tree *h){
	if (h == NULL) return h;
	h->r = rotR(h->r);
	return rotL(h);
}

/* Balance factor. */
int balance(Tree *h){
	if(h == NULL) return 0;
	return height(h->l) - height(h->r);
} 

/* AVL Balancing function based on slides. */
Tree *AVLbalance(Tree *h){
	int balanceFactor, hleft, hright;
	if (h == NULL) return h;
	balanceFactor = balance(h);
	if(balanceFactor > 1) { /* More weight on the left */
		if (balance(h->l) >= 0) h = rotR(h);
		else h = rotLR(h);
	}
	else if(balanceFactor < -1){ /* More weight on the right */
		if (balance(h->r) <= 0) h = rotL(h);
		else h = rotRL(h);
	}
	else{
		hleft = height(h->l);
		hright = height(h->r);
		h->height = hleft > hright ? hleft + 1 : hright + 1;
	}
	return h;
} 

/*		Teams Tree 	 	*/

/* Initialization of teams tree. */
Tree2 *initTree2(){
  return NULL;
}

/* Creates new node. */
Tree2 *newNode2(char *x){
  Tree2 *n = (Tree2*) can_fail_calloc(1,sizeof(Tree2));
  n -> x = x;
  n -> height = 1;
  n -> l = n -> r = NULL;
  return n;
}

/* Returns the height of a tree. */
int height2(Tree2 *h){
	if (h == NULL) return 0;
	return h->height;
}

/* Inerts a node in a tree. */
Tree2 *insertTree2(Tree2 *t,char *x){
  Tree2 *n;
  if(t==NULL){
    n = newNode2(x);
    return n;
  }
  else if(strcmp(x,t->x) < 0){
    t -> l = insertTree2(t -> l,x);
  }
  else{
    t -> r = insertTree2(t -> r,x);
  }
  t = AVLbalance2(t);
  return t;
}

/* Searches a team given its name. */
Tree2 *searchTree2(Tree2 *t, char *nome){
  if(t == NULL) return NULL;
  if( strcmp(nome, t->x) == 0) return t;
  if( strcmp(nome, t->x) < 0)
    return searchTree2(t-> l, nome);
  else
    return searchTree2(t-> r, nome);
}

/* Left rotation. */
Tree2 *rotL2(Tree2 *h){
	int hleft, hright, xleft, xright;
	Tree2 *x = h->r;
	h->r = x->l;
	x->l = h;

	hleft = height2(h->l);
	hright = height2(h->r);
	h->height = hleft > hright ? hleft + 1 : hright + 1;

	xleft = height2(x->l);
	xright = height2(x->r);
	x->height = xleft > xright ? xleft + 1 : xright + 1;

	return x;
}

/* Right rotation. */
Tree2 *rotR2(Tree2 *h){
	int hleft, hright, xleft, xright;
	Tree2 *x = h->l;
	h->l = x->r;
	x->r = h;

	hleft = height2(h->l);
	hright = height2(h->r);
	h->height = hleft > hright ? hleft + 1 : hright + 1;

	xleft = height2(x->l);
	xright = height2(x->r);
	x->height = xleft > xright ? xleft + 1 : xright + 1;

	return x;
}

/* Double rotation Left Right. */
Tree2 *rotLR2(Tree2 *h){
	if (h == NULL) return h;
	h->l = rotL2(h->l);
	return rotR2(h);
}

/* Double rotation Right Left. */
Tree2 *rotRL2(Tree2 *h){
	if (h == NULL) return h;
	h->r = rotR2(h->r);
	return rotL2(h);
}

/* Balance factor. */
int balance2(Tree2 *h){
	if(h == NULL) return 0;
	return height2(h->l) - height2(h->r);
} 

/* AVL Balancing function based on slides. */
Tree2 *AVLbalance2(Tree2 *h){
	int balanceFactor, hleft, hright;
	if (h == NULL) return h;
	balanceFactor = balance2(h);
	if(balanceFactor > 1) { /* More weight on the left */
		if (balance2(h->l) >= 0) h = rotR2(h);
		else h = rotLR2(h);
	}
	else if(balanceFactor < -1){ /* More weight on the right */
		if (balance2(h->r) <= 0) h = rotL2(h);
		else h = rotRL2(h);
	}
	else{
		hleft = height2(h->l);
		hright = height2(h->r);
		h->height = hleft > hright ? hleft + 1 : hright + 1;
	}
	return h;
} 

/* Frees the entire tree. */
void freeTree2(Tree2 *node){
       if (node != NULL) {
        freeTree2(node->r);
        free(node->x);
        freeTree2(node->l);
        free(node);
    }
}

/* Travels through every node of a tree. */
void traverse(Tree2 *h, int *win){
	if (h == NULL)return;
	traverse(h->l, win);
	if (h -> win > *win) *win = h -> win;
	traverse(h->r, win);
}

/* Prints the teams with a certain amount of wins */
void printMostWins(Tree2 *t, int win, int nl){
  if (t != NULL){
    printMostWins(t -> l, win, nl);
    if (t->win == win) printf("%d * %s\n", nl, t -> x);
    printMostWins(t -> r, win, nl);
  }
}
