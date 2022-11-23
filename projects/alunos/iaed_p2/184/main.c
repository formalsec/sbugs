#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"
#include "jogos.h"
#include "auxiliares.h"
#include "comandos.h"

/*Recebe um caracter e executa o comando correspondente a esse caracter.*/
int main()
{
    char c[2];
    linkE head;
    linkJ headj;
    hptr h;
    head = NULL;
    headj = NULL;   
    c[1]='\0';
    aumenta(&h,INI);
    scanf("%c", &c[0]);
    while (c[0] != EOF)
    {
        switch(c[0])
        {
            case 'A':
                aumenta(&h,INC);
                A(&head,&h);                
                break; 
            
            case 'p':
                aumenta(&h,INC);
                p(&headj,&h);               
                break;
            
            case 'a':
                aumenta(&h,INC);
                a(&headj,head,&h);               
                break;
            
            case 'l':
                aumenta(&h,INC);
                l(headj,&h);                
                break;

            case 'r':
                aumenta(&h,INC);
                r(&headj,&h,head);                
                break;

            case 's':
                aumenta(&h,INC);
                s(&headj,&h,head);                
                break;

            case 'P':
                aumenta(&h,INC);
                P(head,&h);
                break;
            
            case 'g':
                aumenta(&h,INC);
                g(head,&h);
                break;

            case 'x':
                freeE(&head);
                freeJ(&headj);
                exit(0);
        }
    scanf("%c", &c[0]);
    }
    return 0;
}
