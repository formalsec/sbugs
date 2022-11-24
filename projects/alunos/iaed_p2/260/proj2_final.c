#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

#define str_max_jogos_equipas 1024
#define tamanho_hash_table 5000

/* Para resolver possiveis colisoes, foi utilizada a resolucao por encadeamento 
externo. */ 

/* Funcao auxiliar que estabelece uma chave a ser introduzida na hash table. */
int codigo_hash(char *nome){
	int h = 0, a = 127;
	for (; *nome != '\0'; nome++){
		h = (a * h + *nome) % tamanho_hash_table;
	}
	return h; 
}

/* Funcao auxiliar que inicializa uma hash table de jogos. */
hash_table_jogos *init_hash_jogos(){
	int h;
	/* aloca a memoria para o ponteiro do tipo hash_table_jogos */
	hash_table_jogos *hash_j = can_fail_malloc(sizeof(hash_table_jogos));

	for(h = 0; h < tamanho_hash_table; h++){
		/* inicializa o ponteiro de vetores tudo a NULL */
		hash_j->vetor[h] = NULL;
	}
	/* retorna o ponteiro */
	return hash_j;
}

/* Funcao auxiliar que inicializa uma hash table de equipas. */
hash_table_equipas *init_hash_equipas(){
	int h;
	/* aloca a memoria para o ponteiro do tipo hash_table_equipas */
	hash_table_equipas *hash_e = can_fail_malloc(sizeof(hash_table_equipas));

	for(h = 0; h < tamanho_hash_table; h++){
		/* inicializa o ponteiro de vetores tudo a NULL */
		hash_e->vetor[h] = NULL;
	}
	/* retorna o ponteiro */
	return hash_e;
}

/* Funcao auxiliar que liberta toda a memoria alocada na estrutura jogo. */
void free_jogo(jogo *pointr){
	free(pointr->nome_jogo);
	free(pointr->equipa_1);
	free(pointr->equipa_2);
	free(pointr);
}

/* Funcao auxiliar que liberta toda a memoria alocada na estrutura equipa. */
void free_equipa(sist_equipas *pointr){
	free(pointr->nome_equipa);
	free(pointr);
}

/* Funcao auxiliar que elimina uma estrutura jogo e atualiza a list_games, 
   retirando a estrutura dentro da lista de jogos. */
void pop_jogo(list_games *lst, jogo *game){
	/* Verifica se o jogo anterior ao jogo a ser removido existe */
	if(game->prev != NULL){
		game->prev->next = game->next;
	}
	else{
		/* Se nao existir, o jogo a seguir ao jogo a ser removido passa a ser o primeiro 
		da lista */
		lst->head = game->next;
	}
	/* Verifica se o jogo a seguir ao jogo a ser removido existe */
	if(game->next != NULL){
		game->next->prev = game->prev;
	}
	else{
		/* Se nao existir, a equipa a seguir a equipa a ser removida passa a ser a primeira 
		da lista */
		lst->last = game->prev;
	}
	free_jogo(game);
}

/* Funcao auxiliar que adiciona um ponteiro da estrutura jogo na hash table 
   atraves do seu codigo hash. */
void push_jogo(int index, jogo *game,hash_table_jogos *hash_jogos){
	jogo_hash *gm = can_fail_malloc(sizeof(jogo_hash));

	gm->pointr_jogo = game;
	gm->next = hash_jogos->vetor[index];
	hash_jogos->vetor[index] = gm;
}

/* Funcao auxiliar que adiciona um ponteiro da estrutura equipa na hash table
   atraves do seu codigo hash. */
void push_equipa(int index, sist_equipas *team,hash_table_equipas *hash_equipas){
	equipa_hash *tm = can_fail_malloc(sizeof(equipa_hash));

	tm->pointr_equipa = team;
	tm->next = hash_equipas->vetor[index];
	hash_equipas->vetor[index] = tm;
}

/* Funcao auxiliar que procura o nome de um jogo. */
jogo_hash *procura_nome_jogo(char nome[str_max_jogos_equipas],hash_table_jogos *hash_jogos){
	int chave_jogo = codigo_hash(nome);
	jogo_hash *temp;

	/* Ciclo for que percorre toda a hash table de jogos. Se o nome do jogo que esta
	   armazenado no pointer dentro da hash table for diferente ao nome do jogo 
	   introduzido pelo usuario no stdin, retorna NULL. */
	for(temp = hash_jogos->vetor[chave_jogo]; temp != NULL; temp = temp->next){
		if(strcmp(temp->pointr_jogo->nome_jogo,nome) == 0){
			return temp;
		}	
	}
	return NULL;
}

/* Funcao auxiliar que calcula o numero de vitorias de uma equipa. */
int n_jogos_ganhos(list_games *lst_jogos, char equipa[str_max_jogos_equipas]){
	jogo *pointr = lst_jogos->head;
	int jogos_ganhos = 0;

	/* Ciclo while para percorrer a lista de jogos. */
	while(pointr != NULL){
		/* If para ver se o nome da equipa 1 armazenada na lista de jogos e igual 
		   ao nome da equipa introduzida pelo usuario no stdin. */
		if(strcmp(pointr->equipa_1, equipa) == 0){
			/* Se o score 1 e maior que o score 2, incrementa. */
			if(pointr->score_1 > pointr->score_2){
				jogos_ganhos++;
			}
			else{
				jogos_ganhos = jogos_ganhos;
			}
		}
		/* If para ver se o nome da equipa 2 armazenada na lista de jogos e igual 
		   ao nome da equipa introduzida pelo usuario no stdin. */
		if(strcmp(pointr->equipa_2, equipa) == 0){
			/* Se o score 2 e maior que o score 1, incrementa. */
			if(pointr->score_2 > pointr->score_1){
				jogos_ganhos++;
			}
			else{
				jogos_ganhos = jogos_ganhos;
			}
		}
		pointr = pointr->next;
	}
	/* retorna o numero de jogos ganhos pela equipa que foi introduzida 
	   pelo utilizador no stdin. */
	return jogos_ganhos;
}

/* Funcao auxiliar que procura o nome de uma equipa. */
equipa_hash *procura_nome_equipa(char nome[str_max_jogos_equipas],hash_table_equipas *hash_equipas){
	int chave_equipa = codigo_hash(nome);
	equipa_hash *temp;

	/* Ciclo for que percorre toda a hash table de equipas. Se o nome da equipa que esta
	   armazenada no pointer dentro da hash table for diferente ao nome da equipa 
	   introduzida pelo usuario no stdin, retorna NULL. */
	for(temp = hash_equipas->vetor[chave_equipa] ; temp != NULL; temp = temp->next){
		if(strcmp(temp->pointr_equipa->nome_equipa, nome) == 0){
			return temp;
		}
	}
	return NULL;
}

/* Funcao que lista todos os jogos pela ordem que foram introduzidos atraves
   do comando l inserido pelo usuario no stdin. */
void comando_l(int NL,list_games *imprime){
	jogo *pointer = imprime->head;

	/* Ciclo while para percorrer a lista de jogos. */
	while(pointer != NULL){
		printf("%d %s %s %s %d %d\n", NL, pointer->nome_jogo, pointer->equipa_1, pointer->equipa_2, pointer->score_1, pointer->score_2);
		pointer = pointer->next;
	}	

}

/* Funcao auxiliar que liberta a memoria alocada na estrutura da lista de jogos e
   na estrutura da hash table de jogos. */
void free_hash_table_jogos(list_games *lst_jogos,hash_table_jogos *hash_jogos){
	int h;
	jogo_hash *aux;
	jogo_hash *hash_j;
	jogo *temp;

	for(h = 0; h < tamanho_hash_table; h++){
		hash_j = hash_jogos->vetor[h];
		while(hash_j != NULL){
			free(hash_j->pointr_jogo->nome_jogo);
			free(hash_j->pointr_jogo->equipa_1);
			free(hash_j->pointr_jogo->equipa_2);
			free(hash_j->pointr_jogo);
			aux = hash_j->next;
			free(hash_j);
			hash_j = aux;
		}
	}
	while(lst_jogos->head != NULL){
		temp = lst_jogos->head->next;
		free(lst_jogos->head);
		lst_jogos->head = temp;
	}
	free(hash_jogos);
	free(lst_jogos);
}

/* Funcao auxiliar que liberta a memoria alocada na estrutura da lista de equipas e
   na estrutura da hash table de equipas. */
void free_hash_table_equipas(list_teams *lst_equipas,hash_table_equipas *hash_equipas){
	int h;
	equipa_hash *aux;
	equipa_hash *hash_e;
	sist_equipas *temp;

	for(h = 0; h < tamanho_hash_table; h++){
		hash_e = hash_equipas->vetor[h];
		while(hash_e != NULL){
			free(hash_e->pointr_equipa->nome_equipa);
			aux = hash_e->next;
			free(hash_e);
			hash_e = aux;
		}
	}

	while(lst_equipas->head != NULL){
		temp = lst_equipas->head->next;
		free(lst_equipas->head);
		lst_equipas->head = temp;
	}
	free(hash_equipas);
	free(lst_equipas);
}

/* Funcao auxiliar que apaga um jogo da lista de jogos, da hash table de jogos e elimina 
   a estrutura deste com o auxilio da funcao pop_jogo. */
void apaga_jogo(list_games *lst_jogos, char nome[str_max_jogos_equipas],hash_table_jogos *hash_jogos){
	int chave_jogo = codigo_hash(nome);
	jogo_hash *verifica_jogo = hash_jogos->vetor[chave_jogo];
	jogo_hash *temp;

	/* If para ver se existe algum pointeiro nao vazio na hash table de chave igual a 
	chave jogo, neste caso. */
	if(verifica_jogo != NULL){
		/* Se o nome do jogo armazenado na hash table for igual ao nome do jogo inserido 
		pelo usuario no stdin, vai ocorrer a eliminacao do ponteiro do jogo na hash table. */
		if(strcmp(verifica_jogo->pointr_jogo->nome_jogo, nome) == 0){
			/* Ponteiro auxiliar que vai guardar o proximo ponteiro do jogo com chave 
			chave jogo. */
			temp = verifica_jogo->next;
			pop_jogo(lst_jogos, verifica_jogo->pointr_jogo);
			free(verifica_jogo);
			hash_jogos->vetor[chave_jogo] = temp;
		}
		/* Ciclo while para ver se ainda existe mais algum ponteiro de jogo com o mesmo 
		valor de chave. */
		while(verifica_jogo->next != NULL){
			if(strcmp(verifica_jogo->next->pointr_jogo->nome_jogo, nome) == 0){
				break;
			}
			else{
				verifica_jogo = verifica_jogo->next;
			}
		}
		temp = verifica_jogo->next;
		pop_jogo(lst_jogos, temp->pointr_jogo);
		free(temp);
		verifica_jogo->next = temp->next;
	}
}

/* Funcao que adiciona um novo jogo atraves do comando a inserido pelo usuario no stdin. */
void comando_a(int NL,list_games *lst_jogos,hash_table_jogos *hash_jogos,hash_table_equipas *hash_equipas){
	jogo_hash *pointr_jogo;
	equipa_hash *pointr_equipa_1;
	equipa_hash *pointr_equipa_2;
	char nome[str_max_jogos_equipas];
	char equipa_1[str_max_jogos_equipas], equipa_2[str_max_jogos_equipas];
	int score_1, score_2;
	int chave_jogo;
	jogo *novo_jogo = can_fail_malloc(sizeof(jogo));
	
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,equipa_1,equipa_2,&score_1,&score_2);

	novo_jogo->nome_jogo = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
	novo_jogo->equipa_1 = can_fail_malloc(sizeof(char) * (strlen(equipa_1) + 1));
	novo_jogo->equipa_2 = can_fail_malloc(sizeof(char) * (strlen(equipa_2) + 1));
	
	strcpy(novo_jogo->nome_jogo, nome);
	strcpy(novo_jogo->equipa_1, equipa_1);
	strcpy(novo_jogo->equipa_2, equipa_2);
	novo_jogo->score_1 = score_1;
	novo_jogo->score_2 = score_2;
	novo_jogo->next = NULL;
	novo_jogo->prev = lst_jogos->last;
	pointr_jogo = procura_nome_jogo(nome,hash_jogos);
	pointr_equipa_1 = procura_nome_equipa(equipa_1,hash_equipas);
	pointr_equipa_2 = procura_nome_equipa(equipa_2,hash_equipas);

	/* If para ver se o nome do jogo que foi inserido pelo usuario no stdin nao existe no 
	sistema. */
	if(pointr_jogo == NULL){
		/* If para ver se alguma das equipas inseridas pelo usuario no stdin existe. */
		if(pointr_equipa_1 != NULL && pointr_equipa_2 != NULL){
			/* If para ver se ainda nao existem jogos na lista de jogos. Adiciona o jogo 
			na head da lista de jogos e na hash table se verificar a condicao. */
			if(lst_jogos->head == NULL){
				lst_jogos->head = novo_jogo;
				chave_jogo = codigo_hash(novo_jogo->nome_jogo);
				push_jogo(chave_jogo, novo_jogo,hash_jogos);
			}
			/* Caso contrario, reposiciona os jogos na lista e adiciona o jogo na lista de
			 jogos e hash table. */
			else{
				novo_jogo->prev = lst_jogos->last;
				lst_jogos->last->next = novo_jogo;
				chave_jogo = codigo_hash(novo_jogo->nome_jogo);
				push_jogo(chave_jogo, novo_jogo,hash_jogos);
			}
			lst_jogos->last = novo_jogo;	
		}
		else{
			printf("%d Equipa inexistente.\n", NL);
		}
	}
	else{
			printf("%d Jogo existente.\n", NL);
	}
}

/* Funcao que adiciona uma nova equipa atraves do comando A inserido pelo usuario no 
   stdin. */
void comando_A(int NL,list_teams *lst_equipas,hash_table_equipas *hash_equipas){
	equipa_hash *pointr_equipa;
	char nome[str_max_jogos_equipas];
	int chave_equipa;
	sist_equipas *nova_equipa = can_fail_malloc(sizeof(sist_equipas));

	scanf(" %[^\n]",nome);

	nova_equipa->nome_equipa = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
	
	strcpy(nova_equipa->nome_equipa, nome);
	nova_equipa->jogos_ganhos = 0;
	nova_equipa->next = NULL;
	nova_equipa->prev = lst_equipas->last;
	pointr_equipa = procura_nome_equipa(nome,hash_equipas);

	/* If para ver se o nome da equipa que foi inserida pelo usuario no stdin nao existe no 
	sistema. */
	if(pointr_equipa == NULL){
		/* If para ver se ainda nao existem equipas na lista de equipas. Adiciona a equipa 
			na head da lista de equipas e na hash table se verificar a condicao. */
		if(lst_equipas->head == NULL){
			lst_equipas->head = nova_equipa;
			chave_equipa = codigo_hash(nova_equipa->nome_equipa);
			push_equipa(chave_equipa, nova_equipa,hash_equipas);
		}
		/* Caso contrario, reposiciona as equipas na lista e adiciona a equipa na lista de
		 equipas e na hash table. */
		else{
			nova_equipa->prev = lst_equipas->last;
			lst_equipas->last->next = nova_equipa;
			chave_equipa = codigo_hash(nova_equipa->nome_equipa);
			push_equipa(chave_equipa, nova_equipa,hash_equipas);
		}
		lst_equipas->last = nova_equipa;	
	}
	else{
		printf("%d Equipa existente.\n", NL);
	}
}

/* Funcao que procura uma equipa atraves do comando P inserido pelo usuario no stdin. */
void comando_P(int NL,list_games *lst_jogos,hash_table_equipas *hash_equipas){
	equipa_hash *pointr_team;
	char equipa[str_max_jogos_equipas];
	int wins;

	scanf(" %[^\n]", equipa);

	pointr_team = procura_nome_equipa(equipa,hash_equipas);

	/* If para ver se o nome da equipa que foi inserida pelo usuario no stdin existe no 
	sistema. */
	if(pointr_team != NULL){
		wins = n_jogos_ganhos(lst_jogos, equipa);
		printf("%d %s %d\n", NL, equipa, wins);
	}
	else{
		printf("%d Equipa inexistente.\n", NL);
	}
}

/* Funcao que apaga um jogo atraves do comando r inserido pelo usuario no stdin. */
void comando_r(int NL,list_games *lst_jogos,hash_table_jogos *hash_jogos){
	jogo_hash *pointr_jogo;
	char nome[str_max_jogos_equipas];

	scanf(" %[^\n]", nome);

	pointr_jogo = procura_nome_jogo(nome,hash_jogos);

	/* If para ver se o nome do jogo que foi inserido pelo usuario no stdin existe no 
	sistema. */
	if(pointr_jogo != NULL){
		apaga_jogo(lst_jogos,nome,hash_jogos);
	}
	else{
		printf("%d Jogo inexistente.\n", NL);
	}
}

/* Funcao que procura um jogo atraves do comando p inserido pelo usuario no stdin. */
void comando_p(int NL,hash_table_jogos *hash_jogos){
	jogo_hash *pointer_jogo;
	char nome[str_max_jogos_equipas];

	scanf(" %[^\n]", nome);

	pointer_jogo = procura_nome_jogo(nome,hash_jogos);

	/* If para ver se o nome do jogo que foi inserido pelo usuario no stdin existe no 
	sistema. */
	if(pointer_jogo != NULL){
		printf("%d %s %s %s %d %d\n", NL, pointer_jogo->pointr_jogo->nome_jogo, pointer_jogo->pointr_jogo->equipa_1, pointer_jogo->pointr_jogo->equipa_2, pointer_jogo->pointr_jogo->score_1, pointer_jogo->pointr_jogo->score_2);
	}
	else{
		printf("%d Jogo inexistente.\n", NL);
	}
}

/* Funcao que altera a pontuacao de um jogo atraves do comando inserido pelo usuario 
   no stdin. */
void comando_s(int NL,hash_table_jogos *hash_jogos){
	jogo_hash *pointer_jogo;
	char nome[str_max_jogos_equipas];
	int score_1;
	int score_2;

	scanf(" %[^:\n]:%d:%d", nome, &score_1, &score_2);

	pointer_jogo = procura_nome_jogo(nome,hash_jogos);

	/* If para ver se o nome do jogo que foi inserido pelo usuario no stdin existe no 
	sistema. */
	if(pointer_jogo != NULL){
		/* Verificada a condicao, altera os scores.  */
		pointer_jogo->pointr_jogo->score_1 = score_1;
		pointer_jogo->pointr_jogo->score_2 = score_2;
	}
	else{
		printf("%d Jogo inexistente.\n", NL);
	}
}

/* Sistema de gestao. */
int main(){
	char letra;
	int NL = 0;
	list_games *lst_jogos;
	list_teams *lst_equipas;
	hash_table_jogos *hash_jogos = init_hash_jogos();
	hash_table_equipas *hash_equipas = init_hash_equipas();
	lst_jogos = can_fail_malloc(sizeof(list_games));
	lst_jogos->head = NULL;
	lst_jogos->last = NULL;
	lst_equipas = can_fail_malloc(sizeof(list_teams));
	lst_equipas->head = NULL;
	lst_equipas->last = NULL;
	
	while(1){
		letra = getchar();
    	switch (letra){
			case 'a':
				NL++;
				comando_a(NL,lst_jogos,hash_jogos,hash_equipas);
				break;
			case 'A':
				NL++;
				comando_A(NL,lst_equipas,hash_equipas);
				break;
			case 'l':
				NL++;
				comando_l(NL,lst_jogos);
				break;
			case 'p':
				NL++;
				comando_p(NL,hash_jogos);
				break;
			case 'P':
				NL++;
				comando_P(NL,lst_jogos,hash_equipas);
				break;
			case 'r':
				NL++;
				comando_r(NL,lst_jogos,hash_jogos);
				break;
			case 's':
				NL++;
				comando_s(NL,hash_jogos);
				break;
			/*case 'g':
				comando_g();
				NL++;
				break; */ 
			case 'x':
				/* Corri com o comando do test-vg e deu erros de memoria nestas duas funcoes.
				Nao sei quais sao os erros.
				free_hash_table_jogos(lst_jogos,hash_jogos); 
				free_hash_table_equipas(lst_equipas,hash_equipas); */
				return 0;
			default:
				break;
    	}
	    scanf("\n");
	}
}

