#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "estrutura.h"

/*
Funcao que adiciona jogos a hash table e a lista ligada se nao 
houver nenhum erro
*/
void cmd_a(jogo * heads_jogos[], equipa * heads_equipas[], int n_linha, lista_jogo * jogos_ordenados){
	char nome[MAX_NOME], equipa1[MAX_NOME], equipa2[MAX_NOME];
	jogo * jogo_aux;
	equipa * aux1, * aux2;
	int golos1, golos2;
	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2,
	&golos1, &golos2);
	if(procura_j(heads_jogos, nome)){
		printf("%d Jogo existente.\n", n_linha);
	}
	else{
		if((aux1 = procura_e(heads_equipas, equipa1)) &&
		(aux2 = procura_e(heads_equipas, equipa2))){
			/*adiciona na hash table*/
			jogo_aux = adi_no(heads_jogos, nome, aux1, aux2, golos1, golos2);
			/*adiciona na lista*/
			adiciona_fim(jogos_ordenados, jogo_aux);
			/*aumenta a vitoria da equipa vencedora*/
			if(golos1 > golos2)
				aux1 -> vitoria += 1;
			else if(golos2 > golos1)
				aux2 -> vitoria += 1;
		}
		else{
			printf("%d Equipa inexistente.\n", n_linha);
		}
	}
}

/*
Funcao que adiciona equipas a hash table se nao 
houver nenhum erro
*/
void cmd_A(equipa * heads_equipas[], int n_linha){
	char nome[MAX_NOME];
	equipa * aux;
	scanf("%[^:\n]", nome);
	aux = procura_e(heads_equipas, nome);
	if(aux){
		printf("%d Equipa existente.\n", n_linha);
	}
	else{
		adi_eq(heads_equipas, nome);
	}
}

/*
Funcao que lista as equipas por ordem de insercao usando a lista ligada
*/
void cmd_l(lista_jogo * jogos_ordenados, int n_linha){
	jogo_l * aux = jogos_ordenados -> head;
	/*vai percorrendo a lista e dando print dos jogos*/
	while(aux){
		printf("%d %s %s %s %d %d\n", n_linha,aux -> jogo_lista -> nome,
		aux -> jogo_lista -> equipa1 -> nome, 
		aux -> jogo_lista -> equipa2 -> nome, aux -> jogo_lista -> golos1,
		aux -> jogo_lista -> golos2);
		aux = aux -> next;
	}
}

/*
Funcao que faz print das carateristicas do jogo pedido
*/
void cmd_p(jogo * heads_jogos[], int n_linha){
	char nome[MAX_NOME];
	jogo * aux;
	scanf("%[^:\n]", nome);
	/*vai buscar o ponteiro para o jogo*/
	aux = procura_j(heads_jogos, nome);
	if(aux)
		printf("%d %s %s %s %d %d\n", n_linha,aux -> nome,
		aux -> equipa1 -> nome, aux -> equipa2 -> nome, aux -> golos1,
		aux -> golos2);
	else
		printf("%d Jogo inexistente.\n", n_linha);
}

/*
Funcao que faz print das carateristicas da equipa pedida
*/
void cmd_P(equipa * heads_equipas[], int n_linha){
	char nome[MAX_NOME];
	equipa * aux;
	scanf("%[^:\n]", nome);
	aux = procura_e(heads_equipas, nome);
	/*vai buscar o ponteiro para a equipa*/
	if(aux)
		printf("%d %s %d\n", n_linha,aux -> nome,
		aux -> vitoria);
	else
		printf("%d Equipa inexistente.\n", n_linha);
}

/*
Funcao que remove um jogo a hash table e a lista ligada
*/
void cmd_r(jogo * heads_jogos[], lista_jogo * jogos_ordenados, int n_linha){
	char nome[MAX_NOME];
	jogo * aux;
	scanf("%[^:\n]", nome);
	/*elimina na lista se houver e ao mesmo tempo devolve se houver o ponteiro
	do jogo a eliminar*/
	aux = elimina_jo(jogos_ordenados, nome);
	if(aux){
		/*reduz a vitoria da equipa que tinha vencido*/
		if(aux -> golos1 > aux -> golos2){
			aux -> equipa1 -> vitoria -= 1;
		}
		else if(aux -> golos2 > aux -> golos1)
			aux -> equipa2 -> vitoria -= 1;
		/*remove na hash table*/
		rem_no(heads_jogos, nome);
	} else
		printf("%d Jogo inexistente.\n", n_linha);
}

/*
Funcao que altera o resultado de um jogo
*/
void cmd_s(jogo * heads_jogos[], int n_linha){
	char nome[MAX_NOME];
	int golos1, golos2;
	jogo * aux;
	scanf("%[^:\n]:%d:%d", nome, &golos1, &golos2);
	/*encontra a equipa*/
	aux = procura_j(heads_jogos, nome);
	if(aux){
		/*reduz a vitoria da equipa que tinha vencido*/
		if(aux -> golos1 > aux -> golos2)
			aux -> equipa1 -> vitoria -= 1;
		else if(aux -> golos2 > aux -> golos1)
			aux -> equipa2 -> vitoria -= 1;
		aux -> golos1 = golos1;
		aux -> golos2 = golos2;
		/*atualiza as vitorias*/
		if(golos1 > golos2)
			aux -> equipa1 -> vitoria += 1;
		else if(golos2 > golos1)
			aux -> equipa2 -> vitoria += 1;
		
	} else
		printf("%d Jogo inexistente.\n", n_linha);
}

/*
Funcao que faz print das equipas com mais vitorias por ordem alfabetica
*/
void cmd_g(equipa * heads_equipas[], int n_linha){
	int max_vitoria = -1, i;
	equipa * aux;
	equipa_l * aux_2;
	lista_equipa * equipas_ordenadas = NULL;
	/*poe no max_vitoria o maximo de vitorias*/
	for(i = 0; i < M_jogos; i++){
		aux = heads_equipas[i];
		while(aux){
			if(aux -> vitoria > max_vitoria)
				max_vitoria = aux -> vitoria;
			aux = aux -> next;
		} 
	}
	/*se ha equipas*/
	if(max_vitoria >= 0){
		equipas_ordenadas = inic_lista_e();
		/*vai pondo as equipas na lista na posicao certa para dar print*/
		for(i = 0; i < M_jogos; i++){
			aux = heads_equipas[i];
			while(aux){
				if((aux -> vitoria) == max_vitoria)
					adiciona_lex(equipas_ordenadas, aux);
				aux = aux -> next;
			} 
		}
		printf("%d Melhores %d\n", n_linha, max_vitoria);
		/*da print das equipas*/
		for(aux_2 = equipas_ordenadas -> head; aux_2 ; aux_2 = aux_2 -> next){
			printf("%d * %s\n", n_linha, aux_2 -> equipa_lista -> nome);
		}	
		free_lista_e(equipas_ordenadas);
	}
}
