#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj1.h"

int main()
{
    unsigned int cont = 1;
    char cmd[256] = "";
    logistics l;

    l.itemCount = 0;
    l.orderCount = 0;

    while(cont)
    {
        fflush(stdin);
        fgets(cmd, 256, stdin);

        switch(cmd[0])
        {
            case 'a':
                newItem(cmd + 2, &l);
                break;

            case 'q':
                addQty(cmd + 2, &l);
                break;

            case 'N':
                newOrder(&l);
                break;
            
            case 'A':
                addItem(cmd + 2, &l);
                break;

            case 'r':
                removeQty(cmd + 2, &l);
                break;

            case 'R':
                removeItem(cmd + 2, &l);
                break;

            case 'C':
                getCost(cmd + 2, &l);
                break;

            case 'p':
                changePrice(cmd + 2, &l);
                break;

            case 'E':
                getDesc(cmd + 2, &l);
                break;

            case 'm':
                getMost(cmd + 2, &l);
                break;

            case 'l':
                listItems(&l);
                break;

            case 'L':
                listOrder(cmd + 2, &l);
                break;

            case 'x':
                cont = 0;
                break;

            default:
                printf("%s", cmd);
                fprintf(stderr, "Malformed input, unknown command %c.\n", cmd[0]);
        }
    }

    return 0;
}
