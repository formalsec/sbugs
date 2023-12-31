#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


unsigned int hash(char *nome)
{
  int i;
  int tamanho = strlen(nome);
  unsigned int hash_valor = 0;
  for (i = 0; i < tamanho; i++)
  {
    hash_valor += nome[i];
    hash_valor = (hash_valor * nome[i]) % 1000;
  }

  return hash_valor;
}

typedef struct Equipa
{
  char *nome;
  int vitorias;
  struct Equipa *next;
} Equipa;
typedef struct 
{
  Equipa **entradas;
} hash_tabela;
hash_tabela *hash_criar(int hash_tamanho)
{
  int i;
  hash_tabela *hashtabela = malloc(sizeof(hash_tabela));
  hashtabela->entradas = malloc((sizeof(Equipa *)) * hash_tamanho);
  for (i = 0; i < hash_tamanho; i++)
  {
    hashtabela->entradas[i] = 0;
  }

  return hashtabela;
}

Equipa *procuraequipa(hash_tabela *hashtabela, char *nome)
{
  unsigned int indice = hash(nome);
  Equipa *entrada = hashtabela->entradas[indice];
  while (entrada != 0)
  {
    if (strcmp(entrada->nome, nome) == 0)
    {
      return entrada;
    }
    else
    {
      
    }

    entrada = entrada->next;
  }

  return entrada;
}

void hash_adicionarequipa(hash_tabela *hashtabela, char *nome, int linha)
{
  unsigned int indice = hash(nome);
  Equipa *entrada;
  if (procuraequipa(hashtabela, nome) != 0)
  {
    printf("%d Equipa existente.\n", linha);
  }
  else
  {
    entrada = malloc(sizeof(Equipa));
    entrada->nome = (char *) malloc((sizeof(char)) * (strlen(nome) + 1));
    strcpy(entrada->nome, nome);
    entrada->vitorias = 0;
    entrada->next = hashtabela->entradas[indice];
    hashtabela->entradas[indice] = entrada;
  }

}

typedef struct Jogo
{
  char *nome;
  char *equipa1;
  char *equipa2;
  int score1;
  int score2;
  struct Jogo *prox;
} Jogo;
typedef struct 
{
  Jogo **entradasj;
} hash_tabela_jogo;
int contador_vetor = 0;
Jogo vetor[10000];
hash_tabela_jogo *hash_criarj(int hash_tamanho)
{
  int i = 0;
  hash_tabela_jogo *hashtabela = malloc(sizeof(hash_tabela_jogo));
  hashtabela->entradasj = malloc((sizeof(Jogo *)) * hash_tamanho);
  for (i = 0; i < hash_tamanho; i++)
  {
    hashtabela->entradasj[i] = 0;
  }

  return hashtabela;
}

void adicionavitoria(hash_tabela *hashtabelaequipas, char *equipa)
{
  unsigned int indice = hash(equipa);
  Equipa *entrada = hashtabelaequipas->entradas[indice];
  entrada->vitorias += 1;
}

void retiravitoria(hash_tabela *hashtabelaequipas, char *equipa)
{
  unsigned int indice = hash(equipa);
  Equipa *entrada = hashtabelaequipas->entradas[indice];
  entrada->vitorias -= 1;
}

Jogo *procurajogo(hash_tabela_jogo *hashtabela, char *nome)
{
  unsigned int indice = hash(nome);
  Jogo *entrada = hashtabela->entradasj[indice];
  while (entrada != 0)
  {
    if (strcmp(entrada->nome, nome) == 0)
    {
      return entrada;
    }
    else
    {
      
    }

    entrada = entrada->prox;
  }

  return entrada;
}

void hash_adicionarjogo(hash_tabela_jogo *hashtabela, hash_tabela *hashtabelaequipas, char *nome, char *equipa1, char *equipa2, int score1, int score2, int linha)
{
  unsigned int indice = hash(nome);
  Jogo *entrada;
  if (procurajogo(hashtabela, nome) != 0)
  {
    printf("%d Jogo existente.\n", linha);
  }
  else
  {
    if ((procuraequipa(hashtabelaequipas, equipa1) == 0) || (procuraequipa(hashtabelaequipas, equipa2) == 0))
    {
      printf("%d Equipa inexistente.\n", linha);
    }
    else
    {
      entrada = malloc(sizeof(Jogo));
      entrada->nome = (char *) malloc((sizeof(char)) * (strlen(nome) + 1));
      entrada->equipa1 = (char *) malloc((sizeof(char)) * (strlen(equipa1) + 1));
      entrada->equipa2 = (char *) malloc((sizeof(char)) * (strlen(equipa2) + 1));
      strcpy(entrada->nome, nome);
      strcpy(entrada->equipa1, equipa1);
      strcpy(entrada->equipa2, equipa2);
      entrada->score1 = score1;
      entrada->score2 = score2;
      if (score1 > score2)
      {
        adicionavitoria(hashtabelaequipas, equipa1);
      }
      else
      {
        if (score2 > score1)
        {
          adicionavitoria(hashtabelaequipas, equipa2);
        }
        else
        {
          
        }

      }

      entrada->prox = hashtabela->entradasj[indice];
      hashtabela->entradasj[indice] = entrada;
      vetor[contador_vetor] = *entrada;
      contador_vetor++;
    }

  }

}

void lista_jogos(int linha)
{
  int i = 0;
  for (i = 0; i < contador_vetor; i++)
  {
    printf("%d %s %s %s %d %d\n", linha, vetor[i].nome, vetor[i].equipa1, vetor[i].equipa2, vetor[i].score1, vetor[i].score2);
  }

}

void apagajogo(hash_tabela_jogo *hashtabelaj, hash_tabela *hashtabelaequipas, char *nome)
{
  unsigned int indice = hash(nome);
  Jogo *J = hashtabelaj->entradasj[indice];
  Jogo *anterior = 0;
  while (J != 0)
  {
    if (strcmp(J->nome, nome) == 0)
    {
      if (anterior != 0)
      {
        anterior->prox = J->prox;
      }
      else
      {
        hashtabelaj->entradasj[indice] = J->prox;
      }

      if (J->score1 > J->score2)
      {
        retiravitoria(hashtabelaequipas, J->equipa1);
      }
      else
      {
        if (J->score2 > J->score1)
        {
          retiravitoria(hashtabelaequipas, J->equipa2);
        }
        else
        {
          
        }

      }

      free(J->nome);
      free(J->equipa1);
      free(J->equipa2);
    }
    else
    {
      
    }

    anterior = J;
    J = J->prox;
  }

}

void alterascore(hash_tabela_jogo *hashtabelaj, hash_tabela *hashtabelaequipas, char *nome, int score1, int score2)
{
  Jogo *J = procurajogo(hashtabelaj, nome);
  if ((J->score1 > J->score2) && (score2 > score1))
  {
    retiravitoria(hashtabelaequipas, J->equipa1);
    adicionavitoria(hashtabelaequipas, J->equipa2);
  }
  else
  {
    
  }

  if ((J->score1 > J->score2) && (score2 == score1))
  {
    retiravitoria(hashtabelaequipas, J->equipa1);
  }
  else
  {
    if ((J->score1 == J->score2) && (score2 > score1))
    {
      adicionavitoria(hashtabelaequipas, J->equipa2);
    }
    else
    {
      if ((J->score1 == J->score2) && (score1 > score2))
      {
        adicionavitoria(hashtabelaequipas, J->equipa1);
      }
      else
      {
        if ((J->score1 < J->score2) && (score1 > score2))
        {
          retiravitoria(hashtabelaequipas, J->equipa2);
          adicionavitoria(hashtabelaequipas, J->equipa1);
        }
        else
        {
          if ((J->score1 < J->score2) && (score1 == score2))
          {
            retiravitoria(hashtabelaequipas, J->equipa2);
          }
          else
          {
            
          }

        }

      }

    }

  }

  J->score1 = score1;
  J->score2 = score2;
}

int main()
{
  hash_tabela *hashtabela = hash_criar(1000);
  hash_tabela_jogo *hashtabelaj = hash_criarj(1000);
  int flag = 1;
  int linha = 0;
  int score1;
  int score2;
  char *nome = (char *) malloc((sizeof(char)) * 1024);
  char *equipa1 = (char *) malloc((sizeof(char)) * 1024);
  char *equipa2 = (char *) malloc((sizeof(char)) * 1024);
  Equipa *E;
  Jogo *J;
  do
  {
    switch (getchar())
    {
      case 'a':
        linha++;
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
        hash_adicionarjogo(hashtabelaj, hashtabela, nome, equipa1, equipa2, score1, score2, linha);
        break;

      case 'A':
        linha++;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        hash_adicionarequipa(hashtabela, nome, linha);
        break;

      case 'l':
        linha++;
        lista_jogos(linha);
        break;

      case 'p':
        linha++;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        J = procurajogo(hashtabelaj, nome);
        if (J == 0)
      {
        printf("%d Jogo inexistente.\n", linha);
      }
      else
      {
        printf("%d %s %s %s %d %d\n", linha, J->nome, J->equipa1, J->equipa2, J->score1, J->score2);
      }

        break;

      case 'P':
        linha++;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        E = procuraequipa(hashtabela, nome);
        if (E == 0)
      {
        printf("%d Equipa inexistente.\n", linha);
      }
      else
      {
        printf("%d %s %d\n", linha, E->nome, E->vitorias);
      }

        procuraequipa(hashtabela, nome);
        break;

      case 'r':
        linha++;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        if (procurajogo(hashtabelaj, nome) == 0)
      {
        printf("%d Jogo inexistente.\n", linha);
      }
      else
      {
        apagajogo(hashtabelaj, hashtabela, nome);
      }

        break;

      case 's':
        linha++;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        if (procurajogo(hashtabelaj, nome) == 0)
      {
        printf("%d Jogo inexistente.\n", linha);
      }
      else
      {
        alterascore(hashtabelaj, hashtabela, nome, score1, score2);
      }

        break;

      case 'g':
        linha++;
        break;

      case 'x':
        linha = 0;
        flag = 0;
        break;

    }

  }
  while (flag == 1);
  free(nome);
  free(hashtabela);
  free(hashtabelaj);
  free(equipa1);
  free(equipa2);
  return 0;
}

