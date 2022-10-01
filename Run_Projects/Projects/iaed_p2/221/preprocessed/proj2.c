/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct equipaHash
{
  struct Equipa *dados;
} equipaHash;
typedef struct Equipa
{
  char name[1023];
  int jogosGanhos;
  struct Equipa *next;
} Equipa;
typedef struct jogoHash
{
  struct jogo *jogoH;
} jogoHash;
typedef struct jogo
{
  char nome[1023];
  struct Equipa *equipa1;
  struct Equipa *equipa2;
  int result1;
  int result2;
  struct jogo *next;
} jogo;
equipaHash teams[503];
jogoHash games[503];
jogoHash ordenados[1];
int NL;
void init()
{
  int i;
  for (i = 0; i < 503; i++)
  {
    teams[i].dados = 0;
    games[i].jogoH = 0;
  }

  ordenados[0].jogoH = 0;
}

int hashKey(char key)
{
  return key % 503;
}

Equipa *findPointerEquipa(char args[])
{
  int key;
  Equipa *temp;
  key = hashKey(args[0]);
  temp = teams[key].dados;
  while (temp != 0)
  {
    if (!strcmp(temp->name, args))
    {
      return temp;
    }
    else
    {
      
    }

    temp = temp->next;
  }

  return 0;
}

jogo *findPointerJogo(char args[])
{
  int key;
  jogo *temp;
  key = hashKey(args[0]);
  temp = games[key].jogoH;
  while (temp != 0)
  {
    if (!strcmp(temp->nome, args))
    {
      return temp;
    }
    else
    {
      
    }

    temp = temp->next;
  }

  return 0;
}

void adicionaEquipa(char args[])
{
  char nome[1023];
  int key;
  Equipa *temp;
  Equipa *prev;
  strcpy(nome, args);
  key = hashKey(nome[0]);
  temp = teams[key].dados;
  if (temp == 0)
  {
    teams[key].dados = malloc(sizeof(Equipa));
    temp = teams[key].dados;
    strcpy(temp->name, nome);
    temp->next = 0;
    temp->jogosGanhos = 0;
    NL += 1;
    return;
  }
  else
  {
    
  }

  while (temp != 0)
  {
    if (!strcmp(temp->name, nome))
    {
      printf("%d Equipa existente.\n", NL);
      NL += 1;
      return;
    }
    else
    {
      
    }

    prev = temp;
    temp = temp->next;
  }

  prev->next = malloc(sizeof(Equipa));
  strcpy(prev->next->name, nome);
  prev->next->jogosGanhos = 0;
  prev->next->next = 0;
  NL += 1;
  return;
}

void addOrdenados(char nome[1023], char equipa1[1023], char equipa2[1023], int res1, int res2)
{
  jogo *temp;
  jogo *prev;
  Equipa *etemp1;
  Equipa *etemp2;
  etemp1 = findPointerEquipa(equipa1);
  etemp2 = findPointerEquipa(equipa2);
  temp = ordenados[0].jogoH;
  if (temp == 0)
  {
    ordenados[0].jogoH = malloc(sizeof(jogo));
    temp = ordenados[0].jogoH;
    strcpy(temp->nome, nome);
    temp->equipa1 = etemp1;
    temp->equipa2 = etemp2;
    temp->result1 = res1;
    temp->result2 = res2;
    temp->next = 0;
    return;
  }
  else
  {
    
  }

  while (temp != 0)
  {
    prev = temp;
    temp = temp->next;
  }

  prev->next = malloc(sizeof(jogo));
  strcpy(prev->next->nome, nome);
  prev->next->equipa1 = etemp1;
  prev->next->equipa2 = etemp2;
  prev->next->result1 = res1;
  prev->next->result2 = res2;
  prev->next->next = 0;
  return;
}

void adicionaJogo(char args[])
{
  char equipa1[1023];
  char equipa2[1023];
  char nome[1023];
  char delim[2];
  char *token;
  int res1;
  int res2;
  int key;
  jogo *temp;
  jogo *prev;
  Equipa *etemp1;
  Equipa *etemp2;
  strcpy(delim, ":");
  token = strtok(args, delim);
  strcpy(nome, token);
  token = strtok(0, delim);
  strcpy(equipa1, token);
  token = strtok(0, delim);
  strcpy(equipa2, token);
  res1 = atoi(strtok(0, delim));
  res2 = atoi(strtok(0, delim));
  key = hashKey(nome[0]);
  temp = games[key].jogoH;
  if (temp == 0)
  {
    etemp1 = findPointerEquipa(equipa1);
    etemp2 = findPointerEquipa(equipa2);
    if ((etemp1 == 0) || (etemp2 == 0))
    {
      printf("%d Equipa inexistente.\n", NL);
      NL += 1;
      return;
    }
    else
    {
      
    }

    games[key].jogoH = malloc(sizeof(jogo));
    temp = games[key].jogoH;
    strcpy(temp->nome, nome);
    temp->equipa1 = etemp1;
    temp->equipa2 = etemp2;
    temp->result1 = res1;
    temp->result2 = res2;
    temp->next = 0;
    if (res1 > res2)
    {
      etemp1->jogosGanhos += 1;
    }
    else
    {
      
    }

    if (res2 > res1)
    {
      etemp2->jogosGanhos += 1;
    }
    else
    {
      
    }

    NL += 1;
    addOrdenados(nome, equipa1, equipa2, res1, res2);
    return;
  }
  else
  {
    
  }

  while (temp != 0)
  {
    if (!strcmp(temp->nome, nome))
    {
      printf("%d Jogo existente.\n", NL);
      NL += 1;
      return;
    }
    else
    {
      
    }

    prev = temp;
    temp = temp->next;
  }

  etemp1 = findPointerEquipa(equipa1);
  etemp2 = findPointerEquipa(equipa2);
  if ((etemp1 == 0) || (etemp2 == 0))
  {
    printf("%d Equipa inexistente.\n", NL);
    NL += 1;
    return;
  }
  else
  {
    
  }

  prev->next = malloc(sizeof(jogo));
  strcpy(prev->next->nome, nome);
  prev->next->equipa1 = etemp1;
  prev->next->equipa2 = etemp2;
  prev->next->result1 = res1;
  prev->next->result2 = res2;
  if (res1 > res2)
  {
    etemp1->jogosGanhos += 1;
  }
  else
  {
    
  }

  if (res2 > res1)
  {
    etemp2->jogosGanhos += 1;
  }
  else
  {
    
  }

  prev->next->next = 0;
  NL += 1;
  addOrdenados(nome, equipa1, equipa2, res1, res2);
  return;
}

void procuraJogo(char args[])
{
  int key;
  jogo *temp;
  key = hashKey(args[0]);
  temp = games[key].jogoH;
  while (temp != 0)
  {
    if (!strcmp(temp->nome, args))
    {
      printf("%d %s %s %s %d %d\n", NL, temp->nome, temp->equipa1->name, temp->equipa2->name, temp->result1, temp->result2);
      NL += 1;
      return;
    }
    else
    {
      
    }

    temp = temp->next;
  }

  printf("%d Jogo inexistente.\n", NL);
  NL += 1;
  return;
}

void procuraEquipa(char args[])
{
  int key;
  Equipa *temp;
  key = hashKey(args[0]);
  temp = teams[key].dados;
  while (temp != 0)
  {
    if (!strcmp(temp->name, args))
    {
      printf("%d %s %d\n", NL, temp->name, temp->jogosGanhos);
      NL += 1;
      return;
    }
    else
    {
      
    }

    temp = temp->next;
  }

  printf("%d Equipa inexistente.\n", NL);
  NL += 1;
  return;
}

void listaJogos()
{
  jogo *temp;
  temp = ordenados[0].jogoH;
  while (temp != 0)
  {
    printf("%d %s %s %s %d %d\n", NL, temp->nome, temp->equipa1->name, temp->equipa2->name, temp->result1, temp->result2);
    temp = temp->next;
  }

  NL += 1;
  return;
}

void alteraScore(char args[])
{
  char nome[1023];
  char *token;
  char delim[2];
  int res1;
  int res2;
  int oldRes1;
  int oldRes2;
  jogo *temp;
  strcpy(delim, ":");
  token = strtok(args, delim);
  strcpy(nome, token);
  res1 = atoi(strtok(0, delim));
  res2 = atoi(strtok(0, delim));
  temp = findPointerJogo(nome);
  if (temp == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    NL += 1;
    return;
  }
  else
  {
    
  }

  oldRes1 = temp->result1;
  oldRes2 = temp->result2;
  temp->result1 = res1;
  temp->result2 = res2;
  if ((res1 > res2) && (oldRes1 < oldRes2))
  {
    temp->equipa1->jogosGanhos += 1;
    temp->equipa2->jogosGanhos -= 1;
  }
  else
  {
    
  }

  if ((res1 < res2) && (oldRes1 > oldRes2))
  {
    temp->equipa2->jogosGanhos += 1;
    temp->equipa1->jogosGanhos -= 1;
  }
  else
  {
    
  }

  if ((res1 == res2) && (oldRes1 < oldRes2))
  {
    temp->equipa2->jogosGanhos -= 1;
  }
  else
  {
    
  }

  if ((res1 == res2) && (oldRes1 > oldRes2))
  {
    temp->equipa1->jogosGanhos -= 1;
  }
  else
  {
    
  }

  if ((res1 > res2) && (oldRes1 == oldRes2))
  {
    temp->equipa1->jogosGanhos -= 1;
  }
  else
  {
    
  }

  if ((res1 < res2) && (oldRes1 == oldRes2))
  {
    temp->equipa2->jogosGanhos -= 1;
  }
  else
  {
    
  }

  NL += 1;
  return;
}

void apagaJogo(char args[])
{
  char nome[1023];
  jogo *temp;
  jogo *prev;
  int key;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  key = hashKey(nome[0]);
  temp = games[key].jogoH;
  prev = games[key].jogoH;
  if (temp == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    NL += 1;
    return;
  }
  else
  {
    
  }

  if (!strcmp(temp->nome, nome))
  {
    if (temp->result1 > temp->result2)
    {
      temp->equipa1->jogosGanhos -= 1;
    }
    else
    {
      
    }

    if (temp->result1 < temp->result2)
    {
      temp->equipa2->jogosGanhos -= 1;
    }
    else
    {
      
    }

    games[key].jogoH = temp->next;
    free(temp);
    NL += 1;
    return;
  }
  else
  {
    
  }

  while (temp != 0)
  {
    if (!strcmp(temp->nome, nome))
    {
      if (temp->result1 > temp->result2)
      {
        temp->equipa1->jogosGanhos -= 1;
      }
      else
      {
        
      }

      if (temp->result1 < temp->result2)
      {
        temp->equipa2->jogosGanhos -= 1;
      }
      else
      {
        
      }

      prev->next = temp->next;
      free(temp);
      NL += 1;
      return;
    }
    else
    {
      
    }

    prev = temp;
    temp = temp->next;
  }

  printf("%d Jogo inexistente.\n", NL);
  NL += 1;
  return;
}

void maiorVictoria()
{
  Equipa *temp;
  char **sort;
  char *tmp;
  int i;
  int j;
  int max;
  int counter;
  int permCounter;
  max = -1;
  counter = 0;
  for (i = 0; i < 503; i++)
  {
    temp = teams[i].dados;
    while (temp != 0)
    {
      if (temp->jogosGanhos == max)
      {
        counter += 1;
      }
      else
      {
        
      }

      if (temp->jogosGanhos > max)
      {
        max = temp->jogosGanhos;
        counter = 1;
      }
      else
      {
        
      }

      temp = temp->next;
    }

  }

  sort = malloc(counter * (sizeof(char *)));
  permCounter = counter;
  counter = 0;
  for (i = 0; i < 503; i++)
  {
    temp = teams[i].dados;
    while (temp != 0)
    {
      if (temp->jogosGanhos == max)
      {
        sort[counter] = malloc(1023 * (sizeof(char)));
        strcpy(sort[counter], temp->name);
        counter += 1;
      }
      else
      {
        
      }

      temp = temp->next;
    }

  }

  tmp = malloc(1023);
  for (i = 0; i < (permCounter - 1); i++)
  {
    for (j = i + 1; j < permCounter; j++)
    {
      if (strcmp(sort[i], sort[j]) > 0)
      {
        strcpy(tmp, sort[i]);
        strcpy(sort[i], sort[j]);
        strcpy(sort[j], tmp);
      }
      else
      {
        
      }

    }

  }

  free(tmp);
  printf("%d Melhores %d\n", NL, max);
  for (i = 0; i < permCounter; i++)
  {
    printf("%d * %s\n", NL, sort[i]);
  }

  for (i = 0; i < permCounter; i++)
  {
    free(sort[i]);
  }

  free(sort);
  NL += 1;
  return;
}

void freeAll()
{
  int i;
  Equipa *temp;
  Equipa *prev;
  jogo *tmp;
  jogo *prv;
  jogo *ordtemp;
  jogo *ordprev;
  for (i = 0; i < 503; i++)
  {
    temp = teams[i].dados;
    while (temp != 0)
    {
      prev = temp;
      temp = temp->next;
      free(prev);
    }

  }

  for (i = 0; i < 503; i++)
  {
    tmp = games[i].jogoH;
    while (tmp != 0)
    {
      prv = tmp;
      tmp = tmp->next;
      free(prv);
    }

  }

  ordtemp = ordenados[0].jogoH;
  while (ordtemp != 0)
  {
    ordprev = ordtemp;
    ordtemp = ordtemp->next;
    free(ordprev);
  }

  return;
}

int main()
{
  char cmd[4098];
  char letra;
  char args[4098 - 2];
  NL = 1;
  init();
  while (1)
  {
    fgets(cmd, 4098, stdin);
    letra = new_sym_var(sizeof(char) * 8);
    for (int args_index = 0; args_index < (4098 - 2); args_index++)
    {
      args[args_index] = new_sym_var(sizeof(char) * 8);
    }

    args[(4098 - 2) - 1] = '\0';
    switch (letra)
    {
      case 'a':
        adicionaJogo(args);
        break;

      case 'A':
        adicionaEquipa(args);
        break;

      case 'l':
        listaJogos();
        break;

      case 'p':
        procuraJogo(args);
        break;

      case 'P':
        procuraEquipa(args);
        break;

      case 'r':
        apagaJogo(args);
        break;

      case 's':
        alteraScore(args);
        break;

      case 'g':
        maiorVictoria();
        break;

      case 'x':
        freeAll();
        return 0;
        break;

    }

  }

  return 0;
}
