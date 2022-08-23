#include "funcoes.h" 

/*Numero maximo de elementos das hashtables (dimensao).*/
#define DIM_HASH 1009

int main()
{
	/*Variavel para cada comando.*/
	char car;

	/*Variavel que contem o numero da linha de input atual.*/
	int conta_linhas = 1;

	/*Variaveis das hashtables.*/
	Jogo **jogos;
	Equipa **equipas;

	/*Dimensao das hashtables.*/
	int dim = DIM_HASH;

	/*Inicializacao das hashtables (por encadeamento externo).*/
	jogos = (Jogo**) malloc(dim*sizeof(Jogo));
	HTinic_jogos(jogos, dim);
	
	equipas = (Equipa**) malloc(dim*sizeof(Equipa));
	HTinic_equipas(equipas, dim);

	/*Execucao do programa: Input(comando) -> funcao */
	while((car=getchar()) != 'x')
	{	
		switch(car)
		{
			case 'a':
				adiciona_jogo(jogos, dim, equipas, conta_linhas);
				break;

			case 'l':
				lista_jogos(jogos, dim, conta_linhas);
				break;

			case 'p':
				procura_jogo(jogos, dim, conta_linhas);
				break;

			case 'r':
				apaga_jogo(jogos, equipas, dim, conta_linhas);
				break;

			case 's':
				altera_score(jogos, equipas, dim, conta_linhas);
				break;

			case 'A':
				adiciona_equipa(equipas, dim, conta_linhas);
				break;

			case 'P':
				procura_equipa(equipas, dim, conta_linhas);
				break;

			case 'g':
				encontra_vencedores(equipas, dim, conta_linhas);
				break;

			default:
				conta_linhas++;
		}
	}
	
	/*Free das hashtables e dos seus repetivos elementos. */
	HTfree_jogos(jogos, dim);
	HTfree_equipas(equipas, dim);

	return 0;
}