#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include "products.h"
#include "misc.h"
#include "orders.h"

int main()
{
    int cmd = getchar();

    while (cmd != EOF) 
    {
        if (cmd == 'x') 
        {
            break;
        }
        else if (cmd == 'a')
        {
            new_product();
        }
        
        else if (cmd == 'q')
        {
            add_stock();
        }

        else if (cmd == 'r')
        {
            remove_stock();
        }

        else if (cmd == 'p')
        {
            change_price();
        }

        else if (cmd == 'k')
        {
            show_stock();
        }

        else if (cmd == 'N')
        {
            new_order();
        }

        else if (cmd == 'A')
        {
            add_to_order();
        }

        else if (cmd =='K')
        {
            show_orders();
        }

        else if (cmd == 'C')
        {
            order_price();
        }

        else if (cmd == 'E')
        {
            order_desc_quantity();
        }

        else if (cmd == 'm')
        {
            compare_orders();
        }

        else if (cmd == 'l')
        {
            sort_products();
        }

        else if (cmd == 'L')
        {
            sort_orders();
        }

        else if (cmd == 'R')
        {
            remove_from_order();
        }

        while (cmd != '\n' && cmd != EOF)
        {
            cmd = getchar();
        }

        cmd = getchar();
    }  
    return 0;
}