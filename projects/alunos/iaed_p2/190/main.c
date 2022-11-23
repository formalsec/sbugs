#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "hashtable.h"
#include "hashtableEquipa.h"
#include "funcoes.h"
#define DIMGRANDE 3500

int main(){
    char str[DIMGRANDE];
    int i=1;
    int keyJogo = 0;
    int contadorJogos = 0;
    int contadorEquipas = 0;
    int tamHash = 500;
    int tamHashEquipa = 500;
    init(tamHash);
    initEquipa(tamHashEquipa);
    while (1) {
        int c, i2;
        for (i2 = 0; i2 < DIMGRANDE - 1 && (c = getchar()) != EOF && c != '\n'; i2++) {
            str[i2] = c;
        }
        str[i2] = '\0';
        switch (str[0]) {
            case 'a':
                a(i,str,&keyJogo,&tamHash,&contadorJogos,&tamHashEquipa);
                if ((contadorJogos/tamHash) > 2)
                    chk_hashtable(&tamHash,contadorJogos);
                break;
            case 'A':
                A(i,str,&tamHashEquipa,&contadorEquipas);
                if ((contadorEquipas/tamHashEquipa) > 2)
                    chk_hashtableEquipa(&tamHashEquipa, contadorEquipas);
                break;
            case 'p':
                p(i,str,&tamHash);
                break;
            case 'P':
                P(i,str,&tamHashEquipa);
                break;
            case 'l':
                l(i,contadorJogos,tamHash);
                break;
            case 'r':
                r(i, str,tamHash,tamHashEquipa,&contadorJogos);
                break;
            case 'g':
                g(i,tamHashEquipa,contadorEquipas);
                break;
            case 's':
                s(i,str,tamHash,tamHashEquipa);
                break;
            case 'x':
                x(tamHash, tamHashEquipa);
                return 0;

        }
        i++;
    }
}

