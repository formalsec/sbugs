#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "estrutura.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	int run = 1, score1, score2, NL = 0, num_jogos = 0;
	char nome[MAX], nome_equipa[MAX], equipa1[MAX], equipa2[MAX], command;
	jogos *hashtable_jogos = criar_hashtablejogos();
	equipas *hashtable_equipas = criar_hashtableequipas();
	while (run)
	{
		command = getchar();
		switch (command)
		{
			case 'a':
				getchar();
				NL++;
				scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
				if (adicionajogo(hashtable_jogos, hashtable_equipas, nome, equipa1, 
					equipa2, score1, score2, num_jogos, NL))
					num_jogos++;
				break;
			case 'l':
				NL++;
				listaordemjogos(hashtable_jogos, num_jogos, NL);
				break;
			case 'p':
				getchar();
				NL++;
				scanf("%[^:\n]", nome);
				procurajogo(hashtable_jogos, nome, NL);
				break;
			case 'r':
				getchar();
				NL++;
				scanf("%[^:\n]", nome);
				apagajogo(hashtable_jogos, hashtable_equipas, nome, NL);
				break;
			case 's':
				getchar();
				NL++;
				scanf("%[^:\n]:%d:%d", nome, &score1, &score2);
				alterascore(hashtable_jogos, hashtable_equipas, nome, score1, score2, NL);
				break;
			case 'A':
				getchar();
				NL++;
				scanf("%[^:\n]", nome_equipa);
				adicionaequipa(hashtable_equipas, nome_equipa, NL);
				break;
			case 'P':
				getchar();
				NL++;
				scanf("%[^:\n]", nome_equipa);
				procuraequipa(hashtable_equipas, nome_equipa, NL);
				break;
			case 'x':
				freehashtable_jogos(hashtable_jogos);
				freehashtable_equipas(hashtable_equipas);
				run = 0;
				break;
		}
	}
	return 0;
}