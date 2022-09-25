/*File generated by PreProcessor.py*/


#include "jogo.h"


hash_table *cria_hash_table()
{
  hash_table *rv = malloc(sizeof(hash_table));
  rv->capacidade = 1997;
  rv->tb_jogo = calloc(rv->capacidade, sizeof(hash_node *));
  return rv;
}

hash_node *cria_no(hash_node *inicio)
{
  hash_node *nn = malloc(sizeof(hash_node));
  nn->proximoNo = inicio;
  inicio = nn;
  return inicio;
}

int verificaExiste_jogo(hash_table *hashJogo, char *jogo)
{
  hash_node *n;
  size_t h = hash(jogo, hashJogo->capacidade);
  for (n = hashJogo->tb_jogo[h]; n != 0; n = n->proximoNo)
  {
    if (strcmp(n->informacoes_jogo->nome_jogo, jogo) == 0)
    {
      return 0;
    }
    else
    {
      
    }

  }

  return 1;
}

int verificaEquipaDentro_aux_1(hash_table_equipa *t, char *equipa1, size_t h)
{
  hash_node_equipa *n;
  for (n = t->tb[h]; n != 0; n = n->next)
  {
    if (strcmp(n->equipa1, equipa1) == 0)
    {
      return 0;
    }
    else
    {
      
    }

  }

  return 1;
}

int verificaEquipaDentro_aux_2(hash_table_equipa *t, char *equipa2, size_t h)
{
  hash_node_equipa *n;
  for (n = t->tb[h]; n != 0; n = n->next)
  {
    if (strcmp(n->equipa1, equipa2) == 0)
    {
      return 0;
    }
    else
    {
      
    }

  }

  return 1;
}

void aumentaGanhos(hash_table_equipa *hashEquipa, hash_node_equipa *equipaAux, size_t h_eq, char *equipa)
{
  for (equipaAux = hashEquipa->tb[h_eq]; equipaAux; equipaAux = equipaAux->next)
  {
    if (strcmp(equipaAux->equipa1, equipa) == 0)
    {
      equipaAux->vitorias += 1;
      return;
    }
    else
    {
      
    }

  }

}

void adiciona_jogo(hash_table *hash_jogo, int *Nr_linha, hash_table_equipa *hashEquipa, inicioFimJogos *Lista_jogos)
{
  char nome_jogo[1024];
  char equipa1[1024];
  char equipa2[1024];
  int pontos1;
  int pontos2;
  hash_node_equipa *equipa_aux;
  NoListaJogos *novo_jogo;
  size_t h;
  size_t h_eq1;
  size_t h_eq2;
  hash_node *n;
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
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
  pontos1 = new_sym_var(sizeof(int) * 8);
  pontos2 = new_sym_var(sizeof(int) * 8);
  h = hash(nome_jogo, hash_jogo->capacidade);
  for (n = hash_jogo->tb_jogo[h]; n != 0; n = n->proximoNo)
  {
    if (strcmp(n->informacoes_jogo->nome_jogo, nome_jogo) == 0)
    {
      printf("%d Jogo existente.\n", *Nr_linha);
      *Nr_linha += 1;
      return;
    }
    else
    {
      
    }

  }

  h_eq1 = hash(equipa1, hashEquipa->capacidade_equipa);
  h_eq2 = hash(equipa2, hashEquipa->capacidade_equipa);
  if ((verificaEquipaDentro_aux_1(hashEquipa, equipa1, h_eq1) == 1) || (verificaEquipaDentro_aux_2(hashEquipa, equipa2, h_eq2) == 1))
  {
    printf("%d Equipa inexistente.\n", *Nr_linha);
    *Nr_linha += 1;
    return;
  }
  else
  {
    
  }

  if (pontos1 > pontos2)
  {
    equipa_aux = hashEquipa->tb[h_eq1];
    aumentaGanhos(hashEquipa, equipa_aux, h_eq1, equipa1);
  }
  else
  {
    
  }

  if (pontos1 < pontos2)
  {
    equipa_aux = hashEquipa->tb[h_eq2];
    aumentaGanhos(hashEquipa, equipa_aux, h_eq2, equipa2);
  }
  else
  {
    
  }

  novo_jogo = malloc(sizeof(NoListaJogos));
  hash_jogo->tb_jogo[h] = cria_no(hash_jogo->tb_jogo[h]);
  novo_jogo->nome_jogo = aloca_memoria(nome_jogo);
  novo_jogo->equipa1 = aloca_memoria(equipa1);
  novo_jogo->equipa2 = aloca_memoria(equipa2);
  novo_jogo->pontos1 = pontos1;
  novo_jogo->pontos2 = pontos2;
  novo_jogo->anterior = Lista_jogos->fim;
  novo_jogo->proximo = 0;
  if (Lista_jogos->fim != 0)
  {
    Lista_jogos->fim->proximo = novo_jogo;
  }
  else
  {
    Lista_jogos->inicio = novo_jogo;
  }

  Lista_jogos->fim = novo_jogo;
  hash_jogo->tb_jogo[h]->informacoes_jogo = novo_jogo;
  *Nr_linha += 1;
}

void print_info_jogo(int *Nr_linha, hash_node *cp)
{
  printf("%d %s %s %s %d %d\n", *Nr_linha, cp->informacoes_jogo->nome_jogo, cp->informacoes_jogo->equipa1, cp->informacoes_jogo->equipa2, cp->informacoes_jogo->pontos1, cp->informacoes_jogo->pontos2);
}

void procura_jogo(hash_table *t, int *Nr_linha)
{
  char jogo[1024];
  hash_node *jogo_aux;
  size_t h;
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  h = hash(jogo, t->capacidade);
  for (jogo_aux = t->tb_jogo[h]; jogo_aux; jogo_aux = jogo_aux->proximoNo)
  {
    if (strcmp(jogo_aux->informacoes_jogo->nome_jogo, jogo) == 0)
    {
      print_info_jogo(Nr_linha, jogo_aux);
      *Nr_linha += 1;
      return;
    }
    else
    {
      
    }

  }

  printf("%d Jogo inexistente.\n", *Nr_linha);
  *Nr_linha += 1;
}

void tiraVitorias(hash_table_equipa *eq, hash_node_equipa *equipa_aux, char *equipa, size_t h_eq)
{
  for (equipa_aux = eq->tb[h_eq]; equipa_aux; equipa_aux = equipa_aux->next)
  {
    if (strcmp(equipa_aux->equipa1, equipa) == 0)
    {
      equipa_aux->vitorias -= 1;
      return;
    }
    else
    {
      
    }

  }

}

void acrescenta_vitorias(hash_table_equipa *eq, hash_node_equipa *equipa_aux, char *equipa, size_t h_eq)
{
  for (equipa_aux = eq->tb[h_eq]; equipa_aux; equipa_aux = equipa_aux->next)
  {
    if (strcmp(equipa_aux->equipa1, equipa) == 0)
    {
      equipa_aux->vitorias += 1;
      return;
    }
    else
    {
      
    }

  }

}

void altera_score(hash_table *t, int *Nr_linha, hash_table_equipa *eq)
{
  int pontos_novo1;
  int pontos_novo2;
  char jogo[1024];
  size_t h_eq1;
  size_t h_eq2;
  size_t h;
  hash_node_equipa *equipa_aux;
  hash_node *jogo_aux;
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  pontos_novo1 = new_sym_var(sizeof(int) * 8);
  pontos_novo2 = new_sym_var(sizeof(int) * 8);
  if (verificaExiste_jogo(t, jogo) == 1)
  {
    printf("%d Jogo inexistente.\n", *Nr_linha);
    *Nr_linha += 1;
    return;
  }
  else
  {
    
  }

  h = hash(jogo, t->capacidade);
  for (jogo_aux = t->tb_jogo[h]; jogo_aux; jogo_aux = jogo_aux->proximoNo)
  {
    if (strcmp(jogo_aux->informacoes_jogo->nome_jogo, jogo) == 0)
    {
      h_eq1 = hash(jogo_aux->informacoes_jogo->equipa1, eq->capacidade_equipa);
      h_eq2 = hash(jogo_aux->informacoes_jogo->equipa2, eq->capacidade_equipa);
      if (jogo_aux->informacoes_jogo->pontos1 > jogo_aux->informacoes_jogo->pontos2)
      {
        equipa_aux = eq->tb[h_eq1];
        tiraVitorias(eq, equipa_aux, jogo_aux->informacoes_jogo->equipa1, h_eq1);
      }
      else
      {
        
      }

      if (jogo_aux->informacoes_jogo->pontos2 > jogo_aux->informacoes_jogo->pontos1)
      {
        equipa_aux = eq->tb[h_eq2];
        tiraVitorias(eq, equipa_aux, jogo_aux->informacoes_jogo->equipa2, h_eq2);
      }
      else
      {
        
      }

      jogo_aux->informacoes_jogo->pontos1 = pontos_novo1;
      jogo_aux->informacoes_jogo->pontos2 = pontos_novo2;
      if (pontos_novo1 > pontos_novo2)
      {
        equipa_aux = eq->tb[h_eq1];
        acrescenta_vitorias(eq, equipa_aux, jogo_aux->informacoes_jogo->equipa1, h_eq1);
      }
      else
      {
        
      }

      if (pontos_novo2 > pontos_novo1)
      {
        equipa_aux = eq->tb[h_eq2];
        acrescenta_vitorias(eq, equipa_aux, jogo_aux->informacoes_jogo->equipa2, h_eq2);
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  *Nr_linha += 1;
}

void remove_no(inicioFimJogos *lista, hash_node *jogo_aux)
{
  if (jogo_aux->informacoes_jogo->anterior == 0)
  {
    lista->inicio = jogo_aux->informacoes_jogo->proximo;
  }
  else
  {
    jogo_aux->informacoes_jogo->anterior->proximo = jogo_aux->informacoes_jogo->proximo;
  }

  if (jogo_aux->informacoes_jogo->proximo == 0)
  {
    lista->fim = jogo_aux->informacoes_jogo->anterior;
  }
  else
  {
    jogo_aux->informacoes_jogo->proximo->anterior = jogo_aux->informacoes_jogo->anterior;
  }

  free(jogo_aux->informacoes_jogo->equipa1);
  free(jogo_aux->informacoes_jogo->equipa2);
}

void removeDaHash(hash_node *temp, hash_node *ant, hash_table *t, char *nome_jogo, size_t h)
{
  if (strcmp(temp->informacoes_jogo->nome_jogo, nome_jogo) == 0)
  {
    t->tb_jogo[h] = temp->proximoNo;
    free(temp);
    return;
  }
  else
  {
    
  }

  while ((temp != 0) && (strcmp(temp->informacoes_jogo->nome_jogo, nome_jogo) != 0))
  {
    ant = temp;
    temp = temp->proximoNo;
  }

  if (temp == 0)
  {
    return;
  }
  else
  {
    
  }

  ant->proximoNo = temp->proximoNo;
  free(temp->informacoes_jogo->nome_jogo);
  free(temp->informacoes_jogo);
  free(temp);
}

void remove_jogo_aux(hash_table *t, hash_table_equipa *eq, inicioFimJogos *lista, char *nome_jogo)
{
  hash_node_equipa *equipa_aux;
  hash_node_equipa *equipa_aux_2;
  size_t h_eq1;
  size_t h_eq2;
  size_t h = hash(nome_jogo, t->capacidade);
  hash_node *jogo_aux;
  hash_node *temp = t->tb_jogo[h];
  hash_node *ant = t->tb_jogo[h];
  for (jogo_aux = t->tb_jogo[h]; jogo_aux; jogo_aux = jogo_aux->proximoNo)
  {
    if (strcmp(jogo_aux->informacoes_jogo->nome_jogo, nome_jogo) == 0)
    {
      if (jogo_aux->informacoes_jogo->pontos1 > jogo_aux->informacoes_jogo->pontos2)
      {
        h_eq1 = hash(jogo_aux->informacoes_jogo->equipa1, eq->capacidade_equipa);
        equipa_aux = eq->tb[h_eq1];
        tiraVitorias(eq, equipa_aux, jogo_aux->informacoes_jogo->equipa1, h_eq1);
        remove_no(lista, jogo_aux);
        removeDaHash(temp, ant, t, nome_jogo, h);
        return;
      }
      else
      {
        
      }

      if (jogo_aux->informacoes_jogo->pontos2 > jogo_aux->informacoes_jogo->pontos1)
      {
        h_eq2 = hash(jogo_aux->informacoes_jogo->equipa2, eq->capacidade_equipa);
        equipa_aux_2 = eq->tb[h_eq2];
        tiraVitorias(eq, equipa_aux_2, jogo_aux->informacoes_jogo->equipa2, h_eq2);
        remove_no(lista, jogo_aux);
        removeDaHash(temp, ant, t, nome_jogo, h);
        return;
      }
      else
      {
        
      }

      if (jogo_aux->informacoes_jogo->pontos2 == jogo_aux->informacoes_jogo->pontos1)
      {
        remove_no(lista, jogo_aux);
        removeDaHash(temp, ant, t, nome_jogo, h);
        return;
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

void remove_jogo(hash_table *t, hash_table_equipa *eq, inicioFimJogos *lista, int *Nr_linha)
{
  char nome_jogo[1024];
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  if (verificaExiste_jogo(t, nome_jogo) == 1)
  {
    printf("%d Jogo inexistente.\n", *Nr_linha);
    *Nr_linha += 1;
    return;
  }
  else
  {
    
  }

  *Nr_linha += 1;
  remove_jogo_aux(t, eq, lista, nome_jogo);
}

void lista_todos(inicioFimJogos *inicioFim, int *Nr_linha)
{
  NoListaJogos *aux = inicioFim->inicio;
  if (aux == 0)
  {
    *Nr_linha += 1;
    return;
  }
  else
  {
    
  }

  while (aux != 0)
  {
    printf("%d %s %s %s %d %d\n", *Nr_linha, aux->nome_jogo, aux->equipa1, aux->equipa2, aux->pontos1, aux->pontos2);
    aux = aux->proximo;
  }

  *Nr_linha += 1;
}

void free_hash_table_jogo(hash_table *t)
{
  hash_node *a;
  size_t i;
  for (i = 0; i < t->capacidade; i++)
  {
    while (t->tb_jogo[i])
    {
      a = t->tb_jogo[i]->proximoNo;
      free(t->tb_jogo[i]);
      t->tb_jogo[i] = a;
    }

  }

  free(t->tb_jogo);
  free(t);
}

void liberta_dupla(inicioFimJogos *lista)
{
  while (lista->inicio)
  {
    NoListaJogos *temp = lista->inicio;
    if (lista->inicio)
    {
      lista->inicio = lista->inicio->proximo;
      free(temp->nome_jogo);
      free(temp->equipa1);
      free(temp->equipa2);
      free(temp);
    }
    else
    {
      
    }

  }

  free(lista);
}

