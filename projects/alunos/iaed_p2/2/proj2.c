#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "doublinklist.h"

#define STR_SIZE 1024
#define MAX_VENCEDORES 99999	/* nr max de equipas com mais vitorias */
#define MAX_EQUIPAS_INIC 13		/* nr max inicial de equipas */
#define MAX_JOGOS_INIC 13		/* nr max inicial de jogos */


int line = 1;					/* linha da stream de input */
char nome[STR_SIZE];			/* nome de jogo ou equipa (muito usado nos comandos) */

/* tabela de dispersao dos jogos e das equipas */
HashTable htJogos, htEquipas;


/* cabeca da lista duplamente linkada dos jogos */
link head = NULL;		


/* Adiciona um novo jogo */
void case_a () {
	
	char nome1[STR_SIZE], nome2[STR_SIZE];	/* nome das equipas */
	int sc1, sc2;							/* score de cada equipa */
	pEquipa eq1, eq2;						/* ponteiros para as equipas */
	
	scanf(" %[^:]:%[^:]:%[^:]:%d:%d", nome, nome1, nome2, &sc1, &sc2);
	eq1 = (pEquipa) HTsearch(nome1, &htEquipas);
	eq2 = (pEquipa) HTsearch(nome2, &htEquipas);
	if(HTsearch(nome, &htJogos) != NULL) {
	
		printf("%d Jogo existente.\n", line);
	}
	else if(eq1 == NULL || eq2 == NULL) {
					
		printf("%d Equipa inexistente.\n", line);
	}
	else {	
		if(sc1 > sc2)		/* incrementa nr jogos ganhos da eq vencedora */
			eq1->ganhos++;
		if(sc2 > sc1)
			eq2->ganhos++;
		DLinsertEnd(NEWjogo(nome, eq1, eq2, sc1, sc2));	/* insere jogo no fim da lista */
		HTinsert((void*) head->prev, &htJogos);			/* adiciona esse link a tabela */
	}
}


/* Lista todos os jogos introduzidos. Ordem de insercao */
void case_l () {
	
	link p = head;
	while(p != NULL) {
		
		printf("%d %s %s %s %d %d\n", line,
				p->v->nome,
				p->v->eq1->nome,
				p->v->eq2->nome,
				p->v->sc1,
				p->v->sc2);
		p = p->next;
	}
}


/* Procura um jogo com o nome dado */
void case_p () {
	
	link p;					/* ponteiro para o no da lista de jogos */

	scanf(" %[^\n]", nome);
	p = (link) HTsearch(nome, &htJogos);
	if(p == NULL) {
					
		printf("%d Jogo inexistente.\n", line);
	}
	else {
	
		printf("%d %s %s %s %d %d\n", line,
				p->v->nome,
				p->v->eq1->nome,
				p->v->eq2->nome,
				p->v->sc1,
				p->v->sc2);
	}
}


/* Apaga um jogo dado um nome */
void case_r () {
	
	link p;						/* apontador para no de jogo */

	scanf(" %[^\n]", nome);
	p = (link) HTsearch(nome, &htJogos);
	if(p == NULL) {
					
		printf("%d Jogo inexistente.\n", line);
	}
	else {
		if(p->v->sc1 > p->v->sc2)	/* decrementa nr jogos ganhos da eq vencedora*/
			p->v->eq1->ganhos--;
		if(p->v->sc2 > p->v->sc1)
			p->v->eq2->ganhos--;	
		HTremove(nome, &htJogos);	/* remove jogo da tabela */
		DLremove_with_item_free(p);	/* remove da lista e liberta mem */
	}
}


/* Altera o score de um jogo dado o nome */
void case_s () {
	
	int sc1, sc2;			/* score de cada equipa */
	link p;					/* apontador para no de jogo */
	
	scanf(" %[^:]:%d:%d", nome, &sc1, &sc2);
	p = (link) HTsearch(nome, &htJogos);
	if(p == NULL) {
					
		printf("%d Jogo inexistente.\n", line);
	}
	else {
		/* decrementa nr jogos ganhos da equipa vencedora antiga */
		if(p->v->sc1 > p->v->sc2)
			p->v->eq1->ganhos--;
		else if(p->v->sc2 > p->v->sc1)
			p->v->eq2->ganhos--;
		/* incrementa nr jogos ganhos  da eq vencedora atual */
		if(sc1 > sc2)
			p->v->eq1->ganhos++;
		else if(sc2 > sc1)
			p->v->eq2->ganhos++;
		/* atualiza scores */
		p->v->sc1 = sc1;
		p->v->sc2 = sc2;
	}
}


/* Adiciona uma nova equipa */
void case_A () {
	
	scanf(" %[^\n]", nome);
	if(HTsearch(nome, &htEquipas) != NULL) {
					
		printf("%d Equipa existente.\n", line);
	}
	else {
	
		HTinsert((void*) NEWequipa(nome), &htEquipas);
	}
}


/* Procura uma equipa dado um nome */
void case_P () {
	
	pEquipa eq;					/* ponteiro para equipa */

	scanf(" %[^\n]", nome);
	eq = (pEquipa) HTsearch(nome, &htEquipas);
	if(eq == NULL) {
					
		printf("%d Equipa inexistente.\n", line);
	}
	else {
	
		printf("%d %s %d\n", line, nome, eq->ganhos);
	}
}


/* comparador de strings usado no qsort */
int compare_str(const void* a, const void* b) {
	
	return strcmp((*(pEquipa*) a)->nome, (*(pEquipa*) b)->nome);

}


/* Encontra as equipas que ganharam mais jogos e lista */
/*  por ordem lexicografica (do nome da equipa) */
void case_g () {
	
	int i, max = 0;							/* nr max de jogos ganhos por 1 equipa */
	int count = 0;							/* nr equipas com nr max de jogos ganhos */
	pEquipa eq, melhores[MAX_VENCEDORES];	/* lista das melhores equipas */
	
	/* encontra nr max de jogos ganhos por uma equipa e conta nr de max's */
	for(i = 0; i < htEquipas.M; i++) {
		
		eq = (pEquipa) htEquipas.t[i];
		if(eq && eq->ganhos >= max) {
				
			if(eq->ganhos > max) {
				max = eq->ganhos;			/* novo maximo. Reset count. */
				count = 0;			
			}
			melhores[count] = eq;
			if(count < MAX_VENCEDORES-1)	/* para nao ultrapassar o tam do array */
				count++;
		}
	}
	
	/* ordena e lista melhores */
	qsort((void*)melhores, count, sizeof(pEquipa), compare_str);
	if(count)
		printf("%d Melhores %d\n", line, max);
	for(i = 0; i < count; i++) {
		printf("%d * %s\n", line, melhores[i]->nome);
	}
}


/* main: le e executa comandos de gestao de jogos */
int main() {

	char c;												/* caracter de commando lido */
	htEquipas = HTinit(MAX_EQUIPAS_INIC, keyEquipa);	/* inicializa tab das equipas */
	htJogos = HTinit(MAX_JOGOS_INIC, keyJogo);			/* inicializa tab dos jogos */

	while((c = getchar()) != 'x') {	/* cicla enquanto nao for o comando x */

		switch(c) {
			
			case 'a':	/* Adiciona um novo jogo */
			
				case_a();
				break;
				
			case 'l':	/* Lista todos os jogos introduzidos */

				case_l();
				break;
			
			case 'p':	/* Procura um jogo com o nome dado */

				case_p();
				break;

			case 'r':	/* Apaga um jogo dado um nome */

				case_r();
				break;
				
			case 's':	/* Altera o score de um jogo dado o nome */

				case_s();
				break;
		
			case 'A':	/* Adiciona uma nova equipa */

				case_A();
				break;
				
			case 'P':	/* Procura uma equipa dado um nome */

				case_P();
				break;
				
			case 'g':	/* Encontra as equipas que ganharam mais jogos */

				case_g();
				break;
								
		}
		scanf("\n");
		line++;
	}
	/* liberta tabelas e listas */
	HTdestroy_with_item_free(&htEquipas);
	HTdestroy(&htJogos);
	DLdestroy_with_item_free();
	return 0;
}
