#include <stdio.h>
#include <stdlib.h>

/*Declarations of constants*/
#define WHITE 1000
#define GREY 1001
#define BLACK 1002

/*Declaration of new variable types*/
typedef struct Person {
    int grade;
    int pos;
    int i_pos;
    int n_friends;
    int current_friend;
    int color;                       /*Color of the node*/
    struct Person** friends;         /*Array of pointers to the following nodes*/
} person;

typedef struct Dummy {
    int grade;
    int pos;
} dummy;

/*Declaration of functions*/
int get_next_node(int, person*);
int close_node(int, person*);
int search(int, int, person*, dummy*);
void heapify(dummy* array, int, int);

/*Main Program*/
int main(int argc, char *argv[]) {
    /*Initialization of variables*/
    int n_nodes, n_c, current, i, p, c, stack_size, next, n_dummies;
    person* array;
    person* stack;
    dummy* dummyArray;
    dummy aux;

    scanf("%d,%d", &n_nodes, &n_c);

    array = malloc(sizeof(person)*(n_nodes+1));
    dummyArray = malloc(sizeof(dummy)*(n_nodes+1));
    stack = malloc(sizeof(person));

    /*Stores the nodes grade and Initiates the other variables*/
    for (i=1;i<=n_nodes;i++) {
        scanf("%d", &array[i].grade);
        array[i].pos = i;
        array[i].i_pos = i;
        array[i].n_friends = 0;
        array[i].current_friend = 0;
        array[i].color = WHITE;
        array[i].friends = malloc(sizeof(person*));
        dummyArray[i-1].grade = array[i].grade;
        dummyArray[i-1].pos = i;
    }

    /*Stores the connections between the nodes*/
    for(i=0;i<n_c;i++) {
        scanf("%d %d", &p, &c);
        array[p].friends = realloc(array[p].friends, sizeof(person**)*(array[p].n_friends + 1));
        array[p].friends[array[p].n_friends] = &array[c];
        array[p].n_friends++;
    }

    /*Sorting the array*/
    n_dummies = sizeof(dummyArray)/sizeof(dummy);
    for(i=(n_dummies/2)-1;i>=0;i--) {
        heapify(dummyArray, n_dummies, i);
    }

    for(i=n_nodes-1;i>=0;i--) {
        aux = dummyArray[i];

        dummyArray[i] = dummyArray[0];
        dummyArray[0] = aux;

        heapify(dummyArray, i, 0);
    }

    /*for(i=0;i<n_nodes;i++) printf("%d ", dummyArray[i].grade);
    printf("\n");*/

    /*Main Loop*/
    current = 0;
    stack_size = 1;
    stack[0] = array[dummyArray[0].pos];
    array[dummyArray[0].pos].color = GREY;
    while (1==1) {

        next = get_next_node(stack[stack_size-1].pos, array);

        if(next == -1) {
            /*pops the last element in the array*/
            close_node(stack[stack_size-1].pos, array);
            stack = realloc(stack, sizeof(person)*(stack_size-1));
            stack_size--;
        } else {
            /*adds the new element*/
            stack = realloc(stack, sizeof(person)*(stack_size+1));
            stack[stack_size] = array[next];
            stack_size++;
        }

        if (stack_size == 0) {
            current = search(current, n_nodes, array, dummyArray);
            if(current != -1) {
                stack = realloc(stack, sizeof(person)*(stack_size+1));
                stack[stack_size] = array[dummyArray[current].pos];
                array[dummyArray[current].pos].color = GREY;
                stack_size++;
            } else {
                break;
            }
            
        }
    }

    for(i=1;i<=n_nodes;i++) {
        printf("%d\n", array[i].grade);
    }

    /*free the memory*/
    for(i=1;i<=n_nodes;i++) {
        free(array[i].friends);
    }
    free(array);

    return 0;
}

/*Implementation of the functions*/
void heapify(dummy* array, int n_node, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    dummy aux;

    if(l<n_node && array[l].grade<array[largest].grade) {
        largest = l;
    }

    if (r<n_node && array[r].grade<array[largest].grade) {
        largest = r;
    }

    if(largest != i) {
        aux = array[i];
        array[i] = array[largest];
        array[largest] = aux;

        heapify(array, n_node, largest);
    }
}

int get_next_node(int pos, person* array) {
    int i, current, limit;
    current = array[pos].current_friend;
    limit = array[pos].n_friends;

    for(i=current;i<limit;i++) {
        if(array[pos].friends[i]->color == WHITE) {
            array[pos].current_friend = i;
            if (array[pos].friends[i]->grade > array[pos].grade) {
                array[pos].grade = array[pos].friends[i]->grade;
            }
            array[pos].friends[i]->color = GREY;
            return array[pos].friends[i]->pos;
        }
    }

    return -1;
}

int close_node(int pos, person* array) {
    int i;

    for(i=0;i<array[pos].n_friends;i++) {
        if(array[pos].friends[i]->grade > array[pos].grade) {
            array[pos].grade = array[pos].friends[i]->grade;
        }
    }

    array[pos].color = BLACK;

    return 0;
}

int search(int current, int n_nodes, person* array, dummy* dummyArray) {
    int i;

    for(i=current;i<n_nodes;i++) {
        if(array[dummyArray[i].pos].color == WHITE) {
            return i;
        }
    }

    return -1;
}