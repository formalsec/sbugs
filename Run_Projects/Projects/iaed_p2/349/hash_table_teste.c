#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_INICIAL 1913
#define MAX 1024

/*********************************JOGO*****************************************/
typedef struct jogo {
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
} jogo;

typedef struct entry_jogos {
    struct jogo *jogo;
    struct entry_jogos *next;
} entry_jogos;

typedef struct {
    entry_jogos **entries;
    int capacidade;
} ht_jogos;

unsigned int hash(const char *nome, int capacidade) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(nome);

    /* do several rounds of multiplication */
    for (; i < key_len; ++i) {
        value = value * 37 + nome[i];
    }

    /* make sure value is 0 <= value < hashtable->capacidade */
    value = value % capacidade;

    return value;
}

entry_jogos *ht_pair_jogos(const char *nome, const char *equipa1, const char *equipa2, int score1, int score2) {
    /* allocate the entry */
    entry_jogos *entry = malloc(sizeof(entry_jogos) * 1);
    entry->jogo = malloc(sizeof(jogo) * 1);
    entry->jogo->nome = malloc(strlen(nome) + 1);
    entry->jogo->equipa1 = malloc(strlen(equipa1) + 1);
    entry->jogo->equipa2 = malloc(strlen(equipa2) + 1);
    entry->jogo->score1 = score1;
    entry->jogo->score2 = score2;

    /* copy the key and value in place */
    strcpy(entry->jogo->nome, nome);
    strcpy(entry->jogo->equipa1, equipa1);
    strcpy(entry->jogo->equipa2, equipa2);

    /* next starts out null but may be set later on */
    entry->next = NULL;

    return entry;
}

ht_jogos *ht_create_jogos(void) {
    int i = 0;
    /* allocate table */
    ht_jogos *hashtable = malloc(sizeof(ht_jogos) * 1);

    /* allocate table entries */
    hashtable->capacidade = TAMANHO_INICIAL;
    hashtable->entries = malloc(sizeof(entry_jogos*) * hashtable->capacidade);

    /* set each to null (needed for proper operation) */
    for (; i < hashtable->capacidade; ++i) {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}

void ht_set_jogos(ht_jogos *hashtable, const char *nome, const char *equipa1, const char *equipa2, int score1, int score2) {
    unsigned int slot = hash(nome, hashtable->capacidade);
    entry_jogos *prev;

    /* try to look up an entry set */
    entry_jogos *entry = hashtable->entries[slot];

    /* no entry means slot empty, insert immediately */
    if (entry == NULL) {
        hashtable->entries[slot] = ht_pair_jogos(nome, equipa1, equipa2, score1, score2);
        return;
    }

    /* walk through each entry until either the end is */
    /* reached or a matching key is found */
    while (entry != NULL) {
        /* check key */
        if (strcmp(entry->jogo->nome, nome) == 0) {
            /* match found, replace value */
            free(entry->jogo->equipa1);
            free(entry->jogo->equipa2);
            entry->jogo->equipa1 = malloc(strlen(equipa1) + 1);
            entry->jogo->equipa2 = malloc(strlen(equipa2) + 1);
            entry->jogo->score1 = score1;
            entry->jogo->score2 = score2;
            strcpy(entry->jogo->equipa1, equipa1);
            strcpy(entry->jogo->equipa2, equipa2);
            return;
        }

        /* walk to next  */
        prev = entry;
        entry = prev->next;
    }

    /* end of chain reached without a match, add new  */
    prev->next = ht_pair_jogos(nome, equipa1, equipa2, score1, score2);
}

jogo *ht_get_jogos(ht_jogos *hashtable, const char *nome) {
    unsigned int slot = hash(nome, hashtable->capacidade);

    /* try to find a valid slot  */
    entry_jogos *entry = hashtable->entries[slot];

    /* no slot means no entry  */
    if (entry == NULL) {
        return NULL;
    }

    /* walk through each entry in the slot, which could just be a single thing  */
    while (entry != NULL) {
        /* return value if found  */
        if (strcmp(entry->jogo->nome, nome) == 0) {
            return entry->jogo;
        }

        /* proceed to next key if available */
        entry = entry->next;
    }

    /* reaching here means there were >= 1 entries but no key match  */
    return NULL;
}

void ht_del_jogos(ht_jogos *hashtable, const char *nome) {
    unsigned int bucket = hash(nome, hashtable->capacidade);
    entry_jogos *prev;
    int idx = 0;

    /* try to find a valid bucket  */
    entry_jogos *entry = hashtable->entries[bucket];

    /* no bucket means no entry  */
    if (entry == NULL) {
        return;
    }

    /* walk through each entry until either the end is reached or a matching key is found  */
    while (entry != NULL) {
        /* check key  */
        if (strcmp(entry->jogo->nome, nome) == 0) {
            /* first item and no next entry */
            if (entry->next == NULL && idx == 0) {
                hashtable->entries[bucket] = NULL;
            }

            /* first item with a next entry  */
            if (entry->next != NULL && idx == 0) {
                hashtable->entries[bucket] = entry->next;
            }

            /* last item  */
            if (entry->next == NULL && idx != 0) {
                prev->next = NULL;
            }

            /* middle item  */
            if (entry->next != NULL && idx != 0) {
                prev->next = entry->next;
            }

            /* free the deleted entry  */
            free(entry->jogo->nome);
            free(entry->jogo->equipa1);
            free(entry->jogo->equipa2);
            free(entry->jogo);
            free(entry);

            return;
        }

        /* walk to next  */
        prev = entry;
        entry = prev->next;

        ++idx;
    }
}

void ht_dump_jogos(ht_jogos *hashtable) {
    int i;
    for (i = 0; i < hashtable->capacidade; ++i) {
        entry_jogos *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%4d]: ", i);

        for(;;) {
            printf("%s=%s=%s=%d=%d", entry->jogo->nome, entry->jogo->equipa1, entry->jogo->equipa2, entry->jogo->score1, entry->jogo->score2);

            if (entry->next == NULL) {
                break;
            }

            entry = entry->next;
        }

        printf("\n");
    }
}

/*********************************JOGO*****************************************/

/*********************************EQUIPAS**************************************/
typedef struct equipa {
    char *nome;
    int vitorias;
} equipa;

typedef struct entry_equipas {
    struct equipa *equipa;
    struct entry_equipas *next;
} entry_equipas;

typedef struct {
    entry_equipas **entries;
    int capacidade;
} ht_equipas;

entry_equipas *ht_pair_equipas(const char *nome, int vitorias) {
    /* allocate the entry */
    entry_equipas *entry = malloc(sizeof(entry_equipas) * 1);
    entry->equipa = malloc(sizeof(equipa) * 1);
    entry->equipa->nome = malloc(strlen(nome) + 1);
    entry->equipa->vitorias = vitorias;

    /* copy the key and value in place */
    strcpy(entry->equipa->nome, nome);

    /* next starts out null but may be set later on */
    entry->next = NULL;

    return entry;
}

ht_equipas *ht_create_equipa(void) {
    int i = 0;
    /* allocate table */
    ht_equipas *hashtable = malloc(sizeof(ht_equipas) * 1);

    /* allocate table entries */
    hashtable->capacidade = TAMANHO_INICIAL;
    hashtable->entries = malloc(sizeof(entry_equipas*) * hashtable->capacidade);

    /* set each to null (needed for proper operation) */
    for (; i < hashtable->capacidade; ++i) {
        hashtable->entries[i] = NULL;
    }
    return hashtable;
}

void ht_set_equipas(ht_equipas *hashtable, const char *nome, int vitorias) {
    unsigned int slot = hash(nome, hashtable->capacidade);
    entry_equipas *prev;

    /* try to look up an entry set */
    entry_equipas *entry = hashtable->entries[slot];

    /* no entry means slot empty, insert immediately */
    if (entry == NULL) {
        hashtable->entries[slot] = ht_pair_equipas(nome, vitorias);
        return;
    }

    /* walk through each entry until either the end is */
    /* reached or a matching key is found */
    while (entry != NULL) {
        /* check key */
        if (strcmp(entry->equipa->nome, nome) == 0) {
            /* match found, replace value */
            entry->equipa->vitorias = vitorias;
            return;
        }

        /* walk to next  */
        prev = entry;
        entry = prev->next;
    }

    /* end of chain reached without a match, add new  */
    prev->next = ht_pair_equipas(nome, vitorias);
}

equipa *ht_get_equipas(ht_equipas *hashtable, const char *nome) {
    unsigned int slot = hash(nome, hashtable->capacidade);

    /* try to find a valid slot  */
    entry_equipas *entry = hashtable->entries[slot];

    /* no slot means no entry  */
    if (entry == NULL) {
        return NULL;
    }

    /* walk through each entry in the slot, which could just be a single thing  */
    while (entry != NULL) {
        /* return value if found  */
        if (strcmp(entry->equipa->nome, nome) == 0) {
            return entry->equipa;
        }

        /* proceed to next key if available */
        entry = entry->next;
    }

    /* reaching here means there were >= 1 entries but no key match  */
    return NULL;
}

void ht_dump_equipas(ht_equipas *hashtable) {
    int i;
    for (i = 0; i < hashtable->capacidade; ++i) {
        entry_equipas *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%4d]: ", i);

        for(;;) {
            printf("%s=%d", entry->equipa->nome, entry->equipa->vitorias);

            if (entry->next == NULL) {
                break;
            }

            entry = entry->next;
        }

        printf("\n");
    }
}

/*********************************EQUIPAS**************************************/

int adicionaJogo(int nl, ht_jogos *hashtable_jogos, ht_equipas *hashtable_equipas) {
  char nome[MAX];
  char equipa1[MAX];
  char equipa2[MAX];
  int score1;
  int score2;
  jogo *jogo;
  equipa *equipa;

  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);

  jogo = ht_get_jogos(hashtable_jogos, nome);
  if (jogo != NULL) {
      printf("%d Jogo existente.\n", nl);
      return 0;
  }

  equipa = ht_get_equipas(hashtable_equipas, equipa1);
  if (equipa == NULL) {
      printf("%d Equipa inexistente.\n", nl);
      return 0;
  }
  equipa = ht_get_equipas(hashtable_equipas, equipa2);
  if (equipa == NULL) {
      printf("%d Equipa inexistente.\n", nl);
      return 0;
  }

  ht_set_jogos(hashtable_jogos, nome, equipa1, equipa2, score1, score2);

  if (score1 > score2){
      equipa = ht_get_equipas(hashtable_equipas, equipa1);
      equipa->vitorias += 1;
  }

  if (score1 < score2){
      equipa = ht_get_equipas(hashtable_equipas, equipa2);
      equipa->vitorias += 1;
  }

  return 0;
}

int adicionaEquipa(int nl, ht_equipas *hashtable) {
    char nome[MAX];
    int i = 0;
    equipa *equipa;
    nl++;

    scanf(" %[^:\n]", nome);

    equipa = ht_get_equipas(hashtable, nome);
    if (equipa != NULL) {
        printf("%d Equipa existente.\n", nl);
        return 0;
    }

    ht_set_equipas(hashtable, nome, i);

    return 0;
}

int procuraJogo(int nl, ht_jogos *hashtable_jogos){
    char nome[MAX];
    jogo *jogo;
    nl++;

    scanf(" %[^:\n]", nome);

    jogo = ht_get_jogos(hashtable_jogos, nome);
    if (jogo == NULL) {
        printf("%d Jogo inexistente.\n", nl);
        return 0;
    }

    printf("%d %s\n", nl, jogo->nome);

    return 0;
}

int procuraEquipa(int nl, ht_equipas *hashtable_equipas){
    char nome[MAX];
    equipa *equipa;
    nl++;

    scanf(" %[^:\n]", nome);

    equipa = ht_get_equipas(hashtable_equipas, nome);
    if (equipa == NULL) {
        printf("%d Equipa inexistente.\n", nl);
        return 0;
    }

    printf("%d %s %d\n", nl, equipa->nome, equipa->vitorias);

    return 0;
}

int alteraScore(int nl, ht_jogos *hashtable_jogos, ht_equipas *hashtable_equipas){
    char nome[MAX];
    int novo_score1;
    int novo_score2;
    jogo *jogo;
    equipa *equipa;
    nl++;

    scanf(" %[^:\n]:%d:%d", nome, &novo_score1, &novo_score2);

    jogo = ht_get_jogos(hashtable_jogos, nome);

    if (jogo == NULL){
        printf("%d Jogo inexistente.\n", nl);
        return 0;
    }

    if(jogo->score1 > jogo->score2){
        equipa = ht_get_equipas(hashtable_equipas, jogo->equipa1);
        equipa->vitorias -= 1;
        if (novo_score1 > novo_score2){
          equipa = ht_get_equipas(hashtable_equipas, jogo->equipa1);
          equipa->vitorias += 1;
        }
        if (novo_score1 < novo_score2){
          equipa = ht_get_equipas(hashtable_equipas, jogo->equipa2);
          equipa->vitorias += 1;
        }
    }

    if(jogo->score1 < jogo->score2){
        equipa = ht_get_equipas(hashtable_equipas, jogo->equipa2);
        equipa->vitorias -= 1;
        if (novo_score1 > novo_score2){
          equipa = ht_get_equipas(hashtable_equipas, jogo->equipa1);
          equipa->vitorias += 1;
        }
        if (novo_score1 < novo_score2){
          equipa = ht_get_equipas(hashtable_equipas, jogo->equipa2);
          equipa->vitorias += 1;
        }
    }

    jogo->score1 = novo_score1;
    jogo->score2 = novo_score2;

    return 0;
}

int removeJogo(int nl, ht_jogos *hashtable_jogos, ht_equipas *hashtable_equipas){
    char nome[MAX];
    jogo *jogo;
    equipa *equipa;
    nl++;

    scanf(" %[^:\n]", nome);

    jogo = ht_get_jogos(hashtable_jogos, nome);

    if (jogo == NULL){
        printf("%d Jogo inexistente.\n", nl);
        return 0;
    }

    if(jogo->score1 > jogo->score2){
        equipa = ht_get_equipas(hashtable_equipas, jogo->equipa1);
        equipa->vitorias -= 1;
    }

    if(jogo->score1 < jogo->score2){
        equipa = ht_get_equipas(hashtable_equipas, jogo->equipa2);
        equipa->vitorias -= 1;
    }

    ht_del_jogos(hashtable_jogos, nome);

    return 0;
}

int libertaMemoriaJogos(ht_jogos *hashtable_jogos){
    int i;
    entry_jogos *entry;
    entry_jogos *entry_aux;

    for(i = 0; i < TAMANHO_INICIAL; i++){
        entry = hashtable_jogos->entries[i];
            while (entry != NULL) {
              entry_aux = entry;
              entry = entry->next;
              free(entry_aux->jogo->nome);
              free(entry_aux->jogo->equipa1);
              free(entry_aux->jogo->equipa2);
              free(entry_aux->jogo);
              free(entry_aux);
            }
    }
    free(hashtable_jogos->entries);
    free(hashtable_jogos);
    return 0;
}

int libertaMemoriaEquipas(ht_equipas *hashtable_equipas){
    int i;
    entry_equipas *entry;
    entry_equipas *entry_aux;

    for(i = 0; i < TAMANHO_INICIAL; i++){
        entry = hashtable_equipas->entries[i];
            while (entry != NULL) {
              entry_aux = entry;
              entry = entry->next;
              free(entry_aux->equipa->nome);
              free(entry_aux->equipa);
              free(entry_aux);
            }
    }
    free(hashtable_equipas->entries);
    free(hashtable_equipas);
    return 0;
}


int main()
{
  ht_jogos *ht_jogos = ht_create_jogos();
  ht_equipas *ht_equipas = ht_create_equipa();

  int i;
  int nl = 0;

	while((i=getchar())!=EOF && i != 'x')
	{
		switch(i)
		{
      case('a'):
      nl++;
      adicionaJogo(nl, ht_jogos, ht_equipas);
      break;

      case('A'):
      nl++;
      adicionaEquipa(nl, ht_equipas);
      break;

      case('p'):
      nl++;
      procuraJogo(nl, ht_jogos);
      break;

      case('P'):
      nl++;
      procuraEquipa(nl, ht_equipas);
      break;

      case('s'):
      nl++;
      alteraScore(nl, ht_jogos, ht_equipas);
      break;

      case('r'):
      nl++;
      removeJogo(nl, ht_jogos, ht_equipas);
      break;
		}
	}
  libertaMemoriaJogos(ht_jogos);
  libertaMemoriaEquipas(ht_equipas);
	return 0;
}
