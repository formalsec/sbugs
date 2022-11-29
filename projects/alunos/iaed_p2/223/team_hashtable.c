#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "team_hashtable.h"

static tlink *theads;
static int N;

/* inicia a hashtable com todos os valores = NULL */
void Tinit(int n) {
	int i;
	N = n;
	theads = can_fail_malloc(N*sizeof(tlink));
	for (i = 0; i< N; i++) {
		theads[i] = NULL;
	}
}

/* insere uma equipa na hashtable */
void Tinsert(Equipa equipa) {
	int i = hash(equipa->nome, N);
	theads[i] = TinsertBegin(theads[i], equipa);
}

/* apaga uma equipa da hashtable */
void Tdelete(Equipa equipa) {
	int i = hash(equipa->nome, N);
	theads[i] = TremoveItem(theads[i], equipa, 0); /* terceiro argumento e zero porque apenas se pretende apaagar um no da lista ligada e nao o conteudo da equipa */
}

/* procura uma equipa na hashtable com o nome indicado por v */
Equipa Tsearch(char *v) {
	int i = hash(v, N);
	return (Tlookup(theads[i], v))->equipa;
}

/* verifica se existe uma equipa com o nome v na hashtable */
int haEquipa(char *v) {
	int i = hash(v, N);
	if (Tlookup(theads[i], v) == NULL) {
		return 0;
	}
	return 1;
}

/* apaga toda a hashtable e a informacao que ela contem */
void Tclear() {
	int i;
	tlink t;
	for (i = 0; i < N; i++) {
		if (theads[i] != NULL) {
			for (t = theads[i]; t != NULL; t = TremoveItem(t, t->equipa, 1));
		}
	}
	free(theads);
}