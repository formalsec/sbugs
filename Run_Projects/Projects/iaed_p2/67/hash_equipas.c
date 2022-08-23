#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_equipas.h"

#define hash(A,B) (A%B)
#define SIZEE 1069

/*inicia a hashtable de uma equipa*/
link_equipa* init_equipa(int n){
  link_equipa *tabela_equipas;
  int i;
  tabela_equipas = (link_equipa*)malloc(n* sizeof(link_equipa));
  for(i=0; i<n; i++){
    tabela_equipas[i] = NULL;
  }
  return tabela_equipas;
}


/* cria uma equipa */
link_equipa nova_equipa(char *nome){
  link_equipa x = (link_equipa) malloc(sizeof(struct node_equipa));
  x->equipa = (pEquipa) malloc(sizeof(struct equipa));
  x->equipa->nome = (char*) malloc((strlen(nome) + 1) * sizeof(char));
  strcpy(x->equipa->nome, nome);
  x->equipa->vitorias = 0;
  x->next = NULL;
  return x;
}


/*procura uma equipa numa lista*/
link_equipa procura_lista_equipa(link_equipa head, char *nome){
  link_equipa t;
  for (t = head; t != NULL; t = t->next){
    if (strcmp(t->equipa->nome, nome)==0){
      return t;
    }
  }
  return NULL;
}

/*insere uma equipa numa lista*/
link_equipa insere_equipa_lista(link_equipa head, char* nome){
  link_equipa x = nova_equipa(nome);
  x->next = head;
  return x;
}
/*remove um jogo duma lista*/
link_equipa remove_equipa_lista(link_equipa head, char* nome){
  if (head == NULL)
    return NULL;

  if (strcmp(head->equipa->nome, nome)==0) {
    link_equipa t;

    t = head->next;

    free(head->equipa->nome);
    free(head->equipa);
    free(head);

    return t;
  }

  head->next = remove_equipa_lista(head->next, nome);


  return head;
}


link_equipa remove_lista_2(link_equipa head){
  if (head == NULL)
    return NULL;

  else{
    link_equipa t;

    t = head->next;

    /* Deallocate the node. */
    free(head->equipa->nome);
    free(head->equipa);
    free(head);

    return t;
  }

  head->next = remove_lista_2(head->next);

  return head;
}

/*funcao hash para strings*/
int hash_strings(char *v, int N){
  int h = 0, a = 127;
  for (;*v != '\0'; v++){
    h = (a*h + *v) % N;
  }
  return h;
}

/*procura uma equipa*/
link_equipa procura_equipa(char* nome, link_equipa* tabela_equipas){
  int i = hash_strings(nome, SIZEE);
  return procura_lista_equipa(tabela_equipas[i], nome);
}
/*insere uma equipa*/
link_equipa* insere_equipa(link_equipa equipa, link_equipa* tabela_equipas){
  int i = hash_strings(equipa->equipa->nome, SIZEE);
  tabela_equipas[i] = insere_equipa_lista(tabela_equipas[i], equipa->equipa->nome);
  return tabela_equipas;
}
/*apaga uma equipa*/
link_equipa* apaga_equipa(char* nome, link_equipa *tabela_equipas){
  int i = hash_strings(nome, SIZEE);
  tabela_equipas[i] = remove_equipa_lista(tabela_equipas[i], nome);
  return tabela_equipas;
}

link_equipa insere_equipa_2(link_equipa equipa, link_equipa lista_equipas){
  lista_equipas = insere_equipa_lista_2(lista_equipas, equipa);
  return lista_equipas;
}

link_equipa insere_equipa_lista_2(link_equipa head, link_equipa equipa){
  link_equipa x;
  if (head==NULL){
    return nova_equipa(equipa->equipa->nome);
  }
  for (x=head;x->next!=NULL; x = x->next);
  x->next = nova_equipa (equipa->equipa->nome);
  return head;
}

void print_equipas(link_equipa head, int linha){
  link_equipa t;
  for (t= head; t!=  NULL; t= t->next){
    printf("%d %s %d\n",linha, t->equipa->nome, t->equipa->vitorias);
  }
}

/*atribui uma vitoria*/
void atribui_vitoria(char* nome, link_equipa* tabela_equipas){
  link_equipa x;
  x = procura_equipa(nome, tabela_equipas);
  x->equipa->vitorias++;
}
/*remove uma vitoria*/
void remove_vitoria(char* nome, link_equipa* tabela_equipas){
  link_equipa x;
  x = procura_equipa(nome, tabela_equipas);
  x->equipa->vitorias--;
}

/*atribui uma vitoria*/
link_equipa atribui_vitoria_2(char* nome, link_equipa lista_equipas){
  link_equipa x;
  x = procura_lista_equipa(lista_equipas, nome);
  x->equipa->vitorias++;
  return lista_equipas;
}
/*remove uma vitoria*/
link_equipa remove_vitoria_2(char* nome, link_equipa lista_equipas){
  link_equipa x;
  x = procura_lista_equipa(lista_equipas, nome);
  x->equipa->vitorias--;
  return lista_equipas;
}

link_equipa apaga_equipa_2(char *nome, link_equipa lista_equipas){
  lista_equipas = remove_equipa_lista(lista_equipas, nome);
  return lista_equipas;
}

link_equipa* liberta_equipas(link_equipa* tabela_equipas){
  int i;
    /*liberta a hashtable*/
    for (i=0; i<SIZEE; i++){
      tabela_equipas[i] = remove_lista_2(tabela_equipas[i]);
    }
    return tabela_equipas;
}
