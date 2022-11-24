#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "jogos.h"

/*
  recebe tres ponteiros para chars, o nome do jogo, e o nome das equipas, dois
  inteiros, o score das equipas e a hash das equipas.
  devolve um novo jogo.
*/
Jogo newJogo(char* nome, char* e1, char* e2, int s1, int s2, ulong* ordem, link* hashEquipas) {
  Jogo final = can_fail_malloc(sizeof(struct jogo));

  final->e1 = newPar(e1, s1, hashEquipas); /* cria um par com o jogo e o seu score */
  final->e2 = newPar(e2, s2, hashEquipas);
  final->nome = can_fail_malloc(sizeof(char*)*(strlen(nome)+1));
  strcpy(final->nome, nome);
  final->ordem = *ordem;

  /* incrementa os jogos ganhos */
  if (s1 > s2) {
    final->e1->equipa->ganhos += 1;
  }
  else if (s2 > s1) {
    final->e2->equipa->ganhos += 1;
  }

  return final;
}

/*
  recebe um ponteiro para chars, o nome da equipa, um inteiro pontos e a hash
  das equipas.
  devolve um novo par.
 */
Par newPar(char* equipa, int pontos, link* hashEquipas) {
  Par final = can_fail_malloc(sizeof(struct par));

  final->equipa = EhashSearch(hashEquipas, equipa); /* procura a equipa na hash das equipas */
  final->pontos = pontos;

  return final;
}

/* recebe uma lista ligada e um jogo e insere o jogo na lista */
jlink JinsertBegin(jlink head, Jogo jogo) {
  jlink new;

  new = can_fail_malloc(sizeof(struct jnode));
  new->jogo = jogo;
  new->next = head;

  return new;
}

/* recebe uma lista ligada e um ponteiro para chars nome.
   devolve um jogo, se nao existir devolve null.
*/
Jogo JsearchList(jlink head, char* nome) {
  jlink p;

  for (p = head; p != NULL; p=p->next) {
    if (strcmp(nome, Key(p->jogo)) == 0) {
      return p->jogo;
    }
  }
  return NULL;
}

/* free a uma estrutura jogo */
void freeJogo(Jogo jogo) {
  free(jogo->e1);
  free(jogo->e2);
  free(jogo->nome);
  free(jogo);
}

/* free a uma estrutura jlink */
void freeJNode(jlink link) {
  freeJogo(link->jogo);
  free(link);
}

/*
  recebe um lista ligada e um ponteiro de chars nome e retira o jogo com esse nome
  da lista. Altera tambem o nr de vitorias da equipa que estivesse a ganhar
 */
jlink removeJogo(jlink head, char* nome) {
  jlink t, prev;

  /* procura pelo jogo na lista */
  for (prev = NULL, t = head; t != NULL; prev=t, t=t->next) {
    if (strcmp(Key(t->jogo), nome) == 0) {
      /* se for o primeiro elemento o seguinte passa a ser o primeiro */
      if (t == head) {
        head = t->next;
      }
      /* se nao for primeiro o proximo do anterior passa a ser o proximo do atual */
      else if (t != head){
        prev->next = t->next;
      }

      /* ve quem esta a ganhar e decrementa o nr de vitorias */
      if (t->jogo->e1->pontos > t->jogo->e2->pontos) {
        t->jogo->e1->equipa->ganhos -= 1;
      }
      else if (t->jogo->e1->pontos < t->jogo->e2->pontos) {
        t->jogo->e2->equipa->ganhos -= 1;
      }

      /* da free a node do jogo retirado */
      freeJNode(t);
      break;
    }
  }

  return head;
}

/* inicia a hash dos jogos */
jlink* JhashInit(){
  int i;
  jlink* heads = can_fail_malloc(HASH_SIZE*sizeof(jlink));
  for (i = 0; i < HASH_SIZE; i++) {
    heads[i] = NULL;
  }

  return heads;
}

/* recebe uma hash e um ponteiro de chars nome e devolve um jogo, devolve NULL se
   nao existir */
Jogo JhashSearch(jlink *heads, char* nome) {
  int i = hash(nome);
  return JsearchList(heads[i], nome);
}

/* recebe uma hash e um jogo e insere o jogo na hash */
jlink* JhashInsert(jlink *heads, Jogo jogo) {
  int i = hash(Key(jogo));
  heads[i] = JinsertBegin(heads[i], jogo);

  return heads;
}

/* recebe uma hash e um ponteiro de chars nome e retira o jogo com esse nome da hash */
jlink* JhashDelete(jlink* heads, char* nome) {
  int i = hash(nome);
  heads[i] = removeJogo(heads[i], nome);

  return heads;
}

/* free a uma lista ligada de jogos */
void freeJList(jlink head) {
  jlink aux;

   while (head != NULL) {
       aux = head;
       head = head->next;
       freeJNode(aux);
    }

}

/* free a hash dos jogos */
void JfreeHash(jlink* heads) {
  int i;
  for (i = 0; i < HASH_SIZE; i++) {
    freeJList(heads[i]);
  }

  free(heads);
}

/*
  recebe uma hash de jogos e um ponteiro para ulong size.
  devolve uma lista de jogos ordenada por ordem de insercao de todos os jogos e
  o tamanho da hash dos jogos
 */
Jogo* listaOrdenada(jlink* hashJogos, ulong* size) {
  int i;
  jlink t;
  Jogo* lista;

  lista = NULL;

  for (i = 0; i < HASH_SIZE; i++) {
    for (t = hashJogos[i]; t != NULL; t=t->next) {
      *size += 1;
      lista = can_fail_realloc(lista, sizeof(Jogo)*(*size)); /* aumenta a lista sempre que encontramos um jogo novo */
      lista[*size-1] = t->jogo;
    }
  }

  /* organiza a lista por ordem de insercao */
  qsort(lista, *size, sizeof(Jogo), Jcmp);

  return lista;
}

/* auxiliar qsort que organiza por ordem de insercao dos jogos */
int Jcmp(const void* a, const void* b) {
  Jogo j1, j2;

  j1 = *(Jogo*) a;
  j2 = *(Jogo*) b;

  return (j1->ordem - j2->ordem);
}
