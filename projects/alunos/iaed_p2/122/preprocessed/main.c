#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "match.h"
#include "hashtable.h"
#include "stack.h"
#include "list.h"


int main()
{
  int lineCounter = 0;
  char command;
  link matches;
  tSTACK teams;
  STinit();
  teams = tSTACKinit();
  matches = 0;
  do
  {
    command = new_sym_var(sizeof(char) * 8);
    if (command == 'a')
    {
      lineCounter++;
      matches = a(matches, teams, lineCounter);
    }
    else
    {
      if (command == 'A')
      {
        lineCounter++;
        A(teams, lineCounter);
      }
      else
      {
        if (command == 'l')
        {
          lineCounter++;
          l(matches, lineCounter);
        }
        else
        {
          if (command == 'p')
          {
            lineCounter++;
            p(lineCounter);
          }
          else
          {
            if (command == 'P')
            {
              lineCounter++;
              P(matches, teams, lineCounter);
            }
            else
            {
              if (command == 'r')
              {
                lineCounter++;
                matches = r(matches, lineCounter);
              }
              else
              {
                if (command == 's')
                {
                  lineCounter++;
                  s(lineCounter);
                }
                else
                {
                  if (command == 'g')
                  {
                    lineCounter++;
                    g(matches, teams, lineCounter);
                  }
                  else
                  {
                    
                  }

                }

              }

            }

          }

        }

      }

    }

  }
  while (command != 'x');
  matches = x(matches, teams);
  return 0;
}

