#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "game_hashtable.h"

static glink *gheads;	/* array com ponteiros para as listas ligadas que constitutem a hashtable */
static int M;			/* tamanho da hashtable */

/* funcao que da o indice relativo ao nome s */
int hash(char *s, int m) {
	int h = 0, a = 127;
	for (; *s != '\0' ; s++) {
		h = (a*h + *s) % m;
	}
	return h;
}

/* funcao que inicia a hashtable com todos os valores = NULL */
void Ginit(int m) {
	int i;
	M = m;
	gheads = can_fail_malloc(M*sizeof(glink));
	for (i = 0; i < M; i++) {
		gheads[i] = NULL;
	}
}

/* insere um jogo na hashtable */
void Ginsert(Jogo jogo) {
	int i = hash(jogo->nome, M);
	gheads[i] = GinsertBegin(gheads[i], jogo);
}

/* apaga um jogo da hashtable */
void Gdelete(Jogo jogo) {
	int i = hash(jogo->nome, M);
	gheads[i] = GremoveItem(gheads[i], jogo, 0);		/* terceiro argumento e zero, logo apenas apaga o no da lista ligada, nao o conteudo do jogo */
}

/* procura um joho na hashtable */
Jogo Gsearch(char *v) {
	int i = hash(v, M);
	return (Glookup(gheads[i], v))->jogo;
}

/* apaga toda a hashtable e o seu conteudo */
void Gclear() {
	int i;
	glink t;
	for (i = 0; i < M; i++) {
		if (gheads[i] != NULL) {
			for (t = gheads[i]; t != NULL; t = GremoveItem(t, t->jogo, 1));
		}
	}
	free(gheads);
}

/* verifica se existe um jogo com o nome indicado por v na hashtable */
int haJogo(char *v) {
	int i = hash(v, M);
	if (Glookup(gheads[i], v) == NULL) {
		return 0;
	}
	return 1;
}

