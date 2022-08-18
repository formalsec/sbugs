#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h" /* Ficheiro que contem as funcoes que geram os jogos e as equipas */

/* Funcao auxiliar que permite calcular o indice de um determinado elemento de uma hashtable */
int Hash(char* received) {
	int h, a = 127;

	for (h = 0; strcmp(received, "\0"); received++) {
		h = (a*h + *received) % HASHSIZE;
	}
	return h;
}

/* Funcao auxiliar que permite imprimir todos os elementos de uma hashtable */
void Printar(listajogos *list) {
	int i;

    for (i = 0; i < HASHSIZE; ++i) {
        jogo *entry = list->hashjogos[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%4d]: ", i);

        for(;;) {
            printf("%s %s %s", entry->nomej, entry->equipa1->nomeeq, entry->equipa2->nomeeq);

            if (entry->proximoj == NULL) {
                break;
            }

            entry = entry->proximoj;
        }

        printf("\n");
    }
}

/* Funcao auxiliar que permite alocar numa nova lista e retornar essa mesma lista criada */
listajogos* NovaListaJogos() {
	int i = 0;
	
	listajogos *novalista = malloc(sizeof(struct listajogos)); /* Permite alocar espaco para a lista que sera criada */
	novalista->fimj = NULL; /* Inicia o root(fim) da lista */
	novalista->inicioj = NULL; /* Inicia a head(inicio) da lista */

	while(i < HASHSIZE) {
		novalista->hashjogos[i] = malloc(sizeof(struct jogo) * HASHSIZE);
		novalista->hashjogos[i] = NULL; /* Inicia todos os indices da hastable */
		i++;
	}
	
	return novalista; /* Criacao da nova lista */
}


/* Funcao auxiliar que permite alocar numa nova lista e retornar essa mesma lista criada */
listaequipas* NovaListaEquipas() {
	int i = 0;

	listaequipas *novalista = malloc(sizeof(struct listaequipas)); /* Permite alocar espaco para a lista que sera criada */
	novalista->fimeq = NULL; /* Inicia o root(fim) da lista */
	novalista->inicioeq = NULL; /* Inicia a head(inicio) da lista */

	while(i < HASHSIZE) {
		novalista->hashequipas[i] = malloc(sizeof(struct equipa) * HASHSIZE); 
		novalista->hashequipas[i] = NULL; /* Inicia todos os indices da hastable */
		i++;
	}

	return novalista; /* Criacao da nova lista */
}


/* Funcao auxiliar que permite, dado um nome de um jogo, procurar se o mesmo existe na hashtable */
jogo* ProcuraJogoAuxiliar(listajogos *list, char* nomejogo) {
	
	int key = Hash(nomejogo), i = 1; /* Gera o indice da hashtable de acordo com o nome do jogo */
	jogo *procurar = list->hashjogos[key]; 


	while (procurar != NULL) {
		if (strcmp(procurar->nomej, nomejogo) == 0) {
			return procurar; /* Retorna o jogo na hashtable caso exista */
			break;
		}
		else {
			int tentativa = (i + key) % HASHSIZE;

			procurar = list->hashjogos[tentativa]; /* Procura o jogo na proxima posicao da hash, caso haja colisao */
			i++;
		}
	}

	return procurar; /* Retorna o jogo (caso nao exista na hash retorna NULL) */
}


/* Funcao auxiliar que permite, dado um nome de uma equipa, procurar se a mesma existe na hashtable */
equipa* ProcuraEquipaAuxiliar(listaequipas *list1, char* equipanome) {

	int key = Hash(equipanome), i = 1; /* Gera o indice da hashtable de acordo com o nome da equipa */
	equipa *procurar = list1->hashequipas[key]; 

	while (procurar != NULL) {
		if (strcmp(procurar->nomeeq, equipanome) == 0) {
			return procurar; /* Retorna a equipa na hashtable */
			break;
		}
		else {
			int tentativa = (i + key) % HASHSIZE;

			procurar = list1->hashequipas[tentativa]; /* Procura a equipa numa outra posicao da hash, caso haja colisao */
			i++;
		}
	}

	return procurar; /* Retorna a equipa (caso nao exista na hash retorna NULL) */
}


/* Funcao auxiliar que recebe uma string e permite alocar memoria para guardar e atualizar
informacao na nova equipa */
equipa* NovaEquipa(char* equipanome, listaequipas *list1) {

	equipa *novaequipa = malloc(sizeof(struct equipa));

	novaequipa->proximoeq = NULL;
	novaequipa->anterioreq = list1->fimeq;
	novaequipa->nomeeq = malloc(sizeof(char) * EQUIPAS);

	novaequipa->nomeeq = strcpy(novaequipa->nomeeq, equipanome);
	novaequipa->vitorias = 0;

	return novaequipa;
}


/* Funcao auxiliar que recebe uma string e permite alocar memoria para guardar e atualizar
informacao no novo jogo */
jogo* NovoJogo(char* nomejogo, char* equipa1nome, char* equipa2nome, int score1recebido, int score2recebido, listajogos *list) {

	
	jogo *novojogo = malloc(sizeof(struct jogo));

	novojogo->proximoj = NULL;
	novojogo->anteriorj = list->fimj;
	novojogo->nomej = malloc(sizeof(char) * NOME);
	novojogo->equipa1 = malloc(sizeof(char) * EQUIPAS);
	novojogo->equipa2 = malloc(sizeof(char) * EQUIPAS);

	novojogo->nomej = strcpy(novojogo->nomej,nomejogo);
	novojogo->equipa1->nomeeq = (char *) memcpy(malloc(sizeof(char)*(strlen(equipa1nome)+1)),equipa1nome, sizeof(char)*(strlen(equipa1nome)+1));
	novojogo->equipa2->nomeeq = (char *) memcpy(malloc(sizeof(char)*(strlen(equipa2nome)+1)),equipa2nome, sizeof(char)*(strlen(equipa2nome)+1));
	novojogo->score1 = score1recebido;
	novojogo->score2 = score2recebido;

	return novojogo;
}


/* Comando 'a':
	Esta funcao recebe um conjunto de caracteres com as informacoes 
	referentes ao novo jogo e permite adiciona-lo ao sistema. */
listajogos* AdicionaJogo(listajogos *list, listaequipas *list1, char* nomejogo, char* equipa1nome, char* equipa2nome, int score1recebido, int score2recebido, int comando) {
	
	jogo *procurajogo, *novojogo;
	equipa *procuraequipa1, *procuraequipa2;
	
	int key = Hash(nomejogo); /* Gera o indice da hashtable de acordo com o nome do jogo */
	int i, vitoria1, vitoria2;
		
	procurajogo = ProcuraJogoAuxiliar(list, nomejogo); /* Verifica se o jogo existe */
	procuraequipa1 = ProcuraEquipaAuxiliar(list1, equipa1nome); /* Verifica se a equipa1 existe */
	procuraequipa2 = ProcuraEquipaAuxiliar(list1, equipa2nome); /* Verifica se a equipa2 existe */

	if (procurajogo != NULL) {
		printf("%d Jogo existente.\n", comando);
		return list;
	}
	if (procuraequipa1 == NULL) {
		printf("%d Equipa inexistente.\n", comando);	
		return list;
	}
	if (procuraequipa2 == NULL) {
		printf("%d Equipa inexistente.\n", comando);
		return list;
	}
	else {
		novojogo = NovoJogo(nomejogo, equipa1nome, equipa2nome, score1recebido, score2recebido, list);
		/* Criacao do novo jogo com a respetiva informacao referente ao mesmo */

		if (score1recebido > score2recebido) {
			vitoria1 = Hash(equipa1nome); /* Gera o indice da hashtable de acordo com o nome da equipa1 */
			list1->hashequipas[vitoria1]->vitorias++; /* Atualiza o numero de vitorias da equipa 1 */
		}
		if (score1recebido < score2recebido) {
			vitoria2 = Hash(equipa2nome); /* Gera o indice da hashtable de acordo com o nome da equipa2 */
			list1->hashequipas[vitoria2]->vitorias++; /* Atualiza o numero de vitorias da equipa 2 */
		}
		
		if (list->hashjogos[key] == NULL) { 
			list->hashjogos[key] = novojogo;
		}
		else { /* Caso haja alguma colisao, adiciona o jogo na posicao seguinte da hashtable */
			for (i = 0; i < HASHSIZE; i++) {
				int tentativa = (i + key) % HASHSIZE;
				
				novojogo->proximoj = list->hashjogos[tentativa];
				
				if (novojogo->proximoj == NULL) {
					list->hashjogos[tentativa] = novojogo;
					break;
				}
			}
		}

		if (list->inicioj == NULL) { /* Caso a lista esteja vazia */
			list->inicioj = novojogo;
		}
		else {
			list->fimj->proximoj = novojogo;
			novojogo->anteriorj = list->fimj;
		}
		list->fimj = novojogo;
	}
	return list;
}


/* Comando 'A':
	Esta funcao recebe um conjunto de caracteres com as informacoes 
	referentes ao novo jogo e permite adiciona-lo ao sistema. */
listaequipas* AdicionaEquipa(listaequipas *list1, char* equipanome, int comando) {

	equipa *procuraequipa = ProcuraEquipaAuxiliar(list1, equipanome); /* Verifica se a equipa existe */

	int key = Hash(equipanome), i; /* Gera o indice da hashtable de acordo com o nome da equipa */

	if (procuraequipa != NULL) {
		printf("%d Equipa existente.\n", comando);
		return list1;
	}
	else {
		equipa *novaequipa = NovaEquipa(equipanome, list1); /* Criacao da nova equipa */

		if (list1->hashequipas[key] == NULL) { 
			list1->hashequipas[key] = novaequipa;
		}
		else { /* Caso haja alguma colisao, adiciona a equipa na posicao seguinte da hashtable */
			for (i = 0; i < HASHSIZE; i++) {
				int tentativa = (i + key) % HASHSIZE;
				
				novaequipa->proximoeq = list1->hashequipas[tentativa];
				
				if (novaequipa->proximoeq == NULL) {
					list1->hashequipas[tentativa] = novaequipa;
					break;
				}
			}
		}
		
		if (list1->inicioeq == NULL) { /* Caso a lista esteja vazia */
			list1->inicioeq = novaequipa;
		}
		else {
			list1->fimeq->proximoeq = novaequipa;
			novaequipa->anterioreq = list1->fimeq;
		}
		list1->fimeq = novaequipa;
	}
	return list1;	
}


/* Comando 'l':
	Esta funcao permite listar todos os jogos adicionados ao sistema */
void ListaJogos(listajogos* list, int comando) {
	jogo *listar = list->inicioj;

	if (listar == NULL) {
		return;
	}
	while (listar != NULL) {

		printf("%d %s %s %s %d %d\n", comando, listar->nomej, listar->equipa1->nomeeq, listar->equipa2->nomeeq, listar->score1, listar->score2);

		listar = listar->proximoj;
	}
	return;
}


/* Comando 'p':
	Funcao que permite, dado um nome de um jogo, procurar se 
	o mesmo existe na hashtable */
jogo* ProcuraJogo(listajogos *list, char* nomejogo, int comando) {

	jogo *procurar = ProcuraJogoAuxiliar(list, nomejogo); /* Verifica se o jogo existe */

	if (procurar == NULL) {
		printf("%d Jogo inexistente.\n", comando);
		return procurar;
	}
	printf("%d %s %s %s %d %d\n", comando, procurar->nomej, procurar->equipa1->nomeeq, procurar->equipa2->nomeeq, procurar->score1, procurar->score2);	
	return procurar;
}


/* Comando 'P':
	Esta funcao permite, dado um nome de uma equipa, procurar se 
	a mesma existe na hashtable */
equipa* ProcuraEquipa(listaequipas *list1, char* equipanome, int comando) {

	equipa *procurar = ProcuraEquipaAuxiliar(list1, equipanome); /* Verifica se a equipa existe */

	if (procurar == NULL) {
		printf("%d Equipa inexistente.\n", comando);
		return procurar;
	}
	printf("%d %s %d\n",comando,procurar->nomeeq,procurar->vitorias);
	return procurar;
}


/* Comando 'r':
	Esta funcao permite, dado um nome de um jogo, apaga-lo da lista duplamente
	ligada e respetiva hashtable de jogos*/
listajogos* ApagaJogo(listajogos *list, listaequipas *list1, char* nomejogo, int comando) {

	int key = Hash(nomejogo), i, vitoria1, vitoria2; /* Gera o indice da hashtable de acordo com o nome da equipa */

	jogo *remover = ProcuraJogoAuxiliar(list, nomejogo); /* Verifica se o jogo existe */

	if (remover == NULL) {
		printf("%d Jogo inexistente.\n", comando);
		return list;
	}
	else {	
		if (remover->score1 > remover->score2) {
			vitoria1 = Hash(remover->equipa1->nomeeq);
			list1->hashequipas[vitoria1]->vitorias--;
		}
		if (remover->score1 < remover->score2) {
			vitoria2 = Hash(remover->equipa2->nomeeq);
			list1->hashequipas[vitoria2]->vitorias--;
		}
		
		if (remover->anteriorj != NULL) {
			remover->anteriorj->proximoj = remover->proximoj;
		}
		if (remover->proximoj != NULL) {
			remover->proximoj->anteriorj = remover->anteriorj;
		}

		if (remover == list->inicioj) {
			list->inicioj = remover->proximoj;
		}
		if (remover == list->fimj) {
			list->fimj = remover->anteriorj;
		}
		
		if (strcmp(nomejogo, list->hashjogos[key]->nomej) == 0) {
			list->hashjogos[key] = remover->proximoj;
		}
		else { /* Caso haja alguma colisao, adiciona o jogo na posicao seguinte da hashtable */
			for (i = 0; i < HASHSIZE; i++) {
				int tentativa = (i + key) % HASHSIZE;
				
				remover->proximoj = list->hashjogos[tentativa];
				
				if (strcmp(nomejogo, list->hashjogos[tentativa]->nomej) == 0) {
					list->hashjogos[tentativa] = remover->proximoj;
				}
			}
		}
		/* Liberta a memoria anteriormente alocada para os dados do jogo agora removido */
		free(remover->nomej);
		free(remover->equipa1);
		free(remover->equipa2);
		free(remover);
	}
	return list;
}


/* Comando 's':
	Esta funcao permite, dado um nome de um jogo e os novos scores, 
	alterar os scores das equipas nesse jogo */
listajogos* AlteraScore(listajogos *list, listaequipas *list1, char* nomejogo, int score1recebido, int score2recebido, int comando) {

	int key = Hash(nomejogo), i, vitoria1, vitoria2; /* Gera o indice da hashtable de acordo com o nome da equipa */

	jogo *alterar = ProcuraJogoAuxiliar(list, nomejogo); /* Verifica se o jogo existe */

	if (alterar == NULL) {
		printf("%d Jogo inexistente.\n", comando);
		return list;
	}

	if (strcmp(nomejogo, list->hashjogos[key]->nomej) == 0) {
		if (list->hashjogos[key]->score1 > list->hashjogos[key]->score2) {
			vitoria1 = Hash(list->hashjogos[key]->equipa1->nomeeq);
			list1->hashequipas[vitoria1]->vitorias--; /*Altera o numero de vitorias da equipa 1 */
		}
		if (list->hashjogos[key]->score1 < list->hashjogos[key]->score2) {
			vitoria2 = Hash(list->hashjogos[key]->equipa2->nomeeq);
			list1->hashequipas[vitoria2]->vitorias--; /*Altera o numero de vitorias da equipa 2 */
		}
		
		list->hashjogos[key]->score1 = score1recebido;
		list->hashjogos[key]->score2 = score2recebido;

		if (score1recebido > score2recebido) {
			vitoria1 = Hash(list->hashjogos[key]->equipa1->nomeeq);
			list1->hashequipas[vitoria1]->vitorias++; /*Altera o numero de vitorias da equipa 1 consoante o novo score */
		}
	
		if (score1recebido < score2recebido) {
			vitoria2 = Hash(list->hashjogos[key]->equipa2->nomeeq);
			list1->hashequipas[vitoria2]->vitorias++; /*Altera o numero de vitorias da equipa 2 consoante o novo score */
		}
	}
	
	else { /* Caso haja alguma colisao, adiciona o jogo na posicao seguinte da hashtable */
		for (i = 0; i < HASHSIZE; i++) {
			int tentativa = (i + key) % HASHSIZE;
				
			alterar->proximoj = list->hashjogos[tentativa];
				
			if (strcmp(nomejogo, list->hashjogos[tentativa]->nomej) == 0) {
				if (list->hashjogos[tentativa]->score1 > list->hashjogos[tentativa]->score2) {
					vitoria1 = Hash(list->hashjogos[tentativa]->equipa1->nomeeq);
					list1->hashequipas[vitoria1]->vitorias--; /*Altera o numero de vitorias da equipa 1 */
				}
				if (list->hashjogos[tentativa]->score1 < list->hashjogos[tentativa]->score2) {
					vitoria2 = Hash(list->hashjogos[tentativa]->equipa2->nomeeq);
					list1->hashequipas[vitoria2]->vitorias--; /*Altera o numero de vitorias da equipa 2 */
				}		
				
				list->hashjogos[tentativa]->score1 = score1recebido;
				list->hashjogos[tentativa]->score2 = score2recebido;

				if (score1recebido > score2recebido) {
					vitoria1 = Hash(list->hashjogos[tentativa]->equipa1->nomeeq);
					list1->hashequipas[vitoria1]->vitorias++; /*Altera o numero de vitorias da equipa 1 consoante o novo score */
				}
	
				if (score1recebido < score2recebido) {
					vitoria2 = Hash(list->hashjogos[tentativa]->equipa2->nomeeq);
					list1->hashequipas[vitoria2]->vitorias++; /*Altera o numero de vitorias da equipa 2 consoante o novo score */
				}			
			}
		}
	}
	return list; /* Retorna a hashtable agora alterada */
}

/* Funcao auxiliar que permite comprar as strings de um array de modo a ordena-las */
static int cmp_str(const void *lhs, const void *rhs)
{
    return strcmp(lhs, rhs);
}


/* Comando 'g':
	Esta funcao permite imprimir por ordem alfabetica de equipas 
	com maior numero de vitorias */
void OrdenaEquipas(listaequipas *list1, int comando) {
	int wins = 0;
	equipa *comeco = list1->inicioeq, *head = list1->inicioeq;
	listaequipas *new = NovaListaEquipas(); /* Cria uma nova lista duplamente ligada de equipas, para ordenar */

	while (comeco != NULL) { 
        if (comeco->vitorias > wins) 
        	wins = comeco->vitorias;
        comeco = comeco->proximoeq; 
    }
    while (head != NULL) {
    	if (head->vitorias == wins)
    		strcpy(new->inicioeq->nomeeq,head->nomeeq);
    	head = head->proximoeq;
    	new->inicioeq = new->inicioeq->proximoeq;
	}
	if (new->inicioeq != NULL) {
		printf("%d Melhores %d\n", comando, wins);
		qsort(new, EQUIPAS, sizeof new->inicioeq, cmp_str);
		for (; new->inicioeq->proximoeq != NULL; new->inicioeq = new->inicioeq->proximoeq) {
			printf("%d * %s\n", comando, new->inicioeq->proximoeq->nomeeq);
		}
	}
}
	
