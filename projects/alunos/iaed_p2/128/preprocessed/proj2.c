#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "funcoes.h"


void le_comandos(link_jogo *heads_jogo, link *heads, limites_lista *jogo, int n_linha);
int main()
{
  link *heads;
  link_jogo *heads_jogo;
  limites_lista *jogo;
  int n_linha = 1;
  jogo = nova_lista();
  heads = inicializa(977);
  heads_jogo = inicializa_hash_jogo(977);
  le_comandos(heads_jogo, heads, jogo, n_linha);
  destroi_tudo(heads_jogo, jogo, heads, 977, 977);
  return 0;
}

void le_comandos(link_jogo *heads_jogo, link *heads, limites_lista *jogo, int n_linha)
{
  char letra;
  letra = new_sym_var(sizeof(char) * 8);
  while (letra != 'x')
  {
    switch (letra)
    {
      case 'a':
        adiciona_jogo(jogo, heads_jogo, heads, n_linha);
        n_linha++;
        break;

      case 'A':
        adiciona_equipa(heads, n_linha);
        n_linha++;
        break;

      case 'l':
        print_jogos(jogo, n_linha);
        n_linha++;
        break;

      case 'p':
        devolve_jogo(heads_jogo, n_linha);
        n_linha++;
        break;

      case 'P':
        devolve_equipa(heads, n_linha);
        n_linha++;
        break;

      case 'r':
        apaga_jogo(heads_jogo, jogo, n_linha);
        n_linha++;
        break;

      case 's':
        altera_score(heads_jogo, n_linha);
        n_linha++;
        break;

      case 'g':
        equipas_mais_vitorias(heads, 977, n_linha);
        n_linha++;
        break;

    }

    letra = new_sym_var(sizeof(char) * 8);
  }

}

