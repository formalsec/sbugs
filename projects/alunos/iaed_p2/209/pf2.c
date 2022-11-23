#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[1027];

typedef struct team{
    char *name;
    int victories;
    struct team *next;
} *link;

typedef struct game{
    char *name;
    link team1;
    link team2;
    int score[2];
    struct game *next;
} *link2;

/* funcoes relacionadas com equipas */
link new_team(char* new_name){
    link x = can_fail_malloc(sizeof(struct team));
    x -> name = can_fail_malloc(sizeof(char) * (strlen(new_name) + 1));
    strcpy(x->name, new_name);
    x -> next = NULL;
    x -> victories = 0;
    return x;
}

link insert_team(link head, char* new_name){
    link x = new_team(new_name);
    x->next = head;
    return x;
}

link lookup(link head, char* text){
    link t;
    for(t = head; t != NULL; t = t->next){
        if(strcmp(t->name, text) == 0){
            return t;
        }
    }
    return NULL;
}

/* ------------------------------------ */

/* funcoes relacionadas com jogos */
link2 lookup2(link2 head, char* text){
    link2 t;
    for(t = head; t != NULL; t = t->next){
        if(strcmp(t->name, text) == 0){
            return t;
        }
    }
    return NULL;
}

link2 new_game(char* gm, int t1, int t2, link team_1, link team_2){
    link2 x = can_fail_malloc(sizeof(struct game));
    x -> name = can_fail_malloc(sizeof(char) * (strlen(gm) + 1));
    strcpy(x->name , gm);
    x -> next = NULL;
    x -> score[0] = t1;
    x -> score[1] = t2;
    x -> team1 = team_1;
    x -> team2 = team_2;
    return x;
}

link2 insert_game(link2 head2, char* gm, int t1, int t2, link tt1, link tt2){
    link2 x = new_game(gm, t1, t2, tt1, tt2);
    x->next = head2;
    return x;
}

void printgames(link2 head, int NL){
    link2 x = head;
    if(head == NULL){
        return;
    }
    printgames(head->next, NL);
    printf("%d %s %s %s %d %d\n", NL,x->name, x->team1->name, x->team2->name, x->score[0], x->score[1]);
}

int delete_game(link2 head, char* text){
    link2 t, prev;
    for(t = head, prev = NULL; t != NULL; prev = t, t = t->next){
        if(strcmp(t->name, text) == 0){
            if(t == head){
                head = t->next;
            }else{
                prev->next = t->next;
            }
            if(t->score[0] > t->score[1]){
                t->team1->victories--;
            }
            if(t->score[0] < t->score[1]){
                t->team2->victories--;
            }
            t->next = NULL;
            free(t->name);
            free(t);
            return 0;
        }
    }
    return 1;
}

/* ------------------------------------- */

/* leitura do stdin */
char* new_char_ptr(int size){
    char *ptr = can_fail_malloc(sizeof(char) * (size + 1));
    return ptr;
}

void store_string(char* ptr, int len){
    int i = 0;
    for(i = 0; i <= len; i++){
        *(ptr + i) = buffer[i];
    }
}

char* get_name(){
    char *ptr;
    char letter = ' ';
    int i = 0;

    while(letter != ':' && letter != '\n'){
        letter = getchar();
        buffer[i] = letter;
        i++;
    }
    buffer[i - 1] = '\0';
    ptr = new_char_ptr(i);
    store_string(ptr, i);

    return ptr;
}

int getscore(){
    int score, i = 0;
    char num = ' ';
    while(num != ':' && num != '\n'){
        num = getchar();
        buffer[i] = num;
        i++;
    }
    buffer[i - 1] = '\0';
    score = atoi(buffer);
    return score;
}
/*--------------------------------*/


/* funcoes relacionadas com o comando 'g */

void build_list2(int max, int size, link head, int NL){
    link t;
    char *a[1023], *temp;
    int j, i = 0;
    for(t = head; t != NULL; t = t->next){
        if(t->victories == max){
            a[i] = t->name;
            i++;
        }
    }
    i = 0;
    for (i = 0; i < size; i++) {
        for (j = i+1; j < size; j++)
            if (strcmp(a[i], a[j]) > 0) {
                temp = a[i]; 
                a[i] = a[j]; 
                a[j] = temp; 
        }
    }
    printf("%d Melhores %d\n", NL, max);
    for(i = 0; i < size; i++){
        printf("%d * %s\n", NL, a[i]);
    }

}

void build_list(link head, int NL){
    int max, size = 0;
    link t;
    for(t = head; t != NULL; t = t->next){
        if(t->victories > max){
            size = 1;
            max = t->victories;
        }else if(t->victories == max){
            size++;
        }
    }
    if(size < 1){
        return;
    }
    build_list2(max, size, head, NL);
}
/* ------------------------------------ */


/* just for debbugging */
void print(link head){
    link t;
    for(t = head; t != NULL; t = t->next){
        printf("%s\n", t->name);
    }
}
/* --------------------- */

int main(){
    link head = NULL;                                       /* lista com as equipas */
    link temp, temp2;
    link2 head2 = NULL;                                     /* lista com os jogos */
    link2 tempg;
                                      /* lista usada para comando 'g' */
    char *ptr, *ptr1, *ptr2, choice, space;
    int s1, s2, NL = 0;

    choice = getchar();
    while(choice != 'x'){
        NL++;
        space = getchar();
        if(space == '\n'){}

        if(choice == 'A'){                                  /* adicionar nova equipa */
            ptr = get_name();
            if(lookup(head, ptr) == NULL){
                head = insert_team(head, ptr);
            }else{
                printf("%d Equipa existente.\n", NL);
            }            
            free(ptr);
        }else if(choice == 'P'){                            /* procurar uma equipa na base de dados */
            ptr = get_name();
            temp = lookup(head, ptr);
            if(temp == NULL){
                printf("%d Equipa inexistente.\n", NL);
            }else{
                printf("%d %s %d\n", NL, temp->name, temp->victories);
            }
            free(ptr);
        }else if(choice == 'a'){
            ptr = get_name();                               /* ler nome do jogo */
            ptr1 = get_name();                              /* ler nome das equipas */
            ptr2 = get_name();
            s1 = getscore();
            s2 = getscore();
            temp = lookup(head, ptr1);
            temp2 = lookup(head, ptr2);
            if(lookup2(head2, ptr) != NULL){
                printf("%d Jogo existente.\n", NL);
            }else if(temp == NULL || temp2 == NULL){
                printf("%d Equipa inexistente.\n", NL);  
            }else{
                head2 = insert_game(head2, ptr, s1, s2, temp, temp2);
                if(s1 > s2){
                    temp -> victories ++;
                }else if(s1 < s2){
                    temp2 -> victories ++;
                }
            }
            free(ptr);
            free(ptr1);
            free(ptr2);
        }else if(choice == 'p'){
            ptr = get_name();
            tempg = lookup2(head2, ptr);
            if(tempg == NULL){
                printf("%d Jogo inexistente.\n", NL);
            }else{
                printf("%d %s %s %s %d %d\n", NL, tempg->name, tempg->team1->name, tempg->team2->name, tempg->score[0], tempg->score[1]);
            }
            free(ptr);
        }else if(choice == 'l'){
            printgames(head2, NL);
        }else if(choice == 'r'){
            ptr = get_name();
            if(delete_game(head2, ptr) == 1){
                printf("%d Jogo inexistente.\n", NL);
            }
            free(ptr);
        }else if(choice == 's'){
            ptr = get_name(); 
            s1 = getscore();
            s2 = getscore();
            tempg = lookup2(head2, ptr);
            if(tempg == NULL){
                printf("%d Jogo inexistente.\n", NL);
            }else{
                if(tempg->score[0] > tempg->score[1]){
                    tempg->team1->victories--;
                }else if(tempg->score[0] < tempg->score[1]){
                    tempg->team2->victories--;
                }
                tempg->score[0] = s1;
                tempg->score[1] = s2;
                if(s1 > s2){
                    tempg->team1->victories++;
                }else if(s1 < s2){
                    tempg->team2->victories++;
                }
            }
            free(ptr);
        }else if(choice == 'g'){
            build_list(head, NL);
        }

        choice = getchar();                                
    }
    return 0;
}