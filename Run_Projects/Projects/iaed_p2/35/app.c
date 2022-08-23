#include "app.h"

void app() {
    /*hash table dos ponteiro para os jogos*/
    Hashtable_JOGOS HTj;
    /*hash table dos ponteiro para as equipas*/
    Hashtable_EQUIPAS HTe;

    /*inicializa a hash table dos ponteiro para os jogos*/
    HTj = HashtableInit_JOGOS(30);

    /*inicializa a hash table dos ponteiro para as equipas*/
    HTe = HashtableInit_EQUIPAS(30);
    while(1) {
        char cmd = getchar();
        switch (cmd) {
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
