#include "projeto2.h"

int main(void)
{
  char command;
  int row = 0;
  TEAM* hashT[hash_size];
  GAME* hashG[hash_size];
  hash_initializer(hashT,hashG);

  while(1)
  {
    command = getchar();
    switch(command)

    {
      case 'a':

        row++;
        a(hashG,hashT,row);

        break;

      case 'A':

        row++;
        A(hashT,row);

        break;

      case 'p':

        row++;
        p(hashG,row);

        break;

      case 'r':

        row++;
        r(hashG,row);

        break;

      case 's':

        row++;
        s(hashG,row);

        break;

      case 'P':

        row++;
        P(hashT,row);

        break;

      case 'l':

        row++;

        break;

      case 'g':

        row++;

        break;

      case 'x':

        row++;
        x(hashT,hashG);

        return 0;

        break;
    }
  }
  
  return 0;
}
