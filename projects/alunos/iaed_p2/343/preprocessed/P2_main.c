#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "jogos.h"
#include "nodes.h"
#include "hash.h"
#include "funcs.h"


int main()
{
  int nl = 0;
  char c;
  node_eq *table_eq = init_eq();
  node_eq *lista_eq;
  node_jg *table_jg = init_jg();
  link *lista = init_lk();
  lista_eq = malloc(sizeof(node_eq));
  lista_eq[0] = 0;
  while (1)
  {
    c = getchar();
    nl++;
    switch (c)
    {
      case 'a':
        acommand(nl, table_jg, table_eq, lista);
        break;

      case 'A':
        Acommand(nl, table_eq, lista_eq);
        break;

      case 'l':
        lcommand(nl, lista);
        break;

      case 'p':
        pcommand(nl, table_jg);
        break;

      case 'P':
        Pcommand(nl, table_eq);
        break;

      case 'r':
        rcommand(nl, table_jg, lista);
        break;

      case 's':
        scommand(nl, table_jg);
        break;

      case 'g':
        gcommand(nl, lista_eq);
        break;

      case 'x':
        xcommand(table_eq, lista_eq, table_jg, lista);
        return 0;

    }

  }

}

