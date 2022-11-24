#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "estruturas.h"
#include "tabelas_disp.h"
#include "comandos.h"


int main()
{
	/*Inicializa estruturas*/
	ST_jg Tj=ST_jg_init(MAX);/*Tabela para jogos*/
	ST_eq Te=ST_eq_init(MAX);/*Tabela para equipas*/
	
	/*Vetor de ponteiros para jogos.
	Os jogos sao adicionados pela ordem que sao adicionados
	ao sistema */
	Jogo *Jogos=can_fail_calloc((Tj->M),sizeof(Jogo));
	
	/*Guarda o numero de linhas. Usada para debug*/
	int num_linhas =1;
	long Nt;
	long Ne;
	/*Letra que e dada como input que distingue o comando a 
	ser executado*/
	char primeira_letra;
	scanf("%c",&primeira_letra);

	while(primeira_letra!='x')
	{
		
		switch(primeira_letra)
		{
			case 'a':
			getchar();
			comando_a(Tj,Te,Jogos,num_linhas);
			break;

			case 'A':
			getchar();
			comando_A(Te,num_linhas);
			break;

			case 'l':
			comando_l(Tj,Jogos, num_linhas);
			break;

			case 'p':
			getchar();
			comando_p(Tj,num_linhas);
			break;

			case 'P':
			getchar();
			comando_P(Te,num_linhas);
			break;

			case 's':
			getchar();
			comando_s(Tj,Te,num_linhas);
			break;

			case 'r':
			getchar();
			comando_r(Tj,Te,Jogos,num_linhas);
			break;

			case 'g':
			comando_g(Te,num_linhas);
			break;
		}
		getchar();
		scanf("%c",&primeira_letra);
		num_linhas++;
		
		/*Verifica se e necessaria a expansao da tabela*/
		Nt=Tj->N;
		Ne=Te->N;
		
		if(Ne++ > (Te->M/2))
		{
			Te=expand_e(Te);
			
		}

		if(Nt++> (Tj->M/2))
		{
			Tj=expand_j(Tj);
			/*Aumenta a capacidade do vetor "Jogo"*/
			Jogos=can_fail_realloc(Jogos,sizeof(Jogo)*(Tj->M));
		}
	}
	
	
	/*Liberta a memoria revervada pelas estruturas*/
	free(Jogos);
	free_HTe(Te);
	free_HTj(Tj);

	return 0;
}