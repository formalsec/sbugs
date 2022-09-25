/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int cmd;
char input[200];
struct produto
{
  int id;
  int peso;
  int preco;
  int qtd;
  char desc[64];
} stock[10000];
struct produto temp;
struct encomenda
{
  int id;
  int peso;
  struct produto prt[200];
} ecm[500];
struct encomenda tempE;
int LeLinha()
{
  int i;
  int c;
  if (!(((cmd == 'N') || (cmd == 'x')) || (cmd == 'l')))
  {
    getchar();
  }
  else
  {
    
  }

  for (i = 0; ((c = getchar()) != EOF) && (c != '\n'); ++i)
    input[i] = c;

  input[i] = '\0';
  return 0;
}

int ExtractInfo(int n)
{
  char *res = input;
  switch (n)
  {
    case 'a':
      strcpy(temp.desc, __strtok_r(res, ":", &res));
      temp.preco = atoi(__strtok_r(res, ":", &res));
      temp.peso = atoi(__strtok_r(res, ":", &res));
      temp.qtd = atoi(__strtok_r(res, ":", &res));
      break;

    case 'q':
      temp.id = atoi(__strtok_r(res, ":", &res));
      temp.qtd = atoi(__strtok_r(res, ":", &res));
      break;

    case 'r':
      temp.id = atoi(__strtok_r(res, ":", &res));
      temp.qtd = atoi(__strtok_r(res, ":", &res));
      break;

    case 'R':
      tempE.id = atoi(__strtok_r(res, ":", &res));
      temp.id = atoi(__strtok_r(res, ":", &res));
      break;

    case 'A':
      tempE.id = atoi(__strtok_r(res, ":", &res));
      temp.id = atoi(__strtok_r(res, ":", &res));
      temp.qtd = atoi(__strtok_r(res, ":", &res));
      break;

    case 'C':
      tempE.id = atoi(input);
      break;

    case 'p':
      temp.id = atoi(__strtok_r(res, ":", &res));
      temp.preco = atoi(__strtok_r(res, ":", &res));
      break;

    case 'E':
      tempE.id = atoi(__strtok_r(res, ":", &res));
      temp.id = atoi(__strtok_r(res, ":", &res));
      break;

    case 'm':
      temp.id = atoi(input);
      break;

    case 'L':
      tempE.id = atoi(input);
      break;

  }

  return 0;
}

int Merge(int lim_inf, int lim_sup, int meio, int tab_final[], int string)
{
  int i;
  int j;
  int k;
  int tab_aux[10000];
  int PRTAUX[200];
  if (string == 0)
  {
    for (i = meio + 1; i > lim_inf; i--)
      tab_aux[i - 1] = tab_final[i - 1];

    for (j = meio; j < lim_sup; j++)
      tab_aux[(lim_sup + meio) - j] = tab_final[j + 1];

    for (k = lim_inf; k <= lim_sup; k++)
    {
      if (stock[tab_aux[j]].preco < stock[tab_aux[i]].preco)
      {
        tab_final[k] = tab_aux[j--];
      }
      else
      {
        if ((stock[tab_aux[j]].preco == stock[tab_aux[i]].preco) && (stock[tab_aux[j]].id < stock[tab_aux[i]].id))
        {
          tab_final[k] = tab_aux[j--];
        }
        else
        {
          tab_final[k] = tab_aux[i++];
        }

      }

    }

  }
  else
  {
    for (i = meio + 1; i > lim_inf; i--)
      PRTAUX[i - 1] = tab_final[i - 1];

    for (j = meio; j < lim_sup; j++)
      PRTAUX[(lim_sup + meio) - j] = tab_final[j + 1];

    for (k = lim_inf; k <= lim_sup; k++)
    {
      if (strcmp(ecm[tempE.id].prt[PRTAUX[j]].desc, ecm[tempE.id].prt[PRTAUX[i]].desc) < 0)
      {
        tab_final[k] = PRTAUX[j--];
      }
      else
      {
        tab_final[k] = PRTAUX[i++];
      }

    }

  }

  return 0;
}

int MergeSort(int lim_inf, int lim_sup, int tab_final[], int string)
{
  int meio = (lim_inf + lim_sup) / 2;
  if (lim_sup <= lim_inf)
  {
    return 0;
  }
  else
  {
    
  }

  MergeSort(lim_inf, meio, tab_final, string);
  MergeSort(meio + 1, lim_sup, tab_final, string);
  Merge(lim_inf, lim_sup, meio, tab_final, string);
  return 0;
}

int cmd_a()
{
  int e;
  for (e = 0; e < 10000; e++)
  {
    if (stock[e].id == (-1))
    {
      strcpy(stock[e].desc, temp.desc);
      stock[e].preco = temp.preco;
      stock[e].peso = temp.peso;
      stock[e].qtd = temp.qtd;
      stock[e].id = e;
      break;
    }
    else
    {
      
    }

  }

  printf("Novo produto %d.\n", stock[e].id);
  return 0;
}

int cmd_q()
{
  if (stock[temp.id].id != (-1))
  {
    stock[temp.id].qtd += temp.qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", temp.id);
  }

  return 0;
}

int cmd_N()
{
  int e;
  for (e = 0; e < 500; e++)
  {
    if (ecm[e].id == (-1))
    {
      ecm[e].id = e;
      break;
    }
    else
    {
      
    }

  }

  printf("Nova encomenda %d.\n", ecm[e].id);
  return 0;
}

int cmd_A()
{
  int e;
  if (ecm[tempE.id].id != (-1))
  {
    if (stock[temp.id].id != (-1))
    {
      if (temp.qtd <= stock[temp.id].qtd)
      {
        if ((ecm[tempE.id].peso + (temp.qtd * stock[temp.id].peso)) <= 200)
        {
          for (e = 0; e < 200; e++)
          {
            if (ecm[tempE.id].prt[e].id == (-1))
            {
              ecm[tempE.id].prt[e].id = temp.id;
              strcpy(ecm[tempE.id].prt[e].desc, stock[temp.id].desc);
              ecm[tempE.id].prt[e].preco = stock[temp.id].preco;
              ecm[tempE.id].prt[e].peso = stock[temp.id].peso;
              ecm[tempE.id].prt[e].qtd += temp.qtd;
              ecm[tempE.id].peso += stock[temp.id].peso * temp.qtd;
              stock[temp.id].qtd -= temp.qtd;
              break;
            }
            else
            {
              if (ecm[tempE.id].prt[e].id == temp.id)
              {
                ecm[tempE.id].prt[e].qtd += temp.qtd;
                ecm[tempE.id].peso += stock[temp.id].peso * temp.qtd;
                stock[temp.id].qtd -= temp.qtd;
                break;
              }
              else
              {
                
              }

            }

          }

        }
        else
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", temp.id, tempE.id);
        }

      }
      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", temp.id, tempE.id);
      }

    }
    else
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", temp.id, tempE.id);
    }

  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", temp.id, tempE.id);
  }

  return 0;
}

int cmd_r()
{
  if (stock[temp.id].id != (-1))
  {
    if (temp.qtd <= stock[temp.id].qtd)
    {
      stock[temp.id].qtd -= temp.qtd;
    }
    else
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", temp.qtd, temp.id);
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", temp.id);
  }

  return 0;
}

int cmd_R()
{
  int e;
  int counter = 0;
  if (ecm[tempE.id].id != (-1))
  {
    if (stock[temp.id].id != (-1))
    {
      for (e = 0; e < 200; e++)
      {
        if (ecm[tempE.id].prt[e].id == temp.id)
        {
          stock[temp.id].qtd += ecm[tempE.id].prt[e].qtd;
          ecm[tempE.id].peso -= ecm[tempE.id].prt[e].qtd * ecm[tempE.id].prt[e].peso;
          ecm[tempE.id].prt[e].qtd = 0;
        }
        else
        {
          if (counter == 200)
          {
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", temp.id, tempE.id);
          }
          else
          {
            counter++;
          }

        }

      }

    }
    else
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", temp.id, tempE.id);
    }

  }
  else
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", temp.id, tempE.id);
  }

  return 0;
}

int cmd_C()
{
  int e;
  int custo = 0;
  if (ecm[tempE.id].id != (-1))
  {
    for (e = 0; e < 200; e++)
    {
      if (ecm[tempE.id].prt[e].id != (-1))
      {
        custo += ecm[tempE.id].prt[e].preco * ecm[tempE.id].prt[e].qtd;
      }
      else
      {
        
      }

    }

    printf("Custo da encomenda %d %d.\n", tempE.id, custo);
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", tempE.id);
  }

  return 0;
}

int cmd_p()
{
  int e;
  int i;
  if (stock[temp.id].id != (-1))
  {
    stock[temp.id].preco = temp.preco;
    for (e = 0; e < 500; e++)
    {
      if (ecm[e].id != (-1))
      {
        for (i = 0; i < 200; i++)
        {
          if (ecm[e].prt[i].id == temp.id)
          {
            ecm[e].prt[i].preco = temp.preco;
          }
          else
          {
            
          }

        }

      }
      else
      {
        break;
      }

    }

  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", temp.id);
  }

  return 0;
}

int cmd_E()
{
  int i;
  int qtd_prd = 0;
  if (ecm[tempE.id].id != (-1))
  {
    if (stock[temp.id].id != (-1))
    {
      for (i = 0; i < 200; i++)
      {
        if (ecm[tempE.id].prt[i].id == temp.id)
        {
          qtd_prd = ecm[tempE.id].prt[i].qtd;
        }
        else
        {
          
        }

      }

      printf("%s %d.\n", stock[temp.id].desc, qtd_prd);
    }
    else
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", temp.id);
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", tempE.id);
  }

  return 0;
}

int cmd_m()
{
  int e;
  int max = 0;
  int ide = 0;
  int i;
  if (stock[temp.id].id != (-1))
  {
    for (e = 0; e < 500; e++)
    {
      if (ecm[e].id != (-1))
      {
        for (i = 0; i < 200; i++)
        {
          if (ecm[e].prt[i].id == temp.id)
          {
            if (e == 0)
            {
              max = ecm[e].prt[i].qtd;
              ide = e;
            }
            else
            {
              if (ecm[e].prt[i].qtd > max)
              {
                max = ecm[e].prt[i].qtd;
                ide = e;
              }
              else
              {
                
              }

            }

          }
          else
          {
            
          }

        }

      }
      else
      {
        break;
      }

    }

    if (max != 0)
    {
      printf("Maximo produto %d %d %d.\n", temp.id, ide, max);
    }
    else
    {
      
    }

  }
  else
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", temp.id);
  }

  return 0;
}

int cmd_l()
{
  int e;
  int i;
  int counter = 0;
  int tab_final[10000];
  for (e = 0; e < 10000; e++)
  {
    if (stock[e].id != (-1))
    {
      tab_final[e] = stock[e].id;
      counter++;
    }
    else
    {
      break;
    }

  }

  MergeSort(0, counter - 1, tab_final, 0);
  printf("Produtos\n");
  for (i = 0; i < counter; i++)
    printf("* %s %d %d\n", stock[tab_final[i]].desc, stock[tab_final[i]].preco, stock[tab_final[i]].qtd);

  return 0;
}

int cmd_L()
{
  int e;
  int j;
  int PRT[200];
  int lim_sup = 0;
  if (ecm[tempE.id].id != (-1))
  {
    for (j = 0; j < 200; j++)
    {
      if (ecm[tempE.id].prt[j].id != (-1))
      {
        PRT[lim_sup] = j;
        lim_sup++;
      }
      else
      {
        
      }

    }

    MergeSort(0, lim_sup - 1, PRT, 1);
    printf("Encomenda %d\n", tempE.id);
    for (e = 0; e < lim_sup; e++)
    {
      if (ecm[tempE.id].prt[PRT[e]].qtd > 0)
      {
        printf("* %s %d %d\n", ecm[tempE.id].prt[PRT[e]].desc, ecm[tempE.id].prt[PRT[e]].preco, ecm[tempE.id].prt[PRT[e]].qtd);
      }
      else
      {
        
      }

    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", tempE.id);
  }

  return 0;
}

int main()
{
  int bol = 1;
  int e;
  int j;
  for (e = 0; e < 10000; e++)
    stock[e].id = -1;

  for (e = 0; e < 500; e++)
  {
    for (j = 0; j < 200; j++)
    {
      ecm[e].id = -1;
      ecm[e].peso = 0;
      ecm[e].prt[j].id = -1;
      ecm[e].prt[j].preco = 0;
      ecm[e].prt[j].qtd = 0;
    }

  }

  while (bol)
  {
    cmd = getchar();
    LeLinha();
    ExtractInfo(cmd);
    switch (cmd)
    {
      case 'a':
        cmd_a();
        break;

      case 'q':
        cmd_q();
        break;

      case 'N':
        cmd_N();
        break;

      case 'A':
        cmd_A();
        break;

      case 'r':
        cmd_r();
        break;

      case 'R':
        cmd_R();
        break;

      case 'C':
        cmd_C();
        break;

      case 'p':
        cmd_p();
        break;

      case 'E':
        cmd_E();
        break;

      case 'm':
        cmd_m();
        break;

      case 'l':
        cmd_l();
        break;

      case 'L':
        cmd_L();
        break;

      case 'x':
        bol = 0;
        break;

    }

  }

  return 0;
}

