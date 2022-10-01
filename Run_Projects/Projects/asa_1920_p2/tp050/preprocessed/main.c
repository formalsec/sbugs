/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
  struct node **direcoes;
  int isChecked;
  int type;
  struct node *anterior;
} node;
node ***list;
node **supermercadosList;
node **casasList;
int supermercados;
int casas;
node **queue;
void atualizaCheck(node *arg)
{
  arg->isChecked = 1;
  if (arg->anterior)
  {
    atualizaCheck(arg->anterior);
  }
  else
  {
    
  }

}

void clearPath(node *arg)
{
  arg->isChecked = 0;
  if (arg->anterior)
  {
    clearPath(arg->anterior);
  }
  else
  {
    
  }

}

int bfs(node *arg, int type)
{
  int i;
  int numeroElementos = 0;
  int posicao = 0;
  node *aux;
  queue[numeroElementos++] = arg;
  arg->isChecked = 2;
  while (numeroElementos > posicao)
  {
    aux = queue[posicao++];
    for (i = 0; i < 4; i++)
    {
      if ((aux->direcoes[i] && (aux->direcoes[i]->type != arg->type)) && (!aux->direcoes[i]->isChecked))
      {
        aux->direcoes[i]->isChecked = 2;
        aux->direcoes[i]->anterior = aux;
        queue[numeroElementos++] = aux->direcoes[i];
        if (aux->direcoes[i]->type == type)
        {
          atualizaCheck(aux->direcoes[i]);
          for (i = 0; i < numeroElementos; i++)
          {
            if (queue[i]->isChecked == 2)
            {
              queue[i]->isChecked = 0;
            }
            else
            {
              
            }

          }

          return 1;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

  }

  return 0;
}

void overridebfs(node *arg, int type)
{
  int i;
  int numeroElementos = 0;
  int posicao = 0;
  node *aux;
  queue[numeroElementos++] = arg;
  arg->isChecked = 2;
  while (numeroElementos > posicao)
  {
    aux = queue[posicao++];
    for (i = 0; i < 4; i++)
    {
      if (aux->direcoes[i])
      {
        if ((aux->direcoes[i]->type == type) || ((aux->direcoes[i]->type != arg->type) && (!aux->direcoes[i]->isChecked)))
        {
          if (aux->direcoes[i]->type == type)
          {
            clearPath(aux->direcoes[i]->anterior);
            aux->direcoes[i]->isChecked = 2;
            aux->direcoes[i]->anterior = aux;
            queue[numeroElementos++] = aux->direcoes[i];
            atualizaCheck(aux->direcoes[i]);
            for (i = 0; i < numeroElementos; i++)
            {
              if (queue[i]->isChecked == 2)
              {
                queue[i]->isChecked = 0;
              }
              else
              {
                
              }

            }

          }
          else
          {
            aux->direcoes[i]->isChecked = 2;
            aux->direcoes[i]->anterior = aux;
            queue[numeroElementos++] = aux->direcoes[i];
          }

        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

  }

}

int resolve()
{
  int i;
  int resultado = 0;
  int auxResultado;
  if (casas >= supermercados)
  {
    for (i = 0; i < supermercados; i++)
    {
      resultado += bfs(supermercadosList[i], 1);
    }

    auxResultado = resultado;
    do
    {
      resultado = auxResultado;
      for (i = 0; i < supermercados; i++)
      {
        if (!supermercadosList[i]->isChecked)
        {
          overridebfs(supermercadosList[i], 1);
        }
        else
        {
          
        }

      }

      for (i = 0; i < casas; i++)
      {
        if (!casasList[i]->isChecked)
        {
          auxResultado += bfs(casasList[i], 2);
        }
        else
        {
          
        }

      }

    }
    while (auxResultado > resultado);
  }
  else
  {
    for (i = 0; i < casas; i++)
    {
      resultado += bfs(casasList[i], 2);
    }

    auxResultado = resultado;
    do
    {
      resultado = auxResultado;
      for (i = 0; i < casas; i++)
      {
        if (!casasList[i]->isChecked)
        {
          printf("indice:%d\n", i);
          overridebfs(casasList[i], 2);
        }
        else
        {
          
        }

      }

      for (i = 0; i < supermercados; i++)
      {
        if (!supermercadosList[i]->isChecked)
        {
          auxResultado += bfs(supermercadosList[i], 1);
        }
        else
        {
          
        }

      }

    }
    while (auxResultado > resultado);
  }

  return resultado;
}

int main()
{
  int avenidas;
  int ruas;
  int i;
  int j;
  int auxAvenida;
  int auxRua;
  avenidas = new_sym_var(sizeof(int) * 8);
  ruas = new_sym_var(sizeof(int) * 8);
  list = malloc(avenidas * (sizeof(node **)));
  for (i = 0; i < avenidas; i++)
  {
    list[i] = malloc(ruas * (sizeof(node *)));
  }

  queue = malloc((ruas * avenidas) * (sizeof(node *)));
  for (i = 0; i < avenidas; i++)
  {
    for (j = 0; j < ruas; j++)
    {
      list[i][j] = malloc(sizeof(node));
      list[i][j]->direcoes = malloc(4 * (sizeof(node *)));
    }

  }

  auxAvenida = avenidas - 1;
  auxRua = ruas - 1;
  list[0][0]->direcoes[0] = 0;
  list[0][0]->direcoes[1] = list[1][0];
  list[0][0]->direcoes[2] = list[0][1];
  list[0][0]->direcoes[3] = 0;
  list[0][0]->type = 0;
  list[0][0]->isChecked = 0;
  list[0][0]->anterior = 0;
  list[0][auxRua]->direcoes[0] = list[0][auxRua - 1];
  list[0][auxRua]->direcoes[1] = list[1][auxRua];
  list[0][auxRua]->direcoes[2] = 0;
  list[0][auxRua]->direcoes[3] = 0;
  list[0][auxRua]->type = 0;
  list[0][auxRua]->isChecked = 0;
  list[0][auxRua]->anterior = 0;
  list[auxAvenida][0]->direcoes[0] = 0;
  list[auxAvenida][0]->direcoes[1] = 0;
  list[auxAvenida][0]->direcoes[2] = list[auxAvenida][1];
  list[auxAvenida][0]->direcoes[3] = list[auxAvenida - 1][0];
  list[auxAvenida][0]->type = 0;
  list[auxAvenida][0]->isChecked = 0;
  list[auxAvenida][0]->anterior = 0;
  list[auxAvenida][auxRua]->direcoes[0] = list[auxAvenida][auxRua - 1];
  list[auxAvenida][auxRua]->direcoes[1] = 0;
  list[auxAvenida][auxRua]->direcoes[2] = 0;
  list[auxAvenida][auxRua]->direcoes[3] = list[auxAvenida - 1][auxRua];
  list[auxAvenida][auxRua]->type = 0;
  list[auxAvenida][auxRua]->isChecked = 0;
  list[auxAvenida][auxRua]->anterior = 0;
  for (j = 1; j < auxRua; j++)
  {
    list[0][j]->direcoes[0] = list[0][j - 1];
    list[0][j]->direcoes[1] = list[1][j];
    list[0][j]->direcoes[2] = list[0][j + 1];
    list[0][j]->direcoes[3] = 0;
    list[0][j]->type = 0;
    list[0][j]->isChecked = 0;
    list[0][j]->anterior = 0;
    list[auxAvenida][j]->direcoes[0] = list[auxAvenida][j - 1];
    list[auxAvenida][j]->direcoes[1] = 0;
    list[auxAvenida][j]->direcoes[2] = list[auxAvenida][j + 1];
    list[auxAvenida][j]->direcoes[3] = list[auxAvenida - 1][j];
    list[auxAvenida][j]->type = 0;
    list[auxAvenida][j]->isChecked = 0;
    list[auxAvenida][j]->anterior = 0;
  }

  for (i = 1; i < auxAvenida; i++)
  {
    list[i][0]->direcoes[0] = 0;
    list[i][0]->direcoes[1] = list[i + 1][0];
    list[i][0]->direcoes[2] = list[i][1];
    list[i][0]->direcoes[3] = list[i - 1][0];
    list[i][0]->type = 0;
    list[i][0]->isChecked = 0;
    list[i][0]->anterior = 0;
    list[i][auxRua]->direcoes[0] = list[i][auxRua - 1];
    list[i][auxRua]->direcoes[1] = list[i + 1][auxRua];
    list[i][auxRua]->direcoes[2] = 0;
    list[i][auxRua]->direcoes[3] = list[i - 1][auxRua];
    list[i][auxRua]->type = 0;
    list[i][auxRua]->isChecked = 0;
    list[i][auxRua]->anterior = 0;
  }

  for (i = 1; i < auxAvenida; i++)
  {
    for (j = 1; j < auxRua; j++)
    {
      list[i][j]->direcoes[0] = list[i][j - 1];
      list[i][j]->direcoes[1] = list[i + 1][j];
      list[i][j]->direcoes[2] = list[i][j + 1];
      list[i][j]->direcoes[3] = list[i - 1][j];
      list[i][j]->type = 0;
      list[i][j]->isChecked = 0;
      list[i][j]->anterior = 0;
    }

  }

  supermercados = new_sym_var(sizeof(int) * 8);
  casas = new_sym_var(sizeof(int) * 8);
  supermercadosList = malloc(supermercados * (sizeof(node *)));
  for (i = 0; i < supermercados; i++)
  {
    auxAvenida = new_sym_var(sizeof(int) * 8);
    auxRua = new_sym_var(sizeof(int) * 8);
    auxRua--;
    auxAvenida--;
    list[auxAvenida][auxRua]->type = 2;
    supermercadosList[i] = list[auxAvenida][auxRua];
  }

  casasList = malloc(casas * (sizeof(node *)));
  for (i = 0; i < casas; i++)
  {
    auxAvenida = new_sym_var(sizeof(int) * 8);
    auxRua = new_sym_var(sizeof(int) * 8);
    auxRua--;
    auxAvenida--;
    list[auxAvenida][auxRua]->type = 1;
    casasList[i] = list[auxAvenida][auxRua];
  }

  printf("%d\n", resolve());
  return 0;
}
