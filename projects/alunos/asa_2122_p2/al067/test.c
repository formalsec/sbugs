#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define DELETED -1 
#define BYV2 2
#define OPEN 4
#define CLOSED -4


typedef struct A{
    int id;
    int parent1;
    int parent2;
    int hasBeenVisited;
}Child;

Child *familyTree;
int *sol;
int *queue1;
int *queue2;

int isValidTree(int len);
int cicleDetected(int el);
void removeFromQueue(int *a, int len);
int addToQueue(int *a, int len, int el);
void firstBFS(int len, int el);
int secondBFS(int len, int el, int el2, int *s);
void bfsDelete(int len, int el);


int main(){
    int v1, v2, n, m, i, child, parent, check;
    scanf("%d%d%d%d", &v1, &v2, &n, &m);
    familyTree = (Child *) can_fail_malloc(sizeof(Child)*n);
    sol = (int*) can_fail_malloc(sizeof(int)*n);
    queue1 = (int*) can_fail_malloc(sizeof(int)*n);
    queue2 = (int*) can_fail_malloc(sizeof(int)*n);
    if(m<0 || v1>n || v1<1 || v2>n || v2<1 || n<1){
        putchar('0');
        return 0;
    }
    
    for(i = 0; i < n; i++){
        Child temp;
        temp.id = i+1;
        temp.parent1 = 0;
        temp.parent2 = 0;
        temp.hasBeenVisited = FALSE;
        familyTree[i] = temp;
        sol[i] = FALSE;
        queue1[i] = 0;
        queue2[i] = 0;
    }
  
    
    for(i = 0; i < m; i++){
        scanf("%d%d", &parent, &child);
        if (child > n || child < 0 || parent > n || parent < 0 || child == parent){
            putchar('0');
            putchar('\n');
            return 0;
        }
        if (familyTree[child-1].parent1 == 0){
            familyTree[child-1].parent1 = parent;
        }
        else if (familyTree[child-1].parent2 == 0 && familyTree[child-1].parent1 != parent){
            familyTree[child-1].parent2 = parent;
        }
        else{
            putchar('\n');
            return 0;
        }
    }

    if(!isValidTree(n)){
        putchar('0');
        putchar('\n');
        return 0;
    }

    if(v1 == v2){
        printf("%d \n", v1);
        return 0;
    }
    
    if(familyTree[v1-1].parent1 == v2 || familyTree[v1-1].parent2 == v2){
        printf("%d \n", v2);
        return 0;
    }

    if(familyTree[v2-1].parent1 == v1 || familyTree[v2-1].parent2 == v1){
        printf("%d \n", v1);
        return 0;
    }

    for(i=0; i<n ; i++){
        familyTree[i].hasBeenVisited = FALSE;
    }

    if(familyTree[v1-1].parent1 == 0 && familyTree[v1-1].parent2 == 0){
        if(familyTree[v2-1].parent1 == 0 && familyTree[v2-1].parent2 == 0){
            printf("-\n");
            return 0;
        }
        firstBFS(n, v2);
        if(familyTree[v1-1].hasBeenVisited == TRUE){
            printf("%d \n", v1);
            return 0;
        }
        else{
           printf("-\n");
            return 0; 
        }
    }
    else if(familyTree[v2-1].parent1 == 0 && familyTree[v2-1].parent2 == 0){
        firstBFS(n, v1);
        if(familyTree[v2-1].hasBeenVisited == TRUE){
            printf("%d \n", v2);
            return 0;
        }
        else{
           printf("-\n");
            return 0; 
        }
    }


    firstBFS(n, v1);
    
    if (familyTree[v2-1].hasBeenVisited == TRUE){
        printf("%d \n", v2);
        return 0;
    }
    

    check = secondBFS(n, v2, v1, &sol[0]);

    
    if (check == TRUE){
        printf("%d \n", v1);
            return 0;
    }

    for(i = 0; i<n ; i++){
        if (sol[i] == TRUE && familyTree[i].hasBeenVisited!=DELETED){
            printf("%d ", i+1);
            check = TRUE;
        }
    }

    if(check == FALSE){
        printf("-\n");
    }
    else{
        putchar('\n');
    }

    return 0;
}

void removeFromQueue(int *a, int len){
    int i, elem, n = 0;
    for (i = len-1; i>= 0; i--){
        elem = a[i];
        a[i] = n;
        n = elem;
    }
}


int addToQueue(int *a, int len, int el){
    int i;
    for(i = 0; i< len; i++){
        if(a[i] == 0){
            a[i] = el;
            return TRUE;
        }
    }
    return FALSE;
}

int isValidTree(int len){
    int i;
    for (i = 0; i<len ; i++){
        if(familyTree[i].hasBeenVisited != CLOSED){
            if(cicleDetected(i+1)){
                return FALSE;
            }
        }
    }
    return TRUE;
}

int cicleDetected(int el){
    int p1, p2;
    familyTree[el-1].hasBeenVisited = OPEN;
    p1 = familyTree[el-1].parent1;
    p2 = familyTree[el-1].parent2;
    if(p1!= 0){
        if(familyTree[p1-1].hasBeenVisited == OPEN){
            return TRUE;
        }
        else if(familyTree[p1-1].hasBeenVisited != CLOSED){
            if(cicleDetected(p1)){
                return TRUE;
            }
        }
    }
    if(p2!= 0){
        if(familyTree[p2-1].hasBeenVisited == OPEN){
            return TRUE;
        }
        else if(familyTree[p2-1].hasBeenVisited != CLOSED){
            if(cicleDetected(p2)){
                return TRUE;
            }
        }
    }
    familyTree[el-1].hasBeenVisited = CLOSED;
    return FALSE;
}

void firstBFS(int len, int el){
    int p1, p2;
    Child current = familyTree[el-1];
    addToQueue(&queue1[0], len, el);
    current.hasBeenVisited = TRUE;
    while(queue1[0] != 0){
        current = familyTree[(queue1[0])-1];
        p1 = current.parent1;
        p2 = current.parent2;
        if(p1 != 0 && !familyTree[p1-1].hasBeenVisited){
            addToQueue(&queue1[0], len, p1);
            familyTree[p1-1].hasBeenVisited = TRUE;
        }
        if(p2 != 0 && !familyTree[p2-1].hasBeenVisited){
            addToQueue(&queue1[0], len, p2);
            familyTree[p2-1].hasBeenVisited = TRUE;
        }
        removeFromQueue(&queue1[0], len);
    }
}

int secondBFS(int len, int el, int el2, int *s){
    int p1, p2;
    Child current;
    addToQueue(&queue1[0], len, el);
    while(queue1[0] != 0){
        current = familyTree[(queue1[0])-1];
        p1 = current.parent1;
        p2 = current.parent2;
        if (current.id == el2){
            return TRUE;
        }
        if (current.hasBeenVisited == TRUE){
            s[current.id-1] = TRUE;
            bfsDelete(len, current.id);
        }
        else {
            if (p1 != 0 && familyTree[p1-1].hasBeenVisited != DELETED && familyTree[p1-1].hasBeenVisited != BYV2){
                addToQueue(&queue1[0], len, p1);
                if(familyTree[p1-1].hasBeenVisited != TRUE){
                    familyTree[p1-1].hasBeenVisited = BYV2;
                } 
            }
            if (p2 != 0 && familyTree[p2-1].hasBeenVisited != DELETED && familyTree[p2-1].hasBeenVisited != BYV2){
                addToQueue(&queue1[0], len, p2);
                if(familyTree[p2-1].hasBeenVisited != TRUE){
                    familyTree[p2-1].hasBeenVisited = BYV2;
                } 
            }
        }
        removeFromQueue(&queue1[0], len);
    }
    return FALSE;
}

void bfsDelete(int len, int el){
    int p1, p2;
    Child current;
    addToQueue(&queue2[0], len, el);
    while(queue2[0] != 0){
        current = familyTree[queue2[0]-1];
        p1 = current.parent1;
        p2 = current.parent2;
        if(p1 != 0){
            addToQueue(&queue2[0], len, p1);
            familyTree[p1-1].hasBeenVisited = DELETED;
        }
        if(p2 != 0){
            addToQueue(&queue2[0], len, p2);
            familyTree[p2-1].hasBeenVisited = DELETED;
        }
        removeFromQueue(&queue2[0], len);
    }
}