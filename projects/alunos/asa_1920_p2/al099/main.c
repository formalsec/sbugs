#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 100



typedef struct cruz{
    int coord[2];
    int type; /*0- normal; 1 - supermarket; 2 - citizen  */
    int visited; /*1 - yes; 0 - no*/
    int reachSize; /* Number of supermarkets reachable by this citizen */
    int used;
    struct cruz ** reach; /* Pointers to all the city blocks that have supermarkets reachable by this citizen */
    struct cruz * adj[4]; /* Pointers to all the city blocks next to the one this citizen lives in  */
} cruz;



int avNum;
int strNum;
int smNum;
int originalsmNum;
int ctNum;
int originalctNum;
int max;
int counter = 0;
cruz ** city;
cruz ** citList;


void processFirstLine(){
    int i;
    city = (cruz **) can_fail_malloc(sizeof(cruz *) * avNum);
    if(!city){
        perror("failed to allocate streets");
		exit(EXIT_FAILURE);
    }
    for(i = 0; i < avNum; i++){
        city[i] = (cruz *)can_fail_malloc(sizeof(cruz) * strNum);
    }
}


void search(cruz * current, cruz * original){
    int i;
    if(current->visited == 1){
        return;
    }
    current->visited = 1;
    for(i = 0 ; i < 4; i++){
        
        if(!(current->adj[i] == NULL)){
            if(current->adj[i]->type == 1 && current->adj[i]->visited == 0){
                int p;
                current->adj[i]->visited = 1;
                original->reachSize++;
                p = original->reachSize;
                original->reach[p - 1] = current->adj[i];
                if(p == smNum){
                    return;
                }

            }else if(current->adj[i]->type == 2){
                current->adj[i]->visited = 1;
            }else {
                if(!(current->adj[i]->visited == 1)){
                    search(current->adj[i], original);
                }
            }
        }
    }
}
void resetVisits(){
    int i, j;
    for(i = 0; i < avNum; i++){
        for(j= 0; j < strNum; j++){
            city[i][j].visited= 0;
        }
    }
}

void find_paths(){
    /* For every citizen on the citizen list, finds all the supermarkets reachable by going
       through every adjacent block, until all have been found or all paths left are blocked
       by a citizen */
    int i;
    for(i = 0; i < ctNum; i++){
        resetVisits();
        if(citList[i] != NULL && citList[i]->type == 2) {
            search(citList[i], citList[i]);
        }
    }
}

void startGraph(){
    /* Initiates the city graph */
    int i, j;
    for(i = 0; i < avNum; i++){
        for(j= 0; j < strNum; j++){
            city[i][j].type = 0;
            city[i][j].visited = 0;
            city[i][j].coord[0] = i + 1;
            city[i][j].coord[1] = j + 1;
        }
    }
}

void swap(int i, int j){
    cruz t = *citList[i];
    citList[i] = citList[j];
    citList[j] = &t;
}
int part(int low, int high){
    int j;
    int pivot = citList[high]->reachSize;
    int i = (low - 1);

    for(j = low; j < high; j++){
        if(citList[j]->reachSize < pivot){
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return (i + 1);
}

void quicksort(int low, int high){
    if(low < high){
        int p = part(low, high);
        quicksort(low, p-1);
        quicksort(p+1, high);
    }
}

int flow(){
    /* The flow is calcuated by sorting the citizen array by number of reachsize prioritizing 
       the citizens who have smaller reachsizes */
    int i, j, start, temp;
    int total = 0;
    start = 0;
    quicksort(0, ctNum-1);
    for(i = 0; i < ctNum; i++){
        temp = citList[i]->reachSize;
        if(temp > 0){
            start = i;
            break;
        }
    }
    for(i = start; i < ctNum; i++){
        temp = citList[i]->reachSize;
        for(j = 0; j < temp; j++){
            if(citList[i]->reach[j]->used == 0){
                total++;
                citList[i]->reach[j]->used = 1;
                break;
            }
        }
    }
    return total;
}

void freeAll(){
    free(city);
}

void adj(){
    /* Attribute all the adjacent points to each coordinate */
    int i,j;
    for(i = 0; i < avNum; i++){
        for(j= 0; j < strNum; j++){
            if(j > 0){
                city[i][j].adj[0] = &city[i][j - 1]; /*esquerda*/
            } else {
                city[i][j].adj[0] = NULL;
            }
            if(j < strNum - 1){
                city[i][j].adj[1] = &city[i][j + 1];/*direita*/
            } else {
                city[i][j].adj[1] = NULL;
            }
            if(i > 0){
                city[i][j].adj[2] = &city[i - 1][j];/*cimA*/
            } else {
                city[i][j].adj[2] = NULL;
            }
            if(i < avNum - 1){
                city[i][j].adj[3] = &city[i + 1][j];/*baixo*/
            } else {
                city[i][j].adj[3] = NULL;
            }
        }
    }
}

int main(){
    char line[MAX_INPUT_SIZE];
    int final, temp, penalty;
    int i = 0;
    penalty = 0;
    final = 0;
    while (fgets(line, sizeof(line)/sizeof(char), stdin)) {
        if(i == 0){
            char * avNums = strtok(line, " ");
            char * strNums = strtok(NULL, "\n");
            avNum = atoi(avNums);
            strNum = atoi(strNums);
            processFirstLine();
        } else if (i == 1){
            char * smNums = strtok(line, " ");
            char * ctNums = strtok(NULL, "\n");
            smNum = atoi(smNums);
            originalsmNum = smNum;
            ctNum = atoi(ctNums);
            originalctNum = ctNum;
            startGraph();
            adj();
            citList = (cruz **)can_fail_malloc(sizeof(cruz *) * ctNum);
        } else if(i <= 1 + originalsmNum){
            char * x = strtok(line, " ");
            char * y = strtok(NULL, "\n");
            int av = atoi(x);
            int st = atoi(y);
            if(city[av- 1][st - 1].type == 0){
                city[av - 1][st - 1].type = 1; /* is a supermarket */
                city[av - 1][st - 1].visited = 0;
                city[av - 1][st - 1].used = 0;
            } else{
                smNum--;
            }
            
        } else if (i <= 1 + originalsmNum + originalctNum){
            char * x = strtok(line, " ");
            char * y = strtok(NULL, "\n");
            int av = atoi(x);
            int st = atoi(y);
            if(city[av- 1][st - 1].type == 0){
                city[av- 1][st - 1].type = 2; /* is where citizens live */
                city[av- 1][st - 1].visited = 0;
                city[av - 1][st - 1].reachSize = 0;
                city[av - 1][st - 1].reach = (cruz **)can_fail_malloc(sizeof(cruz *)* originalsmNum);
                citList[i - 2 - originalsmNum - penalty] = &city[av- 1][st - 1];
            } else if (city[av- 1][st - 1].type == 2){
                /* If it is already a place where citizens live don't change values */
                ctNum--;
                penalty++;
                citList = (cruz **)can_fail_realloc(citList, sizeof(cruz *) * ctNum);
                
            } else if(city[av - 1][st - 1].type == 1){
                /* If it is a supermarket mark it as a citizen but don't add it to the list */
                final++;
                penalty++;
                smNum--;
                ctNum--;
                city[av - 1][st - 1].type = 2;
                citList = (cruz **)can_fail_realloc(citList, sizeof(cruz *) * ctNum);
            }
            if(i == 1 + originalsmNum + originalctNum) break;
        }
        i++;
    }
    
    if(!citList) return 0;
    find_paths();
    temp = flow();
    final = final + temp;
    printf("%d\n", final);
    freeAll();
    return 0;
}