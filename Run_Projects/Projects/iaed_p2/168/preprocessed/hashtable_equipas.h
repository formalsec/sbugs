#include "Equipa.h"

void HTinic_equipas(Equipa **equipas, int M);

void HTinsere_equipa(Equipa* equipa, Equipa **equipas, int dim);

Equipa* HTprocura_equipa(char *nome, Equipa **equipas, int dim);

void HTencontra_mais_vitorias(Equipa **equipas, int dim, int conta_linhas);

void HTfree_equipas(Equipa **equipas, int dim);
