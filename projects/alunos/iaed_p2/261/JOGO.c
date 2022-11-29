#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JOGO.h"

/* Funcao mk_list
   Input: Nada
   Output: Lista
   Descricao: Aloca memoria para a hashtable e
   para a lista duplamente ligada, e inicializa
   os respetivos indices a NULL.
*/
list* mk_list() 
{
	int i;
	list *lista = can_fail_malloc(sizeof(list));
	lista->head = NULL;
	lista->last = NULL;
	lista->hashtable = can_fail_malloc(sizeof(jogo) * HASHSIZE);
	for (i = 0; i < HASHSIZE; i++) 
	{
		*(lista->hashtable+i) = NULL;
	}

	return lista;
}

void freeLista(list* l)
{
	jogo* next_jogo;

	while(l->head != NULL)
	{
		next_jogo = l->head->next;

		free(l->head->nome);
		free(l->head->equipa1);
		free(l->head->equipa2);
		l->head->resultado1 = 0;
		l->head->resultado2 = 0;
		free(l->head);

		l->head = next_jogo;
	}

	free(l->hashtable);
	free(l);

	return;
}

/* Funcao encontrarJogo
   Input: Lista, string com o nome do jogo
   Output: Jogo (Se existir)
*/
jogo* encontrarJogo(list* l, char buffer[MAX])
{
	jogo* Procurar;
	int jogoHash = hash(buffer) % HASHSIZE;
	for (Procurar = *(l->hashtable + jogoHash); Procurar && strcmp(Procurar->nome, buffer) != 0; Procurar = Procurar->collision);

	return Procurar;
}

void merge(int tab_final[], int start, int mid, int end, char* tab_equipa[EQUIPAHASHMAX])
{
    int i, j, k, tab_aux[EQUIPAHASHMAX];
    for (i = mid + 1; i > start; i--)
        tab_aux[i-1] = tab_final[i-1];
    for (j = mid; j < end; j++)
        tab_aux[end + mid - j] = tab_final[j+1];
    for (k = start; k <= end; k++){
        if (strcmp(tab_equipa[tab_aux[j]], tab_equipa[tab_aux[i]]) < 0 || i > mid)
            tab_final[k] = tab_aux[j--];
        else
            tab_final[k] = tab_aux[i++];
    }
}

void mergeSort(int tab_final[EQUIPAHASHMAX], int start, int end, char* tab_equipa[EQUIPAHASHMAX])
{
    int mid = (start + end) / 2;
    if (end <= start)
        return;

    mergeSort(tab_final, start, mid, tab_equipa);
    mergeSort(tab_final, mid + 1, end, tab_equipa);
    merge(tab_final, start, mid, end, tab_equipa);
}

/* Funcao adicionaJogo (a)
   Input: a nome:equipa1:equipa2:score1:score2
   Output: Nada (excepto erro)
   Descricao: Esta funcao adiciona um novo jogo.
*/
list* adicionaJogo(list* l, equipaHash** equipaTable, char* buffer, int n)
{
	int jogoHash;

	jogo* novo_jogo;

	char* nome = strtok(buffer, ":");
	char* eq1 = strtok(NULL, ":");
	char* eq2 = strtok(NULL, ":");
	char* res1 = strtok(NULL, ":");
	char* res2 = strtok(NULL, ":");

	if (encontrarJogo(l, buffer)) 
	{
		printf("%d Jogo existente.\n", n);

		return l;
	}

	if (encontraEquipa(equipaTable, eq1))
	{
		if (encontraEquipa(equipaTable, eq2))
		{
			novo_jogo = can_fail_malloc(sizeof(jogo));
			novo_jogo->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
			strcpy(novo_jogo->nome, nome);

			novo_jogo->equipa1 = can_fail_malloc(sizeof(char) * (strlen(eq1) + 1));
			strcpy(novo_jogo->equipa1, eq1);

			novo_jogo->equipa2 = can_fail_malloc(sizeof(char) * (strlen(eq2) + 1));
			strcpy(novo_jogo->equipa2, eq2);

			novo_jogo->resultado1 = atoi(res1);

			novo_jogo->resultado2 = atoi(res2);

			if (novo_jogo->resultado1 > novo_jogo->resultado2)
			{
				adicionaVitoria(equipaTable, eq1);
			}
			if (novo_jogo->resultado1 < novo_jogo->resultado2)
			{
				adicionaVitoria(equipaTable, eq2);
			}

			novo_jogo->next = NULL;
			novo_jogo->previous = l->last;
			novo_jogo->collision = NULL;

			jogoHash = hash(novo_jogo->nome) % HASHSIZE;

			if (*(l->hashtable + jogoHash) == NULL) 
			{
				*(l->hashtable + jogoHash) = novo_jogo;
			} else 
			{
				novo_jogo->collision = *(l->hashtable + jogoHash);
				*(l->hashtable + jogoHash) = novo_jogo;
			}

			if (l -> head == NULL) 
			{
				l->head = novo_jogo;
			} else 
			{
				l->last->next = novo_jogo;
			}

			l->last = novo_jogo;

			return l;
		}
	}

	printf("%d Equipa inexistente.\n", n);

	return l;
}

/* Funcao listaJogos (l)
   Input: l
   Output: NL nome-jogo nome-equipa1 nome-equipa2 score1 score2
   Descricao: Esta funcao lista todos os jogos
   pela ordem em que estes foram introduzidos
   no sistema.
*/
void listaJogos(list* l, int n)
{
	jogo* x = l->head;
	if (x == NULL)
		return;
	while (x != NULL)
	{
		printf("%d %s %s %s %d %d\n", n, x->nome, x->equipa1, x->equipa2, x->resultado1, x->resultado2);
		x = x->next;
	}
	return;
}

/* Funcao procuraJogo(p)
   Input: p nome
   Output: NL nome-jogo nome-equipa1 nome-equipa2 score1 score2
   Descricao: Esta funcao procura o jogo pelo nome
   e devolve todas as caracteristicas desse mesmo jogo
*/
void procuraJogo(list* l, char buffer[MAX], int n)
{
	jogo* x;
	buffer = strtok(buffer, "\n");
	if ((x = encontrarJogo(l, buffer)))
	{
		printf("%d %s %s %s %d %d\n", n, x->nome, x->equipa1, x->equipa2, x->resultado1, x->resultado2);
		return;
	}
	printf("%d Jogo inexistente.\n", n);
	return;
}

/* Funcao apagarJogo(r)
   Input: r nome
   Output: Nada (exceto erro)
   Descricao: Esta funcao procura o jogo pelo nome e
   apaga o mesmo do sistema.
*/
list* apagarJogo(list* l, equipaHash** equipaTable, char buffer[MAX], int n)
{
	int jogoHash;
	jogo* paraApagar, *jogoCollision;
	paraApagar = l->head;
	buffer = strtok(buffer, "\n");

	if ((paraApagar = encontrarJogo(l, buffer))) 
	{
		if (paraApagar->resultado1 > paraApagar->resultado2)
		{
			removeVitoria(equipaTable, paraApagar->equipa1);
		}
		if (paraApagar->resultado1 < paraApagar->resultado2)
		{
			removeVitoria(equipaTable, paraApagar->equipa2);
		}

		if (paraApagar->next != NULL)
		{
			paraApagar->next->previous = paraApagar->previous;
		}

		if (paraApagar->previous != NULL) 
		{
    		paraApagar->previous->next = paraApagar->next;
		} 

		if (paraApagar == l->head)
		{
			l->head = paraApagar->next;
		}

		if (paraApagar == l->last)
		{
			l->last = paraApagar->previous;
		}

		jogoHash = hash(buffer) % HASHSIZE;
		jogoCollision = *(l->hashtable + jogoHash);

		if (strcmp(jogoCollision->nome, buffer) == 0) 
		{
			*(l->hashtable + jogoHash) = jogoCollision->collision;
		} else 
		{
			for(; strcmp(jogoCollision->collision->nome, buffer) != 0; jogoCollision = jogoCollision->collision);
			
			jogoCollision->collision = jogoCollision->collision->collision;
		}

		free(paraApagar->nome);
		free(paraApagar->equipa1);
		free(paraApagar->equipa2);
		paraApagar->resultado1 = 0;
		paraApagar->resultado2 = 0;
		free(paraApagar);


		
		return l;
	}
	
	printf("%d Jogo inexistente.\n", n);

	return l;
}

/* Funcao alteraResultado (s)
   Input: s nome:score1:score2
   Output: Nada (exceto erro)
   Descricao: Esta funcao procura o jogo pelo nome
   e muda o resultado do jogo pelos novos
*/
list* alteraResultado(list* l, equipaHash** equipaTable, char buffer[MAX], int n)
{
	jogo* paraMudar;
	buffer = strtok(buffer, ":");

	if ((paraMudar = encontrarJogo(l, buffer)))
	{
		if (paraMudar->resultado1 > paraMudar->resultado2)
		{
			removeVitoria(equipaTable, paraMudar->equipa1);
		}
		if (paraMudar->resultado1 < paraMudar->resultado2)
		{
			removeVitoria(equipaTable, paraMudar->equipa2);
		}

		buffer = strtok(NULL, ":");
		paraMudar->resultado1 = atoi(buffer);

		buffer = strtok(NULL, ":");
		paraMudar->resultado2 = atoi(buffer);

		if (paraMudar->resultado1 > paraMudar->resultado2)
		{
			adicionaVitoria(equipaTable, paraMudar->equipa1);
		}
		if (paraMudar->resultado1 < paraMudar->resultado2)
		{
			adicionaVitoria(equipaTable, paraMudar->equipa2);
		}

		return l;
	}
	printf("%d Jogo inexistente.\n", n);
	return l;
}

/* Funcao adicionaEquipa (A)
   Input: A nome
   Output: Nada (exceto erro)
   Descricao: Esta funcao adiciona uma nova equipa.
*/
void adicionaEquipa(equipaHash** equipaTable, char buffer[MAX], int n)
{
	buffer = strtok(buffer, "\n");

	if (encontraEquipa(equipaTable, buffer))
	{
		printf("%d Equipa existente.\n", n);
		return;
	}

	AddEquipa(equipaTable, buffer);
	return;
}

/* Funcao procuraEquipa (P)
   Input: P nome
   Output: NL nome numero-de-jogos-ganhos
   Descricao: Esta funcao procura uma equipa pelo nome
   e devolve o numero de jogos ganhos dessa equipa.
*/
void procuraEquipa(equipaHash** equipaTable, char buffer[MAX], int n)
{
	buffer = strtok(buffer, "\n");  /*remove o \n que vem do fgets */

	if (encontraEquipa(equipaTable, buffer))
	{
		printf("%d %s %d\n", n, buffer, jogosGanhos(equipaTable, buffer));
		return;
	}
	printf("%d Equipa inexistente.\n", n);
	return;
}

/* Funcao melhoresEquipas (g)
   Input: g
   Output: NL Melhores numero-de-jogos-ganhos
   Descricao: Esta funcao procura quais as equipas com
   mais jogos ganhos e devolve-as por ordem alfabetica.
*/
void melhoresEquipas(equipaHash** equipaTable, int n)
{
    int i, counter = 0, e = 0;
    int tab_final[EQUIPAHASHMAX];
    char* tab_equipas[EQUIPAHASHMAX];
    e = equipasMaisJogos(equipaTable, tab_equipas);

    if (e > 0)
    {
        for (i = 0; i < e; i++)
        {
            tab_final[counter] = i;
            counter++;
        }
        printf("%d Melhores %d\n", n, jogosGanhos(equipaTable, tab_equipas[0]));
        mergeSort(tab_final, 0, counter - 1, tab_equipas);
        for (i = 0; i < counter; i++)
        {
            printf("%d * %s\n", n, tab_equipas[tab_final[i]]);
        }
        i = 0;
    	while (i < e)
    	{
    		free(tab_equipas[i]);
    		i++;
    	}
    }  
    return;
}
