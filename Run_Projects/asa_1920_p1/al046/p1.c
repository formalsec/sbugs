/* PROJETO 1 - ASA
 * 2º semestre 2019/2020
 * Álvaro Louro 86373 */

#include <stdio.h>
#include <stdlib.h>

int n; /*number of vertices*/
int m; /*number of edges*/

int i; /*loop index*/

int total_visited;

void propagate(int current_grade, int current_index, int grades[], int sources[], int destinations[], int visited[]) {
    
    visited[current_index] = 1;
    total_visited++;
    
    int k;
    
    for(k = 0; k < m; k++) {
        if(sources[k] == current_index) {
            if(!visited[destinations[k]] && grades[destinations[k]] < current_grade) {
                grades[destinations[k]] = current_grade;
                propagate(current_grade, destinations[k], grades, sources, destinations, visited);
            }
        }
    }
    
    return;
}

int main() {
    
    n = 0;
    m = 0;
    i = 0;
    total_visited = 0;
    
    /*read input*/
    
    if(scanf("%d,%d", &n, &m) != 2)
        return 0;
    
    int grades[n];
    int friends[2][m];
    
    int highest = 0; /*current highest grade*/
    int highest_index = 0;
    int found; /*flag*/
    
    int visited[n];
    
    for(i = 0; i < n; i++) {
        if(scanf("%d", &grades[i]) != 1)
            return 0;
        
        visited[i] = 0; /*initialize array*/
    }
    
    /*invert graph as it is read from input*/
    
    int hasZero = 0;
    
    for(i = 0; i < m; i++) {
        if(scanf("%d %d", &friends[1][i], &friends[0][i]) != 2)
            return 0;
        
        if(friends[0][i] == 0 || friends[1][i] == 0)
            hasZero = 1;
        
        if(!hasZero) {
            friends[0][i] = friends[0][i] - 1;
            friends[1][i] = friends[1][i] - 1;
        }
    }
    
    do {
        
        /*find highest grade (non visited)*/
        
        found = 0;
        
        for(i = 0; i < n; i++) {
            if(!visited[i] && grades[i] >= highest) {
                highest = grades[i];
                highest_index = i;
                found = 1;
            }
        }
        
        if(!found) {
            
            /*reset highest and try again*/
            
            highest = 0;
            
            for(i = 0; i < n; i++) {
                if(!visited[i] && grades[i] >= highest) {
                    highest = grades[i];
                    highest_index = i;
                    found = 1;
                }
            }
        }
        
        propagate(grades[highest_index], highest_index, grades, friends[0], friends[1], visited);
        
    } while(total_visited != n);
    
    for(i = 0; i < n; i++)
        printf("%d\n", grades[i]);
    
    return 0;
}