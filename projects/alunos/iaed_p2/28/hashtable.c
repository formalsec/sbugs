#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hashtable.h"

/* Funcao de hashing utilizada nas hashtables */
unsigned int hash(const char * key) {
  unsigned long int value = 0;
  unsigned int i = 0;
  unsigned int key_len = strlen(key);

  for(i=0;i< key_len;i++) {
    value = value*37 + key[i];
  }

  value = value % HASHTABLE_SIZE;

  return value;
}

/* Cria uma entrada para uma hashtable, alocando a memoria necessaria */
entry * entryCreate(char *key, void * data) {
  entry * entry_ = can_fail_malloc((sizeof(entry) *1));
  entry_->key = can_fail_malloc((strlen(key)+1)* sizeof(char));

  strcpy(entry_->key, key);

  entry_->data = data;
  entry_->next = NULL;

  return entry_;
}

/* Inicializa uma hashtable e aloca memoria, criando-a */
hashtable * hashtableCreate() {
  hashtable * hashtable = can_fail_malloc(sizeof(hashtable));
  int i = 0;

  hashtable->entries = can_fail_malloc(sizeof(entry*) * HASHTABLE_SIZE);

  for(i=0; i<HASHTABLE_SIZE; i++) {
    hashtable->entries[i] = NULL;
  }

  return hashtable;
}

/* Da free de uma entrada de uma hashtable */
void freeEntry(entry * head) {
  if(!head)
    return;

  freeEntry(head->next);
  free(head->key);
  free(head);
}

/* Dada uma hashtable da free desta por completo */
void freeHashtable(hashtable * hashtable) {
  int i = 0;
  for(i=0; i<HASHTABLE_SIZE;i++) {
    freeEntry(hashtable->entries[i]);
  }
  free(hashtable->entries);
  free(hashtable);
}

/* Adiciona um elemento a uma hashtable */
void hashtableAdd(hashtable * hashtable, char * key, void * data) {
  unsigned int position = hash(key);
  entry * prev;
  entry * entry = hashtable->entries[position];

  if(entry == NULL ) {
    hashtable->entries[position] = entryCreate(key, data);
    return;
  }

  while(entry != NULL) {
    if (strcmp(entry->key, key) == 0) return;
    prev = entry;
    entry = prev->next;
  }

  prev->next = entryCreate(key, data);
}

/* Procura um elemento numa hashtable e retorna-o */
void * hashtableGet(hashtable * hashtable, char * key) {
  unsigned int position = hash(key);
  entry * entry = hashtable->entries[position];

  if(entry == NULL) return NULL;

  while(entry!=NULL) {
    if(strcmp(entry->key, key)==0) return entry->data;
    entry = entry -> next;
  }
  return NULL;
}

/* Remove um elemento de uma hashtable */
void hashtableDel(hashtable * hashtable, char * key) {
  unsigned int position = hash(key);
  entry * prev;
  entry * temp;
  entry * entry = hashtable->entries[position];

  temp = entry;
  if(temp == NULL) return;

  if(strcmp(temp->key, key) == 0) {
    hashtable->entries[position] = temp ->next;
    free(temp->key);
    free(temp);
    return;
  }

  while(temp!=NULL) {
    if(strcmp(temp->key, key) == 0) {
      prev->next = temp->next;
      free(temp->key);
      free(temp);
      return;
    }
    prev = temp;
    temp = prev -> next;
  }
}
