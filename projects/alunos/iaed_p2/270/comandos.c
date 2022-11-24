#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "comandos.h"

/* Adiciona um novo jogo ao programa. Recebe 3 strings correspondentes aos
 * nomes do jogo e das respetivas equipas e 2 inteiros correspondentes aos golos
 * de cada equipa. Retorna erros para o stdout no caso do jogo ja existir no
 * sistema ou das equipas nao terem sido previamente criadas */
void cmd_a(int nl, pLista ls_jg, pTabEquipas ht_eq, pTabJogos ht_jg){
  pJogo jg_aux; pEquipa eq_aux1; pEquipa eq_aux2; int golos1, golos2;
  char aux[MAX_CHAR], aux1[MAX_CHAR], aux2[MAX_CHAR];
  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", aux, aux1, aux2, &golos1, &golos2);
  eq_aux1 = procura_eq(aux1, ht_eq); eq_aux2 = procura_eq(aux2, ht_eq);
  if (procura_jg(aux, ht_jg) != NULL)
    printf("%d Jogo existente.\n", nl);
  else if (eq_aux1 == NULL || eq_aux2 == NULL)
    printf("%d Equipa inexistente.\n", nl);
  else{
    jg_aux = novo_jogo(aux, eq_aux1, eq_aux2, golos1, golos2); /*pointer para o jogo*/
    insere_jg(jg_aux, ht_jg); /* insere na tabela de dispercao */
    adiciona_fim(ls_jg, jg_aux); /*insere numa lista.d.ligada (guarda a ordem)*/
    if (golos1 > golos2)
      jogos_ganhos(eq_aux1) += 1;
    else if (golos2 > golos1)
      jogos_ganhos(eq_aux2) += 1;
  }
}

/* Adiciona uma nova equipa. Recebe apenas o nome da equipa a adicionar e imprime
 * um erro no caso da equipa ja existir no sistema. */
void cmd_A(int nl, pTabEquipas ht_eq){
  char aux[MAX_CHAR];
  scanf(" %[^:\n]", aux);
  if (procura_eq(aux, ht_eq) == NULL){
    pEquipa eq_aux;
    eq_aux = nova_equipa(aux);
    insere_eq(eq_aux, ht_eq);
  }
  else printf("%d Equipa existente.\n", nl);
}

/* Lista todos os jogos existentes pela ordem que foram introduzidos.
 * Se nao existir nenhum jogo nao imprime nada no stdout. */
void cmd_l(int nl, pLista ls_jg){
  pJogo n;
  for (n = ls_jg->primeiro; n; n = n->seguinte){ /*percorre uma lista.d.ligada*/
    printf("%d ", nl);                    /*que tem como node um ponteiro para*/
    imprime_jogo(n);                       /*um jogo(guarda a ordem de insercao)*/
  }
}

/* Procura um jogo atraves do nome lido do stdin e imprime as suas caracteristicas
 * no stdout. Imprime um erro no caso do jogo nao existir. */
void cmd_p(int nl, pTabJogos ht_jg){
  pJogo jg_aux; char aux[MAX_CHAR];
  scanf(" %[^:\n]", aux);
  jg_aux = procura_jg(aux, ht_jg);
  if (jg_aux == NULL)
    printf("%d Jogo inexistente.\n", nl);
  else{
    printf("%d ", nl);
    imprime_jogo(jg_aux);
  }
}

/* Procura uma equipa atraves do nome lido do stdin e imprime esse mesmo nome
 * assim como o numero de jogos ganhos pela equipa. Imprime um erro no caso da
 * mesma nao existir. */
void cmd_P(int nl, pTabEquipas ht_eq){
  pEquipa eq_aux; char aux[MAX_CHAR];
  scanf(" %[^:\n]", aux);
  eq_aux = procura_eq(aux, ht_eq);
  if (eq_aux == NULL)
    printf("%d Equipa inexistente.\n", nl);
  else{
    printf("%d ", nl);
    imprime_equipa(eq_aux);
  }
}

/* Apaga um jogo correspondente ao nome lido do stdin. Nao imprime nada excepto
 * se o jogo nao existir o que resulta num erro */
void cmd_r(int nl, pLista ls_jg, pTabJogos ht_jg){
  pJogo jg_aux; char aux[MAX_CHAR];
  scanf(" %[^:\n]", aux);
  jg_aux = procura_jg(aux, ht_jg);
  if (jg_aux == NULL)
    printf("%d Jogo inexistente.\n", nl);
  else{
    if (golos1(jg_aux) > golos2(jg_aux))
      jogos_ganhos(equipa1(jg_aux)) -= 1;
    if (golos2(jg_aux) > golos1(jg_aux))
      jogos_ganhos(equipa2(jg_aux)) -= 1;
    rm_no(ls_jg, jg_aux); /* apaga da lista .d.ligada */
    apaga_jg(aux, ht_jg);  /* apaga da hashtable */
  }
}

/* Altera a pontucao de um certo jogo. Le do stdin o jogo a alterar assim como
 * os novos golos marcados por cada equipa que jogou esse jogo. Imprime um erro
 * no caso do jogo nao existir */
void cmd_s(int nl, pTabJogos ht_jg){
  pJogo jg_aux; int golos1, golos2; char aux[MAX_CHAR];
  scanf(" %[^:\n]:%d:%d", aux, &golos1, &golos2);
  jg_aux = procura_jg(aux, ht_jg);
  if (jg_aux == NULL) printf("%d Jogo inexistente.\n", nl);
  else{
    if (golos1(jg_aux) > golos2(jg_aux)) /*apaga resultado anterior nas equipas*/
      jogos_ganhos(equipa1(jg_aux)) -= 1;
    if (golos2(jg_aux) > golos1(jg_aux))
      jogos_ganhos(equipa2(jg_aux)) -= 1;
    if (golos1 > golos2) /* atribui novo resultado */
      jogos_ganhos(equipa1(jg_aux)) += 1;
    if (golos2 > golos1)
      jogos_ganhos(equipa2(jg_aux)) += 1;
    golos1(jg_aux) = golos1; golos2(jg_aux) = golos2;/*altera na estrutura do jogo*/
  }
}

/* Encontra as equipas que ganharam mais jogos e imprime os nomes das mesmas
 * por ordem lexicografica. Se nao existirem equipas nao imprime nada. */
void cmd_g(int nl, pTabEquipas ht_eq){
  int i = 0, max = 0;
  for ( ; i < M(ht_eq); i++) /* procura o maior numero de jogos ganhos */
    if (equipas(ht_eq)[i] != NULL && jogos_ganhos(equipas(ht_eq)[i]) > max)
      max = jogos_ganhos(equipas(ht_eq)[i]);
  if (N(ht_eq) > 0){ /* apenas se existir alguma equipa */
    int j = 0; char **nomes = can_fail_malloc(sizeof(char*)*100);
    printf("%d Melhores %d\n", nl, max);
    for (i = 0 ; i < M(ht_eq); i++)
      if (equipas(ht_eq)[i] != NULL && jogos_ganhos(equipas(ht_eq)[i]) == max){
        /*adiciona o nome da equipa ao vetor para ser ordenadao */
        nomes[j] = nome(equipas(ht_eq)[i]); j++;
      }
    qsort(nomes, j, sizeof(char *), compara);/*equipas por ordem lexicografica*/
    for (i = 0; i < j; i++)
      printf("%d * %s\n", nl, nomes[i]);
    free(nomes);
  }
}

/* Funcao auxiliar que recebe um ponteiro para um vetor de caracteres, aloca
 * memoria para o vetor, copia o mesmo para o novo vetor com memoria dinamica
 * e devolve-o */
char* strdup(const char *s){
  size_t tamanho = strlen(s) + 1; /* tamanho da string + '\0' */
  char *p = can_fail_malloc(tamanho * sizeof(char));
  while (tamanho--) /* enquanto for diferente de 0 */
    p[tamanho] = s[tamanho];
  return p;
}

/* Funcao auxiliar usada pelo qsort para ordenar por ordem lexicografica que
 * recebe um ponteiro para um ponteiro para um caracter e retorna a funcao strcmp
 * que recebe ponteiros para caracteres (dai a desreferencia dos ponteiros) */
int compara(const void *p1, const void *p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}

/* Funcao auxiliar que liberta a memoria alocada pelas tabelas de dispercao e
 * pela lista duplamente ligada.
 */
void liberta_tudo(pLista ls_jg, pTabEquipas ht_eq, pTabJogos ht_jg){
	liberta_lista(ls_jg); liberta_te(ht_eq); liberta_tj(ht_jg);
}
