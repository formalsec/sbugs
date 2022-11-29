#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj2.h"

/* FUNCAO PRINCIPAL */

/* Funcao principal que executa uma funcao de acordo com o primeiro parametro do input. */
int main()
{
  char command;
  Hash_equipa hash_eq;
  Hash_jogo hash_jg;
  Dados dados = {0};

  cabeca = NULL; /* Inicializacao do ponteiro para o inicio da lista de jogos. */

  HT_Equipas_Init(TAM_HASH, &hash_eq);
  HT_Jogos_Init(TAM_HASH, &hash_jg);

  while (1)
  {
    command = getchar();
    switch (command)
    {
    case 'a':
      dados.NL++;
      func_a(&hash_jg, &hash_eq, dados.NL);
      break;
    case 'A':
      dados.NL++;
      func_A(&hash_eq, dados.NL);
      break;
    case 'l':
      dados.NL++;
      func_l(dados.NL);
      break;
    case 'p':
      dados.NL++;
      func_p(&hash_jg, dados.NL);
      break;
    case 'P':
      dados.NL++;
      func_P(&hash_eq, dados.NL);
      break;
    case 'r':
      dados.NL++;
      func_r(&hash_jg, &hash_eq, dados.NL);
      break;
    case 's':
      dados.NL++;
      func_s(&hash_jg, &hash_eq, dados.NL);
      break;
    case 'g':
      dados.NL++;
      func_g(&hash_eq, dados.NL);
      break;
    case 'x':
      clean_memory(&hash_eq, &hash_jg);
      return EXIT_SUCCESS;
    default:
      printf("ERRO: Comando desconhecido\n");
    }
    getchar();
  }
  return EXIT_FAILURE;
}

/* COMANDOS */

/* Adiciona um jogo. */
void func_a(Hash_jogo *hash_jg, Hash_equipa *hash_eq, int NL)
{
  char nome_jogo[CAR_MAX];
  char equipa_1[CAR_MAX];
  char equipa_2[CAR_MAX];
  int pontuacao_1;
  int pontuacao_2;
  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo, equipa_1, equipa_2, &pontuacao_1, &pontuacao_2);
  HT_Jogos_Insert(nome_jogo, equipa_1, equipa_2, pontuacao_1, pontuacao_2, hash_jg, hash_eq, NL);
}

/* Adiciona uma equipa. */
void func_A(Hash_equipa *hash_eq, int NL)
{
  char nome_equipa[CAR_MAX];
  scanf(" %[^:\n]", nome_equipa);
  HT_Equipas_Insert(nome_equipa, hash_eq, NL);
}

/* Lista todos os jogos pela ordem de entrada. */
void func_l(int NL)
{
  imprimeLista(NL);
}

/* Procura um jogo dado um nome. */
void func_p(Hash_jogo *hash_jg, int NL)
{
  char nome_jogo[CAR_MAX];
  scanf(" %[^:\n]", nome_jogo);
  printJogo(hash_jg, nome_jogo, NL);
}

/* Procura uma equipa dado um nome. */
void func_P(Hash_equipa *hash_eq, int NL)
{
  char nome_equipa[CAR_MAX];
  scanf(" %[^:\n]", nome_equipa);
  if(HT_Get_Equipa(hash_eq,nome_equipa, NULL) != 0 )
    printEquipa(hash_eq, nome_equipa, NL);
  else
    printf("%d Equipa inexistente.\n", NL);
}

/* Elimina um jogo dado um nome. */
void func_r(Hash_jogo *hash_jg, Hash_equipa *hash_eq, int NL)
{
  char nome_jogo[CAR_MAX];
  Jogo *jogo = NULL;
  Equipa *equipa = NULL;
  scanf(" %[^:\n]", nome_jogo);
    if(HT_Get_Jogo(hash_jg, nome_jogo, &jogo) == 0)
    {
      printf("%d Jogo inexistente.\n", NL);
    }
    else
    {
      if (jogo->pontuacao_1 > jogo->pontuacao_2) 
      {
        HT_Get_Equipa(hash_eq,jogo->equipa_1, &equipa);
        equipa->vitorias -= 1;
      }
      else if (jogo->pontuacao_1 < jogo->pontuacao_2) 
      {
        HT_Get_Equipa(hash_eq,jogo->equipa_2, &equipa);
        equipa->vitorias -= 1;
      }
      remocao(jogo);
      HT_Jogo_Delete(jogo, hash_jg);
    }
}

/* Altera a pontuacao(score) de um jogo. */
void func_s(Hash_jogo *hash_jg, Hash_equipa *hash_eq, int NL)
{
  char nome_jogo[CAR_MAX];
  int pontuacao_1;  
  int pontuacao_2;
  Jogo *jogo = NULL;
  Equipa *equipa = NULL;
  scanf(" %[^:\n]:%d:%d", nome_jogo, &pontuacao_1, &pontuacao_2);
  if(HT_Get_Jogo(hash_jg,nome_jogo, &jogo) == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
   if (jogo->pontuacao_1 > jogo->pontuacao_2) 
    {
        HT_Get_Equipa(hash_eq, jogo->equipa_1, &equipa);
        equipa->vitorias -= 1;
    }
    else if(jogo->pontuacao_1 < jogo->pontuacao_2)
    {
        HT_Get_Equipa(hash_eq, jogo->equipa_2, &equipa);
        equipa->vitorias -= 1;
    }  
    jogo->pontuacao_1 = pontuacao_1;
    jogo->pontuacao_2 = pontuacao_2;
    if (jogo->pontuacao_1 > jogo->pontuacao_2) 
    {
        HT_Get_Equipa(hash_eq, jogo->equipa_1, &equipa);
        equipa->vitorias += 1;
    }
    else if(jogo->pontuacao_1 < jogo->pontuacao_2)
    {
        HT_Get_Equipa(hash_eq, jogo->equipa_2, &equipa);
        equipa->vitorias += 1;
    }
  }
}

/* Lista equipas com maior pontuacao por ordem alfabetica. */
void func_g(Hash_equipa *hash_eq, int NL)
{
  seleciona_equipas(hash_eq, NL);
}

/* FUNCOES AUXILIARES */

char *strdup(const char *src)
{
    char *dst = can_fail_malloc(strlen(src) + 1); 
    if (dst == NULL)
        return NULL;  
    strcpy(dst, src); 
    return dst;       
}

/* Funcao de hash que calcula uma posicao da hash table. */
int calc_hash(char *v, int M)
{
    int h = 0, a = 127;
    for (; (*v) != '\0'; v++)
        h = (a * h + (*v)) % M;
    return h;
}

/* Funcao que liberta o espaco alocado. */
void clean_memory(Hash_equipa *hash_eq, Hash_jogo *hash_jg)
{
  HT_Equipas_Delete(hash_eq);
  HT_Jogos_Delete(hash_jg);
  deleteCabeca(&cabeca);
}