#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "matches.h"

Matches * add_match_to_list(Matches ** head, char *m_name, char *m_team1, char *m_team2, int m_score1, int m_score2) { 
    /* allocate space */
    Matches *new_match = (Matches*) can_fail_malloc(sizeof(Matches)); 
  
    Matches *last = *head;  
   
    /* Put in the data  */
    memcpy(new_match->match_name, m_name, strlen(m_name)+1);
    memcpy(new_match->team1, m_team1, strlen(m_team1)+1);
    memcpy(new_match->team2, m_team2, strlen(m_team2)+1);
    new_match->score1 = m_score1;
    new_match->score2 = m_score2;

    if (m_score1 > m_score2)
        new_match->winner = 1;
    else if (m_score2 > m_score1)
        new_match->winner = 2;
    else
        new_match->winner = 0;

  
    new_match->next = NULL; 
  
    /* If the Linked List is empty, then make the new node as head */
    if (*head == NULL) { 
       *head = new_match;
    } else {
        /* Traverse till the last node */
        while (last->next != NULL) 
            last = last->next; 
       
        last->next = new_match;
    }
    return *head;
}

bool match_exists(Matches ** head, char* name) {
    Matches *current;

    for (current = *head; current != NULL; current = current->next) {
        if (strcmp(current->match_name, name) == 0) {
            return true;
        }
    }
    return false;
}

bool team_exists_match(Matches ** head, char* name) {
    Matches *current;

    for (current = *head; current != NULL; current = current->next) {
        if (strcmp(current->match_name, name) == 0) {
            return true;
        }
    }
    return false;
}

Matches * delete_match_from_list(Matches ** head, char* m_name) {
    Matches *current, *prev;

    prev = NULL;

    for (current = *head; current != NULL; prev = current, current = current->next) {
        if (strcmp(current->match_name, m_name) == 0) {
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

void print_match_found(Matches ** head, char* name) {
    Matches * current;

    for (current = *head; current != NULL; current = current->next) {
        if (strcmp(current->match_name, name) == 0) {
            printf(" %s %s %s %d %d\n",
            current->match_name, 
            current->team1, current->team2,
            current->score1, current->score2);
        }
    }
}

void free_matches(Matches * head) {
   Matches * tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}