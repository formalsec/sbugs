#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_jogos.h"

#define SIZEJ 1069

/*init_jogo inicia a hashtable jogos*/
link_jogo * init_jogo(int m){
  int i;
  link_jogo* tabela_jogos;
  tabela_jogos = (link_jogo*)can_fail_malloc(m*sizeof(link_jogo));
  for(i=0; i<m; i++){
    tabela_jogos[i] = NULL;
  }
  return tabela_jogos;
}

/*cria um novo jogo assim como o espaco*/
link_jogo novo_jogo(char* nome, char*equipa1, char*equipa2, int score1, int score2){
  link_jogo x = (link_jogo) can_fail_malloc(sizeof(struct node_jogos));
  x->jogo = (pJogo) can_fail_malloc(sizeof(struct jogo));
  x->jogo->nome = (char*) can_fail_malloc((strlen(nome) + 1) * sizeof(char));
  strcpy(x->jogo->nome, nome);
  x->jogo->equipa1 = (char*) can_fail_malloc((strlen(equipa1) + 1) * sizeof(char));
  strcpy(x->jogo->equipa1, equipa1);
  x->jogo->equipa2 = (char*) can_fail_malloc((strlen(equipa2) + 1) * sizeof(char));
  strcpy(x->jogo->equipa2, equipa2);
  x->jogo->score1 = score1;
  x->jogo->score2 = score2;
  x->next = NULL;
  return x;
}
/*procura um jogo numa lista*/
link_jogo procura_lista_jogo(link_jogo head, char*nome){
  link_jogo t;
  for (t= head; t != NULL; t = t->next){
    if (strcmp(t->jogo->nome, nome)== 0){
      return t;
    }
  }
  return NULL;
}
/*inserir jogo no inicio da lista */
link_jogo insere_lista_jogo(link_jogo head, link_jogo jogo){
  link_jogo x= novo_jogo(jogo->jogo->nome, jogo->jogo->equipa1, jogo->jogo->equipa2, jogo->jogo->score1, jogo->jogo->score2);
  x->next = head;
  return x;

}
/*remove um jogo duma lista*/
link_jogo remove_jogo_lista(link_jogo head, char* nome){
  if (head == NULL)
    return NULL;

  if (strcmp(head->jogo->nome, nome)==0) {
    link_jogo t;

    t = head->next;

    free(head->jogo->nome);
    free(head->jogo->equipa1);
    free(head->jogo->equipa2);
    free(head->jogo);
    free(head);


    return t;
  }

  head->next = remove_jogo_lista(head->next, nome);


  return head;
}

link_jogo remove_lista(link_jogo head){
  if (head == NULL)
    return NULL;

  else{
    link_jogo t;

    t = head->next;

    free(head->jogo->nome);
    free(head->jogo->equipa1);
    free(head->jogo->equipa2);
    free(head->jogo);
    free(head);

    return t;
  }

  head->next = remove_lista(head->next);


  /*
   * Return the pointer to where we were called
   * from.  Since we did not remove this node it
   * will be the same.
   */
  return head;
}

/*funcao de dispersao para stringss*/
int hash_string(char *v, int M){
  int h = 0, a = 127;
  for (;*v != '\0'; v++){
    h = (a*h + *v) % M;
  }
  return h;
}


/*procura jogo na hastable*/
link_jogo procura_jogo(char *nome, link_jogo* tabela_jogos){
  int i;
  i = hash_string(nome, SIZEJ);
  return procura_lista_jogo(tabela_jogos[i], nome);
}
/*insere jogo na hashtable jogos*/
link_jogo* insere_jogo(link_jogo jogo, link_jogo* tabela_jogos){
  int i = hash_string(jogo->jogo->nome, SIZEJ);
  tabela_jogos[i] = insere_lista_jogo(tabela_jogos[i], jogo);
  return tabela_jogos;
}

/*apaga um jogo da hashtable jogos*/
link_jogo* apaga_jogo(char *nome, link_jogo* tabela_jogos){
  int i = hash_string(nome, SIZEJ);
  tabela_jogos[i]= remove_jogo_lista(tabela_jogos[i], nome);
  return tabela_jogos;
}
/*apaga um jogo da lista */
link_jogo apaga_jogo_2(char *nome, link_jogo lista_jogos){
  lista_jogos = remove_jogo_lista(lista_jogos, nome);
  return lista_jogos;
}
/* insere um jogo na lista */
link_jogo insere_jogo_2(link_jogo jogo, link_jogo lista_jogos){
  lista_jogos = insere_lista_jogo(lista_jogos, jogo);
  return lista_jogos;
}
/*insere um jogo no fim da lista*/
link_jogo insere_lista_jogo_2(link_jogo head, link_jogo jogo){
  link_jogo x;
  if (head==NULL){
    return novo_jogo(jogo->jogo->nome, jogo->jogo->equipa1, jogo->jogo->equipa2, jogo->jogo->score1, jogo->jogo->score2);
  }
  for (x=head;x->next != NULL; x = x->next);
  x->next = novo_jogo(jogo->jogo->nome, jogo->jogo->equipa1, jogo->jogo->equipa2, jogo->jogo->score1, jogo->jogo->score2);
  return head;
}

/*print dos jogos de acordo com o comando l*/
void print_jogos(link_jogo head, int linha){
  link_jogo t;
  for (t= head; t!=  NULL; t= t->next){
    printf("%d %s %s %s %d %d\n",linha, t->jogo->nome, t->jogo->equipa1, t->jogo->equipa2, t->jogo->score1, t->jogo->score2);
  }
}

/*altera o score de um jogo*/
void altera_jogo(link_jogo jogo, int score1, int score2){
  jogo->jogo->score1 = score1;
  jogo->jogo->score2 = score2;
}

/*altera o score de um jogo numa lista*/
link_jogo altera_jogo_2(char* nome, int score1, int score2, link_jogo lista_jogos){
  link_jogo x;
  x = procura_lista_jogo(lista_jogos, nome);
  x->jogo->score1 = score1;
  x->jogo->score2 = score2;
  return lista_jogos;
}



link_jogo* liberta_jogos(link_jogo* tabela_jogos){
  int i;
    /*liberta a hashtable*/
    for (i=0; i<SIZEJ; i++){
      tabela_jogos[i] = remove_lista(tabela_jogos[i]);
    }
    return tabela_jogos;
}
