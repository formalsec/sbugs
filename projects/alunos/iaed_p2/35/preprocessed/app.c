#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "app.h"


void app()
{
  Hashtable_JOGOS HTj;
  Hashtable_EQUIPAS HTe;
  HTj = HashtableInit_JOGOS(30);
  HTe = HashtableInit_EQUIPAS(30);
  while (1)
  {
    char cmd = getchar();
    switch (cmd)
    {
      case 'a':
        a(HTj, HTe);
        break;

      case 'A':
        A(HTe);
        break;

      case 'l':
        l();
        break;

      case 'p':
        p(HTj);
        break;

      case 'P':
        P(HTe);
        break;

      case 'r':
        r(HTj, HTe);
        break;

      case 's':
        s(HTj, HTe);
        break;

      case 'g':
        g();
        break;

      case 'x':
        x(HTj, HTe);
        return;

      default:
        break;

    }

  }

}

