#include <stdio.h>
#include <stdlib.h>

enum color{White, Gray, Black};

typedef struct{
    int number;
    int count_arrivel;
    enum color color;
    int nfilhos;
    int *filhos;
    int location;
} Node;

typedef struct stack{
    int value;
    struct stack *next;
}stack;

/* Start Pilha */
static struct stack *top;
void init_stack();
int pop();
void push(int value);
int is_empty();
/* End Pilha */

Node *table;
int max=0, min=0;
int number_total_dominos, number_total_relations;


void initialize();
void putnode(int first_id, int second_id);
void dfs();
int max_location(int id);
int filho_color_white_or_gray(int id);

int main(){
    
    scanf("%d %d", &number_total_dominos, &number_total_relations);

    if(number_total_dominos<2||number_total_relations<0){
        exit(EXIT_FAILURE);
    }
    
    table = (Node*)malloc(sizeof(Node)*number_total_dominos);
    initialize();
    

    int i, first, second;
    for(i=0; i<number_total_relations; i++){
        scanf("%d %d", &first, &second);
        putnode(first-1, second-1);
        table[second-1].count_arrivel++;
    }
    

    dfs();
   

    for(i=0; i<number_total_dominos;i++){
        if(table[i].count_arrivel==0){
            min++;
        }
        if(max<table[i].location){
            max=table[i].location;
        }
    }

    printf("%d %d\n",min,max);

    for(i=0; i<number_total_dominos;i++){
        free(table[i].filhos);
    }
    free(table);


    return 0;
}

void initialize(){
    int i;
    for(i=0; i<number_total_dominos; i++){
        table[i].number = i+1;
        table[i].color = White;
        table[i].count_arrivel = 0;
        table[i].nfilhos = 0;
        table[i].filhos = NULL;
        table[i].location = 1;
    }
}

void putnode(int first, int second){
    if(table[first].nfilhos == 0){
        table[first].filhos =  (int*)malloc(sizeof(int));
        table[first].filhos[0] = second;
        table[first].nfilhos++;
    }else{
        table[first].nfilhos++;
        table[first].filhos = (int*)realloc(table[first].filhos,sizeof(int)*table[first].nfilhos);
        table[first].filhos[table[first].nfilhos-1]= second;
    }
}

void dfs(){
    int i;
    for(i=0;i<number_total_dominos;i++){
        if(table[i].color == White){
            push(i);
            while(!is_empty()){
                int value = top->value;
                table[value].color = Gray;
                int j;
                if(table[value].nfilhos == 0){
                    pop(); 
                    table[value].color = Black;
                    table[value].location = 1;
                }else if(!filho_color_white_or_gray(value)){
                    pop(); 
                    table[value].color = Black;
                    table[value].location = max_location(value);
                }else{
                    for(j=0;j<table[value].nfilhos;j++){
                        if(table[table[value].filhos[j]].color != Black){
                            push(table[value].filhos[j]);
                            table[table[value].filhos[j]].color = Gray;
                        }
                    }
                }
            }
        }
    }

}

int max_location(int id){
    int max=0, i;
    for(i=0; i<table[id].nfilhos;i++){
        if(max<table[table[id].filhos[i]].location){
            max = table[table[id].filhos[i]].location;
        }
    }
    return max +1;
}

int filho_color_white_or_gray(int id){
    int i;
    for(i=0;i<table[id].nfilhos;i++){
        if(table[table[id].filhos[i]].color != Black){
            return 1;
        }
    }
    return 0;
}

/*--------------- Pilha ---------------*/

void init_stack(){
    top = NULL;
}

void push(int value){
    struct stack *new;
    new = (struct stack*)malloc(sizeof(struct stack));
    new->value = value;
    new->next = top;
    top = new;
}
int pop(){
    int value;
    struct stack *old;

    if(!is_empty()){
        value = top->value;
        old = top;
        top = top->next;
        free(old);
        return value;
    }else{
        return -1;
    }
}

int is_empty(){
    return top == NULL;
}