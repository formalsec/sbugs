#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipas.h"
#include "tabdispercao.h"

/* Recebe um ponteiro para uma equipa e Liberta a memoria alocada por ela
 * (nome e ponteiro para a estrutura da equipa)*/
void liberta_equipa(pEquipa a){
  free(nome(a)); free(a);
}

/* Recebe um ponteiro para uma equipa e imprime no stdout o nome e numero de
 * jogos ganhos pela mesma */
void imprime_equipa(pEquipa a){
  printf("%s %d\n", nome(a), a->jogos_ganhos);
}

/* Recebe um ponteiro para o nome da equipa a criar e devolve um ponteiro para
 * a estrutura da equipa alocando memoria para a mesma e para o nome */
pEquipa nova_equipa(char *nome){
  pEquipa eq_aux = can_fail_malloc(sizeof(struct equipa));
  nome(eq_aux) = strdup(nome); /*nome da equipa correponde a chave usada na tabela*/
  eq_aux->jogos_ganhos = 0;
  return eq_aux;
}
