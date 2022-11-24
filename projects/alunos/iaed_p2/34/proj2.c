#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "proj2_aux.h"
#include "proj2_comandos.h"

int main(){
    char entrada[MAX_ENTRADA], *comando;
    char *atr1, *atr2, *atr3, *atr4, *atr5;
    int NL=0;

    Lista_jogos_equipas *lje;
    lje = cria_lista(); /*cria a lista_jogos_equipas onde vai ser guardada toda a informacao*/

    while(1){ /*ciclo infinito para receber input, sai com o comando x*/
        NL+=1; /*contador para a linha do comando de input*/
        fgets(entrada,MAX_ENTRADA, stdin); /*le uma linha do stdin*/
        comando = strtok(entrada, ESPACO); /*separa o comando do restante input*/
      
        switch(*comando)
        {
            case 'a': /*caso o comando = a, recebe quatro atributos e executa o a*/
                atr1= strtok(NULL, SEPARADOR);
                atr2= strtok(NULL, SEPARADOR);
                atr3= strtok(NULL, SEPARADOR);
                atr4= strtok(NULL, SEPARADOR);
                atr5= strtok(NULL, NOVA_LINHA);
                a(NL, atr1, atr2, atr3, atr4, atr5, lje);
                break;
            case 'A': /*caso o comando = A, recebe um atributo e executa o A*/
                atr1= strtok(NULL,NOVA_LINHA);
                A(NL, atr1, lje);
                break;
            case 'l': /*caso o comando = l, executa o l*/
                l(NL, lje);
                break;
            case 'p': /*caso o comando = p, recebe um atributo e executa o p*/
                atr1= strtok(NULL, NOVA_LINHA);
                p(NL, atr1, lje);
                break;
            case 'P': /*caso o comando = P, recebe um atributo e executa o P*/
                atr1= strtok(NULL, NOVA_LINHA);
                P(NL, atr1, lje);
                break;
            case 'r': /*caso o comando = r, recebe um atributo e executa o r*/
                atr1= strtok(NULL, NOVA_LINHA);
                r(NL, atr1, lje);
                break;
            case 's': /*caso o comando = s, recebe tres atributos e executa o s*/
                atr1= strtok(NULL, SEPARADOR);
                atr2= strtok(NULL, SEPARADOR);
                atr3= strtok(NULL, NOVA_LINHA);
                s(NL, atr1, atr2, atr3, lje);
                break;
            case 'g': /*caso o comando = g, executa o g*/
                g(NL, lje);
                break;
            case 'x': /*caso o comando = x, executa o free_lista, termina o programa e retorna 0*/
                free_lista(lje);
                exit(0);
        }
    }
    return 0;
}