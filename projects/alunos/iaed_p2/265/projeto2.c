#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int main()
{
	char p;
	int NL = 0;
	lugar_no_hash_j **hash_do_jogo;
	lugar_no_hash_e **hash_das_equipes;
	link **a_lista;
	hash_do_jogo = iniciar_hash_jogo(Max_tam);
	hash_das_equipes = iniciar_hash_equipe(Max_tam);
	a_lista = iniciar_listinha(Max_tam);
	while(1)
	{													
		switch(p = getchar())
		{
		case 'a':
		NL++;
		getchar();
		adiciona_jogo(hash_do_jogo, a_lista, hash_das_equipes, NL);
		break;
		case 'A':
		NL++;
		getchar();
		adiciona_equipe(hash_das_equipes, NL);
		break;
		case 'l':
		NL++;
		lista_de_jogos(a_lista);
		break;
		case 'p':
		NL++;
		getchar();
		encontrar_jogo(hash_do_jogo, NL);
		break;
		case 'P':
		NL++;
		getchar();
		encontrar_equipe(hash_das_equipes,NL);
		break;
		case 'r':
		NL++;
		break;
		case 's':
		NL++;
		break;
		case 'g':
		NL++;
		break;
		case 'x':
		return 0;	
		}
	}
}


/*##########################################################################################*/
/*################################################################################coisas pra fazer: por NL, mudar de "return(etc) para printf"##########*/
/*######################################  BLOCO JOGO  ######################################*/

JOGO *cria_jogo(char *nomej, EQUIPE *equipa_1, EQUIPE *equipa_2, int a, int b)
{
	JOGO *y;
	y = can_fail_malloc(sizeof(JOGO));
	y -> nome_j = can_fail_malloc(sizeof(char*));
	y -> score1 = a;
	y -> score2 = b;
	strcpy(y -> nome_j, nomej);
	y -> equipa1 -> nome_e = equipa_1 -> nome_e;
	y -> equipa2 -> nome_e = equipa_2 -> nome_e;
	y -> equipa1 -> ganhos = equipa_1 -> ganhos;
	y -> equipa2 -> ganhos = equipa_2 -> ganhos;
	return y;

}
lugar_no_hash_j *adicionar_a_listinha_j(lugar_no_hash_j *point_j, JOGO *jg)
{
	lugar_no_hash_j *lista_j = can_fail_malloc(Max_tam*sizeof(lugar_no_hash_j));
	lista_j -> jogo = jg;
	lista_j -> seguinte_j = point_j;
	return lista_j;
}
lugar_no_hash_j **iniciar_hash_jogo(int m)
{
	int i;
	int M;
	lugar_no_hash_j **hashtable_j;		
	M = m;

	hashtable_j = can_fail_malloc(Max_tam*sizeof(lugar_no_hash_j));
	for (i = 0; i < M; i++)
		hashtable_j[i] = NULL;
	return hashtable_j;
}

link *listinha_da_ordem(link *apoint, JOGO *jogou)
{
	link *listinha = can_fail_malloc(sizeof(link));
	listinha -> jogo = jogou;
	listinha -> next = apoint;
	return listinha;
}
link **iniciar_listinha(int m)
{
	int i;
	int M;
	link **lista;
	M = m;
	lista = can_fail_malloc(Max_char*sizeof(link));
	for (i = 0; i < M; i++)
		lista[i] = NULL;
	return lista;
}
void adiciona_jogo(lugar_no_hash_j **hashtable_j, link **fila, lugar_no_hash_e **hashtable_e, int NL)
{
	JOGO *jog;
	long hash_j;
	char daequipe1[Max_char];
	char daequipe2[Max_char];
	char dojogo[Max_char];
	int plac1;
	int plac2;
	EQUIPE *equipe1; 
	EQUIPE *equipe2;
	
	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", dojogo, daequipe1, daequipe2, &plac1, &plac2);
	if(encontrar_jogo_aux(dojogo, hashtable_j) != NULL)
	{
		printf( "%d Jogo existente.\n",NL);
		return;
	}
	if ((equipe1 = encontrar_equipe_aux(daequipe1, hashtable_e)) == NULL)
	{
		printf( "%d Equipa inexistente.\n",NL);
		return;
	}			
	if ((equipe2 = encontrar_equipe_aux(daequipe2, hashtable_e)) == NULL){
		printf( "%d Equipa inexistente.\n",NL);
		return;
	}

	jog = cria_jogo(dojogo,equipe1,equipe2,plac1,plac2);
	hash_j = hashU(dojogo, Max_char);															/*verificar com alguem*/
	hashtable_j[hash_j] = adicionar_a_listinha_j(hashtable_j[hash_j], jog);
	*fila = listinha_da_ordem(*fila, jog); 
}
void lista_de_jogos(link **fila)
{
	int i;
	i = 0;
	if (fila[0] == NULL)
		return;
	while(fila[i] != NULL)
	{
		printf(fila[i] -> jogo -> nome_j, fila[i] -> jogo -> equipa1 -> nome_e, fila[i] -> jogo -> equipa2 -> nome_e);
		i++;
	}
}
void encontrar_jogo(lugar_no_hash_j **hashtable_j,int NL)
{
	JOGO *point;
	long indcj;
	char names[Max_char];
	scanf("%[^:\n]",names);
	indcj = hashU(names,Max_char);
	point = encontrar_jogo_aux(names,hashtable_j);
	if(point == NULL)
	{
		printf("%d Jogo inexistente.\n", NL);
		return;
	}
	printf("%s %s %s %d %d\n",hashtable_j[indcj] -> jogo -> nome_j, hashtable_j[indcj] -> jogo -> equipa1 -> nome_e, hashtable_j[indcj] -> jogo -> equipa2 -> nome_e, hashtable_j[indcj] -> jogo -> score1, hashtable_j[indcj] -> jogo -> score2);
} 
JOGO *encontrar_jogo_aux(char *names, lugar_no_hash_j **hashtable_j)
{
	long indcj;
	indcj = hashU(names,Max_tam);
	while (hashtable_j[indcj] != NULL && strcmp(names,hashtable_j[indcj]-> jogo -> nome_j) != 0)		
			hashtable_j[indcj] = hashtable_j[indcj] -> seguinte_j;
	if(hashtable_j[indcj] == NULL)
		return NULL;

	else
		return hashtable_j[indcj] -> jogo;
} 
/*##########################################################################################*/
/*##########################################################################################*/
/*################################  Bloco Equipe  ##########################################*/


lugar_no_hash_e **iniciar_hash_equipe(int m) 
{
	int i;
	int M; 
	lugar_no_hash_e **hashtable_e; 
	M = m;
	hashtable_e = can_fail_malloc(Max_tam*sizeof(lugar_no_hash_e));
	for (i = 0; i < M; i++) 
		hashtable_e[i] = NULL;
	return hashtable_e;
}

EQUIPE *cria_equipe(char *nomee)
{
	EQUIPE *x;
	x = can_fail_malloc(sizeof(EQUIPE));
	x->nome_e = can_fail_malloc(sizeof(char*));
	x->ganhos = 0;
	strcpy(x->nome_e, nomee);
	return x; 
}
lugar_no_hash_e *adicionar_a_listinha_e(lugar_no_hash_e *point_e, EQUIPE *eq)
{
	lugar_no_hash_e *lista_e = can_fail_malloc(Max_tam*sizeof(lugar_no_hash_e));
	lista_e -> equipe = eq;
	lista_e -> seguinte_e = point_e;
	return lista_e;
}
void adiciona_equipe(lugar_no_hash_e **hashtable_e,int NL)
{
	EQUIPE *equip;
	long hash;
	char daequipe[Max_char];
	scanf("%[^:\n]", daequipe);
	hash = hashU(daequipe, Max_char);                                                 
	if(encontrar_equipe_aux(daequipe, hashtable_e) != NULL) 
			printf( "%d Equipa existente.\n",NL);
	equip = cria_equipe(daequipe);											
	hashtable_e[hash] = adicionar_a_listinha_e(hashtable_e[hash], equip);
}
																								
void encontrar_equipe(lugar_no_hash_e **hashtable_e, int NL)
{
	EQUIPE *point;
	long indce;
	char names[Max_char];
	scanf("%[^:\n]",names);
	indce = hashU(names,Max_char);
	point = encontrar_equipe_aux(names,hashtable_e);
	if(point == NULL)
	{
		printf("%d Equipa inexistente.\n", NL);
		return;
	}

	printf("%s %d\n", names, hashtable_e[indce] ->equipe -> ganhos);
}
EQUIPE *encontrar_equipe_aux(char *names, lugar_no_hash_e **hashtable_e)
{
	long indce;
	lugar_no_hash_e *aux;
	indce = hashU(names,Max_char);
	aux = hashtable_e[indce];
	if(aux == NULL)
		return NULL;
	while (aux != NULL && strcmp(names,aux-> equipe -> nome_e) != 0)		
			aux = aux -> seguinte_e;
	

	return aux -> equipe;
} 
