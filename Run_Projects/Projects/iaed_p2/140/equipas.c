#include "equipas.h"

/* recebe um ponteiro de chars e devolve um inteiro correspondente ao indice da hash */
int hash(char* nome) {
  int i = 0, a = 127;

  for (; *nome != '\0'; nome++) {
    i = (a*i + *nome) % HASH_SIZE;
  }
  return i;
}

/* recebe um ponteiro para chars e devolve uma nova estrutura equipa */
Equipa newEquipa(char* buffer) {
  Equipa final = malloc(sizeof(struct equipa));

  final->nome = malloc(sizeof(char*)*(strlen(buffer)+1));
  strcpy(final->nome, buffer);
  final->ganhos = 0;

  return final;
}

/* recebe uma lista ligada e uma equipa e insere a equipa no inicio da lista */
link EinsertBegin(link head, Equipa equipa) {
  link new;

  new = malloc(sizeof(struct node));
  new->equipa = equipa;
  new->next = head;

  return new;
}

/* recebe uma lista ligada e um ponteiro para nomes e devolve a equipa com esse nome,
   se nao existir devolve null */
Equipa EsearchList(link head, char* nome) {
  link p;

  for (p = head; p != NULL; p=p->next) {
    if (strcmp(nome, Key(p->equipa)) == 0) {
      return p->equipa;
    }
  }
  return NULL;
}

/* inicia a hash table das equipas */
link* EhashInit(){
  int i;
  link* heads = malloc(HASH_SIZE*sizeof(link));
  for (i = 0; i < HASH_SIZE; i++) {
    heads[i] = NULL;
  }

  return heads;
}

/* recebe uma hash e um ponteiro de chars nome e devolve se o nome existe na hash,
   devolve null se nao existir */
Equipa EhashSearch(link *heads, char* nome) {
  int i = hash(nome);
  return EsearchList(heads[i], nome);
}

/* recebe uma hash e uma equipa e insera a equipa na hash */
link* EhashInsert(link *heads, Equipa equipa) {
  int i = hash(Key(equipa));
  heads[i] = EinsertBegin(heads[i], equipa);

  return heads;
}

/* da free a uma estrutura equipa */
void freeEquipa(Equipa equipa) {
  free(equipa->nome);
  free(equipa);
}

/* da free a uma lista ligada de equipas */
void freeEList(link head) {
  link aux;

  while (head != NULL) {
     aux = head;
     head = head->next;
     freeEquipa(aux->equipa);
     free(aux);
  }
}

/* da free a hash das equipas */
void EfreeHash(link* heads) {
  int i;
  for (i = 0; i < HASH_SIZE; i++) {
    freeEList(heads[i]);
  }

  free(heads);
}

/* recebe a hash das equipas e dois ponteiros para inteiros, o maior nr de vitorias
   e o nr de elementos com esse numero de vitorias.

   Devolve uma lista organizada por ordem alfabetica com desses elementos e ambos os ponteiros
*/
Equipa* listaMaioresVitorias(link* hashEquipas,int* maior, int* count) {
  Equipa* lista;
  link t;
  int i;

  lista = NULL;

  for (i = 0; i < HASH_SIZE; i++) {
    for (t = hashEquipas[i]; t != NULL; t=t->next) {
      /* se o nr de jogos ganhos e igual se for aumenta a lista e adiciona a equipa */
      if (t->equipa->ganhos == *maior) {
        *count += 1; /* incrementa o nr de jogos */
        lista = realloc(lista, sizeof(Equipa)*(*count)); /* aumenta a lista */
        lista[*count-1] = t->equipa;
      }
      /* se o nr de jogos ganhos for superior cria uma lista nova e adiciona a equipa */
      else if (t->equipa->ganhos > *maior) {
        *maior = t->equipa->ganhos; /* altera o nr de maiores vitorias */
        *count = 1;
        free(lista);
        lista = malloc(sizeof(Equipa)); /* cria uma lista nova */
        lista[*count-1] = t->equipa;
      }
    }
  }

  /* organiza por ordem alfabetica */
  qsort(lista, *count, sizeof(Equipa), cmpfunc);

  return lista;
}

/* auxiliar de qsort para organizar as equipas por ordem alfabetica */
int cmpfunc(const void* a, const void* b) {
  Equipa e1, e2;

  e1 = *(Equipa*) a;
  e2 = *(Equipa*) b;

  return strcmp(e1->nome, e2->nome);
}
