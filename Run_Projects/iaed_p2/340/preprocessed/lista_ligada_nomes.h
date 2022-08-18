#ifndef LISTA_H
#define LISTA_H


/* Estrutura das listas ligadas (jogos e equipas). */
typedef struct lista{
	struct lista *previous;
	struct lista *next;
	char *nome;
}Lista;


#define nome_lista(a) (a->nome)
#define proximo_elemento(a) (a->next) 
#define elemento_anterior(a) (a->previous)
#define lista_nomes_jogos(a) (a[0])

Lista **inicializa_lista(Lista **lista);
Lista *cria_elemento(char *nome);
void adiciona_elemento(Lista **lista, Lista *el, Lista **ultimo_jogo);
Lista **remove_el(Lista **lista, Lista **ultimo_jogo, char *nome);
void free_el(Lista *head);

#endif /* LISTA_H */