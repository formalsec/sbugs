#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "main.h"

/* Hashing function based on djb2 algorithm */
unsigned int hash(char *key, int size) {
    unsigned int value = 0;
    unsigned int counter;

    value = 5381;
    while((counter = *key++)){
        value = counter + (value << 6) + (value << 16) - value;
    }


    value = value % size;

    return value;
}

/* Initialize and allocate memory for the hashtable */
Hash_Array* hashtable_init(int size){
    Hash_Array *hashtable;
    int counter;

    /* Create the array */
    hashtable = can_fail_malloc(sizeof(Hash_Array));
    /* Create the entries of the array */
    hashtable->entries = can_fail_malloc(sizeof(Bucket*) * size);

    /* Set each value of the the array to NULL*/
    for(counter = 0; counter < size; counter++) {
        hashtable->entries[counter] = NULL;
    }
    hashtable->size = size;
    return hashtable;
}

/* Receives a key and value and returns a bucket ready to be put into the array */
Bucket* create_bucket(char *key, Game *value) {
    Bucket *bucket;

    /* Allocating memory for the bucket */
    bucket = can_fail_malloc(sizeof(Bucket));
    bucket->key = key;
    bucket->data = value;

    bucket->next = NULL;

    return bucket;
}

/* Creates a bucket with the given information, hashes the key and inserts in the 
respective slot */
void hashtable_insert(Hash_Array *hashtable, char *key, Game *value){
    unsigned int slot;
    Bucket *entry, *prev;

    slot = hash(key, hashtable->size);
    entry = hashtable->entries[slot];

    if(entry == NULL){
        hashtable->entries[slot] = create_bucket(key, value);
    }

    /* Means there was a collision */
    else{ 
        while(entry != NULL){  /* Find the last NULL element at that index */    
            if(strcmp(entry->key, key) == 0){   /* If key is already present, update value */
                free_data(entry->data);
                entry->data = value;    
                return;
            }
            prev = entry;
            entry = prev->next;
        }
        prev->next = create_bucket(key, value);
    }
    return;
}

Game* hashtable_get(Hash_Array *hashtable, char *key){
    unsigned int slot;
    Bucket *entry;
    slot = hash(key, hashtable->size);
    entry = hashtable->entries[slot];

    /* Loop over all the entries in the slot  */
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->data;
        }

        entry = entry->next;
    }

    /* Key was not found */
    return NULL;
}

/* Used to print all availables games */
void hashtable_print_all(Hash_Array *hashtable){
    int counter, aux_counter;
    Bucket *entry;
    for(counter = 0; counter < hashtable->size; counter++){
        entry = hashtable->entries[counter];

        if (entry == NULL) {
            continue;
        }

        printf("%4d:  ", counter);
        for(aux_counter = 0;;aux_counter++){
            if(entry->data->team_flag==0){    /* If its for games */
                printf(" (%s:%s) ->", entry->key, entry->data->team1);
            }
            if(entry->data->team_flag==1){                       /* If its for teams */
                printf(" (%s:%d) ->", entry->key, entry->data->score1);
            }

            if (entry->next == NULL) {
                printf(" NULL");
                break;
            }
            entry = entry->next;
        }
    }
}

/* Print the hashtable - used for debugging */
void hashtable_visualize(Hash_Array *hashtable){
    int counter, aux_counter;
    Bucket *entry;
    for(counter = 0; counter < hashtable->size; counter++){
        entry = hashtable->entries[counter];

        if (entry == NULL) {
            continue;
        }

        printf("%4d:  ", counter);
        for(aux_counter = 0;;aux_counter++){
            if(entry->data->team_flag==0){    /* If its for games */
                printf(" (%s:%s:%d) ->", entry->key, entry->data->team1, *entry->data->index);
            }
            if(entry->data->team_flag==1){                       /* If its for teams */
                printf(" (%s:%d:%d) ->", entry->key, entry->data->score1, *entry->data->index);
            }

            if (entry->next == NULL) {
                printf(" NULL");
                break;
            }
            entry = entry->next;
        }
        putchar('\n');
    }
}

/* Erase the whole hashtable */
void hashtable_free_all(Hash_Array *hashtable){
    int counter, aux_counter;
    Bucket *entry, *aux;
    
    for(counter = 0; counter < hashtable->size; counter++){
        entry = hashtable->entries[counter];

        if (entry == NULL) {
            free(entry);
            continue;
        }

        for(aux_counter = 0;;aux_counter++){
            aux = entry->next;
            free_data(entry->data);
            free(entry->key);
            free(entry);

            if(aux == NULL){
                break;
            }
            
            entry = aux;
        }
    }
    free(hashtable->entries);
    free(hashtable);
    return;
}



/* Receives a key and deletes the bucket associated with that key */
void hashtable_del(Hash_Array *hashtable, char *key){
    unsigned int slot;
    Bucket *entry, *prev;
    int counter;

    slot = hash(key, hashtable->size);
    entry = hashtable->entries[slot];

    for(counter = 0; entry != NULL; counter++){
        if(strcmp(entry->key, key) == 0){

            /* The  only bucket in the slot */
            if(entry->next == NULL && counter == 0){
                hashtable->entries[slot] = NULL;
            }
            /* The first bucket in a slot with other buckets */
            if(entry->next != NULL && counter == 0){
                hashtable->entries[slot] = entry->next;
            }
            /* The last bucket in a slot with other buckets */
            if(entry->next == NULL && counter != 0){
                prev->next = NULL;
            }
            /* Bucket somewhere in the middle of the slot with other buckets */
            if(entry->next != NULL && counter != 0){
                prev->next = entry->next;
            }
            free(entry->key);
            free_data(entry->data);
            free(entry);

            return;
        }
        prev = entry;
        entry = prev->next;
    }
    return;
}

/* Free the data inside the hashtable */
void free_data(Game *data){
    if(data->team_flag == 0){
        free(data->team1);
        free(data->team2);
    }
    free(data); 
    return;
}

/* Get a list of games with the most amount of wins */
void biggest_wins(int line_number, Hash_Array *hashtable){
    int counter, aux_counter;
    int size = 0, max_win=-1, list_size = 10;
    char **team_list;
    Bucket *entry, *aux;
    
    team_list = can_fail_malloc(sizeof(char*)*list_size);

    /* Get a list with all the teams with highest score */
    for(counter = 0; counter < hashtable->size; counter++){
        entry = hashtable->entries[counter];
        
        if (entry == NULL) {
            continue;
        }

        for(aux_counter = 0;;aux_counter++){
            aux = entry->next;

            if(entry->data->score1==max_win){
                size = size + 1;

                team_list[size] = entry->key;
            }
            else if(entry->data->score1>max_win){
                /* add this value to the list */
                size = 0;
                team_list[size] = entry->key; 
                max_win = entry->data->score1;
            }

            if(aux == NULL){
                break;
            }
            
            
            entry = aux;
        }
    }

    /* If there is no team with more than one win */
    if(max_win<0){
        free(team_list);
        return;
    }

    printf("%d Melhores %d\n", line_number, max_win);
    if(size == 0){
        printf("%d * %s\n", line_number, team_list[0]);
        free(team_list);
        return;
    }

    size = size + 1;
    qsort(team_list, size, sizeof(team_list[1024]), compare_str);

    for(counter = 0; counter<size;counter++){
        printf("%d * %s\n", line_number, team_list[counter]);
    }

    free(team_list);
    return;
}

/* Compare function for qsort */
int compare_str(const void * a, const void * b ) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}