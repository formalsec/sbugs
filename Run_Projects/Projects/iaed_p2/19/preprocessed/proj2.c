/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct equipas
{
  char equipa_nome[1023];
  int nr_vitorias;
} Equipas;
typedef struct 
{
  char nome[1023];
  Equipas *equipa_A;
  Equipas *equipa_B;
  int score1;
  int score2;
} Jogo;
typedef struct no
{
  Jogo jogo;
  struct no *proximo;
} *link;
typedef struct no_equipas
{
  Equipas equipas;
  struct no_equipas *proximo;
} *link_equipas;
link_equipas cria_equipa(char *nome, int nv)
{
  link_equipas nova_no_equipa;
  nova_no_equipa = (link_equipas) malloc(sizeof(struct no_equipas));
  strcpy(nova_no_equipa->equipas.equipa_nome, nome);
  nova_no_equipa->equipas.nr_vitorias = nv;
  nova_no_equipa->proximo = 0;
  return nova_no_equipa;
}

link_equipas insertAtBegining(link_equipas head_list, link_equipas new_node)
{
  if (head_list == 0)
  {
    return new_node;
  }
  else
  {
    {
      new_node->proximo = head_list;
      head_list = new_node;
      return new_node;
    }
  }

}

void delete_list(link_equipas *head_list)
{
  link_equipas k;
  link_equipas anterior;
  for (k = *head_list, anterior = 0; k != 0;)
  {
    anterior = k;
    k = k->proximo;
    free(anterior);
  }

}

int hash(char *nome, int M)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*nome) != '\0'; nome++, a = (a * b) % (M - 1))
  {
    h = ((a * h) + (*nome)) % M;
  }

  return h;
}

link *Init_hash(link *heads, int M)
{
  int i;
  heads = (link *) malloc(M * (sizeof(link)));
  for (i = 0; i < M; i++)
  {
    heads[i] = 0;
  }

  return heads;
}

Equipas *NewEquipes(char *equipa_nome)
{
  Equipas *e = (Equipas *) malloc(sizeof(Equipas));
  strcpy(e->equipa_nome, equipa_nome);
  e->nr_vitorias = 0;
  return e;
}

link NewNode(char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
  link novo = (link) malloc(sizeof(struct no));
  novo->jogo.equipa_A = NewEquipes(equipa1);
  novo->jogo.equipa_B = NewEquipes(equipa2);
  novo->jogo.score1 = score1;
  novo->jogo.score2 = score2;
  strcpy(novo->jogo.nome, nome);
  novo->proximo = 0;
  return novo;
}

link *insere_hash(link *heads, int M, char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
  link j;
  int chave = hash(nome, M);
  if (heads[chave] == 0)
  {
    {
      heads[chave] = NewNode(nome, equipa1, equipa2, score1, score2);
    }
  }
  else
  {
    {
      j = NewNode(nome, equipa1, equipa2, score1, score2);
      j->proximo = heads[chave];
      heads[chave] = j;
    }
  }

  return heads;
}

link verifica_jogo(link *heads, int M, char *nome)
{
  int chave = hash(nome, M);
  link y;
  for (y = heads[chave]; y != 0; y = y->proximo)
  {
    if (strcmp(y->jogo.nome, nome) == 0)
    {
      {
        return y;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

void apaga_no(link no)
{
  free(no->jogo.equipa_A);
  free(no->jogo.equipa_B);
  free(no);
}

link *destroy_hash(link *heads, int M)
{
  int i = 0;
  link aux = 0;
  link anterior = 0;
  for (i = 0; i < M; i++)
  {
    for (aux = heads[i], anterior = 0; aux != 0;)
    {
      anterior = aux;
      aux = aux->proximo;
      apaga_no(anterior);
    }

  }

  return heads;
}

void printjogo(link no)
{
  int NL = 0;
  printf("%d %s %s %s %d %d\n", NL, no->jogo.nome, no->jogo.equipa_A->equipa_nome, no->jogo.equipa_B->equipa_nome, no->jogo.score1, no->jogo.score2);
}

int prinflista(link head)
{
  link aux;
  for (aux = head; aux != 0; aux = aux->proximo)
  {
    printjogo(aux);
  }

  return 0;
}

int verifica_equipa(link_equipas listaDeEquipas, char *nome)
{
  link_equipas k;
  for (k = listaDeEquipas; k != 0; k = k->proximo)
  {
    if (strcmp(k->equipas.equipa_nome, nome) == 0)
    {
      {
        return 1;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

link *adiciona_jogo(int NL, link *heads, int M, char *nome, char *equipa1, char *equipa2, int score1, int score2, link_equipas listaDeEquipas, int *pflag)
{
  if (verifica_jogo(heads, M, nome) == 0)
  {
    {
      if ((verifica_equipa(listaDeEquipas, equipa1) == 0) && (verifica_equipa(listaDeEquipas, equipa2) == 0))
      {
        {
          heads = insere_hash(heads, M, nome, equipa1, equipa2, score1, score2);
          *pflag = 1;
          return heads;
        }
      }
      else
      {
        printf("%d Equipa existente.\n", NL);
      }

    }
  }
  else
  {
    printf("%d Jogo existente.\n", NL);
  }

  *pflag = 0;
  return heads;
}

link_equipas adiciona_equipa(link_equipas listaDeEquipas, char *nome, int NL)
{
  if (verifica_equipa(listaDeEquipas, nome) == 1)
  {
    {
      printf("%d Equipa existente.\n", NL);
      return listaDeEquipas;
    }
  }
  else
  {
    
  }

  return insertAtBegining(listaDeEquipas, cria_equipa(nome, 0));
}

void printEverything(link *heads, int M)
{
  int i;
  for (i = 0; i < M; i++)
  {
    prinflista(heads[i]);
  }

}

void comando_p(link *heads, int M, char *nome, int NL)
{
  link k = verifica_jogo(heads, M, nome);
  if (verifica_jogo(heads, M, nome) == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  printjogo(k);
}

link *comando_r(link *heads, int M, char *nome, int NL)
{
  int chave = hash(nome, M);
  link h;
  link anterior;
  for (h = heads[chave], anterior = 0; h != 0;)
  {
    if (strcmp(h->jogo.nome, nome) == 0)
    {
      {
        if (h == heads[chave])
        {
          heads[chave] = h->proximo;
        }
        else
        {
          anterior->proximo = h->proximo;
        }

        apaga_no(h);
        return heads;
      }
    }
    else
    {
      
    }

    anterior = h;
    h = h->proximo;
  }

  printf("%d Jogo inexistente.\n", NL);
  return heads;
}

int main()
{
  char comando;
  char nome[1023];
  char equipa1[1023];
  char equipa2[1023];
  int score1 = 0;
  int score2 = 0;
  int flag = 0;
  int *pflag = &flag;
  link *heads = 0;
  int M = 1013;
  int NL = 0;
  link_equipas listaDeEquipas = 0;
  heads = Init_hash(heads, 1013);
  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      case 'a':
        NL++;
        getchar();
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        for (int equipa1_index = 0; equipa1_index < 10; equipa1_index++)
      {
        equipa1[equipa1_index] = new_sym_var(sizeof(char) * 8);
      }

        equipa1[10 - 1] = '\0';
        for (int equipa2_index = 0; equipa2_index < 10; equipa2_index++)
      {
        equipa2[equipa2_index] = new_sym_var(sizeof(char) * 8);
      }

        equipa2[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        heads = adiciona_jogo(NL, heads, M, nome, equipa1, equipa2, score1, score2, listaDeEquipas, pflag);
        if (flag == 1)
      {
        {
          listaDeEquipas = adiciona_equipa(listaDeEquipas, equipa1, NL);
          listaDeEquipas = adiciona_equipa(listaDeEquipas, equipa2, NL);
        }
      }
      else
      {
        
      }

        break;

      case 'l':
        NL++;
        printEverything(heads, M);
        break;

      case 'A':
        NL++;
        getchar();
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        listaDeEquipas = adiciona_equipa(listaDeEquipas, nome, NL);
        break;

      case 'p':
        NL++;
        getchar();
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        comando_p(heads, M, nome, NL);
        break;

      case 'r':
        NL++;
        getchar();
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        heads = comando_r(heads, M, nome, NL);

    }

  }

  delete_list(&listaDeEquipas);
  destroy_hash(heads, M);
  free(heads);
  return 0;
}

