#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "header.h"

/*Iniciar a hashtable dos Jogos*/
void iniciar_HashGames()
{	
	int i;
	for(i = 0; i<TABLE_SIZE; i++)
		HashGames[i] = NULL;
}
/*Iniciar a hashtable das Equipas*/
void iniciar_HashTeams()
{	
	int i;
	for(i = 0; i<TABLE_SIZE; i++)
		HashTeams[i] = NULL;
}

/*Hash function*/
unsigned int hash(char *nome)
{
	int length = strlen(nome);
	unsigned int value = 0;
	int i;
	for(i = 0; i<length; i++)
	{
		value += nome[i];
	}
	value = value % TABLE_SIZE;
	return value;
}

/*Funcao que verifica se ja existe esse jogo*/
bool equipa_nao_existe(char *equipa)
{
	Equipa *temp;
	unsigned int indice = 0;
	indice = hash(equipa);
	
	if(HashTeams[indice] == NULL)
		return true;
	temp = HashTeams[indice];
	while(temp != NULL && strcmp(temp->nome_equipa, equipa))
	{
		temp = temp->next;
	}
	if(temp == NULL)
		return true;
	return false;
}

/*Funcoes MergeSort, SortedMerge e FrontBackSplit que ordenam uma linked list
de equipas por ordem alfabetica do nome da equipa*/

void MergeSort(EquipasOrd** headteam) 
{ 
    EquipasOrd* head = *headteam; 
    EquipasOrd* a; 
    EquipasOrd* b; 
  
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
  
   
    FrontBackSplit(head, &a, &b); 
  
   
    MergeSort(&a); 
    MergeSort(&b); 
  
    
    *headteam = SortedMerge(a, b); 
} 
  

EquipasOrd* SortedMerge(EquipasOrd* a, EquipasOrd* b) 
{ 
    EquipasOrd* result = NULL; 
  
   
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 
  
    
    if (strcmp(a->team->nome_equipa, b->team->nome_equipa) <= 0) { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return (result); 
} 
  

void FrontBackSplit(EquipasOrd* source, EquipasOrd** frontRef, EquipasOrd** backRef) 
{ 
    EquipasOrd* fast; 
    EquipasOrd* slow; 
    slow = source; 
    fast = source->next; 
  
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 


/*Funcao que desaloca a memoria toda alocada ao longo do funcionamento do programa*/
void FreeMemory()
{
	int i,e;

	Jogo *aux;
	Equipa *aux1;
	JogosOrd *aux2;
	EquipasOrd *aux3;

	for(i = 0; i < TABLE_SIZE; i++)
	{
		if(HashGames[i] != NULL)
		{
			if(HashGames[i]->next != NULL)
			{
				while(HashGames[i] != NULL)
				{
					free(HashGames[i]->nome);
					free(HashGames[i]->equipa_1);
					free(HashGames[i]->equipa_2);
					aux = HashGames[i]->next;
					free(HashGames[i]);
					HashGames[i] = aux;
				}
			}
			else
			{
				free(HashGames[i]->nome);
				free(HashGames[i]->equipa_1);
				free(HashGames[i]->equipa_2);
				free(HashGames[i]);
			}
		}
	}

	for(e = 0; e < TABLE_SIZE; e++)
	{
		if(HashTeams[e] != NULL)
		{
			if(HashTeams[e]->next != NULL)
			{
				while(HashTeams[e] != NULL)
				{	
					free(HashTeams[e]->nome_equipa);
					aux1 = HashTeams[e]->next;
					free(HashTeams[e]);
					HashTeams[e] = aux1;
				}
			}
			else
			{	
				free(HashTeams[e]->nome_equipa);
				free(HashTeams[e]);
			}
		}
	}

	while(headgame != NULL)
	{	
		aux2 = headgame->next;
		free(headgame);
		headgame = aux2;
	}

	while(headteam != NULL)
	{	
		aux3 = headteam->next;
		free(headteam);
		headteam = aux3;
	}	
}	
