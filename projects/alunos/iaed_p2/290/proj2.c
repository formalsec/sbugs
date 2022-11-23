#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* First character of input.*/
char command;
/* Number of last input line.*/
int input_line = 0;
/* Maximum number of characters per team or game.*/
char team[1023];
char team1[1023], team2[1023];
char game[1023];
/* Two variables for the games results.*/
int score1, score2;

/* Linked list to store the teams.*/
typedef struct Team {
    char *name;
    struct Team *next;
} *link;

/* Linked list to store the games.*/
typedef struct Game {
    char *name;
    char *team1;
    char *team2;
    int score1;
    int score2;
    struct Game *next;
} *link2;

/* Create a new node for the new team.*/
link NEW(char* buffer){
    link x = can_fail_malloc(sizeof(struct Team));
    x->name = can_fail_malloc(sizeof(char)*(strlen(buffer)+1)); 
    strcpy(x->name, buffer);
    x->next = NULL;
    return x;
}

/* Insert the new team at the end of the list.*/
link insertEnd(link head, char* name) {
    link x;
    if(head == NULL)
        return NEW(name);
    for(x = head; x->next != NULL; x = x->next)
        ;
    x->next = NEW(name);
    return head;
}

/* Add new team to the lisked list.*/
int add_new_team(){
    scanf("%c %s", &command, team);
    link head;
    link t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->name, team) == 0)
            printf("Equipa existente\n");
    insertEnd(head, team);
    return 0;
}

/* Create a new node for the new game.*/
link2 NEW2(char* buffer){
    link2 x = can_fail_malloc(sizeof(struct Game));
    x->name = can_fail_malloc(sizeof(char)*(strlen(buffer)+1)); 
    strcpy(x->name, buffer);
    x->next = NULL;
    return x;
}

/* Insert the new game at the end of the list.*/
link2 insertEnd2(link2 head, char* name) {
    link2 x;
    if(head == NULL)
        return NEW2(name);
    for(x = head; x->next != NULL; x = x->next)
        ;
    x->next = NEW2(name);
    return head; 
}

/* Add new game to the lisked list.*/
int add_new_game(){
    scanf("%c %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", &command, game, team1, team2, &score1, &score2);
    link Head;
    while(Head != NULL){
        if(strcmp(Head->name, team1) == 0)
            printf("%d Equipa inexistente\n", input_line);
        if(strcmp(Head->name, team2) == 0)
            printf("%d Equipa inexistente\n", input_line);
        Head = Head->next;
    }
    link2 head;
    link2 t;
    for(t = head; t != NULL; t = t->next){
        if(strcmp(t->name, game) == 0) 
            printf("%d Jogo existente\n", input_line);
    insertEnd2(head, game);
    }
    return 0;
}

/* Print the list of all the games by the order they were introduced.*/
int list_games(){
    link2 head;
    link2 t;
    for(t = head; t != NULL; t = t->next)
        printf("%d %s\n",input_line, t->name);
    return 0;
}

/* Print only the node of the asked game.*/
int search_game(){
    scanf("%c %s", &command, game);
    link2 head;
    link2 t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->name, game) == 0)
            printf("%d %s\n",input_line, game); 
    printf("%d Equipa inexistente\n", input_line);
    return 0;
}

/* Print the node of the asked team and how many games that team won.*/
int search_team(){
    return 0;
}

/* Remove the asked game from the list.*/
int delete_game(){
    scanf("%c %s", &command, game);
    link2 head;
    link2 t, prev;
    for(t = head, prev = NULL; t != NULL; prev = t, t = t->next){ 
        if(strcmp(t->name, game) == 0){
            if(t == head)
                head = t->next;
            else
                prev->next = t->next;
            free(t->name);
            free(t);
        }
    }
    printf("%d Jogo inexistente\n", input_line);
    return 0;
}

/* Change the score of a determined game.*/
int change_score(){
    return 0;
}

/* Print the nodes of the teams that won more games by lexicographic order.*/
int list_best(){
    return 0;
}

/* Reads the fist character and executes the corresponding function.*/
int main(){
    char input[10000];
    
    do{  
        input_line++;                                       
        scanf("%s",input);                      
        command = input[0];                     
        switch(command){
            case 'a':
                add_new_game();
                break;
            case 'A':
                add_new_team();
                break;
            case 'l':
                list_games();
                break;
            case 'p':
                search_game();
                break;
            case 'P':
                search_team();
                break;
            case 'r':
                delete_game();
                break;
            case 's':
                change_score();
                break;
            case 'g':
                list_best();
                break;
            case 'x':                           
                return 0;
        }
    } while (strcmp(&command, "x") != 0);         
    return 0;
}
