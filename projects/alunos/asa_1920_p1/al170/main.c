#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Analise e Sintese de Algoritmos, IST 2S 19-20    */
/* Entrega de Projeto 1, DCG ist186399              */

#include <stdio.h>
#include <stdlib.h>

long int n_students = 0;
long int n_rel = 0;
long int higher_grade_student;
long int higher_grade;
long int yikes_counter;

int process_input(long int n_students_aux, long int n_rel_aux) {
    if (n_students_aux < 2 || n_rel_aux < 1) {
        return 1;
    }
    return 0;
}

void input_grades(long int grades[][2]) {
    int i;
    for (i = 0; i < n_students; i++) {
        /* holds the student grade */
        scanf("%ld", &grades[i][1]);
        /* holds the finishing_id number - 0 if not processed and 1 if processed */
        grades[i][0] = 0;
    }
}

void input_rel(long int beneficiary[], long int donner[]) {
    int i;
    for (i = 0; i < n_rel; i++) {
        scanf("%ld %ld", &beneficiary[i], &donner[i]);
    }
}

void select_higher_grade_unprocessed(long int grades[][2]) {
    /* ng stands for non global */
    long int higher_grade_ng = 0;
    long int higher_grade_student_ng = 0;
    int i;
    for (i = 0; i < n_students; i++) {
        if (higher_grade_ng < grades[i][1] && grades[i][0] == 0) {
            higher_grade_ng = grades[i][1];
            higher_grade_student_ng = i;
        }
    }
    higher_grade_student = higher_grade_student_ng + 1;
    higher_grade = higher_grade_ng;
}

void update_values(long int grades[][2], long int beneficiary[], long int donner[]) {
    /* stands for position to change - aka beneficiary student */
    long int ptc;
    int i;
    for (i = 0; i < n_rel; i++) {
        if (donner[i] == higher_grade_student) {
            ptc = beneficiary[i];
            ptc -= 1;
            if (grades[ptc][1] < higher_grade) {
                grades[ptc][1] = higher_grade;
            }
        }
    }
}

void process_unprocessed(long int grades[][2]) {
    long int pgtc;
    pgtc = higher_grade_student;
    pgtc -= 1;
    /* change the finishing_id to 1 - to indicate that it is processed */
    grades[pgtc][0] = 1;
}

void process_grades(long int grades[][2], long int beneficiary[], long int donner[]) {
    int i;
    select_higher_grade_unprocessed(grades);
    update_values(grades, beneficiary, donner);
    process_unprocessed(grades);
    for (i = 0; i < n_students; i++) {
        if (grades[i][0] == 0) {
            process_grades(grades, beneficiary, donner);
        }
    }
}

int main() {
    long int n_students_aux;
    long int n_rel_aux;
    int status;

    /* starts recording the number of students and their relations */

    status = 0;
    n_students_aux = 0;
    n_rel_aux = 0;
    scanf("%ld,%ld", &n_students_aux, &n_rel_aux);
    status = process_input(n_students_aux, n_rel_aux);
    if (status == 1) {
        printf("Invalid Input\n");
        return 1;
    }
    n_students = n_students_aux;
    n_rel = n_rel_aux;

    /* starts recording students grades */

    long int grades[n_students][2];
    input_grades(grades);

    /* starts recording students relationships */

    long int beneficiary[n_rel];
    long int donner[n_rel];

    input_rel(beneficiary, donner);

    /* organization steps */

    process_grades(grades, beneficiary, donner);

    int i;
    for (i = 0; i < n_students; i++) {
        printf("%ld\n", grades[i][1]);
    }

    return 0;
}
