#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "teams.h"

int get_list_size(Teams * head) { 
    int count = 0;  
    Teams * current = head;  
    while (current != NULL) { 
        count++; 
        current = current->next; 
    } 
    return count; 
} 

Teams * add_team_to_list(Teams ** head, char *name) { 
    /* allocate space */
    Teams *new_team = (Teams*) can_fail_malloc(sizeof(Teams)); 
    Teams *current = *head;  

    /* Put in the data  */
    memcpy(new_team->team_name, name, strlen(name)+1);
    new_team->matches_won = 0;
  
    new_team->next = NULL; 
  
    /* If the Linked List is empty, then make the new node as head */
    if (*head == NULL) { 
       *head = new_team;
    } else {
        /* Traverse till the last node */
        while (current->next != NULL) 
            current = current->next; 
       
        current->next = new_team;
    }
    return *head;
}

Teams * delete_team_from_list(Teams ** head, char* t_name) {
    Teams *current, *prev;

    prev = NULL;

    for (current = *head; current != NULL; prev = current, current = current->next) {
        if (strcmp(current->team_name, t_name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return *head;
        }
    }
    return *head;
}

Teams * add_team_highest(Teams ** teams_highest, Teams ** teams, int highest_won) {
    /* allocate space */
    Teams *current;

    for (current = *teams; current != NULL; current = current->next) {
        if (current->matches_won == highest_won) {
          *teams_highest = add_team_to_list(teams_highest, current->team_name);

        }
    }
    sort_teams_alpha(teams_highest);
    return *teams_highest;
}

Teams * increment_matches_won(Teams ** head, char* name) {
    Teams *current;

    for (current = *head; current != NULL; current = current->next) {
        if (strcmp(current->team_name, name) == 0) {
            current->matches_won++;
        }
    }
    return *head;
}

Teams * decrement_matches_won(Teams ** head, char* name) {
    Teams *current;

    for (current = *head; current != NULL; current = current->next) {
        if (strcmp(current->team_name, name) == 0) {
            current->matches_won--;
        }
    }
    return *head;
}

bool team_exists(Teams ** head, char* name) {
    Teams *current;

    for (current = *head; current != NULL; current = current->next) {
        if (strcmp(current->team_name, name) == 0) {
            return true;
        }
    }
    return false;
}

int max_won(Teams ** head) {
    int max = 0;
    Teams *current;

    for (current = *head; current != NULL; current = current->next) {
        if (max < current->matches_won) {
            max = current->matches_won;
        }
    }
    return max;
}

void print_matches_won(Teams ** head, char* name) {
    Teams *current;

    for (current = *head; current != NULL; current = current->next) {
        if (strcmp(current->team_name, name) == 0) {
            printf("%s %d\n", current->team_name, current->matches_won);
        }
    }
}

void print_team_list(int nl, Teams * head) {
    Teams * current = head;

    while (current != NULL) {
    	printf("%d * %s\n", nl, current->team_name);
        current = current->next;
    }

}

void free_teams(Teams * head) {
   Teams * tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}


void sort_teams_alpha(Teams ** head) {
    Teams *current;
    char *tmp = can_fail_malloc(MAX_BUFF);
    current = *head;


    if (current) {
        while (current && current->next) {
            memset(tmp, 0, MAX_BUFF);
            if (strcmp(current->team_name, current->next->team_name) > 0) {
                strcpy(tmp, current->team_name);
                strcpy(current->team_name, current->next->team_name);
                strcpy(current->next->team_name, tmp);
            }
            current = current->next;
        }
    }
    free(tmp);

}