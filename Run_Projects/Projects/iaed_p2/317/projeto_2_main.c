#include "jogos.h"

#define MAX_S_LEN 1024

/*-----------------------funcoes auxiliares-----------------------*/

/*da free as hashtables de jogos e de equipas*/
void free_hashs(EHnode *Ehash,JHnode *Jhash) {
	int i;
	EHnode EHnode_aux, EHtmp;
	JHnode JHnode_aux, JHtmp;
	/* percorrer as heads de cada hashtable*/
	for (i = 0; i < HASH_M; i++){
		/*percorrer a lista ligada que comeca em cada head*/
		for(EHnode_aux = Ehash[i]; EHnode_aux != NULL; ){
			EHtmp = EHnode_aux -> next;
			free_equipa(EHnode_aux -> equipa);
			free(EHnode_aux);
			EHnode_aux = EHtmp;
		}
		for(JHnode_aux = Jhash[i]; JHnode_aux != NULL; ){
			JHtmp = JHnode_aux -> next;
			free_jogo(JHnode_aux -> jogo);
			free(JHnode_aux);
			JHnode_aux = JHtmp;
		}
	}
	free(Ehash);
	free(Jhash);
}

void inicializa_total(EHnode *Ehash, Equipas_sistema *equipas_sis, JHnode *Jhash, Jogos_sistema *jogos_sis){
	inicializa_equipas_sistema(equipas_sis);
	inicializa_equipas_hash(Ehash);
    inicializa_jogos_sistema(jogos_sis);
    inicializa_jogos_hash(Jhash);
}

/*da free a hastable de equipas e de jogos e as listas de jogos e de equipas*/
void free_total(EHnode *Ehash, Equipas_sistema *equipas_sis, JHnode *Jhash, Jogos_sistema *jogos_sis){
	free_jogos_sis(jogos_sis);
	free_equipas_sis(equipas_sis);
	free_hashs(Ehash, Jhash);
}

void swap(Equipa **equipas, int i, int j){
	Equipa *equipa = equipas[i];
	equipas[i] = equipas[j];
	equipas[j] = equipa;
}

int partition (Equipa **equipas, int l, int r){
	int i = (l - 1), j = r;
	Equipa *equipa = equipas[r];
	while (i < j) {
		while (strcmp(equipas[++i] -> nome, equipa -> nome) < 0);
		while (strcmp(equipa -> nome,equipas[--j] -> nome) < 0)
			if (j == l)
				break;
		if (i < j)
			swap(equipas, i, j);
	}
	swap(equipas, i, r);
	return i;
}

void quicksort(Equipa **equipas, int l, int r){
	int i;
	if (r <= l)
		return;
	i = partition(equipas,l,r);
	quicksort(equipas, l, i-1);
	quicksort(equipas, i+1, r);
}

/*-----------------------funcoes principais-----------------------*/

void f_a(int NL, Jogos_sistema *jogos_sis, JHnode *Jhash, EHnode *Ehash) {
	Jogo *jogo;
	Equipa *equipa1, *equipa2;
	char nome[MAX_S_LEN], equipa1_nome[MAX_S_LEN], equipa2_nome[MAX_S_LEN];
	int score1, score2;

	scanf("%[^:]:%[^:]:%[^:]:%d:%d\n", nome, equipa1_nome, equipa2_nome, &score1, &score2);

	/*procura o jogo*/
	jogo = JHsearch(Jhash, nome);

	/*no caso de ja existir um jogo com esse nome no sistema*/
	if (jogo != NULL){
		printf("%d Jogo existente.\n", NL);
		return;
	}

	/*procurar ambas as equipas*/
	equipa1 = EHsearch(Ehash, equipa1_nome);
	equipa2 = EHsearch(Ehash, equipa2_nome);

	/*no caso de uma das equipas ou ambas nao existirem no sistema*/
	if (!(equipa1 != NULL && equipa2 != NULL)){
		printf("%d Equipa inexistente.\n", NL);
		return;
	}

	/*preparar o jogo a ser adicionado*/
    jogo = malloc(sizeof(Jogo));
	jogo -> nome = malloc(sizeof(char) * (strlen(nome) + 1));
	strcpy(jogo -> nome, nome);
	jogo -> e1 = equipa1;
	jogo -> e2 = equipa2;
	jogo -> s1 = score1;
	jogo -> s2 = score2;

	/* identificar e adicionar uma vitoria a quem ganhou o jogo atualizando equipas_sis*/
	if (score1 > score2)
		jogo -> e1 -> jogos_ganhos++;
	else if (score1 < score2)
		jogo -> e2 -> jogos_ganhos++; 

	JSinsert(jogos_sis, jogo); /*colocar o jogo na lista do sistema*/
	JHinsert(Jhash, jogo); /*colocar o jogo na hashtable de jogos*/
}	

void f_l(int NL, Jogos_sistema *jogos_sis) {
	JHnode node;
	/*percorrer a lista de jogos dando print*/
	for(node = jogos_sis -> head; node != NULL; node = node -> next)
			printf("%d %s %s %s %d %d\n", NL, node -> jogo -> nome, node -> jogo -> e1 -> nome,
				node -> jogo -> e2 -> nome, node -> jogo -> s1, node -> jogo -> s2);
}

void f_p(int NL, JHnode *Jhash){
	char nome[MAX_S_LEN];
	Jogo *jogo;

	scanf("%[^\n]\n", nome);

	/*procura o jogo*/
	jogo = JHsearch(Jhash, nome);

	if(jogo != NULL){
		printf("%d %s %s %s %d %d\n", NL, jogo -> nome, jogo -> e1 -> nome,
			jogo -> e2 -> nome, jogo -> s1, jogo -> s2);
		return;
	}
	/*no caso de nao existir nenhum jogo com esse nome no sistema*/
	printf("%d Jogo inexistente.\n", NL);
}

void f_r(int NL, JHnode *Jhash, Jogos_sistema *jogos_sis){
	Jogo *jogo;
	char nome[MAX_S_LEN];

	scanf("%[^\n]\n", nome);
	/*procura o jogo*/
	jogo = JHsearch(Jhash, nome);

	if(jogo != NULL){
		/*atualiza o numero de vitorias e equipas_sis*/
		if (jogo -> s1 > jogo -> s2)
			jogo -> e1 -> jogos_ganhos--;
		else if (jogo -> s1 < jogo -> s2)
			jogo -> e2 -> jogos_ganhos--; 

		JSdelete(jogos_sis, nome); /*apaga o jogo da lista de jogos do sistema*/
		JHdelete(Jhash, nome); /*apaga o jogo da hashtable de jogos*/
		return;
	}
	/*no caso de nao existir nenhum jogo com esse nome no sistema*/
	printf("%d Jogo inexistente.\n", NL);
}

void f_s(int NL, JHnode *Jhash){
	Jogo *jogo;
	char nome[MAX_S_LEN];
	int score1,score2;

	scanf("%[^:]:%d:%d\n", nome, &score1, &score2);
	/*procura o jogo*/
	jogo = JHsearch(Jhash, nome);

	if(jogo != NULL){
		/*atualiza o numero de vitorias*/
		if (jogo -> s1 > jogo -> s2)
			jogo -> e1 -> jogos_ganhos--;
		else if (jogo -> s1 < jogo -> s2)
			jogo -> e2 -> jogos_ganhos--; 
		if (score1 > score2)
			jogo -> e1 -> jogos_ganhos++;
		else if (score1 < score2)
			jogo -> e2 -> jogos_ganhos++;
		jogo -> s1 = score1;
		jogo -> s2 = score2;
		return;
	}
	/*no caso de nao existir nenhum jogo com esse nome no sistema*/
	printf("%d Jogo inexistente.\n", NL);
}

void f_A(int NL, EHnode *Ehash, Equipas_sistema *equipas_sis){
	Equipa *equipa;
	char nome[MAX_S_LEN];

	scanf("%[^\n]\n", nome);

	/*no caso de ja existir uma equipa com esse nome no sistema*/
	if(EHsearch(Ehash, nome) != NULL){ 
	    printf("%d Equipa existente.\n", NL);
		return;
	}
	/*preparar a equipa a ser adicionada*/
	equipa = malloc(sizeof(Equipa));
    equipa -> nome = malloc(sizeof(char) * (strlen(nome) + 1));
	strcpy(equipa -> nome, nome);
    equipa -> jogos_ganhos = 0;

    EHinsert(Ehash, equipa);  /*colocar a equipa na hashtable de equipas*/
    ESinsert(equipas_sis -> equipas, equipa); /*colocar a equipa no sistema*/
    if(equipa -> jogos_ganhos == equipas_sis -> n_max_vitorias)
    	equipas_sis -> n_equipas_max++;

}

void f_P(int NL, EHnode *Ehash){
	Equipa *equipa;
	char nome[MAX_S_LEN];

	scanf("%[^\n]\n", nome);

	equipa = EHsearch(Ehash, nome);

	if(equipa != NULL){
		printf("%d %s %d\n", NL, equipa -> nome, equipa -> jogos_ganhos);
		return;
	}
	/*no caso de nao existir nenhuma equipa com esse nome no sistema*/
	printf("%d Equipa inexistente.\n", NL); 
}

void f_g(int NL, Equipas_sistema *equipas_sis){
	int i = 0, m = EQUI_SIS_M;
	Equipa **equipas_ord;
	EHnode node;
	if(equipas_sis -> n_equipas_max == 0) /*se ainda n tiverem sido introduzidas equipas*/
		return;
	/*inicializar uma lista para colocar as equipas com maior numero de vitorias*/
	equipas_ord = malloc(sizeof(Equipa *) * EQUI_SIS_M);
	equipas_sis -> n_max_vitorias = 0;
	equipas_sis -> n_equipas_max = 0;

	/*percorrer a lista de equipas do sistema*/
	for(node = *(equipas_sis -> equipas); node != NULL; node = node -> next){
		/*encontrar o maior numero de vitorias e o numero de equipas com o maior numero de vitorias*/
		if(node -> equipa -> jogos_ganhos > equipas_sis -> n_max_vitorias){
			equipas_sis -> n_max_vitorias = node -> equipa -> jogos_ganhos;
			equipas_sis -> n_equipas_max = 0;
			i=0;
		}
		/*se a equipa tem o maior numero de vitorias atual coloca-la na lista
		e aumentar o numero de equipas com mais vitorias*/
		if(node -> equipa -> jogos_ganhos == equipas_sis -> n_max_vitorias){
			equipas_sis -> n_equipas_max++;
			/*verificar se o numeros de equipas a colocar excede a memoria alocada para a lista originalmente*/
			if (equipas_sis -> n_equipas_max >= m){
				m += EQUI_SIS_M;
				equipas_ord = realloc(equipas_ord, sizeof(Equipa *) * m); /*aumentar a memoria alocada para a lista caso necessario*/
			}
			equipas_ord[i++] = node -> equipa;
		}
	}

	/*dar sort a lista de equipas criada por ordem lexicografica*/
	quicksort(equipas_ord, 0 ,equipas_sis -> n_equipas_max-1);

	/*percorrer a lista ordenada dand print*/
	printf("%d Melhores %d\n", NL, equipas_sis -> n_max_vitorias);
	for(i = 0; i < equipas_sis -> n_equipas_max; i++){
		printf("%d * %s\n", NL, equipas_ord[i] ->nome);
	}
	free(equipas_ord);
}

int main(){
    int NL = 1;
    char comando;
    EHnode *Ehash = malloc(HASH_M * sizeof(EHnode));
    JHnode *Jhash = malloc(HASH_M * sizeof(JHnode));
    Jogos_sistema *jogos_sis = malloc(sizeof(struct jogos_sistema));
    Equipas_sistema *equipas_sis = malloc(sizeof(struct equipas_sistema));
    inicializa_total(Ehash,equipas_sis,Jhash,jogos_sis);
	while(1){
		comando = getchar();
		getchar();
		switch (comando){
			case 'a':
				f_a(NL, jogos_sis, Jhash, Ehash);
				break;
			case 'l':
				f_l(NL, jogos_sis);
				break;
			case 'p':
				f_p(NL, Jhash);
				break;
			case 'r':
				f_r(NL, Jhash, jogos_sis);
				break;
			case 's':
				f_s(NL, Jhash);
				break;
			case 'A':
				f_A(NL, Ehash, equipas_sis);
				break;
			case 'P':
				f_P(NL, Ehash);
				break;
			case 'g':
				f_g(NL, equipas_sis);
				break;
			case 'x':
				free_total(Ehash, equipas_sis, Jhash, jogos_sis);
				return 0;
		}
		NL++; /*incrementa o contador de linhas de input*/
	}
}