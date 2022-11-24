#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "iteam_hashtable.h"

static tlink *itheads;
static int L;

int hashint(int n, int m) {
	int h;
	h = n % m;
	return h;
}

void iTinit(int l) {
	int i;
	L = l;
	itheads = can_fail_malloc(L*sizeof(tlink));
	for (i = 0; i < L; i++) {
		itheads[i] = NULL;
	}
}

void iTinsert(Equipa equipa) {
	int i = hashint(equipa->vitorias, L);
	itheads[i] = TinsertEnd(itheads[i], equipa);
}

void iTdelete(Equipa equipa) {
	int i = hashint(equipa->vitorias, L);
	itheads[i] = TremoveItem(itheads[i], equipa, 0);
}

tlink iLastList() {
	int i;
	tlink t;
	for (i = 0; i < L; i++) {
		if (itheads[i] != NULL) {
			t = itheads[i];
		}
	}
	return t;
}

int equipasVazioQ() {
	int i;
	for (i = 0; i < L; i++) {
		if (itheads[i] != NULL) {
			return 0;
		}
	}
	return 1;
}

void iTclear() {
	int i;
	tlink t, tmp;
	for (i = 0; i < L; i++) {
		if (itheads[i] != NULL) {
			t = itheads[i];
			while (t != NULL) {
				tmp = t;
				t = t->next;
				free(tmp);
			}
		}
	}
	free(itheads);
}
