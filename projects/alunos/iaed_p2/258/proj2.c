#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inclusao dos ficheiros jogo.h e equipa.h para que o programa saiba que funcoes e estruturas usar na funcao main, visto estarem noutros ficheiros .c e .h */
#include "equipa.h"
#include "jogo.h"
/* PRINCIPAL */
/* Funcao que seleciona o comando a executar */
int main()
{
	int c;
	int n;
	int num_comandos = 1;
	struct TodosJogos jogos;
	struct TodasEquipas equipas;
	for (n = 0; n < TODOS_JOGOS_ELEMENTOS_NUM; n++) {
		jogos.elementos[n] = NULL;
	}
	for (n = 0; n < TODAS_EQUIPAS_ELEMENTOS_NUM; n++) {
		equipas.elementos[n] = NULL;
	}
	equipas.num_equipas = 0; 
	equipas.vetor = NULL; /* Inicializa o vetor como sendo  nulo */
	jogos.num_jogos = 0;
	jogos.vetor = NULL; /* Inicializa o vetor como sendo  nulo */
	while (1)
	{ /* Ciclo criado para se poder efetuar varios comandos durante a execucao do programa */
		c = getchar();
		if (c == EOF)
		{
			return 0;
		}
		if (c == '\n' || c == ' ')
		{
			continue;
		}

		switch (c)
		{ /* Seleciona e executa o respetivo comando de acordo com os inputs */
		case 'a':
			adicionajogo(&jogos, &equipas, num_comandos);
			break;
		case 'A':
			adicionaequipa(&equipas, num_comandos);
			break;
		case 'l':
			listajogo(&jogos, num_comandos);
			break;
		case 'p':
			procurajogo(&jogos, num_comandos);
			break;
		case 'P':
			procuraequipa(&equipas, num_comandos);
			break;
		case 'r':
			apagajogo(&jogos, num_comandos);
			break;
		case 's':
			alterascore(&jogos, num_comandos);
			break;
		case 'g':
			encontravitoriosos(&equipas, num_comandos);
			break;
		case 'x': /* Termina o programa */
			return 0;
		}
		num_comandos += 1; /* Atualizacao do numero da linha */
	}
	
	for (n = 0; n < jogos.num_jogos; n++) {
		if (jogos.vetor[n] == NULL)
		{
			continue;
		}
		free(jogos.vetor[n]->nome);
		free(jogos.vetor[n]);
	}
	free(jogos.vetor); /* Liberta memoria dos vetores */
	
	for (n = 0; n < equipas.num_equipas; n++) {
		if (equipas.vetor[n] == NULL)
		{
			continue;
		}
		free(equipas.vetor[n]->nome);
		free(equipas.vetor[n]);
	}
	free(equipas.vetor); /* Liberta memoria dos vetores */
	
	return 0;
}
