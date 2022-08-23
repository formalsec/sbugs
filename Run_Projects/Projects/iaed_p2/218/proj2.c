#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 1024			/* Maximum length of a received string */
#define HASHNUM 1019		/* size of hashtables */

/* Game struct - holds the information of games that are input to the system */
struct Game
{
	char* name;
	char* team1;
	char* team2;
	int team1Score;
	int team2Score;
} Game;

/* Team struct - holds the information of teams that are input to the system*/
struct Team
{
	char* name;
	int winCount;
} Team;

/* gNode struct - struct that defines the nodes that are used to hold game information */
struct gNode
{
	struct Game* value;
	struct gNode* hashNext; 
	struct gNode* chronoNext;
	struct gNode* chronoPrev;
} gNode;

/*tNode struct - struct that defines the nodes that are used to hold team information */
struct tNode
{
	struct Team* value;
	struct tNode* next; 
} tNode;

/* Global variables */
int NL; 						/* Command number */
struct gNode* Games[HASHNUM]; 	/* Hashtable that holds the game nodes */
struct tNode* Teams[HASHNUM];	/* Hashtable that holds the team nodes */
struct gNode* ChronoHead;		/* Head of a linked list that holds all game nodes in chronological order */
struct gNode* ChronoTail;		/* Tail of a linked list that holds all game nodes in chronological order */

/* hash functions that hashes a key */
int hash(char *toBeHashed)
{
	int i  = 0;
	while(*toBeHashed != '\0')
	{ 
		i += (*toBeHashed-'a')%26;
		toBeHashed ++;
	}
	/* Returns absolute value of hash key */
	return i>=0 ? i%HASHNUM : (-1)*i%HASHNUM;
}

/* function that initialises both hashtables */
void initialiseHashTables()
{
	int i;
	for (i = 0; i < HASHNUM; ++i)
	{
		Games[i] = NULL;
		Teams[i] = NULL;
	}
}

/* function that adds a win to the provided team's winCount */
void addWin(char* teamName)
{
	struct tNode* tHeadCopy;
	int index = hash(teamName);
	for (tHeadCopy=Teams[index]; tHeadCopy!=NULL; tHeadCopy=tHeadCopy->next)
	{
		if (strcmp(tHeadCopy->value->name, teamName)==0)
		{
			tHeadCopy->value->winCount++;
		}
	}
}

/* functon that removes a win from the provided team's winCount */
void removeWin(char* teamName)
{
	struct tNode* tHeadCopy;
	int index = hash(teamName);
	for (tHeadCopy=Teams[index]; tHeadCopy!=NULL; tHeadCopy=tHeadCopy->next)
	{
		if (strcmp(tHeadCopy->value->name, teamName)==0)
		{
			tHeadCopy->value->winCount--;
		}
	}
}

/* function that adds a game to the hashtable after verifying if it is elegible to be added */
void addGame(char command[])
{
	char delim[2] = ":";
	struct gNode* head;
	struct tNode* tHead;
	int gameExists = 0;
	int teamExists1 = 0;
	int teamExists2 = 0;
	char* token;
	int index;
	int tIndex1;
	int tIndex2;
	struct gNode* newptr = malloc(sizeof(gNode));
	struct Game* temp = malloc(sizeof(Game));
	/* game name */
	token = strtok(command, delim);
	temp->name = malloc(sizeof(char)*(strlen(token)+1));
	strcpy(temp->name, token);
	/* team 1 name */ 
	token = strtok(NULL, delim);
	temp->team1 = malloc(sizeof(char)*(strlen(token)+1));
	strcpy(temp->team1, token);
	/* team 2 name */ 
	token = strtok(NULL, delim);
	temp->team2 = malloc(sizeof(char)*(strlen(token)+1));
	strcpy(temp->team2, token);
	/* team 1 score */ 
	token = strtok(NULL, delim);
	temp->team1Score = strtol(token, NULL, 10);
	/* team 2 score */ 
	token = strtok(NULL, delim);
	temp->team2Score = strtol(token, NULL, 10);
	/* adding the value to the node */
	newptr->value = temp;
	newptr->hashNext = NULL;
	newptr->chronoNext = NULL;
	newptr->chronoPrev = NULL;
	/* now we have to check if it can be added */
	index = hash(newptr->value->name);
	tIndex1 = hash(newptr->value->team1);
	tIndex2 = hash(newptr->value->team2);
	/* checks if the name of team 1 is in use to see if it exists */
	if(Teams[tIndex1] == NULL || Teams[tIndex2] == NULL)
	{
		teamExists1 = 0;
		teamExists2 = 0;
	} else 
	{
		/* verifies that team1 exists  */
		for(tHead = Teams[tIndex1]; tHead != NULL; tHead = tHead->next)
		{
			if(strcmp(tHead->value->name, newptr->value->team1)==0)
			{
				teamExists1 = 1;
			}
		}
		/* verifies that team2 exists */
		for(tHead = Teams[tIndex2]; tHead != NULL; tHead = tHead->next)
		{
			if(strcmp(tHead->value->name, newptr->value->team2)==0)
			{
				teamExists2 = 1;
			}
		}
	}
	/* checks if a game witht the same name exists already */
	for(head = Games[index]; head != NULL; head = head->hashNext)
	{
		if (strcmp(head->value->name, newptr->value->name)==0)
		{
			gameExists = 1; /* flag to determine if it exists */
		}
	}
	if(gameExists == 1)
	{
		printf("%d %s\n", NL, "Jogo existente.");
		/* if the game cant be added then everything needs to be freed */
		free(newptr);
		free(temp->name);
		free(temp->team1);
		free(temp->team2);
		free(temp);

	} else if(teamExists1 == 0 || teamExists2 == 0) 
	{
		printf("%d %s\n", NL, "Equipa inexistente.");
		/* if the game cant be added then everything needs to be freed */
		free(newptr);
		free(temp->name);
		free(temp->team1);
		free(temp->team2);
		free(temp);

	} else if(Games[index] == NULL) 
	{
		Games[index] = newptr;
		/* ChronoHead si only NULL when there are no games in the system */
		if(ChronoHead == NULL)
		{
			/* updates winCount of teams */
			if(newptr->value->team1Score > newptr->value->team2Score)
			{
				addWin(newptr->value->team1);
			} else if(newptr->value->team1Score < newptr->value->team2Score)
			{
				addWin(newptr->value->team2);
			}
			/* makes first assign of game to the chonological list */
			ChronoHead = newptr;
			ChronoTail = newptr;
		} else 
		{
			/* updates winCount of teams */
			if(newptr->value->team1Score > newptr->value->team2Score)
			{
				addWin(newptr->value->team1);
			} else if(newptr->value->team1Score < newptr->value->team2Score)
			{
				addWin(newptr->value->team2);
			}
			/* updates links for the chronological list */
			newptr->chronoPrev = ChronoTail;
			ChronoTail->chronoNext = newptr;
			ChronoTail = newptr;
		}
	} 
	else
	{
		/* updates winCount of team */
		if(newptr->value->team1Score > newptr->value->team2Score)
		{
			addWin(newptr->value->team1);
		} else if(newptr->value->team1Score < newptr->value->team2Score)
		{
			addWin(newptr->value->team2);
		}
		/* adds the game as first element of the linked list at the specified index */
		newptr->hashNext = Games[index];
		Games[index] = newptr;
		/* updates links for chronological list */
		newptr->chronoPrev = ChronoTail;
		ChronoTail->chronoNext = newptr;
		ChronoTail = newptr;

	}
}

/* function that adds team to hashtable */
void addTeam(char command[])
{
	struct tNode* tHead;
	int index = hash(command);
	int teamExists = 0;
	struct tNode* newptr = malloc(sizeof(tNode));
	struct Team* temp = malloc(sizeof(Team));
	temp->name = malloc(sizeof(char)*(strlen(command)+1));
	/* adds values to team and tNode */
	strcpy(temp->name, command);
	temp->winCount = 0;
	newptr->value = temp;
	newptr->next = NULL;
	/* adds team in at once if there is no other team sharing the same hash key */
	if(Teams[index]==NULL)
	{
		Teams[index] = newptr;
	} else 
	{
		/* checks if the name is in use */
		for (tHead = Teams[index]; tHead != NULL; tHead = tHead->next)
		{
			if(strcmp(tHead->value->name, command)==0)
			{
					teamExists = 1;
			}
		}
		if (teamExists == 1)
		{
			printf("%d %s\n", NL, "Equipa existente.");
			/* if the team cant be added, everything has to be freed */
			free(newptr);
			free(temp->name);
			free(temp);
		} else 
		{
			/* adds in team at the start of the linked list at that index */
			newptr->next = Teams[index];
			Teams[index] = newptr;
		}
	}

}

/* function that displays information of games in chronological order*/
void listChrono()
{
	struct gNode* headCopy;
	/* loops through the chronological list while printing the information */
	for(headCopy = ChronoHead; headCopy != NULL; headCopy = headCopy->chronoNext)
	{
		printf("%d %s %s %s %d %d\n", NL, headCopy->value->name, headCopy->value->team1, headCopy->value->team2, headCopy->value->team1Score, headCopy->value->team2Score);
	}
}

/* function that searches for a game and if found displays the information on it */
void searchGame(char command[]) 
{
	struct gNode* gHeadCopy;
	struct gNode* printIt;
	int gFound = 0;
	int index = hash(command);
	/* goes through the linked list at the right index to see if the game exists and makes a copy of it */
	for (gHeadCopy = Games[index]; gHeadCopy!=NULL && gFound==0; gHeadCopy = gHeadCopy->hashNext)
	{
		if (strcmp(gHeadCopy->value->name, command)==0)
		{
			printIt = gHeadCopy;
			gFound = 1;
		}
	}
	if (gFound == 0)
	{
		printf("%d %s\n", NL, "Jogo inexistente.");
	} else if(gFound == 1) 
	{
		printf("%d %s %s %s %d %d\n", NL, printIt->value->name, printIt->value->team1, printIt->value->team2, printIt->value->team1Score, printIt->value->team2Score);
	}
}

/* function that searches for a team and if found, displays the information on it */
void searchTeam(char command[])
{
	struct tNode* tHeadCopy;
	struct tNode* printIt;
	int tFound = 0;
	int index = hash(command);
	/* goes through linked list at the right index to see if the team exists and makes a copy of it */
	for (tHeadCopy = Teams[index]; tHeadCopy!=NULL; tHeadCopy = tHeadCopy->next)
	{
		if (strcmp(tHeadCopy->value->name, command)==0)
		{
			printIt = tHeadCopy;
			tFound = 1;
		}
	}
	if (tFound == 0)
	{
		printf("%d %s\n", NL, "Equipa inexistente.");
	} else if(tFound == 1) 
	{
		printf("%d %s %d\n", NL, printIt->value->name, printIt->value->winCount);
	}

}

/* function that frees all allocated memory */
void freeAll()
{
	int i;
	struct gNode* toDestroy;
	struct gNode* nextt = NULL;
	struct tNode* toDestroyT;
	struct tNode* nexttT = NULL;
	/* goes through the chronological list while freeing each node it passes by*/
	for (toDestroy=ChronoHead; toDestroy!=NULL; toDestroy = nextt)
	{
		/* creates copy of pointer to next node in list */
		nextt = toDestroy->chronoNext;
		/* frees all the things that need to be freed */
		free(toDestroy->value->name);
		free(toDestroy->value->team1);
		free(toDestroy->value->team2);
		free(toDestroy->value);
		free(toDestroy);
	}
	/* goes through indices of hashtable */
	for(i=0; i<HASHNUM; i++)
	{
		/* goes through linked list while freeing each node it passes by */
		for (toDestroyT=Teams[i]; toDestroyT!=NULL; toDestroyT=nexttT)
		{
			nexttT = toDestroyT->next;
			free(toDestroyT->value->name);
			free(toDestroyT->value);
			free(toDestroyT);
		}
	}
}

/* function that changes score of a game */
void changeScore(char command[])
{
	struct gNode* gCopy;
	char delim[2] = ":";
	char theGame[LEN];
	int index;
	int found;
	int newScore1;
	int newScore2;
	char *token;
	token = strtok(command, delim);
	/* game name */
	strcpy(theGame, token);
	/* new score 1 */
	token = strtok(NULL, delim);
	newScore1 = strtol(token, NULL, 10);
	/* new score 2 */
	token = strtok(NULL, delim);
	newScore2 = strtol(token, NULL, 10);
	/* set the right index to be searched */
	index = hash(theGame);
	found = 0;
	/* goes througb linked list at the right index */
	for (gCopy=Games[index]; gCopy!=NULL && found==0; gCopy=gCopy->hashNext)
	{
		/* if the game is found then the scores are changed and a win is added and removed from the teams affected if needed */
		if(strcmp(gCopy->value->name, theGame)==0)
		{
			if (gCopy->value->team1Score > gCopy->value->team2Score)
			{
				removeWin(gCopy->value->team1);
			}
			else if(gCopy->value->team1Score < gCopy->value->team2Score) 
			{
				removeWin(gCopy->value->team2);
			}
			gCopy->value->team1Score = newScore1;
			gCopy->value->team2Score = newScore2;
			if (newScore1 > newScore2)
			{
				addWin(gCopy->value->team1);
			}
			else if(newScore1 < newScore2) 
			{
				addWin(gCopy->value->team2);
			}
			found = 1;
		}
	}
	if (found == 0)
	{
		printf("%d %s\n", NL, "Jogo inexistente.");
	}
}

/* functions that frees a specific game node */
void gNodeFree(struct gNode* freeThisOne)
{
	/* Freeing of memory after removal */
	free(freeThisOne->value->name);
	free(freeThisOne->value->team1);
	free(freeThisOne->value->team2);
	free(freeThisOne->value);
	free(freeThisOne);
}

/* function that removes a node from the chronological list */
void removeFromChrono(struct gNode* removeIt)
{
	/*CASE Head - if the node is at the head of the chronological list */
	if (removeIt==ChronoHead)
	{
		/*CASE Only member - if the node is the only one to exist at the moment */
		if (ChronoHead->chronoNext == NULL)
		{
			ChronoHead = NULL;
			ChronoTail = NULL;
		} 
		else 
		{
			ChronoHead = ChronoHead->chronoNext;
			ChronoHead->chronoPrev = NULL;
		}
	} 
	/*CASE Tail - if the node is at the tail of the chronological list*/
	else if(removeIt==ChronoTail)
	{
		/* The tail is moved down one and once updated the chronoNext pointer is removed*/
		ChronoTail = ChronoTail->chronoPrev;
		ChronoTail->chronoNext = NULL;
	} 
	/*CASE Middle - if the node is nor head nor tail then it is somewhere in the middle*/
	else 
	{
		/* Makes previous node's chronoNext equal to chronoNext of node i want to get rid of */
		removeIt->chronoPrev->chronoNext = removeIt->chronoNext;
		/* Same as previous command but for chronoPrev */
		removeIt->chronoNext->chronoPrev = removeIt->chronoPrev;
	}
	gNodeFree(removeIt);
}

/* function that removes a game from the system */
void removeGame(char command[])
{
	struct gNode* gCopy; 
	struct gNode* freeThisOne;
	int found = 0;
	int index = hash(command);
	/*CASE - Node at beginnning of linked list in hashtable */
	if(Games[index]==NULL)
	{
		/* There isnt even a different value in the same hash key */
		found = 0; 
	} else if (strcmp(Games[index]->value->name, command)==0)
	{
		found = 1;
		freeThisOne = Games[index];
		/* Sets the second node as the head */
		Games[index]=Games[index]->hashNext;
		if (freeThisOne->value->team1Score > freeThisOne->value->team2Score)
		{
			removeWin(freeThisOne->value->team1);
		} 
		else if(freeThisOne->value->team1Score < freeThisOne->value->team2Score) 
		{
			removeWin(freeThisOne->value->team2);
		}
		removeFromChrono(freeThisOne);
	} else
	{
		/* loops through the linked list at the index */
		for (gCopy=Games[index]; gCopy!=NULL && found==0; gCopy=gCopy->hashNext)
		{
			/* only continues if the next node is not NULL */
			if(gCopy->hashNext!=NULL) 
			{
				if(strcmp(gCopy->hashNext->value->name, command)==0)
				{
					/* assigns freeThisOne to hold the pointer to the node that will be freed so we can pass it as an arguement later */
					freeThisOne = gCopy->hashNext;
					/*CASE - Node at end of list*/
					if(gCopy->hashNext->hashNext==NULL) 
					{
						/* Simply makes the current node skip the last member of the list if the node to be removed is at the end */
						gCopy->hashNext = NULL;
						/* winCount updated */
						if (freeThisOne->value->team1Score > freeThisOne->value->team2Score)
						{
							removeWin(freeThisOne->value->team1);
						} 
						else if(freeThisOne->value->team1Score < freeThisOne->value->team2Score) 
						{
							removeWin(freeThisOne->value->team2);
						}
						removeFromChrono(freeThisOne);
					} 
					/*CASE Middle - Since the node isnt at either beginning or end, it has to be somewhere in the middle */
					else
					{
						/* Makes the node before the one we want to remove skip over the one we want to remove */
						gCopy->hashNext = gCopy->hashNext->hashNext;
						/* winCount updated */
						if (freeThisOne->value->team1Score > freeThisOne->value->team2Score)
						{
							removeWin(freeThisOne->value->team1);
						} 
						else if(freeThisOne->value->team1Score < freeThisOne->value->team2Score) 
						{
							removeWin(freeThisOne->value->team2);
						}
						removeFromChrono(freeThisOne);
					}
					/* Now that the node has been removed from the hashtable it is safe to remove from the chronological list and then free up the memory */
					found = 1;
				}
			}
		}
	}
	if(found == 0)
	{
		printf("%d %s\n", NL, "Jogo inexistente.");
	}
}

/* function that finds all the teams that are tied with most wins */
void findBigWinners()
{
	int i;
	int j;
	int empates = 0;
	int maxWin = 0;
	int teamsExist = 0; /* if this stays at 0 then no teams exist in the system */
	int winnerCounter = 0;
	struct tNode* storm;
	struct tNode* tHead;
	struct tNode** bigWinners;
	/* This loop goes through the whole team hashtable to find what the largest number 
	of wins is and how many ocurrences of it exist*/
	for (i = 0; i < HASHNUM; i++)
	{
		if(Teams[i]!=NULL) 
		{
			teamsExist = 1;
			for (tHead = Teams[i]; tHead!=NULL; tHead=tHead->next)
			{
				if (tHead->value->winCount > maxWin)
				{
					empates = 1;
					maxWin = tHead->value->winCount;
				} else if (tHead->value->winCount == maxWin)
				{
					empates += 1;
				}
			}
		}
	}
	/* If no teams exist then theres no point in running this part as nothing is supposed to be output */
	if(teamsExist == 1)
	{
		/* array to hold all the teams tied for first place */
		bigWinners = malloc(sizeof(struct tNode*)*empates);
		/* This loop goes through the hashtable to fill the previous array with the winning teams*/
		for (i = 0; i < HASHNUM; i++)
		{
			for (tHead = Teams[i]; tHead!=NULL; tHead=tHead->next)
			{
				if (tHead->value->winCount == maxWin)
				{
					bigWinners[winnerCounter] = tHead;
					winnerCounter += 1;
				}
			}
		}
		/* This loop sorts the array in alphabetical order of team names */
		for (i = 0; i < winnerCounter-1; ++i)
		{
			for (j = 0; j < winnerCounter-i-1; ++j)
			{
				if (strcmp(bigWinners[j]->value->name, bigWinners[j+1]->value->name)>0)
				{
					storm = bigWinners[j];
					bigWinners[j] = bigWinners[j+1];
					bigWinners[j+1] = storm;
				}
			}
		}
		/* now we can print out the results */
		printf("%d Melhores %d\n", NL, maxWin);
		for (i = 0; i < empates; ++i)
		{
			printf("%d * %s\n", NL, bigWinners[i]->value->name);
		}
		free(bigWinners);
	} 
}

/* the magic happens here */
int main()
{
	char mander = ' ';
	char arg[LEN*3+24];
	/*	the size of arg accounts for:
			1 game name
			2 team names
			4 colons
			2 ints 							*/
	initialiseHashTables();
	ChronoHead = NULL;
	ChronoTail = NULL;
	NL=0;
	/* A while loop containing a switch keeps the program running untill the command to stop it, 'x', is called */
	while(mander!='x')
	{
		/* gets selected command */
		mander = getchar();
		/* if the char read is a \n then we dont want to increase the value of NL */
		if (mander=='\n')
		{
			continue;
		}
		NL++;
		/*printf("thing %x %c\n", mander, mander);*/
		switch(mander)
		{
			case 'a':
				/* skips space between command distinguisher and command parameters */
				getchar();
				/* reads rest of command */
				scanf("%[^\n]s", arg);
				/* calls function and sends the parameter */
				addGame(arg);
				break;
			case 'l':
				/* the command for this function is a single letter so no need to use getChar or scanf */
				listChrono();
				break;
			case 'A':
				getchar();
				scanf("%[^\n]s", arg);
				addTeam(arg);
				break;
			case 'p':
				getchar();
				scanf("%[^\n]s", arg);
				searchGame(arg);
				break;
			case 'P':
				getchar();
				scanf("%[^\n]s", arg);
				searchTeam(arg);
				break;
			case 's':
				getchar();
				scanf("%[^\n]s", arg);
				changeScore(arg);
				break;
			case 'r':
				getchar();
				scanf("%[^\n]s", arg);
				removeGame(arg);
				break;
			case 'g':
				findBigWinners();
				break;

		}
	}
	/* when were done we free everything that is still allocated */
	freeAll();
	return 0;
}