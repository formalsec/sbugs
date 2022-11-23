#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "listadligada.h"
#include <stdlib.h>
#include <string.h>

/* Aloca memoria para uma estrutura lista que contem ponteiros para jogos
 * correspondentes a cabeca e ao ultimo elemento da lista ligada, coloca ambos
 * a NULL e devolve um ponteiro para a lista.d.ligada criada
*/
pLista cria_lista(){
	pLista l = can_fail_malloc(sizeof(struct lista));
	l->primeiro = l->ultimo = NULL;
	return l;
}

/* Funcao que recebe um ponteiro para uma lista.d.ligada e liberta a memoria
 * alocada para a mesma sendo que os nos correspondem a ponteiros para jogos
 * e sao libertados posteriormente.
*/
void liberta_lista(pLista l){
	free(l);
}

/* Funcao que remove um no da lista.d.ligada alterando apenas os ponteiros
 * para o no seguinte ou anterior dependendo da posicao que se esta a alterar.
 * Esta funcao recebe um ponteiro para a lista.d.ligada e um ponteiro para um
 * jogo que corresponde ao no que se quer remover da lista.
*/
void rm_no (pLista l, pJogo n){
	if (n->anterior == NULL) /* Se for o primeiro no */
		l->primeiro = n->seguinte;
	else
		n->anterior->seguinte = n->seguinte;
	if (n->seguinte == NULL) /* se for o ultimo  */
		l->ultimo = n->anterior;
	else
		n->seguinte->anterior = n->anterior;
}

/* Funcao que adiciona um no ao fim da lista.d.ligada e que por isso recebe um
 * ponteiro para a lista e outro para o jogo que se pretende adicionar pois
 * este corresponde a um no.
 */
void adiciona_fim(pLista l, pJogo n){
	n->anterior = l->ultimo; n->seguinte = NULL;
	if (l->ultimo)
		l->ultimo->seguinte = n;
	else /* se a lista estiver vazia */
		l->primeiro = n;
	l->ultimo = n;
}
