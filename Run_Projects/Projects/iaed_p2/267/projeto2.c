#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int M = 59; /* Variavel global com o tamanho */
struct jogo** tabela;
struct jogo **hashjogos;
struct equipa **hashequipa;
int n=0;
int linha=0;
/* Hashtables de jogos e das equipas */

/* Estrutura de cada jogo */
struct jogo{
	char *nomeJogo;
	char *nomeEquipa1;
	char *nomeEquipa2;
	int r1;
	int r2;
	struct jogo *anterior, *posterior;
};

/* Estrutura de cada equipa */
struct equipa{
	int n_vitorias;
	char *nomeequipa;
	struct equipa *anterior, *posterior;
};



/* Com base nos slides das aulas */
/* Devolve a posicao do hashtable */
int hash(char *v){
	int h;
	int a = 314;
	int b = 271;
	for (h = 0; *v !='\0'; v++, a = a*b % (M-1)){
		h = (a*h + *v) % M;
	}
	return h;
}

/* Para iniciar a tabela de equipas, com base nos slides das aulas */
void StInitEquipa(){
	int i;
	hashequipa = malloc(M*sizeof(struct equipa));
	for (i=0; i < M; i++){
		hashequipa[i] = NULL; /* Inicializo tudo a NULL */
	}
}

/* Para iniciar a tabela de jogos, com base nos slides das aulas */
void StInitJogo(){
	int i;
	hashjogos = malloc(M*sizeof(struct jogo));
	for (i=0; i < M; i++){
		hashjogos[i] = NULL; /* Inicializo tudo a NULL */
	}
}

struct equipa *cria_equipa(char *nomeequipa){
	struct equipa *equipaAuxiliar = malloc(sizeof(struct equipa)); /* Cria espaco para equipa nova */
	equipaAuxiliar->nomeequipa = malloc(sizeof(char) * strlen(nomeequipa) + 1); /* Preenche com o seu nome */
	equipaAuxiliar->n_vitorias = 0;
	strcpy(equipaAuxiliar->nomeequipa, nomeequipa); /* Transfere a informacao para o ponteiro */
	return equipaAuxiliar; /* Devolve a nova equipa */
}

struct jogo *cria_jogo(char *nomeJogo, char *nomeEquipa1, char *nomeEquipa2,int r1, int r2){
	struct jogo *jogoAuxiliar = malloc(sizeof(struct jogo)); /* Cria espaco */
	jogoAuxiliar->nomeJogo = malloc(sizeof(char) * strlen(nomeJogo) + 1);
	strcpy(jogoAuxiliar->nomeJogo, nomeJogo);
	jogoAuxiliar->nomeEquipa1 = malloc(sizeof(char) * strlen(nomeEquipa1) + 1);
	strcpy(jogoAuxiliar->nomeEquipa1, nomeEquipa1);
	jogoAuxiliar->nomeEquipa2 = malloc(sizeof(char) * strlen(nomeEquipa2) + 1);
	strcpy(jogoAuxiliar->nomeEquipa2, nomeEquipa2);
	jogoAuxiliar->r1 = r1; /* Como sao inteiros escreve se logo no ponteiro */
	jogoAuxiliar->r2 = r2;
	return jogoAuxiliar;
}

/* Funcoes AUXILIARES */
void equipa_ganhou(char* nomeequipa){
	struct equipa *equipaAuxiliar;
	if (hashequipa[hash(nomeequipa)] != NULL) {
		for (equipaAuxiliar = hashequipa[hash(nomeequipa)]; equipaAuxiliar != NULL;
				equipaAuxiliar = equipaAuxiliar-> posterior){
			if (strcmp(nomeequipa, equipaAuxiliar->nomeequipa) == 0){
				equipaAuxiliar->n_vitorias += 1;
			}
		}
	}

}

void equipa_perdeu(char *nomeequipa){
	struct equipa *equipaAuxiliar;
	if (hashequipa[hash(nomeequipa)] != NULL) {
		for (equipaAuxiliar = hashequipa[hash(nomeequipa)]; equipaAuxiliar != NULL;
		equipaAuxiliar = equipaAuxiliar-> posterior){
			if (strcmp(nomeequipa, equipaAuxiliar->nomeequipa) == 0){
				equipaAuxiliar->n_vitorias -= 1; /* Decrementa o numeor de vitorias quando o score e modificado */
			}
		}
	}
}



/* Adiciona um novo jogo */
void funcao_a(){
	struct jogo *jogoAuxiliar;
	struct equipa *equipaAuxiliar;
	char *nomeJogo= malloc(sizeof(char)*1023);
	char *nomeequipa1= malloc(sizeof(char)*1023);
	char *nomeequipa2= malloc(sizeof(char)*1023);
	int r1,r2,j;
	linha++;
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nomeJogo, nomeequipa1, nomeequipa2,&r1,&r2);
	/* Verifica se o jogo existe */
	if (hashjogos[hash(nomeJogo)] != NULL) {
		for (jogoAuxiliar = hashjogos[hash(nomeJogo)]; jogoAuxiliar != NULL;
			jogoAuxiliar = jogoAuxiliar->posterior){
			if (strcmp(nomeJogo, jogoAuxiliar->nomeJogo) == 0){
				printf("%d Jogo existente.\n",linha); /* ja existe um jogo com esse nome no sistema */
				return;
			}
		}
	}
	/* Verifica se a primeira equipa existe */
	j = 0;
	if (hashequipa[hash(nomeequipa1)] != NULL) {
		for (equipaAuxiliar = hashequipa[hash(nomeequipa1)]; equipaAuxiliar != NULL; equipaAuxiliar=equipaAuxiliar->posterior){
			if (strcmp(nomeequipa1, equipaAuxiliar->nomeequipa) == 0){
					j=1;
			}
		}
		if(j==0){
			printf("%d Equipa inexistente.\n",linha);
			return;
		}
	}
	else{
		printf("%d Equipa inexistente.\n",linha);
		return;
	}
	j=0;
	/* Verifica se a segunda equipa existe */
	if (hashequipa[hash(nomeequipa2)] != NULL) {
		for (equipaAuxiliar = hashequipa[hash(nomeequipa2)]; equipaAuxiliar != NULL;
			equipaAuxiliar = equipaAuxiliar->posterior){
			if (strcmp(nomeequipa2, equipaAuxiliar->nomeequipa) == 0){
					j=1;
			}
		}
		if(j==0){
			printf("%d Equipa inexistente.\n",linha);
		}
	}
	else{
		printf("%d Equipa inexistente.\n",linha);
		return;
	}

	jogoAuxiliar = cria_jogo(nomeJogo, nomeequipa1, nomeequipa2, r1, r2);
	tabela[n]=jogoAuxiliar;
	n++;

	/* Verifica qual das equipas ganhou o jogo */
	if (r1 > r2){
		equipa_ganhou(nomeequipa1);
	}
	else if(r1<r2){ /* Pode haver empate */
		equipa_ganhou(nomeequipa2);
	}
	/* Para criar jogo, Quando nao ha elementos na lista ligada */
	if (hashjogos[hash(nomeJogo)] == NULL) {
			jogoAuxiliar->anterior = NULL; /* Primeiro jogo da lista ligada */
			jogoAuxiliar->posterior = NULL; /* Ultimo jogo da lista ligada */
			hashjogos[hash(nomeJogo)] = jogoAuxiliar;
	}

	/* Para criar jogo, Quando existem elementos na lista ligada */
	else{
		jogoAuxiliar->posterior = hashjogos[hash(nomeJogo)];
		hashjogos[hash(nomeJogo)]->anterior = jogoAuxiliar;
		jogoAuxiliar->anterior = NULL;
		hashjogos[hash(nomeJogo)] = jogoAuxiliar;
	}
}



/* Adiciona uma nova equipa */
void funcao_A(){
	struct equipa *equipaAuxiliar;
	char *nomeequipa = malloc(sizeof(char)*1023);
	linha++;
	scanf(" %[^:\n]s", nomeequipa);
	if (hashequipa[hash(nomeequipa)] != NULL) {	/* Verifica se a equipa existe, se sim nao posso adicionar */
		for (equipaAuxiliar = hashequipa[hash(nomeequipa)]; equipaAuxiliar != NULL;
			equipaAuxiliar = equipaAuxiliar-> posterior){
			if (strcmp(nomeequipa, equipaAuxiliar->nomeequipa) == 0){
				printf("%d Equipa existente.\n",linha); /* ja existe uma equipa com esse nome no sistema */
				return;
			}
		}
	}
	equipaAuxiliar = cria_equipa(nomeequipa); /* Devolve a equipa */

	/* Quando nao ha elementos na lista ligada */
	if (hashequipa[hash(nomeequipa)] == NULL) {
		equipaAuxiliar->anterior = NULL; /* Primeira equipa da lista ligada */
		equipaAuxiliar->posterior = NULL;
		hashequipa[hash(nomeequipa)] = equipaAuxiliar; /* Adicionamos a equipa nova na hashtable de equipas nesta posicao vazia */
	}

	/* Quando existem elementos na lista ligada */
	else{
		equipaAuxiliar->posterior = hashequipa[hash(nomeequipa)]; /* Equipa posterior a B e A */
		hashequipa[hash(nomeequipa)]->anterior = equipaAuxiliar; /* Equipa anterior a A e o B */
		equipaAuxiliar->anterior = NULL; /* Anterior a B nao ha */
		hashequipa[hash(nomeequipa)] = equipaAuxiliar; /* Equipa A e B estao na mesma posicao */
	}
}


/* Lista todos os jogos pela ordem em que foram introduzidos */
void funcao_l(){
	int i;
	linha++;
	for(i=0;i < n;i++){
		if(tabela[i]!=NULL){
			printf("%d %s %s %s %d %d\n",linha, tabela[i]->nomeJogo, tabela[i]->nomeEquipa1, tabela[i]->nomeEquipa2,tabela[i]->r1,tabela[i]->r2);
		}
	}
}



/* Procura um jogo pelo nome dado */
void funcao_p(){
	struct jogo* jogoAuxiliar;
	char *nomeJogo= malloc(sizeof(char)*1023);
	linha++;
	scanf(" %[^:\n]", nomeJogo);
	if (hashjogos[hash(nomeJogo)] != NULL) {	/* Verifica se o jogo existe, se sim nao posso adicionar */
		for (jogoAuxiliar = hashjogos[hash(nomeJogo)]; jogoAuxiliar != NULL;
				jogoAuxiliar = jogoAuxiliar-> posterior){
			if (strcmp(nomeJogo, jogoAuxiliar->nomeJogo) == 0){ /* Confirma se existe o jogo */
					printf("%d %s %s %s %d %d\n",linha, jogoAuxiliar->nomeJogo, jogoAuxiliar->nomeEquipa1,jogoAuxiliar->nomeEquipa2,jogoAuxiliar->r1, jogoAuxiliar->r2);
					return;
			}
		}
	}
	printf("%d Jogo inexistente.\n",linha); /* no caso de nao existir nenhum jogo com esse nome no sistema */

}



/* Procura uma equipa dado um nome */
void funcao_P(){
	struct equipa *equipaAuxiliar;
	char *nomeequipa=malloc(sizeof(char)*1023);
	linha++;
	scanf(" %[^:\n]", nomeequipa);
	if (hashequipa[hash(nomeequipa)] != NULL) {	/* Verifica se a equipa existe, se sim nao posso adicionar */
		for (equipaAuxiliar = hashequipa[hash(nomeequipa)]; equipaAuxiliar != NULL;
				equipaAuxiliar = equipaAuxiliar-> posterior){
			if (strcmp(nomeequipa, equipaAuxiliar->nomeequipa) == 0){ /* Confirma se existe a equipa */
					printf("%d %s %d\n",linha, nomeequipa, equipaAuxiliar->n_vitorias); /* Mostra o numero de vitorias da equipa em causa */
					return;
			}
		}
	}
	else{
		printf("%d Equipa inexistente.\n",linha); /* no caso de nao existir nenhuma equipa com esse nome no sistema */
	}
}




/*  Apaga um jogo dado um nome */
void funcao_r(){
	struct jogo* jogoAuxiliar;
	struct jogo* jogoAuxiliar1; /* Para poder guardar o posterior jogo antes de apagar o jogo em causa */
	char *nomeJogo= malloc(sizeof(char)*1023);
	int i;
	linha++;
	scanf(" %[^:\n]", nomeJogo);
	if (hashjogos[hash(nomeJogo)] != NULL) {	/* Verifica se o jogo existe, se sim nao posso adicionar */
		for (jogoAuxiliar = hashjogos[hash(nomeJogo)]; jogoAuxiliar != NULL;
				jogoAuxiliar = jogoAuxiliar-> posterior){
			if (strcmp(nomeJogo, jogoAuxiliar->nomeJogo) == 0){
				for(i=0;i<n;i++){
					if(strcmp(tabela[i]->nomeJogo,nomeJogo)==0){
						tabela[i] = NULL;
					}
				}
				/*Alterar o resultado das equipas*/
				if(jogoAuxiliar->r1 > jogoAuxiliar->r2){
					equipa_perdeu(jogoAuxiliar->nomeEquipa1);
				}
				else if(jogoAuxiliar->r1 < jogoAuxiliar->r2){
					equipa_perdeu(jogoAuxiliar->nomeEquipa2);
				}
				if (jogoAuxiliar->anterior == NULL){ /* Primeiro elemento da lista */
					if(jogoAuxiliar->posterior == NULL){
						hashjogos[hash(nomeJogo)] =NULL;
						return;
					}
					jogoAuxiliar1 = jogoAuxiliar->posterior;
					jogoAuxiliar1->anterior = NULL;
					hashjogos[hash(nomeJogo)] = jogoAuxiliar1; /* guarda o posterior antes de apagar */
					return;
				}
				else{ /* No meio da lista ligada */
					jogoAuxiliar1 = jogoAuxiliar->anterior;
					jogoAuxiliar1->posterior = jogoAuxiliar-> posterior;
					jogoAuxiliar = jogoAuxiliar-> posterior;
					jogoAuxiliar->anterior = jogoAuxiliar1;
					return;
				}
			}
		}
	}
	else{
		printf("%d Jogo inexistente.\n",linha);
	}
}



/* Altera o score de um jogo */
void funcao_s(){
	struct jogo *jogoAuxiliar;
	char *nomeJogo= malloc(sizeof(char)*1023);
	int r1,r2;
	linha++;
	scanf(" %[^:\n]:%d:%d", nomeJogo, &r1, &r2);
	if (hashjogos[hash(nomeJogo)] != NULL) {	/* Verifica se o jogo existe, se sim nao posso adicionar */
		for (jogoAuxiliar = hashjogos[hash(nomeJogo)]; jogoAuxiliar != NULL;
				jogoAuxiliar = jogoAuxiliar-> posterior){
			if (strcmp(nomeJogo, jogoAuxiliar->nomeJogo) == 0){
				/* Verifica se e alterado o vencedor ou nao, se sim tenho decremento as vistorias */
				if (jogoAuxiliar->r1 > jogoAuxiliar->r2){
					if(r1 < r2){
						equipa_ganhou(jogoAuxiliar->nomeEquipa2);
						equipa_perdeu(jogoAuxiliar->nomeEquipa1);
					}
					else if(r1==r2){
						equipa_perdeu(jogoAuxiliar->nomeEquipa1);
					}
				}
				else if(jogoAuxiliar->r1 < jogoAuxiliar->r2){
					if(r1 > r2){
						equipa_ganhou(jogoAuxiliar->nomeEquipa1);
						equipa_perdeu(jogoAuxiliar->nomeEquipa2);
					}
					else if(r1==r2){
						equipa_perdeu(jogoAuxiliar->nomeEquipa2);
					}
				}
				else{
					/*caso em que o jogo estava empatado*/
					if(r1>r2){
						equipa_ganhou(jogoAuxiliar->nomeEquipa1);
					}
					else if(r1<r2){
						equipa_ganhou(jogoAuxiliar->nomeEquipa2);
					}
				}
				jogoAuxiliar->r1 = r1;
				jogoAuxiliar->r2 = r2;
			}
		}
	}
	else{
		printf("%d Jogo inexistente.\n",linha);
	}
}




/* Utilizo a funcao l para listar tamebem os jogos por ordem lexiolografca */
void funcao_g(){
	int maximo;
	int i,j,k;
	struct equipa* equipaAuxiliar;
	char* nomeAuxiliar;
	char** nomes= malloc(sizeof(char*)*200);
	for(j=0; j<200; j++){
		nomes[j]=malloc(sizeof(char)*1023);
	}
	linha++;
	maximo = -1;
	j = 0;

	for(i = 0; i < M; i++){
		if(hashequipa[i]!=NULL){
			for (equipaAuxiliar = hashequipa[i]; equipaAuxiliar != NULL;
			equipaAuxiliar = equipaAuxiliar-> posterior){
				if(equipaAuxiliar->n_vitorias > maximo){
					maximo = equipaAuxiliar->n_vitorias;
				}
			}
		}
	}

	if(maximo==-1){
		for(j=0; j<200; j++){
			free(nomes[j]);
		}
		free(nomes);
		return;
	}

	for(i = 0; i < M; i++){
		if(hashequipa[i]!=NULL){
			for (equipaAuxiliar = hashequipa[i]; equipaAuxiliar != NULL;
			equipaAuxiliar = equipaAuxiliar-> posterior){
				if(equipaAuxiliar->n_vitorias == maximo){
					strcpy(nomes[j],equipaAuxiliar->nomeequipa);
					j++;
				}
			}
		}
	}
	for(i=0;i<j;i++){
		for(k=0;k<j;k++){
			if(strcmp(nomes[k],nomes[i])>0){
				nomeAuxiliar = nomes[i];
				nomes[i] = nomes[k];
				nomes[k] = nomeAuxiliar;
			}
		}
	}
	printf("%d Melhores %d\n",linha,maximo);
	for(i=0;i<j;i++){
		printf("%d * %s\n",linha,nomes[i]);
	}

	for(j=0; j<200; j++){
		free(nomes[j]);
	}
	free(nomes);
	return;
}



void funcao_x(){
	int i;
	struct equipa* equipaAuxiliar;
	struct equipa* equipaAuxiliar1;
	struct jogo* jogoAuxiliar;
	struct jogo* jogoAuxiliar1;

	for(i=0;i<M;i++){
		if(hashequipa[i]!=NULL){
			equipaAuxiliar = hashequipa[i];
			while(equipaAuxiliar != NULL){
				equipaAuxiliar1 = equipaAuxiliar->posterior;
				free(equipaAuxiliar->nomeequipa);
				free(equipaAuxiliar);
				equipaAuxiliar = equipaAuxiliar1;
			}
		}
	}
	for(i=0;i<M;i++){
		if(hashjogos[i]!=NULL){
			jogoAuxiliar = hashjogos[i];
			while(jogoAuxiliar != NULL){
				jogoAuxiliar1 = jogoAuxiliar->posterior;
				free(jogoAuxiliar->nomeJogo);
				free(jogoAuxiliar->nomeEquipa1);
				free(jogoAuxiliar->nomeEquipa2);
				free(jogoAuxiliar);
				jogoAuxiliar = jogoAuxiliar1;
			}
		}
	}
	free(hashjogos);
	free(hashequipa);

}


/* funcao MAIN */
int main() {
	char comando;
	int i;
	StInitJogo();
	StInitEquipa();
	tabela = malloc(sizeof(struct jogo*)*300);
	for(i = 0; i < 300; i++){
		tabela[i] = NULL;
	}
	while(1){
		comando = getchar();
		switch (comando){
			case 'a': funcao_a();
			/* Adiciona um novo jogo */
				break;
			case 'A': funcao_A();
			/* Adiciona uma nova equipa */
				break;
			case 'l': funcao_l();
			/* Lista todos os jogos pela ordem em que foram introduzidos */
				break;
			case 'p': funcao_p();
			/* Procura um jogo pelo nome dado */ 
				break;
			case 'P': funcao_P();
			/* Procura uma equipa */
				break;
			case 'r': funcao_r();
			/* Apaga um jogo dado um nome */
				break;
			case 's': funcao_s();
			/* Altera o score de um jogo */
				break;
			case 'g': funcao_g();
			/* Encontra as equipas que venceram mais jogos */
				break;
			case 'x': funcao_x();
				return 0;
				break;
		}
	}
	return 0;
}
