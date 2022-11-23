#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "includes.h"

/* Adiciona uma equipa a tab dada caso este nao esteja ja na tabela, e atualiza a variavel nl */
void adicionaEquipa(TabEquipas* tab, int* nl);
/* Adiciona um jogo a tab dada, da erro se o jogo ja existir ou se uma das equipas nao existirem e atualiza a variavel nl */
void adicionaJogo(TabJogos* tabjogos, TabEquipas* tabeq, int* nl);
/* Procura uma equipa com o nome dado e imprime o nome e as suas vitorias, da erro se nao existir esta equipa, atualiza a variavel nl */
void procuraEquipa(TabEquipas* tab, int* nl);
/* Procura um jogo com o nome dado e imprime os seus dados, da erro se nao existir esta equipa, atualiza a variavel nl */
void procuraJogo(TabJogos* tabjogos, int* nl);
/* Lista as equipas com o maior numero de vitorias por ordem lexicografica, atualiza a variavel nl */
void listaEquipas(TabEquipas* tabeq, int* nl);
/* Lista todos os jogos introduzidos na tabela por ordem de introducao, atualiza a variavel nl */
void listaJogos(TabJogos* tabjogos, int* nl);
/* Altera o score de um jogo e tambem as vitorias das equipas, da erro se o jogo nao existir, atualiza a variavel nl */
void alteraScore(TabJogos* tabjogos, TabEquipas* tabeq, int* nl);
/* Apaga um jogo e subtrai esse jogo das vitorias da equipa vencedora, da erro se o jogo nao existir, atualiza a variavel nl */
void apagaJogo(TabJogos* tabjogos, TabEquipas* tabeq, int* nl);

int main(){
	char c;
	int num_linha = 0;
	TabEquipas* tab_eq = novaTabEq();
	TabJogos* tab_j = novaTabJogos();

	while((c = getchar()) != 'x'){
		switch (c){
		case 'a':
			adicionaJogo(tab_j, tab_eq, &num_linha);
			break;

		case 'A':
			adicionaEquipa(tab_eq, &num_linha);
			break;

		case 'l':
			listaJogos(tab_j, &num_linha);
			break;

		case 'p':
			procuraJogo(tab_j, &num_linha);
			break;

		case 'P':
			procuraEquipa(tab_eq, &num_linha);
			break;

		case 'r':
			apagaJogo(tab_j, tab_eq, &num_linha);
			break;

		case 's':
			alteraScore(tab_j, tab_eq, &num_linha);
			break;

		case 'g':
			listaEquipas(tab_eq, &num_linha);
			break;

		default:
			break;
		}
		getchar();
	}

	destroiTabEq(tab_eq);
	destroiTabJogos(tab_j);
	return 0;
}

/* Funcoes */

void adicionaEquipa(TabEquipas* tab, int* nl){
	Equipa* eq;
	char nome[MAX_STRING];
	scanf(" %[^:\n]", nome);

	(*nl)++;
	eq = procuraTabEq(tab, nome);

	if(eq)	printf("%d Equipa existente.\n", *nl);
	else	pushTabEq(tab, novaEquipa(novastring(nome)));
}

void adicionaJogo(TabJogos* tabjogos, TabEquipas* tabeq, int* nl){
	char nome[MAX_STRING], eq1[MAX_STRING], eq2[MAX_STRING];
	int sc1, sc2;
	Equipa* vencedor = NULL;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, eq1, eq2, &sc1, &sc2);

	(*nl)++;

	if(procuraTabJogos(tabjogos, nome)){
		printf("%d Jogo existente.\n", *nl);
		return;
	}
	
	if(!procuraTabEq(tabeq, eq1) || !procuraTabEq(tabeq, eq2)){
		printf("%d Equipa inexistente.\n", *nl);
		return;
	}	
	
	pushTabJogos(tabjogos, novoJogo(novastring(nome), novastring(eq1), novastring(eq2), sc1, sc2, *nl));

	if(sc1 > sc2)	vencedor = procuraTabEq(tabeq, eq1);
	if(sc1 < sc2)	vencedor = procuraTabEq(tabeq, eq2);

	if(vencedor)	vencedor->vitorias++;
}

void procuraEquipa(TabEquipas* tab, int* nl){
	char nome[MAX_STRING];
	Equipa* e;
	scanf(" %[^:\n]", nome);

	(*nl)++;
	e = procuraTabEq(tab, nome);

	if(e)	printf("%d %s %d\n", *nl, e->nome, e->vitorias);
	else	printf("%d Equipa inexistente.\n", *nl);
}

void procuraJogo(TabJogos* tabjogos, int* nl){
	char nome[MAX_STRING];
	Jogo* j;

	scanf(" %s", nome);

	(*nl)++;
	j = procuraTabJogos(tabjogos, nome);

	if(j)	printf("%d %s %s %s %d %d\n", *nl, j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
	else	printf("%d Jogo inexistente.\n", *nl);
}

void listaEquipas(TabEquipas* tabeq, int* nl){
	int i;
	Equipa* arr;
	(*nl)++;

	arr = copiaTabEq(tabeq);
	qsort(arr, tabeq->n_eqs, sizeof(Equipa), comparaEq);
	
	if(tabeq->n_eqs > 0)	printf("%d Melhores %d\n", *nl, arr[0].vitorias);
	for(i = 0; i < tabeq->n_eqs; i++)
		if(arr[i].vitorias != arr[0].vitorias)	break;	/*So revisamos ate as vitorias nao serem as maximas */
		else	printf("%d * %s\n", *nl, arr[i].nome);

	free(arr);
}

void listaJogos(TabJogos* tabjogos, int* nl){
	int i;
	Jogo* arr;
	
	(*nl)++;

	arr = copiaTabJogos(tabjogos);

	qsort(arr, tabjogos->n_jogos, sizeof(Jogo), comparaJogos);

	for(i = 0; i < tabjogos->n_jogos; i++)
		printf("%d %s %s %s %d %d\n", *nl, arr[i].nome, arr[i].equipa1, arr[i].equipa2, arr[i].score1, arr[i].score2);

	free(arr);
}

void alteraScore(TabJogos* tabjogos, TabEquipas* tabeq, int* nl){
	char nome[MAX_STRING];
	int sc1, sc2;
	int res_antes, res_depois;	/* res_antes e res_depois correspondem a vitoria/derrota da equipa1 */
	Equipa* eq1, * eq2;
	Jogo* j;

	scanf(" %[^:\n]:%d:%d", nome, &sc1, &sc2);

	(*nl)++;
	j = procuraTabJogos(tabjogos, nome);
	
	if(!j){
		printf("%d Jogo inexistente.\n", *nl);
		return;
	}

	res_antes = CALCULA_RES(j->score1, j->score2);
	res_depois = CALCULA_RES(sc1, sc2);
	j->score1 = sc1;
	j->score2 = sc2;

	if(res_antes == res_depois)	return;		/* nao houve alteracoes nas vitorias */

	eq1 = procuraTabEq(tabeq, j->equipa1);
	eq2 = procuraTabEq(tabeq, j->equipa2);

	if(res_antes == VITORIA){
		eq1->vitorias--;
		if(res_depois == DERROTA)	eq2->vitorias++;
	} else if(res_antes == DERROTA){
		eq2->vitorias--;
		if(res_depois == VITORIA)	eq1->vitorias++;
	} else
		if(res_depois == VITORIA)	eq1->vitorias++;
		else if(res_depois == DERROTA)	eq2->vitorias++;
}

void apagaJogo(TabJogos* tabjogos, TabEquipas* tabeq, int* nl){
	char nome[MAX_STRING];
	Jogo* j;
	Equipa* eq;

	scanf(" %[^:\n]", nome);

	(*nl)++;

	j = procuraTabJogos(tabjogos, nome);
	if(!j){
		printf("%d Jogo inexistente.\n", *nl);
		return;
	}

	if(CALCULA_RES(j->score1, j->score2) == VITORIA){
		eq = procuraTabEq(tabeq, j->equipa1);
		eq->vitorias--;
	}
	if(CALCULA_RES(j->score1, j->score2) == DERROTA){
		eq = procuraTabEq(tabeq, j->equipa2);
		eq->vitorias--;
	}

	popTabJogos(tabjogos, nome);
}