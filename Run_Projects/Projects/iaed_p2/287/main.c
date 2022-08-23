#include <stdio.h>
#include "equipas.h"
#include "comandos.h"

#include "jogos.h"

int main() {
    link_equi * equipas;
    link_jogo * jogos_hashtable;
    Lista_jogos jogos_ls;
    
    
    equipas = inicia_tab_equi(TAM_HASHTABLE_EQUI);
    jogos_hashtable = init_tab_jogos();
    jogos_ls = inicia_ls();
    
  
    le_comandos(equipas,jogos_hashtable,jogos_ls);
    
    apaga_tab_equi(equipas);
    apaga_tab_jogos(jogos_hashtable);
    apaga_ls_jogos(jogos_ls);
    
    return 0;
}
