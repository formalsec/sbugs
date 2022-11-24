#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

struct ll{
	struct lig *el;
	int tipo;
	struct ll *next;
};

struct vertice {
	int cap,h,e,fl,n,tipo/*0 para fornecedores 1 para estacoes 2 para o hiper*/;
	struct ll *llig;
};

struct lig {
	struct vertice *o,*d;
	int fl,max,n;
};

struct llv{
	struct vertice *v;
	struct llv *next;
};

struct lll{
	struct lig *l;
	struct lll *next;
};

struct sol {
	struct llv *v;
	struct lll *l;
};

struct vertice *criarvertice(int cap,int tipo,int n){
	struct vertice *new;
	new = can_fail_malloc(sizeof(struct vertice));
	new->cap = cap;
	new->fl = cap;
	new->n = n;
	new->h = 0;
	new->e = 0;
	new->tipo = tipo;
	return new;
}

struct ll *addlig(struct vertice *v,struct lig *new,int tipo){
	struct ll *lnew = can_fail_malloc(sizeof(struct ll));
	lnew->el = new;
	lnew->tipo = tipo;
	if (v->llig == NULL)
		return lnew;
	lnew->next = v->llig;
	return lnew;
}

struct lig *criarligacao(int o,int ot,int d,int dt,int cap,int n,
						struct vertice **lv,struct vertice *hiper,
						struct vertice *s){
	struct lig *new;
	new = can_fail_malloc(sizeof(struct lig));
	if (ot == 0){
		new->o = hiper;
		hiper->llig = addlig(hiper,new,0);
	}
	else if (ot == 1){
		new->o = lv[o];
		lv[o]->llig = addlig(lv[o],new,0);
	}
	else {
		new->o = s;
		s->llig = addlig(s,new,0);
	}
	if (dt == 0){
		new->d = hiper;
		hiper->llig = addlig(hiper,new,1);
	}
	else {
		new->d = lv[d];
		lv[d]->llig = addlig(lv[d],new,1);
	}
	new->max = cap;
	new->n = n;
	new->fl = 0;
	return new;
}

void push(struct vertice *o,struct vertice *d,struct lig *v){
	int i;
	if (o == v->o){
		if (o->e <( v->max - v->fl)){
			if (o->e < o->fl)
				i = o->e;
			else
				i = o->fl;
		}
		else{
			if ((v->max - v->fl) < o->fl)
				i = v->max - v->fl;
			else
				i = o->fl;
		}

		v->fl += i;
		o->e = o->e -i;
		o->fl = o->fl -i;
		d->e = d->e +i;
		return;
	}
	else {
		if (o->e < v->fl)
			i = o->e;
		else
			i = v->fl;

		v->fl -= i;
		o->e = o->e -i;
		d->e = d->e +i;
		d->fl = d->fl +i;
		return;
	}
}

void relabel(struct vertice *o){
	struct ll *i;
	int k = o->llig->el->o->h;
	for (i = o->llig; i !=NULL; i = i->next){
		if (i->tipo == 0 && i->el->d->h < k 
			&& o->h <= i->el->d->h)
			k = i->el->d->h;
		else if (i->tipo == 1 && i->el->o->h < k 
			&& o->h <= i->el->o->h)
			k = i->el->d->h;
	}
	k++;
	o->h = k;
	return;
}

void discharge(struct vertice *o){
	struct ll *current;
	if (o->e > 0){
		current = o->llig;
		while (o->e > 0){
			if (current == NULL){
				relabel(o);
				current = o->llig;
			}
			else if (current != NULL && o->h == 1 + current->el->o->h 
					&& current->el->fl > 0){
				push(o,current->el->o,current->el);
			}
			else if(current != NULL && o->h == 1 + current->el->d->h
					&& current->el->fl < current->el->max 
					&& o->fl > 0){
				push(o,current->el->d,current->el);
			}
			else {
				current = current->next;
			}
		}
	}
	return;
}

void cortel(struct lig *l,struct sol *sol);

void corte(struct vertice *h,struct sol *sol){
	struct llv *new;
	struct ll *i;

	if (h->tipo == 0)
		return;
	if (h->fl == 0 && h->e == 0){
		new = can_fail_malloc(sizeof(struct llv));
		new->v = h;
		new->next = sol->v;
		sol->v = new;
		return;
	}
	for (i = h->llig; i != NULL;i = i->next){
		if (i->tipo == 1){
			cortel(i->el,sol);
		}
	}
	return;
}

void cortel(struct lig *l,struct sol *sol){
	struct lll *new;
	if (l->fl == l->max){
		new = can_fail_malloc(sizeof(struct lll));
		new->l = l;
		new->next = sol->l;
		sol->l = new;
		return;
	}
	corte(l->o,sol);
	return;
}

struct llv *smv(struct llv *f,struct llv *b){
	struct llv *r;
	if (f == NULL)
		return b;
	if (b == NULL)
		return f;
	if (f->v->n < b->v->n){
		r = f;
		r->next = smv(f->next,b);
	}
	else {
		r = b;
		r->next = smv(f,b->next);
	}
	return r;	
}

void msv(struct llv *v){
	struct llv *f,*b;
	if (v == NULL || v->next == NULL)
		return;
	f = v;
	b = v;
	while(b != NULL){
		b = b->next;
		if (b != NULL){
			b = b->next;
			f = f->next;
		}
	}
	b = f->next;
	f = v;
	msv(f);
	msv(b);
	v = smv(f,b);
	return;
}

struct lll *sml(struct lll *f,struct lll *b){
	struct lll *r;
	if (f == NULL)
		return b;
	if (b == NULL)
		return f;
	if (f->l->o->n < b->l->o->n ||
		(f->l->o->n == b->l->o->n && f->l->d->n < b->l->d->n)){
		r = f;
		r->next = sml(f->next,b);
	}
	else {
		r = b;
		r->next = sml(f,b->next);
	}
	return r;	
}

struct lll *msl(struct lll *l){
	struct lll *f,*b;
	if (l == NULL || l->next == NULL)
		return l;
	f = l;
	b = l->next;
	while(b != NULL){
		b = b->next;
		if (b != NULL){
			b = b->next;
			f = f->next;
		}
	}
	b = f->next;
	f->next = NULL;
	f = l;
	f = msl(f);
	b = msl(b);
	l = sml(f,b);
	return l;
}

void sortsol(struct sol *sol){
	msv(sol->v);
	sol->l = msl(sol->l);
	return;
}

int main(){
	int nf,ne,nl,o,d,cap,i,o1,d1;
	scanf("%d %d %d\n",&nf,&ne,&nl);
	struct vertice *hiper,*s,*lv[nf+ne],*u;
	struct lig *l[nl];
	struct sol *sol;
	struct llv *sv;
	struct lll *sl;
	hiper = criarvertice(o,2,1);
	s = criarvertice(o,2,0);
	for (i = 0; i < nf; ++i){
		scanf("%d",&o);
		lv[i] = criarvertice(o,0,i+2);
		l[1] = criarligacao(0,3,i,1,lv[i]->cap,0,lv,hiper,s);
		l[1]->fl = l[1]->max;
		s->e -= l[1]->max;
		l[1]->d->e = l[1]->max;
	}
	for (i = 0; i < ne; ++i){
		scanf("%d",&o);
		lv[i+nf] = criarvertice(o,1,i+nf+2);
	}
	for (i = 0; i < nl; ++i){
		scanf("%d %d %d\n",&o,&d,&cap);
		if(o == 1)
			o1 = 0;
		else {
			o1 = 1;
			o -= 2;
		}
		if(d == 1)
			d1 = 0;
		else {
			d1 = 1;
			d -= 2;
		}
		l[i] = criarligacao(o,o1,d,d1,cap,i,lv,hiper,s);
	}
	s->h = nf+ne+2;

	u = lv[0];
	i = 0;
	while(u != NULL && i < nf+ne){
		o = u->h;
		discharge(u);
		if (o < u->h){
			lv[i] = lv[0];
			lv[0] = u;
			i = 0;
		}
		i++;
		u = lv[i];
	}

	printf("%d\n",hiper->e);

	sol = can_fail_malloc(sizeof(struct sol));
	corte(hiper,sol);

	sortsol(sol);

	if (sol->v != NULL){
		for (sv = sol->v;sv != NULL;sv = sv->next){
			printf("%d",sv->v->n);
			if (sv->next != NULL)
				printf(" ");
		}
	}
	printf("\n");
	if (sol->l != NULL){
		for (sl = sol->l;sl != NULL;sl = sl->next){
			printf("%d %d\n",sl->l->o->n,sl->l->d->n);
		}
	}

	return 0;
}