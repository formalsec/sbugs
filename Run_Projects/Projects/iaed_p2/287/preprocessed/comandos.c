/*File generated by PreProcessor.py*/


#include "comandos.h"


int le_comandos(link_equi *equipas, link_jogo *jogos_hashtable, Lista_jogos jogos_ls)
{
  int NL = 1;
  while (1)
  {
    char command;
    command = getchar();
    switch (command)
    {
      case 'a':
        a_executa(NL, jogos_hashtable, jogos_ls, equipas);
        NL++;
        break;

      case 'l':
        l_executa(NL, jogos_ls);
        NL++;
        break;

      case 'p':
        p_executa(NL, jogos_hashtable);
        NL++;
        break;

      case 'r':
        r_executa(NL, jogos_hashtable, equipas);
        NL++;
        break;

      case 's':
        s_executa(NL, jogos_hashtable, equipas);
        NL++;
        break;

      case 'A':
        A_executa(NL, equipas, 997);
        NL++;
        break;

      case 'P':
        P_executa(NL, equipas, 997);
        NL++;
        break;

      case 'g':
        g_executa(NL, equipas);
        NL++;
        break;

      case 'x':
        return 0;

    }

  }

}

void a_executa(int NL, link_jogo *jogos_hashtable, Lista_jogos jogos_ls, link_equi *equipas)
{
  char nome[1023];
  char e1[1023];
  char e2[1023];
  int s1;
  int s2;
  Jogo jogo = 0;
  Equipa campea;
  Equipa equipa1;
  Equipa equipa2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  for (int e1_index = 0; e1_index < 10; e1_index++)
  {
    e1[e1_index] = new_sym_var(sizeof(char) * 8);
  }

  e1[10 - 1] = '\0';
  for (int e2_index = 0; e2_index < 10; e2_index++)
  {
    e2[e2_index] = new_sym_var(sizeof(char) * 8);
  }

  e2[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  if (procura_tab_jogo(nome, jogos_hashtable) != 0)
  {
    printf("%d Jogo existente.\n", NL);
    return;
  }
  else
  {
    
  }

  equipa1 = procura_tab_equi(e1, equipas, 997);
  equipa2 = procura_tab_equi(e2, equipas, 997);
  if ((equipa1 == 0) || (equipa2 == 0))
  {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  jogo = novo_jogo(nome, e1, e2, s1, s2);
  insere_tab_jogo(jogo, jogos_hashtable);
  adiciona_jogo_ls(jogo, jogos_ls);
  if (s1 > s2)
  {
    campea = procura_tab_equi(e1, equipas, 997);
    campea->vitorias++;
  }
  else
  {
    
  }

  if (s2 > s1)
  {
    campea = procura_tab_equi(e2, equipas, 997);
    campea->vitorias++;
  }
  else
  {
    
  }

}

void l_executa(int NL, Lista_jogos jogos_ls)
{
  link_jogo_ls temp;
  temp = jogos_ls->cabeca;
  while (temp != 0)
  {
    if (temp->jogo && (strcmp("APAGADO", temp->jogo->nome) != 0))
    {
      printf("%d %s %s %s %d %d\n", NL, temp->jogo->nome, temp->jogo->equipa1, temp->jogo->equipa2, temp->jogo->score_e1, temp->jogo->score_e2);
    }
    else
    {
      
    }

    temp = temp->next;
  }

}

void p_executa(int NL, link_jogo *jogos_hashtable)
{
  char buffer[1023];
  Jogo jogo = 0;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  jogo = procura_tab_jogo(buffer, jogos_hashtable);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  printf("%d %s %s %s %d %d\n", NL, jogo->nome, jogo->equipa1, jogo->equipa2, jogo->score_e1, jogo->score_e2);
}

void r_executa(int NL, link_jogo *jogos_hashtable, link_equi *equipas)
{
  char buffer[1023];
  Jogo jogo;
  Equipa equipa1;
  Equipa equipa2;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  jogo = procura_tab_jogo(buffer, jogos_hashtable);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  equipa1 = procura_tab_equi(jogo->equipa1, equipas, 997);
  equipa2 = procura_tab_equi(jogo->equipa2, equipas, 997);
  if (jogo->score_e1 > jogo->score_e2)
  {
    equipa1->vitorias--;
  }
  else
  {
    
  }

  if (jogo->score_e2 > jogo->score_e1)
  {
    equipa2->vitorias--;
  }
  else
  {
    
  }

  apaga_tab_jogo(jogos_hashtable, jogo->nome);
}

void s_executa(int NL, link_jogo *jogos_hashtable, link_equi *equipas)
{
  char buffer[1023];
  int s1;
  int s2;
  Jogo jogo;
  Equipa equipa1;
  Equipa equipa2;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  jogo = procura_tab_jogo(buffer, jogos_hashtable);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  equipa1 = procura_tab_equi(jogo->equipa1, equipas, 997);
  equipa2 = procura_tab_equi(jogo->equipa2, equipas, 997);
  if (jogo->score_e1 > jogo->score_e2)
  {
    equipa1->vitorias--;
  }
  else
  {
    
  }

  if (jogo->score_e2 > jogo->score_e1)
  {
    equipa2->vitorias--;
  }
  else
  {
    
  }

  jogo->score_e1 = s1;
  jogo->score_e2 = s2;
  if (jogo->score_e1 > jogo->score_e2)
  {
    equipa1->vitorias++;
  }
  else
  {
    
  }

  if (jogo->score_e2 > jogo->score_e1)
  {
    equipa2->vitorias++;
  }
  else
  {
    
  }

}

void A_executa(int NL, link_equi *equipas, int tamanho)
{
  char nome[1023];
  Equipa equipa = 0;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (procura_tab_equi(nome, equipas, tamanho) != 0)
  {
    printf("%d Equipa existente.\n", NL);
    return;
  }
  else
  {
    
  }

  equipa = nova_Equipa(nome);
  insere_tab_equi(equipa, equipas, tamanho);
}

void P_executa(int NL, link_equi *equipas, int tamanho)
{
  char buffer[1023];
  Equipa equipa = 0;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  equipa = procura_tab_equi(buffer, equipas, tamanho);
  if (equipa == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  printf("%d %s %d\n", NL, equipa->nome, equipa->vitorias);
}

void g_executa(int NL, link_equi *equipas)
{
  int i;
  int e = 0;
  int max_vitorias = 0;
  int n_equipas = 0;
  int estado = 0;
  link_equi link_temp = 0;
  Equipa equi_temp = 0;
  char *nomes_equipas[100];
  for (i = 0; i < 997; i++)
  {
    if (equipas[i] != 0)
    {
      link_temp = equipas[i];
      while (link_temp != 0)
      {
        equi_temp = link_temp->equipa;
        estado = 1;
        if (equi_temp->vitorias > max_vitorias)
        {
          max_vitorias = equi_temp->vitorias;
        }
        else
        {
          
        }

        link_temp = link_temp->next;
      }

    }
    else
    {
      
    }

  }

  if (estado == 1)
  {
    for (i = 0; i < 997; i++)
    {
      if (equipas[i] != 0)
      {
        link_temp = equipas[i];
        while (link_temp != 0)
        {
          equi_temp = link_temp->equipa;
          if (equi_temp->vitorias == max_vitorias)
          {
            nomes_equipas[e] = equi_temp->nome;
            e++;
          }
          else
          {
            
          }

          link_temp = link_temp->next;
        }

      }
      else
      {
        
      }

    }

    n_equipas = e;
    qsort(nomes_equipas, n_equipas, sizeof(char *), compara_equipas);
    printf("%d Melhores %d\n", NL, max_vitorias);
    for (i = 0; i < n_equipas; i++)
    {
      if (nomes_equipas[i] != 0)
      {
        printf("%d * %s\n", NL, nomes_equipas[i]);
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
