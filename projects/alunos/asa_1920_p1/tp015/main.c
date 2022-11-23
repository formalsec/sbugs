#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*Grupo 15 Diogo Silva ist193706   Martim Pimentel ist 193738*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Student{
    int id;
    int grade;
    int *adjs;
    int low_value;
    int onStack;
    int numberAdj;
    int number_scc;
}student;

typedef struct Sccs{
    int *adjs;
    int *vertexs;
    int num_vertexs;
    int num_adjs;
    int grade;
    int id;
}scc;

student *students;
scc *sccs_list;
int count = 0;
int scc_count = 0;
int *stack;
int ix = 0;
int idx = 0;

int pop(){
    int aux = stack[ix-1];
    stack[ix-1] = -1;
    ix--;
    return aux;
}

void push(int id){
    stack[ix++] = id;
}

void dfs(int id) {
    int i,aux,temp;

    students[id].id = idx;
    students[id].low_value = idx;
    idx++;
    push(id);
    students[id].onStack = 1;

    for(i=0;i<students[id].numberAdj;i++){
        
        if (students[students[id].adjs[i]].id == -1) {
            dfs(students[id].adjs[i]);
            students[id].low_value = students[id].low_value <= students[students[id].adjs[i]].low_value ? students[id].low_value : students[students[id].adjs[i]].low_value;

        }else if(students[students[id].adjs[i]].onStack){
            students[id].low_value = students[id].low_value <= students[students[id].adjs[i]].id ? students[id].low_value : students[students[id].adjs[i]].id;
        }
    }

    if (students[id].id == students[id].low_value){
        temp = ix;

        scc_count++;

        if (scc_count==1){
            sccs_list = can_fail_malloc(sizeof(struct Sccs));
        }else{
            sccs_list = can_fail_realloc(sccs_list, sizeof(struct Sccs)*scc_count);
        }

        sccs_list[scc_count-1].adjs = can_fail_malloc(sizeof(int));
        sccs_list[scc_count-1].vertexs = can_fail_malloc(sizeof(int));
        sccs_list[scc_count-1].num_adjs = 0;
        sccs_list[scc_count-1].num_vertexs = 0;
        sccs_list[scc_count-1].grade = -1;
        sccs_list[scc_count-1].id = -1;

        for(i=0;i<temp;i++){
            aux = pop();
            students[aux].onStack = 0;
            students[aux].low_value = students[id].id;
            students[aux].number_scc = scc_count -1;

            sccs_list[scc_count-1].grade = sccs_list[scc_count-1].grade < students[aux].grade ? students[aux].grade : sccs_list[scc_count-1].grade;
            sccs_list[scc_count-1].num_vertexs++;
            sccs_list[scc_count-1].vertexs = can_fail_realloc(sccs_list[scc_count-1].vertexs, sizeof(int)*(sccs_list[scc_count-1].num_vertexs));
            sccs_list[scc_count-1].vertexs[sccs_list[scc_count-1].num_vertexs-1] = aux;

            if (aux==id) break;

        }
    }
}

void sccs(){
    int i,index;
    for(i=0; i < count; i++){
        if (students[i].id == -1){
            dfs(i);
        }
    }

    for (i=0;i < count;i++){
        int num_scc = students[i].number_scc;
        for (index=0;index<students[i].numberAdj;index++){
            if (students[students[i].adjs[index]].low_value != students[i].low_value){
                sccs_list[num_scc].num_adjs++;
                sccs_list[num_scc].adjs = can_fail_realloc(sccs_list[num_scc].adjs, sizeof(int)*(sccs_list[num_scc].num_adjs));
                sccs_list[num_scc].adjs[sccs_list[num_scc].num_adjs-1] = students[students[i].adjs[index]].number_scc;
            }
        }
    }
}

void processInput() {
    int alunos, adjsc, i, aux1, aux2;
    if (!scanf("%d,%d", &alunos, &adjsc)) {
        printf("Error");
    }

    students = can_fail_malloc(sizeof(student)*(alunos+1));
    stack = can_fail_malloc(sizeof(int)*adjsc);

    for (i = 0; i < alunos; i++) {
        if (!scanf("%d", &students[i].grade)) {
            printf("Error");
        }
        students[i].adjs = can_fail_malloc(sizeof(int)*2);

        students[i].id = -1;

        students[i].low_value = 0;

        students[i].onStack = 0;

        students[i].numberAdj = 0;

        students[i].number_scc = -1;
    }
    for(i=0;i < adjsc;i++){
        if (!scanf("%d %d",&aux1,&aux2)) {
            printf("Error");
        }
        students[aux1-1].numberAdj++;

        students[aux1-1].adjs = can_fail_realloc(students[aux1-1].adjs,sizeof(int)*(students[aux1-1].numberAdj));

        students[aux1-1].adjs[students[aux1-1].numberAdj-1] = aux2-1;

        stack[i] = -1;
    }
    count = alunos;
}

void maxify_dfs(int id){
    int i;

    sccs_list[id].id = id;

    for (i=0;i<sccs_list[id].num_adjs;i++){
        if (sccs_list[sccs_list[id].adjs[i]].id == -1){
            maxify_dfs(sccs_list[id].adjs[i]);
        }
        sccs_list[id].grade =sccs_list[sccs_list[id].adjs[i]].grade < sccs_list[id].grade ? sccs_list[id].grade : sccs_list[sccs_list[id].adjs[i]].grade;
    }

}

void maxify(){
    int i,j;

    for(i=0;i<scc_count;i++){
            maxify_dfs(i);
    }

    for (i=0;i<scc_count;i++){
        for (j=0;j<sccs_list[i].num_vertexs;j++){
            students[sccs_list[i].vertexs[j]].grade = sccs_list[i].grade;
        }
    }
}

int main() {
    int i;
    processInput();
    sccs();
    maxify();
    for(i=0;i<count;i++){
        printf("%d\n",students[i].grade);
    }
    return 0;
}

