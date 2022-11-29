#ifndef _HASHEQUIPA_
#define _HASHEQUIPA_

#include "equipa.h"
#include "listaEquipa.h"

listaEquipa** criaHashTableEquipa(int M_E);
void          freeHashTableEquipa(listaEquipa** headsEquipas, int M_E);

listaEquipa** insereHashTableEquipa(listaEquipa** headsEquipas, equipa* Equipa, int M_E);
listaEquipa** removeHashTableEquipa(char* nome, listaEquipa** headsEquipas, int M_E);

equipa*       procuraHashTableEquipa(listaEquipa** headsEquipas, char* nome, int M_E);
int           equipaExiste(listaEquipa** headsEquipas, char* nome, int M_E);



#endif
