#ifndef EQUIPAS_H
#define EQUIPAS_H

/* Estrutura das equipas. */
typedef struct equipa{
	struct equipa *next;
	char *nome;
	int ganhos;
}Equipa;


typedef char *Chave;

#define nome_e(a) (a->nome)
#define jogos_ganhos(a) (a->ganhos)
#define proxima_e(a) (a->next) 

Equipa *cria_equipa(char *nome);
void altera_ganhos(Equipa *head, int S);
void free_equipa(Equipa *head);

#endif /* EQUIPAS_H */



