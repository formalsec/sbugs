#ifndef TEAM_H_
#define TEAM_H_

#define MT 101


/*structure with all team's caracteristics, plus "exists"
that works as a boolean to assist on the search function*/
typedef struct teamNode{
    char *name;
    int wins,exists;
    struct teamNode *next;
}TeamNode;

/*hash function from the subject's slides*/
int hashTeam(char *name);

/*adds a team to a certain linked list and puts it in the beggining of the list*/
TeamNode* addTeam(TeamNode *head,char *n);

/*returns the team with the name n*/
TeamNode* searchTeam(TeamNode *head,char *n);

#endif
