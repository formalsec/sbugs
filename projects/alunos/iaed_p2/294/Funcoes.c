#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Funcoes.h"

/*---------------------------------------------------------------------------------------
*	__A__ - Adiciona uma nova equipa.
*	* Formato de entrada: "A nome"
*--------------------------------------------------------------------------------------*/
void A(Hash_Equipa* ptr_HTE, Lista_Equipas* CE, int* Contador_Instrucoes){
	char equipa[STR_LEN];
	Equipas* aux;

	getchar();
	scanf("%[^:\n]", equipa);
	*Contador_Instrucoes += 1;

	if (!(hash_procura_Equipa(ptr_HTE, equipa))){
		int index = hash(equipa);

		aux = can_fail_malloc(sizeof(Equipas));

		aux -> nome = can_fail_malloc(strlen(equipa) + 1);
		strcpy(aux -> nome, equipa);	/*guarda o nome*/

		aux -> vitorias = 0;	/*inicia as vitorias a zero*/

		aux -> proximo = CE -> topo;
		CE -> topo = aux;	/*o topo da lista e atualizado*/
		hash_insercao_EQUIPAS(ptr_HTE, index, aux);	/*insere o ponteiro na hash*/
	}
	else
		printf("%d Equipa existente.\n", *Contador_Instrucoes);
}

/*---------------------------------------------------------------------------------------
*	__a__ - Adiciona um novo jogo.
*	* Formato de entrada: "a nome:equipa1:equipa2:score1:score2"
*--------------------------------------------------------------------------------------*/
void a(Hash_Jogo* ptr_HTJ, Hash_Equipa* ptr_HTE, Lista_Jogos* CJ, int* Contador_Instrucoes){
	char nome_jogo[STR_LEN], equipa01[STR_LEN], equipa02[STR_LEN];
	int pontuacao01, pontuacao02;
	Jogo* aux;

	getchar();
	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo, equipa01, equipa02, &pontuacao01, &pontuacao02);
	*Contador_Instrucoes += 1;

	if (hash_procura_Jogo(ptr_HTJ, nome_jogo))
		printf("%d Jogo existente.\n", *Contador_Instrucoes);

	else if(!(hash_procura_Equipa(ptr_HTE, equipa01)) || (!(hash_procura_Equipa(ptr_HTE, equipa02))))	
		printf("%d Equipa inexistente.\n", *Contador_Instrucoes);
		
	else{
		int index = hash(nome_jogo);
		aux = can_fail_malloc(sizeof(Jogo));

		aux -> nome = can_fail_malloc((strlen(nome_jogo) + 1));
		strcpy(aux -> nome, nome_jogo);		/*guarda o nome do jogo*/

		aux -> equipa1 = can_fail_malloc((strlen(equipa01) + 1));
		strcpy(aux -> equipa1, equipa01);	/*guarda o nome da equipa1*/

		aux -> equipa2 = can_fail_malloc((strlen(equipa02) + 1));
		strcpy(aux -> equipa2, equipa02);	/*guarda o nome da equipa2*/

		aux -> pontuacao1 = pontuacao01;	/*guarda as pontuacoes*/
		aux -> pontuacao2 = pontuacao02;

		if (pontuacao01 > pontuacao02){
			Equipas* aux_t = hash_procura_Equipa(ptr_HTE, equipa01);	/*atualiza vitorias*/
			aux_t -> vitorias += 1;
		}

		else if(pontuacao01 < pontuacao02){
			Equipas* aux_t = hash_procura_Equipa(ptr_HTE, equipa02);	/*atualiza vitorias*/
			aux_t -> vitorias += 1;
		}

		aux -> proximo = NULL;
		aux -> anterior = CJ -> fim;

		if (!(CJ -> fim))				/*se nao existir ultimo e o topo*/
			CJ -> topo = aux;
		else
			CJ -> fim -> proximo = aux;	/*caso contrario o proximo do ultimo e o aux*/

		CJ -> fim = aux;		/*quando acabar de inserir tudo, tenho de dizer wue o meu aux e o novo fim*/
		hash_insercao_JOGOS(ptr_HTJ, index, aux);	/*insere o ponteiro na hash*/
	}
}

/*---------------------------------------------------------------------------------------
*	__P__ - Procura uma equipa dado um nome.
*	* Formato de entrada: "P nome"
*--------------------------------------------------------------------------------------*/
void P(Hash_Equipa* ptr_HTE, int* Contador_Instrucoes){
	char nome_equipa[STR_LEN];
	
	getchar();
	scanf("%[^:\n]", nome_equipa);
	*Contador_Instrucoes += 1;

	if (!(hash_procura_Equipa(ptr_HTE, nome_equipa)))
		printf("%d Equipa inexistente.\n", *Contador_Instrucoes);

	else{
		Equipas* aux = hash_procura_Equipa(ptr_HTE, nome_equipa);
		printf("%d %s %d\n", *Contador_Instrucoes, aux -> nome, aux -> vitorias);
	}
}

/*---------------------------------------------------------------------------------------
*	__p__ - Procura um jogo com o nome dado.
*	* Formato de entrada: "P nome"
*--------------------------------------------------------------------------------------*/
void p(Hash_Jogo* ptr_HTJ, int* Contador_Instrucoes){
	char nome_jogo[STR_LEN];
	
	getchar();
	scanf("%[^:\n]", nome_jogo);
	*Contador_Instrucoes += 1;

	if (!(hash_procura_Jogo(ptr_HTJ, nome_jogo)))
		printf("%d Jogo inexistente.\n", *Contador_Instrucoes);

	else{
		Jogo* aux = hash_procura_Jogo(ptr_HTJ, nome_jogo);
		printf("%d %s %s %s %d %d\n", *Contador_Instrucoes, aux -> nome, aux -> equipa1, aux -> equipa2, aux -> pontuacao1, aux -> pontuacao2);
	}
}

/*---------------------------------------------------------------------------------------
*	__l__ - Lista todos os jogos introduzidos.
*	* Formato de entrada: "l"
*--------------------------------------------------------------------------------------*/
void l(Lista_Jogos* CJ, int* Contador_Instrucoes){
	Jogo* aux;
	*Contador_Instrucoes += 1;
	for (aux = CJ -> topo; aux != NULL; aux = aux -> proximo){
		printf("%d %s %s %s %d %d\n", *Contador_Instrucoes, aux -> nome, aux -> equipa1, aux -> equipa2, aux -> pontuacao1, aux -> pontuacao2);
	}
}

/*---------------------------------------------------------------------------------------
*	Funcao Auxiliar utilizada na funcao s: atualiza_pontuacoes.
*	Atualiza as pontuacoes do jogo escolhido na funcao s.
*--------------------------------------------------------------------------------------*/
void atualiza_pontuacoes(Jogo* aux_j, int pontuacao_nova1, int pontuacao_nova2){
	aux_j -> pontuacao1 = pontuacao_nova1;
	aux_j -> pontuacao2 = pontuacao_nova2;
}

/*---------------------------------------------------------------------------------------
*	Funcao Auxiliar utilizada na funcao s: retira_vitoria.
*	retira 1 vitoria a equipa passada como argumento.
*--------------------------------------------------------------------------------------*/
void retira_vitoria(Hash_Equipa* ptr_HTE, char* equipa){
	Equipas* aux_e;
	aux_e = hash_procura_Equipa(ptr_HTE, equipa);	/*encontra a equipa1 que corresponde ao jogo*/
	if (aux_e -> vitorias != 0)
		aux_e -> vitorias -= 1;		/*retira 1 vitoria*/
}

/*---------------------------------------------------------------------------------------
*	Funcao Auxiliar utilizada na funcao s: adiciona_vitoria.
*	adiciona 1 vitoria a equipa passada como argumento.
*--------------------------------------------------------------------------------------*/
void adiciona_vitoria(Hash_Equipa* ptr_HTE, char* equipa){
	Equipas* aux_e;
	aux_e = hash_procura_Equipa(ptr_HTE, equipa);	/*encontra a equipa2 que corresponde ao jogo*/
	aux_e -> vitorias += 1;		/*retira 1 vitoria*/
}

/*---------------------------------------------------------------------------------------
*	__s__ - Altera o score de um jogo dado o nome.
*	* Formato de entrada: "s nome:score1:score2"
*--------------------------------------------------------------------------------------*/
void s(Hash_Jogo* ptr_HTJ, Hash_Equipa* ptr_HTE, int* Contador_Instrucoes){
	Jogo* aux_j;
	char nome_jogo[STR_LEN];
	int pontuacao_nova1, pontuacao_nova2;

	getchar();
	scanf("%[^:\n]:%d:%d", nome_jogo, &pontuacao_nova1, &pontuacao_nova2);
	*Contador_Instrucoes += 1;

	aux_j = hash_procura_Jogo(ptr_HTJ, nome_jogo);
	if (aux_j == NULL){
		printf("%d Jogo inexistente.\n", *Contador_Instrucoes);
		return;
	}
	/*no caso de a pontuacao antiga da equipa1 ser maior que a da equipa2*/
	else if (aux_j -> pontuacao1 > aux_j -> pontuacao2){	
		if (pontuacao_nova1 > pontuacao_nova2){
			atualiza_pontuacoes(aux_j, pontuacao_nova1, pontuacao_nova2);
		}
		else if(pontuacao_nova1 < pontuacao_nova2){
			atualiza_pontuacoes(aux_j, pontuacao_nova1, pontuacao_nova2);
			retira_vitoria(ptr_HTE, aux_j -> equipa1);
			adiciona_vitoria(ptr_HTE, aux_j -> equipa2);
		}
		else {
			atualiza_pontuacoes(aux_j, pontuacao_nova1, pontuacao_nova2);
			retira_vitoria(ptr_HTE, aux_j -> equipa1);
		}
	}
	/*no caso de a pontuacao antiga da equipa2 ser maior que a da equipa1*/
	else if (aux_j -> pontuacao1 < aux_j -> pontuacao2){	
		if (pontuacao_nova1 < pontuacao_nova2){
			atualiza_pontuacoes(aux_j, pontuacao_nova1, pontuacao_nova2);
		}
		else if(pontuacao_nova1 > pontuacao_nova2){
			atualiza_pontuacoes(aux_j, pontuacao_nova1, pontuacao_nova2);
			adiciona_vitoria(ptr_HTE, aux_j -> equipa1);
			retira_vitoria(ptr_HTE, aux_j -> equipa2);
		}
		else {
			atualiza_pontuacoes(aux_j, pontuacao_nova1, pontuacao_nova2);
			retira_vitoria(ptr_HTE, aux_j -> equipa2);
		}
	}
	else {		/*no caso de a pontuacao antiga da equipa2 ser igual a da equipa1*/
		if (pontuacao_nova1 == pontuacao_nova2){
			atualiza_pontuacoes(aux_j, pontuacao_nova1, pontuacao_nova2);
		}
		else if (pontuacao_nova1 > pontuacao_nova2){
			atualiza_pontuacoes(aux_j, pontuacao_nova1, pontuacao_nova2);
			adiciona_vitoria(ptr_HTE, aux_j -> equipa1);
		}
		else {
			atualiza_pontuacoes(aux_j, pontuacao_nova1, pontuacao_nova2);
			adiciona_vitoria(ptr_HTE, aux_j -> equipa2);
		}
	}
}

/*---------------------------------------------------------------------------------------
*	Funcao Auxiliar utilizada na funcao g: compara_strings.
*	Adaptado do StackOverFlow
*--------------------------------------------------------------------------------------*/

int compara_strings(const void *str1, const void *str2){
    char *const *pp1 = str1;	/*converte um ponteiro void para um ponteiro char*/
    char *const *pp2 = str2;
    return strcmp(*pp1, *pp2);
}

/*---------------------------------------------------------------------------------------
*	__g__ - Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica.
*	* Formato de entrada: "g"
*--------------------------------------------------------------------------------------*/
void g(Lista_Equipas* CE, int* Contador_Instrucoes){
	Equipas* aux_e;
	int Maximo_Vitorias = 0, Contador_aux, Contador_prints, aux_comprimento;
	char** Lista_Equipas_Maiores;

	* Contador_Instrucoes += 1;

	if (CE -> topo == NULL)
		return;

	for(aux_e = CE -> topo; aux_e != NULL; aux_e = aux_e -> proximo){
		if (aux_e -> vitorias > Maximo_Vitorias)
			Maximo_Vitorias = aux_e -> vitorias;			/*descobre maximo*/
	}

	for(aux_e = CE -> topo, Contador_aux = 0; aux_e != NULL; aux_e = aux_e -> proximo){
		if (aux_e -> vitorias == Maximo_Vitorias)
			Contador_aux++;						/*conta o numero de elementos com vitoria maxima*/
	}

	Lista_Equipas_Maiores = can_fail_malloc(sizeof(char*) * Contador_aux);
	aux_comprimento = Contador_aux;

	for(aux_e = CE -> topo, Contador_aux = 0; Contador_aux < aux_comprimento; aux_e = aux_e -> proximo){
		if (aux_e -> vitorias == Maximo_Vitorias){
			Lista_Equipas_Maiores[Contador_aux] = can_fail_malloc(sizeof(char) * (strlen(aux_e -> nome) + 1));
			strcpy(Lista_Equipas_Maiores[Contador_aux], aux_e -> nome);
			Contador_aux++;
		}
	}

	qsort(Lista_Equipas_Maiores, Contador_aux, sizeof(char*), compara_strings);		/*ordena a lista*/
	printf("%d Melhores %d\n", *Contador_Instrucoes, Maximo_Vitorias);

	for (Contador_prints = 0; Contador_prints < Contador_aux; Contador_prints++){
		printf("%d * %s\n", *Contador_Instrucoes, Lista_Equipas_Maiores[Contador_prints]);
		free(Lista_Equipas_Maiores[Contador_prints]);
	}
	free(Lista_Equipas_Maiores);
}

/*---------------------------------------------------------------------------------------
*	Funcao Auxiliar utilizada na funcao r: apaga_lista_jogos.
*	retirado do powerpoint do prof Mikolas.
*--------------------------------------------------------------------------------------*/

void apaga_lista_jogos(Lista_Jogos *CJ, cabeca_JOGO *no_jogo){
	if (no_jogo -> ptrJOGO -> anterior == NULL){	/*no caso de ser o primeiro no da lista*/
		CJ -> topo = no_jogo -> ptrJOGO -> proximo;
	}
	else{
		no_jogo -> ptrJOGO -> anterior -> proximo = no_jogo -> ptrJOGO -> proximo;	/*o proximo do anterior e o proximo*/
	}
	if (no_jogo -> ptrJOGO -> proximo == NULL){		/*no caso de ser o ultimo no da lista*/
		CJ -> fim = no_jogo -> ptrJOGO -> anterior;
	}
	else {
		no_jogo -> ptrJOGO -> proximo -> anterior = no_jogo -> ptrJOGO -> anterior;	/*o anterior do proximo e o anterior*/
	}
	free(no_jogo -> ptrJOGO -> nome);
	free(no_jogo -> ptrJOGO -> equipa1);
	free(no_jogo -> ptrJOGO->equipa2);
	free(no_jogo -> ptrJOGO);
}

/*---------------------------------------------------------------------------------------
*	Funcao Auxiliar utilizada na funcao r: limpa_hash.
*
*--------------------------------------------------------------------------------------*/
void limpa_hash(Hash_Jogo* ptr_HTJ, cabeca_JOGO* no_jogo, int index){ 
	cabeca_JOGO *atual = ptr_HTJ -> gaveta_JOGO[index], *prox = ptr_HTJ -> gaveta_JOGO[index];

    if (atual != NULL && atual == no_jogo){ 	
    /*se for igual ao jogo, passa ao proximo e liberto o espaco do no do atual*/
        ptr_HTJ -> gaveta_JOGO[index] = atual -> proximo;   
        free(atual);              
        return; 
    }
    for (; atual != NULL && atual != no_jogo; atual = atual -> proximo)
    	prox = atual;

    prox -> proximo = atual -> proximo;	/*resolucao de um problema*/
    free(atual);
}

/*---------------------------------------------------------------------------------------
*	__r__ - Apaga um jogo dado um nome.
*	* Formato de entrada: "r nome"
*--------------------------------------------------------------------------------------*/
void r(Hash_Jogo* ptr_HTJ, Hash_Equipa* ptr_HTE, Lista_Jogos* CJ, int* Contador_Instrucoes){
	char nome_jogo[STR_LEN];
	int index;
	cabeca_JOGO* aux_no;
	Jogo* aux_j;

	getchar();
	scanf("%[^:\n]", nome_jogo);
	index = hash(nome_jogo);
	aux_no = ptr_HTJ -> gaveta_JOGO[index];
	*Contador_Instrucoes += 1;

	aux_j = hash_procura_Jogo(ptr_HTJ, nome_jogo);
	if(!(hash_procura_Jogo(ptr_HTJ, nome_jogo))){
		printf("%d Jogo inexistente.\n", *Contador_Instrucoes);
	}
	else{
		for(; aux_no != NULL; aux_no = aux_no -> proximo){
			if(strcmp(aux_no -> ptrJOGO -> nome, nome_jogo) == 0){
				if(aux_no -> ptrJOGO -> pontuacao1 > aux_no -> ptrJOGO -> pontuacao2){
					retira_vitoria(ptr_HTE, aux_j -> equipa1);	/*retira as vitorias*/
					apaga_lista_jogos(CJ, aux_no);	/*apaga a lista de jogos*/
					limpa_hash(ptr_HTJ, aux_no, index);	/*limpa a hash*/
					return;
				}
				else if(aux_no -> ptrJOGO -> pontuacao2 > aux_no -> ptrJOGO -> pontuacao1){
					retira_vitoria(ptr_HTE, aux_j -> equipa2);	/*retira as vitorias*/
					apaga_lista_jogos(CJ, aux_no);		/*apaga a lista de jogos*/
					limpa_hash(ptr_HTJ, aux_no, index);	/*limpa a hash*/
					return;
				}
				else{
					apaga_lista_jogos(CJ, aux_no);		/*apaga a lista de jogos*/
					limpa_hash(ptr_HTJ, aux_no, index);	/*limpa a hash*/
					return;
				}
			}
		}
	}
}
