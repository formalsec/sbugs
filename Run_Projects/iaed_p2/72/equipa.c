#include "equipa.h"

/*
  cria_equipa: (char*, int) -> Equipa
  Cria e inicializa uma estrutura Equipa
*/
Equipa cria_equipa(char* nome, int size_nome){
    Equipa nova;
        
    nova = malloc(sizeof(struct equipa));
    nome_equipa(nova) = malloc(size_nome*sizeof(char));
    vitorias_equipa(nova) = 0;
    
    strncpy(nome_equipa(nova),nome,size_nome);

    return nova;
}

/*
  adiciona_vitoria: (Equipa) -> ()
  Adiciona uma vitoria a equipa
*/
void adiciona_vitoria(Equipa eq){
    vitorias_equipa(eq) += 1;
}

/*
  remove_vitoria: (Equipa) -> ()
  Remove uma vitoria a equipa caso o seu numero de vitorias
  seja maior que 0
*/
void remove_vitoria(Equipa eq){
    if(vitorias_equipa(eq) > 0)
        vitorias_equipa(eq) -= 1;
}

/*
  free_equipa: (Equipa) -> ()
  Liberta o espaco alocado para uma equipa 
*/
void free_equipa(Equipa eq){
    free(nome_equipa(eq));
    free(eq);
}
