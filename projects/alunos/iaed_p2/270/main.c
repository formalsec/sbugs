#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "comandos.h"

/* Inicia as tabelas de dispercao e a lista duplamente ligada, le 9 comandos
 * possiveis do stdin e executa cada um deles  */
int main (){
	pTabEquipas ht_eq = inicia_te(MAX_EQ); pTabJogos ht_jg = inicia_tj(MAX_JG);
	pLista ls_jg = cria_lista();
	int nl = 0; /* contador do numero de comandos executados */
	while(1){ /* termina o programa com o caracter 'x' */
		char comando; comando = getchar(); nl++;
		switch (comando) {
			case 'a': cmd_a(nl, ls_jg, ht_eq, ht_jg); break;
			case 'A': cmd_A(nl, ht_eq); break;
			case 'l': cmd_l(nl, ls_jg); break;
			case 'p': cmd_p(nl, ht_jg); break;
			case 'P': cmd_P(nl, ht_eq); break;
			case 'r': cmd_r(nl, ls_jg, ht_jg); break;
			case 's': cmd_s(nl, ht_jg); break;
			case 'g': cmd_g(nl, ht_eq); break;
      case 'x': liberta_tudo(ls_jg, ht_eq, ht_jg) ; return 0;
		}
		getchar(); /* le o espaco ou o '\n' apos o input do comando escolhido */
	}
}
