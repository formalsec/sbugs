#include "comandos.h"
#include "tabelas_disp.h"
#include "estruturas.h"

/*Numero maximo de carateres de uma string para o nome
tanto de uma equipa ou de um jogo*/
#define MAX_CHAR 1024



/*Comando que adiciona um novo jogo ao sistema*/

void comando_a(ST_jg Tj,ST_eq Te,Jogo * Jogos,int num_linhas)
{	
	char nome[MAX_CHAR], n_equipa1[MAX_CHAR],n_equipa2[MAX_CHAR];
	unsigned int score1,score2;
	Equipa e1,e2;
	Jogo novo_jogo;


	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%u:%u",nome,n_equipa1,n_equipa2,
		&score1,&score2);

	
	/*Verifica se o jogo existe na hash table*/
	if(ST_jg_search(Tj,nome)!=NULL)
	{
		printf("%u Jogo existente.\n",num_linhas);
	}
	
	/*Verifica se as equipas cujos nomes foram dados como 
	input existem na hash table*/
	else if((ST_eq_search(Te,n_equipa1)==NULL)||
		(ST_eq_search(Te,n_equipa2)==NULL))
	{
		printf("%u Equipa inexistente.\n",num_linhas);
	}
	else
	{
		e1=ST_eq_search(Te,n_equipa1);
		e2=ST_eq_search(Te,n_equipa2);

		/*Altera o numero de jogos ganhos das equipas*/
		adiciona_scores(e1,e2,score1,score2);

		/*Cria o novo jogo, alocando a memoria necessaria*/
		novo_jogo=new_Jogo(nome,e1,e2,score1,score2);
		/*Adiciona o jogo ao vetor Jogos*/
		Jogos[Tj->N]=novo_jogo;
		/*Adiciona o jogo ao sistema*/
		ST_jg_insert(Tj,novo_jogo);
		
	}
}




/*Comando que adiciona uma equipa ao sistema*/

void comando_A(ST_eq Te,int num_linhas)
{
	char nome[MAX_CHAR];
	Equipa nova_equipa;
	

	scanf("%[^:\n]",nome);

	/*Verifica se a equipa ja existe no sistema*/
	if(ST_eq_search(Te,nome)!=NULL)
	{
		printf("%u Equipa existente.\n",num_linhas);
	}
	else
	{
		/*Aloca o espaco para a nova equipa*/
		nova_equipa=new_Equipa(nome);
		/*Adicona a equipa ao sistema*/
		ST_eq_insert(Te,nova_equipa);
		
		
	}
}



/*Comando que lista todos os jogos introduzidos, 
pela ordem que foram introduzidos*/

void comando_l(ST_jg Tj,Jogo* Jogos, int num_linhas)
{
	long j;
	Jogo jogo;
	/*Verifica se existem jogos no sistema*/
	if(Tj->N>0)
	{
		/*Imprime os jogos*/
		for(j=0;j<Tj->N;j++)
		{
			jogo=Jogos[j];
			print_Jogo(jogo,num_linhas);
		}
	}
	else
		return;
	
}



/*Comando que procura um jogo no sistema.
Se o encontrar imprime-o*/
void comando_p(ST_jg Tj,int num_linhas)
{
	char nome[MAX_CHAR];
	Jogo jogo;
	scanf("%[^:\n]",nome);

	jogo=ST_jg_search(Tj,nome);
	
	if(jogo!=NULL)
	{
		print_Jogo(jogo,num_linhas);
	}
	else
	{
		printf("%u Jogo inexistente.\n",num_linhas);
	}

}


/*Comando que procura uma equipa no sistema.
Se a encontrar imprime-a*/
void comando_P(ST_eq Te,int num_linhas)
{
	char nome[MAX_CHAR];
	Equipa equipa;
	scanf("%[^:\n]",nome);
	
	equipa=ST_eq_search(Te,nome);

	if(equipa!=NULL)
	{
		print_Equipa(equipa,num_linhas);
		
	}
	else
	{
		printf("%u Equipa inexistente.\n",num_linhas);
		
	}
}



/*Comando que altera o score de um jogo, dado o nome*/
void comando_s(ST_jg Tj,ST_eq Te, int num_linhas)
{
	char nome[MAX_CHAR];
	unsigned int s1,s2;
	Jogo jogo;

	scanf("%[^:\n]:%u:%u",nome,&s1,&s2);
	jogo=ST_jg_search(Tj,nome);
	
	
	if(jogo!=NULL)
	{
		altera_scores(Te,jogo,s1,s2);
	}
	else
	{
		printf("%u Jogo inexistente.\n",num_linhas);
		
	}

}


/*Comando que apaga um jogo, dado o nome*/
void comando_r(ST_jg Tj, ST_eq Te, Jogo *Jogos, int  num_linhas)
{
	char nome[MAX_CHAR];
	Jogo jogo;
	long i,j;

	scanf("%[^:\n]",nome);
	jogo=ST_jg_search(Tj,nome);
	
	if (jogo!=NULL)
	{
		/*Percorre o vetor Jogos ate encontrar o jogo 
		a ser eliminado*/
		for(i=0;i<Tj->N;i++)
		{
			if(jogo==Jogos[i])
				break;
		}
		
		/*Reorganiza o vetor, visto que um dos jogos foi eliminado*/
		for(j=i;j<Tj->N-1;j++)
		{
			Jogos[j]=Jogos[j+1];
		}
		
		/*Altera os jogos ganhos das equipas relativas ao jogo*/
		elimina_scores(Te,jogo);
		/*Elimina o jogo do sistema*/
		ST_jg_delete(Tj,nome);
		
	}
	else
	{
		printf("%u Jogo inexistente.\n",num_linhas);
		
	}

	
}


void comando_g(ST_eq Te,int num_linhas)
{
	/*Guarda o numero maximo de jogos ganhos*/
	unsigned int J_Ganhos_max=0;
	long i,j=0;
	
	long *indice_equipas;
	char ** nomes_equipas;

	/*Caso nao existam equipas no sistema*/
	if(Te->N==0)
	{
		return;
	}
	
	/*Vetor que contem os indices da tabela de equipas,
	cujas equipas tem o numero maximo de jogos ganhos*/
	indice_equipas=malloc(sizeof(long)*(Te->N));
	
	/*Percorre a tabela de equipas*/
	for(i=0;i<Te->M;i++)
	{
		if(Te->st[i]!=NULL)
		{
			/*Se existir uma equipa com mais jogos ganhos do que 
			os da variavel que guarda o numero maximo,
			entao esse numero e atualizado*/
			if(Te->st[i]->jogos_ganhos > J_Ganhos_max)
			{
				J_Ganhos_max=Te->st[i]->jogos_ganhos;
				j=0;
				indice_equipas[j]=i;
				j++;
			
			}
			/*Se a equipa tiver o numero maximo de jogos ganhos,
			adiciona o seu indice na tabela ao vetor*/
			else if(Te->st[i]->jogos_ganhos==J_Ganhos_max)
			{
				indice_equipas[j]=i;
				j++;
			
			}
		}
	}
	
	/*Vetor que guarda os nomes das equipas que tem o maior 
	numero de jogos ganhos*/
	nomes_equipas=malloc(sizeof(char*)*j);

	
	for(i=0;i<j;i++)
	{
		/*Coloca os nomes das equipas com mais jogos 
		ganhos em "nomes_equipas"*/
		nomes_equipas[i]=strdup(Te->st[indice_equipas[i]]->nome);
	}

	/*Organiza os nomes das equipas por ordem lexicografica*/
	qsort(nomes_equipas,j,sizeof(char*),comparador);

	
	/*Imprime os nomes das equipas como pedido no enunciado*/
	printf("%u Melhores %d\n",num_linhas,J_Ganhos_max);
	
	for(i=0;i<j;i++)
	{
		printf("%u * %s\n",num_linhas,nomes_equipas[i]);
	}

	
	/*Liberta o espaco ocupado pelos vetors "nomes_equipas" 
	e "indice_equipas"*/
	for(i=0;i<j;i++)
	{
		free(nomes_equipas[i]);
	}

	free(nomes_equipas);
	
	free(indice_equipas);

}




/*Altera o numero de jogos ganhos de uma equipa, consoante 
os scores dados como input.Funcao utilizada no "comando_a"*/
void adiciona_scores(Equipa e1, Equipa e2, unsigned int s1, unsigned int s2)
{
	/*Averigua a equipa vencedora e incrementa o seu numero de jogos ganhos*/
	if(s1<s2)
		{
			e2->jogos_ganhos++;
		}
		else if(s2<s1)
		{
			e1->jogos_ganhos++;
		}
}


/*Altera o numero de jogos ganhos de duas equipas, consoante os 
scores dados como input.Funcao utilizada no "comando_s"*/
void altera_scores(ST_eq Te,Jogo jogo, unsigned int s1, unsigned int s2)
{
	Equipa e1,e2;
	
	/*Procura as equipas associadas ao jogo*/
	e1=ST_eq_search(Te,jogo->e1->nome);
	e2=ST_eq_search(Te,jogo->e2->nome);

	/*Se os scores antigos forem iguais entao nao sofrem alteracao*/
	if(jogo->s1!=s1 || jogo->s2!=s2)
	{
		/*Primeiro retira os jogos ganhos a equipa vencedora,
		de acordo com os scores antigos*/
		if(jogo->s1!=jogo->s2)
		{
			if(jogo->s1 < jogo->s2)
			{
				e2->jogos_ganhos--;
			}
			else
			{
				e1->jogos_ganhos--;
			}
		}

		/*Depois incrementa os jogos ganhos da equipa vencedora,
		de acordo com os scores novos*/
		if(s1!=s2)
		{
			if(s1<s2)
			{
				e2->jogos_ganhos++;
			}
			else
			{
				e1->jogos_ganhos++;
			}
		}
	
	/*Os scores do jogo sao atualizados*/
	jogo->s1=s1;
	jogo->s2=s2;

	}
	
	
}


/*Decrementa o numero de jogos de uma das equipas associadas a um jogo que 
vai ser eliminado. Funcao utilizada no "comando_r"*/
void elimina_scores(ST_eq Te,Jogo jogo)
{
	Equipa e1,e2;

	/*Procura as equipas associadas ao jogo*/
	e1=ST_eq_search(Te,jogo->e1->nome);
	e2=ST_eq_search(Te,jogo->e2->nome);

	/*Averigua qual tinha sido a vencedora e
	decrementa o seu numero de jogos ganhos*/
	if(jogo->s1!=jogo->s2)
	{
		if(jogo->s1 < jogo->s2)
		{
			e2->jogos_ganhos--;
		}
		else
		{
			e1->jogos_ganhos--;
		}
	}
}



/*E o comparador dado como argumento a "q_sort". Ordena alfabeticamente.*/
int comparador(const void *a, const void * b)
{

	return strcmp(*(char * const *)a,*(char * const*)b);
}

