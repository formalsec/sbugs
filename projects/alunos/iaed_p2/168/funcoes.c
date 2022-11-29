#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "funcoes.h"

/* 'a': Funcao que adiciona um jogo a base de dados de jogos.*/
void adiciona_jogo(Jogo **jogos, int dim, Equipa **equipas, int conta_linhas)
{
	char nome[NOME_JOGO];
	char equipa1[NOME_EQUIPA];
	char equipa2[NOME_EQUIPA];
	int score1;
	int score2;


	Jogo *novo_jogo;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2,
			&score1, &score2);

	/*Se o jogo ja existir previamente, erro.*/
	if(HTprocura_jogo(nome, jogos, dim) != NULL)
		printf("%d Jogo existente.\n", conta_linhas);

	/*Se as equipas presentes nesse jogo nao existirem na 
	base de dados de equipas, erro.*/
	else if((HTprocura_equipa(equipa1, equipas, dim) == NULL) 
			|| (HTprocura_equipa(equipa2, equipas, dim) == NULL))
		printf("%d Equipa inexistente.\n", conta_linhas);

	/*Caso contrario, criar esse jogo, inseri-lo na base de dados.*/
	else
	{
		novo_jogo = novoJogo(nome, equipa1, equipa2, score1, score2, conta_linhas);
		HTinsere_jogo(novo_jogo, jogos, dim);
	
		/*Excpeto se for empate, somar uma vitoria a respetiva equipa.*/
		if(score1 > score2)
			soma_vitorias(HTprocura_equipa(equipa1, equipas, dim));
		
		else if(score2 > score1)
			soma_vitorias(HTprocura_equipa(equipa2, equipas, dim));
	}
}

/* 'l': Funcao que lista todos os jogos da base de dados, pela ordem 
em que foram introduzidos na mesma.*/
void lista_jogos(Jogo **jogos, int dim, int conta_linhas)
{
	HTlista_jogos(jogos, dim, conta_linhas);
}

/* 'p': Funcao que procura um jogo na base de dados de jogos.*/
void procura_jogo(Jogo **jogos, int dim, int conta_linhas)
{
	char nome[NOME_JOGO];
	scanf(" %[^:\n]", nome);

	/*Se o jogo existir na base de dados, dar print ao mesmo.*/
	if(HTprocura_jogo(nome, jogos, dim) != NULL)
		printJogo(HTprocura_jogo(nome, jogos, dim), conta_linhas);
	
	/*Caso contrario, erro.*/
	else
		printf("%d Jogo inexistente.\n", conta_linhas);
}

/* 'r': Funcao que apaga um jogo da base de dados.*/
void apaga_jogo(Jogo **jogos,  Equipa **equipas, int dim, int conta_linhas)
{
	Jogo *jogo;
	Equipa *equipa1;
	Equipa *equipa2;
	char nome[NOME_JOGO];
	scanf(" %[^:\n]", nome);

	/*Se o jogo existir na base de dados, remover o mesmo.*/
	if(HTprocura_jogo(nome, jogos, dim) != NULL)
	{
		jogo = HTprocura_jogo(nome, jogos, dim);
		equipa1 = HTprocura_equipa(jogo->equipa1, equipas, dim);
		equipa2 = HTprocura_equipa(jogo->equipa2, equipas, dim);

		/*Excepto se for empate, subtrair a vitoria da equipa
		respetiva desse jogo.*/
		if(jogo->score_equipa1 > jogo->score_equipa2)
			subtrai_vitorias(equipa1);

		else if(jogo->score_equipa2 > jogo->score_equipa1)
			subtrai_vitorias(equipa2);

		HTremove_jogo(jogo, jogos, dim);
	}

	/*Caso contrario, erro.*/
	else
		printf("%d Jogo inexistente.\n", conta_linhas);
}

/* 's': Funcao que altera o score de um jogo.*/
void altera_score(Jogo **jogos, Equipa **equipas, int dim, int conta_linhas)
{
	Jogo *jogo;
	Equipa *equipa1;
	Equipa *equipa2;
	char nome[NOME_JOGO];
	int score1_novo, score2_novo;
	scanf(" %[^:\n]:%d:%d", nome, &score1_novo, &score2_novo);

	/*Se a equipa existir, alterar o score da mesma.*/
	if(HTprocura_jogo(nome, jogos, dim) != NULL)
	{
		jogo = HTprocura_jogo(nome, jogos, dim);
		equipa1 = HTprocura_equipa(jogo->equipa1, equipas, dim);
		equipa2 = HTprocura_equipa(jogo->equipa2, equipas, dim);

		/*Excepto em caso de empate, remover a vitoria da equipa
		respetiva, de acordo com o score 'antigo'.*/
		if(jogo->score_equipa1 > jogo->score_equipa2)
			subtrai_vitorias(equipa1);

		else if(jogo->score_equipa2 > jogo->score_equipa1)
			subtrai_vitorias(equipa2);

		alteraScore(jogo, score1_novo, score2_novo);

		/*Excepto em caso de empate, adicionar uma vitoria a equipa
		respetiva, de acordo com o score 'novo'.*/
		if (score1_novo > score2_novo)
			soma_vitorias(equipa1);

		else if(score2_novo > score1_novo)
			soma_vitorias(equipa2);
	}

	/*Caso contrario, erro.*/
	else
		printf("%d Jogo inexistente.\n", conta_linhas);
}

/* 'A': Funcao que adiciona uma equipa a base de dados de equipas.*/
void adiciona_equipa(Equipa **equipas, int dim, int conta_linhas)
{
	char nome[NOME_EQUIPA];

	Equipa* nova_equipa;

	scanf(" %[^:\n]", nome);

	/*Se a equipa ja existir na base de dados, erro.*/
	if(HTprocura_equipa(nome, equipas, dim) != NULL)
		printf("%d Equipa existente.\n", conta_linhas);

	/*Caso contrario, cria e adiciona a equipa a base de dados.*/
	else
	{
		nova_equipa = novaEquipa(nome);
		HTinsere_equipa(nova_equipa, equipas, dim);
	}
}

/* 'P': Funcao que procura uma equipa na base de dados de equipas.*/
void procura_equipa(Equipa **equipas, int dim, int conta_linhas)
{
	char nome[NOME_EQUIPA];
	scanf(" %[^:\n]", nome);

	/*Se a equipa existir na base de dados de equipas, print da mesma.*/
	if(HTprocura_equipa(nome, equipas, dim) != NULL)
		printEquipa(HTprocura_equipa(nome, equipas, dim), conta_linhas);

	/*Caso contrario, erro.*/
	else
		printf("%d Equipa inexistente.\n", conta_linhas);
}

/* 'g': Funcao que lista o(s) jogo(s) com maior numero de vitorias,
por ordem lexicografica.*/
void encontra_vencedores(Equipa **equipas, int dim, int conta_linhas)
{
	HTencontra_mais_vitorias(equipas, dim, conta_linhas);
}

