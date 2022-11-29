#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sistema.h"


/*Funcao adicona jogo verifica em primeiro lugar se as equipas de facto existem e se o nome do jogo nao, posto isto verifica qual o score e caso nao seja empate incrementa
	uma vitoria a equipa vencedora presente na respetiva hash table */


void adiciona_jogo(Sistema *system,int cont_line){
	int score_1,score_2;
	Jogo *new_game;
	Team *t1,*t2;
	char nome_jogo[SIZE_STRING],equipa_1[SIZE_STRING],equipa_2[SIZE_STRING];
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome_jogo,equipa_1,equipa_2,&score_1,&score_2);
	t1=	encontra_t(system->tabela_teams,equipa_1);
	t2=encontra_t(system->tabela_teams,equipa_2);
	if (encontra(system->tabela_jogos,nome_jogo)!= NULL){
		printf("%d Jogo existente.\n",cont_line);
	}
	else if (t1 == NULL) printf("%d Equipa inexistente.\n",cont_line);
	else if (t2 == NULL) printf("%d Equipa inexistente.\n",cont_line);
	else {
		new_game = cria_jogo(nome_jogo,equipa_1,equipa_2,score_1,score_2);
		if (score_1>score_2){
			t1->numero_wins++;
			introduz_table(system->tabela_jogos,new_game);
			(system->lista) = add_last(system->lista,new_game);
		}
		else if (score_1<score_2){
			t2->numero_wins++;
			introduz_table(system->tabela_jogos,new_game);
			(system->lista) = add_last(system->lista,new_game);
		}
		else { 
			introduz_table(system->tabela_jogos,new_game);
			(system->lista) = add_last(system->lista,new_game);
		}

	}
		

}


/*Adiciona uma equipa a hash table de equipas verificando primeiro se essa equipa ja nao existe no sistema*/ 


void adiciona_equipa(Sistema *system,int cont_line){
	Team *new_team;
	char name_team[SIZE_STRING];
	scanf(" %[^\n]",name_team);
	if (encontra_t(system->tabela_teams,name_team)!=NULL){
		printf("%d Equipa existente.\n",cont_line);
		return;
	}
	else {
		new_team=cria_team(name_team);
		introduz_table_t(system->tabela_teams,new_team);
		return;
	} 
	
}

/* Caso a equipa exista no sistema retorna a no formato*/

void procura_equipa(Sistema *system,int cont_line){
	Team *t;
	char name_team[SIZE_STRING];
	scanf(" %[^\n]",name_team);
	t=encontra_t(system->tabela_teams,name_team);
	if (t==NULL) printf("%d Equipa inexistente.\n",cont_line);
	else printf("%d %s %d\n",cont_line,name_team,t->numero_wins);
	
}


/*Lista todos os jogos por ordem de insercao ou seja percorre a lista ligada do inicio para o fim, pois os jogos sao 
	inseridos nessa mesma lista em ultimo lugar por cada acao do comando 'a'*/


void lista_jogos(Sistema *system,int cont_line){
	print_lista(system->lista,cont_line);

}

/*Esta funcao procura um jogo determinado jogo pelo seu respetivo nome caso este exista*/


void procura_jogo(Sistema *system,int cont_line){
	Jogo *j;
	char nome_jogo[SIZE_STRING];
	scanf(" %[^\n]",nome_jogo);
	j=encontra(system->tabela_jogos,nome_jogo);
	if (j==NULL) printf("%d Jogo inexistente.\n",cont_line);
	else printf("%d %s %s %s %d %d\n",cont_line,nome_jogo,j->equipa_1,j->equipa_2,j->score_1,j->score_2);


}


/* Apaga um jogo do sistema dado um nome se este existir, caso ele de facto exista modifica a lista ligada previamente antes da sua remocao com o intuito de o ponteiro next desse jogo da lista ligada de jogos apontar para o jogo seguinte sem o eliminar,posto isto
	acerta o numero de wins de uma equipa de acordo com o resultado desse mesmo jogo e por fim, procede a sua eliminacao da hashtable e da lista*/


void apaga_jogo(Sistema *system,int cont_line){
	Jogo *j;
	char nome_jogo[SIZE_STRING];
	scanf(" %[^\n]",nome_jogo);
	j=encontra(system->tabela_jogos,nome_jogo);
	if (j==NULL) printf("%d Jogo inexistente.\n",cont_line);
	else {
		if (j->score_1>j->score_2){
			encontra_t(system->tabela_teams,j->equipa_1)->numero_wins--;
			(system->lista)=Modifica_next_jogo(system->lista,j->nome_jogo);
			Remove_table(system->tabela_jogos,j);
		}
		else if (j->score_2>j->score_1){
			encontra_t(system->tabela_teams,j->equipa_2)->numero_wins--;
			(system->lista)=Modifica_next_jogo(system->lista,j->nome_jogo);
			Remove_table(system->tabela_jogos,j);
		}
		else {
			(system->lista)=Modifica_next_jogo(system->lista,j->nome_jogo);
			Remove_table(system->tabela_jogos,j);
		}
	}
}


/*Esta funcao altera o score de um detrminado jogo analisando em primeiro lugar qual o score que estava antes da sua alteracao e e retira ou nao wins as equipas
	caso seja necessario em comparacao com o novo score */


void altera_jogo(Sistema *system,int cont_line){
	Jogo *aux;
	int score1,score2,estava_1,estava_2;
	char nome_jogo[SIZE_STRING];
	scanf(" %[^:\n]:%d:%d",nome_jogo,&score1,&score2);
	aux=encontra(system->tabela_jogos,nome_jogo);
	if (aux==NULL) printf("%d Jogo inexistente.\n",cont_line);
	else{
		estava_1=aux->score_1;
		estava_2=aux->score_2;
		aux->score_1=score1;
		aux->score_2=score2;
		if (score1>score2){
			if(estava_2>estava_1){
				encontra_t(system->tabela_teams,aux->equipa_1)->numero_wins++;
				encontra_t(system->tabela_teams,aux->equipa_2)->numero_wins--;
			}
			else if (estava_1==estava_2) encontra_t(system->tabela_teams,aux->equipa_1)->numero_wins++;

			else return;

		}
		else if (score1==score2){
			if (estava_2==estava_1) return;
			else if (estava_1>estava_2) encontra_t(system->tabela_teams,aux->equipa_1)->numero_wins--;
			else encontra_t(system->tabela_teams,aux->equipa_2)->numero_wins--;
		}
		else {
			if(estava_1>estava_2){
				encontra_t(system->tabela_teams,aux->equipa_1)->numero_wins--;
				encontra_t(system->tabela_teams,aux->equipa_2)->numero_wins++;
			}
			else if (estava_2==estava_1) encontra_t(system->tabela_teams,aux->equipa_2)->numero_wins++;
			else return;
		}
	}
}



/*Esta funcao encontra as equipas que ganharam mais jogos e lista-as por ordem lexicografica , em primeiro lugar encontra o numero maximo de jogos ganhos e posteriormente quais as equipas com esse mesmo numero 
	de jogos ganhos criando um vetor com os seus nomes , no final do programa e libertada a memoria desses dois vetores que tiveram um papel iimportante na funcao mergesorte para ordenar as equipas em causa */



void lista_teams(Sistema *system,int Equipa_existe,int cont_line){
	int mais_wins,i,size,l;
	char **pointer,**pointer_1;
	if (Equipa_existe==0) return;
	else{
		pointer=can_fail_malloc(sizeof(char*)*HASH_SIZE/20);
		for (i = 0; i < HASH_SIZE/20;i++) pointer[i]=can_fail_malloc(sizeof(char)*SIZE_STRING);
		mais_wins=ve_maior(system->tabela_teams);
		size=teams_maiores(system->tabela_teams,pointer,mais_wins);
		pointer_1=can_fail_malloc(sizeof(char*)*(size));
		merge_principal(pointer,pointer_1,0,size-1);
		printf("%d Melhores %d\n",cont_line,mais_wins);
		for(l=0;l<size;l++){
			printf("%d * %s\n",cont_line,pointer[l]);
		}
		
		for (i = 0; i < HASH_SIZE/20;i++) free(pointer[i]);
		free(pointer);
		free(pointer_1);

	}
}
	

/*linha de comandos com todas as suas funcionalidades */


int main(){
	int run=1,control,cont_line=0,Equipa_existe=0;
	Sistema *system;
	system = init_sistema();
	while (run){
		control = getchar();
		switch (control){
			case 'A':
				cont_line++;
				Equipa_existe=1;
				adiciona_equipa(system,cont_line);
				break;

			case 'a':
				cont_line ++;
				adiciona_jogo(system,cont_line);
				break;

			case 'P':
				cont_line++;
				procura_equipa(system,cont_line);
				break;

			case 'p':
				cont_line++;
				procura_jogo(system,cont_line);
				break; 

			case 'l':
				cont_line++;
				lista_jogos(system,cont_line);
				break;

			case 'r':
				cont_line++;
				apaga_jogo(system,cont_line);
				break;

			case 's':
				cont_line++;
				altera_jogo(system,cont_line);
				break;

			case 'g':
				cont_line++;
				lista_teams(system,Equipa_existe,cont_line);
				break;

			case 'x':
				run=0;
				break;

			default :
				run=0;
				break;

		}
		

		getchar();
		
	}
	
	liberta_sistema(system);		/*Acaba o porgrama entao toda a memoria em causa e libertada */
	return 0;
}



















